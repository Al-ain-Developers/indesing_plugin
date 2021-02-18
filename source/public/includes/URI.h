//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/URI.h $
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
//  This class provides functionality to construct and parse a well formed Uniform
//  Resource Identifier (URI).
//  
//========================================================================================

#pragma once
#ifndef __URI__
#define __URI__

// ----- Includes -----

class IPMStream;
class URIImpl;
class WideString;

static const WideString kCCLibraryAssetURIScheme("cclibraries");

static const WideString kFileAssetURIScheme("file");
static const WideString kHTTPAssetURIScheme("http");
static const WideString kHTTPSAssetURIScheme("https");

/**
 InDesign class used to construct and parse a well formed Uniform
 Resource Identifier (URI).  The class supports the generic URI syntax
 that consists of a hierarchical sequence of components referred to as
 the scheme, authority, path, query, and fragment.  The scheme and path
 components are required, though the path may be empty (no characters).

 When the authority component is present, the path must either be empty
 or begin with a slash ("/") character.  When authority is not present,
 the path cannot begin with two slash characters ("//").  The current
 implementation does not distinguish an authority based on a registered
 name or server address, the optional port and user information.  It is
 left up to the user to extract the aforementioned sub-components from
 the authority.

 For more information on the syntax of a URI, see:
 \URL{http://www.gbiv.com/protocols/uri/rfc/rfc3986.html}
*/
class PUBLIC_DECL URI
{
public:	
	typedef object_type data_type;

	/**
	 Default constructor.
	 Constructs an empty URI object.
	 */
	URI();

	/**
	 Constructor.
	 Constructs an URI object from the given URI string.
	 @param uri	[IN] URI encoded string.
	 */
	URI(const std::string& uri);

	/**
	 Constructor.
	 Constructs an URI object from the given URI WideString.
	 @param uri	[IN] URI encoded WideString.
	 */
	URI(const WideString& uri);

	/**
	 Copy constructor.
	 Constructs an URI object that is a copy of the given URI.
	 @param name [IN] URI object to copy.
	 */
	URI(const URI& uri);

	/**
	 Destructor.
	 Destroys the URI object.
	 */
	virtual ~URI();

	/**
	 Assignment operator.
	 Assigns the given URI to this URI.
	 @param rhs	[IN] URI to assign to this URI.
	 @return Reference to this URI.
	 */
	URI& operator=(const URI& rhs);

	/**
	 Equality operator.
	 Test whether this URI is equal to the given URI.
	 @param rhs	[IN] URI to test for equality against this URI.
	 @return True if this URI is equal to the given URI, else false.
	 */
	bool operator==(const URI& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this URI is not equal to the given URI.
	 @param rhs	[IN] URI to test for non-equality against this URI.
	 @return True if this URI is not equal to the given URI, else false.
	 */
	bool operator!=(const URI& rhs) const;

	/**
	 Less than operator.
	 Test whether this URI is less than the given URI.
	 @param rhs	[IN] URI to test against this URI.
	 @return True if this URI is less than the given URI, else false.
	 */
	bool operator<(const URI& rhs) const;

	/**
	 Sets the URI from a string.
	 @param uri [IN] URI encoded string.
	 @return True if the string contained a valid URI, else false.
	 */
	bool SetURI(const std::string& uri);

	/**
	 Gets the URI as a string.
	 @return URI as a URI encoded string. \\
			 An empty string if the URI scheme and path are not set.
	 */
	std::string GetURI() const;

	/**
	 Sets the URI from a WideString.
	 @param uri [IN] URI encoded WideString.
	 @return True if the string contained a valid URI, else false.
	 */
	bool SetURIW(const WideString& uri);

	/**
	 Gets the URI as a WideString.
	 @return URI as a URI encoded WideString. \\
			 An empty string if the URI scheme and path are not set.
	 */
	WideString GetURIW() const;

	/**
	 Clears the URI.
	 */
	void ClearURI();

	/**
	 Identifiers that denote a URI component. \\
	 The identifiers are used to get, set and remove components from the URI.
	 */
	enum Component {
		/** URI's scheme component. */
		kScheme = 0,
		/** URI's authority component. */
		kAuthority,
		/** URI's path component. */
		kPath,
		/** URI's query component. */
		kQuery,
		/** URI's fragment component. */
		kFragment
	};

	/**
	 Verifies that the URI conforms to the URI specification.
	 @param badComponent [OUT] Optional argument; if not nil, set to the first
							   non-conforming component found in the URI.
	 @return True if the URI conforms to the URI specification, else false.
	 */
	bool VerifyURI(Component* badComponent = nil) const;

	/**
	 Determines whether the URI contains the specified component.
	 @param component [IN] URI component to check for.
	 @return kTrue if the URI contains the component; else kFalse.
	 */
	bool HasComponent(Component component) const;

	/**
	 Sets the value of the specified URI component.
	 @param component [IN] URI component to set.
	 @param value	  [IN] String containing the value to set specified URI component to. \\
						   The string should not be in URI encoding, nor include the URI
						   delimiter specific to the component.
	 */
	void SetComponent(Component component, const WideString& value);

	/**
	 Returns the value of the specified URI component.
	 @param component [IN] URI component to get.
	 @return URI component's value. \\
			 The returned string is not in URI encoding, and does not
			 include the URI delimiter specific to the component. \\
			 If an empty string is returned, call HasComponent()
			 to determine if the component value is empty or not set.
	 */
	WideString GetComponent(Component component) const;

	/**
	 Removes the specified component from the URI.
	 @param component [IN] URI component to remove.
	 */
	void RemoveComponent(Component component);

	/**
	 Persistence-related method for saving or restoring the
	 state of an URI object instance.
	 @param iPMStream [IN] Stream to read the instance data from
						   or write the instance data to.
	 */
	void ReadWrite(IPMStream* s);

private:
	URIImpl* fpImpl;

#ifdef DEBUG
#include <string>
	/**
	 Debug build only!!!
	 Contains the current URI as a string.
	 */
	std::string fURIStr;
#endif
};

#endif	// __URI__
