//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDataLinkHelper.h $
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
#ifndef __IDataLinkHelper__
#define __IDataLinkHelper__

#include "IDatalink.h"

class IDataBase;
class UIDList;
class ICoreFilename;
class IMissingLink;
class NameInfo;

/**
This interface contains helper methods related to IDataLink.
*/
class IDataLinkHelper : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATALINKHELPER };

	/**
		Remove one or more data links from a document. Embedded data is removed for embedded links.
		@param const UIDList* itemList: A list of page items. The associated data links of these page items are deleted.
		@return int32: Return 0 when successful. 
	*/
	virtual int32 RemoveDataLink(const UIDList* itemList) = 0;

	/**
		Get the file extension for the given base name.
		@param PMString &basename: The base name.
		@param PMString &extension: Return the file extension.
	*/
	virtual void GetExtension(PMString &basename, PMString &extension) = 0;

	/**
		Create a data link given a IDFile.
		@param const IDFile &file: The IDFile.
		@param PMString *formatName = nil: The optional format string of describing the file data.
		@return IDataLink *: Return nil on failure.
	*/
	virtual IDataLink *CreateDataLink(const IDFile &file, PMString *formatName = nil) = 0;

	/**
		Set up a data link off the given boss with the given IDFile and format string.
		@param IPMUnknown *boss: A boss that holds an IDataLink.
		@param const IDFile &file: The IDFile.
		@param PMString *formatName = nil: The optional format string of describing the file data.
		@return ErrorCode: Return kSuccess when successful.
	*/
	virtual ErrorCode InitializeDataLink(IPMUnknown *boss, const IDFile &file, PMString *formatName = nil) = 0;

	/**
		Create a new data link based on the given datalink in the given database.
		@param IDataBase *db: The document containing the data link.
		@param IDataLink *dl: Data link pointer.
		@return UID: UID of a new IDataLink or kInvalidUID on failure. 
	*/
	virtual UID NewDataLinkUID(IDataBase *db, IDataLink *dl) = 0;

	/**
		Return whether a link is missing or not.
		@param IDataBase *db: The document containing the page item and data link.
		@param UID pageitemUID: The page item of the associated data link.
		@return bool16: Return true when the link is missing (not found). 
	*/
	virtual bool16 IsLinkMissing(IDataBase *db, UID pageItemUID) = 0;

	/**
		Get the publication's directory.	
		@param IDataBase *db: The document.
		@return ICoreFilename *: Return nil on failure.
	*/
	virtual ICoreFilename *CreatePublicationDir(IDataBase *db) = 0;

	/**
		Get the page item's provider and ask it for the format name and type.  Make up the name.
		@param IDataBase *db: The document containing the page item and data link.
		@param UID pageitemUID: The page item of the associated data link.
		@param NameInfo *ni: Return name information.
		@param PMString *formatName: Return format string.
		@param uint32 *filetype: Return file type.
	*/
	virtual void GetNameInfoFromEmbedded(IDataBase *db, UID pageitem, NameInfo *ni, PMString *formatName, uint32 *filetype) = 0;

	/**
		Search for a data link using several fast search strategies.
		@param NameInfo *pubdirni: Directory to use when looking for relative positioned links.
		@param IDataLink *dl: Data link pointer.
		@param IMissingLink *missingLink = nil: Optional parameter to speed up searching when repeatedly 
			calling AutoFindFile for many missing links.  Can use
			InterfacePtr<IMissingLink> missingLink((IMissingLink *)::CreateObject(kMissingLinkBoss, IID_IMISSINGLINK));
		@param bool32 bIgnoreDateTime = kFalse: [IN] if kFalse, then any potential matches will be ignored if the
			modification date is more than 1 hour different from the date/time returned via dl->GetStoredState().
			If kTrue, then the date/time of potential matches is ignored.
		@return IDataLink::StateType: The state of the link, found, missing or modified.
	*/
	virtual IDataLink::StateType AutoFindFile(NameInfo *pubdirni, IDataLink *dl, IMissingLink *missingLink = nil,
			bool32 bIgnoreDateTime = kFalse) = 0;

	/**
		Get the size of a UID.
		@param IDataBase *db: The document containing the UID.
		@param UID uid: UID.
		@return uint64: Size of the UID.
	*/
	virtual uint64 GetUIDSize(IDataBase *db, UID uid) = 0;

	/**
		Get the data link's IDFile for file type links (kDataLinkBoss).
		@param IDataLink *dl: Data link pointer.
		@param IDFile& sysFile: Return IDFile.
		@return ErrorCode: kSuccess when successful.
	*/
	virtual ErrorCode GetSysFile(IDataLink* dl, IDFile& sysFile) = 0;
};

#endif // __IDataLinkHelper__
