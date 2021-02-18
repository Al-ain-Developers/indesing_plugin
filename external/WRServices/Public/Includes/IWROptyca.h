//========================================================================================
//  
//  File: IWROptyca.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWROptyca__
#define __IWROptyca__

#include "WRDefines.h"
#include "WRAttributes.h"
#include "WRConfig.h"
#include "OptycaTypes.h"
#include "SubstitutionLog.h"
#include "InputOutputHB.h"
#include "IWRHarfbuzzFontAccess.h"
#include "IWRFontContext.h"
#include "IWRFont.h"
#include "WRClass.h"
#include "WRDirectionalityServices.h"
#include "WROptycaRunSettings.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

// constant used to mark chars for which the advance width is not fixed by the client 
// but by the font - usually all chars except em space, en space etc. 
#define UNKNOWNWIDTH 1.0e+21F
#define ISUNKNOWNWIDTH(v) (v >= 1.0e+20F || v <= -1.0e+20F)
#define ISKNOWNWIDTH(v) (v < 1.0e+20F && v > -1.0e+20F)

class IWRFontContext;

#ifdef WINOPTYCA
class WRSERVICES_DECL Trace
{
public:
	virtual void PrintStrikeArray(Optyca* ca) = 0;
};
#endif

// evaluation of the justification quality. Used in ID only to highlight degenerated
// situations so that the user can manually fix them
enum WRJustifBadness { kWRNotBad,kWRKindaBad,kWRBad,kWRVeryBad,kWRMaxBad };

//enum for enableAutoScriptDetection- 0- disabling script detection, 1- enabling but with language set using SetLanguage function, 2 - force script detection
enum WREnableAutoScriptDetectionEnum { kScriptDetectionDisabled, kScriptDetectionEnabledWithLangSet, kScriptDetectionEnabled} ;
enum ShapingEngine
{
	kWRHarfbuzzShaping = 0,
	kWRLipikaShaping = 1,
	kWRLipikaWithHarfbuzzShaping = 2
};

enum ClientEncoding
{
	kUTF32HB, kUTF16HB, kUTF8HB
};
enum RoutingScripts
{
	kWRLatinOnly = 1,
	kWRIndicOnly = 2,
	kWRMENAOnly = 4,
	kWRCJKOnly = 8,
	kWRNoScriptLipikaOnly = 16, // If no scripts are detected route everything via Lipika
};
// what are the desired and allowed values for word and letter spacing
// and for glyph morphing. When should latin ligature be undone
typedef struct
{
	WRFloat 	fMinWordSpacing;
	WRFloat		fDesWordSpacing;
	WRFloat		fMaxWordSpacing;

	WRFloat 	fMinLetterSpacing;
	WRFloat		fDesLetterSpacing;
	WRFloat		fMaxLetterSpacing;

	WRFloat 	fMinGlyphScaling;
	WRFloat		fDesGlyphScaling;
	WRFloat		fMaxGlyphScaling;

	WRFloat		fLigBreakBelow;		// -0.2333 used Times-Italic for these values.
	WRFloat		fLigBreakAbove;		// 0.0800

	bool		fEMLetterSpacing;
} WRJustificationParams;

// values returneg by OptycaStyleClientControl::ExceptionProcessing
// to request a special handling
enum SpecialProcessingType { 
	kSpecialProcessingNone,				///< regular character
	kSpecialProcessingIgnore,			///< skip it (deletion will be recorded in the sublog)
	kSpecialProcessingUseID,			///< override the font char->glyph mapping (spacial char inserted with the glyph panel, with no unicode)
	kSpecialProcessingUseIDAndWidth,	///< override the font char->glyph mapping and the glyph width coming from the font (EM, EN space,)
	kSpecialProcessingInterWordSpace,	///< what is says
	kSpecialProcessingFlushSpace,		///< all the justification extra goes to this character
	kSpecialProcessingTab,				///< the following text will be aligned on the next tab stop
	kSpecialProcessingRightTab,			///< the following text will be right aligned (left aligned in a RTL line) on the right indent

	/// auto text marker
	/** the char must be substitued by a calculated text (Page numbers, section names, ...)
		the actual string is retrieved by OptycaStyleClientControl::GetAutoText **/
	kSpecialProcessingAutoText,			
										
	kSpecialProcessingCalculatedWidth,	///< inline graphics marker

	/// "indent-to-here" marker
	/**
	the effect is to prevent full justification between the indenttohere and the previous tab,
	in compliance with the way InDesign works (otherwise it's very difficult to find where
	is the indent location at composition time, justification not applied yet)
	the indentToHere char itself will be shaped as a zero width space
	**/
	kSpecialProcessingIndentToHere,
	kSpecialProcessingFixedWidthSpace ///< use regular space with specific width if not available as regular char
};

/// Arabic mark positioning control (returned by OptycaStyleClientControl::GetDiacPosPolicy)
enum DiacPosPolicy { 
	kVPosNone = 0,			/**< no positioning (PM compatibility) */
	kVPosLoose = 1, 		/**< loose positioning (PM compatibility) */
	kVPosNormal = 2,  		/**< medium positioning (PM compatibility) */
	kVPosTight = 3, 		/**< tight positioning (PM compatibility )*/
	kVPosMask = 3,			/**< PM compatibility mask */
	kUseGPOS = 0x40,		/**< use OT GPOS whenever available */
	kUseBBox = 0x80			/**< use algorithmic positioning */
};

