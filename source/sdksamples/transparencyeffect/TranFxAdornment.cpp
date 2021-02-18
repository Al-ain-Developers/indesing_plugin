//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxAdornment.cpp $
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
#include "IGraphicsPort.h"
#include "IShape.h"
#include "IViewPortAttributes.h"
#include "IXPUtils.h"

// General includes:
#include "AGMImageAccessor.h"
#include "AutoGSave.h"
#include "PDFID.h"
#include "TransformUtils.h"
#include "GraphicsExternal.h"

// Project includes:
#include "TranFxID.h"
#include "TranFxMatteFactory.h"
#include "TranFxUtils.h"

/** Draws a transparent matte effect behind the page item at the x and y offset
	given by the graphic attributes below:
	<ul>
	<li>kTranFxOffsetXAttrBoss.</li>
	<li>kTranFxOffsetYAttrBoss.</li>
	</ul>

	The adornment takes a snapshot of the page item offscreen as a gray level image, then
	manipulates it as indicated by the custom graphic attributes below:
	<ul>
	<li>kTranFxUseBlackAsOpaqueAttrBoss.</li>
	<li>kTranFxUseAlphaAttrBoss.</li>	
	<li>kTranFxUseBlurAttrBoss.</li>
	</ul>	

	To draw the effect, the adornment uses the resultant grey level image as an alpha paint server. 
	Once the image is thus applied as an alpha mask, the adornment fills the image area with
	black. The alpha mask controls the opacity of each resultant pixel.
	If the alpha mask has a value of 255 it will be drawn as an opaque 
	black pixel, if it has a value of 0 it will be transparent, and if 
	it has a value of 1..254 it will be a grey pixel of increasing darkness 
	and opacity.

	
	@ingroup transparencyeffect
	@see TranFxMatteFactory helper used to create the image mask.
	@see TranFxUtils helper used to access the graphic attributes that control the image processing and drawing.
 */
class TranFxAdornment : public CPMUnknown<IAdornmentShape>
{
	public:
		/** Constructor.
			@param boss
		*/
		TranFxAdornment(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~TranFxAdornment();	
		
		/** Registers for kBeforeShape since the adornment draws 
			behind the item that owns it.
			Note: You are only called for at the draw order(s) you request so
			you must override this, else you won't be called at all.
			@return kBeforeShape. 
		 */
		virtual AdornmentDrawOrder	GetDrawOrderBits();

		/**	Draws the adornment. The method creates a mask image of the page item 
			that owns the adornment, applies it as an alpha paint server then fills
			the area with black. The result is a greyscale image of the page item
			of varying transparency.
			@param iShape IN the page item that owns the adornment.
			@param drawOrder IN significant for adornments that registered for more than one order.
			@param gd the graphics context to draw into.
			@param flags the draw flags (see IShape).
		 */
		virtual void				DrawAdornment
			(
				IShape* iShape, 
				AdornmentDrawOrder drawOrder, 
				GraphicsData* gd, 
				int32 flags
			);
	
		/** Return the bounds of the adornment in view co-ordinates
			adjusting as necessary for any x and y offsets that are applied.
			@param iShape IN the page item that owns the adornment.
			@param drawOrder IN significant for adornments that registered for more than one order.
			@param itemBounds IN stroke bounds of page item that owns the adornment in view co-ordinates.
			@param innerToView IN matrix to be used to transform bounds into view co-ordinates.
			@return bounds of the adornment in view co-ordinates.
		 */
		virtual PMRect				GetPaintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds, // This is the painted bounds of the owing page item
				const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
			);

