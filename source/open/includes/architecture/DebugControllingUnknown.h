//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/DebugControllingUnknown.h $
//  
//  Owner: zwilliam
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
//  The DebugControllingUnknown is a Mac-only debugging utility designed to help
//  find the source of leaked boss objects.
//  
//  To use the DebugControllingUnknown you need to tell the object model to use
//  the DebugControllingUnknown class when constructing boss object of the ClassID
//  being leaked.
//  To accomplish this, copy the following to a .cpp file in your plugin.
//  
//  include "XXXID.h"
//  include "ClassFactory.h"
//  include "DebugControllingUnknown.h"
//  
//  static ClassFactory kCreateXXXBoss(kXXXBoss, CreateDebugControllingUnknown);
//  
//  Replace the three instances of "XXX" with the corresponding string for the boss
//  type you wish to track (i.e. RectID.h, gCreateRectItemBoss, kRectItem, to track
//  rectangle bosses) and your set.  Just re-build your plug-in and reproduce the leak.
//  
//  On quit continue through all outstanding boss and leak asserts.  The
//  DebugControllingUnknown will dump out stack traces for all calls
//  to your boss object which increment or decrement the ref count and are not obviously
//  paired up (i.e. QueryInterface with Release).
//  
//  The dump is sent to the DebugWindow and to the OutstandingBossesLog.txt (in the QA:Logs: folder).
//  Increments (AddRef, Instantiate, etc.) are listed first, decrements (Releases) are listed second.
//  
//  NOTE:
//  DebugControllingUnknown should help you narrow down the source of a leak and it's
//  very easy to use.  However, the code that attempts to pair AddRef situations with Releases
//  frequently cannot match a Release to the corresponding AddRef.  Because of this,
//  you'll generally end up with a list of unpaired AddRefs and Releases in the OutstandingBossesLog,
//  even when only a single call to Release is missing.
//  
//========================================================================================

#include "InterfaceTrackingUtils.h"

#pragma once
#ifdef INTERFACEPROXIES_SUPPORTED

#include "k2lookup.h"

#ifndef __DebugControllingUnknown__
#define __DebugControllingUnknown__
#include  "IControllingUnknown.h"

inline char * AddrToSymbol(char *pAddress, char *pbuffer, int32 szbuffer);

class LogObject;
class IClassInfo;

class StackTrace
{
	// Designed only for private use by the DebugControllingUnknown class
public:
	enum { kMaxLevel = 16, kMinLevel = 3 };
	
	friend bool16 operator==(const StackTrace& t1, const StackTrace& t2);
	
	void Dump(LogObject * logObject);
	void GetStackTraceInStringForm(char * pString);

	static bool16 ModifiedStrCmp(const char * s1, const char * s2);
public:
	
public:
	char * stackTrace[kMaxLevel-kMinLevel];
};


#ifdef MACINTOSH
#pragma export on
#endif

class PUBLIC_DECL InterfaceTracking_DebugControllingUnknown : public IControllingUnknown
{
public:
	friend class SessionBoss;
	InterfaceTracking_DebugControllingUnknown(IControllingUnknown *pDelegate);

	virtual IPMUnknown * QueryInterface ( PMIID interfaceID) const ;
	virtual void DebugAddRef(IPMUnknown* whichInterface) const;
	virtual void DebugRelease(IPMUnknown* whichInterface) const;	
	virtual ImplementationID GetImplementationID(IPMUnknown *p) const;
	virtual PMIID GetInterfaceID (IPMUnknown *p) const;
	
	virtual void DumpBossInterfaceReferences(LogObject * logObject) const;

	virtual void RemoveFromProxyList(const int32 ProxyID);	
	virtual void ReportOverReleasedProxyError(const int32 ProxyID) const;
	virtual void InsertAddRefStackCrawl(const int32 ProxyID);
	virtual void InsertReleaseStackCrawl(const int32 ProxyID);	
	
