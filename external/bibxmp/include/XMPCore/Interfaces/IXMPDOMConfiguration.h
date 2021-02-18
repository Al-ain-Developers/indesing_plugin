#ifndef IXMPDOMConfiguration_h__
#define IXMPDOMConfiguration_h__ 1

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
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	class XMP_PUBLIC IXMPDOMConfiguration_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		// all unsafe functions
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetParameter( const char * key, bool value ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetParameter( const char * key, void * value ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool GetParameterAsBool( const char * key ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void * GetParameter( const char * key ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual void SetParameter( const char * key, UInt32 value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( const char * key, void * value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 GetParameterAsBool( const char * key, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void * GetParameter( const char * key, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPDOMConfiguration_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPDOMConfiguration_v1::~IXMPDOMConfiguration_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

	//implement all unsafe functions as inline calling safe function internally

		inline void IXMPDOMConfiguration_v1::SetParameter( const char * key, bool value ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPDOMConfiguration_v1, const char *, UInt32 >(
				this, &IXMPDOMConfiguration_v1::SetParameter, key, static_cast< UInt32 >( value ) );
		}

		inline void IXMPDOMConfiguration_v1::SetParameter( const char * key, void * value ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPDOMConfiguration_v1, const char *, void * >(
				this, &IXMPDOMConfiguration_v1::SetParameter, key, value );
		}

		inline bool IXMPDOMConfiguration_v1::GetParameterAsBool( const char * key ) const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPDOMConfiguration_v1, bool, UInt32, const char * >(
				this, &IXMPDOMConfiguration_v1::GetParameterAsBool, key );
		}

		inline void * IXMPDOMConfiguration_v1::GetParameter( const char * key ) const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPDOMConfiguration_v1, void *, void *, const char * >(
				this, &IXMPDOMConfiguration_v1::GetParameter, key );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPDOMConfiguration_h__
