//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/APathComponent.h $
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
#ifndef __APathComponent__
#define __APathComponent__

// ----- Includes -----
#include "AFLDecl.h"
#include "AString.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

/**
 Determines if the given character is a valid Windows local drive letter.
 @param c	IN UTF16 character to test.
 @return True if the given character is a valid Windows local drive letter, else false.
 */
AFL_DECL bool IsWinDriveLetter(UTF16TextChar c);

/**
 Determines if the given character is a valid Windows local drive delimiter.
 @param c	IN UTF16 character to test.
 @return True if the given character is a valid Windows local drive delimiter, else false.
 */
AFL_DECL bool IsWinDriveDelimiter(UTF16TextChar c);

class APathComponentImpl;

/**
 Container class used to hold the name of a single component of a path.
 A path componenet can reference a volume, directory or file name.
 @see AString
*/
class AFL_DECL APathComponent
{
public:
	/** Maximum number of characters in a path component string. */
	#ifdef WINDOWS
		static const uint32 kMaxComponentLength = 255;
	#elif defined MACINTOSH
		static const uint32 kMaxComponentLength = 255;
	#endif

	/**
	 Returns the string used to represent the current directory alias.
	 This string can be used to construct a path component to a
	 path's current directory.
	 @return String used to represent the current directory alias.
	 */
	static AString CurrentDirAlias();

	/**
	 Returns the string used to represent the parent of the current directory alias.
	 This string can be used to construct a path component to the parent path of
	 a path's current directory.
	 @return String used to represent the parent of the current directory alias.
	 */
	static AString ParentDirAlias();

	/**
	 Default constructor.
	 Constructs an empty APathComponent object.
	 */
	APathComponent();

	/**
	 Constructor.
	 Constructs an APathComponent object from the given string.
	 @param name	IN String containing the path component name.
	 */
	APathComponent(const AString& name);

	/**
	 Copy constructor.
	 Constructs an APathComponent object that is a copy of the given path component.
	 @param pathComponent	IN Path component to copy.
	 */
	APathComponent(const APathComponent& pathComponent);

	/**
	 Destructor.
	 Destroys the APathComponent object.
	 */
	virtual ~APathComponent();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param lhs, rhs	IN The path components to swap.
	 */
	friend void swap(APathComponent &lhs, APathComponent& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given path component to this path component.
	 @param rhs	IN Path component to assign to this path component.
	 @return Reference to the path component.
	 */
	APathComponent& operator=(const APathComponent& rhs);

	/**
	 Copy constructor using rvalue references.
	 Constructs an APathComponent object that is a copy of the given path component.
	 @param rhs	IN Path component to copy.
	 */
	APathComponent(APathComponent&& rhs) noexcept
		: fpImpl(rhs.fpImpl)
	{
		rhs.fpImpl = nullptr;
	}

	/**
	 Assignment operator using rvalue references.
	 Assigns the given path component to this path component.
	 @param rhs	IN Path component to assign to this path component.
	 @return Reference to the path component.
	 */
	APathComponent& operator=(APathComponent&& rhs) noexcept;

	/**
	 Equality operator.
	 Test whether this path component is equal to the given path component.
	 @param rhs	IN Path component to test for equality against this path component.
	 @return True if this path component is equal to the given path component, else false.
	 */
	bool operator==(const APathComponent& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this path component is not equal to the given path component.
	 @param rhs	IN Path component to test for non-equality against this path component.
	 @return True if this path component is not equal to the given path component, else false.
	 */
	bool operator!=(const APathComponent& rhs) const;

	/**
	 Returns the path component's full name.
	 @return The path component's full name as a UTF16 string.
	 */
	AString Get() const;

	/**
	 Sets the path component's full name.
	 @param fullName	IN String containing the path component's new full name.
	 @return Reference to the path component.
	 */
	APathComponent& Set(const AString& fullName);

	/**
	 Returns the path component's base name.
	 The base name is the portion of the full name before the last period ('.').
	 @return The path component's base name as a UTF16 string.
	 */
	AString GetBase() const;

	/**
	 Sets the path component's base name.
	 The base name is the portion of the full name before the last period ('.').
	 @param baseName	IN String containing the path component's new base name.
	 @return Reference to the path component.
	 */
	APathComponent& SetBase(const AString& baseName);

	/**
	 Returns the path component's extension.
	 The extension is the portion of the full name after the last period ('.').
	 @return The path component's extension as a UTF16 string.
	 */
	AString GetExtension() const;

	/**
	 Sets the path component's extension.
	 The extension is the portion of the full name after the last period ('.').
	 @param extension	IN String containing the path component's new extension.
	 @return Reference to the path component.
	 */
	APathComponent& SetExtension(const AString& extension);

	/**
	 Tests whether the path component is empty.
	 @return True if the path component is empty, else false.
	 */
	bool IsEmpty() const;

	/**
	 Tests whether the path component is an alias.
	 The test checks to see if the component is an alias to the current or parent directory.
	 @return True if the path component is an alias, else false.
	 */
	bool IsAlias() const;

	/**
	 Tests whether the path component is valid.
	 The test checks for characters in the full name that are illegal on the current platform.
	 The test also checks the full name length to make sure it does not exceed maximum length
	 allowed for a path component on the current platform.
	 @return True if the path component is valid, else false.
	 */
	bool IsValid() const;

	/**
	 Makes an invalid path component valid by replacing invalid characters with the given character.
	 This method will not change the length of the name to conform to platform limits.
	 @param c	IN UTF16 charater used to replace the invalid characters in the path component.
	 @return Reference to the path component.
	 */
	APathComponent& MakeValid(UTF16TextChar c);

	/**
	 Checks the path component to see if it refers to a Windows local drive.
	 A Windows local drive component must contain a base name with single upper or
	 lowercase letter, followed by a colon and an empty extension. This method checks
	 the component to see if it conforms to the above rules. If the component does
	 conform, it is set to be a Windows local drive. Otherwise, the component is set
	 to not be a Windows local drive.\\
	 This method needs to be explicitly called since it is not possible to unambiguosly
	 determine if a component refers to a Windows local drive on all platforms. If the
	 component does refer to a Windows local drive, it requires special validation and
	 handling.\\
	 Note: Changing the components full name, base name or extension causes the component
		   to be reset as not referring to a Windows local drive. Therefore, changing the
		   component to refer to a different drive requires that this method be called again.
	 @return True if the path component refers to a Windows local drive, else false.
	 */
	bool SetIsWinDrive();

	/**
	 Tests whether the path component refers to a Windows local drive.
	 SetIsWinDrive() must be called on the component for this method to ever return true.
	 @return True if the path component refers to a Windows local drive, else false.
	 */
	bool IsWinDrive() const;

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

protected:
	APathComponentImpl* fpImpl;
};

}	// namespace afl
}	// namespace adobe


namespace adobe
{
namespace afl
{
inline void swap(APathComponent &lhs, APathComponent &rhs) noexcept
{
	using std::swap;
	swap(lhs.fpImpl, rhs.fpImpl);
}

inline APathComponent& APathComponent::operator=(APathComponent&& rhs) noexcept
{
	using std::swap;
	swap(*this, rhs);

	return *this;
}
}
}

#endif	// __APathComponent__
