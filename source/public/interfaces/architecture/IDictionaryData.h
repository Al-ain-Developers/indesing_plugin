//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDictionaryData.h $
//  
//  Owner: Florin Trofin
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
#ifndef __IDictionaryData__
#define __IDictionaryData__

#include "IPMUnknown.h"
#include <adobe/dictionary_fwd.hpp>
#include <adobe/name.hpp>
#include <adobe/any_regular.hpp>
#include <adobe/closed_hash.hpp>

/** Data interface for storing any name-value pairs.
	@ingroup arch_coredata 
*/
class IDictionaryData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDICTIONARYDATA };
	
	typedef adobe::name_t			KeyType;
	typedef adobe::any_regular_t	ValueType;
	typedef adobe::dictionary_t		Dictionary;

	virtual void Set(Dictionary newDict) = 0;

	virtual Dictionary Get() const = 0;

	/** Set the value.
		@param newValue -	new value of the variable
	*/
	virtual void SetValue(const KeyType& key, const ValueType& newValue) = 0;

	/** Get the value.
		@return value of the specified key
	*/
	virtual bool GetValue(const KeyType& key, ValueType& value) const = 0;
};


#endif // __IDictionaryData__
