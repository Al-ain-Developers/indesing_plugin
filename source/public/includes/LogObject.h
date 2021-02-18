//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LogObject.h $
//  
//  Owner: lance bushore
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
//  This file is conditionally compiled.  If we are building Public, we want
//  to only build this if we are doing a DEBUG build.  If we are building
//  TestLib, we want to build this if we are doing a non-DEBUG build.  This
//  is so that Logging code will be stripped out of shipping code, but still
//  allow us to write logs from test plugins in non-debug builds.
//  
//========================================================================================

#pragma once
#ifndef __LogObject__
#define __LogObject__

#include <time.h>
#include "IDFile.h"
#include "IPMStream.h"		// for OpenMode
#include <string>

#pragma export on
#if defined (ID_ENABLE_DEBUGGING) && (!TESTLIB_BUILD)
#define LOG_DECL PUBLIC_DECL
#else
#define LOG_DECL TESTLIB_DECL
#endif

class IXferBytes;
class IPMStream;

//If you change the definition of LogObject, remember to build
//Public.  Both TestLib and Public include LogObject.cpp, but
//this class belongs to Public in the Debug build.  Building
//TestLib alone won't allow the linker to resolve a reference
//to, for example, an added member function.

/**
	LogObject allows a caller to create and write to a log, i.e., a text-only file,
	or append to an existing log.

	The constructors use an "autoflush" setting.  Before setting that to kTrue,
	consider the potential impact on performance.  The default was changed to
	kFalse, in order to prevent the time-consuming writing to disk that formerly
	occurred on startup.

	Some methods terminate lines.  The terminator varies per platform.

	Some methods indent lines.  Indenting is accomplished by inserting a fixed
	number of spaces, sometimes referred to as a "tab."
*/
class LOG_DECL LogObject 
{
	public:

/**
	This constructor wraps an existing log file or creates a new one in a standard location.
	@param logFileName The name of the file.  The remainder of the path is as
	returned from GetLogFileDir().
	@param newFile If kTrue, then the file is created.
	@param writeMemoryInfo If kTrue, then memory info is automatically written
	once into the log.
	@param autoflush If kTrue, then the underlying stream is automatically
	flushed every time a WriteFoo() method is called.
 */
		LogObject(const char *logFileName, bool16 newFile = kTrue, bool16 writeMemoryInfo = kTrue, bool16 autoflush = kFalse);

/**
	This constructor wraps an existing log file or creates a new one in a
	standard location, and it suppresses the standard header and trailer.
	@param newFile If kTrue, then the file is created.
	@param logFileName The name of the file.  The remainder of the path is as
	returned from GetLogFileDir().
	@param autoflush If kTrue, then the underlying stream is automatically
	flushed every time a WriteFoo() method is called.
 */
		LogObject(bool16 newFile, const char *logFileName, bool16 autoflush = kFalse);// For those who do not want any header trailer text

/**
	This constructor wraps an existing log file or creates a new one in the
	specified location, and it suppresses the standard header and trailer.
	@param pathAndName The name of the file.  The remainder of the path is as
	returned from GetLogFileDir().
	@param newFile If kTrue, then the file is created.
	@param writeMemoryInfo If kTrue, then memory info is automatically written
	into the log.
	@param autoflush If kTrue, then the underlying stream is automatically
	flushed every time a WriteFoo() method is called.
 */
		LogObject(IDFile pathAndName, bool16 newFile = kTrue, bool16 autoflush = kFalse);

/**
	The destructor writes the standard trailer according to the setting set by
	the constructor; flushes the underlying stream, if autoflush has not been
	specified; then, closes the stream.
 */
		virtual ~LogObject();

/**
	Appends the specified text.
	@param terminateLine If kTrue, a line terminator is further appended.
	@param format A "printf"-type string.
	@param ... Any variables called for by "format".
 */
		void	WriteLog(bool16 terminateLine, const char *format, ... );

/**
	Appends the specified text.
	@param format A "printf"-type string.
	@param argptr Argument list, contains any variables called for by "format".
	@param terminateLine If kTrue, a line terminator is further appended.
 */
		void	WriteLogFormat(const char *format, va_list argptr, bool16 terminateLine = kTrue );


/**
	Appends the specified string.
	@param logString The string.
	@param terminateLine If kTrue, a line terminator is further appended.
 */
		void	WriteLog(const PMString& logString, bool16 terminateLine = kTrue);


/**
	Appends the current date and time.
	@param terminateLine If kTrue, a line terminator is further appended.
 */
		void	WriteDateTime(bool16 terminateLine);


/**
	Appends the length of time since this object was constructed.
	@param terminateLine If kTrue, a line terminator is further appended.
 */
		void	WriteElapsedTime(bool16 terminateLine);

/**
	Appends data about available memory and memory used since this object was
	constructed.
 */
		void	WriteMemoryInfo();

/**	
	Appends data about available memory.
 */
		void	WriteAvailableMemory();

/**	
	Appends data about memory used since this object was constructed.
 */
		void	WriteMemoryUsed();

/**	
	Appends a line of dashes.
 */
		void	WriteSeparator();

/**	
	Increases the indent by one tab.
 */
		void	Indent();

/**	
	Reduces the indent by one tab.
 */
		void	UnIndent();

/**	
	Returns the measure of the current indent.
	@return The number of tabs in the indent.
 */
		int16	GetNumIndents();


/**
	Specifies a string to be appended automatically before the material
	specified in WriteLog().
	@param prepend The string to append.
 */
		void	Prepend(const PMString& prepend);

/**	
	Clears the string specified by Prepend().
 */
		void	RemovePrepend();


/**	Turns on or off the flag that determines whether a trailer shall be written
	by the destructor.
	@param writeTrailer If kTrue, a trailer is written.
 */
		void	SetWriteTrailer(bool16 writeTrailer) { fWriteTrailer = writeTrailer; }

/**	
	Returns the location of the QA folder, which is used to store various
	testing resources, including standard logs.
	@return The location of the QA folder.
 */
		static PMString	GetQAFileDir();

/**	
	Returns the location of the standard folder for storing logs.  For InDesign
	Server, this includes a subfolder named after the configuration.
	@return The location of the Logs folder.
 */
		static PMString	GetLogFileDir();

/**	
	Returns the location of the standard folder for storing output from
	benchmarking tests.  For InDesign Server, this includes a subfolder
	named after the configuration.
	@return The location of the Benchmark:Data folder.
 */
		static PMString	GetBenchmarkDataDir();

/**
	Returns the configuration name used by InDesign Server.
	@return The configuration name.
 */
		static PMString	GetPortDirName();

/**	
	Returns the filename of the log.
	@return The filename.
 */
		PMString GetLogFileName(void);


/**
	Inserts a string into the log at the specified position.
	@param logString The string.
	@param startPos The position.
 */
		void	WriteInsert(const PMString& logString, CharCounter startPos);

/**
	Writes the standard header information.
	@param fileName The name to be used in the header to specify this log.
 */
		void	WriteBasicHeader(const char *fileName);

	protected:

	private:
		IPMStream *GetStream( OpenMode mode = kOpenTrunc );
		void CloseStream();
		
			time_t fStartTime;
			int32 fStartMem;
			IDFile fLogFile;
			IPMStream *fLogStream;
			IXferBytes *fXferBytes;
			bool16 fWriteTrailer;
			std::string	fIndent;
			std::string	fPrepend;
			bool16      fAutoflush;
};
#pragma export off
#endif
