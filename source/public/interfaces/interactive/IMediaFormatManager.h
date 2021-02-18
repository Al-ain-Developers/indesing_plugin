//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaFormatManager.h $
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
#ifndef __IMediaFormatManager__
#define __IMediaFormatManager__

#include "IPMUnknown.h"
#include "MediaID.h"
#include "MediaLocation.h"

class IMediaReadFormat;
class IMediaReadFormatInfo;
class IPMStream;

// DEPRECATED. DO NOT USE THIS INTERFACE.
// See IMediaUtils for equivalent methods.

/**
	This interface provides methods for obtaining read-only access to various media
	file formats.
*/ 
class IMediaFormatManager : public IPMUnknown
{

public:

	enum { kDefaultIID = IID_IMEDIAFORMATMANAGER };

	/** Verifies that a media location can be accessed for a MediaType. This method is 
		especially usefulfor checking whether URLs, though well-formed, can nevertheless
		be supported.
		@param loc a MediaLocation to media content.
		@param mediaType is either enMovie or enSound.
		@return kSuccess if the MediaLocation can be accessed, else an ErrorCode that
				describes why the MediaLocation can not be accessed.
	*/
	virtual ErrorCode CanAccess( const MediaLocation & loc, const MediaType mediaType ) = 0;

	/** Tests if the media at the specified location can be played. This could be used, for
		example, to test if a media item can be previewed.
		@return kTrue if the media can be played; kFalse otherwise.
	*/
	virtual bool16 CanPlay( const MediaLocation & loc ) = 0;

	/**
		Retrieves the error status for the last method called. Calling this method resets the
		error status to kSuccess; thus, calling this method twice in succession without an intervening
		call to	another method, always returns kSuccess for the second call.
		@return an ErrorCode, or kSuccess if no error occurred during the execution of the last
		method called.
	*/
	virtual ErrorCode GetLastError() = 0;

	/** Finds an IMediaReadFormat capable of reading media content from a stream.
		@param mediaType is either enMovie or enSound.
		@param iPMStream is a stream capable of reading the media content.
		@return valid pointer to an IMediaReadFormat instance if a format filter exists
		that recognizes the content; nil if a filter was not found.  
	*/ 
	virtual IMediaReadFormat* FindMediaReadFormat( MediaType mediaType, IPMStream* iPMStream ) = 0;

	/** Finds the IMediaReadFormat instance for a specified ClassID.
		@param readFormatClassID the ID of a boss aggregating the IMediaReadFormat interface.
		@return valid pointer to an IMediaReadFormat instance, if available; nil if not found.
	*/
	virtual IMediaReadFormat* FindMediaReadFormat( ClassID readFormatClassID ) = 0;
	
	/** Finds the IMediaReadFormat instance that can read from a specified MediaLocation.
		@param loc a MediaLocation to media content.
		@return valid pointer to an IMediaReadFormat instance which can access the URL and
		recognize the content. Returns nil if Internet access is not available, or there
		is no filter available which recognizes the content.
	*/
	virtual IMediaReadFormat* FindMediaReadFormat( const MediaLocation & loc ) = 0;

	/** Finds the IMediaReadFormatInfo instance that can provide information for a specified
		MediaLocation.
		@param loc a MediaLocation to media content.
		@return valid pointer to an IMediaReadFormatInfo instance which can provide information
		about the content referenced by the URL. Returns nil if no information is available.
	*/
	virtual IMediaReadFormatInfo* FindMediaReadFormatInfo( const MediaLocation & loc ) = 0;

}; // end IMediaFormatManager interface

#endif // end __IMediaFormatManager__
