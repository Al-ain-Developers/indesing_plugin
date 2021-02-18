//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IInvalHandler.h $
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
//  
//  Reviewed:	10/06/98
//  
//========================================================================================

#pragma once
#ifndef __IInvalHandler__
#define __IInvalHandler__

#include "IPMUnknown.h"
#include "CommandID.h"

/** An inval cookie is an object that is called at undo and redo. It is created by an 
	inval handler (see IInvalHandler) and called when an undoable transaction on a
	database is undone or redone.

	@see IInvalHandler
*/ 
class IInvalCookie
{
public:
	/** virtual destructor
		Inval cookies are destructed by the database when 
		they are no longer referenced by the change history.
	*/
	virtual ~IInvalCookie() {};

	/**	This function is called by the database to merge two inval cookies
	    when the former decides the two cookies will be part of the same undoable
		step.
		Provide an implementation of this function that merges the @param(other) cookie into
		'this' cookie.
		@param other 
	 */
	virtual void Merge(const IInvalCookie* other) = 0;

	/**	Provide an implementation of this function that performs
	    changes that will occurr before undo.
	 */
	virtual void InvalBeforeUndo() = 0;

	/**	Provide an implementation of this function that performs
	    changes that will occurr after undo.
	 */
	virtual void InvalAfterUndo() = 0;

	/**	Provide an implementation of this function that performs
	    changes that will occurr before redo.
	 */
	virtual void InvalBeforeRedo() = 0;

	/**	Provide an implementation of this function that performs
	    changes that will occurr after redo.
	 */
	virtual void InvalAfterRedo() = 0;
};

/** An inval handler is responsible for monitoring changes to a particular 'topic'
	in the database during an undoable database transaction
	and scheduling changes (invals) to the topic of interest to occur at undo and redo time.

	Inval handlers are used to force updates (invals) at undo and redo that cannot be forced
	by restoring the state of interfaces (via snapshotting). Also inval handlers should be used
	where ever invals cannot be delayed at undo and redo (and therefore lazy notifications 
	cannot help).

	For example, consider an observer that attaches to a spread (see kSpreadBoss). When a spread
	is created, the observer gets attached to the new spread. If the creation of the spread is undone
	this observer must be detached before the undo takes place. If the creation of the spread is
	redone the observer must be re-attached after the redo takes place. Inval handlers allow for this.

	In order for an inval handler to get notified from the database regarding undoable transactions 
	it must be attached to the database using DBUtils::AttachInvalHandler which takes an
	inval handler id. DBUtils::DetachInvalHandler detaches the inval handler from the database. 
	DBUtils::GetInvalHandler looks up the first inval handler attached to the database with
	a specific inval handler type id.  

	When an inval handler is attached to a database it can be in one of two states: 
	"collecting invals" or "not collection invals". Its intial state is "not collecting invals".
	When in "not collecting invals", if a change to the topic of interest takes place, 
	in order to switch to "collecting invals", 
	the inval handler must call DBUtils::StartCollectingInvals. This call returns kTrue if 
	there is an ongoing undoable transaction in the database and kFalse otherwise (e.g. we are 
	in the middle of undoing). If this call returns kTrue, the inval handler switches to 
	"collecting invals" otherwise it remains in "not collection invals".  

	While in "collecting invals", the inval handler keeps collecting information about subsequent
	changes to the topic until the undoable transaction ends. At end of transaction, the inval handler
	is notified by the database via its EndCollectingInvals function. At this point the inval handler switches
	back to "not collection invals".

	It must be clear that using this scheme, changes to the inval handler's 
	topic that occur outside of an undoable transaction never get tracked down. Those that occur inside an
	undoable transaction do.

	The next subject of discussion is inval cookies. An inval cookie is an object that 
	implements a set of changes (invals) that occur at undo and redo. At end of collecting of invals, 
	the inval handler must generate a inval cookie that implements the changes that it wants 
	operated at undo and redo. The implementation of EndCollectingInvals is the vehicle
	for constructing the cookie and handing it back to the database.

	The inval cookie generated by the inval handler is kept in the change history of the database. 
	When the transaction is undone or redone, the inval cookie is invoked to perform the changes
	that the inval handler had scheduled to occur at undo and redo when it created the cookie.

	@see DBUtils::AttachInvalHandler
	@see DBUtils::StartCollectingInvals
	@see IInvalCookie
	@see DBUtils::DetachInvalHandler
*/ 
class IInvalHandler
{
public:
	enum { kDefaultIID = IID_IINVALHANDLER };

	/**	Constructor. */
	IInvalHandler(){}

	/**	Virtual destructor. */
	virtual ~IInvalHandler() {};

	/**	Called by the database at end of undoable transaction if the
		the inval handler is currently collecting invals.

		At end of collecting of invals, the inval handler creates an inval cookie that 
		implements the changes required at undo and redo. 
		EndCollectingInvals is the vehicle
		for constructing the cookie and handing it back to the database which stores the cookie
		in its change history.

		THE DATABASE WILL TAKE OWNERSHIP OF THE INVAL COOKIE. Therefore, the inval handler
		should not keep any reference to this inval cookie after returning 
		from this function.

		@return inval cookie instance to be called at undo and redo
	 */
	virtual IInvalCookie* EndCollectingInvals () = 0;

	/**	Returns the ID of the inval handler type.
		Each inval handler type has a unique ID keyed from the plug-in prefix.
		We allow multiple instances of inval handlers with the same ID
		to be attached to a database.
		@return InvalHandlerID 
	 */
	virtual InvalHandlerID GetID() const = 0;

	/**	Invalidate all before undo/redo; called by the database
		at undo and redo of a transaction that took place before
		the inval handler was attached.

		It can happen that the inval handler gets attached by the client 
		after changes to the topic of interest have already been made
		in one or more undoable transactions. Because of this late attachment, 
		no inval cookies were generated for these transactions.
		Never the less, the database gives the inval handler a chance to force invals
		to occur at undo and redo of these transactions (and all other transactions
		that occurred before the attachment of the inval handler). Typically, the inval handler
		has to invalidate "all" because it has no trace of what happened during the 
		undoable transaction.
	 */
	virtual void BeforeRevert_InvalAll() = 0;

	/**	Invalidate all after undo/redo;
		see IInvalHandler::BeforeRevert_InvalAll for further documentation.
	 */
	virtual void AfterRevert_InvalAll() = 0;
};

#endif 	// __IInvalHandler__

