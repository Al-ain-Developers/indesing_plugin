//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunPanelWidgetObserver.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IDropDownListController.h"
#include "IPMStream.h"
#include "ISelectionUtils.h"
#include "ISelectionManager.h"
#include "IStringData.h"

// General includes
#include "CObserver.h"
#include "CreateObject.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"
#include "CAlert.h"
#include "Utils.h"
#include "SDKFileHelper.h"

// Project includes
#include "SnipRunID.h"
#include "SnipRunLog.h"
#include "ISnipRunSuite.h"

/** Displays the names of registered snippets in widgets on the panel
	and syncs up other widgets to display related data when the user 
	changes the snippet they want to work with, also provides widgets 
	to support the SnippetRunner framework log.

	@ingroup snippetrunner
	
*/
class SnipRunPanelWidgetObserver : public CObserver
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SnipRunPanelWidgetObserver( IPMUnknown* boss );

	/** Destructor
	*/
	virtual ~SnipRunPanelWidgetObserver() ;
	
	/** 
		Initialises widgets and attaches widget observers.
	*/
	void AutoAttach();

	/** 
		Detaches widget observers. 
	*/
	void AutoDetach();

	/**
		Update is called for all registered observers, and is
		the method through which changes are broadcast. 
		@param theChange this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject this provides a reference to the object which has changed; in this case, the
		widget boss objects that are being observed.
		@param protocol the protocol along which the change occurred.
		@param changedBy this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/
	void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

private:
	/** Attach this observer to the given widget.
		@param panelControlData refers to the panel that contains the widget
		@param widgetID gives the subject to be observed
		@param interfaceID gives the protocol to be observed
	 */
	void AttachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

	/** Attach this observer from the given widget.
		@param panelControlData refers to the panel that contains the widget
		@param widgetID gives the subject being observed
		@param interfaceID gives the protocol being observed
	 */
	void DetachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

	/** Initialise the dropdown that displays the names of code snippets that
		are registered with the framework and available to be run.
		@param panelControlData refers to the panel that contains the widget
	 */
	void InitialiseSnippetNames(const InterfacePtr<IPanelControlData>& panelControlData);

	/** Initialise the Trace checkbox.
		@param panelControlData refers to the panel that contains the widget
	 */
	void InitialiseTrace(const InterfacePtr<IPanelControlData>& panelControlData);

	/** Handle the snippet selected in the dropdown widget being changed.
	 */
	void ChangeSnippet();

	/** Handle the Trace checkbox widget being checked.
	 */
	void TraceOn();

	/** Handle the Trace checkbox widget being unchecked.
	 */
	void TraceOff();

	/** Handle the save log button widget being clicked.
	 */
	void SaveLog();

	/** Handle the clear log button widget being clicked.
	 */
	void ClearLog();

	/** Handle the parameter widget update by saving snippet parameters 
		to the snippet parameter dictionary (SnipRunParameterDictionary).
	 */
	void SaveParameters();

	/** Synchronise the Go button with the name of the snippet to be run.
		@param snippetName
	 */
	void UpdateGoButton(const PMString& snippetName);

	/** Query the text control data interface of the given widget.
		@param widgetID gives the which whose text control data is desired
		@return interface pointer to the widget's text control data.
	 */
	InterfacePtr<ITextControlData> QueryTextControlData(const WidgetID& widgetID);

	// Snippet parameter dictionary helper.
private:
	/** Dictionary helper class that stores key value pairs where the key is
		a snippet name and the value is the snippet's parameters. The dictionary
		is not persistent.
	*/
	class SnipRunParameterDictionary
	{
		public:
			/** Return the parameters for the given snippet or an empty string if
				dictionary does not contain a value for the given key.
				@param key the name of a snippet
				@return the value stored for the given key or an empty string if
				dictionary does not contain the given key.
			*/
			PMString	Get(const PMString& key);

			/** Store the given key value pair in the dictionary, if an entry already exists
				for the given key then update it, otherwise insert a new entry.
			*/
			void		Put(const PMString& key, const PMString& value);

		private:
			/** Snippet parameter dictionary element, key is the name
				of the snippet, value is its parameters.
			*/
			typedef	KeyValuePair<PMString, PMString> Element;	

			/** Dictionary of snippet parameters.
			*/
			typedef	K2Vector<Element> Dictionary;
			Dictionary fDictionary;
	};

	/** When the user edits the parameter widget or when a snippet is run and new parameters
		are recorded for it the parameter values get saved in a dictionary so that they are
		available next time the snippet is run.
	 */
	SnipRunParameterDictionary fSnippetParameterDict;
};

