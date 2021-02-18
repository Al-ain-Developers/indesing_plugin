//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDatabaseSnapshot.h $
//  
//  Owner: Habib Khalfallah 
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
#ifndef __IDatabaseSnapshot__
#define __IDatabaseSnapshot__
#include "IDataBase.h"
#include <boost/intrusive_ptr.hpp>
#include "IDThreadingPrimitives.h"

// For internal use only
// This defines the abstract interface for database snapshot.

class IDatabaseSnapshot;
typedef boost::intrusive_ptr<IDatabaseSnapshot>	DatabaseSnapshotPtr;
class IPubFile;
class IDataBase;
class MemXferBytes;

class IDatabaseSnapshot
{
public:
	IDatabaseSnapshot() : fRefCount(0)
	{}
	
	virtual ~IDatabaseSnapshot() {};
	
	virtual void SetFileInfo(IPubFile*  pubFile, const IDFile & sysFileFromOpen) = 0;
	virtual IPubFile*  GetPubFile() const = 0;
	virtual const IDFile & GetSysFileFromOpen () const = 0;
	// Tmp solution to links updates optimization
	// For more generic solution we need to use a time-stamp like thing 
	virtual uint32  GetLinksUpdateSeed() const = 0;
	virtual void SetLinksUpdateSeed(uint32  seed) = 0;
	virtual IDatabaseSnapshot* GetLastDBSnapshotBeforePubFileSharing () const = 0;
	virtual void DetatchFromBase() = 0;
	virtual IDataBase* CreateCloneDataBase() = 0;

	virtual void AddRef() 
	{
		IDThreading::AtomicIncrement(fRefCount);
	}
	virtual void Release()
	{
		const uint32 newCount = IDThreading::AtomicDecrement(fRefCount);
		ASSERT (newCount < uint32(-1));
		if (newCount == 0)
		{
			delete this;
		}
	}

	virtual MemXferBytes* GetPrivateDataForHTTPLinks() = 0;
	virtual void SetPrivateDataForHTTPLinks(MemXferBytes* bytes) = 0;
protected:
	volatile uint32 fRefCount; // atomic

	friend void intrusive_ptr_add_ref(IDatabaseSnapshot* p)
	{
		p->AddRef();
	}

	friend void intrusive_ptr_release(IDatabaseSnapshot* p)
	{
		p->Release();
	}
};
#endif