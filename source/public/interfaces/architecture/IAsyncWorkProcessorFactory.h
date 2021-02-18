//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAsyncWorkProcessorFactory.h $
//  
//  Owner: Paul Messmer
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
#ifndef __IASYNCWORKPROCESSORFACTORY__
#define __IASYNCWORKPROCESSORFACTORY__

#include "AsyncWork.h"
#include "AppFrameworkID.h"


//--------------------------------------------------------------------------------------
/**
	this interface is on your factory boss that you register with the service registry
*/
class IAsyncWorkProcessorFactory : public IPMUnknown	
{														
public:

	enum { kDefaultIID = IID_IASYNCWORKPROCESSORFACTORY };

	enum LoadModel
	{
		kComputationBound = 1,		// your code does mostly computation
		kExternalWait = 2,			// your code mostly waits on I/O or external things
		kMixed = 3					// you have no clue what your code does
	};

	/**
		@return true if the underlying processor is thread safe, false otherwise
	*/
	virtual bool IsThreadable () const = 0;									

	/**
		@return what type of work you do to help the architecture load balance
	*/
	virtual LoadModel GetLoadModel () const = 0;

	/**
		@return the maximum number of processor instances the architecture is ever
		allowed to create (or maybe it's just recommended).  Not that if !IsThreadable(), this will be 1.
	*/
	virtual uint32 GetMaximumInstances (uint32 nCPUCores) const = 0;

	/**
		Create an instance of your work processor that will subsequently be called
		to process packets.  Note that is IsThreadable(), the thread context in which
		AsyncWorkProcessor::ProcessPacket() gets called may be different from
		call to call and also different than the creation thread context.
	*/
	virtual AsyncWorkProcessor *CreateProcessorInstance () const = 0;
};

//--------------------------------------------------------------------------------------

#endif // __IASYNCWORKPROCESSORFACTORY__
