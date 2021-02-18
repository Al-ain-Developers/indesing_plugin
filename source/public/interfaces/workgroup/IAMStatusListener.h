//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMStatusListener.h $
//  
//  Owner: Bill Tislar
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
#ifndef __IAMSTATUSLISTENER__
#define __IAMSTATUSLISTENER__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IManagedStatus;

/** The IAMStatusListener interface processes updates to changes in an asset's IManagedStatus.
	This interface may be added to any boss that is concerned with IManagedStatus changes; e.g.,
	a UI widget that displays a status message or icon. An IAMStatusListener registers for
	updates by calling the IManagedStatus::AddListener() method for an IManagedStatus instance.
	A listener may register with any number of IManagedStatus instances.
	@see IManagedStatus.
	@see IAssetStateMachine.
*/
class IAMStatusListener : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSTATUSLISTENER };

	/** The Update method is called when there is a change in an IManagedStatus.
		@param is a valid pointer to the IManagedStatus instance reporting a status change. This
			is useful when processing status changes for multiple IManagedStatus instances.
	*/
	virtual void Update( IManagedStatus * status ) = 0;
	
};

#endif // __IAMSTATUSLISTENER__
