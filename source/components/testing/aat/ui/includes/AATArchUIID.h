//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/ui/includes/AATArchUIID.h $
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

#ifndef __AATArchUIID__
#define __AATArchUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kDlgDescriptionFileFormatNumber 3.1
#define kSourceTreeFileFormatNumber		1.0
#define kActionListFileFormatNumber		1.0

#define kAATArchUIPrefix		RezLong(0x3db00)

//Reader
#define 	kDlgDescriptionFileType					kAATArchUIPrefix + 1
#define		kUIXFormFileType						kAATArchUIPrefix + 3
#define		kActionListFileType						kAATArchUIPrefix + 4


//UI codes for this plugin
#define kTreeRepresentationCode 					kAATArchUIPrefix + 1

// <Start IDC>
// PluginID
#define kAATArchUIPluginName 	"AAT Architecture UI"
DECLARE_PMID(kPlugInIDSpace, kAATArchUIPluginID, kAATArchUIPrefix + 1)


//---------------------------------------------------------------
// Resource IDs
//---------------------------------------------------------------

#define kAATArchUIStringsNoTransRsrcID				900
#define kAATArchUIDialogRsrcID					1000
#define kAATArchUIDialogActionResID				1100
#define kAATEditorDialogRsrcID					1200
#define kAATDataValueTreeRsrcID					1300
//gap
#define kAATDataValueComboBoxRsrcID				1600
#define kAATDataValueCheckBoxTreeRsrcID				1700
#define kAATDataValueStaticTextRsrcID				1800
#define kAATDataMeasurementStringTextRsrcID				1900
#define kAATErrorDialogRsrcID						2000
#define kAATCustomSourceDialogRsrcID				2100
#define kAllSourceTreeNodeWidgetRsrcID				2200
#define kCustomSourceNodeWidgetRsrcID				2300
#define kAATNameDialogRsrcID						2400

#define kAATManualActionDialogRsrcID				2500
#define kAATProgressDialogRsrcID					2600

#define kQATestSetEditorDialogRsrcID				2700
#define kTestSetTreeNodeWidgetRsrcID				2800

#define kAATSearchDialogRsrcID					2900
#define kAATSearchResultsDialogRsrcID				3000

#define kAATArchDebuggerRsrcID					3100
#define kSequencerSearchDialogRsrcID				3101
		
#define kAATArchMenuActionResID					128
#define kAATTreeNodeWidgetRsrcID					129
#define kSequencerNodeWidgetRsrcID					130
#define kAATSourceDynamicMenuResID					131
#define kDebuggerNodeWidgetRsrcID					132

#define kTestDataNodeWidgetRsrcID					141
#define kTestCheckBoxNodeWidgetRsrcID				142

#define kSearchResultListElementRsrcID				150

// <Class ID>
//---------------------------------------------------------------
// Boss IDs
//---------------------------------------------------------------

