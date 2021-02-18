//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SimpleLink.h $
//  
//  Owner: Steve Pellegrin
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
#if !defined(__SimpleLink__)
#define __SimpleLink__

// ----- Includes -----

#include "K2Debugging.h"

//========================================================================================
//	Class SimpleLink
//     Used to construct bi-directional queues that can be used as lists.
//========================================================================================

template<class T>
class SimpleLink
{
public:
		typedef	object_type data_type;

public:
	SimpleLink()
		: fParent(nil)
		{Empty();}
	SimpleLink(const SimpleLink<T> &other)
		{Copy(other);}

	~SimpleLink()
		{}
				
	void LinkBefore(SimpleLink<T> *next);
	void LinkAfter(SimpleLink<T> *prev);
	void Unlink();

	void SetParent(T *parent)
		{fParent = parent;}
	T *GetParent()
		{return fParent;}
	const T *GetParent() const
		{return fParent;}
		
	SimpleLink<T> *Previous() const
		{return fPrev;}
	SimpleLink<T> *Next() const
		{return fNext;}

	void Empty()
		{fNext = fPrev = this;}
	bool IsEmpty() const
		{return (fNext == this);}
			
	SimpleLink<T> &operator=(const SimpleLink<T> &other)
		{Copy(other); return *this;}

public:
	// Class methods
	static uint32 ListSize(SimpleLink<T> *head);
	static SimpleLink<T> *FindPrevious(SimpleLink<T> *startLink, uint32 count);
	static void Detach(SimpleLink<T> *first, SimpleLink<T> *last);
	static void AttachAfter(SimpleLink<T> *head, SimpleLink<T> *first, SimpleLink<T> *last);

private:
	void Copy(const SimpleLink<T> &other);
		
private:
	SimpleLink<T> *		fPrev;
	SimpleLink<T> *		fNext;
	T *					fParent;
};


//========================================================================================
//	LinkBefore
//========================================================================================
template<class T>
void SimpleLink<T>::LinkBefore
(
	SimpleLink<T> *		next
)
{
	ASSERT_MSG(IsEmpty(), "SimpleLink::LinkBefore() - Already linked!");

	fNext = next;
	fPrev = next->fPrev;
	fNext->fPrev = fPrev->fNext = this;
}


//========================================================================================
//	LinkAfter
//========================================================================================
template<class T>
void SimpleLink<T>::LinkAfter
(
	SimpleLink<T> *		prev
)
{
	ASSERT_MSG(IsEmpty(), "SimpleLink::LinkAfter() - Already linked!");

	fPrev = prev;
	fNext = prev->fNext;
	fNext->fPrev = fPrev->fNext = this;
}


//========================================================================================
//	Unlink
//========================================================================================
template<class T>
void SimpleLink<T>::Unlink()
{
	fNext->fPrev = fPrev;
	fPrev->fNext = fNext;
	Empty();
}


//========================================================================================
//	Copy
//========================================================================================
template<class T>
void SimpleLink<T>::Copy
(
	const SimpleLink<T> &	other
)
{
	// If the other link is empty, make this one empty too.
	// Otherwise, use the other link's pointers.
	if (other.IsEmpty())
	{
		this->Empty();
	}
	else
	{
		// Hmmm... I wonder whether this is a good thing?
		fNext = other.fNext;
		fPrev = other.fPrev;
	}
	fParent = other.fParent;
}


//========================================================================================
//	ListSize (Class method)
//========================================================================================
template<class T>
uint32 SimpleLink<T>::ListSize
(
	SimpleLink<T> *		head
)
{
	uint32 count = 0;
	SimpleLink<T> *link = head->Next();
	while (link != head)
	{
		count++;
		link = link->Next();
	}

	return count;
}


//========================================================================================
//	FindPrevious (Class method)
//========================================================================================
template<class T>
SimpleLink<T> *SimpleLink<T>::FindPrevious
(
	SimpleLink<T> *		startLink,
	uint32				count
)
{
	SimpleLink<T> *endLink = startLink;
	while (count--)
	{
		endLink = endLink->Previous();
	}

	return endLink;
}


//========================================================================================
//	Detach (Class method)
//========================================================================================
template<class T>
void SimpleLink<T>::Detach
(
	SimpleLink<T> *		first,
	SimpleLink<T> *		last
)
{
	first->fPrev->fNext = last->fNext;
	last->fNext->fPrev = first->fPrev;
}


//========================================================================================
//	AttachAfter (Class method)
//========================================================================================
template<class T>
void SimpleLink<T>::AttachAfter
(
	SimpleLink<T> *		head,
	SimpleLink<T> *		first,
	SimpleLink<T> *		last
)
{
	last->fNext = head->fNext;
	last->fNext->fPrev = last;
	first->fPrev = head;
	head->fNext = first;
}

#endif	// __SimpleLink__