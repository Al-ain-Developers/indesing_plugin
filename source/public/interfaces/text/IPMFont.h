//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IPMFont.h $
//  
//  Owner: emenning
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
//  See the implementation CTPFont.cpp and refer to the CoolType documentation for more information
//  
//========================================================================================

#pragma once
#ifndef __IFont__
#define __IFont__

#include "GRRefCountedObj.h"
#include "CTextEnum.h"
#include "InterfacePtr.h"
#include "IFontMgr.h"
#include "IDFile.h"					// for GetFontFiles()
#include "K2Vector.h"
#include "OTFeature.h"
#include <string>					// for GetGlyphName()

class KinsokuCharType;
class PMString;
class PMRect;
class WideString;
typedef int16    MojikumiClass;
class PMRealGlyphPoint;

#define kDefaultScriptTag		"DFLT"
#define kDefaultLanguageTag	"dflt"

/**
	GlyphAccessData

	@see GetOTGlyphAccess
*/
class GlyphAccessData
{
public:
	typedef object_type data_type;

	GlyphAccessData() : fDesiredTag(0), fFoundNonAALT(kFalse), fFoundNonPUAUnicodeValue(kFalse) {}

	/** INPUT - A preferred unicode value for the glyph. Length == 0 if no preferred textchars. */
	WideString fDesiredTextChars;
	/** INPUT - A preferred opentype feature for the glyph. 0 if there is no preferred OpenType feature */
	int32 fDesiredTag;

	/** OUTPUT - unicode value that will access this glyph. */
	WideString fTextChars;
	/** OUTPUT - opentype features that will access this glyph. */
	OpenTypeFeatureList fFeatureList;
	/** OUTPUT - true if an access was found that does not use the 'AALT' feature. */
	bool16 fFoundNonAALT;
	/** OUTPUT - true if an access was found that does not use a Unicode value in the Private Use Area (PUA).
			PUA values are - kTextChar_PrivateZoneStart = 0xE000 to kTextChar_PrivateZoneEnd = 0x0F8FF
	*/
	bool16 fFoundNonPUAUnicodeValue;
};


/**  This is a shell over the CoolType API for fonts.
	The native CoolType api is in the form of ::GetFontValue(font, key, void*, length)
	This interface makes fonts much easier to deal with.
	@ingroup text_font
*/
class IPMFont : public grRefCountedObj
{
	protected:
		~IPMFont(){} // you should not call delete on an IPMFont*. You should call Release()!
	public:
    
    /*
     This enum should not be used any more as from indesign 2019 onwards as we will be supporting variable fonts, so we will ask the font, for its number of design axes and make a dynamic allocation accordingly.
     */
		enum { kMaxDesignVectorSize = 5 };


		/**	Get Cooltype dictionary

			@return CTFontDict*		CoolType dictionary for this IPMFont
		 */
		virtual CTFontDict* GetCTFontDict() const = 0;

		/**	Gets the postscript name of the font.

			@return std::string		PostScript name of the font
		 */
		virtual std::string GetPostScriptName() const = 0;

		// appends the name specified to the string passed in. Most useful
		// format for menus. Also minimizes copying, memory allocations, etc.

		/**	Full name includes information for family name and style name. Not
			always the same as FamilyName+' '+StyleName. Determined by the font.
			@param s	String to append name to.
		 */
	 	virtual void AppendFullName(PMString& s) const = 0;

		/**	Native full name includes information for family name and style name in the
			language of the script of the font.
			@param s	String to append name to.
		 */
	 	virtual void AppendFullNameNative(PMString& s) const = 0;

		/**	Family name
			@param s	String to append name to.
		 */
 	 	virtual void AppendFamilyName(PMString& s) const = 0;

		/**	Native family name in the language of the script of the font.
			@param s	String to append name to.
		 */
  	 	virtual void AppendFamilyNameNative(PMString& s) const = 0;

		/**	Style name
			@param s	String to append name to.
		 */
	 	virtual void AppendStyleName(PMString& s) const = 0;

		/**	Style name in the language of the script of the font.
			@param s	String to append name to.
		 */
	 	virtual void AppendStyleNameNative(PMString& s) const = 0;

		/**	Font name is postscript name of the font.
			@param s						String to append name to.
			@param originalNameWhenMissing	If kFalse will return the postscript name of available font
											that is replacing the missing font. If kTrue gives the
											postscript name of the missing font.
		 */
 	 	virtual void AppendFontName(PMString& s, bool16 originalNameWhenMissing = kFalse) const = 0;


			// multiple master font stuff
		/**
			Get number of multiple master axes. 0 for non multiple master fonts.

			@return	int32	number of multiple master axes
		*/
		virtual int32 GetNumDesignAxes() const  = 0;
		/**
			Get name of multiple master axis for index value. Only useful for multiple master fonts. Example of
			names are "OpticalSize", "Weight", and "Width"

			@param	index	index into multiple master axes. 0 based and must be less than GetNumDesignAxes
			@param	s		name of axis.
		*/
		virtual void AppendNthDesignAxisName(int32 index, PMString& s) const = 0;
		/**
			Get axis limit of multiple master font for index value. Only useful for multiple master fonts.

			@param	index	index into multiple master axes. 0 based and must be less than GetNumDesignAxes
			@param	min		minimum value
			@param	max		maximum value
		*/
		virtual void GetNthDesignAxisLimits(int32 index, Fixed *min, Fixed *max) const = 0;
		/**
			Access the design vector this IPMFont is using. This method is also used to set the value.

			@return	Fixed*	current design vector IPMFont is using
		*/
		virtual Fixed* AccessDesignVector() = 0;
		/**
			Access the design vector this IPMFont is using. This method does not allow you to set the value.

			@return	Fixed*	current design vector IPMFont is using
		*/
		virtual const Fixed* AccessDesignVector() const = 0;

