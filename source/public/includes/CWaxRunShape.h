//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CWaxRunShape.h $
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
//  Base class for IWaxRunShape.
//  
//========================================================================================

#pragma once
#ifndef __CWaxRunShape__
#define __CWaxRunShape__

#include "CPMUnknown.h"

#include "IWaxLineShape.h"
#include "IWaxRunShape.h"
#include "IWaxRenderData.h"
#include "IWaxGlyphs.h"

#include "PMLineSeg.h"

/** Base implementation of the IWaxRunShape interface.
	@see IWaxRunShape, IWaxLineShape
 */
class PUBLIC_DECL CWaxRunShape : public CPMUnknown<IWaxRunShape>
{
public:
	CWaxRunShape(IPMUnknown* boss) : CPMUnknown<IWaxRunShape>(boss),
		fSelModeFlags(IWaxLineShape::kSelectionMode_Default), fFlags(0)
		{ }

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void  GetInkBounds(PMRect* pInkBounds, Text::DrawPassInfoList* passList) const;

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void  GetWaxBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds) const;
	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16  GetHighlightBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const;

	virtual bool16 GetHighlightBoundsME(int32 runGlyphStartIndex, int32 startGlyphIndex, int32 startGlyphInner, int32 endGlyphIndex, int32 endGlyphInner,
					K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const;

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16  GetSelectionLine(PMLineSeg* pSelectionLine) const;
	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual bool16  GetHighlightLine(PMLineSeg* pHighlightLine, const PMLineSeg& maxTopBottom) const;

	/** Returns
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void  GetCaretLineAt(int32 offset, PMLineSeg* pCaretLine, const PMLineSeg& maxTopBottom) const;

	/** Return the selection mode set via SetSelectionMode() restricted to IWaxLineShape::kFlag_SelectionMask.
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual int32  GetSelectionMode() const;

	/** Set the given mode restricted to IWaxLineShape::kFlag_SelectionMask.
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual  void SetSelectionMode(int32 mode);

	/** Return the flags set via SetFlags()
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	int32 GetFlags() const;

	/** Just does a simple assignment, nothing special
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	void SetFlags(int32 flags);

	/**
	@note See IWaxRunShape for details on this method, its parameters and return values..
	*/
	virtual void GetBorderShadingHeight(int32 mode, PMLineSeg* pShadingHeight) const;

protected:
	/** Return the width of the given "simple" wax span.  Simple means just look at the widths of the glyphs, without any special transformation, etc.
	@param offset IN The desired start of the range
	@param length IN The length of the range.
			If length == -1, the length is to the end of the run.
			If length == 0, then just return the line that falls just before offset (i.e. between the bounds of the previous glyph and this glyph), rather than the glyph bounds of the range.
	@note EXTREME CAUTION should be used when using this method as it assumes many xForms are identity
								(i.e. it ignores pretty much everything except glyph widths)
	@note ALSO NOTE: the span must reside within an adjacent collection (a "line") of wax runs. It will NOT work on stacked collections.
	*/
	virtual bool16  CalculateSimpleSpanWidth(int32 offset, int32 length, PMLineSeg* pSpanWidth) const;

	/** Retrieve the ink bounds of the text within this run.
	@param pInkBounds OUT the bounds within which the ink will fall
	*/
	virtual void  GetTextInkBounds(PMRect *pInkBounds) const;

	/** return the outline adjustment for this run, if any - it is used to calculate ink bounds, as the outline of the resulting glyphs needs to be taken into consideration.
	@return the amount to be incorporated into the ink bounds.
	@note this is derived from the WaxRenderData associated with this run
	*/
	PMReal  GetWaxOutlineAdjustment() const;

	/** Return the selection-height of the owner of this waxRun.
	@param pOwnerLine OUT The selection-height of the owner.
	*/
	// Private note: The owner selection-height is LeadToBase for Roman and Embox for J with bottom at 0.
	virtual void  GetOwnerSelectionLine(PMLineSeg* pOwnerLine) const
		{
			InterfacePtr<const IWaxRun> waxRun(this, UseDefaultIID());
			waxRun->GetOwner()->GetHeight(pOwnerLine);
		}

	// TOP specific stuff
	/** Returns whether or not GetPerGlyphBounds needs to be called or not.
	*/
	bool16  DoPerGlyphBounds() const;
	/** For the given range of CHARACTERS within this run, return the set of bounds for each GLYPH in that range.
		Use pSpan as a base for the height of each bounds and the actual glyph width for the width of the bounds.
	@param offset IN The desired start of the range
	@param length IN The length of the range
	@param pSpan IN Specifies the base for the height of the returned bounds - this can be retrieved via the GetSelectionLine() method.
	@param pSetOfBounds OUT The set of bounds - 1 per glyph within the specified range.
	@note The input specifies the text index range (i.e. number of characters within the run), the output is the range of glyphs, which may or may not equal the number of characters.  See IWaxGlyphs for more details.
	@note Should only be called if DoPerGlyphBounds() returns kTrue
	@see IWaxGlyphs
	*/
	void  GetPerGlyphBounds(int32 offset, int32 length, PMLineSeg* pSpan, K2Vector<PMPolygon4> *pSetOfBounds) const;

	/** return the GlyphTranslationMatrix for the specified glyph.  Returns Identity if there is no matrix assigned.
	@param glyphIndex the desired glyph within this run (relative to this run)
	@return the matrix
	*/
	PMMatrix  GetGlyphTranslationMatrix(int32 glyphIndex) const;

	/** The IWaxLineShape::SelectionFlags associated with this waxRun */
	int32		fSelModeFlags;
	/**  The IWaxRunShape::WaxRunFlags associated with this waxRun */
	int32		fFlags;
};

#endif
