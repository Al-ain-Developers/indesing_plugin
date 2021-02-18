//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/EyeDropperToolID.h $
//  
//  Owner: Dave Stephens
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
//  Contains IDs used by EyeDropper tool plug-in
//  
//========================================================================================

#ifndef __EyeDropperToolID__
#define __EyeDropperToolID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kEyeDropperToolPrefix	 RezLong(0xBA00)
#define kEyeDropperToolPrefix2	 RezLong(0x23700)


// <Start IDC>
// PluginID
#define kEyeDropperToolPluginName 				"EyeDropperTool"
DECLARE_PMID(kPlugInIDSpace, kEyeDropperToolPluginID, kEyeDropperToolPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kEyeDropperToolBoss, kEyeDropperToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kEyeDropperTrackerBoss, kEyeDropperToolPrefix + 2)
DECLARE_PMID(kClassIDSpace, kEyeDropperTrackerRegisterBoss, kEyeDropperToolPrefix + 3)

//gap
DECLARE_PMID(kClassIDSpace, kEyeDropperToolStateBoss, kEyeDropperToolPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSetEyeDropperPrefsCmdBoss, kEyeDropperToolPrefix + 7)

DECLARE_PMID(kClassIDSpace, kEyeDropperDialogBoss, kEyeDropperToolPrefix + 9)
DECLARE_PMID(kClassIDSpace, kEyeDropperCharPrefsPanelBoss, kEyeDropperToolPrefix + 10)
DECLARE_PMID(kClassIDSpace, kEyeDropperParaPrefsPanelBoss, kEyeDropperToolPrefix + 11)
DECLARE_PMID(kClassIDSpace, kEyeDropperStrokePrefsPanelBoss, kEyeDropperToolPrefix + 12)
DECLARE_PMID(kClassIDSpace, kEyeDropperFillPrefsPanelBoss, kEyeDropperToolPrefix + 13)

DECLARE_PMID(kClassIDSpace, kCharAttributesOnWidgetBoss, kEyeDropperToolPrefix + 14)
DECLARE_PMID(kClassIDSpace, kParaAttributesOnWidgetBoss, kEyeDropperToolPrefix + 15)
DECLARE_PMID(kClassIDSpace, kStrokeAttributesOnWidgetBoss, kEyeDropperToolPrefix + 16)
DECLARE_PMID(kClassIDSpace, kFillAttributesOnWidgetBoss, kEyeDropperToolPrefix + 17)
DECLARE_PMID(kClassIDSpace, kConvertAttrBossListCmdBoss, kEyeDropperToolPrefix + 18)
DECLARE_PMID(kClassIDSpace, kConvertAttributeCmdBoss, kEyeDropperToolPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCJKEyeCharPrefsPanelBoss, kEyeDropperToolPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCJKEyeParaPrefsPanelBoss, kEyeDropperToolPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCJKCharAttrOnObserverBoss, kEyeDropperToolPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCJKParaAttrOnObserverBoss, kEyeDropperToolPrefix + 23)

