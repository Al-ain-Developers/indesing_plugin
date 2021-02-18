//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerNameEditObserver.cpp $
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

#include "InLineEditObserver.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IDocument.h"
#include "IStringData.h"

#include "LayerID.h"
#include "LayerPanelID.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"
#include "Utils.h"
#include "UIDList.h"

class LayerNameEditObserver : public InLineEditObserver
{
	public:
		LayerNameEditObserver(IPMUnknown *boss);
		virtual ~LayerNameEditObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();			
		virtual void AutoDetach();
	
};


CREATE_PMINTERFACE(LayerNameEditObserver, kLayerNameEditObserverImpl)

LayerNameEditObserver::LayerNameEditObserver(IPMUnknown *boss) :
	InLineEditObserver(boss)
{
}

LayerNameEditObserver::~LayerNameEditObserver()
{
}

void LayerNameEditObserver::AutoAttach()
{
	InLineEditObserver::AutoAttach();

	InterfacePtr<ISubject> subjectList( this, UseDefaultIID() );
	if (subjectList)
		subjectList->AttachObserver(this, ITextControlData::kDefaultIID); 
}

void LayerNameEditObserver::AutoDetach()
{
	InterfacePtr<ISubject> subjectList( this, UseDefaultIID() );
	if (subjectList)
		subjectList->DetachObserver(this, ITextControlData::kDefaultIID);

	InLineEditObserver::AutoDetach();
}

void LayerNameEditObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (protocol == ITextControlData::kDefaultIID && theChange == kTextChangeStateMessage)
	{
		NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
		TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);

		InterfacePtr<const ITextControlData>	textData(theSubject, UseDefaultIID());
		UIDRef layerRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),layerTreeNode->GetUID());

		InterfacePtr<ICommand> nameCmd(CmdUtils::CreateCommand(kChangeLayerNameCmdBoss));
		if (nameCmd)
		{
			nameCmd->SetItemList(  UIDList(layerRef));
			InterfacePtr<IStringData> data(nameCmd, UseDefaultIID());
			PMString newString(textData->GetString());
			newString.SetTranslatable(kFalse);
			newString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
			data->Set(newString);
			CmdUtils::ProcessCommand(nameCmd);
		}
	}

	InLineEditObserver::Update(theChange, theSubject, protocol, changedBy);
}

