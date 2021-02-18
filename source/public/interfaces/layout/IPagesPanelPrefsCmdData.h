//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPagesPanelPrefsCmdData.h $
//  
//  Owner: Paul Sorrick
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
//  Data interface for Pages Panel prefs command.
//  includes : 	Page icon size, vertical or wrapping view, binding line visible setting.
//  
//========================================================================================

#pragma once
#ifndef __IPagesPanelPrefsCmdData__
#define __IPagesPanelPrefsCmdData__

#include "IPMUnknown.h"
#include "IPagesPanelPrefs.h"

/**
	Command data interface defining the parameters that the pages panel uses to draw used by kSetPagesPanelPrefsCmdBoss
	Users of this command may set just the values that are changing, by default others will remain as is.
*/
class IPagesPanelPrefsCmdData : public IPMUnknown
{
public:

		/** Get the enumerated value indicating the icon size to use in the pages subpanel
			@return Pages subpanel icon size
		*/
	virtual const IPagesPanelPrefs::IconSize GetIconSize() const = 0;

		/** Set the enumerated value indicating the icon size to use in the pages subpanel
			@param size the Pages subpanel icon size, kInvalidSize to leave unchanged.
		*/
	virtual void SetIconSize(IPagesPanelPrefs::IconSize size) = 0;

		/** Get method for the view setting of the layout pages subpanel.
			@return a value from ViewSetting enum
		*/
	virtual const IPagesPanelPrefs::ViewSetting GetViewSetting() const = 0;

		/** Set the view setting for the pages subpanel
			@param setting, a ViewSetting enum
			@see IPagesPanelPrefs::ViewSetting
		*/
	virtual void SetViewSetting(IPagesPanelPrefs::ViewSetting setting) = 0;

		/** Get the enumerated value indicating the icon size to use in the master pages subpanel
			@return master pages  subpanel icon size
		*/
	virtual const IPagesPanelPrefs::IconSize GetMasterIconSize() const = 0;

		/** Set the enumerated value indicating the icon size to use in the masters subpanel
			@param size the Masters subpanel icon size, kInvalidSize to leave unchanged.
		*/
	virtual void SetMasterIconSize(IPagesPanelPrefs::IconSize size) = 0;

		/** Get the show vertical setting for the master pages subpanel
			@return kTrue if Vertical, kFalse if master pages section is set to wrapping, -1 to leave unchanged
		*/
	virtual const bool16 GetMastersVerticalView() const = 0;

		/** Set the show vertical setting for the master pages subpanel
			@param vertical kTrue if Vertical, kFalse if master pages section is set to wrapping, -1 to leave unchanged
		*/
	virtual void SetMastersVerticalView(bool16 vertical) = 0;

		/** Get the bool indicating if the pages subpanel is a fixed size
			@return kFalse if the pages section resizes when the window resizes, kTrue otherwise
		*/
	virtual const bool16 GetPagesFixedSize() const = 0;

		/** Set the bool indicating if the pages subpanel is a fixed size
			@param fixed kFalse if the pages section resizes when the window resizes, kTrue otherwise, -1 to leave unchanged
		*/
	virtual void SetPagesFixedSize(bool16 fixed) = 0;

		/** Get the bool indicating if the master pages subpanel is a fixed size
			@return kFalse if the master pages section resizes when the window resizes, kTrue otherwise
		*/
	virtual const bool16 GetMastersFixedSize() const = 0;

		/** Set the bool indicating if the master pages subpanel is a fixed size
			@param fixed kFalse if the master pages section resizes when the window resizes, kTrue otherwise, -1 to leave unchanged
		*/
	virtual void SetMastersFixedSize(bool16 fixed) = 0;

		/** Get the bool indicating if the pages subpanel is on top
			@return kTrue if the pages section is on the top; kFalse otherwise
		*/
	virtual const bool16 GetPagesOnTop() const = 0;	

		/** Set the bool indicating if the pages subpanel is on top
			@param kTrue if the pages section is on the top; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetPagesOnTop(bool16 top) = 0;	

		/** Get the bool indicating if the thumbnails are on or off for pages
			@return kTrue if the thumbnails are on; kFalse otherwise
		*/
	virtual const bool16 GetPagesThumbnails() const = 0;	

		/** Set the bool indicating if the thumbnails are on or off for pages
			@param on kTrue if the thumbnails are on; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetPagesThumbnails(bool16 on) = 0;	

		/** Get the bool indicating if the thumbnails are on or off for masters
			@return kTrue if the thumbnails are on; kFalse otherwise
		*/
	virtual const bool16 GetMastersThumbnails() const = 0;	

		/** Set the bool indicating if the thumbnails are on or off for masters
			@param on kTrue if the thumbnails are on; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetMastersThumbnails(bool16 on) = 0;	

		/** Get the bool indicating if the transparency indicator should be drawn on spreads with transparency applied.
			This is the checkerboard icon.
			@return kTrue if the transparency icon is on; kFalse otherwise
		*/
	virtual const bool16 GetShowTransparencyIcon() const = 0;	

		/** Set the bool indicating if the transparency indicator should be drawn on spreads with transparency applied.
			This is the checkerboard icon.
			@param show kTrue if the transparency icon is on; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetShowTransparencyIcon(bool16 show) = 0;	

		/** Get the bool indicating if the transition icon should be drawn on spreads with page transitions applied.
			@return kTrue if the spread has a transition applied; kFalse otherwise
		*/
	virtual const bool16 GetShowTransitionsIcon() const = 0;	

		/** Set the bool indicating if the transition icon should be drawn on spreads with page transitions applied.
			@param show if the spread has a transition applied; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetShowTransitionsIcon(bool16 show) = 0;	

		/** Get the bool indicating if the rotation icon should be drawn on spreads with non-zero rotation applied.
			@return kTrue if the rotation icon is on; kFalse otherwise
		*/
	virtual const bool16 GetShowRotationIcon() const = 0;	

		/** Get the bool indicating if the rotation icon should be drawn on spreads with non-zero rotation applied.
			@param show kTrue if the rotation icon is on; kFalse otherwise, -1 to leave unchanged
		*/
	virtual void SetShowRotationIcon(bool16 show) = 0;	
};

#endif // __IPagesPanelPrefsCmdData__
