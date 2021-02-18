//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizTreeViewAdapter.cpp $
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

#include "IStringListData.h"
#include "ListTreeViewAdapter.h"
#include "StringNodeID.h"
#include "DCLSizID.h"

/**
 *  TreeViewAdapter.
	@ingroup detailcontrollistsize
 */
class DCLSizTreeViewAdapter : public ListTreeViewAdapter
{
public:
	DCLSizTreeViewAdapter(IPMUnknown* boss);
	
	virtual ~DCLSizTreeViewAdapter()
	{}
	
	virtual int32	GetNumListItems() const;
	NodeID_rv GetRootNode() const;
	virtual NodeID_rv	GetNthListItem(const int32& nth) const;

};

CREATE_PMINTERFACE(DCLSizTreeViewAdapter, kDCLSizTreeViewAdapterImpl)

DCLSizTreeViewAdapter::DCLSizTreeViewAdapter(IPMUnknown* boss):ListTreeViewAdapter(boss)
{

}
int32 DCLSizTreeViewAdapter::GetNumListItems()const
{	
	return 12;
}

NodeID_rv DCLSizTreeViewAdapter::GetRootNode() const
{
	return StringNodeID::Create("Root");
}

NodeID_rv DCLSizTreeViewAdapter::GetNthListItem(const int32& nth) const
{
	PMString name(kDCLSizItemBaseKey);
	name.AppendNumber(nth+1);
	return StringNodeID::Create(name);	
}
