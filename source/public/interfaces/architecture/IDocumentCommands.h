//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentCommands.h $
//  
//  Owner: chris parrish
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
//  Functions to aid in InCopy Document file actions
//  
//========================================================================================

#pragma once
#ifndef __IDocumentCommands__
#define __IDocumentCommands__

#include "IPMUnknown.h"
#include "IDocument.h"
#include "IOpenFileCmdData.h"
#include "IPageSetupPrefs.h"

#include "PMPageSize.h"

#include "DocFrameworkID.h"

class IDocumentCommands : public IPMUnknown
{
public:
		enum	{kDefaultIID = IID_IDOCUMENTCOMMANDS};
		
		enum DocSizePreset
		{
			kInvalidPreset = -1,
			kCustomPreset,
			kLetterPortrait,
			kA4Portrait,
			kA4Landscape,
			kWebLandscape,
			kWebCommonLandscape,
			kiPhone5Portrait,
			kiPhone6Portrait,
			kiPhone6PlusPortrait,
			kiPadPortrait,
			kiPadLandscape,
			kTabloidPortrait,
			kBusinessCardLandscape,
			kAndroidLandscape,
			kSurfacePro3Landscape,
		};

		struct DocSizePresetSettings
		{
			DocSizePresetSettings()
				:
				fPageSize(kPMPageSizeEmpty),
				fWideOrientation(kFalse),
				fDocIntent(kUnchangedIntent),
				fFacingPage(kFalse),
				fPrimaryTextFrame(kFalse)
			{}

			PMPageSize		fPageSize;
			bool16			fWideOrientation;
			DocumentIntent	fDocIntent;
			bool16			fFacingPage;
			bool16			fPrimaryTextFrame;
		};

		//----- Creation
		//
		// Any code looking to issue a document related command needs
		// to use this interface
		
		// Execute (process) the appropriate commands depending on the product
		virtual 	ErrorCode		New(UIDRef *result, UIFlags uiFlags = kFullUI, PMString* styleToUse = nil,
										IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;
		virtual		ErrorCode	 	Open(UIDRef *result, const IDFile &file, UIFlags uiFlags = kFullUI, 
											IOpenFileCmdData::OpenFlags openFlags = IOpenFileCmdData::kOpenDefault, 
											IOpenFileCmdData::LockFlags lockFlags = IOpenFileCmdData::kUseLockFile, 
											bool16 showInWindow = kTrue,
											IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;
		virtual		ErrorCode	 	Save(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;
		virtual		ErrorCode	 	SaveAs(const UIDRef& doc, const IDFile& destFile, UIFlags uiFlags = kFullUI) = 0;
		virtual		ErrorCode	 	Close(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;

		// Return the appropriate commands depending on the product
		virtual		ICommand*	 	CreateOpenCommand(const IDFile &file, UIFlags uiFlags = kFullUI, 
											IOpenFileCmdData::OpenFlags openFlags = IOpenFileCmdData::kOpenDefault, 
											IOpenFileCmdData::LockFlags lockFlags = IOpenFileCmdData::kUseLockFile, 
											bool16 showInWindow = kTrue,
											IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;
		virtual		ICommand*		CreateNewCommand(UIFlags flags = kFullUI, PMString* styleToUse = nil, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;
		virtual		ICommand*		CreateSaveCommand(const UIDRef& docToClose, UIFlags uiFlags = kFullUI) = 0;
		virtual		ICommand*		CreateSaveAsCommand(void) = 0;
		virtual		ICommand*		CreateSaveACopyCommand(void) = 0;		
		virtual		ICommand*		CreateCloseCommand(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;
		virtual		ICommand*		CreateRecoverCommand(IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport)  = 0;
		virtual		ICommand*		CreateOpenRevertedCommand(void) = 0;
		virtual		ICommand*		CreatePreRevertCommand(void)= 0;
        virtual     ICommand*       CreateVerifierRecoverCommand(IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport)  = 0;
		
		//----- Identification
		//
		// Any code looking to take an action based on the type of a document command
		// (Observers, responders, ...) should pass the commandID
		// here and use the result to determine how to respond
		// This is necessary for allowing SI's to replace these commands
		// with their own versions that may have a different ID
		//
		// SI's are free to reimplement this methods as necessary for their workflows

		// Currently only identify InDesign commands. InCopy 2.0 did not 
		// modify observers to look for InCopy commands. If necessary
		// this can be modified for the 3.0 products.
		
		virtual		bool8			IsOpenCommand(ClassID commandID) = 0;
		virtual		bool8			IsNewCommand(ClassID commandID) = 0;
		virtual		bool8			IsSaveCommand(ClassID commandID) = 0;
		virtual		bool8			IsSaveAsCommand(ClassID commandID) = 0;
		virtual		bool8			IsSaveACopyCommand(ClassID commandID) = 0;
		virtual		bool8			IsCloseCommand(ClassID commandID) = 0;
		virtual		bool8			IsRecoverCommand(ClassID commandID) = 0;
		virtual		bool8			IsPreRevertCommand(ClassID commandID) = 0;
		virtual		bool8			IsOpenRevertedCommand(ClassID commandID) = 0;
		
		// Return the appropriate commands depending on the product
		virtual		ICommand*		CreateNewCommandUsingPreset(DocSizePreset preset, const DocSizePresetSettings &customSettings = DocSizePresetSettings()) = 0;
};

#endif //__IDocumentCommands__
