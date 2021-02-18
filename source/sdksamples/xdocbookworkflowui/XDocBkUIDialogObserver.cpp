//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflowui/XDocBkUIDialogObserver.cpp $
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
//  TODO sa+ update copyright and check copyright on all source files,
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IControlView.h"
#include "IDialogController.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IXDocBkFacade.h"
#include "IBooleanControlData.h"
#include "ITriStateControlData.h"
// General includes:
#include "CObserver.h"
#include "SDKFileHelper.h"
#include "Utils.h"

// Project includes:
#include "XDocBkUIID.h"

/**	Implements IObserver based on the partial implementation CDialogObserver; 
	allows dynamic processing of dialog widget changes, in this case
	the dialog's info button. 
	
	@ingroup xdocbookworkflowui
	
*/
class XDocBkUIDialogObserver : public CObserver
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkUIDialogObserver(IPMUnknown* boss) : CObserver(boss, IID_IXDOCBKUIWIDGETOBSERVER) {}

	/** Destructor. 
	 */
	virtual ~XDocBkUIDialogObserver() {}

	/** Called by the application to allow the observer to attach to the subjects 
		to be observed, in this case the dialog's info button widget. If you want 
		to observe other widgets on the dialog you could add them here. 
	*/
	virtual void AutoAttach();

	/** Called by the application to allow the observer to detach from the subjects being observed. 
	 */
	virtual void AutoDetach();

	/** Called by the host when the observed object changes, in this case when
		the dialog's info button is clicked.
		@param theChange IN specifies the class ID of the change to the subject. Frequently this is a command ID.
		@param theSubject IN points to the ISubject interface for the subject that has changed.
		@param protocol IN specifies the ID of the changed interface on the subject boss.
		@param changedBy IN points to additional data about the change. 
			Often this pointer indicates the class ID of the command that has caused the change.
	*/
	virtual void Update
	(
		const ClassID& theChange, 
		ISubject* theSubject, 
		const PMIID& protocol, 
		void* changedBy
	);

private:
	void ChangeTemplate();
	void ChangeStylesheet();
	void SetOptions();
	void DoAttachDetach(const WidgetID& widgetID, const PMIID& pmiid, bool16 attaching);
	void SetUseImagePostImportResponder(bool16 newState);
	void SetUseXMLTransformer(bool16 newState);
	void SetUseCALSContentHandler(bool16 newState);
	void SetSuppliedOverridesPI(bool16 newState);
	

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(XDocBkUIDialogObserver, kXDocBkUIDialogObserverImpl)

/* 
*/
void XDocBkUIDialogObserver::AutoAttach()
{
	CObserver::AutoAttach();

	do
	{
		this->DoAttachDetach(kXDocBkUIChangeTemplateButtonWidgetID, IBooleanControlData::kDefaultIID, kTrue);
		this->DoAttachDetach(kXDocBkUIUseImagePostImportResponderWidgetID, ITriStateControlData::kDefaultIID, kTrue);
		this->DoAttachDetach(kXDocBkUIUseXMLTransformerWidgetID, ITriStateControlData::kDefaultIID, kTrue);
		this->DoAttachDetach(kXDocBkUISuppliedOverridesPIWidgetID, ITriStateControlData::kDefaultIID, kTrue);
		this->DoAttachDetach(kXDocBkUIUseCALSContentHandlerWidgetID, ITriStateControlData::kDefaultIID, kTrue);
		this->DoAttachDetach(kXDocBkUIChangeStylesheetButtonWidgetID, IBooleanControlData::kDefaultIID, kTrue);



	} while (kFalse);
}

/* 
*/
void XDocBkUIDialogObserver::AutoDetach()
{
	CObserver::AutoDetach();

	do
	{
		this->DoAttachDetach(kXDocBkUIChangeTemplateButtonWidgetID, IBooleanControlData::kDefaultIID, kFalse);
		this->DoAttachDetach(kXDocBkUIUseImagePostImportResponderWidgetID, ITriStateControlData::kDefaultIID, kFalse);
		this->DoAttachDetach(kXDocBkUIUseXMLTransformerWidgetID, ITriStateControlData::kDefaultIID, kFalse);
		this->DoAttachDetach(kXDocBkUISuppliedOverridesPIWidgetID, ITriStateControlData::kDefaultIID, kFalse);
		this->DoAttachDetach(kXDocBkUIUseCALSContentHandlerWidgetID, ITriStateControlData::kDefaultIID, kFalse);
		this->DoAttachDetach(kXDocBkUIChangeStylesheetButtonWidgetID, IBooleanControlData::kDefaultIID, kFalse);

	} while (kFalse);
}

