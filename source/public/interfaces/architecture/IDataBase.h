//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDataBase.h $
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
//  Reviewed: 	10/5/98
//  
//  Purpose:	Provides access to the database that holds a K2 publication.
//  
//  THIS IS NOT A STANDARD BOSS INTERFACE
//  
//========================================================================================

#pragma once
#ifndef __IDATABASE__
#define __IDATABASE__

#include "IPMUnknown.h" // for the definition of INHERITFROM
#include "GlobalTime.h"	// should be removed, but is indirectly included by many files
#include "IDFile.h"		// for IDFile
#include "IDatabaseSnapshot.h"

class IDTime;
class IPMUnknown;
class IPubFile;
class IPMPersist;
class IDatabaseObserver;
class IUIDIterator;
class IInstanceProcessor;
class InstanceProfiler;
class IDBChangesMonitor;
class IDatabaseSnapshot;
/** A database is the underlying data structure used for storage of documents,
	preferences, books, etc. It handles allocation, serialization, deletion of 
	objects in the files. It also handles caching of objects. 
	
	An IDataBase ptr is NOT a reference to a standard boss object. It is a virtual C++ class, but
	does not inherit from IPMUnknown.

	@ingroup arch_db 
*/
class IDataBase	INHERITFROM
{
public:
	/** The database destructor closes an open database, and thus there is no explicit Close() method.
	    Note that any changes to the database made since the last Save()/SaveAs() are lost.
	*/
	virtual ~IDataBase() {};
	
	/** The return type for most DataBase methods	 */
	typedef enum
	{
		/** Success */
		kNoError = 0,
		/** User cancelled the operation, such as with the cancel button on a progress bar */
		kUserCanceled,
		/** Catch-all error code not handled elsewhere */
		kUnknownError,
		/** Insufficient memory */
		kLowMemoryError,
		/** File damaged but may be recoverable */
		kFileDamagedError,		// file may be recoverable
		/** File damaged and is not recoverable */
		kFileCorruptError,		// file is not recoverable
		/** File not found */
		kFileNotFoundError,
		/** File is already open */
		kFileIsOpenError,
		/** File is read-only */
		kFileIsReadOnlyError,
		/** Disk is full or insufficient disk space to complete operation */
		kDiskFullError,
		/** File not found */
		kNotFoundError,
		/** An edited but unsaved file could not be recovered because the original file on disk was already changed by another user */
		kFileChangedError,
		/** Wrong version */
		kWrongVersionError,
		/** File is not open */
		kFileIsNotOpenError,
		/** File format invalid - magic bytes don't match.  @see DBUtils::SetMagicBytes */
		kInvalidFileFormatError,
		/** The database cannot open another file because too many are already open.  @see DBUtils::GetAvailableNewDatabases */
		kTooManyFilesError,
		/** The database cannot be saved at this point because it has outstanding clones. */
		kOutstandingClonesSaveError,
		/** The database cannot be saved at this point because it has outstanding transactions */
		kOutstandingTransactionsSaveError,
		/** The database cannot be merged with clone. */
		kDBMergeFailed,
        /** We could not switch modes (read only shared or read write exclusive) on the underlying file */
        kDBModeSwitchFailed,
        /** File damaged and is not recoverable - size too small */
        kMiniSaveFileVerificationFailedError, //temp file damaged due to MiniSave
        kUserFileVerificationFailedError    //user file damaged due to merge of tempfile
	} DBResultCode;
	
	//------------------------------------------------------------------------------------
	// Objects & UIDS
	//
	// Create, Instantiate and delete objects in the database.
	//------------------------------------------------------------------------------------
	
