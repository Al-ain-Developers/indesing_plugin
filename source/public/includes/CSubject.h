//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CSubject.h $
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
#ifndef __CSUBJECT__
#define __CSUBJECT__

#include "ISubject.h"
#include "HelperInterface.h"
#include "K2SmartPtr.h"
//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IChangeManager;

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------

#pragma export on

/** Base class for implementing ISubject. Usually you can reuse existing implementations
	of ISubject; either @see kCSubjectImpl or @see kCPersistSubjectImpl. If for some reason this
	doesn't work, you should inherit from CSubject instead of directly from ISubject so 
	you get default class behaviors. See ISubject for information about what the methods do.
	@see ISubject
	@see IObserver
	@ingroup arch_db
*/
class PUBLIC_DECL CSubject : public ISubject
{
	public:
		CSubject(IPMUnknown *boss);
		virtual ~CSubject();
		
		virtual IChangeManager* GetChangeManager() const;
		
		virtual bool16 IsAttached(IObserver* observer, 
														 const PMIID& interestedIn,
														 const PMIID& asObserver = IID_IOBSERVER);

		virtual void AttachObserver(IObserver* observer,
																	const PMIID& interestedIn,
																	const PMIID& asObserver = IID_IOBSERVER);
			
		virtual void DetachObserver(IObserver* observer,
									 							  const PMIID& interestedIn,
									 							  const PMIID& asObserver = IID_IOBSERVER);

		virtual void Change(ClassID theChange, const PMIID& interestedIn = IID_IUNKNOWN, void* changedBy = nil);

		virtual void Change(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn = IID_IUNKNOWN, void* changedBy = nil);

		virtual void Mute(bool16 muteOn);
			
		virtual bool16 IsMuted() const;
		

		virtual void AttachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver);
			
		virtual void DetachObserver(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver);

		virtual bool16 IsAttached(AttachmentType attachType, IObserver* observer, const PMIID& interestedIn, const PMIID& asObserver);

		virtual void ModelChange(ClassID theChange, const PMIID& interestedIn, 
									void* changedBy, LazyNotificationData* data);

		virtual void ModelChange(ISubject* originalSubject, ClassID theChange, const PMIID& interestedIn, 
								void* changedBy, LazyNotificationData* data);

		virtual void ModelChange(IDataBase* model, ClassID theChange, const PMIID& interestedIn, 
								void* changedBy, LazyNotificationData* data);


protected:
		bool16 fDetachObserversOnDelete;
		bool16 fMuted;
		const UIDRef fThisRef;
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
