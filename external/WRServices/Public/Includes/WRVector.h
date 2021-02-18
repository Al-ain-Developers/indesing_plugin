//========================================================================================
//  
//  File: WRVector.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRVECTOR__
#define __WRVECTOR__

#include "WRMem.h"
#include <string.h>
#include <limits.h>

#ifndef WRASSERT
  #ifdef WRSERVICES_BUILD
  #include "WRDebug.h"
  #else
  #define WRASSERT(a,b) 
  #endif
#endif
/*
#ifdef WRSERVICES_BUILD
#include "WRMem.h"
#include "WRDebug.h"
#else

#define WRMalloc(s) malloc(s)
#define WRFree(p) free(p)
#define WRRealloc(p,nw,old) realloc(p,nw)
#define WRASSERT(a,b) 
#endif
*/

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

#define OPTYCAVECTORRESERVE	128

#define kWRVectorInvalidIndex (-1)

template <class ItemType> class WRVector
{
public:
	WRVector();
	WRVector(const WRVector& vect);
	~WRVector();

	ItemType*		PeekArray() const { return fData; }
	int				Size() const { return fSize; }
	int				Alloc() const { return fAlloc; }
	ItemType&		operator[](int i) { WRASSERT(i >= 0 && i < fSize,"WRVector index out of range"); return fData[i]; }
	const ItemType&	operator[](int i) const { WRASSERT(i >= 0 && i < fSize,"WRVector index out of range"); return fData[i]; }
	int				EnsureSpace(int sz);
	int				Clear();
	int				Resize(int sz);
	int				Resize(int sz,ItemType initItem);
	void			Reset(ItemType item);
	void			Reset(int start, int count,ItemType item);// resize if needed
	int				Append(ItemType item);
	int				Append(ItemType item,int count);
	int				Insert(ItemType item,int where);
	int				Remove(int where,int count = 1);
	void			FillWithZeros();
	int				Insert(ItemType item,int where,int count);
	const WRVector<ItemType>& operator= (const WRVector<ItemType>& vect);
	void			CopyTail (const WRVector<ItemType>& vect, WRInt32 start);
	void			SwapContent(WRVector<ItemType>& vect);
	int				Search(ItemType item);
	WRBool			Contains(ItemType item);

protected:
	int				fSize;
	int				fAlloc;
	ItemType*		fData;
};

template <class ItemType> WRVector<ItemType>::WRVector()
{
	fSize = 0;
	fAlloc = 0;
	fData = NULL;
}

template <class ItemType> WRVector<ItemType>::WRVector(const WRVector<ItemType>& vect)
{
	fSize = 0;
	fAlloc = 0;
	fData = NULL;
	*this = vect;
}

template <class ItemType> const WRVector<ItemType>& WRVector<ItemType>::operator= (const WRVector<ItemType>& vect)
{
	int len = vect.Size();
	Resize(len);
	memcpy ((void*) PeekArray(), (void*) vect.PeekArray(), sizeof(ItemType) * len);
	return vect;
}

template <class ItemType> void WRVector<ItemType>::CopyTail (const WRVector<ItemType>& vect, WRInt32 start)
{
	int len = vect.Size();
	WRASSERT(start >= 0 && start <= len,"WRVector::CopyTail out of bounds start");
	Resize(len);
	memcpy ((void*)(PeekArray() + start), (void*)(vect.PeekArray() + start), sizeof(ItemType) * (len - start));
}

template <class ItemType> void WRVector<ItemType>::SwapContent (WRVector<ItemType>& vect)
{
	int len = vect.fSize;
	int alloc = vect.fAlloc;
	ItemType* data = vect.fData;
	
	vect.fSize = fSize;
	vect.fAlloc = fAlloc;
	vect.fData = fData;

	fSize = len;
	fAlloc = alloc;
	fData = data;
}

template <class ItemType> WRVector<ItemType>::~WRVector()
{
	Clear();
}


