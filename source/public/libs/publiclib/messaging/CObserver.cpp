//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/messaging/CObserver.cpp $
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

#include "VCPublicHeaders.h"

#ifndef __CCOBSERVER__
#include "CObserver.h"
#endif

#ifndef __ICHANGEMANAGER__
#include "IChangeManager.h"
#endif

#ifndef __ISESSION__
#include "ISession.h"
#endif

#include "PersistUtils.h"


//========================================================================================
// CLASS CObserver
//========================================================================================

DEFINE_HELPER_METHODS(CObserver)


//----------------------------------------------------------------------------------------
// CObserver constructor 
//----------------------------------------------------------------------------------------

CObserver::CObserver(IPMUnknown *boss, PMIID interfaceID) :
	HELPER_METHODS_INIT(boss),
	fDetachSubjectsOnDelete(kTrue),
	fAttachIID(interfaceID),
	fThisRef(::GetUIDRef(boss)),
	fEnabled(kTrue)
{
}

//----------------------------------------------------------------------------------------
// CObserver::~CObserver: 
//----------------------------------------------------------------------------------------

CObserver::~CObserver()
{
	if (fDetachSubjectsOnDelete)
	{
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
		{
			if (fThisRef.GetDataBase() != nil)
				changeManager->RemoveObserver(fThisRef, fAttachIID);
			else
				changeManager->RemoveObserver(this, fAttachIID);
		}
	}
}

//----------------------------------------------------------------------------------------
// CObserver::GetChangeManager: 
//----------------------------------------------------------------------------------------

IChangeManager* CObserver::GetChangeManager() const
{
	ISession* session = GetExecutionContextSession();
	return session ? session->GetChangeManager() : nil;
}
			
void CObserver::AutoAttach()
{
	//noop by default
}

void CObserver::AutoDetach() 
{
	//noop by default
}

void CObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* )
{
}


void CObserver::SetAttachIID(PMIID iid)
{
	fAttachIID = iid;
}

PMIID CObserver::GetAttachIID() const
{
	return fAttachIID;
}

void CObserver::SetEnabled(bool16 state)
{
	fEnabled = state;
}


bool16 CObserver::IsEnabled() const
{
	return fEnabled;
}

