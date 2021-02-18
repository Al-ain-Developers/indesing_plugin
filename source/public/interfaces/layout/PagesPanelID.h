//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/PagesPanelID.h $
//  
//  Owner: Brendan O'Shea
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
//  Contains IDs used by the pages panel
//  
//========================================================================================

#ifndef __PagesPanelID__
#define __PagesPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPagesPanelPrefix	RezLong(0x1800) 

// <Start IDC>
// PluginID
#define kPagesPanelPluginName 						"Pages Panel"
DECLARE_PMID(kPlugInIDSpace, kPagesPanelPluginID, kPagesPanelPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kPagesPanelWidgetBoss, kPagesPanelPrefix + 1 )
DECLARE_PMID(kClassIDSpace, kLayoutPagesSubPanelWidgetBoss, kPagesPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kMasterPagesSubPanelWidgetBoss, kPagesPanelPrefix + 3 )
DECLARE_PMID(kClassIDSpace, kSpreadWidgetBoss, kPagesPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kLayoutSpreadWidgetBoss, kPagesPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kMasterSpreadWidgetBoss, kPagesPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPageTabWidgetBoss, kPagesPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPagesPanelConversionBoss, kPagesPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kInsertPageDragDropDialogBoss, kPagesPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPagesPanelMenuComponentBoss, kPagesPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPagesPanelNewButtonBoss, kPagesPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kPagesPanelDeleteButtonBoss, kPagesPanelPrefix + 12)

// NewMaster Dialog class IDs:
DECLARE_PMID(kClassIDSpace, kNewMasterDialogBoss, kPagesPanelPrefix + 13)

// ApplyMaster Dialog class IDs:
DECLARE_PMID(kClassIDSpace, kApplyMasterDialogBoss, kPagesPanelPrefix + 14)

// Create Alternate Layout Dialog class IDs:
DECLARE_PMID(kClassIDSpace, kCreateAlternateLayoutDialogBoss, kPagesPanelPrefix + 15)

// MasterInfo Dialog class IDs:	
DECLARE_PMID(kClassIDSpace, kMasterInfoDialogBoss, kPagesPanelPrefix + 16)

// ColumnMargin dialog class IDs:
DECLARE_PMID(kClassIDSpace, kColumnMarginDialogBoss, kPagesPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kColumnMarginMenuActionBoss, kPagesPanelPrefix + 18)

// new page & delete page dialog class IDs:
DECLARE_PMID(kClassIDSpace, kNewPageDialogBoss, kPagesPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kDeletePageDialogBoss, kPagesPanelPrefix + 20)


// Drag and Drop class IDs:
DECLARE_PMID(kClassIDSpace, kPageDEHandlerBoss, kPagesPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kPagesDEHandlerBoss, kPagesPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSpreadDEHandlerBoss, kPagesPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSpreadsDEHandlerBoss, kPagesPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kMasterPageDEHandlerBoss, kPagesPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kMasterSpreadDEHandlerBoss, kPagesPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kMasterSpreadsDEHandlerBoss, kPagesPanelPrefix + 27)

DECLARE_PMID(kClassIDSpace, kSpreadStaticTextWidgetBoss, kPagesPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kAlternateLayoutNameWidgetBoss, kPagesPanelPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetPagesPanelPrefsCmdBoss, kPagesPanelPrefix + 30)

// Pages panel options dialog class ID:
DECLARE_PMID(kClassIDSpace, kPagesPanelOptionsDialogBoss, kPagesPanelPrefix + 31)

DECLARE_PMID(kClassIDSpace, kMasterSpreadStaticTextWidgetBoss, kPagesPanelPrefix + 32)
DECLARE_PMID(kClassIDSpace, kMasterListStaticTextWidgetBoss, kPagesPanelPrefix + 33)

// ---- Moved from the Master Pages plug-in
DECLARE_PMID(kClassIDSpace, kMasterPageTestMenuBoss, kPagesPanelPrefix + 34)
DECLARE_PMID(kClassIDSpace, kAlternateLayoutColumnHeaderPanelWidgetBoss, kPagesPanelPrefix + 35)

// ---- end move.

DECLARE_PMID(kClassIDSpace, kPagesPanelStatusWidgetBoss, kPagesPanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kPagesPanelScriptProviderBoss, kPagesPanelPrefix + 37)

// Move page dialog class IDs
DECLARE_PMID(kClassIDSpace, kMovePageDialogWidgetBoss, kPagesPanelPrefix + 38)

DECLARE_PMID(kClassIDSpace, kPagesPanelGrabberTrackerBoss, kPagesPanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPagesPanelGrabberTrackerRegisterBoss, kPagesPanelPrefix + 40)

// Move master dialog class IDs
DECLARE_PMID(kClassIDSpace, kMoveMasterDialogWidgetBoss, kPagesPanelPrefix + 41)
DECLARE_PMID(kClassIDSpace, kLoadMasterPageAlertDialogBoss, kPagesPanelPrefix + 42)

DECLARE_PMID(kClassIDSpace, kPageColorLabelMenuElementWidgetBoss, kPagesPanelPrefix + 43)

DECLARE_PMID(kClassIDSpace, kPagesPanelPageSizesButtonBoss, kPagesPanelPrefix + 45)
DECLARE_PMID(kClassIDSpace, kPageSizePresetButtonActionBoss, kPagesPanelPrefix + 46)

DECLARE_PMID(kClassIDSpace, kAlternateLayoutNameElementWidgetBoss, kPagesPanelPrefix + 47)
DECLARE_PMID(kClassIDSpace, kAlternateLayoutPopupMenuWidgetBoss, kPagesPanelPrefix + 48)
// HTML5 Pagination Options class IDs:
//DECLARE_PMID(kClassIDSpace, kHTML5PaginationOptionsDialogBoss, kPagesPanelPrefix + 49)

