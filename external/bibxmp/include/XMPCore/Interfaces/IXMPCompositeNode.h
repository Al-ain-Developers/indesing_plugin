#ifndef __IXMPCompositeNode_h__
#define __IXMPCompositeNode_h__ 1

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
#endif	// AdobePrivate

#include "XMPCore/Interfaces/IXMPNode.h"

namespace NS_XMPCORE {

	//!
	//! \brief Version1 of the interface that serves as a base interface to all composite types of nodes
	//! in the XMP DOM ( like Arrays and Structures ).
	//! \details Provides all the functions to get various properties of the composite node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPCompositeNode_v1
		: public virtual IXMPNode_v1
	{
	public:

		//!
		//! Get the node specified by the path relative to the composite node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetNode( const spcIXMPPath & path ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the node specified by the path relative to the composite node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetNode( const spcIXMPPath & path ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Appends a given node as the child of the node. In case of array node it is appended at the last
		//! and in case of structure node qualified name of the node to be inserted determines its position.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode containing the node to be
		//! appended as the last child.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# type of given node is not same as other child items of the array node.
		//!		-# given node is already a child of some other node.
		//!		-# node already has a child node with the same qualified name in case of structure node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void AppendNode( const spIXMPNode & node ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Inserts a given node at the path relative to the composite node.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode containing the node to be
		//! inserted at the specified relative path.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path.
		//! \note All the hierarchy of nodes is created if not present.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# type of given node is not same as other child items of the array node.
		//!		-# given node is already a child of some other node.
		//!		-# given path is invalid or logically incorrect.
		//!		-# type of given node is not suitable for the destination location.
		//!		-# a node already exists at the specified path.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void InsertNode( const spIXMPNode & node, const spcIXMPPath & path ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Replaces an existing node with the given node at the path relative to the composite node..
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# type of given node is not same as other child items of the array node.
		//!		-# given node is already a child of some other node.
		//!		-# given index is less than 1 or greater than current child count.
		//!		-# type of given node is not suitable for the destination location.
		//!		-# no node exists at the specified path.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ReplaceNode( const spIXMPNode & node, const spcIXMPPath & path ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get an iterator object to iterate over all the child nodes of the composite node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not.
		//! \return a shared pointer to #NS_XMPCORE::IXMPConstNodeIterator object.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPConstNodeIterator Iterator(
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get an iterator object to iterate over all the child nodes of the composite node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNodeIterator object.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNodeIterator Iterator(
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Remove the node specified by the path relative to the composite node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node which is removed from the tree.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode RemoveNode( const spcIXMPPath & path ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the count of child nodes of the composite node.
		//! \return an object of type #NS_XMPCOMMON::SizeT containing the count of children of the node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT GetChildCount() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Indicates whether the composite node is empty or not.
		//! \return a bool value; true in case the node has no children, false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsEmpty() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Wrapper non virtual functions
		//!
		//! Get a simple node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE spcIXMPSimpleNode GetSimpleNode( const spcIXMPPath & path ) const;

		//!
		//! Get the node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE spIXMPSimpleNode GetSimpleNode( const spcIXMPPath & path );

		//!
		//! Get a array node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPArrayNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE spcIXMPArrayNode GetArrayNode( const spcIXMPPath & path ) const;

		//!
		//! Get the array node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPArrayNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE spIXMPArrayNode GetArrayNode( const spcIXMPPath & path );

		//!
		//! Get a structure node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPStructureNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE spcIXMPStructureNode GetStructureNode( const spcIXMPPath & path ) const;

		//!
		//! Get the structure node specified by the path relative to the node.
		//! \param[in] path shared pointer to a const #NS_XMPCORE::IXMPPath object containing the relative path
		//! from the node to the node client is interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPStructureNode object containing node.
		//! \note In case no node exists at the given path an invalid shared pointer is returned.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE spIXMPStructureNode GetStructureNode( const spcIXMPPath & path );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		virtual pcIXMPNode_base GetNode( pcIXMPPath_base path, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetNode( pcIXMPPath_base path, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void AppendNode( pIXMPNode_base node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void InsertNode( pIXMPNode_base node, pcIXMPPath_base path, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void ReplaceNode( pIXMPNode_base node, pcIXMPPath_base path, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPConstNodeIterator_base Iterator( UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNodeIterator_base Iterator( UInt32 multiThreadingSupport, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPNode_base RemoveNode( pcIXMPPath_base path, pcIError_base & error ) __NOTHROW__ = 0;
		virtual SizeT GetChildCount( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 IsEmpty( pcIError_base & error ) const __NOTHROW__ = 0;
	//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPCompositeNode_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPCompositeNode_v1::~IXMPCompositeNode_v1() __NOTHROW__ { }
}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCore/Interfaces/IXMPConstNodeIterator.h"
	#include "XMPCore/Interfaces/IXMPNodeIterator.h"

	namespace NS_XMPCORE {

		inline spcIXMPNode IXMPCompositeNode_v1::GetNode( const spcIXMPPath & path ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPCompositeNode_v1, pcIXMPNode_base, const IXMPNode, pcIXMPPath_base >(
				this, &IXMPCompositeNode_v1::GetNode, path.get() );
		}

		inline spIXMPNode IXMPCompositeNode_v1::GetNode( const spcIXMPPath & path ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPCompositeNode_v1, pIXMPNode_base, IXMPNode, pcIXMPPath_base >(
				this, &IXMPCompositeNode_v1::GetNode, path.get() );
		}

		inline void IXMPCompositeNode_v1::AppendNode( const spIXMPNode & node ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPCompositeNode_v1, pIXMPNode_base >(
				this, &IXMPCompositeNode_v1::AppendNode, node.get() );
		}

		inline void IXMPCompositeNode_v1::InsertNode( const spIXMPNode & node, const spcIXMPPath & path ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPCompositeNode_v1, pIXMPNode_base, pcIXMPPath_base >(
				this, &IXMPCompositeNode_v1::InsertNode, node.get(), path.get() );
		}

		inline void IXMPCompositeNode_v1::ReplaceNode( const spIXMPNode & node, const spcIXMPPath & path ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPCompositeNode_v1, pIXMPNode_base, pcIXMPPath_base >(
				this, &IXMPCompositeNode_v1::ReplaceNode, node.get(), path.get() );
		}

		inline spIXMPConstNodeIterator IXMPCompositeNode_v1::Iterator(
			eMultiThreadingSupport multiThreadingSupport /*= kMultiThreadingConfiguredAtInitialization */ ) const
		{
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPCompositeNode_v1, pIXMPConstNodeIterator_base, IXMPConstNodeIterator, UInt32 > (
				this, &IXMPCompositeNode_v1::Iterator, static_cast< UInt32> ( multiThreadingSupport ) );
		}

		inline spIXMPNodeIterator IXMPCompositeNode_v1::Iterator(
			eMultiThreadingSupport multiThreadingSupport /*= kMultiThreadingConfiguredAtInitialization */ )
		{
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPCompositeNode_v1, pIXMPNodeIterator_base, IXMPNodeIterator, UInt32 >(
				this, &IXMPCompositeNode_v1::Iterator, static_cast< UInt32 >( multiThreadingSupport ) );
		}

		inline spIXMPNode IXMPCompositeNode_v1::RemoveNode( const spcIXMPPath & path ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPCompositeNode_v1, pIXMPNode_base, IXMPNode, pcIXMPPath_base >(
				this, &IXMPCompositeNode_v1::RemoveNode, path.get() );
		}

		inline SizeT IXMPCompositeNode_v1::GetChildCount() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPCompositeNode_v1, SizeT, SizeT >(
				this, &IXMPCompositeNode_v1::GetChildCount );
		}

		inline bool IXMPCompositeNode_v1::IsEmpty() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPCompositeNode_v1, bool, UInt32 >(
				this, &IXMPCompositeNode_v1::IsEmpty );
		}
}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#if !BUILDING_XMPCORE_LIB
	#include "XMPCore/Interfaces/IXMPSimpleNode.h"

	namespace NS_XMPCORE {

		inline spcIXMPSimpleNode IXMPCompositeNode_v1::GetSimpleNode( const spcIXMPPath & path ) const {
			spcIXMPNode node = GetNode( path );
			if ( node )
				return AdaptConstNodeTo< IXMPSimpleNode >( node, IXMPNode::kXMPNodeTypeSimple );
			return spcIXMPSimpleNode();
		}

		inline spIXMPSimpleNode IXMPCompositeNode_v1::GetSimpleNode( const spcIXMPPath & path ) {
			spIXMPNode node = GetNode( path );
			if ( node )
				return AdaptNodeTo< IXMPSimpleNode >( node, IXMPNode::kXMPNodeTypeSimple );
			return spIXMPSimpleNode();
		}

	}
#endif  // !BUILDING_XMPCORE_LIB

#endif  // __IXMPCompositeNode_h__
