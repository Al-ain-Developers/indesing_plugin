//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIntList.h $
//  
//  Owner: Ryan Gano
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
//  
//  An interface off the scrap document, contains a list of extra info needed for 
//  copying unnamed page destinations around
//  
//========================================================================================

#pragma once
#ifndef __IIntList__
#define __IIntList__

#include "HyperlinkID.h"

/** This class is used to store a list of int32 objects */
class IIntList : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IINTLIST};

public:    
	/** Use to add a new integer
		@param k - the new int to be added
	*/
	virtual void Append(int32 k) = 0;
	
	/** Get the nth integer
		@param n - the integer you want (must be less than Length - 1)
		@return - the integer you requested. (if you request a value that is out of range behavior is undefined)
	*/
	virtual int32 Get(int32 n) = 0;

	/** Get the number of integers currently stored
		@return - The number of integers
	*/
	virtual int32 Length() = 0;

	/** remove all the entries in the array
	*/
	virtual void Clear() = 0;
};


#endif // __IIntList__