		/**	Fills array with number of multiple master instances on the system for this font
			@param *array		array of axes information.
			@param *numberFit	IN number of fixed in array. OUT number actually needed. This is
								number of instances times the number of design axes. Pass nil
								array and 0 to find out size needed for array.
			@return int32		number of instances installed
		 */
		virtual int32 FillOutMMInstances(Fixed *array, int32 *numberFit) const = 0;
		/**
			Appends multiple master instance name.

			@param	which	index of instance. 0 based and must be less than number of instances.
			@param	s		name of instance. used in font style menu.
		*/
		virtual void AppendMMInstanceName(int32 which, PMString& s) const = 0;


			// miscellaneous stuff
		/**
			Get font bounding box. This is the bounding box of a 1 point font. It is
			the union of the bounding box of each character in the font where the character
			is drawn at the point <0,0>.

			@return	PMRect	font bounding box
		*/
		virtual PMRect GetFontBBox() const = 0;
		/**
			Get glyph id of not defined glyph for this font

			@return	Text::GlyphID	notdef glyph
		*/
		virtual Text::GlyphID GetNotDefinedGlyph() const = 0;

		/**	Returns number of glyphs in font. For ATC fonts this is really max glyph id. ATC fonts
			do not have continuous glyph ids.
			@return int32	number of glyphs in font
		 */
		virtual int32 GetNumGlyphs() const = 0;

		/**
			 This is true if and only if this fonts technology key is kType1Font and the default
			 type 1 encoding vector associated with this font is the PostScript "StandardEncoding" vector.

			@return	bool16	kTrue or kFalse
		*/
		virtual bool16 UsesStandardEncoding() const = 0;

		/**
			Get primary writing script of font. Usage of this should be phased out as fonts can now
			support multiple scripts and no one script may really be primary.

			@return	int32	script id
		*/
		virtual	int32 GetWritingScript() const = 0;

		/**
			Gets the version string of the font.

			@param	s		version string
			@return	bool16	kFalse when not found
		*/

		virtual bool16 AppendVersion(PMString& s) const = 0;

		/**
			Gets a vector of paths to the font file. Type 1 fonts have more than one file.

			@return	K2Vector<PMString>*		vector of paths to the font file. Caller is responsible for calling delete on the returned K2Vector*.
		*/
		virtual K2Vector<PMString>* GetFullPath() const = 0;

		/**
			Font Protection

			@see GetProtection
		*/
		enum FontProtection {
						/** */
						kInvalid = 0,
						/** */
						kNormal,
						/** If this is set, the outlines can be used for rasterization, but the control
							points are not allowed to be exposed to users.
						*/
						kNoOutlines,
						/** If this is set, then the hinted outlines cannot be downloaded to a printer;
							however, if kNoOutlines is not set, unhinted outlines can be downloaded.
						*/
						kNoPrinting,
						/** If a font allows "editable embedding," then that font may be embedded
							in a document format where the embedded font can be used to edit the document.
							In PDFs, fonts that are associated with forms or annotations may be used in this way.
							This flag is set when the font cannot be embedded in such a document.
						*/
						kNoEmbedding,
						/** If a font allows "print-and-preview embedding", then that font
							may be embedded in a document format where the embedded font will
							only be used for printing or for document viewing. That is, the embedded font
							will not be used for document editting. For example, most fonts that are embedded in
							PDF are only used for document viewing and printing. This flag is set when the font cannot
							be embedded in such a document.
						*/
						kNoPDFEmbedding,
						/** Obsolete. No longer used. */
						kRestrictedPrinting
				} ;

		/**
			Get font's protection values.

			@return	K2Vector<FontProtection>*	vector of font protection values. Caller is responsible for calling delete on the returned K2Vector*.
		*/
		virtual K2Vector<FontProtection>* GetProtection() const = 0;

		/**
			Font Status

			@see GetFontStatus
		*/
		typedef enum {
						/** */
						kFontInstalled		= 0x01,
						/** */
						kFontNotAvailable	= 0x10,
						/** */
						kFontFauxed = 0x11,
						/** */
						kFontSubstituted = 0x12,
						/** */
						kFontUnknown		= 0xFF
				} FontStatus;

		/**
			Font Technologies

			@see GetFontTechnology
		*/
		enum FontTechnology {
						/** a roman encoded, Adobe Type1 font */
						kType1Font,
						/** a TrueType font */
						kTrueTypeFont,
						/** a CID-Keyed font */
						kCIDFont,
						/** a platform dependent font */
						kBitmapFont,
						/** an Adobe Type Composer font (Rearranged CID font) */
						kATCFont,

						/** Technology is not known */
						kUnknownTechnology = -1
				};

		/**
			Font Types

			@see GetFontType
		*/
		typedef enum  {
						/** technology=kType1Font */
						kType1FontType,
						/** technology=kTrueTypeFont, DSIG table absent */
						kTrueTypeFontType,
						/** technology=kCIDFont, fontiscff =false */
						kCIDFontType,
						/** technology=kATCFont */
						kATCFontType,
						/** technology=kBitmapFont, hasoutlines=false */
						kBitmapFontType,
						/** technology=kCTBitmapFont, hasoutlines=true */
						kOCFFontType,
						/** technology=kCTType1Font, fontiscff=true */
						kOpenTypeCFFFontType,
						/** technology=kCTCIDFont, fontiscff =true */
						kOpenTypeCIDFontType,
						/** technology=kCTTrueTypeFont, DSIG table present */
						kOpenTypeTTFontType,

                        /** Type is not known */
						kUnknownFontType = -1
				} FontType;

