#ifndef __IXMPStructNode_h__
#define __IXMPStructNode_h__ 1

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

#include "XMPCore/Interfaces/IXMPNode.h"
#include "XMPCore/Interfaces/IXMPArrayNode.h"

namespace NS_XMPCORE {

	/**
	 * This class extends XMP node and represents XMP structure property.
	 */
	class XMP_PUBLIC IXMPStructNode_v1
		: public virtual IXMPNode_v1
	{
	public:
		/**
		 * This method creates a simple property of specified name,value,namespace and sets it to this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest SetSimpleNode( const char * nameSpace, const char * name, const char * value );
		/**
		 * This method creates an array of specified name,form type,namespace and sets it to this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest SetArrayNode( const char * nameSpace, const char * name, eXMPArrayNodeForm form );
		/**
		 * This method creates a structure of specified name,namespace and sets it to this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest SetStructNode( const char * nameSpace, const char * name );
		//spIXMPLanguageAlternative SetLanguageAlternative( const char * nameSpace, const char * name );

		using IXMPNode_v1::GetNode;
		/**
		 * This method returns node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetNode( const char * nameSpace, const char * name ) const;
		/**
		 * This method returns node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetNode( const char * nameSpace, const char * name );
		/**
		 * This method returns simple node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPSimpleNode_latest GetSimpleNode( const char * nameSpace, const char * name ) const;
		/**
		 * This method returns simple node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest GetSimpleNode( const char * nameSpace, const char * name );
		/**
		 * This method returns array node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPArrayNode_latest GetArrayNode( const char * nameSpace, const char * name ) const;
		/**
		 * This method returns array node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest GetArrayNode( const char * nameSpace, const char * name );
		/**
		 * This method returns structure node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPStructNode_latest GetStructNode( const char * nameSpace, const char * name ) const;
		/**
		 * This method returns structure node of specified name and namespace if present in this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest GetStructNode( const char * nameSpace, const char * name );
		//spcIXMPLanguageAlternative GetLanguageAlternative( const char * nameSpace, const char * name ) const;
		//spIXMPLanguageAlternative GetLanguageAlternative( const char * nameSpace, const char * name );

		/**
		 * This method does nothing currently.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RenameField( const char * oldNameSpace, const char * oldName, const char * newNameSpace, const char* newName );
		/**
		 * This method does nothing currently.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPConstNodeIterator_latest GetAllPropertiesInNameSpace( const char * nameSpace ) const;
		/**
		 * This method does nothing currently.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNodeIterator_latest GetAllPropertiesInNameSpace( const char * nameSpace );

		using IXMPNode_v1::Remove;
		/**
		 * This method removes a field of specified name and namespace from this structure.
		 */
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest Remove ( const char * nameSpace, const char * name );

	protected:
		virtual pIXMPSimpleNode_latest SetSimpleNode( const char * nameSpace, const char * name, const char * value, pIError_base & err ) __NOTHROW__ = 0;
		virtual pIXMPArrayNode_latest SetArrayNode( const char* nameSpace, const char * name, eXMPArrayNodeForm form, pIError_base & err ) __NOTHROW__ = 0;
		virtual pIXMPStructNode_latest SetStructNode( const char * nameSpace, const char * name, pIError_base & err) __NOTHROW__ = 0;

		virtual pcIXMPNode_latest GetNode( const char * nameSpace, const char * name, pIError_base & err ) const __NOTHROW__ = 0;
		virtual pIXMPNode_latest GetNode( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;

		virtual pcIXMPSimpleNode_latest GetSimpleNode( const char * nameSpace, const char * name, pIError_base & err ) const __NOTHROW__ = 0;
		virtual pIXMPSimpleNode_latest GetSimpleNode( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;
		virtual pcIXMPArrayNode_latest GetArrayNode( const char * nameSpace, const char * name, pIError_base & err ) const __NOTHROW__ = 0;
		virtual pIXMPArrayNode_latest GetArrayNode( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;
		virtual pcIXMPStructNode_latest GetStructNode( const char * nameSpace, const char * name, pIError_base & err ) const __NOTHROW__ = 0;
		virtual pIXMPStructNode_latest GetStructNode( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;
		//virtual pcIXMPLanguageAlternative_latest GetLanguageAlternative( const char * nameSpace, const char * name, pIError_base & err ) const __NOTHROW__ = 0;
		//virtual pIXMPLanguageAlternative_latest GetLanguageAlternative( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;

		virtual bool RenameField( const char * oldNameSpace, const char * oldName, const char * newNameSpace, const char* newName, pIError_base & err ) __NOTHROW__ = 0;

		virtual pIXMPConstNodeIterator_latest GetAllPropertiesInNameSpace( const char * nameSpace, pIError_base & err ) const __NOTHROW__ = 0;
		virtual pIXMPNodeIterator_latest GetAllPropertiesInNameSpace( const char * nameSpace, pIError_base & err ) __NOTHROW__ = 0;

		virtual pIXMPNode_latest Remove ( const char * nameSpace, const char * name, pIError_base & err ) __NOTHROW__ = 0;

		virtual ~IXMPStructNode_v1() __NOTHROW__ = 0;

		#ifndef FRIEND_CLASS_DECLARATION
			#define FRIEND_CLASS_DECLARATION() 
		#endif
		FRIEND_CLASS_DECLARATION();

	};

	inline IXMPStructNode_v1::~IXMPStructNode_v1() __NOTHROW__ { }
};

#endif  // __IXMPStructNode_h__
