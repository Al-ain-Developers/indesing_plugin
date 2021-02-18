#ifndef IXMPDOMSerializer_h__
#define IXMPDOMSerializer_h__ 1

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
// 11-05-14 ADC 5.6-c026 [3847480] New DOM : IXMPDOMParser and IXMPDOMSerializer interfaces should include all the dependencies.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	class XMP_PUBLIC IXMPDOMSerializer_v1
		: public virtual ISharedOwnership_v1
	{
		
	public:
		// all unsafe functions
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMConfiguration GetDOMConfiguration() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String Serialize(const spIXMPNode & node, UInt32 options = 0, UInt32  padding = 0, const char*  newline = "", const char*  indent = "", XMP_Index baseIndent = 0) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMSerializer Clone(
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingUseClonedObjectValue ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pIXMPDOMConfiguration_base GetDOMConfiguration( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIUTF8String_base Serialize(pIXMPNode_base node, UInt32 options, UInt32  padding, const char*  newline, const char*  indent, XMP_Index baseIndent, pcIError_base & error) const __NOTHROW__ = 0;
		virtual pIXMPDOMSerializer_base Clone( UInt32 muliThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPDOMSerializer_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPDOMSerializer_v1::~IXMPDOMSerializer_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCore/Interfaces/IXMPDOMConfiguration.h"
	#include "XMPCommon/Interfaces/IUTF8String.h"
	#include "XMPCore/Interfaces/IXMPNode.h"

	namespace NS_XMPCORE {

	//implement all unsafe functions as inline calling safe function internally
		inline spIXMPDOMConfiguration IXMPDOMSerializer_v1::GetDOMConfiguration() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPDOMSerializer_v1, pIXMPDOMConfiguration_base, IXMPDOMConfiguration >(
				this, &IXMPDOMSerializer_v1::GetDOMConfiguration );
		}

		inline spIUTF8String IXMPDOMSerializer_v1::Serialize( const spIXMPNode & node, UInt32 options, UInt32  padding, const char*  newline, const char*  indent, XMP_Index baseIndent ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMSerializer_v1,
				pIUTF8String_base, IUTF8String, pIXMPNode_base, UInt32, UInt32, const char *, const char *, XMP_Index >(
				this, &IXMPDOMSerializer_v1::Serialize, node.get(), options, padding, newline, indent, baseIndent  );
		}

		inline spIXMPDOMSerializer IXMPDOMSerializer_v1::Clone( eMultiThreadingSupport multiThreadingSupport /*= kMultiThreadingUseClonedObjectValue */ ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMSerializer_v1, pIXMPDOMSerializer_base, IXMPDOMSerializer,
				UInt32 >( this, &IXMPDOMSerializer_v1::Clone, static_cast< UInt32 >( multiThreadingSupport ) );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPDOMSerializer_h__

