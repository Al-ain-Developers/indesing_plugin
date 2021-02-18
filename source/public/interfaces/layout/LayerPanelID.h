//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LayerPanelID.h $
//  
//  Owner: Stacy Molitor
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
//  Contains IDs used by the layers plug-in
//  
//========================================================================================

#ifndef __LayerPanelID__
#define __LayerPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLayerPanelPrefix	RezLong(0x4800)

// <Start IDC>
// PluginID
#define kLayerPanelPluginName 			"Layers Panel"
DECLARE_PMID(kPlugInIDSpace, kLayerPanelPluginID, kLayerPanelPrefix + 1)

// <Class ID>
//========================================================================================
// ----- ClassIDs -----
//========================================================================================


DECLARE_PMID(kClassIDSpace, kLayerTreeElementBoss, kLayerPanelPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kNewLayerButtonBoss, kLayerPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDeleteLayerButtonBoss, kLayerPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kLayerPanelActiveBoss, kLayerPanelPrefix + 5)
//gap
DECLARE_PMID(kClassIDSpace, kLayerPanelElementPencilBoss, kLayerPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLayerPanelElementNameBoss, kLayerPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kLayerPanelEyeballBoss, kLayerPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kLayerPanelPencilBoss, kLayerPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kLayerPanelSwatchBoss, kLayerPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLayerPanelNameBoss, kLayerPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kLayerPanelSelectionProxyBoss, kLayerPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kLayerPageItemPencilBoss, kLayerPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kLayerOptionsDlgBoss, kLayerPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kLayerProxyDEHandlerBoss, kLayerPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kLayerPanelMenuComponentBoss, kLayerPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kLayerZOrderDEHandlerBoss, kLayerPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kLayerEyeDEHandlerBoss, kLayerPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kLayerPencilDEHandlerBoss, kLayerPanelPrefix + 22)

// ---- Moved here from the Layer plug-in.
DECLARE_PMID(kClassIDSpace, kLayerStartupShutdownBoss, kLayerPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kLayerListLayoutActionBoss, kLayerPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kLayerTestMenuBoss, kLayerPanelPrefix + 26)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kLayerPanelBoss, kLayerPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kLayerPanelTreeWidgetBoss, kLayerPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kPageItemDupDeleteDEHandlerBoss, kLayerPanelPrefix + 29)
DECLARE_PMID(kClassIDSpace, kPageItemZOrderDEHandlerBoss, kLayerPanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPageItemSelectionProxyBoss, kLayerPanelPrefix + 31)
DECLARE_PMID(kClassIDSpace, kLayerPageItemNameBoss, kLayerPanelPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace, kDV_LayerTreeElementBoss, kLayerPanelPrefix + 37)

// <Interface ID>
//========================================================================================
// ----- Interface IDs -----
//========================================================================================

DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGTYPEDATA, kLayerPanelPrefix + 1) // Using IntDataImplementation

// ---- Moved here from the Layer plug-in.
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTLAYERLISTOBSERVER, kLayerPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERUIUTILS, kLayerPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERSELECTIONOBSERVER, kLayerPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERSUITE, kLayerPanelPrefix + 5)
// ---- end move.
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETNEWLAYER, kLayerPanelPrefix + 6) // Using kPMUnknownDataImpl
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONPROXYDRAWDATA, kLayerPanelPrefix + 7) 
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERPANELDOCUMENTDATA, kLayerPanelPrefix + 8) 

// <Implementation ID>
//========================================================================================
// ----- Implementation IDs -----
//========================================================================================

//gap
DECLARE_PMID(kImplementationIDSpace, kLayerPanelObserverImpl, kLayerPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLayerNameEHImpl, kLayerPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kNewLayerButtonObserverImpl, kLayerPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDeleteLayerButtonObserverImpl, kLayerPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelMenuComponentImpl, kLayerPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteLayoutCSBExtImpl, kLayerPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelEyeballObserverImpl, kLayerPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelPencilObserverImpl, kLayerPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelNameILEEditingAttributesImpl, kLayerPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelNameObserverImpl, kLayerPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelProxyObserverImpl, kLayerPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelNameViewImpl, kLayerPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLayerSubwidgetEHImpl, kLayerPanelPrefix + 15)

