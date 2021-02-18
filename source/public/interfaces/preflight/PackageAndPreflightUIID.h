//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/PackageAndPreflightUIID.h $
//  
//  Owner: scheng, mphillip
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
#ifndef __PackageAndPreflightUIID__
#define __PackageAndPreflightUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPackageAndPreflightUIPrefix		RezLong(0x9c00)
#define kPackageAndPreflightUIPrefix2		RezLong(0x20b00)		

// <Start IDC>
// PluginID
#define kPackageAndPreflightUIPlugInName			"Package and Preflight UI"
#define kPackageAndPreflightUIPlugInID 			kPackageAndPreflightUIPrefix + 1


// <Start IDC>
// <Class ID>
//	Begin OBSOLETE Class IDs
DECLARE_PMID(kClassIDSpace, kS4SPTestMenuBoss, kPackageAndPreflightUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kS4SPMenuBoss, kPackageAndPreflightUIPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPReportButtonBoss, kPackageAndPreflightUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kS4SPPackageButtonBoss, kPackageAndPreflightUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kS4SPUIBoss, kPackageAndPreflightUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kS4SPUIMasterDlogBoss, kPackageAndPreflightUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kS4SPUISummaryPanelBoss, kPackageAndPreflightUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kS4SPUIFontPanelBoss, kPackageAndPreflightUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kS4SPUILinkPanelBoss, kPackageAndPreflightUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kS4SPUIColorPanelBoss, kPackageAndPreflightUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kS4SPUISettingsPanelBoss, kPackageAndPreflightUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kS4SPMultiColumnTitleWidget, kPackageAndPreflightUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kS4SPMultiColumnListWidget, kPackageAndPreflightUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kS4SPSimpleScrollBarPanoramaSyncBoss, kPackageAndPreflightUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kS4SPMultiColumnListSubViewBoss, kPackageAndPreflightUIPrefix + 16)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPCurrentFontGroupBoss, kPackageAndPreflightUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kS4SPCurrentLinkGroupBoss, kPackageAndPreflightUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kS4SPFontMultiColumnListWidget, kPackageAndPreflightUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kS4SPLinkMultiColumnListWidget, kPackageAndPreflightUIPrefix + 21)//gap
DECLARE_PMID(kClassIDSpace, kS4SPLinkRepairAllBoss, kPackageAndPreflightUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kS4SPLinkUpdateBoss, kPackageAndPreflightUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kS4SPUIAlertBoss, kPackageAndPreflightUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kS4SPStaticTextWidget, kPackageAndPreflightUIPrefix + 26)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPUIJobTicketDlogBoss, kPackageAndPreflightUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kS4SPLinkShowProblemsOnlyBoss, kPackageAndPreflightUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kS4SPFontShowProblemsOnlyBoss, kPackageAndPreflightUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kS4SPSummaryShowHiddenDataBoss, kPackageAndPreflightUIPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPFindFontButtonBoss, kPackageAndPreflightUIPrefix + 34)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPUIPluginPanelBoss, kPackageAndPreflightUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kPreflightSrcDataBoss, kPackageAndPreflightUIPrefix + 38)
#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kS4SPControlTestMenuBoss,kPackageAndPreflightUIPrefix + 39)
#endif
//	End OBSOLETE Class IDs

//______________________________________________________________________
//	Basil Preflight UI
//______________________________________________________________________
DECLARE_PMID(kClassIDSpace, kPreflightUIAppMenuBoss,				kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kClassIDSpace, kPreflightUIPanelBoss,					kPackageAndPreflightUIPrefix2 + 2)
DECLARE_PMID(kClassIDSpace, kPreflightUIColumnTreeViewWidgetBoss,	kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorNodeWidgetBoss,		kPackageAndPreflightUIPrefix2 + 4)

DECLARE_PMID(kClassIDSpace, kPreflightUIPanelMenuBoss,				kPackageAndPreflightUIPrefix2 + 5)
DECLARE_PMID(kClassIDSpace, kPreflightUIInfoWidgetBoss,				kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kClassIDSpace, kPreflightProfileSelectorWidgetBoss,	kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kClassIDSpace, kPreflightUIInfoExpanderWidgetBoss,		kPackageAndPreflightUIPrefix2 + 8)
DECLARE_PMID(kClassIDSpace, kPreflightUIGotoButtonWidgetBoss,		kPackageAndPreflightUIPrefix2 + 9)

DECLARE_PMID(kClassIDSpace, kPreflightProfileDialogBoss,			kPackageAndPreflightUIPrefix2 + 10)
DECLARE_PMID(kClassIDSpace, kProfileDlgRulesTreeViewWidgetBoss,		kPackageAndPreflightUIPrefix2 + 11)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleCategoryNodeWidgetBoss,	kPackageAndPreflightUIPrefix2 + 12)
DECLARE_PMID(kClassIDSpace, kProfileDlgGeneralNodeWidgetBoss,		kPackageAndPreflightUIPrefix2 + 13)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleNodeWidgetBoss,			kPackageAndPreflightUIPrefix2 + 14)
DECLARE_PMID(kClassIDSpace, kProfileDlgNameEditBoxWidgetBoss,		kPackageAndPreflightUIPrefix2 + 15)
DECLARE_PMID(kClassIDSpace, kProfileDlgStaticTextWidgetBoss,		kPackageAndPreflightUIPrefix2 + 16)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleCheckBoxWidgetBoss,		kPackageAndPreflightUIPrefix2 + 17)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileButtonWidgetBoss,		kPackageAndPreflightUIPrefix2 + 18)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileButtonPopupWidgetBoss,kPackageAndPreflightUIPrefix2 + 19)
DECLARE_PMID(kClassIDSpace, kProfileDlgProflieButtonMenuBoss,		kPackageAndPreflightUIPrefix2 + 20)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileListWidgetBoss,		kPackageAndPreflightUIPrefix2 + 21)
DECLARE_PMID(kClassIDSpace, kProfileDlgLinksRuleUIWidgetBoss,		kPackageAndPreflightUIPrefix2 + 22)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileListNodeWidgetBoss,	kPackageAndPreflightUIPrefix2 + 23)

DECLARE_PMID(kClassIDSpace, kProfileDlgRuleGenericDataWidgetBoss,	kPackageAndPreflightUIPrefix2 + 24)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleGenericCheckboxWidgetBoss,kPackageAndPreflightUIPrefix2 + 25)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleGenericEditboxWidgetBoss,kPackageAndPreflightUIPrefix2 + 26)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleGenericDropdownWidgetBoss,kPackageAndPreflightUIPrefix2 + 27)
DECLARE_PMID(kClassIDSpace, kPreflightProfileNameWidgetBoss,		kPackageAndPreflightUIPrefix2 + 28)
//gap

DECLARE_PMID(kClassIDSpace, kPreflightUIIntEditBoxWidgetBoss,		kPackageAndPreflightUIPrefix2 + 29)
DECLARE_PMID(kClassIDSpace, kPreflightUIRealEditBoxWidgetBoss,		kPackageAndPreflightUIPrefix2 + 30)
DECLARE_PMID(kClassIDSpace, kPreflightUITextMeasureEditBoxWidgetBoss,kPackageAndPreflightUIPrefix2 + 31)
DECLARE_PMID(kClassIDSpace, kPreflightUITextSizeMeasureEditBoxWidgetBoss,	kPackageAndPreflightUIPrefix2 + 32)
DECLARE_PMID(kClassIDSpace, kPreflightUILineWtMeasureEditBoxWidgetBoss,	kPackageAndPreflightUIPrefix2 + 33)
DECLARE_PMID(kClassIDSpace, kPreflightUIXMeasureEditBoxWidgetBoss,	kPackageAndPreflightUIPrefix2 + 34)
DECLARE_PMID(kClassIDSpace, kPreflightUIYMeasureEditBoxWidgetBoss,	kPackageAndPreflightUIPrefix2 + 35)
DECLARE_PMID(kClassIDSpace, kPreflightUIPercentageEditBoxWidgetBoss,kPackageAndPreflightUIPrefix2 + 36)

