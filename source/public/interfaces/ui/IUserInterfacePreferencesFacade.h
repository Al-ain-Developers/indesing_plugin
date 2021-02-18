//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IUserInterfacePreferencesFacade.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  A high level API for dealing with user interface preferences
//  
//========================================================================================

#pragma once
#ifndef __IUserInterfacePreferencesFacade__
#define __IUserInterfacePreferencesFacade__

// ----- Includes -----
#include "IPMUnknown.h"

#include "AppUIID.h"
#include "IUserInterfacePreferences.h"
#include "IPatientUserPreference.h"
#include "IGrabberPrefs.h"

/**
 Interface used to set new user interface preferences.
 @see IUserInterfacePreferences
*/
namespace Facade
{
	class IUserInterfacePreferencesFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IUSERINTERFACEPREFERENCESFACADE };

		/** Set the toolbox orientation 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetToolboxOrientationPreference(IUserInterfacePreferences::ToolboxState newOrientation) const = 0;

		/** Set the tooltip preference 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetToolTipPreference(IUserInterfacePreferences::TipsState newState) const = 0;

		/** Set the palette drawer preference 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetPaletteDrawerPreference(bool16 drawersStayOpen) const = 0;

		/** Set the auto show hidden panels preference 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetAutoShowHiddenPanels(bool16 autoShow) const = 0;

	/**  Get the current UI Panel auto show hidden panels (when the panel UI is tabbed away) preference
		@return true if hidden panels auto show when mouse is over the the vertical reveal strip
			(if false, the vertical reveal strips are not drawn)
		*/
		virtual bool16 GetAutoShowHiddenPanels() const = 0;

		/**  Return whether this preference can be set.
					Always false on Win since app frame is always on.
					True on Mac.
			@return true if Application frame setting can be changed, false if not
		*/
		virtual bool16 CanChangeUseApplicationFramePreference() const = 0;

		/** Set the UseApplicationFrame preference 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUseApplicationFramePreference(bool16 useApplicationFrame) const = 0;

		/** Get the UseApplicationFrame preference 
		 @return kTrue if application frame is turned on, kFalse if off.
		*/
		virtual bool16 GetUseApplicationFramePreference() const = 0;

		/**  Return whether this preference can be set.
					Always false on Win since app bar is always visible.
					True on Mac when container/frame mode is turned off.
			@see GetUseApplicationFramePreference
			@return true if App Bar show/hide setting can be changed, false if not
		*/
		virtual bool16 CanChangeShowAppBarPreference() const = 0;

		/**  Return the preference for whether the App Bar is showing or not.
					Always true on Win.
			@return true if App Bar is showing, kFalse if hidden
		*/
		virtual bool16 GetShowAppBarPreference() const = 0;

		/**  Set the preference for whether the App Bar shows or not.
					Setting to false has no effect on Windows.
			@param bShowAppBar [IN]: kTrue to show App Bar, kFalse to hide.
		*/
		virtual ErrorCode SetShowAppBarPreference(bool16 bShowAppBar) const = 0;

		/** Return the OpenNewDocumentsInTabs preference 
		 @return bool16 if new documents should open in a tab, kFalse if open as a new floating window.
		*/
		virtual bool16 GetOpenNewDocumentsInTabsPreference() const = 0;

		/** Set the OpenNewDocumentsInTabs preference 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetOpenNewDocumentsInTabsPreference(bool16 openInTabs) const = 0;

		/**  Get the preference for allowing user to drag floating presentations to dock to create tabs.
			@return kTrue if docking is allowed, kFalse if not allowed
		*/
		virtual bool16 GetEnableFloatingPresentationDockingPreference() const = 0;	
		
		/**  Set the preference for allowing user to drag floating presentations to dock to create tabs.
			@param enableDocking [IN]: true to allow dragging to create tabs, false to disallow.
		*/
		virtual ErrorCode SetEnableFloatingPresentationDockingPreference(bool16 enableDocking) const = 0;

		/** Set the current UI "Show Thumbnails Cursor" preference. Users
			may wish to turn this preference off if their computer is connected
			remotely via something like Remote Desktop.
		 @param showThumbnailCursors [IN]: true to draw the Place cursor as a thumbnail of the imported file. 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetShowThumbnailCursorPreference(bool16 showThumbnailCursors) const = 0;

		/** @return Whether or not the place cursor will draw as a thumbnail of the
			imported file.
		*/
		virtual bool16 GetShowThumbnailCursorPreference(void) const = 0;

		/**  Set the current UI "Show Thumbnails Cursor" preference. Users
			may wish to turn this preference off if their computer is connected
			@param showDimensions [IN]: true to the width/height, x/y position or rotation angle of a page item 
				in the cursor while editing a page item.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowObjectDimensionsCursor(bool16 showDimensions) const = 0;

		/**  Get the current UI "Show Object Dimensions" cursor option preference. Users
			may wish to turn this preference off if their computer is connected
			remotely via something like Remote Desktop.
			@return true if the width/height, x/y position or rotation angle of a page item is displayed in the cursor while editing a page item.
		*/
		virtual bool16 GetUIShowObjectDimensionsCursor() const = 0;

		/**  Set the current UI Open Recent Length preference. Users
			may wish to increase or decrease this value to show more or less files in the Open Recent submenu.
		 @param numOfOpenRecentFilesToDisplay [IN]: number of Open Recent files to display.  Must be from 1 to 30. 
		 @return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIOpenRecentLengthPreference(int32 numOfOpenRecentFilesToDisplay) const = 0;

		/**  Get the current UI Open Recent Length preference. Users
			may wish to increase or decrease this value to show more or less files in the Open Recent submenu.
		 @return number of items to show in the Open Recent submenu.
		*/
		virtual int32 GetUIOpenRecentLengthPreference() const = 0;

		/**  Set the current preference for patient user delay. Users
			may wish to turn off or on this setting based on performance or display issues.
			@param milliseconds, delay value in milliseconds. Range kMinPatientUserDelay to kMaxPatientUserDelay.
			@return kSuccess if the preference is successfully changed, else an error code.
			@see IPatientUserPreference.h for typical values and limits.
		*/
		virtual ErrorCode SetUIPatientUserDelay(const int32& milliseconds) const = 0;
		
		/**  Get the current preference for patient user delay. Users
			may wish to turn off or on this setting based on performance or display issues.
			@return int32 delay value in milliseconds.
			@see IPatientUserPreference.h for typical values.
		*/
		virtual int32 GetUIPatientUserDelay(void) const = 0;

		/**  Set the current preference for grabber hand display quality.
			@param grabberPanning, enum value for panning drawing when using grabber hand.
			@return kSuccess if the preference is successfully changed, else an error code.
			@see IGrabberPrefs.h for enum values, kFullDrawPanning, kFastDrawPanning, or kNoDrawPanning.
		*/
		virtual ErrorCode SetUIGrabberPanning(const IGrabberPrefs::PanningType grabberPanning) const = 0;
		
		/**  Get the current preference for grabber hand panning display quality.
			@return IGrabberPrefs::PanningType enum value.
			@see IGrabberPrefs.h for enum values, kFullDrawPanning, kFastDrawPanning, or kNoDrawPanning.
		*/
		virtual IGrabberPrefs::PanningType GetUIGrabberPanning(void) const = 0;

		/**  Set the current preference for showing the content grabber adornment.
			 This adornment allows the pointer tool to select spline content when clicking on the "donut" adornment.
			@param show, kTrue to show the content grabber adornment, kFalse to hide.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowContentGrabber(bool16 show) const = 0;
		
		/**  Get the current preference for showing the content grabber adornment.
			@return bool16 kTrue if grabber should be shown, kFalse if hidden.
		*/
		virtual bool16 GetUIShowContentGrabber(void) const = 0;

		/**  Set the current preference for showing the live corners adornment on splines.
			 This adornment allows the pointer tool to edit corner radii when clicked on.
			@param show, kTrue to show the live corners adornment, kFalse to hide.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowLiveCorners(bool16 show) const = 0;
		
		/**  Get the current preference for showing the live corners adornment on splines.
			@return bool16 kTrue if live corners adornment should be shown, kFalse if hidden.
		*/
		virtual bool16 GetUIShowLiveCorners(void) const = 0;

		/**  Set the current preference for showing the anchor adornment on objects.
			 This adornment allows the pointer tool to click and drag to anchor to text
			 or with shift pressed created an inline.
			@param show, kTrue to show the anchor adornment, kFalse to hide.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowAnchorAdornment(bool16 show) const = 0;

		/**  Get the current preference for showing the anchor adornment on objects.
			@return bool16 kTrue if anchor adornment should be shown, kFalse if hidden.
		*/
		virtual bool16 GetUIShowAnchorAdornment(void) const = 0;


		/**  Set the current preference for showing the master page overlay for a Page Tool selection.
			@param show, kTrue to show the master page overlay, kFalse to hide.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetShowMasterPageOverlay(bool16 show) const = 0;
		
		/**  Get the current preference for showing the master page overlay for a Page Tool selection.
			@return bool16 kTrue if the master page overlay should be shown, kFalse if hidden.
		*/
		virtual bool16 GetShowMasterPageOverlay(void) const = 0;

		
		/**  Set the current preference for whether page items move when a page is repositioned from the UI.
			@param moveItemsWithPagesWithoutOptionKey
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetObjectsMoveWithPage(bool16 moveItemsWithPagesWithoutOptionKey) const = 0;

		/**  Get the current preference for whether page items move when a page is repositioned from the UI.
			@return bool16 returns whether page items move without the option key held down
		*/
		virtual bool16 GetObjectsMoveWithPage(void) const = 0;


		/**  Set the preference for allowing multi-touch gestures.
			@param enableGestures [IN]: true to allow multi-touch gestures, false to disallow.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetEnableMultiTouchGesturesPreference(bool16 enableGestures) const = 0;

		/**  Get the preference for allowing multi-touch gestures.
			@return kTrue if multi-touch gestures are allowed.
		*/
		virtual bool16 GetEnableMultiTouchGesturesPreference() const = 0;
		
		/**  Set the current preference for preventing selection of locked items.
			@param show, kTrue if you can't select an locked item, kFalse if you can select them.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetPreventSelectingLockedItems(bool16 show) const = 0;

		/**  Get the current preference for preventing selection of locked items.
			@return bool16 kTrue if you can't select an locked item, kFalse if you can select them.
		*/
		virtual bool16 GetPreventSelectingLockedItems(void) const = 0;

		/**  Set the preference for enabling highlighting of object frames under selection tool.
			@param enableHighlighting [IN]: true to enable highlighting, false to disable.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetObjectFrameHighlightingPreference(bool16 enableHighlighting) const = 0;

		/**  Get the preference for enabling highlighting of object frames under selection tool.
			@return kTrue if highlighting is enabled.
		*/
		virtual bool16 GetObjectFrameHighlightingPreference() const = 0;
	
		/**  Get the preference for scrolling all document windows when using the hand tool.
			@param scrollAll [IN]: true to enable scrolling across document windows, false to disable.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetScrollAllWindows(bool16 scrollAll) const = 0;

		/**  Get the preference for scrolling all document windows when using the hand tool.
			@return kTrue if scrolling across document windows is enabled.
		*/
		virtual bool16 GetScrollAllWindows() const = 0;

		/**  Get the preference for zooming all document windows when using the zoom tool.
			@param zoomAll [IN]: true to enable zooming across document windows, false to disable.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetZoomAllWindows(bool16 zoomAll) const = 0;

		/**  Get the preference for zooming all document windows when using the zoom tool.
			@return kTrue if zooming across document windows is enabled.
		*/
		virtual bool16 GetZoomAllWindows() const = 0;

		/**  Set the preference for enabling proxy drawing when dragging vector graphics at high quality.
			@param enableDrawProxyOnDrag [IN]: true to enable setting, false to disable.
		*/
		virtual ErrorCode SetEnableDrawProxyOnDrag(bool16 enableDrawProxyOnDrag) = 0;

		/**  Get the preference for enabling proxy drawing when dragging vector graphics at high quality.
			@return kTrue if setting is enabled.
		*/
		virtual bool16 GetEnableDrawProxyOnDrag() const = 0;	

		/**  Set the current preference for showing the ribbon.
			@param show [IN]: kTrue to show the ribbon, kFalse to hide.
			@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowRibbon(bool16 show) = 0;

		/**  Get the current preference for showing the ribbon.
			@return bool16 kTrue if ribbon should be shown, kFalse if hidden.
		*/
		virtual bool16 GetUIShowRibbon(void) const = 0;

		/**  Set the preference for enabling links creation.
			@param enableCreateLinks [IN]: true to enable setting, false to disable.
		*/
		virtual ErrorCode SetEnableCreateLinks(bool16 enableCreateLinks) = 0;

		/**  Get the preference for enabling links creation.
			@return kTrue if setting is enabled.
		*/
		virtual bool16 GetEnableCreateLinks(void) const = 0;

		/**  Set the preference for enabling mapping of styles.
			@param enableCreateLinks [IN]: true to enable setting, false to disable.
		*/
		virtual ErrorCode SetEnableMapStyles(bool16 enableMapStyles) = 0;
		/**  Get the preference for enabling mapping of styles.
			@return kTrue if setting is enabled.
		*/
		virtual bool16 GetEnableMapStyles(void) const = 0;

		/** Set whether to use a custom monitor resolution (kTrue) or determine it from system settings (kFalse).
		 *	@param bUseCustomResolution [IN] kTrue to use the custom setting, kFalse to use system settings
		 *  @return ErrorCode
		 */
		virtual ErrorCode SetUseCustomMonitorResolution(bool16 bUseCustomResolution) const = 0;
		
		/** Get whether to use a custom monitor resolution (kTrue) or determine it from system settings (kFalse).
		 *	@return kTrue to use the custom setting, kFalse to use system settings
		 */
		virtual bool16 GetUseCustomMonitorResolution() const = 0;
		
		/** Set the custom monitor resolution to use when GetUseCustomMonitorResolution() returns kTrue
		 *	@param ppi [IN] The pixels per inch value to use for the monitor resolution
		 *  @return ErrorCode
		 */	
		virtual ErrorCode SetCustomMonitorResolution(const PMReal& ppi) const = 0;
		
		/** Get the custom monitor resolution to use when GetUseCustomMonitorResolution() returns kTrue
		 *	@return The pixels per inch value to use for the monitor resolution
		 */	
		virtual PMReal GetCustomMonitorResolution() const = 0;

		/** Set the Preference for User Interface brightness
		 * @param brightnessVal [IN], this value varies form 0.0 (for Darkest) to 1.0 (for Brightest). 
		 *		Specify 1.0 for Bright, 0.67 for Medium Bright, 0.33 for medium dark, and 0.0 for Dark.
		 *		Any intermediate value between 0.0 and 1.0 can also be specified.
		 */
		virtual ErrorCode SetUIBrightnessPreference(const PMReal brightnessVal) = 0;

		/** Get the Preference Value for User Interface brightness
		 * @return brightness Value
		 */
		virtual PMReal GetUIBrightnessPreference() const = 0;

		/** Set the Pasteboard color Preference value
		 * @param nPrefValue [IN], specify specify the Pasteboard color preference
		 */
		virtual ErrorCode SetPasteboardColorPreference(const int32 nPrefValue) = 0;

		/** Get the Pasteboard color Preference value
		 * @return the Pasteboard color preference Value
		 */
		virtual int32 GetPasteboardColorPreference() const = 0;

		/** Set whether to show "What's New" dialog on startup.
		 * @param showOnStartup [IN], kTrue if "What's New" dialog should be shown on startup, kFalse otherwise.
		 */
		virtual ErrorCode SetShowWhatsNewOnStartup(bool16 showOnStartup) = 0;

		/** Get whether "What's New" dialog is to be shown on startup.
		 * @return bool16 kTrue if "What's New" dialog should be shown on startup, kFalse otherwise.
		 */
		virtual bool16 GetShowWhatsNewOnStartup() const = 0;

		/** Set whether to add the new swatch(created through the new swatch dialog) to CC Libraries automatically
		* @param addSwatchToCCLibraries [IN], if kTrue the new swatch created using the new swatch dialog will be added to CC Libraries automatically.
		*/
		virtual ErrorCode SetAutoAddSwatchToCCLibraries(bool16 addSwatchToCCLibraries) = 0;

		/** Get whether to add the new swatch(created through the new swatch dialog) to CC Libraries automatically
		* @return bool16 if kTrue the new swatch created using the new swatch dialog will be added to CC Libraries automatically.
		*/
		virtual bool16 GetAutoAddSwatchToCCLibraries() const = 0;

		/** Set whether to add the new char style(created through the new char style dialog) to CC Libraries automatically
		* @param addAddCharStyleToCCLibraries [IN], if kTrue the new char style created using the new char style dialog will be added to CC Libraries automatically.
		*/
		virtual ErrorCode SetAutoAddCharStyleToCCLibraries(bool16 addCharStyleToCCLibraries) = 0;

		/** Get whether to add the new char style(created through the new char style dialog) to CC Libraries automatically
		* @return bool16 if kTrue the new char style created using the new char style dialog will be added to CC Libraries automatically.
		*/
		virtual bool16 GetAutoAddCharStyleToCCLibraries() const = 0;

		/** Set whether to add the new para style(created through the new para style dialog) to CC Libraries automatically
		* @param addParaStyleToCCLibraries [IN], if kTrue the new para style created using the new para style dialog will be added to CC Libraries automatically.
		*/
		virtual ErrorCode SetAutoAddParaStyleToCCLibraries(bool16 addParaStyleToCCLibraries) = 0;

		/** Get whether to add the new para style(created through the new para style dialog) to CC Libraries automatically
		* @return bool16 if kTrue the new para style created using the new para style dialog will be added to CC Libraries automatically.
		*/
		virtual bool16 GetAutoAddParaStyleToCCLibraries() const = 0;

		/** Set whether to show CCX Home workspace in no document state
		* @param show [IN], kTrue to show CCX Home workspace in no document state
		*/
		virtual ErrorCode SetShowHomeWorkspace(bool16 show) = 0;

		/** Get whether to show CCX Home workspace in no document state
		* @return bool16 kTrue if CCX Home workspace in no document state, kFalse otherwise.
		*/
		virtual bool16 GetShowHomeWorkspace() const = 0;

		/**  Set the current preference for showing the stock purchase adornment on unlicensed stock images.
		This adornment allows the pointer tool to click and open the license extension and proceed with in app licensing workflow.
		@param show, kTrue to show the stock purchase adornment, kFalse to hide.
		@return kSuccess if the preference is successfully changed, else an error code.
		*/
		virtual ErrorCode SetUIShowStockPurchaseAdornment(bool16 show) const = 0;

		/**   Get the current preference for showing the stock purchase adornment on unlicensed stock images.
		@return bool16 kTrue if stock purchase adornment should be shown, kFalse if hidden.
		*/
		virtual bool16 GetUIShowStockPurchaseAdornment(void) const = 0;
		
		/**   Sets the current preference for showing the tab height of the panel.
		@param tabHeight , kTrue if large panel tab height is to be supported else kFalse.
		@return kSuccess if the Panel Tab Height Preference is successfully changed else return an errorcode.
		*/
		virtual ErrorCode SetPanelTabHeightPreference(bool16 tabHeight) const = 0;

		/**   Gets the current preference for showing the tab height of the panel.
		@return kTrue if large tabs are supported else returns kFalse.
		*/
		virtual bool16 GetPanelTabHeightPreference(void) const = 0;

		/** Set whether to show legacy New Document Dialog
		* @param show [IN], kTrue to show legacy New Document Dialog
		*/
		virtual ErrorCode SetShowLegacyNewDocDlg(bool16 show) = 0;

		/** Get whether to show legacy New Document Dialog
		* @return bool16 kTrue if legacy New Document Dialog, kFalse otherwise.
		*/
		virtual bool16 GetShowLegacyNewDocDlg() const = 0;
	};
}
#endif // __IUserInterfacePreferencesFacade__
