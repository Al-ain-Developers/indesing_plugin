//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ACEColorMgmtID.h $
//  
//  Owner: Matt Phillips
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

#ifndef __ACEColorMgmtID__
#define __ACEColorMgmtID__

#if PRAGMA_ONCE
#pragma once
#endif

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// <Start IDC>
#define kACEColorMgmtPrefix	 RezLong(0x7d00)		//Refer also to AdobePrefix.h

// <Class ID>
// ClassIDs (i.e. bosses)
DECLARE_PMID(kClassIDSpace, kACECMSManagerBoss, kACEColorMgmtPrefix + 1)
DECLARE_PMID(kClassIDSpace, kACEAnnihilatorBoss, kACEColorMgmtPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCMSProfileBoss, kACEColorMgmtPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCMSProfileTagBoss, kACEColorMgmtPrefix + 6)
DECLARE_PMID(kClassIDSpace, kRasterPortSetupServiceBoss, kACEColorMgmtPrefix + 7)
DECLARE_PMID(kClassIDSpace, kACEColorSpaceMgrBoss, kACEColorMgmtPrefix + 8)

DECLARE_PMID(kClassIDSpace, kAssignProfilesCmdBoss, kACEColorMgmtPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCMSSetProofingCmdBoss, kACEColorMgmtPrefix + 10)
DECLARE_PMID(kClassIDSpace, kConvertToProfileCmdBoss, kACEColorMgmtPrefix + 11)
DECLARE_PMID(kClassIDSpace, kConvertToProfilesCmdBoss, kACEColorMgmtPrefix + 12)
DECLARE_PMID(kClassIDSpace, kACEThreadAnnihilatorBoss, kACEColorMgmtPrefix + 13)
// kACEColorMgmtPrefix + 14 - was kCPSSetEngineCmdBoss
// kACEColorMgmtPrefix + 15 - was kCPSSetIntentCmdBoss
// kACEColorMgmtPrefix + 16 - was kCPSSetIsCustomCmdBoss
// kACEColorMgmtPrefix + 17 - was kCPSSetKPCCmdBoss
// kACEColorMgmtPrefix + 18 - was kCPSSetMismatchAskOpeningCmdBoss
// kACEColorMgmtPrefix + 19 - was kCPSSetMismatchAskPastingCmdBoss
// kACEColorMgmtPrefix + 20 - was kCPSSetMissingAskOpeningCmdBoss
// kACEColorMgmtPrefix + 21 - was kCPSSetPolicyCMYKCmdBoss
// kACEColorMgmtPrefix + 22 - was kCPSSetPolicyRGBCmdBoss
// kACEColorMgmtPrefix + 23 - was kCPSSetPresetNameCmdBoss
// kACEColorMgmtPrefix + 24 - was kCPSSetWorkingCMYKCmdBoss
// kACEColorMgmtPrefix + 25 - was kCPSSetWorkingRGBCmdBoss
DECLARE_PMID(kClassIDSpace, kTransformSwatchesCmdBoss, kACEColorMgmtPrefix + 26)
// kACEColorMgmtPrefix + 28 - was kCPSSetPresetPathCmdBoss
// kACEColorMgmtPrefix + 29 - was kCPSSetEmulate1xCMSOffCmdBoss
DECLARE_PMID(kClassIDSpace, kColorPresetsSettingsSetCmdBoss, kACEColorMgmtPrefix + 30)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IACESPECIFICDATA, kACEColorMgmtPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IACESPECIFICPROFILEDATA, kACEColorMgmtPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IACECMSPROFILETAG, kACEColorMgmtPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IACECOLORDATASPEC, kACEColorMgmtPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IACECMDDATA, kACEColorMgmtPrefix + 6)

