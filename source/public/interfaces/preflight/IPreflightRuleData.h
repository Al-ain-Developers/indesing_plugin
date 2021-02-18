//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleData.h $
//  
//  Owner: SusanCL
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include <vector>

#include "ScriptData.h"

/**	This is the primary parameter data interface for preflight rules. It's dictionary based
	so we don't have to deal with versioning so much. It uses ScriptData as its internal data
	representation for the rule parameter data.

	@see PreflightRuleDataHelper
*/
class IPreflightRuleData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEDATA };

public:
	typedef PMString Key;
	typedef ScriptData::ScriptDataType	ValueType;

	/**	Returns an invalid key. (Not sure if we need this.)
	*/
	virtual	Key	AnInvalidKey () const = 0;

	//_______________________________________________________________________________
	// Read access
	//_______________________________________________________________________________

	/**	Returns whether the key exists.
		@param k is the key.
		@return True if it exists; false otherwise.
	*/
	virtual bool KeyExists(const Key& k) const = 0;

	/**	The data type associated with the data for this key.
		@param k is the key.
		@return the data type. The data type is one of the types supported by ScriptData::ScriptDataType.
		@see ScriptData.h
	*/
	virtual ValueType GetValueType(const Key& k) const = 0;
	/**	Retrieve the data associated with specified key.
		@param k is the key.
		@defData is the default data to return if key does not exist.
		@data is the data associated with the specified to be returned.
		@pExist if not nil, will return a boolean indicates whether or not the key and data pair exists.
		@see ScriptData.h
	*/
	virtual void GetData (const Key& k, const ScriptData& defData, ScriptData& data, bool* pExist = nil) const = 0;
	/**	Returns a list of the keys currently accessible. Note that the order of the keys returns does not
		reflect the order of the keys maintained internally.
		@param keyList is the list of keys to be returned.
	*/
	virtual void GetAllKeys (std::vector<Key>& keyList) const = 0;

	/**	Returns a single key. If there are more than one entry, it returns the first available key.
		If the data store is empty, it returns AnInvalidKey ().
		@return a single key.
	*/
	virtual Key GetKey () const = 0;

	//_______________________________________________________________________________
	// Write access
	//_______________________________________________________________________________

	/**	Sets data.
		@param key is the specified key to be associated with the data.
		@data is the data to set.
	*/
	virtual void SetData (const Key& k, const ScriptData& data) = 0;
	/**	Remove the data entry associated with the specified key.
		@param k is the specified key.
	*/
	virtual void RemoveKey(const Key& k) = 0;
	/**	Remove all data entries.
	*/
	virtual void RemoveAllKeys() = 0;

	/**	Copy data from another IPreflightRuleData interface.
		@param iSrc is the interface to copy from.
	*/
	virtual void CopyFrom(const IPreflightRuleData* iSrc) = 0;

	//_______________________________________________________________________________
	// Utility
	//_______________________________________________________________________________

	/** Determines whether the dictionaries are the same.
		@param iOther IN The other dictionary to compare against.
		@return kTrue if they're equal; kFalse otherwise.
	*/
	virtual bool IsEqual(const IPreflightRuleData* iOther) const = 0;
};
