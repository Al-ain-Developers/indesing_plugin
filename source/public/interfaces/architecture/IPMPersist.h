//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMPersist.h $
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
//========================================================================================

#pragma once
#ifndef __IPMPersist__
#define __IPMPersist__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IDataBase;
class IPMStream;
class IPMPersist;
class IContentTracker;
class IContentReadIterator;
class IContentWriteIterator;
class ISnapshotCache;

/** Manages the persistence aspect of an object: handles streaming the boss
	object, stores the UID and database (IDataBase). 

	@ingroup arch_db 
*/
class IPMPersist : public IPMUnknown	
{
public:
	enum { kDefaultIID = IID_IPMPERSIST };
		
		/** Returns the unique ID used to specify the object to the
			database. This can be used in a call to IDataBase::Instantiate().
			Usually this is called via PersistUtils::GetUID().
		@return The object's UID.
		*/
	virtual UID GetUID() const = 0;

		/** Return a pointer to the object's open database.
		@return The object's database. Usually called via PersistUtils::GetDataBase().
		*/
	virtual IDataBase *GetDataBase() const = 0;
		
		/** Reset the object state using the contents of the stream.
			Streams in every persistent interface. After the object
			is streamed in, it sets the dirty flag if setDirty is
			kTrue. When loading objects from the database, setDirty
			should be false. In all other cases, setDirty should be
			kTrue.
			@param s		The stream we're reading from
			@param setDirty	kTrue if object should be marked dirty after loading
			@param length	Length of the object in the stream, in number of bytes
		*/
	virtual void LoadAll(IPMStream *s, bool16 setDirty, int32 length = 0) = 0;

		/** Stream out all persistent interfaces of the object into
			the stream (s). After the object is streamed out, the
			dirty flag is cleared if clearDirty is kTrue. When streaming
			objects out to the database, clearDirty should be kTrue.
			In all other cases, clearDirty should be false.
			@param s			The stream to write to
			@param clearDirty	kTrue if dirty flag should be cleared after write
		*/
	virtual void SaveAll(IPMStream *s, bool16 clearDirty) = 0;


		/** Mark an interface of the object as dirty.
			Should not be called directly -- usually called by calling Dirty() on 
			the interface, or calling PersistUtils::Dirty().
			@param p					The dirty interface
			@param prop					ImplementationID of the dirty interface
			@param allowModification	kTrue if the database should be marked as dirty,
										false if it's an "optional dirty" which should be
										written out only if the database is dirtied.
		*/
	virtual void SetDirty(IPMUnknown *p, ImplementationID prop, bool16 allowModification = kTrue) = 0;

	virtual void SetDirtyAllowDuplicateMessage(IPMUnknown *p, ImplementationID prop, bool16 allowModification = kTrue) = 0;

	virtual void SetDirtyOverrideMessage(IPMUnknown *p, PMIID overrideIID, ImplementationID prop, bool16 allowModification = kTrue) = 0;

	virtual void SetDirtyOverrideAllowDuplicateMessage(IPMUnknown *p, PMIID overrideIID, ImplementationID prop, bool16 allowModification = kTrue) = 0;


	/**@name  For internal use only */
	//@{-----------------------------------------------------------------------------
		// -----------------------------------------------------------
		// INTERNAL USE ONLY
		// -----------------------------------------------------------


		// Internal Use Only
		// Tell the object what its persistent key is. This is called
		// once from the database when an object is instantiated. 
		// It should never be called from anywhere else.
	virtual void Init(IDataBase *db, UID id) = 0;

		// Internal Use Only
		// Creates a content iterator that can be used to iterate through the 
		// data in the stream. Caller is responsible for deleting
		// @return The new iterator.
	virtual IContentReadIterator *NewReadIterator(IPMStream *s) = 0;

		// Internal Use Only
		// Creates a content iterator that can be used to iterate through the 
		// data in the object, writing to the stream. Caller is responsible 
		// for deleting
		// @return The new iterator.
	virtual IContentWriteIterator *NewWriteIterator(IPMStream *s) = 0;
		
		// Internal Use Only.
		// Load a single interface in from the stream.
	virtual void LoadOne(IPMStream *s, ImplementationID prop, IPMUnknown *loadThis, bool16 setDirty) = 0;
	
		/** Internal Use Only.
			Stream out the persistent interfaces of the object that
			are dirty, combining them with the saved object state in
			the database. 
			@param s			The stream to write to
			@param clearDirty	kTrue if dirty flag should be cleared after write
		*/
	virtual void SaveDirty(IPMStream *s, bool16 clearDirty = kTrue) = 0;
	
		// Internal Use Only
	virtual void SaveSingleInterface(InterfaceReadWrite readWriter, IPMUnknown *face, IPMStream *s, ImplementationID tag, IContentTracker *contentTracker) = 0;	
	
		// allowModification indicates whether on not to consider the pub changed (i.e. prompt the user to save).
	virtual bool16 IsDirty(const IPMUnknown *p) const = 0;
	
	// for internal use - please do not call 
	virtual void ClearDirty() = 0;

	// for internal use - please do not call 
	virtual void ResetOneToSnapshot(ImplementationID prop, SnapshotID snapshotID, ISnapshotCache* snapshotCache) = 0;

	// for internal use - please do not call 
	virtual SnapshotID SnapshotDirty (ImplementationID prop) = 0;
	// for internal use - please do not call 
	virtual void SnapshotDirty () = 0;

	// for internal use - please do not call 
	virtual	void RefreshCachedLastRevInfoAfterDBClone(bool objIsReferenced) = 0;

	// for internal use - please do not call 
	virtual	void UpdateReadStamps() = 0;

	// for internal use - please do not call 
	virtual void MarkDirtyInterfacesToBeCopiedAtNextMiniSave() = 0;
//@}-----------------------------------------------------------------------------
};



#endif // __IPMPersist__
