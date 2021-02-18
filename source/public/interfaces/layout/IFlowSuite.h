//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFlowSuite.h $
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
	#ifndef _IFlowSuite_
	#define _IFlowSuite_

#include "MasterPageID.h"
/**
 Suite interface for making master page items overrideable and not overrideable
  
*/
class IFlowSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IFLOWSUITE };

	public:

		/**	Description: Can the selection be set to the primary text flow?
			@param none
			@return bool16 kTrue if it can, kFalse if not
		 */
		virtual bool16 CanSetPrimaryTextFlow		(void) const = 0;	
	
		/**	Description: Is the selection the primary text flow and can it be cleared?
			@param none
			@return bool16 kTrue if it can, kFalse if not
		 */
		virtual bool16 CanClearPrimaryTextFlow		(void) const = 0;	

		/**	Description: Make selected master page items the primary text flow
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode SetPrimaryTextFlow () = 0;
		
		/**	Description: Clear selected master page items primary text flow
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode ClearPrimaryTextFlow () = 0;
		 
	};

#endif // _IFlowSuite_
