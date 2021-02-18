//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDVOwnerDrawMenu.h $
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
#ifndef __IDVOwnerDrawMenu__
#define __IDVOwnerDrawMenu__

#include "PMTypes.h"
#include "DV_WidgetID.h"
#include "IActionStateList.h"
#include "IGraphicsContext.h"

#include "DVAForwardDeclarations.h"

class IControlView;
class IViewPort;

//========================================================================================
// CLASS IOwnerDrawMenu
//========================================================================================

/** This interface is necessary for OwnerDraw menus.  When an ownerdraw menu is shown, this interface is called to draw the menu.
	It should be placed on the same boss as the IActionComponent for the menu
*/
class IDVOwnerDrawMenu : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDVOWNERDRAWMENU };
							
	// Action states are defined in IActionStateList.h
	// kDisabled_Unselected, kEnabledAction, kSelectedAction, kMultiSelectedAction, kAltSelectedAction
	
	// -----------------------------------------------------------
	/**@name Callbacks to manage Drawing of OwnerDraw menus */
	//@{

	/** 
		This method is called by the Menu Manager code to draw an OwnerDraw menu item.  When called, client should draw into the specified port and rectangle
		@param The IViewPort that you should draw into
		@param The ActionID of the specific menu that is being asked to be drawn.  Only 1 menu item at a time is drawn.  This identifies which menu item to draw.
		@param The rect in which to draw you menu item
		@param kTrue if this menu item has the mouse over it and should be drawn hilited to indicate that it is the curren target menu item.  kFalse otherwise
		@param action state of the menu item.  This is the same as the action states in IActionStateList.h and should be used to determine whether to draw disabled, with a checkmark, etc.  Options are (kDisabled_Unselected, kEnabledAction, kSelectedAction, kMultiSelectedAction, kAltSelectedAction)
	*/
	virtual void DrawMenuItem(IGraphicsContext *oc, ActionID menuActionID, const SysRect& itemRect, bool16 isCurrentlySelectedItem, int16 actionState) = 0;

	/** 
		This method is called by the Menu Manager code to determine the size of the given menu manager.  The height and width returned here will match the height and width of the rectangle given in DrawMenuItem
		@param The ActionID of the specific menu that is being asked to be measured.  Only 1 menu item at a time is measured.  This identifies which menu item to measure.
		@param this an out only parameter.  You should set it to the width of your menu.  This may be nil, so check before setting it
		@param this an out only parameter.  You should set it to the height of your menu.  This may be nil, so check before setting it
	*/
	virtual void MeasureItem(ActionID menuActionID,  uint16* outItemWidth, uint16* outItemHeight) = 0;


	// -----------------------------------------------------------
	/**@name Adding and removing widgets for associated ActionIDs.  Typically, widgets are added to the OwnerDraw menu using these methods and when DrawMenu is called, 
			it will draw the widget that was added for the requested ActionID */
	//@{

	/** 
		Add a widget for a given ActionID.  This is the preferred method for using OwnerDraw Menus.  Widgets are added with AddMenuWidget and associated with an ActionID.
		@param The ActionID of the specific menu item that you are associating with the given widget.
		@param The widget that is being added to the OwnerDraw menus list of widgets and associated actions
	*/
	virtual void AddMenuWidget( ActionID menuActionID,  IControlView* widget ) = 0;
	/** 
		Remove the widget that is associated with the specified action.
		@param The ActionID of the specific menu item whose widget you wish to remove.
		@param When the widget is removed, do you want the UID of the widget deleted?  Typically, you've created the widget for this purpose, so you want to delete the UID when it goes away.
	*/
	virtual void RemoveMenuWidget( ActionID menuActionID, bool16 deleteUID = kTrue ) = 0;
	/** 
		Remove all the widgets that have been added.
		@param When the widgets are removed, do you want the UIDs of the widgets deleted?  Typically, you've created the widgets for this purpose, so you want to delete the UIDs when they go away.
	*/
	virtual void RemoveAllMenuWidgets( bool16 deleteUID = kTrue ) = 0;

	/** Test the Action ID to see if it is one of the actions that this class can render. Override this for components that have a mix of
	    ownerdraw menus and regular menus. If you don't do this, your owner draw code will be called when your regular menu is 
		colorized in the Menus dialog.
		@param actionID the action id you want to test
		@return true if this owner draw class can render the actionID menu.
	*/
	virtual bool16 IsValidActionID(ActionID actionID) = 0;
	
	/** A way to find out what scale the owner drawn view should be drawn at. If using a HIDPI screen this may be greater than 1.
		@return scale to display
	*/
	virtual PMReal GetMenuViewScale() = 0;
	
	/** This is set in the menu manager before calling the owner drawn menu to draw.
		@param scale view is drawn at.
	*/
	virtual void SetMenuViewScale(PMReal scale) = 0;

};

#endif // __IDVOwnerDrawMenu__
