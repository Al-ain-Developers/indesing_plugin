//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUITVHierarchyAdapter.cpp $
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

#include "IActiveContext.h"
#include "IDataBase.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ISelectionUtils.h"
#include "ILayoutUIUtils.h"
#include "IDocument.h"

#include "IPstLstData.h"
#include "PstLstUIUtils.h"
#include "IPstLstSuite.h"
#include "IPstLstUIDList.h"
#include "FileUtils.h"

#include "PstLstUINodeID.h"
#include "PstLstUIID.h"


/** Tree view adapter
	@ingroup persistentlist
	
*/
//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter
//----------------------------------------------------------------------------------------
class PstLstUITVHierarchyAdapter : public ITreeViewHierarchyAdapter
{
public:
	PstLstUITVHierarchyAdapter(IPMUnknown *boss);
	~PstLstUITVHierarchyAdapter();
	
	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual bool16				ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

	virtual	NodeID_rv 		GetGenericNodeID() const;
private:
		IDataBase*		GetDataBase() const;

DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(PstLstUITVHierarchyAdapter, kPstLstUITVHierarchyAdapterImpl)
DEFINE_HELPER_METHODS(PstLstUITVHierarchyAdapter)

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter constructor
//----------------------------------------------------------------------------------------
PstLstUITVHierarchyAdapter::PstLstUITVHierarchyAdapter(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}


//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::~PstLstUITVHierarchyAdapter 
//----------------------------------------------------------------------------------------
PstLstUITVHierarchyAdapter::~PstLstUITVHierarchyAdapter()
{
}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv PstLstUITVHierarchyAdapter::GetRootNode() const
{
	IDataBase * db = this->GetDataBase();
	if (db)
	{ // The following code is trying to get unique string for rootNode with different documents
        const IDFile * dbFile = db->GetSysFile();
        const IDFile* fromOpenFile = db->GetSysFileFromOpen();
        IDFile sysFile;
        if ( dbFile )
            sysFile = IDFile(*dbFile);
        else if ( fromOpenFile )
            sysFile = IDFile(*fromOpenFile);

		PMString rootString = FileUtils::SysFileToPMString(sysFile);
		return PstLstUINodeID::Create(PstLstUINodeID::kInvalidData, kInvalidUID,rootString);
	}

	return kInvalidNodeID;
}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv PstLstUITVHierarchyAdapter::GetParentNode(const NodeID& node) const
{	
	TreeNodePtr<PstLstUINodeID>	pstListNode(node);
	if (pstListNode)
	{
		if ( pstListNode->GetDataType() == PstLstUINodeID::kPersistentListType)
		{
			// This is a level 2 node representing a persistent data 
			InterfacePtr<IPstLstData>	iPstLstData(this->GetDataBase(), pstListNode->GetUID(),UseDefaultIID());
			UID parentUID = iPstLstData->GetParent();
			return PstLstUINodeID::Create(PstLstUINodeID::kPageItemType, parentUID, PMString(""));
		}
		else if ( pstListNode->GetDataType() == PstLstUINodeID::kPageItemType)

			// This is a level 1 node representing selected page items			
			return this->GetRootNode();
	}
			
	return kInvalidNodeID;
}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 PstLstUITVHierarchyAdapter::GetNumChildren(const NodeID& node) const
{
	if (node.IsValid())
	{
		TreeNodePtr<PstLstUINodeID>	pstListNode(node);
		if (pstListNode->GetDataType() == PstLstUINodeID::kInvalidData)
		{
			//Root, see how many selected page items
			InterfacePtr<IPstLstSuite>	iPstLstSuite(static_cast<IPstLstSuite*>(Utils<ISelectionUtils>()->QuerySuite(IPstLstSuite::kDefaultIID)));
			int32 count = 0;
			if (iPstLstSuite)
				iPstLstSuite->GetNumDrawablePageItemSelected(count);
			return count;
		}
		else if (pstListNode->GetDataType() == PstLstUINodeID::kPageItemType)
		{
			InterfacePtr<IPstLstUIDList> iUIDList(this->GetDataBase(), pstListNode->GetUID(), UseDefaultIID());
			if (iUIDList && iUIDList->GetUIDList())
			{
				return iUIDList->GetUIDList()->Length();
			}
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetNthChild
//----------------------------------------------------------------------------------------
NodeID_rv PstLstUITVHierarchyAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	TreeNodePtr<PstLstUINodeID>	pstListNode(node);
	if ( pstListNode->GetDataType() == PstLstUINodeID::kInvalidData)
	{
		//Root, see how many selected page items
		InterfacePtr<IPstLstSuite>	iPstLstSuite(static_cast<IPstLstSuite*>(Utils<ISelectionUtils>()->QuerySuite(IPstLstSuite::kDefaultIID)));
		UIDRef item;
		if (iPstLstSuite)
		{
			iPstLstSuite->GetNthSelectedDrawablePageItem(nth, item);
			UID nthPageItem = item.GetUID();
			return PstLstUINodeID::Create(PstLstUINodeID::kPageItemType, nthPageItem, PMString(""));
		}
	}
	else if ( pstListNode->GetDataType() == PstLstUINodeID::kPageItemType)
	{
		InterfacePtr<IPstLstUIDList> iUIDList(this->GetDataBase(), pstListNode->GetUID(),UseDefaultIID());
		InterfacePtr<IPstLstData>	iPstLstData(iUIDList->GetRef(nth), UseDefaultIID());
		return PstLstUINodeID::Create(PstLstUINodeID::kPersistentListType, iUIDList->GetRef(nth).GetUID(), iPstLstData->GetName());
	}

	return kInvalidNodeID;
}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 PstLstUITVHierarchyAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<PstLstUINodeID>	parentNode(parent);
	TreeNodePtr<PstLstUINodeID>	childNode(child);
	UID parentUID = parentNode->GetUID();
	UID childUID = childNode->GetUID();

	if ( parentNode->GetDataType() == PstLstUINodeID::kInvalidData)
	{
		InterfacePtr<IPstLstSuite>	iPstLstSuite(static_cast<IPstLstSuite*>(Utils<ISelectionUtils>()->QuerySuite(IPstLstSuite::kDefaultIID)));
		int32 numSelections = 0;
		if (iPstLstSuite)
		{
			iPstLstSuite->GetNumDrawablePageItemSelected(numSelections);
			for (int32 i = 0; i < numSelections; i++)
			{
				UIDRef item;
				iPstLstSuite->GetNthSelectedDrawablePageItem(i, item);
				if ( childUID == item.GetUID())
					return i;
			}
		}
	}
	else if ( parentNode->GetDataType() == PstLstUINodeID::kPageItemType)
	{
		InterfacePtr<IPstLstUIDList> iUIDList(this->GetDataBase(), parentUID,UseDefaultIID());
		int32 numSelections = iUIDList->GetUIDList()->Length();
		for (int32 i = 0; i < numSelections; i++)
		{
			if ( childUID == iUIDList->GetRef(i).GetUID())
				return i;
		}
	}

	return 0; // if the parent is the leaf

}

//----------------------------------------------------------------------------------------
// PstLstUITVHierarchyAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv PstLstUITVHierarchyAdapter::GetGenericNodeID() const
{
	return PstLstUINodeID::Create(PstLstUINodeID::kInvalidData, kInvalidUID,"");	// just a dummy node
}


IDataBase* PstLstUITVHierarchyAdapter::GetDataBase() const
{
	IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
	return ::GetDataBase(document);
}
