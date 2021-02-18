//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IWStringData.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IWStringData__
#define __IWStringData__

#include "IPMUnknown.h"
#include "CommandID.h"

class PMString;

/**  Data interface for storing strings (like IStringData except stores a WideString).
	@ingroup arch_coredata 
*/
class IWStringData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWSTRINGDATA };

	/** Set the string value
		@param newString - new value of the string
	*/
	virtual void Set(const WideString& newString) = 0;

	/** Return the string value.
		@return value of the string
	*/
	virtual const WideString& GetString() const = 0;
};



#endif // __IWStringData__
