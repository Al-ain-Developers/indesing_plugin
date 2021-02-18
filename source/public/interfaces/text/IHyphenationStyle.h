//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphenationStyle.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __IHyphenationStyle__
#define __IHyphenationStyle__


#include "IPMUnknown.h"
#include "TextID.h"

class ILanguage;


/**
	IHyphenationStyle is the primary interface of hyphenation related text attribute summary data.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text.
	IHyphenationStyle should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves set the values in this data interface.
	@see IComposeScanner
	@see kComposeStyleBoss
	@see ICompositionStyle
	@see IDrawingStyle
	@see IJustificationStyle
	@ingroup text_comp_style
	@ingroup text_hyphen
*/
class IHyphenationStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IHYPHENATIONSTYLE };

			/**	note: off means only hard hyphens
				manual means also use discretionary hyphens
				dictionary means ALSO use dictionary hyphens
				algorithm means ALSO use algorithm.
				These are additive methods, not exclusive.
				We only support "manual" vs. "algorithm" in the current user interface.
			*/
		typedef enum { kHyphensOff = 0, kHyphensManual, kHyphensDictionary,
					   kHyphensAlgorithm } HyphenationMethod;

		/** Provider Hyphenation Style. Currently only used by the Duden hyphenation provider. */
		enum ProviderHyphenationStyle {
			kHyph_All = 0,
			kHyph_AllButUnaesthetic,
			kHyph_Aesthetic,
			kHyph_PreferredAesthetic
		};

		/** Get the minimum number of characters that must appear before a hyphen.
			@return the minimum number of characters.
		*/
		virtual int16 MinCharsBefore() const = 0;

		/** Get the minimum number of characters that must appear after a hyphen.
			@return the minimum number of characters.
		*/
		virtual int16 MinCharsAfter() const = 0;

		/** Get the shortest word that can hyphenate. Will not be less than MinCharsBefore + MinCharsAfter.
			@return the length of the shortest word.
		*/
		virtual int16 ShortestWord() const = 0;

		/** Set the minimum number of characters that must exist before a hyphen.
			@param i is the minimum number of characters.
		*/
		virtual void SetMinCharsBefore(int16 i) = 0;

		/** Set the minimum number of characters that must exist after a hyphen.
			@param i is the minimum number of characters.
		*/
		virtual void SetMinCharsAfter(int16 i) = 0;

		/** Set the shortest word that can hyphenate.
			@param i is the length of the shortest word.
		*/
		virtual void SetShortestWord(int16 i) = 0;

		/** Get the hyphenation zone. Not used by the paragraph composer. Controls hyphenation in the
			single line composer in ragged text.
			@return the amount the line must be short before considering hyphenating the long word.
		*/
		virtual PMReal HyphenationZone() const = 0;

		/** Set the hyphenation zone. Not used by the paragraph composer. Controls hyphenation in the
			single line composer in ragged text.
			@param zone is the amount the line must be short before considering hyphenating a word.
		*/
		virtual void SetHyphenationZone(PMReal zone) = 0;

		/** Set the maximum number of consecutive hyphenated lines.
			@param ladderCount is the maximum number of hyphenated lines.
		*/
		virtual void SetLadderLimit(int16 ladderCount) = 0;

		/** Get the maximum number of consecutive hyphenated lines.
			@return the maximum number of hyphenated lines.
		*/
		virtual int16 GetLadderLimit() const = 0;

		/** Get the hyphenation mode.
				Note: off means only hard hyphens
				manual means also use discretionary hyphens
				dictionary means ALSO use dictionary hyphens
				algorithm means ALSO use algorithm.
				These are additive methods, not exclusive.
			We only support "manual" vs. "algorithm" in the current user interface.
			@return the hyphenation mode.
		*/
		virtual HyphenationMethod GetHyphenationMethod() const = 0;

		/** Set the hyphenation mode.
			We only support "manual" vs. "algorithm" in the current user interface.
			@see GetHyphenationMethod.
			@param method is the desired hyphenation mode.
		*/
		virtual void SetHyphenationMethod(HyphenationMethod method) = 0;

		/** Should capitalized words be hyphenated? Can be used to globally avoid splitting proper names for example.
			Doesn't consider "all cap" words capitalized.
			@return kTrue if capitalized words should be hyphenated.
		*/
		virtual bool16 HyphenateCapitalized() const = 0;

		/** Should capitalized words be hyphenated?
			Doesn't consider "all cap" words capitalized.
			@param b is if capitalized words should be hyphenated.
		*/
		virtual void SetHyphenateCapitalized(bool16 b) = 0;

		/** Get the global hyphenation penalty factor -- higher values mean fewer hyphens.
			Used by the paragraph composer.
			@return the hyphenation penalty factor..
		*/
		virtual double GetHyphenationPenaltyFactor() const = 0;

		/** Set the global hyphenation penalty factor -- higher values mean fewer hyphens.
			Used by the paragraph composer.
			@param p is the hyphenation penalty factor..
		*/
		virtual void SetHyphenationPenaltyFactor(double p) = 0;

		/** Get the penalty for hyphenating the last full line in a paragraph.
			@return the penalty value.
		*/
		virtual double GetLastLineHyphenPenalty() const = 0;

		/** Set the penalty for hyphenating the last full line in a paragraph.
			@param d is the penalty value.
		*/
		virtual void SetLastLineHyphenPenalty(double d) = 0;

		/** Should the last word in the paragraph be considered for hyphenation?
			@return kTrue if the last word should never be hyphenated..
		*/
		virtual bool16 PreventLastWordHyphen() const = 0;

		/** Should the last word in the paragraph be considered for hyphenation?
			@param b is kTrue if the last word should never be hyphenated..
		*/
		virtual void SetLastWordHyphenPrevention(bool16 b) = 0;

		/** What language is applied?.
			@return an AddRef'd ILanguage interface.
		*/
		virtual ILanguage *QueryLanguage() const = 0;

		/** Set the UID of the language boss applied.
			@param nLanguage is the UID of the language.
		*/
		virtual void SetLanguageUID(UID nLanguage) = 0;

		/** Get the UID of the language boss applied.
			@return the UID of the language.
		*/
		virtual UID GetLanguageUID() const = 0;

		/** Get the global hyphenation penalty factor for hyphenating across frames.
			Used by the paragraph composer.
			@return kTrue when preventing cross frame hyphens.
		*/
		virtual bool16 GetPreventCrossFrameHyphen() const = 0;

		/** Ask the compose to avoid hyphenating across frames.
			Used by the paragraph composer.
			@param p is kTrue when preventing cross frame hyphens.
		*/
		virtual void SetPreventCrossFrameHyphen(bool16 p) = 0;

		/*	Get the hyphenation style for the provider. The provider Duden has four styles that give different hyphenation points.
			@return the provider hyphenations style.
		*/
		virtual ProviderHyphenationStyle GetProviderHyphenationStyle() const = 0;

		/** Set the hyphenation style for the provider. The provider Duden has four styles that give different hyphenation points.
			@param @see IHyphenationStyle::ProviderHyphenationStyle
		*/
		virtual void SetProviderHyphenationStyle(IHyphenationStyle::ProviderHyphenationStyle providerHyphenationStyle) = 0;
};


#endif		// __IHyphenationStyle__

