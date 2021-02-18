//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/InfoPanelID.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//  Contains IDs used by measure tool which is combined in the basic tools project.
//  
//========================================================================================

#ifndef __INFOPANELID__
#define __INFOPANELID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInfoPanelPrefix	 RezLong(0x15C00)
#define kInfoPanel2Prefix	 RezLong(0x17D00)

// PluginID
#define kInfoPanelPluginName			"Info Panel"
START_IDS()

DECLARE_PMID(kPlugInIDSpace, kInfoPanelPluginID, kInfoPanelPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kInfoPanelBoss,					kInfoPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace, kInfoPanelWidgetBoss,			kInfoPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDefaultInfoPanelWidgetBoss,	kInfoPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kScaleToolInfoPanelWidgetBoss,	kInfoPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kRotateToolInfoPanelWidgetBoss,	kInfoPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kShearToolInfoPanelWidgetBoss,  kInfoPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kEyeDropperToolInfoPanelWidgetBoss,		kInfoPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGradientToolInfoPanelWidgetBoss,		kInfoPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kFreeTransformToolInfoPanelWidgetBoss,  kInfoPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kFrameGridHorzToolInfoPanelWidgetBoss,	kInfoPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kFrameGridVertToolInfoPanelWidgetBoss,	kInfoPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kZoomToolPanelWidgetBoss,				kInfoPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kMeasureToolInfoPanelWidgetBoss,		kInfoPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kPenToolInfoPanelWidgetBoss,			kInfoPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kTypeToolSelInfoPanelWidgetBoss,		kInfoPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTypeToolNonSelInfoPanelWidgetBoss,		kInfoPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kIBeamToolSelPanelWidgetBoss,			kInfoPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kIBeamToolNonSelPanelWidgetBoss,		kInfoPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kVertTextToolSelPanelWidgetBoss,		kInfoPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kVertTextToolNonSelPanelWidgetBoss,		kInfoPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kTOPHorzToolPanelWidgetBoss,			kInfoPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kTOPVertToolPanelWidgetBoss,			kInfoPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSelectToolSelInfoPanelWidgetBoss,		kInfoPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSelectToolNonSelInfoPanelWidgetBoss,	kInfoPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kPointerToolSelInfoPanelWidgetBoss,		kInfoPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kPointerToolNonSelInfoPanelWidgetBoss,	kInfoPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kDirectSelectionToolSelInfoPanelWidgetBoss,		kInfoPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kDirectSelectionToolNonSelInfoPanelWidgetBoss,	kInfoPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kCreationToolPanelWidgetBoss,					kInfoPanelPrefix + 29)
DECLARE_PMID(kClassIDSpace, kCreationToolPanelMenuComponentBoss,			kInfoPanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kFillStrokeColorInfoPanelWidgetBoss,			kInfoPanelPrefix + 31)
DECLARE_PMID(kClassIDSpace, kRGBColorInfoWidgetBoss,				kInfoPanelPrefix + 32)
DECLARE_PMID(kClassIDSpace, kCMYKColorInfoWidgetBoss,				kInfoPanelPrefix + 33)
DECLARE_PMID(kClassIDSpace, kLABColorInfoWidgetBoss,				kInfoPanelPrefix + 34)
DECLARE_PMID(kClassIDSpace, kNamedColorInfoWidgetBoss,				kInfoPanelPrefix + 35)
DECLARE_PMID(kClassIDSpace, kInfoPanelStartupShutdownBoss,			kInfoPanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kRectToolPanelWidgetBoss,				kInfoPanelPrefix + 37)
DECLARE_PMID(kClassIDSpace, kRectFrameToolPanelWidgetBoss,			kInfoPanelPrefix + 38)
DECLARE_PMID(kClassIDSpace, kLineToolPanelWidgetBoss,				kInfoPanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kOvalToolPanelWidgetBoss,				kInfoPanelPrefix + 40)
DECLARE_PMID(kClassIDSpace, kOvalFrameToolPanelWidgetBoss,			kInfoPanelPrefix + 41)
DECLARE_PMID(kClassIDSpace, kRegPolyToolPanelWidgetBoss,			kInfoPanelPrefix + 42)
DECLARE_PMID(kClassIDSpace, kRegPolyFrameToolPanelWidgetBoss,		kInfoPanelPrefix + 43)
DECLARE_PMID(kClassIDSpace, kInfoPanelMenuComponentBoss,			kInfoPanelPrefix + 44)
DECLARE_PMID(kClassIDSpace, kFooToolInfoPanelWidgetBoss,			kInfoPanelPrefix + 45)	// test
DECLARE_PMID(kClassIDSpace, kPencilToolPanelWidgetBoss,				kInfoPanelPrefix + 46)
DECLARE_PMID(kClassIDSpace, kInfoPanelToolTipWidgetBoss,			kInfoPanelPrefix + 47)
DECLARE_PMID(kClassIDSpace, kInfoPanelFillColorPopupMenuActionBoss,	kInfoPanelPrefix + 48)
DECLARE_PMID(kClassIDSpace, kInfoPanelStrokeColorPopupMenuActionBoss,kInfoPanelPrefix + 49)
DECLARE_PMID(kClassIDSpace, kPushButtonToolPanelWidgetBoss,			kInfoPanelPrefix + 50)
DECLARE_PMID(kClassIDSpace, kInfoPanelFillStrokeContainerBoss,		kInfoPanelPrefix + 51)
DECLARE_PMID(kClassIDSpace, kInfoPanelMultiLineToolTipWidgetBoss,	kInfoPanelPrefix + 52)
DECLARE_PMID(kClassIDSpace, kSmoothToolPanelWidgetBoss,				kInfoPanelPrefix + 53)
DECLARE_PMID(kClassIDSpace, kEraseToolPanelWidgetBoss,				kInfoPanelPrefix + 54)
DECLARE_PMID(kClassIDSpace, kScissorsToolPanelWidgetBoss,			kInfoPanelPrefix + 55)
DECLARE_PMID(kClassIDSpace, kSplineAddPointToolPanelWidgetBoss,		kInfoPanelPrefix + 56)
DECLARE_PMID(kClassIDSpace, kSplineRemovePointToolPanelWidgetBoss,	kInfoPanelPrefix + 57)
DECLARE_PMID(kClassIDSpace, kSplineDirectionToolPanelWidgetBoss,	kInfoPanelPrefix + 58)
DECLARE_PMID(kClassIDSpace, kMEToolSelPanelWidgetBoss,				kInfoPanelPrefix + 59)
DECLARE_PMID(kClassIDSpace, kMEToolNonSelPanelWidgetBoss,			kInfoPanelPrefix + 60)
DECLARE_PMID(kClassIDSpace, kTOPMEToolPanelWidgetBoss,				kInfoPanelPrefix + 61)
DECLARE_PMID(kClassIDSpace, kGapToolInfoPanelWidgetBoss,			kInfoPanelPrefix + 62)
DECLARE_PMID(kClassIDSpace, kHSBColorInfoWidgetBoss,                kInfoPanelPrefix + 63)
//gap
//droverised widgets
DECLARE_PMID(kClassIDSpace, kDV_SelectToolNonSelInfoPanelWidgetBoss,	kInfoPanelPrefix + 102)
DECLARE_PMID(kClassIDSpace, kDV_InfoPanelToolTipWidgetBoss,				kInfoPanelPrefix + 103)
DECLARE_PMID(kClassIDSpace, kDV_TypeToolSelInfoPanelWidgetBoss,			kInfoPanelPrefix + 104)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELSWITCHER,				kInfoPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELNONSELTOOLPROVIDER,	kInfoPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELSELTOOLPROVIDER,		kInfoPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELATTRIBUTES,			kInfoPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELUTILS,				kInfoPanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTINFOPANELPROTOCOL,		kInfoPanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTINFOPANELTOOLOBSERVER,  kInfoPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IROTATETOOLPANELPROTOCOL,		kInfoPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IROTATETOOLPANELOBSERVER,		kInfoPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORINFOPANELPROTOCOL,		kInfoPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALETOOLPANELPROTOCOL,		kInfoPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHEARTOOLPANELPROTOCOL,		kInfoPanelPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IEYEDROPPERTOOLPANELPROTOCOL,	kInfoPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTTOOLPANELPROTOCOL,		kInfoPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFREETRANSFORMTOOLPANELPROTOCOL,kInfoPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASURETOOLPANELPROTOCOL,		kInfoPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IZOOMTOOLPANELPROTOCOL,			kInfoPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IPENTOOLPANELPROTOCOL,			kInfoPanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPETOOLSELPANELPROTOCOL,		kInfoPanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPETOOLNONSELPANELPROTOCOL,	kInfoPanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTONTOOLSELPANELPROTOCOL,	kInfoPanelPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTONTOOLNONSELPANELPROTOCOL,kInfoPanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELDATA,					kInfoPanelPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELTOOLOBSERVER,			kInfoPanelPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATIONTOOLPROTOCOL,			kInfoPanelPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORINFOPANELATTRS,			kInfoPanelPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPETOOLTEXTSELECTIONOBSERVER,	kInfoPanelPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTOOLPANELPROTOCOL,			kInfoPanelPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELFILLSTROKEDATA,		kInfoPanelPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILEINFOSUITE,					kInfoPanelPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELFILLCOLORINFOENUMDATA,	kInfoPanelPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWITCHCOLORSPACEROTOCOL,		kInfoPanelPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IINFOPANELSTROKECOLORINFOENUMDATA,	kInfoPanelPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IORIGIPOINTDATA,			kInfoPanelPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONTOOLSUITE,		kInfoPanelPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IORIGPOINTINITIALIZED,		kInfoPanelPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESELECTTOOLSELPANEL,  kInfoPanelPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEDTOOLTIPDATA,			kInfoPanelPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IANCHORPOINTDATAINFO,		kInfoPanelPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IGAPTOOLPANELPROTOCOL,		kInfoPanelPrefix + 40)

// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kInfoPanelCreatorImpl,				kInfoPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelUtilsImpl,				kInfoPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelSwitcherImpl,			kInfoPanelPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kInfoPanelToolTipsImpl,			kInfoPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelAttributesImpl,			kInfoPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelObserverImpl,			kInfoPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kDefaultInfoPanelProviderImpl,		kInfoPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDefaultInfoPanelCreatorImpl,		kInfoPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kDefaultInfoPanelObserverImpl,		kInfoPanelPrefix + 10)
//gap
DECLARE_PMID(kImplementationIDSpace, kRotateToolPanelProviderImpl,		kInfoPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kRotateToolPanelCreatorImpl,		kInfoPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kRotateToolPanelObserverImpl,		kInfoPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kScaleToolPanelProviderImpl,		kInfoPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kScaleToolPanelCreatorImpl,		kInfoPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kScaleToolPanelObserverImpl,		kInfoPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kShearToolPanelProviderImpl,		kInfoPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kShearToolPanelCreatorImpl,		kInfoPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kShearToolPanelObserverImpl,		kInfoPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperToolPanelProviderImpl,	kInfoPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperToolPanelCreatorImpl,	kInfoPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperToolPanelObserverImpl,	kInfoPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGradientToolPanelProviderImpl,	kInfoPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kGradientToolPanelCreatorImpl,		kInfoPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGradientToolPanelObserverImpl,	kInfoPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformToolPanelProviderImpl,kInfoPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformToolPanelCreatorImpl, kInfoPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformToolPanelObserverImpl,kInfoPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kFrameGridHorzToolPanelProviderImpl,kInfoPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kFrameGridVertToolPanelProviderImpl,kInfoPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolPanelCreatorImpl,		kInfoPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolPanelObserverImpl,		kInfoPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolPanelProviderImpl,		kInfoPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kZoomToolPanelProviderImpl,		kInfoPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kFileInfoSuiteASBImpl,				kInfoPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kFileInfoSuiteDefaultCSBImpl,		kInfoPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kFileInfoSuiteLayoutCSBImpl,		kInfoPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPenToolPanelObserverImpl,			kInfoPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kPenToolPanelProviderImpl,			kInfoPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPenToolPanelCreatorImpl,			kInfoPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kTypeToolNonSelPanelObserverImpl,	kInfoPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kTypeToolSelPanelObserverImpl,		kInfoPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kTypeToolNonSelPanelCreatorImpl,	kInfoPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTypeToolSelPanelCreatorImpl,		kInfoPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kIBeamToolPanelProviderImpl,		kInfoPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kVertTextToolPanelProviderImpl,	kInfoPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kTOPHorzToolPanelProviderImpl,		kInfoPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTOPVertToolPanelProviderImpl,		kInfoPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSelectToolSelPanelCreatorImpl,	kInfoPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSelectToolSelPanelObserverImpl,	kInfoPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kSelectToolNonSelPanelCreatorImpl,	kInfoPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSelectToolNonSelPanelObserverImpl,kInfoPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPointerToolPanelProviderImpl,		kInfoPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kDirectSelectionToolPanelProviderImpl,	kInfoPanelPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelStartupShutdownImpl,     kInfoPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelDataImpl,				kInfoPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelToolObserverImpl,		kInfoPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCreationToolPanelCreatorImpl,		kInfoPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kCreationToolPanelObserverImpl,	kInfoPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kCreationToolPanelMenuComponentImpl,	kInfoPanelPrefix + 61)
//gap
DECLARE_PMID(kImplementationIDSpace, kFillStrokeColorInfoObserverImpl,		kInfoPanelPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kLABColorInfoPanelAttrsImpl,			kInfoPanelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kLABInfoWidgetCreatorImpl,				kInfoPanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kRGBColorInfoPanelAttrsImpl,			kInfoPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kRGBInfoWidgetCreatorImpl,				kInfoPanelPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kCMYKColorInfoPanelAttrsImpl,			kInfoPanelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kCMYKInfoWidgetCreatorImpl,			kInfoPanelPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kColorInfoWidgetServiceImpl,			kInfoPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kNamedColorInfoPanelAttrsImpl,			kInfoPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kNamedInfoWidgetCreatorImpl,			kInfoPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kRectToolPanelProviderImpl,		kInfoPanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kRectFrameToolPanelProviderImpl,   kInfoPanelPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kLineToolPanelProviderImpl,		kInfoPanelPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kOvalToolPanelProviderImpl,		kInfoPanelPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kOvalFrameToolPanelProviderImpl,	kInfoPanelPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kRegPolyToolPanelProviderImpl,		kInfoPanelPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kRegPolyFrameToolPanelProviderImpl,kInfoPanelPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelDetailControllerImpl,	kInfoPanelPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kDefaultPanelDetailControllerImpl,	kInfoPanelPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kMeassureToolPanelDetailControllerImpl,	kInfoPanelPrefix + 82)
//gap
DECLARE_PMID(kImplementationIDSpace, kRotateToolPanelDetailControllerImpl,		kInfoPanelPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kScaleToolPanelDetailControllerImpl,		kInfoPanelPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kShearToolPanelDetailControllerImpl,		kInfoPanelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperToolPanelDetailControllerImpl,	kInfoPanelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kGradientToolPanelDetailControllerImpl,	kInfoPanelPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformToolPanelDetailControllerImpl,	kInfoPanelPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kPenToolPanelDetailControllerImpl,			kInfoPanelPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kTypeToolSelPanelDetailControllerImpl,		kInfoPanelPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kTypeToolNonSelPanelDetailControllerImpl,	kInfoPanelPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kSelectToolSelPanelDetailControllerImpl,	kInfoPanelPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSelectToolNonSelPanelDetailControllerImpl,kInfoPanelPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kCreationToolPanelDetailControllerImpl,	kInfoPanelPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kSplinePenToolEventWatcherImpl,			kInfoPanelPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelMenuComponentImpl,			    kInfoPanelPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kFooToolPanelProviderImpl,				    kInfoPanelPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kFooToolPanelCreatorImpl,				    kInfoPanelPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelFillColorPopupMenuActionImpl,    kInfoPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelStrokeColorPopupMenuActionImpl,  kInfoPanelPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelFillColorInfoEnumDataImpl,	    kInfoPanelPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelStrokeColorInfoEnumDataImpl,		kInfoPanelPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kOrigPointDataImpl,						kInfoPanelPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kWordCountThreadImpl,						kInfoPanelPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kSelectionToolSuiteASBImpl,				kInfoPanelPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kPushButtonToolPanelProviderImpl,			kInfoPanelPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kSelectionToolSuiteLayoutCSBImpl,			kInfoPanelPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelFillStrokeDataImpl,				kInfoPanelPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kOrigPointIntializedImpl,					kInfoPanelPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kInfoPanelWordCountThreadImpl,				kInfoPanelPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kSmoothToolPanelProviderImpl,				kInfoPanelPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kEraseToolPanelProviderImpl,				kInfoPanelPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kScissorsToolPanelProviderImpl,			kInfoPanelPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kSplineAddPointToolPanelProviderImpl,		kInfoPanelPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kSplineRemovePointToolPanelProviderImpl,	kInfoPanelPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kSplineDirectionToolPanelProviderImpl,		kInfoPanelPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kFillStrokeWidgetToolTipsImpl,				kInfoPanelPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kAnchorPointDataInfoImpl,					kInfoPanelPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kMEToolPanelProviderImpl,					kInfoPanelPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTOPMEToolPanelProviderImpl,				kInfoPanelPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kGapToolPanelCreatorImpl,					kInfoPanelPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kGapToolPanelObserverImpl,					kInfoPanelPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kGapToolPanelProviderImpl,					kInfoPanelPrefix + 124)
//droverised impl
DECLARE_PMID(kImplementationIDSpace, kDV_InfoPanelViewImpl,						kInfoPanelPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kDV_InfoPanelFSContainerViewImpl,			kInfoPanelPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kDV_FillStrokeColorInfoPanelViewImpl,		kInfoPanelPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kHSBColorInfoPanelAttrsImpl,            kInfoPanelPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kHSBInfoWidgetCreatorImpl,                kInfoPanelPrefix + 155)

