//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IActionComponent.h $
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
#ifndef __IActionComponent__
#define __IActionComponent__

#include "IPMUnknown.h"
#include "ActionID.h"
#include "IActionManager.h"
#include "PMTypes.h"

class IActionStateList;
class IActiveContext;

/**
	Interface that action components should implement.
*/
class IActionComponent : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IACTIONCOMPONENT };
		
		/** The action component is asked to update a list of actions to the proper state.
			the list of actions is intially disabled and unselected, so it only has to be
			changed if this state is not correct. Note that action components are never asked to update
			actions that don't belong to them, or actions they have not specified kCustomEnabling for.
			@param ac pointer to the active context
			@param listToUpdate contains the items that client code should update the state for. Note that all states begin as disabled unselected.
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known or relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit. NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil) = 0;

		/** The action component should do the requested action. Note this will never be called 
			except when the action is enabled.
			@param ac pointer to the active context
			@param actionID identifies which action this action component should perform
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known or relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit. NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		*/
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil)= 0;

#ifdef ID_ENABLE_DEBUGGING
		/** Called for test menu components only, and only in the debug build. 
		This allows us to provide a simpler way to add something to the test menu.
		*/
		virtual void Register_Debug_Actions() = 0; 
#endif	
};

#endif	// __IActionComponent__
