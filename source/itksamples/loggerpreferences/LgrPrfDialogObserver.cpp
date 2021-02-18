//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/loggerpreferences/LgrPrfDialogObserver.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITriStateControlData.h"
#include "IDropDownListController.h"
#include "IDiagnosticLog.h"
#include "IDiagnosticLogger.h"
#include "IDiagLogConfigManager.h"
#include "IDiagLoggerManager.h"
#include "ITextControlData.h"
#include "IStringListControlData.h"
#include "IBoolData.h"

// General includes:
#include "CDialogObserver.h"
// Project includes:
#include "LgrPrfID.h"


/** Implements IObserver based on the partial implementation CDialogObserver.

	
	@ingroup loggerpreferences
*/
class LgrPrfDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		LgrPrfDialogObserver(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. */
		virtual ~LgrPrfDialogObserver() {}

		/**
			Called by the application to allow the observer to attach to the subjects
			to be observed, in this case the dialog's info button widget. If you want
			to observe other widgets on the dialog you could add them here.
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed object changes, in this case when
			any control in the preference dialog is clicked.  It will react by enabling/disabling other controls.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update
		(
			const ClassID& theChange,
			ISubject* theSubject,
			const PMIID& protocol,
			void* changedBy
		);

		/**
			Initialize dialog widgets based on the DiagnosticLogConfiguration_debug|release.xml
		*/
		virtual void InitDialogWidgets();
			
		/**
			Set a tri state control's state
			@param widgetId specifies the widget ID to be changed state.
			@param newValue new value, ITriStateControlData::kUnselected, ITriStateControlData::kUnknown, ITriStateControlData::kSelected
			@param notifyChange specifies if the change of state should be broadcasted.
		*/
		virtual void SelectTriStateControl(const WidgetID& widgetId, ITriStateControlData::TriState newValue, bool16 notifyChange = kFalse );
			
		/**
			Enable/Disable a control
			@param widgetId specifies the widget ID to be changed state.
			@param enable specifies if the control should be enabled.
		*/
		virtual void EnableWidget(const WidgetID& widgetId, bool16 enable );
			
		/**
			Check if a tri-state control is selected or not
			@param widgetId specifies the widget ID to be changed state.
			@return true if the control is selected, false else.
		*/
		virtual bool16 WidgetIsSelected(const WidgetID& widgetId);
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(LgrPrfDialogObserver, kLgrPrfDialogObserverImpl)

/* AutoAttach
*/
void LgrPrfDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		// Attach to other widgets you want to handle dynamically here.
	    this->AttachToWidget(kLgrPrfTurnOnRadioWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfTurnOffRadioWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfTextLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfXMLLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfConsoleLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfCatCmdWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfCatActionWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->AttachToWidget(kLgrPrfCatEventWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
 
		InitDialogWidgets();
	} while (kFalse);
}

/* AutoDetach
*/
void LgrPrfDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		// Detach from other widgets you handle dynamically here.
	    this->DetachFromWidget(kLgrPrfTurnOnRadioWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfTurnOffRadioWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfTextLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfXMLLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfConsoleLoggerWID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfCatCmdWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfCatActionWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	    this->DetachFromWidget(kLgrPrfCatEventWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

	} while (kFalse);
}

/* Update
*/
void LgrPrfDialogObserver::Update
(
	const ClassID& theChange,
	ISubject* theSubject,
	const PMIID& protocol,
	void* changedBy
)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);
	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		ASSERT(controlView);
		if(!controlView) {
			break;
		}
		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();
		switch (theSelectedWidget.Get())
		{
			case	kLgrPrfTextLoggerWID:
			case	kLgrPrfXMLLoggerWID:
			case	kLgrPrfConsoleLoggerWID:
			{
				if (this->WidgetIsSelected(kLgrPrfTextLoggerWID) || this->WidgetIsSelected(kLgrPrfXMLLoggerWID) || this->WidgetIsSelected(kLgrPrfConsoleLoggerWID))
				{
					this->EnableWidget(kLgrPrfUseDatabaseWID, kTrue);
					this->EnableWidget(kLgrPrfLogDetailWID, kTrue);
					this->EnableWidget(kLgrPrfLogDetailDropdownWID, kTrue);
					this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kTrue);
				}
				else if (!this->WidgetIsSelected(kLgrPrfTextLoggerWID) && !this->WidgetIsSelected(kLgrPrfXMLLoggerWID) && !this->WidgetIsSelected(kLgrPrfConsoleLoggerWID))
				{
					this->EnableWidget(kLgrPrfUseDatabaseWID, kFalse);
					this->EnableWidget(kLgrPrfLogDetailWID, kFalse);
					this->EnableWidget(kLgrPrfLogDetailDropdownWID, kFalse);
					this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kFalse);
				}
			}
			break;
			case	kLgrPrfTurnOnRadioWID:
			{
				if (theChange == kTrueStateMessage)
				{
					this->EnableWidget(kLgrPrfLoggersGroupWID, kTrue);

					if (this->WidgetIsSelected(kLgrPrfTextLoggerWID) || this->WidgetIsSelected(kLgrPrfXMLLoggerWID) || this->WidgetIsSelected(kLgrPrfConsoleLoggerWID))
					{
						this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kTrue);
					}
				}
			}
			break;
			case	kLgrPrfTurnOffRadioWID:
			{
				if (theChange == kTrueStateMessage)
				{
					this->EnableWidget(kLgrPrfLoggersGroupWID, kFalse);
					this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kFalse);
				}
			}
			break;
			case	kLgrPrfCatCmdWidgetID:
			{
				if (this->WidgetIsSelected(kLgrPrfCatCmdWidgetID))
				{
					this->EnableWidget(kLgrPrfCmdIncludeWidgetID, kTrue);
					this->EnableWidget(kLgrPrfCmdExcludeWidgetID, kTrue);
				}
				else
				{
					this->EnableWidget(kLgrPrfCmdIncludeWidgetID, kFalse);
					this->EnableWidget(kLgrPrfCmdExcludeWidgetID, kFalse);
				}
			}
			break;
			case	kLgrPrfCatActionWidgetID:
			{
				if (this->WidgetIsSelected(kLgrPrfCatActionWidgetID))
				{
					this->EnableWidget(kLgrPrfActionIncludeWidgetID, kTrue);
					this->EnableWidget(kLgrPrfActionExcludeWidgetID, kTrue);
				}
				else
				{
					this->EnableWidget(kLgrPrfActionIncludeWidgetID, kFalse);
					this->EnableWidget(kLgrPrfActionExcludeWidgetID, kFalse);
				}
			}
			break;
			case	kLgrPrfCatEventWidgetID:
			{
				if (this->WidgetIsSelected(kLgrPrfCatEventWidgetID))
				{
					this->EnableWidget(kLgrPrfEventListBoxWidgetID, kTrue);
				}
				else
				{
					this->EnableWidget(kLgrPrfEventListBoxWidgetID, kFalse);
				}
			}
			break;
		}
	} while (kFalse);
}

