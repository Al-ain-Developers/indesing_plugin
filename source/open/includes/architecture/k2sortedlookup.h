//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2sortedlookup.h $
//  
//  Owner: EricM
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
#ifndef __K2SORTEDLOOKUP__
#define __K2SORTEDLOOKUP__

#ifdef ID_DEPRECATED
#include "k2sortedvector.h"


template <class KeyT, class ValueT>
class K2SortedLookup
{
	public:
		K2SortedLookup()
			{}
		K2SortedLookup(int32 chunkSize) :fKeyList(chunkSize), fValueList()
			{
                fValueList.reserve(chunkSize);
            }
		K2SortedLookup(const K2SortedLookup<KeyT, ValueT>& copy)
				:fKeyList(copy.fKeyList), fValueList(copy.fValueList)
			{}
			
		bool16 operator==(const K2SortedLookup<KeyT, ValueT>& /*other*/) const
			{ ASSERT_UNIMPLEMENTED(); return kFalse; }
		bool16 operator!=(const K2SortedLookup<KeyT, ValueT>& /*other*/) const
			{ ASSERT_UNIMPLEMENTED(); return kFalse; }
		
		const KeyT& Key(int32 i) const
			{ return fKeyList[i]; }
		const ValueT& Value(int32 i) const
			{ return fValueList[i]; }
		ValueT& Value(int32 i)
			{ return fValueList[i]; }
		void SetValue(int32 i, const ValueT& v)
			{ fValueList[i] = v; }
		
		void SetChunkSize(int32 chunk)
			{ fKeyList.SetChunkSize(chunk); fValueList.reserve(chunk); }
		void Preallocate(int32 chunk)
			{ fKeyList.Preallocate(chunk); fValueList.reserve(chunk); }
		void Clear()
			{ fKeyList.Clear(); fValueList.clear(); }
		
		void Bind(const KeyT& key, const ValueT& value);
		void Unbind(const KeyT& key);
		
		void Remove(int32 at)
			{ fKeyList.Remove(at); fValueList.erase(fValueList.begin() + at); }
		
		int32 ChunkSize() const
			{ return fKeyList.ChunkSize(); }
		int32 Length() const
			{ return fKeyList.Length(); }
		bool16 IsEmpty() const
			{ return fKeyList.IsEmpty(); }
		
		int32 Location(const KeyT& key) const
			{ return fKeyList.Location(key); }
	
	private:
		K2SortedVector<KeyT>	fKeyList;
		K2Vector<ValueT>		fValueList;
};

#define K2SortedPtrLookup K2SortedLookup
#ifdef _INCLUDE_TPP_IN_H_
	#include "k2sortedlookup.tpp"
#endif //_INCLUDE_TPP_IN_H_
#endif // ID_DEPRECATED
#endif	//  __K2SORTEDLOOKUP__
