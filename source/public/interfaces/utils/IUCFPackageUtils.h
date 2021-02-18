//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/IUCFPackageUtils.h $
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
//========================================================================================

#pragma once

#ifndef IUCFPackageUtils_h__
#define IUCFPackageUtils_h__

#include "JBXID.h"
#include "Utils.h"

/*
	IUCFPackageUtils

	A class used to create and/or open a UCFPackage. PackageRef preserves the UCFPackage
	when opened by a caller.
*/


class IUCFPackageUtils : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IUCFPACKAGETUTILS};

	enum CompressionType
	{
		kNone = 0,
		kStandard = 8, // the value for zip deflated
		kLastValue = 0x7fffffff // promote the enumeration
	};

	enum UCFErrorCode
	{
		kSuccess = 0,			// Success
		kFailure,				// Generic 'something bad happened' failure
		kInvalidParam,			// Specified parameter was incorrect
		
		kNoSuchFile,			// Specified file wasn't found
		kOpenFile,				// Specified file couldn't be opened
		kIOFailure,				// I/O error
		
		kInvalidURI,			// Specified URI is invalid
		
		kNoSuchAsset,			// Specified asset doesn't exist
		kAssetAlreadyExists,	// Asset already in the job bag
		
		kOperationInProgress,	// Failure due to in-progress operation
		kInvalidOutsideUpdate,	// Specified operation cannot be performed outside an update
		
		kCanceledError,			// Operation was canceled by user		
	};

	/*
		PackageRef

		Simple wrapper for the package and the manifest file
		that is passed to the caller to retain a reference to
		the packaging instance. Caller should not reference
		any of the contents.
	*/

	class PackageRef
	{
	public:
		UCFErrorCode GetLastError() { return fError; }

	protected:
		PackageRef() : fError(kSuccess) {}
		virtual ~PackageRef() {}

	private:
		friend class UCFPackageUtils;
		UCFErrorCode fError;
	};

	typedef PackageRef* PackageRefPtr;

	// UCF can write property into two different locations, zip entry or new UCF speccific entry.
	// If your ucf package needs to be compatible with zip application, they have to be set before 
	// stream is opened. Please use IUCFStreamProperty interface to set UCF specific property.
	struct FileProperty
	{
		OSType fileType;
		OSType creator;
		uint64 timeStamp;
	};

public:
	/* UCF library support three modes for opening packages:

	1. reading only(std::ios::in)
	2. writing only(std::ios::out) 
	3. rewriting(std::ios::in | std::ios::out | std::ios::trunc) -- which uses a temp file
		Mode 3 is similar to update a package. But updated package has to be saved to a new file.

	Right now, this interface only support 1 and 2.
	*/

	// Create package for write (mode 2)
	virtual PackageRefPtr CreatePackage(const IDFile & file, const AString& mimeType, bool16 createManifest, UCFErrorCode & err) = 0;
	virtual PackageRefPtr CreatePackage(const IPMStream * stream, const AString& mimeType, bool16 createManifest, UCFErrorCode & err) = 0;

	// Open a stream in package for write.
	virtual IPMStream* CreateStream(PackageRefPtr ref, const WideString & packageRelativePath, CompressionType compress, FileProperty * entryProp = nil) = 0;

	// Close package
	virtual UCFErrorCode ClosePackage(PackageRefPtr ref) = 0;

	// Close and dsicard change (assume it is created for write)
	virtual UCFErrorCode ClosePackageWithoutSave(PackageRefPtr ref) = 0;

	// Open existing package for read. Need to call ClosePackage when finish. (mode 1)
	virtual PackageRefPtr OpenPackage(const IDFile & file, UCFErrorCode & err) = 0;
	virtual PackageRefPtr OpenPackage(const IPMStream * stream, UCFErrorCode & err) = 0;

	// Open a existing file in package for read 
	virtual IPMStream* OpenStream(PackageRefPtr ref, const WideString & packageRelativePath) = 0;

	// Package a folder into a UCF package or unpackage a UCF file to a folder.
	virtual UCFErrorCode PackageUCF( const IDFile& FromFolder, IDFile& ToIDMLFile, const WideString & type, bool16 overwriteExisting = kTrue) = 0;
	virtual UCFErrorCode UnPackageUCF( const IDFile& FromIDMLFile, IDFile& ToFolder ) = 0;

	// Misc functions. 
	virtual bool16 FileExists(PackageRefPtr ref, const WideString & packageRelativePath) = 0;
	virtual bool16 IsUCFPackage(const IDFile & file) = 0;
	virtual UCFErrorCode ExtractPackage(PackageRefPtr ref, const IDFile & folder) = 0;

	// packageRelativePath should be full file spec (path + name)
	virtual bool16 AddExistingFile(PackageRefPtr ref, const IDFile & file, const WideString & packageRelativePath) = 0;

	// Set zip file comment. Must call before close package
	virtual UCFErrorCode SetPackageComment(PackageRefPtr ref, const WideString & comment) = 0;
};


#endif // IUCFPackageUtils_h__
