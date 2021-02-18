//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/JBXID.h $
//  
//  Owner: Greg St. Pierre
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

#ifndef __JBXID__
#define __JBXID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kJBXPrefix						RezLong(0x1ec00)

#define kJBXPluginName					"JBX"
DECLARE_PMID(kPlugInIDSpace,			kJBXPluginID,					kJBXPrefix + 1)

// <Start IDC>

//_________________________________________________________________________________________
// <Class ID>
//_________________________________________________________________________________________
DECLARE_PMID(kClassIDSpace,				kJBXExportPolicyBoss,			kJBXPrefix + 1)
DECLARE_PMID(kClassIDSpace,				kJBXScriptProviderBoss,			kJBXPrefix + 4)
DECLARE_PMID(kClassIDSpace,				kJBXResourceImportPolicyBoss,	kJBXPrefix + 9)
//gap
DECLARE_PMID(kClassIDSpace,				kJBXResTargetImportPolicyBoss,	kJBXPrefix + 11)
DECLARE_PMID(kClassIDSpace,				kJBXExportStreamBoss,			kJBXPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kJBXImportStreamBoss,			kJBXPrefix + 13)
DECLARE_PMID(kClassIDSpace,				kJBXLinkObjectBoss,				kJBXPrefix + 14)

DECLARE_PMID(kClassIDSpace,				kReplaceJBXLinkObjectCmdBoss,	kJBXPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kJBXCharacterStylesResTypeBoss,	kJBXPrefix + 19)
DECLARE_PMID(kClassIDSpace,				kJBXObjectStylesResTypeBoss,	kJBXPrefix + 21)
DECLARE_PMID(kClassIDSpace,				kJBXParagraphStylesResTypeBoss,	kJBXPrefix + 22)
DECLARE_PMID(kClassIDSpace,				kJBXStrokeStylesResTypeBoss,	kJBXPrefix + 23)
DECLARE_PMID(kClassIDSpace,				kJBXSwatchesResTypeBoss,		kJBXPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kJBXAutoRenameResourceImportPolicyBoss,	kJBXPrefix + 29)
DECLARE_PMID(kClassIDSpace,				kJobBagBoss,					kJBXPrefix + 30)
DECLARE_PMID(kClassIDSpace,				kUCFWriteStreamBoss,				kJBXPrefix + 41)
DECLARE_PMID(kClassIDSpace,				kUCFReadStreamBoss,				kJBXPrefix + 42)

//_________________________________________________________________________________________
// <Interface ID>
//_________________________________________________________________________________________

//DECLARE_PMID(kInterfaceIDSpace,		IID_IJBXEXPORTSUITE_Obsolete,			kJBXPrefix + 1)		// Actually an IID_ISNIPPETEXPORTSUITE
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXRESOURCETYPE,			kJBXPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXUTILS,					kJBXPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXLINKOBJECTDATA,			kJBXPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXEXISTINGOBJECTSLISTDATA,kJBXPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXNEWOBJECTSLISTDATA,		kJBXPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXSCRIPTUTILS,			kJBXPrefix + 8)
//gap
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXIMPORTRESULTSDATA,		kJBXPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXJOBBAGCACHEMANAGER,		kJBXPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXPACKAGEUTILS,			kJBXPrefix + 14)

DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXPACKAGESTREAMDATA,		kJBXPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXLINKUTILS,				kJBXPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJBXEXPORTPOLICYDATA,		kJBXPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJOBBAG,					kJBXPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJOBBAGMANAGER,				kJBXPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace,			IID_IJOBBAGPREFS,				kJBXPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMAILSERVICE,				kJBXPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace,			IID_IUCFSTREAMPROPERTY,			kJBXPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace,			IID_IUCFPACKAGETUTILS,			kJBXPrefix + 28)

//_________________________________________________________________________________________
// <Implementation ID>
//_________________________________________________________________________________________
DECLARE_PMID(kImplementationIDSpace,	kJBXExportPolicyImpl,			kJBXPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kJBXScriptUtilsImpl,			kJBXPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kReplaceJBXLinkObjectCmdImpl,	kJBXPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kJBXUtilsImpl,					kJBXPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kJBXResTargetImportPolicyImpl,	kJBXPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kJBXResourceImportPolicyImpl,	kJBXPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kJBXExportStreamImpl,			kJBXPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,	kJBXImportStreamImpl,			kJBXPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,	kJBXLinkObjectDataImpl,			kJBXPrefix + 19)
DECLARE_PMID(kImplementationIDSpace,	kJBXExistingUIDListDataImpl,	kJBXPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,	kJBXNewUIDListDataImpl,			kJBXPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,	kJBXLinkObjectImpl,				kJBXPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,	kJBXLinkUtilsImpl,				kJBXPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,	kJBXJobBagCacheManagerImpl,		kJBXPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kJBXPackageUtilsImpl,			kJBXPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kJBXCharacterStylesResTypeImpl,	kJBXPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kJBXObjectStylesResTypeImpl,	kJBXPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,	kJBXParagraphStylesResTypeImpl,	kJBXPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kJBXStrokeStylesResTypeImpl,	kJBXPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kJBXSwatchesResTypeImpl,		kJBXPrefix + 35)
DECLARE_PMID(kImplementationIDSpace,	kJBXPackageStreamDataImpl,		kJBXPrefix + 36)
DECLARE_PMID(kImplementationIDSpace,	kJBXAutoRenameResourceImportPolicyImpl,	kJBXPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kJBXScriptProviderImpl,			kJBXPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kJBXExportPolicyDataImpl,		kJBXPrefix + 44)
DECLARE_PMID(kImplementationIDSpace,	kJobBagImpl,					kJBXPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kJobBagManagerImpl,				kJBXPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kJobBagPrefsImpl,				kJBXPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kJBXImportResultsDataImpl,		kJBXPrefix + 51)
//gap
DECLARE_PMID(kImplementationIDSpace,	kJBXImportPolicyHelperImpl,		kJBXPrefix + 56)
DECLARE_PMID(kImplementationIDSpace,	kJobBagScriptObjectImpl,		kJBXPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kMailServiceImpl,				kJBXPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,	kUCFPackageUtilsImpl,			kJBXPrefix + 69)
DECLARE_PMID(kImplementationIDSpace,	kUCFStreamReadImpl,				kJBXPrefix + 70)
DECLARE_PMID(kImplementationIDSpace,	kUCFStreamWriteImpl,			kJBXPrefix + 71)
DECLARE_PMID(kImplementationIDSpace,	kUCFStreamPropertyImpl,			kJBXPrefix + 72)
// Service IDs

