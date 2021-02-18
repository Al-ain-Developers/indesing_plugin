//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Data.tpp $
//  
//  Owner: Michael Burbidge
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

// ----- Interface Includes -----

#include "CData.tpp"
#include "IPMStream.h"

// ----- Implementation Includes -----

#include "FileUtils.h"

//========================================================================================
// CLASS Data
//========================================================================================

template < typename T, int32 ImplID >
class Data : public CData<T>
{
public:
	Data(IPMUnknown *boss);
	~Data();

private:
#ifdef USE_ALLOCATE_WITH_BOSS
	static void* CreateImpl(void *memoryBuffer, IPMUnknown *boss);
#else
    static void* CreateImpl(IPMUnknown *boss);
#endif
	static void DestroyImpl(void *facePtr);
	static int SizeOfImpl();
	static InterfaceFactory gFactory;
};

//========================================================================================
// IMPLEMENTATION Data
//========================================================================================

template <typename T, int32 ImplID>
Data<T, ImplID>::Data(IPMUnknown *boss) :
	CData<T>(boss)
{
}

template <typename T, int32 ImplID>
Data<T, ImplID>::~Data()
{
}

#ifdef USE_ALLOCATE_WITH_BOSS

template <typename T, int32 ImplID>
void* Data<T, ImplID>::CreateImpl(void *memoryBuffer, IPMUnknown *boss)
{
	return new (memoryBuffer) Data<T, ImplID>(boss);
}

template <typename T, int32 ImplID>
void Data<T, ImplID>::DestroyImpl(void *facePtr)
{
reinterpret_cast< Data<T, ImplID>* >(facePtr)->~Data();
}

#else

template <typename T, int32 ImplID>
void* Data<T, ImplID>::CreateImpl(IPMUnknown *boss)
{
return new Data<T, ImplID>(boss);
}

template <typename T, int32 ImplID>
void Data<T, ImplID>::DestroyImpl(void *facePtr)
{
delete reinterpret_cast< Data<T, ImplID>* >(facePtr);
}


#endif

template <typename T, int32 ImplID>
int Data<T, ImplID>::SizeOfImpl()
{
	return sizeof (Data<T, ImplID>);
}

template <typename T, int32 ImplID>
InterfaceFactory Data<T, ImplID>::gFactory(ImplID, CreateImpl, (InterfaceDestructor)DestroyImpl, (InterfaceSizeOf)SizeOfImpl, (InterfaceReadWrite)0L, (InterfaceReadWrite)0L);

//========================================================================================
// Free Default ReadWrite template functions for various data types.
//========================================================================================

