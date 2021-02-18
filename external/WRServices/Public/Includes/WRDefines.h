//========================================================================================
//  
//  File: WRDefines.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef _WRDefines__
#define _WRDefines__

#include "WRConfig.h"
#include <stddef.h>
/* Note:
	1. This header is to be used by all clients and therefore must not contain any C++ only definitions
	2. The type definitiones are designed to make the nature of function parameters more clear. Please avoid using basic types (like short, long etc...)
*/

/* 	Platform specification 
 	Please define:
	WRWINDOWS 1
	or
	WRMACINTOSH 1
	tested with #if
	both must be defined
	
	Target specification
	Please define
	DEBUG 1 for debug target
	DEBUG 0 for non debug target
	
 */


#ifdef WR_MAC_ENV
#pragma options align=power
#endif

/* Boolean */
enum {
	WRFalse=0,
	WRTrue=1	
};

typedef char			WRBool;
typedef short			WRBool16;		

/* Anna like type, look at WRFixed.h and WRFloat.h for operators */
typedef char			WRInt8;
typedef unsigned char	WRUInt8;
typedef short			WRInt16;
typedef unsigned short	WRUInt16;
typedef int				WRInt32;
typedef unsigned int	WRUInt32;
typedef int				WRFixed;
typedef float			WRFloat;
	
#define kWRMAXInt8          ((WRInt8)0x7F)
#define kWRMINInt8          ((WRInt8)0x80)
#define kWRMAXInt16         ((WRInt16)0x7FFF)
#define kWRMINInt16         ((WRInt16)0x8000)
#define kWRMAXInt32         ((WRInt32)0x7FFFFFFF)
#define kWRMINInt32         ((WRInt32)0x80000000)

#define kWRMAXUInt8          ((WRUInt8)0xFF)
#define kWRMINUInt8          ((WRUInt8)0x00)
#define kWRMAXUInt16         ((WRUInt16)0xFFFF)
#define kWRMINUInt16         ((WRUInt16)0x0000)
#define kWRMAXUInt32         ((WRUInt32)0xFFFFFFFF)
#define kWRMINUInt32         ((WRUInt32)0x00000000)

#ifndef NULL
#define	NULL 0
#endif

#ifdef WR_WIN_ENV
typedef intptr_t WRIntPtr;
#else
typedef long WRIntPtr;
#endif

/* Character types */
typedef WRUInt8			WRUByteChar, 		*WRUByteCharPtr;
typedef WRInt8			WRByteChar, 		*WRByteCharPtr;
typedef WRUInt16		WRUnichar, 			*WRUnicharPtr;
typedef WRUInt16		WRUnichar16, 		*WRUnichar16Ptr;
typedef WRUInt32		WRUnichar32, 		*WRUnichar32Ptr;
//typedef unsigned short	WRGlyphID, 			*WRGlyphIDPtr;
//#define INVALIDGLYPHID ((WRGlyphID)0xFFFF)
typedef WRUInt16		WRGlyphID16, 		*WRGlyphID16Ptr;
#define INVALIDGLYPHID16 ((WRGlyphID16)0xFFFF)
typedef WRInt32			WRGlyphID32, 		*WRGlyphID32Ptr;
#define INVALIDGLYPHID32 ((WRGlyphID32)0xFFFFFFFF)

/* Counts and offsets of entities */
typedef WRInt32 		WRCount,			*WRCountPtr;
typedef	WRInt32 		WROffset,			*WROffsetPtr;

/* Counts and offsets for characters (both narrow and wide characters) */
typedef WRInt32 		WRCharCount,		*WRCharCountPtr;
typedef	WRInt32 		WRCharOffset,		*WRCharOffsetPtr;

/* short versiones of the above */
typedef WRInt16 		WRCharCountShort, 	*WRCharCountShortPtr;
typedef	WRInt16 		WRCharOffsetShort,	*WRCharOffsetShortPtr;

/* Counts and offsets of bytes */
typedef WRInt32 		WRByteCount,		*WRByteCountPtr;
typedef	WRInt32 		WRByteOffset,		*WRByteOffsetPtr;

/* String types */
typedef WRByteCharPtr 	WRByteCharCString;	/* null terminated byte string */
typedef WRUnicharPtr 	WRUnicharCString;	/* null terminated unicode string */
typedef WRUnichar32Ptr 	WRUnichar32CString;	/* null terminated unicode string */

typedef struct
{
	WRFloat			x;
	WRFloat			y;
} WRFloatPoint;

typedef struct
{
	WRFloat			left;
	WRFloat			top;
	WRFloat			right;
	WRFloat			bottom;
} WRFloatRect;
static int enable_lang_detect;  //variable to handle language detection rajeev
typedef struct
{
	WRFloat			a;
	WRFloat			b;
	WRFloat			c;
	WRFloat			d;
	WRFloat			e;
	WRFloat			f;
} WRFloatMatrix;

typedef struct
{
	WRFixed			a;
	WRFixed			b;
	WRFixed			c;
	WRFixed			d;
	WRFixed			e;
	WRFixed			f;
} WRFixedMatrix;

