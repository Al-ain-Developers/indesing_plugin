//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/INXCoreID.h $
//  
//  Owner: Craig Rainwater
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
//  Info:	Contains IDs used by the INXCore plugin.
//  
//========================================================================================

#ifndef __INXCoreID__
#define __INXCoreID__

// ----- Interfaces -----

#include "IDFactory.h"

// ----- Includes -----

#include "CrossPlatformTypes.h"


#define kINXCorePrefix				RezLong(0x1B400)

// PluginID
#define kINXCorePluginName 			"INXCore"

DECLARE_PMID(kPlugInIDSpace, kINXCorePluginID, kINXCorePrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kINXCoreErrorStringServiceBoss,				kINXCorePrefix + 1)
DECLARE_PMID(kClassIDSpace, kINXManagerBoss,							kINXCorePrefix + 2)
DECLARE_PMID(kClassIDSpace, kINXValidationContentHandlerBoss,			kINXCorePrefix + 3)
DECLARE_PMID(kClassIDSpace, kXMLOutNullStreamBoss,						kINXCorePrefix + 4)	
DECLARE_PMID(kClassIDSpace, kActionSurrogateDOMElementBoss,				kINXCorePrefix + 5)	
DECLARE_PMID(kClassIDSpace, kBasicScriptDOMElementBoss,					kINXCorePrefix + 6)
DECLARE_PMID(kClassIDSpace, kINXTraditionalImportBoss,					kINXCorePrefix + 7)
DECLARE_PMID(kClassIDSpace, kINXTraditionalExportBoss,					kINXCorePrefix + 8)
DECLARE_PMID(kClassIDSpace, kINXExpandedImportBoss,						kINXCorePrefix + 9)
DECLARE_PMID(kClassIDSpace, kINXExpandedExportBoss,						kINXCorePrefix + 10)

DECLARE_PMID(kClassIDSpace, kINXScriptManagerBoss,						kINXCorePrefix + 11)	// base class
DECLARE_PMID(kClassIDSpace, kINXTraditionalImportScriptManagerBoss,		kINXCorePrefix + 12)	// INX Traditional Import
DECLARE_PMID(kClassIDSpace, kINXTraditionalExportScriptManagerBoss,		kINXCorePrefix + 13)	// INX Traditional export
DECLARE_PMID(kClassIDSpace, kINXExpandedImportScriptManagerBoss,		kINXCorePrefix + 14)	// INX Expanded (Alt) import	
DECLARE_PMID(kClassIDSpace, kINXExpandedExportScriptManagerBoss,		kINXCorePrefix + 15)	// INX Expanded (Alt) export

DECLARE_PMID(kClassIDSpace, kINXPageitemDEHandlerHelperBoss,			kINXCorePrefix + 20)	
DECLARE_PMID(kClassIDSpace, kINXTextDEHandlerHelperBoss,				kINXCorePrefix + 21)
DECLARE_PMID(kClassIDSpace, kINXTableDEHandlerHelperBoss,				kINXCorePrefix + 22)
DECLARE_PMID(kClassIDSpace, kINXPerfFileContentHandlerBoss,				kINXCorePrefix + 23)
DECLARE_PMID(kClassIDSpace, kMyINXErrorHandlerBoss,						kINXCorePrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetIDMLComponentNameCmdBoss,				kINXCorePrefix + 25)
DECLARE_PMID(kClassIDSpace, kINXCoreScriptProviderBoss,					kINXCorePrefix + 26)


// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IINXIMPORTPOLICYHELPER,				kINXCorePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMELEMENT,						kINXCorePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXIDMANAGER,						kINXCorePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXCURRENTTABLERUN,				kINXCorePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXATTRIBUTEDATA,					kINXCorePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXHYPERLINKHELPER,				kINXCorePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXIMPORT,							kINXCorePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXEXPORT,							kINXCorePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXUTILS,							kINXCorePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXIMPORTVALIDATION,				kINXCorePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXIMPORTPOLICY,					kINXCorePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXEXPORTPOLICY,					kINXCorePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXVALIDATIONCONTENTHANDLERDATA,	kINXCorePrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXCONTENTHANDLERDATA,				kINXCorePrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTDOMELEMENTHELPER,			kINXCorePrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONDOMELEMENTHELPER,			kINXCorePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXACTIONPOLICY,					kINXCorePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXINFO,							kINXCorePrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMELEMENTREGISTRY,				kINXCorePrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMCACHEMANAGER			,		kINXCorePrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IINXOBSERVER,						kINXCorePrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXSERIALIZE,						kINXCorePrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXDESERIALIZE,					kINXCorePrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXSCHEMAGENERATOR,				kINXCorePrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMOBJECTREFERENCES,				kINXCorePrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXPREFERENCES,					kINXCorePrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXSTYLEMANAGER,					kINXCorePrefix + 27)
//DECLARE_PMID(kInterfaceIDSpace, IID_IINXEXPORTOPTIONSUTILS,				kINXCorePrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXMANAGER,						kINXCorePrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IINX_IMPORT_PACKAGE_DATA,			kINXCorePrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXERRORHANDLER,					kINXCorePrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDMLCOMPONENTNAME,					kINXCorePrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IINX_EXPORT_PACKAGE_DATA,			kINXCorePrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IINXSTORYRANGELIST, 				kINXCorePrefix + 34) // to support partial story export
DECLARE_PMID(kInterfaceIDSpace, IID_IEXCLUDEONSNIPPETEXPORT, 				kINXCorePrefix + 35)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kINXCoreErrorStringServiceImpl,		kINXCorePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBasicScriptDOMElementImpl,			kINXCorePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kINXTraditionalContentHandlerImpl,		kINXCorePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kINXIDManagerImpl,						kINXCorePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kINXAttributeDataImpl,					kINXCorePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kLinkedBinaryScriptDOMElementImpl,		kINXCorePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStoryScriptDOMElementImpl,			kINXCorePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptDOMElementImpl,			kINXCorePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kTextScriptDOMElementImpl,				kINXCorePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMKScriptDOMElementImpl,				kINXCorePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTableScriptDOMElementImpl,			kINXCorePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptDOMElementImpl,			kINXCorePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kHyperlinkHelperImpl,					kINXCorePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kApplicationScriptDOMElementImpl,		kINXCorePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kStyleScriptDOMElementImpl,			kINXCorePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPrefsScriptDOMElementImpl,			kINXCorePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kINXScriptDOMHelperImpl,				kINXCorePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kINXImportPolicyHelperImpl,			kINXCorePrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kINXManagerImpl,						kINXCorePrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kINXTraditionalExportImpl,				kINXCorePrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kINXExpandedExportImpl,				kINXCorePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kINXImportImpl,						kINXCorePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kINXSchemaGeneratorImpl,				kINXCorePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kINXUtilsImpl,							kINXCorePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kINXValidationContentHandlerDataImpl,	kINXCorePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kINXContentHandlerDataImpl,			kINXCorePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kINXCoreScriptManagerImpl,				kINXCorePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kINXCurrentTableRunImpl,				kINXCorePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kXMLOutNullStreamImpl,					kINXCorePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kScriptDOMElementHelperImpl,			kINXCorePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kActionDOMElementImpl,					kINXCorePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kActionSequenceDOMElementImpl,			kINXCorePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kActionDOMElementHelperImpl,			kINXCorePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kActionSurrogateDOMElementImpl,		kINXCorePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kActionScriptImpl,						kINXCorePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kINXValidationContentHandlerImpl,		kINXCorePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kINXInfoImpl,							kINXCorePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDOMElementRegistryImpl,				kINXCorePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kINXDOMCacheManagerImpl,				kINXCorePrefix + 39)
//DECLARE_PMID(kImplementationIDSpace, kINXObserverImpl,					kINXCorePrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kDOMObjectReferencesImpl,				kINXCorePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kINXExpandedContentHandlerImpl,		kINXCorePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kINXTraditionalSerializeImpl,			kINXCorePrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kINXExpandedSerializeImpl,				kINXCorePrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kINXTraditionalDeserializeImpl,		kINXCorePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kINXExpandedDeserializeImpl,			kINXCorePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kINXPreferencesImpl,					kINXCorePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kINXStyleManagerImpl,					kINXCorePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kINXTextDEHandlerHelperImpl,			kINXCorePrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kINXTableDEHandlerHelperImpl,			kINXCorePrefix + 50)
//gap
DECLARE_PMID(kImplementationIDSpace, kINXPerfFileContentHandlerImpl,		kINXCorePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kINXPageitemDEHandlerHelperImpl,		kINXCorePrefix + 53)
//gap
DECLARE_PMID(kImplementationIDSpace, kINXImportPackageDataImpl,				kINXCorePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kINXScriptEngineImpl,					kINXCorePrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kIDMLStoryComponentNameImpl,			kINXCorePrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kIDMLSpreadComponentNameImpl,			kINXCorePrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kIDMLMasterSpreadComponentNamemplImpl,	kINXCorePrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kSetIDMLComponentNameCmdImpl,			kINXCorePrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kINXCoreScriptProviderImpl,			kINXCorePrefix + 61)
//gap
DECLARE_PMID(kImplementationIDSpace, kMyINXErrorHandlerImpl,				kINXCorePrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kINXExportPackageDataImpl,				kINXCorePrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTextChildScriptDOMElementImpl,			kINXCorePrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kINXStoryRangeListImpl,				kINXCorePrefix + 109)	// to support partial story export


