//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHierarchyCmdData.h $
//  
//  Owner: Bernd Paradies
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
//  Similar to INewPageItemCmd you need the parent's UIDRef in order to do AddToHierarchyCmd.
//  
//========================================================================================

#pragma once
#ifndef __IHierarchyCmdData__
#define __IHierarchyCmdData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "GenericID.h"

class UIDList;

/**
	A command interface for kAddToHierarchyCmdBoss. Similar to INewPageItemCmd, you need the parent's UIDRef
	in order to do AddToHierarchyCmd.
 */
class IHierarchyCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHIERARCHYCMDDATA };

	/**	Set the item's parent. Could be the UID of a spread layer, a graphic frame, etc.
		@param parentList [IN] list of parent's for each item in the item list for the command (kAddToHierarchyCmdBoss)
	 */
	virtual void SetParent( const UIDList& parentList ) = 0;

	/**	Returns the parent list from SetParent
		@return UIDList& Returns the parent list from SetParent
	 */
	virtual const UIDList& GetParent() const = 0;

	/**	The item's index in the parent for IHierarchy::Add.
		Must match up with the itemlist passed to the command (kAddToHierarchyCmdBoss).
		@param indexList [IN] index list for each item in command's item list in the parent hierarchy. Typically IHierarchy::kAtTheEnd.
	 */
	virtual void SetIndexInParent( const K2Vector<int32>& indexList ) = 0;

	/**	Returns index positions for each item in its parent hierarchy (from SetIndexInParent)
		@return K2Vector<int32>& Returns a reference to a vector of parent indices for each item in item list for kAddToHierarchyCmdBoss.
	 */
	virtual const K2Vector<int32>&	GetIndexInParent() const = 0;
};

#endif	// __IHierarchyCmdData__
