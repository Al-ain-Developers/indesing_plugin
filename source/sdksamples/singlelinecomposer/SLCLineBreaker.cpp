//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCLineBreaker.cpp $
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
#include "ICompositionStyle.h"
#include "IDrawingStyle.h"
#include "ITextParcelList.h"
#include "IGridRelatedStyle.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IWaxStrand.h"

// General includes:

// Project includes:
#include "SLC.h"
#include "SLCTileMeasure.h"
#include "SLCGlyphNode.h"
#include "SLCLineMetrics.h"
#include "SLCGlyphNodeList.h"
#include "SLCDiagnostics.h"
#include "SLCTileManager.h"
#include "SLCTileComposer.h"
#include "SLCLineBreaker.h"


/* Recompose
*/
bool16 SLCLineBreaker::Recompose(IParagraphComposer::RecomposeHelper* helper)
{
	IComposeScanner* composeScanner = helper->GetComposeScanner();
	TextIndex startingIndex = helper->GetStartingTextIndex();
	ParcelKey parcelKey = helper->GetStartingParcelKey();
	PMReal yPosition = helper->GetStartingYPosition();
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::Recompose()-->In startingIndex=%d, yPosition=%f\n", 
			startingIndex,
			::ToDouble(yPosition));
	bool16 lineComposed = kFalse;
	SLComposerStatusCode status = kCompFailure;
	do
	{
		// Validate arguments.
		ASSERT(helper != nil);
		if (helper == nil)
		{
			break;
		}
		TextIterator iter = composeScanner->QueryDataAt(startingIndex, nil, nil);
		ASSERT_MSG(iter.IsNull() != kTrue, "no characters to compose");
		ASSERT_MSG((*iter).GetValue() != kTextChar_Table && 
				   (*iter).GetValue() != kTextChar_TableContinued,
				   "Can't compose table character, the application is supposed to do that");
		if ((*iter).GetValue() == kTextChar_Table || 
			(*iter).GetValue() == kTextChar_TableContinued)
		{
			break;
		}
        
		// Prepare to compose the line.
		ASSERT_MSG(fComposeScanner == nil, "SLCLineBreaker::Recompose fComposeScanner should be nil on entry");
		fComposeScanner = composeScanner;
		fComposeScanner->AddRef();
		fTextIndex = startingIndex;
		fYPosition = yPosition;
		status = this->Initialise(helper, parcelKey);
		if (status != kCompSuccess)
		{
			break;
		}

		// Compose the line.
		// This will do an AddRef, but RecomposeHelper will own the IWaxLine*, so we don't need to manage ref counts. 
        IWaxLine* waxLine = this->ComposeLine(startingIndex);

		// Clear up.
		this->Finish();

		// Check a wax line containing text has been created.
		if (waxLine == nil)
		{
			break;
		}
		int32 textSpan = fTextIndex - startingIndex;
		ASSERT_MSG(textSpan > 0, "No characters composed");
		if (textSpan <= 0)
		{
			break;
		}

		// Add the line to the wax strand.
		// changed in InDesign CS: done via helper
		// OLD CODE: waxStrand->ApplyComposedLine(startingIndex, waxLine, textSpan);
		if (startingIndex != helper->GetStartingTextIndex())
		{
			ASSERT_MSG(startingIndex == helper->GetStartingTextIndex(), "The starting index must be the same has what the helper says");
			break;
		}
		helper->ApplyComposedLine(waxLine, textSpan);

		lineComposed = kTrue;

	} while (false);

	// Clean up.
	if (fComposeScanner != nil)
	{
		fComposeScanner->Release();
		fComposeScanner = nil;
	}

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::Recompose()-->Out lineComposed=%d\n", lineComposed); 

	return lineComposed; // kTrue if line was composed.
}

