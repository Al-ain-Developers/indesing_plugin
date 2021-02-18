//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionSetDropDownTip.cpp $
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IConditionalTextFacade.h"
#include "IConditionTag.h"
#include "IConditionTagList.h"
#include "IDocument.h"
#include "IControlView.h"
#include "IPanelControlData.h" 
#include "AbstractTip.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----


// ----- Utility files -----

#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionSetDropDownTip : public AbstractTip
{			
public:
	ConditionSetDropDownTip( IPMUnknown *boss );
	virtual ~ConditionSetDropDownTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

// =============================================================================
// *** ConditionalTextUIFacade impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE( ConditionSetDropDownTip, kConditionSetDropDownTipImpl )

ConditionSetDropDownTip::ConditionSetDropDownTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
} // end constructor

// -----------------------------------------------------------------------------

ConditionSetDropDownTip::~ConditionSetDropDownTip()
{
} // end destructor

// -----------------------------------------------------------------------------

PMString ConditionSetDropDownTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString("");

	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
	if (!panelData)	return tipString;
	
	IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
	InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
	if (!tvController) return tipString;

	InterfacePtr<IUIDData>	forDB(tvController, UseDefaultIID());
	IDataBase* db = forDB ? forDB->GetItemDataBase() : nil;
	if (!db) return tipString;

	InterfacePtr<IWorkspace> workspace(nil);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
	if (doc)
		workspace.reset(static_cast<IWorkspace*>(doc->GetDocWorkSpace().Instantiate(IWorkspace::kDefaultIID)));
	else
		workspace.reset(GetExecutionContextSession()->QueryWorkspace());
	
	UID activeSetUID;
	if (Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeSetUID) == kSuccess && activeSetUID != kInvalidUID)
	{
		bool16 newConditions(kFalse), conditionVisibility(kFalse);

		Facade::IConditionalTextFacade::ConditionSetElementList tagsInSet;
		Utils<Facade::IConditionalTextFacade>()->GetConditionsInConditionSet(UIDRef(db, activeSetUID), tagsInSet);

		InterfacePtr<IConditionTagList> tagList(workspace, UseDefaultIID());
		if (tagList && tagList->GetCount() > tagsInSet.size())
		{
			// There are new conditions since set was created, treat it as "override".
			newConditions = kTrue;
		}

		for (Facade::IConditionalTextFacade::ConditionSetElementList::iterator iter = tagsInSet.begin(); iter != tagsInSet.end(); iter++)
		{
			bool16 currentVisibility;
			Utils<Facade::IConditionalTextFacade>()->GetConditionVisibleState(UIDRef(db, (*iter).first), currentVisibility);

			if (currentVisibility != (bool16)(*iter).second)
			{
				// There are visibility differences, treat it as "override".
				conditionVisibility = kTrue;
				break;
			}
		}

		if (newConditions && conditionVisibility)
			tipString.Append("#SetOverrideTip_NewConditionsAndConditionVisibility");
		else if (newConditions)
			tipString.Append("#SetOverrideTip_NewConditions");
		else if (conditionVisibility)
			tipString.Append("#SetOverrideTip_ConditionVisibility");
	}

	return tipString;
} // end GetTipText()
