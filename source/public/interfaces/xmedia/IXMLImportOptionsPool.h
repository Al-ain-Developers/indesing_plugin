//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportOptionsPool.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLImportOptionsPool__
#define __IXMLImportOptionsPool__


#include "IPMUnknown.h"
#include "XMLID.h"


/** Interface for packaging and retrieving data using key value pairs. Primarily used for storing 
	XML import options.

	To have this interface store data for you, set up your data such that you can identify it with 
	a key value pair. Call SetKeyValue() to add data into this interface for storage. Use 
	GetValue() to retrieve data using your key. Keys should be non-namespace XML names that 
	uniquely identifies it.

	The client is responsible for interpreting the data set and retrieved. This interface merely 
	stores the information for you. If the plug-in is missing, the data will continue to be 
	preserved until at a later time it is either deleted or cleared by a plug-in.

	To store a snapshot of the data in the interface, call Get() to retrieve a data block that 
	contains information stored within the interface. Later, call Set() to restore the data in 
	the interface
*/
class IXMLImportOptionsPool : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLIMPORTOPTIONSPOOL };

	/** type to use for key specification */
	typedef WideString KeyType;

	/** Retrieve a bool value given a key
		@param key key to look up a value with
		@value [OUT] receives retrieved value
		@return bool16 kTrue if successful; kFalse if failed, either key not found or failed to 
		convert data to specified type
	*/
	virtual bool16 GetValue(const KeyType& key, bool16& value) const = 0;

	/** Retrieve a int32 value given a key
		@param key key to look up a value with
		@value [OUT] receives retrieved value
		@return bool16 kTrue if successful; kFalse if failed, either key not found or failed to 
		convert data to specified type
	*/
	virtual bool16 GetValue(const KeyType& key, int32& value) const = 0;

	/** Retrieve a string value given a key
		@param key key to look up a value with
		@value [OUT] receives retrieved value
		@return bool16 kTrue if successful; kFalse if failed, because key not found
	*/
	virtual bool16 GetValue(const KeyType& key, WideString& value) const = 0;

	/** Set (if key already exists) or add (if key does not exist) the given key value pair
		@param key key to use
		@param value value to bind with key
		@return bool16 kTrue if key already exists; kFalse if key did not exist
	*/
	virtual bool16 SetKeyValue(const KeyType& key, bool16 value) = 0;

	/** Set (if key already exists) or add (if key does not exist) the given key value pair
		@param key key to use
		@param value value to bind with key
		@return bool16 kTrue if key already exists; kFalse if key did not exist
	*/
	virtual bool16 SetKeyValue(const KeyType& key, int32 value) = 0;

	/** Set (if key already exists) or add (if key does not exist) the given key value pair
		@param key key to use
		@param value value to bind with key
		@return bool16 kTrue if key already exists; kFalse if key did not exist
	*/
	virtual bool16 SetKeyValue(const KeyType& key, const WideString& value) = 0;

	/** Remove the entry with the given key
		@param key key to look up
		@return bool16 kTrue if key found; kFalse if key not found
	*/
	virtual bool16 RemoveKey(const KeyType& key) = 0;

	/** Set the data used in this to the given data block. All previous data stored in this will 
		be deleted. Data in the given data block will be extracted and stored in this
		@param data extract new data from here
		@return ErrorCode error code from extraction. If not kSuccess, old data will remain
	*/
	virtual ErrorCode Set(const WideString& data) = 0;

	/** Take the data stored in this and package it as a data block
		@param [OUT] receives packaged data within this
	*/
	virtual void Get(WideString& data) const = 0;

	/** Erase all data stored in this
	*/
	virtual void Clear(void) = 0;
};


#endif	// __IXMLImportOptionsPool__

