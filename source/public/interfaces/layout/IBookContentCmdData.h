//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookContentCmdData.h $
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
#ifndef __IBOOKCONTENTCMDDATA__
#define __IBOOKCONTENTCMDDATA__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "BookID.h"

class UIDList;

/** Command data interface for those commands relating to document operations within books (kBookBoss).
	@ingroup layout_book
	@see kAddDocToBookCmdBoss 
	@see kMoveDocInBookCmdBoss 
	@see kRemoveDocFromBookCmdBoss 
	@see kConstructContentCmdBoss 
*/
class IBookContentCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKCONTENTCMDDATA };

		/**	Get the book which the contents are targeting to.
			@param none
			@return IDFile& the book which the contents are targeting to.
		*/
		virtual IDFile& GetTargetBook() = 0;

		/**	Set the book which the contents are targeting to.
			@param bookFile IN the target book.
		*/
		virtual void SetTargetBook(const IDFile& bookFile) = 0;

		/**	Get the list of IDFiles related to the contents.
			@param none
			@return K2Vector<IDFile>& the list of IDFiles related to the contents.
		*/
		virtual K2Vector<IDFile>& GetContentFile() = 0;

		/**	Set the list of IDFiles representing the book contents to be operated on.
			@param contentFileList IN the list of contents to be operated on.
		*/
		virtual void SetContentFile(K2Vector<IDFile>& contentFileList) = 0;

		/**	Get the UID list of book contents to be operated on(insert/remove).
			@param none
			@return UIDList* the UID list of book contents.
		*/
		virtual UIDList* GetContentList()= 0;

		/**	Set the UID list of book contents to be operated on(insert/remove).
			@param contentList IN the UID list of book contents.
		*/
		virtual void SetContentList(UIDList* contentList) = 0;

		/**	Get the position where we want to insert the content within the book.
			@param none
			@return int32 the destination.
		*/
		virtual int32 GetDestPosition() = 0;

		/**	Set the position where we want want to insert the content within the book
			@param destPos IN the destination.
		*/
		virtual void SetDestPosition(int32 destPos) = 0;
};


#endif // __IBOOKCONTENTCMDDATA__
