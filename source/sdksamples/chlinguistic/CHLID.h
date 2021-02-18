//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLID.h $
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
//  Defines IDs used by the CHL plug-in.
//  
//========================================================================================

#ifndef __CHLID_h__
#define __CHLID_h__

#include "SDKDef.h"

// Company:
#define kCHLCompanyKey		kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCHLCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kCHLPluginName		"CHLinguistic" // Name of this plug-in.
#define kCHLPrefixNumber	0x48C00 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCHLVersion			"3.0" // Version of this plug-in (for the About Box).
#define kCHLAuthor			"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCHLPrefixNumber above to modify the prefix.)
#define kCHLPrefix			RezLong(kCHLPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kCHLStringPrefix	SDK_DEF_STRINGIZE(kCHLPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCHLPluginID, kCHLPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kCHLActionComponentBoss, kCHLPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kClassIDSpace, kCHLinguisticBoss, kCHLPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCHLSpellingBoss, kCHLPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCHLUserDictBoss, kCHLPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCHLUserDictContentHandlerBoss, kCHLPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCHLThesaurusBoss, kCHLPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCHLErrorStringServiceBoss, kCHLPrefix + 9)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICHLFILENAMETABLE, kCHLPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHLINGUISTICDATA, kCHLPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHLUSERDICTUTILS, kCHLPrefix + 2)


// Implementation IDs:
//DECLARE_PMID(kImplementationIDSpace, kCHLActionComponentImpl, kCHLPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kCHLServiceProviderImpl, kCHLPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCHLFileNameTableImpl, kCHLPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCHLSpellingMgrImpl, kCHLPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCHLSpellingServiceImpl, kCHLPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictMgrImpl, kCHLPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictServiceImpl, kCHLPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictImpl, kCHLPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictIteratorImpl, kCHLPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCHLDataImpl, kCHLPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictUtilsImpl, kCHLPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCHLUserDictContentHandlerImpl, kCHLPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCHLThesaurusMgrImpl, kCHLPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCHLThesaurusImpl, kCHLPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCHLErrorStringServiceImpl, kCHLPrefix + 14)


//Errors
DECLARE_PMID(kErrorIDSpace, kIncorrectSpaceError,		kCHLPrefix + 1)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCHLAboutActionID, kCHLPrefix + 0)

// WidgetIDs:

// "About Plug-ins" sub-menu:
#define kCHLAboutMenuKey			kCHLStringPrefix "kCHLAboutMenuKey"
#define kCHLAboutMenuPath			kSDKDefStandardAboutMenuPath kCHLCompanyKey

// Other StringKeys:
#define kCHLAboutBoxStringKey				kCHLStringPrefix "kCHLAboutBoxStringKey"

// Alert StringKeys:
#define kCHLSpellingMgrInstallFailedKey		kCHLStringPrefix "kCHLSpellingMgrInstallFailed"
#define kCHLFileNameTableInstallFailedKey	kCHLStringPrefix "kCHLFileNameTableInstallFailed"
#define kCHLMissingUserDictionaryInitKey	kCHLStringPrefix "kCHLMissingUserDictionaryInitKey"

// Linguistic StringsKeys:
#define kCHShortName						"CodeHawgs"

#define kCHPrimaryLanguageNameBulgarian 	"Bulgarian"
#define kCHSubLanguageNameBulgarianNull 	""

#define kCHLanguageNameBulgarianKey 		kCHLStringPrefix kCHPrimaryLanguageNameBulgarian

#define kCHCoreFileNameBulgarian 			"BULG.DIC"
#define kCHHyphFileNameBulgarian 			"BULG.HYP"
#define kCHUserDictFileNameBulgarian 		"BULG.UDC"
#define kCHThesaurusFileNameBulgarian 		"BULG.THS"

#define kCHPrimaryLanguageNameHungarian 	"Hungarian"
#define kCHSubLanguageNameHungarianNull 	""

#define kCHLanguageNameHungarianKey 		kCHLStringPrefix kCHPrimaryLanguageNameHungarian

#define kCHCoreFileNameHungarian 			"HUNG.DIC"
#define kCHHyphFileNameHungarian 			"HUNG.HYP"
#define kCHUserDictFileNameHungarian 		"HUNG.UDC"
#define kCHThesaurusFileNameHungarian 		"HUNG.THS"

#define kCHCoreFileNameAramaic 				"ARAM.DIC"
#define kCHHyphFileNameAramaic 				"ARAM.HYP"
#define kCHUserDictFileNameAramaic 			"ARAM.UDC"
#define kCHThesaurusFileNameAramaic 		"ARAM.THS"

#define kCHCoreFileNameEnglishZambia 		"ENGZAM.DIC"
#define kCHHyphFileNameEnglishZambia 		"ENGZAM.HYP"
#define kCHUserDictFileNameEnglishZambia 	"ENGZAM.UDC"
#define kCHThesaurusFileNameEnglishZambia 	"ENGZAM.THS"

#define kCHCoreFileNameBembaZambia 			"BEMZAM.DIC"
#define kCHHyphFileNameBembaZambia 			"BEMZAM.HYP"
#define kCHUserDictFileNameBembaZambia 		"BEMZAM.UDC"
#define kCHThesaurusFileNameBembaZambia 	"BEMZAM.THS"

#define kCHCoreFileNameBembaBotswana		"BEMBOT.DIC"
#define kCHHyphFileNameBembaBotswana 		"BEMBOT.HYP"
#define kCHUserDictFileNameBembaBotswana 	"BEMBOT.UDC"
#define kCHThesaurusFileNameBembaBotswana 	"BEMBOT.THS"

// Path to our linguistic data files folder that lives under
// the application folder. 
#ifdef MACINTOSH
	#define kCHLinguisticFilesSubFolder		":Plug-Ins:Dictionaries:codehawgs:"
#endif
#ifdef WINDOWS
	#define kCHLinguisticFilesSubFolder		"\\Plug-Ins\\Dictionaries\\codehawgs\\"
#endif

// Initial data format version numbers
#define kCHLFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kCHLFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kCHLCurrentMajorFormatNumber kCHLFirstMajorFormatNumber // most recent major format change
#define kCHLCurrentMinorFormatNumber kCHLFirstMinorFormatNumber // most recent minor format change

#endif // __CHLID_h__

// End, CHLID.h.


