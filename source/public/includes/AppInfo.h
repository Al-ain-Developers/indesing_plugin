//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AppInfo.h $
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
//  Purpose:    Defines classes for launching applications (Edit With functionality).
//  
//========================================================================================

#pragma once
#ifndef __APPINFO__
#define __APPINFO__

#include "PMString.h"
#include "K2Vector.h"

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class AppInfo;

/** A list of application infos */
typedef K2Vector<AppInfo> AppInfoList;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Class that contains information about applications, used Edit Original/Edit With functionality.
	AppInfo is used to launch a specific application for a linked file in an external editor.
	In general, clients should not need to contruct this class, but rather gather a list of applications
	that can edit a particular link or link resource via GetEditOriginalEditor and GetEditorList
	respectively. Given an empty AppInfoList, these APIs will gather all the editors for a link in
	the form of a list of AppInfo classes/structures. Then ILinkResource->Edit may be used
	to edit a link via launching an external editor specified with a particular AppInfo.

	@see ILinksUIUtils.h, GetEditOriginalEditorList
	@see ILinksUIUtils.h, EditOriginal
	@see ILinksUtils.h, GetEditorList
	@see ILinkResource.h, Edit
*/
class AppInfo
{
    public:
        typedef object_type data_type;

        AppInfo() {}

        AppInfo
		(
			const PMString&	path,				// Path to .exe
			const PMString&	displayName,		// Display name, used for our menus
			const PMString&	version,			// Version of .exe file
			const bool16 defaultApp = kFalse,	// Is the default app
			const bool16 adobeApp = kFalse		// Is an Adobe app
		) :
          fPath(path),
          fDisplayName(displayName),
          fVersion(version),
		  fIsDefaultApp(defaultApp),
		  fIsAdobeApp(adobeApp) 
			{ fPath.SetTranslatable(kFalse), fDisplayName.SetTranslatable(kFalse), fVersion.SetTranslatable(kFalse); }

		/** Copy Constructor
		*/
		AppInfo(const AppInfo& info) :
			fPath(info.fPath),
			fDisplayName(info.fDisplayName),
			fVersion(info.fVersion),
			fIsDefaultApp(info.fIsDefaultApp),
			fIsAdobeApp(info.fIsAdobeApp)
		{}

		/**	Return the path to the application. 
			On Windows, might look like this: C:\Program Files\Adobe\Adobe Photoshop CS3\Photoshop.exe
			On Mac, might look like this: /Applications/Safari.app
			@param none
			@return PMString 
		 */
		PMString GetPath() const 			{ return fPath; }

		/**	A more user-friendly name with version info appended. Used for menu display. e.g. Adobe Photoshop CS3
			@param none
			@return PMString 
		 */
		PMString GetDisplayName() const		{ return fDisplayName; }

		/**	Return a version string. e.g. CS3 or 5.1
			@param none
			@return PMString 
		 */
		PMString GetVersion() const			{ return fVersion; }

		/**	Is this the default application for a file type (via IEditFile.h or IDataLinkAction.h)
			@param none
			@return kTrue if it's the default app, kFalse if not.
		 */
		bool16	 GetIsDefault() const		{ return fIsDefaultApp; }

		/**	Return if application is considered an Adobe application. Used for sorting and menu display purposes.
			@param none
			@return kTrue if a well-known Adobe app, kFalse otherwise. 
		 */
		bool16	 GetIsAdobeApp() const						{ return fIsAdobeApp; }

        /** Don't care about fIsDefaultApp or fIsAdobeApp for comparison purposes
		*/
		bool16 operator==(const AppInfo& other) const
		{
            return ((fPath == other.fPath) && 
					(fDisplayName == other.fDisplayName) &&
					(fVersion == other.fVersion) );
		}

		/** Less than(<) operator for comparison. Sort by Adobe status, then by display name.
			If display names are equal, sort by version number.
		    @param other IN the object to compare with.
			@return bool16 kTrue means less than, otherwise kFalse.
		*/
		bool16 operator<(const AppInfo& other) const
		{
			if (fIsAdobeApp)
			{
				if (other.fIsAdobeApp)
					return (fDisplayName == other.fDisplayName ? fVersion < other.fVersion : fDisplayName < other.fDisplayName);
				else
					return kTrue;
			}
			else if (other.fIsAdobeApp)
			{
				return kFalse;
			}

			return (fDisplayName == other.fDisplayName ? fVersion < other.fVersion : fDisplayName < other.fDisplayName);
		}

	private:
		PMString	fPath;			// Path to .exe
		PMString	fDisplayName;	// Display name, used for our menus
		PMString	fVersion;		// Version of .exe file
        
		bool16		fIsDefaultApp;	// kTrue if default editor, kFalse otherwise
		bool16		fIsAdobeApp;	// kTrue if app is an "Adobe" app, kFalse otherwise
};

/** Default value for launching default application/editor
*/
extern PUBLIC_DECL const AppInfo kNullAppInfo;

#pragma export off

#endif	// __APPINFO__

