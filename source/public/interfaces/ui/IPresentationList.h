//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPresentationList.h $
//  
//  Owner: Dave Burnard
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
//  Purpose: IPresentationList provides an interface for collecting a set of presentations. It also provides methods for opening
//  and closing a presentation.
//  
//========================================================================================

#pragma once
#ifndef __IPRESENTATIONLIST__
#define __IPRESENTATIONLIST__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "AppUIID.h"

#include "IDocumentPresentation.h"

/** This interface maintains an unordered list of document presentations.
	It's primary use is on the document boss, where it keeps track of all of the presentations open on the document.
	
	Also:
		@see IWindowList (which served this purpose prior to CS4, and from which IPresentationList is derived)
		@see IDocumentUIUtils (for ordered access to the open document presentations.
*/

class IPresentationList : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IPRESENTATIONLIST};

	/** Adds the presentation to the list. 
		@param newPres the presentation to add
	*/
	virtual void AddPresentation(IDocumentPresentation* newPres) = 0;

	/** Notify the list that a presentation has opened. Adds presentation to list if not already there, and sends out a broadcast to let others know
		 that a presentation has been added to the list.
		@param pres the presentation which was opened
	*/
	virtual void PresentationHasOpened(IDocumentPresentation* pres) = 0;
	
	/** Notify the list that a presentation has closed. Removes window from list if  there, and sends out a broadcast to let others know
		 that a presentation has been removed from the list.
		@param win the window which was closed
	*/
	virtual void PresentationHasClosed(IDocumentPresentation* pres) = 0;

	/** Close the nth presentation by creating a command
		@param index the index of the presentation to close
	*/
	virtual void CloseNthPresentation(int32 n) = 0;
	
	/** Close all the presentations in the list by creating commands
	*/
	virtual void CloseAllPresentations() = 0;
	
	/** IPresentationList::iterator to do the usual iterator things on an IPresentationList
	*/
	class iterator
	{
		friend class IPresentationList;
		public:
			typedef std::ptrdiff_t difference_type;
			typedef IDocumentPresentation* value_type;
			bool16 operator==(const iterator& rhs) const { return n == rhs.n && list == rhs.list;}
			bool16 operator!=(const iterator& rhs) const { return !(*this == rhs);}
			iterator& operator++() { ++n; return *this;}
			IDocumentPresentation* operator*() const { return list->At(n);}
		private:
			IPresentationList* list;
			int32 n;
			iterator();
			iterator(IPresentationList* inList, int32 inN) : list(inList), n(inN) {}
	};
	/** IPresentationList::reverse_iterator to do the usual reverse iterator things on an IPresentationList
	*/
	class reverse_iterator
	{
		friend class IPresentationList;
		public:
			typedef std::ptrdiff_t difference_type;
			typedef IDocumentPresentation* value_type;
			bool16 operator==(const reverse_iterator& rhs) const { return n == rhs.n && list == rhs.list;}
			bool16 operator!=(const reverse_iterator& rhs) const { return !(*this == rhs);}
			reverse_iterator& operator++() { --n; return *this;}
			IDocumentPresentation* operator*() const { return list->At(n-1);}
		private:
			IPresentationList* list;
			int32 n;
			reverse_iterator();
			reverse_iterator(IPresentationList* inList, int32 inN) : list(inList), n(inN) {}
	};
	friend class iterator;
	friend class reverse_iterator;

	iterator begin() { return iterator(this, 0);}
	iterator end(){ return iterator(this, size());}
	reverse_iterator rbegin() { return reverse_iterator(this, size());}
	reverse_iterator rend() { return reverse_iterator(this, 0);}
	iterator find(IDocumentPresentation* it) { int32 index = Find(it); return (index == -1) ? end() : iterator(this, index);}
	int32 	size() const { return Length();}
	int32 	empty() const { return Length()==0;}
	IDocumentPresentation* 	at(int32 n) { return At(n);}
	
		/** Check if a particular window is in this list.
		@return kTrue if the given window is in this window list, otherwise kFalse
	*/
	virtual int32		Find(IDocumentPresentation*) const = 0;
	virtual int32		Length() const = 0;
	virtual IDocumentPresentation*		At(int32 index) const = 0;
	
	IDocumentPresentation*		First() const { return At(0);}
};


#endif