//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICounterControlData.h $
//  
//  Owner: Frits Habermann
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

#pragma once
#ifndef __ICOUNTERCONTROLDATA__
#define __ICOUNTERCONTROLDATA__

#include "widgetid.h"

/** Interface representing counter state, used for widgets like a scrollbar or splitter.
*/
class ICounterControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOUNTERCONTROLDATA };

	/** Specify lower bound for range spanned 
		@param min
	*/
	virtual void SetMinimum(int32 min) = 0;
	/** Specify upper bound for range spanned
		@param max
	*/
	virtual void SetMaximum(int32 max) = 0;

	/** Set state to given value, will be within range [min,max]
		@param value value to set
		@param invalidate if kTrue, specify that control needs redrawn
		@param notifyOfChange if kTrue, notify registered observers of change
	*/
	virtual void SetValue(int32 value, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Set a new page size for this control. Note that pageSize is (max - min) / howMuchIsVisibleAtOnce on Win and howMuchIsVisibleAtOnce on Mac
		@param pageSize
	*/
	virtual void SetPageSize(int32 pageSize) = 0;


	/** Accessor for lower bound on counter range
		@return lower bound on counter range
	*/
	virtual int32 GetMinimum() const = 0;

	/** Accessor for upper bound on counter range
		@return upper bound on counter range
	*/
	virtual int32 GetMaximum() const = 0;

	/** Accessor for counter state
		@return current counter state
	*/
	virtual int32 GetValue() const = 0;

	/** Accessor for the "page size", i.e. how much of a scrollbar, say, is visible
		@return the page size
	*/
	virtual int32 GetPageSize() const = 0;

	
	/**
		@param invalidate if kTrue, specify that control needs redrawn
		@param notifyOfChange if kTrue, notify registered observers of change
		@return the new value of counter state
	*/
	virtual int32 Increment(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**
		@param invalidate if kTrue, specify that control needs redrawn
		@param notifyOfChange if kTrue, notify registered observers of change
		@return the new value of counter state
	*/
	virtual int32 Decrement(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**
		@param invalidate if kTrue, specify that control needs redrawn
		@param notifyOfChange if kTrue, notify registered observers of change
		@return the new value of counter state
	*/
	virtual int32 IncrementMultiple(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**
		@param invalidate if kTrue, specify that control needs redrawn
		@param notifyOfChange if kTrue, notify registered observers of change
		@return the new value of counter state
	*/
	virtual int32 DecrementMultiple(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	
	/** Accessor for the current increment value of this counter
		@return current increment value
	*/
	virtual int32 GetIncrement() const = 0;

	/** Accessor the multiple-increment property of this counter
		@return current state of the multiple-increment
	*/
	virtual int32 GetIncrementMultiple() const = 0;


	/** Specify a new increment for the counter. If 0, defaults to 1.
		@param increment new increment for counter
	*/
	virtual void SetIncrement(int32 increment) = 0;

	/** Specify a new multiple-increment property for counter. If 0, defaults to 1.
		@param increment new multiple-increment for counter
	*/
	virtual void SetIncrementMultiple(int32 increment) = 0;

};

/** Data class used by ICounterControlData in broadcasting state change information to observers.
*/
class CounterControlUpdateParams
{
public:
	/** Constructor */
	CounterControlUpdateParams(int32 oldValue, int32 newValue, bool16 verticalOrientation = kFalse) :
		fOldValue(oldValue),
		fNewValue(newValue),
		fIsVertical(verticalOrientation)
	{
	}
	
	/** */
	int32 fOldValue;
	/** */
	int32 fNewValue;
	/** */
	bool16 fIsVertical;
};

#endif
