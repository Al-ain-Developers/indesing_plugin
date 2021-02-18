//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/WOpenFileDialogBase.h $
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
//  Info: This class can be inherited to implement open file dialogs that have custom controls.
//  To do that, override following methods (see an example in WOpenDocDialog):
//  1. Return kTrue in HasCustomControl().
//  3. Add and initialize custom controls using IFileDialogCustomize APIs in AddAndInitializeCustomControls().
//  4. Save the control state values to internal model using SetCustomControlsValues. Typically you need some
//  extra interfaces on the boss to store information for customcontrols.
//  
//========================================================================================

#pragma once
#ifndef __WOpenFileDialogBase__
#define __WOpenFileDialogBase__

#include "IOpenFileDialog.h"

#include "HelperInterface.h"
#include "K2Lookup.h"
#include "PMString.h"
#include "SysFileList.h"
#include "KeyValuePair.h"
#include "K2Vector.h"

#include <shlobj.h>

#pragma export on

//----------------------------------------------------------------------------------------
// WOPenFileDialogBase 
//----------------------------------------------------------------------------------------
class WIDGET_DECL WOpenFileDialogBase : public IOpenFileDialog
{
	public:
		WOpenFileDialogBase(IPMUnknown *boss);
		virtual ~WOpenFileDialogBase();
		
		virtual bool16 DoDialog(IDFile *defaultFile, SysFileList& resultFiles, bool16 allowMultipleFiles = kTrue, const PMString* title = nil, const PMString* infoMessage = nil);		
		// override if you only want your dialog to select directories.
		virtual bool SelectDirectoriesOnly() const { return kFalse; } 
		virtual void AddExtension(const PMString *family, const PMString *extension);

		virtual void AppendAllFilesToFilterList();
		virtual void SetDefaultExtension(const PMString& extension);
		virtual void SetDefaultFilter(const PMString& filterName);

		typedef KeyValuePair<PMString, PMString> FilterEntry;
		typedef K2Vector<FilterEntry> FilterArray;

		// Clients should override these routines to react to provide custom behaviour
		// Invoked privately by the Custom windows Open dialog event handler instance

		// Override this to do initialization of open dialog, by default open window is centered on screen.
		virtual HRESULT HandleInit(IFileOpenDialog*);												
		// Override this to react to the selection change in the open file dialog, no-op by default
		virtual HRESULT HandleSelectionChange(IFileOpenDialog*);
		// Override this to react to the folder about to getting change in the open file dialog, no-op by default
		virtual HRESULT HandleFolderChanging(IFileOpenDialog*, IShellItem*);
		// Override this to react after the the folder is changed in the open file dialog, no-op by default
		virtual HRESULT HandleFolderChange(IFileOpenDialog*);
		// Override this to react after the the file type is changed in the open file dialog, no-op by default
		virtual HRESULT HandleTypeChange(IFileOpenDialog*);													// no-op by default
		// Override this to react when the user selects help in the open file dialog, no-op by default
		virtual HRESULT HandleHelp(IFileOpenDialog*);														// no-op by default
		//Override this to react to Share violation - by changing respValue to 
		// FDESVR_DEFAULT - application has not handled the event, the dialog displays a UI indicating that the file is in use
		// FDESVR_ACCEPT - application accepts the file.
		// FDESVR_REFUSE   application has refused the file, 
		// Most of the variants use DontShowWarningIfOpened, but no-op by default
		virtual HRESULT HandleShareViolation(IFileOpenDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE* respValue);
		//Override this to react to overrite violation - by changing respValue to 
		// FDEOR_DEFAULT - application has not handled the event, the dialog displays a UI indicating that the file is in use
		// FDEOR_ACCEPT - application accepts the file.
		// FDEOR_REFUSE   application has refused the file, 
		// No-op by default
		virtual HRESULT HandleOverrite(IFileOpenDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*);				// no-op by default
		//Override this to react to whether or not to accept the file selected and opened by user
		// Return S_FALSE to stop closing the dialog, S_TRUE to close the dialog and accept the file
		// By default, filename is checked for junk characters.
		virtual HRESULT HandleFileOk(IFileOpenDialog*);													
	