/// OptycaOutputRun font specification
/** which font must be used to draw a glyph? 0 = nominal font, 1 = complementary font
if script fallback is enabled, the WRComplementaryIndex can be negative; in this case the font is GetDefaultFont(1 - index)
@see kWRAttrTag_UseScriptFallback, kWRAttrTag_UseComplementaryFont, GetDefaultFont, OptycaOutputRun
NB: this scheme may evolve in the future
*/

// justification method, alignment direction if not fully justified
// add kIgnoreTrailingSpaces to force a zero width for trailing whites (usually what is expected)
typedef enum { 
	kNoJustification,		// do nothing : line breaking or Roman style justification only
	kLatinLike,				// letter and word spacing, glyph scaling
	kEvenKashidasStretched,	// put kashidas in every connecting place, with an even fractional width (what Sinai did)
	kTraditionalNaskh,		// put kashidas according to the traditional rules for naskh
	kTraditionalKufi,		// put kashidas according to the traditional rules for kufi
	kTraditionalNaskhTatweel,// put kashidas by tatweel insertion only, according to the traditional rules for naskh
	kTraditionalNaskhKashida,// put kashidas by connection stretching only (no long forms), according to the traditional rules for naskh
	kTraditionalNaskhTatweelFrac,// put kashidas by tatweel insertion only, according to the traditional rules for naskh, adjust with fractional tatweel above 1 tatweel
	kTraditionalNaskhKashidaFrac,// put kashidas by connection stretching only (no long forms), according to the traditional rules for naskh, adjust with fractional tatweel above 1 tatweel
	kMethodMask = 0x00FF,
	// others may be added in the future
	kAlignSingleWordOnStart = 0x0000,	// left alignement on a LTR line
	kAlignSingleWordOnEnd = 0x0800,	// right alignement on a LTR line
	kAlignSingleWordOnCenter = 0x1000,
//	kAlignCenter = 0x4000,	was already defined in DragonTail, the best should be to use namespace
	kAlignSingleWordFull = 0x1800,
	kAlignSingleWordMask = 0x1800,
	kAlignOnStart = 0x0000,	// left alignement on a LTR line
	kAlignOnEnd = 0x2000,	// right alignement on a LTR line
	kAlignOnCenter = 0x4000,
//	kAlignCenter = 0x4000,	was already defined in DragonTail, the best should be to use namespace
	kAlignFull = 0x6000,
	kAlignMask = 0x6000,
	kIgnoreTrailingSpaces = 0x8000


	//IAABB???MMMMMMMMM
	// 
	// I = ignore trailing space
	// AA = align rule after last tab
	// BB = align rule after last tab if single word and full justif was requested
	// MMMMMMMMMM = justification method
	// the first tab field is always aligned on start
	// the next tab fields are aligned depending in the tab stop type
	// the last tab field alignment is more complex: the area allocated to it is computed based on the tab alignment, 
	// and then the text is aligned or justified inside this area according to the align rule of the paragraph
} WRJustificationPolicy;

/// Tab stop type
/**
	Defines the type of the tab stop in the OptycaTabStop class
	@see OptycaTabStop
*/
enum WRTabStopType {
	kWRAlignAfterTab,	///< left aligned in LTR, right aligned in RTL
	kWRAlignBeforeTab,	///< right aligned in LTR, left aligned in RTL
	kWRAlignCenterTab,	///< centered
	kWRAlignOnCharTab	///< align on specitic char (often decimal dot)
};

/// Optyca Tab Stop specitication
/**
Members of this class represent tab ruler stops. The x-axis extends in the same direction
as the main paragraph direction. Units are those used for measuring text advance width.
@see WRTabStopType
*/
class OptycaTabStop
{
public:
	OptycaTabStop(WRTabStopType tabType, WRFloat tabPosition, WRUnichar32 alignChar = 0, WRInt32 leaderString = -1) : 
		fType(tabType),
		fPosition(tabPosition),
		fAlignChar(alignChar),
		fLeader( leaderString)
	{
	};

	WRTabStopType GetType() const { return fType; }
	WRFloat GetPosition() const { return fPosition; }
	WRUnichar32 GetAlignChar() const { return fAlignChar; }
	WRInt32 GetLeader() const { return fLeader; }
	void SetType(WRTabStopType tabType) { fType = tabType; }
	void SetPosition(WRFloat tabPosition) { fPosition = tabPosition; }
	void SetAlignChar(WRUnichar32 alignChar) { fAlignChar = alignChar; }
	void SetLeader(WRInt32 leaderIndex) { fLeader = leaderIndex; }

protected:
	WRTabStopType	fType;		///< alignment specification
	WRFloat			fPosition;	///< position relative to the logical start of the line
	WRUnichar32		fAlignChar; ///< the alignment character, if fType == kWRAlignOnCharTab
	WRInt32			fLeader;	///< index of the leader string or -1 if none
};


//==========================================================================================
// OptycaStyleClientControl
// This class encapsulate a lot of callback functions used by optyca to get from the client
// on a on-demand basis some extra information (usually stylistis information) about
// the characters. It is the way optyca can access the content of the client-defined opaque
// style record ref (StyleRef)
// the client must provide a implementation for each callback thru  the definition of a
// derived class.
 
