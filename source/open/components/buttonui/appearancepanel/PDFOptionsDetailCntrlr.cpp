//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/PDFOptionsDetailCntrlr.cpp $
//  
//  Owner: Reena Agrawal
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

// ----- Interface Includes -----

#include "IconRsrcDefs.h"
#include "IControlView.h"
#include "IEVEUtils.h"
#include "IFormFieldSuite.h"
#include "FormFieldUIUtils.h"
#include "IPanelControlData.h"

// ----- Implementation Includes -----

#include "LocaleSetting.h"
#include "setspaneldetailcontroller.h"

#include "Utils.h"

#include "FormFieldUIID.h"
#include "BehaviorUIID.h"

//----------------------------------------------------------------------------------------

class PDFOptionsDetailController : public CPMUnknown<IPanelDetailController>
{
public:

	enum {
		kButtonOptionsConfigDisabled=0, 
		kButtonOptionsConfigEnabled,
		kFormFieldOptionsConfig,
		kListAndComboOptionsConfig,
		kListOptionsConfig,			// this means only lists selected, show multiple select..
		kTextFieldOptionsConfig,
		kCheckBoxOptionsConfig,
		kMainConfig,
		kNumPanelConfigs
	};

	PDFOptionsDetailController(IPMUnknown *boss);
	virtual void	ShowDetailLevel(int16 nthLevel);
	virtual int16	GetDefaultDetailLevel() const { return 1; }
	void ReadWrite(IPMStream *s, ImplementationID prop);
	virtual void RotateDetailLevel();
	virtual int16 GetDetailLevel() const;
	virtual int16 GetNumDetailLevels() const;

private:
	void ShowPanelConfig (int32 detailLevel); 
	void UpdatePanelSize(IControlView* panelView, int32 fullyExpanded);
	enum {kDefaultPanelConfig = kButtonOptionsConfigDisabled};
	int32 fCurrentConfig;
};

//========================================================================================
// METHODS PDFOptionsDetailController
//========================================================================================

CREATE_PERSIST_PMINTERFACE(PDFOptionsDetailController, kPDFOptionsDetailControllerImpl)

PDFOptionsDetailController::PDFOptionsDetailController(IPMUnknown *boss) :
	CPMUnknown<IPanelDetailController>(boss), fCurrentConfig (kDefaultPanelConfig)
{
}

void PDFOptionsDetailController::ReadWrite(IPMStream *s, ImplementationID prop)
{
	bool16 readingFromResource = kFalse;
	s->XferBool(readingFromResource);
	s->XferInt32(fCurrentConfig);
}

void PDFOptionsDetailController::RotateDetailLevel()
{
	// This should not be doing anything as the detail levels will be controlled by the current selection..
	return;
}

void PDFOptionsDetailController::ShowDetailLevel(int16 nthLevel)
{
	if (fCurrentConfig != nthLevel)
	{
		PreDirty ();
		fCurrentConfig = nthLevel;
	}
	ShowPanelConfig(fCurrentConfig);
}

int16 PDFOptionsDetailController::GetDetailLevel() const
{
	return fCurrentConfig;
}

int16 PDFOptionsDetailController::GetNumDetailLevels() const
{
	return kNumPanelConfigs;
}

void PDFOptionsDetailController::ShowPanelConfig(int32 detailLevel)
{
	InterfacePtr<IControlView> iPanelView(this, UseDefaultIID ());
	UpdatePanelSize(iPanelView, detailLevel);
}

