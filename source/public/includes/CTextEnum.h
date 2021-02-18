//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTextEnum.h $
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
#ifndef __CTextEnum__
#define __CTextEnum__


namespace Text {

	/** FirstLineOffsetMetric
		Also called "baseline offset" in the UI.

		The idea here is that every Text Frame has a UI selected value that
		tells the composer how that frame wants the text to align when at the
		top of the frame. Or, in other words, what metric is to be applied to
		the line to compute its height when at the top.

		The only wrinkle that the concept (and thus the values) end up being
		composition specific. Since we want the users to use terms that make
		sense to them based on their type of composition, we have to be prepared
		to deal with composers based on different types of composition not
		understanding all enum values.

		For example, a Japanese user might specify "ICF" for a frame, which
		tells Japanese composers to align the top of the ICF box of the line to
		the top of the frame. The problem is, Roman composers do not think in
		terms of ICF so that value means nothing to it. The reverse it also
		true - leading does not mean very much to Japanese composers either.

		Fortunately, the vast majority of the time there will be a good match
		between composer and text frame option, after all, that's how the user
		will specify it. When a composer encounters a value that is doesn't
		understand it is free to select a composer specific default behavior,
		such as Ascent for Roman composers.
	*/
	enum FirstLineOffsetMetric {
		// Roman
		kFLOLeading = 0,
		kFLOAscent,
		kFLOCapHeight,
		kFLOEmBoxHeight,
		kFLOxHeight,
		kFLOFixedHeight,

		// More J only stuff...
		kFLOEmBoxDepth,		// offset from bottom
		kFLOICFBottomInset,		// offset from bottom
		kFLOICFTopInset,		// offset from top

//>>>>> new values must be inserted here, i.e., just above kFLOCount <<<<<<<
		kFLOCount,  //the number of actually defined enumerators

		kFLO_NoShuffleTop = kFLOCount,		// prevents the line set with this value to shuffle to the top of a parcel

		// The last value. The maximum number of members is limited by
		// the specification of WaxLineImpl::TOFAlignment:5
		kFLOInvalid	= 31
	};


	/**	GridAlignmentMetric.
		Specifies what part of the tile and grid should be aligned to each other
		The offset into the tile that corresponds to each metric is used to hang
		the tile on the grid by the Grid Manager. This offset is computed by the
		composer, and passed to the Tiler along with the metric from below.

		kGAEmBottom - the bottom of the tile's embox is aligned to the bottom
					of the underlying grid box, or grid line if not box based.

		kGABaseline - the tile's baseline is aligned to the Roman baseline of
	                		the underlying grid box, or to the grid line if not box based.

		kGAEmCenter - the center of the tile's embox (set as 1/2 line height)
					is aligned to the center of the underlying grid box, or
					grid line if not box based.

		kGAEmTop - the top of the tile's embox is aligned to the top of the
					underlying grid box, or grid line if not box based.

		kGAICFTop - the top of the tile's ICFBox is aligned to the top of the
					grid's ICF box, or to the line if not box based.

		kGAICFBottom - the bottom of the tile's ICFBox is aligned to the bottom
					of the grid's ICF box, or to the line if not box based.

		kGACapHeight - the tile's CapHeight is aligned to the Roman cap height
					of the underlying grid box, or to the grid line if not box based.
	*/
	enum GridAlignmentMetric {
		kGANone = 0,
		kGABaseline,
		kGAEmTop,
		kGAEmCenter,
		kGAEmBottom,
		kGAICFTop,
		kGAICFBottom,
		kGACapHeight
	};


	/** LeadingModel
		Specifies how line leading is measured and how it results in line
		placement in the Parcel. The first line in the Parcel is placed based on
		first line offset, which does not depend on the leading model. Changing
		the leading of a line results in different line placement for current
		and subsequent lines depending on the leading model.
	*/
	enum LeadingModel {		// Leading is measured from the:
		kRomanLeadingModel = 0,	// Current Roman baseline to previous Roman baseline

