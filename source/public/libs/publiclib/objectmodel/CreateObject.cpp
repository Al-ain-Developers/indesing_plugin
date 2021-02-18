//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/objectmodel/CreateObject.cpp $
//  
//  Owner: mburbidg
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


// ----- Interface Includes -----

#include "IClassInfo.h"
#include "IControlView.h"
// ----- Implementation Includes -----

#include "StreamUtil.h"
#include "RsrcSpec.h"
#include "PMTypes.fh"
#ifdef DEBUG
#include "DebugClassUtils.h"
#endif

#include "CoreResTypes.h"

// ***************************************************************************************************
// Drover based widgets created/read from resources need a context to indicate to the panel control
// data that there is an underlying UI_Node off this boss. This is so things get addref'd properly.
// During stream resource read, an extra addref on the IControlView interface keeps the drover based
// widget boss from being immediately destroyed since at present, unlike our old platform based
// widgets, we don't allow drover based widgets in the instance cache. This AddRef is compensated
// for in DVControlPanelData::ReadWrite.

namespace ResourceStreamReadContext
{
    static bool16 gActiveResourceStreamReadContext = kFalse;
    
    void BeginResourceStreamReadContext()
    {
        ASSERT_MSG(gActiveResourceStreamReadContext == kFalse, "BeginResourceStreamReadContext - a context is already active!");
        gActiveResourceStreamReadContext = kTrue;
    }
    
    void EndResourceStreamReadContext()
    {
        gActiveResourceStreamReadContext = kFalse;
    }
    
    bool16 IsResourceStreamReadContextActive()
    {
        return gActiveResourceStreamReadContext;
    }
} // using namespace ResourceStreamReadContext

// ***************************************************************************************************

IPMUnknown* CreateObject(ClassID id, PMIID iid, const IObjectModel*om)
{
	ASSERT(om != nil);

 	return om->ConstructObject(id, iid);
}

IPMUnknown* CreateObject(IDataBase* db, ClassID id, PMIID iid)
{
	IPMUnknown* widget = nil;
	
	if (db)
	{
		UID uid = db->NewUID(id);
		widget = db->Instantiate(uid, iid);
		if(!widget)
		{
			// caller has no way to clean up this UID...so we'd better do it
			db->DeleteUID(uid);
			db->DestroyDeletedUID(uid);
		}
	}
	else
		widget = ::CreateObject(id, iid);

	return widget;
}


