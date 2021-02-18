//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2lookup.tpp $
//  
//  Owner: EricM, Rewrite: Mat Marcus
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

#ifndef __K2Lookuptpp__
#define __K2Lookuptpp__

#ifdef ID_DEPRECATED
#include "k2lookup.h"

template <class KeyT, class ValueT>
bool16 K2Lookup<KeyT, ValueT>::operator==(const K2Lookup<KeyT, ValueT>& other) const
{
	if (fKeyList.size() != other.fKeyList.size())
		return kFalse;
	
	for (int32 i = (int32)(fKeyList.size() - 1); i >= 0; i--)
		{
		typename K2Vector<KeyT>::const_iterator iter = K2find(other.fKeyList.begin(), other.fKeyList.end(), fKeyList[i]);
		if (iter == other.fKeyList.end())
			return kFalse;
		else if (!(fValueList[i] == other.fValueList[iter-other.fKeyList.begin()]))		// so templates don't HAVE to have operator !=
			return kFalse;
		}
	
	return kTrue;
}



template <class KeyT, class ValueT>
void K2Lookup<KeyT, ValueT>::Bind(const KeyT& key, const ValueT& value)
{
#ifdef DEBUG
	int32	dloc = Location(key);
	
	if (dloc >= 0)
		ASSERT_FAIL("Collision in lookup");
#endif

	fKeyList.push_back(key);
	fValueList.push_back(value);
}

template <class KeyT, class ValueT>
void K2Lookup<KeyT, ValueT>::Rebind(const KeyT& key, const ValueT& value)
{
	int32	dloc = Location(key);
	
	if (dloc >= 0)
		fValueList[dloc] = value;
	else
		{
		fKeyList.push_back(key);
		fValueList.push_back(value);
		}
}


template <class KeyT, class ValueT>
void K2Lookup<KeyT, ValueT>::Unbind(const KeyT& key)
{
	int32	dloc = Location(key);
	
	if (dloc >= 0)
		{
		fKeyList.erase(fKeyList.begin() + dloc);
		fValueList.erase(fValueList.begin() + dloc);
		}
	else
	{
		ASSERT_FAIL("Can't unbind, doesn't exist");
	}
}
#endif // ID_DEPRECATED


#endif //__K2Lookuptpp__