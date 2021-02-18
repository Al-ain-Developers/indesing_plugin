//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/OutPrvID.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __SepPrvID__
#define __SepPrvID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kOutPrvPrefix	 	RezLong(0x11900)		//Refer also to AdobePrefix.h
#define kOutPrvPluginName "Output Preview"

// <Start IDC>
// PluginIDs

DECLARE_PMID(kPlugInIDSpace, kOutPrvPluginID,						kOutPrvPrefix + 1)

// <Class ID>
// ClassIDs (i.e. bosses)

DECLARE_PMID(kClassIDSpace, kSepPrvPaletteBoss,						kOutPrvPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSepPrvListElementBoss,					kOutPrvPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSepPrvStateIconButtonBoss,				kOutPrvPrefix + 3)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kSepPrvPlateViewBoss,					kOutPrvPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSepPrvDrwEvtHandlerBoss,				kOutPrvPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSepPrvAppMenuActionBoss,				kOutPrvPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSepPrvWindowTitleServiceBoss,			kOutPrvPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSepPrvPaletteMenuActionBoss,			kOutPrvPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSepPrvEyeDEHandlerBoss,				kOutPrvPrefix + 9)

DECLARE_PMID(kClassIDSpace, kFlatPrvPaletteBoss,					kOutPrvPrefix + 10)
DECLARE_PMID(kClassIDSpace, kFlatPrvDrwEvtHandlerBoss,				kOutPrvPrefix + 11)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kFlatPrvViewPortBoss,					kOutPrvPrefix + 12)
DECLARE_PMID(kClassIDSpace, kFlatPrvMenuActionBoss,					kOutPrvPrefix + 13)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kFlatPrvPrefsDlgBoss,					kOutPrvPrefix + 14)
DECLARE_PMID(kClassIDSpace, kFlatPrvWindowTitleServiceBoss,			kOutPrvPrefix + 15)

DECLARE_PMID(kClassIDSpace, kFrontWindowProxyBoss,					kOutPrvPrefix + 20)
DECLARE_PMID(kClassIDSpace, kOutPrvStartupServiceBoss,				kOutPrvPrefix + 21)
DECLARE_PMID(kClassIDSpace, kOutPrvWindowScrProvBoss,				kOutPrvPrefix + 22)

DECLARE_PMID(kClassIDSpace, kFlatPrvSetWindowPrefsCmdBoss,			kOutPrvPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSepPrvSetWindowPrefsCmdBoss,			kOutPrvPrefix + 24)

// Note: These aren't true bosses; they're just classIDs for subject changes to windows...
DECLARE_PMID(kClassIDSpace, kFrontWindowChangedMsg,					kOutPrvPrefix + 50)
DECLARE_PMID(kClassIDSpace, kFrontDocChangedMsg,					kOutPrvPrefix + 51)

DECLARE_PMID(kClassIDSpace, kSepPrvChangedModeMsg,					kOutPrvPrefix + 60)
DECLARE_PMID(kClassIDSpace, kSepPrvChangedShowPlateMsg,				kOutPrvPrefix + 61)
DECLARE_PMID(kClassIDSpace, kSepPrvChangedInkLimitMsg,				kOutPrvPrefix + 62)
DECLARE_PMID(kClassIDSpace, kSepPrvChangedBlackSaturationMsg,		kOutPrvPrefix + 63)
DECLARE_PMID(kClassIDSpace, kSepPrvChangedSinglePlateAsBlackMsg,	kOutPrvPrefix + 64)
DECLARE_PMID(kClassIDSpace, kSepPrvChangedHalftoneLPIMsg,			kOutPrvPrefix + 65)

DECLARE_PMID(kClassIDSpace, kFlatPrvChangedModeMsg,					kOutPrvPrefix + 70)
DECLARE_PMID(kClassIDSpace, kFlatPrvChangedViewEventMsg,			kOutPrvPrefix + 71)
DECLARE_PMID(kClassIDSpace, kFlatPrvRefreshEventsMsg,				kOutPrvPrefix + 72)
DECLARE_PMID(kClassIDSpace, kFlatPrvChangedHighlightSettingsMsg,	kOutPrvPrefix + 73)


// <Interface ID>
// IIDs

DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVWINDOWSETTINGS,			kOutPrvPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVPALETTECONTROLLER,		kOutPrvPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVPLATEVIEWDATA,			kOutPrvPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVMANAGER,					kOutPrvPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVGLOBALOBSERVER,			kOutPrvPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVIDLETASK,				kOutPrvPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPPRVOPPIMAGECACHE,			kOutPrvPrefix + 7)

DECLARE_PMID(kInterfaceIDSpace, IID_IFLATPRVWINDOWSETTINGS,			kOutPrvPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATPRVPALETTECONTROLLER,		kOutPrvPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRONTWINDOWPROXY,				kOutPrvPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATPRVMANAGER,				kOutPrvPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATPRVIDLETASK,				kOutPrvPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATPRVGLOBALOBSERVER,			kOutPrvPrefix + 15)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)