		/**
			Get status of font. Use to find out if a font is available on a machine.

			@return	FontStatus	status of font
		*/
		virtual FontStatus GetFontStatus() const = 0;
		/**
			Get technology of font. See also GetFontType

			@return	FontTechnology
		*/
		virtual FontTechnology GetFontTechnology() const = 0;

		/**
			Get technology of font's glyph. Only different from GetFontTechnology for ATC fonts.

			@return	FontTechnology
		*/
		virtual IPMFont::FontTechnology GetGlyphTechnology(Text::GlyphID glyphID) const = 0;

		/**
			Get type of font.

			@return	FontType
		*/
		virtual FontType GetFontType() const = 0;

		/**	Gets font style bits
			@return IFontMgr::FontStyleBits		kSmallCaps or kAllCaps. Other styles not supported
		 */
		virtual IFontMgr::FontStyleBits	GetFontStyle() const = 0;

#ifdef WINDOWS

		/**	Gets logfont for this IPMFont.
			This edge routine is strongly discouraged. It does not return legitimate values
			for fonts installed inside the application\fonts folder.
			InDesign code has the UNICODE flag turned on so this returns a LOGFONTW.
			So logFont.lfFaceName is a WString.

			@param LOGFONT - pass in structure to be filled out.
			@return bool16 - returns false when not font is not installed.
		 */
		virtual bool16 GetWindowsLogFont(LOGFONT *logfont) const = 0;
#endif

		/**
			For a given pointsize get the font's ascent.

			@param	pointsize	point size it get ascent for
			@return	PMReal		ascent
		*/
		virtual PMReal GetAscent(PMReal pointsize) const = 0;
		/**
			For a given pointsize get the font's descent.

			@param	pointsize	point size it get descent for
			@return	PMReal		descent
		*/
		virtual PMReal GetDescent(PMReal pointsize) const = 0;
		/**
			Height of a capital 'X' if outline of X is available. Otherwise
			bbox height.

			@param	pointsize	point size it get cap height for
			@return	PMReal		cap height
		*/
		virtual PMReal GetCapHeight(PMReal pointsize) const = 0;
		/**
			Height of small 'x' if outline of x is available. Otherwise 2/3 of bbox
			height.

			@param	pointsize	point size it get x height for
			@return	PMReal
		*/
		virtual PMReal GetXHeight(PMReal pointsize) const = 0;

		/**
			Height of em-box

			@param	pointsize	point size it get em-box height for
			@param	vertical	if kTrue figure out for vertical text.
			@return	PMReal		height of em-box
		*/
		virtual PMReal GetEmBoxHeight(PMReal pointsize, bool16 vertical) const = 0;
		/**
			Calculate inset of Ideographic Character Face (ICF) box from embox

			@param	pointsize	point size it get insets for
			@param	fromLineTop	distance of ICF top from embox top
			@param	fromLineBottom	distance of ICF bottom from embox bottom
			@param	vertical		if kTrue figure out for vertical text.
		*/
		virtual	void GetICFBoxInsets(PMReal pointsize, PMReal * fromLineTop, PMReal * fromLineBottom, bool16 vertical) const = 0;

		/**
			Get font em-box. describes the left, top, right, and bottom edges (in horizontal
            writing mode) of the ideographic em-box of a 1-unit-em font. This value will
            be defined for every font (including non-CJK fonts, where it can be used to
            em-box-align these fonts alongside CJK fonts), barring any internal error.

			@return	PMRect	em-box of font
		*/
		virtual PMRect GetEmBox() const = 0;
		/**
			Get ICF box. describing the left, top, right, and bottom edges (in horizontal
			writing mode) of the Ideographic Character Face (ICF) box of a 1-unit-em font.
			This value will be defined for every font (including non-CJK fonts), barring
			any internal error.


			@return	PMRect	ICF box of font
		*/
		virtual PMRect GetICFBox() const = 0;

