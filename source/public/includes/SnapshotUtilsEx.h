//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SnapshotUtilsEx.h $
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
//  SnapshotUtilsEx draws items into a memory based graphics context creating a bitmap,
//  or "snapshot", that can be exported to a stream in a variety of formats. Drawing
//  is performed internally by SnapshotUtils via the draw manager IDrawMgr.
//  
//  Overloaded constructors assist in the creation of snapshots of:
//  complete spreads, pages and page items or;
//  selected areas of these items.
//  
//  The constructors allow the caller to control the scale of the snapshot, the amount
//  of bleed, whether a grayscale, RGB, CMYK or Lab bitmap is
//  made and whether an alpha channel for pixel transparency should be generated.
//  
//  After construction of a SnapshotUtilsEx, it is necessary to call Draw() with
//  the desired draw options, including draw quality, anti-aliasing, transparency quality,
//  text greeking and draw flags.
//  
//  If Draw() is successful the caller can access the snapshot by exporting it to a stream
//  via the Export methods or accessing it directly via CreateAGMImageAccessor. 
//  If exporting to a stream, the snapshot bitmap is filtered by the image write format 
//  service specified by the caller and written to the stream. A variety of filters are
//  available (e.g. JPEG, TIFF, GIF).
//  
//  Notes:
//  
//  The default resolution of the snapshot bitmap is 72 dpi.
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
//  if (snapshot.Draw()
//  snapshot.ExportImageToJPEG(stream);
//  
//========================================================================================

#pragma once
#ifndef __SnapshotUtilsEx_h__
#define __SnapshotUtilsEx_h__

class IPMStream;
class IDataBase;

#include "IShape.h"
#include "AGMGraphicsContext.h"
#include "AGMImageAccessor.h"
#include "SnapshotUtils.h"
#include <map>

class SnapshotUtilsExImpl;
class IdleTimer;

//VPAttrMap is a map of view port attribute class IDs and values corresponding to them
typedef std::map<ClassID, PMReal> VPAttrMap;