DECLARE_PMID(kImplementationIDSpace, kSepPrvWindowSettingsImpl,		kOutPrvPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPaletteViewImpl,		kOutPrvPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSepPrvStateIconButtonEHImpl,	kOutPrvPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSepPrvCursorProviderImpl,		kOutPrvPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPaletteObserverImpl,	kOutPrvPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPlateViewImpl,			kOutPrvPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPlateViewDataImpl,		kOutPrvPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPaletteControllerImpl,	kOutPrvPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSepPrvManagerImpl,			kOutPrvPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSepPrvDrwEvtHandlerImpl,		kOutPrvPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSepPrvDrwEvtServiceImpl,		kOutPrvPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSepPrvAppMenuActionImpl,		kOutPrvPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSepPrvWindowTitleServiceImpl,	kOutPrvPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSepPrvWindowTitleProviderImpl,kOutPrvPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSepPrvIdleTaskImpl,			kOutPrvPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSepPrvMouseWatcherImpl,		kOutPrvPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPaletteMenuActionImpl,	kOutPrvPrefix + 18)

DECLARE_PMID(kImplementationIDSpace, kFlatPrvPaletteControllerImpl,	kOutPrvPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvPaletteObserverImpl,	kOutPrvPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvWindowSettingsImpl,	kOutPrvPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvDrwEvtServiceImpl, 	kOutPrvPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvDrwEvtHandlerImpl, 	kOutPrvPrefix + 24)
//OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kFlatPrvViewPortAttrImpl,	 	kOutPrvPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvManagerImpl,	 		kOutPrvPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvIdleTaskImpl,			kOutPrvPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvMenuActionImpl,		kOutPrvPrefix + 28)
//OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kFlatPrvPrefsDlgControllerImpl,kOutPrvPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvGlobalObserverImpl,	kOutPrvPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvSetWindowPrefsCmdImpl,	kOutPrvPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvWindowPrefsImpl,		kOutPrvPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvWindowTitleServiceImpl,kOutPrvPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kFlatPrvWindowTitleProviderImpl,kOutPrvPrefix + 34)

DECLARE_PMID(kImplementationIDSpace, kFrontWindowProxyImpl,			kOutPrvPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kFrontWindowProxyObserverImpl,	kOutPrvPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kFrontWindowProxySubjectImpl,	kOutPrvPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kOutPrvStartupServiceImpl,		kOutPrvPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kOutPrvStartupShutdownImpl,	kOutPrvPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kOutPrvWindowScrProvImpl,		kOutPrvPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kSepPrvEyeDEHandlerImpl,		kOutPrvPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSepPrvEyeDDSourceImpl,		kOutPrvPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kSepPrvEyeDDTargetImpl,		kOutPrvPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSepPrvEyeObserverImpl,		kOutPrvPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSepPrvPlateEHImpl,			kOutPrvPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSepPrvGlobalObserverImpl,		kOutPrvPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSepPrvSetWindowPrefsCmdImpl,	kOutPrvPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSepPrvWindowPrefsImpl,		kOutPrvPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSepPrvOPPImageCacheImpl,		kOutPrvPrefix + 58)

// <Action ID>
// Action IDs

DECLARE_PMID(kActionIDSpace, kSepPrvMAID_Palette, 					kOutPrvPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSepPrvOverprintPreviewMAID, 			kOutPrvPrefix + 2)
DECLARE_PMID(kActionIDSpace, kSepPrvOPPSeparatorMAID, 				kOutPrvPrefix + 3)
DECLARE_PMID(kActionIDSpace, kSepPrvDesaturateBlackMAID, 			kOutPrvPrefix + 4)
DECLARE_PMID(kActionIDSpace, kSepPrvInkManagerMAID,					kOutPrvPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSepPrvSinglePlateAsBlackMAID,			kOutPrvPrefix + 6)

DECLARE_PMID(kActionIDSpace, kFlatPrvMAID_Palette, 					kOutPrvPrefix + 10)
DECLARE_PMID(kActionIDSpace, kFlatPrvPalettePreferencesMAID,		kOutPrvPrefix + 11)
DECLARE_PMID(kActionIDSpace, kFlatPrvEditStylesMAID,				kOutPrvPrefix + 12)

DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateAll,				kOutPrvPrefix + 20)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateCyan,				kOutPrvPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateMagenta,			kOutPrvPrefix + 22)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateYellow,			kOutPrvPrefix + 23)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateBlack,			kOutPrvPrefix + 24)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateSpot1,			kOutPrvPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateSpot2,			kOutPrvPrefix + 26)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateSpot3,			kOutPrvPrefix + 27)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateSpot4,			kOutPrvPrefix + 28)
DECLARE_PMID(kActionIDSpace, kSepPrvMAID_ShowPlateSpot5,			kOutPrvPrefix + 29)
DECLARE_PMID(kActionIDSpace, kSepPrvHalftoneNoneMAID,				kOutPrvPrefix + 30)
DECLARE_PMID(kActionIDSpace, kSepPrvHalftone100MAID,				kOutPrvPrefix + 31)
DECLARE_PMID(kActionIDSpace, kSepPrvHalftone175MAID,				kOutPrvPrefix + 32)
DECLARE_PMID(kActionIDSpace, kSepPrvHalftone200MAID,				kOutPrvPrefix + 33)

