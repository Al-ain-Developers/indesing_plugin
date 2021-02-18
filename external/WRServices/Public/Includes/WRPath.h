//========================================================================================
//
//	File:	WRPath.h
//
//	Author: dsvoboda
//
//	Date:	08-June-2001
//
//	$Revision: #1 $
//
//	$Header: //CoreTech/Dev/WRServicesDaniel/Public/Includes/WRPath.h#1 $
//
//  Copyright 1988 - 2004 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2004.
//
//========================================================================================

#ifndef __WRPath__
#define __WRPath__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include <stdio.h>
#include "WRString.h"

//on Windows the path is null-terminated UTF-16 character Ptr
//on Unix, Mac it is posix path - null-terminated UTF-8 character Ptr
#ifdef WR_WIN_ENV
	typedef WRUnichar16 WRPathChar, *WRPathCharPtr;
	typedef WRUnichar16 WRModeChar, *WRModeCharPtr;
	
	#define kWRPathSeparator '\\'
#else
	typedef char WRPathChar, *WRPathCharPtr;
	typedef char WRModeChar, *WRModeCharPtr;
	
	#define kWRPathSeparator '/'
#endif

#define kWRPathMaxSegmentSize 256

/// Class for storing and manipulating Unicode aware file system paths in a platform independent way
/**
This class defines and implements interface for manipulation with multi-platform full path 
representations. It allows to remove or add segments to a path, create folders on the disk, 
to make sure a path exists (only if destination is folder) by making folder hierarchy contained 
in the full path up to the common existing node.
On Mac it handles POSIX path representation only (UTF-8 encoded, \c '/' character separated path, 
used in BSD POSIX calls), it doesn't support OLD HFS format (platform encoded, \c ':' character 
separated path). It is necessary to convert \b OLD \b HFS format of full paths to \b POSIX format before using this 
class on Mac. There are system calls to do it. To be able to convert \b OLD \b HFS format to \b POSIX format, 
the target the path points to MUST exist on the disk, so it is necessary to make sure the folder or file is 
created before system calls which converts former path format to the latter are used.
On Windows this class supports Unicode path (wchar_t*) and platform (char*) path, through 
WRString parameter.
Maximal length of segment is specified by kWRPathMaxSegmentSize constant (256)
*/

class WRSERVICES_DECL WRPath : public WRClass
{
public:
	
	/// Empty constructor
	/**
	Contructs a empty path
	*/
	WRPath();
	
	/// Constructor using a path litteral stored in a string
	/**
	Contruct a path using a litteral string.
	Segment separator is \c '/' on Mac and Linux platforms and \c '\' on Windows platform
	Paths must be in POSIX format on Mac and Unicode path on Windows (use please ...W versions
	of system calls to obtains some standard path string using system calls)
	Path string can, but doesn't need to contain trailing separator
	@param platformUnicodeFullPath a const ref to a WRString containg the path literal
	*/
	WRPath(const WRString& platformUnicodeFullPath);

	/// Copy constructor
	/**
	Constructs a WRPath pointing to the same location as inPath
	@param inPath a const ref to a WRPath to be copied
	*/
	WRPath(const WRPath& inPath);
	
	/// Destructor
	/**
	Destroys the object
	*/
	~WRPath();
	
	/// Path length
	/**
	Returns the length of the path in number of characters (not bytes!)
	*/
	const WRCharCount GetLength(void) const;
	
	/// Retrieve the path as a WRString 
	/**
	Returns the literal representation of a path pointed by \c this
	@return a WRString object containing the path literal 
	*/
	WRString GetPath(void) const;
	
	/// Assigment operator
	/**
	Allows WRPath type variables to be directly assigned.
	*/
	const WRPath& operator=(const WRPath& inPath);
	
	/// Opens the pointed file
	/**
	Returns stdio FILE*, which can be passes to standard I/O function (as fclose, fread, etc.). 
	Created to simplify mix of standard I/O functions and Unicode. On Mac, this works only when
	real BSD subsystem calls are called, Metrowerks' MSL library implementation of these 
	calls doesn't support POSIX path!
	@param mode a WRString ref containing the stdio open mode (e.g. "w", "rb", etc)
	@return a FILE* descriptor for the opened stream
	*/
	FILE *unicodefopen(WRString& mode) const;
	
	/// Path building
	/**
	Append a segment, taking care of one and only one separator between \c this and the new segment
	*/
	void AppendSegment(const WRString& segment);
	
	/// Removes the last segment of the path
	/**
	Removes last segment from full path and returns the name of last segment to optional parameter.
	@param segname a optional pointer to a WRString where to put the removed segment name
	@todo define the behavior in case of empty segment and reset segname content is that case
	*/
	void RemoveLastSegment(WRString *segname = NULL);
//#ifndef IOS
	/// Path type       
	/**
	@return a boolean
	@retval true if the path points to a directory
	@retval false it it's a file
	*/
	bool IsDirectory() const;
	
	/// Path existence test
	/**
	Return true if the path points to a file or a directory that really exists on disk
	@return a boolean
	@retval true if path exists
	*/
	bool Exists() const;
	
	/// Ensures that the path (to a directory only) exists on disk
	/**
	Create if needed the directory structure contained in the path
	Treats the path only as path of folders. Every segment is taken as folder name. 
	If the path contains file name, RemoveLastSegment must be called before calling EnsurePathExists
	@return a boolean
	@retval true if success
	*/
	bool EnsurePathExists() const;

	/// Creates a subdirectory
	/**
	Creates specified dirname folder on the disk in the directory pointer by \c this 
	@param dirname a WRString ref containing the name of the subdirectory to be created
	@param append a boolean: true, appends the name dirname even to internal representation of the full path, so that it points to the newly created directory
	@return a boolean
	@retval true if the subdirectory was successfully created
	*/
	bool MakeDirectory(WRString& dirname, bool append = true);
//#endif

protected:
	
	/// Internal representation of the path
	/**
	on Windows the path is delimited by \c '\', on Unix, Mac it is POSIX format path delimited by \c '/'
	*/
	mutable WRString	fFullPath; 
};


#endif //WRPath
