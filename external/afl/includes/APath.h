//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/APath.h $
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
#ifndef __APath__
#define __APath__

// ----- Includes -----
#include "AFLDecl.h"
#include "APathComponent.h"
#include "APathIterator.h"
#include "APathReverseIterator.h"
#include "AString.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

#ifdef WINDOWS
class APathImplW;
typedef APathImplW APathImplBase;
#elif defined MACINTOSH
class APathImplM;
typedef APathImplM APathImplBase;
#endif

/**
 Container class used to hold the components of a path.
 A valid path can be an absolute or relative path.
 @see APathComponent
 @see APathIterator
 @see APathReverseIterator
 @see AString
*/
class AFL_DECL APath
{
public:
	typedef APathComponent			value_type;
	typedef APathComponent*			pointer;
	typedef APathComponent&			reference;
	typedef int32					difference_type;
	typedef uint32					size_type;
	typedef APathIterator			iterator;
	typedef APathReverseIterator	reverse_iterator;

	/** Maximum number of characters in a path string. */
	#ifdef WINDOWS
		static const uint32 kMaxPathLength = 32767;
	#elif defined MACINTOSH
		static const uint32 kMaxPathLength = 2048;
	#endif

	/** Constant used to specify the index of the last component in the path. */
	static const uint32 kLastComponentIndex = kMaxUInt32;

	/** Constant used to denote all components upto and including the last component in the path. */
	static const uint32 kToLast = kMaxUInt32;

	/**
	 Identifiers that denote a path type.
	 The identifiers are used to specify the type of path to return in a string,
	 and to provide a hint regarding the type of path when setting a path from a string.
	 */
	enum PathType {
		/** Default OS path: on Windows equivalent to kWinPath; on Mac equivalent to kPosixPath. */
		kDefaultOSPath = 1,
		/** POSIX path: "/folder/file.txt" or "/Volumes/mountpoint/folder/file.txt". */
		kPosixPath,
		/** Windows path: "C:\folder\file.txt" or "#\\#server\mountpoint\folder\file.txt". */
		kWinPath
	};

	/**
	 Identifiers that denote an insertion position.
	 The identifiers are used to specify where to position inserted path components.
	 */
	enum InsertPosition {
		/** Insert the path component after. */
		kInsertAfter = 1,
		/** Insert the path component before. */
		kInsertBefore
	};

	/**
	 Default constructor.
	 Constructs an empty APath object.
	 */
	APath();

	/**
	 Constructor.
	 Constructs an APath containing one path component.
	 @param component	IN Component in the path.
						   An empty path component is ignored.
	 */
	APath(const APathComponent& component);

	/**
	 Constructor.
	 Constructs an APath object from the given path string.\\
	 Call !IsEmpty() after construction to determine if the path was successfully
	 set from the given string.
	 @param pathStr		IN String containing the path.
	 @param typeHint	IN Type of path contained in the string.
	 					   The hint is only used to optimize the parsing of the path,
	 					   not to specify the actual path type.
						   Default \Ref{kDefaultOSPath}.
	 */
	APath(const AString& pathStr, PathType typeHint = kDefaultOSPath);

	/**
	 Copy constructor.
	 Constructs an APath object that is a copy of the given path.
	 @param path	IN Path to copy.
	 */
	APath(const APath& path);

