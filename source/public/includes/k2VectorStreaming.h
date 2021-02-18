//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/k2VectorStreaming.h $
//  
//  Owner: Jesse Jones
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
//  Summary: Template functions used to stream K2Vector's in and out.
//  
//========================================================================================

#pragma once
#ifndef __k2VectorStreaming__
#define __k2VectorStreaming__

#include "IPMStream.h"
#include "KeyValuePair.h"
#include "PMRect.h"
#include "Swap.h"
#include "WideString.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif


// ===================================================================================
//	Internal Functions
// ===================================================================================

// ----- Primitive Streaming -----
inline void K2Write(IPMStream* stream, int8 n)
{
	unsigned char temp = n;
	stream->XferByte(temp);
}

inline void K2Read(IPMStream* stream, int8& n)
{
	unsigned char temp(0);
	stream->XferByte(temp);
	n = temp;
}


inline void K2Write(IPMStream* stream, int16 n)
{
	stream->XferInt16(n);
}

inline void K2Read(IPMStream* stream, int16& n)
{
	stream->XferInt16(n);
}


inline void K2Write(IPMStream* stream, int32 n)
{
	stream->XferInt32(n);
}

inline void K2Read(IPMStream* stream, int32& n)
{
	stream->XferInt32(n);
}


inline void K2Write(IPMStream* stream, uint8 n)
{
	stream->XferByte(n);
}

inline void K2Read(IPMStream* stream, uint8& n)
{
	stream->XferByte(n);
}


inline void K2Write(IPMStream* stream, uint16 n)
{
	int16 temp = n;
	stream->XferInt16(temp);
}

inline void K2Read(IPMStream* stream, uint16& n)
{
	int16 temp(0);
	stream->XferInt16(temp);
	n = temp;
}


inline void K2Write(IPMStream* stream, uint32 n)
{
	int32 temp = n;
	stream->XferInt32(temp);
}

inline void K2Read(IPMStream* stream, uint32& n)
{
	int32 temp(0);
	stream->XferInt32(temp);
	n = temp;
}

inline void K2Write(IPMStream* stream, const PMReal& n)
{
	PMReal temp = n;
	stream->XferRealNumber(temp);
}

inline void K2Read(IPMStream* stream, PMReal& n)
{
	stream->XferRealNumber(n);
}


inline void K2Write(IPMStream* stream, const PMPoint& n)
{
	K2Write(stream, n.X());
	K2Write(stream, n.Y());
}

inline void K2Read(IPMStream* stream, PMPoint& n)
{
	K2Read(stream, n.X());
	K2Read(stream, n.Y());
}


inline void K2Write(IPMStream* stream, const PMRect& n)
{
	K2Write(stream, n.Top());
	K2Write(stream, n.Left());
	K2Write(stream, n.Bottom());
	K2Write(stream, n.Right());
}

inline void K2Read(IPMStream* stream, PMRect& n)
{
	K2Read(stream, n.Top());
	K2Read(stream, n.Left());
	K2Read(stream, n.Bottom());
	K2Read(stream, n.Right());
}

// ----- ReadWrite Object Streaming -----

#define DEFINEK2READWRITE( K2TYPE ) \
	inline void K2Write(IPMStream* stream, const K2TYPE& n) { K2TYPE& temp = const_cast<K2TYPE&>(n); temp.ReadWrite(stream); } \
	inline void K2Read(IPMStream* stream, K2TYPE& n) { n.ReadWrite(stream); }

DEFINEK2READWRITE( PMString )
DEFINEK2READWRITE( WideString )

// ----- IDType Streaming -----

template<class T>
inline void K2Write( IPMStream* s, const IDType<T>& id )
{
	IDType<T>& temp = const_cast< IDType<T>& >(id) ;
	s->XferID( temp ) ;
}

template<class T>
inline void K2Read( IPMStream* s, IDType<T>& id )
{
	s->XferID( id ) ;
}

// ----- KeyValuePair Streaming -----

template <class _T1, class _T2>
inline void K2Write( IPMStream* s, const KeyValuePair<_T1,_T2>& kvp )
{
	KeyValuePair<_T1,_T2>& temp = const_cast< KeyValuePair<_T1,_T2>& >(kvp) ;
	K2Write( s, temp.fKey ) ;
	K2Write( s, temp.fValue ) ;
}

