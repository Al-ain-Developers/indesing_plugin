//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDatabaseObserver.h $
//  
//  Owner: John Dance
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
#ifndef __IDATABASEOBSERVER__
#define __IDATABASEOBSERVER__

#include "IPMUnknown.h"

class IDataBase;

/** To find out when certain database actions happen, implement a DatabaseObserver and attach 
	it to the database. The DatabaseObserver will get called by the database on interesting
	database events. This does not follow the normal subject/observer pattern. Each database
	maintains its own list of observers, so attach to the database you are interested in.
	Note that for ease of maintanence we strongly recommend you NOT inherit directly from IDatabaseObserver
	but rather from CDatabaseObserver instead.
	
	 To use this interface...
	 \li Derive an implementation from CDatabaseObserver, and attach it to a new or existing boss in the .fr file.
	 \li Override methods from CDataBaseObserver for desired actions called by database.
	 \li Override GetEventClassesToObserve and return a combination of IDatabaseObserver::Observable constants corresponding to methods you overrode
	 \li Attach to the database desired with AttachDataObserver
	 
	 @see IDataBase
	 @ingroup arch_db
*/

class IDatabaseObserver : public IPMUnknown {
public:

	/** This enumeration describes the classes of events that a database observer
		    is interested in seeing.  In InDesign/InCopy CS and earlier, database observers 
			would be called for everything, which could hurt performance.  Now your
			GetEventClassesToObserver() will get called during attachment and must specify
            what classes of things it is interested in observing by combining together these Observable constants.
		*/
	enum Observable {
		kWatchDirties = 1,						/** Watch every DirtyObject call - expensive!						*/
		kWatchUIDCreationDestruction = 2,		/** Watch NewUID(), DLeteUID(), UndeleteUID(), DestoryDeletedUID()	*/
		kWatchTransactions = 4,					/** Watch BeginTransaction() and EndTransaction()					*/
		kWatchModified = 8,						/** Watch modification state of database							*/

		kWatchAll = 0xffffffff					/** Watch everything - expensive!!	Be sure you need this if used	*/
	};

		/** Called by the database when it gets a DirtyObject.
			@param db the database we're observing
			@param id the UID that was dirtied
			@param tag the ImplementationID that was dirtied
			@param dbModified kTrue if this dirty could have caused the database to be marked as modified
		*/
	virtual void SetDirty(IDataBase *db, UID id, ClassID clsID, ImplementationID tag, const bool16 dbModified) = 0;

		/** Called by the database when it gets a NewUID.
			@param db the database we're observing
			@param id the UID that was created
			@param clsID the class of the new UID
		*/
	virtual void NewUID(IDataBase *db, UID id, ClassID clsID) = 0;

		/** Called by the database when it gets a DeleteUID.
			@param db the database we're observing
			@param id the UID that was deleted
			@param clsID the class of the deleted UID
		*/
	virtual void DeleteUID(IDataBase *db, UID id, ClassID clsID) = 0;

		/** Called by the database when it gets an UndeleteUID.
			@param db the database we're observing
			@param id the UID that was restored
			@param clsID the class of that the UID was restored to
		*/
	virtual void UndeleteUID(IDataBase *db, UID id, ClassID clsID) = 0;
	
		/** Called by the database when it gets an DestroyDeletedUID.
			@param db the database we're observing
			@param id the UID that was destroyed
		*/
	virtual void DestroyDeletedUID(IDataBase *db, UID id) = 0;

		/** Called by the database when it gets an BeginTransaction.
			@param db the database we're observing
		*/
	virtual void BeginTransaction(IDataBase *db) = 0;

		/** Called by the database when it gets an EndTransaction.
			@param db the database we're observing
		*/
	virtual void EndTransaction(IDataBase *db) = 0;
	
		/** Called by the database when the logical modified state of the database changes.
			@param db the database we're observing
			@param modified is whether the database mofified state is set (e.g. file is dirty from the user's standpoint)
		*/
	virtual void SetModified(IDataBase *db, bool16 modified) = 0;
	
		/** Called by the database when the observer is attached.
			@param db the database we're observing
		*/
	virtual void AttachedTo(IDataBase* db) = 0;
	
		/** Called to discover which methods you are overriding and are interested in having called.
			@erturn a logically-ORed combination of IDatabaseObserver::Observable constants specifying what events this observer should be called for
		*/
	virtual uint32 GetEventClassesToObserve() = 0;
};

#endif // __IDATABASEOBSERVER__