// <Error ID>
// Not a real error. Used to force the SAX parser to stop.
DECLARE_PMID(kErrorIDSpace, kINXCoreStopParsing,							kINXCorePrefix + 1)

// Also not a real error. Used to force IINXExport::Write() to stop.
DECLARE_PMID(kErrorIDSpace, kINXCoreStopWriting,							kINXCorePrefix + 2)

// Import Errors
DECLARE_PMID(kErrorIDSpace, kINXCoreWrongDocType,							kINXCorePrefix + 10)
DECLARE_PMID(kErrorIDSpace, kINXCoreWrongBuildNumber,						kINXCorePrefix + 11)
DECLARE_PMID(kErrorIDSpace, kINXCorePrereleaseFile,							kINXCorePrefix + 12)
DECLARE_PMID(kErrorIDSpace, kINXCoreWrongFeatureSet,						kINXCorePrefix + 13)
DECLARE_PMID(kErrorIDSpace, kINXCoreWrongLanguage,							kINXCorePrefix + 14)
DECLARE_PMID(kErrorIDSpace, kINXCoreSetAttrFailed,							kINXCorePrefix + 15)
DECLARE_PMID(kErrorIDSpace, kINXCoreCreateChildFailed,						kINXCorePrefix + 16)
DECLARE_PMID(kErrorIDSpace, kINXCoreNotCompactStyle,						kINXCorePrefix + 17)
DECLARE_PMID(kErrorIDSpace, kINXCoreImportFailed,							kINXCorePrefix + 18)
DECLARE_PMID(kErrorIDSpace, kINXCoreNotIntendedReader,						kINXCorePrefix + 19)
DECLARE_PMID(kErrorIDSpace, kINXCoreInvalidDOMInformation,					kINXCorePrefix + 20)
DECLARE_PMID(kErrorIDSpace, kINXCoreNotExpandedStyle,						kINXCorePrefix + 21)
DECLARE_PMID(kErrorIDSpace, kINXCoreUnknownElementType,						kINXCorePrefix + 22)
DECLARE_PMID(kErrorIDSpace, kINXCoreInternalError,							kINXCorePrefix + 23)
DECLARE_PMID(kErrorIDSpace, kINXCoreCantOpenSubFile,						kINXCorePrefix + 24)
DECLARE_PMID(kErrorIDSpace, kINXCoreSubFileAlreadyOpened,					kINXCorePrefix + 25)

// Export Errors
DECLARE_PMID(kErrorIDSpace, kINXCoreExportFail,								kINXCorePrefix + 30)

// Other Errors
DECLARE_PMID(kErrorIDSpace, kINXCoreInvalidComponentName,					kINXCorePrefix + 50)

