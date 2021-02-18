//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FileTypeInfo.h $
//  
//  Owner: Richard Rodseth
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
#ifndef __FileTypeInfo__
#define __FileTypeInfo__

#include "PMTypes.h"
#include "PMString.h"


#ifdef PUBLIC_BUILD
#pragma export on
#endif

//========================================================================================
// CLASS FileTypeInfo
/**	Groups together a file type, file creator and file extension (always lowercase).
		@see FileTypeRegistry
*/
//========================================================================================

class PUBLIC_DECL FileTypeInfo
{
public:
	typedef object_type data_type;	

public:
	/** default constructor */
	FileTypeInfo();
	/** constructor */
	FileTypeInfo(const SysOSType& fileType, const SysOSType& fileCreator, const PMString& fileExtension, const PMString& mimeType, const FileTypeInfoID& fileTypeID);
	/** copy constructor */
	FileTypeInfo(const FileTypeInfo& other)
		{Copy(other);}

	~FileTypeInfo();
				
	/** Get the file type */
	SysOSType GetFileType();
	/** Get the file creator */
	SysOSType GetFileCreator();
	/** Get the file extension */
	const PMString&  GetFileExtension();
	/** Get the file mime type */
	const PMString&  GetFileMimeType();
	/** Get the file type info id */
	const FileTypeInfoID&  GetFileTypeInfoID();
	
	/** Set the file type */
	void SetFileType(const SysOSType& fileType);
	/** Set the file creator */
	void SetCreator(const SysOSType& creator);
	/** Set the file extension */
	void SetFileExtension(const PMString& extension);
	/** Set the file mime type */
	void SetFileMimeType(const PMString& mimeType);
	/** Set the file type info id */
  void SetFileTypeID(const FileTypeInfoID& id);

	/** equality operator */
	bool operator==(const FileTypeInfo &other) const;
	/** assignment operator */
	FileTypeInfo & operator=(const FileTypeInfo &other)
		{Copy(other); return *this;}

private:
	void Copy(const FileTypeInfo &other);

private:
	SysOSType		fFileType;
	SysOSType		fFileCreator;
	PMString		fFileExtension;
   PMString    fFileMimeType;
   FileTypeInfoID fFileTypeID; 
};


//--------------------------------------------------------------------------------------
// 	FileTypeInfo::GetFileType
//--------------------------------------------------------------------------------------

inline SysOSType FileTypeInfo::GetFileType()
{
	return fFileType;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::GetCreator
//--------------------------------------------------------------------------------------

inline SysOSType FileTypeInfo::GetFileCreator()
{
	return fFileCreator;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::GetFileExtension
//		(always lowercase)
//--------------------------------------------------------------------------------------

inline const PMString&  FileTypeInfo::GetFileExtension()
{
	return fFileExtension;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::GetFileMimeType
//		(always lowercase)
//--------------------------------------------------------------------------------------

inline const PMString&  FileTypeInfo::GetFileMimeType()
{
	return fFileMimeType;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::GetFileTypeInfoID
//--------------------------------------------------------------------------------------

inline const FileTypeInfoID&  FileTypeInfo::GetFileTypeInfoID()
{
	return fFileTypeID;
}
//--------------------------------------------------------------------------------------
// 	FileTypeInfo::SetFileType
//--------------------------------------------------------------------------------------

inline void FileTypeInfo::SetFileType(const SysOSType& fileType)
{
	fFileType = fileType;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::SetCreator
//--------------------------------------------------------------------------------------

inline void FileTypeInfo::SetCreator(const SysOSType& creator)
{
	fFileCreator = creator;
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::SetFileExtension
//		(always mapped to lowercase)
//--------------------------------------------------------------------------------------

inline void FileTypeInfo::SetFileExtension(const PMString& extension)
{
	fFileExtension = extension;
	fFileExtension.ToLower();
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::SetFileMimeType
//		(always mapped to lowercase)
//--------------------------------------------------------------------------------------

inline void FileTypeInfo::SetFileMimeType(const PMString& mimeType)
{
   fFileMimeType = mimeType;
   fFileMimeType.ToLower();
}

//--------------------------------------------------------------------------------------
// 	FileTypeInfo::SetFileTypeID
//--------------------------------------------------------------------------------------
inline void FileTypeInfo::SetFileTypeID(const FileTypeInfoID& id)
{
   fFileTypeID = id;
}


#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif // __FileTypeInfo__
