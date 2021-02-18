//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2sortedlookup.tpp $
//  
//  Owner: EricM, rewrite: Mat Marcus
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

#ifndef __K2SortedLookuptpp__
#define __K2SortedLookuptpp__

#ifdef ID_DEPRECATED
#include "k2sortedlookup.h"

template <class KeyT, class ValueT>
void K2SortedLookup<KeyT, ValueT>::Bind(const KeyT& key, const ValueT& value)
{
#ifdef DEBUG
	int32	dloc = Location(key);
	
	if (dloc >= 0)
		ASSERT_FAIL("Collision in lookup");
#endif

	int32	loc = fKeyList.Insert(key);
	if (loc < (int32)fValueList.size())
		fValueList.insert(fValueList.begin() + loc, value);
	else
		fValueList.push_back(value);
}

template <class KeyT, class ValueT>
void K2SortedLookup<KeyT, ValueT>::Unbind(const KeyT& key)
{
	int32	dloc = Location(key);
	
	if (dloc >= 0)
		{
		fKeyList.Remove(dloc);
		fValueList.erase(fValueList.begin() + dloc);
		}
	else
	{
		ASSERT_FAIL("Can't unbind, doesn't exist");
	}
}
#endif // ID_DEPRECATED

#endif //__K2SortedLookuptpp__

