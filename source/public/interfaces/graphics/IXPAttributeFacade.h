//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPAttributeFacade.h $
//  
//  Owner: SusanCL
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
//  TODO:	Add Get methods for each transparency attribute.
//  
//========================================================================================

#pragma once
#ifndef __IXPAttributeFacade__
#define __IXPAttributeFacade__
#include "IXPAttributeFacade.h"

#include "IPMUnknown.h"
#include "IXPAttributeSuite.h"
#include "IXPSetVignetteCmdData.h"
#include "IXPSetBasicAttributesCmdData.h"
#include "IXPSetDropShadowCmdData.h"
#include "GraphicTypes.h"
#include "K2Vector.h"
#include "Utils.h"

#include "XPID.h"

class IGraphicStyleAttributeBossList;
class AutomationContext;

/**	This is the high level transparency attribute facade.
	It defines methods to Get and Set all transparency attributes.
	It also defines methods for recording user action related to setting transparency attributes.
*/
class IXPAttributeFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPATTRIBUTEFACADE };
	
public:

	/**
		Set the blend mode property
		@param itemList the item list to apply.
		@param The blend mode used to combine the object's color with the background.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetBlendMode (const UIDList& itemList, PMBlendingMode blendMode) = 0;

	/**
		Get the blend mode property
		@param itemList the item list to get.
		@param The blend mode list of the items.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetBlendMode (const UIDList& itemList, K2Vector<int32>& blendModeList) = 0;
	
	/**
		Set the opacity property
		@param itemList the item list to apply.
		@param The opacity of the object.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetOpacity (const UIDList& itemList, PMReal opacity) = 0;
	
	/**
		Get the opacity property
		@param itemList the item list to get.
		@param The opacity list of the items.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetOpacity (const UIDList& itemList, K2Vector<PMReal>& opacityList) = 0;

	/**
		Set the knockout group property
		@param itemList the item list to apply.
		@param Indicates whether the object is a knockout group.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetKnockoutGroup(const UIDList& itemList, bool16 knockoutGroup) = 0;

	/**
		Get the knockout group property
		@param itemList the item list to get.
		@param knockout group list of the items.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetKnockoutGroup(const UIDList& itemList, K2Vector<bool16>& knockoutGroupList) = 0;

	/**
		Set the isolate blending property
		@param itemList the item list to apply.
		@param Indicates whether the object should blend in isolation.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetIsolateBlending (const UIDList& itemList, bool16 isolateBlending) = 0;

	/**
		Get the isolate blending property
		@param itemList the item list to get.
		@param isolation blendings of the items.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetIsolateBlending (const UIDList& itemList, K2Vector<bool16>& isolateBlendingList) = 0;

	/**
		Set the shadow mode property
		@param itemList the item list to apply.
		@param The shadow mode.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowMode (const UIDList& itemList, PMDropShadowMode shadowMode) = 0;
	
	/**
		Get the shadow mode property
		@param itemList the item list to get.
		@param The shadow mode list.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowMode (const UIDList& itemList, K2Vector<int32>& shadowModeList) = 0;

	/**
		Set the shadow blend mode property
		@param itemList the item list to apply.
		@param The blend mode to use for drawing the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowBlendMode(const UIDList& itemList, PMBlendingMode shadowBlendMode) = 0;

	/**
		Get the shadow blend mode property
		@param itemList the item list to get.
		@param The blend mode list for the items.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowBlendMode(const UIDList& itemList, K2Vector<int32>& shadowBlendModeList) = 0;

	/**
		Set the shadow x offset property
		The horizontal offset of the shadow
		@param itemList the item list to apply.
		@param The horizontal offset of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowXOffset (const UIDList& itemList, PMReal shadowXOffset) = 0;

	/**
		Get the shadow x offset property
		@param itemList the item list to get.
		@param The horizontal offset of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowXOffset (const UIDList& itemList, K2Vector<PMReal>& shadowXOffsetList) = 0;

	/**
		Set the shadow y offset property
		The vertical offset of the shadow
		@param itemList the item list to apply.
		@param The vertical offset of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowYOffset (const UIDList& itemList, PMReal shadowYOffset) = 0;

	/**
		Get the shadow y offset property
		@param itemList the item list to get.
		@param The vertical offset of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowYOffset (const UIDList& itemList, K2Vector<PMReal>& shadowYOffsetList) = 0;

	/**
		Set the shadow blur radius property
		The radius of the blur to apply to the shadow
		@param itemList the item list to apply.
		@param The radius of the blur to apply to the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowBlurRadius (const UIDList& itemList, PMReal shadowBlurRadius) = 0;

	/**
		Get the shadow blur radius property
		The radius of the blur to apply to the shadow
		@param itemList the item list to get.
		@param The radius of the blur.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowBlurRadius (const UIDList& itemList, K2Vector<PMReal>& shadowBlurRadiusList) = 0;

	/**
		Set the shadow color property
		The color to apply to the shadow
		@param itemList the item list to apply.
		@param The color to apply to the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowColor (const UIDList& itemList, UID shadowColor) = 0;

	/**
		Get the shadow color property
		@param itemList the item list to get.
		@param The color to apply to the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowColor (const UIDList& itemList, K2Vector<UID>& shadowColorList) = 0;

	/**
		Set the shadow opacity property
		The opacity of the shadow
		@param itemList the item list to apply.
		@param The opacity of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowOpacity (const UIDList& itemList, PMReal shadowOpacity) = 0;

	/**
		Get the shadow opacity property
		@param itemList the item list to get.
		@param The opacity of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowOpacity (const UIDList& itemList, K2Vector<PMReal>& shadowOpacityList) = 0;

	/**
		Set the shadow spread property
		The spread of the shadow
		@param itemList the item list to apply.
		@param The spread of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowSpread (const UIDList& itemList, PMReal shadowSpread) = 0;

	/**
		Get the shadow spread property
		@param itemList the item list to get.
		@param The spread of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowSpread (const UIDList& itemList, K2Vector<PMReal>& shadowSpreadList) = 0;

	/**
		Set the shadow noise property
		The noise of the shadow
		@param itemList the item list to apply.
		@param The noise of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetShadowNoise (const UIDList& itemList, PMReal shadowNoise) = 0;

	/**
		Get the shadow noise property
		@param itemList the item list to get.
		@param The noise of the shadow.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetShadowNoise (const UIDList& itemList, K2Vector<PMReal>& shadowNoiseList) = 0;

	/**
		Set the feather mode property
		The feather mode
		@param itemList the item list to apply.
		@param The feather mode.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherMode (const UIDList& itemList, PMVignetteMode featherMode) = 0;

	/**
		Get the feather mode property
		The feather mode
		@param itemList the item list to get.
		@param The feather mode.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherMode (const UIDList& itemList, K2Vector<int32>& featherModeList) = 0;

	/**
		Set the feather width property
		The width of the feathering
		@param itemList the item list to apply.
		@param The width of the feathering.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherWidth (const UIDList& itemList, PMReal featherWidth) = 0;

	/**
		Set the feather width property
		The width of the feathering
		@param itemList the item list to get.
		@param The width of the feathering.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherWidth (const UIDList& itemList, K2Vector<PMReal>& featherWidthList) = 0;

	/**
		Set the feather noise property
		The feather noise
		@param itemList the item list to apply.
		@param The feather noise.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherNoise (const UIDList& itemList, PMReal noise) = 0;

	/**
		get the feather noise property
		The feather noise
		@param itemList the item list to get.
		@param The feather noise.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherNoise (const UIDList& itemList, K2Vector<PMReal>& noiseList) = 0;

	/**
		Set the feather inner opacity property
		The feather inner opacity
		@param itemList the item list to apply.
		@param The feather inner opacity.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherInnerOpacity (const UIDList& itemList, PMReal featherInnerOpacity) = 0;

	/**
		Set the feather inner opacity property
		The feather inner opacity
		@param itemList the item list to get.
		@param The feather inner opacity.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherInnerOpacity (const UIDList& itemList, K2Vector<PMReal>& featherInnerOpacityList) = 0;

	/**
		Set the feather outer opacity property
		The feather outer opacity
		@param itemList the item list to apply.
		@param The feather outer opacity.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherOuterOpacity (const UIDList& itemList, PMReal featherOuterOpacity) = 0;

	/**
		Get the feather outer opacity property
		The feather outer opacity
		@param itemList the item list to get.
		@param The feather outer opacity.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherOuterOpacity (const UIDList& itemList, K2Vector<PMReal>& featherOuterOpacityList) = 0;

	/**
		Set the feather corner type property
		The type of feathering to apply
		@param itemList the item list to apply.
		@param The type of feathering to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	SetFeatherCornerType (const UIDList& itemList, PMVignetteCorners featherCornerType) = 0;

	/**
		Get the feather corner type property
		@param itemList the item list to get.
		@param The type of feathering.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	GetFeatherCornerType (const UIDList& itemList, K2Vector<int32>& featherCornerTypeList) = 0;

	/**	Apply the specified transparency attr list to the specified item list
		@param itemList the item list to apply.
		@param iAttrList the attribute list to apply. Only transparency attributes from the list are applied.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	ApplyAttributes	(const UIDList& itemList, IGraphicStyleAttributeBossList* iAttrList) = 0;

	/**	Apply the specified transparency attr list to the specified item list
		@param itemList the item list to apply.
		@param iAttrList the attribute list to apply.
		@return kSuccess if successful otherwise returns an error code.
	*/
	virtual ErrorCode	ApplyAttributes	(const UIDList& itemList, const IXPAttributeSuite::AttributeList& attrList) = 0;

	/**	Apply the spcified set of basic transparency attributes to the specified item list.
		Only those data specified by the attrTypeList are applied.
		@param itemList the item list to apply.
		@param basicData the basic transparency data
		@param attrTypeList the list of basic transparency attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	ApplyBasicAttributes
		(
			const UIDList& itemList, 
			BasicAttributesData* basicData, 
			const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList
		) = 0;

	/**	Apply the spcified set of drop shadow attributes to the specified item list
		Only those data specified by the attrTypeList are applied.
		@param itemList the item list to apply.
		@param dropshadowData the dropshadow data to apply
		@param attrTypeList the list of dropshadow attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	ApplyDropShadowAttributes	
		(
			const UIDList& itemList, 
			DropShadowData* dropshadowData, 
			const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList
		) = 0;
	/**	Apply the spcified set of feather attributes to the current selection.
		Only those data specified by the attrTypeList are applied.
		@param itemList the item list to apply.
		@param featherData the feather data
		@param attrTypeList the list of feather attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode ApplyVignetteAttributes
		(
			const UIDList& itemList, 
			VignetteData* featherData, 
			const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList
		) = 0;

	/**	Record the spcified list of transparency attributes.
		Only those data specified by the attrTypeList are recorded.
		@param pAutomationContext specifies the recording context
		@param iDataBase the database with which the attirubtes are recorded.
		@param iAttrList the list of transparency attribute types to record.
	*/
	virtual void RecordApplyAttributes
		(
			AutomationContext* pAutomationContext, 
			IDataBase* iDataBase, 
			IGraphicStyleAttributeBossList* iAttrList
		) = 0;

	/**	Record the spcified list of transparency attributes.
		Only those data specified by the attrTypeList are recorded.
		@param pAutomationContext specifies the recording context
		@param iDataBase the database with which the attirubtes are recorded.
		@param attrList The list of transparency attributes to record.
	*/
	virtual void RecordApplyAttributes
		(
			AutomationContext* pAutomationContext, 
			IDataBase* iDataBase, 
			const IXPAttributeSuite::AttributeList& attrList
		) = 0;

	/**	Record the spcified set of basic transparency attributes..
		Only those data specified by the attrTypeList are recorded.
		@param pAutomationContext specifies the recording context
		@param basicData the basic transparency data
		@param attrTypeList the list of basic transparency attribute types to record.
	*/
	virtual void RecordApplyBasicAttributes
		(
			AutomationContext* pAutomationContext, 
			BasicAttributesData* basicData, 
			const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList
		) = 0;

	/**	Record the spcified set of drop shadow attributes..
		Only those data specified by the attrTypeList are recorded.
		@param pAutomationContext specifies the recording context
		@param iDataBase the database with which the attirubtes are recorded.
		@param dropshadowData the dropshadow data to apply
		@param attrTypeList the list of dropshadow attribute types to record.
	*/
	virtual void		RecordApplyDropShadowAttributes	(AutomationContext* pAutomationContext, IDataBase*, DropShadowData* dropshadowData, const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList) = 0;

	/**	Record the spcified set of feather attributes.
		Only those data specified by the attrTypeList are recorded.
		@param pAutomationContext specifies the recording context
		@param featherData the feather data
		@param attrTypeList the list of feather attribute types to record.
	*/
	virtual void		RecordApplyVignetteAttributes	(AutomationContext* pAutomationContext, VignetteData* featherData, const K2Vector<IXPAttributeSuite::AttributeType>& attrTypeList) = 0;

};


#endif	// __IXPAttributeSuite__

