//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/EntryNode.h $
//  
//  Owner: Yeming Liu
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
//  
//  Comments: Templatized Node class allowing an arbitrary number of children in the tree.
//  This structure is used to support multi level sorting.
//  
//========================================================================================

#pragma once
#ifndef __ENTRYNODE__
#define __ENTRYNODE__

/** Templatized helper class allowing an arbitrary number of children in the tree. This is 
    using a linked list data structure representing a binary tree. All the nodes in each 
	linked list are on the same level. Each child node starts a new level. Each node in the tree 
	could have a parent, a child, a next sibling and a previous sibling. The first child of a node 
	may not have a previous sibling. This structure is used to support multi level sorting for table of content.
*/
template <class T> 
class EntryNode 
{
	public:
		/** Default contructor.
		*/
		EntryNode() : fData(), fLevel(0), fChild(nil), fSibling(nil), fPrevious(nil), fPreviousIsParent(kFalse) { }

		/** Copy constructor with given data information.
		    @param data IN object copy from.
		*/
		EntryNode(const T& data) : fData(data), fLevel(1), fChild(nil), fSibling(nil), fPrevious(nil), fPreviousIsParent(kFalse) { }

		/** Copy constructor with given data and its corresponding information.
		    @param data IN data copy from.
			@param level IN level where the node will be
			@param child IN node's child
			@param sibling IN node's sibling
			@param previous IN node's previous sibling
			@param isParent IN node's is a parent or not
		*/
		EntryNode(const T& data, int32 level, EntryNode<T>* child, EntryNode<T>* sibling, EntryNode<T>* previous, bool16 isParent) : 
				fData(data), fLevel(level), fChild(child), fSibling(sibling), fPrevious(previous), fPreviousIsParent(isParent) { }

		/** Default destructor.
		*/
		virtual ~EntryNode() {}

		/**	Get the data of the node.
			@param none
			@return T& the data.
		*/
		virtual const T& GetData() { return fData; }

		/**	Set the data of the node
			@param data the data to be set in the node.
		*/
		virtual void     SetData(const T& data) { fData = data; }

		/**	Get the level of the node.
			@param none
			@return int32 the level of the node.
		*/
		virtual int32    GetNodeLevel() { return fLevel; }

		/**	Set the level of the node.
			@param level IN the level to be set for the node.
		*/
		virtual void     SetNodeLevel(int32 level) { fLevel = level; }

		/**	Get the child node of this node.
			@param none
			@return EntryNode<T>* the child node.
		*/
		virtual EntryNode<T>* GetChild() { return fChild; }

		/**	Set the child node of this node.
			@param child IN the child node to be set for this node.
		*/
		virtual void          SetChild(EntryNode<T>* child) { fChild = child; }

		/**	Get the next sibling node of this node.
			@param none
			@return EntryNode<T>* the next sibling node.
		*/
		virtual EntryNode<T>* GetSibling() { return fSibling; }

		/**	Set the next sibling node of this node.
			@param sibling IN the next sibling node to be set for this node.
		*/
		virtual void          SetSibling(EntryNode<T>* sibling) { fSibling = sibling; }

		/**	Get the previous node of this node.
			@param none
			@return EntryNode<T>* the previous node to be set for this node.
		*/
		virtual EntryNode<T>* GetPrevious() { return fPrevious; }

		/**	Set the previous node of this node.
			@param previous IN the previous node to be set for this node.
		*/
		virtual void          SetPrevious(EntryNode<T>* previous) { fPrevious = previous; }

		/**	Get the flag about if the node is parent or not. A node is a parent 
		    if it has child node.
			@param none
			@return bool16 kTrue means the node is a parent, otherwise, return kFalse.
		*/
		virtual bool16 IsPreviousParent() { return fPreviousIsParent; }

		/**	Set the flag about it is a parent node or not.
			@param isParent IN the flag indicates it is a parent node or not.
		*/
		virtual void   SetPreviousIsParent(bool16 isParent) { fPreviousIsParent = isParent; }

	private:
		T        fData;			// any data in the entry node
		int32	 fLevel;		// level where the data will be
		EntryNode<T>* fChild;	// the node's child
		EntryNode<T>* fSibling; // the node's sibling
		EntryNode<T>* fPrevious;// the node's previous node
		bool16   fPreviousIsParent;// flag indicates if thie nodes has parent or not(such as non-first child of a node)
};

#endif // __ENTRYNODE__