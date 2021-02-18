//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaReadFormat.h $
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
#ifndef __IMediaReadFormat__
#define __IMediaReadFormat__


#include "IPMUnknown.h"
#include "MediaID.h"
#include "MediaLocation.h"

class IMediaContentData;
class IPMStream;
class MediaLocation;
class PMRect;

/**	
	This interface provides read-only access to media content. This interface must be supported
	by all media filters.
*/
class IMediaReadFormat : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEDIAREADFORMAT };

	/** Tests if the media filter is able to access media content. This method allows users
		to determine if the filter is in a usable state without incurring the cost of a call
		to Open(). This method is particular useful if the implementation of this interface
		relies on an external component to access media.

		Note: if this method returns kFalse, then calls to all other methods are likely to fail.
		@return kTrue if media can be accessed; kFalse if not.
	*/
	virtual bool16 CanAccessMedia() = 0;

	/** Tests if the media filter can read and recognize the content at a specified
		MediaLocation. This method has no pre or post conditions.
		@param loc a MediaLocation to read.
		@return kTrue if the MediaLocation can be successfully read; kFalse otherwise.
		@see MediaLocation.
	*/
	virtual bool16 CanRead( const MediaLocation & loc ) = 0;

	/** Tests if the media filter recognizes the format of a stream-based content. This method
	    has no pre or post conditions.
		@param iPMStream an IPMStream to media content. The filter should not assume that the
		stream is positioned at the first content byte.
		@return kTrue if the stream's contents are recognized; kFalse otherwise.
	*/
	virtual bool16 CanRead( IPMStream* iPMStream ) = 0;

	/** Closes this interface to the media content. When this method returns, all streams
		provided by this interface are no longer valid. Calling this method when this interface
		is already closed is not considered to be an error.
		@return kSuccess if the close succeeded. A non-zero ErrorCode value is returned if
		an error occurred while closing the interface.
	*/
	virtual ErrorCode Close() = 0;

	/** Creates a readable stream to the media content.
		@param loc the media location.
		@return a pointer to a valid IPMStream object if content is available; nil otherwise.
	*/
	virtual IPMStream * CreateContentStreamRead( const MediaLocation & loc ) = 0;
		
	/** Retrieves media content data recognized by the filter. Content data is metadata
	    about the content. The metadata is set by the filter as IMediaContentData attributes.
	    @param contentData valid pointer to an IMediaContentData instance.
		@precondition The interface must be open before calling this method.
		@return kSuccess if the attributes were successfully retrieved; otherwise returns a
		non-zero ErrorCode.
	*/
	virtual ErrorCode GetAttributes( IMediaContentData * contentData ) = 0;

	/**
		Retrieves the error status for the last method called. Calling this method resets the
		error status to kSuccess; thus, calling this method twice in succession without an intervening
		call to	another method, always returns kSuccess for the second call.
		@return an ErrorCode, or kSuccess if no error occurred during the execution of the last
		method called.
	*/
	virtual ErrorCode GetLastError() = 0;

	/** Retrieves a stream to a poster image, if available.
		@precondition The interface must be open before calling this method.
		@return a valid pointer to an IPMStream instance if a poster image is available;
		returns nil otherwise.
		@postcondition The stream is valid as long as this interface is open. The stream is
		released by the implementation of this interface; do not issue an explicit Release()
		call on the stream.
	*/
	virtual IPMStream * GetPosterStream() = 0;

	/** Tests if this interface is open.
		@return kTrue if this interface is open; kFalse otherwise.
	*/
	virtual bool16 IsOpen() = 0;
					
	/** Opens this interface for reading a specified stream.
		@return kSuccess if the open succeeded or if this interface is already open; returns
		a non-zero ErrorCode value if an error occurred.
	*/
	virtual ErrorCode Open( IPMStream* iPMStream ) = 0;

	/** Opens this interface for reading a specified URL.
		@param url a valid URL string preceded by an http ("http://") or file ("file://")
	    protocol header.
		@return kSuccess if the open succeeded or if this interface is already open; returns
		a non-zero ErrorCode value if an error occurred.		
	*/
	virtual ErrorCode Open( const MediaLocation & loc ) = 0;

}; // end IMediaReadFormat interface class


#endif
