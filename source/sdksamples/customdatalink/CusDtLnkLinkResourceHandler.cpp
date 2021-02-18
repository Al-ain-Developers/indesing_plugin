//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceHandler.cpp $
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

#include "VCPlugInHeaders.h"
#include "CusDtLnkLinkResourceHandler.h"

#include "IPMStream.h"
#include "IURIUtils.h"
#include "ICusDtLnkFacade.h"
#include "CoreFileUtils.h"
#include "AString.h"
#include "FileTypeInfo.h"
#include "FileUtils.h"
#include "IDFile.h"
#include "StreamUtil.h"
#include "URI.h"
#include "Utils.h"
#include "WideString.h"
#include "CusDtLnkID.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif

CREATE_PMINTERFACE(CusDtLnkLinkResourceHandler, kCusDtLnkLinkResourceHandlerImpl)


//========================================================================================
//
// CusDtLnkLinkResourceHandler Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceHandler::CusDtLnkLinkResourceHandler(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkResourceHandler::~CusDtLnkLinkResourceHandler()
{
}

//========================================================================================
// CusDtLnkLinkResourceHandler::IsResourceURIValid
//========================================================================================
static const WideString k_fileScheme(kCusDtLnkScheme);
bool CusDtLnkLinkResourceHandler::IsResourceURIValid(const UIDRef& ref, const URI& uri) const
{

	WideString uriScheme(uri.GetComponent(URI::kScheme));
	if (uriScheme != k_fileScheme) {
		return false;
	}

	WideString path(uri.GetComponent(URI::kPath));
	return !path.IsNull();
}

//========================================================================================
// CusDtLnkLinkResourceHandler::AreResourceIdsEquivalent
//========================================================================================
bool CusDtLnkLinkResourceHandler::AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const
{
	return (id1 == id2);
}

//========================================================================================
// CusDtLnkLinkResourceHandler::GetResourceDataType
//========================================================================================
FileTypeInfo CusDtLnkLinkResourceHandler::GetResourceDataType(const UIDRef& ref, const URI& uri) const
{
	IDFile file;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file)) {
		return FileTypeInfo();
	}

	AString extension(file.GetName().GetExtension());

#ifdef MACINTOSH
	AOSType creator;
	AOSType type;
	MacFileUtils::GetCreatorAndType(file, creator, type);
	return FileTypeInfo(type, creator, PMString(extension.GrabWString(), extension.UTF16Count()), "", 0);
#else
	return FileTypeInfo(0, 0, PMString(extension.GrabWString(), extension.UTF16Count()), "", 0);
#endif
}

//========================================================================================
// CusDtLnkLinkResourceHandler::GetShortResourceName
//========================================================================================
WideString CusDtLnkLinkResourceHandler::GetShortResourceName(const UIDRef& ref, const URI& uri, bool) const
{
	IDFile file;
	Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file);

	AString name(file.GetNameStr());
	return WideString(name.GrabWString(), name.UTF16Count(), name.CharCount());
}