DECLARE_PMID(kClassIDSpace, kEyeDropperPrefsPanelBoss, kEyeDropperToolPrefix + 30)
DECLARE_PMID(kClassIDSpace, kEyeDropperTreeViewWidgetBoss, kEyeDropperToolPrefix + 31)
DECLARE_PMID(kClassIDSpace, kEyeDropperTreeNodeWidgetBoss, kEyeDropperToolPrefix + 32)
DECLARE_PMID(kClassIDSpace, kBranchCheckBoxBoss, kEyeDropperToolPrefix + 33)
DECLARE_PMID(kClassIDSpace, kLeafCheckBoxBoss, kEyeDropperToolPrefix + 34)
DECLARE_PMID(kClassIDSpace, kEyeDropperRIDXHandlerBoss, kEyeDropperToolPrefix + 35)
DECLARE_PMID(kClassIDSpace, kEyeDropperRIDXReplaceStyleCmdBoss, kEyeDropperToolPrefix + 36)
DECLARE_PMID(kClassIDSpace, kEyeDropperRIDXReplaceTextAttrsCmdBoss, kEyeDropperToolPrefix + 37)
// gap
DECLARE_PMID(kClassIDSpace, kColorThemeToolBoss, kEyeDropperToolPrefix + 51)
DECLARE_PMID(kClassIDSpace, kColorThemeToolTrackerBoss, kEyeDropperToolPrefix + 52)
DECLARE_PMID(kClassIDSpace, kColorThemeToolTrackerRegisterBoss, kEyeDropperToolPrefix + 53)
DECLARE_PMID(kClassIDSpace, kColorThemeToolPanelWindowBoss, kEyeDropperToolPrefix + 54) 
DECLARE_PMID(kClassIDSpace, kColorThemeToolDialogBoss, kEyeDropperToolPrefix + 55) 
DECLARE_PMID(kClassIDSpace, kColorThemeToolGripperViewBoss, kEyeDropperToolPrefix + 56) 
DECLARE_PMID(kClassIDSpace, kColorThemeElementWidgetBoss, kEyeDropperToolPrefix + 57)
DECLARE_PMID(kClassIDSpace, kColorThemeToolPopupPanelButtonBoss, kEyeDropperToolPrefix + 58)
DECLARE_PMID(kClassIDSpace, kColorThemeToolPopupPanelBoss, kEyeDropperToolPrefix + 59)
DECLARE_PMID(kClassIDSpace, kColorThemeAddToSwatchButtonBoss, kEyeDropperToolPrefix + 60) 
DECLARE_PMID(kClassIDSpace, kColorThemeToolPopupPanelTreeWidgetBoss, kEyeDropperToolPrefix + 62)
DECLARE_PMID(kClassIDSpace, kColorThemeToolPopupPanelTreeElementWidgetBoss, kEyeDropperToolPrefix + 63)
DECLARE_PMID(kClassIDSpace, kSetColorThemeToolPrefsBoss, kEyeDropperToolPrefix + 64)
DECLARE_PMID(kClassIDSpace, kColorThemeToolOptionsDlgBoss, kEyeDropperToolPrefix + 65) 
// gap
DECLARE_PMID(kClassIDSpace, kColorThemePopupPanelElementWidgetBoss, kEyeDropperToolPrefix + 67) 
DECLARE_PMID(kClassIDSpace, kColorThemeToolStartupShutdownBoss, kEyeDropperToolPrefix + 68)
DECLARE_PMID(kClassIDSpace, kColorThemeExportToCCLibrariesButtonBoss, kEyeDropperToolPrefix + 69)

// DragonTail Class IDs
DECLARE_PMID(kClassIDSpace, kEyeDropperISuiteBoss, kEyeDropperToolPrefix + 100)

//<Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEDROPPERSTATE, kEyeDropperToolPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDROPPERSTATECONTROLLER_OBSOLETE, kEyeDropperToolPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYECHARATTRFILTER, kEyeDropperToolPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEPARAATTRFILTER, kEyeDropperToolPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYESTROKEATTRFILTER, kEyeDropperToolPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEFILLATTRFILTER, kEyeDropperToolPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETEYEDROPPERPREFSCMDDATA, kEyeDropperToolPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILLMETADATACACHEVALID, kEyeDropperToolPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILLMETADATAOBJECT, kEyeDropperToolPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARAATTRIBUTES, kEyeDropperToolPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYESTYLEUIDLIST, kEyeDropperToolPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEGRAPHICSTATETARGET, kEyeDropperToolPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTATTRBOSSLISTCMDDATA, kEyeDropperToolPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTATTRIBUTECMDDATA, kEyeDropperToolPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYECLOSEDOCOBSERVER, kEyeDropperToolPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKEYECHARATTRFILTER, kEyeDropperToolPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKEYEPARAATTRFILTER, kEyeDropperToolPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTEGROUPID, kEyeDropperToolPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMETOOLMOUSEWATCHER, kEyeDropperToolPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEATTRFILTER, kEyeDropperToolPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEGRAPHICTARGETSUITE, kEyeDropperToolPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEDROPPERTABLEATTRIBUTES, kEyeDropperToolPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IORIGINALSELECTEDITEMS, kEyeDropperToolPrefix + 23) 
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEOBJECTATTRFILTER, kEyeDropperToolPrefix + 24) 
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEDROPPERACTIVETOOL, kEyeDropperToolPrefix + 25) 
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORINDEX, kEyeDropperToolPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDSTROKES, kEyeDropperToolPrefix + 27)

// DragonTail IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEDROPPERSUITE, kEyeDropperToolPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICATTRIBUTES, kEyeDropperToolPrefix + 101)

// Gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMEAPPDATA, kEyeDropperToolPrefix + 201)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMESWATCHDATA, kEyeDropperToolPrefix + 202)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMETOOLPANELMGR, kEyeDropperToolPrefix + 203) 
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMEDROPPERSUITE, kEyeDropperToolPrefix + 204) 
// Gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMEAPPDATATOOLSTATE, kEyeDropperToolPrefix + 211)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMEAPPDATACOLORS, kEyeDropperToolPrefix + 212)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMETOOLPREFS, kEyeDropperToolPrefix + 213)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETCOLORTHEMETOOLPREFSCMDDATA, kEyeDropperToolPrefix + 214)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORTHEMEAPPDATARESETALLCOLORS, kEyeDropperToolPrefix + 215)

// Transform Attributes
DECLARE_PMID(kInterfaceIDSpace, IID_IEYETRANSFORMATTRFILTER, kEyeDropperToolPrefix + 216)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kEyeDropperToolImpl, kEyeDropperToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperTrackerImpl, kEyeDropperToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperTrackerRegisterImpl, kEyeDropperToolPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kEyeDropperCursorProviderImpl, kEyeDropperToolPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kDropperStateControllerImpl_Obsolete, kEyeDropperToolPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kEyeDropperTextFocusImpl_Obsolete, kEyeDropperToolPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kEyeCharAttrFilterImpl, kEyeDropperToolPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kEyeParaAttrFilterImpl, kEyeDropperToolPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kEyeStrokeAttrFilterImpl, kEyeDropperToolPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kEyeFillAttrFilterImpl, kEyeDropperToolPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kEyeObjectAttrFilterImpl, kEyeDropperToolPrefix + 13)

DECLARE_PMID(kImplementationIDSpace, kSetEyeDropperPrefsCmdImpl, kEyeDropperToolPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSetEyeDropperPrefsCmdDataImpl, kEyeDropperToolPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperCharPrefsPanelImpl, kEyeDropperToolPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperParaPrefsPanelImpl, kEyeDropperToolPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperStrokePrefsPanelImpl, kEyeDropperToolPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperFillPrefsPanelImpl, kEyeDropperToolPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperDialogCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperCharPanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperParaPanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperStrokePanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperFillPanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCharAttributesOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kParaAttributesOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttributesOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFillAttributesOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kEyeGraphicStateTargetImpl, kEyeDropperToolPrefix + 29)

DECLARE_PMID(kImplementationIDSpace, kConvertAttrBossListCmdDataImpl, kEyeDropperToolPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kConvertAttrBossListCmdImpl, kEyeDropperToolPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kConvertAttributeCmdDataImpl, kEyeDropperToolPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kConvertAttributeCmdImpl, kEyeDropperToolPrefix + 33)

DECLARE_PMID(kImplementationIDSpace, kCJKEyeCharPanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCJKEyeParaPanelCreatorImpl_OBSOLETE, kEyeDropperToolPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kCJKCharAttrDialogControllerImpl_OBSOLETE, kEyeDropperToolPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kCJKParaAttrDialogControllerImpl_OBSOLETE, kEyeDropperToolPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCJKCharAttrOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCJKParaAttrOnObserverImpl_OBSOLETE, kEyeDropperToolPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kCJKEyeCharAttrFilterImpl, kEyeDropperToolPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kCJKEyeParaAttrFilterImpl, kEyeDropperToolPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kEyeCloseDocObserverImpl, kEyeDropperToolPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperTreeViewWidgetMgrImpl, kEyeDropperToolPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperTreeViewAdapterImpl, kEyeDropperToolPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperDialogControllerImpl, kEyeDropperToolPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kAttributeGroupIDImpl, kEyeDropperToolPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kBranchCheckBoxObserverImpl, kEyeDropperToolPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kLeafCheckBoxObserverImpl, kEyeDropperToolPrefix + 68)
//	Gap
DECLARE_PMID(kImplementationIDSpace, kEyeTableAttrFilterImpl, kEyeDropperToolPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kEyeGraphicTargetSuiteImpl, kEyeDropperToolPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperTableAttributesImpl, kEyeDropperToolPrefix + 72)

DECLARE_PMID(kImplementationIDSpace, kEyeDropperStateImpl, kEyeDropperToolPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kOriginalSelectedItemsImpl, kEyeDropperToolPrefix + 81)

