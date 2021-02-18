//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/localization/MLocaleSetting.cpp $
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

#include "MLocaleSetting.h"
#include "PMLocaleIds.h"
#include "IDResourceShell.h"

#include "CoreResTypes.h"
#include "IPMStream.h"
#include "StreamUtil.h"
#include "RsrcSpec.h"


#include "Trace.h"

#include "ShuksanCoolType.h"
#include "BuildNumber.h"
#include "FileUtils.h"

#include <Cocoa/Cocoa.h>

#define MTOOLBOX

#include "CAlert.h"

//========================================================================================
// METHODS MLocaleSetting
//========================================================================================
// ts_gLocaleSetting is modified only from within Initialize & GetSystemScript & that too only
// on the 1st call. Subsequent calls & access from other functions are read-only. The 1st call
// to Initialize & GetSystemScript happen at start-up, hence ts_gLocaleSetting would be accessed
// by threads in a read-only way.
static MLocaleSetting ts_gLocaleSetting;

//----------------------------------------------------------------------------------------
// MLocaleSetting::MLocaleSetting
//----------------------------------------------------------------------------------------

MLocaleSetting::MLocaleSetting() :
	fInitialized(kFalse),
	fLocale(k_enUS),
	fSystemScript(kCTDontKnowScript)
{
}

//----------------------------------------------------------------------------------------
// MLocaleSetting::SetLocale
//----------------------------------------------------------------------------------------

void MLocaleSetting::SetLocale(const PMLocaleId& locale)
{
	ts_gLocaleSetting.fLocale = locale;
	ts_gLocaleSetting.fInitialized = kTrue;
}

