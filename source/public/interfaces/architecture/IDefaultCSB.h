//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDefaultCSB.h $
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
//  Note:		This is the primary interface on the default CSB. Before the boss can be used, it 
//  must be initialized. This is done by calling Initialize() on this interface (the 
//  implementations are responsible for initializing any other interfaces which may need
//  this service).
//  
//========================================================================================

#pragma once
	#ifndef _IDefaultCSB_
	#define _IDefaultCSB_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h"
	#include "ISelectionManager.h"

	//.......ID headers..........................................................................
	#include "ShuksanID.h"

	//.......Other headers.......................................................................
	#include "K2Vector.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
//	class IControlView;
	class IDataBase;
	class IWorkspace;
	class ISelectionManager;
//________________________________________________________________________________________________
//	TYPEDEFS
//________________________________________________________________________________________________
	typedef K2Vector<PMIID>	SuiteIIDCollection;
//	enum {kDontNotifySuites = kFalse, kNotifySuites = kTrue};
/**
	Default CSB Interface. On the document and application workspaces
*/
class IDefaultCSB : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IDEFAULT_CSB };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
/**
				Initialize the interface and any other portions of the boss that need to 
						be initialized. Each Abstract Selection Boss will call Startup/Shutdown. 
						An internal connection count is retained so that only the first startup and 
						last Shutdown actually affect the defaults boss (i.e. the workspace)
*/
		virtual void	Startup (void) = 0;

/**
				Symmetrical call to balance Startup. 
*/
		virtual void	Shutdown (void) = 0;

/**
				Return the database which is the persistent store for the defaults 
						accessed by this boss.
		
		@returns	IDataBase*
*/
		virtual IDataBase*		GetDataBase (void) const = 0;

/**
				Return the workspace associated with these defaults.
	
				The caller is responsible for calling Release().
		
		@returns	IWorkspace* or nil
*/
		virtual IWorkspace*		QueryWorkspace (void) = 0;
		
/**
		     Broadcast a message from the CSB to a suite on the ASB.
		     @param x PMIID
		     @param y message
*/
		virtual void		BroadcastToIntegratorSuite (const PMIID& x, void* y) = 0;

/**
				Broadcast any data from the DefaultCSB that has accumulated since the last
					idle task.
		     @param x IdleTimer
*/
		virtual bool16		BroadcastQueuedMessages (IdleTimer* x) const = 0;

/**
				Broadcast an internal message to the Selection Manager that this CSB
					has messages to broadcast to clients.
*/
		virtual void		SelectionHasQueuedMessages (void) const = 0;
	};

#endif // _IDefaultCSB_