//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentexteditor/HidTxtEdSelectionObserver.cpp $
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

// Interface include:
#include "IControlView.h"
#include "ITextControlData.h"
#include "ISelectionUtils.h"
#include "IPanelControlData.h"
#include "ICounterControlData.h"

// General includes:
#include "SelectionObserver.h"
#include "PMString.h"
#include "WideString.h"

// HiddenText includes:
#include "HidTxtID.h"
#include "IHidTxtSuite.h"

// Project includes:
#include "HidTxtEdID.h"

/** Implements an ActiveSelectionObserver that updates widgets 
	that display hidden text associated with the selection.

	
	@ingroup hiddentexteditor
*/
class HidTxtEdSelectionObserver : public ActiveSelectionObserver
{
	public:
		/** Constructor
			@param boss interface ptr from boss object on which this interface is aggregated.
		 */
						HidTxtEdSelectionObserver(IPMUnknown *boss);

		/** Destructor.
		 */
		virtual			~HidTxtEdSelectionObserver();

	protected:
		/** When an object is added or removed from the selection or if the kind
			of selection changes (e.g. from a a layout selection to a text selection)
			this method is called to synchronise the data displayed with the data
			associated with the selection.
			@param message from selection describing change or nil if the active selection changed.
		*/
		virtual void HandleSelectionChanged(const ISelectionMessage* message);

		/**
 			If the selection's data changes this method gets called. We check
			that data we are interested in is affected before taking any action
			by calling ISelectionMessage::WasSuiteAffected and checking that
			a message from IHidTxtSuite is present. If so we update the data in the
			panel's widgets.
			@param message from selection indicating the attribute(s) affected
		*/
		virtual void HandleSelectionAttributeChanged (const ISelectionMessage* message);

	private:
		/** Update the widget to reflect any change to hidden text.
		*/
		virtual	void UpdateWidget();
};

/*
*/
CREATE_PMINTERFACE(HidTxtEdSelectionObserver, kHidTxtEdSelectionObserverImpl)

/*
*/
HidTxtEdSelectionObserver::HidTxtEdSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss)
{
}

/*
*/
HidTxtEdSelectionObserver::~HidTxtEdSelectionObserver()
{
}

/*
*/
void HidTxtEdSelectionObserver::HandleSelectionChanged(const ISelectionMessage* message)
{
	this->UpdateWidget();
}

/*
*/
void HidTxtEdSelectionObserver::HandleSelectionAttributeChanged( const ISelectionMessage* message)
{
	// It is very important that you filter this call for a suite PMIID.
	// Your active selection observer is called when any attribute of the
	// selection changes, so you only want to update widgets when a change
	// that is of interest occurs.
	if (message && message->WasSuiteAffected(IHidTxtSuite::kDefaultIID)) {
		// Always call ISelectionMessage::WasSuiteAffected before 
		// taking any action. Otherwise your implementation is inefficient.
		this->UpdateWidget();
	}
}

/*
*/
void HidTxtEdSelectionObserver::UpdateWidget()
{
	do {
		bool16 isWidgetEnabled = kFalse;
		PMString widgetText;

		// Call IHidTxtSuite to see if there is hidden text associated with the selection.
		InterfacePtr<const IHidTxtSuite> hidTxtSuite(fCurrentSelection, UseDefaultIID());
		if (hidTxtSuite != nil && hidTxtSuite->CanGetHiddenText()) {
			isWidgetEnabled = kTrue;
			WideString hiddenTextW;
			hidTxtSuite->GetHiddenText(hiddenTextW);
			// Only show characters that the text widget can render.
			for (WideStringConstUTF32Iter iter = hiddenTextW.begin(); iter < hiddenTextW.end(); iter++) {
				if (TextChar::IsK2SpecificChar(*iter) == kFalse) {
					widgetText.AppendW(*iter);
				}
			}

		}
		widgetText.SetTranslatable(kFalse);

		// Update the data displayed in the panel's widgets.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData) {
			break;
		}

		// Scroll the scroll bar to the top.
		IControlView* scrollBarControlView = panelControlData->FindWidget(kHidTxtEdPanelDataScrollBarWidgetID);
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
		if (counterControlData->GetValue() != minValue) {
			counterControlData->SetValue(minValue);
		}

		// Display the hidden text or clear the text widget if there is none.
		IControlView* textControlView = panelControlData->FindWidget(kHidTxtEdPanelDataWidgetID);
		ASSERT(textControlView);
		if (!textControlView) {
			break;
		}
		InterfacePtr<ITextControlData> textControlData(textControlView, UseDefaultIID());
		ASSERT(textControlData);
		if (!textControlData) {
			break;
		}
		textControlData->SetString(widgetText);

		// Enable widgets if hidden text is being displayed, disable otherwise.
		IControlView* dataLabelControlView = panelControlData->FindWidget(kHidTxtEdPanelDataLabelWidgetID);
		ASSERT(dataLabelControlView);
		if (!dataLabelControlView) {
			break;
		}
		if (isWidgetEnabled != dataLabelControlView->IsEnabled()) {
			dataLabelControlView->Enable(isWidgetEnabled);
		}

	} while(false);
}

// End, HidTxtEdSelectionObserver.cpp.