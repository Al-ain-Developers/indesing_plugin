#ifndef __IXMPNodeIterator_h__
#define __IXMPNodeIterator_h__ 1


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
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-12-14 HK  5.5-c030 Creating client glue code for XMP DOM APIs.
// 02-12-14 HK  5.5-c029 Fixing PK failure for XMPCore DOM unit tests.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that represents an iterator over the mutable children of a XMP DOM Node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//! \note Iterators are valid as long as their are no changes performed on the node. In case there are some
	//! changes performed on the node then the behavior is undefined.
	//!
	class XMP_PUBLIC IXMPNodeIterator_v1
		: public virtual ISharedOwnership_v1
	{
	public:

		//!
		//! Get the mutable node currently pointed by the iterator.
		//! \return a shared pointer to an object of type #NS_XMPCORE::IXMPNode.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetNode() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Advances iterator by one position.
		//! \return a shared pointer to an object of type #NS_XMPCORE::IXMPNodeIterator.
		//! \note shared pointer is invalid in case the current node is the last one.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNodeIterator Next() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pIXMPNode_base GetNode( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNodeIterator_base Next( pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPNodeIterator_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPNodeIterator_v1::~IXMPNodeIterator_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline spIXMPNode IXMPNodeIterator_v1::GetNode() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNodeIterator_v1, pIXMPNode_base, IXMPNode >(
				this, &IXMPNodeIterator_v1::GetNode );
		}

		inline spIXMPNodeIterator IXMPNodeIterator_v1::Next() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPNodeIterator_v1, pIXMPNodeIterator_base, IXMPNodeIterator >(
				this, &IXMPNodeIterator_v1::Next );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPNodeIterator_h__
