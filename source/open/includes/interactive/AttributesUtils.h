//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/interactive/AttributesUtils.h $
//  
//  Owner: Tim Wright
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
//  This file contains common defines and macros for often-used functions.
//  
//  Adapted From SDKUtilities.h in the SDK
//  
//========================================================================================

#pragma once
#ifndef __AttributesUtils_h__
#define __AttributesUtils_h__

#include "IAttributesUtils.h"
#include "Utils.h"

//------------------------------------------------------------


namespace AttributesUtils
{
	inline ErrorCode SetInt32Value(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, int32 inValue)
		{return Utils<IAttributesUtils>()->SetInt32Value(inCommandString, iGfxAttrSuite, inAttrBoss, inValue); }
	inline ErrorCode SetBoolValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, bool16 inValue)
		{return Utils<IAttributesUtils>()->SetBoolValue(inCommandString, iGfxAttrSuite, inAttrBoss, inValue); }
	inline ErrorCode SetStringValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const PMString& inValue)
		{return Utils<IAttributesUtils>()->SetStringValue(inCommandString, iGfxAttrSuite, inAttrBoss, inValue); }
	inline ErrorCode SetRealValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const PMReal& inValue)
		{return Utils<IAttributesUtils>()->SetRealValue(inCommandString, iGfxAttrSuite, inAttrBoss, inValue); }
	
	inline bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, int32* outCommonValue)
		{return Utils<IAttributesUtils>()->HasUniqueValue(iGfxAttrSuite, inAttrBoss, outCommonValue); }
	inline bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, bool16* outCommonValue)
		{return Utils<IAttributesUtils>()->HasUniqueValue(iGfxAttrSuite, inAttrBoss, outCommonValue); }
	inline bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, PMString* outCommonValue)
		{return Utils<IAttributesUtils>()->HasUniqueValue(iGfxAttrSuite, inAttrBoss, outCommonValue); }
	inline bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, PMReal* outCommonValue)
		{return Utils<IAttributesUtils>()->HasUniqueValue(iGfxAttrSuite, inAttrBoss, outCommonValue); }
	inline bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->HasUniqueValue(iGfxAttrSuite, inAttrBoss); }

	inline int32 GetInt32Value(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetInt32Value(inBoss, inAttrBoss); }
	inline bool16 GetBoolValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetBoolValue(inBoss, inAttrBoss); }
	inline PMString GetStringValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetStringValue(inBoss, inAttrBoss);
	}
	inline PMString GetFontValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetFontValue(inBoss, inAttrBoss);
	}
	inline PMReal GetRealValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetRealValue(inBoss, inAttrBoss); }
	inline UID GetFontFamilyUIDValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetFontFamilyUIDValue(inBoss, inAttrBoss);
	}
	inline Form::ChoiceList GetChoiceList(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetChoiceList(inBoss, inAttrBoss); }
	inline IPMUnknown* QueryValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, PMIID inInterfaceID)
		{return Utils<IAttributesUtils>()->QueryValue(inBoss, inAttrBoss, inInterfaceID); }

	// Note: Set* routines that take IGraphicAttributeSuite are normally preferred (these handle selections, defaults, etc.)
	// These only operate on one item, and need to take place within a Command...

	inline ErrorCode SetInt32Value(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, int32 inValue)
		{return Utils<IAttributesUtils>()->SetInt32Value(inBoss, inAttrBoss, inValue); }
	inline ErrorCode SetBoolValue(IGraphicStyleDescriptor * inBoss,  const ClassID inAttrBoss, bool16 inValue)
		{return Utils<IAttributesUtils>()->SetBoolValue(inBoss, inAttrBoss, inValue); }
	inline ErrorCode SetStringValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, const PMString& inValue)
		{return Utils<IAttributesUtils>()->SetStringValue(inBoss, inAttrBoss, inValue); }
	inline ErrorCode SetRealValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, const PMReal& inValue)
		{return Utils<IAttributesUtils>()->SetRealValue(inBoss, inAttrBoss, inValue); }

	inline int32 GetInt32Value(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetInt32Value(inBoss, inAttrBoss); }
	inline bool16 GetBoolValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetBoolValue(inBoss, inAttrBoss); }
	inline PMString GetStringValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetStringValue(inBoss, inAttrBoss);
	}
	inline PMString GetFontValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetFontValue(inBoss, inAttrBoss);
	}
	inline PMReal GetRealValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetRealValue(inBoss, inAttrBoss); }
	inline PMPoint GetPointValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
		{return Utils<IAttributesUtils>()->GetPointValue(inBoss, inAttrBoss); }
	inline UID GetFontFamilyUIDValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss)
	{
		return Utils<IAttributesUtils>()->GetFontFamilyUIDValue(inBoss, inAttrBoss);
	}
	inline ErrorCode AddInt32Value(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, int32 inValue)
		{return Utils<IAttributesUtils>()->AddInt32Value(inAttrs, inAttrBoss, inValue); }
	inline ErrorCode AddBoolValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, bool16 inValue)
		{return Utils<IAttributesUtils>()->AddBoolValue(inAttrs, inAttrBoss, inValue); }
	inline ErrorCode AddStringValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMString& inValue)
		{return Utils<IAttributesUtils>()->AddStringValue(inAttrs, inAttrBoss, inValue); }
	inline ErrorCode AddRealValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMReal& inValue)
		{return Utils<IAttributesUtils>()->AddRealValue(inAttrs, inAttrBoss, inValue); }
	inline ErrorCode AddPointValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMPoint& inValue)
		{return Utils<IAttributesUtils>()->AddPointValue(inAttrs, inAttrBoss, inValue); }
	inline ErrorCode AddValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, IPMUnknown* inValue)
		{return Utils<IAttributesUtils>()->AddValue(inAttrs, inAttrBoss, inValue); }
}

//------------------------------------------------------------

#endif // __AttributesUtils_h__


// End, AttributesUtils.h.