DECLARE_PMID(kClassIDSpace, kAATArchUIDialogBoss, 		kAATArchUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kAATMenuActionBoss, 		kAATArchUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kAATTreeViewWidgetBoss, 		kAATArchUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAATNodeWidgetBoss, 			kAATArchUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kAATNameBoss, 				kAATArchUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSequencerTreeViewWidgetBoss, 		kAATArchUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLoadAATFileButtonWidgetBoss, kAATArchUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kClearSequencerButtonWidgetBoss, 	kAATArchUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAddButtonWidgetBoss, 				kAATArchUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSaveSessionListButtonWidgetBoss, 	kAATArchUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kExecuteButtonWidgetBoss, 			kAATArchUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSequencerDDNodeWidgetBoss, 		kAATArchUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kAATDisplayStringWidgetBoss, 	kAATArchUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kReplaceButtonWidgetBoss, 			kAATArchUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSequencerRemoveButtonWidgetBoss, 	kAATArchUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSaveAsSessionListButtonWidgetBoss, kAATArchUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kExtendUIButtonWidgetBoss, 			kAATArchUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kLoadActionsButtonWidgetBoss, 		kAATArchUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kStringAcquisitionWidgetBoss, 		kAATArchUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kDropDownHandlerBoss,		 		kAATArchUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kDuplicateButtonWidgetBoss, 		kAATArchUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCDialogDescriptionBoss, 			kAATArchUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCDialogDescriptionListBoss, 		kAATArchUIPrefix + 23)
//gap
DECLARE_PMID(kClassIDSpace, kListBoxHandlerBoss,				kAATArchUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kButtonHandlerBoss,					kAATArchUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kDialogXMLReader_v1p0Boss,			kAATArchUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kCheckBoxHandlerBoss,				kAATArchUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kColorDropDownHandlerBoss,			kAATArchUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kTextListBoxHandlerBoss,			kAATArchUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kComboBoxHandlerBoss,				kAATArchUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kRenderListBoxHandlerBoss,			kAATArchUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kUIColorDropDownHandlerBoss,		kAATArchUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kStrokeDropDownHandlerBoss,			kAATArchUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kOwnerDropDownHandlerBoss,			kAATArchUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kIconHandlerBoss,					kAATArchUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kEditBoxHandlerBoss,				kAATArchUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kNudgeActionHandlerBoss,			kAATArchUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kRadioButtonHandlerBoss,			kAATArchUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSwitcherWidgetHandlerBoss,			kAATArchUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kAATSourceDDListWidgetBoss, 	kAATArchUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kAATCustomSourceDialogBoss, 	kAATArchUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kAllSourceTreeViewWidgetBoss, 		kAATArchUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kSourceAddButtonWidgetBoss, 		kAATArchUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kSourceRemoveButtonWidgetBoss, 		kAATArchUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kCustomSourceTreeViewWidgetBoss, 	kAATArchUIPrefix + 47)
DECLARE_PMID(kClassIDSpace, kAllSourceNodeWidgetBoss, 			kAATArchUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kCustomSourceNodeWidgetBoss, 		kAATArchUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kSaveAsSourceTreeButtonWidgetBoss, 	kAATArchUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kSaveSourceTreeButtonWidgetBoss, 	kAATArchUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kRenameSourceTreeButtonWidgetBoss, 	kAATArchUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kAddSourceGroupButtonWidgetBoss, 	kAATArchUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kCustomSourceDDListWidgetBoss, 		kAATArchUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kAATNameDialogBoss, 			kAATArchUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kSourceTreeReader_v1p0Boss,			kAATArchUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kDialogXMLReader_v2p0Boss,			kAATArchUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kAATUIIDTranslationListBoss,	kAATArchUIPrefix + 58)
DECLARE_PMID(kClassIDSpace, kDialogsAndPanelsAATActionListBoss,	kAATArchUIPrefix + 59)
DECLARE_PMID(kClassIDSpace, kWindowAATActionAddOnsBoss, 		kAATArchUIPrefix + 60)
DECLARE_PMID(kClassIDSpace, kICBridgeAATActionAddOnsBoss, 		kAATArchUIPrefix + 61)
DECLARE_PMID(kClassIDSpace, kCustomUIAATActionAddOnsBoss, 		kAATArchUIPrefix + 62)
DECLARE_PMID(kClassIDSpace, kValidatorUIAATActionAddOnsBoss, 	kAATArchUIPrefix + 63)
DECLARE_PMID(kClassIDSpace, kAcquisitionAATActionAddOnsBoss,	kAATArchUIPrefix + 64)
DECLARE_PMID(kClassIDSpace, kUIActionsAATActionListBoss,		kAATArchUIPrefix + 65)
DECLARE_PMID(kClassIDSpace, kWindowAATActionListBoss,		 	kAATArchUIPrefix + 66)
DECLARE_PMID(kClassIDSpace, kRunMenuEventWatcherBoss, 			kAATArchUIPrefix + 67)
DECLARE_PMID(kClassIDSpace, kImportExportAATActionListBoss,		kAATArchUIPrefix + 68)
DECLARE_PMID(kClassIDSpace, kImportExportEventWatcherBoss, 		kAATArchUIPrefix + 69)
DECLARE_PMID(kClassIDSpace, kAATManualActionDialogBoss,	kAATArchUIPrefix + 70)
DECLARE_PMID(kClassIDSpace, kAATProgressDialogBoss,		kAATArchUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kAATUIDescXFormBoss,			kAATArchUIPrefix + 72)
DECLARE_PMID(kClassIDSpace, kSourcedXFormBoss,			kAATArchUIPrefix + 73)
DECLARE_PMID(kClassIDSpace, kUIDescXformReader_v1p0Boss,        kAATArchUIPrefix + 74)
DECLARE_PMID(kClassIDSpace, kMainUIAATActionIDListBoss,			kAATArchUIPrefix + 75)
DECLARE_PMID(kClassIDSpace, kAATSequencerHandlerBoss,	kAATArchUIPrefix + 76)
DECLARE_PMID(kClassIDSpace, kAATSourceHandlerBoss,		kAATArchUIPrefix + 77)
DECLARE_PMID(kClassIDSpace, kAATCustomSourceHandlerBoss,kAATArchUIPrefix + 78)
DECLARE_PMID(kClassIDSpace, kReplaceRemoveUIActionXFormBoss,	kAATArchUIPrefix + 79)
DECLARE_PMID(kClassIDSpace, kPathEndStrokeDDHandlerBoss,		kAATArchUIPrefix + 80)
DECLARE_PMID(kClassIDSpace, kTreeHandlerBoss,					kAATArchUIPrefix + 81)
DECLARE_PMID(kClassIDSpace, kAATSourceContextMenuBoss,	kAATArchUIPrefix + 82)
DECLARE_PMID(kClassIDSpace, kAATSequencerContextMenuBoss,	kAATArchUIPrefix + 83)
DECLARE_PMID(kClassIDSpace, kTreeRepresentationGroupBoss,		kAATArchUIPrefix + 84)
DECLARE_PMID(kClassIDSpace, kAATDataTreeRowBoss,			kAATArchUIPrefix + 85)
DECLARE_PMID(kClassIDSpace, kAATDataTreeColumnBoss,		kAATArchUIPrefix + 86)
DECLARE_PMID(kClassIDSpace, kAATDataTreeEntryBoss,		kAATArchUIPrefix + 87)
DECLARE_PMID(kClassIDSpace, kTestSetEditorDialogBoss,			kAATArchUIPrefix + 88)
DECLARE_PMID(kClassIDSpace, kTestSetAddButtonWidgetBoss,		kAATArchUIPrefix + 89)
DECLARE_PMID(kClassIDSpace, kTestSetTreeViewWidgetBoss,			kAATArchUIPrefix + 90)
DECLARE_PMID(kClassIDSpace, kTestSetTreeCheckBoxBoss,			kAATArchUIPrefix + 91)
DECLARE_PMID(kClassIDSpace, kTestSetTreeNodeWidgetBoss,			kAATArchUIPrefix + 92)
DECLARE_PMID(kClassIDSpace, kTestSetRemoveButtonWidgetBoss,		kAATArchUIPrefix + 93)
DECLARE_PMID(kClassIDSpace, kTestSetNewSetButtonWidgetBoss,		kAATArchUIPrefix + 94)
DECLARE_PMID(kClassIDSpace, kTestSetLoadSetButtonWidgetBoss,	kAATArchUIPrefix + 95)
DECLARE_PMID(kClassIDSpace, kTestSetSaveButtonWidgetBoss,		kAATArchUIPrefix + 96)
DECLARE_PMID(kClassIDSpace, kTestSetSaveAsButtonWidgetBoss,		kAATArchUIPrefix + 97)
DECLARE_PMID(kClassIDSpace, kTestSetExecuteButtonWidgetBoss,	kAATArchUIPrefix + 98)
DECLARE_PMID(kClassIDSpace, kSliderHandlerBoss,					kAATArchUIPrefix + 99)
DECLARE_PMID(kClassIDSpace, kPointProxyHandlerBoss,				kAATArchUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, CustomWidgetAATActionAddOnsBoss, 	kAATArchUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kGlyphGridPanelHandlerBoss, 		kAATArchUIPrefix + 102)
DECLARE_PMID(kClassIDSpace, kSpreadWidgetHandlerBoss, 			kAATArchUIPrefix + 103)
DECLARE_PMID(kClassIDSpace, kStrokeFillProxyHandlerBoss, 		kAATArchUIPrefix + 104)
DECLARE_PMID(kClassIDSpace, kAATSearchDialogBoss, 		kAATArchUIPrefix + 105)
DECLARE_PMID(kClassIDSpace, kAATSearchResultsDialogBoss, 	kAATArchUIPrefix + 106)
DECLARE_PMID(kClassIDSpace, kSearchResultListElementNameBoss, 	kAATArchUIPrefix + 107)
DECLARE_PMID(kClassIDSpace, kAATCustomSourceContextMenuBoss, kAATArchUIPrefix + 108)
DECLARE_PMID(kClassIDSpace, kSearchResultsTreeViewWidgetBoss, 	kAATArchUIPrefix + 109)
DECLARE_PMID(kClassIDSpace, kUIDescriptionMgrBoss, 				kAATArchUIPrefix + 110)
DECLARE_PMID(kClassIDSpace, kPluginMgrListBoxHandlerBoss,		kAATArchUIPrefix + 111)
DECLARE_PMID(kClassIDSpace, kCFFTabOrderListBoxHandlerBoss,		kAATArchUIPrefix + 112)
DECLARE_PMID(kClassIDSpace, kAATVersionStrBoss,					kAATArchUIPrefix + 113)
DECLARE_PMID(kClassIDSpace, kWidgetIDChangeXFormBoss,			kAATArchUIPrefix + 114)
DECLARE_PMID(kClassIDSpace, kSearchResultTreeNodeWidgetBoss,	kAATArchUIPrefix + 115)
DECLARE_PMID(kClassIDSpace, kActionListReader_v1p0Boss,			kAATArchUIPrefix + 116)
DECLARE_PMID(kClassIDSpace, kCMenuActionListDataBoss,			kAATArchUIPrefix + 117)
DECLARE_PMID(kClassIDSpace, kCMenuActionDataBoss,				kAATArchUIPrefix + 118)
DECLARE_PMID(kClassIDSpace, kLibraryGridHandlerBoss,				kAATArchUIPrefix + 119)
DECLARE_PMID(kClassIDSpace, kStringIntPairDDHandlerBoss,		kAATArchUIPrefix + 120)
DECLARE_PMID(kClassIDSpace, kMediaDDHandlerBoss,				kAATArchUIPrefix + 121)
DECLARE_PMID(kClassIDSpace, kUndoRedoUICompareMgrBoss, 			kAATArchUIPrefix + 122)
DECLARE_PMID(kClassIDSpace, kDialogXMLReader_v3p0Boss,			kAATArchUIPrefix + 123)
DECLARE_PMID(kClassIDSpace, kGradientSliderHandlerBoss,			kAATArchUIPrefix + 124)
DECLARE_PMID(kClassIDSpace, kQABreakIdleTaskBoss,				kAATArchUIPrefix + 125)
DECLARE_PMID(kClassIDSpace, kQABreakEventWatcherBoss,			kAATArchUIPrefix + 126)
DECLARE_PMID(kClassIDSpace, kAATDebugPanelBoss,			kAATArchUIPrefix + 127)
DECLARE_PMID(kClassIDSpace, kAATEditorDialogBoss, 			kAATArchUIPrefix + 128)
DECLARE_PMID(kClassIDSpace, kCAATActionDataWidgetGroupBoss, 		kAATArchUIPrefix + 129)
DECLARE_PMID(kClassIDSpace, kTestDataTreeViewWidgetBoss, 			kAATArchUIPrefix + 130)
DECLARE_PMID(kClassIDSpace, kTestDataTreeNodeWidgetBoss, 			kAATArchUIPrefix + 131)
DECLARE_PMID(kClassIDSpace, kAATDataTreeViewWidgetBoss, 		kAATArchUIPrefix + 132)
DECLARE_PMID(kClassIDSpace, kAATDataTreeContainerBoss, 		kAATArchUIPrefix + 133)
DECLARE_PMID(kClassIDSpace, kAATDataFileComboWidgetGroupBoss, 			kAATArchUIPrefix + 134)
DECLARE_PMID(kClassIDSpace, kFileComboBrowseButtonWidgetBoss, 		kAATArchUIPrefix + 135)
DECLARE_PMID(kClassIDSpace, kQATDMultilineEditBoxWidgetBoss, 		kAATArchUIPrefix + 136)
DECLARE_PMID(kClassIDSpace, kTestDataCheckBoxTreeViewWidgetBoss, 	kAATArchUIPrefix + 137)
DECLARE_PMID(kClassIDSpace, kTestDataTreeCheckBoxBoss, 				kAATArchUIPrefix + 138)
DECLARE_PMID(kClassIDSpace, kAATDataTreeViewsWidgetGroupBoss, 			kAATArchUIPrefix + 139)
DECLARE_PMID(kClassIDSpace, kAATDataDropDownsWidgetGroupBoss, 			kAATArchUIPrefix + 140)
DECLARE_PMID(kClassIDSpace, kAATDataIndeterminateWidgetGroupBoss, 		kAATArchUIPrefix + 141)
DECLARE_PMID(kClassIDSpace, kAATDataEditBoxWidgetGroupBoss, 				kAATArchUIPrefix + 142)
DECLARE_PMID(kClassIDSpace, kSequencerGroupPanelWidgetBoss, 		kAATArchUIPrefix + 143)
DECLARE_PMID(kClassIDSpace, kModelGroupPanelWidgetBoss, 			kAATArchUIPrefix + 144)
DECLARE_PMID(kClassIDSpace, kSequencerEditButtonWidgetBoss, 		kAATArchUIPrefix + 145)
DECLARE_PMID(kClassIDSpace, kAATDataMeasurementWidgetGroupBoss, 			kAATArchUIPrefix + 146)
DECLARE_PMID(kClassIDSpace, kAATErrorDialogBoss, 				kAATArchUIPrefix + 147)
DECLARE_PMID(kClassIDSpace, kAATTestSetContextMenuBoss, 		kAATArchUIPrefix + 148)
DECLARE_PMID(kClassIDSpace, kSequencerExpanderWidgetBoss,			kAATArchUIPrefix + 149)
DECLARE_PMID(kClassIDSpace, kDebuggerExpanderWidgetBoss,			kAATArchUIPrefix + 150)
DECLARE_PMID(kClassIDSpace, kDebuggerTreeViewWidgetBoss, 			kAATArchUIPrefix + 151)
DECLARE_PMID(kClassIDSpace, kDebuggerGroupPanelWidgetBoss, 			kAATArchUIPrefix + 152)
DECLARE_PMID(kClassIDSpace, kParentChangeXFormBoss, 				kAATArchUIPrefix + 153)
DECLARE_PMID(kClassIDSpace, kCQuickApplyTreeHandlerBoss, 			kAATArchUIPrefix + 154)
DECLARE_PMID(kClassIDSpace, kWidgetInsertXFormBoss,					kAATArchUIPrefix + 155)
DECLARE_PMID(kClassIDSpace, kUIDescXformReader_v2p0Boss,			kAATArchUIPrefix + 156)
DECLARE_PMID(kClassIDSpace, kAATScrollEventObserverBoss,			kAATArchUIPrefix + 157)
DECLARE_PMID(kClassIDSpace, kDataChangeXFormBoss,					kAATArchUIPrefix + 158)
DECLARE_PMID(kClassIDSpace, kAATStringUIDDDListHandlerBoss,			kAATArchUIPrefix + 159)
DECLARE_PMID(kClassIDSpace,	kSequencerSearchDialogBoss, 			kAATArchUIPrefix + 160)
DECLARE_PMID(kClassIDSpace,	kGalleyFitProgressBarHandlerBoss, 			kAATArchUIPrefix + 161)
DECLARE_PMID(kClassIDSpace, kSwatchListBoxHandlerBoss,				kAATArchUIPrefix + 162)
DECLARE_PMID(kClassIDSpace, kStrokeListBoxHandlerBoss,				kAATArchUIPrefix + 163)
DECLARE_PMID(kClassIDSpace, kCornerTypeDDHandlerBoss,				kAATArchUIPrefix + 164)

