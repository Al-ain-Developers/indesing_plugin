//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/PathTypeUIID.h $
//  
//  Owner: Lonnie Millett
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
//  Contains IDs used by Path Type UI plug-in
//  
//========================================================================================

#ifndef __PathTypeUIID__
#define __PathTypeUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPathTypeUIPrefix	 RezLong(0x1D100)

//PICT resource IDs
#define kPathTypeAlignPictBaseID 1010

//---------------------------------------------------------------
// <Start IDC>
//---------------------------------------------------------------

// PluginID
#define kPathTypeUIPluginName 		"Path Type UI"

START_IDS()
DECLARE_PMID(kPlugInIDSpace, kPathTypeUIPluginID, kPathTypeUIPrefix + 1)


//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------

// ClassIDs
DECLARE_PMID(kClassIDSpace, kTOPHorzToolBoss, kPathTypeUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTOPVertToolBoss, kPathTypeUIPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kTOPHorzToolTrackerBoss, kPathTypeUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTOPVertToolTrackerBoss, kPathTypeUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTOPTrackerRegisterBoss, kPathTypeUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTOPMoveTrackerBoss, kPathTypeUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTOPResizeTrackerBoss, kPathTypeUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTOPMenuActionBoss, kPathTypeUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kTOPDlgBoss, kPathTypeUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kInvalSelectedFramesCmdBoss, kPathTypeUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kTOPResizeToolBoss, kPathTypeUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTOPMoveToolBoss, kPathTypeUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kTOPTestMenuBoss, kPathTypeUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kTOPSelectionFilterBoss, kPathTypeUIPrefix + 15)

//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kTOPHorzToolImpl, kPathTypeUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTOPVertToolImpl, kPathTypeUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTOPHorzToolCursorProviderImpl, kPathTypeUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTOPVertToolCursorProviderImpl, kPathTypeUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTOPHorzToolTrackerImpl, kPathTypeUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTOPVertToolTrackerImpl, kPathTypeUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTOPTrackerRegisterImpl, kPathTypeUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kTOPMoveTrackerImpl, kPathTypeUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kTOPResizeTrackerImpl, kPathTypeUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kTOPMenuActionImpl, kPathTypeUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTOPDlgControllerImpl, kPathTypeUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTOPDlgObserverImpl, kPathTypeUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kInvalSelectedFramesCmdImpl, kPathTypeUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTOPTestMenuImpl, kPathTypeUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTOPSelectionFilterImpl, kPathTypeUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTOPFrameEventActionImpl, kPathTypeUIPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kTOPFrameObserverImpl, kPathTypeUIPrefix + 30) Where is this?

//---------------------------------------------------------------
// <Widget ID>
//---------------------------------------------------------------

// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kTOPDlgId, kPathTypeUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTOPDeleteTextButtonWidgetId, kPathTypeUIPrefix + 2)
//						kPathTypeUIPrefix + 3
//						kPathTypeUIPrefix + 4
//						kPathTypeUIPrefix + 5
//						kPathTypeUIPrefix + 6
//						kPathTypeUIPrefix + 7
DECLARE_PMID(kWidgetIDSpace, kTOPTextAlignComboWidgetId,		kPathTypeUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kTOPPathAlignComboWidgetId,		kPathTypeUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kTOPEffectComboWidgetId,			kPathTypeUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kTOPOverlapOffsetComboWidgetId,	kPathTypeUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kTOPEffectLabelWidgetId,			kPathTypeUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kTOPOverlapOffsetNudgeWidgetId,	kPathTypeUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kTOPHorzToolWidgetid,				kPathTypeUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kTOPVertToolWidgetId,				kPathTypeUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTOPAlignTextLabelWidgetId,		kPathTypeUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kTOPToPathLabelWidgetId,			kPathTypeUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kOverlapOffsetLabelWidgetId,		kPathTypeUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kTOPFlipButtonWidgetId,			kPathTypeUIPrefix + 19)

//---------------------------------------------------------------
// <Interface ID>
//---------------------------------------------------------------

// <Action ID>
DECLARE_PMID(kActionIDSpace, kTOPOptionsMenuActionID, kPathTypeUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTOPDeleteMenuActionID, kPathTypeUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTOPHorzToolActionID, kPathTypeUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kTOPVertToolActionID, kPathTypeUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kTOPMenuSepActionID, kPathTypeUIPrefix + 5)

END_IDS()

#endif
