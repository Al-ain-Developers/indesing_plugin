//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleGroupHierarchy.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __IStyleGroupHierarchy__
#define __IStyleGroupHierarchy__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "TextID.h"
class UIDList;

/**
	The IStyleGroupHierarchy interface stores a persistent, UID-based tree structure.  This tree structure is used for InDesign's
	display hierarchy.  The boss objects that represent (StyleGroups and Styles) aggregate an IStyleGroupHierarchy interface.
 */
class IStyleGroupHierarchy : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ISTYLEGROUPHIERARCHY };

		/**
			Special position index for adding items to a hierarchy.
		 */
		enum
		{
			/** Position to add at the end of list */
			kAtTheEnd = -1
		};

		/** Enum to distinguish different type of hierarchy elements
			Currently we have Styles , Style sets. In future we may have style links, etc.
		*/
		enum HierarchyTypeEnum
		{
			/** Type is unknown */
			kHierarchyTypeUnknown = 0,

			/** Type is the root of the style set hierarchy. Not visible in palettes*/
			kHierarchyTypeRoot = 1,

			/** Type is a style */
			kHierarchyTypeStyle = 2,

			/** Type is a style set */
			kHierarchyTypeStyleGroup = 3
		};

		/** Flag to be passed for sorting children.
		*/
		enum SortFlag
		{
			/** Sort ascending */
			kSortAscending = 0x00000001,

			/** Sort descending */
			kSortDescending = 0x00000002,

			/** Sort only only immediate children */
			kSortImmediateChildren = 0x00000004,

			/** Sort entire hierarchy of this node */
			kSortHierarchy = 0x00000008,

			/** Sort all the hierarchy in Ascening order */
			kSortAscendingHierarchy = kSortAscending|kSortHierarchy
		};

		/**	Return the n'th child in the hierarchy. Called holds reference.
			@param n [IN] the index of the child to return.
			@return IStyleGroupHierarchy
		 */
		virtual IStyleGroupHierarchy *QueryChild(int32 n) const = 0;

		/**	Return the n'th child UID in the hierarchy.
			@param n [IN] the index of the child to return.
			@return UID
		 */
		virtual UID GetChildUID(int32 n) const = 0;

		/**	Return the index of this child
			@param p [IN] the child hierarchy to find the position for.
			@return int32 the child's position, -1 if not found.
		 */
		virtual int32 GetChildIndex(const IStyleGroupHierarchy * p) const = 0;

		/**	Return the number of children
			@return int32
		 */
		virtual int32 GetChildCount() const = 0;

		/**	Returns the immediate parent of this item. Caller holds reference. May be nil.
			@return IStyleGroupHierarchy
		 */
		virtual IStyleGroupHierarchy *QueryParent() const = 0;

		/**	Returns the immediate parent UID of this item. May be kInvalidUID.
			@return UID
		 */
		virtual UID GetParentUID() const = 0;


		/**	Returns the ultimate parent of the hierarchy. Caller holds reference.
			@return IStyleGroupHierarchy
		 */
		virtual IStyleGroupHierarchy *QueryRoot() const = 0;

		/**	Returns the UID of the ultimate parent of the hierarchy.
			@return UID
		 */
		virtual UID GetRootUID() const = 0;


		/**	Add a new child before the index position. Or, if kAtTheEnd, add
			it to the end of the list.
			@param newChild [IN] the item to add to the hierarchy.
			@param pos [IN] kAtTheEnd position to add, defaults to kAtTheEnd. Use 0 for initial position of hierarchy.
		 */
		virtual void Add(IStyleGroupHierarchy *newChild, int32 pos = kAtTheEnd) = 0;

		/**	Move the child to a new location in the index order,
			Child must be immediate child of this node.
			@param childToMove [IN] the item to move
			@param to [IN] the index location to move the item
		 */
		virtual void Move(IStyleGroupHierarchy *childToMove, int32 to) = 0;

		/**	Remove the child. It is disowned, and is no longer a child.
			@param childToRemove [IN] the item to remove.
		 */
		virtual void Remove(IStyleGroupHierarchy *childToRemove) = 0;

		/**	Same as above except it allows us to remove the child even if we can't access the IStyleGroupHierarchy interface.
			@param childToRemove [IN] the UID of the child to remove.
		 */
		virtual void Remove(UID childToRemove) = 0;

		/**	Answers, "Is this in before 'item' in the Z-order?"
			NOTE: Both items must be in the same hierarchy and be the
			same distance from the root.
			@param item [IN] the item to compare to this item
			@return bool16 kTrue if before (underneath) this item, kFalse otherwise.
		 */
		virtual bool16 IsLessThan(IStyleGroupHierarchy * item) const = 0;

		/**	Return all the descendents that support interfaceID.
			@param resultList [OUT] the filled in list of descendents meeting the requirements.
			@param interfaceID [IN] the interfaceID to check each child (and grandchild, etc) for.
		 */
		virtual void GetDescendents(UIDList *resultList, const PMIID& interfaceID) const = 0;

		/**	Return ancestors that support interfaceID.  Collection of ancestors
			ends when an ancestor is reached that doesn't support the interface.
			@param resultList [OUT] the filled in list of ancestors meeting the requirements.
			@param interfaceID [IN] the interfaceID to check each parent (and grandparent, etc) for.
		 */
		virtual void GetAncestors(UIDList *resultList, const PMIID& interfaceID) const = 0;

		/** Returns the UID of the node if the node name is found in the immediate children
			of this Hierarchy. kInvalidUID otherwise.
			@param nodeName [IN] node name to find.
		*/
		virtual UID FindByName(const PMString& nodeName) const = 0;

		/** Sort the hierarchy based on the flag.
			@param flag [IN] see SortFlag for details.
		*/
		virtual void Sort(SortFlag flag = kSortAscendingHierarchy) = 0;

		/** Returns the name of this node.
		*/
		virtual PMString GetName(bool16 translated = kFalse) const = 0;

		/** Returns the location of this hierarchy object
			e.g "StyleGroup1:ChildSet2"
		*/
		virtual PMString GetLocation(bool16 translated = kFalse) const = 0;

		/** Returns the full path including name of this hierarchy object
			e.g. "StyleGroup1:ChildSet2:StyleName1"
			@param translated [IN] if you want the full path returned to have translated components
		*/
		virtual PMString GetFullPath(bool16 translated = kFalse) const = 0;

		/** Returns the HierarchyTypeEnum of this hierarchy.
		*/
		virtual HierarchyTypeEnum GetHierarchyType() const = 0;

#ifdef DEBUG
		/**	Checks that all internally held pointers and UIDs are reasonable
			AND calls IsValid() for all children.
			@param none
			@return bool16 kTrue if valid, kFalse if in bad state.
		 */
		virtual bool16 IsValid() const = 0;
#endif

		/**	PRIVATE USE ONLY, DO NOT USE, SetParent is not for external use. 
		    It's in the external interface so that subclasses can call it on 
			IStyleGroupHierarchy parameters.  (protected doesn't work on parameters).
			Use appropriate commands 
			@param *newParent
			@see kMoveStyleOrSetCmdBoss
		 */
		virtual void SetParent(IStyleGroupHierarchy *newParent) = 0;

		/**	FOR PRIVATE USE ONLY, DONT CALL THIS, SetRootUID is not for external use.  
			It's in the external interface so that subclasses can call it on 
			IStyleGroupHierarchy parameters.  (protected doesn't work on parameters)
			@param newRoot
		 */
		virtual void SetRootUID(UID newRoot) = 0;

};

#endif
