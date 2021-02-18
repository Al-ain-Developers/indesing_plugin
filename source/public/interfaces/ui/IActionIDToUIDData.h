//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IActionIDToUIDData.h $
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
//  
//  Purpose of interface:
//  Simple data sharing interface for actioncomponents
//  
//========================================================================================

#pragma once
#ifndef __IActionIDToUIDData_h__
#define __IActionIDToUIDData_h__

#include "IPMUnknown.h"
#include "ActionID.h"

//========================================================================================
// CLASS IActionIDToUIDData
//========================================================================================

/** Handy Interface for maintaining a mapping between ActionIDs and UIDs
*/
class IActionIDToUIDData : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IACTIONIDTOUIDDATA };

	/**  Get a count of the entries in our list
		@return count
	*/
	virtual int32 Length() = 0;

	/**  Given an ActionID, return the associated UID
		@param actionID the action we want to get the UID for
		@return the UID associated with this action
	*/
	virtual UID GetUID(ActionID actionID) = 0;
	
	/**  Remove an action and associated UID from our list
		@param actionID the action we want to remove
	*/
	virtual void RemoveEntry(ActionID actionID) =0;
	
	/**  Add a new entry for an ActionID and associated UID
		@param actionID the action we want to add an entry for
		@param someObject the UID associated with this action
	*/
	virtual void AddEntry(ActionID actionID, UID someObject)=0;
	
};

#endif // __IActionIDToUIDData_h__
