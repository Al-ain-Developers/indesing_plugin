//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunGoButtonObserver.cpp $
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

// Interface includes
#include "ISubject.h"
#include "IControlView.h"
#include "ISelectionUtils.h"
#include "IStringData.h"
#include "IControlView.h"
#include "ITriStateControlData.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"

// General includes
#include "CObserver.h"
#include "Trace.h"
#include "KeyStates.h"

// Project includes
#include "SnipRunID.h"
#include "ISnipRunSuite.h"

/** Runs the snippet when the go button is clicked, also when
	the name of the snippet to be run is changed this
	observer uses ISnipRunSuite::CanRun to determine if the snippet
	can run and enables or disables the button accordingly.

	The name of the snippet this implementation works with is given 
	by the IStringData interface aggregated onto this control's boss
	class as IID_ISNIPRUNSNIPPETNAMESTRINGDATA. To get
	this observer to recognise a change to this data client
	code should call this button's ISubject as shown:
	<pre>
	ISubject::Change(kTextChangeStateMessage, IID_ISNIPRUNSNIPPETNAMESTRINGDATA);
	</pre>

	Implements IObserver based on the partial implementation CObserver.

	
	@ingroup snippetrunner
*/
class SnipRunGoButtonObserver : public CObserver
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SnipRunGoButtonObserver( IPMUnknown* boss );

	/** Destructor
	*/
	virtual ~SnipRunGoButtonObserver() ;
	
	/** Attaches observed subjects. Observes the button's ITriStateControlData to catch clicks
		and the IID_ISNIPRUNSNIPPETNAMESTRINGDATA to catch when the name
		of the snippet to be run changes.
	*/
	virtual void AutoAttach();

	/** Detaches observed subjects.
	*/
	virtual void AutoDetach();

	/** An observed subject has changed.
	*/
	virtual void Update( const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy ) ;

private:
	/*
		InterfaceID used to aggregate the the widget observer onto the panel.
	*/
	const PMIID fObserverIID;
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunGoButtonObserver, kSnipRunGoButtonObserverImpl)

/*
*/
SnipRunGoButtonObserver::SnipRunGoButtonObserver( IPMUnknown* boss ) :
	CObserver( boss ), fObserverIID(IID_ISNIPRUNGOBUTTONOBSERVER)
{
}

/*
*/
SnipRunGoButtonObserver::~SnipRunGoButtonObserver()
{
}

/*
*/
void SnipRunGoButtonObserver::AutoAttach()
{
	do {
		InterfacePtr<ISubject> subject(this, UseDefaultIID());
		ASSERT(subject);
		if (!subject) {
			break;
		}
		subject->AttachObserver(this, ITriStateControlData::kDefaultIID, fObserverIID);
		subject->AttachObserver(this, IID_ISNIPRUNSNIPPETNAMESTRINGDATA, fObserverIID);
	} while(false);
}

/* 
*/
void SnipRunGoButtonObserver::AutoDetach()
{
	do {
		InterfacePtr<ISubject> subject(this, UseDefaultIID());
		ASSERT(subject);
		if (!subject) {
			break;
		}
		subject->DetachObserver(this, ITriStateControlData::kDefaultIID, fObserverIID);
		subject->DetachObserver(this, IID_ISNIPRUNSNIPPETNAMESTRINGDATA, fObserverIID);
	} while(false);
}

/*
*/
void SnipRunGoButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy )
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

		if (theChange == kTextChangeStateMessage)
		{
			// The name of the snippet the button is working with has changed.
			// Enable/disable the control dependent on whether the snippet can run.
			controlView->Enable(suite->CanRun(snippetName));
		}
		else if (theChange == kTrueStateMessage)
		{
			// The button has been clicked, run the snippet if possible.
			if (suite->CanRun(snippetName)) {
				bool16 enableParameterDialog = kTrue;
				if (::IsOptionAltKeyPressed()) {
					enableParameterDialog = kFalse;
				}

				// Gather parameters to be passed to the snippet.
				PMString parameters;
				InterfacePtr<IWidgetParent> widgetParent(this, UseDefaultIID());
				ASSERT(widgetParent);
				if (!widgetParent) {
					break;
				}
				InterfacePtr<IPanelControlData> panelControlData((IPanelControlData*)(widgetParent->QueryParentFor(IPanelControlData::kDefaultIID)));
				ASSERT(panelControlData);
				if (!panelControlData) {
					break;
				}
				IControlView* parameterControlView = panelControlData->FindWidget(kSnipRunParametersWidgetID);
				if (parameterControlView && parameterControlView->GetVisibleState()) {
					// Only pass parameters when the parameter widget is shown.
					InterfacePtr<ITextControlData> textControlData(parameterControlView, UseDefaultIID());
					ASSERT(textControlData);
					if (!textControlData) {
						break;
					}
					parameters = textControlData->GetString();
				}

				// Run the snippet.
				ErrorCode status = suite->Run(snippetName, parameters, enableParameterDialog);

				if (status != kCancel) {
					// Show the parameters the snippet ran with.
					if (parameterControlView) {
						InterfacePtr<ITextControlData> textControlData(parameterControlView, UseDefaultIID());
						ASSERT(textControlData);
						if (!textControlData) {
							break;
						}
						textControlData->SetString(parameters);
					}
				}

			}
			else {
				controlView->Enable(kFalse);
			}
		}
	} while(false);
}

// End, SnipRunGoButtonObserver.cpp.


