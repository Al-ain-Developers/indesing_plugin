//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/XFLExportDlgController.cpp $
//  
//  Owner: DBerggren
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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
#include "XFLExportDlgController.h"

// ----- Interface files -----

#include "IActiveContext.h"
#include "IBoolData.h"
#include "IDropDownListController.h"
#include "IFlashXFLExportFacade.h"
#include "IXFLExportPreferences.h"
#include "IPageRange.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "IUIDListData.h"
#include "IWorkspace.h"

// ----- Include files -----

#include "CAlert.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

CREATE_PMINTERFACE(XFLExportDlgController, kXFLExportDlgControllerImpl)

XFLExportDlgController::XFLExportDlgController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

XFLExportDlgController::~XFLExportDlgController()
{
}

void XFLExportDlgController::ResetDialogFields(IActiveContext* ac)
{
	CDialogController::ResetDialogFields(ac);
}

void XFLExportDlgController::InitializeDialogFields( IActiveContext* ac)
{
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());

	InterfacePtr<IXFLExportPreferences> iData(this, UseDefaultIID());
	InterfacePtr<IPageRange> iPageRange (this, IID_IXFLEXPORTPAGERANGE);
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	IDocument* iDoc = ac->GetContextDocument();
	if (!ws || !iData || !iPanelData || !iDoc || !iPageRange)
		return;
	
	// Copy the prefs on the workspace to temp data on the dialog.
	Utils<Facade::IFlashXFL_ExportFacade>()->GetWorkspacePreferences(ws, iData);

	PMString pageRange(kNullString);
	IPageRange::RangeFormat pageRangeFormat(IPageRange::kAllPages);
	Utils<Facade::IFlashXFL_ExportFacade>()->GetPageRangeInfo(ws, pageRange, pageRangeFormat);
	iPageRange->SetPageRange(pageRange);
	iPageRange->SetPageRangeFormat(pageRangeFormat);

	IControlView* iControlView = nil;
	InterfacePtr<IDropDownListController> iListController;

	// set page range edit box
	if (!ddui_utils::InitializeRangeEdit(iPageRange, iDoc, iPanelData))
		iPageRange->SetPageRangeFormat(IPageRange::kAllPages);

	// see if there are any page items selected, if not disable the control
	InterfacePtr<IUIDListData> iUIDListData(this, UseDefaultIID());
	const UIDList *itemsUIDList(nil);
	if (iUIDListData)
		itemsUIDList = iUIDListData->GetRef();
	if (itemsUIDList && itemsUIDList->size() == 0 && iPageRange->GetPageRangeFormat() == IPageRange::kBySelection)
		iPageRange->SetPageRangeFormat(IPageRange::kAllPages);
	ddui_utils::SetWidgetState(iPanelData, kSelection_RadioButtonWidgetID, itemsUIDList && itemsUIDList->size() != 0);

	// set pages radio button 
	if (iPageRange->GetPageRangeFormat() == IPageRange::kUseRange)
	{
		SetTriStateControlData(kSelection_RadioButtonWidgetID, kFalse);
		SetTriStateControlData(kAll_RadioButtonWidgetID, kFalse);
		SetTriStateControlData(kRange_RadioButtonWidgetID, kTrue);
	}
	else if (iPageRange->GetPageRangeFormat() == IPageRange::kBySelection)
	{
		SetTriStateControlData(kSelection_RadioButtonWidgetID, kTrue);
		SetTriStateControlData(kAll_RadioButtonWidgetID, kFalse);
		SetTriStateControlData(kRange_RadioButtonWidgetID, kFalse);
	}
	else // if (iPageRange->GetPageRangeFormat() == IPageRange::kAllPages)
	{
		SetTriStateControlData(kAll_RadioButtonWidgetID, kTrue);
		SetTriStateControlData(kRange_RadioButtonWidgetID, kFalse);
		SetTriStateControlData(kSelection_RadioButtonWidgetID, kFalse);
	}

	// set rasterize
	if ( iData->GetRasterizePages() && 
		(iPageRange->GetPageRangeFormat() == IPageRange::kBySelection ||
		 iData->GetDynamicMediaHandling() == flash_export::kIncludeAll))
		iData->SetRasterizePages(kFalse);
	SetTriStateControlData(kRastorizeCheckboxWID, iData->GetRasterizePages() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
	ddui_utils::SetWidgetState(iPanelData, kRastorizeCheckboxWID, iPageRange->GetPageRangeFormat() != IPageRange::kBySelection);

	// set flatten XP checkbox
	if ( iData->GetTransparencyHandling() == flash_export::kFlattenTransparency &&
		(iData->GetRasterizePages() ||
		iData->GetDynamicMediaHandling() == flash_export::kIncludeAll))
		iData->SetTransparencyHandling(flash_export::kIgnoreTransparency);
	SetTriStateControlData(kFlattenXPCheckboxWID, iData->GetTransparencyHandling() == flash_export::kFlattenTransparency ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
	ddui_utils::SetWidgetState(iPanelData, kFlattenXPCheckboxWID, iData->GetRasterizePages() == kFalse);

	flash_export::SizeAndFitSettings sizeFitSettings;
	iData->GetSizeAndFitSettings(sizeFitSettings);

	// always set scale radio button
	SetTriStateControlData(kScale_RadioButtonWidgetID, ITriStateControlData::kSelected);

	// set fit to popup
	ddui_utils::SetWidgetState(iPanelData, kFitTo_RadioButtonWidgetID, iPageRange->GetPageRangeFormat() != IPageRange::kBySelection);

	iControlView = iPanelData->FindWidget (kFitToPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	if (sizeFitSettings.fFitToSelection == flash_export::k1280x800)
		iListController->Select (k1280x800Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k1240x620)
		iListController->Select (k1240x620Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k1024x768)
		iListController->Select (k1024x768Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k984x588)
		iListController->Select (k984x588Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k800x600)
		iListController->Select (k800x600Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k760x420)
		iListController->Select (k760x420Index, kTrue, kFalse);
	else if (sizeFitSettings.fFitToSelection == flash_export::k640x480)
		iListController->Select (k640x480Index, kTrue, kFalse);
	else // if (sizeFitSettings.fFitToSelection == flash_export::k600x300)
		iListController->Select (k600x300Index, kTrue, kFalse);
	iControlView->Disable();

	// set width popup - NOTE: the values are set in the observer
	ddui_utils::SetWidgetState(iPanelData, kWidth_RadioButtonWidgetID, iPageRange->GetPageRangeFormat() != IPageRange::kBySelection);
	ddui_utils::SetWidgetState(iPanelData, kWidthPopupWID, false);

	// set height popup - NOTE: the values are set in the observer
	ddui_utils::SetWidgetState(iPanelData, kHeightWidgetID, iPageRange->GetPageRangeFormat() != IPageRange::kBySelection);
	ddui_utils::SetWidgetState(iPanelData, kHeightPopupWID, false);

	// set height width chain icon - NOTE: always ON and disabled
	SetTriStateControlData(kHeight_Width_ConstrainWID, ITriStateControlData::kSelected);
	ddui_utils::SetWidgetState(iPanelData, kHeight_Width_ConstrainWID, false);

	// set scale popup 
	iControlView = iPanelData->FindWidget (kScalePopupWID);
	iControlView->Enable();
	InterfacePtr<ITextValue> textValue(iControlView, UseDefaultIID());
	textValue->SetTextFromValue(sizeFitSettings.fScaleAmount);

	// set dynamic media handling 
	if (iData->GetDynamicMediaHandling() == flash_export::kAppearanceOnly)
		SetTriStateControlData(kAppearanceOnly_RadioButtonWidgetID, kTrue);
	else // if (iData->GetDynamicMediaHandling() == flash_export::kIncludeAll)
		SetTriStateControlData(kIncludeAll_RadioButtonWidgetID, kTrue);

	// set text selection popup
	iControlView = iPanelData->FindWidget (kTextPopupWID);
	iControlView->Enable();
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	// if rasterize pages is on, set to raster, and disable control
	if (iData->GetRasterizePages())
	{
		iListController->Select (kRasterTextIndex, kTrue, kFalse);
		iControlView->Disable();
	}
	else if (iData->GetTextExportPolicy() == flash_export::kLiveText)
		iListController->Select (kFlashTextIndex, kTrue, kFalse);
	else if (iData->GetTextExportPolicy() == flash_export::kVectorizeText)
		iListController->Select (kVectorTextIndex, kTrue, kFalse);
	else if (iData->GetTextExportPolicy() == flash_export::kRasterizeText)
		iListController->Select (kRasterTextIndex, kTrue, kFalse);
	else // if (iData->GetTextExportPolicy() == flash_export::kVellumText)
		iListController->Select (kVellumTextIndex, kTrue, kFalse);

	// set insert hyphens checkbox
	if (iData->GetTextExportPolicy() != flash_export::kVellumText)
		iData->SetInsertHyphensForTLF(kFalse);
	SetTriStateControlData(kInsertHyphensCheckboxWID, iData->GetInsertHyphensForTLF() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
	ddui_utils::SetWidgetState(iPanelData, kInsertHyphensCheckboxWID, iData->GetTextExportPolicy() == flash_export::kVellumText);

	// set image handling
	flash_export::RasterFormat format = iData->GetRasterFormat();
	iControlView = iPanelData->FindWidget (kCompressionPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	if (format == flash_export::kJPEGFormat)
		iListController->Select (kJPEGFormatIndex, kTrue, kFalse);
	else if (format == flash_export::kPNGFormat)
		iListController->Select (kPNGFormatIndex, kTrue, kFalse);
	else // if (format == flash_export::kAutomaticFormat)
		iListController->Select (kAutomaticFormatIndex, kTrue, kFalse);

	// set JPEG Quality popup
	flash_export::JPEGQuality quality = iData->GetJPEGQuality();
	iControlView = iPanelData->FindWidget (kJPEGQualityPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	if (quality == flash_export::kJPEGQuality_Minimum)
		iListController->Select (kMinQualityIndex, kTrue, kFalse);
	else if (quality == flash_export::kJPEGQuality_Low)
		iListController->Select (kLowQualityIndex, kTrue, kFalse);
	else if (quality == flash_export::kJPEGQuality_Medium)
		iListController->Select (kMedQualityIndex, kTrue, kFalse);
	else if (quality == flash_export::kJPEGQuality_High)
		iListController->Select (kHighQualityIndex, kTrue, kFalse);
	else // if (quality == flash_export::kJPEGQuality_Maximum)
		iListController->Select (kMaxQualityIndex, kTrue, kFalse);

	// Enable / disable the control
	iControlView->Enable(format != flash_export::kPNGFormat);

	// set Resolution Combo
	iControlView = iPanelData->FindWidget (kResolutionComboWID);
    textValue = InterfacePtr<ITextValue>(iControlView, UseDefaultIID());
    textValue->SetTextFromValue(iData->GetRasterResolution(), kTrue, kFalse);
}

WidgetID XFLExportDlgController::ValidateDialogFields(IActiveContext* myContext)
{
 	WidgetID id = CDialogController::ValidateDialogFields(myContext);
	if (id != kNoInvalidWidgets)
 		return id;
 
	// check for blank page range string if page range is selected
	if (GetTriStateControlData(kRange_RadioButtonWidgetID) == ITriStateControlData::kSelected)
	{
		InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
		IControlView* iControlView = iPanelData->FindWidget (kPagesPageRangeEditWID);
		InterfacePtr<ITextControlData> textData(iControlView, UseDefaultIID());
		if (textData)
		{
			PMString pageRangeStr(textData->GetString());
			if (pageRangeStr.IsEmpty()) 
			{
				CAlert::WarningAlert("The page range is empty.");	// warning string from PDFUI
				return kPagesPageRangeEditWID;
			}
		}
	}

	return kNoInvalidWidgets;
}

void XFLExportDlgController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	InterfacePtr<IBoolData> dialogWasOKed(this, UseDefaultIID());
	dialogWasOKed->Set(kTrue);

	InterfacePtr<IXFLExportPreferences> iData(this, UseDefaultIID());
	InterfacePtr<IPageRange> iPageRange (this, IID_IXFLEXPORTPAGERANGE);
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	if (!iData || !iPanelData || !iPageRange)
		return;

	// set pages radio button
	if(GetTriStateControlData(kRange_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		iPageRange->SetPageRangeFormat(IPageRange::kUseRange);
	else if(GetTriStateControlData(kSelection_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		iPageRange->SetPageRangeFormat(IPageRange::kBySelection);
	else 
		iPageRange->SetPageRangeFormat(IPageRange::kAllPages);

	// set page range edit box
	IControlView* iControlView = iPanelData->FindWidget (kPagesPageRangeEditWID);
	InterfacePtr<ITextControlData> textData(iControlView, UseDefaultIID());
	iPageRange->SetPageRange(textData->GetString());

	// set rasterize
	iData->SetRasterizePages(GetTriStateControlData(kRastorizeCheckboxWID) == ITriStateControlData::kSelected);

	// set flatten transparency
	if (GetTriStateControlData(kFlattenXPCheckboxWID) == ITriStateControlData::kSelected)
		iData->SetTransparencyHandling(flash_export::kFlattenTransparency);
	else	// TODO: should this be ignore or native?
		iData->SetTransparencyHandling(flash_export::kIgnoreTransparency);

	// allocate and initialize the settings
	flash_export::SizeAndFitSettings sizeFitSettings;
	iData->GetSizeAndFitSettings(sizeFitSettings);

	// set size radio button
	if(GetTriStateControlData(kFitTo_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		sizeFitSettings.fSizeSelection = flash_export::kFitTo;
	else if(GetTriStateControlData(kWidth_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		sizeFitSettings.fSizeSelection = flash_export::kWidthAndHeight;
	else // if(GetTriStateControlData(kScale_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		sizeFitSettings.fSizeSelection = flash_export::kScale;

	// set fit to popup
	iControlView = iPanelData->FindWidget (kFitToPopupWID);
	InterfacePtr<IDropDownListController> iListController(iControlView, UseDefaultIID ());
	int32 selected = iListController->GetSelected();
	if (selected == k1280x800Index)
		sizeFitSettings.fFitToSelection = flash_export::k1280x800;
	else if (selected == k1240x620Index)
		sizeFitSettings.fFitToSelection = flash_export::k1240x620;
	else if (selected == k1024x768Index)
		sizeFitSettings.fFitToSelection = flash_export::k1024x768;
	else if (selected == k984x588Index)
		sizeFitSettings.fFitToSelection = flash_export::k984x588;
	else if (selected == k800x600Index)
		sizeFitSettings.fFitToSelection = flash_export::k800x600;
	else if (selected == k760x420Index)
		sizeFitSettings.fFitToSelection = flash_export::k760x420;
	else if (selected == k640x480Index)
		sizeFitSettings.fFitToSelection = flash_export::k640x480;
	else // if (selected == k600x300Index)
		sizeFitSettings.fFitToSelection = flash_export::k600x300;

	// set width popup
	iControlView = iPanelData->FindWidget (kWidthPopupWID);
	InterfacePtr<ITextValue> textValueX(iControlView, UseDefaultIID());
	sizeFitSettings.fWidthAmount = ::ToUInt32(textValueX->GetTextAsValue());

	// set height popup
	iControlView = iPanelData->FindWidget (kHeightPopupWID);
	InterfacePtr<ITextValue> textValueY(iControlView, UseDefaultIID());
	sizeFitSettings.fHeightAmount = ::ToUInt32(textValueY->GetTextAsValue());

	// set scale popup
	iControlView = iPanelData->FindWidget (kScalePopupWID);
	InterfacePtr<ITextValue> textValue(iControlView, UseDefaultIID());
	sizeFitSettings.fScaleAmount = textValue->GetTextAsValue();

	// finally, save the settings
	iData->SetSizeAndFitSettings(sizeFitSettings);

	// set dynamic media handling
	if(GetTriStateControlData(kAppearanceOnly_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		iData->SetDynamicMediaHandling(flash_export::kAppearanceOnly);
	else 
		iData->SetDynamicMediaHandling(flash_export::kIncludeAll);

	// set text selection popup
	iControlView = iPanelData->FindWidget (kTextPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	selected = iListController->GetSelected();
	if (selected == kFlashTextIndex)
		iData->SetTextExportPolicy(flash_export::kLiveText);
	else if (selected == kVectorTextIndex)
		iData->SetTextExportPolicy(flash_export::kVectorizeText);
	else if (selected == kRasterTextIndex)
		iData->SetTextExportPolicy(flash_export::kRasterizeText);
	else // if (selected == kVellumTextIndex)
		iData->SetTextExportPolicy(flash_export::kVellumText);

	// set insert hyphens
	iData->SetInsertHyphensForTLF(GetTriStateControlData(kInsertHyphensCheckboxWID) == ITriStateControlData::kSelected);

	// set image handling
	iControlView = iPanelData->FindWidget (kCompressionPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	selected = iListController->GetSelected();
	if (selected == kJPEGFormatIndex)
		iData->SetRasterFormat(flash_export::kJPEGFormat);
	else if (selected == kPNGFormatIndex)
		iData->SetRasterFormat(flash_export::kPNGFormat);
	else // if (selected == kAutomaticFormatIndex)
		iData->SetRasterFormat(flash_export::kAutomaticFormat);

	// set JPEG Quality popup
	iControlView = iPanelData->FindWidget (kJPEGQualityPopupWID);
	iListController = InterfacePtr<IDropDownListController>(iControlView, UseDefaultIID ());
	selected = iListController->GetSelected();
	if (selected == kMinQualityIndex)
		iData->SetJPEGQuality(flash_export::kJPEGQuality_Minimum);
	else if (selected == kLowQualityIndex)
		iData->SetJPEGQuality(flash_export::kJPEGQuality_Low);
	else if (selected == kMedQualityIndex)
		iData->SetJPEGQuality(flash_export::kJPEGQuality_Medium);
	else if (selected == kHighQualityIndex)
		iData->SetJPEGQuality(flash_export::kJPEGQuality_High);
	else // if (selected == kMaxQualityIndex)
		iData->SetJPEGQuality(flash_export::kJPEGQuality_Maximum);

	// set Resolution
	iControlView = iPanelData->FindWidget (kResolutionComboWID);
	textValue = InterfacePtr<ITextValue>(iControlView, UseDefaultIID());
	uint32 resolution = ::ToUInt32(textValue->GetTextAsValue());
	iData->SetRasterResolution(resolution);

	// Process the command
	ErrorCode result = Utils<Facade::IFlashXFL_ExportFacade>()->SetWorkspacePreferences(iData, iPageRange);
}

