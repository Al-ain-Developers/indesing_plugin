//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/CSXSID.h $
//  
//  Owner: Jonathan W. Brown
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
//  
//  Contains common IDs used by the CSXS plugin.
//  
//========================================================================================

#ifndef __CSXSID__
#define __CSXSID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCSXSPrefix	RezLong(0x20D00)

// RsrcIDs
#define kCSXSStringsRsrcID				1000
#define kCSXSStringsNoTransRsrcID		2000
#define kCSXSPanelResourceID			3000
#define kCSXSPaletteIconRsrcID			4000
#define kCSXSHtmlPanelResourceID		4500
#define kCSXSDialogResourceID			5000
#define kCSXSMenuResourceID    			9000
#define kCSXSActionResourceID			10000
#define kLoadUnloadExtensionsDlgRscID	11000
#define kStylesConflictDialogRsrcID		12000
#define kCSXSErrorStringTableRsrcID		13000
#define kUserChoiceForCloudTextAdditionDialogRsrcID	14000

// <Start IDC>
// PluginID
#define kCSXSPluginName "CSXS"
DECLARE_PMID(kPlugInIDSpace, kCSXSPluginID, kCSXSPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kCSXSStartupShutdownBoss,					kCSXSPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCSXSExtensionBoss,							kCSXSPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCSXSPanelBoss,								kCSXSPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCSXSActionComponentBoss,					kCSXSPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCSXSTestMenuBoss,							kCSXSPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCSXSDialogBoss,							kCSXSPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCSXSPanelExtensionBoss,					kCSXSPrefix + 7)
DECLARE_PMID(kClassIDSpace, kStylesConflictDialogBoss,					kCSXSPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCCXStartDocEventResponderServiceBoss,		kCSXSPrefix + 9)
DECLARE_PMID(kClassIDSpace, kUserChoiceForCloudTextAdditionDialogBoss,	kCSXSPrefix + 10)

//gap
DECLARE_PMID(kClassIDSpace, kLoadUnloadExtensionDlgBoss,				kCSXSPrefix + 14)

//gap

DECLARE_PMID(kClassIDSpace, kCSXSModalDialogExtensionBoss,				kCSXSPrefix + 16)
//gap

DECLARE_PMID(kClassIDSpace, kExtensionListObserverBoss, kCSXSPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCSXSModelessWindowBoss,					kCSXSPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCSXSScriptProviderBoss,					kCSXSPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCreateTextThumbnailCmdBoss,				kCSXSPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCreateMissingFontObjectCmdBoss,			kCSXSPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSnippetEditingDocSaveResponderBoss,		kCSXSPrefix + 24)
//gap
DECLARE_PMID(kClassIDSpace, kChromiumScrapHandlerBoss,					kCSXSPrefix + 30)
DECLARE_PMID(kClassIDSpace, kChromiumDataExchHandlerImporterHelperBoss,	kCSXSPrefix + 31)
DECLARE_PMID(kClassIDSpace, kChromiumImportBoss,						kCSXSPrefix + 32)
DECLARE_PMID(kClassIDSpace, kStockConnectionStartupShutdownBoss,		kCSXSPrefix + 33)
DECLARE_PMID(kClassIDSpace, kHideCCLibrariesCmdBoss,					kCSXSPrefix + 34)
DECLARE_PMID(kClassIDSpace, kCSXSErrorStringServiceBoss,				kCSXSPrefix + 35)
DECLARE_PMID(kClassIDSpace, kCSXSUnitConversionBoss,					kCSXSPrefix + 36)
DECLARE_PMID(kClassIDSpace, kChromiumImportHelperCCLibrariesBoss,		kCSXSPrefix + 37)
DECLARE_PMID(kClassIDSpace, kCSXSPlugPlugStartupShutdownBoss,			kCSXSPrefix + 38)

//AAL Links

DECLARE_PMID(kClassIDSpace, kChromiumImportHelperAALLinksBoss,			kCSXSPrefix + 40)
DECLARE_PMID(kClassIDSpace, kAALUIStartupShutdownBoss,					kCSXSPrefix + 41)

//Experimentation
DECLARE_PMID(kClassIDSpace, kUserNGLInitProfileWchResponderServiceBoss, kCSXSPrefix + 42)

