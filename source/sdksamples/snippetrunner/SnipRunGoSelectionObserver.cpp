//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunGoSelectionObserver.cpp $
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

//===========================
//  Plug-in includes
//===========================

#include "VCPlugInHeaders.h"

// Interface includes
#include "IStringData.h"
#include "IControlView.h"

// General includes
#include "SelectionObserver.h"
#include "ILayoutUIUtils.h"
#include "ISelectionUtils.h"

// Project includes
#include "SnipRunID.h"
#include "ISnipRunSuite.h"

/** Enables or disables the button when the selection changes dependent
	on whether ISnipRunSuite::CanRun indicates the snippet can or cannot 
	be run.

	The name of the snippet this implementation works with is given 
	by the IStringData interface aggregated onto this control's boss
	class using IID_ISNIPRUNSNIPPETNAMESTRINGDATA.

	This observer subclasses ActiveSelectionObserver so when there is a selection change
	SnipRunGoSelectionObserver will get notified.  

	@ingroup snippetrunner
	
*/
class SnipRunGoSelectionObserver : public ActiveSelectionObserver
{
	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnipRunGoSelectionObserver(IPMUnknown* boss);

		/**
			Destructor.
		*/
		virtual ~SnipRunGoSelectionObserver();

	protected:

		/** Called when the selection changes.
		*/
		virtual void HandleSelectionChanged(const ISelectionMessage* message);
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunGoSelectionObserver, kSnipRunGoSelectionObserverImpl)

/*
*/
SnipRunGoSelectionObserver::SnipRunGoSelectionObserver(IPMUnknown* boss) :
	ActiveSelectionObserver(boss, IID_ISNIPRUNGOSELECTIONOBSERVER)
{
}

/*
*/
SnipRunGoSelectionObserver::~SnipRunGoSelectionObserver()
{
}

/* 
*/
void SnipRunGoSelectionObserver::HandleSelectionChanged(const ISelectionMessage* message)
{
	do {
		InterfacePtr<IControlView> controlView(this, UseDefaultIID());
		ASSERT(controlView);
		if (!controlView) {
			break;
		}
		InterfacePtr<ISnipRunSuite> suite(Utils<ISelectionUtils>()->GetActiveSelection(), UseDefaultIID());
		if (!suite) {
			// If there's no ISnipRunSuite then no snippets can be run so disable the button.
			controlView->Enable(kFalse);
			break;
		}

		// Get the name of the snippet to work with.
		InterfacePtr<IStringData> stringData(this, IID_ISNIPRUNSNIPPETNAMESTRINGDATA);
		ASSERT(stringData);
		if (!stringData) {
			break;
		}
		ISnipRunSuite::SnippetName snippetName = stringData->GetString();
		if (snippetName.empty()) {
			// If the snippet name is empty disable the button.
			controlView->Enable(kFalse);
			break;
		}

		// Enable or disable the button according to whether or not the rnippet can run.
		bool16 canRun = suite->CanRun(snippetName);
		controlView->Enable(canRun);
	} while(false);
}

// End, SnipRunGoSelectionObserver.cpp.



