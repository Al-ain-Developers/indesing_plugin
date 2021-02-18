//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IBehaviorEventData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IBehaviorEventData_h__
#define __IBehaviorEventData_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"

/** Used to pass in an event parameter to a command
*/
class IBehaviorEventData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIOREVENTDATA };
	
	/** Set the event.
		@param event Should be an enum in kBehaviorEventIDSpace
	*/
	virtual void		SetEvent(const ActionEvent& event) = 0;
	
	/** Return the event.
		@return event is an enum in kBehaviorEventIDSpace
	*/
	virtual ActionEvent	GetEvent() const = 0;
};

#endif // __IBehaviorEventData_h__
