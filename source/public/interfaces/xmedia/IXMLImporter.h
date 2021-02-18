//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImporter.h $
//  
//  Owner: Ryan Gano
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

#include "VCPlugInHeaders.h"

#include "XMLID.h"

class XMLReference;
class IDataLink;
class ISAXEntityResolver;

/**
	This is the governor for the complete XML import process. It doesn't
	actually do any of the import work. Rather it walks through the import
	timeline and calls signal/responders and service providers where 
	appropriate so that clients of the import process can perform specific
	actions at the appropriate time.  

	The timeline contains the following steps/hooks:
	Transformations. 
		You can either transform the original stream or the DOM.
		You must have a service provider that handles kXMLImporterTransformerService
	Match incoming XML elements to existing elements and create new elements where needed.
		You must have a signal/responder that responds to kXMLImportMatchMakerSignalService
	Import the contents from the incoming XML into the existing XML elements
		You must have a service provider that handles kXMLContentHandlerService
	Handle Post import processes.
		You must have a signal/responder that responds to kXMLImporterPostImportService
*/
class IXMLImporter : public IPMUnknown
{
public:    
	enum { kDefaultIID = IID_IXMLIMPORTER };
	/**
		This is the starting point for the import. This method takes an IPMStream that contains
		the XML. 

		@param stream - IN The data of import information.
		@param entityResolver - IN The entity resolver to use while handling the content
		@return ErrorCode
	*/
	virtual ErrorCode DoImport(IPMStream* stream, ISAXEntityResolver *entityResolver) = 0;
};
