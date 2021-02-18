//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICreateLowResImageCmdData.h $
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
//  Data Interface for the CreateLowResImageCmd.  Use this interface to pass information
//  and options to the CreateLowResImageCmd.
//  
//========================================================================================

#pragma once
#ifndef __ICreateLowResImageCmdData__
#define __ICreateLowResImageCmdData__

#include "IPMUnknown.h"
#include "AGMImageAccessor.h"

class IImageAttributes;
class IPMStream;
class IImageStream;

/** ICreateLowResImageCmdData is used to pass command data to the kCreateLowResImageCmdBoss.
	When placing images (raster or vector based), InDesign creates a low resolution (typically 72ppi)
	version of the image and stores it in the document such that if the linked image is missing or
	out of date, we can still draw it and we can draw it much faster than drawing at full resolution.
	The proxy image that is generated is typically a kImageInDB boss object and its UID is stored
	in the IID_IIMAGEDATAACCESS interface off of the main page item's boss (e.g. kImageItem).
 
	The proxy image's boss (i.e. kImageInDB), has many of the same interfaces as the main page item
	for raster based images (i.e. kImageItem).  For example, both bosses have an IID_IIMAGEATTRIBUTES
	where the IID_IIMAGEATTRIBUTES on the main page item stores the attributes of the linked image
	as reported by the filter that parsed the image and the IID_IIMAGEATTRIBUTES on the proxy's boss
	stores the attributes of the proxy image.  The main page item boss for vector based images such as
	PDF and EPS have a different set of interfaces that are more pertinent to vector graphics.
 
	The kCreateLowResImageCmdBoss command is typically called when placing/importing images from the command
	that is responsible for filling out the interfaces on the main page item's boss.
 */
class ICreateLowResImageCmdData : public IPMUnknown
{
public:
	
	/** Data structure for passing the parameters that will be used to determine how to
		construct the proxy image.
	*/
	typedef struct {
		IDataBase* lowResImageDB; 						/** the database containing the UID */
		UID			lowResImageUID;						/** pregenerated UID of the resulting downsampled image.  Must contain an IID_IPERSISTUIDDATA interface and should also contain an IID_IIMAGEATTRIBUTES. */
		IImageAttributes *sourceAttributes;				/** source attributes of the image in the stream */
		IImageAttributes *destinationAttributes;		/** desired attributes of the downsampled image */
		IPMStream	*stream;							/** the read stream */
		bool8		embedStream;						/** kFalse to force a conversion of the image data to match the destination attributes.  kTrue to stuff entire stream in the pub. */
		int32		embedSize;							/** number of bytes from the stream to embed if embedStream is kTrue */
		IImageStream *readerSegment;					/** If nil, this command will attempt to locate a reader which believes it can
															parse and return the pixel data in the stream.  If non-nil, this segment will
															be used to provide the data to the ImageStreamManager. */
		ClassID		preferredFormat;					/** pass the ClassID of the IImageWriteFormat boss you want used to create the low res.
															If kInvalidClass, the cmd gets to choose (usually JPEG or TIFF). */
		bool8		showProgressBar;					/** Pass kFalse to suppress the progress bar */
	} lowResDataStruct;
	

	/**	If the proxy will be generated from a stream to an existing
		image, use the following Init().
	 
		@param data [IN]:  Contains information about the source image and how to construct the
			proxy image.
	 */
	virtual void Init( const lowResDataStruct *data ) = 0;
	
	/** Get the data that was set in Init( const lowResDataStruct*) if the proxy is being generated
		from a stream to an image.
		@return A pointer to the data.  This pointer is valid for the lifespan of the interface.
	 */
	virtual const lowResDataStruct * GetLowResInfo() const = 0;
	
	/** If the proxy will be generated from an in-memory bitmap, use the following Init().  Once this Init() 
		is called, the bitmap contained in the AGMImageAccessor will be owned by this interface and should 
		not be deleted.
	 
		@param imageAccessor [IN]: A pointer to the source bitmap from which to generate a proxy.
		@param resolution [IN]: The resolution of the bitmap.
	 */
	virtual void Init( const AGMImageAccessor *imageAccessor, uint32 resolution) = 0;

	/** Get the imageAccessor that was set in Init( const AGMImageAccessor *, uint32 *) if the
		proxy is being generated from an in-memory bitmap.
	 
		@param imageAccessor [OUT]: Optional. On return, will contain a pointer to the AGMImageAccessor
		@param resolution [OUT]: Optional. On return, will contain the resolution of the bitmap.
		@return True if a valid AGMImageAccessor was passed to Init(const AGMImageAccessor *, uint32 *).
	 */
	virtual bool8 GetImageAccessor(const AGMImageAccessor **imageAccessor, uint32 *resolution) const = 0;	
};

#endif
