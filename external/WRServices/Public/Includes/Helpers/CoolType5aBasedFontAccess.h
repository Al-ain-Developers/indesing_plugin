#ifndef __CoolType5aBasedFontAccess__
#define __CoolType5aBasedFontAccess__

#ifdef WR_CT5
	#error CoolType 5a is included by 5 is defined
#endif

#ifndef WR_CT5A
	#define WR_CT5A
#endif

#include <map>
#include <time.h>
#include "WRStrSafe.h"

class CoolType5aBasedFontAccess : public IWRFontAccess
{
public:
	CoolType5aBasedFontAccess() : fCTContext(true), fLastCheckDate(0), fLastSeed(0) // CTFontSet inheriting from the system context
	{}

	void SetCTContext(CTFontSet* context) { fCTContext = context; }

	virtual	WRFontInstance*		WRCreateFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection)
	{
		CCTFontDict fontDict((CTFontDict*) aFont);
		CCTEncoding cctEnc((CTEncoding*)encoding);
		CCTFontInstance cctInst(fontDict, *(BRVCoordMatrix*)matrix ,(CTTextWritingDirection)writingDirection, cctEnc, mmDesignVector);
		CTFontInstance* ctInst = cctInst.GetPointerAndAddRef();
		return (WRFontInstance*)ctInst;
	}

	virtual void WRDeleteFontInstance(WRFontInstance *inst)
	{
		CCTFontInstance cctInst((CTFontInstance*) inst,true);
	}

	virtual WREncoding*	WRGetPreDefinedEncoding( WRInt32 whichEncoding )
	{
		CCTEncoding cctEnc = CCTEncoding(CTPreDefinedEncodingType (whichEncoding));
		CTEncoding* ctEnc = &(*cctEnc);
		return (WREncoding*)ctEnc;
	}

	virtual void WRGetGlyphWidth( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloat* width)
	{ 
		CCTFontInstance cctInst((CTFontInstance*) inst);
#ifndef BIB_NO_THROW
		try
		{
#endif
			*width = cctInst.GetWidth( glyphID );
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			*width = 0;
		}
#endif
	}

	virtual void WRGetGlyphWidth( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloat* width, WRInt32 antiAliasType)
	{ 
		CCTFontInstance cctInst((CTFontInstance*) inst);
#ifndef BIB_NO_THROW
		try
		{
#endif
			if (antiAliasType >=0)
			{
				CTFontDict* pDict = (CTFontDict*)cctInst.GetFont();
				bool bHintableScript = false;
				std::map<CTFontDict*,bool>::const_iterator it = fMapHint.find(pDict);
				if (it == fMapHint.end())
				{
					CCTFontDict fontDict(pDict);
					// Exclude indic scripts from hinting
					bHintableScript = !((fontDict.IsScriptPresent("deva", kCTGlyphSubstitution | kCTGlyphPositioning) 
						|| fontDict.IsScriptPresent("beng", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("guru", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("gujr", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("orya", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("telu", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("knda", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("taml", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("mlym", kCTGlyphSubstitution | kCTGlyphPositioning)
						|| fontDict.IsScriptPresent("khmr", kCTGlyphSubstitution | kCTGlyphPositioning)));

					fMapHint.insert(std::pair<CTFontDict*, bool>(pDict, bHintableScript));
				}
				else
					bHintableScript = it->second;

				if (bHintableScript)
					*width = cctInst.GetWidth( glyphID, true, (CTAAType)antiAliasType );
				else
					*width = cctInst.GetWidth( glyphID );
			}
			else
				*width = cctInst.GetWidth( glyphID );
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			*width = 0;
		}
#endif
	}

	virtual void WRGetGlyphBBox( WRFontInstance *inst, WRGlyphID32 glyphID,WRFloatRect* bbox )
	{ 
		CCTFontInstance cctInst((CTFontInstance*) inst);
#ifndef BIB_NO_THROW
	try
	{
#endif
		cctInst.GetBBox( glyphID, *(BRVRealCoordRect*)bbox );
#ifndef BIB_NO_THROW
	}
	catch (...)
	{
		if (bbox != NULL)
		{
			bbox->left = 0.0;
			bbox->top = 0.0;
			bbox->right = 0.0;
			bbox->bottom = 0.0;
		}
	}
#endif
	}

	void GetMinMaxRange(WRInt32 startIndex, WRInt32* ranges, WRInt32 size, size_t& min, size_t& max);

	virtual WRInt32 WRApplyFeatures(WRFontInstance *inst, IWRStrikeBuffer *strikes, WRInt32 startStrike, WRInt32 *numStrikes,  
								 WROTFeatureInfo *featureInfo, WRFloat* endPenPos);

	virtual int	WRGetGlyphIDs(	WRFontDict* aFont, const char* string, WRInt32 strLength,
											WREncoding* encoding, WRInt32 writingDirection,
											WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail )
	{
		CBRVCoordMatrix mtx;
        CCTFontDict font((CTFontDict*)aFont);
        CCTEncoding cctEnc((CTEncoding*)encoding);
 
		CCTFontInstance cctInst( font, mtx, (CTTextWritingDirection) writingDirection, cctEnc);
		CTFontInstance* ctInst = cctInst;
		return WRGetGlyphIDs((WRFontInstance*)(ctInst), string, strLength, strikes, numStrikesAvail);
	}

	virtual int				WRGetGlyphIDs(	WRFontInstance* inst, const char* string, WRInt32 strLength,
											WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		CCTFontInstance cctInst((CTFontInstance*) inst);

        WRUInt32 origNumStrikes = *numStrikesAvail;
        WRUInt32 numGIDs = static_cast<WRUInt32>(cctInst.GetNumGlyphIDs( (const unsigned char*)string, strLength,(CTGlyphIDFlags) 2 /* kCTGlyphIDFlagVariationSequence */ ));
        *numStrikesAvail = numGIDs;

        if ( numGIDs > origNumStrikes )
            return kWRArrayTooShortErr;

        CTGlyphSharedBuffer gsb(numGIDs);
		// put the symbolic value back when all clients use a CT defining it
        cctInst.GetGlyphIDs( (const unsigned char*)string, strLength, gsb, (CTGlyphIDFlags) 2 /* kCTGlyphIDFlagVariationSequence */ );
        
        int maxGlyphID = WRGetNumGlyphs((WRFontDict*)((CTFontDict*)cctInst.GetFont())) - 1;
        WRGlyphID32 notDefGlyphID = WRGetNotDefGlyphID((WRFontDict*)((CTFontDict*)cctInst.GetFont()));
        
        for (WRUInt32 i=0 ; i<numGIDs ; i++)
        {
            WRGlyphID32 glid = gsb[i].glyphID;
            
            if (glid > maxGlyphID)
            	glid = notDefGlyphID;
            
            strikes[i].glyphID = glid;
        }

		return *numStrikesAvail ? kWRNoErr : kWRSomeBytesNotMappedErr;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return kWRCoolTypeError;
		}
#endif
	}

	virtual int	WRGetGlyphIDsFromUCS4Bytes(	WRFontDict* aFont, const WRUnichar32* ucsString, WRInt32 ucsStrLength,
											WREncoding* encoding, WRInt32 writingDirection,
											WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail )
	{
		CBRVCoordMatrix mtx;
        CCTFontDict font((CTFontDict*)aFont);
        CCTEncoding cctEnc((CTEncoding*)encoding);
 
		// We translate WRUnichar32 string UTF16 string
		// don't allocate for small chunks (almost all cases), use the stack instead
		char	aStaticCTString[sizeof(WRUnichar16) * 2 * 8];
		char*	aCTString;
		if (ucsStrLength >= 8)
			aCTString = (char*) WRMalloc( ucsStrLength * sizeof(WRUnichar16) * 2);
		else
			aCTString = aStaticCTString;

		WRInt32	aCTStringLength = 0;

		unsigned short*	tempPt = (unsigned short *) aCTString;

		for (WRInt32 j = 0; j < ucsStrLength; j++, tempPt++)
		{
			WRUnichar32 uc32 = ucsString[j];

			if (uc32 > 0xFFFF)
			{
				*tempPt++ = (unsigned short) (((uc32 - 0x10000) >> 10) + 0xd800);
				*tempPt = (unsigned short) ((uc32 & 0x3FF) + 0xdc00);
				aCTStringLength += 2;
			}
			else
				*tempPt = (unsigned short)uc32;
			
			aCTStringLength += 2;
		}

		tempPt = (unsigned short *) aCTString;

		int res;

		CCTFontInstance cctInst( font, mtx, (CTTextWritingDirection) writingDirection, cctEnc);
		CTFontInstance* ctInst = cctInst;
		res = WRGetGlyphIDs((WRFontInstance*)(ctInst), aCTString, aCTStringLength, strikes, numStrikesAvail);

		if (aCTString != aStaticCTString)
			WRFree(aCTString);

		return res;
	}

	virtual char WRTranslateGlyphID( WRTranslator* /*trans*/, WRGlyphID32 /*glyphID*/, char* /*toString*/,
												WRInt32* /*toStrLen*/, WRInt32 /*matchPolicy*/ )
	{
//		TODO
//		return ::CTTranslateGlyphID( (CTTranslator*) trans, glyphID, toString, toStrLen, matchPolicy );
		return kWRNoErr;
	}

	virtual	WRInt32 WRGetGlyphClassValue(	WRFontDict *aFont,
										WRRealGlyphPoint *strikes,
										WRInt32 numStrikes,
										WROTGlyphClassValue* classValueArray)
	{
		CCTFontDict fontDict((CTFontDict*)aFont);
#ifndef BIB_NO_THROW
		try
		{
#endif
			if (!fontDict.GetGlyphClassValues((CTRealGlyphPoint*)strikes,numStrikes,(CTGlyphClassValue*)classValueArray))
				return kWRUnsupportedFeatureErr;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return kWRUnsupportedFeatureErr;
		}
#endif
		return kWRNoErr;
	}
	virtual WRBool WRGetFamilyName(WRFontDict *aFont, char* buffer, int avail)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CTUTF16Unit ucBuf[256];		
			size_t ucLen = 256;
			CCTFontDict font((CTFontDict*)aFont);
			font.GetFamilyName(ucBuf,ucLen,true);
			return UTF16toASCII(ucBuf, ucLen, buffer, avail);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return false;
		}
#endif
	}

	virtual WRBool WRGetFontName(WRFontDict *aFont, char* buffer, int avail)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			CBIBStringAtom strAtom = font.GetFontName();
        	if ( ! strAtom.IsValid() )
				return false;
			int len = static_cast<int>(strlen( strAtom.c_str() ));
			if (len+1 >= avail)
				return false;
			WRStrSafe::strcpy(buffer, avail, strAtom.c_str());
			return true;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return false;
		}
#endif
	}

	virtual WRBool WRGetFullName(WRFontDict *aFont, char* buffer, int avail)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CTUTF16Unit ucBuf[256];		
			size_t ucLen = 256;
			CCTFontDict font((CTFontDict*)aFont);
			font.GetFullName(ucBuf,ucLen,true);
			return UTF16toASCII(ucBuf, ucLen, buffer, avail);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return false;
		}
#endif
	}

	virtual WRBool WRGetStyleName(WRFontDict *aFont, char* buffer, int avail)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CTUTF16Unit ucBuf[256];		
			size_t ucLen = 256;
			CCTFontDict font((CTFontDict*)aFont);
			font.GetStyleName(ucBuf,ucLen,true);
			return UTF16toASCII(ucBuf, ucLen,  buffer, avail);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return false;
		}
