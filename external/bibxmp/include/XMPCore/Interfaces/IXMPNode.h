#ifndef __IXMPNode_h__
#define __IXMPNode_h__ 1

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
// 01-09-15 ADC 5.6-c034 Enhanced Clone functionality for Nodes to skip empty nodes.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
//
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
#include "XMPCommon/Interfaces/IError.h"

namespace NS_XMPCORE {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that serves as a base interface to all types of nodes in the XMP DOM.
	//! \details Provides all the functions to get various properties of the node.
	//! \attention Support multi threading through locks but can be disabled by the client.
	//!
	class XMP_PUBLIC IXMPNode_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Indicates various types of node available in XMP Data Model like simple, array and structure.
		//!
		typedef enum {
			//! XMP Node is of Simple Node type (key value pair).
			kXMPNodeTypeSimple				= 0,
			//! XMP Node is of Array type. Indexing start from 1.
			kXMPNodeTypeArray				= 1,
			//! XMP Node is of structure type. 
			kXMPNodeTypeStructure			= 2,

			//! Maximum value this enum can hold, should be treated as invalid value
			kXMPNodeTypeMaxValue			= NS_XMPCOMMON::kMaxEnumValue
		} eXMPNodeType;

		//!
		//! Get the parent node of the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode representing the parent of the node.
		//! \note Returns an invalid shared pointer to const #NS_XMPCORE::IXMPNode in case the node is a root node or
		//! it is not part of tree.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetParent() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the parent node of the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode representing the parent of the node.
		//! \details Returns an invalid shared pointer to #NS_XMPCORE::IXMPNode in case the node is a root node or
		//! it is not part of tree.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetParent() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the local name of the node.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String representing the name of the node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetName() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the name space of the node.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String representing the name space of the node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetNameSpace() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the path of the node from the root of the metadata.
		//! \return a shared pointer to #NS_XMPCORE::IXMPPath representing the path of the node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPath GetPath( eMultiThreadingSupport = NS_XMPCOMMON::kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get all the const qualifiers associated with the node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPQualifiers object containing all the qualifiers associated with the node.
		//! \note In case the node has no qualifiers then an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPQualifiers GetQualifiers() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get all the qualifiers associated with the node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPQualifiers object containing all the qualifiers associated with the node.
		//! \note In case the node has no qualifiers then an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPQualifiers GetQualifiers() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Set all the qualifiers associated with the node.
		//! \param[in] qualifiers a shared pointer to #NS_XMPCORE::IXMPQualifiers object containing all the qualifiers to be
		//! associated with the node.
		//! \attention throws error if qualifiers is an invalid shared pointer.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetQualifiers( const spIXMPQualifiers & qualifiers ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the const qualifier node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing namespace URI of the qualifier node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the qualifier node.
		//! \return a shared pointer to const #NS_XMPCORE::IXMPNode object containing qualifier node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode GetQualifier( const char * nameSpace, const char * name ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the qualifier node of the node having specified namespace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the qualifier node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the qualifier node.
		//! \return a shared pointer to a #NS_XMPCORE::IXMPNode object containing qualifier node.
		//! \note In case no node exists with the specified nameSpace and name combination then an invalid shared pointer
		//! is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode GetQualifier( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Inserts a given qualifier node.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode containing the qualifier node to be inserted.
		//! \attention error is thrown in following cases:
		//!		-# given qualifier node is invalid.
		//!		-# given qualifier node is already a child of some other node.
		//!		-# there exists a qualifier node with the same nameSpace and name combination.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void InsertQualifier( const spIXMPNode & node ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Replaces a given qualifier node.
		//! \param[in] node shared pointer to an object of #NS_XMPCORE::IXMPNode.
		//! \attention error is thrown in following cases:
		//!		-# given qualifier node is invalid.
		//!		-# given qualifier node is already a child of some other node.
		//!		-# there exists no qualifier node with the same nameSpace and name combination.
		//! \note warning is raised in case the type of the old existing node is not same as that of new node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void ReplaceQualifier( const spIXMPNode & node ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Remove the qualifier node with the specified nameSpace and name.
		//! \param[in] nameSpace pointer to a null terminated constant char buffer containing name space URI of the qualifier node.
		//! \param[in] name pointer to a null terminated constant char buffer containing local name of the qualifier node.
		//! \return a shared pointer to #NS_XMPCORE::IXMPNode object containing qualifier node which is removed from the node.
		//! \note In case no qualifier node exists at the given index an invalid shared pointer is returned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode RemoveQualifier( const char * nameSpace, const char * name ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the node type of the node.
		//! \return an object of type #eXMPNodeType indicating the type of the node.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eXMPNodeType GetNodeType() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Indicates whether the node is a direct child of an array node.
		//! \return a bool value; true in case the node is a direct child of an array node, false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool IsArrayItem() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Indicates whether the node has any qualifiers associated with it.
		//! \return a bool value; true in case the node has any qualifier associated with it, false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool HasQualifiers() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Clear the contents of the node.
		//! \param[in] contents a value of bool type indicating clearing contents of the node other than qualifiers
		//! if set to true.
		//! \param[in] qualifiers a value of bool type indicating clearing the qualifiers of the node if set to true.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void Clear( bool contents = true, bool qualifiers = true ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Virtual copy constructor
		//! Clones the node creating an exact replica of the node which is not part of any metadata tree.
		//! \param[in] ignoreEmptyNodes a bool value controlling whether to clone empty nodes or not.
		//! \param[in] ignoreQualifiersForMarkingNodesAsEmpty a bool value controlling whether presence of qualifiers should mark
		//! node as non empty.
		//! \param[in] multiThreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting from
		//! the object begin cloned.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode Clone( bool ignoreEmptyNodes = false, bool ignoreQualifiersForMarkingNodesAsEmpty = false, eMultiThreadingSupport multiThreadingSupport = kMultiThreadingUseClonedObjectValue ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//TODO: @Aman add move, copy and serialize functions. Change Name and NameSpace can also be provided.

