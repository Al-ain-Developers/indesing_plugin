//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IActiveContext.h $
//  
//  Owner: 
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
#ifndef __IActiveContext__
#define __IActiveContext__

#include "IPMUnknown.h"

#include "K2Vector.h"
#include "KeyValuePair.h"

#include "DocumentID.h"
#include "ShuksanID.h"
#include "widgetid.h"
#include "WorkspaceID.h"

class IDocument;
class ISelectionManager;
class IControlView;
class IWorkspace;
class ISubject;

/**
	An IActiveContext maintains a mapping between IIDs and pointers to implementations.
*/
class IActiveContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IACTIVECONTEXT };

	/**
		Most users will only need these utility methods which provide access to the standard interfaces in an active context.
	*/
	IDocument* GetContextDocument() const { return (IDocument*)GetContextInterface(IID_IDOCUMENT); } ;
	ISelectionManager* GetContextSelection() const { return (ISelectionManager*)GetContextInterface(IID_ISELECTIONMANAGER); } ;
	IControlView* GetContextView() const { return (IControlView*)GetContextInterface(IID_ICONTROLVIEW); } ;
	IWorkspace* GetContextWorkspace() const { return (IWorkspace*)GetContextInterface(IID_IWORKSPACE); } ;

	/**
		Obtain a specific interface from the active context.
		@param id is the PMIID of the desired interface
		@return the interface (NB: not AddRef'ed) or nil if not defined
	*/
	virtual IPMUnknown*	GetContextInterface( const PMIID& id ) const = 0 ; 

		// When the context is changed, observers are notified and the "changedBy" parameter
		// passed to the Observer's Update method is a pointer to a ContextInfo.
		// The PMIID field holds the PMIID of the protocol that was changed.
		// The IPMUnknown* field holds the previous value of the active context for the PMIID.
		// NOTE: Old code casts the "changedBy" parameter to be a pointer to a PMIID and
		// uses the PMIID, so it's important that the first field in this class is the PMIID.
		// All code should be migrated to expecting a pointer to a ContextInfo class,
		// rather than the old (const PMIID*), but both will work for now.
	typedef KeyValuePair<PMIID, IPMUnknown*>  ContextInfo;
	typedef K2Vector<ContextInfo> ContextTable;

	/**
		Obtain all of the currently defined context interfaces.
	*/
	virtual void		GetContextInterfaces( ContextTable& table ) const = 0;
	/**
		Replace the existing context interfaces with a new set. In contrast 
		to ChangeContextInterfaces, this method operates as if the table 
		parameter were padded out with a nil pointer value for every IID not
		explicitly in the table.  That is, no existing unspecified interface 
		values in the context's mapping survive. SetContextInterfaces 
		notifies once for each changed IID.
	*/
	virtual void		SetContextInterfaces( const ContextTable& table ) = 0;
	/**
		Add or replace one or more context interfaces. Existing interfaces that 
		are not in the table are not affected. Notification is done after the entire 
		table is changed for each affected PMIID.
	*/
	virtual void		ChangeContextInterfaces( const ContextTable& table ) = 0;

	/**
		SetContextDelegate(IActiveContext* delegate) in effect calls 
		GetContextInterfaces to get the delegate's mapping and passes that 
		table to SetContextInterfaces causing this context to synchronize 
		its mapping with the delegate's and notifying observers of the change.
		In addition, any subsequent changes to this context get propagated to
		the delegate and any changes made directly to the delegate context 
		are observed and realized in this context so that one may observe 
		this context alone to be notified of changes to either context.
		SetContextDelegate also holds a reference to an externally specified
		delegate.
		Making a context its own delegate (e.g. ac->SetContextDelegate(ac))
		means that the context should revert to the "default" mapping for
		its implementation. (For example, the session boss implementation
		installs the no-pub context consisting only of the app workspace and
		that workspace's associated selection.)
		Passing nil instructs the implementation to remove delegate and tear down
		any active interfaces because the context is shutting down.
	*/
	virtual void SetContextDelegate( IActiveContext* newDelegate ) = 0;
	/**
		Test whether a delegate is the current delegate.
	*/
	virtual bool16 IsContextDelegate( IActiveContext* am_I_your_delegate ) const = 0;
};

#endif
