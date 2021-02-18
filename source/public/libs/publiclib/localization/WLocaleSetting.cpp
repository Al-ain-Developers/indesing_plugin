//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/localization/WLocaleSetting.cpp $
//  
//  Owner: Michael Burbidge
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
//========================================================================================

#include "VCPublicHeaders.h"

#include "WLocaleSetting.h"
#include "CoreResTypes.h"
#include "IDResourceShell.h"
#include "WPublicLibGlobals.h"

#include "ShuksanCoolType.h"
#include "buildnumber.h"
#ifdef qME
#include "WRServices.h"
#endif

#define		ACP_EASTERN_EUROPEAN	1250		// Latin 2: Eastern Europe
#define		ACP_CYRILLIC			1251		// Cyrillic
#define		ACP_LATIN1				1252		// Latin 1
#define		ACP_GREEK				1253		// Greek
#define		ACP_TURKISH				1254		// Turkish
#define		ACP_HEBREW				1255		// Hebrew
#define		ACP_ARABIC				1256		// Arabic
#define		ACP_BALTIC				1257		// Baltic
#define		ACP_VIETNAMESE			1258		// Vietnamese

#define		ACP_THAI				874			// Thai
#define		ACP_JAPAN				932			// JIS/Japan
#define		ACP_SIMPLIFIED_CHINESE	936			// Chinese: Simplified chars--PRC and Singapore
#define		ACP_KOREAN				949			// Korean Unified Hangeul
#define		ACP_TRADITIONAL_CHINESE	950			// Chinese: Traditional chars--Taiwan and Hong Kong

#define WTOOLBOX

#define kFeatureSetKey TEXT("Feature Set Locale Setting")


//========================================================================================
// CLASS WLocaleSetting
//========================================================================================

bool16 WLocaleSetting::ts_LocaleCacheValid = kFalse;
PMLocaleId WLocaleSetting::ts_LocaleCacheContent;

int32 WLocaleSetting::ts_SystemScript = kCTDontKnowScript;

//----------------------------------------------------------------------------------------
// WLocaleSetting::SetLocale
//----------------------------------------------------------------------------------------

void WLocaleSetting::SetLocale(const PMLocaleId& locale)
{
	if (!ts_LocaleCacheValid)
	{
		HKEY hAppKey = GetAppKey(locale);

		if (hAppKey != NULL)
		{
			int32 featureSetId = locale.GetFeatureSetId();
			RegSetValueEx(hAppKey, kFeatureSetKey, 0, REG_DWORD, (const BYTE*) &featureSetId, 4);

			RegCloseKey(hAppKey);
		}
	}
	else
	{
		ts_LocaleCacheContent = locale;
	}
}

//----------------------------------------------------------------------------------------
// WLocaleSetting::GetLocale
//----------------------------------------------------------------------------------------

#pragma optimize( "", off )

PMLocaleId WLocaleSetting::GetLocale()
{
	if (ts_LocaleCacheValid) return ts_LocaleCacheContent;

	// ----- Get the feature set resource.

	// This function may be called very early on startup(before PublicLibGlobals::WinEnvironment::Init)
	// so load the feature set resource by specifying the instance directly (avoiding GetResourceHandle call)
	IDResource featureSetRes = IDResourceShell::Get(RsrcSpec(PluginID(kApplicationPluginID), kFeatureSetRsrcType, 1));

	ASSERT_MSG(featureSetRes.IsValid(), "WLocaleSetting - can't find kFeatureSetRsrcType resource");

	int32 featureSet = 0xF000; //Invalid value for early return if resources folder missing. Valid vals as 0x10x (ID), 0x20x (IC) and 0x40x (IDS)
	PMLocaleId locale(featureSet, k_enUS);

	if (featureSetRes.IsValid())
	{
		featureSet = *(int32*)featureSetRes.Get();
		// ----- Initialize the locale id with the feature set id
		ASSERT_MSG(featureSet > kFSBaseID, "Warning - FEAT resource has a strange feature set id");
		locale = PMLocaleId(featureSet, k_enUS);

		HKEY hAppKey = GetAppKey(locale);

		if (hAppKey != NULL)
		{
			int32 featureSetId;
			DWORD dataType, dataLen = 4;
			LONG regqvErr = RegQueryValueEx(hAppKey, kFeatureSetKey, 0, &dataType, (BYTE*)&featureSetId, &dataLen);

			switch (regqvErr)
			{
			case ERROR_FILE_NOT_FOUND:	// if the key does not exist - then create it based on defaults
				SetLocale(locale);
				break;

			case ERROR_SUCCESS:
				ASSERT_MSG(featureSetId > kFSBaseID, "Warning - feature set reg entry has strange feature set id");
				locale = PMLocaleId((int16)featureSetId, k_enUS);
				break;

			default:
				ASSERT_FAIL("WLocaleSetting::GetLocale() - Error getting feature set id.");
				break;
			}
			RegCloseKey(hAppKey);
		}
	}
	ts_LocaleCacheValid = kTrue;
	return ts_LocaleCacheContent = locale;
}

