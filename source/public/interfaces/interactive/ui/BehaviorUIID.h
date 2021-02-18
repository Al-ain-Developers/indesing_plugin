//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/BehaviorUIID.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __BehaviorUIID_h__
#define __BehaviorUIID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormFieldUIID.h"

#define kBehaviorUIPrefix	 		RezLong(0x15900)

// ----- Plug-in ID -----

#define kBehaviorUIPluginName 			"BehaviorsUI"

#define kBehaviorUIPluginID				kFormFieldUIPluginID
//DECLARE_PMID(kPlugInIDSpace,			kBehaviorUIPluginID,				kBehaviorUIPrefix + 1)

// ----- Class IDs -----

DECLARE_PMID(kClassIDSpace,				kBehaviorsWidgetBoss,				kBehaviorUIPrefix + 5)

DECLARE_PMID(kClassIDSpace,				kEventNodeWidgetBoss,				kBehaviorUIPrefix + 10)
DECLARE_PMID(kClassIDSpace,				kBehaviorNodeWidgetBoss,			kBehaviorUIPrefix + 11)
DECLARE_PMID(kClassIDSpace,				kBehaviorOnOffButtonBoss,			kBehaviorUIPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kEditBehaviorsDialogBoss,			kBehaviorUIPrefix + 14)
DECLARE_PMID(kClassIDSpace,				kChooseBehaviorDialogBoss,			kBehaviorUIPrefix + 15)
DECLARE_PMID(kClassIDSpace,				kAddBehaviorButtonWidgetBoss,		kBehaviorUIPrefix + 16)
DECLARE_PMID(kClassIDSpace,				kBehaviorsListWidgetBoss,			kBehaviorUIPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kHolderPanelWidgetBoss,				kBehaviorUIPrefix + 18)
DECLARE_PMID(kClassIDSpace,				kMovieDataPanelBoss,				kBehaviorUIPrefix + 19)
DECLARE_PMID(kClassIDSpace,				kShowHideFieldsDataPanelBoss,		kBehaviorUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,				kShowHideAllNoneButtonWidgetBoss,	kBehaviorUIPrefix + 21)
DECLARE_PMID(kClassIDSpace,				kFieldsListBoxBoss,					kBehaviorUIPrefix + 22)
DECLARE_PMID(kClassIDSpace,				kGoToPositionPanelBoss,				kBehaviorUIPrefix + 23)
DECLARE_PMID(kClassIDSpace,				kEventChoicesWidgetBoss,			kBehaviorUIPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kBehaviorChoicesWidgetBoss,			kBehaviorUIPrefix + 25)
DECLARE_PMID(kClassIDSpace,				kMovieOpChoicesWidgetBoss,			kBehaviorUIPrefix + 26)
DECLARE_PMID(kClassIDSpace,				kMovieChoicesWidgetBoss,			kBehaviorUIPrefix + 27)
DECLARE_PMID(kClassIDSpace,				kSimpleEditBehaviorsDialogBoss,		kBehaviorUIPrefix + 28)
DECLARE_PMID(kClassIDSpace,				kDocumentJavaScriptDialogBoss,		kBehaviorUIPrefix + 29)

DECLARE_PMID(kClassIDSpace,				kSoundDataPanelBoss,				kBehaviorUIPrefix + 30)
DECLARE_PMID(kClassIDSpace,				kSoundOpChoicesWidgetBoss,			kBehaviorUIPrefix + 31)
DECLARE_PMID(kClassIDSpace,				kSoundChoicesWidgetBoss,			kBehaviorUIPrefix + 32)

DECLARE_PMID(kClassIDSpace,				kGoToFirstPageDataPanelBoss,		kBehaviorUIPrefix + 34)
DECLARE_PMID(kClassIDSpace,				kGoToLastPageDataPanelBoss,			kBehaviorUIPrefix + 35)
DECLARE_PMID(kClassIDSpace,				kGoToNextPageDataPanelBoss,			kBehaviorUIPrefix + 36)
DECLARE_PMID(kClassIDSpace,				kGoToPreviousPageDataPanelBoss,		kBehaviorUIPrefix + 37)
DECLARE_PMID(kClassIDSpace,				kZoomChoicesWidgetBoss,				kBehaviorUIPrefix + 38)
DECLARE_PMID(kClassIDSpace,				kGoToURLDataPanelBoss,				kBehaviorUIPrefix + 39)

DECLARE_PMID(kClassIDSpace,				kFieldsWidgetBoss,					kBehaviorUIPrefix + 40)
DECLARE_PMID(kClassIDSpace,				kFieldsNodeWidgetBoss,				kBehaviorUIPrefix + 41)
DECLARE_PMID(kClassIDSpace,				kGoToPageDataPanelBoss,		kBehaviorUIPrefix + 42)

