//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ArticlePanelID.h $
// 
//  Owner: shagupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __ArticlePanelID__
#define __ArticlePanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kArticlePanelPrefix	RezLong(0x21C00)

// <Start IDC>
// PluginID
#define kArticlePanelPluginName 			"Article Panel"
DECLARE_PMID(kPlugInIDSpace, kArticlePanelPluginID, kArticlePanelPrefix + 1)

// <Class ID>
// Boss IDs
DECLARE_PMID(kClassIDSpace, kArticlePanelActionComponentBoss,			kArticlePanelPrefix + 0)
DECLARE_PMID(kClassIDSpace, kArticlePanelWidgetBoss,					kArticlePanelPrefix + 1)
DECLARE_PMID(kClassIDSpace, kArticlePanelTreeWidgetBoss,				kArticlePanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kArticleTreeElementBoss,					kArticlePanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kNewArticleButtonBoss,						kArticlePanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDeleteArticleButtonBoss,					kArticlePanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kArticlePanelCustomHandlerBoss,				kArticlePanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kArticlePanelNameBoss,						kArticlePanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAddContentButtonBoss,						kArticlePanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kArticlePanelGuidanceTextWidgetBoss,		kArticlePanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kArticlePanelSelectionProxyBoss,			kArticlePanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kArticlePanelStatusStringBoss,				kArticlePanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kExportArticleCheckBoxBoss,					kArticlePanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kArticleOptionsDialogBoss,					kArticlePanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kArticleOptionsCheckBoxBoss,				kArticlePanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCreateNewArticleCmdBoss,					kArticlePanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kAddPageItemstoArticleCmdBoss,				kArticlePanelPrefix + 16)


// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEHIERARCHY,					kArticlePanelPrefix + 0) 
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEPANELUTILS,					kArticlePanelPrefix + 1) 
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEUIDDATA,					kArticlePanelPrefix + 2) 
DECLARE_PMID(kInterfaceIDSpace, IID_IDIRECTMEMBERUIDDATA,				kArticlePanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLESELECTIONPROXYDRAWDATA,		kArticlePanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEARTICLEPROXYSELECTION,		kArticlePanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESTATUSWIDGET,				kArticlePanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPANDEDARTICLENODESLIST,			kArticlePanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDARTICLENODESLIST,			kArticlePanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLELISTDATA,					kArticlePanelPrefix + 9)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kArticlePanelActionComponentImpl,				kArticlePanelPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelTreeViewAdapterImpl,				kArticlePanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelTreeViewWidgetMgrImpl,			kArticlePanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelViewImpl,							kArticlePanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelTreeObserverImpl,					kArticlePanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelObserverImpl,						kArticlePanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kArticleTreeDragDropTargetImpl,				kArticlePanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelUtilsImpl,						kArticlePanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelDragDropSourceImpl,				kArticlePanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelCustomDEHandlerImpl,				kArticlePanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelTreeViewControllerImpl,			kArticlePanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kArticleNameEditObserverImpl,					kArticlePanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelNameILEEditingAttributesImpl,		kArticlePanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kArticleNameTextValidationImpl,				kArticlePanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelTreeNodeEHImpl,					kArticlePanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kNewArticleButtonObserverImpl,					kArticlePanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDeleteArticleButtonObserverImpl,				kArticlePanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kAddContentButtonObserverImpl,					kArticlePanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelDragDropTargetImpl,				kArticlePanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kArticlePanelSelectionObserverImpl,			kArticlePanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kArticleSelectionProxyDrawDataImpl,			kArticlePanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kArticleSelectionProxyViewImpl,				kArticlePanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kStatusWidgetObserverImpl,						kArticlePanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kStatusWidgetTipImpl,							kArticlePanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDeleteArticleButtonTipImpl,					kArticlePanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kExportOptionCheckBoxObserverImpl,				kArticlePanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kExpandedNodesImpl,							kArticlePanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSelectedNodesImpl,							kArticlePanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kArticleOptionsDialogControllerImpl,			kArticlePanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kArticleNameEHImpl,							kArticlePanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kArticleOptionsCheckBoxObserverImpl,			kArticlePanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCreateNewArticleCmdImpl,						kArticlePanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kAddPageItemstoArticleCmdImpl,					kArticlePanelPrefix + 32)


// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kArticlePanelWidgetID,					kArticlePanelPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kArticlePanelTreeWidgetID,				kArticlePanelPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kArticleRowWidgetId,					kArticlePanelPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kArticleNameWidgetID,					kArticlePanelPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kArticlePanelSeparatorWidgetID,		kArticlePanelPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kArticleControlStripWidgetID,			kArticlePanelPrefix + 5) 
DECLARE_PMID(kWidgetIDSpace, kArticleNewButtonWidgetID,				kArticlePanelPrefix + 6) 
DECLARE_PMID(kWidgetIDSpace, kArticleDeleteButtonWidgetID,			kArticlePanelPrefix + 7) 
DECLARE_PMID(kWidgetIDSpace, kArticlePanelNodeWidgetID,				kArticlePanelPrefix + 8) 
DECLARE_PMID(kWidgetIDSpace, kTextIconWidgetId,						kArticlePanelPrefix + 9) 
DECLARE_PMID(kWidgetIDSpace, kGroupIconWidgetId,					kArticlePanelPrefix + 10) 
DECLARE_PMID(kWidgetIDSpace, kPlacedIconWidgetId,					kArticlePanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kArticlePageItemRowWidgetId,			kArticlePanelPrefix + 12) 
DECLARE_PMID(kWidgetIDSpace, kArticleObjectRowWidgetId,				kArticlePanelPrefix + 13) 
DECLARE_PMID(kWidgetIDSpace, kAddContentIconWidgetId,				kArticlePanelPrefix + 14) 
DECLARE_PMID(kWidgetIDSpace, kArticlePanelGuidanceTextWidgetID,		kArticlePanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPgItemSelectionProxyWidgetID,			kArticlePanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kArticleStatusTextWidgetID,			kArticlePanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kExportArticleCheckBoxWidgetID,		kArticlePanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kArticleOptionsDialogID,				kArticlePanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kArticleNameStaticWidgetID,			kArticlePanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kArtNameWidgetID,						kArticlePanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kExportArticleCBWidgetID,				kArticlePanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kDontShowAgainDuplicatePageItems,	    kArticlePanelPrefix + 23) 
DECLARE_PMID(kWidgetIDSpace, kCheckBoxGuidanceTextWidgetID,		    kArticlePanelPrefix + 24) 


// <Action ID>
DECLARE_PMID(kActionIDSpace, kArticlePanelActionID,								kArticlePanelPrefix + 0)
DECLARE_PMID(kActionIDSpace, kArticlePanelNewArticleActionID,					kArticlePanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kArticlePanelMenuSepActionID,						kArticlePanelPrefix + 2) 
DECLARE_PMID(kActionIDSpace, kArticlePanelAddSelectionActionID,					kArticlePanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kArticlePanelMenuSep1ActionID,						kArticlePanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kArticlePanelDeleteActionID,						kArticlePanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kArticlePanelGoToItemActionID,						kArticlePanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kArticlePanelAddDocumentContentActionID,			kArticlePanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kArticlePanelUseForPDFStructureOrderActionID,		kArticlePanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kArticlePanelMenuSep2ActionID,						kArticlePanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kArticlePanelArticleOptionsActionID,				kArticlePanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kArticlePanelMenuSep3ActionID,						kArticlePanelPrefix + 11)

// Messages ID 
DECLARE_PMID(kMessageIDSpace, kSetProxyWidgetMsg, kArticlePanelPrefix + 0) 


#endif
// __ArticlePanelID__