// <Interface ID>
//---------------------------------------------------------------
// Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUIUTILS, 					kAATArchUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATDATAWIDGETGROUP, 			kAATArchUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDESCRIPTIONMGR, 			kAATArchUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELACTIONLIST, 				kAATArchUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGDESCRIPTION, 			kAATArchUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGDESCRIPTIONLIST,			kAATArchUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDSTRINGLIST,		 		kAATArchUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IREMOVESTRINGLIST,				kAATArchUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOADEDTESTCASEMANAGER,			kAATArchUIPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASESSIONFILESAVEDATA,			kAATArchUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIACQUISITIONMGR,		 		kAATArchUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDRIVERUTILS, 				kAATArchUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUIHANDLER, 				kAATArchUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IBREAKEVENTWATCHER, 			kAATArchUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATSOURCETREEREGISTRY, 		kAATArchUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONLISTREGISTRY,		 	kAATArchUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELACTIONLISTREGISTRY,		kAATArchUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATCANCELDATA,		 		kAATArchUIPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUIHANDLERREGISTRY, 			kAATArchUIPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUIDESCXFORMREGISTRY,		kAATArchUIPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUIDESCXFORM,				kAATArchUIPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATWIDGETXFORM,				kAATArchUIPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIAATACTIONIDREGISTRY,			kAATArchUIPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIAATACTIONIDLIST,			kAATArchUIPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATTESTSETDESCRIPTION,			kAATArchUIPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IDESCRIPTIONTEXTCONTROLDATA,		kAATArchUIPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUACTIONLISTDATA,			kAATArchUIPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUACTIONDATA,				kAATArchUIPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNDOREDOUICOMPAREMGR, 			kAATArchUIPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEQUENCERMGRREGISTRY, 			kAATArchUIPrefix + 30)



