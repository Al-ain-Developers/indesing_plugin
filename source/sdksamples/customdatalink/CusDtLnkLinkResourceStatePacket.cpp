//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceStatePacket.cpp $
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

#include "VCPluginHeaders.h"
#include "CusDtLnkLinkResourceStatePacket.h"


//========================================================================================
//
// CusDtLnkLinkResourceStatePacket Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceStatePacket::CusDtLnkLinkResourceStatePacket(ILinkManager::OperationType opType,
												 bool bNotify,
												 IDataBase* db,
												 const UID& uid,
												 const URI& uri,
												 ILinkResource::ResourceState state,
												 const WideString& stamp,
												 const IDTime& modTime,
												 uint64 size)
: fOpType(opType),
  fbNotify(bNotify),
  fDB(db),
  fUID(uid),
  fURI(uri),
  fState(state),
  fStamp(stamp),
  fModTime(modTime),
  fSize(size),
  fURIChanged(false),
  fStateChanged(false),
  fStampChanged(false),
  fModTimeChanged(false),
  fSizeChanged(false)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkResourceStatePacket::~CusDtLnkLinkResourceStatePacket()
{
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::operator==
//========================================================================================
bool CusDtLnkLinkResourceStatePacket::operator==(const CusDtLnkLinkResourceStatePacket& rhs) const
{
	if (&rhs == this) {
		return true;
	}

	// only check the database and UID of the link resource,
	// since all the work packets are keyed by the database
	// and UID only
	return (fDB == rhs.fDB && fUID == rhs.fUID);
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::SetURI
//========================================================================================
void CusDtLnkLinkResourceStatePacket::SetURI(const URI& uri)
{
	if (fURI != uri) {
		fURI = uri;
		fURIChanged = true;
	}
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::SetState
//========================================================================================
void CusDtLnkLinkResourceStatePacket::SetState(ILinkResource::ResourceState state)
{
	if (fState != state) {
		fState = state;
		fStateChanged = true;
	}
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::SetStamp
//========================================================================================
void CusDtLnkLinkResourceStatePacket::SetStamp(const WideString& stamp)
{
	if (fStamp != stamp) {
		fStamp = stamp;
		fStampChanged = true;
	}
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::SetModTime
//========================================================================================
void CusDtLnkLinkResourceStatePacket::SetModTime(const IDTime& modTime)
{
	if (fModTime != modTime) {
		fModTime = modTime;
		fModTimeChanged = true;
	}
}

//========================================================================================
// CusDtLnkLinkResourceStatePacket::SetSize
//========================================================================================
void CusDtLnkLinkResourceStatePacket::SetSize(uint64 size)
{
	if (fSize != size) {
		fSize = size;
		fSizeChanged = true;
	}
}