#pragma optimize( "", on )

//----------------------------------------------------------------------------------------
// WLocaleSetting::GetSystemLocale
//----------------------------------------------------------------------------------------

PMLocaleId WLocaleSetting::GetSystemLocale()
{
	const int16 scriptID = WLocaleSetting::GetSystemScript();
	const int16 appFS = GetLocale().GetProductFS();
	switch (scriptID)
	{
		case kCTRomanScript:
			{
				// this is the old version of WLocaleSetting::GetSystemLocale()

				TCHAR language[128];
				TCHAR country[128];

				LCID localeID = ::GetUserDefaultLCID();
				::GetLocaleInfo(localeID, LOCALE_SENGLANGUAGE, language, sizeof(language)/sizeof(TCHAR));
				::GetLocaleInfo(localeID, LOCALE_SENGCOUNTRY, country, sizeof(country)/sizeof(TCHAR));
				return LookupCountryID(localeID);
			}
		case kCTJapaneseScript:
			{
				return PMLocaleId(appFS | kJapaneseLanguageFS, k_jaJP);
			}
		case kCTSimplifiedChineseScript:
			{
				return PMLocaleId(appFS | kJapaneseLanguageFS, k_zhCN);
			}
		case kCTTraditionalChineseScript:
			{
				return PMLocaleId(appFS | kJapaneseLanguageFS, k_zhTW);
			}
		case kCTKoreanScript:
			{
				return PMLocaleId(appFS | kJapaneseLanguageFS, k_koKR);
			}
	}

	return PMLocaleId(appFS | kRomanLanguageFS, k_enUS);
}

//----------------------------------------------------------------------------------------
// WLocaleSetting::LookupCountryID
//----------------------------------------------------------------------------------------

PMLocaleId WLocaleSetting::LookupCountryID(LCID WindowsLocaleId)
{
	LANGID language = LANGIDFROMLCID(WindowsLocaleId);
	const int16 appFS = GetLocale().GetProductFS();

	switch(language)
	{
		case MAKELANGID(LANG_ENGLISH,   SUBLANG_ENGLISH_US):
			return PMLocaleId(appFS | kRomanLanguageFS, k_enUS);

		case MAKELANGID(LANG_ENGLISH,   SUBLANG_ENGLISH_UK):
			return PMLocaleId(appFS | kRomanLanguageFS, k_enGB);

		case MAKELANGID(LANG_GERMAN,    SUBLANG_GERMAN):
			return PMLocaleId(appFS | kRomanLanguageFS, k_deDE);

		case MAKELANGID(LANG_FRENCH,    SUBLANG_FRENCH):
			return PMLocaleId(appFS | kRomanLanguageFS, k_frFR);

		case MAKELANGID(LANG_JAPANESE,  SUBLANG_NEUTRAL):
			return PMLocaleId(appFS | kJapaneseLanguageFS, k_jaJP);

		default:
			TRACEFLOW_OBSOLETE("Old:Public", "Locale not determined or not available (%d)\n", language);
			return PMLocaleId(appFS | kRomanLanguageFS, k_enUS);
	}
}

//----------------------------------------------------------------------------------------
// WLocaleSetting::GetAppKey
//----------------------------------------------------------------------------------------

HKEY WLocaleSetting::GetAppKey(const PMLocaleId locale)
{
	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hVersionKey = NULL;

	TCHAR *appName = NULL, *ver = NULL;

	if (locale.IsProductFS(kInDesignProductFS))
	{
		appName = TEXT("InDesign");
		ver = TEXT("SOFTWARE\\Adobe\\InDesign\\")TEXT(kAppVersionNumberKeyStr);
	}
	else if (locale.IsProductFS(kInCopyProductFS))
	{
		appName = TEXT("InCopy");
		ver = TEXT("SOFTWARE\\Adobe\\InCopy\\")TEXT(kAppVersionNumberKeyStr);
	}
	else if (locale.IsProductFS(kInDesignServerProductFS))
	{
		appName = TEXT("InDesign Server");
		ver = TEXT("SOFTWARE\\Adobe\\InDesign Server\\")TEXT(kAppVersionNumberKeyStr);
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE"), 0, KEY_WRITE|KEY_READ, &hSoftKey) == ERROR_SUCCESS)
	{
		DWORD dw;
		if (RegCreateKeyEx(hSoftKey, TEXT("Adobe"), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,	&hCompanyKey, &dw) == ERROR_SUCCESS)
		{
			if (RegCreateKeyEx(hCompanyKey, appName, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hAppKey, &dw) == ERROR_SUCCESS)
			{
				RegCreateKeyEx(hAppKey, TEXT(kAppVersionNumberKeyStr), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hVersionKey, &dw);
			}
		}
	}
	else
	{
		// If we're not running as an administrator, we still need to be able to get the
		// key for read access to the values!
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, ver, 0, KEY_READ, &hVersionKey);
	}

	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);
	if (hAppKey != NULL)
		RegCloseKey(hAppKey);

	return hVersionKey;
}

