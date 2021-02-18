//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPalettePanelUtils.h $
//  
//  Owner: Dave Burnard
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
//  
//  ***Adobe Patent or Adobe Patent Pending Invention Included Within this File***
//  
//========================================================================================

#pragma once
#ifndef __IPalettePanelUtils__
#define __IPalettePanelUtils__

#include "widgetid.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "IWindow.h"

class ICommand ;
class IControlView;
class IPanelControlData ;

/** Utility interface for palette and panel related methods.
	@ingroup ui_dialog
	@ingroup ui_util
*/
class IPalettePanelUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPALETTEPANELUTILS };

	/** QueryParentPalette - equivalent functionality can be found in IPanelMgr */
	/** QueryPaletteWindow - equivalent functionality can be found in IPanelMgr */

	/** GetNumPanels - equivalent functionality can be found in IPaletteMgr */
				
	// Returns the number of panels the tab group containing the specified panel
	virtual int32 GetNumPanelsInTabGroup( IControlView *panel ) = 0;

	/** Create a command to destroy a panel */
	virtual ICommand* CreateDestroyPanelCmd( UID panelUID ) = 0;

	/** Create and schedule a command to destroy a panel */
	virtual ErrorCode ScheduleDestroyPanelCmd( UID panelUID ) = 0;

	/** Create a command to hide a panel (currently works by hiding the palette) */
	virtual ICommand* CreateHidePanelCmd( UID panelUID ) = 0;

	/** Create and schedule a command to hide a panel */
	virtual ErrorCode ScheduleHidePanelCmd( UID panelUID ) = 0;

	/** Get a panel from a widget id. 
			Used mostly by menus/actions that want to do something to a panel (find/update a specific widget).
			
			Note: If the panel is not visible, this method will return nil. 
			This is because the PanelMgr is optimized to purge panels that are not shown,
			so we don't want to hand out pointers to them.
	*/
	virtual IPanelControlData* QueryPanelByWidgetID(WidgetID widgetID) = 0;
	
	/** Switch the panel to it's next detail level, if it has a panel detail controller. */
	virtual void ShowNextDetailLevel(WidgetID panelWidgetID) = 0;
	
	/** Get string corresponding to the panels current detail level, if it has a panel detail controller.
		 	Either "Show Options" or  "Hide Options"
	*/
	virtual PMString GetCurrentOptionString(WidgetID panelWidgetID) = 0;
	
	/** Get the current list box ID in the given panel. Used for Small palette rows.

			NOTE: The GetCurrentListBoxID variants assume a rather simplistic panel organization, requiring that only one listbox in the
			panels entire subview hierarchy be visible at a time. When designing new panels, keep this in mind. Caveat Emptor.

			IMPORTANT NOTE: This method will fail to find the proper listbox if the panel is not shown.
			If you are calling from the panels code, then get it's panel data and call the second variant of this method.
			If you are calling from somewhere else and all you have is a panelID, then call this one, but handle failure gracefully.
			(You should probably call panelMgr->IsPanelWithWidgetIDShown(panelID) first.)

		@param panelID IN which panel
		@param itemWidgetRsrcID OUT returns the rsrcID to use for elements in the current listbox. See IListBoxAttributes::GetItemWidgetID
		@return the widgetID of the list box
	*/
	virtual WidgetID GetCurrentListBoxID(const WidgetID panelID, RsrcID* itemWidgetRsrcID = nil) = 0;
	
	/** Get the current list box ID in the given panel. Used for Small palette rows.

			NOTE: The GetCurrentListBoxID variants assume a rather simplistic panel organization, requiring that only one listbox in the
			panels entire subview hierarchy be visible at a time. When designing new panels, keep this in mind. Caveat Emptor.

		@param panelID IN which panel
		@param itemWidgetRsrcID OUT returns the rsrcID to use for elements in the current listbox. See IListBoxAttributes::GetItemWidgetID
		@return the widgetID of the list box
	*/
	virtual WidgetID GetCurrentListBoxID(const IPanelControlData* panelData, RsrcID* itemWidgetRsrcID = nil) = 0;

	/** Show or hide panel options for panels with panel detail controllers. */
	virtual void ShowHideOptions(WidgetID panelWidgetID) = 0;

	/** Adjust the bbox of the max document window, considering the current palette locations. */
	virtual GSysRect GetMaxDocAreaRectAvoidingPalettes(bool16 onlyConsiderStashed = kFalse) = 0;

	/** resizes the panel view  in palette
	  @param panelView IN panel to resize
	  @param delta IN  delta amount to resize. these are the relative dimensions i.e. delta = (5,-5)
	            represents increase the width by 5 and reduce the height by 5.
	 */
	virtual void ResizePalettePanel(IControlView* panelView, const PMPoint& delta) = 0;
	
};


#endif	// __IPalettePanelUtils__
