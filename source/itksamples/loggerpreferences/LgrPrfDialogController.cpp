//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/loggerpreferences/LgrPrfDialogController.cpp $
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
#include "IActiveContext.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "IDropDownListController.h"
#include "IDiagnosticLog.h"
#include "IDiagnosticLogger.h"
#include "IDiagLogConfigManager.h"
#include "IDiagLoggerManager.h"
#include "IBoolData.h"
#include "IStringListControlData.h"
#include "ITreeViewMgr.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"

// General includes:
#include "CDialogController.h"
#include <sstream>
// Project includes:
#include "LgrPrfID.h"

/** LgrPrfDialogController
	Methods allow for the initialization, validation, and application of dialog widget
	values.
	Implements IDialogController based on the partial implementation CDialogController.

	
	The main purpose of this plug-in is to provide a view to the application logging service's configuration file.  
	See Diagnostic Logger technote about the application's logging service for more configuration details. This plug-in
	does not provide configuration for all the available settings.  The main purpose is to demonstrate how to use the
	IDiagLogConfigManager to change the setting during run time.
	
	Note: When you use this plug-in to change the configuration file, make sure the DiagnosticLogConfiguration_(debug|release).xml
			is close or InDesign will crash.
	
	@ingroup loggerpreferences
*/
class LgrPrfDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		LgrPrfDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~LgrPrfDialogController() {}

		/** Set up the event drop down. 

			@param context IN the active context
		*/
		virtual void  InitializeDialogFields(IActiveContext* context);

		/** Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

		/** Retrieve an editbox widget's text data.
			@param panelControlData identifies the IPanelControlData where the widget is on.
			@param widgetId identifies the widget on which to act.
			@return text in PMString.
		*/
		PMString GetEditTextBoxData(const IPanelControlData* panelControlData, const WidgetID& widgetId);

		/** Parse a PMString using "," as delimiter, get each token as number and add it to the configuration as include or exclude list.
			@param listString identifies the PMString to parse.
			@param category identifies the category to add on in the configuration.
			@param category identifies the list to add on in the configuration.
			@param iConfigManager identifies the IDiagLogConfigManager.
		*/
		void ParseAndAddList(PMString listString, IDiagLogConfigManager::DiagLogCategory category, IDiagLogConfigManager::ListType listType, IDiagLogConfigManager* iConfigManager);
		
		/** Loop through all the available loggers and enable them if user wishes to.
		*/
		void EnableLoggers();
		
		/** configure the logging setting so the <iddatabase> element is set as user wishes.
		*/
		void SetUseDatabase(IDiagLogConfigManager* iConfigManager);
		
		/** configure the logging setting so the <category> element  for command is set as user wishes. it will
			also set up (multiple) include/exclude list if user supplies the list
		*/
		void SetCommandCategory(IDiagLogConfigManager* iConfigManager);
		
		/** configure the logging setting so the <category> element  for action is set as user wishes. it will
			also set up (multiple) include/exclude list if user supplies the list
		*/
		void SetActionCategory(IDiagLogConfigManager* iConfigManager);
		
		/** configure the logging setting so the <category> element and for event its associated <eventtype> is 
			set as user wishes.
		*/
		void SetEventCategory(IDiagLogConfigManager* iConfigManager);
		
		/** configure the logging setting so the <logging> element and its level attributes is set as user wishes.
		*/
		void SetLoggingLevel(IDiagLogConfigManager* iConfigManager);
};

CREATE_PMINTERFACE(LgrPrfDialogController, kLgrPrfDialogControllerImpl)


/* ApplyFields
*/
void LgrPrfDialogController::InitializeDialogFields(IActiveContext* myContext)
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

		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}

		// Acquire the interfaces we need to set up the strings in the list.
		IControlView* controlView = panelControlData->FindWidget(kLgrPrfEventListBoxWidgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}
		InterfacePtr<ITreeViewHierarchyAdapter> iModelTree(controlView, UseDefaultIID());
		if(iModelTree)
		{
			NodeID root = iModelTree->GetRootNode();
			for (int32 i=IEvent::kActivate; i<IEvent::kEndOfEventTypes; i++)
			{
				if (iConfigManager->GetLogEvent((IEvent::EventType)i))
				{
					NodeID_rv	nthNode = iModelTree->GetNthChild(root, i-1);
					InterfacePtr<ITreeViewController> 	controller(controlView, UseDefaultIID());
					controller->Select(nthNode);
				}	
			}
		}
	} while(false);
}

