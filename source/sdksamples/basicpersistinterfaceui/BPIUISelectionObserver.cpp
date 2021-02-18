//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterfaceui/BPIUISelectionObserver.cpp $
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
#include "ITextControlData.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ICounterControlData.h"
#include "IPanelControlData.h"


// General includes
#include "SelectionObserver.h"
#include "ILayoutUIUtils.h"
#include "ISelectionUtils.h"

// Project includes
#include "BPIUIID.h"
#include "IBPISuite.h"

/** Implements a selection observer, IObserver based on ActiveSelectionObserver,
	that updates the user interface when the selection changes by calling
	IBPISuite to access the IBPIData associated with the selection.

	When the active selection changes (from
	text selection to layout selection for example), or when an object is added or removed
	from the selection or when an attribute of selected objects change this
	observer gets called. It then determines if it needs to update the data in its
	widgets to reflect the IBPIData associated with the selection.

	@ingroup basicpersistinterface
	
*/
class BPISelectionObserver : public ActiveSelectionObserver
{
	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BPISelectionObserver(IPMUnknown* boss);

		/**
			Destructor.
		*/
		virtual ~BPISelectionObserver();

	protected:

		/**
 			When an object is added or removed from the selection or if the kind
			of selection changes (e.g. from a a layout selection to a text selection)
			this method is called which results in BPISelectionObserver::UpdatePanel
			being called.
			@param message from selection describing change or nil if the active selection changed.
		*/
		virtual void HandleSelectionChanged(const ISelectionMessage* message);

		/**
 			If the selection's data changes this method gets called. We check
			that data we are interested in is affected before taking any action
			by calling ISelectionMessage::WasSuiteAffected and checking that
			a message from IBPISuite is present. If so we update the data in the
			panel's widgets to reflect that of the selection.
			@param message from selection indicating the attribute(s) affected
		*/
		virtual void HandleSelectionAttributeChanged (const ISelectionMessage* message);

		/**
			Update the panel to reflect selection's IBPISuite data.
		*/
		void		UpdatePanel();
};

/*
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BPISelectionObserver, kBPIUISelectionObserverImpl)

/* Constructor
*/
BPISelectionObserver::BPISelectionObserver(IPMUnknown* boss) :
	ActiveSelectionObserver(boss)
{
}

/* Destructor
*/
BPISelectionObserver::~BPISelectionObserver()
{
}

/*
*/
void BPISelectionObserver::HandleSelectionChanged(const ISelectionMessage* message)
{
	this->UpdatePanel();
}

/*
*/
void BPISelectionObserver::HandleSelectionAttributeChanged( const ISelectionMessage* iSelectionMsg)
{
	// It is very important that you filter this call for a suite PMIID.
	// Your active selection observer is called when any attribute of the
	// selection changes, so you only want to update widgets when a change
	// that is of interest occurs.
	if (iSelectionMsg->WasSuiteAffected(IBPISuite::kDefaultIID)) {
		// Always call ISelectionMessage::WasSuiteAffected before 
		// taking any action. Otherwise your implementation is inefficient.
		this->UpdatePanel();
	}
}

/*
*/
void BPISelectionObserver::UpdatePanel()
{
	do {
		// Use the suite to access the data.
		K2Vector<WideString> values;
		InterfacePtr<IBPISuite> bpiSuite(fCurrentSelection, UseDefaultIID());
		if (bpiSuite && bpiSuite->CanGetBPIData()) {
			bpiSuite->GetBPIData(values);
		}

		// Update the data displayed in the panel's widgets.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData) {
			break;
		}

		// Scroll multi line widget to top.
		IControlView* scrollBarControlView = panelControlData->FindWidget(kBPIUIDataScrollBarWidgetID);
		ASSERT(scrollBarControlView);
		if (!scrollBarControlView) {
			break;
		}
		InterfacePtr<ICounterControlData> counterControlData(scrollBarControlView, UseDefaultIID());
		ASSERT(counterControlData);
		if (!counterControlData) {
			break;
		}
		int32 minValue = counterControlData->GetMinimum();	
		counterControlData->SetValue(minValue);

		// Display each string returned by the suite in a line in the multi line widget.
		IControlView* textControlView = panelControlData->FindWidget(kBPIUIDataWidgetID);
		ASSERT(textControlView);
		if (!textControlView) {
			break;
		}
		InterfacePtr<ITextControlData> textControlData(textControlView, UseDefaultIID());
		ASSERT(textControlData);
		if (!textControlData) {
			break;
		}
		PMString value;
		value.SetTranslatable(kFalse);
		PMString kNewLine;
		kNewLine.AppendW(kTextChar_LF);
		kNewLine.SetTranslatable(kFalse);
		for (int32 i = 0; i < values.size(); i++) {
			value += values[i];
			value += kNewLine;
		}
		textControlData->SetString(value);
	}
	while (false);
}



// End, BPISelectionObserver.cpp.



