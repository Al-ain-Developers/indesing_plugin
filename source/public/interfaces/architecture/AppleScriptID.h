//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/AppleScriptID.h $
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
//  Info:	Contains IDs used by the Support for AppleScript plugin.
//  
//========================================================================================

#ifndef __AppleScriptID__
#define __AppleScriptID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kAppleScriptPrefix	 RezLong(0x19800)

// PluginID
#define kAppleScriptPluginName 												"Support for AppleScript"
DECLARE_PMID(kPlugInIDSpace, kAppleScriptPluginID,							kAppleScriptPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kAppleScriptMgrBoss,							kAppleScriptPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kAppleScriptRequestDataBoss,						kAppleScriptPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAppleScriptErrorStringServiceBoss,				kAppleScriptPrefix + 4)
DECLARE_PMID(kClassIDSpace, kAppleScriptFunctorBoss,				kAppleScriptPrefix + 5)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLESCRIPTUTILS,						kAppleScriptPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLESCRIPTCLIENTFUNCTOR,				kAppleScriptPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLESCRIPTCONTEXT,					kAppleScriptPrefix + 3)

// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kAppleScriptMgrImpl,					kAppleScriptPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptEngineImpl,				kAppleScriptPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptRunnerImpl,				kAppleScriptPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptUtilsImpl,					kAppleScriptPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptDataConverterImpl,			kAppleScriptPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptSpecificImpl,				kAppleScriptPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptRequestDataImpl,				kAppleScriptPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptErrorStringServiceImpl,	kAppleScriptPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptCoreFunctorImpl,	kAppleScriptPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptClientFunctorImpl,	kAppleScriptPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAppleScriptContextImpl,		kAppleScriptPrefix + 11)

// Service IDs

// Error Codes
DECLARE_PMID(kErrorIDSpace, kCreateParameterError,							kAppleScriptPrefix + 1)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kAppleScriptSuiteScriptElement,			kAppleScriptPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kTypeNamesSuiteScriptElement,				kAppleScriptPrefix + 2)

//Objects

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCoreCountMethodScriptElement,				kAppleScriptPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kCoreDuplicateMethodScriptElement,			kAppleScriptPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kCoreExistsMethodScriptElement,				kAppleScriptPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCoreCreateMethodScriptElement,				kAppleScriptPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kCoreMoveMethodScriptElement,				kAppleScriptPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kCoreDeleteMethodScriptElement,				kAppleScriptPrefix + 85)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kClassPropertyScriptElement,				kAppleScriptPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kObjectReferencePropertyScriptElement,		kAppleScriptPrefix + 171)

//Enums

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kDontAddToASBasePropertiesMetadataScriptElement,kAppleScriptPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kHideASObjects1MetadataScriptElement,		kAppleScriptPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kHideASObjects2MetadataScriptElement,		kAppleScriptPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kHideASObjects3MetadataScriptElement,		kAppleScriptPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kASIgnoreForGetPropertiesMetadataScriptElement,kAppleScriptPrefix + 244)


// <Ignore>
// Resource IDs
#define kAppleScriptStringsRsrcID				2100
#define kAppleScriptStringsNoTransRsrcID		2200
#define kAppleScriptErrorStringTableRsrcID		2300
#define kAppleScriptScriptStringsRsrcID			2400	//Strings associated with descriptions in script element resources

#endif
