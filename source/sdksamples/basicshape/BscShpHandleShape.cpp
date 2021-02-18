//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpHandleShape.cpp $
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
#include "IGraphicsPort.h"
#include "IRasterPort.h"
#include "IGeometry.h"
#include "IPMFont.h"
#include "IFontInstance.h"

// General includes:
#include "AutoGSave.h"
#include "CHandleShape.h"
#include "IGraphicsUtils.h"
#include "TransformUtils.h"

// Project includes:
#include "BscShpID.h"


/** BscShpHandleShape
	is responsible for drawing a page item's selection outline and handles.
	This implementation draws the selection features in red.  The selection
	handles are the word "adobe".

	BscShpHandleShape implements IHandleSHape based on
	the partial implementation CHandleShape.

	@ingroup basicshape
	
*/
class BscShpHandleShape : public CHandleShape
{
	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscShpHandleShape(IPMUnknown* boss);

		/** Destructor. */
		virtual ~BscShpHandleShape();

	protected:

		/**
			Responsible for drawing the selection handles.  Called by the
			parent class Draw() method.  This implementation draws "Adobe" handles if
			fonts are available.  Otherwise it draws rectangular handles.
			@param gd The drawing context
			@param pathSelection Provides info about what handles or paths are selected.
			@param shapeflags IShape drawing flags.
		*/
		virtual void DrawHandlesImmediate(GraphicsData* gd, IConcreteSelection* pathSelection, int32 shapeflags);

		/**
			Responsible for drawing the selection path.  Called by the parent class 
			Draw() method.  This implementation strokes the page item with a red line.
			@param gd The drawing context.
			@param shapeflags IShape drawing flags.
		*/
		virtual void DrawPathImmediate(GraphicsData* gd, int32 shapeflags);

		/**
			Responsible for returning the bounding box of the page item including the selection handles.
			@param itoview Inner coords to drawing device (port) transform.
			@return Bounding PMRect in drawing device coordinates.
		*/
		virtual PMRect GetBBoxImmediate(const PMMatrix& itoview);

		/**
			Responsible for determining whether the selection rectangle contains a point on the path.
			@param gd The drawing context.
			@param r Rectangle describing region of hit in device (view) coords.
			@return kTrue if intersection of rect and path is not null.  kFalse otherwise.
		*/
		virtual bool16 HitTestPathImmediate(GraphicsData* gd, const PMRect& r);

		/**
			Responsible for determining whether the selection rectangle contains a point in a handle.
			@param gd The drawing context.
			@param r Rectangle describing region of hit in device (view) coords.
			@param handleIndex Used for returning information about which of the selections handles was hit.
			@return kTrue if intersection of rect and handles is not null.  kFalse otherwise.
		*/
		virtual bool16 HitTestHandlesImmediate(GraphicsData* gd, const PMRect& r, PointSelector* handleIndex);

		/**
			Responsible for determining whether the selection rectangle contains a specific handle.
			@param gd The drawing context.
			@param r Rectangle describing region of hit in device (view) coords.
			@param point Center of handle in pasteboard coords.
			@param whichPoint the point index that is being tested.
			@return kTrue if intersection of rect and handle is not null.  kFalse otherwise.
		*/
		virtual bool16 HitTestOneHandle(GraphicsData* gd, const PMRect& r, const PBPMPoint& point, PMRect::PointIndex whichPoint) const; 

	private:

		/** Draws selection handles as text to output device. (Default for this class.) */
		void DrawLabelHandles(GraphicsData*, IConcreteSelection*, int32);

		/** Draws graphics as selection handles.  This is fallback. */
		void DrawGraphicHandles(GraphicsData*, IConcreteSelection* , int32);

		/** 
			Initializes the handle data in inner coordiates and determines if graphic or label handles are used.
			All selection handle parameters are hardwired in this routine for simplicity.  Could
			come from resource, preferences, etc.
		*/
		void InitHandle();

		/** Draws selection handle text to the graphics port. */
		void ShowLabel(IGraphicsPort*, PMPoint);
	
	private:

		/** Determines whether to use text or graphic handle.  (kTrue uses label.)*/
		bool16 fUseLabel;
		/** Is the handle description current?  (kTrue is current.) */
		bool16 fHandleCurrent;		
		/** Stores the computed size of a handle in pts. */
		PMPoint fHandleDims;		
		/** Stores dist from handle top to label baseline in pts. */
		PMReal fHandleBlOffsetY;	
		
