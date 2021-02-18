//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/MSaveFileDialogBase.h $
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
//  Info: This class is a base class for using Cocoa NSSavePanel framework to save files.
//  It can be inherited to implement save file dialogs that have custom controls.
//  To do that, override following methods (see an example in MSaveDocDialog)
//  1. Define your custom view through interface builder and load nib using loadNibNamed
//     in the constructor itself.
//  2. Override InitializeAccessoryView().
//  3. Override GetAccessoryView() to return the custom view.
//	4. Override SetValuesFromAccessoryView().
//  
//========================================================================================

#pragma once
#ifndef __MSaveFileDialogBase__
#define __MSaveFileDialogBase__

// ----- Interfaces -----

#include "ISaveFileDialog.h"

// ----- Includes -----

#include "HelperInterface.h"
#include "K2Vector.h"
#include "SysFileList.h"
#import <Cocoa/Cocoa.h>

#pragma export on
@class MSavePanelDelegate;
@class MSavePanel;

//----------------------------------------------------------------------------------------
// MSaveFileDialogBase 
//----------------------------------------------------------------------------------------
class WIDGET_DECL MSaveFileDialogBase : public ISaveFileDialog
{
	public:
	
		MSaveFileDialogBase(IPMUnknown *boss);
		~MSaveFileDialogBase();
		
		virtual bool16 DoDialog(const IDFile *defaultFile, IDFile* resultFile, int32* selectedIndex, bool16 useSystemDefaultDir, bool16 showTypeMenu, const PMString* title);		

		virtual void AddFileTypeInfo(const PMString &description, const PMString &extension);
	
		// For Internal use only
		// Called by the delegate to validate the filename at the native filesystem
		bool16 ValidateSaveFileName(NSURL* fileName);

		// For Internal use only
		// Called by the extension popup list handler, on value change of popup
		void ExtensionSelectionChange(NSInteger extIndex, NSString* formatName);

		//Internal Use Only. 
		//This method will launch uxp extension to save cloud docs.
        void OpenCDPExtension();
				
	protected:

		virtual void PreDoDialog(const IDFile *defaultFile, bool16 useSystemDefaultDir, const PMString* title);	// no op by default
		virtual void PostDoDialog(bool16& dlgResult, IDFile* resultFile);		// no op by default
		
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
		virtual bool16 HasCustomControl()const;
		// Initialize the accessory view attributes/fields... 
		virtual void InitializeAccessoryView();
		// Get the accessory view for the open panel, override this to provide the custom made view ( clients may use interface builder ) 
		virtual NSView* GetAccessoryView()const;
		// Override this to process/set values from different widgets in custom view
		virtual void SetValuesFromAccessoryView();

		//Other customization routines for title of the dialog, Save button label etc.
		// Override this to change the default title: "Save As"
		virtual PMString GetDefaultTitle();
		// Get the value of save button label, override this to change it to some other string
		virtual PMString* GetSaveButtonLabel()const;
	
		// Override this to check the result file is valid or not. 
		// Based on kFalse value, the panel will be kept open waiting for other save file name 
		virtual bool16 IsValidSaveIDFile(const IDFile& resultFile);
	
		// Override this to handle the extension selection change at the extension popup list
		virtual void HandleExtensionSelectionChange(NSInteger extIndex, NSString* formatName);

		virtual void InitDialogOptions(const IDFile *defaultFile, const PMString* title, PMString& defaultFileName);	// rarely overriden

	private:
		const CFURLRef CopyLocationLastUsed() const;
		void SetLocationLastUsed(const IDFile& sysFile);
		void Setup();
		void Cleanup();

	private:
		class SaveFileTypeInfo
		{
			public:
				typedef	object_type data_type;
			
			public:
				SaveFileTypeInfo(const PMString &description, const PMString &extension)
					: fDesc(description), fExt(extension)
					{}
				SaveFileTypeInfo(const SaveFileTypeInfo &other)
					{Copy(other);}
					
				~SaveFileTypeInfo()
					{}
					
				SaveFileTypeInfo &operator=(const SaveFileTypeInfo &other)
					{Copy(other); return *this;}
					
				PMString GetDescription() const
					{return fDesc;}
				PMString GetFileExtension() const
					{return fExt;}
					
				bool operator==(const SaveFileTypeInfo &other)
					{return (fDesc == other.fDesc);}
				bool operator!=(const SaveFileTypeInfo &other)
					{return !(*this == other);}
				
			private:
				void Copy(const SaveFileTypeInfo &other)
					{fDesc = other.fDesc; fExt = other.fExt;}
					
			private:
				PMString	fDesc;
				PMString	fExt;
		};
				
	private:
		NSSavePanel*					fSavePanelRef;
		MSavePanelDelegate*			fSavePanelDelegate;
		NSAutoreleasePool*			fAutoreleasePool;
		K2Vector<SaveFileTypeInfo>	fFileTypeInfoList;
		int32						fInfoListIndex;	
	DECLARE_HELPER_METHODS()

};
#pragma export off


#endif
