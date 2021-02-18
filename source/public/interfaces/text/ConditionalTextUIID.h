//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ConditionalTextUIID.h $
//  
//  Owner: Michele Stutzman
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

#ifndef __ConditionalTextUIID__
#define __ConditionalTextUIID__

#pragma once

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kConditionalTextUIPrefix			RezLong(0x20800)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

//PlugInID
#define kConditionalTextUIPluginName	"ConditionalTextUI"
DECLARE_PMID(kPlugInIDSpace, kConditionalTextUIPluginID, kConditionalTextUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kConditionalTextUIPanelBoss, kConditionalTextUIPrefix + 1)
DECLARE_PMID(kClassIDSpace,	kConditionalTextUIPanelMenuBoss, kConditionalTextUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kNewConditionTagButtonBoss, kConditionalTextUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDeleteConditionTagButtonBoss, kConditionalTextUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kConditionTagEyeballWidgetBoss, kConditionalTextUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kConditionTagListTreeViewWidgetBoss, kConditionalTextUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kConditionTagTreeViewNodeWidgetBoss, kConditionalTextUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kConditionTagListDNDHandlerBoss, kConditionalTextUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kConditionTagNameILEBoss, kConditionalTextUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kConditionTagUIColorSwatchWidgetBoss, kConditionalTextUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kConditionTagOptionsDialogBoss, kConditionalTextUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kConditionalTextLayoutActionBoss, kConditionalTextUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kShowConditionIndicatorsDropDownBoss, kConditionalTextUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kConditionAppliedIconBoss, kConditionalTextUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kConditionSetsDropDownWidgetBoss, kConditionalTextUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kConditionTagTVNodeContextMenuBoss, kConditionalTextUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kNoConditionTagTreeViewNodeWidgetBoss, kConditionalTextUIPrefix + 17)
//gap
DECLARE_PMID(kClassIDSpace, kConditionTagDeleteDialogBoss, kConditionalTextUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kConditionSetNameDialogBoss, kConditionalTextUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kConditionsQuickApplyServiceBoss, kConditionalTextUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kNewConditionSetButtonBoss, kConditionalTextUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kConditionStatusTextWidgetBoss, kConditionalTextUIPrefix + 23)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kConditionalTextUIPanelViewImpl, kConditionalTextUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextUIPanelMenuActionImpl, kConditionalTextUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kNewConditionTagButtonObserverImpl, kConditionalTextUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDeleteConditionTagButtonObserverImpl, kConditionalTextUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kConditionTagEyeballObserverImpl, kConditionalTextUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListTreeViewAdapterImpl, kConditionalTextUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListTreeViewWidgetMgrImpl, kConditionalTextUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListTreeObserverImpl, kConditionalTextUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListTreeSelectionObserverImpl, kConditionalTextUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListDNDSourceImpl, kConditionalTextUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListDNDHandlerImpl, kConditionalTextUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDeleteConditionTagButtonDNDTargetImpl, kConditionalTextUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kConditionTagNameILEObserverImpl, kConditionalTextUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kConditionTagNameILEEditingAttributesImpl, kConditionalTextUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kConditionTagNameTextValidationImpl, kConditionalTextUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kConditionTagColorSwatchViewImpl, kConditionalTextUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextUIPanelDetailControllerImpl, kConditionalTextUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kConditionTagListTreeControllerImpl, kConditionalTextUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextUIFacadeImpl, kConditionalTextUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kConditionTagOptionsDialogControllerImpl, kConditionalTextUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextLayoutActionImpl, kConditionalTextUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextLayoutObserverImpl, kConditionalTextUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kConditionTagEyeballViewImpl, kConditionalTextUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kShowConditionIndicatorsObserverImpl, kConditionalTextUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kConditionSetDropDownTipImpl, kConditionalTextUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kConditionSetDropDownObserverImpl, kConditionalTextUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kConditionTagOptionsDialogObserverImpl, kConditionalTextUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextLayoutTipImpl, kConditionalTextUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextGalleyTipImpl, kConditionalTextUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kConditionalTextVisitorHelperImpl, kConditionalTextUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kConditionTagTVNodeTipImpl, kConditionalTextUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kConditionTagTVNodeContextMenuImpl, kConditionalTextUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kConditionTagTVNodeEHImpl, kConditionalTextUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kConditionTagDeleteDialogControllerImpl, kConditionalTextUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kConditionsQuickApplyServiceImpl, kConditionalTextUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kConditionSetNameDialogControllerImpl, kConditionalTextUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kNewConditionSetButtonObserverImpl, kConditionalTextUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kConditionStatusTextSelectionObserverImpl, kConditionalTextUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kConditionStaticTextViewImpl, kConditionalTextUIPrefix + 39)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIPanelWidgetID, kConditionalTextUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIPanelControlStripWidgetId, kConditionalTextUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kNewConditionTagButtonWidgetID, kConditionalTextUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kDeleteConditionTagButtonWidgetID, kConditionalTextUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIPanelListWidgetId, kConditionalTextUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kConditionTagListTreeViewWidgetID, kConditionalTextUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kConditionTagTreeViewNodeWidgetID, kConditionalTextUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kConditionTagEyeballWidgetID, kConditionalTextUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIStatusWidgetID, kConditionalTextUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kConditionTagNameWidgetID, kConditionalTextUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kConditionTagColorSwatchWidgetID, kConditionalTextUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kConditionTagAppliedStateWidgetId, kConditionalTextUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kShowConditionIndicatorsWidgetId, kConditionalTextUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIGenericPanelWidgetID, kConditionalTextUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kConditionTagDeleteDialogWidgetId, kConditionalTextUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kConditionTagDeleteWarningIconWidgetId, kConditionalTextUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kConditionTagDeleteStaticWidgetID, kConditionalTextUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kConditionTagDeletePopupWidgetID, kConditionalTextUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIPanelSetsAreaWidgetId, kConditionalTextUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kConditionalTextUIPanelIndicatorsAreaWidgetId, kConditionalTextUIPrefix + 20)
//gap
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsButtonsPanelWidgetID, kConditionalTextUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsIndicatorHeaderWidgetID, kConditionalTextUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorColorEditWidgetID, kConditionalTextUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorAppearanceEditWidgetID, kConditionalTextUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorMethodEditWidgetID, kConditionalTextUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorEditPanelWidgetID, kConditionalTextUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorColorStaticWidgetID, kConditionalTextUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorAppearanceStaticWidgetID, kConditionalTextUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorMethodStaticWidgetID, kConditionalTextUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIndicatorLabelsPanelWidgetID, kConditionalTextUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsIndicatorPanelWidgetId, kConditionalTextUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsIndicatorGroupPanelWidgetId, kConditionalTextUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kConditionTagNameEditWidgetID, kConditionalTextUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kConditionTagNameEditPanelWidgetID, kConditionalTextUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kConditionTagNameStaticWidgetID, kConditionalTextUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kConditionTagNameLabelsPanelWidgetID, kConditionalTextUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsNamePanelWidgetId, kConditionalTextUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsNameGroupPanelWidgetID, kConditionalTextUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsPanelWidgetID, kConditionalTextUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsDialogWidgetId, kConditionalTextUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kConditionTagOptionsNameHeaderWidgetID, kConditionalTextUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kConditionUISeperator1WidgetID, kConditionalTextUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kConditionUISeperator2WidgetID, kConditionalTextUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kConditionSetsDropDownWidgetID, kConditionalTextUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kConditionSetsDropDownLabelWidgetID, kConditionalTextUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kNoConditionTagTreeViewNodeWidgetID, kConditionalTextUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kConditionSetNameDialogWidgetID, kConditionalTextUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kConditionSetNameStaticWidgetID, kConditionalTextUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kConditionSetNameEditBoxWidgetID, kConditionalTextUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kNewConditionSetButtonWidgetID, kConditionalTextUIPrefix + 60)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ICONDITIONALTEXTUIFACADE, kConditionalTextUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONDITIONALTEXTLAYOUTOBSERVER, kConditionalTextUIPrefix + 2)

