//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ImportExportUIID.h $
//  
//  Owner: Zak Williamson
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

#ifndef __ImportExportUIID__
#define __ImportExportUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kImportExportUIPrefix	RezLong(0x1bb00)
#define kImportExportUIPrefix2	RezLong(0x22f00)


// PluginID
#define kImportExportUIPluginName 		"Import Export UI"
DECLARE_PMID(kPlugInIDSpace, kImportExportUIPluginID,				kImportExportUIPrefix + 1)

// Service IDs
DECLARE_PMID(kServiceIDSpace, kPlaceGunServiceID,					kImportExportUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kExportMgrServiceID,					kImportExportUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kInDesignDocImportDialogService,		kImportExportUIPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kEPubExportSelectableDialogService,	kImportExportUIPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kXHTMLExportSelectableDialogService,	kImportExportUIPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kHTMLPGTExportSelectableDialogService,kImportExportUIPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kEPubExportFXLSelectableDialogService,kImportExportUIPrefix + 7)

// Class IDs
DECLARE_PMID(kClassIDSpace, kPlaceToolBoss, kImportExportUIPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kPlaceGunBoss, kImportExportUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPlaceTrackerBoss, kImportExportUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kOpenPlaceTrackerRegisterBoss, kImportExportUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPlaceGunServiceBoss, kImportExportUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPlaceComponentBoss, kImportExportUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kImportExportUIConversionProviderBoss, kImportExportUIPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kINXVersionDialogBoss, kImportExportUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kExportComponentBoss, kImportExportUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kExportDialogBoss, kImportExportUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kOpenFileWithWindowCmdBoss, kImportExportUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kExportMgrBoss, kImportExportUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSetExportPrefsCmdBoss, kImportExportUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSetExportFormatPrefsCmdBoss, kImportExportUIPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kPlaceSnippetTrackerBoss, kImportExportUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSnippetImportDrawEventServicesBoss, kImportExportUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kInDesignDocImportDialogBoss,				kImportExportUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kInDesignDocPageImportPreviewWidgetBoss,	kImportExportUIPrefix + 19)
//gap
DECLARE_PMID(kClassIDSpace, kInDesignDocLayersTreeViewWidgetBoss,		kImportExportUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kInDesignDocImportGeneralPanelBoss,			kImportExportUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kInDesignDocImportLayersPanelBoss,			kImportExportUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kImportExportUITestMenuBoss,				kImportExportUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kIDDocLayerNodeWidgetBoss,					kImportExportUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kIDDocLayerNodeEyeBallBoss,					kImportExportUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kInDesignDocChangeLayersDialogBoss,			kImportExportUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kRelinkDialogBoss,							kImportExportUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kRelinkToFolderDialogBoss,					kImportExportUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetRelinkFolderOptionsCmdBoss,				kImportExportUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kRelinkFileExtensionDialogBoss,				kImportExportUIPrefix + 31)
// html/epub export
DECLARE_PMID(kClassIDSpace, kEPubExportSelectableDialogBoss,			kImportExportUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kEPubExportGeneralPanelBoss,				kImportExportUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kEPubExportImagePanelBoss,					kImportExportUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kEPubExportAdvancedPanelBoss,				kImportExportUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kXHTMLExportSelectableDialogBoss,			kImportExportUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kXHTMLExportGeneralPanelBoss,				kImportExportUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kXHTMLExportImagePanelBoss,					kImportExportUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kXHTMLExportAdvancedPanelBoss,				kImportExportUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportSelectableDialogBoss,			kImportExportUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportGeneralPanelBoss,				kImportExportUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportImagePanelBoss,				kImportExportUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportAdvancedPanelBoss,			kImportExportUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kHTMLEPubWarningMsgDialogBoss,				kImportExportUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kEPubExportJavaScriptPanelBoss,				kImportExportUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kEPubExportCSSPanelBoss,					kImportExportUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kEPubExportTextPanelBoss,					kImportExportUIPrefix + 47)
DECLARE_PMID(kClassIDSpace, kEPubExportMetadataPanelBoss,				kImportExportUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kEPubExportPreviewPanelBoss,				kImportExportUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLSelectableDialogBoss,			kImportExportUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLGeneralPanelBoss,				kImportExportUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLMetadataPanelBoss,			kImportExportUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLCSSPanelBoss,					kImportExportUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLJavaScriptPanelBoss,			kImportExportUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLPreviewPanelBoss,				kImportExportUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kEPubExportObjectPanelBoss,					kImportExportUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLConversionSettingsPanelBoss,	kImportExportUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kEPubExportConversionSettingsPanelBoss,		kImportExportUIPrefix + 58)
DECLARE_PMID(kClassIDSpace, kShowURLDialogBoss,							kImportExportUIPrefix + 59)

