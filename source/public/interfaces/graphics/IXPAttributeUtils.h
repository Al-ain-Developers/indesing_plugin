//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPAttributeUtils.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IXPAttributeUtils__
#define __IXPAttributeUtils__

#include "XPID.h"
#include "IPMUnknown.h"
#include "IXPAttributeSuite.h"
#include "Utils.h"

#include "GraphicTypes.h"
#include "ScriptData.h"
#include <vector>

class IGraphicStyleDescriptor;
class IGraphicStyleAttributeBossList;
class IGraphicAttrRealNumber ;
class IGraphicAttrBoolean ;
class IGraphicAttrInt32 ;
class IGraphicAttrPoint;
class ICommand;
class UIDList;
class IPersistUIDData;
class IScriptRequestData;

/** Transparency attribute related utility functions.
		
	@see XPID.h for definition of transparency attribute ClassID.
*/
class IXPAttributeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPATTRIBUTEUTILS };

	//________________________________________________________________________________________
	// [ Common Helpers]
	//________________________________________________________________________________________

	/**	Returns kTrue if the specified attribute class is a basic transparency attribute.
		@param attrClass the transparency attribute class ID
		@return kTrue if attribute class is a basic transparency attribute otherwise kFalse
	*/
	virtual bool16		IsBasicTransparencyAttribute		(ClassID attrClass) = 0;
	/**	Returns kTrue if the specified attribute class is a dropshadow attribute.
		@param attrClass the transparency attribute class ID
		@return kTrue if attribute class is a dropshadow attribute otherwise kFalse
	*/
	virtual bool16		IsDropShadowAttribute				(ClassID attrClass) = 0;
	/**	Returns kTrue if the specified attribute class is a feather attribute.
		@param attrClass the transparency attribute class ID
		@return kTrue if attribute class is a feather attribute otherwise kFalse
	*/
	virtual bool16		IsVignetteAttribute					(ClassID attrClass) = 0;
	/**	Returns a list of transparency attribute class list from the specified attribute class list.
		@param pAttrClassList the source attribute class list
		@return a transparency-only attribute class list.
	*/
	virtual K2Vector<ClassID>*	GetTransparencyAttributesFromList (const K2Vector<ClassID>* pAttrClassList) = 0;
	
	/**	Process the command to apply basic transparency attributes, drop shadow attributes, or
		feather (or vignette) attributes from the given attribute list to the page items.
		Only those attributes whose class ID is part of the specified attributes are applied
		The command used is kXPSetBasicAttributesCmdBoss for basic transparency attributes, 
		kXPSetDropShadowCmdBoss for drop shadow attributes, and kXPSetVignetteCmdBoss for feather attributes.
		@param iAttrList the attribute list to apply
		@param pageItemList the target page item list
		@param bSkipDefaults kTrue if to skip defaults
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode	ApplyBasicTransparencyToPageItems	(IGraphicStyleAttributeBossList* iAttrList, const UIDList& pageItemList, bool16 bSkipDefaults = kFalse ) = 0;
	/**	@see ApplyBasicTransparencyToPageItems
	*/
	virtual ErrorCode	ApplyDropShadowToPageItems			(IGraphicStyleAttributeBossList* iAttrList, const UIDList& pageItemList, bool16 bSkipDefaults = kFalse ) = 0;
	/**	@see ApplyBasicTransparencyToPageItems
	*/
	virtual ErrorCode	ApplyVignetteToPageItems			(IGraphicStyleAttributeBossList* iAttrList, const UIDList& pageItemList, bool16 bSkipDefaults = kFalse ) = 0;

	/** Process the command to apply the specified attributes (in IGraphicStyleAttributeBossList form)
		to the specified page items.  This exercises the kXPSetAttributesCmdBoss.
		@param iAttrList IN The attribute list to set.
		@param pageItemList IN The page items to which to apply the attributes
		@param partialADXYs IN If specified (ie, non-nil), the list of ADXY partials to apply.
		@param autoInitializeGradientFeatherGeometry IN True to do auto-adjustment of gradient feather geometry.
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode ApplyAttributesToPageItems
		(
			IGraphicStyleAttributeBossList* iAttrList, 
			const UIDList& pageItemList, 
			const IXPAttributeSuite::PartialADXYVector* partialADXYs = nil,
			bool32 autoInitializeGradientFeatherGeometry = kFalse
		) = 0;
	
	/** Process the command to apply the specified attributes (in AttributeList form)
		to the specified page items.  This exercises the kXPSetAttributesCmdBoss.
		@param iAttrList IN The attribute list to set.
		@param pageItemList IN The page items to which to apply the attributes
		@param partialADXYs IN If specified (ie, non-nil), the list of ADXY partials to apply.
		@param autoInitializeGradientFeatherGeometry IN True to do auto-adjustment of gradient feather geometry.
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode ApplyAttributesToPageItems
		(
			const IXPAttributeSuite::AttributeList& attrList, 
			const UIDList& pageItemList, 
			const IXPAttributeSuite::PartialADXYVector* partialADXYs = nil,
			bool32 autoInitializeGradientFeatherGeometry = kFalse
		) = 0;
	
	//________________________________________________________________________________________________

	/** Translates attribute types between targets.  For example:

			TranslateAttributeType(kInnerShadowColor, kTargetStroke) -> kStrokeInnerShadowColor
			TranslateAttributeType(kStrokeInnerShadowColor, kTargetPageItem) -> kTargetStroke
			TranslateAttributeType(kTargetStroke, kTargetPageItem) -> kTargetStroke

		The most common usage is to translate from an attribute type that might be page item,
		fill, or stroke to the page item equivalent; thus the default param value for attrTarget.

		@param attrType IN The attribute type (page item, stroke, fill).
		@param attrTarget IN The attribute target to translate the attribute into.
		@return The translated attribute type; or kUnknownAttrType if the
					passed-in type isn't valid in the first place.
	*/
	virtual IXPAttributeSuite::AttributeType TranslateToTarget
		(
			IXPAttributeSuite::AttributeType attrType,
			IXPAttributeSuite::AttributeTarget attrTarget = IXPAttributeSuite::kTargetPageItem
		) = 0;

	/**	Returns the attribute class ID given an attribute type.
		@param attributeType is the attribute type
		@return attribute class ID. Returns kInvalidClass if attributeType is invalid.
	*/
	virtual	ClassID GetAttributeClassID	
		(
			IXPAttributeSuite::AttributeType attributeType
		) = 0;

	/**	Returns the attribute class ID given an attribute type.
		@param attributeType is the attribute type
		@return attribute class ID. Returns kInvalidClass if attributeType is invalid.
	*/
	virtual	IXPAttributeSuite::AttributeType GetAttributeFromClassID	
		(
			ClassID attrClass
		) = 0;

	/**	Returns kTrue if the specified attribute class is a transparency attribute.
		@param attrClass the attribute class ID
		@return kTrue if attribute class is a transparency attribute otherwise kFalse
	*/
	virtual	bool16 IsAttributeTransparencyAttribute
		(
			ClassID attributeClass
		) = 0;

	/**	Returns the specify attribute type's default value.
		@param attributeType is the attribute type
		@return Attribute type's default value.
	*/
	virtual	int32 GetAttributeDefaultValue
		(
			IXPAttributeSuite::AttributeType attributeType
		) = 0;

	/**	Returns the specify attribute type's default value.  This is the preferred method
		since it returns higher-quality information.  Note that the default value here is the
		hard-coded default, not an application or document default.

		@param attrType IN The attribute you're interested in.
		@param value OUT Receives the default hard-coded default value.
		@return Error code (typically kFailure for bad attribute types, kSuccess otherwise).
	*/
	virtual ErrorCode GetAttributeDefaultValue
		(
			IXPAttributeSuite::AttributeType attrType, 
			IXPAttributeSuite::AttributeValue& value
		) = 0;

	/**	Returns the attribute type's interface IID.
		@param attributeType is the attribute type
		@return attribute type's interface IID. Returns IID_IUNKNOWN if attribute type is invalid.
	*/
	virtual	PMIID GetAttributeInterfaceIID
		(
			IXPAttributeSuite::AttributeType attributeType
		) = 0;

	/**	Given a attribute, returns the associated data type.
		@param attrType IN The attribute type.
		@return The attribute's data type.
	*/
	virtual IXPAttributeSuite::AttributeDataType GetAttributeDataType
		(
			IXPAttributeSuite::AttributeType attrType
		) = 0;

	/**	Returns the attribute type's group (e.g., given drop shadow mode, returns drop shadow).
		@param attributeType is the attribute type
		@return Attribute's group.
	*/
	virtual	IXPAttributeSuite::AttributeGroup	GetAttributeGroup
		(
			IXPAttributeSuite::AttributeType attributeType
		) = 0;

	/**	Returns the attribute type's target (e.g., given stroke drop shadow, returns stroke).
		@param attributeType is the attribute type
		@return Attribute's target.
	*/
	virtual	IXPAttributeSuite::AttributeTarget GetAttributeTarget
		(
			IXPAttributeSuite::AttributeType attributeType
		) = 0;

	/**	Returns a list of attribute types for the given attribute group and target.
		@param attributeGroup is the attribute group
		@param attributeTarget is the attribute target
		@param groupAttrList is a list relevant attribute types for the specified attribute group and target.
	*/
	virtual	void GetAttributeGroupAttributeTypes
		(
		const IXPAttributeSuite::AttributeGroup& attributeGroup, 
		const IXPAttributeSuite::AttributeTarget& attributeTarget, 
		std::vector<IXPAttributeSuite::AttributeType>& groupAttrList
		) = 0;

	/** Return the default swatch UID for the given COLOR attribute type in the given document/database.
		Note that this is the *hard coded* value, not the application or document default.

		@param attrType IN The attribute you want; must be a color attr.
		@return The default UID in the document/database, or kInvalidUID if an error or wrong type.
	*/
	virtual UID GetAttributeDefaultSwatchUID
		(
			IXPAttributeSuite::AttributeType type,
			IDataBase* db
		) = 0;

	/**	Return the name of the attribute.
		@param type The transparency attribute ID
		@return An error code, or kSuccess if successful.
	*/
	virtual bool16 GetAttributeName
		(
			IXPAttributeSuite::AttributeType type, 
			PMString& name
		) = 0;

	/**	Return the minimum/maximum values for Real and enum attribute types.
		@param type The transparency attribute ID
		@return An error code, or kSuccess if successful.
	*/
	virtual ErrorCode GetAttributeMinMax
		(
			IXPAttributeSuite::AttributeType type, 
			IXPAttributeSuite::AttributeValue& minValue, 
			IXPAttributeSuite::AttributeValue& maxValue
		) = 0;

	/**	Determines whether the given value (Real and enum types only) is allowed.
		For non-real/enum types no check is made and the attribute is declared 'valid.'

		@param type The transparency attribute ID
		@param value The value to check
		@return An error code, or kSuccess if successful.
	*/
	virtual bool16 IsValidAttributeValue
		(
			IXPAttributeSuite::AttributeType type, 
			const IXPAttributeSuite::AttributeValue& value
		) = 0;

	/** Returns the real type associated with the given attribute (a real number attribute in 
		all cases).  Note that this gives more precise results than GetAttributeUnits, because
		ScriptData::UnitType doesn't capture all the aspects of the nature of the real.

		@param attrType IN The attribute.
		@return The real kind, or kRealKindInvalid if it's not a real number attribute.
	*/
	virtual IXPAttributeSuite::AttributeRealKind GetAttributeRealKind
		(
			IXPAttributeSuite::AttributeType type
		) = 0;

	/** Returns the unit type associated with the given attribute (a real number attribute in 
		all cases).  If the attribute has no unit type (e.g., opacity), returns -1.  (Because
		ScriptData::UnitType has no 'invalid' value, unfortunately.)

		@param attrType IN The attribute.
		@return The unit type, or ((ScriptData::UnitType)-1) if no units associted with the attr.
	*/
	virtual ScriptData::UnitType GetAttributeUnits
		(
			IXPAttributeSuite::AttributeType type
		) = 0;

	/** Creates a IGraphicStyleAttributeBossList attribute list from an AttributeList.

		@param attrList IN The attribute list.
		@return A refcounted boss list.
	*/
	virtual IGraphicStyleAttributeBossList* CreateAttrBossListFromAttrList
		(
			const IXPAttributeSuite::AttributeList& attrList
		) = 0;

	/** Creates a IGraphicStyleAttributeBossList attribute list from an AttributeList.

		@param iBossList IN The attribute list.
		@param attrList OUT The converted attribute list.
	*/
	virtual bool16 GetAttrListFromAttrBossList
		(
			const IGraphicStyleAttributeBossList* iBossList,
			IXPAttributeSuite::AttributeList& attrList
		) = 0;

	/** Translates an attribute type/value into a string.  The type and database are needed
		to handle specific formatting needs for real values and colors, respectively.


	*/
	virtual bool16 GetValueAsString
		(
			IXPAttributeSuite::AttributeType type, 
			const IXPAttributeSuite::AttributeValue& val,
			IDataBase* db,
			PMString& s
		) = 0;

	//________________________________________________________________________________
	// Enumeration utilities
	//________________________________________________________________________________
	
	/** Returns the number of attribute targets.  Yes, you could figure this out just by looking at
		the enumeration, but this allows you to write code that will still work if we ever add any 
		new targets in the future.
		
		@return The number of attribute targets.
	*/
	virtual int32 GetNumAttributeTargets() = 0;
	
	/** Given an index, returns the associated attribute target.
	
		@param n IN The index, between 0 and GetNumAttributeTargets.
		@return An attribute target, or IXPAttributeSuite::kTargetInvalid if n is out of range.
	*/
	virtual IXPAttributeSuite::AttributeTarget GetNthAttributeTarget
		(
			int32 n
		) = 0;

	/** Given an attribute target, returns the associated index.
	
		@param target IN An attribute target.
		@return The zero-based index of the target, or -1 if the target was invalid.
	*/
	virtual int32 GetAttributeTargetIndex
		(
			IXPAttributeSuite::AttributeTarget
		) = 0;

	/** Returns the number of attribute groups.  Yes, you could figure this out just by looking at
		the enumeration, but this allows you to write code that will still work if we ever add any 
		new groups in the future.
		
		@return The number of attribute groups per target.
	*/
	virtual int32 GetNumAttributeGroups() = 0;
	
	/** Given an index, returns the associated attribute group.
	
		@param n IN The index, between 0 and GetNumAttributeGroups.
		@return An attribute group, or IXPAttributeSuite::kGroupInvalid if n is out of range.
	*/
	virtual IXPAttributeSuite::AttributeGroup GetNthAttributeGroup
		(
			int32 n
		) = 0;

	/** Given an attribute group, returns the associated index.
	
		@param group IN An attribute group.
		@return The zero-based index of the group, or -1 if the group was invalid.
	*/
	virtual int32 GetAttributeGroupIndex
		(
			IXPAttributeSuite::AttributeGroup
		) = 0;

	//________________________________________________________________________________
	// Scripting utilities
	//________________________________________________________________________________
	
	/** Given an attribute type/value combination, creates a corresponding ScriptData,
		and/or returns the script ID, and/or returns the element ID.  The latter two
		are simple lookups.  The value conversion takes into account the enum-to-script
		space conversion, but does *not* check for valid value ranges.

		@param attrType			IN	The attribute type.
		@param attrValue		IN	The attribute value (must be a compatible DataType).
		@param iDataBase		IN	The database for swatch inflation.  Either this or iScript is required if pScriptData != nil.
		@param iScript			IN	The script interface.  Either this or db is required iff pScriptData != nil.
		@param scriptVersion	IN	The script event data
		@param pScriptData		OUT If not nil, receives the scriptData to use for the attribute in a scripting context.
		@param pElementID		OUT If not nil, receives the script element ID corresponding to the attribute.
		@param pScriptID		OUT If not nil, receives the script ID corresponding to the attribute.
		@return kTrue if successful, kFalse if not.  Will only fail if the attrType is invalid or
				the associated value is of an incorrect type.  And it'll only fail if the value is
				the wrong type if pScriptData is not nil.
	*/
	virtual bool16 GetAttributeScriptInfo
		(
			IXPAttributeSuite::AttributeType attrType,
			const IXPAttributeSuite::AttributeValue& attrValue,
			IDataBase* iDataBase,
			IScript* iScript,
			IScriptRequestData* data,
			ScriptData* pScriptData,
			ScriptElementID* pElementID,
			ScriptID* pScriptID
		) = 0;

	/**	Given a script ID and an optional target/group, looks up the corresponding attribute.
		Note that the target and group are only optional if you want a "legacy" lookup -- that
		is, a lookup for the script attributes (now only INX attributes) that sit on the page
		item boss itself.  All of the new attributes sit in the hierarchy and require the 
		target and group to 'localize' the property to the correct attribute.

		@param target IN The target to localize to, or kTargetInvalid if you want a legacy lookup.
		@param target IN The group to localize to, or kGroupInvalid if you want a legacy lookup.
		@param propID IN The script property ID to look up.
		@return Attribute type, or kUnknownAttrType if no associated type.
		@see GetAttributeScriptInfo for looking up script info from attribute type.
	*/
	virtual IXPAttributeSuite::AttributeType GetAttributeFromScriptID
		(
			IXPAttributeSuite::AttributeTarget target,
			IXPAttributeSuite::AttributeGroup group,
			ScriptID propID
		) = 0;

	/** Looks up scripting information based on a script request (property ID and iScript object).
		From these two inputs, determines the target, group, and attribute type, as appropriate.
		If the property corresponds to a first-tier (item, stroke, fill, content) object or property,
		returns the target and leaves group/type as invalid.  If the property corresponds to a
		second-tier (blending, drop shadow, etc) property or object, returns the target and group
		and leaves 'type' invalid.  If the property corresponds to any transparency property anywhere
		in the hierarchy, returns 'type' as valid and sets up the target.  If the property is in 
		the hierarchy, also returns 'group', although you could derive that from the attribute.

		@param propID IN The property ID.
		@param iScript IN The scripting object on which the property lives.
		@param target OUT Receives the target, or kTargetInvalid if we found no match for the property (error).
		@param group OUT Receives the group, or kGroupInvalid if the property is a legacy property on the page item.
		@param type OUT Receives the attribute, or kUnknownAttrType if the property isn't an attribute-level property.
	*/

	virtual void LookupScriptInfo
		(
			IScriptRequestData* data,
			ScriptID propID, 
			IScript* iScript, 
			IXPAttributeSuite::AttributeTarget& target, 
			IXPAttributeSuite::AttributeGroup &group,
			IXPAttributeSuite::AttributeType &type
		) = 0;

	/** Given a script 'set' request, translate into a resulting attribute type and value.
		
		@param iScript IN The IScript interface from the setter.
		@param propID IN The property ID to set.
		@param data IN The data to set.
		@param attr OUT Receives the type and value.
		@return Error code (kSuccess if successful).
	*/
	virtual ErrorCode GetAttributeDataFromScriptData
		(
			IScript*			iScript,
			const ScriptID&		propID,
			IScriptRequestData*	data,
			IXPAttributeSuite::AttributeTypeAndValue& attr
		) = 0;

	/** Translate scriptData into a resulting attribute type and value.
		
		@param scriptData IN The script data to translate.
		@param data IN The data to set.
		@param attrType IN The AttributeType which script data will be translated to.
		@param attr OUT Receives the type and value.
		@return Error code (kSuccess if successful).
	*/
	virtual ErrorCode GetAttributeDataFromScriptData
		(
			const ScriptData&	scriptData,
			IScriptRequestData*	data,
			const IXPAttributeSuite::AttributeType& attrType,
			IXPAttributeSuite::AttributeTypeAndValue& attr
		) = 0;

	/** Given a scripting ID (either property or object), return the associated target.  For example,
		passing p_XPPageItemSettings will return IXPAttributeSuite::kTargetPageItem; passing 
		c_StrokeTransparencySettings will return IXPAttributeSuite::kTargetStroke.
		
		@param id IN The ID to match against known target script IDs (objects or properties)
		@return The corresponding target, or IXPAttributeSuite::kTargetInvalid if the script ID doesn't match any.
	*/
	virtual IXPAttributeSuite::AttributeTarget GetTargetFromScriptID(ScriptID id) = 0;

	/** Given a scripting ID (either property or object), return the associated group.  For example,
		passing p_XPBlendingSettings will return IXPAttributeSuite::kGroupBlending; passing 
		c_FeatherSettings will return IXPAttributeSuite::kGroupFeather.
		
		@param id IN The ID to match against known group script IDs (objects or properties)
		@return The corresponding group, or IXPAttributeSuite::kGroupInvalid if the script ID doesn't match any.
	*/
	virtual IXPAttributeSuite::AttributeGroup GetGroupFromScriptID(ScriptID id) = 0;

	//________________________________________________________________________________

	//________________________________________________________________________________________
	// [ Generic Attribute Utilites (not attribute-specific) ]
	//________________________________________________________________________________________

	/**	Get the attribute value from the graphic style descriptor
		@param attrType			Indicates which attribute to get.
		@param attrValue		Receives the attribute value.
		@param styleDescriptor	The graphic style descriptor to pull the value from.
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetAttributeValue
		(
		IXPAttributeSuite::AttributeType attrType,
		IXPAttributeSuite::AttributeValue& attrValue,
		const IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Get the attribute value from a graphics attribute boss.
		@param attrType		Indicates which attribute to get.
		@param iAttr		The attribute boss from which you're pulling the value.
		@param attrValue	Receives the attribute value.
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  GetAttributeValue
		(
		IXPAttributeSuite::AttributeType attrType,
		IXPAttributeSuite::AttributeValue& attrValue,
		const IPMUnknown* iAttr
		) = 0;
		
	/**	Create and return a graphic attribute with the specified value.

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The new attribute.
	*/
	virtual IPMUnknown* CreateAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return a graphic attribute with the specified value.

		@param attr		The attribute type and value to create.
		@return The new attribute.
	*/
	virtual IPMUnknown* CreateAttribute
		(
		const IXPAttributeSuite::AttributeTypeAndValue& attr
		) = 0;
		
	/**	Create and return a RealNumber graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not Real.

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateRealNumberAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return a Boolean graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not boolean.

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IGraphicAttrBoolean* to the new attribute.
	*/
	virtual IGraphicAttrBoolean * CreateBooleanAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return a UID (color) graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not UID-based.

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IPersistUIDData* CreateUIDAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return a int32 graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not int32-based (including enums).

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IGraphicAttrInt32* to the new attribute.
	*/
	virtual IGraphicAttrInt32 * CreateInt32Attribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return an OpacityGradientStops graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not opacity gradient-based (including enums).

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IOpacityGradientStops* to the new attribute.
	*/
	virtual IOpacityGradientStops * CreateOpacityGradientStopsAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and return a PMPoint graphic attribute with the specified value.
		Note that because graphic attributes are not inherited from a common base
		(other than IPMUnknown) we need different Create methods for each of the 
		basic storage types, if you want type safety. 
		This method will fail if the attribute type is not PMPoint-based (including enums).

		@param attrType		The attribute type to create.
		@param attrValue	The value to use for the new attribute.
		@return The IGraphicAttrPoint* to the new attribute.
	*/
	virtual IGraphicAttrPoint * CreatePointAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue
		) = 0;
		
	/**	Create and add an attribute to the specified attribute list.
		@param attrType			The attribute type to add.
		@param attrValue		The value of the attribute.
		@param attributeList	The attribute list to which to add the attribute.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode  AddAttribute
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& attrValue,
		IGraphicStyleAttributeBossList* attributeList
		) = 0;
		
	/**	Create attribute command to apply to the specified page item list.
		@param noise the feather noise to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return The apply attribute command or nil.
	*/
	virtual ICommand* CreateApplyAttributeCommand 
		(
		IXPAttributeSuite::AttributeType attrType,
		const IXPAttributeSuite::AttributeValue& val,
		const UIDList* targetItemList,
		bool16 doPrePost,
		bool16 enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	//  Opacity Gradient Utilities
	//________________________________________________________________________________________

	/** Makes a copy of the specified opacity gradient stops as a lightweight in-memory object.
		This is typically used to modify an existing opacity gradient; ie you make a copy of
		it, change the copy, then use that in a SetAttributes command.
		
		@param iStops IN The gradient stops you want to copy.
		@return A refcounted in-memory copy of the source gradient, or nil if there was an error.
	*/
	
	virtual IOpacityGradientStops* CloneOpacityGradientStops(const IOpacityGradientStops* iStops) = 0;

	//________________________________________________________________________________________
	// Attribute-Specific Utilities
	//	These are largely deprecated because maintaining per-attribute methods is untenable
	//	given the number of different transparency attributes.  For new code use the above
	//	methods.
	//________________________________________________________________________________________

	//________________________________________________________________________________________
	// [ Basic Blend Mode]
	//________________________________________________________________________________________

	/**	Get the basic blending mode from the graphic style descriptor
		@param blendMode the blending mode to get. This is a PMBlendingMode.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
		@see GraphicTypes.h.
	*/
	virtual  ErrorCode  GetBasicBlendMode 
		(
		PMBlendingMode&				blendMode,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/**	Create and return a blend mode attribute with the specified blend mode.
		@param blendMode the blending mdoe to create. This is a PMBlendingMode.
		@return the IGraphicAttrInt32* to the new blend mode attribute.
		@See GraphicTypes.h
	*/
	virtual  IGraphicAttrInt32* CreateBasicBlendModeAttribute
		(
		PMBlendingMode			blendMode
		) = 0;

	/**	Create and add a blend mode attribute to the specified attribute list.
		@param blendMode the blending mdoe to add. This is a PMBlendingMode.
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
		@See GraphicTypes.h
	*/
	virtual  ErrorCode  AddBasicBlendModeAttribute
		(
		PMBlendingMode						blendMode,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;

	/**	Create blend mode attribute command to apply to the specified page item list.
		@param blendMode the blending mdoe to apply. This is a PMBlendingMode.
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
		@See GraphicTypes.h
	*/
	virtual ICommand* CreateBasicBlendModeCommand 
		(
		PMBlendingMode				blendMode,
		const UIDList*				targetItemList,
		bool16						doPrePost,
		bool16						enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Basic Opacity ]
	//________________________________________________________________________________________

	/**	Get the basic opacity from the graphic style descriptor
		@param opacity the basic opacity to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual  ErrorCode  GetBasicOpacity 
		(
		PMReal&						opacity,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/**	Create and return a attribute with the specified opacity value.
		@param opacity the basic opacity to create
		@return the IGraphicAttrRealNumber* to the new opacity attribute.
	*/
	virtual  IGraphicAttrRealNumber * CreateBasicOpacityAttribute
		(
		PMReal		opacity
		) = 0;

	/**	Create and add a opacity attribute to the specified attribute list.
		@param opacity the basic opacity to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual  ErrorCode  AddBasicOpacityAttribute
		(
		PMReal								opacity,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create opacity attribute command to apply to the specified page item list.
		@param opacity the basic opacity to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateBasicOpacityCommand 
		(
		PMReal				opacity,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Basic Knockout Group ]
	//________________________________________________________________________________________

	/**	Get the knockout group setting from the graphic style descriptor
		@param basicKnockoutGrouop the knockout group setting to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual  ErrorCode  GetBasicKnockoutGroup 
		(
		bool16&						basicKnockoutGrouop,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/**	Create and return a attribute with the specified knockout group setting.
		@param basicKnockoutGrouop the knockout group setting to create
		@return the IGraphicAttrBoolean* to the new attribute.
	*/
	virtual  IGraphicAttrBoolean * CreateBasicKnockoutGroupAttribute
		(
		bool16		basicKnockoutGrouop
		) = 0;

	/**	Create and add a knockout group attribute to the specified attribute list.
		@param basicKnockoutGrouop the knockout group setting to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual  ErrorCode  AddBasicKnockoutGroupAttribute
		(
		bool16								basicKnockoutGrouop,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;

	/**	Create knockout group attribute command to apply to the specified page item list.
		@param basicKnockoutGrouop the knockout group setting to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateBasicKnockoutGroupCommand 
		(
		bool16				opacity,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Basic Isolation Group ]
	//________________________________________________________________________________________

	/**	Get the isolation setting from the graphic style descriptor
		@param isolation the isolation setting to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual  ErrorCode  GetBasicIsolationGroup
		(
		bool16&						basicIsolationGrouop,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/**	Create and return a attribute with the specified isolation setting.
		@param basicIsolationGroup the isolation setting to create
		@return the IGraphicAttrBoolean* to the new attribute.
	*/
	virtual  IGraphicAttrBoolean * CreateBasicIsolationGroupAttribute
		(
		bool16						basicIsolationGrouop
		) = 0;

	/**	Create and add a isolation attribute to the specified attribute list.
		@param basicIsolationGroup the isolation setting to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual  ErrorCode  AddBasicIsolationGroupAttribute
		(
		bool16								basicIsolationGroup,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;

	/**	Create isolation attribute command to apply to the specified page item list.
		@param basicIsolationGroup the isolation setting to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateBasicIsolationGroupCommand 
		(
		bool16				basicIsolationGroup,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ DropShadow Mode ]
	//________________________________________________________________________________________

	/**	Get the drop shadow apply setting from the graphic style descriptor
		@param dropShadowMode the drop shadow apply setting to get. This is a PMDropShadowMode.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
		@see GraphicTypes.h.
	*/
	virtual  ErrorCode  GetDropShadowMode
		(
		PMDropShadowMode&			dropShadowMode,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/**	Create and return a attribute with the specified drop shadow apply setting.
		@param dropShadowMode the drop shadow apply setting to create. This is a PMDropShadowMode.
		@return the IGraphicAttrInt32* to the new attribute.
		@see GraphicTypes.h.
	*/
	virtual  IGraphicAttrInt32 * CreateDropShadowModeAttribute
		(
		PMDropShadowMode		dropShadowMode
		) = 0;
		
	/**	Create and add a drop shadow apply attribute to the specified attribute list.
		@param dropShadowMode the drop shadow apply setting to add. This is a PMDropShadowMode.
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
		@see GraphicTypes.h.
	*/
	virtual  ErrorCode  AddDropShadowModeAttribute
		(
		PMDropShadowMode					dropShadowMode,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create rop shadow apply attribute command to apply to the specified page item list.
		@param dropShadowMode the drop shadow apply setting to apply. This is a PMDropShadowMode.
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateDropShadowModeCommand 
		(
		PMDropShadowMode	dropShadowMode,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ DropShadow Blend Mode ]
	//________________________________________________________________________________________

	/**	Get the drop shadow blend mode from the graphic style descriptor
		@param blendMode the drop shadow blend mode to get.  This is a PMBlendingMode.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
		@See GraphicTypes.h
	*/
	virtual  ErrorCode  GetDropShadowBlendMode
		(
		PMBlendingMode&				blendMode,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow blend mode.
		@param blendMode the drop shadow blend mode to create. This is a PMBlendingMode.
		@return the IGraphicAttrInt32* to the new attribute.
		@See GraphicTypes.h
	*/
	virtual  IGraphicAttrInt32 * CreateDropShadowBlendModeAttribute
		(
		PMBlendingMode		blendMode
		) = 0;
		
	/**	Create and add a drop shadow blend mode attribute to the specified attribute list.
		@param blendMode the drop shadow blend mode to add.  This is a PMBlendingMode.
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
		@See GraphicTypes.h
	*/
	virtual  ErrorCode  AddDropShadowBlendModeAttribute
		(
		PMBlendingMode						blendMode,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create rop shadow blend mode attribute command to apply to the specified page item list.
		@param blendMode the drop shadow blend mode to apply.  This is a PMBlendingMode.
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
		@See GraphicTypes.h
	*/
	virtual ICommand* CreateDropShadowBlendModeCommand 
		(
		PMBlendingMode		blendMode,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ DropShadow Opacity ]
	//________________________________________________________________________________________

	/**	Get the drop shadow opacity from the graphic style descriptor
		@param opacity the drop shadow opacity to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowOpacity
		(
		PMReal&						opacity,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow opacity.
		@param opacity the drop shadow opacity to cereate
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowOpacityAttribute
		(
		PMReal						opacity
		) = 0;
		
	/**	Create and add a drop shadow opacity attribute to the specified attribute list.
		@param opacity the drop shadow opacity to get
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowOpacityAttribute
		(
		PMReal								opacity,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create rop shadow opacity attribute command to apply to the specified page item list.
		@param opacity the drop shadow opacity to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowOpacityCommand 
		(
		PMReal				opacity,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ DropShadow X Offset ]
	//________________________________________________________________________________________

	/**	Get the drop shadow x offset from the graphic style descriptor
		@param dropShadowOffsetX the drop shadow x offset to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowOffsetX
		(
		PMReal&						dropShadowOffsetX,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow x offset.
		@param dropShadowOffsetX the drop shadow x offset to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowOffsetXAttribute
		(
		PMReal		dropShadowOffsetX
		) = 0;
		
	/**	Create and add a drop shadow x offset attribute to the specified attribute list.
		@param dropShadowOffsetX the drop shadow x offset to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowOffsetXAttribute
		(
		PMReal								dropShadowOffsetX,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create rop shadow x offset attribute command to apply to the specified page item list.
		@param dropShadowOffsetX the drop shadow x offset to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowOffsetXCommand 
		(
		PMReal				dropShadowOffsetX,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Drop Shadow Y Offset ]
	//________________________________________________________________________________________

	/**	Get the drop shadow y offset from the graphic style descriptor
		@param dropShadowOffsetY the drop shadow y offset to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowOffsetY
		(
		PMReal&						dropShadowOffsetY,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow y offset.
		@param dropShadowOffsetY the drop shadow y offset to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowOffsetYAttribute
		(
		PMReal		dropShadowOffsetY
		) = 0;
		
	/**	Create and add a drop shadow y offset attribute to the specified attribute list.
		@param dropShadowOffsetY the drop shadow y offset to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowOffsetYAttribute
		(
		PMReal								dropShadowOffsetY,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create drop shadow y offset attribute command to apply to the specified page item list.
		@param dropShadowOffsetY the drop shadow y offset to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowOffsetYCommand 
		(
		PMReal				dropShadowOffsetY,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Drop Shadow Blur Radius ]
	//________________________________________________________________________________________

	/**	Get the drop shadow blur radius from the graphic style descriptor
		@param blurRadius the drop shadow blur radius to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowBlurRadius
		(
		PMReal&						blurRadius,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow blur radius.
		@param blurRadius the drop shadow blur radius to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowBlurRadiusAttribute
		(
		PMReal		blurRadius
		) = 0;
		
	/**	Create and add a drop shadow blur radius attribute to the specified attribute list.
		@param blurRadius the drop shadow blur radius to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowBlurRadiusAttribute
		(
		PMReal								blurRadius,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create drop shadow blur radius attribute command to apply to the specified page item list.
		@param blurRadius the drop shadow blur radius to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowBlurRadiusCommand 
		(
		PMReal				blurRadius,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
		

	//________________________________________________________________________________________
	// [ Drop Shadow Color]
	//________________________________________________________________________________________

	/**	Get the drop shadow color UID from the graphic style descriptor
		@param colorUID the drop shadow color UID to get. This must be an UID of a kPMColorBoss.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowColorUID
		(
		UID&						colorUID,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow color UID.
		@param colorUID the drop shadow color UID to Create. This must be an UID of a kPMColorBoss.
		@return the IPersistUIDRefData* to the new attribute.
	*/
	virtual IPersistUIDData* CreateDropShadowColorAttribute
		(
		IDataBase*	iDataBase,
		UID			colorUID
		) = 0;
		
	/**	Create and add a drop shadow color UID attribute to the specified attribute list.
		@param colorUID the drop shadow color UID to add. This must be an UID of a kPMColorBoss.
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowColorAttribute
		(
		IDataBase*							iDataBase,
		UID									colorUID,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create drop shadow color UID attribute command to apply to the specified page item list.
		@param colorUID the drop shadow color UID to apply. This must be an UID of a kPMColorBoss.
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowColorCommand 
		(
		const UIDRef&		colorRef,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Drop Shadow Spread ]
	//________________________________________________________________________________________

	/**	Get the drop shadow spread from the graphic style descriptor
		@param spread the drop shadow spread to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowSpread
		(
		PMReal&						spread,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow spread.
		@param spread the drop shadow spread to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowSpreadAttribute
		(
		PMReal		spread
		) = 0;
		
	/**	Create and add a drop shadow spread attribute to the specified attribute list.
		@param spread the drop shadow spread to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowSpreadAttribute
		(
		PMReal								spread,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create drop shadow spread attribute command to apply to the specified page item list.
		@param spread the drop shadow spread to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowSpreadCommand 
		(
		PMReal				spread,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
		

	//________________________________________________________________________________________
	// [ Drop Shadow Noise ]
	//________________________________________________________________________________________

	/**	Get the drop shadow noise from the graphic style descriptor
		@param noise the drop shadow noise to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetDropShadowNoise
		(
		PMReal&						noise,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified drop shadow noise.
		@param noise the drop shadow noise to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateDropShadowNoiseAttribute
		(
		PMReal		noise
		) = 0;
		
	/**	Create and add a drop shadow noise attribute to the specified attribute list.
		@param noise the drop shadow noise to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddDropShadowNoiseAttribute
		(
		PMReal								noise,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create drop shadow noise attribute command to apply to the specified page item list.
		@param noise the drop shadow noise to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateDropShadowNoiseCommand 
		(
		PMReal				noise,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
		

	//________________________________________________________________________________________
	// [ Vignette Mode ]
	//________________________________________________________________________________________

	/**	Get the feather apply setting from the graphic style descriptor
		@param vignetteMode the feather apply setting to get. This is a PMVignetteMode.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
		@see GraphicTypes.h.
	*/
	virtual ErrorCode  GetVignetteMode
		(
		PMVignetteMode&				vignetteMode,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather apply setting.
		@param vignetteMode the feather apply setting to create
		@return the IGraphicAttrInt32* to the new attribute.
		@see GraphicTypes.h.
	*/
	virtual IGraphicAttrInt32 * CreateVignetteModeAttribute
		(
		PMVignetteMode			vignetteMode
		) = 0;
		
	/**	Create and add a feather apply attribute to the specified attribute list.
		@param vignetteMode the feather apply setting to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
		@see GraphicTypes.h.
	*/
	virtual ErrorCode  AddVignetteModeAttribute
		(
		PMVignetteMode						vignetteMode,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather apply setting attribute command to apply to the specified page item list.
		@param vignetteMode the feather apply setting to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateVignetteModeCommand 
		(
		PMVignetteMode		vignetteMode,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
		

	//________________________________________________________________________________________
	// [ Vignette Width ]
	//________________________________________________________________________________________

	/**	Get the feather width from the graphic style descriptor
		@param width the feather width to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetVignetteWidth
		(
		PMReal&						width,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather width.
		@param width the feather width to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateVignetteWidthAttribute
		(
		PMReal						width
		) = 0;
		
	/**	Create and add a feather width attribute to the specified attribute list.
		@param width the feather width to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddVignetteWidthAttribute
		(
		PMReal								width,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather width attribute command to apply to the specified page item list.
		@param width the feather width to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateVignetteWidthCommand 
		(
		PMReal				width,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Vignette Outer Opacity ]
	//________________________________________________________________________________________

	/**	Get the feather outer opacity from the graphic style descriptor
		@param outerOpacity the feather outer opacity to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetVignetteOuterOpacity 
		(
		PMReal&						outerOpacity,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather outer opacity.
		@param outerOpacity the feather outer opacity to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateVignetteOuterOpacityAttribute
		(
		PMReal		outerOpacity
		) = 0;
		
	/**	Create and add a feather outer opacity attribute to the specified attribute list.
		@param outerOpacity the feather outer opacity to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddVignetteOuterOpacityAttribute
		(
		PMReal								outerOpacity,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather outer opacity attribute command to apply to the specified page item list.
		@param outerOpacity the feather outer opacity to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateVignetteOuterOpacityCommand 
		(
		PMReal				outerOpacity,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Vignette Inner Opacity ]
	//________________________________________________________________________________________

	/**	Get the feather inner opacity from the graphic style descriptor
		@param innerOpacity the feather inner opacity to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetVignetteInnerOpacity 
		(
		PMReal&						innerOpacity,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather inner opacity.
		@param innerOpacity the feather inner opacity to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateVignetteInnerOpacityAttribute
		(
		PMReal		innerOpacity
		) = 0;
		
	/**	Create and add a feather inner opacity attribute to the specified attribute list.
		@param innerOpacity the feather inner opacity to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddVignetteInnerOpacityAttribute
		(
		PMReal								innerOpacity,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather inner opacity attribute command to apply to the specified page item list.
		@param innerOpacity the feather inner opacity to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateVignetteInnerOpacityCommand 
		(
		PMReal				innerOpacity,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Vignette Corners ]
	//________________________________________________________________________________________

	/**	Get the feather corner type from the graphic style descriptor
		@param corners the feather corner type to get. This is a PMVignetteCorners.
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
		@see GraphicTypes.h.
	*/
	virtual ErrorCode  GetVignetteCorners 
		(
		PMVignetteCorners&			corners,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather corner type.
		@param corners the feather corner type to create. This is a PMVignetteCorners.
		@return the IGraphicAttrInt32* to the new attribute.
		@see GraphicTypes.h.
	*/
	virtual IGraphicAttrInt32* CreateVignetteCornersAttribute
		(
		PMVignetteCorners			corners
		) = 0;
		
	/**	Create and add a feather corner type attribute to the specified attribute list.
		@param corners the feather corner type to add. This is a PMVignetteCorners.
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
		@see GraphicTypes.h.
	*/
	virtual ErrorCode  AddVignetteCornersAttribute
		(
		PMVignetteCorners					corners,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather corner type attribute command to apply to the specified page item list.
		@param corners the feather corner type to apply. This is a PMVignetteCorners.
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateVignetteCornersCommand 
		(
		PMVignetteCorners	corners,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	//________________________________________________________________________________________
	// [ Vignette Noise ]
	//________________________________________________________________________________________

	/**	Get the feather noise from the graphic style descriptor
		@param noise the feather noise to get
		@param styleDescriptor the graphic style descriptor
		@return kSuccess if successful or returns an error code
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode  GetVignetteNoise 
		(
		PMReal&						noise,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/**	Create and return a attribute with the specified feather noise.
		@param noise the feather noise to create
		@return the IGraphicAttrRealNumber* to the new attribute.
	*/
	virtual IGraphicAttrRealNumber * CreateVignetteNoiseAttribute
		(
		PMReal		noise
		) = 0;
		
	/**	Create and add a feather noise attribute to the specified attribute list.
		@param noise the feather noise to add
		@param attributeList the attribute list
		@return kSuccess if successful or returns an error code
	*/
	virtual ErrorCode  AddVignetteNoiseAttribute
		(
		PMReal								noise,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;
		
	/**	Create feather noise attribute command to apply to the specified page item list.
		@param noise the feather noise to apply
		@param targetItemList the target page item list
		@param doPrePost kTrue if to perform attribute pre/post actions.
		@param enableDoNotify kTrue if notification should be sent.
		@return the apply attribute command or nil.
	*/
	virtual ICommand* CreateVignetteNoiseCommand 
		(
		PMReal				noise,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;



	//________________________________________________________________________________________

	/**	Return the scripting blending mode given the InDesign blending mode.
		@param mode the InDesign blending mode.
	*/
	virtual ScriptID			GetScriptEnumFromBlendMode (PMBlendingMode mode) = 0;
	/**	Return the InDesign blending mode given the scripting blending mode.
		@param asEnum the scripting blending mode.
	*/
	virtual PMBlendingMode 		GetBlendModeFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting drop shadow mode given the InDesign drop shadow mode.
		@param mode the InDesign drop shadow mode.
	*/
	virtual ScriptID			GetScriptEnumFromDSMode (PMDropShadowMode mode) = 0;
	/**	Return the InDesign drop shadow mode given the scripting drop shadow mode.
		@param asEnum the scripting blending mode.
	*/
	virtual PMDropShadowMode	GetDSModeFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting feather mode given the InDesign feather mode.
		@param mode the InDesign feather mode.
	*/
	virtual ScriptID			GetScriptEnumFromVignetteMode (PMVignetteMode mode) = 0;
	/**	Return the InDesign feather mode given the scripting feather mode.
		@param asEnum the scripting feather mode.
	*/
	virtual PMVignetteMode		GetVignetteModeFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting feather corner type given the InDesign feather corner type.
		@param mode the InDesign blending mode.
	*/
	virtual ScriptID			GetScriptEnumFromCornerType (PMVignetteCorners mode) = 0;
	/**	Return the InDesign feather corner type given the scripting feather corner type.
		@param asEnum the scripting feather corner type.
	*/
	virtual PMVignetteCorners	GetCornerTypeFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting GlowTechnique given the InDesign PMGlowTechnique.
		@param glowTechnique the InDesign GlowTechnique.
	*/
	virtual ScriptID			GetScriptEnumFromGlowTechnique (PMGlowTechnique glowTechnique) = 0;
	/**	Return the InDesign PMGlowTechnique given the scripting GlowTechnique.
		@param asEnum the scripting GlowTechnique.
	*/
	virtual PMGlowTechnique		GetGlowTechniqueFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting InnerGlowSource given the InDesign PMInnerGlowSource.
		@param innerGlowSource the InDesign InnerGlowSource.
	*/
	virtual ScriptID			GetScriptEnumFromInnerGlowSource (PMInnerGlowSource innerGlowSource) = 0;
	/**	Return the InDesign PMInnerGlowSource given the scripting InnerGlowSource.
		@param asEnum the scripting InnerGlowSource.
	*/
	virtual PMInnerGlowSource	GetInnerGlowSourceFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting BevelEmbossStyle given the InDesign PMBevelEmbossStyle.
		@param bevelEmbossStyle the InDesign BevelEmbossStyle.
	*/
	virtual ScriptID			GetScriptEnumFromBevelEmbossStyle (PMBevelEmbossStyle bevelEmbossStyle) = 0;
	/**	Return the InDesign PMBevelEmbossStyle given the scripting BevelEmbossStyle.
		@param asEnum the scripting BevelEmbossStyle.
	*/
	virtual PMBevelEmbossStyle	GetBevelEmbossStyleFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting BevelEmbossTechnique given the InDesign PMBevelEmbossTechnique.
		@param bevelEmbossTechnique the InDesign BevelEmbossTechnique.
	*/
	virtual ScriptID			GetScriptEnumFromBevelEmbossTechnique (PMBevelEmbossTechnique bevelEmbossTechnique) = 0;
	/**	Return the InDesign PMBevelEmbossTechnique given the scripting BevelEmbossTechnique.
		@param asEnum the scripting BevelEmbossTechnique.
	*/
	virtual PMBevelEmbossTechnique	GetBevelEmbossTechniqueFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting BevelEmbossDirection given the InDesign PMBevelEmbossDirection.
		@param bevelEmbossDirection the InDesign BevelEmbossDirection.
	*/
	virtual ScriptID			GetScriptEnumFromBevelEmbossDirection (PMBevelEmbossDirection bevelEmbossDirection) = 0;
	/**	Return the InDesign PMBevelEmbossDirection given the scripting BevelEmbossDirection.
		@param asEnum the scripting BevelEmbossDirection.
	*/
	virtual PMBevelEmbossDirection	GetBevelEmbossDirectionFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting FollowShapeMode given the InDesign PMFollowShapeMode.
		@param FollowShapeMode the InDesign FollowShapeMode.
	*/
	virtual ScriptID			GetScriptEnumFromFollowShapeMode (PMFollowShapeMode followShapeMode) = 0;
	/**	Return the InDesign PMFollowShapeMode given the scripting FollowShapeMode.
		@param asEnum the scripting FollowShapeMode.
	*/
	virtual PMFollowShapeMode	GetFollowShapeModeFromScriptEnum (ScriptID asEnum) = 0;
	/**	Return the scripting GradientType given the InDesign GradientType.
		@param gradientType the InDesign GradientType.
	*/
	virtual ScriptID				GetScriptEnumFromGradientType (GradientType gradientType) = 0;
	/**	Return the InDesign GradientType given the scripting GradientType.
		@param asEnum the scripting GradientType.
	*/
	virtual GradientType			GetGradientTypeFromScriptEnum (ScriptID asEnum) = 0;
};

#endif	// __IXPAttributeUtils__
