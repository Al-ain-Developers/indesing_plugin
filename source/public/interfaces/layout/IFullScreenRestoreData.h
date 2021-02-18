//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFullScreenRestoreData.h $
//  
//  Owner: Bob Freeman
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
#ifndef __IFullScreenRestoreData__
#define __IFullScreenRestoreData__

#include "PMTypes.h"
#include "PMRect.h"
#include "AppUIID.h"
#include "IPreviewPrefs.h"
#include "ILayoutControlData.h"

class PMRect;
/** Data used to restore the state of the document window when exiting full screen mode.
*/
class IFullScreenRestoreData : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IFULLSCREENRESTOREDATA };

	/** Set the rect of the frame of the LayoutPanelWidget.
		@param margins values for the SplitterPanelWidget prior to entering full screen mode
	*/
	virtual void					SetRestoreMargins(const PMRect& margins) = 0;

	/** Gets the margins for the frame of the SplitterPanelWidget.
		@return PMRect for the margins
	*/
	virtual PMRect					GetRestoreMargins() = 0;
								
	/**  Clear the hidden widget list.
	*/
	virtual void					ClearHiddenWidgetList() = 0;

	/** Add a WidgetID of a widget we are hiding as we enter full screen mode.
		@param WidgetID ID of the widget
	*/
	virtual	void					AddHiddenWidget(WidgetID widgetID) = 0;
										
	/** Get the resources plugin id for the widget.
	*/
	virtual int32					GetHiddenWidgetCount() const = 0;

	/** Get the WidgetID of a hidden widget.
		@param at index of hidden widget you want the ID for.
	*/
	virtual	WidgetID				GetHiddenWidgetID(int32 at) = 0;

	/** Set the current screen mode to be restored when we exit full screen
		@param mode IPreviewPrefs::PreviewMode screen mode
		*/
	virtual void					SetRestoreScreenMode(IPreviewPrefs::PreviewMode mode) = 0;

	/** Get the screen mode to be restored when we exit full screen
		@return IPreviewPrefs::PreviewMode screen mode
		*/
	virtual IPreviewPrefs::PreviewMode	GetRestoreScreenMode() = 0;

	/** Set the current state of the structure pane to be restored when we exit full screen
		@param structureShown true if structure was showing
		*/
	virtual void					SetRestoreStructure(bool16 structureShown) = 0;

	/** Get the state of the structure pane to be restored when we exit full screen
		@return bool16 true if structure was showing
		*/
	virtual bool16					GetRestoreStructure() = 0;

	/** Set the current state of the split layout pane to be restored when we exit full screen
		@param splitLayout true if split layout was shown
		*/
	virtual void					SetRestoreSplitLayout(bool16 splitLayout) = 0;

	/** Get the state of the split layout pane to be restored when we exit full screen
		@return bool16 true if split layout was showing
		*/
	virtual bool16					GetRestoreSplitLayout() = 0;

	/** Set the current fit mode to be restored when we exit full screen
		@param fit ILayoutControlData::FitSetting mode
		*/
	virtual void					SetRestoreFit(ILayoutControlData::FitSetting fit) = 0;

	/** Get the screen mode to be restored when we exit full screen
		@return ILayoutControlData::FitSetting mode
		*/
	virtual ILayoutControlData::FitSetting	GetRestoreFit() = 0;

	/** Set the current background color to be restored when we exit full screen
		@param bgColorIndex color index of the preview background color
		*/
	virtual void					SetRestoreBGColorIndex(int32 bgColorIndex) = 0;

	/** Get the background color index to be restored when we exit full screen
		@return index of the preview background color to restore
		*/
	virtual int32					GetRestoreBGColorIndex() = 0;

	/** Set the current draw options to be restored when we exit full screen
		@param drawOptions color index of the preview background color
		*/
	virtual void					SetRestoreDrawOptions(int32 drawOptions) = 0;

	/** Get the draw options to be restored when we exit full screen
		@return IDrawOptions::* to restore
		*/
	virtual int32					GetRestoreDrawOptions() = 0;

	/** Set the current zoom level to be restored when we exit full screen (if there is no specific fit option)
		@param zoom level
		*/
	virtual void					SetRestoreZoom(PMReal zoom) = 0;

	/** Get the draw options to be restored when we exit full screen
		@return PMReal zoom level to restore
		*/
	virtual PMReal					GetRestoreZoom() = 0;

	/** Set the current state of the auto restore hidden panels to be restored when we exit full screen
		@param structureShown true if structure was showing
		*/
	virtual void					SetAutoShowHiddenPanels(bool16 autoShow) = 0;

	/** Get the state of the auto restore hidden panels to be restored when we exit full screen
		@return bool16 true if structure was showing
		*/
	virtual bool16					GetAutoShowHiddenPanels() = 0;

	/** Sets flag to indicate that we are in PresentationMode. We need to know this since windows can be in full screen, but not
	    in presentation mode. This should be set after presentation mode is started and cleared after it's done.
		@param isPresentationMode true if in presentation mode, false otherwise
		*/
	virtual void					SetIsPresentationMode(bool16 isPresentationMode) = 0;
	

	/** returns true if we are in PresentationMode. We need to know this since windows can be in full screen, but not
	    in presentation mode.
		@return true if in presentation mode, false otherwise
		*/
	virtual bool16					IsPresentationMode() = 0;
	
};

#endif