		typedef enum
		{
			/** */
			kBaselineDefault,
			/** */
			kBaselineRoman,
			/** */
			kBaselineEmBoxTop,
			/** */
			kBaselineEmBoxBottom,
			/** */
			kBaselineEmBoxCenter,
			/** */
			kBaselineICFBoxTop,
			/** */
			kBaselineICFBoxBottom,
			/** */
			kBaselineICFBoxCenter,
			/** */
			kNumBaselines,
			/** */
			kBaselineInvalid = 0x7fffFFFF
		} BaselineType;
		/**
			Translate baseline

			@param *strikes			If non-NULL, pointer to an array of PMRealGlyphPoint's with numStrikes valid entries. Only the
									strikes' pt.xPosition (in the case of TopToBottom writing) or pt.yPosition (in the
									case of LeftToRight writing) will be read and modified. They are assumed to be in
									device space.
			@param numStrikes		Number of entries in the strikes array, if the strikes parameter is non-NULL.
			@param *matrix			The matrix that the strikes were scaled by. Pass NULL for the identity matrix.
			@param fromBaseline		The baseline of the input strikes/points.
			@param toBaseline		The desired baseline.
			@param writingDirection
		 */
		virtual void TranslateBaseline(PMRealGlyphPoint *strikes, int32 numStrikes, PMMatrix *matrix, BaselineType fromBaseline, BaselineType toBaseline, IFontMgr::WritingDirection writingDirection) const = 0;
		/**
			Returns the distance from the Roman baseline to the em-box bottom for the
			horizontal writing mode. This is used to calculate roman baseline offset for
			both horizontal and vertical text, since InDesign draws vertical text and horizontal
			text the same (the pen location is at the roman baseline).

			@return	PMReal	horizontal em-box depth
		*/
		virtual PMReal GetHorizEmBoxDepth() const = 0;
		/**
			Returns the distance from the Roman baseline to the ICF box bottom for the
			horizontal writing mode. This is used to calculate roman baseline offset for
			both horizontal and vertical text, since InDesign draws vertical text and horizontal
			text the same (the pen location is at the roman baseline).

			@return	PMReal	horizontal ICF box depth
		*/
		virtual PMReal GetHorizICFBoxDepth() const = 0;
		/**
			Returns true for fonts which contain proportional vertical metrics.

			@return	bool16	kTrue if font contains proportional vertical metrics
		*/
		virtual bool16 VerticalMetricsProportionalByDefault() const = 0;
		/**
			Returns true for fonts which contain proportional horizontal metrics.
			Set to true for CJK fonts which have proportional horizontal widths for
			characters that are typically full-width. For example, glyphs encoded in
			Unicode's Hiragana and Katakana blocks are usually full-width; in some
			fonts they are proportional-width. This is true for fonts like windows
			MS P Mincho and MS P Gothic.
			Only the glyphs' actual widths are checked; the client may use HasOTFeature()
			to check whether proportional metric layout features such as 'palt' and 'vpal'
			are present.

			@return	bool16	kTrue if font contains proportional horizontal metrics
		*/
		virtual bool16 HorizontalMetricsProportionalByDefault() const = 0;

		/**
			Get position for underline

			@param	yOffset
			@param	thickness
			@param	xScale
			@param	yScale
			@param	vertical
			@param	isTcy
		*/
		virtual void GetUnderlinePosition(PMReal *yOffset, PMReal *thickness, PMReal xScale = 1.0, PMReal yScale = 1.0, bool16 vertical = kFalse, bool16 isTcy = kFalse) const = 0;

		/** AllowFakeLigatureSubstitutions
			@return whether this font accepts faking a ligature substitution (when available) for fi, fl, etc.
		*/
		virtual bool16 AllowFakeLigatureSubstitutions() const = 0;

		/**
			applies ligatures - non OpenType ligatures that are looked for are fi, fl, ff, ffi, ffl

			@param strikes		IN strikes to apply ligature to. OUT ligature applied strikes.
			@param *numStrikes	IN number of strikes in strikes array. OUT number of strikes after ligature applied.
			@param *changeAttr	filled out like in CTOTFeature
			@param tryOpenType	try appling opentype ligature feature "liga"
			@return int32		error same as CTOTFeature
		 */
		virtual int32 DoLigatures(PMRealGlyphPoint* strikes, int32 *numStrikes, char *changeAttr = nil, bool16 tryOpenType = kTrue) const = 0;

		/**
			Font has OpenType feature. See http://partners.adobe.com:80/asn/tech/type/opentype/feattags.jsp
			for listing of OpenType features.

			@param	feature		four char's reprosenting the feature tag.
			@return	bool16		kTrue if font has feature.
		*/
		virtual bool16 HasOTFeature(const char feature[4], const char script[4] = 0, const char language[4] = kDefaultLanguageTag) const = 0;

		/**
			CountOTFeatures. This is NOT an efficient call for ATC (composite) fonts.  The value isn't
			cached because of the various script & language tags, and combining the lists from multiple
			component fonts isn't cheap.

			@return	numFeatures		The number of OpenType features in font.
		*/
		virtual int32 CountOTFeatures(const char script[4] = 0, const char language[4] = kDefaultLanguageTag) const = 0;

		/**
			PeekOTFeatures

			@return		A buffer of the OpenType features in font, must be deleted after use.
		*/
		virtual const char* NewOTFeaturesList(const char script[4] = 0, const char language[4] = kDefaultLanguageTag) const = 0;

		/**
			Returns if this font is from an EPS.

			@return	bool16	kTrue if font is from an EPS
		*/
		virtual bool16 GetIsEPSFont() const = 0;

		/**
			Returns if this font is embedded

			@return	bool16	kTrue is font is embedded
		*/
		virtual bool16 GetIsEmbeddedFont() const = 0;

		/**
			This will be kFalse if outlines are not available for this font (ie, it is a
			pure bitmap font).  It will return kTrue if outlines are available.  Note that
			this value says nothing about the accessibility of outlines (ie, outline
			protected fonts will still return kTrue).
			@return	bool16	kTrue if outlines are available
		*/
		virtual bool16 GetHasOutlines() const = 0;

		/**
			If this font is a kCIDFont technology font, then this is the CID registry for
			this font. Example is of Registry ordering supplement value (also know as ROS)
			is "Adobe-Japan1-4" so the registry is "Adobe".

			@param	fontRegistryString	registry
			@return	bool16				kTrue if string is not empty
		*/
		virtual bool16 GetFontRegistry( PMString *fontRegistryString ) const = 0;
		/**
			If this font is a kCIDFont technology font, then this is the CID ordering for
			this font. Example is "Japan1"

			@param	fontOrderingString
			@return	bool16				kTrue if string is not empty
		*/
		virtual bool16 GetFontOrdering( PMString *fontOrderingString ) const = 0;
		/**
			If this font is a kCIDFont technology font, then this is the supplement number
			for this font. Example is 4

			@return	int32	supplement number
		*/
		virtual int32 GetFontCIDSupplementNumber() const = 0;


