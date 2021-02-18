//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITreeDataNode.h $
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

#ifndef __CusDtLnkUITreeDataNode_H_DEFINED__
#define __CusDtLnkUITreeDataNode_H_DEFINED__

#include <map>
/** Class to represent a generic node within a tree, with data
	that is encapsulated in a PMString.

	
	@ingroup customdatalinkui
*/

class CusDtLnkUITreeDataNode
{
public:
	enum TreeDataNodeType { eRootType, eDataBaseType, eAssetType, eValueType } ;
	enum AssetState { eStatePlaceholder, eStateProvisional, eStateFinal }; 
	/** Constructor */
	CusDtLnkUITreeDataNode();

	/** Destructor */
	virtual ~CusDtLnkUITreeDataNode();

	// +K2Vector support

	/**	Copy constructor
		@param rhs [IN] node reference
		@return  
	 */
	CusDtLnkUITreeDataNode(const CusDtLnkUITreeDataNode& rhs);

	/**	Operator assignment
		@param rhs [IN] node reference
		@return CusDtLnkUITreeDataNode& 
	 */
	CusDtLnkUITreeDataNode& operator=(const CusDtLnkUITreeDataNode& rhs);

	/** For K2Vector copy semantics
	*/
	typedef object_type data_type;
	// -K2Vector support

	/**	Operator equality
		@param rhs [IN] node reference
		@return bool 
	 */
	bool operator==(const CusDtLnkUITreeDataNode& rhs) const;


	/**	Accessor for child by zerobased index in parent's list of kids
		@param indexInParent [IN] which child by zero-based index
		@return child at given index 
	 */
	const CusDtLnkUITreeDataNode& GetNthChild(int32 indexInParent) const;

	/**	Accessor for parent
		@return reference to parent node
	 */
	CusDtLnkUITreeDataNode* GetParent() const;

	/**	Accessor for size of child list on this node
		@return int32 giving the number of children on this node 
	 */
	int32 ChildCount() const;

	/**	@return 
	 */
	PMString GetUniqueKey() const;

	TreeDataNodeType GetNodeType() const ;

	void SetNodeType(TreeDataNodeType typ);

	/**	Add child to this node (at end of list)
		@param o [IN] child node to add
	 */
	void AddChild(const CusDtLnkUITreeDataNode& o);

	/**	Remove specified child from our list
		@param o [IN] specifies child to remove
	 */
	void RemoveChild(const CusDtLnkUITreeDataNode& o);

	/** Mutator for the parent of this node
		@param p [IN] specifies new parent to set
	 */
	void SetParent(const CusDtLnkUITreeDataNode* p);

	/**	
		@param uk
	 */
	void SetUniqueKey(const PMString& uk);

	URI GetURIFromNode() const;


	void SetAssetDataBasePath(const PMString& dbPath);

	PMString GetAssetDataBasePath() const;

	
	void AddAssetRecordValue(const PMString& name, const PMString& val);

	int32 GetAssetRecordFieldCount() const;
	PMString GetNthAssetRecordFieldName(int32 index) const;
	PMString GetAssetRecordFieldValue(const PMString& key) const;

	IDFile ResolveAssetPath() const;

	AssetState GetAssetState() const;
	PMString GetDescription() const;

private:
	void deepcopy(const CusDtLnkUITreeDataNode& rhs);

	K2Vector<CusDtLnkUITreeDataNode> fChildren;	



	PMString fUniqueKey;

	CusDtLnkUITreeDataNode* fParent;
	TreeDataNodeType fNodeType;

	// Applies iff node type is asset
	std::map<PMString, PMString> fAssetRecordValues;
	PMString fAssetDataBasePath;


};

#endif // __CusDtLnkUITreeDataNode_H_DEFINED__

