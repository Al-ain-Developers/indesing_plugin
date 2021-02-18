//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageAttributes.h $
//  
//  Owner: jargast
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
#ifndef __IImageAttributes__
#define __IImageAttributes__

#include "IPMUnknown.h"
#include "ImageTypes.h"
#include "ImageID.h"
#include "UIDList.h"

/** IImageAttributes are a collection of tags used to describe the attributes of a raster image.
	The format is very similar to TIFF tags.  Each tag ID is associated with a data type, a length 
	and the data itself.
*/
class IImageAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMAGEATTRIBUTES};

	/** ImageTagTypes enumeration.
		We know the size of the tags enumerated below.  However, if a plugin
		desires to add its own tag, we have to know how to Xfer it and to do so
		we have to know the type.  This realization came after this interface
		was designed and implemented.  Hence, I've added a type argument to SetTag()
		which defaults to kPMTagDefault.  Any plugin which wants to add its own tags
		simply needs to pass one of the following types to SetTag().
	*/
	typedef enum {
		kPMTagDefault				= 0,	// If not one of the Tags enumerated below, then treat as bytes
		kPMTagByte					= 1,	// 8-bit quantity
		kPMTagWord					= 2,	// 16-bit integer
		kPMTagLong					= 3,	// 32-bit integer
		kPMTagFixed					= 4		// 32-bit quantity containing the integer part in the 
											// high order word and the fractional part in the low order 
											// word.  Divide by 65536.0 to convert to float
	} ImageTagTypes;

	/** OPI tags identifier.
		Arithmatically OR kOPIExtraTIFFASCIITagPrefix with a tagID when
		calling SetTag() to mark it as an ASCII tag which should be downloaded
		at print time as an OPI2 %%TIFFASCIITag: comment.  See Open Prepress
		Interface--Version 2.0 specification to learn more about the
		%%TIFFASCIITag: comment.  To retrieve these tags, simply iterate over
		all of the tags using GetTagCount() and GetNthTagID() and simply
		test (GetNthTagID(tagIndex) & kOPIExtraTIFFASCIITagPrefix) == kOPIExtraTIFFASCIITagPrefix.
	*/
	enum {
		kOPIExtraTIFFASCIITagPrefix = 0x17000000
	};

	/** Tag constants.  Most are taken straight from TIFF
		R = required
		TO ADD YOUR OWN TAGS:
		1.  Arithmatically OR your tag ID with your plugin prefix
		2.  When calling SetTag(), pass the appropriate ImageTagType.
	*/
	enum
	{
		kPMTagImageWidth			= 100,	//R TYPE: uint32	
		kPMTagImageHeight			= 101,	//R TYPE: uint32
		kPMTagBitsPerChannel		= 102,	//R TYPE: uint32	1, 2, 4, 6, and 8 are supported.
		kPMTagColorSpace			= 103,	//R TYPE: uint32	One of the defined PM image color spaces
		kPMTagDocumentName			= 104,	//  TYPE: array		null terminated string
		kPMTagImageDescription		= 105,	//  TYPE: array		null terminated strings
		kPMTagChannelsPerPixel		= 106,	//R TYPE: uint32	Number of channels (including extra samples) in image
		kPMTagNumberOfLayers		= 107,	//	TYPE: uint32	default 1, but for Photoshop format images could be more
		kPMTagXResolution			= 108,	//R TYPE: UFixed32	X resolution in DPI (UNSIGNED 32-bit quantity containing the integer part in the 
											//					high order word and the fractional part in the low order word).
		kPMTagYResolution			= 109,	//R TYPE: UFixed32	Y resolution in DPI (UNSIGNED 32-bit quantity containing the integer part in the 
											//					high order word and the fractional part in the low order word).
		kPMTagPlanarConfig			= 110,	//R TYPE: uint32	kPMChunky or kPMPlanar.
		kPMTagColorMap				= 111,	//  TYPE: array		Arranged in interleaved order, 1 >> numBits entries. 
		kPMTagOptimalTileWidth		= 112,	//  TYPE: uint32	Gives the width in pixels of the best tile size to ask for
		kPMTagOptimalTileHeight		= 113,	//  TYPE: uint32	Gives the height in pixels of the best tile size to ask for
		kPMTagChannelNames			= 114,	//  TYPE: array		null terminated strings.  There should be SamplesPerPixel names
		kPMTagChannelInfo			= 115,	//  TYPE: array		TODO:  set of channel descriptions.  Primary, mask, assocatied, unassociated?
		kPMTagLayerInfo				= 116,	//	TYPE: array		TODO:  layer info. Required if num layers > 1
		kPMTagTIFFClipPath			= 117,	//  TYPE: array		TIFF clipping path data.
		kPMTagTIFFXClipPathUnits	= 118,	//  TYPE: uint32		
		kPMTagTIFFYClipPathUnits	= 119,	//  TYPE: uint32
		kPMTagOPIProxy				= 120,	//  TYPE: uint8		0 = not proxy, 1 = proxy: high-res image is given by kPMTagOPIImageID
		kPMTagOPIImageID			= 121,	//  TYPE: array		Full path name of original high-res image
		kPMTagICCProfileData		= 122,	//  TYPE: array		black box inter color 3.0 profile
		kPMTagWhiteIsZero			= 123,	//	TYPE: uint8		For bilevel and grayscale images: True: indicates 0 is imaged as white, False: indicates 0 is imaged as black.
											//					If no tag value is set, then 1-bit images will be treated as 1 and non-1-bit grayscale images will be treated as 0
											//					by the ImageStreamManager.
		kPMTagAlphaType_obsolete	= 124,	//	TYPE: uint32	depreciated - replaced by kPMTagChannelTypeArray
		kPMTagTIFFClipPathName		= 125,	//  TYPE: array		Name of the Photoshop clipping path which identifies the resource.
		kPMTagNoOPIGeneration		= 126,	//  TYPE: uint8		If non-zero, InDesign will not generate OPI comments for this image.
		kPMTagNeverOmit				= 127,	//  TYPE: uint8		If non-zero, InDesign will never Omit this image.
		kPMTagPhotoshop8BIM			= 128,	//	TYPE: array		PhotoShop's Image Resource Block field
		kPMTagTransparencyMask		= 129,	//	TYPE: uint8		zero-based index with respect to the first extra channel of the channel
											//					to use as a kPMUnassociatedTransparency mask.
		kPMTagAlphaPacking			= 130,	//	TYPE: uint32		kPMAlphaPackingPreOrder or kPMAlphaPackingPostOrder -- PostOrder is preferred.  PreOrder may not
											//					be supported by Write filters.
		kPMTagNumberOfVisibleLayers	= 131,	//	TYPE: uint32	number of visible layers
		kPMTagVisibleLayerInfo		= 132,	//	TYPE: array		if num visible layers exists and is > 0, array of name strings
		kPMTagXMPData				= 133,	//  TYPE: array		A block of XMP data.
		kPMTagChannelTypeArray		= 134,	//	TYPE: array		one of kPMAlphaAssociated, kPMAlphaUnassociated or kPMSpotChannel. Default is kPMAlphaUnassociated.
											//					kPMAlphaAssociated indicates a transparency mask where the alpha has been pre-multiplied into
											//					the color values.  To use a kPMAlphaUnassociated alpha as a transparency mask, set the
											//					kPMTagTransparencyMask tag to the zero based index of the alpha to use. Note: Currently, InDesign 2.0
											//					only supports an index of 0 but in the future we will allow the client to specify any channel and we
											//					will automatically un-pre-multiply any existing Associated alpha channel if necessary.
		kPMTagChannelNameArray		= 135,	//	TYPE: array		names associated with the channels in the kPMTagChannelTypeArray tag. Each name is null terminated.
											//					If there is no name (i.e. for kPMAlphaAssociated alpha channel), there will only be a null to
											//					represent the name. 
		kPMTagEPSProxySource		= 136,	//	TYPE: uint32	This tag is only present in the proxy image for an EPS. The tag value tells us if the proxy
											//					was created from a PICT preview, TIFF preview or from rendering the PostScript.  PICT based proxies
											//					are the least trust worthy because they do not usually have transparency data.
		kPMTagHavePSDComposite		= 137,	//	TYPE: uint8		Non-zero value indicates that we have a PSD image which was saved from Photoshop with
											//					Maximize Backwards Compatibility turned on.
		kPMAttributesAreSynthetic	= 138,	//	TYPE: uint8		Non-zero value indicates that attributes are synthetic and not based on actual image attributes
											//					This will be true if image is a temporary created by scripting code and import is still pending
		kPMTagHaveICCProfileData	= 139,	//	TYPE: uint8		Large profiles end up getting deleted from the IImageAttributes to avoid bloat.  Therefore, to
											//					get the profile data, we have to re-read the IImageAttributes from the linked image.  To avoid
											//					unnecessary disk access, this tag can be used as a cache to indicate whether or not there is
											//					an embedded profile.  If the tag does not exist, then we do not know if the profile exists or not.
		kPMTagImageAttributeRev		= 140,	//	TYPE: uint32	This tag holds the revision of the filter when the attributes were initialized via GetImageAttributes.
											//					It is in the form 0xAAAABBBB where AAAA = filter major version, BBBB = filter minor version.
		kPMTagMetaDataRotation		= 141,	//	TYPE: int16		This holds the angle that was read out of the meta data tiff:orientation tag, so we can undo the
											//					rotation when the image is replaced.
		kPMTagJPEG_EXIF_Resolution	= 142,	//	TYPE: UFixed32	Same as kPMTagXResolution except that this resolution value came from the EXIF structure of a JPEG (camera raw) image.
		kPMTagPrivate_Thumbnail		= 143,	//	TYPE: array		Private.
		kPMTagOrientation			= 144	//	TYPE: int16		Corresponds to TIFF tag #274
	};

	enum { 
		kFirstImageAttributeTag = kPMTagImageWidth, 
		kLastImageAttributeTag  = kPMTagEPSProxySource			// Any tag greater than this value will require an ImageTagTypes passed to SetTag
	};

	/** EPS Proxy Source enumeration
	*/
	enum
	{
		kEPSPICTProxy = 0,	// The proxy was generated from a PICT preview
		kEPSTIFFProxy = 1,	// The proxy was generated from a TIFF preview
		kEPSPSProxy = 2		// The proxy was generated by rendering the PostScript into a raster port
	};

	/** Tag default values
	*/
	enum {
		kPMPlanarDefault			= kPMChunky
	};

	/** Some clarifications:
		
		ChannelsPerPixel
		ChannelsPerPixel is equal to the number of extra channels plus either 1 for indexed images or the number of color
		samples for non-indexed images.  For example, an indexed CMYK image with 1 extra channel would return 2 as the
		number of channels, whereas a normal CMYK image with 1 extra channel would return 5.
	*/

	/** Get the size in bytes of the tag tagID.  If GetSize returns
		0 the tag does not exist.
	*/
	virtual uint32 GetTagSize (uint32 tagID) const = 0;
	
	/** Get the tag associated with tagID and copy it into imageTagData
		Returns a pointer to the actual data if it exists.
		If the tag doesn't exists or GetTag fails for any reason
		it will return nil.
	*/
	virtual const char* GetTag (uint32 tagID, void* imageTagData) const = 0;
	
	/** Get the datatype of the tag tagID.
	*/
	virtual ImageTagTypes GetTagType (uint32 tagID) const = 0;

	/** Add a tag to the image.  If a tag with the same ID already
		exists then the new imageTag will replace it.
		imageTagSize is the total number of bytes, not the number of elements.  
	*/
	virtual bool16 SetTag (uint32 tagID, uint32 imageTagSize, const void* imageTagData, ImageTagTypes type = kPMTagDefault) = 0;
	
	/** Deletes the tag associated with tagID.  DeleteTag returns 
		kTrue if it successfully deleted the tag or if the tag 
		didn't exist to begin with.  
	*/
	virtual bool16 DeleteTag (uint32 tagID) = 0;
	
	/** If the tag is part of the image attributes then TagExists returns
		kTrue.
	*/
	virtual bool16 TagExists (uint32 tagID) const = 0;
	
	/** Copies all of the tags to this from copy
	*/
	virtual bool16 CopyTags (const IImageAttributes* copy) = 0;
	
	
	/** These last five routines provide a means to iterate
		over every tag in the attribute list 
	*/
	virtual uint32 GetTagCount() const = 0;
	
	/** GetNthTagSize
	*/
	virtual uint32 GetNthTagSize (uint32 n) const = 0;
	
	/** GetNthTagID
		Get the ID associated with the nth tag.
	*/
	virtual uint32 GetNthTagID (uint32 n) const = 0;
	
	/** GetNthTagType
		Get the data type of the nth tag.
	*/
	virtual ImageTagTypes GetNthTagType (uint32 n) const = 0;

	/** GetNthTag
		This returns the actual tag data pointer, NOT a copy!
	*/
	virtual const char* GetNthTag (uint32 n) const = 0;

	/** Create or get the UIDList of color swatch UIDs that
		are used by the image (i.e. PSD or TIFF). If get returns 
		nil, there aren't any
	*/
	virtual const UIDList* CreateUsedColorUIDList(const UIDList* pUIDList) = 0;
	virtual const UIDList* GetUsedColorUIDList() const = 0;

};

#endif
