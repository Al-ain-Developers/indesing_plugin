//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenFileCmdData.h $
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
//  Purpose:	Parameters used to open a file
//  
//========================================================================================

#pragma once
#ifndef __IOpenFileCmdData__
#define __IOpenFileCmdData__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"
#include "IImportProvider.h"
#include "IDocument.h"
/**
  This interface is used to cache data for open file related command such as kOpenDocCmdBoss, 
  kOpenRevertedDocCmdBoss, kInCopyOpenDocCmdBoss, kOpenFileCmdBoss, kOpenFileWithWindowCmdBoss 
  and kOpenDocFromBookCmdBoss.
*/

class IOpenFileCmdData : public IPMUnknown
{
public:
	/**
		Initialize the settings of this object from the settings of the 'data' object. It acts as 
		a copy constructor.

		@param data refers to the object used to be copied from.
		@return void.
	*/
	virtual void Set(const IOpenFileCmdData &data) = 0;

	/**
		Define the open options. 
	*/
	typedef enum { kOpenDefault, kOpenOriginal, kOpenCopy } OpenFlags;

	/**
		Define the lock options.
	*/
	typedef enum { kUseLockFile, kNotUseLockFile } LockFlags;
	
	/**
		Set the command data through the individual setting.

		@param file refers to the sysFile to import.
		@param uiFlags refers to how much UI to show during import.
		@param openFlags refers to the open option about how you open the file.
		@param lockFlags refers to the lock option determining whether a lock file will be used or not when open.
		@param undoSupport (default=IDocument::kFullUndoSupport), indicates whether commands that change the document 
				(if this is an InDesign/InCopy document) will appear on the undo menu

		@return void.
	*/
	virtual void Set(const IDFile &file, UIFlags uiFlags = kFullUI, OpenFlags openFlags = kOpenDefault, LockFlags lockFlags = kUseLockFile, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;

	/**
		Get the sysfile to import.

		@return const IDFile& file to import.
	*/
	virtual const IDFile &GetSysFile() const = 0;

	/**
		Get the UI flags about how much UI to show during import.

		@return UIFlags which could be kSuppressUI, kMinimalUI and kFullUI.
	*/
	virtual UIFlags GetUIFlags() const = 0;

	/** Set the UI flags */
	virtual void SetUIFlags(UIFlags uiFlags) = 0;

	/**
		Get the open option about how you open the file.

		@return OpenFlags which could be kOpenDefault, kOpenOriginal and kOpenCopy.
	*/
	virtual OpenFlags GetOpenFlags() const = 0;

	/**
		Get the lock option determining whether a lock file will be used or not when open.

		@return LockFlags which could be either kUseLockFile or kNotUseLockFile.  
	*/
	virtual LockFlags GetLockFlags() const = 0;


	/**
		Get the undo support option @see IDocument.

		@return IDocument::UndoSupport.  
	*/
	virtual IDocument::UndoSupport GetUndoSupport() const = 0;
};

#endif