// CoolType like types
enum	{
	/** */
	kWRNoErr,
	/** */
	kWRInvalidMatrixErr,
	/** */
	kWRMatrixTooBigErr,
	/** */
	kWRInvalidGlyphIDErr,
	/** */
	kWRBadFontErr,
	/** */
	kWRMemErr,
	/** */
	kWRArrayTooShortErr,
	/** */
	kWRInvalidEncodingErr,
	/** */
	kWRInvalidTranslatorErr,
	/** */
	kWRSomeBytesNotMappedErr,
	/** */
	kWRSomeBytesMappedCloseErr,
	/** */
	kWRUnsupportedFeatureErr,
	/** */
	kWRInvalidFontTypeErr,
	/** */
	kWRValueProcessedErr,
	/** */
	kWRBrokenRedBlackNodeErr,
	/** */
	kWRPreInitializeCalledWithDifferntAllocatorsErr,
	/** */
	kWRPreInitializeNotCalledErr,
	/** */
	kWRInitializeCalledWithDifParamsErr,
	/** */
	kWRInitializeCalledWithSameParamsErr,
	/** */
	kWRTerminateAlreadyCalledErr,
	/** */
	kWRTerminateDelayedErr,
	/** */
	kWRPostTerminateTooEarlyErr,
	/** the input length exceeded the maximum allowed size */
	kWRInputTooLongErr,
	/** */
	kWRParamErr,

	/** */
	kWRCoolTypeError = 100
};

typedef enum {
	kWRLeftToRight,
	kWRTopToBottom
}WritingDirection;//in future can be updated to include kWRRightToLeft and kWRBottomToTop. Currently RTL is handled via fMainDir flag 

// CF kCT...Encoding in CoolType
enum	{
	kWRDefaultEncoding,
	kWRMacEncoding,
	kWRWinEncoding,
	kWRPlatformEncoding,
	kWRDefaultEncodingTTOverride,
	kWRMacEncodingTTOverride,
	kWRWinEncodingTTOverride,
	kWRPlatformEncodingTTOverride,
	kWRBEUnicodeEncoding,
	kWRLEUnicodeEncoding,
	kWRPDFEncoding,
	kWRPDFEncodingTTOverride,
	kWRBEUnicode3Encoding,
	kWRLEUnicode3Encoding
};

// CF kCT... in CoolType.h
#define	kWRAllowCloseMatch		1
#define kWRStopOnMissingChar	2
#define kWRStopOnArrayTooShort	4
#define	kWRAllowDecomposition	8
#define	kWRForceDecomposition	16
#define	kWRMapControlCodes		32
#define	kWRUseUnicodeAsPivot	64
#define	kWRUseAppleTranscodingSequences	128
#define	kWRUseAppleDeprecatedMappings	256
#define	kWRPreferDisplayableCharacter	512

/// Font dictionary
/** this opaque class is declared by not defined by WRServices. The client is responsible for
	defining what are really font dicts and how to access them. 
	Font dictionaries represent fonts not at a specific size, unlike font instances.
	It creates them and passes pointer to them, casted as WRFontDict*, to WRServices, which in turn will call
	back the client via the IWRFontAccess interface when it needs to do something with font dictionaries.
	Dynamic aspects: font dictionaries are created implicitely when searching for fonts in the client font context
	There is one and only one font dictionary object per installed font, and it's up to the IWRFontAccess implementation
	to release any associated memory when the implementation object is destroyed.
	@sa WRFontInstance
**/
class	WRFontDict;

/// Font instance
/** this opaque class is declared by not defined by WRServices. The client is responsible for
	defining what are really font instances and how to access them. Basically, a font instance 
	represent a typeface at a given size, with a given encoding to access the glyphs. It is used
	when working with strikes (positioned glyphs in WRRealGlyphPoint).
	The IWRFontAccess implementation creates them and passes pointer to them, casted as 
	WRFontInstance*, to WRServices, which in turn will call back the client via the IWRFontAccess 
	interface when it needs to do something with font instances.
	Font instances are explicitely created with IWRFontAccess::WRCreateFontInstance() and deleted 
	with IWRFontAccess::WRDeleteFontInstance().
	@sa WRRealGlyphPoint, WRFontDict, IWRFontAccess
**/
class	WRFontInstance;

/// Font encoding
/** this opaque class is declared by not defined by WRServices. The client is responsible for
	defining what are really font encodings and how to access them. Basically, a font encoding 
	represent a mapping between character codes and glyphIDs.
	The IWRFontAccess implementation creates them and passes pointer to them, casted as 
	WREncoding*, to WRServices, which in turn will call back the client via the IWRFontAccess 
	interface when it needs to do something with font encodings.
	Font encoding are explicitely created with IWRFontAccess::NewEncoding() or IWRFontAccess::WRNewPlatformEncoding() 
	and deleted with IWRFontAccess::WRDeleteEncoding().
	@sa WRFontInstance, IWRFontAccess
**/
class	WREncoding;
class	WRTranslator;

/// Font family 
/** this opaque class is declared by not defined by WRServices. The client is responsible for
	defining font family objects and how to access them, but they're basically
	collections of fonts with the same family name.
	The IWRFontAccess implementation creates them and passes pointer to them, casted as 
	WRFamily*, to WRServices, which in turn will call back the client via the IWRFontAccess 
	interface when it needs to do something with font families.
	Font family are got from a WRFamilyList with IWRFontAccess::WRGetNamedFamily() or IWRFontAccess::WRGetIndexedFamily() 
	or and released with IWRFontAccess::WRReleaseFamily().
	The implementation can either create distinct objects or share them with a ref counters.
	@sa IWRFontAccess, WRFamilyList
**/
class	WRFamily;