DECLARE_PMID(kClassIDSpace,				kImportDataDataPanelBoss,			kBehaviorUIPrefix + 50)
DECLARE_PMID(kClassIDSpace,				kSelectFileButtonBoss,				kBehaviorUIPrefix + 51)

DECLARE_PMID(kClassIDSpace,				kResetFormDataPanelBoss,			kBehaviorUIPrefix + 60)
DECLARE_PMID(kClassIDSpace,				kFieldSelectionWidgetBoss,			kBehaviorUIPrefix + 61)
DECLARE_PMID(kClassIDSpace,				kFieldSelectionNodeWidgetBoss,		kBehaviorUIPrefix + 62)
DECLARE_PMID(kClassIDSpace,				kFieldSelectionButtonWidgetBoss,	kBehaviorUIPrefix + 63)

DECLARE_PMID(kClassIDSpace,				kAnimationDataPanelBoss,			kBehaviorUIPrefix + 64)
DECLARE_PMID(kClassIDSpace,				kAnimationOpChoicesWidgetBoss,		kBehaviorUIPrefix + 65)
DECLARE_PMID(kClassIDSpace,				kAnimationChoicesWidgetBoss,		kBehaviorUIPrefix + 66)
DECLARE_PMID(kClassIDSpace,				kSwitchToMSOStateDataPanelBoss,		kBehaviorUIPrefix + 67)
DECLARE_PMID(kClassIDSpace,				kMSOTargetChoicesWidgetBoss,		kBehaviorUIPrefix + 68)
DECLARE_PMID(kClassIDSpace,				kMSOStateChoicesWidgetBoss,			kBehaviorUIPrefix + 69)

DECLARE_PMID(kClassIDSpace,				kSubmitFormDataPanelBoss,			kBehaviorUIPrefix + 70)
DECLARE_PMID(kClassIDSpace,				kSwitchToNextMSOStateDataPanelBoss,	kBehaviorUIPrefix + 71)
DECLARE_PMID(kClassIDSpace,				kSwitchToPrevMSOStateDataPanelBoss,	kBehaviorUIPrefix + 72)

DECLARE_PMID(kClassIDSpace,				kOpenFileDataPanelBoss,				kBehaviorUIPrefix + 80)
DECLARE_PMID(kClassIDSpace,				kMovieNavPointChoicesWidgetBoss,	kBehaviorUIPrefix + 81)

//gap

DECLARE_PMID(kClassIDSpace,				kJavaScriptDataPanelBoss,			kBehaviorUIPrefix + 110)

DECLARE_PMID(kClassIDSpace,				kFormatNumberDataPanelBoss,			kBehaviorUIPrefix + 120)
DECLARE_PMID(kClassIDSpace,				kFormatPercentDataPanelBoss,		kBehaviorUIPrefix + 121)
DECLARE_PMID(kClassIDSpace,				kFormatDateDataPanelBoss,			kBehaviorUIPrefix + 122)
DECLARE_PMID(kClassIDSpace,				kFormatTimeDataPanelBoss,			kBehaviorUIPrefix + 123)
DECLARE_PMID(kClassIDSpace,				kFormatSpecialDataPanelBoss,		kBehaviorUIPrefix + 124)

DECLARE_PMID(kClassIDSpace,				kFormulaDataPanelBoss,				kBehaviorUIPrefix + 140)

DECLARE_PMID(kClassIDSpace,				kMarkReadOnlyDataPanelBoss,			kBehaviorUIPrefix + 150)

DECLARE_PMID(kClassIDSpace,				kValidateRangeDataPanelBoss,		kBehaviorUIPrefix + 160)

DECLARE_PMID(kClassIDSpace, 			kStandardActionMenusBoss,			kBehaviorUIPrefix + 200)
DECLARE_PMID(kClassIDSpace,				kStrIntPairDropDownWidgetBoss,		kBehaviorUIPrefix + 201)
DECLARE_PMID(kClassIDSpace,				kStrStrPairDropDownWidgetBoss,		kBehaviorUIPrefix + 202)
DECLARE_PMID(kClassIDSpace,				kBehaviorDragDropDEHandlerBoss,		kBehaviorUIPrefix + 203)