		/**	Checks to see if checkGlyphID is in the range of glyphs for this font.
			@param checkGlyphID	Glyph id to check
			@return bool16		kTrue if valid. kFalse if invalid.
		 */
		virtual bool16 IsValidGlyphID(Text::GlyphID checkGlyphID) const = 0;


		/**
			Provides the platform dependent name.
			On the Windows OS, this is the equivalent of the lfFaceName in a
			LOGFONT. On the Mac OS, this is the equivalent of the FOND name.

			@param platformOS	The operating system for which the name is needed.
								platformOS can be any of kOriginalMacOS, kOriginalWinOS, or
								kOriginalUnknownOS. If kOriginalUnknownOS is given, the
								first match for a given writing script is returned.

			@return PMString	platform name. If no name is found this will return an empty string.
		 */
		virtual PMString GetPlatformDependentName(IFontMgr::OriginalOS platformOS = IFontMgr::kOriginalUnknownOS) const = 0;


		/**
			For a whole string or characters get the glyphIDs.
			@param textString	IN Unicode values to get glyphids from
			@param glyphIDs		OUT glyphIDs
			@param vertical		IN get vertical glyphs if kTrue
		 */
		virtual void GetGlyphIDs(const WideString& textString, K2Vector<Text::GlyphID>& glyphIDs, bool16 vertical = kFalse) const = 0;

		/**
			For a buffer append the glyphIDs.
			@param textBuffer		IN Unicode values to get glyphids from
			@param glyphIDs		OUT glyphIDs are appended
			@param vertical		IN get vertical glyphs if kTrue
		 */
		virtual void AppendGlyphIDs(const UTF16TextChar* textBuffer, int32 numUTF16Chars, K2Vector<Text::GlyphID>& glyphIDs, bool16 vertical = kFalse) const = 0;

		/**
			For a single unicode character get the glyphIDs.
			@param character		IN Unicode value to get glyphid
			@param vertical		IN get vertical glyphs if kTrue
			@return Text::GlyphID the glyph corresponding to the character
		 */
		virtual Text::GlyphID GetGlyphID(UTF32TextChar character, bool16 vertical = kFalse) const = 0;

		/**
			For a single platform character get the glyphIDs.
			@param character		IN value to get glyphid
			@param stringLength	IN length of charString in bytes
			@param vertical		IN get vertical glyphs if kTrue
			@param encoding		IN encoding. If it is not provided, platform encoding is used.
			@return Text::GlyphID the glyph corresponding to the character
		 */
		virtual Text::GlyphID GetPlatformGlyphID(const char* charString, int32 bytesPerChar = 1,
									bool16 vertical = kFalse, CTEncoding *encoding = nil) const = 0;

		/**
			For a char string get the glyphIDs.
			@param charString	IN platform values to get glyphids from
			@param stringLength	IN length of charString in bytes
			@param glyphIDs		OUT glyphIDs
			@param vertical		IN get vertical glyphs if kTrue
			@param encoding		IN encoding. If it is not provided, platform encoding is used.
		 */
		virtual void GetPlatformGlyphIDs(const char* charString, int32 stringLength, K2Vector<Text::GlyphID>& glyphIDs, bool16 vertical = kFalse,
			CTEncoding *encoding = nil) const = 0;

		/**
			Determines boundaries of characters in a text string

			For example, this may be used to determine the length of a multiple unicode value sequence
			encoded in unicode 3.0 encoding.

			<b>Note:</b> GetCharacterBoundaries	recognizes surrogate pairs as single characters.
			It also recognizes Unicode value sequences containing Apple "transcoding hints" as
			single characters.
			@param text				IN unicode values to get boundries for
			@param utf16WordLength	IN length of text
			@param offsets			OUT Long integer array supplied by the caller.
									On a successful return, each integer in the array is a byte
									offset to the beginning of each character in the text string.
									One extra offset to the next byte after the last character
									in the text string is returned at the end. Consequently,
									The byte length of ith character can be calculated by
									offsets[i+1] - offsets[i].
		 */
		virtual void GetCharacterBoundaries(const UTF16TextChar * text, int32 utf16WordLength, K2Vector<size_t> &offsets) const = 0;


		/**	Checks to see if checkGlyphID is in the range of glyphs for this font and that it is defined. Uses GetNthValidGlyphIDRange
			@param checkGlyphID	Glyph id to check
			@return bool16		kTrue if valid. kFalse if invalid.
		 */
		virtual bool16 IsDefinedAndValidGlyph(Text::GlyphID checkGlyphID) const = 0;

		/**	Gets number of glyph id ranges for this font. Use with GetNthValidGlyphIDRange to determine valid glyphids.
			@return int32		Number of valid ranges
		 */
		virtual int32 GetNumValidGlyphIDRanges() const = 0;

		/**	Gets the nth range of valid glyph ids. Use GetNumValidGlyphIDRanges to determine number of ranges.
			@param nthRange		range to get
			@param firstGlyphID	OUT first glyph id of range
			@param lastGlyphID	OUT last glyph id of range
		 */
		virtual void GetNthValidGlyphIDRange(int32 nthRange, Text::GlyphID &firstGlyphID, Text::GlyphID &lastGlyphID) const = 0;

		/**	Compare the two IPMFonts to decide if they are the same. This means postscipt name,
			font type, and MM axis information are all the same. We compare CTFontDict and MM axis data.
			If the font is missing the postscript name is the name of the available font that replaces the missing one.
			Use AppendFontName(name, kTrue) to font out the missing postscript name.
			@param *compareFont		font to compare with
			@return bool16			kTrue if same. kFalse if not
		 */
		virtual bool16 IsEqual(const IPMFont *compareFont) const = 0;

