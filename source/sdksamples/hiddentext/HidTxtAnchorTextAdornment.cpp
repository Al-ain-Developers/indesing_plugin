//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtAnchorTextAdornment.cpp $
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
#include "IGlobalTextAdornment.h" // for kTAPriMissingGlyphs
#include "IGraphicsPort.h"
#include "ITextAdornment.h"
#include "ITextAdornmentData.h"
#include "IWaxGlyphs.h"
#include "IBoolData.h"
#include "ITextModel.h"
#include "ITextUtils.h"
#include "IWaxRunShape.h"

// General:
#include "AutoGSave.h"
#include "CPMUnknown.h"
#include "PMLineSeg.h"
#include "OwnedItemDataList.h"
#include "K2Vector.h"
#include "Utils.h"


// Project:
#include "HidTxtID.h"

/** Implements a text adornment(ITextAdornment) that indicates the presence of 
	hidden text in the text flow by drawing a pin icon in the shape of a 
	red triangle at the TextIndex on which the hidden text is anchored.

	The adornment only draws when an IBoolData interface is added to the adornment
	boss class under the IID IID_IHIDTXTSHOWADORNMENTBOOLDATA. The interface provides 
	a flag that indicates the HiddenTextEditor is installed. The adornment only draws
	when the HiddenTextEditor is installed.

	@ingroup hiddentext
	
	@see ITextAdornment
*/
class HidTxtAnchorTextAdornment : public CPMUnknown<ITextAdornment>
{
	public:
		/** Constructor 
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		HidTxtAnchorTextAdornment(IPMUnknown *boss);

		/** Destructor
		*/
		~HidTxtAnchorTextAdornment();

	public:

		/** This adornment draws within the selection bounds of the wax line so 
			it doesn't modify the ink bounds.
			@see ITextAdornment::GetInkBounds for a description of the parameters.
		*/
		virtual void GetInkBounds(PMRect* inkBounds, 
								  const PMRect& runInkBounds,
								  IWaxRun* run,
								  IWaxRenderData* renderData,
								  IWaxGlyphs* glyphs,
								  const ITextAdornmentData* data);

		/** Draw a pin like triangle, point down, to indicate the presence of 
			the hidden text anchor.
			@see ITextAdornment::Draw for a description of the parameters.
		*/
		virtual void Draw(GraphicsData* gd, 
						  int32 iShapeFlags, 
						  IWaxRun* run,
						  IWaxRenderData* renderData, 
						  IWaxGlyphs* glyphs,
						  const ITextAdornmentData* data);

		/** Return kTAPriMissingGlyphs so the adornment draws behind the text.
			@return kTAPriMissingGlyphs so the adornment draws behind the text.
			@see ITextAdornment::GetDrawPriority for a description of the parameters
		*/
		virtual Text::DrawPriority GetDrawPriority(void);

		/** Return nil, this adornment does not have any adornment data(ITextAdornmentData),
			so there's no data to split.
			@return nil
			@see ITextAdornment::SplitAt for a description of the parameters
		*/
		virtual ITextAdornmentData* SplitAt( 
				int32 offsetInRun, 
				IWaxRun* waxRun, IWaxRun* newWaxRun,
				ITextAdornmentData* data);

	private:
		/** List of indexes into the wax run being adorned at
			which hidden text is anchored.
		 */
		typedef K2Vector<int32>	AnchorCharIndexList;

	private:
		/** Scan scan for hidden text owned items in the range
			of text rapresented by the wax run and return their
			indexes in the wax run.
		*/
		void	CollectAnchorCharIndexList(
					IWaxRun* run, 
					const ClassID& desiredClass, 
					AnchorCharIndexList& anchors);

