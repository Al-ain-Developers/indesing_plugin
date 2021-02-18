//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/DictEditorID.h $
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

#ifndef __DictEditorID__
#define __DictEditorID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//---------------------------------------------------------------
// DictEditor Prefix
//---------------------------------------------------------------

// Doublecheck kDictEditorPrefix with AdobePrefix.h, 0x4300 Hex == 17152 Dec
#define kDictEditorPrefix	RezLong(0x4300)

// Converters

// Hotaka
#define	kDictEditorNumberChange					kHotakaInitialMinorFormatNumber
#define kDictEditorConvertMyDataChange			RezLong(58)
#define kDictEditorLastHotakaFormatChange		kDictEditorConvertMyDataChange


// PluginID
#define kDictEditorPluginName 				"Dictionary Editor Dialog"
DECLARE_PMID(kPlugInIDSpace, kDictEditorPluginID, kDictEditorPrefix + 1)

// <Class ID>
// Plugin: 0 to 9
DECLARE_PMID(kClassIDSpace, kDictEditorBoss, kDictEditorPrefix +  1)
DECLARE_PMID(kClassIDSpace, kDictEditorRegisterBoss, kDictEditorPrefix +  2)
// gap
DECLARE_PMID(kClassIDSpace, kDictEditorMenuComponentBoss, kDictEditorPrefix +  4)
// gap
DECLARE_PMID(kClassIDSpace, kOpenDictEditorCmdBoss, kDictEditorPrefix +  6)
//gap
// Observer: 10 to 39
DECLARE_PMID(kClassIDSpace, kDictWordObserverBoss, kDictEditorPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDictHyphListObserverBoss, kDictEditorPrefix + 11)
DECLARE_PMID(kClassIDSpace, kDictRemovedListObserverBoss, kDictEditorPrefix + 12)
DECLARE_PMID(kClassIDSpace, kDictBreaksObserverBoss, kDictEditorPrefix + 13)
DECLARE_PMID(kClassIDSpace, kDictHyphenateObserverBoss, kDictEditorPrefix + 14)
DECLARE_PMID(kClassIDSpace, kDictAddObserverBoss, kDictEditorPrefix + 15)
DECLARE_PMID(kClassIDSpace, kDictReplaceObserverBoss, kDictEditorPrefix + 16)
DECLARE_PMID(kClassIDSpace, kDictRemoveObserverBoss, kDictEditorPrefix + 17)
DECLARE_PMID(kClassIDSpace, kDictLanguageObserverBoss, kDictEditorPrefix + 18)
DECLARE_PMID(kClassIDSpace, kDictSelectableDialogBoss, kDictEditorPrefix + 19)
DECLARE_PMID(kClassIDSpace, kDictHyphListPanelBoss, kDictEditorPrefix + 20)
DECLARE_PMID(kClassIDSpace, kDictRemovedListPanelBoss, kDictEditorPrefix + 21)
DECLARE_PMID(kClassIDSpace, kDictRemoveWordObserverBoss, kDictEditorPrefix + 22)
DECLARE_PMID(kClassIDSpace, kDictPrefsBoss, kDictEditorPrefix + 23)
DECLARE_PMID(kClassIDSpace, kDictPrefsMenuComponentBoss, kDictEditorPrefix + 24)
DECLARE_PMID(kClassIDSpace, kDictHyphVendorBoss, kDictEditorPrefix + 25)
DECLARE_PMID(kClassIDSpace, kDictSpellVendorBoss, kDictEditorPrefix + 26)
DECLARE_PMID(kClassIDSpace, kDictTargetListBoss, kDictEditorPrefix + 27)
DECLARE_PMID(kClassIDSpace, kDictIgnoredListPanelBoss, kDictEditorPrefix + 28)
DECLARE_PMID(kClassIDSpace, kDictHyphSourceBoss, kDictEditorPrefix + 29)
DECLARE_PMID(kClassIDSpace, kDictImportObserverBoss, kDictEditorPrefix + 30)
DECLARE_PMID(kClassIDSpace, kDictExportObserverBoss, kDictEditorPrefix + 31)
DECLARE_PMID(kClassIDSpace, kDictIgnoredListObserverBoss, kDictEditorPrefix + 32)
DECLARE_PMID(kClassIDSpace, kDictIgnoreWordObserverBoss, kDictEditorPrefix + 33)
DECLARE_PMID(kClassIDSpace, kDictOrderListElementBoss, kDictEditorPrefix + 34)
DECLARE_PMID(kClassIDSpace, kDictOrderViewBoss, kDictEditorPrefix + 35)
//gap
DECLARE_PMID(kClassIDSpace, kDictCaseSensitiveObserverBoss, kDictEditorPrefix + 37)
DECLARE_PMID(kClassIDSpace, kDictListTypeObserverBoss, kDictEditorPrefix + 38)
DECLARE_PMID(kClassIDSpace, kDictStatTextObserverBoss, kDictEditorPrefix + 39)
DECLARE_PMID(kClassIDSpace, kDictThesVendorBoss, kDictEditorPrefix + 40)
//gap
DECLARE_PMID(kClassIDSpace, kDictDoubleQuotesBoss, kDictEditorPrefix + 48)
DECLARE_PMID(kClassIDSpace, kDictSingleQuotesBoss, kDictEditorPrefix + 49)
DECLARE_PMID(kClassIDSpace, kDictListBoxBoss, kDictEditorPrefix + 50)
DECLARE_PMID(kClassIDSpace, kDictAllLanguageObserverBoss, kDictEditorPrefix + 51)

