//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/ChooseLinksColumnsDialogController.cpp $
//  
//  Owner: Yeming Liu
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
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ILinkInfoProvider.h"
#include "ILinksUIPanelPrefs.h"
#include "ITreeViewMgr.h"
#include "IWidgetUtils.h"
#include "IDropDownListController.h"
#include "IViewListBoxControlData.h"
#include "IListBoxController.h"
#include "IListBoxAttributes.h"

// ----- Includes -----

#include "CDialogController.h"
#include "LocaleSetting.h"
#include "PreferenceUtils.h"
#include "LinksUIID.h"
#include "LinksUIResDefs.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "IWidgetUtils.h"

class ChooseLinksColumnsDialogController : public CDialogController
{
	public:
		// ----- Initialization -----
		
							ChooseLinksColumnsDialogController(IPMUnknown *boss);
		virtual				~ChooseLinksColumnsDialogController();
		
		// ----- Dialog protocol -----

		virtual void		InitializeDialogFields(IActiveContext* dlgContext);
		virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

CREATE_PMINTERFACE(ChooseLinksColumnsDialogController, kChooseLinksColumnsDialogControllerImpl)

//========================================================================================
// CLASS ChooseLinksColumnsDialogController
//========================================================================================

ChooseLinksColumnsDialogController::ChooseLinksColumnsDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

ChooseLinksColumnsDialogController::~ChooseLinksColumnsDialogController()
{
}

const int kLinksUISmallRowSize = 16;
const int kLinksUIRegularRowSize = 22;
const int kLinksUILargeRowSize = 40;

void AddWidgetsAndInitialize(const ILinkInfoProvider* infoProvider,IViewListBoxControlData* listData,const K2Vector<PMString>& showingNames, const K2Vector<PMString>& moreInfoNames)
{
	PMString descriptionStr = infoProvider->GetInfoDescriptionString();
	
	InterfacePtr<IControlView> rowView ((IControlView*)::CreateObject(::GetDataBase(listData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinksUIDynamicPrefRowResID),IID_ICONTROLVIEW));
	InterfacePtr<const IPanelControlData> rowPanelData(rowView,UseDefaultIID());
	IControlView* labelView = rowPanelData->FindWidget(kLinksUIPrefRowLabelWidgetID);

	// set the data correctly for the 2 checkboxes
	IControlView* showColumnCheckboxView = rowPanelData->FindWidget(kLinksUIPrefRowShowColumnCheckboxWidgetID);
	InterfacePtr<ITriStateControlData> checkboxData(showColumnCheckboxView,UseDefaultIID());
	K2Vector<PMString>::const_iterator providerNameIter = std::lower_bound(showingNames.begin(),showingNames.end(),descriptionStr);
	if(providerNameIter != showingNames.end() && *providerNameIter == descriptionStr)
		checkboxData->Select();
	else
		checkboxData->Deselect();

	IControlView* showMoreInfoCheckboxView = rowPanelData->FindWidget(kLinksUIPrefRowShowInfoCheckboxWidgetID);
	InterfacePtr<ITriStateControlData> moreInfoCheckboxData(showMoreInfoCheckboxView,UseDefaultIID());
	providerNameIter = std::lower_bound(moreInfoNames.begin(),moreInfoNames.end(),descriptionStr);
	if(providerNameIter != moreInfoNames.end() && *providerNameIter == descriptionStr)
		moreInfoCheckboxData->Select();
	else
		moreInfoCheckboxData->Deselect();

	if(::GetClass(infoProvider) == kLinkInfoNameProviderBoss) // they can remove any column except name.
		rowView->Disable();
		
//		PMRect newFrame(0,0,listboxWidth,listAttr->GetCellHeight());
//		checkboxView->SetFrame(newFrame);
	InterfacePtr<ITextControlData>	labelText(labelView, UseDefaultIID());
	labelText->SetString(descriptionStr);	
	listData->Add(rowView, IViewListBoxControlData::kEnd, kFalse, kFalse);	

}

void ChooseLinksColumnsDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
#pragma unused(dlgContext)
	InterfacePtr<IPanelControlData> dialogPanelData(this,UseDefaultIID());
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));

	IControlView *listWidget = dialogPanelData->FindWidget(kLinksUIPrefTreeWidgetID);

	InterfacePtr< IViewListBoxControlData > listData(listWidget,IID_ILISTCONTROLDATA);
	InterfacePtr<IListBoxController> listCntl( listWidget, UseDefaultIID() );
	
	// wipe out the current contents of the listbox.
	listData->Clear(kFalse,kFalse);
	
	// build a sorted list of strings  for the prefs which are showing, so we can check the appropriate boxes.
	K2Vector<PMString> showingNames;
	const int32 numShowingProviders = linksUIPrefs->GetNumShowingInfoColumns();
	for(int showingIndex = 0; showingIndex < numShowingProviders; ++showingIndex)
	{
		InterfacePtr<const ILinkInfoProvider> showingProvider(linksUIPrefs->QueryNthShowingInfoColumn(showingIndex));
		showingNames.push_back(showingProvider->GetInfoDescriptionString());
	}
	std::sort(showingNames.begin(),showingNames.end());

	K2Vector<PMString> moreInfoNames;
	const int32 numMoreInfoProviders = linksUIPrefs->GetNumMoreInfoProviders();
	for(int showingIndex = 0; showingIndex < numMoreInfoProviders; ++showingIndex)
	{
		InterfacePtr<const ILinkInfoProvider> moreInfoProvider(linksUIPrefs->QueryNthMoreInfoProvider(showingIndex));
		moreInfoNames.push_back(moreInfoProvider->GetInfoDescriptionString());
	}
	std::sort(moreInfoNames.begin(),moreInfoNames.end());

	const int32 numProviders = linksUIPrefs->GetNumInfoProviders();
	
	// now add all the rest at the end.
	for(int index = 0; index < numProviders; ++index)
	{
		InterfacePtr<const ILinkInfoProvider> infoProvider(linksUIPrefs->QueryNthInfoProvider(index));
		AddWidgetsAndInitialize(infoProvider,listData,showingNames,moreInfoNames);
	}
	
	listData->Refresh();

	InterfacePtr<IDropDownListController> ddController(dialogPanelData->FindWidget(kLinksUIRowSizeDropDownWidgetID),UseDefaultIID());
	if(linksUIPrefs->GetCurrentRowHeight() < kLinksUIRegularRowSize)
		ddController->Select(0);
	else if(linksUIPrefs->GetCurrentRowHeight() < kLinksUILargeRowSize)
		ddController->Select(1);
	else
		ddController->Select(2);
		

	SetTriStateControlData(kLinksUIPrefsCollapseMultipleCheckboxWidgetID,linksUIPrefs->GetCollapseMultipleLinksToSameResource(),dialogPanelData);
	SetTriStateControlData(kLinksUIShowThumbnailCheckboxWidgetID,linksUIPrefs->GetShowLinkThumbnail(),dialogPanelData);
	SetTriStateControlData(kShowLinkInfoThumbnailCheckboxWidgetID,linksUIPrefs->GetShowLinkInfoThumbnail(),dialogPanelData);
	
}

