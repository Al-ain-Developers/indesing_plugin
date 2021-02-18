//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ILayoutPolicySuite.h $
//  
//  Owner: Dave Stephens
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
//  Comments:	Selection suite for multimedia page items
//  
//========================================================================================

#pragma once
#ifndef _ILayoutPolicySuite_
#define _ILayoutPolicySuite_

#include "IFlowFacade.h"
#include "ILayoutObject.h"

#include "LayoutUIID.h"

/** Selection suite for manipulating HTML page items.
	
*/
class ILayoutPolicySuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTPOLICYSUITE};
		
	/** Tests the current selection for a layout policy.
		@param outPolicy [OUT]: the layout policy applied to the current selection
		@return true if the policy is consistent across the entire selection, false if mixed.
	*/
	virtual bool32 GetLayoutPolicy(ILayoutObject::LayoutPolicy& outPolicy) const = 0;
	
	/** Set the layout policy on the current selection.
		@param policy [IN]: The new layout policy to apply
		@return kSuccess if successful
	 */
	virtual ErrorCode SetLayoutPolicy(ILayoutObject::LayoutPolicy policy) const = 0;
	
	/** Get a page range string for the selected pages.
		@param pPageString [OUT] result page range string
		@return true if there is a page selection
		@see IPageList::GetPageRangeString
	 */
	virtual bool32 GetPageRangeString(PMString & pPageString) const = 0;
	
	/** Return whether or not the current page selection allows the "Based On Master" layout policy to
		be applied. The "Based On Master" layout policy can only be applied if the applied master page's
		geometry is coincident with the selected page's geometry.
	*/
	virtual bool32 CanApplyBasedOnMasterPolicy() const = 0;
		
	/** Get the object constraints applied to the selected page items or key objects
		
		@param outListOfConstraints [OUT]: The constraints
		
		@return true if object constraints are applicable. That is, if the layout policy
		on the selected pages is either Object-based or it is Based on Master and the master policy
		is Object-based.
	*/
	virtual bool32 GetConstraints(Flow::ConstraintList& outListOfConstraints) const = 0;

	/** Set object constraints on the current page item or key object selection.
		@param constraints [IN]: The constraints to apply
		@return kSuccess if successful, otherwise an error code.
	 */
	virtual ErrorCode SetConstraints(const Flow::ConstraintList& constraints) const = 0;

	/** Return whether or not the current page layout policy is Object-Based and there is a selection for which object-based constraints
		can be applied.
	 */
	virtual bool32 CanApplyObjectConstraints() const = 0;
};


#endif // _ILayoutPolicySuite_