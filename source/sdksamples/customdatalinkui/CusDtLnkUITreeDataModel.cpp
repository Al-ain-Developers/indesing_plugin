//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITreeDataModel.cpp $
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

// Interface includes
#include "ICusDtLnkFacade.h"
#include "ICusDtLnkDelimTextReader.h"
// Impl
#include "Utils.h"
#include "SDKFileHelper.h"
#include "StreamUtil.h"
// Project includes
#include "ICusDtLnkUITreeDataModel.h"
//#include "CusDtLnkUITreeUtils.h"
#include "CusDtLnkUITreeDataNode.h"
//#include "PlatformFileSystemIterator.h"

// Other API includes
#include "SDKFileHelper.h"


/** Implementation of ICusDtLnkUITreeDataModel

	@ingroup customdatalinkui
*/
class CusDtLnkUITreeDataModel : CPMUnknown<ICusDtLnkUITreeDataModel>
{
public:
	/**	Constructor
		@param
	 */
	CusDtLnkUITreeDataModel(IPMUnknown* boss);

	/**	Destructor
	 */
	virtual ~CusDtLnkUITreeDataModel();

	/**	See ICusDtLnkUITreeDataModel::Rebuild
	 */
	virtual void Rebuild(IWorkspace * ws) ;

	/**	See ICusDtLnkUITreeDataModel::GetWorkspace
	 */
	virtual IWorkspace* GetWorkspace() const { return fWorkspace;}

	/**	See ICusDtLnkUITreeDataModel::GetRootNodeUniqueKey
	 */
	virtual PMString GetRootNodeUniqueKey() const;

	/**See ICusDtLnkUITreeDataModel::GetRootNode
	*/
	virtual CusDtLnkUITreeDataNode* GetRootNode() const { return fRootNode;}

	/** See ICusDtLnkUITreeDataModel::GetNode
	*/
	virtual CusDtLnkUITreeDataNode* GetNode(const PMString& uniqueKey) const;

	/**	See ICusDtLnkUITreeDataModel::GetParentPath
	*/
	virtual PMString GetParentPath(const PMString& path) const;

	/**	See ICusDtLnkUITreeDataModel::GetChildCount
	*/
	virtual int32 GetChildCount(const PMString& path); 

	/**	See ICusDtLnkUITreeDataModel::GetNthChildPath
	*/
	virtual PMString GetNthChildPath(const PMString& path, int32 nth); 

	/**	See ICusDtLnkUITreeDataModel::GetChildIndexFor
	*/
	virtual int32 GetChildIndexFor(const PMString& par, const PMString& kid); 


protected:

	/** Cache the kids of the given node
	*/
	void cacheChildren(const PMString& path);

	/** Calculate the asset-nodes that should be parented by given database-node
		@param parentingNode database-node
	*/
	void calculateDataBaseChildren(CusDtLnkUITreeDataNode* parentingNode);

	/**	Destroy the tree represented in this 
	 */
	void deleteTree() ;


private:
	
	std::map<PMString, CusDtLnkUITreeDataNode* > fPathNodeMap;
	CusDtLnkUITreeDataNode* fRootNode;
    IWorkspace *fWorkspace;

	static const PMString k_FixedRootNodePath;
};

const PMString CusDtLnkUITreeDataModel::k_FixedRootNodePath("ROOTNODE/");
	
/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUITreeDataModel, kCusDtLnkUITreeDataModelImpl)

/* 
*/
CusDtLnkUITreeDataModel::CusDtLnkUITreeDataModel(IPMUnknown* boss) : 
	CPMUnknown<ICusDtLnkUITreeDataModel>(boss),
		fRootNode(nil), fWorkspace(nil)
{
}



	
/* 
*/
CusDtLnkUITreeDataModel::~CusDtLnkUITreeDataModel()
{
	deleteTree();
}


/* 
*/
void CusDtLnkUITreeDataModel::deleteTree() 
{
	// We've flattened the tree in our hashtable anyway so 
	// use this to delete the nodes.
	std::map<PMString, CusDtLnkUITreeDataNode* >::iterator iter;
	for(iter = fPathNodeMap.begin(); iter != fPathNodeMap.end(); iter++)
	{
		CusDtLnkUITreeDataNode* node = iter->second;
		ASSERT(node);
		delete node;
	}
	fPathNodeMap.clear();
	fRootNode = nil;
	fWorkspace = nil;
}


/*
*/
void CusDtLnkUITreeDataModel::Rebuild(IWorkspace * ws) 
{
	if(fRootNode != nil) {
		deleteTree();
	}
	fWorkspace = ws;
	fRootNode =  new CusDtLnkUITreeDataNode();
	ASSERT(fRootNode);
	fRootNode->SetUniqueKey(k_FixedRootNodePath);
	fRootNode->SetNodeType(CusDtLnkUITreeDataNode::eRootType);
	fPathNodeMap.insert( std::pair<PMString, CusDtLnkUITreeDataNode* >(k_FixedRootNodePath, fRootNode));
	this->calculateDataBaseChildren(fRootNode);

}


