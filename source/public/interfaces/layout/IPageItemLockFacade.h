//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemLockFacade.h $
//  
//  Owner: lance bushore
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
	#ifndef _IPageItemLockFacade_
	#define _IPageItemLockFacade_

#include "GenericID.h"
#include "IDocument.h"

/**
 Lock and Unlock page item Facade
  
*/
namespace Facade
{
	class IPageItemLockFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGEITEMLOCKFACADE };


		/**	Description:Can lock any of the target page items?
			@param targetItemList - the list of items in question
			@return bool16 
		 */
		virtual bool16 CanLock(UIDList targetItemList) const = 0;	
	

		/**	Description: Can Unlock any of the target page items?
			@param targetItemList - the list of items in question
			@return bool16 
		 */
		virtual bool16 CanUnlock(UIDList targetItemList) const = 0;		

		/** Description: IsLockedAndNotSelectable
			@param targetItemList - the list of items in question
			@return bool16 kTrue if items are locked and can't be selected because of preference setting,
				kFalse if unlocked or if item is locked and CAN be selected.
		 */
		virtual bool16 IsLockedAndNotSelectable(UIDList targetItemList) const = 0;		

		/**	Description: Is any ancestor(including the layer) locked
			@param oneItem - the item in question
			@return bool16 
		 */
		virtual bool16 IsAnyAncestorLocked(const UIDRef& oneItem) const = 0;			

		/**	Description: Are all of the target page item locked?
			@param targetItemList - the list of items in question
			@return bool16 
		 */
		virtual bool16 	AreItemsAllLocked (UIDList targetItemList) const = 0;		

		/**	Description: Lock the target page items
			@param targetItemList - the list of items to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode LockPageItems (UIDList targetItemList) = 0;
		
		/**	Description: Unlock the target page items	
			@param targetItemList - the list of items to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode UnlockPageItems (UIDList targetItemList) = 0;

		/**	Description: See if any items are locked on the target spread.	
			@param targetSpread - Spread to check.
			@return bool16 true if any items on the spread are locked. 
		 */
		virtual bool16 	AreAnyUnlockableOnSpread (const UIDRef& targetSpread) const = 0;
		
		/**	Description: See if any items are locked on the target document. This walks all master and regular spreads.
			@param theDoc - the document to operate on
			@return ErrorCode 
		 */
		virtual bool16 	AreAnyUnlockableInDocument (IDocument * theDoc) const = 0;
		
		/**	Description: Unlocks the page items	on the target spread. 
			@param targetSpread - the Spread to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode UnlockAllOnSpread (const UIDRef& targetSpread) = 0;
		
		/**	Description: Unlocks the page items	on the target document. This walks all master and regular spreads.
			@param theDoc - the document to operate on
			@return ErrorCode 
		 */
		virtual ErrorCode UnlockAllInDocument (IDocument * theDoc) = 0;

		 
	};
}
#endif // _IPageItemLockFacade_