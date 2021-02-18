//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRestoreLinkCmdData.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IRestoreLinkCmdData__
#define __IRestoreLinkCmdData__

#include "IPMUnknown.h"
#include "IDatalink.h"
#include "LinksID.h"

class NameInfo;
class PMString;

class UIDList;

/** IRestoreLinkCmdData contains data for the restore link command (kRestoreLinkCmdBoss).
*/
class IRestoreLinkCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRESTORELINKCMDDATA };

	/** Set the data.
		@param db is the database.
		@param uid is UID of the data link (IDataLink).
		@param name is filename to use.
		@param type is the format name to use.
		@param filetype is the data link file type, 0 on Windows.
		@param state is the LinkState to use.
		@param fullPath is an option full path of the filename.
	*/ 
	virtual void Set(IDataBase *db, UID uid, NameInfo *name, PMString *type, uint32 filetype, IDataLink::StateType state, const PMString *fullPath = nil) = 0;

	/** Set the size and time stamp information.
		@param size is the file size in bytes.
		@param time is the file modified time stamp, see GlobalTime.h.
	*/
	virtual void SetSizeTime(uint64 *size, uint64 *time) = 0;

	/** Get the data base.
		@return the data base.
	*/
	virtual IDataBase *GetDataBase() = 0;

	/** Get the data link UID.
		@return the data link UID.
	*/
	virtual UID GetUID() = 0;

	/** Get the data link filename information.
		@return the filename.
	*/
	virtual NameInfo *GetName() = 0;

	/** Get the data link format name string.
		@return the format name.
	*/
	virtual PMString *GetType() = 0;

	/** Get the data link file type.
		@return the file type.
	*/
	virtual uint32 GetFileType() = 0;

	/** Get the data link state.
		@return the data link state.
	*/
	virtual IDataLink::StateType GetState() = 0;

	/** Get the data link file size.
		@return the data link file size in bytes.
	*/
	virtual uint64 *GetSize() = 0;

	/** Get the data link time stamp.
		@return the data link time stamp.
	*/
	virtual uint64 *GetTime() = 0;

	/** Get the data link full path name.
		@return the data link full path name.
	*/
	virtual const PMString *GetFullPath() = 0;
};

#endif
