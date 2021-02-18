//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CShape.h $
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
//  
//  RESTRICTED FILE
//  
//========================================================================================

#pragma once
#ifndef __CShape__
#define __CShape__

#include "IShape.h"
#include "IAdornmentShape.h"
#include "PMMatrix.h"
#include "TransformTypes.h"
#include "HelperInterface.h"

class IViewPort;
class IGraphicsPort;
class ICallback;
class IPageItemCache;
class IHierarchy;
class IGeometry;
class IHandleShape;
class IPageItemAdornmentList;

#pragma export on

class PUBLIC_DECL CShape : public IShape
{
	public:

		CShape(IPMUnknown *boss);
		virtual ~CShape();

		// CShape provides a default implementation for ProcessDrawShape that sends out draw events
		// (kDrawShapeMessage, kBeginShapeMessage, kEndShapeMessage), sets XOR or not
		// and then calls either DrawShape.  In general, shapes should
		// override DrawShape but not ProcessDrawShape.
		virtual void ProcessDrawShape(GraphicsData* gd, int32 flags);
		
		// This method grabs the geometry and transforms the boundingbox into device space
		// then returns the result. 
		virtual PMRect GetPaintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace);

		// return the bbox of the item + printing adornments
		virtual PMRect GetPrintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace, bool32 includeAdornments = kTrue);

		// call callbackInfo->callback for each item in this shape's hierarchy
		virtual void IterateShapeDrawOrder_(const PMMatrix *xform, ICallback *callbackInfo, int32 flags);
	
		// The CShape implementation simply invals the result of GetPaintedBBox.
		virtual void Inval(GraphicsData* gd, ClassID reasonForInval, int32 flags);
		
	protected:
		// If you want your shape to do anything, override DrawShape.  The default draws 
		// an Xbox that fits the bbox returned from IGeometry.
		virtual void DrawShape(GraphicsData* gd, int32 flags);
		
		// A helper method provided for those CShape decendents that are part of
		// objects having children.  DrawHierarchy iterates over the children shapes
		// and calls draw. The default implementations of Draw and DrawShape do not
		// call DrawHierarchy.
		virtual void DrawHierarchy(GraphicsData* gd, int32 flags);
		
		// Another helper methods for those objects that have children.  
		virtual void IterateDrawOrderHierarchy(const PMMatrix *xform, ICallback *callbackInfo, int32 flags);


	
		// boolean checks
		virtual bool16 IsDynamic(int32 flags);
		virtual bool16 IsPatientUser(int32 flags);
		virtual bool16 IsPrinting(int32 flags);
		virtual bool16 ShapeDisabled (GraphicsData *gd, int32 flags);

		//Draws the specified page item adornments
		virtual void DrawPageItemAdornments( GraphicsData *, int32, 
											IAdornmentShape::AdornmentDrawOrder);
		virtual void UnionPageItemAdornmentPaintedBBox(PMRect &, const PMMatrix& innertoview);
		virtual void UnionPrintingPageItemAdornmentPaintedBBox(PMRect &, const PMMatrix& innertoview);

		virtual void InvalPageItemAdornments (IAdornmentShape::AdornmentDrawOrder, GraphicsData* gd, ClassID reasonForInval, int32 flags);
		
		bool16			IsCacheValid() const;

		IDataBase *fDB;

		IPageItemCache*	fPageItemCache;
		
		// The following interfaces are cached for performance reasons.  
		// Note not all objects have a path handle shape
		IHierarchy*				fHierarchy;
		IGeometry*				fGeometry;
		IHandleShape*			fHandleShape;
		IHandleShape*			fPathHandleShape;
		IPageItemAdornmentList*	fAdornmentList;
		
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
