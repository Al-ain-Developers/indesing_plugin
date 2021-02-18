//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRIDXNotifierUtils.h $
//  
//  Owner: Danielle Darling
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
#ifndef __IRIDXNOTIFIERUTILS__
#define __IRIDXNOTIFIERUTILS__

#include "IPMUnknown.h"
#include "IRIDX.h"
#include "IRIDXNotifierHandler.h"
#include "AppFrameworkID.h"
#include "K2SmartPtr.h"
#include "Utils.h"

// ===================================================================================
//	class IRIDXNotifierUtils 
// ===================================================================================
/** Utility called on a reference when it is being modified in some way, deleted, or just to query if it is being 
	actively used.  These functions all call the @IRIDXNotifierHandler interface defined by the RIDXNotifierService provider to do its processing
*/

/**	Helper class to facilitate processing of IsActivelyUsed when IsActivelyUsed is called repeated on the
	same database for similar target UID class.
*/

class RIDXNotifierCacheData
{
public:
	RIDXNotifierCacheData ():
		fRIDXQuery (nil), fTargetClassID (kInvalidClass) {}
		
		~RIDXNotifierCacheData () 
		{
		if (fRIDXQuery != nil) fRIDXQuery->Release ();
		}

public:
	boost::shared_ptr<K2Vector<InterfacePtr<IRIDXNotifierHandler> > >	fHandlers;
	IRIDXQuery*						fRIDXQuery;
	ClassID							fTargetClassID;
};

class IRIDXNotifierUtils : public IPMUnknown 
{
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_IRIDXNOTIFIERUTILS};

	/**
	 	UIDDeleted: Nofitication sent when this particular UID is being deleted, called HandleUIDDeleted in @IRIDXNotifierHandler
	 	@param db					The database it is being deleted from
	 	@param targetUID			The uid being deleted
	 	@param iDataForDeleting		Any data object that may be associated with the target UID being deleted.
	 */
	virtual void BeingDeleted(IDataBase *db, UID targetUID, const IPMUnknown* iDataForDeleting) const = 0;

	/**
	 	UIDDeleted: Nofitication sent when this particular UID is being deleted, called HandleUIDDeleted in @IRIDXNotifierHandler
	 	@param db					The database it is being deleted from
	 	@param targetUIDList		The uid list being deleted
	 	@param iDataForDeleting		Any data object that may be associated with the target UID being deleted.
	 */
	virtual void BeingDeleted(IDataBase *db, const UIDList& targetUIDList, const IPMUnknown* iDataForDeleting) const = 0;

	/**
	 	WillBeModified: Nofitication sent when the data owned by a particular UID is about to be modifited, called HandleUIDModified in @IRIDXNotifierHandler
	 	@param db					The database it is being deleted from
	 	@param targetUID			The uid being modified
	 	@param iDataForModifying	Any data object that may be associated with the target UID being modified.
	 */
	virtual void WillBeModified(IDataBase *db, UID targetUID, const IPMUnknown* iDataForModifying) const = 0;

	/**
	 	WillBeModified: Nofitication sent when the data owned by a particular UID is about to be modifited, called HandleUIDModified in @IRIDXNotifierHandler
	 	@param db					The database it is being deleted from
	 	@param targetUIDList		The uid list being modified
	 	@param iDataForModifying	Any data object that may be associated with the target UID being modified.
	 */
	virtual void WillBeModified(IDataBase *db, const UIDList& targetUIDList, const IPMUnknown* iDataForModifying) const = 0;

	/**
	 	UIDIsActivelyUsed: Nofitication sent when the uid is still being actively used by a client, 
	 	calls UIDIsActivelyUsed in IRIDXNotifierHandler
	 	@param db					The database it is being deleted from
	 	@param targetUID			The uid being modified
	 	@param iOptionData			Any data object that may help in determining if target UID is referenced.
	 	@param pNotifierCache		A notifier cache to use when this method is called repeatedly on the same database and
	 								with similar target class of target UID. If a cache is not passed in,
	 								the process of testing for references will be much slower since we will have to create a RIDX query
	 								every time this is called.
	 */
	virtual bool16 IsActivelyUsed(IDataBase *db, UID targetUID, const IPMUnknown* iOptionData = nil, RIDXNotifierCacheData* pNotifierCache = nil) const = 0;

	/**
	 	Swatch UID converted or deleted: Nofitication sent when the swatch UIDs are being converted to global swatch.
	 	In some cases, UID is replaced. 
	 	@param db					The database it is being deleted from
	 	@param targetUIDList		The uid list being modified or deleted
	 	@param iOptionData			Any data object required by the client.
	 */
	virtual	void SwatchesWillBeConvertedLocalToGlobal (IDataBase *db, const UIDList& targetUIDList, const IPMUnknown* iData) const = 0;
};

#endif

