//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelTreeObserver.cpp $
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
#include "IDocument.h"
#include "ISubject.h"
#include "ITreeViewMgr.h"
#include "ILinkManager.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkInfoProvider.h"
#include "IWorkspace.h"
#include "ITreeViewController.h"
#include "IPanelControlData.h"
#include "IUIFontSpec.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "IColumnHeaderPanelData.h"
#include "ILinksTreeNodeList.h"
#include "IIntData.h"
#include "IStaticTextAttributes.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IColumnHeaderAttributes.h"

// ----- Includes -----

#include "CObserver.h"
#include "LinksUIID.h"
#include "LinksID.h"
#include "LocaleSetting.h"
#include "CreateObject.h"
#include "CoreResTypes.h"
#include "LinksUIResDefs.h"
#include "RsrcSpec.h"
#include "ListLazyNotificationData.h"
#include "LinkQuery.h"

// ----- Utility files -----

#include "ILayoutUIUtils.h"
#include "ILinksUIUtils.h"
#include "PreferenceUtils.h"
#include "LinksTreeUIDNodeID.h"
#include "StdHeightWidthConstants.h"

//#include "K2Vector.tpp"

//========================================================================================
// CLASS LinksUIPanelTreeObserver
//========================================================================================
class LinksUIPanelTreeObserver : public CObserver
{
	public:
		LinksUIPanelTreeObserver(IPMUnknown *boss);
		virtual ~LinksUIPanelTreeObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);
		
		virtual void AutoAttach();
			// If the observer knows who to attach itself to, it'll do so with this call
			
		virtual void AutoDetach();
			// If the observer knows who to detach itself from, it'll do so with this call

	private:
		void ActiveDocChange(const IDocument* activeDoc);
		void AttachToNewFrontDoc(const IDocument* newFrontDoc);
		void DetachFromDoc();
		void UpdateLinkTreeHeaderWidget();
		void AttachDynamicInfoProviders(const IDocument* newFrontDoc);
		void DetachDynamicInfoProviders(const IPMUnknown* oldDoc);
		void NotifyDynamicLinkInfosForInval(const PMIID& protocol);
		void RebuildTree(bool attaching) const;
		void GenerateLinkNodeTreeForCurrentDocument() const;
		bool IsMoreInfoSectionShowing() const;
	
		void HandleLinkModelChange(IDataBase* db, const LazyNotificationData* data);
		void HandleLinksUIPrefsChange(const LazyNotificationData* data);
			
		enum LinkNodeAction {kExpandLinkNodes,kSelectLinkNodes};
		void SelectOrExpandNodes(NodeID whichNode, K2Vector<LinkUIDsStruct>  nodesToSelectOrExpand, LinkNodeAction whichAction) const;
		void RecordCurrentlyExpandedNodes(K2Vector<LinkUIDsStruct>& expandedList, const NodeID& topNode = kInvalidNodeID) const;
		void EnableDrawingIfDisabled();
		
		bool fEnableRedrawAtNextLinkNotification;
		mutable K2Vector<LinkUIDsStruct> fNodesExpandedAtDetach;
};


CREATE_PMINTERFACE(LinksUIPanelTreeObserver, kLinksUIPanelTreeObserverImpl)

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver constructor 
//----------------------------------------------------------------------------------------

LinksUIPanelTreeObserver::LinksUIPanelTreeObserver(IPMUnknown *boss) :
	CObserver(boss),fEnableRedrawAtNextLinkNotification(false)
{
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::~LinksUIPanelTreeObserver: 
//----------------------------------------------------------------------------------------

LinksUIPanelTreeObserver::~LinksUIPanelTreeObserver()
{
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::AutoAttach()
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();

	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject)
		{
			contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
		}

		ActiveDocChange(context->GetContextDocument());
		
		InterfacePtr<const IPMUnknown> sessionWS(GetExecutionContextSession()->QueryWorkspace());
		InterfacePtr<ISubject> wsSubject(sessionWS, UseDefaultIID());
		wsSubject->AttachObserver(ISubject::kBothAttachments,this, IID_ILINKSUIPANELPREFS,IID_IOBSERVER);

		//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::AutoAttach forcing tree to rebuild\n");
		RebuildTree(true);
		
		UpdateLinkTreeHeaderWidget();
	}
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::AutoDetach()
{
	CObserver::AutoDetach();
	
	fNodesExpandedAtDetach.clear();
	RecordCurrentlyExpandedNodes(fNodesExpandedAtDetach);
	
	InterfacePtr<const IPMUnknown> sessionWS(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> wsSubject(sessionWS, UseDefaultIID());
	wsSubject->DetachObserver(ISubject::kBothAttachments,this, IID_ILINKSUIPANELPREFS,IID_IOBSERVER);
	
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject)
		{
			if (contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER))
			{
				contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
			}
		}
	}

	DetachFromDoc();
	InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	linksUIPrefs->SetCurrentDocDB(nil);
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::Update: 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#ifdef DEBUG				
	DebugClassUtilsBuffer buf1;
	TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::Update got message IID %s\n",DebugClassUtils::GetIDName(&buf1,protocol));
