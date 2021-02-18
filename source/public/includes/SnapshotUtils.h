//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SnapshotUtils.h $
//  
//  Owner: Seoras Ashby
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
//  SnapshotUtils draws items into a memory based graphics context creating a bitmap,
//  or "snapshot", that can be exported to a stream in a variety of formats. Drawing
//  is performed internally by SnapshotUtils via the draw manager IDrawMgr.
//  
//  Overloaded constructors assist in the creation of snapshots of:
//  complete spreads, pages and page items or;
//  selected areas of these items or;
//  items drawn later by the caller via the Draw() method.
//  
//  The constructors allow the caller to control the scale of the snapshot, the amount
//  of bleed, the drawing flags passed to IDrawMgr, whether graphics and images
//  are rendered in full resolution or by proxy,  whether a grayscale or RGB bitmap is 
//  made and whether an alpha channel for pixel transparency should be generated.
//  
//  After constructing a SnapshotUtils() object the caller must call GetStatus() to 
//  check the snapshot was created successfully.
//  
//  If successful the caller can access the snapshot by exporting it to a stream
//  via the ExportImage() method. The snapshot bitmap is filtered by the image write format 
//  service specified by the caller and written to the stream. A variety of filters are
//  available (e.g. JPEG, TIFF, GIF).
//  
//  Notes:
//  
//  The default resolution of the snapshot bitmap is 72 dpi.
//  
//  The maximum size of bitmap frame buffer allocated by SnapshotUtils is 2MB. 
//  
//  Downsampling will be applied if the area to be drawn could not be rendered at the requested
//  scale within the limits of the frame buffer.
//  
//  GetStatus() will return kFailure if memory could not be allocated for any reason or if
//  the area to be drawn still could not be rendered within the limited size of frame buffer 
//  after downsampling.
//  
//  Sample:
//  
//  void ItemSnapshot(const UIDRef& itemUIDRef, IPMStream* stream)
//  
//  SnapshotUtils snapshot(itemUIDRef);
//  if (snapshot.GetStatus() == kSuccess)
//  snapshot.ExportImage(kJPEGImageWriteFormatBoss, stream);
//  
//========================================================================================

#pragma once
#ifndef __SnapshotUtils_h__
#define __SnapshotUtils_h__

class IPMStream;
class IDataBase;

#include "IShape.h"
#include "AGMGraphicsContext.h"
#include "AGMImageAccessor.h"

class SnapshotUtilsImpl;

/** 
	DEPRECATED
	Please use SnapshotUtilsEx instead.  It is more robust, has more options and will be maintained going
	forward.
	
	SnapshotUtils is a utility class of routines designed to create an offscreen of a pageitem, page or spread
	and export it as a JPEG, GIF or TIFF.  The output colorspace is always RGB or Grayscale.  The client has options
	to include a transparency alpha as well as options for bleed, image quality, and scaling. 
*/
#ifdef ID_DEPRECATED

class PUBLIC_DECL SnapshotUtils
{
public:

	/** SSJPEGEncoding enumeration for specifying which kind of JPEG image to create when
		exporting to JPEG.  Progressive JPEG images create larger file sizes but can be nice
		when used on the Web to obtain the fade in effect.
	*/
	typedef enum	
	{
		kSSJPEGBaseline,
		kSSJPEGProgressive
	} SSJPEGEncoding; 

	/** SSJPEGQuality enumeration for specifying the image quality when exporting to JPEG.  The higher the
		quality, the larger the file size.
	*/
	typedef enum
	{
		kSSJPEGLowQuality,
		kSSJPEGGoodQuality,
		kSSJPEGExcellentQuality,
		kSSJPEGGreatQuality
	} SSJPEGQuality;

	/** PaletteType enumeration when creating an indexed snapshot.
	*/
	typedef enum
	{
		kNoPalette,						// Indicates that the image should not be indexed
		kTryExactThenAdaptivePalette,	// attempts to create an Exact Color Table. If it can't then an Adaptive Palette will be created.
		kMacPalette,					// Use the Macintosh 256 entry system palette from Photoshop
		kWebPalette,					// Use a 216 entry web safe color palette
		kWinPalette						// Use the Windows 256 entry system palette from Photoshop
	} PaletteType;
	
	/** Transparency Quality options.
	*/
	typedef enum
	{
		kXPOff = 0,
		kXPLow,					// Crude approximations of transparency effects, blends honored
		kXPMedium,				// Low quality transparency effects, no page isolation set
		kXPHigh,				// Normal
		kXPMaximum				// Resolution independent transparency effects (may not be implemented)
	} Transparencies;

