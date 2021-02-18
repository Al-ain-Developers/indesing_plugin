//========================================================================================
//  
//  File: WRAttributes.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRAttributes__
#define __WRAttributes__

#include <vector>
#include "OptycaTypes.h"
#include "WROptycaRunSettings.h"
#include "WROptycaStage.h"

class IWRFontAccess;
//==========================================================================================
// WRAttrID
// generic attributes identifier 

typedef WRInt32 WRTag;

#define kWROwnerTag_WRServices WRInt32(0x57525320) /**< 'WRS ' WRServices private tag */
#define kWRAttrTag_DigitSet WRInt32(0x64696773)		/**< 'digs' (WRDigitSet) digit set attribute */
#define kWRAttrTag_Kashidas WRInt32(0x6B617368)		/**< 'kash' (bool) kashida on/off */
#define kWRAttrTag_Ligatures WRInt32(0x6C696773)		/**< 'ligs' (bool) ligature on/off */
#define kWRAttrTag_DiacVPos WRInt32(0x64767073)		/**< 'dvps' (DiacPosPolicy) mark positioning method */
#define kWRAttrTag_DirOverride WRInt32(0x646F7672)		/**< 'dovr' (int) local dir override */
#define kWRInvalidOffsetMagicNumber WRFloat(1.0e8f) ///< special return value for kWRAttrTag_MarkYDistFromBaseline and kWRAttrTag_MarkYOffset, used to encode the current mode and restrict the xoffset target accordingly
#define kWRAttrTag_MarkXOffset WRInt32(0x6D6B6478)		/**< 'mkdx' (WRFloat) mark x adjustment */
#define kWRAttrTag_MarkYOffset WRInt32(0x6D6B6479)		/**< 'mkdy' (WRFloat) mark y adjustment */
#define kWRAttrTag_MarkYDistFromBaseline WRInt32(0x6D6B7279)		/**< 'mkry' (WRFloat) mark y adjustment, positive values away from baseline, negative closer */
#define kWRAttrTag_SegmentXOffset WRInt32(0x73676478)		/**< 'sgdx' (WRFloat) segment x adjustment */
#define kWRAttrTag_SegmentYOffset WRInt32(0x73676479)		/**< 'sgdy' (WRFloat) segment y adjustment */
#define kWRAttrTag_ParagraphDir WRInt32(0x70646972)	/**< 'pdir' */
#define kWRAttrTag_JustifMethod WRInt32(0x6A73746D)	/**< 'jstm' */
#define kWRAttrTag_KashidaWidth WRInt32(0x6B736877)		/**< 'kshw' (WRFloat) stretching width, relative to the tatweel width (default = 2.0) */
#define kWRAttrTag_UseComplementaryFont WRInt32(0x636D7066) /**< 'cmpf' (bool) is the complementary font mechanism enabled? */
#define kWRAttrTag_UseScriptFallback WRInt32(0x73636662) /**< 'scfb' (bool) is the script fallback mechanism enabled? */ 
#define kWRAttrTag_IsDecimalPoint WRInt32(0x64656376)		/**< 'decp' (WRUnichar32) decimal point for a given script/lang (defined by the style) */

#define kWROwnerTag_All WRInt32(0x414C4C20) ///< 'ALL ' special tag, every responder will be called, no stop at the first answer

/// Record for the protocol used to control whether a script must be available 
/**
	This record describes the data exchanged with the kWRAttrTag_EnableScript query to IWRClientSettings.
	Each time a new script is encountered in the script server life, this query is sent to the client 
	The responder must check the current priority and if it's less or equal to its own priority, then it can
	set the enabled member. If it disable the script, a replacement script must be set in replaceBy (usually kWRUnknownScript).
	The default is to enable all scripts, default priority is 0. It is up the the client to define the priority assignment scheme,
	which can be very simple, as well as the kWRAttrTag_EnableScript implementation, if the enaling is permanently fixed.
	Plug-in-based applications can use this to make script support optional
*/

struct WRScriptEnablementRec
{
	WRScriptID	script; ///< target script
	short		priority;  ///< current priority, responders can't change anything is greater than their own priority 
	bool		enabled; ///< enabled or diabled ?
	WRScriptID	replaceBy; ///< replacement script, usually kWRUnknownScript 
};

