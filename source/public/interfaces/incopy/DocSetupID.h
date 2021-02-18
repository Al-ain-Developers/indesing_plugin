//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/DocSetupID.h $
//  
//  Owner: Tommy Donovan
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
//  Contains IDs used by the page size panel plug-in
//  
//========================================================================================

#ifndef __DocSetupID__
#define __DocSetupID__
#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDocSetupPrefix	RezLong(0x18200) 

#define kDoingDocSetup        0
#define kDoingNewDocument     1
#define kDoingDocPreset       2
#define kUsingDocPreset       3

// <Start IDC>
// PluginID
#define kDocSetupPluginName 			"Document Setup"
DECLARE_PMID(kPlugInIDSpace, kDocSetupPluginID, kDocSetupPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace,  kDocSetupDlgBoss,						kDocSetupPrefix + 1)
DECLARE_PMID(kClassIDSpace,  kNewDocSetupDlgBoss,					kDocSetupPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace,  kDocSetupMenuActionBoss,				kDocSetupPrefix + 4)
DECLARE_PMID(kClassIDSpace,  kICDocSetupDialogCmdBoss,				kDocSetupPrefix + 10)
DECLARE_PMID(kClassIDSpace,  kDocPresetEditMenuActionBoss,			kDocSetupPrefix + 11)
DECLARE_PMID(kClassIDSpace,  kGridTextMeasureBoss,					kDocSetupPrefix + 12)
DECLARE_PMID(kClassIDSpace,  kTextAreaWidthWidgetBoss,				kDocSetupPrefix + 13)
DECLARE_PMID(kClassIDSpace,  kTextAreaCharPerLineWidgetBoss,		kDocSetupPrefix + 14)
//gap
DECLARE_PMID(kClassIDSpace,  kTextAreaDepthWidgetBoss,				kDocSetupPrefix + 16)
DECLARE_PMID(kClassIDSpace,  kICPageSizePresetDropdownListWidgetBoss,	kDocSetupPrefix + 17)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace,  IID_IPRIVATEDOCSETUPDLGUTILS,      kDocSetupPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace,	IID_IICPAGESIZELASTCHOICE,			kDocSetupPrefix + 38) 

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace,  kICPageSizePopupControllerImpl,		kDocSetupPrefix + 41)
//gap
DECLARE_PMID(kImplementationIDSpace,  kDocSetupDlgControllerImpl,			kDocSetupPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,  kDocSetupDlgObserverImpl,				kDocSetupPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,  kDocSetupMenuActionImpl,				kDocSetupPrefix + 54)
//gap
DECLARE_PMID(kImplementationIDSpace,  kICDocSetupDialogCmdImpl,				kDocSetupPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,  kDocPresetDynMenuInfoImpl,			kDocSetupPrefix + 64)
DECLARE_PMID(kImplementationIDSpace,  kGridTextMeasurementTypeImpl,			kDocSetupPrefix + 65)
DECLARE_PMID(kImplementationIDSpace,  kPrivateDocSetupDlgUtilsImpl,			kDocSetupPrefix + 66)
DECLARE_PMID(kImplementationIDSpace,  kTextAreaWidthValidationImpl,			kDocSetupPrefix + 67)
DECLARE_PMID(kImplementationIDSpace,  kTextAreaCharPerLineValidationImpl,	kDocSetupPrefix + 68)
DECLARE_PMID(kImplementationIDSpace,  kTextAreaDepthValidationImpl,			kDocSetupPrefix + 69)

//this is replaced by kICPageSizePresetDDLOpenCloseHandlerImpl below
//DECLARE_PMID(kImplementationIDSpace,  kICPageSizePresetDDLEventHandlerImpl,			kDocSetupPrefix + 70)

DECLARE_PMID(kImplementationIDSpace,  kICPageSizeLastChoiceImpl,			kDocSetupPrefix + 71) 
DECLARE_PMID(kImplementationIDSpace,  kICPageSizePresetDDLOpenCloseHandlerImpl,			kDocSetupPrefix + 72)



