//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelMgr.h $
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
//========================================================================================

#pragma once
#ifndef __IPanelMgr__
#define __IPanelMgr__

#include "PMTypes.h"
#include "PMString.h"
#include "ShuksanID.h"
#include "AppUIID.h"

#include "PaletteRef.h"

class IResourceAccess;
class IControlView;

//========================================================================================
// CLASS IPanelMgr
//========================================================================================

/**
	Interface representing the Panel manager, which holds a collection of panels, and provides access to those panels.
	A panel (in this context) is the topmost InDesign boss object that users may think of as a palette, such as the stroke panel.
	Above the panel are various objects that act as containers to group panels together in various ways. These are represented by
	PaletteRef objects. @see PaletteRef.h and @see PaletteRefUtils.h for more information about how to interact with these
	containing objects.
*/
class IPanelMgr : public IPMUnknown
{
 public:
	enum { kDefaultIID = IID_IPANELMGR };
	
 	virtual void			Startup() = 0;
 	virtual void			ShutDown() = 0;
 	
	/** Create a panel without adding it to the Panel manager.

		@param localeId IN
		@param panelID IN resource id of the panel to be created
		@param pluginID IN plugin id of plugin that contains the panel resource
		@return control view of the new panel. This has been AddRef'ed, so caller must release it.
		*/
	virtual IControlView* 	CreatePanel(const PMLocaleId& localeId,  RsrcID panelID, const PluginID& pluginID) = 0;
			
	/** Add an already created and loaded panel to the Panel manager.
		
		@param paletteType IN which kind of palette this panel goes in. Usually one of (kTabPanelContainerType | kToolbarType | kControlBarType)
		@param panel IN the panel to be added to the Panel manager. PanelMgr will AddRef the panel, and not release until app shutdown.
		@param isResizable IN indicates if the panel should have a resize box.
		@param panelName IN name of the panel (used as menu name in window menu), or empty string if altMenu is used
		@param actionID IN the action id to associate with the panel
		@param altMenu IN full path of panel menu if it appears somewhere other than the window menu
		@param altPos IN menu position to go along with altMenu
		@param scriptID IN which script object to use for this panel
		@param paletteIconPluginID IN plugin id for palette icon
		@param paletteIconRsrcID IN resource id for palette icon
		*/
		// similar to old AdoptPanel
	virtual void			RegisterPanel(PaletteRefType paletteType, IControlView* panel,  bool16 isResizable, const PMString& panelName, ActionID actionID, const PMString& altMenu, PMReal altPos, const ScriptID& scriptID, PluginID paletteIconPluginID, RsrcID paletteIconRsrcID) = 0;
	
	
	/** Move a panel to a palette (removing it from it's current location). See PaletteRefUtils for more variations on this theme.
		
		@param parentPalette IN destination palette window. For a regular tabbed palette, this is expected to be a tabgroup.
		@param panel IN the panel to be moved
		*/
	virtual void			MovePanel(PaletteRef parentPalette, IControlView* panel) = 0;
	

	/** Remove a panel from its palette and destroy it. Typically invoked through kDestroyPanelCmdBoss

		@param panelUID IN UID for the panel to be  destroyed
		@precondition Caller must not be holding a reference to the panel.
	*/
	virtual void			DestroyPanel(const UID& panelUID) = 0;
	
	/** Get a panel by its widgetId or actionId. 

		You can use IsPanelWithWidgetIDShown or DoesPanelExist for related info.

		@param widgetId IN widgetID of the desired panel
		@return the desired panel
	*/
	virtual IControlView*	GetPanelFromWidgetID(const WidgetID& widgetId) const = 0;
	virtual IControlView*	GetPanelFromActionID(const ActionID& actionId) const = 0;

	/** Get a panel by its widgetId or actionId. 
			If the panel is not currently visible, this will return nil.
			You can use IsPanelWithWidgetIDShown or DoesPanelExist for related info.
			It is not safe to hand out pointers to panels that are not shown, PanelMgr may purge them and their contents

		@param widgetId IN widgetID of the desired panel
		@return the desired panel
	*/
	virtual IControlView*	GetVisiblePanel(const WidgetID& widgetId) const = 0;
	virtual IControlView*	GetVisiblePanelFromActionID(const ActionID& actionId) const = 0;

	/** Does the panel manager know about a specific panel. 

		@param widgetId IN widgetID of the desired panel
		@return does the panel exist
	*/
	virtual bool16	DoesPanelExist(const WidgetID& widgetId) const = 0;
	virtual bool16	DoesPanelExistFromActionID(const ActionID& actionId) const = 0;

	/** Show a panel. This may cause one or more containing PaletteRef objects to show as well. Calling this should make the panel appear onscreen.

		@param id IN actionID of the panel
		@param giveKeyFocus IN give key focus to panel
	*/
	virtual void			ShowPanelByMenuID(const ActionID& id, bool16 giveKeyFocus = kTrue) = 0;
	/** Show a panel. This may cause one or more containing PaletteRef objects to show as well. Calling this should make the panel appear onscreen.

		@param widgetId IN widgetId of the panel
		@param giveKeyFocus IN give key focus to panel
	*/
	virtual void			ShowPanelByWidgetID(const WidgetID& widgetId, bool16 giveKeyFocus = kTrue) = 0;


	/** Hide a panel. May also hide containing PaletteRef objects, depending on their contents.
		@param id IN actionID of the panel
	*/
	virtual void			HidePanelByMenuID(const ActionID& id) = 0;
	/** Hide a panel (by hiding the palette that contains the panel).
		@param widgetId IN widgetId of the panel
	*/
	virtual void			HidePanelByWidgetID(const WidgetID& widgetId) = 0;