/* InitDialogWidgets
*/
void LgrPrfDialogObserver::InitDialogWidgets()
{
	do
	{
	    InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iDiagnosticLog);
		if(!iDiagnosticLog) {
			break;
		}
	    InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
		ASSERT(iConfigManager);
		if(!iConfigManager) {
			break;
		}
		InterfacePtr<IDiagLoggerManager> iLoggerManager(iDiagnosticLog->QueryDiagLoggerManager());
		ASSERT(iLoggerManager);
		if(!iLoggerManager) {
			break;
		}
		// init the logger checkbox
		bool16	turnOnView = kFalse;
		bool16	consoleLog = kFalse;
		for (int32 i=0; i<iLoggerManager->GetNumLoggers(); i++)
		{
			IDiagnosticLogger* logger = iLoggerManager->GetNthLogger(i);
			ASSERT(logger);
			if(!logger) {
				break;
			}
			bool16	loggerEnabled =	logger->IsEnabled();
			if (!turnOnView && loggerEnabled)
				turnOnView = kTrue;
			if (logger->GetName() == PMString("text"))
				this->SelectTriStateControl(kLgrPrfTextLoggerWID, loggerEnabled ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue );
			else if (logger->GetName() == PMString("xml"))
				this->SelectTriStateControl(kLgrPrfXMLLoggerWID, loggerEnabled ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue );
			else if (logger->GetName() == PMString("console"))
			{
				this->SelectTriStateControl(kLgrPrfConsoleLoggerWID, loggerEnabled ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue );
				consoleLog = kTrue;
			}
		}
		InterfacePtr<IPanelControlData> thePanel(this, UseDefaultIID());
		ASSERT(thePanel);
		if(!thePanel) {
			break;
		}
		IControlView* widget;
		widget = thePanel->FindWidget(kLgrPrfLogDetailDropdownWID);
		ASSERT(widget);
		if(!widget) {
			break;
		}
		// if can't find the console logger, hide the control
		if (!consoleLog)
		{
			IControlView* controlView = thePanel->FindWidget(kLgrPrfConsoleLoggerWID);
			ASSERT(controlView);
			if(!controlView) {
				break;
			}
			controlView->HideView();			
		}
		// init the use database checkbox
		this->SelectTriStateControl(kLgrPrfUseDatabaseWID, iConfigManager->GetLoadIDDatabase() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue );
		
		// init the detail level dropdown
		InterfacePtr<IDropDownListController> ddController(widget, IID_IDROPDOWNLISTCONTROLLER);
		ASSERT(ddController);
		if(!ddController) {
			break;
		}
		ddController->Select(iConfigManager->GetLoggingLevel());
		
		
		// init the category
		if (iConfigManager->GetCategoryLogging(IDiagLogConfigManager::kDiagLogCommand))
		{
			this->SelectTriStateControl(kLgrPrfCatCmdWidgetID, ITriStateControlData::kSelected, kTrue );
			this->EnableWidget(kLgrPrfCmdIncludeWidgetID, kTrue);
			this->EnableWidget(kLgrPrfCmdExcludeWidgetID, kTrue);
		}
		else
		{
			this->SelectTriStateControl(kLgrPrfCatCmdWidgetID, ITriStateControlData::kUnselected, kTrue );
			this->EnableWidget(kLgrPrfCmdIncludeWidgetID, kFalse);
			this->EnableWidget(kLgrPrfCmdExcludeWidgetID, kFalse);
		}
		if (iConfigManager->GetCategoryLogging(IDiagLogConfigManager::kDiagLogAction))
		{
			this->SelectTriStateControl(kLgrPrfCatActionWidgetID, ITriStateControlData::kSelected, kTrue );
			this->EnableWidget(kLgrPrfActionIncludeWidgetID, kTrue);
			this->EnableWidget(kLgrPrfActionExcludeWidgetID, kTrue);
		}
		else
		{
			this->SelectTriStateControl(kLgrPrfCatActionWidgetID, ITriStateControlData::kUnselected, kTrue );
			this->EnableWidget(kLgrPrfActionIncludeWidgetID, kFalse);
			this->EnableWidget(kLgrPrfActionExcludeWidgetID, kFalse);
		}
		
		if (iConfigManager->GetCategoryLogging(IDiagLogConfigManager::kDiagLogEvents))
		{
			this->SelectTriStateControl(kLgrPrfCatEventWidgetID, ITriStateControlData::kSelected, kTrue );
			this->EnableWidget(kLgrPrfEventListBoxWidgetID, kTrue);
		}
		else
		{
			this->SelectTriStateControl(kLgrPrfCatEventWidgetID, ITriStateControlData::kUnselected, kTrue );
			this->EnableWidget(kLgrPrfEventListBoxWidgetID, kFalse);
		}

		if (iConfigManager->GetLogging()) 
		{
			this->SelectTriStateControl(kLgrPrfTurnOnRadioWID, ITriStateControlData::kSelected, kTrue );
			this->EnableWidget(kLgrPrfLoggersGroupWID, kTrue);
			if (turnOnView)
			{
				this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kTrue);
			}
			else
			{
				this->EnableWidget(kLgrPrfUseDatabaseWID, kFalse);
				this->EnableWidget(kLgrPrfLogDetailDropdownWID, kFalse);
			}
		}
		else
		{
			this->SelectTriStateControl(kLgrPrfTurnOffRadioWID, ITriStateControlData::kSelected, kTrue );
			this->EnableWidget(kLgrPrfLoggersGroupWID, kFalse);
			this->EnableWidget(kLgrPrfOptionsFrameWidgetID, kFalse);
		}
	} while (kFalse);
	
}

