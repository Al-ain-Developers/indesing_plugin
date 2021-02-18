//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/bossrecycler.h $
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
//  
//  Notes on the Usage of BossRecylcer
//  
//  When to use
//  
//  You may use the BossRecycler for bosses that:
//  
//  1. 	are not persistent
//  2. 	are instantiated and deleted often
//  3. 	do not have a custom boss implementation
//  4. 	are reusable (do not rely on beeing freshly newed)
//  
//  How to use
//  
//  In order to use it enter the following two lines in any of the boss'
//  interface .cpp files (but only in one!):
//  
//  include "BossRecycler.h"
//  define RECYCLE_BOSS(boss, maxsize, minsize, chunkSize, bossname, instanceCheckProc)
//  
//  the parameters:
//  boss				the class to recycle
//  maxsize				a maximum size for the recycling repository
//  minsize				a minimum size of the reclycling repository (will not be purged back beyond this point)
//  chunkSize
//  bossname
//  instanceCheckProc	you may provide a method to check instances that are going
//  to be added
//  
//  How it works
//  
//  The RECYCLE_BOSS boss macro declares and defines a custom boss class
//  for your boss. It inherits from PMControllingUnknown and stores unreferenced
//  instances in a storage rather than deleting them. The custom factory method
//  of this boss looks in it's storage for a reusable instance before it creates
//  a new one.
//  
//  How to evaluate it's efficiency
//  
//  In the debug build the recycling boss will trace some statistic data
//  at shutdown time:
//  
//  Recycling statistics for Database Read Stream:
//  Purges: 1  -  Newed Bosses: 9  -  Recycled Bosses: 3110  -  Repository High Water Mark: 6
//  
//  Purges
//  tells you how often the boss repository of unused bosses had to be purged
//  due to low memory.
//  
//  Newed Bosses
//  should be low (depends on the number of purges)
//  tells you how often a new boss (with all it's interfaces) had to be created
//  in the traditional way using new.
//  
//  Recycled Bosses
//  should be high
//  tells you how often a new boss (with all it's interfaces) was reused
//  by simply returning an unsused boss from the repository
//  
//  Repository High Water Mark
//  should be low
//  gives the maximum count of bosses in the repository at any given time
//  
//  Keep our memory clean - recycle your bosses!
//  
//========================================================================================

#pragma once
#ifndef __BossRecycler__
#define __BossRecycler__

#include "PMControllingUnknown.h"
#include "ClassFactory.h"
#include "ShutdownNotifierHelper.h"
#include <boost/thread/recursive_mutex.hpp>
#include "IExecutionContext.h"
#include "BypassAllocator.h"
#ifdef DEBUG
	#include "PMString.h"
#endif

#ifdef DEBUG
		typedef bool16 (*InstanceCheckProc)(IPMUnknown* instance);
#endif

class BossRecyclerShutdownNotifierHelper : public  BaseShutdownNotifierHelper
{
public:
	BossRecyclerShutdownNotifierHelper():
	BaseShutdownNotifierHelper(kBossRecyclerShutdownNotificationService)
	{}
};

template <class T>
class BossRecycler : public PMControllingUnknown
{
	public:
		typedef std::vector<const IPMUnknown*, BypassAllocator<const IPMUnknown*> > RepositoryType;
		typedef RepositoryType::size_type size_type;

		BossRecycler(const ClassID theClass) : 
			PMControllingUnknown(theClass),
			fExecutionContextIDAtCreation(IDThreading::CurrentExecutionContextId())
			{}

		BossRecycler(IClassInfo *theClass) : 
			PMControllingUnknown(theClass),
			fExecutionContextIDAtCreation(IDThreading::CurrentExecutionContextId())
			{}

		virtual void Release() const;
		// unreferenced instances of this boss class will be collected in a
		// repository for recycling

		static void *Factory(ClassID clsID);
		// factory tries to recycle an instance from the repository
		// if the repository is empty or not available a new
		// instance is created

	private:
		static void CreateRepository(void);
		static void DisposeRepository(void);


		static void Register(void);
		// registers the EmptyRepository method below at the MemoryNotificationService
		static void ShutdownNotification(void);
		// allthough considered as private this is called by the MemoryManager
		typedef enum RepositoryState
		{	kKilled, kToBeAllocated, kAllocated, kAllocatedCannotDelete	} RepositoryState;	

		const IDThreading::ExecutionContextID fExecutionContextIDAtCreation;	// The ID of the execution context in which we are created
		static IDThreading::ThreadLocal<RepositoryState> 	tl_RepositoryState;
		static IDThreading::ThreadLocal<RepositoryType*>	tl_Repository;
		const static typename BossRecycler<T>::size_type					kMaxSize;
		const static typename BossRecycler<T>::size_type					kMinSize;
		const static typename BossRecycler<T>::size_type					kGrowSize;
		static IDThreading::ThreadLocal<bool16>						tl_Registered;

#ifdef DEBUG	// gathering statistics in order to evaluate the efficiency of the repository
		static typename BossRecycler<T>::size_type			ts_KillCount, ts_NewCount, ts_RecycledCount, ts_HighWaterMark;
		static const PMString 			k_BossName;
		static bool16 				ts_Asserted;
		
