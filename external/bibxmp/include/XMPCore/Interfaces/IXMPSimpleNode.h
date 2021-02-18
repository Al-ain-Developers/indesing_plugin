#ifndef __IXMPSimpleNode_h__
#define __IXMPSimpleNode_h__ 1

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
//  HK	Honey Kansal
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-12-14 HK  5.5-c029 Fixing PK failure for XMPCore DOM unit tests.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/Interfaces/IXMPNode.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that represents a Simple Property Node of XMP DOM.
	//! \details Provides all the functions to get and set various properties of the simple node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPSimpleNode_v1
		: public virtual IXMPNode_v1
	{
	public:
		//!
		//! Get the value of the simple property node.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing value string
		//! of the simple property node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetValue() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Change the value string of the simple property node.
		//! \param[in] value pointer to a constant null terminated char buffer containing value string.
		//! \note In case the value is null pointer or its contents are empty than the value is set to empty string.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ChangeValue( const char * value ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		
		//!
		//! Indicates whether the simple property node is of URI type.
		//! \return a bool value; true in case the simple node is of URI type, false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsURIType() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Controls whether the type of simple property node should be of IsURI type or not.
		//! \param[in]		isURI	a bool value controlling the IsURI type of the simple property node 
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ChangeURIType( bool isURI ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the simple node

		//!
		//! Creates a simple property node which is not part of any metadata document.
		//! \param[in]		nameSpace	pointer to a const NULL terminated char buffer containing namespace of the simple property.
		//! \param[in]		name		pointer to a const NULL terminated char buffer containing name of the simple property.
		//! \param[in]		value		pointer to a const NULL terminated char buffer containing value of the simple property.
		//! \param[in]		multithreadingSupport	a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPSimpleNode object.
		//! \attention In case the nameSpace or name are NULL pointers or their contents are empty than an error is thrown.
		//! \note In case the value is a null pointer or its contents are empty than the value is set to empty string.
		//!
		XMP_PRIVATE static spIXMPSimpleNode CreateSimpleNode( const char * nameSpace, const char * name, const char * value = NULL,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIUTF8String_base GetValue( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void ChangeValue( const char * value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 IsURIType( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void ChangeURIType( UInt32 isURI, pcIError_base & error ) __NOTHROW__ = 0;
	//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPSimpleNode_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPSimpleNode_v1::~IXMPSimpleNode_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline spcIUTF8String IXMPSimpleNode_v1::GetValue() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPSimpleNode_v1, pcIUTF8String_base, const IUTF8String >(
				this, &IXMPSimpleNode_v1::GetValue );
		}

		inline void IXMPSimpleNode_v1::ChangeValue( const char * value ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPSimpleNode_v1, const char * >(
				this, &IXMPSimpleNode_v1::ChangeValue, value );
		}

		inline bool IXMPSimpleNode_v1::IsURIType() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPSimpleNode_v1, bool, UInt32 >(
				this, &IXMPSimpleNode_v1::IsURIType );
		}

		inline void IXMPSimpleNode_v1::ChangeURIType( bool isURI ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPSimpleNode_v1, UInt32 >(
				this, &IXMPSimpleNode_v1::ChangeURIType, static_cast< UInt32 >( isURI ) );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPSimpleNode_h__
