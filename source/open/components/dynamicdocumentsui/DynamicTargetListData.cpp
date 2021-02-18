//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/DynamicTargetListData.cpp $
//  
//  Owner: Yeming Liu
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
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IDynamicEventTimingMgr.h"
#include "IDynamicTargetListData.h"

// ----- Include files -----

#include "CPMUnknown.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class DynamicTargetListData : public CPMUnknown<IDynamicTargetListData>
{
	public:
		DynamicTargetListData(IPMUnknown* boss);
		virtual ~DynamicTargetListData() { }

		virtual void Append(IDynamicEventTimingMgr::DynamicTargetPtr const &target);
		virtual void GetDynamicTargetList(IDynamicEventTimingMgr::DynamicTargetList &targetList);

		virtual size_t size();
		virtual void Clear();

	private:
		IDynamicEventTimingMgr::DynamicTargetList fTargetDataList;
};

CREATE_PMINTERFACE(DynamicTargetListData, kDynamicTargetListDataImpl) 

DynamicTargetListData::DynamicTargetListData(IPMUnknown* boss) : 
	CPMUnknown<IDynamicTargetListData>(boss) 
{ 
	fTargetDataList.clear();
}

void DynamicTargetListData::Append(IDynamicEventTimingMgr::DynamicTargetPtr const &target)
{
	fTargetDataList.push_back(target);
}

void DynamicTargetListData::GetDynamicTargetList(IDynamicEventTimingMgr::DynamicTargetList &targetList)
{
	targetList = fTargetDataList;
}

size_t DynamicTargetListData::size()
{
	return fTargetDataList.size();
}

void DynamicTargetListData::Clear()
{
	return fTargetDataList.clear();
}