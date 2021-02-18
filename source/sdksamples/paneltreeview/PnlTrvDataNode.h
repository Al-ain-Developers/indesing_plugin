//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvDataNode.h $
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

#ifndef __PnlTrvDataNode_H_DEFINED__
#define __PnlTrvDataNode_H_DEFINED__

/** Class to represent a generic node within a tree, with data
	that is encapsulated in a PMString.

	
	@ingroup paneltreeview
*/

class PnlTrvDataNode
{
public:
	/** Constructor */
	PnlTrvDataNode();

	/** Destructor */
	virtual ~PnlTrvDataNode();

	// +K2Vector support

	/**	Copy constructor
		@param rhs [IN] node reference
		@return  
	 */
	PnlTrvDataNode(const PnlTrvDataNode& rhs);

	/**	Operator assignment
		@param rhs [IN] node reference
		@return PnlTrvDataNode& 
	 */
	PnlTrvDataNode& operator=(const PnlTrvDataNode& rhs);

	/** For K2Vector copy semantics
	*/
	typedef object_type data_type;
	// -K2Vector support

	/**	Operator equality
		@param rhs [IN] node reference
		@return bool 
	 */
	bool operator==(const PnlTrvDataNode& rhs) const;


	/**	Accessor for child by zerobased index in parent's list of kids
		@param indexInParent [IN] which child by zero-based index
		@return child at given index 
	 */
	const PnlTrvDataNode& GetNthChild(int32 indexInParent) const;

	/**	Accessor for parent
		@return reference to parent node
	 */
	PnlTrvDataNode* GetParent() const;

	/**	Accessor for size of child list on this node
		@return int32 giving the number of children on this node 
	 */
	int32 ChildCount() const;

	/**	Get the data associated with this node (path or whatever)
		@return data represented here 
	 */
	PMString GetData() const;

	/**	Add child to this node (at end of list)
		@param o [IN] child node to add
	 */
	void AddChild(const PnlTrvDataNode& o);

	/**	Remove specified child from our list
		@param o [IN] specifies child to remove
	 */
	void RemoveChild(const PnlTrvDataNode& o);

	/** Mutator for the parent of this node
		@param p [IN] specifies new parent to set
	 */
	void SetParent(const PnlTrvDataNode* p);

	/**	Mutator for data stored on this
		@param data [IN] specifies the new data to store
	 */
	void SetData(const PMString& data);

private:
	K2Vector<PnlTrvDataNode> fChildren;	
	PMString fPathData;
	PnlTrvDataNode* fParent;
	void deepcopy(const PnlTrvDataNode& rhs);
};

#endif // __PnlTrvDataNode_H_DEFINED__