		template < typename derivedType >
		XMP_PRIVATE static shared_ptr< const derivedType > AdaptConstNodeTo(
			const spcIXMPNode & baseNode, IXMPNode_base::eXMPNodeType nodeTypeValue, bool throwErrorOnFailure = true )
		{
			IXMPNode_base::eXMPNodeType actualNodeType = baseNode->GetNodeType();
			if ( actualNodeType == nodeTypeValue ) {
				return NS_XMPCOMMON::MakeSharedPointer< const derivedType >( baseNode.get() );
			} else if ( throwErrorOnFailure ) {
				static const char * nodeTypeNames[] = { "kXMPNodeTypeSimple", "kXMPNodeTypeArray", "kXMPNodeTypeStructure" };
				static const char * params[2];
				params[0] = nodeTypeNames[ static_cast< UInt32 >( nodeTypeValue) ];
				params[1] = nodeTypeNames[ static_cast< UInt32 >( actualNodeType ) ];
				ThrowError( IError_base::kDomainXMPDataModel, kXMPDataModelCodeDifferentNodeTypePresent,
					false, "Different type of node present than the one expected by the client", __FILE__, __LINE__,
					2, params );
			} 
			return shared_ptr< const derivedType>();
		}

		template < typename derivedType >
		XMP_PRIVATE static shared_ptr< derivedType > AdaptNodeTo(
			const spIXMPNode & baseNode, IXMPNode_base::eXMPNodeType nodeTypeValue, bool throwErrorOnFailure = true )
		{
			IXMPNode_base::eXMPNodeType actualNodeType = baseNode->GetNodeType();
			if ( actualNodeType == nodeTypeValue ) {
				return NS_XMPCOMMON::MakeSharedPointer< derivedType >( baseNode.get() );
			} else if ( throwErrorOnFailure ) {
				static const char * nodeTypeNames[] = { "kXMPNodeTypeSimple", "kXMPNodeTypeArray", "kXMPNodeTypeStructure" };
				static const char * params[2];
				params[0] = nodeTypeNames[ static_cast< UInt32 >( nodeTypeValue) ];
				params[1] = nodeTypeNames[ static_cast< UInt32 >( actualNodeType ) ];
				ThrowError( IError_base::kDomainXMPDataModel, kXMPDataModelCodeDifferentNodeTypePresent,
					false, "Different type of node present than the one expected by the client", __FILE__, __LINE__,
					2, params );
			}
			return shared_ptr< derivedType>();
		}