DECLARE_PMID(kClassIDSpace,				kGoToAnchorDataPanelBoss,			kBehaviorUIPrefix + 205)
DECLARE_PMID(kClassIDSpace,				kAnchorDocumentDDLObserverBoss,		kBehaviorUIPrefix + 206)
DECLARE_PMID(kClassIDSpace,				kAnchorTypeDDLObserverBoss,			kBehaviorUIPrefix + 207)
DECLARE_PMID(kClassIDSpace,				kOpenAnchorDocObserverBoss,			kBehaviorUIPrefix + 208)

DECLARE_PMID(kClassIDSpace,				kGoToNextViewDataPanelBoss,			kBehaviorUIPrefix + 209)
DECLARE_PMID(kClassIDSpace,				kGoToPreviousViewDataPanelBoss,		kBehaviorUIPrefix + 210)
DECLARE_PMID(kClassIDSpace,				kBehaviorEnableWidgetBoss,			kBehaviorUIPrefix + 211)

DECLARE_PMID(kClassIDSpace,				kViewZoomDataPanelBoss,				kBehaviorUIPrefix + 212)
DECLARE_PMID(kClassIDSpace,				kViewZoomChoicesWidgetBoss,			kBehaviorUIPrefix + 213)

DECLARE_PMID(kClassIDSpace,				kEventDragDropDEHandlerBoss,		kBehaviorUIPrefix + 214)
DECLARE_PMID(kClassIDSpace,				kNamedBehaviorListBoxBoss,			kBehaviorUIPrefix + 215)

DECLARE_PMID(kClassIDSpace,				kBehaviorsDialogBoss,				kBehaviorUIPrefix + 216)
DECLARE_PMID(kClassIDSpace,				kAddBehaviorButtonBoss,				kBehaviorUIPrefix + 217)
DECLARE_PMID(kClassIDSpace,				kDeleteBehaviorButtonBoss,			kBehaviorUIPrefix + 218)

DECLARE_PMID(kClassIDSpace,				kOpenFileBrowseObserverBoss,		kBehaviorUIPrefix + 220)
DECLARE_PMID(kClassIDSpace,				kFormFieldChoicesWidgetBoss,		kBehaviorUIPrefix + 221)

// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace,			IID_IBEHAVIORDATAPANEL, 			kBehaviorUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IACTIONMENUSERVICE,				kBehaviorUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IACTIONMENUMANAGER,				kBehaviorUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IBEHAVIORDRAGDROPDATA,			kBehaviorUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IANCHORFILEDATA,				kBehaviorUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IANCHORTYPEDATA,				kBehaviorUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IEVENTBEHAVIORDATA,				kBehaviorUIPrefix + 7)

// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace,	kBehaviorsTreeViewAdapterImpl, 		kBehaviorUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsTreeViewMgrImpl,			kBehaviorUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsListObserverImpl,			kBehaviorUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorOnOffButtonViewImpl,		kBehaviorUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kEditBehaviorDlgControllerImpl,		kBehaviorUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kChooseBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kAddUpdateBehaviorButtonObserverImpl,	kBehaviorUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsListAdapterImpl,			kBehaviorUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsListMgrImpl,				kBehaviorUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsTreeObserverImpl,			kBehaviorUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kHolderPanelControlDataImpl,		kBehaviorUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kHolderObserverImpl,				kBehaviorUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kSimpleEditBehaviorDlgControllerImpl, kBehaviorUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,	kDocumentJavaScriptDlgControllerImpl, kBehaviorUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,	kNamedBehaviorListControlDataImpl, 	kBehaviorUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace,	kNamedBehaviorListObserverImpl, 	kBehaviorUIPrefix + 20)

DECLARE_PMID(kImplementationIDSpace,	kStrIntPairDDLControlDataImpl, 		kBehaviorUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,	kUIDData2Impl, 						kBehaviorUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,	kEditBehaviorDlgObserverImpl,		kBehaviorUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,	kStrStrPairDDLControlDataImpl, 		kBehaviorUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorTreeNodeEHImpl, 			kBehaviorUIPrefix + 25)

DECLARE_PMID(kImplementationIDSpace,	kMovieBehaviorDataPanelImpl,		kBehaviorUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,	kMovieDDLControlDataImpl, 			kBehaviorUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace,	kMovieBehaviorDlgControllerImpl, 	kBehaviorUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kMovieNavPointDDLControlDataImpl, 	kBehaviorUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kSoundBehaviorDataPanelImpl,		kBehaviorUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kSoundDDLControlDataImpl, 			kBehaviorUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kSoundBehaviorDlgControllerImpl, 	kBehaviorUIPrefix + 32)

DECLARE_PMID(kImplementationIDSpace,	kAnimationBehaviorDataPanelImpl,	kBehaviorUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kAnimationBehaviorPanelObserverImpl, kBehaviorUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kAnimationDDLControlDataImpl,		kBehaviorUIPrefix + 35)

