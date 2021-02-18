//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/XFLExportDlgObserver.cpp $
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IControlView.h"
#include "ISubject.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IDynDocsPublicUtils.h"
#include "IPageList.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IUIDListData.h"

// ----- Includes -----

#include "CDialogObserver.h"
#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsUIUtils.h"
#include "XFLExportDlgController.h"

//====================================================================================================================
// Class XFLExportDlgObserver
//====================================================================================================================
class XFLExportDlgObserver : public CDialogObserver
{
public:
	XFLExportDlgObserver(IPMUnknown* boss);
	virtual ~XFLExportDlgObserver();
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);	

private:
	PMPoint fWidthHeight;
	PMPoint fSelectedWidthHeight;
	PMPoint fSpreadWidthHeight;
	int32 fTextPopupIndexSaved;
	bool fFlattenXPSaved;
	bool fInsertHyphenSaved;
	WidgetID fSelectedWidgetID;

	void SizeRadioChanged(const ClassID& changeId, const WidgetID& widgetID);
	void FitToPopupChanged();
	void WidthEditChanged(const ClassID& changeId, ISubject* iSubject);
	void HeightEditChanged(const ClassID& changeId, ISubject* iSubject);
	void ScalePopupChanged();
	void PagesRadioChanged(const ClassID& changeId, const WidgetID& widgetID);
	void PageRangeEditChanged(const ClassID& changeId);
	void RasterizePagesCheckboxChanged(const ClassID& changeId);
	void FlattenXPCheckboxChanged(const ClassID& changeId);
	void DynamicMediaChanged(const ClassID& changeId);
	void ImageCompPopupChanged(const ClassID& changeId, ISubject* iSubject);
	void TextPopupChanged(const ClassID& changeId, ISubject* iSubject);
	void GetWidthAndHeight(uint32& width, uint32& height) const;
	void GetWidthAndHeightFitTo(uint32& width, uint32& height) const;
	void GetWidthAndHeightScale(uint32& width, uint32& height) const;
	void SetWidthAndHeight(uint32& width, uint32& height) const;
	void SetScale(uint32 width, uint32 height) const;
	void UpdatePageAndSpreadSize(IDocument* iDocument, bool16 bPageRange);
	void UpdateWidthHeightAndScale() const;

};


CREATE_PMINTERFACE(XFLExportDlgObserver, kXFLExportDlgObserverImpl)

//--------------------------------------------------------------------------------------------------------------------
// XFLExportDlgObserver Constructor/Destructor
//--------------------------------------------------------------------------------------------------------------------
XFLExportDlgObserver::XFLExportDlgObserver(IPMUnknown* boss)
	: CDialogObserver(boss),
	fSelectedWidthHeight(0, 0),
	fSpreadWidthHeight(1024, 768),
	fTextPopupIndexSaved(XFLExportDlgController::kFlashTextIndex),
	fFlattenXPSaved(false),
	fInsertHyphenSaved(true),
	fSelectedWidgetID(kInvalidWidgetID)
{
}


XFLExportDlgObserver::~XFLExportDlgObserver()
{
}


