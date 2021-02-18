//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UIDList.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __UIDLIST__
#define __UIDLIST__
//#pragma export on
#include "IPMUnknown.h"

#include "K2Vector.h"
#include "UIDRef.h"
#include "PersistUtils.h"
#include "UIDListInternal.h"
#include "index_based_iterator.h"

//   ==================================================================================
//    * * *                         C L A S S    U I D L i s t                  * * * *
//   ==================================================================================
/** Contains a run-time only data-structure for maintaining a list of UIDs.
	@see PersistUIDList
*/
class PUBLIC_DECL UIDList
{
	// Traits
public:
	typedef object_type data_type;
	typedef UIDListInternal::value_type value_type;
	typedef UIDListInternal::size_type size_type;
	typedef UIDListInternal::const_reference const_reference;
	typedef UIDListInternal::reference reference;
	typedef UIDListInternal::difference_type difference_type;
	typedef UIDListInternal::pointer pointer;
	typedef UIDListInternal::const_pointer const_pointer;

private:
	friend class SortedUIDList;
	UIDListInternal * fUIDList;

public:
	// Defines iterators
	// Because of COW optimization these iterators use indexes instead of pointers.
	typedef index_based_iterator<UIDList, UIDList::value_type> iterator;
	typedef index_based_iterator<UIDList, UIDList::value_type const> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Constructors

	/** This ctor sets the fUIDList to NULL but prevents use of
		Append(), etc since fDB in the fUIDList is never set.
	*/
	UIDList();

	/** Constructor
		@param db IN database where contained UIDs exist
	*/
	explicit UIDList(IDataBase *db);

	/** Copy constructor
		@param copy IN UIDList to copy
	*/
	UIDList(const UIDList &copy);

	UIDList(UIDList &&other) noexcept :
		fUIDList(other.fUIDList)
	{
		other.fUIDList = nil;
	}

	/** Constructor
		@param db IN database where contained UIDs exist
		@param singleEntry IN element to add to the list
	*/
	UIDList(IDataBase *db, const UID singleEntry);

	/** Constructor
		@param object IN object (with associated database) to add to the list
	*/
	UIDList(const IPMUnknown *object);

	/** Constructor
		@param ref IN UIDRef to add to the list
	*/
	UIDList(const UIDRef &ref);

	/** The destructor */
	~UIDList();


	/** Assignment operator
		@param other IN UIDList to replace this UIDList with
	*/
	UIDList& operator=(const UIDList& other);

	UIDList& operator=(UIDList&& other) noexcept
	{
		using std::swap;
		swap(*this, other);
		return *this;
	}

	friend inline void swap(UIDList &a, UIDList &b) noexcept
	{
		std::swap(a.fUIDList, b.fUIDList);
	}

	/** Comparison operator
		@param other IN UIDList to compare to
		@return kTrue if the list is the same
	*/
	bool16 operator==(const UIDList& other) const;

	/** Comparison operator
		@param other IN UIDList to compare to
		@return kTrue if the list is not the same
	*/
	bool16 operator!=(const UIDList& other) const;

	/** const iterator begin
		@return first item in the UIDList
	*/
	const_iterator begin() const
	{
		return fUIDList ? const_iterator(*this, 0) : const_iterator();
	}

	/** non-const iterator begin
		@return first item in the UIDList
	*/
	iterator begin()
	{
		// No PreModify() called here (only when dereferencing the iterator)
		return fUIDList ? iterator(*this, 0) : iterator();
	}