DECLARE_PMID(kClassIDSpace, kSetDocReviewDataCmdBoss,					kCSXSPrefix + 43)
DECLARE_PMID(kClassIDSpace, kUploadArtifactResponderServiceBoss,		kCSXSPrefix + 44)
DECLARE_PMID(kClassIDSpace, kSetDocModifiedCmdBoss,						kCSXSPrefix + 45)
DECLARE_PMID(kClassIDSpace, kHideExtensionCmdBoss,                          kCSXSPrefix + 46)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kCSXSStartupShutdownImpl,			kCSXSPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCSXSPlugPlugImpl,					kCSXSPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCSXSActionComponentImpl,			kCSXSPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCSXSTestMenuImpl,					kCSXSPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCSXSWindowObserverImpl,			kCSXSPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCSXSPanelMgrObserverImpl,			kCSXSPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCSXSDialogControllerImpl,			kCSXSPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCSXSPanelViewImpl,				kCSXSPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCSXSPanelExtensionImpl,			kCSXSPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCCXStartPresetsListImpl,			kCSXSPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCCXStartUtilsImpl,				kCSXSPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCCXStartDocResponderImpl,			kCSXSPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCCXStartDocEventServiceProviderImpl,	kCSXSPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCCXSSelectionObserverImpl, 		kCSXSPrefix + 15)

//gap

DECLARE_PMID(kImplementationIDSpace, kCSXSModalDialogExtensionImpl,		kCSXSPrefix + 16)

//gap

DECLARE_PMID(kImplementationIDSpace, kCCXStartObserverImpl, kCSXSPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCCXStartWSToRestoreNameDataImpl,	kCSXSPrefix + 19)
//gap

DECLARE_PMID(kImplementationIDSpace, kCreateTextThumbnailCmdImpl, kCSXSPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCreateMissingFontObjectCmdImpl,	kCSXSPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kHideCCLibrariesCmdImpl,			kCSXSPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCSXSWindowImpl,					kCSXSPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyNameDataImpl,			kCSXSPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kFontStyleNameDataImpl,			kCSXSPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPostScriptNameDataImpl,			kCSXSPrefix + 28)

DECLARE_PMID(kImplementationIDSpace, kLoadUnloadExtensionDlgCtlImpl,	kCSXSPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kLoadUnloadExtensionDlgObsvImpl,	kCSXSPrefix + 30)
//gap
DECLARE_PMID(kImplementationIDSpace, kCSXSShowPanelImpl,				kCSXSPrefix + 32)
//gap
DECLARE_PMID(kImplementationIDSpace, kCSXSModelessDialogWindowImpl,		kCSXSPrefix + 34)

DECLARE_PMID(kImplementationIDSpace, kCSXSDialogManagerImpl,			kCSXSPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kCSXSVulcanMessageHandlerImpl,		kCSXSPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kVulcanMessageIdleTaskImpl,		kCSXSPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCSXSLoadPanelIdleTaskImpl,		kCSXSPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCSXSScriptProviderImpl,			kCSXSPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kProjectHelloObserverImpl,			kCSXSPrefix + 40) 
//gap
DECLARE_PMID(kImplementationIDSpace, kSnippetEditingDocResponderImpl,	kCSXSPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSnippetEditingModeDataImpl,		kCSXSPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryAssetExportUtilsImpl,	kCSXSPrefix + 44)
//gap
DECLARE_PMID(kImplementationIDSpace, kChromiumScrapHandlerImpl,			kCSXSPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kChromiumDataExchHandlerHelperProviderImpl,	kCSXSPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kChromiumDataExchHandlerImporterHelperImpl,	kCSXSPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kChromiumImportProviderImpl,		kCSXSPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryExportOptionsImpl,	kCSXSPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryCollectionInfoImpl,	kCSXSPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryContextImpl,			kCSXSPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kChromiumScrapDataImpl,			kCSXSPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kStockConnectionCacheImpl,			kCSXSPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kStockIMSIdleTaskImpl,				kCSXSPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kStockConnectionStartupShutdownImpl,	kCSXSPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kStylesConflictDialogControllerImpl,	kCSXSPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kCSXSErrorStringServiceImpl,		kCSXSPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kExperimentationHandlerImpl,		kCSXSPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kRecentDocStyleObserverImpl,		kCSXSPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kCCXStartContextImpl, kCSXSPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kChromiumImportHelperServiceImpl,	kCSXSPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kChromiumImportHelperCCLibrariesImpl, kCSXSPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kCSXSPlugPlugStartupShutdownImpl, kCSXSPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kCSXSPlugPlugStartupShutdownProviderImpl, kCSXSPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kUserChoiceForCloudTextAdditionDialogControllerImpl, kCSXSPrefix + 66)

DECLARE_PMID(kImplementationIDSpace, kCommentsReviewExtensionEventsWrapperImpl, kCSXSPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kCommentsReviewExtensionUtilsImpl, kCSXSPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kAnnotationObserverImpl, kCSXSPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kAnnotationLayoutDrawingObserverImpl, kCSXSPrefix + 70)

//AAL Links
DECLARE_PMID(kImplementationIDSpace, kAALExtensionEventsWrapperImpl, kCSXSPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kChromiumImportHelperAALLinksImpl, kCSXSPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kAALUIStartupShutdownImpl, kCSXSPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kAALExtensionContextImpl, kCSXSPrefix + 74)