//--------------------------------------------------------------------------------------------------------------------
// AutoAttach
//--------------------------------------------------------------------------------------------------------------------
void XFLExportDlgObserver::AutoAttach() 
{
	CDialogObserver::AutoAttach();
	
	InterfacePtr<IPanelControlData>	iPanelData(this, UseDefaultIID());
	if (iPanelData)
	{
		if (fSelectedWidgetID == kInvalidWidgetID)
		{
            IControlView *widget = iPanelData->FindWidget(kSelection_RadioButtonWidgetID);
            InterfacePtr<ITriStateControlData> triData(widget,IID_ITRISTATECONTROLDATA);
			if (triData && triData->IsSelected())
				fSelectedWidgetID = kSelection_RadioButtonWidgetID;
			else
			{
				widget = iPanelData->FindWidget(kRange_RadioButtonWidgetID);
				triData = InterfacePtr<ITriStateControlData>(widget,IID_ITRISTATECONTROLDATA);
				if (triData && triData->IsSelected())
					fSelectedWidgetID = kRange_RadioButtonWidgetID;
				else 
					fSelectedWidgetID = kAll_RadioButtonWidgetID;
			}
		}

		AttachToWidget(kSelection_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kAll_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kRange_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kPagesPageRangeEditWID, IID_ITEXTCONTROLDATA, iPanelData);
		AttachToWidget(kWidth_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kFitTo_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kFitToPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);
		AttachToWidget(kWidthPopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		AttachToWidget(kHeightPopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		AttachToWidget(kScale_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kScalePopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		AttachToWidget(kRastorizeCheckboxWID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kFlattenXPCheckboxWID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kIncludeAll_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		AttachToWidget(kCompressionPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);
		AttachToWidget(kTextPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);

		InterfacePtr<IActiveContext> activeContext(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (!activeContext) return;
		IDocument *contextDoc = activeContext->GetContextDocument();
		if (!contextDoc) return;

		InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
		bool16 bPageRange = iDialogController->GetTriStateControlData(kRange_RadioButtonWidgetID) == ITriStateControlData::kSelected;

		// intialize the saved values
		IControlView* iTextPopupView = iPanelData->FindWidget (kTextPopupWID);
		InterfacePtr<IDropDownListController> iTextPopupController(iTextPopupView, UseDefaultIID());
		fTextPopupIndexSaved = iTextPopupController->GetSelected();
		fInsertHyphenSaved = fTextPopupIndexSaved != XFLExportDlgController::kVellumTextIndex ? true : iDialogController->GetTriStateControlData(kInsertHyphensCheckboxWID) == ITriStateControlData::kSelected;
		fFlattenXPSaved = iDialogController->GetTriStateControlData(kFlattenXPCheckboxWID) == ITriStateControlData::kSelected;

		// update to the new page range
		UpdatePageAndSpreadSize(contextDoc, bPageRange);

		// update the width and height
		UpdateWidthHeightAndScale();

	}
}


//--------------------------------------------------------------------------------------------------------------------
// AutoDetach
//--------------------------------------------------------------------------------------------------------------------
void XFLExportDlgObserver::AutoDetach() 
{
	fSelectedWidgetID = kInvalidWidgetID;
	fSelectedWidthHeight = PMPoint(0, 0);

	InterfacePtr<IPanelControlData>	iPanelData(this, UseDefaultIID());
	if (iPanelData)
	{
		DetachFromWidget(kSelection_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kAll_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kRange_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kPagesPageRangeEditWID, IID_ITEXTCONTROLDATA, iPanelData);
		DetachFromWidget(kWidth_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kFitTo_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kFitToPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);
		DetachFromWidget(kWidthPopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		DetachFromWidget(kHeightPopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		DetachFromWidget(kScalePopupWID, IID_ITEXTCONTROLDATA, iPanelData);
		DetachFromWidget(kScale_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kRastorizeCheckboxWID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kFlattenXPCheckboxWID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kIncludeAll_RadioButtonWidgetID, IID_ITRISTATECONTROLDATA, iPanelData);
		DetachFromWidget(kCompressionPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);
		DetachFromWidget(kTextPopupWID, IID_ISTRINGLISTCONTROLDATA, iPanelData);
	}
	
	CDialogObserver::AutoDetach();
}


//--------------------------------------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------------------------------------
void XFLExportDlgObserver::Update(const ClassID& changeId, ISubject* iSubject, const PMIID& protocolId, void* changedBy)
{
	InterfacePtr<IControlView> theControlView(iSubject, UseDefaultIID());
	if (theControlView != nil) 
	{
		WidgetID widgetID = theControlView->GetWidgetID();
		switch (widgetID.Get()) 
		{
			case kSelection_RadioButtonWidgetID:
			case kAll_RadioButtonWidgetID:
			case kRange_RadioButtonWidgetID:
				PagesRadioChanged(changeId, widgetID);
				break;
			case kPagesPageRangeEditWID:
				PageRangeEditChanged(changeId);
				break;
			case kFitTo_RadioButtonWidgetID:
			case kScale_RadioButtonWidgetID:
			case kWidth_RadioButtonWidgetID:
				SizeRadioChanged(changeId, widgetID);
				break;
			case kFitToPopupWID:
				FitToPopupChanged();
				break;
			case kWidthPopupWID:
				WidthEditChanged(changeId, iSubject);
				break;
			case kHeightPopupWID:
				HeightEditChanged(changeId, iSubject);
				break;
			case kScalePopupWID:
				ScalePopupChanged();
				break;
			case kRastorizeCheckboxWID:
				RasterizePagesCheckboxChanged(changeId);
				break;
			case kFlattenXPCheckboxWID:
				FlattenXPCheckboxChanged(changeId);
				break;
			case kIncludeAll_RadioButtonWidgetID:
				DynamicMediaChanged(changeId);
				break;
			case kCompressionPopupWID:
				ImageCompPopupChanged(changeId, iSubject);
				break;
			case kTextPopupWID:
				TextPopupChanged(changeId, iSubject);
				break;
			default:
				break;
		}
	}

	CDialogObserver::Update( changeId, iSubject, protocolId, changedBy );
}

//========================================================================================
// XFLExportDlgObserver::SizeRadioChanged
//========================================================================================
void XFLExportDlgObserver::SizeRadioChanged(const ClassID& changeId, const WidgetID& widgetID)
{
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());

	if (changeId == kTrueStateMessage) 
	{

		ddui_utils::SetWidgetState(iPanelData, kFitToPopupWID, widgetID.Get() == kFitTo_RadioButtonWidgetID);
		ddui_utils::SetWidgetState(iPanelData, kScalePopupWID, widgetID.Get() == kScale_RadioButtonWidgetID);
		ddui_utils::SetWidgetState(iPanelData, kWidthPopupWID, widgetID.Get() == kWidth_RadioButtonWidgetID);
		ddui_utils::SetWidgetState(iPanelData, kHeightPopupWID, widgetID.Get() == kWidth_RadioButtonWidgetID);

		// we only need to update width, height and scale if Fit To is selected
		uint32 width, height;
		if (widgetID.Get() == kFitTo_RadioButtonWidgetID)
			GetWidthAndHeightFitTo(width, height);
		else
			return;

		// set the width and height
		SetWidthAndHeight(width, height);

		// set the scale percentage
		SetScale(width, height);
	}
}

//========================================================================================
// XFLExportDlgObserver::FitToPopupChanged
//========================================================================================
void XFLExportDlgObserver::FitToPopupChanged()
{
	InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());

	// set the fit to radio button
	iDialogController->SetTriStateControlData(kFitTo_RadioButtonWidgetID, ITriStateControlData::kSelected);

	// get the new values and set them in width and height
	uint32 width, height;
	GetWidthAndHeightFitTo(width, height);
	SetWidthAndHeight(width, height);

	// set the scale percentage
	SetScale(width, height);
}

//========================================================================================
// XFLExportDlgObserver::WidthEditChanged
//========================================================================================
void XFLExportDlgObserver::WidthEditChanged(const ClassID& changeId, ISubject* iSubject)
{
	if (changeId == kTextChangeStateMessage) 
	{
		InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
		InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());

		// get the new value for the width
		InterfacePtr<ITextValue> textValueX(iSubject, UseDefaultIID());
		uint32 targetWidth = ::ToUInt32(textValueX->GetTextAsValue());

		// calculate the new value for the height
		uint32 destHeight;
		ddui_utils::CalculateHeightFromWidth(	fWidthHeight.X(), fWidthHeight.Y(), 
												targetWidth,
												destHeight );

		// boundary checking
		if (destHeight < kMinSize)
		{
			destHeight = kMinSize;
			ddui_utils::CalculateWidthFromHeight(	fWidthHeight.X(), fWidthHeight.Y(),
													destHeight,
													targetWidth );
			textValueX->SetTextFromValue(targetWidth, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);
		}
		else if (destHeight > kMaxSize)
		{
			destHeight = kMaxSize;
			ddui_utils::CalculateWidthFromHeight(	fWidthHeight.X(), fWidthHeight.Y(),
													destHeight,
													targetWidth );
			textValueX->SetTextFromValue(targetWidth, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);
		}

		// set height popup
		IControlView* iView = iPanelData->FindWidget (kHeightPopupWID);
		InterfacePtr<ITextValue> textValueY(iView, UseDefaultIID());
		textValueY->SetTextFromValue(destHeight, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);

		// set the scale percentage
		SetScale(targetWidth, destHeight);
	}
}

//========================================================================================
// XFLExportDlgObserver::HeightEditChanged
//========================================================================================
void XFLExportDlgObserver::HeightEditChanged(const ClassID& changeId, ISubject* iSubject)
{
	if (changeId == kTextChangeStateMessage) 
	{
		InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());

		// get the new value for the height
		InterfacePtr<ITextValue> textValueY(iSubject, UseDefaultIID());
		uint32 targetHeight = ::ToUInt32(textValueY->GetTextAsValue());

		// calculate the new value for the width
		uint32 destWidth;
		ddui_utils::CalculateWidthFromHeight(	fWidthHeight.X(), fWidthHeight.Y(),
												targetHeight,
												destWidth );

		// boundary checking
		if (destWidth < kMinSize)
		{
			destWidth = kMinSize;
			ddui_utils::CalculateHeightFromWidth(	fWidthHeight.X(), fWidthHeight.Y(),
													destWidth,
													targetHeight );
			textValueY->SetTextFromValue(targetHeight, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);
		}
		else if (destWidth > kMaxSize)
		{
			destWidth = kMaxSize;
			ddui_utils::CalculateHeightFromWidth(	fWidthHeight.X(), fWidthHeight.Y(),
													destWidth,
													targetHeight );
			textValueY->SetTextFromValue(targetHeight, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);
		}

		// set width popup
		IControlView* iView = iPanelData->FindWidget (kWidthPopupWID);
		InterfacePtr<ITextValue> textValueX(iView, UseDefaultIID());
		textValueX->SetTextFromValue(destWidth, /*invalidate*/ kTrue, /*notifyOfChange*/ kFalse);

		// set the scale percentage
		SetScale(destWidth, targetHeight);
	}
}

//========================================================================================
// XFLExportDlgObserver::ScalePopupChanged
//========================================================================================
void XFLExportDlgObserver::ScalePopupChanged()
{
	// get the new values and set them in width and height
	uint32 width, height;
	GetWidthAndHeightScale(width, height);
	SetWidthAndHeight(width, height);
}

//========================================================================================
// XFLExportDlgObserver::PagesRadioChanged
//========================================================================================
void XFLExportDlgObserver::PagesRadioChanged(const ClassID& changeId, const WidgetID& widgetID)
{
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	InterfacePtr<IDialogController> iDialogController (this, UseDefaultIID());

	if(widgetID == fSelectedWidgetID && changeId == kFalseStateMessage)
	{
		//can't let this happen -it must stay selected
		IControlView* iView = iPanelData->FindWidget (widgetID);
		InterfacePtr<ITriStateControlData> triData(iView, IID_ITRISTATECONTROLDATA);
		if(triData)
			triData->Select();
	}

	if (changeId == kTrueStateMessage) 
	{
		fSelectedWidgetID = widgetID;

		// start with the radio buttons, and re-enabling everything
		iDialogController->SetTriStateControlData(kSelection_RadioButtonWidgetID, widgetID == kSelection_RadioButtonWidgetID ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, iPanelData, kTrue, kFalse);
		iDialogController->SetTriStateControlData(kAll_RadioButtonWidgetID, widgetID == kAll_RadioButtonWidgetID ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, iPanelData, kTrue, kFalse);
		iDialogController->SetTriStateControlData(kRange_RadioButtonWidgetID, widgetID == kRange_RadioButtonWidgetID ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, iPanelData, kTrue, kFalse);

		// special case the selection radio button
		if (widgetID == kSelection_RadioButtonWidgetID)
		{
			fWidthHeight = fSelectedWidthHeight;

			// disable fit to and width radio buttons and the height label
			ddui_utils::SetWidgetState(iPanelData, kFitTo_RadioButtonWidgetID, false);
			ddui_utils::SetWidgetState(iPanelData, kWidth_RadioButtonWidgetID, false);
			ddui_utils::SetWidgetState(iPanelData, kHeightWidgetID, false);
			// turn off and disable rasterize checkbox
			iDialogController->SetTriStateControlData(kRastorizeCheckboxWID, ITriStateControlData::kUnselected);
			ddui_utils::SetWidgetState(iPanelData, kRastorizeCheckboxWID, false);

			// force scale radio button, and set to 100% if scale was not chosen before
			IControlView* scaleView = iPanelData->FindWidget (kScale_RadioButtonWidgetID);
			InterfacePtr<ITriStateControlData> scaleTriData(scaleView, IID_ITRISTATECONTROLDATA);
			if (scaleTriData->IsDeselected())
			{
				scaleTriData->Select(kTrue, kTrue);
				IControlView* scaleAmt = iPanelData->FindWidget (kScalePopupWID);
				scaleAmt->Enable();
				InterfacePtr<ITextValue> scaleText(scaleAmt, UseDefaultIID());
				scaleText->SetTextFromValue(100);
			}
		}
		else
		{
			ddui_utils::SetWidgetState(iPanelData, kFitTo_RadioButtonWidgetID, true);
			ddui_utils::SetWidgetState(iPanelData, kWidth_RadioButtonWidgetID, true);
			ddui_utils::SetWidgetState(iPanelData, kHeightWidgetID, true);
			ddui_utils::SetWidgetState(iPanelData, kRastorizeCheckboxWID, true);
		}

		InterfacePtr<IActiveContext> activeContext(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (!activeContext) return;
		IDocument *contextDoc = activeContext->GetContextDocument();
		if (!contextDoc) return;

		// update to the new page range
		UpdatePageAndSpreadSize(contextDoc, widgetID.Get() == kRange_RadioButtonWidgetID);

		// update the width and height
		UpdateWidthHeightAndScale();

	}
}

//========================================================================================
// XFLExportDlgObserver::PageRangeEditChanged
//========================================================================================
void XFLExportDlgObserver::PageRangeEditChanged(const ClassID& changeId)
{
	InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
	if (changeId == kEditBoxKeyStrokeMessage) 
	{
		// set the page range radio button
		iDialogController->SetTriStateControlData(kRange_RadioButtonWidgetID, ITriStateControlData::kSelected);
	}
	else if (changeId == kTextChangeStateMessage)
	{
		// set the page range radio button
		iDialogController->SetTriStateControlData(kRange_RadioButtonWidgetID, ITriStateControlData::kSelected);

		InterfacePtr<IActiveContext> activeContext(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (!activeContext) return;
		IDocument *contextDoc = activeContext->GetContextDocument();
		if (!contextDoc) return;

		// update to the new page range
		UpdatePageAndSpreadSize(contextDoc, kTrue);

		// update the width and height
		UpdateWidthHeightAndScale();
	}
}

//========================================================================================
// XFLExportDlgObserver::RasterizePagesCheckboxChanged
//========================================================================================
void XFLExportDlgObserver::RasterizePagesCheckboxChanged(const ClassID& changeId)
{
	InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	IControlView* iFlattenXPView = iPanelData->FindWidget (kFlattenXPCheckboxWID);
	IControlView* iTextPopupView = iPanelData->FindWidget (kTextPopupWID);
	InterfacePtr<IDropDownListController> iTextPopupController(iTextPopupView, UseDefaultIID());
	if (!iTextPopupView || !iTextPopupController || !iFlattenXPView)
		return;

	if (changeId == kTrueStateMessage)
	{
		fFlattenXPSaved = iDialogController->GetTriStateControlData(kFlattenXPCheckboxWID) == ITriStateControlData::kSelected;
		iDialogController->SetTriStateControlData(kFlattenXPCheckboxWID, ITriStateControlData::kUnselected);
		iFlattenXPView->Disable();

		iDialogController->SetTriStateControlData(kAppearanceOnly_RadioButtonWidgetID, ITriStateControlData::kSelected);

		fTextPopupIndexSaved = iTextPopupController->GetSelected();
		iTextPopupController->Select(XFLExportDlgController::kRasterTextIndex);
		iTextPopupView->Disable();
	}
	else
	{
		iDialogController->SetTriStateControlData(kFlattenXPCheckboxWID, fFlattenXPSaved ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		iFlattenXPView->Enable();
		iTextPopupController->Select(fTextPopupIndexSaved);
		iTextPopupView->Enable();
	}
}

//========================================================================================
// XFLExportDlgObserver::FlattenXPCheckboxChanged
//========================================================================================
void XFLExportDlgObserver::FlattenXPCheckboxChanged(const ClassID& changeId)
{
	if (changeId == kTrueStateMessage)
	{
		InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
		iDialogController->SetTriStateControlData(kAppearanceOnly_RadioButtonWidgetID, ITriStateControlData::kSelected);
	}
}

//========================================================================================
// XFLExportDlgObserver::DynamicMediaChanged
//========================================================================================
void XFLExportDlgObserver::DynamicMediaChanged(const ClassID& changeId)
{
	// currently only observing Include All radio button
	if (changeId == kTrueStateMessage)
	{
		InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
		iDialogController->SetTriStateControlData(kRastorizeCheckboxWID, ITriStateControlData::kUnselected);
		iDialogController->SetTriStateControlData(kFlattenXPCheckboxWID, ITriStateControlData::kUnselected);
	}
}

//========================================================================================
// XFLExportDlgObserver::ImageCompPopupChanged
//========================================================================================
void XFLExportDlgObserver::ImageCompPopupChanged(const ClassID& changeId, ISubject* iSubject)
{
	if (changeId == kPopupChangeStateMessage) 
	{
		InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
		IControlView* iQualityPopupView = iPanelData->FindWidget (kJPEGQualityPopupWID);
		if (iQualityPopupView)
		{
			InterfacePtr<IDropDownListController> iDropDownListController(iSubject, UseDefaultIID());
			switch (iDropDownListController->GetSelected()) 
			{
				case XFLExportDlgController::kAutomaticFormatIndex:
				case XFLExportDlgController::kJPEGFormatIndex:
					iQualityPopupView->Enable();
					break;
				case XFLExportDlgController::kPNGFormatIndex:
					iQualityPopupView->Disable();
					break;
				default:
					ASSERT_FAIL("Unknown selection for ExportIntent popup!");
					break;
			}
		}
	}
}

//========================================================================================
// XFLExportDlgObserver::TextPopupChanged
//========================================================================================
void XFLExportDlgObserver::TextPopupChanged(const ClassID& changeId, ISubject* iSubject)
{
	if (changeId == kPopupChangeStateMessage) 
	{
		InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
		IControlView* iInsertHyphensView = iPanelData->FindWidget (kInsertHyphensCheckboxWID);
		if (iInsertHyphensView)
		{
			InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
			InterfacePtr<IDropDownListController> iDropDownListController(iSubject, UseDefaultIID());
			if (iDropDownListController->GetSelected() != XFLExportDlgController::kVellumTextIndex)
			{
				fInsertHyphenSaved = iDialogController->GetTriStateControlData(kInsertHyphensCheckboxWID) == ITriStateControlData::kSelected;
				iDialogController->SetTriStateControlData(kInsertHyphensCheckboxWID, ITriStateControlData::kUnselected);
				iInsertHyphensView->Disable();
			}
			else
			{
				iDialogController->SetTriStateControlData(kInsertHyphensCheckboxWID, fInsertHyphenSaved ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
				iInsertHyphensView->Enable();
			}
		}
	}
}

//========================================================================================
// XFLExportDlgObserver::GetWidthAndHeight
//========================================================================================
void XFLExportDlgObserver::GetWidthAndHeight(uint32& width, uint32& height) const
{
	InterfacePtr<IPanelControlData> iPanelData(this, UseDefaultIID());

	// get the new scale value
	IControlView* iControlView = iPanelData->FindWidget (kWidthPopupWID);
	InterfacePtr<ITextValue> textValueX(iControlView, UseDefaultIID());
	iControlView = iPanelData->FindWidget (kHeightPopupWID);
	InterfacePtr<ITextValue> textValueY(iControlView, UseDefaultIID());
	flash_export::SizeAndFitSettings settings;
	settings.fSizeSelection = flash_export::kWidthAndHeight;
	settings.fWidthAmount = ::ToUInt32(textValueX->GetTextAsValue());
	settings.fHeightAmount = ::ToUInt32(textValueY->GetTextAsValue());

	Utils<IDynDocsPublicUtils>()->CalculateWidthAndHeightForExport(fWidthHeight.X(), fWidthHeight.Y(), settings, width, height);

	// boundary check
	ASSERT(width >= kMinSize && width <= kMaxSize);
	ASSERT(height >= kMinSize && height <= kMaxSize);
}

//========================================================================================
// XFLExportDlgObserver::GetWidthAndHeightFitTo
//========================================================================================
void XFLExportDlgObserver::GetWidthAndHeightFitTo(uint32& width, uint32& height) const
{
	InterfacePtr<IPanelControlData> iPanelData(this, UseDefaultIID());

	// figure out what is chosen
	IControlView* iControlView = iPanelData->FindWidget (kFitToPopupWID);
	InterfacePtr<IDropDownListController> iListController(iControlView, UseDefaultIID ());
	int32 selected = iListController->GetSelected();
	flash_export::SizeAndFitSettings settings;
	settings.fSizeSelection = flash_export::kFitTo;

	if (selected == XFLExportDlgController::k1280x800Index)
	{
		settings.fFitToSelection = flash_export::k1280x800;
	}
	else if (selected == XFLExportDlgController::k1240x620Index)
	{
		settings.fFitToSelection = flash_export::k1240x620;
	}
	else if (selected == XFLExportDlgController::k1024x768Index)
	{
		settings.fFitToSelection = flash_export::k1024x768;
	}
	else if (selected == XFLExportDlgController::k984x588Index)
	{
		settings.fFitToSelection = flash_export::k984x588;
	}
	else if (selected == XFLExportDlgController::k800x600Index)
	{
		settings.fFitToSelection = flash_export::k800x600;
	}
	else if (selected == XFLExportDlgController::k760x420Index)
	{
		settings.fFitToSelection = flash_export::k760x420;
	}
	else if (selected == XFLExportDlgController::k640x480Index)
	{
		settings.fFitToSelection = flash_export::k640x480;
	}
	else // if (selected == XFLExportDlgController::k600x300Index)
	{
		settings.fFitToSelection = flash_export::k600x300;
	}

	// calculate the width and height
	Utils<IDynDocsPublicUtils>()->CalculateWidthAndHeightForExport(fWidthHeight.X(), fWidthHeight.Y(), settings, width, height);

}


//========================================================================================
// XFLExportDlgObserver::GetWidthAndHeightScale
//========================================================================================
void XFLExportDlgObserver::GetWidthAndHeightScale(uint32& width, uint32& height) const
{
	InterfacePtr<IPanelControlData> iPanelData(this, UseDefaultIID());

	// get the new scale value
	IControlView* iControlView = iPanelData->FindWidget (kScalePopupWID);
	InterfacePtr<ITextValue> textValue(iControlView, UseDefaultIID());
	flash_export::SizeAndFitSettings settings;
	settings.fSizeSelection = flash_export::kScale;
	settings.fScaleAmount = textValue->GetTextAsValue();

	// calculate the width and height
	Utils<IDynDocsPublicUtils>()->CalculateWidthAndHeightForExport(fWidthHeight.X(), fWidthHeight.Y(), settings, width, height);

}

//========================================================================================
// XFLExportDlgObserver::SetWidthAndHeight
//========================================================================================
void XFLExportDlgObserver::SetWidthAndHeight(uint32& width, uint32& height) const
{
	bool16 bNotifyOfChange = kFalse;
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	IControlView* iView = iPanelData->FindWidget (kWidthPopupWID);
	InterfacePtr<ITextValue> textValueX(iView, UseDefaultIID());
	iView = iPanelData->FindWidget (kHeightPopupWID);
	InterfacePtr<ITextValue> textValueY(iView, UseDefaultIID());
	if (!textValueX || !textValueY)
		return;

	// boundary check
	if (width < kMinSize)
	{
		width = kMinSize;
		bNotifyOfChange = kTrue;
	}
	else if (width > kMaxSize)
	{
		width = kMaxSize;
		bNotifyOfChange = kTrue;
	}

	// set the value into the widget
	textValueX->SetTextFromValue(width, /*invalidate*/ kTrue, bNotifyOfChange);

	// if we notified about a change, get the width and height again
	if (bNotifyOfChange)
	{
		width = ::ToUInt32(textValueX->GetTextAsValue());
		height = ::ToUInt32(textValueY->GetTextAsValue());
	}

	// boundary check
	bNotifyOfChange = kFalse;
	if (height < kMinSize)
	{
		height = kMinSize;
		bNotifyOfChange = kTrue;
	}
	else if (height > kMaxSize)
	{
		height = kMaxSize;
		bNotifyOfChange = kTrue;
	}

	// set the value into the widget
	textValueY->SetTextFromValue(height, /*invalidate*/ kTrue, bNotifyOfChange);

	// if we notified about a change, get the width and height again
	if (bNotifyOfChange)
	{
		width = ::ToUInt32(textValueX->GetTextAsValue());
		height = ::ToUInt32(textValueY->GetTextAsValue());
	}
}

//========================================================================================
// XFLExportDlgObserver::SetScale
//========================================================================================
void XFLExportDlgObserver::SetScale(uint32 width, uint32 height) const
{
	bool16 bNotifyOfChange = kFalse;
	InterfacePtr<IPanelControlData> iPanelData (this, UseDefaultIID());
	IControlView* iView = iPanelData->FindWidget (kScalePopupWID);
	InterfacePtr<ITextValue> scaleValue(iView, UseDefaultIID());
	PMReal currentScale = scaleValue->GetTextAsValue();

	PMReal scale = std::min(width / fWidthHeight.X(), height / fWidthHeight.Y());
	scale *= 100;

	// boundary checking
	if (scale < kMinScale)
	{
		scale = kMinScale;
		bNotifyOfChange = kTrue;
	}
	else if (scale > kMaxScale)
	{
		scale = kMaxScale;
		bNotifyOfChange = kTrue;
	}

	// need to compare the rounded values here because of partial 
	// scale values - see Watson 1738333
	if (::Round(scale) != ::Round(currentScale))
		scaleValue->SetTextFromValue(scale, /*invalidate*/ kTrue, bNotifyOfChange);
}

//========================================================================================
// XFLExportDlgObserver::UpdatePageAndSpreadSize
//========================================================================================
void XFLExportDlgObserver::UpdatePageAndSpreadSize(IDocument* iDocument, bool16 bPageRange)
{
	InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());
	InterfacePtr<IPageList> iPageList(iDocument, UseDefaultIID());

	UIDList pageUIDList(::GetDataBase(iDocument));

	// handle the page range case
	if (bPageRange)
	{
		InterfacePtr<IPanelControlData>	iPanelData(this, UseDefaultIID());
		IControlView* iControlView = iPanelData->FindWidget (kPagesPageRangeEditWID);
		InterfacePtr<ITextControlData> textData(iControlView, UseDefaultIID());
		PMString pageRangeText(textData->GetString());

		iPageList->PageRangeStringToUIDList(pageRangeText, &pageUIDList);
	}

	// handle the case where the range is invalid, or all pages are selected
	if (pageUIDList.Length() == 0)
	{
		for (int32 pageIndex = 0, pageCount = iPageList->GetPageCount(); pageIndex < pageCount; ++pageIndex)
			pageUIDList.Append(iPageList->GetNthPageUID(pageIndex));
	}

	// calculate the new page and spread sizes based on the uid list
	if (pageUIDList.Length() > 0 && Utils<IDynDocsPublicUtils>().Exists())
	{
		PMReal width, height;

		Utils<IDynDocsPublicUtils>()->CalculateTotalBounds(pageUIDList, true, width, height);
		fSpreadWidthHeight = PMPoint(width, height);

		// if we haven't initialized the selected width and height yet, do so
		if (fSelectedWidthHeight == PMPoint(0,0))
		{
			const UIDList *itemsUIDList(nil);
			InterfacePtr<IUIDListData> iUIDListData(this, UseDefaultIID());
			if (iUIDListData)
				itemsUIDList = iUIDListData->GetRef();
			if (itemsUIDList && itemsUIDList->size() > 0)
			{
				Utils<IDynDocsPublicUtils>()->CalculateSelectedBounds(*itemsUIDList, width, height);
				fSelectedWidthHeight = PMPoint(width, height);
			}
			else
				fSelectedWidthHeight = fSpreadWidthHeight;
		}
	}

	if (fSelectedWidgetID == kSelection_RadioButtonWidgetID)
		fWidthHeight = fSelectedWidthHeight;
	else
		fWidthHeight = fSpreadWidthHeight;

}

//========================================================================================
// XFLExportDlgObserver::UpdateWidthHeightAndScale
//========================================================================================
void XFLExportDlgObserver::UpdateWidthHeightAndScale() const
{
	InterfacePtr<IDialogController> iDialogController(this, UseDefaultIID());

	// get width and height based on selections
	uint32 width, height;
	if (iDialogController->GetTriStateControlData(kFitTo_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		GetWidthAndHeightFitTo(width, height);
	else if (iDialogController->GetTriStateControlData(kScale_RadioButtonWidgetID) == ITriStateControlData::kSelected)
		GetWidthAndHeightScale(width, height);
	else
		GetWidthAndHeight(width, height);

	// set the width and height
	SetWidthAndHeight(width, height);

	// set the scale percentage
	SetScale(width, height);
}

