//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistBaseTypes.h $
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

#ifndef __PersistBasic__
#define __PersistBasic__

#include "IPMStream.h"
#include "k2VectorStreaming.h"
#include "BaseType.h"

/**
	Read/Write template specializations for base types. These functions follow the recipe for implementing 
	serialization utilities for non-parameterized types as outlined in IPMStream.h. 

	Users of these functions need not concern themselves with these implementation specifics. They can simply make
	calls such as Persist::Read (stream, myUint8) or Persist::Write (stream, myInt32).

	Note: We do not provide the same for base types that are platform-dependent, such as bool, wchar_t, size_t.
*/

namespace Persist
{
	/**
		Specializes template function Read for a uint8.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The uint8 being to read into.
	*/
	template<>
	inline void Read<uint8>(IPMStream* stream, uint8& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a uint8.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The uint8 being written.
	*/
	template<>
	inline void Write<uint8>(IPMStream* stream, const uint8& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}

	/**
		Specializes template function Read for a uint16.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The uint16 being to read into.
	*/
	template<>
	inline void Read<uint16>(IPMStream* stream, uint16& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a uint16.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The uint16 being written.
	*/
	template<>
	inline void Write<uint16>(IPMStream* stream, const uint16& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}

	/**
		Specializes template function Read for a uint32.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The uint32 being to read into.
	*/
	template<>
	inline void Read<uint32>(IPMStream* stream, uint32& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a uint32.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The uint32 being written.
	*/
	template<>
	inline void Write<uint32>(IPMStream* stream, const uint32& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}

	/**
		Specializes template function Read for an uint64.

		@param	stream	IN	The stream to read from.
		@param	i	    OUT	The int64 being to read into.
	*/
	template<>
	inline void Read<uint64>(IPMStream* stream, uint64& i)
	{
		ASSERT (stream && stream->IsReading());
		int64 temp(0);
		stream->XferInt64(temp);
		i = temp;
	}

	/**
		Specializes template function Write for an uint64.

		@param	stream	IN	The stream to write to.
		@param	i	    IN	The int32 being written.
	*/
	template<>
	inline void Write<uint64>(IPMStream* stream, const uint64& i)
	{
		ASSERT (stream && stream->IsWriting());
		// Copy to a non-const int64 to match XferID signature. 
		int64 iNonConst = i;
		stream->XferInt64(iNonConst);
	}

	/**
		Specializes template function Read for an int16.

		@param	stream	IN	The stream to read from.
		@param	i	    OUT	The int16 being to read into.
	*/
	template<>
	inline void Read<int16>(IPMStream* stream, int16& i)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, i);
	}

	/**
		Specializes template function Write for an int16.

		@param	stream	IN	The stream to write to.
		@param	i	    IN	The int16 being written.
	*/
	template<>
	inline void Write<int16>(IPMStream* stream, const int16& i)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, i);
	}

	/**
		Specializes template function Read for an int32.

		@param	stream	IN	The stream to read from.
		@param	i	    OUT	The int32 being to read into.
	*/
	template<>
	inline void Read<int32>(IPMStream* stream, int32& i)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, i);
	}

	/**
		Specializes template function Write for an int32.

		@param	stream	IN	The stream to write to.
		@param	i	    IN	The int32 being written.
	*/
	template<>
	inline void Write<int32>(IPMStream* stream, const int32& i)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, i);
	}

	/**
		Specializes template function Read for an int64.

		@param	stream	IN	The stream to read from.
		@param	i	    OUT	The int64 being to read into.
	*/
	template<>
	inline void Read<int64>(IPMStream* stream, int64& i)
	{
		ASSERT (stream && stream->IsReading());
		stream->XferInt64(i);
	}

	/**
		Specializes template function Write for an int32.

		@param	stream	IN	The stream to write to.
		@param	i	    IN	The int32 being written.
	*/
	template<>
	inline void Write<int64>(IPMStream* stream, const int64& i)
	{
		ASSERT (stream && stream->IsWriting());
		// Copy to a non-const int64 to match XferID signature. 
		int64 iNonConst = i;
		stream->XferInt64(iNonConst);
	}

	/**
		Specializes template function Read for a PMReal.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The PMReal being to read into.
	*/
	template<>
	inline void Read<PMReal>(IPMStream* stream, PMReal& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a PMReal.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The PMReal being written.
	*/
	template<>
	inline void Write<PMReal>(IPMStream* stream, const PMReal& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}

	/**
		Specializes template function Read for a PMPoint.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The PMPoint being to read into.
	*/
	template<>
	inline void Read<PMPoint>(IPMStream* stream, PMPoint& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a PMPoint.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The PMPoint being written.
	*/
	template<>
	inline void Write<PMPoint>(IPMStream* stream, const PMPoint& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}

	/**
		Specializes template function Read for a PMRect.

		@param	stream	IN	The stream to read from.
		@param	n	    OUT	The PMRect being to read into.
	*/
	template<>
	inline void Read(IPMStream* stream, PMRect& n)
	{
		ASSERT (stream && stream->IsReading());
		K2Read (stream, n);
	}

	/**
		Specializes template function Write for a PMRect.

		@param	stream	IN	The stream to write to.
		@param	n	    IN	The PMRect being written.
	*/
	template<>
	inline void Write(IPMStream* stream, const PMRect& n)
	{
		ASSERT (stream && stream->IsWriting());
		K2Write (stream, n);
	}


	/**
		Specializes template class Serializer for an IDType<T>.
	*/
	template <typename T>
	struct Serializer < IDType<T> >
	{
		inline static void Read (IPMStream* stream, IDType<T>& id)
		{
			stream->XferID(id);
		}

		inline static void Write (IPMStream* stream, const IDType<T>& id)
		{
			// Cast constness away to to match XferID signature. This should be safe since 
			//  XferID does not modify the object when the stream is being written to.
			stream->XferID(const_cast<IDType<T>&>(id));
		}
	};


	/**
		Specializes template function Read for a UTF32TextChar.

		@param	stream	IN	The stream to read from.
		@param	u	    OUT	The UTF32TextChar being to read into.
	*/
	template<>
	inline void Read<UTF32TextChar>(IPMStream* stream, UTF32TextChar& u)
	{
		ASSERT (stream && stream->IsReading());
		u.ReadWriteUTF16(stream);
	}

	/**
		Specializes template function Write for a UTF32TextChar.

		@param	stream	IN	The stream to write to.
		@param	u	    IN	The ScriptID being written.
	*/
	template<>
	inline void Write<UTF32TextChar>(IPMStream* stream, const UTF32TextChar& u)
	{
		ASSERT (stream && stream->IsWriting());
		// Cast constness away to to match XferID signature. This should be safe since 
		// ReadWriteUTF16 does not modify the object when the stream is being written to.
		UTF32TextChar& uNonConst = const_cast<UTF32TextChar&> (u);
		uNonConst.ReadWriteUTF16(stream);
	}
}

#endif
