//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DBUtils.h $
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
//  Purpose:
//  Utility class
//  
//========================================================================================

#pragma once
#ifndef __DBUTILS_
#define __DBUTILS_

#include "IDataBase.h"
#include "OMFactoryCtor.h"

#pragma export on

class IRIDXDBInterface;
class IInvalHandler;

/** Contains static utility functions related to databases.

	@see IDataBase
	@ingroup arch_db 
*/
class DATABASE_DECL DBUtils
{
public:
	
	
	enum { 
		/** The number of bytes in a unique identifier of an InDesign database type */
		kMagicByteCount = 8 
	};

	/** A series of 8 bytes uniquely identifies an InDesign database type; eg DOCUMENT for .indd files */
	typedef char		MagicBytes[kMagicByteCount];
	/** Database factory function - call this to create an instance of the officially sanctioned type of database.
	    Note that you should already have set the magic bytes for the type of database you want to create
		already via DBUtils::SetMagicBytes before you call this function, and reset the magic bytes to
		the default afterwards.  @see SetMagicBytes
		@return IDataBase* the newly created database object
	*/
	static IDataBase *CreateDataBase(IDataBase::UndoSupport undoSupport, bool hasContentMgr = true);

	// Create a clone from a database snapshot(for internal use only)
	static IDataBase* CreateCloneFromDatabaseSnapshot(DatabaseSnapshotPtr dbSnapshot, IDataBase::UndoSupport undosupport = IDataBase::kPartialUndoSupport) ;

	/** Sets the magic bytes for the next database to be created.  Each database created has a unique
	    identifier of kMagicByteCount bytes that identifies its type.  Before creating a new database,
		you should set the magic bytes to the identifier for your database type, and then afterwards
		(regrettably) you need to remember to set it back to the default, which is "DOCUMENT" for .indd
		files in InDesign.  For example:
	<pre>
	static DBUtils::MagicBytes resetBytes = { 'D', 'O', 'C', 'U', 'M', 'E', 'N', 'T' };
	static DBUtils::MagicBytes myDatabaseBytes = { ... whatever your database type uses ... };
	DBUtils::SetMagicBytes(myDatabaseBytes);
	IDataBase *myDB = DBUtils::CreateDataBase();
	DBUtils::SetMagicBytes(resetBytes);
	if (myDB) ...
	</pre>
		@param bytes The magic bytes to set for newly constructed databases.
	*/
	static void SetMagicBytes(const MagicBytes bytes);

	/** Returns the number of additional new databases currently guaranteed to be openable without error.
		Current implementations of the database restrict the number of databases
		that may be open at any one time.  If this limit is reached, the next
		database that you attempt to create and then IDatabase::Open() or
		IDatabase::New() will fail with error kTooManyFilesError.  Sometimes it
		is useful to know beforehand how many databases you can successfully open.
		This function returns a value that at the time of the call guarantees
		a lower bound on this value (i.e. if GetAvailableNewDatabases() returns
		50, then you can open 50 additional databases without getting kTooManyFilesError.
		You may be able to open more than the returned value in some cases).
		@return uint32 the number of additional databases openable
	*/
	static uint32 GetAvailableNewDatabases ();

	/** Determine if a database object pointer is still valid.  This is sometimes very useful
	    in a place where an IDataBase pointer may have been cached (such as in a scheduled command),
		and later you need to determine if the database is still around or whether it has already
		been closed/destructed.
		@return bool16 kTrue if the database still exists, or kFalse if it has been closed/destructed and is gone.
	*/
	static bool16 IsValidDataBase (IDataBase *db);


	// Inval handler management fuctions.

	/**	Attach the inval handler to the database;
		in order for an inval handler to get notified regarding undoable transactions 
		it must be attached to the database using this method.

		The attach will fail if the database has no undo support.

		The database will TAKE OWNERSHIP OF THE INVAL HANDLER POINTER. The database 
		will delete the pointer when DetachInvalHandler is called or when the database
		is closed, whichever occurs first.

		@param db the database to which the inval handler is to be attached
		@param IInvalHandler* the inval handler instance
		@param id unique ID (keyed off the plug-in prefix) for the inval handler
		@return bool16 kTrue when the attach succeeds

		@post The inval handler must be detached before the database is closed (see DBUtils::DetachInvalHandler).
		@see IInvalHandler
	 */
	static bool16 AttachInvalHandler(IDataBase* db, IInvalHandler*, InvalHandlerID id);

	/**	Detaches the inval handler from the database and deletes the inval handler.
		Thus, THE INVAL HANDLER POINTER BECOMES INVALID ON FUNCTION RETURN. 
		@pre the inval handler must already be attached (see DBUtils::AttachInvalHandler)
		@param db 
		@param IInvalHandler* 
		@see IInvalHandler
	 */
	static void DetachInvalHandler(IDataBase* db, IInvalHandler* );