		/** Return the bounds of the adornment in view co-ordinates
			adjusting as necessary for any x and y offsets that are applied. If this adornment were not
			included during printing, then we'd simply return the itemBounds. However, for this adornment,
			the printed bounds is the same as the painted bounds.
			@param iShape IN the page item that owns the adornment.
			@param drawOrder IN significant for adornments that registered for more than one order.
			@param itemBounds IN stroke bounds of page item that owns the adornment in view co-ordinates.
			@param innerToView IN matrix to be used to transform bounds into view co-ordinates.
			@return bounds of the adornment in view co-ordinates.
		 */
		virtual PMRect				GetPrintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds, // This is the painted bounds of the owing page item
				const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
			);

		/** Not yet implemented.
			@param iShape IN the page item that owns the adornment.
			@param inOutBounds
		 */
		virtual void				AddToContentInkBounds
			(
				IShape* iShape, 
				PMRect* inOutBounds
			);

		/**	Return the draw priority of thius adornment relative to other adornments
			in the draw order.
			@return 0.0 since the priority is not significant.
		 */
		virtual PMReal				GetPriority();

		/** Purges any effect image for the page item that has been saved in
			the image cache. 
		
			Note: Previously a scheme
			that used a document observer was used to purge the cache as objects
			were transformed or invalidated. This was moved to here because this method
			always gets called when these events occur. The benefit is we only get called
			for objects that have the effect applied. The document observer was watching
			for changes on all object and then detecting those that have the effect.
			Putting the cache purge here seems more efficient.
			@param iShape IN the page item that owns the adornment.
			@param drawOrder IN significant for adornments that registered for more than one order.
			@param gd IN the graphics context to draw into.
			@param reasonForInval IN
			@param flags IN the draw flags (see IShape).
		 */
		virtual void				Inval
			(
				IShape* iShape, 
				AdornmentDrawOrder drawOrder, 
				GraphicsData* gd, 
				ClassID reasonForInval, 
				int32 flags
			);

		/** @return kTrue since this adornment prints.
		 */
		virtual bool16				WillPrint();

		/**	Checks the state that controls whether or not this adornment
			will draw.
			@param iShape IN the page item that owns the adornment.
			@param drawOrder IN significant for adornments that registered for more than one order
			@param gd IN the graphics context to draw into.
			@param flags IN the draw flags (see IShape).
			@return kTrue if the adornment will draw, kFalse otherwise. 
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

	private:
		/** Return the value of the x offset(kTranFxOffsetYAttrBoss).
			@param iShape references the object to be checked.
			@return the value of the x offset.
		*/
		PMReal                  GetYOffset(IShape* iShape);

		/** Return the value of the y offset(kTranFxOffsetXAttrBoss).
			@param iShape references the object to be checked.
			@return the value of the y offset.
		*/
		PMReal                  GetXOffset(IShape* iShape);
};

/*
*/
CREATE_PMINTERFACE(TranFxAdornment, kTranFxAdornmentImpl)

/*
*/
TranFxAdornment::TranFxAdornment(IPMUnknown* boss) : CPMUnknown<IAdornmentShape>(boss)
{
}

/*
*/
TranFxAdornment::~TranFxAdornment()
{
}

/*
*/
IAdornmentShape::AdornmentDrawOrder TranFxAdornment::GetDrawOrderBits()
{
	return kBeforeShape;
}

