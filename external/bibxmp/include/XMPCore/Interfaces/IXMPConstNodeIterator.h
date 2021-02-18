#ifndef IXMPConstNodeIterator_h__
#define IXMPConstNodeIterator_h__ 1

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
	//! \brief Version1 of the interface that represents an iterator over the const children of a XMP DOM Node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//! \note Iterators are valid as long as their are no changes performed on the node. In case there are some
	//! changes performed on the node then the behavior is undefined.
	//!
	class XMP_PUBLIC IXMPConstNodeIterator_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Get the const node currently pointed by the iterator.
		//! \return a shared pointer to a const object of type #NS_XMPCORE::IXMPNode.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetNode() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Advances iterator by one position.
		//! \return a shared pointer to an object of type #NS_XMPCORE::IXMPConstNodeIterator.
		//! \note shared pointer is invalid in case the current node is the last one.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPConstNodeIterator Next() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;


	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIXMPNode_base GetNode( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPConstNodeIterator_base Next( pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPConstNodeIterator_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPConstNodeIterator_v1::~IXMPConstNodeIterator_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline spcIXMPNode IXMPConstNodeIterator_v1::GetNode() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPConstNodeIterator_v1, pcIXMPNode_base, const IXMPNode >(
				this, &IXMPConstNodeIterator_v1::GetNode );
		}

		inline spIXMPConstNodeIterator IXMPConstNodeIterator_v1::Next() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPConstNodeIterator_v1, pIXMPConstNodeIterator_base, IXMPConstNodeIterator >(
				this, &IXMPConstNodeIterator_v1::Next );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif // IXMPConstNodeIterator_h__
