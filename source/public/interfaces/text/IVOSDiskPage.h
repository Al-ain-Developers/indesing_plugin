//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IVOSDiskPage.h $
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
//  
//  This is an interface that manages the virtual-memory-paging scheme
//  used by the text storage system. A large story is stored in a list
//  of IVOSDiskPage s. Each "page" stores a list of VOS_Object s. These
//  VOS_Objects are abstract classes that represent a block of data, like a
//  single run. If enough VOS_Objects are added to a single page, it splits
//  into 2 pages. Currently they don't recombine, but they could/should.
//  Each VOS_Object has a conceptual length called "VirtualLength" that
//  represents the number of characters that the VOS_Object represents. The pages
//  know how much VirtualLength is contained therein allowing for quicker searching.
//  Knowing that, most of the routines are obvious. The odd ones are Get/SetStrand()
//  which is used to connect strands to the first page of data (which may change
//  during delete or split operations)
//  
//========================================================================================

#pragma once
#ifndef __IVOSDiskPage__
#define __IVOSDiskPage__

#include "IPMUnknown.h"
#include "TextID.h"
#include "UIDList.h"

class VOS_Object;
class VOS_SavedData;

/**	The IVOSDiskPage represents a node within a double-linked list of IVOSDiskPage's
	each page contains a list of VOS_Objects. This is the basic data structure used by
	each strand within the ITextModel. Pseudo-iterators called VOS_Cursors are used
	to walk the data.
	NOTE: Normally this objects would NOT be accessed directly.
	@ingroup text_vos
	@see ITextModel
	@see VOS_Object
	@see VOS_Cursor
*/
class IVOSDiskPage : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IVOSDISKPAGE };

		/** What is the strand that owns this page?
			@param strandID is the UID of the strand that uses this disk page. */
		virtual void SetStrand(UID strandID) = 0;

		/** What is the strand that owns this page?
			@return the UID of the strand that uses this disk page. */
		virtual UID GetStrand() const = 0;

		/** What is the IVOSDiskPage that comes after this one?
			@return the UID of the next disk page. */
		virtual UID NextPage() const = 0;

		/** What is the IVOSDiskPage that comes before this one?
			@return the UID of the previous disk page. */
		virtual UID PrevPage() const = 0;

		/** What is the IVOSDiskPage that comes after this one?
			@param page is the UID of the next disk page. */
		virtual void SetNextPage(UID page) = 0;

		/** What is the IVOSDiskPage that comes before this one?
			@param page is the UID of the previous disk page. */
		virtual void SetPrevPage(UID page) = 0;

		/** Add a reference to the object. This object must be contained on this page.
			@param object is the VOS_Object who is being referenced. */
		virtual void AddRefObj(VOS_Object* object) = 0;

		/** Release a reference to the object. This object must be contained on this page.
			@param object is the VOS_Object who used to be referenced. */
		virtual void ReleaseObj(VOS_Object* object) = 0;

		/** Find the VOS_Object that is located at the specified offset on this page. This is
				not an absolute index or position, only an offset (in characters) from the beginning
				of the page.
			@param offset is the number of characters from the beginning of the page. Offset is updated
					to be the offset WITHIN the returned object (the object contains the position, but
					doesn't have to start with it).
			@return an AddRef'd object that contains the offset. */
		virtual VOS_Object* QueryFindObject(int32 *offset) = 0;

		/** Find the offset of a VOS_Object that is located on this page. This is
				not an absolute index or position, only an offset (in characters)
				from the beginning of the page.
			@param object is the object in question.
			@return the offset from the page start of the beginning of the object. */
		virtual int32 LocateObjectStart(const VOS_Object *object) = 0;

		/** Query the first object on the page
			@return an AddRef'd pointer to the first object on the page. */
		virtual VOS_Object* QueryFirstObj() = 0;

		/** Query the last object on the page
			@return an AddRef'd pointer to the last object on the page. */
		virtual VOS_Object* QueryLastObj() = 0;

		/** Query the object that occurs after another one on the page. This routine
			will return nil if the passed in object is NOT on this page or if the object is
			the last object on the page -- it doesn't go to the next page automatically.
			@param object is one object on the page.
			@return an AddRef'd pointer to the next object on the page. */
		virtual VOS_Object* QueryNextObj(VOS_Object *object) = 0;

		/** Query the object that occurs before another one on the page. This routine
			will return nil if the passed in object is NOT on this page or if the object is
			the first object on the page -- it doesn't go to the previous page automatically.
			@param obj is one object on the page.
			@return an AddRef'd pointer to the previous object on the page. */
		virtual VOS_Object* QueryPrevObj(VOS_Object *obj) = 0;

		/** Find the index of a VOS_Object that is located on this page. This is not any kind
			of character position, just the index relative to other VOS_Objects on this page.
			@param object is the object in question.
			@return the index of the object. */
		virtual int32 ObjectIndexOnPage(const VOS_Object *object) = 0;

		/** Insert an object onto the page. May cause the page to split into two.
			@param newOne is the new VOS_Object to add to the page.
			@param before is the object to insert before. Nil means to insert at the
					beginning of the page. An object off the page will fail.
		*/
		virtual void InsertObj(VOS_Object *newOne, VOS_Object *before = nil) = 0;

		/** Append an object onto the page. May cause the page to split into two.
			@param newOne is the new VOS_Object to add to the page.
			@param after is the object to append after. Nil means to add at the
					end of the page. An object off the page will fail.
		*/
		virtual void AppendObj(VOS_Object *newOne, VOS_Object *after = nil) = 0;

		/** Remove an object from the page.
			@param theOne is the new VOS_Object to remove. Will fail if the object is not found.
			@param deleteIt indicates whether to force the object to be destructed.
		*/
		virtual void RemoveObj(VOS_Object *theOne, bool16 deleteIt = kTrue) = 0;

		/** Replace an object onto the page.
			@param replaceMe is the old VOS_Object to remove from the page. This object must
					be on this page.
			@param replaceWith is the new VOS_Object to add to the page.
			@param deleteIt indicates whether to force the old object to be destructed.
		*/
		virtual void ReplaceObj(VOS_Object *replaceMe, VOS_Object *replaceWith, bool16 deleteIt = kTrue) = 0;

		/** Remove the page from the chain of pages. Updates the previous & next pointers of
			all diskpages involved, tells the cache, etc. but doesn't delete the object from the database. */
		virtual void RemovePage() = 0;

		/** Insert a new page into the linked list. Maintains the linked list and the caches.
			@param newPage is a UID of a new VOSDiskpage to add to the structure.
			@param before, if non-nil, specifies that the new page is to be inserted before the location
					of an object on the page. Can cause this page to split. */
		virtual void InsertPage(UID newPage, VOS_Object *before = nil) = 0;

		/** How many characters are represented by this disk page?
			@return the number of character positions represented by this page. */
		virtual int32 TotalLength() = 0;

		/** How many VOS_Objects are on this page?
			@return the number of VOS_Objects on this page. */
		virtual int32 TotalObjects() = 0;

		/** What type of VOS_Objects are being stored on this disk page? Each strand
			only can be made up of one type of VOS_Object in the normal scheme.
			@return the ClassID of the VOS_Objects on this page. */
		virtual ClassID	GetClassOfObjectsInStrand() const = 0;

		/** Used by the VOS_Objects to tell the page that lengths have changed.
			@param delta is the adjustment to the total number of characters on the page. */
		virtual void AdjustLength(int32 delta) = 0;

		/** Used by the VOS_Objects on the page to mark the page Dirty.
			@param markDoc indicates whether to mark the document dirty also. */
		virtual void DirtyPage(Bool16 markDoc = kTrue) = 0;

		/** Shortcut method to remove more than one page at a time.
			@param length is the number of characters to span. If the next diskpage is longer than
					the length left, then length is left with the number of characters on the next
					page and that next page's UID is returned.
			@param pageIDList is the list of the IVOSDiskPage objects that were contained in the range.
			@param pageLenList is a list of lengths, each corresponding to the disk pages in the pageIDList.
			@return the next disk page UID when the range doesn't extend through the end of the story. */
		virtual UID RemoveOneOrMorePages(int32 *length,
										 K2Vector<UID> *pageIDList,
										 K2Vector<int32>  *pageLenList) = 0;
};

#endif
		// __IVOSDiskPage__

