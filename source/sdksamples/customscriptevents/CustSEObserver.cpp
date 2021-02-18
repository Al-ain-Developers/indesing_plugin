//========================================================================================
//  
//  $File $
//  
//  Owner: Heath Lynn
//  
//  $Author $
//  
//  $DateTime $
//  
//  $Revision $
//  
//  $Change $
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
#include "IDocument.h"
#include "IIDFileData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPanelControlData.h"
#include "IPersistUIDData.h"
#include "IPlugInList.h"
#include "IScriptEvent.h"
#include "IScriptEventTarget.h"
#include "IScriptUtils.h"
#include "ISelectionManager.h"
#include "IStrokeAttributeSuite.h"
#include "ISubject.h"
#include "IStyleGroupInfo.h"
#include "IStyleInfo.h"
#include "IUnitOfMeasure.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "ErrorUtils.h"
#include "ListLazyNotificationData.h"
#include "SelectionObserver.h"
#include "UIDList.h"

// ----- Utility files -----

#include "FileUtils.h"
#include "PMLocaleId.h"
#include "Utils.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "CustSEID.h"
#include "DocFrameworkID.h"
#include "ScriptingID.h"
#include "SpreadID.h"
#include "TextID.h"


/** CustSEObserver demonstrates how to dipatch custom script events from an observer.
The code observes changes to the active character and paragraph style lists and 
dispatches an "afterParagraphStyleListChanged" or "afterParagraphStyleListChanged"
event when one of the style list change.
*/

class CustSEObserver : public ActiveSelectionObserver
{
public:
	CustSEObserver( IPMUnknown* boss );
	virtual ~CustSEObserver();
	
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	// These methods are called by the startup/shutdown service
	virtual void AutoAttach();
	virtual void AutoDetach();

	// Overriden to get change in active context.  This is also used to 
	// detach and attach to new documents.
	virtual void HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	// This is called when one of the non-selection based changes occurs
	 virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

private:

	//
	// The following functions and data members are used to keep the observer hooked
	// up to the right document and workspace.  This has to do with the misc broadcasts we're
	// observing.
	//

	// This hooks the observer up to a document or the workspace when nil.
	bool16 ObserveDocument(IDocument* document);
	
	// Some changes are broadcast on the kWorkspaceBoss or kDocWorkspaceBoss subject.
	// These calls are used to attach to the active workspace subject.
	void DetachFromWorkspace();
	void AttachToWorkspace(UIDRef workspaceRef);
	
	// Used to attach and detach from the active kDocBoss subject.
	void DetachFromDocument();
	void AttachToDocument(UIDRef docRef);

	void DispatchAppScriptEvent( ScriptElementID eventID );

	UIDRef fCurrentWorkspaceRef;
	UIDRef fCurrentDocRef;

};





CREATE_PMINTERFACE(CustSEObserver, kCustSEObserverImpl)



// -----------------------------------------------------------------------------
CustSEObserver::CustSEObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_ISCRIPTOBSERVER)
{
	fCurrentWorkspaceRef = kInvalidUIDRef;
	fCurrentDocRef = kInvalidUIDRef;
} 


// -----------------------------------------------------------------------------
CustSEObserver::~CustSEObserver()
{
} 


// -----------------------------------------------------------------------------
void CustSEObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	ActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
} 


// -----------------------------------------------------------------------------
void CustSEObserver::AutoAttach()
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	IDocument *document = context ? context->GetContextDocument() : nil;
	ObserveDocument(document);

	ActiveSelectionObserver::AutoAttach();
} 


// -----------------------------------------------------------------------------
void CustSEObserver::AutoDetach()
{
	ActiveSelectionObserver::AutoDetach();
	DetachFromWorkspace();
	DetachFromDocument();
} 

/* HandleSelectionUpdate checks to see if the active document has changed.  If so, it 
calls ObserveDocument to attach to the appropriate document and/or workspace.
*/
void CustSEObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);

	if (protocol == IID_IACTIVECONTEXT)
	{
		InterfacePtr<IActiveContext> context( theSubject, UseDefaultIID());
		IActiveContext::ContextInfo *info = (IActiveContext::ContextInfo*)changedBy;

		if (info->Key() == IID_IDOCUMENT)
		{
			IDocument *document = context ? context->GetContextDocument() : nil;
			ObserveDocument(document);  // document may be nil if this is the app workspace
		}
	}
}

/* Attach the observer to the appropriate document and/or the application workspace.
*/
bool16 CustSEObserver::ObserveDocument(IDocument* document)
{
	UIDRef wsRef(nil,kInvalidUID);
	UIDRef docRef(nil,kInvalidUID);

	if(document)
	{
		docRef = ::GetUIDRef(document);
		wsRef = document->GetDocWorkSpace();
	}
	else
	{
		InterfacePtr<IWorkspace> sessionWS(GetExecutionContextSession()->QueryWorkspace());
		wsRef = ::GetUIDRef(sessionWS);
		docRef = kInvalidUIDRef;
	}

	if (wsRef != fCurrentWorkspaceRef)
	{
		this->DetachFromWorkspace(); // if fCurrentDocument is nil, we'll detach from session workspace
		this->AttachToWorkspace(wsRef);						// if document is nil, we'll attach to session workspace
		this->DetachFromDocument();
		this->AttachToDocument(docRef);
		return kTrue;
	}

	return kFalse;
}

