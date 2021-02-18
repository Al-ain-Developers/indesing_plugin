//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/MediaUIID.h $
//  
//  Owner: wtislar
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

#ifndef __MediaUIID__
#define __MediaUIID__

#if PRAGMA_ONCE
#pragma once
#endif

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kMediaUIPrefix	 RezLong(0x14900)		//Refer also to AdobePrefix.h

// <Start IDC>
// PluginID
#define kMediaUIPluginName 					"MediaUI"
#define kMediaUIPluginID						kMediaUIPrefix + 1

// Anna
#define kMediaUIAnnaRemoveImpls		kAnnaInitialMinorFormatNumber

// Add one of these for each product version.
#define kMediaUILastAnnaMinorFormat	kMediaUIAnnaRemoveImpls

// Overall
#define kMediaUILastFormatChg			kMediaUILastAnnaMinorFormat


// <Class ID>
// gap
DECLARE_PMID(kClassIDSpace, kMediaPanelWidgetBoss, kMediaUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kMediaPanelMenuComponentBoss, kMediaUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kVideoPanelWidgetBoss, kMediaUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSWFPanelWidgetBoss, kMediaUIPrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace, kAudioPanelWidgetBoss, kMediaUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPlaceVideoFromURLDialogBoss, kMediaUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPDFOptionsDialogBoss, kMediaUIPrefix + 17)
//gap
DECLARE_PMID(kClassIDSpace, kUpdatePosterButtonBoss, kMediaUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kWhitePreviewAreaWidgetBoss, kMediaUIPrefix + 23)
//gap
DECLARE_PMID(kClassIDSpace, kPDFOptionsButtonBoss, kMediaUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPlaceMediaButtonBoss, kMediaUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kURLButtonBoss, kMediaUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kShowPreviewButtonBoss, kMediaUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kEditHTMLDialogBoss, kMediaUIPrefix + 31)
//DECLARE_PMID(kClassIDSpace,	kHTMLPreviewPanelBoss, kMediaUIPrefix + 32)
//DECLARE_PMID(kClassIDSpace,	kHTMLPreviewButtonWidgetBoss, kMediaUIPrefix + 33)
//DECLARE_PMID(kClassIDSpace,	kHTMLPreviewPanelMenuBoss, kMediaUIPrefix + 34)
//DECLARE_PMID(kClassIDSpace,	kHTMLPreviewPanelAPEWidgetBoss, kMediaUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kHTMLPosterGeneratorBoss, kMediaUIPrefix + 37)

// <Interface ID>
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPOSTERGENERATOR, kMediaUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAUIUTILS, kMediaUIPrefix + 4)

// <Implementation ID>
// gap
DECLARE_PMID(kImplementationIDSpace, kHTMLPosterGeneratorImpl, kMediaUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMediaErrorHandlerImpl, kMediaUIPrefix + 11)
// gap
DECLARE_PMID(kImplementationIDSpace, kDialogMgrDataImpl, kMediaUIPrefix + 13)
// gap
DECLARE_PMID(kImplementationIDSpace, kMediaPlaceBehaviorUIImpl, kMediaUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSoundAdornmentIconImpl, kMediaUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMovieAdornmentIconImpl, kMediaUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kMediaPanelObserverImpl, kMediaUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kMediaPanelViewImpl, kMediaUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kMediaPanelMenuComponentImpl, kMediaUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kVideoPanelObserverImpl, kMediaUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSWFPanelObserverImpl, kMediaUIPrefix + 32)
//gap
DECLARE_PMID(kImplementationIDSpace, kAudioPanelObserverImpl, kMediaUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPlaceVideoFromURLDCImpl, kMediaUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kPlaceVideoFromURLDOImpl, kMediaUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPDFOptionsDCImpl, kMediaUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kPDFOptionsDOImpl, kMediaUIPrefix + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kMediaPanelButtonTipImpl, kMediaUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kWhitePreviewPanelViewImpl, kMediaUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kEditHTMLDialogControllerImpl, kMediaUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kEditHTMLDialogObserverImpl, kMediaUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kHTMLPreviewButtonWidgetTipImpl, kMediaUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kHTMLPreviewPanelMenuComponentImpl, kMediaUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kHTMLPreviewPanelObserverImpl, kMediaUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kHTMLPreviewPanelViewImpl, kMediaUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAPEPlayerAccessImpl, kMediaUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kMediaUIUtilsImpl, kMediaUIPrefix + 56)



// <Widget ID>

// *** Widget IDs for Movie Settings dialog ***

