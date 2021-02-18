//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightManager.h $
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
//  
//  This is the main entry point into the preflight architecture.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "IPreflightProfileManager.h"
#include "IPreflightObjectModel.h"
#include "IPreflightProcessManager.h"
#include "IPreflightRuleManager.h"

#include "PackageAndPreflightID.h"

class IDocument;
class IPreflightSettingsChangeInfo;

/** The preflight manager is the "top level" interface for everything related to preflight.
	It sits on the session, or you can get to it more safely by

		InterfacePtr<IPreflightManager> iMgr(Utils<IPreflightUtils>()->QueryPreflightManager());

	Mostly it (a) serves up other interesting interfaces, (b) implements a document/DB/file
	map for relating results to a particular document (even if that document has been closed),
	and (c) implements various bottlenecks related to document open/close/save/etc to
	maintain that map.
*/
class IPreflightManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTMANAGER };

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////

	/** Called by the global startup/shutdown mechanism; you should never need to call this.
	*/
	virtual void Startup() = 0;

	/** Called by the global startup/shutdown mechanism; you should never need to call this.
	*/
	virtual void Shutdown() = 0;

	/** Obtain a profile manager for the provided document. The profile manager maintains the
		list of profiles in the document (or application defaults if iDoc is nil).

		@param iDoc IN The document you're interested in, or nil for the application defaults.
		@return A refcounted preflight profile manager interface or nil if there was a problem.
	*/
	virtual IPreflightProfileManager* QueryProfileManager(IDocument* iDoc) const = 0;

	/** Obtain a profile manager for the provided database. The profile manager maintains the
		list of profiles in the document (or application defaults if db is nil).

		@param db IN The database you're interested in, or nil for the application defaults.
		@return A refcounted preflight profile manager interface or nil if there was a problem.
	*/
	virtual IPreflightProfileManager* QueryProfileManager(IDataBase* db) const = 0;

	/** Get the object model (a singleton for now). The preflight object model is responsible
		for building parallel versions of the document for preflight purposes.

		@return A refcounted preflight object model interface. This should never fail except in 
				truly dire circumstances.
	*/
	virtual IPreflightObjectModel* QueryObjectModel() const = 0;

	/** Get the process manager (a singleton for now). The process manager maintains the list
		of active preflight processes (document inspections).

		@return A refcounted IPreflightProcessManager interface. This should never fail except in 
				truly dire circumstances.
	*/
	virtual IPreflightProcessManager* QueryProcessManager() const = 0;

	/** Get the rule manager (a singleton for now). The rule manager maintains the rule ID to
		service mapping along with anything we care to cache about rules.

		@return A refcounted IPreflightProcessManager interface. This should never fail except in 
				truly dire circumstances.
	*/
	virtual IPreflightRuleManager* QueryRuleManager() const = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////

	/** Document ID database. There will be cases, in particular for book preflight, where we are
		going to need to record results for documents that are not open at the moment. So we can't
		just record a database with the preflight objects; we need some way of remembering which
		database/document an object was associated with so we can reopen it later (and/or associate
		it with a re-opened document). Thus this simple database, which just accumulates a list of
		the documents we visit. As observers note new, opened, and saved documents, this database
		is updated automatically.
	*/

	/** Given a document in memory, obtain its corresponding ID. 

		@note This is a TEMPORARY ID useful only during the current application launch. The ID
			will track the document even if it is closed and reopened later, as long as the file
			name hasn't changed in the meantime.

		@param iDoc IN The document you're interested in.
		@return The ID of the corresponding document.
	*/
	virtual PreflightDocumentID GetDocumentID(const IDocument* iDoc) const = 0;

	/** Given a document database in memory, obtain its corresponding ID. 

		@note This is a TEMPORARY ID useful only during the current application launch. The ID
			will track the document even if it is closed and reopened later, as long as the file
			name hasn't changed in the meantime.

		@param iDB IN The database of the document you're interested in.
		@return The ID of the corresponding document.
	*/
	virtual PreflightDocumentID GetDocumentID(const IDataBase* iDB) const = 0;

	/** Given a document ID, obtain an IDocument for it, optionally forcing the document to be 
		reopened if it's not in memory.

		@param docID IN The ID of the document you need access to.
		@return A refcounted IDocument interface, or nil if the document is not in memory or the ID is invalid.
	*/
	virtual IDocument* QueryDocument(PreflightDocumentID docID, bool forceLoadDocument = kFalse) const = 0;

	/** Given a document ID, obtain an IDataBase for it, optionally forcing the document to be 
		reopened if it's not in memory.

		@param docID IN The ID of the document you need access to.
		@return A NON-refcounted IDataBase interface, or nil if the document is not in memory or the ID is invalid.
	*/
	virtual IDataBase* GetDataBase(PreflightDocumentID docID, bool forceLoad = kFalse) const = 0;

	/** Given a document ID, obtain a path to it, whether or not the document is currently open.

		@note New documents that have not been saved will not have a path.

		@param docID IN The ID of the document you need access to.
		@return The file.
	*/
	virtual IDFile GetFile(PreflightDocumentID docID) const = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////

	enum NewOpenMode 
	{ 
		/** Disable all open/new behaviors. 
		*/
		kNewOpenOff,

		/** Apply normal behaviors, according to application default preferences.
		*/
		kNewOpenNormal,

		/** Apply behaviors appropriate for opening a document from a book command. If the book
			is in preflight mode we inherit the book's preflight settings, not the standard ones.
		*/
		kNewOpenBook
	};

	/** Set the behavior that should apply for new/open commands. This defaults to kNewOpenNormal and
		shouldn't be changed except temporarily. Currently used by the book-doc open command to override
		the standard behaviors.

		@param newMode IN The new mode.
	*/
	virtual void SetNewOpenMode(NewOpenMode newMode) = 0;

	/** Set the behavior that should apply for new/open commands.
		@return The mode.
	*/
	virtual NewOpenMode GetNewOpenMode() const = 0;

	/** Called when a document is opened, as determined by a document list observer. In general
		you shouldn't need to call this. The manager responds by determining what action should
		be taken, such as automatically creating a preflight process.

		@param iDoc The document just opened.
	*/
	virtual void OnOpenDocument(IDocument* iDoc) = 0;

	/** Called when a document is opened via the book panel, as determined by a document list 
		observer. In general you shouldn't need to call this. The manager responds by configuring
		preflight for the document if the book has an active preflight configured.

		@param iDoc The document just opened.
	*/
	virtual void OnOpenDocumentFromBook(IDocument* iDoc) = 0;

	/** Called when a document is opened, as determined by a document list observer. In general
		you shouldn't need to call this. The manager responds by creating a preflight process if
		applicable; it also updates the document database (see above).

		@param iDoc The document just opened.
	*/
	virtual void OnNewDocument(IDocument* iDoc) = 0;

	/** Called when a document is saved, as determined by a document list observer. In general
		you shouldn't need to call this. Currently the manager doesn't do anything but it may in
		the future.

		@param iDoc The document saved.
	*/
	virtual void OnSaveDocument(IDocument* iDoc) = 0;

	/** Called when a document is saved-as, as determined by a document list observer. In general
		you shouldn't need to call this. The manager responds by updating its internal document 
		database (see above).

		@param iDoc The document saved.
	*/
	virtual void OnSaveAsDocument(IDocument* iDoc) = 0;

	/** Called when a document is opened, as determined by a document list observer. In general
		you shouldn't need to call this. The manager responds by removing any observers, updating
		the document database, and deleting anything that might reference the document, such as
		processes, tasks, and caches. It also notifies all of the object model services in case
		they have any caches that need to be flushed.

		@param iDoc The document being closed.
	*/
	virtual void OnCloseDocument(IDocument* iDoc) = 0;

	/** Called when a book is closed. If there's an active preflight on the book then we need to
		notify all the affected processes.

		@param iDoc The document being closed.
	*/
	virtual void OnCloseBook(IBook* iBook) = 0;

	/** Called when a settings change is broadcast on the global settings-change digest subject.
		This information is then distributed to the managers that might want to respond.

		@param iInfo IN The settings change info.
	*/
	virtual void OnSettingsChange(const IPreflightSettingsChangeInfo* iInfo) = 0;
};