DECLARE_PMID(kClassIDSpace, kRecentPublicationsListBoss,				kImportExportUIPrefix + 64)
DECLARE_PMID(kClassIDSpace, kRecentPublicationListSetFileMaxCmdBoss,	kImportExportUIPrefix + 65)
DECLARE_PMID(kClassIDSpace, kRecentPublicationListPushNewCmdBoss,		kImportExportUIPrefix + 66)
DECLARE_PMID(kClassIDSpace, kRecentPublicationListCleanListCmdBoss,		kImportExportUIPrefix + 67)
DECLARE_PMID(kClassIDSpace, kPublishButtonClickCmdBoss,					kImportExportUIPrefix + 68)
DECLARE_PMID(kClassIDSpace, kPublishFTUESaveConditionsCmdBoss,			kImportExportUIPrefix + 69)
DECLARE_PMID(kClassIDSpace, kThumbnailImageViewBoss,					kImportExportUIPrefix + 70)
DECLARE_PMID(kClassIDSpace, kLearnMoreAboutStaticTextWidgetBoss,		kImportExportUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kPageRangeValidationBoss,					kImportExportUIPrefix + 72)
DECLARE_PMID(kClassIDSpace, kPageNumberValidationBoss,					kImportExportUIPrefix + 73)
DECLARE_PMID(kClassIDSpace, kSetExportFormatPrefsOnWorkCmdBoss,         kImportExportUIPrefix + 74)
DECLARE_PMID(kClassIDSpace, kSetExportFormatPrefsForTextBoss,			kImportExportUIPrefix + 75)


DECLARE_PMID(kClassIDSpace, kImportPDFCommentsDialogBoss,               kImportExportUIPrefix + 76)
DECLARE_PMID(kClassIDSpace, kPublishWarningIAMShownCmdBoss,                    kImportExportUIPrefix + 77)


// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEGUNUIDDATA, kImportExportUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTMANAGER, kImportExportUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHUMBNAILUTILS, kImportExportUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTUSEDEXPORTFORMAT, kImportExportUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCEREGENPLACECURSOR, kImportExportUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEINDESIGNUIDIALOG,	kImportExportUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTDOCUIUTILS, kImportExportUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDDOCLAYERVISIBILITYCHANGEDMSG, kImportExportUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTUSEDEXPORTFORMATFORTEXT, kImportExportUIPrefix + 9)
//gap
//DECLARE_PMID(kInterfaceIDSpace, IID_PROCESSMISSINGFONTDIALOGIMMEDIATELY, kImportExportUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTUIUTILS, kImportExportUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETEXPORTPREFSCMDDATA, kImportExportUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTDIRECTORY, kImportExportUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTFILENAME, kImportExportUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINKUTILS, kImportExportUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_RELINKTOFOLDEROPTIONS, kImportExportUIPrefix + 16) 
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINKDIALOGOPTIONS, kImportExportUIPrefix + 17)  
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINKEXTENSION, kImportExportUIPrefix + 18)  // IID_ISTRINGDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINKCANCELED, kImportExportUIPrefix + 19)  // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IHASDOCSELECTION, kImportExportUIPrefix + 20)  // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPUBLISH, kImportExportUIPrefix + 21) 
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHDOCSTATECHANGE, kImportExportUIPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTPUBLICATIONLIST, kImportExportUIPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHBUTTONCLICKCOUNT, kImportExportUIPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ILMPFUNNELLOGGING, kImportExportUIPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHBUTTONVISIBILITYCHANGE, kImportExportUIPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHUIVISIBILITYCHANGE, kImportExportUIPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IFETCHIMAGEDATA, kImportExportUIPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPUBLISHANALYTICSHELPER, kImportExportUIPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONDESTINATIONUI, kImportExportUIPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFCMTUIUTILS, kImportExportUIPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWPUBLISHWARNING, kImportExportUIPrefix + 35)


// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kPlaceGunServiceImpl, kImportExportUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunObserverImpl, kImportExportUIPrefix + 2)

