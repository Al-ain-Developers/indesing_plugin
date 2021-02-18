//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/MOpenFileDialogBase.h $
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
//  Info: This class is a base class for using Cocoa NSOpenPanel framework to open files.
//  It can be inherited to implement open file dialogs that have custom controls.
//  To do that, override following methods (see an example in MOpenDocDialog)
//  1. Define your custom view through interface builder and load nib using loadNibNamed
//     in the constructor itself.
//  2. Override InitializeAccessoryView().
//  3. Override GetAccessoryView() to return the custom view.
//	4. Override SetValuesFromAccessoryView().
//  
//========================================================================================

#pragma once
#ifndef __MOpenFileDialogBase__
#define __MOpenFileDialogBase__

#include "IOpenFileDialog.h"

#include "K2Vector.h"
#include "HelperInterface.h"
#include "K2Vector.h"
#include "K2SmartPtr.h"
#include "SysFileList.h"
#import  <Cocoa/Cocoa.h>

#pragma export on
@class MOpenPanelDelegate;
@class NSOpenPanel;
@class MOpenPanel;

//----------------------------------------------------------------------------------------
// MOPenFileDialogBase 
//----------------------------------------------------------------------------------------
class WIDGET_DECL MOpenFileDialogBase : public IOpenFileDialog
{
	public:
		MOpenFileDialogBase(IPMUnknown *boss);
		virtual ~MOpenFileDialogBase();
	
		virtual bool16 DoDialog(IDFile *defaultFile, SysFileList& resultFiles, bool16 allowMultipleFiles = kTrue, const PMString* title = nil, const PMString* infoMessage = nil);		
		virtual void AddExtension(const PMString *family, const PMString *extension);

		// override if you only want your dialog to select directories.
		virtual bool SelectDirectoriesOnly() const { return kFalse; } 

		// Mac only
		virtual void AddType(SysOSType theType);

		// Add the custom popup list names
		virtual void AddCustomMenu(const PMString& theName, SysOSType theType);
	
		// Override this if you want to handle the event of an entry's selection change in the browser list
		virtual void HandleEntrySelectionChange(id sender);
	
		// Overrride this to handle the event of directory location changed in the panel
		virtual void HandleDirectoryChange(NSString* dirName);
        
		//Internal Use Only. 
		//This method will launch uxp extension to open cloud docs.
        void LaunchCDPExtension();

	protected:		
		// This method must be overridden if you have custom controls 
		virtual void PreDoDialog(IDFile *defaultFile, bool16 allowMultipleFiles, const PMString* title, const PMString* infoMessage);	// no op by default
		virtual void PostDoDialog(bool16& dlgResult, SysFileList& resutlFiles);		// no op by default

		virtual void SetAdditionalDialogOptions();		// override this to set additional dialog options (e.g. adding more custom menu.)

		/* 
			In order to provide a customized set of widgets/view to the open dialog. 
			Client should override following routines  - 
			Define your custom view through interface builder and load nib using loadNibNamed in the constructor itself.
			HasCustomControl() - this routine should return true.
			InitializeAccessoryView() - clients should override this routine and initialize the widgets based on the values/prefs stored in the model.
			GetAccessoryView() - Our implementation expects client to return a valid NSView from this routine, if they have returned true in HasCustomControl().
			SetValuesFromAccessoryView() - clients shoud override this to save the values/prefs of the widgets in the custom view. This is called when the dialog is closed.
		*/
		
		// 	Override this and return true if have custom controls
		virtual bool16 HasCustomControl()const { return kFalse;}
		// Initialize the accessory view attributes/fields... 
		virtual void InitializeAccessoryView();
		// Get the accessory view for the open panel, override this to provide the custom made view ( clients may use interface builder ) 
		virtual NSView* GetAccessoryView()const;
		// Override this to process/set values from different widgets in custom view
		virtual void SetValuesFromAccessoryView();

		//Other customization routines for title of the dialog, Open button label etc.
		// override this to change the default title: "Open a File"
		virtual PMString GetDefaultTitle();
		// Get the value of Open button label, override this to change it to some other string
		virtual PMString* GetOpenButtonLabel()const;

		// Get the current directory
		virtual NSString* GetCurrentDirectory()const;

private:
		//----------------------------------------------------------------------------------------
		// Callbacks 
		//----------------------------------------------------------------------------------------	
		void InitDialogOptions(bool16 allowMultipleFiles, const PMString* title, const PMString* infoMessage);
		const CFURLRef CopyLocationLastUsed()const;
		void SetLocationLastUsed(const IDFile& sysFile);
			
	protected:
		bool16					fbUseUnicodeTitle;
		
	private:
		NSOpenPanel*				fOpenPanelRef;
		MOpenPanelDelegate*		fOpenPanelDelegate;
		NSAutoreleasePool*		fAutoreleasePool;
		int16					fCustomMenuLen;
		K2Vector<PMString>		fCustomMenuName;
		K2Vector<SysOSType>		fCustomMenuCreator;
		K2Vector<SysOSType>		fCustomMenuType;
		bool16					fShowAllFileTypes;
	DECLARE_HELPER_METHODS()			
};
#pragma export off

#endif
