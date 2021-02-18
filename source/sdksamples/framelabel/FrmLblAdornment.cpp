//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblAdornment.cpp $
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
#include "IHierarchy.h"
#include "IDocument.h"
#include "ISwatchList.h"
#include "IPMFont.h"
#include "IFontInstance.h"
#include "IGeometry.h"
#include "iuicolorutils.h"
#include "IBoolData.h"
#include "ISession.h"

// General includes:
#include "AutoGSave.h"
#include "CPMUnknown.h"
#include "TransformUtils.h"

// Project includes:
#include "IFrmLblData.h"
#include "FrmLblID.h"
#include "FrmLblType.h"

/** Provides the adornment implementation to draw a text label
	on drawable page items; implements IAdornmentShape. 
	@ingroup framelabel
	
*/

class FrmLblAdornment : public CPMUnknown<IAdornmentShape>
{

	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		FrmLblAdornment(IPMUnknown* boss);

		/** 
			Destructor.
		*/
		~FrmLblAdornment();


		/**
			Tells the draw manager when in the drawing sequence the adornment
			should be asked to draw.
			@return Enum describing when this adornment should be drawn as part of the draw sequence.  See IAdornmentShape.h.
		*/
		virtual AdornmentDrawOrder GetDrawOrderBits();


		/**
			Draws the adornment in the inner coordinates of the page item to which this adornment is attached.
			Note that for the draw to work correctly, it must be within the bounds reported by GetPaintedBBox() below.
			It's confusing, because we draw in the page item's inner coordinates, but we report bounds in the view coordinates.
			@param	iShape		Ptr to page item requesting this adornment to draw.  Handy for getting information about the owning page item, such as its bounding box.
			@param	drawOrder	Tells the adornment when in the (AdornmentDrawOrder) sequence it's being asked to draw.  Used when an adornment is registered for more than one point in the draw order.
			@param	gd			Graphics data structure.  Used to acquire the drawing port, view, draw manager, etc.
			@param	flags		IShape flags describing mode of draw: dynamic, printing, patient user, etc.  Used for deciding when an adornment should not draw, or draw differently to a particular port. For example, draw to the screen but not to print.		
		*/
		virtual void DrawAdornment
			(
				IShape* 			iShape,
				AdornmentDrawOrder	drawOrder,
				GraphicsData*		gd,
				int32				flags
			);


		/** 
			Reports the dimensions of the adornment in the coordinates of the view in which this adornment will draw.
			Note the bounds reported by this method must accurately reflect the bounds used by Draw().
			It's confusing, because we draw in the page item's inner coordinates, but we report bounds in the view coordinates.
			@param	iShape		Ptr to page item requesting this adornment to draw.  Handy for getting information about the owning page item, such as its bounding box.
			@param	drawOrder	Tells the adornment when in the (AdornmentDrawOrder) sequence it's being asked to draw.  Used when an adornment is registered for more than one point in the draw order.
			@param	itemBounds	The painted bounds of the owing page item in the page item's inner coordinates.
			@param	innertoview	The transformation from the inner bounds coordinates of the page item to which this adornment is attached, to the coordinate system of the view in which the adornment will appear.
		*/
		virtual PMRect GetPaintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds,
				const PMMatrix&		innertoview
			);

		/**  GetPrintedAdornmentBounds returns the printed bounds of the adorment.
			@param iShape IN The shape that's being adorned.
			@param drawOrder IN The current draw order bits.
			@param itemBounds IN The bounds of the adorned object.
			@param innertoview IN The inner to view matrix.
		*/
		virtual PMRect GetPrintedAdornmentBounds
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				const PMRect&		itemBounds,
				const PMMatrix&		innertoview
			);
		/** 
			Here for completeness.  See IAdornmentShape for an explanation.
		*/
		virtual void Inval
			(
				IShape*				iShape,
				AdornmentDrawOrder	drawOrder,
				GraphicsData*		gd, 
				ClassID 			reasonForInval, 
				int32 				flags
			);

		/**
			Adornments affect when they are called by the priority value they return
			via their GetPriority() method. Higher priorities (smaller numbers) are
			called before lower priorities (larger numbers).
			@return Always returns the highest priority.
		*/
		virtual PMReal GetPriority() 
				{return 0;}


		/** 
			Adornments can modify their inking bounds if they exceed the content bounds.
			For example, if content adds a drop shadow under some conditions, then the inking
			bounds would be different than the painted bbox calculated in this class.  (Which
			is based on the adornment text and fonts, etc.)
			This class doesn't support any inking changes that would make the inking bounds
			different from the painted bbox, so we just have a do-nothing implementation.
			@param iShape IN Points to interface on page item boss to which this adornment is applied.
			@param inOutBounds IN Points to rectangle describing the current ink bounds. Modify this PMRect to reflect accurate ink bounds.
		*/
		virtual void AddToContentInkBounds(IShape* iShape, PMRect* inOutBounds) {}


		/**
			Adornments can declare they want to draw in TextOffscreen mode.  This will suspend drawing of
			offscreen drawing, so the default is to not draw during text offscreen mode.
			See the Draw() documentation for an explanation of parameters. 
		*/
		virtual bool16 WillDraw
		(
			IShape* 			iShape,		// owning page item
			AdornmentDrawOrder	drawOrder,	// for items that registered for more than one order
			GraphicsData*		gd,
			int32			flags
		)
		{ return kFalse; }


		/**	
		  	See IAdornmentShape::WillPrint
		 */
		virtual bool16 WillPrint(void)
		{ return kFalse; }

		/** See IAdornmentShape::HitTest
		*/
		virtual bool16 HitTest 
			( 
				IShape*		          iShape,         // The owning page item 
				AdornmentDrawOrder    adornmentDrawOrder,    // In case this adornment is used more than once 
				IControlView *		layoutView,
				const PMRect&         r 
			){ return kFalse; }

};

