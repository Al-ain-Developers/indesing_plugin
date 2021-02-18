//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IOtherEntryData.h $
//  
//  Owner: lance bushore
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
#ifndef __IOtherEntryData__
#define __IOtherEntryData__

#include "GlobalTime.h"

/**	This interface exists to support the behavior for the 'Other' entry in some comboboxes, like the font point size combobox.
	The functionality is like so:
		Whenever you launch the application, if you open the font size dropdown, you'll see an entry named 'Other'.
		If you type in a point size value that's not a predefined value in the list(say, 13.3pt) and open the combobox,
			'Other' is replaced by the new custom value. This is intented to make life easier for customers who use 1 weird value repeatedly.
	This functionality is built into the standard combobox, so if you add an item named 'Other' to your combobox list of initial strings, this will just work.
*/
class IOtherEntryData : public IPMUnknown
{
public:
	/**	Returns the index of the 'Other' entry in the list. It may no longer be named 'Other'
	*/
	virtual int32	GetOtherIndex() const = 0;

	/**	Sets the index of the 'Other' entry in the list. It may no longer be named 'Other'
		@param index the new index of the 'Other' item.
	*/
	virtual void	SetOtherIndex(int32 index) = 0;
	
	/**	Returns the launch time of the app when we last reset the 'Other' entry to read "Other"
	*/
	virtual const GlobalTime &	GetLaunchTime() const = 0;
	
	/**	Records the launch time of the app when we last reset the 'Other' entry to read "Other"
		@param launchTime the app launch time, when we reset the entry to be "Other"
	*/
	virtual void	SetLaunchTime(const GlobalTime & launchTime) = 0;
};

#endif
