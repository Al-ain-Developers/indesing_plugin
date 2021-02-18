//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlaceOptions.h $
//  
//  Owner: Adrian O'Lenskie
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
//  This class defines an interface used to store and access options used by the place
//  dialog.
//  
//========================================================================================

#pragma once
#ifndef __IPlaceOptions_h__
#define __IPlaceOptions_h__

#include "IPMUnknown.h"
#include "DocumentID.h"

/**
 IPlaceOptions is used to store and access options that affect the appearance of the
 Place dialog, and options that specify the behavior of the resulting import
 operation.

 @see IPlaceDialogPrefs
 @see IPlaceDialogPrefsCmdData
 @see IImportManagerOptions
*/
class IPlaceOptions : public IPMUnknown
{
	public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IPLACEOPTIONS };
			
	/** Get the "show filter prefs" flag */
	virtual bool16 GetShowFilterPrefs() const = 0;
	/** Set the "show filter prefs" flag */
	virtual void SetShowFilterPrefs(bool16 show) = 0;

	/** Set "replace selected item" flag */
	virtual void SetReplaceSelectedItem(bool16 replace) = 0;
	/** Get the "replace selected item" flag */
	virtual bool16 GetReplaceSelectedItem() const = 0;

	/** Set "generate captions" flag */
	virtual void SetGenerateCaptions(bool16 replace) = 0;
	/** Get the "generate captions" flag */
	virtual bool16 GetGenerateCaptions() const = 0;

	/** Set the "Apply CJK grid options" flag */
	virtual void SetApplyCJKGrid(bool16 replace) = 0;
	/** Enable/Disable the "CJK grid options" control */
	virtual void EnableApplyCJKGrid(bool16 replace) = 0;
	/** Set the "Apply CJK grid options" flag */
	virtual bool16 GetApplyCJKGrid() const = 0;
	/** Is the "CJK grid options" control enabled */
	virtual bool16 IsApplyCJKGridEnabled() const = 0;

	/** Set the Title of the Place Dialog. 
		Allows the ability to change the title of the dialog to something like "Import". */
	virtual void SetDialogTitle(const PMString& dialogTitle) = 0;
	/** Get the Title of the Place Dialog. */
	virtual const PMString& GetDialogTitle() const = 0;

	/** Set the flag that controls whether to display the dialog with or without the extra place options. */
	virtual void SetUsePlaceOptions(bool16 useOptions) = 0;
	/** Get the flag that controls whether to display the dialog with or without the extra place options. */
	virtual bool16 GetUsePlaceOptions() const = 0;

	/** Set the flag to show the preview pane in the place dialog(windows only). */
	virtual void SetShowPreview(bool16 yesNo) = 0;
	/** Get the value of the flag to show the preview pane in the place dialog(windows only). */
	virtual bool16 GetShowPreview(void) const = 0;
	

#ifdef ID_DEPRECATED
/** @see ISuppressedUI for a new (and hopefully better) way to supress controls in the place dialog and elsewhere */

	/** Enable/Disable the "show import filter prefs" control */
	virtual void EnableShowFilterPrefs(bool16 enable) = 0;
	/** Is the "show import filter prefs" control enabled */
	virtual bool16 IsShowFilterPrefsEnabled() const = 0;
	/** Enable/Disable the "replace selected item" control */
	virtual void EnableReplaceSelectedItem(bool16 enable) = 0;
	/** Is the "replace selected item" control enabled */
	virtual bool16 IsReplaceSelectedItemEnabled() const = 0;
#endif		
};

#endif //__IPlaceOptions_h__

