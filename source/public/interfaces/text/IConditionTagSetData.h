//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTagSetData.h $
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
#ifndef __ICONDITIONTAGSETDATA__
#define __ICONDITIONTAGSETDATA__

#include "IPMUnknown.h"
#include "IConditionalTextFacade.h"

#include "ConditionalTextID.h"

#include <vector>

using namespace Facade;

/** 
	Command data interface for the condition visibilities data of a condition set.

	@see kConditionTagSetCreateCmdBoss
	@see kConditionTagSetRedefineCmdBoss
	@see IConditionalTextFacade
*/
class IConditionTagSetData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAGSETDATA };
		
	/** Set the condition tag set data.
		@param conditions IN A vector of pairs for the condition UID and desired visibility flag.
		@see IConditionalTextFacade
	*/
	virtual void SetData(const IConditionalTextFacade::ConditionSetElementList &conditions) = 0;
	
	/** Get the condition tag set data.
		@return A vector of pairs for the condition UIDs and their visibility flags.
		@see IConditionalTextFacade
	*/
	virtual IConditionalTextFacade::ConditionSetElementList GetData() = 0;
};

#endif // __ICONDITIONTAGSETDATA__