		kJAkiBelow,					// Current embox top to next embox top
									// (InDesign-J 1.0 Gyou-okuri model)

		kJAkiAbove,					// Current embox top to previous embox top
									// (Opposite of ID-J: Aki is above the line)

		kCenterLeadingModel,		// Current embox center to previous embox center

		kForcedSpaceAfter,			// Similar to kJAkiBelow except that when
									// lines with this leading model are next
									// a different leading model no proportional
									// adjustments are made, this line "wins".

        kCenterDown					// Current embox center to next embox center
	};


	/** VerticalJustification.
		Vertical Justification values.
	*/
	enum VerticalJustification {
		kVJTop = 0,
		kVJCenter,
		kVJBottom,
		kVJJustify,

		// The last value. The maximum number of members is limited by this
		// value and if you wish to change it you will have to track down all
		// the code that assumes that they can represent this in 4 bits. See
		// TextCellData.cpp for starters.
		//
		kVJInvalid = 15,

		kVJNumValues
	};
	
	/** AutoSizeDimension
		Specifies the auto sizing dimension for text frames.
		kASOff							- auto sizing is off, user needs to resize on its own manually.
		kASHeightOnly					- auto sizing is on in height dimension only i.e. text frame may expand from top and bottom.
		kASWidthOnly					- auto sizing is on in width dimension only i.e. text frame may expand from left and right.
		kASHeightAndWidth				- auto sizing is on in both the dimensions i.e. text frame may expand from anywhere.
		kASHeightAndWidthProportional	- auto sizing is on in both the dimensions proportinally i.e. text frame may expand in both dimensions proportionally.
	*/
	enum AutoSizeDimension {
		kASOff = 0,
		kASHeightOnly,
		kASWidthOnly,
		kASHeightAndWidth,
		kASHeightAndWidthProportional,

		// The last value. The maximum number of members is limited by this
		// value and if you wish to change it you will have to track down all
		// the code that assumes that they can represent this in 4 bits. 
		//
		kASInvalid = 15,
	};	


	/** StartBreakLocation.
		start at or break after.
	*/
	enum StartBreakLocation {
		kNoForcedBreak = 0,
		kStartAnywhere = 0,
		kAtColumn,
		kAtPage,
		kAtFrameBox,
		kAtOddPage,
		kAtEvenPage
		};

	/** DropCapDetailedSettings.
		Dropcap sizing & positioning detailed settings.

		Optical settings are trying to align the glyph ink itself to the dropcap bounding box.
		kHonorLeftGlyphEdge makes the left edge of the ink align to where the left edge of the ink
			at the "body text size" align.
		kHonorDescenders sizes dropcaps with descenders such that the descender hangs no lower
			than the descender at the body text size.

		Japanese Settings are used to align the dropcap glyph within a frame grid.
		The dropcap can be scaled up or down to fit exactly within the grid boxes, or
		the dropcap width can be padded so that the next characters are on the grid.
	*/
	enum DropCapDetailedSettings {

		kDCD_OpticalSettings	= 0x00FF,
		kDropCapDetail_None 	= 0,
		kHonorLeftGlyphEdge 	= 1,
		kHonorDescenders 		= 2,
//		kHonorTopGlyphEdge 		= 4,
//		Contoured right edge settings would go here...

		kDCD_JapaneseSettings 		= 0xFF00,
		kFitDropCapOnJapaneseGrid	= 0x0F00,
		kPadWidth4JapaneseGrid 	= 0x0100,
		kScaleUp4JapaneseGrid 		= 0x0200,
		kScaleDn4JapaneseGrid 		= 0x0400,

		kDCD_DefaultOnState = 0x0101		// left, padding
		};

	typedef int32	GlyphID;
}

const Text::GlyphID kInvalidGlyphID = -1;

// Used by underline and strikethrough, means use the font to calculate the weight/offset for the line
const PMReal kUseFontForULSTWeightOffset = -9999;



#endif	// __CTextEnum__
