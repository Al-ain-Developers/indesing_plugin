//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SelectionObserver.h $
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
//========================================================================================

#pragma once
#ifndef __SELECTION_OBSERVER__
#define __SELECTION_OBSERVER__

#include "CObserver.h"

class ISelectionManager;
class ISelectionMessage;
class IControlView;

/**	Active Selection Observer observes the active context so that it is always 
	observing the active selection (ASB) via the IID_SELECTION_MESSAGE protocol.
*/
class WIDGET_DECL ActiveSelectionObserver : public CObserver
{
public:
	ActiveSelectionObserver(IPMUnknown *boss, PMIID observerIID = IID_IOBSERVER);
	virtual ~ActiveSelectionObserver();

	/**
	Called when this observer should attach to the subject(s) that it  
	observes (Active Context and Active Abstract Selection).

	NOTE:		Subclasses should override AttachToSelectionSubject() to attach to the
	the active selection using their own protocol(s).
	Subclasses which override this method should call the inherited method
	prior to attaching to their own specific protocols. 
	*/
	virtual void 	AutoAttach();

	/**
	DESCR:		Called when this observer should automatically detach from the subject(s) 
	that it observes.

	NOTE:		Subclasses should override DetachFromSelectionSubject() to detach from the
	the active selection using their own protocol(s).
	Subclasses which override this method should call the inherited method 
	after detaching from their own specific protocols.
	*/
	virtual void 	AutoDetach();

	/**
	DESCR:		Handle updates to the observer.  When the active abstract selection boss
	changes, detach from the old and attach to the new. Other
	broadcasts (i.e. those from the selection boss) are passed to 
	HandleSelectionUpdate().

	NOTE:		Subclasses should override HandleSelectionUpdate() rather than this method.
	@param c ClassID
	@param p PMIID
	@param v void star
	*/
	virtual void	Update(const ClassID& c, ISubject*, const PMIID& p, void* v);

protected:
	//........................................................................................
	//	Methods to be overridden by most subclasses
	//........................................................................................
	/**
	DESCR:		Everything relating to the selection should update.

	Either 	(a) there is a new active selection
	or 		(b) the items in the selection has changed

	If ISelectionMessage* is nil, everything should update.
	@param m the selection message
	*/
	virtual void	HandleSelectionChanged(const ISelectionMessage* /*m*/) {}

	/**
	DESCR:		This is a frequent update of the selection. Currently only used by text
	to catch every cursor move.
	*/
	virtual void	HandleFrequentSelectionChanged() {}

	/**
	DESCR:		Some aspect of one or more items in the selection has changed. Only those
	clients whose observed suiteIID was affected by the selection message 
	should update. The suite may have also sent some suite specific broadcast
	data.
	@param m the selection message
	*/
	virtual void	HandleSelectionAttributeChanged(const ISelectionMessage* /*m*/) {}

protected:
	//........................................................................................
	//	Methods to be overridden by some subclasses
	//........................................................................................
	/**
	DESCR:		Attach this observer to the active selection using protocol 
	IID_SELECTION_MESSAGE.
	@param selectionSubject the Subject
	*/
	virtual void	AttachToSelectionSubject(ISubject* selectionSubject);

	/**
	DESCR:		Detach this observer from the active selection using protocol 
	IID_SELECTION_MESSAGE.
	@param selectionSubject the Subject
	*/
	virtual void	DetachFromSelectionSubject(ISubject* selectionSubject);

	/**
	DESCR:		The active selection has changed.
	Calls HandleSelectionChanged() which is overridden by subclasses.
	*/
	virtual void	HandleActiveSelectionChanged();

	/**
	DESCR:		Called when the observer receives a broadcast other than those from the
	active context. i.e. a message from the active selection boss itself,
	which a subclass attached to using a protocol of its choice. All of
	the broadcast information is passed through.

				Processes IID_SELECTION_MESSAGE messages, calling HandleSelectionChanged(),
	HandleFrequentSelectionChanged() or HandleSelectionAttributeChanged() as
	appropriate.

	NOTE:		Subclasses should override this member function only if they attach to 
	additional protocols. If overridden, the subclass should call the inherited 
	method prior to handling the message. Do NOT override Update w/o a very good reason.
	@param c the Class
	@param s the Subject
	@param p PMIID
	@param v void star
	*/
	virtual void 	HandleSelectionUpdate(const ClassID& c, ISubject* s, const PMIID& p, void* v);