	/** Creates a new persistent object in the database.
		Note that you can also use the NewUIDCmd (kNewUIDCmdBoss), which will handle the Undo for you.
	   @param ClassID for the new object
	   @return UID of the newly created object.
	*/
	virtual UID NewUID(ClassID clsID) = 0;
	/** Marks the object with the given UID for deletion.
		The object can longer be instantiated.
	 	Existing references remain valid.
		You can use the command named kDeleteUIDCmdBoss as a client rather than call this.
	   @param UID of the object to delete
	   @return DBResultCode the resulting error code
	*/
	virtual DBResultCode DeleteUID(UID id) = 0;
	/** Restores the previously deleted object with the given UID and ClassID.
		You will want to use exactly the same ClassID that was used to create the object.
		This is often called by Commands during an Undo operation.
	   @param UID of the object to restore
	   @param ClassID for the restored object
	   @return DBResultCode the resulting error code
	*/
	virtual DBResultCode UndeleteUID(UID id, ClassID clsID) = 0;
	/** Frees up space for a previously deleted object with the given UID.
		The object can no longer be resurrected with UndeleteUID.
		This is normally called for you.
	   @param UID of the object to destroy
	   @return DBResultCode the resulting error code
	*/
	virtual DBResultCode DestroyDeletedUID(UID id) = 0;
	
	/** Creates an in-memory version of the db-based object with the given UID, or 
		simply returns a reference to the object if it is already instantiated.
		Does a QueryInterface for the requested interface. Returns nil if the UID
		doesn't exist, or if it's been deleted, or if the requested interface 
		doesn't exist. Pass IID_IUNKNOWN if you don't care what interface you get.
		Normally this is called from InterfacePtr, instead of directly.
	   @param id of the object to instantiate
	   @param interfaceID which interface of the object to return
	   @return IPMUnknown* a pointer to the requested interface of the object (or nil)
	*/
	virtual IPMUnknown *Instantiate(UID id, PMIID interfaceID) = 0;

	/** Like Instantiate(), but only returns a pointer if the requested interface
		is currently instantiated. If the interface would have to be accessed from
		the database, nil is returned.
	   @param id of the object to instantiate
	   @param interfaceID which interface of the object to return
	   @return IPMUnknown* a pointer to the requested interface of the object (or nil)
	*/
	virtual IPMUnknown *QueryInstance(UID id, PMIID interfaceID) = 0;
	
	/** Returns kTrue if the given UID exists and is a reference to a valid object in
		the database. Returns false if the UID has never
		been allocated, or if it's been allocated and subsequently deleted. If it's
		been deleted, then undeleted, it returns true.
	   @param id of the object
	   @return bool8 kTrue if the UID is allocated
	*/
	virtual bool8 IsValidUID(UID id) const = 0;
	
	/** Returns the root UID. This is the root object of the object hierarchy.
		For a document, it will return the kDocBoss (IDocument) object.
	   @return UID of the root object in the database
	*/
	virtual UID GetRootUID() const = 0;
	/** Get the class of the object.
	   @param id of the object
	   @return ClassID that is associated with the UID, or kInvalidClass if there 
	   is no such UID or if it has been deleted.
	*/
	virtual ClassID GetClass(UID id) const = 0;	

	/** Creates and returns a new UIDIterator. Use it to iterate over all
		UIDs in the database. Call DeleteUIDIterator when you are done with it.
		See UIDIterator.h
	   @param includeDeletedUIDs false to skip over deleted UIDs, true otherwise
	   @return IUIDIterator the iterator
	*/
	virtual IUIDIterator *NewUIDIterator(bool8 includeDeletedUIDs = kFalse) const = 0;
	/** Delete an UIDIterator. Every call NewUIDIterator must have a matching call
		to DeleteUIDIterator.
	   @param iterator to delete.
	*/
	virtual void DeleteUIDIterator(IUIDIterator **iterator) const = 0;
	
	/** Internal use only. */
	virtual void AssertOnModification () = 0; // Asserts if the database has been modified used to assert if the database is being dirtied on saveing.
	
	//------------------------------------------------------------------------------------
	// DataBaseObservers
	//
	// DataBaseObservers are notified for modification actions to UIDs.
	// See IDataBaseObserver.h
	//------------------------------------------------------------------------------------

	/** Attaches an observer to the database. The observer will be called when certain 
		database operations happen. @see IDataBaseObserver.h for a list of notifications.
	   @param observer to attach
	*/
	virtual void AttachDataObserver(IDatabaseObserver* observer) = 0;
	/** Detach an observer registered with AttachDataObserver. Every call to AttachDataObserver must have
		a matching call to DetachDataObserver.
	   @param observer to detach
	*/
	virtual void DetachDataObserver(IDatabaseObserver* observer) = 0;

	
	