template <class _T1, class _T2>
inline void K2Read( IPMStream* s, KeyValuePair<_T1,_T2>& kvp )
{
	K2Read( s, kvp.fKey ) ;
	K2Read( s, kvp.fValue ) ;
}

// ----- Optimized Block Streaming -----
template <class T>
void K2WriteBlock(IPMStream* stream, uint32 count, const T* block)
{	
	for (uint32 i = 0; i < count; ++i)
		K2Write(stream, block[i]);					// you'll have to provide a K2Write function for custom types
}

template <class T>
void K2ReadBlock(IPMStream* stream, uint32 count, T* block)
{	
	for (uint32 i = 0; i < count; ++i)
		K2Read(stream, block[i]);					// you'll have to provide a K2Read function for custom types
}


template <>
inline void K2WriteBlock(IPMStream* stream, uint32 count, const char* block)
{	
	stream->XferByte((uint8*) block, count*sizeof(char));
}

template <>
inline void K2ReadBlock(IPMStream* stream, uint32 count, char* block)
{	
	stream->XferByte((uint8*) block, count*sizeof(char));
}


template <>
PUBLIC_DECL void K2WriteBlock(IPMStream* stream, uint32 count, const int16* block);

template <>
PUBLIC_DECL void K2ReadBlock(IPMStream* stream, uint32 count, int16* block);


template <>
PUBLIC_DECL void K2WriteBlock(IPMStream* stream, uint32 count, const uint16* block);

template <>
PUBLIC_DECL void K2ReadBlock(IPMStream* stream, uint32 count,  uint16* block);


template <>
PUBLIC_DECL void K2WriteBlock(IPMStream* stream, uint32 count, const int32* block);

template <>
PUBLIC_DECL void K2ReadBlock(IPMStream* stream, uint32 count, int32* block);


#if 1			// $$$ not safe while UIDs are uint32's
template <>
PUBLIC_DECL void K2WriteBlock(IPMStream* stream, uint32 count, const uint32* block);

template <>
PUBLIC_DECL void K2ReadBlock(IPMStream* stream, uint32 count, uint32* block);
#endif


// ----- Streaming -----

class Uint32s_Cannot_Be_Streamed {			// not instantiable (private default ctor)
	Uint32s_Cannot_Be_Streamed() {}
};

template <class T, class A>
void K2Write(IPMStream* stream, const K2Vector<T, A>& v)
{	
	ASSERT(stream != nil);
	ASSERT(stream->IsWriting());
	
	using namespace K2Meta;
	META_ASSERT<!IS_SAME_TYPE<T, uint32>::RET, Uint32s_Cannot_Be_Streamed>();
	
	int32 count = v.size();
	stream->XferInt32(count);
	
	K2WriteBlock(stream, count, v.begin());
}

template <class T, class A>
void K2Read(IPMStream* stream, K2Vector<T, A>& v)
{
	ASSERT(stream != nil);
	ASSERT(stream->IsReading());
	
	using namespace K2Meta;
	META_ASSERT<!IS_SAME_TYPE<T, uint32>::RET, Uint32s_Cannot_Be_Streamed>();

	int32 count(0);
	stream->XferInt32(count);
	v.resize(count, T());
	
	K2ReadBlock(stream, count, v.begin());
}

// ===================================================================================
//	Global Functions
// ===================================================================================

// ----- Vectors -----
template <class T, class A>
void K2ReadWrite(IPMStream* stream, K2Vector<T, A>& v)
{		
	if (stream->IsReading())
		K2Read(stream, v);
	else
		K2Write(stream, v);
}

template <class A>
void K2ReadWriteObject(IPMStream* stream, K2Vector<UID, A>& v)
{		
	stream->XferObject(v.begin(), v.size());
}

template <class A>
void K2ReadWriteReference(IPMStream* stream, K2Vector<UID, A>& v)
{		
	stream->XferReference(v.begin(), v.size());
}

#pragma export off

#endif	// __k2VectorStreaming__
