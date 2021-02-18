//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/StepRepeatID.h $
//  
//  Owner: jshankar
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
//  Contains IDs used by the copy repeat plug-in
//  
//========================================================================================

#ifndef __COPY_REPEAT_ID_H__
#define __COPY_REPEAT_ID_H__

#include "IDFactory.h"

#define kStepRepeatPrefix RezLong(0xaa00)

// PluginID
#define kStepRepeatPluginName		"StepRepeat"
DECLARE_PMID(kPlugInIDSpace, kStepRepeatPluginID, kStepRepeatPrefix + 1)

// <Class ID> 
DECLARE_PMID(kClassIDSpace, kStepRepeatDialogBoss, kStepRepeatPrefix + 1)
DECLARE_PMID(kClassIDSpace, kStepRepeatMenuActionBoss, kStepRepeatPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kStepAndRepeatCmdBoss, kStepRepeatPrefix + 4)
DECLARE_PMID(kClassIDSpace, kRepeatCountEditboxBoss, kStepRepeatPrefix + 5)
DECLARE_PMID(kClassIDSpace, kVerticalOffsetEditboxBoss, kStepRepeatPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHorizontalOffsetEditboxBoss, kStepRepeatPrefix + 7)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kStepRepeatDialogObserverImpl, kStepRepeatPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kStepRepeatDialogControllerImpl, kStepRepeatPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kStepRepeatMenuActionImpl, kStepRepeatPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kStepRepeatEditIntValidationImpl, kStepRepeatPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kStepAndRepeatCmdImpl, kStepRepeatPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kStepAndRepeatCmdDataImpl, kStepRepeatPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStepRepeatEditMeasureValidationImpl, kStepRepeatPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kStepAndRepeatDialogPrefDataImpl, kStepRepeatPrefix + 8)



// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ISTEPANDREPEATCMDDATA, kStepRepeatPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTEPANDREPEATDIALOGPREFDATA, kStepRepeatPrefix + 2)

// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kStepRepeatWidgetID0, kStepRepeatPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kRepeatCountNudgeWidgetID, kStepRepeatPrefix +  2)
DECLARE_PMID(kWidgetIDSpace, kRepeatCountWidgetID, kStepRepeatPrefix +  3)
DECLARE_PMID(kWidgetIDSpace, kHorizontalOffsetNudgeWidgetID, kStepRepeatPrefix +  4)
DECLARE_PMID(kWidgetIDSpace, kHorizontalOffsetWidgetID, kStepRepeatPrefix +  5)
DECLARE_PMID(kWidgetIDSpace, kVerticalOffsetNudgeWidgetID, kStepRepeatPrefix +  6)
DECLARE_PMID(kWidgetIDSpace, kVerticalOffsetWidgetID, kStepRepeatPrefix +  7)
DECLARE_PMID(kWidgetIDSpace, kRepeatCountTextWidgetID, kStepRepeatPrefix +  8)
DECLARE_PMID(kWidgetIDSpace, kHorizontalOffsetTextWidgetID, kStepRepeatPrefix +  9)
DECLARE_PMID(kWidgetIDSpace, kVerticalOffsetTextWidgetID, kStepRepeatPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kStepRepeatParentWidgetID, kStepRepeatPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSRButtonsPanelWidgetID, kStepRepeatPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSRVerticalEditNumPanelWidgetID, kStepRepeatPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSRHorizontalEditNumPanelWidgetID, kStepRepeatPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSRRepeatEditNumPanelWidgetID, kStepRepeatPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSRStaticTextPanelWidgetID, kStepRepeatPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kSREditBoxesColsPanelWidgetID, kStepRepeatPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kCreateAsGridCheckboxWidgetID, kStepRepeatPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kColumnCountNudgeWidgetID, kStepRepeatPrefix +  19)
DECLARE_PMID(kWidgetIDSpace, kColumnCountWidgetID, kStepRepeatPrefix +  20)
DECLARE_PMID(kWidgetIDSpace, kColumnCountTextWidgetID, kStepRepeatPrefix +  21)
DECLARE_PMID(kWidgetIDSpace, kSRColumnEditNumPanelWidgetID, kStepRepeatPrefix +  22)
DECLARE_PMID(kWidgetIDSpace, kSRRepeatGroupWidgetID, kStepRepeatPrefix +  23)
DECLARE_PMID(kWidgetIDSpace, kSRRepeatGroupTextWidgetID, kStepRepeatPrefix +  24)
DECLARE_PMID(kWidgetIDSpace, kSROffsetSpacingGroupWidgetID, kStepRepeatPrefix +  25)
DECLARE_PMID(kWidgetIDSpace, kSROffsetSpacingGroupTextWidgetID, kStepRepeatPrefix +  26)

// <Action ID> 
DECLARE_PMID(kActionIDSpace, kStepRepeatActionID, kStepRepeatPrefix + 1)
DECLARE_PMID(kActionIDSpace, kStepRepeatSepActionID, kStepRepeatPrefix + 2)

#endif // __COPY_REPEAT_ID_H__
