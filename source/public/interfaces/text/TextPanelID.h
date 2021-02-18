//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextPanelID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __TextPanelID__
#define __TextPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// was #define kTextPanelPrefix	RezLong(0x2800) 	/* doublecheck with AdobePrefix.h */
#define kTextPanelPrefix	RezLong(0xe100) 	/* doublecheck with AdobePrefix.h */
#define kTextPanelPrefix16	RezLong(0x3f00) 	/* doublecheck with AdobePrefix.h */
//#define kTextPanelRecentsPrefix1 RezLong(0xdf00) // TODO: ask for 0xdf and 0xe0 for font menu recent id's
					// note - we actually reserve prefixes e1 thru ef - so we can expand out of this prefix.
#define kTextPanelStringsRsrcID 				1000
#define kTextPanelStringsNoTransRsrcID 	1100

#define kCharPathMenuResID	 					600
#define kCharPathActionResID 					700

#define kTextPanelMenuResID						1200
#define kTextPanelActionResID					1300
// Flag icons
#define kTextPanelFlagsPrefix				500
#define kFontMenuType1Icon				501
#define kFontMenuTrueTypeIcon			502
#define kFontMenuOpenTypeIcon		503
#define kFontMenuOCFIcon			504
#define kFontMenuCheckedIcon		505
#define kFontMenuMultiSelectIcon	506
#define kFontMenuTypekitIcon        507
#define kFontMenuSVGIcon			508
#define kFontMenuOTVarIcon          509
// <Start IDC>
// PluginID
#define kTextPanelPluginName 				"Text Panel"
DECLARE_PMID(kPlugInIDSpace, kTextPanelPluginID, kTextPanelPrefix + 1)

#define kTextPanelFlagNeutral				kTextPanelFlagsPrefix + 0
#define kTextPanelFlagUK					kTextPanelFlagsPrefix + 1
#define kTextPanelFlagCanada				kTextPanelFlagsPrefix + 2
#define kTextPanelFlagDenmark			kTextPanelFlagsPrefix + 3
#define kTextPanelFlagNetherlands			kTextPanelFlagsPrefix + 4
#define kTextPanelFlagSpain				kTextPanelFlagsPrefix + 5
#define kTextPanelFlagFinnland				kTextPanelFlagsPrefix + 6
#define kTextPanelFlagBelgium				kTextPanelFlagsPrefix + 7
#define kTextPanelFlagFrance				kTextPanelFlagsPrefix + 8
#define kTextPanelFlagGermany			kTextPanelFlagsPrefix + 9
#define kTextPanelFlagItaly				kTextPanelFlagsPrefix + 10
#define kTextPanelFlagNorway				kTextPanelFlagsPrefix + 11
#define kTextPanelFlagSweden				kTextPanelFlagsPrefix + 12
#define kTextPanelFlagAutralia				kTextPanelFlagsPrefix + 13
#define kTextPanelFlagUS					kTextPanelFlagsPrefix + 14
#define kTextPanelFlagSwissGerman			kTextPanelFlagsPrefix + 15
#define kTextPanelFlagSwissFrench			kTextPanelFlagsPrefix + 16


// <Class ID>
// Bosses
DECLARE_PMID(kClassIDSpace, kTALanguageObserverBoss, kTextPanelPrefix + 0	)
DECLARE_PMID(kClassIDSpace, kDocumentFontsCloseDocResponderBoss, kTextPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTextWalkerWrapCheckBoxBoss, kTextPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTextWalkerOversetCheckBoxBoss, kTextPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTextWalkerScopeObserverBoss, kTextPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTextDialogWidgetBoss, kTextPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTextSelectableDialogWidgetBoss, kTextPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTextControlSetBoss, kTextPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTextPanelWidgetBoss, kTextPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTextPanelCoreWidgetBoss, kTextPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kTextColorPanelCoreWidgetBoss, kTextPanelPrefix + 10)

DECLARE_PMID(kClassIDSpace, kSizesComponentBoss, kTextPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kMissingComponentBoss, kTextPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTypeTestComponentBoss, kTextPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kFontComponentBoss, kTextPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kDocumentFontComponentBoss, kTextPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kHYPModeObserverBoss, kTextPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kMissingFontsCloseDocResponderBoss, kTextPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTextFontFamilyObserverBoss, kTextPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kTextFontStyleObserverBoss, kTextPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCharPathTestMenuBoss, kTextPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCharPathMenuComponentBoss, kTextPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kFontMenuElementWidgetBoss, kTextPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kFontPreviewCacheStartupShutdownBoss, kTextPanelPrefix + 23)

