//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkDocObserver.cpp $
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



// Interface includes:
#include "IDocument.h"
#include "IHierarchy.h"
#include "ISubject.h"
#include "ICusDtLnkFacade.h"
#include "ILayoutUtils.h"
#include "IGraphicFrameData.h"
#include "IHierarchyCmdData.h"
#include "ListLazyNotificationData.h"
#include "LinksID.h"
#include "ILink.h"

// API includes:
#include "CObserver.h"
#include "UIDList.h"
// Project includes:
#include "CusDtLnkID.h"


/** Implementation of IObserver to respond to notification about changes
	to the document (kDocBoss) subject

	@ingroup customdatalink
*/
class CusDtLnkDocObserver : public CObserver
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkDocObserver(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~CusDtLnkDocObserver();

	/** @see IObserver::AutoAttach
	*/
	void AutoAttach();

	/** @see IObserver::AutoDetach
	*/
	void AutoDetach();

	/** @see IObserver::Update
	*/
	virtual void Update(const ClassID& theChange, 
						ISubject* theSubject, 
						const PMIID& protocol, 
						void* changedBy);
	
    /** Updates this plug-in's panel when the plug-in's model changes.  Widgets that react to changes 
	    in the plug-in's model are updated by lazy notifications handled by this method.
        @param theSubject [IN] provides a reference to the object which has changed.
        @param protocol [IN] the protocol along which the change occurred.
        @param data [IN] 
    */
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

protected:
	/**	Attaches this observer to a document.
	 * 	@param document IN The document to which we want to attach.
	*/
	void AttachDocument(IDocument* document);

	/**	Detaches this observer from a document.
	 * 	@param document IN The document from which we want to detach.
	*/
	void DetachDocument(IDocument* document);

	/** Respond to a list of page items being added to document hierarchy
		@param itemList the items that just got added
	*/
	void HandleAddRemoveAdornment(const UIDList& itemList);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusDtLnkDocObserver, kCusDtLnkDocObserverImpl)

/* CusDtLnkDocObserver Constructor
*/
CusDtLnkDocObserver::CusDtLnkDocObserver(IPMUnknown* boss) 
	: CObserver(boss, IID_ICUSDTLNKDOCOBSERVER)
{
}

/* CusDtLnkDocObserver Destructor
*/
CusDtLnkDocObserver::~CusDtLnkDocObserver()	
{
}


/*	CusDtLnkDocObserver::AutoAttach
*/
void CusDtLnkDocObserver::AutoAttach()
{
	CObserver::AutoAttach();

	InterfacePtr<IDocument> document(this, UseDefaultIID());
	if (document != nil)
		this->AttachDocument(document);
}


/*	CusDtLnkDocObserver::AutoDetach
*/
void CusDtLnkDocObserver::AutoDetach()
{
	CObserver::AutoDetach();

	InterfacePtr<IDocument> document(this, UseDefaultIID());
	if (document != nil)
		this->DetachDocument(document);
}

/*	CusDtLnkDocObserver::Update
*/
void CusDtLnkDocObserver::Update(const ClassID& theChange, 
							   ISubject* theSubject, 
							   const PMIID& protocol, 
							   void* changedBy)
{
	do
	{
/*
		ICommand* command = (ICommand*)changedBy;
		const UIDList itemList = command->GetItemListReference();
		bool16 isCommandDone = command->GetCommandState() == ICommand::kDone;
		if (protocol == IID_IHIERARCHY_DOCUMENT){
			
			bool16 addRemovePossible = ((theChange == kAddToHierarchyCmdBoss) && isCommandDone);
			if(addRemovePossible) {
				this->HandleAddRemoveAdornment(itemList);
			}

		} 
*/

	} while (kFalse);
}

