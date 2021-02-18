#ifndef __IXMPDOMFactory_h__
#define __IXMPDOMFactory_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IXMPDOMFactory.h
/// @brief Definition of IXMPDOMFactory interface and related types
///
/// This header defines the interface of the IXMPDOMFactory type and its related types.
///
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-27-14 HK  5.6-c006 Implementation of Remove API + Adding support for creating empty DOM nodes.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 5.5-c024 Added a new API to the XMPCore to return pointer to interface
//						 IXMPDOMFactory
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCore/XMPCore_Defines.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCore/Interfaces/IXMPArrayNode.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ITSingleton.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	class IXMPPathSegment_v1;
	/**
	 * This class represents a factory to create various artifacts of XMP DOM like array, structure, path etc.
	 */
	class XMP_PUBLIC IXMPDOMFactory_v1
		: public virtual ITSingleton< IXMPDOMFactory_v1 >
	{
	public:
		/**
		 * This method creates and returns a segment for XMP property of specified name in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPathSegment_latest CreatePropertySegment( const char * nameSpace, const char * name );
		/**
		 * This method creates and returns a segment for XMP array index in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPathSegment_latest CreateArrayIndexSegment( const char * nameSpace, size_t index );
		/**
		 * This method creates and returns a segment for XMP qualifier of specified name in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPathSegment_latest CreateQualifierSegment( const char * nameSpace, const char * name );
		/**
		 * This method creates and returns a selecter segment for XMP qualifier of specified name,value in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPathSegment_latest CreateQualifierSelectorSegment( const char * nameSpace, const char * name, const char * value );
		/**
		 * This method creates and returns an empty XMP path.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPath_latest CreateEmptyPath();
		/**
		 * This method creates and returns a path by parsing specified expression.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPath_latest CreatePathByParsing( const char * );
		/**
		 * This method creates and returns XMP DOM from specified XMP packet of specified length.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPMetadata_latest CreateDOMFromPacket( const char * packet, SizeT length);
		/**
		 * This method creates and returns empty XMP qualifier.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPQualifiers_latest CreateQualifiers ();
		/**
		 * This method creates and returns a simple XMP property of specified name in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest CreateSimpleNode( const char * nameSpace, const char * name );
		/**
		 * This method creates and returns an XMP array of specified form type and name in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest CreateArrayNode( eXMPArrayNodeForm form, const char * nameSpace, const char * name );
		/**
		 * This method creates and returns a XMP structure of specified name in specified namespace.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest CreateStructNode( const char * nameSpace, const char * name );

	protected:
		virtual pIXMPPathSegment_latest CreatePropertySegment( const char * nameSpace, const char * name, pIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPPathSegment_latest CreateArrayIndexSegment( const char * nameSpace, size_t index, pIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPPathSegment_latest CreateQualifierSegment( const char * nameSpace, const char * name, pIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPPathSegment_latest CreateQualifierSelectorSegment( const char * nameSpace, const char * name, const char * value, pIError_base & error ) __NOTHROW__ = 0;

		virtual pIXMPPath_latest CreateEmptyPath( pIError_base & ) __NOTHROW__ = 0;
		virtual pIXMPPath_latest CreatePathByParsing( const char *, pIError_base & ) __NOTHROW__ = 0;

		virtual pIXMPMetadata_latest CreateDOMFromPacket( const char * packet, SizeT length, pIError_base & ) __NOTHROW__ = 0;
		
		virtual pIXMPQualifiers_latest CreateQualifiers ( pIError_base & ) __NOTHROW__ = 0;
		virtual pIXMPSimpleNode_latest CreateSimpleNode( const char * nameSpace, const char * name, pIError_base & ) __NOTHROW__ = 0;
		virtual pIXMPArrayNode_latest CreateArrayNode( eXMPArrayNodeForm form, const char * nameSpace, const char * name, pIError_base & ) __NOTHROW__ = 0;
		virtual pIXMPStructNode_latest CreateStructNode( const char * nameSpace, const char * name, pIError_base & ) __NOTHROW__ = 0;

		virtual ~IXMPDOMFactory_v1() = 0;
	};

	inline IXMPDOMFactory_v1::~IXMPDOMFactory_v1() { }
}

extern "C" NS_XMPCORE::IXMPDOMFactory_base * XMP_PUBLIC WXMPMeta_GetXMPDOMFactoryInstance_1();

#endif  // __IXMPDOMFactory_h__