/// Font family list
/** this opaque class is declared by not defined by WRServices. The client is responsible for
	defining font family list objects and how to access them, but they're basically
	collections of font families.
	The IWRFontAccess implementation creates them and passes pointer to them, casted as 
	WRFamilyList*, to WRServices, which in turn will call back the client via the IWRFontAccess 
	interface when it needs to do something with font family lists.
	Font family are got with IWRFontAccess::WRGetFamilyList() and released with IWRFontAccess::WRReleaseFamilyList().
	The implementation can either create distinct objects or share a single one with a ref count.
	@sa IWRFontAccess, WRFamily
**/
class	WRFamilyList;


struct WRRealGlyphPoint 
{
       WRGlyphID32 glyphID;
       WRFloat xPosition;
       WRFloat yPosition;
};

/**
	Values for 'version' field of CTOTFeatureInfo

	<b>kCTOTFeature_v1</b>
	
	Use first six fields (up to and including 'changeAttribs') 
	of CTOTFeatureInfo.

	<b>kCTOTFeature_v2</b>
	
	Use all fields of CTOTFeatureInfo.

	@see _t_CTOTFeatureInfo CTOTFeature
*/

// MH 10/15/01: WROTFeatureGSUBProc added to WROTFeatureInfo (if kWROTFeature_v3)
typedef WRInt32 (WRCALLBACK *WROTFeatureGSUBProc)
    (
    void *clientCtx, WRInt32 currentStrikeIndex, WRInt32 flag, WRInt32 componentCount, WRInt32 termDiacCount
	);

// MH 04/11/2002: fix DoGPOSMarkToLigatureFormat1
typedef WRInt32 (WRCALLBACK *WROTFeatureGPOSProc)
    (
    void *clientCtx, WRInt32 currentMarkStrikeIndex, WRInt32* componentHolderIndex
	);

struct _t_WROTFeature_v3Info
	{
    /**
		Callback that is called once for each glyph substitution
	
		@see <a href="WRCALLBACKWROTFeatureGSUBProc.html">WROTFeatureGSUBProc</a>
	*/
    WROTFeatureGSUBProc featureGSUBCB;

	// MH 04/11/2002: fix DoGPOSMarkToLigatureFormat1
    /**
		Callback that is called during GPOS process, for each mark applied to a ligature, to get from the client:
			1/ The rank of the ligature component which holds the mark: componentHolderIndex
	
		@see <a href="WRCALLBACKCTOTFeatureGPOSProc.html">WROTFeatureGPOSProc</a>
	*/
	WROTFeatureGPOSProc	featureGPOSCB;

    /** Client context for callback. */
    void *clientCtx;

	/**
		To be used for future versions.
	*/
	void *otherParams;
	};

typedef struct _t_WROTFeature_v3Info WROTFeature_v3Info;

#define kWROTFeature_v1  1
#define kWROTFeature_v2  2

// MH 10/15/01: WROTFeatureGSUBProc added to WROTFeatureInfo (if kWROTFeature_v3)
#define kWROTFeature_v3  3

/**
	Values for 'flags' field of WROTFeatureInfo

	<b>kWRApplyGlyphSub</b>

	Apply 'GSUB' lookups for feature tags. Client
	must supply strikes array with glyph IDs.

	<b>kWRApplyGlyphPos</b>

	Apply 'GPOS' lookups for feature tags. Client
	must supply strikes array with glyph IDs. If
	kWRApplyGlyphSub unset, client must have set the
	strikes' positions (as well as endPenPos, if
	non-NULL), typically with WRGetGlyphLocations().

	<b>kWROTGSUBAndGPOS</b> (kWRApplyGlyphSub | kWRApplyGlyphPos)

	First apply 'GSUB' to strikes array, then
	internally apply WRGetGlyphLocations() to
	get strikes' positions, then apply 'GPOS'.
	Client must supply strikes array with glyph
	IDs, and set the xPosition and yPosition of
	the first strike to the desired starting pen
	position.

	At least one of kWRApplyGlyphSub and kWRApplyGlyphPos must be set.

	@see _t_WROTFeatureInfo WROTFeature WRGetGlyphLocations

	<b>kWRUseExtendedGPOSCallback</b>

	Reserved for CoolType font access only. Do not use in the client implementation.

*/
#define kWRApplyGlyphSub        (1<<0)
#define kWRApplyGlyphPos        (1<<1)
#define kWRApplyGlyphSubAndPos (kWRApplyGlyphSub | kWRApplyGlyphPos)
#define kWRReportOriginalIndices (1<<2)
#define kWRRtl                  (1<<3)
#define kWRXisRtl               (1<<4)
#define kWRUseExtendedGPOSCallback (1<<5)

/**
	Value for 'choiceIndexes' field of WROTFeatureInfo

	This value indicates the corresponding feature tag and
	feature range (if present) are to undergo Regular and not
	Alternate Layout.

	@see _t_WROTFeatureInfo WROTFeature
*/
#define kWROTNoChoiceIndex (-1)
#define kWROTDefaultIndex  (1)

