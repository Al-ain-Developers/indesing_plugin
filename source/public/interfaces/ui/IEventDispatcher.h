//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEventDispatcher.h $
//  
//  Owner: ?
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
#ifndef __IEventDispatcher__
#define __IEventDispatcher__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IEvent.h"

class IEventHandler;
class IEventWatcher;

/**	The event dispatcher maintains a stack of event handlers. Events are dispatched to the event handlers, starting with the topmost event 
	event handler on the stack. The event will be passed on to the next handler in the stack, until a handler returns that it has handled the 
	event.
*/
class IEventDispatcher : public IPMUnknown	{
public:
	/** DefaultIID so that UseDefaultIID() can work for this interface */
	enum { kDefaultIID = IID_IEVENTDISPATCHER };
	
	/** enum for where on the stack to add */
	enum PushWhere { kPushOnTop, kPushOnBottom };

	/**
		Add a new handler to the top or bottom of the stack. Stack may be enlarged
		to fit the new handler. An event handler may only be added once or else
		an assertion violation will occur and Push will do nothing.
	*/
	virtual void Push(IEventHandler *newHandler, PushWhere pushWhere = kPushOnTop ) = 0;
	
	/**
		Remove the ehToRemove from the stack. If ehToRemove is not on the stack, does nothing.
	*/
	virtual void Remove(IEventHandler *ehToRemove) = 0;

	/**
		Return a pointer to the indicated event handler on the stack. By default, return the top event handler.
		ehIndex can range from 0 (top EH) to Depth() - 1 (bottom EH).
	*/
	virtual IEventHandler *Peek(int32 ehIndex = 0) const = 0;
		
	/**
		Return the number of event handlers on the stack.
	*/
	virtual int32 Depth() const = 0;
	
	/**
		Initializes the dispatcher
	*/
	virtual void Init() = 0;

	/**
		Terminates the dispatcher
	*/
	virtual void CleanUp() = 0;
	
	/**
		Dispatch the event. The event is passed to the topmost event handler. If it is not handled, it is passed on to the next handler, and so
		on, until either the event has been handled, or it has been passed to all the event handlers on the stack. Returns true if the event
		was handled, false otherwise.
	*/
	virtual bool16 DispatchEvent(IEvent *theEvent, IEvent::SystemHandledState initialState = IEvent::kShouldCall) = 0;
		
#define ITERATOR_ACCESS_TO_EventTypeList 0
#if 0 //VC can't cope with this
	//Essentially a way of declaring classes derived from IEventDispatcher as 
	//friends of class EventTypeList--Hence if class EventTypeList gets reimplemented
	//so must, e.g., CEventDispatcher.
	class EventTypeList;
	protected: static uint32 GetEventTypeListContents( EventTypeList l){ return l.fContents;}
#endif
	

public:
	class EventTypeList {
#if 0 //VC can't cope with this
	friend uint32 IEventDispatcher::GetEventTypeListContents( EventTypeList l);
#endif
	public:
		enum {kMaxEventTypeValue = 31};
		EventTypeList(){
			fContents = kAllEventTypes;
		}
		EventTypeList( IEvent::EventType t){
			fContents = 1<<t;
		}
		EventTypeList( IEvent::EventType t1, IEvent::EventType t2){
			fContents = 1<<t1 | 1<<t2;
		}
		EventTypeList( IEvent::EventType t1, IEvent::EventType t2, IEvent::EventType t3){
			fContents = 1<<t1 | 1<<t2 | 1<<t3;
		}
		EventTypeList& Add( IEvent::EventType t){ //you can chain Add calls if interested in more than 3 event types
			fContents |= 1<<t;
			return *this;
		}
		EventTypeList& operator|=(EventTypeList l){ fContents |= l.fContents; return *this;}
		EventTypeList& operator&=(EventTypeList l){ fContents &= l.fContents; return *this;}
		EventTypeList operator~() const { return EventTypeList(kAllEventTypes & ~fContents);}
		//could be nonmember friend   inline EventTypeList operator~( const EventTypeList& l){ return EventTypeList(~l.fContents);}
		bool16 Contains(IEvent::EventType t){ return (fContents & (1<<t)) != 0;}
		bool16 Empty(){ return fContents == 0;}
#if ITERATOR_ACCESS_TO_EventTypeList
		class const_iterator {
		public:
			const_iterator() {}
			const_iterator(const EventTypeList::const_iterator& x) : next(x.next), rest(x.rest) {}
			IEvent::EventType operator * () const { return static_cast<IEvent::EventType>(next);}
			const_iterator& operator++()
			{
				do{
					++next;
				}while( (rest >>= 1) && !(rest&1));
				return *this;
			}
			const_iterator operator++(int) {const_iterator old(*this); operator++(); return old;}
			friend bool operator==(const_iterator x, const_iterator y) { return x.rest == y.rest;}
			friend bool operator!=(const_iterator x, const_iterator y) { return x.rest != y.rest;}
		
		private:
			const_iterator(uint32 contents) : next(0), rest(contents)
			{
				if(!(rest&1))
					++*this;
			}
			friend class EventTypeList;
			uint32 next;
			uint32 rest;
		
		};
		const_iterator begin() const { return const_iterator(fContents);}
		const_iterator end() const {return const_iterator(0);}
#endif
		
	private:
		EventTypeList(uint32 contents) : fContents(contents){}
//VC can't cope with this:		static const uint32 kAllEventTypes = (uint32(1)<<IEvent::kEndOfEventTypes) - 2;// subtract 1 to turn on all the bits, subtract another 1 to turn off the low order one
		enum {kAllEventTypes = (uint32(1)<<IEvent::kEndOfEventTypes) - 2};// subtract 1 to turn on all the bits, subtract another 1 to turn off the low order one
		uint32 fContents;
	};

	virtual void AddEventWatcher( IEventWatcher *newWatcher, EventTypeList interest) = 0;
	virtual void AddEventWatcher( IEventWatcher *newWatcher, IEvent::EventType interest) = 0;
	virtual void RemoveEventWatcher( IEventWatcher *newWatcher, EventTypeList interest) = 0;
	virtual void RemoveEventWatcher( IEventWatcher *newWatcher, IEvent::EventType interest) = 0;
	virtual void StopAllEventWatchers() = 0;

};


#endif // __IEventDispatcher__
