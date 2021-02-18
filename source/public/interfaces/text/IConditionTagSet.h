//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTagSet.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __ICONDITIONTAGSET__
#define __ICONDITIONTAGSET__

#include "IPMUnknown.h"
#include "IConditionalTextFacade.h"

#include "ConditionalTextID.h"

#include <vector>

class IDataBase;
class WideString;

using namespace Facade;

/** Interface to get and set data associated with condition tag sets. These
	are known as "sets" in the conditional text UI. High-level operations 
	are provided by the conditional text facade.
	
	@see kConditionTagSetBoss
	@see IConditionalTextFacade
*/
class IConditionTagSet : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAGSET };

	/**	Set the name of the condition tag set.
		@param name IN The new name for the condition tag set
		@return ErrorCode kSuccess if successful.
	*/
	virtual ErrorCode SetName(const WideString &name) = 0;
	
	/**	Get the name of the condition tag set.
		@param name OUT The name for the condition tag set
		@return ErrorCode kSuccess if successful.
	*/
	virtual ErrorCode GetName(WideString &name) = 0;
		
	/**	Set up the condition tag set's list of conditions.
		@param conditions IN A vector of pairs for the condition UID and desired visibility flag.
		@return ErrorCode kSuccess if successful.
		@see IConditionalTextFacade
	*/
	virtual ErrorCode SetConditionList(const IConditionalTextFacade::ConditionSetElementList &conditions) = 0;
	
	/**	Set up the condition tag set's list of conditions using the current visibility state for the specified conditions.
		@param conditions IN A UIDList of the conditions to include in the set.
		@return ErrorCode kSuccess if successful.
	*/
	virtual ErrorCode SetConditionList(const UIDList &conditions) = 0;
	
	/**	Get the condition tag set's list of conditions.
		@param conditions OUT A vector of pairs for the condition UID and associated visibility flag.
		@return ErrorCode kSuccess if successful.
		@see IConditionalTextFacade
	*/
	virtual ErrorCode GetConditionList(IConditionalTextFacade::ConditionSetElementList &conditions) = 0;
	
	/**	Remove a condition from the condition tag set.
		@param conditionUID IN The UID of the condition to be removed.
		@return ErrorCode kSuccess if successfully removed the condition; otherwise, kFailure.
	*/
	virtual ErrorCode RemoveCondition(UID conditionUID) = 0;
	
	/**	Append a condition to the condition tag set's list of conditions.
		@param condition IN A pair containing the condition UID and associated visibility flag.
		@return ErrorCode kSuccess if successful.
		@see IConditionalTextFacade
	*/
	virtual ErrorCode AddCondition(const IConditionalTextFacade::ConditionSetElement &condition) = 0;
};

#endif // __ICONDITIONTAGSET__
