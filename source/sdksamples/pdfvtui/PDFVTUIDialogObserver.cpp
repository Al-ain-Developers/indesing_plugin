//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvtui/PDFVTUIDialogObserver.cpp $
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
#include "IControlView.h"
#include "IBooleanControlData.h"
#include "ITextControlData.h"
#include "IDialogController.h"
#include "IPanelControlData.h"
#include "ISubject.h"

// General includes:
#include "CDialogObserver.h"
#include "SDKFileHelper.h"
#include "FileUtils.h"
#include "FileTypeRegistry.h"
#include "Utils.h"
#include "IDocument.h"
#include "IPanelControlData.h"
#include "IDropDownListController.h"
#include "IStringListControlData.h"
#include "StringUtils.h"
#include "StreamUtil.h"
#include "CAlert.h"

// Project includes:
#include "PDFVTUIID.h"
#include "IDropDownListSelection.h"
#include "IDataSourceData.h"
#include "PDFVTUtils.h"

#include <string>
#include <set>

using namespace std;

/** Implements IObserver based on the partial implementation CDialogObserver.

	@ingroup pdfvtui

*/
class PDFVTUIDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/		
		PDFVTUIDialogObserver(IPMUnknown* boss);

		/** Destructor. */
		virtual ~PDFVTUIDialogObserver() {}

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
			the dialog's info button is clicked.
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

    private:
		/** IDs of all the dropdown lists.
		*/
		set<int32> fDropDownLists;

		/** Resets the cached previous selections of all the
			dropdown lists.
			@param keyList key list read from the datasource file.
		*/
		void ResetSelections(const vector<string>& keyList);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PDFVTUIDialogObserver, kPDFVTUIDialogObserverImpl)

PDFVTUIDialogObserver::PDFVTUIDialogObserver(IPMUnknown* boss) : CDialogObserver(boss)
{		
	fDropDownLists.insert(kPDFVTUIFirstNameDropDownListWidgetID);
	fDropDownLists.insert(kPDFVTUILastNameDropDownListWidgetID);
	fDropDownLists.insert(kPDFVTUICityDropDownListWidgetID);
	fDropDownLists.insert(kPDFVTUIPostalCodeDropDownListWidgetID);
	fDropDownLists.insert(kPDFVTUICountryDropDownListWidgetID);
}

/* AutoAttach
*/
void PDFVTUIDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);

		if(!panelControlData)
		{
			break;
		}

		// Attach to other widgets you want to handle dynamically here.
		AttachToWidget(kPDFVTUIFindDataSourceFileButtonWidgetID, IBooleanControlData::kDefaultIID, panelControlData);
		AttachToWidget(kPDFVTUIDataSourceFileTextWidgetID, ITextControlData::kDefaultIID, panelControlData);
		AttachToWidget(kPDFVTUIFirstNameDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		AttachToWidget(kPDFVTUILastNameDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);		
		AttachToWidget(kPDFVTUICityDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		AttachToWidget(kPDFVTUIPostalCodeDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		AttachToWidget(kPDFVTUICountryDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	} while (kFalse);
}

/* AutoDetach
*/
void PDFVTUIDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData)
		{
			break;
		}

		// Detach from other widgets you handle dynamically here.
		DetachFromWidget(kPDFVTUIFindDataSourceFileButtonWidgetID, IBooleanControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUIDataSourceFileTextWidgetID, ITextControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUIFirstNameDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUILastNameDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUICityDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUIPostalCodeDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kPDFVTUICountryDropDownListWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	} while (kFalse);
}