// <Service ID>
// Service IIDs
DECLARE_PMID(kServiceIDSpace, kInfoPanelFillStrokeService,  kInfoPanelPrefix + 1)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kInfoPanelParentWidgetID, kInfoPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kInfoPanelWidgetID,       kInfoPanelPrefix + 2)

// rotate tool panel
DECLARE_PMID(kWidgetIDSpace, kRotateToolPanelWidgetID,				kInfoPanelPrefix + 3)
//gap
DECLARE_PMID(kWidgetIDSpace, kRotateToolXLocStaticWidgetID,			kInfoPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kRotateToolXLocValueWidgetID,			kInfoPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRotateToolYLocStaticWidgetID,			kInfoPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kRotateToolYLocValueWidgetID,			kInfoPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kRotateToolDistanceStaticWidgetID,		kInfoPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kRotateToolDistanceValueWidgetID,		kInfoPanelPrefix + 10)
//gap
DECLARE_PMID(kWidgetIDSpace, kRotateToolWidthStaticWidgetID,		kInfoPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kRotateToolWidthValueWidgetID,			kInfoPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kRotateToolHeightStaticWidgetID,		kInfoPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kRotateToolHeightValueWidgetID,		kInfoPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kRotateToolPanelVertSeperator1WidgetID,kInfoPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kRotateToolPanelAngleIconWidgetID,		kInfoPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kRotateToolAngleValueWidgetID,			kInfoPanelPrefix + 18)