DECLARE_PMID(kClassIDSpace, kFontMaskCacheRootBoss, kTextPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kFontMaskCacheMaskStorageBoss, kTextPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kFontMaskCacheMapStorageBoss, kTextPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kFontMenuTestsBoss, kTextPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kFontMenuTestsEditBoxWidgetBoss, kTextPanelPrefix + 28)

DECLARE_PMID(kClassIDSpace, kBrowseFontMenuComponentBoss, kTextPanelPrefix + 29)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTROBSERVERDATA, kTextPanelPrefix + 1		)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWORKSPACEOBSERVER, kTextPanelPrefix + 2		)
DECLARE_PMID(kInterfaceIDSpace, IID_ITALANGUAGEOBSERVER, kTextPanelPrefix + 3		)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWIDGETOBSERVER, kTextPanelPrefix + 4		)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTROBSERVERDATA_2, kTextPanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPANELDATA, kTextPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTTARGETOBSERVER, kTextPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTTARGETSERVER, kTextPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLIEDATTRIBUTES, kTextPanelPrefix + 10	/* IID_ITEXTATTRIBUTES */)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPREVIEWMASKCACHE, kTextPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMENUVIEWMGR, kTextPanelPrefix + 12)
// Use the following if "frequent" (i.e., every arrow-key) updates are needed,
// as opposed to less frequent (every run change) given by IID_ITEXTTARGETOBSERVER
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTTARGETFREQUENTOBSERVER, kTextPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFONTOBSERVERDATA, kTextPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMENUDATA, kTextPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGFONTMENUDATA, kTextPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEDCOLORUID, kTextPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERPRINTOBSERVER, kTextPanelPrefix + 18)

DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMASKCACHE, kTextPanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMASKCACHEROOT, kTextPanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMASKCACHEMASKSTORAGE, kTextPanelPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPREVIEWPSNAMES, kTextPanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPREVIEWIDLETASK, kTextPanelPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPREVIEWUTILS, kTextPanelPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTFONTMENUDATA, kTextPanelPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGORDOCUMENTFONTRAN, kTextPanelPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGANDDOCUMENTFONTSEPARATOR, kTextPanelPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLEAREDFONTSEPARATOR, kTextPanelPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ICANUPDATERECENTSDATA, kTextPanelPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTS, kTextPanelPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IFIRSTDISPLAYEDFONT, kTextPanelPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIVEFONTPREVIEWMGR, kTextPanelPrefix + 32)

// <Implementation ID>
// Implementations
DECLARE_PMID(kImplementationIDSpace, kTAObserverDataImpl, kTextPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTextWorkSpaceObserverImpl, kTextPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kMissingAndDocumentFontSeparatorImpl, kTextPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTextWidgetObserverImpl, kTextPanelPrefix + 4	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kTARealNumberObserverImpl, kTextPanelPrefix + 5	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kTAInt16ObserverImpl, kTextPanelPrefix + 6	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kTABoolObserverImpl, kTextPanelPrefix + 7	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kTALanguageObserverImpl, kTextPanelPrefix + 8	)
//DECLARE_PMID(kImplementationIDSpace, kTAFlagObserverImpl, kTextPanelPrefix + 9	)
DECLARE_PMID(kImplementationIDSpace, kDocumentFontsCloseDocResponderImpl, kTextPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTextWalkerObserverImpl, kTextPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTextWalkerBoolObserverImpl, kTextPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTextWalkerWrapObserverImpl, kTextPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTextWalkerOversetObserverImpl, kTextPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTextWalkerScopeObserverImpl, kTextPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTextPanelViewImpl, kTextPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTextPanelDialogImpl, kTextPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTextPanelHookViewImpl, kTextPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kTextPanelDialogCreatorImpl, kTextPanelPrefix + 20	)
DECLARE_PMID(kImplementationIDSpace, kTextPanelDialogServiceImpl, kTextPanelPrefix + 21	)
DECLARE_PMID(kImplementationIDSpace, kTextPanelSelectableCreatorImpl, kTextPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTATriObserverImpl, kTextPanelPrefix + 23	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsCloseDocResponderImpl, kTextPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kTextTargetObserverImpl, kTextPanelPrefix + 25	/* TextObserver in TextPanel.Lib */)
DECLARE_PMID(kImplementationIDSpace, kTextTargetServerImpl, kTextPanelPrefix + 26	/* TextObserver in TextPanel.Lib */)