		// optional check method for instances
		static const InstanceCheckProc			kCheckProcPtr;
#endif
};

// hkhalfal: tl_ShutdownNotifier should be local to the bossrecycler template class. 
// The reason tl_ShutdownNotifier has a gloabl scope is that, on the mac, making it local prevents linking
// ObjectModelLib.
// ToDo: fix this problem.
#ifndef tl_ShutdownNotifier_defined
static IDThreading::ThreadLocalManagedObject<BossRecyclerShutdownNotifierHelper>		tl_ShutdownNotifier;
#define tl_ShutdownNotifier_defined
#endif

#include "bossrecycler.tpp"

/* notes on the RECYCLE_BOSS macro

	The RECYCLE_BOSS macro defines a dummy class that is used as the type parameter for the
	BossRecycler template class.
	If there is a name conflict just change the lines "class _##boss##_ {};" in BOTH
	definitions (DEBUG and non-DEBUG).
*/

#ifdef DEBUG
	#define RECYCLE_BOSS(boss, maxsize, minsize, chunkSize, bossname, instanceCheckProc)															\
		class _##boss##_ {};										\
																	\
		template<> IDThreading::ThreadLocal<BossRecycler<_##boss##_>::RepositoryType*> 	BossRecycler<_##boss##_>::tl_Repository(nil);	\
		template<> IDThreading::ThreadLocal<BossRecycler<_##boss##_>::RepositoryState>	BossRecycler<_##boss##_>::tl_RepositoryState (\
																BossRecycler<_##boss##_>::kToBeAllocated);		\
		template<> IDThreading::ThreadLocal<bool16>				BossRecycler<_##boss##_>::tl_Registered(kFalse);	\
		template<> BossRecycler<_##boss##_>::size_type							BossRecycler<_##boss##_>::ts_KillCount=0;			\
		template<> BossRecycler<_##boss##_>::size_type						BossRecycler<_##boss##_>::ts_NewCount=0;			\
		template<> const BossRecycler<_##boss##_>::size_type					BossRecycler<_##boss##_>::kMaxSize=maxsize;		\
		template<> const BossRecycler<_##boss##_>::size_type					BossRecycler<_##boss##_>::kMinSize=minsize;		\
		template<> const BossRecycler<_##boss##_>::size_type					BossRecycler<_##boss##_>::kGrowSize=chunkSize;	\
		template<> BossRecycler<_##boss##_>::size_type							BossRecycler<_##boss##_>::ts_RecycledCount=0;		\
		template<> BossRecycler<_##boss##_>::size_type							BossRecycler<_##boss##_>::ts_HighWaterMark=0;		\
		template<> const PMString										BossRecycler<_##boss##_>::k_BossName (bossname);	\
		template<> bool16										BossRecycler<_##boss##_>::ts_Asserted = kFalse;	\
		template<> const InstanceCheckProc							BossRecycler<_##boss##_>::kCheckProcPtr(instanceCheckProc);	\
		ClassFactory g##boss##Factory(boss, BossRecycler<_##boss##_>::Factory);						\
		ClassFactory *Get##boss##Factory();															\
		ClassFactory *Get##boss##Factory()		{	return &g##boss##Factory;	}
#else

	#define RECYCLE_BOSS(boss, maxsize, minsize, chunkSize, bossname, instanceCheckProc)						\
		class _##boss##_ {};																		\
		template<> IDThreading::ThreadLocal<BossRecycler<_##boss##_>::RepositoryType*> 	BossRecycler<_##boss##_>::tl_Repository(nil);	\
		template<> IDThreading::ThreadLocal<BossRecycler<_##boss##_>::RepositoryState>	BossRecycler<_##boss##_>::tl_RepositoryState (\
																BossRecycler<_##boss##_>::kToBeAllocated);		\
		template<> IDThreading::ThreadLocal<bool16>			BossRecycler<_##boss##_>::tl_Registered(kFalse);	\
		template<> const BossRecycler<_##boss##_>::size_type				BossRecycler<_##boss##_>::kMaxSize=maxsize;		\
		template<> const BossRecycler<_##boss##_>::size_type				BossRecycler<_##boss##_>::kMinSize=minsize;		\
		template<> const BossRecycler<_##boss##_>::size_type				BossRecycler<_##boss##_>::kGrowSize=chunkSize;	\
		ClassFactory g##boss##Factory(boss, BossRecycler<_##boss##_>::Factory);						\
		ClassFactory *Get##boss##Factory();															\
		ClassFactory *Get##boss##Factory()		{	return &g##boss##Factory;	}

#endif // DEBUG

#endif // __BossRecycler__
