//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/ui/includes/AATArchUIDlgDefines.h $
//  
//  Owner: Gregor Kaplan
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

#pragma once

#define kDlgLeftDim			0
#define kDlgRightDim		575
#define	kDlgTopDim			0
#define	kDlgBotDim			400

#define	kDlgMargin			10
#define kDlgTitleTopOffset	-7
#define kDlgTitleBotOffset	9

#define kStdWidgetHeight	20
#define kStdButWidth		80
#define kStdCheckWidth		90
#define kStdCheckHeight		15

//Bottom Controls
#define kResizeWidgetRight		kDlgRightDim
#define kResizeWidgetLeft		kResizeWidgetRight - 16
#define kResizeWidgetBottom		kDlgBotDim
#define kResizeWidgetTop		kResizeWidgetBottom - 16

#define kSaveButRight			kResizeWidgetLeft - kDlgMargin
#define kSaveButLeft			kSaveButRight - kStdButWidth
#define kSaveButTop				kDlgBotDim - kDlgMargin - kStdWidgetHeight
#define kSaveButBot				kSaveButTop + kStdWidgetHeight

#define kSaveAsButRight			kSaveButLeft - kDlgMargin
#define kSaveAsButLeft			kSaveAsButRight - kStdButWidth - 2
#define kSaveAsButTop			kSaveButTop
#define kSaveAsButBot			kSaveButBot

#define kExecuteButRight		kSaveAsButLeft - kDlgMargin
#define kExecuteButLeft			kExecuteButRight - kStdButWidth - 2
#define kExecuteButTop			kSaveButTop
#define kExecuteButBot			kSaveButBot

#define kCloseButRight			kExecuteButLeft - kDlgMargin
#define kCloseButLeft			kCloseButRight - kStdButWidth
#define kCloseButTop			kSaveButTop
#define kCloseButBot			kSaveButBot


//Main UI
#define kAATGroupTop			kStdWidgetHeight
#define	kAATGroupBottom		kSaveButTop - kDlgMargin
#define	kAATGroupRight		kDlgRightDim - kDlgMargin
#define	kAATGroupLeft			kDlgMargin

#define kAATActionListBoxGroupTop			20
#define	kAATActionListBoxGroupBottom		265
#define	kAATActionListBoxGroupLeft			kDlgMargin
#define	kAATActionListBoxGroupRight			265

#define kAATSourceDropDownTop		kDlgMargin + 5
#define kAATSourceDropDownBottom	kAATSourceDropDownTop + kStdWidgetHeight
#define kAATSourceDropDownLeft	5
#define kAATSourceDropDownRight	kAATActionListBoxGroupRight - kAATActionListBoxGroupLeft - 7

#define kAATActionListBoxTop		kAATSourceDropDownBottom + kDlgMargin
#define kAATActionListBoxBottom		kAATActionListBoxGroupBottom - kAATActionListBoxGroupTop - 2
#define kAATActionListBoxLeft		1
#define kAATActionListBoxRight		kAATActionListBoxGroupRight - kAATActionListBoxGroupLeft - 2

// end dim defs

// index defines for the model tree
// the index refers to a node's indices[index] acquired from GetNodeIndex.
// for instance, a node's indices[0] value would be the index of its highest level parent
#define kAATModelObjectTypeIndex	0
#define kSequenceTypeIndex				1
#define kAATActionListTypeIndex			1
#define kActiveAATTypeIndex		2

#define kUIExtensionDialogIndex				1
#define kUIExtensionHighestGroupIndex		2


// index defines for the sequencer tree
// see above for description of what index means
#define kSessionLevelIndex				0
#define kHighestSequenceLevelIndex		1

#define kNumRows			8
#define kNumCols			2

#define kEditorWidgetWidth 		250

#define kEditDlgLeftDim			0
#define kEditDlgRightDim		(kNumCols * kEditorWidgetWidth) + ((kNumCols + 3) * kDlgMargin)
#define	kEditDlgTopDim			0
#define	kEditDlgBotDim			((kNumRows + 1)  * kStdWidgetHeight) + ((kNumRows + 4) * kDlgMargin)

#define kMaxRight kEditDlgRightDim - (3 * kDlgMargin)

