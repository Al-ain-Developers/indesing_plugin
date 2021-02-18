//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IActionManager.h $
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
#ifndef __IActionManager__
#define __IActionManager__


#include "IPMUnknown.h"

#include "ActionID.h"
#include "PMPoint.h"
#include "PMTypes.h"
#include "ActionDefs.h"
#include "TextChar.h"

class IActionComponent;
class IActionStateList;
class PMString;

/**@name Action Area definitions */
//@{
	/** kActionAreaSeparator is used to separate subarea names in action areas (e.g., "KBSCE Edit menu: InCopy: Export: ") */
	const textchar kActionAreaSeparator = kTextChar_Colon ;
//@}

/**	The action manager is the chunk of code that supports both menus and shortcuts. It maintains a list of ActionIDs and the IActionComponents that own them,
	in order to be able to check if a particular action is enabled, and execute that action if it is enabled.
	@see IActionComponent
	@see IActionStateList
	@see IActionRegister
	@see ActionDef.fh
	@see IMenuManager
	@see IShortcutManager
*/
class IActionManager : public IPMUnknown
{
	public:
		/**	Default IID to make UseDefaultIID() work for this interface */
			enum { kDefaultIID = IID_IACTIONMANAGER };
			
		/**	Register a new action with the action manager. This version, which takes a pointer to an action component, is rarely used by client code.
			@param actionComponent The action component boss which will handle enabling/execution of this new action
			@param actionID The action id of the new action. Should be defined in an xxxID.h file.
			@param actionName The name of this action. If this action is added to a menu, this name will be used for the menu item. Ignored unless actionType is kNormalAction.
			@param actionArea A string describing the area for this action. This is used to group actions in the shortcut editor. @see ActionDefs.h for some predefined areas. Ignored unless actionType is kNormalAction.
			@param actionType The type of the action. @see ActionDefs.h
			@param enablingType What kind of enabling this action uses. @see ActionDefs.h . Ignored unless actionType is kNormalAction.
			@param selectionIID The IID this action needs the selection to support. Only meaningful if enablingType includes kDisableIfSelectionDoesNotSupportIID. Ignored unless actionType is kNormalAction.
			@param userEditable Whether or not this action is editable by the user. Currently this controls if the action appears in the Keyboard Shortcut Editor or not. Ignored unless actionType is kNormalAction.
		*/
		virtual void		AddAction( const IActionComponent* actionComponent, const ActionID& actionID, const PMString& actionName, const PMString& actionArea,
										 int16 actionType, uint32 enablingType,	PMIID selectionIID, bool16 userEditable) = 0;

		/**	Register a new action with the action manager. This version, which takes a ClassID for an action component, is often called by an initializer which reads
			ActionDef resources from plugins at first launch.
			@param componentID The action component boss which will handle enabling/execution of this new action
			@param actionID The action id of the new action. Should be defined in an xxxID.h file.
			@param actionName The name of this action. If this action is added to a menu, this name will be used for the menu item. Ignored unless actionType is kNormalAction.
			@param actionArea A string describing the area for this action. This is used to group actions in the shortcut editor. @see ActionDefs.h for some predefined areas. Ignored unless actionType is kNormalAction.
			@param actionType The type of the action. @see ActionDefs.h
			@param enablingType What kind of enabling this action uses. @see ActionDefs.h . Ignored unless actionType is kNormalAction.
			@param selectionIID The IID this action needs the selection to support. Only meaningful if enablingType includes kDisableIfSelectionDoesNotSupportIID. Ignored unless actionType is kNormalAction.
			@param userEditable Whether or not this action is editable by the user. Currently this controls if the action appears in the Keyboard Shortcut Editor or not. Ignored unless actionType is kNormalAction.
		*/
		virtual void		AddAction( ClassID componentID, ActionID actionID, PMString actionName, PMString actionArea, 
										int16 actionType, uint32 enablingType, PMIID selectionIID, bool16 userEditable) = 0;
							
		/** Remove the specified action from the action manager's tables
			@param actionID The action id of the action to remove
			@param actionType The type of the action to remove. @see ActionDefs.h
			@param componentID The action component boss that handled pre- or post-notification for this action. Ignored if actionType is kNormalAction.
		*/
		virtual void		RemoveAction( const ActionID& actionID, int16 actionType = kNormalAction, const ClassID& componentID = kInvalidClass ) = 0;
		
		/** Check how many actions the action manager knows about. */
		virtual int32 GetNumActions() const = 0;
		
		/** Get the nth known ActionID */
		virtual ActionID GetNthAction(int32 index) const = 0;
		
		/** Check if the passed in ActionID is known to the action manager */
		virtual bool16 IsValidAction(const ActionID& actionID) const = 0;
		
		/** Get the action area string for a given action */
		virtual PMString GetActionArea(const ActionID& actionID) const= 0;

		/** Get the action name string for a given action */
		virtual PMString GetActionName(const ActionID& actionID) const= 0;
		
		/** Check if a given action is editable by the user */
		virtual bool16 IsActionUserEditable(const ActionID& actionID) const= 0;

		/** Change the area of an action
			@param actionID is the action to update
			@param actionArea is the new area
		*/
		virtual void UpdateActionArea( const ActionID& actionID, const PMString& actionArea ) = 0 ;

		/** Change the name of an action
			@param actionID is the action to update
			@param actionName is the new name
		*/
		virtual void UpdateActionName( const ActionID& actionID, const PMString& actionName ) = 0 ;

		/**	Function to handle enabling/disabling of actions. For menu actions, called before menu appears.
			@param ac current context for action component should operate on
			@param *listToUpdate list of action states to update
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit. NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		 */
		virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil) = 0;

		/**	Function to handle an action.
			@param ac current context for action component should operate on
			@param actionID action id to handle
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit.  NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		 */
		virtual void PerformAction(IActiveContext* ac, const ActionID& actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil) const = 0;
		
		/** Query the action component that handles a specified action */
		virtual IActionComponent* QueryActionComponent( const ActionID& actionID ) const= 0;

		/** Internal use only */
		virtual bool16 PreStartup(const PMLocaleId& locale) = 0;

		/** Internal use only */
		virtual bool16 PostStartup(const PMLocaleId& locale) = 0;

		/** Internal use only */
		virtual void Shutdown(const PMLocaleId& locale) = 0;
						
#ifdef DEBUG
		typedef enum { enablingInfo, customEnableInfo, nonEditableInfo, allActionInfo, prePostNotifyInfo, actionNameInfo, actionMenuStringInfo } ActionInfoType;
		virtual void DumpActionInfo(ActionInfoType infoType) = 0;
#endif		
};

#endif // __IActionManager__
		
		