DECLARE_PMID(kClassIDSpace, kDictOrderAddDictionaryButtonBoss, kDictEditorPrefix + 60)
DECLARE_PMID(kClassIDSpace, kDictOrderRemoveDictionaryButtonBoss, kDictEditorPrefix + 61)
DECLARE_PMID(kClassIDSpace, kDictOrderNewDictionaryButtonBoss, kDictEditorPrefix + 62)
DECLARE_PMID(kClassIDSpace, kDictOrderReloadDictionaryButtonBoss, kDictEditorPrefix + 63)
DECLARE_PMID(kClassIDSpace, kDictOrderRelinkDictionaryButtonBoss, kDictEditorPrefix + 64)

DECLARE_PMID(kClassIDSpace, kAddUserDictDialogBoss, kDictEditorPrefix + 70)

DECLARE_PMID(kClassIDSpace, kImportWordListFileDialogBoss, kDictEditorPrefix + 80)

DECLARE_PMID(kClassIDSpace, kDictOrderTreeViewWidgetBoss, kDictEditorPrefix + 100)
DECLARE_PMID(kClassIDSpace, kDictOrderTreeNodeWidgetBoss, kDictEditorPrefix + 101)
DECLARE_PMID(kClassIDSpace, kDictOrderTreeViewObserverBoss, kDictEditorPrefix + 102)
DECLARE_PMID(kClassIDSpace, kDictOrderDragDropDEHandlerBoss, kDictEditorPrefix + 103)

DECLARE_PMID(kClassIDSpace, kDictOrderIconSuiteWidgetBoss, kDictEditorPrefix + 110)

DECLARE_PMID(kClassIDSpace, kSetDictProviderUIPrefCmdBoss, kDictEditorPrefix + 120)
DECLARE_PMID(kClassIDSpace, kDudenAlertOpenDocResponderBoss, kDictEditorPrefix + 121)
DECLARE_PMID(kClassIDSpace, kSetDudenAlertShownCmdBoss, kDictEditorPrefix + 122)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kDictDialog, kDictEditorPrefix +  1)
DECLARE_PMID(kImplementationIDSpace, kDictEditorRegister, kDictEditorPrefix +  2)
// gap
DECLARE_PMID(kImplementationIDSpace, kDictEditorMenuComponent, kDictEditorPrefix +  4)
DECLARE_PMID(kImplementationIDSpace, kDictIgnoredListPanelRsrcData, kDictEditorPrefix +  5)
DECLARE_PMID(kImplementationIDSpace, kDictEditorRsrcData, kDictEditorPrefix +  6)
DECLARE_PMID(kImplementationIDSpace, kDictHyphListPanelRsrcData, kDictEditorPrefix +  7)
DECLARE_PMID(kImplementationIDSpace, kDictRemovedListPanelRsrcData, kDictEditorPrefix +  8)
DECLARE_PMID(kImplementationIDSpace, kOpenDictEditorCmd, kDictEditorPrefix +  9)

