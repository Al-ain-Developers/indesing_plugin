//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvtui/PDFVTUIDialogController.cpp $
//  
//  Owner: Devtech
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
// General includes:
#include "CDialogController.h"
// Project includes:
#include "PDFVTUIID.h"
#include "PDFVTID.h"
#include "IDataSourceData.h"
#include "IPDFExportSetupProvider.h"
#include "CAlert.h"
#include "ISession.h"
#include "ILayoutUIUtils.h"
#include "Utils.h"
#include "IDocument.h"
#include "IExportProvider.h"
#include "IPageList.h"
#include "SDKFileHelper.h"
#include "StringUtils.h"

#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"

#include <string>
#include <vector>
#include <map>

#include "PDFVTUtils.h"
#include "IDropDownListSelection.h"

using namespace std;

/** PDFVTUIDialogController
	Methods allow for the initialization, validation, and application of dialog widget
	values.
	Implements IDialogController based on the partial implementation CDialogController.

	@ingroup pdfvtui
*/
class PDFVTUIDialogController : public CDialogController
{
    public:
	    /** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PDFVTUIDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~PDFVTUIDialogController() {}

		/** Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
        virtual void InitializeDialogFields(IActiveContext* dlgContext);

		/** Validate the values in the widgets.
			By default, the widget with ID kOKButtonWidgetID causes
			ValidateFields to be called. When all widgets are valid,
			ApplyFields will be called.
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.
		*/
        virtual WidgetID ValidateDialogFields(IActiveContext* myContext);

		/** Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

    private:

		/** Gets the selection of a dropdown list widget.
			@param id id of the dropdown list widget.
			@param index index of the selected item.
			@param content content of the selected item.
			@return kTrue if succeed, kFalse otherwise.
		*/
		bool16 GetDropDownListSelection(int32 id, int32& index, PMString& content);

		/** Retrieve the CIP4 metadata mapping from the document
			and changes the selection of dropdown list widgets
			accordingly.
			@param keyList key list of the datasource file.
		*/
		void InitSelections(const vector<string>& keyList);
};

CREATE_PMINTERFACE(PDFVTUIDialogController, kPDFVTUIDialogControllerImpl)

/* ApplyFields
*/
void PDFVTUIDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	CDialogController::InitializeDialogFields(dlgContext);

	do
	{
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		InterfacePtr<IDataSourceData> dataSourceData(doc, UseDefaultIID());
		if (dataSourceData == nil)
		{
			ASSERT_FAIL("PDFVTUIDialogController::InitializeDialogFields: IDataSourceData is nil!");
			break;
		}

		PMString filePath = dataSourceData->GetPath();
		filePath.SetTranslatable(kFalse);
		SetTextControlData(kPDFVTUIDataSourceFileTextWidgetID, filePath);
		
		vector<string> keyList;
		PDFVTUtils::GetDataSourceKeyList(keyList, WideString(filePath));
		InitSelections(keyList);
	} while(kFalse);
}

/* ValidateFields
*/
WidgetID PDFVTUIDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);
	// Put code to validate widget values here.
	return result;
}

/* ApplyFields
*/
void PDFVTUIDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{        
    IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
    UIDRef docUIDRef = ::GetUIDRef(doc);

    InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kWritePDFVTDataSourceInfoCmdBoss));
    cmd->SetItemList(UIDList(docUIDRef));

    InterfacePtr<IDataSourceData> data(cmd, UseDefaultIID());        
    PMString filePath = this->GetTextControlData(kPDFVTUIDataSourceFileTextWidgetID);
    data->SetPath(WideString(filePath));	

	int32 selectedIndex = 0;
	PMString selectedString;
	
	map<WideString, WideString> cip4Mapping;

	map<int32, WideString> widgetIDToCIP4Mapping;
	widgetIDToCIP4Mapping[kPDFVTUIFirstNameDropDownListWidgetID] = WideString("FirstName");
	widgetIDToCIP4Mapping[kPDFVTUILastNameDropDownListWidgetID] = WideString("LastName");
	widgetIDToCIP4Mapping[kPDFVTUICityDropDownListWidgetID] = WideString("City");
	widgetIDToCIP4Mapping[kPDFVTUIPostalCodeDropDownListWidgetID] = WideString("PostalCode");
	widgetIDToCIP4Mapping[kPDFVTUICountryDropDownListWidgetID] = WideString("Country");
	
	for (map<int32, WideString>::const_iterator it = widgetIDToCIP4Mapping.begin(); 
		it != widgetIDToCIP4Mapping.end(); it++)
	{
		if (GetDropDownListSelection(it->first, selectedIndex, selectedString))
		{
			if (selectedIndex != 0)
			{
				WideString tmp(selectedString);
				cip4Mapping[tmp] = it->second;
			}
		}
	}	

	data->SetCIP4Mapping(cip4Mapping);

    ErrorCode errorCode = CmdUtils::ProcessCommand(cmd);
    if (errorCode != kSuccess)
    {        
		CAlert::ModalAlert(kPDFVTUIWriteDataSourceErrorStringKey,
			    kOKString,
				kNullString,
				kNullString,
				1,
				CAlert::eInformationIcon
		);
    }
}

