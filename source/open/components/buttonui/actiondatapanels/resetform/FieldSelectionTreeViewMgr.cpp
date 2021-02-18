//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/resetform/FieldSelectionTreeViewMgr.cpp $
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
#include "IFieldSelectionTreeViewAdptr.h"
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
// CLASS FieldSelectionTreeViewMgr
//========================================================================================

class FieldSelectionTreeViewMgr : public CTreeViewWidgetMgr
{
public:
	FieldSelectionTreeViewMgr(IPMUnknown *boss);
	~FieldSelectionTreeViewMgr();

	virtual void 				ReadWrite(IPMStream* s, ImplementationID prop);
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
	virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message) const;

private:
	RsrcID	fViewRsrcID;
};

CREATE_PERSIST_PMINTERFACE(FieldSelectionTreeViewMgr, kFieldSelectionTreeViewMgrImpl)

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr constructor
//----------------------------------------------------------------------------------------

FieldSelectionTreeViewMgr::FieldSelectionTreeViewMgr(IPMUnknown *boss) 
	: CTreeViewWidgetMgr(boss)
{
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr::~FieldSelectionTreeViewMgr 
//----------------------------------------------------------------------------------------

FieldSelectionTreeViewMgr::~FieldSelectionTreeViewMgr()
{
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr::ReadWrite
//----------------------------------------------------------------------------------------

void FieldSelectionTreeViewMgr::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferInt32((int32&) fViewRsrcID);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------

bool16 FieldSelectionTreeViewMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{	
	CTreeViewWidgetMgr::ApplyNodeIDToWidget( node, widget );
	
	TreeNodePtr<IntNodeID> intNode(node);

	InterfacePtr<IFieldSelectionTreeViewAdapter> viewAdapter(this, UseDefaultIID());

	InterfacePtr<ITextControlData> fieldTitle((ITextControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kSHFieldTitleWidgetId, IID_ITEXTCONTROLDATA));
	fieldTitle->SetString(viewAdapter->GetFieldName(node), kFalse, kFalse);

	InterfacePtr<ITriStateControlData> selectedButton((ITriStateControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kSelectedOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA));

	selectedButton->Deselect(kFalse, kFalse);
	
	if (viewAdapter->GetSelected(node))
		selectedButton->Select(kFalse, kFalse);

	return kTrue;
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------

IControlView* FieldSelectionTreeViewMgr::CreateWidgetForNode(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);

	RsrcSpec rsrcSpec(LocaleSetting::GetLocale(), kBehaviorUIPluginID, kViewRsrcType, fViewRsrcID);
	IControlView* nodeView = (IControlView*) ::CreateObject(::GetDataBase(this), rsrcSpec, IID_ICONTROLVIEW);
	
	return nodeView;
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------

WidgetID FieldSelectionTreeViewMgr::GetWidgetTypeForNode(const NodeID& node) const
{
	return kFieldSelectionNodeWidgetId;
}