	/** const iterator rbegin
		@return last item in the UIDList
	*/
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(this->end());
	}

	/** non-const iterator rbegin
		@return last item in the UIDList
	*/
	reverse_iterator rbegin()
	{
		return reverse_iterator(this->end());
	}

	/** const iterator end
		@return last item in the UIDList
	*/
	const_iterator end() const
	{
		return fUIDList ? const_iterator(*this, fUIDList->Length()) : const_iterator();
	}

	/** non-const iterator end
		@return last item in the UIDList
	*/
	iterator end()
	{
		// No PreModify() called here (only when dereferencing the iterator)
		return fUIDList ? iterator(*this, fUIDList->Length()) : iterator();
	}

	/** const iterator rend
		@return first item in the UIDList
	*/
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->begin());
	}

	/** non-const iterator rend
		@return first item in the UIDList
	*/
	reverse_iterator rend()
	{
		return reverse_iterator(this->begin());
	}

	/** Subscript operator (non-standard)
		@param i IN index of item
		@return ith UID
	*/
	UID operator[](int32 i) const
	{
		//ASSERT(fUIDList && i > -1 && i < fUIDList->fArray.size());
		return (fUIDList && (i > -1)) ? fUIDList->fArray[i] : kInvalidUID;
	}

	// Modifier methods - allocate new fUIDListInternal if the current
	// UIDList is not the sole owner

	/** return ith UID reference
		@param i IN index of item
		@return ith UID reference
	*/
	UID& At(int32 i);

	/** return ith UID
		@param i IN index of item
		@return ith UID
	*/
	UID At(int32 i) const
		{ return (*this)[i]; }

	/** set the minimum size of this UIDList (number of entries)
		@param chunk IN set minimum size for this list
	*/
	void SetChunkSize(int32 chunk);

	/** set the minimum size of this UIDList (number of entries)
		@param newlen IN set minimum size for this list
		@return kTrue
	*/
	bool16 Preallocate(int32 newlen);

	/** Erase all the elements */
	void Clear();

	/** Insert the specified element at the beginning of the list
		@param t IN element to insert
	*/
	void Insert(const UID t);

	/** Insert the specified elements before the specified index
		@param list IN elements to insert
		@param before IN index to insert before
	*/
	void Insert(const UIDList &list, int32 before);

	/** Insert the specified element before the specified index
		@param t IN element to insert
		@param before IN index to insert before
	*/
	void Insert(const UID t, int32 before);

	/** Append the specified element at the end of the list
		@param t IN element to append
	*/
	void Append(const UID t);

	/** Append the specified element after the specified index
		@param t IN element to append
		@param after IN index to insert after
	*/
	void Append(const UID t, int32 after);

	/** Append the specified elements at the end of the list
		@param list IN elements to append
	*/
	void Append(const UIDList& list);

	/** Remove the specified element
		@param at IN element to remove
	*/
	void Remove(int32 at);

	/** Removes the element pointed by the iterator.
		All iterators are invalidated after the call except for the returned one.
		@param i [IN] - iterator that points to the element we want to remove.
		Caller must check that iterator is not equal to end().
		@return iterator that points to the next element after the one removed (or end()).
	*/
	iterator erase(iterator i);

	/** Removes the elements in the range [first, last).
		All iterators are invalidated after the call except for the returned one.
		@param first [IN] - iterator that points to the first element in the range that we want to remove.
		@param last [IN] - iterator that points past the last element in the range that we want to remove (open range).
		Caller must ensure that the range is valid and part of the container.
		@return iterator that points to the next element after the last removed.
	*/
	iterator erase(iterator first, iterator last);

	/** Appends a copy of the specified element to the end of the container.
		All iterators and references are invalidated after the call when a reallocation occurs.
		@param value [IN] - value to be added to the end of the container.
	*/
	void push_back(const_reference value);

	/** Returns the actual number of UIDs in the container.
	*/
	size_type size() const
	{
		return fUIDList ? fUIDList->fArray.size() : 0;
	}

	/** Replace the item at the specified index with the new UID
		@param at IN index to replace
		@param t IN UID to put at the specified index
	*/
	void Replace(int32 at, const UID t);

	/** Return the index of the specified element
		@param t IN UID to look up
		@return index in the UIDList, or -1 if t is not in the list
	*/
	int32 Location(UID t) const
	{
		return fUIDList? fUIDList->Location(t) : - 1;
	}

	/** Return kTrue if the specified item is in the list
		@param t IN UID to look for
		@return kTrue if t is in the list
	*/
	bool16 Contains(UID t) const
	{
		return Location(t) != -1;
	}

	/** Return kTrue if the specified item is not in the list
		@param t IN UID to look for
		@return kTrue if t is not in the list
	*/
	bool16 DoesNotContain(UID t) const
	{
		return Location(t) == -1;
	}

	/** Increment the reference count of the underlying list */
	void AddRef()
	{
		if(fUIDList)
			fUIDList->AddRef();
	}

	/** Decrement the reference count of the underlying list */
	void Release();

	// Fetch
	/** @return the current chunk size - deprecated */
	int32 ChunkSize() const
	{
		return fUIDList? 8 : 0; } //AW_TODO: Possibly deprecate this?

	/** @return the UIDList length */
	int32 Length() const
	{
		return fUIDList? fUIDList->Length() : 0;
	}

	/** @return kTrue if the UIDList length is 0 */
	bool16 IsEmpty() const
	{
		return fUIDList? fUIDList->IsEmpty(): kTrue;
	}

	/** @return the first UID in the UIDList */
	UID First() const;

	/** @return a reference to the first UID in the UIDList */
	UID& First();

	/** @return the last UID in the UIDList */
	UID Last() const;

	/** @return a reference to the last UID in the UIDList */
	UID& Last();

	/** @return the database for this UIDList */
	IDataBase *GetDataBase() const;

	/** Get a UIDRef for a specified element
		@param at IN index into the list
		@return a UIDRef for the specified element
	*/
	UIDRef GetRef(int32 at) const;

	/** Reads or Writes to the stream. The format is first the length of the UIDList written as an int32
		and then the UIDs. Use ReadWriteXferObject if the UIDs are owned by this implementation and use
		ReadWriteXferReference if they are references.
		@param stream IN stream to read/write to/from
	 */
	void	ReadWriteXferObject(IPMStream* stream);

	/** Reads or Writes to the stream. The format is first the length of the UIDList written as an int32
		and then the UIDs. Use ReadWriteXferObject if the UIDs are owned by this implementation and use
		ReadWriteXferReference if they are references.
		@param stream IN stream to read/write to/from
	 */
	void	ReadWriteXferReference(IPMStream* stream);