DECLARE_PMID(kWidgetIDSpace, kInfoPanelLocationIconWidgetID,		kInfoPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kInfoPanelDimensionIconWidgetID,		kInfoPanelPrefix + 20)
//gap

// scale tool panel
DECLARE_PMID(kWidgetIDSpace, kScaleToolPanelWidgetID,				kInfoPanelPrefix + 22)
//gap
DECLARE_PMID(kWidgetIDSpace, kScaleToolXLocStaticWidgetID,			kInfoPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kScaleToolXLocValueWidgetID,			kInfoPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kScaleToolYLocStaticWidgetID,			kInfoPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kScaleToolYLocValueWidgetID,			kInfoPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kScaleToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 28)
//gap
DECLARE_PMID(kWidgetIDSpace, kScaleToolWidthStaticWidgetID,			kInfoPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kScaleToolWidthValueWidgetID,			kInfoPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kScaleToolHeightStaticWidgetID,		kInfoPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kScaleToolHeightValueWidgetID,			kInfoPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kScaleToolPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kScaleToolHorzScaleIconWidgetID,		kInfoPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kScaleToolHorzScaleValueWidgetID,		kInfoPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kScaleToolPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kScaleToolVertScaleIconWidgetID,		kInfoPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kScaleToolVertScaleValueWidgetID,		kInfoPanelPrefix + 39)
//gap
//gap

// shear tool panel
DECLARE_PMID(kWidgetIDSpace, kShearToolPanelWidgetID,				kInfoPanelPrefix + 42)
//gap
DECLARE_PMID(kWidgetIDSpace, kShearToolXLocStaticWidgetID,			kInfoPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kShearToolXLocValueWidgetID,			kInfoPanelPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kShearToolYLocStaticWidgetID,			kInfoPanelPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kShearToolYLocValueWidgetID,			kInfoPanelPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kShearToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 48)
//gap
DECLARE_PMID(kWidgetIDSpace, kShearToolWidthStaticWidgetID,			kInfoPanelPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kShearToolWidthValueWidgetID,			kInfoPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kShearToolHeightStaticWidgetID,		kInfoPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kShearToolHeightValueWidgetID,			kInfoPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kShearToolPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kShearToolRotateAngleIconWidgetID,		kInfoPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kShearToolRotateAngleValueWidgetID,	kInfoPanelPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kShearToolPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kShearToolSkewAngleIconWidgetID,		kInfoPanelPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kShearToolSkewAngleValueWidgetID,		kInfoPanelPrefix + 59)
//gap
//gap

// eyedropper tool panel
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolPanelWidgetID,				kInfoPanelPrefix + 62)
//gap
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolXLocStaticWidgetID,			kInfoPanelPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolXLocValueWidgetID,			kInfoPanelPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolYLocStaticWidgetID,			kInfoPanelPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolYLocValueWidgetID,			kInfoPanelPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolPanelVertSeperator1WidgetID,kInfoPanelPrefix + 68)
//gap
//gap
//gap

// gradient tool panel
DECLARE_PMID(kWidgetIDSpace, kGradientToolPanelWidgetID,				kInfoPanelPrefix + 72)
//gap
DECLARE_PMID(kWidgetIDSpace, kGradientToolXLocStaticWidgetID,			kInfoPanelPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kGradientToolXLocValueWidgetID,			kInfoPanelPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kGradientToolYLocStaticWidgetID,			kInfoPanelPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kGradientToolYLocValueWidgetID,			kInfoPanelPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kGradientToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 78)
//gap
DECLARE_PMID(kWidgetIDSpace, kGradientToolWidthStaticWidgetID,			kInfoPanelPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kGradientToolWidthValueWidgetID,			kInfoPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kGradientToolHeightStaticWidgetID,			kInfoPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kGradientToolHeightValueWidgetID,			kInfoPanelPrefix + 83)
//gap
DECLARE_PMID(kWidgetIDSpace, kGradientToolPanelHorzSeperatorWidgetID,	kInfoPanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kGradientToolDistanceStaticWidgetID,		kInfoPanelPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kGradientToolDistanceValueWidgetID,		kInfoPanelPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kGradientToolPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kGradientToolPanelAngleIconWidgetID,		kInfoPanelPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kGradientToolAngleValueWidgetID,			kInfoPanelPrefix + 90)

// freetransform tool panel
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelWidgetID,				kInfoPanelPrefix + 91)
//gap
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolXLocStaticWidgetID,			kInfoPanelPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolXLocValueWidgetID,			kInfoPanelPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolYLocStaticWidgetID,			kInfoPanelPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolYLocValueWidgetID,			kInfoPanelPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 97)
//gap
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolWidthStaticWidgetID,			kInfoPanelPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolWidthValueWidgetID,			kInfoPanelPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolHeightStaticWidgetID,		kInfoPanelPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolHeightValueWidgetID,			kInfoPanelPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolHorzScaleIconWidgetID,		kInfoPanelPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolHorzScaleValueWidgetID,		kInfoPanelPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolVertScaleIconWidgetID,		kInfoPanelPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolVertScaleValueWidgetID,		kInfoPanelPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelDistanceWidgetID,		kInfoPanelPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolDistanceStaticWidgetID,		kInfoPanelPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolDistanceValueWidgetID,		kInfoPanelPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolRotateAngleIconWidgetID,		kInfoPanelPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolRotateAngleValueWidgetID,	kInfoPanelPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelSkewWidgetID,			kInfoPanelPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolSkewAngleIconWidgetID,		kInfoPanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolSkewAngleValueWidgetID,		kInfoPanelPrefix + 116)

// measure tool panel
DECLARE_PMID(kWidgetIDSpace, kMeasureToolPanelWidgetID,				kInfoPanelPrefix + 117)
//gap
DECLARE_PMID(kWidgetIDSpace, kMeasureToolXLocStaticWidgetID,		kInfoPanelPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolXLocValueWidgetID,			kInfoPanelPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolYLocStaticWidgetID,		kInfoPanelPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolYLocValueWidgetID,			kInfoPanelPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolPanelVertSeperator1WidgetID, kInfoPanelPrefix + 123)
//gap
DECLARE_PMID(kWidgetIDSpace, kMeasureToolWidthStaticWidgetID,		kInfoPanelPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolWidthValueWidgetID,		kInfoPanelPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolHeightStaticWidgetID,		kInfoPanelPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolHeightValueWidgetID,		kInfoPanelPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolPanelHorzSeperatorWidgetID,kInfoPanelPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolDistance1StaticWidgetID,	kInfoPanelPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolDistance1ValueWidgetID,	kInfoPanelPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolDistance2StaticWidgetID,	kInfoPanelPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolDistance2ValueWidgetID,	kInfoPanelPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolPanelVertSeperator2WidgetID, kInfoPanelPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolPanelAngleIconWidgetID,	kInfoPanelPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolAngleValueWidgetID,		kInfoPanelPrefix + 136)