//----------------------------------------------------------------------------------------
// ChooseLinksColumnsDialogController:: ApplyFields()
//----------------------------------------------------------------------------------------

void ChooseLinksColumnsDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
#pragma unused(myContext,widgetId)
	InterfacePtr<IPanelControlData> dialogPanelData(this,UseDefaultIID());
	IControlView *listWidget = dialogPanelData->FindWidget(kLinksUIPrefTreeWidgetID);

	InterfacePtr< const IViewListBoxControlData > listData(listWidget,IID_ILISTCONTROLDATA);
	ASSERT_MSG(listData,"Failed to get IViewListBoxControlData from list?");
	
	K2Vector<PMString> showingNames;
	K2Vector<PMString> moreInfoNames;
	for(int i = listData->Length() - 1; i >=0; --i)
	{
		const IControlView* nthWidget = (*listData)[i];
		ASSERT_MSG(nthWidget,"Failed to get nth widget from list?");
		InterfacePtr<const IPanelControlData> rowPanelData(nthWidget,UseDefaultIID());
		IControlView* labelView = rowPanelData->FindWidget(kLinksUIPrefRowLabelWidgetID);
		InterfacePtr<const ITextControlData> textData(labelView,UseDefaultIID());
		PMString controlName = textData->GetString();

		const IControlView* showColumnCheckboxView = rowPanelData->FindWidget(kLinksUIPrefRowShowColumnCheckboxWidgetID);
		InterfacePtr<const ITriStateControlData> checkboxData(showColumnCheckboxView,UseDefaultIID());
		if(checkboxData->IsSelected())
		{
			showingNames.push_back(controlName);
		}
		IControlView* showMoreInfoCheckboxView = rowPanelData->FindWidget(kLinksUIPrefRowShowInfoCheckboxWidgetID);
		InterfacePtr<const ITriStateControlData> moreInfoCheckboxData(showMoreInfoCheckboxView,UseDefaultIID());
		if(moreInfoCheckboxData->IsSelected())
		{
			moreInfoNames.push_back(controlName);
		}
	}
	
	InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));

	// see what was showing originally. We want these things to stay in the panel in the same order they were. Newly turned on stuff can go at the end.
	K2Vector<ILinkInfoProvider*> newShowingProviders,newMoreInfoProviders;
	const int32 numShowingProviders = linksUIPrefs->GetNumShowingInfoColumns();
	for(int showingIndex = 0; showingIndex < numShowingProviders; ++showingIndex)
	{
		InterfacePtr<ILinkInfoProvider> oldShowingProvider(linksUIPrefs->QueryNthShowingInfoColumn(showingIndex));
		if(std::find(showingNames.begin(),showingNames.end(),oldShowingProvider->GetInfoDescriptionString()) != showingNames.end())
			newShowingProviders.push_back(oldShowingProvider);
	}

	const int32 numProviders = linksUIPrefs->GetNumInfoProviders();
	for(int index = 0; index < numProviders; ++index)
	{
		InterfacePtr<ILinkInfoProvider> infoService(linksUIPrefs->QueryNthInfoProvider(index));
		if(std::find(showingNames.begin(),showingNames.end(),infoService->GetInfoDescriptionString()) != showingNames.end() && 
			std::find(newShowingProviders.begin(),newShowingProviders.end(),infoService) == newShowingProviders.end())
			newShowingProviders.push_back(infoService);
		if(std::find(moreInfoNames.begin(),moreInfoNames.end(),infoService->GetInfoDescriptionString()) != moreInfoNames.end())
			newMoreInfoProviders.push_back(infoService);
	}
	linksUIPrefs->SetShowingInfoColumns(newShowingProviders);
	linksUIPrefs->SetMoreInfoProviders(newMoreInfoProviders);
	
	InterfacePtr<const IDropDownListController> ddController(dialogPanelData->FindWidget(kLinksUIRowSizeDropDownWidgetID),UseDefaultIID());
	if(ddController->GetSelected() == 0)
		linksUIPrefs->SetCurrentRowHeight(kLinksUISmallRowSize);
	else if(ddController->GetSelected() == 1)
		linksUIPrefs->SetCurrentRowHeight(kLinksUIRegularRowSize);
	else
		linksUIPrefs->SetCurrentRowHeight(kLinksUILargeRowSize);
		

	linksUIPrefs->SetCollapseMultipleLinksToSameResource(GetTriStateControlData(kLinksUIPrefsCollapseMultipleCheckboxWidgetID,dialogPanelData) == ITriStateControlData::kSelected);
	linksUIPrefs->SetShowLinkThumbnail(GetTriStateControlData(kLinksUIShowThumbnailCheckboxWidgetID,dialogPanelData) == ITriStateControlData::kSelected);
	linksUIPrefs->SetShowLinkInfoThumbnail(GetTriStateControlData(kShowLinkInfoThumbnailCheckboxWidgetID,dialogPanelData) == ITriStateControlData::kSelected);

	
}

