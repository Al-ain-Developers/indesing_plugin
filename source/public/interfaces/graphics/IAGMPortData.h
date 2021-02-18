//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAGMPortData.h $
//  
//  Owner: jargast
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
//  Ports that use AGM will have this interface
//  
//========================================================================================

#pragma once
#ifndef __IAGMPortData__
#define __IAGMPortData__

#include "IPMUnknown.h"
#include "BravoForwardDecl.h"
#include "GraphicsID.h"

/**
 Simple data interface for storing an AGMPort. The port is implicitly ref 
 counted.
 */
class IAGMPortData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAGMPORTDATA };
	
	/**
	 Sets the current AGM port ptr. Implicitly adds a reference to the port.
	 
	 @param port		IN The port to store
	 */
	virtual void SetPort(AGMPort* port) = 0;

	/**
	 Returns the current port.
	 
	 @return the current port, or nil if there is no current port.
	 */
	virtual AGMPort* GetPort() const = 0;

	/**
	 Returns the port's type.
	 
	 Note: Port types are for internal use only and are intentionally not 
	 documented.
	 
	 @return the port's type
	 */
	virtual int32 GetPortType() const = 0;
};

#endif
