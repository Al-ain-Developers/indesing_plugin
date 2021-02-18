//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelFactoryList.h $
//  
//  Owner: robin briggs
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

REGISTER_PMINTERFACE(LayerNameEH, kLayerNameEHImpl)
REGISTER_PMINTERFACE(NewLayerButtonObserver, kNewLayerButtonObserverImpl)
REGISTER_PMINTERFACE(DeleteLayerButtonObserver, kDeleteLayerButtonObserverImpl)
REGISTER_PMINTERFACE(LayerPanelMenuComponent, kLayerPanelMenuComponentImpl)
REGISTER_PMINTERFACE(LayerPanelPencilObserver, kLayerPanelPencilObserverImpl)
REGISTER_PMINTERFACE(LayerPanelEyeballObserver, kLayerPanelEyeballObserverImpl)
REGISTER_PMINTERFACE(LayerElementView, kLayerElementViewImpl)
REGISTER_PMINTERFACE(LayerSwatchView, kLayerSwatchViewImpl)
REGISTER_PMINTERFACE(SelectionProxyView, kSelectionProxyViewImpl)
REGISTER_PMINTERFACE(ActiveView, kActiveViewImpl)
REGISTER_PMINTERFACE(LayerOptionsDlgController, kLayerOptionsDlgControllerImpl)
REGISTER_PMINTERFACE(LayerOptionsDlgObserver, kLayerOptionsDlgObserverImpl)
REGISTER_PMINTERFACE(LayerPanelSelectionObserver, kLayerPanelSelectionObserverImpl)
REGISTER_PMINTERFACE(ProxyViewDragDropSource, kProxyViewDragDropSourceImpl)
REGISTER_PMINTERFACE(LayerProxyDragDropSourceEH, kLayerProxyDragDropSourceEHImpl)
REGISTER_PMINTERFACE(LayerProxyDEHandler, kLayerProxyDEHandlerImpl)
REGISTER_PMINTERFACE(LayerZOrderDragDropSource, kLayerZOrderDragDropSourceImpl)
REGISTER_PMINTERFACE(LayerZOrderDEHandler, kLayerZOrderDEHandlerImpl)
REGISTER_PMINTERFACE(LayerDuplicateDragDropTarget, kLayerDuplicateDragDropTargetImpl)
REGISTER_PMINTERFACE(LayerDeleteDragDropTarget, kLayerDeleteDragDropTargetImpl)
REGISTER_PMINTERFACE(LayerEyeDragDropSource, kLayerEyeDragDropSourceImpl)
REGISTER_PMINTERFACE(LayerEyeDragDropTarget, kLayerEyeDragDropTargetImpl)
REGISTER_PMINTERFACE(LayerEyeDEHandler, kLayerEyeDEHandlerImpl)
REGISTER_PMINTERFACE(LayerEyeDragDropSourceEH, kLayerEyeDragDropSourceEHImpl)
REGISTER_PMINTERFACE(LayerPencilDragDropSource, kLayerPencilDragDropSourceImpl)
REGISTER_PMINTERFACE(LayerPencilDragDropTarget, kLayerPencilDragDropTargetImpl)
REGISTER_PMINTERFACE(LayerPencilDEHandler, kLayerPencilDEHandlerImpl)
REGISTER_PMINTERFACE(LayerPencilDragDropSourceEH, kLayerPencilDragDropSourceEHImpl)
REGISTER_PMINTERFACE(PointyHandCursorProvider, kPointyHandCursorProviderImpl)
REGISTER_PMINTERFACE(ProxyWidgetTip, kProxyWidgetTipImpl)
REGISTER_PMINTERFACE(ActiveLayerWidgetTip, kActiveLayerWidgetTipImpl)

