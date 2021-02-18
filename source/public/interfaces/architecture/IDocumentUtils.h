//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentUtils.h $
//  
//  Owner: hhorton
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
#ifndef _H_IDocumentUtils
#define _H_IDocumentUtils

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "Utils.h"

class IDocFileHandler;
class IDocument;
class PMString;
class Sysfile;


/**	Interface containing various utility methods for documents.
 */
class IDocumentUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDOCUMENTUTILS };
		
		/** Close options for the CloseAll method.
		*/
		enum WhatToClose {
			kCloseDocOnly =					(1 << 0),
			kCloseLibrariesOnly =			(1 << 1),
			kCloseBooksOnly =				(1 << 2),
			kCloseBooksAndLibrariesOnly =	(kCloseBooksOnly | kCloseLibrariesOnly),
			kCloseDocAndBooks =				(kCloseDocOnly | kCloseBooksOnly),
			kCloseDocAndLibraries =			(kCloseDocOnly | kCloseLibrariesOnly),
			kCloseAll =						(kCloseDocOnly | kCloseBooksOnly | kCloseLibrariesOnly)
		};

		/** File Size Optimization options.
		*/
		enum {
			kCropProxyImages =				(1 << 0),
			kResampleProxiesOfScaledImages=	(1 << 1),
			kDeleteUnusedMasterPages =		(1 << 2),
			kDeleteUnusedSwatches =			(1 << 3),
			kDeleteUnusedXMLTags =			(1 << 4),
			kDeleteUnusedLayers =			(1 << 5),
			kOptimizeEverything =			0xFFFF
		};

		/** Prompt options for saving modified documents before close.
		*/
		enum PromptForSave { kDontSaveAll, kAsk, kSaveAll, kSaveAllDontAsk } ;

		/**	Check if the document is saved before close document window, 
						 if the document is modified, prompt for save.
			@param doc The document about to close
			@param allowCancel if allow cancel save 
			@return kTrue if the document is not modified or is saved
							kFalse if document is modified and save is cancelled.
		 */
		virtual bool16 		CheckOnClose(IDocument *doc, bool16 allowCancel = kTrue) = 0;

		/**	Save the document as a new file. Will brought up save as dialog
						 by calling IDocFileHandler::SaveAs()
			@param doc The document to save as
			@return Global Errorcode after save-as.
		 */
		virtual ErrorCode 	DoSaveAs(IDocument *doc) = 0;

		/**	Save the document
			@param doc The document to save 
			@return Global Errorcode after save 
		 */
		virtual ErrorCode 	DoSave(IDocument *doc) = 0;

		/**	Save document a copy. 
		                 The differences between SaveACopy and SaveAs are:
						 \li SaveACopy() save another copy to disk, IDocument still refers to current document
						 \li SaveAs() leave current document unchanged (and closed), but IDocument refers to newly saved file.
			@param doc the document to save a copy 
			@return Global ErrorCode after SaveACopy
		 */
		virtual ErrorCode 	DoSaveACopy(IDocument *doc) = 0;

		/**	If any open document is modified
			@return kTrue if any opend document is modifed, otherwise kFalse 
		 */
		virtual bool16 		IsAnyDocModified(void) = 0;

		/**	Save all documents
			@return kTrue if all document successfully save
					kFalse if any error ocuurred during save, (and leaving remaining document not saved)
		 */
		virtual bool16 		SaveAll(void) = 0;

		/**	Save all modified document
			@param abortOnErr if kTrue, stop saving other documents when error occurs 
							   if kFalse(default), contunue to save other documents when encounter an error
			@param reportErrs if kTrue, bring up alert when error
								if kFalse, don't alert	
			@param saveUntitled if kTrue, also save Untitled (never saved) documents
								 if kFalse, don't save Untiled documents 
			@return If all modified document saved without error. 
		 */
		virtual bool16 		SaveAllModified(bool16 abortOnErr = kFalse, bool16 reportErrs = kFalse, bool16 saveUntitled = kFalse) = 0;

		/**  CloseAll closes all open documents.  This optionally includes books and libraries.

			@param allowCancel Can this close be cancelled.
			@param prompt Should users be allowed to save modified documents.
			@param closeWhat [IN] -  Indicates which combination of Document, Books and Libraries to close.
			@return kTrue if the operation was succesful, kFalse if an error ocurred.
			@postcondition All documents up until error will be closed.
		*/
		virtual bool16 		CloseAll(bool16 allowCancel = kTrue, bool16 prompt = kTrue, WhatToClose closeWhat = kCloseDocOnly) = 0;

		/** Process close all documents, books, and libraries, then schedule a quit of the application.
			@param allowCancel Can this close be cancelled.
			@param prompt Should users be allowed to save modified documents.
			@return kSuccess or an error code.
		*/
		virtual ErrorCode	ProcessCloseAllAndQuit( bool16 allowCancel = kTrue, PromptForSave prompt = kAsk ) = 0 ;

		/** Schedule close all documents, books, and libraries, then schedule a quit of the application.
			@param allowCancel Can this close be cancelled.
			@param prompt Should users be allowed to save modified documents.
			@param priority at which the scheduled command should be processed.
			@return kSuccess or an error code.
		*/
		virtual ErrorCode	ScheduleCloseAllAndQuit( bool16 allowCancel = kTrue, PromptForSave prompt = kAsk, ICommand::Priority priority = ICommand::kLowPriority ) = 0 ;

		/**	Query DocFileHandler of the document. This mean we may
						 have different DocFileHanders which could be specified in IID_ICLASSIDDATA in DocumentBoss
			@param doc the document UIDRef 
			@return IDocFileHandler for the given document.
		 */
		virtual IDocFileHandler *QueryDocFileHandler(const UIDRef &doc) = 0;
	
