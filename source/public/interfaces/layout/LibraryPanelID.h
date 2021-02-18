//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LibraryPanelID.h $
//  
//  Owner: Mark VerMurlen
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

#ifndef __LibraryPanelID__
#define __LibraryPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLibraryPanelPrefix	 RezLong(0x8600)

// Plugin ID
#define kLibraryPanelPluginName 			"Asset Library Panel"
DECLARE_PMID(kPlugInIDSpace, kLibraryPanelPluginID, kLibraryPanelPrefix + 1)


// <Start IDC>
// <Class ID>

DECLARE_PMID(kClassIDSpace, kLibraryPanelBoss, kLibraryPanelPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kLibraryPanelMenuComponentBoss, kLibraryPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kLibraryPanelDataBoss, kLibraryPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kNewLibItemButtonBoss, kLibraryPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kDeleteLibItemButtonBoss, kLibraryPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFindLibItemButtonBoss, kLibraryPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kLibItemInfoButtonBoss, kLibraryPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLibraryItemViewPanelBoss, kLibraryPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kLibraryItemGridBoss, kLibraryPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kLibraryItemButtonBoss, kLibraryPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kLibraryPanelMgrSSBoss, kLibraryPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLibraryPanelMgrBoss, kLibraryPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kLibraryPanelMgrMenuComponentBoss, kLibraryPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kLibraryDisplayMgrBoss, kLibraryPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kLibraryInfoPanelBoss, kLibraryPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kLibrarySubsetDialogBoss, kLibraryPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kLibraryPanelScriptProviderBoss, kLibraryPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kLibraryPanelSelectionScriptProviderBoss, kLibraryPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kLibraryPanelApplyFilterCmdBoss, kLibraryPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kLibraryinfoThumbWidgetBoss, kLibraryPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kExportLibItemButtonBoss, kLibraryPanelPrefix + 23)
//gap
//DECLARE_PMID(kClassIDSpace, kLibrarySaveFileDialogBoss, kLibraryPanelPrefix + 31)
DECLARE_PMID(kClassIDSpace, kLibraryItemListBoxBoss, kLibraryPanelPrefix + 32)
DECLARE_PMID(kClassIDSpace, kLibraryItemListViewCellBoss, kLibraryPanelPrefix + 33)
//gap
DECLARE_PMID(kClassIDSpace, kLibraryItemGridDDTargetDefaultFlavorHelperBoss, kLibraryPanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kLibraryNewButtonDDTargetDefaultFlavorHelperBoss, kLibraryPanelPrefix + 37)
DECLARE_PMID(kClassIDSpace, kLibraryPanelWindowObserverBoss, kLibraryPanelPrefix + 38)
DECLARE_PMID(kClassIDSpace, kLibraryRedirectionDialogBoss, kLibraryPanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kLibraryExportItemsAsCloudAssetsCmdBoss, kLibraryPanelPrefix + 40)
DECLARE_PMID(kClassIDSpace, kLibraryMigrationOptionsDialogBoss, kLibraryPanelPrefix + 41)

// <Interface ID>

DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYPANELUTILS, kLibraryPanelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYDATA, kLibraryPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCSELECTIONOBSERVER, kLibraryPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSELECTIONOBSERVER, kLibraryPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYPANELCMDDATA, kLibraryPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYPANELMGR, kLibraryPanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYDISPLAYMGR, kLibraryPanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYVIEWCONTROLLER, kLibraryPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYITEMBUTTONDATA, kLibraryPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYFILTERHISTORY, kLibraryPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSUBSETMANAGER, kLibraryPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYPERSISTUIDDATA, kLibraryPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IDONTSHOWAGAINPREF, kLibraryPanelPrefix + 12)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYNAME, kLibraryPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYID, kLibraryPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IFAILEDCOUNT, kLibraryPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISKIPPEDCOUNT, kLibraryPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IMIGRATEDCOUNT, kLibraryPanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYMIGRATIONFLAG, kLibraryPanelPrefix + 19)

// <Implementation ID>

