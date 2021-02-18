//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveHelper.h $
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
//  Copyright 2018 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any. The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IAdaptiveHelper__
#define __IAdaptiveHelper__

#include "IPMUnknown.h"
#include "AutoLayoutID.h"
#include "UIDList.h" 
#include "ErrorUtils.h"
#include "IXPAttributeSuite.h"

//Move to AdaptiveCore
#define NORMAILZE_ERROR(err)	if(err == kItemDoesNotIntersectBoundsError || err == kItemTooSmallError || err == kUnableToSetBoundingBoxError)	\
								{	ErrorUtils::PMSetGlobalErrorCode(kSuccess); err = kSuccess;	}
#define SHOW_ERROR(err, msg)	if (err != kSuccess) \
									ASSERT_FAIL(msg);
#ifdef DEBUG
#define HANDLE_ADAPTIVE_ERR(err, msg) NORMAILZE_ERROR(err)	\
										SHOW_ERROR(err, msg);
#else 
#define HANDLE_ADAPTIVE_ERR(err, msg) NORMAILZE_ERROR(err);
#endif

enum OptionsFlag {
	kDefaultSettings = 0,
	kMaintainAspectRatioForNonRectangular = 1,
	kResizeIrrespectiveOfAspectRatio = 2,
};

class IAdaptiveHelper : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IADAPTIVEHELPER };

	/**	The Adaptive layout adjustment happens on the basis of bounds in spread coordinates. This is a simple utility which gives relevant bounds.
		@param pageItemRef	IN	The reference to the page item for which the bounds are to be returned.
		@return	bounds of the page item in spread coordinates.
	*/
	virtual PMRect GetBoundsForPageItem(UIDRef pageItemRef) = 0;

	/**	Based on the initial bounds and some optional controllable options give the final recommended bounds.
		@param pageItemRef		IN	The reference to the page item for which the bounds are to be returned.
		@param initialBounds	IN	The bounds of the page item before any change in the layout took place.
		@param options			IN	The options with which the calculation is to be done. The options are build up of values from OptionsFlag.
		@return	final bounds of the page item in spread coordinates.
	*/
	virtual PMRect GetFinalBoundsForPageItem(const UIDRef& pageItemRef, const PMRect& initialBounds, const uint32& options = 0) = 0;

	/**	This API is used by page item to set the recommended bounds on the other page item. e.g. a page item may want to decide the final bounds for its children. 
		This would cause any subsequent call to GetFinalBoundsForPageItem() to return these bounds.
		@param pageItemRef			IN	The reference to the page item for which the final bounds are to be set.
		@param recommendedBounds	IN	The bounds to be set as the final bounds.
	*/
	virtual void SetRecommendedBoundsForPageItem(UIDRef pageItemRef, PMRect recommendedBounds) = 0;

	/**	Returns whether the hidden objects are to be adjusted or not. A page item should generally follow this but in cases it may choose to ignore the flag.
		@return	kTrue if the hidden items are to be adjusted.
	*/
	virtual bool16 ShouldHandleHidden() = 0;

	/**	Returns whether the locked objects are to be adjusted or not. A page item should generally follow this but in cases it may choose to ignore the flag.
		@return	kTrue if the locked items are to be adjusted.
	*/
	virtual bool16 ShouldHandleLocked() = 0;

	/**	Returns whether the text is to be adjusted or not. A page item should generally follow this but in cases it may choose to ignore the flag.
		@return	kTrue if the text is to be adjusted.
	*/
	virtual bool16 ShouldHandleText() = 0;

	/**	Returns whether the aspect ratio is to be maintained for the non rectangular objects. A page item should generally follow this but in cases it may choose to ignore the flag.
		@return	kTrue if the aspect ratio is to be maintained for the non rectangular objects.
	*/
	virtual bool16 ShouldMaintainAspectRatioForNonRectangularPI() = 0;

	/**	Returns whether the aspect ratio is to be maintained for the page item being passed.
		@param pageItemRef	IN	The reference to the page item.
		@return	kTrue if the aspect ratio is to be maintained for the said page item.
	*/
	virtual bool16 ShouldMaintainAspectRatioForPI(UIDRef pageItemRef) = 0;

	virtual void RegisterMaxFontScaleOf(UID uid, PMReal fontScale) = 0;
	virtual PMReal GetBestPossibleTextScaleFactor(const UIDRef uidRef, const PMReal& hScale, const PMReal& vScale) = 0;
	virtual PMReal GetFontScale(UID itemUID) = 0;

	virtual bool16 LiesInsideMargin(const UIDRef& pageItemRef, const PMRect& initialBounds) = 0;

	virtual ErrorCode AdjustEffects(const UIDList& itemList, const PMRect& initialBounds, const PMRect& finalBounds) = 0;
	virtual PMPoint GetMinSizeOfObject(UIDRef pageItemRef) = 0;
	virtual PMRect GetRelativeFinalBounds(PMRect initialBounds, PMRect initialReferenceBounds, PMRect finalReferenceBounds) = 0;

	virtual PMReal GetMaxAllowedFontSize() = 0;
	virtual PMReal GetMinAllowedFontSize() = 0;
	virtual void PreprocessText(UIDRef uidRef) = 0;
	virtual UID GetSpreadUID(UIDRef pageItemUID) = 0;
};


#endif	// __IAdaptiveHelper__
