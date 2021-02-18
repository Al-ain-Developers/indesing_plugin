//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AFile.h $
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
//========================================================================================

#pragma once
#ifndef __AFile__
#define __AFile__

// ----- Includes -----
#include "AFLDecl.h"
#include "AErrors.h"
#include "APath.h"
#include "APathComponent.h"
#include "AString.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

#ifdef WINDOWS

class AFileImplW;
typedef AFileImplW AFileImplBase;

typedef int32	AOSType;

#elif defined MACINTOSH
class AFileImplM;
typedef AFileImplM AFileImplBase;

/** Macintosh system file type. */

typedef OSType	AOSType;

#endif

/**
 Class used to manipulate a file or directory specified by a path.
 @see APath
 @see APathComponent
 @see AString
 */
class AFL_DECL AFile
{
#ifdef MACINTOSH
    friend class MacFileUtils;
#endif
    
public:
	/**
	 Default constructor.
	 Constructs an AFile object with no path.
	 */
	AFile();

	/**
	 Constructor.
	 Constructs an AFile object pointing to the given path.
	 @param path	IN Path to set the file's path to.
	 */
	AFile(const APath& path);

	/**
	 Constructor.
	 Constructs an AFile object pointing to the given path.
	 @param pathStr	IN String containing the path to set the file's path to.
	 */
	AFile(const AString& pathStr);

	/**
	 Copy constructor.
	 Constructs an AFile object that is a copy of the given file.
	 @param file	IN File object to copy.
	 */
	AFile(const AFile& file);

