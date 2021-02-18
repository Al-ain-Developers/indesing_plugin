//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/AssignmentUIID.h $
//  
//  Owner: Jon Pugh
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

#ifndef __ASSIGNMENTUIID__
#define __ASSIGNMENTUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// double check with AdobePrefix.h
#define kAssignmentUIPrefix			RezLong(0x19A00)  

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kStoryListPanelPluginName	"AssignmentUI"
DECLARE_PMID(kPlugInIDSpace, kStoryListPanelPluginID, kAssignmentUIPrefix + 1)

#define kStoryListNodeIDClass	 kAssignmentUIPrefix + 1

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,		kStoryListPanelMenuBoss,					kAssignmentUIPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kStoryListKitBoss,							kAssignmentUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kStoryListTreeViewBoss,						kAssignmentUIPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kStoryListDDListBoss,						kAssignmentUIPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kStoryTreeNodeWidgetBoss,					kAssignmentUIPrefix + 5)
DECLARE_PMID(kClassIDSpace,		kDocTreeNodeWidgetBoss,						kAssignmentUIPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kSLBridgeChangeResponderBoss,				kAssignmentUIPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kSLUpdateDesignButtonBoss,					kAssignmentUIPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kSLUpdateStoryButtonBoss,					kAssignmentUIPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kSLEditStoryButtonBoss,						kAssignmentUIPrefix + 10)
DECLARE_PMID(kClassIDSpace,		kStaticTextWithAmpersandsBoss,				kAssignmentUIPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kStoryListTVNodeWidgetBoss,					kAssignmentUIPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kAssignmentOptionsDialogBoss,				kAssignmentUIPrefix + 13)
DECLARE_PMID(kClassIDSpace,		kAssignmentOptionsDialogCmdBoss,			kAssignmentUIPrefix + 14)
DECLARE_PMID(kClassIDSpace,		kStoryListDNDHandlerBoss,					kAssignmentUIPrefix + 15)
DECLARE_PMID(kClassIDSpace,		kSLNewButtonBoss,							kAssignmentUIPrefix + 17)
DECLARE_PMID(kClassIDSpace,		kSLDeleteButtonBoss,						kAssignmentUIPrefix + 18)
DECLARE_PMID(kClassIDSpace,		kAssignmentFrameAdornmentBoss,				kAssignmentUIPrefix + 19)
DECLARE_PMID(kClassIDSpace,		kAssNewPageItemResponderBoss,				kAssignmentUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,		kStoryListLayoutActionBoss,					kAssignmentUIPrefix + 21)
//gap
DECLARE_PMID(kClassIDSpace,     kAddToAssignmentMenuBoss,					kAssignmentUIPrefix + 23)
DECLARE_PMID(kClassIDSpace,     kAddSelToAssignmentMenuBoss,				kAssignmentUIPrefix + 24)
DECLARE_PMID(kClassIDSpace,     kAddLayerToAssignmentMenuBoss,				kAssignmentUIPrefix + 25)
DECLARE_PMID(kClassIDSpace,     kAddAllStoriesToAssignmentMenuBoss,			kAssignmentUIPrefix + 26)
DECLARE_PMID(kClassIDSpace,     kAddAllGraphicsToAssignmentMenuBoss,		kAssignmentUIPrefix + 27)
DECLARE_PMID(kClassIDSpace,     kAddSelToAssignmentTextContextMenuBoss,		kAssignmentUIPrefix + 28)
DECLARE_PMID(kClassIDSpace,     kAddSelToAssignmentLayoutContextMenuBoss,	kAssignmentUIPrefix + 29)
DECLARE_PMID(kClassIDSpace,     kAddToAssignmentRtMenuBoss,					kAssignmentUIPrefix + 30)
DECLARE_PMID(kClassIDSpace,		kStoryNameILEBoss,							kAssignmentUIPrefix + 31)
DECLARE_PMID(kClassIDSpace,		kStoryNameILEStaticTextWithAmpersandsBoss,	kAssignmentUIPrefix + 32)
DECLARE_PMID(kClassIDSpace,		kAssignmentUITestMenuBoss,					kAssignmentUIPrefix + 33)
DECLARE_PMID(kClassIDSpace,		kStoryNameILEEditChildEBWidgetBoss,			kAssignmentUIPrefix + 34)
DECLARE_PMID(kClassIDSpace,		kAssignmentPackageAlertDialogBoss,			kAssignmentUIPrefix + 35)
DECLARE_PMID(kClassIDSpace,		kSLNewButtonDNDCmdBoss,						kAssignmentUIPrefix + 36)
DECLARE_PMID(kClassIDSpace,		kStoryListTVUnassignedNodeWidgetBoss,		kAssignmentUIPrefix + 37)
DECLARE_PMID(kClassIDSpace,		kStoryListDNDCmdBoss,						kAssignmentUIPrefix + 38)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYLISTSELECTIONOBSERVER,			kAssignmentUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTUISELECTIONSUITE,			kAssignmentUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTUIUTILS,						kAssignmentUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYLISTDNDDATA,						kAssignmentUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYLISTLAYOUTOBSERVER,				kAssignmentUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTOPTIONSDIALOGDATA,			kAssignmentUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,	IID_ISTORYLISTPANELPRIVATEUTILS,			kAssignmentUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPRIVATENOMISSINGASSIGNMENT,			kAssignmentUIPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTPACKAGEUIFACADE,				kAssignmentUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNMENTPACKAGEALERTUTILS,			kAssignmentUIPrefix + 11)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kStoryListPanelMenuActionImpl,			kAssignmentUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kStoryListTreeViewWidgetMgrImpl,		kAssignmentUIPrefix + 2)	// not used in Firedrake, 
DECLARE_PMID(kImplementationIDSpace, kStoryListPanelTreeViewAdapterImpl,	kAssignmentUIPrefix + 3)	// not used in Firedrake
DECLARE_PMID(kImplementationIDSpace, kStoryListPanelObserverImpl,			kAssignmentUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kStoryListTreeObserverImpl,			kAssignmentUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kStoryListTreeNodeEHImpl,				kAssignmentUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVControllerImpl,			kAssignmentUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kStoryListSelectionObserverImpl,		kAssignmentUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSLTreeNodeControlViewImpl,			kAssignmentUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSLDocTreeNodeControlViewImpl,			kAssignmentUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSLBridgeChangeResponderImpl,			kAssignmentUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSLUpdateDesignObserverImpl,			kAssignmentUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSLUpdateStoryObserverImpl,			kAssignmentUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSLEditStoryObserverImpl,				kAssignmentUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSLEditStoryTipImpl,					kAssignmentUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kStoryListPanelViewImpl,				kAssignmentUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kStoryListTreeTipImpl,					kAssignmentUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kStaticTextWithAmpersandsViewImpl,		kAssignmentUIPrefix + 18)