DECLARE_PMID(kImplementationIDSpace, kPlaceGunCursorProviderImpl, kImportExportUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunToolImpl, kImportExportUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPlaceTrackerImpl, kImportExportUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kOpenPlaceTrackerRegisterImpl, kImportExportUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPlaceComponentImpl, kImportExportUIPrefix + 8)
//gap
DECLARE_PMID(kImplementationIDSpace, kExportComponentImpl, kImportExportUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kExportDialogImpl, kImportExportUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kOpenFileWithWindowCmdImpl, kImportExportUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kExportManagerImpl, kImportExportUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSetExportPrefsCmdImpl, kImportExportUIPrefix + 14)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetExportFormatPrefsCmdImpl, kImportExportUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kLastUsedFormatStringAliasImpl, kImportExportUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kPlaceToolToggleBehaviorImpl, kImportExportUIPrefix + 18)
//gap
DECLARE_PMID(kImplementationIDSpace, kSnippetImportDrawEventServiceImpl, kImportExportUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportDrawEventHandlerImpl, kImportExportUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunKeyEventHandlerImpl, kImportExportUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSnippetPlaceBehaviorUIImpl, kImportExportUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocImportDialogCreatorImpl,		kImportExportUIPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kInDesignDocPlaceBehaviorImpl,				kImportExportUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocPlaceBehaviorUIImpl,			kImportExportUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kImportExportUITestMenuImpl,				kImportExportUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocPageImportPreviewWidgetViewImpl,kImportExportUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocImportGeneralPanelCreatorImpl,	kImportExportUIPrefix + 29)	
DECLARE_PMID(kImplementationIDSpace, kInDesignDocImportGeneralPanelObserverImpl,kImportExportUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocImportLayerPanelCreatorImpl,	kImportExportUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocLayersPanelObserverImpl,		kImportExportUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocLayersPanelControllerImpl,		kImportExportUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocLayersTreeViewAdapterImpl,		kImportExportUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocLayersTreeViewWidgetMgrImpl,	kImportExportUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPlaceInDesignUIDialogImpl,				kImportExportUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPlaceInDesignDocDialogObserverImpl,		kImportExportUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kThumbnailUtilsImpl,						kImportExportUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kIDDocLayerNodeEyeObserverImpl,			kImportExportUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kImportDocUIUtilsImpl,						kImportExportUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kIDDoclayersTreeViewObserverImpl,			kImportExportUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocImportGeneralPanelControllerImpl, kImportExportUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kExportUIUtilsImpl, kImportExportUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSetExportPrefsCmdDataImpl, kImportExportUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocChangeLayerDialogControllerImpl,	kImportExportUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocChangeLayerDialogObserverImpl,		kImportExportUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kRelinkUtilsImpl,				kImportExportUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kRelinkDialogImpl,				kImportExportUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kRelinkToFolderDialogImpl,		kImportExportUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kRelinkToFolderOptionsImpl,		kImportExportUIPrefix + 50) 
DECLARE_PMID(kImplementationIDSpace, kSetRelinkFolderOptionsCmdImpl, kImportExportUIPrefix + 51) 
DECLARE_PMID(kImplementationIDSpace, kRelinkDialogOptionsImpl,		kImportExportUIPrefix + 52) 
DECLARE_PMID(kImplementationIDSpace, kRelinkFileExtensionDialogControllerImpl,	kImportExportUIPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kEPubExportSelectableDialogCreatorImpl,	kImportExportUIPrefix + 54) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportSelectableDialogObserverImpl,	kImportExportUIPrefix + 55) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportGeneralPanelCreatorImpl,		kImportExportUIPrefix + 56) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportGeneralPanelControllerImpl,		kImportExportUIPrefix + 57) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportGeneralPanelObserverImpl,		kImportExportUIPrefix + 58) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportImagePanelCreatorImpl,			kImportExportUIPrefix + 59) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportImagePanelControllerImpl,		kImportExportUIPrefix + 60) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportImagePanelObserverImpl,			kImportExportUIPrefix + 61) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportAdvancedPanelCreatorImpl,		kImportExportUIPrefix + 62) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportAdvancedPanelControllerImpl,	kImportExportUIPrefix + 63) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportAdvancedPanelObserverImpl,		kImportExportUIPrefix + 64) 

DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSelectableDialogCreatorImpl,	kImportExportUIPrefix + 65) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSelectableDialogObserverImpl,	kImportExportUIPrefix + 66) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportGeneralPanelCreatorImpl,		kImportExportUIPrefix + 67) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportGeneralPanelControllerImpl,	kImportExportUIPrefix + 68) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportGeneralPanelObserverImpl,		kImportExportUIPrefix + 69) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportImagePanelCreatorImpl,			kImportExportUIPrefix + 70) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportImagePanelControllerImpl,		kImportExportUIPrefix + 71) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportImagePanelObserverImpl,		kImportExportUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportAdvancedPanelCreatorImpl,		kImportExportUIPrefix + 73) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportAdvancedPanelControllerImpl,	kImportExportUIPrefix + 74) 
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportAdvancedPanelObserverImpl,		kImportExportUIPrefix + 75)

DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportSelectableDialogCreatorImpl,	kImportExportUIPrefix + 76) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportSelectableDialogObserverImpl,kImportExportUIPrefix + 77) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportGeneralPanelCreatorImpl,		kImportExportUIPrefix + 78) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportGeneralPanelControllerImpl,	kImportExportUIPrefix + 79) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportGeneralPanelObserverImpl,	kImportExportUIPrefix + 80) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportImagePanelCreatorImpl,		kImportExportUIPrefix + 81) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportImagePanelControllerImpl,	kImportExportUIPrefix + 82) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportImagePanelObserverImpl,		kImportExportUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportAdvancedPanelCreatorImpl,	kImportExportUIPrefix + 84) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportAdvancedPanelControllerImpl,	kImportExportUIPrefix + 85) 
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportAdvancedPanelObserverImpl,	kImportExportUIPrefix + 86)

