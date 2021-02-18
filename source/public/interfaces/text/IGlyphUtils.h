//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IGlyphUtils.h $
//  
//  Owner: Pascal Rubini
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __IGlyphUtils__
#define __IGlyphUtils__

#include "IPMUnknown.h"
#include "IPMStream.h"
#include "Utils.h"

#include "K2Vector.h"
#include "CTextEnum.h"
#include "TextID.h"
#include "ITextAttrGlyphForm.h"
#include "UnicodeClass.h"

class IPMFont;
class ISelectionManager;
class IFontInstance;
class GlyphAccessData;
class WideString;
class AttributeBossList;

/**
	GlyphEntry
	
	@see GlyphSet
*/
class GlyphEntry
{
public:
	// constructor
	typedef base_type data_type;
	GlyphEntry(Text::GlyphID id = 0) : 
		fGlyphID(id),
		fCachedUnicodeGlyphID(kMaxUInt32)
		{}

	/**	Get the glyph id
		@return Text::GlyphID	glyph id
	 */
	Text::GlyphID		 	GetGlyphID() const { return fGlyphID; }

	/**	Set the glyph id
		@param glyphID	glyph id
	 */
	void					SetGlyphID(const Text::GlyphID glyphID) { fGlyphID = glyphID; }

	/**	Gets a unicode character value for a glyph id. Caches its value.
        @param font			font glyphid is from
        @return				unicode character value. May return 0.
		@see GetUnicodeForGlyphID in IGlyphUtils.h
	*/
	UTF32TextChar		 	GetUnicodeGlyphID(IPMFont *font) const;

	/**	Sets glyphAccessData->fDesiredTag to global gDesiredTag. Calls IPMFont::GetOTGlyphAccess. External code
		should not use this and call IPMFont::GetOTGlyphAccess instead.
		@param font				font glyph id is in
		@param glyphAccessData	access data
		@return bool16			kTrue if success and glyphAccessData has a feature and access textchars has a length.
	 */
	bool16					GetOTFFeatureUnicodeCombo(IPMFont * font, GlyphAccessData & glyphAccessData) const;
	
protected:
	Text::GlyphID		fGlyphID;

protected:
	UTF32TextChar		fCachedUnicodeGlyphID;
};


/** Compare function for sorting a GlyphSet into Unicode sort order.
 */
class GlyphEntryUnicodeCompare
{
public:
	GlyphEntryUnicodeCompare(IPMFont* font) { fFont = font; }

	IPMFont* fFont;

	bool operator()(const GlyphEntry& glyph1, const GlyphEntry& glyph2)
	{
		UTF32TextChar g1 = glyph1.GetUnicodeGlyphID(fFont);
		UTF32TextChar g2 = glyph2.GetUnicodeGlyphID(fFont);

		// One or both of glyphs doesn't have a unicode value. Put these glyphs at end.
		if (g1 == 0 || g2 == 0)
		{
			if (g1 == 0 && g2 == 0)
				return (glyph1.GetGlyphID() < glyph2.GetGlyphID());	// Two glyphs w/o unicode values, compare by glyph id
			else if (g1 == 0)
				return kFalse;	// glyph1 has no unicode value but glyph2 does, consider glyph1 greater than glyph2
			else
				return kTrue;	// glyph2 has no unicode value but glyph1 does, consider glyph1 less than glyph2
		}
		else if (g1 == g2)
		{
			return (glyph1.GetGlyphID() < glyph2.GetGlyphID());	// Two glyphs w/o unicode values, compare by glyph id
		}

		// Comparing actual unicode values here
		return (g1 < g2);
	}
};

/** Compare function for sorting a GlyphSet into CID sort order.
 */
class GlypyEntryCIDCompare
{
public:
	GlypyEntryCIDCompare(IPMFont* font) { fFont = font; }

	IPMFont* fFont;

	bool operator()(const GlyphEntry& glyph1, const GlyphEntry& glyph2)
	{
		return (glyph1.GetGlyphID() < glyph2.GetGlyphID());	// Compare by glyph id
	}
};