//_________________________________________________________________________________________
// Action
//_________________________________________________________________________________________

//_________________________________________________________________________________________
//Script Element IDs
//_________________________________________________________________________________________
DECLARE_PMID(kScriptInfoIDSpace, kJBXImportResourcesScriptElement,				kJBXPrefix + 1)
//	Gap
DECLARE_PMID(kScriptInfoIDSpace, kJBXCreateScriptElement,						kJBXPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kJBXAddFileScriptElement,						kJBXPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kJBXJobBagSuiteScriptElement,					kJBXPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kJBXJobBagObjectScriptElement,					kJBXPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kJBXRemoveFileScriptElement,					kJBXPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kJBXGetFilesScriptElement,						kJBXPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kJBXPackageScriptElement,						kJBXPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kJBXExtractScriptElement,						kJBXPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kJBXIsPackageScriptElement,					kJBXPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kJBXExtractedScriptElement,					kJBXPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kJBXExtractedFileScriptElement,				kJBXPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kUnpackageUCFMethodScriptElement,				kJBXPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kPackageUCFMethodScriptElement,					kJBXPrefix + 23)
//_________________________________________________________________________________________
//Suites
//_________________________________________________________________________________________

//_________________________________________________________________________________________
//Objects
//_________________________________________________________________________________________

//_________________________________________________________________________________________
//Events
//_________________________________________________________________________________________

//_________________________________________________________________________________________
//Properties
//_________________________________________________________________________________________

//_________________________________________________________________________________________
//Enums
//_________________________________________________________________________________________

DECLARE_PMID(kErrorIDSpace, kJBXSaveNamedGridsError,		kJBXPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kJBXSaveCharacterStylesError,	kJBXPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kJBXSaveParagraphStylesError,	kJBXPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kJBXSaveObjectStylesError,		kJBXPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kJBXSaveStrokeStylesError,		kJBXPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kJBXLoadNamedGridsError,		kJBXPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kJBXLoadMojikumiError,		kJBXPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kJBXSaveMojikumiError,		kJBXPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kJBXSaveKinsokuError,		kJBXPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kJBXLoadKinsokuError,		kJBXPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kJBXCreateFileError,			kJBXPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kJBXOpenFileError,				kJBXPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kJBXAddFileError,				kJBXPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kJBXCopyFileError,				kJBXPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kJBXRemoveFileError,			kJBXPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kJBXExtractError,				kJBXPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kJBXPackageError,				kJBXPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kJBXImportStylesError,			kJBXPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kJBXCreateFolderError,			kJBXPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kJBXNotPackageError,			kJBXPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kJBXFileExistsError,			kJBXPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kJBXReadOnlyError,				kJBXPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kJBXImportFileError,			kJBXPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kJBXFileMissingError,			kJBXPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kJBXFileStreamError,			kJBXPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kJBXImportLinkFileError,		kJBXPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kJBXExportLinkFileError,		kJBXPrefix + 27)

// Mail errors
DECLARE_PMID(kErrorIDSpace, kMailError_NoMailService, kJBXPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kMailError_UnknownFailure, kJBXPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kMailError_LogonFailure, kJBXPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kMailError_ResolveRecipientFailure, kJBXPrefix + 31)

#define kJBXDocumentResourceFormatName "JBX Document Resource"

// {F8A70833-1683-41b3-B523-EB7E5689A914}
#define kJobBag_CLSID { 0xf8a70833, 0x1683, 0x41b3, { 0xb5, 0x23, 0xeb, 0x7e, 0x56, 0x89, 0xa9, 0x14 } }
// {D1C0C7B8-A459-46b5-B642-01065834B4EA}
#define kJobBags_CLSID { 0xd1c0c7b8, 0xa459, 0x46b5, { 0xb6, 0x42, 0x1, 0x6, 0x58, 0x34, 0xb4, 0xea } }

// {D2199BBB-4202-4ca2-8A37-1BCD431BA55D}
//#define kJobBagAsset_CLSID { 0xd2199bbb, 0x4202, 0x4ca2, { 0x8a, 0x37, 0x1b, 0xcd, 0x43, 0x1b, 0xa5, 0x5d } }
// {81CB0B6F-BA12-48b4-A4AE-BC2BCD01974C}
//#define kJobBagAssets_CLSID { 0x81cb0b6f, 0xba12, 0x48b4, { 0xa4, 0xae, 0xbc, 0x2b, 0xcd, 0x1, 0x97, 0x4c } }


#endif // __JBXID__

