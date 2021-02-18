//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ColorMgmtUIID.h $
//  
//  Owner:
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

#ifndef __ColorMgmtUIID__
#define __ColorMgmtUIID__

#if PRAGMA_ONCE
#pragma once
#endif

#define PERFORMANCE_TESTING 0

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kColorMgmtUIPrefix	 RezLong(0x7e00)		//Refer also to "AdobePrefix.h"

// <Start IDC>
// PluginID
#define kColorMgmtUIPluginName 					"Color Management UI"
DECLARE_PMID(kPlugInIDSpace, kColorMgmtUIPluginID, kColorMgmtUIPrefix + 1)

// <Class ID>
// ClassIDs (i.e. bosses)
// gap - was DECLARE_PMID(kClassIDSpace, kCMSDocSolidRIDialogBoss, kColorMgmtUIPrefix + 1)
// gap - was DECLARE_PMID(kClassIDSpace, kCMSDocSolidRIMenuActionBoss, kColorMgmtUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCMSObjectMenuActionBoss, kColorMgmtUIPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kCMSObjectDialogBoss, kColorMgmtUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCMSObjectOnOffWidgetBoss, kColorMgmtUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCMSImageImportDialogBoss, kColorMgmtUIPrefix + 7)
// gap - was kCMSAppPrefsDialogBoss kColorMgmtUIPrefix + 8
// gap - was kCMSAppPrefsMenuActionBoss kColorMgmtUIPrefix + 9
// gap - kColorMgmtUIPrefix + 10
DECLARE_PMID(kClassIDSpace, kCMSAppPrefsObserverBoss, kColorMgmtUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kCMSMissingProfilesDialogBoss, kColorMgmtUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCMSUIOpenDocResponderBoss, kColorMgmtUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCMSUICMSStartupResponderBoss, kColorMgmtUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCMSUIMissingProfilesDlgCmdBoss, kColorMgmtUIPrefix + 15)
//gap
DECLARE_PMID(kClassIDSpace, kAssignedProfileMismatchDialogBoss, kColorMgmtUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kAssignProfilesDialogBoss, kColorMgmtUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kColorSettingsDialogBoss, kColorMgmtUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCommonColorMgmtUIMenuACBoss, kColorMgmtUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kConvertProfileWarningDialogBoss, kColorMgmtUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kConvertToProfileDialogBoss, kColorMgmtUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kDiscardProfileWarningDialogBoss, kColorMgmtUIPrefix + 27)
// gap
DECLARE_PMID(kClassIDSpace, kOpenDocResponderBoss_Obsolete, kColorMgmtUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kProofSetupDialogBoss, kColorMgmtUIPrefix + 32)
// gap
DECLARE_PMID(kClassIDSpace, kColorMgmtUITestMenuBoss, kColorMgmtUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kPasteMismatchDialogBoss, kColorMgmtUIPrefix + 37)
// gap
DECLARE_PMID(kClassIDSpace, kBlackConversionPrefsPanelBoss, kColorMgmtUIPrefix + 39)
// gap
DECLARE_PMID(kClassIDSpace, kProfilePolicyConflictDialogBoss, kColorMgmtUIPrefix + 41)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGPROFILESDLGCMDDATA, kColorMgmtUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORSETTINGSDIALOGDATA, kColorMgmtUIPrefix + 2)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPASTEMISMATCHDIALOGDATA, kColorMgmtUIPrefix + 4)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSUIPRIVUTILS, kColorMgmtUIPrefix + 6)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPROFILEPOLICYCONFLICTDIALOGDATA, kColorMgmtUIPrefix + 8)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kCMSDocSolidRIControllerImpl, kColorMgmtUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCMSDocSolidRIMenuActionImpl, kColorMgmtUIPrefix + 3)
// gap - kColorMgmtUIPrefix + 4
//gap
DECLARE_PMID(kImplementationIDSpace, kCMSObjectMenuActionImpl, kColorMgmtUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCMSObjectDialogControllerImpl, kColorMgmtUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCMSObjectOnOffAbstractObserverImpl, kColorMgmtUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCMSImageImportDialogControllerImpl, kColorMgmtUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCMSImageImportPanelCreatorImpl, kColorMgmtUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCMSObjectOnOffDialogObserverImpl, kColorMgmtUIPrefix + 11)
// gap - was kCMSAppPrefsMenuActionImpl kColorMgmtUIPrefix + 13
// gap - kColorMgmtUIPrefix + 14
DECLARE_PMID(kImplementationIDSpace, kCMSUIOpenDocResponderImpl, kColorMgmtUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kMissingProfilesControllerImpl, kColorMgmtUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCMSUICMSStartupResponderImpl, kColorMgmtUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kMissingProfilesDialogCmdImpl, kColorMgmtUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kMissingProfilesDlgCmdDataImpl, kColorMgmtUIPrefix + 19)

