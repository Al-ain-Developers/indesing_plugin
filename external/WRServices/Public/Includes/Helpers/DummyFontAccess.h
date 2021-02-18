#ifndef __DummyFontAccess_h__
#define __DummyFontAccess_h__

#include "IWRFontAccess.h"

class DummyFontAccess:public IWRFontAccess
{
 public:
	virtual	WRFontInstance*	WRCreateFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection); 

	virtual void			WRDeleteFontInstance(WRFontInstance *inst);

	virtual WREncoding*		WRGetPreDefinedEncoding( WRInt32 whichEncoding );

	virtual void			WRGetGlyphWidth( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloat* width );

	virtual void			WRGetGlyphBBox( WRFontInstance *inst, WRGlyphID32 glyphID, WRFloatRect* bbox );

	virtual WRInt32			WRApplyFeatures(WRFontInstance *inst, WRRealGlyphPoint *strikes, WRInt32 *numStrikes, WRInt32 *numStrikesAvail,
										WROTFeatureInfo *featureInfo, WRFloat* endPos);

	virtual int				WRGetGlyphIDs(	WRFontDict* aFont, const char* string, WRInt32 strLength,
											WREncoding* encoding, WRInt32 writingDirection,
											WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail );

	virtual int				WRGetGlyphIDsFromUCS4Bytes(	WRFontDict* aFont, const WRUnichar32* ucsString, WRInt32 ucsStrLength,
														WREncoding* encoding, WRInt32 writingDirection,
														WRRealGlyphPoint* strikes, WRInt32* numStrikesAvail );

	virtual char			WRTranslateGlyphID( WRTranslator* trans, WRGlyphID32 glyphID, WRByteChar* toString,
												WRInt32* toStrLen, WRInt32 matchPolicy );

	virtual	WRInt32			WRGetGlyphClassValue(	WRFontDict *aFont,
													WRRealGlyphPoint *strikes,
													WRInt32 numStrikes,
													WROTGlyphClassValue* classValueArray);
  
  	virtual	WRFamilyList*	WRGetFamilyList( );
  	
	virtual	void			WRReleaseFamilyList( WRFamilyList* famList);
	
	virtual WRFontDict* 	WRGetIndexedFont( WRFamily* family, WRInt32 index );
  
	virtual WRInt32  			WRGetNumFamilies(WRFamilyList*);
	
	virtual WRFamily*		WRGetIndexedFamily(WRFamilyList*, WRInt32 index );
	
	virtual	void			WRReleaseFamily( WRFamily* family);
	
	virtual WRInt32			WRGetNumFontsInFamily( WRFamily* family );
	
	virtual WRBool			WRGetFamilyName(WRFontDict *aFont, char* buffer, int avail);
	
	virtual WRBool			WRGetFontName(WRFontDict *aFont, char* buffer, int avail);
	
	virtual WRBool			WRGetFullName(WRFontDict *aFont, char* buffer, int avail);

	virtual WRBool			WRGetStyleName(WRFontDict *aFont, char* buffer, int avail);
	
	virtual WRScriptID		WRGetWritingScript(WRFontDict *aFont);

	virtual WRInternalTechnology WRGetTechnology(WRFontDict *aFont);

	virtual int				WRGetNumCodePages(WRFontDict *aFont);
	
	virtual WRCodePage		WRGetNthCodePage(WRFontDict *aFont, WRInt32 n);
	
	virtual WRGlyphID32		WRGetNotDefGlyphID(WRFontDict *aFont);
		
	virtual WRBool			WROTHasFeature(WRFontDict *aFont,const char* tag, const char* script, const char* lang );
	
	virtual	WRInt32			WROTAvailableFeatures(WRFontDict *dict, char* feature, char* featureList, WRInt32* countFeatures, const char* script, const char* lang);

	virtual void			WRGetHorizontalMetrics(WRFontDict *aFont,WRFloat& ascent, WRFloat& descent, WRFloat& lineGap);

#ifdef WR_WIN_ENV
	virtual WRBool			WRGetWindowsLOGFONTW(WRFontDict *aFont, WRPLOGFONTW lf);
