//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewGuideCmdData.h $
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
#ifndef __INewGuideCmdData__
#define __INewGuideCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "IGuideData.h"
#include "GuideID.h"
//#include "PMPoint.h"
//#include "GenericID.h"

class INewGuideCmdData : public IPMUnknown {
public:
	enum { kDefaultIID = IID_INEWGUIDECMDDATA };
	// the data needed when creating a NewGuideCmd
	
	/** Catch all setter for specifying how a guide should be created.
		@param guideType [IN] specifies which type of guide to create (e.g. ruler, liquid, magnetic, etc. )
	 */
	virtual void Set(const UIDRef& parent, bool16 isHoriz, const PMReal &distance, const UID &ownerUID, 
					 bool16 isShort = kTrue, const PMReal &threshold = kDefaultViewThreshold, 
					 const int32 colorIndex = IUIColorUtils::kStockRulerGuide, const IGuideData::GuideType guideType = IGuideData::kRulerGuide) = 0;
		// set all the command data

	virtual void SetMultiple(bool16 isMultiple) = 0;
		// Set to true if the guide is part of a multiple guide command (horizontal + vertical), false (default) otherwise
		// Separate from Set method. All guide commands are either vertical or horizontal, only after appending commands
		// together is the SetMultiple used.
	
	/** Sets the type of guide. Default is kSnapping.
		@param guideType [IN] One of snapping, slicing, magnetic, etc.
	 */
	virtual void SetType(const IGuideData::GuideType guideType) = 0;
	
	/** @return Gets the type of guide. Default is kSnapping.
	 */
	virtual IGuideData::GuideType GetType() const = 0;
	
	/** Sets the size of the zone (width for vertical, height for horizontal).
	 @param size [IN] specifies the size of the zone (width for vertical, height for horizontal).
	 */
	virtual void SetLiquidGrowZoneSize(const PMReal& size) = 0;
	
	/** @return Gets the size of the zone (width for vertical, height for horizontal).
	 */
	virtual PMReal GetLiquidGrowZoneSize() const = 0;
	
	virtual void SetLocation(const PMReal& location) = 0;
	virtual PMReal GetLocation() const = 0;

	virtual const UIDRef& GetParent() = 0;
		// returns the parent of the new guide page item, this is a layer UIDRef (which is usually set to the active layer)

	virtual bool16 GetIsHoriz() const = 0;
		// return true if the guide is horizontal, otherwise it's vertical

	virtual bool16 GetIsMultiple() const = 0;
		// return true if the guide is part of a multiple guide command (horizontal + vertical), false (default) otherwise

	virtual const PMReal& GetDistance() const = 0;
		// return the distance the guide is located at

	virtual const UID& GetOwnerUID() const = 0;
			// return the id of the owner, for short guides this is the page it's located on, 
			// for long guides it's the pasteboard

	virtual const PMReal& GetThreshold() const = 0;
			// return the default the threshold when creating a new guide

	virtual const int32 GetColorIndex() const = 0;

	virtual bool16 GetIsShort() const = 0;
};



#endif // __INewGuideCmdData__