/**
	Values for 'changeAttribs' field of WROTFeatureInfo

	<b>kWROTNoChange</b>

	Nothing changed.

	<b>kWROTSingleSubstitute</b>

	This glyph was changed to a different glyph.

	<b>kWROTMultiSubstitute</b>

	This glyph was changed to two or more glyphs.

	<b>kWROTAlternate</b>

	This glyph was changed to a different glyph,
	representing an alternate other than the first
	alternate from the original glyph's set of alternates.

	<b>kWROTLigature</b>

	This glyph was replaced by a ligature glyph; one
	or more glyphs after it were deleted.

	<b>kWROTDeleted</b>

	This glyph was deleted as it became part of a ligature
	or by some other means.

	<b>kWROTRepositioned</b>

	The corresponding strike's xPosition and/or yPosition
	has changed. This flag is used only if kWRApplyGlyphPos is
	set and kWRApplyGlyphSub is unset. (Clients must test for
	themselves whether the endPenPos has changed, since
	this does not correspond directly to a strike.)

	@see _t_WROTFeatureInfo WROTFeature
*/
#define kWROTNoChange         0
#define kWROTSingleSubstitute (1<<0)
#define kWROTMultiSubstitute  (1<<1)
#define kWROTAlternate        (1<<3)
#define kWROTLigature         (1<<4)
#define kWROTDeleted          (1<<5)
#define kWROTRepositioned     (1<<6)
#define kWROTMarkMoved		  (1<<7)
	
/**
	Contains information on applying features to the strikes array

	The fields after and including 'endPenPos' are not used when
	'version' is set to kWROTFeature_v1.

	@see WROTFeature
*/
struct _t_WROTFeatureInfo
	{
	/**
		For version control of this struct

		@see kWROTFeature_v1
	*/
	unsigned short version;

	/**
		How to apply the feature tags
	
		@see kWRApplyGlyphSub
	*/
	unsigned short flags;

	/**
		Array of 'numFeatures' feature tags

		These are 4-character feature tags, representing the
		feature(s) requested to be processed. For example:
		"kern", "swshkern". No NULL-termination is needed.
	*/
	const char *features;

	/**
		Number of feature tags passed in the 'features' array
	*/
	WRInt32 numFeatures;

	/**
		Array of numFeatures longs

		This field can be NULL.  If non-NULL then it indicates
		the alternate choice to be used for Alternate Layout.

		@see kWROTNoChoiceIndex
	*/
	WRInt32 *choiceIndexes;

	/**
		Array of flags

		This array of bytes  must be as long as 'numStrikes'
		if present. Set to NULL if functionality not needed.
		The array will be filled in with bitflags that will
		indicate what changes occurred in the *original* strike
		list. This may not match the resulting list but is
		intended to indicate what has changed to aid in cursor
		positioning, for instance.

		@see kWROTNoChange
	*/
	//WRUInt8 *changeAttribs;

	/**
		Ranges that each feature should be applied to
	
		Optional array of numFeatures*2 longs, representing the ranges within
		the strikes array that each feature should be applied to. See API
		documentation for further details.
	*/
	WRInt32 *featureRanges;

	/**
		4-character OpenType script tag
	
		If this field is NULL, then CoolType will choose an
		appropriate OpenType language system depending on the font's
		writingscript. If not NULL, then this field and the language
		field specify the OpenType language system of the strikes;
		in this case, a NULL language field denotes the default
		language system of the script.

		<b>Note:</b> CoolType currently doesn't provide an API that
		specifies language systems present in a font. Please request
		this of CoolType when you need language-specific functionality.
	*/
	const char *script;

	/**
		4-character OpenType language tag
	
		This is used only if the 'script' field is non-NULL.
		See the 'script' field's description.
	*/
	const char *language;

	/**
		To be used for future versions.
	*/
	// MH 10/15/01: WROTFeatureGSUBProc added to WROTFeatureInfo (if kWROTFeature_v3)
	WROTFeature_v3Info *otherParams;
//	void *otherParams;
	};

/**	Contains information on applying features to the strikes array */
typedef struct _t_WROTFeatureInfo WROTFeatureInfo;

