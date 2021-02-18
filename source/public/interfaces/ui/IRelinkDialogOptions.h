//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IRelinkDialogOptions.h $
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
#ifndef __IRelinkDialogOptions_h__
#define __IRelinkDialogOptions_h__

#include "IPMUnknown.h"
#include "ImportExportUIID.h"

/** Interface for the options used to control the settings & appearance of the options in the relink dialog.
		@see IPlaceOptions, IImportManagerOptions, IRelinkPreferences
*/
class IRelinkDialogOptions : public IPMUnknown
{
	public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IRELINKDIALOGOPTIONS };
			
	/** Set the value for the 'Search for Missing Files in this Folder' checkbox in the relink dialog */
	virtual void SetSearchForMissing(bool search) = 0;
	/** Get the value for the 'Search for Missing Files in this Folder' checkbox in the relink dialog */
	virtual bool GetSearchForMissing() const = 0;
	/** Enable/Disable the "search for missing" control */
	virtual void EnableSearchForMissing(bool enable) = 0;
	/** Is the "search for missing" control enabled */
	virtual bool IsSearchForMissingEnabled() const = 0;

	/** Set the "show filter prefs" flag */
	virtual void SetShowFilterPrefs(bool show) = 0;
	/** Get the "show filter prefs" flag */
	virtual bool GetShowFilterPrefs() const = 0;
	/** Enable/Disable the "show import filter prefs" control */
	virtual void EnableShowFilterPrefs(bool enable) = 0;
	/** Is the "show import filter prefs" control enabled */
	virtual bool IsShowFilterPrefsEnabled() const = 0;

	/** Set the flag that indicates if the user skipped this link. */
	virtual void SetUserSkippedThisLink(bool skipped) = 0;
	/** Get the flag that indicates if the user skipped this link. */
	virtual bool GetUserSkippedThisLink() const = 0;
	/** Set the flag to show the skip button in the relink dialog. */
	virtual void SetShowSkipButton(bool yesNo) = 0;
	/** Get the value of the flag to show the skip button in the relink dialog. */
	virtual bool GetShowSkipButton(void) const = 0;
	
	/** Set the flag to show the preview pane in the relink dialog(windows only). */
	virtual void SetShowPreview(bool yesNo) = 0;
	/** Get the value of the flag to show the preview pane in the relink dialog(windows only). */
	virtual bool GetShowPreview(void) const = 0;
};

#endif //__IRelinkDialogOptions_h__