/*
*/
void TranFxAdornment::DrawAdornment(IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, 
			GraphicsData* gd, int32 flags)
{
	TRACEFLOW(kTranFxPluginName, "TranFxAdornment::Draw-->In\n");

	do {
		ASSERT(drawOrder == kBeforeShape);
		if (drawOrder != kBeforeShape) {
			break;
		}

		// Check the attributes of the port for flags that indicate the
		// adornment should not draw.
		IViewPortAttributes* viewPortAttributes = gd->GetViewPortAttributes();
		ASSERT(viewPortAttributes);
		if (!viewPortAttributes) {
			break;
		}
		// Don't draw if the port is being used to generate a transparency
		// effect mask.
		if (viewPortAttributes->GetAttr(kXPIsMaskPortVPAttr, kFalse)) {
			break;
		}
		// Don't draw if effect drawing is suppressed. This is used as a flag
		// to prevent recursion. When this plug-in uses SnapshotUtils
		// to create an image of a page item it sets this flag to kTrue so that
		// this adornment does not draw.
		if (viewPortAttributes->GetAttr(kXPSuppressEffectsVPAttr, kFalse)) {
			break;
		}

		// This effect is a transparency effect. Check the display
		// performance options and don't draw if transparency is off.
		DrawOptionsSet drawOptionsSet = gd->GetDrawOptions(iShape);
		if (drawOptionsSet.xp == IDrawOptions::kXPOff) {
			break;
		}	

		// Don't draw if in patient user mode and drawing the clipped out image data.
		if (flags & IShape::kDrawingClippedOutImageData) {
			break;
		}

		// Are we printing or drawing to the screen?
		bool32 isPrinting = kFalse;
		if (flags & IShape::kPrinting) {
			// Note this flag is set when drawing for print or PDF.
			isPrinting = kTrue;
			// We don't currently use this flag cause when we are
			// drawing to a print of pdf port the drawOptions below
			// get set to high quality and we use this instead to control
			// the resolution we draw at.
		}

		// Choose the resolution for the effect. Note that this
		// could be optimised. For example, if we are drawing to the
		// screen and have zoomed out, we could probably draw at a lower 
		// resolution than 72 dpi. If we are zoomed in we might want to
		// draw at a higher resolution to reduce pixelisation (that is
		// left as a exercise for the future).
		PMReal resolution = 72.0;
		switch(drawOptionsSet.xp)
		{
			case IDrawOptions::kXPLow:
				resolution = 36.0;
				break;
			case IDrawOptions::kXPMedium:
				resolution = 72.0;
				break;
			case IDrawOptions::kXPHigh:
				resolution = 144.0;
				break;
		}

		// Only enable caching of any effect masks we make if
		// the viewport allows it.
		bool16 enableCaching = viewPortAttributes->GetViewPortCacheing();

		// Create the effect mask from the page item.
		TranFxMatteFactory matteFactory;
		const AGMImageAccessor* matteAccessor = matteFactory.MakeMatte(iShape, 
			resolution, 
			drawOptionsSet,
			enableCaching);
		ASSERT(matteAccessor);
		if (!matteAccessor) {
			break;
		}
		const AGMImageRecord* matteImage =  matteAccessor->GetAGMImageRecord();		
		ASSERT(matteImage);
		if(!matteImage) {
			break;
		}

		// Set up the measures and matrices we need.
		int32 width  = std::abs(matteImage->bounds.xMax - matteImage->bounds.xMin);
		int32 height = std::abs(matteImage->bounds.yMax - matteImage->bounds.yMin);
		ASSERT(width > 0 && height > 0 && resolution >= 1.0);	
		PMReal scaleFactor = 72.0 / resolution;
		PMMatrix inner2pb = ::InnerToPasteboardMatrix(iShape);
		PMMatrix pb2inner = inner2pb.Inverse();

		// Get the bounds of the effect.
		PBPMRect matteBounds = matteFactory.GetBoundingBox(iShape);

		// Set up the port.
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		ASSERT(gPort);
		if (!gPort) {
			break;
		}	
		AutoGSave autoGSave(gPort);
		gPort->concat(pb2inner);
		gPort->translate (matteBounds.Left() + this->GetXOffset(iShape), matteBounds.Top() + this->GetYOffset(iShape));
		gPort->scale(scaleFactor, scaleFactor);

		// Create a paint server from the matte and use it as an alpha server.
		Utils<IXPUtils> xpUtils;
		ASSERT(xpUtils);
		if (!xpUtils) {
			break;
		}
		InterfacePtr<IXPManager> xpManager(xpUtils->QueryXPManager(::GetDataBase(iShape)));
		ASSERT(xpManager);
		if (!xpManager) {
			break;
		}
		PMMatrix matrix;
		AGMPaint* paint = xpUtils->CreateImagePaintServer(const_cast<AGMImageRecord* >(matteImage), 
			&matrix, 
			0,		// flags
			nil);	// Uncalibrated.
		ASSERT(paint);
		if(!paint) {
			break;
		}
		gPort->SetAlphaServer(paint, kTrue, PMMatrix());

		// Extra initialisation is required when drawing to a PDF port.
		bool32 isPDFFlattenerExport = viewPortAttributes->GetAttr(kPDFIsFlattenerTargetVPAttr, kFalse);
		bool32 isPDFExport = viewPortAttributes->GetAttr(kPDFExportVPAttr, kFalse);
		bool16 startedTransparencyGroup = kFalse;
		if (isPDFExport && !isPDFFlattenerExport) {
			AGMColorSpace* blendingSpace = xpManager->GetDocumentBlendingSpace();
			PMRect bounds(0, 0, width, height);
			bool16 knockoutGroup = kFalse;
			bool16 isolationGroup = kFalse;
			// You could add attributes that control knockout (objects blend with backdrop
			// but not each other) or isolation(objects blend with each other but not
			// the backdrop).
			gPort->starttransparencygroup(bounds, blendingSpace, isolationGroup, knockoutGroup);
			startedTransparencyGroup = kTrue;
			xpManager->ReleaseBlendingSpace(blendingSpace);
		}

		// Create a path and fill it. The mask we created above
		// contains an image based on the page item the adornment
		// is attached to. The mask is applied as an alpha
		// server so the image it contains  controls the 
		// transparency of each pixel when we fill the entire area.
		// If you want to control the colour of the fill uncomment
		// the setrgbcolor call below which changes the fill to red.
		gPort->newpath();
		gPort->rectpath(0, 0, width, height);
		gPort->setblendingmode(kPMBlendMultiply);
		//gPort->setrgbcolor(1.0, 0.0, 0.0);
		gPort->fill();

		// Tidy up.
		if (startedTransparencyGroup) {
			gPort->endtransparencygroup();
		}
		xpUtils->ReleasePaintServer(paint);

	} while(false);

	TRACEFLOW(kTranFxPluginName, "TranFxAdornment::Draw-->Out\n");
}

