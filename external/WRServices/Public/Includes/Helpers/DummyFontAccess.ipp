#include "DummyFontAccess.h"
#include "WRDefines.h"
#include "WRUnicodeDatabase.h"

#define kWRDFAMagicValue		1

WRFontInstance*	DummyFontAccess::WRCreateFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection)
{
	//make sure to return non-null
	return (WRFontInstance*) kWRDFAMagicValue; 
} 

void DummyFontAccess::WRDeleteFontInstance(WRFontInstance *inst)
{
	//nothing
}

WREncoding*	DummyFontAccess::WRGetPreDefinedEncoding( WRInt32 whichEncoding )
{
	// We are supposed to work only with unicode encoding
#ifdef WR_LITTLE_ENDIAN
		if (whichEncoding == kWRLEUnicodeEncoding || whichEncoding == kWRLEUnicode3Encoding)
#endif
#ifdef WR_BIG_ENDIAN
		if (whichEncoding == kWRBEUnicodeEncoding || whichEncoding == kWRBEUnicode3Encoding)
#endif
			return (WREncoding*) kWRDFAMagicValue;
		else
			return NULL;
}

void DummyFontAccess::WRGetGlyphWidth( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloat* width )
{	
	InternalGet1GlyphMetrics(glyphID, width, NULL);
}

void DummyFontAccess::WRGetGlyphBBox( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloatRect* bbox )
{
	WRFloat ascent, descent, lineGap;
	WRFloat xWidth;
	
	WRGetGlyphWidth(inst, glyphID, &xWidth);
	
	WRGetHorizontalMetrics(NULL, ascent, descent, lineGap);
	// left is 0
	bbox->left = 0.0;
	// top is ascent of the font
	bbox->top = ascent;
	// right is xWidth
	bbox->right = xWidth;
	// bottom is descent of the font
	bbox->bottom = descent;
}

WRInt32 DummyFontAccess::WRApplyFeatures(WRFontInstance *inst, WRRealGlyphPoint *strikes, WRInt32 *numStrikes, WRInt32 *numStrikesAvail,
										WROTFeatureInfo *featureInfo, WRFloat* endPos)
{
	return kWRBadFontErr;
}

int DummyFontAccess::WRGetGlyphIDs(	WRFontDict* aFont, const char* string, WRInt32 strLength,
							WREncoding* encoding, WRInt32 writingDirection,
							WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail )
{
	return WRGetGlyphIDsFromUCS4Bytes(aFont, (const WRUnichar32*) string, strLength/sizeof(WRUnichar32), encoding, writingDirection, strikes, numStrikesAvail);
}

int DummyFontAccess::WRGetGlyphIDsFromUCS4Bytes(WRFontDict* aFont, const WRUnichar32* ucsString, WRInt32 ucsStrLength,
												WREncoding* encoding, WRInt32 writingDirection,
												WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail )
{
	if (encoding != (WREncoding*)kWRDFAMagicValue)
		return kWRInvalidEncodingErr;

	WRInt32 actLength = (ucsStrLength > *numStrikesAvail) ? *numStrikesAvail : ucsStrLength;
	
	WRGlyphID32 notDefGlyphID = WRGetNotDefGlyphID(aFont);
		
	for (WRInt32 i = 0; i < actLength; i++)
	{
		strikes[i].glyphID = ucsString[i];
	}
		
	*numStrikesAvail = actLength;
		
	if (ucsStrLength > *numStrikesAvail)
		return kWRSomeBytesNotMappedErr;

	return kWRNoErr;
}
	
char DummyFontAccess::WRTranslateGlyphID( WRTranslator* trans, WRGlyphID32 glyphID, WRByteChar* toString,
										WRInt32* toStrLen, WRInt32 matchPolicy )
{
	return kWRBadFontErr;		
}

WRInt32 DummyFontAccess::WRGetGlyphClassValue(	WRFontDict *aFont,
											WRRealGlyphPoint *strikes,
											WRInt32 numStrikes,
											WROTGlyphClassValue* classValueArray)
{
	return kWRUnsupportedFeatureErr;
}

WRFamilyList* DummyFontAccess::WRGetFamilyList( )
{
	return (WRFamilyList*)kWRDFAMagicValue;
}
  	
void DummyFontAccess::WRReleaseFamilyList( WRFamilyList* famList)
{
	//nothing
}
	
WRFontDict* DummyFontAccess::WRGetIndexedFont( WRFamily* family, WRInt32 index )
{
	if (index != 0)
		return NULL;
	
	return (WRFontDict*)kWRDFAMagicValue;
}
  
WRInt32 DummyFontAccess::WRGetNumFamilies(WRFamilyList*)
{
	return 1;
}
	
WRFamily* DummyFontAccess::WRGetIndexedFamily(WRFamilyList*, WRInt32 index )
{
	if (index != 0)
		return NULL;
	
	return (WRFamily*)kWRDFAMagicValue;
}
	
void DummyFontAccess::WRReleaseFamily( WRFamily* family)
{
	//nothing
}
	
WRInt32 DummyFontAccess::WRGetNumFontsInFamily( WRFamily* family )
{
	return 1;
}
	
WRBool DummyFontAccess::WRGetFamilyName(WRFontDict *aFont, char* buffer, int avail)
{
  strncpy(buffer,"dummy", avail);
  return WRTrue;
}
	
