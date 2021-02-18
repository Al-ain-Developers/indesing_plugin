//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/INXFormatDefs.h $
//  
//  Owner: Steve Pellegrin
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __INXFORMATDEFS__
#define __INXFORMATDEFS__

namespace INXCore
{
	// Used to construct serialized attribute values.
	PUBLIC_DECL extern const char* kDOMInt64Separator;
	PUBLIC_DECL extern const char* kDOMDateSeparator;
	PUBLIC_DECL extern const char* kDOMDateTimeSeparator;
	PUBLIC_DECL extern const char* kDOMTimeSeparator;

	PUBLIC_DECL extern const wchar_t* kDOMTrue;
	PUBLIC_DECL extern const wchar_t* kDOMFalse;
	PUBLIC_DECL extern const wchar_t* kDOMTypeValueSeparator;
	PUBLIC_DECL extern const wchar_t* kDOMTypeValueSeparatorEntity;
	PUBLIC_DECL extern const wchar_t* kDOMNilPointer;

	// All of these are unique single characters
	static const wchar_t kDOMReadOnly =						'r';
	static const wchar_t kEmptyType =						'0';
	static const wchar_t kBooleanType =						'b';
	static const wchar_t kStringType =						'c';
	static const wchar_t kKeyType =							'k';
	static const wchar_t kShortType =						's';
	static const wchar_t kLongType =						'l';
	static const wchar_t kLongLongType =					'L';
	static const wchar_t kDoubleType =						'd';
	static const wchar_t kReadableDoubleType =				'D';
	static const wchar_t kObjectType =						'o';
	static const wchar_t kDateType =						't';
	static const wchar_t kReadableDateType =				'T';
	static const wchar_t kFileType =						'f';
	static const wchar_t kEnumType =						'e';
	static const wchar_t kUnitType =						'u';
	static const wchar_t kReadableUnitType =				'U';
	static const wchar_t kListType =						'x';
	static const wchar_t kObjectListType =					'y';
	static const wchar_t kRecordType =						'z';
	static const wchar_t kLeadingSpace =					' ';
	static const wchar_t kStreamType =						'm';

	// Element and attribute names for Expanded INX
	PUBLIC_DECL extern const wchar_t*  kPropertiesElement;
	PUBLIC_DECL extern const wchar_t*  kPropertyElement;
	PUBLIC_DECL extern const wchar_t*  kTypeAttribute;

	// All of these are unique strings
	PUBLIC_DECL extern const wchar_t* kDOMTrueExpanded;
	PUBLIC_DECL extern const wchar_t* kDOMFalseExpanded;

	PUBLIC_DECL extern const wchar_t*  kEmptyTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kBooleanTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kStringTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kShortTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kLongTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kLongLongTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kDoubleTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kObjectTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kDateTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kFileTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kEnumTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kUnitTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kStreamTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kListTypeExpanded;
	PUBLIC_DECL extern const wchar_t*  kRecordTypeExpanded;
}

#endif	//#ifndef __INXFORMATDEFS__