DECLARE_PMID(kImplementationIDSpace,	kSwitchToMSOStateDataPanelImpl,			kBehaviorUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace,	kSwitchToMSOStatePanelObserverImpl,		kBehaviorUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,	kMSOTargetDDLControlDataImpl,			kBehaviorUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace,	kMSOStateDDLControlDataImpl,			kBehaviorUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,	kSwitchToNextMSOStateDataPanelImpl,		kBehaviorUIPrefix + 40)

DECLARE_PMID(kImplementationIDSpace,	kGoToFirstPageDataPanelImpl,		kBehaviorUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kGoToLastPageDataPanelImpl,			kBehaviorUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kGoToNextPageDataPanelImpl,			kBehaviorUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace,	kGoToPreviousPageDataPanelImpl,		kBehaviorUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace,	kGoToFirstPageDlgControllerImpl,	kBehaviorUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kGoToURLBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kGoToURLBehaviorDataPanelImpl,		kBehaviorUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kGoToPageDataPanelImpl,				kBehaviorUIPrefix + 48)

DECLARE_PMID(kImplementationIDSpace,	kShowHideFieldsDataPanelImpl, 		kBehaviorUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kShowHideFieldsDlgControllerImpl,	kBehaviorUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace,	kFieldsTreeViewAdapterImpl,			kBehaviorUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,	kFieldsTreeViewMgrImpl,				kBehaviorUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kFieldsNodeObserverImpl,			kBehaviorUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kShowHideFieldsButtonObserverImpl,	kBehaviorUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace,	kShowHideFieldsPanelObserverImpl,	kBehaviorUIPrefix + 56)

DECLARE_PMID(kImplementationIDSpace,	kSwitchToNextMSOStatePanelObserverImpl, kBehaviorUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace,	kSwitchToPrevMSOStateDataPanelImpl,		kBehaviorUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kSwitchToPrevMSOStatePanelObserverImpl, kBehaviorUIPrefix + 59)

DECLARE_PMID(kImplementationIDSpace,	kImportDataBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,	kImportDataBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace,	kSelectFileObserverImpl,				kBehaviorUIPrefix + 62)

DECLARE_PMID(kImplementationIDSpace,	kResetFormBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace,	kResetFormBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace,	kFieldSelectionTreeViewAdapterImpl,		kBehaviorUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace,	kFieldSelectionTreeViewMgrImpl,			kBehaviorUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace,	kFieldSelectionNodeObserverImpl,		kBehaviorUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace,	kFieldSelectionButtonObserverImpl,		kBehaviorUIPrefix + 75)

DECLARE_PMID(kImplementationIDSpace,	kSubmitFormBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace,	kSubmitFormBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 81)

DECLARE_PMID(kImplementationIDSpace,	kOpenFileBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace,	kOpenFileBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 91)

//gap

DECLARE_PMID(kImplementationIDSpace,	kJavaScriptBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace,	kJavaScriptBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 121)
DECLARE_PMID(kImplementationIDSpace,	kJavaScriptBehaviorDlgObserverImpl,	kBehaviorUIPrefix + 122)

DECLARE_PMID(kImplementationIDSpace,	kFormatNumberBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace,	kFormatNumberBehaviorDlgControllerImpl, kBehaviorUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace,	kFormatPercentBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace,	kFormatPercentBehaviorDlgControllerImpl,kBehaviorUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace,	kFormatDateBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace,	kFormatDateBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace,	kFormatTimeBehaviorDataPanelImpl, 		kBehaviorUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace,	kFormatTimeBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 137)
DECLARE_PMID(kImplementationIDSpace,	kFormatSpecialBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 138)
DECLARE_PMID(kImplementationIDSpace,	kFormatSpecialBehaviorDlgControllerImpl,kBehaviorUIPrefix + 139)

DECLARE_PMID(kImplementationIDSpace,	kFormulaBehaviorDataPanelImpl, 			kBehaviorUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace,	kFormulaBehaviorDlgControllerImpl,		kBehaviorUIPrefix + 141)

DECLARE_PMID(kImplementationIDSpace,	kMarkReadOnlyBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 150)
DECLARE_PMID(kImplementationIDSpace,	kMarkReadOnlyBehaviorDlgControllerImpl,	kBehaviorUIPrefix + 151)

DECLARE_PMID(kImplementationIDSpace,	kValidateRangeBehaviorDataPanelImpl, 	kBehaviorUIPrefix + 160)
DECLARE_PMID(kImplementationIDSpace,	kValidateRangeBehaviorDlgControllerImpl,kBehaviorUIPrefix + 161)

