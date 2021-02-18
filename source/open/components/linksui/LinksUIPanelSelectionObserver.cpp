//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelSelectionObserver.cpp $
//  
//  Owner: Steve Flenniken
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

#include "LinksUIID.h"
#include "SelectionObserver.h"
#include "ILinkItemSuite.h"
#include "ISelectionUtils.h"
#include "ILinksUIUtils.h"
#include "widgetid.h"
#include "IActiveContext.h"
#include "ISubject.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "IPlaceGun.h"
#include "ILinkObject.h"
#include "ILinkManager.h"
#include "LinkQuery.h"
#include "ILinkUtils.h"
#include "ILinksUIPanelPrefs.h"
#include "PreferenceUtils.h"

class LinksUIPanelSelectionObserver : public ActiveSelectionObserver
{
public:
	LinksUIPanelSelectionObserver(IPMUnknown *boss);
	
	virtual void AutoAttach(); 
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

	virtual void HandleSelectionChanged( const ISelectionMessage* iSelectionMessage );
	
private:
	void ActiveDocChange();
	void AttachToNewFrontDoc(const IDocument* newFrontDoc);
	void DetachFromDoc();
	const IDocument* fCurrentFrontDoc;
};

CREATE_PMINTERFACE(LinksUIPanelSelectionObserver, kLinksUIPanelSelectionObserverImpl)

LinksUIPanelSelectionObserver::LinksUIPanelSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_ISELECTIONOBSERVER),fCurrentFrontDoc(nil)
{
}

void LinksUIPanelSelectionObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();
	// also attach to active context, so we can catch active document changes. Attach to each active document so we can watch for place gun messages.
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();

	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_ISELECTIONOBSERVER))
		{
			contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_ISELECTIONOBSERVER);
		}
	}

	ActiveDocChange();
	
}

void LinksUIPanelSelectionObserver::AutoDetach()
{
	ActiveSelectionObserver::AutoDetach();
	
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject)
		{
			if (contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_ISELECTIONOBSERVER))
			{
				contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_ISELECTIONOBSERVER);
			}
		}
	}

	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	UIDList emptyList(linksUIPrefs->GetCurrentDocDB());
	Utils<ILinksUIUtils>()->SelectLinksInPanel(emptyList);

	DetachFromDoc();

}

void LinksUIPanelSelectionObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	ActiveSelectionObserver::LazyUpdate(theSubject,protocol,data);
	if(protocol == IID_IPLACEGUN)
	{
		// update panel selection to match item loaded in place gun.
		InterfacePtr<const IPlaceGun> placeGun(fCurrentFrontDoc,UseDefaultIID());
		if(placeGun && placeGun->IsLoaded())
		{
			IDataBase *docDB = ::GetDataBase(fCurrentFrontDoc);
			const UID firstItemInGun = placeGun->GetFirstPlaceGunItemUID();
			InterfacePtr<const ILinkObject> linkObj(docDB,firstItemInGun,UseDefaultIID());
			if(linkObj)
			{

				UIDList resultUIDs(docDB);
				UID linkUID = Utils<ILinkUtils>()->FindLink(UIDRef(docDB, firstItemInGun));
				if(linkUID != kInvalidUID)
					resultUIDs.push_back(linkUID);

				if(resultUIDs.size() > 0)
				{
					Utils<ILinksUIUtils>()->SelectLinksInPanel(resultUIDs);
				
				}
			
			}
			
		}
	}

}

void LinksUIPanelSelectionObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	ActiveSelectionObserver::Update(theChange,theSubject,protocol,changedBy);
	
	if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
	{
		const PMIID& what = *((const PMIID*)changedBy);

		if( what == IID_IDOCUMENT )
		{
			ActiveDocChange();
		}
	}
}
// Select the items in the links panel to reflect the selection on the
// page.

void LinksUIPanelSelectionObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
#pragma unused(iSelectionMessage)
	// Create UID list for all selected items.
	InterfacePtr<ILinkItemSuite> iLinkItemSuite( static_cast<ILinkItemSuite*>( this->QueryAbstractSelection(IID_ILINKITEMSUITE) ) );
	if(iLinkItemSuite)
	{
		 K2::scoped_ptr<UIDList> datalinks(iLinkItemSuite->CreateItemsDataLinkUIDList());
		if (datalinks)
		{
//			TRACEFLOW("Links:LinksUI","LinksUIPanelSelectionObserver::HandleSelectionChanged selecting %d links in panel, because they're selected in layout\n",datalinks->Length());
			Utils<ILinksUIUtils>()->SelectLinksInPanel(*datalinks);
			return;
		}
	}
	
	// Nothing is selected, unselect the items in the links palette.
	//TRACEFLOW("Links:LinksUI","LinksUIPanelSelectionObserver::HandleSelectionChanged deselecting everything in panel - no links selected in layout\n");
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	UIDList emptyList(linksUIPrefs->GetCurrentDocDB());
	Utils<ILinksUIUtils>()->SelectLinksInPanel(emptyList);

}

void LinksUIPanelSelectionObserver::AttachToNewFrontDoc(const IDocument* newFrontDoc)
{

	if( newFrontDoc )
	{		
		fCurrentFrontDoc = newFrontDoc;
		
		InterfacePtr<ISubject>	docSubject( newFrontDoc, UseDefaultIID() );

		if( docSubject && !docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IPLACEGUN, IID_ISELECTIONOBSERVER))
			docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IPLACEGUN, IID_ISELECTIONOBSERVER);
			
	}
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::DetachFromDoc 
//----------------------------------------------------------------------------------------
void LinksUIPanelSelectionObserver::DetachFromDoc()
{
	if( fCurrentFrontDoc )
	{		
		InterfacePtr<ISubject> docSubject(fCurrentFrontDoc, UseDefaultIID() );

		if( docSubject )
		{
			if( docSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IPLACEGUN, IID_ISELECTIONOBSERVER))
				docSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IPLACEGUN, IID_ISELECTIONOBSERVER);
		}
			
	}
	fCurrentFrontDoc = nil;;

}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::ActiveDocChange: 
//----------------------------------------------------------------------------------------
void LinksUIPanelSelectionObserver::ActiveDocChange()
{
	const IDocument* newFrontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();


	if (newFrontDoc != fCurrentFrontDoc)
	{		
		this->DetachFromDoc();
		
		this->AttachToNewFrontDoc(newFrontDoc);
					
	}

}
