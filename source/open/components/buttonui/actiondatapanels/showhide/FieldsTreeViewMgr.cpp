//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/showhide/FieldsTreeViewMgr.cpp $
//  
//  Owner: Michael Burbidge
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

#include "IWidgetUtils.h"
#include "ITextControlData.h"
#include "IControlView.h"
#include "IFieldsTreeViewAdapter.h"
#include "ITriStateControlData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"
#include "CTreeViewWidgetMgr.h"
#include "IntNodeID.h"
#include "CreateObject.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "Utils.h"

//========================================================================================
// CLASS FieldsTreeViewMgr
//========================================================================================

class FieldsTreeViewMgr : public CTreeViewWidgetMgr
{
public:
	FieldsTreeViewMgr(IPMUnknown *boss);
	~FieldsTreeViewMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
	virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message) const;
};

CREATE_PMINTERFACE(FieldsTreeViewMgr, kFieldsTreeViewMgrImpl)

//----------------------------------------------------------------------------------------
// FieldsTreeViewMgr constructor
//----------------------------------------------------------------------------------------

FieldsTreeViewMgr::FieldsTreeViewMgr(IPMUnknown *boss) 
	: CTreeViewWidgetMgr(boss)
{
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewMgr::~FieldsTreeViewMgr 
//----------------------------------------------------------------------------------------

FieldsTreeViewMgr::~FieldsTreeViewMgr()
{
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------

bool16 FieldsTreeViewMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{	
	CTreeViewWidgetMgr::ApplyNodeIDToWidget( node, widget );
	
	TreeNodePtr<IntNodeID> intNode(node);

	InterfacePtr<IFieldsTreeViewAdapter> viewAdapter(this, UseDefaultIID());

	InterfacePtr<ITextControlData> fieldTitle((ITextControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kSHFieldTitleWidgetId, IID_ITEXTCONTROLDATA));
	fieldTitle->SetString(viewAdapter->GetFieldName(node), kFalse, kFalse);

	InterfacePtr<ITriStateControlData> showButton((ITriStateControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kSHShowOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA));
	
	if (viewAdapter->GetAction(node) == IShowHideFieldActionData::kHide)
		showButton->Deselect(kFalse, kFalse);
	else if (viewAdapter->GetAction(node) == IShowHideFieldActionData::kShow)
		showButton->Select(kFalse, kFalse);
	else
		showButton->SetUnknown(kFalse, kFalse);

	return kTrue;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------

IControlView* FieldsTreeViewMgr::CreateWidgetForNode(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);

	RsrcSpec rsrcSpec(LocaleSetting::GetLocale(), kBehaviorUIPluginID, kViewRsrcType, kFieldsTreeNodeWidgetRsrcID);
	IControlView* nodeView = (IControlView*) ::CreateObject(::GetDataBase(this), rsrcSpec, IID_ICONTROLVIEW);
	
	return nodeView;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------

WidgetID FieldsTreeViewMgr::GetWidgetTypeForNode(const NodeID& node) const
{
	return kSHFieldsNodeWidgetId;
}
