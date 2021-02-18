//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/charpathid.h $
//  
//  Owner: ?
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

#ifndef __CHARPATHID__
#define __CHARPATHID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//#define kCharPathPrefix_obsolete	RezLong(0x40A00)
#define kCharPathPrefix				RezLong(0x13B00)

// <Start IDC>
// PluginIDs
#define kCharPathPluginName				"Create Outlines"
//DECLARE_PMID(kPlugInIDSpace, kCharPathPluginID_obsolete, kCharPathPrefix_obsolete + 1)
DECLARE_PMID(kPlugInIDSpace, kCharPathPluginID, kCharPathPrefix + 1)


//---------------------------------------------------------------
// ClassIDs / Boss IDs
//---------------------------------------------------------------

//DECLARE_PMID(kClassIDSpace, kCharPathItemBoss, kCharPathPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kCharPathToolBoss, kCharPathPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kCharPathTrackerBoss, kCharPathPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kCharPathResizeTrackerBoss, kCharPathPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kCharPathTrackerRegisterBoss, kCharPathPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kCharPathTestMenuBoss, kCharPathPrefix + 6)	// Moved to Text Panel plugin
//DECLARE_PMID(kClassIDSpace, kCharPathToolRegisterBoss, kCharPathPrefix + 7)
//gap
//DECLARE_PMID(kClassIDSpace, kCharPathMenuComponentBoss, kCharPathPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kCreateOutlineCmdBoss, kCharPathPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCreateOutlinesPortCmdBoss, kCharPathPrefix + 11)
//gap
DECLARE_PMID(kClassIDSpace, kCharPathErrorStringServiceBoss, kCharPathPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCreateOutlinesTextCmdBoss, kCharPathPrefix + 15)
DECLARE_PMID(kClassIDSpace, kCreateOutlinesFrameCmdBoss, kCharPathPrefix + 16)
DECLARE_PMID(kClassIDSpace, kCreateOutlinesTableCmdBoss, kCharPathPrefix + 17)
DECLARE_PMID(kClassIDSpace, kCOTextScriptProviderBoss, kCharPathPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCOFrameScriptProviderBoss, kCharPathPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCOTableScriptProviderBoss, kCharPathPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCOSplineItemBoss, kCharPathPrefix + 21)	//jwb 4/16/02 Not in use; intended for use if a create outlines object has different implementations than a regular spline item
DECLARE_PMID(kClassIDSpace, kCreateOutlinesConversionProviderBoss, kCharPathPrefix + 22)

// <Interface ID>
// IIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_ICHARPATHDATA, kCharPathPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEOUTLINESUTILS, kCharPathPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECMDCOLLECTION, kCharPathPrefix + 3)	//used with kCmdCollectionImpl
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEOUTLINESDEBUG, kCharPathPrefix + 4)

//---------------------------------------------------------------
// Implementation IDs
//---------------------------------------------------------------
//DECLARE_PMID(kImplementationIDSpace, kCharPathToolImpl, kCharPathPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kCharPathShapeImpl, kCharPathPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kCharPathDataImpl, kCharPathPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kCharPathToolDataImpl, kCharPathPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kCharPathTrackerImpl, kCharPathPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kCharPathTrackerRegisterImpl, kCharPathPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kCharPathTestMenuImpl, kCharPathPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kCharPathToolRegisterImpl, kCharPathPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kCharPathMenuComponentImpl, kCharPathPrefix + 9)	// Moved to Text panel plugin
//DECLARE_PMID(kImplementationIDSpace, kCreateOutlineCmdImpl, kCharPathPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesLayoutCSBImpl, kCharPathPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesTextCSBImpl, kCharPathPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCharPathErrorStringServiceImpl, kCharPathPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesGraphicsPortImpl, kCharPathPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesPortCmdImpl, kCharPathPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesPortDataImpl, kCharPathPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesTableCSBImpl, kCharPathPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesTextCmdImpl, kCharPathPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesFrameCmdImpl, kCharPathPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesTableCmdImpl, kCharPathPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesUtilsImpl, kCharPathPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCOTextScriptProviderImpl, kCharPathPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCOFrameScriptProviderImpl, kCharPathPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCOTableScriptProviderImpl, kCharPathPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kCOGraphicFrameShapeImpl, kCharPathPrefix + 25)	//jwb 4/16/02 Not in use; intended for use if a create outlines object has different implementations than a regular spline item
//DECLARE_PMID(kImplementationIDSpace, kCOPathPageItemImpl, kCharPathPrefix + 26)		//jwb 4/16/02 Not in use; intended for use if a create outlines object has different implementations than a regular spline item

// <Action ID>
//DECLARE_PMID(kActionIDSpace, kCreateOutlinesActionID, kCharPathPrefix + 1)
//DECLARE_PMID(kActionIDSpace, kCreateOutlinesWithoutDeletingTextActionID, kCharPathPrefix + 2)
//DECLARE_PMID(kActionIDSpace, kCreateOutlinesSepActionID, kCharPathPrefix + 3)

// Error Codes
// NOTE:  The offset is used to find the corresponding error string
DECLARE_PMID(kErrorIDSpace, kNoPathCreated, kCharPathPrefix + 1)	//not necessarily an error
DECLARE_PMID(kErrorIDSpace, kPathCreated, kCharPathPrefix + 2)		//not necessarily an error
DECLARE_PMID(kErrorIDSpace, kPathCompleted, kCharPathPrefix + 3)	//not necessarily an error
DECLARE_PMID(kErrorIDSpace, kInvalidSelectionError, kCharPathPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kNoCharactersSelectedError, kCharPathPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kBadCommandDataError, kCharPathPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCreateOnLockedLayerError, kCharPathPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kCreateOutlineSBIXError, kCharPathPrefix + 14)

//
//Script Element IDs
//

//Suites
//DECLARE_PMID(kScriptInfoIDSpace, k???SuiteScriptElement,				kCharPathPrefix + 1)

//Objects
//DECLARE_PMID(kScriptInfoIDSpace, k???ObjectScriptElement,				kCharPathPrefix + 40)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateOutlinesMethodScriptElement,		kCharPathPrefix + 80)

//Properties
//DECLARE_PMID(kScriptInfoIDSpace, k???PropertyScriptElement,			kCharPathPrefix + 140)

//Enums
//DECLARE_PMID(kScriptInfoIDSpace, k???EnumScriptElement,				kCharPathPrefix + 220)

#endif // __CharPathID__
