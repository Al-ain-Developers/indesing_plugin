//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontInstance.h $
//  
//  Owner: Eric Menninga
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
//  See the implementation CTPFontInstance.cpp and refer to the CoolType
//  documentation for more information
//  
//========================================================================================

#pragma once
#ifndef __IFontInstance__
#define __IFontInstance__

#include "GRRefCountedObj.h"
#include "InterfacePtr.h"
#include "IFontMgr.h"			// for IFontMgr::WritingDirection
#include "CTextEnum.h"			// for Text::GlyphID, etc

class WideString;
class PMString;
class CTFontInst;
class PMMatrix;
class IOutlineInfo;
class PMRealGlyphPoint;

/** This is a shell over the CoolType API for FontInstances.
	@ingroup text_font
*/
class IFontInstance : public grRefCountedObj
{
	public:
		/**
			For a Unicode value get the glyphID.
			@param charCode		IN Unicode value to get glyphids from
			@return glyphID for Unicode
		 */
		virtual Text::GlyphID GetGlyphID(UTF32TextChar charCode) const = 0;

		/**
			For a widestring get the glyphIDs.
			@param textString	IN Unicode values to get glyphids from
			@param glyphIDs		OUT glyphIDs
		 */
		virtual void GetGlyphIDs(const WideString& textString, K2Vector<Text::GlyphID>& glyphIDs) const = 0;

		/**
			For a buffer of utf16 chars get the glyphIDs.
			@param buffer	IN Unicode values to get glyphids from.
			@param bufSize	number of utf16 values in the string (not characters).
			@param glyphIDs		OUT glyphIDs
		 */
		virtual void AppendGlyphIDs(const UTF16TextChar* buffer, int32 bufSize, K2Vector<Text::GlyphID>& glyphIDs) const = 0;

		/**
			For a buffer of utf16 chars get the glyphIDs.
			@param glyphPoints	OUT resulting glyphs are stored here.
			@param numGlyphs	IN number of glyphPoints available in the buffer.
			@param textchars	IN Unicode values to get glyphids from.
			@param bufSize	number of utf16 values in the string (not characters).
			@return the number of glyphIDs written.
		 */
		virtual int32 FillOutGlyphIDs(PMRealGlyphPoint *glyphPoints, int32 numGlyphs, const UTF16TextChar* textchars, int32 bufSize) const = 0;

		/**
			Glyph id for undefined glyph.
			@return undefined glyph identifier
		 */
		virtual Text::GlyphID GetNotDefinedGlyph() const = 0;

		/**
			Returns the default pen displacement

			The default pen displacement is sometimes called escapement or advance width.
			This is a simple lookup function and does not take into account things like
			kerning.  Note that the writing direction for 'this' will effect the values
			returned for this function. If the writing direction is kWD_LeftToRight, the horizontal
			advance    width is returned. If the writing direction is kWD_TopToBottom, the vertical
			advance height is returned. This means that if the font instance contains a
			rotated matrix the width returned is 0, i.e., rotated matrices are not handled by
			this function and a debug alert message is displayed in this case. If the font
			instance contains a rotated matrix then the GetWidths() function should be called.

			@param glyphID		glyphid to get width for
			@return width of glyph
		 */
		virtual PMReal GetGlyphWidth(Text::GlyphID glyphID) const = 0;

		/**
			Returns the default pen displacements for one or more glyphs

			This function is a multiple glyph version of GetGlyphWidth with the important
			exception that font instances that contain rotated matrices are handled
			correctly, i.e., the PMRealGlyphPoint's xPosition and yPosition fields
			are set to the x and y components, respectively, of either the horizontal
			advance (if the writing direction is kWD_LeftToRight) or the vertical advance
			(if the writing direction is kWD_TopToBottom) of each glyph.
			It is a simple lookup function and does not take into account things like
			kerning.

			@param glyphPoints		contains glyphs to get width values for and puts results in x and y fields
			@param numGlyphs		number of glyphs in glyphPoints
		 */
		virtual void GetWidths(PMRealGlyphPoint *glyphPoints, int32 numGlyphs) const = 0;

		/**
			Get bounding box for glyphid.
			@param glyphID		glyphid to get bbox for
			@return bounding box of glyph
		 */
		virtual PMRect GetGlyphBBox(Text::GlyphID glyphID) const = 0;