DECLARE_PMID(kImplementationIDSpace, kHTMLEPubWarningMessageControllerImpl,		kImportExportUIPrefix + 87)

DECLARE_PMID(kImplementationIDSpace, kEPubExportJavaScriptPanelCreatorImpl,		kImportExportUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kEPubExportJavaScriptPanelControllerImpl,	kImportExportUIPrefix + 89) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportJavaScriptPanelObserverImpl,	kImportExportUIPrefix + 90) 

DECLARE_PMID(kImplementationIDSpace, kEPubExportCSSPanelCreatorImpl,			kImportExportUIPrefix + 91) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportCSSPanelControllerImpl,			kImportExportUIPrefix + 92) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportCSSPanelObserverImpl,			kImportExportUIPrefix + 93) 

DECLARE_PMID(kImplementationIDSpace, kEPubExportTextPanelCreatorImpl,			kImportExportUIPrefix + 94) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportTextPanelControllerImpl,		kImportExportUIPrefix + 95) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportTextPanelObserverImpl,			kImportExportUIPrefix + 96) 

DECLARE_PMID(kImplementationIDSpace, kEPubExportMetadataPanelCreatorImpl,		kImportExportUIPrefix + 97) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportMetadataPanelControllerImpl,	kImportExportUIPrefix + 98) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportMetadataPanelObserverImpl,		kImportExportUIPrefix + 99)  

DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelCreatorImpl,		kImportExportUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelControllerImpl,		kImportExportUIPrefix + 101) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelObserverImpl,		kImportExportUIPrefix + 102) 

DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLSelectableDialogCreatorImpl,	kImportExportUIPrefix + 103) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLSelectableDialogObserverImpl,kImportExportUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLGeneralPanelCreatorImpl,		kImportExportUIPrefix + 105) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLGeneralPanelControllerImpl,	kImportExportUIPrefix + 106) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLGeneralPanelObserverImpl,	kImportExportUIPrefix + 107) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLMetadataPanelCreatorImpl,	kImportExportUIPrefix + 108) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLMetadataPanelControllerImpl,	kImportExportUIPrefix + 109) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLMetadataPanelObserverImpl,	kImportExportUIPrefix + 110) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLJavaScriptPanelCreatorImpl,	kImportExportUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLJavaScriptPanelControllerImpl,	kImportExportUIPrefix + 112) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLJavaScriptPanelObserverImpl,	kImportExportUIPrefix + 113) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLCSSPanelCreatorImpl,			kImportExportUIPrefix + 114) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLCSSPanelControllerImpl,		kImportExportUIPrefix + 115) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLCSSPanelObserverImpl,		kImportExportUIPrefix + 116) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLPreviewPanelCreatorImpl,		kImportExportUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLPreviewPanelControllerImpl,	kImportExportUIPrefix + 118) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLPreviewPanelObserverImpl,	kImportExportUIPrefix + 119) 

DECLARE_PMID(kImplementationIDSpace, kEPubExportObjectPanelCreatorImpl,			kImportExportUIPrefix + 120) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportObjectPanelControllerImpl,		kImportExportUIPrefix + 121) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportObjectPanelObserverImpl,		kImportExportUIPrefix + 122) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportConversionSettingsPanelCreatorImpl,			kImportExportUIPrefix + 123) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportConversionSettingsPanelControllerImpl,		kImportExportUIPrefix + 124) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportConversionSettingsPanelObserverImpl,		kImportExportUIPrefix + 125) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLConversionSettingsPanelCreatorImpl,		kImportExportUIPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLConversionSettingsPanelControllerImpl,	kImportExportUIPrefix + 127) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLConversionSettingsPanelObserverImpl,	kImportExportUIPrefix + 128)

DECLARE_PMID(kImplementationIDSpace, kHTMLPublishImpl,									kImportExportUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationsDynamicMenuImpl,				kImportExportUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationsComponentImpl,					kImportExportUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationListImpl,						kImportExportUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationListSetMaxCountCmdImpl,			kImportExportUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationListPushNewCmdImpl,				kImportExportUIPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kRecentPublicationListCleanListCmdImpl,			kImportExportUIPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kPublishButtonClickCountIntDataAliasImpl,          kImportExportUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kPublishButtonClickCmdImpl,						kImportExportUIPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kLMPFunnelLoggingImpl,								kImportExportUIPrefix + 149)

DECLARE_PMID(kImplementationIDSpace, kHTMLEPubWarningMessageObserverImpl,				kImportExportUIPrefix + 151)

