//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/EditOriginalResumeObserver.cpp $
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

#include "IActiveContext.h"
#include "IApplication.h"
#include "ICoreFilename.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IEventConverter.h"
#include "IEventDispatcher.h"
#include "IEventHandler.h"
#include "IFilesChanging.h"
#include "IINXInfo.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "ILinkManager.h"
#include "ILinkObject.h"
#include "ILinkResource.h"
#include "ILinkState.h"
#include "ILinkUtils.h"
#include "ISession.h"
#include "ISharedContentFacade.h"
#include "ISubject.h"
#include "ITracker.h"
#include "IUpdateLink.h"

// ----- Includes -----

#include "CObserver.h"
#include "InCopyImportExportDefs.h"
#include "InDesignSessionDataManager.h" 
#include "UIDList.h"
#include "Utils.h"

// ----- Utility files -----

#include "StringUtils.h"

// ----- ID.h files -----

#include "EPSID.h"
#include "LinksUIID.h"
#include "WorkspaceID.h"

class EditOriginalResumeObserver : public CObserver
{
	typedef CObserver inherited;
	
public:
			 EditOriginalResumeObserver(IPMUnknown *boss) : inherited( boss, IID_IEDITORIGINALRESUMEOBSERVER ) { ; }
	virtual ~EditOriginalResumeObserver() { ; }
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

private:
	void AbortCurrentTracker();
	void UpdateEditedFiles(bool bUpdateINDDOnly);
};

#pragma mark EditOriginalResumeObserver implementation

CREATE_PMINTERFACE(EditOriginalResumeObserver, kEditOriginalResumeObserverImpl)

void EditOriginalResumeObserver::AutoAttach()
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ISubject> subject(theApp, IID_ISUBJECT);
	
	if (!subject->IsAttached(this, IID_IAPPLICATION, IID_IEDITORIGINALRESUMEOBSERVER))
		subject->AttachObserver(this, IID_IAPPLICATION, IID_IEDITORIGINALRESUMEOBSERVER);

    IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
    InterfacePtr<ISubject> contextSubject(activeContext, IID_ISUBJECT);
	
    if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IEDITORIGINALRESUMEOBSERVER))
        contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IEDITORIGINALRESUMEOBSERVER);
}

void EditOriginalResumeObserver::AutoDetach() 
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ISubject> subject(theApp, IID_ISUBJECT);
	subject->DetachObserver(this, IID_IAPPLICATION, IID_IEDITORIGINALRESUMEOBSERVER);

    IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
    InterfacePtr<ISubject> contextSubject(activeContext, IID_ISUBJECT);
    if (contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IEDITORIGINALRESUMEOBSERVER))
        contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IEDITORIGINALRESUMEOBSERVER);
}

void EditOriginalResumeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	#pragma unused(theSubject)
	if ( protocol == IID_IAPPLICATION && (theChange != kApplicationResumeMsg && theChange != kPendingDocumentsClosedMsg))
		return;

	// update if switching documents
	if ( protocol == IID_IACTIVECONTEXT )
	{
		const PMIID& what = *((const PMIID*)changedBy);
		if ( what != IID_IWORKSPACE )
			return;
	}

	if (ValueTypeConversion<bool16>().get(InDesignSessionDataStoreKeyType::Constants::kFilesClosing, kFalse) == kFalse)
		UpdateEditedFiles(protocol == IID_IACTIVECONTEXT);
}


