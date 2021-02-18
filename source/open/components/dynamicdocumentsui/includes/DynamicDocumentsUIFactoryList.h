//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/includes/DynamicDocumentsUIFactoryList.h $
//  
//  Owner: DBerggren
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

REGISTER_PMINTERFACE(PageTransitionsMenuComponent,			kPageTransitionsMenuComponentImpl)
REGISTER_PMINTERFACE(PageTransitionsPanelObserver,			kPageTransitionsPanelObserverImpl)
REGISTER_PMINTERFACE(PageTransitionsDialogController,		kPageTransitionsDialogControllerImpl)
REGISTER_PMINTERFACE(PageTransitionsDialogObserver,			kPageTransitionsDialogObserverImpl)
REGISTER_PMINTERFACE(PageTransitionStaticTextToolTips,		kPageTransitionStaticTextToolTipsImpl)

REGISTER_PMINTERFACE(LiquidLayoutPanelObserver,				kLiquidLayoutPanelObserverImpl)
REGISTER_PMINTERFACE(LiquidLayoutPanelMenuComponent,		kLiquidLayoutPanelMenuComponentImpl)
REGISTER_PMINTERFACE(LayoutAdjustmentWarningObserver,		kLayoutAdjustmentWarningObserverImpl)

REGISTER_PMINTERFACE(TimingPanelView,						kTimingPanelViewImpl)
REGISTER_PMINTERFACE(TimingPanelTreeViewWidgetMgr,			kTimingPanelTreeViewWidgetMgrImpl)
REGISTER_PMINTERFACE(TimingPanelTreeViewAdapter,			kTimingPanelTreeViewAdapterImpl)
REGISTER_PMINTERFACE(TimingPanelMenuComponent,				kTimingPanelMenuComponentImpl)
REGISTER_PMINTERFACE(TimingPanelObserver,					kTimingPanelObserverImpl)
REGISTER_PMINTERFACE(TimingPanelGroupButtonDDTarget,		kTimingPanelGroupButtonDDTargetImpl)
REGISTER_PMINTERFACE(TimingPanelUngroupButtonDDTarget,		kTimingPanelUngroupButtonDDTargetImpl)
REGISTER_PMINTERFACE(TimingPanelDataExchangeHandler,		kTimingPanelDataExchangeHandlerImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeDDSource,			kTimingPanelTreeNodeDDSourceImpl)
REGISTER_PMINTERFACE(TimingPanelTreeDDTarget,				kTimingPanelTreeDDTargetImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeView,				kTimingPanelTreeNodeViewImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeGroupWidgetView,	kTimingPanelTreeNodeGroupWidgetViewImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeEH,					kTimingPanelTreeNodeEHImpl)
REGISTER_PMINTERFACE(TimingPanelEventDDListTips,			kTimingPanelEventDDListTipsImpl)
REGISTER_PMINTERFACE(DynamicTargetListData,					kDynamicTargetListDataImpl) 
REGISTER_PMINTERFACE(TimingPanelPageItemNameObserver,		kTimingPanelPageItemNameObserverImpl)
REGISTER_PMINTERFACE(TimingPanelNameILEEditingAttributes,	kTimingPanelNameILEEditingAttributesImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeGroupWidgetEH,		kTimingPanelTreeNodeGroupWidgetEHImpl)
REGISTER_PMINTERFACE(TimingPanelCursorProvider,				kTimingPanelCursorProviderImpl)
REGISTER_PMINTERFACE(TimingPanelTreeNodeGroupWidgetTip,		kTimingPanelTreeNodeGroupWidgetTipImpl)

REGISTER_PMINTERFACE(AnimationUIEventMenuAction,			kAnimationUIEventMenuActionImpl)
REGISTER_PMINTERFACE(AnimationUIPanelMenuAction,			kAnimationUIPanelMenuActionImpl)
REGISTER_PMINTERFACE(AnimationUIPanelView,					kAnimationUIPanelViewImpl)
REGISTER_PMINTERFACE(AnimationPanelObserver,				kAnimationPanelObserverImpl)
REGISTER_PMINTERFACE(AnimationUISavePresetDialogController, kAnimationUISavePresetDialogControllerImpl)
REGISTER_PMINTERFACE(AnimationUIEventInfoTip,				kAnimationUIEventInfoTipImpl)
REGISTER_PMINTERFACE(AnimationUIAnimateOptionTip,			kAnimationUIAnimateOptionTipImpl)
REGISTER_PMINTERFACE(AnimationUIButtonTriggerEH,			kAnimationUIButtonTriggerEHImpl)
REGISTER_PMINTERFACE(AnimationUIButtonTriggerTrackerRegister, kAnimationUIButtonTriggerTrackerRegisterImpl)
REGISTER_PMINTERFACE(AnimationUIButtonTriggerTracker,		kAnimationUIButtonTriggerTrackerImpl)
REGISTER_PMINTERFACE(AnimationUIButtonTriggerTrackerEH,		kAnimationUIButtonTriggerTrackerEHImpl) 
REGISTER_PMINTERFACE(AnimationAdornmentDrawer,				kAnimationAdornmentDrawerImpl)
REGISTER_PMINTERFACE(AnimationUIXFProxyEH,					kAnimationUIXFProxyEHImpl)

REGISTER_PMINTERFACE(AnimationUIPanelDetailController,			kAnimationUIPanelDetailControllerImpl)
REGISTER_PMINTERFACE(AnimationUIManagePresetsDialogObserver,	kAnimationUIManagePresetsDialogObserverImpl)
REGISTER_PMINTERFACE(AnimationUIManagePresetItemListBoxCtrl,	kAnimationUIManagePresetItemListBoxCtrlImpl)
REGISTER_PMINTERFACE(AnimationUIManagePresetsDialogListNodeView,kAnimationUIManagePresetsDialogListNodeViewImpl)
REGISTER_PMINTERFACE(AnimationUIManagePresetsDialogStaticTextWidgetView, kAnimationUIManagePresetsDialogStaticTextWidgetViewImpl)
REGISTER_PMINTERFACE(AnimationUIManagePresetListBoxWidgetMgr,	kAnimationUIManagePresetListBoxWidgetMgrImpl)

REGISTER_PMINTERFACE(DDPreviewSpreadButtonWidgetTip, kDDPreviewSpreadButtonWidgetTipImpl)
REGISTER_PMINTERFACE(MotionPathAdornmentTip,				kMotionPathAdornmentTipImpl)
REGISTER_PMINTERFACE(EasingPathAdornmentTip,				kEasingPathAdornmentTipImpl)

REGISTER_PMINTERFACE(AnimationUIPresetPopupMenuAction,	kAnimationUIPresetPopupMenuActionImpl)
REGISTER_PMINTERFACE(AnimationUIPresetPopupDynamicMenu,	kAnimationUIPresetPopupDynamicMenuImpl)

#ifdef DEBUG
REGISTER_PMINTERFACE(MotionTestMenu, kMotionTestMenuImpl)
#endif

REGISTER_PMINTERFACE(HTMLFXLPreviewPanelMenuComponent, kHTMLFXLPreviewPanelMenuComponentImpl)