//----------------------------------------------------------------------------------------
// MLocaleSetting::Initialize
//----------------------------------------------------------------------------------------
void MLocaleSetting::Initialize()
{
	ASSERT (IDThreading::IsMainThreadDomain ());
	if (!ts_gLocaleSetting.fInitialized)
	{
		
		ts_gLocaleSetting.fInitialized = kTrue;
		
		// ----- Get the language from our plist. This is what apple's going to use for localizing so we might as well match.
		CFBundleRef bundle = ::CFBundleGetMainBundle();
		ASSERT_MSG(bundle != nil,"Failed to get main bundle!");
		
		CFStringRef versStr = (CFStringRef)::CFBundleGetValueForInfoDictionaryKey(bundle,kCFBundleDevelopmentRegionKey);

		char langStr[256];
		// Don't use CFStringGetCStringPtr because it fails if the UI is set to Czech. Bug 1243848
		bool16 isCorrectLangStr = ::CFStringGetCString(versStr, langStr, sizeof(langStr)-1, kCFStringEncodingMacRoman);
		
		ASSERT_MSG(isCorrectLangStr,"Failed to get language key from bundle. Defaulting to english UI");
		int16 uiLangValue = k_enUS;
		if(isCorrectLangStr)
		{
			if(std::strcmp(langStr,"English") == 0)
				uiLangValue = k_enUS;
			else if(std::strcmp(langStr,"British English") == 0) /// international english identified how?
				uiLangValue = k_enGB;
			else if(std::strcmp(langStr,"German") == 0)
				uiLangValue = k_deDE;
			else if(std::strcmp(langStr,"French") == 0)
				uiLangValue = k_frFR;
			else if(std::strcmp(langStr,"Japanese") == 0)
				uiLangValue = k_jaJP;
			else if(std::strcmp(langStr,"Spanish") == 0)
				uiLangValue = k_esES;
			else if(std::strcmp(langStr,"Portuguese") == 0)
				uiLangValue = k_ptBR;
			else if(std::strcmp(langStr,"Swedish") == 0)
				uiLangValue = k_svSE;
			else if(std::strcmp(langStr,"Danish") == 0)
				uiLangValue = k_daDK;
			else if(std::strcmp(langStr,"Dutch") == 0)
				uiLangValue = k_nlNL;
			else if(std::strcmp(langStr,"Italian") == 0)
				uiLangValue = k_itIT;
			else if(std::strcmp(langStr,"Norwegian") == 0)
				uiLangValue = k_nbNO;
			else if(std::strcmp(langStr,"Finnish") == 0)
				uiLangValue = k_fiFI;
			else if(std::strcmp(langStr,"Czech") == 0)
			{
				uiLangValue = k_csCZ;
				ts_gLocaleSetting.fSystemScript = kCTEastEuropeanRomanScript;
			}
			else if(std::strcmp(langStr,"Polish") == 0)
			{
				uiLangValue = k_plPL;
				ts_gLocaleSetting.fSystemScript = kCTEastEuropeanRomanScript;
			}
			else if(std::strcmp(langStr,"Greek") == 0)
			{
				uiLangValue = k_elGR;
				ts_gLocaleSetting.fSystemScript = kCTGreekScript;
			}
			else if(std::strcmp(langStr,"Hungarian") == 0)
			{
				uiLangValue = k_huHU;
				ts_gLocaleSetting.fSystemScript = kCTEastEuropeanRomanScript;
			}
			else if(std::strcmp(langStr,"Russian") == 0)
			{
				uiLangValue = k_ruRU;
				ts_gLocaleSetting.fSystemScript = kCTCyrillicScript;
			}
			else if(std::strcmp(langStr,"Turkish") == 0)
				uiLangValue = k_trTR;
			else if(std::strcmp(langStr,"Arabic") == 0)
			{
				uiLangValue = k_arAE;
				ts_gLocaleSetting.fSystemScript = kCTArabicScript;
			}
			else if(std::strcmp(langStr,"Hebrew") == 0)
			{
				uiLangValue = k_heIL;
				ts_gLocaleSetting.fSystemScript = kCTHebrewScript;
			}
			else if(std::strcmp(langStr,"Romanian") == 0)
			{
				uiLangValue = k_roRO;
				ts_gLocaleSetting.fSystemScript = kCTEastEuropeanRomanScript;
			}
			else if(std::strcmp(langStr,"Ukrainian") == 0)
			{
				uiLangValue = k_ukUA;
				ts_gLocaleSetting.fSystemScript = kCTCyrillicScript;
			}
			else if(std::strcmp(langStr,"zh_CN") == 0)
				uiLangValue = k_zhCN;
			else if(std::strcmp(langStr,"zh_TW") == 0)
				uiLangValue = k_zhTW;
			else if(std::strcmp(langStr,"Korean") == 0)
				uiLangValue = k_koKR;
			else if(std::strcmp(langStr,"sq_AL") == 0)
			{
				uiLangValue = k_sqAL;
				ts_gLocaleSetting.fSystemScript = kCTEastEuropeanRomanScript;
			}
			else
			{
				ASSERT_FAIL("Unknown kCFBundleDevelopmentRegionKey language. Defaulting to english UI");
			}
		}
				
		// ----- Get the feature set resource.
        // This is helping to figure out the application (ID / IC / IDS)
		IDResource featureSetRes = IDResourceShell::Get(RsrcSpec((PluginID)kApplicationPluginID, kFeatureSetRsrcType, 1));
		ASSERT_MSG(featureSetRes.IsValid(), "MLocaleSetting - can't find kFeatureSetRsrcType resource");
		int32 *featureSet = (int32 *)featureSetRes.Get();

		// ----- Initialize the global locale id with the feature set and the user interface Id.
		int32 fs = ((ResourceEndianWrapper32<int32>) *featureSet);
		ASSERT_MSG(fs > kFSBaseID,"Warning - FEAT resource has a strange feature set id");
//		ASSERT_MSG((*vers)->fRegionCode >= 0 && (*vers)->fRegionCode < kFSBaseID,"Warning - UI locale in vers resource has strange id");
        
		PMLocaleId locale((int16) fs, uiLangValue);
        
        // Read the user preferences for feature set from application preference file (applicationpreference.plist)
        // located in <Installation dir>/Presets/applicationpreference/
        // If the plist file (corresponding to application) does not exists, or plist reading fails, continue using the default feature set
        PMLocaleId preferenceLocale(0,0);
#if DEBUG
#else
        FileUtils::SetAppFolder();
#endif
        bool16 bPrefReadSucceed = GetPreference(locale, preferenceLocale); // Check the preferences file for FeatureSet
        if(bPrefReadSucceed == kTrue)
        {
            locale = PMLocaleId(preferenceLocale.GetFeatureSetId(), locale.GetUserInterfaceId());
        }
        
		ts_gLocaleSetting.fLocale = locale;
	}
}

