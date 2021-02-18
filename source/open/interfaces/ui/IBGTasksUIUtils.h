//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IBGTasksUIUtils.h $
//  
//  Owner: Bernd Paradies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IBGTasksUIUtils__
#define __IBGTasksUIUtils__

#include "AppUIID.h"
#include "IPMUnknown.h"
#include "PMString.h"
#include "UIDRef.h"
/** This provides some utility routines commonly used by menu code.
		i.e. Utils<IBGTasksUIUtils>()->ShowDocActionWarningAboutBGTasks( ... , kCloseActionID, ) ;
*/

class IBGTasksUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBGTASKSUIUTILS};


	typedef enum
	{
		kProcessCmd = 0,
		kAbortCmd
	}UserBGAction;

	virtual UserBGAction ShowDocActionWarningAboutBGTasks(const UIDRef& item, const ActionID& action, UIFlags uiFlags) = 0;
	virtual UserBGAction  ShowCloseAllAndQuitWarningAboutBGTasks(UIFlags uiFlags) = 0;
};

#endif	// __IBGTasksUIUtils__
