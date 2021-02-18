//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkAssetConverter.h $
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

#pragma once
#ifndef __CusDtLnkLinkResourceConverter__
#define __CusDtLnkLLinkResourceConverter__

// ----- Includes -----
#include "ILinkResource.h"

#include "CPMUnknown.h"
#include "IDTime.h"
#include "WideString.h"
#include "URI.h"

class FileTypeInfo;
class IPMStream;
class IDataLink;

//========================================================================================
// Class CusDtLnkLinkAssetConverter
//========================================================================================
class CusDtLnkLinkAssetConverter : public CPMUnknown<ILinkResource>
{
public:
	typedef CPMUnknown<ILinkResource> inherited;

	CusDtLnkLinkAssetConverter(IPMUnknown* boss);
	virtual ~CusDtLnkLinkAssetConverter();

	virtual ResourceId GetURI() const { return fId; }
	virtual ResourceId GetId() const { return fId; }
	virtual bool IsIdEquivalent(const ResourceId& id) const { ASSERT_UNIMPLEMENTED(); return false; }

	virtual LinkClientID GetClientID() const { return fClientId; }

	virtual WideString GetShortName(bool bUIName) const;
	virtual WideString GetLongName(bool bUIName) const;

	virtual ResourceState GetState() const { return fState; }
	virtual void SetState(ResourceState state);

	virtual ResourceStoreState GetStoreState() const { return fStoreState; }
	virtual void SetContainedInObject() { ASSERT_UNIMPLEMENTED(); }

	virtual ResourceStamp GetStamp() const { return fStamp; }
	virtual void SetStamp(const ResourceStamp& stamp);
	virtual bool IsStampEquivalent(const ResourceStamp& stamp) const;

	virtual IDTime GetModTime() const { return fModTime; };
	virtual void SetModTime(const IDTime& time);

	virtual uint64 GetSize() const { return fSize; }
	virtual void SetSize(uint64 size);

	virtual FileTypeInfo GetDataType() const;
	virtual PMString GetFormatType() const { return fFormatType; }
	virtual void SetFormatType(const PMString& formatType);

	virtual bool IsAccessSupported(AccessMode mode) const;
	virtual bool CanQueryStream(AccessMode mode) const;
	virtual IPMStream* QueryStream(AccessMode mode) const;

	virtual bool CanCache() const {ASSERT_UNIMPLEMENTED(); return false;}
	virtual ErrorCode Cache() {ASSERT_UNIMPLEMENTED(); return kFailure;}
	virtual ErrorCode Uncache() {ASSERT_UNIMPLEMENTED(); return kFailure;}

	virtual bool CanEmbed() const {ASSERT_UNIMPLEMENTED(); return false;}
	virtual ErrorCode Embed() {ASSERT_UNIMPLEMENTED(); return kFailure;}

	virtual bool CanUnembed() const {ASSERT_UNIMPLEMENTED(); return false;}
	virtual ErrorCode Unembed() {ASSERT_UNIMPLEMENTED(); return kFailure;}

	virtual bool CanCopyToFile() const { ASSERT_UNIMPLEMENTED(); return false; }
	virtual ErrorCode CopyToFile(IDFile& file) const { ASSERT_UNIMPLEMENTED(); return kFailure; }

	virtual bool CanEdit() const {return false;}
	virtual ErrorCode Edit(const AppInfo& appInfo, PMString* errorString) {ASSERT_UNIMPLEMENTED(); return kFailure;}

	virtual bool CanReveal() const { return false; }
	virtual ErrorCode Reveal() { ASSERT_UNIMPLEMENTED(); return kFailure; }
	virtual bool CanRevealInBridge() const { return false; }
	virtual ErrorCode RevealInBridge() { ASSERT_UNIMPLEMENTED(); return kFailure; }
	virtual bool CanRevealInCloudLibraries() const { return false; }
	virtual ErrorCode RevealInCloudLibraries() { ASSERT_UNIMPLEMENTED(); return kFailure; }

	virtual bool IsFPO() const { return false; }
	virtual bool CanGetXMPPacketInfo() const { return false; }
	virtual bool GetXMPPacketInfo(std::string& packet) const { return false; }
	virtual ResourceDownloadState GetDownloadProgress(PMReal& progress) const { return ILinkResource::kComplete; }
	virtual bool CanDownloadOriginal() const { return false; }
	virtual ErrorCode DownloadOriginal() { return kFailure; }
	virtual ErrorCode AsyncDownloadOriginal(ILinkResource::DownloadCompletionFunction completionFunction) { return kFailure; }
	virtual bool CanReplaceFPOWithOriginal() const { return false; }
	virtual bool CanProvideFile() const { return false; }
	virtual ErrorCode GetFile(IDFile& idFile) const { return kFailure; }

	virtual void AddChildren(const UIDList& children) { ASSERT_UNIMPLEMENTED(); return; }
	virtual void DeleteChildren(const UIDList& children) { ASSERT_UNIMPLEMENTED(); return; }
	virtual uint32 GetChildren(UIDList& children) const { ASSERT_UNIMPLEMENTED(); return 0; }
	virtual uint32 GetNumChildren() const { ASSERT_UNIMPLEMENTED(); return 0; }

	virtual uint32 GetParents(UIDList& parents) const { ASSERT_UNIMPLEMENTED(); return 0; }

	virtual ErrorCode CopyAttributes(const UIDRef& resourceRef);

	virtual ErrorCode EmbedFromStream(IPMStream* stream) { ASSERT_UNIMPLEMENTED(); return kFailure; }

	//	Specific to this implementation only
	virtual ErrorCode Init(IDataLink* iDataLink, const URI& uri);
	virtual bool CanGetLinkInstance() const { return false; };
	virtual ErrorCode GetlinkInstance(PMString &pmStr) const { return kFailure; };

private:
	// Prevent copy construction and assignment.
	CusDtLnkLinkAssetConverter(const CusDtLnkLinkAssetConverter&);
	CusDtLnkLinkAssetConverter& operator=(const CusDtLnkLinkAssetConverter&);

	virtual ErrorCode Init(LinkClientID clientId, const URI& uri,  const ClassID& providerId) { ASSERT_UNIMPLEMENTED(); return kFailure; }
	virtual ErrorCode SoftInit(const ResourceId& resourceId) { ASSERT_UNIMPLEMENTED(); return kFailure; }
	virtual void DeleteOwnedObjects() { ASSERT_UNIMPLEMENTED(); }

	bool GetCurrentTimeAndSizeFromURI(ATime& currentTime, uint64& currentSize);
	bool ConstructStampFromURI(WideString& newStamp);
	void ConstructStampFromTimeSize(ATime storedTime, uint64 storedSize, WideString& newStamp);
	
	bool TimeStampsCloseEnough(uint64 storedTimeStamp, uint64 currentTimeStamp);

	// Stream query methods
	IPMStream* QueryReadStream() const;


	// Member variables
	IDataBase*			fDB;

	ResourceId			fId;
	LinkClientID		fClientId;
	uint64				fSize;
	IDTime				fModTime;
	ResourceState		fState;
	ResourceStamp		fStamp;
	PMString			fFormatType;
	ResourceStoreState	fStoreState;
	UID					fStoredResourceUID;
};

#endif // __CusDtLnkLinkResourceConverter__
