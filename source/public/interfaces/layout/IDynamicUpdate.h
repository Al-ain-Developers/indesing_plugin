//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDynamicUpdate.h $
//  
//  Owner: robin briggs
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
//  Supplies interface for dynamic actions.
//  
//========================================================================================

#pragma once
#ifndef __IDynamicUpdate__
#define __IDynamicUpdate__

#include "IPMUnknown.h"
#include "CommandID.h"

//----------------------------------------------------------------------------------------
// IDynamicUpdate: Aggregated with page item modifying commands to broadcast that the page
// item(s) are being modified dynamically.  Usually used within the context of a tracker
//----------------------------------------------------------------------------------------

class IDynamicUpdate : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDYNAMICUPDATE };

		virtual void BeginDynamicUpdate() = 0;
			// Dynamic updating has begun.
			
		virtual void EndDynamicUpdate(bool16 inval = kTrue) = 0;
			// Dynamic updating is completed.
			
		virtual void AbortDynamicUpdate() = 0;
			// Abort dynamic updating.

		enum DynamicState { kNotStarted, kBeginDynamic, kEndDynamic, kAbortDynamic, kEndDynamicWithoutInval };
		virtual DynamicState GetDynamicState() const = 0;
};

#endif // __IDynamicUpdate__