#define kWRAttrTag_EnableScript WRInt32(0x656E6173) ///< 'enas' (WRScriptEnablementRec)

/// Record for the protocol used to control the font fallback mechanism 
/**
	This record describes the data exchanged with the kWRAttrTag_GlobalComplementaryFont and kWRAttrTag_GlobalScriptFallback
	queries to IWRClientSettings. This query is sent to the client when starting a shaping 
	The responder must check the current priority and if it's less or equal to its own priority, then it can
	set the enabling member. 
	The enabling can the either global (kWRFallbackEnabling_Disabled or kWRFallbackEnabling_Enabled) or style-based (kWRFallbackEnabling_ByStyle).
	In this last case, the StyleClientControl::GetAttribute will be called (kWRAttrTag_UseComplementaryFont and kWRAttrTag_UseScriptFallback)
	to get the actual enabling.
	The default is to globally enable the complementary font and to globally disbale the by-script fallback
*/

enum { 
	kWRFallbackEnabling_Unknown = -1, ///< WRFallbackEnablementRec, unknow status
	kWRFallbackEnabling_Disabled = 0, ///< WRFallbackEnablementRec, method is disabled
	kWRFallbackEnabling_Enabled = 1, ///< WRFallbackEnablementRec, method is enabled
	kWRFallbackEnabling_ByStyle = 2 ///< WRFallbackEnablementRec, finer grain setting  @sa kWRAttrTag_UseComplementaryFont, kWRAttrTag_UseScriptFallback
};

struct WRFallbackEnablementRec
{
	short		priority; ///< current priority, responders can't change anything is greater than their own priority 
	short		enabling; ///< -1: unknown 0 : no 1 : yes 2: by style
};

#define kWRAttrTag_GlobalComplementaryFont WRInt32(0x67637066) ///< 'gcpf' (WRFallbackEnablementRec) is the complementary font mechanism enabled? 
#define kWRAttrTag_GlobalScriptFallback WRInt32(0x67736662) ///< 'gsfb' (WRFallbackEnablementRec) is the script fallback mechanism enabled?

#define kWROwnerTag_WRServicesExtensions WRInt32(0x57525345) ///< 'WRSE' WRServices extension private tag 
#define kWRAttrTag_NextExtension WRInt32(0x6E787465) ///< 'nxte' (WRExtensionQuery) get new extension instance
#define kWRAttrTag_ReleaseExtension  WRInt32(0x726C7365) ///< 'rlse' (WRExtensionQuery) release extension instance data

typedef int (*WRExtensionCB) (void* extData, WRTag selector, void* data);

class IWRCharBuffer;
class IWRStrikeBuffer;
class IWRSegmentBuffer;
class SubstitutionLog;
class OptycaStyleClientControl;
class IWRFont;
class IWROptyca;
class IWRSegment;

struct WRExtensionQuery
{
	short			vers; ///< record version current = 1
	void*			enumData; ///< client private enum data, NULL on first input, NULL on output when iteration is over (must be freed by the client)
	WRExtensionCB	callback;
	void*			extData; ///< extension private data (must be allocated and freed by the client)
};

#define kWRExtSelector_GetFontType WRInt32(0x67667474) ///< 'gftt' (WREGetFontTypeQuery) compute the type of a font

enum WREFontType { WREFontType_DontKnow, WREFontType_Default, WREFontType_Font, WREFontType_FontUC,  WREFontType_FontOT };

struct WREGetFontTypeQuery
{
	short			vers;					///< (in) record version current = 1
	WRFontDict*		dict;					///< (in), font we're interested in
	WRFloat			priority;				///< (in/out), to artibrate between multiple answers; 0 means couldn't answer (other output members are invalid), the highest value wins
	WREFontType		type;					///< (out), class to use for internal support
	WRScriptID		script;					///< (out) main script of the font or kWRDontKnowScript
	bool			hasGlyphlets;			///< (out) true if the font has sub character glyphs
	bool			hasCustomSpaceWidth;	///< (out) true if the font technology use computed space width (like ACE)
};

/// When receiving this selector, the extension is allowed to create any private data to be stored in the extension attribute list of the font
#define kWRExtSelector_PrepareFont WRInt32(0x70737066) ///< 'prpf' (WREPrepareFontQuery) to set font attributes