// <Implementation ID>
//---------------------------------------------------------------
// Implementation IDs
//---------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kAATArchUIObserverImpl,  					kAATArchUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAATArchUIControllerImpl, 					kAATArchUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAATMenuActionImpl,  	  					kAATArchUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kAATModelTreeViewMgrImpl,  					kAATArchUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAATModelTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAATModelTreeObserverImpl,  				kAATArchUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSequencerTreeViewMgrImpl,  				kAATArchUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSequencerTreeViewWidgetMgrImpl, 	 		kAATArchUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSequencerTreeObserverImpl,  				kAATArchUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLoadAATFileButtonObserverImpl, 				kAATArchUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kClearSequencerButtonObserverImpl,  			kAATArchUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAddButtonObserverImpl,  					kAATArchUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSaveSessionListButtonObserverImpl,  			kAATArchUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAATUIUtilsImpl,  						kAATArchUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kExecuteButtonObserverImpl,  				kAATArchUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSequencerDDTargetImpl,  					kAATArchUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSequencerNodeDDSourceImpl,  				kAATArchUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kAATTreeNodeEHImpl,  						kAATArchUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kAATReplaceButtonObserverImpl,  				kAATArchUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSequencerRemoveButtonObserverImpl,  			kAATArchUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSequencerNodeEHImpl,  					kAATArchUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSaveAsSessionListButtonObserverImpl, 		kAATArchUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kUIDescriptionMgrImpl, 					kAATArchUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCPanelActionListImpl, 					kAATArchUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kExtendUIButtonObserverImpl,  				kAATArchUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLoadActionsButtonObserverImpl,  			kAATArchUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kDuplicateButtonObserverImpl,  				kAATArchUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCDialogDescriptionImpl,  					kAATArchUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCDialogDescriptionListImpl,  				kAATArchUIPrefix + 32)
//gap
DECLARE_PMID(kImplementationIDSpace, kUIAcquisitionMgrImpl,  					kAATArchUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSourceTreeReader_v1p0Impl,					kAATArchUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kStringAcquisitionImpl, 					kAATArchUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAcquireServiceProviderImpl,	 			kAATArchUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kDropDownHandlerImpl, 						kAATArchUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kListBoxHandlerImpl, 						kAATArchUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kButtonHandlerImpl, 						kAATArchUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kDialogXMLReader_v1p0Impl,  				kAATArchUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kCheckBoxHandlerImpl, 						kAATArchUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kColorDropDownHandlerImpl, 					kAATArchUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kTextListBoxHandlerImpl, 					kAATArchUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kComboBoxHandlerImpl,	 					kAATArchUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kRenderListBoxHandlerImpl,	 				kAATArchUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kUIColorDropDownHandlerImpl,	 			kAATArchUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kStrokeDropDownHandlerImpl,	 				kAATArchUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kOwnerDropDownHandlerImpl,	 				kAATArchUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kIconHandlerImpl,	 						kAATArchUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kEditBoxHandlerImpl,	 					kAATArchUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kNudgeActionHandlerImpl,	 				kAATArchUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kRadioButtonHandlerImpl,	 				kAATArchUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSwitcherWidgetHandlerImpl,	 				kAATArchUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAATSourceDropListObserverImpl,				kAATArchUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kDialogXMLReader_v2p0Impl,					kAATArchUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kAATUIIDTranslationListImpl,				kAATArchUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kDialogsAndPanelsAATActionListImpl,			kAATArchUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kWindowAATActionAddOnsImpl,					kAATArchUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kICBridgeAATActionAddOnsImpl, 				kAATArchUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kCustomUIAATActionAddOnsImpl, 				kAATArchUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kValidatorUIAATActionAddOnsImpl, 			kAATArchUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kUIDriverUtilsImpl, 						kAATArchUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kUIActionsAATActionListImpl,				kAATArchUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kQAManualActionDlgControllerImpl,			kAATArchUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kQAManualActionDlgObserverImpl,				kAATArchUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kCustomDialogTimeoutWatcherImpl, 			kAATArchUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kAcquisitionAATActionAddOnsImpl,				kAATArchUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kWindowAATActionListImpl,	 				kAATArchUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kQAProgressBarUtilsImpl,  					kAATArchUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kActionListRegistryImpl,					kAATArchUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kCAlertWatcherListImpl, 					kAATArchUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kAATUIHandlerRegistryImpl, 				kAATArchUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kAATUIDescXFormRegistryImpl,     			kAATArchUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kUIDescXformReaderImpl,                	kAATArchUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCAATActionUIDescXFormImpl, 		        kAATArchUIPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kSourcedXFormImpl,							kAATArchUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kWidgetXFormServiceProviderImpl,  		    kAATArchUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kUIAATActionIDServiceProviderImpl,     	kAATArchUIPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kUIAATActionIDRegistryImpl,				kAATArchUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kMainUIAATActionIDListImpl,				kAATArchUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kAATSequencerHandlerImpl, 					kAATArchUIPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kAATSourceHandlerImpl, 					kAATArchUIPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kAATCustomSourceHandlerImpl,	 			kAATArchUIPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kAATSourceNodeDDSourceImpl, 				kAATArchUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kReplaceRemoveUIActionXFormImpl,				kAATArchUIPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kPathEndStrokeDDHandlerImpl,				kAATArchUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kTreeHandlerImpl,							kAATArchUIPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kAATSourceDynamicMenuImpl,					kAATArchUIPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kTreeRepresentationGroupImpl,				kAATArchUIPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kAATDataTreeRowImpl,						kAATArchUIPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kAATDataTreeColumnImpl,					kAATArchUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAATDataTreeEntryImpl,						kAATArchUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kAATDataTreeGroupObserverImpl,				kAATArchUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kPointProxyHandlerImpl,					kAATArchUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kCustomWidgetAATActionAddOnsImpl,			kAATArchUIPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kPluginMgrListBoxHandlerImpl,				kAATArchUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kCFFTabOrderListBoxHandlerImpl,				kAATArchUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kWidgetIDChangeXFormImpl,					kAATArchUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kStringIntPairDDHandlerImpl,				kAATArchUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kActionListReader_v1p0Impl,					kAATArchUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kCMenuActionListDataImpl,					kAATArchUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kCMenuActionDataImpl,						kAATArchUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kMediaDDHandlerImpl,						kAATArchUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kUndoRedoUICompareMgrImpl, 					kAATArchUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kDialogXMLReader_v3p0Impl,					kAATArchUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderHandlerImpl,					kAATArchUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kQABreakEventWatcherImpl,					kAATArchUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kQABreakIdleTaskImpl,						kAATArchUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kAATDebugPanelViewImpl,					kAATArchUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kDebuggerTreeViewMgrImpl,  					kAATArchUIPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kDebuggerTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kDebuggerNodeEHImpl,  						kAATArchUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kDebuggerExpanderWidgetObserverImpl,			kAATArchUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kDebuggerTreeViewImpl,						kAATArchUIPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kParentChangeXFormImpl,					kAATArchUIPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kCQuickApplyTreeHandlerImpl,  				kAATArchUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kWidgetInsertXFormImpl,					kAATArchUIPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kUIDescXformReader_v2p0Impl,     	     	kAATArchUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kAATScrollEventObserverImpl,     	     	kAATArchUIPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kDataChangeXFormImpl,						kAATArchUIPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kAATStringUIDDDListHandlerImpl,				kAATArchUIPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kAATEditorDialogControllerImpl,				kAATArchUIPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kAATEditorDialogObserverImpl,  				kAATArchUIPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kCAATDataWidgetGroupImpl,  					kAATArchUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kTestDataTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kTestDataTreeViewObserverImpl,  				kAATArchUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kTestDataTreeViewMgrImpl,  					kAATArchUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kTestDataValueWidgetMgrImpl,  				kAATArchUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kAATDataFileComboWidgetGroupImpl,  				kAATArchUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kFileComboBrowseButtonObserverImpl,  			kAATArchUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kIndeterminateDDObserverImpl,  				kAATArchUIPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kQATDMultilineEditBoxAttributesImpl,  		kAATArchUIPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kAATDataCheckBoxTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kCLoadedTestCaseManagerImpl,  				kAATArchUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kQASessionFileSaveDataImpl,  				kAATArchUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kAATDataWidgetGroupServiceProviderImpl, 			kAATArchUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kAATDataTreeViewsWidgetGroupImpl,  				kAATArchUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kAATDataDropDownsWidgetGroupImpl,  				kAATArchUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kAATDataIndeterminateWidgetGroupImpl,  			kAATArchUIPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kAATDataEditBoxWidgetGroupImpl,  				kAATArchUIPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kSequencerGroupControlViewImpl,  			kAATArchUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kModelGroupControlViewImpl,  				kAATArchUIPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kSequencerButtonsControlViewImpl,  			kAATArchUIPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kModelButtonsControlViewImpl,  				kAATArchUIPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kAATDataMeasurementWidgetGroupImpl,  				kAATArchUIPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kAATErrorDlgControllerImpl,  				kAATArchUIPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kDebuggerGroupControlViewImpl,  				kAATArchUIPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kSequencerMgrRegistryImpl,  				kAATArchUIPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kGalleyFitProgressBarHandlerImpl,  				kAATArchUIPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kSwatchListBoxHandlerImpl, 					kAATArchUIPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kStrokeListBoxHandlerImpl, 					kAATArchUIPrefix + 157)
//gap
DECLARE_PMID(kImplementationIDSpace, kAATErrorDlgEWImpl,  						kAATArchUIPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kAATSourceTreeRegistryImpl,  				kAATArchUIPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kAllSourceTreeObserverImpl,  				kAATArchUIPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kAllSourceTreeViewMgrImpl,  				kAATArchUIPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceDialogObserverImpl,  			kAATArchUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceDialogControllerImpl,  			kAATArchUIPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kSourceAddButtonObserverImpl,  				kAATArchUIPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kSourceRemoveButtonObserverImpl,  			kAATArchUIPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceTreeObserverImpl,  				kAATArchUIPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceTreeViewMgrImpl,  				kAATArchUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kAllSourceTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceTreeViewWidgetMgrImpl,  			kAATArchUIPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kAllSourceTreeNodeEHImpl,  					kAATArchUIPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceNodeDDSourceImpl,  				kAATArchUIPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceNodeEHImpl,  					kAATArchUIPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceDDTargetImpl,  				kAATArchUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kSaveAsSourceTreeButtonObserverImpl,  		kAATArchUIPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kSaveSourceTreeButtonObserverImpl,  			kAATArchUIPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kRenameSourceTreeButtonObserverImpl,  		kAATArchUIPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kAddSourceGroupButtonObserverImpl,  			kAATArchUIPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kCustomSourceDropListObserverImpl,  			kAATArchUIPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kAATNameDlgControllerImpl,  				kAATArchUIPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kTestSetEditorObserverImpl,  				kAATArchUIPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kTestSetEditorControllerImpl,  				kAATArchUIPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kTestSetAddButtonObserverImpl,  				kAATArchUIPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kTestSetTreeViewWidgetMgrImpl,  				kAATArchUIPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kTestSetTreeNodeEHImpl,  					kAATArchUIPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kTestSetNewSetButtonObserverImpl,  			kAATArchUIPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kTestSetLoadSetButtonObserverImpl,  			kAATArchUIPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kTestSetSaveButtonObserverImpl,  			kAATArchUIPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kTestSetSaveAsButtonObserverImpl,  			kAATArchUIPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kTestSetExecuteButtonObserverImpl,  			kAATArchUIPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kAATTestSetDescriptionImpl,					kAATArchUIPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kTestSetQATreeViewMgrImpl,					kAATArchUIPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kAATTestSetDynamicMenuImpl,					kAATArchUIPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kSliderHandlerImpl,						kAATArchUIPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kTestSetTreeCheckBoxEHImpl,					kAATArchUIPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kAATSequencerDynamicMenuImpl,				kAATArchUIPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kTestSetTreeNodeTipImpl,					kAATArchUIPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kAATModelTreeNodeTipImpl,					kAATArchUIPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kDescriptionTextControlDataImpl,				kAATArchUIPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelHandlerImpl,					kAATArchUIPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetHandlerImpl,					kAATArchUIPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillProxyHandlerImpl,				kAATArchUIPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kAATSearchDlgControllerImpl,				kAATArchUIPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kAATSearchResultsDlgControllerImpl,			kAATArchUIPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kSearchResultsWidgetMgrImpl,				kAATArchUIPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kSearchResultsTreeViewMgrImpl,				kAATArchUIPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kSequencerExpanderWidgetObserverImpl,			kAATArchUIPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kAATSearchResultsTreeNodeEHImpl,  			kAATArchUIPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kLibraryGridHandlerImpl,  					kAATArchUIPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kSequencerSearchDlgControllerImpl,			kAATArchUIPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kSequencerSearchDialogObserverImpl,		kAATArchUIPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kCornerTypeDDHandlerImpl,					kAATArchUIPrefix + 212)