WRBool DummyFontAccess::WRGetFontName(WRFontDict *aFont, char* buffer, int avail)
{
  strncpy(buffer,"dummy", avail);
  return WRTrue;
}
	
WRBool DummyFontAccess::WRGetFullName(WRFontDict *aFont, char* buffer, int avail)
{
  strncpy(buffer,"dummy", avail);
  return WRTrue;
}

WRBool DummyFontAccess::WRGetStyleName(WRFontDict *aFont, char* buffer, int avail)
{
  strncpy(buffer,"dummy", avail);
  return WRTrue;
}
	
WRScriptID DummyFontAccess::WRGetWritingScript(WRFontDict *aFont)
{
	return (WRScriptID)kWRDontKnowScript;
}

WRInternalTechnology DummyFontAccess::WRGetTechnology(WRFontDict *aFont)
{
	return kWRTrueTypeFont;
}

int DummyFontAccess::WRGetNumCodePages(WRFontDict *aFont)
{
	return 0;
}
	
WRCodePage DummyFontAccess::WRGetNthCodePage(WRFontDict *aFont, WRInt32 n)
{
#ifdef WR_MAC_ENV
	return kWRRomanMacintoshCodePage;
#else
	return kWRRomanWindowsCodePage;
#endif
}
	
WRGlyphID32 DummyFontAccess::WRGetNotDefGlyphID(WRFontDict *aFont)
{
  return 0xFFFFFFE;
}

WRBool DummyFontAccess::WROTHasFeature(WRFontDict *aFont, const char* tag, const char* script, const char* lang )
{
	return WRFalse;
}
	
WRInt32 DummyFontAccess::WROTAvailableFeatures(WRFontDict *dict, char* feature, char* featureList, WRInt32* countFeatures, const char* script, const char* lang)
{
	return 0;
}

void DummyFontAccess::WRGetHorizontalMetrics(WRFontDict *aFont,WRFloat& ascent, WRFloat& descent, WRFloat& lineGap)
{
  ascent = (WRFloat)1.0/(WRFloat)1000.0;	
  descent = (WRFloat)1.0/(WRFloat)1000.0;	
  lineGap = (WRFloat)1.0/(WRFloat)1000.0;
}

#ifdef WR_WIN_ENV
WRBool DummyFontAccess::WRGetWindowsLOGFONTW(WRFontDict *aFont, WRPLOGFONTW lf)
{
	return WRFalse;
}
#endif	
	
WRTranslator* DummyFontAccess::WRNewTranslator( WRFontDict* aFont, WREncoding* toEncoding )
{
	return NULL;
}
	
void DummyFontAccess::WRDeleteTranslator( WRTranslator* trans )
{
	//nothing
}
	
char DummyFontAccess::WRTranslateEncoding( WRTranslator* trans, const char* fromString,
												WRInt32* fromStrLength, WREncoding* fromEncoding,
												WRByteChar* toString, WRInt32* toStrLength, WRInt32* bytesWritten,
												WRInt32 matchPolicy )
{
	return 0;
}
												
WREncoding* DummyFontAccess::WRNewEncoding( void )
{
	return (WREncoding*) kWRDFAMagicValue;
}
	
WREncoding* DummyFontAccess::WRNewPlatformEncoding( WRCodePage codePage )
{
	// We are supposed to work only with unicode encoding
#ifdef WR_LITTLE_ENDIAN
		if (codePage == kWRUTF16LittleEndianCodePage)
#endif
#ifdef WR_BIG_ENDIAN
		if (codePage == kWRUTF16BigEndianCodePage)
#endif
			return (WREncoding*) kWRDFAMagicValue;
		else
			return NULL;
}

void DummyFontAccess::WRDeleteEncoding( WREncoding* encode )
{
}
	
WRInt32 DummyFontAccess::WRGetNumGlyphs(WRFontDict *aFont)
{
	return 2048; //???
}

ASBool DummyFontAccess::IsDiacriticMark(WRGlyphID32 unicodeVal) 
{
	WROTGlyphClassValue cl;
	WRByteCount len=sizeof(cl);
	
	WRUDGetCharacterProperty((WRUnichar)unicodeVal,(WRCharacterPropertySelector)kWRClassCharacterProperty,(void*)&cl,&len);
	
	return IsMark(cl);
}

void DummyFontAccess::InternalGet1GlyphMetrics(WRGlyphID32 glyphID, WRFloat *xWidth, WRFloat *yWidth) 
{
	if (IsDiacriticMark(glyphID)) {
		if (yWidth)
	  		*yWidth = (WRFloat)0.01;
		if (xWidth)
	  		*xWidth = (WRFloat)0.01;
	} else {
		if (yWidth)
	  		*yWidth = (WRFloat)1.0;
		if (xWidth)
	  		*xWidth = (WRFloat)1.0;
	}
}
WRFontInstance*	DummyFontAccess::WRCreateVariableFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
		WRFloat* mmDesignVector, WREncoding* encoding,
		WRInt32 writingDirection,int designVectorLength)
	{
		//make sure to return non-null
		return (WRFontInstance*) kWRDFAMagicValue; 
	}

bool DummyFontAccess::WRCheckTypeIFont(WRFontDict *aFont)
{
	return false;
}

