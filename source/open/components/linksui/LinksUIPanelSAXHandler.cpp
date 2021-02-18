//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelSAXHandler.cpp $
//  
//  Owner: Paul Sorrick
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

#include "BasePanelSAXHandler.h"
#include "IApplication.h"
#include "IControlView.h"
#include "ISAXServices.h"
#include "IPanelControlData.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkInfoProvider.h"
#include "ISplitterPanelController.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILinksUIUtils.h"
#include "ISplitterPanelControlData.h"

// ----- Implementation Includes -----

#include "LinksUIID.h"
#include "LinksUIPanelWorkspaceDefs.h"
#include "widgetid.h"
#include "PreferenceUtils.h"
#include "Utils.h"

//========================================================================================
// Class LinksUIPanelSAXHandler
//========================================================================================

class LinksUIPanelSAXHandler : public BasePanelSAXHandler
{
	typedef BasePanelSAXHandler inherited;
	
public:
	LinksUIPanelSAXHandler(IPMUnknown *boss);
	virtual ~LinksUIPanelSAXHandler();

	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer);
	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);
	
private:
	K2Vector<ClassID> fInfoColumnClasses,fMoreInfoClasses;
	K2Vector<int32> fInfoColumnWidths;
		
};


//========================================================================================
// METHODS LinksUIPanelSAXHandler
//========================================================================================
CREATE_PMINTERFACE(LinksUIPanelSAXHandler, kLinksUIPanelSAXHandlerImpl)

LinksUIPanelSAXHandler::LinksUIPanelSAXHandler(IPMUnknown *boss) :
	inherited(boss)
{
}

LinksUIPanelSAXHandler::~LinksUIPanelSAXHandler()
{
}

//----------------------------------------------------------------------------------------
// Register
//----------------------------------------------------------------------------------------
void LinksUIPanelSAXHandler::Register(ISAXServices* saxServices, IPMUnknown *importer)
{
	saxServices->RegisterElementHandler( WideString(""), WideString(LinksUIPanelWorkspaceDefs::kLinksUIPanelOptionsXMLTag), this );

	inherited::Register(saxServices, importer);
}