DECLARE_PMID(kImplementationIDSpace, kLibraryPanelUtilsImpl, kLibraryPanelPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelImpl, kLibraryPanelPrefix + 1)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMenuComponentImpl, kLibraryPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelDataImpl, kLibraryPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMainObserverImpl, kLibraryPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLibraryDocSelectionObserverImpl, kLibraryPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLibrarySelectionObserverImpl, kLibraryPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelCmdDataImpl, kLibraryPanelPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelApplyFilterCmdImpl, kLibraryPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDeleteButtonObserverImpl, kLibraryPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kDeleteButtonDragDropTargetImpl, kLibraryPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNewButtonObserverImpl, kLibraryPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kNewButtonDragDropTargetImpl, kLibraryPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLPFindButtonObserverImpl, kLibraryPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kInfoButtonObserverImpl, kLibraryPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemViewPanelImpl, kLibraryPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridPanelImpl, kLibraryPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridEHImpl, kLibraryPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridObserverImpl, kLibraryPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridDDSourceImpl, kLibraryPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridDDTargetImpl, kLibraryPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListBoxControllerImpl, kLibraryPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridControllerImpl, kLibraryPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridPanoramaImpl, kLibraryPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemButtonImpl, kLibraryPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemButtonObserverImpl, kLibraryPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemButtonDataImpl, kLibraryPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMgrSSServiceImpl, kLibraryPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMgrStartStopImpl, kLibraryPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMgrImpl, kLibraryPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMgrObserverImpl, kLibraryPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelMgrMenuComponentImpl, kLibraryPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kLibraryDisplayMgrImpl, kLibraryPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kLibraryDisplayMgrObserverImpl, kLibraryPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kLibraryInfoPanelControllerImpl, kLibraryPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kLibraryinfoThumbViewImpl, kLibraryPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kLibrarySubsetObserverImpl, kLibraryPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kLibrarySubsetControllerImpl, kLibraryPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kLibrarySubsetFilterObserverImpl, kLibraryPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kLibrarySubsetFilterControllerImpl, kLibraryPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kLibraryFilterHistoryImpl, kLibraryPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kLibrarySubsetManagerImpl, kLibraryPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelScriptProviderImpl, kLibraryPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelSelectionScriptProviderImpl, kLibraryPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelScriptSelectionSuiteImpl, kLibraryPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemButtonTipImpl, kLibraryPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kExportButtonObserverImpl, kLibraryPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kExportButtonDragDropTargetImpl, kLibraryPanelPrefix + 50)
//gap
//DECLARE_PMID(kImplementationIDSpace, kLibrarySaveFileDialogImpl, kLibraryPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewControllerImpl, kLibraryPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewCellImpl, kLibraryPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewImpl, kLibraryPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewEHImpl, kLibraryPanelPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewControlDataImpl, kLibraryPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewPanoramaImpl, kLibraryPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemListViewObserverImpl, kLibraryPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridDDTHelperProviderImpl, kLibraryPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kLibraryItemGridDDTargetDefaultFlavorHelperImpl, kLibraryPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kLibraryNewButtonDDTHelperProviderImpl, kLibraryPanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kLibraryNewButtonDDTargetDefaultFlavorHelperImpl, kLibraryPanelPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelWindowObserverImpl, kLibraryPanelPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelXMLGeneratorImpl, kLibraryPanelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kLibraryMgrUIDDataImpl, kLibraryPanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kLibraryPanelSAXHandlerImpl, kLibraryPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kLibraryRedirectionDialogControllerImpl, kLibraryPanelPrefix + 67)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryExportItemsAsCloudAssetsCmdImpl, kLibraryPanelPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kLibraryMigrationOptionsDialogControllerImpl, kLibraryPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kLibraryMigrationOptionsDialogObserverImpl, kLibraryPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryIDImpl, kLibraryPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kSkippedCountImpl, kLibraryPanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kMigratedCountImpl, kLibraryPanelPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kLibraryMigrationFlagImpl, kLibraryPanelPrefix + 75)