#endif		


	#pragma unused(theChange,theSubject)
	if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
	{
		InterfacePtr<IActiveContext> context(theSubject, UseDefaultIID());
		//const PMIID& what = *((const PMIID*)changedBy);
		IActiveContext::ContextInfo* info = (IActiveContext::ContextInfo*)changedBy;

		if( /*what*/ info->Key() == IID_IDOCUMENT )
		{
			ActiveDocChange(context->GetContextDocument());
			//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::Update forcing tree to rebuild for active document change\n");
			RebuildTree(false);
		}
	}
	else if(protocol == IID_ILINKMANAGER)
	{
		if(theChange == kLinkModelChangeEnd)
		{
				// once we get a model change end, we know we're out of sync with the model until we get an abort or a lazy notification.
			TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::Update got kLinkModelChangeEnd. Will enable redraw at next notification.\n");
			fEnableRedrawAtNextLinkNotification = true;
			InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
			InterfacePtr<IBoolData> disableDrawingData((IBoolData*)wp->QueryParentFor(IID_LINKSPANELDRAWINGDISABLED));
			disableDrawingData->Set(kTrue);

		}
		else if(theChange == kLinkModelChangeAbort)
		{
			TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::Update got kLinkModelChangeAbort. Will enable redraw now.\n");
			fEnableRedrawAtNextLinkNotification = true;
			EnableDrawingIfDisabled();
		}
	}
	else if(protocol == IID_ILINKSUIPANELPREFS)
	{
		ListLazyNotificationData<ClassID> cookie;
		cookie.ItemChanged(theChange);
		
		HandleLinksUIPrefsChange(&cookie);
	}
//	else
//	{	
//		NotifyDynamicLinkInfosForInval(protocol);
//	}
}

bool LinksUIPanelTreeObserver::IsMoreInfoSectionShowing() const
{
	InterfacePtr<const IControlView> moreInfoPanelView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinkInfoOuterPanelWidgetID,IID_ICONTROLVIEW));
	//TRACEFLOW("Links:LinksUI","IsMoreInfoSectionShowing returning %d\n",moreInfoPanelView->IsVisible());
	return moreInfoPanelView->IsVisible();

}

void LinksUIPanelTreeObserver::NotifyDynamicLinkInfosForInval(const PMIID& protocol)
{
	// we should get here for any IID that our info providers have registered us for. See if this message needs to make us inval.
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	const int32 numHandlers = linksUIPrefs->GetNumShowingInfoColumns();
	InterfacePtr<IControlView> treeView(this,UseDefaultIID());

	for (int i = 0; i < numHandlers; ++i) 
	{		
		InterfacePtr<ILinkInfoProvider> infoService(linksUIPrefs->QueryNthShowingInfoColumn(i));
		if(infoService->IsLinkInfoDynamic())
		{
			if(infoService->ShouldCauseRefreshOfInfo(protocol))
			{
//#ifdef DEBUG				
//				DebugClassUtilsBuffer buf1,buf2;
//				TRACEFLOW("Links:LinksUI","Got message %s that we should inval the column of provider %s for\n",DebugClassUtils::GetIDName(&buf1,protocol),DebugClassUtils::GetIDName(&buf2,::GetClass(infoService)));
//#endif				
				PMRect invalRect = treeView->GetFrame();
				invalRect.MoveTo(0,0);
				int32 left,right = 0;
				InterfacePtr<const IColumnHeaderPanelData> columnHeaderData((IColumnHeaderPanelData*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIColumnHeaderRowWidgetID,IID_ICOLUMNHEADERPANELDATA));
				columnHeaderData->GetColumnBounds(i,left,right);
				invalRect.Left() = left;
				invalRect.Right() = right;
				treeView->Invalidate(&invalRect);
			}
		}
	}
	
	if(IsMoreInfoSectionShowing()) // if more info section is not showing, it doesn't need to update.
	{
		NodeIDList selectedItems;
		InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());
		treeController->GetSelectedItems(selectedItems);
		if(selectedItems.size() == 1) // more info section only shows info when 1 item is selected, so don't bother updating otherwise.
		{
			const int32 numMoreInfoHandlers = linksUIPrefs->GetNumMoreInfoProviders();
			for (int i = 0; i < numMoreInfoHandlers; ++i) 
			{
				InterfacePtr<ILinkInfoProvider> moreInfoProvider(linksUIPrefs->QueryNthMoreInfoProvider(i));
				if(moreInfoProvider->IsLinkInfoDynamic())
				{
					if(moreInfoProvider->ShouldCauseRefreshOfInfo(protocol))
					{
//		#ifdef DEBUG				
//						DebugClassUtilsBuffer buf1,buf2;
//						TRACEFLOW("Links:LinksUI","Got message %s that we should refetch the more info of provider %s for\n",DebugClassUtils::GetIDName(&buf1,protocol),DebugClassUtils::GetIDName(&buf2,::GetClass(moreInfoProvider)));
//		#endif								
						// notify so the link info panel can inval appropriately.
						InterfacePtr<ISubject> subject(this, UseDefaultIID());
						if (subject)
							subject->Change(::GetClass(this), IID_IDYNAMICLINKINFOCHANGE, moreInfoProvider);

					}
				}
					
			}
		}
	}

	
}

static IDataBase* gSortDocDB = nil;
static const ILinkInfoProvider* gSortInfoProvider = nil;
static const ILinkInfoProvider* gSecondarySortInfoProvider = nil;
static bool gSortAscending = kTrue;

