//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CActionComponent.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CActionComponent__
#define __CActionComponent__

#include "IActionComponent.h"
#include "HelperInterface.h"

#pragma export on

/** Helper class providing partial implementation of IActionComponent.
*/
class WIDGET_DECL CActionComponent : public IActionComponent
{
	public:
		/** Constructor.
			@param boss object on which the interface being implemented is aggregated
		*/
		CActionComponent(IPMUnknown* boss);
		/** Destructor */
		virtual			~CActionComponent();
				

		/** Called when the action component is asked to update a list of actions to the proper state.
			This method is required to be overridden by subclasses only if there are action components with 
			kCustomEnabling specified.
			The list of actions is intially disabled and unselected, so it only has to be
			changed if this state is not correct. Note that action components are never asked to update
			actions that don't belong to them, or actions they have not specified kCustomEnabling for.
			@param listToUpdate contains the items that client code should update the state for
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit. NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

#ifdef ID_ENABLE_DEBUGGING
		virtual void Register_Debug_Actions();
#endif				
	private:
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __CActionComponent__
		