		/** 
			Controls for the text handle 
		*/
		/** Font handle text. */
		PMString fFontName;			
		/** Characters to appear as a handle. */
		WideString fLabel;			
		/** Size of handle text in pts. */
		int32 fFontSize;			

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscShpHandleShape, kBscShpHandleShapeImpl)

/* BscShpHandleShape Constructor
*/
BscShpHandleShape::BscShpHandleShape(IPMUnknown* boss) : CHandleShape(boss),
	fUseLabel(kFalse),
	fHandleCurrent(kFalse),
	fFontSize(0)
{
}

/* BscShpHandleShape Destructor
*/
BscShpHandleShape::~BscShpHandleShape()
{
}


/* DrawPathImmediate
*/
void BscShpHandleShape::DrawPathImmediate(GraphicsData* gd, int32)
{
	do {

		// Get the graphics port from GraphicsData
		// Port is assumed to already be set for inner coords.
		IGraphicsPort* graphPort = gd->GetGraphicsPort();
		if ( graphPort == nil )
		{
			ASSERT_FAIL("Nil IGraphicsPort*");
			break;
		}

		// Set the color path color to red
		AutoGSave autoGSave(graphPort);
		graphPort->setrgbcolor(PMReal(1.0), PMReal(0.0), PMReal(0.0));

		// Set the path in the port to the item's bounding box in inner coords.
		graphPort->rectpath(fGeometry->GetStrokeBoundingBox());

		// Stroke the bounding box path
		graphPort->setlinewidth(0);
		graphPort->stroke();
	} while (false);
}

/* DrawHandlesImmediate
*/
void BscShpHandleShape::DrawHandlesImmediate(GraphicsData* gd, IConcreteSelection*, int32 flags)
{

	// Reset the handle data if it's not current
	if ( fHandleCurrent != kTrue )
	{
		this->InitHandle();
	}

	// Draw a lable or graphic as the handle
	if (fUseLabel == kTrue)
	{
		this->DrawLabelHandles(gd, nil, flags);
	}
	else
	{
		this->DrawGraphicHandles(gd, nil , flags);
	}
}


/* DrawGraphicHandles
*/
void BscShpHandleShape::DrawGraphicHandles(GraphicsData* gd, IConcreteSelection* , int32 flags)
{
	// Get pointers to the ports for creating paths and drawing them
	IGraphicsPort* graphPort = gd->GetGraphicsPort();
	IRasterPort* rasPort = gd->GetRasterPort();
	if ( (graphPort==nil) || (rasPort==nil) )
	{
		ASSERT_FAIL("Nil IGraphicsPort* or IRasterPort*");
		return;
	}

	// The handles will be located on the bounding box corners and midpoints (inner coords.)
	PMRect	myBounds = fGeometry->GetStrokeBoundingBox();
		
	// Create the square handle paths: corners, midpoints, center
	graphPort->newpath();
	PMPoint point = myBounds.GetCenter();
	Utils<IGraphicsUtils>()->CreateAnchorPointPath(
										rasPort,			// Port containing xform from "source" to drawing device.
										graphPort,			// Port into which square is drawn in "source" coords.
										point,				// "Source" location for center of square. (Inner coords.)
										fHandleDims.X(),	// Size of square.
										kFalse				// Shift fractional pixels down and right. (true=up and left)
										);
	for (int32 i = 0; i < 8; i++)
	{
		point = myBounds.GetPoint(PMRect::IndexToPointIndex(i));
		Utils<IGraphicsUtils>()->CreateAnchorPointPath(rasPort, graphPort, point, fHandleDims.X(), kFalse);
	}

	// Fill the handles
	graphPort->fill();
}


/* DrawLabelHandles
*/
void BscShpHandleShape::DrawLabelHandles(GraphicsData* gd, IConcreteSelection* , int32 flags)
{
	do {

		// Get pointers to the ports
		IGraphicsPort* graphPort = gd->GetGraphicsPort();
		if ( graphPort == nil )
		{
			ASSERT_FAIL("Nil IGraphicsPort*");
			break;
		}

		// Prepare for drawing text: set the color, opacity, typeface, and size in the port.
		InterfacePtr<IFontMgr> fontMgr (GetExecutionContextSession(), UseDefaultIID());
		if ( fontMgr == nil )
		{
			ASSERT_FAIL("Nil IFontMgr*");
			break;
		}
		InterfacePtr<IPMFont> font (fontMgr->QueryFont(fFontName));
		if ( font == nil )
		{
			ASSERT_FAIL("Nil IPMFont*");
			break;
		}

		// Set the port attributes for making the text handles
		AutoGSave autoGSave(graphPort);
		graphPort->setrgbcolor(PMReal(1.0), PMReal(0.0), PMReal(0.0));
		graphPort->setopacity (PMReal(0.5), kFalse);
 		graphPort->selectfont(font, fFontSize);
		graphPort->newpath();

		// Create the handle paths: corners, mid points, center of stroke bbox
		PMRect	myBounds = fGeometry->GetStrokeBoundingBox();
		PMPoint point = myBounds.GetCenter();
		this->ShowLabel(graphPort, point);
		for (int32 i = 0; i < 8; i++)
		{
			point = myBounds.GetPoint(PMRect::IndexToPointIndex(i));
			this->ShowLabel(graphPort, point);
		}
	} while (false);
}