DECLARE_PMID(kImplementationIDSpace, kDictWordObserver, kDictEditorPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kDictHyphListObserver, kDictEditorPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDictRemovedListObserver, kDictEditorPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kDictBreaksObserver, kDictEditorPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDictHyphenateObserver, kDictEditorPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kDictAddObserver, kDictEditorPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDictReplaceObserver, kDictEditorPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kDictRemoveObserver, kDictEditorPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDictLanguageObserver, kDictEditorPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDictWordEventHandler, kDictEditorPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kDictPrefsPanelCreator, kDictEditorPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kDictPrefsMenuComponent, kDictEditorPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kDictHyphVendorObserver, kDictEditorPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDictSpellVendorObserver, kDictEditorPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDictListBoxEH, kDictEditorPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kDictWordEditboxScrapSuiteImpl, kDictEditorPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kDictTargetListObserverImpl, kDictEditorPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kDictListTypeObserverImpl, kDictEditorPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kDictHyphSourceObserver, kDictEditorPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDictPrefsDialogControllerImpl, kDictEditorPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kHyphenationExceptionsImpl_Obsolete, kDictEditorPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kDictImportObserverImpl, kDictEditorPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kDictExportObserverImpl, kDictEditorPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDictCaseSensitiveObserverImpl, kDictEditorPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kDictThesVendorObserver, kDictEditorPrefix + 34)
// gap
DECLARE_PMID(kImplementationIDSpace, kDictArabicSpellingModeObserverImpl, kDictEditorPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDictStatTextObserver, kDictEditorPrefix + 38)
// gap
DECLARE_PMID(kImplementationIDSpace, kImportWordListFileDialogImpl, kDictEditorPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kImportWordListFileOptionsImpl, kDictEditorPrefix + 41)
// gap
DECLARE_PMID(kImplementationIDSpace, kSessionHyphExceptionsPrefsImpl_Obsolete, kDictEditorPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDocHyphExceptionsPrefsImpl_Obsolete, kDictEditorPrefix + 51)
// gap
DECLARE_PMID(kImplementationIDSpace, kDictQuotesValidationImpl, kDictEditorPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kDictSingleQuotesObserverImpl, kDictEditorPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kDictDoubleQuotesObserverImpl, kDictEditorPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kDictQuotesObserverImpl, kDictEditorPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kDictEditorListBoxCtrlImpl, kDictEditorPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kDictRemoveWordEventHandlerImpl, kDictEditorPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kDictAllLanguageObserverImpl, kDictEditorPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kDictIgnoreWordEventHandlerImpl, kDictEditorPrefix + 62)

// gap
DECLARE_PMID(kImplementationIDSpace, kDictOrderViewImpl, kDictEditorPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kDictOrderListViewTipsImpl, kDictEditorPrefix + 71)
// gap

DECLARE_PMID(kImplementationIDSpace, kDictOrderAddDictionaryButtonObsvImpl, kDictEditorPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kDictOrderRemoveDictionaryButtonObsvImpl, kDictEditorPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kDictOrderNewDictionaryButtonObsvImpl, kDictEditorPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kDictOrderReloadDictionaryButtonObsvImpl, kDictEditorPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kDictOrderRelinkDictionaryButtonObsvImpl, kDictEditorPrefix + 84)

DECLARE_PMID(kImplementationIDSpace, kAddUserDictDialogImpl, kDictEditorPrefix + 90)

DECLARE_PMID(kImplementationIDSpace, kDictOrderTreeViewWidgetMgrImpl, kDictEditorPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kDictOrderTreeViewAdapterImpl, kDictEditorPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDictOrderTreeViewObserverImpl, kDictEditorPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kDictOrderTreeViewEHImpl, kDictEditorPrefix + 103)

DECLARE_PMID(kImplementationIDSpace, kDictOrderDDTargetImpl, kDictEditorPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kDictOrderNodeDDSourceImpl, kDictEditorPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kDictOrderTreeNodeEHImpl, kDictEditorPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kDictOrderDEHandlerImpl, kDictEditorPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kDictOrderDDDataImpl, kDictEditorPrefix + 114)

DECLARE_PMID(kImplementationIDSpace, kDictOrderStatusWidgetTipImpl, kDictEditorPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kDictProviderUIPrefsImpl, kDictEditorPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kSetDictProviderUIPrefCmdImpl, kDictEditorPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kDudenAlertResponderImpl, kDictEditorPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kIsWithDudenDocImpl, kDictEditorPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kDudenAlertShownBoolDataImpl, kDictEditorPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kDudenAlertShownCmdImpl, kDictEditorPrefix + 126)



// <Widget ID>
//---------------------------------------------------------------
// Widget IDs
//---------------------------------------------------------------

