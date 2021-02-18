//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IControllingUnknown.h $
//  
//  Owner: robin briggs
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
//  Review Date:
//  
//========================================================================================

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "InterfaceTrackingUtils.h"
#include <vector>
#include "IDThreading.h"
#pragma once
#ifndef __IControllingUnknown__
#define __IControllingUnknown__

class LogObject;

/** This interface is automatically added to every boss class and 
	contains general information
	about a boss object such as its reference count. 
	The implementation of this interface is a C++ object that "controls" the interface
	or "bosses" them, hence the term boss.

	@ingroup arch_om
*/
class IControllingUnknown : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLLINGUNKNOWN };
		
		/** Return the ClassID associated with the object. Generally this
			can be more conveniently called via ::GetClass(theBoss) in
			PersistUtils.h
	  	   @return ClassID of the boss. 
	   */
	virtual ClassID GetClass() const = 0;

		/** Given a pointer to an interface in the boss, return the implementationID
			of that interface. 
		   @param p pointer to an interface of the boss
		   @return ImplementationID of the interface 
		*/
	virtual ImplementationID GetImplementationID(IPMUnknown *p) const = 0;

		/** Given a pointer to an interface in the boss, return the PMIID
			of that interface. 
		   @param p pointer to an interface of the boss
		   @return PMIID of the interface 
		*/
	virtual PMIID GetInterfaceID(IPMUnknown *p) const = 0;
	
		/**	Return the current refcount.
		   @return int32 refCount
		 */
	virtual uint32 GetRefCount() const = 0;

		/**	Return a pointer to an interface, if the interface has already been instantiated.
			Otherwise, return nil. You shouldn't need to call this.
			The reference count is not incremented.
		   @param interfaceID specifies interface to get
		   @return IPMUnknown* to the interface
		 */
	virtual IPMUnknown* GetInterfacePtr(PMIID interfaceID) const = 0;

		/**	Convert implementationID to a pointer to that interface.
			You shouldn't need to call this.
		   @param implID specifies which interface
		   @return IPMUnknown* pointer to the interface 
		 */
	virtual IPMUnknown* GetInterfacePtr(ImplementationID implID) const = 0;

		/**	Convert implementationID to a pointer to that interface.
			You shouldn't need to call this.
		   @param implID specifies which interface
		   @return IPMUnknown* pointer to the interface 
		 */
	virtual const IPMPersist* GetPersist() const = 0;

#ifdef DEBUG
	
		/**	Return a pointer to an interface, if the interface has already been instantiated.
			Otherwise, return nil. You shouldn't need to call this.
			The reference count is not incremented.
		   @param index specifies interface to get by index.
		   @return IPMUnknown* to the interface
		 */
	virtual IPMUnknown* GetInterfacePtrByIndex(int32 index) const = 0;
		// If onOrOff is true, overwrites the vtbl pointer of every interface 
		// with AssertVtbl (asserts & exittoshell). It onOrOff is false, the
		// AssertVtbl is cleared, and the original vtbl is restored. This is 
		// used for debugging objects in the instance cache, which are candidates
		// for destruction (and shouldn't be used). Returns the old value of the
		// setting. This is only to be called by the instance cache of the database.
	virtual bool16 SetAssertOnCall(bool16 onOrOff) = 0;
		// temporarily override the assert
		// must be used balanced with EnableAssertOnCall()
	virtual void DisableAssertOnCall() = 0;
	virtual void EnableAssertOnCall() = 0;

	virtual void SetDebugUID (UID id) = 0;

	virtual void SetChecksum(IPMUnknown *face, uint32 newChecksum) = 0;
	virtual void SetChecksum(int32 faceIndex, uint32 newChecksum) = 0;
	virtual uint32 GetChecksum(int32 faceIndex)const = 0;
	
		// Debug methods to help track boss leaks. 
	virtual void DebugAddRef(IPMUnknown* whichInterface) const = 0;
	virtual void DebugRelease(IPMUnknown* whichInterface) const = 0;
#ifdef INTERFACEPROXIES_SUPPORTED
	virtual void SetOwningBoss (const IControllingUnknown *boss) = 0;	
	virtual const IControllingUnknown * GetOwningBoss () const = 0;	
	virtual const IControllingUnknown * GetDelegateBoss () const = 0;
	virtual void RemoveFromProxyList(const int32 ProxyID) = 0;
	virtual void ReportOverReleasedProxyError(const int32 ProxyID) const = 0;
	virtual void InsertAddRefStackCrawl(const int32 ProxyID) 	= 0;
	virtual void InsertReleaseStackCrawl(const int32 ProxyID) 	= 0;
	virtual void DumpInterfacesToTrack (LogObject * logObject, std::vector<std::pair<ClassID, PMIID> >&leaksSoFarReported) const = 0;
#endif	
	virtual void DumpBossInterfaceReferences(LogObject * logObject) const = 0;
	
#endif
	virtual	void SwitchExecutionContext() = 0;
};


#endif // __IControllingUnknown__
