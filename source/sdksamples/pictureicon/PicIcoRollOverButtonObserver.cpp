//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pictureicon/PicIcoRollOverButtonObserver.cpp $
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

// Implementation includes
#include "widgetid.h"
// Interface includes
#include "ISubject.h"
// Implem includes
#include "CAlert.h"
#include "CObserver.h"
#include "PicIcoID.h"

/**
	Adding an IObserver interface to a widget boss class creates a button
	whose presses can be registered as Update messages to the client code. 

	@ingroup pictureicon
	
*/
class PicIcoRollOverButtonObserver : public CObserver
{
public:
	/**
		Constructor 
	*/		
	PicIcoRollOverButtonObserver(IPMUnknown *boss);
	/**
		Destructor
	*/
	~PicIcoRollOverButtonObserver();
	/**
		AutoAttach is only called for registered observers
		of widgets.  This method is called when the 
		widget boss object is shown.
	*/		
	virtual void AutoAttach();

	/**
		AutoDetach is only called for registered observers
		of widgets. Called when the widget is hidden.
	*/		
	virtual void AutoDetach();

	/**
		Update is called for all registered observers, and is
		the method through which changes are broadcast. 
		@param theChange this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject this provides a reference to the object which has changed; in this case, the button
		widget boss object that is being observed.
		@param protocol the protocol along which the change occurred.
		@param changedBy this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	
};

CREATE_PMINTERFACE(PicIcoRollOverButtonObserver, kPicIcoRollOverButtonObserverImpl)


PicIcoRollOverButtonObserver::PicIcoRollOverButtonObserver(IPMUnknown* boss)
: CObserver(boss)
{
	
}


PicIcoRollOverButtonObserver::~PicIcoRollOverButtonObserver()
{
	
}


void PicIcoRollOverButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
	}
}


void PicIcoRollOverButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
	}
}



void PicIcoRollOverButtonObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	if(theChange == kTrueStateMessage) {
		// No behaviour in this sample: but indicate at least that the message has been received.
		CAlert::InformationAlert(kPicIcoMessageKey);
	}	
}
