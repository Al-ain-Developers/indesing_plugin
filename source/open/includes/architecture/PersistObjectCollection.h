//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/PersistObjectCollection.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __PersistObjectCollection__
#define __PersistObjectCollection__

#include "K2Vector.h"

//************* IMPORTANT ***************
// This collection class is to be ONLY ONLY ONLY used
// with objects that REQUIRE special copy semantics. Things 
// that have pointers to buffers for instance. If you have a
// base type or a struct-type class use K2Vector OR K2Vector!
// IF YOU HAVE QUESTIONS, ASK ROBIN OR ERIC
//************* IMPORTANT ***************

template <class T>
class PersistObjectCollection : public K2Vector<T>
{
public:
	PersistObjectCollection();
	PersistObjectCollection(int32 chunkSize);
	PersistObjectCollection(const PersistObjectCollection<T>& copy);
		
	~PersistObjectCollection();
	
	void ReadWrite(IPMStream *s, ImplementationID prop);

private:
	// ----- ReadWriteItem can be specialized for types that don't have
	//		 ReadWrite methods. [amb]
	void ReadWriteItem(IPMStream *s, ImplementationID prop, T& item);
};

#ifdef _INCLUDE_TPP_IN_H_
	#include "PersistObjectCollection.tpp"
#endif //_INCLUDE_TPP_IN_H_

#endif // __PersistObjectCollection__

