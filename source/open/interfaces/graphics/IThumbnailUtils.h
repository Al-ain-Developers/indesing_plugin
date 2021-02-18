//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/graphics/IThumbnailUtils.h $
//  
//  Owner: lance bushore
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
#ifndef __IThumbnailUtils__
#define __IThumbnailUtils__

// ----- Includes -----
#include "IPMUnknown.h"
#include "ImportExportUIID.h"
#include "Utils.h"

class IImageAttributes;
class IGraphicsPort;
class IPMFont;
class IImageCache;
class AGMImageAccessor;
class IControlView;
class IViewPort;
/**
Utility interface to generate thumbnails
 */
class IThumbnailUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITHUMBNAILUTILS };

		/** main utility for drawing image thumbnail.  This method ignores any page item transforms and graphic attributes
			that have been applied from within InDesign. It generates the thumbnail based on the image proxy.  The resulting
			bitmap will have rowBytes equal to (3 * width).
		*/
		virtual ErrorCode RGBThumbnailFromImageProxy(const UIDRef& graphicPageItemRef, uchar *imageBuffer, uint32* bitmapWidth, uint32* bitmapHeight) = 0;

		/** main utility for drawing text thumbnail */
		virtual ErrorCode RGBThumbnailFromStory(const UIDRef& itemUIDRef, uchar *bitmapBuffer, uint32* bitmapWidth, uint32* bitmapHeight, bool16 *isVerticalText, bool16 drawIcon = kTrue) = 0;

		/** main utility for drawing snippet file thumbnail */
		virtual ErrorCode RGBThumbnailFromSnippet(const UIDRef& descriptorUIDRef, uchar *bitmapBuffer, uint32* bitmapWidth, uint32* bitmapHeight) = 0;

		/** Return an add-referenced thumbnail representation of the link associated with a page item or 
			child link.  If the thumbnail does not exist, then create one by calling RGBThumbnailFromImageProxy and
			cache the result in the ImageCacheMgr.
			@param pageItemOrChildLink [IN]: UIDRef of the page item (ILinkObject) associated with the link or,
			in the case of an OPI link, DCS link or secondary link of a placed InDesign page, the UID of the 'child' link.
			@return An addreferenced pointer to an IImageCache.
			*/		
		virtual IImageCache *QueryThumbnail(const UIDRef& pageItemOrChildLink) = 0;
		
		/** Create a SnapshotUtils based thumbnail of the given page item and add it to the provided iImageAttributes
			as a kPMTagPrivate_Thumbnail tag.
			@param pageItem [IN]: UIDRef of the page item (ILinkObject) associated with the link.  For example,
			if we are trying to get the OPI links of a placed EPS, then pageItem is the UIDRef of the EPS page item.
			@return kSuccess if successful, otherwise an error code.
			*/
		virtual ErrorCode CreateSnapshotThumbnail(const UIDRef& pageItem, IImageAttributes *iImageAttributes) = 0;
		
		/** Utility routine which creates a graphics port around a bitmap, so we can draw to it with AGM
		 @param bitmapBuffer [IN]: pointer to the bitmap buffer to be used. Buffers length is width * height * 4;
		 @param bitmapWidth [IN]: width, in pixels, of the bitmap.
		 @param bitmapHeight [IN]: height, in pixels, of the bitmap.
		 @param hasAlpha [IN]: on input,the cursor to super-impose. On output, the new custom cursor.
		 @param hiRes [IN]: whether the bitmap is at regular or hiRes/retina resolution (2X), in which case the returned IGraphicsPort will be scaled accordingly.
		 @return pointer to an IGraphicsPort interface can be used to draw into the bitmapped buffer.
		 */
		virtual IGraphicsPort* QueryGraphicsPortForBitmap(uchar* bitmapBuffer,uint32 bitmapWidth, uint32 bitmapHeight, bool16 hasAlpha, bool16 hiRes = kFalse) = 0;

		/** helper routines */
		virtual bool DrawPlaceGunCountIntoGraphicsPort(IGraphicsPort * offscreenPort, uint32 bitmapWidth, bool16 isVerticalText) = 0;
		virtual bool DrawCountIntoGraphicsPort(IGraphicsPort * offscreenPort, uint32 bitmapWidth, bool16 isVerticalText, int32 count) = 0;
		

		virtual void DrawImageThumbnail(IGraphicsPort *gPort, IImageCache* imageCache, const PMRect& frame) = 0;
        virtual void DrawAGMImageAccessorThumbnail(IViewPort* viewPort, IControlView* controlView, const SysRgn rgn, const AGMImageAccessor *image, const PMRect& frame, const bool16 drawOutline = kFalse) = 0;
};

#endif 