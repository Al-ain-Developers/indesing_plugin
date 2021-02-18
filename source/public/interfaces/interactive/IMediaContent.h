//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaContent.h $
//  
//  Owner: wtislar
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
#ifndef __IMediaContent__
#define __IMediaContent__

#include "IPMUnknown.h"

#include "MediaID.h"
#include "MediaLocation.h"
#include "IMediaAttributes.h"

/**
	Provides access to media content.
*/
class IMediaContent : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IMEDIACONTENT };

	enum MediaType
	{
		enUndefined, 
		enVideo,
		enAudio,
		enLegacyVideo = 4,	// pre-CS5 video types
		enLegacyAudio	// pre-CS5 audio types
	};
	
	/**
		Provides an IPMStream to read the media content.
		@param rawContentRequired set to kTrue to assure that the stream provides raw,
		unfiltered content. For file-based content, this is equivalent to reading directly
		from the file.
	*/
	virtual IPMStream * CreateContentStreamRead( bool16 rawContentRequired = kFalse ) = 0;

	/** Retrieves the standard MIME type for the media content.
		@return a PMString populated with the mime type; if the MIME type is unknown or
		unavailable, returns a null string.
	*/
	virtual PMString GetMimeType() = 0;

	/** Retrieves the location of the media content.
		@return MediaLocation object.
		@see MediaLocation.
	*/
	virtual const MediaLocation GetLocation() const = 0;

	/** Retrieves the media base file name (without the path).
		@return a PMString object representing the base file name of the media content.
		The string may be null; i.e., it may have zero length.
	*/
	virtual const PMString GetMediaFileName() const = 0;

	/** Retrieves the full media file path.
		@return a PMString object representing the absolute path to the media content.
		The string may be null; i.e., it may have zero length.
	*/
	virtual const PMString GetMediaFilePath() const = 0;

	/** Retrieves the full path for a poster image.
		@return a PMString representing the absolute local path to an image file.
	*/ 
	virtual const PMString GetPosterPath() const = 0;

	/** Retrieves the IMediaAttributes::PosterType for the media page item.
		@return the IMediaAttributes::PosterType.
	*/
	virtual IMediaAttributes::PosterType GetPosterType() const = 0;

	/** Retrieves the UID of the media poster page item.
		@return a page item UID. If the poster page item does not exist, returns kInvalidUID.
	*/
	virtual const UID GetPosterUID() const = 0;

	/** Tests if content has been set. Useful to test when deciding if the media page item
		can be exported or is simply acting as a placeholder.
		@return kTrue if there is content; kFalse if there is none.
	*/
	virtual bool16 HasContent() const = 0;

	/** Tests if a poster is available by determining if
		(1) the content has a poster, and
		(2) the content can be accessed to obtain the poster.
		@return kTrue if poster can be accessed; kFalse if not.
	*/
	virtual bool16 IsPosterAvailable() const = 0;
	
	/** Retrieves the MediaType.
		@return IMediaContent::MediaType.
	*/
	virtual IMediaContent::MediaType GetMediaType() const = 0;

}; // end IMediaContent interface

#endif // __IMediaContent__
