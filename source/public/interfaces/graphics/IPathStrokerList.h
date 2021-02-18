//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStrokerList.h $
//  
//  Owner: Greg St. Pierre
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IInstallablePathStrokerMgr__
#define __IInstallablePathStrokerMgr__

#include "InstStrokeFillID.h"

class IPathStroker;

/**
 Interface defining the list of path strokers available in a document.

 This includes methods for enumeration of existing strokers, querying by 
 sequence and by ClassID/UID, adding or inserting new a stroker, removing a
 stroker, and searching for a stroker by ClassID/UID.

 Note: There are two different flavors of path stroker in InDesign 3.0:
 
 Static path strokers are implemented as services, and are maintained as 
 holdovers from the InDesign 2.0 and prior stroker architecture. They are
 identified using their ClassID only (the UID for these strokers will 
 always be kInvalidUID).

 Custom path strokers are new to InDesign 3.0. They are implemented internally
 using a stock path stroker - kCustomPathStrokerBoss - that defers to an
 instance of IPathStroker identified as a UID. This allows the old model and
 the new model to co-exist. 

 Implementation note: The stroker list stores static path strokers in a 
 reserved section at the front of the list. This can impact the use of insert
 and remove methods. Insert will fail if asked to insert into the static 
 section. Likewise, remove will fail if asked to remove a static stroker.

 @see IPathStroker
 */
class IPathStrokerList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKERLIST };

	/** 
	 Returns count of strokers in the list

	 @return count of strokers in the list
	 */
	virtual uint32 GetStrokerCount() const = 0;

	/**
	 Queries for the n'th stroker in list. If index identifies a valid path
	 stroker, and AddRef'd instance of the stroker is returned. Otherwise, nil
	 is returned.

	 @param index	IN The index of the path stroker to query
	 @return The n'th IPathStroker in the list
	 */
	virtual IPathStroker *QueryNthStroker(uint32 index) const = 0;

	/**
	 Retrieves class and UID for n'th stroker in the list. If index identifies
	 a valid path stroker, the method returns kTrue, and sets the implClass and
	 implUID out parameters to the ClassID and UID, respectively, of the 
	 stroker. Otherwise, kFalse is returned, and the values of implClass and
	 implUID are undefined.

	 @param index		IN The index of the path stroker
	 @param implClass	OUT The ClassID of the stroker if success, else undefined
	 @param implUID		OUT The UID of the stroker if success, else undefined
	 @return kTrue if successful, else kFalse
	 */
	virtual bool16 GetNthStrokerClassAndUID(uint32 index, ClassID &implClass, UID &implUID) const = 0;

	/**
	 Adds a new stroker to the end of the list. The new stroker must be a valid
	 object in the list's database, must be unique in the list, and must be an
	 instance of kCustomPathStrokerBoss. If path stroker is successfully added,
	 returns kTrue, and index out parameter is set to the stroker's index in the
	 list. Otherwise, kFalse is returned, and index is undefined.

	 @param stroker		IN UID of the stroker to add
	 @param index		OUT Index of the path stroker if success, else undefined
	 @return kTrue if successful, else kFalse
	 */
	virtual bool16 AddStroker(UID stroker, uint32 &index) = 0;

	/**
	 Inserts a new stroker in the list at the given index. The new stroker must 
	 be a valid object in the list's database, must be unique in the list, and 
	 must be an instance of kCustomPathStrokerBoss. Index must fall within the
	 custom stroker section of the list or the call will fail. If index is
	 greater than the length of the list, the stroker is implicitly added to the
	 end of the list. 
	 
	 If path stroker is successfully added, returns kTrue. Otherwise, kFalse is 
	 returned.

	 @param stroker		IN UID of the stroker to add
	 @param index		IN Index in the list at which to insert stroker
	 @return kTrue if successful, else kFalse
	 */
	virtual bool16 InsertStroker(UID stroker, uint32 index) = 0;

	/**
	 Removes a stroker from the list. Index must be a valid index in the list
	 and the stroker at index must be custom (static strokers cannot be removed).
	 Returns kTrue if successful. Otherwise kFalse is returned.

	 @param index	IN Index of the path stroker to remove
	 @return kTrue if successful, else kFalse
	 */
	virtual bool16 RemoveNthStroker(uint32 index) = 0;

	/**
	 Finds a stroker in the list based on ClassID and UID. If a stroker is
	 found, the method returns kTrue and the index out parameter is set to its
	 index in the list. Otherwise, kFalse is returned and index is undefined.

	 @param implClass	IN ClassID of stroker to find
	 @param implUID		IN UID of stroker to find
	 @param index		OUT Index of found stroker if successful
	 @return kTrue if stroker is found, else kFalse
	 */
	virtual bool16 FindStroker(ClassID implClass, UID implUID, uint32 &index) const = 0;
};

#endif //!def __IInstallablePathStrokerMgr__
