//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CHandleShape.h $
//  
//  Owner: Jack Kirstein
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
#ifndef __CHandleShape__
#define __CHandleShape__

#include "IConcreteSelection.h"
#include "IHandleShape.h"
#include "GraphicsID.h"
#include "HelperInterface.h"
#include "PMMatrix.h"
#include "IAdornmentHandleShape.h"

class IGraphicsPort;
class IRasterPort;
class IPageItemAdornmentList;
class IHierarchy;

#pragma export on
class WIDGET_DECL CHandleShape : public IHandleShape
{
public:
	CHandleShape(IPMUnknown *boss);

	virtual void DrawHandleShape(GraphicsData* gd, IConcreteSelection* concreteSelection, int32 shapeflags);
	virtual void DrawControlPointPath(GraphicsData* gd, int32 shapeflags);

	virtual bool16 HitTest(GraphicsData* gd, const PMRect &r, PointSelector* handleIndex, bool16 bDragging);
	virtual bool16 HitTestControlPointPath(GraphicsData* gd, const PMRect &r);

	virtual void GetControlPointPathOutlineInfo (IOutlineInfo* iOutlineInfo);

	virtual PMRect GetPaintedHandleBounds( const PMMatrix& theMatrix);
	virtual void Inval(GraphicsData *gd, ClassID reasonForInval, int32 shapeflags);

	virtual ITracker* QueryTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index);
	
	virtual ITip* QueryTip(const PointSelector* handleIndex);
protected:
		// sub classes need to override all of these, but NOT the above methods unless you DON'T want text frame behavior
	virtual void DrawHandlesImmediate(GraphicsData *gd, IConcreteSelection* concreteSelection, int32 shapeflags) = 0;
	virtual void DrawPathImmediate(GraphicsData *gd, int32 shapeflags) = 0;
	virtual PMRect GetBBoxImmediate(const PMMatrix& itoview) = 0;
	virtual bool16 HitTestHandlesImmediate(GraphicsData *gd, const PMRect &r, PointSelector *handleIndex) = 0;
	virtual bool16 HitTestPathImmediate(GraphicsData *gd, const PMRect &r) = 0;

	// utilities -- the virtual one CAN be overridden, but rarely are (exception: standoffs)
	virtual void SetHandleColor( GraphicsData* gd, UID layerUID );
	virtual bool16 HitTestOneHandle( GraphicsData* gd, const PMRect &r, const PMPoint& point, PMRect::PointIndex whichPoint ) const ;

	virtual void TextFrameHandlesPath( GraphicsData* gd, int32 textflags, const PMPoint& pt1, const PMPoint& pt2);
	virtual void DrawTextFrameHandles(GraphicsData *gd, int32 shapeflags, int32 textflags);
	virtual bool16 HitTestTextFrameHandles(GraphicsData *gd, const PMRect &r, PointSelector *handleIndex, int32 textflags);
//	virtual void GetTextFrameHandlePositions(PMPoint *point1, PMPoint *point2);
	virtual void AddTextFrameHandleWidth (const PMMatrix& theMatrix, PMRect* itemBounds) const;
	virtual ITracker* QueryTextFrameTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index);

	bool16 HandlesDisabled (GraphicsData *gd, int32 shapeflags);

	bool16 HasContent(); // returns ktrue if the item has one or more children

protected:
	// helper methods to access the adornments
	void DrawAdornments( IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags);
	void DrawAdornmentControlPointPath(IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, int32 flags);
	bool16 HitTestAdornment(IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, const PMRect &r, PointSelector* handleIndex, bool16 bDragging);
	bool16 HitTestAdornmentControlPointPath(IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, const PMRect &r);
	void GetPaintedAdornmentBounds(IAdornmentHandleShape::AdornmentDrawOrder drawOrder, const PMMatrix& pbtoview, PMRect* handleRect);
	ITracker* QueryAdornmentTracker
		(IAdornmentHandleShape::AdornmentDrawOrder drawOrder, IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index);

protected:
	IGeometry*	fGeometry; // Never nil
	IPageItemAdornmentList*	fAdornmentList; // may be nil
	
	PMReal fHandleRed;
	PMReal fHandleGreen;
	PMReal fHandleBlue;

	
private:

	UID		fTextFrameUID;

	
DECLARE_HELPER_METHODS()
};

#pragma export off
#endif