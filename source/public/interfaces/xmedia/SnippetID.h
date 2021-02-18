//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/SnippetID.h $
//  
//  Owner: Robin_Briggs
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

#ifndef __SnippetsID__
#define __SnippetsID__

#include "IDFactory.h"

// Resource Defs
#define kSnippetsStringsRsrcID 1001
#define kSnippetsErrorStringTableRsrcID 1002
#define kSnippetsStringsNoTransRsrcID 1101
#define kSnippetErrorStringTableRsrcID 1009

#define kSnippetPrefix			RezLong(0x019500)

// PluginID
#define kSnippetsPluginName 		"Snippet"
DECLARE_PMID(kPlugInIDSpace, kSnippetPluginID, kSnippetPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kXMLElementExportBoss, kSnippetPrefix + 1)
DECLARE_PMID(kClassIDSpace, kXMLElementImportBoss, kSnippetPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDocElementImportBoss, kSnippetPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDocElementExportBoss, kSnippetPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPageItemExportBoss, kSnippetPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPageItemImportBoss, kSnippetPrefix + 6)
DECLARE_PMID(kClassIDSpace, kAppPrefsExportBoss, kSnippetPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAppPrefsImportBoss, kSnippetPrefix + 8)
DECLARE_PMID(kClassIDSpace, kChangeAppPrefsImportOptionsCmdBoss, kSnippetPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSnippetContentScriptProviderBoss, kSnippetPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kAutoCorrectExportBoss, kSnippetPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAutoCorrectImportBoss, kSnippetPrefix + 21)
//gap
DECLARE_PMID(kClassIDSpace, kInCopyInterchangeExportBoss, kSnippetPrefix + 30)
DECLARE_PMID(kClassIDSpace, kInCopyInterchangeImportBoss, kSnippetPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace, kSnippetFileImportProviderBoss, kSnippetPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSnippetExportProviderBoss, kSnippetPrefix + 41)
DECLARE_PMID(kClassIDSpace, kSnippetImportValidationBoss, kSnippetPrefix + 42)
DECLARE_PMID(kClassIDSpace, kSnippetStructureExportProviderBoss, kSnippetPrefix + 43)
DECLARE_PMID(kClassIDSpace, kSnippetImportBoss, kSnippetPrefix + 44)
DECLARE_PMID(kClassIDSpace, kSnippetImportResultDescriptorBoss, kSnippetPrefix + 45)
DECLARE_PMID(kClassIDSpace, kGraphicStoryExportBoss, kSnippetPrefix + 46)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETEXPORTSUITE, kSnippetPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETEXPORT, kSnippetPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETIMPORT, kSnippetPrefix + 3)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYINTERCHANGEEXPORTSUITE, kSnippetPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPPREFSEXPORTDELEGATE, kSnippetPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPPREFSIMPORTDELEGATE, kSnippetPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPPREFSIMPORTOPTIONS, kSnippetPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPPREFSEXPORTDATA, kSnippetPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETIMPORTOPTIONS, kSnippetPrefix + 25)


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kSnippetExportPolicyImpl, kSnippetPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXMLElementExportPolicyImpl, kSnippetPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXMLElementImportPolicyImpl, kSnippetPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDocElementImportPolicyImpl, kSnippetPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDocElementExportPolicyImpl, kSnippetPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kXMLSnippetExportSuiteImpl, kSnippetPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSnippetExportSuiteASBImpl, kSnippetPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPageItemExportPolicyImpl, kSnippetPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPageItemImportPolicyImpl, kSnippetPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPageItemSnippetExportSuiteImpl, kSnippetPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAppPrefsExportPolicyImpl, kSnippetPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAppPrefsImportPolicyImpl, kSnippetPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSnippetExportImpl, kSnippetPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportImpl, kSnippetPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectExportPolicyImpl, kSnippetPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectImportPolicyImpl, kSnippetPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSnippetContentScriptProviderImpl, kSnippetPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSnippetScriptImpl, kSnippetPrefix + 18)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportPolicyImpl, kSnippetPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeImportPolicyImpl, kSnippetPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportSuiteImpl, kSnippetPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportSuiteASBImpl, kSnippetPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAppPrefsImportOptionsImpl, kSnippetPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAppPrefsExportDataImpl, kSnippetPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kChangeAppPrefsImportOptionsCmdImpl, kSnippetPrefix + 56)
//gap
DECLARE_PMID(kImplementationIDSpace, kSnippetFileImportProviderImpl, kSnippetPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportValidationImpl, kSnippetPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kSnippetExportProviderImpl, kSnippetPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kSnippetStructureExportProviderImpl, kSnippetPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportServiceImpl, kSnippetPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportProviderImpl, kSnippetPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportPreviewImpl, kSnippetPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportOptionsImpl, kSnippetPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kAppPrefsImportPolicyHelperImpl, kSnippetPrefix + 68)


// Messages
DECLARE_PMID(kMessageIDSpace, kSnippetStaleLinkMsg, kSnippetPrefix + 1)


// Services
DECLARE_PMID(kServiceIDSpace, kSnippetImportService, kSnippetPrefix + 1)

// Errors
DECLARE_PMID(kErrorIDSpace, kSnippetWrongDocType, kSnippetPrefix + 1)
// Not a real error. Used to force the SAX parser to stop.
DECLARE_PMID(kErrorIDSpace, kSnippetStopParsing, kSnippetPrefix + 2)


//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kSnippetFormatPropertyScriptElement,	kSnippetPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSnippetFormatsEnumScriptElement,		kSnippetPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kSnippetObjectScriptElement,			kSnippetPrefix + 3)

enum SnippetScriptIDs
{
	p_SnippetFormat		=	'psif',
	en_SnippetFormat	=	'esif',
	en_INXTraditional	=	'inTa',
	en_INXExpanded		=	'inEx',
	c_Snippet			=	'cSnp',
	c_Snippets			=	'cSns',
};

//GUIDS
// {229ECC34-B916-4231-8915-72C1009C9305}
#define kSnippet_CLSID { 0x229ecc34, 0xb916, 0x4231, { 0x89, 0x15, 0x72, 0xc1, 0x0, 0x9c, 0x93, 0x5 } }
// {EAD853E3-9155-4b8f-88ED-A8849AC7EDD1}
#define kSnippets_CLSID { 0xead853e3, 0x9155, 0x4b8f, { 0x88, 0xed, 0xa8, 0x84, 0x9a, 0xc7, 0xed, 0xd1 } }

#ifndef __ODFRC__
static const int32	kSnippetAttributeID =			'SnPa';
#endif	// __ODFRC__

#endif // __SnippetsID__