#define kEditOKButRight			kEditDlgRightDim - kDlgMargin
#define kEditOKButLeft			kEditOKButRight - kStdButWidth
#define kEditOKButTop			kEditDlgBotDim - kDlgMargin - kStdWidgetHeight
#define kEditOKButBot			kEditOKButTop + kStdWidgetHeight

#define kEditCancelButRight		kEditOKButLeft - kDlgMargin
#define kEditCancelButLeft		kEditCancelButRight - kStdButWidth
#define kEditCancelButTop		kEditOKButTop
#define kEditCancelButBot		kEditOKButBot

#define kEditDataPanelGroupLeft		kDlgMargin
#define kEditDataPanelGroupTop		kDlgMargin
#define kEditDataPanelGroupRight	kEditDlgRightDim - kDlgMargin
#define kEditDataPanelGroupBottom	kEditOKButTop - kDlgMargin

#define kEditAATGroupLeft		kDlgMargin
#define kEditAATGroupTop		kDlgMargin
#define kEditAATGroupRight	kDlgMargin + kEditorWidgetWidth
#define kEditAATGroupBottom	kEditDataPanelGroupBottom - (2 * kDlgMargin)

#define kDataGroupLeft		kEditAATGroupRight + kDlgMargin
#define kDataGroupTop		kDlgMargin
#define kDataGroupRight		kEditDataPanelGroupRight - (2 * kDlgMargin)
#define kDataGroupBottom	kEditAATGroupBottom

//Editor Data Panel
#define kDataStringsLeft	kDlgMargin
#define kDataStringsRight	90
#define kDataEntryRight		kEditAATGroupRight - (2 * kDlgMargin)

#define kValueStringTop		(2 * kDlgMargin)
#define kValueStringBottom	kValueStringTop + kStdWidgetHeight
#define kValueTreeBottom	kValueStringTop + (kStdWidgetHeight * 7)

#define kVarStringTop		(kDataGroupBottom - kDataGroupTop) - (2 * (kDlgMargin + kStdWidgetHeight))
#define kVarStringBottom	kVarStringTop + kStdWidgetHeight

#define kIterStringTop		kVarStringBottom + kDlgMargin
#define kIterStringBottom	kIterStringTop + kStdWidgetHeight

#define kFileEntryLeft		kDlgMargin
#define	kFileEntryRight		kDataEntryRight
#define kFileEntryTop		kValueStringTop
#define kFileEntryBottom	kFileEntryTop + kStdWidgetHeight

#define kBrowseRight		kFileEntryRight
#define kBrowseLeft			kBrowseRight - kStdButWidth		
#define kBrowseTop			kFileEntryBottom + kDlgMargin
#define kBrowseBottom		kBrowseTop + kStdWidgetHeight

#define kRelStrLeft			kDataStringsLeft
#define kRelStrRight		kDataStringsRight + 15
#define kRelStrTop			kBrowseBottom + kDlgMargin
#define kRelStrBottom		kRelStrTop + kStdWidgetHeight

#define kRelDDLeft			kRelStrRight + kDlgMargin
#define kRelDDRight			kBrowseRight
#define kRelDDTop			kRelStrTop
#define kRelDDBottom		kRelStrBottom

/*// rename/group name dialog
#define kNameDlgLeftDim			0
#define kNameDlgRightDim		250
#define	kNameDlgTopDim			0
#define	kNameDlgBotDim			80

#define kNameEBRowTop			kDlgMargin
#define kNameEBRowBottom		kNameEBRowTop + kStdWidgetHeight

#define kNameStringLeft			kDlgMargin
#define kNameStringRight		45

#define kNameEBLeft				kNameStringRight + kDlgMargin
#define kNameEBRight			kNameDlgRightDim - kDlgMargin

#define kNameButtonRowBottom	kNameDlgBotDim - kDlgMargin
#define kNameButtonRowTop		kNameButtonRowBottom - kStdWidgetHeight

#define kNameOKButtonRight		kNameDlgRightDim - kDlgMargin
#define kNameOKButtonLeft		kNameOKButtonRight - kStdButWidth

#define kNameCancelButRight		kNameOKButtonLeft - kDlgMargin
#define kNameCancelButLeft		kNameCancelButRight - kStdButWidth*/