// gap - kColorMgmtUIPrefix + 21
// gap
DECLARE_PMID(kImplementationIDSpace, kAssignProfilesDCImpl, kColorMgmtUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kAssignProfilesDOImpl, kColorMgmtUIPrefix + 25)
// gap - kColorMgmtUIPrefix + 26
// gap
DECLARE_PMID(kImplementationIDSpace, kColorSettingsDCImpl, kColorMgmtUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kColorSettingsDOImpl, kColorMgmtUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kColorSettingsDTImpl, kColorMgmtUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCommonColorMgmtUIMenuACImpl, kColorMgmtUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kConvertProfileWarningDCImpl, kColorMgmtUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kConvertToProfileDCImpl, kColorMgmtUIPrefix + 33)
// gap
// gap
DECLARE_PMID(kImplementationIDSpace, kDiscardProfileWarningDCImpl, kColorMgmtUIPrefix + 36)
// gap
// gap
// gap
// gap
DECLARE_PMID(kImplementationIDSpace, kOpenDocResponderImpl_Obsolete, kColorMgmtUIPrefix + 41)
// gap
DECLARE_PMID(kImplementationIDSpace, kProofSetupDCImpl, kColorMgmtUIPrefix + 43)
// gap
DECLARE_PMID(kImplementationIDSpace, kColorMgmtUITestMenuImpl, kColorMgmtUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kColorSettingsDialogDataImpl, kColorMgmtUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kProofSetupDOImpl, kColorMgmtUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kConvertToProfileDOImpl, kColorMgmtUIPrefix + 48)
// gap
DECLARE_PMID(kImplementationIDSpace, kPasteMismatchDCImpl, kColorMgmtUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPasteMismatchDialogDataImpl, kColorMgmtUIPrefix + 51)
// gap
// gap
DECLARE_PMID(kImplementationIDSpace, kBlackConversionPrefsPanelCreatorImpl, kColorMgmtUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kBlackConversionPrefsDCImpl, kColorMgmtUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kBlackConversionPrefsDOImpl, kColorMgmtUIPrefix + 56)
// gap
// gap
DECLARE_PMID(kImplementationIDSpace, kCMSUIPrivUtilsImpl, kColorMgmtUIPrefix + 59)

DECLARE_PMID(kImplementationIDSpace, kBlackConversionPanelEWImpl, kColorMgmtUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kProofSetupEWImpl, kColorMgmtUIPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kProfilePolicyConflictDCImpl, kColorMgmtUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kProfilePolicyConflictDOImpl, kColorMgmtUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kProfilePolicyConflictDialogDataImpl, kColorMgmtUIPrefix + 64)


// <Service ID>
//	Service IDs

// <Widget ID>
// Dialog Panel IDs
DECLARE_PMID(kWidgetIDSpace, kCMSDocSolidRIDialogWidgetID, kColorMgmtUIPrefix + 1)
// gap - was kCMSAppPrefsDialogWidgetID kColorMgmtUIPrefix + 2
DECLARE_PMID(kWidgetIDSpace, kCMSObjectDialogWidgetID, kColorMgmtUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kCMSImageImportDialogWidgetID, kColorMgmtUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesParentWidgetID, kColorMgmtUIPrefix + 5)

