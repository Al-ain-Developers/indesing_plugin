//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IOpacityGradientStops.h $
//  
//  Owner: Matt Phillips
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
//  Defines an opacity gradient's data.  Similar to gradient fill data, but at each stop
//  there's only a simple PMReal opacity, not a full set.  That, and the gradient type
//  is stored externally since in the future we may want to add this interface onto 
//  color gradients, which would then create a conflict of attributes problem.
//  
//  Note that an empty gradient is assumed to be equivalent to not having a gradient
//  (ie, constant alpha=1).
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"					  
#include "XPID.h"
#include "GraphicTypes.h"

class IOpacityGradientStops : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOPACITYGRADIENTSTOPS };

public:
	/** Resets the gradient to the default configuration (100% opacity to 0% opacity).
	*/
	virtual void ResetToDefault() = 0;
	
	/** Resets the gradient to a no-stop configuration.  Note that this isn't technically a valid
		gradient state; you'll need to add at least two stops for it to be valid.
	*/
	virtual void DeleteAllStops() = 0;
	
	/** Returns the number of stops in the gradient.
		@return The number of stops.
	*/
	virtual int32 GetNumStops() const = 0;
	
	/** Adds a new stop at the specified location.
		@param beforeStop IN The stop before which you want to add the new stop; -1 adds at the end.
		@return The index of the new stop.
	*/
	virtual int32 InsertStop(int32 beforeStop = -1) = 0;

	/** Removes the stop at the specified location.
		@param whichStop IN The stop you want to delete.
		@return kTrue if successful; kFalse if not.
	*/
	virtual bool32 DeleteStop(int32 whichStop) = 0;

	/** Set the opacity for a particular stop.
		@param whichStop IN Which stop to set.
		@param opacity IN The opacity to assign to the stop.
	*/
	virtual void SetStopOpacity(int32 whichStop, PMReal opacity) = 0;
	
	/** Get the opacity for a particular stop.
		@param whichStop IN Which stop to set.
		@return The opacity of the specified stop.
	*/
	virtual PMReal GetStopOpacity(int32 whichStop) const = 0;
	
	/** Set the position for a particular stop.
		@param whichStop IN Which stop to set.
		@param position IN The position to assign to the stop.
		@param autoRearrange IN True to rearrange stop indices automatically based on location comparisons.
				If False, the position will be set without any checking; the caller is responsible for
				maintaining correct ordering.  This is useful if you want to create a particular arrangement
				of stops (legal, of course) without the auto-rearranging switching indices around on you.
		@return The new index of the stop; -1 if an error occurred; whichStop if autoRearrange = kFalse.
	*/
	virtual int32 SetStopPosition(int32 whichStop, PMReal position, bool32 autoRearrange = kTrue) = 0;
	
	/** Get the position for a particular stop.
		@param whichStop IN Which stop to set.
		@return The position of the specified stop.
	*/
	virtual PMReal GetStopPosition(int32 whichStop) const = 0;
	
	/** Set the midpoint for a particular stop.
		@param whichStop IN Which stop to set.
		@param midpoint IN The midpoint to assign to the stop.
	*/
	virtual void SetStopMidpoint(int32 whichStop, PMReal midpoint) = 0;
	
	/** Get the midpoint for a particular stop.
		@param whichStop IN Which stop to set.
		@return The midpoint of the specified stop.
	*/
	virtual PMReal GetStopMidpoint(int32 whichStop) const = 0;
	
	/** Set the relative location for a particular stop.
		@param whichStop IN Which stop to set.
		@param relLoc IN The relative location to assign to the stop.
	*/
	virtual void SetStopMidpointRelativeLocation(int32 whichStop, PMReal relLoc) = 0;
	
	/** Get the relative location for a particular stop.
		@param whichStop IN Which stop to set.
		@return The relative location of the specified stop.
	*/
	virtual PMReal GetStopMidpointRelativeLocation(int32 whichStop) const = 0;
	
	/**	Return kTrue if both sets of gradient data are equal.
		@param iOther The gradient to compare.
		@return kTrue if equal otherwise kFalse.
	*/
	virtual bool16 Equals(const IOpacityGradientStops* iOther) const = 0;

	/**	Makes a copy of another gradient's data.  Any existing data in this gradient is wiped.
		@param pSrc The gradient data from which to copy.
	*/
	virtual void CopyFrom(const IOpacityGradientStops* iOther) = 0;

	/**	Return the data base associated with this gradient data.
		@return the data base associated with this gradient data.
		IDataBase* can be nil if gradient object does not have a assoicated
		database or if a data base cannot be identified.
	*/
	virtual IDataBase* GetDataBase (void) const = 0;
};








