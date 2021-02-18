//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttributeUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IGraphicAttributeUtils__
#define __IGraphicAttributeUtils__


const PMReal kMinCornerRadius = 0;
const PMReal kMaxCornerRadius = 800;

const PMReal kMinMiterLimit = 1;
const PMReal kMaxMiterLimit = 500;
const PMReal kDefaultMiterLimit = 4;

const PMReal kMinStrokeWeight = 0;
const PMReal kMaxStrokeWeight = 800;

const PMReal kMinTintPercentage = 0;
const PMReal kMaxTintPercentage = 100;

const PMReal kMinGradientMidPointStop = 13;
const PMReal kMaxGradientMidPointStop = 87;

const PMReal kMinGradientStop = 0;
const PMReal kMaxGradientStop = 100;

const PMReal kMinOpacityPercentage = 0;
const PMReal kMaxOpacityPercentage = 100;

const PMReal kMinColorCMYKValue = 0;
const PMReal kMaxColorCMYKValue = 100;

const PMReal kMinColorLValue = 0;
const PMReal kMinColorAValue = -128;
const PMReal kMinColorBValue = -128;
const PMReal kMaxColorLValue = 100;
const PMReal kMaxColorAValue = 127;
const PMReal kMaxColorBValue = 127;

const PMReal kMinColorRGBValue = 0;
const PMReal kMaxColorRGBValue = 255;

const PMReal kMinColorHSBHValue = 0;
const PMReal kMinColorHSBSValue = 0;
const PMReal kMinColorHSBBValue = 0;
const PMReal kMaxColorHSBHValue = 360;
const PMReal kMaxColorHSBSValue = 100;
const PMReal kMaxColorHSBBValue = 100;


const PMReal kMinGradientAngleValue = -180;
const PMReal kMaxGradientAngleValue = 180;

const PMReal kDefaultStrokeWt = 1.0;
const PMReal kJDefaultStrokeWt = (0.1 / 25.4 * 72.0);	// 0.1 mm * 1 inch / 25.4 mm * 72 points / inch

const PMReal kDefaultCornerRadius = 12.0;
const PMReal kJDefaultCornerRadius = (5.0 / 25.4 * 72.0);	// 5 mm * 1 inch / 25.4 mm * 72 points / inch

const PMReal kMinArrowHeadScale = 1.0;
const PMReal kMaxArrowHeadScale = 1000.0;
const PMReal kDefaultArrowHeadScale = 100.0;

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "GraphicsID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "ShuksanID.h"
#include "UIDList.h"
#include "PMPoint.h"

class ICommand;
class IGraphicStyleDescriptor;
class IGraphicStyleAttributeBossList;
class IGraphicAttrRealNumber;
class IGraphicAttrClassID;
class IGraphicAttrBoolean;
class IGraphicAttrInt32;
class IPersistUIDData;
class IGraphicAttrPoint;
class IRenderingObject;


