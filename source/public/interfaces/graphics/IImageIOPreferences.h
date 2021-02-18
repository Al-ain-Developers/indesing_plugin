//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageIOPreferences.h $
//  
//  Owner: Dave Stephens
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
#ifndef __IImageIOPreferences__
#define __IImageIOPreferences__

#include "IPMUnknown.h"
#include "ImageID.h"

/** IImageIOPreferences
	This class defines the import/place time preferences for an image.  This interface
	lives off of the workspace (session) and also off of each raster image page item (kImageItem boss).
	The workspace version defines the default settings for newly placed images.  The version
	on the image's boss defines the settings that were used to import that image.
	@see IImageIOPrefsCmdData.h
*/
class IImageIOPreferences : public IPMUnknown
{
public:
	/** default IID for this interface */
	enum { kDefaultIID = IID_IIMAGEIOPREFERENCES };

	/** During import we always create a proxy image which is stored inside the pub.
		The following resolution dictates the size of the low res image.
		@param resolution - IN: The desired proxy resolution.
	*/
	virtual void SetPreviewResolution(int32 resolution) = 0;
	
	/** Return the desired proxy resolution.
	*/
	virtual int32 GetPreviewResolution() const = 0;

	/** During import, if an image format contains a clipping path,
		the place provider has the option of creating a frame
		for the image based on the clipping path.  Setting this
		flag does not imply that there is a path, rather it indicates
		the preference to use if it exists.
		@param doClip - IN: kTrue to automatically apply clipping paths.
	*/
	virtual void SetCreateClippingFrame(bool16 doClip) = 0;
	
	/** Returns whether or not clipping paths will automatically be applied
		to images at Place time.
	*/
	virtual bool16 GetCreateClippingFrame() const = 0;

	/** During import, if an image is small enough (smaller than ILinkData::GetEmbedSize())
		then it may be automatically embedded in the pub. 
		@param allow - IN:  Pass kFalse to SetAllowAutoEmbedding() to prevent the image from 
			being embedded in the pub.
	*/
	virtual void SetAllowAutoEmbedding(bool16 allow) = 0;

	/** Returns whether it is okay to automatically embed an image if it is determined to be small enough
	*/
	virtual bool16 GetAllowAutoEmbedding(void) const = 0;

	/** During import, if an image has multiple alpha channels,
		the user can select which alpha they wish to apply.
		The name is the alpha channel name.
		If channelName is empty, it means no alpha is selected.
		Initial/default value is an empty string.
		@param channelName - IN: The name of the alpha channel.
	*/
	virtual void SetAlphaChannelName(const PMString& channelName) = 0;
	
	/** Returns the name of the alpha channel to apply.
	*/
	virtual PMString GetAlphaChannelName() const = 0;

};

#endif
