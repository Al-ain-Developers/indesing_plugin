//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTileComposer.cpp $
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

// Interface includes:
#include "IComposeScanner.h"
#include "IDrawingStyle.h"

// General includes:
#include "textiterator.h"

// Project includes:
#include "SLC.h"
#include "SLCTileMeasure.h"
#include "SLCGlyphNode.h"
#include "SLCGlyphNodeList.h"
#include "SLCTileComposer.h"


/* FlowTextByTileWidth
*/  
SLComposerStatusCode SLCTileComposer::FlowTextByTileWidth(const SLCTileMeasure& tile, SLCGlyphNodeList & glyphNodeList)
{
	TRACEFLOW("SLCTileComposer", "SLCTileComposer::FlowTextByTileWidth()->In fTextIndex=%d, tile.fXPosition=%f, tile.fWidth=%f\n",
			  fTextIndex,
			  ::ToDouble(tile.fXPosition), 
			  ::ToDouble(tile.fWidth));

	SLComposerStatusCode status = kCompFailure;

	// Reference to the drawing style for the next run of text to be composed.
	IDrawingStyle* nextDrawingStyle = nil;

	// Left edge of the tile relative to the line.
	PMReal tileLeftEdgeOffset = tile.fXPosition - fXPosition;   

	// Metrics accumulated during composition.
	fTextSpan = 0;
	fTextWidth = 0.0;
	fFitTextSpan = 0;
	fFitTextWidth = 0.0;

	// Pointer to GlyphNode for the current run.
	SLCGlyphNode* glyphNode = nil;

	// If the character that causes the tile width to be exceeded
	// is white space this flag will be kTrue when the loop below exits.
	bool16 trailingWhiteSpace = kFalse;

	// Compose to tile width outer loop:
	// Loop round creating a GlyphNode for each run
	// encountered until the width of the glyphs is 
	// more than the width of the tile.
	status = kCompSuccess;
	bool16 tileWidthReached = kFalse;
	while (tileWidthReached == kFalse)
	{
		if (status == kCompSuccess || status == kCompIncompatibleCharacter)
		{
			// Continue composing.
		}
		else
		{
			// End of line or an error, stop composing.
			break;
		}

		// Get the next run.
		nextDrawingStyle = nil;
		int32 length = 0;
		TextIterator iter = fComposeScanner->QueryDataAt(fTextIndex + fTextSpan, 
														 &nextDrawingStyle, 
														 &length);
		if (iter.IsNull())
		{
			// No more characters.
			status = kCompEndOfLine;
			break;
		}
		ASSERT(nextDrawingStyle != nil);
		if (nextDrawingStyle == nil)
		{
			status = kCompFailure;
			break;
		}

		if (glyphNode == nil)
		{
			// This is the start of the first run in this tile.	
			glyphNode = glyphNodeList.CreateGlyphNode(fComposeScanner,
													   nextDrawingStyle,
													   fTextIndex,
													   tileLeftEdgeOffset);
			if (glyphNode == nil)
			{
				break;  
			}
		}

		// If the drawing style has changed or the next character to
		// be composed is not compatible with the current glyph node
		// (happens when an inline graphic is added to a TextGlyphNode and vice versa)
		// we need to start a new run.
		if (nextDrawingStyle != glyphNode->GetDrawingStyle() ||
			status == kCompIncompatibleCharacter)
		{
			// Prepare for next run.	
			glyphNode = glyphNodeList.CreateGlyphNode(fComposeScanner,
													   nextDrawingStyle,
													   fTextIndex + fTextSpan,
													   tileLeftEdgeOffset + fTextWidth);
			if (glyphNode == nil)
			{
				break;
			}
		}

		// We have a glyph node for the nextDrawingStyle so release this reference.
		nextDrawingStyle->Release();
		nextDrawingStyle = nil; 

		// Compose to tile width inner loop:
		// Loop round buffering glyphs until the 
		// current run is exhausted, the tile is overset,
		// or we reach the end of line or detect an error.
		int32 index = 0;
		status = kCompSuccess;
		while (index < length && status == kCompSuccess)
		{
			// Get the next character.
			UTF32TextChar character(iter[index++]);

			// Get the ID and width of the glyph that corresponds to this character.	
			Text::GlyphID glyphID = kInvalidGlyphID;
			PMReal glyphWidth = 0.0;
			status = glyphNode->GetGlyph(character, glyphID, glyphWidth);
			if (status != kCompSuccess)
			{
				break;
			}

			// If tile doesn't have room for this character exit the outer loop.
			if (fTextWidth + glyphWidth >= tile.fWidth)
			{
				tileWidthReached = kTrue;
				if (glyphNode->IsTrailingWhiteSpace(character) == kTrue)
				{
					// There's trailing white space we need to add so
					// we don't break text before it. Set a flag to
					// indicate this must be done.
					trailingWhiteSpace = kTrue;
				}
				break;
			}

			// Buffer glyph information for this character.	
			status = glyphNode->BufferGlyph(character, glyphID, glyphWidth);
			if (status < kCompSuccess)
			{
				break;
			}

			// Maintain accumulated metrics.
			fTextSpan++;
			fTextWidth += glyphWidth;

		} // end while compose to tile width inner loop:

		TRACEFLOW("SLCTileComposer", "compose to tile width iteration: status %d, fTextIndex %d, fTextSpan %d, fTextWidth %f, tile.fWidth %f, drawingStyle 0x%x, length %d\n", 
				  status,
				  fTextIndex, 
				  fTextSpan,
				  ::ToDouble(fTextWidth),
				  ::ToDouble(tile.fWidth),
				  glyphNode->GetDrawingStyle(),
				  length);            

	} // end compose to tile width outer loop:

	// Make a note of metrics for the characters that fit in the tile.
	fFitTextSpan = fTextSpan;
	fFitTextWidth = fTextWidth;

	// Stuff trailing white space outer loop:
	// This loop is entered if we haven't got an end of line in
	// the tile. It scans forward and stuffs trailing white space characters that
	// we shouldn't break before into the tile. The width of these characters
	// will need to be adjusted to fit the tile at a later stage.
	while (trailingWhiteSpace == kTrue)
	{
		if (status == kCompSuccess || status == kCompIncompatibleCharacter)
		{
			// Continue composing.
		}
		else
		{
			// End of line or an error, stop composing.
			break;
		}

		// Get the next run.
		nextDrawingStyle = nil;
		int32 length = 0;
		TextIterator iter = fComposeScanner->QueryDataAt(fTextIndex + fTextSpan,
														 &nextDrawingStyle, 
														 &length);
		if (iter.IsNull())
		{
			// No more characters.
			status = kCompEndOfLine;
			break;
		}
		ASSERT(nextDrawingStyle != nil);
		if (nextDrawingStyle == nil)
		{
			status = kCompFailure;
			break;
		}
		ASSERT(glyphNode != nil);

		// If the drawing style has changed or the next character to
		// be composed is not compatible with the current GlyphNode
		// we need to start a new run.
		if (nextDrawingStyle != glyphNode->GetDrawingStyle() ||
			status == kCompIncompatibleCharacter)
		{
			// Prepare for next run.	
			glyphNode = glyphNodeList.CreateGlyphNode(fComposeScanner,
													   nextDrawingStyle,
													   fTextIndex + fTextSpan,
													   tileLeftEdgeOffset + fTextWidth);
			if (glyphNode == nil)
			{
				break;
			}
		}

		// We have a GlyphNode for the nextDrawingStyle so release this reference.
		nextDrawingStyle->Release();
		nextDrawingStyle = nil; 

		// Stuff trailing white space inner loop:		
		int32 index = 0;
		status = kCompSuccess;
		while (index < length &&status == kCompSuccess)
		{
			// Get the next character.
			UTF32TextChar character(iter[index++]);

			// If the character is not trailing white space quit the outer loop.
			if (glyphNode->IsTrailingWhiteSpace(character) == kFalse)
			{
				trailingWhiteSpace = kFalse;
				break;
			}

			// Buffer glyph information for this white space character.			
			PMReal glyphWidth = 0.0;
			Text::GlyphID glyphID = kInvalidGlyphID;
			status = glyphNode->GetGlyph(character, glyphID, glyphWidth);
			if (status != kCompSuccess)
			{
				break;
			}
			status = glyphNode->BufferGlyph(character, glyphID, glyphWidth);
			if (status < kCompSuccess)
			{
				break;
			}

			// Maintain accumulated metrics.
			fTextSpan++;
			fTextWidth += glyphWidth;

		} // end while stuff trailing white space inner loop:	

		TRACEFLOW("SLCTileComposer", "stuff trailing white space iteration: status %d, fTextIndex %d, fTextSpan %d, fTextWidth %f, drawingStyle 0x%x, length %d,\n", 
				  status,
				  fTextIndex, 
				  fTextSpan,
				  ::ToDouble(fTextWidth),
				  glyphNode->GetDrawingStyle(),
				  length);    

	} // end while stuff trailing white space outer loop:
	if (status == kCompIncompatibleCharacter)
	{
		status = kCompSuccess;
	}

	// Release the references we're holding.
	if (nextDrawingStyle != nil)
	{
		nextDrawingStyle->Release();
	}

	TRACEFLOW("SLCTileComposer", "SLCTileComposer::FlowTextByTileWidth()->Out status=%d, fTextSpan=%d, fTextWidth=%f, fFitTextSpan=%d, fFitTextWidth=%f\n", 
			  status,
			  fTextSpan,
			  ::ToDouble(fTextWidth),
			  fFitTextSpan,
			  ::ToDouble(fFitTextWidth));

	return status;

}

