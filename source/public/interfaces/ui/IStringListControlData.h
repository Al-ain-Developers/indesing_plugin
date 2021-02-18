//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStringListControlData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IStringListControlData_h__
#define __IStringListControlData_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "widgetid.h"

//========================================================================================
// CLASS IStringListControlData
/** Control Data Interface associated with widgets based on a list of strings (typically a drop downs variant).
*/
//========================================================================================

class IStringListControlData : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_ISTRINGLISTCONTROLDATA };	// for UseDefaultIID()

	// ----- Constants -----
	/** @name list position constants */
	enum {
		/** at the beginning of the list */
		kBeginning = 0, 
		/** at the end of the list */
		kEnd = -2, 
		/** not found in the list */
		kInvalidStringIndex = -1 
	};

	// ----- List maintainence -----
	/**  Add a string to the list.

		@param newString IN the string to add
		@param at IN index to add the string, default is at end
		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
  */
  virtual void			AddString(const PMString& newString, int32 at = kEnd, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Remove a string to the list.

		@param index IN index of string to remove
		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
	*/
	virtual void			RemoveString(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Clear the list (remove all the strings).

		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
	*/
	virtual void			Clear(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	
	/** Get one of the strings */
	virtual PMString		GetString(int32 index) const = 0;

	/** Replace one of the strings

		@param index IN which string to replace
		@param replaceString IN the new string
		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
	*/
	virtual void			SetString(int32 index, const PMString& replaceString, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
							
	/** Find the index of a string in the list

		@param string IN the string to find
		@param skipIfDisabled IN whether or not the match (if any) be skipped if it is disabled
		@return index of the string, or kInvalidStringIndex if not found.
	*/
	virtual int32			GetIndex(const PMString& string, bool16 skipIfDisabled = kFalse) const = 0;

	/** Find the index of a string whose beginning matches the passed in string.

		@param stringBeginning IN the string to match
		@param caseSensitive IN should the comparison be case sensitive
		@param skipIfDisabled IN whether or not the match (if any) be skipped if it is disabled
		@return index of the string, or kInvalidStringIndex if not found.
	*/
	virtual int32			GetIndexOfPartialString(const PMString& stringBeginning, bool16 caseSensitive, bool16 skipIfDisabled = kFalse) const = 0;

	/** How many strings are in the list? */
	virtual int32			Length() const = 0;

	// Enable/Disable	
	/**	Enable (or disable) the element at the given position in the list.	

		@param index IN item to enable/disable
		@param doEnable IN enable or disable the item
		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
	*/
	virtual void			Enable(int32 index, bool16 doEnable = kTrue, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Disable the element at the given position in the list.	

		@param index IN item to disable
		@param invalidate IN invalidate the associated view, default is true
		@param notifyOfChange IN notify the associated subject, default is true
	*/
	virtual void			Disable(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Is this item enabled? */
	virtual bool16			IsEnabled(int32 index) const = 0;
};

#endif
