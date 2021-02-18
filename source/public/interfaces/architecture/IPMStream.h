//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMStream.h $
//  
//  Owner: Robin Briggs
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
//  Purpose:
//  This is the interface used for serializing objects.
//  
//  Streams are normally created for you by methods in the StreamUtil class.
//  
//========================================================================================

#include "IPMUnknown.h"

#pragma once
#ifndef __IPMSTREAM__
#define __IPMSTREAM__


/** Flags used for defining what Seek does */
typedef enum
{
		/** seek from the start of the file to the byte offset */
	kSeekFromStart   = 0x01,
		/** seek forward or backward relative to the current position */
	kSeekFromCurrent = 0x02,
		/** seek backward relative to the end of the stream */
	kSeekFromEnd     = 0x04
} SeekFromWhere;

/* Modes used for opening files */
typedef enum
{
		/** Open for input (read access) */
	kOpenIn     = 0x01,
		/** Open for output (read-write access) */
	kOpenOut    = 0x02,
		/** Open for append (append output) */
  	kOpenApp    = 0x04,
  		/** Open truncate (open for write) */
	kOpenTrunc  = 0x08
} OpenMode;

/** Stream states */
typedef enum
{
		/** No error */
	kStreamStateGood	= 0,
		/** Stream has seeked to the end */
	kStreamStateEOF,
		/** Stream failure -- error condition */
	kStreamStateFailure,
		/** Stream is not open */
	kStreamStateClosed
} StreamState;

#ifdef DEBUG
#include "IDBStreamData.h"
#include "DocumentID.h"
#include "WorkspaceID.h"

#define ASSERT_IF_WRITING_TO_DOCUMENT(db_Stream)	if(db_Stream->IsWriting()) {\
		InterfacePtr<IDBStreamData> db_StreamData(db_Stream,IID_IDBSTREAMDATA);\
		if (db_StreamData != nil)\
		{\
			IDataBase *stream_DB = db_StreamData->GetDataBase();\
			UID db_rootUID = stream_DB->GetRootUID();\
			ASSERT_MSG(stream_DB->GetClass(db_rootUID) != kDocBoss,"This shouldn't be written to a pub database!");\
		}}

#define ASSERT_IF_WRITING_TO_DEFAULTS(db_Stream)	if(db_Stream->IsWriting()) {\
		InterfacePtr<IDBStreamData> db_StreamData(db_Stream,IID_IDBSTREAMDATA);\
		if (db_StreamData != nil)\
		{\
			IDataBase *stream_DB = db_StreamData->GetDataBase();\
			UID db_rootUID = stream_DB->GetRootUID();\
			ASSERT_MSG(stream_DB->GetClass(db_rootUID) != kWorkspaceBoss,"This shouldn't be written to a defaults database!");\
		}}

#else
#define ASSERT_IF_WRITING_TO_DOCUMENT(stream)
#define ASSERT_IF_WRITING_TO_DEFAULTS(stream)
#endif

// Use IPMStream::XferEnum instead of the XFER_ENUM and XFER_ENUM16 macros
#define XFER_ENUM(stream, enumVal) { stream->XferInt32((int32&)enumVal); }
#define XFER_ENUM16(stream, enumVal) { int16 _dummy = (int16) enumVal; (int32&) enumVal = (int32) stream->XferInt16(_dummy); }

/** IPMStream is the interface for streaming. It is used for serializing objects to/from the disk,
	copying objects, reading objects in from files, resources, or memory, etc.
	Each of the Xfer functions will either Read or Write the data, depending on the stream type.
	Xfer functions that take two arguments, where the second is a count, read or write an array
	of data.
*/
class IPMStream : public IPMUnknown
{
	public:
			/** StreamType */
		typedef enum _StreamType {
			kUnknown,
				/** Stream is used for reading data in */
			kReader,
				/** Stream is used for writing data out */
			kWriter
			} StreamType;