DECLARE_PMID(kWidgetIDSpace, kDictWordWidgetID, kDictEditorPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kDictHyphListPanelWidgetID, kDictEditorPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kDictHyphListWidgetID, kDictEditorPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDictRemovedListPanelWidgetID, kDictEditorPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kDictRemovedListWidgetID, kDictEditorPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kDictBreaksWidgetID, kDictEditorPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kDictHyphenateWidgetID, kDictEditorPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kDictAddWidgetID, kDictEditorPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kDictReplaceWidgetID, kDictEditorPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kDictRemoveWidgetID, kDictEditorPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kDictLanguageWidgetID, kDictEditorPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsWidgetID, kDictEditorPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kDictHyphVendorWidgetID, kDictEditorPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kDictSpellVendorWidgetID, kDictEditorPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kDictWordTextWidgetID, kDictEditorPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kDictRemovePanelAddWidgetID, kDictEditorPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kDictIgnoredListWidgetID, kDictEditorPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kDictHyphWordTextWidgetID, kDictEditorPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kDictIgnorePanelAddWidgetID, kDictEditorPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kDictHyphAddWidgetID, kDictEditorPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kDictHyphRemoveWidgetID, kDictEditorPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kDictEditParentWidgetID, kDictEditorPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kDictEditLanguageTextWidgetID, kDictEditorPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kDictEditListTextWidgetID, kDictEditorPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsLanguageTextWidgetID, kDictEditorPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsHyphVendTextWidgetID, kDictEditorPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsSpellVendTextWidgetID, kDictEditorPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kDictEditorPopupGroupWidgetID, kDictEditorPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kDictEditorGroup1WidgetID, kDictEditorPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kDictEditorGroup2WidgetID, kDictEditorPrefix + 39)

DECLARE_PMID(kWidgetIDSpace, kDictEditorGroup3WidgetID, kDictEditorPrefix + 40)
//DECLARE_PMID(kWidgetIDSpace, kDictPrefsUDTextWidgetID, kDictEditorPrefix + 41)
//DECLARE_PMID(kWidgetIDSpace, kDictPrefsHETextWidgetID, kDictEditorPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsCheckBox1WidgetID, kDictEditorPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsHyphSourceTextWidgetID, kDictEditorPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kDictHyphSourceWidgetID, kDictEditorPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kDictCurrentCompositionWidgetID, kDictEditorPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsCheckBox2WidgetID, kDictEditorPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kDictIgnoredListPanelWidgetID, kDictEditorPrefix + 48)


DECLARE_PMID(kWidgetIDSpace, kDictEditorLanguageGroupWidgetID, kDictEditorPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kDictDictTargetListWidgetID, kDictEditorPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kDictDictTargetListTextWidgetID, kDictEditorPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kDictEditTargetTextWidgetID, kDictEditorPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kDictTargetWidgetID, kDictEditorPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kDictEditorPopupGroup2WidgetID, kDictEditorPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kDictEditorHyphExceptionsGroupWidgetID, kDictEditorPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kDictEditorUserDictGroupWidgetID, kDictEditorPrefix + 57)

DECLARE_PMID(kWidgetIDSpace, kDictPrefsSingleQuotesTextWidgetID, kDictEditorPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsDoubleQuotesTextWidgetID, kDictEditorPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kDictDoubleQuotesWidgetID, kDictEditorPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kDictSingleQuotesWidgetID, kDictEditorPrefix + 61)

DECLARE_PMID(kWidgetIDSpace, kDictThesVendorWidgetID, kDictEditorPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsThesVendTextWidgetID, kDictEditorPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kDictHunspellLinkWidgetID, kDictEditorPrefix + 67)
//gap

DECLARE_PMID(kWidgetIDSpace, kDictImportWordListWidgetID, kDictEditorPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kDictExportWordListWidgetID, kDictEditorPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kDictCaseSensitiveWidgetID, kDictEditorPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kDictEditorGroup4WidgetID, kDictEditorPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kDictEditorArabicSpellingOptionsGroupWidgetID, kDictEditorPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsASOTextWidgetID, kDictEditorPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kDictPrefsASModeTextWidgetID, kDictEditorPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kDictASModeWidgetID, kDictEditorPrefix + 77)
//gap

DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderListBoxWidgetID, kDictEditorPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderListElementWidgetID, kDictEditorPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderListParentWidgetID, kDictEditorPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderListElementNameWidgetID, kDictEditorPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderCtrlSetWidgetID, kDictEditorPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderAddDictionaryWidgetID, kDictEditorPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderRemoveDictionaryWidgetID, kDictEditorPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderNewDictionaryWidgetID, kDictEditorPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderReloadDictionaryWidgetID, kDictEditorPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderRelinkDictionaryWidgetID, kDictEditorPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kDictionaryOrderOuterFrameWidgetID, kDictEditorPrefix + 90)



//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kDictEditorPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kDictOrderTreeNodeWidgetID, kDictEditorPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kDictOrderPathNameStaticTextWidgetID, kDictEditorPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kDictOrderTreeViewWidgetID, kDictEditorPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kDictOrderPathStateIconWidgetID, kDictEditorPrefix + 103)


DECLARE_PMID(kWidgetIDSpace, kDictEditorGroup5WidgetID, kDictEditorPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kDictEditorDudenDictGroupWidgetID, kDictEditorPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kShowHyphenOptionsCheckBoxWidgetID, kDictEditorPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kDictEditorDudenDictInfoGroupWidgetID, kDictEditorPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kDictEditorDudenDictInfoIconWidgetID, kDictEditorPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kDictEditorDudenDictInfoTextWidgetID, kDictEditorPrefix + 115)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTEDITORMSG, kDictEditorPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTWORDDICT, kDictEditorPrefix + 2)		// kBoolDataImpl
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNOREDWORDDICT, kDictEditorPrefix + 3)		// kBoolDataImpl
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTORDERMSG, kDictEditorPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTWORDLISTFILEOPTIONS, kDictEditorPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTORDERDDDATA, kDictEditorPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTPROVIDERUIPREFS, kDictEditorPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IISWITHDUDENDOC, kDictEditorPrefix + 8)	//kMinusOneInitIntDataImpl
DECLARE_PMID(kInterfaceIDSpace, IID_IDUDENALERTSHOWN, kDictEditorPrefix + 9)


// <Message ID>
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgLanguageHasChanged, kDictEditorPrefix +  1)
	// sent by DictLanguageObserver, changedBy is LanguageID.
	// received by DictEditorObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgBreaksHasChanged, kDictEditorPrefix +  2)
	// sent by DictBreaksObserver, changedBy is bool16.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgSelectNextItem, kDictEditorPrefix +  3)
	// sent by DictWordEH, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgSelectPrevItem, kDictEditorPrefix +  4)
	// sent by DictWordEH, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgAddWord, kDictEditorPrefix +  5)
	// sent by DictWordEH and DictAddObserver, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgRemoveWord, kDictEditorPrefix +  6)
	// sent by DictRemoveObserver, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgReplaceWord, kDictEditorPrefix +  7)
	// sent by DictWordEH and DictAddObserver, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgHyphenateWord, kDictEditorPrefix +  8)
	// sent by DictWordEH and DictAddObserver, changedBy is nil.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgWordAdded, kDictEditorPrefix +  9)
	// sent by DictWordObserver after IUserDictService::AddToUserDict(), changedBy is DictWordObserver.
	// received by DictHyphListObserver and DictRemovedListObserver.
DECLARE_PMID(kMessageIDSpace, kDictPrefsMsgHyphVendorHasChanged, kDictEditorPrefix +  10)
	// sent by DictHyphVendorObserver on changes.
	// received by DictSpellVendorObserver.
DECLARE_PMID(kMessageIDSpace, kDictPrefsMsgSpellVendorHasChanged, kDictEditorPrefix +  11)
	// sent by DictSpellVendorObserver on changes.
	// received by DictHyphVendorObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgItemSelected, kDictEditorPrefix +  12)
	// sent by DictListBoxEH on DictListBoxEH::LButtonDn().
	// received by DictWordObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgItemExecuted, kDictEditorPrefix +  13)
	// sent by DictListBoxEH on DictListBoxEH::ButtonDblClk().
	// received by DictWordObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgWordGetsFocus, kDictEditorPrefix +  14)
	// sent by DictWordEH on DictWordEH::GetFocus().
	// received by DictHyphListObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgWordHasChanged, kDictEditorPrefix +  15)
	// sent by DictWordEH on DictWordEH::KeyCmd().
	// received by DictAddObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgListHasChanged, kDictEditorPrefix +  16)
	// sent by DictHyphListObserver after add/delete.
	// received by DictAddObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgWordPasted, kDictEditorPrefix +  17)
	// sent by DictWordEditboxScrapSuite.
	// received by DictWordObserver.


	// new for Sherpa