/* Returns the bounds of the adornment in view co-ordinates.
*/
PMRect TranFxAdornment::GetPrintedAdornmentBounds
(
	IShape*				iShape,
	AdornmentDrawOrder	drawOrder,
	const PMRect&		itemBounds,  
	const PMMatrix&		innertoview
)
{
	return GetPaintedAdornmentBounds(iShape, drawOrder, itemBounds, innertoview);
}

/* Returns the bounds of the adornment in view co-ordinates.
*/
PMRect TranFxAdornment::GetPaintedAdornmentBounds
(
	IShape*				iShape,
	AdornmentDrawOrder	drawOrder,
	const PMRect&		itemBounds,  
	const PMMatrix&		innertoview
)
{
	PMRect result = itemBounds;
	do {
		// Get the painted bounds of the effect in pasteboard co-ordinates.
		TranFxMatteFactory matteFactory;
		if (matteFactory.GetPaintedBBoxWithoutMatte(iShape, result) == kFalse)
		{
			// This avoids infinite recursion. The painted bbox is not available
			// during a recursive call.
			break;
		}

		// Get the matrices we need.
		PMMatrix inner2pb = ::InnerToPasteboardMatrix(iShape);
		PMMatrix pb2inner = inner2pb.Inverse();

		// Offset in pasteboard co-ordinates.
		result.MoveRel(this->GetXOffset(iShape), this->GetYOffset(iShape));
		
		// Then translate pb2inner plus innertoview.
		PMMatrix pb2inner2view = pb2inner;
		pb2inner2view.PostConcat(innertoview);
		pb2inner2view.Transform(&result);
	} while(false);
	return result;
}


