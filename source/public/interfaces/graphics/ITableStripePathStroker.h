//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITableStripePathStroker.h $
//  
//  Owner: Melissa Cheng
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
//  
//  Defines the stroker service interface used for table strokes.
//  
//========================================================================================

#pragma once
#ifndef __ITableStripePathStroker__
#define __ITableStripePathStroker__

#include "IPMUnknown.h"
#include "GraphicsID.h"

class IGraphicsPort;
class IGraphicStyleDescriptor;
class IPathGeometry;

/** StripeLengthAdjustArray is a vector of real numbers, used to indicate how each 
	much each stripe should be lengthened. Array[0], Array[1], ... correspond with 
	how much the first, second, ... stripes should be lengthened respectively.
*/
typedef K2Vector<PMReal> StripeLengthAdjustArray;

//=================================================================================== 
/** Public interface exposing the table stripe path stroker.

	Allows individual stripes in a stroke to be drawn to different lengths, offset 
	from the path. If the StripeLengthAdjustArrays passed in are empty, the stroke 
	is drawn exactly as it would be by IPathStroker.

	Used in tables to make stripes meet other stripes at joins.
	
	Usually accessed via IPathStroker because both are on the same boss.

    @author     Melissa Cheng
*/ 
//=================================================================================== 

class ITableStripePathStroker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITABLESTRIPEPATHSTROKER };

	/**	Creates striped paths and strokes them (like IPathStroker::StrokePath) but 
		adjusts stripes to different lengths, offset from srcPath, lengthening the stripes 
		at the start and end of the path according to startMeet and endMeet respectively.

		@param pageitem		Graphic style descriptor with line type and other drawing information.
		@param srcPath		Underlying path of stroke. startMeet/endMeet offset from the first/last points of srcPath.
		@param gPort		Graphics port used to draw.
		@param startMeet	Specifies amount to lengthen stripes at start of path.
		@param endMeet		Specifies amount to lengthen stripes at end of path.
	*/ 
	virtual ErrorCode StrokePathToMeetStripe 
		(
			IGraphicStyleDescriptor*	 	pageitem, 
			const IPathGeometry* 			srcPath, 
			IGraphicsPort* 					gPort,
			const StripeLengthAdjustArray&	startMeet,
			const StripeLengthAdjustArray&	endMeet
		) const = 0;
};

#endif