struct LinkInfoCompareClass
{
	inline bool operator()(LinkTreeEntry* const& firstEntry, LinkTreeEntry* const& secondEntry)
	{
		InterfacePtr<const ILink> firstLink(gSortDocDB,firstEntry->GetLinkUIDRef().GetUID(),UseDefaultIID());
		InterfacePtr<const ILink> secondLink(gSortDocDB,secondEntry->GetLinkUIDRef().GetUID(),UseDefaultIID());
		InterfacePtr<const ILinkResource> firstLinkResource(gSortDocDB,firstEntry->GetLinkResourceUID(),UseDefaultIID());
		InterfacePtr<const ILinkResource> secondLinkResource(gSortDocDB,secondEntry->GetLinkResourceUID(),UseDefaultIID());
		if((firstLink && secondLink) || (firstLinkResource && secondLinkResource))
		{
//	#ifdef DEBUG
//			DebugClassUtilsBuffer clsBuf;
//			ASSERT_MSG(firstLink != nil,FORMAT_ARGS("Failed to get ILink from UID %d, which is ClassID %s",firstLinkUID.Get(),DebugClassUtils::GetIDName(&clsBuf,gSortDocDB->GetClass(firstLinkUID))));
//			ASSERT_MSG(secondLink != nil,FORMAT_ARGS("Failed to get ILink from UID %d, which is ClassID %s",secondLinkUID.Get(),DebugClassUtils::GetIDName(&clsBuf,gSortDocDB->GetClass(secondLinkUID))));
//	#endif
			
			int32 compare = gSortInfoProvider->Compare(firstLink,firstLinkResource,secondLink, secondLinkResource);
			if(compare == 0)
				compare = gSecondarySortInfoProvider->Compare(firstLink,firstLinkResource,secondLink, secondLinkResource);
			
			if(gSortAscending)
				return compare < 0;
			else
				return compare > 0;
		}
		return 0;
	}
};

static void SortListOfLinks(IDataBase* docDB, K2Vector<LinkTreeEntry*>& childElements)
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
//	IDataBase* docDB = linksUIPrefs->GetCurrentDocDB();

	gSortDocDB = docDB;
	gSortAscending = linksUIPrefs->GetSortLinksAscending();
	
	gSortInfoProvider = linksUIPrefs->GetSortInfoProvider();
	gSecondarySortInfoProvider = linksUIPrefs->GetSecondarySortInfoProvider();

	std::sort(childElements.begin(), childElements.end(), LinkInfoCompareClass());
}

void RemoveUIDsFromList(UIDList *listOfUIDs, const UIDList& uidsToRemoveFromOtherList)
{
	if(!uidsToRemoveFromOtherList.IsEmpty())
	{
//		TRACEFLOW("Links:LinksUI","Found %d links to filter out, because of multiple links to same resource.\n",uidsToRemoveFromOtherList.size());
		for(int32 filterIndex = uidsToRemoveFromOtherList.size() - 1; filterIndex >= 0; --filterIndex)
		{
			for(int32 i = listOfUIDs->size() - 1; i >=0; --i)
			{
				if(listOfUIDs->At(i) == uidsToRemoveFromOtherList[filterIndex])
				{
					listOfUIDs->Remove(i);
					break;
				}
			}
		}
	}
}

static void SetSublinksForLinkEntry(IDataBase* db, LinkTreeEntry* parentEntry, K2Vector<LinkTreeEntry*>& childElements);

static void ProcessChildLinks(IDataBase* db, const K2Vector<LinkTreeEntry*>& childElements)
{
	for(K2Vector<LinkTreeEntry*>::const_iterator childElementIter = childElements.begin(); childElementIter != childElements.end(); ++childElementIter)
	{
		InterfacePtr<const ILink> theLink(db,(*childElementIter)->GetLinkUIDRef().GetUID(),UseDefaultIID());
		if(theLink)
		{
			UIDList childLinks(db);
			theLink->GetChildren(childLinks);
			if(childLinks.size())
			{
				K2Vector<LinkTreeEntry*> grandChildElements;

//				TRACEFLOW("Links:LinksUI","ProcessChildLinks:Link UID %d apparently has %d child links.\n",*childElementIter,childLinks.size());
				// need to do duplicate resource filtering here...
				for(UIDList::iterator childLinkIter = childLinks.begin(); childLinkIter < childLinks.end(); ++childLinkIter)
				{
					bool filterOutThisLink = false;
					UIDList childLinksToSameResource(db);
					InterfacePtr<const ILink> oneChildLink(db,*childLinkIter,UseDefaultIID());
					if(!oneChildLink)
					{
						filterOutThisLink = true;
//						TRACEFLOW("Links:LinksUI","ProcessChildLinks - trying to get ILink for child link UID %d, but failed?!\n",*childLinkIter);
						break;
					}
//					TRACEFLOW("Links:LinksUI","ProcessChildLinks - processing child with LinkUID %d, Link Resource UID %d!\n",*childLinkIter,oneChildLink->GetResource());
						
					// now look for other child links that share this link resource. We want to combine these in our treeview.
					for(UIDList::iterator secondaryChildLinkIter = childLinkIter + 1; secondaryChildLinkIter != childLinks.end(); ++secondaryChildLinkIter)
					{
						InterfacePtr<const ILink> anotherChildLink(db,*secondaryChildLinkIter,UseDefaultIID());
						if(!anotherChildLink)
						{
//							TRACEFLOW("Links:LinksUI","ProcessChildLinks - trying to get ILink for child link UID %d, but failed?!\n",*secondaryChildLinkIter);
							break;
						}
						if(oneChildLink->GetResource() == anotherChildLink->GetResource())
						{
							//TRACEFLOW("Links:LinksUI","ProcessChildLinks - filtering out child link uid %d, because it's sharing a link resource with another child link\n",*secondaryChildLinkIter);
							childLinksToSameResource.push_back(*secondaryChildLinkIter);
						}
					}
					
					if(childLinksToSameResource.size())
					{
						childLinksToSameResource.push_back(*childLinkIter);
						//TRACEFLOW("Links:LinksUI","ProcessChildLinks - filtering out child link uid %d, because it's sharing a link resource with another child link\n",*childLinkIter);
						// now I need to remove all these links from the list for the parent, add them to the list for the link resource, and add the link resource entry to the parent.

						LinkTreeEntry* sharedResourceEntry = new LinkTreeEntry(UIDRef(childLinksToSameResource.GetDataBase(),kInvalidUID), oneChildLink->GetResource(),*childElementIter);

						K2Vector<LinkTreeEntry*> linksSharingResource;
						for(UIDList::iterator uidIter = childLinksToSameResource.begin(); uidIter != childLinksToSameResource.end(); ++uidIter)
						{
							ASSERT_MSG(childLinksToSameResource.GetDataBase()->IsValidUID(*uidIter),"ProcessChildLinks DB of UIDList doesn't match the UID we're working with");
							LinkTreeEntry* linkSharingResource = new LinkTreeEntry(UIDRef(childLinksToSameResource.GetDataBase(),*uidIter), oneChildLink->GetResource(),sharedResourceEntry);
							linksSharingResource.push_back(linkSharingResource);
						}
						SetSublinksForLinkEntry(db,sharedResourceEntry,linksSharingResource);
						grandChildElements.push_back(sharedResourceEntry);

						filterOutThisLink = true;
						RemoveUIDsFromList(&childLinks,childLinksToSameResource);	// take these UIDs which are now children of the link resource out of our list we're iterating																	

					}
					
					if(!filterOutThisLink)
					{
						ASSERT_MSG(childLinksToSameResource.GetDataBase()->IsValidUID(*childLinkIter),"ProcessChildLinks DB of UIDList doesn't match the UID we're working with");
						LinkTreeEntry* newChildElement = new LinkTreeEntry(UIDRef(childLinksToSameResource.GetDataBase(),*childLinkIter),oneChildLink->GetResource(),*childElementIter);
						grandChildElements.push_back(newChildElement);
					}
					
				}
			
				//TRACEFLOW("Links:LinksUI","ProcessChildLinks - linkUID %d has %d child links\n",::GetUID(theLink),childLinks.size());
				SetSublinksForLinkEntry(db,*childElementIter,grandChildElements);
			}
		}
	}
}

