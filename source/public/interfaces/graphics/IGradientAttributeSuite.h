//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientAttributeSuite.h $
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
//========================================================================================

#pragma once
#ifndef __IGradientAttributeSuite__
#define __IGradientAttributeSuite__

#include "IPMUnknown.h"
#include "IGraphicAttrMessage.h"

#include "GraphicTypes.h"
#include "PMPoint.h"
#include "K2Vector.h"

#include "GradientFillID.h"

const PMReal			kDefaultGradientAngle			= 0.0;
const PMReal			kDefaultGradientLength			= 0.0;

const PMPoint			kDefaultGradientCenter			= PMPoint (0,0);
const PMReal			kDefaultGradientRadius			= 0.0;
const PMReal			kDefaultGradientHiliteLength	= 0.0;
const PMReal			kDefaultGradientHiliteAngle		= 0.0;

const PMReal			kInvalidRealNumberValue	= -1.0;

//________________________________________________________________________________________
//	Class definition
//________________________________________________________________________________________
class IGraphicStyleAttributeBossList;


/**	A selection related attribute suite interface for the gradient attributes.
	It provides get and set methods for accessing the gradient attributes.
	It works in conjunction with the IGraphicAttributeSuite. @see also IGraphicAttributeSuite.h
*/
class IGradientAttributeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRADIENTATTRIBUTESUITE };
	
	//________________________________________________________________________________________
	//	Data Types
	//________________________________________________________________________________________
	enum AttributeType
		{
		/**	kUnknownAttrType indicates an unknown gradient attribute type.
		*/
		kUnknownAttrType = -1,
		
		//	Fill attributes

		/**	kFillAngle indicates the gradient fill angle attribute.
		*/
		kFillAngle = 0,
		/**	kFillLength indicates the gradient fill length attribute.
		*/
		kFillLength,
		/**	kFillCenter indicates the gradient fill center attribute if gradient type
			is a kRadial gradient. It indicates a gradient start point attribute if
			gradient type is a kAxial gradient.
		*/
		kFillCenter,
		/**	kFIllRadius indicates the gradient fill radius attribute.
		*/
		kFIllRadius,
		/**	kFIllHiliteAngle indicates the gradient fill hilite angle attribute.
		*/
		kFIllHiliteAngle,
		/**	kFIllHiliteLength indicates the gradient fill hilite length attribute.
		*/
		kFIllHiliteLength,
		
		//	Stroke attributes

		/**	kFillAngle indicates the gradient stroke angle attribute.
		*/
		kStrokeAngle,
		/**	kFillLength indicates the gradient stroke length attribute.
		*/
		kStrokeLength,
		/**	kFillCenter indicates the gradient stroke center attribute if gradient type
			is a kRadial gradient. It indicates a gradient start point attribute if
			gradient type is a kAxial gradient.
		*/
		kStrokeCenter,
		/**	kFIllRadius indicates the gradient stroke radius attribute.
		*/
		kStrokeRadius,
		/**	kFIllHiliteAngle indicates the gradient stroke hilite angle attribute.
		*/
		kStrokeHiliteAngle,
		/**	kFIllHiliteLength indicates the gradient stroke hilite length attribute.
		*/
		kStrokeHiliteLength,
				
		/**	kMaxNumberAttrTypes indicates the maximum number of gradient attribute types.
		*/
		kMaxNumberAttrTypes
		};
		