	//--------------------------------------------------------------------------------------
	// DataBase File Info
	//-------------------------------------------------------------------------------------
		
	/** Represents the endian/byte order of data stored in the database */
	typedef enum
	{
		/** never valid */
		kSwapUnknown = 0,
		/** little endian */
		kIntelOrder,	
		/** big endian */
		kMotorolaOrder	
	} ByteSwapOrder;
	
	/** Returns the number of times the database has been saved
		@return uint32 save count
	*/
	virtual uint32 GetSaveCount() const = 0;
	/** Returns kTrue if the database was opened read only
		@return bool16 kTrue if the database was opened read only
	*/
	virtual bool16 IsReadOnly() const = 0;
	/** Returns kTrue if the database has been modified since last save.
		@return bool16 kTrue if the database has been modified since last save.
	*/
	virtual bool16 IsModified() const = 0;
	// Sets the version number of the application that was used
	// to create the database. INTERNAL USE ONLY
	virtual IDataBase::DBResultCode SetVersionNumber(const int32& majorVersion, const int32& minorVersion) = 0;
	/** Returns the version number of the application that was used
		to create the database
		@param int32* majorVersion major version number (return value!)
		@param int32* minorVersion minor version number (return value!)
	*/
	virtual void GetVersionNumber(int32 *majorVersion, int32 *minorVersion) const = 0;
	/** Returns the byte order of the database
		@return ByteSwapOrder endian order of the database
	*/
	virtual ByteSwapOrder GetByteSwap() const = 0;	
	/** Returns the file associated with the database (if the database has
		been opened or saved). Returns nil if there is no file associated yet.
		@return IDFile* pointer to the file information.
	*/
	virtual const IDFile* GetSysFile() const = 0;
	
	
	//------------------------------------------------------------------------------------
	// DataBase File Handling
	//------------------------------------------------------------------------------------
	
	/** Flags to determine how to a database is opened */
	typedef enum
	{
		/**  Opened for read only */
		kRead,
		/**  Opened for reading and writing */
		kWrite,
		/**  Open a copy.  The original file is opened read-only only long enough to copy out
		     the contents, after which it is closed and the database is considered unsaved */
		kCopy
	} OpenFlags;
	
	/** Flags to determine how a database is saved */
	typedef enum
	{
		/** Do a save-as, which changes the database's user file to be the save target file */
		kSaveAs,
		/** Save a copy only if the current database content */
		kSaveACopy
	} SaveFlags;
	
	/** Selecting the protection level of a database allows you to trade off performance and
		file-size versus fault-tolerance level when dealing with databases, depending on
		how important the data is in the database.
		*/
	typedef enum
	{
		/** File will get deleted after use.  This is the fastest mode.
			Basically this is the same as kNoProtection, only creation and deletion
			is faster. The file cannot be re-opened once it is closed.
		*/
		kDeleteAfterUse = -1,
		/** The data is not protected on disk. It is often buffered in memory,
			and written out only as needed.  This is fastest, and also produces
			the smallest files on disk.  However, these databases need to be
			properly closed to be re-opened.  No recovery operations are supported.
		*/
		kNoProtection = 0, 
		/** Database is fault-tolerant, recoverable to the point of the last Save
		    or Save-As operation.  This is somewhat slower than kNoProtection and also
			can produce larger files on disk after multiple Saves (but you can compact the database
			file by doing a save-as or save-a-copy operation). 
		*/
		kProtectSave, 
		/** Database is fault-tolerant and recoverable to the point of the 
			last save, save-as, or periodic mini-save operation, whichever happened last.
			This is the highest level of protection and also the slowest.
		*/
		kProtectMiniSave
	} ProtectionLevel;
		
	/** Prototype for a progress callback to be installed with SetProgressCallback()
		below.
		If a callback returns something different than kNoError the database will cancel
		and return this error code.
	*/
	typedef DBResultCode (*DBProgressFunction)(int32 stepsDone, int32 stepCount);