/* Update
*/
void PDFVTUIDialogObserver::Update
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

		if(!controlView)
		{
			break;
		}

		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();

		// Check for Cancel button.
        if (theSelectedWidget == kCancelButton_WidgetID && theChange == kTrueStateMessage)
		{
            break;
        }

        // Check for OK button.
        if (theSelectedWidget == kOKButtonWidgetID && theChange == kTrueStateMessage)
		{
            break;
        }

		if (theSelectedWidget == kPDFVTUIFindDataSourceFileButtonWidgetID && theChange == kTrueStateMessage)
		{
			SDKFileOpenChooser fileChooser;
            fileChooser.SetTitle(kPDFVTUIDataSourceFileKey);
			
			SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);
			fileChooser.AddFilter(macFileCreator, "txt", "TEXT file(txt)");
            fileChooser.AddFilter(kTEXTFileTypeInfoID, kPDFVTUIFileTypeTextKey);
            fileChooser.AddFilter(kCSVFileTypeInfoID, kPDFVTUIFileTypeCSVKey);
			
			fileChooser.ShowDialog();
			if (fileChooser.IsChosen())
			{
				IDFile chosenFile = fileChooser.GetIDFile();
				SDKFileHelper helper(chosenFile);
				PMString filePath = helper.GetPath();
				filePath.SetTranslatable(kFalse);

				WideString ws(filePath);
				IDFile dataSourceFile = FileUtils::PMStringToSysFile(ws);
				InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(dataSourceFile));
				PDFVTUtils::Encoding enc = PDFVTUtils::DetectEncoding(stream);
				stream->Close();
				if (enc == PDFVTUtils::kUnsupportedEncoding)
				{
					CAlert::ErrorAlert(kUnsupportedEncodingWarningKey);
					break;
				}

				InterfacePtr<IDialogController> dlgController(this, UseDefaultIID());
				dlgController->SetTextControlData(kPDFVTUIDataSourceFileTextWidgetID, filePath);
			}
		}

		if (theSelectedWidget == kPDFVTUIDataSourceFileTextWidgetID && theChange == kTextChangeStateMessage)
		{
			InterfacePtr<IPanelControlData> pPanelData(this, UseDefaultIID());
			InterfacePtr<IDialogController> dlgController(this, UseDefaultIID());
			if (pPanelData == nil)
			{
				ASSERT_FAIL("PDFVTUIDialogController::Update: PanelControlData is nil!");
				break;
			}

			PMString path = dlgController->GetTextControlData(kPDFVTUIDataSourceFileTextWidgetID);
			WideString wPath(path);
			vector<string> keyList;
			PDFVTUtils::GetDataSourceKeyList(keyList, wPath);
			this->ResetSelections(keyList);
		}

		if (fDropDownLists.find(theSelectedWidget.Get()) != fDropDownLists.end() && theChange == kPopupChangeStateMessage)
		{			
			InterfacePtr<IDialogController> dlgController(this, UseDefaultIID());			

			InterfacePtr<IPanelControlData> pPanelData(this, UseDefaultIID());

			IControlView* pSelectedDropDownListControlView(pPanelData->FindWidget(theSelectedWidget));
			InterfacePtr<IDropDownListController> pSelectedDropDownListController(pSelectedDropDownListControlView, UseDefaultIID());
			int32 selection = pSelectedDropDownListController->GetSelected();
			if (selection != IDropDownListController::kNoSelection)
			{
				InterfacePtr<IDropDownListSelection> pDropDownListSelection(this, UseDefaultIID());
				for (set<int32>::const_iterator it = fDropDownLists.begin(); it != fDropDownLists.end(); it++)
				{
					if (*it == theSelectedWidget.Get())
					{
						continue;
					}
					IControlView* pDropDownListControlView(pPanelData->FindWidget(*it));				
					InterfacePtr<IDropDownListController> pDropDownListController(pDropDownListControlView, UseDefaultIID());				

					pDropDownListController->Enable(pDropDownListSelection->GetSelection(theSelectedWidget.Get()), kTrue, kTrue, kFalse);
					if (selection != 0)
					{
						pDropDownListController->Disable(selection, kTrue, kFalse);							
					}					
				}				
				pDropDownListSelection->SetSelection(theSelectedWidget.Get(), selection);
			}		
		}
	} while (kFalse);
}

void PDFVTUIDialogObserver::ResetSelections(const vector<string>& keyList)
{	
	InterfacePtr<IPanelControlData> pPanelData(this, UseDefaultIID());

	for (set<int32>::const_iterator it = fDropDownLists.begin(); it != fDropDownLists.end(); it++)
	{
		IControlView* pDropDownListControlView(pPanelData->FindWidget(*it));
		InterfacePtr<IDropDownListController> pDropDownListController(pDropDownListControlView, UseDefaultIID());

		InterfacePtr<IStringListControlData> pDropDownStringListController(pDropDownListControlView, UseDefaultIID());
		pDropDownStringListController->Clear();
		pDropDownStringListController->AddString(kPDFVTUICIP4UnmappedKey);;

		vector<string>::const_iterator keyListIt = keyList.begin();
		for(; keyListIt != keyList.end(); keyListIt++)
		{
			WideString ws;
			StringUtils::ConvertUTF8ToWideString(*keyListIt, ws);			
			pDropDownStringListController->AddString(PMString(ws).SetTranslatable(kFalse));			
		}
		pDropDownListController->Select(0, kTrue, kFalse);
	}

	InterfacePtr<IDropDownListSelection> dropDownListSelection(this, UseDefaultIID());
	dropDownListSelection->Init();
}

//  Code generated by DollyXs code generator
