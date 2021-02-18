//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StreamUtil.h $
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

#pragma once
#ifndef __StreamUtil__
#define __StreamUtil__

#include "ShuksanID.h"
#include "IPMStream.h"
#include "IBoolData.h"

class IXferBytes;
class IDataBase;
class RsrcSpec;

/** StreamUtil is a class of static functions that create and manipulate InDesign streams.
	It is provided for convenience and ease of use.
	
	Note that any of the create stream methods will return nil if there is an error 
	creating a stream (e.g., file cannot be opened, etc.). So client code should check
	for nil on return.

	Example Code:
<pre>
		InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamRead(myFile));
		if (s)	{
			// read from file
		}
		else {
			// handle error
</pre>
			
	Also, in all cases, the stream returned is a referenced object, and the caller is
	responsible for releasing it. Typically this is handled via InterfacePtr, as in 
	the example above.
*/
#pragma export on
class PUBLIC_DECL StreamUtil {
	public:

		// Database stream access

		/** Open a stream for reading a database object 
			
			@param db what database the object is in
			@param UID the object in the database to access
			@return IPMStream* the new stream, or nil if the stream cannot be opened.
		*/
	 static IPMStream *CreateDBStreamRead(IDataBase *db, UID id);

		/** Open a stream for writing a database record. 
			
			@param db what database the object is in
			@param UID the object in the database to access
			@return IPMStream* the new stream, or nil if the stream cannot be opened.
		*/
	 static IPMStream *CreateDBStreamWrite(IDataBase *db, UID id);
	
		/** For internal use only.
			Open a stream for copying a database record. 
			
			@param src database to copy from
			@param dest database to copy to
			@param IXerBytes* the handler to use for the copy
			@return IPMStream* the new stream, or nil if the stream cannot be opened.
		*/
	 static IPMStream *CreateCopyStream(IDataBase *src, IDataBase *dest, IXferBytes *xfer = nil);
	
		/** For internal use only.
			Copy a uid from the src database into a new object in the destination database.
			
			@param src database to copy from
			@param dest database to copy to
			@param dest object to copy to
			@param pmobject used in translating UIDs during the copy (for internal use only)
			@return IPMStream* the new stream, or nil if the stream cannot be opened.
		*/
	 static IPMStream *CreateDBStreamCopy(IDataBase *src, IDataBase *dest, UID id, IPMUnknown* pmobject = nil);

		// File access
	
		/** Open a stream for reading from a file. 
		
			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateFileStreamRead(const IDFile& sysFile, uint32 mode = kOpenIn, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

		/** Open a stream for writing to a file. 

			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateFileStreamWrite(const IDFile& sysFile, uint32 mode = kOpenOut, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

		/** Open a stream for reading from a file. The file is opened on demand, the first time a
			read is requested. Note that in this case, you may get back a valid stream from the
			CreateFileStreamReadLazy method, but the file hasn't yet been opened. It will be
			opened as the result of a subsequent read request. If the open fails, the stream
			will go into an error state @see GetStreamState. Client code should check for this.

			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateFileStreamReadLazy(const IDFile& sysFile, uint32 mode = kOpenIn, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

		/** Open a stream for writing to a file. The file is opened on demand, the first time a
			write is requested. Note that in this case, you may get back a valid stream from the
			CreateFileStreamWriteLazy method, but the file hasn't yet been opened. It will be
			opened as the result of a subsequent write request. If the open fails, the stream
			will go into an error state @see GetStreamState. Client code should check for this.

			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateFileStreamWriteLazy(const IDFile& sysFile, uint32 mode = kOpenOut  | kOpenTrunc, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

	 static IPMStream *CreateObjectTextFileStreamWrite(IDataBase* db, const IDFile& sysFile, uint32 mode = kOpenOut, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);
	
	/** @name  Bauhaus managed streams */
	//@{-----------------------------------------------------------------------------
	
		/** Open a stream for reading from a file, downloads the file if it's not already in local repository. 
			Returns nil if file cannot be opened.
			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateManagedFileStreamRead(const IDFile& sysFile, uint32 mode = kOpenIn, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

		/** Open a stream for reading from a file. File is actually opened on demand, the
			first time a read is requested. Downloads the file if it's not already in local repository. 
			Returns nil if file cannot be opened.
			@param sysFile the file to read from
			@param mode mode for opening the file (open for read, read/write, etc.)
			@param fileType on Macintosh, this is the Finder file type
			@param creator on Macintosh, this the Finder creator type
			@return IPMStream* the new stream, or nil if the file couldn't be opened.
		*/
	 static IPMStream *CreateManagedFileStreamReadLazy(const IDFile& sysFile, uint32 mode = kOpenIn, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f);

	//@}-----------------------------------------------------------------------------

	/** @name  Memory-based streams */
	//@{-----------------------------------------------------------------------------

		/** Open a stream for reading from memory.
		 
			@param buffer memory address to start reading from
			@param len number of bytes to read
			
			@return IPMStream* the new stream.
		*/
	 static IPMStream *CreatePointerStreamRead(char *buffer, size_t len);

