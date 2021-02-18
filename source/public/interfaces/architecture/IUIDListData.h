//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUIDListData.h $
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
#ifndef __IUIDListData__
#define __IUIDListData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "CommandID.h"

/** Interface for storing a list of UID values (UIDList). Use this when all the objects in the 
	list are from the same database. Use IUIDRefListData if objects in the list can be from
	more than one database.
	@ingroup arch_coredata
	@see UIDList
	@see UIDRef
	@see IUIDRefListData
*/
class IUIDListData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIDLISTDATA };

	/** Set the value of the list. This object will acquire ownership of the array, and will delete it.
	@param array - the new value of the list
	*/
	virtual void Set(UIDList* array) = 0;
	
	/** Return the database that the items in the list are in.
	@return IDataBase* - which database the UIDs are in
	*/
	virtual IDataBase *GetDataBase() = 0;
	
	/** Return the n'th item in the list.
	@param index - which item in the list to return (0-based)
	@return UIDRef - the value of the item as an object reference. This can be instantiated.
	*/
	virtual const UIDRef GetItemRef(int32 index) const = 0;
	
	/** Return a pointer to the list. The pointer is still owned by this object, so if you need to 
	make changes you should copy the list. The pointer is nil if the list has never been set.
	There is no need to delete it.
	@return UIDList* - the list
	*/
	virtual const UIDList* GetRef() const = 0;
};

#endif // __IUIDListData__