	/**	Calculates the bounds of the given item and creates a snapshot. This constructor 
		is used to create an image of a complete spread, page or page item. Note that when
		itemUIDRef references a page (kPageBoss) a snapshot is made of the items 
		on the spread that intersect the page bounds.
		@param itemUIDRef - IN - The spread, page or page item to draw
		@param xScaleFactor - IN - X Scale
		@param yScaleFactor - IN - Y Scale
		@param desiredRes  - IN - desired resolution of resulting snapshot
		@param minRes  - IN - minimum resolution of resulting snapshot
		@param bleedAmount  - IN - Extend the bounds of the area to be drawn by the given amount of bleed
		@param flags - IN - Drawing flags (kPreviewMode suppresses drawing of margins and guides)
		@param fullResolutionGraphics - IN - kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
		@param drawGray  - IN - kTrue to draw grayscale, kFalse to draw RGB
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param transparencyQuality - IN - Controls the quality level of transparency effects such as drop shadows,
			feathers, and blending modes.  Use kXPOff to disable transparency effects.
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling
			is less than the greek below value.
		@param antiAliasing - IN - if kTrue, anti aliasing will be turned on for all page items.
		@param overprintPreview - IN - determines whether overprint preview will be in effect.
	 */
	SnapshotUtils
	(
		const UIDRef& itemUIDRef, 
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0,
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0,
		const PMReal& bleedAmount = 0.0,
		int32 flags = IShape::kPreviewMode,
		bool8 fullResolutionGraphics = kFalse,
		bool8 drawGray = kFalse, 
		bool8 addTransparencyAlpha = kFalse,
		Transparencies transparencyQuality = kXPHigh,
		const PMReal& greekBelowPtSize = 7.0,
		bool8 antiAliasing = kTrue,
		bool8 overprintPreview = kFalse
	);
	

	/**	Creates a snapshot of the parts of the given item that intersect the area 
		specified by clippingBounds. This constructor is used to draw part of a 
		spread, page or page item.
		@param clippingBounds - IN - Bounding box in spread co-ordinates of the area to be drawn
		@param itemUIDRef - IN - The spread, page or page item to draw
		@param xScaleFactor - IN - X Scale
		@param yScaleFactor - IN - Y Scale
		@param desiredRes  - IN - desired resolution of resulting snapshot
		@param minRes  - IN - minimum resolution of resulting snapshot
		@param bleedAmount  - IN - Extend the bounds of the area to be drawn by the given amount of bleed
		@param flags - IN - Drawing flags (kPreviewMode suppresses drawing of margins and guides)
		@param fullResolutionGraphics - IN - kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
		@param drawGray  - IN - kTrue to draw grayscale, kFalse to draw RGB
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param transparencyQuality - IN - Controls the quality level of transparency effects such as drop shadows,
			feathers, and blending modes.  Use kXPOff to disable transparency effects.
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling
			is less than the greek below value.
		@param antiAliasing - IN - if kTrue, anti aliasing will be turned on for all page items.
		@param overprintPreview - IN - determines whether overprint preview will be in effect.
	 */
	SnapshotUtils
	(
		const PMRect& clippingBounds,	
		const PMMatrix& boundsToSpreadMatrix,	
		const UIDRef& itemUIDRef, 		
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0,
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0,
		const PMReal& bleedAmount = 0.0,	
		int32 flags = IShape::kPreviewMode,	
		bool8 fullResolutionGraphics = kFalse, 	
		bool8 drawGray = kFalse, 				
		bool8 addTransparencyAlpha = kFalse,
		Transparencies transparencyQuality = kXPHigh,
		const PMReal& greekBelowPtSize = 7.0,
		bool8 antiAliasing = kTrue,
		bool8 overprintPreview = kFalse
	);
	

	/**	Create a graphics context for the area specified by clippingBounds into which items
		from the given database will later be drawn by the caller. Only items that intersect
		the clippingBounds will be drawn.

		@param clippingBounds - IN - Bounding box in spread co-ordinates of the area to be drawn
		@param database - IN - The database containing the items to be drawn
		@param xScaleFactor - IN - X Scale
		@param yScaleFactor - IN - Y Scale
		@param desiredRes  - IN - desired resolution of resulting snapshot
		@param minRes  - IN - minimum resolution of resulting snapshot
		@param bleedAmount  - IN - Extend the bounds of the area to be drawn by the given amount of bleed
		@param flags - IN - Drawing flags (kPreviewMode suppresses drawing of margins and guides)
		@param fullResolutionGraphics - IN - kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
		@param drawGray  - IN - kTrue to draw grayscale, kFalse to draw RGB
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param transparencyQuality - IN - Controls the quality level of transparency effects such as drop shadows,
			feathers, and blending modes.  Use kXPOff to disable transparency effects.
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling
			is less than the greek below value.
		@param antiAliasing - IN - if kTrue, anti aliasing will be turned on for all page items.
		@param overprintPreview - IN - determines whether overprint preview will be in effect.
	 */
	SnapshotUtils
	(
		const PMRect& clippingBounds,		 
		const PMMatrix& boundsToSpreadMatrix,	
		IDataBase* database, 			
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0, 
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0, 
		const PMReal& bleedAmount = 0.0, 
		int32 flags = IShape::kPreviewMode,
		bool8 fullResolutionGraphics = kFalse,
		bool8 drawGray = kFalse, 
		bool8 addTransparencyAlpha = kFalse,
		Transparencies transparencyQuality = kXPHigh,
		const PMReal& greekBelowPtSize = 7.0,
		bool8 antiAliasing = kTrue,
		bool8 overprintPreview = kFalse
	);
	
