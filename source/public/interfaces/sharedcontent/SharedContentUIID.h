//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/SharedContentUIID.h $ 
//   
//  Owner: Ashish Duggal
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//
//  ADOBE CONFIDENTIAL
//   
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe. 
//   
//======================================================================================== 

#ifndef __SharedContentUIID__
#define __SharedContentUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSharedContentUIPrefix				RezLong(0x21F00)

// <Start IDC>
#define kSharedContentUIPluginName 			"Shared Content UI"
DECLARE_PMID(kPlugInIDSpace, kSharedContentUIPluginID, kSharedContentUIPrefix + 1)

// <Class ID> 
DECLARE_PMID(kClassIDSpace, kPlaceLinkStoryMenuActionBoss, kSharedContentUIPrefix + 0)
//---gap---
DECLARE_PMID(kClassIDSpace, kLinkedStoryStatusActionComponentBoss, kSharedContentUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSharedContentLayoutActionBoss, kSharedContentUIPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kStyleMappingsDialogBoss, kSharedContentUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kStyleMappingSplitterWidgetBoss, kSharedContentUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kStyleMappingListWidgetBoss, kSharedContentUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kStyleNameComboboxWidgetBoss, kSharedContentUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kStyleListElementWidgetBoss, kSharedContentUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAddStyleMappingButtonBoss, kSharedContentUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDeleteStyleMappingButtonBoss, kSharedContentUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kStyleMappingsComboILEWidgetBoss, kSharedContentUIPrefix + 12)


//---------------gap----------------------------

DECLARE_PMID(kClassIDSpace, kPlaceLinkPageItemMenuActionBoss, kSharedContentUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kArticleLinkOptionsDialogBoss, kSharedContentUIPrefix + 21)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kPlaceLinkStoryMenuActionImpl, kSharedContentUIPrefix + 0) 
//---gap---
DECLARE_PMID(kImplementationIDSpace, kSharedStoryUIUtilsImpl, kSharedContentUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kLinkedStoryStatusActionComponentImpl, kSharedContentUIPrefix + 3) 
DECLARE_PMID(kImplementationIDSpace, kSharedContentLayoutActionImpl, kSharedContentUIPrefix + 4) 
DECLARE_PMID(kImplementationIDSpace, kSharedContentLayoutObserverImpl, kSharedContentUIPrefix + 5) 
//gap
DECLARE_PMID(kImplementationIDSpace, kStyleMappingsDialogControllerImpl, kSharedContentUIPrefix + 8) 
DECLARE_PMID(kImplementationIDSpace, kStoryLinkOptionsDialogObserverimpl, kSharedContentUIPrefix + 9) 
//DECLARE_PMID(kImplementationIDSpace, kStyleMappingSplitterRollOverImpl, kSharedContentUIPrefix + 10) 
DECLARE_PMID(kImplementationIDSpace, kMappingListTreeViewAdapterImpl, kSharedContentUIPrefix + 11) 
DECLARE_PMID(kImplementationIDSpace, kMappingListWidgetMgrImpl, kSharedContentUIPrefix + 12) 
DECLARE_PMID(kImplementationIDSpace, kStyleMappingsDialogObserverimpl, kSharedContentUIPrefix + 13) 
DECLARE_PMID(kImplementationIDSpace, kStyleNameEditBoxObserverImpl, kSharedContentUIPrefix + 14) 
//gap
DECLARE_PMID(kImplementationIDSpace, kStyleMappingNameValidationImpl, kSharedContentUIPrefix + 16) 

//-----------------------gap-----------------------
DECLARE_PMID(kImplementationIDSpace, kPlaceLinkPageItemMenuActionImpl, kSharedContentUIPrefix + 20) 
DECLARE_PMID(kImplementationIDSpace, kArticleLinkOptionsDialogControllerImpl, kSharedContentUIPrefix + 21) 
DECLARE_PMID(kImplementationIDSpace, kLinkedArticlePlacePrefsDataImpl, kSharedContentUIPrefix + 22) 
DECLARE_PMID(kImplementationIDSpace, kSharedContentUIUtilsImpl, kSharedContentUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkObjectAdornmentTipImpl, kSharedContentUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kStyleGroupCBAttributesImpl, kSharedContentUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingSplitterRollOverImpl, kSharedContentUIPrefix + 26)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDSTORYUIUTILS, kSharedContentUIPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCUIDIALOGCANCELLED, kSharedContentUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTLAYOUTOBSERVER, kSharedContentUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEMAPPINGSCHANGED, kSharedContentUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTIPLESELECTION, kSharedContentUIPrefix + 4)