//---------------------------------------------------------------
// Widget IDs
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kAATArchUIParentWidgetId, 				kAATArchUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kAATDisplayStringWidgetID, 				kAATArchUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kAATModelTreeControlWidgetID, 				kAATArchUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kAATListBoxGroupWidgetID, 				kAATArchUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kAATListBoxGroupTextWidgetID, 				kAATArchUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kAATArchAddButtonWidgetID, 						kAATArchUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRemoveButtonWidgetID, 					kAATArchUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kQATestDuplicateButtonWidgetID, 			kAATArchUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kEditButtonWidgetID, 					kAATArchUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kAATArchLoadButtonWidgetID, 					kAATArchUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kExecuteButtonWidgetID, 					kAATArchUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kAATArchSaveButtonWidgetID, 					kAATArchUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSequencerTreeControlWidgetID, 			kAATArchUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSequencerListBoxGroupWidgetID, 			kAATArchUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSequencerListBoxGroupTextWidgetID, 		kAATArchUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kAATGroupWidgetID, 						kAATArchUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kAATGroupTextWidgetID, 					kAATArchUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kClearSequencerButtonWidgetID, 			kAATArchUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kAATReplaceButtonWidgetID, 				kAATArchUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSaveAsButtonWidgetID, 					kAATArchUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kCloseButtonWidgetID, 					kAATArchUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kExtendUIButtonWidgetID, 					kAATArchUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLoadActionsButtonWidgetID, 				kAATArchUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kAATSourceDropDownListWidgetId, 			kAATArchUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kManualActionDialogWidgetID,				kAATArchUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kUserDefinedManualStaticWidgetID,			kAATArchUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kManualActionClickStaticWidgetID,			kAATArchUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kQAProgressDialogWidgetID,				kAATArchUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kQAProgressMainInfoWidgetID,				kAATArchUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kAATProgressBarWidgetID,					kAATArchUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kQAProgressSecondInfoStrWidgetID,			kAATArchUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kQASecondProgressBarWidgetID,				kAATArchUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kQACancelInstructionStrWidgetID,			kAATArchUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kAATVersionStrWidgetID,					kAATArchUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kAATDebugParentWidgetID,					kAATArchUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDebuggerTreeControlWidgetID, 				kAATArchUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kDebuggerListBoxGroupWidgetID, 			kAATArchUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kDebuggerListBoxGroupTextWidgetID, 			kAATArchUIPrefix + 38)


