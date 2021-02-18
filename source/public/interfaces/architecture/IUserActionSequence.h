//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUserActionSequence.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

	#pragma once
	#ifndef _IUserActionSequence_
	#define _IUserActionSequence_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h"
	
	//.......ID headers...........................................................................
	#include "AppFrameworkID.h"
//________________________________________________________________________________________________
//	DEFINES
//________________________________________________________________________________________________
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IUserActionSequence : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IUSERACTIONSEQUENCE };
		typedef	WideString								UserActionSequenceName;
		typedef	K2Vector<InterfacePtr<IPMUnknown> >		UserActionList;
		
		typedef enum {
			/**	Specify an invalid user action sequence ID. */
			kInvalidSequenceID = 0,
			/**	Specify a user action set. */
			kSetSequence,
			/**	Specify a user action group. */
			kGroupSequence,
			/**	Specify a user action item. */
			kActionSequence
			} SequenceID;
	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		
		/**	Returns the name of this user action sequence.
			@return the user action sequence name in a WideString.
		*/
		virtual const UserActionSequenceName&	GetName (void) const = 0;
		
		/**	Sets the name of this user action sequence.
			@param newName is the new user action sequence name in a WideString.
		*/
		virtual void							SetName (UserActionSequenceName& newName) = 0;		
		
		/**	Sets the name of this user action sequence.
			@param newName is the new user action sequence name in a PMString.
		*/
		virtual void							SetName (PMString&) = 0;		
		
		/**	Returns the user action sequence ID. This is one of type defined by SequenceID.
			@return the user action sequence ID.
		*/
		virtual IUserActionSequence::SequenceID	GetSequenceID () const = 0;
		
		/**	Sets the user action sequence ID. This is one of type defined by SequenceID.
			@param sequenceID the new user action sequence ID to set.
		*/
		virtual void							SetSequenceID (IUserActionSequence::SequenceID sequenceID) = 0;
		
		/**	Returns a list of its user actions.
			@param actionList is the list of user actions.
		*/
		virtual void							GetActions (UserActionList& actionList) = 0;
		
		/**	Adds a list of user actions at the specified position.
			@param newActionList is the list of user actions.
			@param position is the position at which to add the new actions. If position is -1,
			new actions are appended at the end.
		*/
		virtual void							AddActions (UserActionList& newActionList, int32 position = -1) = 0;

		/**	Adds a user action at the specified position.
			@param iNewAction is new user action to add.
			@param position is the position at which to add the new action. If position is -1,
			new action is appended at the end.
		*/
		virtual void							AddAction (IPMUnknown* iNewAction, int32 at = -1) = 0;

		/**	Removes only the user actions specified by the list. Child actions are not removed.
			@param actionList is list of user actions to remove.
		*/
		virtual void							RemoveActions (UserActionList& actionList) = 0;

		/**	Removes user actions specified by the list and recursively remove all children as well.
			@param actionList is list of user actions to remove.
		*/
		virtual void							RemoveActionsAndChildren (UserActionList& actionList) = 0;
		/**	Removes all user actions.
		*/
		virtual void							RemoveAllActions (void) = 0;	
		
		/**	Set this user action sequence's parent.
			@param iNewParent is the new parent to set.
		*/
		virtual void							SetParent (IUserActionSequence* iNewParent) = 0;

		/**	Returns the specified interface of this user action sequence's parent.
			@param interfaceIID is the requested interface IID.
			@return the requested user action sequence parent interface.
		*/
		virtual IPMUnknown*						QueryParent (const PMIID& interfaceIID = IID_IUNKNOWN) = 0;
		
		/**	Create a clone copy of this user action sequence.
			@param iNewParent is the new parent for the cloned user action sequence. 
			If iNewParent is nil, the parent of the cloned user action is the same as this user action sequence.
		*/
		virtual IUserActionSequence*			Clone (IPMUnknown* iNewParent = nil) = 0;

		/**	Record the specified user action atom.
			@param actionName is the name of the specified action list.
			@param iUserActionAtom is the user action atom to record.
		*/
		virtual void							Record (const WideString& actionName, IPMUnknown* iUserActionAtom) = 0;
	private:
	};

#endif // _IUserActionSequence_