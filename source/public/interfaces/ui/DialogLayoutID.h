//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/DialogLayoutID.h $
//  
//  Owner: lance bushore
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

#ifndef __DialogLayoutID__
#define __DialogLayoutID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDialogLayoutPrefix	 RezLong(0x17e00)

// PluginID
#define kDialogLayoutPluginName 			"DialogLayout"
DECLARE_PMID(kPlugInIDSpace, kDialogLayoutPluginID, kDialogLayoutPrefix + 1)

// class ids
DECLARE_PMID(kClassIDSpace, kHighLevelDialogBoss, kDialogLayoutPrefix + 1)
DECLARE_PMID(kClassIDSpace, kHighLevelEnablingCheckboxBoss, kDialogLayoutPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDialogScriptProviderBoss, kDialogLayoutPrefix + 3)
DECLARE_PMID(kClassIDSpace, kWidgetScriptProviderBoss, kDialogLayoutPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDialogLayoutErrorStringBoss, kDialogLayoutPrefix + 5)
DECLARE_PMID(kClassIDSpace, kDialogLayoutStartupShutdownBoss, kDialogLayoutPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHighLevelMeasureComboboxBoss, kDialogLayoutPrefix + 7)
DECLARE_PMID(kClassIDSpace, kHighLevelMeasureEditboxBoss, kDialogLayoutPrefix + 8)


// impl ids
DECLARE_PMID(kImplementationIDSpace, kEVEUtilsImpl, kDialogLayoutPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCEveInfoImpl, kDialogLayoutPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPanelEveInfoImpl, kDialogLayoutPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kComboBoxEditboxEVEInfoImpl, kDialogLayoutPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kNudgeButtonEVEInfoImpl, kDialogLayoutPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kComboBoxDropDownEVEInfoImpl, kDialogLayoutPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kDropDownEVEInfoImpl, kDialogLayoutPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kButtonEVEInfoImpl, kDialogLayoutPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kTriStateEVEInfoImpl, kDialogLayoutPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kEnablingCheckboxObserverImpl, kDialogLayoutPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kHighLevelDialogControllerImpl, kDialogLayoutPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDialogScriptProviderImpl, kDialogLayoutPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kDialogScriptImpl, kDialogLayoutPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDialogLayoutErrorStringServiceImpl, kDialogLayoutPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kWidgetScriptProviderImpl, kDialogLayoutPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kHighLevelMeasureTypeImpl, kDialogLayoutPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kWidgetScriptImpl, kDialogLayoutPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineEVEInfoImpl, kDialogLayoutPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kScriptedDialogListImpl, kDialogLayoutPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kEVEPersistBoolDataImpl, kDialogLayoutPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kClusterEveInfoImpl, kDialogLayoutPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFixedSizeEVEInfoImpl, kDialogLayoutPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSingleLineEditTextEVEInfoImpl, kDialogLayoutPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kMultiLineEditBoxEVEInfoImpl, kDialogLayoutPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kComboBoxEVEInfoImpl, kDialogLayoutPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSeparatorEVEInfoImpl, kDialogLayoutPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kButtonBarEVEInfoImpl, kDialogLayoutPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kAGMStaticMultiLineEVEInfoImpl, kDialogLayoutPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPictureTextButtonEVEInfoImpl, kDialogLayoutPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTouchPanelEveInfoImpl, kDialogLayoutPrefix + 32)

// <Interface ID>
// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace, IID_IEVEINFO, kDialogLayoutPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IEVEUTILS, kDialogLayoutPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTWIDGETTYPE, kDialogLayoutPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTEDDIALOGLIST, kDialogLayoutPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIGHLEVELMEASUREMENTCLASS, kDialogLayoutPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGPREVIOUSLYSHOWN, kDialogLayoutPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYEVELAYOUTBOOLDATA, kDialogLayoutPrefix + 7)

// widget ids
DECLARE_PMID(kWidgetIDSpace, kHighLevelDropDownInitialWidgetID, kDialogLayoutPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kHighLevelButtonPanelWidgetID, kDialogLayoutPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kHighLevelDialogWidgetID, kDialogLayoutPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kEnablingCheckboxWidgetID, kDialogLayoutPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kHighLevelButtonSpacerPanelWidgetID, kDialogLayoutPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kGroupboxStaticTextWidgetID, kDialogLayoutPrefix + 6)

