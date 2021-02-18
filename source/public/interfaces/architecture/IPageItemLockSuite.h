//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPageItemLockSuite.h $
//  
//  Owner: Shengliu Dai
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
	#ifndef _IPageItemLockSuite_
	#define _IPageItemLockSuite_
/**
 Lock and Unlock page item suite interface
  
*/
class IPageItemLockSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGEITEMLOCKSUITE };

	public:

		/**	Description:Can lock any selected page items?
			@param none
			@return bool16 
		 */
		virtual bool16 CanLock		(void) const = 0;	
	


		/**	Description: Can Unlock any selected page items?
			@param none
			@return bool16 
		 */
		virtual bool16 CanUnlock		(void) const = 0;	


		/**	Description: Are there selection selected page item?
			@param none
			@return bool16 
		 */
		virtual bool16 	HaveSelection (void) const = 0;	
		


		/**	Description: Are all selected page item locked?
			@param none
			@return bool16 
		 */
		virtual bool16 	AreItemsAllLocked (void) const = 0;	
		


		/**	Description: Lock selected page items
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode LockPageItems () = 0;
		


		/**	Description: Unlock selected page items	
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode UnlockPageItems () = 0;

		/**	Description: Deselect any locked page items	
			@param none
			@return bool16 true if at least one was deselected. 
		 */
		virtual bool16 DeselectLockedPageItems () = 0;
		 
	};

#endif // _IPageItemLockSuite_