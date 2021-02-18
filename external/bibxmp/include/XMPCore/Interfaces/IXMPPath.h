#ifndef __IXMPPath_h__
#define __IXMPPath_h__ 1

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
//  ADC Amandeep Chawla
//	HK	Honey Kansal
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 HK  5.5-c034 Implementing Serialize(), Clone() and all setter/modifier methods of XMP DOM.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that provides an easy iterative description of a specific path into the XMP tree.
	//! \details Path consists of multiple path segments in an order and each #NS_XMPCORE::IXMPPathSegment represents one segment
	//! of the path into the XMP tree. Provides all the functions to create path and get the various properties of a path.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPPath_v1
		: public virtual ISharedOwnership_v1
	{
	public:

		//!
		//! Serializes the IXMPPath object to a utf8 string representation. This will produce either a long form of the path using
		//! the full namespace strings or short form of the path using the prefix for the namespace.
		//! \param[in]		map		a shared pointer to a const #NS_XMPCORE::IXMPNameSpacePrefixMap object which will contain the
		//! mapping for nameSpaces to prefixes.
		//! \return a shared pointer to #NS_XMPCOMMON::IUTF8String object containing serialized form of path.
		//! \note In case map is not a valid shared pointer than it will serialize to long form of the path.
		//! \attention In case a mapping does not exist for a namespace an error will be thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String Serialize( const spcIXMPNameSpacePrefixMap & map = spcIXMPNameSpacePrefixMap() ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Appends a path segment to the path.
		//! \param[in]		segment	a shared pointer to a const #NS_XMPCORE::IXMPPathSegment object.
		//! \attention In case the segment is not a valid shared pointer an error will be thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void AppendPathSegment( const spcIXMPPathSegment & segment ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Removes a path segment from the path.
		//! \param[in]		index	an object of type #NS_XMPCOMMON::SizeT indicating the index for the path segment to be removed
		//! from the path.
		//! \attention In case the index is out of bounds an error will be thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void RemovePathSegment( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the path segment at a particular index in the path
		//! \param[in]		index	an object of type #NS_XMPCOMMON::SizeT indicating the index for the path segment in the path.
		//! \return a shared pointer to a const #NS_XMPCORE::IXMPPathSegment object.
		//! \attention In case value of index is out of bounds than an error will be thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPPathSegment GetPathSegment( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the number of the path segments in the path.
		//! \return an object of type #NS_XMPCOMMON::SizeT representing the number of path segments in the path.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT GetPathSegmentCount() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! To check whether path is empty or not.
		//! \returns a bool object indicating true in case the path is empty (no path segment)
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsEmpty() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get a new path having a selected range of path segments
		//! \param[in]		startingIndex			an object of type #NS_XMPCOMMON::SizeT indicating the starting index of the path segment to
		//! be part of the returned path object. Default value is 1.
		//! \param[in]		countOfSegments			an object of type #NS_XMPCOMMON::SizeT indicating the count of the path segments to be part
		//! of the returned path object starting from startingIndex. Default value is #NS_XMPCOMMON::kMaxSize_t.
		//! \param[in]		multithreadingSupport	a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \note In case countOfSegments is more than the number of segments available in the path object starting from the starting index
		//! then internally it is truncated to the number of path segments available.
		//! \attention In case startingIndex contains any invalid value then an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPath CloneSubPath( SizeT startingIndex = 1, SizeT countOfSegments = kMaxSize_t,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the specific segments

		//!
		//! Creates an empty path.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPPath object.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//!
		XMP_PRIVATE static spIXMPPath CreateEmptyPath( eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

		//!
		//! Creates a path from a string containing serialized form of the path.
		//! \param[in] serializedPath pointer to a const NULL terminated char buffer containing serialized form of the path.
		//! The serialized form should only be in short form.
		//! \param[in] map a shared pointer to a const #NS_XMPCORE::IXMPNameSpacePrefixMap object which will contain the
		//! mapping for nameSpaces to prefixes.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPPath object.
		//! \note In case the serializedPath is NULL or the contents are empty then it will result in an empty path.
		//! \attention In case serializedPath contains some data then passing invalid map will result in an error.
		//!
		XMP_PRIVATE static spIXMPPath CreatePathByParsing( const char * serailizedPath = NULL, const spcIXMPNameSpacePrefixMap & map = spcIXMPNameSpacePrefixMap(),
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		virtual pIUTF8String_base Serialize( pcIXMPNameSpacePrefixMap map, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void AppendPathSegment( pcIXMPPathSegment_base segment, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void RemovePathSegment( SizeT index, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pcIXMPPathSegment GetPathSegment( SizeT index, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual SizeT GetPathSegmentCount( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 IsEmpty( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPPath_base CloneSubPath( SizeT startingIndex, SizeT countOfSegments, UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPPath_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPPath_v1::~IXMPPath_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCore/Interfaces/IXMPPathSegment.h"

	namespace NS_XMPCORE {

		inline spIUTF8String IXMPPath_v1::Serialize( const spcIXMPNameSpacePrefixMap & map /*= spcIXMPNameSpacePrefixMap() */ ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPath_v1, pIUTF8String_base, IUTF8String, pcIXMPNameSpacePrefixMap_base >(
				this, &IXMPPath_v1::Serialize, map.get() );
		}

		inline void IXMPPath_v1::AppendPathSegment( const spcIXMPPathSegment & segment ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPPath_v1, pcIXMPPathSegment_base >(
				this, &IXMPPath_v1::AppendPathSegment, segment.get() );
		}

		inline void IXMPPath_v1::RemovePathSegment( SizeT index ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPPath_v1, SizeT >(
				this, &IXMPPath_v1::RemovePathSegment, index );
		}

		inline spcIXMPPathSegment IXMPPath_v1::GetPathSegment( SizeT index ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPath_v1, pcIXMPPathSegment_base, const IXMPPathSegment, SizeT >(
				this, &IXMPPath_v1::GetPathSegment, index );
		}

		inline SizeT IXMPPath_v1::GetPathSegmentCount() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPPath_v1, SizeT, SizeT >(
				this, &IXMPPath_v1::GetPathSegmentCount );
		}

		inline bool IXMPPath_v1::IsEmpty() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPPath_v1, bool, UInt32 >(
				this, &IXMPPath_v1::IsEmpty );
		}

		inline spIXMPPath IXMPPath_v1::CloneSubPath( SizeT startingIndex, SizeT countOfSegments, eMultiThreadingSupport multiThradingSupport ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPath_v1, pIXMPPath_base, IXMPPath, SizeT, SizeT, UInt32 >(
				this, &IXMPPath_v1::CloneSubPath, startingIndex, countOfSegments, static_cast< UInt32 >( multiThradingSupport ) );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPPath_h__
