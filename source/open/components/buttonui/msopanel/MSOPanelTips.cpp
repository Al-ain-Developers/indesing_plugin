//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTips.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ITool.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----
#include "AbstractTip.h"
#include "FormFieldUIDefs.h"
#include "PMRect.h"
#include "PMString.h"

// ----- Utility files -----

#include "IPalettePanelUtils.h"
#include "StringUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelTips : public AbstractTip
{			
public:
	MSOPanelTips( IPMUnknown *boss );
	virtual ~MSOPanelTips();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

// =============================================================================
// *** MSOPanelTips impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTips, kMSOPanelTipsImpl)

MSOPanelTips::MSOPanelTips(IPMUnknown *boss) :
	AbstractTip(boss)
{
} // end constructor

MSOPanelTips::~MSOPanelTips()
{
} // end destructor

// -----------------------------------------------------------------------------

PMString MSOPanelTips::GetTipText(const PMPoint& mouseLocation)
{
	PMString	str("");

	InterfacePtr<IControlView> view(this, UseDefaultIID());

	if (view)
	{
		WidgetID	wID = view->GetWidgetID();

		if (wID == kMSOSelectionIconWidgetID && view->IsVisible())
		{
			PMRect msoSelectionRect = view && view->IsVisible() ? view->GetBBox() : PMRect();

			if (msoSelectionRect.PointIn(mouseLocation))
			{
				if (view->GetRsrcID() == kMSOIsNotSelectedIconRsrcID)
					str = "$$$/Tip/MSOPanel/MSOIsNotSelected";
				else
					str = "$$$/Tip/MSOPanel/MSOIsSelected";
			}
		}
		else if (wID == kMSOPanelTreeViewNodeWidgetID)
		{
			InterfacePtr<IPanelControlData> pData(this, UseDefaultIID());

			IControlView *selectionIconWidget = pData->FindWidget(kMSOStateSelectionIconWidgetID);

			PMRect selectionIconRect = selectionIconWidget->GetBBox();

			if (selectionIconRect.PointIn(mouseLocation) && selectionIconWidget->IsVisible())
			{
				if (selectionIconWidget->GetRsrcID() == kMSOStateIsSelectedIconRsrcID)
					str = "$$$/Tip/MSOPanel/MSOStateIsSelected";
				else
					str = "$$$/Tip/MSOPanel/MSOStateContentIsSelected";
			}
			else
			{
				InterfacePtr<IPanelControlData> panelPData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
				IControlView *msoSelectionIconWidget = panelPData ? panelPData->FindWidget(kMSOSelectionIconWidgetID) : nil;
				if (msoSelectionIconWidget && 
					msoSelectionIconWidget->IsVisible() && 
					msoSelectionIconWidget->GetRsrcID() == kMSOIsSelectedIconRsrcID)
				{
					if (view->IsHilited())
						str = "$$$/Tip/MSOPanel/MSOActiveStateRowMSOIsSelected";
					else
						str = "$$$/Tip/MSOPanel/MSOStateRowMSOIsSelected";
				}
				else if (!selectionIconWidget->IsVisible())
				{
					// Another state is selected
					str = "$$$/Tip/MSOPanel/MSOAnotherStateIsSelected";
				}
			}
		}
		else if (wID == kNewMSOStateButtonWidgetID)
		{
			InterfacePtr<IControlView> treeView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMSOPanelTreeWidgetID, IID_ICONTROLVIEW));
			InterfacePtr<ITreeViewHierarchyAdapter> treeViewAdapter(treeView, UseDefaultIID());
			int32 numStates = treeViewAdapter ? treeViewAdapter->GetNumChildren(treeViewAdapter->GetRootNode()) : 0;

			if (numStates > 0)
				str = "$$$/Tip/MSOPanel/NewState";
			else
				str = "$$$/Tip/MSOPanel/NewMSO";
		}
	}

	return str;
}  // end GetTipText()

