//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CM2MMessageListener.h $
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

#ifndef __CM2MMessageListener__
#define __CM2MMessageListener__

#include "IM2MMessageListener.h"
#include "IClassInfo.h"
#include "IObjectModel.h"
#include "IPMStream.h"


#pragma export on

/**
The CM2MMessageListener is an attempt to simplifiy the management of
PrivateData for Listeners, especially for those which would like to create
SubListeners which allows a Listener to listen to more than one class and
have a different policy for each.

The CM2MMessageListener enforces that important requirement that there can
only be ONE SubListener per class. If you find yourselves needing to have
two SubListeners for the same class, even if they are looking at different
messages, you cannot do it - you will have create entirely separate Listeners.

Here's what you do:

	class SubListener1 : public CM2MMessageListener::myPrivateData
	{
		public:
			//
			// This constructor called from our static CreatFor() method.
			//
			SubListener1(IM2MMessageListener::MessageHelper& helper) :
				fVarSetInMessage(-1),
				fVarSetInValidate(kFalse)
				{
				}

			//
			// This constructor called from CM2MMessageListener::SnapshotRead()
			//
			SubListener1(IPMStream* inStream) :
				fVarSetInValidate(kFalse)
				{
				SnapshotReadWrite(inStream);
				}

			//
			// The CM2MMessageListener::myPrivateData requires us to
			// implement this method. We just use our common Snapshot method.
			//
			void		SubListenerSnapshotReadWrite(IPMStream* s)
				{
				SnapshotReadWrite(s);
				}

			//
			// The CM2MMessageListener::myPrivateData requires us to implement
			// this method. We will only be called for messages that we asked
			// for.
			//
			void		Message(IM2MMessageListener::MessageHelper& helper)
				{
				if ((fVarSetInMessage == -1) &&
					(helper.GetChange().GetIID() == IID_ISTORYLIST))
				{
					//
					// The StoryList might be changing the number of stories.
					// Get the current count before it changes.
					//
					ASSERT(helper.GetFromPreChange());
					ASSERT(helper.GetChange().GetOriginalWasTarget());
					InterfacePtr<const IStoryList> sl(helper.GetTarget(), UseDefaultIID());
					fVarSetInMessage = sl->GetAllTextModelCount();
				}
				}

			//
			// The CM2MMessageListener::myPrivateData requires us to implement
			// this method. We will only be called for messages that we asked
			// for.
			//
			void		Validate(IM2MMessageListener::ValidateHelper& helper)
				{
				IM2MMessageListener::ChangeData	change;

				//
				// This could fail if we signed up for and got messages from a
				// boss other than the Target, typicall as a Descenent, which
				// was subsequently deleted before being called here.
				//
				// In this example we do not get messages from Descendents.
				//
				bool16 success = helper.GetFirstChange(change);
				ASSERT(success);

				do
				{
					if (change.GetIID() == IID_ISTORYLIST)
					{
						ASSERT(fVarSetInMessage != -1);
						InterfacePtr<const IStoryList> sl(helper.GetTarget(), UseDefaultIID());
						int32 newCount = sl->GetAllTextModelCount();

						if (newCount != fVarSetInMessage)
						{
							//
							// The total number of TextModels in the document
							// have changed. Let's remember that.
							//
							fVarSetInValidate = kTrue;
						}
					}
				}
				while (helper.GetNextChange(changeData);

				// Anything interesting change?
				if (fVarSetInValidate)
				{
					// Yes! Broadcast something, fire command, whatever...
				}
				}

			//
			// These four static methods are what the CM2MMessageListener needs.
			//
			static bool16	GetCanHandle(const IClassInfo* cInfo)
				{
				//
				// The IStoryList is on the kDocBoss it is quicker to match
				// against this rather than searching for the interface.
				//
				if (cInfo->GetClass() != kDocBoss)
					return kFalse;

				ASSERT(cInfo->GetImplementation(IID_ISTORYLIST) != kInvalidImpl);
				return kTrue;
				}

			static void		GetMessages(const PMIID*& targetM,
										uint32& targetMSize,
										const PMIID*& ancestorM,
										uint32& ancestorMSize,
										const PMIID*& descendentM,
										uint32& descendentMSize,
										const PMIID*& unrelatedM,
										uint32& unrelatedMSize)
				{
				//
				// We are only interested in changes/messages that originate
				// from bosses which have the StoryList - which is the doc.
				//
				targetM = fTargetMList;
				targetMSize = fTargetMListSize;
				}

			static myPrivateData*	CreateFor(IM2MMessageListener::MessageHelper& helper)
				{
				//
				// We would not be called unless GetCanHandle() returned kTrue.
				//
				// Note that you do NOT have to return anything from here.
				//
				return new SubListener1(helper);
				}

			static myPrivateData*	SnapshotRead(const UIDRef& targetRef,
												IPMStream* inStream)
				{ return new SubListener1(targetRef, inStream); }

		private:
			//
			// Static information about the PMIID messages we are interested
			// in. In this case we are only interested in changes that
			// originated on the class we are interested in.
			//
			static PMIID	fTargetMList[];
			static uint32	fTargetMListSize;

			//
			// This variable is set in Message() so we have to snapshot it. In
			// this example it contains the number of TextModels in the doc.
			//
			int32	fVarSetInMessage;

			//
			// This variable is set in Validate() so we don't snapshot it.
			//
			bool16	fVarSetInValidate;

			//
			//
			void	SnapshotReadWrite(const UIDRef& targetRef, IPMStream* s)
				{
				s->XferInt32(fVarSetInMessage);
				ASSERT(!fVarSetInValidate);	// must match constructor
				}

	}

	const PMIID  SubListener1::kTargetMList[] = { IID_ISTORYLIST };
	const uint32 SubListener1::kTargetMListSize = (sizeof(kTargetMList) / sizeof(kTargetMList[0]));

	class SubListener2 : public CM2MMessageListener::myPrivateData
	{
		//
		// Another SubListener like the one above...
		//

	};

	class YourListener : public CM2MMessageListener
	{
		public:
			YourListener(IPMUnknown* boss) :
				CM2MMessageListener(boss)
				{ }

			int32				GetSubListenerCount() const
				{ return 2; }

			funcGetCanHandle	GetNthSubListenerGetCanHandle(int32 n) const
				{
				if (n == 0)
					return SubListener1::GetCanHandle;
				else
					return SubListener2::GetCanHandle;
				}

			funcGetMessages		GetNthSubListenerGetMessages(int32 n) const
				{
				if (n == 0)
					return SubListener1::GetMessages;
				else
					return SubListener2::GetMessages;
				}

			funcCreateFor		GetNthSubListenerCreateFor(int32 n) const
				{
				if (n == 0)
					return SubListener1::CreateFor;
				else
					return SubListener2::CreateFor;
				}

			funcSnapshotRead	GetNthSubListenerSnapshotRead(int32 n) const
				{
				if (n == 0)
					return SubListener1::SnapshotRead;
				else
					return SubListener2::SnapshotRead;
				}
	};

*/
class PUBLIC_DECL CM2MMessageListener : public CPMUnknown<IM2MMessageListener>
{
public:
	/**
	Note: This ideally would be protected but it makes it a little harder for
	creating the SubListeners.
	*/
	class myPrivateData : public PrivateData
	{
		static const int32	kPreCheckValue  = 101363;
		static const int32	kPostCheckValue = 101364;

