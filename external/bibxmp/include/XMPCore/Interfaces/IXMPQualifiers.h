#ifndef __IXMPQualifiers_h__
#define __IXMPQualifiers_h__ 1

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
//  ADC Amandeep Chawla
//  DKG Deepak Kumar Garg
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 DKG 5.6-c016 Fixing crash in XMPCompositeNode, functionality bugs in XMPNode and linking issue in XMPQualifiers.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
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
	//! \brief Version1 of the interface that represents qualifiers added to any node of XMP DOM.
	//! \details Provides all the functions to get and set various properties of the qualifier nodes.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPQualifiers_v1
		: public virtual IXMPStructureNode_v1
	{
	public:
		//!
		//! Get the const node on which these qualifiers are present.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode representing the host of qualifier nodes.
		//! \note Returns an invalid shared pointer to const #NS_XMPCORE::IXMPNode in case the qaulifier node
		//! is not part of tree.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetHost() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the node on which these qualifiers are present.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode representing the host of qualifier nodes.
		//! \note Returns an invalid shared pointer to #NS_XMPCORE::IXMPNode in case the qaulifier node
		//! is not part of tree.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetHost() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Creates an object of qualifiers which is not part of any metadata document.
		//! \param[in]		multithreadingSupport	a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether the new object
		//! created should be thread safe or not. By default new object created will inherit its setting from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPQualifiers object.
		//! \note In case the value is a null pointer or its contents are empty than the value is set to empty string.
		//!
		XMP_PRIVATE static spIXMPQualifiers CreateQualifiers( eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIXMPNode_base GetHost( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetHost( pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		using IXMPStructureNode_v1::GetParent;
		using IXMPNode_v1::GetNameSpace;
		using IXMPNode_v1::GetName;

		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPQualifiers_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPQualifiers_v1::~IXMPQualifiers_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

	//implement all unsafe functions as inline calling safe function internally

		inline spcIXMPNode IXMPQualifiers_v1::GetHost() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPQualifiers_v1, pcIXMPNode_base, const IXMPNode >(
				this, &IXMPQualifiers_v1::GetHost );
		}

		inline spIXMPNode IXMPQualifiers_v1::GetHost() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPQualifiers_v1, pIXMPNode_base, IXMPNode >(
				this, &IXMPQualifiers_v1::GetHost );
		}

	// some functions of IXMPNode which can't be defined in IXMPNode.h because of cyclic header file dependency
		inline spcIXMPQualifiers IXMPNode_v1::GetQualifiers() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pcIXMPQualifiers_base, const IXMPQualifiers >(
				this, &IXMPNode_v1::GetQualifiers );
		}

		inline spIXMPQualifiers IXMPNode_v1::GetQualifiers() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPNode_v1, pIXMPQualifiers_base, IXMPQualifiers >(
				this, &IXMPNode_v1::GetQualifiers );
		}

		inline void IXMPNode_v1::SetQualifiers( const spIXMPQualifiers & qualifiers ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPNode_v1, pIXMPQualifiers_base >(
				this, &IXMPNode_v1::SetQualifiers, qualifiers.get() );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPQualifiers_h__
