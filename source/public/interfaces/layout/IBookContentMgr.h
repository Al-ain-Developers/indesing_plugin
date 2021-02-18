//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookContentMgr.h $
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
//========================================================================================

#pragma once
#ifndef __IBOOKCONTENTMGR__
#define __IBOOKCONTENTMGR__

#include "K2Vector.h"
#include "KeyValuePair.h"
#include "BookID.h"

class UIDList;
class IDFile;

typedef K2Vector<KeyValuePair<UID, IDFile> > BookContentUIDFileList;

/** This interface is used to manage individual content items (kBookContentBoss) within a book (kBookBoss).
	@ingroup layout_book
	@see kBookContentBoss
	@see kBookBoss
	@see IBookContent
*/
class IBookContentMgr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKCONTENTMGR };

		/**	Add the contents(chapters) to the end of the book.
			@param list IN UIDList of chapters to be added.
			@return ErrorCode kSuccess means we add all the chapters.
		*/
		virtual ErrorCode   AppendContents(UIDList* list) = 0;
								
		/**	Insert the contents(chapters) to the specified position in the book.
			@param list IN UIDList of chapters to be added.
			@param pos IN the position where we insert the chapters. 
			              By default(-1), we add to the end of the book.
			@return ErrorCode kSuccess means we add all the chapters.
		*/
		virtual ErrorCode   InsertContents(UIDList* list, int32 pos = -1) = 0;								

		/** Remove the contents(chapters) from the book.
			@param list IN UIDList of chapters to be removed from book.
		*/
		virtual void		RemoveContents(UIDList* list) = 0;

		/**	Get the nth content(chapter) of the book.
			@param n IN the index of content, 0-based. 
			@return UID the nth content.
		*/
		virtual UID 	    GetNthContent(int32 n) = 0;

		/** Get the position for the specified content(chapter)
			@param content IN the specified content.
			@return int32 the index of the specified content.
		*/
		virtual int32	    GetContentIndex(UID content) = 0;

		/**	Get the total number of contents(chapters) in the book.
			@param none
			@return int32 the number of contents in the book.
		*/
		virtual int32       GetContentCount() = 0;

		/**	Get the UID of current selected content(chapter) in the book.
			@param none
			@return UID the current selected content in the book.
		*/
		virtual UID		    GetCurrentContent() = 0;

		/**	Set the specified content(chapter) as the current content in the book.
			@param current IN the UID of content to be set as current.
		*/
		virtual void        SetCurrentContent(UID current) = 0;

		/**	Get the index of current selected content(chapter) in the book. 
			@param none
			@return int32 the index of the current content, 0-based.
		*/
		virtual int32		GetCurrentContentIndex() = 0;

		/**	Get the content UID with the specified IDFile. 
			@param whatFile IN the speciied IDFile.
			@param location OUT if content is found, set the position within the book.
			@return UID the content corresponding to the specified IDFile.
		*/
		virtual UID			FindContentByName(const IDFile& whatFile, int32& location) = 0;

		/**	Clear all the contents(chapters) in the book.
			@param none
		*/
		virtual void		Clear() = 0;

		/**	Update the book content's (UID, IDFile) map in the book content manager. 
			@param content IN the UID of the chapter.
			@param docFile IN the corresponding IDFile of the chapter.
		*/
		virtual void		UpdateBookContentFileList(const UID& content, const IDFile& docFile) = 0;
};

#endif //__IBOOKCONTENTMGR__
