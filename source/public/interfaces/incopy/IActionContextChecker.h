//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IActionContextChecker.h $
//  
//  Owner: matt ramme
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
#ifndef __IActionContextChecker__
#define __IActionContextChecker__


#include "IPMUnknown.h"

#include "PMString.h"
#include "InCopyCoreID.h"

/**	This interface exists to allow some actions which are usually disabled when a modal dialog is displayed to be 
	enabled in certain cases. Usually the action manager automatically disables all actions which do not specify kEnableEvenDuringDialogs.
	When InCopy is running, it will first look for an IActionContextChecker interface on the current shortcut context, and
	call AllowActionToRun to see if the action should be enabled.
	
	@see IShortcutContext
*/
class IActionContextChecker : public IPMUnknown
{
	public:
		/** Default IID to make UseDefaultIID()) work */
		enum { kDefaultIID = IID_IACTIONCONTEXTCHECKER };

		/** Check if this action should get to run. Gets passed the actionID of the action in question, and it's enabling type. */
		virtual bool16	AllowActionToRun(ActionID actionID, uint32 enablingType) = 0;
};

#endif // __IActionContextChecker__