/* Initialise
*/
SLComposerStatusCode SLCLineBreaker::Initialise(const IParagraphComposer::RecomposeHelper* helper, ParcelKey parcelKey)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::Initialise()-->In\n");
	SLComposerStatusCode status = kCompFailure;

	fGlyphNodeList.Clear();

	do
	{
		// Acquire the complete style at the index in the text model where
		// we start composing.
		IDrawingStyle* drawingStyle = helper->GetComposeScanner()->GetCompleteStyleAt(fTextIndex);
		ASSERT(drawingStyle != nil);
		if (drawingStyle == nil)
		{
			break;
		}

		// Determine whether this is the first line in the paragraph.
		fFirstLine = (fTextIndex == helper->GetParagraphStart());

		// Get the paragraph indent settings & calculate left indent.		
		InterfacePtr<ICompositionStyle> compositionStyle(drawingStyle, IID_ICOMPOSITIONSTYLE);
		ASSERT(compositionStyle != nil);
		if (compositionStyle == nil)
		{
			break;
		}
		Text::FirstLineOffsetMetric flo = (parcelKey.IsValid() ? helper->GetTextParcelList()->GetFirstLineOffsetMetric(parcelKey) : Text::kFLOLeading);
		PMReal indentLeft = compositionStyle->IndentLeftBody();
		PMReal indentRight = compositionStyle->IndentRightBody();
		if (fFirstLine == kTrue)
		{
			// Add the first line in paragraph left indent.
			indentLeft += compositionStyle->IndentLeftFirst();
		}

		// Prepare the tile manager to get tiles for this line.
		fSLCTileManager.Initialise(helper, parcelKey, flo, indentLeft, indentRight);

		// Create a GlyphNode for the first character to be composed
		// the line & use it to initialise the line metrics.
		SLCGlyphNode* glyphNode = fGlyphNodeList.CreateGlyphNode(fComposeScanner, drawingStyle, fTextIndex, indentLeft);
		ASSERT(glyphNode != nil);
		if (glyphNode == nil)
		{
			break;
		}
		ASSERT(glyphNode->GetStatus() == kCompSuccess);
		if (glyphNode->GetStatus() != kCompSuccess)
		{
			break;
		}
		fLineMetrics.SetLeading(glyphNode->GetLeading());
		fLineMetrics.SetAscent(glyphNode->GetAscent());
		fLineMetrics.SetCapHeight(glyphNode->GetCapHeight());
		fLineMetrics.SetXHeight(glyphNode->GetXHeight());
		fLineMetrics.Dump("SLCLineBreaker", "initial fLineMetrics: ");

		// Get grid alignment to be applied.
		fGridAlignmentMetric = this->GetGridAlignmentMetric(drawingStyle);

		status = kCompSuccess;

	} while (false);

	fGlyphNodeList.Clear();

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::Initialise()-->Out status=%d\n", status);

	return status;

}

/* FInish
*/
void SLCLineBreaker::Finish()
{
	fSLCTileManager.Finish();
}

/* ComposeLine
*/
IWaxLine* SLCLineBreaker::ComposeLine(const TextIndex& startingIndex)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::ComposeLine()-->In startingIndex=%d\n", 
			  startingIndex);
	IWaxLine* result = nil;
	SLComposerStatusCode status = kCompFailure;

	// Take a copy of the initial metrics used to compose the line
	// so that if we have to recompose the line for any reason
	// we can reset the line metrics to those we started with.
	SLCLineMetrics initialLineMetrics = fLineMetrics;

	do
	{
		// Get the tiles into which text is to be composed.
		if (this->GetTiles() != kCompSuccess)
		{
			break;
		}

		// If the line is being re-composed...
		if (status == kCompChangeOfHeight || status == kCompWillNotFit)
		{
			// ...restore the line metrics to their initial values.
			fLineMetrics = initialLineMetrics;
			fLineMetrics.Dump("SLCLineBreaker", "fLineMetrics reset to initial values: ");
		}

		// Compose the line.
		status = this->FillLine();
		if (status >= kCompSuccess)
		{
			// The line is composed.
			break;
		}
		else if (status == kCompChangeOfHeight || status == kCompWillNotFit)
		{
			// Recompose.
		}
		else
		{
			// Stop, some error we can't handle has happened.
			break;
		}

		// Recompose. 
		// If the line needs deeper tiles fLineMetrics will have the metrics required
		// to be passed to the tiler.
		fTextIndex = startingIndex;

		// If no characters will fit in the current tiles try the next line down.
		// Perhaps tiles can be found there in which the text will fit.
		if (status == kCompWillNotFit)
		{
			// This prevents the composer from potentially going into an infinite loop in
			// the following condition. The tiles we have are deep enough to take the text
			// (the status would be kCompChangeOfHeight otherwise) line breaking is telling
			// us that no word will fit in these tiles. We could either ask for deeper tiles
			// at the current y position or change the y position to the next line and ask for
			// tiles of the same depth. We do the latter.
			fYPosition = fSLCTileManager.GetTileBottom();
		}

	} while (status == kCompChangeOfHeight || status == kCompWillNotFit);

	// Generate wax for the composed line.
	if (status >= kCompSuccess)
	{
		result = this->CreateWaxLine();
	}

	fGlyphNodeList.Clear();

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::ComposeLine()-->Out result=0x%x\n", result);

	return result;

}

