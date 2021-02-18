//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHierarchy.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IHIERARCHY__
#define __IHIERARCHY__

#include "IPMUnknown.h"
#include "GenericID.h"

class UIDList;

/**	
	The IHierarchy interface stores a persistent, UID-based tree structure.  This tree structure is used for InDesign's
	display hierarchy.  The boss objects that represent spreads, layers, and the various other types of page items
	(splines, images, etc.) aggregate an IHierarchy interface.
 */
class IHierarchy : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IHIERARCHY };

		/**	
			Special position index for adding items to a hierarchy.
		 */
		enum
		{
			kAtTheEnd = -1
		};
		
		/**	
			Flags for GetDescendents.
		 */
		enum
		{
			/**	
				Act on all children, including those that are hidden.
			 */
			kIncludeHidden = 0x00000001		
		};
		
		/**	Return the n'th child in the hierarchy. Called holds reference.
			@param n the index of the child to return. 
			@return IHierarchy 
		 */
		virtual IHierarchy *QueryChild(int32 n) const = 0;

		/**	Return the n'th child UID in the hierarchy.
			@param n the index of the child to return. 
			@return UID 
		 */
		virtual UID GetChildUID(int32 n) const = 0;
	
		/**	Return the index of this child
			@param p the child hierarchy to find the position for.
			@return int32 the child's position, -1 if not found.
		 */
		virtual int32 GetChildIndex(const IHierarchy * p) const = 0;

		/**	Return the number of children
			@param none
			@return int32 
		 */
		virtual int32 GetChildCount() const = 0;

		/**	Returns the immediate parent of this item. Caller holds reference. May be nil.
			@param none
			@return IHierarchy 
		 */
		virtual IHierarchy *QueryParent() const = 0;

		/**	Returns the immediate parent UID of this item. May be kInvalidUID.
			@param none
			@return UID 
		 */
		virtual UID GetParentUID() const = 0;
			
		/**	SetParent is not for external use. It's in the external
			interface so that subclasses can call it on IHierarchy
			parameters.  (protected doesn't work on parameters).
			See kRemoveFromHierarchyCmdBoss and kAddToHierarchyCmdBoss and
			IHierarchyUtils::AddToHierarchy and IHierarchyUtils::RemoveFromHierarchy
			@param *newParent 
		 */
		virtual void SetParent(IHierarchy *newParent) = 0;
		
		/**	Returns the ultimate parent of the hierarchy. Caller holds reference.
			@param none
			@return IHierarchy 
		 */
		virtual IHierarchy *QueryRoot() const = 0;

		/**	Returns the UID of the ultimate parent of the hierarchy.
			@param none
			@return UID 
		 */
		virtual UID GetRootUID() const = 0;

		/**	SetRootUID is not for external use.  It's in the external
			interface so that subclasses can call it on IHierarchy
			parameters.  (protected doesn't work on parameters)
			@param newRoot 
		 */
		virtual void SetRootUID(UID newRoot) = 0;

		/**	Add a new child before the index position. Or, if kAtTheEnd, add
			it to the end of the list.
			@param *newChild the item to add to the hierarchy.
			@param kAtTheEnd position to add, defaults to kAtTheEnd. Use 0 for initial position of hierarchy.
		 */
		virtual void Add(IHierarchy *newChild, int32 pos = kAtTheEnd) = 0;
			
		/**	Move the child to a new location in the z-order.
			@param *childToMove the item to move
			@param to the index location to move the item
		 */
		virtual void Move(IHierarchy *childToMove, int32 to) = 0;			

		/**	Remove the child. It is disowned, and is no longer a child.
			@param *childToRemove the item to remove.
		 */
		virtual void Remove(IHierarchy *childToRemove) = 0;
	
		/**	Same as above except it allows us to remove the child even if we can't access the IHierarchy interface.
			@param childToRemove the UID of the child to remove.
		 */
		virtual void Remove(UID childToRemove) = 0;

		/**	Answers, "Is this in before 'item' in the Z-order?"
			NOTE: Both items must be in the same hierarchy and be the
			same distance from the root.
			@param item the item to compare to this item
			@return bool16 kTrue if before (underneath) this item, kFalse otherwise.
		 */
		virtual bool16 IsLessThan(IHierarchy * item) = 0;

		/**	Return all the descendents that support interfaceID.
			@param *resultList [OUT] the filled in list of descendents meeting the requirements. 
			@param interfaceID [IN] the interfaceID to check each child (and grandchild, etc) for.
			@param flags Generally 0, but may include hidden items (kIncludeHidden)
		 */
		virtual void GetDescendents(UIDList *resultList, const PMIID& interfaceID, int32 flags = 0) const = 0;
			
		/**	Return ancestors that support interfaceID.  Collection of ancestors
			ends when an ancestor is reached that doesn't support the interface.
			@param *resultList [OUT] the filled in list of ancestors meeting the requirements.
			@param interfaceID [IN] the interfaceID to check each parent (and grandparent, etc) for. 
		 */
		virtual void GetAncestors(UIDList *resultList, const PMIID& interfaceID) const = 0;

		/**	Return the spread layer's UID for this hierarchy node.
			@param none
			@return UID 
		 */
		virtual UID GetLayerUID() const = 0;

		/**	Return the spread's UID for this hierarchy node.
			@param none
			@return UID 
		 */
		virtual UID GetSpreadUID() const = 0;
			
#ifdef DEBUG
		/**	Checks that all internally held pointers and UIDs are reasonable
			AND calls IsValid() for all children.
			@param none
			@return bool16 kTrue if valid, kFalse if in bad state.
		 */
		virtual bool16 IsValid() = 0;
#endif
};

#endif