DECLARE_PMID(kImplementationIDSpace, kTextDialogView, kTextPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kTextPanelDialogControllerImpl, kTextPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kFontSearchMenuViewMgrImpl, kTextPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kFontMenuViewMgrImpl, kTextPanelPrefix + 30)
//gap
DECLARE_PMID(kImplementationIDSpace, kSizesComponentImpl, kTextPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kFontComponentImpl, kTextPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMissingComponentImpl, kTextPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTypeTestComponentImpl, kTextPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kTextPanelSelDialogControllerImpl, kTextPanelPrefix + 36)

DECLARE_PMID(kImplementationIDSpace, kTAUsedLanguageObserverImpl, kTextPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kHYPModeObserverImpl, kTextPanelPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kTextFontFamilyObserverImpl, kTextPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kTextFontStyleObserverImpl, kTextPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kTextFontObserverDataImpl, kTextPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kDynamicFontMenuImpl, kTextPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kFontMenuDataImpl, kTextPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMissingFontDynamicMenuImpl, kTextPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMissingFontMenuDataImpl, kTextPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDynamicFontSizesMenuImpl, kTextPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDocumentFontDynamicMenuImpl, kTextPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDocumentFontMenuDataImpl, kTextPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kDocumentFontComponentImpl, kTextPanelPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kCharPathTestMenuImpl, kTextPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kCharPathMenuComponentImpl, kTextPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kOwnerDrawFontMenuImpl, kTextPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kFontMenuElementViewImpl, kTextPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kFontPreviewCacheStartupShutdownImpl, kTextPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kFontPreviewMaskCacheImpl, kTextPanelPrefix + 55)

DECLARE_PMID(kImplementationIDSpace, kFontMaskCacheImpl, kTextPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kFontMaskCacheRootImpl, kTextPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kFontMaskCacheMaskStorageImpl, kTextPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kFontMaskCacheMapStorageImpl, kTextPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kFontPreviewPSNamesImpl, kTextPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kFontPreviewIdleTaskImpl, kTextPanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kFontPreviewUtilsImpl, kTextPanelPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kTAInt32ObserverImpl, kTextPanelPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kLiveFontPreviewMgrImpl, kTextPanelPrefix + 64)    
//gap
DECLARE_PMID(kImplementationIDSpace, kDVParentFontElementViewImpl, kTextPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kFontMenuTestsImpl, kTextPanelPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kFontMenuTestsEditBoxObserverImpl, kTextPanelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kFontMenuTestsEditBoxAttributesImpl, kTextPanelPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kFontMenuFindListDataImpl, kTextPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kFontMenuDataBuildTreeDataImpl, kTextPanelPrefix + 71)

DECLARE_PMID(kImplementationIDSpace, kBrowseFontMenuComponentImpl, kTextPanelPrefix + 72)