DECLARE_PMID(kClassIDSpace, kPreflightOptionsDialogBoss,			kPackageAndPreflightUIPrefix2 + 38)
DECLARE_PMID(kClassIDSpace, kPreflightUIOnOffWidgetBoss,			kPackageAndPreflightUIPrefix2 + 39)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorHeaderWidgetBoss,		kPackageAndPreflightUIPrefix2 + 40)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorInfoProviderBoss,		kPackageAndPreflightUIPrefix2 + 41)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorPageInfoProviderBoss,	kPackageAndPreflightUIPrefix2 + 42)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorTextWidgetBoss,		kPackageAndPreflightUIPrefix2 + 43)
DECLARE_PMID(kClassIDSpace, kPreflightUIErrorPageTextWidgetBoss,	kPackageAndPreflightUIPrefix2 + 44)
DECLARE_PMID(kClassIDSpace, kPreflightUIEmbedButtonWidgetBoss,		kPackageAndPreflightUIPrefix2 + 45)
DECLARE_PMID(kClassIDSpace, kPreflightUIScopePanelWidgetBoss,		kPackageAndPreflightUIPrefix2 + 46)
// gap
DECLARE_PMID(kClassIDSpace, kPreflightUIBookMenuBoss,				kPackageAndPreflightUIPrefix2 + 48)
DECLARE_PMID(kClassIDSpace, kPreflightBookOptionsDialogBoss,		kPackageAndPreflightUIPrefix2 + 49)

DECLARE_PMID(kClassIDSpace, kPreflightUIStatusPanelWidgetBoss,		kPackageAndPreflightUIPrefix2 + 50)
DECLARE_PMID(kClassIDSpace, kPreflightUIStatusPopupMenuActionBoss,	kPackageAndPreflightUIPrefix2 + 51)
//gap

DECLARE_PMID(kClassIDSpace, kProfileDlgRuleDataNodeWidgetBoss,		kPackageAndPreflightUIPrefix2 + 53)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleGenericTBLRWidgetBoss,	kPackageAndPreflightUIPrefix2 + 54)
DECLARE_PMID(kClassIDSpace, kProfileDlgFontSpecDropdownWidgetBoss,	kPackageAndPreflightUIPrefix2 + 55)
DECLARE_PMID(kClassIDSpace, kPreflightUIInfoBoxBorderPanelWidgetBoss,kPackageAndPreflightUIPrefix2 + 56)
DECLARE_PMID(kClassIDSpace, kPreflightUIMenuActionFilterBoss,		kPackageAndPreflightUIPrefix2 + 57)
DECLARE_PMID(kClassIDSpace, kProfileDlgDuplicateBasicDialogBoss,	kPackageAndPreflightUIPrefix2 + 58)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileListStaticTextWidgetBoss,	kPackageAndPreflightUIPrefix2 + 59)
DECLARE_PMID(kClassIDSpace, kProfileDlgRuleStaticTextWidgetBoss,	kPackageAndPreflightUIPrefix2 + 60)
DECLARE_PMID(kClassIDSpace, kProfileDlgInLineContainerWidgetBoss,	kPackageAndPreflightUIPrefix2 + 61)
DECLARE_PMID(kClassIDSpace, kProfileDlgMultiEditContainerWidgetBoss,kPackageAndPreflightUIPrefix2 + 62)
DECLARE_PMID(kClassIDSpace, kProfileDlgInLineDropdownContainerWidgetBoss,	kPackageAndPreflightUIPrefix2 + 63)
DECLARE_PMID(kClassIDSpace, kProfileDlgInLineEditContainerWidgetBoss,kPackageAndPreflightUIPrefix2 + 64)
DECLARE_PMID(kClassIDSpace, kProfileDlgInlineStaticTextWidgetBoss,	kPackageAndPreflightUIPrefix2 + 65)
DECLARE_PMID(kClassIDSpace, kProfileDlgInlineDropDownStaticTextWidgetBoss,	kPackageAndPreflightUIPrefix2 + 66)
DECLARE_PMID(kClassIDSpace, kProfileDlgInLineEditEventMonitorBoss,	kPackageAndPreflightUIPrefix2 + 67)
DECLARE_PMID(kClassIDSpace, kPreflightUITreeScrollerWidgetBoss,		kPackageAndPreflightUIPrefix2 + 68)
DECLARE_PMID(kClassIDSpace, kPreflightDlgRulesTreeScrollerWidgetBoss,kPackageAndPreflightUIPrefix2 + 69)
DECLARE_PMID(kClassIDSpace, kProfileDlgProfileListScrollerWidgetBoss,kPackageAndPreflightUIPrefix2 + 70)
DECLARE_PMID(kClassIDSpace, kProfileDescriptionInlineStaticTextWidgetBoss,kPackageAndPreflightUIPrefix2 + 71)


// <Interface ID>
//	Begin OBSOLETE Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPPACKAGEUI, kPackageAndPreflightUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPPREFLIGHTUI, kPackageAndPreflightUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPJOBTICKETUI, kPackageAndPreflightUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPMULTICOLUMNATTR, kPackageAndPreflightUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPMULTICOLUMNLISTATTR, kPackageAndPreflightUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPMULTICOLUMNTITLEATTR, kPackageAndPreflightUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPTABLE, kPackageAndPreflightUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPTABLESELECTOR, kPackageAndPreflightUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPTEXTFONTATTR, kPackageAndPreflightUIPrefix + 9)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPHASKEYBOARDFOCUS, kPackageAndPreflightUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SLINKBROWSEUI, kPackageAndPreflightUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKMENU, kPackageAndPreflightUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IS4SPUIUTILS, kPackageAndPreflightUIPrefix + 17)
//	End Obsolete Interface IDs

//______________________________________________________________________
//	Basil Preflight UI
//______________________________________________________________________
DECLARE_PMID(kInterfaceIDSpace, IID_IPROFILEDLGUTILS,				kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTNATIVERULEUIHANDLER,	kPackageAndPreflightUIPrefix2 + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEUI,				kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROFILEDLGRULEDATAPANELHANDLER,kPackageAndPreflightUIPrefix2 + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEPREFLIGHTUIUTILS,		kPackageAndPreflightUIPrefix2 + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIPANELDATA,			kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOPTIONSDLGUTILS,		kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIPANELPREFS,			kPackageAndPreflightUIPrefix2 + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIERRORINFOPROVIDER,	kPackageAndPreflightUIPrefix2 + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERATEREPORTBOOLDATA,		kPackageAndPreflightUIPrefix2 + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIUTILS,				kPackageAndPreflightUIPrefix2 + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTDLGPROFILEMANAGER,	kPackageAndPreflightUIPrefix2 + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIINFOBOXLINEBREAKDATA,kPackageAndPreflightUIPrefix2 + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROFILEDLGRULEDATANODEHANDLER,	kPackageAndPreflightUIPrefix2 + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUIGLOBALOBSERVER,		kPackageAndPreflightUIPrefix2 + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWSTATICNUDGEWIDGETFLAG,		kPackageAndPreflightUIPrefix2 + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEUIPARAMTABLE,		kPackageAndPreflightUIPrefix2 + 17)


// <Service ID>
//	Begin Obsolete Service IDs
DECLARE_PMID(kServiceIDSpace, kPreflightDialogService, kPackageAndPreflightUIPrefix + 1)
//	End Obsolete Service IDs

// <Message ID>
//	Begin Obsolete Message IDs
DECLARE_PMID(kMessageIDSpace, kS4SPSelectionChanged, kPackageAndPreflightUIPrefix + 1) //If the user has moved the selection
DECLARE_PMID(kMessageIDSpace, kS4SPPreflightChanged, kPackageAndPreflightUIPrefix + 2)	//if the preflight has been modified by anything
//	End Obsolete Message IDs
DECLARE_PMID(kMessageIDSpace, kPreflightUIProfileConflictDontShowID, kPackageAndPreflightUIPrefix + 3)

