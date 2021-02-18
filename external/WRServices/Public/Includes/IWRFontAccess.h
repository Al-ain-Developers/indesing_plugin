//========================================================================================
//  
//  File: IWRFontAccess.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRFontAccess__
#define __IWRFontAccess__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRFontContextComponent.h"
#include "WRPath.h"
#include "WRString.h"
#include "IWRStrikeBuffer.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif
#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

WRInt32 FindKnownSuffix(const char* p, WRInt32 len);
char* SuffixSearch(char* str, const char* suffix);
bool isplain(const char *s); 

typedef struct  {
	WRInt32			codePage;			
	const char* 	codePageName;
	WRInt32			writingScript;
	WRUInt32		flags;
} WRCodePageInfo;

typedef enum { kGetOutlineInfo_MoveTo, kGetOutlineInfo_LineTo, kGetOutlineInfo_ConicTo, kGetOutlineInfo_CubicTo } GetOutlineInfoPointType;
typedef bool (*OutlinePointCB)(void* userData, GetOutlineInfoPointType t, WRFloat* coords);

class IWRFontContext;

/// An interface to access the client font manager
/** IWRFontAccess should be bound to the low level font library and has no default implementation. 
However, WRServices comes with helpers corresponding to the most common cases (Cooltype 4.5 and 5, FreeType).
The client is expected to create instances implmenting this interface and to pass the to IWRFontContext::Init()
The various font related objects are handled via pointer to opaque types (WRFontDict, WRFontInstance, ...). The implementation 
of IWRFontAccess is responsible for creating the actual objects and accessors. The pointer are passed to WRServices casted to pointer to opaque types,
and casted back to the real data in the accessors.
@sa CoolType5BasedFontAccess, CoolType5aBasedFontAccess, FreeType2otfBasedFontAccess, DummyFontAccess, CoolType4BasedFontAccess
**/

class WRSERVICES_DECL IWRFontAccess : public WRFontContextComponent
{
public:
	IWRFontAccess();
	virtual ~IWRFontAccess();