	/** Creates a new file.
		@param protLevel protection level
		@return resulting error code
	*/
	virtual DBResultCode New(ProtectionLevel protLevel) = 0;
	/** Opens an existing file.
		@param whatFile file to open
		@param protLevel protection level
		@param openFlag open read-only, writeable, or as a copy
		@return resulting error code
	*/
	virtual DBResultCode Open(const IDFile& whatFile, ProtectionLevel protLevel,
													OpenFlags openFlag = kWrite) = 0;
	/** Reverts the database to the last saved state.  This is only allowed
	    when there are no outstanding references to anything in the database.
		@return resulting error code
	*/
	virtual DBResultCode Revert() = 0;
	/** Recovers damagedFile.
		@param damagedFile file to recover
		@param protLevel protection level
		@param oldProtLevel 
		@param miniSaveFile 
		@return resulting error code
	*/
	virtual DBResultCode Recover(const IDFile* damagedFile, ProtectionLevel protLevel,
				ProtectionLevel oldProtLevel, const IDFile* miniSaveFile = nil) = 0;
				
	/** Saves changes to the file.  You should not save a database on which there is an outstanding transaction, 
		which is why save commands typically do not target the actual database being saved.
		@return resulting error code
	*/
	virtual DBResultCode Save() = 0;
	/** Saves the database to a new file.  You should not save a database on which there is an outstanding transaction, 
		which is why save commands typically do not target the actual database being saved.
		@param destFile file to save to 
		@param saveFlag saveAs or saveACopy
	*/
	virtual DBResultCode SaveAs(const IDFile& destFile,
													SaveFlags saveFlag = kSaveAs) = 0;
	
	/** Sets the database to a "modified" state -- regardless whether db has been
		modified or not.
		@param modified 
	*/
	virtual void SetModified(bool16 modified) = 0;


	/** This stack-based class is to be used in a scope where you want to perform
	    an operation which is "logically const" on the database (that is, you
		don't want operations during that scope to set the modified state of
		the database if it was not already set).  Just put the following in the scope you need:
		IDataBase::SaveRestoreModifiedState saveRestore(db);
	*/
	class SaveRestoreModifiedState
	{
	public:
		SaveRestoreModifiedState(IDataBase * db)
			: fDB(db)
			{
			if (db && db->IsModified())
				fDB = nil;	// If the database is already modified we don't need to restore
			}

		~SaveRestoreModifiedState()
			{
			if (fDB)
				fDB->SetModified(kFalse);
			}
		private:
			IDataBase * fDB;
	};
	
	/** This is used to set the Macintosh file creator and file type.
		On the Macintosh, this is expected to be a pointer to a 
		file creator, followed by a file type (both OSType).
		@param fileInfo creator & type
	*/
	virtual void SetPlatformFileInfo(void *fileInfo) = 0;

	/** Sets the progress callback function of the database and returns the previous one.
		@param callback
	*/
	virtual DBProgressFunction SetProgressCallback(DBProgressFunction callback) = 0;
	
	
	//--------------------------------------------------------------------------------------
	// Transactions & Mini-Save
	//
	// All changes to the database must be encapsulated in a transaction.
	// Nested transactions are possible.
	//
	// You usually do not have to call Begin/EndTransaction yourself.
	//
	// An assert regarding a database change outside of a transaction is usually 
	// caused by either a modification outside of a command, a command with
	// an incorrect target, or a command that modifies more than one database.
	//--------------------------------------------------------------------------------------
	
	/** Starts a transaction. You should not normally need to call this directly. Changes to the 
		document or preferences should be enclosed in Commands, and then this will be 
		called for you by the command maanger. If you change the database via direct modifications 
		it may result in corrupted documents.  If you receive an assert about a database change outside 
		of a transaction it is usually caused by either a modification outside of a command, a command with
		an incorrect target, or a command that modifies more than one database.  The appropriate solution
		is normally to use commands correctly as opposed to inserting a call to BeginTransaction which
		just alleviates the assert instead of addressing the underlying issue.

		@return DBResultCode resulting error code
	*/
	virtual DBResultCode BeginTransaction() = 0;
	/** Ends a transaction.
		Note: There is no commit/rollback - EndTransaction implies a commit.
		@return DBResultCode resulting error code
	*/
	virtual DBResultCode EndTransaction() = 0;

