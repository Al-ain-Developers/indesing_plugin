//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKITreeViewHierarchyAdapter.cpp $
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
#include "TKIID.h"
#include "ITKIStringListData.h"
#include "ListTreeViewAdapter.h"
#include "TKITreeNodeID.h"

class TKITreeViewHierarchyAdapter : public ListTreeViewAdapter
{
public:
	TKITreeViewHierarchyAdapter(IPMUnknown* boss);
	virtual	~TKITreeViewHierarchyAdapter(){}
	virtual int32 GetNumListItems() const;
	NodeID_rv GetRootNode() const;
	virtual NodeID_rv GetNthListItem(const int32& nth) const;
};	

CREATE_PMINTERFACE(TKITreeViewHierarchyAdapter, kTKITreeViewHierarchyAdapterImpl)

TKITreeViewHierarchyAdapter::TKITreeViewHierarchyAdapter(IPMUnknown* boss):ListTreeViewAdapter(boss)
{
}

NodeID_rv TKITreeViewHierarchyAdapter::GetRootNode() const
{
	return TKITreeNodeID::Create();
}

NodeID_rv TKITreeViewHierarchyAdapter::GetNthListItem(const int32& nth) const
{
	InterfacePtr<ITKIStringListData> iListData(this, IID_ITKISTRINGLISTDATA);
	return iListData->GetStringList()[nth];
}

int32 TKITreeViewHierarchyAdapter::GetNumListItems()const
{	
	InterfacePtr<ITKIStringListData> iListData(this, IID_ITKISTRINGLISTDATA);
	return iListData->GetStringList().size();
}