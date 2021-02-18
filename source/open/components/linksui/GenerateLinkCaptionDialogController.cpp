//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/GenerateLinkCaptionDialogController.cpp $
//  
//  Owner: lance bushore
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

// ----- Interfaces -----
#include "IControlView.h"
#include "ICmdCollection.h"
#include "ILoadPlaceGunCmdData.h"
#include "ITextControlData.h"
#include "IPanelControlData.h"
#include "ILinkInfoProvider.h"
#include "ILinksUIPanelPrefs.h"
#include "IWidgetUtils.h"
#include "IDropDownListController.h"
#include "ITextModelCmds.h"
#include "IStringListControlData.h"
#include "ILinkCaptionPrefs.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ILinksUIUtils.h"
#include "ILayerList.h"
#include "IDocument.h"
#include "ILayerUtils.h"
#include "ILayerUIUtils.h"
#include "IDocumentLayer.h"
#include "IActiveContext.h"
#include "IStyleGroupListControlData.h"
#include "IWorkspace.h"
#include "IEVEUtils.h"

// ----- Includes -----

#include "CDialogController.h"
#include "PreferenceUtils.h"
#include "LinksUIID.h"
#include "UIDList.h"
#include "OpenPlaceID.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "LinksUIResDefs.h"

class GenerateLinkCaptionDialogController : public CDialogController
{
	public:
		// ----- Initialization -----
		
							GenerateLinkCaptionDialogController(IPMUnknown *boss);
		virtual				~GenerateLinkCaptionDialogController();
		
		// ----- Dialog protocol -----

		virtual void		InitializeDialogFields(IActiveContext* dlgContext);
		virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

CREATE_PMINTERFACE(GenerateLinkCaptionDialogController, kGenerateLinkCaptionDialogControllerImpl)

//========================================================================================
// CLASS GenerateLinkCaptionDialogController
//========================================================================================

GenerateLinkCaptionDialogController::GenerateLinkCaptionDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

GenerateLinkCaptionDialogController::~GenerateLinkCaptionDialogController()
{
}



static void SelectCorrectAlignmentEntry(IControlView* dropdownWidget, ILinkCaptionPrefs::CaptionAlignment whichAlignment)
{
	ASSERT_MSG(dropdownWidget != nil,"Failed to get layer dropdown widget.");
	int32 indexToSelect = 0;
	switch(whichAlignment)
	{
		case ILinkCaptionPrefs::kAlignBelow:
			indexToSelect = 0; break;
		case ILinkCaptionPrefs::kAlignAbove:
			indexToSelect = 1; break;
		case ILinkCaptionPrefs::kAlignLeft:
			indexToSelect = 2; break;
		case ILinkCaptionPrefs::kAlignRight:
			indexToSelect = 3; break;
		default:
			ASSERT_FAIL("unknown alignment option");
	}
	InterfacePtr<IDropDownListController> ddController(dropdownWidget,UseDefaultIID());
	ddController->Select(indexToSelect);
}

static ILinkCaptionPrefs::CaptionAlignment GetSelectedAlignmentOption(IControlView* dropdownWidget)
{
	InterfacePtr<const IDropDownListController> ddController(dropdownWidget,UseDefaultIID());
	switch(ddController->GetSelected())
	{
		case 0:
			return ILinkCaptionPrefs::kAlignBelow;
		case 1:
			return ILinkCaptionPrefs::kAlignAbove;
		case 2:
			return ILinkCaptionPrefs::kAlignLeft;
		case 3:
			return ILinkCaptionPrefs::kAlignRight;
	}
	ASSERT_FAIL("GetSelectedAlignmentOption got unexpected item selected. Did someone add to the options?");
	return ILinkCaptionPrefs::kAlignAbove;
}


static void BuildLayerDropdown(IControlView* dropdownWidget, const IDocument* doc, const PMString& layerNameToSelect)
{
	ASSERT_MSG(dropdownWidget != nil,"Failed to get layer dropdown widget.");
	InterfacePtr<IStringListControlData> ddStrings(dropdownWidget,UseDefaultIID());
	ddStrings->Clear(kFalse);
	ddStrings->AddString("#CaptionSameLayerAsImage",IStringListControlData::kEnd,kFalse);
	ddStrings->AddString("#CaptionActiveLayer",IStringListControlData::kEnd,kFalse);
	if(doc)
	{
		InterfacePtr<const ILayerList> layerList(doc,UseDefaultIID());
		int32 numUILayers = Utils<ILayerUtils>()->CountUILayers(layerList);
		for(int i = 0; i < numUILayers; ++i)
		{
			InterfacePtr<const IDocumentLayer> docLayer(Utils<ILayerUIUtils>()->QueryNthUILayer(layerList,i));
			ddStrings->AddString(docLayer->GetName(),IStringListControlData::kEnd,kFalse);
		}
		
	}
	int32 indexToSelect = ddStrings->GetIndex(layerNameToSelect);
	if(indexToSelect == IStringListControlData::kInvalidStringIndex)
		indexToSelect = 0; // CaptionSameLayerAsImage
	InterfacePtr<IDropDownListController> ddController(dropdownWidget,UseDefaultIID());
	ddController->Select(indexToSelect);
}

void GenerateLinkCaptionDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	// now update the UI from the current prefs settings.
	InterfacePtr<const ILinkCaptionPrefs> linkCaptionPrefs((ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, dlgContext));
	InterfacePtr<const IPanelControlData> dialogPanelData(this,UseDefaultIID());

	SetTextValue(kCaptionOffsetEditWidgetID,linkCaptionPrefs->GetFrameOffset(),dialogPanelData);