	public:
		/**
		Validate() must be implemented by the overriding class.
		*/
		
		/**
		Just a forward of IM2MMessageListener::Message() to the PrivateData.
		Overriding classes must implement.
		*/
		virtual void	Message(IM2MMessageListener::MessageHelper& helper) = 0;

		/**
		The SubListener should snapshot. If you don't have any data that ever
		changes between construction and the call to Validate() then you do not
		have to do anything.
		Overriding classes must implement.
		@param outStream Pointer to IPMStream
		*/
		virtual void	SubListenerSnapshotReadWrite(IPMStream* stream) = 0;

		/**
		@see IM2MMessageListener::PrivateData::SnapshotReadWrite().
		We override this so we can remember which SubListener wrote the
		snapshot data so on read we can figure out who to call.
		*/
		virtual void	SnapshotReadWrite(IPMStream* stream)
		{
			// This helps catch override errors. See SnapshotRead() below.
			int32	pre_checkValue = kPreCheckValue;
			stream->XferInt32(pre_checkValue);

			ASSERT_MSG((stream->IsWriting()) ||
					   (pre_checkValue == kPreCheckValue), "CM2MMessageListener::SnapshotReadWrite() - a sub-listener has overriden CM2MMessageListener::myPrivateData::SnapshotReadWrite(). Implement only CM2MMessageListener::myPrivateData::SubListenerSnapshotReadWrite()");

			// Write out the index of the SubListener who created the data.
			stream->XferInt32(fSubListenerIndex);
			ASSERT(fSubListenerIndex >= 0);

			//
			// Let the SubListener snapshot. If they don't have any data
			// that ever changes between construction and the call to
			// Validate() then they don't have to do anything.
			//
   			SubListenerSnapshotReadWrite(stream);

			// This helps catch unfinished read errors. See
			// SnapshotRead() below.
			int32	post_checkValue = kPostCheckValue;
			stream->XferInt32(post_checkValue);

			ASSERT_MSG((stream->IsWriting()) ||
					   (post_checkValue == kPostCheckValue), "CM2MMessageListener::SnapshotReadWrite() - a sub-listener has a sub-listener has not read all that it had previously written");

		}

