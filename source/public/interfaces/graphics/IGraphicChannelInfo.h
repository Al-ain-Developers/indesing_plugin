//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicChannelInfo.h $
//  
//  Owner: David Berggren
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
//  
//  Purpose:
//  Stores info about channels read in from a placed graphic (i.e. PSD or AI file)
//  Assumes channel names are unique
//  
//========================================================================================

#pragma once
#ifndef __IGraphicChannelInfo__
#define __IGraphicChannelInfo__

#include "IPMUnknown.h"
#include "IColorData.h"
#include "ImageID.h"
#include "PMString.h"

/** 
	An interface for holding the graphic channel information for
	placed graphics such as Photoshop (PSD) files. It is assumed 
	that the ID of each channel is unique.
*/
class IGraphicChannelInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICCHANNELINFO };

	/** 
		This enum represents the type of the channel. The 
		channel info can be a mix of alpha channels and 
		spot channels
	*/
	typedef enum 
	{
		/** the channel type is unknown or uninitialized
		*/
		kPMChannelTypeUnknown		= 0,

		/** the channel type is an alpha channel that is   
		    pre-multiplied into the color values of the image
		*/
		kPMAlphaAssociated			= 1,

		/** the channel type is an alpha channel that is 
		    not pre-multiplied into the image
		*/
		kPMAlphaUnassociated		= 2,

		/** the channel type is a spot channel
		*/
		kPMSpotChannel				= 3,	

		/** the channel type is an alpha channel that is 
		    not pre-multiplied into the image, but it is the
			background transparency mask
		*/
		kPMAlphaUnassociatedBackground	= 4	
	} GraphicChannelType;

	// ***********************
	// Add/Remove methods
	// ***********************

	/**	Add a channel into the interface. 
		@param channelName IN a PMString containing a channel name.
		@param channelID IN a unique number that can represent the channel
		@param channelType IN the type of channel as defined by GraphicChannelType
		@param channelOpacity IN the opacity of the channel, 0 = transparent, 100 = opaque
		@param colorSpace IN the color space of the channel, i.e. kPMCsCalCMYK
		@param colorData IN the color space's color data information
	*/
	virtual void AddChannel (	const PMString&					channelName, 
								const int32						channelID,
								const GraphicChannelType		channelType,
								const int32						channelOpacity,
								const int32						colorSpace,
								const ColorArray&				colorData
							) = 0;

	/**	Remove a channel from the interface.
		@param channelIndex IN the index of the channel to remove.
	*/
	virtual void RemoveChannel ( const int32 channelIndex ) = 0;

	/**	Clear all channels out of the interface.
	*/
	virtual void Clear() = 0;

	// ***********************
	// Set methods
	// ***********************

	/**	Set the channel name of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to rename.
		@param newName IN the new name to be given to the channel
	*/
	virtual void SetChannelName (const int32 channelIndex, const PMString& newName) = 0;

	/**	Set the channel ID of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to renumber.
		@param newID IN the new unique ID to be given to the channel
	*/
	virtual void SetChannelID (const int32 channelIndex, const int32 newID) = 0;

	/**	Set the channel type of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to change.
		@param newID IN the new GraphicChannelType to be given to the channel
	*/
	virtual void SetChannelType (const int32 channelIndex, const GraphicChannelType newType) = 0;

	/**	Set the channel opacity of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to change.
		@param newOpacity IN the new opacity to be given to the channel.  0 = transparent, 100 = opaque
	*/
	virtual void SetChannelOpacity (const int32 channelIndex, const int32 newOpacity) = 0;

	/**	Set the channel color information of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to change.
		@param colorSpace IN the new color space to be given to the channel, i.e. kPMCsCalCMYK 
		@param colorData IN the color space's color data information
	*/
	virtual void SetChannelColor (const int32 channelIndex, const int32 colorSpace, const ColorArray& colorData) = 0;

	// ***********************
	// Get methods
	// ***********************

	/**	Get the number of channels currently stored in the interface. For use when iterating
		through the channels, setting or getting specific information.
		@return int32 of the number of channels. 
	*/
	virtual int32 GetNumberChannels () const = 0;

	/**	Get the channel name of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return PMString of the channel name. 
	*/
	virtual PMString				GetNthChannelName (const int32 channelIndex) const = 0;
	/**	Get the channel ID of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return int32 of the channel ID. 
	*/
	virtual int32					GetNthChannelID (const int32 channelIndex) const = 0;
	/**	Get the channel type of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return GraphicChannelType of the channel type - see enum above. 
	*/
	virtual GraphicChannelType		GetNthChannelType (const int32 channelIndex) const = 0;
	/**	Get the channel opacity of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return int32 of the channel opacity, 0 = transparent, 100 = opaque 
	*/
	virtual int32					GetNthChannelOpacity (const int32 channelIndex) const = 0;
	/**	Get the channel color space of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return int32 of the channel color space, i.e. kPMCsCalCMYK 
	*/
	virtual int32					GetNthChannelColorSpace (const int32 channelIndex) const = 0;
	/**	Get the channel color space of a given channel index.
		@param channelIndex IN the index (zero based) of the channel to get.
		@return ColorArray of the channel color data - see IColorData.h
	*/
	virtual ColorArray				GetNthChannelColorData (const int32 channelIndex) const = 0;

};

#endif