//gap
DECLARE_PMID(kWidgetIDSpace, kAATEditorParentWidgetId, 				kAATArchUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kAATEditorGroupWidgetID, 					kAATArchUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kAATEditorGroupTextWidgetID, 				kAATArchUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kTestDataTreeNodeWidgetID, 				kAATArchUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kTestDataTextWidgetID, 					kAATArchUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kTestDataTreeControlWidgetID, 				kAATArchUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kTestDataTreeTitleWidgetID, 				kAATArchUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kTestDataGroupWidgetID, 					kAATArchUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kDataGroupWidgetID, 						kAATArchUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kDataGroupTitleWidgetID,	 				kAATArchUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kDataValueStringWidgetID,	 				kAATArchUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kDataVariableStringWidgetID,	 			kAATArchUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kAATDataValueTreeWidgetID,	 			kAATArchUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kAATDataContainerWidgetID,	 			kAATArchUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kIterationStaticTextWidgetID,	 			kAATArchUIPrefix + 79)
//gap
DECLARE_PMID(kWidgetIDSpace, kIndeterTypeStaticTextWidgetID,	 		kAATArchUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kRelativeToStaticTextWidgetID,	 			kAATArchUIPrefix + 83)

//gap

DECLARE_PMID(kWidgetIDSpace, kAATDataComboBoxContainterWidgetID, 			kAATArchUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kAATDataComboBoxWidgetID, 				kAATArchUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kAATDataStaticTextContainterWidgetID, 			kAATArchUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kAATDescStaticTextWidgetID, 				kAATArchUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kAATStaticTextScrollBarWidgetID, 			kAATArchUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kAATDataMeasureTextContainterWidgetID, 			kAATArchUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kAATDataMeasureStaticTextWidgetID, 				kAATArchUIPrefix + 110)