DECLARE_PMID(kImplementationIDSpace,	kActionMenuManagerImpl,					kBehaviorUIPrefix + 200)
DECLARE_PMID(kImplementationIDSpace,	kActionMenuProviderImpl, 				kBehaviorUIPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, 	kStandardActionMenusImpl, 				kBehaviorUIPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, 	kBehaviorTreeViewItemDDSourceImpl, 		kBehaviorUIPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, 	kBehaviorDragDropDEHandlerImpl, 		kBehaviorUIPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, 	kBehaviorDragDropDataImpl, 				kBehaviorUIPrefix + 206)

DECLARE_PMID(kImplementationIDSpace, 	kGoToAnchorDlgControllerImpl,			kBehaviorUIPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, 	kGoToAnchorDataPanelImpl,				kBehaviorUIPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, 	kAnchorDocumentDDLObserverImpl,			kBehaviorUIPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, 	kAnchorTypeDDLObserverImpl,				kBehaviorUIPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, 	kAnchorFileListDataImpl,				kBehaviorUIPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, 	kAnchorTypeListDataImpl,				kBehaviorUIPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, 	kOpenAnchorDocObserverImpl,				kBehaviorUIPrefix + 213)

DECLARE_PMID(kImplementationIDSpace,	kGoToNextViewDataPanelImpl,				kBehaviorUIPrefix + 214)
DECLARE_PMID(kImplementationIDSpace,	kGoToPreviousViewDataPanelImpl,			kBehaviorUIPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, 	kBehaviorEnableObserverImpl,			kBehaviorUIPrefix + 216)

DECLARE_PMID(kImplementationIDSpace,	kViewZoomBehaviorDlgControllerImpl,		kBehaviorUIPrefix + 217)
DECLARE_PMID(kImplementationIDSpace,	kViewZoomBehaviorDataPanelImpl,			kBehaviorUIPrefix + 218)

DECLARE_PMID(kImplementationIDSpace,	kBehaviorsTreeViewDDTargetImpl,			kBehaviorUIPrefix + 219)
DECLARE_PMID(kImplementationIDSpace,	kEventDragDropDEHandlerImpl,			kBehaviorUIPrefix + 220)
DECLARE_PMID(kImplementationIDSpace,	kEventTreeViewItemDDSourceImpl,			kBehaviorUIPrefix + 221)
DECLARE_PMID(kImplementationIDSpace,	kNamedBehaviorListBoxEHImpl, 			kBehaviorUIPrefix + 223)

DECLARE_PMID(kImplementationIDSpace,	kBehaviorsDialogControllerImpl,			kBehaviorUIPrefix + 227)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsPanelCreatorImpl,				kBehaviorUIPrefix + 228)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorsDialogObserverImpl,			kBehaviorUIPrefix + 229)
DECLARE_PMID(kImplementationIDSpace,	kDeleteBehaviorButtonObserverImpl,		kBehaviorUIPrefix + 230)
DECLARE_PMID(kImplementationIDSpace,	kBehaviorOnOffButtonEventHandlerImpl,	kBehaviorUIPrefix + 231)
// gap
DECLARE_PMID(kImplementationIDSpace,	kEventBehaviorDataImpl,					kBehaviorUIPrefix + 233)
DECLARE_PMID(kImplementationIDSpace,	kMoveBehaviorDataImpl,					kBehaviorUIPrefix + 234)

DECLARE_PMID(kImplementationIDSpace,	kOpenFileBrowseObserverImpl,			kBehaviorUIPrefix + 235)

DECLARE_PMID(kImplementationIDSpace, 	kGoToAnchorPanelObserverImpl,			kBehaviorUIPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, 	kGoToFirstPagePanelObserverImpl,		kBehaviorUIPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, 	kGoToURLPanelObserverImpl,				kBehaviorUIPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, 	kMovieBehaviorPanelObserverImpl,		kBehaviorUIPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, 	kSoundBehaviorPanelObserverImpl,		kBehaviorUIPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, 	kOpenFileBehaviorPanelObserverImpl,		kBehaviorUIPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, 	kViewZoomPanelObserverImpl,				kBehaviorUIPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, 	kGoToPagePanelObserverImpl,				kBehaviorUIPrefix + 243)

DECLARE_PMID(kImplementationIDSpace, 	kSubmitFormBehaviorPanelObserverImpl,	kBehaviorUIPrefix + 244)

// ----- Widget IDs -----