	/**
	 Destructor.
	 Destroys the APath object.
	 */
	virtual ~APath();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param lhs, rhs	IN The paths to swap.
	 */
	friend void swap(APath &lhs, APath& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given path to this path.
	 @param rhs	IN Path to assign to this path.
	 @return Reference to the path.
	 */
	APath& operator=(const APath& rhs);

	/**
	 Copy constructor using rvalue references.
	 Constructs an APath object that is a copy of the given path.
	 @param rhs	IN Path to copy.
	 */
	APath(APath&& rhs) noexcept
		: fpImpl(rhs.fpImpl)
	{
		rhs.fpImpl = nullptr;
	}

	/**
	 Assignment operator using rvalue references.
	 Assigns the given path to this path.
	 @param rhs	IN Path to assign to this path.
	 @return Reference to the path.
	 */
	APath& operator=(APath&& rhs) noexcept;

	/**
	 Equality operator.
	 Test whether this path is equal to the given path.
	 @param rhs	IN Path to test for equality against this path.
	 @return True if this path is equal to the given path, else false.
	 */
	bool operator==(const APath& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this path is not equal to the given path.
	 @param rhs	IN Path to test for non-equality against this path.
	 @return True if this path is not equal to the given path, else false.
	 */
	bool operator!=(const APath& rhs) const;

	/**
	 Addition operator.
	 Appends the given path to the end of this path.
	 @param rhs	IN Path to append to this path.
	 @return A path that is the result of appending the given path to this path.
	 */
	APath operator+(const APath& rhs) const;

	/**
	 Addition operator.
	 Appends the given path to the end of this path.
	 @param rhs	IN Path to append to this path.
	 @return Reference to this path.
	 */
	APath& operator+=(const APath& rhs);

	/**
	 Addition operator.
	 Appends the given path component to the end of this path.
	 @param rhs	IN Path component to append to this path.
	 @return A path that is the result of appending the given path component to this path.
	 */
	APath operator+(const APathComponent& rhs) const;

	/**
	 Addition operator.
	 Appends the given path component to the end of this path.
	 @param rhs	IN Path component to append to this path.
	 @return Reference to this path.
	 */
	APath& operator+=(const APathComponent& rhs);

	/**
	 Returns the path as a string.
	 @param type		IN Type of path to return.
						   Default \Ref{kDefaultOSPath}.
	 @param bMakeLong	IN Denotes whether to prepend a string that flags
						   the path as a long path to some OS file routines.
						   Should be set to true only if the returned path
						   is to be used as an argument to OS file routines.
						   Ignored for POSIX paths and all paths on the Mac.
	 @return The path as a string.
	 */
	AString GetPath(PathType type = kDefaultOSPath, bool bMakeLong = false) const;

	/**
	 Sets the path from the given path string.
	 @param pathStr		IN String containing the path.
	 @param typeHint	IN Type of path contained in the string.
	 					   The hint is only used to optimize the parsing of the path,
	 					   not to specify the actual path type.
						   Default \Ref{kDefaultOSPath}.
	 @return True if the path was set, else false.
	 */
	bool SetPath(const AString& pathStr, PathType typeHint = kDefaultOSPath);

	/**
	 Returns the parent path as a string.
	 @param type		IN Type of path to return.
						   Default \Ref{kDefaultOSPath}.
	 @param bMakeLong	IN Denotes whether to prepend a string that flags
						   the path as a long path to some OS file routines.
						   Should be set to true only if the returned path
						   is to be used as an argument to OS file routines.
						   Ignored for POSIX paths and all paths on the Mac.
	 @return The parent path as a string.
	 */
	AString GetParentPath(PathType type = kDefaultOSPath, bool bMakeLong = false) const;

	/**
	 Sets the parent path from the given path string.
	 @param pathStr		IN String containing the parent path.
	 @param typeHint	IN Type of path contained in the string.
	 					   The hint is only used to optimize the parsing of the path,
	 					   not to specify the actual path type.
						   Default \Ref{kDefaultOSPath}.
	 @return True if the parent path was set, else false.
	 */
	bool SetParentPath(const AString& pathStr, PathType typeHint = kDefaultOSPath);

	/**
	 Appends the given path to this path.
	 @param path	IN Path to append to the end of this path.
	 @return Reference to the path.
	 */
	APath& Append(const APath& path);

	/**
	 Appends the given path component to this path.
	 @param path	IN Path component to append to the end of this path.
	 @return Reference to the path.
	 */
	APath& Append(const APathComponent& component);

	/**
	 Gets a path component's parent path.
	 @param index	IN Zero-based index of the path component whose parent path to retrieve.
	 @return The parent path or an empty path when the path is empty or the index is invalid.
	 */
	APath GetParent(uint32 index = kLastComponentIndex) const;

	/**
	 Gets a path component's parent path.
	 @param iter	IN Path iterator pointing to the path component whose parent path to retrieve.
	 @return The parent path or an empty path if iterator is on the root (first) path component.
	 */
	APath GetParent(const APathIterator& iter) const;

	/**
	 Gets a path component's parent path.
	 @param iter	IN Path reverse iterator pointing to the path component whose parent path to retrieve.
	 @return The parent path or an empty path if iterator is on the root (first) path component.
	 */
	APath GetParent(const APathReverseIterator& iter) const;

	/**
	 Sets a path component's parent path.
	 @param index	IN Zero-based index of the path component whose parent path to set.
					   All parent folders of the path component are replaced.
					   If the current path is empty and index equals \Ref{kLastComponentIndex},
					   then the path is set to the given path. 
	 @param path	IN Path used to set the component's parent path.
	 @return True if the parent path was set, else false.\\
			 False is returned when the path is empty or the index is invalid.
	 */
	bool SetParent(uint32 index, const APath& path);

	/**
	 Sets a path component's parent path.
	 @param iter	IN Path iterator pointing to the path component whose parent path to set.
					   All parent folders of the path component are replaced.
	 @param path	IN Path used to set the component's parent path.
	 @return True if the parent path was set, else false.
	 */
	bool SetParent(const APathIterator& iter, const APath& path);

	/**
	 Sets a path component's parent path.
	 @param iter	IN Path reverse iterator pointing to the path component whose parent path to set.
					   All parent folders of the path component are replaced.
	 @param path	IN Path used to set the component's parent path.
	 @return True if the parent path was set, else false.
	 */
	bool SetParent(const APathReverseIterator& iter, const APath& path);

	/**
	 Extracts a subpath from the path.
	 @param index	IN Zero-based index of the first component in the path that
					   is to be included in the extracted subpath.
	 @param count	IN Maximum number of path components in the path that
					   are to be included in the extracted subpath.
					   \Ref{kToLast} to extract all components to the end of the path.
					   The count must be greater than zero.
	 @return The extracted subpath or an empty path when the index or count is invalid.
	 */
	APath Subpath(uint32 index, uint32 count = kToLast) const;

	/**
	 Extracts a subpath from the path.
	 @param iter	IN Path iterator pointing to the first component in the path that
					   is to be included in the extracted subpath.
	 @param count	IN Maximum number of path components in the path that
					   are to be included in the extracted subpath.
					   \Ref{kToLast} to extract all components to the end of the path.
					   The count must be greater than zero.
	 @return The extracted subpath or an empty path when the path iterator or count is invalid.
	 */
	APath Subpath(const APathIterator& iter, uint32 count = kToLast) const;

	/**
	 Extracts a subpath from the path.
	 @param iter	IN Path reverse iterator pointing to the first component in the path that
					   is to be included in the extracted subpath.
	 @param count	IN Maximum number of path components in the path that
					   are to be included in the extracted subpath.
					   \Ref{kToLast} to extract all components to the end of the path.
					   The count must be greater than zero.
	 @return The extracted subpath or an empty path when the path iterator or count is invalid.
	 */
	APath Subpath(const APathReverseIterator& iter, uint32 count = kToLast) const;

	/**
	 Replaces components in the path with all the components in the given path.
	 @param index	IN Index of the first component in the path that is to be replaced.
					   If the current path is empty and index equals \Ref{kLastComponentIndex},
					   then the path is set to the given path. 
	 @param count	IN Maximum number of path components in the path that are to be replaced.
					   \Ref{kToLast} to replace all components to the end of the path.
					   The count must be greater than zero.
	 @param path	IN Path containing the replacement path components.
	 @return True if the path was replaced, else false.
	 */
	bool Replace(uint32 index, uint32 count, const APath& path);

	/**
	 Replaces components in the path with all the components in the given path.
	 @param iter	IN Path iterator pointing to the first component in the path that
					   is to be replaced.
	 @param count	IN Maximum number of path components in the path that are to be replaced.
					   \Ref{kToLast} to replace all components to the end of the path.
					   The count must be greater than zero.
	 @param path	IN Path containing the replacement path components.
	 @return True if the path was replaced, else false.
	 */
	bool Replace(const APathIterator& iter, uint32 count, const APath& path);

	/**
	 Replaces components in the path with all the components in the given path.
	 @param iter	IN Path reverse iterator pointing to the first component in the path that
					   is to be replaced.
	 @param count	IN Maximum number of path components in the path that are to be replaced.
					   \Ref{kToLast} to replace all components to the end of the path.
					   The count must be greater than zero.
	 @param path	IN Path containing the replacement path components.
	 @return True if the path was replaced, else false.
	 */
	bool Replace(const APathReverseIterator& iter, uint32 count, const APath& path);

	/**
	 Path component access operator.
	 Gets the nth path component in the path.\\
	 This operator is equivalent to calling \Ref{GetComponent}().
	 @param index	IN Zero-based index of the path component to retrieve.
	 @return The path component or an empty path component if the index is invalid.
	 */
	APathComponent operator[](uint32 index) const;

	/**
	 Gets the nth path component in the path.
	 @param index	IN Zero-based index of the path component to retrieve.
	 @return The path component or an empty path component if the index is invalid.
	 */
	APathComponent GetComponent(uint32 index) const;

	/**
	 Sets the nth path component in the path.
	 @param index		IN Zero-based index of the path component to set.
	 @param component	IN Path component used to replace the component at the given index.
	 					   The path component cannot be empty.
	 @return True if the path component was set, else false.
	 */
	bool SetComponent(uint32 index, const APathComponent& component);

	/**
	 Sets the path component pointed to by the iterator.
	 @param iter		IN Path iterator pointing to the path component to set.
	 @param component	IN Path component used to replace the component pointed to by the iterator.
	 					   The path component cannot be empty.
	 @return True if the path component was set, else false.
	 */
	bool SetComponent(const APathIterator& iter, const APathComponent& component);

	/**
	 Sets the path component pointed to by the iterator.
	 @param iter		IN Path reverse iterator pointing to the path component to set.
	 @param component	IN Path component used to replace the component pointed to by the iterator.
	 					   The path component cannot be empty.
	 @return True if the path component was set, else false.
	 */
	bool SetComponent(const APathReverseIterator& iter, const APathComponent& component);

	/**
	 Inserts a path component into the path.
	 @param index		IN Zero-based index of the path component where to perform the insertion.
	 @param component	IN Path component to insert.
	 					   The path component cannot be empty.
	 @param insertPos	IN Specifies whether to insert the new component before or after the path
						   component at the given index.
	 @return True if the path component was inserted, else false.
	 */
	bool InsertComponent(uint32 index, const APathComponent& component, InsertPosition insertPos = kInsertAfter);

	/**
	 Inserts a path component into the path.
	 @param iter		IN Path iterator pointing to the path component where to perform the insertion.
	 @param component	IN Path component to insert.
	 					   The path component cannot be empty.
	 @param insertPos	IN Specifies whether to insert the new component before or after the path
						   component pointed to by the iterator.
	 @return True if the path component was inserted, else false.
	 */
	bool InsertComponent(const APathIterator& iter, const APathComponent& component, InsertPosition insertPos = kInsertAfter);

	/**
	 Inserts a path component into the path.
	 @param iter		IN Path reverse iterator pointing to the path component where to perform the insertion.
	 @param component	IN The path component to insert.
	 					   The path component cannot be empty.
	 @param insertPos	IN Specifies whether to insert the new component before or after the path
						   component pointed to by the iterator.
	 @return True if the path component was inserted, else false.
	 */
	bool InsertComponent(const APathReverseIterator& iter, const APathComponent& component, InsertPosition insertPos = kInsertAfter);

	/**
	 Deletes a path component from the path.
	 @param index	IN Zero-based index of the path component to delete.
	 @return True if the path component was deleted, else false.
	 */
	bool DeleteComponent(uint32 index);

	/**
	 Deletes a path component from the path.
	 @param iter	IN Path iterator pointing to the path component to delete.
	 @return True if the path component was deleted, else false.
	 */
	bool DeleteComponent(const APathIterator& iter);

	/**
	 Deletes a path component from the path.
	 @param iter	IN Path reverse iterator pointing to the path component to delete.
	 @return True if the path component was deleted, else false.
	 */
	bool DeleteComponent(const APathReverseIterator& iter);

	/**
	 Gets the number of path components in the path.
	 @return Number of path components in the path.
	 */
	uint32 Size() const;

	/**
	 Test whether the path is empty.
	 An empty path does not contain any path components.
	 @return True if the path is empty, else false.
	 */
	bool IsEmpty() const;

	/**
	 Tests whether the path is valid.
	 The test checks for path constructs and characters that are illegal on the current platform.
	 @return True if the path is valid, else false.
	 */
	bool IsValid() const;

	/**
	 Test whether the path is an absolute path.
	 An abslute path is a full path that may contain alias components.
	 @return True if the path is absolute, else false if a relative path.
	 */
	bool IsAbsolute() const;

	/**
	 Test whether the path is a relative path.
	 A relative path is a partial path that may contain alias components.
	 @return True if the path is relative, else false if an absolute path.
	 */
	bool IsRelative() const;

	/**
	 Explicitly sets the path as an absolute path.
	 */
	void SetAbsolute();

	/**
	 Explicitly sets the path as a relative path.
	 */
	void SetRelative();

	/**
	 Changes a relative path into an absolute path.
	 This path must be valid and relative for this method to succeed.
	 @param pPath			IN Pointer to a valid and absolute path this path is relative to.
	 						   If nullptr, the path is assumed to be relative to the application's
							   current working directory.
	 @param bResolveAliases	IN Denotes whether to resolve aliases in the resulting absolute path.
	 @return True if the path is successfully made into a absolute path, else false.
	 */
	bool MakeAbsolute(const APath* pPath = nullptr, bool bResolveAliases = true);

	/**
	 Resolves all the directory aliases in the path.
	 After calling this method the path will not contain any directory alias components.
	 @return True the path contained any aliases, else false.\\
			 Note: a return value of false does not denote a failure, only that the path
				   did not contain any aliases.
	 */
	bool ResolveAliases();

	/**
	 Returns a random-access iterator positioned on the first path component.
	 The iterator is used to iterate over the path components in the path.
	 @return Iterator positioned on the first path component or just beyond the end for an empty path.
	 */
	iterator begin() const;

	/**
	 Returns a random-access iterator positioned past the last path component.
	 The iterator is used to iterate over the path components in the path.
	 @return Iterator positioned just beyond the last path component.
	 */
	iterator end() const;

	/**
	 Returns a random-access reverse iterator positioned on the first path component in a reversed path.
	 The iterator is used to iterate over the path components in the path in reverse.
	 @return Iterator positioned to last path component or just before the beginning of an empty path.
	 */
	reverse_iterator rbegin() const;

	/**
	 Returns a random-access reverse iterator positioned past the last path component in a reversed path.
	 The iterator is used to iterate over the path components in the path in reverse.
	 @return Iterator positioned just before the first path component.
	 */
	reverse_iterator rend() const;

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

protected:
	APathImplBase* fpImpl;
};

}	// namespace afl
}	// namespace adobe

namespace adobe
{
namespace afl
{
inline void swap(APath &lhs, APath &rhs) noexcept
{
	using std::swap;
	swap(lhs.fpImpl, rhs.fpImpl);
}

inline APath& APath::operator=(APath&& rhs) noexcept
{
	using std::swap;
	swap(*this, rhs);

	return *this;
}
}
}

#endif	// __APath__
