//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTreeViewWidgetMgr.cpp $
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

// Interface includes:
#include "IActiveContext.h"
#include "IConditionTag.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWorkspace.h"
#include "IUIDData.h"

// General includes:
#include "CTreeViewWidgetMgr.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "IconRsrcDefs.h"
#include "UIDList.h"
#include "UIDNodeID.h"

// Project includes:
#include "CusCondTxtUIID.h"
#include "CusCondTxtRezDefs.h"
#include "ICustomConditionTag.h"

/**
 *  Tree view manager
	@ingroup customconditionaltext
 */
class CusCondTxtTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	CusCondTxtTreeViewWidgetMgr(IPMUnknown *boss);
	virtual ~CusCondTxtTreeViewWidgetMgr() {}
	
	virtual bool16 ApplyNodeIDToWidget(const NodeID& node, IControlView* widget, int32) const;
	IControlView* CreateWidgetForNode(const NodeID& node) const;
	
};


CREATE_PMINTERFACE(CusCondTxtTreeViewWidgetMgr, kCusCondTxtUITreeViewWidgetMgrImpl)

/* Constructor
*/
CusCondTxtTreeViewWidgetMgr::CusCondTxtTreeViewWidgetMgr(IPMUnknown *boss) : CTreeViewWidgetMgr(boss, kList)
{
}

/* ApplyNodeIDToWidget
*/
bool16 CusCondTxtTreeViewWidgetMgr::ApplyNodeIDToWidget(const NodeID& node, IControlView* widget, int32) const
{
	do
	{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		IWorkspace *ws = context->GetContextWorkspace();
		if (ws == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}

		IDataBase* db = ::GetDataBase(ws);
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}

		TreeNodePtr<UIDNodeID>	uidNode(node);

		InterfacePtr<IPanelControlData>	widgetsChildren(widget, UseDefaultIID());
		if (widgetsChildren == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}

		InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());
		
		if (adapter && node == adapter->GetRootNode())
		{
			// Fill in the widget for the "[Unconditional]" item
			PMString unconditionalName("#ConditionTag_Unconditional", PMString::kTranslateDuringCall);
			SetNodeName(widgetsChildren, unconditionalName);
		}
		else 
		{
			// Normal condition node; fill in name and visiblity.
			InterfacePtr<IConditionTag> tag(db, uidNode->GetUID(), UseDefaultIID());
			if(tag == nil)
			{
				ASSERT_FAIL("IConditionTag is invalid");
				break;
			}

			// Name
			SetNodeName(widgetsChildren, tag->GetName());

			InterfacePtr<ICustomConditionTag> customConditionTag(tag, UseDefaultIID());
			if (customConditionTag == nil)
			{
				ASSERT_FAIL("ICustomConditionTag is invalid");
				break;
			}
			IControlView* printIcon = widgetsChildren->FindWidget(kConditionTagIsPrintedStateWidgetId);
			if (printIcon == nil)
			{
				ASSERT_FAIL("IControlView is invalid");
				break;
			}

			IControlView* idmlIcon = widgetsChildren->FindWidget(kConditionTagIsIdmlStateWidgetId);
			if (printIcon == nil)
			{
				ASSERT_FAIL("IControlView is invalid");
				break;
			}

			RsrcID printRsrcID = customConditionTag->IsPrintVisible() ? kIsPrintedIndicatorRsrcID : kNoIcon;
			RsrcID idmlRsrcID = customConditionTag->IsIdmlVisible() ? kIsIdmlIndicatorRsrcID : kNoIcon;

			if(printIcon->GetRsrcPluginID() != kCusCondTxtUIPluginID || printIcon->GetRsrcID() != printRsrcID)
			{
				printIcon->SetRsrcPluginID(kCusCondTxtUIPluginID);
				printIcon->SetRsrcID(printRsrcID);
				printIcon->Invalidate();
			}

			if(idmlIcon->GetRsrcPluginID() != kCusCondTxtUIPluginID || idmlIcon->GetRsrcID() != idmlRsrcID)
			{
				idmlIcon->SetRsrcPluginID(kCusCondTxtUIPluginID);
				idmlIcon->SetRsrcID(idmlRsrcID);
				idmlIcon->Invalidate();
			}
		}
			
	} while (false);

	return kTrue;
}

/* CreateWidgetForNode
*/
IControlView* CusCondTxtTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	return (IControlView*)::CreateObject(::GetDataBase(this),
				RsrcSpec(LocaleSetting::GetLocale(), kCusCondTxtUIPluginID, kViewRsrcType, 
				kCusCondTxtTreeNodeRsrcID),IID_ICONTROLVIEW);
}