		// Clients should override these routines to react to provide custom behaviour for custom controls
		// Override to react when the custom control item like a radio button is selected, no-op by default
		virtual HRESULT HandleCustomControlItemSelected(IFileDialogCustomize*, DWORD ctrl, DWORD ctrlItem);
		// Override to react when the custom button is clicked, no-op by default
		virtual HRESULT HandleCustomButtonClicked(IFileDialogCustomize*, DWORD ctrl);						
		// Override this to populate the menu items or list while the custom 
		// Open button drop-down list customized through EnableOpenDropDown or a Tools menu is about to display its contents.
		virtual HRESULT HandleControlActivating(IFileDialogCustomize*, DWORD ctrl);							
		// Override to react when the custom check box is clicked, no-op by default
		virtual HRESULT HandleCheckBoxToggled(IFileDialogCustomize*, DWORD ctrl, BOOL state);				

	protected:
		// 	Override this and return true if have custom controls
		virtual bool16 HasCustomControl()const;
		// Initialize the accessory view attributes/fields... 
		virtual HRESULT AddAndInitializeCustomControls(IFileDialogCustomize* pfdc);
		virtual HRESULT SetCustomControlsValues(IFileDialogCustomize* pfdc);

		// Override this to set the label of open button
		virtual PMString GetOpenButtonLabel()const	{ return PMString();	}
		// Override this to set the label of the filename edit box
		virtual PMString GetFileNameLabel() const	{ return PMString();	}

		virtual void PreDoDialog(IDFile *defaultFile, bool16 allowMultipleFiles, const PMString* title, const PMString* infoMessage);	// no-op by default
		virtual void PostDoDialog(bool16& dlgResult, SysFileList& resultFiles);		// no-op by default	
		virtual void OnModifyFilters();					// gives derived classes a chance to modify the filter list
		virtual void GetInitialDirectory(IDFile *defaultFile, PMString *dir, PMString *file);	// rarely overridden

		virtual void SetAdditionalFOSFlags(uint32 flags);
		// These methods can be overridden so user of the dialog don't need to set them before calling DoDialog();
		virtual uint32 GetAdditionalFOSFlags();			// override this to set additional OPENFILENAME flags
		virtual PMString GetDefaultExtension();			// override this to set the default extension 

		/**
			Retrieves the current index of the default filter (the index is 1-based).
			NOTE: this index may change if the filter array is modified so it should not be saved off.
			If a default filter is not set (nobody called SetDefaultFilter) it will then look up
			the default extension into the filter list. If there is not default extension either
			or a filter with that extension could not be found, it will return 0 (zero).
		*/
		virtual uint32 GetDefaultFilterIndex();			// override this to set the default filter index
		virtual PMString GetDefaultTitle();				// override this to change the default title

		// Clients who want to check file existence and the file is not in use by some other app on Open button pressed, should override following returning true
		virtual bool16 ShouldCheckFileExistenceOnFileOK() const { return kFalse; }

		// Following function checks if the given file path is already in use by other application or not
		// Clients who want to check something additional should override this and display their alert.
		virtual HRESULT CheckFileExistenceOnFileOK(PWSTR pszFilePath);

		// This method must be overridden if you have custom controls 
		// The provided window handle will never be NULL
		HWND GetOwnerHandle();

		// non virtual util functions
		HRESULT DontShowWarningIfOpened(IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* resp);

		bool16 AllowsMultiSelect(IFileOpenDialog* pfd);

		FilterArray const& GetFilterArray() const { return fFilterArray; }
		void SetFilterArray(const FilterArray& newFilterArray);

		// Adds a new filter that is a combination of all the existing individual filters
		void AddAllSupportedFilesFilter(const PMString& supportedFilterName);
		
		// gets files from the IFileDialog containing selected files, which can be tricky for multiple files.
		// If there is no platform error it returns S_OK
		HRESULT GetFileListFromOpenFileResult(SysFileList& resultFiles, IFileOpenDialog *pfod); 

		// Typically used from the HandleFileOK to check if the files about to be opened are 
		// not opened by some other application
		HRESULT IsOtherAppUsingOpenedFiles(IFileOpenDialog* pfd);

	private:
		HRESULT PreHandleFileOk(IFileOpenDialog* pfd);
		bool16 GetLocationLastUsed(PMString& dir);
		void SetLocationLastUsed(const IDFile& sysFile);

		// Constructs a list of tuples containing file type description with extensions
		void InitFilterString( std::vector<COMDLG_FILTERSPEC>& fileTypes ) const;

	private:
		FilterArray						fFilterArray;
		PMString						fDefaultFilter;
		PMString						fDefaultExtension;
		FILEOPENDIALOGOPTIONS			fAdditionalFlags;

	DECLARE_HELPER_METHODS()			
};

#pragma export off

#endif
