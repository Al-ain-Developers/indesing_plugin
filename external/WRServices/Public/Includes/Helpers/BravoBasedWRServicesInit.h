#ifndef __BravoBasedWRServicesInit__
#define __BravoBasedWRServicesInit__

#include "WRMem.h"
#include "WRServices.h"

#if !defined(WR_CT5) && !defined(WR_CT5A)	
	#error FontAccess helper must be included before this header or WR_CT5 or WR_CT5A symbol must be defined 
#endif

#ifdef BIB_MULTI_THREAD
class BravoBasedMultiProcessing : public IWRMultiProcessing
{
public:
	BravoBasedMultiProcessing() {};
	virtual ~BravoBasedMultiProcessing() {};

	virtual WRMutex*			CreateMutexI() ;
	virtual	void				DisposeMutex(WRMutex* mutex) ;
	virtual	void				LockMutex(WRMutex* mutex) ;
	virtual	void				UnlockMutex(WRMutex* mutex) ;

	virtual WRReadWriteLock*	CreateReadWriteLock() ;
	virtual	void				DisposeReadWriteLock(WRReadWriteLock* rwlock) ;
	virtual	void				LockReader(WRReadWriteLock* rwlock) ;
	virtual	void				UnlockReader(WRReadWriteLock* rwlock) ;
	virtual	void				LockWriter(WRReadWriteLock* rwlock) ;
	virtual	void				UnlockWriter(WRReadWriteLock* rwlock) ;
};

WRMutex* BravoBasedMultiProcessing::CreateMutexI()
{
	return (WRMutex*) new BRVMutualExclusion();
}

void BravoBasedMultiProcessing::DisposeMutex(WRMutex* mutex)
{
	BRVMutualExclusion* brvMutex = (BRVMutualExclusion*) mutex;
	delete brvMutex;
}

void BravoBasedMultiProcessing::LockMutex(WRMutex* mutex)
{
	BRVMutualExclusion* brvMutex = (BRVMutualExclusion*) mutex;
	brvMutex->Lock();
}

void BravoBasedMultiProcessing::UnlockMutex(WRMutex* mutex)
{
	BRVMutualExclusion* brvMutex = (BRVMutualExclusion*) mutex;
	brvMutex->Unlock();
}

WRReadWriteLock* BravoBasedMultiProcessing::CreateReadWriteLock()
{
	return (WRReadWriteLock*) new BRVMultipleReaderSingleWriter(true);
}

void BravoBasedMultiProcessing::DisposeReadWriteLock(WRReadWriteLock* mutex)
{
	BRVMultipleReaderSingleWriter* brvReadWriteLock = (BRVMultipleReaderSingleWriter*) mutex;
	delete brvReadWriteLock;
}

void BravoBasedMultiProcessing::LockReader(WRReadWriteLock* mutex)
{
	BRVMultipleReaderSingleWriter* brvReadWriteLock = (BRVMultipleReaderSingleWriter*) mutex;
	brvReadWriteLock->ReadLock();
}

void BravoBasedMultiProcessing::UnlockReader(WRReadWriteLock* mutex)
{
	BRVMultipleReaderSingleWriter* brvReadWriteLock = (BRVMultipleReaderSingleWriter*) mutex;
	brvReadWriteLock->ReadUnlock();
}

void BravoBasedMultiProcessing::LockWriter(WRReadWriteLock* mutex)
{
	BRVMultipleReaderSingleWriter* brvReadWriteLock = (BRVMultipleReaderSingleWriter*) mutex;
	brvReadWriteLock->WriteLock();
}

void BravoBasedMultiProcessing::UnlockWriter(WRReadWriteLock* mutex)
{
	BRVMultipleReaderSingleWriter* brvReadWriteLock = (BRVMultipleReaderSingleWriter*) mutex;
	brvReadWriteLock->WriteUnlock();
}
#else

#define BravoBasedMultiProcessing IWRMultiProcessing

#endif

/// An helper interface to encapsulate and facilitate the WRServices pre-initialization procedure
/** BravoBasedWRServicesInit should be used instead of direct WRServicesPreInitialize calls when client use Bravo for Multiprocessing and 
CoolType5*BasedFontAccess. This helper helps to manage multiple initialization scheme, sets automaticaly MultiProcessing based on Bravo BIB 
library and creates instance of CoolTypeBasedHelper.
The .h and .cpp files should be included AFTER FontAccess Helper.
**/
class BravoBasedWRServicesInit
{
	static WRUInt32 fPreInitCount;
	static WRMemObj *fMemObj;
	static BravoBasedMultiProcessing *fMultiProcessing;
	static IWRFontAccess* fFontAccess;

public:
	/// WRServices preinitialization
	/** This routine MUST BE called before WRServicesInitialize calls AND AFTER Bravo libraries are initialized (CTInit, BIBInit).
		@param memObj a pointer to a WRMemObj object containing pointers to allocator and deallocator routine, use NULL to use standard internal allocators.
		@param createFontAccess a bool, true to create a font access, pointed by fFontAccess 
		@return a WRServices Error
	**/
	static WRInt32 PreInitialize(WRMemObj *memObj, bool createFontAccess = true)
	{
		if (fPreInitCount != 0)
			return kWRNoErr;
		
		fMemObj = memObj;

		WRServicesPreInitialize(memObj);

		fPreInitCount = WRServicesGetPreInitializeCount();
		
		if (fPreInitCount == 1)
		{
			//Only first Client should initialize Multi Threading.
#ifdef BIB_MULTI_THREAD
			fMultiProcessing = new BravoBasedMultiProcessing();
#else
			fMultiProcessing = NULL;
#endif

			WRServicesSetMultiProcessing(fMultiProcessing);

			if (createFontAccess)
			{
#ifdef WR_CT5
				fFontAccess = new CoolType5BasedFontAccess();
#elif defined(WR_CT5A)
				fFontAccess = new CoolType5aBasedFontAccess();
#endif
			}
			
			WRServicesSetFontAccess(fFontAccess);
		}

		return kWRNoErr;
	}

	/// WRServices postterminate
	/** This routine MUST BE called AFTER WRServicesTerminate calls AND BEFORE Bravo libraries are terminated.
		If kWRPostTerminateTooEarlyErr is returned, it means client allocator were passed in PreInitialize but the client is not the last one to PostTerminate. 
		This situation should be treated as critical condition.
		@return a WRServices Error
	**/
	static WRInt32 PostTerminate()
	{
		//PreInitialize never called? Exit gracefully
		if (fPreInitCount == 0)
			return kWRNoErr;
		
		//Attention!!! fMemObj is not accessible at this time, only its original address can be compared with NULL
		
		//Error condition - we are not last to terminate, but we were first to preinit with our own membuffer - NOT GOOD!!!
		if (fMemObj != NULL && fPreInitCount == 1 && WRServicesGetPreInitializeCount() != 1)\
		{
			//This really should not happen! EVER! 
			return kWRPostTerminateTooEarlyErr;
		}

		//call the real PostTerminate - ref count is handled inside
		WRServicesPostTerminate();

		fPreInitCount--;

		//These deletes are done directly in WRServicesPostTerminate, we can't call it here, because we lost our memory manager in WRServicesPostTerminate();
		//delete fMultiProcessing;
		//delete fFontAccess;

		return kWRNoErr;
	}
};
#endif


