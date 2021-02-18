//========================================================================================
//  
//  File: WRRedBlackTree.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRRedBlackTree__
#define __WRRedBlackTree__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRAllocPool.h"


// T must at least have the following members
// Compare(T&) const
// Print(FILE*f)

#define qRBDEBUG 1

#if qRBDEBUG
#include <stdio.h>
#endif

template < class T> class WRRedBlackNode
{
public:
	WRRedBlackNode(T* data) { fParent = fLeft = fRight = NULL; fRed = false; fData = data; }
	~WRRedBlackNode();

	void Red() { fRed = true; }
	void Black() { fRed = false; }
	void SetColor(bool b) { fRed = b; }
	bool IsRoot() const { return fParent == NULL; }
	bool IsRed() const { return fRed; }
	bool Color() const { return fRed; }
	bool IsBlack() const { return !fRed; }
	bool IsNilNode() const { return fLeft == NULL; }
	bool IsLeftChild() const { return fParent->fLeft == this; }
	bool IsRightChild() const { return fParent->fLeft == this; }
	bool HasBlackSibling() const { return fLeft->IsBlack() && fRight->IsBlack(); }
	void SetRight(WRRedBlackNode<T>* p)
	{
		fRight = p;
		p->fParent = this;
	}
	void SetLeft(WRRedBlackNode<T>* p)
	{
		fLeft = p;
		p->fParent = this;
	}

#if qRBDEBUG
	void Print(FILE* f, int depth);
	WRInt32 VerifyIntegrity(FILE* f) const;
#endif

public:
	int		Compare(const WRRedBlackNode<T>* that) const { return fData->Compare(*that->fData); }
	T*	   fData;
	WRRedBlackNode<T>*	fParent;
	WRRedBlackNode<T>*	fLeft;
	WRRedBlackNode<T>*	fRight;
	bool				fRed;
};

template < class T> class WRRedBlackAllocPool
{
public:
	WRRedBlackAllocPool(WRAllocPool* nodeAllocPool,WRAllocPool* dataAllocPool)
	{ 
		fNodeAllocPool = nodeAllocPool; 
		fDataAllocPool = dataAllocPool;
	}
	~WRRedBlackAllocPool();
	WRRedBlackNode<T>*	Alloc();
	T*					AllocData();
	WRRedBlackNode<T>*	AllocNode(T* data = NULL);
	void				Free(WRRedBlackNode<T>*);
	void				FreeData(T*);
	void				FreeNode(WRRedBlackNode<T>*);
protected:
	WRAllocPool*	fNodeAllocPool;
	WRAllocPool*	fDataAllocPool;
};

template <class T> WRRedBlackAllocPool<T>::~WRRedBlackAllocPool()
{
}

template <class T> void WRRedBlackAllocPool<T>::Free(WRRedBlackNode<T>* node)
{
	if (node)
	{
		if (node->fData)
		{
			FreeData(node->fData);
			node->fData = NULL;
		}
		FreeNode(node);
	}
}

template <class T> void WRRedBlackAllocPool<T>::FreeNode(WRRedBlackNode<T>* node)
{
	if (node)
	{
		if (fNodeAllocPool)
			fNodeAllocPool->Free(node);
		else
			delete node;
	}
}

template <class T> void WRRedBlackAllocPool<T>::FreeData(T* data)
{
	if (data)
	{
		if (fDataAllocPool)
			fDataAllocPool->Free(data);
		else
			delete data;
	}
}

template <class T> WRRedBlackNode<T>* WRRedBlackAllocPool<T>::Alloc()
{
	WRRedBlackNode<T>* res = AllocNode();
	if (res)
	{
		res->fData = DataAlloc();
		res->fParent = res->fLeft = res->fRight = NULL; res->fRed = false;
	}
}

template <class T> WRRedBlackNode<T>* WRRedBlackAllocPool<T>::AllocNode(T* data)
{
	WRRedBlackNode<T>* res;
	if (fNodeAllocPool)
	{
		res = (WRRedBlackNode<T>*) fNodeAllocPool->Alloc();
		res->fParent = res->fLeft = res->fRight = NULL; res->fRed = false; 
		res->fData = data;
	}
	else
		res = new WRRedBlackNode<T>(data);
	return res;
}

template <class T> T* WRRedBlackAllocPool<T>::AllocData()
{
	T* res;
	if (fDataAllocPool)
		res = (T*) fDataAllocPool->Alloc();
	else
		res = new T;
	return res;
}