/*  Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunPanelWidgetObserver, kSnipRunPanelWidgetObserverImpl)

/* Constructor
*/
SnipRunPanelWidgetObserver::SnipRunPanelWidgetObserver( IPMUnknown* boss ) :
	CObserver( boss )
{
}

/* Destructor
*/
SnipRunPanelWidgetObserver::~SnipRunPanelWidgetObserver()
{
}

/* 
*/
void SnipRunPanelWidgetObserver::AutoAttach()
{
	do
	{
		// Instantiate the log.
		SnipRunLog *theLog = SnipRunLog::Instance();
		if (theLog)
			theLog->InitPanelView(); //Gets done by constructor the first time, but this is necessary to do again if panel closed and reopened

		// Initialise widget state.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("AutoAttach() invalid panelControlData");
			break;
		}
		this->InitialiseSnippetNames(panelControlData);
		this->InitialiseTrace(panelControlData);

		// Attach widget observers.
		this->AttachWidget(panelControlData, kSnipRunNameWidgetID, ITextControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kSnipRunTraceLogWidgetID, ITriStateControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kSnipRunSaveLogWidgetID, ITriStateControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kSnipRunClearLogWidgetID, ITriStateControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kSnipRunParametersWidgetID, ITextControlData::kDefaultIID);

	} while(false);

}

/* 
*/
void SnipRunPanelWidgetObserver::AutoDetach()
{
	do
	{
		// Detach widget observers.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("AutoDetach() invalid panelControlData");
			break;
		}	
		this->DetachWidget(panelControlData, kSnipRunNameWidgetID, ITextControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kSnipRunTraceLogWidgetID, ITriStateControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kSnipRunSaveLogWidgetID, ITriStateControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kSnipRunClearLogWidgetID, ITriStateControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kSnipRunParametersWidgetID, ITextControlData::kDefaultIID);

		SnipRunLog *theLog = SnipRunLog::Instance();
		if (theLog)
			theLog->DetachPanelView(); //Disconnecting the log from the panel early on

	} while(false);

}

/* 
*/
void SnipRunPanelWidgetObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	// A widget's value has been changed by the user.
	if (theChange == kTextChangeStateMessage)
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView != nil)
		{
			WidgetID widgetID = controlView->GetWidgetID();
			switch (widgetID.Get())
			{
				case kSnipRunNameWidgetID:
					this->ChangeSnippet();
					break;
				case kSnipRunParametersWidgetID:
					this->SaveParameters();
					break;
				default:
					ASSERT_FAIL(FORMAT_ARGS("Unknown WidgetID 0x%x", widgetID.Get()));
					break;
			}
		}
		else
		{
			ASSERT_FAIL("Update() controlView invalid");
		}
	}
	else if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView != nil)
		{
			WidgetID widgetID = controlView->GetWidgetID();
			switch (widgetID.Get())
			{
				case kSnipRunTraceLogWidgetID:
					this->TraceOn();
					break;
				case kSnipRunSaveLogWidgetID:
					this->SaveLog();
					break;
				case kSnipRunClearLogWidgetID:
					this->ClearLog();
					break;
				default:
					ASSERT_FAIL(FORMAT_ARGS("Unknown WidgetID 0x%x", widgetID.Get()));
					break;
			}
		}
	}
	else if (theChange == kFalseStateMessage)
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView != nil)
		{
			WidgetID widgetID = controlView->GetWidgetID();
			switch (widgetID.Get())
			{
				case kSnipRunTraceLogWidgetID:
					this->TraceOff();
					break;
			}
		}
		else
		{
			ASSERT_FAIL("Update() controlView invalid");
		}
	}
}


/* 
*/
void SnipRunPanelWidgetObserver::AttachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		if (subject == nil)
		{
			ASSERT_FAIL("subject invalid");
			break;
		}
		subject->AttachObserver(this, interfaceID);
	}
	while (false);
}

/*
*/
void SnipRunPanelWidgetObserver::DetachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		if (subject == nil)
		{
			ASSERT_FAIL("subject invalid");
			break;
		}
		subject->DetachObserver(this, interfaceID);
	}
	while (false);;
}

