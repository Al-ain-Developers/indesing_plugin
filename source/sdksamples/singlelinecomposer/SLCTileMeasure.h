//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTileMeasure.h $
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

#ifndef __SLCTileMeasure_h__
#define __SLCTileMeasure_h__

#include "K2Vector.h"
#include "K2Vector.tpp"

/** Stores measures for a tile, an area on a line into which text is flowed.

  	@ingroup singlelinecomposer
	
	@see SLCTileManager
*/
class SLCTileMeasure
{
public:
	typedef base_type data_type;

	/** Constructor.
	*/
	SLCTileMeasure(const PMReal& xPosition, 
				   const PMReal& width, 
				   int32 textSpan) 
	: fXPosition(xPosition), fWidth(width), fTextSpan(textSpan)
	{
	}

	/** Destructor.
	*/
	virtual ~SLCTileMeasure(void)
	{
	}

	/** x position of the tile (it might seem better to store an
		offset relative to the edge of the line but the tiler
		gives us positions, the wax line stores positions so we store
		positions here).
	*/
	PMReal      fXPosition;

	/** The width of the tile.
	*/
	PMReal      fWidth;

	/** Set to zero when composition starts, set to the number of
		characters in the tile once composition completes.
	*/
	int32       fTextSpan;
};

/** A collection of tile measures representing all the areas in a line into which text can flow.
This collection will only have more than one member if text wrap causes intrusions into the flow
of text on a line.
*/
typedef K2Vector<SLCTileMeasure> SLCTileMeasures;

#endif // __SLCTileMeasure_h__

// End, SLCTileMeasure.h

