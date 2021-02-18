//========================================================================================
//
//	File:	IWRFontDatabase.h
//
//	Author: prubini
//
//	Date:	6/8/01
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRFontDatabase__
#define __WRFontDatabase__

#include "WRConfig.h"
#include "WRDefines.h"
#include "IWRFontContext.h"
#include "WRClass.h"
#include "WRVector.h"
#include "WRPath.h"


#ifdef WR_MAC_ENV
#pragma options align=power
#endif


class FontDBDefaults
{
public:
	char		fRmDefaultFontFamily[128];
	char		fArDefaultFontFamily[128];
	char		fHbDefaultFontFamily[128];
	char		fCEDefaultFontFamily[128];
	char		fCyrDefaultFontFamily[128];
	char		fGreekDefaultFontFamily[128];	
	char		fTurkishDefaultFontFamily[128];	
	char		fBalticDefaultFontFamily[128];	
	WRScriptID	fRunningScript;
};


class WRFontDict;
class WRFontRec;


class WRSERVICES_DECL IWRFontDatabase : public WRClass
{
protected:
	virtual ~IWRFontDatabase() {}
public:
	static IWRFontDatabase*	GetWRFontDatabase();
	static void				ReleaseWRFontDatabase();

	virtual void SetDefaults(FontDBDefaults* dbParams) = 0;
	virtual const char* GetDefault(WRScriptID script) = 0;
	virtual void Init(IWRMultiProcessing* multi) = 0;
	virtual void Terminate() = 0;
	virtual void SetDBPaths(WRPath* pathWinSoft, WRPath* pathUser) = 0;

	virtual WRFontRec* GetEntry(const char* fontName,WRPlatform pf) = 0;
	
	virtual const WRPath* GetUserDBPath(void) = 0;
};


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif //__WRFontDatabase__