// DragonTail Impls
DECLARE_PMID(kImplementationIDSpace, kEyeDropperSuiteImpl, kEyeDropperToolPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kGenericAttributesImpl, kEyeDropperToolPrefix + 101)

DECLARE_PMID(kImplementationIDSpace, kEyeDropperRIDXHandlerImpl, kEyeDropperToolPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperRIDXReplaceStyleCmdImpl, kEyeDropperToolPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperRIDXReplaceTextAttrsCmdImpl, kEyeDropperToolPrefix + 104)
// gap

DECLARE_PMID(kImplementationIDSpace, kColorThemeToolImpl, kEyeDropperToolPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolTrackerImpl, kEyeDropperToolPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolTrackerRegisterImpl, kEyeDropperToolPrefix + 203)
//gap
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolCursorProviderImpl, kEyeDropperToolPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kColorThemeAppDataImpl, kEyeDropperToolPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolObserverImpl, kEyeDropperToolPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kColorThemeSwatchDataImpl, kEyeDropperToolPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolMouseWatcherImpl, kEyeDropperToolPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolEventWatcherImpl, kEyeDropperToolPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPanelMgrImpl, kEyeDropperToolPrefix + 214) 
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolDialogControllerImpl, kEyeDropperToolPrefix + 215) 
DECLARE_PMID(kImplementationIDSpace, kColorThemeElementViewImpl, kEyeDropperToolPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolDialogObserverImpl, kEyeDropperToolPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kColorThemeElementViewEHImpl, kEyeDropperToolPrefix + 218)

DECLARE_PMID(kImplementationIDSpace, kColorThemeDropperSuiteImpl, kEyeDropperToolPrefix + 219)

DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelWidgetAttributesImpl, kEyeDropperToolPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelTreeViewAdapterImpl, kEyeDropperToolPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelPanelTreeWidgetMgrImpl, kEyeDropperToolPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelTreeNodeControlViewImpl, kEyeDropperToolPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelTreeNodeMouseRolloverImpl, kEyeDropperToolPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelTreeNodeEHImpl, kEyeDropperToolPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPanelWindowImpl, kEyeDropperToolPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPanelViewImpl, kEyeDropperToolPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolGripperViewImpl, kEyeDropperToolPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelPanelTreeObserverImpl, kEyeDropperToolPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kColorThemeAddToSwatchButtonTipImpl, kEyeDropperToolPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelButtonTipImpl, kEyeDropperToolPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kColorThemeElementTipImpl, kEyeDropperToolPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPrefsImpl, kEyeDropperToolPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kSetColorThemeToolPrefsCmdImpl, kEyeDropperToolPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kSetColorThemeToolPrefsCmdDataImpl, kEyeDropperToolPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kColorThemeOptionsDlgControllerImpl, kEyeDropperToolPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kThemeColorDDSourceImpl, kEyeDropperToolPrefix + 237)
// gap
DECLARE_PMID(kImplementationIDSpace, kColorThemeExportToCCLibrariesButtonTipImpl, kEyeDropperToolPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kColorCloudConnectionCacheImpl, kEyeDropperToolPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kColorCloudIMSIdleTaskImpl, kEyeDropperToolPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kColorCloudConnectionStartupShutdownImpl, kEyeDropperToolPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kColorCloudImpl, kEyeDropperToolPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kColorThemeToolStartupShutdownImpl, kEyeDropperToolPrefix + 245)

// Transform Attributes
DECLARE_PMID(kImplementationIDSpace, kEyeTransformAttrFilterImpl, kEyeDropperToolPrefix + 246)

DECLARE_PMID(kImplementationIDSpace, kColorThemeToolPopupPanelViewImpl, kEyeDropperToolPrefix + 247)


