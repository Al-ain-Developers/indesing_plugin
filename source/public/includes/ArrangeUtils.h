//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ArrangeUtils.h $
//  
//  Owner: Richard Rodseth
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
#ifndef __ARRANGEUTILS__
#define __ARRANGEUTILS__

#include "UIDList.h"

class IHierarchy;
class UIDRef;

//===============================================================
// Debugging utilities 
//===============================================================

#ifdef DEBUG
void DumpItemList(UIDList* itemList);
void DumpIndexList(K2Vector<int32>* indexList);
void DumpChildren(IHierarchy* parent);
#endif


//===============================================================
// class Arranger 
//===============================================================

/*
	This class is used by BringToFrontCmd, BringForwardCmd, SendBackwardCmd 
	and SendToBackCommand. It contains a few static methods, but is 
	generally allocated on the stack. This allows some of its methods to
	cache frequently-computed values in data members.
*/

#pragma export on

class PUBLIC_DECL Arranger
{
public:

	enum
	{
		kNotSorted = 0,
		kSorted = 1
	};
	
	Arranger(UIDList* selectedItems, bool16 sorted);
		// Construct an arranger on the stack. If the list is already
		// sorted, pass kSorted, otherwise pass kNotSorted.
		
	~Arranger();
	
	// -- Static functions --

	static int32 NodeDepth(IHierarchy* item);
		// returns the depth of a node, where the root is 0
		// Used by IsLessThan
		
	//static bool16 IsLessThan(IHierarchy* firstNode, IHierarchy* secondNode);
	static bool16 IsLessThan(const UIDRef& firstItem, const UIDRef& secondItem);
		// returns kTrue, if firstItem appears before secondItem in the display order
		// firstItem and secondItem must have a common root, but need not be at the
		// same depth in the tree
		
	static bool16 IsGreaterThan(const UIDRef& firstItem, const UIDRef& secondItem);
		// returns kTrue, if firstItem appears after secondItem in the display order
		// firstItem and secondItem must have a common root, but need not be at the
		// same depth in the tree

	static void SortItemsBackToFront(UIDList* itemList);
		// Sorts a list of nodes into display order. The nodes can be at any level
		// in the hierarchy

	static void SortItemsFrontToBack(UIDList* itemList);
		// Sorts a list of nodes into reverse-display order. The nodes can be at any level
		// in the hierarchy

	// -- Member functions --
	
	void SortItems();
		// Sorts fSelectedItems if it needs sorting

	int32 GetMaxBack(IHierarchy* parent);
		// Returns the index of the frontmost selected item which is "at the back"
	
	int32 GetMinFront(IHierarchy* parent);
		// Returns the index of the backmost selected item which is "at the front"
	
	bool16 CanSendBack(UID refObj = kInvalidUID);
		// Returns kTrue if any items are eligible to move back
		
	bool16 IsAtBack(IHierarchy* node);
	bool16 IsAtBack(IHierarchy* parent, int32 nodePosition);

	bool16 CanBringForward(UID refObj = kInvalidUID);
		// Returns kTrue if any items are eligible to move forward
		
	bool16 IsInFront(IHierarchy* node);
	bool16 IsInFront(IHierarchy* parent, int32 nodePosition);
	
private:
	UIDList*	fSelectedItems; // The list of items to which the command is applied
	bool16		fSorted;		
	UID			fLastParent_MinFront;
	UID			fLastParent_MaxBack;
	int32		fMaxBack; // The largest index known to be part of the back range
	int32		fMinFront; // The smallest index known to be part of the front range
};

#pragma export off

#endif // __ARRANGEUTILS__
