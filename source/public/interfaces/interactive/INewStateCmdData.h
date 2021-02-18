//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/INewStateCmdData.h $
//  
//  Owner: Tim Wright
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
#ifndef __INewStateCmdData_h__
#define __INewStateCmdData_h__

#include "IPMUnknown.h"
#include "FormFieldID.h"

/** Command parameters for the NewStateCmd command
*/
class INewStateCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INEWSTATECMDDATA };

	enum NamePolicy {
	   kUseDefaultName,
	   kUseDuplicateName,
	   kBaseNameOnString,
	   kDoNotName
	};

	/** Set the policy for naming the new state.
		@param inNamePolicy the policy to use when determining the state name.
	*/
	virtual void SetNamePolicy(NamePolicy inNamePolicy) = 0;

	/** Get the policy for naming the new state.
		@return the policy for naming the new state
	*/
	virtual NamePolicy GetNamePolicy() const = 0;

	/** Set the string to base the new state's name on. This string will be made unique
		within the apperarnce list of the object that we are adding a state to.
		This string is only used if the name policy is kBaseNameOnString.
		@param inString the string to use as the name of the state
	*/
	virtual void SetNameString(const PMString& inString) = 0;

	/** Set the string to base the new state's name on.
		@return the string that the new state's name will be based on.
	*/
	virtual PMString GetNameString() const = 0;

	/** Set where in the state-order the state should be created.
		@param inPosition the position to insert the state at (IAppearanceList::kLastInOrder is acceptable.)
	*/
	virtual void SetPosition(int32 inPosition) = 0;

	/** Get the position that the state will be inserted in the state-order.
		@return the position
	*/
	virtual int32 GetPosition() const = 0;

};

//=============================================================================

#endif // __INewStateCmdData_h__

//  INewStateCmdData.h.
