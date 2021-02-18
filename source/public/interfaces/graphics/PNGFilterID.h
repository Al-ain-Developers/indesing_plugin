//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PNGFilterID.h $
//  
//  Owner: Sdu 
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
//  Contains IDs used by the Portable Network Graphics (PNG) format filter
//  
//========================================================================================

#ifndef __PNGFilterID__
#define __PNGFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPNGFilterPrefix_obsolete		RezLong(0x46b00)
#define kPNGFilterPrefix				RezLong(0x13c00)

// <Start IDC>
// PluginID
#define kPNGFilterPluginName			"PNG Import Filter"
DECLARE_PMID(kPlugInIDSpace, kPNGFilterPluginID_obsolete, kPNGFilterPrefix_obsolete + 1)
DECLARE_PMID(kPlugInIDSpace, kPNGFilterPluginID, kPNGFilterPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kPNGImageReadFormatBoss, kPNGFilterPrefix +  1)
DECLARE_PMID(kClassIDSpace, kPNGErrorStringServiceBoss, kPNGFilterPrefix +  2)
DECLARE_PMID(kClassIDSpace, kPNGExportProviderBoss, kPNGFilterPrefix +  3)
DECLARE_PMID(kClassIDSpace, kPNGFilterConversionBoss, kPNGFilterPrefix +  4)
DECLARE_PMID(kClassIDSpace, kSetPNGPrefsCmdBoss, kPNGFilterPrefix +  5)
DECLARE_PMID(kClassIDSpace, kPNGImageWriteFormatBoss, kPNGFilterPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPNGExportCommandBoss, kPNGFilterPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPNGExportSetPrefsCommandBoss,	kPNGFilterPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPNGExportPrefsScriptProviderBoss,	kPNGFilterPrefix + 9)

// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGPREFERENCES, kPNGFilterPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGIMAGEWRITEOPTIONS, kPNGFilterPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETPNGPREFSCMDDATA, kPNGFilterPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_DISABLE_GAMMA_BOOLDATA, kPNGFilterPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGEXPORTPREFERENCES,			kPNGFilterPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGEXPORTSETPREFSCMDDATA,		kPNGFilterPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGEXPORTSUITE,				kPNGFilterPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGPRIVATEUTILS,				kPNGFilterPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGEXPORT,						kPNGFilterPrefix + 9)

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kPNGImageReadFormatService, kPNGFilterPrefix +  1)
DECLARE_PMID(kImplementationIDSpace, kPNGImageReadFormatInfo, kPNGFilterPrefix +  2)
DECLARE_PMID(kImplementationIDSpace, kPNGImageReadFormat, kPNGFilterPrefix +  3)
DECLARE_PMID(kImplementationIDSpace, kPNGErrorStringServiceImpl, kPNGFilterPrefix +  4)
//gap
DECLARE_PMID(kImplementationIDSpace, kPngPreferences, kPNGFilterPrefix +  6)
DECLARE_PMID(kImplementationIDSpace, kPNGScriptImpl, kPNGFilterPrefix +  7)
DECLARE_PMID(kImplementationIDSpace, kPNGOLERefCountImpl, kPNGFilterPrefix +  8)
DECLARE_PMID(kImplementationIDSpace, kSetPNGPrefsCmdImpl, kPNGFilterPrefix +  9)
DECLARE_PMID(kImplementationIDSpace, kPNGImageWriteFormatServiceImpl, kPNGFilterPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPNGImageWriteFormatInfoImpl, kPNGFilterPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPNGImageWriteFormatImpl, kPNGFilterPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPNGImageWriteOptionsImpl, kPNGFilterPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSetPngPrefsCmdDataImpl, kPNGFilterPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPNGExportProviderImpl, kPNGFilterPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPNGExportCommandImpl, kPNGFilterPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPNGExportPreferencesImpl,			kPNGFilterPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kPNGExportSetPrefsCommandImpl,		kPNGFilterPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPNGExportSetPrefsCommandDataImpl,	kPNGFilterPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kPNGExportSuiteLayoutCSBImpl,		kPNGFilterPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPNGExportSuiteASBImpl,			kPNGFilterPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPNGExportPrefsScriptProviderImpl,	kPNGFilterPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPNGPrivateUtilsImpl,	kPNGFilterPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPNGExportImpl,					kPNGFilterPrefix + 24)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportPreferenceObjectScriptElement, kPNGFilterPrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportPreferencePropertyScriptElement, kPNGFilterPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportRangeAllPropertyScriptElement, kPNGFilterPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportPageNumPropertyScriptElement, kPNGFilterPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportExportingSpreadPropertyScriptElement, kPNGFilterPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportQualityPropertyScriptElement, kPNGFilterPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportColorPropertyScriptElement, kPNGFilterPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportResolutionRealPropertyScriptElement, kPNGFilterPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportTransparentBkgndPropertyScriptElement, kPNGFilterPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportAntiAliasPropertyScriptElement, kPNGFilterPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportUseDocumentBleedsPropertyScriptElement, kPNGFilterPrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportSimulateOverprintPropertyScriptElement, kPNGFilterPrefix + 30)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportRangeAllEnumScriptElement, kPNGFilterPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportQualityEnumScriptElement, kPNGFilterPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kPNGExportColorSpaceEnumScriptElement, kPNGFilterPrefix + 52)

// Obsolete IDs
DECLARE_PMID(kClassIDSpace, kPNGImageReadFormatBoss_obsolete, kPNGFilterPrefix_obsolete +  1)
DECLARE_PMID(kImplementationIDSpace, kPngPreferences_obsolete, kPNGFilterPrefix_obsolete +  6)

#endif // __PNGFilterID__