static void SetSublinksForLinkEntry(IDataBase* db, LinkTreeEntry* parentEntry, K2Vector<LinkTreeEntry*>& childElements)
{	
	SortListOfLinks(db,childElements);
	parentEntry->SetChildEntries(childElements);
	ProcessChildLinks(db,childElements);
}

void LinksUIPanelTreeObserver::GenerateLinkNodeTreeForCurrentDocument() const
{
	InterfacePtr<ILinksTreeNodeList> sortedLinksInterface(this,UseDefaultIID());
	TRACEFLOW("Links:LinksUI","GenerateLinkNodeTreeForCurrentDocument clearing all entries from tree cache\n");
//	sortedLinksInterface->ClearAllEntries();

	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	IDataBase* docDB = linksUIPrefs->GetCurrentDocDB();
	if(docDB)
	{
		//ASSERT_MSG(docDB->IsValidUID(kRootDocumentLinksNodeUID),"LinksUIPanelTreeObserver::GenerateLinkNodeTreeForCurrentDocument DB of doc doesn't have kRootDocumentLinksNodeUID");
		LinkTreeEntry *rootLinkEntry = new LinkTreeEntry(UIDRef(docDB,kRootDocumentLinksNodeUID),kInvalidUID,nil);

		InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
		LinkQuery query;  // don't want child links.
		query.SetLinkType(ILink::kImport); 
		query.SetLinkType(ILink::kBidirectional); 
		query.SetLinkType(ILink::kExport); 
		query.SetShowInUI(kTrue);
		
		UIDList topLevelLinks(docDB);
		linkMgr->QueryLinks(query, kIDLinkClientID, topLevelLinks);
		
		//TRACEFLOW("Links:LinksUI","GenerateLinkNodeTreeForCurrentDocument - link manager claims to have %d links\n",topLevelLinks.size());

		// strip out multiple links to same resource
		K2Vector<LinkTreeEntry*> childElements;
		K2Vector<UID> alreadyAddedResourceUIDs;
		for(UIDList::iterator iter = topLevelLinks.begin(); iter != topLevelLinks.end(); ++iter)
		{
			bool filterOutLink = false;
			LinkTreeEntry* newLinkResourceEntry = nil;

			InterfacePtr<const ILink> theLink(docDB,*iter,UseDefaultIID());
		
			if(!theLink)
			{
#ifdef DEBUG
// DataMerge links cause this assert because DM is missing from InCopy/InDesign server apparently...and the LinksManger isn't filtering them out.
//				DebugClassUtilsBuffer clsBuf;
//				ASSERT_FAIL(FORMAT_ARGS("Failed to get ILink from UID %d, which is ClassID %s",iter->Get(),DebugClassUtils::GetIDName(&clsBuf,docDB->GetClass(*iter))));
#endif
				filterOutLink = true;
			}
			else
			{
				if(linksUIPrefs->GetCollapseMultipleLinksToSameResource())
				{
					ILinkManager::QueryResult matchingLinks;
					if(linkMgr->QueryLinksByResourceUID(theLink->GetResource(),false, matchingLinks) > 1) // we just want the top level this time - no child links.
					{
						filterOutLink = true;

						if(std::find(alreadyAddedResourceUIDs.begin(),alreadyAddedResourceUIDs.end(),theLink->GetResource()) == alreadyAddedResourceUIDs.end()) // only want to do this stuff the first time we encounter a particular resource with dupl links.
						{
							alreadyAddedResourceUIDs.push_back(theLink->GetResource());
							ASSERT_MSG(newLinkResourceEntry == nil,"going to leak this - why is it set already?");
							newLinkResourceEntry = new LinkTreeEntry(UIDRef(docDB,kInvalidUID),theLink->GetResource(),rootLinkEntry);
							K2Vector<LinkTreeEntry*> linksSharingResource;
							//TRACEFLOW("Links:LinksUI","Resource UID %d has %d links pointing to it\n",theLink->GetResource().Get(),matchingLinks.size());
							for(ILinkManager::QueryResult::iterator duplResourceIter = matchingLinks.begin(); duplResourceIter != matchingLinks.end(); ++duplResourceIter)
							{
								ASSERT_MSG(docDB->IsValidUID(*duplResourceIter),"LinksUIPanelTreeObserver::GenerateLinkNodeTreeForCurrentDocument DB of doc doesn't match the link UID");
								LinkTreeEntry* newChildElement = new LinkTreeEntry(UIDRef(docDB,*duplResourceIter),theLink->GetResource(),newLinkResourceEntry);
								linksSharingResource.push_back(newChildElement);
							}
							SetSublinksForLinkEntry(docDB,newLinkResourceEntry,linksSharingResource);
						}
					}
				}

			}
			if(!filterOutLink)
			{
				ASSERT_MSG(docDB->IsValidUID(*iter),"LinksUIPanelTreeObserver::GenerateLinkNodeTreeForCurrentDocument DB of doc doesn't match the link UID");
				LinkTreeEntry* newChildElement = new LinkTreeEntry(UIDRef(docDB,*iter),theLink->GetResource(),rootLinkEntry);
				childElements.push_back(newChildElement);
			}
			if(newLinkResourceEntry)
			{
				ASSERT_MSG(filterOutLink,"How can we be adding a resource entry if we're not filtering out a link entry?");
				childElements.push_back(newLinkResourceEntry);
			}
			
		}				
			
		SetSublinksForLinkEntry(docDB,rootLinkEntry, childElements);
		sortedLinksInterface->AddEntireTree(rootLinkEntry);
	}	
	else
		sortedLinksInterface->AddEntireTree(nil);
			
}


