//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTileManager.h $
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

#ifndef __SLCTileManager_h__
#define __SLCTileManager_h__

#include "IParagraphComposer.h"

class PMReal;
class SLCLineMetrics;
//class K2Vector;

/** Manages the tiler (IParagraphComposer::Tiler) and creates tile measures (SLCTileMeasures) 
	that represent the areas on a line into which text can flow. Normally there
	will only be one tile on a line. However text wrap may cause intrusions which
	breaks up the places in the line text can go. The tiler takes care of this as
	well as accounting for the effect of irregularly shaped text containers.

	@ingroup singlelinecomposer
	
	@see IParagraphComposer
	@see SLCTileMeasure
*/
class SLCTileManager
{
public:
	/** Constructor. Nothing much done here.
	*/
	SLCTileManager(void) : fTiler(nil), fTOPHeightMetric(Text::kFLOLeading), fAtTOP(kFalse), fParcelPositionDependent(kFalse)
	{
	}

	/** Destructor. Nothing done here.
	*/
	virtual ~SLCTileManager(void)
	{
	}

	/** Prepares the object to use the given tiler.
		@param tiler to be used to obtain tiles, the reference count is bumped.
		@param parcelKey into IParcelList of parcel into which text is to flow.
		@param lineIndentLeft is used to set the left edge of
		the tile measures if it intrudes into a tiler tile.
		@param lineIndentRight is used to set the right edge of
		the tile measures if it intrudes into a tiler tile.
		@postcondition MakeTileMeasures can be called.
		@postcondition Finish must be called.
	*/
	virtual SLComposerStatusCode Initialise(const IParagraphComposer::Tiler* tiler, 
											ParcelKey parcelKey, 
											Text::FirstLineOffsetMetric flo,
											const PMReal& lineIndentLeft,
											const PMReal& lineIndentRight);

	/** Get tiles from the tiler at the given yPosition
		and with the given parameters.
		@precondition Initialise has been called.
		@param yPosition
		@param lineMetrics
		@param gridAlignment
		@param gridAlignmentMetricAdj
		@param nCurrentPosition
		@postcondition GetTileMeasures can be called.
		@postcondition other accessors for tiler returned and derived
		properties can be called.
	*/
	virtual SLComposerStatusCode MakeTileMeasures(const PMReal& yPosition,
												  const SLCLineMetrics& lineMetrics,
												  Text::GridAlignmentMetric gridAlignment, 
												  const PMReal& gridAlignmentMetricAdj, 
												  const TextIndex& nCurrentPosition);

	/** Tidies up after composition of the line is complete.
		@precondition Initialise has been called.
		@postcondition references held by the object are released.
	*/
	virtual void Finish(void);

	/** @return kTrue if the story is overset, kFalse otherwise.
	*/
	bool16 IsStoryOverset(void) const
	{
		if (fParcelKey.IsValid() == kFalse)	return kTrue;
		else return kFalse;
	}

	/** @return IParcelList key of parcel that contains the tiles.
	*/
	ParcelKey GetParcelKey(void) const
	{
		return fParcelKey;
	}

	/** @return height of the tiles.
	*/
	const PMReal& GetHeight(void) const
	{
		return fHeight;
	}

	/** @return height of tiles when they are at the top of the parcel.
	*/
	const PMReal& GetTOPHeight(void) const
	{
		return fTOPHeight;
	}

	/** @return metric used to control the offset between top of parcel
		and the text baseline when the tiles are at the top of the parcel.
	*/
	Text::FirstLineOffsetMetric GetTOPHeightMetric(void)
	{
		return fTOPHeightMetric;
	}

	/** kTrue if at top of parcel, kFalse otherwise.
	*/
	bool16 GetAtTOP(void) const
	{
		return fAtTOP;
	}

	/** kTrue if parcel position dependent, kFalse otherwise.
	*/
	bool16 GetParcelPositionDependent(void) const
	{
		return fParcelPositionDependent;
	}


	/** Top of the tiles derived from tiles returned by tiler.
	*/
	const PMReal& GetTileTop(void) const
	{
		return fTileTop;
	}

	/** Bottom of the tiles derived from tiles returned by the tiler.
	*/
	const PMReal& GetTileBottom(void) const
	{
		return fTileBottom;
	}

	/** Essential tile measures derived from tiles returned by the
		tiler adjusted to account for left and right line indents.
		@return tile measures to be used to flow text into the line.
	*/
	SLCTileMeasures& GetTileMeasures(void)
	{
		return fTileMeasures;
	}

	/** Dump info to Trace.
	*/
	virtual void Dump(void);

private:
	/**	Get tiles from tiler into fTiles.
		@param yPosition IN
		@param lineMetrics IN
		@param gridAlignmentMetric IN
		@param gridAlignmentMetricAdj IN
		@param nCurrentPosition IN
		@return kCompSuccess on success, kCompFailure otherwise.
	*/
	SLComposerStatusCode GetTiles(  const PMReal& yPosition, 
									const SLCLineMetrics& lineMetrics,
									Text::GridAlignmentMetric gridAlignmentMetric, 
									const PMReal& gridAlignmentMetricAdj, 
									const TextIndex& nCurrentPosition);

	/**	Build tile measures from fTiles.
		@return kCompSuccess on success, kCompFailure otherwise.
	*/
	SLComposerStatusCode BuildTileMeasures(void);

	/*	Members set up on initialisation.
	*/
	const IParagraphComposer::Tiler* fTiler;
	PMReal fLineIndentLeft;
	PMReal fLineIndentRight;

	/*	Members updated each time Tiler is called for tiles.
	*/
	ParcelKey fParcelKey;
	PMReal fHeight;
	PMReal fTOPHeight;
	Text::FirstLineOffsetMetric fTOPHeightMetric;
	PMRectCollection fTiles;
	PMReal fYOffset;
	bool16 fAtTOP;
	bool16 fParcelPositionDependent;
	PMReal fLeftMargin;
	PMReal fRightMargin;

	/*	Members derived from the data returned by Tiler and used to flow text into the line.
	*/
	PMReal fTileTop;
	PMReal fTileBottom;
	SLCTileMeasures fTileMeasures;
};

#endif // __SLCTileManager_h__

// End, SLCTileManager.h

