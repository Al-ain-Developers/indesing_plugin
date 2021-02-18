//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CHierarchyNode.cpp $
//  
//  Owner: Lonnie Millett
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

#include "VCPublicHeaders.h"


#include "CHierarchyNode.h"
#include "PersistUIDList.h"
#include "IPMStream.h"
#include "ISpread.h"

#include "IM2MMessageManager.h"
#include "TransformUtils.h"

#ifdef DEBUG
#include "IAppearanceList.h"
#include "ISession.h"
#include "IMemoryManager.h"
#include "ISpreadLayer.h"
#endif
#include "IPageItemBoundsList.h"
#include "IPageItemCache.h"
#include "IShapeGraphixCache.h"
#include "DisableInstantiationAsserts.h"

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PERSIST_PMINTERFACE(CHierarchyNode, kCHierarchyNodeImpl)
DEFINE_HELPER_METHODS(CHierarchyNode)

//----------------------------------------------------------------------------------------
// CHierarchyNode constructor
//----------------------------------------------------------------------------------------

CHierarchyNode::CHierarchyNode(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fRootUID(kInvalidUID),
	fParentUID(kInvalidUID),
	fChildrenUIDs(nil)
{
	const UIDRef thisRef(::GetUIDRef(boss));
	fRootUID = thisRef.GetUID();
	fChildrenUIDs = new PersistUIDList(thisRef.GetDataBase());
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::~CHierarchyNode 
//----------------------------------------------------------------------------------------

CHierarchyNode::~CHierarchyNode()
{
	delete fChildrenUIDs;
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::QueryChild 
//----------------------------------------------------------------------------------------

IHierarchy *CHierarchyNode::QueryChild(int32 i) const
{
	return (IHierarchy *)fChildrenUIDs->GetDataBase()->Instantiate((*fChildrenUIDs)[i], IID_IHIERARCHY);
}



//----------------------------------------------------------------------------------------
// CHierarchyNode::GetChildUID 
//----------------------------------------------------------------------------------------

UID CHierarchyNode::GetChildUID(int32 i) const
{
	return (*fChildrenUIDs)[i];
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::GetChildIndex 
//----------------------------------------------------------------------------------------

int32 CHierarchyNode::GetChildIndex(const IHierarchy * p) const
{
	return fChildrenUIDs->Location(::GetUID(p));
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::GetChildCount 
//----------------------------------------------------------------------------------------

int32 CHierarchyNode::GetChildCount() const
{
	return fChildrenUIDs->Length();
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::QueryParent 
//----------------------------------------------------------------------------------------

IHierarchy *CHierarchyNode::QueryParent() const
{
	UID parentUID = fParentUID;
	
	if (parentUID == kInvalidUID)
		return nil;
		
	return (IHierarchy *)fChildrenUIDs->GetDataBase()->Instantiate(parentUID, IID_IHIERARCHY);
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::SetParent 
//----------------------------------------------------------------------------------------

void CHierarchyNode::SetParent(IHierarchy *newParent)
{
	UID newParentUID;
	const UIDRef thisRef = ::GetUIDRef(this);
	const UIDRef newParentRef = ::GetUIDRef(newParent);

	ASSERT((thisRef.GetDataBase() == newParentRef.GetDataBase()) ||
		   (newParentRef.GetDataBase() == nil));
	
	if (fParentUID != newParentRef.GetUID())
	{
		ASSERT_MSG( fParentUID == kInvalidUID || newParentRef.GetUID() == kInvalidUID, "CHierarchyNode - resetting parent (add without remove)" ) ;

		const UID oldRootUID = this->GetRootUID();
		const UID oldDocumentUID = thisRef.GetDataBase()->GetRootUID();
		const UID newRootUID = (newParent? newParent->GetRootUID() : kInvalidUID);
		const UID newDocumentUID = newParent ? oldDocumentUID : kInvalidUID;

		//
		// 03/28/07 dwaterfa: According to the comments in IHierarchy this
		// method really should be protected, but can't be. So it is not
		// intended to be callable except in the context of Add/Remove and
		// thus we don't have to do any notifications around it.
		//

		PreDirtySetParent(newParent);
		fParentUID = newParentRef.GetUID();
		
		if (newParent != nil)
			SetRootUID(newRootUID);
		else
			SetRootUID(thisRef.GetUID());
	}
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::GetParentUID 
//----------------------------------------------------------------------------------------

UID CHierarchyNode::GetParentUID() const
{
	return fParentUID;
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::QueryRoot 
//----------------------------------------------------------------------------------------

IHierarchy *CHierarchyNode::QueryRoot() const
{
	ASSERT_MSG(fRootUID != kInvalidUID, "CHierarchyNode::QueryRoot - fRootUID != kInvalidUID");
		
	return (IHierarchy *)fChildrenUIDs->GetDataBase()->Instantiate(fRootUID, IID_IHIERARCHY);
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::GetRootUID 
//----------------------------------------------------------------------------------------

UID CHierarchyNode::GetRootUID() const
{
	return fRootUID;
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::SetRootUID ---------------------

//-------------------------------------------------------------------
void CHierarchyNode::SetRootUID(UID newRoot)
{
	ASSERT_MSG(newRoot != kInvalidUID, "CHierarchyNode::SetRootUID - newRoot != kInvalidUID");
	
	UID oldRoot = GetRootUID();

	if(fRootUID != newRoot)
	{
		PreDirtySetRootUID(newRoot);
		DetachFromRoot();
		fRootUID = newRoot;
		AttachToRoot();
	}
	
	if (oldRoot != newRoot)
	{
		for (int32 i = fChildrenUIDs->Length()-1; i >= 0; i--)
		{
			InterfacePtr<IHierarchy> child(QueryChild(i));
			if (child)
				child->SetRootUID(newRoot);
		}
	}
}



//----------------------------------------------------------------------------------------
// CHierarchyNode::Add 
//----------------------------------------------------------------------------------------

void CHierarchyNode::Add(IHierarchy *newChild, int32 pos)
{
	ASSERT_MSG(newChild != nil, "CHierarchyNode::Add - newChild != nil");
	ASSERT_MSG(pos == IHierarchy::kAtTheEnd || (pos >= 0 && pos <= fChildrenUIDs->Length()),
			 "CHierarchyNode::Add - pos == IHierarchy::kAtTheEnd || (pos >= 0 && pos <= fChildrenUIDs->Length())");
	PreDirtyAddingChild(newChild, pos);

#ifdef DEBUG
	{
		// make sure we only add spread layers to spreads
		//
		InterfacePtr<ISpread> spread(this, IID_ISPREAD);
		InterfacePtr<ISpreadLayer> spreadLayer(newChild, IID_ISPREADLAYER);
		if (spreadLayer)
			ASSERT_MSG(spread, "CHierarchyNode::Add: You should only add a SpreadLayer to a Spread or MasterPage spread");
		
		if (spread)
			ASSERT_MSG(spreadLayer, "CHierarchyNode::Add: You should only add a SpreadLayer to a Spread or MasterPage spread");

		// Make sure this UID isn't already in the tree
		// This checking failed in low memory
		InterfacePtr<IMemoryManager> memMgr(GetExecutionContextSession(), IID_IMEMORYMANAGER);
		memMgr->CheckMemory(kFalse);
	
		if(memMgr->MemoryIsLow())
		{
			ASSERT_FAIL( "CHierarchyNode::Add - Low memory. Checking for existing child skipped" ) ;
		}
		else
		{
			UIDList descendents( ::GetDataBase( this ) ) ;
			InterfacePtr<IHierarchy> rootHier ( QueryRoot() );
			rootHier->GetDescendents( &descendents, IID_IUNKNOWN ) ;
			int32 loc = descendents.Location( ::GetUID( newChild ) ) ;
			ASSERT_MSG( loc == -1, "CHierarchyNode::Add - new child already in this hierarchy" ) ;
		}
	}
#endif

	if (pos == kAtTheEnd || pos == fChildrenUIDs->Length())
		fChildrenUIDs->Append(::GetUID(newChild));
	else
		fChildrenUIDs->Insert(::GetUID(newChild), pos);
	
	InterfacePtr<IPageItemBoundsList> iBoundsList (this, IID_IPAGEITEMBOUNDSLIST);
	if ( iBoundsList )
		iBoundsList->Add (newChild, pos);
	
	InterfacePtr<IPageItemCache> iPageItemCache (this, IID_IPAGEITEMCACHE);
	if ( iPageItemCache )
		iPageItemCache->InvalidateCaches();
	
	newChild->SetParent(this);
    
    InterfacePtr<IShapeGraphixCache> shapeGraphixCache(newChild, UseDefaultIID());
    if (shapeGraphixCache)
        shapeGraphixCache->Invalidate();
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::Move 
//----------------------------------------------------------------------------------------

void CHierarchyNode::Move(IHierarchy *childToMove, int32 to)
{
	ASSERT_MSG(childToMove != nil, "CHierarchyNode::Move - childToMove != nil");
	ASSERT_MSG(to == IHierarchy::kAtTheEnd || (to >= 0 && to <= fChildrenUIDs->Length()),
			 "CHierarchyNode::Move - to == IHierarchy::kAtTheEnd || (to >= 0 && to <= fChildrenUIDs->Length())");
	
	const int32		from = GetChildIndex(childToMove);

	PreDirtyMovingChild(childToMove, from, to);

	const UIDRef	childRef(::GetUIDRef(childToMove));

	fChildrenUIDs->Remove(from);

	if (to == IHierarchy::kAtTheEnd)
		to = GetChildCount();
		
	if (to >= fChildrenUIDs->Length())
		{
		fChildrenUIDs->Append(childRef.GetUID());
		}
	else
		{
		fChildrenUIDs->Insert(childRef.GetUID(), to);
		}

	InterfacePtr<IPageItemBoundsList> iBoundsList (this, IID_IPAGEITEMBOUNDSLIST);
	if ( iBoundsList )
		iBoundsList->Move (childToMove, from, to);

	InterfacePtr<IPageItemCache> iPageItemCache (this, IID_IPAGEITEMCACHE);
	if ( iPageItemCache )
		iPageItemCache->InvalidateCaches();

	InterfacePtr<IShapeGraphixCache> shapeGraphixCache(this, UseDefaultIID());
	if (shapeGraphixCache)
		shapeGraphixCache->ChildInvalidated(childToMove);
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::Remove 
//----------------------------------------------------------------------------------------

void CHierarchyNode::Remove(IHierarchy *childToRemove)
{
	this->Remove(::GetUID(childToRemove));
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::Remove 
//----------------------------------------------------------------------------------------

void CHierarchyNode::Remove(UID childToRemove)
{
	InterfacePtr<IHierarchy> childHierarchy(fChildrenUIDs->GetDataBase(), childToRemove, IID_IHIERARCHY);

	int32 loc = fChildrenUIDs->Location(childToRemove);
	ASSERT(loc != -1);

	PreDirtyRemovingChild(childHierarchy, loc);

	if (childHierarchy)
		childHierarchy->SetParent(nil);
	
	fChildrenUIDs->Remove(loc);

	InterfacePtr<IPageItemBoundsList> iBoundsList (this, IID_IPAGEITEMBOUNDSLIST);
	if ( iBoundsList )
		iBoundsList->Remove (childHierarchy, loc);

	InterfacePtr<IPageItemCache> iPageItemCache (this, IID_IPAGEITEMCACHE);
	if ( iPageItemCache )
		iPageItemCache->InvalidateCaches();

	InterfacePtr<IShapeGraphixCache> shapeGraphixCache(this, UseDefaultIID());
	if (shapeGraphixCache)
		shapeGraphixCache->ChildInvalidated(childHierarchy);
}

//----------------------------------------------------------------------------------------
// CHierarchyNode::IsLessThan 
//----------------------------------------------------------------------------------------

bool16 CHierarchyNode::IsLessThan(IHierarchy * item)
{
	// Items compared must be in the same hierarchy
	ASSERT_MSG(GetRootUID() == item->GetRootUID(), "CHierarchyNode::IsLessThan - GetRootUID() == item->GetRootUID()");

	InterfacePtr<IHierarchy> thisParent(QueryParent());
	InterfacePtr<IHierarchy> itemParent(item->QueryParent());
	
	// Items compared must be at the same level in the hierarchy
	ASSERT_MSG(thisParent && itemParent, "CHierarchyNode::IsLessThan - thisParent && itemParent");
	
#ifdef INTERFACEPROXIES_SUPPORTED
	if (InterfaceTrackingUtils::EqualIFacePtrs(thisParent , itemParent))
#else
	if (thisParent == itemParent)
#endif
		return (thisParent->GetChildIndex(this) < itemParent->GetChildIndex(item));
	
	return (thisParent->IsLessThan(itemParent));
}




//----------------------------------------------------------------------------------------
// CHierarchyNode::GetDescendents 
//----------------------------------------------------------------------------------------

void CHierarchyNode::GetDescendents(UIDList *resultList, const PMIID& interfaceID, int32 flags) const
{
	CHierarchyNode	*ncThis = (CHierarchyNode*)this;

	int32 sz = GetChildCount();
	
	// Performance boost for complex pages
	//	reduces reallocation inside UIDList when there are lots of children
	if (sz > resultList->ChunkSize())
		resultList->Preallocate(resultList->Length() + sz);
		
	for (int32 i = 0; i < sz; i++)
	{
		InterfacePtr<const IHierarchy> itemHierarchy(ncThis->QueryChild(i));
		if (itemHierarchy)
			itemHierarchy->GetDescendents(resultList, interfaceID, flags);
	}
	
	// Add the node if it supports the interface	
	InterfacePtr<const IPMUnknown> obj(this, interfaceID);
	if (obj)	
		resultList->Append(::GetUID(ncThis));
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::GetAncestors 
//----------------------------------------------------------------------------------------

void CHierarchyNode::GetAncestors(UIDList *resultList, const PMIID& interfaceID) const
{
	CHierarchyNode	*ncThis = (CHierarchyNode*)this;

	InterfacePtr<IHierarchy> parentHierarchy(ncThis->QueryParent());
	if (parentHierarchy)
	{
		InterfacePtr<IPMUnknown> obj(parentHierarchy, interfaceID);
		if (obj)
			resultList->Append(::GetUID(obj));
		parentHierarchy->GetAncestors(resultList, interfaceID);
	}
}


//----------------------------------------------------------------------------------------
// CHierarchyNode::ReadWrite 
//----------------------------------------------------------------------------------------

void CHierarchyNode::ReadWrite(IPMStream *s, ImplementationID prop)
{
	if (s->IsReading())
		DetachFromRoot();
		
	s->XferReference(fRootUID);
	s->XferReference(fParentUID);
	
	fChildrenUIDs->ReadWrite(s, prop);
	
	if (s->IsReading())	
		AttachToRoot();
}


void CHierarchyNode::AttachToRoot()
{
}


void CHierarchyNode::DetachFromRoot()
{
}

void CHierarchyNode::PreDirtyAddingChild(IHierarchy* child, int32 pos)
{
	ASSERT(child->GetParentUID() == kInvalidUID);

	IDataBase* db = ::GetDataBase(this);
	if (db)
	{
		InterfacePtr<IM2MMessageManager> m2mmm(db, db->GetRootUID(), UseDefaultIID());
		if (m2mmm)
		{
			m2mmm->PreChangeMessage(this, IID_IHIERARCHY_CHILD);
			m2mmm->PreChangeMessageAllowDuplicate(child, IID_IHIERARCHY_ROOT);
		}
	}

	PreDirtyNoMessage();
}

void CHierarchyNode::PreDirtyMovingChild(IHierarchy* child, int32 from, int32 to)
{
	IDataBase* db = ::GetDataBase(this);
	if (db)
	{
		InterfacePtr<IM2MMessageManager> m2mmm(db, db->GetRootUID(), UseDefaultIID());
		if (m2mmm)
		{
			m2mmm->PreChangeMessage(this, IID_IHIERARCHY_CHILD_ZORDER);
			m2mmm->PreChangeMessage(child, IID_IHIERARCHY_ZORDER);
		}
	}

	PreDirtyNoMessage();
}

void CHierarchyNode::PreDirtyRemovingChild(IHierarchy* child, int32 pos)
{
	IDataBase* db = ::GetDataBase(this);
	if (db)
	{
		InterfacePtr<IM2MMessageManager> m2mmm(db, db->GetRootUID(), UseDefaultIID());
		if (m2mmm)
		{
			m2mmm->PreChangeMessage(this, IID_IHIERARCHY_CHILD);
			m2mmm->PreChangeMessageAllowDuplicate(child, IID_IHIERARCHY_ROOT);
		}
	}

	PreDirtyNoMessage();
}

UID CHierarchyNode::GetLayerUID() const
{
	InterfacePtr<const IHierarchy>pParent( ((CHierarchyNode*)this)->QueryParent() );
	return pParent ? pParent->GetLayerUID() : kInvalidUID;
}

UID CHierarchyNode::GetSpreadUID() const
{
	InterfacePtr<const IHierarchy>pRoot( ((CHierarchyNode*)this)->QueryRoot() );

#ifdef INTERFACEPROXIES_SUPPORTED
	if (InterfaceTrackingUtils::EqualIFacePtrs(this , pRoot))
#else
	if (this == pRoot)
#endif
	{
		InterfacePtr<const ISpread> spread((CHierarchyNode*)this, IID_ISPREAD);
		if (spread)
			return ::GetUID(spread);
		else
			return kInvalidUID;
	}
	else if (pRoot != nil)
		return pRoot->GetSpreadUID();
	else 
		return kInvalidUID;
}

#ifdef DEBUG

//----------------------------------------------------------------------------------------
// CHierarchyNode::IsValid 
//----------------------------------------------------------------------------------------

bool16 CHierarchyNode::IsValid()
{
	bool16 isValid = kTrue;

	// The root uid of an empty hierarchy is the item itself, so it should never be kInvalidUID
	if (fRootUID == kInvalidUID)
	{
		isValid = kFalse;
		ASSERT_FAIL("Invalid Root UID");
	}
		
	// The root node of a hierarchy is allowed to have an invalid parent, all others
	// must have valid parent UIDs.
	UID thisUID = ::GetUID(this);
	if (fRootUID != thisUID && fParentUID == kInvalidUID)
	{
		isValid = kFalse;
		ASSERT_FAIL("Invalid Parent UID");
	}

	// Check that the parent has this node as a child
	if (isValid && fParentUID != kInvalidUID)	{
		InterfacePtr<IHierarchy> parent(fChildrenUIDs->GetDataBase(), fParentUID, UseDefaultIID());
		if (parent != nil)  {
			int32 childLocation = parent->GetChildIndex(this);
			if ( childLocation < 0 ) {
				
				// Check if the parent could be a page item with multiple appearances
				InterfacePtr<IAppearanceList> appearanceList( parent, IID_IAPPEARANCELIST );
				if ( !appearanceList )
					ASSERT_FAIL("Parent does not point to child");
				}
			}
		}
	
	if (isValid)
	{
		// All children UIDs must be valid, and the child items should point back up to the parent.
		for (int32 i = fChildrenUIDs->Length() - 1; i >= 0; --i)
			if ((*fChildrenUIDs)[i] == kInvalidUID)
				{
				isValid = kFalse;
				ASSERT_FAIL("Invalid child UID");
				}
		
		for (int32 j = 0; isValid && j < fChildrenUIDs->Length(); j++)
			{
			DisableInstantiationAsserts disableAsserts;
			
			InterfacePtr<IHierarchy> child(fChildrenUIDs->GetRef(j), IID_IHIERARCHY);
			if (child) //a nil child interface probably indicates a missing plugin
			{
				if (child->GetParentUID() != thisUID)	
					{
					isValid = kFalse;
					ASSERT_FAIL("Child does not point to parent in hierarchy");
					}
				if ( !child || !child->IsValid())
					{
					isValid = kFalse;
					ASSERT_FAIL("Problem child");
					}
				}
			}
		}
		
	return isValid;
}
#endif
