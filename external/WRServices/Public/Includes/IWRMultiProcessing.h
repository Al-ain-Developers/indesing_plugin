//========================================================================================
//  
//  File: IWRMultiProcessing.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 2001 WinSoft SA. All rights reserved.
//  
//========================================================================================

#ifndef __IWRMultiProcessing__
#define __IWRMultiProcessing__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRFontContextComponent.h"


class IWRMultiProcessing;
class IWRFontContext;

class WRMutex; ///< opaque type for reprsenting mutexes (always handled by pointer and casted by the client to actual types)
class WRReadWriteLock; ///< opaque type for reprsenting read write locks (always handled by pointer and casted by the client to actual types)

/// Isterface for the multi-thread synchronization
/** 
If a WRFontContext is in a multi-thread context, access must be synchronized. Instead of embedding its 
own primitives, Lipika relies on the implementation supplied by the client, through the subclassing of this
interface.
It is required to provide two types of primitives: Mutexes and Multiple reader - single write locks.
**/
class WRSERVICES_DECL IWRMultiProcessing : public WRFontContextComponent
{
public:
	virtual ~IWRMultiProcessing();
	virtual WRMutex*			CreateMutexI() = 0;					///< allocate a new mutex object
	virtual	void				DisposeMutex(WRMutex* mutex) = 0;	///< delete a mutex object allocated by CreateMutex
	virtual	void				LockMutex(WRMutex* mutex) = 0;		///< acquire mutex
	virtual	void				UnlockMutex(WRMutex* mutex) = 0;	///< release mutex

	virtual WRReadWriteLock*	CreateReadWriteLock() = 0;							///< allocate a new multiple reader single writer lock object
	virtual	void				DisposeReadWriteLock(WRReadWriteLock* rwlock) = 0;	///< delete a lock object allocated by CreateReadWriteLock
	virtual	void				LockReader(WRReadWriteLock* rwlock) = 0;			///< acquire a lock for reading
	virtual	void				UnlockReader(WRReadWriteLock* rwlock) = 0;			///< release a lock that was acquired for reading
	virtual	void				LockWriter(WRReadWriteLock* rwlock) = 0;			///< acquire a lock for writing
	virtual	void				UnlockWriter(WRReadWriteLock* rwlock) = 0;			///< release a lock that was acquired for writing
};



#endif
