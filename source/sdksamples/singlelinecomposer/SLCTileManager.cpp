//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTileManager.cpp $
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
// Note: interface includes below only needed for diagnostic trace purposes:
#include "ITextParcelList.h"
#include "IGeometry.h"
#include "IParcelList.h"
#include "ITextFrameColumn.h"

// General includes:

// Project includes:
#include "SLC.h"
#include "SLCTileMeasure.h"
#include "SLCLineMetrics.h"
#include "SLCTileManager.h"

/* Initialise
*/
SLComposerStatusCode SLCTileManager::Initialise(const IParagraphComposer::Tiler* tiler, 
												ParcelKey parcelKey, 
												Text::FirstLineOffsetMetric flo,
												const PMReal& lineIndentLeft, 
												const PMReal& lineIndentRight)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::Initialise()-->In\n");
	SLComposerStatusCode status = kCompFailure;
	do
	{
		ASSERT(tiler != nil);
		if (tiler == nil)
		{
			break;
		}
		ASSERT_MSG(fTiler == nil, "Initialise called without an accompanying Finish, please call Finish");
		fTiler = tiler;
		fParcelKey = parcelKey;
		fLineIndentLeft = lineIndentLeft;
		fLineIndentRight = lineIndentRight;
		fHeight = 0.0;
		fTOPHeight = 0.0;
		fTOPHeightMetric = flo;
		fYOffset = 0.0;
		fAtTOP = kFalse;
		fParcelPositionDependent = kFalse;
		fTileTop = 0.0;
		fTileBottom = 0.0;

		status = kCompSuccess;
	} while (false);
	TRACEFLOW("SLCTileManager", "SLCTileManager::Initialise()-->Out\n");
	return status;
}

/* Finish
*/
void  SLCTileManager::Finish(void)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::Finish()-->In\n");
	ASSERT_MSG(fTiler!=nil, "Finish called without calling Initialise, please call Initialise first");
	if (fTiler != nil)
	{
		fTiler = nil;
	}
	TRACEFLOW("SLCTileManager", "SLCTileManager::Finish()-->Out\n");
}

/* MakeTileMeasures
*/
SLComposerStatusCode SLCTileManager::MakeTileMeasures(const PMReal& yPosition, 
													  const SLCLineMetrics& lineMetrics, 
													  Text::GridAlignmentMetric gridAlignmentMetric,  
													  const PMReal& gridAlignmentMetricAdj,  
													  const TextIndex& nCurrentPosition)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::GetTileMeasures-->In\n");
	SLComposerStatusCode status = kCompFailure;

	do
	{
		// Clear out the old.
		fTileMeasures.clear();

		// Get new tiles from the tiler....
		status = this->GetTiles(yPosition, 
								lineMetrics, 
								gridAlignmentMetric, 
								gridAlignmentMetricAdj, 
								nCurrentPosition);
		if (status != kCompSuccess)
		{
			break;
		}

		// ...and derive the tile measures (position and width) from them.
		status = this->BuildTileMeasures();
		if (status != kCompSuccess)
		{
			break;
		}

		// Trace the tile info for diagnostic purposes.
		this->Dump();

	} while (false);

	TRACEFLOW("SLCTileManager", "SLCTileManager::GetTileMeasures-->Out status=%d\n", status);
	return status;
}