struct WREPrepareFontQuery
{
	short			vers; ///< (in) record version current = 1
	IWRFont*		font; ///< (in) font to prepare
};


/// classify a glyph or a character
#define kWRExtSelector_ClassifyGlyph WRInt32(0x636C7366) ///< 'clsf' (WREClassifyGlyphQuery) compute the type of char/glyph

struct WREClassifyGlyphQuery
{
	short			vers;		///< (in) record version current = 1
	IWRFont*		font;		///< (in), font we're interested in
	WRUnichar32		unicode;	///< (in) or 0 if unknown
	WRGlyphID32		gid;		///< (in) or INVALIDGLYPHID32 if unknown
	WRFloat			priority;	///< (out)  to artibrate between multiple answers; 0 means couldn't answer (other output members are invalid), the highest value wins
	WRGlyphClass	cl;			///< (out) glyph class
};

// check script support
#define kWRExtSelector_DictScriptSupport WRInt32(0x64737370) ///< 'dssp' (WREDictScriptSupportQuery) 
#define kWRExtSelector_FontScriptSupport WRInt32(0x66737370) ///< 'fssp' (WREFontScriptSupportQuery)

struct WREDictScriptSupportQuery
{
	short			vers;		///< (in)record version current = 1
	WRFontDict*		dict;		///< (in) font we're interested in
	WRScriptID		script;		///< (in) script to check
	WRFloat			priority;	///< (out)  to artibrate between multiple answers; 0 means couldn't answer (other output members are invalid), the highest value wins
	bool			support;	///< (out) is the script supported
};

struct WREFontScriptSupportQuery
{
	short			vers;		///< (in)record version current = 1
	IWRFont*		font;		///< (in) font we're interested in
	WRScriptID		script;		///< (in) script to check
	WRFloat			priority;	///< (out) to artibrate between multiple answers; 0 means couldn't answer (other output members are invalid), the highest value wins
	bool			support;	///< (out) is the script supported?
};

#define kWRExtSelector_HasGlyphlets WRInt32(0x68676c74) ///< 'hglt' (WREHasGlyphletsQuery)

struct WREHasGlyphletsQuery
{
	short			vers;			///< (in) record version current = 1
	WRFontDict*		dict;			///< (in) font we're interested in
	WRFloat			priority;		///< (out) to artibrate between multiple answers; 0 means couldn't answer (other output members are invalid), the highest value wins
	bool			hasGlyphlets;	///< (out) does the font use glyphlets?
};

#define kWRExtSelector_RunBreak WRInt32(0x7262726b) ///< 'rbrk' (WRERunBreakQuery) is there a need for a run break for at least one of the remaining steps

struct WRERunBreakQuery
{
	short			vers;		///< (in) record version current = 1
	IWROptyca*		shaper;		///< (in) current shaper object
	OptycaStage		stage;		///< (in) current stage
	StyleRef		style1;		///< (in) style before
	StyleRef		style2;		///< (in) style after
	bool			runBreak;	///< (out) is there a run break?
};


#define kWRExtSelector_Eval WRInt32(0x657616C) ///< 'eval' (WREEvalQuery) evaluate the module capabilities regarging the shaping of a chunck

enum WREShapingEval { 
	WREShapingEval_None,	///< cannot handle
	WREShapingEval_Basic,	///< provides a minimal basic support
	WREShapingEval_Advanced ///< can take full advantage of the font on this run
};

struct WREEvalQuery
{
	short				vers;		///< (in)record version current = 1
	IWROptyca*			shaper;		///< (in) current shaper object
	IWRFont*			font;		///< (in) current font
	WRInt32				start;		///< (in) if cannot handle, set to the next call point
	WRInt32				end;		///< (in) max extent of the run / (out) supported extent of the run
	WRInt32				nextCall;	///< (out) character index for next call if not handled
	WRFloat				priority;	///< (out)  to artibrate between multiple answers; 0 means "cannot handle" (other output members are invalid), the highest value wins
	WREShapingEval		rating;		///< (out)  the level of support provided by the module
};

