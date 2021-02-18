//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DigitalPublishingDictionary.h $
//  
//  Owner: Adobe Systems Inc.
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once

#include "PMRect.h"
#include "IDFile.h"

#include <boost/shared_ptr.hpp>

namespace id_digpub
{

/**
 Forward declare of Object type used by DigitalPublishing dictionaries
 */
class Object;
typedef boost::shared_ptr<Object> ObjectPtr;

class Object
{
public:
	/**
	 Object types
	 */
	enum Type
	{
		kBoolean,		// bool16
		kInteger,		// int32
		kLongInteger,	// int64
		kReal,			// PMReal
		kString,		// WideString
		kFile,			// IDFile
		kDate,			// IDTime
		kDictionary,	// Object
		kArray,			// Object
		
		kInvalidType = 0xffffffff
	};
	
	virtual ~Object() {}
	
	/**
	 @return the type of the object
	 */
	virtual Type GetType() const = 0;
	
	/**
	 Factory method for creating an instance of a boolean object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateBoolean(bool16 value) const = 0;
	
	/**
	 Factory method for creating an instance of an integer object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateInteger(int32 value) const = 0;

	/**
	 Factory method for creating an instance of a long integer object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateLongInteger(int64 value) const = 0;

	/**
	 Factory method for creating an instance of a real (floating point) object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateReal(PMReal const &value) const = 0;

	/**
	 Factory method for creating an instance of a string object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateString(WideString const &value) const = 0;

	/**
	 Factory method for creating an instance of a file object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateFile(IDFile const &value) const = 0;
	
	/**
	 Factory method for creating an instance of a date object.
	 
	 @param value		The object's initial value
	 @return a new object instance
	 */
	virtual ObjectPtr CreateDate(IDTime const &value) const = 0;

	/**
	 Factory method for creating an instance of a dictionary object.
	 
	 @return a new object instance
	 */
	virtual ObjectPtr CreateDictionary() const = 0;

	/**
	 Factory method for creating an instance of an array object.
	 
	 @param size		The array's initial size
	 @return a new object instance
	 */
	virtual ObjectPtr CreateArray(size_t size = 0) const = 0;

	/**
	 Boolean getter. Assumes object is a boolean. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetBoolean(bool16 &value) const = 0;
	
	/**
	 Boolean setter. Assumes object is a boolean. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetBoolean(bool16 value) = 0;
	
	/**
	 Integer getter. Assumes object is an integer. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetInteger(int32 &value) const = 0;

	/**
	 Integer setter. Assumes object is an integer. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetInteger(int32 value) = 0;
	
	/**
	 Long integer getter. Assumes object is a long integer. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetLongInteger(int64 &value) const = 0;

	/**
	 Long integer setter. Assumes object is a long integer. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetLongInteger(int64 value) = 0;
	
	/**
	 Real getter. Assumes object is a real (floating point value). Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetReal(PMReal &value) const = 0;

	/**
	 Real setter. Assumes object is a real (floating point value). Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetReal(PMReal const &value) = 0;
	
	/**
	 String getter. Assumes object is a string. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetString(WideString &value) const = 0;

	/**
	 String setter. Assumes object is a string. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetString(WideString const &value) = 0;
	
	/**
	 File getter. Assumes object is a file. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetFile(IDFile &value) const = 0;
	
	/**
	 File setter. Assumes object is a file. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetFile(IDFile const &value) = 0;
	
	/**
	 Date getter. Assumes object is a date. Fails if not.
	 
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	virtual bool GetDate(IDTime &value) const = 0;
	
	/**
	 Date setter. Assumes object is a date. Fails if not.
	 
	 @param value		The object's new value
	 @return true if the value was set successfully
	 */
	virtual bool SetDate(IDTime const &value) = 0;
	
	/**
	 Retrieves the set of keys stored in the object, which is assumed to be a dictionary.
	 Fails if object isn't a dictionary.
	 
	 @param keys		Out param that receives the list of defined keys
	 @return true if the list of keys was retrieved successfully
	 */
	virtual bool GetDictionaryKeys(K2Vector<WideString> &keys) const = 0;
	