/* 
*/
void SnipRunPanelWidgetObserver::InitialiseSnippetNames(const InterfacePtr<IPanelControlData>& panelControlData)
{
	do
	{
		// Acquire the interfaces we need to set up the strings in the list.
		IControlView* controlView = panelControlData->FindWidget(kSnipRunNameWidgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}
		InterfacePtr<IStringListControlData> stringListControlData(controlView, UseDefaultIID());
		if (stringListControlData == nil)
		{
			ASSERT_FAIL("invalid stringListControlData");
			break;
		}

		// Clear the drop down list.
		stringListControlData->Clear
			(
			kFalse, // don't invalidate. 
			kFalse // don't notify
			);

		ISnipRunSuite::SnippetNames snippetNames;
		InterfacePtr<ISnipRunSuite> suite(Utils<ISelectionUtils>()->GetActiveSelection(), UseDefaultIID());
		ASSERT(suite);
		if (!suite) {
			break;
		}
		suite->GetSnippetNames(snippetNames);

		// Add their names to the drop down.
		ISnipRunSuite::SnippetNames::iterator iter;
		for (iter = snippetNames.begin(); iter < snippetNames.end(); iter++) {
			stringListControlData->AddString
				(
				*iter, 
				IStringListControlData::kEnd, 
				kFalse, // don't invalidate.
				kFalse //don't notify.
				);
		}
		controlView->Invalidate();

		// Set up panel to run default snippet.
		this->ChangeSnippet();

	} while(false);
}

/* 
*/
void SnipRunPanelWidgetObserver::InitialiseTrace(const InterfacePtr<IPanelControlData>& panelControlData)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(kSnipRunTraceLogWidgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}
		InterfacePtr<ITriStateControlData> triStateControlData(controlView, UseDefaultIID());
		if (triStateControlData == nil) {
			ASSERT_FAIL("triStateControlData invalid");
			break;
		}

		// Turn echo of log messages to Trace on/off based on the state of kSnipRunTraceLogWidgetID.
		SnipRunLog::Instance()->SetTrace(triStateControlData->IsSelected());


		// Only enable the Trace checkbox under the debug build.
		bool16 enable = kFalse;
#ifdef DEBUG
		enable = kTrue;
#endif
		controlView->Enable(enable);


	}
	while (false);
}

/*
*/
void SnipRunPanelWidgetObserver::TraceOn()
{
	SnipRunLog::Instance()->SetTrace(kTrue);
}

/*
*/
void SnipRunPanelWidgetObserver::TraceOff()
{
	SnipRunLog::Instance()->SetTrace(kFalse);
}

/*
*/
void SnipRunPanelWidgetObserver::SaveLog()
{
	ErrorCode status = kFailure;
	bool16 userCancelled = kFalse;
	do
	{
		// Choose file to save the log into.
		SDKFileSaveChooser fileChooser;
		PMString title(kSnipRunSaveDialogNameStringKey);
		fileChooser.SetTitle(title);
		fileChooser.AddFilter('CWIE', 'TEXT', "txt", "TEXT file(txt)");
		fileChooser.SetFilename(kSnipRunDefaultFilenameStringKey);
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			userCancelled = kTrue;
			break;
		}	

		// Open a stream for the file selected by the user.
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(fileChooser.GetIDFile(), kOpenOut, 'TEXT', 'CWIE'));
		if (stream == nil)
		{
			break;
		}

		// Save the log into the file.
		stream->Open();
		if (stream->GetStreamState() == kStreamStateGood)
		{
			stream->SetEndOfStream();
			SnipRunLog::Instance()->SaveLog(stream);
			stream->Flush();
		}
		stream->Close();

		status = kSuccess;
	} while(false);

	if (status == kFailure)
	{
		ErrorUtils::PMSetGlobalErrorCode(kCancel);
		if (userCancelled == kFalse)
			CAlert::ErrorAlert(kSnipRunSaveLogFailedStringKey);
	}
}

/*
*/
void SnipRunPanelWidgetObserver::ClearLog()
{
	do
	{
		SnipRunLog::Instance()->Clear();
	} while(false);
}

