//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchCacheManager.cpp $
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
#include "ISubject.h"
#include "ICommand.h"
#include "IGraphicFrameData.h"
#include "IGraphicFrameData.h"
#include "IPageItemTypeUtils.h"
#include "ISession.h"
#include "IWorkspace.h"
#include "IUIDListData.h"

#include "IFrameType.h"
#include "IHierarchy.h"
#include "CreateObject.h"
#include "IDFile.h"
#include "IImageUtils.h"
#include "ILinkManager.h"


// General includes:
#include "CObserver.h"
#include "ShuksanID.h"
#include "UIDList.h"
#include "Utils.h"
#include "Trace.h"
#include "ErrorUtils.h"
#include "CAlert.h"
#include "DebugClassUtils.h"
#include "LazyNotificationData.h"
#include "ListLazyNotificationData.h"

// Project includes:
#include "LnkWtchID.h"
#include "ILnkWtchCache.h"

/** Watches links being added and removed from a document and maintains a cache
	of links added since the document was opened in interface ILnkWtchCache.

	@see ILnkWtchCache

	@ingroup linkwatcher
*/
class LnkWtchCacheManager : public CObserver
{
public:
	/** Constructor.
		@param boss object this object is aggregated on.
	*/
	LnkWtchCacheManager(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~LnkWtchCacheManager();

	/** Attach protocols of interest.
	*/
	void AutoAttach();

	/** Detach protocols of interest.
	*/
	void AutoDetach();

	/** Handle broadcasts on protocols of interest.
		@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
		@param theSubject points to the ISubject interface for the subject that has changed.
		@param protocol specifies the ID of the changed interface on the subject boss.
		@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
	*/
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy){};
	virtual void LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* data);

protected:
	void AddToCache(const UIDList& itemList);
	void RemoveFromCache(const UIDList& itemList);
#ifndef SDKAUTOUNDO
	// Old code:
	void UndoAddToCache(const UIDList& itemList);
	void UndoRemoveFromCache(const UIDList& itemList);
#endif // SDKAUTOUNDO
	void DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	InterfacePtr<ILnkWtchCache> fAddedLinkCache;
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(LnkWtchCacheManager, kLnkWtchCacheManagerImpl)

/*
*/
LnkWtchCacheManager::LnkWtchCacheManager(IPMUnknown* boss) :
CObserver(boss, IID_ILNKWTCHCACHEMANAGER)
{
}

/*
*/
LnkWtchCacheManager::~LnkWtchCacheManager()
{
}
/*
*/
void LnkWtchCacheManager::AutoAttach()
{
	CObserver::AutoAttach();
	do {
		InterfacePtr<IDocument>	document(this, UseDefaultIID());
		ASSERT(document != nil);
		if (document == nil) {
			break;
		}
		InterfacePtr<ISubject> subject(document, UseDefaultIID());
		ASSERT(subject != nil);
		if (subject == nil) {
			break;
		}
		if( !subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINKRESOURCE, IID_ILNKWTCHCACHEMANAGER))
			subject->AttachObserver(ISubject::kBothAttachments,this, IID_ILINKRESOURCE, IID_ILNKWTCHCACHEMANAGER);
			
		if( !subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINK, IID_ILNKWTCHCACHEMANAGER))
			subject->AttachObserver(ISubject::kBothAttachments,this, IID_ILINK, IID_ILNKWTCHCACHEMANAGER);
			
		if( !subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINKMANAGER, IID_ILNKWTCHCACHEMANAGER))
			subject->AttachObserver(ISubject::kBothAttachments,this, IID_ILINKMANAGER, IID_ILNKWTCHCACHEMANAGER);
		InterfacePtr<ILnkWtchCache> cache(this, UseDefaultIID());
		if (cache)
		{
			fAddedLinkCache = cache;
		}
	} while (false);
}

/*
*/
void LnkWtchCacheManager::AutoDetach()
{
	CObserver::AutoDetach();
	do {
		InterfacePtr<IDocument>	document(this, UseDefaultIID());
		ASSERT(document != nil);
		if (document == nil) {
			break;
		}
		InterfacePtr<ISubject> subject(document, UseDefaultIID());
		ASSERT(subject != nil);
		if (subject == nil) {
			break;
		}
		if( subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINKRESOURCE, IID_ILNKWTCHCACHEMANAGER))
			subject->DetachObserver(ISubject::kBothAttachments,this, IID_ILINKRESOURCE, IID_ILNKWTCHCACHEMANAGER);
			
		if( subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINK, IID_ILNKWTCHCACHEMANAGER))
			subject->DetachObserver(ISubject::kBothAttachments,this, IID_ILINK, IID_ILNKWTCHCACHEMANAGER);
			
		if( subject->IsAttached(ISubject::kBothAttachments,this, IID_ILINKMANAGER, IID_ILNKWTCHCACHEMANAGER))
			subject->DetachObserver(ISubject::kBothAttachments,this, IID_ILINKMANAGER, IID_ILNKWTCHCACHEMANAGER);
		if (fAddedLinkCache)
		{
			fAddedLinkCache.reset(nil);
		}
	} while (false);
}

/*
*/
void LnkWtchCacheManager::LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* data)
{

	if(protocol == IID_ILINK || protocol == IID_ILINKRESOURCE)
	{    
		K2Vector<UID> addedItems, updatedItems, deletedItems;
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		if (listData) {
			listData->BreakoutChanges(&addedItems, &deletedItems, &updatedItems);
		}

		if(!listData || !addedItems.empty() || !deletedItems.empty())
		{
			if (!addedItems.empty())
			{
				UIDList addedList(::GetDataBase(theSubject));
				for(auto itr = addedItems.rbegin(); itr != addedItems.rend(); ++itr)
					addedList.Append(*itr);
				this->AddToCache(addedList);
			}
			else if (!deletedItems.empty())
			{
				UIDList deletedList(::GetDataBase(theSubject));
                for(auto itr = deletedItems.rbegin(); itr != deletedItems.rend(); ++itr)
                    deletedList.Append(*itr);
				this->RemoveFromCache(deletedList);
			}
		}
	}
}