// <Widget ID>
// Character attribute widgets <1-50>
DECLARE_PMID(kWidgetIDSpace, kCharAttrEnableCheckBoxWidgetId, kEyeDropperToolPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kCharAttrFontCheckBoxWidgetId, kEyeDropperToolPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kCharAttrSizeCheckBoxWidgetId, kEyeDropperToolPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kCharAttrColorTintCheckBoxWidgetId, kEyeDropperToolPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kCharGroupWidgetId, kEyeDropperToolPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kCharBorderWidget, kEyeDropperToolPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kCharAttributesOnWidget, kEyeDropperToolPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kCharStylesCheckBoxWidgetId, kEyeDropperToolPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kCharAttrLeadCheckBoxWidgetId, kEyeDropperToolPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kCharAttrKernTrackCheckBoxWidgetId, kEyeDropperToolPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kCharAttrCapsPositionkCheckBoxWidgetId, kEyeDropperToolPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kCharAttrUnderlineCheckBoxWidgetId, kEyeDropperToolPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCharAttrStrikeCheckBoxWidgetId, kEyeDropperToolPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCharAttrLigOldStyleCheckBoxWidgetId, kEyeDropperToolPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kCharAttrScaleSkewCheckBoxWidgetId, kEyeDropperToolPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kCharAttrBLShiftCheckBoxWidgetId, kEyeDropperToolPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kCharAttrLanguageCheckBoxWidgetId, kEyeDropperToolPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kCharAttrNoBreaksCheckBoxWidgetId, kEyeDropperToolPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kCharAttrOutlineCheckBoxWidgetId, kEyeDropperToolPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kCharAttrOpenTypeCheckBoxWidgetId, kEyeDropperToolPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kCharAttrCJKOpenTypeCheckBoxWidgetId, kEyeDropperToolPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kCharAttrOutlineJoinCheckBoxWidgetId, kEyeDropperToolPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kCharAttrStrokeAlignCheckBoxWidgetId, kEyeDropperToolPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kCharAttrMiterLimitCheckBoxWidgetId, kEyeDropperToolPrefix + 24)

// Paragraph attribute widgets <51-100>
DECLARE_PMID(kWidgetIDSpace, kParaAttrEnableCheckBoxWidgetId, kEyeDropperToolPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kParaGroupWidgetId, kEyeDropperToolPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kParaBorderWidget, kEyeDropperToolPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kParaAttributesOnWidget, kEyeDropperToolPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kParaRulesCheckBoxWidgetId, kEyeDropperToolPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kParaStylesCheckBoxWidgetId, kEyeDropperToolPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kParaKeepsCheckBoxWidgetId, kEyeDropperToolPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kParaHyphenCheckBoxWidgetId, kEyeDropperToolPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kParaJustCheckBoxWidgetId, kEyeDropperToolPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kParaTabsCheckBoxWidgetId, kEyeDropperToolPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kParaAlignCheckBoxWidgetId, kEyeDropperToolPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kParaIndentsCheckBoxWidgetId, kEyeDropperToolPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kParaSpacingCheckBoxWidgetId, kEyeDropperToolPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kParaDropCapsCheckBoxWidgetId, kEyeDropperToolPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kParaComposerCheckBoxWidgetId, kEyeDropperToolPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kParaBLGridCheckBoxWidgetId, kEyeDropperToolPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kParaBulletsCheckBoxWidgetId, kEyeDropperToolPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kParaSpanColumnsCheckBoxWidgetId, kEyeDropperToolPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kParaShadingCheckBoxWidgetId, kEyeDropperToolPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kParaBorderCheckBoxWidgetId, kEyeDropperToolPrefix + 70)

// Fill attribute widgets <101-150>
DECLARE_PMID(kWidgetIDSpace, kFillGroupWidgetId, kEyeDropperToolPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kFillBorderWidget, kEyeDropperToolPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kFillAttributesOnWidget, kEyeDropperToolPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kFillAttrEnableCheckBoxWidgetId, kEyeDropperToolPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kFillAttrColorCheckBoxWidgetId, kEyeDropperToolPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kFillAttrOverprintCheckBoxWidgetId, kEyeDropperToolPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kFillColorAndTintCheckBoxWidgetId, kEyeDropperToolPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kFillOverprintCheckBoxWidgetId, kEyeDropperToolPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kFillTransparencyWidgetId, kEyeDropperToolPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kFillEffectsWidgetId, kEyeDropperToolPrefix + 110)

// Color theme tool
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolWidgetId, kEyeDropperToolPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPanelSeperatorWidgetID, kEyeDropperToolPrefix +132)
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolOptionsDlgWidgetID, kEyeDropperToolPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kCTOptionsDiscardEffectsCheckboxWidgetID, kEyeDropperToolPrefix +134) 
DECLARE_PMID(kWidgetIDSpace, kCTOptionsDropDownWidgetID, kEyeDropperToolPrefix +135)
DECLARE_PMID(kWidgetIDSpace, kCTOptionsDropDownTextWidgetID, kEyeDropperToolPrefix +136)