class OptycaStyleClientControl
{
public:

	virtual ~OptycaStyleClientControl() { }
	
	/// Tests if to styles are compatible for ligatures
	/** 
		The client must implemement a test to determine if the styles are graphically close enough to apply create ligatures across 
		the run boundary (for example, differences of font or size usually break the ligature).
		It's up to the client to define through this method the compatibility rules.
		A the implementation is often close to the one of CanDoCursivityAcross, but CanDoLigatureAcross should also test the 
		occurence of manual kerning between the two, which is usually a condition to break a ligature. However,
		a zero manual kerning is usually interpereted as a special case, meaning no kerning but do ligature.
		@param styleA the StyleRef for the first run in logical order
		@param styleB the StyleRef for the second run in logical order
		@return a bool true is the kerning can be applied on both runs in one call 
	*/
	virtual bool				CanDoLigatureAcross(StyleRef styleA, StyleRef styleB) = 0;

	/// Tests if to styles are compatible for cursivity
	/** 
		The client must implemement a test to determine if the styles are close enough to apply the cursivity across the run boundary 
		(for example, differences of font or size usually break the cursivity, since the countours cannot connect smoothly)
		It's up to the client to define through this method the compatibility rules.
		A default implementation is provided, which calls CanDoLigatureAcross, assuming the rules are roughly the same, but real applications
		usually need to implement both.
		@param styleA the StyleRef for the first run in logical order
		@param styleB the StyleRef for the second run in logical order
		@return a bool true is the kerning can be applied on both runs in one call 
	*/
	virtual bool				CanDoCursivityAcross(StyleRef styleA, StyleRef styleB) { return CanDoLigatureAcross(styleA, styleB); }

	/// Tests if to styles are compatible for kerning
	/** 
		The client must implemement a test to determine if the styles are graphically close enough to apply the kerning in one shot 
		(for example, difference of color usually transparent to the kerning process)
		It's up to the client to define through this method the compatibility rules
		The kerning method and kerning value are checked separately in SameKerningMethod
		@param styleA the StyleRef for the first run in logical order
		@param styleB the StyleRef for the second run in logical order
		@return a bool true is the kerning can be applied on both runs in one call 
		@sa SameKerningMethod
	*/
	virtual bool				CanUseSingleKerning(StyleRef styleA, StyleRef styleB) = 0;

	/// Tests if tthe kerning is the same in the two styles
	/** 
		The client must implemement a test to determine if the kerning method is identical: both metrics, bot optical
		of both manual wth the same value
		@param styleA the StyleRef for the first run in logical order
		@param styleB the StyleRef for the second run in logical order
		@return a bool true is the methods are the same
	*/
	virtual bool				SameKerningMethod(StyleRef styleA, StyleRef styleB)
	{
		WRUNUSED(styleA);
		WRUNUSED(styleB);

		return true;
	}


	/// Get the font dict associated with a style
	/** 
		The client is expected to implement this method and return the font instance in the form of a WRFontDict pointer and horizontal and vertical point sizes.
		The horizontal and vertical point size are usually the same, unless there's a anisotropic scaling of the font.
		@param style the StyleRef that needs to be accessed
		@param h a WRFloat& where the implementation must store the horizontal point size
		@param v a WRFloat& where the implementation must store the vertical point size
		@return a WRFontDict*
	*/
	virtual WRFontDict*			GetFont(StyleRef style,WRFloat& h, WRFloat& v) = 0;

	/// Get the complementary font dict associated with a style
	/** 
		The client is expected to implement this method and return the complementary font instance in the form of a WRFontDict pointer and horizontal and vertical point sizes.
		The horizontal and vertical point size are usually the same, unless there's a anisotropic scaling of the font.
		If there's no complementary font defined, the implementation must return NULL.
		This method will only be called if the complementary font mechanism is activated, i.e. if the client didn't override the kWRAttrTag_UseComplementaryFont
		in the GetAttributeValue method to return false.
		@param style the StyleRef that needs to be accessed
		@param h a WRFloat& where the implementation must store the horizontal point size
		@param v a WRFloat& where the implementation must store the vertical point size
		@return a WRFontDict*
	*/
	virtual WRFontDict*			GetComplementaryFont(StyleRef style,WRFloat& h, WRFloat& v) = 0;

	/// Get the language associated with a style
	/** 
		The client is expected to implement this method and return a WRLanguageID. This language is used for various purposes such as selecting the right OpenType feature tree, ligature tables or the appropriate default digit set. 
		@param style the StyleRef that needs to be accessed
		@return a WRLanguageID*
	*/
	virtual WRLanguageID		GetLanguage(StyleRef style) = 0;

	virtual void		SetLanguage(StyleRef style, WRLanguageID lang) {
		WRUNUSED(style);
		WRUNUSED(lang);
	}  
	virtual int		EnableAutoScriptdetection() { return 0;}//returns value 0,1 or 2
	virtual WRInt32				GetFeatureCount(StyleRef style) = 0;
	virtual void				GetNthFeature(StyleRef style,WRInt32 i,WRInt32& tag, WRInt32& choice) = 0;

	virtual WRFloat				GetTracking(StyleRef style) = 0;

