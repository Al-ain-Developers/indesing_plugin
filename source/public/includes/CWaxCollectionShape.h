//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CWaxCollectionShape.h $
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
//  Base class for IWaxRunShape on collections.
//  
//========================================================================================

#pragma once
#ifndef __CWaxCollectionShape__
#define __CWaxCollectionShape__

#include "K2Vector.h"
#include "PMMatrix.h"
#include "PMPolygon4.h"
#include "CWaxRunShape.h"

#pragma export on

/** Base implementation of the IWaxRunShape interface for collections of wax runs.  A collection can either be stacked or adjacent.
	An adjacent collection is one in which a subsequent run follows the same flow as the previous run.
	For example, if the first run goes from X=5 to X=9, then the next run would follow from that, for example from X=9 to X=34.
	A stacked collection typically has the runs stacked on top of each other with the same initial offset (typically 0).
	Thus a stacked collection of 3 runs typically has all 3 runs with X=0 and, for example, Y1= -5, Y2=0, Y3=5
	@note WaxCollections work in both horizontal and vertical text flows.
	@see IWaxRunShape, CWaxRunShape, The Wax
 */
class PUBLIC_DECL CWaxCollectionShape : public CWaxRunShape
{
public:
	/** */
	CWaxCollectionShape(IPMUnknown* boss) : CWaxRunShape(boss)
		{ }

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void GetInkBounds(PMRect* pInkBounds, Text::DrawPassInfoList* passList) const;

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void GetWaxBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds) const;
	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16 GetHighlightBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const;

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16 GetSelectionLine(PMLineSeg* pSelectionLine) const;
	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16 GetHighlightLine(PMLineSeg* pHighlightLine, const PMLineSeg& maxTopBottom) const;

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void GetCaretLineAt(int32 offset, PMLineSeg* pCaretLine, const PMLineSeg& maxTopBottom) const;

protected:
	/**
	@note See CWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16 CalculateSimpleSpanWidth(int32 offset, int32 length, PMLineSeg* pSpanWidth) const;

	/** Get the appropriate bounds for this collection. GetHighlightBounds() and GetWaxBounds() just call this directly and it iterates the children collecting thier bounds and adjusting for being in the collection.
	@see GetHighlightBounds() and GetWaxBounds() for more details on what it does and a description of the parameters and return values.
	*/
	virtual bool16 GetBounds(bool16 whichBounds, int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const;

	/**
	@note See CWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void GetTextInkBounds(PMRect *pInkBounds) const;

	/** Take care of XOR issues when the collection is a (vertically) stacked collection of runs.
	*/
	virtual void HandleStackedXORIssues(K2Vector<PMPolygon4> *pSetOfBounds, int32 prevLineStart, int32 currLineStart, const PMReal& newTop, PMRect& highlightAdjust) const;
	/** Take care of XOR issues when the collection is a (horizontally) adjacent collection of runs.
	*/
	virtual void HandleAdjacentXORIssues(K2Vector<PMPolygon4> *pSetOfBounds, int32 offsetIntoSet, PMRect& highlightAdjust) const;

	/** Adjust the maxTopBottom passed into various interfaces to take the collection into account. Called internally from GetHighlightLine(), GetCaretLineAt() and GetBounds(kFalse, ...)
	Examples: a stacked collection may wish to ignore the maxTopBottom because it's allowed to extend beyond the waxLine bounds (warichuu does this).
	An adjacent collection may not care about maxTopBottom and this would be a NOP.  Others may override it completely (TCY falls into this case).
	*/
	virtual PMLineSeg AdjustMaxTopBottom(const PMLineSeg& maxTopBottom) const = 0;
};

#pragma export off

#endif
