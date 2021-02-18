//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookUtils.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "Utils.h"

class IPreflightOptions;
class IDocument;
class IDataBase;
class IPreflightBookOptions;
class IPreflightProcess;
class IPreflightBookData;
class IBook;
class RangeProgressBar;

/**	Utilities related to book preflight.
*/
class IPreflightBookUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKUTILS };

public:
	/** Given a book, get its active preflight data if there is an active preflight.
		@param iBook IN The book.
		@return A refcounted book data interface, or nil if there is no active preflight.
	*/
	virtual IPreflightBookData* QueryActivePreflight(IBook* iBook) const = 0;

	/** Given a book database, get its active preflight data if there is an active preflight.
		@param iBookDB IN The database of the book.
		@return A refcounted book data interface, or nil if there is no active preflight.
	*/
	virtual IPreflightBookData* QueryActivePreflight(IDataBase* iBookDB) const = 0;

	/** Given a book, get its active preflight options if there is an active preflight.
		@param iBook IN The book.
		@return A refcounted book options interface, or nil if there is no active preflight.
	*/
	virtual IPreflightBookOptions* QueryActivePreflightOptions(IBook* iBook) const = 0;

	/** Given a book database, get its active preflight options if there is an active preflight.
		@param iBookDB IN The database of the book.
		@return A refcounted book options interface, or nil if there is no active preflight.
	*/
	virtual IPreflightBookOptions* QueryActivePreflightOptions(IDataBase* iBookDB) const = 0;

	/** Determines whether a given set of document preflight options are set up compatibly with
		the specified book options. Compatible means the layer, pasteboard, and nonprinting 
		options are identical, and the options call for using the document's embedded profile
		if it has one.

		@param iBookOpts IN The book options to use as the baseline.
		@param iDocOpts IN The document options to compare. Can come from a document or process.
		@param iDocDB IN The document, if it is available. Slightly different rules apply if it
			is not, because we can't determine whether a document has an embedded profile if it's
			not available.
		@return kTrue if the options are compatible; kFalse if not.
	*/

	virtual bool AreBookAndDocOptionsCompatible
		(
			const IPreflightBookOptions* iBookOpts, 
			const IPreflightOptions* iDocOpts,
			IDataBase* iDocDB
		) const = 0;

	/** Given a document and some book options, create a new set of preflight options that should
		be used to configure the document for preflight for that book.

		@param iBookOpts IN The book options to use.
		@param iDocDB IN The document you're creating the options for. (Needed to get profile names
			and embedded profile information.)
		@return A refcounted in-memory preflight options set.
	*/
	virtual IPreflightOptions* CreateDocOptionsFromBookOptions
		(
			const IPreflightBookOptions* iBookOpts, 
			IDataBase* iDocDB
		) const = 0;

	/** Updates associations between a book's contents and the processes related to that book.
		This is called if you've made changes to the process or book state and want to re-sync.

		@param iBook IN The book that changed (or its processes).
	*/
	virtual void UpdateBookAssociations(IBook* iBook) const = 0;

	/** Updates associations between a document and any books it relates to. This is called when
		you've modified something about the database that the book should update in response to.
		@param iDocDB IN The affected document.
	*/
	virtual void UpdateBookAssociations(IDataBase* iDocDB) const = 0;

	/** Determines whether the given document is in the given book, and if so, returns its 
		content UID.
		@param iBook IN The book.
		@param iDocDB IN The document.
		@return The content UID in the book, or kInvalidUID if the document is not in the book.
	*/
	virtual UID FindDocumentInBook(IBook* iBook, IDataBase* iDocDB) const = 0;

	/** Examines the contents of the book, and if any have gone out of date or have come back
		into existence, updates the book preflight status accordingly.

		@param iBook IN The affected book.
	*/
	virtual void VerifyBookContentFileStates(IBook* iBook) const = 0;

	/** Examines the contents of all open books, and if any have gone out of date or have come back
		into existence, updates the book preflight status accordingly.
	*/
	virtual void VerifyBookContentFileStates() const = 0;

	/** Given a book content identifier, break the connection between the preflight book content
		data and the process supplying it. This will also delete the process if it's no longer
		needed (ie the document itself isn't open and this is the only book that was using the
		process).

		@param contentRef IN The book content.
	*/
	virtual void DisassociateContentProcess(const UIDRef& contentRef) const = 0;

	/** Returns a list of the books that are using a given process, ie have content for which
		the process is providing results.

		@param processID IN The ID of the process you're interested in.
		@param books OUT Receives the list of books. (These are not refcounted.)
	*/
	virtual void GetBooksUsingProcess(uint32 processID, K2Vector<IBook*>& books) const = 0;

	/** Analogous to ApplyOptionsToDocument; handles all internal status changes as a result.
	*/
	virtual ErrorCode ApplyOptionsToBook(IDataBase* iBookDB, const IPreflightBookOptions* iNewOpts) const = 0;

	/** Preflight a book
		@param iBook is the book to preflight.
		@param bookContentList is the list of book documents to preflight. 
				This could be one or more document in the book or the entire book content.
		@param iOptsToUse is the book preflight options to use.
		@param pProgressBar if not nil, a progress bar is shown and updated.
		@return the interface pointer to IPreflightBookData.
		@see IPreflightBookData.h
	*/
	virtual IPreflightBookData* DoBookPreflight(IBook* iBook, const UIDList& bookContentList, const IPreflightBookOptions* iOptsToUse, RangeProgressBar* pProgressBar = nil) const = 0;
};