//
//Script Element IDs
//

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyNamePolicy30MetadataScriptElement,			kINXCorePrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertiesAndChildrenPolicy30MetadataScriptElement,	kINXCorePrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyAnchorPointPolicy30MetadataScriptElement,		kINXCorePrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kINXCharacterObjectImportClassPolicy30MetadataScriptElement,	kINXCorePrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kINXBinaryObjectImportClassPolicy30MetadataScriptElement,		kINXCorePrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kINXGenericContainerImportClassPolicy30MetadataScriptElement,	kINXCorePrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kRunInStyleINXPolicies30MetadataScriptElement,					kINXCorePrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchAvailablePolicy30MetadataScriptElement,				kINXCorePrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextStyleRangeImportClassPolicy30MetadataScriptElement,	kINXCorePrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kINXLinkedBinaryObjectImportClassPolicy30MetadataScriptElement,kINXCorePrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kINXExcludeChildUserDictPolicy30MetadataScriptElement,			kINXCorePrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kStoryNoteINXPolicies30MetadataScriptElement,					kINXCorePrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kINXTreatAsStoryChildPolicy30MetadataScriptElement,			kINXCorePrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextFrameTOPINXPolicies30MetadataScriptElement,			kINXCorePrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kTableINXPolicies30MetadataScriptElement,						kINXCorePrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kRowColumnINXPolicies30MetadataScriptElement,					kINXCorePrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kCellINXPolicies30MetadataScriptElement,						kINXCorePrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kTextINXPolicies30MetadataScriptElement,						kINXCorePrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kTextStyleRangeINXPolicies30MetadataScriptElement,				kINXCorePrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentINXPolicies30MetadataScriptElement,					kINXCorePrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementINXPolicies30MetadataScriptElement,					kINXCorePrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kINXNoDefaultsCachePolicy30MetadataScriptElement,				kINXCorePrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kINXDataTreatmentCDATAPolicy30MetadataScriptElement,			kINXCorePrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kINXDataTreatmentTextPolicy30MetadataScriptElement,			kINXCorePrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy1_30MetadataScriptElement,	kINXCorePrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleINXPolicies30MetadataScriptElement,					kINXCorePrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kSubtopicINXPolicies30MetadataScriptElement,					kINXCorePrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleEntryINXPolicies30MetadataScriptElement,				kINXCorePrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy2_30MetadataScriptElement,	kINXCorePrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kLinkINXPolicies30MetadataScriptElement,						kINXCorePrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyNamePolicyJ_30MetadataScriptElement,			kINXCorePrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyNamePolicyJ_40MetadataScriptElement,			kINXCorePrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontINXPolicies1_40MetadataScriptElement,			kINXCorePrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontEntryINXPolicies40MetadataScriptElement,			kINXCorePrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy1_40MetadataScriptElement,	kINXCorePrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kNamedGridINXPolicies40MetadataScriptElement,					kINXCorePrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontINXPolicies2_40MetadataScriptElement,			kINXCorePrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleINXPolicies40MetadataScriptElement,					kINXCorePrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleINXPolicies40MetadataScriptElement,				kINXCorePrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kChangeINXPolicies40MetadataScriptElement,						kINXCorePrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteINXPolicies40MetadataScriptElement,					kINXCorePrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteStoryOffsetINXPolicies40MetadataScriptElement,		kINXCorePrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContentsINXPolicies40MetadataScriptElement,			kINXCorePrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kINXLinkedBinaryObjectImportClassPolicy40MetadataScriptElement,kINXCorePrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectINXPolicies40MetadataScriptElement,				kINXCorePrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kChangeStoryOffsetINXPolicies40MetadataScriptElement,			kINXCorePrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicLayerINXPolicies40MetadataScriptElement,				kINXCorePrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreElementAndChildAttributesPolicy40MetadataScriptElement,kINXCorePrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAndChildAttributesPolicy40MetadataScriptElement,	kINXCorePrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy40MetadataScriptElement,			kINXCorePrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenationExceptionINXPolicies40MetadataScriptElement,		kINXCorePrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kLinkINXPolicies40MetadataScriptElement,						kINXCorePrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy2_40MetadataScriptElement,	kINXCorePrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kInCopyDocUserINXPolicies40MetadataScriptElement,				kINXCorePrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kGridDataINXPolicies40MetadataScriptElement,					kINXCorePrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kINXNoDefaultsCachePolicy1_50MetadataScriptElement,			kINXCorePrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyName50MetadataScriptElement,					kINXCorePrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy50MetadataScriptElement,			kINXCorePrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kTextVariableINXPolicies50MetadataScriptElement,				kINXCorePrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kTextVariableInstanceINXPolicies50MetadataScriptElement,		kINXCorePrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kXPDefaultContainerINXPolicies50MetadataScriptElement,			kINXCorePrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy1_50MetadataScriptElement,	kINXCorePrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentINXOrderChild50MetadataScriptElement,					kINXCorePrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemINXOrderChild50MetadataScriptElement,					kINXCorePrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXPageItemOrder50MetadataScriptElement,					kINXCorePrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicLineINXOrderChild50MetadataScriptElement,				kINXCorePrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXGraphicLineOrder50MetadataScriptElement,				kINXCorePrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kRectangleINXOrderChild50MetadataScriptElement,				kINXCorePrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXRectangleOrder50MetadataScriptElement,					kINXCorePrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kOvalINXOrderChild50MetadataScriptElement,						kINXCorePrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXOvalOrder50MetadataScriptElement,						kINXCorePrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameINXOrderChild50MetadataScriptElement,				kINXCorePrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXTextFrameOrder50MetadataScriptElement,					kINXCorePrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kPolygonINXOrderChild50MetadataScriptElement,					kINXCorePrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kTOPINXPolygonOrder50MetadataScriptElement,					kINXCorePrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kStoryINXOrderChild50MetadataScriptElement,					kINXCorePrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kGridDataINXOrder50MetadataScriptElement,						kINXCorePrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kLanguageINXDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kINXSwatchDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kINXColorDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 79)
DECLARE_PMID(kScriptInfoIDSpace, kINXAGMBlackBoxDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kINXInkDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kINXMixedInkGroupDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kINXMixedInkDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kINXTintDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kINXGradientDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kINXStrokeStyleDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kINXDashSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kINXDotSSDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kINXStripeSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kINXFontFamilyDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kINXCharSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kINXCharStyleDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kINXBNListDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kINXParaSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kINXParaStyleDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kINXCellSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kINXCellStyleDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kINXTableSSDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kINXTableStyleDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kINXObjectSGDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kINXObjectStyleDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kINXTrapStyleDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextVariableDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLTagDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kINXLayerDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kINXMasterSpreadDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kINXSpreadDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kINXSectionDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kINXICDocUserDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kINXStoryDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLStoryDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextDestDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kINXPageDestDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kINXURLDestDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kINXExtPageDestDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextSourceDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kINXPISourceDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kINXHyperlinkDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLItemDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 119)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLElementDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLDTDDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLCommentDocumentOrder50MetadataScriptElement,			kINXCorePrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLPIDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLExportDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLImportDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kINXIndexDocumentOrder50MetadataScriptElement,					kINXCorePrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kINXBookmarkDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kINXCompFontDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kINXNamedGridDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kINXKinsokuDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kINXMojikumiDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kINXTOCStyleDocumentOrder50MetadataScriptElement,				kINXCorePrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kINXMatchAvailablePolicy60MetadataScriptElement,				kINXCorePrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kINXRootCellStyleDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kINXRootTableStyleDocumentOrder60MetadataScriptElement,		kINXCorePrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kINXRootObjectStyleDocumentOrder60MetadataScriptElement,		kINXCorePrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kINXRootCharStyleDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kINXRootParaStyleDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kINXBaseObjectOnlyPolicy60MetadataScriptElement,				kINXCorePrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kINXConditionTagDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleGroupINXPolicies60MetadataScriptElement,			kINXCorePrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kINXDontOutputSelfIDPolicy60MetadataScriptElement,				kINXCorePrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy60MetadataScriptElement,			kINXCorePrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kINXXRefFormatDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kINXNoDefaultsCachePolicy60MetadataScriptElement,				kINXCorePrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kHideFromINXDOM1MetadataScriptElement,							kINXCorePrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingDocChildGraphicScriptElement,						kINXCorePrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingDocChildResourceScriptElement,						kINXCorePrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingDocChildStylesScriptElement,							kINXCorePrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingMasterSpreadScriptElement,							kINXCorePrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingStoriesScriptElement,								kINXCorePrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingSpreadsScriptElement,								kINXCorePrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingStructureScriptElement,								kINXCorePrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingXMLTagsScriptElement,								kINXCorePrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingXMLMappingScriptElement,								kINXCorePrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingXMLBackingStoryScriptElement,						kINXCorePrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesScriptElement,							kINXCorePrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesScriptElement2,							kINXCorePrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingDocumentPerExportScriptElement,						kINXCorePrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontPackagingDocChildResourceScriptElement,			kINXCorePrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStylePackagingDocChildStylesScriptElement,					kINXCorePrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesScriptElement3,							kINXCorePrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesScriptElement4,							kINXCorePrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kINXXRefSourceDocumentOrder60MetadataScriptElement,			kINXCorePrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kINXStyleRangeParentPolicy60MetadataScriptElement,				kINXCorePrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kINXParagraphStyleRangePolicy60MetadataScriptElement,			kINXCorePrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kINXCharacterStyleRangePolicy60MetadataScriptElement,			kINXCorePrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextRangeObjectPolicy60MetadataScriptElement,				kINXCorePrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kIDMLTextContainerPolicy60MetadataScriptElement,				kINXCorePrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kINXChangeObjectPolicy60MetadataScriptElement,					kINXCorePrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kINXXMLElementObjectPolicy60MetadataScriptElement,				kINXCorePrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy3_30MetadataScriptElement,	kINXCorePrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy3_40MetadataScriptElement,	kINXCorePrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kINXDontOutputSelfIDPolicy60_Alt_MetadataScriptElement,		kINXCorePrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kINXConditionTagSetDocumentOrder60MetadataScriptElement,		kINXCorePrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kIDMLComponentNamePropertyScriptElement,						kINXCorePrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingDocumentPerInstanceScriptElement,					kINXCorePrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kINXIgnoreDefaultValueCheckPolicy2_60MetadataScriptElement,	kINXCorePrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kINXStyleSetMetadataScriptElement,								kINXCorePrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kInCopyDocUserINXPolicies60MetadataScriptElement,				kINXCorePrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kStoryPrefsINXOrder60MetadataScriptElement,					kINXCorePrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingTopicINXPolicies60MetadataScriptElement,				kINXCorePrefix + 182)