void LinksUIPanelTreeObserver::SelectOrExpandNodes(NodeID whichNode, K2Vector<LinkUIDsStruct>  nodesToSelectOrExpand, LinkNodeAction whichAction) const
{
#ifdef DEBUG
	if(whichAction == kSelectLinkNodes)
		TRACEFLOW("Links:LinksUI","SelectOrExpandNodes with %d items in list\n",nodesToSelectOrExpand.size());
#endif

	InterfacePtr<const ITreeViewHierarchyAdapter>	treeAdapter(this, UseDefaultIID());
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());	
	InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());

	TreeNodePtr<const LinksTreeUIDNodeID>	newRootLinkNode(whichNode);
	for(K2Vector<LinkUIDsStruct>::const_iterator iter = nodesToSelectOrExpand.begin(); iter != nodesToSelectOrExpand.end(); ++iter)
	{
		for(int i = treeAdapter->GetNumChildren(whichNode) -1; i >=0; --i)
		{
			NodeID childNode = treeAdapter->GetNthChild(whichNode,i);
			TreeNodePtr<const LinksTreeUIDNodeID>	childLinkNode(childNode);
			if(childLinkNode->GetLinkUIDRef().GetUID() == iter->fLinkUID && childLinkNode->GetLinkResourceUID() == iter->fLinkResourceUID)
			{
				if(whichAction == kExpandLinkNodes)
					treeViewMgr->ExpandNode(childNode);
				else
				{
					treeController->Select(childNode);
				}
				break;
			}
			SelectOrExpandNodes(childNode,nodesToSelectOrExpand,whichAction);

		}

	}

}

void LinksUIPanelTreeObserver::RecordCurrentlyExpandedNodes(K2Vector<LinkUIDsStruct>& expandedList, const NodeID& startingNode) const
{
	NodeID rootNode = startingNode;
	InterfacePtr<const ITreeViewHierarchyAdapter>	treeAdapter(this, UseDefaultIID());
	if(!startingNode.IsValid())
		rootNode = treeAdapter->GetRootNode();
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());	
	for(int i = treeAdapter->GetNumChildren(rootNode) -1; i >=0; --i)
	{
		NodeID childNode = treeAdapter->GetNthChild(rootNode,i);
		if(treeViewMgr->IsNodeExpanded(childNode))
		{
			TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(childNode);
			const LinkTreeEntry* treeEntry = linksUIDNode->GetTreeEntry();
			if(treeEntry)
			{
				expandedList.push_back(LinkUIDsStruct(treeEntry->GetLinkUIDRef().GetUID(),treeEntry->GetLinkResourceUID()));
			}
			RecordCurrentlyExpandedNodes(expandedList,childNode);
		}
	}
}

void LinksUIPanelTreeObserver::RebuildTree(bool attaching) const
{
	K2Vector<LinkUIDsStruct> previouslySelected;
	K2Vector<LinkUIDsStruct> previouslyExpanded;
	if(!attaching)
	{
		// save off selection
		NodeIDList selectedItems;
		InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());
		treeController->GetSelectedItems(selectedItems);
		for(auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
		{
			TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(*iter);
			const LinkTreeEntry* treeEntry = linksUIDNode->GetTreeEntry();
			if(treeEntry)
			{
				UID currentTreEntry = treeEntry->GetLinkUIDRef().GetUID();
				if(treeEntry->GetLinkUIDRef().GetDataBase()->IsValidUID(currentTreEntry)) //don't add invalid entries to the list
				{
					previouslySelected.push_back(LinkUIDsStruct(currentTreEntry,treeEntry->GetLinkResourceUID()));
				}
			}
		}

		// save off expanded nodes(note we only do this for children of the root node atm. Should cover most common cases.
		RecordCurrentlyExpandedNodes(previouslyExpanded);
	}
	else
		previouslyExpanded = fNodesExpandedAtDetach;

	// clear the selection, so we get a selection change message
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	UIDList emptyList(linksUIPrefs->GetCurrentDocDB());
	Utils<ILinksUIUtils>()->SelectLinksInPanel(emptyList); 


	//actually rebuild the tree
	GenerateLinkNodeTreeForCurrentDocument();	
	//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate forcing tree to rebuild for some change\n");
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
	treeViewMgr->ChangeRoot();
	
	// now see which of the previously expanded nodes are still around, and expand them.
	InterfacePtr<const ITreeViewHierarchyAdapter>	treeAdapter(this, UseDefaultIID());
	SelectOrExpandNodes(treeAdapter->GetRootNode(),previouslyExpanded,kExpandLinkNodes);
	
	// now see which of the previously selected nodes are still around, and select them.
	if(!attaching)
		SelectOrExpandNodes(treeAdapter->GetRootNode(),previouslySelected,kSelectLinkNodes);
}