// freetransform tool
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolWidthHeightWidgetID,	kInfoPanelPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolMoveRelativeWidgetID,	kInfoPanelPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolRelativeMoveIconWidgetID,	kInfoPanelPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelDeltaXIconWidgetID, kInfoPanelPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolRelativeXValueWidgetID,	kInfoPanelPrefix + 141)

// pen tool panel
DECLARE_PMID(kWidgetIDSpace, kPenToolPanelWidgetID,					kInfoPanelPrefix + 142)
//gap
DECLARE_PMID(kWidgetIDSpace, kPenToolXLocStaticWidgetID,			kInfoPanelPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kPenToolXLocValueWidgetID,				kInfoPanelPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kPenToolYLocStaticWidgetID,			kInfoPanelPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kPenToolYLocValueWidgetID,				kInfoPanelPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kPenToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 148)
//gap
DECLARE_PMID(kWidgetIDSpace, kPenToolWidthStaticWidgetID,			kInfoPanelPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kPenToolWidthValueWidgetID,			kInfoPanelPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kPenToolHeightStaticWidgetID,			kInfoPanelPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kPenToolHeightValueWidgetID,			kInfoPanelPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kPenToolPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kPenToolDistanceStaticWidgetID,		kInfoPanelPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kPenToolDistanceValueWidgetID,			kInfoPanelPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kPenToolPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kPenToolPanelAngleIconWidgetID,		kInfoPanelPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kPenToolAngleValueWidgetID,			kInfoPanelPrefix + 159)
//gap

// type tool panel
DECLARE_PMID(kWidgetIDSpace, kTypeToolNonSelPanelWidgetID,			kInfoPanelPrefix + 161)
//gap
DECLARE_PMID(kWidgetIDSpace, kTypeToolXLocStaticWidgetID,			kInfoPanelPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kTypeToolXLocValueWidgetID,			kInfoPanelPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kTypeToolYLocStaticWidgetID,			kInfoPanelPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kTypeToolYLocValueWidgetID,			kInfoPanelPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kTypeToolDistanceStaticWidgetID,		kInfoPanelPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kTypeToolDistanceValueWidgetID,		kInfoPanelPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kTypeToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 169)
//gap
DECLARE_PMID(kWidgetIDSpace, kTypeToolWidthStaticWidgetID,			kInfoPanelPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kTypeToolWidthValueWidgetID,			kInfoPanelPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kTypeToolHeightStaticWidgetID,			kInfoPanelPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kTypeToolHeightValueWidgetID,			kInfoPanelPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kTypeToolPanelAngleIconWidgetID,		kInfoPanelPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kTypeToolAngleValueWidgetID,			kInfoPanelPrefix + 176)

// type tool panel with selection
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelDistanceStaticWidgetID,	kInfoPanelPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelDistanceValueWidgetID,	kInfoPanelPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelVertSeperator2WidgetID,	kInfoPanelPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelAngleIconWidgetID,		kInfoPanelPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelAngleValueWidgetID,		kInfoPanelPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kTypeToolPanelHorzSeperator2WidgetID,	kInfoPanelPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kTypeToolPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kTypeToolPanelVertSeperator2WidgetID,  kInfoPanelPrefix + 184)
//gap

DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBSwatchStaticWidgetID,	kInfoPanelPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKSwatchStaticWidgetID,	kInfoPanelPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABSwatchStaticWidgetID,	kInfoPanelPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kInfoPanelFillStrokeWidgetID,				kInfoPanelPrefix + 189)

// selection tool panel when selected
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelWidgetID,			kInfoPanelPrefix + 190)
//gap
DECLARE_PMID(kWidgetIDSpace, kSelectionToolXLocStaticWidgetID,			kInfoPanelPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolXLocValueWidgetID,			kInfoPanelPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolYLocStaticWidgetID,			kInfoPanelPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolYLocValueWidgetID,			kInfoPanelPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolPanelVertSeperator1WidgetID,	kInfoPanelPrefix + 196)
//gap
DECLARE_PMID(kWidgetIDSpace, kSelectionToolWidthStaticWidgetID,			kInfoPanelPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolWidthValueWidgetID,			kInfoPanelPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolHeightStaticWidgetID,		kInfoPanelPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolHeightValueWidgetID,			kInfoPanelPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelHorzSeperator1WidgetID,	kInfoPanelPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelTypeStaticWidgetID,	kInfoPanelPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelTypeValueWidgetID,	kInfoPanelPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelActualResStaticWidgetID,kInfoPanelPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelActualResValueWidgetID,	kInfoPanelPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelEffectiveResStaticWidgetID,kInfoPanelPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelEffectiveResValueWidgetID, kInfoPanelPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kExpandedSelectionToolSelPanelWidgetID,		kInfoPanelPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelHorzSeperator2WidgetID,	kInfoPanelPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelVertSeperatorWidgetID,	kInfoPanelPrefix + 211)

// selection tool panel when non-selected
DECLARE_PMID(kWidgetIDSpace, kNonSelelectionPanelWidgetID,					kInfoPanelPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kNonSelelectionDefaultPanelWidgetID,			kInfoPanelPrefix + 213)
//gap
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelXLocStaticWidgetID,			kInfoPanelPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelXLocValueWidgetID,			kInfoPanelPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelYLocStaticWidgetID,			kInfoPanelPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelYLocValueWidgetID,			kInfoPanelPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelDistanceStaticWidgetID,		kInfoPanelPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelDistanceValueWidgetID,		kInfoPanelPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelVertSeperator1WidgetID,		kInfoPanelPrefix + 221)
//gap
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelWidthStaticWidgetID,			kInfoPanelPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelWidthValueWidgetID,			kInfoPanelPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelHeightStaticWidgetID,		kInfoPanelPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelHeightValueWidgetID,			kInfoPanelPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelAngleIconWidgetID,			kInfoPanelPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelAngleValueWidgetID,			kInfoPanelPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kExpandedNonSelectionPanelWidgetID,			kInfoPanelPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelHorzSeperator1WidgetID,		kInfoPanelPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelLocationStaticWidgetID,	kInfoPanelPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelLocationValueWidgetID,	kInfoPanelPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelLastModifiedStaticWidgetID,	kInfoPanelPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelLastModifiedValueWidgetID,	kInfoPanelPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelAuthorStaticWidgetID,		kInfoPanelPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelAuthorValueWidgetID,			kInfoPanelPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelFileSizeStaticWidgetID,		kInfoPanelPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kNonSelectionPanelFileSizeValueWidgetID,		kInfoPanelPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBSwatchWidgetID,				kInfoPanelPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKSwatchWidgetID,				kInfoPanelPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABSwatchWidgetID,				kInfoPanelPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kInfoPanelFillStrokeContainerWidgetID,			kInfoPanelPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolDefaultPanelWidgetID,		kInfoPanelPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelHorzSeperator2WidgetID,	kInfoPanelPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelVertSeperator3WidgetID,	kInfoPanelPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolDefaultSelPanelWidgetID, kInfoPanelPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelDefaultPanelWidgetID,		kInfoPanelPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kPenToolDefaultPanelWidgetID,			kInfoPanelPrefix + 248)

DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelGradientIconWidgetID,	kInfoPanelPrefix + 249)

DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolDefaultPanelWidgetID,   kInfoPanelPrefix + 250)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoPanelDefaultWidgetID,		kInfoPanelPrefix + 251)
DECLARE_PMID(kWidgetIDSpace, kExpandedFreeTransformToolPanelWidgetID, kInfoPanelPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kGradientToolDefaultPanelWidgetID,		kInfoPanelPrefix + 253)
DECLARE_PMID(kWidgetIDSpace, kMeasureToolDefaultPanelWidgetID,		kInfoPanelPrefix + 254)
DECLARE_PMID(kWidgetIDSpace, kTypeToolNonSelDefaultPanelWidgetID,	kInfoPanelPrefix + 255)

// creation tool
DECLARE_PMID(kWidgetIDSpace, kCreationToolPanelWidgetID,				kInfoPanel2Prefix + 1)
//gap
DECLARE_PMID(kWidgetIDSpace, kCreationToolXLocStaticWidgetID,			kInfoPanel2Prefix + 3)
DECLARE_PMID(kWidgetIDSpace, kCreationToolXLocValueWidgetID,			kInfoPanel2Prefix + 4)
DECLARE_PMID(kWidgetIDSpace, kCreationToolYLocStaticWidgetID,			kInfoPanel2Prefix + 5)
DECLARE_PMID(kWidgetIDSpace, kCreationToolYLocValueWidgetID,			kInfoPanel2Prefix + 6)
DECLARE_PMID(kWidgetIDSpace, kCreationToolDistanceStaticWidgetID,		kInfoPanel2Prefix + 7)
DECLARE_PMID(kWidgetIDSpace, kCreationToolDistanceValueWidgetID,		kInfoPanel2Prefix + 8)
DECLARE_PMID(kWidgetIDSpace, kCreationToolPanelVertSeperator1WidgetID,  kInfoPanel2Prefix + 9)
//gap
DECLARE_PMID(kWidgetIDSpace, kCreationToolWidthStaticWidgetID,			kInfoPanel2Prefix + 11)
DECLARE_PMID(kWidgetIDSpace, kCreationToolWidthValueWidgetID,			kInfoPanel2Prefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCreationToolHeightStaticWidgetID,			kInfoPanel2Prefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCreationToolHeightValueWidgetID,			kInfoPanel2Prefix + 14)
DECLARE_PMID(kWidgetIDSpace, kCreationToolPanelAngleIconWidgetID,		kInfoPanel2Prefix + 15)
DECLARE_PMID(kWidgetIDSpace, kCreationToolAngleValueWidgetID,			kInfoPanel2Prefix + 16)
//gap
DECLARE_PMID(kWidgetIDSpace, kDefaultCreationToolPanelWidgetID,			kInfoPanel2Prefix + 18)
DECLARE_PMID(kWidgetIDSpace, kExpandedCreationToolPanelWidgetID,		kInfoPanel2Prefix + 19)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelFillIconWidgetID,			kInfoPanel2Prefix + 20)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelStrokeIconWidgetID,			kInfoPanel2Prefix + 21)
//gap

DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKWidgetID,				kInfoPanel2Prefix + 23)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKCStaticWidgetID,		kInfoPanel2Prefix + 24)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKCValueWidgetID,			kInfoPanel2Prefix + 25)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKMStaticWidgetID,		kInfoPanel2Prefix + 26)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKMValueWidgetID,			kInfoPanel2Prefix + 27)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKYStaticWidgetID,		kInfoPanel2Prefix + 28)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKYValueWidgetID,			kInfoPanel2Prefix + 29)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKKStaticWidgetID,		kInfoPanel2Prefix + 30)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelCMYKKValueWidgetID,			kInfoPanel2Prefix + 31)

DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBWidgetID,				kInfoPanel2Prefix + 32)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBRStaticWidgetID,			kInfoPanel2Prefix + 33)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBRValueWidgetID,			kInfoPanel2Prefix + 34)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBGStaticWidgetID,			kInfoPanel2Prefix + 35)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBGValueWidgetID,			kInfoPanel2Prefix + 36)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBBStaticWidgetID,			kInfoPanel2Prefix + 37)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelRGBBValueWidgetID,			kInfoPanel2Prefix + 38)

DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABWidgetID,				kInfoPanel2Prefix + 39)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABLStaticWidgetID,			kInfoPanel2Prefix + 40)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABLValueWidgetID,			kInfoPanel2Prefix + 41)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABAStaticWidgetID,			kInfoPanel2Prefix + 42)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABAValueWidgetID,			kInfoPanel2Prefix + 43)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABBStaticWidgetID,			kInfoPanel2Prefix + 44)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelLABBValueWidgetID,			kInfoPanel2Prefix + 45)

DECLARE_PMID(kWidgetIDSpace, kCMYKColorInfoWidgetID,					kInfoPanel2Prefix + 46)
DECLARE_PMID(kWidgetIDSpace, kRGBColorInfoWidgetID,						kInfoPanel2Prefix + 47)
DECLARE_PMID(kWidgetIDSpace, kLABColorInfoWidgetID,						kInfoPanel2Prefix + 48)
DECLARE_PMID(kWidgetIDSpace, kFillColorInfoPanelWidgetID,				kInfoPanel2Prefix + 49)
DECLARE_PMID(kWidgetIDSpace, kStrokeColorInfoPanelWidgetID,				kInfoPanel2Prefix + 50)
DECLARE_PMID(kWidgetIDSpace, kNamedColorInfoWidgetID,					kInfoPanel2Prefix + 51)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelNamedValueWidgetID,			kInfoPanel2Prefix + 52)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelSpotColorIconWidgetID,		kInfoPanel2Prefix + 53)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelProcessColorIconWidgetID,	kInfoPanel2Prefix + 54)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelMixedInkIconWidgetID,		kInfoPanel2Prefix + 55)

DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolPanelDeltaYIconWidgetID,	kInfoPanel2Prefix + 56)
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolRelativeYValueWidgetID,	kInfoPanel2Prefix + 57)

DECLARE_PMID(kWidgetIDSpace, kExpandedTypeToolSelPanelWidgetID,			kInfoPanel2Prefix + 58)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelHorzSeperatorWidgetID,	kInfoPanel2Prefix + 59)
//gap
//gap
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelWordStaticWidgetID,		kInfoPanel2Prefix + 62)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelWordValueWidgetID,		kInfoPanel2Prefix + 63)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelLineStaticWidgetID,		kInfoPanel2Prefix + 64)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelLineValueWidgetID,		kInfoPanel2Prefix + 65)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelParagraphStaticWidgetID,	kInfoPanel2Prefix + 66)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelParagraphValueWidgetID,	kInfoPanel2Prefix + 67)

DECLARE_PMID(kWidgetIDSpace, kFooToolPanelWidgetID,						kInfoPanel2Prefix + 68)
DECLARE_PMID(kWidgetIDSpace, kFooToolMessageWidgetID,					kInfoPanel2Prefix + 69)

DECLARE_PMID(kWidgetIDSpace, kSelectionToolWidthHeightWidgetID,			kInfoPanel2Prefix + 70)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolMoveRelativeWidgetID,		kInfoPanel2Prefix + 71)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolRelativeMoveIconWidgetID,	kInfoPanel2Prefix + 72)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolPanelDeltaXIconWidgetID,		kInfoPanel2Prefix + 73)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolRelativeXValueWidgetID,		kInfoPanel2Prefix + 74)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolPanelDeltaYIconWidgetID,		kInfoPanel2Prefix + 75)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolRelativeYValueWidgetID,		kInfoPanel2Prefix + 76)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolDistanceStaticWidgetID,		kInfoPanel2Prefix + 77)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolDistanceValueWidgetID,		kInfoPanel2Prefix + 78)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolPanelAngleIconWidgetID,		kInfoPanel2Prefix + 79)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolAngleValueWidgetID,			kInfoPanel2Prefix + 80)

DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelWidgetID,					kInfoPanel2Prefix + 81)
DECLARE_PMID(kWidgetIDSpace, kTypeToolCursorXLocationStaticWidgetID,	kInfoPanel2Prefix + 82)
DECLARE_PMID(kWidgetIDSpace, kTypeToolCursorXLocationValueWidgetID,		kInfoPanel2Prefix + 83)
DECLARE_PMID(kWidgetIDSpace, kTypeToolCursorYLocationStaticWidgetID,	kInfoPanel2Prefix + 84)
DECLARE_PMID(kWidgetIDSpace, kTypeToolCursorYLocationValueWidgetID,		kInfoPanel2Prefix + 85)

DECLARE_PMID(kWidgetIDSpace, kRotateToolDefaultPanelWidgetID,			kInfoPanel2Prefix + 86)
DECLARE_PMID(kWidgetIDSpace, kScaleToolDefaultPanelWidgetID,			kInfoPanel2Prefix + 87)
DECLARE_PMID(kWidgetIDSpace, kShearToolDefaultPanelWidgetID,			kInfoPanel2Prefix + 88)

// default info Panel
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoPanelWidgetID,			kInfoPanel2Prefix + 89)
//gap
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoXLocStaticWidgetID,	kInfoPanel2Prefix + 91)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoXLocValueWidgetID,		kInfoPanel2Prefix + 92)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoYLocStaticWidgetID,	kInfoPanel2Prefix + 93)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoYLocValueWidgetID,		kInfoPanel2Prefix + 94)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoDistanceStaticWidgetID,kInfoPanel2Prefix + 95)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoDistanceValueWidgetID,	kInfoPanel2Prefix + 96)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoVertSeperator1WidgetID,kInfoPanel2Prefix + 97)
//gap
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoWidthStaticWidgetID,	kInfoPanel2Prefix + 99)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoWidthValueWidgetID,	kInfoPanel2Prefix + 100)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoHeightStaticWidgetID,	kInfoPanel2Prefix + 101)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoHeightValueWidgetID,	kInfoPanel2Prefix + 102)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoAngleIconWidgetID,		kInfoPanel2Prefix + 103)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoAngleValueWidgetID,	kInfoPanel2Prefix + 104)

// Type panel for selection
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelUnicodeStaticWidgetID, kInfoPanel2Prefix + 105)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelUnicodeValueWidgetID,  kInfoPanel2Prefix + 106)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelVertSeperator1WidgetID, kInfoPanel2Prefix + 107)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelWidthStaticWidgetID,	kInfoPanel2Prefix + 108)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelWidthValueWidgetID,	kInfoPanel2Prefix + 109)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelHeightStaticWidgetID,	kInfoPanel2Prefix + 110)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelHeightValueWidgetID,	kInfoPanel2Prefix + 111)

// additional scale tool panel
DECLARE_PMID(kWidgetIDSpace, kScaleToolDistanceStaticWidgetID,		kInfoPanel2Prefix + 112)
DECLARE_PMID(kWidgetIDSpace, kScaleToolDistanceValueWidgetID,		kInfoPanel2Prefix + 113)
DECLARE_PMID(kWidgetIDSpace, kScaleToolPanelAngleIconWidgetID,		kInfoPanel2Prefix + 114)
DECLARE_PMID(kWidgetIDSpace, kScaleToolAngleValueWidgetID,			kInfoPanel2Prefix + 115)

// additional shear tool panel
DECLARE_PMID(kWidgetIDSpace, kShearToolDistanceStaticWidgetID,		kInfoPanel2Prefix + 116)
DECLARE_PMID(kWidgetIDSpace, kShearToolDistanceValueWidgetID,		kInfoPanel2Prefix + 117)
//gap
//gap

// additional eyedropper tool panel
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolDistanceStaticWidgetID,	kInfoPanel2Prefix + 120)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolDistanceValueWidgetID,	kInfoPanel2Prefix + 121)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolAngleIconWidgetID,		kInfoPanel2Prefix + 122)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolAngleValueWidgetID,		kInfoPanel2Prefix + 123)
//gap
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolWidthStaticWidgetID,	kInfoPanel2Prefix + 125)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolWidthValueWidgetID,		kInfoPanel2Prefix + 126)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolHeightStaticWidgetID,	kInfoPanel2Prefix + 127)
DECLARE_PMID(kWidgetIDSpace, kEyeDropperToolHeightValueWidgetID,	kInfoPanel2Prefix + 128)