/* GetTiles
*/
SLComposerStatusCode SLCLineBreaker::GetTiles(void)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::GetTiles()-->In fYPosition=%f\n", 
			  ::ToDouble(fYPosition));

	SLComposerStatusCode status = kCompFailure;

	do
	{
		// Ask the tile manager to prepare tile measures for this line.
		status = fSLCTileManager.MakeTileMeasures(fYPosition, 
												  fLineMetrics, 
												  fGridAlignmentMetric, 
												  kSLCGridAlignmentMetricOffset, 
												  fTextIndex);
		if (status != kCompSuccess)
		{
			break;
		}

		// Maintain the position the top of the area into which text is flowed.
		fYPosition = fSLCTileManager.GetTileTop();

		// Maintain the left edge of the line as the left edge of the 
		// first tile measure.
		fXPosition = fSLCTileManager.GetTileMeasures()[0].fXPosition;

	} while (false);

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::GetTiles()-->Out status=%d\n", status);

	return status;

}

/* FillLine
*/
SLComposerStatusCode SLCLineBreaker::FillLine(void)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FillLine()-->In fXPosition() %f, fYPosition %f\n", ::ToDouble(fXPosition), ::ToDouble(fYPosition));

	// Fill each tile on the line with text.
	SLComposerStatusCode status = kCompFailure;
	fGlyphNodeList.Clear();
	int32 startingIndex = fTextIndex;
	SLCTileMeasures::iterator iter;
	SLCTileMeasures& tileMeasures = fSLCTileManager.GetTileMeasures();
	for (iter = tileMeasures.begin(); iter < tileMeasures.end(); iter++)
	{
		status = this->FillTile(*iter);
		if (status != kCompSuccess)
		{
			break;
		}
	}   

	if (fTextIndex - startingIndex <= 0 && status >= kCompSuccess)
	{
		// We couldn't fit any words in these tiles.
		status = kCompWillNotFit;
	}

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FillLine()-->Out status=%d\n", status);    

	return status;

}

/* FillTile
*/  
SLComposerStatusCode SLCLineBreaker::FillTile(SLCTileMeasure& tile)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FillTile()->In fTextIndex=%d, tile.fXPosition=%f, tile.fWidth=%f\n",
			  fTextIndex,
			  ::ToDouble(tile.fXPosition), 
			  ::ToDouble(tile.fWidth));

	SLComposerStatusCode status = kCompFailure;
	do
	{
		// Prepare to compose text for the tile.
		TextIndex startingIndex = fTextIndex;
		int32 fromGlyphNodeIndex = fGlyphNodeList.Length();
		tile.fTextSpan = 0;

		// Flow the text into the tile.
		SLCTileComposer tileComposer(fComposeScanner, fXPosition, fTextIndex);
		status = tileComposer.FlowTextByTileWidth(tile, fGlyphNodeList);
		if (status < kCompSuccess)
		{
			break;
		}

		// Check out the composed text for line break, tracked line metrics etc.
		SLComposerStatusCode tmpStatus = this->ProcessGlyphNodes(fromGlyphNodeIndex);
		if (tmpStatus < kCompSuccess)
		{
			status = tmpStatus;
			break;
		}

		// Save the number of characters in this tile.
		tile.fTextSpan = fTextIndex - startingIndex;

	} while (false);

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FillTile()->Out status=%d, fTextIndex=%d, tile.fXPosition=%f, tile.fWidth=%f, tile.fTextSpan=%d\n", 
			  status,
			  fTextIndex,
			  ::ToDouble(tile.fXPosition),
			  ::ToDouble(tile.fWidth),
			  tile.fTextSpan
			 );

	return status;

}

