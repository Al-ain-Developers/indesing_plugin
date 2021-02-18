//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/PanelEditorID.h $
//  
//  Owner: Michael Burbidge
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

#pragma once
#ifndef __PanelEditorID__
#define __PanelEditorID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPanelEditorPrefix	 RezLong(0x4500)

// PluginID
#define kPanelEditorPluginName 			"PanelEdit"
START_IDS()

DECLARE_PMID(kPlugInIDSpace, kPanelEditorPluginID, kPanelEditorPrefix + 1)

// <Start IDC>
// <Class ID>
// ----- Class IDs -----

DECLARE_PMID(kClassIDSpace, kPanelEditorMenuComponentBoss, kPanelEditorPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPanelEditorEHBoss, kPanelEditorPrefix + 2)
DECLARE_PMID(kClassIDSpace, kWidgetTrackerBoss, kPanelEditorPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAddWidgetPanelBoss, kPanelEditorPrefix + 4)
DECLARE_PMID(kClassIDSpace, kMenuAcceleratorsDialogBoss, kPanelEditorPrefix + 5)
DECLARE_PMID(kClassIDSpace, kWidgetGeometryPanelWidgetBoss, kPanelEditorPrefix + 6)
DECLARE_PMID(kClassIDSpace, kAlignLeftWidgetCmdBoss, kPanelEditorPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAlignRightWidgetCmdBoss, kPanelEditorPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAlignTopWidgetCmdBoss, kPanelEditorPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAlignBottomWidgetCmdBoss, kPanelEditorPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCenterHorzWidgetCmdBoss, kPanelEditorPrefix + 11)
DECLARE_PMID(kClassIDSpace, kCenterVertWidgetCmdBoss, kPanelEditorPrefix + 12)
DECLARE_PMID(kClassIDSpace, kNudgeLeftWidgetCmdBoss, kPanelEditorPrefix + 13)
DECLARE_PMID(kClassIDSpace, kNudgeRightWidgetCmdBoss, kPanelEditorPrefix + 14)
DECLARE_PMID(kClassIDSpace, kNudgeUpWidgetCmdBoss, kPanelEditorPrefix + 15)
DECLARE_PMID(kClassIDSpace, kNudgeDownWidgetCmdBoss, kPanelEditorPrefix + 16)
DECLARE_PMID(kClassIDSpace, kShrinkHorzWidgetCmdBoss, kPanelEditorPrefix + 17)
DECLARE_PMID(kClassIDSpace, kShrinkVertWidgetCmdBoss, kPanelEditorPrefix + 18)
DECLARE_PMID(kClassIDSpace, kExpandHorzWidgetCmdBoss, kPanelEditorPrefix + 19)
DECLARE_PMID(kClassIDSpace, kExpandVertWidgetCmdBoss, kPanelEditorPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAssignAcceleratorsButtonBoss, kPanelEditorPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAcceleratorMenusTreeWidgetBoss, kPanelEditorPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPanelEditorCmdInterceptorBoss, kPanelEditorPrefix + 23)
DECLARE_PMID(kClassIDSpace, kNormalizeWidgetCmdBoss, kPanelEditorPrefix + 24)
DECLARE_PMID(kClassIDSpace, kEditableMenuAcceleratorWidgetBoss, kPanelEditorPrefix + 25)
DECLARE_PMID(kClassIDSpace, kMenuAcceleratorLockBoss, kPanelEditorPrefix + 26)

// <Implementation ID>
// ----- Implementation IDs -----

