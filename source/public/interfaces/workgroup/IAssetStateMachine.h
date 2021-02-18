//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAssetStateMachine.h $
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
#ifndef __IASSETSTATEMACHINE__
#define __IASSETSTATEMACHINE__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IManagedStatus;


/** The IAssetStateMachine encapsulates the rules for handling asset status changes. This
	interface represents a convenient abstraction for consolidating the rules for status
	processing into a single class. Using and providing an implementation for this
	interface is optional.
*/
class IAssetStateMachine : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSETSTATEMACHINE };

	/** This method initializes the state of an IManagedStatus instance. Suggested usage:
		called during the IAMServiceProvider::enInitialize service.
		@param managedStatus is a valid pointer to an IManagedStatus instance.
		@param objectUID is the UID of the document model object associated with the IManagedStatus.
		@see IManagedStatus.
		@see IAMServiceProvider.
	*/
	virtual void InitializeState( IManagedStatus * managedStatus, UID objectUID = kInvalidUID ) = 0;
	
	/** This method processes state changes for an IManagedStatus instance. Suggested usage:
		called by the IAssetMonitor HandleChangesCmd.
		@param managedStatus is a valid pointer to an IManagedStatus instance.
		@param objectUID is the UID of the document model object associated with the IManagedStatus.
		@param useCachedData is a control flag; when true, cached status data can be used to handle the
			state change.
		@see IManagedStatus.
		@see IAssetMonitor.
	*/	
	virtual void HandleStateChange( IManagedStatus * managedStatus, UID objectUID = kInvalidUID, bool useCachedData = false ) = 0;
		
}; // end IAssetStateMachine interface

#endif // __IASSETSTATEMACHINE__