//----------------------------------------------------------------------------------------
// MLocaleSetting::GetLocale
//----------------------------------------------------------------------------------------

PMLocaleId MLocaleSetting::GetLocale()
{
	if (!ts_gLocaleSetting.fInitialized)
		MLocaleSetting::Initialize();

	return ts_gLocaleSetting.fLocale;
}

//----------------------------------------------------------------------------------------
// MLocaleSetting::GetSystemLocale
//----------------------------------------------------------------------------------------

PMLocaleId MLocaleSetting::GetSystemLocale()
{
	const int16 scriptID = MLocaleSetting::GetSystemScript();
	return scriptLookup(scriptID);
}

//----------------------------------------------------------------------------------------
// MLocaleSetting::scriptLookup
//----------------------------------------------------------------------------------------

PMLocaleId MLocaleSetting::scriptLookup(int script)
{
	// This should be soft-coded sometime in the near future.
	int32 app = GetLocale().GetProductFS() << 16;	// app code in high word
	switch (script)
    {
		case smRoman:		return PMLocaleId(app | kRomanLanguageFS, k_enUS);
		case smJapanese:	return PMLocaleId(app | kJapaneseLanguageFS, k_jaJP);
		case smSimpChinese: return PMLocaleId(app | kJapaneseLanguageFS, k_zhCN);
		case smTradChinese: return PMLocaleId(app | kJapaneseLanguageFS, k_zhTW);
		case smKorean:		return PMLocaleId(app | kJapaneseLanguageFS, k_koKR);
		default:			return PMLocaleId(app | kRomanLanguageFS, k_enUS);
    }
}

//---------------------------------------------------------------------------------------
// MLocaleSetting::GetSystemScript
//----------------------------------------------------------------------------------------

int16 MLocaleSetting::GetSystemScript()
{
	if( ts_gLocaleSetting.fSystemScript == kCTDontKnowScript )
	{
		// CC DeCarb: switched this from calling Get-Application-TextEncoding to CFStringGetSystemEncoding since
		//	we want the system's preferred input language, not the application's. See GetLocale vs GetSystemLocale above.
		//	Our original code used GetAppFont, which referred to the system wide "application font".
		//	The user's preferred language setting should be a better source for the System script/encoding. 
		//
		// Get-Application-TextEncoding:
		//	Your application needs to use the application text encoding when it creates a CFString from text 
		//	stored in Resource Manager resources. Typically the text uses a Mac encoding such as MacRoman or MacJapanese.
		//
		// CFStringGetSystemEncoding:
		//	This function returns the default text encoding used by the OS when it creates strings.
		//	In Mac OS X, this encoding is determined by the user's preferred language setting.
		//	The preferred language is the first language listed in the International pane of the System Preferences.
		
		TextEncoding encoding = ::CFStringGetSystemEncoding();
		ScriptCode script;
		::RevertTextEncodingToScriptInfo(encoding, &script, NULL, NULL);
		
		ts_gLocaleSetting.fSystemScript = script;
#ifdef qME
		const int systemEncoding = encoding;
		ts_gLocaleSetting.fSystemScript = systemEncoding;
#endif
		ASSERT_MSG( ts_gLocaleSetting.fSystemScript != kCTDontKnowScript, "LocaleSetting::GetSystemScript() - unknown system script." );
		if( ts_gLocaleSetting.fSystemScript == kCTDontKnowScript )
			ts_gLocaleSetting.fSystemScript = kCTRomanScript;
	}

	return ts_gLocaleSetting.fSystemScript;
}

//---------------------------------------------------------------------------------------
// MLocaleSetting::GetPreferenceFileName
//----------------------------------------------------------------------------------------

