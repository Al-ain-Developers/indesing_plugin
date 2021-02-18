//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/bossrecycler.tpp $
//  
//  Owner: roey horns
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

#include "Trace.h"
#include "ISession.h"
#include "InterfaceTrackingUtils.h"
#ifdef INTERFACEPROXIES_SUPPORTED
#include "DebugControllingUnknown.h"
#endif

// store unreferenced instances into the repository rather than deleting them
template <class T>
void BossRecycler<T>::Release() const
{
#ifdef INTERFACEPROXIES_SUPPORTED
// hkhalfal April 18 2001 If tarcking going on do not recycle
    if(fOwningBoss && fOwningBoss != this)
 {
        PMControllingUnknown::Release();
       return;
  }
#endif
#ifdef DEBUG

	if(GetPersist() != nil)
	{
		if(!ts_Asserted)
		{
			ASSERT_FAIL("Do not use the BossRecycler for persistent bosses");
			ts_Asserted = kTrue;
		}

		PMControllingUnknown::Release();
		return;
	}

	// copied from PMControllingUnknown::Release
	ASSERT_MSG(fRefCount < 32768, "Warning: this object has a really high ref count");
	ASSERT_MSG(fRefCount >= 0, "Releasing object too many times!");

	if((fRefCount == 1) && (kCheckProcPtr != nil))
	{
		if(!kCheckProcPtr(const_cast<BossRecycler<T>*>(this)))
		{
			delete this;
			return;
		}
	}
#endif


	if(--fRefCount == 0)
	{
		if(tl_RepositoryState.Get() == kToBeAllocated)
		{
			CreateRepository();
		}

		RepositoryState prev_RepositoryState = tl_RepositoryState.Get();
		if (prev_RepositoryState == kAllocated)
			tl_RepositoryState.Set(kAllocatedCannotDelete);
		if(fExecutionContextIDAtCreation == IDThreading::CurrentExecutionContextId() &&
			tl_RepositoryState.Get() > kToBeAllocated && tl_Repository.Get()->size() < kMaxSize)
		{
			if(!tl_Registered.Get())
			{
				Register();
			}
			// prevent nested deletion of tl_Repository.Get() originated by a call to BossRecycler<T>::DisposeRepository following a purge
			tl_Repository.Get()->push_back(this);

#ifdef DEBUG
			if(tl_Repository.Get()->size() > ts_HighWaterMark)
				ts_HighWaterMark = tl_Repository.Get()->size();
#endif
		}
		else
		{
			delete this;
		}
		if (prev_RepositoryState == kAllocated)
			tl_RepositoryState.Set(kAllocated);
	}
}



// check first for recycleable instances in the repository before it
// creates a new instance.
// it uses the repository on a last in-first out basis because this seems
// to be the most efficient way for the current implementation of our
// K2Vector.
template <class T>
void *BossRecycler<T>::Factory(ClassID clsID)
{
	BossRecycler<T> *newBoss = nil;
	if(tl_RepositoryState.Get() > kToBeAllocated)
	{
		// prevent nested deletion of tl_Repository.Get() originated by a call to BossRecycler<T>::DisposeRepository following a purge
		RepositoryState prev_RepositoryState = tl_RepositoryState.Get();
		if (prev_RepositoryState == kAllocated)
			tl_RepositoryState.Set(kAllocatedCannotDelete);
		if (!tl_Repository.Get()->empty())
		{
			newBoss = (BossRecycler<T> *) tl_Repository.Get()->back();
			newBoss->AddRef();
			tl_Repository.Get()->pop_back();
#ifdef DEBUG
			ts_RecycledCount++;
#endif
		}
		if (prev_RepositoryState == kAllocated)
				tl_RepositoryState.Set(kAllocated);
	}

	if(newBoss == nil)
	{
		newBoss = new BossRecycler<T>(clsID);
#ifdef DEBUG
		ts_NewCount++;
#endif
	}
	return newBoss;
}


// Allocates the memory for the repository.
template <class T>
void BossRecycler<T>::CreateRepository(void)
{
	if(tl_RepositoryState.Get() == kToBeAllocated)
	{

		if (GetExecutionContextSession())
		{
			ISession::SessionStateType const sessionState = GetExecutionContextSession()->GetState();

			if(sessionState > ISession::kRunning)
			{
				// the first instance of this boss was created
				// at shutdown time, so we will not be able
				// to create the repository

				tl_RepositoryState.Set(kKilled);
			}
			else if(sessionState == ISession::kRunning)
			{
				tl_Repository.Set(new RepositoryType());
				tl_RepositoryState.Set(kAllocated);
			}
		}
		else
			tl_RepositoryState.Set(kKilled);	
	}
}

template <class T>
void BossRecycler<T>::DisposeRepository(void)
{
	if(tl_RepositoryState.Get() == kAllocated)
	{
		// prevent nested deletion of tl_Repository.Get() originated by a call to BossRecycler<T>::DisposeRepository following a purge
		tl_RepositoryState.Set(kAllocatedCannotDelete);
		while (!tl_Repository.Get()->empty())
		{
			delete (BossRecycler<T>*) tl_Repository.Get()->back();		
			tl_Repository.Get()->pop_back();
		}

		delete tl_Repository.Get();
		tl_Repository.Set(nil);
		tl_RepositoryState.Set(kToBeAllocated);	
	}
}


// Registers the ShutdownNotification method at theShutdownNotificationService.
// Since we may get called BEFORE a valid session with service providers is established
// or AFTER the session has already shut down the services we need to check for a valid,
// running session first.
template <class T>
void BossRecycler<T>::Register(void)
{
	if(!tl_Registered.Get())
	{
		tl_Registered.Set(tl_ShutdownNotifier.Get()->Register(BossRecycler<T>::ShutdownNotification));
	}
}


// This is called by the Shutdown Notification Service upon shutdown
template <class T>
void BossRecycler<T>::ShutdownNotification(void)
{
	DisposeRepository();

#ifdef DEBUG
	TRACEFLOW_OBSOLETE("Old:XMediaUI", "Recycling statistics for %s:\n", k_BossName.GetUTF8String().c_str());
	TRACEFLOW_OBSOLETE("Old:XMediaUI", "Purges: %ld  -  Newed Bosses: %ld  -  Recycled Bosses: %ld  -  Repository High Water Mark: %ld\n", ts_KillCount, ts_NewCount, ts_RecycledCount, ts_HighWaterMark);
#endif
}