//gap

DECLARE_PMID(kClassIDSpace, kMasterPagesSubMasterPanelWidgetBoss, kPagesPanelPrefix + 56)
DECLARE_PMID(kClassIDSpace, kLayoutPagesSubMasterPanelWidgetBoss, kPagesPanelPrefix + 57)
DECLARE_PMID(kClassIDSpace, kColumnMarginPanelBoss, kPagesPanelPrefix + 58)
DECLARE_PMID(kClassIDSpace, kEditPagesButtonBoss, kPagesPanelPrefix + 59)
DECLARE_PMID(kClassIDSpace, kPageNumberComboBoxWidgetBoss, kPagesPanelPrefix + 60)
DECLARE_PMID(kClassIDSpace, kPageNumberNewButtonBoss, kPagesPanelPrefix + 61)
DECLARE_PMID(kClassIDSpace, kPageNumberDeleteButtonBoss, kPagesPanelPrefix + 62)
DECLARE_PMID(kClassIDSpace, kPageSelectionComboBoxWidgetBoss, kPagesPanelPrefix + 63)
DECLARE_PMID(kClassIDSpace, kPageSelectionNewButtonBoss, kPagesPanelPrefix + 64)
DECLARE_PMID(kClassIDSpace, kPageSelectionDeleteButtonBoss, kPagesPanelPrefix + 65)

// <Interface ID>
// IIDs
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESIZEGROUPOBSERVER, kPagesPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADWIDGETCONTROLLER, kPagesPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETABCONTROLLER, kPagesPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVEPAGESTARGETDOCUMENT, kPagesPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESSUBPANELCONTROLLER, kPagesPanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESPANELPREFS, kPagesPanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESPANELPREFSCMDDATA, kPagesPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IINITIALDRAGPOINT, kPagesPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEPAGESPANELUTILS, kPagesPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDCOLORCOUNT, kPagesPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESPANELSELECTIONOBSERVER, kPagesPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTERNATELAYOUTUIDDATA, kPagesPanelPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ITIPROTATIONDATA, kPagesPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLUMNINVOKEOBSERVER, kPagesPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_MARGINCOLUMNDIALOGUEDATA, kPagesPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGECBSELECTIONOBSERVER, kPagesPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IWARNINGICONSIZEADJUST, kPagesPanelPrefix + 17)


// <Implementation ID>
// Implementation IDs
// Pages panel implementation IDs
DECLARE_PMID(kImplementationIDSpace, kPagesPanelImpl, kPagesPanelPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kLayoutPagesSubPanelImpl, kPagesPanelPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kMasterPagesSubPanelImpl, kPagesPanelPrefix + 3 )
DECLARE_PMID(kImplementationIDSpace, kPagesPanelCursorProviderImpl, kPagesPanelPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kPagesPanelObserverImpl, kPagesPanelPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kMasterPagesSubPanelObserverImpl, kPagesPanelPrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kLayoutPagesSubPanelObserverImpl, kPagesPanelPrefix + 7 )
DECLARE_PMID(kImplementationIDSpace, kPageTabEventHandlerImpl, kPagesPanelPrefix + 8 )
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetEventHandlerImpl, kPagesPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetControllerImpl, kPagesPanelPrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kPagesPanelStatusViewImpl, kPagesPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelStatusPendingUpdateControllerImpl, kPagesPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelMenuComponentImpl, kPagesPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kColumnMarginMenuActionImpl, kPagesPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelNewButtonObserverImpl, kPagesPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelDeleteButtonObserverImpl, kPagesPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPageTabPanoramaImpl, kPagesPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelResizeRuleImpl, kPagesPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPagesSubPanelResizeRuleImpl, kPagesPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLayoutSpreadWidgetControllerImpl, kPagesPanelPrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetDragDropSourceImpl, kPagesPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetDDSourceImpl, kPagesPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetControlViewImpl, kPagesPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPageTabControllerImpl, kPagesPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPageTabControlViewImpl, kPagesPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetControllerImpl, kPagesPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetEventHandlerImpl, kPagesPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelUIDListControlDataImpl, kPagesPanelPrefix + 28)

// NewMaster dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kNewMasterDialogControllerImpl, kPagesPanelPrefix + 29)

// ApplyMaster dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kApplyMasterDialogControllerImpl, kPagesPanelPrefix + 30)

DECLARE_PMID(kImplementationIDSpace, kNewMasterDialogObserverImpl, kPagesPanelPrefix + 31)

// MasterInfo dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kMasterInfoDialogControllerImpl, kPagesPanelPrefix + 32)

// ColumMargin implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kColumnMarginDialogControllerImpl, kPagesPanelPrefix + 33)

// New page dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kNewPageDialogObserverImpl, kPagesPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kNewPageDialogControllerImpl, kPagesPanelPrefix + 35)

// Palette options dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kPagesPanelOptionsDlgContImpl, kPagesPanelPrefix + 36)

// ColumMargin implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kColumnMarginDialogObserverImpl, kPagesPanelPrefix + 37)

// Move page dialog implementation IDs
DECLARE_PMID(kImplementationIDSpace, kMovePageDialogControllerImpl,	kPagesPanelPrefix + 38)

// More Palette options dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kPagesPanelOptionsDialogObserverImpl, kPagesPanelPrefix + 39)

// Delete page dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kDeletePageDialogControllerImpl, kPagesPanelPrefix + 40)

// Insert page drag drop dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kInsertPageDragDropDialogControllerImpl, kPagesPanelPrefix + 41)

