//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LinkResourceStatePacket.h $
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
//  
//  Description:
//  This class contain information about a link resource used for resource state updates
//  and automatic resolution of a missing resource.
//  
//========================================================================================

#pragma once
#ifndef __LinkResourceStatePacket__
#define __LinkResourceStatePacket__

// ----- Includes -----
#include "AsyncWork.h"

#include "IDataBase.h"
#include "ILinkManager.h"
#include "ILinkResource.h"
#include "IDTime.h"
#include "URI.h"


/**
 InDesign class used to contain information about a link resource
 that is used while updating the state of the resource and/or
 automatically resolveing a missing resource's new location.

 @see ILinkResource
 @see URI
*/
class PUBLIC_DECL LinkResourceStatePacket : public AsyncWorkPacket
{
public:
	/**
	 Default constructor.
	 Constructs a LinkResourceStatePacket object.
	 @param opType	[IN] Type of state update operation performed. 
	 @param bNotify	[IN] Denotes whether the state update should
						 notify if the model is changed in the callback.
	 @param db		[IN] Database that contains the link resource.
	 @param uid		[IN] UID of a link resource.
	 @param uri		[IN] URI of a link resource.
	 @param state	[IN] State of a link resource.
	 @param stamp	[IN] Stamp of the link resource.
	 @param modTime	[IN] Modification time of the link resource.
	 @param size	[IN] Size of the link resource in bytes.
	 */
	LinkResourceStatePacket(ILinkManager::OperationType opType,
							bool bNotify,
							IDataBase* db,
							const UID& uid,
							const URI& uri,
							ILinkResource::ResourceState state,
							const WideString& stamp,
							const IDTime& modTime,
							uint64 size);

	/**
	 Destructor.
	 Destroys the LinkResourceStatePacket object.
	 */
	virtual ~LinkResourceStatePacket();

	/**
	 Equality operator.
	 Test whether this LinkResourceStatePacket is equal to the given LinkResourceStatePacket.
	 @param rhs	[IN] LinkResourceStatePacket to test for equality against this LinkResourceStatePacket.
	 @return True if this LinkResourceStatePacket is equal to the given LinkResourceStatePacket, else false.
	 */
	bool operator==(const LinkResourceStatePacket& rhs) const;

	/**
	 Returns the type type of state update operation performed;
	 asynchronous or synchronous.
	 @return Type of state update operation performed.
	 */
	ILinkManager::OperationType GetOperationType() const { return fOpType; }

	/**
	 Returns whether the state update should notify
	 if the model is changed in the callback.
	 @return True if the state update should notify, else false.
	 */
	bool GetNotify() const { return fbNotify; }

	/**
	 Returns the database that contains the link resource this packet pertains to. \\
	 NOTE: Never access the database from a link resource state processor that is
		   executing on a thread.  Access is OK if the processor is executing in
		   the idle task.
	 @return Database that contains the link resource this packet pertains to.
	 */
	IDataBase* GetDatabase() const { return fDB; }

	/**
	 Returns the UID of the link resource.
	 @return UID of the link resource.
	 */
	UID GetResource() const { return fUID; }

	/**
	 Returns the URI of the link resource.
	 @return URI of the link resource.
	 */
	URI GetURI() const { return fURI; }

	/**
	 Sets the new URI of the link resource.
	 @param uri [IN] New URI of a link resource.
	 */
	void SetURI(const URI& uri);

	/**
	 Determines whether the link resource's URI has changed.
	 @return True if link resource's URI has changed, else false.
	 */
	inline bool URIChanged() { return fURIChanged; }

	/**
	 Returns the state of the link resource.
	 @return State of the link resource.
	 */
	ILinkResource::ResourceState GetState() const { return fState; }

	/**
	 Sets the new state of a link resource.
	 @param state [IN] New state of a link resource.
	 */
	void SetState(ILinkResource::ResourceState state);

	/**
	 Determines whether the link resource's state has changed.
	 @return True if link resource's state has changed, else false.
	 */
	inline bool StateChanged() { return fStateChanged; }

	/**
	 Returns the stamp of the link resource.
	 @return Stamp of the link resource.
	 */
	WideString GetStamp() const { return fStamp; }

	/**
	 Sets the new stamp of the link resource.
	 @param stamp [IN] New stamp of the link resource.
	 */
	void SetStamp(const WideString& stamp);

	/**
	 Determines whether the link resource's stamp has changed.
	 @return True if link resource's stamp has changed, else false.
	 */
	inline bool StampChanged() { return fStampChanged; }

	/**
	 Returns the modification time of the link resource.
	 @return Stamp of the link resource.
	 */
	IDTime GetModTime() const { return fModTime; }

	/**
	 Sets the new modification time of the link resource.
	 @param stamp [IN] New stamp of the link resource.
	 */
	void SetModTime(const IDTime& modTime);

	/**
	 Determines whether the link resource's modification time has changed.
	 @return True if link resource's modification time has changed, else false.
	 */
	inline bool ModTimeChanged() { return fModTimeChanged; }

	/**
	 Returns the byte size of the link resource.
	 @return Byte size of the link resource.
	 */
	uint64 GetSize() const { return fSize; }

	/**
	 Sets the new byte size of the link resource.
	 @param stamp [IN] New byte size of the link resource.
	 */
	void SetSize(uint64 size);

	/**
	 Determines whether the link resource's byte size has changed.
	 @return True if link resource's byte size has changed, else false.
	 */
	inline bool SizeChanged() { return fSizeChanged; }

	/**
	 Determines whether the link resource has changed.
	 @return True if link resource has changed, else false.
	 */
	inline bool LinkResourceChanged() { return (fURIChanged || fStateChanged || fStampChanged || fModTimeChanged || fSizeChanged); }

private:
	// Prevent copy construction and assignment.
	LinkResourceStatePacket(const LinkResourceStatePacket&);
	LinkResourceStatePacket& operator=(const LinkResourceStatePacket&);

	ILinkManager::OperationType		fOpType;
	bool							fbNotify;

	IDataBase*						fDB;
	UID								fUID;
	URI								fURI;
	ILinkResource::ResourceState	fState;
	WideString						fStamp;
	IDTime							fModTime;
	uint64							fSize;

	bool							fURIChanged;
	bool							fStateChanged;
	bool							fStampChanged;
	bool							fModTimeChanged;
	bool							fSizeChanged;
};

#endif	// __LinkResourceStatePacket__