/* SelectTriStateControl
*/
void LgrPrfDialogObserver::SelectTriStateControl(const WidgetID& widgetId, ITriStateControlData::TriState newValue, bool16 notifyChange )
{
	do {
		InterfacePtr<IPanelControlData>	panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if(!panelData) {
			break;
		}
			
		IControlView* controlView = panelData->FindWidget(widgetId);
		ASSERT(controlView);
		if(!controlView) {
			break;
		}		
		InterfacePtr<ITriStateControlData> controlData(controlView, UseDefaultIID());
		ASSERT(controlData);
		if(!controlData) {
			break;
		}		
		if( newValue == ITriStateControlData::kUnknown )
		{
			controlData->SetState( ITriStateControlData::kUnselected, kTrue, notifyChange );
			controlView->Enable( kFalse );
		}
		else
		{
			controlData->SetState( newValue, kTrue, notifyChange );
			controlView->Enable( kTrue );
		}
	} while (kFalse);
}

/* EnableWidget
*/
void LgrPrfDialogObserver::EnableWidget(const WidgetID& widgetId, bool16 enable )
{
	do {
		InterfacePtr<IPanelControlData>	thePanel(this, UseDefaultIID());
		ASSERT(thePanel);
		if(!thePanel) {
			break;
		}
		IControlView* widget= thePanel->FindWidget(widgetId);
		ASSERT(widget);
		if (!widget) {
			break;
		}	
		if (enable)	{
			widget->Enable();
		}
		else {
			widget->Disable();
		}
	} while (kFalse);
}

/* EnableWidget
*/
bool16 LgrPrfDialogObserver::WidgetIsSelected(const WidgetID& widgetId)
{
	bool16 isSelected = kFalse;
	
	do {
		InterfacePtr<IPanelControlData>	thePanel(this, UseDefaultIID());
		ASSERT(thePanel);
		if(!thePanel) {
			break;
		}
		IControlView* widget = thePanel->FindWidget(widgetId);
		ASSERT(widget);
		if (!widget) {
			break;
		}	
		InterfacePtr<ITriStateControlData> widgetData(widget, UseDefaultIID());
		ASSERT(widgetData);
		if (!widgetData) {
			break;
		}
		if (widgetData->IsSelected()) {
			isSelected = kTrue;
		}
	} while (kFalse);
	return isSelected;
}

//  Code generated by DollyXs code generator