		/** Open a stream for writing to memory.

			@param buffer memory address to start writing to
			@param len number of bytes that can be written before end of stream
			
			@return IPMStream* the new stream
		*/
	 static IPMStream *CreatePointerStreamWrite(char *buffer, size_t len);
	
		/** Open a stream for reading from memory.
			@param underlyingXferBytes IXferBytes instance the memory stream will read from.
			@param takeOwnership Denotes whether the stream is to be the sole owner of the given IXferBytes.
			@param recycleBoss Denotes whether to utilize a recycle boss for the stream.\\
							   If the underlying IXferBytes must be released to free up resources, a
							   file for instance, it is recommended to not use a recycle boss since the 
							   IXferBytes might not be released until the stream boss is reused.
			@return IPMStream* the new read stream
		*/
	 static IPMStream *CreateMemoryStreamRead(IXferBytes* underlyingXferBytes, bool16 takeOwnership = kFalse, bool16 recycleBoss = kTrue);

		/** Open a stream for writing to memory. 
			@param underlyingXferBytes IXferBytes instance the memory stream will write to.
			@param takeOwnership Denotes whether the stream is to be the sole owner of the given IXferBytes.
			@param recycleBoss Denotes whether to utilize a recycle boss for the stream.\\
							   If the underlying IXferBytes must be released to free up resources, a
							   file for instance, it is recommended to not use a recycle boss since the 
							   IXferBytes might not be released until the stream boss is reused.
			@return IPMStream* the new write stream
		*/
	 static IPMStream *CreateMemoryStreamWrite(IXferBytes* underlyingXferBytes, bool16 takeOwnership = kFalse, bool16 recycleBoss = kTrue);

	//@}-----------------------------------------------------------------------------

		/** Open a stream for reading from a resource.

			@param spec a descriptor of the resource to read
			@param useLocaleIndexResource kTrue to use a localized resource
			
			@return IPMStream* the new stream
		*/
	 static IPMStream *CreateResourceStreamRead(const RsrcSpec& spec, bool16 useLocaleIndexResource = kTrue);

		// For Internal Use Only.
	 static IPMStream *CreateObjectResourceStreamRead(const RsrcSpec& spec, IDataBase* db);
	 
	 	/** The following functions are used for verifying stream contents.
			They is debugging only because they are used to control assertions. There's
			an assert that comes up if an object has been modified, but Dirty() was
			never called on it ("object changed but not marked dirty"). The assert 
			is for early detection of cases which could cause document corruption, but
			it does come up in some situations that are actually OK. For example, if 
			your code does dynamic conversion of data, so that it gets converted when
			its read in, it would get this assert but be OK. Or if it writes out the
			current time. In any case, you can set a flag on the stream that causes the
			assert not to fire. From your ReadWrite, in the case where you're writing
			out, call SetStreamContentsChanged, and the assert will not come up.
		*/
#if defined(DEBUG)
		/** Set the stream back to normal after a call to SetStreamContentsChanged.
			Does nothing in Release target.
		
			@param s the stream to set
		*/
	static void ResetStreamContentsChanged(IPMStream *s)
		{
			InterfacePtr<IBoolData> sBool(s, IID_IBOOLDATA);
			if (sBool != nil)
				sBool->Set(kFalse);
		}
		/** Set the stream to "changes expected" to prevent the assert from firing.
			Does nothing in Release target.
		
			@param s the stream to set
		*/
	static void SetStreamContentsChanged(IPMStream *s)
		{
			InterfacePtr<IBoolData> sBool(s, IID_IBOOLDATA);
			if (sBool != nil)
				sBool->Set(kTrue);
		}
		/** Get the stream to "changes expected" to see if the assert should fire.
			Does nothing in Release target.
			Internal Use Only.
		
			@param s the stream to set
			@return bool16 return true if the stream has changes expected
		*/
	static bool16 StreamContentsChanged(IPMStream *s)
		{
			InterfacePtr<IBoolData> sBool(s, IID_IBOOLDATA);
			if (sBool == nil)
				return kFalse;
			else
				return sBool->GetBool();
		}
#else
		/** Set the stream back to normal after a call to SetStreamContentsChanged.
			Does nothing in Release target.
		
			@param s the stream to set
		*/
	static void ResetStreamContentsChanged(IPMStream *)
		{}
		/** Set the stream to "changes expected" to prevent the assert from firing.
			Does nothing in Release target.
		
			@param s the stream to set
		*/
	static void SetStreamContentsChanged(IPMStream *)
		{}
		/** Get the stream to "changes expected" to see if the assert should fire.
			Does nothing in Release target.
			Internal Use Only.
		
			@param s the stream to set
			@return bool16 return true if the stream has changes expected
		*/
	static bool16 StreamContentsChanged(IPMStream *)
		{return kFalse;}
#endif

};
#pragma export off

#endif // __StreamUtil__
