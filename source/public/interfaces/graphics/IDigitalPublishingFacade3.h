//========================================================================================
//  Owner: Adobe Systems Inc.
//  
//  Copyright 2010-2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once

#include "IDigitalPublishingFacade2.h"

namespace Facade
{
	class IDigitalPublishingFacade3 : public IDigitalPublishingFacade2
	{
	public:
		enum { kDefaultIID = IID_IDIGITALPUBLISHINGFACADE3 };
		
		/**
		 Creates a DPS article for an InDesign document, using the specified options
		 
		 @param document	The document to export
		 @param options		The options to use while creating the article file
		 @param articleFile	The location in which to create the article file
		 
		 @return an ErrorCode describing the status of the call
		 */
		virtual ErrorCode ExportDPSArticle(	IDocument const *document, 
											id_digpub::ObjectPtr const &optionsDict,
											IDFile const &articleFile
										) const = 0;

		/**
		 Returns a dictionary object containing version information about the
		 Digital Publishing plug-in article versions. The dictionary will have the
		 following key/values:
		 
		 Key					Value
		 ArticlePlugInVersion:	array of integers representing [InDesign major version, 
								InDesign minor version, DPS article plug-in minor version, Sprint version]
		 
		 ArticleVersion:		array of integers representing [Article major version, 
								Article minor version, Article revision]

		 SupportedArticleViewerVersions: array of supported article viewer version strings. The strings are in the
									form "Viewer major version.Viewer minor version.Viewer revision"

		 @return the version information for the DPS plug-in as a dictionary
		 */
		virtual id_digpub::ObjectPtr GetDigitalPublishingArticleVersion() const = 0;
	};
}