/**
	GlyphSet. Vector of GlyphEntries
	
	@see IGlyphUtils
*/
class GlyphSet: public K2Vector<GlyphEntry>
{
public:
	/**	Number of glyphs in set
		@return int32	number of glyphs in set
	 */
	int32				NumOfGlyphs() const
							{ return size(); }

	/**	Add entry to set. Added at end.
		@param checkUnique	if kTrue only add if glyph is not already in set 
		@param altID		glyph to add
	 */
	void				AddGlyphEntry(bool checkUnique, Text::GlyphID altID)
							{
								if (checkUnique && GetGlyphIndex(altID) != -1)
									return;
								push_back(GlyphEntry(altID));
							}

	/** Sort orders for viewing glyph sets in the main area of the Glyph panel */
	enum GlyphSortOrder { 
		/** By glyph Unicode value */
		kUnicodeOrder, 
		/** By glyph CID value (font definition order) */
		kCIDOrder,
		/** Not sorted */
		kNoOrder };

	/**	Sort the glyph set into Unicode or CID order.
	 */
	void				Sort(IPMFont *font, GlyphSortOrder order)
							{
								if (order == kCIDOrder)
									std::sort(begin(), end(), GlypyEntryCIDCompare(font));
								else if (order == kUnicodeOrder)
									std::sort(begin(), end(), GlyphEntryUnicodeCompare(font));
							}

	/**	Get glyph id at index.
		@param index 
		@return Text::GlyphID 
	 */
	Text::GlyphID		GetGlyphID(int32 index) const
							{ return (*this)[index].GetGlyphID(); }

	/**	Calls GlyphEntry::GetUnicodeGlyphID
		@param index		index to get unicode from
        @param font			font glyphid is from
        @return				unicode character value. 0 if in PUA area and userArea is not nil.
	 */
	UTF32TextChar		GetUnicodeGlyphID(int32 index, IPMFont *font) const
							{ return (*this)[index].GetUnicodeGlyphID(font); }

	/**	Getglyph id index
		@param id		glyph id to find index for
		@return int32	index
	 */
	int32				GetGlyphIndex(Text::GlyphID id) const
							{
								for (int i = 0; i< NumOfGlyphs(); i++)
									if (GetGlyphID(i) == id)
										return i;
								return -1;
							}

	/**	Read write the vector
		@param s	stream to read write
	 */
	void				ReadWrite(IPMStream *s)
							{
								int32    glyphID(kInvalidGlyphID);
								int32    j(0);
								int32    numOfGlyphs(0);

								if (s->IsReading())
								{
									s->XferInt32(numOfGlyphs);
									clear();
									for (j = 0; j < numOfGlyphs; j++)
									{
										s->XferInt32(glyphID);
										AddGlyphEntry(kFalse /*checkUnique*/, Text::GlyphID(glyphID));
									}
								}
								else
								{
									numOfGlyphs = NumOfGlyphs();
									s->XferInt32(numOfGlyphs);
									for (j = 0; j < numOfGlyphs; j++)
									{
										glyphID = GetGlyphID(j);
										s->XferInt32(glyphID);
									}
								}
							}

};

/** Pointer to a character categorization function. e.g. &UnicodeClass::IsAnyNumber()
 */
typedef bool (* GlyphFilterProc) (const UTF32TextChar& c);    

/** Collection of function pointers (typically a UnicodeClass categorization function). e.g. UnicodeClassProcList filterArray; filterArray.push_back(&UnicodeClass::IsPunctuationOpen()); filterArray.push_back(&UnicodeClass::IsPunctuationClose());
	Allows glyph sets to be assembled that meet several filter criteria.
	@see http://www.unicode.org/charts/ for unicode character code classifications
	@see IGlyphUtils.h, GetFilteredGlyphs
 */
typedef K2Vector<GlyphFilterProc> GlyphFilterProcList;


