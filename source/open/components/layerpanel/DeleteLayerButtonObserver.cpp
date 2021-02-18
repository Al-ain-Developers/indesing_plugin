//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/DeleteLayerButtonObserver.cpp $
//  
//  Owner: Lonnie Millett
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

#include "ILayerList.h"
#include "IDocument.h"
#include "ISubject.h"
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocumentLayer.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"
#include "IPageItemScrapFacade.h"

#include "UIDList.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"
#include "EventUtilities.h"
#include "CmdUtils.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "widgetid.h"
#include "IPalettePanelUtils.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class DeleteLayerButtonObserver
//----------------------------------------------------------------------------------------

class DeleteLayerButtonObserver : public CObserver
{
	public:
		DeleteLayerButtonObserver(IPMUnknown *boss);
		virtual ~DeleteLayerButtonObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	private:
		void UpdateButton();
};




CREATE_PMINTERFACE(DeleteLayerButtonObserver, kDeleteLayerButtonObserverImpl)

//----------------------------------------------------------------------------------------
// DeleteLayerButtonObserver constructor 
//----------------------------------------------------------------------------------------

DeleteLayerButtonObserver::DeleteLayerButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// DeleteLayerButtonObserver::~DeleteLayerButtonObserver: 
//----------------------------------------------------------------------------------------

DeleteLayerButtonObserver::~DeleteLayerButtonObserver()
{
}



void DeleteLayerButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget( this, kLayerPanelTreeWidgetID,IID_ISUBJECT ));
	if(treeSubject)
		treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);

	this->UpdateButton();
}

//----------------------------------------------------------------------------------------
// DeleteLayerButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void DeleteLayerButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget( this, kLayerPanelTreeWidgetID,IID_ISUBJECT ));
	if(treeSubject)
		treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
}


void DeleteLayerButtonObserver::Update(const ClassID& theChange, ISubject* , const PMIID& protocol , void* )
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage)
	{
		IDataBase* docDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (docDB != nil && data->IsSelected())
		{
			UIDList piList = LayerPanelUtils::GetPageItemsSelectedInPanel(this, docDB);
			if(piList.size())
			{
				Utils<Facade::IPageItemScrapFacade>()->DeletePageItems(piList);
			}
			else
			{
				bool16 optionKeyDown = ::IsOptionAltKeyPressed();
				InterfacePtr<ICommand> cmd(LayerPanelUtils::CreateDeleteLayersCmd(!optionKeyDown, this));
				if (cmd)
					CmdUtils::ProcessCommand(cmd);
			}
		}
	}
	else if(protocol == IID_ITREEVIEWCONTROLLER && theChange == kListSelectionChangedMessage )
	{
		this->UpdateButton();
	}
}

//----------------------------------------------------------------------------------------
// DeleteLayerButtonObserver::UpdateButton: 
//----------------------------------------------------------------------------------------
void DeleteLayerButtonObserver::UpdateButton()
{
	InterfacePtr<IControlView> pView( this, IID_ICONTROLVIEW ) ;
	bool16 canDelete = kFalse;
	IDataBase* docDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	UIDList piList = LayerPanelUtils::GetPageItemsSelectedInPanel(this, docDB);
	if(piList.size())
	{
		canDelete = Utils<Facade::IPageItemScrapFacade>()->CanDeletePageItems(piList);
	}
	else
	{
		// Get widgetparent for the layer panel itself
		InterfacePtr<IPanelControlData> layerPanelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
		canDelete = LayerPanelUtils::CanDeleteTargetLayers(layerPanelData);
	}
	bool16 forceRedraw = kFalse;
	
	if (pView->GetEnableState() && !canDelete)
	{
		pView->Disable();
		forceRedraw = kTrue;
	}
	else if (!pView->GetEnableState() && canDelete)
	{
		pView->Enable();
		forceRedraw = kTrue;
	}

	if (forceRedraw)
	{
		SysRgn myRgn = ::CreateRectSysRgn( pView->GetBBox() ); 
#ifdef MACINTOSH
        //FIXME_INVAL
        pView->ForceRedraw( myRgn, kFalse );
#else
        pView->ForceRedraw( myRgn, kTrue );
#endif
		::DeleteSysRgn( myRgn );
	}
}

