//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/loggerpreferences/LgrPrfEventTreeViewWidgetMgr.cpp $
//  
//  Owner: InDesign Developer Technologies
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
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPluginHeaders.h"

#include "IControlView.h"
#include "IInLineEditController.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"

#include "CTreeViewWidgetMgr.h"
#include "StringNodeID.h"
#include "LgrPrfID.h"


/**
 *  Tree view manager
	@ingroup loggerpreferences
 */
class LgrPrfEventTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	LgrPrfEventTreeViewWidgetMgr(IPMUnknown *boss);
	virtual ~LgrPrfEventTreeViewWidgetMgr()
	{}
    
    virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const;

    void RegisterStyles()
    {
        RegisterStyleWidget(kLargePaletteRowsTreeStyle, kLgrPrfEventListElementRsrcID, kLgrPrfPluginID);
    }
};


CREATE_PMINTERFACE(LgrPrfEventTreeViewWidgetMgr, kLgrPrfEventTreeViewWidgetMgrImpl)

LgrPrfEventTreeViewWidgetMgr::LgrPrfEventTreeViewWidgetMgr(IPMUnknown *boss) :
CTreeViewWidgetMgr(boss, kList)
{
}


/* ApplyDataToWidget
 */
bool16 LgrPrfEventTreeViewWidgetMgr::ApplyDataToWidget(const NodeID& node, 
                                            IPanelControlData* widgetList, 
                                            int32 message) const
{
	do
	{
		TreeNodePtr<StringNodeID> nodeID(node);
		PMString listName = nodeID->GetString();
		listName.Translate();
		SetNodeName( widgetList, listName, kLgrPrfEventTextWidgetID );	      
	} while (false);

	return kTrue;
}