		/**
		Most clients will not need to worry about this issue so we stub it. See
		IM2MMessageListener::PrivateData::Abandon() for more information.
		*/
		virtual void	Abandon(bool16)
			{ }

		/**
		This is used to figure out which SubListener to call to SnapshotRead().
		@param n Index of the SubListener who created the myPrivateData.
		*/
		void		SetSubListenerIndex(int32 n)
			{ fSubListenerIndex = n; }

	private:
		int32		fSubListenerIndex;

	};

protected:
	/**
	Returns the number of SubListeners implemented the overriding class.
	Overriding classes must implement.
	@return Number of SubListeners available. Must be at least one.
	*/
	virtual int32	GetSubListenerCount() const = 0;

	/**
	Typedef for function which returns kTrue if the SubListener can handle the
	specified class.
	@param cInfo Pointer to IClassInfo for the class to be handled.
	@return kTrue if the SubListener can handle the class.
	*/
	typedef bool16 (*funcGetCanHandle)(const IClassInfo* cInfo);

	/**
	Returns a function pointer to the nTh SubListeners GetCanHandle() function.
	Overriding classes must implement.
	@param n Index of SubListener
	@return Pointer to GetCanHandle() function
	*/
	virtual funcGetCanHandle GetNthSubListenerGetCanHandle(int32 n) const = 0;

	/**
	Typedef for function that which returns static pointers to the messages
	which the SubListener supports.
	@param targetM
	@param targetMSize
	@param ancestorM
	@param ancestorMSize
	@param descendentM
	@param descendentMSize
	@param unrelatedM
	@param unrelatedMSize
	*/
	typedef void (*funcGetMessages)(const PMIID*& targetM, uint32& targetMSize,
							const PMIID*& ancestorM, uint32& ancestorMSize,
							const PMIID*& descendentM, uint32& descendentMSize,
							const PMIID*& unrelatedM, uint32& unrelatedMSize);

	/**
	Returns a function pointer to the nTh SubListeners GetMessages() function.
	Overriding classes must implement.
	@param n Index of SubListener
	@return Pointer to GetMessages() function
	*/
	virtual funcGetMessages	GetNthSubListenerGetMessages(int32 n) const = 0;

	/**
	Typedef for function which creates an instance of myPrivateData for the
	object specified by the helper. The callee is free to examine the info in
	the helper and decide if it wants to create or not, however, typical
	implementations will just do it.
	@param helper Reference to helper for the class to be handled.
	@return Pointer to new instances of myPrivateData.
	*/
	typedef myPrivateData* (*funcCreateFor)(IM2MMessageListener::MessageHelper& helper) ;

	/**
	Returns a function pointer to the nTh SubListeners CreateFor() function.
	Overriding classes must implement.
	@param n Index of SubListener
	@return Pointer to CreateFor() function
	*/
	virtual funcCreateFor	GetNthSubListenerCreateFor(int32 n) const = 0;

	/**
	Typedef for function which will be called to snapshot read and return a
	return a new constructed myPrivateData and initialize from the specified
	stream. Callee must return an instance even it did not write anything into
	the snapshot.
	@param targetRef UIDRef to target boss
	@param inStream Point to IPMStream
	@return Pointer to new instance of myPrivateData.
	*/
	typedef myPrivateData* (*funcSnapshotRead)(const UIDRef& targetRef,
												IPMStream* inStream);

	/**
	Returns a function pointer to the nTh SubListeners SnapshotRead() function.
	Overriding classes must implement.
	@param n Index of SubListener
	@return Pointer to SnapshotRead() function
	*/
	virtual funcSnapshotRead GetNthSubListenerSnapshotRead(int32 n) const = 0;

	/**
	We provide implementations for all the IM2MMessageListener methods.
	*/
	
	/**
	Constructor.
	@param boss Pointer to IPMUnknown
	*/
	CM2MMessageListener(IPMUnknown* boss);