// Drag and Drop implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kPageTabDragDropSourceImpl, kPagesPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPagesDeleteDragDropTargetImpl, kPagesPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kPagesDuplicateDragDropTargetImpl, kPagesPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kCreateSpreadOfMasterTargetImpl, kPagesPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kCreateMasterOfSpreadTargetImpl, kPagesPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterToPageTargetImpl, kPagesPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSpreadDragDropTargetImpl, kPagesPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPageDEHandlerImpl, kPagesPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPagesDEHandlerImpl, kPagesPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSpreadDEHandlerImpl, kPagesPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kSpreadsDEHandlerImpl, kPagesPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kMasterPageDEHandlerImpl, kPagesPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadDEHandlerImpl, kPagesPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadsDEHandlerImpl, kPagesPanelPrefix + 55)

DECLARE_PMID(kImplementationIDSpace, kSpreadStaticTextViewImpl, kPagesPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kLayoutPagesPanoramaImpl, kPagesPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSubPanelEventHandlerImpl, kPagesPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetPanelViewImpl, kPagesPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetPanelViewImpl, kPagesPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPageTabWidgetTipImpl, kPagesPanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kNewPageButtonWidgetTipImpl, kPagesPanelPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kSpreadStaticTextWidgetTipImpl, kPagesPanelPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPagesSubPanelControllerImpl, kPagesPanelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kSetPagesPanelPrefsCmdImpl, kPagesPanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kCPagesPanelPrefsImpl, kPagesPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelPrefsCmdDataImpl, kPagesPanelPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadStaticTextViewImpl, kPagesPanelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kMasterListStaticTextViewImpl, kPagesPanelPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kSpreadWidgetTipImpl, kPagesPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetTipImpl, kPagesPanelPrefix + 71)

// Save prefs to Palette Workspaces
DECLARE_PMID(kImplementationIDSpace, kPagesPanelXMLGeneratorImpl, kPagesPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelSAXHandlerImpl, kPagesPanelPrefix + 73)

DECLARE_PMID(kImplementationIDSpace, kMasterPagesSubPanelControllerImpl, kPagesPanelPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kMovePageDialogObserverImpl, kPagesPanelPrefix + 75)

// Create Alternate Layout dialog implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kCreateAlternateLayoutDialogControllerImpl, kPagesPanelPrefix + 76)

// ---- Moved from the Master Pages plug-in
DECLARE_PMID(kImplementationIDSpace, kPagesPanelGrabberToolImpl, kPagesPanelPrefix + 77)	// ID for a tracker, not a real impl
DECLARE_PMID(kImplementationIDSpace, kPagesPanelGrabberTrackerImpl, kPagesPanelPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelGrabberTrackerRegisterImpl, kPagesPanelPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kMovesPagesTargetDocumentImpl, kPagesPanelPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kMasterPageTestMenuImpl, kPagesPanelPrefix + 81)
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kInsertPageDragDropDialogObserverImpl, kPagesPanelPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelScriptProviderImpl, kPagesPanelPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kMasterPagesPanoramaImpl, kPagesPanelPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kPrivatePagesPanelUtilsImpl, kPagesPanelPrefix + 85)

// Move master dialog implementation IDs
DECLARE_PMID(kImplementationIDSpace, kMoveMasterDialogControllerImpl,	kPagesPanelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kLoadMasterPageAlertDialogControllerImpl, kPagesPanelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kLoadMasterPageAlertDialogObserverImpl, kPagesPanelPrefix + 88)

DECLARE_PMID(kImplementationIDSpace, kAlternateLayoutNameILEEditingEHImpl, kPagesPanelPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kDynamicPageColorLabelMenuImpl, kPagesPanelPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kOwnerDrawPageColorLabelMenuImpl, kPagesPanelPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kPageColorLabelMenuElementViewImpl, kPagesPanelPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kPageSizeGroupObserverImpl, kPagesPanelPrefix + 93)
// gap
DECLARE_PMID(kImplementationIDSpace, kAlternateLayoutNameTextValidationImpl, kPagesPanelPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAlternateLayoutNameEditObserverImpl, kPagesPanelPrefix + 96)

DECLARE_PMID(kImplementationIDSpace, kPagesPanelSelectionObserverImpl, kPagesPanelPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kPageSizesMenuButtonEHImpl, kPagesPanelPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelPageSizesActionComponentImpl, kPagesPanelPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kPagesPanelPageSizeObserverImpl, kPagesPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kAlternateLayoutColumnHeaderObserverImpl, kPagesPanelPrefix + 101)

//DECLARE_PMID(kImplementationIDSpace, kHTML5PaginationOptionsDialogControllerImpl, kPagesPanelPrefix + 102)
//DECLARE_PMID(kImplementationIDSpace, kHTML5PaginationOptionsDialogObserverImpl, kPagesPanelPrefix + 103)

DECLARE_PMID(kImplementationIDSpace, kMasterPagesSubMasterPanelImpl, kPagesPanelPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kLayoutPagesSubMasterPanelImpl, kPagesPanelPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadWidgetPreChildEventHandlerImpl, kPagesPanelPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kColumnMarginPanelObserverImpl, kPagesPanelPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kEditPagesButtonObserverImpl, kPagesPanelPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kPageNumberComboBoxObserverImpl, kPagesPanelPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kPageNumberNewButtonObserverImpl, kPagesPanelPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kPageNumberDeleteButtonObserverImpl, kPagesPanelPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kMarginColumnDlgDataImpl, kPagesPanelPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kPageSelComboBoxSelectionObserverImpl, kPagesPanelPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kPageSelectionComboBoxObserverImpl, kPagesPanelPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kPageSelectionNewButtonObserverImpl, kPagesPanelPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kPageSelectionDeleteButtonObserverImpl, kPagesPanelPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kPageSelectionTextValidation, kPagesPanelPrefix + 118)

