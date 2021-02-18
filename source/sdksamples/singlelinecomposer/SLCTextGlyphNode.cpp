//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTextGlyphNode.cpp $
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
#include "IFontInstance.h"
#include "IPMFont.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRenderData.h"
#include "IWaxGlyphs.h"

// General Includes:
#include "CreateObject.h"
#include "TextChar.h"
#include "Trace.h"

// Project:
#include "SLC.h"
#include "SLCTextGlyphNode.h"

// Chunk size used to allocate dynamic memory.
const int32 kBufSize = 32;


/* Constructor
*/
SLCTextGlyphNode::SLCTextGlyphNode(IComposeScanner* composeScanner,
								   IDrawingStyle* drawingStyle,
								   TextIndex startingIndex,
								   const PMReal& xOffset)
	: SLCGlyphNode(composeScanner, drawingStyle, startingIndex, xOffset, kGNTText), fFontInstance(nil), fBufferSize(0)
{
	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode\n");
	do
	{
		// Check parent class constructed OK.
		ASSERT(this->GetStatus() == kCompSuccess);
		if (this->GetStatus() != kCompSuccess)
		{
			break;
		}
		// Reset so this constructor can indicate status.
		fStatus = kCompFailure;

		// Initialise the buffer control member variables.
#if defined(USING_PTRS_FOR_MEMBERS)
		fGlyphIDs = new Text::GlyphID[kBufSize];
		fGlyphWidths = new PMReal[kBufSize];
		if (fGlyphIDs != nil && fGlyphWidths != nil)
		{
			fBufferSize = kBufSize;
		}
		else
		{
			fBufferSize = 0;
		}
#else
		fGlyphIDs.clear();
		fGlyphIDs.resize(kBufSize, kInvalidGlyphID);
		fGlyphWidths.clear();
		fGlyphWidths.resize(kBufSize, PMReal(0.0));
		if (fGlyphIDs.capacity() > 0 && fGlyphWidths.capacity() > 0)
		{
			fBufferSize = kBufSize;
		}
		else
		{
			fBufferSize = 0;
		}
#endif

		// Cache the font instance so we can get GlyphID's and metrics later on.
		fFontInstance = fDrawingStyle->QueryFontInstance(kFalse/*horizontal*/);
		ASSERT(fFontInstance != nil);
		if (fFontInstance == nil)
		{
			break;
		}

		// Cache font metric values.
		fPointSize = fDrawingStyle->GetPointSize();
		fLeading = fDrawingStyle->GetLeading();
		InterfacePtr<IPMFont> font(fDrawingStyle->QueryFont());
		ASSERT(font != nil);
		if (font == nil)
		{
			break;
		}
		fAscent = font->GetAscent(fPointSize);
		fCapHeight = font->GetCapHeight(fPointSize);
		fXHeight = font->GetXHeight(fPointSize);

		// Calculate the width adjustment that will be applied
		// to each glyph in this run to compensate for
		// AGM fixed-point math.
		this->CalculateFixedToPMRealEmDashWidthRoundingError();

		// If we get this far we've successfully constructed the object.
		fStatus = kCompSuccess;

	} while (false);

}

/* Destructor
*/
SLCTextGlyphNode::~SLCTextGlyphNode()
{
	TRACEFLOW("SLCGlyphNode", "~SLCTextGlyphNode\n");
#if defined(USING_PTRS_FOR_MEMBERS)
	if (fGlyphIDs != nil)
	{
		delete [] fGlyphIDs;
	}
	if (fGlyphWidths != nil)
	{
		delete [] fGlyphWidths;
	}
#endif
	if (fFontInstance != nil)
	{
		fFontInstance->Release();
	}
}

