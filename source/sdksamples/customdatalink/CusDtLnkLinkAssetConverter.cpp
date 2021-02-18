//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkAssetConverter.cpp $
//  
//  Owner: SusanCL
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

#include "CusDtLnkLinkAssetConverter.h"
#include "ILinkResource.h"

#include "IDataBase.h"
#include "IPMStream.h"
#include "IURIUtils.h"

#include "IDatalink.h"
#include "IStoreInternal.h"
#include "ILinkObjectReference.h"
#include "NAMEINFO.H"
#include "ICusDtLnkFacade.h"


#include "FileTypeInfo.h"
#include "ShuksanID.h"
#include "StreamUtil.h"
#include "FileUtils.h"
#include "URI.h"
#include "Utils.h"

#include "StringNumeric.h"
#include "WideString.h"
#include "PMString.h"
#include "CusDtLnkID.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif


CREATE_PMINTERFACE(CusDtLnkLinkAssetConverter, kCusDtLnkLinkAssetConverterImpl)

//========================================================================================
//
// CusDtLnkLinkAssetConverter Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkAssetConverter::CusDtLnkLinkAssetConverter(IPMUnknown* boss)
: inherited(boss),
  fDB(::GetDataBase(boss)),
  fClientId(kIDLinkClientID),
  fState(kUnknown),
  fStoreState(kNormal),
  fStoredResourceUID(kInvalidUID)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkAssetConverter::~CusDtLnkLinkAssetConverter()
{

}

//========================================================================================
// CusDtLnkLinkAssetConverter::SetSize
//========================================================================================
void CusDtLnkLinkAssetConverter::SetSize(uint64 size)
{
	if (fSize != size) {
		fSize = size;
	}
}

//========================================================================================
// CusDtLnkLinkAssetConverter::SetModTime
//========================================================================================
void CusDtLnkLinkAssetConverter::SetModTime(const IDTime& time)
{
	if (fModTime != time) {
		fModTime = time;
	}
}

//========================================================================================
// CusDtLnkLinkAssetConverter::SetState
//========================================================================================
void CusDtLnkLinkAssetConverter::SetState(ResourceState state)
{
	if (state == kUnknown)
	{
		ASSERT_FAIL("CusDtLnkLinkAssetConverter::SetState() - kUnknown is a reserved state, and cannot be set!");
		return;
	}

	if (fState != state) 
	{
		fState = state;
	}
}

//========================================================================================
// CusDtLnkLinkAssetConverter::SetStamp
//========================================================================================
void CusDtLnkLinkAssetConverter::SetStamp(const ResourceStamp& stamp)
{
	fStamp = stamp;
}

//========================================================================================
// CusDtLnkLinkAssetConverter::IsStampEquivalent
//========================================================================================
bool CusDtLnkLinkAssetConverter::IsStampEquivalent(const ResourceStamp& stamp) const
{
	return (fStamp == stamp);
}

//========================================================================================
// CusDtLnkLinkAssetConverter::GetShortName
//========================================================================================
WideString CusDtLnkLinkAssetConverter::GetShortName(bool) const
{
	IDFile file;
	Utils<ICusDtLnkFacade>()->URIToIDFile(fId, file);

	AString name(file.GetNameStr());
	return WideString(name.GrabWString(), name.UTF16Count(), name.CharCount());
}

