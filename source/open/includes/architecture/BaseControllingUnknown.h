//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/BaseControllingUnknown.h $
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
#ifndef __BaseControllingUnknown__
#define __BaseControllingUnknown__

#include "IControllingUnknown.h"
#include "IExecutionContext.h"

class IClassInfo;

#ifdef DEBUG
class LogObject;
#include "IDThreadingPrimitives.h"
#endif		// DEBUG

/**	BaseControllingUnknown is the base implementation class for all boss objects.
	It is the controller that keeps track of the multiple interfaces of the boss.
	All controlling unknowns should inherit from BaseControllingUnknown, so that
	debugging tools, like boss tracking, will work consistently for all bosses.
*/
class PUBLIC_DECL BaseControllingUnknown : public IControllingUnknown
{
public:
	BaseControllingUnknown(const ClassID theClass);
	BaseControllingUnknown(IClassInfo const* theClass);
	virtual ~BaseControllingUnknown();

	virtual void AddRef() const;
	virtual void Release() const;
	virtual void LastRelease() const;
			
	virtual ClassID GetClass() const;		

	virtual uint32 GetRefCount() const;
	virtual IPMUnknown* GetInterfacePtr(ImplementationID implID) const;
	virtual PMIID GetInterfaceID(IPMUnknown *p) const;
	virtual IPMUnknown* GetInterfacePtr(PMIID interfaceID) const = 0;
	virtual const IPMPersist* GetPersist() const = 0;


#ifdef DEBUG
	virtual void SetDebugUID (UID id);
	virtual void DebugAddRef(IPMUnknown* whichInterface) const;
	virtual void DebugRelease(IPMUnknown* whichInterface) const;
	virtual bool16 SetAssertOnCall(bool16 onOrOff);
	virtual bool16 SetVTableOverwrite(bool16 onOrOff);
	virtual void DisableAssertOnCall();
	virtual void EnableAssertOnCall();

	virtual void SetChecksum(IPMUnknown *face, uint32 newChecksum);
	virtual void SetChecksum(int32 faceIndex, uint32 newChecksum);
	virtual uint32 GetChecksum(int32 faceIndex)const;

	virtual void DumpBossInterfaceReferences(LogObject * logObject) const;
#ifdef INTERFACEPROXIES_SUPPORTED 
	virtual void SetOwningBoss (const IControllingUnknown *boss);	
	virtual const IControllingUnknown * GetDelegateBoss () const;
	virtual const IControllingUnknown * GetOwningBoss () const;	
	virtual void RemoveFromProxyList(const int32 ProxyID) {};
	virtual void ReportOverReleasedProxyError(const int32 ProxyID) const {};
	virtual void InsertAddRefStackCrawl(const int32 ProxyID) 	{};
	virtual void InsertReleaseStackCrawl(const int32 ProxyID) {};
	virtual void DumpInterfacesToTrack (LogObject * logObject, std::vector<std::pair<ClassID, PMIID> >&leaksSoFarReported) const;
#endif
#endif
	virtual	void SwitchExecutionContext();

private:
	void CommonConstruct();

private:
	// for pmpersist
	IClassInfo const*GetClassInfo() const;
	

protected:
	IClassInfo const* fClassInfo;
	mutable int32		fRefCount;

#ifdef DEBUG
		// for detecting boss leaks
public:	
	static uint32 GetObjectCount()
		{ return ts_ObjCount; }
	static void DebugShutdown();
		// Call this right before exiting program to check if there
		// are any leaks caused by missing Releases
	
protected:
	bool16						fIsDestructing;
	ClassID 					fDebugClassId;
#ifdef INTERFACEPROXIES_SUPPORTED 
	mutable const IControllingUnknown *fOwningBoss;
#endif
private:
	UID							fDebugUID;	
	K2Vector<void*> 			fOriginalVtbl;
	K2Vector<int32> 			fOriginalClassData;
	bool16 						fVtblIsOverwritten;
	bool16 						fVtblShouldBeOverwritten;
	int32 						fVtblOverwriteDisabledCount;

	static uint32 				ts_ObjCount;

// ----- Track bosses

	BaseControllingUnknown *fNextOutstandingBoss;
	BaseControllingUnknown *fPreviousOutstandingBoss;

	IDThreading::ExecutionContextID fOwningExecutionContextId; // The ID of the execution context that owns us

public:

	typedef K2Vector<BaseControllingUnknown *> OutstandingBossList;
	static void GetOutstandingBosses (OutstandingBossList &list);

	// Checks if the calling thread is in the same domain with the owning thread (see IDThreading::IsSameThreadDomain)
	bool IsOwningExecutionContext() const { return fOwningExecutionContextId == IDThreading::CurrentExecutionContextId(); }

#endif // DEBUG
};

#endif // __BaseControllingUnknown__
