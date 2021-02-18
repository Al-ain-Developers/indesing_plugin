//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VOSSimpleCursor.h $
//  
//  Owner: EricM
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
#ifndef __VOSSIMPLECURSOR__
#define __VOSSIMPLECURSOR__

#include "VOSObject.h"

class IVOSDiskPage;
class VOS_SavedData;

#pragma export on


/** VOS_SimpleCursor is basically an iterator used to iterate over text model strands.
	A VOS_Cursor is returned from IVOSCache::Locate(). The returned object must be deleted.
	The iterator points to an object (VOS_Object) and has an internal offset into that object.
	A particular run of characters could be contained within one VOS_Object and the exact position
	would be specified by the local offset.
	This is not meant to be directly constructed, but only retrieved from the IVOSCache interface of the strand.
	NOTE:  This is not derived from IPMUnknown.
	@ingroup text_vos
	@see ITextModel
	@see IVOSCache
	@see VOS_Object
	@see VOS_Cursor
	@see VOS_SavedData
*/
class PUBLIC_DECL VOS_SimpleCursor
{
	public:
		VOS_SimpleCursor(IPMUnknown* cache);
		VOS_SimpleCursor(IPMUnknown* cache, IVOSDiskPage* block, int32 offset);

		~VOS_SimpleCursor();

		VOS_SimpleCursor(const VOS_SimpleCursor& other);
		VOS_SimpleCursor& operator=(const VOS_SimpleCursor& other);

			/** GetPreviousSimple -- get a new iterator pointing to the object before this one.
			@param prevExists will be true if the iterator wasn't already at the beginning.
			@return a new iterator object.
			*/
		VOS_SimpleCursor GetPreviousSimple(bool16 *prevExists = nil) const;
			/** GetNextSimple -- get a new iterator pointing to the next object.
			@param nextExists is true when the iterator wasn't already at the end.
			@return a new iterator object.
			*/
		VOS_SimpleCursor GetNextSimple(bool16 *nextExists = nil) const;

			/** Move this cursor to the next object.
			@return true when the move to the next object succeeded (not past end).
			*/
		bool16 MoveToNext();
			/** Move this cursor to the previous object.
			@return true when the move to the previous succeeds (not already at beginning).
			*/
		bool16 MoveToPrevious();

			/** AtBeginning check
			@return true if the iterator is pointing at the beginning of the strand
			*/
		bool16 AtBeginning() const;
			/** AtEnd check
			@return true if the iterator is pointing at the end of the strand
			*/
		bool16 AtEnd() const;

			/** Local Offset
			@return the offset into the current object -- not a global position.
			*/
		int32 LocalOffset() const
			{ return fObjOffset; }

			/** Move the internal offset. Doesn't advance to the next object when advanced too far.
				Or to the previous object when negative.
			@param delta specifies the amount to add to the current offset.
			*/
		void IncrementOffset(int32 delta)
			{ fObjOffset += delta; ASSERT_MSG(fObjOffset >= 0, "offset should be positive"); }

			/** Set the internal offset. Doesn't advance to the next object when Set too large;
				or to the previous object when negative.
			@param off specifies the offset into the current object to use.
			*/
		void SetOffset(int32 off)
			{ fObjOffset = off; ASSERT_MSG(fObjOffset >= 0, "offset should be positive"); }

			/** ObjectLength -- how large is the object being pointed to?
			@return the number of characters the current object represents.
			*/
		int32 ObjectLength() const
			{ return (fObject ? fObject->VirtualLength() : 0); }

			/** Mark the object dirty.
			*/
		void DirtyObject()
			{ if (fObject) fObject->PreDirty(); }

			/** Get the underlying object. Should be matched with a call to ReleaseObject().
			@return a pointer to the underlying object.
			*/
		VOS_Object* QueryObject()
			{ if (fObject)
					fObject->AddRef();
			  return fObject;	}

			/** Release the object. Strictly not necessary because this routine just
				calls the Release() on the underlying object, but the thinking was that letting
				the cursor know may allow future caching.
			@param obj is the pointer to the object to release that was retrieved with QueryObject.
			*/
		static void ReleaseObject(VOS_Object *obj)
			{ if (obj) obj->Release(); }

			/** Is the cursor pointing at anything?
			@return true when the iterator isn't pointing at anything.
			*/
		bool16 IsEmpty() const
			{ return fObject == nil; }

			/** Remove the object from the containing data structure.
			@param deleteIt indicates whether to delete the object being removed.
			@return true when the deletion succeeds.
			*/
		bool16 RemoveObject(bool16 deleteIt = kTrue);

			/** Remove all objects from the data structure starting with the current location and
				contained within the passed in length.
			@param pLen2Del specifies the number of character positions to delete. Only entire objects
				are deleted. If the length to delete spans 2 full objects plus half of a third, the parameter
				is set to the number of characters to delete from the 3rd object, and the iterator is left pointing to it.
			@param data points to a data structure to hold the deleted objects.
			*/
		void RemoveObjects(int32 *pLen2Del, VOS_SavedData *data);

			/** Copy all objects from the data structure starting with the current location and
				contained within the passed in length.
			@param pLen2Copy specifies the number of character positions to copy. Only entire objects
				are copied. If the length to copy spans 2 full objects plus half of a third, the parameter
				is set to the number of characters to copy from the 3rd object, and the iterator is left pointing to it.
			@param copyInto points to a data structure to hold the copied objects.
			*/
		void CopyObjects(int32 *pLen2Copy, VOS_SavedData *copyInto = nil);

			/** Rationalize moves the iterator to the beginning of the next object if it
				currently points to the end of an object.
			*/
		void Rationalize();
			/** Remove the link to the pointed to object completely.
			*/
		void Clear();

			/** Return a referenced pointer to the containing data structure boss object.
			@return an interface to the containing boss object. (kVOSDiskPageBoss)
			*/
		IPMUnknown* QueryOwningObject()
			{	if (fOwner)
					fOwner->AddRef();
				return fOwner; }

	protected:
			/** add this object to the VOS_SavedData data structure for undo of delete.
				Only called by RemoveObjects(). Cursor moves forward when nextExists and len2Del > 0.
			@param front specifies whether to add this object to the front or the end of the datastructure undo.
			@param undo is the data structure to add to.
			@param nextExists RETURNS kTrue if this is not the last object.
			@param len2Del is the number of characters to delete after this object.
			*/
		void AddUndoObject(bool16 front, VOS_SavedData *undo, bool16 *nextExists, int32 len2Del);

			/** copy this object to the VOS_SavedData data structure for copy-paste.
				Only called by CopyObjects(). Cursor moves forward when nextExists and len2Copy > 0.
			@param front specifies whether to add this object to the front or the end of the datastructure undo.
			@param copy is the data structure to add to.
			@param nextExists RETURNS kTrue if this is not the last object.
			@param len2Copy is the number of characters to copy after this object.
			*/
		void CopyObject(bool16 front, VOS_SavedData *copy, bool16 *nextExists, int32 len2Copy);

			/** copy the entire VOS_DiskPage of the object pointed to into the VOS_SavedData data structure for copy-paste.
				Only called by CopyObjects().
			@param copy is the data structure to add to.
			@param unused is unused.
			@param len2Copy is the number of characters to copy beyond that page. It is used to possible advance the cursor.
			*/
		void CopyPageRef(VOS_SavedData *copy, bool16 *unused, int32 len2Copy);

		IPMUnknown	*fOwner;
		VOS_Object	*fObject;
		int32		fObjOffset;
};

#pragma export off

#endif		// __VOSSIMPLECURSOR__
