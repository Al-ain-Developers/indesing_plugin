//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/WOpenSaveDlgUtils.h $
//  
//  Owner: Lin Xia
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
//  Info: Utility fuctions used by WOpenFileDialogBase and WSaveFileDialogBase.
//  
//========================================================================================

#pragma once
#ifndef __WOpenSaveDlgUtils__
#define __WOpenSaveDlgUtils__

#include "PMString.h"
#include "SysFileList.h"
#include <shlobj.h>

#pragma export on

class WIDGET_DECL WOpenSaveDlgUtils
{
public:

	// Return the handle of the parent window.
	static HWND GetParentWindowHandle();

	// Move window to the center of the screen.
	static void CenterOnScreen(HWND window);

	// Get the directory, file name, and extension of the file.
	// Return 0 if success, non 0 if failed.
	static int32 GetFileInfo(const IDFile *theFile, PMString *dir, PMString *file);

	// Return kTure if list contains extension.
	static bool16 DoesListContainExtension(PMString &list, PMString &extension);

	// Creates a shell item from the given path string
	static IShellItem* CreateShellItemFromPathString(PMString &pathName);

	// gets system filepath from the IShellItem.
	// If there is no platform error it returns S_OK
	// It is the responsibility of the caller to free the string pointed to by ppszFilePath when it is no longer needed. 
	// Call CoTaskMemFree on *ppszName to free the memory.
	static HRESULT CopySysFilePathFromShellItem(IShellItem *psiResult, PWSTR* ppszFilePath);

	// gets file from the system file path IShellItem and returns the corresponding IDFile.
	// If there is no platform error it returns S_OK
	static void GetIDFileFromSysFilePath(IDFile& resultFile, PWSTR pszFilePath); 

	// gets files from the IShellItem and returns the corresponding IDFile.
	// If there is no platform error it returns S_OK
	static HRESULT GetIDFileFromShellItem(IDFile& resultFile, IShellItem *psiResult);

	/* Function to add a check box button in the open file dialog with the 
		ID - checkBoxID, 
		Check box string - untranslated label, 
		State - checkState true means checked, unchecked otherwise
		ControlState - isDisabled true means disabled, enabled otherwise
	*/
	static HRESULT AddCheckBoxButton(IFileDialogCustomize *pfdc, DWORD checkBoxID, PMString& label, bool16 checkState, bool16 isDisabled = kFalse);

	/* Function to add a combo box in the open file dialog with the 
		ID - comboBoxID,
		ControlState - isDisabled true means disabled, enabled otherwise
	*/
	static HRESULT AddComboBox(IFileDialogCustomize *pfdc, DWORD comboBoxID, bool16 isDisabled = kFalse);

	/* Function to add a radio button to a radio list in the open file dialog with the 
		List ID - radioListID - group of radio buttons identifier, 
		ButtonID - radioButtonID - id of radio button
		Radio string - untranslated label, 
		ControlState - isDisabled true means disabled, enabled otherwise
	*/
	static HRESULT	AddRadioButtonToRadioList(IFileDialogCustomize *pfdc, DWORD radioListID, DWORD radioButtonID, PMString& label, bool16 isDisabled = kFalse);

	/* Function to add a push button in the open file dialog with the 
		ID - buttonID, 
		Button string - untranslated label, 
		ControlState - isDisabled true means disabled, enabled otherwise
	*/
	static HRESULT AddPushButton(IFileDialogCustomize *pfdc, DWORD buttonID, PMString& label, bool16 isDisabled = kFalse);

	/* Function to add a text box in the open file dialog with the
	ID - textBoxID,
	Box string - untranslated label,
	ControlState - isDisabled true means disabled, enabled otherwise
	*/
	static HRESULT AddTextBox(IFileDialogCustomize *pfdc, DWORD textBoxID, PMString& label, bool16 isDisabled = kFalse);
};
#pragma export off

#endif
