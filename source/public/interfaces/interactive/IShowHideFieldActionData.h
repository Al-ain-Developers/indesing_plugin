//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IShowHideFieldActionData.h $
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
#ifndef __IShowHideFieldActionData_h__
#define __IShowHideFieldActionData_h__

#include "IBehaviorData.h"
#include "BehaviorID.h"
#include "K2Vector.h"
#include "K2Pair.h"

//========================================================================================
// CLASS IShowHideFieldActionData
//========================================================================================

/** Data interface for Show Hide Field Behavior
	@see INamedPageItemList (for a way of getting candidates for SetFields()
*/
class IShowHideFieldActionData : public IBehaviorData
{
public:
	typedef int32 Action;
	enum ActionConstants { kHide = 0, kShow, kNone };
	
	/** Set the fields to show or hide
		@param fields a list of fields to show or hide.  First item in pair is UID for field,
				second is whether to show, hide or do nothing to the the field.
	*/
	virtual void							SetFields(const K2Vector< K2Pair<UID, Action> >& fields) = 0;

	/** Get the fields to show or hide
		@return A list of fields to show or hide.  First item in pair is UID for field,
				second is whether to show, hide or do nothing to the the field.
	*/
	virtual K2Vector< K2Pair<UID, Action> >	GetFields() const = 0;
};

#endif // __IShowHideFieldActionData_h__
