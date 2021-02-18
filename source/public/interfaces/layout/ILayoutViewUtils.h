//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutViewUtils.h $
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
#ifndef __ILayoutViewUtils__
#define __ILayoutViewUtils__

#include "LayoutUIID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMRect.h"
#include "ILayoutControlData.h"
#include "IDocumentPresentation.h"


/** Layout-view related utilities */
class ILayoutViewUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTVIEWUTILS };

	/** Shows the secondary layout widget to the presentation.
		@param documentPresentation the document view that should be modified.
		*/
	virtual void ShowSplitLayoutView(IDocumentPresentation* documentPresentation) = 0;

	/** Removes the secondary layout widget from the presentation.
		@param documentPresentation the document view that should be modified.
		*/
	virtual void HideSplitLayoutView(IDocumentPresentation* documentPresentation) = 0;

	/** Toggles the split layout view mode
		@param documentPresentation the document view that should be switched.
		*/
	virtual void ToggleSplitLayoutView(IDocumentPresentation* documentPresentation) = 0;

	/** Returns kTrue if there is a secondary layout widget shown, kFalse otherwise.
		@param documentPresentation the document view that should be switched.
		@return bool16 kTrue if split layout view is shown, kFalse otherwise.
		*/
	virtual bool16 IsSplitLayoutViewShown(IDocumentPresentation* documentPresentation) const = 0;

	/** Gather all the presentations with a layout view.
		@param layoutViews OUT a K2Vector to gather a list of layout views (will return both layout views in a split layout view if both shown)
		@param exceptView IN an optional control view to avoid putting in return list, may be nil to gather all views
		@param db IN the document to collect views for, nil to collect all layout views
		*/
	virtual void GetAllLayoutViews(K2Vector<IControlView*>& layoutViews, const IControlView* exceptView, IDataBase* db) = 0;

	/** Internal use only.
		Zoom all the given layout views. Either zoom in or out based on bZoomIn parameter. Also, client may provide
		a new scale factor for the zoom if desired. If not provided, zoom occurs by one zoom level.
		@param layoutViews IN a K2Vector of layout views to zoom
		@param zoomToPoints IN a K2Vector of points in pb coordinate space to zoom on. If empty, use center of view as zoom point.
		@param bZoomIn IN a bool16 value to specify whether to zoom in (kTrue) or out (kFalse). Ignored if newScaleFactor is provided.
		@param fit Use a fit-to setting instead of a zoom percentage. 
		@see ILayoutUIUtils, GetNextZoomValue
		*/
	virtual void ZoomLayoutViews(K2Vector<IControlView*>& layoutViews, K2Vector<PBPMPoint>& zoomToPoints, bool16 bZoomIn, PMReal newScaleFactor = -1, ILayoutControlData::FitSetting fit = ILayoutControlData::kFitNone) = 0;

	/** Internal use only.
		Gather all the spread rectangles (in PasteboardCoordinates) for a given document.
		@param rectList OUT an PMRectCollection to hold the return rectangles
		@param document IN a document to collect the spread rectangles for.
		*/
	virtual void GatherSpreadRects(PMRectCollection& rectList, IDocument* document) = 0;

	/** Internal use only.
	 */
	virtual PBPMPoint TransformPointToNewSpread(const PBPMPoint& sourcePoint, const PBPMPoint& targetPoint, PMRectCollection& rectList) = 0;
};

#endif	// __ILayoutViewUtils__