/*DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelTreeViewControllerImpl,	kImportExportUIPrefix + 129) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelTreeViewAdapterImpl,	kImportExportUIPrefix + 130) 
DECLARE_PMID(kImplementationIDSpace, kEPubExportPreviewPanelTreeViewWidgetMgrImpl,	kImportExportUIPrefix + 131) */
DECLARE_PMID(kImplementationIDSpace, kThumbnailImageViewImpl,							kImportExportUIPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kFetchImageDataImpl,								kImportExportUIPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kRepublishAnalyticsHelperImpl,							kImportExportUIPrefix + 155)

DECLARE_PMID(kImplementationIDSpace, kSetExportFormatPrefsOnWorkCmdImpl,                     kImportExportUIPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kSetExportFormatPrefsOnTextCmdImpl,                     kImportExportUIPrefix + 157)

DECLARE_PMID(kImplementationIDSpace, kAnnotPageDestinationUIImpl,	kImportExportUIPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kAnnotTextDestinationUIImpl,	kImportExportUIPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kAnnotPageItemDestinationUIImpl,	kImportExportUIPrefix + 160)

DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentsDialogImpl,		kImportExportUIPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kImportPDFCmtUIUtilsImpl,          kImportExportUIPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kShowPublishWarningBoolDataImpl,          kImportExportUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kPublishWarningIAMShownCmdImpl,          kImportExportUIPrefix + 164)

// Error ID

// <Widget ID>

//    INX Version Panel
//DECLARE_PMID(kWidgetIDSpace, kINXVersionButtonsPanelWidgetID,				kImportExportUIPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionEveParentPanelWidgetID,				kImportExportUIPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionOptionsPanelWidgetID,				kImportExportUIPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoPanelWidgetID,					kImportExportUIPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoIconWidgetID,					kImportExportUIPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoTextWidgetID,					kImportExportUIPrefix + 10)

//DECLARE_PMID(kWidgetIDSpace, kINXVersionButtonsPanelWidgetID,				kImportExportUIPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionEveParentPanelWidgetID,				kImportExportUIPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionOptionsPanelWidgetID,				kImportExportUIPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoPanelWidgetID,					kImportExportUIPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoIconWidgetID,					kImportExportUIPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kINXVersionInfoTextWidgetID,					kImportExportUIPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kRePublishPanelWidgetID,						kImportExportUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kNewPublishButtonWidgetID,						kImportExportUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kRePublishButtonWidgetID,						kImportExportUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPublishedDocsWidgetID,						kImportExportUIPrefix + 4)
//gap
DECLARE_PMID(kWidgetIDSpace, kRePublishDescriptionWidgetID,					kImportExportUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRePublishTitleWidgetID,						kImportExportUIPrefix + 7)
//gap
DECLARE_PMID(kWidgetIDSpace, kRePublishDocInfoNameWidgetID,					kImportExportUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kRePublishDocInfoDateWidgetID,					kImportExportUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kLoadingIconWidgetID,							kImportExportUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kViewHyperlinkWidgetID,						kImportExportUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSelectDocLabelWidgetID,						kImportExportUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kFetchingDocLabelWidgetID,						kImportExportUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kNoDocLabelWidgetID,							kImportExportUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kDocFetchErrorLabelWidgetID,					kImportExportUIPrefix + 16)
// Import InDesign doc dialog
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportDialogWidgetID,				kImportExportUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportGroupWidgetID,				kImportExportUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPlace_NumPageWidgetID,						kImportExportUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPlace_PagesGroupTextWidgetID,					kImportExportUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPlace_PagesGroupWidgetID,						kImportExportUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPlace_PreviewWidgetID,						kImportExportUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPlace_PreviewCheckBoxWidgetID,				kImportExportUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPlace_FirstPageWidgetID,						kImportExportUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kPlace_PreviousPageWidgetID,					kImportExportUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kPlace_NextPageWidgetID,						kImportExportUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPlace_LastPageWidgetID,						kImportExportUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPlace_PageNumberWidgetID,						kImportExportUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportLayersPanelWidgetID,			kImportExportUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportGeneralPanelWidgetID,		kImportExportUIPrefix + 33)
//gap
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportPageRangeClusterWidgetID,	kImportExportUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportOnePageWidgetID,				kImportExportUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportAllPagesWidgetID,			kImportExportUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportRangeWidgetID,				kImportExportUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportRangeEditboxWidgetID,		kImportExportUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kThumbnailElementWidgetID,						kImportExportUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kHiDPIUseWarningWidgetID,						kImportExportUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportCropToTextWidgetID,			kImportExportUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocImportCropToDDWidgetID,			kImportExportUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocLayersPanelWidgetID,				kImportExportUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocShowLayersGroupWidgetID,			kImportExportUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocShowLayersGroupLabelWidgetID,		kImportExportUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kInDesignDocLayersTreeViewWidgetID,			kImportExportUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kIDDocImportLayerNodeWidgetID,					kImportExportUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kIDDocLayersUpdateLinkOpGroupWidgetID,			kImportExportUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kIDDocLayersUpLink_GroupLabelWidgetID,			kImportExportUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kIDDocLayersUpLink_UpdateLinkLabelWidgetID,	kImportExportUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kIDDocLayersUpdateLinkDropDownWidgetID,		kImportExportUIPrefix + 53)

