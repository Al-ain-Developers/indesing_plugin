//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/NewLayerButtonObserver.cpp $
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

#include "ISubject.h"
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "IControlView.h"
#include "IWorkspace.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"

#include "EventUtilities.h"
#include "CmdUtils.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "LayerID.h"
#include "RsrcSpec.h"

#include "LayerPanelDefs.h"
#include "LayerPanelUtils.h"
#include "CoreResTypes.h"
#include "widgetid.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class NewLayerButtonObserver
//----------------------------------------------------------------------------------------

class NewLayerButtonObserver : public CObserver
{
	public:
		NewLayerButtonObserver(IPMUnknown *boss);
		virtual ~NewLayerButtonObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);



	private:
		void UpdateButton();

};





//----------------------------------------------------------------------------------------
//
// Class implementation
//
//----------------------------------------------------------------------------------------


//========================================================================================
// CLASS NewLayerButtonObserver
//========================================================================================

CREATE_PMINTERFACE(NewLayerButtonObserver, kNewLayerButtonObserverImpl)

//----------------------------------------------------------------------------------------
// NewLayerButtonObserver constructor 
//----------------------------------------------------------------------------------------

NewLayerButtonObserver::NewLayerButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// NewLayerButtonObserver::~NewLayerButtonObserver: 
//----------------------------------------------------------------------------------------

NewLayerButtonObserver::~NewLayerButtonObserver()
{
}


//----------------------------------------------------------------------------------------
// NewLayerButtonObserver::AutoAttach: 
// We also observe IID_ILISTCONTROLDATA, but that is hooked up
// when the listbox is created. See LayerPanelObserver.cpp, AutoAttach.
//----------------------------------------------------------------------------------------

void NewLayerButtonObserver::AutoAttach()
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
// NewLayerButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void NewLayerButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget( this, kLayerPanelTreeWidgetID,IID_ISUBJECT ));
	if(treeSubject)
		treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
}

//----------------------------------------------------------------------------------------
// NewLayerButtonObserver::Update: 
//	By default, just create a new layer at the top of the list with no dialog.
//	If command key is down, create a new layer with no dialog, but create above current active layer.
//	If option key only is down, open the new layer dialog.
//	If command key and option key is down, create a new layer with no dialog, but create below current active layer.
//----------------------------------------------------------------------------------------

void NewLayerButtonObserver::Update(const ClassID& theChange, ISubject* , const PMIID& protocol, void* )
{
	// ==> Please update GetObserverInfo()  <==
	bool16 optionKeyDown = IsOptionAltKeyPressed(); // If true, do New Layer dialog
	bool16 commandKeyDown = IsCommandKeyPressed(); // If true, create new layer below current active layer
	bool16 shiftKeyDown = ::IsShiftKeyPressed();	// If true, and commandKeyDown, create new layer on top

	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data->IsSelected())
		{
			IDataBase* frontDocumentDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
			if (frontDocumentDB)
			{
				LayerPanelUtils::LayerLocation location = LayerPanelUtils::kAboveActive;	
				if (commandKeyDown)
						location = shiftKeyDown ? LayerPanelUtils::kOnTop : LayerPanelUtils::kBelowActive;

				// Shortcut to force the New Layer dialog to come up	
				if (optionKeyDown)
				{
					LayerPanelUtils::InvokeLayerDialog(LayerPanelUtils::kNewLayerDialog, location, nil, nil);
					return;
				}
				else
				{
					InterfacePtr<ICommand> newLayerCmd(LayerPanelUtils::CreateNewLayerCommand(location));
					if (newLayerCmd)
						CmdUtils::ProcessCommand(newLayerCmd);
				}
			}
		}
	}
	else if(protocol == IID_ITREEVIEWCONTROLLER && theChange == kListSelectionChangedMessage )
	{
		this->UpdateButton();
	}

}

//----------------------------------------------------------------------------------------
// NewLayerButtonObserver::UpdateButton: 
//----------------------------------------------------------------------------------------
void NewLayerButtonObserver::UpdateButton()
{
	InterfacePtr<IControlView> pView( this, IID_ICONTROLVIEW ) ;
	
	bool16 canNew = (LayerPanelUtils::GetCurrentLayerPanelDB(this) != nil);
	bool16 forceRedraw = kFalse;
	
	if (pView->GetEnableState() && !canNew)
	{
		pView->Disable();
		forceRedraw = kTrue;
	}
	else if (!pView->GetEnableState() && canNew)
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


