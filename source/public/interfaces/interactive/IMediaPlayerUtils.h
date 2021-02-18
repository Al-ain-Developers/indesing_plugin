//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaPlayerUtils.h $
//  
//  Owner: wtislar
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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
#ifndef __IMediaPlayerUtils_h__
#define __IMediaPlayerUtils_h__

#include "IMediaContent.h"
#include "IPMUnknown.h"

#include "MediaFilterID.h"
#include "Utils.h"

class IFlashPlayerController;
class IMediaContentData;
class IObserver;

/**
	This interface defines utility methods for accessing a media player.
*/
class IMediaPlayerUtils : public IPMUnknown
{
public:
	
	enum { kDefaultIID = IID_IMEDIAPLAYERUTILS };
	
	/** Tests if a player can obtain a poster from a specified URL. Posters may not be created for
		a variety of reasons, such as internal player error, security restriction or the media does
		not have a visual representation (pure audio media does not).
		@param mediaType specifies the type of media.
		@param mediaURL is a valid URL currently loaded in the player.
		@return true if a poster can be created; false otherwise.
	*/
	virtual bool CanCreatePosterFromURL( IMediaContent::MediaType mediaType, const WideString & mediaURL ) = 0;
	
	/** DEPRECATED **/
	virtual IPMStream * CreatePosterStream( IMediaContent::MediaType mediaType ) = 0;
	
	/** Tests if a player is able to create posters.
		@param mediaType specifies the type of media.
		@return true if the player can create posters; false otherwise.
	*/
	virtual bool CanCreatePosters( IMediaContent::MediaType mediaType ) = 0;
	
	/** Retrieves the current player playhead time.
		@param mediaType specifies the type of media.
		@param outTime is set to the playhead time in milliseconds.
	*/
	virtual ErrorCode GetPlayerTime( IMediaContent::MediaType mediaType, uint32 & outTime ) = 0;
	
	/** Tests if a URL is loaded for a media type.
		@param mediaType specifies the type of media.
	*/
	virtual bool IsMediaLoaded( IMediaContent::MediaType mediaType ) = 0;
	
	/** Initializes the player.
		@param pFlashPlayerController valid pointer to an IFlashPlayerController instance.
		@param mediaType specifies the type of media to be played. There is a single player for
		each of the types: enAudio, enVideo and enSWFAnimation.
		@return kSuccess if a player was successfully initialized; kFailure if a player was unavailable.
	*/
	virtual ErrorCode InitializePlayer( IFlashPlayerController * pFlashPlayerController, IMediaContent::MediaType mediaType ) = 0;

	/** Tests if a player has been initalized.
		@param mediaType specifies the type of media. Players exist for enAudio, enVideo and enSWFAnimation.
		@return true if the player is initialized; otherwise returns false.
	*/
	virtual bool IsPlayerInitialized( IMediaContent::MediaType mediaType ) = 0;
	
	/** Loads a player with a specified URL.
		@param url specifies a valid URL. Header must be "file", "http" or "rtmp". Extension must be "flv", "f4v", "swf" or "mp3".
		@param mediaType specifies the player media type.
		@param data valid pointer to IMediaContentData; attributes will be passed to the player as needed.
		@param iObserver points to IObserver instance to notify when a player event occurs.
		@param clientID if specified, prevents reloading the same url for the same clientID.
		@return kSuccess if the load was successful; kFailure otherwise.
	*/
	virtual ErrorCode PreviewMedia( const WideString & url, IMediaContent::MediaType mediaType, const IMediaContentData * data, IObserver * iObserver = nil, UIFlags uiFlags = kFullUI, UIDRef clientID = kInvalidUIDRef ) = 0;
	
	/** Terminates a player.
		@param mediaType specifies the player media type.
		@return kSuccess if the player was terminated; kFailure otherwise.
	*/
	virtual ErrorCode TerminatePlayer( IMediaContent::MediaType mediaType ) = 0;
	
	/** Removes a previously-loaded URL from the player.
		@param mediaType specifies the player media type.
		@return kSuccess if the URL was removed; kFailure otherwise.
	*/
	virtual ErrorCode UnloadMedia( IMediaContent::MediaType mediaType ) = 0;
	
	/** Retrieves the IFlashPlayerController instance for a media type.
		@param mediaType specifies the player media type.
		@return pointer to the IFlashPlayerController or nil if no controller is set.
	*/
	virtual IFlashPlayerController * GetPlayerController( IMediaContent::MediaType mediaType ) = 0;
	
	/** Sets the IFlashPlayerController instance for the media type.
		@param pFlashPlayerController valid pointer to an IFlashPlayerController instance or nil;
		@param mediaType specifies the player media type.
	*/
	virtual void SetPlayerController( IFlashPlayerController * pFlashPlayerController, IMediaContent::MediaType mediaType ) = 0;
	
	/** For internal Adobe use only */
	virtual void LogMessage( const PMString & debugMsg ) = 0;
};

#endif // __IMediaPlayerUtils_h__