DECLARE_PMID(kWidgetIDSpace, kInDesignDocChangeLayersDialogWidgetID,		kImportExportUIPrefix + 54)
//gap

// Relink File Extension dialog
DECLARE_PMID(kWidgetIDSpace, kRelinkFileExtensionDialogWidgetID,			kImportExportUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kRelinkFileExtensionPanelWidgetID,				kImportExportUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kRelinkExtensionMsgWidgetID,					kImportExportUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kRelinkExtensionPanelWidgetID,					kImportExportUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kRelinkExtensionTitleWidgetID,					kImportExportUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kRelinkExtensionEditWidgetID,					kImportExportUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kRelinkExtensionButtonsPanelWidgetID,			kImportExportUIPrefix + 65)

// EBook export preference dialog
DECLARE_PMID(kWidgetIDSpace, kEPubExportSelDlgWidgetID,						kImportExportUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kEPubExportGeneralPanelWidgetID,				kImportExportUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kIncludeMetaCheckboxWidgetID,					kImportExportUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kPublishEntryTextEditBoxWidgetID,				kImportExportUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kUUIDTextEditBoxWidgetID,						kImportExportUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kBasedOnLayoutRadioWidgetID,					kImportExportUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kBasedOnXMLStructureRadioWidgetID,				kImportExportUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kBasedOnArticlePanelRadioWidgetID,				kImportExportUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kBulletsDropDownListWidgetID,					kImportExportUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kNumbersDropDownListWidgetID,					kImportExportUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kViewEBookCheckboxWidgetID,					kImportExportUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kGroupTitleWidgetID,							kImportExportUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kCoverImageDropdownWidgetID,					kImportExportUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kBulletNumberGroupPanelWidgetID,				kImportExportUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kPubishImageResolutionDropdownWidgetID,		kImportExportUIPrefix + 81)

DECLARE_PMID(kWidgetIDSpace, kEPubExportImagePanelWidgetID,					kImportExportUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kImageResolutionDropdownWidgetID,				kImportExportUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kImageSizeDropdownWidgetID,					kImportExportUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kImageFormattedWidgetID,						kImportExportUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kImageConversionDropdownWidgetID,				kImportExportUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kGIFGroupPanelWidgetID,						kImportExportUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kGIFPaletteDropdownWidgetID,					kImportExportUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kGIFInterlaceCheckboxWidgetID,					kImportExportUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kJPEGGroupPanelWidgetID,						kImportExportUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kJPEGQualityDropdownWidgetID,					kImportExportUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kJPEGEncodingDropdownWidgetID,					kImportExportUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kIgnoreObjectSettingWidgetID,					kImportExportUIPrefix + 93)

DECLARE_PMID(kWidgetIDSpace, kEPubFormatDropdownWidgetID,					kImportExportUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kEPub3PGTWarningIconWidgetId,					kImportExportUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kEPubFormatWarningTextWidgetID,				kImportExportUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kCoverImageFilePathTextEditBoxWidgetID,		kImportExportUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kTOCStylesDropDownListWidgetID,				kImportExportUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kStripSoftRetuenCheckboxWidgetID,				kImportExportUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kNavigationDropDownListWidgetID,				kImportExportUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kSplitDocumentParaStyleDropDownWidgetID,		kImportExportUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kFootnotePlacementDropDownListWidgetID,        kImportExportUIPrefix + 103)

DECLARE_PMID(kWidgetIDSpace, kEmbedCSSCheckboxWidgetID,						kImportExportUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kEmbedCSSPanelWidgetID,						kImportExportUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kPreserveOverridePanelWidgetID,				kImportExportUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kHTMLWithoutClassesRadioWidgetID,				kImportExportUIPrefix + 107)

DECLARE_PMID(kWidgetIDSpace, kPreserveOverrideCheckboxWidgetID,				kImportExportUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kIncludeEmbeddableFontCheckboxWidgetID,		kImportExportUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kJavascriptPanelWidgetID,						kImportExportUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kContentOrderDropdownWidgetID,					kImportExportUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kContentOrderPanelWidgetID,					kImportExportUIPrefix + 112)

// xhtml dialog
DECLARE_PMID(kWidgetIDSpace, kXHTMLExportSelDlgWidgetID,					kImportExportUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kXHTMLExportGeneralPanelWidgetID,				kImportExportUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kSelectionRadioWidgetID,						kImportExportUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kDocumentRadioWidgetID,						kImportExportUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kHTMLWithClassesRadioWidgetID,					kImportExportUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kGenerateCSSPanelWidgetID,						kImportExportUIPrefix + 118)

