//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/AutoLayoutPanelID.h $
//  
//  Owner: Rich Gartland
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __AutoLayoutPanelID__
#define __AutoLayoutPanelID__

#include "IDFactory.h"

#define kAutoLayoutPanelPrefix		RezLong(0x7100)		/*  Prefix registered in DeveloperPrefix.h */

// <Start IDC>
// PluginID
#define kAutoLayoutPanelPluginName 		"Layout Adjustment Panel"
DECLARE_PMID(kPlugInIDSpace, kAutoLayoutPanelPluginID, kAutoLayoutPanelPrefix + 1)

// <Class ID>
// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kAutoLayoutDialogWidgetBoss, kAutoLayoutPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kAutoLayoutPrefsMenuActionBoss, kAutoLayoutPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAutoLayoutOnWidgetBoss, kAutoLayoutPanelPrefix + 4)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kAutoLayoutOnWidget, kAutoLayoutPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kStretchGraphicsWidget, kAutoLayoutPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLoosenLocksWidget, kAutoLayoutPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kIgnoreGuidesWidget, kAutoLayoutPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kAutoSnapZoneEditBoxWidget, kAutoLayoutPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kMoveGuidesWidget, kAutoLayoutPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kStickyGuidesWidget, kAutoLayoutPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kAutoLayoutDialogPanelWidgetId, kAutoLayoutPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kGroupPanelHeader1, kAutoLayoutPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kGroupPanelHeader2, kAutoLayoutPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kAutoLayoutGroupWidgetId, kAutoLayoutPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSnapZoneTextWidgetId, kAutoLayoutPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kAutoSnapZoneNudgeWidget, kAutoLayoutPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kAutoLayoutPanelWidgetId, kAutoLayoutPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kAutoLayoutFittedPanelWidget, kAutoLayoutPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kALButtonsPanelWidgetID, kAutoLayoutPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kALLiquidLayoutGroupWidgetID, kAutoLayoutPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kALLiquidLayoutWarningInfoWidgetId, kAutoLayoutPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kALLiquidLayoutWarningIconWidgetId, kAutoLayoutPanelPrefix + 19)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kDocPrefObserver, kAutoLayoutPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutDialogObserver, kAutoLayoutPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutDialogTestMenu, kAutoLayoutPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutPrefsMenuAction, kAutoLayoutPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutDialogController, kAutoLayoutPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutPanelCreator, kAutoLayoutPanelPrefix + 6)
// gap
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutOnObserver, kAutoLayoutPanelPrefix + 8)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kAutoLayoutPrefsActionID, kAutoLayoutPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kAutoLayoutSepActionID, kAutoLayoutPanelPrefix + 2)
#endif
	// __AutoLayoutPanelID__
