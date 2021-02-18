//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IHandleShape.h $
//  
//  Owner: jargast
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
//  Purpose of Interface:
//  IHandleShape is the shape interface for selection handles.
//  
//  IHandleShape is ONLY for drawing and hit testing of selection handles
//  It is NOT a persistant interface and should have no duties other than
//  those mentioned.
//  
//========================================================================================

#pragma once
#ifndef __IHANDLESHAPE__
#define __IHANDLESHAPE__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "GraphicsID.h"
#include "PathTypes.h"
#include "PMRect.h"
#include "UIDRef.h"	
#include "GraphicsData.h"

class IViewPort;
class IGeometry;
class PMMatrix;
class ITracker;
class IConcreteSelection;
class IOutlineInfo;
class ITip;

/**
	This interface is ONLY for drawing, inval and hit testing of selection handles.
	It is NOT a persistant interface and should have no duties other than those mentioned.
*/
class IHandleShape : public IPMUnknown
{
	public:
		/**
			Draw the selection handle of item.

			@param gd the graphics context used for drawing.
			@param concretSelection the selection boss.
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void DrawHandleShape(GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags = 0) = 0;

		/**
			Draw the path based on item's control points.

			@param gd the graphics context used for drawing.
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void DrawControlPointPath(GraphicsData* gd, int32 flags = 0) = 0;

		/**
			Check if a particular handle of the item has been hit or not within the specified area.

			@param gd the graphics context used for hit testing.
			@param r the area for checking hit test.
			@param handleIndex the index of selection handle.
			@param bDragging the flag indicating if hit test if during dragging or not.
			@return bool16 kTrue if it hits, otherwise kFalse.
		*/
		virtual bool16 HitTest(GraphicsData* gd, const PMRect &r, PointSelector* handleIndex, bool16 bDragging = kFalse) = 0;

		/**
			Check if the control point path has been hit or not. 

			@param gd the graphics context used for hit testing.
			@param r the area for checking hit test.
			@return bool16 kTrue if it hits, otherwise kFalse.
		*/
		virtual bool16 HitTestControlPointPath(GraphicsData* gd, const PMRect &r) = 0;

		/**
			Get the path information of item's control points. 

			@param iOutlineInfo the out parameter with the control point path.
			@return void.
		*/
		virtual void GetControlPointPathOutlineInfo (IOutlineInfo* iOutlineInfo) = 0;
		
		/**
			Get the bounding box by computing it in pasteboard coords and then transforming it by pbtoview.  

			@param pbtoview the matrix to transform the bounds based on pasteboard coordinates.
			@return PMRect the bounds for painting(redrawing). 
		*/
		virtual PMRect GetPaintedHandleBounds(const PMMatrix& pbtoview) = 0;

		/**
			Invalidate the appropriate region of the object in the graphics context.

			@param gd the graphics context used for invalidation.
			@param reasonForInval the ClassID defined for inval reason for handling different inval cases. 
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void Inval(GraphicsData *gd, ClassID reasonForInval = 0, int32 flags = 0) = 0;

		/**
			Query the tracker based on the given mouse position, hit test mode and selection handle index.
			
			@param layView the active layout view where mouse is on.
			@param where the mouse position based on pasteboard coordinate.
			@param selectionMode the hit test flags.
			@param index specifies the index of selection handle.
			@return ITracker* the result tracker and caller should deference it. 
		*/
		virtual ITracker* QueryTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index) = 0;
      
		/**
           Query for any tip implemented on the shape. If there is any tip on the shape then the ITip interfacePtr 
			will be returned else nil is returned in the default implementation

			@param handleIndex the index of the handle for the shape
			@return ITip* the result tip  
		*/
		virtual ITip* QueryTip(const PointSelector* handleIndex) = 0;
};


#endif