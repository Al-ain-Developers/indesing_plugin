//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LinkQuery.h $
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
//  This class provides functionality to construct a link query.
//  
//========================================================================================

#pragma once
#ifndef __LinkQuery__
#define __LinkQuery__

// ----- Includes -----
#include "ILink.h"

class LinkQueryData;


/**
 InDesign class used to construct a link query.

 The methods (with exceptions noted) may be called multiple times
 to OR the values.  Calling different methods will create an AND
 condition between them.

 For example the following code segment: \\
	LinkQuery query; \\
	query.SetLinkType(ILink::kImport); \\
	query.SetLinkType(ILink::kBidirectional); \\
	query.SetResourceModState(ILink::kResourceModified); \\

 Results in the following query: \\
	(LinkType = kImport OR LinkType = kBidirectional) AND (ResourceModState = kResourceModified).

 After the query has been constructed, call ILinkManager::QueryLinks()
 to process the query and get the set of ILink UIDs that satisfy the query.
 An empty query will return every ILink UID. 
 @see ILinkManager
*/
class PUBLIC_DECL LinkQuery
{
public:	
	/**
	 Default constructor.
	 Constructs an empty LinkQuery object.
	 */
	LinkQuery();

	/**
	 Copy constructor.
	 Constructs an LinkQuery object that is a copy of the given LinkQuery.
	 @param query [IN] LinkQuery object to copy.
	 */
	LinkQuery(const LinkQuery& query);

	/**
	 Destructor.
	 Destroys the LinkQuery object.
	 */
	virtual ~LinkQuery();

	/**
	 Assignment operator.
	 Assigns the given LinkQuery to this LinkQuery.
	 @param rhs	[IN] LinkQuery to assign to this LinkQuery.
	 @return Reference to this LinkQuery.
	 */
	LinkQuery& operator=(const LinkQuery& rhs);

	/**
	 Equality operator.
	 Test whether this LinkQuery is equal to the given LinkQuery.
	 @param rhs	[IN] LinkQuery to test for equality against this LinkQuery.
	 @return True if this LinkQuery is equal to the given LinkQuery, else false.
	 */
	bool operator==(const LinkQuery& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this LinkQuery is not equal to the given LinkQuery.
	 @param rhs	[IN] LinkQuery to test for non-equality against this LinkQuery.
	 @return True if this LinkQuery is not equal to the given LinkQuery, else false.
	 */
	bool operator!=(const LinkQuery& rhs) const;

	/**
	 Sets the type of link to query for.
	 Multiple calls results in an OR conditional in the query.
	 @param type [IN] Type of a link.
	 */
	void SetLinkType(ILink::LinkType type);

	/**
	 Sets the UID of a child link whose parents to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param parent [IN] UID of a child link.
	 */
	void SetChild(UID child);

	/**
	 Sets the UID of a parent link whose children to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param parent [IN] UID of a parent link.
	 */
	void SetParent(UID parent);

	/**
	 Sets the UID of a link resource in a link to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param resourceUID [IN] UID of a link resource.
	 */
	void SetResource(UID resourceUID);

	/**
	 Sets the modification state of a link resource to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param modState [IN] Modification state of a linked resource.
	 */
	void SetResourceModState(ILink::ResourceModificationState modState);

	/**
	 Sets the UID of a link object in a link to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param objectUID [IN] UID of a link object.
	 */
	void SetObject(UID objectUID);

	/**
	 Sets the modification state of a link object to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param modState [IN] Modification state of a linked object.
	 */
	void SetObjectModState(ILink::ObjectModificationState modState);

	/**
	 Sets the update export policy of a link to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param policy [IN] Link update export policy.
	 */
	void SetExportPolicy(ILink::ExportPolicy policy);

	/**
	 Sets the update import policy of a link to query for. \\
	 Multiple calls results in an OR conditional in the query.
	 @param policy [IN] Link update import policy.
	 */
	void SetImportPolicy(ILink::ImportPolicy policy);

	/**
	 Sets the show link in Link UI flag to query for. \\
	 Only one flag can be specified: kTrue or kFalse.
	 Multiple calls do not result in an OR conditional in the query.
	 @param bShowInUI [IN] Boolean denoting whether the link is displayed in the Links UI.
	 */
	void SetShowInUI(bool16 bShowInUI);

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

	LinkQueryData* fData;
};

#endif	// __LinkQuery__
