//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IToolToggleBehavior.h $
//  
//  Owner: Paul S.
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
#ifndef __ITOOLTOGGLEBEHAVIOR__
#define __ITOOLTOGGLEBEHAVIOR__

#include "PMTypes.h" 
#include "IPMUnknown.h"
#include "widgetid.h"

/** Interface to allow a plugin to override the toggling of a third party tool to
	the pointer tool. By default, all tools will toggle to the most recent selection
	tool (pointer tool or direct select tool) if the Cmd key is down. By implementing
	this interface for your tool, you can disable this behavior.
*/
class IToolToggleBehavior: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOOLTOGGLEBEHAVIOR };

		/** 
			IsPointerToolToggleEnabled
			Does this tool toggle to the most recent selection tool? 
			@param currentModifiers which modifier keys are currently pressed. @see KBSCModifierDefs.h
			@return True if the tool toggles to the pointer selection tool if the Cmd key is down.
		*/
		virtual bool16 IsPointerToolToggleEnabled(uint16 currentModifiers) const = 0;
};


#endif
