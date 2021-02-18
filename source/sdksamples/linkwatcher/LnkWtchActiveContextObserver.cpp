//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchActiveContextObserver.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Implementation includes
#include "widgetid.h"

// Interface includes
#include "ISubject.h"
#include "IControlView.h"
#include "ITreeViewMgr.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "IActiveContext.h"
#include "IWorkspace.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"

// Implem includes
#include "CAlert.h"
#include "CObserver.h"
#include "Utils.h"
#include "LnkWtchID.h"
#include "DebugClassUtils.h"

#include "ILnkWtchCache.h"


/** Updates a list box user interface to display the contents
	of this plug-in's cache, ILnkWtchCache. The cache lists the
	links added to a document since it was opened. There is one
	cache per document. The user interface onlys display the 
	content of one cache, the cache associated with the document
	the user is actively working with.
	
	Observes the active context and displays the cache associated with the
	active document. Observes ILnkWtchCache updates the list box when the 
	cache is changed.

	@see ILnkWtchCache
	@ingroup linkwatcher
*/
class LnkWtchActiveContextObserver : public CObserver
{
public:

	/** Constructor.
		@param boss object on which this interface is aggregated.
	*/
	LnkWtchActiveContextObserver(IPMUnknown *boss);

	/** Destructor.
	*/	
	~LnkWtchActiveContextObserver();

	/** Attaches to the active context and to this plug-in's cache (ILnkWtchCache) if
		a document is active.
	*/	
	virtual void AutoAttach();

	/** Detaches from the active context and from this plug-in's cache (ILnkWtchCache) if
		it is attached.
	*/	
	virtual void AutoDetach();

	/** Reacts to change in the active context.

		@param theChange this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject this provides a reference to the object which has changed; in this case, the button
		widget boss object that is being observed.
		@param protocol the protocol along which the change occurred.
		@param changedBy this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/	
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

private:

	/**	Called when the active context changes.
		@param theSubject 
		@param changedBy 
	 */
	void HandleActiveContextUpdate(ISubject* theSubject, void* changedBy);

	/**	Called when the observed cache (ILnkWtchCache) changes.
	 */
	void HandleCacheUpdate();

	/**	Attaches to the cache (IID_ILNKWTCHCACHE) and set fCurrentDocument
		to indicate the document being observed.
		@param theDocument 
	 */
	void AttachCurrentDocumentTo(IDocument* theDocument);

	/**	Detach from the cache (IID_ILNKWTCHCACHE) if attached and
		clear fCurrentDocument.
	 */
	void DetachCurrentDocument();

	/**	Handles detaching / attaching as the active document changes. 
		@param context 
	 */
	void ActiveDocChange(IActiveContext* context);

	/**	Displays entries from the cache for document currently being
		observed (ILnkWtchCache interface on fCurrentDocument) in this
		plug-in's list box widget. A complete refresh is done each time
		the cache is changed.
	 */
	void UpdateListBox();

	/**	Dumps debug info on an IObserver::Update call to trace.
		@param theChange 
		@param theSubject 
		@param protocol 
		@param changedBy 
	 */
	void DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	IDocument* fCurrentDocument;

#ifdef SDKAUTOUNDO
	// New code:
public:
	/**	Handles update when ILnkWtchCache changes.
		@param theSubject 
		@param protocol 
		@param data 
	 */
	void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

private:

	/**	Dumps debug info on an IObserver::LazyUpdate call to trace.
		@param theSubject 
		@param protocol 
		@param data 
	 */
	void DumpLazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);
#endif // SDKAUTOUNDO
};

/*
*/
CREATE_PMINTERFACE(LnkWtchActiveContextObserver, kLnkWtchActiveContextObserverImpl)

/*
*/
LnkWtchActiveContextObserver::LnkWtchActiveContextObserver(IPMUnknown* boss)
: CObserver(boss), fCurrentDocument(nil)
{

}

/*
*/
LnkWtchActiveContextObserver::~LnkWtchActiveContextObserver()
{

}

/*
*/
void LnkWtchActiveContextObserver::AutoAttach()
{
	// Observe the active context.
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
#ifdef SDKAUTOUNDO 
		// New code:
		contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IOBSERVER);
#else
		// Old code:
		contextSubject->AttachObserver(this, IID_IACTIVECONTEXT);
#endif
	}

	// Observe the current document in the active context (if any).
	this->ActiveDocChange(context);	
}

/*
*/
void LnkWtchActiveContextObserver::AutoDetach()
{

	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
#ifdef SDKAUTOUNDO 
		// New code:
		contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
#else
		// Old code:
		contextSubject->DetachObserver(this, IID_IACTIVECONTEXT);
#endif
	}

	if(fCurrentDocument)
	{
		this->DetachCurrentDocument();
	}
}

/*
*/
void LnkWtchActiveContextObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	this->DumpUpdate(theChange, theSubject, protocol, changedBy);
	switch (protocol.Get())
	{
	case IID_IACTIVECONTEXT:	
		this->HandleActiveContextUpdate(theSubject, changedBy);
		break;
#ifndef SDKAUTOUNDO
		// Old code:
		// For auto undo the protocol is observed using lazy notification - see LazyUpdate
	case IID_ILNKWTCHCACHE:
		{
			this->HandleCacheUpdate();
		}
		break;
#endif // SDKAUTOUNDO
	default:
		{
			ASSERT_FAIL (FORMAT_ARGS ("LnkWtchActiveContextObserver::Update does not support protocol (%x)", protocol.Get()));
		}
	}
}


