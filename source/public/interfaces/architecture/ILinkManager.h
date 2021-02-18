//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkManager.h $
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
//  This class defines an interface used to manage linked resources and links.
//  
//========================================================================================

#pragma once
#ifndef __ILinkManager__
#define __ILinkManager__

// ----- Includes -----
#include "IPMUnknown.h"

#include "ILink.h"
#include "ILinkResource.h"
#include "LinksID.h"
#include <vector>

class ILinkObject;

class LinkResourceQuery;
class LinkQuery;
class URI;
class WideString;


/**
 ILinkManager is used to own and manage all ILink and ILinkResource objects in a document.
 In addition the manager maintains Meta information on every link and resource that can be
 easily and quickly queried using a LinkQuery or LinkResourceQuery.
 
 There should be one, and only one, ILinkManager per InDesign database.  However, different
 flavors of links can be differentiated by the LinkClientID.  For example, InDesign placed
 links all have a client identifier of kIDLinkClientID, and hyperlinks have a client id of
 kHyperlinkLinkClientID.  Both flavors of links are managed by the same manager, but the
 manager prevents links and resources with different client ids from interacting with each
 other.  Therefore, a link with a client id of kIDLinkClientID cannot link a resource with
 a client id of kHyperlinkLinkClientID.  The client ids can also be utilized to control
 where and how the links and resources are displayed to the user.  For example, the Links
 Panel only shows links and resources with a client id of kIDLinkClientID; hyperlinks have
 their own UI.

 Most operations provided by the manager, with the exception of queries, should be initiated
 from the ILinkFacade.

 @see ILink
 @see ILinkFacade
 @see ILinkObject
 @see ILinkResource
 @see LinkResourceQuery
 @see LinkQuery
 @see UID
 @see URI
*/
class ILinkManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKMANAGER };

	/**
	 Class used hold link and link resource UIDs that are contained in the
	 ListLazyNotificationData sent with IID_ILINKDATA_CHANGED notifications.
	 */
	class ChangeData
	{
	public:
		typedef object_type data_type;

		/**
		 Identifiers that denote what kind of UID is referenced.
		 */
		enum Type {
			/** UID references a link. */
			kLink = 0,
			/** UID references a link resource. */
			kResource,
			/** UID references a link whose link resource UID changed. */
			kLinksResource
		};

		ChangeData(Type type, UID uid) : fType(type), fUID(uid) {}
		ChangeData(const ChangeData& data) : fType(data.fType), fUID(data.fUID) {}
		~ChangeData() {}

		ChangeData& operator=(const ChangeData& rhs)
		{
			ChangeData temp(rhs);
			std::swap(temp.fType, fType);
			std::swap(temp.fUID, fUID);
			return *this;
		}

		bool operator==(const ChangeData& rhs) const { return (fType == rhs.fType && fUID == rhs.fUID); }
		bool operator<(const ChangeData& rhs) const
		{
			if (fType < rhs.fType) return true;
			else if (fType == rhs.fType) return (fUID < rhs.fUID);
			else return false;
		}

		Type GetType() { return fType; }
		UID GetUID() { return fUID; }

		static ChangeData Make(Type type, UID uid) { return ChangeData(type, uid); }

	private:
		Type	fType;
		UID		fUID;
	};

	/**
	 A QueryResult is used to contain the results of a LinkQuery and LinkResourceQuery.
	 */
	typedef std::vector<UID> QueryResult;

	/**
	 Identifiers that denote how an resource state update or auto resolve operation
	 should be performed.
	 */
	enum OperationType {
		/** Perform the operation asynchronously. */
		kAsynchronous = 0,
		/** Perform the operation synchronously. */
		kSynchronous
	};
	
	/**
	 Returns whether any links or link resources are in the process of being added,
	 deleted or changed.
	 @return True if the link or resources are currently being added, deleted or changed;
			 else false.
	 */
	virtual bool IsModelChanging() const = 0;

	/**@name LinkResource methods */
	//@{
	/**
	 Creates a new link resource from a URI.
	 @param uri			 [IN] URI of the link resource to create.
	 @param clientId	 [IN] Link client identifier of the resource to create.
	 @param bUseExisting [IN] Denotes whether to return the UID of an existing
							  link resource if one already exists with the given URI.
							  Pass true to return the UID of an existing link resource
							  if possible, false to always create a new link resource.
	 @return UID of the created or existing link resource. \\
			 kInvalidUID if the create fails.
	 */
	virtual UID CreateResource(const URI& uri, LinkClientID clientId, bool bUseExisting) = 0;

	/**
	 Reinitializes a link resource with a the given URI while preserving the link resource's
	 current UID.  The state of the link resource is the same as if it were newly created.
	 @param resourceUID						[IN] UID of the link resource to reintialize.
	 @param uri								[IN] URI of the link resource.
	 @param updateResourceStateSync			[IN] whether the linkResource state should be updated synchronously
	 @return kSuccess if the link resource is successfully reintialized with the given URI,
			 else an error code.
	 */
	virtual ErrorCode ReinitResource(UID resourceUID, const URI& uri, bool updateResourceStateSync = true) = 0;

	/**
	 Deletes a link resource. \\
	 An resource that is currently referenced by a link cannot be deleted. \\
	 The resource's child resources (and associated child links) are also deleted as
	 long as no other resources or links reference them. 
	 @param resourceUID [IN] UID of the link resource to delete.
	 @return kSuccess if the link resource is deleted, else an error code.
	 */
	virtual ErrorCode DeleteResource(UID resourceUID) = 0;

	/**
	 Returns the link resource with the given UID.
	 @param resourceUID [IN] UID of the link resource to retrieve.
	 @return Link resource with the given UID. \\
			 Nil if the no link resource is found.
	 */
	virtual ILinkResource* QueryResourceByUID(UID resourceUID) const = 0;

	/**
	 Updates the state of a link resource.
	 @param resourceUID	 [IN] UID of the link resource to update.
	 @param opType		 [IN] Denotes whether to perform the state update
							  operation asynchronously or synchronously.
	 @return kSuccess if the link resource's state is successfully updated, else an error code. \\
			 When performing the operation asynchronously, the returned error code
			 denotes whether the state update request was successfully queued.
	 */
	virtual ErrorCode UpdateResourceState(UID resourceUID, OperationType opType) = 0;

	/**
	 Cancels an asynchronous link resource state update request.
	 @param resourceUID [IN] UID of the link resource to cancel the asynchronous request for.
	 */
	virtual void CancelUpdateResourceState(UID resourceUID) = 0;

	/**
	 Wait for the asynchronous link resource state update request to get completed.
	 @param resourceUID [IN] UID of the link resource whose asynchronous request needs to be completed.
	 */
	virtual void WaitForUpdateResourceStateCompletion(UID resourceUID) = 0;


	/**
	 Attempts to automatically (find without user interaction) the location of a link resource.
	 @param resourceUID	 [IN] UID of the link resource to resolve.
	 @param relativeURI	 [IN] Relative location of where to start the search. \\
							  For example, this is often the location of the document,
							  and depending upon the protocal of the link may not be utilized.
	 @param bIgnoreStamp [IN] Denotes whether to ignore the resource's stamp when looking
							  for potential matches.
	 @return kSuccess if the link resource is successfully resolved, else an error code.
	 */
	virtual ErrorCode ResolveResource(UID resourceUID, const URI& relativeURI, bool bIgnoreStamp) = 0;

	/**
	 Returns the UIDs of the link resources that match the given query.
	 @param query	 [IN] Query to perform on the link resources.
	 @param clientId [IN] Link client identifier of the resources to query.
	 @param result	 [OUT] UIDs of the link resources that match the query.
	 @return Number link resources that matched the query.
	 */
	virtual uint32 QueryResources(const LinkResourceQuery& query, LinkClientID clientId, QueryResult& result) const = 0;
	uint32 QueryResources(const LinkResourceQuery& query, QueryResult& result) const
		{ return QueryResources(query, kIDLinkClientID, result); }

	virtual uint32 QueryResources(const LinkResourceQuery& query, LinkClientID clientId, UIDList& result) const = 0;
	uint32 QueryResources(const LinkResourceQuery& query, UIDList& result) const
		{ return QueryResources(query, kIDLinkClientID, result); }

	/**
	 Returns the class id of the link resource provider associated with the given scheme.
	 @param scheme [IN] Scheme to get the link resource provider for.
	 @return Id of the link resource provider associated with the given scheme.
			 kInvalidClass if no provider is associated with the scheme.
	 */
	virtual ClassID GetResourceProviderByScheme(const WideString& scheme) const = 0;
	//@}


	/**@name Link methods */
	//@{
	/**
	 Creates a new link of the given type.
	 @param type		[IN] Type of link to create.
	 @param clientId	[IN] Link client identifier of the link to create.
							 The id must match the client id of the resource.
	 @param resourceUID	[IN] UID of the link resource to link.
	 @param objectUID	[IN] UID of the link object to link.
	 @return UID of the created link. \\
			 kInvalidUID if the create fails.
	 */
	virtual UID CreateLink(ILink::LinkType type, LinkClientID clientId, UID resourceUID, UID objectUID) = 0;

	/**
	 Creates a new link of the given class.
	 @param classID		[IN] Class identifier of link to create.
	 @param clientId	[IN] Link client identifier of the link to create.
							 The id must match the client id of the resource.
	 @param resourceUID	[IN] UID of the link resource to link.
	 @param objectUID	[IN] UID of the link object to link.
	 @return UID of the created link. \\
			 kInvalidUID if the create fails.
	 */
	virtual UID CreateLink(ClassID classID, LinkClientID clientId, UID resourceUID, UID objectUID) = 0;

	/**
	 Deletes a link.
	 @param linkUID			[IN] UID of the link to delete.
	 @param bDeleteResource	[IN] Denotes whether to delete the link resource held by the link if it is
								 not referenced by any other link.
	 @return kSuccess if the link is deleted, else an error code.
	 */
	virtual ErrorCode DeleteLink(UID linkUID, bool bDeleteResource) = 0;

	/**
	 Returns the link with the given UID.
	 @param linkUID	[IN] UID of the link to retrieve.
	 @return Link with the given UID. \\
			 Nil if the no link is found.
	 */
	virtual ILink* QueryLinkByUID(UID linkUID) const = 0;

	/**
	 Returns the UIDs of the links that match the given query.
	 @param query	 [IN] Query to perform on the links.
	 @param clientId [IN] Link client identifier of the links to query.
	 @param result	 [OUT] UIDs of the links that match the query.
	 @return Number of links that matched the query.
	 */
	virtual uint32 QueryLinks(const LinkQuery& query, LinkClientID clientId, QueryResult& result) const = 0;
	uint32 QueryLinks(const LinkQuery& query, QueryResult& result) const
		{ return QueryLinks(query, kIDLinkClientID, result); }

	virtual uint32 QueryLinks(const LinkQuery& query, LinkClientID clientId, UIDList& result) const = 0;
	uint32 QueryLinks(const LinkQuery& query, UIDList& result) const
		{ return QueryLinks(query, kIDLinkClientID, result); }

	/**
	 Returns the UIDs of the links that link the given resource.
	 @param resourceUID	  [IN] UID of the link resource.
	 @param bChildLinksOK [IN] Denotes whether to include child links in the results.
	 @param result		  [OUT] UIDs of the links that link the given resource.
	 @return Number links that link the given resource.
	 */
	virtual uint32 QueryLinksByResourceUID(UID resourceUID, bool bChildLinksOK, QueryResult& result) const = 0;
	virtual uint32 QueryLinksByResourceUID(UID resourceUID, bool bChildLinksOK, UIDList& result) const = 0;

	/**
	 Returns the UIDs of the links that link the given object.
	 @param objectUID [IN] UID of the link object.
	 @param result	  [OUT] UIDs of the links that link the given object.
	 @return Number links that link the given object.
	 */
	virtual uint32 QueryLinksByObjectUID(UID objectUID, QueryResult& result) const = 0;
	virtual uint32 QueryLinksByObjectUID(UID objectUID, UIDList& result) const = 0;
	//@}


	/**@name LinkObject methods */
	//@{
	/**
	 Returns the link object with the given UID.
	 @param objectUID [IN] UID of the link object to retrieve.
	 @return Link object with the given UID. \\
			 Nil if the no link object is found.
	 */
	virtual ILinkObject* QueryObjectByUID(UID objectUID) const = 0;
	//@}
};

#endif // __ILinkManager__
