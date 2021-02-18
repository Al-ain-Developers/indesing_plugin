//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTagList.h $
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
#ifndef __ICONDITIONTAGLIST__
#define __ICONDITIONTAGLIST__

#include "IPMUnknown.h"
#include "ConditionalTextID.h"

class PMString;

/**
	An interface off the workspace (document or session) that holds a list of IConditionTag.

	The list is maintained in ascending alphabetical order.

	@see IConditionalTextFacade
	@see IConditionTag
 */
class IConditionTagList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAGLIST };

	/**	
		Add a new condition tag. The condition is added in ascending alphabetical order.
		@param tag IN The condition to add to the list.
	 */
	virtual void Add(UID condition) = 0;

	/**	
		Remove the specified condition tag from the list.
		@param tag IN The condition to remove from the list. 
	 */
	virtual void Remove(UID condition) = 0;

	/**	
		Move the condition tag. This should be called after the condition's name is changed 
		in order to maintain ascending alphabetical order.
		@param tag IN The UID of the condition to move.
	 */
	virtual void Move(UID condition) = 0;
		
	/**	
		Get the number of tags in the list.
		@return int32 The number of conditions.
	 */
	virtual int32 GetCount() const = 0;

	/**	
		Get the UID of the condition tag at the specified index in the list.
		@param index IN The index of the condition.
		@return UID The UID of the condition at the specified index.
	 */
	virtual UID GetNthCondition(int32 index) const = 0;

	/**	 
		Get the index of the specified condition tag in the list.
		@param tag IN The UID of the condition.
		@return int32 The index of the condition (0-based), or -1 if not found.
	 */
	virtual int32 GetConditionIndex(UID condition) const = 0;

	/**
		Get the UID of the condition tag with the specified name.
		@param name IN The name of the condition to find.
		@return UID The UID of the condition found, kInvalidUID if not found.
	 */
	virtual UID FindByName(const WideString& name) = 0;
};

#endif // __ICONDITIONTAGLIST__