#ifdef DEBUG

		/**	Check document after open. 3rd party may overwrite this add any check
			@param file document file 
			@param db The database after file open 
			@return ErrorCode. Check result. 
		 */
		virtual ErrorCode	CheckAfterOpen(const IDFile& file, IDataBase *db) = 0;

		/**	Check document before close. Such as CheckForLeaks
			@param db The database of the document 
			@return ErrorCode. Check result.
		 */
		virtual ErrorCode	CheckBeforeClose(IDataBase *db) = 0;

		/**	Check for leaks
			@param db The database of the document  
			@return if the document has memory leaks 
		 */
		virtual bool8 		CheckForLeaks(IDataBase *db) = 0;


#endif
		virtual IDataBase::DBResultCode DocDBCallback(int32 stepsDone, int32 stepCount) = 0;

		/** Attempt to decrease the total binary file size of the given document.
			@param doc [IN]: The document to optimize.
			@param options [IN]: How to optimize
			@return true if optimizations were found, false otherwise.
		*/
		virtual bool		OptimizeForSize(IDocument *doc, uint32 options) = 0;

		/** FOR INTERNAL USE ONLY. Log the database open failure and set the global error state
			@param errCode [IN]: the errorCode to set
			@param db[IN]: The database of the document 
		*/ 
		virtual void LogAndSetDBError(ErrorCode errCode, IDataBase* db) = 0;

		/** FOR INTERNAL USE ONLY. Log the database open failure and set the global error state
			@param errCode [IN]: the errorCode to set
			@param db[IN]: The database of the document 
		*/ 
		virtual void LogAndSetDBError(ErrorCode errCode, const IDFile *file, IDataBase* db) = 0;
    
        /** Gets the missing font list from the document which are available on TypeQuest
            @param doc [IN]: The document to get missing font list from.
            @param fontAvailableOnTQ [IN]: Vector to store missing fonts list on TQ
         */
        virtual void GetTQMissingFontsOnDoc(IDocument* doc, std::vector<std::string> &fontAvailableOnTQ) = 0;

		/**	Validate document structures
			@param db The database of the document
			@param validateClassID ClassID for validator Boss, for specific validation, 0 for all registered validators.
			@return ErrorCode. Check result.
		 */
		virtual ErrorCode	ValidateDocumentStructures(IDataBase* db, ClassID validateClassID = 0) = 0;
    
};

#endif	/* _H_IDocumentUtils */