DECLARE_PMID(kMessageIDSpace, kMsgSetupWidgetImpl, kTextPanelPrefix + 221	/* kWidgetPrefix, called at the first init */)
DECLARE_PMID(kMessageIDSpace, kMsgUpdateWidgetsImpl, kTextPanelPrefix + 222	/* update widgets */)
DECLARE_PMID(kMessageIDSpace, kMsgApplyModelImpl, kTextPanelPrefix + 223	/* kTextAttrPrefix, apply settings from the widget */)
DECLARE_PMID(kMessageIDSpace, kMsgWidgetToTargetImpl, kTextPanelPrefix + 224	/* sent by the TextTargetServer, received by the TextTargetObserver, changedBy is an ITextTargetAttributes. */)
DECLARE_PMID(kMessageIDSpace, kMsgTargetToWidgetImpl, kTextPanelPrefix + 225	/* sent by the TextTargetServer, received by the TextTargetObserver, changedBy is an ITextTargetAttributes. */)
DECLARE_PMID(kMessageIDSpace, kMsgCallBackWidgetToTargetImpl, kTextPanelPrefix + 226	/* sent by the TextTargetObserver, received by the TextTargetServer, changedBy is the TextTargetObserver. */)
DECLARE_PMID(kMessageIDSpace, kMsgCallBackTargetToWidgetImpl, kTextPanelPrefix + 227	/* sent by the TextTargetObserver, received by the TextTargetServer, changedBy is the TextTargetObserver. */)
DECLARE_PMID(kMessageIDSpace, kMsgEnableWidgetImpl, kTextPanelPrefix + 228	/* sent by the TextTargetServer, received by the TextTargetObserver, calls TextTargetObserver::EnableWidget(). */)
DECLARE_PMID(kMessageIDSpace, kMsgDisableWidgetImpl, kTextPanelPrefix + 229	/* sent by the TextTargetServer, received by the TextTargetObserver, calls TextTargetObserver::DisableWidget(). */)
DECLARE_PMID(kMessageIDSpace, kMsgCreateTargetImpl, kTextPanelPrefix + 230	/* sent by any TextTargetObserver, received by the TextTargetServer, changedBy is an ITextTargetAttribute** */)
DECLARE_PMID(kMessageIDSpace, kMsgResetAttributeImpl, kTextPanelPrefix + 231	/* sent when alt-reset clicked; clear front panel's attributes */)
DECLARE_PMID(kMessageIDSpace, kMsgResetToBaseStyleImpl, kTextPanelPrefix + 232	/* sent when the reset to base style button is clicked */)
DECLARE_PMID(kMessageIDSpace, kMsgUpdateRecentsMenu, kTextPanelPrefix + 233	/* sent when it's a good time to update the recents font menu, used to avoid unappealling redraws */)

// note - we actually reserve prefixes e1 thru ef - so we can use ids in the range (kTextPanelPrefix +0) to (kTextPanelPrefix + 3839)
// <Action ID>
DECLARE_PMID(kActionIDSpace, kSizeOtherActionID, kTextPanelPrefix +1)
DECLARE_PMID(kActionIDSpace, kSizeMenuSepActionID, kTextPanelPrefix +2)
DECLARE_PMID(kActionIDSpace, kSize6ActionID, kTextPanelPrefix +3)
#define kFirstSizeActionID kSize6ActionID
DECLARE_PMID(kActionIDSpace, kSize7ActionID, kTextPanelPrefix +4)
DECLARE_PMID(kActionIDSpace, kSize7Pt5ActionID, kTextPanelPrefix +5)
DECLARE_PMID(kActionIDSpace, kSize8ActionID, kTextPanelPrefix +6)
DECLARE_PMID(kActionIDSpace, kSize8Pt5ActionID, kTextPanelPrefix +7)
DECLARE_PMID(kActionIDSpace, kSize9ActionID, kTextPanelPrefix +8)
DECLARE_PMID(kActionIDSpace, kSize10ActionID, kTextPanelPrefix +9)
DECLARE_PMID(kActionIDSpace, kSize11ActionID, kTextPanelPrefix +10)
DECLARE_PMID(kActionIDSpace, kSize12ActionID, kTextPanelPrefix +11)
DECLARE_PMID(kActionIDSpace, kSize13ActionID, kTextPanelPrefix +12)
DECLARE_PMID(kActionIDSpace, kSize14ActionID, kTextPanelPrefix +13)
DECLARE_PMID(kActionIDSpace, kSize16ActionID, kTextPanelPrefix +14)
DECLARE_PMID(kActionIDSpace, kSize18ActionID, kTextPanelPrefix +15)
DECLARE_PMID(kActionIDSpace, kSize24ActionID, kTextPanelPrefix +16)
DECLARE_PMID(kActionIDSpace, kSize30ActionID, kTextPanelPrefix +17)
DECLARE_PMID(kActionIDSpace, kSize32ActionID, kTextPanelPrefix +18)
DECLARE_PMID(kActionIDSpace, kSize36ActionID, kTextPanelPrefix +19)
DECLARE_PMID(kActionIDSpace, kSize48ActionID, kTextPanelPrefix +20)
DECLARE_PMID(kActionIDSpace, kSize60ActionID, kTextPanelPrefix +21)
DECLARE_PMID(kActionIDSpace, kSize72ActionID, kTextPanelPrefix +22)
DECLARE_PMID(kActionIDSpace, kSize100ActionID, kTextPanelPrefix +23)
#define kLastSizeActionID kSize100ActionID
//gap