DECLARE_PMID(kImplementationIDSpace, kPanelEditorMenuComponentImpl, kPanelEditorPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kPanelEditorKBSCImpl, kPanelEditorPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPanelEditorEHImpl, kPanelEditorPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kWidgetTrackerImpl, kPanelEditorPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAddWidgetControllerImpl, kPanelEditorPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPanelEditorDataImpl, kPanelEditorPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCreateDialogStreamImpl, kPanelEditorPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorControllerImpl, kPanelEditorPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kWidgetGeometryThreadImpl, kPanelEditorPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kWidgetGeometryPanelImpl, kPanelEditorPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAlignLeftWidgetCmdImpl, kPanelEditorPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAlignRightWidgetCmdImpl, kPanelEditorPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kAlignTopWidgetCmdImpl, kPanelEditorPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAlignBottomWidgetCmdImpl, kPanelEditorPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCenterHorzWidgetCmdImpl, kPanelEditorPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCenterVertWidgetCmdImpl, kPanelEditorPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kWidgetListCmdDataImpl, kPanelEditorPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kNudgeLeftWidgetCmdImpl, kPanelEditorPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kNudgeRightWidgetCmdImpl, kPanelEditorPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kNudgeUpWidgetCmdImpl, kPanelEditorPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kNudgeDownWidgetCmdImpl, kPanelEditorPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kShrinkHorzWidgetCmdImpl, kPanelEditorPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kShrinkVertWidgetCmdImpl, kPanelEditorPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kExpandHorzWidgetCmdImpl, kPanelEditorPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kExpandVertWidgetCmdImpl, kPanelEditorPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kAssignAcceleratorsButtonObserverImpl, kPanelEditorPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsTreeViewWidgetMgrImpl, kPanelEditorPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPanelEditorCmdInterceptorImpl, kPanelEditorPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kNormalizeWidgetCmdImpl, kPanelEditorPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kPanelEditorObserverImpl, kPanelEditorPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsTreeEHImpl, kPanelEditorPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsTreeAdapterImpl, kPanelEditorPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsDialogDataImpl, kPanelEditorPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsDataImpl, kPanelEditorPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsEditingAttributesImpl, kPanelEditorPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsLockObserverImpl, kPanelEditorPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsLockEventHandlerImpl, kPanelEditorPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsLockViewImpl, kPanelEditorPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kMenuAcceleratorsAccelObserverImpl, kPanelEditorPrefix + 39)

// <Interface ID>
// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace, IID_IPANELEDITORDATA, kPanelEditorPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETLISTCMDDATA, kPanelEditorPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUACCELERATORSDATA, kPanelEditorPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUACCELERATORSDIALOGDATA, kPanelEditorPrefix + 4)

// <Widget ID>
// ----- Widget IDs -----

DECLARE_PMID(kWidgetIDSpace, kClassIdWidgetID, kPanelEditorPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kLeftWidgetID, kPanelEditorPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTopWidgetID, kPanelEditorPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kRightWidgetID, kPanelEditorPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kBottomWidgetID, kPanelEditorPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kWidth_WidgetID, kPanelEditorPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kHeight_WidgetID, kPanelEditorPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kSourceFileWidgetID, kPanelEditorPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kWidgetIDWidgetID, kPanelEditorPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kParentWidgetIDWidgetID, kPanelEditorPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kPanelEditorParentWidgetId, kPanelEditorPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kWidgetIdTextWidgetId, kPanelEditorPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kParentIdTextWidgetId, kPanelEditorPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLeftTextWidgetId, kPanelEditorPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kRightTextWidgetId, kPanelEditorPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTopTextWidgetId, kPanelEditorPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kBottomTextWidgetId, kPanelEditorPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kWidthTextWidgetId, kPanelEditorPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kHeightTextWidgetId, kPanelEditorPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPanelEditorStatusWidgetId, kPanelEditorPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kInstructionsWidgetId, kPanelEditorPrefix + 21)

DECLARE_PMID(kWidgetIDSpace, kKBSCInstruction1WidgetID, kPanelEditorPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kKBSCInstruction2WidgetID, kPanelEditorPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kKBSCInstruction3WidgetID, kPanelEditorPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kKBSCInstruction4WidgetID, kPanelEditorPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kKBSCInstruction5WidgetID, kPanelEditorPrefix + 26)
#define kFirstKBSCInstructionsWidgetID kKBSCInstruction1WidgetID
#define kLastKBSCInstructionsWidgetID kKBSCInstruction5WidgetID
//gap
DECLARE_PMID(kWidgetIDSpace, kNumChildWidgetID, kPanelEditorPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kNumChildTextWidgetId, kPanelEditorPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kClassIDWidgetID, kPanelEditorPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kClassIdTextWidgetId, kPanelEditorPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kGeometryGroupWidgetId, kPanelEditorPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kInstructionGroupWidgetId, kPanelEditorPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kEnabledTextWidgetId, kPanelEditorPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kEnabledWidgetID, kPanelEditorPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kUntranslatedLabelWidgetID, kPanelEditorPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kUntranslatedWidgetID, kPanelEditorPrefix + 72)

