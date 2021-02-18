//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IWindowPortData.h $
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
#ifndef __IWindowPortData_h__
#define __IWindowPortData_h__

#include "IPMUnknown.h"
#include "GraphicsID.h"

/**
 Data interface for storing a system window and port
 */
class IWindowPortData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWINDOWPORTDATA };

	/**
	 Sets the system window and port stored by this object
	 
	 @param window		IN The system window to store
	 @param port		IN The system port to store
	 */
	virtual void 		Set(SysWindow window, SysPort port) = 0;
	
	/**
	 Returns the system window stored by this object
	 
	 @return The system window stored by this object
	 */
	virtual SysWindow	GetWindow() const = 0;

	/**
	 Returns the system port stored by this object
	 
	 @return The system port stored by this object
	 */
	virtual SysPort		GetPort() const = 0;
};

#endif