//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxLineShape.h $
//  
//  Owner: zwilliam
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
#ifndef __IWaxLineShape__
#define __IWaxLineShape__

#include "IPMUnknown.h"
#include "TextID.h"
#include "GraphicsData.h"
#include "DrawPassInfo.h"

class PMRect;
class PMLineSeg;

/** Interface for accessing the shape of the wax line. I.e. it's various bounds and related flags. Used mostly for selection and highlighting.
	@ingroup text_wax
*/
class IWaxLineShape : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXLINESHAPE };

	/** Draw the waxLine. This includes the text associated with this wax line and any adornments (including global adornments) attacted to it.
		The method should inspect all objects (i.e. adornments) associated with it and match any that relate to this pass.
		Only objects matching this particular pass should be drawn.
		This method will (also) ask each waxRun (via IWaxRunText) to draw itself.

	@param gd IN Where to draw.
	@param iShapeFlags IN Flags defining this type of draw. See IShape "drawing flags" enum.
	@param pass IN This particular phase of drawing. The line may not necessarily have anything to draw on every pass.
	@param areaToDraw IN If this is non-nil then it specifies the rectangle that will be drawn and may be used for optimizing what is actually drawn.
	@see IShape, IGlobalTextAdornment, ITextAdornment, IAdornmentShape, IWaxRunText, DrawPassInfo
	*/
	virtual void Draw(GraphicsData* gd, int32 iShapeFlags, Text::DrawPassInfo::Pass pass, const PMRect* areaToDraw = nil) = 0;

	/** Retrieve the Ink Bounds for this wax line.  The ink bounds is the area (rectangle) in which the ink will draw.
	It is used primarily for invalidation.  The caller is guaranteed that no ink will draw outside this rectangle for any thing associated with this wax run.

	This method will ask each waxRun for its bounds and aggregate them (union).

	@param pInkBounds OUT Should be initialized to empty when called. It will be untouched if there is no ink drawn by this run.
		The bounds will include the effect of text, local adornments and any IGlobalTextAdornment whose GetHasInkBounds()
		method returns kTrue.

	@note The ink bounds are in waxLine coordinate space (i.e. "within the line" space).
		(The same space as the waxRun itself - no xForm need be done at the waxLine level).

	@see IGlobalTextAdornment, ITextAdornment, IWaxRunShape
	*/
	virtual void GetInkBounds(PMRect * pInkBounds) = 0;

	/** Return the number of passes needed to draw this run.
	@see DrawPassInfo
	*/
	virtual int32 GetPassCount() = 0;

	/** Return the pass information structure for the nth Pass.  Typically this information is collected in a sorted list and then processed (after all lines in the parcel have been asked).
		@note The pass information at this level DOES NOT include those global text adornments whose
			IGlobalTextAdornment::CheckCouldDraw() method returns kFalse. That class of adornments are considered to be attached
			to ALL WaxRuns and therefore it is pointless to make the WaxLine remember them - this is left upto the Parcel container
			to sort out. See IWaxRunText for more information.

		@note The DrawPassInfo is NOT sorted.
	*/
	virtual Text::DrawPassInfo GetNthPass(int32 n) = 0;

	/** Parameters for the selection height (describe what the top and bottom of the selection should be derived from.)
		It is divided into two parts:  General Range and Overrides.  Each run in the line inspects these flags and computes its selection height.
		So, the flags pertain to a particular run and is sometimes constrained by the line's parameters.
	*/
	enum SelectionFlags {
		/** Ascent to Descent */
		kFlag_SelectionAscToDesc			= 0x00000000,
		/** Ascent to Baseline */
		kFlag_SelectionAscToBase			= 0x00000001,
		/** (Top of) Leading to Baseline - all other flags are ignored if this is set */
		kFlag_SelectionLeadToBase			= 0x00000002,	// all other flags ignored
		/** Embox based */
		kFlag_SelectionJapanese			= 0x00000004,	// Embox based

		/** Mask for the above bits */
		kFlag_SelectionRangeMask			= 0x0000000f,

		/** Respect the baseline shift, if any */
		kFlag_SelectionRespectShift 		= 0x00000010,
		/** ignore this run's Top when computing entire line's bounds */
		kFlag_SelectionSkipThisYTop		= 0x00000020,
		/** ignore the line's Top when computing a particular run's bounds*/
		kFlag_SelectionSkipLineYTop		= 0x00000040,
		/** ignore this run's Bottom  when computing entire line's bounds */
		kFlag_SelectionSkipThisYBottom	= 0x00000080,
		/** ignore the line's Bottom when computing a particular run's bounds*/
		kFlag_SelectionSkipLineYBottom	= 0x00000100,

		/** Mask for the above bits */
		kFlag_SelectionMask					= 0x000001ff,

		/** Reserved area for 3rd party flags */
		kFlag_ReservedForImplementors	= 0xffff0000
	};

	/** Really just a grouping of SelectionFlags for ease of use */
	enum SelectionMode {
		kSelectionMode_AscToDesc	= kFlag_SelectionAscToDesc,
		kSelectionMode_DropCap 		= (kFlag_SelectionAscToBase | kFlag_SelectionRespectShift | kFlag_SelectionSkipThisYTop |
																kFlag_SelectionSkipThisYBottom | kFlag_SelectionSkipLineYBottom),
		kSelectionMode_Anchor 		= kFlag_SelectionLeadToBase,
		kSelectionMode_Japanese		= kFlag_SelectionJapanese,

		kSelectionMode_Default		= kSelectionMode_AscToDesc
	};

	/** */
	virtual int32 GetSelectionMode() const = 0;
	/** @note ADDs mode to the current mode - there is no way to clear existing flags */
	virtual void SetSelectionMode(int32 mode) = 0;

	/** Return whether this waxLines has overlapping highlight rectangles. */
	virtual bool16 GetHasOverlappingHiliteRects() = 0;

	/** Get the selection line (top/bottom) for this line.  This is typically used to determine the constraints on the height of the highlight for this waxLine.
	See GetCaretLineAt for more details on this and IWaxLineHilite for more details on highlighting, in general.

	@param pSelectionLine OUT the calculated line.
	@see IWaxLineHilite
	*/
	virtual void GetSelectionLine(PMLineSeg* pSelectionLine) = 0;
	/** Returns the caret bounds at the given position.  I.e. the bounds of the caret.

	@param offset	A valid offset in to the wax, relative to this run.
	@param pCaretLine		The returned bounds of the caret.
						The direction of the caret can be determined by checking for a logical width of 0.
						In other words, if the caret is vertical, the width will be 0 and if the caret is horizontal, the height will be 0.
						NOTE: it is possible that in the future the caret could be some other angle, so that should be accounted for.
	@param maxTopBottom Constraint on the caret height - pCaretLine will be trimmed to maxTopBottom (if DeltaY() is non-zero).
	*/
	virtual void GetCaretLineAt(int32 offset, PMLineSeg* pCaretLine, const PMLineSeg& pMaxTopBottom) const = 0;

    /* Cached data type related enumerators */
    enum CachedDataType {
        /* Flag depicting cached Ink bounds and PassInfo etc. */
        kCachedDataType_Ink = 0,
        
        /* Flag depicting cached Shading related data like shading height mode, shading bounds etc. */
        kCachedDataType_Shading = 1,
        
        /* Flag depicting cached Shading related data like border height mode, border bounds etc. */
        kCachedDataType_Border = 2,

		/* Flag depicting cached Column Rule related data like column rule height mode, bounds etc. */
		kCachedDataType_ColumnRule = 4
    };
    
	/** Invalidate cached information (if any) held by this interface with the aim that subsequent calls to this interface will (automatically and silently) re-compute the original data.

     @param invalAll    A boolean value depicting whether all the cached content needs to be invalidated, or the specific cached data type, passed as second argument, needs to be invalidated. Its default value is kTrue.
     
     @param cachedDataType	Specific cached data type to be invalidated. This will be honored only if the first arugment passed has kFalse value. Default value is kCachedDataType_Ink

    @note that this does NOT cause screen inval with WaxLine::Inval()
	*/
    virtual void InvalCachedData(const bool16 invalAll = kTrue, const IWaxLineShape::CachedDataType cachedDataType = IWaxLineShape::kCachedDataType_Ink) = 0;

	/** Return whether or not this object has cached data for the input type.
     
    @param cachedDataType	Specific cached data type, for which the presence of caching data needs to be returned. Default value is kCachedDataType_Ink
     @return - kTrue indicates cached data for the input type is available, and kFalse for otherwise.
     */
    virtual bool16 GetHasCachedData(const IWaxLineShape::CachedDataType cachedDataType = IWaxLineShape::kCachedDataType_Ink) const = 0;

	/**
	The implementation is asked to re-compute the InkBounds.
	*/
	virtual void UpdateInkBounds(const PMRect* pInitialBounds = nil) = 0;

	/* Paragraph shading height determination flags */

	enum ShadingHeightFlags {
		/* Top Edge Ascent */
		kFlag_ShadingTopFlag_Ascent			= 0x00000001,
		/* Top Edge Leading */
		kFlag_ShadingTopFlag_Leading		= 0x00000002, 
		/* Top Edge Baseline */
		kFlag_ShadingTopFlag_Baseline = 0x00000004,
		/* Top Edge Cap Height */
		kFlag_ShadingTopFlag_CapHeight		= 0x00000008,
		/* Top Edge Em Box - Useful for CJK feature set */
		kFlag_ShadingTopFlag_EmBox = 0x00000010,
		/* Top Edge x Height */
		kFlag_ShadingTopFlag_xHeight = 0x00000020,
		/* Top Edge Em Box center - Useful for CJK feature set */
		kFlag_ShadingTopFlag_EmBoxCenter = 0x00000040,
		/* Mask for Top Edge */
		kFlag_ShadingTopRangeMask			= 0x000000ff,

		/* Bottom Edge Baseline*/
		kFlag_ShadingBottomFlag_Baseline	= 0x00000100,
		/* Bottom Edge Descent */
		kFlag_ShadingBottomFlag_Descent		= 0x00000200,
		/* Bottom Edge Em Box - Useful for CJK feature set */
		kFlag_ShadingBottomFlag_EmBox = 0x00000400,
		/* Bottom Edge Em Box center - Useful for CJK feature set */
		kFlag_ShadingBottomFlag_EmBoxCenter = 0x00000800,
		/* Mask for Bottom Edge */
		kFlag_ShadingBottomRangeMask = 0x00000f00,
	};

	enum ShadingHeightMode 
	{
		/** Ascent to Descent */
		kFlag_ShadingHeightAscToDesc		= kFlag_ShadingTopFlag_Ascent		| kFlag_ShadingBottomFlag_Descent,
		/** Ascent to Baseline */
		kFlag_ShadingHeightAscToBase		= kFlag_ShadingTopFlag_Ascent		| kFlag_ShadingBottomFlag_Baseline,
		/** Ascent to EmBox*/
		kFlag_ShadingHeightAscToEmBox		= kFlag_ShadingTopFlag_Ascent		| kFlag_ShadingBottomFlag_EmBox,
		/** Ascent to EmBox center */
		kFlag_ShadingHeightAscToEmBoxCenter = kFlag_ShadingTopFlag_Ascent		| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** Leading to Descent */
		kFlag_ShadingHeightLeadToDesc		= kFlag_ShadingTopFlag_Leading		| kFlag_ShadingBottomFlag_Descent,
		/** Leading to Baseline*/
		kFlag_ShadingHeightLeadToBase		= kFlag_ShadingTopFlag_Leading		| kFlag_ShadingBottomFlag_Baseline,
		/** Leading to EmBox*/
		kFlag_ShadingHeightLeadToEmBox		= kFlag_ShadingTopFlag_Leading		| kFlag_ShadingBottomFlag_EmBox,
		/** Leading to EmBox Center */
		kFlag_ShadingHeightLeadToEmBoxCenter = kFlag_ShadingTopFlag_Leading		| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** Baseline to Descent*/
		kFlag_ShadingHeightBaseToDesc		= kFlag_ShadingTopFlag_Baseline		| kFlag_ShadingBottomFlag_Descent,
		/** Baseline to Baseline*/
		kFlag_ShadingHeightBaseToBase		= kFlag_ShadingTopFlag_Baseline		| kFlag_ShadingBottomFlag_Baseline,
		/** Baseline to EmBox*/
		kFlag_ShadingHeightBaseToEmBox		= kFlag_ShadingTopFlag_Baseline		| kFlag_ShadingBottomFlag_EmBox,
		/** Baseline to EmBox Center */
		kFlag_ShadingHeightBaseToEmBoxCenter = kFlag_ShadingTopFlag_Baseline	| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** Embox height to Descent*/
		kFlag_ShadingHeightEmBoxToDesc		= kFlag_ShadingTopFlag_EmBox		| kFlag_ShadingBottomFlag_Descent,
		/** Embox height to Baseline*/
		kFlag_ShadingHeightEmBoxToBase		= kFlag_ShadingTopFlag_EmBox		| kFlag_ShadingBottomFlag_Baseline,
		/** Embox top to bottom*/
		kFlag_ShadingHeightEmBoxToEmBox		= kFlag_ShadingTopFlag_EmBox		| kFlag_ShadingBottomFlag_EmBox,
		/** Embox top to Embox bottom center*/
		kFlag_ShadingHeightEmBoxToEmBoxCenter = kFlag_ShadingTopFlag_EmBox		| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** xHeight to Descent*/
		kFlag_ShadingHeightxHeightToDesc	= kFlag_ShadingTopFlag_xHeight		| kFlag_ShadingBottomFlag_Descent,
		/** xHeight to Baseline*/
		kFlag_ShadingHeightxHeightToBase	= kFlag_ShadingTopFlag_xHeight		| kFlag_ShadingBottomFlag_Baseline,
		/** xHeight to EmBox*/
		kFlag_ShadingHeightxHeightToEmBox	= kFlag_ShadingTopFlag_xHeight		| kFlag_ShadingBottomFlag_EmBox,
		/** xHeight to EmBox center*/
		kFlag_ShadingHeightxHeightToEmBoxCenter = kFlag_ShadingTopFlag_xHeight	| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** Cap Height to Descent */
		kFlag_ShadingHeightCapHeightToDesc	= kFlag_ShadingTopFlag_CapHeight	| kFlag_ShadingBottomFlag_Descent,
		/** Cap Height to Baseline */
		kFlag_ShadingHeightCapHeightToBase	= kFlag_ShadingTopFlag_CapHeight	| kFlag_ShadingBottomFlag_Baseline,
		/** Cap Height to EmBox*/
		kFlag_ShadingHeightCapHeightToEmBox	= kFlag_ShadingTopFlag_CapHeight	| kFlag_ShadingBottomFlag_EmBox,
		/** Cap Height to EmBox Center*/
		kFlag_ShadingHeightCapHeightToEmBoxCenter = kFlag_ShadingTopFlag_CapHeight	| kFlag_ShadingBottomFlag_EmBoxCenter,

		/** Embox Top Center to Descent */
		kFlag_ShadingHeightEmBoxCenterToDesc = kFlag_ShadingTopFlag_EmBoxCenter | kFlag_ShadingBottomFlag_Descent,
		/** Embox Top Center to Baseline */
		kFlag_ShadingHeightEmBoxCenterToBase = kFlag_ShadingTopFlag_EmBoxCenter | kFlag_ShadingBottomFlag_Baseline,
		/** Embox Top Center to EmBox*/
		kFlag_ShadingHeightEmBoxCenterToEmBox = kFlag_ShadingTopFlag_EmBoxCenter | kFlag_ShadingBottomFlag_EmBox,
		/** Embox Top Center to EmBox Bottom Center*/
		kFlag_ShadingHeightEmBoxCenterToEmBoxCenter = kFlag_ShadingTopFlag_EmBoxCenter | kFlag_ShadingBottomFlag_EmBoxCenter,
	};

	/** Returns the shading height for this waxline based on the input shading mode and the roman baseline passed.	
	@param shadingHeightMode IN - @see IWaxLineShape::ShadingHeightMode - different modes for determining shading height.
	@param pShadingHeight OUT - pointer to the line segment containing shading height.
	@param romanBaseline IN - this is the roman baseline for this wax line. In different locales and feature sets
	this value may differ. Typically for English this value is 0 and Japanese it's (-Embox bottom).
	*/
	virtual void GetShadingHeight(ShadingHeightMode shadingHeightMode, PMLineSeg* pShadingHeight, const PMReal & romanBaseline) = 0;

	/** Returns the border height for this waxline based on the input border mode and the roman baseline passed.	
	@param borderHeightMode IN - @see IWaxLineShape::ShadingHeightMode - different modes for determining border height.
	@param pBorderHeight OUT - pointer to the line segment containing border height.
	@param romanBaseline IN - this is the roman baseline for this wax line. In different locales and feature sets
	this value may differ. Typically for English this value is 0 and Japanese it's (-Embox bottom).
	*/
	virtual void GetBorderHeight(ShadingHeightMode borderHeightMode, PMLineSeg* pBorderHeight, const PMReal & romanBaseline) = 0;

	/** Returns the cached shading bounds for this waxline.
	@param shadingBounds OUT - cached shading bounds.
	@return - kTrue indicates there are valid shading bounds available, and kFalse for otherwise.
	*/
	virtual bool16 GetShadingBounds(PMRect& shadingBounds)const = 0;

	/** Returns the cached border bounds for this waxline.
	@param borderBounds OUT - cached border bounds.
	@return - kTrue indicates there are valid border bounds available, and kFalse for otherwise.
	*/
	virtual bool16 GetBorderBounds(PMRect& borderBounds)const = 0;

	/** Sets the shading bounds to be cached for this waxline.
	@param shadingBounds IN - shading bounds to be set for this waxline.
	*/
	virtual void SetShadingBounds(const PMRect& shadingBounds) = 0;

	/** Sets the border bounds to be cached for this waxline.
	@param borderBounds IN - border bounds to be set for this waxline.
	*/
	virtual void SetBorderBounds(const PMRect& borderBounds) = 0;

	/** Returns the column rule for this waxline based on the input border mode and the roman baseline passed.
		@param columnHeightMode IN - @see IWaxLineShape::ShadingHeightMode - different modes for determining column rule height.
		@param pColumnHeight OUT - pointer to the line segment containing column rule height.
		@param romanBaseline IN - this is the roman baseline for this wax line. In different locales and feature sets
		this value may differ. Typically for English this value is 0 and Japanese it's (-Embox bottom).
	*/
	virtual void GetColumnRuleHeight(ShadingHeightMode columnHeightMode, PMLineSeg* pColumnHeight, const PMReal & romanBaseline) = 0;
};

#endif
