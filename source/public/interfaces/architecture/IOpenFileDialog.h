//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenFileDialog.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IOpenFileDialog__
#define __IOpenFileDialog__

#include "IPMUnknown.h"
#include "DocumentID.h"

#ifdef WINDOWS
	#include "ShObjIdl.h"
#endif

class PMString;
class SysFileList;

//----------------------------------------------------------------------------------------
// Constants 
//----------------------------------------------------------------------------------------
#ifdef MACINTOSH
const OSType kAllFileTypes = 'all ';		// used to indicate that we want to show all files regardless of type
#endif

namespace OpenFileDialog
{
	// Filter name for "All Files"
	extern WIDGET_DECL const PMString kAllFilesFilterName;
}

/** 
	This interface is used to display a dialog to open a single file or multiple files.
	Typically you need to do the following steps:
	1. Create a object of kOpenFileDialogBoss.
	2. Call AddExtension and AddType() to set the file filter info.
	3. (optional) Use other methods to change default settings.
	4. Call DoDialog() to open the dialog.

	To add a custom control, create a new boss and implement this interface.
	The implementation should inherit (W/M)OpenFileDialogBase.
	See more comments in their headers.
*/
class IOpenFileDialog : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOPENFILEDIALOG };

        /** Displays the file open dialog.
            @param defaultFile[in]- the file that the dialog should default to.
            @param resultFiles[out] - will be filled with the file(s) the user selected.
            @param allowMultipleFiles[in]- specifies if multiple selection is allowed.
            @param title[in]- title for the dialog box. Default title is "Open a File".
            @param infoMessage[in]- Mac only parameter. Descriptive text that will be displayed below the browser list.
            @return bool16 kFalse if the user cancelled the dialog, kTrue otherwise.
        */
		virtual bool16 DoDialog(IDFile *defaultFile, SysFileList& resultFiles,
			bool16 allowMultipleFiles = kTrue, const PMString* title = nil, const PMString* infoMessage = nil) = 0;

		
        /** Adds an extension to the file filter list.
            @param family[in]- the name of the filter. If the filter exists, the extension will be added to it's list.
			If the filter doesn't exist, a new one will be added to the bottom of the filter list.
            @param extension[in] - extension associated with the filter.
        */
		virtual void AddExtension(const PMString *family, const PMString *extension) = 0;

#ifdef WINDOWS	
        /** WINDOWS ONLY : Adds "All Files" filter to file filter list.
			If "All Files" doesn't already exist in the list it's added to the list.
			The client code should not make any assumption about the position of this filter in the list.
        */
		virtual void AppendAllFilesToFilterList() = 0;

        /** WINDOWS ONLY : Sets additional OFN flags for the dialog.
			The default flags are FOS_SHAREAWARE | FOS_PATHMUSTEXIST plus FOS_ALLOWMULTISELECT if
 			allowMultipleFiles parameter passed in DoDialog() is kTrue.
            @param flags[in]- additional flags besides the ones specified above.
        */
		virtual void SetAdditionalFOSFlags(uint32 flags)= 0;

        /** WINDOWS ONLY : Sets the default file extension. This extension is appended automatically
			to a file name if the user doesn't type one. While for Save dialogs this is very helpful, for Open
			dialogs this can be confusing for the user, so the usage of this method is discouraged.
			NOTE: if you want to specify a default filter to be selected in the filter drop down list
			you should use SetDefaultFilter method. If no filter is specified as default, this default extension
			will be looked up in the filter list and that filter will be selected as default.
            @param extension[in]- default extension for files.
        */
		virtual void SetDefaultExtension(const PMString& extension) = 0;

        /** WINDOWS ONLY : Sets the default filter in the filter selection list.
            @param filterName[in]- the name of the filter to be selected as the default one.
        */
		virtual void SetDefaultFilter(const PMString& filterName) = 0;

#elif defined (MACINTOSH)
		/** MAC ONLY : Adds a new type.
            @param theType[in]- the new type to be added.
        */
		virtual void AddType(SysOSType theType) = 0;
	
		/** MAC ONLY : Adds a custom type menu entry.
		 @param theName[in]- name of the entry.
		 @param theType[in]- the type.
		 */
		virtual void AddCustomMenu(const PMString& theName, SysOSType theType) = 0;	
#endif
};


#endif