/* GetTiles
*/
SLComposerStatusCode SLCTileManager::GetTiles(const PMReal& yPosition,  const SLCLineMetrics& lineMetrics,  Text::GridAlignmentMetric gridAlignmentMetric, const PMReal& gridAlignmentMetricAdj, const TextIndex& nCurrentPosition)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::GetTiles-->In yPosition=%f, height=%f\n", ::ToDouble(yPosition));
	SLComposerStatusCode status = kCompFailure;

	do
	{
		// Clear out the old tiles.
		fTiles.clear();

		// The minumum width of a tile must be big enough to fit the indents plus one glyph.
		PMReal minimumWidth = fHeight + fLineIndentLeft + fLineIndentRight;

		// Call the tiler in a loop until tiles are found. The tiler
		// will return tiles if the story is overset.
		fYOffset = yPosition;

		// Remember the heights being used to size the tile. We use this later
		// to check that the tiles are tall enough to accept the glyphs
		// encountered on the line.
		fHeight = lineMetrics.GetValue(kSLCLineHeightMetric);
		fTOPHeight = lineMetrics.GetValue(fTOPHeightMetric);
		bool16 tileFound = kFalse;
		do
		{
			// this should be 0.0 in Roman, line aki in J.
			// ###TODO: CHECK and TEST THIS
			//
			// 10/02/09 dwaterfa: Nah, this is not correct. The value here is
			// adjustment to make to the YPosition of the WaxLine (bottom of
			// the returned Tile) to reach the leading model reference point.
			// So for Roman and AkiAbove this value IS zero, for AkiBelow it is
			// the negative of the line height (to reach the top of the embox),
			// and for Center Leading (Up) it is negative 1/2 line height (to
			// reach the center of the emBox).
			//
			Text::LeadingModel leadingModel = kSLCLeadingModel;
			PMReal leading = lineMetrics.GetLeading();
			PMReal leadingModelOffset = 0.0; // Roman
			PMReal leadingDiff = leading - lineMetrics.GetCapHeight();

			tileFound = fTiler->GetTiles(minimumWidth,
										fHeight,
										fTOPHeight,
										gridAlignmentMetric,
										gridAlignmentMetricAdj,
										leadingModel,
										leading,
										leadingModelOffset,
										leadingDiff,
										nCurrentPosition,
										kTrue, //affectedByVerticalJust.
										&fParcelKey,
										&fYOffset, 
										&fTOPHeightMetric,
										fTiles,
										&fAtTOP,
										&fParcelPositionDependent,
										&fLeftMargin,
										&fRightMargin);
			if (tileFound == kFalse)
			{
				// Tile is at top of the parcel but the specified pTOPHeightMetric 
				// does not match the parcel's. Call tiler again with the
				// fTOPHeightMetric it returned and its associated value.
				fTOPHeight = lineMetrics.GetValue(fTOPHeightMetric);
				TRACEFLOW("SLCTileManager", "Calling IParagraphComposer::Tiler::GetTiles again with fTopHeightMetric=%d, fTOPHeight=%f", 
						  fTOPHeightMetric,
						  ::ToDouble(fTOPHeight));
			}
		} while (tileFound == kFalse);

		// Complain bitterly if no tile can be found.
		ASSERT(fTiles.size() > 0);
		if (fTiles.size() <= 0)
		{
			break;
		}

		// OK we have tiles from the tiler.
		fTileTop = fTiles[0].Top();
		fTileBottom = fTiles[0].Bottom();

		status = kCompSuccess;

	} while (false);

	TRACEFLOW("SLCTileManager", "SLCTileManager::GetTiles-->Out status=%d\n", status);

	return status;
}

/* BuildTileMeasures
*/
SLComposerStatusCode SLCTileManager::BuildTileMeasures(void)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::BuildTileMeasures-->In\n");
	SLComposerStatusCode status = kCompFailure;
	fTileMeasures.clear();

	do
	{
		// Check out the tiles we've got, adjust their bounds
		// to account for left and right indent. and derive 
		// SLCTileMeasures from them.
		for (int32 i = 0; i < fTiles.size(); i++)
		{
			const PMRect& currentTile = fTiles [i];

			bool16 ignore = kFalse;
			bool16 adjust = kFalse;

			PMReal tileIndentLeft = 0.0;
			if (currentTile.Right() < fLeftMargin + fLineIndentLeft)
			{
				// indent means tile has no useful space.
				ignore = kTrue;
				ASSERT_FAIL("tiler returned tile that was smaller than requested minimum width");
			}
			else if (currentTile.Left() < fLeftMargin + fLineIndentLeft)
			{
				// The left indent intrudes into the tile.
				tileIndentLeft = fLineIndentLeft - (currentTile.Left() - fLeftMargin);
				adjust = kTrue;
			}

			// Set the right indent for the tile.
			PMReal tileIndentRight = 0.0;
			if (currentTile.Left() > fRightMargin - fLineIndentRight)
			{
				ignore = kTrue;
				ASSERT_FAIL("tiler returned tile that was smaller than requested minimum width");
			}
			else if (currentTile.Right() > fRightMargin - fLineIndentRight)
			{
				// The right indent intrudes into the tile.
				tileIndentRight = fLineIndentRight - (fRightMargin - currentTile.Right());
				adjust = kTrue;
			}

			if (ignore == kTrue)
			{
				// Ignore this tile and check out the next one.
				continue;
			}
			else if (adjust == kTrue)
			{
				// Create an adjusted tile measure.
				// The left or right indent for the line intrudes
				// into this tile. Adjust the left/right edge 
				// accordingly.
				PMRect adjusted(currentTile.Left() + tileIndentLeft,
								currentTile.Top(),
								currentTile.Right() - tileIndentRight,
								currentTile.Bottom());
				fTileMeasures.push_back(SLCTileMeasure(currentTile.Left() + tileIndentLeft,	// fXPosition.
													   currentTile.Width() - tileIndentLeft - tileIndentRight, // fWidth.
													   0));	// fTextSpan.
			}
			else
			{
				// Create a tile measure.
				fTileMeasures.push_back(SLCTileMeasure(currentTile.Left(), // fXPosition.
													   currentTile.Width(),	// fWidth.
													   0));	// fTextSpan.

			}
		}

		ASSERT(fTileMeasures.size() > 0);
		if (fTileMeasures.size() <= 0)
		{
			break;
		}

		status = kCompSuccess;

	} while (false);

	TRACEFLOW("SLCTileManager", "SLCTileManager::BuildTileMeasures-->In status=%d\n", status);

	return status;
}

