//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchTreeViewWidgetMgr.cpp $
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
#include "CTreeViewWidgetMgr.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "ILnkWtchCache.h"

#include "ListIndexNodeID.h"
#include "LnkWtchID.h"

/** Implements tree view widget manager. 
  
	@ingroup linkwatcher
	
*/

class LnkWtchTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	LnkWtchTreeViewWidgetMgr(IPMUnknown *boss);

	virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const;
	virtual void	RegisterStyles();
};

CREATE_PMINTERFACE(LnkWtchTreeViewWidgetMgr, kLnkWtchTreeViewWidgetMgrImpl)

LnkWtchTreeViewWidgetMgr::LnkWtchTreeViewWidgetMgr(IPMUnknown *boss) :
	CTreeViewWidgetMgr(boss, kList)
{
}

bool16 LnkWtchTreeViewWidgetMgr::ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const
{
	TreeNodePtr<ListIndexNodeID>	myNode(node);
	ASSERT(myNode != nil);

	if (myNode)
	{
		int32 nodeIndex = myNode->GetIndex();
		IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
		InterfacePtr<ILnkWtchCache> cache(document, UseDefaultIID());
		const ILnkWtchCache::Entries& entries = cache->Get();
		ILnkWtchCache::Entries::const_iterator iter;
		int32 count = 0;
		for (iter = entries.begin(); iter < entries.end(); iter++)
		{
			if (iter->fRemoved == kFalse)
			{
				if (count == nodeIndex)
				{
					PMString name = cache->GetName(*iter);
					name.SetTranslatable(kFalse);
					SetNodeName( widgetList, name, kLnkWtchTextWidgetID );
					break;
				}
				count++;
			}
		}
 	}

	return kTrue;
}

void LnkWtchTreeViewWidgetMgr::RegisterStyles()
{
	RegisterStyleWidget(kLargePaletteRowsTreeStyle, kLnkWtchListElementRsrcID, kLnkWtchPluginID);
}
