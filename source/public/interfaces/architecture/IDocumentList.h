//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentList.h $
//  
//  Owner: Robin_Briggs
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
//  Purpose of Interface:
//  Create, open, manage, and close documents
//  
//========================================================================================

#pragma once
#ifndef __IDOCUMENTLIST__
#define __IDOCUMENTLIST__

#include "IPMUnknown.h"
#include "DocumentID.h"
#include	"IDocument.h"

/**	 IID_IDOCUMENTLIST interface 
				 store a list of open documents.
 */
class IDocumentList : public IPMUnknown
{
public:
	/**	 UI flag, used for handling missing plug-in conditions
	 */
	enum UIFlags { 
		kAskMissing, 		/** ask the user how to handle missing plug-ins */
		kIgnoreMissing, 	/** ignore any missing plug-ins */
		kCancelMissing, 	/** cancel open if there are default or critical plug-ins missing */
		kForceIgnoreMissing, /** force ignore of missing plug-ins for this and all subsequent opens of this doc */
		kDontCheck 			
		};
	/**	 Get number of open documents. Headless documents are counted.
		@param bClosePlacedINDDFiles: If kTrue, closes any placed INDD files that may be opened, before counting the number of opened documents
		@return int32 the number of documents in the list
		@see ILayoutUIUtils.h, GetUIDocumentWindowCount
	 */
	virtual int32 GetDocCount(bool16 bClosePlacedINDDFiles = kFalse) const = 0;

	/**	 Get n'th document
		@param n index of of the document (0-based) 
		@return IDocument  the n'th document
	 */
	virtual IDocument * GetNthDoc(int32 n) = 0;

	/**	 Find the document with the document file.
					 Search  to see if one (whatFile) is already open. If so, return it
		@param whatFile IDFile. 
		@return IDocument the open documents 
	 */
	virtual IDocument *FindDoc(const IDFile& whatFile) const = 0;

	/**	 Find the document with the database.
					 Search  to see if one (db) is already open. If so, return it
		@param db IDataBase. 
		@return IDocument the open documents 
	 */
	virtual IDocument *FindDocByDataBase(IDataBase* db) const = 0;

	/**	Search the open documents to see if one is already open(document could be previous version). If so, return it.
		@param whatFile IDFile
		@return IDocument the open document
	 */
	virtual IDocument *FindDocFromPreviousVersion(const IDFile& whatFile) = 0;
	

	/**	 Create a new document. The new document is added to the document list.
					This method starts a transaction on the newly created database that
					has to be ended by the caller.
	  
		@note Third Party Developers should use a command (such as kNewDocCmdBoss) instead. IDocumentCommands contains command generator methods for convenience.
		@see IDocumentCommands.h
		
		@param docClassID Document boss's class id 
		@param protection DataBase's protection level, See IDataBase.h
		@param fileInfo (default=nil) for MAC, store file creator type and and pub type 
		@param undoSupport (default=IDocument::kFullUndoSupport), indicates whether commands that change the document will appear on the undo menu

		@return IDocument newly created document 

	 */
	virtual IDocument * NewDoc(const ClassID& docClassID, IDataBase::ProtectionLevel protection, void* fileInfo = nil, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;

	/**	 Open a document; The new document is added to the document list;
					This method starts a transaction on the newly created database that
					has to be ended by the caller.
		
		@note Third Party Developers should use a command (such as kOpenDocCmdBoss) instead. IDocumentCommands contains command generator methods for convenience.
		@see IDocumentCommands.h
		
		@param whatFile IDFile to open 
		@param protection DataBase's protection level, See IDataBase.h 
		@param bOpenOriginal if kTrue(default), open original file
							  otherwise, open a copy	
		@param alertMissingPlugIns UIFlag, default = kAskMissing, alert if missing plugin is detected. 
									kIgnoreMissing, Ignore missing plugin
									kCancelMissing, Cancel open when missing plugin
									kIgnoreMissing, Don't alert on missing plugin data from file
									kDontCheck, don't check missing plugins
		@param bUseLockFile default = kTrue, if use lock file 
		@param undoSupport (default=IDocument::kFullUndoSupport), indicates whether commands that change the document will appear on the undo menu
		@return IDocument opened document 
	 */
	virtual IDocument * OpenDoc(const IDFile& whatFile, IDataBase::ProtectionLevel protection, bool16 bOpenOriginal = true, UIFlags alertMissingPlugIns = kAskMissing, bool16 bUseLockFile = kTrue, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;

	// For Private Use Only
	/**	 Open a document clone; The new document is added to the document list;		
		@param db IDataBase
		@param docName name to use for the document
		@return IDocument opened document 
	 */
	virtual IDocument * OpenDocClone(IDataBase*db, const PMString& docName) = 0;

	/**	 Recover and open a document identified by recoveryID
					This method starts a transaction on the newly created database that
					has to be ended by the caller.
		
		@note Third Party Developers should use a command (such as kRecoverDocumentCmdBoss) instead. IDocumentCommands contains command generator methods for convenience.
		@see IDocumentCommands.h
		
		@param pubFile IDFile to recover 
		@param miniSaveFile IDFile stores mini save 
		@param protection DataBase's protection level 
		@param fileInfo (default=nil) for MAC, store file creator type and and pub type 
		@param bIsFauxUserFile(default= kFlase), if is faux user file, (currently, incopy user file) 
		@param undoSupport (default=IDocument::kFullUndoSupport), indicates whether commands that change the document will appear on the undo menu
		@return IDocument recovered document
	 */
	virtual IDocument * RecoverDoc(const IDFile* pubFile, const IDFile* miniSaveFile, IDataBase::ProtectionLevel protection, void* fileInfo = nil, bool16 bIsFauxUserFile = kFalse, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;

	/**	  Close the document
	  
		@note Third Party Developers should use a command (such as kCloseDocCmdBoss) instead. IDocumentCommands contains command generator methods for convenience.
		@see IDocumentCommands.h
		
	    @param doc Document to close 
	 */
	virtual void CloseDoc(IDocument * doc) = 0;

	// For Private Use Only
	/**	  Close document clone		
	    @param doc Document to close 
	 */
	virtual void CloseDocClone(IDocument * doc) = 0;

	/**	 Close all open documents
		@param none
	 */
	virtual void CloseAll() = 0;
	

	/**	 Purges unused memory in each of the documents
		@param level  levels from MemUtils.h
	 */
	virtual void PurgeMemory(int32 level) = 0;
};

#endif
