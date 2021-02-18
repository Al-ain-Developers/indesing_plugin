//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IJustificationStyle.h $
//  
//  Owner: eric_menninga
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
#ifndef __IJustificationStyle__
#define __IJustificationStyle__


#include "IPMUnknown.h"
#include "IWaxLine.h"
#include "TextID.h"


/**
	Justification style contains mostly Roman justification related data from text attributes.
	Part of the kComposeStyleBoss.
	@see IDrawingStyle.
	@ingroup text_comp_style
*/
class IJustificationStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IJUSTIFICATIONSTYLE };

		enum JustificationMethod {
            /** Standard - latin like justification
				letter and word spacing, glyph scaling, as is it done for Roman; letter spacing is only used between
				non-connection letters
            */ 
			kJustifMethodDefault = 0,
            /** Arabic (Legacy)
				put kashidas in every connecting place, with an even fractional width. This is a mode for compatibility
				with InDesign ME 1.5 and even earlier PageMaker ME versions.
            */ 
			kJustifMethodArabic,
            /** Naskh
					kashida width: value from GetKashidaWidth is used to determine how much kashida to add
					connection stretching: OpenType feature strl/r if available
					justification alternates: if available in the font
            */ 
			kJustifMethodNaskh,
            /** Naskh with Kashida insertion only
					kashida width: value from GetKashidaWidth is used to determine how much kashida to add
					connection stretching: OpenType feature strl/r is not applied
					justification alternates: none
            */ 
			kJustifMethodTraditionalNaskhTatweel,
            /** Naskh with Kashida insertion and Stretched Connections 
					kashida width: value from GetKashidaWidth is used to determine how much kashida to add
					connection stretching: OpenType feature strl/r if available
					justification alternates: none
           */ 
			kJustifMethodTraditionalNaskhKashida,
           /** Naskh with Kashida insertion only. Uses fractional widths based on space left to justify
					kashida width: value from GetKashidaWidth is used to determine how much kashida to add
					connection stretching: OpenType feature strl/r is not applied
					justification alternates: none
            */ 
			kJustifMethodTraditionalNaskhTatweelFrac,
            /** Naskh with Kashida insertion and Stretched Connections.  Uses fractional widths based on space left to justify
					kashida width: value from GetKashidaWidth is used to determine how much kashida to add
					connection stretching: OpenType feature strl/r if available
					justification alternates: none
           */ 
			kJustifMethodTraditionalNaskhKashidaFrac
		};


		/**
		This sets the "range kerning" value -- know as tracking to non-PageMaker users.
		*/
		virtual void SetKernAfter(PMReal kern) = 0;

		/**
		This returns the "range kerning" value -- know as tracking to non-PageMaker users.
		*/
		virtual PMReal GetKernAfter() const = 0;

		/**
		Get justification method. Only used by world ready composer.
		@return JustificationMethod
		*/
		virtual JustificationMethod	GetJustificationMethod() const = 0;
		/**
		Set justification method. Only used by world ready composer.
		@param justMethod
		*/
		virtual void	SetJustificationMethod(JustificationMethod justMethod) = 0;

		/**
		What is the desired width of a word space?
		*/
		virtual PMReal GetAlteredWordspace() const = 0;

		/**
		What is the desired letterspacing?  This is desired letterspacing + tracking.
		*/
		virtual PMReal GetAlteredLetterspace(bool16 isVertical) const = 0;

		/** Set the recommended minimum wordspace value.
		Value is expressed as fraction of the original space width. I.e. min = 0.80
		means allow the spaces to be up to 20% narrower.
		*/
		virtual void SetMinWordspace(PMReal min) = 0;

		/** Set the recommended maximum wordspace value.
		Value is expressed as fraction of the original space width. I.e. max = 1.33
		means allow the spaces to be up to 33% wider
		*/
		virtual void SetMaxWordspace(PMReal max) = 0;

		/** Set the desired wordspace value.
		Value is expressed as fraction of the original space width. I.e. desired = 1.0
		means the spaces should be unchanged.
		*/
		virtual void SetDesiredWordspace(PMReal desired) = 0;

		/** Set the recommended minimum letterspace value.
		Specified as a fraction of a space's width. I.e. min = -0.02 means
		allow 2% of the width of the space to be removed from every character's width.
		*/
		virtual void SetMinLetterspace(PMReal min) = 0;

		/** Set the recommended maximum letterspace value.
		Specified as a fraction of a space's width. I.e. max = 0.05 means
		allow 5% of the width of the space to be added to every character's width.
		*/
		virtual void SetMaxLetterspace(PMReal max) = 0;

		/** Set the desired letterspace value.
		Specified as a fraction of a space's width. I.e. min = -0.01 means
		add 1% of the width of the space to every character's width.
		*/
		virtual void SetDesiredLetterspace(PMReal desired) = 0;

		/** Set the recommended minimum glyphscale value.
		Specified as a scale. Min = 0.95 means glyphs can be scaled to 95% of their original width.
		*/
		virtual void SetMinGlyphscale(PMReal min) = 0;

		/** Set the recommended maximum glyphscale value.
		Specified as a scale. Min = 1.05 means glyphs can be scaled up by 5%.
		*/
		virtual void SetMaxGlyphscale(PMReal max) = 0;

		/** Set the desired glyphscale value.
		Specified as a scale. desired = 1.0 means leave the glyphs unscaled.
		*/
		virtual void SetDesiredGlyphscale(PMReal desired) = 0;

		/** Get wordspacing values.
		How big should the spaces be?  Values are specified in fractions:
		Normal setting for "desired" would be 1.0
		*/
		virtual void GetWordspace(PMReal *min, PMReal *des, PMReal *max) const = 0;
		/** Get letterspacing.
		How much space should be added between letters? Values are fractions of a default space width.
		Normal setting for "desired" would be 0.0
		*/
		virtual void GetLetterspace(PMReal *min, PMReal *des, PMReal *max) const = 0;
		/** Get glyphscaling values.
		How much scaling should be applied to the text?  Values are percentages.
		Normal setting for "desired" would be 1.0
		*/
		virtual void GetGlyphscale(PMReal *min, PMReal *des, PMReal *max) const = 0;

		// unused at this time
		virtual bool16 GetAutoQuadding() const = 0;
		virtual void SetAutoQuadding(bool16 b) = 0;

		/** Should ligatures be applied to the text?
		@param below is a kerning measurement below which ligatures should be turned off.
		*/
		virtual void SetLigaturesBreakBelow(PMReal below) = 0;
		/** Should ligatures be applied to the text?
		@param above is a kerning measurement above which ligatures should be turned off.
		*/
		virtual void SetLigaturesBreakAbove(PMReal above) = 0;

		/** At what tightness should ligatures be disabled?
		*/
		virtual PMReal GetLigaturesBreakBelow() const = 0;
		/** At what looseness should ligatures be disabled?
		*/
		virtual PMReal GetLigaturesBreakAbove() const = 0;

		/** Should ligatures be applied to the text?
		Turn them off in text that is too tight or too loose.
		*/
		virtual bool16 LigaturesAllowed(bool16 isVertical) const = 0;

		/**
		Calculate a penalty for the width of the last line in a paragraph.
		@param width is the width of the last line.
		@param target is the desired width (frame width) of the last line.
		@return is a penalty associated with a very long or very short last line.
		*/
		virtual double GetLastLineLengthPenalty(double width, double target) const = 0;

		/**
		Calculate a penalty factor for adjacent lines to favor consistent tightnesses.
		@param prevLine is the tightness of the previous line.
		@param thieLine  is the tightness of the current line.
		@param capheight is the maximum cap height for the line, which scales the penalty.
		@return is a penalty associated with a inconsistent justification.
		*/
		virtual double GetLineConsistencyPenalty(IWaxLine::LineTightness prevLine,
												 IWaxLine::LineTightness thisLine,
												 double capheight) const = 0;

		/**
		Get width of kashida to be used in naskh justifications.
		@return PMReal is how many kashidas to use when justifying text. 1 means width of 1 kashida in font. 0 means no kashida is added when justifying.
		*/
		virtual	PMReal GetKashidaWidth() const = 0;
		/**
		Set width of kashida to be used in naskh justifications.
		@param width is how many kashidas to use when justifying text. 1 means width of 1 kashida in font. 0 means no kashida is added when justifying.
		*/
		virtual	void SetKashidaWidth(PMReal width) = 0;

};

#endif
	// __IJustificationStyle__