//=======================================================================
// constructors and destructors

template  <class T> class WRRedBlackTree
{
public:
	WRRedBlackTree(WRRedBlackAllocPool<T>* pool);
	virtual ~WRRedBlackTree();
	void Reset();
	void Free(WRRedBlackNode<T>* n);
	WRRedBlackAllocPool<T>*	GetPool() { return fPool; }

	WRRedBlackNode<T>*	Search(const WRRedBlackNode<T>* x);
	WRRedBlackNode<T>*	Search(const T* what);
	bool Insert(WRRedBlackNode<T>* x);
	WRRedBlackNode<T>* Remove(WRRedBlackNode<T>* n);
	WRRedBlackNode<T>*	First();
	WRRedBlackNode<T>*	Last();
	WRRedBlackNode<T>*	Next(WRRedBlackNode<T>* x);
	WRRedBlackNode<T>*	Prev(WRRedBlackNode<T>* x);
	void Set(WRRedBlackNode<T>* x, WRRedBlackNode<T>* p, WRRedBlackNode<T>* l, WRRedBlackNode<T>* r);
	
	void Print(FILE* f);
	WRInt32				GetCount() const { return fCount; }
#if qRBDEBUG
	void				VerifyIntegrity(FILE* f) const;
#endif


protected:
	void LeftRotate(WRRedBlackNode<T>* x);
	void RightRotate(WRRedBlackNode<T>* x);
	WRRedBlackNode<T>*	NewSentinel() { return fPool->AllocNode(NULL); }
	void DeleteFixup(WRRedBlackNode<T>* x);

	WRRedBlackNode<T>*	fRoot;
	WRInt32				fCount; // count of non-nil nodes
	WRRedBlackAllocPool<T>* fPool;
};

template <class T> WRRedBlackTree<T>::WRRedBlackTree(WRRedBlackAllocPool<T>* pool )
{
	fPool = pool;
	fRoot = NewSentinel();
	fCount = 0;
}

template <class T> WRRedBlackTree<T>::~WRRedBlackTree()
{
	Free(fRoot);
}

template <class T> void WRRedBlackTree<T>::Reset()
{
	Free(fRoot);
	fRoot = NewSentinel();
	fCount = 0;
}

template <class T> void WRRedBlackTree<T>::Free(WRRedBlackNode<T>* node)
{
	if (node)
	{
		Free(node->fLeft);
		node->fLeft = NULL;
		Free(node->fRight);	
		node->fRight = NULL;
	}
	fPool->Free(node);
}

template <class T> WRRedBlackNode<T>::~WRRedBlackNode()
{
	/*
	if (fLeft)
		delete fLeft;
	if (fRight)
		delete fRight;
	if (fData) 
		delete fData;
	*/
}

#if qRBDEBUG

//=======================================================================
// debug

template <class T> void WRRedBlackTree<T>::VerifyIntegrity(FILE* f) const
{
	fRoot->VerifyIntegrity(f);
}

template <class T> WRInt32 WRRedBlackNode<T>::VerifyIntegrity(FILE* f) const
{
	if (fLeft == NULL || fRight == NULL)
	{
		// nil node
		if (fData)
			throw kWRBrokenRedBlackNodeErr;
		if (fLeft != NULL || fRight != NULL || IsRed())
			throw kWRBrokenRedBlackNodeErr;
		return 1;
	}
	else
	{
		if (fLeft->fParent != this)
			throw kWRBrokenRedBlackNodeErr;

		if (fRight->fParent != this)
			throw kWRBrokenRedBlackNodeErr;

		// verify black height
		WRInt32 leftBlackHeight = fLeft->VerifyIntegrity(f);
		WRInt32 rightBlackHeight = fRight->VerifyIntegrity(f);
		if (leftBlackHeight != rightBlackHeight)
				throw kWRBrokenRedBlackNodeErr;

		// valid data?
		if (fData == NULL)
			throw kWRBrokenRedBlackNodeErr;

		// verify order
		if (!fLeft->IsNilNode() && fData->Compare(*(fLeft->fData)) < 0)
			throw kWRBrokenRedBlackNodeErr;

		if (!fRight->IsNilNode() && fData->Compare(*fRight->fData) > 0)
			throw kWRBrokenRedBlackNodeErr;

		if (IsRed())
		{
			// verify sibling of res nodes
			if (!HasBlackSibling())
				throw kWRBrokenRedBlackNodeErr;
		}
		else
		{
			leftBlackHeight++;
		}
		return leftBlackHeight;
	}
}



