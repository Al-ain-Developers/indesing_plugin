//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/FileLinkResourceHandler.cpp $
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
//========================================================================================

#include "VCPublicHeaders.h"
#include "FileLinkResourceHandler.h"

#include "IPMStream.h"
#include "ILinkUtils.h"
#include "IURIUtils.h"

#include "AString.h"
#include "CoreFileUtils.h"
#include "FileTypeInfo.h"
#include "FileTypeRegistry.h"
#include "FileUtils.h"
#include "IDFile.h"
#include "StreamUtil.h"
#include "StringNumeric.h"
#include "URI.h"
#include "Utils.h"
#include "WideString.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif

// see  .../source/components/utilities/plugin/PublicImpl.cpp
//CREATE_PMINTERFACE(FileLinkResourceHandler, kFileLinkResourceHandlerImpl)


//========================================================================================
//
// FileLinkResourceHandler Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
FileLinkResourceHandler::FileLinkResourceHandler(IPMUnknown* boss)
: inherited(boss),
  fbInited(false)
{
}

//========================================================================================
// Destructor
//========================================================================================
FileLinkResourceHandler::~FileLinkResourceHandler()
{
}

//========================================================================================
// FileLinkResourceHandler::Init
//========================================================================================
bool FileLinkResourceHandler::Init(const UIDRef& ref, const URI& uri)
{
	fbInited = Utils<ILinkUtils>()->ResourceIdToIDFile(uri, fFile);
	fFileTypeInfoID = kInvalidFileTypeInfoID;
	fShortNameCache.Clear();
	fShortUINameCache.Clear();
	fLongNameCache.Clear();
	fLongUINameCache.Clear();
	return fbInited;
}

//========================================================================================
// FileLinkResourceHandler::IsResourceURIValid
//========================================================================================
bool FileLinkResourceHandler::IsResourceURIValid(const UIDRef& ref, const URI& uri) const
{
	// Cannot use static here for the following reasons:
	// In order to satisfy thread-safety the static cannot be local.
	// Once you declare it outside of the scope of this function, 
	// because this cpp file is defined in public, initialization of 
	// global wide strings from public does not quite work because cooltype
	// is not initialized yet.
	const WideString kFileScheme("file");

	WideString uriScheme(uri.GetComponent(URI::kScheme));
	if (uriScheme != kFileScheme) {
		return false;
	}

	WideString path(uri.GetComponent(URI::kPath));
	return !path.IsNull();
}

//========================================================================================
// FileLinkResourceHandler::AreResourceIdsEquivalent
//========================================================================================
bool FileLinkResourceHandler::AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const
{
	return (id1 == id2);
}

//========================================================================================
// FileLinkResourceHandler::GetResourceDataType
//========================================================================================
FileTypeInfo FileLinkResourceHandler::GetResourceDataType(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited) {
		return FileTypeInfo();
	}

	if (fFileTypeInfoID == kInvalidFileTypeInfoID) {
		fFileTypeInfoID = FileTypeRegistry::GetFileTypeInfoIDForFile(fFile);
	}

	if (fFileTypeInfoID == kInvalidFileTypeInfoID) {
		AString extension(fFile.GetName().GetExtension());

	#ifdef MACINTOSH
		AOSType creator;
		AOSType type;
		MacFileUtils::GetCreatorAndType(fFile, creator, type);
		return FileTypeInfo(type, creator, PMString(extension.GrabWString(), extension.UTF16Count()), "", 0);
	#else
		return FileTypeInfo(0, 0, PMString(extension.GrabWString(), extension.UTF16Count()), "", 0);
	#endif
	}

	return FileTypeRegistry::GetCurrentFileTypeInfo(fFileTypeInfoID);
}

//========================================================================================
// FileLinkResourceHandler::GetShortResourceName
//========================================================================================
WideString FileLinkResourceHandler::GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const
{
	if (bUIName) {
		if (!fShortUINameCache.empty()) return fShortUINameCache;
	}
	else {
		if (!fShortNameCache.empty()) return fShortNameCache;
	}

	AString name(fFile.GetNameStr());
	fShortNameCache = WideString(name.GrabWString(), name.UTF16Count(), name.CharCount());

	#ifdef MACINTOSH
		MacFileUtils::POSIXNameToHFSName(name);
		fShortUINameCache = WideString(name.GrabWString(), name.UTF16Count(), name.CharCount());
	#else
		fShortUINameCache = fShortNameCache;
	#endif

	return (bUIName ? fShortUINameCache : fShortNameCache);
}

//========================================================================================
// FileLinkResourceHandler::GetLongResourceName
//========================================================================================
WideString FileLinkResourceHandler::GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const
{
	if (bUIName) {
		if (!fLongUINameCache.empty()) return fLongUINameCache;
	}
	else {
		if (!fLongNameCache.empty()) return fLongNameCache;
	}

	AString path(fFile.GetPath(false));
	fLongNameCache = WideString(path.GrabWString(), path.UTF16Count(), path.CharCount());

	#ifdef MACINTOSH
		PMString tmpLongName;
		FileUtils::IDFileToPMString(fFile, tmpLongName);
		fLongUINameCache = WideString(tmpLongName);
	#else
		fLongUINameCache = fLongNameCache;
	#endif

	if (bUIName && !fLongUINameCache.empty()) return fLongUINameCache;

	return fLongNameCache;
}

