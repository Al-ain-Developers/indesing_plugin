//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTagSetList.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __ICONDITIONTAGSETLIST__
#define __ICONDITIONTAGSETLIST__

#include "IPMUnknown.h"
#include "ConditionalTextID.h"

class PMString;

/**
	An interface off the workspace (document or session) that holds a list of IConditionTagSet.
	
	Condition sets are UID based objects that capture visibility states for each condition.  These
	are maintained in lists on the application and document workspaces.  Visibilities for condition(s)
	created after a set is created do not change when a set is made active.  A set may be redefined to
	capture the visibilites for those conditions.

	The list is maintained in ascending alphabetical order.

	@see IConditionalTextFacade
 */
class IConditionTagSetList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAGSETLIST };

	/**	
		Add a new condition tag set at the (optionally) specified location. The condition 
		set is added in ascending alphabetical order.
		@param tag IN The condition tag set to add to the list.
	 */
	virtual void Add(UID set) = 0;

	/**	
		Remove the specified condition tag set from the list.
		@param tag IN The set to remove from the list. 
	 */
	virtual void Remove(UID set) = 0;

	/**	
		Move the condition tag set. This should be called after the condition set is renamed 
		in order to maintain ascending alphabetical order.
		@param tag IN The UID of the set to move.
	 */
	virtual void Move(UID set) = 0;
		
	/**	
		Get the number of condition tag sets in the list.
		@return int32 The number of sets.
	 */
	virtual int32 GetCount() const = 0;

	/**	
		Get the UID of the condition tag set at the specified index in the list.
		@param index IN The index of the set.
		@return UID The UID of the set at the specified index.
	 */
	virtual UID GetNthSet(int32 index) const = 0;

	/**	 
		Get the index of the specified condition tag set in the list.
		@param tag IN The UID of the set.
		@return int32 The index of the set (0-based), or -1 if not found.
	 */
	virtual int32 GetSetIndex(UID set) const = 0;

	/**
		Get the UID of the condition tag set with the specified name.
		@param name IN The name of the set to find.
		@return UID The UID of the set found, kInvalidUID if not found.
	 */
	virtual UID FindByName(const WideString& name) const = 0;
	
	/**
		Suggest a condition tag set name.
		@return a unique new set name
	 */	
	virtual WideString SuggestNewName() const = 0;
};

#endif // __ICONDITIONTAGSETLIST__
