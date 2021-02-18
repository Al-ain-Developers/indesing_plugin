//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistK2Types.h $
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

#ifndef __PersistK2__
#define __PersistK2__

#include "IPMStream.h"
#include "K2Pair.h"
#include "KeyValuePair.h"
#include "K2Vector.h"

/**
	Serializer template specializations for K2 types. These structs follow the recipe for implementing 
	serialization utilities for parameterized types as outlined in IPMStream.h. 

	Users of these utilities need not concern themselves with these implementation specifics. They can simply make
	calls such as Persist::Read (stream, myK2Pair) or Persist::Write (stream, myK2Vector).
*/

namespace Persist
{

	/**
		Specializes template class Serializer for a K2Pair
	*/
	template <typename _T1, typename _T2>
	struct Serializer < K2Pair<_T1, _T2> >
	{
		inline static void Read (IPMStream* stream, K2Pair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsReading());

			Persist::Read (stream, p.first);
			Persist::Read (stream, p.second);
		}

		inline static void Write (IPMStream* stream, const K2Pair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsWriting());

			Persist::Write (stream, p.first);
			Persist::Write (stream, p.second);
		}
	};

	/**
		Specializes template class Serializer for a KeyValuePair
	*/
	template <typename _T1, typename _T2>
	struct Serializer < KeyValuePair<_T1, _T2> >
	{
		inline static void Read (IPMStream* stream, KeyValuePair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsReading());

			Persist::Read (stream, p.fKey);
			Persist::Read (stream, p.fValue);
		}

		inline static void Write (IPMStream* stream, const KeyValuePair<_T1, _T2>& p)
		{
			ASSERT (stream && stream->IsWriting());

			Persist::Write (stream, p.fKey);
			Persist::Write (stream, p.fValue);
		}
	};

	/**
		Specializes template class Serializer for a K2Vector
	*/
	template <typename T>
	struct Serializer < K2Vector<T> >
	{
		inline static void Read (IPMStream* stream, K2Vector<T>& v)
		{
			ASSERT (stream && stream->IsReading());

			v.clear();

			int32 size;
			Persist::Read (stream, size);

			T t;
			v.resize(size, t);
			for (typename K2Vector<T>::iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Read(stream,  *i);
			}
		}

		inline static void Write (IPMStream* stream, const K2Vector<T>& v)
		{
			ASSERT (stream && stream->IsWriting());

			const int32 size = v.size();
			Persist::Write (stream, size);

			for (typename K2Vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Write(stream,  *i);
			}
		}
	};
}

#endif
