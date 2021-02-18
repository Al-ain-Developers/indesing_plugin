//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpShape.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IGeometry.h"
#include "IGraphicsPort.h"

// General includes:
#include "CGraphicFrameShape.h"

// Project includes:
#include "BscShpID.h"


/** BscShpShape
	is responsible for drawing a (drawable) page item.
	This includes: stroke, fill, any (IHierarchy) children.  This implementation simply
	draws a grey fill, and an X through the page item then draws the (IHierarchy) 
	children.

	@ingroup basicshape
	
*/
class BscShpShape : public CGraphicFrameShape
{
	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscShpShape(IPMUnknown* boss);

		/** Destructor. */
		virtual ~BscShpShape();
		
	protected:

		/**
			Called by the parent class Draw() method.  Responsible for drawing everything
			in the bounds of this object.
			@param	gd The current drawing context.
			@param	flags The IShape drawing flags for the current drawing context.
		*/
		virtual void DrawShape(GraphicsData* gd, int32 flags);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscShpShape, kBscShpShapeImpl)

/* BscShpShape Constructor
*/
BscShpShape::BscShpShape(IPMUnknown* boss)
: CGraphicFrameShape(boss)
{
}


/* BscShpShape Destructor
*/
BscShpShape::~BscShpShape()
{
}

/*
*/
void BscShpShape::DrawShape(GraphicsData* gd, int32 flags)
{

	do {

		// Get the graphics port so we can draw to it.  The graphics
		// port is already set (by the parentClass::Draw() method) for
		// drawing in page item inner coordinates.
		if ( gd == nil )
		{
			ASSERT_FAIL("Nil GraphicsData*");
			break;
		}
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		if (gPort == nil)
		{
			ASSERT_FAIL("Nil IGraphicsPort*");
			break;
		}

		// Get the geometry for this item in inner coords.
		const PMRect r = fGeometry->GetStrokeBoundingBox();

		// Draw a background.
		// Fill the item boundary with gray & draw an 'X' (the diagonals)
		gPort->gsave();
		gPort->rectpath(r);
		gPort->setgray(0.75);
		gPort->fill();
		gPort->moveto(r.Left(), r.Top());
		gPort->lineto(r.Right(), r.Bottom());
		gPort->moveto(r.Right(), r.Top());
		gPort->lineto(r.Left(), r.Bottom());
		gPort->setlinewidth(0);
		gPort->stroke();
		gPort->grestore();

		// Draw frame and contents.
		CGraphicFrameShape::DrawShape(gd, flags);

	} while(false);

}

// End, BscShpShape.cpp.






