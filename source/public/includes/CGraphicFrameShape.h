//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CGraphicFrameShape.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __CGRAPHICFRAMESHAPE__
#define __CGRAPHICFRAMESHAPE__

#include "CPathShape.h"
class IGraphicFrameData;

#pragma export on

class PUBLIC_DECL CGraphicFrameShape : public CPathShape
{
	public:
		CGraphicFrameShape(IPMUnknown *boss);
		virtual ~CGraphicFrameShape();
		
	protected:
		virtual void DrawShape(GraphicsData* gd, int32 flags);

		/** DrawShape is broken out into fill, children, and stroke. This method implements
			the fill. It issues the appropriate event dispatches, adornments, etc., and does
			the fill based on the path already in gstate.

			The gstate will be symmetric across this call, ie the gstate on exit should be
			the same as the gstate on entry.

			@param gd IN The class that provides all the drawing context.
			@param flags IN Drawing flags (IShape::*)
		*/
		virtual void DrawShape_Fill(GraphicsData* gd, int32 flags);

		/** DrawShape is broken out into fill, children, and stroke. This method implements
			the children. This takes into account any ghosting of content required and 
			eventually calls DrawHierarchy.

			The gstate will be symmetric across this call, ie the gstate on exit should be
			the same as the gstate on entry.

			@param gd IN The class that provides all the drawing context.
			@param flags IN Drawing flags (IShape::*)
		*/
		virtual void DrawShape_Hierarchy(GraphicsData* gd, int32 flags);

		/** DrawShape is broken out into fill, children, and stroke. This method implements
			the fill. It issues the appropriate event dispatches, adornments, etc., and does
			the stroke based on the path already in gstate.

			The gstate depth will be symmetric across the call but since this is the last
			operation in the chain it does not attempt to maintain gstate otherwise.

			@param gd IN The class that provides all the drawing context.
			@param flags IN Drawing flags (IShape::*)
		*/
		virtual void DrawShape_Stroke(GraphicsData* gd, int32 flags);

		virtual bool16 IsGraphicFrame() const ;
		
		// Overridden for frames that have text
		virtual PMRect GetPaintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace);
		virtual PMRect GetPrintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace, bool32 includeAdornments = kTrue);

	protected:
		IGraphicFrameData*	fFrameData;
};

#pragma export off

#endif
