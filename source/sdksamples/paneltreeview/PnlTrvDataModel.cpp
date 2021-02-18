//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvDataModel.cpp $
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

// Impl includes
#include <map>
#include "SDKFileHelper.h"
#include "IPnlTrvDataModel.h"
#include "PnlTrvUtils.h"
#include "PnlTrvDataNode.h"
#include "PlatformFolderTraverser.h"
#include "FileUtils.h"

/**  Class representing a folder hierarchy. 
	@ingroup paneltreeview
*/
class PnlTrvDataModel : CPMUnknown<IPnlTrvDataModel>
{
public:
	/** Default constructor */
	PnlTrvDataModel(IPMUnknown* boss);

	/**	Destructor
	 */
	virtual ~PnlTrvDataModel();

	/**		See IPnlTrvDataModel::GetRootPath 
	*/
	virtual PMString GetRootPath() const;

	/** 	See IPnlTrvDataModel::GetNode
	*/
	virtual PnlTrvDataNode* GetNode(const PMString& path) const;

	/**		See IPnlTrvDataModel::GetParentPath
	 */
	virtual PMString GetParentPath(const PMString& path) const;

	/**		See IPnlTrvDataModel::GetChildCount
	 */
	virtual int32 GetChildCount(const PMString& path); 

	/**		See IPnlTrvDataModel::GetNthChildPath
	 */
	virtual PMString GetNthChildPath(const PMString& path, int32 nth); 

	/**		See IPnlTrvDataModel::GetChildIndexFor 
	 */
	virtual int32 GetChildIndexFor(const PMString& par, const PMString& kid); 

	/**	See IPnlTrvDataModel::Rebuild
	 */
	virtual void Rebuild(const PMString& rootPath);

protected:
	/** Cache the kids of the given node in file system
	*/
	void cacheChildren(const PMString& path);

	
	/**	Determine if this is a path that we want to put in the data model
		@param p [IN] specifies path of interest
		@return bool16 if the path is a file system path of interest
	 */
	bool16 validPath(const PMString& p);

	/**	Destroy the tree represented in this 
	 */
	void deleteTree() ;

private:
	std::map<PMString, PnlTrvDataNode* > fPathNodeMap;
	PnlTrvDataNode* fRootNode;
};

CREATE_PMINTERFACE(PnlTrvDataModel, kPnlTrvDataModelImpl)

/* Constructor
*/
PnlTrvDataModel::PnlTrvDataModel(IPMUnknown* boss) : 
	CPMUnknown<IPnlTrvDataModel>(boss),
	fRootNode(nil)
{
}
	
/* Destructor
*/
PnlTrvDataModel::~PnlTrvDataModel()
{
	deleteTree();
}

/* deleteTree
*/
void PnlTrvDataModel::deleteTree() 
{
	// We've flattened the tree in our hashtable anyway so 
	// use this to delete the nodes.
	std::map<PMString, PnlTrvDataNode* >::iterator iter;
	for(iter = fPathNodeMap.begin(); iter != fPathNodeMap.end(); iter++)
	{
		PnlTrvDataNode* node = iter->second;
		ASSERT(node);
		delete node;
	}
	fPathNodeMap.clear();
	fRootNode = nil;
}

/* Rebuild
*/
void PnlTrvDataModel::Rebuild(const PMString& path)
{
	if(fRootNode != nil) {
		deleteTree();
	}
	if(path.empty() == kFalse) {
		fRootNode =  new PnlTrvDataNode();
		fRootNode->SetData(path);
		fPathNodeMap.insert( std::pair<PMString, PnlTrvDataNode* >(path, fRootNode));
		this->cacheChildren(path);
	}
}

/* GetParentPath
*/
PMString  PnlTrvDataModel::GetParentPath(const PMString& path) const
{
	// We assume that the parent is cached, because we
	// found its kids
	std::map<PMString, PnlTrvDataNode* >::const_iterator result = fPathNodeMap.find(path);
	if(result != fPathNodeMap.end())
	{
		PnlTrvDataNode* node = result->second;
		ASSERT(node);
		ASSERT(fRootNode);
		// Use the comparison we've defined on the node class
		if((*node) == (*fRootNode))
		{
			return PMString();
		}
		return node->GetParent()->GetData();
	}
	return PMString();
}

/* GetChildCount
*/
int32 PnlTrvDataModel::GetChildCount(const PMString& path) // not const any more
{
	std::map<PMString, PnlTrvDataNode* >::const_iterator result = fPathNodeMap.find(path);
	if (result != fPathNodeMap.end())
    {
		int32 possChildCount = result->second->ChildCount();
		if(possChildCount > 0) {
			// Don't trust a zero value, it may just be we didn't yet cache the kids
			return possChildCount;
		}
	}
    
	// So, we may not have cached the kids.
	this->cacheChildren(path);
    
	// Don't recurse, as we may have no kids and we only want one try
	std::map<PMString, PnlTrvDataNode* >::const_iterator postCacheResult = fPathNodeMap.find(path);
	if (postCacheResult != fPathNodeMap.end())
    {
		return postCacheResult->second->ChildCount();
	}
	return 0;
}

