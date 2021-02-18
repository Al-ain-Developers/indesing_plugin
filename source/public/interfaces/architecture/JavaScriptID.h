//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/JavaScriptID.h $
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
//========================================================================================

#ifndef __JAVASCRIPTID__
#define __JAVASCRIPTID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// Resource IDs
#define kjsIconResID						229
#define kJavaScriptStringResID				2100
#define kJavaScriptStringsNoTransRsrcID		2200
#define kJavaScriptErrorStringTableRsrcID	2300
//#define kJavaScriptScriptStringsRsrcID	2400	//Strings associated with descriptions in script element resources


#define kJavaScriptPrefix	 RezLong(0x15F00)

// PluginID
#define kJavaScriptPluginName 					"JavaScript"
DECLARE_PMID(kPlugInIDSpace, kJavaScriptPluginID,							kJavaScriptPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kJavaScriptMgrBoss,								kJavaScriptPrefix + 1)
DECLARE_PMID(kClassIDSpace, kJavaScriptStringRegisterBoss,					kJavaScriptPrefix + 2)
DECLARE_PMID(kClassIDSpace, kJavaScriptRequestDataBoss,						kJavaScriptPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBridgeTalkIdleTaskBoss,						kJavaScriptPrefix + 4)
DECLARE_PMID(kClassIDSpace, kJavaScriptErrorStringServiceBoss,				kJavaScriptPrefix + 5)
DECLARE_PMID(kClassIDSpace, kExtendScriptEngineBoss,						kJavaScriptPrefix + 6)
DECLARE_PMID(kClassIDSpace, kJavaScriptFunctorBoss,							kJavaScriptPrefix + 7)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTUIMGR,							kJavaScriptPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXTENDSCRIPTENGINE,					kJavaScriptPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IBRIDGETALKUTILS,						kJavaScriptPrefix + 3)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IJAVASCRIPTUTILS,						kJavaScriptPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXTENDSCRIPTUTILS,						kJavaScriptPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IJAVASCRIPTCLIENTFUNCTOR,				kJavaScriptPrefix + 7)

// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kJavaScriptMgrImpl,					kJavaScriptPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptRunnerImpl,					kJavaScriptPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptSpecificImpl,				kJavaScriptPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptRequestDataImpl,			kJavaScriptPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kExtendScriptEngineImpl,				kJavaScriptPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptErrorStringServiceImpl,		kJavaScriptPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptDataConverterImpl,			kJavaScriptPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kBridgeTalkIdleTaskImpl,				kJavaScriptPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptClientFunctorImpl,			kJavaScriptPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kScriptUIMgrImpl,						kJavaScriptPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptUtilsImpl,					kJavaScriptPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kExtendScriptUtilsImpl,				kJavaScriptPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kBridgeTalkUtilsImpl,					kJavaScriptPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptEngineImpl,					kJavaScriptPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptCoreFunctorImpl,			kJavaScriptPrefix + 15)

// Error Codes
DECLARE_PMID(kErrorIDSpace, kExitJavaScriptError,							kJavaScriptPrefix + 1)		//not an error; a flag for the runner
DECLARE_PMID(kErrorIDSpace, kUnknownJSObjectTypeError,						kJavaScriptPrefix + 2)		//not an error; a flag for the runner
//gap for other "not an error" error codes
DECLARE_PMID(kErrorIDSpace, kTargetEngineNotFoundError,						kJavaScriptPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kCantDeleteDefaultMainEngine,					kJavaScriptPrefix + 11)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kJavaScriptSuiteScriptElement,				kJavaScriptPrefix + 1)

//Objects

//Events
DECLARE_PMID(kScriptInfoIDSpace, kIndexOperatorMethodScriptElement,			kJavaScriptPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kToSourceMethodScriptElement,				kJavaScriptPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kGetElementsMethodScriptElement,			kJavaScriptPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kToSpecifierMethodScriptElement,			kJavaScriptPrefix + 93)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kIsValidPropertyScriptElement,				kJavaScriptPrefix + 120)

//Enums

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kHideJSObjects1MetadataScriptElement,		kJavaScriptPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kHideJSObjects2MetadataScriptElement,		kJavaScriptPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kHideJSObjects3MetadataScriptElement,		kJavaScriptPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kDontAddToJSBasePropertiesMetadataScriptElement,kJavaScriptPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kJSIgnoreForGetPropertiesMetadataScriptElement,kJavaScriptPrefix + 245)


enum JavaScriptScriptIDs
{
	s_JavaScriptSuite		= 'JSSu',
	e_IndexOperator			= 'OpIn',
	e_toSource				= 'TSrc',
	e_getElements			= 'GElm',
	e_toSpecifier			= 'Xpth',
	p_isValid				= 'isVl',
	p_uid					= 'puid',
	p_packageName			= 'pckN',
	e_Exit					= 'Exit',
	e_Beep					= 'Beep',
} ;

#endif
