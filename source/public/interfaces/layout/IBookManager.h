//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookManager.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IBOOKMANAGER__
#define __IBOOKMANAGER__

#include "IPMUnknown.h"

#include "K2Vector.h"

#include "BookID.h"

class IBook;
class IDocument;

/** This interface is used to create, open, manage, and close books.
	The syntax for CreateBook (kNewBookCmdBoss), 
	OpenBook (kOpenBookCmdBoss), RecoverBook (kRecoverBookCmdBoss) 
	and CloseBook (kCloseBookCmdBoss)
	is similar to IDocumentList.

	@ingroup layout_book
	@see kSessionBoss
	@see IDocumentList
*/
class IBookManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKMANAGER };

		/**	 UI flag, used for handling missing plug-in conditions
		*/
		typedef enum 
			{ kAskMissing, /** ask the user how to handle missing plug-ins */
			  kIgnoreMissing, /** ignore any missing plug-ins */
			  kCancelMissing /** cancel open if there are default or critical plug-ins missing */
			} UIFlags;

		/**	Create a new book. The new book is added to the open book list in the book manager. 
		    This method starts a transaction on the newly created database that has to be ended 
			by the caller.
			@param whatBook IN the given name for the newly created book.
			@param protection IN DataBase's protection level, See IDataBase.h
			@param platformFileInfo IN (default=nil) only for MAC, store file creator type and and pub type. 
			@return IBook* newly created book.
		*/
		virtual IBook*   CreateBook(
							const IDFile& whatBook,  
							IDataBase::ProtectionLevel protection, 
							void* platformFileInfo = nil) = 0;

		/**	Open a book. The opened book is added to the open book list in the book manager. 
		    This method starts a transaction on the newly created database that has to be ended 
			by the caller.
			@param whatFile IN IDFile to open
			@param protection IN DataBase's protection level, See IDataBase.h 
			@param bAlreadyOpen OUT kTrue means book is already opened, otherwise, kFalse.
			@param bOpenExclusive IN if kFalse(default), open a copy file, otherwise, open original.
			@param alertMissingPlugIns IN UIFlag for dealing with missing plugins.
			@return IBook* the opened book.
		*/
		virtual IBook*   OpenBook(
							const IDFile& whatFile, 
							IDataBase::ProtectionLevel protection,
							bool16* bAlreadyOpen,
							bool16 bOpenExclusive = kFalse, 
							UIFlags alertMissingPlugIns = kAskMissing) = 0;

		/**	Recover and open a book identified by the given pubFile. 
			This method starts a transaction on the newly created database that
			has to be ended by the caller.
			@param pubFile IN IDFile to recover. 
			@param miniSaveFile IN IDFile stores mini save.
			@param protection IN DataBase's protection level. 
			@param fileInfo IN (default=nil) only for MAC, store file creator type and and pub type. 
			@return IBook* the recovered book.
		*/
		virtual IBook*   RecoverBook(
							const IDFile* pubFile, 
							const IDFile* miniSaveFile, 
							IDataBase::ProtectionLevel protection, 
							void* fileInfo = nil) = 0;

		/**	Close the given book.
			@param iBook IN the book to close.
		*/
		virtual void      CloseBook(IBook* iBook) = 0;

		/**	Close all opened books.
			@param none
		*/
		virtual void	  CloseAll() = 0;

		/**	Get nth book in the open book list.
			@param n IN index of of the document (0-based) 
			@return IBook* the nth open book.
		*/
		virtual IBook*    GetNthBook(int32 n) = 0;

		/**	Get the index of the given book.
			@param iBook IN the given book.
			@return int32 the index of the book (0-based).
		*/
		virtual int32     GetBookIndex(IBook* iBook) = 0;

		/**	Get number of open books
			@param none
			@return int32 the number of opened books.
		*/
		virtual int32     GetBookCount() = 0;

		/**	Get current active book in the open book list. There is only one active book.
			@param none
			@return IBook* the active book.
		*/
		virtual IBook*    GetCurrentActiveBook() = 0;

		/**	Set the given book as the active book.
			@param iBook the book to be set as active.
		*/
		virtual void      SetCurrentActiveBook(IBook* iBook) = 0;

		/**	Find the book with the given book file. Search to see if whatBook is 
		    already open or not.
			@param whatBook IN the book file to search.
			@return IBook* the result book. Returns nil means whatBook is not open.
		*/
		virtual IBook*    FindOpenBookByName(const IDFile& whatBook) = 0;

		/**	Utility function for checking if the given document is within current open books or not. 
			Currently, this is used in table of content for generating table of content 
			across book.
			@param doc IN the document to check.
			@param bookName OUT the book which the given document is IN.
			@return bool16 kTrue means the given document is in the open books, otherwise, return kFalse.
		*/
		virtual bool16	  IsDocumentWithinOpenBooks(IDocument* doc, PMString& bookName) = 0;
};

#endif //__IBOOKMANAGER__