// <Widget ID>
// Widget IDs:
// NewMaster dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kNewMasterDialogWidgetID, kPagesPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kNewMasterMasterSpreadPopupWidgetID, kPagesPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kNewMasterEditNameWidgetID, kPagesPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kNewMasterNPagesWidgetID, kPagesPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kNewMasterEditPrefixWidgetID, kPagesPanelPrefix + 5)

// ApplyMaster dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kApplyMasterDialogWidgetID, kPagesPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kApplyMasterPageRangeWidgetID, kPagesPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kApplyMasterMasterSpreadPopupWidgetID, kPagesPanelPrefix + 8)

// Create Alternate Layout dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kCreateAlternateLayoutDialogWidgetID, kPagesPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutNameStaticTextWidgetID, kPagesPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutNameEditWidgetID, kPagesPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutPageSizeStaticTextWidgetID, kPagesPanelPrefix + 15)

// MasterInfo dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kMasterInfoDialogWidgetID, kPagesPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kMasterInfoEditNameWidgetID, kPagesPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kMasterInfoMasterSpreadPopupWidgetID, kPagesPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kMasterInfoNPagesWidgetID, kPagesPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kMasterInfoEditPrefixWidgetID, kPagesPanelPrefix + 20)

// ColumnMargin dialog widget IDs:
DECLARE_PMID(kWidgetIDSpace, kMarginEditTopWidgetID, kPagesPanelPrefix + 21 )
DECLARE_PMID(kWidgetIDSpace, kMarginTopNudgeWidgetID, kPagesPanelPrefix + 22 )
DECLARE_PMID(kWidgetIDSpace, kMarginEditBottomWidgetID, kPagesPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kMarginBottomNudgeWidgetID, kPagesPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kMarginEditInsideWidgetID, kPagesPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kMarginInsideNudgeWidgetID, kPagesPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kMarginEditOutsideWidgetID, kPagesPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kMarginOutsideNudgeWidgetID, kPagesPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kMarginTopTextWidgetID, kPagesPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kMarginBottomTextWidgetID, kPagesPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kMarginLeftTextWidgetID, kPagesPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kMarginRightTextWidgetID, kPagesPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kMarginInsideTextWidgetID, kPagesPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kMarginOutsideTextWidgetID, kPagesPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kMarginGroupTextWidgetID, kPagesPanelPrefix + 35)

DECLARE_PMID(kWidgetIDSpace, kColumnNumberEditWidgetID, kPagesPanelPrefix + 36 )
DECLARE_PMID(kWidgetIDSpace, kColumnNumberNudgeWidgetID, kPagesPanelPrefix + 37 )
DECLARE_PMID(kWidgetIDSpace, kColumnHGutterEditWidgetID, kPagesPanelPrefix + 38 )
DECLARE_PMID(kWidgetIDSpace, kColumnHGutterNudgeWidgetID, kPagesPanelPrefix + 39 )
DECLARE_PMID(kWidgetIDSpace, kColumnVGutterEditWidgetID, kPagesPanelPrefix + 40 )
DECLARE_PMID(kWidgetIDSpace, kColumnVGutterNudgeWidgetID, kPagesPanelPrefix + 41 )
DECLARE_PMID(kWidgetIDSpace, kColumnNumberStaticTextWidgetID, kPagesPanelPrefix + 42 )
DECLARE_PMID(kWidgetIDSpace, kColumnGutterStaticTextWidgetID, kPagesPanelPrefix + 43 )
DECLARE_PMID(kWidgetIDSpace, kColumnDirectionStaticTextWidgetID, kPagesPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kColumnGroupTextWidgetID, kPagesPanelPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kColumnDirectionClusterWidgetID, kPagesPanelPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kColumnDirectionWidgetID, kPagesPanelPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kColumnSizePanelWidgetID, kPagesPanelPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kColumnSizeTitleWidgetID, kPagesPanelPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kColumnSizeInfoWidgetID, kPagesPanelPrefix + 50)

// Pages panel widget IDs:
DECLARE_PMID(kWidgetIDSpace, kPagesContainerWidgetID, kPagesPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kSpreadTextWidgetID, kPagesPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kLayoutPagesSubPanelWidgetID, kPagesPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kMasterPagesSubPanelWidgetID, kPagesPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelWidgetID, kPagesPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelControlStripWidgetID, kPagesPanelPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kLayoutPagesScrollBarWidgetID, kPagesPanelPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kMasterPagesScrollBarWidgetID, kPagesPanelPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelNewButtonWidgetID, kPagesPanelPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelDeleteButtonWidgetID, kPagesPanelPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kPagesStatusWidgetID, kPagesPanelPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelSplitterWidgetID, kPagesPanelPrefix + 62)

// Widget IDs for Insert Page (within a document)
DECLARE_PMID(kWidgetIDSpace, kNewPageDialogWidgetID, kPagesPanelPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kNewPageNPagesWidgetID, kPagesPanelPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kNewPageMasterPopupWidgetID, kPagesPanelPrefix + 65 )
DECLARE_PMID(kWidgetIDSpace, kNewPageInsertOptionPopupWidgetID, kPagesPanelPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kNewPagePageNumberWidgetId, kPagesPanelPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kNewPagePageNumberNudgeWidgetId, kPagesPanelPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kMarginsAutoLayoutCheckboxWidgetID, kPagesPanelPrefix + 69)

