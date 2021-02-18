//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkID.h $
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
//  Defines IDs used by the XDocBk plug-in.
//  
//========================================================================================

#ifndef __XDocBkID_h__
#define __XDocBkID_h__

#include "SDKDef.h"

// Company:
#define kXDocBkCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kXDocBkCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kXDocBkPluginName	"XDocBookWorkflow"				// Name of this plug-in.
#define kXDocBkPrefixNumber	0x5c3b0 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kXDocBkVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kXDocBkAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kXDocBkPrefixNumber above to modify the prefix.)
#define kXDocBkPrefix		RezLong(kXDocBkPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kXDocBkStringPrefix	SDK_DEF_STRINGIZE(kXDocBkPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

START_IDS()

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kXDocBkPluginID, kXDocBkPrefix + 0)

// <ClassIDs>:
DECLARE_PMID(kClassIDSpace, kXDocBkImageSizerCmdBoss,				kXDocBkPrefix + 0)
DECLARE_PMID(kClassIDSpace, kXDocBkChangeOptionsCmdBoss,			kXDocBkPrefix + 1)
DECLARE_PMID(kClassIDSpace, kXDocBkImportProviderBoss,				kXDocBkPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXDocBkExportProviderBoss,				kXDocBkPrefix + 3)
DECLARE_PMID(kClassIDSpace, kXDocBkCALSContentHandlerBoss,			kXDocBkPrefix + 4)
DECLARE_PMID(kClassIDSpace, kXDocBkXMLPostImportIterationBoss,		kXDocBkPrefix + 5)
DECLARE_PMID(kClassIDSpace, kXDocBkXMLTransformerBoss,				kXDocBkPrefix + 6)
DECLARE_PMID(kClassIDSpace, kXDocBkChangeServiceXMLImportPrefsCmdBoss,		kXDocBkPrefix + 7)
DECLARE_PMID(kClassIDSpace, kXDocBkErrorStringServiceBoss,			kXDocBkPrefix + 8)
DECLARE_PMID(kClassIDSpace, kXDocBkConversionProviderBoss,			kXDocBkPrefix + 9)
DECLARE_PMID(kClassIDSpace, kXDocBkPrefsScriptProviderBoss, kXDocBkPrefix + 10)   

//</ClassIDs>
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IXDOCBKOPTIONS,						kXDocBkPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IXDOCBKFACADE,						kXDocBkPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IXDOCBKSERVICEIDINTDATA,			kXDocBkPrefix + 4)


//<ImplementationIDs>:
DECLARE_PMID(kImplementationIDSpace, kXDocBkActionComponentImpl,		kXDocBkPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kXDocBkImageSizerCmdImpl,			kXDocBkPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kXDocBkChangeOptionsCmdImpl,		kXDocBkPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kXDocBkOptionsImpl,				kXDocBkPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXDocBkCustImportCmdImpl,			kXDocBkPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kXDocBkCustImportCmdDataImpl,		kXDocBkPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kXDocBkFacadeImpl,					kXDocBkPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kXDocBkImportProviderImpl,			kXDocBkPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kXDocBkExportProviderImpl,			kXDocBkPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kXDocBkCALSContentHandlerImpl,		kXDocBkPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kXDocBkXMLPostImportIterationImpl,	kXDocBkPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kXDocBkXMLTransformerImpl,			kXDocBkPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kXDocBkCALSContentXMLImportPrefsImpl,	kXDocBkPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kXDocBkXPostImpXMLImportPrefsImpl,	kXDocBkPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kXDocBkXTransXMLImportPrefsImpl,	kXDocBkPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kXDocBkChangeServiceXMLImportPrefsCmdImpl,	kXDocBkPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kXDocBkErrorStringServiceImpl,	kXDocBkPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kXDocBkPrefsScriptProviderImpl,	kXDocBkPrefix + 23)

//<ErrorIDs>:
DECLARE_PMID(kErrorIDSpace, kXDocBkTemplateUninitializedErr,			kXDocBkPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseAlreadyInTableElementErr,	kXDocBkPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseInTableNotInCellElementErr,	kXDocBkPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseNotInRowElementErr,			kXDocBkPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseUnknownElementErr,			kXDocBkPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseCantGetTextChunkErr,			kXDocBkPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseHeaderCantGoHereErr,			kXDocBkPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLHeaderFirstRowsErr,				kXDocBkPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseCantAddRowNotInTableErr,		kXDocBkPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kXDocBkAlreadyInHeaderOrBodyErr,			kXDocBkPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kXDocBkCantGetTextModelFromContentItemErr,	kXDocBkPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseNotInTableElementErr,		kXDocBkPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kXDocBkXMLParseDontHaveTableErr,			kXDocBkPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kXDocBkFailureErrorCode,					kXDocBkPrefix + 13)

//</ImplementationIDs>
// <ActionIDs>:
//</ActionIDs>

END_IDS()

