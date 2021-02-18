//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IM2MMessageListener.h $
//  
//  Owner: dwaterfa
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __IM2MMessageListener__
#define __IM2MMessageListener__

#include "IPMUnknown.h"

#include "AppFrameworkID.h"
#include "OMTypes.h"

class IClassInfo;
class IPMStream;
class IHierarchy;


//
// AdobePatentID="P866" (dwaterfa 10/15/08)
//

/**
	Model To Model Listeners are a low level mechanism to "listen to" (vs
	Subject/Observer) changes to persistent objects in a database. It was used
	internally in CS4 to revise the way TextWrap and TextFrames detect changes
	to the the myriad number of properties and objects they depend on.
	
	For example, MultiColumnTextFrames are dependent on their parent Spline for
	its stroke, stroke alignment, text inset, movement relative to the spread,
	etc.

	Any changes to these properties requires explict action by the MCF to
	manage its size and/or text content.
	
	Listeners are registered with K2 service providers thus:
	
		<pre>
	Class
	{
		kFooListenerServiceBoss,
		kInvalidClass,
		{
			IID_IK2SERVICEPROVIDER, kM2MMessageListenerServiceProviderImpl,
			IID_IM2MMESSAGELISTENER, kFooListenerImpl,
		}
	}
	    </pre>
	
	Listeners can be attached to any persistent objects in the system and this
	attachment is determined by the M2MMessageManager on the first change to a
	persistent instance of a class by calling all the Listeners on their 
	GetMessagesFor() method. A Listener which wishes to receive further
	notifcation of changes to any instance of the specified class must return a
	list of "messages" in the form of PMIIDs associated with the class.
	
	The next time any implementation which implement one of the specified IIDs
	on that class changes the Listener will be called at its Message() method.
	
	Listeners which use the MessageHelper::AddPrivateData() method to add
	PrivateData will be called back on their Validate() method when the Command
	Stack goes empty, typically, but not exclusively.

	In Validate() they can fire commands (or make direct model changes) which
	will be associated with the same transaction as the command that is just
	finishing.
	
	Listeners have several advantages over the traditional Subject/Observer
	mechanism:
	
	1. Listeners do not need to know or rely on known Commands or Protocols in order to find out about changes to any class it is listening to.
	
	2. Listeners are typically called immediately before the implementation it is listening to changes - allowing it to take read and save (in PrivateData) the state of the implementation and compare it to the final state at Validate() time. This allows detailed understanding of the actual change that took place on the particular boss.
	
	3. Listeners can listen to many changes and defer their reaction until Validate() at which time they can decide how to proceed. This improves performance, and in some cases correctness, because the Listener does not have to react to every change as an Observer has to.
	
	4. Listeners can listen to messages in the context of their place in the IHierarchy (Ancestor, Descendent) without having to explicitly listen to the parent or descendent objects. This quite useful when changes to Ancestor, such as a transform, effectively changes position of the object being listened to but without and explit change to any of it's interfaces.
	
	See CM2MMessageListener for a simplified way to implement Listeners which
	wish to have PrivateData (as most will).
*/