// Misc Widget IDs
DECLARE_PMID(kWidgetIDSpace, kLayoutPagesHScrollBarWidgetID, kPagesPanelPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutNameTextWidgetID, kPagesPanelPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kMarginChainWidgetID, kPagesPanelPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kToPageTextWidgetId, kPagesPanelPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kApplyTextWidgetId, kPagesPanelPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutColumnHeaderPanelWidgetID, kPagesPanelPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutColumnHeaderSeparatorWidgetID, kPagesPanelPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutNameElementWidgetID, kPagesPanelPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPrefixTextWidgetId, kPagesPanelPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kNameTextWidgetId, kPagesPanelPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kNumPagesTextWidgetId, kPagesPanelPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kBasedOnTextWidgetId, kPagesPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kName2TextWidgetId, kPagesPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kPagesTextWidgetId, kPagesPanelPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kMarginNColumnParentWidgetId, kPagesPanelPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kMarginGroupWidgetId, kPagesPanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kColumnGroupWidgetId, kPagesPanelPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kPageTabWidgetID, kPagesPanelPrefix + 87)
// gap
DECLARE_PMID(kWidgetIDSpace, kLayoutSpreadParentWidgetId, kPagesPanelPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kMasterSpreadParentWidgetId, kPagesPanelPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kNumberPagesLabelWidgetId, kPagesPanelPrefix + 92)

// pages panel options dialog widget IDs:
DECLARE_PMID(kWidgetIDSpace, kPagesThumbnailsCheckboxWidgetID, kPagesPanelPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kMastersThumbnailsCheckboxWidgetID, kPagesPanelPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelOptionsDialogWidgetID, kPagesPanelPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelPagesGroupWidgetID, kPagesPanelPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelPagesGroupTitleTextWidgetID, kPagesPanelPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kPagesIconSizeTextWidgetID, kPagesPanelPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kPagesIconSizePopupWidgetID, kPagesPanelPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutPopupMenuWidgetID, kPagesPanelPrefix + 100)

DECLARE_PMID(kWidgetIDSpace, kPagesPanelMastersGroupWidgetID, kPagesPanelPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelMastersGroupTitleTextWidgetID, kPagesPanelPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kMasterIconSizeTextWidgetID, kPagesPanelPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kMasterIconSizePopupWidgetID, kPagesPanelPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kMastersVerticalCheckboxWidgetID, kPagesPanelPrefix + 105)

DECLARE_PMID(kWidgetIDSpace, kPagesPanelLayoutGroupWidgetID, kPagesPanelPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelLayoutGroupTitleTextWidgetID, kPagesPanelPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelLayoutClusterWidgetID, kPagesPanelPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kPagesOnTopRadioWidgetID, kPagesPanelPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kMastersOnTopRadioWidgetID, kPagesPanelPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelResizeTextWidgetID, kPagesPanelPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelResizePopupWidgetID, kPagesPanelPrefix + 112)

DECLARE_PMID(kWidgetIDSpace, kMasterPagesSubMasterPanelWidgetID, kPagesPanelPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kLayoutPagesSubMasterPanelWidgetID, kPagesPanelPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kEnableAdaptiveLayoutCheckBoxWidgetID, kPagesPanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kAdjustLayoutAccordionWidgetID, kPagesPanelPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kFontOptionParentWidgetID, kPagesPanelPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kAdjustLayoutGroupPanelWidgetID, kPagesPanelPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kAdjustLayoutWarningWidgetID, kPagesPanelPrefix + 119)



// gap

// The following widget ids are used for move page dialog
DECLARE_PMID(kWidgetIDSpace, kMovePageDialogWidgetID,				kPagesPanelPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kMovePagePageRangeWidgetID,			kPagesPanelPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kMovePageOptionPopupWidgetID,			kPagesPanelPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kMovePageNudgeWidgetID,				kPagesPanelPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kMovePageTargetPageNumberWidgetID,		kPagesPanelPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kMovePageDocumentPopupWidgetID,		kPagesPanelPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kMovePageDeletePagesCheckboxWidgetID,	kPagesPanelPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kMovePageComboGroupWidgetID,			kPagesPanelPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kAdjustLayoutAccordion2WidgetID, kPagesPanelPrefix + 128)
// gap

// More pages panel options dialog widget IDs:
DECLARE_PMID(kWidgetIDSpace, kAdjustLayoutWarningJWidgetID, kPagesPanelPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kPagesIconGroupTitleTextWidgetID, kPagesPanelPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kShowTransparencyIconCheckboxWidgetID, kPagesPanelPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kShowTransitionsIconCheckboxWidgetID, kPagesPanelPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kShowRotationIconCheckboxWidgetID, kPagesPanelPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kPagesPanelIconsGroupWidgetID, kPagesPanelPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kIconsWarningIconWidgetID, kPagesPanelPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kIconsWarningTextWidgetID, kPagesPanelPrefix + 138)

// Don't show again alert ids
DECLARE_PMID(kWidgetIDSpace, kDeletePageWillTriggerSmartReflowAlertID, kPagesPanelPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kDeletedPageContainsContentAlertID, kPagesPanelPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kDeleteAlternateLayoutAlertID, kPagesPanelPrefix + 141)
// gap

// More Create Alternate Layout dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutAdjustLayoutStaticTextWidgetID, kPagesPanelPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutAdjustLayoutPopupWidgetID, kPagesPanelPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutCreateStaticTextWidgetID, kPagesPanelPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutTextLinksCheckboxWidgetID, kPagesPanelPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutPageRangeStaticWidgetID, kPagesPanelPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutPageRangeComboBoxWidgetID, kPagesPanelPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutSmartTextReflowCheckboxWidgetID, kPagesPanelPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutCopyTextStylesCheckboxWidgetID, kPagesPanelPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutOptionsGroupLabelWidgetID, kPagesPanelPrefix + 151)

//gap

// DeletePage dialog widget IDs
DECLARE_PMID(kWidgetIDSpace, kDeletePageDialogWidgetID, kPagesPanelPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kDeletePagesTextWidgetId, kPagesPanelPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kDeletePagePageRangeWidgetID, kPagesPanelPrefix + 167)
// gap

