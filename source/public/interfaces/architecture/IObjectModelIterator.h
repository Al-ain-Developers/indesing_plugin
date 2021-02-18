//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IObjectModelIterator.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IObjectModelIterator__
#define __IObjectModelIterator__

/**
	Abstract class for iterating over the classes registered in the object model. 
	You can get one of these by calling IObjectModel::NewObjectModelIterator.
	THIS IS NOT A STANDARD BOSS INTERFACE!!
	@see IObjectModel
*/
class IObjectModelIterator INHERITFROM
{
public:
	/** This object should be deleted when you are all done with it. */
	virtual ~IObjectModelIterator() {}

	/**
		An iterator iterates over classes that implement a given interface. Next() returns the 
		next class that supports the interface, or kInvalidClass if there are no more classes.
	*/
	virtual ClassID Next() = 0;
};

#endif
