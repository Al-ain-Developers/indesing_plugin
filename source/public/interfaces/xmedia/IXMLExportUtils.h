//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLExportUtils.h $
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
#ifndef __IXMLExportUtils__
#define __IXMLExportUtils__

#include "IPMUnknown.h"
#include "IXMLExportOptions.h"
#include "TransformTypes.h"

class IPMStream;
class XMLReference;
class IXMLExportOptions;
class IXMLOutStream;
class PMString;
class ILinkObject;
class ILinkResource;

typedef void* ExportSessionToken;

/** Export related utility interface; used by the current XML export provider.
*/
class IXMLExportUtils : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_IXMLEXPORTUTILS};

	/**	ExportImageOption are required as a parameter in GetDestinationImageName()
	 */
	enum	ExportImageOption 
	{
		/**	Copies the original image. See CopyOriginal().
		 */
		kCopyOriginal, 
		/**	Optimizes the image. See OptimizeOriginal().
		 */
		kOptimizeOriginal, 
		/**	Generates a formatted image. See FormatOriginal().
		 */
		kFormatOriginal
	};


	/**	Creates an RGB version of the image at a resolution equal to the smaller of 72 dpi and the native image resolution.
		Geometrical transformations, clipping, and any containing frames will not be included in the resulting image.
		@param pageItem specifies page item to be rasterised
		@param outStream where to write the pixels
		@param options  interface (IXMLExportOptions) storing options for the image generation process
		@return ErrorCode kSuccess if operation completed successfully, kFailure otherwise
		@param desiredWidth [IN] if non-zero and less than or equal to the original image width, resample the image uniformly such that its target width matches this given width.		
	 */
	virtual ErrorCode GenerateOptimizedImage(const IPMUnknown *pageItem, IPMStream *outStream, const IXMLExportOptions* options, const PMReal& desiredWidth = 0) = 0;
	
	/**	Creates an RGB snapshot of the pageItem as it appears in the pub.  That is, if the pageItem is rotated in the pub, then
		an image will be generated containing the rotated pageItem.  In addition, if the pageitem has a containing frame,
		the frame will also be part of the image thus preserving clipping.

		@param pageItem specifies page item to be rasterised
		@param outStream where to write the pixels
		@param options  interface (IXMLExportOptions) storing options for the image generation process
		@return ErrorCode kSuccess if operation completed successfully, kFailure otherwise
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
		@param bItemBackgroundExportAsPng[IN] used to explicitly set PNG as export format
		@param bDrawNonPrintingObjects[IN] used to explicitly draw non-printing objects
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling is less than the greek below value. 
	 */
	virtual ErrorCode GenerateFormattedImage(const IPMUnknown *pageItem, IPMStream *outStream, const IXMLExportOptions* options, bool32 includeFrameInRendering = kTrue,bool16 bItemBackgroundExportAsPng = kFalse, bool16 bDrawNonPrintingObjects = kTrue, PMReal greekBelowPtSize = 0.0) = 0;	

	/**	The user has a choice at export time of selecting GIF, JPEG or Automatic as the image type.
		GetBestOptimizedImageType() can be used to detect which type will be used when exporting an
		optimized image of the given pageItem.
		@param pageItem specifies page item to be rasterised
		@return IXMLExportOptions::ImageType indicating a calculated best type for this image
	 */
	virtual IXMLExportOptions::ImageType GetBestOptimizedImageType(const IPMUnknown *pageItem) const = 0;

	/**	The user has a choice at export time of selecting GIF, JPEG or Automatic as the image type.
		GetBestFormattedImageType() can be used to detect which type will be used when exporting a
		formatted image of the given pageItem.
		@param pageItem specifies page item to be rasterised
		@param isPublishedOnline specifies if export is publish online
		@return IXMLExportOptions::ImageType calculated to be most appropriate for this given page item
	 */
	virtual IXMLExportOptions::ImageType GetBestFormattedImageType(const IPMUnknown *pageItem, bool16 isPublishedOnline = kFalse) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option copies the original image. Managed source images are supported. 
		@param stream specifies the XML output stream with IID_XMLCOPYMAP, which is being used to avoid copying images twice.
		@param imagesFolder specifies the target folder where the original image will be copied to
		@param iLinkObject specifies the pageitem of the original image.
		@param sessionToken identifies the export session that owns the resulting file
		@param linkName specifies the name of the link in links panel
	 */
	virtual void CopyOriginal(IXMLOutStream *stream, const IDFile& imagesFolder, ILinkObject* iLinkObject, ExportSessionToken sessionToken, const PMString* linkName = nil) const = 0;

	/**	Given the original image file, copies it to imagesFolder. Managed source images are supported. 
		@param stream specifies the XML output stream with IID_XMLCOPYMAP, which is being used to avoid copying the same image twice.
		@param imagesFolder specifies the target folder where the original image will be copied to
		@param sourceFile specifies the original image.
		@param sessionToken identifies the export session that owns the resulting file
	 */
	virtual void CopyOriginal(IXMLOutStream *stream, const IDFile& imagesFolder, const IDFile& sourceFile, ExportSessionToken sessionToken) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option uses image conversion for optimizing images. 
		It uses GenerateOptimizedImage() and GetBestOptimizedImageType().
		@param stream specifies the XML output stream with IID_XMLOPTIMIZEDMAP, which is being used to avoid converting the same image twice.
		@param exportOptions provides the chosen image type for the image conversion. See IXMLExportOptions::GetImageType().
		@param imagesFolder specifies the target folder where the original image will be copied to.
		@param iLinkObject specifies the pageitem of the original image.
		@param sessionToken identifies the export session that owns the resulting file
		@param desiredWidth [IN] if non-zero and less than or equal to the original image width, resample the image uniformly such that its target width matches this given width.
	 */
	virtual void OptimizeOriginal(IXMLOutStream *stream, IXMLExportOptions* exportOptions, const IDFile& imagesFolder, ILinkObject* iLinkObject, ExportSessionToken sessionToken, const PMReal& desiredWidth = 0) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option generates a new image based on the formatting and transformation that is being used. This util method is currently used by XMLExportProvider and PackageDoc4GLCmd.
		It uses GenerateOptimizedImage() and GetBestOptimizedImageType().		
		@param stream specifies the XML output stream with IID_IXMLFORMATTEDMAPDATA, which is being used to retrieve the converted file name. 
		An image is always converted because the transformation may be different from image to image.
		@param exportOptions provides the chosen image type for the image conversion. See IXMLExportOptions::GetImageType().
		@param imagesFolder specifies the target folder where the original image will be copied to.
		@param iLinkObject specifies the pageitem of the original image.
		@param element specifies XMLReference that will be updated with the URL of the new formatted image. 
		@param sessionToken identifies the export session that owns the resulting file
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
	 */
	virtual void FormatOriginal(IXMLOutStream *stream, 
								IXMLExportOptions* exportOptions, 
								const IDFile& imagesFolder, 
								ILinkObject* iLinkObject, 
								const XMLReference *element, 
								ExportSessionToken sessionToken,
								bool32 includeFrameInRendering = kTrue) const = 0;

	/** Returns true if the pageitem or any of its ancestors has transparency applied to it.
		@param pageItem [IN] pointer to an interface on a page item.
	 */
	virtual bool16 HasTransparency(const IPMUnknown *pageItem) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option generates the file name of the destination image based on export image option (copy, optimized, or formatted).
		@param exportImageOption specifies whether the destination name should be generated for CopyOriginal(), OptimizeOriginal, or  FormatOriginal().
		@param exportOptions provides the chosen image type for the image conversion. See IXMLExportOptions::GetImageType().
		@param iLinkObject specifies the pageitem of the original image.
		@param overwriteDestination specifies whether the destination file can be overwritten or whether a file with a unique name should be used instead. Defaulted to kFalse.
		@return file name string of the destination image or empty string on errors.
	 */
	virtual PMString GetDestinationImageName( ExportImageOption exportImageOption, const IDFile& imagesFolder, ILinkObject* iLinkObject, const IXMLExportOptions* exportOptions, bool16 overwriteDestination = kFalse ) const = 0;
		
	/**	WriteDocumentHeader used to be XMLExportProvider::ExportDocumentHeader(). It takes IXMLExportOptions and a rootName and generates a document header using 
		IXMLExportOptions's GetDTD(), GetFPI(), GetStyleSheet(), and GetComments().
		@param xmlStream is the stream the document header will be written out to.
		@param exportOptions provides GetDTD(), GetFPI(), GetStyleSheet(), and GetComments() for the document header.
		@param rootName is being used for root name of the root element (e.g. article) for IXMLOutStream::DocType.
	 */
	virtual void WriteDocumentHeader(IXMLOutStream *xmlStream, IXMLExportOptions* exportOptions, const PMString& rootName) const = 0;

	/**	OpenFileInApp calls private OpenFileInHelper() in LaunchXMLViewer.cpp. It launches the application specified in appFile and passes the fileURL 
		als parameter for the file or site to open.
		@param appFile browser or any other application.
		@param fileURL specifies the URL that appFile should open.
	 */
	virtual void OpenFileInApp( const IDFile& appFile, const PMString& fileURL ) const = 0;	
	
	/** Does this image, and its parent frame, need to be rasterized due to a 2D transform, transparency,
		clipping paths or a frame that in some way clips the image.
		@param imageItem [IN] pointer to an interface on the image
		@param checkForRotationOrSkew [IN] Should we check for a rotation or skew relative to the spread?
		@param checkForTransparency [IN] Should we check for transparency anywhere in this image's hierarchy?
		@param checkForImageClipping [IN] Should we check for a clipping path on the image?
		@param checkForFrameCropping [IN] Should we check for the frame cropping the image in some way?
		@param checkForVectorGraphic [IN] Should we check whether this image is actually a vector graphic such as an EPS or PDF?
	 */
	virtual bool32 NeedsRasterizationOrSVG(const IPMUnknown *imageItem,
										   bool32 checkForRotationOrSkew = kTrue, 
										   bool32 checkForTransparency = kTrue,
										   bool32 checkForImageClipping = kTrue,
										   bool32 checkForFrameCropping = kTrue,
										   bool32 checkForVectorGraphic = kTrue) const = 0;
	/** Does this graphic is a SVG?
		@param imageItem [IN] pointer to an interface on the image or graphic
	*/
	virtual bool16 isSVGItem(const IPMUnknown *imageItem) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option uses image conversion for optimizing images. 
		It uses GenerateOptimizedImage() and GetBestOptimizedImageType().
		@param stream specifies the XML output stream with IID_XMLOPTIMIZEDMAP, which is being used to avoid converting the same image twice.
		@param exportOptions provides the chosen image type for the image conversion. See IXMLExportOptions::GetImageType().
		@param imagesFolder specifies the target folder where the original image will be copied to.
		@param iLinkObject specifies the pageitem of the original image.
		@param sessionToken identifies the export session that owns the resulting file
		@param useOriginalImageNameOnly [IN] whether to add any prefix or suffix to original image name (eg "_opt").
		@param desiredWidth [IN] if non-zero and less than or equal to the original image width, resample the image uniformly such that its target width matches this given width.
		
	 */
	virtual void OptimizeOriginal2(IXMLOutStream *stream, IXMLExportOptions* exportOptions, const IDFile& imagesFolder, bool32 useOriginalImageNameOnly, ILinkObject* iLinkObject, ExportSessionToken sessionToken, const PMReal& desiredWidth = 0) const = 0;

	/**	There are three graphics related XML export options (Copy Original, Optimize Original, and FormatOriginal). 
		This option generates a new image based on the formatting and transformation that is being used. This util method is currently used by XMLExportProvider and PackageDoc4GLCmd.
		It uses GenerateOptimizedImage() and GetBestOptimizedImageType().		
		@param stream specifies the XML output stream with IID_IXMLFORMATTEDMAPDATA, which is being used to retrieve the converted file name. 
		An image is always converted because the transformation may be different from image to image.
		@param exportOptions provides the chosen image type for the image conversion. See IXMLExportOptions::GetImageType().
		@param imagesFolder specifies the target folder where the original image will be copied to.
		@param iLinkObject specifies the pageitem of the original image.
		@param element specifies XMLReference that will be updated with the URL of the new formatted image. 
		@param sessionToken identifies the export session that owns the resulting file
		@param useOriginalImageNameOnly [IN] whether to add any prefix or suffix to original image name (eg "_fmt").
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
		
	 */
	virtual void FormatOriginal2(IXMLOutStream *stream, 
								IXMLExportOptions* exportOptions, 
								const IDFile& imagesFolder, 
								bool32 useOriginalImageNameOnly,
								ILinkObject* iLinkObject, 
								const XMLReference *element, 
								ExportSessionToken sessionToken,								
								bool32 includeFrameInRendering = kTrue
								) const = 0;

	/**	Creates an RGB snapshot of the pageItem as it appears in the pub.  That is, if the pageItem is rotated in the pub, then
		an image will be generated containing the rotated pageItem.  In addition, if the pageitem has a containing frame,
		the frame will also be part of the image thus preserving clipping.

		@param pageItem specifies page item to be rasterised
		@param outStream where to write the pixels
		@param options  interface (IXMLExportOptions) storing options for the image generation process
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
		@param bItemBackgroundExportAsPng[IN] used to explicitly set PNG as export format
		@param excludeText[IN] determines whether to exclude text in the exported image 
		@return ErrorCode kSuccess if operation completed successfully, kFailure otherwise
	 */

	virtual ErrorCode GenerateFormattedImageForText(const IPMUnknown *pageItem, 
											IPMStream *outStream, 
											const IXMLExportOptions* options, 
											bool32 includeFrameInRendering = kTrue,
											bool16 bItemBackgroundExportAsPng = kTrue,   // by default export as PNG
											bool16 excludeText = kFalse
											) = 0;	

	
	/** Get the bounds around what will actually print. This includes the stroke bounds
		plus whatever adornments are set to print and also the optical alignment margins.
		Compute the bounds in pasteboard coords and then
		transform by theMatrix.

		@param theMatrix the matrix to transform the bounds based on pasteboard coordinates.
		@param includeAdornments [IN] Whether or not printing adornments are included in the resulting bounding box
		@return PMRect the bounds for printing. 
	*/
	virtual PMRect GetPrintedBBoxForTextFrame(const UIDRef &textFrameRef, const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace /*= Transform::PasteboardCoordinates()*/, bool32 includeAdornments = kTrue) = 0;

	/**	Creates an RGB snapshot of the pageItem as it appears in the pub.  That is, if the pageItem is rotated in the pub, then
	an image will be generated containing the rotated pageItem.  In addition, if the pageitem has a containing frame,
	the frame will also be part of the image thus preserving clipping.

		@param pageItem specifies page item to be rasterised
		@param outStream where to write the pixels
		@param options  interface (IXMLExportOptions) storing options for the image generation process
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
		@param bItemBackgroundExportAsPng[IN] used to explicitly set PNG as export format
		@param bDrawNonPrintingObjects[IN] used to explicitly draw non-printing objects
		@param greekBelowPtSize - IN - Point size at which text will be greeked if its points size multiplied by the scaling is less than the greek below value.
		@param includeOtherBackgroundObjects - IN - determines whether page items behind input page item is included in the generated raster.
		@return ErrorCode kSuccess if operation completed successfully, kFailure otherwise
	*/
	virtual ErrorCode GenerateFormattedImage2(const IPMUnknown *pageItem, IPMStream *outStream, const IXMLExportOptions* options, bool32 includeFrameInRendering = kTrue, bool16 bItemBackgroundExportAsPng = kFalse, bool16 bDrawNonPrintingObjects = kTrue, PMReal greekBelowPtSize = 0.0, bool16 includeOtherBackgroundObjects = kFalse) = 0;

	/**	Creates an RGB snapshot of the pageItem as it appears in the pub.  That is, if the pageItem is rotated in the pub, then
	an image will be generated containing the rotated pageItem.  In addition, if the pageitem has a containing frame,
	the frame will also be part of the image thus preserving clipping.

		@param pageItem specifies page item to be rasterised
		@param outStream where to write the pixels
		@param options  interface (IXMLExportOptions) storing options for the image generation process
		@param includeFrameInRendering [IN] For graphics, determines whether the parent frame is included in the generated raster.
		@param bItemBackgroundExportAsPng[IN] used to explicitly set PNG as export format
		@param excludeText[IN] determines whether to exclude text in the exported image
		@param includeOtherBackgroundObjects[IN] - determines whether page items behind input page item is included in the generated raster.
		@return ErrorCode kSuccess if operation completed successfully, kFailure otherwise
	*/

	virtual ErrorCode GenerateFormattedImageForText2(const IPMUnknown *pageItem,
		IPMStream *outStream,
		const IXMLExportOptions* options,
		bool32 includeFrameInRendering = kTrue,
		bool16 bItemBackgroundExportAsPng = kTrue,   // by default export as PNG
		bool16 excludeText = kFalse,
		bool16 includeOtherBackgroundObjects = kFalse
		) = 0;

	/**	Given the original image file, copies it to imagesFolder. Managed source images are supported.

		@param stream specifies the XML output stream with IID_XMLCOPYMAP, which is being used to avoid copying the same image twice.
		@param imagesFolder specifies the target folder where the original image will be copied to
		@param linkResource specifies the link resource abstraction over original image.
		@param sessionToken identifies the export session that owns the resulting file
		@param linkName specifies the name of the link in links panel
	*/
	virtual void CopyOriginal(IXMLOutStream *stream, const IDFile& imagesFolder, ILinkResource* iLinkResource, ExportSessionToken sessionToken, const PMString* linkName = nil) const = 0;
};


#endif
