//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IUserInterfacePreferences.h $
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
#ifndef __IUserInterfacePreferences__
#define __IUserInterfacePreferences__

#include "IPMUnknown.h"
#include "AppUIID.h"

/** Interface responsible for maintaining user interface preferences.
*/
class IUserInterfacePreferences : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IUSERINTERFACEPREFERENCES };
	/** ToolboxState returned by GetToolboxOrientation(). */
	enum ToolboxState {
		/** kTallSkinny is the single column toolbox. */
		kTallSkinny = 0,
		/** kTallRegular is the default 2 column toolbox. */
		kTallRegular,
		/** kWideSkinny is the single row toolbox. */
		kWideSkinny
		};


	/**  Get the current toolbox preference
		@return current toolbox preference
	*/
	virtual ToolboxState GetToolboxOrientation() const = 0;
	
	/** Set the toolbox preference
		@param newOrientation [IN]: toolbox orientation
	*/
	virtual void SetToolboxOrientation(ToolboxState newOrientation) = 0;

	enum TipsState {
		/** kNoTips indicates that tips are disabled. */
		kNoTips = 0, 
		/** kNormalTips indicates that tips are on, default time delay. */
		kNormalTips, 
		/** kSlowTips indicates that tips are on, longer time delay. */
		kSlowTips, 
		/** kFastTips indicates that tips are on, shorter time delay. */
		kFastTips
		};
	
	
	/**  Get the current tips preference
		@return current tips preference
	*/
	virtual TipsState GetTipsState() const = 0;
		
	/** Set the tips preference 
		@param newState [IN]: whether or not and how tips are to be displayed
	*/
	virtual void SetTipsState(TipsState newState) = 0;

	/**  Get the current UI Palette drawer persistence preference
		@return true if palette drawers stay open
	*/
	virtual bool16 GetUIPaletteDrawersStayOpen() const = 0;
	
	/**  Set the current UI Palette drawer persistence preference
		@param drawersStayOpen [IN]: true to make palette drawers stay open.
	*/
	virtual void SetUIPaletteDrawersStayOpen(bool16 drawersStayOpen) = 0;

	/**  Get the current UI Panel auto show hidden panels (when the panel UI is tabbed away) preference
		@return true if hidden panels auto show when mouse is over the the vertical reveal strip
			(if false, the vertical reveal strips are not drawn)
	*/
	virtual bool16 GetUIAutoShowHiddenPanels() const = 0;
	
	/**  Set the current UI Panel auto show preference
		@param autoReveal [IN]: true to make hidden panels auto reveal.
	*/
	virtual void SetUIAutoShowHiddenPanels(bool16 autoShow) = 0;

	/**  Return the preference for whether the ApplicationContainer functions as an ApplicationFrame.
				Always true on Win.
		@return true if ApplicationContainer functions as an ApplicationFrame
	*/
	virtual bool16 GetUseApplicationContainerAsAppFrame() const = 0;
	
	/**  Set the preference for whether the ApplicationContainer functions as an ApplicationFrame.
				Setting to false has no effect on Windows.
		@param iWantToLiveInABox [IN]: true to make ApplicationContainer function as an ApplicationFrame. The horror...
	*/
	virtual void SetUseApplicationContainerAsAppFrame(bool16 iWantToLiveInABox ) = 0;

	/**  Return the preference for whether the App Bar is showing or not.
				Always true on Win.
		@return kTrue if App Bar is showing, kFalse if hidden
	*/
	virtual bool16 GetShowAppBar() const = 0;
	
	/**  Set the preference for whether the App Bar shows or not.
				Setting to false has no effect on Windows.
		@param bShowAppBar [IN]: kTrue to show App Bar, kFalse to hide.
	*/
	virtual void SetShowAppBar(bool16 bShowAppBar) = 0;

	/**  Get the preference for where to put a newly opened document presentation.
		@return true if a new document tab should be created in the active context, or false if a new floating document window should be opened.
	*/
	virtual bool16 GetNewPresentationsAppearAsNewTabInActiveContext() const = 0;
	
	/**  Set the preference for where to put a newly opened document presentation.
		@param drawersStayOpen [IN]: true to make palette drawers stay open.
	*/
	virtual void SetNewDocumentPresentationsAppearAsNewTabInActiveContext(bool16 createNewDocumentTabs ) = 0;

	/**  Get the current UI preference for allowing user to drag floating presentations to dock to create tabs.
		@return kTrue if docking is allowed, kFalse if not allowed
	*/
	virtual bool16 GetEnableFloatingPresentationDocking() const = 0;	

	/**  Set the current UI preference for allowing user to drag floating presentations to dock to create tabs.
		@param enableDocking [IN]: true to allow dragging to create tabs, false to disallow.
	*/
	virtual void SetEnableFloatingPresentationDocking(bool16 enableDocking) = 0;

	/**  Get the current UI "Show Thumbnails Cursor" preference. Users
		may wish to turn this preference off if their computer is connected
		remotely via something like Remote Desktop.
		@return true if the Place cursor draws as a thumbnail of the imported file.
	*/
	virtual bool16 GetUIShowThumbnailCursor() const = 0;

	/**  Set the current UI "Show Thumbnails Cursor" preference. Users
		may wish to turn this preference off if their computer is connected
		@param showThumbnails [IN]: true to draw the Place cursor as a thumbnail of the imported file. 
	*/
	virtual void SetUIShowThumbnailCursor(bool16 showThumbnails) = 0;

	/**  Get the current UI "Show Object Dimensions" cursor option preference. Users
		may wish to turn this preference off if their computer is connected
		remotely via something like Remote Desktop.
		@return true if the width/height, x/y position or rotation angle of a page item is displayed in the cursor while editing a page item.
	*/
	virtual bool16 GetUIShowObjectDimensionsCursor() const = 0;

	/**  Set the current UI "Show Thumbnails Cursor" preference. Users
		may wish to turn this preference off if their computer is connected
		@param showDimensions [IN]: true to the width/height, x/y position or rotation angle of a page item 
			in the cursor while editing a page item.
	*/
	virtual void SetUIShowObjectDimensionsCursor(bool16 showDimensions) = 0;

	/**  Get the current UI Open Recent Length preference. Users
		may wish to increase or decrease this value to show more or less files in the Open Recent submenu.
		@return number of items to show in the Open Recent submenu.
	*/

	virtual int32 GetUIOpenRecentLength() const = 0;

	/**  Set the current UI Open Recent Length preference. Users
		may wish to increase or decrease this value to show more or less files in the Open Recent submenu.
		@param numOfOpenRecentFilesToDisplay [IN]: number of Open Recent files to display.  Must be from 1 to 30.
	*/
	virtual void SetUIOpenRecentLength(int32 numOfOpenRecentFilesToDisplay) = 0;

	/**  Get the current preference for showing the content grabber adornment.
		@return bool16 kTrue if grabber should be shown, kFalse if hidden.
	*/
	virtual bool16 GetUIShowContentGrabber(void) const = 0;

	/**  Set the current preference for showing the content grabber adornment.
		 This adornment allows the pointer tool to select spline content when clicking on the "donut" adornment.
		@param show, kTrue to show the content grabber adornment, kFalse to hide.
	*/
	virtual void SetUIShowContentGrabber(bool16 show) = 0;
		
	/**  Get the current preference for showing the live corners adornment on splines.
		@return bool16 kTrue if live corners adornment should be shown, kFalse if hidden.
	*/
	virtual bool16 GetUIShowLiveCorners(void) const = 0;

	/**  Set the current preference for showing the live corners adornment on splines.
		 This adornment allows the pointer tool to edit corner radii when clicked on.
		@param show, kTrue to show the live corners adornment, kFalse to hide.
	*/
	virtual void SetUIShowLiveCorners(bool16 show) = 0;

	/**  Get the current preference for showing the anchor adornment on objects.
		@return bool16 kTrue if anchor adornment should be shown, kFalse if hidden.
	*/
	virtual bool16 GetUIShowAnchorAdornment(void) const = 0;

	/**  Set the current preference for showing the anchor adornment on objects.
		 This adornment allows the pointer tool to click and drag to anchor to text
		 or with shift pressed created an inline.
		@param show, kTrue to show the anchor adornment, kFalse to hide.
	*/
	virtual void SetUIShowAnchorAdornment(bool16 show) = 0;


	/**  Get the current preference for showing the master page overlay for a Page Tool selection.
		@return bool16 kTrue if master page overlay should be shown, kFalse if hidden.
	*/
	virtual bool16 GetShowMasterPageOverlay(void) const = 0;

	/**  Set the current preference for showing the master page overlay for a Page Tool selection.
		@param show, kTrue to show the master page overlay, kFalse to hide.
	*/
	virtual void SetShowMasterPageOverlay(bool16 show) = 0;

		
	/**  Get the current preference for whether page items move when a page is repositioned from the UI.
		@return bool16 returns whether page items move without the option key held down
	*/
	virtual bool16 GetObjectsMoveWithPage(void) const = 0;

	/**  Set the current preference for whether page items move when a page is repositioned from the UI.
		@param moveItemsWithPagesWithoutOptionKey
	*/
	virtual void SetObjectsMoveWithPage(bool16 moveItemsWithPagesWithoutOptionKey) = 0;



	/**  Get the preference for allowing multi-touch gestures.
		@return kTrue if multi-touch gestures are allowed.
	*/
	virtual bool16 GetEnableMultiTouchGestures() const = 0;

	/**  Set the preference for allowing multi-touch gestures.
		@param enableGestures [IN]: true to allow multi-touch gestures, false to disallow.
	*/
	virtual void SetEnableMultiTouchGestures(bool16 enableGestures) = 0;
		
	/**  Get the current preference for preventing selection of locked items.
		@return bool16 kTrue if you can't select an locked item, kFalse if you can select them.
		*/
	virtual bool16 GetPreventSelectingLockedItems(void) const = 0;

	/**  Set the current preference for preventing selection of locked items.
		@param show, kTrue if you can't select an locked item, kFalse if you can select them.
	*/
	virtual void SetPreventSelectingLockedItems(bool16 show) = 0;

	/**  Get the preference for enabling highlighting of object frames under selection tool.
		@return kTrue if highlighting is enabled.
	*/
	virtual bool16 GetObjectFrameHighlighting() const = 0;

	/**  Set the preference for enabling highlighting of object frames under selection tool.
		@param enableHighlighting [IN]: true to enable highlighting, false to disable.
	*/
	virtual void SetObjectFrameHighlighting(bool16 enableHighlighting) = 0;

	/**  Get the preference for scrolling all document windows when using the hand tool.
		@return kTrue if scrolling across document windows is enabled.
	*/
	virtual bool16 GetScrollAllWindows() const = 0;

	/**  Get the preference for scrolling all document windows when using the hand tool.
		@param scrollAll [IN]: true to enable scrolling across document windows, false to disable.
	*/
	virtual void SetScrollAllWindows(bool16 scrollAll) = 0;

	/**  Get the preference for zooming all document windows when using the zoom tool.
		@return kTrue if zooming across document windows is enabled.
	*/
	virtual bool16 GetZoomAllWindows() const = 0;

	/**  Get the preference for zooming all document windows when using the zoom tool.
		@param zoomAll [IN]: true to enable zooming across document windows, false to disable.
	*/
	virtual void SetZoomAllWindows(bool16 zoomAll) = 0;

	/**  Get the preference for enabling proxy drawing when dragging vector graphics at high quality.
		@return kTrue if setting is enabled.
	*/
	virtual bool16 GetEnableDrawProxyOnDrag() const = 0;

	/**  Set the preference for enabling proxy drawing when dragging vector graphics at high quality.
		@param enableDrawProxyOnDrag [IN]: true to enable setting, false to disable.
	*/
	virtual void SetEnableDrawProxyOnDrag(bool16 enableDrawProxyOnDrag) = 0;

	/**  Get the current preference for showing the ribbon.
	@return bool16 kTrue if ribbon should be shown, kFalse if hidden.
	*/
	virtual bool16 GetUIShowRibbon(void) const = 0;

	/**  Set the current preference for showing the ribbon.
	@param show, kTrue to show the ribbon, kFalse to hide.
	@return kSuccess if the preference is successfully changed, else an error code.
	*/
	virtual void SetUIShowRibbon(bool16 show) = 0;

	/**  Get the current preference for enabling the creation of links.
	@return bool16 kTrue if link creation is enabled, kFalse if hidden.
	*/
	virtual bool16 GetEnableCreateLinks(void) const	= 0;

	/**  Set the current preference for enabling the creation of links.
	@param show, kTrue to enable the link creation, kFalse to hide.
	@return kSuccess if the preference is successfully changed, else an error code.
	*/
	virtual void SetEnableCreateLinks(bool16 enableCreateLinks) = 0;

	/**  Get the current preference for enabling the mapping of style.
	@return bool16 kTrue if mapping of styles is enabled, kFalse if hidden.
	*/
	virtual bool16 GetEnableMapStyles(void) const = 0;

	/**  Set the current preference for enabling the mapping of style.
	@param show, kTrue to enable the mapping of styles, kFalse to hide.
	@return kSuccess if the preference is successfully changed, else an error code.
	*/
	virtual void SetEnableMapStyles(bool16 enableMapStyles) = 0;

	/** Set whether to use a custom monitor resolution (kTrue) or determine it from system settings (kFalse).
	 *	@param bUseCustomResolution [IN] kTrue to use the custom setting, kFalse to use system settings
	 */
	virtual void SetUseCustomMonitorResolution(bool16 bUseCustomResolution) = 0;

	/** Get whether to use a custom monitor resolution (kTrue) or determine it from system settings (kFalse).
	 *	@return kTrue to use the custom setting, kFalse to use system settings
	 */
	virtual bool16 GetUseCustomMonitorResolution() const = 0;
	
	/** Set the custom monitor resolution to use when GetUseCustomMonitorResolution() returns kTrue
	 *	@param ppi [IN] The pixels per inch value to use for the monitor resolution
	 */	
	virtual void SetCustomMonitorResolution(const PMReal& ppi) = 0;

	/** Get the custom monitor resolution to use when GetUseCustomMonitorResolution() returns kTrue
	 *	@return The pixels per inch value to use for the monitor resolution
	 */	
	virtual PMReal GetCustomMonitorResolution() const = 0;

	enum UIBrightnessPreference {
		/** Bright UI, 100% brightness. */
		kBrightUI = 0,
		/** Medium Bright UI, 67% brightness. */
		kMediumBrightUI,
		/** Medium Dark UI, 33% brightness. */
		kMediumDarkUI,
		/** Dark UI, 0% brightness. */
		kDarkUI,
		/** Custom Dark UI, user defined brightness  */
		kCustomUI,
	};

	static PMReal UIBrightnessPreferenceValue[];

	/** Set the Preference for User Interface brightness
	 * @param brightnessVal [IN], this value varies form 0.0 (for Darkest) to 1.0 (for Brightest). 
	 *		Specify 1.0 for Bright, 0.67 for Medium Bright, 0.33 for medium dark, and 0.0 for Dark.
	 *		Any intermediate value between 0.0 and 1.0 can also be specified.
	 */
	virtual void SetUIBrightnessPreference(const PMReal brightnessVal) = 0;

	/** Get the Preference Value for User Interface brightness
	 * @return brightness Value
	 */
	virtual PMReal GetUIBrightnessPreference() const = 0;

	enum PasteboardColorPreference {
		/** White Colored Pasteboard */
		kPasteboardWhiteColored = 0,
		/** Theme Colored Pasteboard*/
		kPasteboardThemeColored,
	};

	/** Set the Pasteboard color Preference value
	 * @param nPrefValue [IN], specify the paper color preference
	 */
	virtual void SetPasteboardColorPreference(const int32 nPrefValue) = 0;

	/** Get the Pasteboard color Preference value
	 * @return the Pasteboard color preference Value
	 */
	virtual int32 GetPasteboardColorPreference() const = 0;

	/** Set whether to show "What's New" dialog on startup.
	 * @param showOnStartup [IN], kTrue if "What's New" dialog should be shown on startup, kFalse otherwise.
	 */
	virtual void SetShowWhatsNewOnStartup(bool16 showOnStartup) = 0;

	/** Get whether "What's New" dialog is to be shown on startup.
	 * @return bool16 kTrue if "What's New" dialog should be shown on startup, kFalse otherwise.
	 */
	virtual bool16 GetShowWhatsNewOnStartup() const = 0;

	/** Set whether to add the new swatch(created through the new swatch dialog) to CC Libraries automatically
	* @param addSwatchToCCLibraries [IN], if kTrue the new swatch created using the new swatch dialog will be added to CC Libraries automatically.
	*/
	virtual void SetAutoAddSwatchToCCLibraries(bool16 addSwatchToCCLibraries) = 0;

	/** Get whether to add the new swatch(created through the new swatch dialog) to CC Libraries automatically
	* @return bool16 if kTrue the new swatch created using the new swatch dialog will be added to CC Libraries automatically.
	*/
	virtual bool16 GetAutoAddSwatchToCCLibraries() const = 0;

	/** Set whether to add the new char style(created through the new char style dialog) to CC Libraries automatically
	* @param addAddCharStyleToCCLibraries [IN], if kTrue the new char style created using the new char style dialog will be added to CC Libraries automatically.
	*/
	virtual void SetAutoAddCharStyleToCCLibraries(bool16 addCharStyleToCCLibraries) = 0;

	/** Get whether to add the new char style(created through the new char style dialog) to CC Libraries automatically
	* @return bool16 if kTrue the new char style created using the new char style dialog will be added to CC Libraries automatically.
	*/
	virtual bool16 GetAutoAddCharStyleToCCLibraries() const = 0;

	/** Set whether to add the new para style(created through the new para style dialog) to CC Libraries automatically
	* @param addParaStyleToCCLibraries [IN], if kTrue the new para style created using the new para style dialog will be added to CC Libraries automatically.
	*/
	virtual void SetAutoAddParaStyleToCCLibraries(bool16 addParaStyleToCCLibraries) = 0;

	/** Get whether to add the new para style(created through the new para style dialog) to CC Libraries automatically
	* @return bool16 if kTrue the new para style created using the new para style dialog will be added to CC Libraries automatically.
	*/
	virtual bool16 GetAutoAddParaStyleToCCLibraries() const = 0;

	/** for internal use only 
		Set the preference for ApplicationContainer functions as an ApplicationFrame 
	*/
	virtual void EnableApplicationContainerAsAppFrame() = 0;
	/** Set whether to show CCX Home workspace in no document state
	* @param show [IN], kTrue to show CCX Home workspace in no document state
	*/
	virtual void SetShowHomeWorkspace(bool16 show) = 0;

	/** Get whether to show CCX Home workspace in no document state
	* @return bool16 kTrue if CCX Home workspace in no document state, kFalse otherwise.
	*/
	virtual bool16 GetShowHomeWorkspace() const = 0;

	/**  Get the current preference for showing the stock purchase adornment on unlicensed stock images.
	@return bool16 kTrue if stock purchase adornment should be shown, kFalse if hidden.
	*/
	virtual bool16 GetUIShowStockPurchaseAdornment(void) const = 0;

	/**  Set the current preference for showing the stock purchase adornment on unlicensed stock images.
	This adornment allows the pointer tool to click and open the license extension and proceed with in app licensing workflow.
	@param show, kTrue to show the stock purchase adornment, kFalse to hide.
	*/
	virtual void SetUIShowStockPurchaseAdornment(bool16 show) = 0;

	/**  Get the current preference for Panel Tab Height.
	@return kTrue if Large Tabs are used else return kFalse.
	*/
	virtual bool16 GetPanelTabHeightPreference(void) const = 0;

	/**  Set the current preference for the Panel Tab Height.
	@param tabHeight, kTrue for large tab height else kFalse if small Tabs are supported for Panels. 
	*/
	virtual void SetPanelTabHeightPreference(bool16 tabHeight) = 0;

	/** Set whether to show legacy New Document Dialog
	* @param show [IN], kTrue to show legacy New Document Dialog
	*/
	virtual void SetShowLegacyNewDocDlg(bool16 show) = 0;

	/** Get whether to show legacy New Document Dialog
	* @return bool16 kTrue if legacy New Document Dialog, kFalse otherwise.
	*/
	virtual bool16 GetShowLegacyNewDocDlg() const = 0;
};

#endif
