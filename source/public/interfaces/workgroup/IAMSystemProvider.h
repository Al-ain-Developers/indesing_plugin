//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMSystemProvider.h $
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
#ifndef __IAMSYSTEMPROVIDER__
#define __IAMSYSTEMPROVIDER__

#include "IPMUnknown.h"
#include "workgroupid.h"


class IAssetMonitor;
class IAMServiceProvider;
class IAMUIServiceProvider;


/** The IAMSystemProvider provides the components for an asset management system.
*/

class IAMSystemProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSYSTEMPROVIDER };
	
	/** This method retrieves the IAssetMonitor instance if it exists.
		@return a valid pointer or nil if the AMSP does not support asset monitoring.
	*/
	virtual IAssetMonitor* GetAssetMonitor() = 0;
	
	/** This method retrieves the IAMServiceProvider.
		@return a valid pointer or nil (it is unlikely that a useful AMSP will not have an
			IAMServiceProvider).
	*/
	virtual IAMServiceProvider* GetServiceProvider() = 0;
	
	/** This method retrieves the IAMUIServiceProvider if it exists.
		@return a valid pointer or nil if the AMSP does not handle UI.
	*/
	virtual IAMUIServiceProvider* GetUIServiceProvider() = 0;
	
	/** The Init() method performs any initialization required by the IAMSystemProvider. This
		method must be called before calling any other method.
		@return a failure ErrorCode if there was an initialization error; otherwise, this method
			should return kSuccess.
	*/
	virtual ErrorCode Init() = 0;	
};

#endif // __IAMSYSTEMPROVIDER__