#define kWRExtSelector_Shape WRInt32(0x7368170) ///< 'shap' (WREShapingQuery) evaluate the module capabilities regarging the shaping of a chunck
struct WREShapingQuery
{
	short				vers;	///< (in) record version current = 1
	IWROptyca*			shaper; ///< (in) current shaper object
	IWRFont*			font;	///< (in) current font
	WRFloat				hSize;	///< (in) actual horizontal font size
	WRFloat				vSize;	///< (in) actual vertical font size
	WRInt32				segIndex;	///< (in) segment index if reshaping, otherwise -1
	WRInt32				start;  ///< (in) run start
	WRInt32				end;	///< (in) run end
};

#define kWRExtSelector_SpaceWidth WRInt32(0x73707764) ///< 'spwd' (WRESpaceWidthQuery) get the space width, in case it is custom in the technology
struct WRESpaceWidthQuery
{
	short				vers;		///< (in) record version current = 1
	IWROptyca*			shaper;		///< (in) current shaper object
	StyleRef			style;		///< (in) current style
	IWRFont*			font;		///< (in) current font
	WRFloat				hSize;		///< (in) actual horizontal font size
	WRFloat				priority;	///< (out) to artibrate between multiple answers; 0 means "cannot handle" (other output members are invalid), the highest value wins
	WRFloat				width;		///< (out) computed space width
};

// not used sofar
#define kWRExtSelector_ClassifyChar WRInt32(0x636C7363) ///< 'clsc' (WREClassifyCharQuery) opportunity to tweak the unicode properties
struct WREClassifyCharQuery
{
	short				vers;		///< (in)	record version current = 1
	WRFloat				priority;	///< (out)	to artibrate between multiple answers; 0 means "cannot handle" (other output members are invalid), the highest value wins
	WRUnichar32			unicode;	///< (in)	unicode to classify
	WRScriptID			script;		///< (out)	script
	WRUCSDirection		dir;		///< (out)	direction class
};

#if defined(WR_WIN_ENV) && defined(_DEBUG)
#define kWRExtSelector_GetProfile WRInt32(0x70726F66) ///< 'prof' (WREGetProfileQuery) debug feature to display glyph profiles
struct WREGetProfileQuery
{
	short				vers;
	IWRFontAccess*		access;
	WRFontDict*			dict;
	WRUInt32			glyphID;
	WRUInt32			angle;
	std::vector<WRInt32>* vectX;
	std::vector<WRInt32>* vectY;
};
#endif // WR_WIN_ENV && _DEBUG

#define kWRExtSelector_GetPositioningField WRInt32(0x70666C64) ///< 'pfld' (WREGetPositioningFieldQuery) debug feature to display dot positioning field
struct WREGetPositioningFieldQuery
{
	short				vers;
	int					fontSize;
	void*				field;
};

#define kWRExtSelector_InvalidateCache WRInt32(0x696E766C) /// < 'invl' (WREInvalidateCacheQuery) indicates that the font cache needs to be invalidated
struct WREInvalidateCacheQuery
{
	short vers;
};

#define kWROwnerTag_ACE WRInt32(0x41434520) ///< 'ACE '
#define kWRAttrTag_InternalKerningHor WRInt32(0x696E6B68) ///< 'inkh'
#define kWRAttrTag_InternalKerningVer WRInt32(0x696E6B76) ///< 'inkv'
#define kWRAttrTag_ExternalKerningHor WRInt32(0x65786B68) ///< 'exkh'
#define kWRAttrTag_ExternalKerningVer WRInt32(0x65786B76) ///< 'exkv'

#define kWRAttrTag_Mimicry  WRInt32(0x6D696D63) ///< 'mimc'
#define kWRAttrTag_DotRotation  WRInt32(0x646F7472) ///< 'dotr'
#define kWRAttrTag_Swash  WRInt32(0x73777368) ///< 'swsh'
#define kWRAttrTag_Keshideh  WRInt32(0x6B657368) ///< 'kesh'
#define kWRAttrTag_Stylistic  WRInt32(0x73616C74) ///< 'salt'
#define kWRAttrTag_PackedVariation  WRInt32(0x70766172) ///< 'pvar'
#define kWRAttrTag_Hamza  WRInt32(0x68616D7A) ///< 'hamz'