		/**
			Measure text using this font instance. Finds width and maximum height.
			@param text							Unicode values to find dimensions of.
			@param utf16BufferLength	Length of Unicode text.
			@param xWidth						OUT width of Unicode values.
			@param yWidth						OUT maximum height of Unicode values.
		 */
		virtual void MeasureWText(const UTF16TextChar* text, int32 utf16BufferLength, PMReal& xWidth, PMReal* yHeight = nil) const = 0;
		/**
			Measure text using this font instance. Finds width and maximum height.
			@param string						Unicode values to find dimensions of.
			@param xWidth						OUT width of Unicode values.
			@param yWidth						OUT maximum height of Unicode values.
		 */
		virtual void MeasureWText(const WideString& string, PMReal& xWidth, PMReal* yHeight = nil) const = 0;

		/**
			Measure text using this font instance. Finds width and maximum height.
			@param string						Unicode values to find dimensions of.
			@param xWidth						OUT width of Unicode values.
			@param yWidth						OUT maximum height of Unicode values.
		 */
		virtual void MeasureWText(const PMString& string, PMReal& xWidth, PMReal* yHeight = nil) const = 0;

		/**
			Returns whether font instance has kerning table. This is not an OpenType specific
			call. This call will return true if the font has kerning whether it is OpenType or not.
			@return kTrue if font instance has kerning table
		 */
		virtual bool16 HasKerningTable() const = 0;

		/**
			Get kerning values for glyphids.
			@param glyphPoints		contains glyphs to get kern values for and puts results in x and y fields
			@param numGlyphs		number of glyphs in glyphPoints
			@param vertical			vertical or horizontal kerning? (ie "kern" or "vkrn" opentype feature?)
			@param scriptTag script tag
			@param langTag language tag
		 */
		virtual void GetKerns(PMRealGlyphPoint *glyphPoints, int32 numGlyphs, bool16 vertical = kFalse, const char* scriptTag = nil, const char* langTag = nil) const = 0;

		/**
			Flags for outline iterators

			<b>kHintedOutlines</b> If set, the outlines will be fetched with hints applied at the size
			specified by the font matrix. If not set, unhinted outlines will be fetched

			<b>kVerticalOutlines</b> If set, CoolType will assume that the outlines are being set
			vertically and the origin will be shifted accordingly.  This will approximate postscript's
			vmode=1 and will shift the outlines left and down

			<b>kVerticalGlyphs</b> If set, the glyphs are assumed to be vertical glyphs but no wmode adjustment will be done.
			When set, the outlines for ATC font glyphs whose baseline is adjusted vertically will
			be adjusted horizontally instead. kVerticalOutlines and kVerticalGlyphs are mutually
			exclusive so both flags must not be set.
		*/
		 enum { kNormalOutlines = 0,
				kHintedOutlines = 1,
				kVerticalOutlines = 2,
				kVerticalGlyphs = 4 } ;

		/** Allows the caller to get path information about a specific Glyph.
			IOutlineInfo is a call back class. The various methods of IOutlineInfo are called
			for each segment of the character path.
			@param callBack callback class
			@param glyphID glyph for which path info is obtained
			@param xOffset x offset
			@param yOffset y offset
			@param flags outline iterator
		*/
		virtual void GetOutlineInfo(IOutlineInfo *callBack, Text::GlyphID glyphID, PMReal xOffset, PMReal yOffset, int32 flags = kNormalOutlines) const = 0;

		/**
			Get the font instance's ascent. Height of the lower case 'd'.
		*/
		virtual PMReal GetAscent() const = 0;

		/**
			Get the font's descent. Bottom of the lower case 'p'.
		*/
		virtual PMReal GetDescent() const = 0;

		/**
			Height of a capital 'X' if outline of X is available. Otherwise, bbox height.
		*/
		virtual PMReal GetCapHeight() const = 0;

		/**
			Height of small 'x' if outline of x is available. Otherwise 2/3 of bbox height.
		*/
		virtual PMReal GetXHeight() const = 0;