// Widget IDs for Application Settings dialog
DECLARE_PMID(kWidgetIDSpace, kProfilePolicyConflictDialogWID, kColorMgmtUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kProfilePolicyConflictNoConvertDialogWID, kColorMgmtUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kProPolWarningDescWID, kColorMgmtUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLeaveDocRadioButtonWidgetID, kColorMgmtUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPolicyLabelWidgetID, kColorMgmtUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kDocPolicyTextWidgetID, kColorMgmtUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kAppPolicyTextWidgetID, kColorMgmtUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kAdjustDocRadioButtonWidgetID, kColorMgmtUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kAssignProfileLabelWidgetID, kColorMgmtUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kAssignProfilePopupWidgetID, kColorMgmtUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPlacedContentLabelWidgetID, kColorMgmtUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPlacedContentPopupWidgetID, kColorMgmtUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kConvertDocToWorkingWidgetID, kColorMgmtUIPrefix + 32)
//DECLARE_PMID(kWidgetIDSpace, kConversionOptionsGroupPanelWidgetID, kColorMgmtUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kColorSettingsDescriptionGroupPanelWidgetID, kColorMgmtUIPrefix + 34)

// gap - kColorMgmtUIPrefix + 35

// Widget IDs for CMS Document Settings dialog
// gap - kColorMgmtUIPrefix + 40
// gap - kColorMgmtUIPrefix + 41
// gap - kColorMgmtUIPrefix + 42
// gap - kColorMgmtUIPrefix + 43
// gap - kColorMgmtUIPrefix + 44
// gap - kColorMgmtUIPrefix + 45
// gap - kColorMgmtUIPrefix + 46
// gap - kColorMgmtUIPrefix + 47
DECLARE_PMID(kWidgetIDSpace, kCMSPrefsDialogParentWidgetID, kColorMgmtUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kColorSourceParentWidgetID, kColorMgmtUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kIntentGroupWidgetID, kColorMgmtUIPrefix + 50)
// gap - kColorMgmtUIPrefix + 51
DECLARE_PMID(kWidgetIDSpace, kDocSolidIntentTextWidgetID, kColorMgmtUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kDocSolidIntentDropDownWidgetID, kColorMgmtUIPrefix + 53)
// gap - kColorMgmtUIPrefix + 54
// gap - kColorMgmtUIPrefix + 55

// Widget IDs for the CMS object dialog (and image import)
DECLARE_PMID(kWidgetIDSpace, kObjectCMSOnCheckboxWidgetID, kColorMgmtUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kIntentTextWidgetID, kColorMgmtUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kIntentDropDownWidgetID, kColorMgmtUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kProfileTextWidgetID, kColorMgmtUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kProfileDropDownWidgetID, kColorMgmtUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kCMSOffWarningWidgetID, kColorMgmtUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kCMSOffWarningPart1WidgetID, kColorMgmtUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kCMSOffWarningPart2WidgetID, kColorMgmtUIPrefix + 67)

// Widget IDs for the Missing Profiles dialog
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesListWidgetID, kColorMgmtUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kMissingListScrollBarWidgetID, kColorMgmtUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesWarningSignWidgetID, kColorMgmtUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesText1WidgetID, kColorMgmtUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesText2WidgetID, kColorMgmtUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kColorSettingsDialogWidgetID, kColorMgmtUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kMainGroupWidgetID, kColorMgmtUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kSettingsPanelWidgetID, kColorMgmtUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kSettingsLabelWidgetID, kColorMgmtUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kSettingsPopupWidgetID, kColorMgmtUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kAdvancedModeCheckBoxWidgetID, kColorMgmtUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kWorkingSpacesGroupWidgetID, kColorMgmtUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kWorkingSpacesLabelWidgetID, kColorMgmtUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kWSRGBLabelWidgetID, kColorMgmtUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kWSRGBPopupWidgetID, kColorMgmtUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kWSCMYKLabelWidgetID, kColorMgmtUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kWSCMYKPopupWidgetID, kColorMgmtUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kPoliciesGroupWidgetID, kColorMgmtUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kPoliciesLabelWidgetID, kColorMgmtUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPoliciesRGBLabelWidgetID, kColorMgmtUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kPoliciesRGBPopupWidgetID, kColorMgmtUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kPoliciesCMYKLabelWidgetID, kColorMgmtUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kPoliciesCMYKPopupWidgetID, kColorMgmtUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kProfileMismatchesLabelWidgetID, kColorMgmtUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kMismatchAskWhenOpeningCheckBoxWidgetID, kColorMgmtUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kAskWhenPastingCheckBoxWidgetID, kColorMgmtUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kMissingAskWhenOpeningCheckBoxWidgetID, kColorMgmtUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kMissingProfilesLabelWidgetID, kColorMgmtUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kConversionOptionsGroupWidgetID, kColorMgmtUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kConversionOptionsLabelWidgetID, kColorMgmtUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kEngineLabelWidgetID, kColorMgmtUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kEnginePopupWidgetID, kColorMgmtUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kIntentLabelWidgetID, kColorMgmtUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kIntentPopupWidgetID, kColorMgmtUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kUseBPCCheckBoxWidgetID, kColorMgmtUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kDescriptionLabelWidgetID, kColorMgmtUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kDescriptionPanelWidgetID, kColorMgmtUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kDescriptionTextWidgetID, kColorMgmtUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kLoadButtonWidgetID, kColorMgmtUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kSaveButtonWidgetID, kColorMgmtUIPrefix + 111)