/* ApplyFields
*/
void LgrPrfDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
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
	    	
    	// enable logger
    	EnableLoggers();
    	
		// set use database
		SetUseDatabase(iConfigManager);

		// set logging level
		SetLoggingLevel(iConfigManager);

		// log command?
		SetCommandCategory(iConfigManager);
		
		// log action?
		SetActionCategory(iConfigManager);
		
		// log event?
		SetEventCategory(iConfigManager);

		if (GetSelectedClusterWidget(kLgrPrfMasterSwitchClusterWID) == kLgrPrfTurnOnRadioWID) {
			// turn on master switch
		    iConfigManager->SetLogging(kTrue);
		}
		else {
		    iConfigManager->SetLogging(kFalse);
		}
		iConfigManager->Save();
		iConfigManager->Load();
	} while (kFalse);
}

void LgrPrfDialogController::EnableLoggers()
{
	do
	{
	    InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iDiagnosticLog);
		if(!iDiagnosticLog) {
			break;
		}
		InterfacePtr<IDiagLoggerManager> iLoggerManager(iDiagnosticLog->QueryDiagLoggerManager());
		ASSERT(iLoggerManager);
		if(!iLoggerManager) {
			break;
		}
		for (int32 i=0; i<iLoggerManager->GetNumLoggers(); i++) {
			IDiagnosticLogger* logger = iLoggerManager->GetNthLogger(i);
			ASSERT(logger);
			if(!logger) {
				break;
			}
			if (logger->GetName() == PMString("text")) {
				if (GetTriStateControlData(kLgrPrfTextLoggerWID) == ITriStateControlData::kSelected) {
					logger->Enable(kTrue);
				}
				else {
					logger->Enable(kFalse);
				}
			}
			else if (logger->GetName() == PMString("xml")) {
				if (GetTriStateControlData(kLgrPrfXMLLoggerWID) == ITriStateControlData::kSelected) {
					logger->Enable(kTrue);
				}
				else {
					logger->Enable(kFalse);
				}
			}
			else if (logger->GetName() == PMString("console")) {
				if (GetTriStateControlData(kLgrPrfConsoleLoggerWID) == ITriStateControlData::kSelected) {
					logger->Enable(kTrue);
				}
				else {
					logger->Enable(kFalse);
				}
			}
		}
	} while (kFalse);
}

void LgrPrfDialogController::SetUseDatabase(IDiagLogConfigManager* iConfigManager)
{
	if (GetTriStateControlData(kLgrPrfUseDatabaseWID) == ITriStateControlData::kSelected) {
		iConfigManager->SetLoadIDDatabase(kTrue);
	}
	else {
		iConfigManager->SetLoadIDDatabase(kFalse);
	}
}

void LgrPrfDialogController::SetCommandCategory(IDiagLogConfigManager* iConfigManager)
{
	do
	{
		PMString	listString;
		if (GetTriStateControlData(kLgrPrfCatCmdWidgetID) == ITriStateControlData::kSelected) {
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogCommand, kTrue);
		}
		else {
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogCommand, kFalse);
		}
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		listString = GetEditTextBoxData(panelControlData, kLgrPrfCmdIncludeWidgetID);
		listString.SetTranslatable(kFalse);
		ParseAndAddList(listString, IDiagLogConfigManager::kDiagLogCommand, IDiagLogConfigManager::kIncludeList, iConfigManager);
		listString = GetEditTextBoxData(panelControlData, kLgrPrfCmdExcludeWidgetID);
		listString.SetTranslatable(kFalse);
		ParseAndAddList(listString, IDiagLogConfigManager::kDiagLogCommand, IDiagLogConfigManager::kExcludeList, iConfigManager);
	} while (kFalse);
}