	/** Gets the current transaction level on this database. Client code typically has no need for this.
		@return current transaction count
	*/
	virtual int32 GetTransactionLevel() const = 0;

	/** Gets the level of protection for the file
		Note: This value is defined at New/Open and there is no way to change it.
		@return ProtectionLevel protection level
	*/
	virtual ProtectionLevel GetProtectionLevel() const = 0;
	/** Sets the interval (in milliseconds) in which the database should perform it's mini-save
		Returns the new interval (which might be different from msecs since there are certain limits)
		@param msecs new interval in milliseconds
		@return uint32 the previous interval
	*/
	virtual uint32 SetMiniSaveInterval(uint32 msecs) = 0;
	/** Returns the current interval (in milliseconds) in which the database performs it's mini-save
		@return uint32 the interval
	*/
	virtual uint32 GetMiniSaveInterval() const = 0;
	
	/** Inquires the temporary file used for mini save, recovery, and spill from memory
		@return IDFile* the file used for mini save
	*/
	virtual const IDFile* GetMiniSaveFile() const = 0;
	
	/** Gets the error information
		@return DBError the error code associated with the previous action
	*/
	virtual DBResultCode GetErrorCode() = 0;
	/** Resets error state
	*/
	virtual void ClearError() = 0;
	
		
	//------------------------------------------------------------------------------------
	// Contiguous UID Support
	//------------------------------------------------------------------------------------

	/** Internal use only. */
	virtual UID NewContiguousUID (uint16 type, bool16 externallyWritable) = 0;
	/** Internal use only. */
	virtual bool16 GetContiguousUIDChangeMarker (UID id) const = 0;
	/** Internal use only. */
	virtual void SetContiguousUIDChangeMarker (UID id, bool16 changed) = 0;

	//------------------------------------------------------------------------------------
	// For internal use only
	//------------------------------------------------------------------------------------

	/** Internal use only. */
	virtual void DestructInstance(UID id) = 0;
	/** Internal use only. */
	virtual void ClearDirty(IPMPersist *flushThis) = 0;
	/** Internal use only. */
	virtual void DirtyObject(IPMPersist *flushThis, ClassID clsID, ImplementationID tag, bool16 allowModification = kTrue, bool16 firstDirtyInterface = kTrue) = 0;
	/** Internal use only. */
	virtual void SetError(DBResultCode dbErrCode, const IDFile* userProvidedFile = nullptr) = 0;
	/** Internal use only. */
	virtual void PurgeMemory(int32 level) = 0;
	/** Internal use only. */
	virtual void AdviseMemoryState(int32 level) = 0;
	/** Internal use only. */
	virtual void RegisterRootObject(IPMUnknown *root) = 0;
	/** Internal use only. */
	virtual IPubFile* GetPubFile() = 0;
	/** Internal use only. */
	virtual void IterateInstantiatedObjects(IInstanceProcessor *i) = 0;
	/** Internal use only. */
	virtual InstanceProfiler *NewInstanceProfiler() = 0;
		
#ifdef DEBUG
	/** Internal use only. */
	virtual void SetInstanceCacheState(bool16 on) = 0;
	/** Internal use only. */
	virtual bool16 GetInstanceCacheState() = 0;
	
	/** Internal use only. */
	virtual bool16 SetDirtyLimit(bool16 allowModification) = 0;
	/** Internal use only. */
	virtual bool16 GetDirtyLimit() = 0;
	
	/** Internal use only. */
	virtual bool16 BeingDestructed() = 0;
#endif

	//------------------------------------------------------------------------------------
	// Date/Time for Underlying Store
	//------------------------------------------------------------------------------------

	/** Gets the creation time of the database file
		@param gt Set to the creation time of the database file on success
		@return DBResultCode resulting error code
	*/
	virtual DBResultCode GetCreationTime (IDTime &gt) = 0;

