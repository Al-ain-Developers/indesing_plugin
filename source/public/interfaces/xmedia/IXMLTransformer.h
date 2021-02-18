//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTransformer.h $
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

#include "XMLID.h"

class IIDXMLDOMDocument;

/**
	This class can be used during two different phases of the XML
	import. 
	
	The first phase is while there is a stream. During this phase 
	you can pass the stream to a transformer using an XSLt script.

	The second phase will occur imediately after the DOM has been
	created. During this phase you can manually manipulate the DOM
	by inserting, removing, and changing elements. 

	Place this interface on the same boss as a service provider that
	supports kXMLImporterTransformerService to ensure that it gets
	called at the appropriate times.
*/
class IXMLTransformer : public IPMUnknown
{
public:    
	enum { kDefaultIID = IID_IXMLTRANSFORMER };

	/** 
		Transform an XML stream using an XSLT script

		@param in - The original stream
		@param out - The new stream. (nil if no transformation occurred)
		@param xmlImporter - A pointer to the importer boss (so we can get import data)
		@return - kSuccess if the transform succeeded.
	*/
	virtual ErrorCode TransformStream(const IPMStream *in, IPMStream **out, IPMUnknown *xmlImporter = nil) = 0;

	/**
		Transform a DOM

		@param dom - The DOM to be manipulated
		@param xmlImporter - A pointer to the importer boss (so we can get import data)
		@return - kSuccess if the transform succeeded.
	*/
	virtual ErrorCode TransformDOM(IIDXMLDOMDocument *dom, IPMUnknown *xmlImporter = nil) = 0;
};
