//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CelPnlEditBoxObserver.cpp $
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
//  
//  API:
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Implementation Includes:
#include "CObserver.h"

#include "CelPnlID.h"

/** CelPnlEditBoxObserver
	implements the observer.

	CelPnlEditBoxObserver implements IObserver based on the partial implementation CObserver.
	This observer is empty! Edit this method to observe the EditBox widget.

	@ingroup cellpanel
	
*/
class CelPnlEditBoxObserver : public CObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CelPnlEditBoxObserver(IPMUnknown *boss);
		
		/**
			Destructor.
		*/
		virtual ~CelPnlEditBoxObserver();
		
		/**
			Respond to a change in an observed subject. Called by the host when the observed object changes.
			Called for all registered observers, and is the method through which changes are broadcast.
			
			@param theChange theChange represents the change to an object, often this is a command id.
			@param theSubject theSubject is the subject that changed.
			@param protocol  protocol is the interface of the subject's boss that changed.
			@param changedBy changedBy is used to pass additional data about the change, often this is a pointer to the command that caused the change.
		*/
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
			
		/** 
			Called by the application to allow the observer to attach to the subjects to be observed.
			AutoAttach is only called for registered observers of widgets.
		*/
		virtual void AutoAttach();
		
		/**
			Called by the application to allow the observer to detach from the subjects being observed.
			AutoDetach is only called for registered observers of widgets.
		*/
		virtual void AutoDetach();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CelPnlEditBoxObserver, kCelPnlEditBoxObserverImpl)

/* CelPnlEditBoxObserver
*/
CelPnlEditBoxObserver::CelPnlEditBoxObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

/* ~CelPnlEditBoxObserver
*/
CelPnlEditBoxObserver:: ~CelPnlEditBoxObserver()
{
}

/* Update
*/
void CelPnlEditBoxObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
}

/* AutoAttach
*/
void CelPnlEditBoxObserver::AutoAttach()
{
}

/* AutoDetach
*/
void CelPnlEditBoxObserver::AutoDetach()
{
}

// End, CelPnlEditBoxObserver.cpp.