static void MarkLinkNodeAndParentsChanged(const UIDRef& linkUIDRef, ITreeViewMgr* treeViewMgr)
{
	NodeID changedNode = Utils<ILinksUIUtils>()->CreateNodeFromLinkUIDRef(linkUIDRef);
	if(changedNode.IsValid())
	{
		TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(changedNode);
		const LinkTreeEntry* treeEntry = linksUIDNode->GetTreeEntry();
		if(treeEntry)
		{
			treeViewMgr->NodeChanged(changedNode,kTrue);

			const LinkTreeEntry*	parentEntry = treeEntry->GetParentEntry();
			while(parentEntry && parentEntry->GetLinkUIDRef().GetUID() != kRootDocumentLinksNodeUID)
			{
				NodeID parentNode = LinksTreeUIDNodeID::Create(parentEntry);		
				treeViewMgr->NodeChanged(parentNode,kTrue);
				linksUIDNode.reset(parentNode);
				parentEntry = linksUIDNode->GetTreeEntry()->GetParentEntry();
			}
		}
	}
}

void LinksUIPanelTreeObserver::HandleLinkModelChange(IDataBase* db, const LazyNotificationData* data)
{
	K2Vector<ILinkManager::ChangeData> addedItems, updatedItems, deletedItems;
	const ListLazyNotificationData<ILinkManager::ChangeData> *listData = static_cast<const ListLazyNotificationData<ILinkManager::ChangeData> *>(data);
	if (listData)
		listData->BreakoutChanges(&addedItems, &deletedItems, &updatedItems);
			
	//TRACEFLOW("Links:LinksUI","Notification contains %d added items, %d deleted items, and %d updated items(listData is 0x%x)\n",addedItems.Length(),deletedItems.Length(),updatedItems.Length(),listData);

	bool notifySelectionChange = false;
	
	if(!listData || !addedItems.empty() || !deletedItems.empty())
	{
		//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate forcing tree to rebuild because of adds/deletes/unknown changes\n");
		RebuildTree(false);
	}
	else
	{
		// find the updated items in the tree and invalidate them.
		if(listData && !updatedItems.empty())
		{
			InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
			InterfacePtr<const ILinkManager> linkMgr(db,db->GetRootUID(),UseDefaultIID());
	
			notifySelectionChange = true;

			for (auto &theUpdatedItem : updatedItems)
			{
				if(theUpdatedItem.GetType() == ILinkManager::ChangeData::kLink)
				{
					UIDRef linkUIDRef(db,theUpdatedItem.GetUID());
					//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate updating single node for Link change. Link UID: %d\n",theUpdatedItem.GetUID().Get());
					MarkLinkNodeAndParentsChanged(linkUIDRef,treeViewMgr);
				}
				else if(theUpdatedItem.GetType() == ILinkManager::ChangeData::kResource)
				{
					// ok, we need to find all the nodes in the tree that refer to this resource, and mark them changed.
					UIDRef changedResourceRef(db,theUpdatedItem.GetUID());
					
					ILinkManager::QueryResult resultUIDs;
					linkMgr->QueryLinksByResourceUID(theUpdatedItem.GetUID(), true, resultUIDs);
					for(int j = static_cast<int>(resultUIDs.size()) - 1; j >= 0; --j)
					{
						//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate updating single node for IID_ILINKRESOURCE change. Link UID: %d, Link Resource UID: %d\n",resultUIDs[j].Get(),theUpdatedItem.GetUID().Get());
						UIDRef linkUIDRef(db,resultUIDs[j]);
						MarkLinkNodeAndParentsChanged(linkUIDRef,treeViewMgr);
					}
				}
				else
				{
					ASSERT_MSG(theUpdatedItem.GetType() == ILinkManager::ChangeData::kLinksResource,"Unknown type of change");
					//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate rebuilding tree because Link UID: %d, changed to use a different Link Resource UID.\n",theUpdatedItem.GetUID().Get());
					RebuildTree(false);
					break;
				}
			}
		}

	}
	EnableDrawingIfDisabled();
	
	if(notifySelectionChange)
	{
		InterfacePtr<ISubject> mySubject(this,UseDefaultIID());
		mySubject->Change(kLinksUITreeSelectionAlteredMsgBoss, IID_ITREEVIEWCONTROLLER);
	}


}

void LinksUIPanelTreeObserver::EnableDrawingIfDisabled()
{
	if(fEnableRedrawAtNextLinkNotification)
	{
		fEnableRedrawAtNextLinkNotification = false;
		//TRACEFLOW("Links:LinksUI","EnableDrawingIfDisabled - Enabling drawing of panel.\n");
		InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
		InterfacePtr<IBoolData> disableDrawingData((IBoolData*)wp->QueryParentFor(IID_LINKSPANELDRAWINGDISABLED));
		disableDrawingData->Set(kFalse);
		
		InterfacePtr<IBoolData> invalWhenPossibleData(disableDrawingData,IID_LINKSPANELSHOULDINVALDATA);
		if(invalWhenPossibleData->Get())
		{
			invalWhenPossibleData->Set(kFalse);
			InterfacePtr<IControlView> panelView(disableDrawingData,UseDefaultIID());
			panelView->Invalidate();
		}
	}
}

