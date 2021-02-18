#ifndef IXMPNameSpacePrefixMap_h__
#define IXMPNameSpacePrefixMap_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
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
// mm-dd-yy who Description of changes, most recent first.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that represents map where each entry consists of prefix string
	//! as the key and corresponding nameSpace string as its value.
	//! \details Provides all the functions to get/set the entries inside the map.
	//! \attention Supports Multi-threading at object level through locks.
	//!
	class XMP_PUBLIC IXMPNameSpacePrefixMap_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Adds a new pair of prefix string and its corresponding nameSpace string or replace an existing entry.
		//! \param[in]		prefix		pointer to a constant null terminated char buffer containing prefix string.
		//! \param[in]		nameSpace	pointer to a constant null terminated char buffer containing nameSpace string.
		//! \return a bool type object containing true in case operation was successful, false otherwise.
		//! \note raises warning in case of prefix or nameSpace are null pointers or their contents are empty.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool AddOrReplacePair( const char * prefix, const char * nameSpace ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Finds the prefix string in the map and removes an entry corresponding to it in the map.
		//! \param[in]		prefix		pointer to a constant null terminated char buffer containing prefix string.
		//! \return a bool type object containing true in case entry was found and then deleted from the map, false otherwise.
		//! \note raises warning in case of prefix is null pointer or its contents are empty.
		//! \attention throws #NS_XMPCOMMON::spcIError in case of failure in removing or searching process.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RemovePrefix( const char * prefix ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Finds the nameSpace string in the map and removes an entry corresponding to it in the map.
		//! \param[in]		nameSpace	pointer to a constant null terminated char buffer containing nameSpace string.
		//! \return a bool type object containing true in case entry was found and then deleted from the map, false otherwise.
		//! \note raises warning in case nameSpace is null pointer or its contents are empty.
		//! \attention throws #NS_XMPCOMMON::spcIError in case of failure in removing or searching process.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RemoveNameSpace( const char * nameSpace ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Checks for the existence of a particular prefix in the map.
		//! \param[in]		prefix		pointer to a constant null terminated char buffer containing prefix string.
		//! \return a bool type object containing true in case there is an entry present corresponding to the prefix string, otherwise false.
		//! \note raises warning in case prefix is null pointer or its contents are empty.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsPrefixPresent( const char * prefix ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Checks for the existence of a particular nameSpace in the map.
		//! \param[in]		nameSpace	pointer to a constant null terminated char buffer containing nameSpace string.
		//! \return a bool type object containing true in case there is an entry present corresponding to the nameSpace string, otherwise false.
		//! \note raises warning in case nameSpace is null pointer or its contents are empty.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsNameSpacePresent( const char * nameSpace ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the nameSpace string corresponding to the prefix string.
		//! \param[in]		prefix		pointer to a constant null terminated char buffer containing prefix string.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing nameSpace string corresponding to prefix string.
		//! \note In case queried prefix is not present then invalid shared pointer is returned.
		//! \note raises warning in case prefix is null pointer or its contents are empty.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetNameSpace( const char * prefix ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the prefix string corresponding to the nameSpace string.
		//! \param[in]		nameSpace	pointer to a constant null terminated char buffer containing nameSpace string.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing prefix string corresponding to nameSpace string.
		//! \note In case queried nameSpace is not present then invalid shared pointer is returned.
		//! \note raises warning in case nameSpace is null pointer or its contents are empty.
		//!

		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetPrefix( const char * nameSpace ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! To get the total number of entries in the map.
		//! \return an object of type #NS_XMPCOMMON::SizeT containing the count of entries in the map.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT GetPairsCount() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Virtual Copy Constructor.
		//! \details makes an another object which is exact replica of the existing object.
		//! \param[in]		multithreadingSupport	a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not.
		// \return a shared pointer to IXMPNameSpacePrefixMap which is exact replica of the current object.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNameSpacePrefixMap Clone( eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create NameSpacePrefix maps

		//!
		//! Provides the default mapping of prefix string and nameSpace strings used by XMPCore.
		//! \return a shared pointer to const IXMPNameSpacePrefixMap object containing all the mappings used
		//! as default by the XMPCore.
		//!
		XMP_PRIVATE static spcIXMPNameSpacePrefixMap GetDefaultNameSpacePrefixMap();

		//!
		//! Creates an empty name space - prefix map and returns it to the client as a shared pointer.
		//! \param[in]		multithreadingSupport	a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not.
		//! \return a shared pointer to ane empty #NS_XMPCORE::IXMPNameSpacePrefixMap object.
		//!
		XMP_PRIVATE static spIXMPNameSpacePrefixMap CreateEmptyNameSpacePrefixMap( eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	protected:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual UInt32 AddOrReplacePair( const char * prefix, const char * nameSpace, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 RemoveNameSpace( const char * nameSpace, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 RemovePrefix( const char * prefix, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 IsPrefixPresent( const char * prefix, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 IsNameSpacePresent( const char * nameSpace, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetNameSpace( const char * prefix, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetPrefix( const char * nameSpace, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual SizeT GetPairsCount( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNameSpacePrefixMap_base Clone( UInt32 multiThreadingSuport, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected virtual Destructor
		//!
		virtual ~IXMPNameSpacePrefixMap_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPNameSpacePrefixMap_v1::~IXMPNameSpacePrefixMap_v1() __NOTHROW__ { }

};

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
#include "XMPCommon/Utilities/TWrapperFunctions.h"

namespace NS_XMPCORE {
	inline bool IXMPNameSpacePrefixMap_v1::AddOrReplacePair( const char * prefix, const char * nameSpace ) {
		return NS_XMPCOMMON::CallSafeFunction< IXMPNameSpacePrefixMap_v1, bool, UInt32, const char *, const char * >(
			this, &IXMPNameSpacePrefixMap_v1::AddOrReplacePair, prefix, nameSpace );
	}

	inline bool IXMPNameSpacePrefixMap_v1::RemoveNameSpace( const char * nameSpace ) {
		return NS_XMPCOMMON::CallSafeFunction< IXMPNameSpacePrefixMap_v1, bool, UInt32, const char * >(
			this, &IXMPNameSpacePrefixMap_v1::RemoveNameSpace, nameSpace );
	}

	inline bool IXMPNameSpacePrefixMap_v1::RemovePrefix( const char * prefix ) {
		return NS_XMPCOMMON::CallSafeFunction< IXMPNameSpacePrefixMap_v1, bool, UInt32, const char * >(
			this, &IXMPNameSpacePrefixMap_v1::RemovePrefix, prefix );
	}

	inline bool IXMPNameSpacePrefixMap_v1::IsPrefixPresent( const char * prefix ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IXMPNameSpacePrefixMap_v1, bool, UInt32, const char * >(
			this, &IXMPNameSpacePrefixMap_v1::IsPrefixPresent, prefix );
	}

	inline bool IXMPNameSpacePrefixMap_v1::IsNameSpacePresent( const char * nameSpace ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IXMPNameSpacePrefixMap_v1, bool, UInt32, const char * >(
			this, &IXMPNameSpacePrefixMap_v1::IsNameSpacePresent, nameSpace );
	}

	inline spcIUTF8String IXMPNameSpacePrefixMap_v1::GetNameSpace( const char * prefix ) const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNameSpacePrefixMap_v1, pcIUTF8String_base,
			const IUTF8String, const char * >( this, &IXMPNameSpacePrefixMap_v1::GetNameSpace, prefix );
	}

	inline spcIUTF8String IXMPNameSpacePrefixMap_v1::GetPrefix( const char * nameSpace ) const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNameSpacePrefixMap_v1, pcIUTF8String_base,
			const IUTF8String, const char * >( this, &IXMPNameSpacePrefixMap_v1::GetPrefix, nameSpace );
	}

	inline SizeT IXMPNameSpacePrefixMap_v1::GetPairsCount() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IXMPNameSpacePrefixMap_v1, SizeT, SizeT >(
			this, &IXMPNameSpacePrefixMap_v1::GetPairsCount );
	}

	inline spIXMPNameSpacePrefixMap IXMPNameSpacePrefixMap_v1::Clone( eMultiThreadingSupport multiThreadingSupport ) const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNameSpacePrefixMap_v1, pIXMPNameSpacePrefixMap_base,
			IXMPNameSpacePrefixMap, UInt32 >( this, &IXMPNameSpacePrefixMap_v1::Clone, static_cast< UInt32>( multiThreadingSupport ) );
	}

}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPNameSpacePrefixMap_h__
