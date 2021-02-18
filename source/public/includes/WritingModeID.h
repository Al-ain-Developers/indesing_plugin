//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WritingModeID.h $
//  
//  Owner: Kevin Van Wiel
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

#ifndef __WritingModeID__
#define __WritingModeID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


//========================================================================================
//	NOTE: WritingModeID2.h uses this prefix+100
//========================================================================================
#define kWMPrefix	RezLong(0xa200)	 


// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kWritingModePluginName 				"Galley"
DECLARE_PMID(kPlugInIDSpace, kWritingModePluginID, kWMPrefix + 1)

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kWMTextEngine, kWMPrefix + 1)
DECLARE_PMID(kClassIDSpace, kWritingModeTestMenuBoss, kWMPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kDeleteWritingViewCmdBoss, kWMPrefix + 6)
DECLARE_PMID(kClassIDSpace, kRecomposeCmdBoss, kWMPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kWritingFrameBoss, kWMPrefix + 9)
DECLARE_PMID(kClassIDSpace, kFakeSpreadBoss, kWMPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kWritingStringRegistryBoss, kWMPrefix + 13)
DECLARE_PMID(kClassIDSpace, kGalleyTextEngineBoss, kWMPrefix + 14)
DECLARE_PMID(kClassIDSpace, kZeroFrameBoss, kWMPrefix + 16)
//gap
DECLARE_PMID(kClassIDSpace, kSetWaxLineCmdBoss, kWMPrefix + 18)
DECLARE_PMID(kClassIDSpace, kShowHidePaletteCmdBoss, kWMPrefix + 19)
DECLARE_PMID(kClassIDSpace, kOpenObserverAppActionBoss, kWMPrefix + 20)

//Print and PDFExport
//gap
DECLARE_PMID(kClassIDSpace, kInCopyGalleySettingDataBoss, kWMPrefix + 54)

// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IWRITINGOBSERVER, kWMPrefix + 4)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWLINEDATA, kWMPrefix + 9)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENOBSERVER, kWMPrefix + 12)
// removed IID_ITEXTVIEWMODEDATA, kWMPrefix + 13
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTUIDDATA, kWMPrefix + 14)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTEXTADORNMENT, kWMPrefix + 16)
//gap

//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYGALLEYSETTINGDATA, kWMPrefix + 52)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYEDITORWINDOWSIZE, kWMPrefix + 54)

// <Implementation ID>
//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------
//gap

DECLARE_PMID(kImplementationIDSpace, kWritingStringRegistryImpl, kWMPrefix + 20)

//gap

DECLARE_PMID(kImplementationIDSpace, kLayoutViewLineDataImpl, kWMPrefix + 29)

DECLARE_PMID(kImplementationIDSpace, kShowHidePaletteCmdImpl, kWMPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kOpenObserverAppActionImpl, kWMPrefix + 37)



//gap

DECLARE_PMID(kImplementationIDSpace, kInCopyGalleySettingDataImpl, kWMPrefix + 65)


// InvalHandlerTypeID
DECLARE_PMID(kInvalHandlerIDSpace, kWritingModeInvalHandlerID, kWMPrefix + 1)


#endif	//__WritingModeID__
