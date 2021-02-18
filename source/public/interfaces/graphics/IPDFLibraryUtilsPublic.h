//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFLibraryUtilsPublic.h $
//  
//  Owner: Greg St. Pierre
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
//  A collection of PDF-specific utilities
//  
//========================================================================================

#pragma once

#ifndef IPDFLibraryUtils_Public__
#define IPDFLibraryUtils_Public__

#include "PDFID.h"
#include "Utils.h"

// These are opaque types
typedef struct _t_PDDoc *PDDoc;
typedef struct _t_PDPage *PDPage;

/**
 A collection of PDF-specific utilities. These replace and extend functionality
 found in IPDFLibrary and IPDFDocPort.
 */
class IPDFLibraryUtilsPublic : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFLIBRARYUTILSPUBLIC };
	
	/**
	 Determines whether the specified object is a PDF export port.
	 
	 @param port	The object to test
	 @return kTrue if the viewport is a PDF export port, or kFalse if not.
	 */
	virtual bool16 IsPDFExportPort(IPMUnknown const *port) const = 0;
	
	/**
	 Acquires the PDF library, ensuring that it is initialized. 
	 
	 Note: Call IsLibraryAvailable() to determine if the library is available for use.
	 
	 Note: This call *must* be matched with a call to ReleasePDFLibrary(), even when
	 IsLibraryAvailable() returns kFalse.
	 
	 @see IsLibraryAvailable
	 @see ReleasePDFLibrary
	 */
	virtual void AcquirePDFLibrary() const = 0;
	
	/**
	 Releases the PDF library, ensuring that it is terminated when no longer needed.
	 
	 @see AcquirePDFLibrary
	 */
	virtual void ReleasePDFLibrary() const = 0;
	
	/**
	 Determines whether the PDF library is available for use.
	 
	 @return kTrue if the library is available, or kFalse if not.
	 */
	virtual bool16 IsLibraryAvailable() const = 0;
	
	/**
	 Retrieves PDDoc object stored by the specified port, which is assumed to be a 
	 PDF export port (ie., that a call to IsPDFExportPort() for the port would return
	 kTrue).
	 
	 @param port		[IN] The port object from which to retrieve a PDDoc
	 @param document	[OUT] The PDDoc stored by the port
	 @return true if the port was a PDF export port and the port was successfully retrieved; otherwise false
	 @see IsPDFExportPort
	 */
	virtual bool GetPDDocForPDFExportPort(IPMUnknown *port, PDDoc &document) const = 0;
	
	/**
	 Retrieves the current PDPage object stored by the specified port, which is assumed 
	 to be a PDF export port (ie., that a call to IsPDFExportPort() for the port would 
	 return kTrue).
	 
	 @param port		[IN] The port object from which to retrieve a PDPage
	 @param page		[OUT] The current PDPage stored by the port
	 @return true if the port was a PDF export port and the port was successfully retrieved; otherwise false
	 @see IsPDFExportPort
	 */
	virtual bool GetPDPageForPDFExportPort(IPMUnknown *port, PDPage &page) const = 0;
};

/**
 Simple stack-based utility for acquiring an explicit reference to the PDF library.
 
 Note: This is not typically necessary. The PDF place and export commands will do
 this implicitly for you.
 
 Usage:
 
 PDFLibraryAcquireReference pdflibRef;
 
 if (pdflibRef.IsAvailable())
 {
	// Do something with the PDF library
 }
 
 */
class PDFLibraryAcquireReference
{
public:
	PDFLibraryAcquireReference()
	{
		Utils<IPDFLibraryUtilsPublic>()->AcquirePDFLibrary();
	}
	
	~PDFLibraryAcquireReference()
	{
		Utils<IPDFLibraryUtilsPublic>()->ReleasePDFLibrary();
	}
	
	bool16 IsAvailable() const
	{
		return Utils<IPDFLibraryUtilsPublic>()->IsLibraryAvailable();
	}
};

#endif
