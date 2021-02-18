//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/common/SDKDef.h $
//  
//  Owner: Adobe Developer Technologies
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
//  
//  This file contains common defines and macros for SDK plug-ins.
//  A standard prefix "kSDKDef" has been applied to all symbol names
//  so SDKDef symbols can be identified easily in source code. A set
//  of standard symbol suffixes such as "VersionNumber" and "ResourceID"
//  have been applied to indicate the different types of symbol defined
//  in the file.
//  
//  This file obsoletes the SDKDefines.h header from the InDesign 1.x SDK.
//  The INDESIGN_1X_ROMAN_API compile time symbol used by SDKDefines.h
//  to factor out differences between the InDesign 1.x And InDesign 1.0J 
//  APIs is obsolete. A single build of the application supports both Roman 
//  and Japanese APIs.
//  
//========================================================================================

#ifndef __SDKDef_h__
#define __SDKDef_h__

#include "FormatNumber.h"

/*
// Product (Host) and Plug-in Default Version numbers:
*/
#define kSDKDefHostMajorVersionNumber		kMajorVersionNumber /* Was kHostMajorVersionNumber in obsolete SDKDefines.h.*/
#define kSDKDefHostMinorVersionNumber		kMinorVersionNumber /* Was kHostMinorVersionNumber in obsolete SDKDefines.h. */
#define kSDKDefPlugInMajorVersionNumber		kMajorVersionNumber /* Was kPlugInMajorVersionNumber in obsolete SDKDefines.h. */
#define kSDKDefPlugInMinorVersionNumber		kMinorVersionNumber /* Was kPlugInMinorVersionNumber in obsolete SDKDefines.h. */
#define kSDKDefPlugInMajorVersionNumberForResource kMajorVersionNumberForResource
#define kSDKDefPlugInMinorVersionNumberForResource kMinorVersionNumberForResource
#define kSDKDefPlugInStepVersionNumberForResource  0
/*
// SDK persistent data format version numbers
*/
#define kSDKDef_10_PersistMajorVersionNumber	kK2MajorFormatNumber
#define kSDKDef_10_PersistMinorVersionNumber	kLastK2MinorVersionNumber
#define kSDKDef_15_PersistMajorVersionNumber	kSherpaMajorFormatNumber
#define kSDKDef_15_PersistMinorVersionNumber	0
#define kSDKDef_1J_PersistMajorVersionNumber	kHotakaMajorFormatNumber
#define kSDKDef_1J_PersistMinorVersionNumber	kHotakaInitialMinorFormatNumber
#define kSDKDef_20_PersistMajorVersionNumber	kAnnaMajorFormatNumber
#define kSDKDef_20_PersistMinorVersionNumber	kAnnaInitialMinorFormatNumber
#define kSDKDef_30_PersistMajorVersionNumber	kDragontailMajorFormatNumber
#define kSDKDef_30_PersistMinorVersionNumber	kDragontailInitialMinorFormatNumber
#define kSDKDef_40_PersistMajorVersionNumber	kFiredrakeMajorFormatNumber
#define kSDKDef_40_PersistMinorVersionNumber	kFiredrakeInitialMinorFormatNumber
#define kSDKDef_50_PersistMajorVersionNumber	kCobaltMajorFormatNumber
#define kSDKDef_50_PersistMinorVersionNumber	kCobaltInitialMinorFormatNumber
#define kSDKDef_60_PersistMajorVersionNumber	kBasilMajorFormatNumber
#define kSDKDef_60_PersistMinorVersionNumber	kBasilInitialMinorFormatNumber
#define kSDKDef_70_PersistMajorVersionNumber	kRocketMajorFormatNumber
#define kSDKDef_70_PersistMinorVersionNumber	kRocketInitialMinorFormatNumber

