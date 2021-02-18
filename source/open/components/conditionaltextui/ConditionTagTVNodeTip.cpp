//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagTVNodeTip.cpp $
//  
//  Owner: Matt Ramme
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IConditionTag.h"
#include "IConditionTagSuite.h"
#include "IControlView.h"
#include "IPanelControlData.h" 
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWidgetParent.h"

// ----- Includes -----
#include "AbstractTip.h"
#include "ConditionalTextUIDefs.h"
#include "IconRsrcDefs.h"
#include "PMString.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "ISelectionUtils.h"
#include "StringUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagTVNodeTip : public AbstractTip
{			
public:
	ConditionTagTVNodeTip( IPMUnknown *boss );
	virtual ~ConditionTagTVNodeTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE( ConditionTagTVNodeTip, kConditionTagTVNodeTipImpl )


ConditionTagTVNodeTip::ConditionTagTVNodeTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
} 



ConditionTagTVNodeTip::~ConditionTagTVNodeTip()
{
} 


PMString ConditionTagTVNodeTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString("");
	if (GetClass(this) == kConditionTagTreeViewNodeWidgetBoss)
	{
		InterfacePtr<IPanelControlData> pData(this, UseDefaultIID());

		InterfacePtr<IControlView> view(this, UseDefaultIID());
		PMRect frame = view->GetBBox();

		IControlView *eyeballWidget = pData->FindWidget(kConditionTagEyeballWidgetID);
		IControlView *appliedWidget = pData->FindWidget(kConditionTagAppliedStateWidgetId);
		IControlView *indicatorWidget = pData->FindWidget(kConditionTagColorSwatchWidgetID);

		PMRect eyeballRect = eyeballWidget->GetBBox();
		PMRect appliedRect = appliedWidget->GetBBox();
		PMRect indicatorRect = indicatorWidget->GetBBox();

		if (eyeballRect.PointIn(mouseLocation))
		{
			InterfacePtr<ITriStateControlData> eyeballData(eyeballWidget, UseDefaultIID());
			if (eyeballData->IsSelected())
				tipString.Append("#ConditionalTextEyeballHideWidgetTip");
			else if (eyeballData->IsDeselected())
				tipString.Append("#ConditionalTextEyeballShowWidgetTip");
		}
		else if (appliedRect.PointIn(mouseLocation) && appliedWidget->IsVisible())
		{
			InterfacePtr<IConditionTagSuite> conditionSuite((IConditionTagSuite*)Utils<ISelectionUtils>()->QuerySuite(IConditionTagSuite::kDefaultIID));
			if (conditionSuite == nil)
			{
				tipString.Append("#ConditionalTextApplyNoSelectionTip");
			}
			else
			{
				RsrcID statusIcon = appliedWidget->GetRsrcID();
				if (statusIcon == kAppliedToSomeCharactersIndicatorRsrcID)
					tipString.Append("#ConditionalTextAppliedSomeTip");
				else if (statusIcon == kAppliedToAllCharactersIndicatorRsrcID)
					tipString.Append("#ConditionalTextAppliedAllTip");
				else if (statusIcon == kNoIcon)
					tipString.Append("#ConditionalTextAppliedNoneTip");
			}
		}
		else if (indicatorRect.PointIn(mouseLocation))
		{
			InterfacePtr<IWidgetParent>	forParent(this, UseDefaultIID());
			InterfacePtr<ITreeNodeIDData>	nodeID(this, UseDefaultIID());
			ASSERT_MSG(nodeID, "Can't get node for condition tag!"); 
			
			InterfacePtr<IUIDData>	forDB((IUIDData*)forParent->QueryParentFor(IID_IUIDDATA));
			IDataBase* db = forDB ? forDB->GetItemDataBase() : nil;
			ASSERT_MSG(db, "Can't get database for widget!"); 

			TreeNodePtr<UIDNodeID> tagNode(nodeID->Get());
			InterfacePtr<IConditionTag> tag(db, tagNode->GetUID(), UseDefaultIID());
			IConditionTag::IndicatorMethod tagMethod = tag->GetMethod();
			IConditionTag::UnderlineIndicatorAppearance tagAppearance = tag->GetAppearance();
			tipString = PMString("#ConditionalTextIndicatorTip", PMString::kTranslateDuringCall);
			PMString stringDetail("");
			if (tagMethod == IConditionTag::kHighlight)
				stringDetail = PMString("#ConditionTagOptions_MethodHighlight", PMString::kTranslateDuringCall);
			else if (tagMethod == IConditionTag::kUnderline)
			{
				PMString stringDetail2("#ConditionTagOptions_MethodUnderline", PMString::kTranslateDuringCall);
				if (tagAppearance == IConditionTag::kSingleWavy)
					stringDetail = PMString("#ConditionTagOptions_WavyUnderline", PMString::kTranslateDuringCall);
				else if (tagAppearance == IConditionTag::kSolid)
					stringDetail = PMString("#ConditionTagOptions_SolidUnderline", PMString::kTranslateDuringCall);
				else if (tagAppearance == IConditionTag::kDashed)
					stringDetail = PMString("#ConditionTagOptions_DashedUnderline", PMString::kTranslateDuringCall);
				stringDetail.Append(" ");
				stringDetail.Append(stringDetail2);
			}
			ReplaceStringParameters(&tipString, stringDetail);
			return tipString;
		}
	}
	else if (::GetClass(this) == kNoConditionTagTreeViewNodeWidgetBoss)
	{
		InterfacePtr<IPanelControlData> pData(this, UseDefaultIID());

		InterfacePtr<IControlView> view(this, UseDefaultIID());
		PMRect frame = view->GetBBox();

		IControlView *eyeballWidget = pData->FindWidget(kConditionTagEyeballWidgetID);
		IControlView *appliedWidget = pData->FindWidget(kConditionTagAppliedStateWidgetId);

		PMRect eyeballRect = eyeballWidget->GetBBox();
		PMRect appliedRect = appliedWidget->GetBBox();

		if (eyeballRect.PointIn(mouseLocation))
		{
			InterfacePtr<ITriStateControlData> eyeballData(eyeballWidget, UseDefaultIID());
			tipString.Append("#ConditionalTextEyeballUnconditionalWidgetTip");
		}
		else if (appliedRect.PointIn(mouseLocation) && appliedWidget->IsVisible())
		{
			InterfacePtr<IConditionTagSuite> conditionSuite((IConditionTagSuite*)Utils<ISelectionUtils>()->QuerySuite(IConditionTagSuite::kDefaultIID));
			if (conditionSuite == nil)
			{
				tipString.Append("#ConditionalTextAppliedNoneTipUncondition");
			}
			else
			{
				RsrcID statusIcon = appliedWidget->GetRsrcID();
				if (statusIcon == kAppliedToSomeCharactersIndicatorRsrcID)
					tipString.Append("#ConditionalTextAppliedSomeTipUncondition");
				else if (statusIcon == kAppliedToAllCharactersIndicatorRsrcID)
					tipString.Append("#ConditionalTextAppliedAllTipUncondition");
				else if (statusIcon == kNoIcon)
					tipString.Append("#ConditionalTextAppliedNoneTipUncondition");
			}
		}
	}

	return tipString;
} 
