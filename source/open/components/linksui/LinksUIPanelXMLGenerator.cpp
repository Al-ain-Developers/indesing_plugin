//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelXMLGenerator.cpp $
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

#include "BasePanelXMLGenerator.h"
#include "ILinkInfoProvider.h"
#include "IXMLOutStream.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ILinksUIPanelPrefs.h"
#include "ISplitterPanelControlData.h"

// ----- Implementation Includes -----

#include "LinksUIID.h"
#include "PreferenceUtils.h"
#include "LinksUIPanelWorkspaceDefs.h"

const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelOptionsXMLTag = "LinksUIPanelOptions";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnXMLTag = "LinkInfoColumn";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoXMLTag = "MoreLinkInfo";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelRowHeightXMLAttributeName = "rowHeight";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelInfoClassXMLAttributeName = "infoClass";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnWidthXMLAttributeName = "columnWidth";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelSecondarySorterClassXMLAttributeName = "secondarySorter";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelSorterClassXMLAttributeName = "sorter";
const char* LinksUIPanelWorkspaceDefs::kLinksUISortAscendingXMLAttributeName = "sortAscending";
const char* LinksUIPanelWorkspaceDefs::kLinksUIShowThumbnailXMLAttributeName = "showThumbnail";
const char* LinksUIPanelWorkspaceDefs::kLinksUIShowInfoThumbnailXMLAttributeName = "showInfoThumbnail";
const char* LinksUIPanelWorkspaceDefs::kLinksUICollapseMultipleXMLAttributeName = "collapseMultiple";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelSplitterPositionXMLAttributeName = "splitterPos";
const char* LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoPaneHiddenXMLAttributeName = "infoPaneHidden";

//========================================================================================
// Class LinksUIPanelXMLGenerator
//========================================================================================

class LinksUIPanelXMLGenerator : public BasePanelXMLGenerator
{
	typedef BasePanelXMLGenerator inherited;
	
public:
	LinksUIPanelXMLGenerator(IPMUnknown *boss);
	virtual ~LinksUIPanelXMLGenerator();

	virtual void GenerateContent(IXMLOutStream *s, int32 beforeChildIndex = 0);
};


//========================================================================================
// METHODS LinksUIPanelXMLGenerator
//========================================================================================
CREATE_PMINTERFACE(LinksUIPanelXMLGenerator, kLinksUIPanelXMLGeneratorImpl)

LinksUIPanelXMLGenerator::LinksUIPanelXMLGenerator(IPMUnknown *boss) :
	inherited(boss)
{
}

LinksUIPanelXMLGenerator::~LinksUIPanelXMLGenerator()
{
}

//----------------------------------------------------------------------------------------
// GenerateContent
//----------------------------------------------------------------------------------------
void LinksUIPanelXMLGenerator::GenerateContent(IXMLOutStream *s, int32 beforeChildIndex)
{
	inherited::GenerateContent(s, beforeChildIndex);

	IXMLOutStream::AttributeList attrs;

	InterfacePtr<const ILinksUIPanelPrefs> linkPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	
	// row height
	PushInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelRowHeightXMLAttributeName, linkPanelPrefs->GetCurrentRowHeight());
	
	
	const ILinkInfoProvider *secondarySortProvider = linkPanelPrefs->GetSecondarySortInfoProvider();
	if(secondarySortProvider)
		PushInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSecondarySorterClassXMLAttributeName, ::GetClass(secondarySortProvider).Get());
	const ILinkInfoProvider *sortProvider = linkPanelPrefs->GetSortInfoProvider();
	if(sortProvider)
		PushInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSorterClassXMLAttributeName, ::GetClass(sortProvider).Get());
	
	// Splitter position
	InterfacePtr<const IPanelControlData> myWidgets(this, UseDefaultIID());
	const IControlView* splitter = myWidgets->FindWidget(kLinkUISplitterPanelWidgetID);
	InterfacePtr<const ISplitterPanelControlData> splitterControlData(splitter, UseDefaultIID());
	if (splitterControlData)
	{
		PushInt( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelSplitterPositionXMLAttributeName, splitterControlData->GetSplitterEdge());
		PushBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoPaneHiddenXMLAttributeName, splitterControlData->IsSinglePanelVisible());
	}

	PushBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUISortAscendingXMLAttributeName, linkPanelPrefs->GetSortLinksAscending());
	PushBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIShowThumbnailXMLAttributeName, linkPanelPrefs->GetShowLinkThumbnail());
	PushBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUICollapseMultipleXMLAttributeName, linkPanelPrefs->GetCollapseMultipleLinksToSameResource());
	PushBool( attrs, LinksUIPanelWorkspaceDefs::kLinksUIShowInfoThumbnailXMLAttributeName, linkPanelPrefs->GetShowLinkInfoThumbnail());
	
	PMString LinksUIPanelOptionsTag( LinksUIPanelWorkspaceDefs::kLinksUIPanelOptionsXMLTag );
	
	s->PushWithAttributes( LinksUIPanelOptionsTag.GrabWString(), attrs, kTrue );				
	{
		PMString columnInfoTagStr( LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnXMLTag );
		PMString moreInfoTagStr( LinksUIPanelWorkspaceDefs::kLinksUIPanelMoreInfoXMLTag );

		// column count, classIDs, widths
		int32 numShowingColumns = linkPanelPrefs->GetNumShowingInfoColumns();
		K2Vector<int32> columnWidths;
		linkPanelPrefs->GetColumnWidths(columnWidths);
		ASSERT_MSG((int32)columnWidths.size() == numShowingColumns,"Num widths out of sync with num columns");
		
		for(int i = 0; i < numShowingColumns; ++i)
		{
			IXMLOutStream::AttributeList columnAttrs;
			InterfacePtr<const ILinkInfoProvider> nthColumnProvider(linkPanelPrefs->QueryNthShowingInfoColumn(i));
			ClassID providerClass = ::GetClass(nthColumnProvider);
			PushInt( columnAttrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelInfoClassXMLAttributeName, providerClass.Get());
			PushInt( columnAttrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelColumnWidthXMLAttributeName, columnWidths[i]);
			
			s->PushWithAttributes( columnInfoTagStr.GrabWString(), columnAttrs, kFalse );				
			s->Pop( kTrue );		

		}

		int32 numMoreInfoProviders = linkPanelPrefs->GetNumMoreInfoProviders();
		for(int i = 0; i < numMoreInfoProviders; ++i)
		{
			IXMLOutStream::AttributeList infoAttrs;
			InterfacePtr<const ILinkInfoProvider> nthProvider(linkPanelPrefs->QueryNthMoreInfoProvider(i));
			ClassID providerClass = ::GetClass(nthProvider);
			PushInt( infoAttrs, LinksUIPanelWorkspaceDefs::kLinksUIPanelInfoClassXMLAttributeName, providerClass.Get());
			s->PushWithAttributes( moreInfoTagStr.GrabWString(), infoAttrs, kFalse );				
			s->Pop( kTrue );		
		}


	}	

	s->Pop( kTrue );		
}


