//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IConvertShapeCmdData.h $
//  
//  Owner: Shengliu Dai
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
//  Purpose:	
//  Data interface for changing the shape of page items in ConvertShapeCmd.cpp. 
//  
//========================================================================================

#pragma once
#ifndef __IConvertShapeCmdData__
#define __IConvertShapeCmdData__

#include "IConvertShapeSuite.h"
#include "SplineID.h"

class IConvertShapeCmdData : public IPMUnknown 
{
public:
	enum {kDefaultIID = IID_ICONVERTSHAPECMDDATA};


	/**	Set convert shape command data
		@param shapeType Shape type for converting to
		@param corner ClassID of corner effect type (service provider of kPathCornerService) 
					default = kInvalidClass means no corner effect
		@param cornerRadius PMReal value in points for radius to be used for corner effect (service provider of kPathCornerService) 
					default = 12 points. Used only when corner class is not kInvalidClass
		@param numSides number of sides of polygon for converting to, default is 6. Can range from kMinPolygonSides to  kMaxPolygonSides.
						unused if the shapetype is not polygon, such as triangle, rectangle, oval etc. Use -1 to leave unchanged.
		@param starInset amount of star inset of polygon for converting to, default is 0. Can range from kMinPolygonInset to kMaxPolygonInset.
						unused if the shapetype is not polygon, such as triangle, rectangle, oval etc. Use -1 to leave unchanged.
	 */
	virtual void Set(IConvertShapeSuite::ShapeType shapeType, const ClassID corner = kInvalidClass, const PMReal& cornerRadius = 12.0, const int32 numSides = 6, const int32 starInset = 0)=0;


	/**	GetShapeType
		@param none
		@return Shape type for converting to 
	 */
	virtual const IConvertShapeSuite::ShapeType GetShapeType() const = 0;

	/**	Get corner effect provider Class
		@param none
		@return ClassID of corner effect type (service provider of kPathCornerService)  
	 */
	virtual const ClassID GetCornerEffectClass() const  = 0;

	/**	Get corner effect radius 
		@param none
		@return radius of corner effect (service provider of kPathCornerService)  
	 */
	virtual const PMReal& GetCornerRadius() const  = 0;

	/**	GetNumSides
		@param none
		@return number of sides of polygon for converting to 
	 */
	virtual const int32& GetNumSides() const = 0;

	/**	GetStarInset
		@param none
		@return star inset of polygon for converting to 
	 */
	virtual const int32& GetStarInset() const = 0;

};



#endif // __IConvertShapeCmdData__