//gap
DECLARE_PMID(kImplementationIDSpace, kLayerSwatchViewImpl, kLayerPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSelectionProxyViewImpl, kLayerPanelPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kLayerNameViewImpl, kLayerPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSelectionProxyDrawDataImpl, kLayerPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLayerOptionsDlgControllerImpl, kLayerPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelSelectionObserverImpl, kLayerPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kActiveViewImpl, kLayerPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLayerDuplicateDragDropTargetImpl, kLayerPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kProxyViewDragDropSourceImpl, kLayerPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLayerProxyDragDropSourceEHImpl, kLayerPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPageItemDupDeleteDEHandlerImpl, kLayerPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kLayerProxyDEHandlerImpl, kLayerPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kLayerZOrderDragDropSourceImpl, kLayerPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kLayerTreeDragDropTargetImpl, kLayerPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kLayerZOrderDEHandlerImpl, kLayerPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kLayerDeleteDragDropTargetImpl, kLayerPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kLayerEyeDragDropSourceImpl, kLayerPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kLayerEyeDragDropTargetImpl, kLayerPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kLayerEyeDEHandlerImpl, kLayerPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kLayerEyeDragDropSourceEHImpl, kLayerPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kLayerPencilDragDropSourceImpl, kLayerPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kLayerPencilDragDropTargetImpl, kLayerPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kLayerPencilDEHandlerImpl, kLayerPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kLayerPencilDragDropSourceEHImpl, kLayerPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPointyHandCursorProviderImpl, kLayerPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelResizeRuleImpl, kLayerPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelViewImpl, kLayerPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kLayerElementResizeRuleImpl, kLayerPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLayerElementViewImpl, kLayerPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kProxyWidgetTipImpl, kLayerPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kActiveLayerWidgetTipImpl, kLayerPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kLayerCellWidgetFactoryImpl, kLayerPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kLayerListBoxControlDataImpl, kLayerPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kLayerCellWidgetControllerImpl, kLayerPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kLayerWidgetListBoxHelperImpl, kLayerPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelElementObserverImpl, kLayerPanelPrefix + 52)

// ---- Moved here from the Layer plug-in.
DECLARE_PMID(kImplementationIDSpace, kCLayoutLayerListObserverImpl, kLayerPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kLayerStartupShutdownImpl, kLayerPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kLayerSelectionObserverImpl, kLayerPanelPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteDefaultCSBImpl, kLayerPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteLayoutCSBImpl, kLayerPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteIntegratorImpl, kLayerPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteTableCSBImpl, kLayerPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kLayerSuiteTextCSBImpl, kLayerPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kLayerUIUtilsImpl, kLayerPanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kLayerListLayoutActionImpl, kLayerPanelPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kLayerTestMenuImpl, kLayerPanelPrefix + 64)
// ---- end move
DECLARE_PMID(kImplementationIDSpace, kLayerOptionsDlgObserverImpl, kLayerPanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelTreeViewAdapterImpl, kLayerPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelTreeViewWidgetMgrImpl, kLayerPanelPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kLayerPanelTreeObserverImpl, kLayerPanelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kLayerTreeRowPanelEHImpl, kLayerPanelPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kLayerPageItemPencilObserverImpl, kLayerPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kLayerPageItemPencilEHImpl, kLayerPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kLayerNameTextValidationImpl, kLayerPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kPageItemZOrderDEHandlerImpl, kLayerPanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kLayerPageItemNameEHImpl, kLayerPanelPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kLayersPanelTreeViewControllerImpl, kLayerPanelPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kPageItemNameEditObserverImpl, kLayerPanelPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kLayerNameEditObserverImpl, kLayerPanelPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kLayersPanelXMLGeneratorImpl, kLayerPanelPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kLayersPanelSAXHandlerImpl, kLayerPanelPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kLayersTreeViewTypeAheadImpl, kLayerPanelPrefix + 80)

// <Widget ID>
//========================================================================================
// ----- Widget IDs -----
//========================================================================================

//gap
DECLARE_PMID(kWidgetIDSpace, kLayerDeleteButtonWidgetID, kLayerPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLayerNewButtonWidgetID, kLayerPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kLayerListSmallWidgetID, kLayerPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kLayerStatusWidgetID, kLayerPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementEyeballWidgetID, kLayerPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementPencilWidgetID, kLayerPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementNameWidgetID, kLayerPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementSwatchWidgetID, kLayerPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementProxyWidgetID, kLayerPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementActiveWidgetID, kLayerPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kLayerPageItemElementWidgetID, kLayerPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kLayerPageItemElementTextWidgetID, kLayerPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLayerPageItemElementPencilWidgetID, kLayerPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kLayerControlStripWidgetID, kLayerPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPageItemSelectionProxyWidgetID, kLayerPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kLayerTreeBorderPanelWidgetID, kLayerPanelPrefix + 17)

