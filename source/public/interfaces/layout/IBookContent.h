//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookContent.h $
//  
//  Owner: Yeming Liu
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
//  TODO::expand the book content as directories etc.
//  
//========================================================================================

#pragma once
#ifndef __IBOOKCONTENT__
#define __IBOOKCONTENT__

#include "BookID.h"

/**
	This interface is used to access the information about book content. 
	Currently, the book content is individual InDesign documents. 
	We also call book content as chapter.

	@ingroup layout_book
	@see kBookContentBoss 
*/
class IBookContent : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKCONTENT };

		/**	Get the current book.
			@param none
			@return PMString the file name of current book.
		*/
		virtual PMString GetCurrentBook() = 0;

		/**	Set the current book.
			@param book IN the file name of current book that is to be the current book.
		*/
		virtual void SetCurrentBook(const PMString& book) = 0;

		/**	Get the string representation of book content(chapter)'s page range.
			@param none
			@return PMString the string reprsentation fo page range.
		*/
		virtual PMString GetPageRange() = 0;

		/**	Set the page range of the current book.
			@param pageRange IN the string of page range to be set on the book content.
		*/
		virtual void SetPageRange(const PMString& pageRange) = 0;

		/**	Get the first page number of the book content(chapter).
			@param none
			@return int32 the first page number of book content.
		*/
		virtual int32 GetFirstPageNum() = 0;

		/**	Set the first page number of book content(chapter).
			@param pageNum IN the page number to be set
		*/
		virtual void SetFirstPageNum(const int32& pageNum) = 0;

		/**	Returns kTrue if the book content is available, kFalse otherwise.
			@return kTrue if the book content is available, kFalse otherwise.
		*/
		virtual bool16 IsAvailable() = 0;

		/**	Check if chapter is paginated or not.
			@param none
			@return bool16 kTrue means chapter is paginated, otherwise return kFalse.
		*/
		virtual bool16 IsPaginated() = 0;

		/**	Set the flag about if chapter is paginated or not.
			@param paginate IN the flag to be set as to chapter's pagination.
		*/
		virtual void SetPaginated(bool16 paginate) = 0;

		/**	Open the chapter. This API currently is NOT used in InDesign' core code base 
			and it is a no-op. Third party may want to override this if they want to use it.
			@param none
		*/
		virtual void Open() = 0;
		/**	Get the chapter number of the book content(chapter).
			@param none
			@return int32 the chapter number of book content.
		*/
		virtual int32 GetChapterNumber() = 0;
		/**	Set the chapter number of book content(chapter).
			@param chapterNumber IN the chapter number to be set
		*/
		virtual void SetChapterNumber(int32 chapterNumber) = 0;

		/**	Returns kTrue if a file can be obtained for the book content, kFalse otherwise.
			@param file
			@return kTrue if a file can be obtained for the book content, kFalse otherwise.
		*/
		virtual  bool16 GetIDFile(IDFile& file) const = 0;

		/**	Returns the short name of the book content.
			@return the short name of the book content.
		*/
		virtual WideString GetShortName() const = 0;

		/**	Returns the long name of the book content.
			@return the long name of the book content.
		*/
		virtual WideString GetLongName() const = 0;

		/**	Returns the size of the book content.
			@return the size of the book content.
		*/
		virtual uint64 GetSize() const = 0;

		/**	Returns the modification time of the book content.
			@return the modification time of the book content.
		*/
		virtual IDTime GetModTime() const = 0;

		/**	Returns kTrue if the book content is unmodified and available, kFalse otherwise.
			@return kTrue if the book content is unmodified and available, kFalse otherwise.
		*/
		virtual bool16 IsNormal() const = 0;

		/**	Returns kTrue if the book content is missing, kFalse otherwise.
			@return kTrue if the book content is missing, kFalse otherwise. 
		*/
		virtual bool16 IsMissing() const = 0;

		/**	Returns kTrue if the book content is modified, kFalse otherwise.
			@return kTrue if the book content is modified, kFalse otherwise. 
		*/
		virtual bool16 IsModified() const = 0;
};

#endif //__IBOOKCONTENT__
