//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HierarchyVisitorHelper.h $
//  
//  Owner: Rich Gartland
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
#ifndef __HIERARCHYVISITORHELPER__
#define __HIERARCHYVISITORHELPER__

#include "IPMUnknown.h"
#include "IVisitorHelper.h"
#include "HelperInterface.h"

class PMRect;

#pragma export on

/**	Base implementation for IVisitorHelper classes that use IHierarchy for finding children.
*/
class PUBLIC_DECL HierarchyVisitorHelperImpl : public IVisitorHelper
{
	public:
		HierarchyVisitorHelperImpl(IPMUnknown *boss);
		~HierarchyVisitorHelperImpl();

		/**	Override this to call the proper routine in theVisitor for the node.
			@param theVisitor IN a pointer to the IBaseVisitor that knows how to pass control off to specific visitor
			routines, depending on the type of node found
			@return bool16 whether to stop traversal yet or not; kTrue means stop immediately, kFalse means continue
		*/
		virtual bool16 Accept(IBaseVisitor* theVisitor);

		/** Determine how many children this node has, and if necessary, do any allocation or caching needed when 
			individual children are accessed via QueryChild.
			@param theHandler IN pointer to the IBaseHandler in use for this visitation.
			@return bool16 the number of children found for this item.
		*/
		virtual int32 CollectChildren(IBaseHandler* theHandler);

		/**	Query for a specific child of this node.
			@param index IN the index of the node desired (zero-based)
			@return an IVisitorHelper pointer to the child node
		*/
		virtual IVisitorHelper* QueryChild(int32 index);
	private:
		UIDList	fIntersectingItemUIDs;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