#define kWRAttrTag_EndOfAyahDigitScaling WRInt32(0x656F6164) ///< 'eoad'
#define kWRAttrTag_EndOfAyahLeftSidebearing WRInt32(0x656F616C) ///< 'eoal'
#define kWRAttrTag_EndOfAyahRightSidebearing WRInt32(0x656F6172) ///< 'eoar'
#define kWRAttrTag_EndOfAyahHasCustomRing WRInt32(0x656F6173) ///< 'eoas'
#define kWRAttrTag_EOAStyleRingCapacity WRInt32(0x656F6163) ///< 'eoac'
#define kWRAttrTag_EOAStyleOuterRect WRInt32(0x65616F72) ///< 'eaor'
#define kWRAttrTag_EOAStyleInnerRect WRInt32(0x656F6972) ///< 'eair'
#define kWRAttrTag_GetFunctionPointers WRInt32(0x66756E63) ///< 'func'

#define kWROwnerTag_Core WRInt32(0x434F5245) ///< 'CORE'
#define kWRAttrTag_KerningAfter  WRInt32(0x6B65726E) ///< 'kern' data is a WRFloat, containing the advance adjustment for a 1 pt size.
#define kWRAutoKernMagicNumber WRFloat(1.0e8f) ///< special return value for kWRAttrTag_KerningAfter, meaning automatic kerning
#define kWRAttrTag_ExtraKerning  WRInt32(0x786B726E) ///< 'xkrn' data is a WRFloat, containing the advance adjustment for a 1 pt size, to be added to automatic kerning.

/// 'sbsh' (float) GetAttributeValue tag override the default (0.33) shift factor for subscript
/**
	The default downward shift for optyca subscript fauxing is 0.33 * nominal point size.
	The client can override this by answering to this tag in the GetAttribute implementation. The override can be based on the StyleRef or
	can be an higher level parameter
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_SubscriptShift  WRInt32(0x73627368)

/// 'spsh' (float) GetAttributeValue tag override the default (0.33) shift factor for superscript
/**
	The default upward shift for optyca superscript fauxing is 0.33 * nominal point size.
	The client can override this by answering to this tag in the GetAttribute implementation. The override can be based on the StyleRef or
	can be an higher level parameter
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_SuperscriptShift  WRInt32(0x73707368)

/// 'sbfc' (float) GetAttributeValue tag override the default (0.583) scale factor for subscript
/**
	The default point size for optyca subscript fauxing is 0.583 * nominal point size.
	The client can override this by answering to this tag in the GetAttribute implementation. The override can be based on the StyleRef or
	can be an higher level parameter
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_SubscriptScale  WRInt32(0x73626663)

/// 'spfc' (float) GetAttributeValue tag override the default (0.583) scale factor for superscript
/**
	The default point size for optyca superscript fauxing is 0.583 * nominal point size.
	The client can override this by answering to this tag in the GetAttribute implementation. The override can be based on the StyleRef or
	can be an higher level parameter
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_SuperscriptScale  WRInt32(0x73706663)

/// 'spfc' (float) GetAttributeValue tag override the default (0.7) scale factor for smallcaps
/**
	The default point size for optyca smallcaps fauxing is 0.7 * nominal point size.
	The client can override this by answering to this tag in the GetAttribute implementation. The override can be based on the StyleRef or
	can be an higher level parameter
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_SmallCapScale  WRInt32(0x73636663)

/// 'alis' (WRInt32) GetAttributeValue tag, antialiasing setting for hinting
/**
	The default is -1, meaning no hinting. Is hinting is wanted, pass the antialiasing type (client dependent, will be passed back in 
	IWRFontAccess::GetGlyphWith, the value is not interpreted elsewhere, except for negativity)
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_AntiAliasing WRInt32(0x616C6973) /**< 'alis' (WRInt32) anti alialing type for hinting (-1 for no hintig) */

/// 'blmh' (WRUnichar32) GetAttributeValue tag, character to be used as a base for baseless marks
/**
	This is a paragraph-wide attribute. The default is 0 (no character). Space can  be used, but kWRUnichar_DottedCircle = 0x25CC is the one recommended by Unicode (if not in the font, Optyca will fall back on space). 
	@sa OptycaStyleClientControl::GetAttributeValue
*/
#define kWRAttrTag_BaselessMarkHandling WRInt32(0x626C6D68) ///< 'blmh' data is an int32, describing what character to use as a surrogate base for baseless marks.

#define kWRAttrTag_MaxPositioningSteps WRInt32(0x6D777073) /**< 'mxps' (WRInt32) reserved */

#endif // __WRAttributes__
