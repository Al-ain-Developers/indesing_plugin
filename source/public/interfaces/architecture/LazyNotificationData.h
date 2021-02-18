//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/LazyNotificationData.h $
//  
//  Owner: Habib Khalfallah
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
#ifndef __LazyNotificationData__
#define __LazyNotificationData__

#include <boost/noncopyable.hpp>

/** This is the abstract interface for lazy notification data.
	LazyNotificationData objects get passed to the ISubject::ModelChange function.
	ISubject::ModelChange adds the LazyNotificationData object to a queue and associates
	it with a message ID, the PMIID protocol argument passed to ISubject::ModelChange.
	Lazy notifications are broadcast at idle time by the InDesign runtimes. When the lazy 
	notification gets broadcast, the observer's LazyUpdate function is called and the LazyNotificationData
	object is passed to it.

	The LazyNotificationData interface supports two functions: Add, and Clone. 
	What are these functions good for? 

	During the sequence, there can be multiple attempts to add the same message ID to the queue.
	When the LazyNotificationData is nil, the first attempt will add the message to the queue
	and all subsequent attempts will not change what's in the queue. When the LazyNotificationData 
	is not nil, the first attempt adds the LazyNotificationData  to the queue and gives
	it its message ID. In the consecutive attempts, the LazyNotificationData  
	in the queue is modified. The way this is done is by having the InDesign runtimes
	call the Add function on the LazyNotificationData already in the queue and pass it
	the new lazy notification data as argument.

	At Undo, the InDesign runtimes queue up the same message IDs that were queued up in Do, 
	and modify their LazyNotificationData's (if the Do LazyNotificationData was not nil). 
	If the Do LazyNotificationData is nil, at Undo
	we simply queue the same message ID with a nil LazyNotificationData. If the Do LazyNotificationData 
	is not nil, at Undo we ask the Do LazyNotificationData to generate the Undo LazyNotificationData
	for us and queue the same message ID with the new generated LazyNotificationData. This is achieved
	by getting the InDesign runtimes to call the Clone function of the original LazyNotificationData with boolean 
	argument set to true. At Redo, all we do is queue up the same message IDs and LazyNotificationData's that 
	were queued up in Do.
*/

class PUBLIC_DECL LazyNotificationData : public boost::noncopyable
{
public:
	/**
		Join the @param other IN LazyNotificationData pointer argument to the this.
	*/
	virtual void  Add (const LazyNotificationData* other)  = 0;

	/**
		If the @param undoing IN is false generate an exact copy of this. If the @param undoing IN 
		is true generate an undo version of this (swap the adds and deletes).
	*/
	virtual LazyNotificationData*  Clone (bool16 undoData) const = 0;
	
	/** Mark the notification data indicating that everything needs rebuilding*/
	virtual void MarkShouldRebuildAll () = 0;

	/** Returns kTrue if nil pointer should be broadcast to observers indicating
	that the lazy notification data should not be used (the observer
	should refresh its state entirely), kFalse otherwise. Indicates that a lazy
	notification data object detected too many changes occuring within a single
	sequence, and it is preferential for observers to refresh their state completely
	from the model. For example, if a sequence created and deleted many page items, 
	the lazy notification data object would be called to merge another object on 
	each modification (LazyNotificationData::Add). At some point, the lazy notification
	data object could decide to stop merging data, and indicate the observer should just
	re-build all state from the model.
	*/
	virtual bool ShouldRebuildAll () const = 0;

	/**
		Virtual destructor.
	*/
	virtual ~LazyNotificationData()
	{};
	
	/** Used to validate the data held in the LazyNotificationData.
		This is called internally after a LazyNotificationData has
		been cloned for undo. It may be called more often
		than that later but for now we don't want to call
		it too much because we want to avoid performance
		problems. (This is only called in debug)
	*/
	virtual void Validate(IDataBase *db) = 0;
};

#endif