/* Dump
*/
void SLCTileManager::Dump(void)
{
	TRACEFLOW("SLCTileManager", "SLCTileManager::Dump():\n");
	do
	{
		if (this->IsStoryOverset())
		{
			TRACEFLOW("SLCTileManager", "Composing overset text.\n");
		}
		else
		{
			// Dump frame/parcel info.
			ParcelKey parcelKey = fParcelKey;
			if (parcelKey.IsValid() == kFalse)
			{
				break;
			}

			PMRect contentBounds = fTiler->GetParcelContentBounds(parcelKey);
			TRACEFLOW("SLCTileManager", "frameBounds Left=%f Top=%f Right=%f Bottom=%f\n", 
					  ::ToDouble(contentBounds.Left()), 
					  ::ToDouble(contentBounds.Top()), 
					  ::ToDouble(contentBounds.Right()), 
					  ::ToDouble(contentBounds.Bottom()));
		}
	} while (false);

	// Dump tiles from the tiler.
	for (int32 i = 0; i < fTiles.size(); i++)
	{
		const PMRect& tile = fTiles [i];
		TRACEFLOW("SLCTileManager", "tiles [%d] Left=%f Top=%f Right=%f Bottom=%f\n",
				  i, 
				  ::ToDouble(tile.Left()), 
				  ::ToDouble(tile.Top()), 
				  ::ToDouble(tile.Right()), 
				  ::ToDouble(tile.Bottom()));
	}

	// Dump tile measures derived from tiler info.
	SLCTileMeasures::iterator iter;
	TRACEFLOW("SLCTileManager", "fTileMeasures at fTileTop=%f, fTileBottom=%f\n",
			  ::ToDouble(fTileTop),
			  ::ToDouble(fTileBottom));
	TRACEFLOW("SLCTileManager", "# fXPosition, fWidth, fTextSpan\n");
	for (iter = fTileMeasures.begin(); iter < fTileMeasures.end(); iter++)
	{
		TRACEFLOW("SLCTileManager", "%d, %f, %f, %d\n", 
				  iter - fTileMeasures.begin(),
				  ::ToDouble(iter->fXPosition), 
				  ::ToDouble(iter->fWidth), 
				  iter->fTextSpan);
	}

	// Dump assorted tiler returned and derived information.
#ifdef DEBUG
	PMString parcelStr(fParcelKey.ToDec());
#else
	PMString parcelStr("<unknown>");
#endif
	TRACEFLOW("SLCTileManager", "fParcelKey=%s, fLineIndentLeft=%f, fLineIndentRight=%f, fHeight=%f, fTOPHeight=%f, fTOPHeightMetric=%d\n",
		parcelStr.GetUTF8String().c_str(),
			  ::ToDouble(fLineIndentLeft),
			  ::ToDouble(fLineIndentRight),
			  ::ToDouble(fHeight),
			  ::ToDouble(fTOPHeight),
			  fTOPHeightMetric);
	TRACEFLOW("SLCTileManager", "fYOffset=%f, fAtTOP=%d, fParcelPositionDependent=%d, fTileTop=%f, fTileBottom=%f, fLeftMargin=%f, fRightMargin=%f\n",
			  ::ToDouble(fYOffset),
			  fAtTOP,
			  fParcelPositionDependent,
			  ::ToDouble(fTileTop),
			  ::ToDouble(fTileBottom),
			  ::ToDouble(fLeftMargin),
			  ::ToDouble(fRightMargin));
}

// End, SLCTileManager.cpp.




