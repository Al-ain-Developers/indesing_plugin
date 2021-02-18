//========================================================================================
//  
//  File: IWRScript.h
//  
//  Author: Niti Hantaweepant
//  
//  Copyright 2006 Adobe Inc. & WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. & WinSoft SA. 2006.
//  
//========================================================================================

#ifndef __IWRScript__
#define __IWRScript__

#include "WRClass.h"
#include "OptycaFeatureSet.h"
#include "OptycaTypes.h"
#include "OptycaFont.h"

class OptycaFontOT;
class OptycaImpl;

typedef WRInt32 (*FindComponentMarkHolderProc) (OptycaFontOT* optycaFont, OptycaImpl* ca, WRInt32 markIndex);

enum {
	kPercentIndex = 10,
	kDecimalPointIndex,
	kThousandSeparator
};

/* OT Font tags --------------------------------*/

extern WRInt32 gTAG_case;
extern WRInt32 gTAG_cpsp;
extern WRInt32 gTAG_smcp;
extern WRInt32 gTAG_c2sc;
extern WRInt32 gTAG_locl;
extern WRInt32 gTAG_subs;
extern WRInt32 gTAG_sups;


class IWRScript : public WRClass
{
public:
	virtual ~IWRScript() {}

	virtual const char* GetScriptName() const = 0;
	// returns the script name as a c string ptr ("roman"), debugging purposes.

	virtual const WRScriptID GetScriptID() const = 0;
	// returns the scriptID (kWRRomanScript).

	virtual WRError Init() = 0;
	// called once after construction, to initialize hard coded tables etc
	// returns an error code if anything went wrong ( missing resource?)

	virtual void Reset() = 0;
	// called once for each chunk of this script, usually to reset working arrays and variables

	virtual const char* GetOTScriptTag() const = 0;
	// returns the OpenType script tag as a c string (eg "latn" for roman)

	// returns true if the character doesn't require a script switch

	// returns true if the character is shared between multiple script (punctuation, kashida, danda
	virtual bool IsCharCompatible(WRUnichar32 ch) const = 0;

	// returns true if the character is shared between multiple script (punctuation, kashida, danda
	virtual bool IsWeak(WRUnichar32 ch) const = 0;

	// virtual const WRUnichar32* GetDefaultDigitSet(WRLanguageID langID) const = 0;
	// returns a pointer to const array of unicode, for each digit, percent, dec, thousand separator
	// null if no substitution required

	virtual const WRUnichar32* GetDigitSet(WRDigitSet digitSet) const = 0;
	// return the same kind of array as the previous call, but the digitset idf is explicitly passed

	virtual const int GetNextClusterNominalGlyphs(int codeStartPos, int glyphStartPos) = 0;
	// gets the nominal glyphs for the shaping cluster starting at pos, returns the cluster length

	virtual void ApplyCanonicalNormalizationFeatures() = 0;
	// take care of multiple representations of the same text (ccmp) and locale specific mandatory
	// transformations (locl)

	virtual void ApplyCursivity(int runStartPos, int runCount, WRLanguageID languageID) = 0;

	virtual void PrepareJustification(int runStartPos, int runCount) = 0;
	// prepare justification data if needed

	virtual OptycaImpl* GetShaper() = 0;

	// Script Features 
	/** 
	 * kHasFakedMarks was introduced specifically for Indic scripts, where
	 * we allow marks to have non-zero width. This is useful especially for some
	 * 'ill-design' fonts (Chandas and Uttara for instance) that define the short-i (0X93F)
	 * as a mark rather than a base.
	 **/
	typedef enum {
		kCanDisableLigature,
		kHasUppercase,
		kHasMarkVerticalPositioning,
		kHasZeroWidthMarks,
		kHasFakedMarks,
		kLastScriptFeature
	} ScriptFeature;	

	virtual bool HasFeature(ScriptFeature selector) const = 0;	

	// get diacritic positioning rule
	virtual OptycaFont::DiacPositionRule GetDiacPositionRule(WRUnichar32 baseUC, WRUnichar32 diacUC) const = 0;

	// substitute diacritic if needed
	virtual void SubstituteDiacritic(WRUnichar32 baseUC, WRUnichar32 diacUC, int runPos, int runEnd, OptycaFont* font, bool previousWasAbove, bool& above) const = 0;

	/// Set OT features for mark positioning
	/**
	 * Set OpenType features for mark positioning according to specific script
	 * @param featureInfo 
	 */
	virtual void SetMarkPositionOTFeature(WROTFeatureInfo& featureInfo) const = 0;

	/// Return callback function for component mark holder
	virtual FindComponentMarkHolderProc GetFindComponentMarkHolderProc() const = 0;

	// Possibility for the Script to prevent non open type diacritic policy (useful for Indic scripts)
	virtual DiacPosPolicy OverrideDiacPolicy(const DiacPosPolicy dp) const = 0;

	virtual bool IsCursive() const = 0;

	/// Does a specific unicode allow for letter spacing?
	/**
	This method is uses by the full justification to control where letterspacing is allowed 
	in the case of a script that is not truly cursive but where glytphs must touch (e.g. Devanagari)
	@param ch an WRUnichar32
	@return true if letterspacing is allowed after the letter
	**/
	virtual bool GetsLetterSpacing(WRUnichar32 /*ch*/) const { return true; }

};

#endif