		/**
			Get unicode and Opentype feature that produces the glyphID passed in.

			@param	glyphID					glyph to get access for
			@param	glyphAccessData			pass in preferences and returns results
			@param	featureToSearchCount	number of OpenType features to search. -1 to search all available
			@param	featuresToSearch		OpenType features to search. use nil if count is -1
			@return	bool16					kTrue if success. kFalse if an error occured
		*/
		virtual bool16 GetOTGlyphAccess(Text::GlyphID glyphID, GlyphAccessData * glyphAccessData, int32 featureToSearchCount, const char * featuresToSearch) const = 0;

		/**
			Get all unicode and Opentype features that produces the glyphID passed in.

			@param	glyphID					glyph to get access for
			@param	glyphAccessData			returns results
			@return	bool16					kTrue if success. kFalse if an error occured
		*/
		virtual bool16 GetAllOTGlyphAccess(Text::GlyphID glyphID, K2Vector<GlyphAccessData>& glyphAccessData) const = 0;

		/**
			Get the files used by this font.

			@param	outFiles	Vector of files used by this font
		*/
		virtual void  GetFontFiles(K2Vector<IDFile>& outFiles) const = 0;

		/**
			Get the mojikumi tsume of the given CID

			@param	cid				CID to be searched
			@param	vertical		kTrue if glyph is being drawn upright in vertical text
			@param	leftTsume		if font is CID font and has known mojikumi tsume info then this param will be modified to return the tsume (-1.0 - 0.0)
			@param	rightTsume		if font is CID font and has known mojikumi tsume info then this param will be modified to return the tsume (-1.0 - 0.0)
			@return	bool16			kTrue if success. kFalse if an error occured
		*/
		virtual bool16  GetCIDMojikumiTsume(Text::GlyphID cid, bool16 vertical, PMReal& leftTsume, PMReal& rightTsume) const = 0;

		/**
			Get the mojikumi class of the given CID

			@param	cid				CID to be searched
			@param	vertical		kTrue if glyph is being drawn upright in vertical text
			@param	mojikumiClass	if font is CID font and has known mojikumi class info then this param will be modified to return the class
			@return	bool16			kTrue if success. kFalse if an error occured
		*/
		virtual bool16  GetCIDMojikumiClass(Text::GlyphID cid, bool16 vertical, MojikumiClass& mojikumiClass) const = 0;

		/**
			Find the number of alternates for this glyphID for a given feature

			@param	glyphID		glyph to get number of alternates for
			@param	feature		feature to look for alternates
			@return	int32		number of alternates
		*/
		virtual int32 GetNumAlternates(Text::GlyphID glyphID, const char* feature) const = 0;

		/**
			Gets the component font for a glyph id. Only useful for ATC fonts.

			@param	glyphID		glyphID to find font for
			@param	componentGlyphID	glyphID in component font
			@return	IPMFont*	component font
		*/
		virtual IPMFont* QueryComponentFontAndGlyphID(Text::GlyphID glyphID, Text::GlyphID &componentGlyphID) const = 0;

		/**
			Gets the number of glyph names.
			If this font's technology is kType1Font then this method returns the number of
			the glyphs available in this font. This will also attempt to return names for
			TrueType fonts. Note, it's possible that some or all of the names
			returned are empty strings ("") because the True Type font doesn't have
			names available.

			To get the number of glyphs in the font, use IPMFont::GetNumGlyphs.

			@return	int32	number of glyph names
		*/
		virtual int32 GetNumGlyphNames() const = 0;

		/**
			Gets name of a glyph.

			Returns the glyph name for the glyphid in the font.

			@param	glyphID		glyphID to get name for
			@return	std::string	name of glyph
		*/
		virtual std::string GetGlyphName(Text::GlyphID glyphID) const = 0;

		/**	This method is used internally
			@return CTEncoding*
		 */
		virtual CTEncoding* GetCTEncoding() const = 0;

		/**
			Whether the font is CFF (Compact Font Format)

			Note that the font may be of Type 1 or CID font technology.

			@return bool16	Returns true only if the font's glyphs are represented in CFF.
		 */
		virtual bool16 IsCFF() const = 0;

		/**
			Gets baseline shift for an ATC glyph

			This returns the ATC baseline shift (in horizontal writing mode) for
			'glyphID' in a 1-unit-em instance of the font. If the font is
			not an ATC font, or if the ATC component font that 'glyphID' is
			associated with does not specify a baseline shift, this method
			returns 0.

			For example, if an ATC font is created such that a particular
			component font's glyphs are to be shifted upward by 200 font units
			(relative to a 1000-unit-em font) in horizontal writing mode, then
			this method will return -0.2 for all glyphs in that component font.

			Most clients do not need to concern themselves with this API since
			other metrics APIs take the baseline shift into account. This API
			is useful for only those clients who set vertical text by
			themselves using horizontal text metrics, since they will need to
			adjust the vertical text by the ATC baseline shift also.

			@param	glyphID		glyphID to get baseline shift for
			@return	PMReal		baseline shift for glyphID
		 */
		virtual PMReal GetATCBaselineShift(Text::GlyphID glyphID) const = 0;

		/**
			Gets the vendor id from the font.

			@param	vendorName	version id
			@return	bool16	kFalse when not found
		*/
		virtual bool16 AppendVendorID(PMString& vendorName) const = 0;

		/**
			Gets the copyright string from the font.

			@param	s		copyright string
			@return	bool16	kFalse when not found
		*/
		virtual bool16 AppendCopyrightString(PMString& s) const = 0;

