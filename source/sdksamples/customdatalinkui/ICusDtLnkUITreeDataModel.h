//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/ICusDtLnkUITreeDataModel.h $
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

#ifndef __ICusDtLnkUITreeDataModel_H_DEFINED__
#define __ICusDtLnkUITreeDataModel_H_DEFINED__

#include "IPMUnknown.h"
#include "CusDtLnkUIID.h"

class CusDtLnkUITreeDataNode;
class IWorkspace;

/**  From SDK sample; interface to data model
	representing tree of assets, with database files as child of root, and
	assets as child nodes of those.
	@ingroup customdatalinkui
*/
class ICusDtLnkUITreeDataModel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICUSDTLNKUITREEDATAMODEL };
	
	/**	Call to explicitly rebuild the model
	 */
	virtual void Rebuild(IWorkspace * ws)=0;

	/**	Access current workspace
		@return IWorkspace* current workspace
	 */
	virtual IWorkspace* GetWorkspace() const =0;

	/**	Accessor for the root path
		@return PMString giving the path associated with the root node
	 */
	virtual PMString GetRootNodeUniqueKey() const=0;

	/**	Accessor for the root node
		@return CusDtLnkUITreeDataNode* root node reference
	 */
	virtual CusDtLnkUITreeDataNode* GetRootNode() const=0;

	/** Accessor for arbitrary node by unique key
		@param [IN] uniqueKey
		@return CusDtLnkUITreeDataNode* for node with given unique key, nil if it couldn't be found
	*/
	virtual CusDtLnkUITreeDataNode* GetNode(const PMString& uniqueKey) const = 0;

	/**	Given a path, discover the path of its parent
		@param path [IN] specifies given path
		@return Returns path as string
	 */
	virtual PMString GetParentPath(const PMString& path) const=0;

	/**	Determine the number of children given a path
		@param path [IN] specifies given path
		@return Returns number of children
	 */
	virtual int32 GetChildCount(const PMString& path)=0; 

	/**	Get the path associated with the specified child
		@param path [IN] specifies given path
		@param nth [IN] specifies which child
		@return Returns path as string
	 */
	virtual PMString GetNthChildPath(const PMString& path, int32 nth)=0; 

	/**	Determine the index in the parent's list of kids for 
		a particular child
		@param par [IN] specifies parent
		@param kid [IN] specifies kid
		@return Returns index 
	 */
	virtual int32 GetChildIndexFor(const PMString& par, const PMString& kid)=0; 

};


#endif // __ICusDtLnkUITreeDataModel_H_DEFINED__

