//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IPendingUpdateController.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPENDINGUPDATECONTROLLER__
#define __IPENDINGUPDATECONTROLLER__

#include "IPMUnknown.h"
#include "ControlStripID.h"

class IPendingUpdateController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPENDINGUPDATECONTROLLER };

	/**	Called at draw time just before drawing in order to give a chance to do any updates.
		that have been delayed.
		@param None
		@return void 
	 */
	virtual void Update(void) = 0;

	/**	Set a flag that there are pending updates.
		@param bool16 kTrue to mark a pending update is required, kFalse to clear. kFalse should be used only internally by draw code.
		@return void 
	 */
	virtual void SetPendingUpdate(const bool16 bUpdate) = 0;

	/**	Return a flag that there are pending updates.
		@param None
		@return bool16 kTrue if pending updates, kFalse otherwise.
	 */
	virtual bool16 GetPendingUpdate(void) = 0;

	/**	Used for dynamic updating to reduce flash. Sets IID_IDYNAMICERASEBEFOREDRAWFLAG at this widget level and higher.
		@param bool16 when kTrue, panel will erase before draw, kFalse to override.
		@return void
	 */
	virtual void SetDynamicErase(bool16 bDynamicErase) = 0;
};

#endif // __IPENDINGUPDATECONTROLLER__
