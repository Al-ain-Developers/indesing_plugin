//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAdornmentShape.h $
//  
//  Owner: Heath Lynn
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
//  Purpose:
//  This is the interface used to add adornments to page items.  For an example see...
//  
//========================================================================================

#pragma once
#ifndef __IAdornmentShape__
#define __IAdornmentShape__

#include "IPMUnknown.h"
#include "IGraphicsContext.h"
#include "IShape.h"

/** 	IAdornmentShape is the interface that a boss must implement to be considered a page item adornment.
	The ClassID for the boss will be added to a page item adornment list on a page item.  It's draw order bits
	will designate when the adornment will draw.
	
	Typically the boss that implements this interface would be marked recycleable in the source file
	that implements this interface.  This is because instances of this boss can come and go very frequently 
	during drawing and hit testing.
*/
class IAdornmentShape : public IPMUnknown
{

public:

	enum { kDefaultIID = IID_IADORNMENTSHAPE };
	
	enum AdornmentDrawOrder
	{
		kNone = 0,
		kBeforeShape = 1,
		kAfterFill = 2,
		kBeforeTextBackground = 4,
		kBeforeText	= 8,
		kBeforeTextForeground = 16,
		kAfterTextForeground = 32,
		kBeforeStroke = 64,
		kAfterStroke = 128,
		kAfterShape = 256,

		kBeforeFill = 512,		// Corresponds to kAfterFill
		kBeforeContent = 1024,	// Before content, whatever that content is (text/graphic).
		kAfterContent = 2048,	// After content, whatever that content is (text/graphic).

		kAfterEndShape = 4096,	// After kEndShapeMessage

		kAfterSpread = 8192,

		kAllAdornmentFlags = 16383
	};

	enum AdornmentDrawNumber
	{
		kNumberOfAdornments = 14
	};

	/**  GetDrawOrderBits returns the bits that designate when the adornment draws.
		Upon calling AddAdornment, the adornment is inserted into
		the list based on these draw order bits.  If more the one of
		the flags are & together, the adornment is put on the list
		in all specified locations.
		
		@return The bits that designate when the adornment draws.
	*/
	virtual AdornmentDrawOrder GetDrawOrderBits() = 0;

	/**  DrawAdornment draws the page item adornment.
		@param iShape IN The shape that's being adorned.
		@param drawOrder IN The current draw order bits.
		@param gd IN The current GraphicsData.
		@param flags IN The graphics's ports flags.
	*/
	virtual void DrawAdornment
		(
			IShape* 			iShape,		// owning page item
			AdornmentDrawOrder	drawOrder,	// for items that registered for more than one order
			GraphicsData*		gd,
			int32				flags
		) = 0;


	/**  GetPaintedAdornmentBounds returns the painted bounds of the adorment.
		@param iShape IN The shape that's being adorned.
		@param drawOrder IN The current draw order bits.
		@param itemBounds IN The bounds of the adorned object.
		@param innertoview IN The inner to view matrix.
	*/
	virtual PMRect GetPaintedAdornmentBounds
		(
			IShape*				iShape,
			AdornmentDrawOrder	drawOrder,
			const PMRect&		itemBounds, // This is the painted bounds of the owing page item
			const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
		) = 0;

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
			const PMRect&		itemBounds, // This is the painted bounds of the owing page item
			const PMMatrix&		innertoview	// NOTE: this is inner to view not pb to view
		) = 0;

	/** AddToContentInkBounds
	
		Takes as input a rectangle representing the bounds of some content which 
		has changed its inkinkg in some way.  The adornment will modify that bounds 
		if necessary to reflect the change in inking that it would want as a result.  
		This is only used by adornments for which the inking bounds are based on 
		the content.  Adornments for which inking bboxes are based solely on the 
		frame do not need to implement this routine.
		Note: The bounds are based on inner coordinates.
		
		@param iShape IN The shape that is being adorned.
		@param inOutBounds INOUT The bounds of some content which has changed, the adornment will modify.
	*/
	virtual void AddToContentInkBounds(IShape* iShape, PMRect* inOutBounds) = 0;

	/**  GetPriority is used to resolve ties between adornments in the page item adornment list.
		@return A floating point number (lower means higher priority).
	*/
	virtual PMReal GetPriority() = 0;

	/** AddToContentInkBounds
	This method is provided for completeness.  When the owning shape is inval'd it
	includes the adornment in it's bounding box.   Under most circumstances the
	adornment need do nothing in its inval method.
	There are times, however, when specific page items will get a specific reasonFoInval,
	and an adornment may want to know about that inval.  This provides a mechanism
	to respond to such an event.

		@param iShape IN The shape that's being adorned.
		@param drawOrder IN The current draw order bits.
		@param gd IN The current GraphicsData.
		@param reasonForInval IN The reason for invaling.
		@param flags IN The graphics's ports flags.

	*/
	virtual void Inval
		(
			IShape*				iShape,
			AdornmentDrawOrder	drawOrder,
			GraphicsData*		gd, 
			ClassID 			reasonForInval, 
			int32 				flags
		) = 0;
	
	/**  Return true if this adornment is one that will print (i.e. not just an on-screen adornment). 
		Drop shadow is an example of a printing adornment. Default implementation in CAdornmentShape is
		to return kFalse.

		@return kTrue if this adornment will print.
	*/
	virtual bool16 WillPrint() = 0;

	/**  This method is being called by the TextOffScreen code. Textoffscreen drawing is suspended if 
		page item adornments want to draw into the background. The default implementation in CAdornmentShape returns kFalse.
		Note that FrameShape::Inval still only calls its CShape::InvalPageItemAdornments() if it didn't draw into the text offscreen.
		@param iShape IN The shape that's being adorned.
		@param drawOrder IN The current draw order bits.
		@param gd IN The current GraphicsData.
		@param flags IN The graphics's ports flags.
	*/
	virtual bool16 WillDraw
		(
			IShape* 			iShape,		// owning page item
			AdornmentDrawOrder	drawOrder,	// for items that registered for more than one order
			GraphicsData*		gd,
			int32			flags
		) = 0;

	/** This method will return true if the mouse point is over the adornment. If you override this
	    you will need to call this directly. It is not hooked into any other hit test framework.
		@param iHandleShape the item with the adornment
		@param adornmentDrawOrder In case this adornment is used more than once
		@param layoutView view
		@param mouseRect Rectangle around the mouse point in Window coordinates
		@return true if mouse is over adornment
	*/
    virtual bool16 HitTest 
        ( 
            IShape*				iShape,         // The owning page item 
            AdornmentDrawOrder  adornmentDrawOrder,    // In case this adornment is used more than once
			IControlView *		layoutView,
            const PMRect&       mouseRect
        ) = 0; 
         

};

#endif