DECLARE_PMID(kInterfaceIDSpace, IID_ICMSENGINEDATA, kACEColorMgmtPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPOLICYDATA, kACEColorMgmtPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILECODEDATA, kACEColorMgmtPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILEDATA, kACEColorMgmtPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNPROFILESCMDDATA, kACEColorMgmtPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILECATEGORYDATA, kACEColorMgmtPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROOFING, kACEColorMgmtPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSRENDERINGINTENTDATA, kACEColorMgmtPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPRESETSMANAGER, kACEColorMgmtPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPRESETSSETTINGS, kACEColorMgmtPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTTOPROFILESCMDDATA, kACEColorMgmtPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IACEPROFILESIGNATURE, kACEColorMgmtPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMSWATCHESCMDDATA, kACEColorMgmtPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPRESETSSETTINGSDATA, kACEColorMgmtPrefix + 21)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kACECMSManagerImpl, kACEColorMgmtPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kACESpecificDataImpl, kACEColorMgmtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kACECMSManagerServiceImpl, kACEColorMgmtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kACEStartupShutdownImpl, kACEColorMgmtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kACEStartupServiceImpl, kACEColorMgmtPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kACESpecificProfileDataImpl, kACEColorMgmtPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kACECMSProfileImpl, kACEColorMgmtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kACECMSProfileTagImpl, kACEColorMgmtPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kACERasterPortSetupImpl, kACEColorMgmtPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kACERasterPortSetupServiceImpl, kACEColorMgmtPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kACEColorSpaceMgrImpl, kACEColorMgmtPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kACEColorSpaceMgrServiceImpl, kACEColorMgmtPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kACEImageTagServiceImpl, kACEColorMgmtPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kACEColorConverterImpl, kACEColorMgmtPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kACECmdDataImpl, kACEColorMgmtPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kCMSEngineDataImpl, kACEColorMgmtPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCMSPolicyDataImpl, kACEColorMgmtPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileCodeDataImpl, kACEColorMgmtPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileDataImpl, kACEColorMgmtPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kAssignProfilesCmdDataImpl, kACEColorMgmtPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kAssignProfilesCmdImpl, kACEColorMgmtPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileCategoryDataImpl, kACEColorMgmtPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kCMSProofingImpl, kACEColorMgmtPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCMSRenderingIntentDataImpl, kACEColorMgmtPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCMSSetProofingCmdImpl, kACEColorMgmtPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kColorPresetsManagerImpl, kACEColorMgmtPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kColorPresetsSettingsImpl, kACEColorMgmtPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kConvertToProfileCmdImpl, kACEColorMgmtPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kConvertToProfilesCmdDataImpl, kACEColorMgmtPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kConvertToProfilesCmdImpl, kACEColorMgmtPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kACEThreadStartupShutdownImpl, kACEColorMgmtPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kACEThreadStartupServiceImpl, kACEColorMgmtPrefix + 36)
// kACEColorMgmtPrefix + 37 - was kCPSSetIntentCmdImpl
// kACEColorMgmtPrefix + 38 - was kCPSSetIsCustomCmdImpl
// kACEColorMgmtPrefix + 39 - was kCPSSetKPCCmdImpl
// kACEColorMgmtPrefix + 40 - was kCPSSetMismatchAskOpeningCmdImpl
// kACEColorMgmtPrefix + 41 - was kCPSSetMismatchAskPastingCmdImpl
// kACEColorMgmtPrefix + 42 - was kCPSSetMissingAskOpeningCmdImpl
// kACEColorMgmtPrefix + 43 - was kCPSSetPolicyCMYKCmdImpl
// kACEColorMgmtPrefix + 44 - was kCPSSetPolicyRGBCmdImpl
// kACEColorMgmtPrefix + 45 - was kCPSSetPresetNameCmdImpl
// kACEColorMgmtPrefix + 46 - was kCPSSetWorkingCMYKCmdImpl
// kACEColorMgmtPrefix + 47 - was kCPSSetWorkingRGBCmdImpl
DECLARE_PMID(kImplementationIDSpace, kPersistCMSProfileCodeDataImpl, kACEColorMgmtPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kACEProfileSignatureImpl, kACEColorMgmtPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kTransformSwatchesCmdImpl, kACEColorMgmtPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTransformSwatchesCmdDataImpl, kACEColorMgmtPrefix + 51)
// kACEColorMgmtPrefix + 54 - was kCPSSetPresetPathCmdImpl
// kACEColorMgmtPrefix + 55 - was kCPSSetEmulate1xCMSOffCmdImpl
DECLARE_PMID(kImplementationIDSpace, kColorPresetsSettingsSetCmdImpl, kACEColorMgmtPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kColorPresetsSettingsDataImpl, kACEColorMgmtPrefix + 57)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kPasteMismatchDialogWidgetID, kACEColorMgmtPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kMPD_WarningIconWidgetID, kACEColorMgmtPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kMPD_WarningTextWidgetID, kACEColorMgmtPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kMPD_SourceLabelWidgetID, kACEColorMgmtPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kMPD_SourceWidgetID, kACEColorMgmtPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kMPD_DestinationLabelWidgetID, kACEColorMgmtPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kMPD_DestinationWidgetID, kACEColorMgmtPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kMPD_HowGroupWidgetID, kACEColorMgmtPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kMPD_HowLabelWidgetID, kACEColorMgmtPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kMPD_HowClusterPanelWidgetID, kACEColorMgmtPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kMPD_ConvertRadioButtonWidgetID, kACEColorMgmtPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kMPD_DontConvertRadioButtonWidgetID, kACEColorMgmtPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kMPD_HiddenOKButtonWidgetID, kACEColorMgmtPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kMPD_NormalOKButtonWidgetID, kACEColorMgmtPrefix + 14)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kColorSettingsObjectScriptElement,		kACEColorMgmtPrefix + 40)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kCMYKPolicyPropertyScriptElement,		kACEColorMgmtPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kEnableColorManagementPropertyScriptElement,		kACEColorMgmtPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kEnginePropertyScriptElement,		kACEColorMgmtPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kEngineListPropertyScriptElement,		kACEColorMgmtPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultIntentPropertyScriptElement,		kACEColorMgmtPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kMismatchAskWhenOpeningPropertyScriptElement,		kACEColorMgmtPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kMismatchAskWhenPastingPropertyScriptElement,		kACEColorMgmtPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kMissingAskWhenOpeningPropertyScriptElement,		kACEColorMgmtPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kRGBPolicyPropertyScriptElement,		kACEColorMgmtPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kSettingsPropertyScriptElement,		kACEColorMgmtPrefix + 79)
DECLARE_PMID(kScriptInfoIDSpace, kSettingsListPropertyScriptElement,		kACEColorMgmtPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kSettingsPathPropertyScriptElement,		kACEColorMgmtPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kUseBPCPropertyScriptElement,		kACEColorMgmtPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kWorkingSpaceCMYKPropertyScriptElement,		kACEColorMgmtPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kWorkingSpaceCMYKListPropertyScriptElement,		kACEColorMgmtPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kWorkingSpaceRGBPropertyScriptElement,		kACEColorMgmtPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kWorkingSpaceRGBListPropertyScriptElement,		kACEColorMgmtPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kProofingProfilePropertyScriptElement,		kACEColorMgmtPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kProofingTypePropertyScriptElement,		kACEColorMgmtPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kSimulateInkBlackPropertyScriptElement,		kACEColorMgmtPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kSimulatePaperWhitePropertyScriptElement,		kACEColorMgmtPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kCMYKProfilePropertyScriptElement,		kACEColorMgmtPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kCMYKProfileListPropertyScriptElement,		kACEColorMgmtPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kRGBProfilePropertyScriptElement,		kACEColorMgmtPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kRGBProfileListPropertyScriptElement,		kACEColorMgmtPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kSolidColorIntentPropertyScriptElement,		kACEColorMgmtPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kAfterBlendingIntentPropertyScriptElement,		kACEColorMgmtPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultImageIntentPropertyScriptElement,		kACEColorMgmtPrefix + 97)
//DECLARE_PMID(kScriptInfoIDSpace, kProfilePropertyScriptElement,		kACEColorMgmtPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kImageRenderingIntentPropertyScriptElement,		kACEColorMgmtPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kProfileListPropertyScriptElement,		kACEColorMgmtPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kColorSettingsPropertyScriptElement,		kACEColorMgmtPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveNumbersPropertyScriptElement,		kACEColorMgmtPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kDocPolicyRGBPropertyScriptElement,		kACEColorMgmtPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kDocPolicyCMYKPropertyScriptElement,		kACEColorMgmtPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kBlackConversionScreenPropertyScriptElement,kACEColorMgmtPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kBlackConversionExportPropertyScriptElement,kACEColorMgmtPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kAccurateLABSpotsPropertyScriptElement,	kACEColorMgmtPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kDLItemGrayPolicyPropertyScriptElement,	kACEColorMgmtPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kDLItemRGBPolicyPropertyScriptElement,		kACEColorMgmtPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kDLItemCMYKPolicyPropertyScriptElement,	kACEColorMgmtPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kDLItemPolicyEnumScriptElement,			kACEColorMgmtPrefix + 111)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kColorSettingsPolicyEnumScriptElement,		kACEColorMgmtPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultRenderingIntentEnumScriptElement,		kACEColorMgmtPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kProofingTypeEnumScriptElement,		kACEColorMgmtPrefix + 122)


//GUIDS
// {33d19dfa-cc8b-4977-ad62-948b130d0ceb}
#define kCMSSettings_CLSID { 0x33d19dfa, 0xcc8b, 0x4977, {0xad, 0x62, 0x94, 0x8b, 0x13, 0x0d, 0x0c, 0xeb} }

#endif	// __ACEColorMgmtID__

// End, ACEColorMgmtID.h.