// IDs for Layer Options dialog
DECLARE_PMID(kWidgetIDSpace, kLayerNameStaticWidgetID, kLayerPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kLayerNameWidgetID, kLayerPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kLayerShowCheckboxWidgetID, kLayerPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLayerLockCheckboxWidgetID, kLayerPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kLayerShowGuidesCheckboxWidgetID, kLayerPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kLayerLockGuidesCheckboxWidgetID, kLayerPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kLayerColorStaticWidgetID, kLayerPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kLayerSwatchWidgetID, kLayerPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kLayerColorDropDownWidgetID, kLayerPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kLayerListElementNamePanelWidgetID, kLayerPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kLayerOptionsParentWidgetId, kLayerPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kLayerGenericWidgetId, kLayerPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kLayerParentWidgetId, kLayerPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kLayerListParentWidgetId, kLayerPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kLayerPanelTreeWidgetID, kLayerPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kLayerPanelSeparatorWidgetID, kLayerPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kIgnoreTextWrapCheckboxWidgetID, kLayerPanelPrefix + 36)
//DECLARE_PMID(kWidgetIDSpace, kLayerTextWrapGroupWidgetId, kLayerPanelPrefix + 37)
//DECLARE_PMID(kWidgetIDSpace, kLayerTextWrapGroupTitleWidgetId, kLayerPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kUILayerColorWidgetID, kLayerPanelPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kColorNameWidgetID, kLayerPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kUILayerNameStaticWidgetID, kLayerPanelPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kLayerPrintCheckboxWidgetID, kLayerPanelPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kLayerPageItemNamePanelWidgetID, kLayerPanelPrefix + 43)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kLayerPanelActionID, kLayerPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewLayerActionID, kLayerPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDeleteLayerOrPageItemActionID, kLayerPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kLayerOptionsActionID, kLayerPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kShowHideLayersActionID, kLayerPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kLockUnlockLayersActionID, kLayerPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kPasteRemembersLayersActionID, kLayerPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kMergeLayersActionID, kLayerPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kDeleteUnusedLayersActionID, kLayerPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kSmallPaletteRowsActionID, kLayerPanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep1ActionID, kLayerPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep2ActionID, kLayerPanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep3ActionID, kLayerPanelPrefix + 13)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep4ActionID, kLayerPanelPrefix + 14)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep5ActionID, kLayerPanelPrefix + 15)
DECLARE_PMID(kActionIDSpace, kShowAllLayersActionID, kLayerPanelPrefix + 16) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kHideOtherLayersActionID, kLayerPanelPrefix + 17) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kUnlockAllLayersActionID, kLayerPanelPrefix + 18) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kLockOtherLayersActionID, kLayerPanelPrefix + 19) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kHideAllLayersActionID, kLayerPanelPrefix + 20) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kLockAllLayersActionID, kLayerPanelPrefix + 21) // not a real action - just a message
DECLARE_PMID(kActionIDSpace, kDuplicateLayerOrPageItemActionID, kLayerPanelPrefix + 22)
DECLARE_PMID(kActionIDSpace, kSelectLayerContextActionID, kLayerPanelPrefix + 23)
DECLARE_PMID(kActionIDSpace, kNewLayerContextActionID, kLayerPanelPrefix + 24)
DECLARE_PMID(kActionIDSpace, kDeleteLayerContextActionID, kLayerPanelPrefix + 25)
DECLARE_PMID(kActionIDSpace, kLayerOptionsContextActionID, kLayerPanelPrefix + 26)
DECLARE_PMID(kActionIDSpace, kMergeLayersContextActionID, kLayerPanelPrefix + 27)
DECLARE_PMID(kActionIDSpace, kDuplicateLayerContextActionID, kLayerPanelPrefix + 28)
DECLARE_PMID(kActionIDSpace, kSelectLayerPageItemActionID, kLayerPanelPrefix + 29)
DECLARE_PMID(kActionIDSpace, kSelectZoomLayerPageItemActionID, kLayerPanelPrefix + 30)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep6ActionID, kLayerPanelPrefix + 31)
DECLARE_PMID(kActionIDSpace, kUngroupRemembersLayersActionID, kLayerPanelPrefix + 32)

// ----- Tree Node ID types -----
#define kLayerTreeNodeID		kLayerPanelPrefix + 1


#endif // __LayerPanelID__
