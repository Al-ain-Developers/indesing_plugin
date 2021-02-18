//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIStatusTextObserver.cpp $
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
#include "ILinkManager.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"
#include "ILinksUIPanelPrefs.h"
#include "ITreeViewController.h"

// ----- Includes -----

#include "CObserver.h"
#include "LinksUIID.h"
#include "LinkQuery.h"
#include "LinkResourceQuery.h"

// ----- Utility files -----

#include "StringUtils.h"
#include "ILinksUIUtils.h"
#include "PreferenceUtils.h"
//#include "K2Vector.tpp"

class LinksUIStatusTextObserver : public CObserver
{
	public:
		LinksUIStatusTextObserver(IPMUnknown *boss);
		virtual ~LinksUIStatusTextObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();

	private:
		void UpdateStatusWidget() const;
};


CREATE_PMINTERFACE(LinksUIStatusTextObserver, kLinksUIStatusTextObserverImpl)

LinksUIStatusTextObserver::LinksUIStatusTextObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

LinksUIStatusTextObserver::~LinksUIStatusTextObserver()
{
}

void LinksUIStatusTextObserver::AutoAttach()
{
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
	
	UpdateStatusWidget();
	
}

void LinksUIStatusTextObserver::AutoDetach()
{
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
}

void LinksUIStatusTextObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(theSubject,changedBy)
	if(protocol == IID_ITREEVIEWCONTROLLER && (theChange == kListSelectionChangedMessage || theChange == kLinksUITreeSelectionAlteredMsgBoss))
	{
//		TRACEFLOW("Links:LinksUI","LinksUIStatusTextObserver::Update got kListSelectionChangedMessage/kLinksUITreeSelectionAlteredMsgBoss\n");
		// if tree selection changes, have to rebuild status string
		UpdateStatusWidget();
	}


}

				// update the status widget
void LinksUIStatusTextObserver::UpdateStatusWidget() const
{
	PMString newStatusStr;

	InterfacePtr<const ITreeViewController> treeController((ITreeViewController*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ITREEVIEWCONTROLLER));
	NodeIDList selectedNodes;
	treeController->GetSelectedItems(selectedNodes);

	if(selectedNodes.size() > 0)
	{
		if(selectedNodes.size() == 1)
		{
			newStatusStr.SetCString("#OneSelectedLinkStr"); // some languages need different text for singular vs. plural...so we do a different key string for the singular case.
		}
		else
		{
			newStatusStr.SetCString("#NumSelectedLinksParamStr");
			newStatusStr.Translate();
			
			PMString numLinksStr;
			numLinksStr.AppendNumber(selectedNodes.size());
			numLinksStr.SetTranslatable(kFalse);
			StringUtils::ReplaceStringParameters(&newStatusStr,numLinksStr);
		}
	}
	else
	{
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		IDataBase *docDB  = linksUIPrefs->GetCurrentDocDB();
		if(docDB)
		{
			UIDList resultUIDs(docDB);
			InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
			
			LinkQuery query1; 
			query1.SetShowInUI(kTrue);
			uint32 numLinks = linkMgr->QueryLinks(query1, kIDLinkClientID, resultUIDs);
			
			PMString numLinksStr;
			numLinksStr.AppendNumber(numLinks);
			numLinksStr.SetTranslatable(kFalse);

			newStatusStr.SetCString("#ShortLinkStatusParamStr");
			newStatusStr.Translate();
			StringUtils::ReplaceStringParameters(&newStatusStr,numLinksStr);
		}
	}
		
		
	InterfacePtr<ITextControlData> statusTextData(this,UseDefaultIID());
	statusTextData->SetString(newStatusStr);
}