DECLARE_PMID(kWidgetIDSpace, kMovieSettingsDialogWidgetID, kMediaUIPrefix + 1)
//gap
DECLARE_PMID(kWidgetIDSpace, kMediaNameLabelWidgetID, kMediaUIPrefix + 4 )
DECLARE_PMID(kWidgetIDSpace, kMediaNameEditBoxWidgetID, kMediaUIPrefix + 5 )
DECLARE_PMID(kWidgetIDSpace, kMediaDescriptionLabelWidgetID, kMediaUIPrefix + 6 )
DECLARE_PMID(kWidgetIDSpace, kMediaDescriptionEditBoxWidgetID, kMediaUIPrefix + 7 )
DECLARE_PMID(kWidgetIDSpace, kMediaDescriptionScrollBarWidgetID, kMediaUIPrefix + 8 )
DECLARE_PMID(kWidgetIDSpace, kMovieSettingsSourceGroupWidgetId, kMediaUIPrefix + 9 )
DECLARE_PMID(kWidgetIDSpace, kMovieSettingsSourceGroupTextWidgetID, kMediaUIPrefix + 10 )
DECLARE_PMID(kWidgetIDSpace, kMovieSettingsSourceClusterPanelWidgetID, kMediaUIPrefix + 11 )
DECLARE_PMID(kWidgetIDSpace, kChooseAFileRadioButtonWidgetID, kMediaUIPrefix + 12 )
DECLARE_PMID(kWidgetIDSpace, kSpecifyURLRadioButtonWidgetID, kMediaUIPrefix + 13 )
DECLARE_PMID(kWidgetIDSpace, kMediaFileNameWidgetID, kMediaUIPrefix + 14 )
DECLARE_PMID(kWidgetIDSpace, kFileBrowseButtonWidgetID, kMediaUIPrefix + 15 )
DECLARE_PMID(kWidgetIDSpace, kURLEditBoxWidgetID, kMediaUIPrefix + 16 )
DECLARE_PMID(kWidgetIDSpace, kOptionsGroupWidgetID, kMediaUIPrefix + 17 )
//DECLARE_PMID(kWidgetIDSpace, kOptionsGroupTextWidgetID, kMediaUIPrefix + 18 )
DECLARE_PMID(kWidgetIDSpace, kModeTextWidgetID, kMediaUIPrefix + 19 )
DECLARE_PMID(kWidgetIDSpace, kModeDropDownListWidgetID, kMediaUIPrefix + 20 ) // todo: remove (now called "looping")
DECLARE_PMID(kWidgetIDSpace, kShowControllerCheckBoxWidgetID, kMediaUIPrefix + 21 )
DECLARE_PMID(kWidgetIDSpace, kFloatingWindowCheckBoxWidgetID, kMediaUIPrefix + 22 )
DECLARE_PMID(kWidgetIDSpace, kWindowSizeTextWidgetID, kMediaUIPrefix + 23 )
DECLARE_PMID(kWidgetIDSpace, kWindowSizeDropDownListWidgetID, kMediaUIPrefix + 24 )
DECLARE_PMID(kWidgetIDSpace, kWindowPositionTextWidgetID, kMediaUIPrefix + 25 )
DECLARE_PMID(kWidgetIDSpace, kWindowPositionDropDownListWidgetID, kMediaUIPrefix + 26 )
DECLARE_PMID(kWidgetIDSpace, kPosterThumbnailWidgetID, kMediaUIPrefix + 27 )
DECLARE_PMID(kWidgetIDSpace, kPosterLabelWidgetID, kMediaUIPrefix + 28 )
DECLARE_PMID(kWidgetIDSpace, kPosterDropDownListWidgetID, kMediaUIPrefix + 29 )
DECLARE_PMID(kWidgetIDSpace, kPlayOnPageTurnCheckBoxWidgetID, kMediaUIPrefix + 30 )
DECLARE_PMID(kWidgetIDSpace, kMovieVerifyButtonWidgetID, kMediaUIPrefix + 31 )
DECLARE_PMID(kWidgetIDSpace, kMovieSizeLabelWidgetID, kMediaUIPrefix + 32 )
DECLARE_PMID(kWidgetIDSpace, kMovieSizeWidgetID, kMediaUIPrefix + 33 )
DECLARE_PMID(kWidgetIDSpace, kPosterMakerPanelWidgetID, kMediaUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kMoviePlayerWidgetID, kMediaUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kEmbedMediaCheckBoxWidgetID, kMediaUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPosterBrowseButtonWidgetID, kMediaUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kDoNotPrintPosterCheckBoxWidgetID, kMediaUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kSoundSettingsDialogWidgetID, kMediaUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kSoundFileNameLabelTextWidgetID, kMediaUIPrefix + 40 )
DECLARE_PMID(kWidgetIDSpace, kQuickTimeRequiredWarningDontShowID, kMediaUIPrefix + 41 )
DECLARE_PMID(kWidgetIDSpace, kUnverifiedURLWarningDontShowID, kMediaUIPrefix + 42 )
DECLARE_PMID(kWidgetIDSpace, kChoosePosterHintWidgetID, kMediaUIPrefix + 43 )
DECLARE_PMID(kWidgetIDSpace, kMediaPanelWidgetID, kMediaUIPrefix + 44 )
DECLARE_PMID(kWidgetIDSpace, kVideoPanelWidgetID, kMediaUIPrefix + 45 )
DECLARE_PMID(kWidgetIDSpace, kAudioPanelWidgetID, kMediaUIPrefix + 46 )
DECLARE_PMID(kWidgetIDSpace, kCreatePosterFromFrameButtonWidgetID, kMediaUIPrefix + 47 )
DECLARE_PMID(kWidgetIDSpace, kSWFMediaPanelWidgetID, kMediaUIPrefix + 48 )
DECLARE_PMID(kWidgetIDSpace, kMediaPlayerWidgetID, kMediaUIPrefix + 49 )
// gap
DECLARE_PMID(kWidgetIDSpace, kControllerDropDownListWidgetID, kMediaUIPrefix + 51 )
// gap
DECLARE_PMID(kWidgetIDSpace, kNoSelectionTextWidgetID, kMediaUIPrefix + 55 )
DECLARE_PMID(kWidgetIDSpace, kBottomButtonPanelWidgetID, kMediaUIPrefix + 56 )
// gap
DECLARE_PMID(kWidgetIDSpace, kPlaceVideoFromURLButtonWidgetID, kMediaUIPrefix + 61 )
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsButtonWidgetID, kMediaUIPrefix + 62 )
DECLARE_PMID(kWidgetIDSpace, kPlaceMediaButtonWidgetID, kMediaUIPrefix + 63 )
DECLARE_PMID(kWidgetIDSpace, kLegacyVideoTextWidgetID, kMediaUIPrefix + 64 )
DECLARE_PMID(kWidgetIDSpace, kStopOnPageTurnCheckBoxWidgetID, kMediaUIPrefix + 65 )
DECLARE_PMID(kWidgetIDSpace, kPlayLoopCheckBoxWidgetID, kMediaUIPrefix + 66 )
DECLARE_PMID(kWidgetIDSpace, kMediaPreviewButtonWidgetID, kMediaUIPrefix + 67 )
DECLARE_PMID(kWidgetIDSpace, kLegacyAudioTextWidgetID, kMediaUIPrefix + 68 )
DECLARE_PMID(kWidgetIDSpace, kPlaceVideoFromURLPanelWidgetID, kMediaUIPrefix + 69 )
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsPanelWidgetID, kMediaUIPrefix + 70 )
DECLARE_PMID(kWidgetIDSpace, kMissingMediaTextWidgetID, kMediaUIPrefix + 71 )
DECLARE_PMID(kWidgetIDSpace, kMediaLabelsWidgetID, kMediaUIPrefix + 72 )
// gap
DECLARE_PMID(kWidgetIDSpace, kMediaPlayerPanelWidgetID, kMediaUIPrefix + 74 )
// gap
DECLARE_PMID(kWidgetIDSpace, kEditHTMLDialogWidgetID, kMediaUIPrefix + 80 )
DECLARE_PMID(kWidgetIDSpace, kHTMLTextWidgetID, kMediaUIPrefix + 81 )
//gap
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewPanelWidgetID,	kMediaUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewPanelControlStripWidgetID, kMediaUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewProxyWidgetID, kMediaUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewButtonWidgetID, kMediaUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewPreviousButtonWidgetID, kMediaUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewNextButtonWidgetID, kMediaUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kHTMLPreviewInBrowserButtonWidgetID, kMediaUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kHTMLOneDeviceButtonWidgetID, kMediaUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kHTMLTwoDevicesButtonWidgetID, kMediaUIPrefix + 98)
//gap

