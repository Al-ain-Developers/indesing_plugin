//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxLineHilite.h $
//  
//  Owner: Ric Kamicar
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
//  Interface for iterating through Wax Runs.
//  
//========================================================================================

#include "IGraphicsContext.h"
#include "PMLineSeg.h"
#include "PMMatrix.h"
#include "PMRect.h"
#include "K2Vector.h"

/** Interface for obtaining and drawing the highlight for a waxline
	@ingroup text_wax
*/
class ITextSelectionAdornment;
class IWaxLineHilite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXLINEHILITE };

	/** Get the set of bounds that would be highlighted for the entire range of text within the waxLine. See the other GetHighlightBounds() method for details.
	*/
	virtual void GetHighlightBounds(const PMMatrix &toWindow, bool16 XORmode, const PMRect& highlightAdjust, const PMLineSeg &maxTopBottom, K2Vector<PMPolygon4>* pSetOfHighlightBounds) const = 0;

	/** Get the set of bounds to highlight for the given range on the waxLine.
		@param offset IN where in the line to start the computation for the highlight (0 for the start of the waxLine)
		@param length IN the length of the text to highlight (-1 can be used to denote the rest of the text to the end of the waxLine)
		@param toWindow IN Matrix that converts to window coordinates from this.
		@param XORmode IN If kFalse indicates that the caller will not use XOR to highlight.
		@param highlightAdjust IN Used to indicate that an amount should be shaved off the highlight on the indicated side
			(used to prevent double XOR problems when two (adjacent) waxLine's highlights touch).
		@param maxTopBottom IN is used to prevent double XOR problems when waxLines are too close together.
				- any highlight should be trimmed to these bounds (if DeltaY() is non-zero).
		@param pSetOfHighlightBounds OUT the resulting set of bounds.  There may be none, one, or many bounds that apply to this line.
	*/
	virtual void GetHighlightBounds(int32 offset, int32 length, const PMMatrix &toWindow, bool16 XORmode, const PMRect& highlightAdjust, const PMLineSeg &maxTopBottom, K2Vector<PMPolygon4>* pSetOfHighlightBounds) const = 0;

	/** Draw the highlight for the given set of bounds on the given IGraphicsContext.
	@param gc IN Where to draw the bounds.
	@param pSetOfHighlightBounds IN The set of bounds returned from GetHighlightBounds().
	*/
	virtual void DrawLineHighlight(IGraphicsContext* gc, const K2Vector<PMPolygon4>* pSetOfHighlightBounds) const = 0;

	/** Get the associated text selection adornment if any.
	*/
	virtual const ITextSelectionAdornment* GetTextSelectionAdornment() const = 0;

};