			/** Read or write a single enum value.
			*/
		template<typename T> inline void XferEnum(T& e)
		{
			int32 tmp(0);
			if (IsReading()) {
				XferInt32(tmp);
				e = static_cast<T>(tmp);
			}
			else {
				tmp = static_cast<int32>(e);
				XferInt32(tmp);
			}
		}
		
		virtual ~IPMStream() {}
			/** Read or write a single byte.
			*/
		virtual uchar XferByte(uchar& chr) = 0;
			/** Read or write an array of bytes.
			*/
		virtual int32 XferByte(uchar *buf, int32 num) = 0;

			/** Read or write a single bool16.
			*/
		virtual bool16 XferBool(bool16& chr) = 0;
			/** Read or write an array of bools.
			*/
		virtual int32 XferBool(bool16 *buf, int32 num) = 0;

			/** Read or write a single int16.
			*/
		virtual int16 XferInt16(int16& i) = 0;
			/** Read or write an array of int16.
			*/
		virtual int32 XferInt16(int16 *buf, int32 num) = 0;

			/** Read or write a single int32.
			*/
		virtual int32 XferInt32(int32& i) = 0;
			/** Read or write an array of int32.
			*/
		virtual int32 XferInt32(int32 *buf, int32 num) = 0;

			/** Read or write a single int64.
			*/
		virtual int64 XferInt64(int64& i) = 0;

			/** Read or write a single pointer - this will fail if writing to a user document, and return garbage
			 *	when reading from a user document; useful only for memory streams.
			 *	There is no validity checking on the pointer, it is up to the reader/writer to manage the pointers lifetime.
			 *	On a 32 bit machine, this will xfer 4 bytes, on a 64 bit machine, it will xfer 8 bytes.
			*/
		virtual uintptr_t XferPointer(uintptr_t& i) = 0;

			/** Read or write a single IDType id.
				Generic implementation for most IDType based types.
				If necessary, one can specialize the implementation.
			*/
		template<class T>
		inline IDType<T> XferID(IDType<T>& id)
		{
			XferInt32((int32&)id.Get());
			return id;
		}

			/** Read or write a single IDType id.
				Generic implementation for most IDType based types.
				If necessary, one can specialize the implementation.
			*/
		template<class T>
		inline int32 XferID(IDType<T>* buf, int32 count)
		{
			for (int32 i = 0; i < count; ++i)
				XferID(buf[i]);
			return count;
		}

			/** Read or write a single ClassID.
			*/
		virtual ClassID XferID(ClassID& i) = 0;
			/** Read or write an array of ClassIDs.
			*/
		virtual int32 XferID(ClassID *buf, int32 num) = 0;

			/** Read or write a single ImplementationID. idSpace is implied
				to be kImplementationIDSpace
			*/
		virtual ImplementationID XferID(ImplementationID& i) = 0;
			/** Read or write an array of ImplementationIDs.
			*/
		virtual int32 XferID(ImplementationID *buf, int32 num) = 0;

			/** Read or write a single WidgetID. idSpace is implied
				to be kWidgetIDSpace
			*/
		virtual WidgetID XferID(WidgetID& i) = 0;
			/** Read or write an array of WidgetIDs.
			*/
		virtual int32 XferID(WidgetID *buf, int32 num) = 0;

			/** Read or write a single PluginID. idSpace is implied
				to be kPluginIDSpace
			*/
		virtual PluginID XferID(PluginID& i) = 0;
			/** Read or write an array of PluginIDs.
			*/
		virtual int32 XferID(PluginID *buf, int32 num) = 0;

			/** Read or write a single PMIID. idSpace is implied
				to be kInterfaceIDSpace
			*/
		virtual PMIID XferID(PMIID& i) = 0;
			/** Read or write an array of PMIIDs.
			*/
		virtual int32 XferID(PMIID *buf, int32 num) = 0;

			/** Read or write a single Action id. idSpace is implied to
				be kActionIDSpace
			*/
		virtual ActionID XferID(ActionID& i) = 0;
			/** Read or write an array of ActionIDs.
			*/
		virtual int32 XferID(ActionID *buf, int32 num) = 0;