DECLARE_PMID(kWidgetIDSpace,			kBehaviorsPanelWidgetID, 			kBehaviorUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorPanelControlStripWidgetID, kBehaviorUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,			kNewBehaviorButtonWidgetID, 		kBehaviorUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,			kDeleteBehaviorButtonWidgetID, 		kBehaviorUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorsTreeWidgetID, 			kBehaviorUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorsTreeBorderWidgetID, 		kBehaviorUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,			kEventNodeWidgetId, 				kBehaviorUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorNodeWidgetId, 				kBehaviorUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,			kEventTitleWidgetId, 				kBehaviorUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorTitleWidgetId, 			kBehaviorUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorOnOffButtonWidgetID, 		kBehaviorUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorIconWidgetID, 				kBehaviorUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,			kEditBehaviorsDialogWidgetID, 		kBehaviorUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorOptionsGroupWidgetId, 		kBehaviorUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorOptionsGroupTitleWidgetID, kBehaviorUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorsListWidgetID, 			kBehaviorUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,			kEventChoicesWidgetID, 				kBehaviorUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorChoicesWidgetID, 			kBehaviorUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,			kChooseBehaviorDialogWidgetID, 		kBehaviorUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorDescriptionWidgetId, 		kBehaviorUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,			kAddBehaviorButtonWidgetID, 		kBehaviorUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorDescriptionGroupWidgetId, 	kBehaviorUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorDescriptionTitleWidgetId, 	kBehaviorUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorListNodeWidgetId, 			kBehaviorUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorsListBorderWidgetId, 		kBehaviorUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorsDataHolderWidgetID, 		kBehaviorUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorNodeID, 					kBehaviorUIPrefix + 28)


DECLARE_PMID(kWidgetIDSpace,			kGoToFirstPagePanelWidgetID, 		kBehaviorUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace,			kGoToLastPagePanelWidgetID, 		kBehaviorUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace,			kGoToNextPagePanelWidgetID, 		kBehaviorUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace,			kGoToPreviousPagePanelWidgetID, 	kBehaviorUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace,			kZoomLabelWidgetID, 				kBehaviorUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace,			kZoomWidgetID, 						kBehaviorUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace,			kGoToURLPanelWidgetID, 				kBehaviorUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace,			kURLLabelWidgetID, 					kBehaviorUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace,			kGoToURLWidgetID, 					kBehaviorUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace,			kGoToPagePanelWidgetID,				kBehaviorUIPrefix + 39)

DECLARE_PMID(kWidgetIDSpace,			kMoviePanelWidgetID, 				kBehaviorUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace,			kMovieLabelWidgetID, 				kBehaviorUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace,			kMovieWidgetID, 					kBehaviorUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace,			kOperationLabelWidgetID, 			kBehaviorUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace,			kOperationWidgetID, 				kBehaviorUIPrefix + 44)

DECLARE_PMID(kWidgetIDSpace,			kSoundPanelWidgetID, 				kBehaviorUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace,			kSoundLabelWidgetID, 				kBehaviorUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace,			kSoundWidgetID, 					kBehaviorUIPrefix + 47)

DECLARE_PMID(kWidgetIDSpace,			kAnimationPanelWidgetID, 			kBehaviorUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace,			kAnimationLabelWidgetID, 			kBehaviorUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace,			kAnimationWidgetID, 				kBehaviorUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace,			kAnimationOperationLabelWidgetID, 	kBehaviorUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace,			kAnimationOperationWidgetID, 		kBehaviorUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace,			kAnimationAutoReverseWidgetID,		kBehaviorUIPrefix + 53)

DECLARE_PMID(kWidgetIDSpace,			kSwitchToMSOStatePanelWidgetID, 	kBehaviorUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace,			kMSOTargetLabelWidgetID, 			kBehaviorUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace,			kMSOTargetChoiceWidgetID, 			kBehaviorUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace,			kMSOStateLabelWidgetID, 			kBehaviorUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace,			kMSOStateChoiceWidgetID, 			kBehaviorUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace,			kMSOAutoReverseWidgetID,			kBehaviorUIPrefix + 59)

DECLARE_PMID(kWidgetIDSpace,			kSwitchToNextMSOStatePanelWidgetID, kBehaviorUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace,			kNextMSOTargetLabelWidgetID, 		kBehaviorUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace,			kNextMSOTargetChoiceWidgetID, 		kBehaviorUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace,			kSwitchToPrevMSOStatePanelWidgetID, kBehaviorUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace,			kPrevMSOTargetLabelWidgetID, 		kBehaviorUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace,			kPrevMSOTargetChoiceWidgetID, 		kBehaviorUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace,			kLoopAtBeginningOrEndWidgetID,		kBehaviorUIPrefix + 66)

