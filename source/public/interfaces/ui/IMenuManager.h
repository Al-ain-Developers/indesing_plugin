//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMenuManager.h $
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
#ifndef __IMenuManager__
#define __IMenuManager__

#include "IPMUnknown.h"

#include "ActionID.h"
#include "OMTypes.h"
#include "TextChar.h"

class PMReal;
class PMString;

/**@name Menu definitions */
//@{
	/** kMenuPathSeparator is used to separate submenu names in menu paths (e.g., "Main:&Edit:Prefere&nces:") */
	const textchar kMenuPathSeparator = kTextChar_Colon ;
	/** Append the kMenuSeparatorChar to a menu path (e.g., "Main:&Edit:-") in order to add a menu separator between menu items */
	const textchar kMenuSeparatorChar = kTextChar_HyphenMinus ;
//@}

/** Interface to menu manager. */
class IMenuManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMENUMANAGER };
		
		/**
			Add a menu item.
			
			@param actionID identifier associated with the menu item; kInvalidActionID for a submenu entry
			@param menuPath to add a menu item, pass the full path of the submenu on which to add the menu item (e.g., "Main:&File"),
								the name associated with the actionID param will determine the menu item's name (e.g., kSaveActionID for "&Save");
							to add a submenu entry, append a ":" to the full path of the submenu including the submenu's name 
								(e.g., "Main:&Edit:Prefere&nces:") and pass kInvalidActionID for the actionID param
							to add a separator, append a "-" to the full path of the of the submenu on which to add the separator
								(e.g., "Main:&Edit:-") and pass a valid ActionID for the actionID param (but not one that's registered with the IActionManager)
			@param menuPos the menu position - menu items on the same menu are sorted based on this number; menu items with the same number are sorted alphabetically
			@param isDynamic isDynamic indicates that this menu item requires a call to 'IDynamicMenu::RebuildMenu' before menu enable/display.
			@param isOwnerDraw indicates that this menu item is drawn by the IOwnerDrawItem interface on the action component instead of being drawn by platform menu code
			@param iconPluginID is the pluginID of the icon(if any) associated with the menu item
			@param iconRsrcID is the resource ID of the icon(if any) associated with the menu item
		*/
		virtual void AddMenuItem(ActionID actionID, PMString menuPath, PMReal menuPos, bool16 isDynamic, bool16 isOwnerDraw = kFalse, uint32 iconPluginID = 0, uint32 iconRsrcID = 0) = 0;
								
		/** Deletes all the menu items for this actionID
			@param actionID identifier associated with the menu item
		*/
		virtual void RemoveAllMenusForAction(ActionID actionID) = 0;
		
		/** Deletes the specified menu item - i.e. Pass "Main:&File" and kNewActionID to delete 'New...' from the file menu.
			If you pass a submenu item, it's entry (and associated positioning information) will be removed, but not the menu 
			items on that submenu. As a result the submenu will still appear, but at the bottom of the containing menu.
			@param menuPath the full path name of the menu item
			@param actionID identifier associated with the menu item
		*/
		virtual void RemoveMenuItem(PMString menuPath, ActionID actionID) = 0;

		/** Deletes the specified submenu entry and all of its menu items - i.e. Pass 
			"Main:&File:&New:" to delete the 'New' submenu and its contents from the file menu
			@param menuPath the full path name of the submenu with a ":" appended
		*/
		virtual void RemoveSubmenuAndChildren(PMString menuPath) = 0;

		/** Display and react to user choice of a popup menu.
			@param popupLabel name for the popup menu (key)
			@param whereToPop contains global coordinate to specify where popup should be displayed
			@param mousePoint contains global location of mouse at when mouse was clicked. May be the same as whereToPop.
			@param removeDisabledItems 
			@param widget contains the popup menu, may be nil.
			@param excludeRect contains global coordinate rect, may be nil. For Win Only, popup menu should not overlap the excludeRect. Takes precedence over widget bounds, when provided.
		*/
		virtual void HandlePopupMenu(PMString popupLabel, GSysPoint whereToPop, GSysPoint mousePoint, bool16 removeDisabledItems = kTrue, IPMUnknown* widget = nil, GSysRect* excludeRect = nil) = 0;

		/** Call to find out if the menu is popped up and the user is interacting with the menu.
			@return kTrue if a menu is popped up, kFalse otherwise.
		*/
		virtual bool16 IsMenuUp() const = 0;

		/** For internal use only. 
			Remove icon of menu action id with icon.

			@param actionID identifier associated with the menu item; kInvalidActionID for a submenu entry
			@param menuPath to add a menu item, pass the full path of the submenu on which to add the menu item (e.g., "Main:&File"),
								the name associated with the actionID param will determine the menu item's name (e.g., kSaveActionID for "&Save");
							to add a submenu entry, append a ":" to the full path of the submenu including the submenu's name
								(e.g., "Main:&Edit:Prefere&nces:") and pass kInvalidActionID for the actionID param
							to add a separator, append a "-" to the full path of the of the submenu on which to add the separator
								(e.g., "Main:&Edit:-") and pass a valid ActionID for the actionID param (but not one that's registered with the IActionManager)

		*/
		virtual void RemoveIconOfActionID(ActionID actionID, PMString menuPath) = 0;

#ifdef DEBUG
		typedef enum { positionInfo, rootMenuNames, allMenuNames, allMenuInfo, macMenuIDs} MenuInfoType;
		virtual void DumpMenuInfo(MenuInfoType infoType) const = 0;
#endif		

};

#endif // __IMenuManager__