// Widget IDs for Insert Page Drag Drop dialog (via drag and drop between documents)
DECLARE_PMID(kWidgetIDSpace, kInsertPageDragDropDialogWidgetID, kPagesPanelPrefix + 173)

// The following widget ids are used for move master dialog
DECLARE_PMID(kWidgetIDSpace, kMoveMasterDialogWidgetID, kPagesPanelPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterDialog1ColumnWidgetID, kPagesPanelPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterSourceStaticTextWidgetID, kPagesPanelPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterSelectionStaticTextWidgetID, kPagesPanelPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterDialog2ColumnWidgetID, kPagesPanelPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterDialog3ColumnWidgetID, kPagesPanelPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kMoveMasterDocumentStaticTextWidgetID, kPagesPanelPrefix + 186)

// The following widget ids are used for load master page alert dialog
DECLARE_PMID(kWidgetIDSpace, kLoadMasterPageAlertDialogWidgetID,	kPagesPanelPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kLoadMasterPageAlertSignWidgetID,		kPagesPanelPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kLoadMasterPageAlertMessageWidgetID,	kPagesPanelPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kRenameMasterPageButtonWidgetID,		kPagesPanelPrefix + 190)

DECLARE_PMID(kWidgetIDSpace, kPagesPanelPageSizesButtonWidgetID,		kPagesPanelPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kAlternateLayoutGripperWidgetID,		kPagesPanelPrefix + 192)

DECLARE_PMID(kWidgetIDSpace, kColumnHGutterWidgetID,		kPagesPanelPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kColumnVGutterWidgetID,		kPagesPanelPrefix + 194)

DECLARE_PMID(kWidgetIDSpace, kMarginLeftWidgetID,			kPagesPanelPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kMarginRightWidgetID,			kPagesPanelPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kMarginInsideWidgetID,			kPagesPanelPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kMarginOutsideWidgetID,		kPagesPanelPrefix + 198)

//For Columns and Margin Kit in Properties Panel
DECLARE_PMID(kWidgetIDSpace, kPageNumberComboGroupWidgetID, kPagesPanelPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kPageNumberLabelWidgetID,		kPagesPanelPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kPageNumberNudgeWidgetID,		kPagesPanelPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kPageNumberComboBoxWidgetID,	kPagesPanelPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kEditPagesButtonWidgetID,		kPagesPanelPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kColumnNumberIconWidgetID,		kPagesPanelPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kColumnGutterIconWidgetID,		kPagesPanelPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kMarginTopIconWidgetID,		kPagesPanelPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kMarginBottomIconWidgetID,		kPagesPanelPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kMarginLeftIconWidgetID,		kPagesPanelPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kMarginInsideIconWidgetID,		kPagesPanelPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kMarginRightIconWidgetID,		kPagesPanelPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kMarginOutsideIconWidgetID,	kPagesPanelPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveDialgoueGroupWidgetID, kPagesPanelPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveDummyEmptyWidgetID, kPagesPanelPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveInformationIconWidgetID, kPagesPanelPrefix + 214)

// <Message ID>
//Message IDs
DECLARE_PMID(kMessageIDSpace, kColumMarginDialogInvokedMessage, kPagesPanelPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kPagesPanelSelectionChangedMessage, kPagesPanelPrefix + 2)

	
// <Action ID>
DECLARE_PMID(kActionIDSpace, kPagesPanelActionID, kPagesPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kColumnsMarginsActionID, kPagesPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kNewPageActionID, kPagesPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kNewMasterPageActionID, kPagesPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kDuplicatePageActionID, kPagesPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kDeletePageActionID, kPagesPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kSelectUnusedMastersActionID, kPagesPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kPagesSep1ActionID, kPagesPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kMasterOptionsActionID, kPagesPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kApplyMasterToPagesActionID, kPagesPanelPrefix + 10)

DECLARE_PMID(kActionIDSpace, kRemoveOverridesActionID, kPagesPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kPagesSep2ActionID, kPagesPanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kSaveAsMasterActionID, kPagesPanelPrefix + 13)
DECLARE_PMID(kActionIDSpace, kPagesSep3ActionID, kPagesPanelPrefix + 14)
DECLARE_PMID(kActionIDSpace, kPagesSep4ActionID, kPagesPanelPrefix + 15)
DECLARE_PMID(kActionIDSpace, kKeepSpreadTogetherActionID, kPagesPanelPrefix + 16)
DECLARE_PMID(kActionIDSpace, kAllowShuffleActionID, kPagesPanelPrefix + 17)
DECLARE_PMID(kActionIDSpace, kPagesPanelOptionsActionID, kPagesPanelPrefix + 18)
DECLARE_PMID(kActionIDSpace, kBreakMasterLinkActionID, kPagesPanelPrefix + 19)
DECLARE_PMID(kActionIDSpace, kOverrideAllMasterActionID, kPagesPanelPrefix + 20)

DECLARE_PMID(kActionIDSpace, kMovePageActionID,	kPagesPanelPrefix + 21)
DECLARE_PMID(kActionIDSpace, kImportMasterPageActionID, kPagesPanelPrefix + 22)
DECLARE_PMID(kActionIDSpace, kPrimaryTextFrameActionID, kPagesPanelPrefix + 23)
DECLARE_PMID(kActionIDSpace, kDeleteSpreadSepActionID, kPagesPanelPrefix + 24)
DECLARE_PMID(kActionIDSpace, kLayoutPagesSepActionID, kPagesPanelPrefix + 25)
DECLARE_PMID(kActionIDSpace, kShowMasterPageItemsActionID, kPagesPanelPrefix + 26)