/**
	Executes OpenType features on a strikes array

	OpenType layout features are identified by their 4-character tags, and
	include Ligatures ('liga'), Small Capitals ('smcp'), Traditional Forms
	('trad'), and Vertical Alternates and Rotation ('vrt2'). A feature may be
	comprised of glyph substitution lookups (specified in the font's 'GSUB'
	table), glyph positioning lookups (specified in the 'GPOS' table), or
	both. Use WROTAvailableFeatures() to determine the features present in a
	font.
	
	The order in which features are applied depends on the order of lookups
	in the 'GSUB' and 'GPOS' tables in the font, and not on the order in the
	features array of this API.
	
	If the version is set to kWROTFeature_v1, all features are applied to the
	entire strikes array. Only the first 6 fields in the WROTFeatureInfo
	struct are read.
	
	If the version is set to kWROTFeature_v2, a feature may be applied to one
	or more ranges within the strikes array; these sub-ranges may overlap.
	(Version 1 is provided for compatibility with previous clients; new
	clients are encouraged to use version 2 because of its enhanced
	functionality.)
	
	The featureRanges array, if non-NULL, must contain numFeatures*2
	elements. Each feature specified in the features array will correspond,
	in order, to a range in the featureRanges array. A range is represented
	by two consecutive longs: the starting and ending indexes, respectively,
	into the strikes array (which starts at index 0). A client need not bother
	"clamping" a range e.g. if there are 3 strikes, then the range -1 .. 4 will
	be regarded as 0 .. 2 by CoolType.
	
	The features, featureRanges, and choiceIndexes arrays work in parallel,
	forming numFeatures "triads" of feature tag, feature range, and choice
	index:

<pre>
Triad member:     Default, if corresponding array is NULL:
----------------- ----------------------------------------
feature tag       "Required" feature in the font
feature range     The entire strikes array
choice index      kWROTNoChoiceIndex
</pre>
	
	Two kinds of actions are possible for each "triad", depending on the
	choice index:
	
	<i>a. Regular Layout:</i>
	
	   This happens if the choice index is set to kWROTNoChoiceIndex (or no
	   choiceIndexes array is present).
	
	   The feature is applied to the specified range of strikes.
	   Substitutions and/or positionings such as ligatures and kerning may
	   occur. If a glyph has one or more alternates, the glyph will be
	   substituted by its first alternate. The strikes array may increase or
	   decrease in size.
	
	<i>b. Alternate Layout:</i>
	
	   This happens if the choice index is >= 0.
	
	   If 0, then nothing happens. If > 0, then the glyph is replaced by one
	   of its alternates, if it has any. The first alternate corresponds to
	   choice index 1, the second to choice index 2, and so on. Use
	   WROTNumberOfAlternates() to determine the number of alternates
	   available.
	
	The ordering of the elements in the 3 parallel arrays is irrelevant so
	long as the correct "triads" are formed.
	
	<b>Example 1:</b>
	
	   Apply the Ligature and Kerning features to the entire strikes array:
<pre>
version:        kWROTFeature_v2 (or kWROTFeature_v1)
numFeatures:    2
features:       'l','i','g','a',   'k','e','r','n'
featureRanges:  NULL
choiceIndexes:  NULL (i.e. Regular Layout)
</pre>	

	<b>Example 2:</b>
	
	   Apply the Ligature feature to strike ranges 3..5 and 6..8, and the
	   Small Capitals feature to ranges 0..5 and 7..9:
<pre>	
version:        kWROTFeature_v2
numFeatures:    3
features:       'l','i','g','a',   's','m','c','p',   's','m','c','p'
featureRanges:  3, 8,              0, 5,              7, 9
choiceIndexes:  NULL (i.e. Regular Layout)
</pre>	
	
	   Identical results would be produced if the 2 'liga' ranges weren't
	   consolidated into one.
	
	<b>Example 3:</b>

	  Here the Ligature feature is applied to strike range 0..2, and the All
	  Alternates feature is applied to the following 2 glyphs, selecting
	  their fifth and sixth alternates, respectively. Note that a separate
	  "triad" is required for each alternate in this case, since their choice
	  indexes are not the same:
<pre>	
version:        kWROTFeature_v2
numFeatures:    3
features:       'l','i','g','a',   'a','a','l','t',   'a','a','l','t'
featureRanges:  0, 2,              3, 3,              4, 4
choiceIndexes:  kWROTNoChoiceIndex 5                  6
</pre>	

	  The first triad undergoes Regular Layout; the others, Alternate Layout.

	@param inst				Pointer to a WRFontInstance created with
							WRCreateFontInstance().

	@param strikes			Pointer to an array of WRRealGlyphPoint's with
							numStrikes valid entries and numStrikesAvail
							available entries (to allow room for
							possible expansion with 'GSUB'). If
							expansion occurs, and the number of strikes
							needed is greater than numStrikesAvail, then
							the function will set numStrikesAvail to
							that number and return the
							kWRArrayTooShortErr error without processing
							further; the client can then re-size the
							array and call again. Note that
							kWRArrayTooShortErr may be returned several
							times for a particular API call. On
							successful return, the function will reset
							numStrikes to the actual valid number of
							strikes if this increases or decreases with
							'GSUB'.

	@param numStrikes		See description of strikes above. (May be
							reset by this function.)

	@param numStrikesAvail	See description of strikes above. (May be
							reset by this function.)

	@param mmDesignVector	Obsolete: Set to NULL

	@param featureInfo		A pointer to a structure containing
							information on applying features to the
							strikes array.

	@return kWRNoErr					- Success.

	@return kWRBadFontErr				- The given font is not a WRFontDict or
										  corrupted.

	@return kWRMemErr					- Internal out of memory error.

	@return kWRArrayTooShortErr			- Array not long enough. See description of
										  strikes below.

	@return kWRUnsupportedFeatureErr	- This font does not support this feature. No
										  error occurred, informational.

	@return kWRInvalidFontTypeErr		- This font cannot support features.

	@see WROTAvailableFeatures
*/


	/* 	Unicode directionality attribute
	Note: This is an enum, don't count on the numerical values and make sure that each value is unique
*/