DECLARE_PMID(kWidgetIDSpace, kXHTMLExportImagePanelWidgetID,				kImportExportUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kCopyImagesPopupWidgetID,						kImportExportUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kNonServerPanelWidgetID,						kImportExportUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kServerPanelWidgetID,							kImportExportUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kPathOnServerTextEditBoxWidgetID,				kImportExportUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kFileExtensionTextEditBoxWidgetID,				kImportExportUIPrefix + 124)

DECLARE_PMID(kWidgetIDSpace, kXHTMLExportAdvancedPanelWidgetID,				kImportExportUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kJavascriptListboxWidgetID,					kImportExportUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kCSSListboxWidgetID,							kImportExportUIPrefix + 128)

DECLARE_PMID(kWidgetIDSpace, kImagePositionCheckBoxWidgetID,				kImportExportUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kIconExportAlignLeftWidgetID,					kImportExportUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kIconExportAlignCenterWidgetID,				kImportExportUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kIconExportAlignRightWidgetID,					kImportExportUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kIconExportSpaceBeforeWidgetID,				kImportExportUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kExportSpaceBeforeNudgeWidgetID,				kImportExportUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kExportSpaceBeforeObserverWidgetID,			kImportExportUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kIconExportSpaceAfterWidgetID,					kImportExportUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kExportSpaceAfterNudgeWidgetID,				kImportExportUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kExportSpaceAfterObserverWidgetID,				kImportExportUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kImageAlignmentSpacePanelWidgetID,				kImportExportUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kExportImageLocationDropDownID,				kImportExportUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kExportPageBreakCheckBoxID,					kImportExportUIPrefix + 141)
// gap
DECLARE_PMID(kWidgetIDSpace, kExportAlignTypeFocusGroupID,					kImportExportUIPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kMarginTopEditBoxWidgetID,						kImportExportUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kMarginTopEditBoxNudgeWidgetID,				kImportExportUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kMarginBottomEditBoxWidgetID,					kImportExportUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kMarginBottomEditBoxNudgeWidgetID,				kImportExportUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kMarginLeftEditBoxWidgetID,					kImportExportUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kMarginLeftNudgeWidgetID,						kImportExportUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kMarginRightEditBoxWidgetID,					kImportExportUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kMarginRightNudgeWidgetID,						kImportExportUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kEPubMarginPanelWidgetID,						kImportExportUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kEPubMarginChainButtonWidgetID,				kImportExportUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kSVGGroupPanelWidgetID,						kImportExportUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kUseSVGAsDropDownWidgetID,						kImportExportUIPrefix + 156)

// htmlpgt dialog
DECLARE_PMID(kWidgetIDSpace, kHTMLPGTExportSelDlgWidgetID,					kImportExportUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kHTMLPGTExportGeneralPanelWidgetID,			kImportExportUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kHTMLPGTExportImagePanelWidgetID,				kImportExportUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kHTMLPGTExportAdvancedPanelWidgetID,			kImportExportUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kAddJavascriptButtonWidgetID,					kImportExportUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kDeleteJavascriptButtonWidgetID,				kImportExportUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kAddCSSButtonWidgetID,							kImportExportUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kDeleteCSSButtonWidgetID,						kImportExportUIPrefix + 167)

// html/epub export warning message dialog
DECLARE_PMID(kWidgetIDSpace, kWarningMessageStaticTextWidgetID,				kImportExportUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kImageUseOriginaldWidgetID,					kImportExportUIPrefix + 169)