DECLARE_PMID(kWidgetIDSpace, kDeviceProfilesDialogWidgetID, kColorMgmtUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kSystemProfilesGroupWidgetID, kColorMgmtUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kSystemProfilesLabelWidgetID, kColorMgmtUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kMonitorLabelWidgetID, kColorMgmtUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kMonitorPopupWidgetID, kColorMgmtUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kCompositeLabelWidgetID, kColorMgmtUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kCompositePopupWidgetID, kColorMgmtUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kSeparationsLabelWidgetID, kColorMgmtUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kSeparationsPopupWidgetID, kColorMgmtUIPrefix + 120)

DECLARE_PMID(kWidgetIDSpace, kMissingProfileDialogWidgetID, kColorMgmtUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kWarningIconWidgetID, kColorMgmtUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kWarningTextWidgetID, kColorMgmtUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kHowGroupWidgetID, kColorMgmtUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kHowLabelWidgetID, kColorMgmtUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kHowClusterPanelWidgetID, kColorMgmtUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kLeaveAsIsRadioButtonWidgetID, kColorMgmtUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kAssignCurRadioButtonWidgetID, kColorMgmtUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kAssignProRadioButtonWidgetID, kColorMgmtUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kAssignProPopupWidgetID, kColorMgmtUIPrefix + 130)

DECLARE_PMID(kWidgetIDSpace, kEmbeddedProfileMismatchDialogWidgetID, kColorMgmtUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kEmbeddedLabelWidgetID, kColorMgmtUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kEmbeddedWidgetID, kColorMgmtUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kWorkingLabelWidgetID, kColorMgmtUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kWorkingWidgetID, kColorMgmtUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kUseRadioButtonWidgetID, kColorMgmtUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kConvertRadioButtonWidgetID, kColorMgmtUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kDiscardRadioButtonWidgetID, kColorMgmtUIPrefix + 138)

DECLARE_PMID(kWidgetIDSpace, kAssignedProfileMismatchDialogWidgetID, kColorMgmtUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kAssignedLabelWidgetID, kColorMgmtUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kAssignedWidgetID, kColorMgmtUIPrefix + 141)

DECLARE_PMID(kWidgetIDSpace, kDiscardProfileWarningDialogWidgetID, kColorMgmtUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainCheckBoxWidgetID, kColorMgmtUIPrefix + 143)
// gap
DECLARE_PMID(kWidgetIDSpace, kConvertProfileWarningDialogWidgetID, kColorMgmtUIPrefix + 145)

DECLARE_PMID(kWidgetIDSpace, kConvertToProfileDialogWidgetID, kColorMgmtUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kSourceSpaceGroupWidgetID, kColorMgmtUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kSourceSpaceLabelWidgetID, kColorMgmtUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kRGBSourceLabelWidgetID, kColorMgmtUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kRGBSourceTextWidgetID, kColorMgmtUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kCMYKSourceLabelWidgetID, kColorMgmtUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kCMYKSourceTextWidgetID, kColorMgmtUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kDestinationSpaceGroupWidgetID, kColorMgmtUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kDestinationSpaceLabelWidgetID, kColorMgmtUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kRGBDestinationLabelWidgetID, kColorMgmtUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kRGBDestinationPopupWidgetID, kColorMgmtUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kCMYKDestinationLabelWidgetID, kColorMgmtUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kCMYKDestinationPopupWidgetID, kColorMgmtUIPrefix + 158)