/* GetGlyph
*/
SLComposerStatusCode SLCTextGlyphNode::GetGlyph(const UTF32TextChar& character,
												Text::GlyphID& glyphID,
												PMReal& glyphWidth)
{
	SLComposerStatusCode status = kCompFailure;
	glyphID = kInvalidGlyphID;
	glyphWidth = 0.0;
	do
	{
		// Get  glyph info for the character.
		switch (character.GetValue())
		{
		case kTextChar_CR:
		case kTextChar_SoftCR:
			{
				// End of line, represent as a space.
				status = kCompSuccess;
				glyphID = this->DetermineGlyphID(kTextChar_Space);
				glyphWidth = this->DetermineGlyphWidth(glyphID);
				break;
			}
		case kTextChar_Table:
		case kTextChar_TableContinued:
			{
				// Table, stop composing, the application composes tables.
				// Our responsibility is to compose the text up to but
				// not including this character and return control to the
				// application.
				status = kCompStop;
				break;
			}
		case kTextChar_Tab:
			{
				// Represent tabs as spaces.
				status = kCompSuccess;
				glyphID = this->DetermineGlyphID(kTextChar_Space);
				glyphWidth = this->DetermineGlyphWidth(glyphID);
				break;
			}
		case kTextChar_ObjectReplacementCharacter:
			{
				// This GlyphNode can't handle this character.
				status = kCompIncompatibleCharacter;
				break;
			}
		default:
			{
				// Determine the GlyphID and width of the character.
				status = kCompSuccess;
				glyphID = this->DetermineGlyphID(character);
				glyphWidth = this->DetermineGlyphWidth(glyphID);
				break;
			}
		} // end switch

	} while (false);

	return status;

}

/* BufferGlyph
*/
SLComposerStatusCode SLCTextGlyphNode::BufferGlyph(const UTF32TextChar& character,
												   const Text::GlyphID& glyphID,
												   const PMReal& glyphWidth)
{
	SLComposerStatusCode status = kCompFailure;
	do
	{
		// If the buffers are too small grow them to accommodate more data.
		if (this->GrowBuffers() != kCompSuccess)
		{
			status = kCompOutOfMemory;
			break;
		}

		// Set the return status dependent on the character code.
		switch (character.GetValue())
		{
		case kTextChar_CR:
		case kTextChar_SoftCR:
			{
				// End of line, buffer the glyph.
				status = kCompEndOfLine;
				break;
			}
		case kTextChar_Table:
		case kTextChar_TableContinued:
			{
				// Table, don't buffer it, we don't compose tables, the application does.
				status = kCompStop;
				ASSERT_FAIL("don't buffer kTextChar_Table or kTextChar_TableContinued, the application composes these characters");
				break;
			}
		case kTextChar_ObjectReplacementCharacter:
			{
				// Can't buffer this character, SLCInLineGraphicGlyphNode can.
				status = kCompIncompatibleCharacter;
				break;
			}
		default:
			{
				// Buffer the glyph.
				status = kCompSuccess;
				break;
			}
		} // end switch

		if (status < kCompSuccess)
		{
			// This node can't buffer the glyph info for this character.
			break;
		}

		// Buffer the glyph information that corresponds to the character.
		fGlyphIDs[fTextSpan] = glyphID;
		fGlyphWidths[fTextSpan] = glyphWidth;
		fTextSpan++;

	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode::BufferGlyph() status=%d, character=0x%x, glyphID=0x%x, glyphWidth=%f\n",
			  status,
			  character.GetValue(),
			  glyphID,
			  ::ToDouble(glyphWidth));

	return status;
}

/* GrowBuffers
*/
SLComposerStatusCode SLCTextGlyphNode::GrowBuffers(void)
{
	SLComposerStatusCode status = kCompOutOfMemory;
	do
	{
		// If the buffers are too small grow them.
		if (fTextSpan >= fBufferSize)
		{
			int32 newsize = fBufferSize + kBufSize;
#if defined(USING_PTRS_FOR_MEMBERS)
			PMReal* newWidths = new PMReal[newsize];
			ASSERT(newWidths != nil);
			if (newWidths == nil)
			{
				break;
			}
			Text::GlyphID* newGlyphs = new Text::GlyphID[newsize];
			ASSERT(newGlyphs != nil);
			if (newGlyphs == nil)
			{
				break;
			}

			::memcpy(newGlyphs, fGlyphIDs, sizeof(Text::GlyphID) * fTextSpan);
			delete [] fGlyphIDs;
			fGlyphIDs = newGlyphs;

			::memcpy(newWidths, fGlyphWidths, sizeof(PMReal) * fTextSpan);
			delete [] fGlyphWidths;
			fGlyphWidths = newWidths;
#else
			fGlyphIDs.resize(newsize, kInvalidGlyphID);
			fGlyphWidths.resize(newsize, PMReal(0.0));
#endif

			fBufferSize = newsize;
		}

		// Paranoid check that we have buffers.
#if defined(USING_PTRS_FOR_MEMBERS)
		ASSERT(fGlyphIDs != nil);
		if (fGlyphIDs == nil)
		{
			break;
		}
		ASSERT(fGlyphWidths != nil);
		if (fGlyphWidths == nil)
		{
			break;
		}
#else
		if (fGlyphIDs.capacity() <= 0)
		{
			ASSERT(fGlyphIDs.size() > 0);
			break;
		}
		if (fGlyphWidths.capacity() <= 0)
		{
			ASSERT(fGlyphWidths.size() > 0);
			break;
		}
#endif
		status = kCompSuccess;

	} while (false);

	return status;

}

