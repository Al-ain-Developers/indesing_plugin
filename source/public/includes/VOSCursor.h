//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VOSCursor.h $
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
#ifndef __VOSCURSOR__
#define __VOSCURSOR__

#include "VOSSimpleCursor.h"

class IVOSCache;
class IVOSDiskPage;

#pragma export on

/** Like VOS_SimpleCursor, VOS_Cursor is basically an iterator used to iterate over text model strands.
	A VOS_Cursor is returned from IVOSCache::Locate(). The returned object must be deleted.
	The iterator points to an object (VOS_Object) and has an internal offset into that object.
	A particular run of characters could be contained within one VOS_Object and the exact position
	would be specified by the local offset.
	A VOS_Cursor allows more editing of the "container" than the VOS_SimpleCursor does.
	This is not meant to be directly constructed, but only retrieved from the IVOSCache interface of the strand.
	NOTE:  This is not derived from IPMUnknown.
	@ingroup text_vos
	@see ITextModel
	@see IVOSCache
	@see VOS_Object
	@see VOS_SimpleCursor
*/
class PUBLIC_DECL VOS_Cursor : public VOS_SimpleCursor
{
	public:
		VOS_Cursor(IVOSCache* cache);
		VOS_Cursor(IVOSCache* cache, IVOSDiskPage* block, int32 offset);
		VOS_Cursor(const VOS_SimpleCursor& cursor);
		~VOS_Cursor();

		/** Get a cursor pointing to the previous object. If there is no previous object,
			the cursor is left in place, but "found" is set to false.
			@param found is kTrue when the new cursor was positioned before this one.
			@return a new VOS_Cursor. */
		VOS_Cursor GetPrevious(bool16 *found = nil) const;

		/** Get a cursor pointing to the next object. If there is no next object,
			the cursor is left in place, but "found" is set to false.
			@param found is kTrue when the new cursor was positioned after this one.
			@return a new VOS_Cursor. */
		VOS_Cursor GetNext(bool16 *found = nil) const;

		/**	Append a new VOS_Object into the data structure after the position that this cursor is pointing to.
			@param object is the new object to place into the container. It is appended after "this".
			@duplicate indicates whether to use the object directly, or make a copy.
		*/
		void AppendAfter(VOS_Object *object, bool16 duplicate = kTrue);

		/**	Append a new VOS_Object into the data structure after the position that this cursor
			is pointing to and also reposition the cursor to point to the new object.
			@param object is the new object to place into the container. It is appended after "this".
			@duplicate indicates whether to use the object directly, or make a copy.
		*/
		void AppendAfterAndMove(VOS_Object *object, bool16 duplicate = kTrue);

		/**	Insert a new VOS_Object into the data structure before the position that this cursor is pointing to.
			@param object is the new object to place into the container. It is inserted before "this".
			@duplicate indicates whether to use the object directly, or make a copy.
		*/
		void InsertBefore(VOS_Object *object, bool16 duplicate = kTrue);

		/**	Replace the VOS_Object pointed to with the new one that is passed in.
			@param object is the new object to place into the container. It replaces the object currently pointed to.
			@duplicate indicates whether to use the object directly, or make a copy.
		*/
		void ReplaceObjectWith(VOS_Object *obj, bool16 duplicate = kTrue);

#ifdef DEBUG
	private:
					/** gCount is a construction count -- incremented when constructed, decremented when destructed.
						can be used to watch the usage patterns with these cursors. */
		// In a multi-threaded environment these stats may not be updated accurately.
		// Atomic add and subtracts of these stats are required in order to have accurate values. 
		// This would put a great overhead on the performance. Hence, we are not using atomic add and
		// subtract expecting that these stats need not be accurate.
		static int32	ts_Count;
#endif

	private:

		/**	This routine is used by the cursor to find the first VOS_DiskPage in the correct strand.
			It is used when InsertBefore is called and the cursor is unset -- this places the new
			object at the beginning of the data.
			@return the UID of the first disk page in the current strand. */
		UID GetFirstPageOfStrand();

};

#pragma export off


#endif		// __VOSCURSOR__
