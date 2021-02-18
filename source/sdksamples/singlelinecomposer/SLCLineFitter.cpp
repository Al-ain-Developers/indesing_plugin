//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCLineFitter.cpp $
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
#include "IWaxCollection.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"

// General includes:
#include "TextChar.h"

// Project includes:
#include "SLC.h"
#include "SLCTileMeasure.h"
#include "SLCGlyphNode.h"
#include "SLCLineMetrics.h"
#include "SLCGlyphNodeList.h"
#include "SLCDiagnostics.h"
#include "SLCTileComposer.h"
#include "SLCLineFitter.h"

/* RebuildLineToFit
*/
bool16 SLCLineFitter::RebuildLineToFit(IParagraphComposer::RebuildHelper* helper)
{
	const IWaxLine* waxLine = helper->GetWaxLine();
	IComposeScanner* composeScanner = helper->GetComposeScanner();
	TextIndex startingIndex = helper->GetTextIndex();
	TRACEFLOW("SLCLineFitter", "SLCLineFitter::RebuildLineToFit()-->In startingIndex=%d\n", startingIndex); 
	bool16 result = kFalse;

	do
	{
		// Validate parameters.
		ASSERT(composeScanner != nil);
		if (composeScanner == nil)
		{
			break;
		}
		ASSERT(waxLine != nil);
		if (waxLine == nil)
		{
			break;
		}
		ASSERT(waxLine->GetTextSpan() > 0);
		if (waxLine->GetTextSpan() <= 0)
		{
			break;
		}
		TextIterator iter = composeScanner->QueryDataAt(startingIndex, nil, nil);
		ASSERT_MSG(iter.IsNull() != kTrue, "no characters to compose");
		if (iter.IsNull())
		{
			break;
		}
		ASSERT_MSG((*iter).GetValue() != kTextChar_Table && 
				   (*iter).GetValue() != kTextChar_TableContinued,
				   "Can't compose table character, the application is supposed to do that");
		if ((*iter).GetValue() == kTextChar_Table || 
			(*iter).GetValue() == kTextChar_TableContinued)
		{
			break;
		}

		// Initialise local members in preparation for rebuilding the line.
		ASSERT_MSG(fComposeScanner == nil, "fComposeScanner should be nil on entry");
		fComposeScanner = composeScanner;
		fComposeScanner->AddRef();
		ASSERT_MSG(fWaxLine == nil, "fWaxLine should be nil on entry");
		fWaxLine = waxLine;
		fWaxLine->AddRef();
		fTextIndex = startingIndex;
		fXPosition = fWaxLine->GetXPosition();

		// Fit the characters into the line.
		if (this->FitLine() == kCompSuccess)
		{
			result = kTrue;
		}

	} while (false);

	// Clean up.
	if (fWaxLine != nil)
	{
		fWaxLine->Release();
		fWaxLine = nil;
	}
	if (fComposeScanner != nil)
	{
		fComposeScanner->Release();
		fComposeScanner = nil;
	}

	TRACEFLOW("SLCLineFitter", "SLCLineFitter::RebuildLineToFit()-->Out result=%d\n", result); 

	return result;
}

/* FitLine
*/
SLComposerStatusCode SLCLineFitter::FitLine(void)
{
	TRACEFLOW("SLCLineFitter", "SLCLineFitter::FitLine()-->In fTextIndex=%d, fXPosition=%f\n", fTextIndex, ::ToDouble(fXPosition)); 

	SLCDiagnostics slcDiagnostics;

	SLComposerStatusCode status = kCompFailure;

	fGlyphNodeList.Clear();

	do
	{
		// Trace the wax line we are going to fit glyphs into.
		slcDiagnostics.DumpWaxLine("SLCLineFitter", fWaxLine);

		// Build a vector of tile measures from the wax line.
		SLCTileMeasures tileMeasures;
		int32 numberOfTiles = fWaxLine->GetNumberOfTiles();
		ASSERT(numberOfTiles > 0);
		if (numberOfTiles <= 0)
		{
			break;
		}
		{
			for (int32 i = 0; i < numberOfTiles; i++)
			{
				SLCTileMeasure tile(fWaxLine->GetXPosition(i),
									fWaxLine->GetTargetWidth(i),
									fWaxLine->GetTextSpanInTile(i));
				tileMeasures.push_back(tile);
			}
		}

		// Fit the characters in the line into these tile measures.
		{
			for (int32 i = 0; i < tileMeasures.size(); i++)
			{
				status = this->FitTile(tileMeasures[i]);
				if (status < kCompSuccess)
				{
					break;
				}
			}
		}

		// Generate wax for the line.
		if (status >= kCompSuccess)
		{
			status = this->CreateWax(slcDiagnostics);
		}

	} while (false);

	fGlyphNodeList.Clear();

	TRACEFLOW("SLCLineFitter", "SLCLineFitter::FitLine()-->Out status=%d\n", status); 

	return status;
}