DECLARE_PMID(kActionIDSpace, kNewPageContextActionID, kPagesPanelPrefix + 27)
DECLARE_PMID(kActionIDSpace, kMovePageContextActionID, kPagesPanelPrefix + 28)
DECLARE_PMID(kActionIDSpace, kNewMasterPageContextActionID, kPagesPanelPrefix + 29)
DECLARE_PMID(kActionIDSpace, kSelectUnusedMastersContextActionID, kPagesPanelPrefix + 30)

DECLARE_PMID(kActionIDSpace, kApplyMasterToPagesContextActionID, kPagesPanelPrefix + 31)

DECLARE_PMID(kActionIDSpace, kDeletePageDialogActionID, kPagesPanelPrefix + 32)

DECLARE_PMID(kActionIDSpace, kAllowOverridesActionID, kPagesPanelPrefix + 33)
DECLARE_PMID(kActionIDSpace, kCreateAlternateSepActionID, kPagesPanelPrefix + 34)
DECLARE_PMID(kActionIDSpace, kAllowOverridesContextActionID, kPagesPanelPrefix + 35)

DECLARE_PMID(kActionIDSpace, kRotateSpreadTo90CWActionID, kPagesPanelPrefix + 36)	
DECLARE_PMID(kActionIDSpace, kRotateSpreadTo90CCWActionID, kPagesPanelPrefix + 37)	
DECLARE_PMID(kActionIDSpace, kRotateSpreadTo180ActionID, kPagesPanelPrefix + 38)	
DECLARE_PMID(kActionIDSpace, kRotateSpreadTo0ActionID, kPagesPanelPrefix + 39)	
DECLARE_PMID(kActionIDSpace, kRotateSpreadSepActionID, kPagesPanelPrefix + 40)

DECLARE_PMID(kActionIDSpace, kRotateSpreadBySepActionID, kPagesPanelPrefix + 41)
DECLARE_PMID(kActionIDSpace, kRotateSpreadBy90CWActionID, kPagesPanelPrefix + 42)
DECLARE_PMID(kActionIDSpace, kRotateSpreadBy90CCWActionID, kPagesPanelPrefix + 43)
DECLARE_PMID(kActionIDSpace, kRotateSpreadBy180ActionID, kPagesPanelPrefix + 44)
DECLARE_PMID(kActionIDSpace, kViewRotateSpreadSepActionID, kPagesPanelPrefix + 45)
DECLARE_PMID(kActionIDSpace, kPagesSep0ActionID, kPagesPanelPrefix + 46)
DECLARE_PMID(kActionIDSpace, kPageTransitionSepActionID,  kPagesPanelPrefix + 47)
DECLARE_PMID(kActionIDSpace, kChoosePageTransitionActionID,	 kPagesPanelPrefix + 48)
DECLARE_PMID(kActionIDSpace, kEditPageTransitionActionID,	 kPagesPanelPrefix + 49)
DECLARE_PMID(kActionIDSpace, kClearAllPageTransitionActionID,	 kPagesPanelPrefix + 50)

DECLARE_PMID(kActionIDSpace, kRTChoosePageTransitionActionID,	 kPagesPanelPrefix + 51)
DECLARE_PMID(kActionIDSpace, kRTEditPageTransitionActionID,  kPagesPanelPrefix + 52)
DECLARE_PMID(kActionIDSpace, kRTClearTransitionsActionID,	 kPagesPanelPrefix + 53)
DECLARE_PMID(kActionIDSpace, kPageTransitionSep1ActionID,	 kPagesPanelPrefix + 54)
DECLARE_PMID(kActionIDSpace, kPageTransitionSep2ActionID,	 kPagesPanelPrefix + 55)
DECLARE_PMID(kActionIDSpace, kRTPageTransitionSepActionID,	 kPagesPanelPrefix + 56)
DECLARE_PMID(kActionIDSpace, kPageColorLabelMenuDynamicActionID,	 kPagesPanelPrefix + 57)
DECLARE_PMID(kActionIDSpace, kPageColorLabelSep1ActionID,	 kPagesPanelPrefix + 58)
DECLARE_PMID(kActionIDSpace, kPageColorLabelNoneActionID,	 kPagesPanelPrefix + 59)
DECLARE_PMID(kActionIDSpace, kPageColorLabelMasterActionID,	 kPagesPanelPrefix + 60)

DECLARE_PMID(kActionIDSpace, kCreateAlternateLayoutActionID,	 kPagesPanelPrefix + 61)
DECLARE_PMID(kActionIDSpace, kPagesViewHorizontallyActionID,	 kPagesPanelPrefix + 62)
DECLARE_PMID(kActionIDSpace, kPagesViewVerticallyActionID,	 kPagesPanelPrefix + 63)
DECLARE_PMID(kActionIDSpace, kPagesViewByAlternateLayoutActionID,	 kPagesPanelPrefix + 64)
DECLARE_PMID(kActionIDSpace, kPagesPanelPageSizeDynamicActionID,	 kPagesPanelPrefix + 65) 
DECLARE_PMID(kActionIDSpace, kMasterPagesSubMenuSep1ActionID,	 kPagesPanelPrefix + 66) 
DECLARE_PMID(kActionIDSpace, kMasterPagesSubMenuSep2ActionID,	 kPagesPanelPrefix + 67) 
DECLARE_PMID(kActionIDSpace, kCreateAlternateSplitWindowActionID,	 kPagesPanelPrefix + 68)
DECLARE_PMID(kActionIDSpace, kDeleteAlternateLayoutActionID,	 kPagesPanelPrefix + 69)

