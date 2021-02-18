//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IArrangeFacade.h $
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
	#ifndef _IArrangeFacade_
	#define _IArrangeFacade_

#include "LayoutID.h"

namespace Facade
{
	class IArrangeFacade : public IPMUnknown
	{
		public:
			enum { kDefaultIID = IID_IARRANGEFACADE };

		public:
			/**	Can these items be brought to front?
				@param targetItemList the list of items to be affected
				@param referenceItem the item these should be positioned relative to(if any)
				@return bool16 - kTrue == Yes, kFalse == No
			 */
			virtual bool16 CanBringToFront(const UIDList& targetItemList, UID referenceItem = kInvalidUID) const = 0;	

			/**	Can these items be brought forward?
				@param targetItemList the list of items to be affected
				@return bool16 - kTrue == Yes, kFalse == No
			 */
			virtual bool16 CanBringForward(const UIDList& targetItemList) const = 0;	

			/**	Can these items be sent backward?
				@param targetItemList the list of items to be affected
				@return bool16 - kTrue == Yes, kFalse == No
			 */
			virtual bool16 CanSendBackward(const UIDList& targetItemList) const = 0;	

			/**	Can these items be sent to back?
				@param targetItemList the list of items to be affected
				@param referenceItem the item these should be positioned relative to(if any)
				@return bool16 - kTrue == Yes, kFalse == No
			 */
			virtual bool16 CanSendToBack(const UIDList& targetItemList, UID referenceItem = kInvalidUID) const = 0;	

			/**	Bring the targeted items to the front
				@param targetItemList the list of items to be affected
				@param referenceItem the item these should be positioned relative to(if any)
				@param bDuplicate, kTrue to duplicate the items before moving to the new z-order location
				@return ErrorCode - Success/Failure
			 */
			virtual ErrorCode ProcessBringToFront (const UIDList& targetItemList, UID referenceItem = kInvalidUID, bool16 bDuplicate = kFalse) = 0;

			/**	Bring the targeted items forward
				@param targetItemList the list of items to be affected
				@return ErrorCode - Success/Failure
			 */
			virtual ErrorCode ProcessBringForward (const UIDList& targetItemList) = 0;

			/**	Send the targeted items backward in the Z-order
				@param targetItemList the list of items to be affected
				@return ErrorCode - Success/Failure
			 */
			virtual ErrorCode ProcessSendBackward (const UIDList& targetItemList) = 0;

			/**	Send the items to the back of the z-order
				@param targetItemList the list of items to be affected
				@param referenceItem the item these should be positioned relative to(if any)
				@param bDuplicate, kTrue to duplicate the items before moving to the new z-order location
				@return ErrorCode - Success/Failure
			 */
			virtual ErrorCode ProcessSendToBack (const UIDList& targetItemList, UID referenceItem = kInvalidUID, bool16 bDuplicate = kFalse) = 0;
				
	};
}
#endif // _IArrangeFacade_