/* DetermineGlyphID
*/
Text::GlyphID SLCTextGlyphNode::DetermineGlyphID(const UTF32TextChar& character) const
{
	Text::GlyphID result = kInvalidGlyphID;

	if (character.GetValue() == kTextChar_ReplacementCharacter ||
		character.GetValue() == kTextChar_NonRomanSpecialGlyph)
	{
		// The GlyphID for a special character is obtained from the drawing style.
		// Special characters are used to describe glyphs that have no
		// corresponding Unicode character code.
		// Instead the character code kTextChar_ReplacementCharacter or
		// kTextChar_NonRomanSpecialGlyph is inserted in the text flow and a
		// text attribute, kTextAttrSpecialGlyphBoss, is used to map in the
		// correct GlyphID from the font. Special characters have their
		// own unique run/drawing style.
		result = fDrawingStyle->GetSpecialGlyph();
	}
	else
	{
		// The GlyphID for a normal character is obtained from the font instance.
		result = fFontInstance->GetGlyphID(character);
	}

	return result;
}

/* DetermineGlyphWidth
*/
PMReal SLCTextGlyphNode::DetermineGlyphWidth(const Text::GlyphID& glyphID) const
{
	PMReal glyphWidth = 0.0;
	if (glyphID != kInvalidGlyphID)
	{
		// Get the width of the glyph from IFontInstance.
		PMReal agmGlyphWidth = fFontInstance->GetGlyphWidth(glyphID);

		// Convert the fixed-point width to a floating point number.
		glyphWidth = agmGlyphWidth;

		// Calculate the fixed-point to floating-point rounding error adjustment
		// for the glyph width.
		// On construction the rounding error for an em-dash is calculated.
		//(See method CalculateFixedToPMRealEmDashWidthRoundingError()).
		// Here we scale this rounding error in proportion to the width of
		// the glyph relative to the width of an em-dash.
		//
		// This adjustment is not strictly necessary for Roman text measures since
		// the font measures are in points. For more exotic measures such as those
		// used in Japan the rounding error will me significant and must be compensated
		// for.
		PMReal roundingErrorAdjustment = this->GetFixedToPMRealEmDashWidthRoundingError() * (agmGlyphWidth / this->GetEmDashWidth());

		// Apply the rounding error adjustment.
		glyphWidth += roundingErrorAdjustment;
	}

	return glyphWidth;

}

/* CalculateFixedToPMRealEmDashWidthRoundingError
*/
void SLCTextGlyphNode::CalculateFixedToPMRealEmDashWidthRoundingError(void)
{
	// Set the rounding error to zero and the em-dash width to the point size
	// in case the font does not support an em-dash character.
	fFixedToPMRealEmDashWidthRoundingError = 0.0;
	fEmDashWidth = ::ToFixed(this->GetPointSize());

	do
	{
		// Get the GlyphID for the em-dash character.
		Text::GlyphID emDashGlyphID = this->DetermineGlyphID(kTextChar_EmDash);
		if (emDashGlyphID == kInvalidGlyphID)
		{
			break; // No em-dash character in this font.
		}

		// Save off the width of an em-dash as a fixed-point number
		// returned by IFontInstance(AGM). Note that we don't use
		// IDrawingStyle::GetEmDashWidth() because the error introduced
		// by IFontInstance is needed.
		fEmDashWidth = fFontInstance->GetGlyphWidth(emDashGlyphID);

		// Get the scale factor for the text.
		PMReal scaleFactor = fDrawingStyle->GetXScale();

		// Save off the difference between the floating-point point size
		// of the text and the fixed-point width of an em-dash.
		// This gives the rounding error used to calculate
		// an adjustment for the width of each glyph (See DetermineGlyphWidth()).
		fFixedToPMRealEmDashWidthRoundingError = (this->GetPointSize() * scaleFactor) - fEmDashWidth;

		// Fixed-point is fully accurate to the fourth decimal place.
		// If the rounding error is too large to be reasonable limit it.
		const PMReal kMaxRoundingError = 0.0001;
		if (fFixedToPMRealEmDashWidthRoundingError > kMaxRoundingError)
		{
			TRACEFLOW("SLCGlyphNode", "    fFixedToPMRealEmDashWidthRoundingError %f unreasonably large, limiting to 0.0, pointSize %f, scaleFactor %f, fEmDashWidth %f\n",
					  ::ToDouble(fFixedToPMRealEmDashWidthRoundingError),
					  ::ToDouble(this->GetPointSize()),
					  ::ToDouble(scaleFactor),
					  ::ToDouble(fEmDashWidth));
			fFixedToPMRealEmDashWidthRoundingError = 0.0;
		}

	} while (false);

}

