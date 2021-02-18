//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FileTypeRegistry.h $
//  
//  Owner: Steve Pellegrin
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
#ifndef __FileTypeRegistry_h__
#define __FileTypeRegistry_h__

#include "PMLocaleId.h"
#include "K2Vector.h"
#include "FileTypeInfo.h"
#include "OMTypes.h"
#include "KeyValuePair.h"
#include "DBUtils.h"
#include "IDResourceShell.h"

//========================================================================================
// CLASS FileTypeRegistry
//========================================================================================

#pragma export on

/**
 A global registry of file type information (file type, creator, file extension, and mime type)
 with a key of type FileTypeInfoID.

 There may be more than one set of file type information associated with a single key.
 For example, for the "document" key, we could have different sets of information for
 different versions of the product. This could happen if we decide to change the PC file
 extension and/or Mac file type from one version to the next.

 The last set of information added to each key is considered to be the "current" information.
 When you call FileTypeRegistry::GetFileTypeInfo(), for example, you are given the most-recently-added
 information. The moral: add historical info first and the current info last.

 Does not rely on the object model (so it can be used at startup).
	
 Data from all resources of type FileTypeTable in the application are added to the registry.
 */
class PUBLIC_DECL FileTypeRegistry
{
public:
	typedef K2Vector<FileTypeInfo>		FileTypeInfoList;
	typedef K2Vector<OSType>			OSTypeList;
	typedef K2Vector<PMString>			FileExtensionList;
	typedef K2Vector<PMString>			FileMimeTypeList;


public:
	/**
	 Default constructor.
	 Constructs a FileTypeRegistry object.
	 */
	FileTypeRegistry();

	/**
	 Destructor.
	 Destroys the FileTypeRegistry object.
	 */
	virtual ~FileTypeRegistry();
		
	/**
	 Checks if a file type information ID is registered.
	 @param id	IN File type information ID to check.
	 @return kTrue if the file type information ID is registered, else kFalse.
	 */
	static bool16 FileTypeIsRegistered(FileTypeInfoID id);
	
	/**
	 Adds a set of file type information for the specified file type ID. \\
	 The added entry is considered to be the "current" information and will be
	 returned by the various GetCurrent...() methods.
	 @param id			IN File type information ID.
	 @param fileInfo	IN File type information to add for the given ID.
	 */
	static void AddCurrentFileType(FileTypeInfoID id, const FileTypeInfo& fileInfo);

	/**
	 Un-registers a file type information ID.
	 Removes the current entry for the given ID.
	 @param id	IN File type information ID to remove the current entry for.
	 */
	static void RemoveCurrentFileType(FileTypeInfoID id);

	/**
	 Un-registers a file type information ID.
	 Removes all entries for the given ID.
	 @param id	IN File type information ID to remove all entries for.
	 */
	static void RemoveAllFileType(FileTypeInfoID id);
	
	/**
	 Returns the "current" file type information entry for the given file type information ID.
	 @param id	IN File type information ID to return the current entry for.
	 @return Current file type information for the given ID.
	 */
	static FileTypeInfo GetCurrentFileTypeInfo(FileTypeInfoID id);
	
	/**
	 Returns all the file type information entries for the given file type information ID. \\
	 Duplicate entries are not added to the list.
	 @param id			IN File type information ID to return all the entries for.
	 @param list		IN List to add the file type information entries to.
	 @param clearList	IN Denotes whether to clear the given list before adding
						   the file type information entries for the given ID.
	 @return kTrue if file type information entries were added to the list, else kFalse.
	 */
	static bool16 GetAllFileTypeInfo(FileTypeInfoID id, FileTypeInfoList &list, bool16 clearList);
	
	/**
	 Returns the "current" Mac file type for the given file type information ID.
	 @param id	IN File type information ID to return the current Mac file type for.
	 @return Current Mac file type for the given ID.
	 */
	static OSType GetCurrentFileType(FileTypeInfoID id);
	
	/**
	 Returns all the Mac file types for the given file type information ID. \\
	 Duplicate file types are not added to the list.
	 @param id			IN File type information ID to return all the Mac file types for.
	 @param list		IN List to add the Mac file types to.
	 @param clearList	IN Denotes whether to clear the given list before adding
						   the Mac file types for the given ID.
	 @return kTrue if any Mac file types were added to the list, else kFalse.
	 */
	static bool16 GetAllFileType(FileTypeInfoID id, OSTypeList &list, bool16 clearList);

	/**
	 Returns the "current" Mac creator for the given file type information ID.
	 @param id	IN File type information ID to return the current Mac creator for.
	 @return Current Mac creator for the given ID.
	 */
	static OSType GetCurrentFileCreator(FileTypeInfoID id);

	/**
	 Returns all the Mac creators for the given file type information ID. \\
	 Duplicate creators are not added to the list.
	 @param id			IN File type information ID to return all the Mac creators for.
	 @param list		IN List to add the Mac creators to.
	 @param clearList	IN Denotes whether to clear the given list before adding
						   the Mac creators for the given ID.
	 @return kTrue if any Mac creators were added to the list, else kFalse.
	 */
	static bool16 GetAllFileCreator(FileTypeInfoID id, OSTypeList &list, bool16 clearList);
	
