//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/PersistObjectCollection.tpp $
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

#ifndef __PersistObjectCollection_TPP__
#define __PersistObjectCollection_TPP__

#ifndef __PersistObjectCollection__
#include "PersistObjectCollection.h"
#endif

#include "K2Vector.tpp"

#include "IPMStream.h"

//************* IMPORTANT ***************
// This collection class is to be ONLY ONLY ONLY used
// with objects that REQUIRE special copy semantics. Things 
// that have pointers to buffers for instance. If you have a
// base type or a struct-type class use K2Vector OR K2Vector!
// IF YOU HAVE QUESTIONS, ASK ROBIN OR ERIC
//************* IMPORTANT ***************

template<class T>
PersistObjectCollection<T> :: PersistObjectCollection() :
	K2Vector<T>()
{
}

template<class T>
PersistObjectCollection<T> :: PersistObjectCollection(int32 chunkSize) :
	K2Vector<T>()
{
    K2Vector<T>::reserve(chunkSize);
}

template<class T>
PersistObjectCollection<T> :: PersistObjectCollection(const PersistObjectCollection<T>& copy) :
	K2Vector<T>(copy)
{
}

template<class T>
PersistObjectCollection<T> :: ~PersistObjectCollection()
{
}

template<class T>
void PersistObjectCollection<T> :: ReadWrite(IPMStream *s, ImplementationID prop)
{
	int32 cnt = K2Vector<T>::size();
	s->XferInt32(cnt);
	if (s->IsReading())
		K2Vector<T>::clear();
	for (int32 i = 0; i < cnt; i++)
		if (s->IsReading())
		{
			T t;
			ReadWriteItem(s, prop, t);
			K2Vector<T>::push_back(t);
		}
		else
			ReadWriteItem(s, prop, (*this)[i]);
}

template<class T>
void PersistObjectCollection<T> :: ReadWriteItem(IPMStream *s, ImplementationID prop, T& item)
{
	item.ReadWrite(s, prop);
}

#endif // __PersistObjectCollection_TPP__