DECLARE_PMID(kImplementationIDSpace, kStoryListTVAdapterImpl,				kAssignmentUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVWidgetMgrImpl,				kAssignmentUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVNodeTipImpl,				kAssignmentUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVSelObserverImpl,			kAssignmentUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVObserverImpl,				kAssignmentUIPrefix + 23)

DECLARE_PMID(kImplementationIDSpace, kAssignmentOptionsDialogControllerImpl,kAssignmentUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kAssignmentOptionsDialogCreatorImpl,	kAssignmentUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kAssignmentOptionsDialogObserverImpl,	kAssignmentUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAssignmentOptionsDialogCmdImpl,		kAssignmentUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kStoryListPanelUtilsImpl,				kAssignmentUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kStoryListDNDSourceImpl,				kAssignmentUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kStoryListDNDTargetImpl,				kAssignmentUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kStoryListDNDHandlerImpl,				kAssignmentUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kStoryListDNDDataImpl,					kAssignmentUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageUIFacadeImpl,		kAssignmentUIPrefix + 34)

DECLARE_PMID(kImplementationIDSpace, kSLNewObserverImpl,					kAssignmentUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kSLNewButtonTipImpl,					kAssignmentUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSLDeleteObserverImpl,					kAssignmentUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSLDeleteButtonTipImpl,				kAssignmentUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAssignmentFrameAdornmentImpl,			kAssignmentUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kAssNewPageItemResponderImpl,			kAssignmentUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kStoryListLayoutObserverImpl,			kAssignmentUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kStoryListLayoutActionImpl,			kAssignmentUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSLDeleteButtonDNDTargetImpl,			kAssignmentUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kStoryListTVNodeEHImpl,				kAssignmentUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kAssignmentOptionsDialogDataImpl,		kAssignmentUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSLPSelectionSuiteASBImpl,				kAssignmentUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSLPSelectionSuiteCSBImpl,				kAssignmentUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kAddToAssignmentMenuComponentImpl,		kAssignmentUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentMenuComponentImpl,	kAssignmentUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAddLayerToAssignmentMenuComponentImpl,	kAssignmentUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAddAllStoriesToAssignmentMenuComponentImpl,	kAssignmentUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAddAllGraphicsToAssignmentMenuComponentImpl,	kAssignmentUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAddToAssignmentDynMenuImpl,			kAssignmentUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentDynMenuImpl,		kAssignmentUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kAddLayerToAssignmentDynMenuImpl,		kAssignmentUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAddAllStoriesToAssignmentDynMenuImpl,	kAssignmentUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kAddAllGraphicsToAssignmentDynMenuImpl,kAssignmentUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kStoryListPanelPrivateUtilsImpl,		 kAssignmentUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentTextContextDynMenuImpl,	kAssignmentUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentLayoutContextDynMenuImpl,	kAssignmentUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentTextContextMenuComponentImpl,	kAssignmentUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kAddSelToAssignmentLayoutContextMenuComponentImpl,	kAssignmentUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kAddToAssignmentRtMenuComponentImpl,	kAssignmentUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kAddToAssignmentRtDynMenuImpl,			kAssignmentUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPrivateNoMissingAssignmentImpl,		kAssignmentUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kSLNewButtonDNDTargetImpl,				kAssignmentUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kStoryNameILEObserverImpl,				kAssignmentUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kStoryNameILEEditingAttributesImpl,	kAssignmentUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kStoryNameILEWidgetAttributesImpl,		kAssignmentUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kAssignmentUITestMenuImpl,				kAssignmentUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kStoryNameILEChildEBTextControlDataImpl,kAssignmentUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageAlertUtilsImpl,		kAssignmentUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageAlertDlgObserverImpl,kAssignmentUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kSLNewButtonDNDCmdImpl,				kAssignmentUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kStoryListDNDCmdImpl,					kAssignmentUIPrefix + 77)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kWidgetIDSpace, kStoryListPanelWidgetID,						kAssignmentUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kStoryListKitPanelViewWidgetID,				kAssignmentUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kStoryListKitDockBarViewWidgetID,				kAssignmentUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kStoryListPanelCtrlSetWidgetID,				kAssignmentUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kStoryListDockBarCtrlSetWidgetID,				kAssignmentUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kStoryListTreeViewWidgetID,					kAssignmentUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kStoryListTreeViewBorderWidgetID,				kAssignmentUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kStoryListDDListWidgetID,						kAssignmentUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kStoryNodeWidgetId,							kAssignmentUIPrefix + 9) //not used in Firedrake
DECLARE_PMID(kWidgetIDSpace, kStoryNodeNameWidgetID,						kAssignmentUIPrefix + 10)//not used in Firedrake
DECLARE_PMID(kWidgetIDSpace, kUserIDTextWidgetID,							kAssignmentUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kUserNameTextWidgetID,							kAssignmentUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSLControlStripWidgetID,						kAssignmentUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kIconBridgeStateWidgetId,						kAssignmentUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kIconStatusWidgetId,							kAssignmentUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kUpdateDesignButtonWidgetID,					kAssignmentUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kUpdateStoryButtonWidgetID,					kAssignmentUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kEditStoryButtonWidgetID,						kAssignmentUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kStoryListTVNodeWidgetID,						kAssignmentUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kStoryListNodeNameWidgetID,					kAssignmentUIPrefix + 21)