DECLARE_PMID(kActionIDSpace, kPrintPagesActionID,				 kPagesPanelPrefix + 70)
DECLARE_PMID(kActionIDSpace, kPrintPagesContextActionID,		 kPagesPanelPrefix + 71)
DECLARE_PMID(kActionIDSpace, kDeleteSpreadsInAlternateLayoutActionID,	 kPagesPanelPrefix + 72)
DECLARE_PMID(kActionIDSpace, kPagesSep0_5ActionID,	 kPagesPanelPrefix + 73)
DECLARE_PMID(kActionIDSpace, kNewPageWithoutDialogActionID, kPagesPanelPrefix + 74)

// Reserved for Page Color Flag colors.
DECLARE_PMID(kActionIDSpace, kFirstPageColorLabelMenu,	 kPagesPanelPrefix + 200)
// Do not assign any id's in this range
DECLARE_PMID(kActionIDSpace, kLastPageColorLabelMenu,	 kPagesPanelPrefix + 214)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPagesPanelObjectScriptElement,			kPagesPanelPrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kShowTransparencyIconPropertyScriptElement,kPagesPanelPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kIconSizePropertyScriptElement,			kPagesPanelPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalViewPropertyScriptElement,		kPagesPanelPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kMasterIconSizePropertyScriptElement,		kPagesPanelPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kMasterVerticalViewPropertyScriptElement,	kPagesPanelPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kPagesThumbnailsPropertyScriptElement,		kPagesPanelPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kMastersThumbnailsPropertyScriptElement,	kPagesPanelPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kShowTransitionsIconPropertyScriptElement,	kPagesPanelPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kPagesPanelResizePropertyScriptElement,	kPagesPanelPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kPagesOnTopPropertyScriptElement,			kPagesPanelPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kShowRotationIconPropertyScriptElement,	kPagesPanelPrefix + 12)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kIconSizeEnumScriptElement,				kPagesPanelPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kPagesPanelResizeEnumScriptElement,		kPagesPanelPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kViewSettingScriptElement,					kPagesPanelPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kViewSettingEnumScriptElement,				kPagesPanelPrefix + 23)


//GUIDS
// {7A700041-3346-438d-89C6-3469C36CB0B8}
#define kPagesPanel_CLSID     { 0x7a700041, 0x3346, 0x438d, { 0x89, 0xc6, 0x34, 0x69, 0xc3, 0x6c, 0xb0, 0xb8 } }

//ScriptIDs
enum PagesPanelScriptIDs {
	c_PagesPanel			=	'pgsp',

	p_PagesPanel			=	'PgsP',
	p_IconSize				=	'picn',
	p_MasterIconSize		=	'pmic',
	p_VerticalView			=	'pvrt',	// Legacy
	p_ViewSetting			=	'pvst',
	p_MasterVerticalView	=	'pmvt',
	p_PagesPanelResize		=	'prsz',
	p_PagesOnTop			=	'ppot',

	en_PageIconSize			=	'isze',
	en_PageIconExtraSmall	=	'pesm',
	en_PageIconSmall		=	'psml',
	en_PageIconMedium		=	'pmed',
	en_PageIconLarge		=	'pLrg',
	en_PageIconExtraLarge	=	'pelg',
	en_PageIconExtraExtraLarge	=	'pxxl',

	en_PagesPanelResize		=	'pprz',
	en_ProportionalResize	=	'pppr',
	en_PagesFixed			=	'ppfx',
	en_MastersFixed			=	'ppmf',

	p_PagesThumbnails		=	'pppt',
	p_MastersThumbnails		=	'ppmt',

	p_TransparencyIcon		=	'pptr',
	p_TransitionsIcon		=	'ppta',
	p_RotationIcon			=	'ppro',

	en_ViewSettingsEnum		=	'vpse',
	en_Vertically			=	'vrow',
	en_Horizontally			=	'hstk',
	en_AlternateLayout		=	'vstk'
} ;


// Resource IDs for Pages Panel dialogs
#define kPagesPanelRsrcID				2000		// Resource ID of DocPalette Window
#define kColumnMarginDialogRsrcID		2100		// resource id of columns/margins dialog
#define kMasterSubPanelRsrcID			2200		// Resource ID of MasterPalette Window
#define kLayoutSpreadWidgetRsrcID		2300		// Resource ID of Layout spread widget
#define kMasterSpreadWidgetRsrcID		2400		// Resource ID of Master spread widget
#define kNewPageDialogRsrcID			2500		// resource id of Insert Page dialog
#define kMasterSpreadListWidgetRsrcID	2600		// Resource ID of Master spread list widget
#define kMasterInfoDialogRsrcID			2700		// Resource ID of New master dialog
#define kApplyMasterDialogRsrcID		2800		// Resource ID of New master dialog
#define kNewMasterDialogRsrcID			2900		// Resource ID of New master dialog
#define kMovePageDialogRsrcID			3000		// Resource ID of Move page dialog
#define kSyncMasterPageDialogRsrcID		3100		// Resource ID of Synchronize master page dialog
#define kDeletePageDialogRsrcID			3200		// Resource ID of Delete page dialog
#define kInsertPageDragDropDialogRsrcID	3300		// Resource ID of Insert page dialog for drag and drop between documents
#define kPagesPanelOptionsDialogRsrcID	3400		// Resource ID of Pages Panel Options dialog
#define kMoveMasterDialogRsrcID			3500		// Resource ID of Move Master dialog
#define kLoadMasterPageAlertDialogRsrcID 3600		// Resource ID of Load master page alert dialog
#define kCreateAlternateLayoutDialogRsrcID 3700		// Resource ID of Create Alternate Layout dialog
#define kAlternateLayoutNameElementWidgetRsrcID 3800	// Resource ID of Create Alternate Layout name container widget for columns in pages panel. One at the top of each column.
//#define kHTML5PaginationOptionsDialogRsrcID 3900	// Resource ID of HTML5 Pagination Options dialog

#endif // __PagesPanelID__

