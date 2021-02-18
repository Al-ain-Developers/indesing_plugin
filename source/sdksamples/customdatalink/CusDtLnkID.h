//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkID.h $
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
//========================================================================================

#ifndef __CusDtLnkID_h__
#define __CusDtLnkID_h__

#include "SDKDef.h"

// Company:
#define kCusDtLnkCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCusDtLnkCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCusDtLnkPluginName	"CustomDataLink"			// Name of this plug-in.
#define kCusDtLnkPrefixNumber	0xb3300 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCusDtLnkVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCusDtLnkAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCusDtLnkPrefixNumber above to modify the prefix.)
#define kCusDtLnkPrefix		RezLong(kCusDtLnkPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCusDtLnkStringPrefix	SDK_DEF_STRINGIZE(kCusDtLnkPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCusDtLnkPluginID, kCusDtLnkPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCusDtLnkScriptProviderBoss, kCusDtLnkPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCusDtLnkLinkResponderBoss, kCusDtLnkPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUpdateLinkServiceBoss, kCusDtLnkPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCusDtLnkBasicCustDataLinkBoss, kCusDtLnkPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCusDtLnkBoss, kCusDtLnkPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCusDtLnkAliasedDataLinkBoss, kCusDtLnkPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCusDtLnkChangeOptionsCmdBoss, kCusDtLnkPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCusDtLnkDocResponderBoss, kCusDtLnkPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCusDtLnkAdornmentBoss, kCusDtLnkPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCusDtLnkDelimTextReaderBoss, kCusDtLnkPrefix + 11)
DECLARE_PMID(kClassIDSpace, kCusDtLnkReferenceConverterBoss, kCusDtLnkPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCusDtLnkNewDataLinkCmdBoss, kCusDtLnkPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCusDtLnkOptionScriptProviderBoss, kCusDtLnkPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCusDtLnkLinkResourceProviderBoss, kCusDtLnkPrefix + 15)
DECLARE_PMID(kClassIDSpace, kCusDtLnkLinkResourceHandlerBoss, kCusDtLnkPrefix + 16)
DECLARE_PMID(kClassIDSpace, kCusDtLnkPhase2ConversionBoss, kCusDtLnkPrefix + 17)
DECLARE_PMID(kClassIDSpace, kCusDtLnkNewLinkConverterBoss, kCusDtLnkPrefix + 18)
DECLARE_PMID(kClassIDSpace, kkCusDtLnConversionProviderBoss, kCusDtLnkPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCusDtLnkLinkInfoProviderBoss, kCusDtLnkPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCusDtLnkStartupShutdownBoss, kCusDtLnkPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kCusDtLnkBoss, kCusDtLnkPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kCusDtLnkBoss, kCusDtLnkPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kCusDtLnkBoss, kCusDtLnkPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kCusDtLnkBoss, kCusDtLnkPrefix + 25)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKOPTIONS, kCusDtLnkPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKFACADE, kCusDtLnkPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKDATALINKBOOLDATA, kCusDtLnkPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKDELIMTEXTREADER, kCusDtLnkPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKDATABASESASOPTIONS, kCusDtLnkPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKPMIIDINTDATA, kCusDtLnkPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKUNIQUEKEYSTRINGDATA, kCusDtLnkPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKDOCOBSERVER, kCusDtLnkPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKSTATEUPDATEPROCESSOR, kCusDtLnkPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKIDLETASK, kCusDtLnkPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKINTERFACE, kCusDtLnkPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkScriptProviderImpl, kCusDtLnkPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResponderImpl, kCusDtLnkPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kCusDtLnkSwitchLinkCmdImpl, kCusDtLnkPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUpdateLinkServiceImpl, kCusDtLnkPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkOptionsImpl, kCusDtLnkPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkChangeOptionsCmdImpl, kCusDtLnkPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkFacadeImpl, kCusDtLnkPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkRespServiceProviderImpl, kCusDtLnkPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkAliasedDataLinkImpl, kCusDtLnkPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkAliasedDataLinkActionImpl, kCusDtLnkPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkAliasedLinkedStreamImpl, kCusDtLnkPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkDocResponderImpl, kCusDtLnkPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkDocRespServiceProviderImpl, kCusDtLnkPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkAdornmentShapeImpl, kCusDtLnkPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkDelimTextReaderImpl, kCusDtLnkPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkDataBasesAsOptionsImpl, kCusDtLnkPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkReferenceConverterImpl, kCusDtLnkPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkScriptImpl, kCusDtLnkPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUniqueKeyStringDataImpl, kCusDtLnkPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkDocObserverImpl, kCusDtLnkPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkNewDataLinkCmdImpl, kCusDtLnkPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkOptionScriptProviderImpl, kCusDtLnkPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceFactoryImpl, kCusDtLnkPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceHandlerImpl, kCusDtLnkPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceStateUpdaterImpl, kCusDtLnkPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceStateProcessorFactoryImpl, kCusDtLnkPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkPhase2ConversionImpl, kCusDtLnkPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkNewLinkConverterImpl, kCusDtLnkPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkAssetConverterImpl, kCusDtLnkPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkImportLinkConverterImpl, kCusDtLnkPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkInfoProviderImpl, kCusDtLnkPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceStateUpdaterIdleTaskImpl, kCusDtLnkPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkStateUpdateProcessorImpl, kCusDtLnkPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkStartupShutdownImpl, kCusDtLnkPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkLinkResourceHelperHandlerImpl, kCusDtLnkPrefix + 37)
//DECLARE_PMID(kImplementationIDSpace, kCusDtLnkImpl, kCusDtLnkPrefix + 37)
//DECLARE_PMID(kImplementationIDSpace, kCusDtLnkImpl, kCusDtLnkPrefix + 38)
//DECLARE_PMID(kImplementationIDSpace, kCusDtLnkImpl, kCusDtLnkPrefix + 39)