/* 
*/
PMString  CusDtLnkUITreeDataModel::GetParentPath(const PMString& path) const
{
	PMString retval;
	do {

		// We assume that the parent is cached, because we
		// found its kids
		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator result = fPathNodeMap.find(path);
		if(result != fPathNodeMap.end()) {
			CusDtLnkUITreeDataNode* node = result->second;
			ASSERT(node);
			ASSERT(fRootNode);
			// Use the comparison we've defined on the node class
			if((*node) == (*fRootNode)) {
				// Root by our definition has no parent
				break;
			}
			retval =  node->GetParent()->GetUniqueKey();
			break;
		}
		
	} while(kFalse);
	return retval;
}


CusDtLnkUITreeDataNode* CusDtLnkUITreeDataModel::GetNode(const PMString& uniqueKey) const
{
	CusDtLnkUITreeDataNode* retval = nil;

	std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator result = fPathNodeMap.find(uniqueKey);
	if(result != fPathNodeMap.end()) {
		retval = result->second;
	}
	return retval;
}


/* 
*/
int32 CusDtLnkUITreeDataModel::GetChildCount(const PMString& path) // not const any more
{
	int32 retval = 0;
	do {
		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator result = fPathNodeMap.find(path);
		if(result != fPathNodeMap.end()) {
			int32 possChildCount = result->second->ChildCount();
			if(possChildCount > 0) {
				// Don't trust a zero value, it may just be we didn't yet cache the kids
				retval = possChildCount;
				break;
			}
		}
		// So, we may not have cached the kids.
		this->cacheChildren(path);
		// Don't recurse, as we may have no kids and we only want one try
		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator postCacheResult = fPathNodeMap.find(path);
		if(postCacheResult != fPathNodeMap.end()) {
			retval = postCacheResult->second->ChildCount();
			break;
		}
	} while(kFalse);
	return retval;
}

/* 
*/
PMString CusDtLnkUITreeDataModel::GetNthChildPath(
	const PMString& path, int32 nth) // not const any more
{
	PMString retval;
	do {

		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator result = fPathNodeMap.find(path);
		if(result != fPathNodeMap.end()) {
			int32 possChildCount = result->second->ChildCount();
			if(possChildCount > 0) {
				// Again, distrust a node with zero child count, may be kids not yet cached 
				retval = result->second->GetNthChild(nth).GetUniqueKey();
				break;
			}
		}
		// Again, we may not have cached the kids.
		this->cacheChildren(path);
		// Don't recurse, as we may have no kids and we only want one try
		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator postCacheResult = fPathNodeMap.find(path);
		if(postCacheResult != fPathNodeMap.end()) {
			retval = postCacheResult->second->GetNthChild(nth).GetUniqueKey();
			break;
		}
	} while(kFalse);

	return retval;
}

/* 
*/
int32  CusDtLnkUITreeDataModel::GetChildIndexFor(
	const PMString& par, const PMString& kid) //const
{
	// Can we be called here without the kids being already cached?
	int32 retval=(-1);
	std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator result = fPathNodeMap.find(par);
	if(result != fPathNodeMap.end()) {
		CusDtLnkUITreeDataNode* node = result->second;
		if(node->ChildCount() == 0) {
			// Try to cache the kids, we may not have done so
			this->cacheChildren(par);
		}
		for(int32 i=0; i < node->ChildCount(); i++){
			PMString kidPath = node->GetNthChild(i).GetUniqueKey();
			if(kid == kidPath) {
				retval=i;
				break;
			}
		}
	}
	
	return retval;
}


/* 
*/
PMString CusDtLnkUITreeDataModel::GetRootNodeUniqueKey() const
{
	PMString retval;
	
	if(fRootNode != nil) {
		retval = fRootNode->GetUniqueKey();
	}
	return retval;
}


