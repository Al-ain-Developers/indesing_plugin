//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutObject.h $
//  
//  Owner: Shawn Sheridan
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================
#pragma once
#ifndef __ILayoutObject__
#define __ILayoutObject__

#include "SpreadID.h"
#include "IPMUnknown.h"


/**
 *	The ILayoutObject is used to apply a layout policy to an object such that when the
 *	object is resized, the policy can be used to determine how to adapt the children
 *	of the object.
 *	@see ILayoutPolicySuite.h, IFlowFacade.h
 */
class ILayoutObject : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTOBJECT };

	/**
	 *	Layout policies
	 *	kPreserveLayoutPolicy is used when creating alternate layouts and simply means that the duplicated
	 *		master pages and pages should have the same policies as the originals.
	 *	kNoLayoutPolicy = Off
	 *	kRecenterLayoutPolicy = Do not resize or scale anything. Simply reposition page items such that their distance to the center
	 *		of the design area is maintained.
	 *	kRepositionLayoutPolicy = Object-based. This policy not only repositions but may also resize page items depending on the
	 *		page item constraints set up via IFlowFacade::SetConstraints.
	 *	kScaleLayoutPolicy = Proportionally scales the contents of the page, maintaining aspect ratios, and centers the result to
	 *		letter box/pillar box.
	 *	kGuideSliceLayoutPolicy = Uses liquid/slicing guides to determine which items on the page are resizable.
	 *	kUseMasterLayoutPolicy = If the master page's geometry is coincident with the layout page, then use the policy on the master page.
	 *		Otherwise, kNoLayoutPolicy is used.
	 */
	enum LayoutPolicy {
			kPreserveLayoutPolicy = -1,	// Means leave unchanged
			kNoLayoutPolicy = 0,		// Off
			kRecenterLayoutPolicy,		// Re-center
			kRepositionLayoutPolicy,	// Object-based
			kScaleLayoutPolicy,			// Scale
			kGuideSliceLayoutPolicy,	// Guide-based
//			kInterpolationLayoutPolicy,
			kUseMasterLayoutPolicy		// Controlled by Master
		};

	/** Vector of layout policies to get/set to/from range of objects  */
	typedef K2Vector<LayoutPolicy> LayoutPolicyList;

	/** Get the layout policy that is applied to this object (typically a page)
	 *	@return The layout policy
	 */
	virtual LayoutPolicy GetLayoutPolicy() const = 0;
	
	/** Set the layout policy for this object (typically a page).
	 *	@param policy [IN] The layout policy to apply.
	 */
	virtual void SetLayoutPolicy( LayoutPolicy policy) = 0;
};

DECLARE_BASE_TYPE(ILayoutObject::LayoutPolicy);


#endif	// __ILayoutObject__