#endif
	}

	virtual	WRFamilyList*	WRGetFamilyList( )
	{
		CCTFamilyList tmpFamily( fCTContext, kCTASCIIEnum);
		CTFamilyList* ctFam = tmpFamily.GetPointerAndAddRef();
		return (WRFamilyList*) ctFam;
	}

	virtual	void	WRReleaseFamilyList( WRFamilyList* famList)
	{
		CTFamilyList* ctFamList = (CTFamilyList*)famList;
		if (ctFamList)
            gCTBaseInterface.Release(ctFamList);
	}

	virtual WRFontDict* 	WRGetIndexedFont( WRFamily* family, WRInt32 index )
	{
		CCTFamily cctFam((CTFamily*)family);
		CCTFontDict cctDict = cctFam.GetNthFont(index);
		CTFontDict* ctDict = cctDict;
		return (WRFontDict*)ctDict;
	}

	virtual WRInt32 WRGetNumFamilies(WRFamilyList* famList)
	{
		CCTFamilyList tmpFamily( (CTFamilyList*) famList);
        return static_cast<WRInt32>(tmpFamily.GetNumFamilies());
	}

	virtual WRFamily* WRGetIndexedFamily(WRFamilyList* famList, WRInt32 index )
	{
		CCTFamilyList cctFamList( (CTFamilyList*) famList);
		CCTFamily cctFam = cctFamList.GetNthFamily(index);
		CTFamily* ctFam = cctFam.GetPointerAndAddRef();
		return (WRFamily*) ctFam;
	}

	virtual	void	WRReleaseFamily( WRFamily* family)
	{
		CTFamily* ctFamily = (CTFamily*)family;
		if (ctFamily)
            gCTBaseInterface.Release(ctFamily);
	}

	virtual WRInt32 WRGetNumFontsInFamily( WRFamily* family )
	{
		CCTFamily cctFam((CTFamily*)family);
		return static_cast<WRInt32>(cctFam.GetNumFonts());
	}

	virtual WRScriptID WRGetWritingScript(WRFontDict *aFont)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			return WRScriptID(font.GetWritingScript());
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return kWRDontKnowScript;
		}
