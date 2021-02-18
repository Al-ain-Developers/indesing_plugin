#ifndef IXMPDOMImplementationRegistry_h__
#define IXMPDOMImplementationRegistry_h__ 1

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
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;
	
	//!
	//! \brief Version1 of the interface that serves as a database/registry of all the parsers and
	//! serializers available with the XMPCore library.
	//! \details Provides all the functions to
	//!		-# get registered serializers and parsers from the database.
	//!		-# add client defined serializers and parsers to the database.
	//! \attention Support multi threading if library is configured to support multi-threading by default.
	//! \note By default following keys are registered by default with the database by the library:
	//! \note		-# rdf
	//!
	class XMP_PUBLIC IXMPDOMImplementationRegistry_v1
		: public virtual ISharedOwnership_v1
	{
	public:

		//!
		//! Creates a copy of the parser corresponding to the key and returns to the client for usage.
		// \param[in] key pointer to a const NULL terminated char buffer containing key of the parser in the database.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPDOMParser object.
		//! \note In case the key is not present in the database an invalid shared pointer will be returned.
		//! \note key is case sensitive.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMParser CreateParser( const char * key,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Creates a copy of the serializer corresponding to the key and returns to the client for usage.
		// \param[in] key pointer to a const NULL terminated char buffer containing key of the serializer in the database.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPDOMSerializer object.
		//! \note In case the key is not present in the database an invalid shared pointer will be returned.
		//! \note key is case sensitive.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPDOMSerializer CreateSerializer( const char * key,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Registers a parser with the database along with the key.
		//! \param[in] key pointer to a const NULL terminated char buffer containing key of the parser to be used while registering.
		//! \param[in] parser a shared pointer to #NS_XMPCORE::IXMPDOMParser object to be registered with the database.
		//! \attention currently it is unimplemented.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void RegisterParser( const char * key, const spIXMPDOMParser & parser ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Registers a serializer with the database along with the key.
		//! \param[in] key pointer to a const NULL terminated char buffer containing key of the serializer to be used while registering.
		//! \param[in] parser a shared pointer to #NS_XMPCORE::IXMPDOMSerializer object to be registered with the database.
		//! \attention currently it is unimplemented.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void RegisterSerializer( const char * key, const spIXMPDOMSerializer & serializer ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Provides the reference to the database of Serializers and Parsers available with the library.
		//! \return a shared pointer to IXMPDOMImplementationRegistry object containing all the entries for serailizers and parsers.
		//!
		XMP_PRIVATE static spIXMPDOMImplementationRegistry GetDOMImplementationRegistry();

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pIXMPDOMParser_base CreateParser( const char * key, UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPDOMSerializer_base CreateSerializer( const char * key, UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void RegisterParser( const char * key, pIXMPDOMParser_base parser, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void RegisterSerializer( const char * key, pIXMPDOMSerializer_base serializer, pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPDOMImplementationRegistry_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPDOMImplementationRegistry_v1::~IXMPDOMImplementationRegistry_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCore/Interfaces/IXMPDOMParser.h"
	#include "XMPCore/Interfaces/IXMPDOMSerializer.h"

	namespace NS_XMPCORE {

	//implement all unsafe functions as inline calling safe function internally

		inline spIXMPDOMParser IXMPDOMImplementationRegistry_v1::CreateParser( const char * key,
			eMultiThreadingSupport multiThreadingSupport /*= kMultiThreadingConfiguredAtInitialization */ ) const
		{
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMImplementationRegistry_v1, pIXMPDOMParser_base, IXMPDOMParser, const char *, UInt32 >(
				this, &IXMPDOMImplementationRegistry_v1::CreateParser, key, static_cast< UInt32 >( multiThreadingSupport ) );
		}

		inline spIXMPDOMSerializer IXMPDOMImplementationRegistry_v1::CreateSerializer( const char * key,
			eMultiThreadingSupport multiThreadingSupport /*= kMultiThreadingConfiguredAtInitialization */ ) const
		{
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPDOMImplementationRegistry_v1, pIXMPDOMSerializer_base, IXMPDOMSerializer, const char *, UInt32 >(
				this, &IXMPDOMImplementationRegistry_v1::CreateSerializer, key, static_cast< UInt32 >( multiThreadingSupport ) );
		}

		inline void IXMPDOMImplementationRegistry_v1::RegisterParser( const char * key, const spIXMPDOMParser & parser ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPDOMImplementationRegistry_v1, const char *, pIXMPDOMParser_base >(
				this, &IXMPDOMImplementationRegistry_v1::RegisterParser, key, parser.get() );
		}

		inline void IXMPDOMImplementationRegistry_v1::RegisterSerializer( const char * key, const spIXMPDOMSerializer & serializer ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPDOMImplementationRegistry_v1, const char *, pIXMPDOMSerializer_base >(
				this, &IXMPDOMImplementationRegistry_v1::RegisterSerializer, key, serializer.get() );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPDOMImplementationRegistry_h__