enum {
	kWRdirMainDir=-1,			/* utility */
	kWRdirNULL=0,				/* Usefull as a sentinel (not part of the unicode standard	*/
	kWRdirL,					/* Left-to-Right, 					Strong 	*/
	kWRdirLRE,					/* Left-to-Right Embedding, 		Strong 	*/
	kWRdirLRO,					/* Left-to-Right Override,			Strong	*/
	kWRdirR,					/* Right-to-Left, 					Strong	*/
	kWRdirAL,					/* Right-to-Left Arabic,			Strong	*/
	kWRdirRLE,					/* Right-to-Left Embedding,			Strong	*/
	kWRdirRLO,					/* Right-to-Left Override,			Strong	*/
	kWRdirPDF,					/* Pop Directional Format,			Weak	*/
	kWRdirEN,					/* European Number,					Weak	*/
	kWRdirES,					/* European Number Seperator,		Weak	*/
	kWRdirET,					/* European Number Terminator,		Weak	*/
	kWRdirAN,					/* Arabic Number,					Weak	*/
	kWRdirCS,					/* Common Number Seperator,			Weak	*/
	kWRdirNSM,					/* Non-Spacing Mark,				Weak	*/
	kWRdirBN,					/* Boundary Neutral,				Weak	*/
	kWRdirB,					/* Paragraph Separator,				Neutral */
	kWRdirS,					/* Segment Separator,				Neutral */
	kWRdirWS,					/* Whitespace,						Neutral */
	kWRdirON,					/* Other Neutrals,					Neutral */
	/* following are special types for specific characters 				*/
	kWRdirNADS,				/* National Digit Shapes			U+206E  */
	kWRdirNODS,				/* Nominal Digit Shapes				U+206F  */
	/* following are WinSoft types for backward directionality non unicode algorithms	*/
	/* example:																			*/
	/*			kWRdirES_ET must be processed as kWRdirES by unicode algorithms			*/
	/*			kWRdirES_ET must be processed as kWRdirET by Winsoft algorithms			*/
	kWRdirES_ET,				/* Unicode ES:European Number Separator		Winsoft ET:European Number Terminator */
	kWRdirCS_ES,				/* Unicode CS:Common Number Separator		Winsoft ES:European Number Separator*/
	kWRdirBN_ON,				/* Unicode BN:Boundary Neutral				Winsoft ON:Other Neutrals	*/
	kWRdirCS_ON,				/* Unicode CS:Common Number Seperator		Winsoft ON:Other Neutrals	*/
	
	kWRdirNumOfDirectionalityTypes
} ;
typedef short WRUCSDirection;

enum {
	kWRErr_noError=0,
	kWRErr_bufferTooSmall=1,
	kWRErr_unknownCharacter=2,
	kWRErr_paramError=3,
	kWRErr_endOfFile=4,
	kWRErr_allocFailed = 5,
	kWRErr_tableTooShort = 6,
	kWRErr_tableNotFound = 7
};
typedef short	WRError;

enum {
	kWRcdmNone,			/* Character has no decomposition					*/
	kWRcdmCanonical,	/* default 											*/
	kWRcdmFont,			/* A font variant (e.g. a blackletter form)			*/
	kWRcdmNoBreak,		/* A no-break version of a space or hyphen			*/
	kWRcdmInitial,		/* An initial presentation form (Arabic)			*/
	kWRcdmMedial,		/* A medial presentation form (Arabic)				*/
	kWRcdmFinal,		/* A final presentation form (Arabic)				*/
	kWRcdmIsolated,		/* An isolated presentation form (Arabic)			*/
	kWRcdmCircle,		/* An encircled form								*/
	kWRcdmSuper,		/* A superscript form								*/
	kWRcdmSub,			/* A subscript form									*/
	kWRcdmVertical,		/* A vertical layout presentation form				*/
	kWRcdmWide,			/* A wide (or zenkaku) compatibility character		*/
	kWRcdmNarrow,		/* A narrow (or hankaku) compatibility character	*/
	kWRcdmSmall,		/* A small variant form (CNS compatibility)			*/
	kWRcdmSquare,		/* A CJK squared font variant						*/
	kWRcdmFraction,		/* A vulgar fraction form							*/
	kWRcdmCompat		/* Otherwise unspecified compatibility character	*/
};
typedef short WRCharacterDecompostionMapping;


/* Embedding level (Directionality) */
typedef unsigned char WREmbeddingLevel, *WREmbeddingLevelPtr;

/* Script codes */
/* Please keep this compatible with CoolType */
/* Follow the naming convention (kWRXXXScript) */
enum {
	kWRRomanScript=0,
	kWRJapaneseScript=1,
	kWRTraditionalChineseScript=2,
	kWRKoreanScript=3,
	kWRArabicScript=4,
	kWRHebrewScript=5,
	kWRGreekScript=6,
	kWRCyrillicScript=7,
	kWRRightLeftScript=8,
	kWRDevanagariScript=9,
	kWRGurmukhiScript=10,
	kWRGujaratiScript=11,
	kWROriyaScript=12,
	kWRBengaliScript=13,
	kWRTamilScript=14,
	kWRTeluguScript=15,
	kWRKannadaScript=16,
	kWRMalayalamScript=17,
	kWRSinhaleseScript=18,
	kWRBurmeseScript=19,
	kWRMyanmarScript=kWRBurmeseScript,
	kWRKhmerScript=20,
	kWRThaiScript=21,
	kWRLaotianScript=22,
	kWRGeorgianScript=23,
	kWRArmenianScript=24,
	kWRSimplifiedChineseScript=25,
	kWRTibetanScript=26,
	kWRMongolianScript=27,
	kWRGeezScript=28,
	kWRCentralEuropeanRomanScript=29,
	kWRVietnameseScript=30,
	kWRExtendedArabicScript=31,
	kWRKlingonScript=32,
	kWRIcelandicScript=79,
	kWRTurkishScript=81,
	kWRCroatianScript=82,
	kWRRomanianScript=83,
	kWRUkrainianScript=84,
	kWRBalticScript=85,
	kWRSyriacScript=86,
	kWRThaanaScript=87,
	kWRYiScript=88,
	kWRCherokeeScript=89,
	kWRLastScript=89,
	kWRDontKnowScript = -1,
	kWRRootScript = -2
};