		/**
			Returns height of em-box. In CJK fonts, this is the height of the ideographic embox,
			which is usually equal to the pointsize, unless the font uses a scaled embox.

			In vertical font instances, this "height" is actually the width of the embox,
			since ideographs are drawn upright in the vertical line of text.

			The font's embox is based on the left, top,
			right, and bottom edges (in horizontal writing mode) of the ideographic em-box of
			the font. This value will be defined for every font (including non-CJK
			fonts, where it can be used to em-box-align these fonts alongside CJK fonts).

			The ideographic em-box of a font, also referred to as an ideographic font's design
			space, defines a standard monospaced escapement around the glyphs of the font, for
			both horizontal and vertical writing modes. This will be an em high and an em wide
			unless the vendor explicitly indicates otherwise in the font. The OpenType
			specification strongly recommends against this being other than an em wide, but
			there are legitimate reasons for having it be other than an em high: some fonts
			used in Japanese newspaper layout, for example, have a vertically compressed
			ideographic em-box.

			See the 'ideo' Baseline tag in the OpenType tag registry for more information.

			@return	height of em-box
		*/
		virtual PMReal GetEmBoxHeight() const = 0;

		/**
			Calculate inset of Ideographic Character Face (ICF) box from embox. In vertical font
			instances, this is the left inset and right inset.

		   The ICF box is the maximum bounding box of the ideographic portion of a CJK font,
		   usually centered within the em-box. Note that this value is defined also for
		   non-CJK fonts.

		   The ICF box is used to size character grids to approximate the ink boundaries
		   of each character and of the outsides of a full-justified frame.

		   See the 'icfb' and 'icft' Baseline tags in the OpenType tag registry for more information.

			@param	fromEmTop	distance of ICF top from embox top
			@param	fromEmBottom	distance of ICF bottom from embox bottom
		*/
		virtual void GetICFBoxInsets(PMReal * fromEmTop, PMReal * fromEmBottom) const = 0;

		/**
			Returns the distance from the Roman baseline to the em-box bottom for the
			horizontal writing mode. This is used to calculate roman baseline offset for
			both horizontal and vertical text, since InDesign draws vertical text and horizontal
			text from the same location (the pen location is at the roman baseline).
			@return	horizontal em-box depth
		*/
		virtual PMReal GetHorizEmBoxDepth() const = 0;

		/**
			Returns the distance from the Roman baseline to the ICF box bottom for the
			horizontal writing mode. This is used to calculate roman baseline offset for
			both horizontal and vertical text, since InDesign draws vertical text and horizontal
			text from the same location (the pen location is at the roman baseline).

			@return	horizontal ICF box depth
		*/
		virtual PMReal GetHorizICFBoxDepth() const = 0;

		/**	Returns CTFontInst pointer for this font instance
		*/
 		virtual CTFontInst* GetCTFontInst() const = 0;

		/**	Returns CTFontDict pointer for this font instance
		*/
		virtual CTFontDict* GetParentCTFontDict() const = 0;

		/**	Returns design axes vector and length in case of variable font.
		*	'designVec' must be an allocated array that is at least of length kCTMaxDesignElements. 
		*   If designVec passed nil then, only designVecLen gets populated.
		*	@param designVec	pass memory allocated array of RMReal, which gets populated by API.
		*	@param designVecLen	populated by API to get number of design axes.	
		*/
		virtual void GetDesignVector(PMReal* designVec, size_t& designVecLen) const = 0;

		/**	Returns number of design axes in case of variable font.
		*	@return number of design axis in font.
		*/
		virtual size_t GetNumDesignAxes() const = 0;

		/**	Returns PMMatrix for this font instance
		*/
		virtual const PMMatrix& GetPMMatrix() const = 0;

		/**	Get WritingDirection for this font instance
		 */
		virtual IFontMgr::WritingDirection GetWritingDirection() const = 0;

		/**
			FeatureInfoFlags
			@see ApplyFeatures
		*/
		enum FeatureInfoFlags {
			/** Apply 'GSUB' lookups for feature tags. */
			kApplyGlyphSub			= 1 << 0,
			/** Apply 'GPOS' lookups for feature tags. */
			kApplyGlyphPos			= 1 << 1,
			/** Apply 'GSUB' and 'GPOS' lookups for feature tags. */
			kApplyGlyphSubAndPos	= kApplyGlyphSub | kApplyGlyphPos,
//			/** This flag is not used by ApplyFeatures. */
//			kReportOriginalIndices	= 1 << 2,
			/** Indicates the directionality of the glyph run.
				If this flag is set, then the glyphpoint array is for a
				right-to-left run of text; otherwise, it is for a left-to-right
				run of text. In either case, the glyphpoints are ordered
				in the reading order.
			*/
			kRightToLeft				= 1<<3,
			kCTFlagsBitMask			= 0x0F,