	virtual WRBool				CanTryOpenTypeKern(StyleRef style, WRFontDict* kernFontDict) = 0;
	virtual WRBool				GetPairKern(StyleRef style1, WRGlyphID32 glyph1, StyleRef style2, WRGlyphID32 glyph2, 
									bool rtl,
									WRFloat& xk, WRFloat& yk, WRFontDict* kernFontDict1, WRFontDict* kernFontDict2) = 0;

	virtual DiacPosPolicy		GetDiacPosPolicy(StyleRef style) = 0;
	virtual bool				IsSymetricSwappingEnabled(StyleRef ) { return true; }
	virtual WRDigitSet			GetDigitSubstitution(StyleRef style) = 0;
	virtual bool				AreLigaturesEnabled(StyleRef style) = 0;
	virtual bool				AreKashidasEnabled(StyleRef style) = 0;
	virtual WRCapitalizeMode	GetCapitalsMode(StyleRef style) = 0;
	virtual WRPositionMode		GetPositionMode(StyleRef style) = 0;
	virtual	void				GetDiacUserOffsets(StyleRef style, WRFloat& dx, WRFloat& dy) // [OBSOLETE] offsets for a 1000 pts size, like tracking 
								{ WRUNUSED(style); dx = dy = 0; }
	virtual SpecialProcessingType	ExceptionProcessing(StyleRef style, WRUnichar32 ch, WRGlyphID32& id, WRFloat& wd) = 0;
	virtual WRInt32				GetAutoText(StyleRef style, WRInt32 index, WRUnichar32* text, WRInt32 maxLen) = 0;
	virtual WRFloat				CalculateWidth(StyleRef style, WRInt32 index) = 0;
	virtual WRFloat				GetLeftEdgeOpticalAdjustment(StyleRef style, WRGlyphID32 gid) = 0;
	virtual WRFloat				GetRightEdgeOpticalAdjustment(StyleRef style, WRGlyphID32 gid) = 0;
	
	
	/// Get the character rotation associated with a style
	/** 
		The client can override this method to trigger a glyph spacing appropriate for the rotation angle.
		There's a default implementation for this attribute returning no rotation (0).
		@param style the StyleRef that needs to be accessed
		@return a float specifying the rotation in degrees, counterclockwise
	*/
	virtual WRFloat				GetCharacterRotation(StyleRef style ) { WRUNUSED(style); return 0.0; }

	/// Generic tag-based callback to get access to client attributes
	/**
		This method is a callback used by Optyca to retrieve attribute values from an opaque StyleRef.
		The implementation is expected to fill the data block and return the number of bytes written or to return 0, meaning there's a error condition or the tag is not supported by the client.
		If a value is not returned, Optyca will use a default behavior appropriate to the attribute nature.
		Usually, attributes use fixed size data, specified with the tag in WRAttributes.h ; 
		if the data is variable is length, Optyca will first call GetAttributeValue with a NULL data block pointer and expects the implementation to return the required length. It will call the method again after allocating the data block.
		@param owner a WRTag classification tag, which can be used in the client implementation to optimize the value lookup (#kWROwnerTag_Core, #kWROwnerTag_WRServices, #kWROwnerTag_ACE)
		@param attr a WRTag specifying the the requested attribute
		@param style a StyleRef that can be used by the client to return a style-dependent value for the attribute
		@param data a void* pointer to the data block to be filled with the attribute value
		@param len a long specifying the available length in byte of the data block pointed by \a data
		@return an long containing how many byte where written (0 means tag not implemented by the client)
		@sa WRAttributes.h
	*/
	virtual WRInt32				GetAttributeValue(WRTag owner, WRTag attr, StyleRef style, void* data, WRInt32 len) 
		{ 
			WRUNUSED(owner);
			WRUNUSED(attr);
			WRUNUSED(style);
			WRUNUSED(data);
			WRUNUSED(len);
			return 0; 
		}
	virtual	bool				RunBreak(OptycaStage stage, StyleRef styleA, StyleRef styleB) = 0;
	//Variable Fonts 
	virtual void GetDesignVector(StyleRef style, WRVector<WRFloat> &designVector) 
	{ 
		WRUNUSED(style);
		WRUNUSED(designVector);
	}

};

/// Output glyph run desscriptor
/** describes an output run, with a stylistic homogeneity
stylerefs are those given by the client as input
if the fSettings.complementary is not 0, the client must 
switch to a complementary font for drawing the run.
if the fSettings.complementary is < 0, the client must 
switch to the script fallback font (script = 1 - fSettings.complementary);
@see WRComplementaryIndex
*/

struct OptycaOutputRun
{
	WRCharOffset			fStart; /**< offset in the strike array */
	WRCharCount				fCount; /**< length in the strike array */
	OptycaRunSettings		fSettings;
	WRInt32					fSegmentIndex; /**< reserved */
};



