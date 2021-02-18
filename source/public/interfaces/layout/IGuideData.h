//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideData.h $
//  
//  Owner: Stacy Molitor
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
#ifndef __IGuideData__
#define __IGuideData__

#include "IPMUnknown.h"
#include "GuideID.h"
#include "PMReal.h"
#include "PMPoint.h"
#include "iuicolorutils.h"
#include "IZoomCmdData.h"
#include "K2Vector.h"

const PMReal kNoViewThreshold = 0.0;			// no view threshold, the guide is always drawn
const PMReal kDefaultViewThreshold = kMinZoom;
const PMReal kDefaultGuideWidth = 1.0;
const PMReal kDefaultGuideHeight = 1.0;

/** Represents properties of a ruler guide (kGuideItemBoss).
   A ruler guide is defined by it's orientation (horizontal or vertical), its distance from the origin, 
   its owner(a page id or the pasteboard), its view threshold beyond which a guide is not drawn, and 
   its color to draw the guide. 
   
   There are two types of ruler guides: 1) short guides which are drawn clipped to the 
   page dimensions; 2) long guides which extend across the entire pasteboard dimensions.  
   The guide type is determined by the owner UID.

   @ingroup layout_guide
   @see kGuideItemBoss
 */

class IGuideData : public IPMUnknown
{
	public:
		enum {kDefaultIID = IID_IGUIDEDATA};

		enum GuideType
		{
			kRulerGuide = 0,
			kLiquidGuide,
			kMagneticGuide,
			kGrowZoneGuide
		};

		/**
			Set the guide attributes.
			@param isHoriz refers to the orientation of guide(kTrue indicates horizontal guide and kFalse indicates vertical guide).
			@param distance refers to the distance from origin.
			@param ownerUID refers to the owner of a page or the pasteboard.
			@param threshold refers to the percentage beyond which a guide is not drawn.
			@param colorIndex refers to the color that draws the guide.
			@return void.
		*/

		virtual void Set(bool16 isHoriz, const PMReal &distance, const UID &ownerUID, 
			const PMReal &threshold = kDefaultViewThreshold, 
			const int32 colorIndex = IUIColorUtils::kStockRulerGuide) = 0;
		
		/**
			Change the color UID of guide.
			@param colorUID refers to the color that draws the guide.
			@return void.
		*/

		virtual void SetIsShort(bool16 isShort) = 0;

		/**
			Set location of the guide. For horizontal guide, location is X value of the middle point(X, Y) of the guide;
			for vertical guide, location is Y value of the middle point(X, Y) of the guide. 
			@param location refers to X or Y value of the middle point(X, Y).
			@return void.
		*/

		virtual void SetLocation(const PMReal& location) = 0;

		/** Sets the type of guide. Default is kRulerGuide.
		 @param guideType [IN] One of ruler, liquid, magnetic, etc.
		 */
		virtual void SetType(const GuideType guideType) = 0;
	
		/** @return Gets the type of guide. Default is kRulerGuide.
		 */
		virtual GuideType GetType() const = 0;
	
		/** Sets the size of the zone (width for vertical, height for horizontal).
		 @param size [IN] specifies the size of the zone (width for vertical, height for horizontal).
		 */
		virtual void SetLiquidGrowZoneSize(const PMReal& size) = 0;
		
		/** @return Gets the size of the zone (width for vertical, height for horizontal).
		 */
		virtual PMReal GetLiquidGrowZoneSize() const = 0;
	
		/**
			Change the orientation of the guide. For example, switch between horizontal and vertical.
			@param isHoriz refers to the orientation of guide(kTrue indicates horizontal guide and kFalse indicates vertical guide).
			@return void.
		*/

		virtual void ModifyIsHoriz(bool16 isHoriz) = 0;

		/**
			Change the distance the guide is located at. For example, move the guide.
			@param distance refers to the distance from origin.
			@return void.
		*/

		virtual void ModifyDistance(const PMReal &distance) = 0;
			
		/**
			Change the owner, a page uid for a short guide and the pasteboard for long guide.
			@param ownerUID refers to the owner of a page or the pasteboard.
			@return void.
		*/

		virtual void ModifyOwnerUID(const UID &ownerUID) = 0;
			
		/**
			Change the view threshold, this represents the percentage beyond which a guide is not drawn.
			@param ownerUID refers to the owner of a page or the pasteboard.
			@return void.
		*/

		virtual void ModifyViewThreshold(const PMReal viewThreshold) = 0;
			
		/**
			Change the color UID of guide.
			@param colorUID refers to the color that draws the guide.
			@return void.
		*/

		virtual void ModifyColorUID(const UID colorUID) = 0;

		/**
			Get the orientation of the guide.
			
			@return bool16 kTrue is horizontal guide, kFalse is vertical guide.
		*/

		virtual bool16 GetIsHoriz() const = 0;
			
		/**
			Get the distance the guide is located at.
			
			@return PMReal that is the distance the guide is located at.
		*/

		virtual PMReal GetDistance() const = 0;
		
		/**
			Get UID of the owner, a page uid for a short guide and the pasteboard for long guide.
			
			@return UID the owner, for short guides this is the page it's located on, for long guides it's the pasteboard.
		*/

		virtual UID GetOwnerUID() const = 0;
			
		/**
			Get the view threshold beyond which a guide is not drawn.
			
			@return PMReal the view percentage, kNoViewThreshold means the guide is always drawn.
		*/

		virtual PMReal GetViewThreshold() const = 0;
			
		/**
			Get the color index of the guide. DON'T use this after Anna(InDesign 2.0), USE GetColorUID() instead.
			
			@return int32 the color index.
		*/

		virtual int32 GetColorIndex_FOR_CONVERSION_ONLY() const = 0;

		/**
			Get the color UID of guide.

			@return UID the color that draws the guide.
		*/

		virtual UID GetColorUID() const = 0;
			
		/**
			Get the color UID of guide.

			@return bool16 kTrue if it's a short guide (page guide), kFalse if it's a long guide that extends across 
			the pasteboard.  This value is not stored.  It's computed based on the OwnerUID.
		*/

		virtual bool16 GetIsShort() = 0;
			
		/**
			Get top left point of the guide.

			@return PMPoint represents the top left point.
		*/

		virtual PMPoint GetTopLeftPoint() = 0;
			
		/**
			Get bottom right point of the guide.

			@return PMPoint represents the bottom right point.
		*/

		virtual PMPoint GetBottomRightPoint() = 0;
			
		/**
			Get the X value of middle point for horizontal guide or Y value of middle point(X, Y) for vertical guide.

			@return PMReal represents X or Y value of middle point(X, Y) of guide.
		*/

		virtual PMReal GetLocation() = 0;
};

DECLARE_BASE_TYPE(IGuideData::GuideType);


#endif