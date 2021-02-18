//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemVisibilityFacade.h $
//  
//  Owner: bob freeman
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
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _IPageItemVisibilityFacade_
	#define _IPageItemVisibilityFacade_

#include "GenericID.h"

/**
 Show and Hide page item Facade
  
*/
namespace Facade
{
	class IPageItemVisibilityFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGEITEMVISIBILITYFACADE };


		/**	Description:Tests to see if the target item can be hidden using the IID_IVISIBLE interface.
			@param targetItem - the page item in question
			@return bool16 - true if the interface exists
		 */
		virtual bool16 CanHide(const UIDRef& targetItem) const = 0;	

		/**	Description:Tests to see if any of the target items can be hidden using the IID_IVISIBLE interface.
			@param targetItem - the page item in question
			@return bool16 - true if the interface exists
		 */
		virtual bool16 CanAnyHide(const UIDList& targetItemList) const = 0;	

		/**	Description:Gets the visible flag stored on the item. It does not go up the hierarchy to determine
			if the item is effectively visible. In other words, if a parent is hidden and its child visible and this
			is called on the child, it returns visible. If the object does not suppor the visible flag, it just returns
			true or visible
			@param targetItem - the page item in question
			@return bool16 - true if visible flag is true or if object doesn't support the flag. false if flag is false.
		 */
		virtual bool16 GetVisibleState(const UIDRef& targetItem) const = 0;	
	

		/**	Description: returns true if the item or any of it's ancestors have the visibility flag false.
			@param targetItemList - the list of items in question
			@return bool16 - true if the item or any of it's ancestors have the visibility flag false.
		 */
		virtual bool16 IsHidden(const UIDRef& targetItem) const = 0;			

		/**	Description: Returns true if any of the target items or their ancestors are hidden.
			@param targetItemList - the list of items in question
			@return bool16 - Returns true if any of the target items or their ancestors are hidden.
		 */
		virtual bool16 	AreAnyHidden (const UIDList& targetItemList) const = 0;		

		/**	Description: Returns true if all of the target items or their ancestors are hidden.
			@param targetItemList - the list of items in question
			@return bool16 - Returns true if all of the target items or their ancestors are hidden.
		 */
		virtual bool16 	AreAllHidden (const UIDList& targetItemList) const = 0;		

		/**	Description: Returns true if any items on the given spread are hidden.
			@param targetItem - the spread in question
			@return bool16 - Returns true if any of the target items or their ancestors are hidden.
		 */
		virtual bool16 	AreAnyHiddenOnSpread (const UIDRef& targetItem) const = 0;		

		/**	Description: Show the page item. If an ancestor is hidden, this change will not be visible.
			@param targetItemList - the list of items to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode Show (const UIDList& targetItemList) = 0;
		
		/**	Description: Unlock the target page items	
			@param targetItemList - the list of items to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode Hide (const UIDList& targetItemList) = 0;
		 
		/**	Description: Show all hidden items in target spread	
			@param targetSpread - the spread to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode ShowAllInSpread (const UIDRef& targetSpread) = 0;

		/**	Description: Get the list of hidden objects on a given spread. These are objects that
		    have the visible flag on them
			@param [IN] targetSpread - the spread to gather objects from
			@param [IN/OUT] hiddenItems - the returned list of hidden items
			@return ErrorCode 
		 */
		virtual ErrorCode GetHiddenObjects(const UIDRef& targetSpread, UIDList& hiddenItems ) = 0;


	};
}
#endif // _IPageItemVisibilityFacade_