void PDFOptionsDetailController::UpdatePanelSize(IControlView* panelView, int32 detailLevel)
{
	InterfacePtr<IPanelControlData> iPanelData(panelView, UseDefaultIID());
	IControlView* iConstraintsExpanderIconView = iPanelData->FindWidget(kPDFOptionsExpanderWidgetID);

	// Button and Form field generic ones
	IControlView* descriptionLabelWidgetView = iPanelData->FindWidget(kPDFDescriptionLabelWID);
	IControlView* descriptionWidgetView = iPanelData->FindWidget(kButtonPDFDescriptionWID);
	IControlView* printableWidgetView = iPanelData->FindWidget(kButtonPDFPrintableCheckBoxWID);

	// Form field generic ones
	IControlView* readOnlyWidgetView = iPanelData->FindWidget(kReadOnlyCheckBoxWidgetID);
	IControlView* requiredWidgetView = iPanelData->FindWidget(kRequiredCheckBoxWidgetID);

	// Check box and Radio buttons specific
	IControlView* selectedByDefaultWidgetView = iPanelData->FindWidget(kSelectedByDefaultCheckBoxWidgetID);

	// Text field specific
	IControlView* passwordWidgetView = iPanelData->FindWidget(kPasswordCheckBoxWidgetID);
	IControlView* scrollableWidgetView = iPanelData->FindWidget(kScrollableCheckBoxWidgetID);
	IControlView* multiLineWidgetView = iPanelData->FindWidget(kMultilineCheckBoxWidgetID);

	// Combo box and List box specific
	IControlView* pdfOptionsPanelWidgetView = iPanelData->FindWidget(kPDFOptionsPanelWID);
	IControlView* listPanelWidgetView = iPanelData->FindWidget(kListOptionsPanelWidgetID);
	IControlView* listItemsLabelWidgetView = iPanelData->FindWidget(kListItemsLabelWidgetID);
	IControlView* listItemTextBoxWidgetView = iPanelData->FindWidget(kListItemTextNodeWID);
	IControlView* itemAddButtonWidgetView = iPanelData->FindWidget(kAddListOptionButtonWidgetID);
	IControlView* itemRemoveButtonWidgetView = iPanelData->FindWidget(kRemoveListOptionButtonWidgetID);
	IControlView* listItemsBorderWidgetView = iPanelData->FindWidget(kListItemsBorderWidgetID);
	IControlView* listTreeWidgetView = iPanelData->FindWidget(kListItemsWidgetID);
	IControlView* multipleSelectionWidgetView = iPanelData->FindWidget(kMultipleSelectionCheckBoxWidgetID);
	IControlView* sortItemsWidgetView = iPanelData->FindWidget(kSortItemsCheckBoxWidgetID);

	// Text, Combo and List box specific
	IControlView* fontTypePanelView = iPanelData->FindWidget(kFormFontsPanelWidgetID);
	IControlView* fontSizePanelView = iPanelData->FindWidget(kFontSizePanelWID);
	IControlView* fontSizeStaticWidgetView = iPanelData->FindWidget(kFontSizeStaticWID);
	IControlView* fontSizeEditBoxWidgetView = iPanelData->FindWidget(kFontSizeEditBoxWidgetID);
	IControlView* rtlCheckBoxWidgetView = iPanelData->FindWidget(kMERTLOptionCheckBoxWidgetID);
	IControlView* exportValueStaticWidgetView = iPanelData->FindWidget(kExportValueStaticWID);
	IControlView* exportValueEditWidgetView = iPanelData->FindWidget(kExportValueEditWidgetID);
	
	if (detailLevel == kMainConfig)
	{
		if (iConstraintsExpanderIconView->GetRsrcID() != kTreeBranchCollapsedRsrcID)
			iConstraintsExpanderIconView->SetRsrcID(kTreeBranchCollapsedRsrcID);

		// Hide everything..
		pdfOptionsPanelWidgetView->HideView();
		descriptionLabelWidgetView->HideView();
		descriptionWidgetView->HideView();
		printableWidgetView->HideView();
		readOnlyWidgetView->HideView();
		requiredWidgetView->HideView();
		selectedByDefaultWidgetView->HideView();
		passwordWidgetView->HideView();
		scrollableWidgetView->HideView();
		multiLineWidgetView->HideView();
		listPanelWidgetView->HideView();
		listItemsLabelWidgetView->HideView();
		listItemTextBoxWidgetView->HideView();
		itemAddButtonWidgetView->HideView();
		itemRemoveButtonWidgetView->HideView();
		listItemsBorderWidgetView->HideView();
		listTreeWidgetView->HideView();
		multipleSelectionWidgetView->HideView();
		sortItemsWidgetView->HideView();
		fontTypePanelView->HideView();
		fontSizePanelView->HideView();
		fontSizeStaticWidgetView->HideView();
		fontSizeEditBoxWidgetView->HideView();
		rtlCheckBoxWidgetView->HideView();
		exportValueStaticWidgetView->HideView();
		exportValueEditWidgetView->HideView();
	}
	else
	{
		descriptionLabelWidgetView->ShowView();
		descriptionWidgetView->ShowView();
		printableWidgetView->ShowView();

		if (iConstraintsExpanderIconView->GetRsrcID() != kTreeBranchExpandedRsrcID)
			iConstraintsExpanderIconView->SetRsrcID(kTreeBranchExpandedRsrcID);

		if (detailLevel == kButtonOptionsConfigDisabled || detailLevel == kButtonOptionsConfigEnabled)
		{
			if (detailLevel == kButtonOptionsConfigEnabled)
			{
				descriptionLabelWidgetView->Enable();
				descriptionWidgetView->Enable();
				printableWidgetView->Enable();
			}
			else
			{
				descriptionLabelWidgetView->Disable();
				descriptionWidgetView->Disable();
				printableWidgetView->Disable();
			}

			// Specific ones to be hidden
			pdfOptionsPanelWidgetView->HideView();
			readOnlyWidgetView->HideView();
			requiredWidgetView->HideView();
			selectedByDefaultWidgetView->HideView();
			passwordWidgetView->HideView();
			scrollableWidgetView->HideView();
			multiLineWidgetView->HideView();
			listPanelWidgetView->HideView();
			listItemsLabelWidgetView->HideView();
			listItemTextBoxWidgetView->HideView();
			itemAddButtonWidgetView->HideView();
			itemRemoveButtonWidgetView->HideView();
			listItemsBorderWidgetView->HideView();
			listTreeWidgetView->HideView();
			multipleSelectionWidgetView->HideView();
			sortItemsWidgetView->HideView();
			fontTypePanelView->HideView();
			fontSizePanelView->HideView();
			fontSizeStaticWidgetView->HideView();
			fontSizeEditBoxWidgetView->HideView();
			rtlCheckBoxWidgetView->HideView();
			exportValueStaticWidgetView->HideView();
			exportValueEditWidgetView->HideView();
		}
		else if (detailLevel == kCheckBoxOptionsConfig)
		{
			descriptionLabelWidgetView->Enable();
			descriptionWidgetView->Enable();
			printableWidgetView->Enable();
			
			pdfOptionsPanelWidgetView->ShowView();
			readOnlyWidgetView->ShowView();
			requiredWidgetView->ShowView();
			selectedByDefaultWidgetView->ShowView();
			passwordWidgetView->HideView();
			scrollableWidgetView->HideView();
			multiLineWidgetView->HideView();
			listPanelWidgetView->HideView();
			listItemsLabelWidgetView->HideView();
			listItemTextBoxWidgetView->HideView();
			itemAddButtonWidgetView->HideView();
			itemRemoveButtonWidgetView->HideView();
			listItemsBorderWidgetView->HideView();
			listTreeWidgetView->HideView();
			multipleSelectionWidgetView->HideView();
			sortItemsWidgetView->HideView();
			fontTypePanelView->HideView();
			fontSizePanelView->HideView();
			fontSizeStaticWidgetView->HideView();
			fontSizeEditBoxWidgetView->HideView();
			rtlCheckBoxWidgetView->HideView();
			exportValueStaticWidgetView->ShowView();
			exportValueEditWidgetView->ShowView();
		}
		else if (detailLevel == kTextFieldOptionsConfig)
		{
			descriptionLabelWidgetView->Enable();
			descriptionWidgetView->Enable();
			printableWidgetView->Enable();

			pdfOptionsPanelWidgetView->ShowView();
			readOnlyWidgetView->ShowView();
			requiredWidgetView->ShowView();
			selectedByDefaultWidgetView->HideView();
			passwordWidgetView->ShowView();
			scrollableWidgetView->ShowView();
			multiLineWidgetView->ShowView();
			listPanelWidgetView->HideView();
			listItemsLabelWidgetView->HideView();
			listItemTextBoxWidgetView->HideView();
			itemAddButtonWidgetView->HideView();
			itemRemoveButtonWidgetView->HideView();
			listItemsBorderWidgetView->HideView();
			listTreeWidgetView->HideView();
			multipleSelectionWidgetView->HideView();
			sortItemsWidgetView->HideView();
			fontTypePanelView->ShowView();
			fontSizePanelView->ShowView();
			fontSizeStaticWidgetView->ShowView();
			fontSizeEditBoxWidgetView->ShowView();
			exportValueStaticWidgetView->HideView();
			exportValueEditWidgetView->HideView();

			// ME RTL shoule be shown only if the featureset is ME.
			if (LocaleSetting::GetLocale().GetLanguageFS() == kRightToLeftLanguageFS)
				rtlCheckBoxWidgetView->ShowView();
			else
				rtlCheckBoxWidgetView->HideView();
		}
		else if(detailLevel == kListAndComboOptionsConfig || detailLevel == kListOptionsConfig)
		{
			descriptionLabelWidgetView->Enable();
			descriptionWidgetView->Enable();
			printableWidgetView->Enable();

			pdfOptionsPanelWidgetView->ShowView();
			readOnlyWidgetView->ShowView();
			requiredWidgetView->ShowView();
			selectedByDefaultWidgetView->HideView();
			passwordWidgetView->HideView();
			scrollableWidgetView->HideView();
			multiLineWidgetView->HideView();
			listPanelWidgetView->ShowView();
			listItemsLabelWidgetView->ShowView();
			listItemTextBoxWidgetView->ShowView();
			itemAddButtonWidgetView->ShowView();
			itemRemoveButtonWidgetView->ShowView();
			listItemsBorderWidgetView->ShowView();
			listTreeWidgetView->ShowView();
			sortItemsWidgetView->ShowView();
			fontTypePanelView->ShowView();
			fontSizePanelView->ShowView();
			fontSizeStaticWidgetView->ShowView();
			fontSizeEditBoxWidgetView->ShowView();
			exportValueStaticWidgetView->HideView();
			exportValueEditWidgetView->HideView();

			// ME RTL shoule be shown only if the featureset is ME.
			if (LocaleSetting::GetLocale().GetLanguageFS() == kRightToLeftLanguageFS)
				rtlCheckBoxWidgetView->ShowView();
			else
				rtlCheckBoxWidgetView->HideView();
			
			if (detailLevel == kListOptionsConfig)
				multipleSelectionWidgetView->ShowView();
			else
				multipleSelectionWidgetView->HideView();
		}
		else if (detailLevel == kFormFieldOptionsConfig)
		{
			descriptionLabelWidgetView->Enable();
			descriptionWidgetView->Enable();
			printableWidgetView->Enable();

			pdfOptionsPanelWidgetView->HideView();
			readOnlyWidgetView->ShowView();
			requiredWidgetView->ShowView();
			selectedByDefaultWidgetView->HideView();
			passwordWidgetView->HideView();
			scrollableWidgetView->HideView();
			multiLineWidgetView->HideView();
			listPanelWidgetView->HideView();
			listItemsLabelWidgetView->HideView();
			listItemTextBoxWidgetView->HideView();
			itemAddButtonWidgetView->HideView();
			itemRemoveButtonWidgetView->HideView();
			listItemsBorderWidgetView->HideView();
			listTreeWidgetView->HideView();
			multipleSelectionWidgetView->HideView();
			sortItemsWidgetView->HideView();
			fontTypePanelView->HideView();
			fontSizePanelView->HideView();
			fontSizeStaticWidgetView->HideView();
			fontSizeEditBoxWidgetView->HideView();
			rtlCheckBoxWidgetView->HideView();
			exportValueStaticWidgetView->HideView();
			exportValueEditWidgetView->HideView();
		}
	}

	Utils<IEVEUtils>()->ApplyEveLayout(panelView);
	panelView->Invalidate();      
}
