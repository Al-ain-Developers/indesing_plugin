//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBoolData.h $
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
//========================================================================================

#pragma once
#ifndef __IBoolData__
#define __IBoolData__

#include "IPMUnknown.h"
#include "CommandID.h"

/** Data interface for storing booleans.
	@ingroup arch_coredata 
*/
class IBoolData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBOOLDATA };

	typedef bool16		ValueType;

	/** 	Return the value stored by this interface
		@return The stored boolean
	*/
	ValueType Get() const
		{ return GetBool(); }
		
	/** 	Store a new boolean value into this interface.
		@param b The new boolean to store
	*/
	virtual void Set(ValueType b) = 0;
	
	/** 	Return the value stored by this interface
		@return The stored boolean
	*/
	virtual bool16 GetBool() const = 0;
	
};


#endif // __IBoolData__