//assignment options dialog
DECLARE_PMID(kWidgetIDSpace, kAssignmentOptionsDlgWidgetID,					kAssignmentUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kAssignmentOptionsGroupWidgetID,				kAssignmentUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kAssignmentOptionsLabelWidgetID,				kAssignmentUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kAssignmentNameLabelWidgetID,					kAssignmentUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kAssignmentNameEditTextWidgetID,				kAssignmentUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kAssignmentColorLabelWidgetID,					kAssignmentUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kAssignmentColorDropDownWidgetID,				kAssignmentUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kAssignedToLabelWidgetID,						kAssignmentUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kAssignedToEditTextWidgetID,					kAssignmentUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kAssignmentExportOptionsLabelWidgetID,			kAssignmentUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kAssignmentExportOptionsClusterWidgetID,		kAssignmentUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kAssignmentExportFramesRadioBoxWidgetID,		kAssignmentUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kAssignmentExportSpreadsRadioBoxWidgetID,		kAssignmentUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kAssignmentExportAllRadioBoxWidgetID,			kAssignmentUIPrefix + 35)

DECLARE_PMID(kWidgetIDSpace, kSLNewButtonWidgetID,							kAssignmentUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kSLDeleteButtonWidgetID,						kAssignmentUIPrefix + 38)

