//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchTreeViewAdapter.cpp $
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

#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "ILnkWtchCache.h"
#include "ListTreeViewAdapter.h"

#include "ListIndexNodeID.h"
#include "LnkWtchID.h"

/** Implements tree view adapter. 
  
	@ingroup linkwatcher
	
*/
class LnkWtchTreeViewAdapter : public ListTreeViewAdapter
{
public:
	LnkWtchTreeViewAdapter(IPMUnknown *boss);
	~LnkWtchTreeViewAdapter();

protected:
	virtual int32			GetNumListItems() const;
};

CREATE_PMINTERFACE(LnkWtchTreeViewAdapter, kLnkWtchTreeViewAdapterImpl)

LnkWtchTreeViewAdapter::LnkWtchTreeViewAdapter(IPMUnknown *boss) :
	ListTreeViewAdapter(boss)
{
}

LnkWtchTreeViewAdapter::~LnkWtchTreeViewAdapter()
{
}


int32 LnkWtchTreeViewAdapter::GetNumListItems() const
{
	IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
	InterfacePtr<ILnkWtchCache> cache(document, UseDefaultIID());
	if (cache)
	{
		const ILnkWtchCache::Entries& entries = cache->Get();
		ILnkWtchCache::Entries::const_iterator iter;
		int32 count = 0;
		for (iter = entries.begin(); iter < entries.end(); iter++)
		{
			if (iter->fRemoved == kFalse)
			{
				count++;
			}
		}	
		
		return count;
	}
	else
		return 0;
}

