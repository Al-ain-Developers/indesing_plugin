//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCInlineGraphicGlyphNode.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IComposeScanner.h"
#include "IDrawingStyle.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRenderData.h"
#include "IWaxGlyphs.h"
#include "ITextModel.h"
#include "IItemStrand.h"
#include "IGeometry.h"
#include "IInlineGraphic.h"

// General Includes:
#include "CreateObject.h"
#include "TextChar.h"
#include "Trace.h"
#include "TextID.h"

// Project:
#include "SLC.h"
#include "SLCInlineGraphicGlyphNode.h"

/* Constructor
*/
SLCInlineGraphicGlyphNode::SLCInlineGraphicGlyphNode(IComposeScanner* composeScanner,
													 IDrawingStyle* drawingStyle,
													 TextIndex startingIndex,
													 const PMReal& xOffset) :
    SLCGlyphNode(composeScanner, drawingStyle, startingIndex, xOffset, kGNTInlineGraphic),
	fInlineUIDRef(UIDRef(nil, kInvalidUID))
{
	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode\n");
}

/* Destructor
*/
SLCInlineGraphicGlyphNode::~SLCInlineGraphicGlyphNode(void)
{
	TRACEFLOW("SLCGlyphNode", "~SLCInlineGraphicGlyphNode\n");
}

/* GetGlyph
*/
SLComposerStatusCode SLCInlineGraphicGlyphNode::GetGlyph
	(
	const UTF32TextChar& character,
	Text::GlyphID& glyphID,
	PMReal& glyphWidth
	)
{
	// This glyph node can only buffer a single inline graphic.
	// If it already contains data indicate that the character
	// cannot be handled.
	SLComposerStatusCode status = kCompIncompatibleCharacter;
	if (this->GetTextSpan() == 0)
	{
		// Buffer the inline graphic associated with this character.
		if (character.GetValue() == kTextChar_ObjectReplacementCharacter)
		{
			status = this->GetInlineGraphic(glyphWidth);
			// The glyphID that corresponds to an inline is kInvalidGlyphID.
			glyphID = kInvalidGlyphID;
		}
	}
	return status;
}

/* BufferGlyph
*/
SLComposerStatusCode SLCInlineGraphicGlyphNode::BufferGlyph
	(
	const UTF32TextChar& character,
	const Text::GlyphID& glyphID,
	const PMReal& glyphWidth
	)
{
	// This method can get called once per instance, the object only stores a single inline.
	SLComposerStatusCode status = kCompIncompatibleCharacter;
	if (this->GetTextSpan() == 0 &&
		character.GetValue() == kTextChar_ObjectReplacementCharacter)
	{
		this->SetTextSpan(1);
		status = kCompSuccess;
	}
	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode::BufferGlyph() status=%d, character=0x%x, glyphID=0x%x, glyphWidth=%f\n",
			  status,
			  character.GetValue(),
			  glyphID,
			  ::ToDouble(glyphWidth));
	return status;
}

/* GetInlineGraphic
*/
SLComposerStatusCode SLCInlineGraphicGlyphNode::GetInlineGraphic(PMReal& glyphWidth)
{
	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode::GetInlineGraphic()-->In\n");

	SLComposerStatusCode status = kCompFailure;
	glyphWidth = 0.0;
	do
	{
		InterfacePtr<ITextModel> textModel(fComposeScanner, UseDefaultIID());
		ASSERT(textModel != nil);
		if (textModel == nil)
		{
			break;
		}
		InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID));
		ASSERT(itemStrand != nil);
		if (itemStrand == nil)
		{
			break;
		}
		UID inlineUID = itemStrand->GetOwnedUID(this->GetTextIndex(), kInlineBoss);
		ASSERT_MSG(inlineUID != kInvalidUID, FORMAT_ARGS("Owned item at TextIndex %d is missing from IItemStrand", this->GetTextIndex()));
		if (inlineUID == kInvalidUID)
		{
			// Can't find the owned item that should be associated with this character.
			// Just carry on. We won't create wax.
			status = kCompSuccess;
			break;
		}

		// If we get here we have an inline graphic.
		// Size the dimensions of the glyph to the dimensions of the inline.
		InterfacePtr<IGeometry> pageItem(::GetDataBase(fComposeScanner), inlineUID, UseDefaultIID());
		ASSERT(pageItem != nil);
		if (pageItem == nil)
		{
			break;
		}
		fInlineUIDRef = ::GetUIDRef(pageItem);
		fInlineBoundingBox = pageItem->GetStrokeBoundingBox();
		glyphWidth = this->GetWidth();

		// Inline geometry is maintained relative to the baseline of the text.
		this->SetHeight(-fInlineBoundingBox.Top());

		status = kCompSuccess;
	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode::GetInlineGraphic()-->Out status=%d, glyphWidth=%f, glyphHeight=%f\n",
			  status,
			  ::ToDouble(glyphWidth),
			  ::ToDouble(fLeading));

	return status;
}

