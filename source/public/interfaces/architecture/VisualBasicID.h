//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/VisualBasicID.h $
//  
//  Owner: Jonathan W. Brown
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
//  Info:	Contains IDs used by the Support for Visual Basic plugin.
//  
//========================================================================================

#ifndef __VisualBasicID__
#define __VisualBasicID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"
#include "GUID.h"

#define kVisualBasicPrefix	 RezLong(0x19900)

// RsrcID
#define kVisualBasicStringsRsrcID			7000
#define kVisualBasicStringsNoTransRsrcID	7100
#define kVisualBasicErrorStringTableRsrcID	7002
#define kVisualBasicScriptStringsRsrcID		7200	//Strings associated with descriptions in script element resources

// PluginID
#define kVisualBasicPluginName 				"Support for Visual Basic"
DECLARE_PMID(kPlugInIDSpace, kVisualBasicPluginID, kVisualBasicPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kOLEAutomationMgrBoss,						kVisualBasicPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCollectionScriptProviderBoss,				kVisualBasicPrefix + 2)
DECLARE_PMID(kClassIDSpace, kOLEAutomationRequestDataBoss,				kVisualBasicPrefix + 3)
DECLARE_PMID(kClassIDSpace, kVisualBasicErrorStringServiceBoss,			kVisualBasicPrefix + 4)
DECLARE_PMID(kClassIDSpace, kVisualBasicFunctorBoss,					kVisualBasicPrefix + 5)
DECLARE_PMID(kClassIDSpace, kVBActiveScriptContextBoss,					kVisualBasicPrefix + 6)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IVISUALBASICUTILS,					kVisualBasicPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IVISUALBASICCLIENTFUNCTOR,			kVisualBasicPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IVBACTIVESCRIPTCONTEXT,				kVisualBasicPrefix + 3)

// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kOLEAutomationMgrImpl,				kVisualBasicPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kOLEAutomationEngineImpl,			kVisualBasicPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kOLEAutomationRequestDataImpl,		kVisualBasicPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kVisualBasicUtilsImpl,				kVisualBasicPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kVisualBasicRunnerImpl,			kVisualBasicPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kOLEAutomationDataConverterImpl,	kVisualBasicPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCollectionScriptProviderImpl,		kVisualBasicPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kOLEAutomationSpecificImpl,		kVisualBasicPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kVisualBasicErrorStringServiceImpl,kVisualBasicPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kVisualBasicClientFunctorImpl,		kVisualBasicPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kVisualBasicCoreFunctorImpl,		kVisualBasicPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kVBActiveScriptContextImpl,		kVisualBasicPrefix + 14)

// Service IDs

// Error Codes
DECLARE_PMID(kErrorIDSpace, kCantLoadTypeLibraryError,					kVisualBasicPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kArgumentsAreReadOnlyError,					kVisualBasicPrefix + 2)

//
//Script Element IDs
//

//Suites
//DECLARE_PMID(kScriptInfoIDSpace, kVisualBasicSuiteScriptElement,			kVisualBasicPrefix + 1)

//Objects

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateCollectionMethodScriptElement,		kVisualBasicPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kAddToCollectionMethodScriptElement,		kVisualBasicPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveFromCollectionMethodScriptElement,	kVisualBasicPrefix + 102)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kCountPropertyScriptElement,				kVisualBasicPrefix + 180)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kObsoleteVBEnumeratorsEnumScriptElement,	kVisualBasicPrefix + 220)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kSkipVerifyObjectSpecifierParamMetadataScriptElement,kVisualBasicPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kHideVBObjects1MetadataScriptElement,		kVisualBasicPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kHideVBObjects2MetadataScriptElement,		kVisualBasicPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kHideVBObjects3MetadataScriptElement,		kVisualBasicPrefix + 243)


//ScriptIDs
enum VisualBasicScriptIDs
{
	//s_VisualBasicSuite		= 'VBSt',
	e_CreateCollection		= 'NewC'
} ;


//GUIDS
// {7ACE5CC7-834E-4536-BCDC-04445CD174D8}
#define kIID_ICOMObject		{ 0x7ace5cc7, 0x834e, 0x4536, { 0xbc, 0xdc, 0x4, 0x44, 0x5c, 0xd1, 0x74, 0xd8 } }
DECLARE_GUID( IID_ICOMObject, kIID_ICOMObject ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code
// {C7C3F5A2-88A3-11D0-ABCB-00A0C90FFFC0}
#define kFolder_CLSID { 0xC7C3F5A2, 0x88A3, 0x11D0, { 0xAB, 0xCB,  0x00,  0xA0,  0xC9,  0x0F,  0xFF,  0xC0 } }
DECLARE_GUID( Folder_CLSID, kFolder_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code
// {C7C3F5A4-88A3-11D0-ABCB-00A0C90FFFC0}
#define kFile_CLSID { 0xC7C3F5A4, 0x88A3, 0x11D0, { 0xAB, 0xCB,  0x00,  0xA0,  0xC9,  0x0F,  0xFF,  0xC0 } }
DECLARE_GUID( File_CLSID, kFile_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code

#endif