/// interface to optyca shaper objects
/**
this class is the unit for communicating this the shaping algorithm
it has private buffers for everything, and may resize them dynamically.
usually, there's only a single instance of this class, reused for each
composition node

the analyzer assumes that the font is unique: cursivity is broken by
a font change. Multiple physical fonts for a single logical font must be
handled internally by the analyzer - to be investigated

On input, first set the input unicodes (SetUnicodes) - a copy is performed (is it really necessary or useful?)
Optyca::SetCodes allocates a run index array of the same size. If the shaping atom has multiple runs,
call CreateRun repeatedly with each run range (the style is not interpreted, it's just a client ref.
set the font with Optyca::SetFont (an internal cache will be maintained so that this operation will be 
fast)

on output:
@li the internal strike array may be copied or accessed with GetStrikes,GetNumStrikes
@li the substitution log can be either read (GetLog) or retrieved (RetrieveLog). In that last case the log mem block is detached from the log object and may be stored anywhere. Release it with free()
@li the resulting runs may be enumerated by GetFirstRun() and GetNextRun();
**/

class WRSERVICES_DECL IWROptyca : public WRClass
{
public:

	IWROptyca();
	virtual ~IWROptyca();

	//This method is used to choose the desired shaping engine, whether shaping to be done by Lipika or Harfbuzz.
	virtual void SetShapingEngine(ShapingEngine s) = 0;
	virtual void SetClientEncoding(ClientEncoding enc) = 0;
	virtual void SetEncodingMapUsed(bool) = 0;
	
	/*This method is used to set the scripts to be routed through traditional Lipika workflow.
	Use enum RoutingScripts
	{	kWRLatinOnly = 1,
		kWRIndicOnly = 2,
		kWRMENAOnly = 4,
	};
	For example: 
	In order to set ony Latin to route through Lipika pass kWRLatinOnly.
	In order to set Latin and Indic only to route through Lipika the client has to pass (kWRLatinOnly | kWRIndicOnly). This ensures that the text which contains only a combination of Indic and Latin scripts will pass through Lipika.
	*/
	virtual void SetRoutingScriptsForLipika(WRInt8 scripts) = 0;
	
	virtual void SetWritingDirection(WritingDirection dir) = 0;
	virtual ShapingEngine GetShapingEngine() = 0;
	virtual ClientEncoding GetClientEncoding() = 0;
	virtual bool GetEncodingMapUsed() = 0;
	/// Set the text to shape based on a UFT-16 array (without surrogates)
	/**
	  This method sets the input string by copying an array of UTF-16 without surrogates
	  It must be called first because it resets and  prepare many members
	  @param text a pointer to the first item of a WRUnichar16 array
	  @param len a WRInt32, the number of characters
	  @return a WRInt32, the error code in case of failure, kWRNoErr otherwise
	  @sa SetUnicodes(const WRUnichar32* text,WRInt32 len)
    */
	virtual WRInt32			SetUnicodes(const WRUnichar16* text,WRInt32 len) = 0;

	/// Set the text to shape based on a UFT-32 array
	/**
	  This method sets the input string by copying an array of UTF-32.
	  It must be called first because it resets and  prepare many members
	  @param text a pointer to the first item of a WRUnichar32 array
	  @param len a WRInt32, the number of characters
	  @return a WRInt32, the error code in case of failure, kWRNoErr otherwise
	  @sa SetUnicodes(const WRUnichar16* text,WRInt32 len)
    */
	virtual WRInt32			SetUnicodes(const WRUnichar32* text,WRInt32 len) = 0;

	/// Sets the main direction an optionally the levels
	/**
	  This method set the main shaping direction, an optionaly initialize the levels.
	  If levels is not NULL, it must point to an array of WRLevels, containing the same number
	  of element as the the input array (SetUnicode must have been called before)
	  @param mainDir a bool, pass true if the main direction is RTL, false otherwise
	  @param levels a pointer to the first item of a WRLevel array
	  @sa SetUnicodes(const WRUnichar16* text,WRInt32 len), SetUnicodes(const WRUnichar32* text,WRInt32 len),GetLevels()
    */
	virtual void		SetLevels(WRBool mainDir, const WREmbeddingLevel* levels) = 0;			// set the levels based on a client array
																									// levels may be null to set only the maindir
	typedef enum {
		kNoWordBreak	= 0,
		kWordBreak		= (1<<0),
		kLineBreak		= (1<<1),
		kJustifiedBreak	= (1<<2),
		kBreakAfter		= (1<<7) // internal
	} WRBreakProperty;

	/// Sets the linguistic word breaks
	/**
	  This method allows the client to optionally pass linguistic word breaks, i.e. work breaks 
	  those are not created by break characters (space).
	  Those word breaks will be used in the full justification process. At the present time,
	  the "desired" word spacing is NOT applied on linguistic breaks.
	  Calling this method is optional; if the client doesn't or calls with breaks = NULL, only the traditional break characters
	  will be honored.
	  @param breaks a pointer to the first item of a breaks array (one for each input character); length is implicitely the number of characters passed to SetUnicodes
	  @sa SetUnicodes(const WRUnichar16* text,WRInt32 len), SetUnicodes(const WRUnichar32* text,WRInt32 len),GetLevels()
	  @return a WRInt32, the error code in case of failure, kWRNoErr otherwise
    */
	virtual WRInt32			SetLinguisticWordBreaks(const WRUInt8*	breaks) = 0;			