		/**
			Gets the license information from the font.

			@param	s		license string
			@return	bool16	kFalse when not found
		*/
		virtual bool16 AppendLicenseInfoURL(PMString& s) const = 0;

		/**
		A way to tell if this is an SVG Font..

		@return bool16  kTrue if font is an SVG Font, kFalse otherwise
		*/
		virtual bool16 IsSVGFont() const = 0;

		/**
		A way to tell if this is font has SBIX Table..

		@return bool16  kTrue if font has SBIX Table, kFalse otherwise
		*/
		virtual bool16 IsSBIXFont() const = 0;

		/**
		A way to tell if this is font has SVG or SBIX Table..

		@return bool16  kTrue if font has SVG or SBIX Table, kFalse otherwise
		*/
		virtual bool16 IsColorFont() const = 0;

		/**
		Whether the font has SVG glyph description for a particular glyphId.

		@param    glyphId        [IN] id of the glyph to check for SVG description

		@return                True only if there is an SVG document corresponding to the glyphId
		in the SVG table of the font. otherwise false.
		*/

		virtual bool16 HasValidSVGOTDescForGlyph (Text::GlyphID glyphId) const = 0;

		/**
		A way to tell if this is an Emoji Font..

		@return bool16  kTrue if font is an Emoji Font, kFalse otherwise
		*/
		virtual bool16 IsEmojiFont() const = 0;

		/**
            A way to tell if the font came from Typekit Desktop.
         
            @return bool16  kTrue if font came from Typekit Desktop, kFalse otherwise
        */
		virtual bool16 IsTypekitDesktopFont() const = 0;

		/**
            Get the typekit ID of the font
         
            @return PMString  typekit font id, if it is a typekit subscribed font, else empty string.
        */
        virtual PMString GetTypekitFontID() const = 0;

	
	/**
            Get the stylisticSet name of the font
         
            @return PMString  return the name of stylisticset if exist else return null string
    @param featureTag                Open type feature tag corresponding to the stylistic set eg: ss01,ss02 
	
	NOTE:-This API should be called only when 
   virtual bool16 HasOTFeature(const char feature[4], const char script[4] = 0, const char language[4] = kDefaultLanguageTag)  
    returns true for a given stylistic set feature tag 

        */

		virtual PMString GetFontSytlisticName(const char featureTag[4]) const = 0;
		/*
		This method check whether a given font has the color glyph corresponding to the "Font Preview Text For Locale" example :- ["SAMPLE" string in the font preview of character panel]
		@return bool16 kTrue if the color text is available.
		*/
		virtual bool16 IsColorTextAvailable() const = 0;
	
	
	/**
	 Enum for the font weight.
	 */
	typedef enum {		// Mimicing from CTTypes. Leaving spaces between for some more if added.
		kFontWeightThin = 100,
		kFontWeightExtraLight = 200,
		kFontWeightLight = 300,
		kFontWeightNormal = 400,
		kFontWeightMedium = 500,
		kFontWeightSemiBold = 600,
		kFontWeightBold = 700,
		kFontWeightExtraBold = 800,
		kFontWeightHeavy = 900,	// Black
		kFontWeight_Unknown = 0xFFFFFFFF,
	} FontWeightType;
	
	typedef enum {
		kFontWidthUltraCondensed = 100,
		/** Extra-condensed */
		kFontWidthExtraCondensed = 200,
		/** Condensed */
		kFontWidthCondensed = 300,
		/** Semi-condensed */
		kFontWidthSemiCondensed = 400,
		/** Medium (Normal) */
		kFontWidthMedium = 500,
		/** Semi-expanded */
		kFontWidthSemiExpanded = 600,
		/** Expanded */
		kFontWidthExpanded = 700,
		/** Extra-expanded */
		kFontWidthExtraExpanded = 800,
		/** Ultra-expanded */
		kFontWidthUltraExpanded = 900,
		/** Invalid/not set value */
		kFontWidth_Unknown = 0xFFFFFFFF
	} FontWidthType;
	
	typedef enum {
		kFontXHeightAny = 100,
		/** No Fit */
		kFontXHeightNoFit = 200,
		/** Constant/Small */
		kFontXHeightConstantSmall = 300,
		/** Constant/Standard */
		kFontXHeightConstantStandard = 400,
		/** Constant/Large */
		kFontXHeightConstantLarge = 500,
		/** Ducking/Small */
		kFontXHeightDuckingSmall = 600,
		/** Ducking/Standard */
		kFontXHeightDuckingStandard = 700,
		/** Ducking/Large */
		kFontXHeightDuckingLarge = 800,
		/** Invalid/not set value */
		kFontXHeight_Unknown = 0xFFFFFFFF
		
	} FontXHeightType;
	
	typedef enum {
		kFontContrastAny = 100,
		/** No Fit */
		kFontContrastNoFit = 200,
		/** None */
		kFontContrastNone = 300,
		/** Very Low */
		kFontContrastVeryLow = 400,
		/** Low */
		kFontContrastLow = 500,
		/** Medium Low */
		kFontContrastMediumLow = 600,
		/** Medium */
		kFontContrastMedium = 700,
		/** Medium High */
		kFontContrastMediumHigh = 800,
		/** High */
		kFontContrastHigh = 900,
		/**Very High */
		kFontContrastVeryHigh = 1000,
		/** Invalid/not set value */
		kFontContrast_Unknown = 0xFFFFFFFF
	} FontContrastType;
	
