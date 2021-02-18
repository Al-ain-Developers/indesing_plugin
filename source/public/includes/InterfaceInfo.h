//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfaceInfo.h $
//  
//  Owner: Robin_Briggs
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
//  Wraps interface information for a class.
//  
//========================================================================================

#pragma once
#ifndef __InterfaceInfo__
#define __InterfaceInfo__

#include "OMTypes.h"
#include "IPMStream.h"
#include "PersistBaseTypes.h"
#include "IPlugIn.h"

extern IPlugIn::ThreadingPolicy GetPluginThreadingPolicy(PluginID pluginID);

/** Wraps interface information for a class.
*/
class InterfaceInfo {
public: 
	typedef base_type data_type;
	
	InterfaceInfo() :
#ifdef USE_ALLOCATE_WITH_BOSS
		fFaceID(IID_IUNKNOWN), fImplID(kInvalidImpl), fOwner(kInvalidPlugin), fIsAddin(kFalse), fOffset(0), fThreadingPolicy(IPlugIn::kUnknownThreadingPolicy)
#else
    fFaceID(IID_IUNKNOWN), fImplID(kInvalidImpl), fOwner(kInvalidPlugin), fIsAddin(kFalse), fThreadingPolicy(IPlugIn::kUnknownThreadingPolicy)
#endif
	{
	}
	
#ifdef USE_ALLOCATE_WITH_BOSS
	InterfaceInfo(PMIID faceID, ImplementationID implID, PluginID owner, bool isAddin, int32 offset) :
    fFaceID(faceID), fImplID(implID), fOwner(owner), fIsAddin(isAddin), fOffset(offset)
#else
    InterfaceInfo(PMIID faceID, ImplementationID implID, PluginID owner, bool isAddin) :
    fFaceID(faceID), fImplID(implID), fOwner(owner), fIsAddin(isAddin)
#endif
	{
		ASSERT_MSG(implID != kInvalidImpl,"Creating interfaceInfo with kInvalidImpl");
		fThreadingPolicy = ::GetPluginThreadingPolicy(fOwner);
	}
	
	PMIID GetInterface() const { return fFaceID; }
	ImplementationID GetImplementation() const { return fImplID; }
	PluginID GetOwnerComponent() const { return fOwner; }
#ifdef USE_ALLOCATE_WITH_BOSS
	int32 GetOffset() const { return fOffset; }
	void SetOffset(int32 newOffset) { fOffset = newOffset; }
#endif
	bool IsAddin() const { return fIsAddin; }
	IPlugIn::ThreadingPolicy GetThreadingPolicy() const { return fThreadingPolicy; }
	void ReadWrite(IPMStream *s)
	{
		s->XferID(fFaceID);
		s->XferID(fImplID);
		s->XferID(fOwner);
#ifdef USE_ALLOCATE_WITH_BOSS
		s->XferInt32(fOffset);
#endif
		s->XferEnum(fThreadingPolicy);
	}

private:
	PMIID fFaceID;
	ImplementationID fImplID;
	PluginID fOwner;			// ID of the plugin who added this interface to the boss.
#ifdef USE_ALLOCATE_WITH_BOSS
	int32 fOffset;
#endif
	IPlugIn::ThreadingPolicy fThreadingPolicy; // specifies if threading policy for this interface
    bool fIsAddin;
};

// Persistence
namespace Persist
{
	template<>
	inline void Read<InterfaceInfo>(IPMStream* stream, InterfaceInfo& entry)
	{
		ASSERT (stream && stream->IsReading());
		entry.ReadWrite(stream);
	}
	
	template<>
	inline void Write<InterfaceInfo>(IPMStream* stream, const InterfaceInfo& entry)
	{
		ASSERT (stream && stream->IsWriting());
		const_cast<InterfaceInfo&>(entry).ReadWrite(stream);
	}
}


#endif // __InterfaceInfo__



