//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxRunShape.h $
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
//========================================================================================

#pragma once
#ifndef __IWaxRunShape__
#define __IWaxRunShape__

#include "IPMUnknown.h"
#include "PMMatrix.h"
#include "DrawPassInfo.h"
#include "TextID.h"

class IGraphicsContext;

/** Interface for accessing the shape of the wax run. I.e. it's various bounds and related flags. Used mostly for selection and highlighting.
	@ingroup text_wax
	@see CWaxRunShape, IWaxLineShape
*/
class IWaxRunShape : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXRUNSHAPE };


	/** Retrieve the Ink Bounds for this wax run.  Called by IWaxLineShape. For more details on parameters and description, see IWaxLineShape.

	@param pInkBounds OUT The overall bounds of this run.

	@param passList OUT The list of Draw() passes that this Run requires to draw. This includes the text, local adornments and OPTIONAL global adornments.
		- The only IGlobalTextAdornment that need to be added in this list are those whose CheckCouldDraw() method returns kTrue
			AND whose CheckGetCheckIsActive() method return kTrue. (there is no reason for the WaxRuns and WaxLines to save
			pass information for global adornments that are not optional - the containing parcel has access to the same information
			through the ITextSessionData interface)

		When called, the passList may not be empty so it is important to avoid creating duplicates or redundant pass information.
		The rule is that a required pass always overrides one or more optional passes. However, lacking a required pass, any number
		of optional passes may simultaneous exist. I.e. use the following pattern:

		@code
		// -- required pass
		Text::DrawPassInfo	required(pass, kInvalidClass);
		if (passList->Location(required) == -1)
			passList->Append(required);									// optionals remain.

		 // -- optional pass
		 Text::DrawPassInfo	optional(pass, someClassID);
		if (passList->Location(required) == -1)							// Note the use of required as parameter.
			passList->Append(optional);
		@endcode

	@see IWaxLineShape, IGlobalTextAdornment, ITextAdornment, IWaxRunText
	*/
	virtual void GetInkBounds(PMRect* pInkBounds, Text::DrawPassInfoList* passList) const = 0;

	/** Get the set of polygons representing the area of the wax representing the glyphs representing the text.
	(i.e. convert TextRange to Bounding box)

	@param offset IN where in the run to start the computation for the highlight (0 for the start of the waxRun)
	@param length IN the length of the text to highlight (-1 can be used to denote the rest of the text to the end of the waxRun)
	@param pSetOfBounds OUT the resulting set of bounds.  There may be none, one, or many bounds that apply to this run.

	@note	The Wax Bounds represents the true area of the run.

	@note: the DIFFERENCE between the wax bounds and the highlight bounds is that the latter can be
			modified due to the context of the waxRun. E.g. if the leading is too small the wax bounds can
			overlap, so the higher level code restricts the top/bottom of the highlight.  Also, if the font
			is smaller in this run, the upper level code may ask for consistent highlighting and can expand
			the bounds.  Super/Subscripts are another example. (and Drop Caps are another issue entirely.)
	*/
	virtual void GetWaxBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds) const = 0;

	/** Get the set of polygons representing the area to be highlighted when the given range of text is highlighted, taking
	into consideration the context of the run. (i.e. convert TextRange to Bounding box)

	@param offset IN where in the run to start the computation for the highlight (0 for the start of the waxRun)
	@param length IN the length of the text to highlight (-1 can be used to denote the rest of the text to the end of the waxRun)
	@param pSetOfBounds OUT the resulting set of bounds.  There may be none, one, or many bounds that apply to this run.
	@param highlightAdjust IN Used to indicate that an amount should be shaved off the highlight on the indicated side
		(used to prevent double XOR problems when two (adjacent) waxRun's highlights touch).
	@param maxTopBottom IN is used to prevent double XOR problems when waxRuns are too close together.
			- any highlight should be trimmed to these bounds (if DeltaY() is non-zero).

	@return kTrue if you can use XOR to highlight the text.

	@note See notes in GetWaxBounds for the difference between waxBounds and highlightBounds.
	*/
	virtual bool16 GetHighlightBounds(int32 offset, int32 length, K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const = 0;

	virtual bool16	GetHighlightBoundsME(int32 runGlyphStartIndex, int32 start, int32 startInner, int32 end, int32 endInner,
									K2Vector<PMPolygon4> *pSetOfBounds, PMRect& highlightAdjust, const PMLineSeg& maxTopBottom) const = 0;

	/** Get the selection line (top/bottom) for THIS run.
	@note: this is NOT necessarily the actual highlight line - that is determined by looking at all the runs in the collection.

	@param pSelectionLine OUT the calculated line.

	@return kTrue if you can use XOR to highlight the text.

	@note See notes in GetWaxBounds for the difference between waxBounds (in this case, selectionLine) and highlightBounds (in this case, highlightLine).
	*/
	virtual bool16 GetSelectionLine(PMLineSeg* pSelectionLine) const = 0;

	/** Get the highlight line (top/bottom) for this run within its collection.
	@note: this depends on the collection having processed each run's Selection Line (which is presented to this run as maxTopBottom).

	@param maxTopBottom Constraint on the caret height - pHighlightLine will be trimmed to maxTopBottom (if DeltaY() is non-zero).

	@return kTrue if you can use XOR to highlight the text.

	@note See notes in GetWaxBounds for the difference between waxBounds (in this case, selectionLine) and highlightBounds (in this case, highlightLine).
	*/
	virtual bool16 GetHighlightLine(PMLineSeg* pHighlightLine, const PMLineSeg& maxTopBottom) const = 0;


	/** Returns the caret bounds at the given position.  I.e. the bounds of the caret.

	@param offset	A valid offset in to the wax, relative to this run.
	@param pCaretLine		The returned bounds of the caret. See IWaxLineShape::GetCaretLineAt() for more details.
	@param maxTopBottom Constraint on the caret height - pCaretLine will be trimmed to maxTopBottom (if DeltaY() is non-zero).
	@see IWaxLineShape
	*/
	virtual void GetCaretLineAt(int32 offset, PMLineSeg* pCaretLine, const PMLineSeg& maxTopBottom) const = 0;

	/** Property Accessor for the wax run Selection Mode.
		@see IWaxLineShape::SelectionMode, GetSelectionMode. */
	virtual int32 GetSelectionMode() const = 0;
	/** Property Accessor for the wax run Selection Mode.
		@see IWaxLineShape::SelectionMode, SetSelectionMode. */
	virtual void SetSelectionMode(int32 mode) = 0;

	/** WaxRun flags */
	enum {
	/** Run is in a stacked collection and is the first in the collection */
		kFlag_IsFirstStacked		= 0x00000001,
	/** Run is in a stacked collection and is the last in the collection */
		kFlag_IsLastStacked		= 0x00000002,

	/** Area in which 3rd parties can add flags. */
		kFlag_ReservedForImplementors	= 0xffff0000
	} WaxRunFlags;

	/**Property Accessor for WaxRunFlags in this interface. */
	virtual int32 GetFlags() const = 0;
	/** Property Accessor for WaxRunFlags in this interface. - Caller must do any ANDing or ORing. */
	virtual void SetFlags(int32 flags) = 0;				// Caller must do any ANDing or ORing.

	/** Returns the shading height for this wax run based on the input shading mode.
	@param shadingHeightMode IN - @see IWaxLineShape::ShadingHeightMode - different modes for determining shading height.
	@param pShadingHeight OUT - pointer to the line segment containing shading height.
	*/
	virtual void GetBorderShadingHeight(int32 mode, PMLineSeg* pShadingHeight) const = 0;

};

#endif
