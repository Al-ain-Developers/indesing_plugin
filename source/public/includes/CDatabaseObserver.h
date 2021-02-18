//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDatabaseObserver.h $
//  
//  Owner: Paul Messmer
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
#ifndef __CDatabaseObserver__
#define __CDatabaseObserver__

#include "IDataBase.h"
#include "IDatabaseObserver.h"

#pragma export on

/** To find out when certain database actions happen, implement an DatabaseObserver and attach 
	it to the database.  Database observers should inherit from CDatabaseObserver and 
	not IDatabaseObserver.  See IDatabaseObserver for full details.

	@see IDataBaseObserver
	@ingroup arch_db
*/

class PUBLIC_DECL CDatabaseObserver : public IDatabaseObserver
{
public:	
	virtual void SetDirty(IDataBase *db, UID id, ClassID clsID, ImplementationID tag, const bool16 dbModified);
	virtual void NewUID(IDataBase *db, UID id, ClassID clsID);
	virtual void DeleteUID(IDataBase *db, UID id, ClassID clsID);
	virtual void UndeleteUID(IDataBase *db, UID id, ClassID clsID);
	virtual void DestroyDeletedUID(IDataBase *db, UID id);
	virtual void BeginTransaction(IDataBase *db);
	virtual void EndTransaction(IDataBase *db);
	virtual void SetModified(IDataBase *db, bool16 modified);
	virtual void AttachedTo(IDataBase* db);
};

#pragma export off

#endif