/* ShowLabel
*/
void BscShpHandleShape::ShowLabel(IGraphicsPort* graphPort, PMPoint labelCenter)
{
	// Can't do anyting without the graphics port
	if (graphPort == nil)
	{
		ASSERT_FAIL("Nil IGraphicsPort*");
		return;
	}
	
	// Compute the (left,baseline) starting point of the handle text
	PMPoint labelTextStart(0,0);
	labelTextStart.X(labelCenter.X() - fHandleDims.X()/2);
	labelTextStart.Y(labelCenter.Y() + fHandleBlOffsetY);

	// Draw the text in the port
	graphPort->show(labelTextStart.X(), labelTextStart.Y(), fLabel.NumUTF16TextChars(), fLabel.GrabUTF16Buffer(nil));
}


/* GetBBoxImmediate
*/
PMRect BscShpHandleShape::GetBBoxImmediate(const PMMatrix& itoview)
{

	// Get the stroke bounding box in inner coords
	PMRect bounds = fGeometry->GetStrokeBoundingBox();

	// Use saved handle dimensions if possible 
	if ( fHandleCurrent != kTrue )
	{
		// Compute the size of the handles
		InitHandle();
	}

	// Must have at least a line to add handles.
	if ( bounds.Width() != 0 || bounds.Height() != 0 )
	{
		// Add the size of the handles to the stroke bounding box.
		bounds.Inset(-fHandleDims.X()/2, -fHandleDims.Y()/2);
	}

	// Transform the bounds. (Typically into the drawing device {view} coords.)
	itoview.Transform(&bounds);

	return bounds;

}


/* HitTestHandlesImmediate
*/
bool16 BscShpHandleShape::HitTestHandlesImmediate(GraphicsData* gd, const PMRect& hitRect, PointSelector* handleIndex)
{
	// Create a rectangle from the bounds (inner coords.)
	// Use the bounds to iterate over the 8 boundary points.
	PMRect	bounds = fGeometry->GetStrokeBoundingBox();
	for (int32 i = 0; i < 8; i++)
	{
		// Get the coords for this handle point in inner coords and convert to pasteboard coords
		PMRect::PointIndex ptIndex =  PMRect::IndexToPointIndex( i );
		PMPoint	point = bounds.GetPoint( ptIndex ) ;
		::TransformInnerPointToPasteboard( fGeometry, &point ) ;
		
		// Test to see if this point lies in the area of the hit
		if ( this->HitTestOneHandle( gd, hitRect, point, ptIndex ) )
		{
			handleIndex->PointIndex( i ) ;
			handleIndex->PathIndex( 0 ) ;
			handleIndex->Selector( kAnchorPt ) ;
			return kTrue;
		}
	}
	return kFalse;
}

/* HitTestOneHandle
	hitRect is in drawing device (window) coords.  point is in pasteboard coords.  
	This makes for a little more work because point (technically) must 
	be in inner coordinates before it can be inset for the handle dimensions.  
	Admittedly, this is belt and suspenders because it's unlikely there
	would be a rotation, scale, or skew transform between the two systems.
*/
bool16 BscShpHandleShape::HitTestOneHandle( GraphicsData* gd, const PMRect& hitRect, const PBPMPoint& handleMidPt, PMRect::PointIndex whichPoint) const
{
	// Transform the test point to inner coordinates. 
	PMPoint innerHandleMidPt = handleMidPt;
	::TransformPasteboardPointToInner(fGeometry, &innerHandleMidPt); 
	
	// Create a rectangle of zero area at the handle center point (inner coords.)	
	PMRect handleRect(innerHandleMidPt);

	// Add the size of the handles.
	handleRect.Inset(-fHandleDims.X()/2, -fHandleDims.Y()/2);

	// Transform (in 2 steps) the rectangle to drawing device (window, view) coords.
	::TransformInnerRectToPasteboard(fGeometry, &handleRect);
	const PMMatrix&	theMatrix = gd->GetContentToViewMatrix();		// PB to view
	theMatrix.Transform( &handleRect );					

	// If the handle rectangle intersects with the hit rectangle, return kTrue
	return ::Intersect( hitRect, handleRect );
}