// Stroke attribute widgets <151-180>
DECLARE_PMID(kWidgetIDSpace, kStrokeGroupWidgetId, kEyeDropperToolPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kStrokeBorderWidget, kEyeDropperToolPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttributesOnWidget, kEyeDropperToolPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrEnableCheckBoxWidgetId, kEyeDropperToolPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrColorCheckBoxWidgetId, kEyeDropperToolPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrOverprintCheckBoxWidgetId, kEyeDropperToolPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrLineCapCheckBoxWidgetId, kEyeDropperToolPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrJoinCheckBoxWidgetId, kEyeDropperToolPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrMiterCheckBoxWidgetId, kEyeDropperToolPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrLineCheckBoxWidgetId, kEyeDropperToolPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kStrokeAttrCornersCheckBoxWidgetId, kEyeDropperToolPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kStrokeColorAndTintCheckBoxWidgetId, kEyeDropperToolPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kStrokeOverprintCheckBoxWidgetId, kEyeDropperToolPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kStrokeWeightCheckBoxWidgetId, kEyeDropperToolPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kStrokeCapCheckBoxWidgetId, kEyeDropperToolPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kStrokeJoinCheckBoxWidgetId, kEyeDropperToolPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kStrokeMiterLimitCheckBoxWidgetId, kEyeDropperToolPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kStrokeDashCheckBoxWidgetId, kEyeDropperToolPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignmentCheckBoxWidgetId, kEyeDropperToolPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kStrokeStartCheckBoxWidgetId, kEyeDropperToolPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kStrokeEndCheckBoxWidgetId, kEyeDropperToolPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kStrokeCornerEffectsWidgetId, kEyeDropperToolPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kStrokeTransparencyWidgetId, kEyeDropperToolPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kStrokeEffectsWidgetId, kEyeDropperToolPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kGraphicStyleArrowHeadAlignmentCheckBoxWidgetId, kEyeDropperToolPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kGraphicStyleArrowHeadStartScaleCheckBoxWidgetId, kEyeDropperToolPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kGraphicStyleArrowHeadEndScaleCheckBoxWidgetId, kEyeDropperToolPrefix + 177)


// CJK character attribute widgets <181-200>
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharPrefsWidgetID, kEyeDropperToolPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharAttrGroupWidgetId, kEyeDropperToolPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharAttrBorderWidgetId, kEyeDropperToolPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharAttrOnWidgetId, kEyeDropperToolPrefix + 184)

DECLARE_PMID(kWidgetIDSpace, kCJKEyeTatechuyokoWidgetId, kEyeDropperToolPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeKentenWidgetId, kEyeDropperToolPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeWarichuWidgetId, kEyeDropperToolPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeShataiWidgetId, kEyeDropperToolPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeTsumeWidgetId, kEyeDropperToolPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeJidoriWidgetId, kEyeDropperToolPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharRotationWidgetId, kEyeDropperToolPrefix + 191)
//obsolete DECLARE_PMID(kWidgetIDSpace, kCJKEyeGridAlignmentWidgetId, kEyeDropperToolPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeForcedAkiWidgetId, kEyeDropperToolPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeCharacterHangWidgetId, kEyeDropperToolPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeRubiWidgetId, kEyeDropperToolPrefix + 195)

// CJK paragraph attribute widgets <201-220>
DECLARE_PMID(kWidgetIDSpace, kCJKEyeParaPrefsWidgetID, kEyeDropperToolPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeParaAttrGroupWidgetId, kEyeDropperToolPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeParaAttrBorderWidgetId, kEyeDropperToolPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeParaAttrOnWidgetId, kEyeDropperToolPrefix + 204)

DECLARE_PMID(kWidgetIDSpace, kCJKEyeAlignFirstWidgetId, kEyeDropperToolPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeKumiNumberWidgetId, kEyeDropperToolPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeKinsokuWidgetId, kEyeDropperToolPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeMojikumiWidgetId, kEyeDropperToolPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeGyoudoriWidgetId, kEyeDropperToolPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeRotateRomanWidgetId, kEyeDropperToolPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeRensuujiWidgetId, kEyeDropperToolPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeBunriKinshiCheckBoxWidgetId, kEyeDropperToolPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeUseCenteredLeadingCheckBoxWidgetId, kEyeDropperToolPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeIdeoSpaceBehaviorCheckBoxWidgetId, kEyeDropperToolPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kCJKEyeWordWrapOffCheckBoxWidgetId, kEyeDropperToolPrefix + 215)