template <class T> void WRRedBlackTree<T>::Print(FILE* f)
{
	fRoot->Print(f,0);
}

template <class T> void WRRedBlackNode<T>::Print(FILE* f, int depth)
{
	if (fLeft)
		fLeft->Print(f,depth+1);
	for (int i = 0; i< depth;i++)
		fputc(' ',f);
	fputc(fRed ? 'o' : '*' ,f);
	if (fData)
		fData->Print(f);
	else
		fprintf(f,"nil data");
	fprintf(f,"\n");
	if (fRight)
		fRight->Print(f,depth+1);
}

#endif

//=======================================================================================

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::First()
{
	WRRedBlackNode<T>* current = fRoot;
	while (current->fLeft != NULL)
		current = current->fLeft;

	return current->fParent;
}

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Last()
{
	WRRedBlackNode<T>* current = fRoot;
	while (current->fRight != NULL)
		current = current->fRight;

	return current->fParent;
}

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Next(WRRedBlackNode<T>* x)
{
	// leftmost node of the right subtree
	x = x->fRight;
	while (x->fLeft != NULL)
		x = x->fLeft;

	while (x->fParent)
	{
		if (x->IsLeftChild())
			return x->fParent; // coming from left branch parent not visited yet
		x = x->fParent; // coming from right branch, parent already visited
	}
	return NULL; // finished
}
template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Prev(WRRedBlackNode<T>* x)
{
	// leftmost node of the right subtree
	x = x->fLeft;
	while (x->fRight != NULL)
		x = x->fRight;

	while (x->fParent)
	{
		if (x->IsRightChild())
			return x->fParent; // coming from right branch parent not visited yet
		x = x->fParent; // coming from left branch, parent already visited
	}
	return NULL; // finished
}

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Search(const WRRedBlackNode<T>* what)
{
	WRRedBlackNode<T>* current = fRoot;
	int res;
	while(1)
	{
		if (current->IsNilNode())
			return current;
		res = current->Compare(what);
		if (res == 0)
			return current;
		if (res > 0)
			current = current->fLeft;
		else
			current = current->fRight;
	}
}

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Search(const T* what)
{
	WRRedBlackNode<T>* current = fRoot;
	int res;
	while(1)
	{
		if (current->IsNilNode())
			return current;
		res = current->fData->Compare(*what);
		if (res == 0)
			return current;
		if (res > 0)
			current = current->fLeft;
		else
			current = current->fRight;
	}
}

template <class T> void WRRedBlackTree<T>::LeftRotate(WRRedBlackNode<T>* x)
{
	WRRedBlackNode<T>* y = x->fRight;
	x->fRight = y->fLeft;
	if (y->fLeft != NULL)
		y->fLeft->fParent = x; // restore parent link

	y->fParent = x->fParent;
	if (x->IsRoot())
		fRoot = y;
	else
		if (x == x->fParent->fLeft)
			x->fParent->fLeft = y;
		else
			x->fParent->fRight = y;
	y->fLeft = x;
	x->fParent = y;
}

template <class T> void WRRedBlackTree<T>::RightRotate(WRRedBlackNode<T>* x)
{
	WRRedBlackNode<T>* y = x->fLeft;
	x->fLeft = y->fRight;
	if (y->fRight != NULL)
		y->fRight->fParent = x;

	y->fParent = x->fParent;
	if (x->IsRoot())
		fRoot = y;
	else
		if (x == x->fParent->fRight)
			x->fParent->fRight = y;
		else
			x->fParent->fLeft = y;
	y->fRight = x;
	x->fParent = y;
}