//gap
//gap
//gap
DECLARE_PMID(kWidgetIDSpace, kSelectionToolXContentLocStaticWidgetID,			kInfoPanel2Prefix + 132)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolYContentLocStaticWidgetID,			kInfoPanel2Prefix + 133)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelColorProfileStaticWidgetID,	kInfoPanel2Prefix + 134)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelColorProfileValueWidgetID,	kInfoPanel2Prefix + 135)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelObjectInfoWidgetID,			kInfoPanel2Prefix + 136)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelColorProfileWidgetID,		kInfoPanel2Prefix + 137)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelColorSpaceStaticWidgetID,	kInfoPanel2Prefix + 138)
DECLARE_PMID(kWidgetIDSpace, kSelectionToolSelPanelColorSpaceValueWidgetID,		kInfoPanel2Prefix + 139)

DECLARE_PMID(kWidgetIDSpace, kDefaultInfoHorzSeperatorWidgetID,	kInfoPanel2Prefix + 140)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoVertSeperator2WidgetID,kInfoPanel2Prefix + 141)

DECLARE_PMID(kWidgetIDSpace, kExpandedDefaultInfoPanelWidgetID,kInfoPanel2Prefix + 142)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoPanelHorzSeperatorWidgetID, kInfoPanel2Prefix + 143)
DECLARE_PMID(kWidgetIDSpace, kDefaultInfoPanelVertSeperator2WidgetID, kInfoPanel2Prefix + 144)
DECLARE_PMID(kWidgetIDSpace, kExpandedSelectionToolSelPanelObjectInfoWidgetID, kInfoPanel2Prefix + 145)

DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelOpenTypeStaticWidgetID, kInfoPanel2Prefix + 146)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelOpenTypeValueWidgetID,  kInfoPanel2Prefix + 147)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelAllCharacterStaticWidgetID,		kInfoPanel2Prefix + 148)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelAllCharacterValueWidgetID,		kInfoPanel2Prefix + 149)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelFullWidthCharacterStaticWidgetID,	kInfoPanel2Prefix + 150)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelFullWidthCharacterValueWidgetID,	kInfoPanel2Prefix + 151)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelHalfWidthCharacterStaticWidgetID,	kInfoPanel2Prefix + 152)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelHalfWidthCharacterValueWidgetID,	kInfoPanel2Prefix + 153)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelKanjiStaticWidgetID,				kInfoPanel2Prefix + 154)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelKanjiValueWidgetID,				kInfoPanel2Prefix + 155)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelJapaneseCharacterStaticWidgetID,	kInfoPanel2Prefix + 156)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelJapaneseCharacterValueWidgetID,	kInfoPanel2Prefix + 157)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelMojikumiClassStaticWidgetID,		kInfoPanel2Prefix + 158)
DECLARE_PMID(kWidgetIDSpace, kTypeToolSelPanelMojikumiClassValueWidgetID,		kInfoPanel2Prefix + 159)

DECLARE_PMID(kWidgetIDSpace, kGapToolPanelWidgetID,				kInfoPanel2Prefix + 160)
DECLARE_PMID(kWidgetIDSpace, kGapToolXLocStaticWidgetID,		kInfoPanel2Prefix + 161)
DECLARE_PMID(kWidgetIDSpace, kGapToolXLocValueWidgetID,			kInfoPanel2Prefix + 162)
DECLARE_PMID(kWidgetIDSpace, kGapToolYLocStaticWidgetID,		kInfoPanel2Prefix + 163)
DECLARE_PMID(kWidgetIDSpace, kGapToolYLocValueWidgetID,			kInfoPanel2Prefix + 164)
DECLARE_PMID(kWidgetIDSpace, kGapToolPanelVertSeperator1WidgetID, kInfoPanel2Prefix + 165)
DECLARE_PMID(kWidgetIDSpace, kGapToolWidthStaticWidgetID,		kInfoPanel2Prefix + 166)
DECLARE_PMID(kWidgetIDSpace, kGapToolWidthValueWidgetID,		kInfoPanel2Prefix + 167)
DECLARE_PMID(kWidgetIDSpace, kGapToolHeightStaticWidgetID,		kInfoPanel2Prefix + 168)
DECLARE_PMID(kWidgetIDSpace, kGapToolHeightValueWidgetID,		kInfoPanel2Prefix + 169)
DECLARE_PMID(kWidgetIDSpace, kGapToolPanelHorzSeperatorWidgetID,kInfoPanel2Prefix + 170)
DECLARE_PMID(kWidgetIDSpace, kGapToolDefaultPanelWidgetID,		kInfoPanel2Prefix + 171)
DECLARE_PMID(kWidgetIDSpace, kGapToolPanelVertSeperator2WidgetID, kInfoPanel2Prefix + 172)
//HSB Widget IDs
DECLARE_PMID(kWidgetIDSpace, kHSBColorInfoWidgetID, kInfoPanel2Prefix + 173)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBHStaticWidgetID, kInfoPanel2Prefix + 174)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBHValueWidgetID, kInfoPanel2Prefix + 175)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBSStaticWidgetID, kInfoPanel2Prefix + 176)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBSValueWidgetID, kInfoPanel2Prefix + 177)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBBStaticWidgetID, kInfoPanel2Prefix + 178)
DECLARE_PMID(kWidgetIDSpace, kColorInfoPanelHSBBValueWidgetID, kInfoPanel2Prefix + 179)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kInfoPanelActionID,					kInfoPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kShowInfoOptionsActionID,				kInfoPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kInfoPanelSep1ActionID,				kInfoPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kInfoPanelFileInfoActionID,			kInfoPanelPrefix + 4)
// gap
DECLARE_PMID(kActionIDSpace, kInfoPanelFillColorPopupSwatchNameActionID,kInfoPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kInfoPanelFillColorPopupSpaceActionID,		kInfoPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kInfoPanelStrokeColorPopupSwatchNameActionID,kInfoPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kInfoPanelStrokeColorPopupSpaceActionID,		kInfoPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kInfoPanelSep2ActionID,				kInfoPanelPrefix + 10)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kTypeToolObserverAttachDetachInvalHandlerID, kInfoPanelPrefix + 1)

END_IDS()
#endif // __INFOPANELID__








