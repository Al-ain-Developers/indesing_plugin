//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgTreeViewDlgSwitcher.cpp $
//  
//  Owner: Vikram Sethi
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

#include "IPanelControlData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "IWidgetParent.h"
#include "ITextControlData.h"

#include "CSelectableDialogSwitcher.h"
#include "ListIndexNodeID.h"
#include "BscSlDlgID.h"

/** Implements dialog switcher. 
  
	@ingroup basicselectabledialog
	
*/

class BscSlDlgTreeViewDlgSwitcher : public CSelectableDialogSwitcher
{
public:
	BscSlDlgTreeViewDlgSwitcher(IPMUnknown *boss);
	virtual	~BscSlDlgTreeViewDlgSwitcher();

protected:
	virtual void		LoadDialogPanels();
	virtual void		SelectionWidgetAddString(const PMString& newString, int32 at = IStringListControlData::kEnd, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual void		SelectionWidgetClear(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual PMString	SelectionWidgetGetString(int32 index) const;
	virtual int32		SelectionWidgetLength() const;
	virtual void		SelectionWidgetRemoveString(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual void		SelectionWidgetSelect(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);	

private:
	int32 fNumPanelsAdded;	// indicates that how many panels has been added into fDialogPanelList.
};

CREATE_PERSIST_PMINTERFACE(BscSlDlgTreeViewDlgSwitcher, kBscSlDlgTreeViewDlgSwitcherImpl)

BscSlDlgTreeViewDlgSwitcher::BscSlDlgTreeViewDlgSwitcher(IPMUnknown *boss) :
	CSelectableDialogSwitcher(boss),
	fNumPanelsAdded(0)
{
}

BscSlDlgTreeViewDlgSwitcher::~BscSlDlgTreeViewDlgSwitcher()
{
}

void BscSlDlgTreeViewDlgSwitcher::LoadDialogPanels()
{
	CSelectableDialogSwitcher::LoadDialogPanels();

	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* treeView = iPanelControlData->FindWidget( kSelectDialogSelectionWidgetID );

	InterfacePtr<ITreeViewMgr>	iTreeMgr(treeView, UseDefaultIID());
	iTreeMgr->ChangeRoot();
}

PMString BscSlDlgTreeViewDlgSwitcher::SelectionWidgetGetString(int32 index) const
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* treeView = iPanelControlData->FindWidget( kSelectDialogSelectionWidgetID );
	InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewAdapter(treeView, UseDefaultIID());	
	
	NodeID rootNode = iTreeViewAdapter->GetRootNode();
	NodeID nodeRV = iTreeViewAdapter->GetNthChild(rootNode, index);

	TreeNodePtr<ListIndexNodeID> myNode(nodeRV);
	int32 nth  = myNode->GetIndex();
	//I assume nth == index
	ASSERT_MSG(nth == index, "this is not expected.");

	BscSlDlgTreeViewDlgSwitcher* nonConstThis = (BscSlDlgTreeViewDlgSwitcher*)this;
	WidgetID nthPanelWidgetID = nonConstThis->GetPanelWidgetID(nth);
	PMString panelName;
	if (nthPanelWidgetID != kInvalidWidgetID)
	{
		// Get panel name.
		IControlView* nthPanelView = nonConstThis->GetDialogPanel(nthPanelWidgetID);
		InterfacePtr<ITextControlData> iPanelName(nthPanelView, IID_ITEXTCONTROLDATA);
		panelName = iPanelName->GetString();
	}
	panelName.Translate();

	return panelName;
}

void BscSlDlgTreeViewDlgSwitcher::SelectionWidgetSelect(int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* treeView = iPanelControlData->FindWidget( kSelectDialogSelectionWidgetID );
	InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewAdapter(treeView, UseDefaultIID());	
	
	NodeID rootNode = iTreeViewAdapter->GetRootNode();
	NodeID nodeRV = iTreeViewAdapter->GetNthChild(rootNode, index);

	InterfacePtr<ITreeViewController> iTreeViewController(treeView, UseDefaultIID());	
	// Make sure nothing else is selected or we won't be able to select this one
	iTreeViewController->DeselectAll(notifyOfChange);
	iTreeViewController->Select(nodeRV, notifyOfChange);	
}

void BscSlDlgTreeViewDlgSwitcher::SelectionWidgetAddString(const PMString& newString, int32 at, bool16 invalidate, bool16 notifyOfChange)
{
	++fNumPanelsAdded;
}

void BscSlDlgTreeViewDlgSwitcher::SelectionWidgetClear(bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* treeView = iPanelControlData->FindWidget( kSelectDialogSelectionWidgetID );

	InterfacePtr<ITreeViewMgr>	iTreeMgr(treeView, UseDefaultIID());
	iTreeMgr->ClearTree(kTrue);
	iTreeMgr->ChangeRoot();
}

int32 BscSlDlgTreeViewDlgSwitcher::SelectionWidgetLength() const
{   
	return fNumPanelsAdded;
}

void BscSlDlgTreeViewDlgSwitcher::SelectionWidgetRemoveString(int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	--fNumPanelsAdded;
}