IPMUnknown* CreateObjectNoInit (IDataBase* db, const RsrcSpec& spec, PMIID returnIID, const IObjectModel*om)
{
    IPMUnknown* pObj(nil);
    
	ASSERT_MSG(db != 0, "CreateObject - database required to create object from resource");
	ASSERT_MSG(spec.GetType() == kViewRsrcType,"CreateObject called for wrong resourceType");

    // cache the initial state of the stream read context locally in this method, we only want to Begin/End
    // the context on the object's very first call to CreateObjectNoInit (since this method can call itself
    // when the object's sub-objects(widgets) get created)
    bool16 bResourceStreamReadContextActive = ResourceStreamReadContext::IsResourceStreamReadContextActive();
    
    if ( !bResourceStreamReadContextActive )
        ResourceStreamReadContext::BeginResourceStreamReadContext();
    
	InterfacePtr<IPMStream> stream((IPMStream*) StreamUtil::CreateObjectResourceStreamRead(spec, db));
	if (stream != 0)
	{
		ClassID classId = stream->XferInt32((int32&) classId);

		InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);
		InterfacePtr<IClassInfo> clsInfo(om->QueryClassInfo(classId));
		
		UID uid = db->NewUID(classId);
		InterfacePtr<IPMUnknown> newObj(db, uid, IID_IUNKNOWN);
		if(newObj)
		{
			int16 spacer = stream->XferInt16(spacer);
			ASSERT_MSG(spacer == kMagicInterfacePadding,"Some interface read wrong amount");

			while (kTrue)
			{
				PMIID iid = stream->XferInt32((int32&) iid);
				if (stream->GetStreamState() != kStreamStateGood)
				{
//#ifdef DEBUG				
//					DebugClassUtilsBuffer classBuf,iidBuf;
//					ASSERT_FAIL(FORMAT_ARGS("CreateObjectNoInit not reading data for IID %s in class %s because stream state is %d.\n",DebugClassUtils::GetIDName(&iidBuf, iid),DebugClassUtils::GetIDName(&classBuf,classId),stream->GetStreamState()));
//#endif
					break;
				}
					
				ImplementationID implId = clsInfo->GetImplementation(iid);
				if(implId == kInvalidImpl)
				{
#ifdef DEBUG
					DebugClassUtilsBuffer buf1,buf2;
					ASSERT_FAIL(FORMAT_ARGS("CreateObject- Trying to read data for class %s in plugin %x, can't find impl for IID %s",
						DebugClassUtils::GetIDName(&buf1,classId),spec.GetPluginID().Get(),DebugClassUtils::GetIDName(&buf2,iid)));
#endif
					break;
				}
				StackBasedReadWritePtr readWriter(om, implId);
				
				if (readWriter.GetReadWrite() == nil)
				{
#ifdef DEBUG
					DebugClassUtilsBuffer buf1,buf2,buf3;
					ASSERT_FAIL(FORMAT_ARGS("CreateObject- Trying to read data for class %s in plugin %s, failed to get ReadWrite for Impl %s",
						DebugClassUtils::GetIDName(&buf1,classId),DebugClassUtils::GetIDName(&buf2,spec.GetPluginID()),DebugClassUtils::GetIDName(&buf3,implId)));
#endif
					break;
				}
				InterfacePtr<IPMUnknown> unknown(db, uid, iid);
				if (unknown != nil)	
				{
					::PreDirty(unknown);					
					(*readWriter)(unknown, stream, implId, 0);

#ifdef DEBUG
					if(stream->GetStreamState() != kStreamStateGood)
					{
						DebugClassUtilsBuffer buf1,buf2;
						ASSERT_FAIL(FORMAT_ARGS("CreateObject- ReadWrite for impl %s in class %s read past end of resource in plugin %x",
							DebugClassUtils::GetIDName(&buf1,implId),DebugClassUtils::GetIDName(&buf2,classId),spec.GetPluginID().Get()));
					}
#endif
					stream->XferInt16(spacer);
#ifdef DEBUG
					if(stream->GetStreamState() == kStreamStateGood && spacer != kMagicInterfacePadding)
					{
						DebugClassUtilsBuffer buf1,buf2;
						ASSERT_FAIL(FORMAT_ARGS("CreateObject- ReadWrite for impl %s in class %s read wrong amount in plugin %x",
							DebugClassUtils::GetIDName(&buf1,implId),DebugClassUtils::GetIDName(&buf2,classId),spec.GetPluginID().Get()));
					}
#endif
				}
			}

					
			pObj = newObj->QueryInterface(returnIID);
		}
	}

    if ( !bResourceStreamReadContextActive )
        ResourceStreamReadContext::EndResourceStreamReadContext();
    
	return pObj;
}



IPMUnknown* CreateObject(IDataBase* db, const RsrcSpec& spec, PMIID returnIID, const IObjectModel*om)
{
	IPMUnknown *returnVal = CreateObjectNoInit (db, spec, returnIID, om);
	if (returnVal)
	{
		// ----- We should consider generalizing this, into some initialization interface that
		//		 if it exists is called after an object is created. This is important for objects
		//		 that are part of a network or hierarchy of objects and need an init method
		//		 that is called after the network or hierarchy is created. [amb]
		InterfacePtr<IControlView> view(returnVal, UseDefaultIID());
		if (view)
			view->DoPostCreate();		
	}
	return returnVal;
}
