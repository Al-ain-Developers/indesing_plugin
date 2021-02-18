//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistASLTypes.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//
//  Implements persistence support for ASL (Adobe Source Library) types
//
//========================================================================================

#pragma once

#ifndef __PersistASLTypes__
#define __PersistASLTypes__

#include "IPMStream.h"
#include <adobe/vector.hpp>

namespace Persist
{
	/**
		Specializes template class Serializer for an adobe::vector
	*/
	template <typename T>
	struct Serializer < adobe::vector<T> >
	{
		inline static void Read (IPMStream* stream, adobe::vector<T>& v)
		{
			ASSERT (stream && stream->IsReading());

			v.clear();

			int32 size;
			Persist::Read (stream, size);

			v.resize(size);
			for (typename adobe::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Read(stream,  *i);
			}
		}

		inline static void Write (IPMStream* stream, const adobe::vector<T>& v)
		{
			ASSERT (stream && stream->IsWriting());

			const int32 size = static_cast<int32>(v.size());
			Persist::Write (stream, size);

			for (typename adobe::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
			{
				Persist::Write(stream, *i);
			}
		}
	};
}

#endif	//__PersistASLTypes__
