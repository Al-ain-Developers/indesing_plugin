//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightRuleCheckBoxObserver.cpp $
//  
//  Owner: InDesign Developer Technologies
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

// General includes
#include "widgetid.h"
#include "CObserver.h"

// Interface includes
#include "ISubject.h"
#include "ITriStateControlData.h"
// Project includes
#include "PreflightRuleUIID.h"
#include "PreflightRuleDataHelper.h"
/**

	Observes the "pen" buttons in the widget list.

	@ingroup wlistboxcomposite
	
*/
class PreflightCheckBoxObserver : public CObserver
{
public:

	/**
		Constructor for WLBListBoxObserver class.
		@param interface ptr from boss object on which this interface is aggregated.
	*/
	PreflightCheckBoxObserver(IPMUnknown *boss);

	/**
		AutoAttach is only called for registered observers
		of widgets.  This method is called by the application
		core when the widget is shown.
	
	*/	
	virtual void AutoAttach();

	/**
		AutoDetach is only called for registered observers
		of widgets. Called when widget hidden.
	*/	
	virtual void AutoDetach();

	/**
		Update when there's been a change on the pen widget.
	
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

CREATE_PMINTERFACE(PreflightCheckBoxObserver, kPreflightCheckBoxObserverImpl)


PreflightCheckBoxObserver::PreflightCheckBoxObserver(IPMUnknown* boss) : CObserver(boss)
{
	
}

void PreflightCheckBoxObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
	}
	
}


void PreflightCheckBoxObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->DetachObserver(this,IID_ITRISTATECONTROLDATA);
	}
}


void PreflightCheckBoxObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	PreflightRuleDataHelper::NotifyRuleDataChanged(this);
}

