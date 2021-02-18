//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2lookup.h $
//  
//  Owner: EricM, reimplement: Mat Marcus
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
#ifndef __K2Lookup__
#define __K2Lookup__

#ifdef ID_DEPRECATED
#include "K2Vector.h"

template <class KeyT, class ValueT>
class K2Lookup
{
	public:
		K2Lookup()
			{}
		explicit K2Lookup(int32 capacity) :fValueList(), fKeyList()
			{
                fValueList.reserve(capacity);
                fKeyList.reserve(capacity);
            }
		K2Lookup(const K2Lookup<KeyT, ValueT>& copy)
				:fValueList(copy.fValueList), fKeyList(copy.fKeyList)
			{}

		bool16 operator==(const K2Lookup<KeyT, ValueT>& other) const;
		bool16 operator!=(const K2Lookup<KeyT, ValueT>& other) const
			{ return !((*this) == other); }

		const KeyT& Key(int32 i) const
			{ return fKeyList[i]; }
		ValueT& Value(int32 i)
			{ return fValueList[i]; }
		const ValueT& Value(int32 i) const
			{ return fValueList[i]; }
		void SetValue(int32 i, const ValueT& v)
			{ fValueList[i] = v; }

		void SetChunkSize(int32 chunk)
			{ fValueList.reserve(chunk); fKeyList.reserve(chunk); }
		void Preallocate(int32 chunk)
			{ fValueList.reserve(chunk); fKeyList.reserve(chunk); }
		void Clear()
			{ fValueList.clear(); fKeyList.clear(); }

		void Bind(const KeyT& key, const ValueT& value);
		void Rebind(const KeyT& key, const ValueT& value);
		void Unbind(const KeyT& key);

		void Remove(int32 at)
			{ fValueList.erase(fValueList.begin() + at); fKeyList.erase(fKeyList.begin() + at); }

		int32 ChunkSize() const
			{ return 8; } //AW_TODO: Possibly deprecate this?
		int32 Length() const
			{ return (int32)fKeyList.size(); }
		bool16 IsEmpty() const
			{ return fKeyList.empty(); }

		int32 Location(const KeyT& key) const
			{
				typename K2Vector<KeyT>::const_iterator iter = K2find(fKeyList.begin(), fKeyList.end(), key);
				return (iter != fKeyList.end() ? iter - fKeyList.begin() : -1);
			}

	private:
		K2Vector<KeyT>	 fKeyList;
		K2Vector<ValueT> fValueList;
};

#define K2PtrLookup K2Lookup
#ifdef _INCLUDE_TPP_IN_H_
	#include "k2lookup.tpp"
#endif //_INCLUDE_TPP_IN_H_
#endif // ID_DEPRECATED
#endif //__K2Lookup__
