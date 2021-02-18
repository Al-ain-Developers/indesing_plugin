//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtInvalHandler.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __GTTxtEdtInvalHandler_h__
#define __GTTxtEdtInvalHandler_h__

#include "IInvalHandler.h"
#include <vector>

class IDataBase;

/**
	A cookie that allows us to re-attach or re-detach our story edit observer across story create/delete
	undo/redo events.

	@ingroup gotolasttextedit
*/
class GTTxtEdtInvalCookie : public IInvalCookie
{
public:
	/**
		Constructor
	*/
	GTTxtEdtInvalCookie(const UIDRef& storyUIDRef, bool16 storyCreated);
	/**
		Destructor
	*/
	virtual ~GTTxtEdtInvalCookie();
	/**
		Invalidation before undo. Called before the undo of a sequence that this cookie has an association with.
	*/
	void InvalBeforeUndo();
	/**
		Invalidation after undo. Called after the undo of a sequence that this cookie has an association with.
	*/
	void InvalAfterUndo();
	/**
		Invalidation before redo. Called before the redo of a sequence that this cookie has an association with.
	*/
	void InvalBeforeRedo();
	/**
		Invalidation after redo. Called after the redo of a sequence that this cookie has an association with.
	*/
	void InvalAfterRedo();
	/**
		Called to merge the cookies when multiple cookies generated within the same
		transaction. For example, say there is an abortable command sequence
		(see IAbortableCmdSeq). For each call to CmdUtils::SetSequenceMark within
		the sequence the IInvalHandler::EndCollectingInvals method is called, so 
		a separate cookie can be generated per sequence mark. At the end of the sequence
		these cookies are merged together into one cookie through this method.
		@param other
	*/
	void Merge(const IInvalCookie* other);

	/**
		Add a new cookie crumb to the invalidation.
		@param storyUIDRef IN the uidref of the story affected.
		@param storyCreated IN kTrue if the story was created, kFalse if it was deleted.
	*/
	void AddNewCookieCrumb(const UIDRef& storyUIDRef, bool16 storyCreated);

	/** Returns kTrue if the cookie needs to be called on undo / redo, kFalse otherwise.
	*/
	bool16 IsUndoRequired();

private:

	/** Crumb maintained by this cookie.
	*/
	typedef std::pair<UID,bool16> GTTxtEdtCookieCrumb;

	/** List of crumbs maintained by this cookie.
	*/
	typedef std::vector<GTTxtEdtCookieCrumb> GTTxtEdtCookieCrumbList;

	GTTxtEdtCookieCrumbList fCookieCrumbList;
	IDataBase* fDataBase;
};


/**
	Called when a sequence completes for which this handler is recording invalidations. The inval handler will provide an instance of
	a cookie that is called on undo/redo.

	@see GTTxtEdtInvalCookie
	@ingroup gotolasttextedit
*/
class GTTxtEdtInvalHandler : public IInvalHandler
{
public:

	/**
		Constructor
	*/
	GTTxtEdtInvalHandler() : IInvalHandler(),fInvalCookie(nil),fCollectingInvals(kFalse){};
	/**
		Destructor
	*/
	virtual ~GTTxtEdtInvalHandler() {};

	/** If in "not collecting invals" state, call DBUtils::StartCollectingInvals to see if an undoable transaction
		is in progress, switch to "collecting invals" if so, then record the UIDRef of the story plus
		the action. Otherwise, in "collecting invals" record the UIDRef of the story, and the action.
		@param storyUIDRef IN the uidref of the story affected.
		@param storyCreated IN kTrue if the story was created, kFalse if it was deleted.
	*/
	void AddStoryInvalInfo(const UIDRef& storyUIDRef, bool16 storyCreated);

	/**
		The core indicates that the sequence we have declared an interest in (see the StartCollectingInvals call in the 
		GTTxtEdtNewDeleteStoryObserver) has completed, giving us the opportunity to creare a cookie encapsulating the state
		we require for handling the undo/redo behaviour.
		@return a cookie.
	*/
	IInvalCookie* EndCollectingInvals () ;
	/**
		Return the inval handler ID for this invalidation handler.
		@return the inval handler ID.
	*/
	InvalHandlerID GetID() const;
	/**
		Deals with the need to hard reset the cache (for example, if you only collect invals when a panel is showing,
		you need to use the reset mechanism if the user undos beyond the panel was shown).
	*/
	void BeforeRevert_InvalAll() ;
	/**
		Deals with the need to hard reset the cache (for example, if you only collect invals when a panel is showing,
		you need to use the reset mechanism if the user undos beyond the panel was shown).
	*/
	void AfterRevert_InvalAll() ;

private:
	/**
		The cookie associated with this invalidation.
	*/
	GTTxtEdtInvalCookie* fInvalCookie;
	/**
		kTrue if we are collecting invalidations.
	*/
	bool16 fCollectingInvals;

};


#endif // __GTTxtEdtInvalHandler_h__

// End, GTTxtEdtInvalHandler.h.




