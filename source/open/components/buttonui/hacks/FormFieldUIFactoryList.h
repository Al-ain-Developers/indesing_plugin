//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/hacks/FormFieldUIFactoryList.h $
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
//  Adapted from GroupFactoryList.h
//  
//========================================================================================

	REGISTER_PMINTERFACE(FormFieldUIComponent, kFormFieldUIComponentImpl)
	
	REGISTER_PMINTERFACE(GenericFieldUIFactory, kGenericFieldUIFactoryImpl)
	REGISTER_PMINTERFACE(PushButtonUIFactory, kPushButtonUIFactoryImpl)

	REGISTER_PMINTERFACE(TextAttributesTargetServer, kTextAttributesTargetServerImpl)

	REGISTER_PMINTERFACE(TextFieldUIObserver, kTextFieldUIObserverImpl)
	REGISTER_PMINTERFACE(ListBoxUIObserver, kListBoxUIObserverImpl)
	REGISTER_PMINTERFACE(ToggleStatesButtonObserver, kToggleStatesButtonObserverImpl)

	REGISTER_PMINTERFACE(AppearancePanelObserver, kAppearancePanelObserverImpl)
	REGISTER_PMINTERFACE(StateListBoxController, kStateListBoxControllerImpl)
	REGISTER_PMINTERFACE(StateListBoxObserver, kStateListBoxObserverImpl)
	REGISTER_PMINTERFACE(DeleteStateButtonObserver, kDeleteStateButtonObserverImpl)
	REGISTER_PMINTERFACE(ConvertToButtonObserver, kConvertToButtonObserverImpl)
	REGISTER_PMINTERFACE(ConvertToObjectObserver, kConvertToObjectObserverImpl)
	REGISTER_PMINTERFACE(AppearancePanelMenuComponent, kAppearancePanelMenuComponentImpl)
	REGISTER_PMINTERFACE(AppearancePanelDetailController, kAppearancePanelDetailControllerImpl)
	REGISTER_PMINTERFACE(AppearancePanelPrefsDialogController, kAppearancePanelPrefsDialogControllerImpl)
	REGISTER_PMINTERFACE(DeleteBehaviorButtonObserver, kDeleteBehaviorButtonObserverImpl)

	REGISTER_PMINTERFACE(AppearancePanelEyeballObserver, kAppearancePanelEyeballObserverImpl)
	REGISTER_PMINTERFACE(StateThumbnailView, kStateThumbnailViewImpl)

	REGISTER_PMINTERFACE(ProxyViewDragDropSource, kAPProxyViewDragDropSourceImpl)
	REGISTER_PMINTERFACE(StateProxyDEHandler, kStateProxyDEHandlerImpl)
	REGISTER_PMINTERFACE(StateDuplicateDragDropTarget, kStateDuplicateDragDropTargetImpl)
	REGISTER_PMINTERFACE(StateDeleteDragDropTarget, kStateDeleteDragDropTargetImpl)
	REGISTER_PMINTERFACE(StateEyeDragDropSource, kStateEyeDragDropSourceImpl)
	REGISTER_PMINTERFACE(StateEyeDragDropTarget, kStateEyeDragDropTargetImpl)
	REGISTER_PMINTERFACE(StateEyeDEHandler, kStateEyeDEHandlerImpl)
	REGISTER_PMINTERFACE(StateEyeDragDropSourceEH, kStateEyeDragDropSourceEHImpl)
	REGISTER_PMINTERFACE(AppearancePalettePanel, kAppearancePalettePanelImpl )

	REGISTER_PMINTERFACE(ListBoxListZOrderDDSource, kListBoxListZOrderDDSourceImpl)	
	REGISTER_PMINTERFACE(ListBoxDEHandler, kListBoxDEHandlerImpl)

	REGISTER_PMINTERFACE(TabOrderDialogController, kTabOrderDialogControllerImpl)

	REGISTER_PMINTERFACE(OrderListObserver, kOrderListObserverImpl)
	REGISTER_PMINTERFACE(OrderListControlData, kOrderListControlDataImpl)
	REGISTER_PMINTERFACE(ListBoxListZOrderDDTarget, kOrderListBoxListZOrderDDTargetImpl)
	REGISTER_PMINTERFACE(AppearancePlaceBehaviorUI, kAppearancePlaceBehaviorUIImpl);
	REGISTER_PMINTERFACE(FormFieldLabelDrawer, kFormFieldLabelDrawerImpl);
	
	// Moved from Behaviors UI project
	REGISTER_PMINTERFACE(StandardActionMenus, kStandardActionMenusImpl)
	REGISTER_PMINTERFACE(ActionMenuManager, kActionMenuManagerImpl)
	REGISTER_PMINTERFACE(ActionMenuProvider, kActionMenuProviderImpl)
	REGISTER_PMINTERFACE(BehaviorTreeViewItemDDSource, kBehaviorTreeViewItemDDSourceImpl)
	REGISTER_PMINTERFACE(BehaviorDragDropDEHandler, kBehaviorDragDropDEHandlerImpl)
	REGISTER_PMINTERFACE(BehaviorDragDropData, kBehaviorDragDropDataImpl)
	REGISTER_PMINTERFACE(BehaviorEnableObserver, kBehaviorEnableObserverImpl)
	REGISTER_PMINTERFACE(BehaviorOnOffButtonEventHandler, kBehaviorOnOffButtonEventHandlerImpl)
	REGISTER_PMINTERFACE(EventBehaviorData, kEventBehaviorDataImpl)
	REGISTER_PMINTERFACE(MoveBehaviorData, kMoveBehaviorDataImpl)
	REGISTER_PMINTERFACE(BehaviorTreeNodeEH, kBehaviorTreeNodeEHImpl)
	REGISTER_PMINTERFACE(BehaviorsTreeViewMgr, kBehaviorsTreeViewMgrImpl)
	REGISTER_PMINTERFACE(BehaviorsTreeViewAdapter, kBehaviorsTreeViewAdapterImpl)
	REGISTER_PMINTERFACE(BehaviorsTreeObserver, kBehaviorsTreeObserverImpl)
	REGISTER_PMINTERFACE(BehaviorOnOffButtonView, kBehaviorOnOffButtonViewImpl)
	REGISTER_PMINTERFACE(HolderObserver, kHolderObserverImpl)
	REGISTER_PMINTERFACE(HolderPanelControlData, kHolderPanelControlDataImpl)
	REGISTER_PMINTERFACE(BehaviorsTreeViewDDTarget, kBehaviorsTreeViewDDTargetImpl)

	REGISTER_PMINTERFACE(DropDownListControlDataOf<ContainerData>, kStrIntPairDDLControlDataImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<StrStrContainerData>, kStrStrPairDDLControlDataImpl)

	REGISTER_PMINTERFACE(ViewZoomPanelObserver, kViewZoomPanelObserverImpl)
	REGISTER_PMINTERFACE(ViewZoomBehaviorDataPanel, kViewZoomBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(SoundBehaviorPanelObserver, kSoundBehaviorPanelObserverImpl)
	REGISTER_PMINTERFACE(SoundBehaviorDataPanel, kSoundBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<SoundListElement>, kSoundDDLControlDataImpl)
	REGISTER_PMINTERFACE(ShowHideFieldsDataPanel, kShowHideFieldsDataPanelImpl)
	REGISTER_PMINTERFACE(ShowHideFieldsPanelObserver, kShowHideFieldsPanelObserverImpl)
	REGISTER_PMINTERFACE(ShowHideFieldsButtonObserver, kShowHideFieldsButtonObserverImpl)
	REGISTER_PMINTERFACE(FieldsTreeViewAdapter, kFieldsTreeViewAdapterImpl)
	REGISTER_PMINTERFACE(FieldsTreeViewMgr, kFieldsTreeViewMgrImpl)
	REGISTER_PMINTERFACE(FieldsNodeObserver, kFieldsNodeObserverImpl)
	REGISTER_PMINTERFACE(OpenFileBhvrPanelObserver, kOpenFileBehaviorPanelObserverImpl)
	REGISTER_PMINTERFACE(OpenFileBehaviorDataPanel, kOpenFileBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(OpenFileBrowseObserver, kOpenFileBrowseObserverImpl)
	REGISTER_PMINTERFACE(GoToURLPanelObserver, kGoToURLPanelObserverImpl)
	REGISTER_PMINTERFACE(GoToURLComboBoxObserver, kGoToURLComboBoxObserverImpl)
	REGISTER_PMINTERFACE(GoToURLBehaviorDataPanel, kGoToURLBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(GoToFirstPageDataPanel, kGoToFirstPageDataPanelImpl)
	REGISTER_PMINTERFACE(GoToFirstPagePanelObserver, kGoToFirstPagePanelObserverImpl)
	REGISTER_PMINTERFACE(GoToPageDataPanel, kGoToPageDataPanelImpl)
	REGISTER_PMINTERFACE(GoToPagePanelObserver, kGoToPagePanelObserverImpl)
	REGISTER_PMINTERFACE(GoToLastPageDataPanel, kGoToLastPageDataPanelImpl)
	REGISTER_PMINTERFACE(GoToNextPageDataPanel, kGoToNextPageDataPanelImpl)
	REGISTER_PMINTERFACE(GoToPreviousPageDataPanel, kGoToPreviousPageDataPanelImpl)
	REGISTER_PMINTERFACE(GoToNextViewDataPanel, kGoToNextViewDataPanelImpl)
	REGISTER_PMINTERFACE(GoToPreviousViewDataPanel, kGoToPreviousViewDataPanelImpl)
	REGISTER_PMINTERFACE(GoToAnchorPanelObserver, kGoToAnchorPanelObserverImpl)
	REGISTER_PMINTERFACE(GoToAnchorDataPanel, kGoToAnchorDataPanelImpl)
	REGISTER_PMINTERFACE(GoToAnchorDocumentObserver, kAnchorDocumentDDLObserverImpl)
	REGISTER_PMINTERFACE(GoToAnchorTypeObserver, kAnchorTypeDDLObserverImpl)
	REGISTER_PMINTERFACE(OpenAnchorDocObserver, kOpenAnchorDocObserverImpl)
	REGISTER_PMINTERFACE(AnchorFileListData, kAnchorFileListDataImpl)
	REGISTER_PMINTERFACE(AnchorTypeListData, kAnchorTypeListDataImpl)
	REGISTER_PMINTERFACE(MovieBehaviorPanelObserver, kMovieBehaviorPanelObserverImpl)
	REGISTER_PMINTERFACE(MovieBehaviorDataPanel, kMovieBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<MovieListElement>, kMovieDDLControlDataImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<MovieNavPointListElement>, kMovieNavPointDDLControlDataImpl)

	REGISTER_PMINTERFACE(MSOPanelView, kMSOPanelViewImpl)
	REGISTER_PMINTERFACE(MSOPanelMenuAction, kMSOPanelMenuActionImpl)
	REGISTER_PMINTERFACE(MSOPanelObserver, kMSOPanelObserverImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewObserver, kMSOPanelTreeViewObserverImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewAdapter, kMSOPanelTreeViewAdapterImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewWidgetMgr, kMSOPanelTreeViewWidgetMgrImpl)
	REGISTER_PMINTERFACE(MSOPanelStateThumbnailView, kMSOPanelStateThumbnailViewImpl)
	REGISTER_PMINTERFACE(MSOPanelStateNameILEObserver, kMSOPanelStateNameILEObserverImpl)
	REGISTER_PMINTERFACE(MSOPanelStateNameILEEditingAttributes, kMSOPanelStateNameILEEditingAttributesImpl)
	REGISTER_PMINTERFACE(MSOPanelStateNameTextValidation, kMSOPanelStateNameTextValidationImpl)
	REGISTER_PMINTERFACE(NewMSOStateButtonObserver, kNewMSOStateButtonObserverImpl)
	REGISTER_PMINTERFACE(DeleteMSOStateButtonObserver, kDeleteMSOStateButtonObserverImpl)
	REGISTER_PMINTERFACE(MSOPanelDetailController, kMSOPanelDetailControllerImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewController, kMSOPanelTreeViewControllerImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewEH, kMSOPanelTreeViewEHImpl)
	REGISTER_PMINTERFACE(MSOPanelTips, kMSOPanelTipsImpl)
	REGISTER_PMINTERFACE(MSOPanelStateDNDHandler, kMSOPanelStateDNDHandlerImpl)
	REGISTER_PMINTERFACE(MSOPanelStateDNDSource, kMSOPanelStateDNDSourceImpl)
	REGISTER_PMINTERFACE(DeleteMSOStateButtonDNDTarget, kDeleteMSOStateButtonDNDTargetImpl)
	REGISTER_PMINTERFACE(NewMSOStateButtonDNDTarget, kNewMSOStateButtonDNDTargetImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewDNDTarget, kMSOPanelTreeViewDNDTargetImpl)
	REGISTER_PMINTERFACE(MSOPanelTreeViewNodeEH, kMSOPanelTreeViewNodeEHImpl)
	REGISTER_PMINTERFACE(MSOPanelPointyHandCursorProvider, kMSOPanelPointyHandCursorProviderImpl)
	REGISTER_PMINTERFACE(MSOSelectionIconEH, kMSOSelectionIconEHImpl)
	REGISTER_PMINTERFACE(PasteIntoMSOStateButtonObserver, kPasteIntoMSOStateButtonObserverImpl)
	REGISTER_PMINTERFACE(AddToMSOStateButtonObserver, kAddToMSOStateButtonObserverImpl)

	REGISTER_PMINTERFACE(AnimationBehaviorDataPanel, kAnimationBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(AnimationBehaviorPanelObserver, kAnimationBehaviorPanelObserverImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<AnimationTargetReference>, kAnimationDDLControlDataImpl)

	REGISTER_PMINTERFACE(MSOBehaviorDataPanel<kSwitchToMSOStatePanelRsrcID>, kSwitchToMSOStateDataPanelImpl)
	REGISTER_PMINTERFACE(MSOBehaviorDataPanel<kSwitchToNextMSOStatePanelRsrcID>, kSwitchToNextMSOStateDataPanelImpl)
	REGISTER_PMINTERFACE(MSOBehaviorDataPanel<kSwitchToPrevMSOStatePanelRsrcID>, kSwitchToPrevMSOStateDataPanelImpl)
	REGISTER_PMINTERFACE(SwitchToMSOStatePanelObserver, kSwitchToMSOStatePanelObserverImpl)
	REGISTER_PMINTERFACE(SwitchToNextOrPrevMSOStatePanelObserver<kNextMSOTargetChoiceWidgetID>, kSwitchToNextMSOStatePanelObserverImpl)
	REGISTER_PMINTERFACE(SwitchToNextOrPrevMSOStatePanelObserver<kPrevMSOTargetChoiceWidgetID>, kSwitchToPrevMSOStatePanelObserverImpl)
	REGISTER_PMINTERFACE(DropDownListControlDataOf<MSOTargetReference>, kMSOTargetDDLControlDataImpl);

	REGISTER_PMINTERFACE(BhvrTargetChoicesTips, kBhvrTargetChoicesTipsImpl)
	REGISTER_PMINTERFACE(MSOStateDDLElementView, kMSOStateDDLElementViewImpl)
	REGISTER_PMINTERFACE(MSOStateOwnerDrawDDItem, kMSOStateOwnerDrawDDItemImpl)
	REGISTER_PMINTERFACE(BehaviorsTreeViewEH, kBehaviorsTreeViewEHImpl)

	REGISTER_PMINTERFACE(SubmitFormBehaviorDataPanel, kSubmitFormBehaviorDataPanelImpl)
	REGISTER_PMINTERFACE(SubmitFormBhvrPanelObserver, kSubmitFormBehaviorPanelObserverImpl)
	REGISTER_PMINTERFACE(PDFOptionsDetailController, kPDFOptionsDetailControllerImpl)
	REGISTER_PMINTERFACE(ListItemsTreeViewAdapter, kListItemsTreeViewAdapterImpl)
	REGISTER_PMINTERFACE(ListItemsTreeViewMgr, kListItemsTreeViewMgrImpl)
	REGISTER_PMINTERFACE(RemoveListOptionButtonObserver, kRemoveListOptionButtonObserverImpl)
	REGISTER_PMINTERFACE(ListItemsTreeObserver, kListItemsTreeObserverImpl)	
	REGISTER_PMINTERFACE(AddListOptionButtonObserver, kAddListOptionButtonObserverImpl)
	REGISTER_PMINTERFACE(ListItemsTreeEH, kListItemsTreeEHImpl)
	REGISTER_PMINTERFACE(ListItemsDDSource, kListItemsDDSourceImpl)
	REGISTER_PMINTERFACE(ListItemsTreeViewDDTarget, kListItemsTreeViewDDTargetImpl)
	REGISTER_PMINTERFACE(ListItemsDDHandler, kListItemsDDHandlerImpl)
	REGISTER_PMINTERFACE(FontSizeTextValidation, kFontSizeTextValidationImpl)
	REGISTER_PMINTERFACE(FontSizeTextValue, kFontSizeTextValueImpl)
	REGISTER_PMINTERFACE(ListItemsNodeEventHandler, kListItemsNodeEventHandlerImpl)
	REGISTER_PMINTERFACE(ListItemsEditBoxEH, kListItemsEditBoxEHImpl)
		REGISTER_PMINTERFACE(FormsFontComboBoxView, kFormsFontComboboxViewImpl)
		REGISTER_PMINTERFACE(FormsFontObserver, kFormsFontObserverImpl)

