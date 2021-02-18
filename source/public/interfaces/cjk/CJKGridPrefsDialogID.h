//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/CJKGridPrefsDialogID.h $
//  
//  Owner: Tetsuya Araki
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

#ifndef __CJKGridPrefsDialogID__
#define __CJKGridPrefsDialogID__


#include "CrossPlatformTypes.h"
#include "IDFactory.h"



/* doublecheck with AdobePrefix.h */
#define kCJKGridPrefsDialogPrefix				RezLong(0xd000)


// PluginID
#define kCJKGridPrefsDialogPluginName 			"CJKGridPrefsDialog"


DECLARE_PMID(kPlugInIDSpace, kCJKGridPrefsDialogPluginID, kCJKGridPrefsDialogPrefix + 1)


// Double check kCJKGridPrefsDialogPrefix with DeveloperPrefix.h



// <Start IDC>
// <Class ID>
//Class IDs
DECLARE_PMID(kClassIDSpace, kCJKGridPrefsDialogBoss, kCJKGridPrefsDialogPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kCJKPrefsMenuActionBoss, kCJKGridPrefsDialogPrefix + 3)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDUIUTILS, kCJKGridPrefsDialogPrefix + 1)

// <Implementation ID>
//Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsDialogControllerImpl, kCJKGridPrefsDialogPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsDialogObserverImpl, kCJKGridPrefsDialogPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCJKGridUIUtilsImpl, kCJKGridPrefsDialogPrefix + 3) 
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsMenuActionImpl, kCJKGridPrefsDialogPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsPanelCreatorImpl, kCJKGridPrefsDialogPrefix + 5)


// <Widget ID>
//Widget IDs
DECLARE_PMID(kWidgetIDSpace, kCJKGridPrefsDialogPanelWidgetID, kCJKGridPrefsDialogPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kCJKGridGroupPanelWidgetID, kCJKGridPrefsDialogPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kCJKGridGroupPanelTitleTextWidgetID, kCJKGridPrefsDialogPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kCJKGridCellShapeTextWidgetID, kCJKGridPrefsDialogPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kCJKGridCellShapeWidgetID, kCJKGridPrefsDialogPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kCJKGridCellShapeNudgeWidgetID, kCJKGridPrefsDialogPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kCJKGridICFModeTextWidgetID, kCJKGridPrefsDialogPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kCJKGridICFModeWidgetID, kCJKGridPrefsDialogPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kCJKGridSingleColorModeTextWidgetID, kCJKGridPrefsDialogPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kCJKGridSingleColorModeWidgetID, kCJKGridPrefsDialogPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kCJKGridNthCellWidgetID, kCJKGridPrefsDialogPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kCJKGridNthCellTextWidgetID, kCJKGridPrefsDialogPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCJKGridViewLimitTextWidgetID, kCJKGridPrefsDialogPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCJKGridViewLimitWidgetID, kCJKGridPrefsDialogPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kCJKGridViewLimitNudgeWidgetID, kCJKGridPrefsDialogPrefix + 15)

DECLARE_PMID(kWidgetIDSpace, kFrameGridGroupPanelWidgetID, kCJKGridPrefsDialogPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kFrameGridGroupPanelTitleTextWidgetID, kCJKGridPrefsDialogPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kFrameGridApplyGridTextWidgetID, kCJKGridPrefsDialogPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kFrameGridApplyGridWidgetID, kCJKGridPrefsDialogPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kFrameGridCharCountSizeTextWidgetID, kCJKGridPrefsDialogPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kFrameGridCharCountSizeNudgeWidgetID, kCJKGridPrefsDialogPrefix + 25)
//DECLARE_PMID(kWidgetIDSpace, kFrameGridCharCountSizeWidgetID, kCJKGridPrefsDialogPrefix + 26)

DECLARE_PMID(kWidgetIDSpace, kPageGridGroupPanelWidgetID, kCJKGridPrefsDialogPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPageGridGroupPanelTitleTextWidgetID, kCJKGridPrefsDialogPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPageGridGenericPanellWidgetId, kCJKGridPrefsDialogPrefix + 32)
//DECLARE_PMID(kWidgetIDSpace, kPageGridColorSwatchWidgetID, kCJKGridPrefsDialogPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kPageGridColorDropDownWidgetID, kCJKGridPrefsDialogPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kPageGridColorTextWidgetID, kCJKGridPrefsDialogPrefix + 35)
//DECLARE_PMID(kWidgetIDSpace, kCJKGridSeparatorWidgetID, kCJKGridPrefsDialogPrefix + 20)

// <Action ID>
//Action IDs
DECLARE_PMID(kActionIDSpace, kCJKGridPrefsActionID, kCJKGridPrefsDialogPrefix + 1)


#endif //__CJKGridPrefsDialogID__
