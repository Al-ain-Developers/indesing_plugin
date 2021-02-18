//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUIDRefListData.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IUIDRefListData__
#define __IUIDRefListData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "CommandID.h"
#include "K2Iterator.h"
#include "K2Vector.h"

/** Data interface for storing a list of UIDRef objects. Use IUIDRefListData if you have a 
	list of objects that are from different databases. If all the objects in the list are
	going to be from the same database, IUIDListData is more efficient. 
	@ingroup arch_coredata 
	@see IUIDListData
	@see UIDList
	@see UIDRef
*/
class IUIDRefListData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIDREFLISTDATA };
	
	/** Return the n'th object in the list.
		@param index - which object to return (0-based).
		@return UIDRef - a reference to the object. This can be instantiated.
	*/
	virtual UIDRef at(int32 index) const = 0;
	
	/** Return a pointer to the list. The pointer continues to be owned by this object.
		@return K2Vector(<UIDRef> - the list
	*/
	virtual const K2Vector<UIDRef> *GetList() const = 0;

	/** Remove all items from the list.
	*/
	virtual void     	clear() = 0;
	
	/** Insert an item to the list.
		@param pos - where in the list to put the item
		@param newItem - new entry to add.
	*/
	virtual void		insert(K2Vector<UIDRef>::iterator pos, UIDRef newItem) = 0;
	
	/** Insert an items from uidlist to the list.
		@param uidList - stores items.
	*/
	virtual void		insert(const UIDList& itemList) = 0;


	/** Append an item to the end of the list.
		@param newItem - new entry to add
	*/
	virtual void		push_back(UIDRef newItem) = 0;
	
	/** Return the number of items in the list.
		@return int32 - number of items in the list.
	*/
	virtual int32		size() const  = 0;
	
	/** Remove an item from the list.
		@param pos - index of which item to remove
	*/
	virtual void		Remove(int32 pos) = 0;
	
	/** Find an item in the list.
		@param which - looks for a matching item
		@return int32 - index where item was found, or -1 if item not in list
	*/
	virtual int32		Location(UIDRef which) = 0;
	
	/** Return an iterator on the start of the list.
		@return iterator on the start of the list.
	*/
	virtual K2Vector<UIDRef>::iterator               begin() = 0;
	
	/** Return an iterator on the start of the list. 
		@return iterator on the start of the list.
	*/
	virtual K2Vector<UIDRef>::const_iterator         begin() const = 0;
	
	/** Return an iterator on the end of the list. 
		@return iterator on the end of the list.
	*/
	virtual K2Vector<UIDRef>::iterator               end() = 0;

	/** Return an iterator on the end of the list. 
		@return iterator on the end of the list.
	*/
	virtual K2Vector<UIDRef>::const_iterator         end() const = 0;

	/** Return a reverse iterator you can use to start iterating the list. It will start at the 
		end of the list and walk back. 
		@return iterator on the start of the list.
	*/
	virtual K2Vector<UIDRef>::reverse_iterator       rbegin() = 0;

	/** Return a reverse iterator to the "end" of the list. Use this to check the end condition
		on a reverse iteration through the list.
	*/
	virtual K2Vector<UIDRef>::reverse_iterator       rend() = 0;

	virtual void CopyFrom(const IUIDRefListData*  iUIDRefListData) = 0;
};

#endif // __IUIDRefListData__