DECLARE_PMID(kWidgetIDSpace, kAATErrorDlgParentWidgetId, 				kAATArchUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kTesletteNumErrorsStaticTextWidgetID,	 	kAATArchUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kTesletteErrorLogTextWidgetID,	 			kAATArchUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kAATErrorTextScrollBarWidgetID,	 		kAATArchUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kAATErrorLogGroupWidgetID, 				kAATArchUIPrefix + 115)
//gap
DECLARE_PMID(kWidgetIDSpace, kAATNameDlgParentWidgetId, 				kAATArchUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kTesletteNameStaticTextWidgetID, 			kAATArchUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kAATNameEditBoxWidgetID, 					kAATArchUIPrefix + 120)



//IDs 128-192 are reserved for Widget generation in the Editor Dialog
DECLARE_PMID(kWidgetIDSpace, kFirstDataGroupWidgetID, 					kAATArchUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kLastDataGroupWidgetID, 					kAATArchUIPrefix + 192)

//Start 193
DECLARE_PMID(kWidgetIDSpace, kCustomSourceEditorParentWidgetId, 			kAATArchUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kSaveAsSourceTreeButtonWidgetId, 			kAATArchUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kSaveSourceTreeButtonWidgetId, 			kAATArchUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kCustomSourceDoneButtonWidgetId, 			kAATArchUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kCustomSourceCancelButtonWidgetId, 			kAATArchUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kSourceTreesGroupWidgetID, 				kAATArchUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kAllSourceGroupWidgetID, 					kAATArchUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kAllSourceGroupTextWidgetID, 				kAATArchUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kAllSourceTreeControlWidgetID, 			kAATArchUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kSourceAddButtonWidgetID, 				kAATArchUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kSourceRemoveButtonWidgetID, 				kAATArchUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kCustomSourceGroupWidgetID, 				kAATArchUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kCustomSourceGroupNameEBWidgetID, 			kAATArchUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kCustomSourceTreeControlWidgetID, 			kAATArchUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kRenameSourceTreeButtonWidgetId, 			kAATArchUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kAddSourceGroupButtonWidgetId, 			kAATArchUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kTestSetEditorParentWidgetId, 				kAATArchUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kTestSetTreeGroupTextWidgetID, 			kAATArchUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kTestSetTreeGroupWidgetID, 				kAATArchUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kTestSetTreeControlWidgetID, 				kAATArchUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kTestSetDoneButtonWidgetId, 				kAATArchUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kTestSetAddButtonWidgetId, 				kAATArchUIPrefix + 214)
//gap
DECLARE_PMID(kWidgetIDSpace, kTestSetNewSetButtonWidgetId, 				kAATArchUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kTestSetSaveButtonWidgetId, 				kAATArchUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kTestSetSaveAsButtonWidgetId, 				kAATArchUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kTestSetLoadSetButtonWidgetId, 			kAATArchUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kTestSetExecuteButtonWidgetId, 			kAATArchUIPrefix + 220)

