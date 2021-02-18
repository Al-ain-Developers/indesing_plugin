#ifndef IXMPStructureNode_h__
#define IXMPStructureNode_h__ 1

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
// 11-05-14 ADC 5.6-c026 [3847480] New DOM : IXMPDOMParser and IXMPDOMSerializer interfaces should include all the dependencies.
// 11-05-14 ADC 5.6-c025 Added some utility functions to IXMPArrayNode and IXMPStructureNode.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-25-14 ADC 5.6-c005 Porting changes done by Honey to Mac Environment.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
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
	//! \brief Version1 of the interface that represents a structure Node of XMP DOM.
	//! \details Provides all the functions to get and set various properties of the structure node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPStructureNode_v1
		: public virtual IXMPCompositeNode_v1
	{
	public:

		using IXMPCompositeNode_v1::GetNode;

		//!
		//! Get the const child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetNode( const char * nameSpace, const char * name ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetNode( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetSimpleNode;

		//!
		//! Get the const simple child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPSimpleNode GetSimpleNode( const char * nameSpace, const char * name ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the simple child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of simple node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode GetSimpleNode( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetStructureNode;
		//!
		//! Get the const structure child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPStructureNode GetStructureNode( const char * nameSpace, const char * name ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the structure child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of structure node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructureNode GetStructureNode( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::GetArrayNode;
		//!
		//! Get the const array child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPSimpleNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPArrayNode GetArrayNode( const char * nameSpace, const char * name ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the array child node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//! \attention In case a node exists at the given path but is of not of array node type an error is thrown.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode GetArrayNode( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::InsertNode;
		//!
		//! Inserts a given node.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode containing the node to be inserted.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# given node is already a child of some other node.
		//!		-# there exists a node with the same nameSpace and name combination.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void InsertNode( const spIXMPNode & node ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::ReplaceNode;
		//!
		//! Replaces a given node.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode.
		//! \attention error is thrown in following cases:
		//!		-# given node is invalid.
		//!		-# given node is already a child of some other node.
		//!		-# there exists no node with the same nameSpace and name combination.
		//! \note type of the old existing node may/may not be same as that of new node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ReplaceNode( const spIXMPNode & node ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		using IXMPCompositeNode_v1::RemoveNode;
		//!
		//! Remove the node with the specified nameSpace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing node which is removed from the tree.
		//! \note In case no node exists with the given nameSpace and name combination an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode RemoveNode( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		// Factories to create the structure node
		//!
		//! Creates a structure node which is not part of any metadata document.
		//! \param[in] nameSpace pointer to a const NULL terminated char buffer containing namespace of the structure node.
		//! \param[in] name pointer to a const NULL terminated char buffer containing name of the structure node.
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting
		//! from the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPStructureNode object.
		//! \attention error is thrown in the following cases:
		//!		-# nameSpace is NULL or its contents are empty.
		//!		-# name is NULL or its contents are empty.
		//!
		XMP_PRIVATE static spIXMPStructureNode CreateStructureNode( const char * nameSpace, const char * name,
			eMultiThreadingSupport multiThreadingSupport = kMultiThreadingConfiguredAtInitialization );

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIXMPNode_base GetNode( const char * nameSpace, const char * name, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetNode( const char * nameSpace, const char * name, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void InsertNode( pIXMPNode node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void ReplaceNode( pIXMPNode node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPNode_base RemoveNode( const char * nameSpace, const char * name, pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPStructureNode_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPStructureNode_v1::~IXMPStructureNode_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"

	namespace NS_XMPCORE {

		inline spcIXMPNode IXMPStructureNode_v1::GetNode( const char * nameSpace, const char * name ) const  {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPStructureNode_v1, pcIXMPNode_base, const IXMPNode, const char *, const char * >(
				this, &IXMPStructureNode_v1::GetNode, nameSpace, name );
		}

		inline spIXMPNode IXMPStructureNode_v1::GetNode( const char * nameSpace, const char * name ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPStructureNode_v1, pIXMPNode_base, IXMPNode, const char *, const char * >(
				this, &IXMPStructureNode_v1::GetNode, nameSpace, name );
		}

		inline void IXMPStructureNode_v1::InsertNode( const spIXMPNode & node ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPStructureNode_v1, pIXMPNode_base >(
				this, &IXMPStructureNode_v1::InsertNode, node.get() );
		}

		inline void IXMPStructureNode_v1::ReplaceNode( const spIXMPNode & node ) {
			NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPStructureNode_v1, pIXMPNode_base >(
				this, &IXMPStructureNode_v1::ReplaceNode, node.get() );
		}

		inline spIXMPNode IXMPStructureNode_v1::RemoveNode( const char * nameSpace, const char * name ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPStructureNode_v1, pIXMPNode_base, IXMPNode, const char *, const char * >(
				this, &IXMPStructureNode_v1::RemoveNode, nameSpace, name );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#if !BUILDING_XMPCORE_LIB
	#include "XMPCore/Interfaces/IXMPSimpleNode.h"
	#include "XMPCore/Interfaces/IXMPArrayNode.h"

	namespace NS_XMPCORE {

		inline spcIXMPStructureNode IXMPCompositeNode_v1::GetStructureNode( const spcIXMPPath & path ) const {
			spcIXMPNode node = GetNode( path );
			if ( node )
				return AdaptConstNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spcIXMPStructureNode();
		}

		inline spIXMPStructureNode IXMPCompositeNode_v1::GetStructureNode( const spcIXMPPath & path ) {
			spIXMPNode node = GetNode( path );
			if ( node )
				return AdaptNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spIXMPStructureNode();
		}

		inline spcIXMPSimpleNode IXMPStructureNode_v1::GetSimpleNode( const char * nameSpace, const char * name ) const {
			spcIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptConstNodeTo< IXMPSimpleNode >( node, IXMPNode_base::kXMPNodeTypeSimple );
			else
				return spcIXMPSimpleNode();
		}

		inline spIXMPSimpleNode IXMPStructureNode_v1::GetSimpleNode( const char * nameSpace, const char * name ) {
			spIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptNodeTo< IXMPSimpleNode >( node, IXMPNode_base::kXMPNodeTypeSimple );
			else
				return spIXMPSimpleNode();
		}

		inline spcIXMPStructureNode IXMPStructureNode_v1::GetStructureNode( const char * nameSpace, const char * name ) const {
			spcIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptConstNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spcIXMPStructureNode();
		}

		inline spIXMPStructureNode IXMPStructureNode_v1::GetStructureNode( const char * nameSpace, const char * name ) {
			spIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptNodeTo< IXMPStructureNode >( node, IXMPNode_base::kXMPNodeTypeStructure );
			else
				return spIXMPStructureNode();
		}

		inline spcIXMPArrayNode IXMPStructureNode_v1::GetArrayNode( const char * nameSpace, const char * name ) const {
			spcIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptConstNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spcIXMPArrayNode();
		}

		inline spIXMPArrayNode IXMPStructureNode_v1::GetArrayNode( const char * nameSpace, const char * name ) {
			spIXMPNode node = GetNode( nameSpace, name );
			if ( node )
				return AdaptNodeTo< IXMPArrayNode >( node, IXMPNode_base::kXMPNodeTypeArray );
			else
				return spIXMPArrayNode();
		}

	}

#endif  // !BUILDING_XMPCORE_LIB

#endif // IXMPStructureNode_h__