void LinksUIPanelTreeObserver::HandleLinksUIPrefsChange(const LazyNotificationData* data)
{
	K2Vector<ClassID> addedItems, updatedItems, deletedItems;
	const ListLazyNotificationData<ClassID> *listData = static_cast<const ListLazyNotificationData<ClassID> *>(data);
	if (listData)
		listData->BreakoutChanges(&addedItems, &deletedItems, &updatedItems);

	ASSERT_MSG(addedItems.size() == 0 && deletedItems.size() == 0,"Dunno what to do with this lazy notification data...");
	
	for(auto iter = updatedItems.rbegin(); iter != updatedItems.rend(); ++iter)
	{
		if(*iter == kLinksUIPrefTreeStructureChangeMsgBoss)
		{
			//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate forcing tree to rebuild for IID_ILINKSUIPANELPREFS change kLinksUIPrefTreeStructureChangeMsgBoss\n");
			
			RebuildTree(false);	
			break;
		
		}
		else if(*iter == kLinksUITreeRowChangeMsgBoss)
		{
			//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate invalidating all rows for IID_ILINKSUIPANELPREFS change kLinksUITreeRowChangeMsgBoss\n");
			InterfacePtr<const ITreeViewHierarchyAdapter>	treeAdapter(this, UseDefaultIID());
			InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
			NodeID rootNode = treeAdapter->GetRootNode();
			TreeNodePtr<const LinksTreeUIDNodeID>	rootLinkNode(rootNode);
			if(rootNode.IsValid() && rootLinkNode->GetTreeEntry() != nil)
				treeViewMgr->NodeChanged(rootNode,kTrue);

			RebuildTree(false);
		}
		else if(*iter == kLinksUIPrefInfoPaneChangeMsgBoss)
		{
			//TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate invalidating info pane for IID_ILINKSUIPANELPREFS change kLinksUIPrefInfoPaneChangeMsgBoss\n");
			InterfacePtr<ISubject> mySubject(this,UseDefaultIID());
			mySubject->Change(kLinksUITreeSelectionAlteredMsgBoss, IID_ITREEVIEWCONTROLLER);
		}
		  
	}
	
	UpdateLinkTreeHeaderWidget();
	
	// if we got kLinksUIPrefInfoPaneChangeMsgBoss or  kLinksUIPrefTreeStructureChangeMsgBoss - we need to update the attach/detach of dynamic link info providers, because the showing info or columns may have changed.
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	IDataBase* currentLinksUIDocDB = linksUIPrefs->GetCurrentDocDB();
	if( currentLinksUIDocDB )
	{		
		InterfacePtr<IDocument> doc( currentLinksUIDocDB,currentLinksUIDocDB->GetRootUID(), UseDefaultIID() );

		if( doc )
		{
			DetachDynamicInfoProviders(doc);
			AttachDynamicInfoProviders(doc);
		}
	}
}

void LinksUIPanelTreeObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
#ifdef DEBUG				
	DebugClassUtilsBuffer buf1;
	TRACEFLOW("Links:LinksUI","LinksUIPanelTreeObserver::LazyUpdate got message IID %s\n",DebugClassUtils::GetIDName(&buf1,protocol));
#endif				
	#pragma unused(data,theSubject)

	if(protocol == IID_ILINKDATA_CHANGED)
	{    
		HandleLinkModelChange(::GetDataBase(theSubject),data);
	}
	else if(protocol == IID_ILINKSUIPANELPREFS)
	{
		HandleLinksUIPrefsChange(data);
	}
	else
		NotifyDynamicLinkInfosForInval(protocol);

}

void LinksUIPanelTreeObserver::AttachDynamicInfoProviders(const IDocument* newFrontDoc)
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	const int32 numHandlers = linksUIPrefs->GetNumShowingInfoColumns();
	for (int i = 0; i < numHandlers; ++i) 
	{
		InterfacePtr<ILinkInfoProvider> infoService(linksUIPrefs->QueryNthShowingInfoColumn(i));
		if(infoService->IsLinkInfoDynamic())
			infoService->AttachToDocument(this,newFrontDoc);
			
	}
	
	const int32 numMoreInfoHandlers = linksUIPrefs->GetNumMoreInfoProviders();
	for (int i = 0; i < numMoreInfoHandlers; ++i) 
	{
		InterfacePtr<ILinkInfoProvider> infoService(linksUIPrefs->QueryNthMoreInfoProvider(i));
		if(infoService->IsLinkInfoDynamic())
			infoService->AttachToDocument(this,newFrontDoc);
			
	}
	
	
}