//______________________________________________________________________
// Basil preflight Service IDs
//______________________________________________________________________
DECLARE_PMID(kServiceIDSpace, kPreflightUIErrorInfoService, kPackageAndPreflightUIPrefix2 + 1)

//______________________________________________________________________
// Basil preflight Message IDs
//______________________________________________________________________
DECLARE_PMID(kMessageIDSpace, kProfileGeneralInfoChangeMessage,			kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kMessageIDSpace, kProfileRuleDataChangeMessage,			kPackageAndPreflightUIPrefix2 + 2)
DECLARE_PMID(kMessageIDSpace, kProfilesSavedMessage,					kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kMessageIDSpace, kProfileRuleCategoryTrueChangeMessage,	kPackageAndPreflightUIPrefix2 + 4)
DECLARE_PMID(kMessageIDSpace, kProfileRuleCategoryFalseChangeMessage,	kPackageAndPreflightUIPrefix2 + 5)
DECLARE_PMID(kMessageIDSpace, kProfileRuleStateChangeMessage,			kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kMessageIDSpace, kProfileNewDeleteMessage,					kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kMessageIDSpace, kPreflightUIPanelDataChanged,				kPackageAndPreflightUIPrefix2 + 8)
DECLARE_PMID(kMessageIDSpace, kProfileApptemptedChangesToBasicProfile,	kPackageAndPreflightUIPrefix2 + 9)
DECLARE_PMID(kMessageIDSpace, kProfileCustomRuleDataChangeMessage,		kPackageAndPreflightUIPrefix2 + 10)


// <Implementation ID>
//	Begin Obsolete implemenation IDs
DECLARE_PMID(kImplementationIDSpace, kS4SPTestMenu, kPackageAndPreflightUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kS4SPTable, kPackageAndPreflightUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kS4SPMenu, kPackageAndPreflightUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kInaccessibleUrlLinkRuleUIImpl, kPackageAndPreflightUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageButtonObserver, kPackageAndPreflightUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kS4SPReportButtonObserver, kPackageAndPreflightUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPackageUI, kPackageAndPreflightUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLinkBrowseUI, kPackageAndPreflightUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kJobTicketUI, kPackageAndPreflightUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPreflightLinkPanelCreator, kPackageAndPreflightUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPreflightSummaryPanelCreator, kPackageAndPreflightUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPreflightFontPanelCreator, kPackageAndPreflightUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPreflightColorPanelCreator, kPackageAndPreflightUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kPreflightSettingsPanelCreator, kPackageAndPreflightUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPreflightMasterDialogCreator, kPackageAndPreflightUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnTitleView, kPackageAndPreflightUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnAttr, kPackageAndPreflightUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnListView, kPackageAndPreflightUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnListAttr, kPackageAndPreflightUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnTitleAttr, kPackageAndPreflightUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnPanorama, kPackageAndPreflightUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnListEventHandler, kPackageAndPreflightUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kS4SPSimpleScrollBarPanoramaSyncImpl, kPackageAndPreflightUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kS4SPSimpleScrollBarPanoramaSyncObserverImpl, kPackageAndPreflightUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kS4SPPanelWithBorderView, kPackageAndPreflightUIPrefix + 25)
//gap
DECLARE_PMID(kImplementationIDSpace, kLinkPanelController, kPackageAndPreflightUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSettingsPanelController, kPackageAndPreflightUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kFontPanelController, kPackageAndPreflightUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kInkPanelController, kPackageAndPreflightUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kSummaryPanelController, kPackageAndPreflightUIPrefix + 31)
//gap
DECLARE_PMID(kImplementationIDSpace, kTableSelector, kPackageAndPreflightUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kS4SPMultiColumnListViewEventHandler, kPackageAndPreflightUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kS4SPFontTableObserver, kPackageAndPreflightUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkTableObserver, kPackageAndPreflightUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kS4SPFontListObserver, kPackageAndPreflightUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkListObserver, kPackageAndPreflightUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkUpdateObserver, kPackageAndPreflightUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkRepairAllObserver, kPackageAndPreflightUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSummaryPanelObserver, kPackageAndPreflightUIPrefix + 41)
//gap
DECLARE_PMID(kImplementationIDSpace, kJobTicketDialogCreator, kPackageAndPreflightUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kS4SPSaveDialog, kPackageAndPreflightUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kOKCancelDialogObserver, kPackageAndPreflightUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kOKCancelSelectableObserver, kPackageAndPreflightUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kJobTicketDialogController, kPackageAndPreflightUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kHiddenLayerDialogSwitcher, kPackageAndPreflightUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kS4SPHasKeyboardFocus, kPackageAndPreflightUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kS4SPFontShowProblemsOnlyObserver, kPackageAndPreflightUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkShowProblemsOnlyObserver, kPackageAndPreflightUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kS4SPSummaryShowHiddenDataObserver, kPackageAndPreflightUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kFontPanelObserver, kPackageAndPreflightUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kLinkPanelObserver, kPackageAndPreflightUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kS4SPFontShowProblemsOnlyView, kPackageAndPreflightUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kS4SPLinkShowProblemsOnlyView, kPackageAndPreflightUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kS4SPSummaryShowHiddenDataView, kPackageAndPreflightUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kInkPanelObserver, kPackageAndPreflightUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kS4SPFindFontButtonObserverImpl, kPackageAndPreflightUIPrefix + 62)
//gap
DECLARE_PMID(kImplementationIDSpace, kPreflightPluginPanelCreator, kPackageAndPreflightUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPluginPanelController, kPackageAndPreflightUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookMenuImpl, kPackageAndPreflightUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace,kS4SPUIUtilsImpl,    kPackageAndPreflightUIPrefix + 68)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace,kS4SPControlTestMenu,    kPackageAndPreflightUIPrefix + 69)
#endif
//	End Obsolete implemenation IDs

//______________________________________________________________________
//	Basil Preflight UI
//______________________________________________________________________
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kPreflightNativeRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 2)

DECLARE_PMID(kImplementationIDSpace, kImageResolutionRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kImplementationIDSpace, kWhiteOverprintRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kOversetTextRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 5)
DECLARE_PMID(kImplementationIDSpace, kMissingModifiedGraphicsRuleUIImpl,kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kStrokeRequirementsRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kImplementationIDSpace, kSmallTextRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 8)
//DECLARE_PMID(kImplementationIDSpace, kTestingHelperRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 9)
DECLARE_PMID(kImplementationIDSpace, kBleedSlugRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 10)
DECLARE_PMID(kImplementationIDSpace, kPageSizeOrientationRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 11)
DECLARE_PMID(kImplementationIDSpace, kPageCountRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 12)
DECLARE_PMID(kImplementationIDSpace, kColorspaceRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 13)
DECLARE_PMID(kImplementationIDSpace, kSpotColorSetupRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 14)
DECLARE_PMID(kImplementationIDSpace, kFontUsageRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 15)
//DECLARE_PMID(kImplementationIDSpace, kTextAndTransparencyRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 16)
DECLARE_PMID(kImplementationIDSpace, kScaledTypeRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 17)
DECLARE_PMID(kImplementationIDSpace, kTransparencyUsageRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 18)
DECLARE_PMID(kImplementationIDSpace, kImageColorManagementRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 19)
//DECLARE_PMID(kImplementationIDSpace, kImageCompressionRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 20)
DECLARE_PMID(kImplementationIDSpace, kOPIRuleUIImpl,					kPackageAndPreflightUIPrefix2 + 21)
DECLARE_PMID(kImplementationIDSpace, kInteractiveContentRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 22)
//DECLARE_PMID(kImplementationIDSpace, kPlacedPDFRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 23)
//DECLARE_PMID(kImplementationIDSpace, kPlacedEPSRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 24)
//DECLARE_PMID(kImplementationIDSpace, kRichBlackRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 25)
DECLARE_PMID(kImplementationIDSpace, kCMYPlatesRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 26)
//DECLARE_PMID(kImplementationIDSpace, kPlacedContentSpotRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 27)
//DECLARE_PMID(kImplementationIDSpace, kDPOERuleUIImpl,					kPackageAndPreflightUIPrefix2 + 28)
DECLARE_PMID(kImplementationIDSpace, kTransparencyBlendingRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 29)
DECLARE_PMID(kImplementationIDSpace, kBlankPagesRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 30)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 31)
//DECLARE_PMID(kImplementationIDSpace, kUnusedColorsRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 32)
DECLARE_PMID(kImplementationIDSpace, kBleedTrimHazardRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 33)
DECLARE_PMID(kImplementationIDSpace, kConditionIndicatorsRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 34)
DECLARE_PMID(kImplementationIDSpace, kTextOverridesRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 35)
DECLARE_PMID(kImplementationIDSpace, kCrossReferencesRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 36)
DECLARE_PMID(kImplementationIDSpace, kOverprintRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 37)
DECLARE_PMID(kImplementationIDSpace, kRegistrationRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kLayerVisibilityRuleUIImpl,		kPackageAndPreflightUIPrefix2 + 39)
//DECLARE_PMID(kImplementationIDSpace, kCompositionViolationsRuleUIImpl,	kPackageAndPreflightUIPrefix2 + 40)
DECLARE_PMID(kImplementationIDSpace, kMissingGlyphRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 41)
DECLARE_PMID(kImplementationIDSpace, kScaledGraphicsRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 42)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckRuleUIImpl,				kPackageAndPreflightUIPrefix2 + 43)
DECLARE_PMID(kImplementationIDSpace, kHiddenPageItemRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 44)
DECLARE_PMID(kImplementationIDSpace, kTrackedChangeRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 45)
DECLARE_PMID(kImplementationIDSpace, kUnresolvedCaptionVariableRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 46)
DECLARE_PMID(kImplementationIDSpace, kMultiPageSizesRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 47)
DECLARE_PMID(kImplementationIDSpace, kSpanColumnsRuleUIImpl,			kPackageAndPreflightUIPrefix2 + 48)

