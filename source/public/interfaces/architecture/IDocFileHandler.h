//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocFileHandler.h $
//  
//  Owner: Roey Horns
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
//  Purpose:	Interface for the handler of file related actions for an open document.
//  
//========================================================================================

#pragma once
#ifndef __IDOCFILEHANDLER__
#define __IDOCFILEHANDLER__

#include "DocumentID.h"
#include "IPMUnknown.h"


class IDocFileHandler : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDOCFILEHANDLER };
		
		// Should return kTrue if the document is modified or unsaved.
		virtual bool8 CanSave(const UIDRef& doc) = 0;		
		// Save the document.
		// If it is unsaved Save should call SaveAs
		virtual void Save(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;

		// Can save as.
		virtual bool8 CanSaveAs(const UIDRef& doc) = 0;
		// Save the doc as destFile.
		// If destFile is nil SaveAs should ask the user (if uiFlags allow) or fail.
		// The asStationery flag should be considered as Mac only and will only be honored
		// if destFile is not nil.
		virtual void SaveAs(const UIDRef& doc, const IDFile *destFile = nil,
												UIFlags uiFlags = kFullUI,
												bool8 asStationery = kFalse,
												FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID) = 0;

		// Can save a copy.
		virtual bool8 CanSaveACopy(const UIDRef& doc) = 0;
		// Save a copy of the doc as destFile.
		// If destFile is nil SaveACopy should ask the user (if uiFlags allow) or fail.
		// The asStationery flag should be considered as Mac only and will only be honored
		// if destFile is not nil.
		virtual void SaveACopy(const UIDRef& doc, const IDFile *destFile = nil,
												UIFlags uiFlags = kFullUI,
												bool8 asStationery = kFalse,
												FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID) = 0;

		// Can revert should return kFalse if the doc is unmodified or unsaved.
		virtual bool8 CanRevert(const UIDRef& doc) = 0;
		// Revert should ask the user (if uiFlags allow).
		virtual void Revert(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;

		// Can close.
		virtual bool8 CanClose(const UIDRef& doc) = 0;
		// Close should close any open window and finaly the document.
		// If uiFlags allow the user should get a chance to save a modified document.

		enum CloseCmdMode { kProcess, kSchedule };
		virtual void Close(const UIDRef& doc, UIFlags uiFlags = kFullUI, bool8 allowCancel = kTrue, CloseCmdMode cmdMode = kSchedule) = 0;


		// Methods implemented in a standard way by the default DocFileHandler. Other handlers
		// should call these to insure consistent behavior.

		// Check to see if the file is dirty on close and, if so, ask the user whether
		// it should be saved.
		enum CloseOptions { kSave, kDontSave, kCancel, kSaveVersion, kJustSaveVersion };
		virtual CloseOptions CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel) = 0;
		// Get the appropriate default SaveAs file name.
		virtual void GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir) = 0;

		// FOR INTERNAL USE ONLY! Very Similar to SaveAs method.
		// Instead of destfile, pass in a filename, that will be shown pre-populated in the SaveAs dialog.
		virtual void SaveAs2(const UIDRef& doc, const PMString& fileName, UIFlags uiFlags = kFullUI, 
			bool8 asStationery = kFalse, FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID) = 0;
};

#endif //__IDOCFILEHANDLER__
