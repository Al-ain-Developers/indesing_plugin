//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAttributesUtils.h $
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
//========================================================================================

#pragma once
#ifndef __IAttributesUtils_h__
#define __IAttributesUtils_h__

#include "FormFieldTypes.h"

//=============================================================================

class IGraphicAttributeSuite;
class IGraphicStyleAttributeBossList;
class IGraphicStyleDescriptor;
class UIDList;
class PMPoint;

/** Utility interface for getting and setting graphic attributes.
	In particular, used to get and set form field graphic attributes.
*/
class IAttributesUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IATTRIBUTESUTILS };

	/** Set a graphic attribute on a selection 
		@param inCommandString, the command string to use for the set. This is what shows up as the Undo <command>
		@param iGfxAttrSuite the selection to modify
		@param inAttrBoss attribute to modify eg kTextMaxLengthAttrBoss
		@param inValue new value of attribute
	*/
	virtual ErrorCode SetInt32Value(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const int32& inValue) = 0;
	virtual ErrorCode SetBoolValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const bool16& inValue) = 0;
	virtual ErrorCode SetStringValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const PMString& inValue) = 0;
	virtual ErrorCode SetRealValue(const PMString& inCommandString, IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, const PMReal& inValue) = 0;
	
	/** Get a graphic attribute on a selection. Properly handles multiple selections of items.
		@param iGfxAttrSuite the selection to modify
		@param inAttrBoss attribute to get eg kTextMaxLengthAttrBoss
		@param outCommonValue value of attribute if all items in the selection match
		@returns true if all the values of the attribute in the selection are the same.
	*/
	virtual bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, int32* outCommonValue) = 0;
	virtual bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, bool16* outCommonValue) = 0;
	virtual bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, PMString* outCommonValue) = 0;
	virtual bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss, PMReal* outCommonValue) = 0;
	virtual bool16 HasUniqueValue(IGraphicAttributeSuite * iGfxAttrSuite, const ClassID inAttrBoss) = 0;

	/** Get a graphic attribute on a IGraphicStyleDescriptor. Used to get attributes from a single page item. (eg kPushButtonItemBoss)
		Will assert and return a dummy default if attribute doesn't exist.
		@param inBoss the list of attributes, typically a page item.
		@param inAttrBoss attribute to get eg kTextMaxLengthAttrBoss
		@returns values of attribute.
	*/
	virtual int32 GetInt32Value(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual bool16 GetBoolValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMString GetStringValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMReal GetRealValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual Form::ChoiceList GetChoiceList(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;

	/** Get a graphic attribute on a IGraphicStyleDescriptor. Used to get attributes from a single page item. (eg kPushButtonItemBoss)
		Will assert and return a dummy default if attribute doesn't exist.
		@param inBoss the list of attributes, typically a page item.
		@param inAttrBoss attribute to get eg kTextMaxLengthAttrBoss
		@param inInterfaceID interface to get eg IID_IINTEGER
		@returns values of attribute.
	*/
	virtual IPMUnknown* QueryValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, PMIID inInterfaceID) = 0;


	/** Set a graphic attribute on a IGraphicStyleDescriptor. Used to get attributes from a single page item. (eg kPushButtonItemBoss)
		Note: These Set* routines that take IGraphicAttributeSuite are normally preferred (these handle selections, defaults, etc.)
		These only operate on one item, and need to take place within a Command...

		@param inBoss the list of attributes, typically a page item.
		@param inAttrBoss attribute to get eg kTextMaxLengthAttrBoss
		@param inValue new value of attribute
		@returns result of attribute setting command.
	*/
	virtual ErrorCode SetInt32Value(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, const int32& inValue) = 0;
	virtual ErrorCode SetBoolValue(IGraphicStyleDescriptor * inBoss,  const ClassID inAttrBoss, const bool16& inValue) = 0;
	virtual ErrorCode SetStringValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, const PMString& inValue) = 0;
	virtual ErrorCode SetRealValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss, const PMReal& inValue) = 0;


	/** Get a graphic attribute on a IGraphicStyleAttributeBossList.
		Will assert and return a dummy default if attribute doesn't exist.
		@param inBoss the list of attributes
		@param inAttrBoss attribute to get eg kTextMaxLengthAttrBoss
		@returns values of attribute.
	*/
	virtual int32 GetInt32Value(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
	virtual bool16 GetBoolValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMString GetStringValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMReal GetRealValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMPoint GetPointValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;

	/** Add a graphic attribute on a IGraphicStyleAttributeBossList.
		Will assert and return a dummy default if attribute doesn't exist.
		
		Used when setting multiple attributes, or when setting default attributes (eg the Form FIeld setting dialogs)
		@param inAttrs the list of attributes
		@param inAttrBoss attribute to set eg kTextMaxLengthAttrBoss
		@param inValue new value of attribute
		@returns result of attribute setting command.
	*/
	virtual ErrorCode AddInt32Value(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, int32 inValue) = 0;
	virtual ErrorCode AddBoolValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, bool16 inValue) = 0;
	virtual ErrorCode AddStringValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMString& inValue) = 0;
	virtual ErrorCode AddRealValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMReal& inValue) = 0;
	virtual ErrorCode AddPointValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, const PMPoint& inValue) = 0;
	virtual ErrorCode AddValue(IGraphicStyleAttributeBossList * inAttrs, const ClassID inAttrBoss, IPMUnknown* inAttrValue) = 0;
	virtual PMString GetFontValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual PMString GetFontValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
	virtual UID GetFontFamilyUIDValue(IGraphicStyleDescriptor * inBoss, const ClassID inAttrBoss) = 0;
	virtual UID GetFontFamilyUIDValue(IGraphicStyleAttributeBossList * inBoss, const ClassID inAttrBoss) = 0;
};

//=============================================================================

#endif // __IAttributesUtils_h__