// Look to see whether any of the files being edited have been saved and closed and then update them.
void EditOriginalResumeObserver::UpdateEditedFiles(bool bUpdateINDDOnly)
{
	#pragma unused(bUpdateINDDOnly)
	InterfacePtr<IFilesChanging> filesChanging(GetExecutionContextSession(), UseDefaultIID());
	if (!filesChanging)
		return;

	// Don't update any links when a dialog is up (especially the link info dialog).
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if ( !app->IsApplicationActive() )
			return;

		InterfacePtr<IDialogMgr> dm(app, IID_IDIALOGMGR);
		if (dm->IsAnyDialogInFront())
			return;
	}

	int32 length = filesChanging->Length();
	if ( length == 0 )
		return;

	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
    IDocument* doc = activeContext->GetContextDocument();

	if ( !doc )
		return;

	IDataBase *currentDB = ::GetDataBase(doc);

	// Abort any trackers at this point so we don't update a link that a tracker is operating on.
	AbortCurrentTracker();

	Utils<Facade::ISharedContentFacade> iSharedContentFacade;
    
    UIDList completeList(currentDB);

	for (int32 i = length; i--;)
	{
		UIDRef resourceRef = filesChanging->GetRef(i);
		IDataBase *db = resourceRef.GetDataBase();

		if (db != currentDB)
		{
			continue;
		}
		else if ( !db->IsValidUID(resourceRef.GetUID()))
		{
			filesChanging->Remove(i);
		}
		else
		{			
			// anirudh, fix for bug# 1416884.
			// We should instantiate a link only for a valid ref, hence moved it down here.
			InterfacePtr<ILinkResource> linkResource(resourceRef,UseDefaultIID());
			
			// INDD docs are closed with a scheduled command. Hence, the context switch due to the user closing the
			// document occurs before the file has actually been closed.
			bool docInDoc = linkResource && linkResource->GetFormatType() == "InDesign Format Name";

			if ( bUpdateINDDOnly && !docInDoc )
				continue;


			if (!linkResource)
				filesChanging->Remove(i);
			else
			{
				if(iSharedContentFacade && iSharedContentFacade->IsSharedContentLinkResource(linkResource))
					continue;

				bool bInTheMiddleOfInCopyStuff = (linkResource->GetFormatType() == InCopy::kInCopyInterchangeFormatName && Utils<IINXInfo>()->IsINXContextActive());
				if(bInTheMiddleOfInCopyStuff)
					continue;
			
				InterfacePtr<const ILinkManager> linkMgr(db,db->GetRootUID(),UseDefaultIID());
				Utils<Facade::ILinkFacade>()->UpdateResourceStates(UIDList(db, ::GetUID(linkResource)), ILinkManager::kSynchronous); // do I really need to call this?
				UIDList listOfLinks;
				linkMgr->QueryLinksByResourceUID(::GetUID(linkResource), false, listOfLinks);
				for(int j = listOfLinks.size() - 1; j >=0; --j)
				{
					if(!Utils<Facade::ILinkFacade>()->CanUpdateLink(listOfLinks.GetRef(j),false))
						listOfLinks.Remove(j);
				}

				if (listOfLinks.size() == 0)
				{
					// None of the links can be updated. Remove this resource from our list
				//	filesChanging->Remove(i); // actually, lets not. If the user has left the file open for write in the authoring app, 'CanUpdateLink' will return false. Let's just leave it in the list for next time.
					continue; // do not update
				}
                completeList.Append(listOfLinks);

				// We are currently processing the application activation change message. No dialog should open while processing this event.
				// If any dialog launches, the user will have time to switch application again,
				// and the new application activation change message will be received by the modal loop of dialog, before the current message finishes processing,
				// which is not acceptable. Hence, updating the link should be scheduled.
                
                //Arvin fix for bug# 4216607
                //In order to avoid Missing Fonts Pop-up getting stacked one upon the other, we should call UpdateLinks only when we have complete list of links, hence commenting this call here and calling it after 'for-loop'
				//Utils<Facade::ILinkFacade>()->UpdateLinks(listOfLinks,false,kMinimalUI,true /*scheduled*/);
				filesChanging->Remove(i);
	
			}
		}
	}
    Utils<Facade::ILinkFacade>()->UpdateLinks(completeList,false,kMinimalUI,true /*scheduled*/);
}

void EditOriginalResumeObserver::AbortCurrentTracker()
{
	// NOTE (see bug #1114983):
	// This check is a special situation that can arise on Windows.
	// When ID is not frontmost app, user can click and hold mouse down to
	// both activate AND start up a tracker. Later, kApplicationResumeMsg message
	// comes through, at which point this observer may update a link that is currently
	// being tracked (and therefore change the page item and UID out from under the tracker).
	// This check abort any tracking that was in progress if we need to update links.
	IEventConverter *iEventConverter = GetExecutionContextSession()->GetEventConverter();
	bool16 isTrackingMouse = iEventConverter->IsTrackingMouse();
	if (isTrackingMouse)
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IEventDispatcher> dispatcher(theApp, UseDefaultIID());

		int32 depth( dispatcher->Depth() );
		
		while (depth)
		{
			IEventHandler *nextEH = dispatcher->Peek(--depth);
			InterfacePtr<ITracker> tracker(nextEH, IID_ITRACKER);
			
			if (tracker)
			{
				//  99% of trackers don't care about the event passed into AbortTracker - those that do need to check.
				tracker->AbortTracking(nil);
				tracker->Release();				// This is to bracket the creation of the tracker
			}
		}
	}
}

