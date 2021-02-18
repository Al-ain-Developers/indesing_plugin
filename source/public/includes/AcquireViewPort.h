//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AcquireViewPort.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __AcquireViewPort__
#define __AcquireViewPort__

#include "IViewPort.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/**
 A object that can be used to acquire the focus for a given view port. 
 BeginPortFocus is called when the object is initialized and EndPortFocus 
 is called when the object is destroyed.
 
 @see IViewPort
 */
class PUBLIC_DECL AcquireViewPort
{
public:
	// ----- Initialization -----
	
	/**
	 Constructs an AcquireViewPort object given a viewport
	 
	 @param unknown		The viewport to acquire (assumed to aggregate IViewPort)
	 */
	AcquireViewPort(IPMUnknown* unknown);
	
	/**
	 Destructor
	 */
	virtual ~AcquireViewPort();

private:
	IViewPort*				fViewPort;
};

#pragma export off

#endif