/** Utilities for dealing with glyphs.
	@ingroup text_font
*/
class IGlyphUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGLYPHUTILS };

    /** Gets a unicode character value for a glyph id
        @param *font        font glyphid is from
        @param id			glyph id to get character value
        @param *userArea	OUT if not nil and character value is in private use area 0 is returned and userArea
							contains the private use area unicode value.
        @return				unicode character value. 0 if in PUA area and userArea is not nil.
	*/
	virtual UTF32TextChar GlyphToCharacter(IPMFont *font,Text::GlyphID id,UTF32TextChar* userArea = nil) = 0;

    /** Gets a unicode character value for a glyph id. Uses GlyphToCharacter to get its work done.
		Will also get a unicode value for glyphs in OpenType features. Return first character for glyphs composed of multiple characters.
        @param *font        font glyphid is from
		@param glyphID		glyph id to get character value
		@return				unicode character value. Will return characters in private use area. May return 0. 
	 */
	virtual UTF32TextChar GetUnicodeForGlyphID(IPMFont *font, const Text::GlyphID& glyphID) const = 0;

	/**	Return a string for the name of the unicode character. 
		@param c			the UTF32TextChar character to look up the name for
		@return				the Unicode name of the character. Maybe be missing for some characters, will return empty string in this case.
	 */
	virtual PMString	GetUnicodeName(const UTF32TextChar& c) = 0;
		
    /** Inserts a glyph into textmodel
        @param *setMgr      selection manager
        @param *font        font of glyph.
        @param *baseGlyphEntry	entry of base glyph
        @param *alternateGlyphEntry	entry of alternate glyph
        @param selectChar	select glyph inserted
        @param setFont		set font of glyph to font passed in. font is restored to previous font after insertion
        @return				unicode character value. 0 if in PUA area and userArea is not nil.
	*/
	virtual void	InsertTheCharacter(ISelectionManager *selMgr, IPMFont *font, const GlyphEntry * baseGlyphEntry,
		const GlyphEntry * alternateGlyphEntry, bool16 selectChar = kFalse, bool16 setFont = kFalse) = 0;

	/**	Gets alternate glyph values for a given glyph.
		@param font			font to get glyph alternates in
		@param fontInstance	font instance to get glyph alternates in. needs to be an instance of font
		@param chars		unicode value(s) for glyph. multiple values only if glyph is a combination of unicode
							values like a ligature.
		@param glyph		glyph to get alternates for
		@param glyphSet		OUT set of glyph alternates.
		@param sortOrder how the returned glyph set should be sorted
		@return int32		returns length of glyphset.
	 */
	virtual int32	GetSelectionGlyphSet(IPMFont *font, IFontInstance* fontInstance, const WideString& chars,
		Text::GlyphID glyph, GlyphSet *glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Get alternates for glyphs
		@param font			font to get glyph alternates in
		@param fontInstance	font instance to get glyph alternates in. needs to be an instance of font
		@param glyphs		glyphs to find alternates for
		@param numGlyphs	number of glyphs. must be < 20 (kMaxStrikes). 
		@param glyphSet		OUT set of glyph alternates.
		@param sortOrder how the returned glyph set should be sorted
		@return int32		returns length of glyphset. returns 0 if numGlyphs was >=20.
	 */
	virtual int32	GetGlyphListGlyphSet(IPMFont *font, IFontInstance* fontInstance, Text::GlyphID* glyphs,
		int32 numGlyphs, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Determine if glyph has alternate with a given OpenType feature tag.
		@param font		font to look for alternate glyph in
		@param glyph	glyph to look for alternate
		@param tag		OpenType feature tag to look for. 'aalt' if set to nil.
		@return bool16	kTrue if there is an alternate with OpenType feature tag.
	 */
	virtual bool16	GetGlyphHasAlternate(IPMFont *font, Text::GlyphID glyph, const char * tag = nil) = 0;

	/**	Determine how many alternate with a given OpenType feature tag the glyph has.
		@param font		font to look for alternate glyph in
		@param glyph	glyph to look for alternate
		@param tag		OpenType feature tag to look for. 'aalt' if set to nil.
		@return uint16	the number of alternates with the OpenType feature tag.
	 */
	virtual unsigned	GetGlyphAlternateCount (IPMFont *font, Text::GlyphID glyph, const char * tag = nil) = 0;

	/**	Get all glyphs in font
		@param font		font to get glyphs in
		@param glyphSet	OUT all glyphs in font
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
	 */
	virtual int32	GetEntireFont(IPMFont *font, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Get all glyphs in a font that satisfy the given filter function (typically from UnicodeClass). 
		@param font		font to get glyphs for
		@param glyphSet	OUT filtered glyphs in font meeting the filter function(s) condition(s).
		@param includeFilterProcList	a list of function pointers to use to filter "in" the glyphs in the font, typically from UnicodeClass.h. GlyphFilterProcList filterArray; filterArray.push_back(&UnicodeClass::IsPunctuationOpen()); filterArray.push_back(&UnicodeClass::IsPunctuationClose());
		@param excludeFilterProcList	a list of function pointers to use to further filter "out" the glyphs in the font captured by the includeFilterProcList, typically from UnicodeClass.h.
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
		@see UnicodeClass.h for type definitions for filter procs.
	 */
	virtual int32	GetFilteredGlyphs(IPMFont *font, GlyphSet * glyphSet, GlyphFilterProcList& includeFilterProcList, GlyphFilterProcList& excludeFilterProcList, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder ) = 0;

	/**	Get glyphs for a OpenType feature. Also sets global gDesiredTag that is used by GetGlyphAccessInfo for what
		OpenType feature to prefer.
		@param tags		OpenType features to get glyphs for
		@param numTags	number of OpenType features
		@param font		font to get glyphs in
		@param glyphSet	OUT glyphs with OpenType features
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
	 */
	virtual int32	GetOTFFeatureGlyphSet(const char * tags, int32 numTags, IPMFont * font, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;


	/**	Try and find an open type feature for the font/glyph combo. Return if a suitable one was found.
		Probably INTERNAL use only.
		@param font		font glyph id is in
		@param fontInstance font instance to get OTF feature for. needs to be an instance of font
		@param baseGlyph entry of base glyph
		@param alternate entry of alternate glyph
		@param tags OpenType features to get glyphs for
		@param choice OUT return index value of OTF feature chosen from tags array.
		@return bool16 whether the particular feature was found
	 */
	virtual bool16 GetOTFFeature(IPMFont * font, IFontInstance * fontInstance, const GlyphEntry * baseGlyph, const GlyphEntry * alternate, char * tagBuffer/* 4 bytes */, int32 & choice) = 0;

	/**	Get glyphs for a OpenType feature
		@param tags		OpenType features to get glyphs for
		@param numTags	number of OpenType features
		@param font		font to get glyphs in
		@param glyphSet	OUT glyphs with OpenType features
		@return int32	1 if has alternates. 0 if no alternates.
	 */
	virtual int32		GetGlyphsForFeatureAccessInfo(const char * tags, int32 numTags, IPMFont * font,
		GlyphSet * glyphSet) = 0;

	/**	Sets glyphAccessData->fDesiredTag to global gDesiredTag. Calls IPMFont::GetOTGlyphAccess. External code
		should not use this and call IPMFont::GetOTGlyphAccess instead.
		@param glyphID			glyph id to get access for
		@param font				font glyph id is in
		@param glyphAccessData	access data
		@return int32			0 if success. 1 if failure.
	 */
	virtual int32		GetGlyphAccessInfo(Text::GlyphID glyphID, IPMFont * font,
		GlyphAccessData * glyphAccessData) = 0;


	/**	Description
		Probably INTERNAL use only.
		@param fontInstance font instance to test out application of OTF features. needs to be an instance of font
		@param textString a string of length 1 to apply OTF the feature to
		@param tags		OpenType features array
		@param choices array of choice for features. count is the same as numFeatures.
		@param numFeatures number of features in features variable
		@param testGlyphID 
		@return  kTrue if feature can be applied, kFalse if not
		@see IFontInstance.h, ApplyFeatures
	 */
	virtual bool16	TestFeatureSubstitution(IFontInstance * fontInstance, const WideString& textString, char * tags, int32 * choices, int32 numFeatures, Text::GlyphID testGlyphID) = 0;

	/**	Get an attribute for an open type feature. Return if a suitable one was found.
		@param tags		OpenType feature to get attribute for
		@param choice	value of OTF feature chosen from tags array
		@param attrBossList OUT attribute for the open type feature
		@param featureList OUT 
		@param form OUT 
		@param fontInstance font instance to get attribute for.
		@param stringToApply string to get OTF attribute for
		@param g glyphID to get OTF attribute for
	 */
	virtual void	GetOTFAttribute(char * tags, int32 choice, AttributeBossList * attrBossList, OpenTypeFeatureList& featureList, int32& form,
									  IFontInstance *fontInstance, const WideString& stringToApply, Text::GlyphID g) = 0;

	
	/**	GlyphFormIsKnown
		@param	feature IN, the feature whose value you want to confirm is a legal value.
		@return	true if the glyph form is known (< ITextAttrGlyphForm::kBeyondEndForm)
	*/
		virtual
		bool
	GlyphFormIsKnown (ITextAttrGlyphForm::GlyphForm feature) const
		= 0;

	/**	IsGlyphFormFeature
		@param	feature IN, the 4-character OpenType feature tag, stuffed into a 32-bit integer.
				The integer is the platform result of treating the char pointer as an int32 pointer.
		@return	whether the supplied feature is one covered by this class (i.e., it's in GlyphForm.)
	*/
		virtual
		bool
	IsGlyphFormFeature (int32 feature) const
		= 0;
	
	/**	IsGlyphFormFeature
		@param	feature IN, the 4-character OpenType feature tag.
		@return	whether the supplied feature is one covered by this class (i.e., it's in GlyphForm.)
	*/
		virtual
		bool
	IsGlyphFormFeature (const char *feature) const
		= 0;

	/**	GlyphFormFromFeature
		@param	feature IN, the 4-character OpenType feature tag, stuffed into a 32-bit integer.
				The integer is the platform result of treating the char pointer as an int32 pointer.
		@return	The GlyphForm corresponding to the feature, or kNoForm if !FeatureInPurview (feature)
	*/
		virtual
		ITextAttrGlyphForm::GlyphForm
	GlyphFormFromFeature (int32 feature) const
		= 0;

	/**	GlyphFormFromFeature
		@param	feature IN, the 4-character OpenType feature tag.
		@return	The GlyphForm corresponding to the feature, or kNoForm if !FeatureInPurview (feature)
	*/
		virtual
		ITextAttrGlyphForm::GlyphForm
	GlyphFormFromFeature (const char *feature) const
		= 0;

	/**	GlyphFormToFeatureInt
		@param	feature IN, the GlyphForm whose OpenType tag you want.
		@return	The OpenType feature tag corresponding to 'feature', with the characters stuffed into an int.
				The integer is the platform result of treating the char pointer as an int32 pointer.
	*/
		virtual
		int32
	GlyphFormToFeatureInt (ITextAttrGlyphForm::GlyphForm feature) const
		= 0;

	/**	GlyphFormToFeatureChars
		@param	feature IN, the GlyphForm whose OpenType tag you want.
		@return	The OpenType feature tag corresponding to 'feature', represented as characters.
	*/
		virtual
		const char *
	GlyphFormToFeatureChars (ITextAttrGlyphForm::GlyphForm feature) const
		= 0;
			
	/**	GlyphFormDescriptiveString
		@param	feature IN, the GlyphForm whose description string you want.
		@return	The descriptive string.
	*/
		virtual
		const char *
	GlyphFormDescriptiveString (ITextAttrGlyphForm::GlyphForm feature) const
		= 0;

		virtual
		ITextAttrGlyphForm::GlyphForm
	GlyphFormIncrement (ITextAttrGlyphForm::GlyphForm &) const
		= 0;

		virtual
		ITextAttrGlyphForm::GlyphForm
	GlyphFormDecrement (ITextAttrGlyphForm::GlyphForm &) const
		= 0;
};

#if IS_BIG_ENDIAN_ARCH
#define k_DLIG_CONSTANT		0x646C6967	
#define k_HLIG_CONSTANT		0x686C6967
#define k_CASE_CONSTANT		0x63617365
#define k_C2SC_CONSTANT		0x63327363
#define k_SMCP_CONSTANT		0x736d6370
#define k_ONUM_CONSTANT		0x6f6e756d
#define k_PNUM_CONSTANT		0x706e756d
#define k_TNUM_CONSTANT		0x746e756d
#define k_LNUM_CONSTANT		0x6c6e756d
#define k_SUPS_CONSTANT		0x73757073
#define k_SINF_CONSTANT		0x73696e66
#define k_SUBS_CONSTANT		0x73756273
#define k_NUMR_CONSTANT		0x6e756d72
#define k_DNOM_CONSTANT		0x646e6f6d
#define k_SWSH_CONSTANT		0x73777368
#define k_CSWH_CONSTANT		0x63737768
#define k_TALT_CONSTANT		0x74616c74
#define k_CLIG_CONSTANT		0x636c6967
#define k_CALT_CONSTANT		0x63616c74
#define k_ORDN_CONSTANT		0x6f72646e
#define k_FRAC_CONSTANT		0x66726163
#define k_LIGA_CONSTANT		0x6c696761
#define k_HKNA_CONSTANT		0x686B6E61
#define k_VKNA_CONSTANT		0x766B6E61
#define k_ITAL_CONSTANT		0x6974616c

#define k_TRAD_CONSTANT		0x74726164
#define k_EXPT_CONSTANT		0x65787074
#define k_JP78_CONSTANT		0x6a703738
#define k_JP83_CONSTANT		0x6a703833
#define k_HWID_CONSTANT		0x68776964
#define k_TWID_CONSTANT		0x74776964
#define k_QWID_CONSTANT		0x71776964
#define k_PWID_CONSTANT		0x70776964
#define k_FWID_CONSTANT		0x66776964
#define	k_NLCK_CONSTANT		0x6E6C636B
#define k_JP04_CONSTANT		0x6a703034
#define k_JP90_CONSTANT		0x6a703930

#define k_INIT_CONSTANT		0x696e6974
#define k_MEDI_CONSTANT		0x6d656469
#define k_FINA_CONSTANT		0x66696e61
#define k_ISOL_CONSTANT		0x69736f6c

#else

#define k_DLIG_CONSTANT		0x67696C64	
#define k_HLIG_CONSTANT		0x67696C68	
#define k_CASE_CONSTANT		0x65736163	
#define k_C2SC_CONSTANT		0x63733263	
#define k_SMCP_CONSTANT		0x70636d73	
#define k_ONUM_CONSTANT		0x6d756e6f	
#define k_PNUM_CONSTANT		0x6d756e70	
#define k_TNUM_CONSTANT		0x6d756e74	
#define k_LNUM_CONSTANT		0x6d756e6c	
#define k_SUPS_CONSTANT		0x73707573	
#define k_SINF_CONSTANT		0x666e6973	
#define k_SUBS_CONSTANT		0x73627573	
#define k_NUMR_CONSTANT		0x726d756e	
#define k_DNOM_CONSTANT		0x6d6f6e64	
#define k_SWSH_CONSTANT		0x68737773	
#define k_CSWH_CONSTANT		0x68777363	
#define k_TALT_CONSTANT		0x746c6174	
#define k_CLIG_CONSTANT		0x67696c63	
#define k_CALT_CONSTANT		0x746c6163	
#define k_ORDN_CONSTANT		0x6e64726f	
#define k_FRAC_CONSTANT		0x63617266	
#define k_LIGA_CONSTANT		0x6167696c	
#define k_HKNA_CONSTANT		0x616e6b68	
#define k_VKNA_CONSTANT		0x616e6b76	
#define k_ITAL_CONSTANT		0x6c617469	

#define k_TRAD_CONSTANT		0x64617274
#define k_EXPT_CONSTANT		0x74707865
#define k_JP78_CONSTANT		0x3837706a
#define k_JP83_CONSTANT		0x3338706a
#define k_HWID_CONSTANT		0x64697768
#define k_TWID_CONSTANT		0x64697774
#define k_QWID_CONSTANT		0x64697771
#define k_PWID_CONSTANT		0x64697770
#define k_FWID_CONSTANT		0x64697766
#define	k_NLCK_CONSTANT		0x6B636C6E	
#define k_JP04_CONSTANT		0x3430706a
#define k_JP90_CONSTANT		0x3039706a

#define k_INIT_CONSTANT		0x74696e69
#define k_MEDI_CONSTANT		0x6964656d
#define k_FINA_CONSTANT		0x616e6966
#define k_ISOL_CONSTANT		0x6c6f7369

#endif

#endif
		// __IGlyphUtils__
		
