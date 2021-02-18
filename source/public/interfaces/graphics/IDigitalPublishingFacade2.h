//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDigitalPublishingFacade2.h $
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

#include "IDigitalPublishingFacade.h"

namespace Facade
{
	class IDigitalPublishingFacade2 : public IDigitalPublishingFacade
	{
	public:
		enum { kDefaultIID = IID_IDIGITALPUBLISHINGFACADE2 };
		
		/**
		 Returns a dictionary object containing version information about the
		 Digital Publishing plug-in version. The dictionary will have the
		 following key/values:
		 
		 Key			Value
		 PlugInVersion: array of integers representing [InDesign major version, 
						InDesign minor version, DPS plug-in minor version, Sprint version]
		 
		 FolioVersion: array of integers representing [Folio major version, 
						Folio minor version, Folio revision]

		 PListVersion: array of integers representing [PList major version,
						PList minor version, PList revision]

		 SupportedViewerVersions: array of supported viewer version strings. The strings are in the
									form "Viewer major version.Viewer minor version.Viewer revision"

		 @return the version information for the DPS plug-in as a dictionary
		 */
		virtual id_digpub::ObjectPtr GetDigitalPublishingVersion() const = 0;
		
		/**
		 Returns the list of overlays contained in a pair of InDesign documents, 
		 using the specified options.
		 
		 @param portrait The document representing the folio's portrait orientation
		 @param landscape The document representing the folio's landscape orientation
		 @param options The options to use while creating the folio file
		 @param overlayDict [OUT] On successful exit, an array of dictionaries describing the identified overlays
		 
		 @param return an ErrorCode describing the status of the call
		 */
		virtual ErrorCode GetAllOverlays(
			IDocument const *portrait, 
			IDocument const *landscape,
			id_digpub::ObjectPtr const &options,
			id_digpub::ObjectPtr &overlayDict
		) const = 0;
		
		/**
		 Creates a 'mini' folio for a pair of InDesign documents, using the specified options
		 
		 @param portrait The document representing the folio's portrait orientation
		 @param landscape The document representing the folio's landscape orientation
		 @param options The options to use while creating the folio file
		 @param metadata The metadata to associate with the folio
		 @param folioFile The location in which to create the folio file
		 
		 @param return an ErrorCode describing the status of the call
		 */
		virtual ErrorCode CreateArticleFolio(
			IDocument const *portrait, 
			IDocument const *landscape,
			id_digpub::ObjectPtr const &options,
			DigitalPublishingMetadata const *metadata,
			IDFile const &folioFile
		) const = 0;
		
		/**
		 Adds a pair of documents, assumed to represent a single article in its
		 two orientations, to a folio.
		 
		 @param folio The folio the pair of documents will be added to
		 @param portrait The document representing the folio's portrait orientation
		 @param landscape The document representing the folio's landscape orientation
		 @param options The options to use while creating the folio file
		 @param metadata The metadata to associate with the article
		 
		 @return an ErrorCode indicating whether the call succeeded
		 */
		virtual ErrorCode AddDocumentPairToMagazineFolio(
			DigitalPublishingFolio *folio, 
			IDocument const *portrait, 
			IDocument const *landscape, 
			id_digpub::ObjectPtr const &options,
			DigitalPublishingMetadata const *metadata
		) const = 0;
	};
}

