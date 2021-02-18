//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LinkResourceQuery.h $
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
//  This class provides functionality to construct a link resource query.
//  
//========================================================================================

#pragma once
#ifndef __LinkResourceQuery__
#define __LinkResourceQuery__

// ----- Includes -----
#include "ILinkResource.h"

class LinkResourceQueryData;


/**
 InDesign class used to construct a link resource query.

 All the methods may be called multiple times to OR the
 values.  Calling different methods will create an AND
 condition between them.

 For example the following code segment: \\
	LinkResourceQuery query; \\
	query.SetScheme(WideString("file")); \\
	query.SetState(ILinkResource::kMissing); \\
	query.SetState(ILinkResource::kUnknown); \\

 Results in the following query: \\
	(Scheme = "file") AND (State = kMissing OR State = kUnknown).

 After the query has been constructed, call ILinkManager::QueryResources()
 to process the query and get the set of ILinkResource UIDs that satisfy the query.
 An empty query will return every ILinkResource UID. 
 @see ILinkManager
*/
class PUBLIC_DECL LinkResourceQuery
{
public:	
	/**
	 Default constructor.
	 Constructs an empty LinkResourceQuery object.
	 */
	LinkResourceQuery();

	/**
	 Copy constructor.
	 Constructs an LinkResourceQuery object that is a copy of the given LinkResourceQuery.
	 @param query [IN] LinkResourceQuery object to copy.
	 */
	LinkResourceQuery(const LinkResourceQuery& query);

	/**
	 Destructor.
	 Destroys the LinkResourceQuery object.
	 */
	virtual ~LinkResourceQuery();

	/**
	 Assignment operator.
	 Assigns the given LinkResourceQuery to this LinkResourceQuery.
	 @param rhs [IN] LinkResourceQuery to assign to this LinkResourceQuery.
	 @return Reference to this LinkResourceQuery.
	 */
	LinkResourceQuery& operator=(const LinkResourceQuery& rhs);

	/**
	 Equality operator.
	 Test whether this LinkResourceQuery is equal to the given LinkResourceQuery.
	 @param rhs	[IN] LinkResourceQuery to test for equality against this LinkResourceQuery.
	 @return True if this LinkResourceQuery is equal to the given LinkResourceQuery, else false.
	 */
	bool operator==(const LinkResourceQuery& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this LinkResourceQuery is not equal to the given LinkResourceQuery.
	 @param rhs	[IN] LinkResourceQuery to test for non-equality against this LinkResourceQuery.
	 @return True if this LinkResourceQuery is not equal to the given LinkResourceQuery, else false.
	 */
	bool operator!=(const LinkResourceQuery& rhs) const;

	/**
	 Sets the URI of a link resource to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param uri [IN] URI of a link resource.
	 */
	void SetURI(const URI& uri);

	/**
	 Sets the scheme of a link resource to query for.
	 Multiple calls results in an OR conditional in the query.
	 @param scheme [IN] Scheme of a link resource.
	 */
	void SetScheme(const WideString& scheme);

	/**
	 Sets the state of a link resource to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param state [IN] State of a link resource.
	 */
	void SetState(ILinkResource::ResourceState state);

	/**
	 Sets the store state of a link resource to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param storeState [IN] Store state of a link resource.
	 */
	void SetStoreState(ILinkResource::ResourceStoreState storeState);

	/**
	 Sets the access mode of a link resource to query for. \\
	 For example, calling SetAccessMode(ILinkResource::kRead) will result
	 in a query that returns the UIDs of all the readable link resources. \\
	 Multiple calls results in an OR conditional in the query. \\
	 Note: Queries on access modes alone cannot be performed in an efficient
		   manner, and therefore should not performed without careful consideration.
	 @param mode [IN] Access mode.
	 */
	void SetAccessMode(ILinkResource::AccessMode mode);

	/**
	 Determines if the query is empty.
	 @return True if the query is empty, else false.
	 */
	bool IsEmpty() const;

	/**
	 Clears the query.
	 */
	void Clear();

private:
	friend class LinkManager;
	friend class ScrapLinkManager;

	LinkResourceQueryData* fData;
};

#endif	// __LinkResourceQuery__
