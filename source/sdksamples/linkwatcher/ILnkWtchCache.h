//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/ILnkWtchCache.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ILnkWtchCache_h__
#define __ILnkWtchCache_h__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "UIDList.h"
#include "LnkWtchID.h"


/** Cache that references all links added to the document since it was opened.
	Entries in the cache consist of a UID and a removed flag and are keyed by the 
	UID of the link.

	We must leave entries in the cache for removed links in order to
	distinguish a remove of a link that existed in the document
	when it was opened from a remove of a link that was added to the 
	document. If we erased the cache entry for removed links completely 
	we could not make this distinction. So we set a flag that indicates
	the added link has now been removed.

	An add link operation records a new entry in the cache with the UID of the
	new link and the removed flag is false. Undo of the operation removes the 
	entry from the cache.

	A remove link operation leaves the entry in the cache with its removed flag
	set to true. Undo of the operation simply sets the removed flag to its previous
	state (false).

	@ingroup linkwatcher
*/
class ILnkWtchCache : public IPMUnknown
{
public:
	/** kDefaultIID */
	enum { kDefaultIID = IID_ILNKWTCHCACHE };

	/** An entry in the cache has a UID and a removed flag.
	*/
	typedef struct Entry {
		typedef base_type data_type;
		UID fUID;
		bool16 fRemoved;
		bool16 operator==(const Entry& other) const {  return fUID == other.fUID; }
		Entry(UID uid, bool16 removed) : fUID(uid), fRemoved(removed) {}
	} Entry;
	/** A vector of entries.
	*/
	typedef	K2Vector<Entry> Entries; 

	/**	Returns all entries in the cache.
		@return all entries in the cache. 
	 */
	virtual const Entries& Get() const = 0;

	/**	Returns the name of the link associated with the given cache entry.
		@param entry the cache entry hose name is required
		@param fullName kTrue to include the path, kFalse for the file name only.
		@return the name of the link associated with the given cache entry  
	 */
	virtual const PMString GetName(const Entry& entry, bool16 fullName = 0) const = 0;

	/**	Push an entry to into the cache.
		@param entry 
	 */
	virtual void push_back(const Entry& entry) = 0;

	/**	Return index in cache of the given entry if found, -1 otherwise.
		@param entry 
		@return index in cache of the given entry if found, -1 otherwise. 
	 */
	virtual int32 Location(const Entry& entry) = 0; 

	/**	Set the removed flag for the cache entry at the index given.
		@param pos index in the cache whose removed flag is to be changed.
		@param removed kTrue to set flag , kFalse to clear
	 */
	virtual void MarkRemoved(const int32 pos, bool16 removed) = 0;

	/**	Delete the cache entry at the given index.
		@param pos index of entry to be cleared.
	 */
	virtual void Delete(const int32 pos) = 0; 

	/**	Clear all entries in the cache.
	 */
	virtual void clear() = 0;

	/**	Dump cache entries to trace.
	 */
	virtual void Dump() const = 0;

	/**	Broadcast notification that the cache has changed.
	 */
	virtual void NotifyCacheChanged() = 0;
};

#endif // __ILnkWtchCache_h__