	BuildLayerDropdown(dialogPanelData->FindWidget(kCaptionLayerDropDownWidgetID),dlgContext->GetContextDocument(),linkCaptionPrefs->GetCaptionLayerName());
	
	SelectCorrectAlignmentEntry(dialogPanelData->FindWidget(kCaptionAlignmentDropDownWidgetID),linkCaptionPrefs->GetCaptionAlignment());
	
	SetTriStateControlData(kCaptionGroupWithImageCheckboxWidgetID,linkCaptionPrefs->GetGroupCaptionWithImage(),dialogPanelData); 

	IControlView* rowContainer = dialogPanelData->FindWidget(kSelectCaptionRowsPanelWidgetID);
	InterfacePtr<IPanelControlData> rowContainerPanelData(rowContainer,UseDefaultIID());
	
	// if we have too many rows, delete them now
	while(rowContainerPanelData->Length() > linkCaptionPrefs->GetNumCaptionLines())
	{
		rowContainerPanelData->RemoveWidget((int32)0,kTrue,kTrue);
	}

	// if we need more rows, add them now.
	while(rowContainerPanelData->Length() < linkCaptionPrefs->GetNumCaptionLines())
	{
		InterfacePtr<IControlView> newRowView ((IControlView*)::CreateObject(::GetDataBase(rowContainerPanelData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kDynamicCaptionRowResID),IID_ICONTROLVIEW));
		rowContainerPanelData->AddWidget(newRowView);
	}

	// now walk thru each row and set the data properly.
	for(int32 rowIndex = rowContainerPanelData->Length() -1; rowIndex >= 0; --rowIndex)
	{
		IControlView* rowView = rowContainerPanelData->GetWidget(rowIndex);
		Utils<ILinksUIUtils>()->SetupCaptionRowWidget(rowView,linkCaptionPrefs->GetNthBeforeString(rowIndex),linkCaptionPrefs->GetNthLinkInfoProviderName(rowIndex),linkCaptionPrefs->GetNthAfterString(rowIndex));
	}
	
	// now force the dialog to re-layout, since we may have changed how many rows we have.
	InterfacePtr<IControlView> dialogView(this,UseDefaultIID());
	Utils<IEVEUtils>()->ApplyEveLayout(dialogView);

}

static PMString GetSelectedDropdownString(IControlView* dropdownWidget)
{
	ASSERT_MSG(dropdownWidget != nil,"Failed to get dropdown widget.");
	InterfacePtr<const IDropDownListController> ddController(dropdownWidget,UseDefaultIID());
	InterfacePtr<IStringListControlData> ddStrings(dropdownWidget,UseDefaultIID());
	return ddStrings->GetString(ddController->GetSelected());
}

static UID GetSelectedParaStyleUID(IControlView* dropdownWidget)
{
	ASSERT_MSG(dropdownWidget != nil,"Failed to get dropdown widget.");
	InterfacePtr<const IStyleGroupListControlData> pListControlData ( dropdownWidget, UseDefaultIID() );
	return pListControlData->GetSelectedStyle();
}

void GenerateLinkCaptionDialogController::ApplyDialogFields(IActiveContext* dlgContext, const WidgetID& widgetId) 
{
#pragma unused(widgetId,dlgContext)
	InterfacePtr<ICommand> setCaptionPrefsCmd ( CmdUtils::CreateCommand( kSetLinkCaptionPrefsCmdBoss ) );
	InterfacePtr<ILinkCaptionPrefs> cmdData(setCaptionPrefsCmd,UseDefaultIID());
	
	cmdData->ClearAllCaptionLines();

	InterfacePtr<const IPanelControlData> dialogPanelData(this,UseDefaultIID());
	PMReal newOffset = GetTextValue(kCaptionOffsetEditWidgetID,dialogPanelData);
	cmdData->SetFrameOffset(newOffset);
	
	PMString layerName = GetSelectedDropdownString(dialogPanelData->FindWidget(kCaptionLayerDropDownWidgetID));
	cmdData->SetCaptionLayerName(layerName);
	
	cmdData->SetCaptionAlignment(GetSelectedAlignmentOption(dialogPanelData->FindWidget(kCaptionAlignmentDropDownWidgetID)));
	
	UID paraStyleUID = GetSelectedParaStyleUID(dialogPanelData->FindWidget(kCaptionParaStyleDropDownWidgetID));
	cmdData->SetCaptionParagraphStyleUID(paraStyleUID);

	cmdData->SetGroupCaptionWithImage(GetTriStateControlData(kCaptionGroupWithImageCheckboxWidgetID,dialogPanelData) == ITriStateControlData::kSelected);
	
	IControlView* rowContainer = dialogPanelData->FindWidget(kSelectCaptionRowsPanelWidgetID);
	InterfacePtr<const IPanelControlData> rowContainerPanelData(rowContainer,UseDefaultIID());
	for(int32 rowIndex = 0; rowIndex < rowContainerPanelData->Length(); ++rowIndex)
	{
		IControlView* rowView = rowContainerPanelData->GetWidget(rowIndex);
		InterfacePtr<const IPanelControlData> rowPanelData(rowView,UseDefaultIID());
		
		PMString beforeStr = GetTextControlData(kCaptionBeforeMetadataEditWidgetID,rowPanelData);
		beforeStr.ParseForEmbeddedCharacters();
		PMString afterStr = GetTextControlData(kCaptionAfterMetadataEditWidgetID,rowPanelData);
		afterStr.ParseForEmbeddedCharacters();
		cmdData->AddNewCaptionLine(beforeStr,GetSelectedDropdownString(rowPanelData->FindWidget(kCaptionMetadataDropDownWidgetID)),afterStr);
	}
	
	
	CmdUtils::ProcessCommand( setCaptionPrefsCmd ) ;
}