	/**	Looks up the first inval handler attached to the database with
		the specified inval handler type id.

		@param db 
		@param id 
	 */
	static IInvalHandler* GetInvalHandler(const IDataBase* db, InvalHandlerID id);	// For purges. When interfaces come back to life after a purge,
																	// they can enquire if the were already registerred with the sequence.

	/**	When an inval handler is attached to a database it can be in one of two states: 
	"collecting invals" or "not collection invals". Its intial state is "not collecting invals".
	When in "not collecting invals", if a change to the topic of interest takes place, 
	in order to switch to "collecting invals", the inval handler must call DBUtils::StartCollectingInvals. 
	This call returns kTrue if there is an ongoing undoable transaction in the database and kFalse otherwise (e.g. we are 
	in the middle of undoing). If this call returns kTrue, the inval handler switches to 
	"collecting invals" otherwise it remains in "not collection invals". 

		@param db 
		@param handler 
		@return kTrue if there is an ongoing undoable transaction in the database, kFalse otherwise 
			(for example, the application is in the middle of undoing a transaction)
	 */
	static bool16 StartCollectingInvals (IDataBase* db, IInvalHandler* handler);

	// Lazy notification functions

	/**	Use of this method is very rare. 
		It is related to lazy notifications associated with a "snapshot view interface".
		It is used to strip from the lazy notification queue all the lazy broadcasts 
		associated with the "snapshot view interface" when 
		that interface no longer targets the database to which the lazy notification queue
		belongs.

		@param db 
		@param subject object on which the "snapshot view interface" broadcasts its changes.
	 */
	static void DiscardLazyNotificationSubject(IDataBase* db, const UIDRef& subject);

	/** Internal use only. */
	typedef void (*CUIDFilterFunction) (void *buffer, uint32 size, uint16 type);
	
	/** Internal use only. */
	static void SetCUIDImportFilter (CUIDFilterFunction functor);
	/** Internal use only. */
	static void SetCUIDExportFilter (CUIDFilterFunction functor);
	/** Internal use only. */
	static CUIDFilterFunction GetCUIDImportFilter ();
	/** Internal use only. */
	static CUIDFilterFunction GetCUIDExportFilter ();
	
		// Set the constructor function. Returns the old one.
	/** Internal use only. */
	static BossConstructor SetObjectConstructor(BossConstructor newConstructor);

	/** Returns all impls in UID that ever got persisted
	*/
	static  void GetUIDPersistedInterfaces(IDataBase *db, UID id, ClassID clsID, IPMPersist* obj, std::vector<ImplementationID>& implList);
	
		// Call this to tell the database what to stamp new files with, and 
		// what files can legally be opened.
	/** Internal use only. */
	static void SetBuildVersion(int32 majorVersionNumber, int32 minorVersionNumber);
		// Call this to find out if the file is a valid database file.  
		// Currently this always returns true for unclear historical reasons, which makes it less than useful. [][]
	/** Internal use only. */
	static bool16 IsValidDataBase(const IDFile *fileToCheck);
		// Defines where to put mini save files.
		// Copies the value of newPath.
		// A call with newPath = nil deletes the path  (this is necessary to avoid a memory leak)
	/** Internal use only. */
	static void SetRecoveryPath(const IDFile* newPath);
	/** Internal use only. */
	static const IDFile *GetRecoveryPath();
		// EnableInstanceCaches enables/disables all caches and returns kTrue
		// if the caches were enabled before
	/** Internal use only. */
	static bool16 EnableInstanceCaches(bool16 enable);
	/** Internal use only. */
	static void AddClass(IDataBase *db, ClassID newCls, UID uid);
		// Tell the PlugInContentMgr that a new class has been added to the document.
	/** Internal use only. */
	static void ProcessDeferredContent(IDataBase *db);

	/** Internal use only. */
	static IDataBase::CachePolicy	GetNewDataBaseCachePolicy();
	/** Internal use only. */
	static void						SetNewDataBaseCachePolicy(IDataBase::CachePolicy);
			
		// Reference Index 
	/** Internal use only. */
	static IRIDXDBInterface *GetRIDXDBInterface ();
	/** Internal use only. */
	static void SetRIDXDBInterface (IRIDXDBInterface *i);
	/** Internal use only. */
	static void EnableRIDXDBInterface ();
   		
#ifdef DEBUG
		// limits UID to a number smaller than 0xFFFFFFFF
		// and returns the current limit
	/** Internal use only. */
	static UID SetMaxUID(UID newMaxUID);
		// returns the current limit for UIDs
	/** Internal use only. */
	static UID GetMaxUID();
	
	/** Internal use only. */
	static	void	SetAssertOnInstantiateFail(bool16 showAsserts);
	/** Internal use only. */
	static	bool16	ShowInstantiateAsserts();

#endif

	//internal use only
	static void ShutdownSUIDS();
	static void PreShutdownSUIDS();
	static void InitializeSUIDS();
	static uint32 GetTotalCurrentNetworkCacheSize();
};

#pragma export off

#endif //__DBUTILS_