bool16 PDFVTUIDialogController::GetDropDownListSelection(int32 id, int32& index, PMString& content)
{
	InterfacePtr<IPanelControlData> pPanelData(QueryIfNilElseAddRef(nil));
	IControlView* dropDownListControlView = pPanelData->FindWidget(id);
	if (dropDownListControlView == nil)
	{
		return kFalse;
	}
	InterfacePtr<IDropDownListController> controller(dropDownListControlView, UseDefaultIID());
	index = controller->GetSelected();
	if (index != IDropDownListController::kNoSelection)
	{
		InterfacePtr<IStringListControlData> pDropDownStringListController(controller, UseDefaultIID());
		content = pDropDownStringListController->GetString(index);
	}
	return kTrue;
}

void PDFVTUIDialogController::InitSelections(const vector<string>& keyList)
{	
	K2Vector<int32> dropDownLists;
	dropDownLists.push_back(kPDFVTUIFirstNameDropDownListWidgetID);
	dropDownLists.push_back(kPDFVTUILastNameDropDownListWidgetID);
	dropDownLists.push_back(kPDFVTUICityDropDownListWidgetID);
	dropDownLists.push_back(kPDFVTUIPostalCodeDropDownListWidgetID);
	dropDownLists.push_back(kPDFVTUICountryDropDownListWidgetID);

	size_t size = dropDownLists.size();
	ASSERT(size < 32767);

	InterfacePtr<IPanelControlData> pPanelData(this, UseDefaultIID());
	for (int32 i = 0; i < size; i++)
	{
		IControlView* pDropDownListControlView(pPanelData->FindWidget(dropDownLists[i]));
		InterfacePtr<IDropDownListController> pDropDownListController(pDropDownListControlView, UseDefaultIID());

		if (pDropDownListControlView == nil)
		{
			ASSERT_FAIL("PDFVTUIDialogController::Update: DropDownListControlView is nil!");
			break;
		}

		InterfacePtr<IStringListControlData> pDropDownStringListController(pDropDownListControlView, UseDefaultIID());
		pDropDownStringListController->Clear();
		pDropDownStringListController->AddString(kPDFVTUICIP4UnmappedKey);
		for (size_t j = 0; j < keyList.size(); j++)
		{
			WideString ws;
			StringUtils::ConvertUTF8ToWideString(keyList[j], ws);
			pDropDownStringListController->AddString(PMString(ws).SetTranslatable(kFalse));
		}
		pDropDownListController->Select(0, kTrue, kFalse);
	}

	InterfacePtr<IDropDownListSelection> pDropDownListSelection(this, UseDefaultIID());
	pDropDownListSelection->Init();

	IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	InterfacePtr<IDataSourceData> dataSourceData(doc, UseDefaultIID());
	map<WideString, WideString> cip4Mapping = dataSourceData->GetCIP4Mapping();

	for (map<WideString, WideString>::const_iterator it = cip4Mapping.begin(); it != cip4Mapping.end(); it++)
	{
		WideString key = it->first;
		WideString value = it->second;

		int32 dropDownListToFind = kInvalidWidgetID.Get();
		if (value == WideString("FirstName"))
		{
			dropDownListToFind = kPDFVTUIFirstNameDropDownListWidgetID;
		}
		else if (value == WideString("LastName"))
		{
			dropDownListToFind = kPDFVTUILastNameDropDownListWidgetID;
		}
		else if (value == WideString("City"))
		{
			dropDownListToFind = kPDFVTUICityDropDownListWidgetID;
		}
		else if (value == WideString("PostalCode"))
		{
			dropDownListToFind = kPDFVTUIPostalCodeDropDownListWidgetID;
		}
		else if (value == WideString("Country"))
		{
			dropDownListToFind = kPDFVTUICountryDropDownListWidgetID;
		}

		if (dropDownListToFind == kInvalidWidgetID.Get())
		{
			continue;
		}

		IControlView* pDropDownListControlView(pPanelData->FindWidget(dropDownListToFind));
		InterfacePtr<IDropDownListController> pDropDownListController(pDropDownListControlView, UseDefaultIID());
		InterfacePtr<IStringListControlData> pDropDownStringListController(pDropDownListControlView, UseDefaultIID());
		int32 index = pDropDownStringListController->GetIndex(PMString(key));
		if (index == IStringListControlData::kInvalidStringIndex)
		{
			continue;
		}
		pDropDownListController->Select(index, kTrue, kFalse);
		pDropDownListSelection->SetSelection(dropDownListToFind, index);
		
		for (int32 i = 0; i < size; i++)
		{
			if (dropDownLists[i] == dropDownListToFind)
			{
				continue;
			}
			IControlView* pDropDownListControlView1(pPanelData->FindWidget(dropDownLists[i]));
			InterfacePtr<IDropDownListController> pDropDownListController1(pDropDownListControlView1, UseDefaultIID());
			InterfacePtr<IStringListControlData> pDropDownStringListController1(pDropDownListControlView1, UseDefaultIID());
			pDropDownStringListController1->Disable(index, kTrue, kFalse);
		}
	}	
}

//  Code generated by DollyXs code generator