/*
*/
void LnkWtchActiveContextObserver::HandleActiveContextUpdate(ISubject* theSubject, void* changedBy)
{
	IActiveContext::ContextInfo* contextInfo = reinterpret_cast<IActiveContext::ContextInfo*>(changedBy);
	if (contextInfo->Key() == IID_IDOCUMENT)
	{
		InterfacePtr<IActiveContext> context( theSubject, UseDefaultIID() );
		this->ActiveDocChange(context);
	}
}

/*
*/
void LnkWtchActiveContextObserver::HandleCacheUpdate()
{
	this->UpdateListBox();
}

/*
*/
void LnkWtchActiveContextObserver::ActiveDocChange(IActiveContext* context)
{
	ASSERT(context);
	IDocument* theDocument = context->GetContextDocument();
	if (theDocument != fCurrentDocument)
	{
		if (fCurrentDocument)
		{
			this->DetachCurrentDocument();
		}

		if (theDocument)
		{
			this->AttachCurrentDocumentTo(theDocument);
		}
	}
	this->UpdateListBox();
}

/*
*/
void LnkWtchActiveContextObserver::AttachCurrentDocumentTo(IDocument* theDocument)
{
	ASSERT(fCurrentDocument == nil);
	if(theDocument)
	{		
		InterfacePtr<ISubject> documentSubject(theDocument, IID_ISUBJECT);
		if (documentSubject)
		{
#ifdef SDKAUTOUNDO
			// New code:
			documentSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILNKWTCHCACHE, IID_IOBSERVER);
#else
			// Old code:
			documentSubject->AttachObserver(this, IID_ILNKWTCHCACHE);
#endif // SDKAUTOUNDO
		}
		fCurrentDocument = theDocument;
	}
}

/*
*/
void LnkWtchActiveContextObserver::DetachCurrentDocument()
{
	ASSERT(fCurrentDocument != nil);
	if (fCurrentDocument)
	{
		InterfacePtr<ISubject> documentSubject(fCurrentDocument, IID_ISUBJECT);
		if (documentSubject)
		{
#ifdef SDKAUTOUNDO
			// New code:
			documentSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILNKWTCHCACHE, IID_IOBSERVER);
#else
			// Old code:
			documentSubject->DetachObserver(this, IID_ILNKWTCHCACHE);
#endif // SDKAUTOUNDO
		}
		fCurrentDocument = nil;
	}
}

/*
*/ 
void LnkWtchActiveContextObserver::UpdateListBox()
{
	do {
		if (!fCurrentDocument)
			break;

		// Get hold of our panel data so we can access our widgets.
		InterfacePtr<IWidgetParent> iWidgetParent(this, UseDefaultIID());
		if (iWidgetParent == nil)
		{
			ASSERT_FAIL("iWidgetParent invalid");
			break;
		}

		InterfacePtr<IPanelControlData> iPanelControlData(iWidgetParent->GetParent(), UseDefaultIID());
		if (iPanelControlData == nil)
		{
			ASSERT_FAIL("panel control data not found");
			break;
		}

		// Update tree view
		IControlView* treeWidget = iPanelControlData->FindWidget(kLnkWtchListBoxWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget) {
			break;
		}

		InterfacePtr<ITreeViewMgr> iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr){
			break;
		}
		
		iTreeViewMgr->ChangeRoot(kTrue);

	}while (false);
}

/*
*/
void LnkWtchActiveContextObserver::DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#ifdef DEBUG
	// Dump some diagnostic trace about the update.
	DebugClassUtilsBuffer theChangeName = "";
	DebugClassUtils::GetIDName(&theChangeName, theChange);
	DebugClassUtilsBuffer theSubjectName = "";
	if (theSubject)
	{
		DebugClassUtils::GetIDName(&theSubjectName, ::GetClass(theSubject));
	}
	DebugClassUtilsBuffer protocolName = "";
	DebugClassUtils::GetIDName(&protocolName, protocol);
	TRACEFLOW("LinkWatcher:ListBoxObserver","Update %s, %s, %s\n",
		theChangeName,
		theSubjectName,
		protocolName);
#endif // DEBUG
}

#ifdef SDKAUTOUNDO
// New code:
/*
*/
void LnkWtchActiveContextObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data) 
{
	this->DumpLazyUpdate(theSubject, protocol, data);
	if (protocol == ILnkWtchCache::kDefaultIID)
	{
		this->HandleCacheUpdate();
	}
	else
	{
		ASSERT_FAIL (FORMAT_ARGS ("LnkWtchActiveContextObserver::LazyUpdate does not support protocol (%x)", protocol.Get()));
	}
}

/*
*/
void LnkWtchActiveContextObserver::DumpLazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data) 
{
#ifdef DEBUG
	// Dump some diagnostic trace about the update.
	DebugClassUtilsBuffer theSubjectName = "";
	if (theSubject)
	{
		DebugClassUtils::GetIDName(&theSubjectName, ::GetClass(theSubject));
	}
	DebugClassUtilsBuffer protocolName = "";
	DebugClassUtils::GetIDName(&protocolName, protocol);
	PMString dataName = "";
	if (data)
	{
		dataName = "LazyNotificationData";
	}
	TRACEFLOW("LinkWatcher:ListBoxObserver","LazyUpdate %s, %s, %s\n",
		theSubjectName,
		protocolName,
		dataName.GetUTF8String().c_str());
#endif // DEBUG
}
#endif // SDKAUTOUNDO