	/// obsolete
	/**
	  Obsolete
	  @todo see if it can be removed from IWROptyca
    */
	virtual WRInt32			SetFont(WRFontDict* dict,WRFloat size) = 0;									// obsolete
	virtual void		SetStyleClientControl(OptycaStyleClientControl* styleClientControl) = 0;
	virtual OptycaStyleClientControl*	GetStyleClientControl() = 0;
	virtual void		SetFontContext(IWRFontContext* fontContext) = 0;
	virtual IWRFontContext*	GetFontContext( void ) = 0;
	
	virtual void			SetHarfbuzzFontAccess(IWRHarfbuzzFontAccess* harfbuzzFontAccess) = 0;
	virtual IWRHarfbuzzFontAccess*	GetHarfbuzzFontAccess(void) = 0;
	virtual void		CreateRun(StyleRef style, WRInt32 start,WRInt32 count) = 0;
	virtual void		AddOTFeature(WRInt32 tag, WRInt32 choice, WRInt32 start, WRInt32 count) = 0;

	virtual WRInt32			GetGlyphID(WRFontDict* dict,WRUnichar32 c, WRGlyphID32* glyphs, WRInt32 avail) = 0; // to get the gid of a single unicode
	virtual const char*	PeekAvailableFeatures(WRFontDict* dict,WRLanguageID langID,WRInt32& count) = 0;
	virtual void		SetJustification(WRJustificationPolicy policy, WRJustificationParams* params, WRFloat targetWidth) = 0;

	/// Set the string to be added at start of line (extra characters because hyphenation-related spelling change)
	/**
	Instruct Optyca to automatically add some characters at the beggining of the line, and to record it as a 1-n substitution.
	This is used to change the spelling in some complex hyphenation patterns (German, Hungarian)
	@param uc a const ref to a unicode array, not terminated, containing the extra characters
	@param len a WRInt32 containing the number of characters
	*/
	virtual WRInt32		SetStartOfLineHyphen(const WRUnichar32* uc,WRInt32 len) = 0; 

	/// Set the string to be added at end of line (extra characters because hyphenation-related spelling change, hyphen)
	/**
	Instruct Optyca to automatically add some characters at the end of the line, and to record it as a 1-n substitution.
	Usually, it's only an hyphen, but it can be more in case of spelling changes in some complex hyphenation patterns (German, Hungarian)
	@param uc a const ref to a unicode array, not terminated, containing the extra characters
	@param len a WRInt32 containing the number of characters
	*/
	virtual WRInt32		SetEndOfLineHyphen(const WRUnichar32* uc,WRInt32 len) = 0; 

	/// Set the auto tab stops
	/**
	  This method set the spacing between automatic tabs as well as their initial offset
	  The offset is usually 0 for normal lines, but for lines with a first indent, it's equal to -firstIdent
	  @param tabWidth a WRFloat, the spacing between two consecutive auto tab stop location, 0.0 meaning no auto tabs (default)
	  @param tabOffset a WRFloat, the offset (between - tabWith and 0) of the first tab (will be at tabWidth + tabOffset)
    */
	virtual void		SetAutoTabs(WRFloat tabWidth, WRFloat tabOffset) = 0;

	/// Add a tabulation stop 
	/**
	  This method adds a new tabulation stop of a given type at a given location.
	    tab stops are in logical order:
		in LTR main dir:
		- the x origin is at left and rightward
		- tabs are in the increasing order of x logical coord,ie from left to right
		- AlignAfterTab type means left and AlignBefore tab means right
		in RTL main dir:
		- the x origin is at right and leftward
		- tabs are in the increasing order of x logical coord,ie from right to left
		- AlignAfterTab type means right and AlignBefore tab means left
	  @param tabType a WRTabStopType (left, center, right, decimal)
	  @param tabPosition a WRFloat, the tab stop location
	  @param alignChar a WRUnichar32, the char to be aligned on the decimal tab (ignored for other tab types)
	  @param leader a pointer to a zero terminated WRUnichar32 string, to be used as a pattern for leader (no leader if NULL)
	  @todo use a list in this description
    */
	virtual void		AddTabStop(WRTabStopType tabType,WRFloat tabPosition, WRUnichar32 alignChar = 0, const WRUnichar32* leader = NULL) = 0;
	
	virtual bool		UsesComplementaryFont(WRFontDict* dict,WRFontDict* compdict,const WRUnichar32* codes, WRInt32 len, WRDigitSet ds, WRLanguageID langID, WRUnichar32 (*filter)(WRUnichar32)) = 0;

	// processing
	enum { 
		kComputeMarks = 1,					// usually not needed when breaking lines
		kForceMainDirForTrailing = 2, 
		kKernInfoOnNext = 4					// SLO used to put kern infor on next char, ID on previous
	};
	virtual WRInt32 DoShaping(WRInt32 flags) = 0;

	virtual IWRStrike* GetWRStrike(WRInt32 i) = 0;

	/// Returns the strike array 
	/**
	  This method returns a pointer to the strike array. Its length is returned by GetNumStrikes().
	  Call PrepareGlyphRuns() before to make sure that glyphs are in the right order. 
	  Before calling PrepareGlyphRuns(), glyphs are always in logical order.
	  @return a pointer to the first WRRealGlyphPoint of the array
	  @sa PrepareGlyphRuns(),GetNumStrikes(), GetDiacXOffsets(), GetDiacYOffsets(), GetGlyphWidths(), GetGlyphClasses()
    */
	virtual WRRealGlyphPoint*	CompatGetStrikes() = 0;