bool16  MLocaleSetting::GetPreferenceFileName(const PMLocaleId& locale, PMString& outStrPrefFileName)
{
    bool bRetVal = kFalse;

    // Create file name preference.plist
    PMString strPresetFolderName ("Presets");
    strPresetFolderName.SetTranslatable(kFalse);
    PMString strPrefFileName ("applicationpreference.plist");
    strPrefFileName.SetTranslatable(kFalse);
    PMString strPrefFolderName ("applicationpreferences");
    strPrefFolderName.SetTranslatable(kFalse);
    
    PMString strAppName;
    strAppName.SetTranslatable(kFalse);
    
    if (locale.IsProductFS(kInDesignProductFS))
    {
        strAppName = PMString("indesign");
    }
    else if (locale.IsProductFS(kInCopyProductFS))
    {
        strAppName = PMString("incopy");
    }
    else
    {
        strAppName = PMString("indesignserver");
    }
    
    IDFile appDir;
    bool16 appFolderObtained = FileUtils::GetAppInstallationFolder(&appDir);
    ASSERT_MSG(appFolderObtained, "Cannot locate Application Preference Directory. \nDirectory should be located at <Installation dir>/Presets/applicationpreferences");
    if( appFolderObtained == kTrue )
    {
        appDir.ResolvePathAliases();

        AString astrPresetsThemePath( appDir.GetPath().GetPath() );
        PMString strPresetsThemePath(astrPresetsThemePath.GrabWString(), astrPresetsThemePath.UTF16Count());
        strPresetsThemePath.Append(PMString("/"));  // mac version of GetDirectorySeperator() returns ":" for separator
        strPresetsThemePath.Append(strPresetFolderName);
        strPresetsThemePath.Append(PMString("/"));  // mac version of GetDirectorySeperator() returns ":" for separator
        strPresetsThemePath.Append(strPrefFolderName);
        strPresetsThemePath.Append(PMString("/"));  // mac version of GetDirectorySeperator() returns ":" for separator
        strPresetsThemePath.Append(strAppName);
        strPresetsThemePath.Append(PMString("/"));  // mac version of GetDirectorySeperator() returns ":" for separator
        strPresetsThemePath.Append(strPrefFileName);

        outStrPrefFileName =  strPresetsThemePath;
        bRetVal = kTrue;
    }

    return bRetVal;
}

//---------------------------------------------------------------------------------------
// MLocaleSetting::ReadPreferenceFile
//----------------------------------------------------------------------------------------

bool16 MLocaleSetting::ReadPreferenceFile(const PMLocaleId& locale, int32& outFeatureSet)
{
    bool16 bRetVal = kFalse;

    PMString strPrefFileName;
    if(GetPreferenceFileName(locale, strPrefFileName))
    {
        //Read Pref file Content and obtain FeatureSet
        CFStringRef strPrefFileNameCFString = strPrefFileName.CreateCFString();
        NSData* prefData = [[NSFileManager defaultManager] contentsAtPath:(NSString*) strPrefFileNameCFString];
        if(prefData != nil)
        {
            NSString * errorDesc = nil;
            NSPropertyListFormat plFormat;
            NSDictionary *prefDictionary = (NSDictionary*)[NSPropertyListSerialization propertyListFromData:prefData
                                                                                           mutabilityOption:NSPropertyListMutableContainersAndLeaves
                                                                                                     format:&plFormat
                                                                                           errorDescription:&errorDesc];
            
            if(prefDictionary != nil)
            {
                outFeatureSet = [[prefDictionary valueForKey:@kFeatureSetStr] intValue];
                bRetVal = kTrue;
            }
        }
        CFRelease(strPrefFileNameCFString);
    }

    return bRetVal;
}

//---------------------------------------------------------------------------------------
// MLocaleSetting::GetPreference
//----------------------------------------------------------------------------------------

bool16 MLocaleSetting::GetPreference(const PMLocaleId& locale, PMLocaleId& newLocale)
{
    bool16 bRetVal = kFalse;
    int32 featureSetID = 0;
    
    // Check the application preferences file
    if(ReadPreferenceFile(locale, featureSetID))
    {
        newLocale = PMLocaleId((int16) featureSetID, locale.GetUserInterfaceId());
        
        // put a safelty check to validate the feature set for application, so that InDesign's feature set does get set on InCopy's feature set
        if(locale.GetProductFS() == newLocale.GetProductFS())
        {
            bRetVal = kTrue;
        }
    }
    
    return bRetVal;
}
