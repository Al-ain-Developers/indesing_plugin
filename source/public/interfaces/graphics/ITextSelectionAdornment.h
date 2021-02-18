//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITextSelectionAdornment.h $
//  
//  Owner: Reena Agrawal
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
#ifndef __ITextSelectionAdornment__
#define __ITextSelectionAdornment__

#include "IPMUnknown.h"
#include "IGraphicsContext.h"

#include "PMPolygon4.h"

#include "K2Vector.tpp"
#include "GenericID.h"

/** 	ITextSelectionAdornment is the interface that a boss must implement to be considered a page item adornment.
	The ClassID for the boss will be added to a page item adornment list on a page item.  It's draw order bits
	will designate when the adornment will draw.
	
	Typically the boss that implements this interface would be marked recycleable in the source file
	that implements this interface.  This is because instances of this boss can come and go very frequently 
	during drawing and hit testing.
*/

class IWaxLineHilite;
class ITextSelectionAdornment : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTSELECTIONADORNMENT };
	
	/**  DrawAdornment draws the page item adornment.
		@param gd IN The current GraphicsData.
		@param pSetOfHighlightBounds IN highlight bounds in waxline space.
		@param gc IN graphics context.
		@param flags IN The graphics's ports flags.
	*/
	virtual void DrawAdornment(const IWaxLineHilite* waxLineHilite, const K2Vector<PMPolygon4>* pSetOfHighlightBounds, IGraphicsContext* gc, int32 flags) = 0;

	/** This method will return true if the mouse point is over the adornment. If you override this
	    you will need to call this directly. It is not hooked into any other hit test framework.
		@param layoutView view
		@param mousePoint Mouse point in Window coordinates
		@return true if mouse is over adornment
	*/

	virtual bool16 HitTest(const PMPoint& mousePoint) const = 0;

	/** This method will return true if the mouse point is within the hover rect. This is used to dismiss the
		context UI in case mouse goes out of the hover rect.
		@param layoutView view
		@param mousePoint Mouse point in Window coordinates
		@return true if mouse is over adornment
	*/

	virtual bool16 IsMouseWithinHoverRect(const PMPoint& mousePoint) const = 0;

	/** This method will return the adornment bounds for the adornment.
	@param layoutView view
	@param mousePoint Mouse point in Window coordinates
	@return true if mouse is over adornment
	*/

	virtual PMRect GetAdornmentBounds() const = 0;

};

#endif