/*
*/
void SnipRunPanelWidgetObserver::ChangeSnippet()
{
	do
	{
		// Get the name of the selected snippet.
		InterfacePtr<ITextControlData> nameTextControlData(this->QueryTextControlData(kSnipRunNameWidgetID));
		if (nameTextControlData == nil)
		{
			ASSERT_FAIL("nameTextControlData invalid");
			break;
		}
		PMString snippetName = nameTextControlData->GetString();

		// Sync up the panel properties with those of the selected snippet.
		InterfacePtr<ISnipRunSuite> suite(Utils<ISelectionUtils>()->GetActiveSelection(), UseDefaultIID());
		if (!suite) {
			// ISnipRunSuite needs to be added using an AddIn to the suite boss class
			// for the selection format that is causing this failure. 
			// See ClassDescriptionTable in SnipRun.fr.
			ASSERT_FAIL("ISnipRunSuite is not available for the active selection format, this should not happen");
		}
		bool16 isRegistered = kFalse;
		if (suite) {
			isRegistered = suite->IsRegistered(snippetName);
		}

		PMString description;
		if (suite && isRegistered) {
			suite->GetDescription(snippetName, description);
		}
		description.SetTranslatable(kFalse);
		InterfacePtr<ITextControlData> synopsisTextControlData(this->QueryTextControlData(kSnipRunSynopsisWidgetID));
		if (synopsisTextControlData != nil) {
			synopsisTextControlData->SetString(description);
		}

		PMString preconditions;
		if (suite && isRegistered) {
			suite->GetPreconditions(snippetName, preconditions);
		}
		preconditions.SetTranslatable(kFalse);
		InterfacePtr<ITextControlData> syntaxTextControlData(this->QueryTextControlData(kSnipRunPreconditionsWidgetID));
		if (syntaxTextControlData != nil) {
			syntaxTextControlData->SetString(preconditions);
		}

		// Tell the Go button the snippet name has changed..
		this->UpdateGoButton(snippetName);

		// Get the snippet's parameters from the parameter dictionary
		// and display them in the parameter widget.
		InterfacePtr<ITextControlData> parametersTextControlData(this->QueryTextControlData(kSnipRunParametersWidgetID));
		if (parametersTextControlData == nil)
		{
			ASSERT_FAIL("parametersTextControlData invalid");
			break;
		}
		parametersTextControlData->SetString(fSnippetParameterDict.Get(snippetName), kTrue/*Invalidate*/, kFalse/*don't notify*/);
		// Note the above call does not notify. This is intentional since this class observes the
		// parameter widget for change then saves the parameters to the dictionary when such an
		// occurs. The save would be redundant so notification is suppressed.

	} while (false);
}

/*
*/
void SnipRunPanelWidgetObserver::SaveParameters()
{
	do
	{
		// Get the name of the selected snippet.
		InterfacePtr<ITextControlData> nameTextControlData(this->QueryTextControlData(kSnipRunNameWidgetID));
		if (nameTextControlData == nil)
		{
			ASSERT_FAIL("nameTextControlData invalid");
			break;
		}
		PMString snippetName = nameTextControlData->GetString();

		// Get the parameters.
		InterfacePtr<ITextControlData> parametersTextControlData(this->QueryTextControlData(kSnipRunParametersWidgetID));
		if (parametersTextControlData == nil)
		{
			ASSERT_FAIL("parametersTextControlData invalid");
			break;
		}
		PMString parameters = parametersTextControlData->GetString();

		// Save the snippet's parameters in the dictionary for later recall.
		fSnippetParameterDict.Put(snippetName, parameters);
	} while (false);
}

/*
*/
InterfacePtr<ITextControlData> SnipRunPanelWidgetObserver::QueryTextControlData(const WidgetID& widgetID)
{
	InterfacePtr<ITextControlData> result(nil);
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("invalid panelControlData");
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}
		InterfacePtr<ITextControlData> textControlData(controlView, UseDefaultIID());
		if (textControlData == nil)
		{
			ASSERT_FAIL("invalid textControlData");
			break;
		}
		result = textControlData;
	} while(false);
	return result;
}

/*	Send the go button a message indicating the selected snippet
	has changed and it should test if it can run.
*/
void SnipRunPanelWidgetObserver::UpdateGoButton(const PMString& snippetName)
{
	do {
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (!panelControlData) {
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(kSnipRunGoWidgetID);
		if (!controlView) {
			break;
		}
		InterfacePtr<IStringData> stringData(controlView, IID_ISNIPRUNSNIPPETNAMESTRINGDATA);
		if (!stringData) {
			break;
		}
		stringData->Set(snippetName);
		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		if (!subject) {
			break;
		}
		subject->Change(kTextChangeStateMessage, IID_ISNIPRUNSNIPPETNAMESTRINGDATA);
	} while(false);
}

// --------------------------------- SnipRunParameterDictionary helper ---------------------------------------------------

/*
*/
PMString SnipRunPanelWidgetObserver::SnipRunParameterDictionary::Get(const PMString& key)
{
	PMString result;
	int32 keyLocation = FindLocationInSorted(fDictionary, key);
	if (keyLocation >= 0) {
		result = fDictionary[keyLocation].Value();
	}
	return result;
}

/*
*/
void SnipRunPanelWidgetObserver::SnipRunParameterDictionary::Put(const PMString& key, const PMString& value)
{
	int32 keyLocation = FindLocationInSorted(fDictionary, key);
	if (keyLocation >= 0) {
		fDictionary[keyLocation].SetValue(value);
	}
	else {
		InsertKeyValueInSorted(fDictionary, key, value);
	}
}

// End, SnipRunPanelWidgetObserver.cpp.



