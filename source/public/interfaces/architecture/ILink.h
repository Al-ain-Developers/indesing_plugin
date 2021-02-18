//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILink.h $
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
//  This class defines an interface used to establish a relationship between an
//  ILinkObject and an ILinkResource.
//  
//========================================================================================

#pragma once
#ifndef __ILink__
#define __ILink__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

class IPMStream;
class IDTime;
class UIDList;


/**
 Interface used to establish a relationship between an ILinkObject and an ILinkResource. \\
 Three types of object and resource relationships are supported: import, export and
 bi-directional (import/export). \\
 An import link updates the object when the resource changes. \\
 An export link updates the resource when the object changes. \\
 A bi-directional link updates the object when the resource changes, and updates the resource
 when the object changes. If both the resource and object change, it is the responsibility of 
 the link object to determine how to handle the confict.  For example, a naive approach may
 be to always update the resource from the object if both the resource and object have changed. \\
 \\
 There are also special links only used to track when a resource's modification state changes.
 These links do not link to an object, only to a resource.  Two types of resource only links
 are supported: child and unplaced.  When a child or unplaced link is updated it only refreshes
 the resource stamp and resource modification date/time stored by the link.
 @see ILinkObject
 @see ILinkResource
 @see IDTime
 @see UID
 */
class ILink : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINK };
	
	/**
	 Identifiers that denote the type of the link.
	 */
	enum LinkType {
		/**
		 Link is an import link. \\
		 An import link updates the object when the resource changes.
		 */
		kImport = 0,
		/**
		 Link is an export link. \\
		 An export link updates the resource when the object changes.
		 */
		kExport,
		/**
		 Link is a bi-directional link. \\
		 A bi-directional link updates the object when the resource changes,
		 and updates the resource when the object changes. If both the resource
		 and object change, conflict resolution rules will need to be applied.
		 */
		kBidirectional,
		/**
		 Link is a child link. \\
		 A child link is never linked to an object, only to a resource that has
		 a parent resource linked to an object.  It is linked to a child resource
		 so it can keep track of when the resource's modification state changes.
		 Updating a child link only refreshes the resource stamp and resource
		 modification date/time stored by the link.
		 */
		kChild
	};

	/**
	 Returns the type of the link.
	 @return Type of the link.
	 */
	virtual LinkType GetLinkType() const = 0;

	/**
	 Returns the link's link client identifier.
	 @return Link's link client identifier.
	 */ 
	virtual LinkClientID GetClientID() const = 0;

	/**
	 Returns the UID of the resource associated with the link.
	 @return UID of the linked resource. \\
			 kInvalidUID if the resource UID has not been set.
	 */
	virtual UID GetResource() const = 0;

	/**
	 Sets the UID of the link resource associated with the link.
	 @param resourceUID [IN] UID of the linked resource.
	 */
	virtual void SetResource(UID resourceUID) = 0;

	/**
	 Identifiers that denote the modification state of the linked resource.
	 The identifiers are used to get and set the modification state of a linked resource.
	 */
	enum ResourceModificationState {
		/** Resource has been modified since the last update. */
		kResourceModified = 0,
		/** Resource has not been modified since the last update. */
		kResourceUnmodified
	};
	
	/**
	 Returns the linked resource's modification state.
	 The resource modification state is always kResourceUnmodified for export links.
	 @return Linked resource's modification state.
	 */ 
	virtual ResourceModificationState GetResourceModificationState() const = 0;

	/**
	 Sets the linked resource's modification state.
	 The resource modification state is ignored for export links.
	 @param modState [IN] Modification state of the linked resource.
	 */ 
	virtual void SetResourceModificationState(ResourceModificationState modState) = 0;

	/**
	 Returns the UID of the link object associated with the link.
	 @return UID of the linked object. \\
			 kInvalidUID if the link object UID has not been set.
	 */
	virtual UID GetObject() const = 0;

	/**
	 Sets the UID of the link object associated with the link.
	 @param objectUID [IN] UID of the linked object.
	 */ 
	virtual void SetObject(UID objectUID) = 0;

	/**
	 Identifiers that denote the modification state of the linked object.
	 The identifiers are used to get and set the modification state of a linked object.
	 */
	enum ObjectModificationState {
		/** Object has been modified since the last update. */
		kObjectModified = 0,
		/** Object has not been modified since the last update. */
		kObjectUnmodified
	};
	
	/**
	 Returns the linked object's modification state. \\
	 The object modification state is always kObjectUnmodified for import links.
	 @return Linked object's modification state.
	 */ 
	virtual ObjectModificationState GetObjectModificationState() const = 0;

	/**
	 Sets the linked object's modification state. \\
	 The object modification state is ignored for import links.
	 @param modState [IN] Modification state of the linked object.
	 */ 
	virtual void SetObjectModificationState(ObjectModificationState modState) = 0;

	/**
	 Returns whether the link should be displayed in the Links UI.
	 @return True if the link should be displayed in the Links UI, else false.
	 */
	virtual bool16 GetShowInUI() const = 0;

	/**
	 Sets whether the link should be displayed in the Links UI.
	 @param bShowInUI [IN] Boolean denoting whether the link should be
						   displayed in the Links UI.
	 */ 
	virtual void SetShowInUI(bool16 bShowInUI) = 0;

	/**
	 Returns whether the link allows the resource to be embedded.
	 @return True if the link allows the resource to be embedded, else false.
	 */
	virtual bool16 GetCanEmbed() const = 0;

	/**
	 Sets whether the link allows the resource to be embedded.
	 @param bCanEmbed [IN] Boolean denoting whether the link's resource
						   can be embedded.
	 */ 
	virtual void SetCanEmbed(bool16 bCanEmbed) = 0;

	/**
	 Returns whether the link allows the resource to be unembedded.
	 @return True if the link allows the resource to be unembedded, else false.
	 */
	virtual bool16 GetCanUnembed() const = 0;

	/**
	 Sets whether the link allows the resource to be unembedded.
	 @param bCanUnembed [IN] Boolean denoting whether the link's resource
							 can be unembedded.
	 */ 
	virtual void SetCanUnembed(bool16 bCanUnembed) = 0;

	/**
	 Returns whether the link allows the resource to be packaged.
	 @return True if the link allows the resource to be packaged, else false.
	 */
	virtual bool16 GetCanPackage() const = 0;

	/**
	 Sets whether the link allows the resource to be packaged.
	 @param bCanPackage [IN] Boolean denoting whether the link's resource
						   can be packaged.
	 */ 
	virtual void SetCanPackage(bool16 bCanPackage) = 0;

	/**
	 Identifiers that denote the policy used to specify when to automatically
	 update the link object via an import when the resource is modified.
	 */
	enum ImportPolicy {
		/** Never automatically update the object. */
		kNoAutoImport = 0,
		/** Update the object via an import when the resource is marked modified. */
		kImportOnModify
	};
	
	/**
	 Returns the policy specifying when to update the link object
	 via an import when the resource is marked modified. \\
	 The import policy is always kNoAutoImport for an export link.
	 @return Link's update export policy.
	 */ 
	virtual ImportPolicy GetImportPolicy() const = 0;

	/**
	 Sets the policy specifying when to update the link object
	 via an import when the resource is marked modified. \\
	 The update import policy is ignored for export links.
	 @param policy [IN] Link's update import policy.
	 */ 
	virtual void SetImportPolicy(ImportPolicy policy) = 0;

	/**
	 Returns the resource's stamp when it was last imported.
	 @return Resource's stamp when it was last imported. \\
			 Undefined if the link type is kExport, or the resource has never been imported.
	 */ 
	virtual WideString GetImportStamp() const = 0;

	/**
	 Returns the resource's modification date/time when it was last imported.
	 @return Resource's modification date/time when it was last imported. \\
			 0 if the link type is kExport, the resource has never been imported.
	 */ 
	virtual IDTime GetImportModTime() const = 0;

	/**
	 Returns the date and time the resource was the last imported into the object.
	 @return Date and time the resource was the last imported into the object. \\
			 0 if the link type is kExport, or the resource has never been imported.
	 */ 
	virtual IDTime GetLastImportTime() const = 0;

	/**
	 Identifiers that denote the policy used to specify when to automatically
	 update the link resource via an export when the object is modified.
	 */
	enum ExportPolicy {
		/** Never automatically export to the resource. */
		kNoAutoExport = 0,
		/** Update the resource via an export when the object is marked modified. */
		kExportOnModify,
		/** Update the resource via an export on close. */
		kExportOnClose,
		/** Update the resource via an export on save. */
		kExportOnSave
	};
	
	/**
	 Returns the policy specifying when to update the link resource
	 via an export when the object is marked modified. \\
	 The export policy is always kNoAutoExport for an import link.
	 @return Link's update export policy.
	 */ 
	virtual ExportPolicy GetExportPolicy() const = 0;

	/**
	 Sets the policy specifying when to update the link resource
	 via an export when the object is marked modified. \\
	 The update export policy is ignored for import links.
	 @param policy [IN] Link's update export policy.
	 */ 
	virtual void SetExportPolicy(ExportPolicy policy) = 0;

	/**
	 Returns the date and time that the object was last exported to the resource.
	 @return Date and time that the object was last exported to the resource. \\
			 0 if the link type is kImport, or the object has never been exported.
	 */ 
	virtual IDTime GetLastExportTime() const = 0;

	/**
	 Adds child links to the link's hierarchy.
	 @param children [IN] UIDs of the child links to add
						  to the link's hierarchy.
	 @return kSuccess if the child links were successfully added,
			 else an error code.
	 */ 
	virtual void AddChildren(const UIDList& children) = 0;

	/**
	 Deletes child links from the link's hierarchy.
	 @param children [IN] UIDs of the child links to deleted
						  from the link's hierarchy.
	 @return kSuccess if the child links were successfully deleted,
			 else an error code.
	 */ 
	virtual void DeleteChildren(const UIDList& children) = 0;

	/**
	 Gets direct descendant child links from the link's hierarchy.
	 @param children [OUT] UIDs of the child links in the link's
						   hierarchy.
	 @return Number of direct descendant child links in
			 the link's hierarchy that were retrieved.
	 */ 
	virtual uint32 GetChildren(UIDList& children) const = 0;

	/**
	 Returns the number of direct descendant child links
	 in the link's hierarchy.
	 @return Number of direct descendant child links in
			 the link's hierarchy.
	 */ 
	virtual uint32 GetNumChildren() const = 0;

	/**
	 Gets links that are direct parents the link.  
	 @return UID of the link's parent link, else kInvalidUID.
	 */ 
	virtual UID GetParent() const = 0;

	/**
	 Updates the link resource or object, as determined by the link's type.
	 @param bForceUpdate [IN] Denotes whether to force an update, or to only update if needed. \\
							  True to force an update, false to only update if needed. 
	 @param uiFlags		 [IN] Denotes whether to allow UI during the update operation.
	 @param linkUID		 [OUT] UID of the link as a result of the update, which may or
							   may not be the same as the UID of the link before the update
							   operation.  
	 @return kSuccess if the update succeeds, else an error code.
	 */ 
	virtual ErrorCode Update(bool bForceUpdate, UIFlags uiFlags, UID& linkUID) = 0;

	/**
	 Copies the attributes of the link referenced by the given UIDRef to this link.
	 @param linkRef [IN] UIDRef of the link to copy. \\
						 The UIDRef may reference a link in a different database.
	 @return kSuccess if the link attributes were successfuly copied, else an error code.
	 */
	virtual ErrorCode CopyAttributes(const UIDRef& linkRef) = 0;

private:
	friend class LinkManager;
	friend class ScrapLinkManager;

	/**
	 Initializes the link. \\
	 This method is called by the LinkManager immediately after a link
	 object is created; subsequent calls to Init are not allowed and
	 will fail.
	 @param clientId    [IN] Link client identifier of the link.
	 @param resourceUID	[IN] UID of the link resource to link.
	 @param objectUID	[IN] UID of the link object to link.
	 @return True if the link is successfully initialized, else false.
	 */ 
	virtual bool Init(LinkClientID clientId, UID resourceUID, UID objectUID) = 0;

	friend class LinkScriptProvider;
	virtual void InitFromINX(IDataBase* db,
							 LinkType type,
							 LinkClientID clientId,
							 const WideString& importStamp,
							 const IDTime& importModTime,
							 const IDTime& lastImportTime,
							 const IDTime& lastExportTime,
							 bool16 isSharedContentLink = kFalse) = 0;

	virtual ErrorCode CopyAttributes(const ILink* pLink) = 0;
};

#endif // __ILink__