//gap
DECLARE_PMID(kWidgetIDSpace, kHighLevelFirstDynamicWidgetID, kDialogLayoutPrefix + 40)
// ids in this range are reserved
DECLARE_PMID(kWidgetIDSpace, kHighLevelLastDynamicWidgetID, kDialogLayoutPrefix + 255)

// error ids
DECLARE_PMID(kErrorIDSpace, kIllegalTextControlDataErr, kDialogLayoutPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kIllegalRadioButtonIndexErr, kDialogLayoutPrefix + 2)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kUISuiteScriptElement,kDialogLayoutPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kDialogObjectScriptElement,kDialogLayoutPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kWidgetObjectScriptElement,kDialogLayoutPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kTextEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kStaticTextWidgetObjectScriptElement,kDialogLayoutPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kDropDownWidgetObjectScriptElement,kDialogLayoutPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kCheckboxWidgetObjectScriptElement,kDialogLayoutPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kColumnWidgetObjectScriptElement,kDialogLayoutPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kRadioButtonGroupWidgetObjectScriptElement,kDialogLayoutPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kRadioButtonWidgetObjectScriptElement,kDialogLayoutPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kIntEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kIntComboboxWidgetObjectScriptElement,kDialogLayoutPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kEnablingCheckboxPanelObjectScriptElement,kDialogLayoutPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kAngleComboboxWidgetObjectScriptElement,kDialogLayoutPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPercentComboboxWidgetObjectScriptElement,kDialogLayoutPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kRealEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kPercentEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kAngleEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kRealComboboxWidgetObjectScriptElement,kDialogLayoutPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kMeasureComboboxWidgetObjectScriptElement,kDialogLayoutPrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kMeasureEditboxWidgetObjectScriptElement,kDialogLayoutPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kBorderPanelObjectScriptElement,kDialogLayoutPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kRowWidgetObjectScriptElement,kDialogLayoutPrefix + 32)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kShowDialogMethodScriptElement,kDialogLayoutPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kDestroyDialogMethodScriptElement,kDialogLayoutPrefix + 81)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kCanCancelTypePropertyScriptElement,kDialogLayoutPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kStaticLabelTypePropertyScriptElement,kDialogLayoutPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kEditContentsTypePropertyScriptElement,kDialogLayoutPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kCheckedStateTypePropertyScriptElement,kDialogLayoutPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kWidgetStringsTypePropertyScriptElement,kDialogLayoutPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kDropDownSelectedTypePropertyScriptElement,kDialogLayoutPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kRadioButtonSelectedTypePropertyScriptElement,kDialogLayoutPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kMinValuePropertyScriptElement,kDialogLayoutPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kMaxValuePropertyScriptElement,kDialogLayoutPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kEditboxUnitsPropertyScriptElement,kDialogLayoutPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kSmallNudgePropertyScriptElement,kDialogLayoutPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kLargeNudgePropertyScriptElement,kDialogLayoutPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kMinWidthPropertyScriptElement,kDialogLayoutPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kEditValueTypePropertyScriptElement,kDialogLayoutPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kStaticAlignmentPropertyScriptElement,kDialogLayoutPrefix + 154)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kStaticAlignmentEnumScriptElement,kDialogLayoutPrefix + 200)


