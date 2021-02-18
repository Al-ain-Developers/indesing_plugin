//========================================================================================
//  
//  File: IWRFontInfo.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRFontInfo__
#define __IWRFontInfo__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRFontContextComponent.h"
#include "WRVector.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Interface for querying about font properties
/**
IWRFontInfo is an interface to a class for querying about font properties, whether they’re installed or not. 
The kind of information returned by the API is the same as what you can get with CTGetVal calls. 
If the client gives NULL in the IWRFontContext::Create call, a default implementation(WRDefaultFontInfoImpl)  will be provided by WRServices,
which relies on the FontDatabase service and on the Access object to answer the queries. 
The default implementation uses internal caches so that there’s no performance issue in calling it often for the same font.
Note: Prior to WRServices 4, there as a huge setup time liked to BuildFromCurrentContext(), which scans the font list and fill internal caches.
BuildFromCurrentContext() is still functional, but Reset() can be use instead to avoid loading the full list: it is used in conjunction with
IWRFontAccess::SearchFont() to fill the internal cache incrementally, when the font are used.
@sa IWRFontContext, IWRFontAccess
**/
class IWRFont;

class WRSERVICES_DECL IWRFontInfo : public WRFontContextComponent
{
public:
	virtual ~IWRFontInfo() {}
	enum { kStandard,kArabicXT,kPhonyx,kLinotype,kPseudoWithUnicode,kPseudoNoUnicode,kSimplifiedArabic,kWin31,kACE,kUnknownTech };

	/// Discards all cached information about runtime fonts
	/** Either this method or BuildFromCurrentContext must be called whenever the active font repertoire is changed externally
		(font installation or uninstallation). This condition can be detected by calling IWRFontAccess::CheckFontList(), assuming a proper
		implemetation was provided for this method (the default implementation does nothing)
		The method invalidates the content of all FontInfo internal caches, which will be rebuilt incrementally.
		This does not call IWRFontCache  and IWROptycaPool invalidations, which must be done before.
		Usually, all those related invalidations are performed indirectly by calling IWRFontContext::Invalidate();
		@sa IWRFontContext::Invalidate(), BuildFromCurrentContext(), IWRFontCache::Invalidate(), IWROptycaPool::Cleanup()
	*/
	virtual void Reset()=0;
	/// rebuild all cached information about runtime fonts 
	/** Either this method or Reset must be called whenever the active font repertoire is changed externally
		(font installation or uninstallation). This condition can be detected by calling IWRFontAccess::CheckFontList(), assuming a proper
		implemetation was provided for this method (the default implementation does nothing)
		This method invalidates the content of all FontInfo internal caches, and rebuild them by enumerating the installed fonts.
		This does not call IWRFontCache  and IWROptycaPool invalidations, which must be done before.
		Usually, all those related invalidations are performed indirectly by calling IWRFontContext::Invalidate();
		@sa IWRFontContext::Invalidate(), Reset(), IWRFontCache::Invalidate(), IWROptycaPool::Cleanup()
	*/
	virtual void BuildFromCurrentContext()=0;
	virtual WRScriptID GetWritingScript(WRFontDict* font) = 0;
	virtual WRAccessTechnology GetAccessTechnology(WRFontDict* font) = 0;
	virtual WRInt32 GetCodePage(WRFontDict* font) = 0;
	virtual WRFontDict* GetComplementaryFont(WRFontDict* font) = 0;
	virtual void SetComplementaryFont(WRFontDict* font, WRFontDict* comp) = 0;
	virtual const char* GetComplementaryFamilyName(WRFontDict* font) = 0;
	virtual const char* GetSubstituteFontName(WRFontDict* font) = 0;
	virtual const char* ComputeComplementaryFamilyName(WRFontDict* font) = 0;
	
	virtual WRScriptID GetWritingScript(const char* fontname,short pf) = 0;
	virtual WRAccessTechnology GetAccessTechnology(const char* fontname,short pf) = 0;
	virtual WRInt32 GetCodePage(const char* fontname,short pf) = 0;
	virtual const char* GetComplementaryFamilyName(const char* fontname,short pf) = 0;
	virtual const char* GetSubstituteFontName(const char* fontname,short pf) = 0;
	virtual bool CheckScriptSupport(WRFontDict* font, WRScriptID script) = 0;
	virtual WRBool CheckCodePageSupport(WRFontDict* fontDict, WRCodePage codepage) = 0;
	virtual WRFontDict*  FindFontByScript(WRScriptID script) = 0;
	virtual WRFontDict*  FindFontByCodePage(WRCodePage codepage) = 0;

	virtual WRScriptID RemoveWindowsLanguageSuffix(WRScriptID script, const char* subsettedFontName, char* fontName, WRInt32 avail, WRBool checkIfExists = WRTrue) = 0;
#ifdef WR_WIN_ENV
 	virtual bool GDILogFontSearch( WRFontDict* font, WRPLOGFONT lf,WRHDC dc = NULL) = 0;
#endif
	virtual WRFontDict*	GetDefaultFont(WRScriptID script) = 0;
	virtual WRFontDict* SearchFont(const char* name, WRVector<WRFloat> designVector = WRVector<WRFloat>()) = 0;
	virtual WRFontDict* SearchFont(const char* family, const char* style, WRInt32& matchQuality) = 0;
	virtual WRFontDict* SearchFamily(const char* name) = 0;
	virtual bool HasGlyphlets(WRFontDict*) { return 0; }
	virtual bool HasCustomSpaceWidth(WRFontDict*) { return 0; }
	virtual bool CheckScriptSupport(IWRFont* font, WRScriptID script) = 0;
};

#endif
