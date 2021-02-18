//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/IXDocBkFacade.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __IXDocBkFacade_H_DEFINED__
#define __IXDocBkFacade_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "XDocBkID.h"

// Forward declarations:
class IDocument;

/** From SDK sample; facade interface that represents the main capabilities required from client code.
	
	TODO the comment above seems to indicate that the class is not cohesive enough to be described functionally.
	facade that does this or that (import/import XML) would be more useful to reader.

	TODO "From SDK sample" are you suggesting all sample code needs this?

	@ingroup xdocbookworkflow
	@see XDocBookWorkflowUI
*/
class IXDocBkFacade : public IPMUnknown
{

public:

	/** Default interface identifier for UseDefaultIID 
		@see UseDefaultIID
	*/
	enum { kDefaultIID = IID_IXDOCBKFACADE };

	/** Sets the persistent options (IXDocBkOptions) on the session workspace (kWorkspaceBoss).	
		@param optionsVec IN K2Vector of PMString objects, containing the options.
		@return kSuccess on success, other ErrorCode otherwise.
		@see IXDocBkOptions
		@see kWorkspaceBoss
		@see kXDocBkChangeOptionsCmdBoss
	*/
	virtual ErrorCode SetOptions(const K2Vector<WideString>& optionsVec)=0;

	/** Have options been set up? Decouple client code from knowledge of all options
		@return kTrue if options set, kFalse otherwise
	*/
	virtual bool16 AreOptionsSet()=0;


	/** Resize inlines in document to fit within width of columns
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode ResizeInlines(const UIDRef& documentUIDRef)=0;


	/** Imports XML file into specified document
		@param xmlFile IN file to import
		@param destDocumentUIDRef IN target document
		@param stylesheetPath optional XSL stylesheet path, which can be empty
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode ImportXMLFile(const IDFile& xmlFile, const UIDRef& destDocumentUIDRef, const PMString& stylesheetPath)=0;

	/** Export XML logical structure from given document into specified file
		@param sysFile IN file to export to
		@param doc IN where logical structure comes from
		@param targetBoss IN may carry a selection or nil if not exporting from selection
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode ExportXMLFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)=0;

	/** Return string based representation of path to template for importing into
		@return string giving path to template, empty if not set up (see SetOptions)
	*/
	virtual PMString GetTemplatePath()=0;

	/** Return string based representation of path for default template in same folder
		@param importingXMLFile
		@return string giving path to template
	*/
	virtual PMString GetDefaultTemplateFromFolder(const IDFile& importingXMLFile)=0;

	/** Return path to optional XSL stylesheet
		@return stylesheet path, empty if not set up
	*/
	virtual PMString GetStylesheetPath()=0;

	/** Change service-specific preference to use our XML transformer on stream.
		@param newState specifies turn on (kTrue) or off (kFalse)
		@return kSuccess on success, other ErrorCode otherwise
		@see IXMLTransformer
	
	*/
	virtual ErrorCode SetUseXMLTransformer(bool16 newState)=0;

	/** Change service-specific preference to use post-import iterator to place images
		@return kSuccess on success, other ErrorCode otherwise
		@see IXMLPostImportIteration
	*/
	virtual ErrorCode SetUsePostImportIterator(bool16 newState)=0;

	/** Change service-specific preference to use SAX handler to create images
		@return kSuccess on success, other ErrorCode otherwise
		@see ISAXDOMSerializerHandler
	*/
	virtual ErrorCode SetUseCALSContentHandler(bool16 newState)=0;

	/** Determine if the XML transformer (on stream) is being used to apply context sensitive styling
		through XSLT

		@return kTrue if use of XML transformer on inbound stream is enabled, kFalse if not
		@see IXMLTransformer
	*/
	virtual bool16 IsUsingXMLTransformer()=0;

	/**
		@return kTrue if post-import iterator for placing images is enabled, kFalse if not
		@see IXMLPostImportIteration
	*/
	virtual bool16 IsUsingPostImportIterator()=0;

	/** Determine if SAX Handler to create tables from CALS model is turned on
		@return kTrue if using CALS SAX handler to create tables, kFalse otherwise
		@see ISAXDOMSerializerHandler
	*/
	virtual bool16 IsUsingCALSContentHandler()=0;


	/** Set option to delete aid:xxx attrs on import
		@return kSuccess on success, other ErrorCode otherwise
	
	*/
	virtual ErrorCode SetDeleteNamespacedAttrs(bool16 newState)=0;
	
	/** Determine if option to delete aid:xxx attrs is turned on
		@return kTrue if turned on, kFalse if turned off
	*/
	virtual bool16 IsDeleteNamespacedAttrs()=0;

	/** Set option to delete aid:xxx attrs on import
		@return kSuccess on success, other ErrorCode otherwise
	
	*/
	virtual ErrorCode SetDeleteInboundStrucTableElements(bool16 newState)=0;
	
	/** Determine if option to delete aid:xxx attrs is turned on
		@return kTrue if turned on, kFalse if turned off
	*/
	virtual bool16 IsDeleteInboundStrucTableElements()=0;

	/** Determine whether the option to tag created table is turned on
		@return kTrue if turned on, kFalse if turned off
	*/
	virtual bool16 IsTaggingTable()=0;

	/**
	*/
	virtual bool16 IsSuppliedXSLOverridingPI()=0;

	/**
	*/
	virtual ErrorCode SetSuppliedXSLOverridingPI(bool16 newState)=0;

	/** Set option to tag created table
		@return kSuccess on success, other ErrorCode otherwise
	*/	
	virtual ErrorCode SetTaggingTable(bool16 newState)=0;

	/** Method that just exercises methods on this facade
	*/
	virtual void UnitTestFacade()=0;

	/** Append platform path separator to string
		@param path input string
		@return path input with platform path separator appended
	*/
	virtual PMString AddPathSeparator(const PMString& path)=0;
};

#endif // __IXDocBkFacade_H_DEFINED__

