//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SchemaTypes.h $
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
//  
//  Adobe patent application tracking # P409, entitled 'Schema-based file Conversion',
//  inventors: Robin Briggs, Steve Pellegrin
//  
//========================================================================================

#pragma once
#if !defined(_SCHEMA_TYPES_)
#define _SCHEMA_TYPES_

// ----- Includes -----

#include "AnsiBasedTypes.h"


#if !defined(__ODFRC__)
namespace Schemas
{
#endif
	typedef int16	SwitchType;
	typedef uint16	FieldType;
	typedef uint16	FieldID;

	const FieldID	kInvalidFieldID = 0;


	// Base values for various Field types.
	const FieldType kInvalidField				= 0x0000;
	const FieldType kBuiltInBase				= 0x0001;
	const FieldType kBuiltInArrayOffset			= 0x4000;
	const FieldType kStandardObjectsBase		= 0x8001;
	const FieldType kStructuredTypesBase		= 0xC001;
	
	// "BuiltIn" field types (most map to Stream xfer methods).
	const FieldType kBool8						= (kBuiltInBase + 0);
	const FieldType kBool16						= (kBuiltInBase + 1);
	const FieldType kInt8						= (kBuiltInBase + 2);
	const FieldType kUint8						= (kBuiltInBase + 3);
	const FieldType kInt16						= (kBuiltInBase + 4);
	const FieldType kUint16						= (kBuiltInBase + 5);
	const FieldType kInt32						= (kBuiltInBase + 6);
	const FieldType kUint32						= (kBuiltInBase + 7);
	const FieldType kReal						= (kBuiltInBase + 8);
	const FieldType kClassID					= (kBuiltInBase + 9);
	const FieldType kInterfaceID				= (kBuiltInBase + 10);
	const FieldType kImplementationID			= (kBuiltInBase + 11);
	const FieldType kWidgetID					= (kBuiltInBase + 12);
	const FieldType kMessageID					= (kBuiltInBase + 13);
	const FieldType kServiceID					= (kBuiltInBase + 14);
	const FieldType kErrorID					= (kBuiltInBase + 15);
	const FieldType kPluginID					= (kBuiltInBase + 16);
	const FieldType kObject						= (kBuiltInBase + 17);
	const FieldType kReference					= (kBuiltInBase + 18);
	const FieldType kAttrBoss					= (kBuiltInBase + 19);
	const FieldType kAttrBossList				= (kBuiltInBase + 20);
	const FieldType kDataBlob8					= (kBuiltInBase + 21);
	const FieldType kDataBlob16					= (kBuiltInBase + 22);
	const FieldType kDataBlob32					= (kBuiltInBase + 23);

	// Arrays of BuiltIn types.
	const FieldType kBool8Array					= (kBool8 + kBuiltInArrayOffset);
	const FieldType kBool16Array				= (kBool16 + kBuiltInArrayOffset);
	const FieldType kInt8Array					= (kInt8 + kBuiltInArrayOffset);
	const FieldType kUint8Array					= (kUint8 + kBuiltInArrayOffset);
	const FieldType kInt16Array					= (kInt16 + kBuiltInArrayOffset);
	const FieldType kUint16Array				= (kUint16 + kBuiltInArrayOffset);
	const FieldType kInt32Array					= (kInt32 + kBuiltInArrayOffset);
	const FieldType kUint32Array				= (kUint32 + kBuiltInArrayOffset);
	const FieldType kRealArray					= (kReal + kBuiltInArrayOffset);
	const FieldType kClassIDArray				= (kClassID + kBuiltInArrayOffset);
	const FieldType kInterfaceIDArray			= (kInterfaceID + kBuiltInArrayOffset);
	const FieldType kImplementationIDArray		= (kImplementationID + kBuiltInArrayOffset);
	const FieldType kWidgetIDArray				= (kWidgetID + kBuiltInArrayOffset);
	const FieldType kMessageIDArray				= (kMessageID + kBuiltInArrayOffset);
	const FieldType kServiceIDArray				= (kServiceID + kBuiltInArrayOffset);
	const FieldType kErrorIDArray				= (kErrorID + kBuiltInArrayOffset);
	const FieldType kPluginIDArray				= (kPluginID + kBuiltInArrayOffset);
	const FieldType kObjectArray				= (kObject + kBuiltInArrayOffset);
	const FieldType kReferenceArray				= (kReference + kBuiltInArrayOffset);
		
	// "Object" field types must have special handling.
	const FieldType kPMString					= (kStandardObjectsBase + 0);
	const FieldType kPMPoint					= (kStandardObjectsBase + 1);
	const FieldType kPMRect						= (kStandardObjectsBase + 2);
	const FieldType kPMMatrix					= (kStandardObjectsBase + 3);
	const FieldType kNameInfo					= (kStandardObjectsBase + 4);
	const FieldType kWideString					= (kStandardObjectsBase + 5);
	const FieldType kURI						= (kStandardObjectsBase + 6);
	
	// Structured field types.
	const FieldType kFieldArray					= (kStructuredTypesBase + 0);

#if !defined(__ODFRC__)
	// Useful helper functions
	inline bool16 IsValidField(FieldType t)
		{return (t != kInvalidField);}
	inline bool16 IsBasicField(FieldType t)
		{return ((t >= kBuiltInBase) && (t < (kBuiltInBase + kBuiltInArrayOffset)));}
	inline bool16 IsBasicArrayField(FieldType t)
		{return ((t >= (kBuiltInBase + kBuiltInArrayOffset)) && (t < kStandardObjectsBase));}
	inline bool16 IsStandardObjectField(FieldType t)
		{return ((t >= kStandardObjectsBase) && (t < kStructuredTypesBase));}
	inline bool16 IsStructuredTypeField(FieldType t)
		{return (t >= kStructuredTypesBase);}
	inline bool16 BaseType(FieldType t)
		{return IsBasicArrayField(t) ? (t - kBuiltInArrayOffset) : t;}
#endif

	// SchemaList types
	const SwitchType kSchemaListBase				= 0x0001;

	const SwitchType kClassSchema					= (kSchemaListBase + 0);
	const SwitchType kOtherClassSchema				= (kSchemaListBase + 1);
	const SwitchType kSchema						= (kSchemaListBase + 2);
	const SwitchType kImplementationSchema			= (kSchemaListBase + 3);
	const SwitchType kOtherImplementationSchema		= (kSchemaListBase + 4);

	// Directive types
	const SwitchType kDirectiveBase					= 0x0001;

	const SwitchType kRemoveClass					= (kDirectiveBase + 0);
	const SwitchType kMoveClass						= (kDirectiveBase + 1);
	const SwitchType kMoveClassToPlugin				= (kDirectiveBase + 2);
	const SwitchType kReplaceClass					= (kDirectiveBase + 3);
	const SwitchType kRemoveImplementation			= (kDirectiveBase + 4);
	const SwitchType kMoveImplementation			= (kDirectiveBase + 5);
	const SwitchType kMoveImplementationToPlugin	= (kDirectiveBase + 6);
	const SwitchType kReplaceImplementation			= (kDirectiveBase + 7);
	const SwitchType kRemovePlugin					= (kDirectiveBase + 8);
	const SwitchType kRenumberPlugin				= (kDirectiveBase + 9);
	const SwitchType kIgnorePlugin					= (kDirectiveBase + 10);
	
	// Special value for FormatNumberPaths.
	const int32 NoPathPredecessor				= -1;


#if !defined(__ODFRC__)
}	// End namespace Schemas
#endif

#endif	// !defined(_SCHEMA_TYPES_)