	/// Font instance creation
	/** The implemetation must return a pointer to an opaque object representing the 
		instance of the passed font at a specific size. 
	**/
	virtual	WRFontInstance*	WRCreateFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection) = 0;
	virtual void			WRDeleteFontInstance(WRFontInstance *inst) = 0;
	virtual WREncoding*		WRGetPreDefinedEncoding( WRInt32 whichEncoding ) = 0;

	/// Returns the glyph unhinted advance width
	/** returns the glyph advance, without any  hinting
		@param inst a pointer to a WRFontInstance, which must be with the final scaling matrix if hinting is expected
		@param glyphID the target WRGlyphID 
		@param width a pointer to a WRFloat where the result will be stored
	**/
	virtual void			WRGetGlyphWidth( WRFontInstance *inst, WRInt32 glyphID, WRFloat* width) = 0;

	/// Returns the glyph advance width, possibly hinted
	/** returns the glyph advance, with hinting depending on the antialias type 
		@li -1 : no hinting
		@li 0 : no antialias, bitmap hinting
		@li 1 : gray scale anti alias
		@li 2: color antialias
		the default implemetation calls the unhinted flavor of the WRGetGlyphWidth
		@param inst a pointer to a WRFontInstance, which must be with the final scaling matrix if hinting is expected
		@param glyphID the target WRGlyphID 
		@param width a pointer to a WRFloat where the result will be stored
		@param antiAliasType a WRInt32 describing the kind of antialias that will be performed when drawing
	**/
	virtual void			WRGetGlyphWidth( WRFontInstance *inst, WRInt32 glyphID, WRFloat* width, WRInt32  antiAliasType )
	{
		WRUNUSED(antiAliasType);
		WRGetGlyphWidth(inst,glyphID, width);
	}
	virtual void			WRGetGlyphBBox( WRFontInstance *inst, WRInt32 glyphID, WRFloatRect* bbox ) = 0;
	virtual void			WRGetICFBox( WRFontDict*, WRFloatRect *icfBox ); // implement it as CTGetVal(icfbox), never called if GetCharacterRotation always return 0
	
	virtual WRInt32			WRApplyFeatures(WRFontInstance *inst, IWRStrikeBuffer *strikes, WRInt32 startStrike, WRInt32 *numStrikes, WROTFeatureInfo *featureInfo, WRFloat* endPos) = 0;

	virtual WRInt32				WRGetGlyphIDs(	WRFontDict* aFont, const char* string, WRInt32 strLength,
											WREncoding* encoding, WRInt32 writingDirection,
											WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail ) = 0;

	// The client implementation must return kWRSomeBytesNotMappedErr when output value of *numStrikesAvail <= 0
	virtual WRInt32				WRGetGlyphIDsFromUCS4Bytes(	WRFontDict* aFont, const WRUnichar32* ucsString, WRInt32 ucsStrLength,
														WREncoding* encoding, WRInt32 writingDirection,
														WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail ) = 0;

	virtual char			WRTranslateGlyphID( WRTranslator* trans, WRGlyphID32 glyphID, WRByteChar* toString,
												WRInt32* toStrLen, WRInt32 matchPolicy ) = 0;
	virtual	WRInt32			WRGetGlyphClassValue(	WRFontDict *aFont,
													WRRealGlyphPoint *strikes,
													WRInt32 numStrikes,
													WROTGlyphClassValue* classValueArray) = 0;
	virtual	WRFamilyList*	WRGetFamilyList( ) = 0;
	virtual	void			WRReleaseFamilyList( WRFamilyList* famList) = 0;
	virtual	WRFamily*		WRGetNamedFamily(WRFamilyList* famList,const char* familyName); // there's a default impl
	virtual WRFontDict* 	WRGetIndexedFont( WRFamily* family, WRInt32 index ) = 0;
	virtual WRInt32  			WRGetNumFamilies(WRFamilyList*) = 0;
	virtual WRFamily*		WRGetIndexedFamily(WRFamilyList*, WRInt32 index ) = 0;
	virtual	void			WRReleaseFamily( WRFamily* family) = 0;
	virtual WRInt32			WRGetNumFontsInFamily( WRFamily* family ) = 0;
	virtual WRBool			WRGetFamilyName(WRFontDict *aFont, char* buffer, WRInt32 avail) = 0;
	virtual WRBool			WRGetFontName(WRFontDict *aFont, char* buffer, WRInt32 avail) = 0;
	virtual WRBool			WRGetFullName(WRFontDict *aFont, char* buffer, WRInt32 avail) = 0;
	virtual WRBool			WRGetStyleName(WRFontDict *aFont, char* buffer, WRInt32 avail) = 0;

	virtual WRScriptID		WRGetWritingScript(WRFontDict *aFont) = 0;
	virtual WRInternalTechnology WRGetTechnology(WRFontDict *aFont) = 0;
	virtual WRInt32				WRGetNumCodePages(WRFontDict *aFont) = 0;
	virtual WRCodePage		WRGetNthCodePage(WRFontDict *aFont, WRInt32 n) = 0;
	virtual WRGlyphID32		WRGetNotDefGlyphID(WRFontDict *aFont) = 0;
	virtual WRInt32			WRGetPairKern( WRFontInstance *inst, WRGlyphID32 first, WRGlyphID32 second, WRFloat *xKern );
	virtual WRBool			WROTHasFeature(WRFontDict *aFont,const char* tag, const char* script, const char* lang ) = 0;
	virtual	WRInt32			WROTAvailableFeatures(WRFontDict *dict, char* feature, char* featureList, WRInt32* countFeatures, const char* script, const char* lang) = 0;
	virtual void			WRGetHorizontalMetrics(WRFontDict *aFont,WRFloat& ascent, WRFloat& descent, WRFloat& lineGap) = 0;

#ifdef WR_WIN_ENV
	virtual WRBool			WRGetWindowsLOGFONTW(WRFontDict *aFont, WRPLOGFONTW lf) = 0;
