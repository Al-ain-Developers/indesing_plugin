//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkAdornmentShape.cpp $
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
#include "IAdornmentShape.h"
#include "IGeometry.h"
#include "IGraphicsPort.h"
#include "IHierarchy.h"
#include "IInterfaceColors.h"
#include "IShape.h"
#include "IViewPortAttributes.h"
#include "ICusDtLnkFacade.h"
// General includes:
#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "TransformUtils.h"
#include "Utils.h"
#ifdef DEBUG
#include "DebugClassUtils.h"
#endif

// Project includes:
#include "CusDtLnkID.h"


/** Implementation of IAdornmentShape to decorate custom datalinked container page 
	items
	@ingroup customdatalink
*/
class CusDtLnkAdornmentShape : public CPMUnknown<IAdornmentShape>
{
	public:
		/** Constructor.
			@param boss
		*/
		CusDtLnkAdornmentShape(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~CusDtLnkAdornmentShape();	
		
		/** See IAdornmentShape::GetDrawOrderBits
		 */
		virtual AdornmentDrawOrder	GetDrawOrderBits();

			/** See IAdornmentShape::Draw
		 */
		virtual void				DrawAdornment
			(
				IShape* iShape, 
				AdornmentDrawOrder drawOrder, 
				GraphicsData* gd, 
				int32 flags
			);
	
		/** See IAdornmentShape::GetPaintedBBox
		 */
		virtual PMRect				GetPaintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds, // This is the painted bounds of the owning page item
				const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
			);

		/** See IAdornmentShape::GetPrintedBBox
		 */
		virtual PMRect				GetPrintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds, // This is the printed bounds of the owning page item
				const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
			);

		/** See IAdornmentShape::AddToContentInkBounds
		 */
		virtual void				AddToContentInkBounds
			(
				IShape* iShape, 
				PMRect* inOutBounds
			);
		/** See IAdornmentShape::GetPriority
		 */
		virtual PMReal				GetPriority();

			/** See IAdornmentShape::Inval
		 */
		virtual void				Inval
			(
				IShape* iShape, 
				AdornmentDrawOrder drawOrder, 
				GraphicsData* gd, 
				ClassID reasonForInval, 
				int32 flags
			);

		/** See IAdornmentShape::WillPrint
		 */
		virtual bool16				WillPrint();

		/** See IAdornmentShape::WillDraw
		 */
		virtual bool16				WillDraw
			(
				IShape* 			iShape,
				AdornmentDrawOrder	drawOrder,	
				GraphicsData*		gd,
				int32				flags
			);

		/** See IAdornmentShape::HitTest
		*/
		virtual bool16 HitTest 
			( 
				IShape*				  iShape,         // The owning page item 
				AdornmentDrawOrder    adornmentDrawOrder,    // In case this adornment is used more than once 
				IControlView *		layoutView,
				const PMRect&         r 
			){ return kFalse; }

//protected:
	//bool16 isToDraw(IShape* iShape);
};

/*
*/
CREATE_PMINTERFACE(CusDtLnkAdornmentShape, kCusDtLnkAdornmentShapeImpl)

/*
*/
CusDtLnkAdornmentShape::CusDtLnkAdornmentShape(IPMUnknown* boss) : CPMUnknown<IAdornmentShape>(boss)
{
}

/*
*/
CusDtLnkAdornmentShape::~CusDtLnkAdornmentShape()
{
}

/*
*/
IAdornmentShape::AdornmentDrawOrder CusDtLnkAdornmentShape::GetDrawOrderBits()
{
	return kAfterEndShape; // After everything so transparency on item won't affect this adornment
}

/*
*/
void CusDtLnkAdornmentShape::DrawAdornment(IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, 
			GraphicsData* gd, int32 flags)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAdornmentShape::Draw\n");

	do {
		
		ASSERT(drawOrder == kAfterEndShape);
		if (drawOrder != kAfterEndShape) {
			break;
		}

		if (flags & IShape::kPrinting) {
			break;
		}
		UIDRef shapeUIDRef =::GetUIDRef(iShape);
		if(!Utils<ICusDtLnkFacade>()->NeedsOurAdornment(shapeUIDRef)) {
			TRACEFLOW(kCusDtLnkPluginName, 
				"WARNING: adornment on shape (UID=%d) that doesn't need it\n", shapeUIDRef.GetUID().Get());
			break;
		}
		ASSERT(gd);
		if(!gd) {
			break;
		}
		// Set up the port.
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		ASSERT(gPort);
		if (!gPort) {
			break;
		}	
		
		AutoGSave autoGSave(gPort);
		InterfacePtr<IGeometry> geometry(iShape, UseDefaultIID());
		ASSERT(geometry);
		if(!geometry) {
			break;
		}
		PMRect boundsRect = geometry->GetStrokeBoundingBox();
		gPort->newpath();
		PMReal left = boundsRect.Left();
		PMReal right = boundsRect.Right();
		PMReal top = boundsRect.Bottom() - 10.0;
		PMReal bottom = boundsRect.Bottom();
		// Fill a red bar at base of image
		RealAGMColor col(1.0,0.0,0.0);
		gPort->setrgbcolor( col.red, col.green, col.blue );
		gPort->moveto(left,top);
		gPort->lineto(right,top);
		gPort->lineto(right,bottom);
		gPort->lineto(left,bottom);
		gPort->closepath();
		gPort->fill();
	} while(false);


}

/* Returns the bounds of the adornment in view co-ordinates.
*/
PMRect CusDtLnkAdornmentShape::GetPaintedAdornmentBounds
(
	IShape*				iShape,
	AdornmentDrawOrder	drawOrder,
	const PMRect&		itemBounds,  
	const PMMatrix&		innertoview
)
{
	PMRect result = itemBounds;

	return result;
}

/* Returns the bounds of the adornment in view co-ordinates.
*/
PMRect CusDtLnkAdornmentShape::GetPrintedAdornmentBounds
(
	IShape*				iShape,
	AdornmentDrawOrder	drawOrder,
	const PMRect&		itemBounds,  
	const PMMatrix&		innertoview
)
{
	PMRect result = itemBounds;

	return result;
}

/*
*/
void CusDtLnkAdornmentShape::AddToContentInkBounds(IShape* iShape, PMRect* inOutBounds)
{
}

/*	Returning a default value of 0.0 means the order is unimportant relative to 
	other "standard" priority adornments.
*/
PMReal CusDtLnkAdornmentShape::GetPriority()
{
	return 0.0;
}

/*	
*/
void CusDtLnkAdornmentShape::Inval(IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, 
			ClassID reasonForInval, int32 flags)
{

}

/*
*/
bool16 CusDtLnkAdornmentShape::WillPrint()
{
	return kFalse;
}

/*
*/
bool16 CusDtLnkAdornmentShape::WillDraw
		(
			IShape* 			iShape,
			AdornmentDrawOrder	drawOrder,
			GraphicsData*		gd,
			int32			flags
		)
{
	bool16 result = kFalse;
	do {
		ASSERT(drawOrder == kAfterShape);
		if (drawOrder != kAfterShape) {
			break;
		}

		if (flags & IShape::kPrinting) {
			break;
		}
		
		result = kTrue;

	} while(false);

	return result;
}
