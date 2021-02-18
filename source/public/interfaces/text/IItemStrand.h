//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IItemStrand.h $
//  
//  Owner: emenning
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
#ifndef __IItemStrand__
#define __IItemStrand__
#include "IPMUnknown.h"
#include "PMTypes.h"
#include "TextID.h"
#include "K2Vector.h"
#include "OwnedItemDataList.h"

class UIDList;
class IOwnedItem;
typedef K2Vector<ClassID>	ClassList;


/**
	Interface to the owned item strand.
	@ingroup text_story
*/
class IItemStrand : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IITEMSTRAND };

		/**
			Insert an owned item at a certain position. If an owned item with the same class
			already exists at this location, replace it.
			@param position IN text index where to reference owned item.
			@param objectType IN class of owned item.
			@param object IN uid of owned item.
		*/
		virtual void SetOwnedUID(TextIndex position, ClassID objectType, UID object) = 0;

		/**
			@return the uid of the owned item with a certain class referenced at a certain position.
			Return kInvalidUID if such an owned item does not exist.

			@param position IN text index of owned item.
			@param objectType IN class of owned item.
			@param count OUT length from position to the end of the range
			where the owned item is referenced.
			@pram runBegin OUT text index of the beginning of the range where the owned item is referenced.
		*/
		virtual UID GetOwnedUID(TextIndex position, ClassID objectType, int32 *count = nil, TextIndex *runBegin = nil) = 0;

		/**
			@return all owned items referenced in a range.
			@param position IN start of range.
			@param length IN length of the range.
			@param uidListToFill OUT list of found owned item uids
			@param classListToFill OUT list of found owned item classes.
		*/
		virtual void GetAllItems(TextIndex position, int32 length, UIDList *uidListToFill, ClassList* classListToFill = nil) = 0;

		/**
			@return the number of owned items referenced at a position.
			@param position IN text index where we should look.
			@param count OUT length from position to the end of the range
			where the owned items are referenced.
			@param runBegin OUT text index of the beginning of the range where the owned items are referenced.
		*/
		virtual int32 CountOwnedItems(TextIndex position, int32 *count = nil, TextIndex *runBegin = nil) = 0;

		/**
			@return the uid of the nth owned item referenced at a certain position.
			@param position IN text index where to look.
			@param n IN rank of the owned item to look for.
			@param objectType OUT class of owned item.
			@param count OUT length from position to the end of the range
			where the owned item is referenced.
			@pram runBegin OUT text index of the beginning of the range where the owned item is referenced.
		*/
		virtual UID GetNthOwnedUID(TextIndex position, int32 n, ClassID *objectType, int32 *count = nil, TextIndex *runBegin = nil) = 0;

		/**
			@return the position where an owned item is referenced.
			@param objectType IN class of owned item.
			@param object IN uid of owned item.
			@param hint IN helps speed up the search if caller has an idea where the owned item may be located.
		*/
		virtual TextIndex GetOwnedItemIndex(ClassID objectType, UID object, TextIndex hint = 0) = 0;

		/**
			@return the position where an owned item is referenced.
			@param ownedItem IN an interface pointer to the owned item.
		*/
		virtual TextIndex GetOwnedItemIndex(const IOwnedItem* ownedItem) const = 0;

		/**
			Collect all owned items in a range.
			@param start IN range start,
			@param len IN range length.
			@param resultList OUT list of the offset in the story, class id, and uid of each
			owned item found.
		*/
		virtual void CollectOwnedItems(TextIndex start, int32 len, OwnedItemDataList* resultList) const = 0;
};

#endif //__IItemStrand__