			/** Read or write a single ScriptInfo id. idSpace is implied to
				be kScriptInfoIDSpace
			*/
		virtual ScriptElementID XferID(ScriptElementID& i) = 0;
			/** Read or write an array of ScriptElementIDs.
			*/
		virtual int32 XferID(ScriptElementID *buf, int32 num) = 0;

			/** Read or write a single ScriptID id.
			*/
		virtual ScriptID XferID(ScriptID& i) = 0;
			/** Read or write an array of ScriptIDs.
			*/
		virtual int32 XferID(ScriptID *buf, int32 num) = 0;

			/** Read or write a single LinkClientID id. idSpace is implied
				to be kLinkClientIDSpace.
			*/
		virtual LinkClientID XferID(LinkClientID& i) = 0;
			/** Read or write an array of LinkClientIDs.
			*/
		virtual int32 XferID(LinkClientID *buf, int32 num) = 0;


			/** Read or write a single UID-based object. Call this method when an 
				object is being written out, and the object has a UID to another object 
				that it owns. The stream will decide whether to output just the UID, or 
				to make a copy of the object. For instance, if an object has children, 
				it should call XferObject to write out the children.
			*/
		virtual UID XferObject(UID& u) = 0;
			/** Read or write an array of objects.
			*/
		virtual int32 XferObject(UID *buf, int32 num) = 0;

			/** Read or write a single object reference. Call this method when an object
				is being written out, and the object has a UID to another object but it
				just refers to the other object, it doesn't own it. For instance, if an
				object has a reference to some global object that is owned by the document
				(for instance a style or color), it uses XferReference to tell the stream
				to map the reference from a reference to a color in the source document, to
				an equivalent color in the destination document.
			*/
		virtual UID XferReference(UID& u) = 0;
			/** Read or write an array of object references.
			*/
		virtual int32 XferReference(UID *buf, int32 num) = 0;

			/** Read or write a single real number.
			*/
		virtual PMReal& XferRealNumber(PMReal& r) = 0;
			/** Read or write an array of real number.
			*/
		virtual int32 XferRealNumber(PMReal *buf, int32 num) = 0;

			/** This method is mainly for notation purposes. Streams that write data
				in a text format write out appropriate syntax for the beginning and
				ending of structs and arrays.
			*/
		virtual void Comment(const char* comment) = 0;

			/** Set the location for the next xfer. Analogous to seeking in a file.
			@return new location in the stream, following the requested Seek. Hence stream->Seek(0,kSeekFromCurrent) returns the current stream position.
			*/
		virtual int64 Seek(int64 numberOfBytes, SeekFromWhere fromHere) = 0;
			/** Set the end of the stream at the current location. Truncates the
				stream!
			*/
		virtual void SetEndOfStream() = 0;

			/** Flushes any pending writes out to the operating system.
			*/
		virtual void Flush() = 0;

			/** Return the current stream state. Use this method to tell whether you've
				read past the end of the stream.
			*/
		virtual StreamState GetStreamState() = 0;

			/** Returns true if the stream is a read (input) stream.
			*/
		virtual bool16 IsReading() const = 0;
			/** Returns true if the stream is a write (output) stream.
			*/
		virtual bool16 IsWriting() const = 0;

			/**
			Write streams which are created for the purposes of duplicating,
			such as from IScrapUtils::CopyObject(), may influence how persisting
			implemenations behave if they have state that is dependent on
			external state. The value returned here is by definition constant
			throughout the life of the stream. Most implementors of IPMStreams
			will always return kFalse and only those which duplicate objects,
			rathern than simply persisting them, in XferReference() and
			XferObject() should be returning kTrue.
			@param optDestDB Pointer to IDataBase pointer. If non-nil, will be filled in with the destination if the method returns kTrue, otherwise unchanged.
			@return kTrue if IsWriting() return kTrue and the underlying stream is for the purposes of stream duplication.
			*/
        virtual bool16 IsWritingForDuplication(IDataBase** optDestDB = nil) const = 0;

