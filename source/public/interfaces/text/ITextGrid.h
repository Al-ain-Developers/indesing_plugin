//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextGrid.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextGrid__
#define __ITextGrid__


#include "IPMUnknown.h"
#include "PMRect.h"
#include "TextID.h"
#include "CTextEnum.h"


/** 
	@ingroup text_layout
*/
class ITextGrid : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTGRID };

		//
		// Returns the top-to-top distance between grid cells. For single
		// dimensional (baseline) grids, this is simply the distance between
		// adjacent lines. For two dimensional cell-based (CJK) grids, this is
		// the distance between the same position on adjacent cells.
		//
		// Text Frames which do not have grids enabled will return 0.0.
		//
		virtual PMReal 	GetVerticalSpacing() const = 0;

		//
		// Some grids, such as InDesign J text frame grids will have
		// a text size that is a component of vertical spacing.  
		// GetGridHasTextSize returns whether or not the grid has
		// a text size.  And GetGridTextSize returns the text size.
		//
		virtual bool16 GetGridHasTextSize() const = 0;
		virtual PMReal GetGridTextSize() const = 0;
	
		//
		// Adjusts the top and bottom points by moving them down (or up)
		// relative to the Text Frame to achieve the desired vertical
		// alignment.
		//
		// pYTop			Address of top and bottom values for the tile to
		// pYBottom			be aligned.
		//
		// 					These values are adjusted only if the the grid was
		//					effective.
		//
		// alignmentMetric	These two argument work together to determine what
		// alignmentOffset	part of the above tile is aligned to what part of
		//					the grid.
		//
		//					The alignmentMetric determines WHAT position in the
		//					grid is to be aligned to.
		//
		//					kGABaseline				Roman baseline
		//					kGAEmTop/Center/Bottom	Top/Center/Bottom of the
		//											Em Box
		//					kGAICFTop/Center/Bottom	Top/Center/Bottom of the
		//											ICF Box
		//
		//					The alignmentOffset then determines what position
		//					in the tile is the snap point as an offset from
		//					*pYBottom. A value of zero would simply have the
		//					bottom of the tile aligned to the specified point
		//					on the grid.
		//
		//					A negative value will cause the tile to align above
		//					*pYBottom and a positive value will cause the tile
		//					to align below *pYBottom.
		//
		//					To align Roman composed text to the Roman baseline
		//					of any grid simply specify (kGABaseline, 0.0).
		//
		//					To align Japanese composed text to top of the EmBox
		//					of a grid simply specify (kEmBoxTop, -EmBoxHeight).
		//
		// pParcelRelative	The value pointed to by this argument will be set
		//					to indicate if the location of the effective grid
		//					is relative to the Parcel (kTrue) or not (kFalse).
		//
		//					Note that this value DOES NOT indicate that tile
		//					was adjusted by the grid. Implementations should
		//					return the appropriate value even if the values
		//					were not adjusted.
		//
		//					This information is used by the Text System to
		//					determine what should happen to the composed
		//					WaxLine when the Parcel is moved. If the
		//					effective grid is local then the WaxLine can be
		//					left alone, otherwise it will be recomposed.
		//
		// Returns			kFalse	The adjustment forced us outside the Parcel.
		//					kTrue	The final position, whether it was moved or
		//							not, is within the Parcel.
		//
		virtual bool16	AlignVertically(PMReal *pYTop, PMReal *pYBottom,
									Text::GridAlignmentMetric alignmentMetric,
									PMReal alignmentOffset,
									bool16 *pParcelRelative) const = 0;

};
#endif