/* ProcessGlyphNodes
*/
SLComposerStatusCode SLCLineBreaker::ProcessGlyphNodes(int32 fromGlyphNodeIndex)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::ProcessGlyphNodes()-->In, fromGlyphNodeIndex=%d, IsStoryOverset()=%d\n", 
			  fromGlyphNodeIndex, 
			  IsStoryOverset());

	SLComposerStatusCode status = kCompFailure; 
	SLCGlyphNode* glyphNode = nil;

	do
	{
		// Check for GlyphNodes.
		if (fGlyphNodeList.Length() <= fromGlyphNodeIndex)
		{
			// There's nothing to do.
			break; 
		}
		fGlyphNodeList.Dump(fromGlyphNodeIndex, "SLCLineBreaker::ProcessGlyphNodes nodes");

		// Process the new glyph nodes.
		if (this->IsStoryOverset() == kFalse)
		{

			// The story is not overset identify where the text can be broken.
			this->FindTextBreak(fromGlyphNodeIndex);

			// Iterate over each new glyph node and check the tiles 
			// used were deep enough. Touch each new node to find the
			// tallest rather than breaking out as soon as it is clear that
			// the tiles were not deep enough.
			fLineMetrics.Dump("SLCLineBreaker", "fLineMetrics before line height update:\n");
			int32 i;
			for (i = fromGlyphNodeIndex; i < fGlyphNodeList.Length(); i++)
			{
				this->UpdateLineHeight(fGlyphNodeList [i]);
				if (fLineMetrics.GetValue(kSLCLineHeightMetric) > fSLCTileManager.GetHeight())
				{
					// The height of text on the line is greater than the height of the tiles.
					// We need to get new deeper tiles and recompose.
					status = kCompChangeOfHeight;
				}
			} // end for
			fLineMetrics.Dump("SLCLineBreaker", "fLineMetrics after line height update:\n");

			// A line that falls at the top of frame is a special case. Say you had
			// 10 point text set in a frame with a first baseline offset set to leading.
			// Say one of the characters has 20 point leading. The rule below catches this.
			// If the top of frame line height exceeds the height used to size the tile 
			// a height change is flagged to force recomposition with new tiles.
			if (status != kCompChangeOfHeight && fSLCTileManager.GetAtTOP() == kTrue)
			{
				if (fLineMetrics.GetValue(fSLCTileManager.GetTOPHeightMetric()) > fSLCTileManager.GetTOPHeight())
				{
					status = kCompChangeOfHeight;
				}
			}

			// If a height change has been detected the line must be recomposed
			// with deeper tiles. The tracked line metrics contain the height
			// of tile needed to compose this text.
			// All of the glyph nodes that have been built will be thrown away.	
			if (status == kCompChangeOfHeight)
			{
				break;
			}
		}

		// If we get to here a count of the characters that have been
		// composed in the new glyph nodes is made and used to update the
		// index into the text model of the next character to be composed.
		int32 textSpan = fGlyphNodeList.GetTextSpan(fromGlyphNodeIndex);
		fTextIndex += textSpan;
		status = kCompSuccess;

	} while (false);

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::ProcessGlyphNodes()-->Out, status=%d\n", status);

	return status;

}

/* FindTextBreak
*/
SLComposerStatusCode SLCLineBreaker::FindTextBreak(int32 fromGlyphNodeIndex)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FindTextBreak()-->In, fromGlyphNodeIndex=%d, IsStoryOverset()=%d\n", 
			  fromGlyphNodeIndex, 
			  IsStoryOverset());

	SLComposerStatusCode status = kCompFailure; 
	SLCGlyphNode* glyphNode = nil;

	// Searching backwards from last to first look for a glyph node
	// that contains a point where text can be broken.
	int32 textBreakRunIndex = fGlyphNodeList.Length();
	while (textBreakRunIndex > fromGlyphNodeIndex)
	{
		textBreakRunIndex--;
		glyphNode = fGlyphNodeList [textBreakRunIndex];

		// If a break point in the text is found exit the loop.
		status = glyphNode->FindTextBreak();
		if (status == kCompSuccess)
		{
			break;
		}

		// Remove the node if a break point can't be found.
		// The text in it can't be included in this line.
		fGlyphNodeList.Remove(textBreakRunIndex);
		delete glyphNode;

	} // end while

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::FindTextBreak()-->Out, status=%d\n", status);

	return status;

}

