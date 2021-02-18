//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISplineUtils.h $
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
#ifndef __ISplineUtils__
#define __ISplineUtils__

#include "SplineID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IShape.h"
#include "PMPathPoint.h"
#include "PMRect.h"
#include "HitTestDragConstants.h"

class ICommand;
class IControlView;
class IPathGeometry;
class IGraphicFrameData;
class ITextModel;
class UIDList;

/** Valid values for spline curve parameter are 0 <= u <= 1.0
*/
#define kInvalidParameter -1.0


/** Utilities related to the model for splines.
	@ingroup layout_util
*/
class ISplineUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPLINEUTILS };

	/**	Filter out items that are no elibigle for making compound paths. Locked items are also filtered out.
		@param selectedItems the UIDList to operate on.
		@see IsMakeCompoundPathAllowed in IGraphicFrameData
	 */
	virtual void FilterMakeCompoundPathList( UIDList& selectedItems ) = 0;
	
	/**	Filter out items that are no elibigle for releasing compound paths. Locked items are also filtered out.
		@param selectedItems the UIDList to operate on.
		@see IsReleaseCompoundPathAllowed in IGraphicFrameData
	 */
	virtual void FilterReleaseCompoundPathList( UIDList& selectedItems ) = 0;


	/**	Given an item list, make a new item list replacing TOP splines with their main item as requested.
		@param &itemList, original item list to operate on
		@param *pNewItemList [OUT] output list, could be empty
		@param bReplaceByMainIfNeeded if kTrue, replace TOP splines with their main item. If kFalse, all items are put into pNewItemList
		@see GetMainSplineItemUID in ITOPSplineData
	 */
	virtual void StripTOPSpline( const UIDList &itemList, UIDList *pNewItemList, bool16 bReplaceByMainIfNeeded = kFalse ) = 0;

	/**	Returns a pipeline command that copies the path object and deletes all but one of its paths (it keeps the pathIndex path)
		@param pathItem the path page item to creat a command for
		@param pathIndex the path index of this item to operate on
		@return ICommand* the returned command. Caller must release.
	 */
	virtual ICommand* CreateCopySubPathPipelineCmd( const UIDRef& pathItem, int32 pathIndex ) = 0;

	/**
	This method will compute the inset bounding box of the specified Spline.
	The inset bounding box is defined as the inner bounds of the stroke further
	inset by the TextInset.

	Note that the returned inner bounds will always be at least 1 high and
	1 wide. This property allows us the MCF to not have to deal with cases
	where the stroke or inset give it no space. So in effect the MCF will not
	ever be smaller than 1x1.
	@param gfd Pointer to IGraphicFrameData interface on a spline boss.
	*/
	virtual PMRect	ComputeInnerContentBBox( const IGraphicFrameData* gfd ) = 0;


	/**
	Return the parameters/properties of use in computing the inner content
	bounds of the Spline.
	@param gfd Pointer to IGraphicFrameData interface on a spline boss.
	@param pTextInset OUT Pointer to PMRect which will be filled in with text inset
	@param pStrokeWeight OUT Pointer to PMReal which will be filled in with stroke weight
	@param pStrokeAlignment OUT Pointer to int32 which will be filled in with stroke alignment if stroke weight is non-zero, otherwise kStrokeAlignCenter.
	@param pEffectiveInnerStrokeWeight OUT Optional Pointer to PMReal which will be filled in with effective inner stroke weight
	*/
	virtual void	GetInnerContentBoundsData( const IGraphicFrameData* gfd,
											PMRect* pTextInset,
											PMReal* pStrokeWeight,
											int32* pStrokeAlignment,
											PMReal* pEffectiveStrokeWeight = nil ) = 0;

	/**
	This method will compute the minimum inner dimension for the specified
	spline data to be effective.
	@param leftTextInset
	@param topTextInset
	@param rightTextInset
	@param bottomTextInset
	@param strokeWeight
	@param strokeAlignment
	@param pSplineLeftWidth
	@param pSplineTopHeight
	@param pSplineRightWidth
	@param pSplineBottomHeight
	*/
	virtual void	ComputeMinimumInnerDimensionsFor(PMReal leftTextInset,
											PMReal topTextInset,
											PMReal rightTextInset,
											PMReal bottomTextInset,
											PMReal strokeWeight,
											int32 strokeAlignment,
											PMReal* pSplineLeftWidth,
											PMReal* pSplineTopHeight,
											PMReal* pSplineRightWidth,
											PMReal* pSplineBottomHeight) = 0;
	

	/**
	This method will compute the inset bounding box relative to the specified
	spline path bbox.
	Note that the returned inner bounds will always be at least 1 high and
	1 wide even if the calculated inner bounds are overlapping or less than one.
	This property allows us the MCF to not have to deal with cases where the
	stroke or inset give it no space. So in effect the MCF will not ever be
	smaller than 1x1. When this adaptation occurs this method returns kFalse.
	@param splinePathBBox
	@param leftTextInset
	@param topTextInset
	@param rightTextInset
	@param bottomTextInset
	@param strokeWeight
	@param strokeAlignment
	@param pInnerPathLeft
	@param pInnerPathTop
	@param pInnerRight
	@param pInnerPathBottom
	@return kTrue if the inner content bounds meet the minimm desired by the MultiColumnTextFrame, kFalse otherwise. Callers seeing kFalse may wish to call
	*/
	virtual bool16	ComputeInnerContentBounds(const PMRect& splinePathBBox,
											PMReal leftTextInset,
											PMReal topTextInset,
											PMReal rightTextInset,
											PMReal bottomTextInset,
											PMReal strokeWeight,
											int32 strokeAlignment,
											PMReal* pInnerPathLeft,
											PMReal* pInnerPathTop,
											PMReal* pInnerPathRight,
											PMReal* pInnerPathBottom) = 0;


};


#endif	// __ISplineUtils__

