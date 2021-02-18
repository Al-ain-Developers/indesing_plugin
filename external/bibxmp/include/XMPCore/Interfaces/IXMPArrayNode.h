#ifndef __IXMPArrayNode_h__
#define __IXMPArrayNode_h__ 1

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
// 11-05-14 ADC 5.6-c025 Added some utility functions to IXMPArrayNode and IXMPStructureNode.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-18-14 HK  5.5-c034 Implementing Serialize(), Clone() and all setter/modifier methods of XMP DOM.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-12-14 HK  5.5-c030 Creating client glue code for XMP DOM APIs.
// 02-12-14 HK  5.5-c029 Fixing PK failure for XMPCore DOM unit tests.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/Interfaces/IXMPCompositeNode.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that represents an Array Node of XMP DOM.
	//! \details Provides all the functions to get and set various properties of the array node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPArrayNode_v1
		: public virtual IXMPCompositeNode_v1
	{
	public:
		//!
		//! Indicates different kinds of array forms possible in XMP i.e, unordered, ordered and alternative.
		//!
		typedef enum {
			//! Array contains entries which are un-ordered.
			kXMPArrayNodeFormUnordered		= 0,
			//! Array contains entries which are ordered.
			kXMPArrayNodeFormOrdered		= 1,
			//! Array contains entries which are ordered plus default value should be the top one.
			kXMPArrayNodeFormAlternative	= 2,

			//! Maximum value this enum can hold, should be treated as invalid value
			kXMPArrayNodeFormMaxValue		= NS_XMPCOMMON::kMaxEnumValue
		} eXMPArrayNodeForm;

		//!
		//! Get the type of array.
		//! \return a value of type #eXMPArrayNodeForm indicating the type of array.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eXMPArrayNodeForm GetArrayForm() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetNode;

		//!
		//! Get the const node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client
		//! is interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists at the given index an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetNode( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the const node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists at the given index an invalid shared pointer is returned.
		//! \note The index of an array is 1-based.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetNode( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetSimpleNode;

		//!
		//! Get the const simple child node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPSimpleNode GetSimpleNode( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the simple child node of the node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode GetSimpleNode( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetStructureNode;
		//!
		//! Get the const structure child node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPStructureNode GetStructureNode( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the structure child node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructureNode GetStructureNode( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetArrayNode;
		//!
		//! Get the const array child node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPArrayNode GetArrayNode( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the array child node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index of the node client is
		//! interested in.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \note The index of an array is 1-based.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode GetArrayNode( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::InsertNode;
		//!
		//! Inserts a given node at the specified index.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode containing the node to be
		//! inserted at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index where the node should
		//! be inserted.
		//! \note The index of an array is 1-based.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# type of given node is not same as other child items of the array node.
		//!		-# given node is already a child of some other node.
		//!		-# given index is less than 1 or greater than current child count + 1.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void InsertNode( const spIXMPNode & node, SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::ReplaceNode;
		//!
		//! Replaces an existing node with the given node at the specified index.
		//! \param[in] node shared pointer to an object of #NS_XMPCOMMON::IXMPNode.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index from
		//! where the node should be replaced.
		//! \note The index of an array is 1-based.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# type of given node is not same as other child items of the array node.
		//!		-# given node is already a child of some other node.
		//!		-# given index is less than 1 or greater than current child count.
		//!		-# no node exists at the requested index.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ReplaceNode( const spIXMPNode & node, SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::RemoveNode;
		//!
		//! Remove the node at the specified index.
		//! \param[in] index an object of type #NS_XMPCOMMON::SizeT indicating the index from where the node
		//! should be removed.
		//! \note The index of an array is 1-based.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node which is removed from the tree.
		//! \note In case no node exists at the given index an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode RemoveNode( SizeT index ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the array node

		//!
		//! Creates an un-ordered array node which is not part of any metadata document.
		//! \param[in] nameSpace pointer to a const NULL terminated char buffer containing namespace of the array node.
		//! \param[in] name pointer to a const NULL terminated char buffer containing name of the array node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting
		//! from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPArrayNode object.
		//! \attention error is thrown in the following cases:
		//!		-# nameSpace is NULL or its contents are empty.
		//!		-# name is NULL or its contents are empty.
		//!		-# invalid value is provided for arrayNodeForm.
		//!
		XMP_PRIVATE static spIXMPArrayNode CreateUnorderedArrayNode( const char * nameSpace, const char * name,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

		//!
		//! Creates an ordered array node which is not part of any metadata document.
		//! \param[in] nameSpace pointer to a const NULL terminated char buffer containing namespace of the array node.
		//! \param[in] name pointer to a const NULL terminated char buffer containing name of the array node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting
		//! from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPArrayNode object.
		//! \attention error is thrown in the following cases:
		//!		-# nameSpace is NULL or its contents are empty.
		//!		-# name is NULL or its contents are empty.
		//!		-# invalid value is provided for arrayNodeForm.
		//!
		XMP_PRIVATE static spIXMPArrayNode CreateOrderedArrayNode( const char * nameSpace, const char * name,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

		//!
		//! Creates an alternative array node which is not part of any metadata document.
		//! \param[in] nameSpace pointer to a const NULL terminated char buffer containing namespace of the array node.
		//! \param[in] name pointer to a const NULL terminated char buffer containing name of the array node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting
		//! from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPArrayNode object.
		//! \attention error is thrown in the following cases:
		//!		-# nameSpace is NULL or its contents are empty.
		//!		-# name is NULL or its contents are empty.
		//!		-# invalid value is provided for arrayNodeForm.
		//!
		XMP_PRIVATE static spIXMPArrayNode CreateAlternativeArrayNode( const char * nameSpace, const char * name,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual UInt32 GetArrayForm( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIXMPNode_base GetNode( SizeT index, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetNode( SizeT index, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void InsertNode( pIXMPNode_base node, SizeT index, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void ReplaceNode( pIXMPNode_base node, SizeT index, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPNode_base RemoveNode( SizeT index, pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPArrayNode_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPArrayNode_v1::~IXMPArrayNode_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline IXMPArrayNode_base::eXMPArrayNodeForm IXMPArrayNode_v1::GetArrayForm() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPArrayNode_v1, eXMPArrayNodeForm, UInt32 >(
				this, &IXMPArrayNode_v1::GetArrayForm );
		}

		inline spcIXMPNode IXMPArrayNode_v1::GetNode( SizeT index ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPArrayNode_v1, pcIXMPNode_base, const IXMPNode, SizeT >(
				this, &IXMPArrayNode_v1::GetNode, index );
		}

		inline spIXMPNode IXMPArrayNode_v1::GetNode( SizeT index ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPArrayNode_v1, pIXMPNode_base, IXMPNode, SizeT >(
				this, &IXMPArrayNode_v1::GetNode, index );
		}

		inline void IXMPArrayNode_v1::InsertNode( const spIXMPNode & node, SizeT index ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPArrayNode_v1, pIXMPNode_base, SizeT >(
				this, &IXMPArrayNode_v1::InsertNode, node.get(), index );
		}

		inline void IXMPArrayNode_v1::ReplaceNode( const spIXMPNode & node, SizeT index ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPArrayNode_v1, pIXMPNode_base, SizeT >(
				this, &IXMPArrayNode_v1::ReplaceNode, node.get(), index );
		}

		inline spIXMPNode IXMPArrayNode_v1::RemoveNode( SizeT index ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPArrayNode_v1, pIXMPNode_base, IXMPNode, SizeT >(
				this, &IXMPArrayNode_v1::RemoveNode, index );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#if !BUILDING_XMPCORE_LIB
#include "XMPCore/Interfaces/IXMPSimpleNode.h"
#include "XMPCore/Interfaces/IXMPStructureNode.h"

	namespace NS_XMPCORE {

		inline spcIXMPArrayNode IXMPCompositeNode_v1::GetArrayNode( const spcIXMPPath & path ) const {
			spcIXMPNode node = GetNode( path );
			if ( node )
				return AdaptConstNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spcIXMPArrayNode();
		}

		inline spIXMPArrayNode IXMPCompositeNode_v1::GetArrayNode( const spcIXMPPath & path ) {
			spIXMPNode node = GetNode( path );
			if ( node )
				return AdaptNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spIXMPArrayNode();
		}

		inline spcIXMPSimpleNode IXMPArrayNode_v1::GetSimpleNode( SizeT index ) const {
			spcIXMPNode node = GetNode( index );
			if ( node )
				return AdaptConstNodeTo< IXMPSimpleNode >( node, IXMPNode_base::kXMPNodeTypeSimple );
			else
				return spcIXMPSimpleNode();
		}

		inline spIXMPSimpleNode IXMPArrayNode_v1::GetSimpleNode( SizeT index ) {
			spIXMPNode node = GetNode( index );
			if ( node )
				return AdaptNodeTo< IXMPSimpleNode >( node, IXMPNode_base::kXMPNodeTypeSimple );
			else
				return spIXMPSimpleNode();
		}

		inline spcIXMPStructureNode IXMPArrayNode_v1::GetStructureNode( SizeT index ) const {
			spcIXMPNode node = GetNode( index );
			if ( node )
				return AdaptConstNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spcIXMPStructureNode();
		}

		inline spIXMPStructureNode IXMPArrayNode_v1::GetStructureNode( SizeT index ) {
			spIXMPNode node = GetNode( index );
			if ( node )
				return AdaptNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spIXMPStructureNode();
		}

		inline spcIXMPArrayNode IXMPArrayNode_v1::GetArrayNode( SizeT index ) const {
			spcIXMPNode node = GetNode( index );
			if ( node )
				return AdaptConstNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spcIXMPArrayNode();
		}

		inline spIXMPArrayNode IXMPArrayNode_v1::GetArrayNode( SizeT index ) {
			spIXMPNode node = GetNode( index );
			if ( node )
				return AdaptNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spIXMPArrayNode();
		}

	}

#endif  // !BUILDING_XMPCORE_LIB

#endif  // __IXMPArrayNode_h__