#endif
	}

	virtual WRInternalTechnology WRGetTechnology(WRFontDict *aFont)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			return WRInternalTechnology(font.GetFontTechnology());
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return kWRUnknownTechnology;
		}
#endif
	}

	virtual int	WRGetNumCodePages(WRFontDict *aFont)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			return static_cast<int>(font.GetNumCodePages());
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return 0;
		}
#endif
	}

	virtual WRCodePage WRGetNthCodePage(WRFontDict *aFont, WRInt32 n)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			CTCPInfo    cpInfo;
	        font.GetNthCodePage( n, cpInfo );
	        return WRCodePage(cpInfo.codePage);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return kWRDontKnowCodePage;
		}
#endif
	}

	virtual WRGlyphID32		WRGetNotDefGlyphID(WRFontDict *aFont)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict font((CTFontDict*)aFont);
			return WRGlyphID32(font.GetNotdefGlyphID());
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return 0;
		}
#endif
	}

	virtual WRBool			WROTHasFeature( WRFontDict *aFont,const char* tag, const char* script, const char* lang  )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict fontDict((CTFontDict*)aFont);
			
			if (fontDict.GetNumDesignAxes() != 0) // MM1 font
				return fontDict.HasFeature(tag,script,lang);

			if (strcmp(tag, kWRAnyFeatureTag) == 0)
			{
				return fontDict.IsScriptPresent(script, kCTGlyphSubstitution | kCTGlyphPositioning);
			}
			return fontDict.IsFeaturePresent(script, lang ? lang : kCTDefaultLanguageTag, tag, kCTGlyphSubstitution | kCTGlyphPositioning);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return false;
		}
