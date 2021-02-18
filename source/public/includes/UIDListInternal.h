//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UIDListInternal.h $
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
#ifndef __UIDLISTINTERNAL__
#define __UIDLISTINTERNAL__

class IDataBase;
class SortedUIDList;

const int32 kUIDDefaultChunkSize = 8;

/** Class UIDListInternal is for the private use of UIDList. Do not use directly.
	Contains a run-time only data-structure for maintaining a list of UIDs.
*/
class     PUBLIC_DECL   UIDListInternal
{
	friend class SortedUIDList;
	friend class UIDList;
 
#if defined(DEBUG) && defined(MACINTOSH)

	friend void GetUIDListDescriptionHelper(void* uidListInternalArg, char* buffer, uint32 bufferSize);

#endif

private:
		/** Constructor */
		UIDListInternal(IDataBase *db) :fRefCount(1), fArray(), fDB(db)
		{ fArray.reserve(kUIDDefaultChunkSize); }

		/** copy constructor */
		UIDListInternal(const UIDListInternal& copy) :fRefCount(1), fArray(copy.fArray), fDB(copy.fDB)
			{;}
		/** Constructor */
		UIDListInternal(IDataBase *db, const UID singleEntry) : fRefCount(1), fArray(), fDB(db)
			{ fArray.push_back(singleEntry); ;}
		/** Constructor */
		UIDListInternal(const IPMUnknown *obj) : fRefCount(1), fArray(), fDB(::GetDataBase(obj))
			{ fArray.push_back(::GetUID(obj)); ;}
		/** Constructor */
		UIDListInternal(const UIDRef& obj) : fRefCount(1), fArray(), fDB(obj.GetDataBase())
		{ fArray.push_back(obj.GetUID()); ;} 
public:
		/** Increment the reference count of the underlying list */
		void AddRef() { fRefCount++; }

		/** Decrement the reference count of the underlying list */
		void Release();

		/** Destructor */
		~UIDListInternal() 
		{;}

private:
		// Types
		typedef K2Vector<UID> UIDArray;
		typedef UIDArray::value_type value_type;
		typedef UIDArray::size_type size_type;
		typedef UIDArray::const_reference const_reference;
		typedef UIDArray::reference reference;
		typedef UIDArray::difference_type difference_type;
		typedef UIDArray::pointer pointer;
		typedef UIDArray::const_pointer const_pointer;
					
		/** Assignment operator
			@param other IN UIDList to replace this UIDList with
		*/
		UIDListInternal& operator=(const UIDListInternal& other)
			{ fArray = other.fArray;  fDB = other.fDB; return *this; }
		/** Comparison operator
			@param other IN UIDList to compare to 
			@return kTrue if the list is the same
		*/
		bool16 operator==(const UIDListInternal& other) const
			{ return fArray == other.fArray; }
		/** Comparison operator
			@param other IN UIDList to compare to 
			@return kTrue if the list is not the same
		*/
		bool16 operator!=(const UIDListInternal& other) const
			{ return fArray != other.fArray; }
		
		/** Subscript operator (non-standard) 
			@param i IN index of item
			@return ith UID
		*/
		const_reference operator[](int32 i) const
			{ return fArray[i]; }

		/** Subscript operator (non-standard) 
			@param i IN index of item
			@return ith UID
		*/
		reference operator[](int32 i)
			{ return (fArray[i]); }

		/** set the minimum size of this UIDList (number of entries)
			@param chunk IN set minimum size for this list
		*/
		void SetChunkSize(int32 chunk)
			{ fArray.reserve(chunk); }

		/** set the minimum size of this UIDList (number of entries)
			@param newlen IN set minimum size for this list
			@return kTrue
		*/
		bool16 Preallocate(int32 newlen)
			{ fArray.reserve(newlen); return kTrue; }

		/** Erase all the elements */
		void Clear()
			{ fArray.clear(); }

		/** Insert the specified element at the beginning of the list 
			@param t IN element to insert
		*/
		void Insert(const UID t)
			{ fArray.insert(fArray.begin(),t); }

		/** Insert the specified element before the specified index
			@param t IN element to insert
			@param before IN index to insert before
		*/
		void Insert(const UID t, int32 before)
			{ fArray.insert(fArray.begin() + before, t); }

		/** Insert the specified elements before the specified index
			@param list IN elements to insert
			@param before IN index to insert before
		*/
		void Insert(const UIDListInternal& list, int32 before);

		/** Append the specified element at the end of the list
			@param t IN element to append
		*/
		void Append(const UID t)
			{ fArray.push_back(t); }

		/** Append the specified element after the specified index
			@param t IN element to append
			@param after IN index to insert after
		*/
		void Append(const UID t, int32 after)
			{ fArray.insert(fArray.begin() + after + 1, t); }

		/** Append the specified elements at the end of the list
			@param list IN elements to append
		*/
		void Append(const UIDListInternal& list);

		/** Remove the specified element
			@param at IN element to remove
		*/
		void Remove(int32 at)
			{ fArray.erase(fArray.begin() + at); }

		/** Replace the item at the specified index with the new UID
			@param at IN index to replace
			@param t IN UID to put at the specified index	
		*/
		void Replace(int32 at, const UID t)
			{ fArray[at] = t; }
		
		/** @return the current chunk size - deprecated */
		int32 ChunkSize() const
			{ return 8; } //AW_TODO: Possibly deprecate this?

		/** @return the UIDList length */
		int32 Length() const
			{ return fArray.size(); }

		/** @return kTrue if the UIDList length is 0 */
		bool16 IsEmpty() const
			{ return fArray.empty(); }

		/** @return a reference to the first UID in the UIDList */
		const_reference First() const
			{ return fArray.front(); }

		/** @return the first UID in the UIDList */
		reference First()
			{ return fArray.front(); }

		/** @return a reference to the last UID in the UIDList */
		const_reference Last() const
			{ return fArray.back(); }

		/** @return the last UID in the UIDList */
		reference Last()
			{ return fArray.back(); }

		/** Return the index of the specified element
			@param t IN UID to look up
			@return index in the UIDList, or -1 if t is not in the list
		*/
		int32 Location(UID t) const
			{ 
				UIDArray::const_iterator iter = K2find(fArray, t); 
				return (iter != fArray.end() ? iter - fArray.begin() : -1);
			}
			
		/** @return the database for this UIDList */
		IDataBase *GetDataBase()	const { return fDB; }
		
		/** Get a UIDRef for a specified element
			@param at IN index into the list
			@return a UIDRef for the specified element 
		*/
		UIDRef GetRef(int32 at) const
			{ return UIDRef(fDB, fArray[at]); }

		/** @return the reference count of the underlying list */
		int32 GetReferenceCount() { return fRefCount;}

		// Data
		int32 fRefCount;
		UIDArray	fArray;
		IDataBase *fDB;
};	

#if defined(DEBUG) && defined(MACINTOSH)
void PUBLIC_DECL GetUIDListDescriptionHelper(void* uidListInternalArg, char* buffer, uint32 bufferSize);
#endif

#endif // __UIDLISTINTERNAL__