DECLARE_PMID(kActionIDSpace, kFontSearchActionID, kTextPanelPrefix +30)
DECLARE_PMID(kActionIDSpace, kTypeSizeMenuSepActionID, kTextPanelPrefix +31)
DECLARE_PMID(kActionIDSpace, kFontMenuDynamicActionID, kTextPanelPrefix +32)
DECLARE_PMID(kActionIDSpace, kFontSizesMenuDynamicActionID, kTextPanelPrefix +33)
DECLARE_PMID(kActionIDSpace, kTextSizeSepActionID, kTextPanelPrefix +34)
DECLARE_PMID(kActionIDSpace, kFontMenuSepActionID, kTextPanelPrefix +35)
DECLARE_PMID(kActionIDSpace, kMissingFontMenuDynamicActionID, kTextPanelPrefix +36)
DECLARE_PMID(kActionIDSpace, kDocumentFontMenuDynamicActionID, kTextPanelPrefix + 37)
DECLARE_PMID(kActionIDSpace, kPairKerningFirstActionID, kTextPanelPrefix +38)
// loadable pair kerning fits here -ids here reserved
DECLARE_PMID(kActionIDSpace, kPairKerningLastActionID, kTextPanelPrefix +42)
DECLARE_PMID(kActionIDSpace, kEdgeAlignmentFirstActionID, kTextPanelPrefix +43)
// loadable edge adjustments in here -ids here reserved
DECLARE_PMID(kActionIDSpace, kEdgeAlignmentLastActionID, kTextPanelPrefix +52)

DECLARE_PMID(kActionIDSpace, kDocumentFontSeparatorActionID, kTextPanelPrefix +53);
DECLARE_PMID(kActionIDSpace, kFirstMissingFontActionID, kTextPanelPrefix +54)
// DONT USE THE IDS 54-162 they are reserved for missing fonts
DECLARE_PMID(kActionIDSpace, kLastMissingFontActionID, kTextPanelPrefix +163)
DECLARE_PMID(kActionIDSpace, kFirstFontActionID, kTextPanelPrefix +164			/* First font item */)
// DONT USE THE IDS 165-3803 they are reserved for fonts
DECLARE_PMID(kActionIDSpace, kLastFontActionID, kTextPanelPrefix +3292			/* Last font item */)

DECLARE_PMID(kActionIDSpace, kFirstRecentsFontActionID, kTextPanelPrefix +3293) /* first recents item */
// DONT USE THE IDS 3293-3804; they are reserved for recently used fonts
DECLARE_PMID(kActionIDSpace, kLastRecentsFontActionID, kTextPanelPrefix +3804) /* last recents item */

// note - we actually reserve prefixes e1 thru ef - so we can use ids in the range (kTextPanelPrefix +0) to (kTextPanelPrefix + 3839)
// Only 3839 is free ActionID still remaining in this range.
DECLARE_PMID(kActionIDSpace, kCreateOutlinesActionID, kTextPanelPrefix + 3805)
DECLARE_PMID(kActionIDSpace, kCreateOutlinesWithoutDeletingTextActionID, kTextPanelPrefix + 3806)
DECLARE_PMID(kActionIDSpace, kCreateOutlinesSepActionID, kTextPanelPrefix + 3807)

// DONT USE THE IDS 3808-3838 they are reserved for separators of the fonts
DECLARE_PMID(kActionIDSpace, kFirstRecentsSepActionID, kTextPanelPrefix +3808)
DECLARE_PMID(kActionIDSpace, kFirstFontSepActionID, kTextPanelPrefix +3809			/* first font separator */)
DECLARE_PMID(kActionIDSpace, kLastFontSepActionID, kTextPanelPrefix +3838			/* last font separator */)
// 3839 is still available

DECLARE_PMID(kActionIDSpace, kFirstDocumentFontActionID, kTextPanelPrefix16 +1)
// DONT USE THE IDS 2-103; they are reserved for document fonts
DECLARE_PMID(kActionIDSpace, kLastDocumentFontActionID, kTextPanelPrefix16 +104)


#endif // __TextPanelID__