template <class ItemType> int WRVector<ItemType>::EnsureSpace(int sz)
{
	if (fAlloc >= sz)
		return kWRNoErr;

	if ((sz < 0) || (sz >= INT_MAX - OPTYCAVECTORRESERVE))
		return kWRMemErr;

//#ifdef WRSERVICES_BUILD
	int oldSize = fAlloc;
//#endif
	fAlloc = OPTYCAVECTORRESERVE + sz;
	if (fData)
//#ifdef WRSERVICES_BUILD
		fData = (ItemType*) WRRealloc(fData, fAlloc * sizeof(ItemType),oldSize * sizeof(ItemType));
//#else
//		fData = (ItemType*) realloc(fData, fAlloc * sizeof(ItemType));// MH very stange compilor C4189 warning 
//#endif
	else
		fData = (ItemType*) WRMalloc(fAlloc * sizeof(ItemType));

	if (fData == NULL)
		return kWRMemErr;
	else
		return kWRNoErr;
}

template <class ItemType> int WRVector<ItemType>::Resize(int sz)
{
	int err = EnsureSpace(sz);
	if (!err)
		fSize = sz;
	return err;
}

template <class ItemType> int WRVector<ItemType>::Resize(int sz,ItemType item)
{
	int err = EnsureSpace(sz);
	if (!err)
	{
		while(fSize < sz)
			fData[fSize++] = item;
	}
	return err;
}


template <class ItemType> int WRVector<ItemType>::Append(ItemType item)
{
	int err = EnsureSpace(fSize+1);
	if (!err)
	{
		fData[fSize++] = item;
	}
	return err;
}

template <class ItemType> int WRVector<ItemType>::Insert(ItemType item,int where)
{
	int err = EnsureSpace(fSize+1);
	if (!err)
	{
		memmove((void*)(fData+where+1),fData+where, (fSize-where)*sizeof(ItemType));
		fSize++;
		fData[where] = item;
	}
	return err;
}

template <class ItemType> int WRVector<ItemType>::Remove(int where,int count)
{
	memmove((void*)(fData+where),(void*)(fData+where+count), (fSize-where-count)*sizeof(ItemType));
	fSize-=count;
	return kWRNoErr;
}

template <class ItemType> void WRVector<ItemType>::FillWithZeros()
{
	memset(fData,0,fSize * sizeof(ItemType));
}

template <class ItemType> int WRVector<ItemType>::Insert(ItemType item,int where,int count)
{
	int err = EnsureSpace(fSize+count);
	if (!err)
	{
		memmove(fData+where+count,fData+where, (fSize-where)*sizeof(ItemType));
		fSize+=count;
		for (int i=0; i< count;i++)
			fData[where++] = item;
	}
	return err;
}

template <class ItemType> int WRVector<ItemType>::Append(ItemType item,int count)
{
	int err = EnsureSpace(fSize+count);
	if (!err)
	{
		for (int i=0; i< count;i++)
			fData[fSize++] = item;
	}
	return err;
}

template <class ItemType> int WRVector<ItemType>::Clear()
{
	if (fData)
		WRFree(fData);
	fAlloc = fSize = 0;
	fData = NULL;
	return kWRNoErr;
}

template <class ItemType> void WRVector<ItemType>::Reset(ItemType item)
{
	for (int i = 0; i< fSize; i++)
		fData[i] = item;
}

template <class ItemType> void WRVector<ItemType>::Reset(int start, int count,ItemType item)
{
	if (fSize < start+count)
		Resize(start+count);

	for (int i = 0; i< count; i++)
		fData[start++] = item;
}

template <class ItemType> int WRVector<ItemType>::Search(ItemType item)
{
	for (int i = 0; i< fSize; i++)
	{
		if (fData[i] == item)
			return i;
	}
	
	return kWRVectorInvalidIndex;
}

template <class ItemType> WRBool WRVector<ItemType>::Contains(ItemType item)
{
	if (Search(item) != kWRVectorInvalidIndex)
		return WRTrue;
	else
		return WRFalse;
}

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