/** Graphic attribute related utility functions.

	Each attribute type has four methods:
	1.	Get__.
		Get the attribute value from the specified graphic style descriptor.
	2.	Create__Attribute.
		Create the attribute with the specified value and return a pointer to the attribute's
		persistent data interface.
	3.	Add__Attribute.
		Create and add the attribute with the specified value to the attribute list.
	4.	Create__Command.
		Create and return the apply attribute command given the attribute value and item list.
		The attribute command boss used is kGfxApplyAttrOverrideCmdBoss.
*/
class IGraphicAttributeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICATTRIBUTEUTILS };

	/** 
	Enumerates the different types of corners types available
	*/ 
	typedef enum  { 

		/** Simple Corner of any shape*/ 
		kSimpleCorner,

		/** Top Left Live Corner of the rectangle*/ 
		kLiveTopLeftCorner, 

		/** Top Right Live Corner of the rectangle */ 
		kLiveTopRightCorner, 

		/** Bottom Left Live Corner of the rectangle */ 
		kLiveBottomLeftCorner, 

		/** Bottom Right Live Corner of the rectangle*/ 
		kLiveBottomRightCorner, 
	}CornerType;




	/** Returns the stroke weight in the specified graphic style descriptor.
		@param strokeWeight the stroke weight to return.
		@param styleDescriptor the graphic style descriptor.
		@return kTrue if successful otherwise an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetStrokeWeight 
		(
		PMReal&							strokeWeight,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Returns the visible stroke weight in the specified graphic style descriptor.
		Stroke weight is 0 if the current stroke is [None].
		@param strokeWeight the visible stroke weight to return.
		@param styleDescriptor the graphic style descriptor. 
		@return kTrue if successful otherwise an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetVisibleStrokeWeight 
		(
		PMReal&							strokeWeight,
		IGraphicStyleDescriptor*		styleDescriptor
		) = 0;
		
	/** Creates and returns the stroke weight attribute.
		@param strokeWeight the stroke weight.
		@return the IGraphicAttrRealNumber pointer to the stroke weight attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateStrokeWeightAttribute
		(
		PMReal		strokeWeight
		) = 0;
		
	/** Creates and adds the stroke weight attribute to the specified attribute list.
		@param strokeWeight the stroke weight.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddStrokeWeightAttribute
		(
		PMReal							strokeWeight,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke weight attribute to the specified item list.
		@param strokeWeight the stroke weight.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateStrokeWeightCommand 
		(
		PMReal				strokeWeight,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// =============================================
// Gradient Fill Angle
// =============================================

	/** Returns the gradient fill angle in the specified graphic style descriptor.
		@param gradientAngle the gradient fill angle to return.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientFillAngle 
		(
		PMReal&							gradientAngle,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill angle attribute.
		@param gradientAngle the gradient fill angle to create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill angle attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientFillAngleAttribute
		(
		PMReal		gradientAngle
		) = 0;
		
	/** Creates and adds the gradient fill angle attribute to the specified attribute list.
		@param gradientAngle the gradient fill angle to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillAngleAttribute
		(
		PMReal							gradientAngle,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply fill gradient angle attribute to the specified item list.
		@param gradientAngle the gradient fill angle to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillAngleCommand 
		(
		PMReal				gradientAngle,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
    
   


// =============================================
// Gradient Stroke Angle
// =============================================

	/** Returns the gradient stroke angle in the specified graphic style descriptor.
		@param gradientAngle the gradient stroke angle to return.
		Gradient angle is always 0 for radial stroke gradient.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor
		
	*/
	virtual ErrorCode GetGradientStrokeAngle 
		(
		PMReal&						gradientAngle,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient stroke angle attribute.
		@param gradientAngle the gradient stroke angle to create.
		@return the IGraphicAttrRealNumber pointer to the gradient stroke angle attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientStrokeAngleAttribute
		(
		PMReal		gradientAngle
		) = 0;
		
	/** Creates and adds the gradient stroke angle attribute to the specified attribute list.
		@param gradientAngle the gradient stroke angle to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeAngleAttribute
		(
		PMReal							gradientAngle,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gradient angle attribute to the specified item list.
		@param gradientAngle the gradient stroke angle to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeAngleCommand 
		(
		PMReal				gradientAngle,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// =============================================
// Gradient Fill Length
// =============================================

	/** This method is umimplemented and will be removed.
	*/
	virtual ErrorCode GetGradientFillLength
		(
		PMReal&			gradientLength,
		UID				graphicStyleUID,
		IDataBase*		dataBase
		) = 0;

	/** Get the gradient fill length attribute.
		@param gradientLength the gradient fill length to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientFillLength 
		(
		PMReal&						gradientLength,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill length attribute.
		@param gradientLength the gradient fill length to create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill length attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientFillLengthAttribute
		(
		PMReal		gradientLength
		) = 0;
		
	/** Creates and adds the gradient fill length attribute to the specified attribute list.
		@param gradientLength the gradient fill length to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillLengthAttribute
		(
		PMReal							gradientLength,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient fill length attribute to the specified item list.
		@param gradientLength the gradient fill length to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillLengthCommand 
		(
		PMReal				gradientLength,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// =============================================
// Gradient Stroke Length
// =============================================

	/** Returns the gradient length for stroke in the specified graphic style descriptor.
		This attribute typically only exists if the stroke rendering attribute is a gradient.
		@param gradientLength the stroke gradient length to return.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor
		
	*/
	virtual ErrorCode GetGradientStrokeLength 
		(
		PMReal&							gradientLength,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the stroke gradient length attribute.
		The gradient length attribute for stroke is only relevant if stroke attribute is a gradient.
		@param gradientLength the stroke gradient stroke length to create.
		@return the IGraphicAttrRealNumber pointer to the stroke gradient length attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientStrokeLengthAttribute
		(
		PMReal		gradientLength
		) = 0;
		
	/** Creates and adds the gradient length attribute for stroke to the specified attribute list.
		@param gradientLength the stroke gradient length to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeLengthAttribute
		(
		PMReal							gradientLength,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gradient length attribute to the specified item list.
		@param gradientLength the stroke gradient length to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeLengthCommand 
		(
		PMReal				gradientLength,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// =============================================
// Gradient Fill Outer Center
// =============================================

	/** Get the gradient fill center or start point attribute.
		If gradient type is radial, this is the center point of the gradient and
		if gradient type is axial, this is the start point of the gradient.
		@param gradientGradCenter the gradient center of start point to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientFillGradCenter
		(
		PMPoint&						gradientGradCenter,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill center or start point attribute.
		@param gradientGradCenter the gradient fill center or start point to create.
		@return the IGraphicAttrPoint pointer to the gradient fill center or start point attribute.
	*/
	virtual IGraphicAttrPoint* CreateGradientFillGradCenterAttribute
		(
		PMPoint		gradientGradCenter
		) = 0;
		
	/** Creates and adds the gradient fill center or start point attribute to the specified attribute list.
		@param gradientGradCenter the gradient fill center or start point to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillGradCenterAttribute
		(
		PMPoint							gradientGradCenter,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient fill center of start point attribute to the specified item list.
		@param gradientGradCenter the gradient fill center or start point to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillGradCenterCommand 
		(
		PMPoint				gradientGradCenter,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

 
// =============================================
// Gradient Stroke Grad Center
// =============================================

	/** Get the gradient center or start point attribute for stroke.
		If gradient type is radial, this is the center point of the gradient and
		if gradient type is axial, this is the start point of the gradient.
		@param gradientGradCenter the gradient center of start point to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientStrokeGradCenter
		(
		PMPoint&						gradientGradCenter,
		IGraphicStyleDescriptor*		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient center or start point attribute for stroke.
		@param gradientGradCenter the gradient center or start point to create.
		@return the IGraphicAttrPoint pointer to the gradient center or start point attribute.
	*/
	virtual IGraphicAttrPoint* CreateGradientStrokeGradCenterAttribute
		(
		PMPoint		gradientGradCenter
		) = 0;
		
	/** Creates and adds the gradient center or start point attribute for stroke to the specified attribute list.
		@param gradientGradCenter the gradient fill center or start point to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeGradCenterAttribute
		(
		PMPoint							gradientGradCenter,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gradient center of start point attribute to the specified item list.
		@param gradientGradCenter the stroke gradient center or start point to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeGradCenterCommand 
		(
		PMPoint				gradientGradrCenter,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// =============================================
// Gradient Fill Radius
// =============================================

	/** Get the gradient fill radius. This attribute relates to radial gradient.
		@param gradientRadius the gradient radius to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientFillRadius 
		(
		PMReal&							gradientRadius,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill radius attribute for a radial gradient.
		@param gradientRadius the gradient fill radius create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill radius attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientFillRadiusAttribute
		(
		PMReal		gradientRadius
		) = 0;
		
	/** Creates and adds the gradient fill radius attribute to the specified attribute list.
		@param gradientRadius the gradient fill radius to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillRadiusAttribute
		(
		PMReal							gradientRadius,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient fill radius attribute to the specified item list.
		@param gradientRadius the gradient fill radius to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillRadiusCommand 
		(
		PMReal				gradientRadius,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// =============================================
// Gradient Stroke Radius
// =============================================

	/** Get the stroke gradient radius. This attribute relates to stroke radial gradient.
		@param gradientRadius the gradient radius to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientStrokeRadius 
		(
		PMReal&							gradientRadius,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the stroke gradient radius attribute for a radial gradient.
		@param gradientRadius the gradient radius create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill radius attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientStrokeRadiusAttribute
		(
		PMReal		gradientRadius
		) = 0;
		
	/** Creates and adds the gradient radius attribute for stroke to the specified attribute list.
		@param gradientRadius the stroke gradient radius to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeRadiusAttribute
		(
		PMReal							gradientRadius,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gradient radius attribute to the specified item list.
		@param gradientRadius the stroke gradient radius to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeRadiusCommand 
		(
		PMReal				gradientRadius,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// =============================================
// Gradient Fill Hilite Length
// =============================================

	/** Get the gradient fill hilite length.
		@param gradientHiliteLength the gradient fill hilite length to create.
		@param styleDescriptor the graphic  
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor
	*/
	virtual ErrorCode GetGradientFillHiliteLength 
		(
		PMReal&							gradientHiliteLength,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill hilite length.
		@param gradientHiliteLength the gradient fill hilite length to create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill hilite length attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientFillHiliteLengthAttribute
		(
		PMReal		gradientHiliteLength
		) = 0;
		
	/** Creates and adds the gradient fill hilite length attribute to the specified attribute list.
		@param gradientHiliteLength the gradient fill hilite length.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillHiliteLengthAttribute
		(
		PMReal							gradientHiliteLength,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient fill hilite length attribute to the specified item list.
		@param gradientHiliteLength the gradient fill hilite length to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillHiliteLengthCommand 
		(
		PMReal				gradientHiliteLength,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// =============================================
// Gradient Stroke HiliteLength
// =============================================

	/** Get the gradient hilite length for stroke.
		@param gradientHiliteLength the stroke gradient hilite length to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientStrokeHiliteLength 
		(
		PMReal&							gradientHiliteLength,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the stroke gradient hilite length.
		@param gradientHiliteLength the stroke gradient hilite length to create.
		@return the IGraphicAttrRealNumber pointer to the stroke gradient hilite length attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientStrokeHiliteLengthAttribute
		(
		PMReal		gradientHiliteLength
		) = 0;
		
	/** Creates and adds the stroke gradient hilite length attribute to the specified attribute list.
		@param gradientHiliteLength the stroke gradient hilite length.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeHiliteLengthAttribute
		(
		PMReal							gradientHiliteLength,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient hilite length attribute for stroke to the specified item list.
		@param gradientHiliteLength the stroke gradient hilite length to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeHiliteLengthCommand 
		(
		PMReal				gradientHiliteLength,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;
		
// =============================================
// Gradient Fill Hilite Angle
// =============================================

	/** Get the gradient fill hilite angle.
		@param gradientHiliteAngle the gradient fill hilite angle to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientFillHiliteAngle 
		(
		PMReal&							gradientHiliteAngle,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the gradient fill hilite angle.
		@param gradientHiliteAngle the gradient fill hilite angle to create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill hilite angle attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientFillHiliteAngleAttribute
		(
		PMReal		gradientHiliteAngle
		) = 0;
		
	/** Creates and adds the gradient fill hilite angle attribute to the specified attribute list.
		@param gradientHiliteAngle the gradient fill hilite angle.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientFillHiliteAngleAttribute
		(
		PMReal							gradientHiliteAngle,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply gradient fill hilite angle attribute to the specified item list.
		@param gradientHiliteAngle the gradient fill hilite angle to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientFillHiliteAngleCommand 
		(
		PMReal				gradientHiliteAngle,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// =============================================
// Gradient Stroke HiliteLength
// =============================================

	/** Get the stroke gradient hilite angle.
		@param gradientHiliteAngle the gradient fill hilite angle to create.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGradientStrokeHiliteAngle 
		(
		PMReal&							gradientHiliteAngle,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;
		
	/** Creates and returns the stroke gradient hilite angle.
		@param gradientHiliteAngle the gradient hilite angle to create.
		@return the IGraphicAttrRealNumber pointer to the gradient fill hilite angle attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGradientStrokeHiliteAngleAttribute
		(
		PMReal		gradientHiliteAngle
		) = 0;
		
	/** Creates and adds the stroke gradient hilite angle attribute to the specified attribute list.
		@param gradientHiliteAngle the gradient hilite angle.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGradientStrokeHiliteAngleAttribute
		(
		PMReal							gradientHiliteAngle,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gradient hilite angle attribute to the specified item list.
		@param gradientHiliteAngle the gradient fill hilite angle to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGradientStrokeHiliteAngleCommand 
		(
		PMReal				gradientHiliteAngle,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Corner Radius
// _____________________________________________

	/** Get the stroke corner radius.
	@param cornerRadius the stroke corner radius to get.
	@param styleDescriptor the graphic style descriptor. 
	@param cornerType the corner for which the radius is required.
	@return kSuccess if successful or returns an error code.
	@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetCornerRadius 
		(
		PMReal&					 cornerRadius,
		IGraphicStyleDescriptor* styleDescriptor,
		CornerType               cornerType = kSimpleCorner
		) = 0;

	/** Creates and returns the stroke corner radius.
	@param cornerRadius the corner radius to create.
	@param cornerType the corner for which the radius is required.
	@return the IGraphicAttrRealNumber pointer to the corner radius attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateCornerRadiusAttribute
		(
		PMReal		cornerRadius,
		CornerType  cornerType = kSimpleCorner
		) = 0;

	/** Creates and adds the stroke corner radius attribute to the specified attribute list.
	@param cornerRadius the corner radius.
	@param attributeList the attribute list.
	@param cornerType the corner for which the radius is required.
	@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddCornerRadiusAttribute
		(
		PMReal							cornerRadius,
		IGraphicStyleAttributeBossList*	attributeList,
		CornerType                      cornerType = kSimpleCorner
		) = 0;

	/** Creates the attribute command to apply stroke corner radius attribute to the specified item list.
	@param cornerRadius the corner radius to apply.
	@param targetItemList the item list.
	@param cornerType the corner for which the radius command is required.
	@param doPrePost kTrue if attribute pre/post action should be applied.
	@param enableDoNotify kTrue if notification should occur.
	@return apply attribute command.
	*/
	virtual ICommand* CreateCornerRadiusCommand 
		(
		PMReal				cornerRadius,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify,
		CornerType          cornerType = kSimpleCorner
		) = 0;

// _____________________________________________
//	Miter Limit
// _____________________________________________

	/** Get the stroke miter limit.
		@param cornerRadius the miter limit to get.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetMiterLimit 
		(
		PMReal&						miterLimit,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/** Creates and returns the miter limit attribute.
		@param miterLimit the miter limit to create.
		@return the IGraphicAttrRealNumber pointer to the corner radius attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateMiterLimitAttribute
		(
		PMReal		miterLimit
		) = 0;

	/** Creates and adds the miter limit attribute to the specified attribute list.
		@param miterLimit the miter limit to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddMiterLimitAttribute
		(
		PMReal							miterLimit,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply miter limit attribute to the specified item list.
		@param miterLimit the miter limit to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateMiterLimitCommand 
		(
		PMReal				miterLimit,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;


// _____________________________________________
//	Overprint fill
// _____________________________________________

	/** Get the fill overprint setting. kTrue if overprint is turned on and kFalse if off.
		@param overprintFill the fill overprint setting.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetOverprintFill 
		(
		bool16&							overprintFill,
		IGraphicStyleDescriptor*		styleDescriptor
		) = 0;

	/** Creates and returns the fill overprint attribute.
		@param overprintFill the fill overprint setting to create.
		@return the IGraphicAttrBoolean pointer to the fill overprint attribute.
	*/
	virtual IGraphicAttrBoolean* CreateOverprintFillAttribute
		(
		bool16		overprintFill
		) = 0;

	/** Creates and adds the fill overprint attribute to the specified attribute list.
		@param overprintFill the fill overprint setting to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddOverprintFillAttribute
		(
		bool16							overprintFill,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply fill overprint attribute to the specified item list.
		@param overprintFill the fill overprint setting to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateOverprintFillCommand 
		(
		bool16				overprintFill,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Overprint storke
// _____________________________________________

	/** Get the stroke overprint setting from the specified graphic style descriptor.
		kTrue if overprint is turned on and kFalse if off.
		@param overprintStroke the stroke overprint setting.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetOverprintStroke 
		(
		bool16&							overprintStroke,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the stroke overprint attribute.
		@param overprintStroke the stroke overprint setting to create.
		@return the IGraphicAttrBoolean pointer to the stroke overprint attribute.
	*/
	virtual IGraphicAttrBoolean* CreateOverprintStrokeAttribute
		(
		bool16		overprintStroke
		) = 0;

	/** Creates and adds the stroke overprint attribute to the specified attribute list.
		@param overprintStroke the stroke overprint setting to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddOverprintStrokeAttribute
		(
		bool16							overprintStroke,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke overprint attribute to the specified item list.
		@param overprintStroke the stroke overprint setting to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateOverprintStrokeCommand 
		(
		bool16				overprintStroke,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Line cap
// _____________________________________________

	/** Get the line cap from the specified graphic style descriptor.
		@param lineCap the line cap. This is defined in @see GraphicTypes.h.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetLineCap 
		(
		int32&							lineCap,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the line cap attribute.
		@param lineCap the line cap to create. This is defined in @see GraphicTypes.h.
		@return the IGraphicAttrInt32 pointer to the line capattribute.
		@see GraphicTypes.h.
	*/
	virtual IGraphicAttrInt32* CreateLineCapAttribute
		(
		int32		lineCap
		) = 0;

	/** Creates and adds the line cap attribute to the specified attribute list.
		@param lineCap the line cap to add. This is defined in @see GraphicTypes.h.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
	*/
	virtual ErrorCode AddLineCapAttribute
		(
		int32							lineCap,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply line cap attribute to the specified item list.
		@param lineCap the line cap to apply. This is defined in @see GraphicTypes.h.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateLineCapCommand 
		(
		int32				lineCap,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Join type
// _____________________________________________

	/** Get the line join type from the specified graphic style descriptor.
		@param joinType the line join type. This is defined in 
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
		@see IGraphicStyleDescriptor
	*/
	virtual ErrorCode GetJoinType 
		(
		int32&							joinType,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the join type attribute.
		@param joinType the line join type to create. This is defined in @see GraphicTypes.h.
		@return the IGraphicAttrInt32 pointer to the line join type attribute.
	*/
	virtual IGraphicAttrInt32* CreateJoinTypeAttribute
		(
		int32		joinType
		) = 0;

	/** Creates and adds the line join type attribute to the specified attribute list.
		@param joinType the line join type to add. This is defined in 
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
	*/
	virtual ErrorCode AddJoinTypeAttribute
		(
		int32							joinType,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply line join type attribute to the specified item list.
		@param joinType the line join type to apply. This is defined in 
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateJoinTypeCommand 
		(
		int32				joinType,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Arrow Head Alignment
// _____________________________________________

	/** Get the Arrow Head Alignment from the specified graphic style descriptor.
		@param arrowHeadAlignment whether Arrow Head to be drawn Inside or Outside path. This is defined in @see GraphicTypes.h.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetArrowHeadAlignment 
		(
		int32&							arrowHeadAlignment,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the Arrow Head Alignment attribute.
		@param arrowHeadAlignment the Arrow Head Alignment to create. This is defined in @see GraphicTypes.h.
		@return the IGraphicAttrInt32 pointer to the Arrow Head Alignment attribute.
		@see GraphicTypes.h.
	*/
	virtual IGraphicAttrInt32* CreateArrowHeadAlignmentAttribute
		(
		int32		arrowHeadAlignment
		) = 0;

	/** Creates and adds the Arrow Head Alignment attribute to the specified attribute list.
		@param arrowHeadAlignment whether Arrow Head to be drawn Inside or Outside path. This is defined in @see GraphicTypes.h. 
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GraphicTypes.h.
	*/
	virtual ErrorCode AddArrowHeadAlignmentAttribute
		(
		int32							arrowHeadAlignment,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply Arrow Head Alignment attribute to the specified item list.
		@param arrowHeadAlignment whether Arrow Head to be drawn Inside or Outside path. This is defined in @see GraphicTypes.h.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GraphicTypes.h.
	*/
	virtual ICommand* CreateArrowHeadAlignmentCommand 
		(
		int32				arrowHeadAlignment,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Line implementation
// _____________________________________________

	/** Get the line style from the specified graphic style descriptor.
		@param lineImplementation the line style class ID if style is predefined.
		These are predefined path stroker boss defined in InstStrokeFillID.h.
		@param lineImplementationUID the line style UID if style is customed.
		These are customed line styles defined using the line style dialog. The customed line
		styles are one of kCustomPathStrokerBoss or kCustomDashedPathStrokerBoss objects.
		@param styleDescriptor the graphic style descriptor.
		@return kSuccess if successful or returns an error code.
		@see InstStrokeFillID.h
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetLineImplementation 
		(
		ClassID&						lineImplementation,
		UID&							lineImplementationUID,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the line style attribute.
		@param lineImplementation the line style if style is predefined.
		@param lineImplementationUID the line style if style is customed.
		@return the IGraphicAttrClassID pointer to the line style attribute.
		@see also GetLineImplementation
	*/
	virtual IGraphicAttrClassID* CreateLineImplementationAttribute
		(
		ClassID		lineImplementation,
		UID			lineImplementationUID
		) = 0;

	/** Creates and adds the line style attribute to the specified attribute list.
		@param lineImplementation the line style if style is predefined.
		@param lineImplementationUID the line style if style is customed.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see also GetLineImplementation
	*/
	virtual ErrorCode AddLineImplementationAttribute
		(
		ClassID							lineImplementation,
		UID								lineImplementationUID,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply line style attribute to the specified item list.
		@param lineImplementation the line style to apply if style is predefined.
		@param lineImplementationUID the line style to apply if style is customed.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see also GetLineImplementation
	*/
	virtual ICommand* CreateLineImplementationCommand 
		(
		ClassID				lineImplementation,
		UID					lineImplementationUID,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Line end-start implementation
// _____________________________________________

	/** Get the line end-start style from the specified graphic style descriptor.
		@param lineEndStartImplementation the line-end start style. line-end styles are provided
		through kArrowHeadServiceBoss. Currently they are predefined line-end 
		styles defined in InstStrokeFillID.h. Example, kSimpleArrowHeadBoss is a line-end style.
		@param styleDescriptor the graphic style descriptor.
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@see InstStrokeFillID.h. 
	*/
	virtual ErrorCode GetLineEndStartImplementation 
		(
		ClassID&						lineEndStartImplementation,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the line end-start style attribute.
		@param lineEndStartImplementation the line-end start style. 
		@return the IGraphicAttrClassID pointer to the line style attribute.
		@see GetLineEndStartImplementation.
	*/
	virtual IGraphicAttrClassID* CreateLineEndStartImplementationAttribute
		(
		ClassID		lineEndStartImplementation
		) = 0;

	/** Creates and adds the line end-start style attribute to the specified attribute list.
		@param lineEndStartImplementation the line-end start style
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GetLineEndStartImplementation.
	*/
	virtual ErrorCode AddLineEndStartImplementationAttribute
		(
		ClassID							lineEndStartImplementation,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply line end-start style attribute to the specified item list.
		@param lineEndStartImplementation the line-end start style. 
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GetLineEndStartImplementation.
	*/
	virtual ICommand* CreateLineEndStartImplementationCommand 
		(
		ClassID				lineEndStartImplementation,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Line end-end implementation
// _____________________________________________

	/** Get the line end-end style from the specified graphic style descriptor.
		@param lineEndStartImplementation the line-end end style. line-end styles are provided
		through kArrowHeadServiceBoss. Currently they are predefined line-end 
		styles defined in InstStrokeFillID.h. Example, kSimpleArrowHeadBoss is a line-end style.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@see InstStrokeFillID.h. 
	*/
	virtual ErrorCode GetLineEndEndImplementation 
		(
		ClassID&						lineEndEndImplementation,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the line end-end style attribute.
		@param lineEndEndImplementation the line-end end style. 
		@return the IGraphicAttrClassID pointer to the line-end end style attribute.
		@see GetLineEndEndImplementation
	*/
	virtual IGraphicAttrClassID* CreateLineEndEndImplementationAttribute
		(
		ClassID		lineEndEndImplementation
		) = 0;

	/** Creates and adds the line end-end style attribute to the specified attribute list.
		@param lineEndEndImplementation the line-end end style. 
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GetLineEndEndImplementation
	*/
	virtual ErrorCode AddLineEndEndImplementationAttribute
		(
		ClassID							lineEndEndImplementation,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply line end-end style attribute to the specified item list.
		@param lineEndEndImplementation the line-end end style. 
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GetLineEndEndImplementation
	*/
	virtual ICommand* CreateLineEndEndImplementationCommand 
		(
		ClassID				lineEndEndImplementation,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
	//	Arrow Head Start Scaling
	// _____________________________________________

	/**
	Creates an arrow head start scale attribute.
	@param arrowHeadScaleFactor The percentage scale factor which specifies the scaling to be applied to the start arrow head.
	*/
	virtual IGraphicAttrRealNumber* CreateArrowHeadStartScaleAttribute
	(
		PMReal		arrowHeadScaleFactor
	) = 0;

	/** Creates the attribute command to apply arrow head start scale attribute to the specified item list.
	@param arrowHeadScaleFactor The percentage scaling to be applied to the start arrow head
	@param targetItemList the item list.
	@param doPrePost kTrue if attribute pre/post action should be applied.
	@param enableDoNotify kTrue if notification should occur.
	@return apply attribute command.
	@see GraphicTypes.h.
	*/
	virtual ICommand* CreateArrowHeadStartScaleCommand
	(
		PMReal				arrowHeadScaleFactor,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
	) = 0;

	/** Get the Arrow head start scale factor applied from the specified graphic style descriptor.
	@param arrowHeadScaleFactor The percentage scaling to be applied to the start arrow head.
	@param styleDescriptor the graphic style descriptor.
	@return kSuccess if successful or returns an error code.
	@see GraphicTypes.h.
	@see IGraphicStyleDescriptor
	*/
	virtual ErrorCode GetArrowHeadStartScale
	(
		PMReal&							arrowHeadScaleFactor,
		IGraphicStyleDescriptor* 		styleDescriptor
	) = 0;

	/** Creates and adds the arrow head start scale attribute to the specified attribute list.
	@param arrowHeadScaleFactor the percentage scaling to be applied to the start arrow head.
	@param attributeList the attribute list.
	@return kSuccess if successful or returns an error code.
	@see GraphicTypes.h.
	*/
	virtual ErrorCode AddArrowHeadStartScaleAttribute
	(
		PMReal							arrowHeadScaleFactor,
		IGraphicStyleAttributeBossList*	attributeList
	) = 0;

	// _____________________________________________
	//	Arrow Head End Scaling
	// _____________________________________________

	/**
	Creates an arrow head end scale attribute.
	@param arrowHeadScaleFactor The percentage scale factor which specifies the scaling to be applied to the end arrow head.
	*/
	virtual IGraphicAttrRealNumber* CreateArrowHeadEndScaleAttribute
	(
		PMReal		arrowHeadScale
	) = 0;

	/** Creates the attribute command to apply arrow head end scale attribute to the specified item list.
	@param arrowHeadScaleFactor The percentage scaling to be applied to the end arrow head
	@param targetItemList the item list.
	@param doPrePost kTrue if attribute pre/post action should be applied.
	@param enableDoNotify kTrue if notification should occur.
	@return apply attribute command.
	@see GraphicTypes.h.
	*/
	virtual ICommand* CreateArrowHeadEndScaleCommand
	(
		PMReal				arrowHeadScale,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
	) = 0;

	/** Get the Arrow head end scale factor applied from the specified graphic style descriptor.
	@param arrowHeadScaleFactor The percentage scaling to be applied to the end arrow head.
	@param styleDescriptor the graphic style descriptor.
	@return kSuccess if successful or returns an error code.
	@see GraphicTypes.h.
	@see IGraphicStyleDescriptor
	*/
	virtual ErrorCode GetArrowHeadEndScale
	(
		PMReal&							arrowHeadScale,
		IGraphicStyleDescriptor* 		styleDescriptor
	) = 0;
	
	/** Creates and adds the arrow head end scale attribute to the specified attribute list.
	@param arrowHeadScaleFactor the percentage scaling to be applied to the end arrow head.
	@param attributeList the attribute list.
	@return kSuccess if successful or returns an error code.
	@see GraphicTypes.h.
	*/
	virtual ErrorCode AddArrowHeadEndScaleAttribute
	(
		PMReal							arrowHeadScale,
		IGraphicStyleAttributeBossList*	attributeList
	) = 0;

	// _____________________________________________
	//	Live corner implementation
	// _____________________________________________

	/** Get the line corner style from the specified graphic style descriptor.
	@param cornerImplementation the corner style. The corner styles are provided
	through kCornerServiceBoss. Currently they are predefined corner
	styles defined in InstStrokeFillID.h. Example, kRoundedCornerBoss is a line-end style.
	@param styleDescriptor the graphic style descriptor.
	@param cornerType the corner for which the implementation is required.
	@return kSuccess if successful or returns an error code.
	@see IGraphicStyleDescriptor
	@see InstStrokeFillID.h.
	*/
	virtual ErrorCode GetCornerImplementation 
		(
		ClassID&					cornerImplementation,
		IGraphicStyleDescriptor* 	styleDescriptor,
		CornerType                  cornerType = kSimpleCorner
		) = 0;

	/** Creates and returns the line corner style attribute.
	@param cornerImplementation the corner style. 

	@param cornerType the corner for which the implementation is required.
	@return the IGraphicAttrClassID pointer to the corner style attribute.
	@see GetCornerImplementation
	*/
	virtual IGraphicAttrClassID* CreateCornerImplementationAttribute
		(
		ClassID		cornerImplementation,
		CornerType  cornerType = kSimpleCorner
		) = 0;

	/** Creates and adds the corner style attribute to the specified attribute list.
	@param cornerImplementation the corner style. 
	@param attributeList the attribute list.
	@param cornerType the corner for which the implementation is required.
	@return kSuccess if successful or returns an error code.
	@see GetCornerImplementation
	*/
	virtual ErrorCode AddCornerImplementationAttribute
		(
		ClassID							cornerImplementation,
		IGraphicStyleAttributeBossList*	attributeList,
		CornerType                      cornerType = kSimpleCorner	
		) = 0;

	/** Creates the attribute command to apply line corner style attribute to the specified item list.
	@param cornerImplementation the corner style. 
	@param targetItemList the item list.
	@param cornerType the corner for which the implementation command is required.
	@param doPrePost kTrue if attribute pre/post action should be applied.
	@param enableDoNotify kTrue if notification should occur.
	@return apply attribute command.
	@see GetCornerImplementation
	*/
	virtual ICommand* CreateCornerImplementationCommand 
		(
		ClassID				cornerImplementation,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify,
		CornerType          cornerType = kSimpleCorner
		) = 0;



// _____________________________________________
//	Stroke rendering UID
// _____________________________________________

	/** Get the stroke rendering UID from the specified graphic style descriptor.
		@param strokeRenderingUID the stroke rendering UID. A rendering UID must be a
		rendering object boss with the reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@see IRenderingObject
		@see ISwatchList
	*/
	virtual ErrorCode GetStrokeRenderingUID
		(
		UID&							strokeRenderingUID,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Query for the stroke rendering object from the graphic style descriptor.
		@param styleDescriptor the graphic style descriptor. 
		@return the IRenderingObject pointer or nil.
		@see IRenderingObject
		@see IGraphicStyleDescriptor.
	*/
	virtual IRenderingObject* QueryStrokeRenderingObject 
		(
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the stroke rendering attribute attribute.
		@param strokeRenderingUID the stroke rendering UID for the attribute. A rendering UID must be a
		rendering object boss with reqruied IRenderingObject interface. 
		@return the IPersistUIDData pointer to the stroke rendering attribute.
		@see GetStrokeRenderingUID
	*/
	virtual IPersistUIDData* CreateStrokeRenderingAttribute
		(
		UID		strokeRenderingUID
		) = 0;

	/** Creates and adds the stroke rendering attribute to the specified attribute list.
		@param strokeRenderingUID the stroke rendering UID for the attribute. A rendering UID must be a
		rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GetStrokeRenderingUID
	*/
	virtual ErrorCode AddStrokeRenderingAttribute
		(
		UID								strokeRenderingUID,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke rendering attribute to the specified item list.
		@param strokeRenderingUID the stroke rendering UID to apply. A rendering UID must be a
		rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GetStrokeRenderingUID
	*/
	virtual ICommand* CreateStrokeRenderingCommand 
		(
		UID					strokeRenderingUID,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Fill rendering UID
// _____________________________________________

	/** Get the fill rendering UID from the specified graphic style descriptor.
		@param fillRenderingUID the fill rendering UID. A rendering UID must be a
		rendering object boss with the reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@see IRenderingObject.
		@see ISwatchList.
	*/
	virtual ErrorCode GetFillRenderingUID
		(
		UID&						fillRenderingUID,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/** Query for the fill rendering object from the graphic style descriptor.
		@param styleDescriptor the graphic style descriptor. 
		@return the IRenderingObject pointer or nil.
		@see IRenderingObject.
		@see IGraphicStyleDescriptor.
	*/
	virtual IRenderingObject* QueryFillRenderingObject 
		(
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/** Creates and returns the fill rendering attribute attribute.
		@param fillRenderingUID the fill rendering UID. A rendering UID must be a
		rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@return the IPersistUIDData pointer to the fill rendering attribute.
		@see GetFillRenderingUID
	*/
	virtual IPersistUIDData* CreateFillRenderingAttribute
		(
		UID		fillRenderingUID
		) = 0;

	/** Creates and adds the fill rendering attribute to the specified attribute list.
		@param fillRenderingUID the fill rendering UID to add.  A rendering UID must be a
		rendering object boss with the reqruied IRenderingObject interface.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GetFillRenderingUID
	*/
	virtual ErrorCode AddFillRenderingAttribute
		(
		UID								fillRenderingUID,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply fill rendering attribute to the specified item list.
		@param fillRenderingUID the fill rendering UID to add. A rendering UID must be a
		rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GetFillRenderingUID
	*/
	virtual ICommand* CreateFillRenderingCommand 
		(
		UID					fillRenderingUID,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Fill Tint
// _____________________________________________

	/** Get the fill tint from the specified graphic style descriptor.
		@param fillTint the fill tint percent. If there's no tint overrides for the fill, tint is kInvalidTintPercent.
		Otherwise, tint is 0 or greater but less than 100.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetFillTint
		(
		PMReal&						fillTint,
		IGraphicStyleDescriptor* 	styleDescriptor
		) = 0;

	/** Creates and returns the fill tint attribute attribute.
		@param fillTint the fill tint percent.
		@return the IGraphicAttrRealNumber pointer to the fill tint attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateFillTintAttribute
		(
		PMReal		fillTint
		) = 0;

	/** Creates and adds the fill tint attribute to the specified attribute list.
		@param fillTint the fill tint percent to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddFillTintAttribute
		(
		PMReal							fillTint,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply fill tint attribute to the specified item list.
		@param fillTint the fill tint percent to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateFillTintCommand 
		(
		PMReal				fillTint,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Stroke Tint
// _____________________________________________

	/** Get the stroke tint from the specified graphic style descriptor.
		@param strokeTint the stroke tint percent. If there's no tint overrides for the stroke, tint is kInvalidTintPercent.
		Otherwise, tint is 0 or greater but less than 100.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetStrokeTint 
		(
		PMReal&							strokeTint,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the stroke tint attribute attribute.
		@param strokeTint the stroke tint percent.
		@return the IGraphicAttrRealNumber pointer to the stroke tint attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateStrokeTintAttribute
		(
		PMReal		strokeTint
		) = 0;

	/** Creates and adds the stroke tint attribute to the specified attribute list.
		@param strokeTint the stroke tint percent to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddStrokeTintAttribute
		(
		PMReal							strokeTint,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke tint attribute to the specified item list.
		@param strokeTint the stroke tint percent to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateStrokeTintCommand 
		(
		PMReal				strokeTint,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	EvenOdd
// _____________________________________________

	/** Get even-odd fill from the specified graphic style descriptor.
		@param evenOddFill the even-odd fill.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetEvenOdd 
		(
		bool16&							evenOddFill,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the even-odd fill attribute attribute.
		@param evenOddFill the even-odd fill setting.
		@return the IGraphicAttrBoolean pointer to the even-odd fill attribute.
	*/
	virtual IGraphicAttrBoolean* CreateEvenOddAttribute
		(
		bool16		evenOddFill
		) = 0;

	/** Creates and adds the even-odd fill attribute to the specified attribute list.
		@param evenOddFill the even-odd fill setting to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddEvenOddAttribute
		(
		bool16								evenOddFill,
		IGraphicStyleAttributeBossList*		attributeList
		) = 0;

	/** Creates the attribute command to apply even-odd fill attribute to the specified item list.
		@param evenOddFill the even-odd fill to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateEvenOddCommand 
		(
		bool16				evenOddFill,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Non-print
// _____________________________________________

	/** Get non-printing setting from the specified graphic style descriptor.
		kTrue if non-printing otherwise kFalse.
		@param nonPrint the non-printing setting.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetNonPrint 
		(
		bool16&							nonPrint,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the non-print attribute attribute.
		@param nonPrint the non-printing setting.
		@return the IGraphicAttrBoolean pointer to the non-print attribute.
	*/
	virtual IGraphicAttrBoolean* CreateNonPrintAttribute
		(
		bool16		nonPrint
		) = 0;

	/** Creates and adds the on-print attribute to the specified attribute list.
		@param nonPrint the non-printing setting to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddNonPrintAttribute
		(
		bool16							nonPrint,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply non-print attribute to the specified item list.
		@param nonPrint the non-printing setting to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateNonPrintCommand 
		(
		bool16				nonPrint,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
// _____________________________________________

	/** Apply the rendering UID to the specified rendering attribute class to a list of page items.
		@param pageItemList the list of page items.
		@param renderObjectClassID the rendering class of the rendering UID.
		Rendering class can be one of supported rendering object types: 
		kPMColorBoss, kGradientRenderingObjectBoss, and kGraphicStateNoneRenderingObjectBoss.
		@param renderUID rendering UID. A rendering UID must be one of the rendering objects with the required IRenderingObject interface.
		@param attributeClassID the rendering attribute class. (It must be kGraphicStyleFillRenderingAttrBoss or kGraphicStyleStrokeRenderingAttrBoss).
		@see IRenderingObject
		@see ISwatchList.h
		@see ColorSystemID.h
		@see GradientFillID.h
		@see GraphicStylesID.h
	*/
	virtual void ApplyRenderUIDToPageItems 
		(
		UIDList&		 pageItemList,
		ClassID			 renderObjectClassID,
		UID				 renderUID,
		ClassID			 attributeClassID
		) = 0;

// =============================================
// Gap Attributes
// =============================================

	/** Get the stroke gap rendering UID from the specified graphic style descriptor.
		Stroke gap attribute is only relevant for certain line style such as dashed or compound lines.
		@param gapRenderingUID the stroke gap rendering UID.
		A rendering UID must be a rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@see IRenderingObject.
	*/
	virtual ErrorCode GetGapRenderingUID
		(
		UID&							gapRenderingUID,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Query for the stroke gap rendering object from the graphic style descriptor.
		@param styleDescriptor the graphic style descriptor. 
		@return the IRenderingObject pointer or nil.
		@see IRenderingObject.
		@see IGraphicStyleDescriptor.
		@see GetGapRenderingUID.
	*/
	virtual IRenderingObject* QueryGapRenderingObject 
		(
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the stroke gap rendering attribute attribute.
		@param gapRenderingUID the stroke rendering UID for the attribute.
		A rendering UID must be a rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@return the IPersistUIDData pointer to the corner style attribute.
		@see GetGapRenderingUID.
	*/
	virtual IPersistUIDData* CreateGapRenderingAttribute
		(
		UID		gapRenderingUID
		) = 0;

	/** Creates and adds the stroke gap rendering attribute to the specified attribute list.
		@param gapRenderingUID the stroke gap rendering UID for the attribute.
		A rendering UID must be a rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@see GetGapRenderingUID.
	*/
	virtual ErrorCode AddGapRenderingAttribute
		(
		UID								gapRenderingUID,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gap rendering attribute to the specified item list.
		@param gapRenderingUID the stroke gap rendering UID to apply.
		A rendering UID must be a rendering object boss with reqruied IRenderingObject interface. 
		This can be a named swatch UID or an unnamed swatch UID.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@see GetGapRenderingUID.
	*/
	virtual ICommand* CreateGapRenderingCommand 
		(
		UID					gapRenderingUID,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Stroke Gap Tint
// _____________________________________________

	/** Get the stroke gap tint from the specified graphic style descriptor.
		@param gapTint the stroke gap tint percent. If there's no tint overrides for the stroke gap attribute,
		tint is kInvalidTintPercent. Otherwise, tint is 0 or greater but less than 100.
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
	*/
	virtual ErrorCode GetGapTint 
		(
		PMReal&							gapTint,
		IGraphicStyleDescriptor* 		styleDescriptor
		) = 0;

	/** Creates and returns the stroke gap tint attribute attribute.
		@param gapTint the stroke gap tint percent.
		@return the IGraphicAttrRealNumber pointer to the stroke gap tint attribute.
	*/
	virtual IGraphicAttrRealNumber* CreateGapTintAttribute
		(
		PMReal		gapTint
		) = 0;

	/** Creates and adds the stroke  gaptint attribute to the specified attribute list.
		@param gapTint the stroke gap tint percent to add.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddGapTintAttribute
		(
		PMReal							gapTint,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke tint gap attribute to the specified item list.
		@param gapTint the stroke gap tint percent to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateGapTintCommand 
		(
		PMReal				gapTint,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// _____________________________________________
//	Overprint storke gap
// _____________________________________________

	/** Get the stroke gap overprint setting from the specified graphic style descriptor.
		kTrue if overprint is turned on and kFalse if off.
		@param overprintGap the stroke gap overprint setting.
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor
	*/
	virtual ErrorCode GetOverprintGap
		(
		bool16&							overprintGap,
		IGraphicStyleDescriptor*		styleDescriptor
		) = 0;

	/** Creates and returns the stroke gap overprint attribute.
		@param overprintGap the stroke gap overprint setting to create.
		@return the IGraphicAttrBoolean pointer to the stroke overprint attribute.
	*/
	virtual IGraphicAttrBoolean* CreateOverprintGapAttribute
		(
		bool16		overprintGap
		) = 0;

	/** Creates and adds the stroke gap overprint attribute to the specified attribute list.
		@param overprintGap the stroke v overprint setting to create.
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
	*/
	virtual ErrorCode AddOverprintGapAttribute
		(
		bool16							overprintGap,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke gap overprint attribute to the specified item list.
		@param overprintGap the stroke gap overprint setting to apply.
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
	*/
	virtual ICommand* CreateOverprintGapCommand 
		(
		bool16				overprintGap,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

// =============================================
// Stroke alignment
// =============================================

	/** Get the stroke alignment from the specified graphic style descriptor.
		@param strokeAlignment the stroke alignment. This is a PMStrokeAlignment. 
		@param styleDescriptor the graphic style descriptor. 
		@return kSuccess if successful or returns an error code.
		@see IGraphicStyleDescriptor.
		@See GraphicTypes.h
	*/
	virtual ErrorCode GetStrokeAlignment
		(
		int32&							strokeAlignment,	// 
		IGraphicStyleDescriptor*		styleDescriptor
		) = 0;

	/** Creates and returns the stroke alignment attribute.
		@param strokeAlignment the stroke alignment to create. This is a PMStrokeAlignment. 
		@return the IGraphicAttrInt32 pointer to the line capattribute.
		@See GraphicTypes.h
	*/
	virtual IGraphicAttrInt32* CreateStrokeAlignmentAttribute
		(
		int32		strokeAlignment
		) = 0;

	/** Creates and adds the stroke alignment attribute to the specified attribute list.
		@param strokeAlignment the stroke alignment to create.
		This is a PMStrokeAlignment. 
		@param attributeList the attribute list.
		@return kSuccess if successful or returns an error code.
		@See GraphicTypes.h
	*/
	virtual ErrorCode AddStrokeAlignmentAttribute
		(
		int32							strokeAlignment,
		IGraphicStyleAttributeBossList*	attributeList
		) = 0;

	/** Creates the attribute command to apply stroke alignment attribute to the specified item list.
		@param strokeAlignment the stroke alignment to apply. This is a PMStrokeAlignment. 
		@param targetItemList the item list.
		@param doPrePost kTrue if attribute pre/post action should be applied.
		@param enableDoNotify kTrue if notification should occur.
		@return apply attribute command.
		@See GraphicTypes.h
	*/
	virtual ICommand* CreateStrokeAlignmentCommand 
		(
		int32				strokeAlignment,
		const UIDList*		targetItemList,
		bool16				doPrePost,
		bool16				enableDoNotify
		) = 0;

	virtual ErrorCode GetInt32Value(	IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, int32& value ) = 0 ;
	virtual ErrorCode GetBoolValue(		IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, bool16& value ) = 0 ;
	virtual ErrorCode GetStringValue(	IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, PMString& value ) = 0 ;
	virtual ErrorCode GetRealValue(		IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, PMReal& value ) = 0 ;
	virtual ErrorCode GetPointValue(	IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, PMPoint& value ) = 0 ;
	virtual ErrorCode GetClassValue(	IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, ClassID& value ) = 0 ;
	virtual ErrorCode GetUIDValue(		IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, UID& value ) = 0 ;

	virtual ErrorCode AddInt32Value(	IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const int32& value ) = 0 ;
	virtual ErrorCode AddBoolValue(		IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const bool16& value ) = 0 ;
	virtual ErrorCode AddStringValue(	IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const PMString& value ) = 0 ;
	virtual ErrorCode AddRealValue(		IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const PMReal& value ) = 0 ;
	virtual ErrorCode AddPointValue(	IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const PMPoint& value ) = 0 ;
	virtual ErrorCode AddClassValue(	IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const ClassID& value ) = 0 ;
	virtual ErrorCode AddUIDValue(		IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, const UID& value ) = 0 ;
	virtual ErrorCode AddValue(			IGraphicStyleAttributeBossList* attributeList, const ClassID& attrID, IPMUnknown* iAttr ) = 0 ;

	virtual ErrorCode GetFontValue(		IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, PMString& value) = 0;
	virtual ErrorCode GetFontFamilyUIDValue(IGraphicStyleDescriptor* styleDescriptor, const ClassID& attrID, UID& value) = 0;
    
    /** Creates and returns the aspect ratio attribute.
     @param aspectRatio the aspect ratio value.
     @return the IGraphicAttrRealNumber pointer to the aspect ratio attribute.
     */
    
    virtual IGraphicAttrRealNumber* CreateGradientFillAspectRatio( PMReal aspectRatio) = 0;
};

#endif	// __ODFRC__
#endif	// __IGraphicAttributeUtils__