//----------------------------------------------------------------------------------------
// Error identifiers
//----------------------------------------------------------------------------------------
//DECLARE_PMID(kErrorIDSpace, kMyErr, kConditionalTextUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kConditionalTextUIPanelActionID, kConditionalTextUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewConditionTagActionID, kConditionalTextUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kContextMenuDeleteConditionTagActionID, kConditionalTextUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kContextMenuEditConditionTagActionID, kConditionalTextUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kContextMenuUnapplyConditionTagActionID, kConditionalTextUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kLoadConditionTagsActionID, kConditionalTextUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kLoadConditionTagsAndSetsActionID, kConditionalTextUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kLoadSeperatorActionID, kConditionalTextUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kQuickApplyConditionsPrefActionID, kConditionalTextUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kQuickApplyConditionSetsPrefActionID, kConditionalTextUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kDeleteConditionTagActionID, kConditionalTextUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kEditConditionSeperatorActionID, kConditionalTextUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kEditConditionTagActionID, kConditionalTextUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kShowConditionIndicatorsActionID, kConditionalTextUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kShowAllTagsActionID, kConditionalTextUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kHideAllTagsActionID, kConditionalTextUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kShowHideConditionsSeperatorActionID, kConditionalTextUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kShowAndPrintConditionIndicatorsActionID, kConditionalTextUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kHideConditionIndicatorsActionID, kConditionalTextUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kShowHideConditionSetOptionsActionID, kConditionalTextUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kConditionSetOptionsSeperatorActionID, kConditionalTextUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSelectUnusedSeperatorActionID, kConditionalTextUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kSelectUnusedConditionsActionID, kConditionalTextUIPrefix + 23)

#endif //  __ConditionalTextID__

