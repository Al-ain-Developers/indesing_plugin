#ifndef __ISharedOwnership_h__
#define __ISharedOwnership_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommonDefines.h"

namespace NS_XMPCOMMON {

	//!
	//! \brief Version1 of the interface that serves as the base interface of all the
	//! externally exposed interfaces.
	//! \details This allows all interfaces to be used as shared pointers so as to reduce the burden of
	//! scope management from the client or library code. It makes the heap allocated object to be self memory
	//! and life time managed. This provides functions so as to inform the actual object when a shared pointer
	//! is created or destroyed and appropriately release the memory during the last call to ReleaseSharedOwnership.
	//! \attention Supports Multi-threading at object level through use of Atomic Variables.
	//! \note Any class/interface which inherits from this class needs to provide implementation for
	//! AcquireSharedOwnership and ReleaseSharedOwnership pure virtual function. Also the destructor of derived
	//! class should be declared as protected so that by mistake also client of this object cannot call delete on this.
	//!
	class XMP_PUBLIC ISharedOwnership_v1 {
	public:
		//!
		//! Called by the clients of the object to indicate he has acquired the shared ownership of the object.
		//!
		virtual void AcquireSharedOwnership() const __NOTHROW__ = 0;

		//!
		//! Called by the clients of the object to indicate he has released his shared ownership of the object.
		//! if this being the last client than this function should call Destroy to delete and release the memory.
		//!
		virtual void ReleaseSharedOwnership() const __NOTHROW__ = 0;

	protected:
		//!
		//! calls delete on the actual object.
		//!
		virtual void Destroy() __NOTHROW__ { delete this; };

		//!
		//! protected virtual destructor.
		//!
		virtual ~ISharedOwnership_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline ISharedOwnership_v1::~ISharedOwnership_v1() __NOTHROW__ { }

	typedef ISharedOwnership_v1				ISharedOwnership_latest;

};

#endif  // __ISharedOwnership_h__