void LinksUIPanelTreeObserver::DetachDynamicInfoProviders(const IPMUnknown* oldDoc)
{
	// we need to detach all the dynamic infos, because we might be getting called after the user has changed prefs and turned off some columns or more info providers...
	InterfacePtr<const IDocument> doc(oldDoc,UseDefaultIID());
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	const int32 numHandlers = linksUIPrefs->GetNumInfoProviders();
	for (int i = 0; i < numHandlers; ++i) 
	{
		InterfacePtr<ILinkInfoProvider> infoService(linksUIPrefs->QueryNthInfoProvider(i));
		if(infoService->IsLinkInfoDynamic())
			infoService->DetachFromDocument(this,doc);
			
	}
}
//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::AttachToNewFrontDoc 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::AttachToNewFrontDoc(const IDocument* newFrontDoc)
{

	if( newFrontDoc )
	{		
		AttachDynamicInfoProviders(newFrontDoc);
		
		InterfacePtr<ISubject>	docSubject( newFrontDoc, UseDefaultIID() );

		if( docSubject && !docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILINKDATA_CHANGED, IID_IOBSERVER))
			docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILINKDATA_CHANGED, IID_IOBSERVER);
		
		TRACEFLOW("Links:LinksUI","Attaching to IID_ILINKMANAGER on document\n");	
		if( docSubject && !docSubject->IsAttached(ISubject::kRegularAttachment,this, IID_ILINKMANAGER, IID_IOBSERVER))
			docSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ILINKMANAGER, IID_IOBSERVER);
			
	}
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::DetachFromDoc 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::DetachFromDoc()
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	IDataBase* currentLinksUIDocDB = linksUIPrefs->GetCurrentDocDB();
	if( currentLinksUIDocDB )
	{		
		InterfacePtr<ISubject> docSubject( currentLinksUIDocDB,currentLinksUIDocDB->GetRootUID(), UseDefaultIID() );

		if( docSubject )
		{
			DetachDynamicInfoProviders(docSubject);
			
			if( docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILINKDATA_CHANGED, IID_IOBSERVER))
				docSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILINKDATA_CHANGED, IID_IOBSERVER);
				
			TRACEFLOW("Links:LinksUI","Detaching from IID_ILINKMANAGER on document\n");	
			if( docSubject->IsAttached(ISubject::kRegularAttachment,this, IID_ILINKMANAGER, IID_IOBSERVER))
				docSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ILINKMANAGER, IID_IOBSERVER);
		}
			
	}
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeObserver::ActiveDocChange: 
//----------------------------------------------------------------------------------------
void LinksUIPanelTreeObserver::ActiveDocChange(const IDocument* activeDoc)
{
	InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	IDataBase* currentLinksUIDocDB	= linksUIPrefs->GetCurrentDocDB();
	IDataBase* activeDocDB			= ::GetDataBase(activeDoc);
	
	TRACEFLOW("Drover:Widgets","LinksUIPanelTreeObserver::ActiveDocChange old doc DB 0x%x, new doc DB 0x%x\n", currentLinksUIDocDB, activeDocDB);

	
	if (activeDocDB != currentLinksUIDocDB)
	{		
		this->DetachFromDoc();
		
		this->AttachToNewFrontDoc(activeDoc);
					
		linksUIPrefs->SetCurrentDocDB(activeDocDB);

	}
	InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());
	treeController->DeselectAll();
	EnableDrawingIfDisabled();
}

void LinksUIPanelTreeObserver::UpdateLinkTreeHeaderWidget()
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	const int32 numHandlers = linksUIPrefs->GetNumShowingInfoColumns();

	InterfacePtr<IPanelControlData> headerRowPCD((IPanelControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIColumnHeaderRowWidgetID,IID_IPANELCONTROLDATA));
	headerRowPCD->ReleaseAll();
	
	const ILinkInfoProvider* sortProvider = linksUIPrefs->GetSortInfoProvider();
	int32 sortColIndex = -1;

	// create needed widgets
	for(int i = 0; i < numHandlers; ++i) 
	{	
		InterfacePtr<const ILinkInfoProvider> infoService(linksUIPrefs->QueryNthShowingInfoColumn(i));
		if(infoService == sortProvider)
			sortColIndex = i;

		PMRsrcID headerIcon = infoService->GetInfoDescriptionIcon();
		InterfacePtr<IControlView> newHeaderWidget((IControlView*) ::CreateObject(::GetDataBase(headerRowPCD),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, (headerIcon.fId == kInvalidRsrcID ? kLinksUIDynamicColumnTextItemResID : kLinksUIDynamicColumnIconWidgetResID)),IID_ICONTROLVIEW));
		ASSERT_MSG(newHeaderWidget != nil,"Failed to create widget for column header");
		
		InterfacePtr<ITextControlData>	nodeNameData(newHeaderWidget, UseDefaultIID());
		if(nodeNameData)
		{
			nodeNameData->SetString(infoService->GetInfoDescriptionString());	

			InterfacePtr<IStaticTextAttributes> textAttr(newHeaderWidget,UseDefaultIID());
			textAttr->SetAlignment(infoService->GetInfoTextAlignment());			
		}
		else
		{
			ASSERT_MSG(headerIcon.fId != kInvalidRsrcID,"This widget isn't text based, but we don't have a resource id for the icon?");
			newHeaderWidget->SetRsrcPluginID(headerIcon.fPluginId);
			newHeaderWidget->SetRsrcID(headerIcon.fId);
		}
			
		InterfacePtr<IIntData> providerIndexData(newHeaderWidget,IID_LINKINFOPROVIDERINDEX);
		providerIndexData->Set(i);
		
		headerRowPCD->AddWidget(newHeaderWidget);
	}
			
	InterfacePtr<IColumnHeaderPanelData> headerColumnData(headerRowPCD,UseDefaultIID());
	headerColumnData->SetColumnSort(sortColIndex,!linksUIPrefs->GetSortLinksAscending());

	headerColumnData->SetColumnGap(LinksUIUtils::kLinksUIColumnGap,kFalse,kFalse); 
	headerColumnData->SetHeaderIndent(kCC2016StandardGapBetweenWidgets,kFalse,kFalse); // should match indent for tree expander widget.
	K2Vector<int32> widths;
	linksUIPrefs->GetColumnWidths(widths);
	headerColumnData->SetColumnWidths(widths,kTrue,kFalse);
	headerColumnData->ArrangeWidgetsIntoColumns();

	// Set minimum width for columns in header
	InterfacePtr<IColumnHeaderAttributes> headerColumnAttributes(headerRowPCD,UseDefaultIID());
	ASSERT_MSG(headerColumnAttributes, "Cannot obtain header column attributes.");
	int32 minColumnWidth = 19;
	headerColumnAttributes->SetMinimumColumnWidth(minColumnWidth);

}




