//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookSyncCmdData.h $
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
#ifndef __IBOOKSYNCCMDDATA__
#define __IBOOKSYNCCMDDATA__

#include "BookID.h"

class UIDList;

/** Command data interface associated with command to synchronize book (kBookBoss).

	@ingroup layout_book
	@see kBookSyncCmdBoss 
*/
class IBookSyncCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKSYNCCMDDATA };

		/**	Set all the synchronization command data.
			@param sysFile IN the book file where the synchronization operation happens.
			@param itemList IN the list of target(file) we copy styles to.
			@param syncAll IN flag indicates if we should sync all the documents in the book or 
			       only the given documents(itemList).
			@param useDefaultOptions IN flag indicates if we use existing setting in the book or 
			       use the setting from current UI input.         
			@param syncOptionsOnly IN flag indicates if we just save the sync options or 
			       do both save the sync options AND copying styles from source document 
				   to target document. 
		*/
		virtual void Set
			(
				IDFile& sysFile, 
				UIDList* itemList, 
				bool16 syncAll = kTrue, 
				bool16 useDefaultOptions = kTrue, 
				bool16 syncOptionsOnly = kTrue
			) = 0;

		/**	Get the book file where the synchronization operation happens.
			@param none
			@return IDFile the book file.
		*/
		virtual IDFile GetBookFile() = 0;

		/**	Set the book file.
			@param BookFile IN the book file.
		*/
		virtual void SetBookFile(const IDFile& BookFile) = 0;

		/**	Get the list of chapters where the styles will copy to.
			@param none
			@return UIDList* the list of chapters.
		*/
		virtual UIDList* GetUIDList() = 0;

		/**	Set the list of chapters where the styles will copy to.
			@param uidList IN the list of chapters.
		*/
		virtual void SetUIDList(UIDList* uidList) = 0;

		/**	Get the flag about if we do synchronize for all the chapters in the book or not.
			@param none
			@return bool16 kTrue means we do synchronize all the chapters, otherwise return kFalse.
		*/
		virtual bool16 IsSyncAll() = 0;

		/**	Get the flag about if we use the default options to do sync operations or not.
			@param none
			@return bool16 kTrue means use the current sync option on the book, kFalse means 
			        use the sync options from the UI. 
		*/
		virtual bool16 UseDefaultOptions() = 0;

		/**	Get the flag about if we just sync options or do sync chapters AND options.
			@param none
			@return bool16 kTrue means sync options only, otherwise kFalse means sync 
			        options and sync chapters.
		*/
		virtual bool16 ToSyncOptionsOnly() = 0; 
};

#endif //__IBOOKSYNCCMDDATA__