// ---- Moved here from the Layer plug-in.
REGISTER_PMINTERFACE(CLayoutLayerListObserver, kCLayoutLayerListObserverImpl)
REGISTER_PMINTERFACE(LayerStartupShutdown, kLayerStartupShutdownImpl)
REGISTER_PMINTERFACE(LayerSelectionObserver, kLayerSelectionObserverImpl)
REGISTER_PMINTERFACE(LayerSuiteDefaultCSB, kLayerSuiteDefaultCSBImpl)
REGISTER_PMINTERFACE(LayerSuiteLayoutCSB, kLayerSuiteLayoutCSBImpl)
REGISTER_PMINTERFACE(SelectionExt<LayerSuiteLayoutCSB>, kLayerSuiteLayoutCSBExtImpl)
REGISTER_PMINTERFACE(LayerSuiteIntegrator, kLayerSuiteIntegratorImpl)
REGISTER_PMINTERFACE(LayerSuiteTableCSB, kLayerSuiteTableCSBImpl)
REGISTER_PMINTERFACE(LayerSuiteTextCSB, kLayerSuiteTextCSBImpl)
REGISTER_PMINTERFACE(LayerUIUtils, kLayerUIUtilsImpl)
REGISTER_PMINTERFACE(LayerListLayoutAction, kLayerListLayoutActionImpl)
#ifdef DEBUG
REGISTER_PMINTERFACE(LayerTestMenu, kLayerTestMenuImpl)
#endif

REGISTER_PMINTERFACE(LayerPanelTreeViewAdapter, kLayerPanelTreeViewAdapterImpl)
REGISTER_PMINTERFACE(LayerPanelTreeViewWidgetMgr, kLayerPanelTreeViewWidgetMgrImpl)
REGISTER_PMINTERFACE(LayerPanelTreeObserver, kLayerPanelTreeObserverImpl)
REGISTER_PMINTERFACE(LayerTreeRowPanelEH, kLayerTreeRowPanelEHImpl)
REGISTER_PMINTERFACE(LayerPageItemPencilObserver, kLayerPageItemPencilObserverImpl)
REGISTER_PMINTERFACE(LayerPageItemPencilEH, kLayerPageItemPencilEHImpl)
REGISTER_PMINTERFACE(PageItemZOrderDEHandler, kPageItemZOrderDEHandlerImpl)
REGISTER_PMINTERFACE(LayerPanelView, kLayerPanelViewImpl)
REGISTER_PMINTERFACE(LayerPageItemNameEH, kLayerPageItemNameEHImpl)
REGISTER_PMINTERFACE(SelectionProxyDrawData, kSelectionProxyDrawDataImpl)
REGISTER_PMINTERFACE(LayersPanelTreeViewController, kLayersPanelTreeViewControllerImpl)
REGISTER_PMINTERFACE(LayerTreeDragDropTarget, kLayerTreeDragDropTargetImpl)
REGISTER_PMINTERFACE(PageItemNameEditObserver, kPageItemNameEditObserverImpl)
REGISTER_PMINTERFACE(LayerPanelNameILEEditingAttributes, kLayerPanelNameILEEditingAttributesImpl)
REGISTER_PMINTERFACE(LayerPanelNameView, kLayerPanelNameViewImpl)
REGISTER_PMINTERFACE(LayerNameEditObserver, kLayerNameEditObserverImpl)
REGISTER_PMINTERFACE(LayerSubwidgetEH, kLayerSubwidgetEHImpl)
REGISTER_PMINTERFACE(LayerNameTextValidation, kLayerNameTextValidationImpl)
REGISTER_PMINTERFACE(LayersPanelSAXHandler, kLayersPanelSAXHandlerImpl)
REGISTER_PMINTERFACE(LayersPanelXMLGenerator, kLayersPanelXMLGeneratorImpl)
REGISTER_PMINTERFACE(PageItemDupDeleteDEHandler, kPageItemDupDeleteDEHandlerImpl)
REGISTER_PMINTERFACE(LayersTreeViewTypeAhead, kLayersTreeViewTypeAheadImpl)