	virtual void AddRef() const 
	{
		fDelegate->AddRef();
	}	
	virtual void Release() const 
	{
		fDelegate->Release();
	}	
	virtual ClassID GetClass() const 
	{
		return fDelegate->GetClass();
	}
	virtual uint32 GetRefCount() const
	{
		return fDelegate->GetRefCount();
	}
	virtual IPMUnknown* GetInterfacePtr(ImplementationID implID) const
	{
		return fDelegate->GetInterfacePtr(implID);
	}
	virtual IPMUnknown* GetInterfacePtr(PMIID interfaceID) const
	{
		return fDelegate->GetInterfacePtr(interfaceID);
	}
	virtual const IPMPersist* GetPersist() const
	{
		return fDelegate->GetPersist();
	}
#ifdef DEBUG
	virtual IPMUnknown* GetInterfacePtrByIndex(int32 index) const
	{
		return fDelegate->GetInterfacePtrByIndex(index);
	}
#endif
	virtual void SetChecksum(IPMUnknown *face, uint32 newChecksum)
	{
		fDelegate->SetChecksum(face, newChecksum);
	}
	virtual void SetChecksum(int32 faceIndex, uint32 newChecksum)
	{
		fDelegate->SetChecksum(faceIndex, newChecksum);
	}
	virtual uint32 GetChecksum(int32 faceIndex)const
	{
		return fDelegate->GetChecksum(faceIndex);
	}
	virtual bool16 SetAssertOnCall(bool16 onOrOff) 
	{
		return fDelegate->SetAssertOnCall(onOrOff);
	}
	virtual void DisableAssertOnCall() 
	{
		fDelegate->DisableAssertOnCall();
	}	
	virtual void EnableAssertOnCall() 
	{
		fDelegate->EnableAssertOnCall();
	}
	virtual void SetDebugUID (UID id) 
	{
		fDelegate->SetDebugUID (id);
	}
	virtual void DumpInterfacesToTrack (LogObject * logObject, std::vector<std::pair<ClassID, PMIID> >&leaksSoFarReported) const
	{
		fDelegate->DumpInterfacesToTrack(logObject, leaksSoFarReported);
	}
	virtual void SetOwningBoss (const IControllingUnknown *boss)
	{
	 fDelegate->SetOwningBoss (boss);
	}
	virtual const IControllingUnknown* GetOwningBoss () const {return nil;} 
	virtual const IControllingUnknown * GetDelegateBoss () const {return fDelegate;};

	virtual	void SwitchExecutionContext();

	virtual ~InterfaceTracking_DebugControllingUnknown();

protected:
	// The following template is used to avoid generated code bloat.
	mutable K2Lookup<int32, void *> 			fActiveInterfaceTrackingProxyList;
	// The following template is used to avoid generated code bloat.
	mutable K2Lookup<int32, void *> 			fProxyGarbageList;	
	mutable K2Vector<StackTrace *> 				fProxyStackTraceList;	
	mutable K2Vector<StackTrace *>				fProxyStackTraceGarbageList;

	typedef K2Vector<StackTrace *> StackTraceCollection;
	mutable K2Vector<StackTraceCollection>		fProxyAddRefStackCrawls;
	mutable K2Vector<StackTraceCollection>		fProxyReleaseStackCrawls;
	mutable int32								fCurrentProxyID;	
	mutable bool16 								fDoNotTrack;
	IControllingUnknown *						fDelegate;	
	IClassInfo*									fClassInfo;
	static StackTrace * NewStackTrace();	
};
//
// Boss Constructor functions
//
PUBLIC_DECL IPMUnknown * CreateInterfaceTracking_DebugControllingUnknown(IControllingUnknown *pDelegate);

#ifdef MACINTOSH
#pragma export off
#endif	// MACINTOSH
	
#endif	// __DebugControllingUnknown__

#endif 	// INTERFACEPROXIES_SUPPORTED