/* FlowTextByTileTextSpan
*/
SLComposerStatusCode SLCTileComposer::FlowTextByTileTextSpan(const SLCTileMeasure& tile, SLCGlyphNodeList & glyphNodeList)
{
	TRACEFLOW("SLCTileComposer", "SLCTileComposer::FlowTextByTileTextSpan()->In fTextIndex=%d, tile.fXPosition=%f, tile.fWidth=%f, tile.fTextSpan=%d\n",
			  fTextIndex,
			  ::ToDouble(tile.fXPosition), 
			  ::ToDouble(tile.fWidth),
			  tile.fTextSpan);

	// Reference to the drawing style for the next run of text to be composed.
	IDrawingStyle* nextDrawingStyle = nil;

	// Left edge of the tile relative to the line.
	PMReal tileLeftEdgeOffset = tile.fXPosition - fXPosition;   

	// Metrics accumulated during composition.
	fTextSpan = 0;
	fTextWidth = 0.0;
	fFitTextSpan = 0;
	fFitTextWidth = 0.0;

	// Pointer to GlyphNode for the current run.
	SLCGlyphNode* glyphNode = nil;

	// Compose range of text outer loop:
	// Loop round creating a GlyphNode for each run
	// encountered until the range of characters fTextIndex:fTextIndex+tile.fTextSpan
	// has been flowed into the tile.
	SLComposerStatusCode status = kCompSuccess;
	while (fTextSpan < tile.fTextSpan)
	{
		if (status == kCompSuccess || status == kCompIncompatibleCharacter)
		{
			// Continue composing.
		}
		else
		{
			// End of line or an error, stop composing.
			break;
		}

		// Get the next run.
		nextDrawingStyle = nil;
		int32 length = 0;
		TextIterator iter = fComposeScanner->QueryDataAt(fTextIndex + fTextSpan, 
														 &nextDrawingStyle, 
														 &length);
		if (iter.IsNull())
		{
			// No more characters.
			status = kCompEndOfLine;
			break;
		}
		ASSERT(nextDrawingStyle != nil);
		if (nextDrawingStyle == nil)
		{
			status = kCompFailure;
			break;
		}

		if (glyphNode == nil)
		{
			// This is the start of the first run in this tile.	
			glyphNode = glyphNodeList.CreateGlyphNode(fComposeScanner,
													   nextDrawingStyle,
													   fTextIndex,
													   tileLeftEdgeOffset);
			if (glyphNode == nil)
			{
				break;  
			}
		}

		// If the drawing style has changed or the next character to
		// be composed is not compatible with the current GlyphNodeType
		// we need to start a new run.
		if (nextDrawingStyle != glyphNode->GetDrawingStyle() ||
			status == kCompIncompatibleCharacter)
		{
			// Prepare for next run.	
			glyphNode = glyphNodeList.CreateGlyphNode(fComposeScanner,
													   nextDrawingStyle,
													   fTextIndex + fTextSpan,
													   tileLeftEdgeOffset + fTextWidth);
			if (glyphNode == nil)
			{
				break;
			}
		}

		// We have a glyph node for the nextDrawingStyle so release this reference.
		nextDrawingStyle->Release();
		nextDrawingStyle = nil; 

		// Compose range of text inner loop:
		// Loop round buffering glyphs.
		int32       index = 0;
		status = kCompSuccess;
		while (index < length &&
			   fTextSpan < tile.fTextSpan &&
			   status >= kCompSuccess)
		{
			// Get the next character.
			UTF32TextChar character(iter[index++]);

			// Get the ID and width of the glyph that corresponds to this character.	
			Text::GlyphID glyphID = kInvalidGlyphID;
			PMReal glyphWidth = 0.0;
			status = glyphNode->GetGlyph(character, glyphID, glyphWidth);
			if (status != kCompSuccess)
			{
				break;
			}

			// Buffer glyph information for this character.	
			status = glyphNode->BufferGlyph(character, glyphID, glyphWidth);
			if (status < kCompSuccess)
			{
				break;
			}

			// Maintain accumulated width and character counts.
			fTextSpan++;
			fTextWidth += glyphWidth;
			if (fTextWidth <= tile.fWidth)
			{
				fFitTextWidth = fTextWidth;
				fFitTextSpan = fTextSpan;
			}

		} // end while compose range of text inner loop:

	} // end while compose range of text outer loop:

	// Release the references we're holding.
	if (nextDrawingStyle != nil)
	{
		nextDrawingStyle->Release();
	}

	TRACEFLOW("SLCTileComposer", "SLCTileComposer::FlowTextByTileTextSpan()->Out status=%d, fTextSpan=%d, fTextWidth=%f, fFitTextSpan=%d, fFitTextWidth=%f\n", 
			  status,
			  fTextSpan,
			  ::ToDouble(fTextWidth),
			  fFitTextSpan,
			  ::ToDouble(fFitTextWidth));

	return status;
}

// End, SLCTileComposer.cpp.