#endif
	}

	virtual	WRInt32			WROTAvailableFeatures(WRFontDict *dict, char* feature, char* featureList, WRInt32* countFeatures, const char* script, const char* lang)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTFontDict fontDict((CTFontDict*)dict);

			if (feature && fontDict.GetNumDesignAxes() != 0) // MM1 font
				return fontDict.HasFeature(feature,script,lang) ? kWRNoErr : kWRUnsupportedFeatureErr;
	
			if (feature)
				return fontDict.IsFeaturePresent(script,lang ? lang : kCTDefaultLanguageTag, feature, kCTGlyphSubstitution | kCTGlyphPositioning) ? kWRNoErr : kWRUnsupportedFeatureErr;

			WRInt32 nbFeatures = static_cast<WRInt32>(fontDict.GetNumFeatures(script,lang));

			if (featureList && *countFeatures < nbFeatures)
				return kWRArrayTooShortErr;

			if (featureList)
				for (int i = 0; i < nbFeatures; i++)
					fontDict.GetNthFeature(i, featureList + i*4, script,lang);

			*countFeatures = nbFeatures;

			return kWRNoErr;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
            return kWRUnsupportedFeatureErr;
		}
#endif
	}

	virtual void WRGetHorizontalMetrics(WRFontDict *aFont,WRFloat& ascent, WRFloat& descent, WRFloat& lineGap)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			BRVRealCoord typoAscent;
	        BRVRealCoord typoDescent;
	        BRVRealCoord typoLineGap;
			CCTFontDict fontDict((CTFontDict*)aFont);
			fontDict.GetHorizontalMetrics(typoAscent,typoDescent,typoLineGap);
			ascent = typoAscent;
			descent = typoDescent;
			lineGap = typoLineGap;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			ascent = 0.0;
			descent = 0.0;
			lineGap = 0.0;
		}
