//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistSTLTypes.h $
//  
//  Owner: Abhishek Gulati
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

#ifndef __PersistSTL__
#define __PersistSTL__

#include "IPMStream.h"
#include <map>
#include <string>
#include <vector>

/**
	Serializer and Read/Write template specializations for STL types. These structs and functions follow the recipes for implementing 
	serialization utilities for parameterized and non-parameterized types respectively as outlined in IPMStream.h. 

	Users of these utilities need not concern themselves with these implementation specifics. They can simply make
	calls such as Persist::Read (stream, mySTLPair) or Persist::Write (stream, mySTLString).
*/

namespace Persist
{
	/**
		Specializes template class Serializer for an std::pair
	*/
	template <typename _T1, typename _T2>
	struct Serializer < std::pair<_T1, _T2> >
	{
		inline static void Read (IPMStream* stream, std::pair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsReading());

			Persist::Read (stream, p.first);
			Persist::Read (stream, p.second);
		}

		inline static void Write (IPMStream* stream, const std::pair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsWriting());

			Persist::Write (stream, p.first);
			Persist::Write (stream, p.second);
		}
	};

	/**
		Specializes template function Read for an std::string.

		@param	stream	IN	The stream to read from.
		@param	str	    OUT	The std::string being to read into.
	*/
	template <>
	inline void Read (IPMStream* stream, std::string& str)
	{
		ASSERT (stream && stream->IsReading());

		int32 size;
		Persist::Read(stream, size);

		str.resize (size);

		// Get the pointer to the start of the string buffer.
		char* buf = &str[0];
		stream->XferByte	((uchar*)buf, size);
	}

	/**
		Specializes template function Write for an std::string.

		@param	stream	IN	The stream being written to.
		@param	str	    IN	The std::string being written.
	*/
	template <>
	inline void Write (IPMStream* stream, const std::string& str)
	{
		ASSERT (stream && stream->IsWriting());

		int32 size = (int32)str.size();
		Persist::Write(stream, size);

		// Get the pointer to the start of the string buffer.
		const char* buf = &str[0];
		stream->XferByte ((uchar*)buf, size);
	}

	/**
		Specializes template class Serializer for an std::vector
	*/
	template <typename T>
	struct Serializer < std::vector<T> >
	{
		inline static void Read (IPMStream* stream, std::vector<T>& v)
		{
			ASSERT (stream && stream->IsReading());

			v.clear();

			int32 size;
			Persist::Read (stream, size);

			v.resize(size);
			for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Read(stream,  *i);
			}
		}

		inline static void Write (IPMStream* stream, const std::vector<T>& v)
		{
			ASSERT (stream && stream->IsWriting());

			const int32 size = static_cast<int32>(v.size());
			Persist::Write (stream, size);

			for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Write(stream, *i);
			}
		}
	};

	/**
		Specializes template class Serializer for an std::map
	*/
	template <typename _KeyType, typename _DataType>
	struct Serializer < std::map<_KeyType, _DataType> >
	{
		inline static void Read (IPMStream* stream, std::map<_KeyType, _DataType>& m)
		{
			ASSERT (stream && stream->IsReading());

			m.clear();

			int32 size;
			Persist::Read (stream, size);

			while(size--)
			{
				_KeyType key;
				Persist::Read (stream, key);

				_DataType data;
				Persist::Read (stream, data);

				const bool unique = m.insert (std::pair<const _KeyType, _DataType> (key, data)).second;
				#pragma unused(unique) // Avoid 'unused variable' warning in release builds.
				ASSERT_MSG (unique, "Duplicate key found while deserializing a map.");
			}
		}

		inline static void Write (IPMStream* stream, const std::map<_KeyType, _DataType>& m)
		{
			ASSERT (stream && stream->IsWriting());

			const int32 size = (int32)m.size();
			Persist::Write (stream, size);

			for (typename std::map<_KeyType, _DataType>::const_iterator i = m.begin(); i != m.end(); ++i)
			{
				const _KeyType& key = i->first;
				Persist::Write(stream, key);

				const _DataType& data = i->second;
				Persist::Write (stream, data);
			}
		}
	};
}

#endif