	/**
	 Returns the "current" file extension for the given file type information ID. \\
	 The returned extension is always in lowercase.
	 @param id	IN File type information ID to return the current file extension for.
	 @return Current lowercase file extension for the given ID.
	 */
	static PMString GetCurrentFileExtension(FileTypeInfoID id);
	
	/**
	 Returns the "current" magic bytes for the given file type information ID.
	 @param id		IN File type information ID to return the current magic bytes for.
	 @param magic	OUT Current magic bytes for the given ID.
	 @return kTrue if the magic bytes were set, else kFalse.
	 */
	static bool16 GetCurrentMagicByte(FileTypeInfoID id, DBUtils::MagicBytes magic);

	/**
	 Returns all the file extensions for the given file type information ID. \\
	 The returned extensions are always in lowercase. \\
	 Duplicate extensions are not added to the list.
	 @param id			IN File type information ID to return all the extensions for.
	 @param list		IN List to add the extensions to.
	 @param clearList	IN Denotes whether to clear the given list before adding
						   the extensions for the given ID.
	 @return kTrue if any lowercase file extensions were added to the list, else kFalse.
	 */
	static bool16 GetAllFileExtension(FileTypeInfoID id, FileExtensionList &list, bool16 clearList);

	/**
	 Returns the "current" file mimetype for the given file type information ID. \\
	 The returned mimetype is always in lowercase.
	 @param id	IN File type information ID to return the current mimetype for.
	 @return Current lowercase file mimetype for the given ID.
	 */
	static PMString GetCurrentFileMimeType(FileTypeInfoID id);
	
	/**
	 Returns all the file mimetypes for the given file type information ID. \\
	 The returned mimetypes are always in lowercase. \\
	 Duplicate mimetypes are not added to the list.
	 @param id			IN File type information ID to return all the mimetypes for.
	 @param list		IN List to add the mimetypes to.
	 @param clearList	IN Denotes whether to clear the given list before adding
						   the mimetypes for the given ID.
	 @return kTrue if any lowercase file mimetypes were added to the list, else kFalse.
	 */
	static bool16 GetAllFileMimeType(FileTypeInfoID id, FileMimeTypeList &list, bool16 clearList);

	/**
	 Returns the best matching FileTypteInfoID for the given file. \\
	 On the mac, the file's finder filetype is compared first. If more than one match is found,
	 then the file's creator is taken into account, followed by file's extension if necessary. \\
	 On windows, only the file's extension is relevant.
	 @param file	IN File to find the best matching FileTypteInfoID for.
	 @return Best matching FileTypteInfoID for the given file.
	 */
	static FileTypeInfoID GetFileTypeInfoIDForFile(const IDFile& file);

private:
	void LoadFileTypeRegistry();
	bool SetupBootStrapStringStreamCallback(IDResource r);
	bool PubFileAliasCountCallback(IDResource r, void* count);
	void AddFileTypeTable(IPMStream* stream);
	void AddPubFileAlias(IPMStream* stream);
	void PrivAddCurrentFileType(FileTypeInfoID id, const FileTypeInfo& fileInfo);
	void PrivRemoveCurrentFileType(FileTypeInfoID id);
	void PrivRemoveAllFileType(FileTypeInfoID id);
	bool16 PrivFileTypeIsRegistered(FileTypeInfoID id);
	FileTypeInfo PrivGetCurrentInfo(FileTypeInfoID id);
	OSType PrivGetCurrentFileCreator(FileTypeInfoID id);
	bool16 PrivGetAllInfo(FileTypeInfoID id, FileTypeInfoList &list);
	bool16 MakeInfoMRU(FileTypeInfoID id);
	FileTypeInfoID AliasedInfoID(FileTypeInfoID id);
	
private:
	//--------------------------------------------------
	// Class IDInfo
	//    Used to store a set of FileTypeInfo objects
	//    associated with a single file type ID.
	//--------------------------------------------------
	class IDInfo
	{
	public:
		typedef object_type data_type;
		
		IDInfo()
			{}
		IDInfo(const FileTypeInfo &info)
			{AddCurrentInfo(info);}
		IDInfo(const IDInfo &other)
			{Copy(other);}
		~IDInfo()
			{}
			
		bool operator==(const IDInfo&) const { ASSERT_FAIL("appease K2Vector.Location"); return false; }

		void AddCurrentInfo(const FileTypeInfo &info)
			{fInfoList.push_back(info);}
		bool16 RemoveCurrentInfo()
			{fInfoList.pop_back(); return !fInfoList.empty();}
		bool16 GetAllInfo(FileTypeInfoList &list) const
			{list = fInfoList; return !fInfoList.empty();}
			
		IDInfo&operator =(const IDInfo &other)
			{Copy(other); return *this;}
	
	private:
		void Copy(const IDInfo &other)
			{fInfoList = other.fInfoList;}
			
	private:
		FileTypeInfoList	fInfoList;
	};
	
private:
	typedef KeyValuePair<FileTypeInfoID, IDInfo>	IDPair;
	typedef K2Vector<IDPair>						IDVector;
	
private:
	IDVector				fFileTypeTable;
	IDVector::iterator		fMRU;
	FileTypeInfoID			fPubFileAlias;
	FileTypeInfoID			fTmplFileAlias;
	OSType					fPubCurrentCreator;
};

#pragma export off

#endif // __FileTypeRegistry_h__
