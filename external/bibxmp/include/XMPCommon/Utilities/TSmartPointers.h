#ifndef __TSmartPointers_h__
#define __TSmartPointers_h__ 1

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
// mm-dd-yy who Description of changes, most recent on top
//
// 03-31-15 ADC 5.6-c071 Fixing issues with Mac build.
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 08-03-14 ADC 1.0-m029 Fixing crashers on Macintosh.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-25-14 ADC 1.0-m011 Changes required for compiling on Visual Studio 2010.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-19-14 ADC 1.0-m007 Public Header files were referring to couple of private header files.
// 02-19-14 ADC 5.5-c007 Public Header files were referring to couple of private header files.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
//
// =================================================================================================
#endif // AdobePrivate


#include "XMPCommon/XMPCommonDefines.h"

#if SUPPORT_SHARED_POINTERS_IN_STD
	#include <memory>
	#include <functional>
#elif SUPPORT_SHARED_POINTERS_IN_TR1
	#if XMP_WinBuild
		#include <memory>
		#include <functional>
	#else
		#include <tr1/memory>
		#include <tr1/functional>
	#endif
#else
	#error "location of shared pointer stuff is unknown"
#endif

#include <cstring>

namespace NS_XMPCOMMON {

#if SUPPORT_SHARED_POINTERS_IN_STD
	using std::shared_ptr;
	using std::mem_fn;
	using std::weak_ptr;
	using std::enable_shared_from_this;
	using std::dynamic_pointer_cast;
	using std::static_pointer_cast;
	using std::const_pointer_cast;
	using std::bad_weak_ptr;
#elif SUPPORT_SHARED_POINTERS_IN_TR1
	using std::tr1::shared_ptr;
	using std::tr1::mem_fn;
	using std::tr1::weak_ptr;
	using std::tr1::enable_shared_from_this;
	using std::tr1::dynamic_pointer_cast;
	using std::tr1::static_pointer_cast;
	using std::tr1::const_pointer_cast;
	using std::tr1::bad_weak_ptr;
#endif

	//!
	//! Function to create NULL Pointer Error on the client side and throw it if possible or otherwise
	//! throws a std::bad_exception.
	//! \param processFatal		[in]	a value of bool type indicating whether the severity of error is process level
	//! or operation level; true for process level severity, false otherwise.
	//! \param message			[in]		pointer to a constant null terminated char buffer containing message. NULL pointer
	//! will be treated as empty message string.
	//! \param fileName			[in]		pointer to a constant null terminated char buffer containing fileName in which error
	//! originated.
	//! \param lineNumber		[in]		a value of #NS_XMPCOMMON::UInt32 type respresenting the lineNumber at which error
	//! originated.
	//! \param paramsCount		[in]		an object of type #NS_XMPCOMMON::SizeT indicating the number of parameters to be
	//! associated with the error object.
	//! \param params			[in]		pointer to the first location of an array of constant null terminated char buffers,
	//! where in each location stores a parameter string.
	//!
	void ThrowNULLPointerError( bool processFatal, const char * message, const char * fileName,
		UInt32 lineNumber, SizeT paramsCount, const char ** params );

	//!
	//! Function to create Version Unavailability Error on the client side and throw it if possible or otherwise
	//! throws a std::bad_exception.
	//! \param processFatal		[in]		a value of bool type indicating whether the severity of error is  process level
	//! or operation level; true for process level severity, false otherwise.
	//! \param message			[in]		pointer to a constant null terminated char buffer containing message. NULL pointer
	//! will be treated as empty message string.
	//! \param fileName			[in]		pointer to a constant null terminated char buffer containing fileName in which error
	//! originated.
	//! \param lineNumber		[in]		a value of #NS_XMPCOMMON::UInt32 type respresenting the lineNumber at which error
	//! originated.
	//! \param paramsCount		[in]		an object of type #NS_XMPCOMMON::SizeT indicating the number of parameters to be
	//! associated with the error object.
	//! \param params			[in]		pointer to the first location of an array of constant null terminated char buffers,
	//! where in each location stores a parameter string.
	//!
	void ThrowVersionNotAvailableError( bool processFatal, const char * message, const char * fileName,
		UInt32 lineNumber, SizeT paramsCount, const char ** params );

