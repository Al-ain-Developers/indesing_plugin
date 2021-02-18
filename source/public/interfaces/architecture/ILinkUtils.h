//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkUtils.h $
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
#ifndef __ILinkUtils__
#define __ILinkUtils__

#include "LinksID.h"
#include "ILinkResource.h"
#include "URI.h"

class ILink;
class ICoreFilename;
class IDataLink;
/**
	Utility interface that provides useful functionality for programming against the links architecture.
	@see ILinkCmdSuite
	@see ILinkManager
*/
class ILinkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKUTILS };

	/**
		Copies the set of links found on the source item to the target item. Each boss object behind 
		the source and target UIDs will support the ILinkObject interface. This method will create 
		a link (ILink) connecting the target item (ILinkObject) to an resource (ILinkResource) for each link 
		that exists on the source item. Both the source and target items are assumed to be on the same
		database. No links are deleted (either on source or target) as part of this operation. New links 
		are created, associated with the target item.
		@param iDataBase	 [IN] Document database the items exist in.
		@param sourceItemUID [IN] Source of the copy operation.
		@param targetItemUID [IN] Target of the copy operation.
		@return kSuccess on success, otherwise an error.
	*/
	virtual ErrorCode CopyLinks(IDataBase* iDataBase, UID sourceItemUID, UID targetItemUID) = 0;

	/**
		Replaces the set of links on the target item with those that exist on the source item. This method
		assumes the source and target items support the ILinkObject interface. All links that exist on the 
		target item are deleted prior to the operation. A new link (ILink) is associated with the 
		target (ILinkObject) to every resource (ILinkResource) that is linked to on the source item. No links are
		deleted on the source item as part of this operation. New links are created, associated with the target 
		item. 
		@param iDataBase	 [IN] Document databse the items exist in.
		@param sourceItemUID [IN] Source of the copy operation.
		@param targetItemUID [IN] Target of the copy operation.
		@return kSuccess on success, otherwise an error.
	*/
	virtual ErrorCode ReplaceLinks(IDataBase* iDataBase, UID sourceItemUID, UID targetItemUID) = 0;

	/**
		Copies the specified link to the object specified. A copy of the link
		is made in the target link object database, and this new link is associated with the target link object.
		@param sourceLinkUIDRef	  [IN] Link to be copied.
		@param targetObjectUIDRef [IN] Link object (signature interface ILinkObject) the new link is
									   associated with.
		@param newLink			  [OUT] UID of the newly created link (the copy of the link specified by sourceLinkUIDRef).
		@return kSuccess on success, otherwise and error code.
	*/
	virtual ErrorCode CopyLinkToLinkObject(const UIDRef& sourceLinkUIDRef, const UIDRef& targetObjectUIDRef, UID& newLink) = 0;

	/**
		Get a link related to the source item. Returns the UID of first associated link. Does not search 
		the item's hierarchy, see FindLink() instead.
		@param itemRef [IN] Reference to item we are examining.
		@return UID of the found link, or kInvalidUID.
	*/
	virtual UID GetLink(const UIDRef& itemRef) const = 0;

	/**
		Find any link related to the source item.
		This method searches the item's hierarchy for an association to a link. If none 
		is found, the method determines if there is an association with a text story, and
		the story is tested for an association to a link. If a link association is found, the
		method returns the link.
		@param itemRef [IN] Reference to item we are examining.
		@return UID of the found link, or kInvalidUID.
	*/
	virtual UID FindLink(const UIDRef& itemRef) const = 0;

	/**
		Find any resource that is linked or related to the source item. \\
		This method searches the item's hierarchy for an association to a link resource.
		If none is found, the method determines if there is an association with a text story,
		and the story is tested for an association to a link resource. If a link resource
		association is found, the method returns the UID of link resource.
		@param itemRef [IN] Reference to item we are examining.
		@return UID of the found link resource, or kInvalidUID.
	*/
	virtual UID FindLinkResource(const UIDRef& itemRef) const = 0;

	/**
		Determine if the link information for a page item is missing. The link is missing if there is no
		link (ILink) associated with the link object (ILinkObject). A link is missing if the link resource state 
		associated with the link is set to ILinkResource::kMissing. If the link is embedded, it is not missing.
		@param itemRef [IN] Reference to item we are testing
		@return True if the link is missing, otherwise false
	*/
	virtual bool IsLinkMissing(const UIDRef& itemRef) const = 0;

	/**
		Determine if the link information for a page item is embedded. A link is embedded if the link resource
		store state associated with the link is set to ILinkResource::kEmbedded.
		@param itemRef [IN] Reference to item we are testing
		@return True if the link is embedded, otherwise false
	*/
	virtual bool IsLinkEmbedded(const UIDRef& itemRef) const = 0;

	/**
		If IsLinkMissing returns false and IsLinkEmbedded returns false, determine if the associated 
		ILink's GetResourceModificationState is ILink::kResourceModified or the ILinkResource's state 
		is not ILinkResource::kAvailable.
		@param itemRef [IN] Reference to item we are testing
		@return True if the link is missing or needs updating.
	*/
	virtual bool IsLinkMissingOrOutOfDate(const UIDRef& itemRef) const = 0;

	/**
		Determines if a link resource is associated with any link.
		@param resourceRef [IN] Reference to link resource to check.
		@return True if the link resource is associated with a link, else false
	*/
	virtual bool IsResourceLinked(const UIDRef& resourceRef) const = 0;

	/**
		Get the link's IDFile.
		@param link [IN]  Link we are testing
		@param file [OUT] IDFile if found
		@return True if the link's resource had an IDFile, otherwise false
	*/
	virtual bool GetFileFromLink(ILink *link, IDFile *file) const = 0;

	/**
		Get the link's IDFile for the given page item.
		@param itemRef [IN]  UIDRef of the item we are testing
		@param file	   [OUT] the IDFile if found
		@return True if the link's resource had an IDFile, otherwise false
	*/
	virtual bool GetFileFromLink(const UIDRef& itemRef, IDFile *file) const = 0;

    /** Create a read stream to the linked item's contents.
        @param itemRef [IN] UIDRef of the linked page item.
        @return A pointer to an add-referenced IPMStream to the linked contents.
    */
    virtual IPMStream* CreateReadStreamFromLink(const UIDRef& itemRef) const = 0;

    /** Create a write stream to the linked item's contents.
        @param itemRef [IN] UIDRef of the linked page item.
        @return A pointer to an add-referenced IPMStream to the linked contents.
    */
    virtual IPMStream* CreateWriteStreamFromLink(const UIDRef& itemRef) const = 0;

	/**
		Create a file from the embedded data.
        @param itemRef [IN] UIDRef of the linked page item.
		@param file	   [IN] File to create.
		@return ErrorCode: kSuccess when successful.
	*/
	virtual ErrorCode CreateFileFromEmbedded(const UIDRef& itemRef, IDFile& file) const = 0;

	/**
		Returns a stream that contains the data link's data. 
        @param itemRef [IN] UIDRef of the linked page item.
		@return Nil on failure. 
	*/
	virtual IPMStream* QueryLinkedStream(const UIDRef& itemRef) const = 0;

	/**
		Get the size of a UID.
		@param db  [IN] The document containing the UID.
		@param uid [IN] UID.
		@return Size of the UID.
	*/
	virtual uint64 GetUIDSize(IDataBase *db, UID uid) const = 0;

	/**
	 Converts an IDFile to an ILinkResource::ResourceId.
	 @param file	   [IN]  IDFile to convert.
	 @param resourceId [OUT] Resulting ILinkResource::ResourceId.
	 @return True if the conversion succeeds, else false. 
	 */ 
	virtual bool IDFileToResourceId(const IDFile& file, ILinkResource::ResourceId& resourceId) const = 0;

	/**
	 Converts an ILinkResource::ResourceId to an IDFile.
	 @param resourceId [IN]	 ILinkResource::ResourceId to convert.
	 @param file	   [OUT] Resulting IDFile.
	 @return True if the conversion succeeds, else false. 
	 */ 
	virtual bool ResourceIdToIDFile(const ILinkResource::ResourceId& resourceId, IDFile& file) const = 0;
	
	/**
	 Find any resource that matches the URI and stamp of the given resource.\\
	 Since the resource stamps are compared, it is important that the stamps
	 be up-to-date before calling this method.
	 @param resourceRef [IN] Reference to resource we are matching.
	 @param bEmbedded   [IN] Denotes whether the resource to match must be embedded. \\
							 True if the matching resource must be embedded,
							 false if the matching resource cannot be embedded.
	 @return UID of the matching link resource, or kInvalidUID.
	 */
	virtual UID FindMatchingResource(const UIDRef& resourceRef, bool bEmbedded) const = 0;

	/**
	 Find any resource that matches the given link resource identifier (URI).
	 @param db		   [IN] Database the resource to match.
	 @param clientId   [IN] Link client identifier of the resources to check.
	 @param resourceId [IN] Link resource identifier (URI) to match.
	 @param bEmbedded  [IN] Denotes whether the resource to match must be embedded. \\
							 True if the matching resource must be embedded,
							 false if the matching resource cannot be embedded.
	 @return UID of the matching link resource, or kInvalidUID.
	 */
	virtual UID FindMatchingResource(IDataBase* db, const LinkClientID& clientID, const ILinkResource::ResourceId& resourceId, bool bEmbedded) const = 0;

	/**
	 Determine whether a file's associated editor is available and gather a list of editors for the file.
	 @param linkResource	   [IN]  Link resource we want to edit.
	 @param appList			   [OUT] The editor list, could be empty.
	 @param bDefaultEditorOnly [IN]  If kTrue, return default editor only, kFalse to gether all editors for the file.
	 @return True if an editor is available.
	 */
	virtual bool GetEditorList(const UIDRef& linkResource, AppInfoList& appList, const bool16 bDefaultEditorOnly) = 0;

	/**
	 Performs a form C string normalization (canonical composition) on the given file's path.
	 @param file [IN] File whose path to compose..
	 @return True if the file's path needed normalization; else false.
	 */
	virtual bool ComposePath(IDFile& file) const = 0;

	/**
	 Use this method to identify whether or not a data link is from within a placed InDesign document.  That is,
	 is this link a placed image, for example, on a page within an InDesign document which has been placed within
	 another InDesign document?  If so, then we may not want users to be allowed to perform certain operations
	 on the link.
	 @param iLink [IN] The link in question.
	 @return kTrue if the link comes from within a placed INDD document. 
	 */
	virtual bool32 IsINDDInternalLink(const ILink* iLink) const = 0;

	/**
	 Gets the OPI name of the link resource associated to the source item.\\
	 If there is no OPI name, an empty string is returned.
	 @param itemRef [IN] Reference to item we are examining.
	 @param name	[OUT] OPI name of the link resource.\\
						  On the Mac an OPI file name is an HFS path.\\
						  On Windows, an OPI file name is a local or UNC path.\\
						  If the link resource does not reference a file, the
						  returned OPI name is the resource's long name.
	 @return True if the OPI name was obtained, else false. 
	 */
	virtual bool GetOPIName(const UIDRef& itemRef, PMString& name) const = 0;

	/** Serializes a file's XMP metadata to a string.
		@param theFile [IN] The file to examine.
		@param packet [OUT] A reference to the string to which the metadata is serialized.
		@return kTrue if XMP is found, kFalse otherwise
	*/
	virtual bool16				GetXMPPacket(IDFile& theFile, std::string& packet) = 0;

	/**
	Use this method to get the scheme of the link, i.e whether a placed link is from file system, CC Libraries or any other source.
	@param iLink [IN] The link in question.
	@return WideString the link's scheme. 
	*/
	virtual WideString GetLinkScheme(const ILink* iLink) = 0;

	/**
	Use this method to check whether the underlying link content is locally available or not
	@param iLink [IN] The link in question.
	@return kTrue if the content is available, kFalse otherwise.
	*/
	virtual bool16 IsLinkContentAvailable(const ILink* iLink) = 0;

};

#endif	// __ILinkUtils__
