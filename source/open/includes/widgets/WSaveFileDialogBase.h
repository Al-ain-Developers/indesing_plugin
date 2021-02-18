//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/WSaveFileDialogBase.h $
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
//  Info: This class can be inherited to implement save file dialogs that have custom controls.
//  To do that, override following methods (see an example in WExportConfigFileDlg):
//  1. Return kTrue in HasCustomControl().
//  3. Add and initialize custom controls using IFileDialogCustomize APIs in AddAndInitializeCustomControls().
//  4. Save the control state values to internal model using SetCustomControlsValues. Typically you need some
//  extra interfaces on the boss to store information for customcontrols.
//  
//========================================================================================

#pragma once
#ifndef __WSaveFileDialogBase__
#define __WSaveFileDialogBase__

#include "ISaveFileDialog.h"
#include "HelperInterface.h"
#include "K2Lookup.h"
#include "WOpenSaveDlgUtils.h"
#include <ShObjIdl.h>

#pragma export on

//----------------------------------------------------------------------------------------
// WSaveFileDialogBase 
//----------------------------------------------------------------------------------------
class WIDGET_DECL WSaveFileDialogBase : public ISaveFileDialog
{
	public:
		WSaveFileDialogBase(IPMUnknown *boss);
		virtual ~WSaveFileDialogBase();
		
		virtual bool16 DoDialog(const IDFile *defaultFile, IDFile* resultFile, int32* selectedIndex, bool16 useSystemDefaultDir, bool16 showTypeMenu, const PMString* title);
		virtual void AddFileTypeInfo(const PMString &description, const PMString &extension);
		virtual void SetAdditionalFOSFlags(uint32 flags);

		// Clients should override these routines to react to provide custom behaviour
		// Invoked privately by the Custom windows Save dialog event handler instance

		// Override this to do initialization of open dialog, by default save window is centered on screen.
		virtual HRESULT HandleInit(IFileSaveDialog*);			
		// Override this to react to the selection change in the save file dialog, no-op by default
		virtual HRESULT HandleSelectionChange(IFileSaveDialog*);
		// Override this to react to the folder about to getting change in the save file dialog, no-op by default
		virtual HRESULT HandleFolderChanging(IFileSaveDialog*, IShellItem*);
		// Override this to react after the the folder is changed in the save file dialog, no-op by default
		virtual HRESULT HandleFolderChange(IFileSaveDialog*);				
		// Override this to react after the the file type is changed in the save file dialog, no-op by default
		virtual HRESULT HandleTypeChange(IFileSaveDialog*);					
		// Override this to react when the user selects help in the save file dialog, no-op by default
		virtual HRESULT HandleHelp(IFileSaveDialog*);						
		//Override this to react to Share violation - by changing respValue to 
		// FDESVR_DEFAULT - application has not handled the event, the dialog displays a UI indicating that the file is in use
		// FDESVR_ACCEPT - application accepts the file.
		// FDESVR_REFUSE   application has refused the file, 
		// By default shows the user a choice to replace the file, if user presses no, it is rejected
		virtual HRESULT HandleShareViolation(IFileSaveDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE* resp);
		//Override this to react to overrite violation - by changing respValue to 
		// FDEOR_DEFAULT - application has not handled the event, the dialog displays a UI indicating that the file is in use
		// FDEOR_ACCEPT - application accepts the file.
		// FDEOR_REFUSE   application has refused the file, 
		// No-op by default
		virtual HRESULT HandleOverrite(IFileSaveDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*);				// no-op by default
		//Override this to react to whether or not to accept the file selected and opened by user
		// Return S_FALSE to stop closing the dialog, S_TRUE to close the dialog and accept the file
		// By default, filename length is checked.		
		virtual HRESULT HandleFileOk(IFileSaveDialog*);													
	
		// Clients should override these routines to react to provide custom behaviour for custom controls
		// Override to react when the custom control item like a radio button is selected, no-op by default
		virtual HRESULT HandleCustomControlItemSelected(IFileDialogCustomize*, DWORD ctrl, DWORD ctrlItem);	
		// Override to react when the custom button is clicked, no-op by default
		virtual HRESULT HandleCustomButtonClicked(IFileDialogCustomize*, DWORD ctrl);						
		// Override this to populate the menu items or list while the custom Tools menu is about to display its contents.	
		virtual HRESULT HandleControlActivating(IFileDialogCustomize*, DWORD ctrl);							
		// Override to react when the custom check box is clicked, no-op by default
		virtual HRESULT HandleCheckBoxToggled(IFileDialogCustomize*, DWORD ctrl, BOOL state);				
	protected:

		// 	Override this and return true if have custom controls
		virtual bool16 HasCustomControl()const;
		// Initialize the accessory view attributes/fields... 
		virtual HRESULT AddAndInitializeCustomControls(IFileDialogCustomize* pfdc);
		virtual HRESULT SetCustomControlsValues(IFileDialogCustomize* pfdc);

		virtual PMString GetSaveButtonLabel()const	{ return PMString();	}
		virtual PMString GetFileNameLabel() const	{ return PMString();	}

		// This method must be overridden if you have custom controls 
		// The provided window handle will never be NULL

		virtual void PreDoDialog(const IDFile *defaultFile, bool16 useSystemDefaultDir, bool16 showTypeMenu, const PMString* title);	// no-op by default
		virtual void PostDoDialog(bool16& dlgResult, IDFile *resultFile);			// no-op by default
		virtual HWND GetOwnerHandle();					// rarely overridden
		virtual void SetFilterString(std::vector<COMDLG_FILTERSPEC>& fileTypes);	// rarely overridden

		// These methods can be overridden so user of the dialog don't need to set them before calling DoDialog();
		virtual uint32 GetAdditionalFOSFlags();			// override this to set additional OPENFILENAME flags
		virtual PMString GetDefaultExtension();			// override this to set the default extenstion 
		virtual uint32 GetDefaultFilterIndex();			// override this to set the default filter index
		virtual PMString GetDefaultTitle();				// override this to change the default title

		virtual void GetInitialDirectory(const IDFile *defaultFile, bool16 useSystemDefaultDir, PMString *dir, PMString *file, uint32 *initialFilter);

		// nonvirtual utility functions
		// AllowReplaceSelf which shows the user a choice to replace the file, if user presses no, it is rejected
		HRESULT AllowReplaceSelf(IFileSaveDialog* pfsd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* fdShareResp);
		int32 AppendExtensionName(PMString *fileName, uint32 fFilterIndex);
		PMString GetFormatExtensionNameFromIndex(const uint32 index);

		uint32	fFilterIndex;

	private:
		
		void UpdateManagedFileNameControl();
		
		bool16 GetLocationLastUsed(PMString& dir);
		void SetLocationLastUsed(const IDFile& sysFile);

		bool16 GetComposedFilePath(IDFile* file);

		K2Lookup<PMString, PMString>	fExtensionList;
		IDFile*							fDefaultFile;
		uint32							fAdditionalFlags;
		PMString						fDefaultExtension;
		uint32							fDefaultFilterIndex;
	DECLARE_HELPER_METHODS()			
};
#pragma export off

#endif
