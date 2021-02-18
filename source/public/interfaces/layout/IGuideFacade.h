//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideFacade.h $
//  
//  Owner: Bob Freeman
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
#ifndef __IGuideFacade__
#define __IGuideFacade__

// ----- Interfaces -----
#include "Utils.h"
#include "IGuideData.h"

// ----- ID.h files -----
#include "GuideID.h"

namespace Facade
	{
	/** A high level API for dealing with Guide.  To use this Facade, include
	    this header file and use the following example syntax:
	    result = Utils<Facade::IGuideFacade>()->SetGuideColor( ... );

	    @author Paul Sorrick
	*/
	class IGuideFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IGUIDEFACADE };
		
		static const bool16 kVerticalGuide = kFalse;
		static const bool16 kHorizontalGuide = kTrue;

		/**	Sets the guide orientation for one or more guides.
		
			@param guides - a list of guides to change the orientation of.
			@param orientation - Vertical (kFalse) or Horizontal (kTrue). 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetGuideOrientation(const UIDList& guideList, const bool16& orientation) = 0;

		/**	Sets the guide color for one or more guides.
		
			@param guides - a list of guides to change the color on.
			@param color - The UID of the UI color to change the color. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetGuideColor(const UIDList& guideList, const UID& colorUID) = 0;

		/**	Sets the guide color for one or more guides. Default value is kDefaultViewThreshold, or 0.05 (i.e. guides always visible since 0.05% is min zoom) 
			1.0 would set the threshold to 100%
		
			@param guides - a list of guides to change the view threshold for.
			@param threshold - the view threshold to set. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetGuideViewThreshold(const UIDList& guideList, const PMReal& threshold) = 0;

		/**	Sets the guide color for one or more guides.
		
			@param guides - a list of guides to change the type of.
			@param guideType - The type to change the guides to. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetGuideType(const UIDList& guideList, const IGuideData::GuideType guideType) = 0;

		/**	Sets the guide grow zone for one or more guides.
		
			@param guides - a list of guides to change the zone for.
			@param zone - The grow zone to change the guides to. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetGuideGrowZone(const UIDList& guideList, const PMReal& zone) = 0;



		/**	Gets the guide orientation for a given guide--Vertical (kFalse) or Horizontal (kTrue)
		
			@param guideRef - UIDRef for the guide (kGuideItemBoss)
			@return orientation - Vertical (kFalse) or Horizontal (kTrue). 

			@return ErrorCode - result of the operation.
		 */
		virtual bool16 GetGuideOrientation(const UIDRef& guideRef) const = 0;

		/**	Gets the guide color for a given guide.
		
			@param guideRef - UIDRef for the guide (kGuideItemBoss)
			@return UID - UID of the UI Color that is set. 
		 */
		virtual UID GetGuideColor(const UIDRef& guideRef) const = 0;

		/**	Gets the guide threshold for a given guide.
		
			@param guideRef - UIDRef for the guide (kGuideItemBoss)
			@return PMReal - The view threshold for the guide. 
		 */
		virtual PMReal GetGuideViewThreshold(const UIDRef& guideRef) const = 0;

		/**	Gets the guide type for a given guide.
		
			@param guideRef - UIDRef for the guide (kGuideItemBoss)
			@return IGuideData::GuideType - The type of the guide.
		 */
		virtual IGuideData::GuideType GetGuideType(const UIDRef& guideRef) const = 0;

		/**	Gets the guide grow zone for a given guide.
		
			@param guideRef - UIDRef for the guide (kGuideItemBoss)
			@return PMReal - The grow zone of the guide.
		 */
		virtual PMReal GetGuideGrowZone(const UIDRef& guideRef) const = 0;
	};
}

#endif // __IGuideFacade__

