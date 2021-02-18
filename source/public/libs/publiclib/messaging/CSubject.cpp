//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/messaging/CSubject.cpp $
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

#ifndef __CSUBJECT__
#include "CSubject.h"
#endif

#ifndef __IOBSERVER__
#include "IObserver.h"
#endif

#ifndef __ICHANGEMANAGER__
#include "IChangeManager.h"
#endif

#ifndef __ISESSION__
#endif
#include "IControllingUnknown.h"

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(CSubject, kCSubjectImpl)

DEFINE_HELPER_METHODS(CSubject)

//----------------------------------------------------------------------------------------
// CSubject constructor 
//----------------------------------------------------------------------------------------

CSubject::CSubject(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fDetachObserversOnDelete(kTrue),
	fMuted(kFalse),
	fThisRef(::GetUIDRef(boss))
	
{
}

//----------------------------------------------------------------------------------------
// CSubject::~CSubject: 
//----------------------------------------------------------------------------------------

CSubject::~CSubject()
{
	// It's possible that the session has already gone away.  If so, then there's no
	// change manager left to remove dependencies from
	if (fDetachObserversOnDelete)
	{
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
		{
			if (fThisRef.GetDataBase() != nil)
				changeManager->RemoveSubject(fThisRef);
			else 
				changeManager->RemoveSubject(this);
		}
	}
}

//----------------------------------------------------------------------------------------
// CSubject::GetChangeManager: 
//----------------------------------------------------------------------------------------

IChangeManager* CSubject::GetChangeManager() const
{
	ISession* session = GetExecutionContextSession();
	return session ? session->GetChangeManager() : nil;
}

//----------------------------------------------------------------------------------------
// CSubject::IsAttached: 
//----------------------------------------------------------------------------------------

bool16 CSubject::IsAttached(IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	IChangeManager* changeManager = this->GetChangeManager();
	if (changeManager)
	{
		return changeManager->HasDependency(this, observer, asObserver, interestedIn, false);
	}
	else
		return kFalse;
}

//----------------------------------------------------------------------------------------
// CSubject::IsAttached: 
//----------------------------------------------------------------------------------------

bool16 CSubject::IsAttached(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	IChangeManager* changeManager = this->GetChangeManager();
	if (changeManager)
	{
#ifdef DEBUG
		ASSERT(asObserver != IID_IUNKNOWN);
		InterfacePtr<IControllingUnknown>boss(observer, IID_IUNKNOWN);
		PMIID observerIID = boss->GetInterfaceID(observer);
		ASSERT_MSG(observerIID == IID_IUNKNOWN || asObserver == observerIID, "Incorrect Observer IID passed in.");
#endif
		switch (attachType)
		{
		case kRegularAttachment:
				return changeManager->HasDependency(this, observer, asObserver, interestedIn, false);
		case kLazyAttachment:
				return changeManager->HasDependency(this, observer, asObserver, interestedIn, true);
		case kBothAttachments:
				return changeManager->HasDependency(this, observer, asObserver, interestedIn, true) 
						&&
						changeManager->HasDependency(this, observer, asObserver, interestedIn, false);
		default:
			ASSERT_FAIL("Unrecognized attachment type");
			return kFalse;
		}
	}
	else
		return kFalse;
}

//----------------------------------------------------------------------------------------
// CSubject::AttachObserver: 
//----------------------------------------------------------------------------------------

void CSubject::AttachObserver(IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	//____________________________________________________________________________________
	//	This is a fix to restore faster performance for the benchmarking tests for 
	//	Cobalt alpha (InDesign CS3). Attaching with IID_IUNKNOWN is no longer supported.
	//	-Michael Martz
	//____________________________________________________________________________________
	if (interestedIn == IID_IUNKNOWN)
		{
		ASSERT_FAIL ("InDesign no longer supports attaching observers to subjects with the IID_IUNKNOWN protocol. You should attach with the specific protocol you wish to observe.");
		return;
		}
		
	IChangeManager* changeManager = this->GetChangeManager();
	ASSERT_MSG(changeManager != nil, "The change manager doesn't exist!?");
	ASSERT_MSG(observer != nil, "Skipping adding a dependency to a nil observer!?");
	if (changeManager && observer)
	{
		observer->SetAttachIID(asObserver);
		changeManager->AddDependency(this, observer, asObserver, interestedIn, false);
	}
}

//----------------------------------------------------------------------------------------
// CSubject::DetachObserver: 
//----------------------------------------------------------------------------------------

void CSubject::DetachObserver(IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	IChangeManager* changeManager = this->GetChangeManager();
	if (changeManager)
		changeManager->RemoveDependency(this, observer, asObserver, interestedIn, false);
}

//----------------------------------------------------------------------------------------
// CSubject::AttachObserver: 
//----------------------------------------------------------------------------------------

void CSubject::AttachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	IChangeManager* changeManager = this->GetChangeManager();
	ASSERT_MSG(changeManager != nil, "The change manager doesn't exist!?");
	ASSERT_MSG(observer != nil, "Skipping adding a dependency to a nil observer!?");
	if (changeManager && observer)
	{
#ifdef DEBUG
		ASSERT(asObserver != IID_IUNKNOWN);
		InterfacePtr<IControllingUnknown>boss(observer, IID_IUNKNOWN);
		PMIID observerIID = boss->GetInterfaceID(observer);
		ASSERT_MSG(observerIID == IID_IUNKNOWN || asObserver == observerIID, "Incorrect Observer IID passed in.");
#endif
		observer->SetAttachIID(asObserver);
		switch (attachType)
		{
		case kRegularAttachment:
			changeManager->AddDependency(this, observer, asObserver, interestedIn, false);
			break;
		case kLazyAttachment:
			changeManager->AddDependency(this, observer, asObserver, interestedIn, true);
			break;
		case kBothAttachments:
			changeManager->AddDependency(this, observer, asObserver, interestedIn, false);
			changeManager->AddDependency(this, observer, asObserver, interestedIn, true);
			break;
		}
	}
}

