//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/StreamUtil.cpp $
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
//========================================================================================

#include "VCPublicHeaders.h"

#include "StreamUtil.h"
#include "CreateObject.h"
#include "IDBStreamCopyData.h"
#include "IMemoryStreamData.h"
#include "IResourceStreamData.h"
#include "IObjectTextFileStreamData.h"
#include "ICopyStreamData.h"
#include "RsrcSpec.h"
#include "DocFrameworkID.h"
#include "PrivateStreamUtil.h"


IPMStream *StreamUtil::CreateDBStreamRead(IDataBase *db, UID id)
{
	return PrivateStreamUtil::CreateDBStream(db, id, kDBStreamReadBoss);
}


IPMStream *StreamUtil::CreateDBStreamWrite(IDataBase *db, UID id)
{
	return PrivateStreamUtil::CreateDBStream(db, id, kDBStreamWriteBoss);
}

IPMStream *StreamUtil::CreateFileStreamRead(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateFileStream(kFileStreamReadBoss, sysFile, mode, fileType, creator);
}

IPMStream *StreamUtil::CreateFileStreamReadLazy(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateFileStreamLazy(kFileStreamReadLazyBoss, sysFile, mode, fileType, creator);
}


IPMStream *StreamUtil::CreateFileStreamWrite(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateFileStream(kFileStreamWriteBoss, sysFile, mode, fileType, creator);
}


IPMStream *StreamUtil::CreateFileStreamWriteLazy(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateFileStreamLazy(kFileStreamWriteLazyBoss, sysFile, mode, fileType, creator);
}


IPMStream *StreamUtil::CreateObjectTextFileStreamWrite(IDataBase* db, const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	IPMStream* stream = PrivateStreamUtil::CreateFileStream(kObjectTextFileStreamWriteBoss, sysFile, mode, fileType, creator);

	InterfacePtr<IObjectTextFileStreamData> data(stream, IID_IOBJECTTEXTFILESTREAMDATA);
	data->Set(db);
	
	return stream;
}


IPMStream *StreamUtil::CreateManagedFileStreamRead(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateManagedFileStream(kFileStreamReadBoss, sysFile, mode, fileType, creator);
}

IPMStream *StreamUtil::CreateManagedFileStreamReadLazy(const IDFile& sysFile, uint32 mode , OSType fileType , OSType creator)
{
	return PrivateStreamUtil::CreateManagedFileStreamLazy(kFileStreamReadBoss, sysFile, mode, fileType, creator);
}


IPMStream *StreamUtil::CreatePointerStreamRead(char *buffer, size_t len)
{
	IPMStream	*stream = PrivateStreamUtil::CreatePointerStream(kPointerStreamReadBoss, buffer, len);
	stream->SetSwapping(kFalse);
	return stream;
}


IPMStream *StreamUtil::CreatePointerStreamWrite(char *buffer, size_t len)
{
	IPMStream *stream = PrivateStreamUtil::CreatePointerStream(kPointerStreamWriteBoss, buffer, len);
	stream->SetSwapping(kFalse);
	return stream;
}


IPMStream *CreateMemoryStream(ClassID clsID, IXferBytes* underlyingXferBytes, bool16 takeOwnership)
{
	IPMStream *s = (IPMStream *)::CreateObject(clsID, IID_IPMSTREAM);
	if (!s)
		return nil;

	InterfacePtr<IMemoryStreamData> data(s, IID_IMEMORYSTREAMDATA);
	data->Set(underlyingXferBytes, takeOwnership);
	if (!s->Open())	{
		s->Release();
		return nil;
		}
	return s;
}

IPMStream *StreamUtil::CreateMemoryStreamRead(IXferBytes* underlyingXferBytes, bool16 takeOwnership, bool16 recycleBoss)
{
	IPMStream	*stream = CreateMemoryStream(recycleBoss ? kMemStreamReadRecycleBoss : kMemStreamReadBoss, underlyingXferBytes, takeOwnership);
	stream->SetSwapping(kFalse);
	return stream;
}

IPMStream *StreamUtil::CreateMemoryStreamWrite(IXferBytes* underlyingXferBytes, bool16 takeOwnership, bool16 recycleBoss)
{
	IPMStream *stream = CreateMemoryStream(recycleBoss ? kMemStreamWriteRecycleBoss : kMemStreamWriteBoss, underlyingXferBytes, takeOwnership);
	stream->SetSwapping(kFalse);
	return stream;
}


IPMStream *StreamUtil::CreateResourceStreamRead(const RsrcSpec& spec,bool16 useLocaleIndexResource)
{
	IPMStream *s = (IPMStream *)::CreateObject(kResourceStreamReadBoss, IID_IPMSTREAM);
	InterfacePtr<IResourceStreamData> data(s, IID_IRESOURCESTREAMDATA);
	data->Set(spec,nil,useLocaleIndexResource);
	if (!s->Open())	
	{
		s->Release();
		return nil;
	}
	s->SetSwapping (RESOURCE_ENDIAN_SWAPPING);	
	return s;
}


IPMStream *StreamUtil::CreateObjectResourceStreamRead(const RsrcSpec& spec, IDataBase* db)
{
	IPMStream *s = (IPMStream *)::CreateObject(kObjectResourceStreamReadBoss, IID_IPMSTREAM);
	InterfacePtr<IResourceStreamData> data(s, IID_IRESOURCESTREAMDATA);
	data->Set(spec, db);
	if (!s->Open())	{
		s->Release();
		return nil;
		}
	s->SetSwapping (RESOURCE_ENDIAN_SWAPPING);	
	return s;
}


IPMStream *StreamUtil::CreateCopyStream(IDataBase *src, IDataBase *dest, IXferBytes *xfer)
{
	IPMStream *s = (IPMStream *)::CreateObject(kCopyStreamBoss, IID_IPMSTREAM);
	InterfacePtr<ICopyStreamData> data(s, IID_ICOPYSTREAMDATA);
	data->Set(src, dest, xfer);
	if (s->Open())
		{
		InterfacePtr<IPMStream>	instream(s, IID_IPMSTREAMIN);
		if (instream->Open())
			return s;
		}

		// already returned when successful.
	s->Release();
	return nil;
}


IPMStream *StreamUtil::CreateDBStreamCopy(IDataBase *src, IDataBase *dest, UID id, IPMUnknown* pmobject)
{
	IPMStream *s = (IPMStream *)::CreateObject(kDBStreamCopyBoss, IID_IPMSTREAM);
	InterfacePtr<IDBStreamCopyData> data(s, IID_IDBSTREAMCOPYDATA);
	data->Set(src, dest, id, pmobject);
	if (!s->Open())	{
		s->Release();
		return nil;
		}
	return s;
}