	/**
	DESCR:		Query the abstract selection that this observer is attached to for an
	interface (or suite).

	NOTE:		The caller is responsible for calling Release() on the returned interface.
	@param p PMIID
	@return IPMUnknown
	*/
	virtual IPMUnknown*	QueryAbstractSelection(const PMIID& p);

	/**
	DESCR:		Attach this observer to the active selection.
	Obtains the ISubject of the active selection and passes it 
	to AttachToSelectionSubject() which is overridden by subclasses.
	*/
	virtual void	AttachToActiveSelection();

	/**
	DESCR:		Detach this observer from the current selection.
	Obtains the ISubject of the active selection and passes it 
	to DetachFromSelectionSubject() which is overridden by subclasses.
	*/
	virtual void	DetachFromActiveSelection();

protected:
	PMIID 				 	fObserverIID;
	ISelectionManager*		fCurrentSelection;
};

/** Selection Highlight Observer observes a single selection object, specifed by each 
	subclass. The QueryControlView() pure virtual is overridden by a subclass to 
	indicate which view's selection to observe.
*/
class WIDGET_DECL SelectionHighlightObserver : public CObserver
{
public:
	SelectionHighlightObserver(IPMUnknown *boss, PMIID observerIID = IID_IOBSERVER);

	/**
	DESCR:		Called when this observer should attach to the subject(s) that it  
	observes (the selection owned by the view returned by QueryControlView()).

	NOTE:		Subclasses should override AttachToSelectionSubject() to attach to additional
	protocol(s).
	Subclasses which override this method should call the inherited method
	prior to attaching to their own specific protocols. 
	*/
	virtual void 	AutoAttach(); 

	/**
	DESCR:		Called when this observer should automatically detach from the subject(s) 
	that it observes.

	NOTE:		Subclasses should override DetachFromSelectionSubject() to detach from the
	the active selection using their own protocol(s).
	Subclasses which override this method should call the inherited method 
	after detaching from their own specific protocols.
	*/
	virtual void 	AutoDetach();

	/**
	DESCR:		Handle updates to the observer.  When the active abstract selection boss
	changes, detach from the old and attach to the new. Other
	broadcasts (i.e. those from the selection boss) are passed to 
	HandleSelectionUpdate().

	NOTE:		Subclasses should override this method to 
	process IID_SELECTION_HIGHLIGHT_MESSAGE messages.
	@param c the Class
	@param s the Subject
	@param p PMIID
	@param v void star
	*/
	virtual void 	Update(const ClassID& c, ISubject* s, const PMIID& p, void* v);

protected:
	/**
	DESCR:		Attach this observer to the active selection using protocol 
	IID_SELECTION_HIGHLIGHT_MESSAGE.
	@param selectionSubject the Subject
	*/
	virtual void	AttachToSelectionSubject(ISubject* selectionSubject);

	/**
	DESCR:		Detach this observer from the active selection using protocol 
	IID_SELECTION_HIGHLIGHT_MESSAGE.
	@param selectionSubject the Subject
	*/
	virtual void	DetachFromSelectionSubject(ISubject* selectionSubject);

	/**
	DESCR:		Query the abstract selection that this observer is attached to for an
	interface (or suite).

	NOTE:		The caller is responsible for calling Release() on the returned interface.
	@param p PMIID
	@return IPMUnknown
	*/
	IPMUnknown*	QueryAbstractSelection(const PMIID& p);

	virtual IControlView*	QueryControlView() = 0;		

protected:
	PMIID 				 	fObserverIID;
	ISelectionManager*		fCurrentSelection;
};

#endif // __SELECTION_OBSERVER__