//GUIDS
// {BACEA510-B2B4-4a50-97FD-DECD0DB1A4C6}
#define kDialog_CLSID { 0xbacea510, 0xb2b4, 0x4a50, { 0x97, 0xfd, 0xde, 0xcd, 0xd, 0xb1, 0xa4, 0xc6 }}
// {E470F8F5-7EBF-4b2a-B4C7-8BF929D14899}
#define kDialogs_CLSID { 0xe470f8f5, 0x7ebf, 0x4b2a, { 0xb4, 0xc7, 0x8b, 0xf9, 0x29, 0xd1, 0x48, 0x99 }}
// {1EF90526-6E13-471a-A4D0-621D7DAE6383}
#define kWidget_CLSID { 0x1ef90526, 0x6e13, 0x471a, { 0xa4, 0xd0, 0x62, 0x1d, 0x7d, 0xae, 0x63, 0x83 }}
// {198B3A70-6FF4-4a87-8E0F-241190B5D315}
#define kWidgets_CLSID { 0x198b3a70, 0x6ff4, 0x4a87, { 0x8e, 0xf, 0x24, 0x11, 0x90, 0xb5, 0xd3, 0x15 }}
// {F03EC221-07E2-4069-B4BF-3917F0400460}
#define kTextEditbox_CLSID { 0xf03ec221, 0x7e2, 0x4069, { 0xb4, 0xbf, 0x39, 0x17, 0xf0, 0x40, 0x4, 0x60 }}
// {45264B16-137C-443e-92C4-5DA6DB26A829}
#define kTextEditboxes_CLSID { 0x45264b16, 0x137c, 0x443e, { 0x92, 0xc4, 0x5d, 0xa6, 0xdb, 0x26, 0xa8, 0x29 }}
// {29E2C123-6633-42a8-AA13-54DA23BAB7A3}
#define kStatictext_CLSID { 0x29e2c123, 0x6633, 0x42a8, { 0xaa, 0x13, 0x54, 0xda, 0x23, 0xba, 0xb7, 0xa3 }}
// {38A8FB15-E42A-4c71-BD45-27650FBAABED}
#define kStaticTexts_CLSID { 0x38a8fb15, 0xe42a, 0x4c71, { 0xbd, 0x45, 0x27, 0x65, 0xf, 0xba, 0xab, 0xed }}
// {0CF3754F-0748-4e6d-9179-5F34D3B9CB42}
#define kDropDown_CLSID { 0xcf3754f, 0x748, 0x4e6d, { 0x91, 0x79, 0x5f, 0x34, 0xd3, 0xb9, 0xcb, 0x42 }}
// {EBB30B87-6335-4692-9A03-5F968E9B1586}
#define kDropDowns_CLSID { 0xebb30b87, 0x6335, 0x4692, { 0x9a, 0x3, 0x5f, 0x96, 0x8e, 0x9b, 0x15, 0x86 }}
// {C32E5412-6FAC-45b3-BD0B-002CB7431771}
#define kCheckbox_CLSID { 0xc32e5412, 0x6fac, 0x45b3, { 0xbd, 0xb, 0x0, 0x2c, 0xb7, 0x43, 0x17, 0x71 }}
// {B09C9105-8C2C-4271-8B1C-646926F5CC55}
#define kCheckboxes_CLSID { 0xb09c9105, 0x8c2c, 0x4271, { 0x8b, 0x1c, 0x64, 0x69, 0x26, 0xf5, 0xcc, 0x55 }}
// {7ECBF629-B1A5-4db3-A2A6-FBE7E1A275BD}
#define kColumnWidget_CLSID {0x7ecbf629, 0xb1a5, 0x4db3, { 0xa2, 0xa6, 0xfb, 0xe7, 0xe1, 0xa2, 0x75, 0xbd }}
// {D4D0E4CA-67C4-49b6-AAAB-1542851501B1}
#define kColumnWidgets_CLSID {0xd4d0e4ca, 0x67c4, 0x49b6, { 0xaa, 0xab, 0x15, 0x42, 0x85, 0x15, 0x1, 0xb1 }}
// {AA746D9F-6C48-4b0d-B27D-D5F8E74C8DB8}
#define kRadioButtonGroup_CLSID { 0xaa746d9f, 0x6c48, 0x4b0d, { 0xb2, 0x7d, 0xd5, 0xf8, 0xe7, 0x4c, 0x8d, 0xb8 }}
// {8B2909F0-1A1A-4950-AC9D-66EBF4E01FEB}
#define kRadioButtonGroups_CLSID { 0x8b2909f0, 0x1a1a, 0x4950, { 0xac, 0x9d, 0x66, 0xeb, 0xf4, 0xe0, 0x1f, 0xeb }}
// {770F5E5B-4E61-4b00-A230-8D5516FB7D8A}
#define kRadioButtonControl_CLSID {0x770f5e5b, 0x4e61, 0x4b00, { 0xa2, 0x30, 0x8d, 0x55, 0x16, 0xfb, 0x7d, 0x8a }}
// {4DE818E5-43D9-4f4b-96A9-387F70528E2E}
#define kRadioButtonControls_CLSID {0x4de818e5, 0x43d9, 0x4f4b, { 0x96, 0xa9, 0x38, 0x7f, 0x70, 0x52, 0x8e, 0x2e }}
// {F7A8FF11-041A-4b29-9557-B5A8DDCA8AA1}
#define kIntEditbox_CLSID {0xf7a8ff11, 0x41a, 0x4b29, { 0x95, 0x57, 0xb5, 0xa8, 0xdd, 0xca, 0x8a, 0xa1 }}
// {FF5D2EF8-DE6B-47df-B6E9-956B43E6ED43}
#define kIntEditboxes_CLSID {0xff5d2ef8, 0xde6b, 0x47df, { 0xb6, 0xe9, 0x95, 0x6b, 0x43, 0xe6, 0xed, 0x43 }}
// {BF60A933-65BB-407f-A458-182DD1579E17}
#define kIntCombobox_CLSID {0xbf60a933, 0x65bb, 0x407f, { 0xa4, 0x58, 0x18, 0x2d, 0xd1, 0x57, 0x9e, 0x17 }}
// {00785382-2FBA-47cf-B62B-E04B85CB1C2E}
#define kIntComboboxes_CLSID {0x785382, 0x2fba, 0x47cf, { 0xb6, 0x2b, 0xe0, 0x4b, 0x85, 0xcb, 0x1c, 0x2e }}
// {095E0F68-3825-4190-A315-D4458109CEE3}
#define kEnablingCheckboxPanel_CLSID {0x95e0f68, 0x3825, 0x4190, { 0xa3, 0x15, 0xd4, 0x45, 0x81, 0x9, 0xce, 0xe3 }}
// {6BEF766B-BDD3-4492-80E7-EC151759B702}
#define kEnablingCheckboxPanels_CLSID {0x6bef766b, 0xbdd3, 0x4492, { 0x80, 0xe7, 0xec, 0x15, 0x17, 0x59, 0xb7, 0x2 }}
// {4A194CA6-5570-4de1-BC10-70C855CBB8CD}
#define kAngleCombobox_CLSID {0x4a194ca6, 0x5570, 0x4de1, { 0xbc, 0x10, 0x70, 0xc8, 0x55, 0xcb, 0xb8, 0xcd }}
// {4A1021F6-51AE-41de-BACB-102174820161}
#define kAngleComboboxes_CLSID {0x4a1021f6, 0x51ae, 0x41de, { 0xba, 0xcb, 0x10, 0x21, 0x74, 0x82, 0x1, 0x61 }}
// {E3B3A2F1-35BB-4db3-BCC7-F3DD7420B66F}
#define kPercentCombobox_CLSID {0xe3b3a2f1, 0x35bb, 0x4db3, { 0xbc, 0xc7, 0xf3, 0xdd, 0x74, 0x20, 0xb6, 0x6f }}
// {D14B2AC8-B5BF-4003-AEEA-C1A9AE6A1041}
#define kPercentComboboxes_CLSID {0xd14b2ac8, 0xb5bf, 0x4003, { 0xae, 0xea, 0xc1, 0xa9, 0xae, 0x6a, 0x10, 0x41 }}
// {B0F8CEAB-B0FC-4ec1-BB50-DE897C1F0B67}
#define kRealEditbox_CLSID {0xb0f8ceab, 0xb0fc, 0x4ec1, { 0xbb, 0x50, 0xde, 0x89, 0x7c, 0x1f, 0xb, 0x67 }}
// {ACEDD68E-C591-4da3-BFBA-3AD62FB5BE59}
#define kRealEditboxes_CLSID {0xacedd68e, 0xc591, 0x4da3, { 0xbf, 0xba, 0x3a, 0xd6, 0x2f, 0xb5, 0xbe, 0x59 }}
// {95F86F90-2040-4d35-8E21-9B7215402F72}
#define kPercentEditbox_CLSID {0x95f86f90, 0x2040, 0x4d35, { 0x8e, 0x21, 0x9b, 0x72, 0x15, 0x40, 0x2f, 0x72 }}
// {1A81FB1A-BA42-4d1c-8A16-0562B2B21455}
#define kPercentEditboxes_CLSID {0x1a81fb1a, 0xba42, 0x4d1c, { 0x8a, 0x16, 0x5, 0x62, 0xb2, 0xb2, 0x14, 0x55 }}
// {0B824642-566D-428c-B478-2DF0953CB602}
#define kAngleEditbox_CLSID {0xb824642, 0x566d, 0x428c, { 0xb4, 0x78, 0x2d, 0xf0, 0x95, 0x3c, 0xb6, 0x2 }}
// {72785C56-7A80-4f7a-BA62-612D63DC0155}
#define kAngleEditboxes_CLSID {0x72785c56, 0x7a80, 0x4f7a, { 0xba, 0x62, 0x61, 0x2d, 0x63, 0xdc, 0x1, 0x55 }}
// {EEA59952-2888-46c3-BF4E-424BDB0BD53F}
#define kRealCombobox_CLSID {0xeea59952, 0x2888, 0x46c3, { 0xbf, 0x4e, 0x42, 0x4b, 0xdb, 0xb, 0xd5, 0x3f }}
// {3DC83780-1ABC-4b95-9D4E-53398C7CACAF}
#define kRealComboboxes_CLSID {0x3dc83780, 0x1abc, 0x4b95, { 0x9d, 0x4e, 0x53, 0x39, 0x8c, 0x7c, 0xac, 0xaf }}
// {7F521535-D9E9-46a4-9493-E12416126F86}
#define kMeasureComboboxes_CLSID {0x7f521535, 0xd9e9, 0x46a4, { 0x94, 0x93, 0xe1, 0x24, 0x16, 0x12, 0x6f, 0x86 }}
// {7DBBFFC6-A7A8-4a5c-8C7E-6DC5EEAF9946}
#define kMeasureCombobox_CLSID {0x7dbbffc6, 0xa7a8, 0x4a5c, { 0x8c, 0x7e, 0x6d, 0xc5, 0xee, 0xaf, 0x99, 0x46 }}
// {99B1C97E-920C-4fde-AD4D-69AF771C7D54}
#define kMeasureEditboxes_CLSID {0x99b1c97e, 0x920c, 0x4fde, { 0xad, 0x4d, 0x69, 0xaf, 0x77, 0x1c, 0x7d, 0x54 }}
// {111584BF-95B0-43ed-9C9D-24116A882E80}
#define kMeasureEditbox_CLSID {0x111584bf, 0x95b0, 0x43ed, { 0x9c, 0x9d, 0x24, 0x11, 0x6a, 0x88, 0x2e, 0x80 }}
// {AD32757F-393F-402c-9967-8A699BC3AF35}
#define kBorderPanel_CLSID { 0xad32757f, 0x393f, 0x402c, { 0x99, 0x67, 0x8a, 0x69, 0x9b, 0xc3, 0xaf, 0x35 } }
// {8D49AA57-C7CF-4b62-80E2-1ECACC1D666B}
#define kBorderPanels_CLSID { 0x8d49aa57, 0xc7cf, 0x4b62, { 0x80, 0xe2, 0x1e, 0xca, 0xcc, 0x1d, 0x66, 0x6b } }
// {42740710-13BF-42b6-89A4-6BE1DF884709}
#define kRowWidget_CLSID { 0x42740710, 0x13bf, 0x42b6, { 0x89, 0xa4, 0x6b, 0xe1, 0xdf, 0x88, 0x47, 0x9 } }
// {DAD06A68-9683-4640-97F7-E85FA22128E2}
#define kRowWidgets_CLSID { 0xdad06a68, 0x9683, 0x4640, { 0x97, 0xf7, 0xe8, 0x5f, 0xa2, 0x21, 0x28, 0xe2 } }


#endif