/* Detach style related attachments from the workspace.
*/
void CustSEObserver::DetachFromWorkspace()
{
	if(fCurrentWorkspaceRef != kInvalidUIDRef)
	{
		InterfacePtr<ISubject> wsSubject(fCurrentWorkspaceRef, IID_ISUBJECT);
		if (wsSubject)
		{
			
			wsSubject->DetachObserver(ISubject::kLazyAttachment,this,IID_ISTYLEINFO, IID_ISCRIPTOBSERVER);
			wsSubject->DetachObserver(ISubject::kLazyAttachment,this,IID_ISTYLEGROUPINFO, IID_ISCRIPTOBSERVER);
			wsSubject->DetachObserver(ISubject::kLazyAttachment,this,IID_IPARASTYLEGROUPMANAGER, IID_ISCRIPTOBSERVER);
			wsSubject->DetachObserver(ISubject::kLazyAttachment,this,IID_ICHARSTYLEGROUPMANAGER, IID_ISCRIPTOBSERVER);
		}
		fCurrentWorkspaceRef = UIDRef::gNull;
	}
}

/* Attach style related observers to the workspace.
*/
void CustSEObserver::AttachToWorkspace(UIDRef workspaceRef)
{
	// Attach to the Stylelist for Create and Delete Style messages
	InterfacePtr<ISubject> wsSubject(workspaceRef, IID_ISUBJECT);
	if (wsSubject)
	{
		wsSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISTYLEINFO, IID_ISCRIPTOBSERVER);
		wsSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISTYLEGROUPINFO, IID_ISCRIPTOBSERVER);
		wsSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IPARASTYLEGROUPMANAGER, IID_ISCRIPTOBSERVER);
		wsSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ICHARSTYLEGROUPMANAGER, IID_ISCRIPTOBSERVER);
		
		
		fCurrentWorkspaceRef = workspaceRef;
	}
}

/* Detach observers from the current document.
*/
void CustSEObserver::DetachFromDocument()
{
	if(fCurrentDocRef != kInvalidUIDRef)
	{
		InterfacePtr<ISubject> docSubject(fCurrentDocRef, IID_ISUBJECT);
		if (docSubject)
		{
			
			docSubject->DetachObserver(ISubject::kLazyAttachment,this,IID_ISPREADLIST, IID_ISCRIPTOBSERVER);
		}
		fCurrentDocRef = UIDRef::gNull;
	}
}

/*  Attach observers to the new document.
*/
void CustSEObserver::AttachToDocument(UIDRef docRef)
{
	// Attach to the Stylelist for Create and Delete Style messages
	InterfacePtr<ISubject> docSubject(docRef, IID_ISUBJECT);
	if (docSubject)
	{
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_ISCRIPTOBSERVER);
		
		fCurrentDocRef = docRef;
	}
}

/* Determine what's changed and dispatch script events if applicable.
*/
void CustSEObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	if( protocol.Get() == IID_ISPREADLIST )
	{
		DispatchAppScriptEvent(kSpreadListChangedScriptElement);
		return;
	}

	// Use the ListLazyNotificationData to determine what type of style we're dealing with.
	bool isParaStyle = false;
	bool isCharStyle = false;
	bool isStyleGroup = false;

	K2Vector<UID> addedItems;
	K2Vector<UID> changedItems;
	K2Vector<UID> deletedItems;

	IDataBase* db = ::GetDataBase(theSubject);
	if( data != nil)
	{
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		listData->BreakoutChanges(&addedItems, &deletedItems, &changedItems);

		UID anyItem = kInvalidUID;

		if( addedItems.size() > 0)
			anyItem = addedItems.front();
		else if(changedItems.size() > 0)
			anyItem = changedItems.front();

		if( anyItem != kInvalidUID )
		{
			// We limit this event to Para or Char styles
			InterfacePtr<IStyleInfo> styleInfo(db, anyItem, UseDefaultIID());
			if( styleInfo)
			{
				isParaStyle = styleInfo->GetStyleType() == IStyleInfo::kParagraphStyle;
				isCharStyle = styleInfo->GetStyleType() == IStyleInfo::kCharacterStyle;
			}
			
			InterfacePtr<IStyleGroupInfo> styleGroupInfo(db, anyItem, UseDefaultIID());
			if( styleGroupInfo)
			{
				isStyleGroup = true;
			}
		}

		// If styles were deleted it's not possible to instantiate
		// the object and check which type of style we are dealing with.
		// In this case we can use the following protocols to determine
		// the style check.
		//
		if(protocol.Get() == IID_IPARASTYLEGROUPMANAGER)
			isParaStyle = true;

		if(protocol.Get() == IID_ICHARSTYLEGROUPMANAGER)
			isCharStyle = true;
	}
	else
	{
		// There is no data so we need to dispatch change event to both panels.
		// Only one of them  has changed, but at this point there is no way to
		// determine which changed.
		//
		// An example of this is when a style is moved in the list.
		//

		isParaStyle = isCharStyle = true;
	}

	switch(protocol.Get())
	{

	case IID_IPARASTYLEGROUPMANAGER:
	case IID_ICHARSTYLEGROUPMANAGER:
		{
			// Break if it's deletion of styles.
			// Allow style group changes to pass through.
			if(!isStyleGroup && deletedItems.size() == 0)
			{
				break;
			}
		}
	case IID_ISTYLEGROUPINFO:
	case IID_ISTYLEINFO:
		{
			if(isParaStyle)
			{
				DispatchAppScriptEvent(kParaStyleListChangedScriptElement);
			}
			
			if(isCharStyle )
			{
				DispatchAppScriptEvent(kCharStyleListChangedScriptElement);
			}
		}
		break;
	}
}

/* Dispatches the event using the IScriptEventTarget API.
*/
void CustSEObserver::DispatchAppScriptEvent( ScriptElementID eventID )
{
	InterfacePtr<IScript> appScript( Utils<IScriptUtils>()->QueryApplicationScript() ) ;
	InterfacePtr<IScriptEventTarget> target( appScript, UseDefaultIID() ) ;
	if(target)
		target->DispatchScriptEvent( eventID ) ;
}