			kModifyWidthsInPlace	= 1 << 5
		};

		/**
			Change attribute flags
			@see ApplyOTFeatures changeAttrib
		*/
		enum {
		    kNoChange         = 0,			//kCTOTNoChange
//		    kSingleSubstitute = 1<<0,		// kCTOTSingleSubstitute
//		    kMultiSubstitute  = 1<<1,		// kCTOTMultiSubstitute
//			kAlternate        = 1<<3,		// kCTOTAlternate
			kLigatureApplied      = 1<<4,	//kCTOTLigature
			kGlyphDeleted         = 1<<5,	//kCTOTDeleted
//		    kRepositioned     = 1<<6		//kCTOTRepositioned
		};

		/**	Applies features for a set of glyphs.
			In OpenType fonts, the order in which features are applied depends on
			the order of lookups in the 'GSUB' and 'GPOS' tables in the font, and
			not on the order in the features array of this API.

			The featureRanges array, if non-NULL, must contain numFeatures*2
			elements. Each feature specified in the features array will correspond,
			in order, to a range in the featureRanges array. A range is represented
			by two consecutive longs: the starting and ending indexes, respectively,
			into the glyphPoints array (which starts at index 0). A client need not bother
			"clamping" a range e.g. if there are 3 glyphPoints, then the range -1 .. 4 will
			be regarded as 0 .. 2.

			@param glyphPoints 		Pointer to an array of PMRealGlyphPoint's with
									'numGlyphPoints' valid entries and 'numGlyphPointsAvail'
									available entries (to allow room for possible expansion with
									'GSUB'). The valid entries must have their glyphID's
									initialized but the x and y positions needn't be initialized.<p>

									If expansion occurs, and the number of glyphPoints
									needed is greater than numGlyphPointsAvail, then the function
 									will set numGlyphPointsAvail to that number and return false
									(the client can then re-size the array and call again);
									otherwise it will return true and set 'numGlyphPoints' to the
									actual valid number of glyphPoints if this increases or
									decreases with 'GSUB'.<p>

									If glyph positioning is requested (kApplyGlyphPos or
									kApplyGlyphSubAndPos), The xPosition and yPosition fields
									of the glyphPoints will be set to the deltas from the
									glyphs' default positions were no positioning features
									applied. So if the requested positioning layout features e.g.
									"kern" didn't affect the glyphs, the xPosition and yPositions
									would all be set to 0 on return.<p>

									The position of the glyphPoints is expressed in a coordinate system with
									the x axis horizontal, increasing in the direction of the run of text
									(i.e. increasing toward the right if rightToLeft is kFalse,
									increasing toward the left if rightToLeft is kTrue). The y axis is vertical,
									increasing from top to bottom.<br>

			@param numGlyphPoints	number of glyphs in glyphPoints
			@param numGlyphPointsAvail	glyphPoints allocated in glyphPoints variable
			@param numFeatures		number of features in features variable
			@param features			features to apply to glyphs
			@param choiceIndices	array of choice for features. count is the same as numFeatures.
									use -1 for features without choice
			@param featureRanges	length of size_t is 2*numFeatures. size_t pair indicates
									the range of glyphs to apply the feature to. 0,0 would
									apply only to the first glyph. One pair for each feature in the
									features array. This array is optional
									and may be NULL
			@param changeAttrib		Array of flags. This array of bytes  must be as long as 'numStrikes'
									if present. Set to NULL if functionality not needed.
									The array will be filled in with bitflags that will indicate what
									changes occurred in the* original* strike list. This may not match
									the resulting list but is intended to indicate what has changed to
									aid in cursor positioning, for instance.
			@param flags			@see FeatureInfoFlags
			@param penPos			If this optional parameter is non-NULL and glyph positioning is
									requested (kApplyGlyphPos or kApplyGlyphSubAndPos in the
									featureInfo's flags field), then this parameter must point to
									an array of 2 elements.<p>

									On successful return, these elements (which needn't be
									initialized by the client) will be set to the x and y deltas,
									respectively, from the point to which the pen advances after
									the last resulting glyphPoint's default pen displacement.
									If glyph positioning is not requested, this parameter is
									not read and may be set to NULL
			@param caretPositions   The glyphs' positions for rasterizing will be maintained in
									the 'glyphPoints' array, but if the client wants precise caret
									positioning it must maintain its own parallel array for caret
									positions. Conceptually, before applying layout features, these
									two arrays coincide.<br><p>

									If this parameter is non-NULL and glyph positioning is requested,
									(kApplyGlyphPos or kApplyGlyphSubAndPos in the featureInfo's flags field)
									then this parameter must point to an array of (<i>n</i> + 1)
									entries, where <i>n</i> is the input value of 'numGlyphPointsAvail'.
									On successful return, these entries (which needn't be
									initialized by the client) will be set to the increments in
									caret positions that resulted from applying the features.<p>

									If the writing direction of the font instance is
									left to right, the caret increments in the x direction are
									returned. If the writing direction is top to bottom, the caret
									increments in the y direction are returned.<p>

									The initial <i>m</i> entries (where <i>m</i> is the output value of
									'numGlyphPoints') will correspond to the caret positions just
									before each of the glyphs in the resulting 'glyphPoints' array,
									and the next entry will correspond to the caret position just
									after the last glyph in the resulting 'glyphPoints' array.
									Caret positions within a ligature glyph are not provided.<br>

			@param scriptTag		4-character OpenType script tag. The 'script' and 'language' parameters
									identify the language system to be used. If 'script' is NULL, a	language system in
									the font based on the font's writing script is used; the 'language'
									parameter is ignored. 'script' and 'language' are ignored for non-OpenType fonts.
			@param langTag			4-character OpenType language tag. See 'script' parameter above.
			@return kFalse if there was an error
		 */
		virtual bool16 ApplyFeatures(PMRealGlyphPoint* glyphPoints, size_t& numGlyphPoints, size_t &numGlyphPointsAvail,
									 int32 numFeatures, const char* features, const int32* choiceIndices,
									 const size_t *featureRanges, char* changeAttrib, FeatureInfoFlags flags,
									 PMReal* penPos = nil, PMReal* caretPositions = nil,
									 const char* scriptTag = nil, const char* langTag = nil) const = 0;


