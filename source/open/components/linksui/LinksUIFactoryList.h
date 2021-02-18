//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIFactoryList.h $
//  
//  Owner: lance bushore
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

REGISTER_PMINTERFACE(LinksUIPanelTreeViewAdapter, kLinksUIPanelTreeViewAdapterImpl)
REGISTER_PMINTERFACE(LinksUIPanelTreeViewWidgetMgr, kLinksUIPanelTreeViewWidgetMgrImpl)
REGISTER_PMINTERFACE(LinksUIPanelTreeObserver, kLinksUIPanelTreeObserverImpl)
REGISTER_PMINTERFACE(LinksUITreeViewController, kLinksUITreeViewControllerImpl)
REGISTER_PMINTERFACE(LinksUIPanelPrefs, kLinksUIPanelPrefsImpl)
REGISTER_PMINTERFACE(LinkThumbnailView, kLinkThumbnailViewImpl)
REGISTER_PMINTERFACE(LinkInfoPanelObserver, kLinkInfoPanelObserverImpl)
REGISTER_PMINTERFACE(LinksUIPanelMenuComponent, kLinksUIPanelMenuComponentImpl)
REGISTER_PMINTERFACE(ChooseLinksColumnsDialogController, kChooseLinksColumnsDialogControllerImpl)
REGISTER_PMINTERFACE(ToggleLinkInfoButtonObserver, kToggleLinkInfoButtonObserverImpl)
REGISTER_PMINTERFACE(LinkUIStaticTextView, kLinkUIStaticTextViewImpl)
REGISTER_PMINTERFACE(EditOriginalWithMenu, kEditOriginalWithMenuImpl)
REGISTER_PMINTERFACE(EditOriginalWithMenuComponent, kEditOriginalWithMenuComponentImpl)
REGISTER_PMINTERFACE(EditOriginalSelectionWithMenu, kEditOriginalSelectionWithMenuImpl)
REGISTER_PMINTERFACE(FilesChanging, kFilesChangingImpl)
REGISTER_PMINTERFACE(EditOriginalResumeObserver, kEditOriginalResumeObserverImpl)
REGISTER_PMINTERFACE(EditOriginalSelectionWithMenuComponent, kEditOriginalSelectionWithMenuComponentImpl)
REGISTER_PMINTERFACE(LinksUIPanelSelectionObserver, kLinksUIPanelSelectionObserverImpl)
REGISTER_PMINTERFACE(LinksUIUtilsImpl, kLinksUIUtilsImpl)
REGISTER_PMINTERFACE(LinksUIPanelView, kLinksUIPanelViewImpl)
REGISTER_PMINTERFACE(LinksUIButtonObserver, kLinksUIButtonObserverImpl)
REGISTER_PMINTERFACE(OpenProblemLinksDialogCmd, kOpenProblemLinksDialogCmdImpl)
REGISTER_PMINTERFACE(ProblemLinksDialogController, kProblemLinksDialogControllerImpl)
REGISTER_PMINTERFACE(ProblemLinksDialogObserver, kProblemLinksDialogObserverImpl)
REGISTER_PMINTERFACE(LinksUIColumnHeaderObserver,kLinksUIColumnHeaderObserverImpl)
REGISTER_PMINTERFACE(LinkInfoIconView, kLinkInfoIconViewImpl)
REGISTER_PMINTERFACE(LinksTreeNodeList, kLinksTreeNodeListImpl)
REGISTER_PMINTERFACE(LinksUITreeRowPanelEH, kLinksUITreeRowPanelEHImpl)
REGISTER_PMINTERFACE(LinksUIPanelSAXHandler, kLinksUIPanelSAXHandlerImpl)
REGISTER_PMINTERFACE(LinksUIPanelXMLGenerator, kLinksUIPanelXMLGeneratorImpl)
REGISTER_PMINTERFACE(LinksUITreePanelControlData, kLinksUITreePanelControlDataImpl)
REGISTER_PMINTERFACE(LinkUILinkNameTip, kLinkUILinkNameTipImpl)
REGISTER_PMINTERFACE(LinksUIStatusTextTip, kLinksUIStatusTextTipImpl )
REGISTER_PMINTERFACE(LinkInfoIconTip, kLinkInfoIconTipImpl )
REGISTER_PMINTERFACE(LinkInfoPanelPanorama, kLinkInfoPanelPanoramaImpl)
REGISTER_PMINTERFACE(LinkInfoPanelView, kLinkInfoPanelViewImpl)
REGISTER_PMINTERFACE(NextPrevLinkButtonObserver, kNextPrevLinkButtonObserverImpl)
REGISTER_PMINTERFACE(LinkInfoPanelEH, kLinkInfoPanelEHImpl)
REGISTER_PMINTERFACE(LinksUIStatusTextObserver, kLinksUIStatusTextObserverImpl)
REGISTER_PMINTERFACE(LinkInfoIconEH, kLinkInfoIconEHImpl)
REGISTER_PMINTERFACE(LinkInfoTextLabelEH, kLinkInfoTextLabelEHImpl)
REGISTER_PMINTERFACE( LinksUIButtonTips, kLinksUIButtonTipsImpl )
REGISTER_PMINTERFACE(LinksUIRowElementCursorProvider, kLinksUIRowElementCursorProviderImpl)
REGISTER_PMINTERFACE(GenerateLinkCaptionDialogController, kGenerateLinkCaptionDialogControllerImpl)
REGISTER_PMINTERFACE(LinkCaptionActionComponent, kLinkCaptionActionComponentImpl)
REGISTER_PMINTERFACE(AddDeleteCaptionRowButtonObserver, kAddDeleteCaptionRowButtonObserverImpl)
REGISTER_PMINTERFACE(CaptionParaStyleObserver, kCaptionParaStyleObserverImpl)
REGISTER_PMINTERFACE(CaptionLayerObserver, kCaptionLayerObserverImpl)
REGISTER_PMINTERFACE(LinksTreeViewTypeAhead, kLinksTreeViewTypeAheadImpl)
REGISTER_PMINTERFACE(MetadataLabelEVEInfo, kMetadataLabelEVEInfoImpl)
REGISTER_PMINTERFACE(LinksUIPanelViewObserver, kLinksUIPanelViewObserverImpl)

#ifdef DEBUG
REGISTER_PMINTERFACE(LinksUITestMenu, kLinksUITestMenuImpl)
REGISTER_PMINTERFACE(LinkInfoDebugUIDsProvider, kLinkInfoDebugUIDsProviderImpl)
#endif

REGISTER_PMINTERFACE(LinksUILinkNamePanelView, kLinksUILinkNamePanelViewImpl)
REGISTER_PMINTERFACE(ClosingDocumentsResponder, kClosingDocumentsResponderImpl)
REGISTER_PMINTERFACE(ClosingDocumentsServiceProvider, kClosingDocumentsServiceProviderImpl)
