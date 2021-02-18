//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/commondata/CPersistUIDRefData.cpp $
//  
//  Owner: brendan
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
//  Description : Persistent UID Data, very similar to PersistUIDData, but 
//  the read/write method does a XferReference instead of a 
//  XferObject (which is what PersistUIDData does).
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "CPersistUIDRefData.h"
#include "ShuksanID.h"
#include "IPMStream.h"

/** A "nil" value for UIDRefs -- a valid UIDRef will never be equal to kInvalidUIDRef. */
const UIDRef kInvalidUIDRef(nil, kInvalidUID);

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PERSIST_PMINTERFACE(CPersistUIDRefData, kCPersistUIDRefDataImpl)

DEFINE_HELPER_METHODS(CPersistUIDRefData)

CPersistUIDRefData::CPersistUIDRefData(IPMUnknown* boss) :
	HELPER_METHODS_INIT(boss),
	fUID(kInvalidUID)
{

}


CPersistUIDRefData::~CPersistUIDRefData()
{

}


void CPersistUIDRefData::SetUID (const UID& id) 
{
	if (fUID != id)
	{
		PreDirty (kCPersistUIDRefDataImpl);
		fUID = id;
	}
}



UID CPersistUIDRefData::GetUID () const
{
	return fUID;
}


void CPersistUIDRefData::ReadWrite (IPMStream* iPMStream, ImplementationID)
{
	iPMStream->XferReference (fUID);
}

//note: we need this second implementation because some bosses
// were using kPersistUIDRefDataImpl twice, which isn't allowed -ldb 11/18/98
class CPersistUIDRefData2 : public CPersistUIDRefData
{
public:
	CPersistUIDRefData2(IPMUnknown* boss):CPersistUIDRefData(boss){}
};

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PERSIST_PMINTERFACE(CPersistUIDRefData2, kCPersistUIDRefDataImpl2)


// To be safe for Sherpa, we added a #3 version of this to
// avoid possible conflicts with third party plug-ins that
// may have been already adding in this persistent interface implementation.
class CPersistUIDRefData3 : public CPersistUIDRefData
{
public:
	CPersistUIDRefData3(IPMUnknown* boss):CPersistUIDRefData(boss){}
};

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PERSIST_PMINTERFACE(CPersistUIDRefData3, kCPersistUIDRefDataImpl3)