class PUBLIC_DECL IM2MMessageListener : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IM2MMESSAGELISTENER };

	/**
	Return a pointer to the vector of PMIID messages that the Listener is
	interested in about the specified Class. If the Listener is not interested
	in the class then it should return nil.
	*/
	virtual void	GetMessagesFor(const IClassInfo* cInfo,
									const PMIID*& targetM,
									uint32& targetMSize,
									const PMIID*& ancestorM,
									uint32& ancestorMSize,
									const PMIID*& descendentM,
									uint32& descendentMSize,
									const PMIID*& unrelatedM,
									uint32& unrelatedMSize) const = 0;

	/**
	The Relation enum describes the relationship in IHierarchy terms between
	the boss the Listener is listening to, specified by
	MessageHelper::GetTarget() and ValidateHelper::GetTarget(), and the boss
	the message was originated from.

	Note that messages of Relation other than kTarget are by definition the
	result of a explit call by another Listener to forward the message from a
	boss that they are listening to to another boss. MessageHelper::Forward()
	is one way to do this.
	*/
	enum Relation {
		/**
		The message is from a boss that is an ancestor to, but NOT the parent
		of, the boss the Listener is listening to.
		*/
		kHierAncestor	= -2,

		/**
		The message is from a boss that is the parent of the boss the Listener
		is listening to.
		*/
		kHierParent		= -1,

		/**
		The message is from the boss that Listener is listening to.
		*/
		kTarget			= 0,

		/**
		The message is from a boss that is the child of the boss the Listener
		is listening to.
		*/
		kHierChild		= 1,

		/**
		The message is from a boss that is the descendent of, but NOT the child
		of, the boss the Listener is listening to.
		*/
		kHierDescendent	= 2,

		/**
		The message is from a boss that is unrelated by IHierarchy to the boss
		the Listener is listening to.
		*/
		kUnrelated
	};

	class	PrivateData;
	class	ChangeData;

	/**
	Helper class used for calls to Message().
	*/
	class PUBLIC_DECL MessageHelper
	{
	public:
		/**
		Returns the Database of the boss which is the target of the message.
		This is the boss the Listener is listening to.
		@return Pointer to IDataBase
		*/
		virtual IDataBase*		GetDataBase() const = 0;

		/**
		Returns the boss which is the target of the message. This is the boss
		the Listener is listening to.
		@return Pointer to IPMUnknown
		*/
		virtual const IPMUnknown* GetTarget() const = 0;

		/**
		Returns a reference to the boss which is the target of the message.
		This is the boss the Listener is listening to.
		@return UIDRef
		*/
		virtual UIDRef			GetTargetRef() const = 0;

		/**
		Returns the ClassID of the boss which is the target of the message.
		This is the boss the Listener is listening to.
		@return ClassID
		*/
		virtual ClassID			GetTargetClassID() const = 0;

		/**
		Returns the ChangeData describing the message.
		@return Reference to ChangeData
		*/
		virtual const ChangeData& GetChange() const = 0;

		/**
		Returns kTrue if the original source of the message was from a call to
		any of the M2MMessageManager::PreChangeMessage() or
		M2MMessageManager::PreChangeMessageAllowDuplicate() methods. Messages of
		this type come from a call to PreDirty() and thus mean that the changing
		implementation has not yet been changed. Callees are free to query the
		changing implementation for pre-changed values.
		@return kTrue if from prechange, kFalse otherwise
		*/
		virtual bool16			GetFromPreChange() const = 0;

		/**
 		In the most common usage driven from PMPersist::PreDirty() the
		M2MMessageManager only delivers the same message to the same Listener
		once per "transaction" that is ended by a call to Validate().
		
		Certain implementations however, such as IHierarchy and ITransform,
		affect other bosses other than themselves and so repeat changes are
		meaningful to Listeners.

		We expect that the number of implementations in this class to be very,
		very small (otherwise performance will suffer).

		Returns kTrue if the original source of the message was from a call to
		any of the M2MMessageManager::PreChangeMessageAllowDuplicate() methods
		AND the message is a duplicate of a message that was already received
		by the target of the message.
		@return kTrue if a duplicate message.
		*/
		virtual bool16			GetIsDuplicateChange() const = 0;

		/**
		Messages are delivered to the set of Listeners listening to a boss in
		an indeterminate order. Some Listeners, because the data they are
		managing is itself changed through the actions of other Listeners, have
		a difficult time ensuring cached data is properly invalidated. The
		kPageItemTransformImpl is good example of this.
		
		The DeferMesageToEnd() method provides a way to affect this delivery
		order in a limited way by asking that the message be re-delivered to
		the Listener after all the other Listeners have been called. This works
		when the the actions of the Listener itself have no side effects on
		other bosses or implementations.

		Note that the callig order between Listeners who have also asked to
		have the message deferred to the end is still indeterminate
		@return kTrue if the message was deferred
		*/
		virtual bool16			GetWasDeferred() const = 0;

		/**
		This methods allows the Listener to specify a pointer to private data
		that will be passed into subsequent calls to the Message() and
		Validate() methods.

		Note that the M2MMessageManager will only call Validate() must provide private datarequired* in order to get called
		during Validate().
		
		Although the data is private, it's lifetime is controlled by the
		M2MMessageManager and will be deleted by it at the end of the
		'transaction'.
		*/
		virtual void			AddPrivateData(PrivateData* data) = 0;

		/**
		This method allows the Listener to have the message re-delivered after
		all other Listeners of the same message have been called.
		See GetWasDeferred() above for more information.
		*/
		virtual void			DeferMessageToEnd() = 0;

		/**
		Forwards the same message but to a new boss.
		@param newTargetBoss Pointer to the boss which will be the target of the message
		@param relationToTarget The Relation value which describes the relationship between the targetBoss and the boss which was the Listener is listening to.
		*/
		virtual void			Forward(const IPMUnknown* newTargetBoss,
										Relation relationToTarget) = 0;

		/**
		Replaces the PMIID message with the one specified, leaving the message
		context the same in regards to prechange and duplicate, and forwards it
		to a new boss.
		@param newTargetBoss Pointer to the boss which will be the target of the message
		@param relationToTarget The Relation value which describes the relationship between the targetBoss and the boss which was the Listener is listening to.
		@param overrideIID New PMIID for the message.
		*/
		virtual void			ForwardAs(const IPMUnknown* newTargetBoss,
										Relation relationToTarget,
										PMIID overrideIID) = 0;

		/**
		Send a new message which will appear to other Listeners as a
		non-prechange, non-duplicate message (see GetFromPreChange() and
		GetIsDuplicateChange()).
		@param targetBoss Pointer to the boss which will be considered the target of the message
		@param origTargetBoss Pointer to the boss which will be considered the original target of the message. May be nil if originalRelation is kTarget. If originalRelation is not kTarget then must not be nil and not equal to targetBoss.
		@param originalRelation The Relation value which describes the relationship between the targetBoss and the origTargetBoss.
		@param idd PMIID of the message
		*/
		virtual void			Message(const IPMUnknown* targetBoss,
										const IPMUnknown* originalTargetBoss,
										Relation originalRelation,
										PMIID iid) = 0;

		/**
		Forwards the specified overrideIID to the parent Spread of the specified
		PageItem.

		Note that by custom IIDs change by the caller to reflect the hierarchy
		relationship when they are forward - for example IID_IGEOMETRY becomes
		IID_IHIERARCHY_GEOMETRY.

		@param hier PageItem to find the Spread relative to
		@param overrideIID PMIID of the message, if kInvalidInterfaceIID then the current message is forwarded, othewise the value specified is used. You will get asserts if the override value is the SAME as the current value.
		@return kTrue if we forwarded to someone
		*/
		virtual bool16			ForwardToSpreadOf(IHierarchy* hier,
										PMIID overrideIID = kInvalidInterfaceID) = 0;

		/**
		Forwards the specified overrideIID to the Hierarchy Parent of the
		specified PageItem.

		We do not forward to Spread Layers or the Spread or to Parents who
		do not think we are their child by IHierarchy.

		Note that by custom IIDs change by the caller to reflect the hierarchy
		relationship when they are forward - for example IID_IGEOMETRY becomes
		IID_IHIERARCHY_GEOMETRY.

		@param hier PageItem to find the Parent relative to
		@param overrideIID PMIID of the message, if kInvalidInterfaceIID then the current message is forwarded, othewise the value specified is used. You will get asserts if the override value is the SAME as the current value.
		@return kTrue if we forwarded to someone
		*/
		virtual bool16			ForwardToParentOf(IHierarchy* hier,
										PMIID overrideIID = kInvalidInterfaceID) = 0;

		/**
		Forwards the specified overrideIID to the Descendents of the specified
		PageItem. Descendents are defined here to be by IHierarchy or by
		IAppearanceList.

		@param hier PageItem to find the Descendent relative to
		@param overrideIID PMIID of the message, if kInvalidInterfaceIID then the current message is forwarded, othewise the value specified is used. You will get asserts if the override value is the SAME as the current value.
		@return kTrue if we forwarded to someone
		*/
		virtual bool16			ForwardToDescendentsOf(IHierarchy* hier,
										PMIID overrideIID = kInvalidInterfaceID) = 0;

	protected:
		///
		MessageHelper();
		///
		~MessageHelper();

	private:
		///
		MessageHelper(const MessageHelper&);
		///
		MessageHelper& operator=(const MessageHelper&);

	};

	/**
	Notification that a message has been sent to a boss listened to by the
	callee Listener. It is ASSERT()able that the only messages that a Listener
	will see are part of the set returned by what was returned from
	GetMessagesFor().

	Listeners may only do direct modifications to data in
	this context (do not fire commands) and keep their work to a minimum in
	the interest of performance.

	Those Listeners which need to do major work, such as firing commands, must
	create PrivateData and defer this work to a PrivateData::Validate() method.
	@param helper Reference to ChangingHelper boss.
	@param data Reference to PrivateData class created in a previous call in the same M2MMessageManager 'transaction'. See MessageHelper::AddPrivateData().
	*/
	virtual void	Message(MessageHelper& helper, PrivateData* data) = 0;

	/**
	A Listener which has previously created PrivateData is being called to
	create a new instance of PrivateData and initialize it from the snapshot
	(possibly) created by a previous call to PrivateData::SnapshotWrite().

	Note that a Listener which does not change any state of their PrivateData
	during calls to Message() does not need to write anything out when called
	for SnapshotWrite(). However, the Listener will still be called at this
	method and will need to construct and return a new instance of their
	PrivateData().
	@param targetRef UIDRef to object the Listener is associated with
	@param inStream Pointer to IPMStream input stream positioned at the snapshot data (if any) previously written in a call to PrivateData::SnapshotWrite()
	*/
	virtual PrivateData* SnapshotRead(const UIDRef& targetRef,
										IPMStream* inStream) = 0;

	/**
	PrivateData is the key to harnessing the full power of the Model to Model
	Messaging because it allows the Listener to store away the pre-change state
	of implementations that is is listening to and defer action until after the
	original top level command which started the 'transaction' is complete at
	which time in a call to Validate() it can compare the current state of the
	implementations to the saved pre-change state and determine what really
	changed.

	When the call to Validate() occurs it is free to react to this change by
	firing commands and thus starting another round of 'transactions'.

	Although created by the Listener (see MessageHelper::AddPrivateData()), the
	lifetime of it is controlled by M2MMessageManager and it will be deleted
	at will by it without any guarantee of a call to Validate().

	Thus the PrivateData must be snapshot if it is changed in any way during
	calls to Message(). Because of this, it is recommended that implementations
	only store the minimum data, typically pre-change state, and leave the
	determination of what to do until the call to Validate().

	Note that the PrivateData does not need to do any sort of call to PreDirty()
	because the M2MMessageManager, which controls the process, will always be 
	dirtied by any message, duplicate or not.

	Implementations which wish to use PrivateData are strongly encouraged to
	consider using the baseclass CM2MMessageListener as it will simplify their
	code and further allow a single Listener to manage sub-listeners.
	*/
	class PUBLIC_DECL PrivateData
	{
	public:
		/**
		Destructor for PrivateData. It is not guaranteed that the PrivateData
		will be validated OR aborted before it is destructed. Further, the
		context of destruction is not always in a valid context for the callee
		to access other parts of the document.
		
		As a result the callee must not do anything other then free its own
		internal resources without causing any side effects to the document.
		*/
		virtual	~PrivateData();

		/**
		The PrivateData is called to snapshot changes that have been made to
		the PrivateData since it was constructed. Implementation which do not
		change themselves during calls to Message() are free to do nothing
		during this call.
		@param stream Pointer to IPMStream input/output stream
		*/
		virtual void	SnapshotReadWrite(IPMStream* stream) = 0;
	
		/**
		Helper class used for calls to Validate().
		*/
		class PUBLIC_DECL ValidateHelper
		{
		public:
			/**
			Returns the Database of the boss which is the target of the message.
			This is the boss the Listener is listening to.
			@return Pointer to IDataBase
			*/
			virtual IDataBase*		GetDataBase() const = 0;
	
			/**
			Returns the boss which is the target of the message. This is the
			boss the Listener is listening to.
			@return Pointer to IPMUnknown
			*/
			virtual const IPMUnknown* GetTarget() const = 0;
	
			/**
			Returns a reference to the boss which is the target of the message.
			This is the boss the Listener is listening to.
			@return UIDRef
			*/
			virtual UIDRef			GetTargetRef() const = 0;
	
			/**
			Returns the ClassID of the boss which is the target of the message.
			This is the boss the Listener is listening to.
			@return ClassID
			*/
			virtual ClassID			GetTargetClassID() const = 0;
	
			/**
			Resets the internal iterator of ChangeData to the top and returns
			the next message which had been received by the Listener through
			a call to Message().

			Because the Helper will supress messages for bosses which have been
			deleted from the DataBase by the time Validate() is called it is
			possible for there to be NO messages for Listeners which are only
			getting messages from Descendents, for example.

			Note that the order of iteration through the messages bears not
			relation to the order that the messages were actually received in.
			@param data Reference to ChangeData to be filled in with the first message
			@return kTrue if there is First message, kFalse otherwise.
			*/
			virtual bool16			GetFirstChange(ChangeData& data) const = 0;
	
			/**
			Returns the next message which had been received by the Listener
			through a call to Message() and increments the internal iterator.

			Note that the order of iteration through the messages bears not
			relation to the order that the messages were actually received in.
			@param data Reference to ChangeData to be filled in with the next message
			@return kTrue if data was filled in, kFalse if the iteration is at the end
			*/
			virtual bool16			GetNextChange(ChangeData& data) const = 0;
	
			/**
			Send a new message which will appear to other Listeners as
			a non-prechange, non-duplicate message (see
			MessageHelper::GetFromPreChange() and GetIsDuplicateChange()).

			Listeners on the target boss which have not yet had their Validate()
			methods called will receive this message. Likewise if this
			message/target boss combination has not been seen during this
			'transaction' new instances of Listeners will be created in the
			same way as messages originating from calls to
			PMPersist::PreDirty() will be.

			The one caveat is that any messages, including those which originate
			in calls to PMPersist::PreDirty(), which would normally result in
			a call to the Listener currently in a call to Validate() will NOT
			result in a new instance of the current Listener. Thus the Listener
			is responsible for understanding the full effects of their changes
			as they won't be told about this. This policy break feedback loops.
			@param targetBoss Pointer to the boss which will be considered the target of the message
			@param origTargetBoss Pointer to the boss which will be considered the original target of the message. May be nil if originalRelation is kTarget. If originalRelation is not kTarget then must not be nil and not equal to targetBoss.
			@param originalRelation The Relation value which describes the relationship between the targetBoss and the origTargetBoss.
			@param idd PMIID of the message
			*/
			virtual void			Message(const IPMUnknown* targetBoss,
											const IPMUnknown* origTargetBoss,
											Relation originalRelation,
											PMIID iid) = 0;
	
		protected:
			///
			ValidateHelper();
			///
			~ValidateHelper();
	
		private:
			///
			ValidateHelper(const ValidateHelper& other);
			///
			ValidateHelper& operator=(const ValidateHelper& other);
	
		};
	
		/**
		Post-notification to Listeners which have registered private data.
		@param helper Reference to ValidateHelper class.
		*/
		virtual void	Validate(ValidateHelper& helper) = 0;

		/**
		This method will be called when the transaction the PrivateData is part
		of will not be completed. The calling context is either at the end of
		the undo processing where the rollback has already occured OR it can be
		before it is happened as a result of the M2MMessageManager seeing that
		the global error state has been set. Further, it is possible that the
		callee may have already been called in Validate().

		Most implementations need not worry about doing anything in this method
		unless they are trying to sychronize between external state.

		Consider the case where a implementation in its constructor sends a
		standard ModelChange() message to some external listener to mute some
		activity related to the changing model state. At the call to Validate()
		it then sends a lazy broadcast message to both unmute the activity and
		provide information describing the change that occured.

		If the Validate() is never called because the transaction is rolled back
		the PrivateData needs to ensure that it still sends an unmute message.
		Likewise if the validation of some other PrivateData causes the global
		error state to be set then we know that the transaction WILL be rolled
		back and the scheduled lazy broadcast will NOT be set and the external
		state not unmuted.
		@param wasValidated kTrue if Validate() was called on the PrivateData
		*/
		virtual void	Abandon(bool16 wasValidated) = 0;
		
	
	protected:
		///
		PrivateData();

	private:
		///
		PrivateData(const PrivateData&);
		///
		PrivateData& operator=(const PrivateData&);

	};


	/**
	Helper class describing a message
	*/
	class ChangeData
	{
	public:
		/// Default Constructor
		ChangeData() :
			fOriginalTargetRef(),
			fRelation(kTarget),
			fIID(kInvalidInterfaceID)
			{ }

		/**
		Constructor
		@param originalTargetRef UIDRef of original target boss
		@param r Relation of the original target boss to the boss that the change will be delivered too. See MessageHelper::GetTarget()
		@param iid The PMIID message
		*/
		ChangeData(const UIDRef& originalTargetRef,
					Relation r, PMIID iid) :
			fOriginalTargetRef(originalTargetRef),
			fRelation(r),
			fIID(iid)
			{ }

		const UIDRef&	GetOriginalTargetRef() const
			{ return fOriginalTargetRef; }

		Relation		GetOriginalRelation() const
			{ return fRelation; }

		bool16			GetOriginalWasAncestor() const
			{
			return ((fRelation == kHierAncestor) ||
					(fRelation == kHierParent));
			}

		bool16			GetOriginalWasParent() const
			{ return (fRelation == kHierParent); }

		bool16			GetOriginalWasTarget() const
			{ return (fRelation == kTarget); }

		bool16			GetOriginalWasChild() const
			{ return (fRelation == kHierChild); }

		bool16			GetOriginalWasDescendent() const
			{
			return ((fRelation == kHierDescendent) ||
					(fRelation == kHierChild));
			}

		bool16			GetOriginalWasUnrelated() const
			{ return (fRelation == kUnrelated); }

		PMIID			GetIID() const
			{ return fIID; }

	private:
		UIDRef		fOriginalTargetRef;
		Relation	fRelation;
		PMIID		fIID;
	};

};

#endif	// __IM2MMessageListener__

