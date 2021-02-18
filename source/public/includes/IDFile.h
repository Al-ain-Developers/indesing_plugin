//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDFile.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This class is a wrapper around the AFile class which provides InDesign specific
//  implementations and extensions to the AFile class.
//  
//========================================================================================

#pragma once
#ifndef __IDFile__
#define __IDFile__

// ----- Includes -----
#include "AFile.h"
#include "IDPath.h"
#include "PMString.h"
#include "WideString.h"
#include "IDThreading.h"

class IPMStream;

using namespace adobe::afl;

/**
 InDesign class used to manipulate a file or directory specified by a path.
 @see AFile
*/
class PUBLIC_DECL IDFile : public AFile
{
public:	
	typedef AFile inherited;
	typedef object_type data_type;

	/**
	 Default constructor.
	 Constructs an IDFile object pointing to the current working directory.
	 */
	IDFile();

	/**
	 Constructor.
	 Constructs an IDFile object pointing to the given path.
	 @param path	IN Path to set the file's path to.
	 */
	IDFile(const APath& path);

	/**
	 Constructor.
	 Constructs an IDFile object pointing to the given path.
	 @param path	IN Path to set the file's path to.
	 */
	IDFile(const IDPath& path);

	/**
	 Constructor.
	 Constructs an IDFile object pointing to the given path.
	 @param pathStr	IN String containing the path to set the file's path to.\\
					   On Windows, a UTF16 UNC or local path.\\
					   On the Mac, a UTF16 POSIX path
	 */
	IDFile(const AString& pathStr);

	/**
	 Constructor.
	 Constructs an IDFile object pointing to the given path.
	 @param pathStr	IN String containing the path to set the file's path to.\\
					   On Windows, a UTF16 UNC or local path.\\
					   On the Mac, a UTF16 POSIX path
	 */
	explicit IDFile(const WideString& pathStr);

	/**
	 Copy constructor.
	 Constructs an IDFile object that is a copy of the given file.
	 @param file	IN File object to copy.
	 */
	IDFile(const AFile& file);

	/**
	 Copy constructor.
	 Constructs an IDFile object that is a copy of the given file.
	 @param file	IN File object to copy.
	 */
	IDFile(const IDFile& file);

	/**
	 Destructor.
	 Destroys the IDFile object.
	 */
	virtual ~IDFile();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param rhs	IN File to swap with this file.
	 */
	friend void swap(IDFile &a, IDFile &b) noexcept;

	/**
	 Assignment operator.
	 Assigns the given file to this file.
	 @param rhs	IN File to assign to this file.
	 @return Reference to this file.
	 */
	IDFile& operator=(const IDFile& rhs);

	IDFile(IDFile&& rhs) noexcept
		: AFile(std::move(rhs))
#ifdef DEBUG
		, fDebugPath(std::move(rhs.fDebugPath))
#endif
#ifdef WINDOWS
		, fTmpPathStr(std::move(rhs.fTmpPathStr))
#endif
	{
#ifdef DEBUG
		rhs.fDebugPath = 0;
#endif
	}

