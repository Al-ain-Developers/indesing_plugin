#ifndef __IXMPPathSegment_h__
#define __IXMPPathSegment_h__ 1

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
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 5.5-c024 Added a new API to the XMPCore to return pointer to interface  IXMPDOMFactory
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCore/XMPCoreDefines.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//! 
	//! \brief Version1 of the interface that represents one segment in a path to a node into the XMP tree.
	//! \details Provides all the functions to access properties of the path segment and factory functions
	//! to create various kinds of path segments.
	//! \attention Not thread safe and not required as only read only access is provided to client.
	//!
	class XMP_PUBLIC IXMPPathSegment_v1
		: public virtual ISharedOwnership_v1
	{
	public:

		//!
		//! This enumeration represents the types of a path segment.
		//!
		typedef enum {
			//! Any property that consists of namespace and a localName
			kXMPPathSegementTypeProperty			= 0,
			//! An array index which does not have a namespace or localName itself
			kXMPPathSegmentTypeArrayIndex			= 1,
			//! A qualifier of a property, also consists of namespace and localName
			kXMPPathSegmentTypeQualifier			= 2,
			//! Selects a specific qualifier by its value (e.g. specific language)
			kXMPPathSegmentTypeQualifierSelector	= 3,

			//! Maximum value this enum can hold, should be treated as invalid value
			kXMPPathSegmentTypeMaxValue				= kMaxEnumValue,
		} eXMPPathSegmentType;

		//!
		//! Get the name space of the path segment.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object representing namespace of the path segment.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetNameSpace() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the name of the path segment.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing name of the path segment.
		//! \note raises warning in case of path segment is of type kXMPPathSegmentTypeArrayIndex and returns invalid shared pointer in such cases.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetName() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the type of the path segment.
		//! \return an object of type #eXMPPathSegmentType representing type of the path segment.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eXMPPathSegmentType GetType() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the index of the array type path segment.
		//! \return an objet of type #NS_XMPCOMMON::SizeT object representing index ot the array type path segment.
		//! \note raises warning in case of path segment is not of type kXMPPathSegmentTypeArrayIndex and returns #NS_XMPCOMMON::kMaxSize_t
		//! in such cases.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT GetIndex() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the value of the qualifier type path segment.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object representing value of the qualifier type path segment.
		//! \note raises warning in case path segment is not of type kXMPPathSegmentTypeQualifier and returns invalid shared pointer is such cases.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetValue() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the specific segments

		//!
		//! Creates a normal property path segment.These are essentially all properties (simple, struct and arrays).
		//! \param[in]		nameSpace	pointer to a null terminated constant char buffer containing name space URI of the property.
		//! \param[in]		name		pointer to a null terminated constant char buffer containing local name of the property.
		//! \return a shared pointer to const #NS_XMPCOMMON::IXMPPathSegment.
		//! \attention throws #NS_XMPCOMMON::spcIError if pointers to const char buffers are NULL or their content is empty.
		//!
		XMP_PRIVATE static spcIXMPPathSegment CreatePropertyPathSegment( const char * nameSpace, const char * name );
		
		//!
		//! Creates an array index path segment that denotes a specific element of an array.
		//! Such segments do not have an own name and inherits the namespace from the Array property itself.
		//! \param[in]		nameSpace	pointer to a null terminated constant char buffer containing name space URI of the property.
		//! \param[in]		index		an object of type #NS_XMPCOMMON::SizeT containting the index of the array element.
		//! \return a shared pointer to const #NS_XMPCOMMON::IXMPPathSegment.
		//! \attention throws #NS_XMPCOMMON::spcIError in pointers to const char buffers are NULL or their content is empty.
		//!
		//!
		XMP_PRIVATE static spcIXMPPathSegment CreateArrayIndexPathSegment( const char * nameSpace, SizeT index );

		//!
		//! Creates a Qualifier path segment, which behaves like a normal property
		//! \param[in]		nameSpace	pointer to a null terminated constant char buffer containing name space URI of the property.
		//! \param[in]		name		pointer to a null terminated constant char buffer containing local name of the property.
		//! \return a shared pointer to const #NS_XMPCOMMON::IXMPPathSegment.
		//! \attention throws #NS_XMPCOMMON::spcIError in pointers to const char buffers are NULL or their content is empty.
		//!//!
		XMP_PRIVATE static spcIXMPPathSegment CreateQualifierPathSegment( const char * nameSpace, const char * name );
		
		//!
		//! Creates a path segment that selects a specific qualifier by its value.
		//! For example a specific language in a alternative array of languages.
		//! \param[in]		nameSpace	pointer to a null terminated constant char buffer containing name space URI of the property.
		//! \param[in]		name		pointer to a null terminated constant char buffer containing local name of the property.
		//! \param[in]		value		pointer to a null terminated constant char buffer containing value of the language (xml:lang)
		//! qualifier of the property.
		//! \return a shared pointer to const #NS_XMPCOMMON::IXMPPathSegment.
		//! \attention throws #NS_XMPCOMMON::spcIError in pointers to const char buffers are NULL or their content is empty.
		//!//!
		XMP_PRIVATE static spcIXMPPathSegment CreateQualifierSelectorPathSegment( const char * nameSpace, const char * name, const char * value );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		virtual pcIUTF8String_base GetNameSpace( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetName( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetType( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual SizeT GetIndex( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetValue( pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPPathSegment_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPPathSegment_v1::~IXMPPathSegment_v1() __NOTHROW__ { }

};

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
#include "XMPCommon/Utilities/TWrapperFunctions.h"

namespace NS_XMPCORE {

	inline spcIUTF8String IXMPPathSegment_v1::GetNameSpace() const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			this, &IXMPPathSegment_v1::GetNameSpace );
	}

	inline spcIUTF8String IXMPPathSegment_v1::GetName() const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			this, &IXMPPathSegment_v1::GetName );
	}

	inline IXMPPathSegment_v1::eXMPPathSegmentType IXMPPathSegment_v1::GetType() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IXMPPathSegment_v1, eXMPPathSegmentType, UInt32 >(
			this, &IXMPPathSegment_v1::GetType );
	}

	inline SizeT IXMPPathSegment_v1::GetIndex() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IXMPPathSegment_v1, SizeT, SizeT >(
			this, &IXMPPathSegment_v1::GetIndex );
	}

	inline spcIUTF8String IXMPPathSegment_v1::GetValue() const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			this, &IXMPPathSegment_v1::GetValue );
	}

}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPPathSegment_h__
