#ifndef __IClientAllocator_h__
#define __IClientAllocator_h__ 1

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
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclarations.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCOMMON {

	//!
	//! \brief Version1 of the interface that represents an interface to be implemented by client in case
	//! he is interested in controlling the memory allocation and deallocation on the heap.
	//! \details In case client is interested in controlling the memory allocation and deallocation on
	//! the heap he can implement this interface and register the same with the
	//! #NS_XMPCOMMON::IConfigurationManager. For every request of memory allocation or deallocation on
	//! the heap corresponding function will be called by the library.
	//! \attention Support for Multi threading is under clients hand.
	//!
	class XMP_PUBLIC IClientAllocator_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Called by the library whenever it needs some space on the heap.
		//! \param size	[in]		a value of type #NS_XMPCOMMON::SizeT indicating the number of bytes
		//! required by the library on the heap.
		//! \return a pointer to memory location on the heap.
		//!
		virtual void * Allocate( SizeT size ) = 0;

		//!
		//! Called by the library whenever there is no further need for a previously allocated space on the heap.
		//! \param ptr	[in]		a pointer to a memory location which is no longer needed.
		//!
		virtual void Deallocate( void * ptr ) = 0;

		//!
		//! Called by the library whenever it needs to expand or contract some space already allocated on
		//! the heap, preserving the contents.
		//! \param ptr	[in]		a pointer to a memory location which was previously allocated on the heap.
		//! \param size	[in]		a value of type #NS_XMPCOMMON::SizeT indicating the new number of bytes
		//! required by the library on the heap.
		//! \return a pointer to memory location on the heap which is of new size and previous contents are
		//! preserved.
		//!
		virtual void * Reallocate( void * ptr, SizeT size ) = 0;

#if !SOURCE_COMPILED
	public:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual void * Allocate( SizeT size, pcIError_base & error ) __NOTHROW__;
		virtual void Deallocate( void * ptr, pcIError_base & error ) __NOTHROW__;
		virtual void * Reallocate( void * ptr, SizeT size, pcIError_base & error ) __NOTHROW__;
		//! \endcond
#endif  // !SOURCE_COMPILED

	protected:
		virtual ~IClientAllocator_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IClientAllocator_v1::~IClientAllocator_v1() __NOTHROW__ { }

};

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
//! \cond XMP_INTERNAL_DOCUMENTATION
#include "XMPCommon/Utilities/TWrapperFunctions.h"

namespace NS_XMPCOMMON {
	inline void * IClientAllocator_v1::Allocate( SizeT size, pcIError_base & error ) __NOTHROW__ {
		return NS_XMPCOMMON::CallUnSafeFunction< IClientAllocator_v1, void *, void *, SizeT >( error, this, NULL, &IClientAllocator_v1::Allocate, size );
	}

	inline void IClientAllocator_v1::Deallocate( void * ptr, pcIError_base & error ) __NOTHROW__ {
		return NS_XMPCOMMON::CallUnSafeFunctionReturningVoid< IClientAllocator_v1, void * >( error, this, &IClientAllocator_v1::Deallocate, ptr );
	}

	inline void * IClientAllocator_v1::Reallocate( void * ptr, SizeT size, pcIError_base & error ) __NOTHROW__ {
		return NS_XMPCOMMON::CallUnSafeFunction< IClientAllocator_v1, void *, void *, void *, SizeT >( error, this, NULL, &IClientAllocator_v1::Reallocate, ptr, size );
	}
}
//! \endcond
#endif  // !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB

#endif  // __IClientAllocator_h__