/*
// ResourceIDs:
// Used to identify ODFRC resources and platform specific resources within the 
// local plug-in resource space.
*/
#define kSDKDefIconInfoResourceID			180 // Was kSDKIconInfoResourceID in obsolete SDKDefines.h.
#define kSDKDefIconInfoRolloverResourceID	180 // for rollover state
#define kSDKDefGenericIconInfoResourceID			181 // A generic icon.
#define kSDKDefIconGenericRolloverResourceID	181 // for rollover state
#define kSDKDefMenuResourceID				200 // Was kSDKMenuResourceID in obsolete SDKDefines.h.
#define kSDKDefDialogResourceID				kSDKDefMenuResourceID + 50
#define kSDKDefStringsResourceID			kSDKDefMenuResourceID + 100
#define kSDKDefStringsNoTransResourceID		kSDKDefMenuResourceID + 150
#define kSDKDefActionResourceID				kSDKDefMenuResourceID + 200
#define kSDKDefPluginVersionResourceID 		kSDKDefMenuResourceID + 250
#define kSDKDefProductVersionResourceID			kSDKDefMenuResourceID + 260
#define kSDKDefDirectiveListResourceID			kSDKDefMenuResourceID + 270
#define kSDKDefSchemaFormatNumberResourceID		kSDKDefMenuResourceID + 280
#define kSDKDefClassDescriptionTableResourceID kSDKDefMenuResourceID + 300
#define kSDKDefFactoryListResourceID 		kSDKDefMenuResourceID + 350
#define kSDKDefErrorStringResourceID		kSDKDefMenuResourceID + 450
#define kSDKDefPanelResourceID				kSDKDefMenuResourceID + 500
#define kSDKDefPluginDependencyResourceID	kSDKDefMenuResourceID + 550
#define kSDKDefIDListResourceID				kSDKDefMenuResourceID + 600 // used by selectable dialogs 
#define kSDKDefIDListPairResourceID			kSDKDefMenuResourceID + 650 // used by selectable dialogs)
#define kSDKDefSchemaListResourceID			kSDKDefMenuResourceID + 700
#define kSDKDefKitListResourceID			kSDKDefMenuResourceID + 750

/*
// "Plug-ins" and "About Plug-ins" menus:
//
// Responsibility for the creation, positioning and string localisation of the "Plug-ins" menu  in the main menu bar and 
// "About Plug-ins" sub-menu under the Help Menu (Win) or Apple menu (Mac) has transitioned into the core application. 
// InDesign 2.0 SDK plug-ins do not have to create these menu items or provide localized string translations for the 
// strings.
//
// Note that the localised symbols, kMenuPlugIns_enUS, kMenuAbout_enUS et al, defined in SDKDefines.h are obsolete
// since the application localises these strings.
//
*/
#define kSDKDefPlugInsMenuApplicationKey	"Plugin_Menu" // Was kMenuPlugIns in obsolete SDKDefines.h.
#define kSDKDefAboutMenuApplicationKey		"AboutPlugins" // Was kMenuAbout in obsolete SDKDefines.h.

/*
// MenuPaths:
*/
#define kSDKDefPlugInsStandardMenuPath		"Main:" kSDKDefPlugInsMenuApplicationKey ":" // Was kMenuStandardPlugIns in obsolete SDKDefines.h.
#ifdef MACINTOSH
	#define kSDKDefStandardAboutMenuPath	"Main:AppleMenu:" kSDKDefAboutMenuApplicationKey ":" // Was kMenuStandardAbout in obsolete SDKDefines.h.
#else // PC
	#define kSDKDefStandardAboutMenuPath	"Main:&Help:" kSDKDefAboutMenuApplicationKey ":" // Was kMenuStandardAbout in obsolete SDKDefines.h.
#endif // MACINTOSH
#define kSDKDefPreferencesStandardMenuPath	"Main:&Edit:Preferences" // Was kMenuStandardPreferences in obsolete SDKDefines.h.
#define kSDKDefPrefsShortStandardMenuPath	"&Edit:Preferences:" // Was kMenuStandardShortPrefs in obsolete SDKDefines.h.
#define kSDKDefDelimitMenuPath				":" // Was kMenuDelim if anyone knows am API include that does this we should use it instead.
#define kSDKDefDelimiterAndSeparatorPath	":-" // Postfix for the menu path to make it explicit an item is a separator.
#define kSDKDefAlphabeticPosition 1.0 // Use this position for all your menu items to have the app decide positioning.