//*******************************************************************************************************************
// Being Rocket/Troll scripting metadata ids
//*******************************************************************************************************************
DECLARE_PMID(kScriptInfoIDSpace, kIDMLTextRangeObjectPolicy70MetadataScriptElement,				kINXCorePrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kINXBaseObjectOnlyPolicy70MetadataScriptElement,				kINXCorePrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kINXDontOutputSelfIDPolicy70MetadataScriptElement,				kINXCorePrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kSpreadINXOrderChild70MetadataScriptElement,					kINXCorePrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kButtonINXOrderChild70MetadataScriptElement,					kINXCorePrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kMSOINXOrderChild70MetadataScriptElement,						kINXCorePrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy70MetadataScriptElement,			kINXCorePrefix + 189)

//*******************************************************************************************************************
// Begin block of IDML story child object rank metadata IDs
//*******************************************************************************************************************

DECLARE_PMID(kScriptInfoIDSpace, kINXXMLElementRankPolicy60MetadatScriptElement,				kINXCorePrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kINXParaStyleIterRankPolicy60MetadatScriptElement,				kINXCorePrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kINXCharStyleIterRankPolicy60MetadatScriptElement,				kINXCorePrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kINXHyperlinkTextSourceRankPolicy60MetadatScriptElement,		kINXCorePrefix + 198)

