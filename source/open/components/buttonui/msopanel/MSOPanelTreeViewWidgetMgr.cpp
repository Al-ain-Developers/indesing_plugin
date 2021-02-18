//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewWidgetMgr.cpp $
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

#include "IAppearanceSuite.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "IPanelDetailController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CoreResTypes.h"
#include "CTreeViewWidgetMgr.h"
#include "FormFieldUIDefs.h"
#include "LocaleSetting.h"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	MSOPanelTreeViewWidgetMgr(IPMUnknown *boss);
	~MSOPanelTreeViewWidgetMgr();
	
	virtual void				RegisterStyles();
	virtual bool16				ApplyDataToWidget(const NodeID& node, IPanelControlData* widgetsChildren, int32 message) const;
	virtual PMReal				GetNodeWidgetHeight(const NodeID& node) const ;
};

// =============================================================================
// *** MSOPanelTreeViewWidgetMgr impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTreeViewWidgetMgr, kMSOPanelTreeViewWidgetMgrImpl)

MSOPanelTreeViewWidgetMgr::MSOPanelTreeViewWidgetMgr(IPMUnknown *boss) : CTreeViewWidgetMgr(boss, kList)
{
	// Register styles now since detail controller sets the style and that
	// bypasses the lazy register.
	RegisterStyles();
} // end constructor

MSOPanelTreeViewWidgetMgr::~MSOPanelTreeViewWidgetMgr()
{
} // end destructor

// -----------------------------------------------------------------------------

void MSOPanelTreeViewWidgetMgr::RegisterStyles()
{
	InterfacePtr<const IWidgetParent> wp(this, UseDefaultIID());
	InterfacePtr<IPanelDetailController> detailController((IPanelDetailController*)wp->QueryParentFor(IID_IPANELDETAILCONTROLLER));
	if (detailController)
	{

		// Plus one because detail level is 0-based and tree node style is 1-based
		switch (detailController->GetDetailLevel()+1)
		{
			case kSmallSize:
				{
				RegisterStyleWidget(kSmallSize, kMSOPanelTreeViewSmallNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kMediumSize, kMSOPanelTreeViewNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kLargeSize, kMSOPanelTreeViewLargeNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kExtraLargeSize, kMSOPanelTreeViewExtraLargeNodeRsrcID, kFormFieldUIPluginID);
				}
				break;
			case kLargeSize:
				{
				RegisterStyleWidget(kLargeSize, kMSOPanelTreeViewLargeNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kSmallSize, kMSOPanelTreeViewSmallNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kMediumSize, kMSOPanelTreeViewNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kExtraLargeSize, kMSOPanelTreeViewExtraLargeNodeRsrcID, kFormFieldUIPluginID);
				}
				break;
			case kExtraLargeSize:
				{
				RegisterStyleWidget(kExtraLargeSize, kMSOPanelTreeViewExtraLargeNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kSmallSize, kMSOPanelTreeViewSmallNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kMediumSize, kMSOPanelTreeViewNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kLargeSize, kMSOPanelTreeViewLargeNodeRsrcID, kFormFieldUIPluginID);
				}
				break;
			case kMediumSize:
			default:
				{
				RegisterStyleWidget(kMediumSize, kMSOPanelTreeViewNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kSmallSize, kMSOPanelTreeViewSmallNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kLargeSize, kMSOPanelTreeViewLargeNodeRsrcID, kFormFieldUIPluginID);
				RegisterStyleWidget(kExtraLargeSize, kMSOPanelTreeViewExtraLargeNodeRsrcID, kFormFieldUIPluginID);
				}
				break;
		}
	}
	else
	{
		RegisterStyleWidget(kMediumSize, kMSOPanelTreeViewNodeRsrcID, kFormFieldUIPluginID);
		RegisterStyleWidget(kSmallSize, kMSOPanelTreeViewSmallNodeRsrcID, kFormFieldUIPluginID);
		RegisterStyleWidget(kLargeSize, kMSOPanelTreeViewLargeNodeRsrcID, kFormFieldUIPluginID);
		RegisterStyleWidget(kExtraLargeSize, kMSOPanelTreeViewExtraLargeNodeRsrcID, kFormFieldUIPluginID);
	}
} // end RegisterStyles()

// -----------------------------------------------------------------------------

PMReal MSOPanelTreeViewWidgetMgr::GetNodeWidgetHeight(const NodeID& node) const 
{ 
#pragma unused(node)
	PMReal h = kMSOStateMediumRowHeight;

	InterfacePtr<const IWidgetParent> wp(this, UseDefaultIID());
	InterfacePtr<IPanelDetailController> detailController((IPanelDetailController*)wp->QueryParentFor(IID_IPANELDETAILCONTROLLER));
	if (detailController) 
	{
		// Plus one because detail level is 0-based and tree node style is 1-based
		switch (detailController->GetDetailLevel()+1)
		{
			case kSmallSize:
				h = kMSOStateSmallRowHeight;
				break;
			case kLargeSize:
				h = kMSOStateLargeRowHeight;
				break;
			case kExtraLargeSize:
				h = kMSOStateExtraLargeRowHeight;
				break;
		}
	}

	return h;
} // end GetNodeWidgetHeight()

// -----------------------------------------------------------------------------

bool16 MSOPanelTreeViewWidgetMgr::ApplyDataToWidget(const NodeID& node, IPanelControlData* widgetsChildren, int32) const
{	
	// Set the node name and visibility icon.
	TreeNodePtr<MSOStateNodeID>	msoStateNode(node);
	ASSERT(msoStateNode != nil);

	if (msoStateNode)
	{
		IDataBase *db = msoStateNode->GetDataBase();

		InterfacePtr<IFormFieldSuite> formFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (appearanceSuite && formFieldSuite && formFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
		{
			// Name
			PMString stateName(appearanceSuite->GetStateName(msoStateNode->GetAppearance()));
			stateName.Translate();
			SetNodeName(widgetsChildren, stateName);

			// Selection icon
			IControlView* selectionIconView = widgetsChildren->FindWidget(kMSOStateSelectionIconWidgetID);
			if (selectionIconView)
			{
				if (appearanceSuite->SelectionHasContentInState(msoStateNode->GetAppearance()))
				{
					// Set appropraite RSRC
					if (appearanceSuite->IsActiveStateOfAppearanceItemOfTypeSelected(kMultiStateObjectItemBoss))
						selectionIconView->SetRsrcID(kMSOStateIsSelectedIconRsrcID);
					else
						selectionIconView->SetRsrcID(kMSOStateContentIsSelectedIconRsrcID);
					selectionIconView->ShowView();
				}
				else
					selectionIconView->HideView();
			}
		}
	}

	return kTrue;
} // end ApplyDataToWidget()
