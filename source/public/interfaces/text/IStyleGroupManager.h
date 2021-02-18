//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleGroupManager.h $
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
#ifndef __IStyleGroupManager__
#define __IStyleGroupManager__

#include "IPMUnknown.h"
#include "GenericID.h"

class IStyleGroupHierarchy;

/** The IStyleGroupManager is the access point for style set management. It gives access
	to the root IStyleGroupHierarchy from where you can get the full style set hierarchy.
*/

class IStyleGroupManager : public IPMUnknown
{
public:
	// kDefaultIID enum is not provided as all the StyleGroupManagers such as IParaStyleGroupManager
	// will have thier own ids.

	/** Returns the root hierarchy managed by this Manager.
	*/
	virtual IStyleGroupHierarchy* GetRootHierarchy() const = 0;

	/** Returns the default Style UID for this style set hierarchy.
	*/
	virtual UID GetDefaultStyleUID() const = 0;

	/** Sets the default style UID for this style set hierarchy.
		@param d [IN] the default style uid to set.
	*/
	virtual UID SetDefaultStyleUID(UID d) = 0;

	/** Returns the root style UID for this style set hierarchy. All the styles are
		based on this style.
	*/
	virtual UID GetRootStyleUID() const = 0;

    /** What kind of style match was found */ 
    enum StyleNameMatch { 
                /** Name is unique */ 
                kUniqueName,
                /** Name exactly matches existing name */ 
				kExactNameMatch,
                /** Name match start of style group. For example. aa exists as a style name
					and stylePath is aa:newname. UID of matched style is returned
				*/ 
                kStartofNameMatchesStyle,
                /** Name match style group. For example. aa exists as a group
					and stylePath is aa. UID of matched group is returned
				*/ 
                kNameMatchesStyleGroup
            } ; 
	/** Returns a UID whose path matches the passed path. The list may contain
		style sets as well as styles.
		@param stylePath [IN] name to find.
		@param matchInfo [OUT] how found.
		@return kInvalidUID if no match found, else UID of the found style.
	*/
	virtual UID FindByName(const PMString& stylePath, StyleNameMatch *matchInfo = nil) const = 0;

	/** Returns the UID of the style whose name matches the passed name with in the specified paren.
		@param parent [IN] style set node which will be searched for the style.
		@param name [IN] name to search for.
		@return kInvalidUID if the style or style set is not found.
	*/
	virtual UID FindByName(UID parent, const PMString& name) const = 0;

	/** Is the selfUID object based on the otherUID parameter? This can be through any levels of hierarchy.
		This relies on the IStyleInfo interface.
		@param self [IN] self UID
		@param other [in] other UID
		@return kTrue if the self UID is based on other UID, kFalse otherwise.
	*/
	virtual bool16 IsBasedOn(UID self, UID other) const = 0;


	/** Move the child to a new parent before specific index.
		@param childToMove [in] child to move.
		@param newParent [IN] new parent of the child.
		@param pos [IN] index position before which this child will be moved in to new parent.
			put IStyleGroupHierarchy::kAtTheEnd to move as last child.
	*/
	virtual void Move(UID childToMove, UID newParent, int32 pos) = 0;

	/** Remove this child from this hierarchy from deep with in this hierarchy
		@param childToRemove [IN] child to remove.
	*/
	virtual void Remove(UID childToRemove) = 0;

	/** Returns kTrue if the object specified by id a member of the hierarchy managed by this Manager.
		@param id [IN] objects UID.
		@return kTrue if the id belongs to the hierarchy managed by this.
	*/
	virtual bool16 IsHierarchyMember(UID id) const = 0;

	/**
	USED ONLY BY OBJECT STYLES CURRENTLY
	Sets the Default Text Style for this name table
	*/
	virtual void SetDefaultTextStyleUID(UID d) = 0;		

	/**
	USED ONLY BY OBJECT STYLES CURRENTLY
	Gets the Default Text Style for this name table
	*/
	virtual UID GetDefaultTextStyleUID() const = 0;

	/**
	USED ONLY BY OBJECT STYLES CURRENTLY
	Sets the Default Frame Grid Style for this name table
	*/
	virtual void SetDefaultFrameGridStyleUID(UID d) = 0;		

	/**
	USED ONLY BY OBJECT STYLES CURRENTLY
	Gets the Default Frame Grid Style for this name table
	*/
	virtual UID GetDefaultFrameGridStyleUID() const = 0;

	/** PRIVATE USE ONLY, DO NOT CALL THIS. this is needed for document conversion.
	*/
	virtual UID SetRootStyleUID(UID id) = 0;


};
#endif //__IStyleGroupManager__