//	gap: reserved for rule UI

//	Custom rule UI
DECLARE_PMID(kImplementationIDSpace, kProfileDlgLinksRulePanelObserverImpl,		kPackageAndPreflightUIPrefix2 + 79)
//	gap
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileDialogCreatorImpl,		kPackageAndPreflightUIPrefix2 + 80)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgControllerImpl,					kPackageAndPreflightUIPrefix2 + 81)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgGeneralPanelObserverImpl,		kPackageAndPreflightUIPrefix2 + 82)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleNodeObserverImpl,			kPackageAndPreflightUIPrefix2 + 83)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRulesTreeViewWidgetMgrImpl,		kPackageAndPreflightUIPrefix2 + 84)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRulesTreeViewAdapterImpl,		kPackageAndPreflightUIPrefix2 + 85)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListBoxControllerImpl,	kPackageAndPreflightUIPrefix2 + 86)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListBoxWidgetMgrImpl,	kPackageAndPreflightUIPrefix2 + 87)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListBoxTreeAdapterImpl,	kPackageAndPreflightUIPrefix2 + 88)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListNodeViewImpl,		kPackageAndPreflightUIPrefix2 + 89)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgObserverImpl,					kPackageAndPreflightUIPrefix2 + 90)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgUtilsImpl,						kPackageAndPreflightUIPrefix2 + 91)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileButtonObserverImpl,		kPackageAndPreflightUIPrefix2 + 92)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfilePopupMenuActionImpl,		kPackageAndPreflightUIPrefix2 + 93)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgCategoryNodeObserverImpl,		kPackageAndPreflightUIPrefix2 + 94)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgNameEBValidationImpl,			kPackageAndPreflightUIPrefix2 + 95)

DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleGenericWidgetObserverImpl,		kPackageAndPreflightUIPrefix2 + 96)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataCheckboxWidgetHandlerImpl,	kPackageAndPreflightUIPrefix2 + 97)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataEditboxWidgetHandlerImpl,	kPackageAndPreflightUIPrefix2 + 98)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataDropdownWidgetHandlerImpl,	kPackageAndPreflightUIPrefix2 + 99)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleNodeViewImpl,					kPackageAndPreflightUIPrefix2 + 100)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgSizeBoxEHImpl,						kPackageAndPreflightUIPrefix2 + 101)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataContainerObserverImpl,		kPackageAndPreflightUIPrefix2 + 102)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataTBLRWidgetHandlerImpl,		kPackageAndPreflightUIPrefix2 + 103)
DECLARE_PMID(kImplementationIDSpace, kPreflightDlgProfileManagerImpl,				kPackageAndPreflightUIPrefix2 + 104)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataStaticTextWidgetHandlerImpl,kPackageAndPreflightUIPrefix2 + 105)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRulesTVWidgetViewImpl,				kPackageAndPreflightUIPrefix2 + 106)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRulesTVScrollerWidgetViewImpl,		kPackageAndPreflightUIPrefix2 + 107)

//	gap
DECLARE_PMID(kImplementationIDSpace, kPreflightOptionsDlgControllerImpl,		kPackageAndPreflightUIPrefix2 + 110)
DECLARE_PMID(kImplementationIDSpace, kPreflightOptionsDlgObserverImpl,			kPackageAndPreflightUIPrefix2 + 111)
DECLARE_PMID(kImplementationIDSpace, kPreflightOptionsDlgUtilsImpl,				kPackageAndPreflightUIPrefix2 + 112)

DECLARE_PMID(kImplementationIDSpace, kPreflightUIPanelMenuActionImpl,			kPackageAndPreflightUIPrefix2 + 120)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIPanelViewImpl,					kPackageAndPreflightUIPrefix2 + 121)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIProfileSelectorObserverImpl,	kPackageAndPreflightUIPrefix2 + 122)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoExpanderObserverImpl,		kPackageAndPreflightUIPrefix2 + 123)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorsTVAdapterImpl,			kPackageAndPreflightUIPrefix2 + 124)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorsTVWidgetMgrImpl,			kPackageAndPreflightUIPrefix2 + 125)
DECLARE_PMID(kImplementationIDSpace, kPrivatePreflightUIUtilsImpl,				kPackageAndPreflightUIPrefix2 + 126)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIPanelObserverImpl,				kPackageAndPreflightUIPrefix2 + 127)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIPanelDataImpl,					kPackageAndPreflightUIPrefix2 + 128)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorsTVObserverImpl,			kPackageAndPreflightUIPrefix2 + 129)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIPanelPrefsImpl,				kPackageAndPreflightUIPrefix2 + 130)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorInfoServiceImpl,			kPackageAndPreflightUIPrefix2 + 131)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorInfoProviderImpl,			kPackageAndPreflightUIPrefix2 + 132)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorPageInfoProviderImpl,		kPackageAndPreflightUIPrefix2 + 133)
DECLARE_PMID(kImplementationIDSpace, kPreflightUISelectItBtnObsImpl,			kPackageAndPreflightUIPrefix2 + 134)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorNodeEHImpl,				kPackageAndPreflightUIPrefix2 + 135)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoBoxObserverImpl,			kPackageAndPreflightUIPrefix2 + 136)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIGotoButtonObserverImpl,		kPackageAndPreflightUIPrefix2 + 137)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIProfileNameObserverImpl,		kPackageAndPreflightUIPrefix2 + 138)
//gap
DECLARE_PMID(kImplementationIDSpace, kPreflightUIOnOffButtonObserverImpl,		kPackageAndPreflightUIPrefix2 + 139)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIEmbedButtonObserverImpl,		kPackageAndPreflightUIPrefix2 + 140)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIScopePanelObserverImpl,		kPackageAndPreflightUIPrefix2 + 141)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIProfileNameNoShadowDDLViewImpl,		kPackageAndPreflightUIPrefix2 + 142)
//gap

DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorPageInfoEHImpl,			kPackageAndPreflightUIPrefix2 + 143)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIPointyHandCursorProviderImpl,	kPackageAndPreflightUIPrefix2 + 144)

