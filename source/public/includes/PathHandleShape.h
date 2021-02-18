//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PathHandleShape.h $
//  
//  Owner: Jeff Argast
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
//  
//  Shared header for spline item and standoff item
//  
//========================================================================================

#pragma once
#ifndef __PathHandleShape__
#define __PathHandleShape__

#include "CHandleShape.h"

class GraphicsData;
class PMRect;
class PMPoint;
class IRasterPort;
class IGraphicsPort;
class IPathGeometry;
class IConcreteSelection;

#pragma export on

class WIDGET_DECL PathHandleShape : public CHandleShape
{
public:
	PathHandleShape(IPMUnknown *boss);

	virtual void GetControlPointPathOutlineInfo (IOutlineInfo* iOutlineInfo);

	virtual ITracker* QueryTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index);

protected:
	virtual void DrawHandlesImmediate(GraphicsData *gd, IConcreteSelection* concreteSelection, int32 flags);
	virtual void DrawPathImmediate(GraphicsData *gd, int32 flags);
	virtual PMRect GetBBoxImmediate(const PMMatrix& itoview);
	virtual bool16 HitTestHandlesImmediate(GraphicsData *gd, const PMRect &r, PointSelector *handleIndex);
	virtual bool16 HitTestPathImmediate(GraphicsData *gd, const PMRect &r);

	// Create all the anchor points
	virtual void CreateAnchorPaths( GraphicsData *gd, IConcreteSelection* concreteSelection ) ;	

	// Create the direction handle paths
	virtual void CreateDirectionHandlePaths( GraphicsData *gd, IConcreteSelection* concreteSelection ) ;

	// Create the selected anchor point path
	virtual void CreateSelectedAnchorPath (GraphicsData *gd, const PointSelector& selectedPoint, const PMReal& size);

	// Create the selected anchor point path dot
	virtual void CreateSelectedAnchorPointDot (GraphicsData *gd, const PointSelector& selectedPoint);

	// Create an anchor point path in the port
	virtual void CreateAnchorPointPath (GraphicsData *gd, const PMPoint& pt, const PMReal& size);

	// Create the center anchor point path
	virtual void CreateCenterAnchorPath( GraphicsData *gd, const PMReal& size ) ;

	// Create a direction point path in the port
	virtual void CreateDirectionPointPath (GraphicsData *gd, const PMPoint& pt);
	
	virtual void CreateControlPath (IGraphicsPort* gPort);

	// returns kTrue if the point actually exists
	virtual bool16 VerifySelectedPoint( const PointSelector& selector ) const ;


protected:
	IPathGeometry*	fPathGeometry;
};

#pragma export off

#endif