DECLARE_PMID(kWidgetIDSpace,			kShowHideFieldsPanelWidgetID, 		kBehaviorUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace,			kSHFieldsWidgetID, 					kBehaviorUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace,			kSHFieldsBorderWidgetID, 			kBehaviorUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace,			kSHFieldsNodeWidgetId, 				kBehaviorUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace,			kSHFieldTitleWidgetId, 				kBehaviorUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace,			kSHShowAllButtonWidgetID, 			kBehaviorUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace,			kSHHideAllButtonWidgetID, 			kBehaviorUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace,			kSHClearAllButtonWidgetID, 			kBehaviorUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace,			kSHShowOnOffButtonWidgetID, 		kBehaviorUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace,			kSHVisibilityLabelWidgetID, 		kBehaviorUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace,			kMovieNavPointWidgetID, 			kBehaviorUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace,			kNavPointLabelWidgetID, 			kBehaviorUIPrefix + 92)

DECLARE_PMID(kWidgetIDSpace,			kImportDataPanelWidgetID, 			kBehaviorUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace,			kSelectFileLabelWidgetID, 			kBehaviorUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace,			kSelectFileWidgetID, 				kBehaviorUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace,			kSelectFileIconWidgetID, 			kBehaviorUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace,			kJavaScriptEditLabelWidgetID, 		kBehaviorUIPrefix + 104)
//DECLARE_PMID(kWidgetIDSpace,			kJavaScriptEditScrollWidgetID, 		kBehaviorUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace,			kJavaScriptEditWidgetID, 			kBehaviorUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace,			kLinkToFileWidgetID, 				kBehaviorUIPrefix + 107)

DECLARE_PMID(kWidgetIDSpace,			kResetFormPanelWidgetID, 			kBehaviorUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace,			kSelectAllButtonWidgetID, 			kBehaviorUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace,			kDeselectAllButtonWidgetID, 		kBehaviorUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace,			kSelectedOnOffButtonWidgetID, 		kBehaviorUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace,			kFieldSelectionNodeWidgetId, 		kBehaviorUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace,			kFieldSelectionBorderWidgetID, 		kBehaviorUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace,			kFieldSelectionWidgetID, 			kBehaviorUIPrefix + 116)

DECLARE_PMID(kWidgetIDSpace,			kSubmitFormPanelWidgetID, 			kBehaviorUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace,			kExportFormatGroupWidgetId, 		kBehaviorUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace,			kExportFormatGroupTitleWidgetID, 	kBehaviorUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace,			kFieldSelectionGroupWidgetId, 		kBehaviorUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace,			kFieldSelectionGroupTitleWidgetID, 	kBehaviorUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace,			kFieldDataWidgetID, 				kBehaviorUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace,			kIncludeCommentsWidgetID, 			kBehaviorUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace,			kIncrementalChangesWidgetID, 		kBehaviorUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace,			kConvertDatesWidgetID, 				kBehaviorUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace,			kIncludeEmptyFieldsWidgetID, 		kBehaviorUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace,			kFormatChoicesWidgetID, 			kBehaviorUIPrefix + 130)

DECLARE_PMID(kWidgetIDSpace,			kOpenFilePanelWidgetID, 			kBehaviorUIPrefix + 132)
//gap

DECLARE_PMID(kWidgetIDSpace,			kJavaScriptPanelWidgetID, 			kBehaviorUIPrefix + 138)

DECLARE_PMID(kWidgetIDSpace,			kFormatNumberPanelWidgetID, 		kBehaviorUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace,			kDecimalPlacesLabelWidgetID, 		kBehaviorUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace,			kDecimalPlacesWidgetID, 			kBehaviorUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace,			kDecimalStyleLabelWidgetID, 		kBehaviorUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace,			kDecimalStyleWidgetID, 				kBehaviorUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace,			kNegativeStyleLabelWidgetID, 		kBehaviorUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace,			kNegativeStyleWidgetID, 			kBehaviorUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace,			kCurrencySymbolLabelWidgetID, 		kBehaviorUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace,			kCurrencySymbolWidgetID, 			kBehaviorUIPrefix + 188)

DECLARE_PMID(kWidgetIDSpace,			kFormatPercentPanelWidgetID, 		kBehaviorUIPrefix + 190)

