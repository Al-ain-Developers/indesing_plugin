//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPageItemPencilObserver.cpp $
//  
//  Owner: lance bushore
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

#include "CObserver.h"

#include "ISubject.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "ITreeNodeIDData.h"
#include "IDocument.h"
#include "IWidgetParent.h"
#include "IPageItemLockFacade.h"
#include "IIntData.h"

#include "LayerPanelID.h"
#include "UIDList.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"
#include "Utils.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class LayerPageItemPencilObserver
//----------------------------------------------------------------------------------------

class LayerPageItemPencilObserver : public CObserver
{
	public:
		LayerPageItemPencilObserver(IPMUnknown *boss);
		virtual ~LayerPageItemPencilObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);


};


CREATE_PMINTERFACE(LayerPageItemPencilObserver, kLayerPageItemPencilObserverImpl)


LayerPageItemPencilObserver::LayerPageItemPencilObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}



LayerPageItemPencilObserver::~LayerPageItemPencilObserver()
{
}


void LayerPageItemPencilObserver::AutoAttach()
{
	// watch for changes in the state of this button (i.e. when it gets clicked on)
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}


void LayerPageItemPencilObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

void LayerPageItemPencilObserver::Update(const ClassID& theChange, ISubject* , const PMIID& , void* )
{
	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
			if (frontDocDB == nil)
				return;

			NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
	
			UIDList itemUIDs(frontDocDB,uidNode->GetUID());
			if(Utils<Facade::IPageItemLockFacade>()->CanLock(itemUIDs))
			{
				Utils<Facade::IPageItemLockFacade>()->LockPageItems(itemUIDs);
			}
			else if(Utils<Facade::IPageItemLockFacade>()->CanUnlock(itemUIDs))
			{
				Utils<Facade::IPageItemLockFacade>()->UnlockPageItems(itemUIDs);
			}
		}
	}
}