#endif
	}

#ifdef WR_WIN_ENV
	virtual WRBool			WRGetWindowsLOGFONTW(WRFontDict *aFont,WRPLOGFONTW lf)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
 		CCTFontDict cctFont((CTFontDict*)aFont);
		return cctFont.GetWinLOGFONT(lf);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return false;
		}
#endif
	}
#endif

	virtual WRTranslator*	WRNewTranslator( WRFontDict* aFont, WREncoding* toEncoding )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTEncoding  cctEnc ((CTEncoding*) toEncoding);
	 		CCTFontDict cctFont((CTFontDict*)aFont);
			CCTTranslator trans( cctEnc, cctFont);
	        return (WRTranslator*) trans.GetPointerAndAddRef();
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return NULL;
		}
#endif
	}

	virtual void			WRDeleteTranslator( WRTranslator* trans )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTTranslator cctTrans( (CTTranslator*)trans, true);
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return;
		}
#endif
	}

	virtual char			WRTranslateEncoding( WRTranslator* trans, const char* fromString,
												WRInt32* fromStrLength, WREncoding* fromEncoding,
												WRByteChar* toString, WRInt32* toStrLength, WRInt32* bytesWritten,
												WRInt32 matchPolicy )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		CCTTranslator cctTrans( (CTTranslator*)trans);

        //TODO: fix for obsolete match policies
        size_t fromBytesRead;
        char retCode = kWRNoErr;
        *bytesWritten = *toStrLength;

		size_t myBytesWritten = *bytesWritten;

        bool succeeded = cctTrans.TranslateEncoding((CTEncoding*) fromEncoding, (const unsigned char*)fromString, *fromStrLength, fromBytesRead,
                (unsigned char*)toString, *toStrLength, myBytesWritten, (CTTranslatePolicy)matchPolicy);
        *fromStrLength = static_cast<WRInt32>(fromBytesRead);
		*bytesWritten = static_cast<WRInt32>(myBytesWritten);
        if ( !succeeded )
            {
            // the ct5 api failed for one of 2 reasons:
            retCode = (*bytesWritten > *toStrLength) ? (char)kWRArrayTooShortErr
                                                     : (char)kWRSomeBytesNotMappedErr;
            }

        *toStrLength = *bytesWritten;

        return retCode;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return kWRCoolTypeError;
		}
#endif
	}

	virtual void WRDeleteEncoding( WREncoding* encode )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
			CCTEncoding cctEnc( (CTEncoding*) encode, true );
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return;
		}
#endif
	}

	virtual WREncoding*	WRNewEncoding( void )
	{
		CCTEncoding cctEncoding;
		CTEncoding* ctEnc = cctEncoding.GetPointerAndAddRef();
		return (WREncoding*)ctEnc;
	}

	virtual WREncoding*	WRNewPlatformEncoding( WRCodePage cp )
	{
		CCTEncoding cctEnc = CCTEncoding(CTCodePage(cp));
		CTEncoding* ctEnc = cctEnc.GetPointerAndAddRef();
		return (WREncoding*)ctEnc;
	}

	virtual WRInt32			WRGetNumGlyphs(WRFontDict *aFont)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		CCTFontDict font((CTFontDict*)aFont);
		return static_cast<WRInt32>(font.GetNumGlyphs());
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return 0;
		}