DECLARE_PMID(kImplementationIDSpace, kPreflightUIAppMenuImpl,					kPackageAndPreflightUIPrefix2 + 145)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIBookMenuImpl,					kPackageAndPreflightUIPrefix2 + 146)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookOptionsDCImpl,				kPackageAndPreflightUIPrefix2 + 147)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookOptionsDOImpl,				kPackageAndPreflightUIPrefix2 + 148)

DECLARE_PMID(kImplementationIDSpace, kPreflightUIMenuActionFilterImpl,			kPackageAndPreflightUIPrefix2 + 149)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIUtilsImpl,						kPackageAndPreflightUIPrefix2 + 150)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIStatusMenuComponentImpl,		kPackageAndPreflightUIPrefix2 + 151)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIStatusWidgetObserverImpl,		kPackageAndPreflightUIPrefix2 + 152)

DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoBoxTextViewImpl,			kPackageAndPreflightUIPrefix2 + 153)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoBoxLineBreakerImpl,		kPackageAndPreflightUIPrefix2 + 154)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoBoxLineBreakDataImpl,		kPackageAndPreflightUIPrefix2 + 155)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorNodeViewImpl,				kPackageAndPreflightUIPrefix2 + 156)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIInfoBoxBorderPanelViewImpl,	kPackageAndPreflightUIPrefix2 + 157)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorHeaderPanelEHImpl,		kPackageAndPreflightUIPrefix2 + 158)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorsTVMgrImpl,				kPackageAndPreflightUIPrefix2 + 159)

DECLARE_PMID(kImplementationIDSpace, kPreflightUIErrorNodeTipsImpl,				kPackageAndPreflightUIPrefix2 + 160)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIStatusWidgetTipsImpl,			kPackageAndPreflightUIPrefix2 + 161)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIStatusWidgetEHImpl,			kPackageAndPreflightUIPrefix2 + 162)

DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleDataNodeHandlerImpl,		kPackageAndPreflightUIPrefix2 + 163)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgDupBasicDlgControllerImpl,		kPackageAndPreflightUIPrefix2 + 164)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListStaticTextViewImpl,	kPackageAndPreflightUIPrefix2 + 165)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIGlobalObserverImpl,			kPackageAndPreflightUIPrefix2 + 166)
DECLARE_PMID(kImplementationIDSpace, kPreflightUIGotoButtonTipsImpl,			kPackageAndPreflightUIPrefix2 + 167)
//gap
DECLARE_PMID(kImplementationIDSpace, kPreflightUITVWidgetViewImpl,				kPackageAndPreflightUIPrefix2 + 169)
DECLARE_PMID(kImplementationIDSpace, kPreflightUITVScrollerWidgetViewImpl,		kPackageAndPreflightUIPrefix2 + 170)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgRuleCheckboxEHImpl,				kPackageAndPreflightUIPrefix2 + 171)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgCheckboxTriStateControlDataImpl,kPackageAndPreflightUIPrefix2 + 172)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineEditSingleClickEHImpl,	kPackageAndPreflightUIPrefix2 + 173)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgILEMultiLineWidgetAttrImpl,		kPackageAndPreflightUIPrefix2 + 174)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineEditControllerImpl,		kPackageAndPreflightUIPrefix2 + 175)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineEditViewImpl,				kPackageAndPreflightUIPrefix2 + 176)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgILEDropdownWidgetAttrImpl,		kPackageAndPreflightUIPrefix2 + 177)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgILEEditWidgetAttrImpl,			kPackageAndPreflightUIPrefix2 + 178)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineStaticTextViewImpl,		kPackageAndPreflightUIPrefix2 + 179)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineDropDownStaticTextViewImpl,kPackageAndPreflightUIPrefix2 + 180)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgInLineEditEventMonitorEHImpl,	kPackageAndPreflightUIPrefix2 + 181)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListWidgetViewImpl,		kPackageAndPreflightUIPrefix2 + 182)
DECLARE_PMID(kImplementationIDSpace, kProfileDlgProfileListScrollerWidgetViewImpl,kPackageAndPreflightUIPrefix2 + 183)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleUIParamTableDrivenImpl,		kPackageAndPreflightUIPrefix2 + 184)

// <Widget ID>
// Begin Obsolete Preflight UI Widget IDs
DECLARE_PMID(kWidgetIDSpace, kS4SPSelectDialogPopupGroupWidgetID, kPackageAndPreflightUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPreflightMasterWidgetID, kPackageAndPreflightUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPreflightMasterPackageButtonID, kPackageAndPreflightUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPreflightMasterReportButtonID, kPackageAndPreflightUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPreflightSummaryWidgetID, kPackageAndPreflightUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPreflightFontWidgetID, kPackageAndPreflightUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPreflightLinkWidgetID, kPackageAndPreflightUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPreflightInkWidgetID, kPackageAndPreflightUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPreflightSettingsWidgetID, kPackageAndPreflightUIPrefix + 9)

//Summary Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kSummaryAmountTextWidgetID, kPackageAndPreflightUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kSummaryFontStatusIconWidgetID, kPackageAndPreflightUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSummaryFontStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSummaryFontStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSummaryFontStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatusIconWidgetID, kPackageAndPreflightUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kSummaryInkStatusIconWidgetID, kPackageAndPreflightUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSummaryInkStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kSummaryInkStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kSummaryInkStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kSummaryShowDataCheckBoxWidgetID, kPackageAndPreflightUIPrefix + 23)

//Font Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kFontCurrentGroupTitleWidgetID, kPackageAndPreflightUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFontFileNameTextWidgetID, kPackageAndPreflightUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kFontFullNameTextWidgetID, kPackageAndPreflightUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kFontFirstUsedOnPageTextWidgetID, kPackageAndPreflightUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kFontStatusIconWidgetID, kPackageAndPreflightUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kFontStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kFontStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kFontStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kFontListWidgetID, kPackageAndPreflightUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kFontListTitleWidgetID, kPackageAndPreflightUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kFontListScrollBarWidgetID, kPackageAndPreflightUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kFontListSubViewWidgetID, kPackageAndPreflightUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kFontShowProblemsCheckBoxWidgetID, kPackageAndPreflightUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kFontCurrentGroupWidgetID, kPackageAndPreflightUIPrefix + 37)

//Link Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kLinkCurrentGroupTitleWidgetID, kPackageAndPreflightUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kLinkFileNameTextWidgetID, kPackageAndPreflightUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kLinkUpdatedTextWidgetID, kPackageAndPreflightUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kLinkFullNameTextWidgetID, kPackageAndPreflightUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kLinkLastModifiedTextWidgetID, kPackageAndPreflightUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kLinkStatusIconWidgetID, kPackageAndPreflightUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kLinkStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kLinkStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kLinkStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kLinkListWidgetID, kPackageAndPreflightUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kLinkListTitleWidgetID, kPackageAndPreflightUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kLinkListScrollBarWidgetID, kPackageAndPreflightUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kLinkListSubViewWidgetID, kPackageAndPreflightUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kLinkShowProblemsCheckBoxWidgetID, kPackageAndPreflightUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kLinkUpdateButtonWidgetID, kPackageAndPreflightUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kLinkRepairAllButtonWidgetID, kPackageAndPreflightUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kLinkCurrentGroupWidgetID, kPackageAndPreflightUIPrefix + 54)

//Ink Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kInkStatusIconWidgetID, kPackageAndPreflightUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kInkStatus1TextWidgetID, kPackageAndPreflightUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kInkStatus2TextWidgetID, kPackageAndPreflightUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kInkStatus3TextWidgetID, kPackageAndPreflightUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kInkListWidgetID, kPackageAndPreflightUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kInkListTitleWidgetID, kPackageAndPreflightUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kInkListScrollBarWidgetID, kPackageAndPreflightUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kInkListSubViewWidgetID, kPackageAndPreflightUIPrefix + 62)