			/** Turn byte swapping on/off. When on, the stream will treat the data target as having
				the oppsite byte order to the current platform. The stream will automatically byte swap
				if swapping has been turned on, enabling conversion across platforms.
				Swapping is off by default.
			*/
		virtual void SetSwapping(bool16 swapOn) = 0;
			/** @return kTrue if the stream is set to swap.
			*/
		virtual bool16 GetSwapping() const = 0;

			/** Open the stream for reading or writing. This must be called before any
				Xfers are called. It gets called for you by the StreamUtils functions.
				Typically streams may have data interfaces that must be filled out before
				you can call Open.
				@return kTrue if stream successfully opened, kFalse otherwise.
			*/
		virtual bool16 Open() = 0;
			/** Close the stream. Call this when you are all done with the stream.
			*/
		virtual void Close() = 0;

};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("ipmstream:indesign:adobe",IPMStream);

namespace Persist
{
	/**
		@struct	Serializer

		Base template with static methods for reading and writing generic types.

		If you simply need to use serialization utilities, use Persist::Read or Persist::Write functions below.
		The following implementation specifics are useful if you have a type that you want to provide
		serialization utilities for.

		The default implementations of the static Read/Write methods call ReadWrite on the object to be read into/written.

		If you need to override this behavior for a parameterized type such as std::pair, you should provide
		a template specialization with appropriate Read and Write implementations. See Serializer<std::pair>
		in PersistSTLTypes.h or Serializer<K2Vector> in PersistK2Types.h an example.

		If you need to override this behavior for a non-parameterized type such as int32, you need not provide
		a template specialization for Serializer. Instead, you should do so for Persist::Read and Persist::Write
		methods as mentioned below.

	*/
	template <typename T>
	struct Serializer
	{
		inline static void Read (IPMStream* stream, T& t)
		{
			ASSERT (stream && stream->IsReading());

			t.ReadWrite(stream);
		}

		inline static void Write (IPMStream* stream, const T& t)
		{
			ASSERT (stream && stream->IsWriting());

			// Cast constness away to to match ReadWrite signature. This should be safe since ReadWrite
			// implementations do not modify the object when the stream is being written to.
			T& tNonConst = const_cast<T&> (t);
			tNonConst.ReadWrite(stream);
		}
	};

	/**
		A template function for reading a generic type.
		@param	stream	IN	The stream to read from.
		@param	t	    OUT	The object to read into.

		Usage is straightforward; for example Persist::Read(stream, myInt32).
		The following implementation specifics can be ignored unless you have a type that you want to provide
		serialization utilities for.

		The default implementation of this method calls ReadWrite on the object to be read into.

		If you need to override this behavior for a non-parameterized type such as int32, you should provide
		a template specialization with the appropriate implementation. See Read<int32> in PersistBaseTypes.h
		for an example. DO NOT PROVIDE A NON-TEMPLATE OVERLOAD FOR THIS METHOD.

		If you need to override this behavior for a parameterized type such as std::pair, you would instead
		need to provide a template specialization for Serializer as mentioned above.

	*/
	template<typename T>
	inline void Read (IPMStream* stream, T& t)
	{
		Serializer<T>::Read(stream, t);
	}

	/**
		A template function for writing a generic type.
		@param	stream	IN	The stream to write to.
		@param	t	    IN	The object to write.

		Usage is straightforward; for example Persist::Write(stream, myInt32).
		The following implementation specifics can be ignored unless you have a type that you want to provide
		serialization utilities for.

		The default implementation of this method calls ReadWrite on the object to be written.

		If you need to override this behavior for a non-parameterized type such as int32, you should provide
		a template specialization with the appropriate implementation. See Write<int32> in PersistBaseTypes.h
		for an example. DO NOT PROVIDE A NON-TEMPLATE OVERLOAD FOR THIS METHOD.

		If you need to override this behavior for a parameterized type such as std::pair, you would instead
		need to provide a template specialization for Serializer as mentioned above.
	*/
	template<typename T>
	inline void Write (IPMStream* stream, const T& t)
	{
		Serializer<T>::Write(stream, t);
	}
}


#endif