#endif
}
	
	virtual void			WRGetGlyphNames(WRFontDict * /*aFont*/,char** /*names*/,WRInt32 /*numGlyphs*/)
	{
		// Implement if WRCHECKMARKPOSITIONING is enabled
		//::CTGetVal((CTFontDict*) aFont, "charstringnames", &names, numGlyphs * sizeof (char*));
	}

	virtual void			WRGetICFBox( WRFontDict *aFont, WRFloatRect *icfBox )
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		CCTFontDict font((CTFontDict*)aFont);
	
		BRVRealCoordRect box;
		font.GetICFBox(box);

		icfBox->left = box.xMin;
		icfBox->top = box.yMin;
		icfBox->right = box.xMax;
		icfBox->bottom = box.yMax;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			icfBox->left = 0.0;
			icfBox->top = 0.0;
			icfBox->right = 0.0;
			icfBox->bottom = 0.0;
		}
#endif
	}
	virtual WRInt32			WRGetNumPaths(WRFontDict* aFont);
	virtual WRError			WRGetNthPath(WRFontDict* font, int i, WRPath& path) ;

	virtual WRFontDict*	WRSearchFont(const char* name)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		CBIBStringAtom enc; 
		size_t designVecLength; 
		CCTFontDict cctFontDict = fCTContext.FindFont(name, enc, NULL, designVecLength);
		if (!cctFontDict.IsValid() || cctFontDict.GetFontStatus() == kCTFontStatus_Disabled || cctFontDict.GetFontStatus() == kCTFontStatus_Invalid || cctFontDict.GetNumGlyphs() == 0) 
			return NULL;
		CTFontDict* ctDict = cctFontDict;
		return (WRFontDict*)ctDict;
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			return NULL;
		}
