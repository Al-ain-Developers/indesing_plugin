//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISaveFileDialog.h $
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
#ifndef __ISaveFileDialog__
#define __ISaveFileDialog__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "DocumentID.h"

#ifdef WINDOWS
	#include "ShObjIdl.h"
#endif

/**	ISaveFileDialog is used to allow the user to specify where to save a file.

	Typically you need to do the following steps:
	1. Create a object of kSaveFileDialogBoss.
	2. Call SetFileTypeInfo() to set the file type and extension of the file you are going to save.
	3. (Optional) Use other methods to change default settings.
	4. Call DoDialog() to display the dialog.
	To add a custom control, create a new boss and implement this interface.
	The implementation should inherit (W/M)SaveFilaDialogBase. See more comments
	in their headers.
*/
class ISaveFileDialog : public IPMUnknown
{
	public:
	
		/** Displays the save file dialog.
		
			@param defaultFile[in]- specifies the default file to use when saving. It should NOT be nil.
				On Windows, defaultFile can be a file name with full path, a file name without path,
				or a path name without a file name. When a path is given, it is used as the default directory.
				Otherwise the last used directory for save is used as the default one.
				On Mac, defaultFile always contains a path. To ignore the directory in defaultFile and use the 
				system default directory (the last used save directory), set useSystemDefaultDir to be kTrue;
			@param resultFile[out]- the file to save to
			@param selectedIndex[inout]- optional parameter. may be nil. If not nil, it's used to select the default index in the list, and returns the index selected by the user
			@param useSystemDefaultDir[in]- pass kTrue to ignore the directory in defaultFile and use the 
				system default directory (the last used save directory)
			@param showTypeMenu[in]- passing kFalse will hide the Type menu in the dialog.
			@param title[in]- the title for the window.  The default title is "Save As".
			@return false if user canceled, true otherwise.
		*/
		virtual bool16 DoDialog(const IDFile *defaultFile, IDFile* resultFile, int32* selectedIndex = nil, bool16 useSystemDefaultDir = kFalse, bool16 showTypeMenu = kTrue, const PMString* title = nil) = 0;

		/** Add another creator, type, extension tuple to popup.
		
			@param description[in]- text description of the file type to be displayed in the types popup menu.
			@param extension[in]- file extension
		*/
		virtual void AddFileTypeInfo(const PMString &description, const PMString &extension) = 0;
		
#ifdef WINDOWS	
		/** Sets platform-specific flags.
		
			@param flags[in]- platform specific flags.
				For PC only:
					The default flags are FOS_SHAREAWARE | FOS_PATHMUSTEXIST.
					Use this method to set additional FOS flags besides these two.
		*/
		virtual void SetAdditionalFOSFlags(uint32 flags)= 0;
#endif	
};

#endif
