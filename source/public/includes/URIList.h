//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/URIList.h $
//  
//  Owner: Adrian O'Lenskie
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
#ifndef __URIList_h__
#define __URIList_h__

#include "URI.h"
#include <vector>

/**
 Class used to hold a list of URI objects.
 @see URI
 */
class PUBLIC_DECL URIList
{
public:
	/**
	 Default constructor.
	 Constructs a URIList object.
	 */
	URIList();

	/**
	 Destructor.
	 Destroys the URIList object.
	 */
	~URIList();

	/**
	 Returns the number of URIs in the list.
	 @return Number of URIs in the list.
	 */
	virtual int32 GetURICount() const;

	/**
	 Returns the n'th URI in the list.
	 @param n	IN Index of the URI to return from the list.
	 @return Pointer to the n'th URI in the list.
	 */
	virtual const URI& GetNthURI(int32 n) const;

	/**
	 Adds a URI to the list.
	 @param newURI	IN URI to add to the list.
	 */
	virtual void AddURI(const URI& newURI);
	
	/**
	 Sorts the list by scheme then path.
	 */
	virtual void Sort();
	
private:
	URIList(const URIList& rhs);				// disable copying
	URIList& operator=(const URIList& rhs);
	
	std::vector<URI> fURIList;
};

#endif // __URIList_h__
