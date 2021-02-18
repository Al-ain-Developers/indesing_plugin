//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/loggerpreferences/LgrPrfEventTreeViewAdapter.cpp $
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

#include "IStringListData.h"
#include "ListTreeViewAdapter.h"
#include "IDiagnosticLog.h"
#include "IDiagnosticLogger.h"
#include "IDiagLogConfigManager.h"
#include "IDiagLoggerManager.h"
#include "StringNodeID.h"
#include "IEvent.h"
#include "LgrPrfID.h"

/**
 *  TreeViewAdapter.
	@ingroup loggerpreferences
 */
class LgrPrfEventTreeViewAdapter : public ListTreeViewAdapter
{
public:
	LgrPrfEventTreeViewAdapter(IPMUnknown* boss);
	
	virtual ~LgrPrfEventTreeViewAdapter()
	{}
	
	virtual int32	GetNumListItems() const;
	NodeID_rv GetRootNode() const;
	virtual NodeID_rv	GetNthListItem(const int32& nth) const;

};

CREATE_PMINTERFACE(LgrPrfEventTreeViewAdapter, kLgrPrfEventTreeViewAdapterImpl)

LgrPrfEventTreeViewAdapter::LgrPrfEventTreeViewAdapter(IPMUnknown* boss):ListTreeViewAdapter(boss)
{

}

/* GetNumListItems
 */
int32 LgrPrfEventTreeViewAdapter::GetNumListItems()const
{	
	return IEvent::kEndOfEventTypes-2;
}

/* GetRootNode
 */
NodeID_rv LgrPrfEventTreeViewAdapter::GetRootNode() const
{
	return StringNodeID::Create("Root");
}

/* GetNthListItem
 */
NodeID_rv LgrPrfEventTreeViewAdapter::GetNthListItem(const int32& nth) const
{
	PMString	eventName;
	do
	{
		InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iDiagnosticLog);
		if(!iDiagnosticLog) {
			break;
		}

		InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
		ASSERT(iConfigManager);
		if(!iConfigManager) {
			break;
		}

		eventName = iConfigManager->GetEventName((IEvent::EventType)(nth+1));
		eventName.SetTranslatable(kFalse);
	} while (false);
	
	return StringNodeID::Create(eventName);	
}
