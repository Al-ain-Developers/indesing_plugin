//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IObserver.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IOBSERVER__
#define __IOBSERVER__

#include "ShuksanID.h"

class ISubject;
class LazyNotificationData;

//----------------------------------------------------------------------------------------
// Class IObserver
//----------------------------------------------------------------------------------------

/**	This interface provides a notification mechanism for objects that need to be 
	informed of changes made to another object. An observer attaches to the subject interface (ISubject)
	on the object it wants to be notifed of when a change occurs.  The observed object can be 
	another boss object, or itself if the observer is interested in changes made to 
	its own interfaces.  An object is allowed to have multiple IObserver interfaces as long 
	as each observer has a unique interface ID.

   @see ISubject for documentation on the two types of notification available, regular notification and lazy notification.
*/

class INTERFACE_DECL IObserver : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOBSERVER };

		/**	Regular notification of a change in an observed subject; this method is called immediately after the
			change is made, it is not called on undo or redo.
.
			@param theChange represents the change to an object, often this is the ClassID of the command that made the change
			@param theSubject is the subject that changed
			@param protocol is the interface of the subject's boss that changed
			@param changedBy is used to pass additional data about the change, often this is a pointer to the command that caused the change
			@see ISubject::AttachObserver(IObserver*, const PMIID&, AttachmentType) to receive
				regular notification attach to the subject by calling this method specifying 
				an attachment type of regular, or, both if you also want lazy notification. You can
				also receive regular notification by attaching to the subject using
				ISubject::AttachObserver(IObserver*,const PMIID&,const PMIID&).
			@see IObserver::LazyUpdate for lazy notification
		*/
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy) = 0;
			
		/**	If the observer knows which subject(s) to attach itself to, it'll do so with this call
		*/
		virtual void AutoAttach() = 0;
			
		/**	If the observer knows which subject(s) to detach itself from, it'll do so with this call
		*/
		virtual void AutoDetach() = 0;

		/**	Set the interface ID of this observer; normally this is IID_IOBSERVER but if there are several observers
				on a boss they each need to have a different interface ID.
			@param iid is the interface ID of this observer
		*/
		virtual void SetAttachIID(PMIID iid) = 0;

		/**	Get the interface ID of this observer. 
			@return the interface ID of this observer
		*/
		virtual PMIID GetAttachIID() const = 0;
			
		/**	Enable or disable the observer; a disabled observer will not receive an update for a change.
			@param state kTrue to enable, kFalse to disable
		*/
		virtual void SetEnabled(bool16 state) = 0;
			
		/**	Returns kTrue if this observer is enabled, kFalse otherwise
		*/
		virtual bool16 IsEnabled() const = 0;

		/**	Lazy notification of a change in an observed subject; this method is called after the 
			transaction in which the change was performed completes and after undo or redo.

			@param theSubject is the subject that changed
			@param protocol is the interface of the subject's boss that changed
			@param data lazy notification data or nil. Observers must be able to handle a call
				that has nil data. In certain low memory conditions the lazy notification 
				data passed to ISubject::ModelChange may not be passed on to observers.
				The observer must be able to work without data in which case the observer would
				usually refresh its entire state by re-examining all objects of interest.
				See LazyNotificationData for documentation.
			@see ISubject::AttachObserver(IObserver*, const PMIID&, AttachmentType) to receive 
				lazy notification attach to the subject by calling this method specifying an attachment 
				type of lazy, or, both if you also want regular notification.
			@see IObserver::Update for regular notification
		 */
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data) = 0;
};

#endif
