//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISubject.h $
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
#ifndef __ISUBJECT__
#define __ISUBJECT__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "K2SmartPtr.h"
#include "LazyNotificationData.h"

class IObserver;
class IChangeManager;
class IDataBase;
struct void_type
{};


//----------------------------------------------------------------------------------------
// Class ISubject
//----------------------------------------------------------------------------------------

/**	This interface provides a notification mechanism for objects that need to be informed 
	of changes made to another object; the object being changed is known as the subject, the
	object being notified is known as the observer (see IObserver). When an object is modified, 
	its ISubject::ModelChange or ISubject::Change method is called to notify attached observers. 
	There are two kinds of notification, regular notification and lazy notification.

	Regular notification is initiated by calling ISubject::ModelChange or ISubject::Change.
	This causes IObserver::Update methods to be called for observers that are attached to
	this subject using regular attachment. These observers are called within the scope of 
	change method.

	Lazy notification is initiated by calling ISubject::ModelChange. In addition to the regular
	notification described above this also causes IObserver::LazyUpdate methods to be called for 
	observers that are attached to this subject using lazy attachment. These observers are not 
	called within the scope of the ISubject::ModelChange method. Instead, a message is queued 
	and these observers are called later on, when the application is idle.

	Changes to objects which persist in InDesign databases that support undo must be notified using 
	ISubject::ModelChange. For example, if an object in an InDesign document (kDocBoss) is modified,
	then ISubject::ModelChange must be called to notify observers. Changes to objects stored in
	InDesign databases that don't support undo, or to objects that are not persistent, must be
	notified using ISubject::Change. For example, if a widget object changes state, then
	ISubject::Change is called to notify observers.

	Consider a typical notification use case for a change to an object stored in an InDesign database 
	that supports undo. A command (ICommand) modifies the object when its Command::Do method 
	is called. When the Command::DoNotify method is called it calls ISubject::ModelChange which calls 
	observers attached to the object using regular attachment via their IObserver::Update method 
	(regular notification). Additionally, the ISubject::ModelChange method queues a message so that 
	observers attached to the subject using lazy attachment get called later on when the application is 
	idle via their IObserver::LazyUpdate method (lazy notification). Note:
	<ul>
	<li>If the object being modified is persists in an InDesign database that supports undo then 
	ISubject::ModelChange must be used to notify observers of the change.
	<li>Lazy notification is also broadcast on undo or redo, therefore, observers must use lazy attachment 
	in order to be called on undo or redo. On subsequent undo or redo of the change the 
	IObserver::LazyUpdate method gets called. Note that <b>the IObserver::Update method is not 
	called on undo or redo</b>.
	<li>Lazy notification is the most efficient form of notification to use for updating objects in 
	the user interface. IObserver::LazyUpdate gets called once per transaction on the InDesign database since 
	the notification is broadcast after all the changes have been made and the transaction is complete. Contrastingly,
	IObserver::Update may get called several times within a transaction, since the notification is broadcast 
	immediately after the change is made. 
	</ul>

   @see IObserver
*/
class ISubject : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISUBJECT };
	
		/**	Check whether an observer that uses regular attachment is attached to this subject. 

			Note: this method is equivalent to calling 
			ISubject::IsAttached(AttachmentType, IObserver*, const PMIID& interestedIn, const PMIID& asObserver) specifying
			and attachment type of kRegularAttachment.

			@param observer the observer to be checked
			@param interestedIn identifies the interface in this subject that the observer is attached to
			@param asObserver the interface id of the observer
			@return kTrue if the specified observer has been attached
		*/
		virtual bool16 IsAttached(IObserver* observer, 
								 const PMIID& interestedIn,
								 const PMIID& asObserver = IID_IOBSERVER) = 0;

		/**	Attach an observer that uses regular attachment to this subject.

			Note: this method is equivalent to calling 
			ISubject::AttachObserver(AttachmentType, IObserver*, const PMIID& interestedIn, const PMIID& asObserver) 
			specifying an attachment type of kRegularAttachment.

			@param observer the observer to be attached
			@param interestedIn may be used to narrow the scope of interested changes
			@param asObserver must be used if the observer has an interface id that is different than IID_IOBSERVER
		*/
		virtual void AttachObserver(IObserver* observer,
									  const PMIID& interestedIn,
									  const PMIID& asObserver = IID_IOBSERVER) = 0;

		/**	Detach an observer that uses regular attachment from this subject.

			Note: this method is equivalent to calling 
			ISubject::DetachObserver(AttachmentType, IObserver*, const PMIID& interestedIn, const PMIID& asObserver) 
			specifying an attachment type of kRegularAttachment.

			@param observer the observer to be detached
			@param interestedIn identifies the interface in this subject that the observer is attached to
			@param asObserver is the interface id of the observer
		*/
		virtual void DetachObserver(IObserver* observer,
									const PMIID& interestedIn,
									  const PMIID& asObserver = IID_IOBSERVER) = 0;

		/**	Notify observers that are attached to this subject via regular attachment that  
			the object this subject is part of has been changed.

			This method iterates over the observers that are attached to this subject using regular attachment
			and calls their IObserver::Update method (regular notification).

			@param theChange is the actual change, often the ClassID of a command
			@param interestedIn specifies the interface of the object that was modified
			@param changedBy is generic pointer to the object that caused the change, usually a pointer to a command object
			@see IObserver::Update
		*/
		virtual void Change(ClassID theChange, const PMIID& interestedIn = IID_IUNKNOWN, void* changedBy = nil) = 0;

		/**	Notify observers that are attached to this subject via regular attachment that  
			the object this subject is part of has been changed.

			This method iterates over the observers that are attached to this subject using regular attachment
			and calls their IObserver::Update method (regular notification).

			The difference between this method and the other Change method is that the object given
			by the originalSubject parameter is passed into IObserver::Update as the subject that was 
			changed, rather than this subject.

			@param originalSubject is the original subject of the object that was changed
			@param theChange is the actual change, often the ClassID of a command
			@param interestedIn identifies the interface of the object that was modified
			@param changedBy is generic pointer to the object that caused the change, usually a pointer to a command object
			@see IObserver::Update
		*/
		virtual void Change(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn = IID_IUNKNOWN, void* changedBy = nil) = 0;

		/**	Mutes all messages from this object. Muting a subject allows you to make changes 
			to the object without notifying its observers.
			@param muteOn if kTrue, turns mute on; if kFalse, turns mute off
		*/
		virtual void Mute(bool16 muteOn) = 0;

		/** Returns kTrue if this subject is muted.
		*/
		virtual bool16 IsMuted() const = 0;

		/**	Access the internal implementation of the notification mechanism.
			@return the change manager interface pointer
		*/
		virtual IChangeManager* GetChangeManager() const = 0;

			
		/** Notify observers that are attached to this subject via regular or lazy attachment that  
			the object this subject is part of has been changed; this is the ModelChange method you 
			probably want to call.

			This method iterates over the observers that are attached to this subject using regular attachment
			and calls their IObserver::Update method (regular notification). Additionally, this method queues 
			a message so that observers that are attached to the subject using lazy attachment get called 
			later on when the application is idle via their IObserver::LazyUpdate method (lazy notification).

			@pre this subject must be part of an InDesign database that supports undo
			@param theChange is the actual change, often the ClassID of a command
			@param interestedIn identifies the interface of the object that was modified
			@param changedBy pointer to the object that caused the change, usually a pointer to a command object
			@param data contains additional information about the change, nil otherwise; see LazyNotificationData for documentation.
			@see IObserver::Update
			@see IObserver::LazyUpdate
		 */
		virtual void ModelChange(ClassID theChange, const PMIID& interestedIn, 
								void* changedBy = nil, LazyNotificationData* data = nil) = 0;

		/**	Notify observers that are attached to this subject via regular or lazy attachment that  
			the object this subject is part of has been changed. Only use this method if you are sure 
			you cannot use ISubject::ModelChange(ClassID, const PMIID&, void*, LazyNotificationData*).
			
			This method passes the object given by the originalSubject parameter to
			IObserver::Update as the subject that was changed, rather than this subject. However,
			the originalSubject is not available when IObserver::LazyUpdate is called. When the 
			lazy notification occurs, this subject is passed to IObserver::LazyUpdate. 
			If you need access to originalSubject, do so in the IObserver::Update method.

			@pre this subject must be part of an InDesign database that supports undo
			@param originalSubject is the original subject of the object that was changed
			@param theChange is the actual change, often the ClassID of a command
			@param interestedIn identifies the interface of the object that was modified
			@param changedBy is generic pointer to the object that caused the change, usually a pointer to a command object
			@param data contains additional information about the change, nil otherwise; see LazyNotificationData for documentation.
			@see IObserver::Update
			@see IObserver::LazyUpdate
		 */
		virtual void ModelChange(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn, 
								void* changedBy = nil, LazyNotificationData* data = nil) = 0;

		/**	Use of this method is very rare. Call one of the other ModelChange methods
			unless you are sure this one is the right one for your use case. It is
			used to notify that a "snapshot view interface" has changed. For example, 
			the layout widget uses this method to notify that ILayoutControlData
			has changed. ILayoutControlData is implemented as a "snapshot view interface"
			and change to this interface must get undone and redone as changes to 
			the document being viewed get undone and redone.

			@param model pointer to an InDesign database that supports undo
			@param theChange is the actual change, often the ClassID of a command
			@param interestedIn identifies the interface of the object that was modified
			@param changedBy is generic pointer to the object that caused the change, usually a pointer to a command object
			@param data contains additional information about the change, nil otherwise; see LazyNotificationData for documentation.

			@see CREATE_VIEW_PMINTERFACE in "InterfaceFactory.h". 
			@see "Snapshot view interface" extension pattern documentation in the Programming Guide
		 */
		virtual void ModelChange(IDataBase* model, ClassID theChange, const PMIID& interestedIn, 
								void* changedBy = nil, LazyNotificationData* data = nil) = 0;

		/** Type of attachment.
		*/
		enum AttachmentType 
		{
			/** For observers that want regular notification via IObserver::Update.
			*/
			kRegularAttachment = 0, 
			/** For observers that want lazy notification via IObserver::LazyUpdate.
			*/
			kLazyAttachment, 
			/** For observers that want both regular and lazy notification.
			*/
			kBothAttachments
		} ;

		/**	Check whether the observer is attached to this subject. 	
			@param attachType specifies the type of attachment
			@param observer is the observer to be checked
			@param interestedIn identifies the interface in this subject that the observer is attached to
			@param asObserver the interface id of the observer
			@return kTrue if the specified observer is attached, kFalse otherwise
		 */
		virtual bool16 IsAttached(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver) = 0;

		/**	Attach the observer using the given attachment type (regular, lazy or both) to this subject.
			@param attachType specifies the type of attachment the observer uses and controls the type of
				notification it receives, for example regular notification or lazy notification.
			@param observer is the observer to be attached
			@param interestedIn specifies the scope of interested changes; for example if you are interested in 
				a specific interface on this subject pass the interface id here.
			@param asObserver the interface id of the observer
		 */
		virtual void AttachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver) = 0;

		/**	Detach the observer using the given attachment type (regular, lazy or both) from this subject.
			@param attachType specifies the type of attachment
			@param observer is the observer to be detached
			@param interestedIn identifies the interface in this subject that the observer is attached to
			@param asObserver the interface id of the observer
		 */
		virtual void DetachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver) = 0;
};

#endif