void LgrPrfDialogController::SetActionCategory(IDiagLogConfigManager* iConfigManager)
{
	do
	{
		PMString	listString;
		if (GetTriStateControlData(kLgrPrfCatActionWidgetID) == ITriStateControlData::kSelected){
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogAction, kTrue);
		}
		else {
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogAction, kFalse);
		}
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		listString = GetEditTextBoxData(panelControlData, kLgrPrfActionIncludeWidgetID);
		listString.SetTranslatable(kFalse);
		ParseAndAddList(listString, IDiagLogConfigManager::kDiagLogAction, IDiagLogConfigManager::kIncludeList, iConfigManager);
		listString = GetEditTextBoxData(panelControlData, kLgrPrfActionExcludeWidgetID);
		listString.SetTranslatable(kFalse);
		ParseAndAddList(listString, IDiagLogConfigManager::kDiagLogAction, IDiagLogConfigManager::kExcludeList, iConfigManager);
	} while (kFalse);
}

void LgrPrfDialogController::SetEventCategory(IDiagLogConfigManager* iConfigManager)
{
	do
	{
		if (GetTriStateControlData(kLgrPrfCatEventWidgetID) == ITriStateControlData::kSelected) {
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogEvents, kTrue);
		}
		else {
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogEvents, kFalse);
		}
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(kLgrPrfEventListBoxWidgetID);
		ASSERT(controlView);
		if(!controlView) {
			break;
		}
		InterfacePtr<ITreeViewController> 	controller(controlView, UseDefaultIID());
		ASSERT(controller);
		if(!controller) {
			break;
		}
		InterfacePtr<ITreeViewHierarchyAdapter> adapter(controlView, UseDefaultIID());
		ASSERT(adapter);
		if(!adapter) {
			break;
		}
		
		NodeID root = adapter->GetRootNode();
		for (int32 i=IEvent::kActivate; i<IEvent::kEndOfEventTypes; i++)
		{
			NodeID_rv	nthNode = adapter->GetNthChild(root, i-1);
			if (controller->IsSelected(nthNode))
				iConfigManager->SetLogEvent((IEvent::EventType)i, kTrue);
			else
				iConfigManager->SetLogEvent((IEvent::EventType)i, kFalse);
		}
	} while (kFalse);
}

void LgrPrfDialogController::SetLoggingLevel(IDiagLogConfigManager* iConfigManager)
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(kLgrPrfLogDetailDropdownWID);
		ASSERT(controlView);
		if(!controlView) {
			break;
		}
		InterfacePtr<IDropDownListController> dropDown(controlView, UseDefaultIID());
		ASSERT(dropDown);
		if(!dropDown) {
			break;
		}
		iConfigManager->SetLoggingLevel((IDiagLogConfigManager::DiagLoggingLevel)dropDown->GetSelected());
	} while (kFalse);
}

PMString LgrPrfDialogController::GetEditTextBoxData(const IPanelControlData* panelControlData, const WidgetID& widgetId)
{
	PMString	text;
	do
	{
		IControlView* widgetControlView = panelControlData->FindWidget(widgetId);
		ASSERT(widgetControlView);
		if(!widgetControlView) {
			break;
		}

		InterfacePtr<ITextControlData> textControlData(widgetControlView, UseDefaultIID());
		ASSERT(textControlData);
		if(!textControlData) {
			break;
		}
		text = textControlData->GetString();
	} while (kFalse);
	return text;
}

void LgrPrfDialogController::ParseAndAddList(PMString listString, IDiagLogConfigManager::DiagLogCategory category, IDiagLogConfigManager::ListType listType, IDiagLogConfigManager* iConfigManager)
{
			
	PMString*	item = nil;
	int32		id, i = 1;
	bool16		moreItem = kTrue;
	do {
		item = listString.GetItem(",", i++);
		if (item) {
			if (item->Contains("0x") || (item->Contains("0X"))) {
				std::string src(item->GrabCString());
				std::istringstream iStream(src);
				
				iStream >> std::hex >> id;	
				iConfigManager->AddCategoryList(category, listType, id);
				
			}
			delete item;
		}
		else
			moreItem = kFalse;
	} while (moreItem);
}
//  Code generated by DollyXs code generator