/* GetNthChildPath
*/
PMString PnlTrvDataModel::GetNthChildPath(
	const PMString& path, int32 nth) // not const any more
{
	std::map<PMString, PnlTrvDataNode* >::const_iterator result = fPathNodeMap.find(path);
	if(result != fPathNodeMap.end())
    {
		int32 possChildCount = result->second->ChildCount();
		if(possChildCount > 0)
        {
			// Again, distrust a node with zero child count, may be kids not yet cached 
			return result->second->GetNthChild(nth).GetData();
		}
	}
    
	// Again, we may not have cached the kids.
	this->cacheChildren(path);
    
	// Don't recurse, as we may have no kids and we only want one try
	std::map<PMString, PnlTrvDataNode* >::const_iterator postCacheResult = fPathNodeMap.find(path);
	if(postCacheResult != fPathNodeMap.end())
    {
		return postCacheResult->second->GetNthChild(nth).GetData();
	}

	return PMString();
}

/* GetChildIndexFor
 */
int32  PnlTrvDataModel::GetChildIndexFor(const PMString& par, const PMString& kid)
{
	// Can we be called here without the kids being already cached?
	int32 retval=(-1);
	std::map<PMString, PnlTrvDataNode* >::const_iterator result = fPathNodeMap.find(par);
	if(result != fPathNodeMap.end())
    {
		PnlTrvDataNode* node = result->second;
		if(node->ChildCount() == 0)
        {
			// Try to cache the kids, we may not have done so
			this->cacheChildren(par);
		}
        
		for(int32 i=0; i < node->ChildCount(); i++){
			PMString kidPath = node->GetNthChild(i).GetData();
			if(kid == kidPath) {
				retval=i;
				break;
			}
		}
	}
	
	return retval;
}

/* GetRootPath
*/
PMString PnlTrvDataModel::GetRootPath() const
{
	if (fRootNode != nil)
	{
		return fRootNode->GetData();
	}
	return PMString();
}

PnlTrvDataNode* PnlTrvDataModel::GetNode(const PMString& path) const
{
	PnlTrvDataNode* retval = nil;

	std::map<PMString, PnlTrvDataNode* >::const_iterator result = fPathNodeMap.find(path);
	if(result != fPathNodeMap.end()) {
		retval = result->second;
	}
	return retval;
}

/* validPath
*/
bool16 PnlTrvDataModel::validPath(const PMString& p)
{
	const PMString thisDir(".");
	const PMString parentDir("..");
	return p != thisDir && p != parentDir;
}

void PnlTrvDataModel::cacheChildren(const PMString& parentPath)
{
	do
	{	
		PnlTrvDataNode* parentNode = nil;
		std::map<PMString, PnlTrvDataNode* >::const_iterator iterForParent = fPathNodeMap.find(parentPath);
		if(iterForParent == fPathNodeMap.end())
        {
            break;
		}
		parentNode = iterForParent->second;
		ASSERT(parentNode);

		SDKFileHelper parentFileHelper(parentPath);
		IDFile parIDFile = parentFileHelper.GetIDFile();
        
		PlatformFolderTraverser folderTraverser(parIDFile, kFalse, kTrue, kFalse, kTrue);
        IDFile sysfile;
		while (folderTraverser.Next(&sysfile))
		{
            PMString extension;
            FileUtils::GetExtension(sysfile, extension);
            if (extension == PMString("DS_Store"))
            {
                continue;
            }
            
            SDKFileHelper fileHelper(sysfile);
            
			// Insert will fail if the item is there already...
			// so look to see if we have a node already and erase if we have
			std::map<PMString, PnlTrvDataNode* >::iterator existingIter = fPathNodeMap.find(fileHelper.GetPath());
			if (existingIter != fPathNodeMap.end())
            {
				// See Docs on UniqueAssociativeContainer and look at insert semantics
				// http://www.sgi.com/tech/stl/UniqueAssociativeContainer.html
				PnlTrvDataNode* existingNodeBeingReplaced = existingIter->second;
				delete existingNodeBeingReplaced;
				fPathNodeMap.erase(existingIter);
			}
			
			PMString truncP = sysfile.GetFileName();
			if (validPath(truncP))
			{
				PnlTrvDataNode* newNode = new PnlTrvDataNode();
				newNode->SetData(fileHelper.GetPath());
				newNode->SetParent(parentNode);
				parentNode->AddChild(static_cast<const PnlTrvDataNode& >(*newNode));
                
				fPathNodeMap.insert( std::pair<PMString, PnlTrvDataNode* >(fileHelper.GetPath(), newNode));
			}
		}
	} while (kFalse);
}
