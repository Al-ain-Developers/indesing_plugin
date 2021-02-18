//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CObserver.h $
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
#ifndef __COBSERVER__
#define __COBSERVER__

#include "IObserver.h"
#include "HelperInterface.h"
#include "ShuksanID.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IChangeManager;

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------

#pragma export on

/** Base class for implementing IObserver. If you are defining a new observer, please inherit
	from CObserver instead of directly from IObserver.

	See IObserver for information about what the methods do.

	@see ISubject
	@see IObserver
	@ingroup arch_db
*/
class PUBLIC_DECL CObserver : public IObserver
{
	public:
		CObserver(IPMUnknown *boss, PMIID interfaceID = IID_IOBSERVER);
		virtual ~CObserver();
		
		IChangeManager* GetChangeManager() const;
			
		virtual void AutoAttach();
			// If the observer knows who to attach itself to, it'll do so with this call
			
		virtual void AutoDetach();
			// If the observer knows who to detach itself from, it'll do so with this call
			
		virtual void SetAttachIID(PMIID iid);
		
		virtual PMIID GetAttachIID() const;
			// Get and set the IID of the interface this observer is attached as.
			
		virtual void SetEnabled(bool16 state);
			// Enable or disable the observer.  A disabled observer will not receive an update for a change.
			
		virtual bool16 IsEnabled() const;
			// Accessor for enabled state

		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

	protected:
		bool16	fDetachSubjectsOnDelete;
		PMIID	fAttachIID;
		const UIDRef fThisRef;
		bool16 fEnabled;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
