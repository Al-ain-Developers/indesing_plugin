//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/TableCellObserver.cpp $
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

// Interface Includes:
#include "ISubject.h"
#include "ICounterControlData.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"

// Implementation Includes:
#include "CObserver.h"
#include "widgetid.h"

#include "CelPnlID.h"

/**
	This implementation handles updating of the scroll bars and updates the table cell widget (kTableCellWidgetBoss).

	@ingroup cellpanel
	
*/
class TableCellObserver : public CObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TableCellObserver(IPMUnknown *boss);
		
		/**
			Destructor.
		*/
		virtual ~TableCellObserver();
		
		/**
			Respond to a change in an observed subject. Called by the host when the observed object changes.
			Called for all registered observers, and is the method through which changes are broadcast.
			Our observer is attached to two scrollbar widget.
			
			@param theChange theChange represents the change to an object, often this is a command id.
			@param theSubject theSubject is the subject that changed.
			@param protocol  protocol is the interface of the subject's boss that changed.
			@param changedBy changedBy is used to pass additional data about the change, often this is a pointer to the command that caused the change.
		*/
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		/**
			Called by the application to allow the observer to attach to the subjects to be observed.
			AutoAttach is only called for registered observers of widgets.
			When AutoAttach is called from the app, we attach ourselves to scrollbars.
		*/
		virtual void AutoAttach();
		
		/**
			Called by the application to allow the observer to detach from the subjects being observed.
			AutoDetach is only called for registered observers of widgets.
			When AutoDetach is called from the app, we detach ourselves to scrollbars.
		*/
		virtual void AutoDetach();
		
	private:
		/** Private data member */
		int32 fLastVScrollValue, fLastHScrollValue;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(TableCellObserver, kTableCellObserverImpl)

/*  TableCellObserver::TableCellObserver
*/
TableCellObserver::TableCellObserver(IPMUnknown* boss) : CObserver(boss),
	fLastHScrollValue(0),
	fLastVScrollValue(0)
{
}

/*  TableCellObserver::~TableCellObserver
*/
TableCellObserver::~TableCellObserver()
{
}

/*  TableCellObserver::Update
*/
void TableCellObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kCounterChangeStateMessage)
	{
		do{
			InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
			if(myParent == nil) break;
			
			InterfacePtr<IPanelControlData>	panelData((IPanelControlData*)myParent->QueryParentFor(IID_IPANELCONTROLDATA));
			if(panelData == nil) break;
			
			InterfacePtr<ICounterControlData> vScrollValue(panelData->FindWidget(kTableCellScrollWidgetID), UseDefaultIID());
			if(vScrollValue == nil) break;
			
			InterfacePtr<ICounterControlData> hScrollValue(panelData->FindWidget(kTableCellHScrollWidgetID), UseDefaultIID());
			if(hScrollValue == nil) break;
			
			int32 vValue = vScrollValue->GetValue();
			int32 hValue = hScrollValue->GetValue();
			
			if((vValue != fLastVScrollValue) || (hValue != fLastHScrollValue))
			{
				InterfacePtr<IControlView>	myView(this, UseDefaultIID());
				myView->Invalidate();
				fLastVScrollValue = vValue;
				fLastHScrollValue = hValue;
			}
		}while(kFalse);
	}		
}

/*  TableCellObserver::AutoAttach
*/
void TableCellObserver::AutoAttach()
{
	do{
		InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
		if(myParent == nil) break;
		
		InterfacePtr<IPanelControlData> panelData((IPanelControlData*)myParent->QueryParentFor(IID_IPANELCONTROLDATA)) ;
		if(panelData == nil) break;
		
		InterfacePtr<ISubject>			vScrollBar(panelData->FindWidget(kTableCellScrollWidgetID), UseDefaultIID());
		if(vScrollBar == nil) break;
		
		InterfacePtr<ISubject>			hScrollBar(panelData->FindWidget(kTableCellHScrollWidgetID), UseDefaultIID());
		if(hScrollBar == nil) break;
		
		vScrollBar->AttachObserver(this, IID_ICOUNTERCONTROLDATA);
		hScrollBar->AttachObserver(this, IID_ICOUNTERCONTROLDATA);
		
	}while(kFalse);
}

/*  TableCellObserver::AutoDetach
*/
void TableCellObserver::AutoDetach()
{
	do{
		InterfacePtr<IWidgetParent>		myParent(this, 	 UseDefaultIID());
		if(myParent == nil) break;
		
		InterfacePtr<IPanelControlData> panelData((IPanelControlData*)myParent->QueryParentFor(IID_IPANELCONTROLDATA)) ;
		if(panelData == nil) break;
		
		InterfacePtr<ISubject>			vScrollBar(panelData->FindWidget(kTableCellScrollWidgetID), UseDefaultIID());
		if(vScrollBar == nil) break;
		
		InterfacePtr<ISubject>			hScrollBar(panelData->FindWidget(kTableCellHScrollWidgetID), UseDefaultIID());
		if(hScrollBar == nil) break;
		
		vScrollBar->DetachObserver(this, IID_ICOUNTERCONTROLDATA);
		hScrollBar->DetachObserver(this, IID_ICOUNTERCONTROLDATA);
			
	}while(kFalse);
}

//End, TableCellObserver.cpp.
