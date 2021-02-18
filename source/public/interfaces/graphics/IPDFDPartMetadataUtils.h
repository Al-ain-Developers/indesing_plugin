//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFDPartMetadataUtils.h $ 
//   
//  Owner: Sameer Manuja
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//   
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2010 Adobe Systems Incorporated. All Rights Reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//   
//======================================================================================== 

#pragma once
#ifndef __IPDFDPartMetadataUtils__
#define __IPDFDPartMetadataUtils__

#include "PDFID.h"

typedef uint32 CosObjID;
#define kInvalidCosObjID	(0)

// opaque types
typedef struct OPAQUE_64_BITS CosObj;

typedef ConstCString NameType; /* utf-8 encoded name */

class IPDFDPartMetadataUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFDPARTMETADATAUTILS };

		/**
			Creates a new dictionary object.
			@param int32 initialSize: initial size of the dictionary.
			The dictionary can grow dynamically as needed.
			@return CosObjID: the dictionary object identifier.
		*/
		virtual CosObjID CreateNewDict(int32 initialSize) = 0;

		/**
			Adds a boolean value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param bool16 value: the boolean value to put.
		*/
		virtual void PutBool(CosObjID dict, NameType key, bool16 value) = 0;

		/**
			Adds an integer value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param int32 value: the integer value to put.
		*/
		virtual void PutInt(CosObjID dict, NameType key, int32 value) = 0;

		/**
			Adds a float value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param float value: the float value to put.
		*/
		virtual void PutFloat(CosObjID dict, NameType key, float value) = 0;

		/**
			Adds a name value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param NameType value: the name value to put.
		*/
		virtual void PutName(CosObjID dict, NameType key, NameType value) = 0;

		/**
			Adds a string value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param const PMString& value: the string value to put.
		*/
		virtual void PutString(CosObjID dict, NameType key, const PMString& value) = 0;

		/**
			Adds a dictionary value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param CosObjID value: the dictionary object value to put.
		*/
		virtual void PutDict(CosObjID dict, NameType key, CosObjID value) = 0;

		/**
			Adds an array value to the dictionary object.
			@param CosObjID dict: the dictionary object identifier.
			@param NameType key: the name of the key.
			@param CosObjID value: the array object value to put.
		*/
		virtual void PutArray(CosObjID dict, NameType key, CosObjID value) = 0;

		/**
			Creates a new array object.
			@param int32 initialSize: initial size of the array.
			The array can grow dynamically as needed.
			@return CosObjID: the array object identifier.
		*/
		virtual CosObjID CreateNewArray(int32 initialSize) = 0;

		/**
			Gets the size of the array object.
			@param CosObjID arry: the array object identifier.
			@return int32: the size of the array object.
		*/
		virtual int32 GetArraySize(CosObjID arry) const = 0;

		/**
			Puts a boolean value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param bool16 value: the boolean value to put.
		*/
		virtual void PutBool(CosObjID arry, int32 index, bool16 value) = 0;

		/**
			Puts an integer value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param int32 value: the integer value to put.
		*/
		virtual void PutInt(CosObjID arry, int32 index, int32 value) = 0;

		/**
			Puts a float value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param float value: the float value to put.
		*/
		virtual void PutFloat(CosObjID arry, int32 index, float value) = 0;

		/**
			Puts a name value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param NameType value: the name value to put.
		*/
		virtual void PutName(CosObjID arry, int32 index, NameType value) = 0;

		/**
			Puts a string value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param const PMString& value: the string value to put.
		*/
		virtual void PutString(CosObjID arry, int32 index, const PMString& value) = 0;

		/**
			Puts a dictionary value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param CosObjID value: the dictionary value to put.
		*/
		virtual void PutDict(CosObjID arry, int32 index, CosObjID value) = 0;

		/**
			Puts an array value at the specified location in the array object.
			@param CosObjID arry: the array object identifier.
			@param int32 index: location to put the value at, zero-based.
			@param CosObjID value: the array value to put.
		*/
		virtual void PutArray(CosObjID arry, int32 index, CosObjID value) = 0;

		/** Adobe internal use only. */
		virtual CosObj GetCosObjFromID(CosObjID objID) const = 0;
};

#endif