//*******************************************************************************************************************
// End block of IDML story child object rank metadata IDs
//*******************************************************************************************************************

DECLARE_PMID(kScriptInfoIDSpace, kObjectExportOptionsINXPolicies75MetadataScriptElement,		kINXCorePrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesPolicy75MetadataScriptElement,			kINXCorePrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesPolicy80MetadataScriptElement,			kINXCorePrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOptionsPolicy80MetadataScriptElement,			kINXCorePrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kPackagingPreferencesPolicy100MetadataScriptElement,			kINXCorePrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy130MetadataScriptElement,        kINXCorePrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextRangeObjectPolicy130MetadataScriptElement,				kINXCorePrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kINXTextFrameTOPINXPolicies130MetadataScriptElement,			kINXCorePrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kINXSetElementAttributesPolicy2_130MetadataScriptElement,		kINXCorePrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kINXAnnotationPageDestinationDocumentOrder140MetadataScriptElement, kINXCorePrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kINXAnnotationPageItemDocumentOrder140MetadataScriptElement, kINXCorePrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kINXAnnotationTextDestinationDocumentOrder140MetadataScriptElement, kINXCorePrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kINXAnnotationDocumentOrder140MetadataScriptElement, kINXCorePrefix + 212)

#ifndef __ODFRC__
static const int32	kXMLNamespaceAttributeID = 'xmNs';
static const int32  kDOMVersionAttributeID = 'DOMv';
#endif	// __ODFRC__

#endif	// __INXCoreID__