/** SnapshotUtilsEx is a utility class of routines designed to create an offscreen of a pageitem, page or spread
	and export it as a JPEG, GIF or TIFF.  The client has options for colorspace, whether or not
	to include a transparency alpha, and options for bleed, image quality, and scaling. 
*/
class PUBLIC_DECL SnapshotUtilsEx
{
public:
	/** ColorSpace options
	*/
	typedef enum {
		kCsGray,
		kCsRGB,
		kCsCMYK,
		kCsLab
	} SSColorSpaceFamily;

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
		@param colorSpace  - IN - The colorspace of the snapshot.
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param simulateOverprint  - IN - kTrue to simulate overprint, ie the equivalent of turning 
			on overprint preview. Uses more memory and somewhat slower.
	 */
	SnapshotUtilsEx
	(
		const UIDRef& itemUIDRef, 
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0,
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0,
		const PMReal& bleedAmount = 0.0,
		SSColorSpaceFamily colorSpace = kCsRGB,
		bool8 addTransparencyAlpha = kFalse,
		bool8 simulateOverprint = kFalse
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
		@param colorSpace  - IN - The colorspace of the snapshot.
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param simulateOverprint  - IN - kTrue to simulate overprint, ie the equivalent of turning 
			on overprint preview. Uses more memory and somewhat slower.
	 */
	SnapshotUtilsEx
	(
		const PMRect& clippingBounds,	
		const PMMatrix& boundsToSpreadMatrix,	
		const UIDRef& itemUIDRef, 		
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0,
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0,
		const PMReal& bleedAmount = 0.0,	
		SSColorSpaceFamily colorSpace = kCsRGB,
		bool8 addTransparencyAlpha = kFalse,
		bool8 simulateOverprint = kFalse
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
		@param colorSpace  - IN - The colorspace of the snapshot.
		@param addTransparencyAlpha  - IN - kTrue to store transparency as an alpha channel, kFalse no alpha channel
			The alpha is a mask which identifies the non-transparent portions
			of the snapshot area -- that is, the areas where page items are not.
			This alpha is usefull if for example this snapshot is to be used as a TIFF
			preview for an EPS.  If you were to place the resulting EPS into InDesign, or
			even QuarkXPress, the transparent areas would be preserved when drawing in
			Proxy mode.
		@param simulateOverprint  - IN - kTrue to simulate overprint, ie the equivalent of turning 
			on overprint preview. Uses more memory and somewhat slower.
	 */
	SnapshotUtilsEx
	(
		const PMRect& clippingBounds,		 
		const PMMatrix& boundsToSpreadMatrix,	
		IDataBase* database, 			
		const PMReal& xScaleFactor = 1.0,
		const PMReal& yScaleFactor = 1.0, 
		const PMReal& desiredRes = 72.0,
		const PMReal& minRes = 72.0, 
		const PMReal& bleedAmount = 0.0, 
		SSColorSpaceFamily colorSpace = kCsRGB,
		bool8 addTransparencyAlpha = kFalse,
		bool8 simulateOverprint = kFalse
	);
	
	/**	Destructor.  Destroy the snapshot
		@param none
		@return  
	 */
	virtual ~SnapshotUtilsEx();

	
	/** Construct the bitmap using the arguments passed into the constructor and then draw using
		the drawing arguments passed to this routine.  If a constructor containing a UIDRef was used,
		then the IShape implementation of that UIDRef will be asked to draw its hierarchy.   That is,
		the UIDRef and its children will draw.  If no UIDRef was used, then all page items intersecting
		the clippingBounds will be drawn.

		@param flags - IN - Drawing flags (kPreviewMode suppresses drawing of margins and guides)
		@param fullResolutionGraphics - IN - kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling
			is less than the greek below value.
		@param enableAntiAliasing - IN - kTrue to anti-alias the drawing of all page items.
		@param transparencyQuality - IN - Controls the quality level of transparency effects such as drop shadows,
			feathers, and blending modes.  Use kXPOff to disable transparency effects.
		@param abortCheck - IN - This argument is a callback which will be called before each page item is drawn.
			If you need to abort the generation of this snapshot because too much time has elapsed, there is a
			pending event that you want to handle, or any other reason, then pass in an IdleTimer.  If the call
			to (*abortCheck)() equal zero, then the draw operation will be aborted and an error code of kCancel will
			be returned. @see IIdleTask.h for the definition of IdleTimer.
		@param pVPAttrMap - IN - This argument is a pointer to a map of view port attributes 
			and values corresponding to them. If you want to control the content of the snapshot
			that gets drawn, you can pass a map of various viewport attributes class IDs (like 
			kPrintBaselineGridsVPAttr, kPrintLayersVPAttr, or kXPFlattenerOffVPAttr) and their 
			corresponding values. This function would iterate the various mappings and set the 
			values corresponding to them in the view port attributes of the graphics port, 
			before actually drawing on it.
		@param bDrawNonPrintingObjects - IN - If true, then page items marked as non-printing will draw.
			If false, non-printing page items will be ignored. This setting does not affect non-printing layers.
		@return ErrorCode 
	*/
	ErrorCode Draw(int32 flags = IShape::kPreviewMode,
						bool32 fullResolutionGraphics = kFalse, 	
						const PMReal& greekBelowPtSize = 7.0, 
						bool32 enableAntiAliasing = kTrue,
						SnapshotUtils::Transparencies transparencyQuality = SnapshotUtils::kXPHigh,
						IdleTimer *abortCheck = nil,
						VPAttrMap* pVPAttrMap = nil,
						bool32 bDrawNonPrintingObjects = kTrue
						);
		
	/** Construct the bitmap using the arguments passed into the constructor and then draw using
		the drawing arguments passed to this routine.  Typically, this method is called when the
		constructor WITHOUT a UIDRef is used.

		@param pageItem - IN - the page item to draw.
		@param flags - IN - Drawing flags (kPreviewMode suppresses drawing of margins and guides)
		@param fullResolutionGraphics - IN - kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling
			is less than the greek below value.
		@param enableAntiAliasing - IN - kTrue to anti-alias the drawing of all page items.
		@param transparencyQuality - IN - Controls the quality level of transparency effects such as drop shadows,
			feathers, and blending modes.  Use kXPOff to disable transparency effects.
		@param abortCheck - IN - This argument is a callback which will be called before each page item is drawn.
			If you need to abort the generation of this snapshot because too much time has elapsed, there is a
			pending event that you want to handle, or any other reason, then pass in an IdleTimer.  If the call
			to (*abortCheck)() equal zero, then the draw operation will be aborted and an error code of kCancel will
			be returned. @see IIdleTask.h for the definition of IdleTimer.
		@param pVPAttrMap - IN - This argument is a pointer to a map of view port attributes 
			and values corresponding to them. If you want to control the content of the snapshot
			that gets drawn, you can pass a map of various viewport attributes class IDs (like 
			kPrintBaselineGridsVPAttr, kPrintLayersVPAttr, or kXPFlattenerOffVPAttr) and their 
			corresponding values. This function would iterate the various mappings and set the 
			values corresponding to them in the view port attributes of the graphics port, 
			before actually drawing on it.
		@param bDrawNonPrintingObjects - IN - If true, then page items marked as non-printing will draw.
			If false, non-printing page items will be ignored. This setting does not affect non-printing layers.
		@return ErrorCode 
	*/
	ErrorCode Draw(UID pageItem,
						int32 flags,
						bool32 fullResolutionGraphics, 	
						const PMReal& greekBelowPtSize, 
						bool32 enableAntiAliasing,
						SnapshotUtils::Transparencies transparencyQuality,
						IdleTimer *abortCheck = nil,
						VPAttrMap* pVPAttrMap = nil,
						bool32 bDrawNonPrintingObjects = kTrue
						);

	/** Exports the bitmap to a stream using the given image write format service (these filters are registered
		in the service registry under ServiceID==kImageWriteFormatService).
		USE ExportImageToJPEG, ExportImageToTIFF, ExportImageToPNG or ExportImageToGIF 
		unless you have your own formatClass.

		@param formatClass - IN - ClassID of the export format (e.g. kTIFFImageWriteFormatBoss, kJPEGImageWriteFormatBoss, kGIFImageWriteFormatBoss)
		@param writeStream - OUT - Stream to receive the bitmap data
		@param colorMapped - IN - kTrue to make the resulting image indexed, kFalse otherwise
		@return ErrorCode 
	 */
	ErrorCode ExportImage
	(
		ClassID formatClass,
		IPMStream* writeStream,
		bool8 colorMapped
	);	

	/**	JPEG is very small and depending on the 'quality' setting can be
		very high quality.  But it cannot be indexed and it does not support transparency.

		@param writeStream - OUT - Stream to receive the bitmap data
		@param encoding - IN - JPEG encoding: kSSJPEGProgressive or kSSJPEGBaseline
		@param  quality - IN - kSSJPEGLowQuality, kSSJPEGGoodQuality, kSSJPEGExcellentQuality,	kSSJPEGGreatQuality
		@param embedColorProfile - IN - true to embed the color profile in the JPEG, false to strip it.
		@return ErrorCode 
	 */
	ErrorCode ExportImageToJPEG
	(
		IPMStream* writeStream, 
		SnapshotUtils::SSJPEGEncoding	encoding = SnapshotUtils::kSSJPEGBaseline,
		SnapshotUtils::SSJPEGQuality		quality = SnapshotUtils::kSSJPEGExcellentQuality,
		bool							embedColorProfile = false
	);
	
	/**	Supports transparency
		@param writeStream - OUT - Stream to receive the bitmap data
		@param paletteType - OUT - What kind of color palette do you want
	 @param embedColorProfile - IN - true to embed the color profile in the JPEG, false to strip it.
		@return ErrorCode 
	 */
	ErrorCode ExportImageToTIFF
	(
		IPMStream* writeStream,
		SnapshotUtils::PaletteType paletteType = SnapshotUtils::kNoPalette,
		bool							embedColorProfile = false
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
		SnapshotUtils::PaletteType paletteType = SnapshotUtils::kTryExactThenAdaptivePalette,
		bool8	interlaced = kFalse
	);

	/**	PNG supports transparency.
		@param writeStream - OUT - Stream to receive the bitmap data
		@param compression - IN - Legal values are 0..9. Out of range values are (silently) clipped
			to a valid range.
		@return ErrorCode 
	 */
	ErrorCode ExportImageToPNG
	(
		IPMStream* writeStream, 
		uint32 compression = 5
	);

	/** The AGMGraphicsContext returned from GetGraphicsContext() can be used to obtain the Windows HDC or
		the Mac GrafPtr of the offscreen containing the offscreen bitmap.  Note that this method will return
		nil if the offscreen will not fit into memory.  SnapshotUtilsEx can still successfully create and export
		a snapshot even if it cannot hold the snapshot as an in-memory offscreen by tiling.  That is, SnapshotUtilsEx
		will offscreen the snapshot in tiles and export each tile sequentially.
	*/
	AGMGraphicsContext * GetGraphicsContext(void) const;

	/** CreateAGMImageAccessor returns a pointer to an AGMImageAccessor which can be used to obtain information
		about the actual offscreen bitmap used to create the snapshot.  The caller of this routine is
		responsible for calling 'delete' on the returned AGMImageAccessor.  Note that this method will return nil
		if we are tiling due to not being able to hold an in-memory offscreen for the entire snapshot.
		@see GetGraphicsContext.
	*/
	AGMImageAccessor * CreateAGMImageAccessor(void) const;

	/** CreateAlphaAGMImageAccessor returns a greyscale representation of the transparency alpha generated during
		the snapshot.  If the snapshot was constructed passing False for the 'addTransparencyAlpha' argument,
		then nil will be returned.  If kXPOff is passed for the 'transparencyQuality' argument, then each pixel
		will be either 0 (black) or 255(white).  The caller of this routine is responsible for calling 'delete' 
		on the returned AGMImageAccessor. Note that this method will return nil
		if we are tiling due to not being able to hold an in-memory offscreen for the entire snapshot.
		@see GetGraphicsContext.
	*/
	AGMImageAccessor * CreateAlphaAGMImageAccessor(void) const;

protected:
	SnapshotUtilsExImpl *fImpl;
};

#endif

// End, SnapshotUtilsEx.h
