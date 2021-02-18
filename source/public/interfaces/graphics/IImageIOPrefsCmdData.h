//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageIOPrefsCmdData.h $
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
//  
//  Purpose: This Data interface is used to pass image read and image write preference
//  data to the SetImageIOPrefsCmd.
//  
//========================================================================================

#pragma once
#ifndef __IImageIOPrefsCmdData__
#define __IImageIOPrefsCmdData__

#include "IPMUnknown.h"
#include "ImageID.h"

/** IImageIOPrefsCmdData
	Data interface for the kSetImageIOPrefsCmdBoss.  If the command has an item list, then
	the prefs will be set for the items in the list.  Otherwise, the command will set the prefs
	for the session.
	@see IImageIOPreferences.h
*/
class IImageIOPrefsCmdData : public IPMUnknown
{
public:
	/** default IID for this interface */
	enum { kDefaultIID = IID_IIMAGEIOPREFSCMDDATA };

	/** Set the desired resolution, clipping, auto-embedding and alpha channel name settings.
		@param preResolution - IN: Desired preview/proxy resolution.
		@param bClip - IN: kTrue to automatically apply embedded Photoshop clipping paths.
		@param allowAutoEmbedding - IN: kTrue to allow InDesign to automatically embed any
			image which is below the ILinkData::GetEmbedSize() threshold in size.
		@param alphaChannelName - IN: Name of the alpha channel to apply.
	*/
	virtual void Set(int32 preResolution,
					bool16 bClip,
					bool16 allowAutoEmbedding = kTrue,
					const PMString& alphaChannelName = PMString() ) = 0;

	/** Return the preferred resolution of the low resolution proxy
	*/
	virtual const int32 GetPreviewResolution() const  = 0;

	/** Return whether we should create a Frame based on any Photoshop embedded clipping path encountered
	*/
	virtual const bool16 GetCreateClippingFrame() const = 0;

	/** During import, if an image is small enough (smaller than ILinkData::GetEmbedSize())
		then it may be automatically embedded in the pub. Pass kFalse to SetAllowAutoEmbedding()
		to prevent the image from being embedded in the pub.
		@return Is it okay to automatically embed an image if it is determined to be small enough?
	*/
	virtual bool16 GetAllowAutoEmbedding(void) const = 0;

	/** During import, if an image has multiple alpha channels,
		the user can select which alpha they wish to apply.
		The name is the alpha channel name.
		If string is empty, it means no alpha is selected.
		Initial/default value is an empty string.
		@return The name of the alpha channel to apply.
	*/
	virtual PMString GetAlphaChannelName() const = 0;
};

#endif // __IImageIOPrefsCmdData__
