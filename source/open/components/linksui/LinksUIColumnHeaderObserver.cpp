//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIColumnHeaderObserver.cpp $
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
#include "ISubject.h"
#include "ILinksUIPanelPrefs.h"
#include "IColumnHeaderPanelData.h"
#include "ILinkInfoProvider.h"
// ----- Includes -----

#include "CObserver.h"
#include "LinksUIID.h"
#include "PreferenceUtils.h"
#include "ILinksUIUtils.h"
#include "Utils.h"


//========================================================================================
// CLASS LinksUIColumnHeaderObserver
//========================================================================================
class LinksUIColumnHeaderObserver : public CObserver
{
	public:
		LinksUIColumnHeaderObserver(IPMUnknown *boss);
		virtual ~LinksUIColumnHeaderObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
};


CREATE_PMINTERFACE(LinksUIColumnHeaderObserver, kLinksUIColumnHeaderObserverImpl)

//----------------------------------------------------------------------------------------
// LinksUIColumnHeaderObserver constructor 
//----------------------------------------------------------------------------------------

LinksUIColumnHeaderObserver::LinksUIColumnHeaderObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

//----------------------------------------------------------------------------------------
// LinksUIColumnHeaderObserver::~LinksUIColumnHeaderObserver: 
//----------------------------------------------------------------------------------------

LinksUIColumnHeaderObserver::~LinksUIColumnHeaderObserver()
{
}

//----------------------------------------------------------------------------------------
// LinksUIColumnHeaderObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void LinksUIColumnHeaderObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
	{
		subject->AttachObserver(this, IID_ICOLUMNHEADERPANELDATA);
		subject->AttachObserver(this, IID_ICOLUMNHEADERMOUSEUPNOTIFY);
	}
}

//----------------------------------------------------------------------------------------
// LinksUIColumnHeaderObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void LinksUIColumnHeaderObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
	{
		subject->DetachObserver(this, IID_ICOLUMNHEADERPANELDATA);
		subject->DetachObserver(this, IID_ICOLUMNHEADERMOUSEUPNOTIFY);
	}
}

void LinksUIColumnHeaderObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(theSubject)
	if(protocol == IID_ICOLUMNHEADERPANELDATA)
	{
		InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		if(theChange == kColumnHeaderReorderChangeMsgBoss)
		{
			IColumnHeaderPanelData::ColumnHeaderChangeInfo *changeInfo = (IColumnHeaderPanelData::ColumnHeaderChangeInfo*)changedBy;
			TRACEFLOW("Links:LinksUI","LinksUIColumnHeaderObserver got kColumnHeaderReorderChangeMsgBoss, with oldColumnIndex %d, new index %d\n",changeInfo->fOldColumnIndex, changeInfo->fNewColumnIndex);
			if(changeInfo->fOldColumnIndex != changeInfo->fNewColumnIndex)
			{
				InterfacePtr<ILinkInfoProvider> movingColumn(linksUIPrefs->QueryNthShowingInfoColumn(changeInfo->fOldColumnIndex));

				int32 numShowing = linksUIPrefs->GetNumShowingInfoColumns();
				
				K2Vector<ILinkInfoProvider*> newShowingProviders;
				for(int index = 0; index < numShowing; ++index)
				{
					InterfacePtr<ILinkInfoProvider> infoProvider(linksUIPrefs->QueryNthShowingInfoColumn(index));
					if(infoProvider != movingColumn)
						newShowingProviders.push_back(infoProvider);
				}
				newShowingProviders.insert(newShowingProviders.begin() + changeInfo->fNewColumnIndex,movingColumn);
				
				linksUIPrefs->SetShowingInfoColumns(newShowingProviders);
			}

		}

		InterfacePtr<const IColumnHeaderPanelData> columnHeaderData(this,UseDefaultIID());
		K2Vector<int32> columnWidths;
		columnHeaderData->GetColumnWidths(columnWidths);

		linksUIPrefs->SetColumnWidths(columnWidths);
		
	}
	else	if(protocol == IID_ICOLUMNHEADERMOUSEUPNOTIFY)
	{
		int32 whichColumnIndex = *((int32*)changedBy);
		if(whichColumnIndex >= 0)
		{
			InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			InterfacePtr<const ILinkInfoProvider> columnToSort(linksUIPrefs->QueryNthShowingInfoColumn(whichColumnIndex));
			Utils<ILinksUIUtils>()->SetPanelSortProvider(columnToSort);
		}
	}
	
}