	//!
	//! Template function to create a shared pointer of the same type from the raw pointer of an object implementing
	//! #NS_XMPCOMMON::ISharedOwnership_v1 interface.
	//! \param ptr	[in]	ptr of template type Ty.
	//! \return a shared pointer of object type Ty.
	//!
	template< typename Ty >
	shared_ptr< Ty > MakeUncheckedSharedPointer( Ty * ptr ) {
		ptr->AcquireSharedOwnership();
		return shared_ptr< Ty >( ptr, mem_fn(&Ty::ReleaseSharedOwnership) );
	}

	//!
	//! Template function to create a shared pointer of a derived or base class from the raw pointer of some class
	//! inherting from #NS_XMPCOMMON::ISharedOwnership_v1.
	//! \param ptr	[in]	ptr of template type InPtrType.
	//! \return a shared pointer of object type OutPtrType.
	//! \attention throws either a shared pointer of const #NS_XMPCOMMON::IError type or std::bad_exception if
	//! dynamic conversion from InPtrType to OutPtrType fails.
	//!
	template< typename OutPtrType, typename InPtrType >
	shared_ptr< OutPtrType > MakeSharedPointer( InPtrType * ptr ) {
		if ( ptr == NULL )
			return shared_ptr< OutPtrType >();
#if SUPPORT_DYNAMIC_CAST_OPTIMIZATION
		static bool dynamicCastSuccess = false;
		static ptrdiff_t diffInPointerAddresses = 0;
#endif
		OutPtrType * outPtr = NULL;

#if SUPPORT_DYNAMIC_CAST_OPTIMIZATION
		if ( dynamicCastSuccess ) {
			outPtr = static_cast< OutPtrType * >( static_cast< void * > ( ( ( char * ) ptr ) + diffInPointerAddresses ) );
		} else {
			outPtr = dynamic_cast< OutPtrType * >( ptr );
			if ( outPtr ) {
				dynamicCastSuccess = true;
				diffInPointerAddresses = ( char * ) outPtr - ( char * ) ptr;
			}
		}
#else
		outPtr = dynamic_cast< OutPtrType * >( ptr );
#endif

		if ( outPtr ) {
			ptr->AcquireSharedOwnership();
			return shared_ptr< OutPtrType >( outPtr, mem_fn(&OutPtrType::ReleaseSharedOwnership) );
		} else {
			const char * typeNameForInPtr = typeid( ptr ).name();

			if ( strstr( typeNameForInPtr, "IError" ) == NULL ) {
				const char * typeNameForOutPtr = typeid( outPtr ).name();
				const char * parameters[2] = { typeNameForInPtr, typeNameForOutPtr };
				ThrowVersionNotAvailableError( true, "Version client is seeking is not available in the library",
					__FILE__, __LINE__, 2, parameters );
			} else {
			#if BAD_EXCEPTION_SUPPORT_STRINGS
				throw std::bad_exception( "Version of IError client is seeking is not available in the library" );
			#else
				throw std::bad_exception();
			#endif
			}

			return shared_ptr< OutPtrType >();
		}
	}

	//!
	//! Template function to create a shared pointer of the same type from the raw pointer of a class not
	//! inheriting from #NS_XMPCOMMON::ISharedOwnership_v1.
	//! \param ptr	[in]	ptr of template type Ty.
	//! \return a shared pointer of object type Ty.
	//!
	template< typename Ty >
	shared_ptr< Ty > MakeUncheckedSharedPointerWithDefaultDelete( Ty * ptr ) {
		return shared_ptr< Ty >( ptr );
	}

}

#endif  // __TSmartPointers_h__