//----------------------------------------------------------------------------------------
// StartElement
//----------------------------------------------------------------------------------------
void LinksUIPanelSAXHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{
	#pragma unused(uri,localname)
	if (qname == WideString(LinksUIPanelWorkspaceDefs::kLinksUIPanelOptionsXMLTag))
	{//
		fInfoColumnClasses.clear();
		fMoreInfoClasses.clear();
		fInfoColumnWidths.clear();
		
		// Get the current prefs
		InterfacePtr<ILinksUIPanelPrefs> linksUIPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		if (!linksUIPanelPrefs)
			return;

		int32 rowHeight = linksUIPanelPrefs->GetCurrentRowHeight();
		
		ClassID sortClass = kInvalidClass;
		ClassID secondarySortClass = kInvalidClass;
		const ILinkInfoProvider* sortProvider = linksUIPanelPrefs->GetSortInfoProvider();
		if(sortProvider)
			sortClass = ::GetClass(sortProvider);
		const ILinkInfoProvider* secondarySortProvider = linksUIPanelPrefs->GetSecondarySortInfoProvider();
		if(secondarySortProvider)
			secondarySortClass = ::GetClass(secondarySortProvider);

		bool16 sortAscending = linksUIPanelPrefs->GetSortLinksAscending();
		bool16 showThumbnail = linksUIPanelPrefs->GetShowLinkThumbnail();
		bool16 showInfoThumbnail = linksUIPanelPrefs->GetShowLinkInfoThumbnail();
		bool16 collapseMultiple = linksUIPanelPrefs->GetCollapseMultipleLinksToSameResource();

		int32 newRowHeight = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelRowHeightXMLAttributeName, rowHeight);
		int32 newSortClass = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSorterClassXMLAttributeName, sortClass.Get());
		int32 newSecondarySortClass = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSecondarySorterClassXMLAttributeName, secondarySortClass.Get());
		bool16 newSortAscending = GetAttributeBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUISortAscendingXMLAttributeName, sortAscending);
		bool16 newShowThumbnail = GetAttributeBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIShowThumbnailXMLAttributeName, showThumbnail);
		bool16 newShowInfoThumbnail = GetAttributeBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIShowInfoThumbnailXMLAttributeName, showInfoThumbnail);
		bool16 newCollapseMultiple = GetAttributeBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUICollapseMultipleXMLAttributeName, collapseMultiple);

		linksUIPanelPrefs->SetCurrentRowHeight(newRowHeight);
		linksUIPanelPrefs->SetSortLinksAscending(newSortAscending);
		linksUIPanelPrefs->SetShowLinkThumbnail(newShowThumbnail);
		linksUIPanelPrefs->SetShowLinkInfoThumbnail(newShowInfoThumbnail);
		linksUIPanelPrefs->SetCollapseMultipleLinksToSameResource(newCollapseMultiple);
		
		// in order to set the secondary sort provider, we set it as the sort provider first, then the primary one. This bumps the secondary one down.
		InterfacePtr<IK2ServiceRegistry>	serviceR(GetExecutionContextSession(), UseDefaultIID());
		if(newSecondarySortClass != kInvalidClass)
		{
			InterfacePtr<const IK2ServiceProvider> secondarySortServiceProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, secondarySortClass));
			InterfacePtr<const ILinkInfoProvider> secondarySortInfoProvider(secondarySortServiceProvider,UseDefaultIID());
			if(secondarySortInfoProvider)
				linksUIPanelPrefs->SetSortInfoProvider(secondarySortInfoProvider);
		}
		if(newSortClass != kInvalidClass)
		{
			InterfacePtr<const IK2ServiceProvider> sortServiceProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, newSortClass));
			InterfacePtr<const ILinkInfoProvider> sortInfoProvider(sortServiceProvider,UseDefaultIID());
			if(sortInfoProvider)
				linksUIPanelPrefs->SetSortInfoProvider(sortInfoProvider);
		}

		// Splitter position
		InterfacePtr<const IPanelControlData> myWidgets(this, UseDefaultIID());
		const IControlView* splitter = myWidgets->FindWidget(kLinkUISplitterPanelWidgetID);
		InterfacePtr<ISplitterPanelController> splitterController(splitter, UseDefaultIID());
		if (splitterController)
		{
			int32 splitterPos = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSplitterPositionXMLAttributeName, -1);
			if (splitterPos != -1)
			{
				splitterController->SetSplitterEdge( splitterPos );
				splitterController->SyncPanelsToSplitter();
			}
			InterfacePtr<ISplitterPanelControlData> splitterControlData(splitter, UseDefaultIID());
			bool16 newHideInfoPane = GetAttributeBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoPaneHiddenXMLAttributeName, splitterControlData->IsSinglePanelVisible());
			if(newHideInfoPane != splitterControlData->IsSinglePanelVisible())
				Utils<ILinksUIUtils>()->ToggleLinkInfoSectionVisibility(false,false);
		}
	} 
	else if(qname == WideString(LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnXMLTag))
	{
		int32 columnInfoClass = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelInfoClassXMLAttributeName, 0);
		int32 columnWidth = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnWidthXMLAttributeName, 50);
		fInfoColumnClasses.push_back(columnInfoClass);
		fInfoColumnWidths.push_back(columnWidth);
	}
	else if(qname == WideString(LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoXMLTag))
	{
		int32 moreInfoClass = GetAttributeInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelInfoClassXMLAttributeName, 0);
		fMoreInfoClasses.push_back(moreInfoClass);
	}
	else
		ASSERT_FAIL("LinksUIPanelSAXHandler called for an element it didn't register to receive");
}

void LinksUIPanelSAXHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname)
{
	#pragma unused(uri,localname)
	if (qname == WideString(LinksUIPanelWorkspaceDefs::kLinksUIPanelOptionsXMLTag))
	{
		InterfacePtr<ILinksUIPanelPrefs> linksUIPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		InterfacePtr<IK2ServiceRegistry>	serviceR(GetExecutionContextSession(), UseDefaultIID());
		K2Vector<ILinkInfoProvider*> providers;
		int numRemovedCol = 0;
		for(unsigned int i = 0; i < fInfoColumnClasses.size(); ++i)
		{
			InterfacePtr<const IK2ServiceProvider> infoService(serviceR->QueryServiceProviderByClassID(kLinkInfoService, fInfoColumnClasses[i]));
			InterfacePtr<ILinkInfoProvider> infoProvider(infoService,UseDefaultIID());
			if(infoProvider)
				providers.push_back(infoProvider);
			else {
				// ID-4212068 - numRemovedCol will ensure correct index of element which has to be erased,
				// as each erase in fInfoColumnWidths will decrease size of vector as well.
				fInfoColumnWidths.erase(fInfoColumnWidths.begin() + i - numRemovedCol); // remove the entry for the column width for the column we couldn't restore.
				numRemovedCol++;
			}
		}
		linksUIPanelPrefs->SetShowingInfoColumns(providers);
		linksUIPanelPrefs->SetColumnWidths(fInfoColumnWidths); 
			
		providers.clear();
		for(unsigned int i = 0; i < fMoreInfoClasses.size(); ++i)
		{
			InterfacePtr<const IK2ServiceProvider> infoService(serviceR->QueryServiceProviderByClassID(kLinkInfoService, fMoreInfoClasses[i]));
			InterfacePtr<ILinkInfoProvider> infoProvider(infoService,UseDefaultIID());
			if(infoProvider)
				providers.push_back(infoProvider);
		}
		linksUIPanelPrefs->SetMoreInfoProviders(providers);
		
	}
}