/* CreateWax
*/
SLComposerStatusCode SLCInlineGraphicGlyphNode::CreateWax(const IWaxLine* waxLine) const
{
	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode::CreateWax()-->In\n");
	SLComposerStatusCode status = kCompFailure;
	do
	{
		ASSERT(waxLine != nil);
		if (waxLine == nil)
		{
			break;
		}

		InterfacePtr<IWaxRun> waxRun(this->CreateWaxRun());
		if (waxRun == nil)
		{
			break;
		}

		InterfacePtr<IInlineGraphic> inlineGraphic(waxRun, UseDefaultIID());
		ASSERT(inlineGraphic != nil);
		if (inlineGraphic == nil)
		{
			break;
		}
		inlineGraphic->SetGraphic(fInlineUIDRef);

		InterfacePtr<IWaxGlyphs> waxGlyphs(waxRun, UseDefaultIID());
		ASSERT(waxGlyphs != nil);
		if (waxGlyphs == nil)
		{
			break;
		}
		TRACEFLOW("SLCGlyphNodeAddGlyph", "fGlyphIDs [0]=0x%x, fGlyphWidths [0]=%f ILG\n",
				  kInvalidGlyphID,
				  ::ToDouble(this->GetWidth()));
		waxGlyphs->AddGlyph(kInvalidGlyphID, ::ToFloat(this->GetWidth()));

		// Add the wax run to the line.
		// InDesign 2.0 note: IWaxLine no longer has AddRun method. Use IWaxCollection instead
		InterfacePtr<IWaxCollection> waxCollection(waxLine, UseDefaultIID());
		ASSERT(waxCollection != nil);
		if (waxCollection == nil)
		{
			break;
		}
		waxCollection->AddRun(waxRun);

		status = kCompSuccess;

	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCInlineGraphicGlyphNode::CreateWax()-->Out status=%d\n", status);

	return status;
}

/* CreateWaxRun
*/
IWaxRun* SLCInlineGraphicGlyphNode::CreateWaxRun() const
{
	IWaxRun* result = nil;

	do
	{
		// Check we have an inline buffered.
		ASSERT(this->GetTextSpan() == 1);
		if (this->GetTextSpan() != 1)
		{
			break;
		}
		ASSERT(fInlineUIDRef != UIDRef(nil, kInvalidUID));
		if (fInlineUIDRef == UIDRef(nil, kInvalidUID))
		{
			break;
		}

		// Create inline graphic wax run boss.
		InterfacePtr<IWaxRun> waxRun(static_cast<IWaxRun*>(::CreateObject(kWaxILGRunBoss, IWaxRun::kDefaultIID)));
		ASSERT_MSG(waxRun != nil, "create kWaxILGRunBoss invalid");
		if (waxRun == nil)
		{
			break;
		}
		waxRun->SetXPosition(fXOffset);
		waxRun->SetYPosition(fDrawingStyle->GetEffectiveBaseline());

		// InDesign 2.0 note: Adornments have to be setup via a new method to account
		// for cases where there is no IWaxRenderData but there are adornments.
		fDrawingStyle->AddAdornments(waxRun);

		result = waxRun;
		result->AddRef();

	} while (false);

	return result;

}

/* SetHeight
*/
void SLCInlineGraphicGlyphNode::SetHeight(const PMReal& height)
{
	fLeading = height;
	fAscent = height;
	fCapHeight = height;
	fXHeight = height;
}

// End SLCInlineGraphicGlyphNode.cpp.