/*
// Other MenuKeys and MenuValues:
*/
// Use this for a panel or special menu:
#define kSDKDefAboutThisPlugInMenuKey	"About this pl&ug-in..." // Was kAboutThisPlugIn in obsolete SDKDefines.h.
#define kSDKDefAboutThisPlugInMenuValue_enUS	"About this pl&ug-in..." // Was kMenuAboutThisPlugIn_enUS in obsolete SDKDefines.h.
#define kSDKDefAboutThisPlugInMenuValue_enGB	"About this pl&ug-in..." // Was kMenuAboutThisPlugIn_enGB in obsolete SDKDefines.h.
#define kSDKDefAboutThisPlugInMenuValue_jaJP	"このプラグインについて…(&U)" // Was kMenuAboutThisPlugIn_jaJP in obsolete SDKDefines.h.
#define kSDKDefAboutThisPlugInMenuValue_frFR	"About this pl&ug-in..."	// Was kMenuAboutThisPlugIn_frFR in obsolete SDKDefines.h.
#define kSDKDefAboutThisPlugInMenuValue_deDE	"About this pl&ug-in..." // Was kMenuAboutThisPlugIn_deDE in obsolete SDKDefines.h.	
#define kSDKDefAboutThisPlugInMenuValue_esES	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_ptBR	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_svSE	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_daDK	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_nlNL	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_itIT	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_nbNO	"About this pl&ug-in..." // NEW
#define kSDKDefAboutThisPlugInMenuValue_fiFI	"About this pl&ug-in..." // NEW

// Use this for a panel or special menu:
#define kSDKDefOptionsMenuKey			"SDK Options..." // Was kMenuOptions in obsolete SDKDefines.h.
#define kSDKDefOptionsMenuValue_enUS			"Options..." // Was kMenuOptions_enUS in obsolete SDKDefines.h.
#define kSDKDefOptionsMenuValue_enGB			"Options..." // Was kMenuOptions_enGB in obsolete SDKDefines.h.
#define kSDKDefOptionsMenuValue_jaJP			"オプション..." // Was kMenuOptions_jaJP in obsolete SDKDefines.h.
#define kSDKDefOptionsMenuValue_frFR			"Options..." // Was kMenuOptions_frFR in obsolete SDKDefines.h.	
#define kSDKDefOptionsMenuValue_deDE			"Options..." // Was kMenuOptions_deDE in obsolete SDKDefines.h.
#define kSDKDefOptionsMenuValue_esES			"Options..." // NEW
#define kSDKDefOptionsMenuValue_ptBR			"Options..." // NEW
#define kSDKDefOptionsMenuValue_svSE			"Options..." // NEW
#define kSDKDefOptionsMenuValue_daDK			"Options..." // NEW
#define kSDKDefOptionsMenuValue_nlNL			"Options..." // NEW
#define kSDKDefOptionsMenuValue_itIT			"Options..." // NEW
#define kSDKDefOptionsMenuValue_nbNO			"Options..." // NEW
#define kSDKDefOptionsMenuValue_fiFI			"Options..." // NEW

// The SDK company name under for sample code sub-menus:
#define kSDKDefPlugInCompanyKey		"SDK" // Was kSDKDefPlugInCompany="Adobe_Developer_Support"  in obsolete SDKDefines.h.
#define kSDKDefPlugInCompanyValue	"SDK"

// The default alert shown in the Missing Plug-in dialog when a doc is opened containg data from a missing plug-in.
#define kSDKDefMissingPluginAlertValue		"Third party developers can explain how to get hold of their missing plug-in here"

/*
// MenuDef Resource flags:
*/
// Flag to identify an action as editable in Keyboard Shortcut Editor:
#define kSDKDefInvisibleInKBSCEditorFlag kFalse // Was kInvisibleInKBSCEditor in obsolete SDKDefines.h.
#define kSDKDefVisibleInKBSCEditorFlag kTrue // Was kVisibleInKBSCEditor in obsolete SDKDefines.h.

// Flag to identify a dynamic menu item:
#define kSDKDefIsNotDynamicMenuFlag kFalse // Was kIsNotDynamicMenu in obsolete SDKDefines.h.
#define kSDKDefIsDynamicMenuFlag kTrue // Was kIsDynamicMenu in obsolete SDKDefines.h.

// Keyboard shortcut editor areas:
#define kSDKPluginActionArea					"KBSCE SDK Plug-Ins" // KBSCE key for special SDK related KBSC's
#define kSDKPluginActionArea_enUS				"SDK Plug-Ins [US]"
#define kSDKPluginActionArea_enGB				"SDK Plug-Ins [GB]"
#define kSDKPluginActionArea_jaJP				"SDK プラグイン [JP]"
#define kSDKPluginActionArea_frFR				"SDK Plug-Ins [FR]"
#define kSDKPluginActionArea_deDE				"SDK Plug-Ins [DE]"
#define kSDKPluginActionArea_esES				"SDK Plug-Ins [ES]"
#define kSDKPluginActionArea_ptBR				"SDK Plug-Ins [BR]"
#define kSDKPluginActionArea_svSE				"SDK Plug-Ins [SE]"
#define kSDKPluginActionArea_daDK				"SDK Plug-Ins [DK]"
#define kSDKPluginActionArea_nlNL				"SDK Plug-Ins [NL]"
#define kSDKPluginActionArea_itIT				"SDK Plug-Ins [IT]"
#define kSDKPluginActionArea_nbNO				"SDK Plug-Ins [NO]"
#define kSDKPluginActionArea_fiFI				"SDK Plug-Ins [FI]"
#define kMiscellaneousArea						kOtherActionArea    /* TO BE OBSOLETED - please use kOtherActionArea instead */