// <Widget ID>
// Widget IDs

DECLARE_PMID(kWidgetIDSpace, kSepPrvPaletteWID,						kOutPrvPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kSepPrvModeLabelWID,					kOutPrvPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kSepPrvModePopupWID,					kOutPrvPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSepPrvPlateListWID,					kOutPrvPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kSepPrvControlStripWID,				kOutPrvPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kSepPrvTopStripWID,					kOutPrvPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSepPrvInkLimitWID,					kOutPrvPrefix + 7)

DECLARE_PMID(kWidgetIDSpace, kSepPrvListElementWID,					kOutPrvPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kSepPrvListElemStateIconWID,			kOutPrvPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSepPrvListElemPercentWID,		   	    kOutPrvPrefix + 12)

// Flattener Preview IDs
DECLARE_PMID(kWidgetIDSpace, kFlatPrvPaletteWID,					kOutPrvPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvLblHighlightWID,				kOutPrvPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvPopHighlightWID,				kOutPrvPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvChkAutoRefreshWID,				kOutPrvPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvBtnRefreshWID,					kOutPrvPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvSep2WID,						kOutPrvPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvLblStyleWID,					kOutPrvPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvPopStyleWID,					kOutPrvPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvChkIgnoreOverridesWID,			kOutPrvPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kFlatPrvBtnApplyWID,					kOutPrvPrefix + 31)

//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsDlgWID,					kOutPrvPrefix + 50)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsLblColorGrayWID,			kOutPrvPrefix + 51)
//OBSOLETE: //OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsPopColorGrayWID,			kOutPrvPrefix + 52)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsLblContentOpacityWID,		kOutPrvPrefix + 53)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsEdtContentOpacityWID,		kOutPrvPrefix + 54)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsLblHighlightOpacityWID,	kOutPrvPrefix + 55)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsEdtHighlightOpacityWID,	kOutPrvPrefix + 56)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsPopNoCacheDisplayWID,		kOutPrvPrefix + 57)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsLblNoCacheDisplayWID,		kOutPrvPrefix + 58)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsPopOpaqueSpreadDisplayWID,kOutPrvPrefix + 59)
//OBSOLETE: DECLARE_PMID(kWidgetIDSpace, kFlatPrvPrefsLblOpaqueSpreadDisplayWID,kOutPrvPrefix + 60)

// Note: These are used with the FlatPrvViewPortAttributes interface to allow setting and getting
// of all of these values without having to use the "old fashioned" method-based get/setters.
// This in turn simplifies a number of other interfaces..

DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvResolutionVPAttr,			kOutPrvPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvOutputOPICommentsVPAttr,		kOutPrvPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvCacheingVPAttr,				kOutPrvPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvBitmapSamplingVPAttr,		kOutPrvPrefix + 4)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvVectorSamplingVPAttr,		kOutPrvPrefix + 5)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvFilterContentVPAttr,			kOutPrvPrefix + 6)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvLineScreenVPAttr,			kOutPrvPrefix + 7)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvTilingVPAttr,				kOutPrvPrefix + 8)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvProofPrintVPAttr,			kOutPrvPrefix + 9)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvDisallowImageCropVPAttr,		kOutPrvPrefix + 10)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvOmitEPSVPAttr,				kOutPrvPrefix + 11)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvOmitPDFVPAttr,				kOutPrvPrefix + 12)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvOmitBitmapImagesVPAttr,		kOutPrvPrefix + 13)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvDrawPasteboardShadowVPAttr,	kOutPrvPrefix + 14)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvDrawPageShadowVPAttr,		kOutPrvPrefix + 15)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvIsPrintingPortVPAttr,		kOutPrvPrefix + 16)
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvIsPrivatePortVPAttr,			kOutPrvPrefix + 17)

// Now for the real vpattrs.. this one lets anyone who cares (image plugin currently)
// know that we're doing a flattener preview.
DECLARE_PMID(kViewPortAttrIDSpace, kFlatPrvActiveVPAttr,				kOutPrvPrefix + 18)

// This one's for separation preview, and whether we're in single-plate-black mode.
// The latter is a hint to the logic in the page pageitem when deciding whether or not
// to draw the page background in paper color.
DECLARE_PMID(kViewPortAttrIDSpace, kSepPrvOPPEnabledVPAttr,				kOutPrvPrefix + 20)
DECLARE_PMID(kViewPortAttrIDSpace, kSepPrvForceOPPPaperColorVPAttr,		kOutPrvPrefix + 21)

// Scripting IDs
DECLARE_PMID(kScriptInfoIDSpace, kSepPrvOPPScriptID,					kOutPrvPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSepPrvModeScriptID,					kOutPrvPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kSepPrvModeEnumScriptID,				kOutPrvPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kSepPrvInkLimitScriptID,				kOutPrvPrefix + 4)

// Warning ID's (for don't-show-agains)
const int32 kOPPRGBConflictWarningID = kOutPrvPrefix + 1;

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kFlatPrvCacheInvalHandlerID, kOutPrvPrefix + 1)


#endif // __SepPrvID__


