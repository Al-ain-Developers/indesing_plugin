//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKITreeViewWidgetMgr.cpp $
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
#include "IControlView.h"
#include "CTreeViewWidgetMgr.h"
#include "CreateObject.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysControlIds.h"
#include "TKIID.h"
#include "TKITreeNodeID.h"
#include "ITextControlData.h"

class TKITreeViewWidgetMgr: public CTreeViewWidgetMgr
{
public:
	TKITreeViewWidgetMgr(IPMUnknown* boss);
	virtual ~TKITreeViewWidgetMgr() {}
	virtual bool16 ApplyDataToWidget(const NodeID& node, IPanelControlData* widgetList, int32 message = 0) const;
	virtual void RegisterStyles();
	virtual IControlView* CreateWidgetForNode(const NodeID& node) const;
};	

CREATE_PMINTERFACE(TKITreeViewWidgetMgr, kTKITreeViewWidgetMgrImpl)

TKITreeViewWidgetMgr::TKITreeViewWidgetMgr(IPMUnknown* boss) : CTreeViewWidgetMgr(boss, kList)
{
}

void TKITreeViewWidgetMgr::RegisterStyles()
{
	RegisterStyleWidget(kLargePaletteRowsTreeStyle, kTKITreeViewNodeWidgetRsrcID, kTKIPluginID);
}

/* 
 * Sets the displayed text label for a tree node by getting 
 * the data out of the tree node and applying it to the UI 
 * widget for the node.
 */
bool16 TKITreeViewWidgetMgr::ApplyDataToWidget(const NodeID& node, IPanelControlData* widgetList, int32 message) const
{
	do
	{
		TreeNodePtr<TKITreeNodeID> nodeID(node);
		PMString listName = nodeID->GetString();
	      
		IControlView* nameView = widgetList->FindWidget(kTKITreeNodeTextWidgetID);
	        
		InterfacePtr<ITextControlData> textControlData(nameView, UseDefaultIID());
		ASSERT(textControlData);
		if (textControlData == nil) 
		{
			break;
		}
		textControlData->SetString(listName);

	} while (false);

	return kTrue;
}

IControlView* TKITreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	IControlView* retval = (IControlView*) ::CreateObject(
		::GetDataBase(this),
		RsrcSpec(LocaleSetting::GetLocale(), 
		kTKIPluginID, 
		kViewRsrcType, 
		kTKITreeViewNodeWidgetRsrcID),
		IID_ICONTROLVIEW);

	return retval;
}