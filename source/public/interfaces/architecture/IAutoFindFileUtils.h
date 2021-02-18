//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAutoFindFileUtils.h $
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
//  This class defines an utility interface that attempts to automatically find/resolve
//  missing files.
//  
//========================================================================================

#pragma once
#ifndef __IAutoFindFileUtils__
#define __IAutoFindFileUtils__

#include "UtilitiesID.h"

class IDFile;
class WideString;
class URI;

/**
 IAutoFindFileUtils is used to automatically find/resolve missing files.  The utility
 first attempts to find the file relative to the given directory.  If no file is found,
 the utility will attempt to find the file in the application's IDirList directory list.
*/
class IAutoFindFileUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAUTOFINDFILEUTILS };

	/**
	 Attempts to automatically (find without user interaction) the file with the
	 same name of the missing file.
	 @param dir		[IN]  Relative location of where to start the search.
	 @param oldFile	[IN]  Original path to the missing file.
	 @param newFile	[OUT] New path of the missing file.
	 @return kTrue if missing file was found, else kFalse.
	 */
	virtual bool16 AutoFindFile(const IDFile& dir, const IDFile& oldFile, IDFile* newFile) = 0;

	/**
	 Attempts to automatically (find without user interaction) the file with the
	 same name of the missing file.
	 @param dir		[IN]  Relative location of where to start the search.
	 @param oldFile	[IN]  Original path to the missing file.
	 @param newFile	[OUT] New path of the missing file.
	 @return True if missing file was found, else false.
	 */
	virtual bool AutoFindFile(const IDFile& dir, const IDFile& oldFile, IDFile& newFile) = 0;

	/**
	 Naively converts a HFS path to a POSIX path by adding a slash to the front of the path, 
	 replacing colons with forward slashes, and replacing forward slashes with colons. \\
	 No attempt is made to validate the HFS path before conversion.
	 @param hfsPath	  [IN]	HFS path to convert.
	 @param posixPath [OUT] Resulting POSIX path.
	 */
	virtual void HFSPathToPOSIXPath(const WideString& hfsPath, WideString& posixPath) const = 0;

	/**
	Attempts to automatically (find without user interaction) the URI with the
	same name of the missing URI.
	@param dir		[IN]  Relative location of where to start the search.
	@param oldURI	[IN]  Original URI to the missing file.
	@param newURI	[OUT] New URI of the missing file.
	@return kTrue if missing URI was found, else kFalse.
	*/
	virtual bool16 AutoFindFile(const IDFile& dir, const URI& oldURI, URI& newURI) = 0;

};

#endif	// __IAutoFindFileUtils__