public:
	//________________________________________________________________________________
	//	Return the attribute count specified by the Attribute Class ID and the attribute type
	//________________________________________________________________________________

	/**	Return the attribute count for the spcified attrribute class.
		@param ClassID attributeClassID specifies the attribute class.
		@return the number of count for this attribute class.
	*/
	virtual uint16 			GetAttributeCount (ClassID attributeClassID) = 0;
	/**	Return the attribute count for the spcified attrribute class and value.
		@param attributeClassID specifies the attribute class.
		@param index specifies the nth attribute value.
		@return the number of count for this attribute class and value.
	*/
	virtual uint16 			GetAttributeValueCount (ClassID attributeClassID, uint32 index) = 0;
	/**	Return the attribute count for the spcified attrribute type.
		@param attributeType specifies the attribute type.
		@return the number of count for this attribute type.
	*/
	virtual uint16 			GetAttributeCount (AttributeType attributeType) = 0;
	
	//________________________________________________________________________________
	//	Attribute value accessors
	//________________________________________________________________________________

	/**	Returns the nth attribute specified by the attribute class ID.
		The caller is responsible to release the object returned.
		@param index specifies the nth attribute for this attribute class.
		@param attributeClass specifies the attribute class.
		@param interfaceIID is the interested interface IID.
		@return the interface pointer to the specified attribute.
	*/
	virtual const IPMUnknown* 	QueryAttribute			(uint32 index, ClassID attributeClass, const PMIID& interfaceIID = IID_IUNKNOWN) = 0;

	/**	Create a copy of the nth attribute specified by the attribute class ID.
		The caller is responsible to release the object returned.
		@param index specifies the nth attribute for this attribute class.
		@param attributeClass specifies the attribute class.
		@param interfaceIID is the interested interface IID.
		@return the interface pointer to the specified attribute copy.
	*/
	virtual IPMUnknown* 	CreateAttributeCopy				(uint32 index, ClassID attributeClass, const PMIID& interfaceIID = IID_IUNKNOWN) = 0;
	
	/**	Copy the content of source attribute into the nth attribute of the same type.
		@param index specifies the nth attribute for this attribute class.
		@param iSourceAttribute specifies the source attribute.
		@return kSuccess if successful. Otherwise returns an error code.
	*/
	virtual ErrorCode	 	CopyIntoAttribute				(uint32 index, IPMUnknown* iSourceAttribute) = 0;
	
	//________________________________________________________________________________
	//	Returns the nth specific attribute value
	//________________________________________________________________________________

	/**	Returns the nth attribute value for the specified attribute type.
		@param index specifies the nth attribute for this attribute class.
		@param attributeType specifies the attribute type.
		@return a PMReal for the specified attribute.
	*/
	virtual PMReal			GetRealNumberAttributeValue 	(uint32 index, AttributeType attributeType) = 0;
	/**	Returns the nth attribute value for the specified attribute type.
		@param index specifies the nth attribute for this attribute class.
		@param attributeType specifies the attribute type.
		@return a PMPoint for the specified attribute.
	*/
	virtual PMPoint			GetPointAttributeValue 			(uint32 index, AttributeType attributeType) = 0;

	/**	Return kTrue if the attribugte specified is unique.
		@param attributeClass specifies the attribute class.
		@return true if specified attribute is unique.
	*/
	virtual bool16			IsAttributeUnique 				(ClassID attributeClass) = 0;
	/**	Return kTrue if the attribugte specified is unique.
		@param attributeType specifies the attribute type.
		@return true if specified attribute is unique.
	*/
	virtual bool16			IsAttributeUnique				(AttributeType attributeType) = 0;

	/**	Apply the specified attribute.
		If applying a angle attribute, other related gradient attributes will be adjusted
		relative to the left-bottom of the text/graphic frame which the angle attribute
		is being applied.
		@param attributeClass is the specified attribute class.
		@param iAttribute is the attribute.
		@return kSuccess if successful. Otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyAttribute					(ClassID attributeClass, const IPMUnknown* iAttribute) = 0;

	/**	Apply the list of attributes. Attributes are applied as is without any modification.
		@param iAttributeList is the list of attributes to apply.
		@return kSuccess if successful. Otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyAttributes					(IGraphicStyleAttributeBossList* iAttributeList) = 0;

	/**	Apply the gradient vector to the current selection.
		If one or more item in the current current selection does not already have gradient
		fill rendering object applied, the current stroke or fill gradient rendering
		object will be applied to the entire selection first.
		@param startPoint is the starting point of the vector in the pastboard coordinate.
		@param endPoint is the ending point of the vector in the pastboard coordinate.
		@return kSuccess if successful. Otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyGradientVector				(const PMPoint& startPoint, const PMPoint& endPoint) = 0;

	/**	Apply the default gradient attributes  based on the gradient type.
		Attributes are applied relative to the frame geometry. All related attributes
		are reset to their original default values.
		@param gradientType specifies the gradient type. This is either kAxial or kRadial.
		@see also GraphicTypes.h
		@return kSuccess if successful. Otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyDefaultAttributes			(GradientType gradientType) = 0;

};

DECLARE_BASE_TYPE(IGradientAttributeSuite::AttributeType);

#endif	// __IGradientAttributeSuite__

