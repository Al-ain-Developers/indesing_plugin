//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechartui/CdlChtUIWidgetObserver.cpp $
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

// Interface includes:
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"

// General includes:
#include "CObserver.h"

// Project includes:
#include "CdlChtUIID.h"

/** Provides the capability to observe the widgets on the panel and respond appropriately
	to changes in their state.
	
	@ingroup candlechartui
	
*/
class CdlChtUIWidgetObserver : public CObserver
{
public:
	/** Constructor
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/      
	CdlChtUIWidgetObserver(IPMUnknown* boss);

	/**	Destructor. Performs cleanup.
	*/
	~CdlChtUIWidgetObserver();

	/**	AutoAttach is only called for registered observers
		of widgets.  This method is called by the application
		core when the widget is shown.
	*/      
	virtual void AutoAttach();

	/** AutoDetach is only called for registered observers
		of widgets. Called when the widget is hidden.
	*/      
	virtual void AutoDetach();

	/** Update is called for all registered observers, and is
		the method through which changes are broadcast. 
		@param theChange IN this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject IN this provides a reference to the object which has changed; in this case, the button
		widget boss object that is being observed.
		@param protocol IN the protocol along which the change occurred.
		@param changedBy IN this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	void handleWidgetHit(InterfacePtr<IControlView>& controlView, const ClassID& theChange, WidgetID widgetID) ;
	void attachWidget(InterfacePtr<IPanelControlData>&  panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
	void detachWidget(InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

	const PMIID fObserverIID;

};

/* CREATE_PMINTERFACE
	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CdlChtUIWidgetObserver, kCdlChtUIWidgetObserverImpl)

/* Constructor
*/
CdlChtUIWidgetObserver::CdlChtUIWidgetObserver(IPMUnknown* boss)
	: CObserver(boss), fObserverIID(IID_ICdlChtUIWIDGETOBSERVER)
{
}

/* Destructor
*/
CdlChtUIWidgetObserver::~CdlChtUIWidgetObserver()	
{
}

/* AutoAttach
*/
void CdlChtUIWidgetObserver::AutoAttach()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData)
		{
			break;
		}

		// TODO attach to widgets to observe here 
		// this->attachWidget(...);
	} while (kFalse);
}

/* AutoDetach
*/
void CdlChtUIWidgetObserver::AutoDetach()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData)
		{
			break;
		}
		// TODO detach from widgets here 
		// this->detachWidget(...);

	} while (kFalse);
}


/* attachWidget
*/
void CdlChtUIWidgetObserver::attachWidget(InterfacePtr<IPanelControlData>& panelControlData,
										  const WidgetID& widgetID, const PMIID& interfaceID)
{
	ASSERT(panelControlData != nil);

	TRACE("TblAttWidgetObserver::AttachWidget(widgetID=0x%x, interfaceID=0x%x\n", widgetID.Get(), interfaceID.Get());
	do
	{
		if (!panelControlData) break;

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView != nil);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		ASSERT(subject != nil);
		if (subject == nil)
		{
			break;
		}
		subject->AttachObserver(this, interfaceID, fObserverIID);
	}
	while (kFalse);
}

/* detachWidget
*/
void CdlChtUIWidgetObserver::detachWidget(InterfacePtr<IPanelControlData>& panelControlData,
                                          const WidgetID& widgetID, const PMIID& interfaceID)
{
	ASSERT(panelControlData != nil);
	do
	{
		if (panelControlData == nil) break;

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView != nil);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		ASSERT(subject != nil);
		if (subject == nil)
		{
			break;
		}
		subject->DetachObserver(this, interfaceID, fObserverIID);
	}
	while (false);
}


/* Update
*/
void CdlChtUIWidgetObserver::Update(const ClassID& theChange, ISubject* theSubject, 
									const PMIID& protocol, void* changedBy)
{
	do
	{
		ASSERT(theSubject);
		if (!theSubject)
		{
			break;
		}
		InterfacePtr<IControlView>  icontrolView(theSubject, UseDefaultIID());
		ASSERT(icontrolView);
		if (!icontrolView)
		{
			break;
		}
		WidgetID thisID = icontrolView->GetWidgetID();
		if (thisID != kInvalidWidgetID)
		{
			this->handleWidgetHit(icontrolView, theChange, thisID);
		}
	} while (kFalse);
}

/* handleWidgetHit
*/
void CdlChtUIWidgetObserver::handleWidgetHit(InterfacePtr<IControlView>& controlView, 
											 const ClassID& theChange, WidgetID widgetID) 
{
	do
	{

		ASSERT(widgetID != kInvalidWidgetID);
		ASSERT(controlView);
		if (controlView==nil)
		{
			break;

		}

		// TODO: add code to handle this event

	} while (kFalse);
}

// End, CdlChtUIWidgetObserver.cpp.
