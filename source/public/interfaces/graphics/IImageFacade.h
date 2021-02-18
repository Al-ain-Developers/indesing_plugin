//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageFacade.h $
//  
//  Owner: David Stephens
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
#ifndef __IImageFacade__
#define __IImageFacade__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "ImageTypes.h"
#include "ImageID.h"
#include "BravoForwardDecl.h"

class IPMStream;

namespace Facade
{
// Please use the IImageFacade directly via the UtilsBoss if possible, see Utils.h:
//		i.e. Utils<Facade::IImageFacade>()->GetImageInfo( ... );
// Or, you can simply include ImageFacade.h (instead of IImageFacade.h) and then use
//		ImageFacade::GetImageInfo( ... );

	/**   A high level API for dealing with images.  Please use the IImageFacade 
		directly via the UtilsBoss if possible, see Utils.h:
		i.e. Utils<IImageFacade>()->GetImageInfo( ... ) ;
		  @author David Stephens
		  @see IImageWrapFacade and IClippingFacade
	   */
	class IImageFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IIMAGEFACADE };

		// ***********************
		// Image Info Routines
		// ***********************

		/**	Get the colorspace, bounds in native coordinates, horizontal resolution, and/or the vertical resolution.
			To convert to InDesign coordinates, you must multiply by 72 and then divide by the image resolution.
			Client may pass nil for any of the arguments.
			@param imageOrProxyBoss IN a pointer to any of the image's interfaces or its 
			proxy's interfaces.
			@param bounds OUT If non-nill, then on return it will contain the native bounds
			of the image.  That is, it will contain the width and height in pixels of the
			native image.  To convert to points, multiply by 72 and divide by the resolution.
			@param colorSpace OUT IF non-nill, then on return it will contain one of
			kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace or kPMICCLabColorSpace.
			@param *xRes OUT If non-nill, on return will contain the horizontal resolution
			of the image as a Fixed.  To convert to decimal, divide by 65536.
			@param *yRes OUT If non-nill, on return will contain the vertical resolution
			of the image as a Fixed.  To convert to decimal, divide by 65536.
			@return ErrorCode 
		 */
		virtual ErrorCode GetImageInfo(const IPMUnknown* imageOrProxyBoss, PMRect* bounds,
			int32* colorSpace, Fixed *xRes, Fixed *yRes) const  = 0;

		/**	Get the colorspace, bounds in native coordinates, horizontal resolution, and/or the vertical resolution.
			To convert to InDesign coordinates, you must multiply by 72 and then divide by the image resolution.
			Client may pass nil for any of the arguments.
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@param bounds OUT If non-nill, then on return it will contain the native bounds
			of the image.  That is, it will contain the width and height in pixels of the
			native image.  To convert to points, multiply by 72 and divide by the resolution.
			@param colorSpace OUT IF non-nill, then on return it will contain one of
			kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace or kPMICCLabColorSpace.
			@param *xRes OUT If non-nill, on return will contain the horizontal resolution
			of the image as a Fixed.  To convert to decimal, divide by 65536.
			@param *yRes OUT If non-nill, on return will contain the vertical resolution
			of the image as a Fixed.  To convert to decimal, divide by 65536.
			@return ErrorCode 
		 */
		virtual ErrorCode GetImageInfo(const UIDRef& imageOrProxyRef, PMRect* bounds,
			int32* colorSpace, Fixed *xRes, Fixed *yRes) const  = 0;

		/**	Get the number of color channels, alpha channels, and spot colors
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@param totalChannels OUT total number of channels
			@param colorChannels OUT total number of color channels (not including spot colors)
			@param transparencyAlphas OUT 0 or 1
			@param spotChannels OUT total number of spot channels
			@param extraChannels OUT total number of extra alphas which are not spot channels and do not describe transparency
			@return ErrorCode 
		 */
		virtual ErrorCode GetChannelInfo(
			const UIDRef& imageOrProxyRef,
			uint32& totalChannels,			// total number of channels
			uint32& colorChannels,			// total number of color channels (not including spot colors)
			uint32& transparencyAlphas,		// 0 or 1
			uint32& spotChannels,			// total number of spot channels
			uint32& otherChannels			// total number of extra alphas which are not spot channels and do not describe transparency
			) const = 0; 

		/**	Get the name of a spot channel
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@param spotIndex IN The zero based index of the spot channel with respect 
			to the first spot channel
			@param name OUT The name of the spot color
			@return ErrorCode 
		 */
		virtual ErrorCode GetSpotChannelName (const UIDRef& imageOrProxyRef,uint32 spotIndex, PMString& name) const = 0;

		/**	Get the name of the Transparency Alpha
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@param name OUT The name of the transparency alpha if it exists.
			@return ErrorCode 
		 */
		virtual ErrorCode GetTransparencyAlphaName (const UIDRef& imageOrProxyRef,PMString& name) const = 0;

		/**	Get the name of one of the extra channels
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@param extraChannelIndex IN The zero based index of the extra channel with respect 
			to the first extra channel
			@param name OUT The name of the transparency alpha if it exists.
			@return ErrorCode 
		 */
		virtual ErrorCode GetExtraChannelName( const UIDRef& imageOrProxyRef, uint32 extraChannelIndex, PMString& name ) const = 0;

		/**	Is the transparency alpha pre-multiplied into the color samples. I.e., is the alpha
			Associated Alpha.
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@return bool16 
		 */
		virtual bool16 IsTransparencyAlphaPreMultiplied( const UIDRef& imageOrProxyRef ) const = 0;

		// GetProxy

		/**	Get the UIDRef of the proxy image
			@param imageBoss IN A pointer to one of the interfaces of the image.
			@return UIDRef of the proxy 
		 */
		virtual const UIDRef GetProxyUIDRef(const IPMUnknown* imageBoss) const = 0;

		/**	Get the UIDRef of the proxy image
			@param imageRef IN The UIDRef of the image
			@return UIDRef of the proxy 
		 */
		virtual const UIDRef GetProxyUIDRef(const UIDRef& imageRef) const = 0;


		/**	Is the image embedded.  I.e., if kTrue, then the link, if present, is not needed.
			@param boss IN A pointer to one of the image's interfaces
			@return bool16 
		 */
		virtual bool16 IsEmbeddedImage(const IPMUnknown* boss) const = 0;
		/**	Is the image embedded.  I.e., if kTrue, then the link, if present, is not needed.
			@param imageRef IN The UIDRef of the image
			@return bool16 
		 */
		virtual bool16 IsEmbeddedImage(const UIDRef& imageRef) const = 0;

		/**	Get a stream to the raw image data of the placed image or its proxy.
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@return IPMStream 
		 */
		virtual IPMStream *GetImageStream(const UIDRef& imageOrProxyRef) const = 0;

		/**	looks in the IImageAttributes of the provided imageRef or proxyRef for the 
			kPMTagICCProfileData tag and converts the data within the tag, if present, 
			to an AGMColorSpace*.
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@return AGMColorSpace*
		 */
		virtual AGMColorSpace *GetAGMColorProfileFromImage(const UIDRef &imageOrProxyRef) const = 0;

		/**	Get the ClassID of the import filter which can read the image.
			@param imageOrProxyRef IN The UIDRef of the image or its proxy image.
			@return ClassID 
		 */
		virtual ClassID GetReadFilterClassID(const UIDRef& imageOrProxyRef) const = 0;


		/**	Get an AddRefed pointer to the ClippingPathFacade.
			@param void 
			@return IClippingFacade* 
		 */
		// virtual IClippingFacade* QueryClippingPathFacade(void) const = 0;
		
		/**	Get an AddRefed pointer to the ImageWrapFacade.
			@param void 
			@return IImageWrapFacade* 
		 */
		// virtual IImageWrapFacade* QueryImageWrapFacade(void) const = 0;
	};
}

#endif	// __IImageFacade__