/* 
*/
void XDocBkUIDialogObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID& protocol, 
	void* changedBy
)
{
	do
	{
		
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		ASSERT(controlView);
		if (!controlView)
		{
			break;
		}

		// Get the button ID from the view.
		WidgetID widgetID = controlView->GetWidgetID();

		switch (widgetID.Get())
		{
			case kXDocBkUIChangeTemplateButtonWidgetID:
			{
				if (theChange != kTrueStateMessage) {
					break;
				}
				this->ChangeTemplate();
				this->SetOptions();
			}
			break;

			

			case kXDocBkUIUseImagePostImportResponderWidgetID:
			{
				if(theChange == kTrueStateMessage) {			
					this->SetUseImagePostImportResponder(kTrue);
				}
				else if(theChange == kFalseStateMessage) {
					this->SetUseImagePostImportResponder(kFalse);
				}
			}
			break;

			case kXDocBkUIUseXMLTransformerWidgetID:
			{
				if(theChange == kTrueStateMessage) {			
					this->SetUseXMLTransformer(kTrue);
				}
				else if(theChange == kFalseStateMessage) {
					this->SetUseXMLTransformer(kFalse);
				}
			}
			break;

			case kXDocBkUIUseCALSContentHandlerWidgetID:
			{
				if(theChange == kTrueStateMessage) {			
					this->SetUseCALSContentHandler(kTrue);
				}
				else if(theChange == kFalseStateMessage) {
					this->SetUseCALSContentHandler(kFalse);
				}
			}
			break;

			case kXDocBkUISuppliedOverridesPIWidgetID:
			{
				if(theChange == kTrueStateMessage) {			
					this->SetSuppliedOverridesPI(kTrue);
				}
				else if(theChange == kFalseStateMessage) {
					this->SetSuppliedOverridesPI(kFalse);
				}
			}
			break;

			case kXDocBkUIChangeStylesheetButtonWidgetID:
			{
				if (theChange != kTrueStateMessage) {
					break;
				}
				this->ChangeStylesheet();
				this->SetOptions();
			}
			break;

		}
	} while (kFalse);
}

/*
*/
void XDocBkUIDialogObserver::ChangeTemplate()
{
	do
	{
		PMString technotePathTitle(kXDocBkUISetOption1StringKey, PMString::kTranslateDuringCall);
		SDKFileOpenChooser openChooser;
		openChooser.AddAllFiles(); // Not sure INDT shows up
		openChooser.SetTitle(technotePathTitle);
		openChooser.ShowDialog();
		if (!openChooser.IsChosen())
		{
			// No choice, don't proceed
			break;
		}
		PMString file = openChooser.GetPath();
		if (file.empty())
		{
			break;
		}

		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		ASSERT(dialogController);
		if (!dialogController)
		{
			break;
		}
		file.SetTranslatable(kFalse);
		dialogController->SetTextControlData(kXDocBkUITemplateTextEditWidgetID, file);
	} while (kFalse);
}


/* 
*/
void XDocBkUIDialogObserver::SetOptions()
{
	do
	{
		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		ASSERT(dialogController);
		if (!dialogController) {
			break;
		}

        K2Vector<WideString> optionsVec;
        optionsVec.reserve(cXDocBkOptionCardinality);

		PMString templatePath = dialogController->GetTextControlData(kXDocBkUITemplateTextEditWidgetID);
		optionsVec.push_back(WideString(templatePath));
		
		PMString stylesheetPath = dialogController->GetTextControlData(kXDocBkUIStylesheetTextEditWidgetID);
		optionsVec.push_back(WideString(stylesheetPath));

		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade) {
			break;
		}
		facade->SetOptions(optionsVec);
	} while (kFalse);

}

/* DoAttachDetach
*/
void XDocBkUIDialogObserver::DoAttachDetach(const WidgetID& widgetID, const PMIID& pmiid, bool16 attaching)
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData)
		{
			break;
		}
		IControlView* view = panelControlData->FindWidget(widgetID);
		ASSERT(view);
		if (!view)
		{
			break;
		}
		InterfacePtr<ISubject> subject(view, UseDefaultIID());
		ASSERT(subject);
		if (!subject)
		{
			break;
		}

		// We're not IID_IOBSERVER as normal, because we're on a selectable dialog
		if (attaching)
		{
			if (!subject->IsAttached(this, pmiid, IID_IXDOCBKUIWIDGETOBSERVER))
			{
				subject->AttachObserver(this, pmiid, IID_IXDOCBKUIWIDGETOBSERVER);
			}
		}
		else
		{
			if (subject->IsAttached(this, pmiid, IID_IXDOCBKUIWIDGETOBSERVER))
			{
				subject->DetachObserver(this, pmiid, IID_IXDOCBKUIWIDGETOBSERVER);
			}
		}
	} while (kFalse);
}

/*
*/
void XDocBkUIDialogObserver::SetUseImagePostImportResponder(bool16 newState)
{
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		ErrorCode err = facade->SetUsePostImportIterator(newState);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
	} while(kFalse);

}

/*
*/
void XDocBkUIDialogObserver::SetUseCALSContentHandler(bool16 newState)
{
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		ErrorCode err = facade->SetUseCALSContentHandler(newState);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
	} while(kFalse);

}


/*
*/
void XDocBkUIDialogObserver::SetUseXMLTransformer(bool16 newState)
{
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		ErrorCode err = facade->SetUseXMLTransformer(newState);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
	} while(kFalse);

}


/*
*/
void XDocBkUIDialogObserver::SetSuppliedOverridesPI(bool16 newState)
{
	
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		ErrorCode err = facade->SetSuppliedXSLOverridingPI(newState);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
	} while(kFalse);

}



void XDocBkUIDialogObserver::ChangeStylesheet()
{
	do
	{
		PMString stylesheetTitle(kXDocBkUISetOption2StringKey, PMString::kTranslateDuringCall);
		SDKFileOpenChooser openChooser;
		openChooser.AddAllFiles(); // Not sure INDT shows up
		openChooser.SetTitle(stylesheetTitle);
		openChooser.ShowDialog();
		if (!openChooser.IsChosen())
		{
			// No choice, don't proceed
			break;
		}
		PMString file = openChooser.GetPath();
		if (file.empty())
		{
			break;
		}

		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		ASSERT(dialogController);
		if (!dialogController)
		{
			break;
		}
		file.SetTranslatable(kFalse);
		dialogController->SetTextControlData(kXDocBkUIStylesheetTextEditWidgetID, file);
	} while (kFalse);

}
		

		
// End, XDocBkUIDialogObserver.cpp.