/* CreateWaxLine
*/
IWaxLine* SLCLineBreaker::CreateWaxLine(void)
{
	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::CreateWaxLine()-->In fXPosition=%f, fYPosition=%f\n",
			  ::ToDouble(fXPosition),
			  ::ToDouble(fYPosition));
	IWaxLine* waxLine = nil;
	do
	{
		// Create a wax line to hold the composed text.
		// NOTE: similar to IParagraphComposer::RecomposeHelper::QueryNewWaxLine
		// TODO: IParagraphComposer::RecomposeHelper::QueryNewWaxLine should be
		// used instead of creating the wax line directly.
		waxLine = ::CreateObject2<IWaxLine>(kWaxLineBoss);
		ASSERT_MSG(waxLine != nil, "create kWaxLineBoss failed");
		if (waxLine == nil)
		{
			break;
		}

		// Set the number of tiles on the line and
		// the x position, width and number
		// of characters in each tile.
		const SLCTileMeasures& tileMeasures = fSLCTileManager.GetTileMeasures();
		int32   numberOfTiles = tileMeasures.size();
		waxLine->SetNumberOfTiles(numberOfTiles);
		for (int32 i = 0; i < numberOfTiles; i++)
		{
			waxLine->SetTextSpanInTile(tileMeasures[i].fTextSpan, i); 
			waxLine->SetXPosition(tileMeasures[i].fXPosition, i);
			waxLine->SetTargetWidth(tileMeasures[i].fWidth, i);
		}
		if (numberOfTiles > 1)
		{
			// Line has intrusions & should not be shuffled.
			waxLine->SetNoShuffle(kTrue);
		}

		// Set the y position, the baseline for text on the line.
		// SetYPosition now a method on IWaxRun
		fYPosition = fSLCTileManager.GetTileBottom();
		waxLine->SetCompositionYPosition(fYPosition);

		// Set the height of the line and the height of the line when
		// it falls at the top of a parcel.
		waxLine->SetLineHeight(fLineMetrics.GetValue(kSLCLineHeightMetric));
		waxLine->SetTOFLineHeight(fLineMetrics.GetValue(fSLCTileManager.GetTOPHeightMetric()), fSLCTileManager.GetTOPHeightMetric());
		waxLine->SetLeadingModel(kSLCLeadingModel);

		// Set other wax properties.
		waxLine->SetGridAlignment(fGridAlignmentMetric, kSLCGridAlignmentMetricOffset);
		waxLine->SetParcelKey(fSLCTileManager.GetParcelKey());
		waxLine->SetAtTOF(fSLCTileManager.GetAtTOP());
		waxLine->SetParcelPositionDependent(fSLCTileManager.GetParcelPositionDependent());

	} while (false);

	TRACEFLOW("SLCLineBreaker", "SLCLineBreaker::CreateWaxLine()-->Out result=0x%x\n", waxLine);

	return waxLine;

}

/* GetGridAlignmentMetric
*/
Text::GridAlignmentMetric SLCLineBreaker::GetGridAlignmentMetric(IDrawingStyle* drawingStyle)
{
	Text::GridAlignmentMetric result = Text::kGANone;

	do
	{
		Text::GridAlignmentMetric gridAlignmentMetric = result;
		InterfacePtr<IGridRelatedStyle> gridRelatedStyle(drawingStyle, UseDefaultIID());
		if (gridRelatedStyle == nil)
		{
			break;
		}

		if (gridRelatedStyle->GetAlignOnlyFirstLine() == kFalse)
		{
			// Peg the line to the grid.
			gridAlignmentMetric = gridRelatedStyle->GetGridAlignmentMetric();
		}
		else if (fFirstLine == kTrue)
		{
			// Only peg the line to the grid if it is the first line in a paragraph.
			// The Roman feature set does not expose the paragraph attribute
			// that controls this setting so it will always be kFalse unless
			// you write code to set this attribute.
			gridAlignmentMetric = gridRelatedStyle->GetGridAlignmentMetric();
		}

		ASSERT_MSG(gridAlignmentMetric <= Text::kGABaseline, "unsupported gridAlignmentMetric, defaulting to none");
		if (gridAlignmentMetric <= Text::kGABaseline)
		{
			result = gridAlignmentMetric;
		}
	} while (false);

	return result;

}

/* IsStoryOverset
*/
bool16 SLCLineBreaker::IsStoryOverset() const 
{
	return fSLCTileManager.IsStoryOverset(); 
}

/* UpdateLineHeight
*/
void SLCLineBreaker::UpdateLineHeight(const SLCGlyphNode* glyphNode)
{
	// If the metric value for this node is greater than the tracked 
	// maximum for the line update the tracked maximum accordingly.
	if (glyphNode->GetLeading() > fLineMetrics.GetLeading())
	{
		fLineMetrics.SetLeading(glyphNode->GetLeading());
	}
	if (glyphNode->GetAscent() > fLineMetrics.GetAscent())
	{
		fLineMetrics.SetAscent(glyphNode->GetAscent());
	}
	if (glyphNode->GetCapHeight() > fLineMetrics.GetCapHeight())
	{
		fLineMetrics.SetCapHeight(glyphNode->GetCapHeight());
	}
	if (glyphNode->GetXHeight() > fLineMetrics.GetXHeight())
	{
		fLineMetrics.SetXHeight(glyphNode->GetXHeight());
	}
}

// End, SLCLineBreaker.cpp.