/*
// About Box:
// Standard string value displayed in the About Box. You should personalise your
// plug-in by prefixing kSDKDefAboutBoxStandardValue with your plug-in name, version 
// and author.
*/
#define kSDKDefCopyrightStandardValue 		"Copyright 1999-2020 Adobe. All Rights Reserved."
#define kSDKDefPartnersStandardValue_enUS 	"http://www.adobe.com/partners.html"
#define kSDKDefPartnersStandardValue_jaJP	"http://www.adobe.com/partners.html"
#define kSDKDefPartnersStandardValue_enGB 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_deDE 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_frFR 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_esES 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_ptBR 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_svSE 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_daDK 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_nlNL 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_itIT 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_nbNO 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_fiFI 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_koKR 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_zhCN 	kSDKDefPartnersStandardValue_enUS
#define kSDKDefPartnersStandardValue_zhTW 	kSDKDefPartnersStandardValue_enUS

/*
// Application String Keys:
// You do not need to provide translations for these keys in your string 
// translation tables since they are already provided by the application.
*/
// Buttons:
#define kSDKDefOKButtonApplicationKey		"OK" // Was kButtonOK in obsolete SDKDefines.h.
#define kSDKDefCancelButtonApplicationKey	"Cancel" // Was kButtonCancel in obsolete SDKDefines.h.
#define kSDKDefResetButtonApplicationKey	"Reset" // Was kButtonReset in obsolete SDKDefines.h.
#define kSDKDefApplyButtonApplicationKey	"Apply" // Was kButtonApply in obsolete SDKDefines.h.
#define kSDKDefPreviousButtonApplicationKey "Pre&v"// Was kButtonPrevious in obsolete SDKDefines.h.
#define kSDKDefNextStandardButtonApplicationKey "Ne&xt" // Was kButtonNext in obsolete SDKDefines.h.

// Colors:
#define kSDKDefBlackApplicationKey	"Black" // Was kColorBlack in obsolete SDKDefines.h.
#define kSDKDefRedApplicationKey	"Red" // Was kColorRed in obsolete SDKDefines.h.
#define kSDKDefGreenApplicationKey	"Green" // Was kColorGreen in obsolete SDKDefines.h.
#define kSDKDefBlueApplicationKey	"Blue" // Was kColorBlue in obsolete SDKDefines.h.
#define kSDKDefOrangeApplicationKey	"Orange" // Was kColorOrange in obsolete SDKDefines.h.
#define kSDKDefPurpleApplicationKey	"Purple" // Was kColorPurple in obsolete SDKDefines.h.
#define kSDKDefVioletApplicationKey	"Violet" // Was kColorViolet in obsolete SDKDefines.h.
#define kSDKDefIndigoApplicationKey	"Indigo" // Was kColorIndigo in obsolete SDKDefines.h.
#define kSDKDefYellowApplicationKey	"Yellow" // Was kColorYellow in obsolete SDKDefines.h.
#define kSDKDefWhiteApplicationKey	"White" // Was kColorWhite in obsolete SDKDefines.h.

/*
// Stringizing Macros:
// SDK_DEF_STRINGIZE expands the macro parameter and then stringizes it
// using SDK_DEF_PRIVATE_STRINGIZE. Note that the two levels of macros
// are required to achieve this. Use it like this...
//
// #define kMyPluginNamePrefixNumber 0x47700
// #define kMyPluginNameStringPrefix SDK_DEF_STRINGIZE(kMyPluginNamePrefixNumber)
//
// ...to generate the string equivalent of a #define symbol. 
// 
// In the example shown kMyPluginNameStringPrefix expands into the string "0x47700" 
// not "kMyPluginNamePrefixNumber". The SDK_DEF_STRINGIZE parameter is expanded 
// because SDK_DEF_STRINGIZE does not specify stringizing or concatenation of the 
// parameter. The result then forms the actual argument for SDK_DEF_PRIVATE_STRINGIZE.
// SDK_DEF_PRIVATE_STRINGIZE uses its parameter without expansion because it 
// performs stringizing but it cannot prevent or undo the expansion already done by 
// SDK_DEF_STRINGIZE.
*/
#define SDK_DEF_PRIVATE_STRINGIZE(s) #s
#define SDK_DEF_STRINGIZE(s) SDK_DEF_PRIVATE_STRINGIZE(s)