	/** Gets the modification time of the database file
		@param gt Set to the modification time of the database file on success
		@return DBResultCode resulting error code
	*/
	virtual DBResultCode GetModificationTime (IDTime &gt) = 0;

	//------------------------------------------------------------------------------------
	// Save Sequence Numbers
	//------------------------------------------------------------------------------------

	/** Internal use only. */
	virtual uint64 GetSequenceNumberAtOpen () const = 0;
	/** Internal use only. */
	virtual uint64 GetCurrentSequenceNumber () const = 0;

	/** Internal use only. */
	typedef enum
	{
		kUserFileExclusive = 0,
		kUserFileShared
	} UserFileMode;

	//------------------------------------------------------------------------------------
	// Cache performance. This API is for internal use only.
	//------------------------------------------------------------------------------------
	/** Internal use only. */
	virtual uint32	GetCacheFaultRate() const = 0;
	/** Internal use only. */
	virtual uint32	GetCacheTotalFaults() const = 0;

	/** Internal use only. */
	enum CachePolicy
	{
		kAnnaCachePolicy,
		kFaultRateBasedPolicy,
		kCacheAllPolicy
	};

	/** Internal use only. */
	virtual CachePolicy	GetCachePolicy() const = 0;
	/** Internal use only. */
	virtual void		SetCachePolicy(CachePolicy policy) = 0;
	
	//------------------------------------------------------------------------------------
	// Support for better error handling
	//------------------------------------------------------------------------------------


	/** Support for better error handling.  Returns the file that was used in the Open or Recover operation on the database.
		This is useful for better error handling because GetSysFile() return nil after Open()
		fails, yet we want to ask the database what IDFile the call failed on.  
		@return IDFile* the file that was used in the Open or Recover operation on the database, or nil if Open or Recover was never called.
	*/
	virtual const IDFile* GetSysFileFromOpen() const = 0;

	//------------------------------------------------------------------------------------
	// Snapshot Database Handler
	// Used for tracking changes to UIDs for automatic undo redo of commands.	
	//------------------------------------------------------------------------------------

	/** The return type of GetUndoSupport
	There are three kinds:
	kNoUndoSupport : when the database has no support for tracking UID changes.

	kFullUndoSupport : when the database has support for tracking UID changes and the database
	is revisioned so that when undo is invoked, older revisions of the database a restored.
	
	kPartialUndoSupport : when the database has support for tracking UID changes but no 
	revisioning. This means that when errors occurr, a transaction is reverted through automatic
	error handling. However, once a transaction is committed, it becomes irreversible.
	*/

	typedef enum {kNoUndoSupport, kFullUndoSupport, kPartialUndoSupport} UndoSupport;

	/** Returns the undo support type of the database.
	*/
	virtual UndoSupport GetUndoSupport() const = 0;
	
	/** Internal use only. */
	virtual IDBChangesMonitor* GetDBChangesMonitor() const = 0;

	/** Internal use only. */
	virtual IDatabaseSnapshot* GetLastDBSnapshotBeforePubFileSharing() const = 0;

	/** Internal use only. */

	virtual void SetDBChangesMonitor(IDBChangesMonitor* dbChangesMonitor, UndoSupport undoSupport)  = 0;

	//------------------------------------------------------------------------------------
	// Support for documents which are not datbases
	//------------------------------------------------------------------------------------
	// InCopy stores documents as XML and merely uses the database as a scratch work file.
	// As a result, assumptions about the user pubfile are invalid.  The "faux" user file
	// is our way of informing the database of this situation so as to prevent problems
	// with scripting, the UI and recovery.
	/** Internal use only. */
	virtual void SetFauxUserFile(const IDFile &newFile) = 0;
	/** Internal use only. */
	virtual bool16 IsFauxUserFile() const = 0;