DECLARE_PMID(kMessageIDSpace, kDictEditorMsgTargetHasChanged, kDictEditorPrefix +  18)
	// sent by DictTargetListObserver.
	// received by DictEditorObserver, DictStatTextObserver.
DECLARE_PMID(kMessageIDSpace, kDictPrefsMsgHyphSourceHasChanged, kDictEditorPrefix +  19)
	// sent by DictSpellVendorObserver on changes.
	// received by DictHyphVendorObserver.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgImportWordList, kDictEditorPrefix +  20)
	// sent by DictImportObserver on changes.
	// received by xxx.
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgExportWordList, kDictEditorPrefix +  21)
	// sent by DictExportObserver on changes.
	// received by xxx.

	// Firedrake
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgCaseSensitiveHasChanged, kDictEditorPrefix +  25)
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgDefaultDictCreated, kDictEditorPrefix +  26)
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgDictionaryListTypeChanged, kDictEditorPrefix +  27)

	//Cobalt
DECLARE_PMID(kMessageIDSpace, kDictEditorMsgOpenDictEditorDlog, kDictEditorPrefix +  28)
DECLARE_PMID(kMessageIDSpace, kDictPrefsMsgThesVendorHasChanged, kDictEditorPrefix +  29)

			// Dict order
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgListHasChanged, kDictEditorPrefix +  30)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgDictionaryAdded, kDictEditorPrefix +  31)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgRemoveDictionary, kDictEditorPrefix +  32)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgItemExecuted, kDictEditorPrefix +  33)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgItemSelected, kDictEditorPrefix +  34)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgReloadDictionary, kDictEditorPrefix +  35)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgRelinkDictionary, kDictEditorPrefix +  36)
DECLARE_PMID(kMessageIDSpace, kDictOrderMsgReorderDictionary, kDictEditorPrefix +  37)





// <Action ID>
//---------------------------------------------------------------
// Action IDs
//---------------------------------------------------------------

DECLARE_PMID(kActionIDSpace, kEditDictionaryActionID, kDictEditorPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDictionaryPrefsActionID, kDictEditorPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDictPrefsSepActionID, kDictEditorPrefix + 3)

//
//Script Element IDs
//

// -- The implementations and resources for these have been moved to the text plugin
// -- but the IDs can't change or we assert when testing the high level API.

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kHyphenationExceptionObjectScriptElement,			kDictEditorPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kDictionaryPreferenceObjectScriptElement,			kDictEditorPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kUserDictionaryObjectScriptElement,				kDictEditorPrefix + 43)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kAddExceptionMethodScriptElement,					kDictEditorPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveExceptionMethodScriptElement,				kDictEditorPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kAddWordMethodScriptElement,						kDictEditorPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveWordMethodScriptElement,						kDictEditorPrefix + 83)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kRemovedWordsPropertyScriptElement,				kDictEditorPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kAddedWordsPropertyScriptElement,					kDictEditorPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kDictPrefsPropertyScriptElement,					kDictEditorPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kCompositionPropertyScriptElement,					kDictEditorPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kMergeUserDictionaryPropertyScriptElement,			kDictEditorPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kRecomposeWhenChangedPropertyScriptElement,		kDictEditorPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kRemovedExceptionsPropertyScriptElement,			kDictEditorPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kAddedExceptionsPropertyScriptElement,				kDictEditorPrefix + 167)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kDictionaryCompositionEnumScriptElement,		kDictEditorPrefix + 220)


//GUIDS
// {A3736547-4F5C-11d2-AB07-00C04FA349C7}
#define kDictPref_CLSID { 0xa3736547, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736543-4F5C-11d2-AB07-00C04FA349C7}
#define kUserDict_CLSID { 0xa3736543, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736544-4F5C-11d2-AB07-00C04FA349C7}
#define kUserDicts_CLSID { 0xa3736544, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736545-4F5C-11d2-AB07-00C04FA349C7}
#define kHyphException_CLSID { 0xa3736545, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736546-4F5C-11d2-AB07-00C04FA349C7}
#define kHyphExceptions_CLSID { 0xa3736546, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }


//Misc
#define kDictOrderNodeIDClass kDictEditorPrefix + 1

#endif // __DictEditorID__
