//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IImageUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IImageUtils__
#define __IImageUtils__

#include "ImageID.h"
#include "IPMUnknown.h"
#include "IImageAttributes.h"
#include "Utils.h"

#if MACINTOSH
const RsrcID kPCXType = 'PCXC';
#else
const RsrcID kPCXType = 301;
#endif


#include "IShape.h"
#include "BravoForwardDecl.h"

class IPMStream;
class ICopyableInMemoryCache;


/** Utility methods designed to quickly obtain information about a given
	raster based image.  Some of these utils are designed to work with PDF, EPS, AI, WMF, DCS and PICT images
	but most are designed to work with pure raster formats such as TIFF, JPEG, etc.
	<pre>Utils<IImageUtils>()->IsEmbeddedImage( ... );</pre>

	@see SnapshotUtils.h for information about creating a snapshot of a portion of the document as a
	TIFF, JPEG or GIF.

	@ingroup layout_util
*/
class IImageUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMAGEUTILS };
	enum { kUseFirstAlpha = kMaxUInt32 };

	/**	IsEmbeddedImage is a routine for pure raster images which returns true if
	 	the image was embedded. Note, it the image was embedded as a side effect of a 
	 	place (as would happen for small images which are wholly embedded rather than
	 	represented by a proxy) this routine returns false. If you need to determine whether
	 	the image is embedded in the links panel, test IDataLink::GetStoredState. This
		routine was written for raster image formats.
		@param boss 
		@return bool16 
	 */
	virtual bool16 IsEmbeddedImage(const IPMUnknown* boss) = 0;

	/**	Image reading utility.  This routine constructs a read stream to the image data
		associated with imageRef.  If the image was embedded at place time, then the stream
		will point to the embedded data rather than the linked image on disk.
		@param imageRef 
		@return IPMStream 
	 */
	virtual IPMStream *GetImageStream(const UIDRef& imageRef) = 0;

	/**	Get a platform specific, 256 color RGB color map. Caller
		is responsible for deleting the result.
		@return system color RGB map
	 */
	virtual uint8* GetPlatformSystemClut(void) = 0;

	/**	Determine if item is a raster or a vector graphic, or some other kind.
		@param boss 
		@return kTrue if the item is a raster image or vector graphic, kFalse otherwise.
	 */
	virtual bool16 IsGraphic(const IPMUnknown* boss) = 0;


	/**	Determine if item is a raster or a vector graphic, or some other kind.
		@param imageRef 
		@return kTrue if the item is a raster image or vector graphic, kFalse otherwise.
	 */
	virtual bool16 IsGraphic(const UIDRef& imageRef) = 0;

	/**	Determine if item is a raster image (For example TIFF, JPEG, PCX, BMP, PNG, GIF, Scitex CT)
		@param boss of the item to check its type. 
		@return returns kTrue if the item is a raster image. 
	 */
	virtual bool16 IsRasterImage(const IPMUnknown* boss) = 0;

	/**	Determine if item is a raster image (For example TIFF, JPEG, PCX, BMP, PNG, GIF, Scitex CT)
		@param imageRef, UIDRef of the item to check its type. 
		@return returns kTrue if the item is a raster image. 
	 */
	virtual bool16 IsRasterImage(const UIDRef& imageRef) = 0;

	/**	Determine if item is a vector graphic (For example PDF, EPS, WMF, PICT)
		@param boss of the item to check its type. 
		@return returns kTrue if the item is a vector graphic (which may or may not contain raster data). 
	 */
	virtual bool16 IsVectorGraphic(const IPMUnknown* boss) = 0;

	/**	Determine if item is a vector graphic (For example PDF, EPS, WMF, PICT)
		@param imageRef UIDRef of the item to check its type. 
		@return returns kTrue if the item is a vector graphic (which may or may not contain raster data). 
	 */
	virtual bool16 IsVectorGraphic(const UIDRef& imageRef) = 0;

	/**	Returns the UID of the proxy and the page item for a page item with
		a link which matches the link from which the given stream was created.
		This utility allows the client to avoid creating a duplicate proxy when
		the same image is placed multiple times.
		@param stream 
		@param srcPageItem 
		@param dupPageItemUID [OUT] 
		@param dupProxyUID [OUT] 
	 */
	virtual void GetDuplicateProxy(const IPMStream& stream, const UIDRef& srcPageItem, UID *dupPageItemUID, UID *dupProxyUID) = 0;

	/**	looks in the IImageAttributes of the provided imageRef or proxyRef for the kPMTagICCProfileData
		tag and converts the data within the tag, if present, to an AGMColorSpace*.  This routine
		was written for raster formats.
		@param imageOrProxyRef reference to image or a proxy 
		@return pointer to AGM color space
	 */
	virtual AGMColorSpace *GetAGMColorProfileFromImage(UIDRef imageOrProxyRef) = 0;


	/**
		Image Tag Utils...
		Here are all of the ImageTag Get (ITG) functions that have default
		values when the tag doesn't exist. These functions are provided 
		for convenience.
	*/

	/**	Helper method to access kPMTagChannelTypeArray tag information.
		Checks if there is an alpha channel defined in the channel info array
		@param iImageAttributes 
		@return Returns kTrue if alpha channel is found, kFalse otherwise 
	 */
	virtual bool16 ITGAlphaExists(const IImageAttributes* iImageAttributes) = 0;

	/**	Helper method to access kPMTagChannelTypeArray tag information
		tries to get the alpha type of the given index
		@param iImageAttributes 
		@param index [IN] - if kUseFirstAlpha passed in, look for the first alpha (skipping over
			any spot channels) and return it.  Otherwise, treat index as a zero-based index into
			the array of alphas and spots.
		@return alpha type of the alpha or spot indicated by index.  If there is a problem , kPMAlphaUnassociated otherwise.
	 */
	virtual uint32 ITGAlphaType(const IImageAttributes* iImageAttributes, uint32 index = kUseFirstAlpha) = 0;

	/**	helper method to access kPMTagChannelTypeArray tag information
		@param iImageAttributes 
		@return returns the total number of channels in the array 
	 */
	virtual uint32 ITGNumberOfChannels(const IImageAttributes* iImageAttributes) = 0;

	/**	helper method to access kPMTagChannelTypeArray tag information
		@param iImageAttributes 
		@return returns the number of alpha channels in the array 
	 */
	virtual uint32 ITGNumberOfAlphaChannels(const IImageAttributes* iImageAttributes) = 0;

	/**	helper method to access kPMTagChannelTypeArray tag information
		@param iImageAttributes 
		@return returns the number of spot channels in the array 
	 */
	virtual uint32 ITGNumberOfSpotChannels(const IImageAttributes* iImageAttributes) = 0;

	/**	Helper method to access kPMTagNumberOfLayers tag information (method moved from ImageTagUtils.cpp)
		@param iImageAttributes 
		@return returns number of layers stored in kPMTagNumberOfLayers tag, or 1 if tag doesn't exist 
	 */
	virtual uint32 ITGNumberOfLayers(const IImageAttributes* iImageAttributes) = 0;

	/**	helper method to access kPMTagChannelNameArray tag information
		@param iImageAttributes 
		@param channelNames [OUT] returns the channel names in the K2Vector passed in 
		@return returns number of channel names stored in kPMTagChannelNameArray tag, or 0 if tag doesn't exist 
	 */
	virtual uint32 ITGGetChannelNames(const IImageAttributes* iImageAttributes, K2Vector<PMString>& channelNames) = 0;

	/**	Helper method to access kPMTagChannelTypeArray tag information
		@param iImageAttributes 
		@param channelTypes [OUT] returns the channel types (i.e. kPMAlphaAssociated) stored in the K2Vector passed in 
		@return returns number of channels stored in kPMTagChannelTypeArray tag, or 0 if tag doesn't exist 
	 */
	virtual uint32 ITGGetChannelTypes(const IImageAttributes* iImageAttributes, K2Vector<uint32>& channelTypes) = 0;

	/**	If the linked content associated with the specified source page item has a duplicate
		somewhere else in the document, and that has a 'full' in memory cache, then return it.
		the ICopyableInMemoryCache can be used to copy the in-memory contents from the source
		page item to a duplicate destination page item.  Although the interface allows implementations for
		any page item, it currently (InDesign 3.0) only has implementations for 
		vector image types (e.g. EPS, PDF, WMF, PICT) and not raster.

		@param srcPageItem 
		@return ICopyableInMemoryCache* 
	 */
	virtual ICopyableInMemoryCache* QueryDuplicateCache( const UIDRef& srcPageItem ) = 0;

	/** Images created with Photoshop often have an RGB thumbnail embedded in its 8BIM data resource, which
		is stored in the images "tags."  This method attempts to extract the thumbnail from the 8BIM tag of
		the main image item's IImageAttributes and copy it to the prevBaseaddr.  It is assumed that the output
		buffer pointed to by prevBaseaddr is big enough to hold the image. Note that if bLongAlign is true, then
		the output will be padded if necessary to ensure that each scanline has a multiple of 4 bytes.
		@param iImageAttributes [IN]: A pointer to the IImageAttributes, presumably from a kImageItem, containing
			the attributes of the source image.
		@param prevBaseaddr [IN/OUT]: A pointer to the output buffer where RGB data will be copied.
		@param prevWidth [IN/OUT]: On entry, the number of pixels wide the output buffer is prepared to hold. If bDoJustify is
			kFalse, then on return, prevWidth will contain the pixel width of the returned thumbnail.  If bDoJustify
			is kTrue, then on return, prevWidth will contain the same value as on entry and the thumbnail will
			be centered within the input width. Note that the returned value will never be larger than the value on entry.
		@param prevHeight [IN/OUT]: On entry, the number of scanlines the output buffer is prepared to hold.  If bDoJustify is
			kFalse, then on return, prevHeight will contain the pixel height of the returned thumbnail.  If bDoJustify
			is kTrue, then on return, prevHeight will contain the same value as on entry and the thumbnail will
			be centered within the input height. Note that the returned value will never be larger than the value on entry.
		@param bDoJustify [IN]: If kTrue, then center the thumbnail within the provided bitmap buffer and do not change the
			prevWidth and prevHeight.  If kFalse, then align the thumbnail with the upper left of the provided bitmap buffer
			and change the values of prevWidth and prevHeight to match the actual thumbnail size.  In either case, the aspect
			ratio of the thumbnail is preserved.
		@param bLongAlign [IN]: If kTrue, then pad each row of image data to ensure a multiple of 4 row bytes.
		@return kTrue if a thumbnail was found and successfully copied to the output buffer.  kFalse otherwise.
	*/
	virtual bool32 GetPhotoshopThumbnail(
		const IImageAttributes *iImageAttributes,
		uint8*		prevBaseaddr,
		uint32*		prevWidth,
		uint32*		prevHeight,
		bool32		bDoJustify,
		bool32		bLongAlign = kFalse
	) = 0;

	/** If the image is a native duotone image (i.e. it has an IDuotoneInfo interface with
		a non-zero number inks), then return the CAGMColorSpace to apply to the grayscale image
		to get the proper effect.  If the returned colorspace has an IsValid result of false, then
		this image is not a duotone.
		@param imageObject [IN]: a pointer to the page item (presumably a kImageItem).
		@return the duotone colorspace or an invalid colorspace if the image is not a duotone.
	*/
	virtual CAGMColorSpace GetDuotoneColorSpace(IPMUnknown *imageObject) = 0;

	/** For the image refered to by the UIDRef, attempt to read out the tiff:Orientation meta data
		information, and return the angle in metaDataOrientation. This API will only return kSuccess
		for TIFF orientations of 1 (top left) [returns angle 0]; 3 (bottom right) [returns 180]; 
		6 (right top) [returns 90] and 8 (left bottom) [returns -90]
		@param uidRef [IN]: a UIDRef of the image item.
		@param metaDataOrientation [OUT]: the orientation out of the meta data, either 
		0, 90, -90 or 180. Note: we return kFailure for any orientation that involves a flip.
		@return ErrorCode: kSuccess if successful; kFailure if error or flipped or doesn't exist.
	*/
	virtual ErrorCode GetMetaDataOrientation(const UIDRef& uidRef, int16* metaDataOrientation) = 0;

	/** For the image attributes refered to by the IImageAttributes pointer, attempt to
		read out the tiff:Orientation meta data	information, and return the angle in 
		metaDataOrientation. This API will only return kSuccess	for TIFF orientations 
		of 1 (top left) [returns angle 0]; 3 (bottom right) [returns 180]; 6 (right top)
		[returns 90] and 8 (left bottom) [returns -90].
		@param iImageAttributes [IN]: a pointer to the IImageAttributes of the image item.
		@param metaDataOrientation [OUT]: the orientation out of the meta data, either 
		0, 90, -90 or 180. Note: we return kFailure for any orientation that involves a flip.
		@return ErrorCode: kSuccess if successful; kFailure if error or flipped or doesn't exist.
	*/
	virtual ErrorCode GetMetaDataOrientation(IImageAttributes* iImageAttributes, int16* metaDataOrientation) = 0;

	/** Rotates the image data in right angle (90 degree) increments. A pointer to the image data along with metrics
		are passed in and the resulting image returned in the same buffer. If bJustify is set true, the resulting 
		image will be centered. If bReorient is set true, the rotated image's height and width are returned as well.
		@param iImageAttributes [IN]: A pointer to the IImageAttributes, presumably from a kImageItem, containing
			the attributes of the source image.
		@param imageBuffer [IN/OUT]: A pointer to the image data buffer containing the source image data. This buffer
			will also contain the rotated image upon return.
		@param imageWidth [IN/OUT]: On entry, the number of pixels wide the image buffer holds.  If bReorient is
			kFalse, then on return, width will be unchanged. If bReorient is kTrue, then on return, width 
			will contain the number of pixels of width of the rotated image.
		@param imageHeight [IN/OUT]: On entry, the number of scanlines the image buffer holds.  If bReorient is
			kFalse, then on return, height will be unchanged. If bReorient is kTrue, then on return, height 
			will contain the number of scanlines of the rotated image.
		@param imageChannels [IN]: The value for the number of channels each image pixel contains.
		@param rotation [IN]: The value for the rotation. Acceptable values are 0, 90, -90, & 180.
		@param bReorient [IN]: If set to true, this flag will cause the image height and width to be swapped if necessary.
		@return kTrue if a thumbnail was found and successfully copied to the output buffer.  kFalse otherwise.
	*/
	virtual bool32 RotateThumbnailImage(
		const IImageAttributes *iImageAttributes,
		uint8*		 imageBuffer,
		int32*		 imageWidth,
		int32*		 imageHeight,
		const int16  imageChannels,
		const int16  rotation,
		const bool32 bDoJustify = kTrue,
		const bool32 bReorient  = kFalse
	) = 0;

	/**    Writes JPEG data to the supplied IPMStream.
	@param data is the JPEG data in RGB layout.
	@param width is the width of the image.
	@param height is the height of the image.
	@param outStream is the stream in which the JPEG will be written.
	@return true if successful.
	*/
	virtual bool16 WriteJPEGToStream(char* data, uint32 width, uint32 height, IPMStream* outStream) = 0;

	/**    Returns the Image attributes.
	@param itemRef[IN]: a UIDRef of the image item.
	@return IImageAttributes* if successful else nil.
	*/
	virtual IImageAttributes* QueryImageAttributes(const UIDRef& itemRef) = 0;
};


#endif	// __IImageUtils__