DECLARE_PMID(kWidgetIDSpace, kAATSearchDlgParentWidgetId, 		kAATArchUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kTesletteSearchStaticTextWidgetID, 		kAATArchUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kAATSearchEditBoxWidgetID, 			kAATArchUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kTesletteSearchInStaticTextWidgetID, 		kAATArchUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kAATSearchTreeClusterWidgetId, 		kAATArchUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kSearchDefaultSourceRBWidgetId, 			kAATArchUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kSearchCurrentSourceRBWidgetId, 			kAATArchUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kAATSearchResultsDlgParentWidgetId, 	kAATArchUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kTesletteSearchResultsStringWidgetID, 		kAATArchUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kSearchResultsListWidgetID, 				kAATArchUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kSearchResultListPanelWidgetID, 			kAATArchUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kSearchResultListElementNameWidgetID, 		kAATArchUIPrefix + 232)

DECLARE_PMID(kWidgetIDSpace, kSequencerSearchDlgParentWidgetId, 		kAATArchUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchStaticTextWidgetID, 		kAATArchUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchEditBoxWidgetID, 			kAATArchUIPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchByStaticTextWidgetID, 		kAATArchUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchByTreeClusterWidgetId, 	kAATArchUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchByActionNumRBWidgetId, 	kAATArchUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchByNameRBWidgetId, 			kAATArchUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kTopObjectGroupWidgetID, 					kAATArchUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kTopObjectGroupTextWidgetID, 				kAATArchUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchDirectionTreeClusterWidgetId, 			kAATArchUIPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchUpRBWidgetId, 				kAATArchUIPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kSequencerSearchDownRBWidgetId, 			kAATArchUIPrefix + 244)


//---------------------------------------------------------------
// Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kAATExecuteActionID,						kAATArchUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kWriteAATModelActionID, 					kAATArchUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDoMainDialogActionID, 					kAATArchUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kAATExecuteDirActionID, 					kAATArchUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kCloseDocsBetTestFilesActionID, 			kAATArchUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSuppressProgressBarActionID, 				kAATArchUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kSuppressCADialogsActionID, 				kAATArchUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kBeepOnCADialogsActionID, 				kAATArchUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kNoTimeoutCADialogsActionID, 				kAATArchUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, k30SecTimeoutCADialogsActionID, 			kAATArchUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, k1MinTimeoutCADialogsActionID, 			kAATArchUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, k5MinTimeoutCADialogsActionID, 			kAATArchUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kAATMenuSepActionID, 					kAATArchUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kBeepOnFinishActionID, 					kAATArchUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kOpenDialogOnFinishActionID, 				kAATArchUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kShowErrorDialogPrefActionID, 				kAATArchUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kAATUnloadDynamicMenuActionID, 			kAATArchUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kAATCustomizeContextMenuActionID, 			kAATArchUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kAATAddContextMenuActionID, 				kAATArchUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kAATDynamicMenuActionID, 					kAATArchUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kSetSessionDefaultsMenuActionID, 			kAATArchUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kLoadSessionDefaultsMenuActionID, 			kAATArchUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kUseBaseSessionSettingsPrefActionID, 		kAATArchUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kUnloadSourceTreeDynamicMenuActionID, 		kAATArchUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kWriteStringKeyValueMapMenuActionID, 		kAATArchUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kDoTestSetDialogActionID, 				kAATArchUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kRemoveTestFileFromSetMenuActionID, 		kAATArchUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kRemoveUncheckedFromSetMenuActionID, 		kAATArchUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kAATDynamicMenu2ActionID, 				kAATArchUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kAATExecuteTestSetsActionID, 				kAATArchUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kCommentOutSeqItemMenuActionID, 			kAATArchUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kAATDynamicMenu3ActionID, 				kAATArchUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kAATPackageForPulpoActionID, 				kAATArchUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kSearchSourceTreeContextMenuActionID, 		kAATArchUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kSearchCustomSourceCntxtMenuActionID, 		kAATArchUIPrefix + 35)
#ifdef PRERELEASE
DECLARE_PMID(kActionIDSpace, kGoToAATDocumentationActionID, 			kAATArchUIPrefix + 36)
#endif
DECLARE_PMID(kActionIDSpace, kCaptureOnUndoRedoActionID, 				kAATArchUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kQADebugAATPanelActionID,					kAATArchUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kAATReloadXFormsActionID,					kAATArchUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kAATWriteXFormFormatActionID, 				kAATArchUIPrefix + 40)
DECLARE_PMID(kActionIDSpace, kSearchSequencerMenuActionID, 			kAATArchUIPrefix + 41)
DECLARE_PMID(kActionIDSpace, kShowErrorLocationPrefActionID,            kAATArchUIPrefix + 42)

DECLARE_PMID(kActionIDSpace, kAATMenuSep2ActionID, 					kAATArchUIPrefix + 43)
DECLARE_PMID(kActionIDSpace, kAATMenuSep3ActionID, 					kAATArchUIPrefix + 44)
DECLARE_PMID(kActionIDSpace, kAATMenuSep4ActionID, 					kAATArchUIPrefix + 45)
DECLARE_PMID(kActionIDSpace, kAATMenuSep5ActionID, 					kAATArchUIPrefix + 46)
DECLARE_PMID(kActionIDSpace, kRemoveSequencerMenuActionID, 			kAATArchUIPrefix + 47)

//---------------------------------------------------------------
//	Service IDS
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kAATWidgetGroupService,					kAATArchUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kAcquireService,						kAATArchUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kWidgetXFormService,					kAATArchUIPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kUIAATActionIDService,						kAATArchUIPrefix + 4)


#endif // __QAAATActionArchUIID__