DECLARE_PMID(kWidgetIDSpace, kAssignProfilesDialogWidgetID, kColorMgmtUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kRGBGroupWidgetID, kColorMgmtUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kRGBGroupLabelWidgetID, kColorMgmtUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kRGBClusterPanelWidgetID, kColorMgmtUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kRGBDiscardCheckBoxWidgetID, kColorMgmtUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kRGBAssignCurrentRadioButtonWidgetID, kColorMgmtUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kRGBAssignProfileCheckBoxWidgetID, kColorMgmtUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kRGBProfilePopupWidgetID, kColorMgmtUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kCMYKGroupWidgetID, kColorMgmtUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kCMYKGroupLabelWidgetID, kColorMgmtUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kCMYKClusterPanelWidgetID, kColorMgmtUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kCMYKDiscardCheckBoxWidgetID, kColorMgmtUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kCMYKAssignCurrentRadioButtonWidgetID, kColorMgmtUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kCMYKAssignProfileCheckBoxWidgetID, kColorMgmtUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kCMYKProfilePopupWidgetID, kColorMgmtUIPrefix + 173)

DECLARE_PMID(kWidgetIDSpace, kProofSetupDialogWidgetID, kColorMgmtUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kSetupGroupWidgetID, kColorMgmtUIPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kSetupGroupLabelWidgetID, kColorMgmtUIPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kProfileLabelWidgetID, kColorMgmtUIPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kProfilePopupWidgetID, kColorMgmtUIPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kSimulateLabelWidgetID, kColorMgmtUIPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kPaperWhiteCheckboxWidgetID, kColorMgmtUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kInkBlackCheckboxWidgetID, kColorMgmtUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kVectorRILabelWidgetID, kColorMgmtUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kVectorRIPopupWidgetID, kColorMgmtUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kRasterRILabelWidgetID, kColorMgmtUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kRasterRIPopupWidgetID, kColorMgmtUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kPostBlendRILabelWidgetID, kColorMgmtUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kPostBlendRIPopupWidgetID, kColorMgmtUIPrefix + 187)

DECLARE_PMID(kWidgetIDSpace, kRGBAssignCurrentStaticTextWidgetID, kColorMgmtUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kCMYKAssignCurrentStaticTextWidgetID, kColorMgmtUIPrefix + 189)
// gap - was kEnableCMSCheckboxWidgetId, kColorMgmtUIPrefix + 190
DECLARE_PMID(kWidgetIDSpace, kAssignCurStaticTextWidgetID, kColorMgmtUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kCSFSyncIconWID, kColorMgmtUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kCSFSyncStatusWID, kColorMgmtUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kCSFSafeCMYKIndicatorWID, kColorMgmtUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kCSFSafeCMYKDescIndicatorWID, kColorMgmtUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kPreserveNumbersCheckboxWidgetID, kColorMgmtUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kCSFUnSyncIconWID, kColorMgmtUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kCSFSingleAppIconWID, kColorMgmtUIPrefix + 198)

// gap: Former policy conflict dialog

DECLARE_PMID(kWidgetIDSpace, kBlackConversionPrefsPanelWID, kColorMgmtUIPrefix + 210)
//DECLARE_PMID(kWidgetIDSpace, kBlkConIdealizedDisplayCheckboxWID, kColorMgmtUIPrefix + 211)
//DECLARE_PMID(kWidgetIDSpace, kBlkConIdealizedExportCheckboxWID, kColorMgmtUIPrefix + 212)

// gap: formerly spot to process open-time dialog

DECLARE_PMID(kWidgetIDSpace, kBlkHandleGroupPanelWidgetID, kColorMgmtUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kBlkHandleLabelWidgetID, kColorMgmtUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kBlkOnScreenLabelWidgetID, kColorMgmtUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kBlkOnScreenPopupWidgetID, kColorMgmtUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kBlkPrintExportLabelWidgetID, kColorMgmtUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kBlkPrintExportPopupWidgetID, kColorMgmtUIPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kBlkExample100KGroupPanelWidgetID, kColorMgmtUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kBlkExample100KLabelWidgetID, kColorMgmtUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kBlkExampleRichGroupPanelWidgetID, kColorMgmtUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kBlkExampleRichLabelWidgetID, kColorMgmtUIPrefix + 239)