	IDFile& operator=(IDFile&& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given file to this file.
	 @param rhs	IN File to assign to this file.
	 @return Reference to this file.
	 */
	IDFile& operator=(const AFile& rhs);

	/**
	 Equality operator.
	 Test whether this file's path is identical to the given file's path.
	 @param rhs	IN File to test for equality against this file.
	 @return True if this file's path is identical to the given file's path, else false.
	 */
	bool operator==(const IDFile& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this file's path is not identical to the given file's path.
	 @param rhs	IN File to test for non-equality against this file.
	 @return True if this file's path is not identical to the given file's path, else false.
	 */
	bool operator!=(const IDFile& rhs) const;

	/**
	 Sets the file's path.
	 @param path	IN Path to set the file's path to.
					   An empty path to remove file's path.
	 */
	void SetPath(const IDPath& path);

	/**
	 Sets the file's path.
	 @param pathStr	IN String containing the path to set the file's path to.
					   An empty string to remove file's path.\\
					   On Windows, a UTF16 UNC or local path.\\
					   On the Mac, a UTF16 POSIX path
	 */
	void SetPath(const WideString& pathStr);

	/**
	 Returns whether the file is a stationary file.
	 Returns the value of the file's stationary attribute.
	 @return True if a stationary file, else false.\\
			 False if the file or directory does not exist and the attribute has not been set.
	 */
	bool IsStationary() const;
	
	/**
	 Sets the file's stationary attribute.
	 @param bStationary		IN Value of the stationary attribute.
	 @return True if the stationary attribute was successfully set, else false.
	 */
	bool SetStationary(bool bStationary);
	
	/**
	 Persistence-related method for saving or restoring the
	 state of an IDFile object instance.
	 @param s IN Stream to read from or write to.
	 */
	void ReadWrite(IPMStream* s);


	//====================================================================================
	//
	// DEPRECATED Methods
	//
	// The following deprecated methods are provided to aid in the integration of the
	// new file library (AFL) architecture into InDesign.  New code should avoid using
	// the following methods.
	//
	//====================================================================================

	/**
	 Constructor.
	 Constructs an IDFile object pointing to the given path.
	 @param pathStr	IN String containing the path to set the file's path to.\\
					   On Windows, a UTF16 UNC or local path.\\
					   On the Mac, a Unicode HFS path.
	 */
	explicit IDFile(const PMString& pathStr);

	/**
	 Returns the last component of the file's path as a Unicode name.
	 On the Mac, the name is returned as a Unicode HFS file name; colons in
	 the name are changed to forward slashes.
	 @return The last path component as a Unicode name.
	 */
	PMString GetFileName() const;

	/**
	 Sets the last component in the file's path.
	 On the Mac, all forward slashes in the name are changed to colons.
	 @param nameStr	IN String containing the new file name, or an empty
					   string to remove the last component in the file's path.
	 @return True if the last component was set, else false.
	 */
	bool16 SetFileName(const PMString& nameStr);

#ifdef WINDOWS
	/**@name Windows specific methods */
	//@{

	/**
	 Legacy persistence-related method for saving or restoring the
	 state of an IDFile object instance in the same manner used to
	 persist a SysFile object.
	 On Windows the IDFile is persisted as a PMString.
	 On the Mac the IDFile is persisted as an FSSpec.
	 This method should only be used to persist an IDFile object
	 that was previously persisted as a SysFile object.
	 @param iPMStream	IN Stream to read the instance data from
						   or write the instance data to.
	 */
	void ReadWriteDeprecated(IPMStream* iPMStream);

	/**
	 Sets the file's path.
	 @param str	IN String containing the path to set the file's path to.
				   An empty string to remove file's path.
	 */
	void SetString(const PMString& str);

	/**
	 Sets the file's path.
	 @param cStr		IN C string containing the path to set the file's path to.
						   An empty string to remove file's path.
	 */
	void SetCString(ConstCString cStr);

	/**
	 Sets the file's path.
	 @param xStr IN T string containing the path to set the file's path to.
					An empty string to remove file's path.
	 */
	void SetTString(const TCHAR* xStr);

	/**
	 Sets the file's path.
	 @param xStr	IN Character buffer with or without a terminating zero.
					   An empty buffer to remove file's path.
	 @param nBytes	IN Number of chars in the buffer excluding the terminating
					   zero if present.
	 */
	void SetXString(const char* xStr, int32 nBytes);

	/**
	 Sets the file's path.
	 @param xStr		IN Unicode UTF16 buffer with or without a terminating zero.
						   An empty buffer to remove file's path.
	 @param nDblBytes	IN Number of UTF16s in the buffer excluding the terminating
						   zero if present.
	 */
	void SetXString(const UTF16TextChar* xStr, int32 nDblBytes);

	/**
	 Returns the file's path as a PMString.
	 @return PMString containing the file's path.
	 */
	PMString GetString() const;

	/**
	 Returns the file's path as a null terminated TCHAR string.
	 @return Null terminated TCHAR string containing the file's path.
	 */
	TCHAR* GrabTString();

	/**
	 Returns the file's path as a const null terminated TCHAR string.
	 @return Const null terminated TCHAR string containing the file's path.
	 */
	const TCHAR* GrabTString() const;

	/**
	 Returns the file's path as a 0 terminated UTF16 buffer.
	 @return 0 terminated UTF16 buffer containing the file's path.
	 */
	const UTF16TextChar* GrabWString() const;

	//@}
#elif defined MACINTOSH
	/**
	 Returns the parent directory identifier of this file.
	 @return The parent directory identifier of the file. 
			 0 if the parent directory identifier cannot be obtained.
	 */
	uint32 GetParId() const;

	/**
	 Returns the node identifier of this file.
	 @return The node identifier of the file. 
			 0 if the node identifier cannot be obtained.
	 */
	uint32 GetNodeId() const;
	//@}
#endif

private:
#ifdef DEBUG
	/**
	 Called by AFile when the current path changes.
	 @param path	IN Current file/directory path.
	 */
	void PathChanged(const AString& path);

	/**
	 Debug build only!!!
	 Contains the current file/directory path.
	 On Windows a UTF16 path.
	 On the Mac a UTF8 POSIX path.
	 NULL if the current path is empty.
	 */
#ifdef WINDOWS
	wchar_t*	fDebugPath;
#elif defined MACINTOSH
	char*		fDebugPath;
#endif
#endif

#ifdef WINDOWS
	/**
	 Windows only!!!
	 Temporary path string used to return the path as a PMString, CString,
	 ConstCString, TCHAR buffer, WString, or UTF16TextChar buffer. This path
	 string is not guaranteed, nor expected, to match the IDFile's current path.
	 */
	PMString	fTmpPathStr;
	mutable IDThreading::spin_mutex fTmpPathStrMutex;
#endif
};

inline void swap(IDFile &lhs, IDFile &rhs) noexcept
{
	using std::swap;

	swap(static_cast<AFile &>(lhs), static_cast<AFile &>(rhs));
#ifdef DEBUG
	swap(lhs.fDebugPath, rhs.fDebugPath);
#endif
#ifdef WINDOWS
	swap(lhs.fTmpPathStr, rhs.fTmpPathStr);
#endif
}
	
inline IDFile& IDFile::operator=(IDFile&& rhs) noexcept
{
	swap(*this, rhs);

	return *this;
}

// define adobe::type_info<IDFile> to avoid typeid classes when moving across DLL boundaries
ADOBE_NAME_TYPE_0("idfile:indesign:adobe", IDFile)

#endif	// __IDFile__