	/** Is the panel and its palette shown.
			Note: Will return kFalse for a minimized palette (panel's control view is hidden in this case).
			Use IsPanelWithMenuIDVisible instead if you need to know if it's on the screen at all.

		@param id IN actionID of the panel
		@return is the panel actually showing on screen
	*/
	virtual bool16			IsPanelWithMenuIDShown(const ActionID& id) const = 0;
	virtual bool16			IsPanelWithWidgetIDShown(const WidgetID& widgetId) const = 0;

	/** Are these panels visible(and not mostly covered by some other window. The version that takes a list is more efficient if you need to ask about several panels at once.

		@param inActionList IN actionIDs of the panels
		@param outMostlyVisibleList OUT bools indicating the mostlyvisible state of the panels.
	*/
	virtual void			ArePanelsWithMenuIDMostlyVisible(const K2Vector<ActionID> &  inActionList, K2Vector<bool16>& outMostlyVisibleList) const = 0;
	/** Is the panel visible onscreen (OK if panel is collapsed or obscured).

		@param id IN actionID of the panel
		@return true only if panel is less then 50% obscured by other palettes
	*/
	virtual bool16			IsPanelWithMenuIDMostlyVisible(const ActionID& id) const = 0;
		
#ifdef ID_DEPRECATED
/** @see GetPanelMenuName or PaletteRefUtils::GetPaletteLabel */

	/** Get the menu string associated with a panel.
		Note: Renamed for clarity in CS4, this has always returned the menu item name rather than the panel's name.
		
	*/
	virtual PMString		GetPanelName(const ActionID& id) const {return GetPanelMenuName(id);}	//Deprecated. 
#endif

	/** Get/Set the menu string associated with a panel. */
	virtual PMString		GetPanelMenuName(const ActionID& id) const = 0;
	virtual void			SetPanelMenuName(const ActionID& id, const PMString& menustr) = 0;

	/** Query for the panel based on it's palette container. Should only pass in the immediate parent of a panel, such as a kToolbarType, kControlBarType, or kTabPanelContainerType */
	virtual IControlView* GetPanelFromPaletteContainer(PaletteRef palette) const = 0;		
	
	/** Query for the PaletteRef holding a panel. @see PaletteRefUtils.h for tips on manipulating the PaletteRef object hierarchy. 
		For regular tabbed palettes, this should return an object of type kTabPanelContainerType. Controlbars should return an object of type kControlBarType,
		and toolbars should return an object of type kToolbarType.
	*/
	virtual PaletteRef	 GetPaletteRefContainingPanel( const IPMUnknown* panel ) const = 0;	
	
	/** Return the entries in the panel list */
	virtual uint32			GetPanelCount() const = 0;
	virtual bool16			GetNthPanelInfo(uint32 index, UID& panelUID, ActionID* actionID = nil, WidgetID* widgetID = nil, PMString* panelName = nil, ScriptID* scriptID = nil) const = 0;
	
	/** 	Set if the panel is resizable. Resizable panels have a resize widget in the bottom right corner to enable the user to drag resize them. Most panels are either resizable or not all the time, but a few
		have different modes, some of which are resizable, and some of which are not. This provides a way to switch between being a resizable panel and not.
		@param widgetId IN widgetId of the panel
		@param resizable is the panel resizable
	*/
	virtual void			SetPanelResizabilityByWidgetID(const WidgetID& widgetId, bool16 isResizable) = 0;

	/** Is the panel resizable. Resizable panels have a resize widget in the bottom right corner to enable the user to drag resize them.
		@param widgetId IN widgetId of the panel
		@return is the panel resizable
	*/
	virtual bool16			IsPanelWithWidgetIDResizable(const WidgetID& widgetId) const = 0;
	
	/** Resize the parent palette of the given panel to accomodate the panels new size. Usually called internally by the panelmgr. This API may be removed in the future.
	*/
	virtual void			FitPaletteToPanel(const IControlView* panel) = 0;

	/** Fixup the the origin of a panel used in a toolbar or controlbar. (Called by framework. Client code should not need to call this.)
	*/
	virtual void			FixupPanelOrigin(IControlView* panel, PaletteRef parentPalette) const = 0;

	/** Add a popup menu to the panel and set its name. Pass the empty string to remove a popup menu from the panel.
		@param panel IN the panel
		@param popupMenuName IN the name of the popup menu
	*/
	virtual void			SetPanelPopupMenuName( IControlView* panel, const PMString& popupMenuName ) = 0 ;

	/** Retrieve the current popup menu name, if any, from the panel
		@param panel IN the panel
		@return the name of the popup menu
	*/
	virtual PMString		GetPanelPopupMenuName( IControlView* panel ) const = 0 ;
  #ifdef MACINTOSH
	/** MAC OS X only: While a menu (main, popup or dropdown) is open, view system updates are not processed. 
		This can pose a problem for dynamically updated panels, for example, views based on FlashPlayer widgets. 
		Such a view can request that it be redrawn periodically using this API. 
	 */
	virtual void			AddViewForRedrawingWhileAMenuIsOpen(IControlView* view) = 0;
	virtual void			RemoveViewForRedrawingWhileAMenuIsOpen(IControlView* view) = 0;
  #endif
	virtual IControlView*	GetPanelFromPanelName(const PMString& panelName) const = 0;

	/** for_internal_use_only
		To log any open/close panel usage.	
	*/
	virtual void			UsageTracking_PanelClosed(const PaletteRef& paletteRef) const = 0;

	/** for_internal_use_only
		To log any open/close panel usage.
	*/
	virtual void				LogPanelUsage() const = 0;
};

#endif
