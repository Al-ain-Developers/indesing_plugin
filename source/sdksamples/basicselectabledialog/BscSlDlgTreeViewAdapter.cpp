//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgTreeViewAdapter.cpp $
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
#include "ISelectableDialogSwitcher.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWidgetParent.h"
#include "ListTreeViewAdapter.h"

#include "ListIndexNodeID.h"
#include "BscSlDlgID.h"

/** Implements tree view adapter. 
  
	@ingroup basicselectabledialog
	
*/
class BscSlDlgTreeViewAdapter : public ListTreeViewAdapter
{
public:
	BscSlDlgTreeViewAdapter(IPMUnknown *boss);
	~BscSlDlgTreeViewAdapter();

protected:
	virtual int32			GetNumListItems() const;
};

CREATE_PMINTERFACE(BscSlDlgTreeViewAdapter, kBscSlDlgTreeViewAdapterImpl)

BscSlDlgTreeViewAdapter::BscSlDlgTreeViewAdapter(IPMUnknown *boss) :
	ListTreeViewAdapter(boss)
{
}

BscSlDlgTreeViewAdapter::~BscSlDlgTreeViewAdapter()
{
}


int32 BscSlDlgTreeViewAdapter::GetNumListItems() const
{
	InterfacePtr<IWidgetParent> iWidgetParent(this, IID_IWIDGETPARENT);
    InterfacePtr<ISelectableDialogSwitcher> iSelectableDialog((ISelectableDialogSwitcher*)iWidgetParent->QueryParentFor(IID_ISELECTABLEDIALOGSWITCHER));
	int32 numDialogPanels = iSelectableDialog->GetNumDialogPanels();
	return numDialogPanels;
}

