//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizTreeViewWidgetMgr.cpp $
//  
//  Owner: Danielle Darling
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

#include "IControlView.h"
#include "IInLineEditController.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"

#include "CTreeViewWidgetMgr.h"
#include "StringNodeID.h"
#include "DCLSizID.h"


/**
 *  Tree view manager
	@ingroup detailcontrollistsize
 */
class DCLSizTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	DCLSizTreeViewWidgetMgr(IPMUnknown *boss);
	virtual ~DCLSizTreeViewWidgetMgr()
	{}
    
    virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const;

    void RegisterStyles()
    {
        RegisterStyleWidget(kLargePaletteRowsTreeStyle, kDCLSizListElementRsrcID, kDCLSizPluginID);
        RegisterStyleWidget(kSmallPaletteRowsTreeStyle, kDCLSizSmallListElementRsrcID, kDCLSizPluginID);
    }
};


CREATE_PMINTERFACE(DCLSizTreeViewWidgetMgr, kDCLSizTreeViewWidgetMgrImpl)

DCLSizTreeViewWidgetMgr::DCLSizTreeViewWidgetMgr(IPMUnknown *boss) :
CTreeViewWidgetMgr(boss, kList)
{
}



bool16 DCLSizTreeViewWidgetMgr::ApplyDataToWidget(const NodeID& node, 
                                            IPanelControlData* widgetList, 
                                            int32 message) const
{
	do
	{
		TreeNodePtr<StringNodeID> nodeID(node);
		PMString listName = nodeID->GetString();
		listName.Translate();
		SetNodeName( widgetList, listName, kDCLSizTextWidgetID );	      
	} while (false);

	return kTrue;
}