DECLARE_PMID(kWidgetIDSpace, kEPubExportJavaScriptPanelWidgetID,			kImportExportUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kEPubExportCSSPanelWidgetID,					kImportExportUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kEmbedPageMarginTextWidgetID,					kImportExportUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kEmbedPageMarginPanelWidgetID,					kImportExportUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kEPubExportTextPanelWidgetID,					kImportExportUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kStripPrecedingHyphenCheckboxWidgetID,			kImportExportUIPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kSplitDocCheckboxWidgetID,						kImportExportUIPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kSplitDocPanelWidgetID,						kImportExportUIPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kSingleParaStyleRadioWidgetID,					kImportExportUIPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kEPubExportMetadataPanelWidgetID,				kImportExportUIPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kEPubExportPreviewPanelWidgetID,				kImportExportUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kEPubViewAppsListboxWidgetID,					kImportExportUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kAddApplnButtonWidgetID,						kImportExportUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kRemoveApplnButtonWidgetID,					kImportExportUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kMetadataTitleTextEditBoxWidgetID,				kImportExportUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kMetadataCreatorTextEditBoxWidgetID,			kImportExportUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kMetadataDateTextEditBoxWidgetID,				kImportExportUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kMetadataDescTextEditBoxWidgetID,				kImportExportUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kMetadataRightsTextEditBoxWidgetID,			kImportExportUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kMetadataSubjectTextEditBoxWidgetID,			kImportExportUIPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kParaStyleExportTagsRadioWidgetID,				kImportExportUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLSelDlgWidgetID,					kImportExportUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLGeneralPanelWidgetID,			kImportExportUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kEPubCoverPanelWidgetID,						kImportExportUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kEPubNavigationPanelWidgetID,					kImportExportUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kEPubPagePanelWidgetID,						kImportExportUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kEPubPageRangeWidgetID,						kImportExportUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kEPubFXLOptionsPanelWidgetID,					kImportExportUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kEPubFixedLayoutOptWidgetID,					kImportExportUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kEPubPageMergeDropdownWidgetID,				kImportExportUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kEPubLockOrientationCheckboxWidgetID,			kImportExportUIPrefix + 200) //FXLTODO: remove.
DECLARE_PMID(kWidgetIDSpace, kEPubPageRangeTextEditBoxWidgetID,				kImportExportUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLJavaScriptPanelWidgetID,			kImportExportUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLCSSPanelWidgetID,				kImportExportUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLPreviewPanelWidgetID,			kImportExportUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kEPubNavigationSingleLevelWidgetID,			kImportExportUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kEPubParaStylesDropDownListWidgetID,			kImportExportUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kEPubNavigationMultiLevelWidgetID,				kImportExportUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kEPubExportObjectPanelWidgetID,				kImportExportUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kEPubExportFXLConversionSettingsPanelWidgetID,	kImportExportUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kEPubExportConversionSettingsPanelWidgetID,	kImportExportUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kLayoutDropDownWidgetID,						kImportExportUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kImageAlignmentDropdownWidgetID,				kImportExportUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kImageResolutionEditBoxWidgetID,				kImportExportUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kPNGGroupPanelWidgetID,						kImportExportUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kCoverImageFileLocationPanelWidgetID,			kImportExportUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kEPubExportAllRadioWidgetID,					kImportExportUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kEPubExportRangeRadioWidgetID,					kImportExportUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kPNGCompLvlDropdownWidgetID,					kImportExportUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kEPubPNGCompLvlWidgetID,						kImportExportUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kEPubChooseCoverImageButtonWidgetID,			kImportExportUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kPreviewApplicationCheckBoxWidgetID,			kImportExportUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kPreviewApplicationNameWidgetID,				kImportExportUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kPreviewPanelApplicationListWidgetID,			kImportExportUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kPreviewDefaultAppNameWidgetID,				kImportExportUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kDefaultAppPanelWidgetID,						kImportExportUIPrefix + 225)
//DECLARE_PMID(kWidgetIDSpace, kReaderCanDownloadID,							kImportExportUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kImageSettingsGroupTitleWidgetID,				kImportExportUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kFileNameStaticTextWidgetID,					kImportExportUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kFileNameEditWidgetID,							kImportExportUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kDescriptionStaticTextWidgetID,				kImportExportUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kDescriptionEditWidgetID,						kImportExportUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kCoverPageNudgeWidgetID,						kImportExportUIPrefix + 255)
DECLARE_PMID(kWidgetIDSpace, kWarningMessageScrollWidgetID,					kImportExportUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace, kWarningMessageHeaderTextWidgetID,				kImportExportUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kWarningMessageFooterTextWidgetID,				kImportExportUIPrefix2 + 7) 
DECLARE_PMID(kWidgetIDSpace, kCommonTitleEtcWidgetID,						kImportExportUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace, kSeparatorAfterTopClusterPanelWidgetID,		kImportExportUIPrefix2 + 14)

// Action IDs
DECLARE_PMID(kActionIDSpace, kPlaceActionID, kImportExportUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPlaceSeperatorActionID, kImportExportUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kExportActionID, kImportExportUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kExportSeperatorActionID, kImportExportUIPrefix + 4 )
DECLARE_PMID(kActionIDSpace, kPlaceFromCloudLibrariesActionID, kImportExportUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kPublishActionID, kImportExportUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kRecentPublicationsDynamicActionID, kImportExportUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kWebDashboardActionID, kImportExportUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kPublishSepActionID, kImportExportUIPrefix + 9)
//DECLARE_PMID(kActionIDSpace, Unused, kImportExportUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kFirstPublicationActionID, kImportExportUIPrefix + 11)
// Reserved ID's for recent-publications
DECLARE_PMID(kActionIDSpace, kLastPublicationActionID, kImportExportUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kImportPDFCommentsActionID, kImportExportUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kLaunchSharesheetActionID, kImportExportUIPrefix + 22)

// Messages ID 

// Script Element IDs

// Suites

// Objects

// Events

// Properties

// Enums

#endif // __ImportExportUIID__