		/** Private: GetCTFontInstance returns the underlying opaque font instance object.
			@return the opaque underlying font instance.
		*/
		virtual CTFontInstance* GetCTFontInstance() const = 0;

		/** GermanLocaleDropsLigatures
			In some earlier versions of Adobe OpenType fonts, the German locale
			would not do ligatures. However, earlier versions of InDesign would do ligatures
			because the locale was not considered. After passing in the locale, we want to
			continue to do ligatures anyway in the fonts with this behavior.
			@return true if the font supports ligatures with LATN, DefaultLanguage, but not LATN, GERMAN
		*/
		virtual bool16 GermanLocaleDropsLigatures() const = 0;

};


template <>
class InterfacePtr<IFontInstance>
{
public:
			// Note: Constructing an InterfacePtr from an existing,
			// "real" interface pointer implies the InterfacePtr
			// now owns the reference that was held by the real pointer.
		InterfacePtr(IFontInstance * pFace)
			: fFace(pFace) {}

		~InterfacePtr()
			{ Release_(fFace); }

		InterfacePtr(void) : fFace(nil)
			{}

		InterfacePtr(const InterfacePtr<IFontInstance>& o) : fFace(AddRef_(o.get()))
			{}

		InterfacePtr<IFontInstance>& operator=(const InterfacePtr<IFontInstance>& p)
			{ if (&p != this) reset(AddRef_(p.get())); return *this; }

		operator IFontInstance*() const
			{ return fFace; }
			// We allow the cast operator to return a nil pointer
			// since it is valid to test against nil and may be valid
			// to pass a nil pointer to some methods.

		IFontInstance * operator ->() const
			{
			#ifdef DEBUG
				ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
			#endif
			return fFace;
			}

		// Added forget, get and reset from InterfacePtr
		IFontInstance* forget()
			{
				IFontInstance* result = fFace;
				fFace = 0;
				return result;
			}

		IFontInstance* get() const
			{	return fFace; }

		void reset(IFontInstance* p = 0)
			{
				Release_(fFace);
				fFace = p;
			}

		void reset(const IFontInstance* p)
			{
				Release_(fFace);
				fFace = const_cast<IFontInstance*>(p);
			}

private:
	static IFontInstance* AddRef_(const IFontInstance* p)
		{ if (p) p->AddRef(); return const_cast<IFontInstance*>(p);}
	static void Release_(IFontInstance* p)
		{ if (p) p->Release(); }


	IFontInstance * fFace;
};
#endif

