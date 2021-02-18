//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/GuideMgrID.h $
//  
//  Owner: Paul Sorrick
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

#ifndef __GuideMgrID__
#define __GuideMgrID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGuideMgrPrefix	 RezLong(0x5400) 

// <Start IDC>
// PluginID
#define kGuideMgrPanelPluginName 			"Create Guides Dialog"
DECLARE_PMID(kPlugInIDSpace, kGuideMgrPanelPluginID, kGuideMgrPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGuideMgrMenuActionBoss, kGuideMgrPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGuideMgrDialogBoss, kGuideMgrPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGuideMgrHorizontalEditBoxWidgetBoss, kGuideMgrPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGuideMgrVerticalEditBoxWidgetBoss, kGuideMgrPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGuideMgrIntEditBoxWidgetBoss, kGuideMgrPrefix + 6)

// <Interface ID>
// IIDs

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kGuideMgrMenuActionImpl, kGuideMgrPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGuideMgrDialogObserverImpl, kGuideMgrPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGuideMgrDialogControllerImpl, kGuideMgrPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGuideMgrDialogIntEditBoxValidImpl, kGuideMgrPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGuideMgrDialogMeasureEditBoxValidImpl, kGuideMgrPrefix + 5)

// <Widget ID>
// Widget IDs for Guide Manager dialog
//*
DECLARE_PMID(kWidgetIDSpace, kCGRowsStaticTextWidgetID, kGuideMgrPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kCGColsStaticTextWidgetID, kGuideMgrPrefix + 2 )
DECLARE_PMID(kWidgetIDSpace, kRowGutterStaticTextWidgetID, kGuideMgrPrefix + 3 )
DECLARE_PMID(kWidgetIDSpace, kColGutterStaticTextWidgetID, kGuideMgrPrefix + 4 )
//*/
DECLARE_PMID(kWidgetIDSpace, kRowsWidgetID, kGuideMgrPrefix + 5 )
DECLARE_PMID(kWidgetIDSpace, kRowsNudgeWidgetID, kGuideMgrPrefix + 6 )
DECLARE_PMID(kWidgetIDSpace, kColumnsWidgetID, kGuideMgrPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kColumnsNudgeWidgetID, kGuideMgrPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kRowsGutterWidgetID, kGuideMgrPrefix + 9 )
DECLARE_PMID(kWidgetIDSpace, kRowsGutterNudgeWidgetID, kGuideMgrPrefix + 10 )
DECLARE_PMID(kWidgetIDSpace, kColumnsGutterWidgetID, kGuideMgrPrefix + 11 )
DECLARE_PMID(kWidgetIDSpace, kColumnsGutterNudgeWidgetID, kGuideMgrPrefix + 12 )

DECLARE_PMID(kWidgetIDSpace, kFitToMarginsRadioWidgetID, kGuideMgrPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kFitToPagesRadioWidgetID, kGuideMgrPrefix + 14 )
DECLARE_PMID(kWidgetIDSpace, kFitToStaticTextWidgetID, kGuideMgrPrefix + 15 )

DECLARE_PMID(kWidgetIDSpace, kRemoveGuidesCheckBoxWidgetID, kGuideMgrPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kRowsGroupTextWidgetID, kGuideMgrPrefix + 17 )
DECLARE_PMID(kWidgetIDSpace, kColumnsGroupTextWidgetID, kGuideMgrPrefix + 18 )
DECLARE_PMID(kWidgetIDSpace, kOptionsGroupTextWidgetID, kGuideMgrPrefix + 19 )

DECLARE_PMID(kWidgetIDSpace, kGuideMgrParentWidgetId, kGuideMgrPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kFitClusterWidgetId, kGuideMgrPrefix + 21)

DECLARE_PMID(kWidgetIDSpace, kCreateGuidesClusterWidgetId, kGuideMgrPrefix + 25)
// <Action ID>
DECLARE_PMID(kActionIDSpace, kGuideMgrActionID, kGuideMgrPrefix + 1)

#endif