DECLARE_PMID(kWidgetIDSpace, kAssignmentFolderLabelWidgetID,					kAssignmentUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kAssignmentLocationWidgetID,					kAssignmentUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kDeleteAssignmentWarningWidgetId,				kAssignmentUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kAssignmentRelinkButtonWidgetID,				kAssignmentUIPrefix + 42)
//DECLARE_PMID(kWidgetIDSpace, kIconMissingWidgetId,							kAssignmentUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainStoriesCheckedOutByCurrentID,	kAssignmentUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainLinksMissingModifiedID,			kAssignmentUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kIncludeLinksWhenPackageWidgetID,				kAssignmentUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainOpenPackageUndoID,				kAssignmentUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kAsnPkgAlertDlgWidgetID,						kAssignmentUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kAssignmentPackageAlertStaticWidgetID,			kAssignmentUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kAssignmentPackageAlertClusterWidgetID,		kAssignmentUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kAssignmentPackageAlertRB1WidgetID,			kAssignmentUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kAssignmentPackageAlertRB2WidgetID,			kAssignmentUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kAssignmentPackageAlertRB3WidgetID,			kAssignmentUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kAsnPkgAlertWarningIconWidgetID,				kAssignmentUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kStoryListTVUnassignedNodeWidgetID,			kAssignmentUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kAssignmentOptionsCS3DlgWidgetID,				kAssignmentUIPrefix + 58)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,	kStoryListPanelActionID,					kAssignmentUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,	kSLNewAssignmentActionID,					kAssignmentUIPrefix + 2)
DECLARE_PMID(kActionIDSpace,	kSLRemoveActionID,							kAssignmentUIPrefix + 3)
DECLARE_PMID(kActionIDSpace,	kSLAssignmentOptionsActionID,				kAssignmentUIPrefix + 4)
DECLARE_PMID(kActionIDSpace,	kSLNewAssignmentNoUIActionID,				kAssignmentUIPrefix + 5)
DECLARE_PMID(kActionIDSpace,	kSeperatorActionID,							kAssignmentUIPrefix + 6)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction1ID,						kAssignmentUIPrefix + 7)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction2ID,						kAssignmentUIPrefix + 8)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction3ID,						kAssignmentUIPrefix + 9)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction4ID,						kAssignmentUIPrefix + 10)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction5ID,						kAssignmentUIPrefix + 11)
DECLARE_PMID(kActionIDSpace,	kSLGoToActionID,							kAssignmentUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,	kSLRelinkAssignmentActionID,				kAssignmentUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,	kSLUpdateSelectedAssignmentsActionID,		kAssignmentUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,	kSLUpdateAllAssignmentsActionID,			kAssignmentUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,	kShowHideAssignmentColorID,					kAssignmentUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction6ID,						kAssignmentUIPrefix + 17)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction7ID,						kAssignmentUIPrefix + 18)
DECLARE_PMID(kActionIDSpace,	kSeperatorAction8ID,						kAssignmentUIPrefix + 19)
DECLARE_PMID(kActionIDSpace,	kSLNoDialogRemoveActionID,					kAssignmentUIPrefix + 20)

//reserve for dynamic menu items
DECLARE_PMID(kActionIDSpace,	kSLAddToNewAssignmentActionID,						kAssignmentUIPrefix + 21)
DECLARE_PMID(kActionIDSpace,	kSLAddToNewAssignmentRtMenuActionID,				kAssignmentUIPrefix + 22)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToNewAssignmentActionID,					kAssignmentUIPrefix + 23)
DECLARE_PMID(kActionIDSpace,	kSLAddLayerToNewAssignmentActionID,					kAssignmentUIPrefix + 24)
DECLARE_PMID(kActionIDSpace,	kSLAddAllStoriesToNewAssignmentActionID,			kAssignmentUIPrefix + 25)
DECLARE_PMID(kActionIDSpace,	kSLAddAllGraphicsToNewAssignmentActionID,			kAssignmentUIPrefix + 26)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToNewAssignmentTextContextActionID,		kAssignmentUIPrefix + 27)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToNewAssignmentLayoutContextActionID,		kAssignmentUIPrefix + 28)