//---------------------------------------------------------------------------------------
// WLocaleSetting::GetSystemScript
//----------------------------------------------------------------------------------------

int16 WLocaleSetting::GetSystemScript()
{
	if( WLocaleSetting::ts_SystemScript == kCTDontKnowScript )
	{
		// this is the old version of WPMString::GetSystemScript()
		uint32 codepage = WTOOLBOX::GetACP();
		switch(codepage)
		{
			case ACP_EASTERN_EUROPEAN:
				WLocaleSetting::ts_SystemScript = kCTEastEuropeanRomanScript;
				break;

			case ACP_CYRILLIC:
				WLocaleSetting::ts_SystemScript = kCTCyrillicScript;
				break;

			case ACP_LATIN1:
				WLocaleSetting::ts_SystemScript = kCTRomanScript;
				break;

			case ACP_GREEK:
				WLocaleSetting::ts_SystemScript = kCTGreekScript;
				break;

			case ACP_TURKISH:
#ifdef qME
		        // although the turkish mac OS says it is roman
		        // the endocing is different (extra constant kWRTurkishScript)
		        // on win the codepage is specific to Turkey
		        WLocaleSetting::ts_SystemScript = kWRTurkishScript;
#else
				WLocaleSetting::ts_SystemScript = kCTRomanScript;
#endif
				break;

			case ACP_HEBREW:
				WLocaleSetting::ts_SystemScript = kCTHebrewScript;
				break;

			case ACP_ARABIC:
				WLocaleSetting::ts_SystemScript = kCTArabicScript;
				break;

			case ACP_BALTIC:
#ifdef qME
				// stop the third WW
				// baltic languages are NOT written with the cyrillic alphabet
				// but with an extended roman alphabet...
				// on win, its a specific codepage, not included in CE
		        WLocaleSetting::ts_SystemScript = kWRBalticScript;
#else
				WLocaleSetting::ts_SystemScript = kCTCyrillicScript;
#endif
				break;

			case ACP_VIETNAMESE:
				WLocaleSetting::ts_SystemScript = kCTVietnameseScript;
				break;

			case ACP_JAPAN:
				WLocaleSetting::ts_SystemScript = kCTJapaneseScript;
				break;

			case ACP_SIMPLIFIED_CHINESE:
				WLocaleSetting::ts_SystemScript = kCTSimplifiedChineseScript;
				break;

			case ACP_KOREAN:
				WLocaleSetting::ts_SystemScript = kCTKoreanScript;
				break;

			case ACP_TRADITIONAL_CHINESE:
				WLocaleSetting::ts_SystemScript = kCTTraditionalChineseScript;
				break;
		}

/*
		// this is the old version of WLocaleSetting::GetSystemLocale()

		char language[128];
		char country[128];

		LCID localeID = GetUserDefaultLCID();
		GetLocaleInfo(localeID, LOCALE_SENGLANGUAGE, language, 128);
		GetLocaleInfo(localeID, LOCALE_SENGCOUNTRY, country, 128);

		TRACEFLOW_OBSOLETE("Old:Public", "LCID: %d\n", localeID);
		TRACEFLOW_OBSOLETE("Old:Public", "EngLanguageName: %s\n", language);
		TRACEFLOW_OBSOLETE("Old:Public", "EngCountryName: %s\n", country);

		WLocaleSetting::ts_SystemScript = LookupCountryID(localeID);

		ASSERT_MSG( WLocaleSetting::ts_SystemScript != kCTDontKnowScript, "LocaleSetting::GetSystemScript() - unknown system script." );
		if( WLocaleSetting::ts_SystemScript == kCTDontKnowScript )
			WLocaleSetting::ts_SystemScript = kCTRomanScript;
*/
	}

	return WLocaleSetting::ts_SystemScript;
}