//Print Settings Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kSettingsListWidgetID, kPackageAndPreflightUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kSettingsListTitleWidgetID, kPackageAndPreflightUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kSettingsListScrollBarWidgetID, kPackageAndPreflightUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kSettingsListSubViewWidgetID, kPackageAndPreflightUIPrefix + 66)

//Job Ticket Panel Widget IDs
DECLARE_PMID(kWidgetIDSpace, kJobTicketFileNameWidgetID, kPackageAndPreflightUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kJobTicketContactWidgetID, kPackageAndPreflightUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kJobTicketCompanyWidgetID, kPackageAndPreflightUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kJobTicketAddressWidgetID, kPackageAndPreflightUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kJobTicketAddress2WidgetID, kPackageAndPreflightUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kJobTicketAddress3WidgetID, kPackageAndPreflightUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kJobTicketAddress4WidgetID, kPackageAndPreflightUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kJobTicketPhoneWidgetID, kPackageAndPreflightUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kJobTicketFaxWidgetID, kPackageAndPreflightUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kJobTicketEmailWidgetID, kPackageAndPreflightUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kJobTicketInstructionsWidgetID, kPackageAndPreflightUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kJobTicketInstructions2WidgetID, kPackageAndPreflightUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kJobTicketInstructions3WidgetID, kPackageAndPreflightUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kJobTicketInstructions4WidgetID, kPackageAndPreflightUIPrefix + 80)

DECLARE_PMID(kWidgetIDSpace, kPreflightTextWidgetId, kPackageAndPreflightUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kS4SPGroup1WidgetId, kPackageAndPreflightUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kS4SPFilenameTextWidget, kPackageAndPreflightUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kFullnameTextWidget, kPackageAndPreflightUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kFirstUsedOnPageTextWidgetId, kPackageAndPreflightUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kLinkUpdatedTextWidgetId, kPackageAndPreflightUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kFileLastModifiedTextWidgetId, kPackageAndPreflightUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kS4SPCompleteNameTextWidgetId, kPackageAndPreflightUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kJobTicketDialogWidgetId, kPackageAndPreflightUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kContactTextWidgetId, kPackageAndPreflightUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kCompanyTextWidgetId, kPackageAndPreflightUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kAddressTextWidgetId, kPackageAndPreflightUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kAddress2TextWidgetId, kPackageAndPreflightUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kAddress3TextWidgetId, kPackageAndPreflightUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kAddress4TextWidgetId, kPackageAndPreflightUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kPhoneTextWidgetId, kPackageAndPreflightUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kFaxTextWidgetId, kPackageAndPreflightUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kEmailTextWidgetId, kPackageAndPreflightUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kInstructionsTextWidgetId, kPackageAndPreflightUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kInstructions2TextWidgetId, kPackageAndPreflightUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kInstructions3TextWidgetId, kPackageAndPreflightUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kInstructions4TextWidgetId, kPackageAndPreflightUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kS4SPAlertDialogWidgetId, kPackageAndPreflightUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kBigNoteIconWidgetId, kPackageAndPreflightUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kFontAlertTextWidgetId, kPackageAndPreflightUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kInstructions1TextWidgetId, kPackageAndPreflightUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kS4SPAlert1DialogWidgetId, kPackageAndPreflightUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kLargeWarningSignWidgetId, kPackageAndPreflightUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kS4SPStaticTextWidgetId, kPackageAndPreflightUIPrefix + 109)

DECLARE_PMID(kWidgetIDSpace, kPackageAndPreflightUIPrefixWidgetID0, kPackageAndPreflightUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kS4SPFindFontButtonWidgetID, kPackageAndPreflightUIPrefix + 111)

// for plugin panel
DECLARE_PMID(kWidgetIDSpace, kPreflightPluginWidgetID, kPackageAndPreflightUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kS4SPPluginListWidgetID, kPackageAndPreflightUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kPluginListTitleWidgetID, kPackageAndPreflightUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kPluginListScrollBarWidgetID, kPackageAndPreflightUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kPluginListSubViewWidgetID, kPackageAndPreflightUIPrefix + 116)

DECLARE_PMID(kWidgetIDSpace, kSummaryExternalPluginTextWidgetID, kPackageAndPreflightUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kSummaryNonOpaqueObjectsTextWidgetID, kPackageAndPreflightUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kSummaryNumDocumentsTextWidgetID, kPackageAndPreflightUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kSummaryPaginationOptionsTextWidgetID, kPackageAndPreflightUIPrefix + 120)

//Link Panel Preflight Widget IDs
DECLARE_PMID(kWidgetIDSpace, kPreflightImageActualResTextWidgetId,		kPackageAndPreflightUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kPreflightImageEffectiveResTextWidgetId,	kPackageAndPreflightUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kPreflightImageActualPPIValueWidgetID,		kPackageAndPreflightUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kPreflightImageEffectivePPIValueWidgetID,	kPackageAndPreflightUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kS4SPLayerOverridesTextWidgetId,	kPackageAndPreflightUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kLayerOverridesTextWidgetId,	kPackageAndPreflightUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kCannotUpdateSecondaryLinksWarningID, kPackageAndPreflightUIPrefix + 127) // for a Don't Show Again alert
// End Obsolete Preflight UI Widget IDs

DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatus4TextWidgetID,			kPackageAndPreflightUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kLinkStatus4TextWidgetID,					kPackageAndPreflightUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kCloudTextAssetUnlinkMessageWidgetID,		kPackageAndPreflightUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kSummaryLinkStatusInfoIconWidgetID,		kPackageAndPreflightUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kLinkStatusInfoIconWidgetID,				kPackageAndPreflightUIPrefix + 132)

//______________________________________________________________________
//	Basil Preflight UI
//______________________________________________________________________
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericPanel1WID,			kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericPanel2WID,			kPackageAndPreflightUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericPanel3WID,			kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericPanel4WID,			kPackageAndPreflightUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericPanel5WID,			kPackageAndPreflightUIPrefix2 + 5)

//	Preflight Profile dialog
DECLARE_PMID(kWidgetIDSpace, kPreflightProfileDialogWID,			kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgEmbedStatusPanelWID,		kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgEmbedProfileTextLabelWID,	kPackageAndPreflightUIPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgEmbedProfileTextWID,		kPackageAndPreflightUIPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgSaveAsButtonWID,			kPackageAndPreflightUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgUpdateButtonWID,			kPackageAndPreflightUIPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgProfilePanelWID,			kPackageAndPreflightUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgProfileListWID,				kPackageAndPreflightUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgProfileButtonPanelWID,		kPackageAndPreflightUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRulesPanelWID,				kPackageAndPreflightUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgNewProfileButtonWID,		kPackageAndPreflightUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgDeleteProfileButtonWID,		kPackageAndPreflightUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgProfileGearButtonWID,		kPackageAndPreflightUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRulesTreeViewWID,			kPackageAndPreflightUIPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleBaseCategoryNodeWID,	kPackageAndPreflightUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCategoryNodeWID,		kPackageAndPreflightUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCategoryNameWID,		kPackageAndPreflightUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGeneralPanelNodeWID,	kPackageAndPreflightUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgNameLabelWID,				kPackageAndPreflightUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgDescriptionLabelWID,		kPackageAndPreflightUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgNameWidgetID,				kPackageAndPreflightUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgDescriptionTextWID,			kPackageAndPreflightUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgDescriptionScrollWID,		kPackageAndPreflightUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCategoryCheckBoxWID,	kPackageAndPreflightUIPrefix2 + 29)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgIconPanel1WID,				kPackageAndPreflightUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgIconPanel2WID,				kPackageAndPreflightUIPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgIconPanel3WID,				kPackageAndPreflightUIPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCheckBoxWID,			kPackageAndPreflightUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleNameWID,				kPackageAndPreflightUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericPanelWID,		kPackageAndPreflightUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleContainerSpacerWID,		kPackageAndPreflightUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataContainerPanelWID,	kPackageAndPreflightUIPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleLinksRulePanelWID,		kPackageAndPreflightUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleMissingLinkCheckBoxWID,	kPackageAndPreflightUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleModifiedLinkCheckBoxWID,kPackageAndPreflightUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCheckboxContainerPanelWID,kPackageAndPreflightUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericCheckboxPanelWID,kPackageAndPreflightUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericCheckboxWID,		kPackageAndPreflightUIPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericCheckboxLabelWID,kPackageAndPreflightUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCheckboxPanelWID,		kPackageAndPreflightUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleIndentSpaceHelperWID,	kPackageAndPreflightUIPrefix2 + 46)

DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleEditBoxContainerPanelWID,	kPackageAndPreflightUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericEditboxPanelWID,	kPackageAndPreflightUIPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericEditboxLabelWID,	kPackageAndPreflightUIPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericEditboxWID,		kPackageAndPreflightUIPrefix2 + 50)

DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericNudgeWID,		kPackageAndPreflightUIPrefix2 + 51)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataXMeasureWID,		kPackageAndPreflightUIPrefix2 + 52)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataYMeasureWID,		kPackageAndPreflightUIPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataTextMeasureWID,		kPackageAndPreflightUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataTextSizeWID,		kPackageAndPreflightUIPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataLineWtMeasureWID,	kPackageAndPreflightUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataPercentageWID,		kPackageAndPreflightUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataGenericRealEditWID,	kPackageAndPreflightUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataGenericIntEditWID,	kPackageAndPreflightUIPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataGenericTextEditWID,	kPackageAndPreflightUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericDropdownPanelWID,kPackageAndPreflightUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericDropdownWID,		kPackageAndPreflightUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericDropdownLabelWID,kPackageAndPreflightUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataChildContainerPanelWID,kPackageAndPreflightUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericEditboxSuffixWID,kPackageAndPreflightUIPrefix2 + 65)

DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleNodeWID,				kPackageAndPreflightUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericTBLRWID,			kPackageAndPreflightUIPrefix2 + 67)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericTBLRLabelWID,	kPackageAndPreflightUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericTBLRConstrainPanelWID,kPackageAndPreflightUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleGenericTBLRChainIconWID,kPackageAndPreflightUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleSimpleDropDownPanelWID,	kPackageAndPreflightUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleSimpleDropdownWID,		kPackageAndPreflightUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleSimpleDropdownLabelWID,	kPackageAndPreflightUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleCheckboxGroupPanelWID,	kPackageAndPreflightUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgNameEmbeddedStatusWidgetID,	kPackageAndPreflightUIPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace, ProfileDlgDuplicateBasicDlgWID,		kPackageAndPreflightUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataStaticTextWID,		kPackageAndPreflightUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleDataStaticTextPanelWID,	kPackageAndPreflightUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleStaticNudgeWID,			kPackageAndPreflightUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleNoStaticNudgeWID,		kPackageAndPreflightUIPrefix2 + 80)	//	This is a fax WID to indicate we don't need to draw static nudge control

//	It is very important that this widget ID is the last widget ID in the range for profile dialog's
//	tree view widget.
//	The tree view manager uses the node widget ID to determine if it can reuse, cache, or dispose
//	of node widget. Our rule node widgets are all unique; so their widget IDs must also be unique.
//	Since we dynamically build our rule node widgets from this generic widget, we are 
//	going to dynamically sets the rule node widget ID by adding an index to this base WID.
//	We don't want our range to overlap with any other widget ID used by the dialog. But it can
//	overlap with widget IDs outside of the dialog.
DECLARE_PMID(kWidgetIDSpace, kProfileDlgRuleContainerNodeWID,		kPackageAndPreflightUIPrefix2 + 100)

//	Preflight UI Panel

DECLARE_PMID(kWidgetIDSpace, kPreflightUIPanelWID,					kPackageAndPreflightUIPrefix2 + 101)
DECLARE_PMID(kWidgetIDSpace, kPreflightUITopPanelWID,				kPackageAndPreflightUIPrefix2 + 102)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorsIconWID,				kPackageAndPreflightUIPrefix2 + 103)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorsTextWID,				kPackageAndPreflightUIPrefix2 + 104)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIProfileSelectorLabelWID,	kPackageAndPreflightUIPrefix2 + 105)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIProfileSelectorWID,		kPackageAndPreflightUIPrefix2 + 106)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorPanelWidgetID,		kPackageAndPreflightUIPrefix2 + 107)
DECLARE_PMID(kWidgetIDSpace, kPreflightUITreeViewPanelWID,			kPackageAndPreflightUIPrefix2 + 108)
DECLARE_PMID(kWidgetIDSpace, kPreflightUITreeViewWidgetID,			kPackageAndPreflightUIPrefix2 + 109)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoExpanderPanelWID,		kPackageAndPreflightUIPrefix2 + 110)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoExpanderTitleTextWID,	kPackageAndPreflightUIPrefix2 + 111)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoExpanderIconWID,		kPackageAndPreflightUIPrefix2 + 112)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoTextPanelWID,			kPackageAndPreflightUIPrefix2 + 113)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoTextWID,				kPackageAndPreflightUIPrefix2 + 114)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIInfoScrollWID,				kPackageAndPreflightUIPrefix2 + 115)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorCategoryNodeWID,		kPackageAndPreflightUIPrefix2 + 116)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorCategoryNameWID,		kPackageAndPreflightUIPrefix2 + 117)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorNodeWID,				kPackageAndPreflightUIPrefix2 + 119)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorNodeFixupWID,			kPackageAndPreflightUIPrefix2 + 120)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorNodeTextWID,			kPackageAndPreflightUIPrefix2 + 121)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorNodePageWID,			kPackageAndPreflightUIPrefix2 + 122)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorRuleNodeWID,			kPackageAndPreflightUIPrefix2 + 123)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIErrorHeaderRowWidgetID,	kPackageAndPreflightUIPrefix2 + 124)
DECLARE_PMID(kWidgetIDSpace, kPreflightNavigatorPanelWID,			kPackageAndPreflightUIPrefix2 + 125)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIGotoNextButtonWID,			kPackageAndPreflightUIPrefix2 + 126)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIGotoPrevButtonWID,			kPackageAndPreflightUIPrefix2 + 127)

DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusPanelWID,			kPackageAndPreflightUIPrefix2 + 128)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPanelSeparatorWID,			kPackageAndPreflightUIPrefix2 + 129)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIEmbedButtonWID,			kPackageAndPreflightUIPrefix2 + 130)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPreflightOnOffWID,			kPackageAndPreflightUIPrefix2 + 131)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIScopePanelWID,				kPackageAndPreflightUIPrefix2 + 132)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPageAllRadioWID,			kPackageAndPreflightUIPrefix2 + 133)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPageRangePanelWID,			kPackageAndPreflightUIPrefix2 + 134)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPageRangeRadioWID,			kPackageAndPreflightUIPrefix2 + 135)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPageRangeEditWID,			kPackageAndPreflightUIPrefix2 + 136)

