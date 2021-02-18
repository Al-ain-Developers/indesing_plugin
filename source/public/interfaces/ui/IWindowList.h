//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWindowList.h $
//  
//  Owner: frits habermann
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
//  Purpose: IWindowList provides an interface for collecting a set of windows. It also provides methods for opening
//  and closing a window.
//  
//========================================================================================

#pragma once
#ifndef __IWINDOWLIST__
#define __IWINDOWLIST__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IWindow.h"

class IWindow;
/** This interface maintains a list of windows. There's an implementation of this interface on the application boss, holding all the application's windows, 
	and another on the document boss, holding all the document's windows.
*/
class IWindowList : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IWINDOWLIST};

	/** Simply adds the window to the list. 
		@param newWin the window to add
	*/
	virtual void AddWindow(IWindow *newWin) = 0;

	/** Notify window list that "win" was opened. Adds window to list if not already there, and sends out a broadcast to let others know
		 that a window has been added to the list.
		@param win the window which was opened
	*/
	virtual void WindowOpened(IWindow * win) = 0;
	
	/** Notify window list that "win" was closed. Adds window to list if not already there, and sends out a broadcast to let others know
		 that a window has been removed from the list.
		@param win the window which was closed
	*/
	virtual void WindowClosed(IWindow * win) = 0;

	/** Close the window at position index by creating a command
			Note: Calling this method on an arbitrary IWindow, is not recommended.
		@param index the index of the window to close
	*/
	virtual void CloseWindow(int32 index) = 0;
	
	/** Close all the windows in the list by creating commands
			Note: Calling this method on an arbitrary set of IWindows, is not recommended.
	*/
	virtual void CloseAll() = 0;
	
	/** Returns the object associated with the SysWindow. Usually this will be an IWindow, although it could be another interface, if 
		 the object doesn't have an associated IWindow. Returns nil if the SysWindow is not in the list.
		 @param window	the OS window you're interested in.
		 @return a pointer to an interface on that window's boss.
	*/
	virtual IPMUnknown *GetPMUnknown(SysWindow window) = 0;
	
	

#ifdef ID_DEPRECATED
	/** Obsolete. I don't think this has ever worked.
	*/
	virtual IWindow* GetFrontWindow() = 0;
#endif
		
	/** Check if a particular window is in this list.
		@return kTrue if the given window is in this window list, otherwise kFalse
	*/
	virtual bool16	IsWindowInList(IWindow *) const = 0;
	
	/** IWindowList::iterator to do the usual iterator things on an IWindowList
	*/
	class iterator
	{
		friend class IWindowList;
		public:
			typedef std::ptrdiff_t difference_type;
			typedef IWindow* value_type;
			bool16 operator==(const iterator& rhs) const { return n == rhs.n && list == rhs.list;}
			bool16 operator!=(const iterator& rhs) const { return !(*this == rhs);}
			iterator& operator++() { ++n; return *this;}
			IWindow* operator*() const { return list->GetNthWindow(n);}
		private:
			IWindowList* list;
			int32 n;
			iterator();
			iterator(IWindowList* inList, int32 inN) : list(inList), n(inN) {}
	};
	/** IWindowList::reverse_iterator to do the usual reverse iterator things on an IWindowList
	*/
	class reverse_iterator
	{
		friend class IWindowList;
		public:
			typedef std::ptrdiff_t difference_type;
			typedef IWindow* value_type;
			bool16 operator==(const reverse_iterator& rhs) const { return n == rhs.n && list == rhs.list;}
			bool16 operator!=(const reverse_iterator& rhs) const { return !(*this == rhs);}
			reverse_iterator& operator++() { --n; return *this;}
			IWindow* operator*() const { return list->GetNthWindow(n-1);}
		private:
			IWindowList* list;
			int32 n;
			reverse_iterator();
			reverse_iterator(IWindowList* inList, int32 inN) : list(inList), n(inN) {}
	};
	friend class iterator;
	friend class reverse_iterator;

	iterator begin() { return iterator(this, 0);}
	iterator end(){ return iterator(this, WindowCount());}
	reverse_iterator rbegin() { return reverse_iterator(this, WindowCount());}
	reverse_iterator rend() { return reverse_iterator(this, 0);}


public://until I get everyone using the iterators

	/** Return the n'th window
		@param n which window
		@return the requested window
	*/
	virtual IWindow* GetNthWindow(int32 n ) = 0;
	
	/** Return the number of windows in the list. 
		@return count of windows
	*/
	virtual int32 WindowCount() const = 0;

	/** Returns the list of document windows sorted in z-order.
		@return list of sorted document windows.
	 */
	virtual const K2Vector<IWindow *>& GetZOrderSortedDocumentWindows() const = 0;

	/** Set docWindow to topmost in the sorted list
	 */

	virtual void MakeDocumentWindowTopmost(IWindow * docWindow) = 0;


#ifdef ID_DEPRECATED
	/** Obsolete, use WindowCount() instead.
	*/
	int32 Length() const {return WindowCount();};
#endif
};


#endif