DECLARE_PMID(kWidgetIDSpace,			kFormatDatePanelWidgetID, 			kBehaviorUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace,			kDateFormatStringLabelWidgetID, 	kBehaviorUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace,			kDateFormatStringWidgetID, 			kBehaviorUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace,			kDateStyleLabelWidgetID, 			kBehaviorUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace,			kDateStyleWidgetID, 				kBehaviorUIPrefix + 199)

DECLARE_PMID(kWidgetIDSpace,			kFormatTimePanelWidgetID, 			kBehaviorUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace,			kTimeStyleLabelWidgetID, 			kBehaviorUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace,			kTimeStyleWidgetID, 				kBehaviorUIPrefix + 202)

DECLARE_PMID(kWidgetIDSpace,			kFormatSpecialPanelWidgetID, 		kBehaviorUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace,			kSpecialStyleLabelWidgetID, 		kBehaviorUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace,			kSpecialStyleWidgetID, 				kBehaviorUIPrefix + 207)

DECLARE_PMID(kWidgetIDSpace,			kFormulaPanelWidgetID, 				kBehaviorUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace,			kFormulaLabel1WidgetID, 			kBehaviorUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace,			kFormulaLabel2WidgetID, 			kBehaviorUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace,			kFormulaChoicesWidgetID, 			kBehaviorUIPrefix + 213)

DECLARE_PMID(kWidgetIDSpace,			kMarkReadOnlyPanelWidgetID, 		kBehaviorUIPrefix + 220)

DECLARE_PMID(kWidgetIDSpace,			kValidateRangePanelWidgetID, 		kBehaviorUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace,			kValidateRangeLabel1WidgetID, 		kBehaviorUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace,			kRangeMinLabelWidgetID, 			kBehaviorUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace,			kRangeMinWidgetID, 					kBehaviorUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace,			kRangeMaxLabelWidgetID, 			kBehaviorUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace,			kRangeMaxWidgetID, 					kBehaviorUIPrefix + 229)

DECLARE_PMID(kWidgetIDSpace,			kGoToAnchorPanelWidgetID, 			kBehaviorUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace,			kAnchorLabelWidgetID, 				kBehaviorUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace,			kAnchorWidgetID, 					kBehaviorUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace,			kAnchorDocumentChoicesWidgetID, 	kBehaviorUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace,			kAnchorChoicesWidgetID, 			kBehaviorUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace,			kAnchorTypeWidgetID, 				kBehaviorUIPrefix + 235)

DECLARE_PMID(kWidgetIDSpace,			kGoToNextViewPanelWidgetID, 		kBehaviorUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace,			kGoToPreviousViewPanelWidgetID, 	kBehaviorUIPrefix + 238)

DECLARE_PMID(kWidgetIDSpace,			kViewZoomPanelWidgetID, 			kBehaviorUIPrefix + 240)

DECLARE_PMID(kWidgetIDSpace,			kViewZoomWidgetID, 					kBehaviorUIPrefix + 242)
DECLARE_PMID(kWidgetIDSpace,			kSimpleEditBehaviorsDialogWidgetID,	kBehaviorUIPrefix + 243)

DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxPanelWID,			kBehaviorUIPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxItemStaticWID,		kBehaviorUIPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxItemEditWID,		kBehaviorUIPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxListWidgetID,		kBehaviorUIPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxAddWidgetID,		kBehaviorUIPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, 			kBehaviorListBoxDeleteWidgetID,		kBehaviorUIPrefix + 249)
DECLARE_PMID(kWidgetIDSpace,			kBehaviorListBoxChangeWidgetID,		kBehaviorUIPrefix + 250)
DECLARE_PMID(kWidgetIDSpace,			kDocumentJavaScriptDialogWID,		kBehaviorUIPrefix + 251)

DECLARE_PMID(kWidgetIDSpace,			kBehaviorsDialogWidgetID,			kBehaviorUIPrefix + 252)
DECLARE_PMID(kWidgetIDSpace,			kGoToPageWidgetID,					kBehaviorUIPrefix + 254)
DECLARE_PMID(kWidgetIDSpace,			kPageCountWidgetID,					kBehaviorUIPrefix + 255)

// ----- Action IDs -----

// ----- Service IDs -----

DECLARE_PMID(kServiceIDSpace,			kActionMenuService,					kBehaviorUIPrefix + 1)

// ----- Message IDs -----

DECLARE_PMID(kMessageIDSpace,			kBehaviorListBoxDoubleClick, 		kBehaviorUIPrefix + 1)

// ----- Error IDs -----

DECLARE_PMID(kErrorIDSpace,				kInvalidURLField, 					kGoToURLWidgetID)

#endif // __BehaviorUIID_h__
