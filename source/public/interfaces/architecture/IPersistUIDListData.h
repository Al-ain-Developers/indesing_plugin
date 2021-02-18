//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPersistUIDListData.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPersistUIDListData__
#define __IPersistUIDListData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "PersistUIDList.h"
#include "IPMStream.h"
#include "CommandID.h"

/** Interface for storing list of UID values (as PersistUIDList).
	@ingroup arch_coredata
	@see PersistUIDList
	@see UIDList
*/
class IPersistUIDListData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPERSISTUIDLISTDATA };

	/** Set the list to the incoming value. Set takes ownership of 
		the pointer, and IPersistUIDListData will be responsible
		for deleting it.
		@param array	the new list of UIDs. IPersistUIDListData
						takes ownership of the pointer, and IPersistUIDListData 
						will be responsible	for deleting it.
	*/
	virtual void Set(PersistUIDList* array) = 0;

#ifdef ID_DEPRECATED	//deprecated in CS5; remove in CS6
	/**	Returns a pointer to the list.
		@return A pointer to the list.
	*/
	virtual const PersistUIDList* GetRef() const = 0;
#endif
	/**	Returns a pointer to the list.
		@return A pointer to the list.
	*/
	virtual const PersistUIDList* GetUIDList() const = 0;

	/**	Returns the database the UIDs all belong to.
		@return IDataBase*	the database the UIDs belong to
	*/
	virtual IDataBase* GetDataBase() const = 0;

	/** @return the number of UIDs in the list
	*/
	virtual int32 Length() const = 0 ;

	/**	Returns the UIDRef of the n'th UID in the list.
		@param index	the index number of the item to return
		@return UIDRef of the item
	*/
	virtual const UIDRef GetItemRef(int32 index) const = 0;

	/**	Removes a UID from the list.
		@param at index into the list of the UID to remove.
	*/
	virtual void Remove(int32 at) = 0;

	/**	Appends an item to the list.
		@param t UID to append to the list.
	*/
	virtual void Append(const UID t) = 0;
};

#endif // __IPersistUIDListData__
