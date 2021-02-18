//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRIDXNotifierHandler.h $
//  
//  Owner: Danielle Darling
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
#ifndef __IRIDXNOTIFIERHANDLER__
#define __IRIDXNOTIFIERHANDLER__

#include "IPMUnknown.h"
#include "AppFrameworkID.h"

class IDataBase;
class RIDXSource;

// ===================================================================================
//	class IRIDXNotifierHandler 
// ===================================================================================
/** Handler which is called when the UID is being modified in some way, deleted, or just to query if it is being 
	actively used.  These functions are called by @IRIDXNotifierUtils
*/
class IRIDXNotifierHandler : public IPMUnknown 
{
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_IRIDXNOTIFIERHANDLER};

	/** Type of Notification being sent.  Currently deleting, modifying, and checking if the UID is actively used
	*/
	enum NotificationType {kBeingDeleted, kWillBeModified, kTestActivelyUsed, kSwatchesWillBeConvertedLocalToGlobal};
	/** Type of Notification status.  Will return if the notification was handled, also if the notification is a bool
		question (like IsActivelyUses) it will return a boolean result (kTrueStatus or kFalseStatus)
	*/
	enum NotificationStatus {kHandledStatus, kDidntHandleStatus, kTrueStatus, kFalseStatus};

	/**
	 	Notify: Nofitication sent when a particular UID is being manipulated @IRIDXNotifierHandler
	 	@param type			@NotificationType type of the notification
	 	@param db			The database it is being deleted from
	 	@param targetUID	The uid notification is being sent about
	 	@param source		The information about the source with the link to the UID
	 	@param data			Any data needed by the Notify
	 	@return NotificationStatus	The status of the notification, whether it was handled or not or whether it answers the question or not
	 */
	virtual NotificationStatus Notify(const NotificationType type, IDataBase *db, const UID targetUID, 
						const RIDXSource& source, const IPMUnknown *data) const = 0;

	/**
	 	Notify: Nofitication sent when a list of UID is being manipulated @IRIDXNotifierHandler
	 	@param type			 @NotificationType type of the notification
	 	@param db			 The database it is being deleted from
	 	@param targetUIDList The uid notification is being sent about
	 	@param source		 The information about the source with the link to the list of UIDs
	 	@param data			 Any data needed by the Notify
	 	@return NotificationStatus	The status of the notification, whether it was handled or not or whether it answers the question or not
	 	@precondition The UIDs in the targetUIDList must all referenced by the same source (same source UID and implementation).
	 */
	virtual NotificationStatus Notify(const NotificationType type, IDataBase *db, const UIDList& targetUIDList, 
						const RIDXSource& source, const IPMUnknown *data) const = 0;
	/**
		WantsNotification: returns true if this handler wants to be notified when changes are made to this type of class
	 	@param type				@NotificationType type of the notification
	 	@param classIDOfTarget	the classID of the target
	 	@param data			 	Any data needed by the Notify
	 */
	 virtual bool16 WantsNotification(const NotificationType type, const ClassID classIDOfTarget) const = 0;
	 
	 
	 /**
	 	AlwaysNotifyForNonPersistReferences: return true if the handler wants to be notified wheneve changes are made to this type of class.
	 	The handler wants to return true in this case if there are non-persistent cases which will need notification.
	 	@param type				@NotificationType type of the notification
	 	@param classIDOfTarget	the classID of the target
	 */
	virtual bool16 AlwaysNotifyForNonPersistReferences (const NotificationType type, const ClassID classIDOfTarget) const = 0;

	/**
	 	Notify: Nofitication sent when a list of UID is being manipulated @IRIDXNotifierHandler
	 	@param type			 @NotificationType type of the notification
	 	@param db			 The database it is being deleted from
	 	@param targetUIDList The uid notification is being sent about
	 	@param data			 Any data needed by the Notify
	 	@return NotificationStatus	The status of the notification, whether it was handled or not or whether it answers the question or not
	 */
	virtual NotificationStatus Notify(const NotificationType type, IDataBase *db, const UIDList& targetUIDList, const IPMUnknown *data) const = 0;
};

#endif

