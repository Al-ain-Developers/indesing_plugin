//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaReadFormatInfo.h $
//  
//  Owner: wtislar
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
#ifndef __IMediaReadFormatInfo__
#define __IMediaReadFormatInfo__

#include "FileTypeList.h"
#include "MediaID.h"
#include "MediaLocation.h"
#include "PMTypes.h"
#include "PMFlavorTypes.h"

#include "IPMUnknown.h"
#include "IDocument.h"

/**
	This interface provides metadata for a specific kind of media format. This interface
	must be supported by all media filters.
*/
class IMediaReadFormatInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEDIAREADFORMATINFO };

	/** Retrieves a list of file types that the filter supports.
		@param fileTypeList valid pointer to an OSTypeList object to be
		populated by this method.
	*/
	virtual void GetFileTypes(OSTypeList* fileTypeList) = 0;
	
	/** Retrieves a list of extensions that the filter supports.
		@param extensionList valid pointer to an ExtensionList object to
		be populated by this method.
	*/
	virtual void GetExtensions(ExtensionList* extensionList) = 0;
	
	/** Retrieves the format name identifier.
		@param formatName valid pointer to a PMString object to be populated
		with the format name string by this method.
	*/
	virtual void GetFormatName(PMString* formatName) = 0;
	

	/** Retrieves a list of external flavors.

	    Clipboard support:  On the Mac, a clipboard flavor/type is equivalent
	    to an OSType.  On Windows, to get the clipboard flavor/type you must
	    register the format name with Windows and it will return the format.

		@param flavorList valid pointer to an ExternalPMFlavorList object to be
		populated by this method.
	*/
	virtual void GetExternalFlavors(ExternalPMFlavorList *flavorList) = 0;

	/** Retrieves the MediaType defined in MediaID.h.
		@return the MediaType.
	*/
	virtual MediaType GetMediaType() const = 0;

	/** Retrieves the media's mime type as defined in RFC 2046, Multipurpose Mail
	    Extensions (MIME) Part Two: Media Types.
		@return a PMString representing the mime type; a null PMString if the mime
		type is not known.
	*/
	virtual PMString GetMimeType( MediaLocation loc = MediaLocation() ) = 0;
	 
	/** Tests if a specific file type is recognized by this filter.
		@param fileType the OSType to test.
		@return kTrue if the fileType is recognized; kFalse otherwise.
	*/	 
	virtual bool16 CanReadFileType(OSType fileType) = 0;
	
	/** Tests if a specific extension is recognized by this filter.
		@param extension a PMString containing the extension to test.
		@return kTrue if the extension is recognized; kFalse otherwise.
	*/
	virtual bool16 CanReadExtension(const PMString& extension) = 0;

	/** Retrieves the base filename (with jpg extension) of the standard poster to
		represent the media type.
		@return the name of an existing poster jpg file.
	*/
	virtual const PMString GetStandardPosterFileName() const = 0;
}; // end IMediaReadFormatInfo interface

#endif //__IMediaReadFormatInfo__