/* CreateWax
*/
SLComposerStatusCode SLCTextGlyphNode::CreateWax(const IWaxLine* waxLine) const
{
	SLComposerStatusCode status = kCompFailure;
	do
	{
		// Check we've got composed text to put in the run.
		ASSERT(fTextSpan > 0);
		if (fTextSpan <= 0)
		{
			break;
		}

		// Create wax run.
		InterfacePtr<IWaxRun> waxRun(this->CreateWaxRun());
		if (waxRun == nil)
		{
			break;
		}

		// Add the GlyphIDs and their widths.
		InterfacePtr<IWaxGlyphs>    waxGlyphs(waxRun, IID_IWAXGLYPHS);
		ASSERT(waxGlyphs != nil);
		if (waxGlyphs == nil)
		{
			break;
		}
		for (int32 i = 0; i < this->GetTextSpan(); i++)
		{
			TRACEFLOW("SLCGlyphNodeAddGlyph", "fGlyphIDs [%d]=0x%x, fGlyphWidths [%d]=%f\n",
					  i,
					  fGlyphIDs[i],
					  i,
					  ::ToDouble(fGlyphWidths[i]));
			waxGlyphs->AddGlyph(fGlyphIDs[i], ::ToFloat(fGlyphWidths[i]));
		}

		// Add the wax run to the line
		ASSERT(waxLine != nil);
		if (waxLine == nil)
		{
			break;
		}

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

	return status;

}

/* CreateWaxRun
*/
IWaxRun* SLCTextGlyphNode::CreateWaxRun(void) const
{
	IWaxRun* result = nil;
	do
	{
		// Create the wax run.
		// InDesign 2.0 Note: kWaxRunBoss renamed kWaxTextRunBoss.
		InterfacePtr<IWaxRun> waxRun(static_cast<IWaxRun*>(::CreateObject(kWaxTextRunBoss, IID_IWAXRUN)));
		ASSERT_MSG(waxRun != nil, "create kWaxTextRunBoss failed");
		if (waxRun == nil)
		{
			break;
		}
		waxRun->SetXPosition(fXOffset);
		waxRun->SetYPosition(fDrawingStyle->GetEffectiveBaseline());

		// Ask the drawing style to fill out the render data for the run.
		InterfacePtr<IWaxRenderData> waxRenderData(waxRun, IID_IWAXRENDERDATA);
		ASSERT(waxRenderData != nil);
		if (waxRenderData == nil)
		{
			break;
		}
		fDrawingStyle->FillOutRenderData(waxRenderData, kFalse/*horizontal*/);

		// InDesign 2.0 note: Adornments have to be setup via a new method to account
		// for cases where there is no IWaxRenderData but there are adornments.
		fDrawingStyle->AddAdornments(waxRun);

		result = waxRun;
		result->AddRef();

	} while (false);

	return result;

}

/* FindTextBreak
*/
SLComposerStatusCode SLCTextGlyphNode::FindTextBreak(void)
{
	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode::FindTextBreak()-->In\n");

	SLComposerStatusCode status = kCompFailure;

	do
	{
		// Apply initial rules common to all text break point analysis.
		do
		{
			// Always break if the last character in the GlyphNode is a CR.
			UTF32TextChar breakAfterCharacter;
			if (this->GetCharacter(this->GetTextSpan() - 1, breakAfterCharacter) != kCompSuccess)
			{
				break;
			}
			if (breakAfterCharacter.GetValue() == kTextChar_CR ||
				breakAfterCharacter.GetValue() == kTextChar_SoftCR)
			{
				status = kCompSuccess;
				break;
			}
		} while (false);

		// If a break point in the text has been identified stop.
		if (status == kCompSuccess)
		{
			break;
		}

		// Apply specific text break rules.
		status = this->ApplyTextBreakRules();

	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode::FindTextBreak()-->Out, status = %d\n", status);

	return status;
}

/* ApplyTextBreakRules
*/
SLComposerStatusCode SLCTextGlyphNode::ApplyTextBreakRules(void)
{
	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode::ApplyTextBreakRules()-->In\n");

	SLComposerStatusCode status = kCompFailure;

	do
	{
		// Get the last character in the GlyphNode.
		UTF32TextChar breakAfterCharacter;
		if (this->GetCharacter(this->GetTextSpan() - 1, breakAfterCharacter) != kCompSuccess)
		{
			break;
		}

		// Loop back through the characters in the GlyphNode
		// until a character that can be broken on is found.
		do
		{
			if (breakAfterCharacter.GetValue() == kTextChar_Space ||
				breakAfterCharacter.GetValue() == kTextChar_HyphenMinus ||
				breakAfterCharacter.GetValue() == kTextChar_DiscretionaryHyphen ||
				breakAfterCharacter.GetValue() == kTextChar_UnicodeHyphen)
			{
				status = kCompSuccess;
				break;
			}
			if (this->PushOut(breakAfterCharacter) != kCompSuccess)
			{
				break;
			}
		} while (status == kCompFailure);

		// If a break point in the text has not been identified stop.
		if (status != kCompSuccess)
		{
			break;
		}

	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCTextGlyphNode::ApplyTextBreakRules()-->Out\n");

	return status;
}

/* GetCharacter
*/
SLComposerStatusCode SLCTextGlyphNode::GetCharacter(int32 glyphNodeIndex, UTF32TextChar& character) const
{
	SLComposerStatusCode status = kCompFailure;

	do
	{
		if (glyphNodeIndex < 0 || glyphNodeIndex > this->GetTextSpan() - 1)
		{
			break;
		}

		TextIterator iter = fComposeScanner->QueryDataAt(this->GetTextIndex() + glyphNodeIndex,
														 nil, // Not interested in drawing style
														 nil); // Not interested in length of run
		ASSERT_MSG(iter.IsNull() != kTrue, "no character at this index");
		if (iter.IsNull())
		{
			status = kCompEndOfLine;
			break;
		}
		character = *iter;
		status = kCompSuccess;
	} while (false);

	return status;
}

/* PushOut
*/
SLComposerStatusCode SLCTextGlyphNode::PushOut(UTF32TextChar& lastCharacter)
{
	SLComposerStatusCode status = kCompFailure;
	int32 count = this->GetTextSpan();
	if (count > 0)
	{
		count--;
		this->SetTextSpan(count);
	}
	if (count > 0)
	{
		status = this->GetCharacter(count-1, lastCharacter);
	}
	return status;
}

/* GetWidth
*/
PMReal SLCTextGlyphNode::GetWidth(void) const
{
	// Tot up the widths of all buffered glyphs.
	PMReal result = 0.0;
	for (int32 i = 0; i < this->GetTextSpan(); i++)
	{
		result += fGlyphWidths[i];
	}
	return result;
}

/* GetTrailingWhiteSpaceWidth
*/
bool16 SLCTextGlyphNode::GetTrailingWhiteSpaceWidth(PMReal& width) const
{
	bool16 result = kTrue;
	Text::GlyphID spaceGlyphID = this->DetermineGlyphID(kTextChar_Space);
	for (int32 i = this->GetTextSpan()-1; i >= 0; i--)
	{
		if (fGlyphIDs[i] != spaceGlyphID)
		{
			// Stop counting on first non white space encountered.
			result = kFalse;
			break;
		}
		width += fGlyphWidths[i];
	}
	return result;
}

/* FitTrailingWhiteSpace
*/
bool16 SLCTextGlyphNode::FitTrailingWhiteSpace(const PMReal& widthScaleFactor)
{
	bool16 result = kTrue;
	do
	{
		// Validate the scale factor.
		ASSERT(widthScaleFactor > PMReal(0.0) && widthScaleFactor < PMReal(1.0));
		if (widthScaleFactor <= PMReal(0.0) || widthScaleFactor >= PMReal(1.0))
		{
			result = kFalse;
			break;
		}

		// Scale the width of any trailing white space by the given factor.
		Text::GlyphID spaceGlyphID = this->DetermineGlyphID(kTextChar_Space);
		for (int32 i = this->GetTextSpan()-1; i >= 0; i--)
		{
			if (fGlyphIDs[i] != spaceGlyphID)
			{
				result = kFalse;
				break;
			}
			fGlyphWidths[i] *= widthScaleFactor;
		}
	} while (false);
	return result;
}

// End SLCTextGlyphNode.cpp.

