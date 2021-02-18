//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/PersistUtils.cpp $
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
//  Utilities for getting objects' persistent identity.
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "IClassInfo.h"
#include "IPMStream.h"
#include "AppUIID.h"
#include "SoapServerID.h"
#include "AppFrameworkID.h"

#include "ErrorUtils.h"
#include "MemUtils.h"
#include "Product.h"

namespace
{
	// Optimized version for ClassIsDescendantOf that takes the object model
	bool16 ClassIsDescendantOf(const ClassID& anscestor, const ClassID& descendant, const IObjectModel* om)
	{
		ASSERT(om);

		InterfacePtr<IClassInfo> clsInfo(om->QueryClassInfo(descendant));

		if(clsInfo)
		{
			ClassID parent = clsInfo->GetParentClass();
			if (parent == anscestor)
				return kTrue;
			else if (parent == kInvalidClass)
				return kFalse;
			else
				return ClassIsDescendantOf(anscestor, parent, om);
		}
		else
			return kFalse;
	}
}

const UIDRef UIDRef::gNull(nil, kInvalidUID);

UID GetUID( const IPMUnknown *obj)
{
	InterfacePtr<const IControllingUnknown> boss(obj, IID_ICONTROLLINGUNKNOWN);
	if (boss)
	{
		const IPMPersist *persist = boss->GetPersist();
		if (persist)
			return persist->GetUID();
	}
	return kInvalidUID;
}


IDataBase *GetDataBase(const IPMUnknown *obj)
{
	InterfacePtr<const IControllingUnknown> boss(obj, IID_ICONTROLLINGUNKNOWN);
	if (boss)
	{
		const IPMPersist *persist = boss->GetPersist();
		if (persist)
			return persist->GetDataBase();
	}
	return nil;
}


UIDRef GetUIDRef(const IPMUnknown *obj)
{
	InterfacePtr<const IControllingUnknown> boss(obj, IID_ICONTROLLINGUNKNOWN);
	if (boss)
	{
		const IPMPersist *persist = boss->GetPersist();
		if (persist)
			return UIDRef(persist->GetDataBase(), persist->GetUID());
	}
	return UIDRef(nil, kInvalidUID);
}


void PreDirty(IControllingUnknown *boss, IPMUnknown *p, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(boss != nil, "::PreDirty() - object is nil!");
	IPMPersist *persist = const_cast<IPMPersist*>(((boss == nil) ? nil : boss->GetPersist()));
	if (persist)
		persist->SetDirty(p, prop, allowModification);
}


void PreDirtyNoMessage(IControllingUnknown *boss, IPMUnknown *p, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(boss != nil, "::PreDirty() - object is nil!");
	IPMPersist *persist = const_cast<IPMPersist*>(((boss == nil) ? nil : boss->GetPersist()));
	if (persist)
		persist->SetDirtyOverrideMessage(p, kInvalidInterfaceID, prop, allowModification);
}


void PreDirty(IPMUnknown *p, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(p != nil, "::PreDirty() - object is nil!");
	InterfacePtr<IPMPersist> persist(p, IID_IPMPERSIST);
	if (persist)
		persist->SetDirty(p, prop, allowModification);
}


void PreDirtyNoMessage(IPMUnknown *p, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(p != nil, "::PreDirty() - object is nil!");
	InterfacePtr<IPMPersist> persist(p, IID_IPMPERSIST);
	if (persist)
		persist->SetDirtyOverrideMessage(p, kInvalidInterfaceID, prop, allowModification);
}

void PreDirtyAllowDuplicateMessage(IPMUnknown *p, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(p != nil, "::PreDirty() - object is nil!");
	InterfacePtr<IPMPersist> persist(p, IID_IPMPERSIST);
	if (persist)
		persist->SetDirtyAllowDuplicateMessage(p, prop, allowModification);
}

void PreDirtyOverrideMessage(IPMUnknown *p, PMIID overrideIID, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(p != nil, "::PreDirty() - object is nil!");
	InterfacePtr<IPMPersist> persist(p, IID_IPMPERSIST);
	if (persist)
		persist->SetDirtyOverrideMessage(p, overrideIID, prop, allowModification);
}

void PreDirtyOverrideAllowDuplicateMessage(IPMUnknown *p, PMIID overrideIID, ImplementationID prop, bool16 allowModification)
{
	ASSERT_MSG(p != nil, "::PreDirty() - object is nil!");
	InterfacePtr<IPMPersist> persist(p, IID_IPMPERSIST);
	if (persist)
		persist->SetDirtyOverrideAllowDuplicateMessage(p, overrideIID, prop, allowModification);
}


void PreDirtyViewInterface(IPMUnknown *pFace, ImplementationID prop )
{
	InterfacePtr<IViewObjectChanges>viewObjectChanges (pFace, UseDefaultIID());
	InterfacePtr<IControllingUnknown> boss(pFace, IID_IUNKNOWN);
	if (viewObjectChanges)
		viewObjectChanges->SetDirty(boss, pFace, prop);
}

