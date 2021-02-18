//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgTreeViewWidgetMgr.cpp $
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
#include "CTreeViewWidgetMgr.h"

#include "ITextControlData.h"
#include "IWidgetParent.h"
#include "ISelectableDialogSwitcher.h"

#include "ListIndexNodeID.h"
#include "BscSlDlgID.h"

/** Implements tree view widget manager. 
  
	@ingroup basicselectabledialog
	
*/

class BscSlDlgTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	BscSlDlgTreeViewWidgetMgr(IPMUnknown *boss);

	virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const;
	virtual void	RegisterStyles();
};

CREATE_PMINTERFACE(BscSlDlgTreeViewWidgetMgr, kBscSlDlgTreeViewWidgetMgrImpl)

BscSlDlgTreeViewWidgetMgr::BscSlDlgTreeViewWidgetMgr(IPMUnknown *boss) :
	CTreeViewWidgetMgr(boss, kList)
{
}

bool16 BscSlDlgTreeViewWidgetMgr::ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const
{
	TreeNodePtr<ListIndexNodeID>	myNode(node);
	ASSERT(myNode != nil);

	if (myNode)
	{
		int32 nodeIndex = myNode->GetIndex();
		InterfacePtr<IWidgetParent> iWidgetParent(this, IID_IWIDGETPARENT);
		InterfacePtr<ISelectableDialogSwitcher> iSelectableDialog((ISelectableDialogSwitcher*)iWidgetParent->QueryParentFor(IID_ISELECTABLEDIALOGSWITCHER));
		WidgetID nthPanelWidgetID = iSelectableDialog->GetPanelWidgetID(nodeIndex);
		if (nthPanelWidgetID != kInvalidWidgetID)
		{
			// Get panel name.
			IControlView* nthPanelView = iSelectableDialog->GetDialogPanel(nthPanelWidgetID);
			InterfacePtr<ITextControlData> iPanelName(nthPanelView, IID_ITEXTCONTROLDATA);
			PMString panelName = iPanelName->GetString();
			panelName.Translate();
			SetNodeName( widgetList, panelName, kBscSlDlgTreeNodeNameWidgetID );
		}
 	}

	return kTrue;
}

void BscSlDlgTreeViewWidgetMgr::RegisterStyles()
{
	RegisterStyleWidget(kBscSlDlgTreeNodeTreeStyle, kBscSlDlgTreeNodeRsrcID, kBscSlDlgPluginID);
}