//Script Element IDs
//Events
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkMethodScriptElement, kCusDtLnkPrefix + 1)
// Properties
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkPropertyScriptElement, kCusDtLnkPrefix + 2)
// Obj
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkDataLinkObjectScriptElement, kCusDtLnkPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkUpdateMethodScriptElement, kCusDtLnkPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkSuiteScriptElement, kCusDtLnkPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkLinkInfoPropertyScriptElement, kCusDtLnkPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkUniqueKeyPropertyScriptElement, kCusDtLnkPrefix + 7)
// Prefs
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkOptionObjectScriptElement, kCusDtLnkPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkOptionPropertyScriptElement, kCusDtLnkPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkOptionDatabasePairListPropertyScriptElement, kCusDtLnkPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkOptionAssetPairListPropertyScriptElement, kCusDtLnkPrefix + 11)
// Metadata
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkObjectINXPolicies40MetadataScriptElement, kCusDtLnkPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kCusDtLnkPropertyINXPolicies40MetadataScriptElement, kCusDtLnkPrefix + 13)

// StringKeys:
//#define kCusDtLnkSwitchLinkCmdBossStringKey kCusDtLnkStringPrefix "kCusDtLnkSwitchLinkCmdBossStringKey"
#define kCusDtLnkChangeOptionsCmdKey		kCusDtLnkStringPrefix "kCusDtLnkChangeOptionsCmdKey"
// These are keys for options on our custom data interface on the workspace, 
// and aren't going into the stringtable but we follow the same pattern as for other 'keys'
#define kCusDtLnkCurrentlyChosenUniqueKeyOption	kCusDtLnkStringPrefix "kCusDtLnkCurrentlyChosenUniqueKeyOption"
// Initial data format version numbers
#define kCusDtLnkFirstMajorFormatNumber  RezLong(1)
#define kCusDtLnkFirstMinorFormatNumber  RezLong(0)

// conversion ID
#define kCusDtLnkConvertLinksToNewArchitecture		kBasilInitialMinorFormatNumber
// Data format version numbers for the PluginVersion resource 
#define kCusDtLnkCurrentMajorFormatNumber kBasilMajorFormatNumber
#define kCusDtLnkCurrentMinorFormatNumber kCusDtLnkConvertLinksToNewArchitecture



// NOTE: these would be user-customizable options in a 'real' implementation,
// but I am hardcoding for now for this sample. These are fields in the 'database'
// that have special semantics for this implementation.
#define kCusDtLnkAssetDataBaseAssetPathFieldNameKey kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseAssetPathFieldNameKey"
#define kCusDtLnkAssetDataBaseRecordIDFieldNameKey kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseRecordIDFieldNameKey"
#define kCusDtLnkAssetDataBaseDateFieldNameKey kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseDateFieldNameKey"
#define kCusDtLnkAssetDataBaseTimeFieldNameKey kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseTimeFieldNameKey"
#define kCusDtLnkAssetDataBaseLinkInfoNameKey	kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseLinkInfoNameKey"
#define kCusDtLnkAssetDataBaseStatusFieldNameKey	kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseStatusFieldNameKey"
#define kCusDtLnkAssetDataBaseDescriptionFieldNameKey	kCusDtLnkStringPrefix "kCusDtLnkAssetDataBaseDescriptionFieldNameKey"

#define kCusDtLnkScheme	"CSVLink"			// scheme of the uri for our link.

#endif // __CusDtLnkID_h__

//  Code generated by DollyXs code generator