ClassID GetClass( const IPMUnknown *obj)
{
	ASSERT_MSG(obj != nil, "::GetClass() - object is nil!");
	InterfacePtr<const IControllingUnknown> boss(obj, IID_ICONTROLLINGUNKNOWN);
	if (boss)
		return boss->GetClass();
	else
		return kInvalidClass;
}

bool16 ClassesAreCompatible(const ClassID& aClass, const ClassID& bClass)
{
	const IObjectModel* om = GetObjectModelInstance();

	return aClass == bClass || ClassIsDescendantOf(aClass, bClass, om) || ClassIsDescendantOf(bClass, aClass, om);
}

bool16 ClassIsDescendantOf(const ClassID& anscestor, const ClassID& descendant)
{
	return ClassIsDescendantOf(anscestor, descendant, GetObjectModelInstance());
}



// Copy data from the instream and send through the functor.  If the length is
// less than 2k, then use a local buffer.  Otherwise, allocate a buffer
// to reduce the number of calls to XferByte(), each of which can be very
// expensive.  DStephens 8/1/01
void CopyData(IPMStream *inStream, int32 length, CopyDataFunctor *transferOut)
{
	const int32 kLocalBufferSize = 2048;
	uchar localBuffer[kLocalBufferSize];
	int32 bufferSize = 64 * 1024;
	if ( bufferSize > length )
		bufferSize = length;

	uchar *buffer = nil;
	uchar *pBuffer = nil;

	if ( bufferSize <= kLocalBufferSize )
		pBuffer = localBuffer;
	else {
		buffer = new uchar[bufferSize];
		pBuffer = buffer;

		if ( !pBuffer ) {
			pBuffer = localBuffer;
			bufferSize = kLocalBufferSize;
		}
	}

	while (length > 0)	{
		int32 amtToCopy = (length < bufferSize) ? length : bufferSize;
		inStream->XferByte(pBuffer, amtToCopy);
		if (!transferOut->Transfer(pBuffer, amtToCopy))
			break;

		length -= amtToCopy;
	}

	if ( buffer )
		delete [] buffer;
}

class CopyDataStream : public CopyDataFunctor
{
public:
	CopyDataStream(IPMStream *outStream) :
		fOutStream(outStream)
		{}
	virtual bool Transfer(uchar *buffer, uint32 amtToCopy)
	{
		int32 count = fOutStream->XferByte(buffer, amtToCopy);

		if ( count != amtToCopy ) {
			ErrorUtils::PMSetGlobalErrorCode(IDataBase::kDiskFullError);
			return false;
		}
		return true;
	}
private:
	IPMStream *fOutStream;
};

void CopyData(IPMStream *inStream, IPMStream *outStream, int32 length)
{
	CopyDataStream copyDataFunctor(outStream);
	CopyData(inStream, length, &copyDataFunctor);
}




#ifdef DEBUG
int32 GetRefCount(const IPMUnknown *obj)
{
	ASSERT_MSG(obj != nil, "::GetRefCount() - object is nil!");
	InterfacePtr<const IControllingUnknown> boss(obj, IID_ICONTROLLINGUNKNOWN);
	if (boss)
		return boss->GetRefCount() - 1; // take off the one our interfacePtr adds
	else
		return 0;
}

ImplementationID GetImplID(const IPMUnknown *obj, PMIID interfaceID)
{
	ASSERT_MSG(obj != nil, "::GetImplID() - object is nil!");

	InterfacePtr<IClassInfo> clsInfo(GetObjectModelInstance()->QueryClassInfo(GetClass(obj)));
	if(clsInfo)
		return clsInfo->GetImplementation(interfaceID);
	return kInvalidImpl;
}

#endif


// GetPluginID() returns the plug-in ID using this search path:
//	(1) plug-in ID of the boss of obj.
//	(2) plug-in ID of the application boss.
//	(3) kApplicationPluginID.

PUBLIC_DECL PluginID GetPluginID( const IPMUnknown *obj )
{
	PluginID pluginID = kAppUIPluginID;

	// ---- The application ui plug is not part of the server product. This causes the
	//		resource manager to set the global error code. Here we use the soap server
	//		plug-in as the default plug-in. It contains no ui resources but does exist
	//		so that the resource manager will not error but will search up the chain
	//		getting the resources in the executable.

	if (Product::Get() == kInDesignServerProduct)
		pluginID = kSoapServerID;
	else if (!IDThreading::IsMainThreadDomain())// if on worker thread return kAppFrameworkPluginID 
		pluginID = kAppFrameworkPluginID;

	const IExecutionContext* ec = GetExecutionContext();
	ISession* session = ec->GetSession();
	if( session )
	{
		ClassID clsID = obj ? ::GetClass( obj ) : kInvalidClass;
		if( clsID != kInvalidClass )
		{
			const IObjectModel* om = ec->GetObjectModel();
			InterfacePtr<IClassInfo> classInfo( om->QueryClassInfo(clsID));
			if( classInfo )
				pluginID = classInfo->GetOwnerComponent();
		}
	}
	return pluginID;
}


