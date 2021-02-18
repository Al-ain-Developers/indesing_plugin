//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDPath.h $
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
//  This class is a wrapper around the APath class which provides InDesign specific
//  implementations and extensions to the APath class.
//  
//========================================================================================

#pragma once
#ifndef __IDPath__
#define __IDPath__

// ----- Includes -----
#include "APath.h"

class IPMStream;
class WideString;

using namespace adobe::afl;

/**
 InDesign class used to manipulate a file or directory specified by a path.
 @see AFile
*/
class PUBLIC_DECL IDPath : public APath
{
public:	
	typedef APath inherited;
	typedef object_type data_type;

	/**
	 Default constructor.
	 Constructs an empty APath object.
	 */
	IDPath();

	/**
	 Constructor.
	 Constructs an APath containing one path component.
	 @param component	IN Component in the path.
						   An empty path component is ignored.
	 */
	IDPath(const APathComponent& component);

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
	IDPath(const AString& pathStr, PathType typeHint = kDefaultOSPath);

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
	IDPath(const WideString& pathStr, PathType typeHint = kDefaultOSPath);

	/**
	 Copy constructor.
	 Constructs an IDPath object that is a copy of the given path.
	 @param path	IN Path to copy.
	 */
	IDPath(const IDPath& path);

	/**
	 Copy constructor.
	 Constructs an IDPath object that is a copy of the given path.
	 @param path	IN Path to copy.
	 */
	IDPath(const APath& path);

	/**
	 Destructor.
	 Destroys the IDPath object.
	 */
	virtual ~IDPath();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param rhs	IN Path to swap with this path.
	 */
	friend void swap(IDPath &lhs, IDPath &rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given path to this path.
	 @param rhs	IN Path to assign to this path.
	 @return Reference to the path.
	 */
	IDPath& operator=(const IDPath& rhs);

	IDPath(IDPath&& rhs) noexcept
		: APath(std::move(rhs))
	{
	}

	IDPath& operator=(IDPath&& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given path to this path.
	 @param rhs	IN Path to assign to this path.
	 @return Reference to the path.
	 */
	IDPath& operator=(const APath& rhs);

	/**
	 Equality operator.
	 Test whether this path is equal to the given path.
	 @param rhs	IN Path to test for equality against this path.
	 @return True if this path is equal to the given path, else false.
	 */
	bool operator==(const IDPath& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this path is not equal to the given path.
	 @param rhs	IN Path to test for non-equality against this path.
	 @return True if this path is not equal to the given path, else false.
	 */
	bool operator!=(const IDPath& rhs) const;
	
	/**
	 Addition operator.
	 Appends the given path to the end of this path.
	 @param rhs	IN Path to append to this path.
	 @return Reference to this path.
	 */
	IDPath& operator+=(const IDPath& rhs);

	/**
	 Addition operator.
	 Appends the given path component to the end of this path.
	 @param rhs	IN Path component to append to this path.
	 @return Reference to this path.
	 */
	IDPath& operator+=(const APathComponent& rhs);

	/**
	 Sets the path from the given path string.
	 @param pathStr		IN String containing the path.
	 @param typeHint	IN Type of path contained in the string.
	 					   The hint is only used to optimize the parsing of the path,
	 					   not to specify the actual path type.
						   Default \Ref{kDefaultOSPath}.
	 @return True if the path was set, else false.
	 */
	bool SetPath(const WideString& pathStr, PathType typeHint = kDefaultOSPath);

	/**
	 Appends the given path to this path.
	 @param path	IN Path to append to the end of this path.
	 @return Reference to the path.
	 */
	IDPath& Append(const IDPath& path);

	/**
	 Appends the given path component to this path.
	 @param path	IN Path component to append to the end of this path.
	 @return Reference to the path.
	 */
	IDPath& Append(const APathComponent& component);
};

inline void swap(IDPath &lhs, IDPath &rhs) noexcept
{
	using std::swap;
	swap(static_cast<APath &>(lhs), static_cast<APath &>(rhs));
}
	
inline IDPath& IDPath::operator=(IDPath&& rhs) noexcept
{
	swap(*this, rhs);

	return *this;
}

#endif	// __IDPath__
