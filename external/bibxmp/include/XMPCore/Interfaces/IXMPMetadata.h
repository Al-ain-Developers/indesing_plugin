#ifndef __IXMPMetadata_h__
#define __IXMPMetadata_h__ 1

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
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 HK  5.5-c034 Implementing Serialize(), Clone() and all setter/modifier methods of XMP DOM.
// 02-12-14 HK  5.5-c030 Creating client glue code for XMP DOM APIs.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/Interfaces/IXMPStructureNode.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that represents the whole xmp metadata for an asset.
	//! Provides all the functions to add or remove nodes to and from metadata.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPMetadata_v1
		: public virtual IXMPStructureNode_v1
	{
	public:
		//!
		//! Get the about URI string for the xmp metadata.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing
		//! URI string.
		//! \note By default this is an empty string.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetAboutURI() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Set the about URI string for the xmp metadata.
		//! \param[in] uri pointer to a constant null terminated char buffer containing uri string.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetAboutURI( const char * uri ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the XMP Metadata.
		//!
		//! Creates an empty metadata object.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting
		//! from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPMetadata object.
		//!
		XMP_PRIVATE static spIXMPMetadata CreateMetadata(
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIUTF8String_base GetAboutURI( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void SetAboutURI( const char * uri, pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		using IXMPStructureNode_v1::GetParent;
		using IXMPNode_v1::GetNameSpace;
		using IXMPNode_v1::GetName;

		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPMetadata_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPMetadata_v1::~IXMPMetadata_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline spcIUTF8String IXMPMetadata_v1::GetAboutURI() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPMetadata_v1, pcIUTF8String_base, const IUTF8String >(
				this, &IXMPMetadata_v1::GetAboutURI );
		}

		inline void IXMPMetadata_v1::SetAboutURI( const char * uri ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPMetadata_v1, const char * >(
				this, &IXMPMetadata_v1::SetAboutURI, uri );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPMetadata_h__
