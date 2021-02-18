//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUITVWidgetMgr.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "IActiveContext.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"


#include "CTreeViewWidgetMgr.h"
#include "PstLstUINodeID.h"
#include "PstLstUIID.h"


/** Tree view widget manager
	@ingroup persistentlist
	
*/
class PstLstUITVWidgetMgr : public CTreeViewWidgetMgr
{
public:
	PstLstUITVWidgetMgr(IPMUnknown *boss) : CTreeViewWidgetMgr(boss, kHierarchical)
	{}
	
	virtual ~PstLstUITVWidgetMgr()
	{}
	
    virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const;

	virtual	PMReal	GetIndentForNode(const NodeID& node) const {return 16;}

	void RegisterStyles()
    {
        RegisterStyleWidget(kLargePaletteRowsTreeStyle, kPstLstUIListElementRsrcID, kPstLstUIPluginID);
    }
};


CREATE_PMINTERFACE(PstLstUITVWidgetMgr, kPstLstUITVWidgetMgrImpl)


bool16 PstLstUITVWidgetMgr::ApplyDataToWidget(const NodeID& node, 
                                                         IPanelControlData* widgetList, 
                                                         int32 message) const
{
    TreeNodePtr<PstLstUINodeID> nodeID(node);
	int32 dataType = nodeID->GetDataType();
	UID uid = nodeID->GetUID();
	char* buf = new char[11];
	sprintf(buf, "0x%x", uid.Get());
	PMString uidString(buf);
	delete [] buf;
    		
    // Now show or hide the Expander widget
    IControlView* expander = widgetList->FindWidget(kTreeNodeExpanderWidgetID);
    if (expander)
    {
		expander->ShowView(dataType == PstLstUINodeID::kPageItemType);
    }
		
	PMString display(uidString);
	if (dataType == PstLstUINodeID::kPersistentListType)
	{ //The node show uidString + description
		PMString description = nodeID->GetDataDescription();
		display = uidString + " " + description;
	}

	SetNodeName( widgetList, display, kPstLstUITextWidgetID );
    
	return kTrue;
}
