//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceStateUpdateCmdData.h $
//  
//  Owner: Michael Easter
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
#ifndef __ILinkResourceStateUpdateCmdData__
#define __ILinkResourceStateUpdateCmdData__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

#include "ILinkResource.h"

class IDataBase;
class IDTime;
class URI;
class WideString;


/**
 Data interface used by the LinkResourceStateUpdateCmd which is used to update
 a link resource's URI, stamp and state.
 */
class ILinkResourceStateUpdateCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCESTATEUPDATECMDDATA };
	
	/**
	 Identifiers that denote the type of update action to be performed by
	 the LinkResourceStateUpdateCmd on the link resource with the given UID.
	 */
	enum UpdateAction {
		/** Update the resource's URI. */
		kUpdateURI = 1,
		/** Update the resource's state, stamp, modification time and size. */
		kUpdateState,
		/** Update the resource's stamp, modification time and size. */
		kUpdateStamp,
		/** Update the resource's modification time only. */
		kUpdateModTime,
		/** Update the resource's size only. */
		kUpdateSize
	};

	/**
	 Sets the UpdateAction to be performed by the state update command.
	 @param action [IN] UpdateAction to be performed.
	 */ 
	virtual void SetUpdateAction(UpdateAction action) = 0;

	/**
	 Returns the UpdateAction to be performed by the state update command.
	 @return UpdateAction to be performed.
	 */ 
	virtual UpdateAction GetUpdateAction() const = 0;

	/**
	 Sets the database to be targeted by the state update command.
	 @param db [IN] Database target.
	 */ 
	virtual void SetDatabase(IDataBase* db) = 0;

	/**
	 Returns the database to be targeted by the state update command.
	 @return Database target.
	 */ 
	virtual IDataBase* GetDatabase() const = 0;

	/**
	 Sets the UID of the link resource to update.
	 @param uid [IN] Resource UID.
	 */ 
	virtual void SetResource(const UID& uid) = 0;

	/**
	 Returns the UID of the link resource to update.
	 @return Resource UID.
	 */ 
	virtual const UID& GetResource() const = 0;

	/**
	 Sets the new URI of the resource.
	 @param uri [IN] Resource's new URI.
	 */ 
	virtual void SetURI(const URI& uri) = 0;

	/**
	 Returns the new URI of the resource.
	 @return Resource's new URI.
	 */ 
	virtual const URI& GetURI() const = 0;

	/**
	 Sets the new state of the resource.
	 @param state [IN] Resource's new state.
	 */ 
	virtual void SetState(ILinkResource::ResourceState state) = 0;

	/**
	 Returns the new state of the resource.
	 @return Resource's new state.
	 */ 
	virtual ILinkResource::ResourceState GetState() const = 0;

	/**
	 Sets the new stamp of the resource.
	 @param stamp [IN] Resource's new stamp.
	 */ 
	virtual void SetStamp(const WideString& stamp) = 0;

	/**
	 Returns the new stamp of the resource.
	 @return Resource's new stamp.
	 */ 
	virtual const WideString& GetStamp() const = 0;

	/**
	 Sets the new modification time of the resource.
	 @param modTime [IN] Resource's new modification time.
	 */ 
	virtual void SetModTime(const IDTime& modTime) = 0;

	/**
	 Returns the new modification time of the resource.
	 @return Resource's new modification time.
	 */ 
	virtual const IDTime& GetModTime() const = 0;

	/**
	 Sets the new data size of the resource.
	 @param size [IN] Resource's new data size.
	 */ 
	virtual void SetSize(uint64 size) = 0;

	/**
	 Returns the new data size of the resource.
	 @return Resource's new data size.
	 */ 
	virtual uint64 GetSize() const = 0;

	/**
	 Sets whether links referencing the resource are allowed
	 to be marked modified. \\
	 Normally any changes to the resource that might result in links
	 being out-of-date will cause the links referencing the resource
	 to be marked modified. \\
	 Setting the MarkLinksModified flag to false has the following implications:\\
	 1. Prevents the modification state of any link referencing the
	 resource from being changed. \\
	 2. If a link is not already marked modified and the resource's stamp
	 is different than the the link's import stamp, then the link's import
	 stamp and import modification time will be updated to match the resource's
	 stamp and modification date/time. \\
	 By default, the MarkLinksModified flag is set to true, which allows
	 referencing links to be set as modified. This flag should only be marked
	 false for exceptional/unusual circumstances.
	 @param bMarkLinksModified [IN] Boolean denoting whether the links
									referencing the resource are allowed
									to be marked modified.
	 */ 
	virtual void SetMarkLinksModified(bool bMarkLinksModified) = 0;

	/**
	 Returns whether links referencing the resource are allowed
	 to be marked modified. \\
	 Normally any changes to the resource that might result in links
	 being out-of-date will cause the links referencing the resource
	 to be marked modified. \\
	 Setting the MarkLinksModified flag to false has the following implications:\\
	 1. Prevents the modification state of any link referencing the
	 resource from being changed. \\
	 2. If a link is not already marked modified and the resource's stamp
	 is different than the the link's import stamp, then the link's import
	 stamp and import modification time will be updated to match the resource's
	 stamp and modification date/time. \\
	 By default, the MarkLinksModified flag is set to true, which allows
	 referencing links to be set as modified. This flag should only be marked
	 false for exceptional/unusual circumstances.
	 @return True if links referencing the resource can be marked modified,
			 else false.
	 */ 
	virtual bool GetMarkLinksModified() const = 0;

	/**
	 Sets the document state to dirty if set true
	 @param bDbModified[IN] set to kTrue to make doc dirty
	*/
	virtual void SetDatabaseModified(bool16 bDbModified = kFalse) = 0;

	/**
	 Returns true if the document is to be set to dirty
	 after the command executes
	*/
	virtual bool16 GetDatabaseModified() const = 0;

	/**
	 DEPRECATED - there is no way to prevent notification.
	 Sets whether to notify about the changed resource.
	 @param bNotify [IN] True to notify, else false.
	 */ 
	virtual void SetNotify(bool bNotify) = 0;

	/**
	 DEPRECATED - there is no way to prevent notification.
	 Returns whether to notify about the changed resource.
	 @return True to notify, else false.
	 */ 
	virtual bool GetNotify() const = 0;
};

#endif	// __ILinkResourceStateUpdateCmdData__
