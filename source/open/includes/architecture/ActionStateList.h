//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/ActionStateList.h $
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
#ifndef __ActionStateList__
#define __ActionStateList__

#include "IActionStateList.h"
#include "K2Vector.h"
#include "K2Vector.h"

#pragma export on

class DV_WIDGET_DECL ActionStateList : public IActionStateList 
{
	public:
		ActionStateList();
		~ActionStateList();

		void AddActionID(ActionID id);

		int32 Length() const;
		ActionID GetNthAction(int32 index) const;

		void SetNthActionState(int32 index, int16 state);
		int16 GetNthActionState(int32 index) const;

		void SetNthActionName(int32 index, const PMString& name);
		const PMString& GetNthActionName(int32 index) const;
	private:
		K2Vector<int16> fStateList;
		K2Vector<ActionID> fActionIDList;
		K2Vector<PMString*> fNameList;
		PMString fNullString;
};
#pragma export off

#endif // __ActionStateList__