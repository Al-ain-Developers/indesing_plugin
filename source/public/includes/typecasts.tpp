//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/typecasts.tpp $
//  
//  Owner: Brendan O'Shea
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

#ifndef __typecastsTPP__
#define __typecastsTPP__

/**
	Convenience function to cast to an arbitrary type from a void *. 

	This can be used with non-pointer integer types, for example when
	retrieving an integer from the 'changedBy' parameter in an observer's 
	Update method. 

	Using this method makes explicit that the code intends to look at the
	value of a void *. Most often used in conjunction with to_voidptr_cast. 
	
	Example usage: 
	int foo = from_voidptr_cast<int>(aVoidStar);
	
	@param p [IN] - the void *.
*/
template<typename T>
inline T from_voidptr_cast(void *p)
{
	return (T)((uintptr_t)p);
}

/**
	Convenience function to cast an arbitrary type to a void *. 

	This can be used with non-pointer integer types, for example when
	passing an integer in the 'changedBy' parameter in a subect's 
	Change method. 

	Using this method makes explicit that the code intends to treat the
	value as a void *. Most often used in conjunction with from_voidptr_cast. 
	
	Example usage: 
	void *foo = to_voidptr_cast(aIntegerValue);
*/
template<typename T>
inline void *to_voidptr_cast(T t)
{
	return (void *)((uintptr_t)t);
}

#endif