DECLARE_PMID(kWidgetIDSpace, kBlkOverprintGroupPanelWidgetID, kColorMgmtUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kBlkOverprintLabelWidgetID, kColorMgmtUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kBlkOverprintBlackCheckboxWidgetID, kColorMgmtUIPrefix + 242)

DECLARE_PMID(kWidgetIDSpace, kBlkUIDescPanelWID, kColorMgmtUIPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kBlkUIDescPanelTitleWID, kColorMgmtUIPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kBlkUIDescLabelWID, kColorMgmtUIPrefix + 245)

DECLARE_PMID(kWidgetIDSpace, kBlk100KBlkIconWidgetID, kColorMgmtUIPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kBlkRichBlkIconWidgetID, kColorMgmtUIPrefix + 247)

DECLARE_PMID(kWidgetIDSpace, kProofDescPanelWID, kColorMgmtUIPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kProofDescPanelTitleWID, kColorMgmtUIPrefix + 249)
DECLARE_PMID(kWidgetIDSpace, kProofIconWidgetID, kColorMgmtUIPrefix + 250)
DECLARE_PMID(kWidgetIDSpace, kProofDescSmallWidgetID, kColorMgmtUIPrefix + 251)
DECLARE_PMID(kWidgetIDSpace, kProofDescLargeWidgetID, kColorMgmtUIPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kProofPreserveWarnIconWidgetID, kColorMgmtUIPrefix + 253)

// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kCantReadColorSettingFromOtherPlateform, kColorMgmtUIPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kColorSettingFormatWrongOrCorrupt, kColorMgmtUIPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kColorSettingFormatTooRecent, kColorMgmtUIPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kColorSettingStillExists, kColorMgmtUIPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kColorSettingCantWriteDisk, kColorMgmtUIPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kColorSettingFolderIsFile, kColorMgmtUIPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kColorSettingCantCreateFolder, kColorMgmtUIPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kColorSettingEmptyName, kColorMgmtUIPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kColorSettingExistName, kColorMgmtUIPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kColorSettingToLongName, kColorMgmtUIPrefix + 10	)
DECLARE_PMID(kErrorIDSpace, kColorSettingBadSyntaxName, kColorMgmtUIPrefix + 11)

// <Action ID>
// gap - was kCMSAppPrefsActionID kColorMgmtUIPrefix + 1
DECLARE_PMID(kActionIDSpace, kCMSDocSolidRIActionID, kColorMgmtUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kCMSObjectSettingsActionID, kColorMgmtUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCMSSepActionID, kColorMgmtUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kImageCMSSepActionID, kColorMgmtUIPrefix + 5)

DECLARE_PMID(kActionIDSpace, kColorSettingsActionID, kColorMgmtUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kSeparator1ActionID, kColorMgmtUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kConvertToProfileActionID, kColorMgmtUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kAssignProfilesActionID, kColorMgmtUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kSeparator2ActionID, kColorMgmtUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kProofColorsActionID, kColorMgmtUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kCustomActionID, kColorMgmtUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kSeparator3ActionID, kColorMgmtUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kSimulateDocCMYKActionID, kColorMgmtUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kSimulateWorkingCMYKActionID, kColorMgmtUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kSeparator4ActionID, kColorMgmtUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kSimulateMacintoshRGBActionID, kColorMgmtUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kSimulateWindowsRGBActionID, kColorMgmtUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kSimulateMonitorRGBActionID, kColorMgmtUIPrefix + 20)
#if PERFORMANCE_TESTING
DECLARE_PMID(kActionIDSpace, kCMSPerformance1MAID, kColorMgmtUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kCMSPerformance2MAID, kColorMgmtUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kCMSPerformance3MAID, kColorMgmtUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kCMSPerformance4MAID, kColorMgmtUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kCMSPerformance5MAID, kColorMgmtUIPrefix + 25)
#endif
DECLARE_PMID(kActionIDSpace, kBatchColorSettingsMAID, kColorMgmtUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kBlackConversionPrefsMAID, kColorMgmtUIPrefix + 27)

#endif // __ColorMgmtUIID__

// End, ColorMgmtUIID.h.
