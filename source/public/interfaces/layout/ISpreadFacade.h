//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpreadFacade.h $
//  
//  Owner: Bob Freeman
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
#ifndef __ISpreadFacade__
#define __ISpreadFacade__

// ----- Interfaces -----
#include "ILayoutObject.h"
#include "Utils.h"

// ----- ID.h files -----
#include "SpreadID.h"

namespace Facade
	{
	/** A high level API for dealing with Spreads and Pages.  To use this Facade, include
	    this header file and use the following example syntax:
	    result = Utils<Facade::ISpreadFacade>()->SetPageColorLabel( ... );

	    @author Bob Freeman
	*/
	class ISpreadFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ISPREADFACADE };
		
		/**	Sets the page color flag color for one or more pages. The pages in the list must all be of the same
		    type: Master or Layout and pages or spread. For example, you can have a list of master spreads or a 
			list of Layout pages but not a mixture.
		
			@param pagesOrSpreads - pages to set the page color flag on. If the page is a master, all dependent pages will also have their flags set.
			@param color - The UIDRef of the UI color to set the flag to. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode SetPageColorLabel
							(
								UIDList pagesOrSpreads, 
								UIDRef color
							) = 0;


		/**	Gets the current page color flag color for a given page. If the color is not set, kInvalidUID is returned.
		
			@param page - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.

			@return UID - UID of the UI Color that is set. kInvalidUID is returned if the color is not set.
		 */
		virtual const UID GetPageColorLabel
							(
								UIDRef page
							) = 0;

		/** Get the list of unique effective layout policies for the given list of pages. Here, "effective" means that if
		 * the layout policy is "Controlled by Master", then we'll return the master's layout policy if it honors the rules for
		 * being a "controller" or No Layout Policy otherwise.
		 * @param pageList [IN]: The list of source pages
		 * @param outList [OUT]: The list of layout policies that are applied to the given source pages. Duplicates are removed.
		 */
		virtual void GetEffectiveLayoutPolicy(const UIDList& pageList, ILayoutObject::LayoutPolicyList& outList) const = 0;
		
		/** Get the list of unique layout policies for the given list of pages
			@param pageList [IN]: The list of source pages
			@param outList [OUT]: The list of layout policies that are applied to the given source pages. Duplicates are removed.
		 */
		virtual void GetLayoutPolicy(const UIDList& pageList, ILayoutObject::LayoutPolicyList& outList) const = 0;

		/** Set the given layout policy on the given list of pages
			 @param pageList [IN]: The list of target pages
			 @param policy [IN]: The policy to apply.
			 @return an ErrorCode
		 */
		virtual ErrorCode SetLayoutPolicy(const UIDList& pageList, ILayoutObject::LayoutPolicy policy) = 0;
		
		/** Determine whether or not the "Based on Master" layout policy can take effect on the given list of pages.
		 The "Based On Master" layout policy can only be applied if the applied master page's
		 geometry is coincident with the selected page's geometry.
			 @param pageList [IN]: The list of pages to test
			 @return kTrue if the "Based on Master" layout policy can take effect on the given list of pages.
		 */
		virtual bool32 CanApplyBasedOnMasterPolicy(const UIDList& pageList) const = 0;

		/** Determine the optional page setting for the page(s).
			@param pageList [IN]: The list of source pages
			@param outList [OUT]: The list of optional page settings that are applied to the given source pages. Duplicates are removed. Empty if no items list have an optional page setting.
		*/
		virtual void GetOptionalPage(const UIDList& pageList, K2Vector<bool16>& outList) const = 0;

		/** Set the list of pages to have the given optional page setting
			 @param pageList [IN]: The list of target pages
			 @param policy [IN]: The optional page setting to apply.
			 @return an ErrorCode
		 */
		virtual ErrorCode SetOptionalPage(const UIDList& pageList, bool16 optional) = 0;
	};
}

#endif // __ISpreadFacade__