	typedef enum {
		kFontCapStyleNone = 100,
		kFontCapStyleStandard = 200,
		kFontCapStyleCapsOnly = 300,
		kFontCapStyleUnknown = 0xffffffff
	} FontCapStyleType;
	
	typedef enum {
		kFontNumberStyleNone = 100,
		kFontNumberStyleLowerCase = 200,
		kFontNumberStyleUpperCase = 300,
		kFontNumberStyleUnknown = 0xffffffff
	} FontNumberStyleType;
	/**
	 @param	installTime	[OUT] An integral value the representing the number of seconds
	 elapsed since 00:00 hours, Jan 1, 1970 UTC. Client code should
	 use appropriate library methods to convert this value to a
	 convenient human-friendly format.
	 
	 @return	true if a valid font file was found and its creation/modification time could be
	 obtained, false otherwise.
	 */
	virtual bool16 GetFontInstallTime(std::time_t& installTime) = 0;
	
	/**
	 Gets the weight class of the font. This value is retrieved from the OS/2 table of a font.
	 Some fonts may not have the OS/2 table or the version of the table in which this value is
	 present.
	 
	 @return The weight class value if it exists in the font; otherwise kCTFontWeightInvalid.
	 
	 @see CTFontWeightClass
	 */
	virtual FontWeightType GetFontWeight() const = 0;
	
	/**
	 Gets the width class of the font. This value is retrieved from the OS/2 table of a font.
	 Some fonts may not have the OS/2 table or the version of the table in which this value is
	 present.
	 
	 @return The width class value if it exists in the font; otherwise kCTFontWidthInvalid.
	 
	 @see CTFontWidthClass
	 */
	virtual FontWidthType GetFontWidth() const = 0;
	
	
	/**
	 Gets the x-height class of the font. This value is retrieved from the OS/2 table of a font.
	 Some fonts may not have the OS/2 table or the version of the table in which this value is
	 present.
	 
	 @return The x-height class value if it exists in the font; otherwise kCTFontXHeightInvalid.
	 
	 @see CTFontXHeightClass
	 */
	virtual FontXHeightType GetFontXHeight() const = 0;
	
	
	/**
	 Gets the contrast class of the font. This value is retrieved from the OS/2 table of a font.
	 Some fonts may not have the OS/2 table or the version of the table in which this value is
	 present.
	 
	 @return The contrast class value if it exists in the font; otherwise kCTFontContrastInvalid.
	 
	 @see CTFontContrastClass
	 */
	virtual FontContrastType GetFontContrast() const = 0;
	
	/**
	 Get the caps style of the font based on some calculation heuristics.
	 FOR INTERNAL USE ONLY.
	 */
	virtual FontCapStyleType GetFontCapStyleType() = 0;
	
	/**
	 Get the Numbering style of the font based on some calculation heiristics.
	 FOR INTERNAL USE ONLY.
	 */
	virtual FontNumberStyleType GetFontNumberStyleType() = 0;

	/**
		@return true if font is variable font, otherwise false.
	*/
	virtual bool16 IsVariableFont() const = 0;
    
    /**
     Sets the Nth instance's design axes of variable font.
     @param n Index of instance in variable font dict
     */
    virtual bool16 SetNthVariableDesignAxes(int32 n) = 0;
    
    /**
     Sets a variable instance's design axes of variable font, given design axes values.
     @param designAxes Array of design axis values
     */
    virtual void SetNthVariableDesignAxes(Fixed* designAxes) = 0;

};

DECLARE_BASE_TYPE(IPMFont::FontProtection);

template <>
class InterfacePtr<IPMFont>
{
public:
			// Note: Constructing an InterfacePtr from an existing,
			// "real" interface pointer implies the InterfacePtr
			// now owns the reference that was held by the real pointer.
		InterfacePtr(IPMFont * pFace)
			: fFace(pFace) {}

		~InterfacePtr()
			{ Release_(fFace); }

		InterfacePtr(void) : fFace(nil)
			{}

		InterfacePtr(const InterfacePtr<IPMFont>& f) : fFace(AddRef_(f.get()))
			{}

		// Constructor that enables InterfacePtr<const IFoo> to be constructed from an InterfacePtr<IFoo>.
//		template <class OtherType>
//			InterfacePtr(const InterfacePtr<OtherType>& p)
//			:fFace(AddRef_(p.get())) { }

		InterfacePtr<IPMFont>& operator=(const InterfacePtr<IPMFont>& p)
			{	reset(AddRef_(p.get())); return *this; }
		InterfacePtr<IPMFont>& operator=(const InterfacePtr<const IPMFont>& p)
			{	reset(AddRef_(p.get())); return *this; }

		operator IPMFont*() const
			{ return fFace; }
			// We allow the cast operator to return a nil pointer
			// since it is valid to test against nil and may be valid
			// to pass a nil pointer to some methods.


		IPMFont* operator ->() const
			{
			#ifdef DEBUG
				ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
			#endif
			return fFace;
			}

		// Added forget, get and reset from InterfacePtr
		IPMFont* forget()
			{
				IPMFont* result = fFace;
				fFace = 0;
				return result;
			}

		IPMFont* get() const
			{	return fFace; }

		void reset(IPMFont* p = 0)
			{
				Release_(fFace);
				fFace = p;
			}

		void reset(const IPMFont* p)
			{
				Release_(fFace);
				fFace = const_cast<IPMFont*>(p);
			}

private:
	static IPMFont* AddRef_(const IPMFont* p)
		{ if(p) p->AddRef(); return const_cast<IPMFont*>(p);}
	static void Release_(IPMFont* p)
		{ if(p) p->Release(); }

	IPMFont * fFace;
};


#endif
		//__IFont__

