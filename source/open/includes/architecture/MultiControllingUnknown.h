//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/MultiControllingUnknown.h $
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
#ifndef __MultiControllingUnknown__
#define __MultiControllingUnknown__


#include "BaseControllingUnknown.h"
#include "K2Vector.h"

#ifdef DEBUG
	#if _M_AMD64
		// 64 bit pointer
		#define DEADDEAD_FLAG_INTERFACE_PTR (reinterpret_cast<IPMUnknown*>((uintptr_t)(0xDEADDEADDEADDEAD)))
		#define DEADBEEF_FLAG_INTERFACE_PTR (reinterpret_cast<IPMUnknown*>((uintptr_t)(0xDEADBEEFDEADBEEF)))
	#else
		// 32 bit pointer
		#define DEADDEAD_FLAG_INTERFACE_PTR (reinterpret_cast<IPMUnknown*>((uintptr_t)(0xDEADDEAD)))
		#define DEADBEEF_FLAG_INTERFACE_PTR (reinterpret_cast<IPMUnknown*>((uintptr_t)(0xDEADBEEF)))
	#endif
#endif


/**	MultiControllingUnknown is for non-persistent bosses.
	It is table-driven; it keeps the multiple interfaces of the boss in a table,
	which allows different interfaces to be allocated in different blocks of memory.
*/
class PUBLIC_DECL MultiControllingUnknown : public BaseControllingUnknown
{
public:
	MultiControllingUnknown(const ClassID theClass);
	MultiControllingUnknown(IClassInfo const* theClass);
	virtual ~MultiControllingUnknown();

	virtual IPMUnknown *QueryInterface(PMIID interfaceID) const;
	virtual void LastRelease() const;
			
	virtual ImplementationID GetImplementationID(IPMUnknown *p) const;
	virtual IPMUnknown* GetInterfacePtr(PMIID interfaceID) const;
	using BaseControllingUnknown::GetInterfacePtr;
	virtual const IPMPersist* GetPersist() const
		{ return nil; }
#ifdef DEBUG	
	virtual IPMUnknown* GetInterfacePtrByIndex(int32 index) const;
#endif
protected:
	// Array of interface instances
	typedef K2Vector<IPMUnknown*> InterfaceInstanceArray;
	mutable InterfaceInstanceArray	fInterfaces;
};


#endif // __MultiControllingUnknown__
