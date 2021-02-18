#ifndef IXMPDOMParser_h__
#define IXMPDOMParser_h__ 1

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

#include <string>

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	class XMP_PUBLIC IXMPDOMParser_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		typedef enum {
			kActionTypeAppendAsChildren			= 0,
			kActionTypeReplaceChildren			= 1,
			kActionTypeInsertBefore				= 2,
			kActionTypeInsertAfter				= 3,
			kActionTypeReplace					= 4,
		} eActionType;

		// all unsafe functions
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMConfiguration GetDOMConfiguration() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPMetadata Parse( const char * buffer,
			SizeT size = std::string::npos , UInt32 options = 0) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ParseWithContext( const spIXMPNode & node,
			eActionType actionType, const char * buffer, SizeT size  = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMParser Clone(
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingUseClonedObjectValue ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pIXMPDOMConfiguration_base GetDOMConfiguration( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPMetadata_base Parse(const char * buffer, SizeT size, UInt32 options, pcIError_base & error) const __NOTHROW__ = 0;
		virtual void ParseWithContext( pIXMPNode_base ptr, UInt32 actionType, const char * buffer, SizeT size, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPDOMParser_base Clone( UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPDOMParser_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPDOMParser_v1::~IXMPDOMParser_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCore/Interfaces/IXMPDOMConfiguration.h"
	#include "XMPCore/Interfaces/IXMPMetadata.h"

	namespace NS_XMPCORE {

		//implement all unsafe functions as inline calling safe function internally

		inline spIXMPDOMConfiguration IXMPDOMParser_v1::GetDOMConfiguration() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPDOMParser_v1, pIXMPDOMConfiguration_base, IXMPDOMConfiguration >(
				this, &IXMPDOMParser_v1::GetDOMConfiguration );
		}

		inline spIXMPMetadata IXMPDOMParser_v1::Parse( const char * buffer, SizeT size /*= std::string::npos */ , UInt32 options) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMParser_v1, pIXMPMetadata_base,
				IXMPMetadata, const char *, SizeT >( this, &IXMPDOMParser_v1::Parse, buffer, size , options);
		}

		inline void IXMPDOMParser_v1::ParseWithContext( const spIXMPNode & node, eActionType actionType,
			const char * buffer, SizeT size /*= std::string::npos */ ) const
		{
			NS_XMPCOMMON::CallConstSafeFunctionReturningVoid< IXMPDOMParser_v1, pIXMPNode_base, UInt32, const char *, SizeT >(
				this, &IXMPDOMParser_v1::ParseWithContext, node.get(), static_cast< UInt32 >( actionType), buffer, size );
		}

		inline spIXMPDOMParser IXMPDOMParser_v1::Clone( eMultiThreadingSupport multiThreadingSupport ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMParser_v1, pIXMPDOMParser_base, IXMPDOMParser, UInt32 >(
				this, &IXMPDOMParser_v1::Clone, static_cast< UInt32 >( multiThreadingSupport ) );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPDOMParser_h__