//========================================================================================
// CusDtLnkLinkResourceHandler::GetLongResourceName
//========================================================================================
WideString CusDtLnkLinkResourceHandler::GetLongResourceName(const UIDRef& ref, const URI& uri, bool) const
{
	WideString dbPath = uri.GetComponent(URI::kPath);
	PMString dpath(dbPath);
	PMString dbName = Utils<ICusDtLnkFacade>()->TruncatePath(dpath);
	
	WideString recordID = uri.GetComponent(URI::kQuery);

	IDFile file;
	URIUTILS->URIToIDFile(uri, file);
	AString path(file.GetPath(false));
	WideString fileName(path.GrabWString(), path.UTF16Count(), path.CharCount());
	
	WideString longName;
	longName.Append(WideString(dbName));
	longName.Append(WideString("/"));
	longName.Append(WideString(recordID));
	longName.Append(WideString(":"));
	longName.Append(WideString(fileName));
	return longName;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::AreStampsEquivalent
//========================================================================================
bool CusDtLnkLinkResourceHandler::AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const
{
	if (stamp1 == stamp2) {
		return true;
	}

	// TODO
	return (stamp1 == stamp2);
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanReadResource
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanReadResource(const UIDRef& ref, const URI& uri) const
{
	IDFile file;
	return (Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file) && file.GetAttribute(IDFile::kReadable));
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanWriteResource
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanWriteResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanReadWriteResource
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanReadWriteResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanCreateResourceStream
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const
{
	IDFile file;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file)) {
		return false;
	}

	switch (mode) {
		case ILinkResource::kRead:
			return file.CanOpen(IDFile::kReadAccess, IDFile::kShareReadAccess);
			break;
		case ILinkResource::kWrite:
			break;
		case ILinkResource::kReadWrite:
			break;
		default:
			ASSERT_FAIL("CusDtLnkLinkResourceHandler::CanCreateResourceStream() - Unrecognized access mode!");
			break;
	}

	return false;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CreateResourceReadStream
//========================================================================================
IPMStream* CusDtLnkLinkResourceHandler::CreateResourceReadStream(const UIDRef& ref, const URI& uri) const
{
	IDFile file;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file) || !file.GetAttribute(IDFile::kReadable)) {
		return nil;
	}

#ifdef MACINTOSH
	AOSType creator;
	AOSType type;
	MacFileUtils::GetCreatorAndType(file, creator, type);
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamReadLazy(file, kOpenIn, type, creator)).forget();
#else
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamReadLazy(file, kOpenIn)).forget();
#endif

//	static IPMStream *CreateFileStreamRead(const IDFile& sysFile, uint32 mode = kOpenIn, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);
//	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamReadLazy(file, kOpenIn)).forget();
//	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamRead(file, kOpenIn)).forget();
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CreateResourceWriteStream
//========================================================================================
IPMStream* CusDtLnkLinkResourceHandler::CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const
{
	return nil;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CreateResourceReadWriteStream
//========================================================================================
IPMStream* CusDtLnkLinkResourceHandler::CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const
{
	return nil;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanCopyToFile
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanCopyToFile(const UIDRef& ref, const URI& uri) const
{
	IDFile file;
	return (Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file) && file.Exists());
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CopyToFile
//========================================================================================
ErrorCode CusDtLnkLinkResourceHandler::CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const
{
	IDFile rsrcFile;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(uri, rsrcFile))
		return kFailure;
	
	return CoreFileUtils::CopyFile(rsrcFile, file) ? kSuccess : kFailure;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanEditResource
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanEditResource(const UIDRef& ref, const URI& uri) const
{
//	ASSERT_UNIMPLEMENTED(); 
	// TODO
	IDFile file;
	return (Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file) && file.GetAttribute(IDFile::kWritable));
}

//========================================================================================
// CusDtLnkLinkResourceHandler::EditResource
//========================================================================================
ErrorCode CusDtLnkLinkResourceHandler::EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const
{
//	ASSERT_UNIMPLEMENTED(); 
	IDFile file;
	return (Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file) && file.GetAttribute(IDFile::kWritable))
			? FileUtils::OpenFileInEditor(file, appInfo, errorString) : kFailure;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanRevealResource
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanRevealResource(const UIDRef& ref, const URI& uri) const
{
//	ASSERT_UNIMPLEMENTED(); 
	// TODO
	return false;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::RevealResource
//========================================================================================
ErrorCode CusDtLnkLinkResourceHandler::RevealResource(const UIDRef& ref, const URI& uri) const
{
//	ASSERT_UNIMPLEMENTED(); 
	// TODO
	return kFailure;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::CanRevealResourceInBridge
//========================================================================================
bool CusDtLnkLinkResourceHandler::CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const
{
//	ASSERT_UNIMPLEMENTED(); 
	// TODO
	return false;
}

//========================================================================================
// CusDtLnkLinkResourceHandler::RevealResourceInBridge
//========================================================================================
ErrorCode CusDtLnkLinkResourceHandler::RevealResourceInBridge(const UIDRef& ref, const URI& uri) const
{
//	ASSERT_UNIMPLEMENTED(); 
	// TODO
	return kFailure;
}