		/** Draw a red triangle icon on its point to indicate the
			presence of hidden text.
		*/
		void	DrawPinIcon(
					int32 anchorCharIndex, 
					IWaxRun* run, 
					IWaxGlyphs* waxGlyphs, 
					GraphicsData* gd);
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(HidTxtAnchorTextAdornment, kHidTxtAnchorTextAdornmentImpl)

/*
*/
HidTxtAnchorTextAdornment::HidTxtAnchorTextAdornment(IPMUnknown* boss) : CPMUnknown<ITextAdornment>(boss)
{
}

/*
*/
HidTxtAnchorTextAdornment::~HidTxtAnchorTextAdornment()
{
}

/*
*/
void HidTxtAnchorTextAdornment::GetInkBounds(
			PMRect* inkBounds,
			const PMRect& runInkBounds,
			IWaxRun* run,
			IWaxRenderData* renderData, 
			IWaxGlyphs* glyphs,
			const ITextAdornmentData* data)
{
}

/*
*/
void HidTxtAnchorTextAdornment::Draw(
			GraphicsData* gd, 
			int32 flags, 
			IWaxRun* run,
			IWaxRenderData* renderData,
			IWaxGlyphs* waxGlyphs,
			const ITextAdornmentData* data)
{
	do {
		// Test to see if the HiddenTextEditor plug-in is installed.
		// HiddenTextEditor adds the interface below to the adornment's
		// boss class when it is installed.
		InterfacePtr<IBoolData> showAdornmentBoolData(this, IID_IHIDTXTSHOWADORNMENTBOOLDATA);
		if (showAdornmentBoolData == nil || showAdornmentBoolData->Get() == kFalse) {
			// Don't show the presence of hidden text, the HiddenTextEditor plug-in is not present. 
			break;
		}

		// Validate parameters.
		ASSERT(run);
		if (run == nil) {
			break;
		}
		ASSERT(waxGlyphs);
		if (waxGlyphs == nil) {
			break;
		}

		// Collect the indexes in the wax run of of the characters
		// on which hidden text is anchored.
		AnchorCharIndexList anchors;
		this->CollectAnchorCharIndexList(run, kHidTxtModelBoss, anchors);

		// Draw a pin icon behind the character on which each 
		for (K2Vector<int32>::const_iterator const_iter = anchors.begin(); const_iter < anchors.end(); const_iter++) {
			this->DrawPinIcon(*const_iter, run, waxGlyphs, gd);
		} // end for

	} while (false);

}

/*
*/
Text::DrawPriority HidTxtAnchorTextAdornment::GetDrawPriority(void)
{
	return kTAPriMissingGlyphs;
}

/*
*/
ITextAdornmentData* HidTxtAnchorTextAdornment::SplitAt( 
				int32 offsetInRun, 
				IWaxRun* waxRun, IWaxRun* newWaxRun,
				ITextAdornmentData* data 
			)
{
    return nil;
}

/*
*/
void HidTxtAnchorTextAdornment::CollectAnchorCharIndexList(IWaxRun* run, 
											const ClassID& desiredClass, 
										AnchorCharIndexList& anchors)
{
	do {
		// Get the text model associated with this run.
		const IWaxLine* waxLine = run->GetWaxLine();
		ASSERT(waxLine);
		if (waxLine == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(waxLine->QueryTextModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		TextIndex startIndex = run->TextOrigin();
		int32 span = run->GetWaxSpan();
		// Get the TextIndex of each hidden text owned item in the given wax run.
		Utils<ITextUtils> textUtils;
		ASSERT(textUtils);
		if (!textUtils) {
			break;
		}
		OwnedItemDataList ownedItems;
		textUtils->CollectOwnedItems(textModel, startIndex, span, &ownedItems);
		for (OwnedItemDataList::iterator iter = ownedItems.begin(); iter < ownedItems.end(); iter++) {
			if (iter->fClassID == desiredClass) {
				anchors.push_back(iter->fAt - startIndex);
			}
		}
	} while(false);
}

/*
*/
void HidTxtAnchorTextAdornment::DrawPinIcon(int32 anchorCharIndex, IWaxRun* run, IWaxGlyphs* waxGlyphs, GraphicsData* gd)
{
	do {
		InterfacePtr<IWaxRunShape> waxRunShape(waxGlyphs, UseDefaultIID());
		ASSERT(waxRunShape);
		if (waxRunShape == nil) 
		{
			break;
		}
		PMLineSeg selection;
		waxRunShape->GetSelectionLine(&selection);

		// Calculate the position of some points to
		// represent a pin icon as a triangle defined 
		// by three points.
		// p1    p2           (top of selection for the line)
		//
		//
		//
		//
		//    p3              (bottom of selection of the line)
		PMPoint p1, p2, p3;
		const PMReal halfTriangleWidth = ((selection.Bottom() - selection.Top()) * 0.25) / 2;
		bool16 hasPerGlyphMatrix = waxGlyphs->HasPerGlyphMatrix();
		if (hasPerGlyphMatrix) {
			// Find the index of the glyph associated with the anchor.
			int32 startGlyphIndex = -1;
			int32 startGlyphLength = 0;
			waxGlyphs->MapCharsToGlyphs(anchorCharIndex, 1, &startGlyphIndex, &startGlyphLength);
			ASSERT(startGlyphIndex != -1);
			if (startGlyphIndex == -1) {
				startGlyphIndex = 0;
			}

			// Get the matrix that controls where the anchor glyph draws.
			// Transform the points of the triangle so that it draws 
			// correctly for text on a path.
			PMMatrix position = waxGlyphs->GetGlyphDrawPosition(startGlyphIndex);
			PMReal xPosition = run->GetXPosition();
			PMReal yPosition = run->GetYPosition();
			position.Translate(xPosition, yPosition);
			p1.X(0.0 - halfTriangleWidth);
			p1.Y(selection.Top());
			p2.X(0.0 + halfTriangleWidth);
			p2.Y(selection.Top());
			p3.X(0.0);
			p3.Y(selection.Bottom());
			position.Transform(&p1);
			position.Transform(&p2);
			position.Transform(&p3);
		}
		else {
			// Find the distance of the anchor glyph from the start of the run.
			PMReal glyphOffset;
			if (anchorCharIndex > 0) {
				// Escapement is through the desired index, so subtract 1
				glyphOffset = waxGlyphs->GetCharEscapementAt(anchorCharIndex-1);
			}
			else {
				glyphOffset = waxGlyphs->GetCharEscapementAt(0);
			}
			PMReal xPosition = run->GetXPosition() + glyphOffset;
			p1.X(xPosition - halfTriangleWidth);
			p1.Y(selection.Top());
			p2.X(xPosition + halfTriangleWidth);
			p2.Y(selection.Top());
			p3.X(xPosition);
			p3.Y(selection.Bottom());
		}

		// Draw the triangle.
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		ASSERT(gPort);
		if (gPort == nil) 
		{
			break;
		}
		AutoGSave autoGSave(gPort);
		gPort->newpath();
		gPort->moveto(p1.X(), p1.Y());
		gPort->lineto(p2.X(), p2.Y());
		gPort->lineto(p3.X(), p3.Y());
		gPort->closepath();
		gPort->setrgbcolor(PMReal(1.0), PMReal(0.0), PMReal(0.0));
		gPort->fill();
	} while(false);
}

// End, HidTxtAnchorTextAdornment.cpp.