//========================================================================================
// FileLinkResourceHandler::AreStampsEquivalent
//========================================================================================
bool FileLinkResourceHandler::AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const
{
	const uint64 kOneSecond(10000000);
	const uint64 kTwoSecond(20000000);
	// Cannot use static here for the following reasons:
	// In order to satisfy thread-safety the static cannot be local.
	// Once you declare it outside of the scope of this function, 
	// because this cpp file is defined in public, initialization of 
	// global wide strings from public does not quite work because cooltype
	// is not initialized yet.
	const WideString kFileScheme("file ");
	const WideString kDelimiter(" ");

	if (stamp1 == stamp2) {
		return true;
	}

	if (!stamp2.Contains(kFileScheme, 0)) {
		return false;
	}

	// first compare the file's data size 
	K2::scoped_ptr<WideString> size1Str(stamp1.GetItem(kDelimiter, 3));
	K2::scoped_ptr<WideString> size2Str(stamp2.GetItem(kDelimiter, 3));
	if (!size1Str || !size2Str) {
		return false;
	}

	uint64 size1;
	if (stringnumeric::FromString(*size1Str.get(), size1) != kSuccess) {
		return false;
	}

	uint64 size2;
	if (stringnumeric::FromString(*size2Str.get(), size2) != kSuccess) {
		return false;
	}

	if (size1 != size2) {
		return false;
	}

	// now compare the file's modified time 
	K2::scoped_ptr<WideString> time1Str(stamp1.GetItem(kDelimiter, 2));
	K2::scoped_ptr<WideString> time2Str(stamp2.GetItem(kDelimiter, 2));
	if (!time1Str || !time2Str) {
		return false;
	}

	uint64 time1;
	if (stringnumeric::FromString(*time1Str.get(), time1) != kSuccess) {
		return false;
	}

	uint64 time2;
	if (stringnumeric::FromString(*time2Str.get(), time2) != kSuccess) {
		return false;
	}

	// Moving a file from NTFS to FAT or from an assignment package to the file system
	// can result in modifed links because the time resolution on FAT and the package's
	// DOS time is 2 second versus 100 nanoseconds for NTFS. Therefore, if either of the
	// time stamps do not have fractions of a second we will use a lax 2 second comparison.
	bool bUseLaxComparison(!(time1 % kOneSecond && time2 % kOneSecond));

	if (time1 != time2) {
		if (time1 < time2) {
			// is time1 within 1 second of time2
			return ((time1 + (bUseLaxComparison ? kTwoSecond : kOneSecond)) >= time2);
		}
		else {
			// is time2 within 1 second of time1
			return ((time2 + (bUseLaxComparison ? kTwoSecond : kOneSecond)) >= time1);
		}
	}

	return true;
}

//========================================================================================
// FileLinkResourceHandler::CanReadResource
//========================================================================================
bool FileLinkResourceHandler::CanReadResource(const UIDRef& ref, const URI& uri) const
{
	return (fbInited && fFile.GetAttribute(IDFile::kReadable));
}

//========================================================================================
// FileLinkResourceHandler::CanWriteResource
//========================================================================================
bool FileLinkResourceHandler::CanWriteResource(const UIDRef& ref, const URI& uri) const
{
	return (fbInited && (!fFile.Exists() || fFile.GetAttribute(IDFile::kWritable)));
}

//========================================================================================
// FileLinkResourceHandler::CanReadWriteResource
//========================================================================================
bool FileLinkResourceHandler::CanReadWriteResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

//========================================================================================
// FileLinkResourceHandler::CanCreateResourceStream
//========================================================================================
bool FileLinkResourceHandler::CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const
{
	if (!fbInited) {
		return false;
	}

	switch (mode) {
		case ILinkResource::kRead:
			// #2851854 - IDFile::kReadAccess,IDFile::kShareReadAccess check for 
			// fsRdPerm|fsWrDenyPerm on the Mac.  In some instances, having a file
			// open with these perms will cause another FSOpenFork(fsRdPerm) to fail.
			// Since this call to CanOpen also returns true if we have fsRdPerm, but not
			// fsRdPerm|fsWrDenyPerm, we just check for fsRdPerm to eliminate this risk.
//			return fFile.CanOpen(IDFile::kReadAccess, IDFile::kShareReadAccess);
		 #ifdef MACINTOSH
			return fFile.CanOpen(IDFile::kReadAccess, IDFile::kShareReadWriteAccess);	// read access
		 #else
			return fFile.CanOpen(IDFile::kReadAccess, IDFile::kShareReadAccess);		// read/write-deny
		 #endif
			break;
		case ILinkResource::kWrite:
//			return fFile.CanOpen(IDFile::kWriteAccess, IDFile::kExclusiveAccess);
			return (!fFile.Exists() || fFile.CanOpen(IDFile::kWriteAccess, IDFile::kShareReadAccess));
			break;
		case ILinkResource::kReadWrite:
//			return fFile.CanOpen(IDFile::kReadWriteAccess, IDFile::kExclusiveAccess);
			break;
		default:
			ASSERT_FAIL("FileLinkResourceHandler::CanCreateResourceStream() - Unrecognized access mode!");
			break;
	}

	return false;
}