/*
*/
void CusDtLnkUITreeDataModel::calculateDataBaseChildren(CusDtLnkUITreeDataNode* parentingNode)
{
	do {
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		ASSERT(parentingNode);
		if(!parentingNode) {
			break;
		}
		int32 dbCount = facade->GetAssetDataBaseCount(fWorkspace);
		for(int32 i=0; i < dbCount; i++) {

			PMString dbName = facade->GetNthAssetDataBase(fWorkspace, i);
			if(dbName.empty()) {
				continue;
			}
			PMString path = facade->GetAssetDataBasePath(fWorkspace, dbName);
			CusDtLnkUITreeDataNode* newNode = new CusDtLnkUITreeDataNode();
			newNode->SetUniqueKey(path);
			newNode->SetParent(parentingNode);
			newNode->SetNodeType(CusDtLnkUITreeDataNode::eDataBaseType);
			parentingNode->AddChild(
				static_cast<const CusDtLnkUITreeDataNode& >(*newNode));
			fPathNodeMap.insert( std::pair<PMString, 
				CusDtLnkUITreeDataNode* >(path, newNode));
		} // i loop

	} while(kFalse);
}
/*
*/
void CusDtLnkUITreeDataModel::cacheChildren(const PMString& parentPath)
{
	
	do
	{	
		CusDtLnkUITreeDataNode* parentingNode = nil;
		std::map<PMString, CusDtLnkUITreeDataNode* >::const_iterator iterForParent = fPathNodeMap.find(parentPath);
		if(iterForParent == fPathNodeMap.end()) {
			break;
		}
		parentingNode = iterForParent->second;
		ASSERT(parentingNode);
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		switch(parentingNode->GetNodeType()) {

			case CusDtLnkUITreeDataNode::eAssetType:
				{
					// It's an asset, so the parent node
					// should have a chunk of data
					//
					// Let's create one child for each value

					for(int32 i=0; i < parentingNode->GetAssetRecordFieldCount(); i++) {
						PMString valueUniqueKey(parentingNode->GetUniqueKey());
						PMString key = parentingNode->GetNthAssetRecordFieldName(i);
						PMString val = parentingNode->GetAssetRecordFieldValue(key);
						// Truncate only on /, not : or other seps
						PMString truncVal = 
							facade->TruncatePath(val, kFalse, kTextChar_Solidus);

						valueUniqueKey += "/";
						valueUniqueKey += key;
						valueUniqueKey += "=";
						valueUniqueKey += truncVal;

						CusDtLnkUITreeDataNode* newValueNode = new CusDtLnkUITreeDataNode();
						newValueNode->SetUniqueKey(valueUniqueKey);
						newValueNode->SetParent(parentingNode);
						newValueNode->SetAssetDataBasePath(parentingNode->GetAssetDataBasePath());
						newValueNode->SetNodeType(CusDtLnkUITreeDataNode::eValueType);
						parentingNode->AddChild(
							static_cast<const CusDtLnkUITreeDataNode& >(*newValueNode));
						fPathNodeMap.insert( 
							std::pair<PMString, CusDtLnkUITreeDataNode* >(
								valueUniqueKey, newValueNode));
						
					}
				}
				break;


			case CusDtLnkUITreeDataNode::eDataBaseType:
				{
					// It's a database, so load the database
					// and make nodes from each asset we find in it
					InterfacePtr<ICusDtLnkDelimTextReader> reader(CreateObject2<ICusDtLnkDelimTextReader>(kCusDtLnkDelimTextReaderBoss));
					ASSERT(reader);
					if(!reader) {
						break;
					}

					// Open stream onto database path
					PMString pathToOpen = parentingNode->GetUniqueKey();
					SDKFileHelper fileHelper(pathToOpen);
					//ASSERT(fileHelper.IsExisting());
					if(!fileHelper.IsExisting()) {
						break;
					}
					
					InterfacePtr<IPMStream> stream( StreamUtil::CreateFileStreamRead(fileHelper.GetIDFile()));
					ASSERT(stream);
					if(!stream) {
						break;
					}
					if(!reader->CanRead(stream)) {
						stream->Close();
						break;
					}
					K2Vector<PMString> names;
					bool16 couldReadNames = reader->ReadRecord(stream, names);
					ASSERT(couldReadNames);
					if(!couldReadNames) {
						stream->Close();
						break;
					}
					ASSERT(names.size()>0);

					if(names.size() == 0) {
						stream->Close();
						break;
					}
					
					PMString truncatedDBPath = Utils<ICusDtLnkFacade>()->TruncatePath(pathToOpen);
				
					while (stream->GetStreamState() == kStreamStateGood) {
						K2Vector<PMString> fields;
						bool16 couldReadRec = reader->ReadRecord(stream, fields);
						bool16 foundDataOnThisRow = (couldReadRec && fields.size()>1);
						if(!foundDataOnThisRow) {
							continue;
						}
						// TODO you can't guarantee this, maybe
						// try to use the fieldname? we're using the fieldname
						// later, so lets use it here too
						PMString recordIdentifier = fields[0];
					
						// Make unique key from databasename / record-id
						PMString uniqueKey(truncatedDBPath);
						uniqueKey += "/";
						uniqueKey += recordIdentifier;

						CusDtLnkUITreeDataNode* newNode = new CusDtLnkUITreeDataNode();
						newNode->SetUniqueKey(uniqueKey);
						newNode->SetParent(parentingNode);
						newNode->SetAssetDataBasePath(pathToOpen);
						newNode->SetNodeType(CusDtLnkUITreeDataNode::eAssetType);
						parentingNode->AddChild(
							static_cast<const CusDtLnkUITreeDataNode& >(*newNode));
						fPathNodeMap.insert( 
							std::pair<PMString, CusDtLnkUITreeDataNode* >(
								uniqueKey, newNode));
						// Now add each field
						K2Vector<PMString>::const_iterator iterNames = names.begin();
						K2Vector<PMString>::const_iterator iterVals = fields.begin();
						for( ; iterNames != names.end() && iterVals != fields.end();
								iterNames++, iterVals++) {
							PMString name = *iterNames;
							PMString val = *iterVals;
							newNode->AddAssetRecordValue(name,val);
						}
						
					} // while stream good

					// Tidy up stream
					stream->Close();

				} //parent was database
				break;

		} // switch

	} while(kFalse);
	
}


//	end, File: CusDtLnkUITreeDataModel.cpp