private:
	// Iterators need access to the private methods.
	friend class index_based_iterator<UIDList, UIDList::value_type>;
	friend class index_based_iterator<UIDList, UIDList::value_type const>;

	/** If the storage is shared (refcount > 1) creates a copy by calling Replicate().
		This method should be called before any non-const operation is about to happen on the container. (Private)
	*/
	void PreModify();

	/** Replicate makes own copy of fUIDList for the UIDList "envelope" (Private)
	*/
	void Replicate();

	enum EXferType { eXferObject, eXferReference };
	/** Read / write the data (Private)
	*/
	void ReadWrite(IPMStream* s, const EXferType xfer);

	/** Accessor used by the iterators (Private) */
	const_reference get_const_ref(difference_type pos) const
	{
		ASSERT(fUIDList);
		return fUIDList->operator[](pos);
	}

	/** Accessor used by the iterators (Private) */
	reference get_ref(difference_type pos)
	{
		// If a copy of the container occurs between two calls to this operator
		// we will be modifying shared data (because of the COW optimization)
		// so we have to call PreModify() every time;
		PreModify();
		return fUIDList->operator[](pos);
	}

#ifdef DEBUG
	/** Checks if the iterator is valid */
	bool IsValidIterator(const_iterator const& it) const
	{
		// Checks if the iterator is from this container (uidlist) and within legal range
		return ((it.get_container() == this) && it.is_valid());
	}
#endif
} ;

//L1 and L2 have items common to both removed from each (and as a side effect, items are sorted and distinct)
PUBLIC_DECL void Disjoin( UIDList& L1, UIDList& L2);

//L1 receives the union of the two and L2 receives the intersection (and as a side effect, items are sorted and distinct)
PUBLIC_DECL void Join( UIDList& L1, UIDList& L2);

//L1 receives L1\L2 and L2 receives the intersection (and as a side effect, items are sorted and distinct)
//That is, after the call to Difference, L1 has members _also_ in L2 removed, and L2 has members _not_ in L1 removed.
PUBLIC_DECL void Difference( UIDList& L1, UIDList& L2);

/*
// Arithmetical operators
inline UIDList::difference_type operator-(const_iterator const& lhs, const_iterator const& rhs)
{
	return lhs.base() - rhs.base();
}

inline UIDList::iterator operator+(UIDList::difference_type offset, iterator const& rhs)
{
	return (rhs + offset);
}

inline UIDList::const_iterator operator+(UIDList::difference_type offset, const_iterator const& rhs)
{
	return (rhs + offset);
}

// Comparison operators
inline bool operator==(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return (lhs.compare(rhs) == 0);
}

inline bool operator!=(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return !(lhs == rhs);
}

inline bool operator<(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return (lhs.compare(rhs) < 0);
}

inline bool operator>(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return rhs < lhs;
}

inline bool operator<=(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return !(rhs < lhs);
}

inline bool operator>=(UIDList::const_iterator const& lhs, UIDList::const_iterator const& rhs)
{
	return !(lhs < rhs);
}
*/
//#pragma export off

#endif // __UIDLIST__