	//------------------------------------------------------------------------------------
	// More UID functions.  Move up with rest between builds; but don't change vtable now [][]
	//------------------------------------------------------------------------------------
	// Creates a new persistent object in the database.  The caller specifies the desired
	// UID of the new object.  This will succeed under the following conditions:
	//    1.  The requested UID is in the valid range - (currently: 1 <= UID <= 2^31-1)
	//    2.  The UID has either never been used, or can be re-used
	// A UID that was used before can only be re-used provided that it does not exist
	// in either the temporary file or the user file.  This requires at least calling
	// DeleteUID and DestoryUID, and performing a save operation afterwards if the
	// database protection level is greater than kNoProtection.
	//
	// There may be three outcomes when calling this function.  Callers should be prepared:
	//
	// If the function succeeds, the object is created and the function returns kTrue
	// 
	// If the function fails because the UID isn't available to be used (outside of the
	// valid range, not available for re-use yet), the function returns kFalse but the
	// database error state is not set
	//
	// If the function fails for some more insidious reason, it returns kFalse and the 
	// database error state is set appropriately
	/** Internal use only. */
	virtual bool16 PlacementNewUID(ClassID clsID, UID id) = 0;

	// Returns kTrue if the passed UID is valid for use/re-use with PlacementNewUID()
	/** Internal use only. */
	virtual bool16 PlacementUIDIsAvailable (UID id) = 0;

	// Flush dirty objects for RIDX query
	/** Internal use only. */
	virtual void FlushDirtyObjectsForRIDXQuery () = 0;

	// Clone the database
	virtual IDataBase* Clone() = 0;

	// Clone a database snapshot (for internal use only)
	virtual DatabaseSnapshotPtr CloneADatabaseSnapshot() = 0;

	// Call this function after an execution context switch took place (call from child task).
	// Necessary regardless whether the datase has been created as a clone.
	virtual	bool SwitchExecutionContext() = 0;
	// Call this function before an execution context switch(call from the the parent task).
	// Not necessary if the datase has just been created as a clone
	virtual	bool PrepareForExecutionContextSwitch() = 0;

	// clone must be a clone if this
	virtual	 DBResultCode Merge(IDataBase *clone) = 0;

	/** Internal use only. */
	virtual DBResultCode DestroyDeletedUID_AfterLastReferenceIsReleased(UID id) = 0;

	/** Internal Use only */
	virtual void AllowPurge() = 0;
	virtual void DisallowPurge() = 0;
	virtual void DoScheduledPurge() = 0;
	virtual bool IsPurgeAllowed() const = 0;
	
	virtual DBResultCode AttemptMiniSave() = 0;
	virtual bool PubFileIsShared() const = 0;
	
	/* You can override what Instantiate() does by setting an override function. Use nil to remove a function.
		SetInstantiateFunction returns the function that was previously being used, in case client code needs to
		restore it later.
	*/
	struct  InstantiateFunctionObj
	{
		virtual IPMUnknown* operator () (IDataBase *db, UID id, PMIID faceID) = 0;
	};

	typedef InstantiateFunctionObj* InstantiateFunction;

	virtual InstantiateFunction SetInstantiateFunction(InstantiateFunction overrideInstantiate = nil) = 0;
	virtual InstantiateFunction GetInstantiateFunction() const = 0 ;

    /* FileRecoveryMode - for internal use only */
    typedef enum {
        kNoRecovery,
        /* File opened using Pre trans master page */
        kUsingPreTransMasterPage,
        /*File opened using LPM CoWP page*/
        kUsingLPMCoWorkerPage
    } FileRecoveryMode;
};


/** Stack based helper class for keeping track of when it is OK to purge.
	Differs slightly from the generic PurgeLock class because it will cause
	a purge on destruction if one has been deferred.
*/
template <class T>
class DBPurgeLock
{
public:
	DBPurgeLock(T *handler) :
		fHandler(handler)
	{
		fHandler->AllowPurge();
	}
	~DBPurgeLock()
	{
		fHandler->DisallowPurge();
		fHandler->DoScheduledPurge();
	}
private:
	T *fHandler;
};

// define adobe::type_info<IDatabase> specialization so any_regular_t can move IDataBase across DLL boundaries
ADOBE_NAME_TYPE_0("idatabase:indesign:adobe", IDataBase)

#endif // __IDATABASE__