	/**
	 Retrieves a value from a dictionary object. Fails if the key isn't defined or
	 if the object isn't a dictionary (use GetType to distinguish).
	 
	 @param key			The key whose value is to be retrieved
	 @param value		Out param to receive the object associated with key
	 @return true if the value was successfully retrieved
	 */
	virtual bool GetDictionaryValue(WideString const &key, ObjectPtr &value) const = 0;
	
	/**
	 Sets a value in a dictionary object. Fails if the object isn't a dictionary.
	 
	 Note: Any value currently associated with key will be replaced
	 
	 @param key			The key whose value is to be set
	 @param value		The value to associate with key
	 @return true if the value was successfully set
	 */
	virtual bool SetDictionaryValue(WideString const &key, ObjectPtr const &value) = 0;
	
	/**
	 Removes a key from a dictionary object. Fails if the object isn't a dictionary.
	 
	 Note: Return value does not reflect whether a key was actually removed, only if
	 the operation itself was successful (i.e., this object is a dictioanry)
	 
	 @param key			The key to remove
	 @return true if the operation was successful
	 */
	virtual bool RemoveDictionaryValue(WideString const &key) = 0;
	
	/**
	 Clears a dictionary object. Fails if the object isn't a dictionary.
	 
	 @return true if the operation was successful
	 */
	virtual bool ClearDictionary() = 0;
	
	/**
	 Retrieves the size of an array object. Fails if the object is not an array.
	 
	 @param size		Out param that receives the size of the array
	 @return true if the size of the array was received successfully
	 */
	virtual bool GetArraySize(size_t &size) const = 0;
	
	/**
	 Sets the size of an array object. Fails if the object is not an array.
	 
	 Note: If the array is made larger, it is padded with invalid (null) objects.
	 These are not considered valid objects and care should be exercised when
	 doing this. Recommended use is to immediately fill open slots with valid
	 values or to use the simpler AppendArrayValue method instead.
	 
	 @param size		The new size of the array
	 @return true if the array was successfully resized
	 */
	virtual bool SetArraySize(size_t size) = 0;
	
	/**
	 Retrieves the nth value in an array object. Fails if the object is not an array
	 or if the index is invalid.
	 
	 @param index		The index of the value to retrieve
	 @param value		Out param to receive the object at index
	 @return true if the value was successfully retrieved
	 */
	virtual bool GetNthArrayValue(size_t index, ObjectPtr &value) const = 0;
	
	/**
	 Sets the nth value in an array object. Fails if the object is not an array,
	 if the index is invalid, or if the value is invalid (null).
	 
	 @param index		The index at which to store the value
	 @param value		The value to be stored
	 @return true if the value was successfully set
	 */
	virtual bool SetNthArrayValue(size_t index, ObjectPtr const &value) = 0;
	
	/**
	 Appends a value to an array object. Fails if the object is not an array or
	 if the value is invalid (null).
	 
	 @param value		The value to be appended
	 @return true if the value was successfully appended
	 */
	virtual bool AppendArrayValue(ObjectPtr const &value) = 0;

	// Convenience methods for working with dictionaries
	