	/// Returns the strike array length 
	/**
	  This method returns the number of glyphs contained in the strike array. This is also the length
	  of the arrays return by GetDiacXOffsets(), GetDiacYOffsets(), GetGlyphWidths() and GetGlyphClasses()
	  @return a WRInt32
	  @sa GetDiacXOffsets(), GetDiacYOffsets(), GetGlyphWidths(), GetGlyphClasses()
    */
	virtual WRInt32			GetNumStrikes() = 0;

	/// Returns an array of mark horizontal offets 
	/**
	  This method returns an array of mark horizontal offets, to be added to glyph position
	  before drawing. Offsets are not merged by Optyca so that glyph positions are clean
	  for measuring and highlighting operations.
	  The array length is returned by GetNumStrikes().
	  Call PrepareGlyphRuns() before to make sure that offsets are in the right order.
	  Before calling PrepareGlyphRuns(),offsets are always in logical order.
	  @return a pointer to the first WRFloat offset of the array
	  @sa PrepareGlyphRuns(), GetStrikes(), GetNumStrikes(), GetDiacYOffsets(), GetGlyphWidths(), GetGlyphClasses()
    */
	virtual WRFloat*	CompatGetDiacXOffsets() = 0;

	/// Returns an array of mark horizontal offets 
	/**
	  This method returns an array of mark vertical offets, to be added to glyph position
	  before drawing. Offsets are not merged by Optyca so that glyph positions are clean
	  for measuring and highlighting operations.
	  The array length is returned by GetNumStrikes().
	  Call PrepareGlyphRuns() before to make sure that offsets are in the right order.
	  Before calling PrepareGlyphRuns(),offsets are always in logical order.
	  @return a pointer to the first WRFloat offset of the array
	  @sa PrepareGlyphRuns(), GetStrikes(), GetNumStrikes(), GetDiacXOffsets(), GetGlyphWidths(), GetGlyphClasses()
    */
	virtual WRFloat*	CompatGetDiacYOffsets() = 0;

	/// Returns an array of raw glyph widths
	/**
	  This method returns an array of raw glyph widths.These widths are the advances of glyphs coming
	  form the font, before letter spacing, tracking, kerning, justification are applied.
	  These raw advances are necessary to compute an offset to be added to xpositions before
	  drawing, so that RTL glyphs are drawn aligned with the right side of their advance cells, instead
	  of with the left side. 
	  The array length is returned by GetNumStrikes().
	  Call PrepareGlyphRuns() before to make sure that widths are in the right order.
	  Before calling PrepareGlyphRuns(), widths are always in logical order.
	  @return a pointer to the first WRFloat width of the array
	  @sa PrepareGlyphRuns(), GetStrikes(), GetNumStrikes(), GetDiacXOffsets(), GetDiacYOffsets(), GetGlyphClasses()
    */
	virtual WRFloat*	CompatGetGlyphWidths() = 0;

	/// Get pointer to the input unicode array
	/**
	  This method returns the pointer the the level array
	  As it's kept aligned with the strike array, don't expect it to be identical to
	  the one given in SetLevels (its length can be retrieved by calling GetNumStrikes())
	  @return a WRLevel pointer to the begining of the level array
	  @sa SetLevels(WRBool mainDir,const WREmbeddingLevel*	levels),GetNumStrikes()
    */
	virtual WREmbeddingLevel* CompatGetLevels() = 0;

	/// Returns a reference to the main substitution log 
	/**
	  This method returns a reference to the internal SubstitutionLog describing substititutions applied
	  to the inpt string. 
	  @return a reference to a SubstitutionLog
    */
	virtual SubstitutionLog&	GetLog() = 0;
	/// Returns a reference to the Harfbuzz mapping log 
	/**
	This method returns a reference to the internal mapping object containing input-output maping from Harfbuzz
	@return a reference to a InputOutputHB
	*/
	virtual InputOutputHB&	GetHarfbuzzMapping() = 0;

	/// Returns the total width of the output 
	/**
	  This method returns the total width of the output, including any trailing spaces (GetTrailingCount()).
	  @return a WRFloat
	  @sa GetTrailingWidth(), GetTrailingCount()
    */
	virtual WRFloat		CompatGetWidth() = 0;

	/// Returns the total width of the trailing spaces 
	/**
	  This method returns the total width of the trailing spaces (GetTrailingCount()). This width stays outside
	  the target width if Optyca was intstructed to ignore trailing spaces.
	  @return a WRFloat
	  @sa GetWidth(), GetTrailingCount()
    */
	virtual WRFloat		CompatGetTrailingWidth() = 0;

	/// Returns the number of trailing spaces 
	/**
	  This method returns the number of trailing spaces at the end of the input.
	  @return a WRInt32
	  @sa GetTrailingWidth()
    */
	virtual WRInt32			GetTrailingCount() = 0;

	/// Returns the maximum ascent 
	/**
	  This method returns the maximum (positive) ascent in the composed line 
	  @return a WRFloat
    */
	virtual WRFloat		GetAscent() = 0;

	/// Returns the maximum descent 
	/**
	  This method returns the maximum (positive) descent in the composed line 
	  @return a WRFloat
    */
	virtual WRFloat		GetDescent() = 0;