typedef short WRScriptID;


/* 	CodePages
	Please keep the naming convention and numbering convention
	Naming Convention
	kWR<Script><Platform><extra>CodePage

	Numbering convention
	a. Windows codepage: use the codepage number
	b. Mac Script: use 10000 + script
	c. ISO: Use the numbers in the name (ISO8859-1 > 88591)
	d. kWRUTF8CodePage: must be used only by WRToUnicodeTranslator and WRFromUnicodeTranslator
*/

enum {
	kWRDontKnowCodePage=-1,
	// Arabic
	kWRArabicISO88596CodePage=88596,
	kWRArabicWindowsCodePage=1256,
	kWRArabicMacintoshCodePage=10004,
	kWRArabicDOSCodePage=864,
	kWRArabicASMOCodePage=708,
	kWRArabicASMOTranspCodePage=720,
	kWRArabicMacArabicXTCodePage=10100,
	kWRArabicWinArabicXTCodePage=10101,
	kWRArabicWindowsSimplifiedCodePage=10102,
	kWRArabicPhonyxCodePage=10103,

	// Cyrillic
	kWRCyrillicISO88595CodePage=88595,
	kWRCyrillicWindowsCodePage=1251,
	kWRCyrillicMacintoshCodePage=10007,
	kWRRussianDOSCodePage=866,
	kWRCyrillicKoi8CodePage=20866,
	// East European
	kWRCentralEuropeanWindowsCodePage=1250,
	kWRCentralEuropeanMacintoshCodePage=10029,
	kWRCentralEuropeanISO88592CodePage=88592,
	kWRSlavicDOSCodePage=852,
	// Greek
	kWRGreekISO88597CodePage=88597,
	kWRGreekWindowsCodePage=1253,
	kWRGreekMacintoshCodePage=10006,
	kWRGreekMacintoshCodePageSharedKeyboard=10200,
	// Hebrew
	kWRHebrewISO88598CodePage=88598,
	kWRHebrewISO88598VisualCodePage=885981,
	kWRHebrewWindowsCodePage=1255,
	kWRHebrewWindowsVisualCodePage=12551,
	kWRHebrewMacintoshCodePage=10005,
	kWRHebrewMacintoshVisualCodePage=100051,
	kWRHebrewDOSCodePage=862,
	// Roman
	kWRRomanISO88591CodePage=88591,
	kWRRomanASCIICodePage=20127,
	kWRRomanWindowsCodePage=1252,
	kWRRomanMacintoshCodePage=10000,
	kWRMultilingualDOSCodePage=850,
	// Turkish
	kWRTurkishISO88599CodePage=88599,
	kWRTurkishWindowsCodePage=1254,
	kWRTurkishMacintoshCodePage=10081,
	// Baltic
	kWRBalticISO88594CodePage=88594,
	kWRBalticISO885910CodePage=885910,
	kWRBalticISO885913CodePage=885913,
	kWRBalticISO885915CodePage=885915,
   	kWRBalticWindowsCodePage=1257,
	// Maltese
	kWRSouthEuropeISO88593CodePage = 88593,
	// Vietnamese
	kWRVietnameseWindowsCodePage=1258,
	// Romanian
	kWRRomanianMacintoshCodePage=10010,
	kWRRomanianISO885916CodePage=885916,
	// Ukrainian
	kWRUkrainianMacintoshCodePage=10017,
	kWRUkrainianKoi8CodePage=21866,
	// Icelandic
	kWRIcelandicMacintoshCodePage=10079,
	// Croatian
	kWRCroatianMacintoshCodePage=10082,
	// Thai
	kWRThaiWindowsCodePage=874,
	kWRThaiMacintoshCodePage=10021,
	// Japanese
	kWRJapaneseWindowsCodePage=932,
	kWRJapaneseMacintoshCodePage=10001,
	// Chinese
	kWRSimpChineseWindowsCodePage=936,
	kWRSimpChineseMacintoshCodePage=10025,
	kWRTradChineseWindowsCodePage=950,
	kWRTradChineseMacintoshCodePage=10002,
	// Korean
	kWRKoreanWindowsCodePage=949,
	kWRKoreanMacintoshCodePage=10003,
	// UTF 16
	kWRUTF16LittleEndianCodePage=1200,
	kWRUTF16BigEndianCodePage=1201,
	
	// UTF8
	kWRUTF8CodePage=65001
};

typedef WRInt32 WRCodePage;

enum {	kWRStandardTechnology,
		kWRArabicXTTechnology,
		kWRPhonyxTechnology,
		kWRLinotypeTechnology,
		kWRPseudoWithUnicodeTechnology,
		kWRPseudoNoUnicodeTechnology,
		kWRSimplifiedArabicTechnology,
		kWRWin31Technology,
		kWRUnknownTechnology 
};

