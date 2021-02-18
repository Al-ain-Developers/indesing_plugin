//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IVOSCache.h $
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
#ifndef __IVOSCACHE__
#define __IVOSCACHE__

#include "IPMUnknown.h"
#include "VOSCursor.h"
#include "TextID.h"
#include "K2Vector.h"

class IVOSDiskPage;
class UIDList;
class ITextModel;


/**	The IVOSCache interface exists on each strand within a text model. It is used to get an iterator over
	the strand (VOS_Cursor). It has other summary data about the strand.
	@ingroup text_vos
	@see ITextModel
	@see VOS_Object
	@see VOS_Cursor
	@see IVOSDiskPage
*/
class IVOSCache : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IVOSCACHE };

			/** Return a cursor object pointing to the data in the strand at the passed in position.
				@param virtualKey is the character index within the strand that the cursor will point to.
				@return a VOS_Cursor object pointing to the correct position in the strand.
			*/
		virtual VOS_Cursor Locate(int32 virtualKey) = 0;

			/** What is the absolute TextIndex of the first object on the passed in IVOSDiskPage.
				Disk page objects don't have absolute positions themselves, only deltas.
				@param page is the page to ask about.
				@return the TextIndex of the first element on the page. */
		virtual int32 LocatePageStart(IVOSDiskPage * page) = 0;

			/**	Tells this IVOSCache that the page has been split. Called by the disk page to keep the cache in sync.
				@param formerFirst is the page that was split.
				@param newSecond is the new diskpage that was created when formerFirst was split and inserted after it. */
		virtual void PageSplit(IVOSDiskPage *formerFirst, IVOSDiskPage *newSecond) = 0;

			/**	Tells this IVOSCache that the page length has changed. Called by the disk page to keep the cache in sync.
				@param which is the diskpage that has changed length. */
		virtual void LengthAdjusted(IVOSDiskPage *which) = 0;

			/**	Tells this IVOSCache that the page has been removed. Called by the disk page to keep the cache in sync.
				@param which is the diskpage that has been removed. */
		virtual void PageRemoved(IVOSDiskPage *which) = 0;

			/**	Tells this IVOSCache that a new page has been added. Called by the disk page to keep the cache in sync.
				@param newOne is the page that was added.
				@param beforeThis is the diskpage that comes after the new page. */
		virtual void PageInserted(IVOSDiskPage *newOne, IVOSDiskPage *beforeThis) = 0;

			/** Clears all data in the cache, which will be regenerated.
			*/
		virtual void Reset() = 0;

			/** Add all IVOSDiskPage objects used by this strand to the UIDList.
				@param story is the owning story.
				@param list is the UIDList to fill out. */
		virtual void GetAllPageUIDs(ITextModel *story, UIDList *list) = 0;

			/** Get complete IVOS_DiskPage data for a range of text indices.
				@param startPage is the IVOSDiskPage object to begin getting information for.
				@param length is the number of characters to span. If the next diskpage is longer than
						the length left, then length is left with the number of characters on the next
						page and that next page's UID is returned.
				@param pageCount is set to be the number of IVOSDiskPage objects that were processed
						and added to the lists.
				@param pageIDList is the list of the IVOSDiskPage objects that were contained in the range.
				@param pageLenList is a list of lengths, each corresponding to the disk pages in the pageIDList.
				@return the next disk page UID when the range doesn't extend through the end of the story. */
		virtual UID GetPageUIDs( UID startPage,
								int32 *length,
								int32 *pageCount,
								K2Vector<UID> *pageIDList,
								K2Vector<int32>  *pageLenList) = 0;


			/**	Tells this IVOSCache that a bunch of pages were removed.
				@param startPage is the first page that was deleted.
				@param pageCount is the number of removed pages. */
		virtual void PagesRemoved(UID startPage,int32 pageCount) = 0;

#ifdef DEBUG
			/** Checks to see if the internal lists match the actual data. */
		virtual void Validate() const = 0;
#endif
};

#endif		// __IVOSCACHE__