// <Widget ID>
//gap
DECLARE_PMID(kWidgetIDSpace, kShowStatusWidgetId, kLibraryPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelResizeButtonWidgetID, kLibraryPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kNewLibraryButtonWidgetID, kLibraryPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kDeleteLibraryButtonWidgetID, kLibraryPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kFindButtonWidgetId, kLibraryPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBottomControlStripWidgetId, kLibraryPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kNoEditWidgetId, kLibraryPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kInfoButtonWidgetId, kLibraryPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemViewPanelWidgetId, kLibraryPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemScrollBarWidgetId, kLibraryPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemGridWidgetId, kLibraryPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemListViewScrollBarWidgetId, kLibraryPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLibraryRedirectionDialogWidgetID, kLibraryPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kCCBannerIconWidgetID, kLibraryPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainRedirectionCheckBoxWidgetID, kLibraryPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kExportLibraryButtonWidgetID, kLibraryPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kLibraryMigrationOptionsWidgetID, kLibraryPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kLaunchCCLibrariesButtonWidgetID, kLibraryPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kInfoNameWidgetId, kLibraryPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kInfoDateWidgetId, kLibraryPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kInfoTypeWidgetId, kLibraryPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kStaticInfoTypeWidgetId, kLibraryPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kInfoDescriptionWidgetId, kLibraryPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemThumbnailWidgetID, kLibraryPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kNewCCLibraryRadioButtonWidgetID, kLibraryPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kNewCCLibraryEditTextWidgetID, kLibraryPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kExistingCCLibraryRadioButtonWidgetID, kLibraryPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kExistingCCLibraryDropdownWidgetID, kLibraryPanelPrefix + 29)

DECLARE_PMID(kWidgetIDSpace, kSubsetMoreChoicesId, kLibraryPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSubsetFewerChoicesId, kLibraryPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kSubsetSearchAllId, kLibraryPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kSubsetSearchShownId, kLibraryPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kSubsetBackId, kLibraryPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kSubsetForwardId, kLibraryPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kParametersTextWidgetId, kLibraryPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kSubsetMatchClusterId, kLibraryPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kSubsetMatchAllId, kLibraryPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kSubsetMatchAnyId, kLibraryPanelPrefix + 39)

DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID0, kLibraryPanelPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID1, kLibraryPanelPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID2, kLibraryPanelPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID3, kLibraryPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID4, kLibraryPanelPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID5, kLibraryPanelPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID6, kLibraryPanelPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kLibraryPanelWidgetID7, kLibraryPanelPrefix + 48)

// IMPORTANT NOTE
// All the library subset items need their own ID space plus more.
// See the #include "SubsetDialog_inc.fr" lines at the end of LibrarySubsetDialog_enUS.fr
// If you need to add widget ids, add them before the kLibrarySubset items and bump these ids.
// But if you absolutely must add widget ids at the end of this file, be
// sure and leave an offset of at about 50 (kLibraryPanelPrefix + 106 would be the first to use).
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetMetaDataField, kLibraryPanelPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetTextPredicates, kLibraryPanelPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetDatePredicates, kLibraryPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetTypePredicates, kLibraryPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetTextField, kLibraryPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetTypeField, kLibraryPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kLibrarySubsetDateField, kLibraryPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kLibraryItemListBoxWidgetId, kLibraryPanelPrefix + 56)

// We have kept the widgetID to be 100 so as to give scope of addition of
// another ~50 widgets, now every library gets a unizqe ID, till be vanish
//the range of this plugin :::::: Watch point:::: puts a restriction on number
//of libraries that can be opened in one session
DECLARE_PMID(kWidgetIDSpace, kFirstLibraryPanelWidgetId, kLibraryPanelPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kLastLibraryPanelWidgetId, kLibraryPanelPrefix + 255)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kNewLibraryActionID, kLibraryPanelPrefix + 1)
//DECLARE_PMID(kActionIDSpace, kOpenLibraryActionID, kLibraryPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kAddPageLibItemsActionID, kLibraryPanelPrefix +3)
DECLARE_PMID(kActionIDSpace, kGetLibItemInfoActionID, kLibraryPanelPrefix +4)
DECLARE_PMID(kActionIDSpace, kDeleteLibItemActionID, kLibraryPanelPrefix +5)
DECLARE_PMID(kActionIDSpace, kPlaceLibItemActionID, kLibraryPanelPrefix +6)
DECLARE_PMID(kActionIDSpace, kShowAllActionID, kLibraryPanelPrefix +7)
DECLARE_PMID(kActionIDSpace, kShowSubsetActionID, kLibraryPanelPrefix +8)
DECLARE_PMID(kActionIDSpace, kViewThumbnailsActionID, kLibraryPanelPrefix +9)
DECLARE_PMID(kActionIDSpace, kViewListActionID, kLibraryPanelPrefix +10)
DECLARE_PMID(kActionIDSpace, kViewOrderByNameActionID, kLibraryPanelPrefix +11)
DECLARE_PMID(kActionIDSpace, kViewOrderByAssendingDateActionID, kLibraryPanelPrefix +12)
DECLARE_PMID(kActionIDSpace, kViewOrderByDescendingDateActionID, kLibraryPanelPrefix +13)
DECLARE_PMID(kActionIDSpace, kViewOrderByKindActionID, kLibraryPanelPrefix +14)
DECLARE_PMID(kActionIDSpace, kCloseLibraryActionID, kLibraryPanelPrefix +15)
DECLARE_PMID(kActionIDSpace, kAddLibItemActionID, kLibraryPanelPrefix +16)
DECLARE_PMID(kActionIDSpace, kLibPanelSep1ActionID, kLibraryPanelPrefix +17)
DECLARE_PMID(kActionIDSpace, kLibPanelSep2ActionID, kLibraryPanelPrefix +18)
DECLARE_PMID(kActionIDSpace, kLibPanelSep3ActionID, kLibraryPanelPrefix +19)
DECLARE_PMID(kActionIDSpace, kLibPanelSep4ActionID, kLibraryPanelPrefix +20)
DECLARE_PMID(kActionIDSpace, kLibPanelSep5ActionID, kLibraryPanelPrefix +21)
DECLARE_PMID(kActionIDSpace, kFirstLibraryPanelActionID, kLibraryPanelPrefix +22)
	// ids between kFirstLibraryPanelAction and kLastLibraryPanelAction are reserved
