//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideDataSuite.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IGUIDEDATASUITE__
#define __IGUIDEDATASUITE__

// ----- Interface files

#include "IPMUnknown.h"
#include "IColorData.h"
#include "IGuideData.h"

// ----- ID files

#include "ShuksanID.h"	// for IID_IGUIDEDATASUITE

/** Defines the interface for a guide data suite to be used in the new selection architecture
	@ingroup layout_suite
*/
class IGuideDataSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGUIDEDATASUITE };

		// ----- Abilities

		/**	Does the selection contain guides (guides cannot be selected with anything else)
			@param none
			@return bool16 
		 */
		virtual bool16 AreGuidesSelected() const = 0;

		/**	Return a list of view threshold values for guides in the selection. Only the unique values are returned.
			@param guideList 
		 */
		virtual void GetViewThreshold(K2Vector<PMReal>& thresholdList) = 0;

		/**	Return a list of color UID values for guides in the selection. Only the unique UIDs are returned.
			@param colorIndex 
		 */
		virtual void GetColorUID(K2Vector<UID>& colorUIDList) = 0;

		/**	Return a list of guide data types for guides in the selection. Only the unique types are returned.
			@param typeList 
		 */
		virtual void GetType(K2Vector<IGuideData::GuideType>& typeList) = 0;

		/**	Return a list of guide zones for guides in the selection. Only the unique values are returned.
			@param growZoneList 
		 */
		virtual void GetGrowZone(K2Vector<PMReal>& growZoneList) = 0;


		// ----- Execution
		
		/**	Deselect guides with a view threshold below the specified value.
			@param viewTheshold - value for view threshold when guides are no longer visible.
			@return ErrorCode 
		 */
		virtual ErrorCode DeselectGuideUnderViewThreshold(PMReal viewTheshold) = 0;

		/**	Change the color of the selected guides.
			@param colorRef - UIDRef for the UID color to change the guide color.
			@return ErrorCode 
		 */
		virtual ErrorCode DoSetColor(const UID& colorUID) = 0;
		
		/**	Change the viewThreshold of the selected guides.
			@param viewTheshold - value for view threshold when guides are no longer visible.
			@return ErrorCode 
		 */
		virtual ErrorCode DoSetThreshold(const PMReal& viewTheshold) = 0;

		/**	Process commands to set the guides in the selection to the indicated guide type.
			@param type - what type of guides to set, see IGuideData
			@return ErrorCode 
		 */
		virtual ErrorCode DoSetType(IGuideData::GuideType type) = 0;

		/**	Process commands to set the guides in the selection to have the indicated grow zone.
			@param growZone - the grow zone to set, see IGuideData
			@return ErrorCode 
		 */
		virtual ErrorCode DoSetGrowZone(const PMReal& growZone) = 0;
};

#endif		// __IGUIDEDATASUITE__