DECLARE_PMID(kActionIDSpace,	kSLAddToAssignmentDynamicActionID,					kAssignmentUIPrefix + 29)
DECLARE_PMID(kActionIDSpace,	kSLAddToAssignmentDynamicEndActionID,				kAssignmentUIPrefix + 54)
DECLARE_PMID(kActionIDSpace,	kSLAddToAssignmentRtMenuDynamicActionID,			kAssignmentUIPrefix + 55)
DECLARE_PMID(kActionIDSpace,	kSLAddToAssignmentRtMenuDynamicEndActionID,			kAssignmentUIPrefix + 80)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentDynamicActionID,				kAssignmentUIPrefix + 81)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentDynamicEndActionID,			kAssignmentUIPrefix + 106)
DECLARE_PMID(kActionIDSpace,	kSLAddLayerToAssignmentDynamicActionID,				kAssignmentUIPrefix + 107)
DECLARE_PMID(kActionIDSpace,	kSLAddLayerToAssignmentDynamicEndActionID,			kAssignmentUIPrefix + 132)
DECLARE_PMID(kActionIDSpace,	kSLAddAllStoriesToAssignmentDynamicActionID,		kAssignmentUIPrefix + 133)
DECLARE_PMID(kActionIDSpace,	kSLAddAllStoriesToAssignmentDynamicEndActionID,		kAssignmentUIPrefix + 158)
DECLARE_PMID(kActionIDSpace,	kSLAddAllGraphicsToAssignmentDynamicActionID,		kAssignmentUIPrefix + 159)
DECLARE_PMID(kActionIDSpace,	kSLAddAllGraphicsToAssignmentDynamicEndActionID,	kAssignmentUIPrefix + 184)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentTextContextDynamicActionID,	kAssignmentUIPrefix + 185)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentTextContextDynamicEndActionID,	kAssignmentUIPrefix + 210)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentLayoutContextDynamicActionID,		kAssignmentUIPrefix + 211)
DECLARE_PMID(kActionIDSpace,	kSLAddSelToAssignmentLayoutContextDynamicEndActionID,	kAssignmentUIPrefix + 236)
DECLARE_PMID(kActionIDSpace,	kPackageAssignmentActionID,							kAssignmentUIPrefix + 237)
DECLARE_PMID(kActionIDSpace, 	kSLRevealInFinderActionID, 								kAssignmentUIPrefix + 238)
DECLARE_PMID(kActionIDSpace, 	kSLRevealInBridgeActionID, 								kAssignmentUIPrefix + 239)
DECLARE_PMID(kActionIDSpace,	kPackageAndEmailAssignmentActionID,					kAssignmentUIPrefix + 240)
DECLARE_PMID(kActionIDSpace,	kForwardPackagedAssignmentActionID,					kAssignmentUIPrefix + 241)
DECLARE_PMID(kActionIDSpace,	kForwardAndEmailPackagedAssignmentActionID,			kAssignmentUIPrefix + 242)
DECLARE_PMID(kActionIDSpace,	kReturnPackagedAssignmentActionID,						kAssignmentUIPrefix + 243)
DECLARE_PMID(kActionIDSpace,	kReturnAndEmailPackagedAssignmentActionID,				kAssignmentUIPrefix + 244)
DECLARE_PMID(kActionIDSpace,	kOpenPackagedAssignmentActionID,						kAssignmentUIPrefix + 245)
DECLARE_PMID(kActionIDSpace,	kSeparatorAction6ID,									kAssignmentUIPrefix + 246)
DECLARE_PMID(kActionIDSpace,	kCancelPackagedAssignmentActionID,						kAssignmentUIPrefix + 247)
DECLARE_PMID(kActionIDSpace,	kSeparatorAction9ID,									kAssignmentUIPrefix + 248)
DECLARE_PMID(kActionIDSpace,	kSeparatorAction10ID,									kAssignmentUIPrefix + 249)
DECLARE_PMID(kActionIDSpace,	kSLUpdateOutOfDateAssignmentsActionID,			kAssignmentUIPrefix + 250)


//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Error Codes
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Strings
//----------------------------------------------------------------------------------------

#define kStoryListPanelStringsRsrcID				1000
#define kStoryListPanelStringsNoTransRsrcID			2000
#define kStoryListPanelActionRsrcID					2100
#define kStoryListPanelMenuRsrcID					3100
#define kStoryListPanelRsrcID						4100
#define kStoryListPanelListRsrcID					4200
#define kStoryListTVNodeRsrcID						4300
#define kStoryListTVUnassignedNodeRsrcID			4400

#endif // __ASSIGNMENTUIID__