typedef short WRAccessTechnology;

enum	{
	kWRType1Font,			/* a roman encoded, Adobe Type1 font					*/
	kWRTrueTypeFont,		/* a TrueType font										*/
	kWRCIDFont,				/* a CID-Keyed font										*/
	kWRBitmapFont,			/* a platform dependent font							*/
	kWRATCFont,				/* an Adobe Type Composer font (Rearranged CID font)	*/
	
	/* this constant can be passed to CTFindFont to locate
		named fonts when you don't care what the font
		technology is.  It is not a valid technology for
		a font to have. */
	kWRAnyTechnology = -1
};

typedef short WRInternalTechnology;


enum {	kWRUnknownPlatform,
		kWRWindowsPlatform,
		kWRMacintoshPlatform,
		kWRUnixPlatform
};

typedef short WRPlatform;

typedef WRInt32 WRWindowsCharset;

#ifdef WR_WIN_ENV
#define kWRRunningPlatform kWRWindowsPlatform
#elif defined(WR_UNIX_ENV)
#define kWRRunningPlatform kWRUnixPlatform
#else
#define kWRRunningPlatform kWRMacintoshPlatform
#endif

enum {
		kWRTextOriented,
		kWRGraphicsOriented,
		kWRClientTypeCount
};

typedef short WRClientType;

enum {
		kWRAreaCEEA,
		kWRAreaME,
		kWRAreaRCJK,
		kWRAreaCount
};

typedef short WRClientArea;


enum {
	/** */
	kWROTUnknownGlyphClassValue = 0,
	/** */
	kWROTBaseGlyphClassValue = 1,
	/** */
	kWROTLigatureGlyphClassValue = 2,
	/** */
	kWROTMarkGlyphClassValue = 3,
	/** */
	kWROTComponentGlyphClassValue = 4
};

typedef WRInt32 WROTGlyphClassValue;

inline WRBool IsMark(WROTGlyphClassValue cl ) { return ( cl == kWROTMarkGlyphClassValue ); }
inline WRBool IsLig(WROTGlyphClassValue cl ) { return ( cl == kWROTLigatureGlyphClassValue ); }


typedef unsigned short WRLanguageID;

// Masks for best encoding
#define MSK_CP_JAPANESE					0x0001
#define MSK_CP_SIMPLIFIED_CHINESE		0x0002
#define MSK_CP_KOREAN					0x0004
#define MSK_CP_TRADITIONAL_CHINESE		0x0008
#define MSK_CP_EAST_EUROPE				0x0010
#define MSK_CP_RUSSIAN					0x0020
#define MSK_CP_LATIN					0x0040
#define MSK_CP_GREEK					0x0080
#define MSK_CP_TURKISH					0x0100
#define MSK_CP_HEBREW					0x0200
#define MSK_CP_ARABIC					0x0400
#define MSK_CP_BALTIC					0x0800
#define MSK_CP_VIETNAMESE				0x1000
#define MSK_ASCII						0x1FFF
#define MSK_CP_CJK	(MSK_CP_JAPANESE|MSK_CP_SIMPLIFIED_CHINESE|MSK_CP_KOREAN|MSK_CP_TRADITIONAL_CHINESE)

#define MSK_CP_LATIN_MAC				0x0001
#define MSK_CP_ARABIC_MAC				0x0002
#define MSK_CP_HEBREW_MAC				0x0004
#define MSK_CP_GREEK_MAC				0x0008
#define MSK_CP_RUSSIAN_MAC				0x0010
#define MSK_CP_ROMANIAN_MAC				0x0020
#define MSK_CP_UKRAINIAN_MAC			0x0040
#define MSK_CP_EAST_EUROPE_MAC			0x0080
#define MSK_CP_ICELANDIC_MAC			0x0100
#define MSK_CP_TURKISH_MAC				0x0200
#define MSK_CP_CROATIAN_MAC				0x0400

/**	Memory allocation function provided in the WRMemObj */
typedef void*	(WRCALLBACK *WRMemAlloc)( size_t size, void* userData );

/**	Memory deallocation function provided in the CTMemObj */
typedef void	(WRCALLBACK *WRMemFree)( void* ptr, void* userData );

/**	Memory management object */
struct _t_WRMemObj {
	WRMemAlloc		alloc;
	WRMemFree		free;
	void*			userData;
};

typedef struct _t_WRMemObj WRMemObj;

typedef void*	WRHDC;
typedef void*	WRHKL;
typedef void*	WRPLOGFONT;
typedef void*	WRPLOGFONTW;

// Produces a long in the exact same order as the input tag
#ifdef WR_LITTLE_ENDIAN
#define WRTag2Long(t) ((WRInt32)( ((t)[0]) | (WRInt32)((t)[1])<<8 | (WRInt32)((t)[2])<<16 | (WRInt32)((t)[3])<<24 ))
#else
#define WRTag2Long(t) ((WRInt32)( ((t)[3]) | (WRInt32)((t)[2])<<8 | (WRInt32)((t)[1])<<16 | (WRInt32)((t)[0])<<24 ))
#endif

#define kWRAnyFeatureTag "****"

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif /* _WRDefines__ */
