//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IURIUtils.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This class defines an utility interface used to manipulate URIs.
//  
//========================================================================================

#pragma once
#ifndef __IURIUtils__
#define __IURIUtils__

// ----- Includes -----
#include "IPMUnknown.h"
#include "UtilitiesID.h"
#include "SysFileList.h"
#include "URIList.h"

class IDFIle;
class URI;

#define URIUTILS Utils<IURIUtils>()


/**
 Utility interface that provides methods used to manipulate Uniform
 Resource Identifiers (URI).
 @see IDFile
 @see URI
 */
class IURIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IURIUTILS };

	/**
	 Converts an IDFile to an URI.
	 @param file [IN] IDFile to convert.
	 @param uri	 [OUT] Resulting URI.
	 @return True if the conversion succeeds, else false. 
	 */ 
	virtual bool IDFileToURI(const IDFile& file, URI& uri) const = 0;

	/**
	 Converts an URI to an IDFile.
	 @param uri	 [IN] URI to convert.
	 @param file [OUT] Resulting IDFile.
	 @return True if the conversion succeeds, else false. 
	 */ 
	virtual bool URIToIDFile(const URI& uri, IDFile& file) const = 0;

	/** 
		Convert the sys file list to a URIList
		@param uriList [IN] the list of URIs to convert.
		@param sysFileList [OUT] the list of IDFiles
		@return kTrue if the conversion succeeds.
	*/
	virtual bool URIListToSysFileList(const URIList& uriList, SysFileList& sysFileList) const = 0;
	/** 
		Convert the URIList to a SysFileList
		@param sysFileList [IN] the list of sys files to convert.
		@param uriList [OUT] the list of URIs
		@return kTrue if the conversion succeeds.
	*/
	virtual bool SysFileListToURIList(const SysFileList& sysFileList, URIList& uriList) const = 0;

};

#endif // __IURIUtils__