/*
// Version Number String macro:
// Used to create a string for the PluginVersion resource.
// This is provideded only as a convenience. The PluginVersion field after the FeatureSet array
// can contain any string, but has a default, SDK samples will contain a string
// made up of the major.minor.step.build  numbers. e.g. "3.0.0.385"
*/
#define SDK_DEF_MAKE_VERSIONSTRING(ver_maj, ver_min, ver_step, ver_build) SDK_DEF_STRINGIZE(ver_maj)"." SDK_DEF_STRINGIZE(ver_min)"." SDK_DEF_STRINGIZE(ver_step)"." SDK_DEF_STRINGIZE(ver_build)

/*
// Plug-in version string used in About box. In the debug build, we append 'D' at the end of the version string.
*/
#ifdef DEBUG
#define kSDKDefPluginVersionString SDK_DEF_MAKE_VERSIONSTRING(kSDKDefPlugInMajorVersionNumberForResource, kSDKDefPlugInMinorVersionNumberForResource, kSDKDefPlugInStepVersionNumberForResource, kBuildNumber)"D"
#else
#define kSDKDefPluginVersionString SDK_DEF_MAKE_VERSIONSTRING(kSDKDefPlugInMajorVersionNumberForResource, kSDKDefPlugInMinorVersionNumberForResource, kSDKDefPlugInStepVersionNumberForResource, kBuildNumber) 
#endif

/*
//	Writing script values
//	For the most part, the names of these enum line up with the UNICODE 
//	Consortium's definition of writing scripts. 
//	Refer to http://www.unicode.org/unicode/uni2book/u2.html under "Chapters"
//	These are values for the "script" parameter in various 
//	UNICODE, string, and font related classes and interfaces. 
//	They include the following: 
//		ICompositeFont
//		IEncodingUtils
//		IFontFamily
//		IFontMgr
//		IKeyboard
//		ILanguage
//		IPMFont
//		ITextUtils
//		IWaxRenderData
//		LocaleSetting (MLocaleSetting.h, WLocaleSetting.h)
//		PlatformChar
//		PMString
//		PMTextUtils
//		(there may be more...)
*/
enum	
{
	kSDKRomanScript,
	kSDKJapaneseScript,
	kSDKTraditionalChineseScript,
	kSDKKoreanScript,
	kSDKArabicScript,
	kSDKHebrewScript,
	kSDKGreekScript,
	kSDKCyrillicScript,
	kSDKRightLeftScript,
	kSDKDevanagariScript,
	kSDKGurmukhiScript,
	kSDKGujaratiScript,
	kSDKOriyaScript,
	kSDKBengaliScript,
	kSDKTamilScript,
	kSDKTeluguScript,
	kSDKKannadaScript,
	kSDKMalayalamScript,
	kSDKSinhaleseScript,
	kSDKBurmeseScript,
	kSDKKhmerScript,
	kSDKThaiScript,
	kSDKLaotianScript,
	kSDKGeorgianScript,
	kSDKArmenianScript,
	kSDKSimplifiedChineseScript,
	kSDKTibetanScript,
	kSDKMongolianScript,
	kSDKGeezScript,
	kSDKEastEuropeanRomanScript,
	kSDKVietnameseScript,
	kSDKExtendedArabicScript,
	
	/* Count of above writing scripts (not a valid writing script value) */
	kSDKScriptCount,

	/* Font script not known (also a wildcard = use the platform default) */
	kSDKDontKnowScript = -1 
};

/*
// These definitions replace the ones from OMTypes.h.  Previously, IDs were base types
// but are now classes.  Consequently, these were no longer defined for ODFRC.
// kTrue and kFalse are (ODFRC) defined in PMTypes.h
*/
#ifdef __ODFRC__

#define kInvalidUID 0
#define kInvalidWidgetID 0
#define kInvalidClass 0
#define kInvalidPlugin 0
#define kInvalidImpl 0
#define kInvalidService 0
#define kInvalidInterfaceID 0
#define kInvalidKitViewID 0
#define kInvalidActionID 0
#define kInvalidFileTypeInfoID 0

#endif // __ODFRC__

#endif // __SDKDef_h__
