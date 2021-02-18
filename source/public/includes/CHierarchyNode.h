//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CHierarchyNode.h $
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

#pragma once
#ifndef __CHIERARCHYNODE__
#define __CHIERARCHYNODE__

#include "IHierarchy.h"

#ifndef __PTRCOLLECTION__
#include "K2Vector.h"
#endif

#include "HelperInterface.h"

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class PersistUIDList;

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
#pragma export on

class PUBLIC_DECL CHierarchyNode : public IHierarchy
{
public:
	CHierarchyNode(IPMUnknown *boss);
	virtual ~CHierarchyNode();
	
	virtual IHierarchy *QueryChild(int32 n) const;
	virtual UID GetChildUID(int32 n) const;
	virtual int32 GetChildIndex(const IHierarchy * p) const;
	virtual int32 GetChildCount() const;
	virtual IHierarchy *QueryParent() const;
	virtual void SetParent(IHierarchy *newParent);
	virtual UID GetParentUID() const;
	virtual IHierarchy *QueryRoot() const;
	virtual UID GetRootUID() const;
	virtual void SetRootUID(UID newRoot);
	virtual void Add(IHierarchy *newChild, int32 pos);
	virtual void Move(IHierarchy *childToMove, int32 to);
	virtual void Remove(IHierarchy *childToRemove);
	virtual void Remove(UID childToRemove);

	virtual bool16 IsLessThan(IHierarchy * item);
	virtual void GetDescendents(UIDList *resultList, const PMIID& interfaceID, int32 flags = 0) const;
	virtual void GetAncestors(UIDList *resultList, const PMIID& interfaceID) const;
	virtual UID GetLayerUID() const;
	virtual UID GetSpreadUID() const;

	void ReadWrite(IPMStream *s, ImplementationID prop);	

#ifdef DEBUG
		virtual bool16 IsValid();
			// Checks that all internally held pointers and UIDs are reasonable
			// AND calls IsValid() for all children.
#endif

protected:
	void AttachToRoot();
	void DetachFromRoot();

	virtual void PreDirtySetParent(IHierarchy*)
		{ PreDirtyNoMessage(); }
	virtual void PreDirtySetRootUID(UID)
		{ PreDirtyNoMessage(); }
	virtual void PreDirtyAddingChild(IHierarchy* child, int32 pos);
	virtual void PreDirtyMovingChild(IHierarchy* child, int32 from, int32 to);
	virtual void PreDirtyRemovingChild(IHierarchy* child, int32 pos);

	UID fRootUID;
	UID fParentUID;	
	PersistUIDList* fChildrenUIDs;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
