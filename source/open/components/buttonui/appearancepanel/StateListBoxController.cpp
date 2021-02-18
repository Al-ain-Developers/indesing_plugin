//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateListBoxController.cpp $
//  
//  Owner: Tim Wright
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
//  Based on LayerListBoxController.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IAppearanceSuite.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IViewListBoxControlData.h"
#include "IStateData.h"

// ----- Includes -----

#include "CTreeBasedListBoxController.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

class StateListBoxController : public CTreeBasedListBoxController
{
public:
	typedef CTreeBasedListBoxController inherited;
								StateListBoxController(IPMUnknown* boss);
	virtual						~StateListBoxController();
								
	virtual int32				Search(const PMString& subString) const;
};

CREATE_PMINTERFACE(StateListBoxController, kStateListBoxControllerImpl)

StateListBoxController::StateListBoxController(IPMUnknown *boss) : inherited(boss)
{
}

StateListBoxController::~StateListBoxController()
{
}

int32 StateListBoxController::Search(const PMString& subString) const
{
	bool16 optionKeyDown = ::IsOptionAltKeyPressed();
	if (optionKeyDown) return -1;

	InterfacePtr<IViewListBoxControlData> listData(this, IID_ILISTCONTROLDATA);
	int32 length = listData->Length();
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	
	if (iAppearanceSuite)
	{
		// Look for the subString at the beginning of each name in the first pass.
		// During the second pass, look for the substring anywhere.
		for (int32 pass = 0; pass < 2; pass++)
		{	
			for (int32 i = 0; i < length; i++)
			{
				InterfacePtr<IStateData> listElementStateData((*listData)[i], IID_ISTATEDATA);
				PMString stateName;
				switch (listElementStateData->GetState())
				{
					case Form::kStateNormal:
						stateName = "$$$/Panel/Normal";
						break;
					case Form::kStateOver:
						stateName = "$$$/Panel/Over";
						break;
					case Form::kStateDown:
						stateName = "$$$/Panel/Down";
						break;
					case Form::kStateNormalOff:
						stateName = "$$$/Panel/Off";
						break;
					case Form::kStateNormalOn:
						stateName = "$$$/Panel/On";
						break;
					case Form::kStateOverOff:
						stateName = "$$$/Panel/RolloverOff";
						break;
					case Form::kStateOverOn:
						stateName = "$$$/Panel/RolloverOn";
						break;
					case Form::kStateDownOff:
						stateName = "$$$/Panel/DowmOff";
						break;
					case Form::kStateDownOn:
						stateName = "$$$/Panel/DownOn";
						break;	
					default:
						stateName = iAppearanceSuite->GetStateName(listElementStateData->GetState());
						break;
				}
				
				if (listElementStateData)
				{					
					// for the first pass, match any item that starts with these letters, regardless of case.
					if(pass == 0)
					{
						stateName.Remove(subString.CharCount(),kMaxInt32); // chop off the end.
						if(stateName.Compare(kFalse,subString) == 0)
							return i;
					}
					else
					{
						// for the second pass, match any item that contains these exact letters, considering case.
						if (stateName.IndexOfString(subString) > 0)
							return i;
					}
				}
			}
		}
	}
	
	return -1;
}