// Other StringKeys:
#define kXDocBkImageSizerCmdKey				kXDocBkStringPrefix "kXDocBkImageSizerCmdKey"
#define kXDocBkChangeOptionsCmdKey			kXDocBkStringPrefix "kXDocBkChangeOptionsCmdKey"
#define kXDocBkChangeServiceXMLImportPrefsCmdKey kXDocBkStringPrefix "kXDocBkChangeServiceXMLImportPrefsCmdKey"
// NB these have to be valid XML element names, hence my switching the order, as element names
// can't begin with a number
#define kXDocBkXTransXMLImportPrefsKey	"kXDocBkXTransXMLImportPrefsKey" kXDocBkStringPrefix 
#define kXDocBkXPostImpXMLImportPrefsKey	 "kXDocBkXPostImpXMLImportPrefsKey" kXDocBkStringPrefix
#define kXDocBkCALSContentXMLImportPrefsKey	 "kXDocBkCALSContentXMLImportPrefsKey" kXDocBkStringPrefix
#define kXDocBkStrucTableIterXMLImportPrefsKey	 "kXDocBkStrucTableIterXMLImportPrefsKey" kXDocBkStringPrefix
#define kXDocBkTaggingTableIterXMLImportPrefsKey	 "kXDocBkTaggingTableIterXMLImportPrefsKey" kXDocBkStringPrefix
#define kXDocBkXSLSuppliedOverridesPIPrefsKey	"kXDocBkXSLSuppliedOverridesPIPrefsKey" kXDocBkStringPrefix

const int32 cXDocBkTemplatePathIndex=0;
const int32 cXDocBkStylesheetPathIndex =	cXDocBkTemplatePathIndex + 1;
const int32 cXDocBkLastOption =				cXDocBkStylesheetPathIndex;
const int32 cXDocBkOptionCardinality = cXDocBkLastOption + 1;
// Open provider strings
#define kXDocBkFormatKey			kXDocBkStringPrefix "kXDocBkFormatKey"
#define kXDocBkFileExtensionKey		"dcbk"
#define kXDocBkFileOSType			'TEXT'
#define kXDocBkExportFormatNameKey	kXDocBkStringPrefix "kXDocBkExportFormatNameKey"


// Initial Data format IDs of the persistent  data was first introduced in InDesign 2.0 (XMLWorkflow plug-in)
#define kXDocBkInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kXDocBkInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber
// Note: The data format has not been changed since InDesign 2.0.

// InDesign CS4 format changes
#define kXDocBkStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kXDocBkStoreWideStringMinorFormat		RezLong(1)

// Error String resource IDs/keys
#define kXDocBkErrorStringTableRsrcID 1301
#define kXDocBkTemplateUninitializedErrKey				kXDocBkStringPrefix "kXDocBkTemplateUninitializedErrKey"
#define kXDocBkXMLParseAlreadyInTableElementErrKey		kXDocBkStringPrefix "kXDocBkXMLParseAlreadyInTableElementErrKey"
#define kXDocBkXMLParseInTableNotInCellElementErrKey	kXDocBkStringPrefix "kXDocBkXMLParseInTableNotInCellElementErrKey"
#define kXDocBkXMLParseNotInRowElementErrKey			kXDocBkStringPrefix "kXDocBkXMLParseNotInRowElementErrKey"	
#define kXDocBkXMLParseUnknownElementErrKey				kXDocBkStringPrefix	"kXDocBkXMLParseUnknownElementErrKey"
#define kXDocBkXMLParseCantGetTextChunkErrKey			kXDocBkStringPrefix "kXDocBkXMLParseCantGetTextChunkErrKey"
#define kXDocBkXMLParseHeaderCantGoHereErrKey			kXDocBkStringPrefix "kXDocBkXMLParseHeaderCantGoHereErrKey"
#define kXDocBkXMLHeaderFirstRowsErrKey					kXDocBkStringPrefix "kXDocBkXMLHeaderFirstRowsErrKey"
#define kXDocBkXMLParseCantAddRowNotInTableErrKey		kXDocBkStringPrefix "kXDocBkXMLParseCantAddRowNotInTableErrKey"
#define kXDocBkAlreadyInHeaderOrBodyErrKey				kXDocBkStringPrefix "kXDocBkAlreadyInHeaderOrBodyErrKey"
#define kXDocBkCantGetTextModelFromContentItemErrKey	kXDocBkStringPrefix "kXDocBkCantGetTextModelFromContentItemErrKey"
#define kXDocBkXMLParseNotInTableElementErrKey			kXDocBkStringPrefix "kXDocBkXMLParseNotInTableElementErrKey"
#define kXDocBkXMLParseDontHaveTableErrKey				kXDocBkStringPrefix "kXDocBkXMLParseDontHaveTableErrKey"

//ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkPrefObjectScriptElement,							kXDocBkPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkPrefObjectPropertyScriptElement,					kXDocBkPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkOptionPropertyScriptElement,						kXDocBkPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkImportItPropertyScriptElement,						kXDocBkPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkXMLTsfPropertyScriptElement,						kXDocBkPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkCALSContendHndlPropertyScriptElement,				kXDocBkPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kXDocBkSuppliedXSLOverridingPIPropertyScriptElement,		kXDocBkPrefix + 6)

// Format IDs for the PluginVersion resource 
#define kXDocBkLastMajorFormatChange	kXDocBkStoreWideStringMajorFormat		// Last major format change
#define kXDocBkLastMinorFormatChange	kXDocBkStoreWideStringMinorFormat		// Last minor format change
// TODO sa+ what data format change tests have you done/do you need to do for preferences stored on the session workspace? 

#endif // __XDocBkID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, XDocBkID.h.