//========================================================================================
// FileLinkResourceHandler::CreateResourceReadStream
//========================================================================================
IPMStream* FileLinkResourceHandler::CreateResourceReadStream(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited || !fFile.GetAttribute(IDFile::kReadable)) {
		return nil;
	}

#ifdef MACINTOSH
	AOSType creator;
	AOSType type;
	MacFileUtils::GetCreatorAndType(fFile, creator, type);
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamReadLazy(fFile, kOpenIn, type, creator)).forget();
#else
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamReadLazy(fFile, kOpenIn)).forget();
#endif
}

//========================================================================================
// FileLinkResourceHandler::CreateResourceWriteStream
//========================================================================================
IPMStream* FileLinkResourceHandler::CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited || (fFile.Exists() && !fFile.GetAttribute(IDFile::kWritable))) {
		return nil;
	}

#ifdef MACINTOSH
	AOSType creator;
	AOSType type;
	MacFileUtils::GetCreatorAndType(fFile, creator, type);
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamWriteLazy(fFile, kOpenOut | kOpenTrunc, type, creator)).forget();
#else
	return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamWriteLazy(fFile, kOpenOut | kOpenTrunc)).forget();
#endif
}

//========================================================================================
// FileLinkResourceHandler::CreateResourceReadWriteStream
//========================================================================================
IPMStream* FileLinkResourceHandler::CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const
{
	//return InterfacePtr<IPMStream>(StreamUtil::CreateFileStreamWriteLazy(file, kOpenOut)).forget();
	return nil;
}

//========================================================================================
// FileLinkResourceHandler::CanCopyToFile
//========================================================================================
bool FileLinkResourceHandler::CanCopyToFile(const UIDRef& ref, const URI& uri) const
{
	return (fbInited && fFile.Exists());
}

//========================================================================================
// FileLinkResourceHandler::CopyToFile
//========================================================================================
ErrorCode FileLinkResourceHandler::CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const
{
	return (fbInited && CoreFileUtils::CopyFile(fFile, file)) ? kSuccess : kFailure;	
}

//========================================================================================
// FileLinkResourceHandler::CanEditResource
//========================================================================================
bool FileLinkResourceHandler::CanEditResource(const UIDRef& ref, const URI& uri) const
{
	return fbInited;
}

//========================================================================================
// FileLinkResourceHandler::EditResource
//========================================================================================
ErrorCode FileLinkResourceHandler::EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const
{
	return (fbInited ? FileUtils::OpenFileInEditor(fFile, appInfo, errorString) : kFailure);
}

//========================================================================================
// FileLinkResourceHandler::CanRevealResource
//========================================================================================
bool FileLinkResourceHandler::CanRevealResource(const UIDRef& ref, const URI& uri) const
{
	return fbInited; // if we can have a file, we can reveal it - right?
}

//========================================================================================
// FileLinkResourceHandler::RevealResource
//========================================================================================
ErrorCode FileLinkResourceHandler::RevealResource(const UIDRef& ref, const URI& uri) const
{
	return (fbInited ? FileUtils::ShowFile(fFile) : kFailure);
}

//========================================================================================
// FileLinkResourceHandler::CanRevealResourceInBridge
//========================================================================================
bool FileLinkResourceHandler::CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const
{
	return fbInited; // if we can have a file, we can reveal it - right?
}

//========================================================================================
// FileLinkResourceHandler::RevealResourceInBridge
//========================================================================================
ErrorCode FileLinkResourceHandler::RevealResourceInBridge(const UIDRef& ref, const URI& uri) const
{
	return (fbInited ? FileUtils::BrowseToFile(&fFile) : kFailure);
}

bool FileLinkResourceHandler::CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const
{
	return kTrue;
}

bool FileLinkResourceHandler::GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const
{
	IDFile file = fFile;

	if (file.Exists())
		return Utils<ILinkUtils>()->GetXMPPacket(file, packet);
	else
		return kFalse;	
}

bool FileLinkResourceHandler::CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

bool FileLinkResourceHandler::CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

ErrorCode FileLinkResourceHandler::DownloadOriginalResource(const UIDRef& ref, const URI& uri) const
{
	return kFailure;
}

ErrorCode FileLinkResourceHandler::AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const
{
	return kFailure;
}

bool FileLinkResourceHandler::CanProvideFile(const UIDRef& ref, const URI& uri) const
{
	return kTrue;
}

ErrorCode FileLinkResourceHandler::GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const
{
	idFile = fFile;
	return kSuccess;
}
