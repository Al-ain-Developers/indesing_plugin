//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsTreeViewMgr.cpp $
//  
//  Owner: Reena Agrawal
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

// ----- Interface Includes -----

#include "IFormFieldSuite.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CoreResTypes.h"
#include "CTreeViewWidgetMgr.h"
#include "FormFieldUIUtils.h"
#include "IntNodeID.h"
#include "LocaleSetting.h"

// ----- ID.h files -----
#include "FormFieldUIDefs.h"
#include "FormFieldUIID.h"

//========================================================================================
// CLASS ListItemsTreeViewMgr
//========================================================================================

class ListItemsTreeViewMgr : public CTreeViewWidgetMgr
{
public:
	typedef CTreeViewWidgetMgr	Inherited;

	ListItemsTreeViewMgr(IPMUnknown *boss);
	~ListItemsTreeViewMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	bool16				ApplyNodeIDToWidget(const NodeID& node, IControlView* widget, int32 message) const;
	virtual WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
};

CREATE_PMINTERFACE(ListItemsTreeViewMgr, kListItemsTreeViewMgrImpl)

//----------------------------------------------------------------------------------------
// ListItemsTreeViewMgr constructor
//----------------------------------------------------------------------------------------

ListItemsTreeViewMgr::ListItemsTreeViewMgr(IPMUnknown *boss) 
	: Inherited(boss, kList)
{
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewMgr::~ListItemsTreeViewMgr 
//----------------------------------------------------------------------------------------

ListItemsTreeViewMgr::~ListItemsTreeViewMgr()
{
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------

bool16 ListItemsTreeViewMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{
	// Call base class for hilite selection
	Inherited::	ApplyHighlightToWidget(node, widget);

	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	if (iFormFieldSuite &&
		(iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss)))
	{
		Form::ChoiceList choiceList;
		iFormFieldSuite->GetChoiceList(choiceList);

		TreeNodePtr<const IntNodeID> treeNode(node);
		PMString choiceStr;
		if (treeNode->Get() < choiceList.size())
			choiceStr = choiceList[treeNode->Get()];

		InterfacePtr<ITextControlData> itemOption((ITextControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget,
				kItemOptionWidgetId, IID_ITEXTCONTROLDATA));
		itemOption->SetString(choiceStr, kFalse, kFalse);
	}

	return kTrue;
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------

IControlView* ListItemsTreeViewMgr::CreateWidgetForNode(const NodeID& node) const
{
	return (IControlView*)::CreateObject(::GetDataBase(this),
				RsrcSpec(LocaleSetting::GetLocale(), kFormFieldUIPluginID, kViewRsrcType, 
				kListItemsNodeWidgetRsrcID), IID_ICONTROLVIEW);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------
 
WidgetID ListItemsTreeViewMgr::GetWidgetTypeForNode(const NodeID& node) const
{
	return kListItemsNodeWidgetId;
}
