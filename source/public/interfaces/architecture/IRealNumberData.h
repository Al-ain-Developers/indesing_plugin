//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRealNumberData.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IRealNumberData__
#define __IRealNumberData__

#include "IPMUnknown.h"
#include "CommandID.h"

/**  Data interface for storing a floating-point value (PMReal). Note that the most common implementation of this interface
	does not set the PMReal to anything by default, so it's important that there be a call to Set before any call to GetRealNumber.
	@ingroup arch_coredata 
*/
class IRealNumberData : public IPMUnknown {
public:
	enum	{ kDefaultIID = IID_IREALNUMBERDATA };

	/**	Set the new PMReal value.
		@param theValue specifies the new PMReal value to set.
		@see also PMReal
	*/
	virtual void Set(const PMReal& theValue) = 0;

	/**	Returns the current PMReal value.
	*/
	virtual const PMReal GetRealNumber() const = 0;
};


#endif // __IRealNumberData__