	/**	Destructor.  Destroy the snapshot
		@param none
		@return  
	 */
	virtual ~SnapshotUtils();

	/**	After constructing a SnapshotUtils() object the caller must call GetStatus() to 
		check the snapshot was created successfully.
		@param none
		@return ErrorCode - kSuccess indicates success.  Any other return indicates failure 
			(At this point the only other status returned is kFailure).	
	 */
	ErrorCode GetStatus() const;
	
	/** Invokes the draw manager (IDrawMgr) to draw the given item into the snapshot.
		@param itemUID 
	 */
	void Draw(const UID& itemUID);
	
	/** Exports the bitmap to a stream using the given image write format service (these filters are registered
		in the service registry under ServiceID==kImageWriteFormatService).
		OBSOLETE:  USE ExportImageToJPEG, ExportImageToTIFF or ExportImageToGIF unless you have your own formatClass.

		@param formatClass - IN - ClassID of the export format (e.g. kTIFFImageWriteFormatBoss, kJPEGImageWriteFormatBoss, kGIFImageWriteFormatBoss)
		@param writeStream - OUT - Stream to receive the bitmap data
		@param colorMapped - IN - kTrue to make the resulting image indexed, kFalse otherwise
		@return ErrorCode 
	 */
	ErrorCode ExportImage
	(
		ClassID formatClass,
		IPMStream* writeStream,
		bool8 colorMapped = kFalse
	);	
		
	/**	JPEG is very small and depending on the 'quality' setting can be
		very high quality.  But it cannot be indexed and it does not support transparency.

		@param writeStream - OUT - Stream to receive the bitmap data
		@param encoding - IN - JPEG encoding: kSSJPEGProgressive or kSSJPEGBaseline
		@param  quality - IN - kSSJPEGLowQuality, kSSJPEGGoodQuality, kSSJPEGExcellentQuality,	kSSJPEGGreatQuality
		@return ErrorCode 
	 */
	ErrorCode ExportImageToJPEG
	(
		IPMStream* writeStream, 
		SSJPEGEncoding	encoding = kSSJPEGBaseline,
		SSJPEGQuality		quality = kSSJPEGExcellentQuality
	);
	
	/**	Supports transparency
		@param writeStream - OUT - Stream to receive the bitmap data
		@param paletteType - OUT - What kind of color palette do you want
		@return ErrorCode 
	 */
	ErrorCode ExportImageToTIFF
	(
		IPMStream* writeStream,
		PaletteType paletteType = kNoPalette
	);

	/**	GIFs support transparency and are always indexed
		@param writeStream - OUT - Stream to receive the bitmap data
		@param paletteType - IN - What kind of color palette do you want
		@param  interlaced - IN - interlacing is usefull when an application needs to fade
			an image in while loading it but in general takes causes
			the reader to take longer to display the image.
		@return ErrorCode 
	 */
	ErrorCode ExportImageToGIF
	(
		IPMStream* writeStream, 
		PaletteType paletteType = kTryExactThenAdaptivePalette,
		bool8	interlaced = kFalse
	);

	/** The AGMGraphicsContext returned from GetGraphicsContext() can be used to obtain the Windows HDC or
		the Mac GrafPtr of the offscreen containing the offscreen bitmap.
	*/
	AGMGraphicsContext * GetGraphicsContext(void) const;

	/** CreateAGMImageAccessor returns a pointer to an AGMImageAccessor which can be used to obtain information
		about the actual offscreen bitmap used to create the snapshot.  The caller of this routine is
		responsible for calling 'delete' on the returned AGMImageAccessor.
	*/
	AGMImageAccessor * CreateAGMImageAccessor(void) const;

	/** CreateAlphaAGMImageAccessor returns a greyscale representation of the transparency alpha generated during
		the snapshot.  If the snapshot was constructed passing False for the 'addTransparencyAlpha' argument,
		then nil will be returned.  If kXPOff is passed for the 'transparencyQuality' argument, then each pixel
		will be either 0 (black) or 255(white).  The caller of this routine is responsible for calling 'delete' 
		on the returned AGMImageAccessor.
	*/
	AGMImageAccessor * CreateAlphaAGMImageAccessor(void) const;

private:
	SnapshotUtilsImpl *fImpl;
};
#endif

#endif

// End, SnapshotUtils.h
