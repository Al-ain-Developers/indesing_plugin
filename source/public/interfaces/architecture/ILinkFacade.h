//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkFacade.h $
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
//  A high level API for dealing with links, link resources and link objects.
//  
//========================================================================================

#pragma once
#ifndef __ILinkFacade__
#define __ILinkFacade__

// ----- Includes -----
#include "IPMUnknown.h"

#include "ILink.h"
#include "ILinkManager.h"
#include "ILinkResourceRenditionData.h"

#include "LinksID.h"
#include "Utils.h"

class URI;


/**
 Interface used to manage linked resources and links.  When possible,
 interaction with a linked resource or link should be performed via the
 methods in this interface rather than directly with ILinkResource or
 ILink.
 @see ILink
 @see ILinkResource
 @see ILinkObject
 @see UID
 @see UIDRef
 @see URI
*/
namespace Facade
{
	class ILinkFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ILINKFACADE };

		/**@name LinkResource command methods */
		//@{
		/**
		 Creates a new link resource from a URI.
		 @param db			 [IN]  Database to create the link resource in.
		 @param uri			 [IN]  URI of the link resource to create.
		 @param clientId	 [IN]  Link client identifier of the resource to create.
		 @param formatType	 [IN]  Resource's import/export format type.
		 @param resourceUID	 [OUT] UID of the created link resource.
								   kInvalidUID if the create fails.
		 @return kSuccess if the link resource is successfully created, else an error code.
		 */
		virtual ErrorCode CreateResource(IDataBase* db, const URI& uri, LinkClientID clientId, const PMString& formatType, UID& resourceUID) const = 0;

		/**
		 Deletes link resources. \\
		 A resource that is currently referenced by a link cannot be deleted. \\
		 The resource's child resources (and associated child links) are also deleted as
		 long as no other resources or links reference them. 
		 @param resources [IN] List of link resources to delete.
		 @return kSuccess if the link resources are deleted, else an error code.
		 */
		virtual ErrorCode DeleteResources(const UIDList& resources) const = 0;

		/**
		 Reinitializes a link resource with a the given URI while preserving the link resource's
		 current UID.  The state of the link resource is the same as if it were newly created.
		 @param resourceRef	[IN] UIDRef of the link resource to reintialize.
		 @param uri			[IN] URI of the link resource.
		 @return kSuccess if the link resource is successfully reintialized with the given URI,
				 else an error code.
		 */
		virtual ErrorCode ReinitResource(const UIDRef& resourceRef, const URI& uri) const = 0;

		/**
		 Determines if a resource can be relinked. 
		 @param resourceRef [IN] UIDRef of the link resource to check.
		 @return True if the resource can be relinked, else false.
		 */
		virtual bool CanRelinkResource(const UIDRef& resourceRef) const = 0;

		/**
		 Relinks a link resource to the item specified by the given URI, and updates all the
		 links that reference the resource.
		 @param resourceRef	[IN] UIDRef of the link resource to relink.
		 @param uri			[IN] URI of the item to relink to.
		 @param uiFlags		[IN] Denotes whether to allow UI during the relink operation.
		 @return kSuccess if the link resource is relinked, else an error code.
		 */
		virtual ErrorCode RelinkResource(const UIDRef& resourceRef, const URI& uri, UIFlags uiFlags) const = 0;

		/**
		 Updates the state of link resources.
		 @param resources [IN] List of link resources to update.
		 @param opType	  [IN] Denotes whether to perform the state update
							   operations asynchronously or synchronously.
		 @return kSuccess if the link resources' states are successfully updated, else an error code. \\
				 When performing the operation asynchronously, the returned error code
				 denotes whether the state update requests were successfully queued.
		 */
		virtual ErrorCode UpdateResourceStates(const UIDList& resources, ILinkManager::OperationType opType) const = 0;

		/**
		 Attempts to automatically (find without user interaction) the location of a link resource.
		 @param resources	 [IN] List of link resources to update.
		 @param relativeURI	 [IN] Relative location of where to start the search. \\
								  For example, this is often the location of the document,
								  and depending upon the protocal of the link may not be utilized.
		 @param bIgnoreStamp [IN] Denotes whether to ignore the resource's stamp when looking
								  for potential matches.
		 @return kSuccess if the link resources are successfully resolved, else an error code.
		 */
		virtual ErrorCode ResolveResources(const UIDList& resources, const URI& relativeURI, bool bIgnoreStamp) const = 0;

		/**
		 Attempts to automatically find (without user interaction) the location of missing link resources,
		 and optionally update out-of-date links that reference the found resources.
		 @param db			 [IN] Database whose missing link resources to find.
		 @param clientId	 [IN] Link client identifier of the missing resources to find.
		 @param relativeURI	 [IN] Relative location of where to start the search. \\
								  For example, this is often the location of the document,
								  and depending upon the protocal of the link may not be utilized.
		 @param bIgnoreStamp [IN] Denotes whether to ignore the missing resources' stamps when looking
								  for potential matches.  If true, matches are based on the name of the
								  resource only, else matches are based on the resources name and stamp.
		 @param bUpdate		 [IN] Denotes whether to update out-of-date links that reference the missing
								  resources that were found.
		 @param uiFlags		 [IN] Denotes whether to allow UI during the operation.
		 @param nFixed		 [OUT] Number of missing resources found.
		 @return kSuccess if one or more link resources are successfully found, else an error code.
		 */
		virtual ErrorCode FindMissingResources(IDataBase* db,
											   LinkClientID clientId,
											   const URI& relativeURI,
											   bool bIgnoreStamp,
											   bool bUpdateLinks,
											   UIFlags uiFlags,
											   uint32& nFixed) const = 0;

		/**
		 Returns a link resource's long name.\\
		 For a file link, the long name is the resource's file path.
		 @param resourceRef	[IN] UIDRef of the link resource.
		 @return Link resource's long name.
		 */ 
		virtual WideString GetResourceLongName(const UIDRef& resourceRef) const = 0;

		/**
		 Returns a link resource's import/export format type.
		 @param resourceRef	[IN] UIDRef of the link resource.
		 @return Link resource's import/export format type.
		 */ 
		virtual PMString GetResourceFormatType(const UIDRef& resourceRef) const = 0;

		/**
		 Returns a link resource's data size in bytes.
		 @param resourceRef	[IN] UIDRef of the link resource.
		 @return Link resource's data size in bytes.
		 */ 
		virtual uint64 GetResourceSize(const UIDRef& resourceRef) const = 0;
		
		/**
		 Returns the links linked to a link resource.
		 @param resourceRef	  [IN] UIDRef of the link resource.
		 @param bChildLinksOK [IN] Denotes whether to include child links in the result.
		 @param links		  [OUT] List of links linked to the resource.
		 @return Number of links linked to the resource.
		 */ 
		virtual uint32 GetResourceLinks(const UIDRef& resourceRef, bool bChildLinksOK, UIDList& links) const = 0;
		//@}


		/**@name Link command methods */
		//@{
		/**
		 Creates a new link of the given type.
		 @param type			 [IN]  Type of link to create.
		 @param clientId		 [IN]  Link client identifier of the link to create.
		 @param objectRef		 [IN]  UIDRef of the link object to link.
		 @param resourceRef		 [IN]  UIDRef of the link resource to link.
									   The resource must have the same LinkClientID as the link.
		 @param bSetLinkModified [IN]  Denotes whether to set the created link as modified or not.
									   If the link is to be updated after creation, pass true; else
									   set to false.
		 @param linkUID			 [OUT] UID of the created link.
									   kInvalidUID if the create fails.
		 @return kSuccess if the link is successfully created, else an error code.
		 */
		virtual ErrorCode CreateLink(IDataBase* db,
									 ILink::LinkType type,
									 LinkClientID clientId,
									 UID objectUID,
									 UID resourceUID,
									 bool bSetLinkModified,
									 UID& linkUID) const = 0;

		/**
		 Creates a new link of the given type.
		 @param type				 [IN]  Type of link to create.
		 @param clientId			 [IN]  Link client identifier of the link to create.
		 @param objectRef			 [IN]  UIDRef of the link object to link.
		 @param resourceURI			 [IN]  URI of the link resource to link.
		 @param bSetLinkModified	 [IN]  Denotes whether to mark the created link as modified or not.
										   If the link is to be updated after creation, pass true; else
										   set to false.
		 @param linkUID				 [OUT] UID of the created link.
										   kInvalidUID if the create fails.
		 @return kSuccess if the link is successfully created, else an error code.
		 */
		virtual ErrorCode CreateLink(IDataBase* db,
									 ILink::LinkType type,
									 LinkClientID clientId,
									 UID objectUID,
									 const URI& resourceURI,
									 bool bSetLinkModified,
									 UID& linkUID) const = 0;

		/**
		 Creates a new link of the given class.
		 @param classID			 [IN]  Class identifier of link to create.
		 @param clientId		 [IN]  Link client identifier of the link to create.
		 @param objectRef		 [IN]  UIDRef of the link object to link.
		 @param resourceRef		 [IN]  UIDRef of the link resource to link.
									   The resource must have the same LinkClientID as the link.
		 @param bSetLinkModified [IN]  Denotes whether to set the created link as modified or not.
									   If the link is to be updated after creation, pass true; else
									   set to false.
		 @param linkUID			 [OUT] UID of the created link.
									   kInvalidUID if the create fails.
		 @return kSuccess if the link is successfully created, else an error code.
		 */
		virtual ErrorCode CreateLink(IDataBase* db,
									 ClassID classID,
									 LinkClientID clientId,
									 UID objectUID,
									 UID resourceUID,
									 bool bSetLinkModified,
									 UID& linkUID) const = 0;

		/**
		 Creates a new link of the given class.
		 @param classID				 [IN]  Class identifier of link to create.
		 @param clientId			 [IN]  Link client identifier of the link to create.
		 @param objectRef			 [IN]  UIDRef of the link object to link.
		 @param resourceURI			 [IN]  URI of the link resource to link.
		 @param bSetLinkModified	 [IN]  Denotes whether to mark the created link as modified or not.
										   If the link is to be updated after creation, pass true; else
										   set to false.
		 @param linkUID				 [OUT] UID of the created link.
										   kInvalidUID if the create fails.
		 @return kSuccess if the link is successfully created, else an error code.
		 */
		virtual ErrorCode CreateLink(IDataBase* db,
									 ClassID classID,
									 LinkClientID clientId,
									 UID objectUID,
									 const URI& resourceURI,
									 bool bSetLinkModified,
									 UID& linkUID) const = 0;

		/**
		 Deletes links.
		 @param links			[IN] List of links to delete.
		 @param bDeleteResource [IN] Denotes whether to delete the link resource held by a link if it is
									 not referenced by any other link.
		 @param bDeleteChildren	[IN] Denotes whether to delete child links of the link being deleted.
		 @return kSuccess if the links are deleted, else an error code.
		 */
		virtual ErrorCode DeleteLinks(const UIDList& links, bool bDeleteResource, bool bDeleteChildren) const = 0;

		/**
		 Deletes links that are associated with the given link object UIDs.
		 @param objects			[IN] List of link objects whose associated links to delete.
		 @param bDeleteResource [IN] Denotes whether to delete the link resource held by a link if it is
									 not referenced by any other link.
		 @param bDeleteChildren	[IN] Denotes whether to delete child links of the link being deleted.
		 @return kSuccess if the links are deleted, else an error code.
		 */
		virtual ErrorCode DeleteLinksByObject(const UIDList& objects, bool bDeleteResource, bool bDeleteChildren) const = 0;

		/**
		 Attaches an existing link to an object. The previous object linked is forgotten but unaffected.
		 @param objectRef [IN] UIDRef of the object to attach the link to.
		 @param linkUID	  [IN] UID of the link.
		 @return kSuccess if the link is successfully attached, else an error code.
		 */
		virtual ErrorCode AttachLink(const UIDRef& objectRef, UID linkUID) const = 0;

		/**
		 Determines if a link's resource can be embedded. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be embedded, else false.
		 */
		virtual bool CanEmbedLink(const UIDRef& linkRef) const = 0;

		/**
		 Embeds link resources.\\
		 Note: Embedding a link will never result in a new UID for the link. 
		 @param links [IN] List of links whose resources to embed.
		 @return kSuccess if the link resources are embedded, else an error code.
		 */
		virtual ErrorCode EmbedLinks(const UIDList& links) const = 0;

		/**
		 Determines if a link's resource can be unembedded. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be unembedded, else false.
		 */
		virtual bool CanUnembedLink(const UIDRef& linkRef) const = 0;

		/**
		 Unembeds link resources to the location they were embedded from.\\
		 Note: Unembedding a link will never result in a new UID for the link. 
		 @param links	[IN] List of links whose resources to unembed.
		 @param uiFlags	[IN] Denotes whether to allow UI during the unembed operation.
		 @return kSuccess if the link resources are unembedded, else an error code.
		 */
		virtual ErrorCode UnembedLinks(const UIDList& links, UIFlags uiFlags) const = 0;

		/**
		 Unembeds link resources to the location specified by the given URI.\\
		 Note: Unembedding a link will never result in a new UID for the link. 
		 @param links	[IN] List of links whose resources to unembed.
		 @param uri		[IN] URI of the location where to unembed the link resources. \\
							 For example, if the URI is a file URI, it specifies the target
							 folder of the unembedded link resource files.
		 @param uiFlags	[IN] Denotes whether to allow UI during the unembed operation.
		 @return kSuccess if the link resources are unembedded, else an error code.
		 */
		virtual ErrorCode UnembedLinks(const UIDList& links, const URI& uri, UIFlags uiFlags) const = 0;

		/**
		 Determines if a link can be updated. 
		 @param linkRef		 [IN] UIDRef of the link to check.
		 @param bForceUpdate [IN] Denotes whether the update will be forced. \\
								  True if the update will be forced, else false. 
		 @return True if the link can be updated, else false.
		 */
		virtual bool CanUpdateLink(const UIDRef& linkRef, bool bForceUpdate) const = 0;

		/**
		 Update a link.
		 @param linkRef		 [IN] UIDRef of the link to update.
		 @param bForceUpdate [IN] Denotes whether to force an update, or to only update if needed. \\
								  True to force an update, false to only update if needed. 
		 @param uiFlags		 [IN] Denotes whether to allow UI during the update operation.
		 @param newLinkUID	 [OUT] UID of the link as a result of the update, which may or
								   may not be the same as the UID of the link before the update
								   operation.
		 @return kSuccess if the link is updated, else an error code.
		 */
		virtual ErrorCode UpdateLink(const UIDRef& linkRef, bool bForceUpdate, UIFlags uiFlags, UID& newLinkUID) const = 0;

		/**
		 Updates links.
		 @param links		 [IN] List of links to update.
		 @param bForceUpdate [IN] Denotes whether to force an update, or to only update if needed. \\
								  True to force an update, false to only update if needed. 
		 @param uiFlags		 [IN] Denotes whether to allow UI during the update operation.
		 @param bScheduleCmd [IN] Denotes whether to schedule or process the update links request. \\
								  True to schedule the update for later, false to process the update now. 
		 @param pNewLinks	 [OUT] List of the resulting links of the update operation.
								   To ignore the optional parameter pass nil, the default.
								   This parameter is also ignored if the update links request is scheduled.\\
								   The nth link in the newLinks UIDList corresponds the nth
								   link in the given links UIDList, and may or may not be the
								   same as the given UID. kInvalidUID is returned for links that have
								   been deleted as a result of the update.
		 @return kSuccess if the links are updated or scheduled for update, else an error code.
		 */
		virtual ErrorCode UpdateLinks(const UIDList& links,
									  bool bForceUpdate,
									  UIFlags uiFlags,
									  bool bScheduleCmd,
									  UIDList* pNewLinks = nil) const = 0;

		/**
		 Updates links Recursively.
		 @param links		 [IN] List of links to update.
		 @param bForceUpdate [IN] Denotes whether to force an update, or to only update if needed. \\
								  True to force an update, false to only update if needed. 
		 @param uiFlags		 [IN] Denotes whether to allow UI during the update operation.
		 @param bScheduleCmd [IN] Denotes whether to schedule or process the update links request. \\
								  True to schedule the update for later, false to process the update now. 
		 @return kSuccess if the links are updated, else an error code.
		 */
		virtual ErrorCode UpdateLinksRecursively(const UIDList& links,
											     bool bForceUpdate,
											     UIFlags uiFlags,
												 bool bScheduleCmd) const = 0;

		/**
		 Determines if a link can be relinked. 
		 @param linkRef [IN] UIDRef of the link to check.
		 @return True if the link can be relinked, else false.
		 */
		virtual bool CanRelinkLink(const UIDRef& linkRef) const = 0;

		/**
		 Relinks a link to the item specified by the given URI.
		 @param linkRef	   [IN] UIDRef of the link to relink.
		 @param uri		   [IN] URI of the item to relink to.
		 @param uiFlags	   [IN] Denotes whether to allow UI during the relink operation.
		 @param newLinkUID [OUT] UID of the link as a result of the relink, which may or
								 may not be the same as the UID of the link before the relink
								 operation.
		 @return kSuccess if the link is relinked, else an error code.
		 */
		virtual ErrorCode RelinkLink(const UIDRef& linkRef, const URI& uri, UIFlags uiFlags, UID& newLinkUID) const = 0;

		/**
		 Relinks links' resources to a file with a matching name in the specified folder.
		 @param links		 [IN] List of links whose resources to relink.
		 @param folder		 [IN] Folder to relink the resources to.
		 @param extension	 [IN] If not blank, the resources are relinked to a matching
								  file with the given extension.
		 @param uiFlags		 [IN] Denotes whether to allow UI during the relink operation.
		 @param skippedLinks [IN] List of the link UIDs that could not be relinked because
								  no matching file existed.
		 @return kSuccess if one or more of the links are relinked, else an error code.
		 */
		virtual ErrorCode RelinkLinksToFolder(const UIDList& links, const IDFile& folder, const WideString& extension, UIFlags uiFlags, UIDList& skippedLinks) const = 0;

		/**
		 Relinks links' resources to a file with a matching base name and the specified extension
		 in the same folder as the original file.
		 @param links		 [IN] List of links whose resources to relink.
		 @param extension	 [IN] New extension of the files to be relinked.
		 @param uiFlags		 [IN] Denotes whether to allow UI during the relink operation.
		 @param skippedLinks [IN] List of the link UIDs that could not be relinked because
								  no matching file with the given extension existed.
		 @return kSuccess if one or more of the links are relinked, else an error code.
		 */
		virtual ErrorCode RelinkLinksExtension(const UIDList& links, const WideString& extension, UIFlags uiFlags, UIDList& skippedLinks) const = 0;

		/**
		 Determines if a link's resource can be copied to a folder. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be copied to a folder, else false.
		 */
		virtual bool CanCopyLinkToFolder(const UIDRef& linkRef) const = 0;

		/**
		 Copies links' resources to the specified folder, and optionally relinks the resources
		 to point to the new location.
		 @param links	 [IN] List of links whose resources to copy.
		 @param folder	 [IN] Folder to copy the resources to.
		 @param bRelink	 [IN] Denotes whether to relink the resources to the files in the destination folder.
		 @param uiFlags	 [IN] Denotes whether to allow UI during the copy operation.
		 @return kSuccess if the links' resources are copied, else an error code.
		 */
		virtual ErrorCode CopyLinksToFolder(const UIDList& links, const IDFile& folder, bool bRelink, UIFlags uiFlags) const = 0;

		/**
		 Updates links' resource modification states to modified if the resource
		 has been modified.
		 @param links [IN] List of links to update.
		 @return kSuccess if the links' states are updated, else an error code.
		 */
		virtual ErrorCode UpdateLinkStates(const UIDList& links) const = 0;

		/**
		 Set links' resource modification states to to the given state.
		 @param links	 [IN] List of links to set.
		 @param modState [IN] Resource modification state to set the links to.
		 @return kSuccess if the links' states are set, else an error code.
		 */
		virtual ErrorCode SetLinkResourceModStates(const UIDList& links, ILink::ResourceModificationState modState) const = 0;

		/**
		 Determines if a link's resource can be edited. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be edited, else false.
		 */
		virtual bool CanEditLink(const UIDRef& linkRef) const = 0;

		/**
		 Edits a link's resource. 
		 @param linkRef		[IN] UIDRef of the link whose resource to edit.
		 @param appInfo		[IN] Indicates which app to edit the resource with.
								 kNullAppInfo to use the default editor.
		 @param errorString	[OUT] If editing fails, this fills out an error message
								  when the string pointer is non-nil
		 @return kSuccess if the link's resource was edited, else an error code.
		 */
		virtual ErrorCode EditLink(const UIDRef& linkRef, const AppInfo& appInfo, PMString* errorString) const = 0;

		/**
		 Determines if a link's resource can be opened in InDesign. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be opened (i.e. it is a sharedContent link), else false.
		 */
		virtual bool CanGoToSource(const UIDRef& linkRef) const = 0;

		/**
		 Opens a link's resource in InDesign.
		 @param linkRef		[IN] UIDRef of the link whose resource to open.
		 @param errorString	[OUT] If opening fails, this fills out an error message
								  when the string pointer is non-nil
		 @return kSuccess if the link's resource was opened, else an error code.
		 */
		virtual ErrorCode GoToSource(const UIDRef& linkRef, PMString* errorString) const = 0;

		/**
		 Determines if a link's resource can be revealed in the system's file browser. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be revealed, else false.
		 */
		virtual bool CanRevealLink(const UIDRef& linkRef) const = 0;

		/**
		 Reveals a link's resource in the system's file browser. 
		 @param linkRef [IN] UIDRef of the link whose resource to reveal.
		 @return kSuccess if the link's resource was revealed, else an error code.
		 */
		virtual ErrorCode RevealLink(const UIDRef& linkRef) const = 0;

		/**
		 Determines if a link's resource can be revealed in Adobe Bridge. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be revealed in Bridge, else false.
		 */
		virtual bool CanRevealLinkInBridge(const UIDRef& linkRef) const = 0;

		/**
		 Reveal a link's resource in Adobe Bridge. 
		 @param linkRef [IN] UIDRef of the link whose resource to reveal in Adobe Bridge.
		 @return kSuccess if the link's resource was revealed in Bridge, else an error code.
		 */
		virtual ErrorCode RevealLinkInBridge(const UIDRef& linkRef) const = 0;
		
		/**
		 Determines if a link's resource can be revealed in CC Libraries panel. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be revealed in CC Libraries panel, else false.
		 */
		virtual bool CanRevealLinkInCloudLibraries(const UIDRef& linkRef) const = 0;
		
		/**
		 Reveale a link's resource in CC Libraries. 
		 @param linkRef [IN] UIDRef of the link whose resource to reveal in CC Libraries.
		 @return kSuccess if the link's resource was revealed in CC Libraries, else an error code.
		 */
		virtual ErrorCode RevealLinkInCloudLibraries(const UIDRef& linkRef) const = 0;

		/**
		 Determines whether a link's linked object can be displayed.
		 @param linkRef [IN] UIDRef of the link to check.
		 @return True if the goto operation is supported, else false.
		 */
		virtual bool CanGotoLink(const UIDRef& linkRef) const = 0;

		/**
		 Displays a link's linked object.
		 @param linkRef		[IN] UIDRef of the link whose linked object to go to.
		 @param errorString	[OUT] If the goto fails, this fills out an error
								  message when the string pointer is non-nil
		 @return kSuccess if the goto operation succeeds, else an error code.
		 */
		virtual ErrorCode GotoLink(const UIDRef& linkRef, PMString* errorString) const = 0;

		/**
		 Determines if a link's resource can be packaged. 
		 @param linkRef [IN] UIDRef of the link whose resource to check.
		 @return True if the link's resource can be packaged, else false.
		 */
		virtual bool CanPackageLink(const UIDRef& linkRef) const = 0;

		/**
		 Returns a link's linked resource.
		 @param linkRef	[IN] UIDRef of the link.
		 @return Link's linked resource.
		 */ 
		virtual UID GetLinkResource(const UIDRef& linkRef) const = 0;

		/**
		 Returns a link's linked object.
		 @param linkRef	[IN] UIDRef of the link.
		 @return Link's linked object.
		 */ 
		virtual UID GetLinkObject(const UIDRef& linkRef) const = 0;

		/**
		 Returns whether a link has child links.
		 @param linkRef	[IN] UIDRef of the link.
		 @return True if the link has child links, else false.
		 */ 
		virtual bool LinkHasChildren(const UIDRef& linkRef) const = 0;

		/**
		 Identifiers that denote the combined status of a link and its
		 linked resource. The identifiers take into account the link's
		 resource and object modification states, as well as the link's
		 linked resource's state and stored state.
		 The identifiers are used to get the combined status of a link
		 and its linked resource.
		 The state may not be the actual current state of the resource.
		 */
		enum LinkStatus {
			/** Link is up-to-date and available for use. */
			kLinkUpToDate = 0,
			/** Link is out-of-date and needs to be updated. */
			kLinkOutOfDate,
			/** Link resource is embedded, and link is up-to-date. */
			kLinkResourceEmbedded,
			/** Link resource is cached, and link is up-to-date. */
			kLinkResourceCached,
			/** Link resource is contained, and link is up-to-date. */
			kLinkResourceContained,
			/** Link resource is missing. */
			kLinkResourceMissing,
			/** Link resource is not accessible by the user. */
			kLinkResourceInaccessible,
			/** Link resource state is pending an update. */
			kLinkResourcePending,
			/** Link resource state cannot be determined. */
			kLinkResourceUnknown
		};

		/**
		 Returns the combined status of a link and its linked resource.
		 @param linkRef		 [IN] UIDRef of the link.
		 @param bUpdateState [IN] Denotes whether to update the resource and
								  link states first, so the returned status is
								  a current status rather than the cached status.
		 @return Combined status of the link and its linked resource.
		 */ 
		virtual LinkStatus GetLinkStatus(const UIDRef& linkRef, bool bUpdateState) const = 0;

		/**
		Determines if a resource which is a placeholder(FPO) can be replaced.
		@param linkRef [IN] UIDRef of the link to be replaced.
		@return true if the resource if placeholder (FPO) can be replaced with the original, else false.
		@see ILinkResourceRenditionData::ResourceRenditionType
		*/
		virtual bool CanReplaceFPOWithOriginalLink(const UIDRef& linkRef) const = 0;

		/**
		Replaces a link resource which is a placeholder (FPO) with the original.
		@param linkRef	[IN] UIDRef of the link.
		@param uiFlags	[IN] Denotes whether to allow UI during the replace operation.
		@param bIgnoreErrors [IN] Denotes whether to ignore intermediate errors for some of the links.
		@param newLinkUIDs [OUT] UIDList of the links as a result of the replace to original. Link UIDs may 
		change as a result of this operation.
		@return kSuccess if the FPO link resource is replaced with original, else an error code.
		@see ILinkResourceRenditionData::ResourceRenditionType
		*/
		virtual ErrorCode ReplaceFPOWithOriginalLink(const UIDRef& linkRef, UIFlags uiFlags, bool16 bIgnoreErrors, UIDList& newLinkUIDs) const = 0;

		/**	
		Replaces the placeholder links with the original links.
		@param links			[IN] List of links to replace.
		@param uiFlags			[IN] Denotes whether to allow UI during the replace operation.
		@param bIgnoreErrors	[IN] Denotes whether to ignore intermediate errors for some of the links.
		@param pNewLinks		[OUT] List of the resulting links of the replace with original operation.
		The nth link in the newLinks UIDList corresponds the nth
		link in the given links UIDList, and may or may not be the
		same as the input UID. kInvalidUID is returned for links that have
		been deleted as a result of the replace.
		@return kSuccess if the placeholder links are replaced with original links.
		@see ILinkResourceRenditionData::ResourceRenditionType
		*/
		virtual ErrorCode ReplaceAllFPOWithOriginalLinks(const UIDList& links, 
															UIFlags uiFlags, 
															bool16 bIgnoreErrors,
															UIDList* pNewLinks = nil) const = 0;
		/**
		Determines if the original for an FPO resource can be downloaded.
		@param linkRef [IN] UIDRef of the link to be downloaded.
		@return true if the original resource for an FPO resource can be downloaded, else false.
		@see ILinkResourceRenditionData::ResourceRenditionType
		*/
		virtual bool CanDownloadOriginalLink(const UIDRef& linkRef) const = 0;

		/**
		Downloads the original asset for the given placeholder link resource.
		@param linkRef	[IN] UIDRef of the link whose original asset is downloaded.
		@param async	[IN] Whether the download is synchronous or asynchronous.
		@return kSuccess if the original is downloaded for sync operation or can be downloaded for async operation, else an error code.
		*/
		virtual ErrorCode DownloadOriginalLink(const UIDRef& linkRef, bool async = true) const = 0;

		/**
		Downloads the original links for all the placeholder links.
		@param links [IN] List of links to download.
		@param async [IN] Whether the download is synchronous or asynchronous.
		@return kSuccess if the originals are downloaded for sync operations or can be downloaded for async operations for all placeholder resources, else an error code.
		*/
		virtual ErrorCode DownloadAllOriginalLinks(const UIDList& links, bool async = true) const = 0;
		
        /**
         Gets the Default rendition type for HTTP Links
         @param type [OUT] current default rendition type for HTTP links
         @return true if the fetching is successful, otherwise false
         */
        virtual bool GetHTTPLinksDefaultRenditionType(ILinkResourceRenditionData::ResourceRenditionType &type) const = 0;
        
        /**
         Sets the Default rendition type for HTTP Links
         @param type [IN] the new default rendition type value
         @return kSuccess if the rendition type is successfully changed, else an error code.
         */
        virtual ErrorCode SetHTTPLinksDefaultRenditionType(const ILinkResourceRenditionData::ResourceRenditionType &type) const = 0;
        
	};
} // namespace Facade

#endif // __ILinkFacade__
