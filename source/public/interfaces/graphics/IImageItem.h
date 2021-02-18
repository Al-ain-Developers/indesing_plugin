//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageItem.h $
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
#ifndef __IIMAGEITEM__
#define __IIMAGEITEM__

#include "IPMUnknown.h"
#include "ImageID.h"

class UIDRef;

/**
	The IImageItem interface is a simple interface that lives on every raster image based
	page item.  Most often, the presense of this interface is used as a test as to whether
	or not a given page item is a raster image.  Also, this interface can be used to obtain
	color profile data from an image containing an embedded profile.
*/
class IImageItem : public IPMUnknown
{
public:		
	/** default IID for this interface */
	enum { kDefaultIID = IID_IIMAGEITEM};

	/** Determine whether or not this image has an embedded profile.
		@return kTrue if the image has an embedded profile.
	*/
	virtual bool32 HasProfile(void) const = 0;

	/** Retrieve the embedded color profile information from a full resolution image.
		@param imageItem - IN: This paramater is not used because this interface lives
			on the boss of the image and hence we already know the UIDRef.  That is,
			the UIDRef of the image is equal to ::GetUIDRef(this).
		@param dataSize - OUT: On return, the size of the profile data.
		@return	A pointer to the profile data which the client is responsible for deleting.
	*/
	virtual uchar* GetProfileData(const UIDRef& imageItem, uint32 *dataSize) const = 0;
};


#endif