#endif	
	
	virtual WRTranslator*	WRNewTranslator( WRFontDict* aFont, WREncoding* toEncoding );
	
	virtual void			WRDeleteTranslator( WRTranslator* trans );
	
	virtual char			WRTranslateEncoding( WRTranslator* trans, const char* fromString,
												WRInt32* fromStrLength, WREncoding* fromEncoding,
												WRByteChar* toString, WRInt32* toStrLength, WRInt32* bytesWritten,
												WRInt32 matchPolicy );
												
	virtual WREncoding*		WRNewEncoding( void );
	
	virtual WREncoding*		WRNewPlatformEncoding( WRCodePage codePage );

	virtual void			WRDeleteEncoding( WREncoding* encode );
	
	virtual WRInt32			WRGetNumGlyphs(WRFontDict *aFont);
	virtual	WRFontInstance*	WRCreateVariableFontInstance(WRFontDict *aFont, WRFloatMatrix *matrix,
												WRFloat* mmDesignVector, WREncoding* encoding,
												WRInt32 writingDirection,int designVectorLength=0); 

	virtual bool WRCheckTypeIFont(WRFontDict *aFont);
 /* virtual WRFontGroup* WRGetNamedFontGroup( const char* groupType,const char* groupName, WRInt32* index ) {return NULL;}

  virtual WRInt32 WRGetNumFontGroups(const char* groupType );

  virtual WRFontGroup*	WRGetIndexedFontGroup( const char* groupType,WRInt32 index, char** groupName ) {return NULL;}

  virtual WRInt32 WRGetNumFontsInGroup( WRFontGroup* group );

  virtual WRInternalTechnology WRGetTechnology(WRFontDict *aFont)
    {
      return (WRInternalTechnology) kWRAnyTechnology;
    }

  virtual int WRGetNumCodePages(WRFontDict *aFont)
    {
      return 0;
    }

	virtual WRCodePage		WRGetNthCodePage(WRFontDict *aFont, WRInt32 n)

#ifdef WR_WIN_ENV
  virtual WRBool WRGetWindowsLOGFONT(WRFontDict *aFont, LOGFONT* lf) 
    {
      miAssert(false);
      
      return WRFalse;
    }
#endif

  virtual WRTranslator*	WRNewTranslator( WRFontDict* aFont, WREncodingObj* toEncoding )
    {
      return NULL;
    }

  virtual void WRDeleteTranslator( WRTranslator* trans )
    {
      miAssert(false);
    }
  
  virtual char WRTranslateEncoding( WRTranslator* trans, const char* fromString,
				    WRInt32* fromStrLength, WREncodingObj* fromEncoding,
				    char* toString, WRInt32* toStrLength, WRInt32* bytesWritten,
				    WRInt32 matchPolicy )
    {
      miAssert(false);
      
      return kWRBadFontErr;		
    }
  
  virtual void WRDeleteEncoding( WREncodingObj* encode )
    {
      miAssert(false);
    }
  
  virtual WREncodingObj* WRNewEncoding( void )
    {
      miAssert(false);

      return NULL;
    }

  virtual void WRSetTrueTypeEncodingCodePage( WREncodingObj* encode, WRCodePage codePage )
    {
      miAssert(false);
    }


  virtual WRInt32 WRGetNumGlyphs(WRFontDict *aFont)
    {
      // Should be called only for OpenType fonts
      miAssert(false);

      return 0;
    }

  virtual void WRGetGlyphNames(WRFontDict *aFont,char** names,WRInt32 numGlyphs)
    {
      // Should be called only for OpenType fonts
      miAssert(false);
    }

  virtual WRFontDict* WRFindFont(const char* name)
    {
      // Shouldn't be called
      miAssert(false);

      return NULL;
    }

  virtual WRBool WRDefKeyVal(WRFontDict *aFont,const char* key,void* val)
    {
      // Shouldn't be called
      miAssert(false);

      return WRFalse;
    }

  virtual ASUns16 SpecialGlyphToUCS(ASUns16 glyph);
  virtual ASUns16 UCSToSpecialGlyph(ASUns16 ucs);
  virtual ASUns16 ReplaceSpecialGlyph(WRFontDict* aFont, ASUns16 glyph);

  void SetContext(WR_CComposer* aComposer) { context = aComposer; }*/

 protected:

  void	InternalGet1GlyphMetrics(WRGlyphID32 glyphID, WRFloat *xWidth, WRFloat *yWidth);

  ASBool IsDiacriticMark(WRGlyphID32 glyphID);
	
};

#endif //__DummyFontAccess_h__