// <Action ID>

DECLARE_PMID(kActionIDSpace, kMovieObjectSettingsActionID,	kMediaUIPrefix + 1)
// gap
DECLARE_PMID(kActionIDSpace, kSoundObjectSettingsActionID,	kMediaUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kMediaPanelActionID, 			kMediaUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kVideoFromURLActionID, 		kMediaUIPrefix + 5)
// gap
DECLARE_PMID(kActionIDSpace, kPDFOptionsActionID, 			kMediaUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kEditHTMLActionID, 			kMediaUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kInsertHTMLActionID, 			kMediaUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kInsertHTMLSepActionID, 		kMediaUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kPreviewHTML5InBrowserActionID, 		kMediaUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kHTMLPreviewPanelActionID,		kMediaUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kHTMLTestInBrowserActionID,	kMediaUIPrefix + 15)


// <Ignore>
// ***** Resource IDs *****
#define kMediaPanelRsrcID						6000
#define kNavigationPointNodeWidgetRsrcID		6100
#define kMenuDef_MediaPanelRsrcID				129
#define kMediaUIStringsRsrcID 					3001
#define kMediaUIStringsNoTransRsrcID 			4001

#define kCommonMediaUIStringsRsrcID				5001	// Resource ID of Common Media UI strings

// HTML Preview panel resource definition
#define kHTMLPreviewPaletteRsrcID					6200
#define kHTMLPreviewPaletteIconRsrcID				6201
#define kHTMLPreviewPanelActionsRsrcID				6202
#define kHTMLPreviewDocumentIconRsrcID				6203
#define kHTMLPreviewRefreshIconRsrcID				6204
#define kHTMLPreviewInBrowserRefreshIconRsrcID		6205
#define kHTMLTwoDevicesIconRsrcID					6206
#define kHTMLOneDeviceIconRsrcID					6207
#define kMinHTMLPreviewPanelWidth					207			
#define kMinHTMLPreviewPanelHeight					160
#define kMenuDef_HTMLPreviewPanelRsrcID				130
#define kPanelList_HTMLPreviewPanelRsrcID			150