/* AddToContentInkBounds, used for resizing textframe etc.
*/
void TranFxAdornment::AddToContentInkBounds(IShape* iShape, PMRect* inOutBounds)
{
	PMRect result = *inOutBounds;
	do {
		// Get the painted bounds of the effect in pasteboard co-ordinates.
		TranFxMatteFactory matteFactory;
		if (matteFactory.GetPaintedBBoxWithoutMatte(iShape, result) == kFalse)
		{
			// This avoids infinite recursion. The painted bbox is not available
			// during a recursive call.
			break;
		}

		// Get the matrices we need.
		PMMatrix inner2pb = ::InnerToPasteboardMatrix(iShape);
		PMMatrix pb2inner = inner2pb.Inverse();

		// Offset in pasteboard co-ordinates.
		result.MoveRel(this->GetXOffset(iShape), this->GetYOffset(iShape));
		
		// Then translate pb2inner
		pb2inner.Transform(&result);
		if (!result.IsEmpty()) inOutBounds->Union(result);

	} while(false);
}

/*	Returning a default value of 0.0 means the order is unimportant relative to 
	other "standard" priority adornments.
*/
PMReal TranFxAdornment::GetPriority()
{
	return 0.0;
}

/*	Purge any cached effect for the image. This gets called when the item that
	owns the adornment invalidates. This will happen when the item is resized,
	rotated or otherwise transformed. Also when some graphic attribute changes
	such as stroke weight, fill, colour, etc.
*/
void TranFxAdornment::Inval(IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, 
			ClassID reasonForInval, int32 flags)
{
#if 0 //#ifdef DEBUG
	DebugClassUtilsBuffer reasonForInvalName;
	DebugClassUtils::GetIDName(&reasonForInvalName, reasonForInval);
	TRACEFLOW(kTranFxPluginName, "TranFxAdornment::Inval-->In(reasonForInval=%s)\n",
		reasonForInvalName);
#endif
		TranFxMatteFactory maskMaker;
		maskMaker.PurgeImageCache(UIDList(::GetUIDRef(iShape)));
}

/*
*/
bool16 TranFxAdornment::WillPrint()
{
	return kTrue;
}

/*
*/
bool16 TranFxAdornment::WillDraw
		(
			IShape* 			iShape,
			AdornmentDrawOrder	drawOrder,
			GraphicsData*		gd,
			int32			flags
		)
{
	bool16 result = kFalse;
	do {
		ASSERT(drawOrder == kBeforeShape);
		if (drawOrder != kBeforeShape) {
			break;
		}

		// Check the attributes of the port for flags that indicate the
		// adornment should not draw.
		IViewPortAttributes* viewPortAttributes = gd->GetViewPortAttributes();
		ASSERT(viewPortAttributes);
		if (!viewPortAttributes) {
			break;
		}
		// Don't draw if the port is being used to generate a transparency
		// effect mask.
		if (viewPortAttributes->GetAttr(kXPIsMaskPortVPAttr, kFalse)) {
			break;
		}
		// Don't draw if effect drawing is suppressed. This is used as a flag
		// to prevent recursion. When this plug-in uses SnapshotUtils
		// to create an image of a page item it sets this flag to kTrue so that
		// this adornment does not draw.
		if (viewPortAttributes->GetAttr(kXPSuppressEffectsVPAttr, kFalse)) {
			break;
		}

		// This effect is a transparency effect. Check the display
		// performance options and don't draw if transparency is off.
		DrawOptionsSet drawOptionsSet = gd->GetDrawOptions(iShape);
		if (drawOptionsSet.xp == IDrawOptions::kXPOff) {
			break;
		}	

		// If in patient user mode and drawing the clipped out image data, return.
		if (flags & IShape::kDrawingClippedOutImageData) {
			break;
		}

		result = kTrue;

	} while(false);

	return kFalse;
}

/*
*/
PMReal TranFxAdornment::GetYOffset(IShape* iShape)
{
	PMReal result = 0.0; 
	TranFxUtils tranFxUtils;
	tranFxUtils.HasYOffset(UIDList(iShape), result);
	return result;
}

/*
*/
PMReal TranFxAdornment::GetXOffset(IShape* iShape)
{
	PMReal result = 0.0;
	TranFxUtils tranFxUtils;
	tranFxUtils.HasXOffset(UIDList(iShape), result);
	return result;
}
// End, TranFxAdornment.cpp

