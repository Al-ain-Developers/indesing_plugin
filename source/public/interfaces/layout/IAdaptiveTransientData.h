//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveTransientData.h $
//  
//  Owner: Sachin Singhal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IAdaptiveTransientData__
#define __IAdaptiveTransientData__

#include "IPMUnknown.h"
#include "AutoLayoutID.h"

#include "PMRect.h"
#include "UIDList.h"

/** The data structure to hold the temporary data for a particular page item while the Adaptive (Adjust) Layout is in progress.
*/
class AdapativePageItemData
{
public:
	UIDList fDependents;
	PMRect fInitialBounds, fFinalBounds, fRecommendedBounds;
	PMPoint fStartPoint, fEndPoint, fFinalStartPoint, fFinalEndPoint;
	UID fTOPUID, fSpreadUID;
	bool16 fUnlockThis, fLeftToRightBinding, fDependentsInitialised, fHasRecommendedBounds;

	AdapativePageItemData() : fDependentsInitialised(kFalse), fUnlockThis(kFalse), fTOPUID(kInvalidUID), fSpreadUID(kInvalidUID), fHasRecommendedBounds(false), fHasNewStartAndEndPointForTOP(false) {}
	~AdapativePageItemData() {}

	/**	Returns true if start and end point information pertaining to the TOP on this page item has been set.
		@return true if TOP related information has been set.
	*/
	bool16 HasNewStartAndEndPointForTOP() { return fHasNewStartAndEndPointForTOP; }

	/**	Returns the start and end point information pertaining to the TOP on this page item.
		@param	startPoint [out] starting point of the TOP.
		@param	endPoint [out] ending point of the TOP.
		@reset	reset [in] true if the TOP information is to be reset after returning the values.
	*/
	void GetStartAndEndPointForTOP(PMPoint &startPoint, PMPoint &endPoint, bool reset = false)
	{
		if (fHasNewStartAndEndPointForTOP)
		{
			startPoint = fStartBracketPoint;
			endPoint = fEndBracketPoint;
			if (reset)
				fHasNewStartAndEndPointForTOP = false;
		}
	}

	/**	Sets starting point and ending point information for the TOP on this page item.
		@param	startPoint [in] starting point of the TOP.
		@param	endPoint [in] ending point of the TOP.
	*/
	void SetStartAndEndPointForTOP(PMPoint startPoint, PMPoint endPoint)
	{
		fStartBracketPoint = startPoint;
		fEndBracketPoint = endPoint;
		fHasNewStartAndEndPointForTOP = true;
	}

	/**	Returns true if recommended final bounds has been set for this page item.
		@return true if bounds has been recommended for this page item and false otherwise.
	*/
	bool HasRecommendedBounds() { return fHasRecommendedBounds; }

	/**	Returns recommended final bounds that has been set for this page item.
		@param	reset [in] true if the recommended bounds are to be rest after returning the bounds.
		@return Bounds which have been recommended for this page item and false otherwise. These are supposed to be in spread coordinates.
	*/
	virtual PMRect GetRecommendedBounds(bool reset = false)
	{
		PMRect returnRect = fRecommendedBounds;
		if (reset)
		{
			fRecommendedBounds = PMRect();
			fHasRecommendedBounds = false;
		}
		return returnRect;
	}

	/**	Sets recommended final bounds for this page item.
		@param	The final recommended bounds for this page item. These are supposed to be in spread coordinates.
	*/
	void SetRecommendedBounds(PMRect bounds)
	{
		fRecommendedBounds = bounds;
		fHasRecommendedBounds = true;
	}

private:
	PMPoint fStartBracketPoint, fEndBracketPoint;
	bool fHasNewStartAndEndPointForTOP;
};

/** Interface to store transient page item data for Adaptive (Adjust) layout.
*/
class IAdaptiveTransientData : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IADAPTIVETRANSIENTDATA };

	/**	This is called to retrieve the data object pertaining to this particular page item. This object contains temporary page item data for Adaptive (Adjust) layout.
		@param	UID [in] The uid corresponding to which the data is to be returned.
	*/
	virtual AdapativePageItemData* GetData(UID)= 0;

	/** This is called at the very end of the processing of Adaptive (Adjust) Layout to clear out the data which anyhow is no longer relevant.
	*/
	virtual void Reset() = 0;
};

#endif	// __IAdaptiveTransientData__