/* HitTestPathImmediate
*/
bool16 BscShpHandleShape::HitTestPathImmediate(GraphicsData* gd, const PMRect& hitRect)
{
	// Set the bbox geometry (inner coords) in the port...
	IGraphicsPort* graphPort = gd->GetGraphicsPort();
	if (graphPort == nil)
	{
		ASSERT_FAIL("Nil IGraphicsPort*");
		return kFalse;
	}
	graphPort->rectpath(fGeometry->GetStrokeBoundingBox());

	//... so we can use the raster port to find out if hit rectangle includes the path
	IRasterPort* rPort = gd->GetRasterPort();
	bool16 isHit = rPort->instroke(hitRect);
	
	// Clean up by clearing bbox from the port
	graphPort->newpath();

	// The center point can be used for selection, so test it too. 
	if (!isHit)
	{
		// Compute the center point of the bbox & xform to pasteboard coords for comparison
		PMRect	bounds = fGeometry->GetStrokeBoundingBox();
		PMPoint	centerPoint = bounds.GetCenter();
		::TransformInnerPointToPasteboard( fGeometry, &centerPoint) ;
		
		// Test the center point just like a handle
		isHit = this->HitTestOneHandle(gd, hitRect, centerPoint, PMRect::kCenter);
	}	

	return isHit;
}


/* InitHandle
*/
void BscShpHandleShape::InitHandle()
{
	fHandleCurrent = kFalse;
	fUseLabel = kFalse;
		
	// Try to initialize the parameters for the label handle
	do {	// false loop

		// Get the label properties
		fLabel = WideString("Adobe");
		fFontSize = 12;
		fFontName = "Osaka";
		
		// The font manager is used to get the font name and to make an instance of the font.
		InterfacePtr<IFontMgr> fontMgr (GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil)
		{
			ASSERT_FAIL("Nil IFontMgr*");
			break;
		}
			
		// Using the name, get the font so we can make an instance.  If none is available, just exit.
		IPMFont* tempFont = fontMgr->QueryFont(fFontName);
		if (tempFont == nil)
		{
			// Ok, the desired font name is not available.  Get the default and use that.
			fFontName = fontMgr->GetDefaultFontName();
			tempFont = fontMgr->QueryFont(fFontName);
			if (tempFont == nil)
			{
				ASSERT_FAIL("Default font not available.");
				break;
			}
		}
		InterfacePtr<IPMFont> labelFont (tempFont); 		// Get automatic Release() of IPMFont interface.
		
		// Set a font matrix with scaling for the size we intend to use.
		PMMatrix matrix(	PMReal(fFontSize),	0.0, 
							0.0, 				PMReal(fFontSize), 
							0.0, 				0.0 
						);
						
		// Create an instance of the font so we have access to the glyphs.
        InterfacePtr<IFontInstance> fontInst(fontMgr->QueryFontInstance(labelFont, matrix));
		if (fontInst == nil)
		{
			// Font was available, so we should be able to make an instance.
			ASSERT_FAIL("Nil IFontInstance*");
			break;
		}

		// Now measure the length of our string using the glyphs from the font.
        PMReal width, height;
        fontInst->MeasureWText(fLabel.GrabUTF16Buffer(nil), fLabel.NumUTF16TextChars(), width, &height);

		// Set the property for the label string dimensions.
        fHandleDims.X(width);
		fHandleDims.Y(height);

		// If we don't get a height, use the ascender height
		// See Adobe Technical Note #5004, "Adobe Font Metrics File Format Specification"
        if(height == 0.0)
        {
			// From top of ascender to bottom of descender
        	fHandleDims.Y(fontInst->GetAscent() + fontInst->GetDescent());
		}

		// Compute the offset from the handle Y midpoint to the label text Y baseline
		fHandleBlOffsetY = fHandleDims.Y()/2 - fontInst->GetDescent();

		// Text handles are fully initialized
 		fUseLabel = kTrue;
			
	} while(false);
	
	// Couldn't initialize the text parameters, so use the square graphic handles.
	if ( fUseLabel == kFalse )
	{
        fHandleDims.X(PMReal(4.0));
		fHandleDims.Y(fHandleDims.X());
		fHandleBlOffsetY = 0.0;
	}
	
	// Everthing's initialized
	fHandleCurrent = kTrue;
}

// End, BscShpHandleShape.cpp.