#endif
	virtual WREncoding*		WRGetUnicodeEncoding();
	virtual WRTranslator*	WRNewTranslator( WRFontDict* aFont, WREncoding* toEncoding ) = 0;
	virtual void			WRDeleteTranslator( WRTranslator* trans ) = 0;
	virtual char			WRTranslateEncoding( WRTranslator* trans, const char* fromString,
												WRInt32* fromStrLength, WREncoding* fromEncoding,
												WRByteChar* toString, WRInt32* toStrLength, WRInt32* bytesWritten,
												WRInt32 matchPolicy ) = 0;
	virtual WREncoding*		WRNewEncoding( void ) = 0;
	virtual WREncoding*		WRNewPlatformEncoding( WRCodePage codePage ) = 0;
	virtual void			WRDeleteEncoding( WREncoding* encode ) = 0;
	virtual WRInt32			WRGetNumGlyphs(WRFontDict *aFont) = 0;
	virtual void			WRGetGlyphNames(WRFontDict *,char**,WRInt32 ); 		// Reimplement if WRCHECKMARKPOSITIONING is enabled

	virtual WRBool			WRHasGlyph(WRFontDict* font,WRUnichar32 uc);

	virtual WRInt32			WRGetNumPaths(WRFontDict* /* font */); // Reimplement if font utils are used
	virtual WRError			WRGetNthPath(WRFontDict* /* font */, WRInt32 /* i */, WRPath& /* path */); // Reimplement if font utils are used

	/// Serch for a font by postcriptname
	/** This method search for the font this the passed postscript name in the client's font list.
	Warning: The default implementation always returns NULL (not found). The method wasn't made abstract for API stability. However, it is required
	to perform a real search for the incremental build of the IWRFontInfo cache, if IWRFontContext::Invalidate() is called with rebuild=false
	@param name a const string containing the null-terminated postcript name
	@return a WRFontDict* or NULL if not found
	*/
	virtual WRFontDict*		WRSearchFont(const char* name);

	/// Serch for a font by family name and style name
	/** This method search for the font this the passed family ands style names in the client's font list.
	@param familyName a const string containing the null-terminated poscript name
	@param styleName a const string containing the null-terminated style name
	@param matchQuality a ref to a WRInt32 returning the quality of the matched font:
	@li 0 full match
	@li 1 style not found, the font is the regular style of the family 
	@li 2 style not found, the font is the first of the family (no regular style found)
	@li 3 reserved, not used
	@li 4 not found
	Warning: The default implementation always returns NULL (not found). The method wasn't made abstract for API stability. However, it is required
	to perform a real search for the incremental build of the IWRFontInfo cache, if IWRFontContext::Invalidate() is called with rebuild=false
	@return a WRFontDict* or NULL if not found
	*/
	virtual WRFontDict*		WRSearchFont(const char* familyName, const char* styleName, WRInt32& matchQuality);

	/// Check if the font list was changed
	/** This method returns true if there was a change since the previous call to the list of fonts associated to the font context 
	The client must call it regularly (on idle time) and call WRServicesFontContext()->Invalidate() if it returned true
	Warning: The default implementation always returns false (changes are not detected). The method wasn't made abstract for API stability.
	**/
	virtual bool			CheckFontList(void);

	/// Reset caches
	/** Reset any cache which could become invalid on font list change. Called by BuildFromFontContext.
	**/
	virtual void			Reset();

	/// Gets the font's units per em
	/**
	@param font a pointer to the WRFontDict
	@param unitsPerEm a ref to a WRUInt16 returning the number of units per Em of the font
	@return WRTrue if the font has units per Em or WRFalse if not (bitmap fonts or composite fonts)
	**/
	virtual WRBool			GetUnitsPerEm(WRFontDict* font, WRUInt16& unitsPerEm) = 0;

	virtual bool			GetFontVersion(WRFontDict *fntDict, WRUInt8 *versionStr, WRByteCount len) = 0;

	virtual	bool			GetOutlineInfo(void* userData, OutlinePointCB callBack, WRFontDict *fntDict, WRGlyphID32 glyphID) = 0;
	virtual	WRFontInstance*	WRCreateVariableFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection,int designVectorLength=0) = 0;

	virtual bool WRCheckTypeIFont(WRFontDict *aFont) = 0;
protected:
	IWRStrikeBuffer*			fTempStrikes;
	IWRStrikeBuffer*			GetTempStrikes(int sz);
};


class WRFontEnumerator
{
public:
	WRFontEnumerator(IWRFontAccess* access) : fAccess(access), fFamList(NULL), fFamily(NULL)
	{
		fFamList = fAccess->WRGetFamilyList();
		fFamCount = fAccess->WRGetNumFamilies(fFamList);
		fFamIndex = -1;
		fFontIndex = fFontCount = 0;
	}
	virtual ~WRFontEnumerator()
	{
		fAccess->WRReleaseFamilyList(fFamList);
		if (fFamily)
			fAccess->WRReleaseFamily(fFamily);
	}

	virtual WRFontDict* GetFirstOfNextFamily()
	{
		while (++fFamIndex < fFamCount)
		{
			ChangeFamily(fAccess->WRGetIndexedFamily(fFamList, fFamIndex));	
			if (++fFontIndex < fFontCount)
				return fAccess->WRGetIndexedFont(fFamily, fFontIndex);
		}
		ChangeFamily(NULL);
		return NULL;
	}

	virtual WRFontDict* GetNextFont()
	{
		if (++fFontIndex < fFontCount)
			return fAccess->WRGetIndexedFont(fFamily, fFontIndex);
		return GetFirstOfNextFamily();

	}
protected:
	void ChangeFamily(WRFamily* family)
	{
		if (fFamily)
		{
			fAccess->WRReleaseFamily(fFamily);
			fFamily = NULL;
		}
		fFamily = family;
		if (fFamily)
			fFontCount = fAccess->WRGetNumFontsInFamily(fFamily);
		fFontIndex = -1;
	}
	IWRFontAccess*	fAccess;
	WRFamilyList*	fFamList;
	WRFamily*		fFamily;
	WRInt32			fFamCount;
	WRInt32			fFamIndex;
	WRInt32			fFontCount;
	WRInt32			fFontIndex;
};


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