//-------------------------------gap---------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDARTICLEPLACEPREFSDATA, kSharedContentUIPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOPTIONSSTORYUIDLISTDATA, kSharedContentUIPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTUIUTILS, kSharedContentUIPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTUIDREFLIST, kSharedContentUIPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOPTIONSOBJECTUIDLISTDATA, kSharedContentUIPrefix + 54)

// <Action ID> 
DECLARE_PMID(kActionIDSpace, kPlaceLinkStoryActionID, kSharedContentUIPrefix + 0)
//---gap---
DECLARE_PMID(kActionIDSpace, kShowLinkedStoryStatusActionID, kSharedContentUIPrefix + 2) 

//-------------------------------gap---------------------------

//DECLARE_PMID(kActionIDSpace, kPlaceLinkPageItemActionID, kSharedContentUIPrefix + 20) -- gap---
DECLARE_PMID(kActionIDSpace, kLinkedArticleOptionsDlgActionID, kSharedContentUIPrefix + 21) 


//<Widget ID>
//---gap---
DECLARE_PMID(kWidgetIDSpace, kSharedContentUIRemoveForcedLineBreaksCheckboxWidgetID, kSharedContentUIPrefix + 3)
//gap
DECLARE_PMID(kWidgetIDSpace, kStyleMappingsDialogWidgetID, kSharedContentUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kStyleTypeDropDownWidgetId, kSharedContentUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kStyleMappingsSplitterWidgetID, kSharedContentUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kLeftSplitterPanelWidgetID, kSharedContentUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kRightSplitterPanelWidgetID, kSharedContentUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kSourceStyleTitleWidgetID, kSharedContentUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kTargetStyleTitleWidgetID, kSharedContentUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kStyleMappingListWidgetID, kSharedContentUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSrcStyleNameComboILEWidgetID, kSharedContentUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kDstStyleNameComboILEWidgetID, kSharedContentUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kStyleMappingListElementWidgetID, kSharedContentUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kAddStyleMappingBtnWidgetId, kSharedContentUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kDeleteStyleMappingBtnWidgetId, kSharedContentUIPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kMappingRightSplitterPanelWidgetID, kSharedContentUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kMappingSplitterWidgetID, kSharedContentUIPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kStyleMappingComboILEWidgetID, kSharedContentUIPrefix + 21)


//-------------------------------gap---------------------------
DECLARE_PMID(kWidgetIDSpace, kArticleLinkOptionsDialogWidgetID, kSharedContentUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kOverridePathgeometryCheckboxWidgetID, kSharedContentUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kOverrideGraphicAttributesCheckboxWidgetID, kSharedContentUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kOverrideContentCheckboxWidgetID, kSharedContentUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kArticleGeneralLinkOptionsDialogWidgetID, kSharedContentUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kOverrideInteractiveAttributesCheckboxWidgetID, kSharedContentUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kOverrideGuidanceTextLabelWidgetID, kSharedContentUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kAdvancedButtonWidgetID, kSharedContentUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kOverwriteWarningCheckboxWidgetID, kSharedContentUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kUpdateOnSaveCheckboxWidgetID, kSharedContentUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kUseAsDefaultCheckboxWidgetID, kSharedContentUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kArticleOptionsSeparatorWidgetID, kSharedContentUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kStyleMappingExceptionsCheckboxWidgetID, kSharedContentUIPrefix + 62)
//--- gap ---
DECLARE_PMID(kWidgetIDSpace, kCustomStyleMappingButtonWidgetID, kSharedContentUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kOverrideOtherAttributesCheckboxWidgetID, kSharedContentUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kSourceDocDropDownWidgetId, kSharedContentUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kNumExceptionsStringWidgetID, kSharedContentUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kStyleMappingsInfoTextWidgetID, kSharedContentUIPrefix + 68)


// Resource IDs 
#define kSharedContentUIStringsRsrcID						100

// Resource IDs 
#define kSharedArticleUIStringsRsrcID						200

#define kSharedArticleLinkObjectIconRsrcID					2000
	
#endif // __SharedContentID__
