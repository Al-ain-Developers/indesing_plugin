//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageUIUtils.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPageUIUtils__
#define __IPageUIUtils__

#include "SpreadUIID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "PMPoint.h"
#include "UIDRef.h"
#include "IColorData.h"
#include "IFlowFacade.h"

class IShape;
class PointSelector;
class GraphicsData;

/** Utilites for answering questions about ruler guides when there is an open document window.
	Please use the IPageUIUtils via kUtilsBoss (see Utils.h).
    <pre>Utils<IPageUIUtils>()->CalculatePageAdornmentRect( ... ) ;</pre>

	@ingroup layout_util
*/
class IPageUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEUIUTILS };

	/** Given a page item shape, calculate the location of the given adornment rects. Used for page adornments.
		@param IShape*, the page's shape interface
		@param PMMatrix, the inner to window matrix for the item.
		@param PMRectCollection& [OUT] outRectList, rects for each of the six constraints for the current key item
		@return void, the window coordinate rectangle representing the screen location of the page item adornment. kEmptyRect if none.
	*/
	virtual void CalculatePageHandleAdornmentRects(IShape* pageShape, const PMMatrix& innerToWindowMatrix, PMRectCollection& outRectList) = 0;

	virtual Flow::ConstraintIndex MapPointIndexToConstraintIndex(int32 pointIndex) = 0;

	virtual int32 MapConstraintIndexToHandleIndex(Flow::ConstraintIndex i, Flow::Constraint constraint) = 0;

	/**
	 Draw object-based page item constraints for the Object-based page layout policy
	 @param gd [IN] The graphics port to draw into
	 */
	virtual void DrawItemConstraints(GraphicsData* gd, const UIDRef& pageItem) = 0;
};


#endif	// __IPageUIUtils__