	/**
	 Boolean getter. Assumes object is a dictionary and the child value indexed
	 by key is a boolean. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetBooleanValue(WideString const &key, bool16 &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetBoolean(value);
	}
	
	/**
	 Boolean setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a boolean value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetBooleanValue(WideString const &key, bool16 value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetBoolean(value)) ||
			SetDictionaryValue(key, CreateBoolean(value))
		;
	}
	
	/**
	 Integer getter. Assumes object is a dictionary and the child value indexed
	 by key is an integer. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetIntegerValue(WideString const &key, int32 &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetInteger(value);
	}
	
	/**
	 Integer setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a integer value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetIntegerValue(WideString const &key, int32 value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetInteger(value)) ||
			SetDictionaryValue(key, CreateInteger(value))
		;
	}
	
	/**
	 Long integer getter. Assumes object is a dictionary and the child value indexed
	 by key is a long integer. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetLongIntegerValue(WideString const &key, int64 &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetLongInteger(value);
	}
	
	/**
	 Long integer setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a long integer value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetLongIntegerValue(WideString const &key, int64 value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetLongInteger(value)) ||
			SetDictionaryValue(key, CreateLongInteger(value))
		;
	}
	
	/**
	 Real getter. Assumes object is a dictionary and the child value indexed
	 by key is a real (floating point value). Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetRealValue(WideString const &key, PMReal &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetReal(value);
	}
	
	/**
	 Real (floating point) setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a real value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetRealValue(WideString const &key, PMReal const &value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetReal(value)) ||
			SetDictionaryValue(key, CreateReal(value))
		;
	}

	/**
	 String getter. Assumes object is a dictionary and the child value indexed
	 by key is a string. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetStringValue(WideString const &key, WideString &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetString(value);
	}
	
	/**
	 String setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a string value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetStringValue(WideString const &key, WideString const &value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetString(value)) ||
			SetDictionaryValue(key, CreateString(value))
		;
	}
	
	/**
	 File getter. Assumes object is a dictionary and the child value indexed
	 by key is a file. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetFileValue(WideString const &key, IDFile &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetFile(value);
	}
	
	/**
	 File setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a file value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetFileValue(WideString const &key, IDFile const &value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetFile(value)) ||
			SetDictionaryValue(key, CreateFile(value))
		;
	}
	
	/**
	 Date getter. Assumes object is a dictionary and the child value indexed
	 by key is a date. Fails if not.
	 
	 @param key			The key to retrieve
	 @param value		Out param to receive the object's value
	 @return true if the value was retrieved successfully
	 */
	bool GetDateValue(WideString const &key, IDTime &value) const
	{
		ObjectPtr valueObj;
		
		return GetDictionaryValue(key, valueObj) && valueObj->GetDate(value);
	}
	
	/**
	 Date setter. Assumes object is a dictionary. Fails if not.
	 
	 Note: If a date value already exists under key in the dictionary,
	 its value is replaced; otherwise a new value is created and stored.
	 
	 @param key			The key to set
	 @param value		The value to be stored
	 @return true if the value was set successfully
	 */
	bool SetDateValue(WideString const &key, IDTime const &value)
	{
		ObjectPtr valueObj;
		
		return 
			(GetDictionaryValue(key, valueObj) && valueObj->SetDate(value)) ||
			SetDictionaryValue(key, CreateDate(value))
		;
	}
	
	/**
	 Retrieves the nth real (floating point) value from an array object. Fails
	 if object is not an array, if index is out of range, or value at index is
	 not a real.
	 
	 @param index		The index to query
	 @param value		Out param to receive the real value
	 @return true if the value was retrieved
	 */
	bool GetNthArrayRealValue(size_t index, PMReal &value) const
	{
		ObjectPtr nthValue;
		
		return GetNthArrayValue(index, nthValue) && nthValue->GetReal(value);
	}
	
	/**
	 Retrieves the nth file value from an array object. Fails if object is not an 
	 array, if index is out of range, or value at index is not a file.
	 
	 @param index		The index to query
	 @param value		Out param to receive the file value
	 @return true if the value was retrieved
	 */
	bool GetNthArrayFileValue(size_t index, IDFile &value) const
	{
		ObjectPtr nthValue;
		
		return GetNthArrayValue(index, nthValue) && nthValue->GetFile(value);
	}
	
	/**
	 Factory method for creating an object to represent a PMPoint
	 
	 @param x		The point's x value
	 @param y		The point's y value
	 @return the new object instance
	 */
	ObjectPtr CreatePointObject(PMReal const &x, PMReal const &y) const
	{
		ObjectPtr pointArray = CreateArray(2);
		
		if (pointArray)
		{
			pointArray->SetNthArrayValue(0, CreateReal(x));
			pointArray->SetNthArrayValue(1, CreateReal(y));
		}
		
		return pointArray;
	}

	/**
	 Factory method for creating an object to represent a PMPoint
	 
	 @param r		The point whose value is used to create the object
	 @return the new object instance
	 */
	ObjectPtr CreatePMPointObject(PMPoint const &p) const
	{
		return CreatePointObject(p.X(), p.Y());
	}
	