#endif
	}

	virtual WRFontDict*	WRSearchFont(const char* familyName, const char* styleName, int& matchQuality)
	{
		CTUTF16Unit ucBuf[256];		
		char buffer[256];
		size_t ucLen = 256;
		size_t avail = 256;
		CTFontDict* resDict = NULL;
		CCTFamilyList cctFamList( fCTContext, kCTASCIIEnum);
		matchQuality = 4;
		size_t numFamilies = cctFamList.GetNumFamilies();
		for (size_t i = 0; i < numFamilies && matchQuality > 2; i++)
		{
			CCTFamily cctFam = cctFamList.GetNthFamily(i);
			size_t numFont = cctFam.GetNumFonts();
			for (size_t j = 0; j < numFont; j++)
			{
				CCTFontDict cctDict = cctFam.GetNthFont(j);
#ifndef BIB_NO_THROW
				try
				{
#endif
				if (!cctDict.IsValid() || cctDict.GetFontStatus() == kCTFontStatus_Disabled || cctDict.GetFontStatus() == kCTFontStatus_Invalid || cctDict.GetNumGlyphs() == 0) 
					continue;
#ifndef BIB_NO_THROW
				}
				catch (...)
				{
				continue;
				}
#endif
				CTFontDict* ctDict = cctDict;
				if (j == 0)
				{
					ucLen = 256;
					avail = 256;
					cctDict.GetFamilyName(ucBuf,ucLen,true);
					// doesn't match, continue with the next family
					if(!UTF16toASCII(ucBuf,  (int)ucLen, buffer, (int) avail) || WR_stricmp(buffer,familyName))
						break;
				}
				ucLen = 256;
				avail = 256;
				cctDict.GetStyleName(ucBuf,ucLen,true);
				if(!UTF16toASCII(ucBuf, (int)ucLen, buffer,  (int)avail))
					continue; // weird style, ignore it
				if (WR_stricmp(buffer,styleName) == 0)
				{	// found
					matchQuality = 0;
					return (WRFontDict*)ctDict;
				}
				if (WR_stricmp(buffer,"Regular") == 0 || WR_stricmp(buffer,"Plain") == 0 || WR_stricmp(buffer,"Roman") == 0)
				{	// default if the exact style isn't found
					matchQuality = 1;
					resDict = ctDict;
				}
				else if (matchQuality > 2)
				{	// last resort choice inside the family
					matchQuality = 2;
					resDict = ctDict;
				}
			}
		}
        return (WRFontDict*)resDict; 
    } 
	virtual bool CheckFontList(void)
	{
		time_t currentDate = time(NULL);
		if (currentDate != fLastCheckDate)
		{
			BRVUns32 seed = fCTContext.Sync();
			fLastCheckDate = currentDate;
			if (seed != fLastSeed)
			{
				fLastSeed = seed;
				return true;
			}
		}
		return false;
	}

	virtual WRBool GetUnitsPerEm(WRFontDict* aFont, WRUInt16& unitsPerEm)
	{
		unitsPerEm = 0;

		if (aFont)
		{
			CCTFontDict font((CTFontDict*)aFont);

			if (font.GetUnitsPerEm(unitsPerEm))
				return WRTrue;
		}

		return WRFalse;
	}

	virtual bool GetFontVersion(WRFontDict *fntDict, WRUInt8 *versionStr, WRByteCount len);

	virtual	bool GetOutlineInfo(void* userData, OutlinePointCB callBack, WRFontDict *fntDict, WRGlyphID32 glyphID);
     virtual	WRFontInstance*		WRCreateVariableFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
		WRFloat* mmDesignVector, WREncoding* encoding,
		WRInt32 writingDirection,int designVectorLength)
	{
		CCTFontDict fontDict((CTFontDict*)aFont);
		int numDesignAxes = static_cast<int>(fontDict.GetNumDesignAxes());
		BRVRealCoord *defaultVector = (BRVRealCoord*)malloc(numDesignAxes *sizeof(BRVRealCoord));
		//checks to make sure that valid design vector is passed in FontInstance Creation
		if (designVectorLength<numDesignAxes)
		{
			fontDict.GetDefaultDesignVector(defaultVector);
			for (int i = 0; i < designVectorLength; i++)
			{
				defaultVector[i] = mmDesignVector[i];
			}
			designVectorLength = numDesignAxes;
			mmDesignVector = defaultVector;
		}
		else if(designVectorLength>numDesignAxes)
		{
			designVectorLength = numDesignAxes;
		}
		CCTEncoding cctEnc((CTEncoding*)encoding);
		CCTFontInstance cctInst(fontDict, *(BRVCoordMatrix*)matrix, (CTTextWritingDirection)writingDirection, cctEnc, mmDesignVector,designVectorLength);
		free(defaultVector);
		CTFontInstance* ctInst = cctInst.GetPointerAndAddRef();
		return (WRFontInstance*)ctInst;
	}

	 virtual bool WRCheckTypeIFont(WRFontDict *aFont)
	 {
		 CCTFontDict fontDict((CTFontDict*)aFont);
		 if (fontDict.GetFontType()== kCTFontTypeType1 || fontDict.GetFontType() == kCTFontTypeCID || fontDict.GetFontType() == kCTFontTypeATC || fontDict.GetFontType() == kCTFontTypeBitmap || fontDict.GetFontType() == kCTFontTypeType3 || fontDict.GetFontType() == kCTDontKnowFontType)
			 return true;
		 return false;
	 }
protected:

	static	int WR_stricmp(const char *s1, const char *s2);
	static	int WR_tolower(int c);
	static	WRBool UTF16toASCII(CTUTF16Unit *ucBuf, size_t ucLen, char* buffer, int avail);
	WRInt32 WRApplyFeaturesForMM1Fonts(WRFontInstance *inst, IWRStrikeBuffer *strikes, WRInt32 startstrike, WRInt32 *numStrikes, WROTFeatureInfo *featureInfo, WRFloat* endPenPos);

	CCTFontSet					fCTContext;
	std::map<CTFontDict*,bool>	fMapHint;
	time_t						fLastCheckDate;
	BRVUns32					fLastSeed;
};
#endif