DECLARE_PMID(kWidgetIDSpace, kEveInfoGroupWidgetID, kPanelEditorPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kEveInfoLabelWidgetID, kPanelEditorPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kEveArrangementLabelWidgetID, kPanelEditorPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kEveArrangementWidgetID, kPanelEditorPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kEveSpaceAfterLabelWidgetID, kPanelEditorPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kEveSpaceAfterWidgetID, kPanelEditorPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kEveAlignLabelWidgetID, kPanelEditorPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kEveAlignWidgetID, kPanelEditorPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kEveChildAlignLabelWidgetID, kPanelEditorPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kEveChildAlignWidgetID, kPanelEditorPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kEveMarginLabelWidgetID, kPanelEditorPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kEveMarginWidgetID, kPanelEditorPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kEveDescStringWidgetID, kPanelEditorPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kEveChildSpaceLabelWidgetID, kPanelEditorPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kEveChildSpaceWidgetID, kPanelEditorPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kVisTextWidgetId, kPanelEditorPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kVisibleWidgetID, kPanelEditorPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kBindingLabelWidgetID, kPanelEditorPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kBindingWidgetID, kPanelEditorPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kIControlViewTextWidgetID, kPanelEditorPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kIControlViewWidgetID, kPanelEditorPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kMenuAcceleratorsDialogPanelWidgetID, kPanelEditorPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kAcceleratorMenusTreeWidgetID, kPanelEditorPrefix + 95) 
DECLARE_PMID(kWidgetIDSpace, kAssignAcceleratorsButtonWidgetID, kPanelEditorPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kMenuAcceleratorNodeRsrcID, kPanelEditorPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kMenuAcceleratorNodeWidgetID, kPanelEditorPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeAcceleratorWidgetID, kPanelEditorPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kOrigColumnOuterPanelWidgetID, kPanelEditorPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kLockColumnOuterPanelWidgetID, kPanelEditorPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kAccelColumnOuterPanelWidgetID, kPanelEditorPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kLockOuterPanelWidgetID, kPanelEditorPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeOriginalWidgetID, kPanelEditorPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kMenuNameColumnOuterPanelWidgetID, kPanelEditorPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kMenuAcceleratorLockWidgetID, kPanelEditorPrefix + 106)

// <Action ID>
// ----- Action IDs -----

DECLARE_PMID(kActionIDSpace, kPanelEditorActionID, kPanelEditorPrefix + 1)
DECLARE_PMID(kActionIDSpace, kToggleEditModeActionID, kPanelEditorPrefix +2)
DECLARE_PMID(kActionIDSpace, kSaveWidgetDescActionID, kPanelEditorPrefix +3)
DECLARE_PMID(kActionIDSpace, kPEAlignLeftActionID, kPanelEditorPrefix +4)
DECLARE_PMID(kActionIDSpace, kPEAlignRightActionID, kPanelEditorPrefix +5)
DECLARE_PMID(kActionIDSpace, kPEAlignTopActionID, kPanelEditorPrefix +6)
DECLARE_PMID(kActionIDSpace, kPEAlignBottomActionID, kPanelEditorPrefix +7)
DECLARE_PMID(kActionIDSpace, kPECenterHorzActionID, kPanelEditorPrefix +8)
DECLARE_PMID(kActionIDSpace, kPECenterVertActionID, kPanelEditorPrefix +9)
DECLARE_PMID(kActionIDSpace, kPENormalizeActionID, kPanelEditorPrefix +10)
DECLARE_PMID(kActionIDSpace, kDevSep1ActionID, kPanelEditorPrefix +11)
DECLARE_PMID(kActionIDSpace, kDevSep2ActionID, kPanelEditorPrefix +12)
DECLARE_PMID(kActionIDSpace, kDevSep3ActionID, kPanelEditorPrefix +13)
DECLARE_PMID(kActionIDSpace, kPECopyWidgetIDActionID, kPanelEditorPrefix +14)
DECLARE_PMID(kActionIDSpace, kPECopyWidgetFrameActionID, kPanelEditorPrefix +15)
DECLARE_PMID(kActionIDSpace, kPECopyWidgetKeyStringActionID, kPanelEditorPrefix +16)
DECLARE_PMID(kActionIDSpace, kApplyEveLayoutActionID, kPanelEditorPrefix +17)
DECLARE_PMID(kActionIDSpace, kMenuAcceleratorsActionID, kPanelEditorPrefix +18)
DECLARE_PMID(kActionIDSpace, kQuitMenuAcceleratorsActionID, kPanelEditorPrefix +19)

END_IDS()
#endif	// __PanelEditorID__