//----------------------------------------------------------------------------------------
// CSubject::DetachObserver: 
//----------------------------------------------------------------------------------------

void CSubject::DetachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver)
{
	IChangeManager* changeManager = this->GetChangeManager();
	if (changeManager)
	{
#ifdef DEBUG
		ASSERT(asObserver != IID_IUNKNOWN);
		InterfacePtr<IControllingUnknown>boss(observer, IID_IUNKNOWN);
		PMIID observerIID = boss->GetInterfaceID(observer);
		ASSERT_MSG(observerIID == IID_IUNKNOWN || asObserver == observerIID, "Incorrect Observer IID passed in.");
#endif
		switch (attachType)
		{
		case kRegularAttachment:
			changeManager->RemoveDependency(this, observer, asObserver, interestedIn, false);
			break;
		case kLazyAttachment:
			changeManager->RemoveDependency(this, observer, asObserver, interestedIn, true);
			break;
		case kBothAttachments:
			changeManager->RemoveDependency(this, observer, asObserver, interestedIn, false);
			changeManager->RemoveDependency(this, observer, asObserver, interestedIn, true);
			break;
		}
	}
}

//----------------------------------------------------------------------------------------
// CSubject::Change: 
//----------------------------------------------------------------------------------------

void CSubject::Change(ClassID theChange, const PMIID& interestedIn, void* changedBy)
{
	if (!fMuted)
	{
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
			changeManager->SubjectChanged(this, theChange, interestedIn, changedBy);
	}
}

//----------------------------------------------------------------------------------------
// CSubject::Change: 
//----------------------------------------------------------------------------------------

void CSubject::Change(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn, void* changedBy)
{
	if (!fMuted)
	{
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
			changeManager->SubjectChanged(originalSubject, this, theChange, interestedIn, changedBy);
	}
}

void CSubject::ModelChange(ClassID theChange, const PMIID& interestedIn, 
							void* changedBy, LazyNotificationData* data)
{
	if (!fMuted)
	{
		IDataBase* db = ::GetDataBase(this);
		ASSERT_MSG (db, "Using lazy notifications requires a valid subject database");
		if (!db) return;
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
			changeManager->SubjectModelChanged(this, db, theChange, interestedIn, changedBy, data);
	}
	else if (data)
	{
		delete data;
	}
}

void CSubject::ModelChange(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn, 
							void* changedBy, LazyNotificationData* data)
{
	if (!fMuted)
	{
		IDataBase* db = ::GetDataBase(this);
		ASSERT_MSG (db, "Using lazy notifications requires a valid subject database");
		if (!db) return;
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
			changeManager->SubjectModelChanged(originalSubject, this, db, theChange, interestedIn, changedBy, data);
	}
	else if (data)
	{
		delete data;
	}
}

void CSubject::ModelChange(IDataBase* model, ClassID theChange, const PMIID& interestedIn, 
							void* changedBy, LazyNotificationData* data)
{
	if (!fMuted)
	{
		ASSERT_MSG (model, "Using lazy notifications requires a valid subject database");
		if (!model) return;
		IChangeManager* changeManager = this->GetChangeManager();
		if (changeManager)
			changeManager->SubjectModelChanged(this, model, theChange, interestedIn, changedBy, data);
	}
	else if (data)
	{
		delete data;
	}
}
//----------------------------------------------------------------------------------------
// CSubject::Mute: 
//----------------------------------------------------------------------------------------

void CSubject::Mute(bool16 muteOn)
{
	fMuted = muteOn;
}

//----------------------------------------------------------------------------------------
// CSubject::IsMuted: 
//----------------------------------------------------------------------------------------

bool16 CSubject::IsMuted() const
{
	return fMuted;
}