/* FitTile
*/  
SLComposerStatusCode SLCLineFitter::FitTile(const SLCTileMeasure& tile)
{
	TRACEFLOW("SLCLineFitter", "SLCLineFitter::FitTile()->In fTextIndex=%d, tile.fXPosition=%f, tile.fWidth=%f, tile.fTextSpan=%d\n",
			  fTextIndex,
			  ::ToDouble(tile.fXPosition), 
			  ::ToDouble(tile.fWidth),
			  tile.fTextSpan);
	SLComposerStatusCode status = kCompFailure;

	int32 fromGlyphNodeIndex = fGlyphNodeList.Length();

	do
	{
		// Flow range of characters into the tile.
		SLCTileComposer tileComposer(fComposeScanner, fXPosition, fTextIndex);
		status = tileComposer.FlowTextByTileTextSpan(tile, fGlyphNodeList);
		if (status < kCompSuccess)
		{
			break;
		}
		ASSERT(tile.fTextSpan == tileComposer.GetTextSpan());
		if (tile.fTextSpan != tileComposer.GetTextSpan())
		{
			break;
		}

		// Check if the text fits in the tile.
		if (tileComposer.GetFitTextSpan() == tile.fTextSpan)
		{
			status = kCompSuccess;
			break;
		}

		// Fit trailing white space.
		this->FitTrailingWhiteSpace(tile, fromGlyphNodeIndex, tileComposer);
		status = kCompSuccess;

	} while (false);

	if (status >= kCompSuccess)
	{
		// Update the index into the text model of the next character to be composed.
		fTextIndex += tile.fTextSpan;
	}

	fGlyphNodeList.Dump(fromGlyphNodeIndex, "SLCLineFitter nodes");

	TRACEFLOW("SLCLineFitter", "SLCLineFitter::FitTile()->Out status=%d, fTextIndex=%d, tile.fTextSpan=%d, fGlyphNodeList.GetTextSpan=%d\n", 
			  status,
			  fTextIndex,
			  tile.fTextSpan,
			  fGlyphNodeList.GetTextSpan(fromGlyphNodeIndex));

	return status;
}

/* FitTrailingWhiteSpace
*/
void SLCLineFitter::FitTrailingWhiteSpace(const SLCTileMeasure& tile, int32 fromGlyphNodeIndex, const SLCTileComposer& tileComposer)
{
	do
	{
		// Get the width of the trailing white space.
		PMReal trailingWhiteSpaceWidth = fGlyphNodeList.GetTrailingWhiteSpaceWidth(fromGlyphNodeIndex);
		const PMReal kZero(0.0);
		ASSERT(trailingWhiteSpaceWidth > kZero);
		if (trailingWhiteSpaceWidth <= kZero)
		{
			break;
		}

		// Calculate the width into which the trailing space must fit applying a minimum limit if appropriate.
		// Note we don't use SLCTileMeasure::GetFitWidth since some of the trailing white space may already fit
		// but the rest of it may cause the tile width to be exceeded. We want to scale all trailing white space
		// not just the trailing white space that doesn't fit.
		PMReal fitToWidth = tile.fWidth - (tileComposer.GetTextWidth() - trailingWhiteSpaceWidth);
		const PMReal kSLCMinTrailingWhiteSpaceWidth(1.0);
		if (fitToWidth < kSLCMinTrailingWhiteSpaceWidth)
		{
			fitToWidth = kSLCMinTrailingWhiteSpaceWidth;
		}

		// Calculate the scale factor to be applied...
		PMReal widthScaleFactor = fitToWidth / trailingWhiteSpaceWidth;
		TRACEFLOW("SLCLineFitter", "trailingWhiteSpaceWidth=%f, fitToWidth=%f, widthScaleFactor=%f\n",
				  ::ToDouble(trailingWhiteSpaceWidth),
				  ::ToDouble(fitToWidth),
				  ::ToDouble(widthScaleFactor));

		// ...and adjust the width of all trailing white space accordingly.
		fGlyphNodeList.FitTrailingWhiteSpace(fromGlyphNodeIndex, widthScaleFactor);

	} while (false);


}

/* CreateWax
*/
SLComposerStatusCode SLCLineFitter::CreateWax(const SLCDiagnostics & slcDiagnostics)
{
	TRACEFLOW("SLCLineFitter", "SLCLineFitter::CreateWax()-->In\n"); 

	SLComposerStatusCode status = kCompFailure;

	do
	{
		// The wax is built from info in fGlyphNodeList. If it is empty then complain.
		ASSERT_MSG(fGlyphNodeList.Length() > 0, "Glyph node list is empty, can't create wax");
		if (fGlyphNodeList.Length() <= 0)
		{
			break;
		}

		// Create wax for the line.
		InterfacePtr<IWaxCollection> waxCollection(fWaxLine, UseDefaultIID());
		ASSERT_MSG(waxCollection->GetWaxLine() != nil, "wax line not properly initialized!");
		if (waxCollection->GetWaxLine() == nil)
		{
			waxCollection->SetWaxLine(fWaxLine);
		}
		ASSERT(waxCollection->Count() == 0);
		for (int32 i = 0; i < fGlyphNodeList.Length(); i++)
		{
			fGlyphNodeList [i]->Dump("");
			fGlyphNodeList [i]->CreateWax(fWaxLine);
		}
		waxCollection->ConstructionComplete();
		slcDiagnostics.DumpWaxLineAndRuns("SLCLineFitter", fWaxLine);  

		status = kCompSuccess;

	} while (false);

	TRACEFLOW("SLCLineFitter", "SLCLineFitter::CreateWax()-->Out status=%d\n", status); 

	return status;
}

// End, SLCLineFitter.cpp.