template <class T> bool WRRedBlackTree<T>::Insert(WRRedBlackNode<T>* x)
{
	WRRedBlackNode<T>* current = Search(x);

	// check for uniqueness
	if (!current->IsNilNode())
		return false;

	x->Red();

	if (current == fRoot)
		fRoot = x;
	else if (current->IsLeftChild())
		current->fParent->fLeft = x;
	else
		current->fParent->fRight = x;
	
	x->fParent = current->fParent;

	x->fLeft = current;
	current->fParent = x;
	x->fRight = NewSentinel();
	x->fRight->fParent = x;

	while(!x->IsRoot() && x->fParent->IsRed())
	{
		WRRedBlackNode<T>* xp = x->fParent;
		WRRedBlackNode<T>* xpp = xp->fParent;
		if ( xp == xpp->fLeft)
		{
			WRRedBlackNode<T>* y = xpp->fRight;
			if (y->IsRed())
			{
				xp->Black();
				y->Black();
				xpp->Red();
				x = xpp;
			}
			else
			{
				if (x == xp->fRight)
				{
					x = xp;
					LeftRotate(x);
					xp = x->fParent;
					xpp = xp->fParent;
				}
				xp->Black();
				xpp->Red();
				RightRotate(xpp);
			}
		}
		else
		{
			WRRedBlackNode<T>* y = xpp->fLeft;
			if (y->IsRed())
			{
				xp->Black();
				y->Black();
				xpp->Red();
				x = xpp;
			}
			else
			{
				if (x == xp->fLeft)
				{
					x = xp;
					RightRotate(x);
					xp = x->fParent;
					xpp = xp->fParent;
				}
				xp->Black();
				xpp->Red();
				LeftRotate(xpp);
			}
		}
	}
	fRoot->Black();

	fCount++;
	return true;
}


template <class T> void WRRedBlackTree<T>::DeleteFixup(WRRedBlackNode<T>* x)
{
	while(!x->IsRoot() && x->IsBlack())
	{
		if (x->IsLeftChild())
		{
			WRRedBlackNode<T>* w = x->fParent->fRight;
			if (w->IsRed())
			{
				w->Black();
				x->fParent->Red();
				LeftRotate(x->fParent);
				w = x->fParent->fRight;
			}
			if (w->HasBlackSibling())
			{
				w->Red();
				x = x->fParent;
			}
			else
			{
				if (w->fRight->IsBlack())
				{
					w->fLeft->Black();
					w->Red();
					RightRotate(w);
					w = x->fParent->fRight;
				}
				w->SetColor(x->fParent->Color());
				x->fParent->Black();
				w->fRight->Black();
				LeftRotate(x->fParent);
				x = fRoot;
			}
		}
		else
		{
			WRRedBlackNode<T>* w = x->fParent->fLeft;
			if (w->IsRed())
			{
				w->Black();
				x->fParent->Red();
				RightRotate(x->fParent);
				w = x->fParent->fLeft;
			}
			if (w->HasBlackSibling())
			{
				w->Red();
				x = x->fParent;
			}
			else
			{
				if (w->fLeft->IsBlack())
				{
					w->fRight->Black();
					w->Red();
					LeftRotate(w);
					w = x->fParent->fLeft;
				}
				w->SetColor(x->fParent->Color());
				x->fParent->Black();
				w->fLeft->Black();
				RightRotate(x->fParent);
				x = fRoot;
			}
		}

	}
	x->Black();
}

template <class T> WRRedBlackNode<T>* WRRedBlackTree<T>::Remove(WRRedBlackNode<T>* n)
{
	WRRedBlackNode<T>* cut,*child;
    if (n->fLeft->IsNilNode() || n->fRight->IsNilNode())
		cut = n;
	else
		cut = Next(n);

	if (!cut->fLeft->IsNilNode())
	{
		child = cut->fLeft;
		cut->fLeft = NULL;
	}
	else
	{
		child = cut->fRight;
		cut->fRight = NULL;
	}

	child->fParent = cut->fParent;
	if (cut->IsRoot())
		fRoot = child;
	else
		if (cut->IsLeftChild())
			cut->fParent->fLeft = child;
		else
			cut->fParent->fRight = child;

	if (cut != n)
		SWAP(n->fData,cut->fData);

    if (cut->IsBlack())
		DeleteFixup(child);

	fCount--;
	// cleanup any attached leaf?

	return cut;
}

//========================================================================================

template  <class T> class WRRedBlackTreeIterator
{
public:
	WRRedBlackTreeIterator(WRRedBlackTree<T>* tree) { fTree = tree; fCurrent = NULL; }

	virtual T*	Current() { return fCurrent ? fCurrent->fData : NULL; }
	virtual T*	First() { fCurrent = fTree->First();  return Current(); }
	virtual T*	Last() { fCurrent = fTree->Last();  return Current(); }
	virtual T*	Next() { fCurrent = fTree->Next(fCurrent);  return Current(); }
	virtual T*	Prev() { fCurrent = fTree->Prev(fCurrent);  return Current(); }

protected:
	WRRedBlackTree<T>* fTree;
	WRRedBlackNode<T>* fCurrent;
};

#endif