DECLARE_PMID(kWidgetIDSpace, kPreflightOptionsDialogWidgetID,			kPackageAndPreflightUIPrefix2 + 137)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgScopeGroupWID,				kPackageAndPreflightUIPrefix2 + 138)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgScopeGroupTitleWID,		kPackageAndPreflightUIPrefix2 + 139)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgScopeGroupPageTitleWID,	kPackageAndPreflightUIPrefix2 + 140)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptScopePageAllRadioWID,			kPackageAndPreflightUIPrefix2 + 141)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptScopePageRangeRadioWID,		kPackageAndPreflightUIPrefix2 + 142)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptScopePageRangeEditWID,		kPackageAndPreflightUIPrefix2 + 143)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgIncludeGroupWID,			kPackageAndPreflightUIPrefix2 + 144)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgIncludeGroupTitleWID,		kPackageAndPreflightUIPrefix2 + 145)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptIncludeLayersLabelWID,		kPackageAndPreflightUIPrefix2 + 146)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptIncludeLayersDropdownWID,		kPackageAndPreflightUIPrefix2 + 147)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptIncludeObjsOnPBCheckboxWID,	kPackageAndPreflightUIPrefix2 + 148)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptNonPrintingsCheckboxWID,		kPackageAndPreflightUIPrefix2 + 149)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgProfileGroupWID,			kPackageAndPreflightUIPrefix2 + 150)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgProfileGroupTitleWID,		kPackageAndPreflightUIPrefix2 + 151)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptDlgProfileClusterWID,			kPackageAndPreflightUIPrefix2 + 152)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptUseEmbedProfileRadioWID,		kPackageAndPreflightUIPrefix2 + 153)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptUseProfileRadioWID,			kPackageAndPreflightUIPrefix2 + 154)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptProfileListDropdownWID,		kPackageAndPreflightUIPrefix2 + 155)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptScopePageRangePanelWID,		kPackageAndPreflightUIPrefix2 + 156)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptWorkingProfileTitleWID,		kPackageAndPreflightUIPrefix2 + 157)
DECLARE_PMID(kWidgetIDSpace, kPreflightOptEmbedInNewDocCheckboxWID,		kPackageAndPreflightUIPrefix2 + 158)

// Preflight book options dialog. Note that it reuses most of the widgets from the preflight options 
// dialog since they are very similar.

DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptionsDialogWidgetID,		kPackageAndPreflightUIPrefix2 + 159)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptWhichDocsPanelWID,		kPackageAndPreflightUIPrefix2 + 160)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptWhichDocsTitleWID,		kPackageAndPreflightUIPrefix2 + 161)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptAllDocsRadioWID,			kPackageAndPreflightUIPrefix2 + 162)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptSelDocsRadioWID,			kPackageAndPreflightUIPrefix2 + 163)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptWPInfoTextWID,			kPackageAndPreflightUIPrefix2 + 164)
DECLARE_PMID(kWidgetIDSpace, kPreflightBookOptReportCheckBoxWID,		kPackageAndPreflightUIPrefix2 + 165)

DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusWidgetPanelWID,			kPackageAndPreflightUIPrefix2 + 166)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusWidgetWID,				kPackageAndPreflightUIPrefix2 + 167)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusStateIconWID,			kPackageAndPreflightUIPrefix2 + 168)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusTextWID,					kPackageAndPreflightUIPrefix2 + 169)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIStatusPopupMenuWID,			kPackageAndPreflightUIPrefix2 + 170)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPreflightOnWID,				kPackageAndPreflightUIPrefix2 + 171)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIPreflightOffWID,				kPackageAndPreflightUIPrefix2 + 172)
DECLARE_PMID(kWidgetIDSpace, kPreflightUIScopeTitleWID,					kPackageAndPreflightUIPrefix2 + 173)

DECLARE_PMID(kWidgetIDSpace, kPreflightDlgGenericRulesPanel3WID,		kPackageAndPreflightUIPrefix2 + 174)
DECLARE_PMID(kWidgetIDSpace, kPreflightDlgRulesProfileNameGroupPanel3WID,kPackageAndPreflightUIPrefix2 + 175)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgDescriptionInLineTextWID,		kPackageAndPreflightUIPrefix2 + 176)
DECLARE_PMID(kWidgetIDSpace, kProfileDlgInlineEditIconWidtetID,			kPackageAndPreflightUIPrefix2 + 177)

DECLARE_PMID(kWidgetIDSpace, kPreflightUIProfileNameWID,					kPackageAndPreflightUIPrefix2 + 178)
DECLARE_PMID(kWidgetIDSpace, kDialogGroupPanelContainerWidgetID, 		kPackageAndPreflightUIPrefix2 + 179)

// Added check box for the instruction.txt pref.
DECLARE_PMID(kWidgetIDSpace, kS4SPPackageCreateInstructionsCheckBoxWID, kPackageAndPreflightUIPrefix2 + 180)


//______________________________________________________________________
// Old <Action ID>
//______________________________________________________________________
DECLARE_PMID(kActionIDSpace, kPreflightActionID, kPackageAndPreflightUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPackageActionID, kPackageAndPreflightUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPreflightBookPopupMenuActionID, kPackageAndPreflightUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPackageBookPopupMenuActionID, kPackageAndPreflightUIPrefix + 4)

//______________________________________________________________________
//	Basil Preflight UI
//______________________________________________________________________
DECLARE_PMID(kActionIDSpace, kPreflightActionID_Panel,				kPackageAndPreflightUIPrefix2 + 1)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_Options,			kPackageAndPreflightUIPrefix2 + 2)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ManageProfile,		kPackageAndPreflightUIPrefix2 + 3)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_Separator1,			kPackageAndPreflightUIPrefix2 + 4)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_SaveReport,			kPackageAndPreflightUIPrefix2 + 5)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_DocSummary,			kPackageAndPreflightUIPrefix2 + 6)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_Separator2,			kPackageAndPreflightUIPrefix2 + 7)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_EmbedUnembed,		kPackageAndPreflightUIPrefix2 + 8)
//DECLARE_PMID(kActionIDSpace, kPreflightActionID_StopResumePreflight,kPackageAndPreflightUIPrefix2 + 10)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_GlobalOff,			kPackageAndPreflightUIPrefix2 + 11)

DECLARE_PMID(kActionIDSpace, kPreflightActionID_ButtonPopup_Load,	kPackageAndPreflightUIPrefix2 + 12)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ButtonPopup_Reveal,	kPackageAndPreflightUIPrefix2 + 13)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ButtonPopup_EmbedUnembed,kPackageAndPreflightUIPrefix2 + 14)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ButtonPopup_Export,kPackageAndPreflightUIPrefix2 + 15)

DECLARE_PMID(kActionIDSpace, kPreflightActionID_Panel2,	kPackageAndPreflightUIPrefix2 + 16)
DECLARE_PMID(kActionIDSpace, kPreflightUIStatusMenuActionID_Separator,	kPackageAndPreflightUIPrefix2 + 17)
DECLARE_PMID(kActionIDSpace, kPreflightUIStatusMenuActionID_DocPreflightOnOff,	kPackageAndPreflightUIPrefix2 + 18)
DECLARE_PMID(kActionIDSpace, kPreflightUIStatusMenuActionID_DisableAllPreflights,kPackageAndPreflightUIPrefix2 + 19)

DECLARE_PMID(kActionIDSpace, kPreflightActionID_ErrorRowsPrefs1,kPackageAndPreflightUIPrefix2 + 20)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ErrorRowsPrefs2,kPackageAndPreflightUIPrefix2 + 21)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ErrorRowsPrefs3,kPackageAndPreflightUIPrefix2 + 22)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_ErrorRowsPrefsNoLimit,kPackageAndPreflightUIPrefix2 + 23)
DECLARE_PMID(kActionIDSpace, kPreflightActionID_Separator3,kPackageAndPreflightUIPrefix2 + 24)

//______________________________________________________________________
// Basil Preflight <Error ID>
//______________________________________________________________________


//	Basil Preflight Tree node ID
#define kPreflightUIErrorNodeID	kPackageAndPreflightUIPrefix2 + 1	
#define kProfileDlgRuleNodeID	kPackageAndPreflightUIPrefix2 + 2	
#define kProfileDlgStringNodeID	kPackageAndPreflightUIPrefix2 + 3	

//	Basil Preflight Tree style ID
#define kProfileDlgRuleBaseCategoryWidgetStyleID	kPackageAndPreflightUIPrefix2 + 1	
#define kProfileDlgRuleCategoryWidgetStyleID		kPackageAndPreflightUIPrefix2 + 2	
#define kProfileDlgRuleGeneralPanelWidgetStyleID	kPackageAndPreflightUIPrefix2 + 3	
#define kProfileDlgRuleContainerWidgetStyleID		kPackageAndPreflightUIPrefix2 + 4	

// <End IDC>


#endif // __PackageAndPreflightUIID__

