//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRecentFileInfo.h $
//  
//  Owner: Michael Easter
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Description:
//  
//  
//========================================================================================


#pragma once
#ifndef __IRecentFileInfo__
#define __IRecentFileInfo__

// ----- Includes -----
#include "IPMUnknown.h"
#include "DocFrameworkID.h"
#include "IDTime.h"

/**
Interface used to hold file info for a document.
*/

class IRecentFileInfo : public IPMUnknown
{
public:
	struct FileInfo
	{
		typedef object_type data_type;

		FileInfo() : fThumbnailWidth(0), fThumbnailHeight(0), fFileSize(0)
		{
		}

		FileInfo(const std::string& encodedThumbnail, const std::string& format, int32 thumbnailWidth, int32 thumbnailHeight, uint32 fileSize, IDTime lastOpenedTime) :
			fEncodedThumbnail(encodedThumbnail),
			fFormat(format),
			fThumbnailWidth(thumbnailWidth),
			fThumbnailHeight(thumbnailHeight),
			fFileSize(fileSize),
			fLastOpenedTime(lastOpenedTime)
		{
		}

		std::string fEncodedThumbnail;	// File thumbnail data(Base 64 encoded)
		std::string fFormat;			// File thumbnail format
		int32		fThumbnailWidth;	// File thumbnail width
		int32		fThumbnailHeight;	// File thumbnail height
		uint64		fFileSize;			// File size
		IDTime		fLastOpenedTime;	// File last opened time
	};

	enum { kDefaultIID = IID_IRECENTFILEINFO };

	/**
		Sets a document file info.
		@param fileInfo	IN Document file info.
	*/
	virtual void SetFileInfo(const FileInfo& fileInfo) = 0;

	/**
		Returns the file thumbnail info.
		@param fileInfo	OUT Document file info.
	*/
	virtual void GetFileInfo(FileInfo &fileInfo) const = 0;
};

#endif	// __IRecentFileInfo__