	/**
	@see IM2MMessageListener::GetMessagesFor().
	*/
	virtual void		GetMessagesFor(const IClassInfo* cInfo,
									const PMIID*& targetM,
									uint32& targetMSize,
									const PMIID*& ancestorM,
									uint32& ancestorMSize,
									const PMIID*& descendentM,
									uint32& descendentMSize,
									const PMIID*& unrelatedM,
									uint32& unrelatedMSize) const
		{
		ASSERT((targetM == nil) && (targetMSize == 0));
		ASSERT((ancestorM == nil) && (ancestorMSize == 0));
		ASSERT((descendentM == nil) && (descendentMSize == 0));
		ASSERT((unrelatedM == nil) && (unrelatedMSize == 0));

		const int32 slCount = GetSubListenerCount();

		for (int32 n = 0; n < slCount; n++)
		{
			//
			// If GetCanHandle() function returns a match then we get the
			// messages from the SubListener. First match wins.
			//
			if ((*GetNthSubListenerGetCanHandle(n))(cInfo))
			{
				(*GetNthSubListenerGetMessages(n))(targetM, targetMSize,
												ancestorM, ancestorMSize,
												descendentM, descendentMSize,
												unrelatedM, unrelatedMSize);
				break;
			}
		}
		}

	/**
	@see IM2MMessageListener::Message().
	*/
	virtual void		Message(MessageHelper& helper, PrivateData* data)
		{
		myPrivateData*	myData = (myPrivateData*)data;

		if (myData == nil)
		{
			//
			// No private data defined. Try to create some. Extract an
			// IClassInfo from the helper.
			//
			InterfacePtr<const IControllingUnknown> cu(helper.GetTarget(), UseDefaultIID());
			InterfacePtr<const IObjectModel> om(GetExecutionContextSession(), UseDefaultIID());
			InterfacePtr<const IClassInfo> cInfo(om->QueryClassInfo(cu->GetClass()));
			const int32 slCount = GetSubListenerCount();

			for (int32 n = 0; n < slCount; n++)
			{
				//
				// If there is only one sub-listener, or the GetCanHandle()
				// function returns a match then we let the SubListener create
				// some private data. First match wins.
				//
				if ((slCount == 1) ||
					((*GetNthSubListenerGetCanHandle(n))(cInfo)))
				{
					//
					// This SubListener get a chance to create. If it fails to
					// do so we purposely DO NOT let another SubListener try.
					//
					// Because your Listener will ONLY be called with messages
					// that it intested in the only reason to not create the
					// private data might be some state of the object - but
					// this is rare case.
					// 
					myData = (*GetNthSubListenerCreateFor(n))(helper);
					if (myData)
					{
						myData->SetSubListenerIndex(n);
						helper.AddPrivateData(myData);
					}
					break;
				}
			}
					
		}

		if (myData)
		{
			myData->Message(helper);
		}
		}

	/**
	@see IM2MMessageListener::SnapshotRead().
	It is important that derived classes NOT overrides this method or
	myPrivateData::SnapshotWrite() or else the mechanism to identify which
	SubListener created the myPrivateData will be lost. 
	*/
	virtual PrivateData*	SnapshotRead(const UIDRef& targetRef,
											IPMStream* inStream)
		{
		int32	pre_checkValue, post_checkValue, n;

		// Did someone override SnapshotWrite() but not this? Hard to check
		// the reverse case.
		inStream->XferInt32(pre_checkValue);
		ASSERT_MSG((pre_checkValue == 101363), "CM2MMessageListener::SnapshotRead() - a sub-listener has overriden CM2MMessageListener::myPrivateData::SnapshotReadWrite(). Implement only CM2MMessageListener::myPrivateData::SubListenerSnapshotReadWrite()");

		// Get the SubListener index.
		inStream->XferInt32(n);
		ASSERT((n >= 0) && (n < GetSubListenerCount()));

		// Call the SubListener's SnapshotRead() method.
		myPrivateData*	myData = (*GetNthSubListenerSnapshotRead(n))(targetRef, inStream);
		myData->SetSubListenerIndex(n);

		// Make sure everything which was expected to be
		// read was read.
		inStream->XferInt32(post_checkValue);
		ASSERT_MSG((post_checkValue == 101364), "CM2MMessageListener::SnapshotRead() - a sub-listener has not read all that it had previously written");

		return myData;
		}


};

#pragma export on

#endif	// __CM2MMessageListener__

