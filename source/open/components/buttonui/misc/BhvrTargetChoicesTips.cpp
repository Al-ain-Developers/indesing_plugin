//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/misc/BhvrTargetChoicesTips.cpp $
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
//  ADOBE CONFIDENTIAL
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

#include "IActiveContext.h"
#include "IAnimationBehaviorData.h"
#include "IAppearanceItemFacade.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "IIntData.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "AbstractTip.h"
#include "ITool.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"

// ----- Includes -----

#include "PMString.h"
#include "StringUtils.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "BehaviorUIID.h"
#include "FormFieldUIID.h"


class BhvrTargetChoicesTips : public AbstractTip
{			
public:
	BhvrTargetChoicesTips( IPMUnknown *boss );
	virtual ~BhvrTargetChoicesTips();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);

private:
	template<typename Ifc>
	inline InterfacePtr<Ifc> GetWidget(WidgetID const &id) const
	{
		// Pardon the mess
		return InterfacePtr<Ifc>(static_cast<Ifc *>(Utils<IWidgetUtils>()->QueryRelatedWidget(this, id, Ifc::kDefaultIID)));
	}
};

// =============================================================================
// *** BhvrTargetChoicesTips impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(BhvrTargetChoicesTips, kBhvrTargetChoicesTipsImpl)

BhvrTargetChoicesTips::BhvrTargetChoicesTips(IPMUnknown *boss) :
	AbstractTip(boss)
{
} // end constructor

BhvrTargetChoicesTips::~BhvrTargetChoicesTips()
{
} // end destructor

// -----------------------------------------------------------------------------

PMString BhvrTargetChoicesTips::GetTipText(const PMPoint& mouseLocation)
{
	PMString	str("");

	InterfacePtr<IControlView> view(this, UseDefaultIID());

	if (view)
	{
		WidgetID	wID = view->GetWidgetID();
		InterfacePtr<IDropDownListController> choice(nil);

		switch( wID.Get() )
		{
			case kAnimationWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kAnimationWidgetID).forget());
				break;

			case kMovieWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kMovieWidgetID).forget());
				break;

			case kSoundWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kSoundWidgetID).forget());
				break;

			case kMSOTargetChoiceWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kMSOTargetChoiceWidgetID).forget());
				break;

			case kMSOStateChoiceWidgetID:
				{
					InterfacePtr<IDropDownListController> stateChoice = GetWidget<IDropDownListController>(kMSOStateChoiceWidgetID);
					InterfacePtr<IPanelControlData> data(stateChoice, UseDefaultIID());

					int32 stateSelection = stateChoice->GetSelected();
					if (stateSelection >= 0)
					{
						InterfacePtr<IUIDData> msoData(data->GetWidget(stateSelection), UseDefaultIID());
						InterfacePtr<IIntData> stateData(data->GetWidget(stateSelection), UseDefaultIID());
						if (msoData && stateData)
							str = Utils<Facade::IAppearanceItemFacade>()->GetStateName(msoData->GetRef(), stateData->Get());
					}
				}
				break;

			case kNextMSOTargetChoiceWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kNextMSOTargetChoiceWidgetID).forget());
				break;

			case kPrevMSOTargetChoiceWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kPrevMSOTargetChoiceWidgetID).forget());
				break;

			case kAnchorDocumentChoicesWidgetID:
				choice.reset(GetWidget<IDropDownListController>(kAnchorDocumentChoicesWidgetID).forget());
				break;
		}

		if (choice != nil)
		{
			int32 selection = choice->GetSelected();

			bool changed = false;

			if (selection != IDropDownListController::kNoSelection)
			{
				InterfacePtr<IStringListControlData> stringData(choice, UseDefaultIID());
				if (stringData)
					str = stringData->GetString(selection);
			}
		}
	}

	return str;
}  // end GetTipText()