/*
*/
void LnkWtchCacheManager::AddToCache(const UIDList& itemList)
{
	bool cacheChanged = false;
	for (int32 i = 0; i < itemList.Length(); i++) {
		UIDRef itemUIDRef = itemList.GetRef(i);
		ILnkWtchCache::Entry entry(itemUIDRef.GetUID(), kFalse);
		int32 index = fAddedLinkCache->Location(entry);
		if (index == -1)
		{
			// Add the link to the cache.
			fAddedLinkCache->push_back(entry);
			cacheChanged = true;
		}
		else
		{
			ASSERT_FAIL("LnkWtchCacheManager::AddToCache uid added twice");
		}
	}
	if (cacheChanged)
	{
		fAddedLinkCache->NotifyCacheChanged();
	}
}

#ifndef SDKAUTOUNDO
// Old code:
/*
*/
void LnkWtchCacheManager::UndoAddToCache(const UIDList& itemList)
{
	bool cacheChanged = false;
	for (int32 i = 0; i < itemList.Length(); i++) {
		UIDRef itemUIDRef = itemList.GetRef(i);
		ILnkWtchCache::Entry entry(itemUIDRef.GetUID(), kFalse);
		int32 index = fAddedLinkCache->Location(entry);
		if (index != -1)
		{
			// Delete the link from the cache.
			fAddedLinkCache->Delete(index);
			cacheChanged = true;
		}
	}
	if (cacheChanged)
	{
		fAddedLinkCache->NotifyCacheChanged();
	}
}
#endif // SDKAUTOUNDO

/*
*/
void LnkWtchCacheManager::RemoveFromCache(const UIDList& itemList)
{
	bool cacheChanged = false;
	for (int32 i = 0; i < itemList.Length(); i++) {
		UIDRef itemUIDRef = itemList.GetRef(i);
		ILnkWtchCache::Entry entry(itemUIDRef.GetUID(), kFalse);
		int32 index = fAddedLinkCache->Location(entry);
		if (index != -1)
		{
			// The link exists in the cache so it is a link that was added since
			// the doc was opened. Set it's removed flag.
			// We must leave entries in the cache for removed links in order to
			// distinguish a remove of a link that existed in the document
			// when it was opened from a remove of a link that was added to the 
			// document. If we erased the cache entry for removed links completely 
			// we could not make this distinction. So we set a flag that indicates
			// the added link has now been removed.
			fAddedLinkCache->MarkRemoved(index, kTrue);
			cacheChanged = true;
		}
		// else the link existed in the document when it was opened so ignore.
	}
	if (cacheChanged) {
		fAddedLinkCache->NotifyCacheChanged();
	}
}

#ifndef SDKAUTOUNDO
// Old code:
/*
*/
void LnkWtchCacheManager::UndoRemoveFromCache(const UIDList& itemList)
{
	bool cacheChanged = false;
	for (int32 i = 0; i < itemList.Length(); i++) {
		UIDRef itemUIDRef = itemList.GetRef(i);
		// Undo of remove; clear the remove flag if the UID has been cached.
		ILnkWtchCache::Entry entry(itemUIDRef.GetUID(), kTrue);
		int32 index = fAddedLinkCache->Location(entry);
		if (index != -1)
		{
			// The link exists in the cache so it is a link that was added since
			// the doc was opened. Clear it's removed flag.
			fAddedLinkCache->MarkRemoved(index, kFalse);
			cacheChanged = true;
		}
		// else the link existed in the document when it was opened so ignore.
	}
	if (cacheChanged) {
		fAddedLinkCache->NotifyCacheChanged();
	}
}
#endif // SDKAUTOUNDO

/*
*/
static const char* k_stateNames[7] = {"kNotDone", "kDoneDynamic", "kDone", "kNotUndone", "kUndone","kNotRedone", "kRedone"};
void LnkWtchCacheManager::DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
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
	DebugClassUtilsBuffer changedByName = "";
	DebugClassUtilsBuffer commandStateName = "";
	PMString itemListNames;
	if (changedBy)
	{
		ICommand* command = static_cast<ICommand*>(changedBy); 
		ClassID commandClassID = ::GetClass(command);
		DebugClassUtils::GetIDName(&changedByName, commandClassID);
		if (commandClassID != kInvalidClass)
		{	
			strcpy(commandStateName, k_stateNames [command->GetCommandState()]);

			const UIDList& itemList = command->GetItemListReference();
			int32 itemListLength = itemList.Length();
			IDataBase* database = itemList.GetDataBase();
			DebugClassUtilsBuffer itemClassName;
			itemListNames.Append("itemList ");
			DebugClassUtilsBuffer buf;
			for (int32 i = 0; i < itemListLength; i++) 
			{
				UID itemUID = itemList [i];
				ClassID itemClassID = database->GetClass(itemUID);
				DebugClassUtils::GetIDName(&itemClassName, itemClassID);
				sprintf(buf, "[%d=%s(uid %d)]",
					i,
					itemClassName,
					itemUID.Get());
				itemListNames.Append(buf);
			}
		}
	}
	TRACEFLOW("LinkWatcher:LinkObserver"," %s, %s, %s, %s, %s, %s\n",
		theChangeName,
		protocolName,
		theSubjectName,
		changedByName,
		commandStateName,
		itemListNames.GetUTF8String().c_str());
#endif // DEBUG
}

// End, LnkWtchCacheManager.cpp