// Dialog resource IDs

#define kPlaceVideoFromURLDialogRsrcID			3400
#define kPDFOptionsDialogRsrcID					3500
#define kEditHTMLDialogRsrcID					3600

// ----- Icon resource ids.
#define kMediaPanelIconRsrcID					600
#define kAddNavigationPointIconResID			601
#define kRemoveNavigationPointIconResID			602
#define kUpdatePosterIconResID					603
#define kPlaceVideoFromURLIconResID				604
#define kPDFOptionsIconResID					605
#define kPlaceMediaIconResID					606
#define kShowPreviewIconRsrcID					607
#define kMovieAdornmentIconResID				1500
#define kSoundAdornmentIconResID				1501

#define kMediaPanelActionsRsrcID				10000	// Resource ID of popup menu on Media Panel

// For panel geometry
#define kVideoWidgetsHeight							125 // includes Play on Page Load checkbox thru Show Controller on Rollover checkbox
#define kVideoPanelDefaultHeight					494	// includes preview area thru "+" and "-" buttons

#define kMediaPanelDefaultHeight					525
#define kBottomButtonPanelHeight					30	//(kCC2016StandardGapBetweenWidgets+1+kCC2016PanelIconHeight) 

#define kMediaPanelDefaultWidth						270 // new wider width to accommodate localization.
#define kAudioPanelDefaultHeight					315
#define kSWFPanelDefaultHeight						262

#define kPreviewPlayerWidgetHeight					203
#define kPreviewAreaHeight							205 // includes player widget and the separator bar
#define kNavigationPointsListBoxWidgetHeight		90
#define kNavigationPointsListPanelWidgetHeight		118

#define kVideoPanelCollapsedHeight					(kVideoPanelDefaultHeight-kNavigationPointsListPanelWidgetHeight)

//	kPreviewablePlayerWhiteBackgroundWidgetHeight is used as the containing panel for the media player widget.
//	XD widen the media panel. As a result, we have empty spaces to the left/right of the player widget.
//	In order minimize showing gray, I put a white panel behind the player widget. 
//	But need to subtract the area where the play head and counter are shown. This area is shown in gray.
//	It's ugly but XD is OK with this....
#define kPreviewablePlayerWhiteBackgroundWidgetHeight 167 // This is kPreviewPlayerWidgetHeight minus the play head area.
#define kPreviewableMediaWidth						210
#define kMediaLabelWidgetWidth						70
#define kMediaLabelWidgetWidth_DE						80
#define kMediaLabelWidgetWidth_FR						95
#define kMediaLabelWidgetWidth_ES						65
#define kMediaLabelWidgetWidth_NL						50
#define kMediaLabelWidgetWidth_HU						65
#define kMediaLabelWidgetWidth_UA						50
#define kMediaLabelWidgetWidth_JP					75
#define kMediaButtonWidth							18
#define kMediaIconWidth								15




#endif // __MovieUIID__

// End, MediaUIID.h.