CREATE_PMINTERFACE(FrmLblAdornment, kFrmLblAdornmentImpl)

/*	Constructor.
*/
FrmLblAdornment::FrmLblAdornment(IPMUnknown* boss) 
	: CPMUnknown<IAdornmentShape>(boss)
{
	TRACE("Creating the adornment\n");
}

/* Destructor
*/
FrmLblAdornment::~FrmLblAdornment()
{
	TRACE("Releasing the Adronemnt\n");
}


/* Draw
*/
IAdornmentShape::AdornmentDrawOrder FrmLblAdornment::GetDrawOrderBits()
{
	// kAfterEndShape could be used if this item didn't print, or if this adornment shouldn't be affected by transparency set on the object
	IAdornmentShape::AdornmentDrawOrder flags = (IAdornmentShape::AdornmentDrawOrder)(kAfterShape);
	return flags;
}


/* Draw
	Performs the following steps:
	1) Get the graphics port from the graphics data
	2) Set the graphics port for drawing the label
	3) Compute the starting coordinates for drawing the label
	4) Draw the label
	5) Restore the graphics port
*/
void FrmLblAdornment::DrawAdornment
	(
		IShape* 			shape,
		AdornmentDrawOrder	drawOrder,
		GraphicsData*		gd,
		int32				flags 
	)
{
	do {
		TRACE("Drawing the frame adornment!\n");

		ASSERT(drawOrder == kAfterShape);
		if (drawOrder != kAfterShape) 
		{
			break;
		}

		if ((flags & IShape::kPrinting) || (flags & IShape::kPreviewMode))
		{
			//do not draw adornment if the printing preference is not valid or preference is not set
			InterfacePtr<IBoolData> prnLblPref((IBoolData*)GetExecutionContextSession()->QueryWorkspace(IID_IFRMLBLPRINTBOOLDATA));
			if(prnLblPref == nil || prnLblPref->Get() == kFalse)
			{
				break;
			}
		}

		TRACE("Got a call to FrmLblAdornment::Draw\n");		

		if (gd == nil)
		{
			ASSERT_FAIL("Nil GraphicsData*");
			break;
		}

		// Get access to the data describing the label
		InterfacePtr<IFrmLblData> labelData(shape, UseDefaultIID());
		if (labelData == nil)
		{
			TRACE("Label data == nil for this item");
			// We are often called in the general list to process, so return without assert.
			break; 
		}

		FrmLblInfo frmLblInfo = labelData->Get();
		const WideString& labelString = frmLblInfo.label;
		if (labelString.empty())
		{
			TRACE("Label length is zero");
			break;
		}

		// The labels are created using the default font.
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil)
		{
			ASSERT_FAIL("LabelDrawHandler::HandleEvent: fontMgr invalid");
			break;
		}

		// The default font, and the items geometry & hierarchy should be
		// available, but if they aren't a return is sufficient (an
		// assert here might come up a lot on a heavily populated page
		// and if this code is in error, the labels won't draw anyway.)

		InterfacePtr<IPMFont> theFont(fontMgr->QueryFont(fontMgr->GetDefaultFontName()));
		InterfacePtr<IGeometry> itemGeometry(labelData, UseDefaultIID());
		InterfacePtr<IHierarchy> itemHier(labelData, UseDefaultIID());
		if (theFont == nil || itemGeometry == nil || itemHier == nil)
		{
			// ASSERT_FAIL("LabelDrawHandler::HandleEvent: font, geometry, or hierachy unavailable");
			break;
		}

		InterfacePtr<IPMPersist> persist(itemHier, UseDefaultIID());
		if (persist == nil)
		{
			ASSERT_FAIL("Nil IPMPersist*");
			break;
		}
		IDataBase* theDB = persist->GetDataBase();
		InterfacePtr<IDocument> theDoc(theDB, theDB->GetRootUID(), UseDefaultIID());
		if (theDoc == nil)
		{
			ASSERT_FAIL("Nil IDocument*");
			break;
		}

		// The graphics port is the port that the page item is currently drawing to.
		// That could be the screen, a printer, a PDF, or some other port:
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		if (gPort == nil)
		{
			ASSERT_FAIL("Nil IGraphicsPort*");
			break;
		}

		// Drawing methods are much like the PostScript commands. 
		// A good reference for the IGraphicsPort methods is the  PostScript
		// Language Reference Manual.

		// Save the current port settings.  This is the equivalent of pushing them on a stack
		AutoGSave autoGSave(gPort);

		// Set the drawing color for the port to a special value for the label
		if(frmLblInfo.fontColor != kInvalidUID)
		{
			ColorArray colorArray = Utils<IUIColorUtils>()->GetRGBColorValue(theDB, frmLblInfo.fontColor);
			gPort->setrgbcolor(colorArray[0], colorArray[1], colorArray[2]);
		}
		else
		{
			gPort->setrgbcolor(203/256.0, 43/256.0, 138/256.0);
		}

		// Set the font in the port
		gPort->selectfont(theFont, static_cast<PMReal>(frmLblInfo.pointSize));

		PMMatrix fontMatrix(static_cast<PMReal>(frmLblInfo.pointSize), 0.0, 0.0,
							static_cast<PMReal>(frmLblInfo.pointSize), 0.0, 0.0 );

		// Get access to a default instance of the font in the label point size
		InterfacePtr<IFontInstance> fontInst(fontMgr->QueryFontInstance(theFont, fontMatrix));
		if (fontInst == nil)
		{
			ASSERT_FAIL("Nil IFontInstance*");
			break; 
		}

		PMReal x, y;
		PMRect bBox = itemGeometry->GetPathBoundingBox();

		TRACE("The frame box is (L: %f, T: %f, R: %f, B: %f)\n", ::ToDouble(bBox.Left()), ::ToDouble(bBox.Top()), ::ToDouble(bBox.Right()), ::ToDouble(bBox.Bottom()));
		switch(frmLblInfo.position)
		{

		// Place the label left and aligned with the top side of the frame
		case kFrmLblLeft:
			//Transform Y axis to X axis with same direction if rotate 90 degree
			x = bBox.Top(); 
			//Transform X axis to Y axis with reverse direction if rotate 90 degree
			y = -bBox.Left() + fontInst->GetAscent();
			gPort->rotate(90.0);
			break;

		// Place the label right and aligned with the bottom side of the frame
		case kFrmLblRight:
			//Transform Y axis to X axis with reverse direction if rotate -90 degree
			x = -bBox.Bottom(); 
			//Transform X axis to Y axis with same direction if rotate -90 degree
			y = bBox.Right() + fontInst->GetAscent();
			gPort->rotate(-90.0);
			break;

		// Place the label above and aligned with the left side of the frame
		case kFrmLblTop:
			x = bBox.Left(); 
			y = bBox.Top() - fontInst->GetDescent();
			break;

		// Place the label beneath and aligned with the left side of the frame
		case kFrmLblBottom:
			x = bBox.Left(); 
			y = bBox.Bottom() + fontInst->GetAscent(); 
			break;

		default:
			//ASSERT_FAIL("Invalid frame label position");
			return;
		}
		TRACE("the label is going in at (%f,%f) and is %d characters long\n",::ToDouble(x),::ToDouble(y),labelString.CharCount());

		// Draw the string in the port
		gPort->show(x, y, labelString.NumUTF16TextChars(), labelString.GrabUTF16Buffer(nil));

	} while (false); // Only do once.
}

