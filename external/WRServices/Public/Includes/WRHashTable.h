//========================================================================================
//  
//  File: WRHashTable.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRHashTable__
#define __WRHashTable__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRMem.h"
#include "WRAllocPool.h"

// T must at least have the following members
// Compare(T&) const



template < class T> class WRHashTableNode
{
public:
	WRHashTableNode(const T* data,WRHashTableNode<T>* nxt = NULL) { fNext = nxt; fData = *data; }
	~WRHashTableNode();


public:
	int					Compare(const T* that) const { return fData.Compare(*that); }
	T					fData;
	WRHashTableNode<T>*	fNext;
};



//=======================================================================
// constructors and destructors

template  <class T> class WRHashTable
{
public:
	WRHashTable(WRInt32 primTableSize,WRAllocPool* pool);
	virtual ~WRHashTable();
	typedef	WRHashTableNode<T>	_nodetype;
	typedef _nodetype* _nodeptr;

	virtual void	Reset();

	virtual T*		Search(const T* what, WRInt32 n = 0);
	virtual T*		Add(const T* x);

	virtual WRInt32 Count() const { return fCount; }
	virtual WRInt32 PrimSize() const { return fSize; }
	virtual void SetPrimSize(WRInt32 sz) { if (fTable == NULL) fSize = sz; }
	virtual WRHashTableNode<T>* PrimEntry(WRInt32 i) { return fTable ? fTable[i] : NULL; }

protected:

	void	AllocPrimTable();

	WRInt32				fSize; // prim table size
	_nodeptr*			fTable;
	WRInt32				fCount; // number of entries
	WRAllocPool*		fPool;
};


template < class T> class WRHashTableIterator
{
public:
	WRHashTableIterator(WRHashTable<T>* table) : fHashTable(table) { Reset(); }
	void Reset() { fPrimIndex = -1; fSecIndex = NULL; }
	T*	Next();
protected:
	int	fPrimIndex;
	WRHashTableNode<T>* fSecIndex;
	WRHashTable<T>*	fHashTable;
};

template <class T> T* WRHashTableIterator<T>::Next()
{
	T* res = NULL;
	while (fSecIndex == NULL && fPrimIndex + 1 < fHashTable->PrimSize())
		fSecIndex = fHashTable->PrimEntry(++fPrimIndex);

	if (fSecIndex)
	{
		res = &(fSecIndex->fData);
		fSecIndex = fSecIndex->fNext;
	}

	return res;
}


template <class T> WRHashTable<T>::WRHashTable(WRInt32 primTableSize,WRAllocPool* pool) : 
	fSize(primTableSize),
	fTable(NULL),
	fCount(0),
	fPool(pool)
{
}

template <class T> WRHashTable<T>::~WRHashTable()
{
	Reset();
	if (fTable)
		WRFree(fTable);
}

template <class T> void WRHashTable<T>::Reset()
{
	if (fTable)
	{
		for (WRInt32 i = 0; i < fSize; i++)
		{
			_nodeptr item = fTable[i];
			while(item)
			{
				_nodeptr next = item->fNext;
				if (fPool)
					fPool->Free(item);
				else
					delete item;
				item = next;
			}
			fTable[i] = NULL;
		}
	}
	fCount = 0;
}

template <class T> WRHashTableNode<T>::~WRHashTableNode()
{
}

template <class T> void WRHashTable<T>::AllocPrimTable()
{
	fTable = (_nodeptr*) WRMalloc(sizeof(_nodeptr) * fSize);
	memset(fTable, 0, sizeof(_nodeptr) * fSize);
}


template <class T> T* WRHashTable<T>::Search(const T* what,WRInt32 n)
{
	WRUInt32 key = what->Hash();
	key = key % fSize; // lazy mod should be enough

	if (fTable)
	{
		_nodeptr item = fTable[key];
		while(item)
		{
			if (item->fData.Compare(what) == 0)
			{
				if (n == 0)
					return &(item->fData);
				else 
					n--;
			}
			item = item->fNext;
		}
	}
	return NULL;
}


template <class T> T* WRHashTable<T>::Add(const T* what)
{
	WRUInt32 key = what->Hash();
	key = key % fSize; // lazy mod should be enough

	if (fTable == NULL)
		AllocPrimTable();

	if (fPool)
	{
		WRHashTableNode<T>* res;
		res = (WRHashTableNode<T>*) fPool->Alloc();
		res->fData = *what;
		res->fNext = fTable[key]; 
		fTable[key] = res;
	}
	else
		fTable[key] = new WRHashTableNode<T>(what,fTable[key]);

	fCount++;
	return &(fTable[key]->fData);
}


#endif