	#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		// all safe functions
		virtual pcIXMPNode_base GetParent( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetParent( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetName( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetNameSpace( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPPath_base GetPath( UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIXMPQualifiers_base GetQualifiers( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPQualifiers_base GetQualifiers( pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetQualifiers( pIXMPQualifiers_base qualifiers, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pcIXMPNode_base GetQualifier( const char * nameSpace, const char * name, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIXMPNode_base GetQualifier( const char * nameSpace, const char * name, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void InsertQualifier( pIXMPNode_base node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void ReplaceQualifier( pIXMPNode_base node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPNode_base RemoveQualifier( const char * nameSpace, const char * name, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 GetNodeType( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 IsArrayItem( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 HasQualifiers( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void Clear( UInt32 contents, UInt32 qualifiers, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIXMPNode_base Clone( UInt32 ignoreEmptyNodes, UInt32 ignoreQualifiersForMarkingNodesAsEmpty, UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
	#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IXMPNode_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IXMPNode_v1::~IXMPNode_v1() __NOTHROW__ { }

}

#if !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB
	#include "XMPCommon/Utilities/TWrapperFunctions.h"
	#include "XMPCommon/Interfaces/IUTF8String.h"
	#include "XMPCore/Interfaces/IXMPPath.h"

	namespace NS_XMPCORE {

		inline spcIXMPNode IXMPNode_v1::GetParent() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pcIXMPNode_base, const IXMPNode >(
				this, &IXMPNode_v1::GetParent );
		}

		inline spIXMPNode IXMPNode_v1::GetParent() {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPNode_v1, pIXMPNode_base, IXMPNode >(
				this, &IXMPNode_v1::GetParent );
		}

		inline spcIUTF8String IXMPNode_v1::GetName() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pcIUTF8String_base, const IUTF8String >(
				this, &IXMPNode_v1::GetName );
		}

		inline spcIUTF8String IXMPNode_v1::GetNameSpace() const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pcIUTF8String_base, const IUTF8String >(
				this, &IXMPNode_v1::GetNameSpace );
		}

		inline spIXMPPath IXMPNode_v1::GetPath( eMultiThreadingSupport multiThreadingSupport ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pIXMPPath_base, IXMPPath, UInt32 >(
				this, &IXMPNode_v1::GetPath, static_cast< UInt32 >( multiThreadingSupport ) );
		}

		inline IXMPNode_base::eXMPNodeType IXMPNode_v1::GetNodeType() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPNode_v1, eXMPNodeType, UInt32 >(
				this, &IXMPNode_v1::GetNodeType );
		}

		inline bool IXMPNode_v1::IsArrayItem() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPNode_v1, bool, UInt32 >(
				this, &IXMPNode_v1::IsArrayItem );
		}

		inline bool IXMPNode_v1::HasQualifiers() const {
			return NS_XMPCOMMON::CallConstSafeFunction< IXMPNode_v1, bool, UInt32 >(
				this, &IXMPNode_v1::HasQualifiers );
		}

		inline spcIXMPNode IXMPNode_v1::GetQualifier( const char * nameSpace, const char * name ) const {
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pcIXMPNode_base, const IXMPNode, const char *, const char * >(
				this, &IXMPNode_v1::GetQualifier, nameSpace, name );
		}

		inline spIXMPNode IXMPNode_v1::GetQualifier( const char * nameSpace, const char * name ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPNode_v1, pIXMPNode_base, IXMPNode, const char *, const char * >(
				this, &IXMPNode_v1::GetQualifier, nameSpace, name );
		}

		inline void IXMPNode_v1::InsertQualifier( const spIXMPNode & node ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPNode_v1, pIXMPNode_base >(
				this, &IXMPNode_v1::InsertQualifier, node.get() );
		}

		inline void IXMPNode_v1::ReplaceQualifier( const spIXMPNode & node ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPNode_v1, pIXMPNode_base >(
				this, &IXMPNode_v1::ReplaceQualifier, node.get() );
		}

		inline spIXMPNode IXMPNode_v1::RemoveQualifier( const char * nameSpace, const char * name ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IXMPNode_v1, pIXMPNode_base, IXMPNode, const char *, const char * >(
				this, &IXMPNode_v1::RemoveQualifier, nameSpace, name );
		}

		inline void IXMPNode_v1::Clear( bool contents /*= true*/, bool qualifiers /*= true */ ) {
			return NS_XMPCOMMON::CallSafeFunctionReturningVoid< IXMPNode_v1, UInt32, UInt32 >(
				this, &IXMPNode_v1::Clear, static_cast< UInt32 >( contents ), static_cast< UInt32 >( qualifiers ) );
		}

		inline spIXMPNode IXMPNode_v1::Clone( bool ignoreEmptyNodes/* = false*/, bool ignoreQualifiersForMarkingNodesAsEmpty/* = false*/,
			eMultiThreadingSupport multiThreadingSupport/*= kMultiThreadingUseClonedObjectValue */ ) const
		{
			return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IXMPNode_v1, pIXMPNode_base, IXMPNode, UInt32, UInt32, UInt32 >(
				this, &IXMPNode_v1::Clone, static_cast< UInt32 >( ignoreEmptyNodes ), static_cast< UInt32 >( ignoreQualifiersForMarkingNodesAsEmpty ),
				static_cast< UInt32 >( multiThreadingSupport ) );
		}

	}

#endif  // !SOURCE_COMPILED && !BUILDING_XMPCORE_LIB

#endif  // __IXMPNode_h__