//Experimentation
DECLARE_PMID(kImplementationIDSpace, kUserNGLInitProfileWchServiceProviderImpl, kCSXSPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kUserNGLInitProfileWchResponderImpl, kCSXSPrefix + 76)

DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationUtilsImpl, kCSXSPrefix + 77)
//Gap
DECLARE_PMID(kImplementationIDSpace, kSetDocArtifactDataCmdImpl, kCSXSPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kUploadArtifactServiceProviderImpl, kCSXSPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kUploadArtifactResponderImpl, kCSXSPrefix + 81)
//Gap
DECLARE_PMID(kImplementationIDSpace, kAsyncRequestQueueImpl, kCSXSPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCCXSharesheetExtensionContainerImpl, kCSXSPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kCCXSharesheetObserverImpl, kCSXSPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kSharingOptionsPopupImpl, kCSXSPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kReviewAnnotationsUtilsImpl, kCSXSPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kReviewAnnotMappingDataImpl,        kCSXSPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kIsFileSavedImpl,					 kCSXSPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kShareSheetProgressIdleTaskImpl,    kCSXSPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kCCXDocDBObserverImpl,              kCSXSPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kDocShareDataImpl,                  kCSXSPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSetDocModifiedCmdImpl,             kCSXSPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kShareForReviewSourceImpl,          kCSXSPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kHideExtensionCmdImpl,        kCSXSPrefix + 96)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSPLUGPLUG,						kCSXSPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSEXTENSION,						kCSXSPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSPANELMGROBSERVER,				kCSXSPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSWINDOWOBSERVER,				kCSXSPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSOFPWDATA,						kCSXSPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IRETAINPOSITION,					kCSXSPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSHIDINGEXTENSION,				kCSXSPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMSHOWPANEL,					kCSXSPrefix + 9)

DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSDIALOGMANAGER,					kCSXSPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSVULCANMESSAGEHANDLER,			kCSXSPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IVULCANMESSAGEIDLETASK,				kCSXSPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSPANELLOADIDLETASK,				kCSXSPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSSELECTIONOBSERVER,             kCSXSPrefix + 14)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETEDITINGMODEDATA,			kCSXSPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYASSETEXPORTUTILS,		kCSXSPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYEXPORTOPTIONS,			kCSXSPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYCOLLECTIONINFO,		kCSXSPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYCONTEXT,				kCSXSPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHROMIUMSCRAPDATA,					kCSXSPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTFAMILYNAMEDATA,				kCSXSPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSTYLENAMEDATA,					kCSXSPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPOSTSCRIPTNAMEDATA,			kCSXSPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOCKCONNECTIONCACHE,				kCSXSPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOCKIMSIDLETASK,					kCSXSPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTDISPLAYMODE,				kCSXSPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCEHIDECCLIBRARIES,				kCSXSPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTPRESETSLIST,				kCSXSPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADYEVENTRECEIVED,				kCSXSPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTUTILS,						kCSXSPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTSTATE,						kCSXSPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTOBSERVER,					kCSXSPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTWSTORESTORE,				kCSXSPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPERIMENTATIONHANDLER,			kCSXSPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTDOCSTYLEOBSERVER,			kCSXSPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTCONTEXT,					kCSXSPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHROMIUMIMPORTHELPER,				kCSXSPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ICSXSPLUGPLUGSTARTUPSHUTDOWNSERVICE, kCSXSPrefix + 41)

DECLARE_PMID(kInterfaceIDSpace, IID_ICMDNPREVIEWMODEENABLED,             kCSXSPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCEHIDELEARNPANEL,				kCSXSPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ILEARNPANELCLOSEFORCEHIDE,			kCSXSPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ILEARNPANELCLOSEAPPICON,			kCSXSPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTSREVIEWEXTENSIONEVENTSWRAPPER, kCSXSPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTSREVIEWEXTENSIONUTILS,		   kCSXSPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONOBSERVER,				   kCSXSPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONLAYOUTDRAWINGOBSERVER,	   kCSXSPrefix + 49)

//AAL Links
DECLARE_PMID(kInterfaceIDSpace, IID_IAALEXTENSIONEVENTWRAPPER, kCSXSPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IAALEXTENSIONCONTEXT, kCSXSPrefix + 51)


//CC Review and Commenting.
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLABORATIONUTILS, kCSXSPrefix + 52)
//Gap
DECLARE_PMID(kInterfaceIDSpace, IID_IASYNCREQUESTQUEUE, kCSXSPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSHARESHEETEXTENSIONCONTAINER, kCSXSPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSHARESHEETOBSERVER, kCSXSPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHARINGOPTIONSPOPUP, kCSXSPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWANNOTATIONSUTILS, kCSXSPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWANNOTMAPPINGDATA,            kCSXSPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IISFILESAVED, kCSXSPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROGRESSIDLETASK, kCSXSPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCDBOBSERVER,      kCSXSPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCSHAREDATA,       kCSXSPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREFORREVIEWSOURCE, kCSXSPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWDOCCREATED,   kCSXSPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWDOCUIDDATA,       kCSXSPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCEHIDECOMMENTINGPANEL, kCSXSPrefix + 69)
// <Widget ID>
// Widget ids
//gap