//========================================================================================
// CusDtLnkLinkAssetConverter::GetLongName
//========================================================================================
WideString CusDtLnkLinkAssetConverter::GetLongName(bool) const
{
	WideString dbPath = fId.GetComponent(URI::kPath);
	PMString dpath(dbPath);
	PMString dbName = Utils<ICusDtLnkFacade>()->TruncatePath(dpath);
	
	WideString recordID = fId.GetComponent(URI::kQuery);

	IDFile file;
	URIUTILS->URIToIDFile(fId, file);
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
// CusDtLnkLinkAssetConverter::GetDataType
//========================================================================================
FileTypeInfo CusDtLnkLinkAssetConverter::GetDataType() const
{
	IDFile file;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(fId, file)) {
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
// CusDtLnkLinkAssetConverter::SetFormatType
//========================================================================================
void CusDtLnkLinkAssetConverter::SetFormatType(const PMString& formatType)
{
	if (fFormatType != formatType)
	{
		fFormatType = formatType;
	}
}


//========================================================================================
// CusDtLnkLinkAssetConverter::IsAccessSupported
//========================================================================================
bool CusDtLnkLinkAssetConverter::IsAccessSupported(AccessMode mode) const
{
	if (mode == kRead)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//========================================================================================
// CusDtLnkLinkAssetConverter::CanQueryStream
//========================================================================================
bool CusDtLnkLinkAssetConverter::CanQueryStream(AccessMode mode) const
{
	if (mode == kRead)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//========================================================================================
// CusDtLnkLinkAssetConverter::QueryStream
//========================================================================================
IPMStream* CusDtLnkLinkAssetConverter::QueryStream(AccessMode mode) const
{
	switch (mode) {
		case kRead:
			return QueryReadStream();
			break;
		default:
			ASSERT_FAIL("CusDtLnkLinkAssetConverter::QueryStream() - Unsupported or unrecognized access mode!");
			break;
	}

	return nil;
}


//========================================================================================
// CusDtLnkLinkAssetConverter::CopyAttributes
//========================================================================================
ErrorCode CusDtLnkLinkAssetConverter::CopyAttributes(const UIDRef& resourceRef)
{
	return kFailure;
}


//========================================================================================
// CusDtLnkLinkAssetConverter::Init
//========================================================================================
ErrorCode CusDtLnkLinkAssetConverter::Init (IDataLink* iDataLink, const URI& uri)
{
	NameInfo	nameInfo;
	PMString	formatName;
	uint32		fileType;
	ErrorCode	errorCode = iDataLink->GetNameInfo (&nameInfo, &formatName, &fileType);

	fId = uri;

	if (errorCode == kSuccess)
	{
		uint64		storedSize = 0;
		uint64		storedTime = 0;
		IDataLink::StateType	calculatedType = IDataLink::kLinkNormal;
		IDataLink::StateType	oldStoredType = iDataLink->GetStoredState (&storedSize, &storedTime);

		uint64		modTime = 0;

		//	Check if times are consistent or close enough.
		ResourceStamp	resourceStamp;
		if (oldStoredType != IDataLink::kEmbedded)
		{
			uint64		currentSize = 0;
			uint64		currentTime = 0;
			bool16		fileExists = GetCurrentTimeAndSizeFromURI (currentTime, currentSize);

			if (fileExists)
			{
				bool	hasStamp = ConstructStampFromURI (resourceStamp);
				ASSERT (hasStamp);

				if (storedSize != currentSize || TimeStampsCloseEnough (storedTime, currentTime) == false)
				{
					//ASSERT (oldStoredType == IDataLink::kLinkOutOfDate);

					ConstructStampFromTimeSize (storedTime, storedSize, resourceStamp);
					modTime = storedTime;

					if (oldStoredType != IDataLink::kLinkOutOfDate)
					{
						calculatedType = IDataLink::kLinkOutOfDate;
						iDataLink->SetStoredState (nil, nil, calculatedType);
					}
				}
				else
				{
					modTime = currentTime;
				}
			}
			else
			{
				//	File does not exist.
				// the persisted type can easily be different from the current type.

				calculatedType = IDataLink::kLinkMissing;
				ConstructStampFromTimeSize (storedTime, storedSize, resourceStamp);
				modTime = storedTime;
			}
		}
		else
		{
			//	Embedded
			calculatedType = IDataLink::kEmbedded;
			ConstructStampFromTimeSize (storedTime, storedSize, resourceStamp);
			modTime = storedTime;
		}

		SetSize(storedSize);

		// the persisted type can easily be different from the current type.
		// commenting out assert. dstephens 06/06/2007
		//ASSERT (calculatedType == oldStoredType);

		ILinkResource::ResourceState	state = (oldStoredType == IDataLink::kLinkMissing) ? kMissing : kAvailable;

		//	Set attributes
		SetFormatType(formatName);
		SetModTime(modTime);
		SetStamp(resourceStamp);
		SetState(state);

		//	Embeded
		if (oldStoredType == IDataLink::kEmbedded)
		{
			InterfacePtr<ILinkObjectReference>	iOldObjectRef (iDataLink, UseDefaultIID ());
			if (iOldObjectRef != nil && iOldObjectRef->GetUID () != kInvalidUID)
			{
				InterfacePtr<IStoreInternal>	iStoreInternal (fDB, iOldObjectRef->GetUID (), IID_ISTOREINTERNAL);
				
				//	Delete old stored data
				UID		storedUID = iStoreInternal->GetStoredUID ();
				if (storedUID != kInvalidUID && fDB->IsValidUID (storedUID))
				{
					//iStoreInternal->SetStoredUID (kInvalidUID);
					fStoreState = kEmbedded;
					SetState(kAvailable);
					fStoredResourceUID = storedUID;
				}
			}
		}
	}

	return errorCode;
}


//========================================================================================
//
// CusDtLnkLinkAssetConverter Private Implementation
//
//========================================================================================

//========================================================================================
// CusDtLnkLinkAssetConverter::QueryReadStream
//========================================================================================
IPMStream* CusDtLnkLinkAssetConverter::QueryReadStream() const
{
	if (fStoredResourceUID != kInvalidUID)
	{
		return StreamUtil::CreateDBStreamRead(fDB, fStoredResourceUID);;
	}

	return nil;
}

//========================================================================================
// CusDtLnkLinkAssetConverter::GetCurrentTimeAndSizeFromURI
//========================================================================================
bool CusDtLnkLinkAssetConverter::GetCurrentTimeAndSizeFromURI(ATime& currentTime, uint64& currentSize)
{
	IDFile	file;
	Utils<ICusDtLnkFacade>()->URIToIDFile(fId, file);
	bool bFileExists(file.Exists());

	currentTime = 0;
	currentSize = 0;
	if (bFileExists)
	{
		currentTime = Utils<ICusDtLnkFacade>()->GetAssetTimestampFromURI(fId);
		currentSize = file.GetSize();
	}

	return bFileExists;
}

//========================================================================================
// CusDtLnkLinkAssetConverter::ConstructStampFromURI
//========================================================================================
bool CusDtLnkLinkAssetConverter::ConstructStampFromURI(WideString& newStamp)
{
	ATime	modifiedTime (0);
	uint64	size (0);
	bool bFileExists = GetCurrentTimeAndSizeFromURI(modifiedTime, size);

	if (bFileExists)
	{
		ConstructStampFromTimeSize(modifiedTime, size, newStamp);
	}

	return (bFileExists);
}

//========================================================================================
// CusDtLnkLinkAssetConverter::ConstructStampFromTimeSize
//========================================================================================
static const WideString k_ConstructStampFromTimeSize_scheme(kCusDtLnkScheme);
void CusDtLnkLinkAssetConverter::ConstructStampFromTimeSize(ATime time, uint64 size, WideString& newStamp)
{

	// update the resource's stamp
	newStamp.clear ();
	newStamp.Append(k_ConstructStampFromTimeSize_scheme);

	WideString modTimeStr;
	if (stringnumeric::ToString(time, modTimeStr) == kSuccess)
	{
		newStamp.Append(modTimeStr);
	}
	else
	{
		ASSERT_FAIL ("CusDtLnkLinkAssetConverter::ConstructStampFromTimeSize - mod time to WideString failed!");
	
		WideString	dummy ("0000");
		newStamp.Append (dummy);
	}
	
	newStamp.Append(WideString(" "));

	WideString sizeStr;
	if (stringnumeric::ToString(size, sizeStr) == kSuccess)
	{
		newStamp.Append(sizeStr);
	}
	else
	{
		ASSERT_FAIL ("CusDtLnkLinkAssetConverter::ConstructStampFromTimeSize - File size to WideString failed!");

		WideString	dummy ("0000");
		newStamp.Append (dummy);
	}

}

//========================================================================================
// CusDtLnkLinkAssetConverter::TimeStampsCloseEnough
//========================================================================================
bool CusDtLnkLinkAssetConverter::TimeStampsCloseEnough(uint64 storedTimeStamp, uint64 currentTimeStamp)
{
	if (storedTimeStamp == currentTimeStamp)
		return true;

	//	If the time stamps are not the same, then we check to see how close the times are.
	//	This hueristic is copied from the old DataLink code.
	//	The reasoning is as follows:
	//		Moving a file from NTFS to FAT makes the links modified because the
	//		time resolution on FAT is 2 second intervals and NTFS is 100 nanoseconds.
	//		There are (normal?) cases where the time stamp on different files are very close together.
	//		For example, QA's test files as they are copied out of Perforce are given the system's
	//		current time.  We don't want to sometimes say the link is up-to-date after you relink
	//		to a different file.


	// Get the time resolution of the file and compare at it's resolution.
	// Compare at 2 second intervals when one of the timestamps doesn't have any fractions of a second.
	if (currentTimeStamp % (uint64)GlobalTime::kOneSecond &&
		storedTimeStamp % (uint64)GlobalTime::kOneSecond)
		return false;  // Both have fractions of a second, we are not lax in this situation, must be exact.

	// Get the seconds, no fractions of a second.
	storedTimeStamp = storedTimeStamp / (uint64)GlobalTime::kOneSecond;
	currentTimeStamp = currentTimeStamp / (uint64)GlobalTime::kOneSecond;

	uint64 diff;
	if (storedTimeStamp > currentTimeStamp)
		diff = storedTimeStamp - currentTimeStamp;
	else
		diff = currentTimeStamp - storedTimeStamp;
	// diff is positive

	if (diff <= 2)
	{
		// OK, one time stamp doesn't have any fractions of a second
		// and the other one is within two seconds, well give it to you.

		return true; // The time stamps are close enough.
	}

	// If the difference is less than a day, check further.
	if (diff < 24 * 3600 + 2)
	{
		// Off by an hour is common when moving between Mac and Windows.  Off by 23 and 24 hours
		// occurs too but much less frequently.

		// Is the difference one hour plus or minus 2 seconds?
		if (diff > 3600 - 2 && diff < 3600 + 2)
			return true;

		// Is the difference 23 hours plus or minus 2 seconds?
		if (diff > 23 * 3600 - 2 && diff < 23 * 3600 + 2)
			return true;

		// Is the difference 24 hours plus or minus 2 seconds?
		if (diff > 24 * 3600 - 2 /*already done above && diff < 24 * 3600 + 2*/ )
			return true;
	}

	return false; // The time stamps are not the same.
}