	/**
	 Destructor.
	 Destroys the AFile object.
	 */
	virtual ~AFile();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param lhs, rhs	IN The files to swap.
	 */
	friend void swap(AFile &lhs, AFile& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given file to this file.
	 @param rhs	IN File to assign to this file.
	 @return Reference to this file.
	 */
	AFile& operator=(const AFile& rhs);

	/**
	 Copy constructor using rvalue references.
	 Constructs an AFile object that is a copy of the given file.
	 @param rhs	IN File object to copy.
	 */
	AFile(AFile&& rhs) noexcept
		: fpImpl(rhs.fpImpl)
	{
		rhs.fpImpl = nullptr;
	}

	/**
	 Assignment operator using rvalue references.
	 Assigns the given file to this file.
	 @param rhs	IN File to assign to this file.
	 @return Reference to this file.
	 */
	AFile& operator=(AFile&& rhs) noexcept;

	/**
	 Equality operator.
	 Test whether this file's path is identical to the given file's path.
	 @param rhs	IN File to test for equality against this file.
	 @return True if this file's path is identical to the given file's path, else false.
	 */
	bool operator==(const AFile& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this file's path is not identical to the given file's path.
	 @param rhs	IN File to test for non-equality against this file.
	 @return True if this file's path is not identical to the given file's path, else false.
	 */
	bool operator!=(const AFile& rhs) const;

	/**
	 Test whether the path is set.
	 @return True if the path is set, else false.
	 */
	bool HasPath() const;

	/**
	 Tests whether the file's path is valid.
	 The test checks for path constructs and characters that are illegal on the current platform.
	 @return True if the path is valid, else false.
	 @see APath::IsValid
	 */
	bool HasValidPath() const;

	/**
	 Returns the file's path.
	 @return The path.
	 */
	APath GetPath() const;

	/**
	 Returns the file's path as a string.
	 On Windows, a UTF16 UNC or local path.
	 On the Mac, a UTF16 POSIX path.
	 @param bMakeLong	IN Denotes whether to prepend a string that flags
						   the path as a long path to some OS file routines.
						   Should be set to true only if the returned path
						   is to be used as an argument to OS file routines.
						   Ignored for POSIX paths and all paths on the Mac.
	 @return The path string.
	 */
	AString GetPath(bool bMakeLong) const;

	/**
	 Sets the file's path.
	 If the path is empty, all cached attributes are cleared.
	 @param path	IN Valid path to set the file's path to.
					   An empty path to remove file's path.
	 */
	void SetPath(const APath& path);
	void SetPath(APath&& path);

	/**
	 Sets the file's path.
	 If the path is empty, all cached attributes are cleared.
	 @param pathStr	IN String containing the path to set the file's path to.
					   An empty string to remove file's path.
	 */
	void SetPath(const AString& pathStr);

	/**
	 Resolves all the directory aliases in the file's path.
	 After calling this method the path will not contain any directory alias components.
	 @see APath::ResolveAliases
	 */
	void ResolvePathAliases();

	/**
	 Test whether the parent path is set.
	 @return True if the parent path is set, else false.
	 */
	bool HasParentPath() const;

	/**
	 Returns the file's parent path.
	 @return The parent path.
	 */
	APath GetParentPath() const;

	/**
	 Returns the file's parent path as a string.
	 On Windows, a UTF16 UNC or local path.
	 On the Mac, a UTF16 POSIX path.
	 @param bMakeLong	IN Denotes whether to prepend a string that flags
						   the path as a long path to some OS file routines.
						   Should be set to true only if the returned path
						   is to be used as an argument to OS file routines.
						   Ignored for POSIX paths and all paths on the Mac.
	 @return The parent path string.
	 */
	AString GetParentPath(bool bMakeLong) const;

	/**
	 Sets the file's parent path.
	 @param parentPath	IN Valid path to set the file's parent path to.
						   An empty path to remove file's parent path.
	 */
	void SetParentPath(const APath& parentPath);

	/**
	 Sets the file's parent path.
	 @param parentPathStr	IN String containing the path to set the file's parent path to.
							   An empty string to remove file's parent path.
	 */
	void SetParentPath(const AString& parentPathStr);

	/**
	 Returns the last component of the file's path.
	 @return The last component.
	 */
	APathComponent GetName() const;

	/**
	 Returns the last component of the file's path as a string.
	 @return The last component as a string.
	 */
	AString GetNameStr() const;

	/**
	 Sets the last component in the file's path.
	 @param name	IN Path component containing the new file name, or an empty
					   component to remove the last component in the file's path.
	 @return True if the last component was set, else false.
	 */
	bool SetName(const APathComponent& name);

	/**
	 Sets the last component in the file's path.
	 @param nameStr	IN String containing the new file name, or an empty
					   string to remove the last component in the file's path.
	 @return True if the last component was set, else false.
	 */
	bool SetName(const AString& nameStr);

	/**
	 Appends a component to the end of the file's path.
	 @param name	IN Path component containing the file name to append to the 
					   of the file's path.  If the component is empty, it is ignored.
	 @return True if the name was appended, else false.
	 */
	bool AppendName(const APathComponent& name);

	/**
	 Appends a component to the end of the file's path.
	 @param nameStr	IN String containing the file name to append to the 
					   of the file's path.  If the string is empty, it is ignored.
	 @return True if the name was appended, else false.
	 */
	bool AppendName(const AString& nameStr);

	/**
	 Removes the last component from the file's path.
	 @return True if the last component was removed or the file's path is empty,
			 else false.
	 */
	bool RemoveName();

	/**
	 Makes a new empty file on the file system using the objects path.
	 Attributes set before the file existed are set if the create succeeds.
	 Any errors encountered when setting the attributes are ignored.
	 @param bCreateParent	IN If true, parent folders that don't exist are created.
							   If false, the parent path must exist.
	 @param osErr			OUT Error code returned by the OS if the create fails.
	 							nullptr if not interested in the OS error code. 
	 @return True if the file is created, else false.
	 */
	bool MakeFile(bool bCreateParent = true, AOSErr* osErr = nullptr);

	/**
	 Makes a new empty directory on the file system using the objects path.
	 Attributes set before the directory existed are set if the create succeeds.
	 Any errors encountered when setting the attributes are ignored.
	 @param bCreateParent	IN If true, parent folders that don't exist are created.
							   If false, the parent path must exist.
	 @param osErr			OUT Error code returned by the OS if the create fails.
	 							nullptr if not interested in the OS error code. 
	 @return True if the directory is created, else false.
	 */
	bool MakeDirectory(bool bCreateParent = true, AOSErr* osErr = nullptr);

	/**
	 Deletes the file or directory from the file system. \\
	 If a directory, it must be empty (contain no files or folders).
	 To delete a non-empty directory, call CoreFileUtils::DeleteDirectory().
	 @return True if successfully deleted, else false.
	 */
	bool Delete() const;

	/**
	 Set whether the file or directory specified by the path is deleted when the object is destroyed.
	 Once set, the DeleteOnDestroy flag's state persist until explicitly reset, even if the file's
	 path is changed.
	 By default, the file or directory is not deleted when the object is destructed.
	 @param bDeleteOnDestroy	IN If true, the file or directory is deleted.
	 */
	void DeleteOnDestroy(bool bDeleteOnDestroy = true);

	/**
	 Test whether the file or directory exists on the file system.
	 @return True if exists, else false.
	 */
	bool Exists() const;

	/**
	 Test whether the parent path of the file or directory exists on the file system.
	 @return True if the parent path exists, else false.
	 */
	bool ParentExists() const;

	/**
	 Resolves an alias by setting it to the file or directory the alias references.
	 @return True if the file or directory is successfully resolved, else false. 
	 @see CoreFileUtils::ResolveAlias
	 */
	bool ResolveAlias();

	/**
	 Identifiers that denote the type of file access desired.
	 You cannot obtain access to a file with an access mode that conflicts with
	 a sharing mode specified in a previous open request (from any process) whose
	 handle is still open.
	 */
	enum AccessMode {
		/** Read access; open the file for reading only. */
		kReadAccess = 1,
		/** Write access; open the file for writing only. */
		kWriteAccess,
		/** Read and write access; open the file for reading and writing. */
		kReadWriteAccess
	};

	/**
	 Identifiers that denote the type of file sharing to allow.
	 You cannot share access to a file with a sharing mode that conflicts with an
	 access mode specified in a previous open request (from any process) whose
	 handle is still open.
	 */
	enum ShareMode {
		/** Share read access; others can open the file for reading only. */
		kShareReadAccess = 1,
		/** Share write access; others can open the file for writing only. */
		kShareWriteAccess,
		/** Share read and write access; others can open the file for reading and writing. */
		kShareReadWriteAccess,
		/** Exclusive access; others cannot open the file for reading nor writing. */
		kExclusiveAccess
	};

	/**
	 Test whether the file or directory can be opened with the specified access and sharing mode.
	 The state of whether a file can be opened may change at any time, so it is best to attempt to
	 open the file immediately following the call to CanOpen(). 
	 @param access	IN Type of file access desired.
	 @param sharing	IN Type of file sharing to allow.
	 @return True if the file or directory can be opened with the given access and sharing mode,
			 else false.
	 */
	bool CanOpen(AccessMode access, ShareMode sharing) const;

	/**
	 Test whether the file or directory is currently open.
	 @return True if open, else false.
	 */
	bool IsOpen() const;

	/**
	 Test whether the file or directory is empty.
	 An empty file contains 0 bytes.
	 An empty directory does not contain any files.
	 @return True if the file is empty or does not exist, else false.
	 */
	bool IsEmpty() const;

	/**
	 Returns the size of a file or directory.
	 If a file, returns the number of bytes in the file.
	 If a directory, returns the number of files contained in the directory.
	 @return The size of the file or directory,
			 0 if the file or directory is empty or does not exist.
	 */
	uint64 GetSize() const;

	/**
	 Sets the last modified time of an existing file or directory to the current system time.
	 @return True if the last modified time was successfully set, else false.
	 */
	bool Touch();

	/**
	 Identifiers that denote Boolean attributes that can be retrieved and/or set.
	 The identifiers are used to get and set the Boolean attributes of a file or directory.
	 */
	enum BoolAttribute {
		/** Is a file. Cannot be set. */
		kFile = 1,
		/** Is a directory. Cannot be set. */
		kDirectory,
		/** Is an alias. Cannot be set. */
		kAlias,
		/** Is an alias to a file. Cannot be set. */
		kFileAlias,
		/** Is an alias to a directory. Cannot be set. */
		kDirectoryAlias,
		/** File or directory can be read. Cannot be set. */
		kReadable,
		/** File or directory can be written. Cannot be set. */
		kWritable,
		/** On Mac, file or directory is locked.\\
			On Windows, file or directory has the read-only attribute set. */
		kLocked,
		/** File or directory is hidden. */
		kHidden,
		/** File is stationary. Applicable on the Mac only. */
		kStationary
	};

	/**
	 Returns the value of the given Boolean attribute.
	 @param attribute	IN Boolean attribute to get.
	 @return The value of the given attribute.\\
			 False if the file or directory does not exist or access was denied.
	 */
	bool GetAttribute(BoolAttribute attribute) const;

	/**
	 Sets a Boolean attribute.
	 @param attribute	IN Boolean attribute to set.
	 @param bValue		IN Value of the given attribute.
	 @return True if the attribute was successfully set, else false.
	 */
	bool SetAttribute(BoolAttribute attribute, bool bValue);

	/**
	 Structure used to retrieve the value of all the Boolean attributes at once.
	 */
	struct BoolAttributes {
		/** True if a file, else false. */
		bool bFile;
		/** True if a directory, else false. */
		bool bDirectory;
		/** True if an alias, else false. */
		bool bAlias;
		/** On Mac, true if the file or directory is locked, else false. \\
			On Windows, true if the file or directory has the read-only attribute set, else false. */
		bool bLocked;
		/** True if the file or directory is hidden, else false. */
		bool bHidden;
		/** On Mac, true if a file is stationary, else false.\\
			Always false on Windows. */
		bool bStationary;
		/** True if an alias to a file, else false.\\
			Always false if the bGetAliasAttrs argument is set to false. */
		bool bFileAlias;
		/** True if an alias to a directory, else false.\\
			Always false if the bGetAliasAttrs argument is set to false. */
		bool bDirectoryAlias;
		/** True if the file or directory can be read, else false.\\
			Always false if the bGetAccessAttrs argument is set to false. */
		bool bReadable;
		/** True if the file or directory can be written, else false.\\
			Always false if the bGetAccessAttrs argument is set to false. */
		bool bWritable;
	};

	/**
	 Returns the value of all the Boolean attributes.
	 @param attributes		OUT Value of all the Boolean attributes.
	 @param bGetAliasAttrs	IN Denotes whether to get the extended alias attributes
							   that specify if the alias references a file or directory.\\
							   Getting the extended alias attributes can be expensive,
							   so only pass true if you will use the returned attributes.
	 @param bGetAccessAttrs	IN Denotes whether to get the file access read/write attributes.\\
							   Getting the access attributes can be expensive,
							   so only pass true if you will use the returned attributes.
	 @return True if the attributes were successfully retrieved, else false.
	 */
	bool GetAttributes(BoolAttributes& attributes, bool bGetAliasAttrs, bool bGetAccessAttrs) const;

	/**
	 Identifiers that denote the time attributes that can be retrieved and set.
	 The identifiers are used to get and set time attributes of the file or directory.\\
	 The time is measured in 100-nanosecond intervals since January 1, 1601 (UTC).
	 */
	enum TimeAttribute {
		/** Time the file or directory was created. */
		kCreated = 1,
		/** Time the file or directory was last modified. */
		kModified,
		/** Time the file or directory was last accessed. */
		kAccessed
	};

	/**
	 Returns the value of the given time attribute.
	 @param attribute	IN Time attribute to get.
	 @return The value of the given attribute.\\
			 0 if the file or directory does not exist or access was denied.
	 */
	ATime GetAttribute(TimeAttribute attribute) const;

	/**
	 Sets a time attribute.
	 @param attribute	IN Time attribute to set.
	 @param time		IN Value of the given attribute.
	 @return True if the attribute was successfully set, else false.
	 */
	bool SetAttribute(TimeAttribute attribute, const ATime& time);

	/**
	 Structure used to retrieve the value of all the time attributes at once.
	 */
	struct TimeAttributes {
		/** Time the file or directory was created. */
		ATime created;
		/** Time the file or directory was last modified. */
		ATime modified;
		/** Time the file or directory was last accessed. */
		ATime accessed;
	};

	/**
	 Returns the value of all the time attributes.
	 @param attributes	OUT Value of all the time attributes.
	 @return True if the attributes were successfully retrieved, else false.
	 */
	bool GetAttributes(TimeAttributes& attributes) const;

	/**
	 Identifiers that denote the AOSType attributes that can be retrieved and set.
	 The identifiers are used to get and set AOSType attributes of the file.
	 */
	enum OSTypeAttribute {
		/** File's creator. Applicable on the Mac only. */
		kCreator = 1,
		/** File's type. Applicable on the Mac only. */
		kType
	};

	/**
	 Gets the value of the given AOSType attribute.
	 @param attribute	IN AOSType attribute to get.
	 @param attribute	OUT Value of the AOSType attribute.
	 @return True if the attribute was successfully retrieved, else false.
	 */
	bool GetAttribute(OSTypeAttribute attribute, AOSType& osType) const;

	/**
	 Sets a AOSType attribute.
	 @param attribute	IN AOSType attribute to set.
	 @param str			IN Value of the given attribute.
	 @return True if the attribute was successfully set, else false.
	 */
	bool SetAttribute(OSTypeAttribute attribute, const AOSType& osType);

	/**
	 Structure used to retrieve the value of all the AOSType attributes at once.
	 */
	struct OSTypeAttributes {
		/** File's creator. Applicable on the Mac only. */
		AOSType creator;
		/** File's type. Applicable on the Mac only. */
		AOSType type;
	};

	/**
	 Returns the value of all the AOSType attributes.
	 @param attributes	OUT Value of all the AOSType attributes.
	 @return True if the attributes were successfully retrieved, else false.
	 */
	bool GetAttributes(OSTypeAttributes& attributes) const;

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

protected:
	/**
	 Override this method in a subclass to be notified when the path changes.
	 This method is never called during construction of the object.
	 @param path	OUT New file path.
	 */
	virtual void PathChanged(const AString& path);

	AFileImplBase* fpImpl;
};

}	// namespace afl
}	// namespace adobe

namespace adobe
{
namespace afl
{
inline void swap(AFile &lhs, AFile &rhs) noexcept
{
	using std::swap;
	swap(lhs.fpImpl, rhs.fpImpl);
}

inline AFile& AFile::operator=(AFile&& rhs) noexcept
{
	using std::swap;
	swap(*this, rhs);

	return *this;
}
}
}

#endif	// __AFile__