template <typename T>
void ReadWrite(IPMStream *s, ImplementationID prop, T& data)
{
	ASSERT_FAIL("Must provide ReadWrite functor to Data<> template");
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, uchar& data)
{
	s->XferByte(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, int16& data)
{
	s->XferInt16(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, int32& data)
{
	s->XferInt32(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, ClassID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, ImplementationID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, WidgetID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, PluginID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, PMIID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, ActionID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, ScriptElementID& data)
{
	s->XferID(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, PMReal& data)
{
	s->XferRealNumber(data);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, PMString& data)
{
	data.ReadWrite(s);
}

template <>
void ReadWrite(IPMStream *s, ImplementationID prop, IDFile& data)
{
	if (s->IsReading())
	{
		PMString fileStr;
		fileStr.ReadWrite(s);
		data = FileUtils::PMStringToSysFile(fileStr);
	}
	else
	{
		PMString fileStr;
		fileStr = FileUtils::SysFileToPMString(data);
		fileStr.ReadWrite(s);
	}
}

//========================================================================================
// CLASS DefaultReadWrite
//========================================================================================

template <typename T>
class DefaultReadWrite
{
public:
	void operator()(IPMStream *s, ImplementationID prop, T data);
};

template <typename T>
void DefaultReadWrite<T>::operator()(IPMStream *s, ImplementationID prop, T data)
{
	ReadWrite(s, prop,data);
}

//========================================================================================
// CLASS PersistData
//========================================================================================

template < typename T, int32 ImplID, typename ReadWriteFunc = DefaultReadWrite<T> >
class PersistData : public CData<T>
{
public:
	PersistData(IPMUnknown *boss);
	~PersistData();

	void ReadWrite(IPMStream *s, ImplementationID prop);
	
private:
	ReadWriteFunc fReadWrite;

private:
#ifdef USE_ALLOCATE_WITH_BOSS
	static void* CreateImpl(void *memoryBuffer, IPMUnknown *boss);
#else
    static void* CreateImpl(IPMUnknown *boss);
#endif
	static void DestroyImpl(void *facePtr);
	static int SizeOfImpl();
	static void ReadWriteImpl(PersistData<T, ImplID, ReadWriteFunc>* obj, IPMStream *s, ImplementationID prop, int32 length);
	static InterfaceFactory gFactory;
};

//========================================================================================
// IMPLEMENTATION PersistData
//========================================================================================

template <typename T, int32 ImplID, typename ReadWriteFunc>
PersistData<T, ImplID, ReadWriteFunc>::PersistData(IPMUnknown *boss) :
	CData<T>(boss)
{
}

template <typename T, int32 ImplID, typename ReadWriteFunc>
PersistData<T, ImplID, ReadWriteFunc>::~PersistData()
{
}

template <typename T, int32 ImplID, typename ReadWriteFunc>
void PersistData<T, ImplID, ReadWriteFunc>::ReadWrite(IPMStream *s, ImplementationID prop)
{
	fReadWrite(s, prop, this->Get());
}

#ifdef USE_ALLOCATE_WITH_BOSS

template <typename T, int32 ImplID, typename ReadWriteFunc>
void* PersistData<T, ImplID, ReadWriteFunc>::CreateImpl(void *memoryBuffer, IPMUnknown *boss)
{
	return new (memoryBuffer) PersistData<T, ImplID, ReadWriteFunc>(boss);
}

template <typename T, int32 ImplID, typename ReadWriteFunc>
void PersistData<T, ImplID, ReadWriteFunc>::DestroyImpl(void *facePtr)
{
	reinterpret_cast< PersistData<T, ImplID, ReadWriteFunc>* >(facePtr)->~PersistData();
}

#else

    template <typename T, int32 ImplID, typename ReadWriteFunc>
    void* PersistData<T, ImplID, ReadWriteFunc>::CreateImpl(IPMUnknown *boss)
    {
        return new PersistData<T, ImplID, ReadWriteFunc>(boss);
    }

    template <typename T, int32 ImplID, typename ReadWriteFunc>
    void PersistData<T, ImplID, ReadWriteFunc>::DestroyImpl(void *facePtr)
    {
        delete reinterpret_cast< PersistData<T, ImplID, ReadWriteFunc>* >(facePtr);
    }

#endif

template <typename T, int32 ImplID, typename ReadWriteFunc>
int PersistData<T, ImplID, ReadWriteFunc>::SizeOfImpl()
{
	return sizeof (PersistData<T, ImplID, ReadWriteFunc>);
}

template <typename T, int32 ImplID, typename ReadWriteFunc>
void PersistData<T, ImplID, ReadWriteFunc>::ReadWriteImpl(PersistData<T, ImplID, ReadWriteFunc>* obj, IPMStream *s, ImplementationID prop, int32 length)
{
	obj->ReadWrite(s, prop);
}

template <typename T, int32 ImplID, typename ReadWriteFunc>
InterfaceFactory PersistData<T, ImplID, ReadWriteFunc>::gFactory(ImplID, CreateImpl, (InterfaceDestructor)DestroyImpl, (InterfaceSizeOf)SizeOfImpl, (InterfaceReadWrite)ReadWriteImpl, (InterfaceReadWrite)0L);
