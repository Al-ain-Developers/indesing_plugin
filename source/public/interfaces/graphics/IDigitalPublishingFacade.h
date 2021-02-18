//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDigitalPublishingFacade.h $
//  
//  Owner: Adobe Systems Inc.
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

#ifndef __IDigitalPublishingFacade_h__
#define __IDigitalPublishingFacade_h__

#include "DigitalPublishingID.h"

#include "IDTime.h"
#include "MiniFolioOptions.h"
#include "Utils.h"

class IDocument;

#include <boost/shared_ptr.hpp>

namespace id_digpub
{

/**
 Forward declare of Object type used by DigitalPublishing dictionaries
 */
class Object;
typedef boost::shared_ptr<Object> ObjectPtr;

}

/**
 Opaque type representing a folio for the API below
 */
class DigitalPublishingFolio;

/**
 Opaque type representing metadata for a folio
 */
class DigitalPublishingMetadata;

typedef IDTime DigitalPublishingDateTime;

/**
 IDigitalPublishingFacade defines the interface for this plug-ins facade.
 A Facade is a functional API layer that sits on top of commands and other 
 complicated model operatoins.  Script providers and selection suites often 
 have to do the same thing.  Putting command and other model specific code 
 into a facade provides code reuse.
 
 @ingroup DigitalPublishing
*/
namespace Facade
{
	class IDigitalPublishingFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IDIGITALPUBLISHINGFACADE };
		
		/**
		 Creates an instance of a metadata object
		 */
		virtual DigitalPublishingMetadata *CreateMetadata() const = 0;
		
		/**
		 Sets the date when the folio was originally created
		 
		 This attribute is required. It is not currently used by the viewer.
		 
		 Note: This attribute is ignored if applied to an article.
		 
		 @param metadata	The target metadata
		 @param date		The date the folio was created
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataDate(DigitalPublishingMetadata *metadata, DigitalPublishingDateTime const &date) const = 0;
		
		/**
		 Sets the date when the folio was last updated
		 
		 This attribute is optional. It is not currently used by the viewer.
		 
		 Note: This attribute is ignored if applied to an article.
		 
		 @param metadata	The target metadata
		 @param date		The date the folio was last updated
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataUpdateDate(DigitalPublishingMetadata *metadata, DigitalPublishingDateTime const &date) const = 0;
				
		/**
		 Sets the folio's number. This, along with the folio's magazine title, 
		 should uniquely identify this folio.
		 
		 This attribute is required. It is displayed by the viewer in the header section.
		 
		 Note: This attribute is ignored if applied to an article.

		 @param metadata	The target metadata
		 @param number		The folio number for the folio, as a string
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataFolioNumber(DigitalPublishingMetadata *metadata, WideString const &number) const = 0;
		
		/**
		 Sets the folio's magazine title
		 
		 This attribute is required. It is displayed by the viewer in the header section.
		 
		 Note: This attribute is ignored if applied to an article.

		 @param metadata	The target metadata
		 @param title		The title of the folio's magazine
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataMagazineTitle(DigitalPublishingMetadata *metadata, WideString const &title) const = 0;
		
		/**
		 Sets the description for a folio or an article
		 
		 This attribute is optional. When applied to an article, it is currently 
		 used by the viewer in the browser view. It is not currently used when
		 applied to a folio.

		 @param metadata	The target metadata
		 @param desc		The folio's description
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataDescription(DigitalPublishingMetadata *metadata, WideString const &desc) const = 0;
		
		/**
		 Sets the category for a folio
		 
		 This attribute is optional. It is not currently used by the viewer.
		 
		 Note: This attribute is ignored if applied to an article.
		 
		 @param metadata	The target metadata
		 @param category	The folio's category
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataCategory(DigitalPublishingMetadata *metadata, WideString const &category) const = 0;

		/**
		 Sets the title for an article
		 
		 This attribute is required. It is used by the viewer in the scrubber, 
		 browser, and table of contents views.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param title		The article's title
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataArticleTitle(DigitalPublishingMetadata *metadata, WideString const &title) const = 0;

		/**
		 Sets the author for an article
		 
		 This attribute is required. It is used by the viewer in the scrubber 
		 and browser views.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param author		The article's author
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataArticleAuthor(DigitalPublishingMetadata *metadata, WideString const &author) const = 0;

		/**
		 Sets the "kicker" for an article. This is a short descriptive phrase
		 or callout.
		 
		 This attribute is optional. If included, it is used by the viewer in 
		 the scrubber, browser, and table of contents views.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param kicker		The article's kicker
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataArticleKicker(DigitalPublishingMetadata *metadata, WideString const &kicker) const = 0;

		/**
		 Sets whether an article is an advertisement
		 
		 This attribute is optional. It is used by the viewer to determine if the
		 article is an advertisement. The default is false.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param isAd		Boolean value indicating whether article is an advertisement
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataArticleIsAdvertisement(DigitalPublishingMetadata *metadata, bool16 isAd) const = 0;

		/**
		 Sets whether an article should be hidden from the Table of Contents (TOC)
		 
		 This attribute is optional. It is used by the viewer to determine whether
		 an article should be shown in the table of contents or not. The default is false.
		 If the attribute is not provided, but the IsAdvertisement attribute is provided
		 and is true, the article will not be shown in the TOC.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param hideFromTOC	Boolean value indicating whether article should be hidden from the TOC
		 @return kSuccess if successful, otherwise an error code
		 */
		static inline ErrorCode SetMetadataArticleHideFromTOC(DigitalPublishingMetadata *metadata, bool16 hideFromTOC)
		{
			Utils<Facade::IDigitalPublishingFacade> dpFacade;
			ASSERT(dpFacade);

			return dpFacade->AddMetadataKeyValue(	metadata,
													WideString("hideFromTOC"),
													WideString(hideFromTOC ? "true" : "false")
												);
		}

		/**
		 Set the intent for the article.
		 
		 This attribute is optional. It is used by the viewer to navigate to a specific article.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param intent		WideString string designating the article's intent
		 @return kSuccess if successful, otherwise an error code
		 */
		static inline ErrorCode SetMetadataArticleIntent(DigitalPublishingMetadata *metadata, WideString const &intent)
		{
			Utils<Facade::IDigitalPublishingFacade> dpFacade;
			ASSERT(dpFacade);

			return dpFacade->AddMetadataKeyValue(	metadata,
													WideString("intent"),
													intent
												);
		}

		/**
		 Set the section for the article.
		 
		 This attribute is optional. It is used to define the section the article belongs to.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param section		WideString string designating the article's section
		 @return kSuccess if successful, otherwise an error code
		 */
		static inline ErrorCode SetMetadataArticleSection(DigitalPublishingMetadata *metadata, WideString const &section)
		{
			Utils<Facade::IDigitalPublishingFacade> dpFacade;
			ASSERT(dpFacade);

			return dpFacade->AddMetadataKeyValue(	metadata,
													WideString("section"),
													section
												);
		}

		/**
		 Sets whether or not article content is trusted.
		 
		 This attribute is optional. It is used to allow access to V1 Library JSAPI.
		 This attribute is relevant only for HTML stack type.
		 
		 @param metadata			The target metadata
		 @param isTrustedContent	Boolean value indicating whether an HTML article content should be trusted. 
		 @return kSuccess if successful, otherwise an error code
		 */
		static inline ErrorCode SetMetadataArticleIsTrustedContent(DigitalPublishingMetadata *metadata, bool16 isTrustedContent)
		{
			Utils<Facade::IDigitalPublishingFacade> dpFacade;
			ASSERT(dpFacade);

			return dpFacade->AddMetadataKeyValue(	metadata,
													WideString("isTrustedContent"),
													WideString(isTrustedContent ? "true" : "false")
												);
		}

		/**
		 Sets the tags for an article. These are short textual items that can be used to 
		 informally classify an article.
		 
		 This attribute is optional. If included, it is used by the viewer in the scrubber 
		 and browser views.
		 
		 Note: This attribute is ignored if applied to a folio.
		 
		 @param metadata	The target metadata
		 @param title		The article's title
		 @return kSuccess if successful, otherwise an error code
		 */
		virtual ErrorCode SetMetadataArticleTags(DigitalPublishingMetadata *metadata, K2Vector<WideString> const &tags) const = 0;
		
		/**
		 Sets an arbitrary metadata item. All values must be encoded as strings.
		 
		 All attributes set through this API are considered optional and are ignored by the
		 viewer application.
		 
		 @param metadata	The target metadata
		 @param key			The key for the metadata item
		 @param value		The key's value
		 */
		virtual ErrorCode AddMetadataKeyValue(
			DigitalPublishingMetadata *metadata,
			WideString const &key,
			WideString const &value
		) const = 0;
		
		/**
		 Gets an arbitrary metadata item. All returned values are encoded as strings.
		 
		 @param metadata	The target metadata
		 @param key			The key to retreive
		 @param value		Out parameter: will contain the value for the key if successful
		 @return kTrue if the specified key's value was successfully retrieved, else kFalse
		 */
		virtual bool16 GetMetadataValueForKey(
			DigitalPublishingMetadata *metadata,
			WideString const &key,
			WideString &value
		) const = 0;
		
		/**
		 Disposes of a metadata instance.
		 
		 @param metadata	The metadata to be disposed of
		 */
		virtual void DisposeMetadata(DigitalPublishingMetadata *metadata) const = 0;
		
		/**
		 Creates a 'mini' folio for a pair of InDesign documents, using the specified options
		 
		 @param portrait The document representing the folio's portrait orientation
		 @param landscape The document representing the folio's landscape orientation
		 @param options The options to use while creating the folio file
		 @param folioFile The location in which to create the folio file
		 
		 @param return an ErrorCode describing the status of the call
		 */
		virtual ErrorCode CreateMiniFolio(
			IDocument const *portrait, 
			IDocument const *landscape,
			MiniFolioOptions const &options,
			DigitalPublishingMetadata const *metadata,
			IDFile const &folioFile
		) const = 0;
		
		/**
		 Creates a new folio instance. The returned instance is owned by the caller
		 and must be deleted by a call to DisposeFolio
		 
		 @return a new DigitalPublishingFolio instance, or nil if an error occurs
		 */
		virtual DigitalPublishingFolio *CreateFolio() const = 0;
		
		/**
		 Sets the metadata for a folio
		 
		 @param folio The folio to which the metadata should be added
		 @param metadata The metadata to add to the folio

		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode SetFolioMetadata(
			DigitalPublishingFolio *folio, 
			DigitalPublishingMetadata const *metadata
		) const = 0;
		
		/**
		 FolioOrientations
		 */
		enum FolioOrientation
		{
			kOrientationAuto			= 0x0,
			kOrientationPortrait		= 0x1,
			kOrientationLandscape		= 0x2,
			kOrientationBoth			= kOrientationPortrait | kOrientationLandscape,
			
			kInvalidFolioOrientation = 0xffffffff
		};

		/**
		 Sets the orientation for a folio
		 
		 @param folio The folio to which the orientation should be set
		 @param orientation The orientation to set for the folio (defaults to kOrientationBoth)

		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode SetFolioOrientation(
			DigitalPublishingFolio *folio, 
			FolioOrientation orientation = kOrientationBoth
		) const = 0;
		
		/**
		 Sets the target dimensions for a folio. May be called more than once for multiple target
		 sizes, although all mini-folios must support all requested output dimensions.
		 
		 @param folio The folio to which the target dimensions should be set
		 @param wideDimension The wide dimension to set for the folio (larger of the numbers)
		 @param narrowDimension The narrow dimension to set for the folio (smaller of the numbers)

		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode SetFolioTargetDimensions(
			DigitalPublishingFolio *folio, 
			uint32 wideDimension,
			uint32 narrowDimension
		) const = 0;
		
		/**
		 Sets the content stack ID map for a folio
		 
		 @param folio The folio to which the content stack ID map should be set
		 @param contentStackIDMap An ObjectPtr created from CreateEmptyDictionary() filled with
				key/value pairs mapping document names to content stack IDs. This is used when
				fixing up navTo hyperlinks.

		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode SetContentStackIDMap(
			DigitalPublishingFolio *folio, 
			id_digpub::ObjectPtr const &contentStackIDMap
		) const = 0;
		
		/**
		 Adds a directory to a folio to be packaged along with the mini-folios.
		 
		 @param folio The folio being created
		 @param directory The location of the directory to add
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode AddDirectoryToFolio(
			DigitalPublishingFolio *folio, 
			IDFile const &directory
		) const = 0;

		/**
		 FolioBindingDirection -- Right-Edge Binding
		 */
		enum FolioBindingDirection
		{
			kLeftEdgeBinding			= 0x0,
			kRightEdgeBinding			= 0x1
		};
		
		/**
		 FMR Right Edge Binding
		 Sets the binding direction for a folio
		 
		 @param folio The folio to which the binding direciton should be set
		 @param direction The binding direction to set for the folio
		 */
		virtual ErrorCode SetFolioBindingDirection(
			DigitalPublishingFolio *folio,
			FolioBindingDirection direction
		) const = 0;
		
		/**
		 Adds a mini-folio to a folio.
		 
		 @param folio The folio being created
		 @param miniFolio The location of the mini folio to add
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode AddMiniFolioToFolio(
			DigitalPublishingFolio *folio, 
			IDFile const &miniFolio
		) const = 0;
		
		/**
		 Adds a pair of document, assumed to represent a single article in its
		 two orientations, to a folio.
		 
		 @param folio The folio being created
		 @param portrait The document representing the folio's portrait orientation
		 @param landscape The document representing the folio's landscape orientation
		 @param options The options to use while creating the folio file
		 @param metadata The metadata to associate with the article
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode AddDocumentPairToFolio(
			DigitalPublishingFolio *folio, 
			IDocument const *portrait, 
			IDocument const *landscape, 
			MiniFolioOptions const &options,
			DigitalPublishingMetadata const *metadata
		) const = 0;
		
		/**
		 Exports a folio to a single package.
		 
		 @param folio The folio to export
		 @param packageFile The location for the package being exported
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode ExportFolioToPackage(
			DigitalPublishingFolio *folio,
			IDFile const &packageFile
		) const = 0;
		
		/**
		 Exports a flattened folio to a manifest file and a series of mini-folios.
		 
		 @param folio The folio to export
		 @param manifestFile The location for the package being exported
		 @param articleDirectory The location, relative to manifestFile's parent directory, in which the mini-folios are saved
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode ExportFolioToDirectory(
			DigitalPublishingFolio *folio,
			IDFile const &manifestFile,
			IDPath const &articleDirectory
		) const = 0;
		
		/**
		 Exports a folio to a manifest file and a directory structure (i.e. June folio format) package.
		 
		 @param folio The folio to export 
		 @param packageFile The location for the package being exported
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode ExportFolioToDirectoryPackage(
			DigitalPublishingFolio *folio,
			IDFile const &packageFile
		) const = 0;
		
		/**
		 Disposes an instance of a DigitalPublishingFolio created by a call to CreateFolio
		 
		 @param folio The folio to dispose
		 */
		virtual void DisposeFolio(DigitalPublishingFolio *folio) const = 0;

		/**
		 Factory method for creating an instance of an empty dictionary.
		 
		 @return a new instance of an empty dictionary object
		 */
		virtual id_digpub::ObjectPtr CreateEmptyDictionary() const = 0;
		
		/**
		 ObjectFormats
		 */
		enum ObjectFormat
		{
			kXMLObjectFormat,
			kBinaryObjectFormat,
			
			kInvalidObjectFormat = 0xffffffff
		};
		
		/**
		 Writes an object to a stream, assumed to be opened for writing, using the
		 specified format.
		 
		 @param obj			The root object to write
		 @param s			The stream to write to
		 @param format		The format to use
		 @return true if successful
		 */
		virtual bool WriteDigPubObjectToStream(
			id_digpub::ObjectPtr const &obj, 
			IPMStream *s, 
			ObjectFormat format = kBinaryObjectFormat
		) const = 0;
		
		/**
		 Reads an object to a stream, assumed to be opened for reading, using the
		 specified format as a hint. If you know the format used to write the stream
		 originally, you may specify it. If not, use the default value to cause this
		 routine to examine the bytes in the stream to determine what format was used.
		 
		 @param obj			The root object to write
		 @param s			The stream to write to
		 @param format		The format to use
		 @return true if successful
		 */
		virtual bool ReadDigPubObjectFromStream(
			id_digpub::ObjectPtr &obj, 
			IPMStream *s,
			ObjectFormat format = kInvalidObjectFormat
		) const = 0;
	};

	class IDigitalPublishingRasterizerFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IDIGITALPUBLISHINGRASTERIZERFACADE };
		
		/**
		 Calculates the bounding box for a list of UIDs, in spread coordinates, using the
		 same method used internally by RasterizePageitemToStream. This ensures that 
		 bounding boxes can be calculated consistently.
		 
		 @param items		The page items to rasterize
		 @param bounds		Out param to receive the calculated bounds, in spread coordinates
		 */
		virtual void GetBoundingBoxForItemsInSpreadCoords(UIDList const &items, PMRect &bounds) const = 0;
		
		/**
		 Rasterizes the given page items to a specified width and height, scaling contents to 
		 fit, then saves the results to the specified stream.
		 
		 settings is an optional dictionary which may include the following values (case-sensitive):
		 
		 Compression:			string, one of 'png', 'jpeg', or 'auto'. Default is 'auto'
		 Downsampling:			string, one of 'bicubic' or 'antialiased'. Default is 'bicubic'
		 JPEGQuality:			string, one of 'max', 'high', 'med', 'low', 'min'. Default is 'high'
		 RasterizationScale:	real, the scale at which to rasterize. Default is 1.
		 IncludeAlpha:			bool, if true the raster will have an alpha channel. Default is true
		 ClipItems:				bool, if true page items are clipped to their parent's bounds. Default is true
		 FilterToSpread:		bool, if true page items outside the spread bounds are omitted. Default is true
		 ImageResolution:		uint, the resolution at which to rasterize. Must be between 18 and 600. Default is 72
		 
		 explicitBounds can be used to override the default bounding box calculation that would
		 normally be used (the plug-in normally uses GetBoundingBoxForItemsInSpreadCoords to make
		 this determination). It is the caller's responsibility to ensure that the bounding box is
		 correct; the plug-in will not attempt to validate it.
		 
		 @param items			The page items to rasterize
		 @param width			The width of the resulting raster
		 @param height			The height of the resulting raster
		 @param explicitBounds	Optional bounding box for page items, in spread coordinates
		 @param settings		Settings to use during the export
		 @param out				The stream to which the raster is written
		 
		 @return an ErrorCode describing success or failure of the operation
		 */
		virtual ErrorCode RasterizePageitemsToStream(
			UIDList const &items, 
			uint32 width, uint32 height,
			PMRect const *explicitBounds,
			id_digpub::ObjectPtr const &settings,
			IPMStream *out
		) = 0;
	};

	class IDigitalPublishingVectorExportFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IDIGITALPUBLISHINGVECTOREXPORTFACADE };
				
		/**
		 Exports the given page items to a PDF.
		 
		 settings is an optional dictionary which may include the following values (case-sensitive):
		 
		 JPEGQuality:			string, one of 'max', 'high', 'med', 'low', 'min'. Default is 'high'
		 ImageResolution:		uint, the resolution at which to downsample raster images. Must be between 18 and 600. Default is 72
								Note: 'Resolution' is allowed as a fallback key. If both are present, 'ImageResolution' is preferred.
		 Scale:					real, amount by which document should be scaled
		 
		 TileSize:				optional PMPoint with desired tiled size, if any. If omitted, output is not tiled
		 
		 ThumbnailGeneration:	optional dictionary for controlling thumbnail generation. If omitted, no thumbnails are generated.
		 
			ThumbnailScale:		real, specifies scale for thumbnail. A value of 2 would result in a 1/2 size thumbnail. Default is 3
			OutputDirectory:	file, must be a directory. The directory in which to generate thumbnails. Default is a temporary directory
			BaseFileName:		string, specifies base file name for generated thumbnails. Sequence # and extension will be appended.

		 results is an optional dictionary. If included, it will be populated with the following
		 values on successful exit (case-sensitive):
		 
		 Bounds:				PMRect, the bounds for the exported PDF. If tiled, this is the union of the tiles' bounds
		 Tiles:					array of:
			Page:				uint, the 1-based page index in the PDF for this tile
			Bounds:				PMRect, the bounds for the export tile's page
			
		 Tiles array will only be present if tiling is true (i.e., valid TileSize is present in settings)
		 
		 If thumbnail generation is enabled, generated thumbnails will be included in results. When tiling,
		 information about the thumbnails will be included in each tile's dictionary. Otherwise, information
		 about the single thumbnail will be included in the main results dictionary.
		 
		 The information includes:
		 
		 ThumbnailBounds:		PMRect, the bounds for the thumbnail in normalized image coordinates
		 ThumbnailFile:			file, the location of the thumbnail image
		 
		 Note: It is the caller's responsibility to delete any generated thumbnail images and to remove
		 the thumbnail directory if necessary.
		 
		 @param items					The page items to export. The page items will be exported to a single page in the PDF
		 @param pageItemsToSuppress		Page items to be excluded from the export. May be empty.
		 @param settings				Settings to use during the export
		 @param results					Optional dictionary to receive results
		 @param out						The file to which the PDF is written
		 
		 @return an ErrorCode describing success or failure of the operation
		 */
		virtual ErrorCode ExportPageitemsAsPDF(
			UIDList const &items, 
			UIDList const &pageItemsToSuppress,
			id_digpub::ObjectPtr const &settings,
			id_digpub::ObjectPtr *results,
			IDFile const &out
		) = 0;
	};
}

#endif