// Other widgets <220 and up>
DECLARE_PMID(kWidgetIDSpace, kEyeDropperParentWidgetID, kEyeDropperToolPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperGroupPanelWidgetID, kEyeDropperToolPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperBorderWidgetID, kEyeDropperToolPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolWidgetId, kEyeDropperToolPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperCharPrefsWidgetID, kEyeDropperToolPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperParaPrefsWidgetID, kEyeDropperToolPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperStrokePrefsWidgetID, kEyeDropperToolPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperFillPrefsWidgetID, kEyeDropperToolPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperPrefsPopupGroupWidgetID, kEyeDropperToolPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperProxyAlertWidgetID, kEyeDropperToolPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperVectorAlertWidgetID, kEyeDropperToolPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperBlackBoxFillAlertWidgetID, kEyeDropperToolPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPanelWidgetID, kEyeDropperToolPrefix + 232) 
DECLARE_PMID(kWidgetIDSpace, kCTGripperContainerWidgetID, kEyeDropperToolPrefix +233)
DECLARE_PMID(kWidgetIDSpace, kCTGripperWidgetID, kEyeDropperToolPrefix +234) 
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPopupButtonWidgetId, kEyeDropperToolPrefix +235) 
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPopupPanelWidgetID, kEyeDropperToolPrefix +236) 
DECLARE_PMID(kWidgetIDSpace, kCTAddToSwatchButtonWidgetID, kEyeDropperToolPrefix +237) 
DECLARE_PMID(kWidgetIDSpace, kCTTilesNButtonsContainerWidgetID, kEyeDropperToolPrefix +238)
DECLARE_PMID(kWidgetIDSpace, kColorTilesContainerWidgetID, kEyeDropperToolPrefix +239) 


// Tree widgets
DECLARE_PMID(kWidgetIDSpace, kEyeDropperTreeWidgetID, kEyeDropperToolPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperTreeLeafWidgetId, kEyeDropperToolPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperTreeBranchWidgetId, kEyeDropperToolPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeCheckBoxWidgetId, kEyeDropperToolPrefix + 243)

// Object Widgets
DECLARE_PMID(kWidgetIDSpace, kObjectAttrPrefsWidgetId, kEyeDropperToolPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kObjectAttrTransparencyWidgetId, kEyeDropperToolPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kObjectAttrEffectsWidgetId, kEyeDropperToolPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kObjectAttrTextTransparencyWidgetId, kEyeDropperToolPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kObjectAttrTextEffectsWidgetId, kEyeDropperToolPrefix + 249)


// Table Widgets
DECLARE_PMID(kWidgetIDSpace, kTableAttrOnWidgetId, kEyeDropperToolPrefix + 250)

DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPopupPanelTreeWidgetID, kEyeDropperToolPrefix +251)
DECLARE_PMID(kWidgetIDSpace, kColorThemeToolPopupPanelTreeElementWidgetID, kEyeDropperToolPrefix +252)
// gap
DECLARE_PMID(kWidgetIDSpace, kCTExportToCCLibrariesButtonWidgetID, kEyeDropperToolPrefix + 254)

//DO NOT GO ABOVE 255!!!
// WE WONT GO. I DEFINED ANOTHER PREFIX. :)

// Transform Attribute Options
DECLARE_PMID(kWidgetIDSpace, kTransformAttrDimensionCheckBoxWidgetID, kEyeDropperToolPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrPositionCheckBoxWidgetID, kEyeDropperToolPrefix2 + 2)




// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kEyeDropperPrefsPanelServiceImpl, kEyeDropperToolPrefix + 1)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kEyeDropperToolActionID, kEyeDropperToolPrefix + 1)
DECLARE_PMID(kActionIDSpace, kColorThemeToolActionID, kEyeDropperToolPrefix + 2)

// <ViewPortAttr ID>
// ViewPortAttrIDs
DECLARE_PMID(kViewPortAttrIDSpace, kAllowObjectDrawOptionOverrides, kEyeDropperToolPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kDrawGraphicsAtleastAsProxy, kEyeDropperToolPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kDoNotDrawPageFillAndStroke, kEyeDropperToolPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kDrawNonPrintingInPreviewMode, kEyeDropperToolPrefix + 4)

#endif