/* GetPrintedBBox
*/
PMRect FrmLblAdornment::GetPrintedAdornmentBounds
	(
		IShape*				shape,
		AdornmentDrawOrder	drawOrder,
		const PMRect&		itemBounds,
		const PMMatrix&		innertoview	
	)
{
	return itemBounds;
}

/* GetPaintedBBox
*/
PMRect FrmLblAdornment::GetPaintedAdornmentBounds
	(
		IShape*				shape,
		AdornmentDrawOrder	drawOrder,
		const PMRect&		itemBounds,
		const PMMatrix&		innertoview	
	)
{
	// Create a rectangle to describe the bounds of the adornment in the inner coordinates of
	// of the page item for which this adornment will draw.
	PMRect aChildRect(itemBounds);
	PMMatrix viewToInner = innertoview.Inverse();
	viewToInner.Transform( &aChildRect );

	do {

		// Get access to the data describing the label
		InterfacePtr<IFrmLblData> labelData(shape, UseDefaultIID());
		if (labelData == nil)
		{
			TRACE("Label data == nil for this item");
			// We are often called in the general list to process, so return without assert.
			break; 
		}

		// Get the default font
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil)
		{
			ASSERT_FAIL("Nil IFontMgr*");
			break; 
		}

		FrmLblInfo frmLblInfo = labelData->Get();
		InterfacePtr<IPMFont> font(fontMgr->QueryFont(fontMgr->GetDefaultFontName()));
		if (font == nil)
		{
			ASSERT_FAIL("Nil IPMFont*");
			break;
		}

		// Compute the length of the string, given the font and point size
		const WideString& labelString = frmLblInfo.label;
		if ( !labelString.empty() )
		{
			// Create a matrix describing the label character size in points
			PMMatrix matrix( static_cast<PMReal>(frmLblInfo.pointSize), 0.0, 0.0,
							 static_cast<PMReal>(frmLblInfo.pointSize), 0.0, 0.0 );

			// Get access to a default instance of the font in the label point size
			InterfacePtr<IFontInstance> fontInst(fontMgr->QueryFontInstance(font, matrix));
			if (fontInst == nil)
			{
				ASSERT_FAIL("Nil IFontInstance*");
				break; 
			}

			// Ask the font instance to calculate the size of the label string
			PMReal width;
			fontInst->MeasureWText((textchar*) labelString.GrabUTF16Buffer(nil), labelString.NumUTF16TextChars(), width);
			PMReal height = fontInst->GetAscent() + fontInst->GetDescent();

			// Hack safety net for height...
			if(height == 0)
				height = 1.5 * frmLblInfo.pointSize;

			// Compute the position of the label in the page item's inner coordiantes
			// At this point aChildRect should not be smaller than the area used by the Draw() method.
			switch(frmLblInfo.position)
			{
			case kFrmLblLeft:
				aChildRect.Left( aChildRect.Left() - height);
				aChildRect.Bottom( aChildRect.Top() + width);
				break;

			case kFrmLblRight:
				aChildRect.Right( aChildRect.Right() + height);
				aChildRect.Top( aChildRect.Bottom() - width);
				break;

			case kFrmLblTop:
				aChildRect.Right( aChildRect.Left() +  width);
				aChildRect.Top( aChildRect.Top() - height);
				break;

			case kFrmLblBottom:
				aChildRect.Right( aChildRect.Left() +  width);
				aChildRect.Bottom( aChildRect.Bottom() + height);
				break;

			default:
				//ASSERT_FAIL("Invalid frame label position");
				break;
			}
		}

		// Now transform the description to the coordinates of the view in which this adornment will draw
		innertoview.Transform(&aChildRect);

	} while (false);

	return aChildRect;

}

/* Inval
*/
void FrmLblAdornment::Inval
	(
		IShape*				iShape,
		AdornmentDrawOrder	drawOrder,
		GraphicsData*		gd, 
		ClassID 			reasonForInval, 
		int32 				flags
	)
{
}
