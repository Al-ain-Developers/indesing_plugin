//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ILowResImageList.h $
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
//  Purpose:
//  The implementation of this interface provides a mechanism for optimizing the
//  copy/pasting of images.  Specifically, it provides a means for NOT creating duplicates
//  of the low res proxy image which is embedded with each image at Place time.  Instead,
//  the low res is tracked by this list and when an image is copied and pasted, we simply
//  bump our persistant reference count in the image list instead of duplicating all
//  of the image data.  See also IScrapImageList.h.
//  
//========================================================================================

#pragma once
#ifndef __ILowResImageList__
#define __ILowResImageList__

#include "IPMUnknown.h"

/** The ILowResImageList is a pure virtual interface for a singleton list of
	all the proxy images in a given document.  Therefore, this interface lives
	on the kDocWorkspaceBoss with the IID_ILOWRESIMAGELIST interface id.  Every
	image, raster (e.g. tiff, jpeg, etc) and vector (pdf, pict, eps, wmf, etc.),
	has its own low resolution proxy created at place time such that it can
	efficiently be drawn without having to re-read the image data from the
	original image file every time the document is opened.  These proxies are
	stored in the ILowResImageList, allowing them to be shared if the same image
	is duplicated or placed multiple times.
*/
class ILowResImageList : public IPMUnknown
{
public:

	/** Increment the refcount for the image at position 'at'
		@param at - IN: zero-based index into the list of an image to addref.
		@return Returns the refcount value after the addref.
	*/
	virtual int32 PersistAddRef(int32 at) = 0;

	/** Decrement the refcount for the image at position 'at'
		@param at - IN: zero-based index into the list of an image to release.
		@return Returns the refcount value after the release.
	*/
	virtual int32 PersistRelease(int32 at) = 0;

	/** Look for a proxy image with the given UID.
		@param lowResUID - IN: The UID of the image
		@return Zero based index of the image or -1 if it cannot be found.
	*/
	virtual int32 FindImage(UID lowResUID) const = 0;

	/** Add a proxy image UID to the list
		@param lowResUID - IN: The UID of the new image.
	*/
	virtual void Add(UID lowResUID) = 0;

	/** Removes the given image from the list
		@param at - IN: zero-based index into the list of an image to remove.
	*/
	virtual void Remove (int32 at) = 0;

	/** Get the UID of the Proxy image at the entry referenced by the given index.
		@param at - IN: zero-based index.
		@return The UID at position 'at' or kInvalidUID if the position is not valid.
	*/
	virtual UID GetUID(int32 at) const = 0;

	/** Get the refcount of the proxy image at the given index.
		@param at - IN: zero-based index.
		@return the refcount (i.e. number of instances of imported page items sharing this proxy).
	*/
	virtual int32 GetRefCount(int32 at) const = 0;

	/** Routine to persist or read the list.
		@param iPMStream - IN/OUT: Source stream if reading, destination stream if writing.
		@param prop - IN: The implementation ID.
	*/
	virtual void ReadWrite (IPMStream* iPMStream, ImplementationID prop) = 0;

};

#endif

