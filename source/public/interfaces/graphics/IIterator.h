//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IIterator.h $
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

#pragma once
#ifndef __IITERATOR__
#define __IITERATOR__

/** IIterator is an abstract base class used to define the interface to 
 iterators within shuksan. Since the initialization & previous/next 
 methods are highly dependant on the thing being iterated over, there is
 no common implementation, but if all iterators conform to a single 
 standard, they will be easier to use.
*/
class IIterator
{
public:
	virtual ~IIterator() {}
	/** Initialize internal state
		@return the first thing being iterated over.
	*/
	virtual UIDRef	First() = 0;

	/** Move to the next thing being iterated over. 
		@return a UIDRef,  kInvalidUID if there are no more.
	*/
	virtual UIDRef	Next() = 0;

// TODO: Are these next two methods useful? If not, get rid of them.
//
	/** @return the last thing being iterated over */
	virtual UIDRef	Last() = 0;
		
	/** return the previous thing being iterated. 
		@return a UIDRef, kInvalidUID if there are no more.
	*/
	virtual UIDRef	Previous() = 0;
};

#endif // __IITERATOR__