	/**
	 Retrieves the PMPoint value associated with a key from a dictionary.
	 Fails if object is not a dictionary or if value at key is undefined
	 or invalid.
	 
	 @param key		The key to query
	 @param bounds	Out param to receive the rectangle value
	 @return true if the rectangle was retrieved successfully
	 */
	bool GetPMPointValue(WideString const &key, PMPoint &point) const
	{
		ObjectPtr pointArray;
		
		return
			GetDictionaryValue(key, pointArray) &&
			pointArray->GetNthArrayRealValue(0, point.X()) &&
			pointArray->GetNthArrayRealValue(1, point.Y())
		;
	}
	
	/**
	 Factory method for creating an object to represent a PMRect
	 
	 @param left	The rectangle's left value
	 @param top		The rectangle's top value
	 @param right	The rectangle's right value
	 @param bottom	The rectangle's bottom value
	 @return the new object instance
	 */
	ObjectPtr CreateRectObject(PMReal const &left, PMReal const &top, PMReal const &right, PMReal const &bottom) const
	{
		ObjectPtr rectArray = CreateArray(4);
		
		if (rectArray)
		{
			rectArray->SetNthArrayValue(0, CreateReal(left));
			rectArray->SetNthArrayValue(1, CreateReal(top));
			rectArray->SetNthArrayValue(2, CreateReal(right));
			rectArray->SetNthArrayValue(3, CreateReal(bottom));
		}
		
		return rectArray;
	}

	/**
	 Factory method for creating an object to represent a PMRect
	 
	 @param r		The rectangle whose value is used to create the object
	 @return the new object instance
	 */
	ObjectPtr CreatePMRectObject(PMRect const &r) const
	{
		return CreateRectObject(r.Left(), r.Top(), r.Right(), r.Bottom());
	}
	
	/**
	 Retrieves the PMRect value associated with a key from a dictionary.
	 Fails if object is not a dictionary or if value at key is undefined
	 or invalid.
	 
	 @param key		The key to query
	 @param bounds	Out param to receive the rectangle value
	 @return true if the rectangle was retrieved successfully
	 */
	bool GetPMRectValue(WideString const &key, PMRect &bounds) const
	{
		ObjectPtr rectArray;
		
		return
			GetDictionaryValue(key, rectArray) &&
			rectArray->GetNthArrayRealValue(0, bounds.Left()) &&
			rectArray->GetNthArrayRealValue(1, bounds.Top()) &&
			rectArray->GetNthArrayRealValue(2, bounds.Right()) &&
			rectArray->GetNthArrayRealValue(3, bounds.Bottom())
		;
	}
	
	/**
	 Factory method for creating an asset object. An asset is a 3-tuple 
	 comprised of a file, an ID, and a tag. The returned object is a
	 dictionary.
	 
	 @param file		The file portion of the asset
	 @param id			The asset's ID
	 @param tag			The asset's tag (optional)
	 @return the new object
	 */
	ObjectPtr CreateAssetObject(IDFile const &file, WideString const &id, WideString const &tag = WideString()) const
	{
		ObjectPtr assetObject = CreateDictionary();
		
		if (assetObject)
		{
			assetObject->SetFileValue(WideString("File"), file);
			assetObject->SetStringValue(WideString("ID"), id);
			
			if (!tag.empty())
			{
				assetObject->SetStringValue(WideString("Tag"), tag);
			}
		}
		
		return assetObject;
	}
	
	/**
	 Convenience method for retrieving the values for an asset from an object,
	 which is assumed to be a dictionary with File and ID values. Fails if not.
	 
	 Note: This assumes that the assets used by calling code require both the
	 File and ID values. If this is not the case, you should consider simply
	 calling yourAssetObject->GetFileValue(WideString("File"), file).
	 
	 @param file			Out param to receive the file portion of this asset
	 @param id				Out param to receive the asset's ID
	 @param tag				Out param to receive the asset's tag
	 @return true if the asset's values were successfully retrieved
	 */
	bool GetAssetObjectValues(IDFile &file, WideString &id, WideString &tag) const
	{
		if (GetFileValue(WideString("File"), file) && GetStringValue(WideString("ID"), id))
		{
			if (!GetStringValue(WideString("Tag"), tag))
			{
				tag = WideString();
			}
			
			return true;
		}
		
		return false;
	}
};

}
