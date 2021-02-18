//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelPencilObserver.cpp $
//  
//  Owner: Brendan O'Shea
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
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IControlView.h"
#include "ILayerList.h"
#include "IBoolData.h"
#include "IDocumentLayer.h"
#include "LayerPanelUtils.h"
#include "IPanelControlData.h"

#include "CmdUtils.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "LayerID.h"
#include "UIDList.h"
#include "widgetid.h"
#include "CAlert.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class LayerPanelPencilObserver
//----------------------------------------------------------------------------------------

class LayerPanelPencilObserver : public CObserver
{
	public:
		LayerPanelPencilObserver(IPMUnknown *boss);
		virtual ~LayerPanelPencilObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);


};


CREATE_PMINTERFACE(LayerPanelPencilObserver, kLayerPanelPencilObserverImpl)

//----------------------------------------------------------------------------------------
// LayerPanelPencilObserver constructor 
//----------------------------------------------------------------------------------------

LayerPanelPencilObserver::LayerPanelPencilObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// LayerPanelPencilObserver::~LayerPanelPencilObserver: 
//----------------------------------------------------------------------------------------

LayerPanelPencilObserver::~LayerPanelPencilObserver()
{
}


//----------------------------------------------------------------------------------------
// LayerPanelPencilObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void LayerPanelPencilObserver::AutoAttach()
{
	// watch for changes in the state of this button (i.e. when it gets clicked on)
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// LayerPanelPencilObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void LayerPanelPencilObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// LayerPanelPencilObserver::Update: 
//----------------------------------------------------------------------------------------

void LayerPanelPencilObserver::Update(const ClassID& theChange, ISubject*, const PMIID& , void*)
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			InterfacePtr<const IDocumentLayer> layerClicked(LayerPanelUtils::QueryLayerFromPanelWidget(this));
			if(layerClicked)
			{
				InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kLockLayerCmdBoss));
				cmd->SetItemList(  UIDList(layerClicked));
				InterfacePtr<IBoolData> cmdData(cmd, IID_IBOOLDATA);
				cmdData->Set(!layerClicked->IsLocked());
				CmdUtils::ProcessCommand(cmd);
			}
		}
	}
}


