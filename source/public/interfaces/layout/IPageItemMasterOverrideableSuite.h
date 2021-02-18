//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemMasterOverrideableSuite.h $
//  
//  Owner: Melissa Cheng
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
	#ifndef _IPageItemMasterOverrideableSuite_
	#define _IPageItemMasterOverrideableSuite_

#include "MasterPageID.h"
/**
 Suite interface for making master page items overrideable and not overrideable
  
*/
class IPageItemMasterOverrideableSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGEITEMMASTEROVERRIDEABLESUITE };

	public:

		/**	Description:Can override any selected master page items?
			@param none
			@return bool16 
		 */
		virtual bool16 CanOverride		(void) const = 0;	
	


		/**	Description: Cannot override any selected master page items?
			@param none
			@return bool16 
		 */
		virtual bool16 CannotOverride		(void) const = 0;	


		/**	Description: Are there any selected master page items?
			@param none
			@return bool16 
		 */
		virtual bool16 	HaveSelection (void) const = 0;	
		


		/**	Description: Are all selected master page items overrideable?
			@param none
			@return bool16 
		 */
		virtual bool16 	AreItemsAllMasterOverrideable (void) const = 0;	
		


		/**	Description: Make selected master page items overrideable
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeMasterPageItemsOverrideable () = 0;
		


		/**	Description: Make selected master page items not overrideable
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeMasterPageItemsNotOverrideable () = 0;
		 
	};

#endif // _IPageItemMasterOverrideableSuite_