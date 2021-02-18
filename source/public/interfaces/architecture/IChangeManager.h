//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IChangeManager.h $
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
#ifndef __ICHANGEMANAGER__
#define __ICHANGEMANAGER__

#ifndef __PMTYPES__
#include "PMTypes.h"	
#endif

#include "IPMUnknown.h"	
#include "ShuksanID.h"		// IID_ICHANGEMANAGER

//----------------------------------------------------------------------------------------
// Typedefs
//----------------------------------------------------------------------------------------

typedef int32 DependencyLabels;
	// The valid range of labels

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------

const DependencyLabels kNoLabel = 0;

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class ISubject;
class IObserver;
class IPMUnknown;
class LazyNotificationData;
//----------------------------------------------------------------------------------------
// IChangeManager: Abstract Superclass of change managers
//----------------------------------------------------------------------------------------

/** This is an interface to the change manager, which manages subject/observer relationships,
	and subject/observer notifications. You should not need to access this class directly
	unless you are implementing a new subject type (which is quite unusual). Normally, all 
	interaction with the messaging system is either through ISubject or IObserver.

    @see ISubject
	@see IObserver
*/
class IChangeManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICHANGEMANAGER };
			
		/** Register an observer as a dependent of the subject. Normally this is called for you
			from ISubject::AttachObserver.
			@param subject the subject to attach the observer to
			@param observer the observer to attach
			@param observerIID the IID the change manager should use to access the observer
			@param interestedIn the type of change this observer wants to be notifed about
		*/
		virtual void AddDependency(ISubject* subject, IObserver* observer,
									const PMIID& observerIID, const PMIID& interestedIn,
									bool lazy) = 0;
	
		/** Remove an observer as a dependent of the subject. Normally this is called for you
			from ISubject::DetachObserver. If an observer is attached in multiple ways to the
			same subject (e.g. for multiple protocols) this detaches only one attachment 
			relationship and leaves the others unchanged.
			@param subject the subject to detach the observer from
			@param observer the observer to attach
			@param observerIID which observer(in case the boss has multiple) to detach
			@param interestedIn the type of change this observer originally registered for
		*/
		virtual void RemoveDependency(ISubject* subject, IObserver* observer,
									const PMIID& observerIID, const PMIID& interestedIn,
									bool lazy) = 0;
	
		/** Determine if a dependency already exists
			@param subject the subject we're asking about
			@param observer the observer we're asking about
			@param observerIID which observer(in case the boss has multiple) to check for
			@param interestedIn the type of change this observer originally registered for
			@return kTrue if the observer is attach to the subject
		*/
		virtual bool16 HasDependency(ISubject* subject, IObserver* observer,
									const PMIID& observerIID, const PMIID& interestedIn,
									bool lazy) = 0;

		/** Remove all dependencies that reference this subject
		*/
		virtual void RemoveSubject(ISubject* theSubject) = 0;

		/** Remove all dependencies that reference this observer
			@param observer the observer we're asking about
			@param observerIID which observer(in case the boss has multiple) to remove
		*/
		virtual void RemoveObserver(IObserver* theObserver, const PMIID& observerIID) = 0;

		/** Remove all dependencies that reference the subject. 
		*/
		virtual void RemoveSubject(const UIDRef& theSubject) = 0;

		/** Remove all dependencies that reference this observer
			@param theObserver the observer we're asking about
			@param observerIID which observer(in case the boss has multiple) to remove
		*/
		virtual void RemoveObserver(const UIDRef& theObserver, const PMIID& observerIID) = 0;

		/** Notifies dependents of "notifier" that it has changed. This is normally called
			by ISubject::Change, and will iterate over the observers that are attached to
			the subject (if there are any) and call their Update functions.
			@param subject that changed (specifies which observers to call)
			@param theChange type of the change, often a ClassID of a command
			@param interestedIn specifies the interface the change affected
			@param changedBy the change agent (may be nil; but often this is the command that 
			initiated the broadcast)
		*/
		virtual void SubjectChanged(ISubject* subject, ClassID theChange,
									const PMIID& interestedIn, void* changedBy) = 0;
	
		//-------------------------------------------------------------------------------
		/**@name 	For Internal Use Only	*/
		//@{-----------------------------------------------------------------------------

		/*  Similar to the previous method but this one lets you start the dependency notification
			part way along the dependecy chain, i.e. with subject's observers but notifying them that
			it was in fact originalSubject that changed. */
		virtual void SubjectChanged(ISubject* originalSubject, ISubject* subject, 
									ClassID theChange, const PMIID& interestedIn, void* changedBy) = 0;

		virtual void SubjectModelChanged(ISubject* subject, IDataBase* model, 
								  ClassID theChange, const PMIID& interestedIn, 
									void* changedBy, LazyNotificationData* data) = 0;

		virtual void SubjectModelChanged(ISubject* originalSubject, ISubject* subject, IDataBase* model, 
								  ClassID theChange, const PMIID& interestedIn, 
									void* changedBy, LazyNotificationData* data) = 0;

		virtual void LazySubjectChanged(ISubject* subject, const PMIID& interestedIn, 
										const LazyNotificationData* data) = 0;

#ifdef DEBUG
		// returns IID that observer is attached to.
		virtual PMIID IsObserverAttached(IObserver* theObserver, const PMIID& observerIID) = 0;
		virtual void Dump() = 0;
#endif

		/** Returns true if it's OK to send a message. Check this before doing anything that
			might cause a SubjectChanged() during a purge operation. If the purge originated
			from the change manager, it will cause a fatal error to send the message. In that
			case, you can prevent it by calling CanSendMessage, which will return false if 
			the change manager is in the middle of handling an add or remove and cannot send
			a message.
			@return bool16	true if it's ok to use the ChangeManager, false otherwise
		*/
		virtual bool16 CanSendMessage() const = 0;

	protected:
		IChangeManager();

	//@}-----------------------------------------------------------------------------
};

//----------------------------------------------------------------------------------------
// inlines
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// IChangeManager constructor 
//----------------------------------------------------------------------------------------

inline IChangeManager::IChangeManager()
{
}


#endif