DECLARE_PMID(kWidgetIDSpace, kExtensionListWidgetID, 					kCSXSPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kStylesConflictDialogWidgetID,				kCSXSPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kUseTextWidgetID,							kCSXSPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kUseIncomingStyleWidgetID,					kCSXSPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kUseExistingStyleWidgetID,					kCSXSPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTextFrameTextWidgetID,					kCSXSPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kEntireStoryWidgetID,						kCSXSPrefix + 7)
// Define your widget ids above
// Auto generated CSXS panel widget IDs start from here
DECLARE_PMID(kWidgetIDSpace, kFirstCSXSPanelWidgetID,					kCSXSPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kLastCSXSPanelWidgetID,					kCSXSPrefix + 254)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kShareMyScreenSeparatorActionID,			kCSXSPrefix + 0)
DECLARE_PMID(kActionIDSpace, kShowPDFExportOptionsActionID,             kCSXSPrefix + 1)
DECLARE_PMID(kActionIDSpace, kShowSharingOptionsActionID,               kCSXSPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPDFPresetExportActionID,                  kCSXSPrefix + 3)

// Define your action ids above
// Auto generated CSXS panel action IDs start from here
DECLARE_PMID(kActionIDSpace, kFirstCSXSPanelActionID,					kCSXSPrefix + 100)
DECLARE_PMID(kActionIDSpace, kLastCSXSPanelActionID,					kCSXSPrefix + 255)

// <Error ID>
// Error IDs
//DECLARE_PMID(kErrorIDSpace, kCSXSUnknownActionError,					kCSXSPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kNoSupportedPageItemsError,					kCSXSPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kUnableToFindActionPanelError,				kCSXSPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCantImportMetadataError,					kCSXSPrefix + 4)

// <Message ID>
DECLARE_PMID(kMessageIDSpace, IID_IFOLIOBUILDERLOADINGMSG,				kCSXSPrefix + 0)
DECLARE_PMID(kMessageIDSpace, IID_IFOLIOBUILDERUNLOADEDMSG,				kCSXSPrefix + 1)
//Messages sent for snippet editing mode
DECLARE_PMID(kMessageIDSpace, kSnippetEditingModeMessage,				kCSXSPrefix + 2)

// <Script ID>
// Objects

// Methods
DECLARE_PMID(kScriptInfoIDSpace, kGetHelloJSONDataMethodScriptElement,					kCSXSPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kInvokeColorPickerMethodScriptElement,					kCSXSPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kCreateThumbnailWithPropertiesMethodScriptElement,		kCSXSPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kOpenCloudAssetForEditMethodScriptElement,				kCSXSPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kSetCloudLibraryExportOptionsMethodScriptElement,		kCSXSPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kExportSelectionForCloudLibraryMethodScriptElement,	kCSXSPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kIsUserSharingAppUsageDataMethodScriptElement,			kCSXSPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kSetCloudLibraryCollectionMethodScriptElement,			kCSXSPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMissingFontObjectMethodScriptElement,			kCSXSPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTemporaryCopyMethodScriptElement,				kCSXSPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kGetStyleConflictResolutionStrategyMethodScriptElement,	kCSXSPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kStyleTypeEnumScriptElement,							kCSXSPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kTextHasLocalOverridesMethodScriptElement,				kCSXSPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveFileFromRecentMethodScriptElement,				kCSXSPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kCreateStyleThumbnailWithPropertiesMethodScriptElement,	kCSXSPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kIsAppInTouchModeMethodScriptElement,					kCSXSPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kGetCCXJSONDataMethodScriptElement,					kCSXSPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kOpenPanelMethodScriptElement,							kCSXSPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kExportForCloudLibraryMethodScriptElement,				kCSXSPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kGetSelectedTextDirectionMethodScriptElement,			kCSXSPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kGetUserChoiceForCloudTextAdditionMethodScriptElement, kCSXSPrefix + 20)

// Properties
DECLARE_PMID(kScriptInfoIDSpace, kGetHomeScreenVisibilityScriptElement,					kCSXSPrefix + 81)

// Enums
DECLARE_PMID(kScriptInfoIDSpace, kSelectedTextDirectionEnumScriptElement,				kCSXSPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kThreadedTextFrameTextOptionsEnumScriptElement,		kCSXSPrefix + 152)

#endif // __CSXSID__
