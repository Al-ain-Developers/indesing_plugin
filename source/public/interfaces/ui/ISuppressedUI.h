//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISuppressedUI.h $
//  
//  Owner: Matt Joss
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
#ifndef __ISuppressedUI__
#define __ISuppressedUI__

#include "AppUIID.h"

class IControlView;
class IDragDropTarget;
class DataObjectIterator;
class IDragDropSource;

/** Interface for suppressing the display or enablement of interface elements
	to allow 3rd parties to customize/disable UI for some clients.  This interface is expected
	to be on the Session boss and all UI elements will check for it there.  The implementation 
	on the session boss is typically a aggregator which forwards calls on to services which 
	of type 'kSuppressedUIService' which also implement this interface.  There is a service 
	implementation that is provided, kSuppressedUIWithXMLFileImpl, which will read in 
	lists of suppressed elements from an XML file.
*/


class ISuppressedUI : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISUPPRESSEDUI };

	// -----------------------------------------------------------
	/**@name Manage workspaces in standard locations */
	//@{

	/** 
		Called by UI code to determine if the specified widget should be disabled
		@param widget the widget in question
		@return kTrue to disable the widget, kFalse if you do not wish to disable the widget
	*/
	virtual bool16			IsWidgetDisabled( const IControlView* widget ) const = 0;

	/** 
		Called by UI code to determine if the specified widget should be hidden
		@param widget the widget in question
		@return kTrue to hide the widget, kFalse if you do not wish to hide the widget
	*/
	virtual bool16			IsWidgetHidden( const IControlView* widget ) const = 0;

	/** 
		Called by UI code to determine if the specified widget should accept a drop.  data and source contain more information about this particular drop.
		You can choose to accept some drops and disable others
		@param target the widget in question
		@param data contains information about the dragdrop action in question
		@param source contains the source of the dragdrop operation
		@return kTrue to disable the drop to this widget, kFalse if you do not wish to disable the drop to this widget
	*/
	virtual bool16			IsDragDropDisabled( const IDragDropTarget* target, DataObjectIterator* data, const IDragDropSource* source ) const = 0;

	/** 
		Called by ActionManager to determine if the specified action should be disabled.  Disabled actions will show up in menus, but will be disabled.
		@param action the action
		@return kTrue to disable the action, kFalse if you do not wish to disable the action
	*/
	virtual bool16			IsActionDisabled( ActionID action ) const = 0;

	/** 
		Called by ActionManager to determine if the specified action should be hidden.  Hidden actions will NOT show up in menus.
		@param action the action
		@return kTrue to hide the action, kFalse if you do not wish to hide the action
	*/
	virtual bool16			IsActionHidden( ActionID action ) const = 0;

	/** 
		Called by MenuManager to determine if the specified menu should be disabled.  This refers to submenus which are menu items that contain a menu
		beneath them.  They have no actionID and are specified by Menu path.  e.g. File > New is a submenu.
		@param untranslatedSubMenuName the This should contain the full menu path in it's untranslated form.  This is the same format used to add submenus
		in MenuDef resource.  e.g. "Main:&Window:PW_Workspace:" is a submenu path for Palette Workspaces
		@return kTrue to disable the submenu, kFalse if you do not wish to disable the submenu
	*/
	virtual bool16			IsSubMenuDisabled( const PMString& untranslatedSubMenuName ) const = 0;

	/** 
		Called by MenuManager to determine if the specified menu should be hidden.  This refers to submenus which are menu items that contain a menu
		beneath them.  They have no actionID and are specified by Menu path.  e.g. File > New is a submenu.
		@param untranslatedSubMenuName the This should contain the full menu path in it's untranslated form.  This is the same format used to add submenus
		in MenuDef resource.  e.g. "Main:&Window:PW_Workspace:" is a submenu path for Palette Workspaces
		@return kTrue to hide the submenu, kFalse if you do not wish to hide the submenu
	*/
	virtual bool16			IsSubMenuHidden( const PMString& untranslatedSubMenuName ) const = 0;

	/** 
		The different variations of Open and Save dialogs in InDesign do not contain InDesign widgets and therefore can't be handled in the same way.
		These are handled specifically by an identifier found in SuppressedUIXMLDefs.h.  You can either Hide all the custom controls or disable individual 
		controls.  Suppressing all controls will not cause the dialog to not show the custom control area.  Suppressing only individual controls will disable them.
		At this point, you cannot hide individual controls.  This method is called by the dialog to determine if it should hide or disable it's custom controls
		@param platformDialogIdentifier an identifier which identifies the dialog asking whether it's custom controls should be hidden
		@return kTrue to hide the custom controls, kFalse if you do not wish to hide the custom controls
	*/
	virtual bool16			IsPlatformDialogControlSuppressed( const PMString& platformDialogIdentifier ) const = 0;

	/** 
		Call Reset() to force the implementations of this interface to recreate a list of items that it would like to suppress.  Since the calls above occur very frequently,
		the implementation needs to respond very quickly and should keep a cache of suppressed items.  When Reset() is called, it should recreate it's
		cache.  For instance, the implementation that reads suppressed items from an XML file will reread the xml file when Reset() is called.
	*/
	virtual void			Reset( ) = 0; // or Initialize()
};

#endif //__ISuppressedUI__