/* ExtLinkUITreeObserver::LazyUpdate 
*/
void CusDtLnkDocObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	if (protocol == IID_ILINK)
	{
		K2Vector<UID> addedItems, updatedItems, deletedItems;
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		if (listData) {
			listData->BreakoutChanges(&addedItems, &deletedItems, &updatedItems);
		}
		if(!addedItems.empty()){
			UIDList addedList(::GetDataBase(theSubject));
			for(auto iter = addedItems.rbegin(); iter != addedItems.rend(); ++iter){
				UIDRef linkUIDRef(::GetDataBase(theSubject), *iter);
				InterfacePtr<const ILink> theLink(linkUIDRef,UseDefaultIID());
				addedList.Append(theLink->GetObject());
			}
			this->HandleAddRemoveAdornment(addedList);
		}
		if(!updatedItems.empty()){
			UIDList updatedList(::GetDataBase(theSubject));
			for (auto iter = updatedItems.rbegin(); iter != updatedItems.rend(); ++iter) {
				UIDRef linkUIDRef(::GetDataBase(theSubject), *iter);
				InterfacePtr<const ILink> theLink(linkUIDRef,UseDefaultIID());
				updatedList.Append(theLink->GetObject());				
			}
			this->HandleAddRemoveAdornment(updatedList);
		}
	}
}

/*	CusDtLnkDocObserver::AttachDocument
*/
void CusDtLnkDocObserver::AttachDocument(IDocument* document)
{
	do
	{
		InterfacePtr<ISubject> docSubject(document, UseDefaultIID());
		ASSERT(docSubject);
		if(!docSubject) {
			break;
		}
		if (!docSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_ICUSDTLNKDOCOBSERVER)) {
			docSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_ICUSDTLNKDOCOBSERVER);
		}			
		if( !docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILINK, IID_ICUSDTLNKDOCOBSERVER)) {
			docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILINK, IID_ICUSDTLNKDOCOBSERVER);
		}
	} while (kFalse);
}


/*	CusDtLnkDocObserver::DetachDocument
*/
void CusDtLnkDocObserver::DetachDocument(IDocument* document)
{
	do
	{
		InterfacePtr<ISubject> docSubject(document, UseDefaultIID());
		ASSERT(docSubject);
		if(!docSubject) {
			break;
		}
		if (docSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_ICUSDTLNKDOCOBSERVER)) {
			docSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_ICUSDTLNKDOCOBSERVER);
		}
		if( docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILINK, IID_ICUSDTLNKDOCOBSERVER)) {
			docSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILINK, IID_ICUSDTLNKDOCOBSERVER);
		}
	} while (kFalse);
}

void CusDtLnkDocObserver::HandleAddRemoveAdornment(const UIDList& itemList)
{
	Utils<ICusDtLnkFacade> facade;
	ASSERT(facade);
	if(!facade) {
		return;
	}
	do {

		for(int32 i=0; i < itemList.Length(); i++) {
			UIDRef pageItemUIDRef = itemList.GetRef(i);
			
			// Maybe this item has our adornment, but doesn't need it any more
			if(!facade->NeedsOurAdornment(pageItemUIDRef)) {
				if(facade->HasOurAdornment(pageItemUIDRef)) {
					UIDList tempUIDList(pageItemUIDRef);
					ErrorCode err = facade->RemoveAdornment(tempUIDList);
					ASSERT(err == kSuccess);
				}
				continue;
			}
			// Only add if we think we have found a container for out custom datalinked item
			// and also only add if is a graphic frame
			InterfacePtr<IHierarchy> hierarchy(pageItemUIDRef, UseDefaultIID());
			if(hierarchy){
				InterfacePtr<IGraphicFrameData> graphicFrameData(hierarchy->QueryParent(), UseDefaultIID());
				if(graphicFrameData) {
					UIDList containerUIDList(::GetUIDRef(graphicFrameData));
					ErrorCode err = facade->AddAdornment(containerUIDList);
					ASSERT(err == kSuccess);
				}
			}
		}
	} while(kFalse);
}	