	/// Returns the maximum line leading 
	/**
	  This method returns the maximum (positive) line leading in the composed line 
	  @return a WRFloat
    */
	virtual WRFloat		GetLeading() = 0;

	/// Returns the advance of a glyph 
	/**
	  This method returns the advance for a glyph at a given index in the
	  strike array.
	  @param i a WRInt32 index of the glyph in the strike array
	  @return a WRFloat
    */
	virtual WRFloat		CompatGetAdvanceWidth(WRInt32 i) = 0;

	/// Obsolete 
	/**
	  Obsolete 
   */
	virtual WRJustifBadness	GetJustificationBadness() = 0;
	// output run iterator

	virtual void InitOutputRunEnum() = 0;
	enum {	kNOR_doGlyphReordering = 1,
			kNOR_breakOnScript = 2,
			kNOR_breakBeforeTab = 4,
			kNOR_checkCompatibility = 8, /// if set, compatible runs are merged; this is useful internally, but usually not externally
			kNOR_compatOnCursivityBreaker = 0x10, // else on ligature breaker by default
			kNOR_breakOnKerningChange = 0x20,
			kNOR_breakOnNullKerning = 0x40
	};

	virtual bool NextOutputRun(OptycaOutputRun& run,WRInt32 flags) = 0;
	virtual WRFloat GetGlyphScaling() = 0;
	virtual WRDSAlgorithm	GetBidiAlgorithm() const = 0;
	virtual void SetBidiAlgorithm(WRDSAlgorithm algo) = 0;

	// full internal reordering

	/// Initialize the reordered run iterator.
    /**
	  This method creates on internal list of reordered output runs. GetNumGlyphRuns() and GetGlyphRuns() can then be called to parse this list.
	  CAUTION: After PrepareGlyphRuns, the strike array referenced by GetStrikes() and the other parallel output arrays are reordered accordingly too.
      @param doReodering pass true if you want a graphical order and false for the logical order.
      @sa GetNumGlyphRuns(), GetGlyphRuns() and GetStrikes()
    */

	virtual void				PrepareGlyphRuns(bool doReodering) = 0;
	virtual void				PrepareGlyphRuns_HB(bool doReodering) = 0;

	/// Returns the count of output runs
	/**
	  This method returns the size of the internal list of reordered output runs. Therefore PrepareGlyphRuns() must have been called prioir to calling
	  this method.
	  @return a WRInt32, the run count
	  @sa PrepareGlyphRuns(), GetGlyphRuns()
    */

	virtual WRInt32					GetNumGlyphRuns() = 0;
		
	/// Returns a pointer to the reordered output run array
	/**
	  This method returns a pointer to the array of reordered runs. Therefore PrepareGlyphRuns() must have been called prioir to calling
	  this method.
	  @return an pointer to the first item of an OptycaOutputRun array
	  @sa PrepareGlyphRuns() and GetGlyphRuns()
    */
	virtual const OptycaOutputRun*		GetGlyphRuns() = 0; 

	/// get the main strike array
	/**
	This method return a pointer to the main strike array. It is mainly used by external modules.
	@return a IWRStrikeBuffer pointer
	**/
	virtual IWRStrikeBuffer*		GetStrikes() = 0;

	/// get the main char array
	/**
	This method return a pointer to the main character array. It is mainly used by external modules.
	@return a IWRCharBuffer pointer
	**/
	virtual IWRCharBuffer*			GetCharacters() = 0;

	/// get the main segment array
	/**
	This method returns a pointer to the main segment array. It is mainly used by external modules.
	@return a IWRSegmentBuffer pointer
	**/
	virtual IWRSegmentBuffer*		GetSegments() = 0;

	/// get the current run settings
	/**
	This method returns a pointer to the current run setting, as computed by the run iterators. It is mainly used by external modules.
	@return a OptycaRunSettings refernce  
	**/
	virtual OptycaRunSettings&		CurrentRunSettings() = 0;

	/// get the current horizontal size
	/**
	This method returns the horizontal font size for the current run, as computed by the run iterators. It doesn't include the scaling factor, if
	needed for superscript, subscript, etc.
	It is mainly used by external modules.
	@return a WRFloat  
	**/
	virtual WRFloat					CurrentHSize() = 0;

	/// get the current vertical size
	/**
	This method returns the vertical font size for the current run, as computed by the run iterators. It doesn't include the scaling factor, if
	needed for superscript, subscript, etc.
	It is mainly used by external modules.
	@return a WRFloat  
	**/
	virtual WRFloat					CurrentVSize() = 0;

	/// align indent for failed full justification
	/**
	When full justification is requested but cannot be achieved, the output width is less than the target width. Where the difference should go
	when rendering can be complex (RTL, tabs). This method return the amount that must be put on the left side.
	@return a WRFloat  
	**/
	virtual WRFloat		GetAlignIndent() = 0;

	virtual void enableVariableFonts(bool flag)=0;
	
#ifdef WINOPTYCA
public:
	void SetDoc(Trace* doc)		{ fTrace = doc; }
private:
	Trace* fTrace;
#endif
public:
	void SetNext(IWROptyca* next) { fNext = next; }
	IWROptyca* GetNext()			{ return fNext; }
protected:
	IWROptyca*						fNext;


	
};

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