DECLARE_PMID(kActionIDSpace, kLastLibraryPanelActionID, kLibraryPanelPrefix +102)
DECLARE_PMID(kActionIDSpace, kLibraryMenuSeperatorActionID, kLibraryPanelPrefix +103)
DECLARE_PMID(kActionIDSpace, kImportLibraryActionID, kLibraryPanelPrefix +104)
DECLARE_PMID(kActionIDSpace, kAddPageSeparateLibItemsActionID, kLibraryPanelPrefix +105)
DECLARE_PMID(kActionIDSpace, kUpdateLibItemActionID, kLibraryPanelPrefix +106)
DECLARE_PMID(kActionIDSpace, kViewLargeThumbnailsActionID, kLibraryPanelPrefix +107)
DECLARE_PMID(kActionIDSpace, kMigrateLibItemActionID, kLibraryPanelPrefix +108)

// <Service ID>
// Service Providers
DECLARE_PMID(kServiceIDSpace, kLibraryItemGridDDTargetFlavorHelperService, kLibraryPanelPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kLibraryNewButtonDDTargetFlavorHelperService, kLibraryPanelPrefix + 2)


//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kLibraryPanelObjectScriptElement,			kLibraryPanelPrefix + 1)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kShowAllAssetsMethodScriptElement,			kLibraryPanelPrefix + 40)

//Properties
//DECLARE_PMID(kScriptInfoIDSpace, kLibraryPanelPropertyScriptElement,		kLibraryPanelPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedLibraryPropertyScriptElement,	kLibraryPanelPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kLibraryPanelViewPropertyScriptElement,	kLibraryPanelPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kSortAssetsPropertyScriptElement,			kLibraryPanelPrefix + 123)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kLibraryPanelViewEnumScriptElement,		kLibraryPanelPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kSortAssetsEnumScriptElement,				kLibraryPanelPrefix + 223)


//GUIDS
// {2794FC46-473D-424e-B344-84613F611409}
#define kLibraryPanel_CLSID	{ 0x2794fc46, 0x473d, 0x424e, { 0xb3, 0x44, 0x84, 0x61, 0x3f, 0x61, 0x14, 0x9 } }


//ScriptIDs
enum LibraryPanelScriptIDs {
	c_LibraryPanel			=	'cLbp',

	p_LibraryPanel			=	'pLbp',
	p_AssociatedLibrary		=	'paLb',
	p_View					=	'pVew',

	e_ShowAll				=	'eSAl',

	en_LibraryPanelViews	=	'eLPV',
	en_ListView				=	'eLVi',
	en_ThumbnailView		=	'eThV',
	en_LargeThumbnailView	=	'eLTV',
	en_SortAssets			=	'eSAs',
	en_SortByName			=	'eSBN',
	en_SortByOldest			=	'eSBO',
	en_SortByNewest			=	'eSBn',
	en_SortByType			=	'eSBT',

	kLastLibraryPanelScriptID
} ;

#endif // __LibraryPanelID__