// <Widget ID>
// Widget IDs
//gap
DECLARE_PMID(kWidgetIDSpace,  kICPageSizePopupWidgetID,					kDocSetupPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeWidthEditWidgetID,				kDocSetupPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,  kICPageSizeWidthNudgeWidgetID,			kDocSetupPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeHeightEditWidgetID,				kDocSetupPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeHeightNudgeWidgetID,				kDocSetupPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeWidthLabelWidgetID,				kDocSetupPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeHeightLabelWidgetID,				kDocSetupPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,  kICPageSizePanelWidgetID,					kDocSetupPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,  kPageGroupWidgetId,						kDocSetupPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,  kDocSetupDlgWidgetId,						kDocSetupPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,  kPageSizeGroupWidgetID,					kDocSetupPrefix + 12)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaGroupWidgetID,					kDocSetupPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaLabelWidgetID,					kDocSetupPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaWidthEditWidgetID,				kDocSetupPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaWidthNudgeWidgetID,				kDocSetupPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaHeightEditWidgetID,				kDocSetupPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaHeightNudgeWidgetID,				kDocSetupPrefix + 18)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaWidthLabelWidgetID,				kDocSetupPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaHeightLabelWidgetID,				kDocSetupPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,  kDocPresetLabelWidgetID,					kDocSetupPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,  kDocPresetPopupWidgetID,					kDocSetupPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaHeightUnitPopupWidgetID,			kDocSetupPrefix + 23)
DECLARE_PMID(kWidgetIDSpace,  kNewDocSetupDlgWidgetId,					kDocSetupPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,  kSavePresetButtonWidgetID,				kDocSetupPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,  kDocPresetNameWidgetID,					kDocSetupPrefix + 26)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaGroupBoarderWidgetID,			kDocSetupPrefix + 27)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaPopupWidgetID,					kDocSetupPrefix + 28)
DECLARE_PMID(kWidgetIDSpace,  kGridDirectionTitleWidgetID,				kDocSetupPrefix + 29)
DECLARE_PMID(kWidgetIDSpace,  kGridDirectionWidgetID,					kDocSetupPrefix + 30)
DECLARE_PMID(kWidgetIDSpace,  kGridSettingGroupPanelWidgetID,			kDocSetupPrefix + 31)
DECLARE_PMID(kWidgetIDSpace,  kGridSettingBoarderWidgetID,				kDocSetupPrefix + 32)
DECLARE_PMID(kWidgetIDSpace,  kGridVScalePanelWidgetID,					kDocSetupPrefix + 33)
DECLARE_PMID(kWidgetIDSpace,  kGridVScaleTitleWidgetID,					kDocSetupPrefix + 34)
DECLARE_PMID(kWidgetIDSpace,  kGridVScaleWidgetID,						kDocSetupPrefix + 35)
DECLARE_PMID(kWidgetIDSpace,  kGridVScaleNudgeWidgetID,					kDocSetupPrefix + 36)
DECLARE_PMID(kWidgetIDSpace,  kGridHScalePanelWidgetID,					kDocSetupPrefix + 37)
DECLARE_PMID(kWidgetIDSpace,  kGridHScaleTitleWidgetID,					kDocSetupPrefix + 38)
DECLARE_PMID(kWidgetIDSpace,  kGridHScaleWidgetID,						kDocSetupPrefix + 39)
DECLARE_PMID(kWidgetIDSpace,  kGridHScaleNudgeWidgetID,					kDocSetupPrefix + 40)
DECLARE_PMID(kWidgetIDSpace,  kGridCharSpacePanelWidgetID,				kDocSetupPrefix + 41)
DECLARE_PMID(kWidgetIDSpace,  kGridCharSpaceTitleWidgetID,				kDocSetupPrefix + 42)
DECLARE_PMID(kWidgetIDSpace,  kGridCharSpaceWidgetID,					kDocSetupPrefix + 43)
DECLARE_PMID(kWidgetIDSpace,  kGridCharSpaceNudgeWidgetID,				kDocSetupPrefix + 44)
DECLARE_PMID(kWidgetIDSpace,  kGridLineSpacePanelWidgetID,				kDocSetupPrefix + 45)
DECLARE_PMID(kWidgetIDSpace,  kGridLineSpaceTitleWidgetID,				kDocSetupPrefix + 46)
DECLARE_PMID(kWidgetIDSpace,  kGridLineSpaceWidgetID,					kDocSetupPrefix + 47)
DECLARE_PMID(kWidgetIDSpace,  kGridLineSpaceNudgeWidgetID,				kDocSetupPrefix + 48)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaCharPerLineEditWidgetID,			kDocSetupPrefix + 49)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaCharPerLineNudgeWidgetID,		kDocSetupPrefix + 50)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaCharPerLineTypeWidgetID,			kDocSetupPrefix + 51)
DECLARE_PMID(kWidgetIDSpace,  kTextAreaCharPerLineLabelWidgetID,		kDocSetupPrefix + 52)
DECLARE_PMID(kWidgetIDSpace,  kDSFacingPagesCheckBoxWidgetID,			kDocSetupPrefix + 53)
DECLARE_PMID(kWidgetIDSpace,  kDSBindingLabelWidgetID,					kDocSetupPrefix + 54)
DECLARE_PMID(kWidgetIDSpace,  kDSDocOrientationHiliteBorderWidgetID,	kDocSetupPrefix + 55)
DECLARE_PMID(kWidgetIDSpace,  kDSTitleClusterWidgetId,					kDocSetupPrefix + 56)
DECLARE_PMID(kWidgetIDSpace,  kDSPageBindingLeftToRightIconWidgetID,	kDocSetupPrefix + 57)
DECLARE_PMID(kWidgetIDSpace,  kDSPageBindingRightToLeftIconWidgetID,	kDocSetupPrefix + 58)

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kDocSetupActionID,					kDocSetupPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDocSetupSepActionID,				kDocSetupPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDocPresetEditActionID,			kDocSetupPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDocPresetSepActionID,				kDocSetupPrefix + 4)
DECLARE_PMID(kActionIDSpace, kDocPresetDynamicActionID,			kDocSetupPrefix + 5)
DECLARE_PMID(kActionIDSpace, kFirstDocPresetActionID,			(kDocSetupPrefix + 6))
// ids between kFirstDocStyleActionID and kLastDocStyleActionID are reserved
DECLARE_PMID(kActionIDSpace, kLastDocPresetActionID,			(kDocSetupPrefix + 221))




#endif // __DocumentSetupDlgID__

