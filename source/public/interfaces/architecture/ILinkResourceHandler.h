//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceHandler.h $
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
//  This class defines an interface that implements behavior for an ILinkResource that
//  is specific to the type of the resource as identified by the scheme of the link
//  resource's URI.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResourceHandler__
#define __ILinkResourceHandler__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"
#include "AppInfo.h"

#include "ILinkResource.h"


/**
 ILinkResourceHandler is used to implement behavior for an ILinkResource that is specific
 to the type of a resource as identified by the scheme of the link resource's URI.  The
 link resource defers many operations and attribute request to the handler.  For example,
 it is left to the handler to determine if two resources have equivalent URIs or stamps.
 The handler is also used to determine what operations are allowed, to obtain streams to
 the resource, and to edit and copy the resource.

 To associate a handler for a specific type of resource, a factory for the type of resource
 is registered via a link resource provider for the kLinkResourceService.  For example, a
 file based link resource will require a different provider and handler than a database link
 resource. 
 
 When an ILinkResource object is instantiated, the handler is obtained using the scheme of
 the resource's URI as a key to find the appropriate provider.  If no handler is found, due
 to a missing plug-in for instance, the link resource is assigned a default handler that
 essentially treats the resource as if it were missing.  Therefore, all resources that have
 a custom URI must provide a handler.

 @see ILinkResource
 @see IPMStream
 @see URI
 */
class ILinkResourceHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCEHANDLER };

	/**
	 Called by the LinkResource to allow the handler to initialize itself.
	 This method can be used by the handler to optimize its resource handling.
	 For example, the handler may want to parse the URI in this method so
	 that calls to other methods can used the parsed information.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the link resource.
	 @return True if the handler initializes without errors, else false.
	 */
	virtual bool Init(const UIDRef& ref, const URI& uri) = 0;

	/**
	 Called to determine if the provider supports the given URI.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI to check.
	 @return True if the URI is supported, else false.
	 */
	virtual bool IsResourceURIValid(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if the given resource references are equivalent.
	 @param id1 [IN] Resource identifier to compare with id2.
	 @param id2 [IN] Resource identifier to compare with id1.
	 @return True if the given resource identifiers are equivalent, else false.
	 */ 
	virtual bool AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const = 0;

	/**
	 Called to get a resource's data/file type.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to get the data/file type for.
	 @return Resource's data/file type.
	 */ 
	virtual FileTypeInfo GetResourceDataType(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to get a resource's short name. \\
	 For example, the short name for a file resource is the file's name.
	 @param ref			 [IN] UID reference of the link resource.
	 @param uri			 [IN] URI of the resource to get a short name for.
	 @param bUIName [IN] Denotes to return the resource's short UI name if different
						 from the resource's actual short name.\\
						 In some cases, resources may want to have short UI name that
						 differs from the resource's actual short name. For example, file
						 resources on the Mac return a POSIX file name as the resource's
						 actual short name, and a HFS file name as the resource's short
						 UI name.
	 @return Resource's short name.
	 */ 
	virtual WideString GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const = 0;

	/**
	 Called to get a resource's long name. \\
	 For example, the long name for a file resource is the file's full path.
	 @param ref			 [IN] UID reference of the link resource.
	 @param uri			 [IN] URI of the resource to get a long name for.
	 @param bUIName [IN] Denotes to return the resource's long UI name if different
						 from the resource's actual long name.\\
						 In some cases, resources may want to have long UI name that
						 differs from the resource's actual long name. For example,
						 file resources on the Mac return a POSIX path as the resource's
						 actual long name, and a HFS path as the resource's long UI name.
	 @return Resource's long name.
	 */ 
	virtual WideString GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const = 0;

	/**
	 Called to get additional information about a resource's state. \\
	 The additional information is added to state string the Links UI displays in the
	 link information pane and the status tooltip.
	 @param ref		   [IN] UID reference of the link resource.
	 @param uri		   [IN] URI of the resource to get a state informational string for.
	 @param state	   [IN] Resource's current availability state.
	 @param storeState [IN] Resource's current store state.
	 @return Additional resource state information.
	 */ 
	virtual PMString GetResourceStateInfo(const UIDRef& ref, const URI& uri, ILinkResource::ResourceState state, ILinkResource::ResourceStoreState storeState) const = 0;

	/**
	 Called to determine if the given resource stamps are equivalent.
	 @param stamp1 [IN] Stamp to compare with stamp2.
	 @param stamp2 [IN] Stamp to compare with stamp1.
	 @return True if the given stamps are equivalent, else false.
	 */ 
	virtual bool AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const = 0;

	/**
	 Called to determine if a resource can be read.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be read, else false.
	 */
	virtual bool CanReadResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be written.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be written, else false.
	 */
	virtual bool CanWriteResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be read and written simultaneously.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be read and written simultaneously, else false.
	 */
	virtual bool CanReadWriteResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can currently be opened with the given access mode.
	 @param ref	   [IN] UID reference of the link resource.
	 @param uri	   [IN] URI of the resource to check.
	 @param access [IN] Type of access desired.
	 @return True if the resource can be opened with the given access mode, else false.
	 */
	virtual bool CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode access) const = 0;

	/**
	 Called to create a stream that can be used to read data from a resource. \\
	 The caller assumes responsibility for deleting the stream.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to create a read stream for.
	 @return Pointer to a read stream. \\
			 Nil if the resource is not readable.
	 */
	virtual IPMStream* CreateResourceReadStream(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to create a stream that can be used to write data to a resource. \\
	 The caller assumes responsibility for deleting the stream.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to create a write stream for.
	 @return Pointer to a write stream. \\
			 Nil if the resource is not writable.
	 */
	virtual IPMStream* CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to create a stream that can be used to read and write data from/to a resource. \\
	 The caller assumes responsibility for deleting the stream.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to create a read/write stream for.
	 @return Pointer to a read/write stream. \\
			 Nil if a read/write stream is not supported.
	 */
	virtual IPMStream* CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be cached.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be cached, else false.
	 */
	virtual bool CanCacheResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be embedded.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be embedded, else false.
	 */
	virtual bool CanEmbedResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be unembedded.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be unembedded, else false.
	 */
	virtual bool CanUnembedResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be copied to a file.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be copied to a file, else false.
	 */
	virtual bool CanCopyToFile(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to copy a resource to the given file.
	 @param ref	 [IN] UID reference of the link resource.
	 @param uri  [IN] URI of the resource to copy.
	 @param file [IN] File to copy the resource to.
	 @return kSuccess if the resource was successfuly copied, else an error code.
	 */
	virtual ErrorCode CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const = 0;

	/**
	 Called to determine if a resource can be edited.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be edited, else false.
	 */
	virtual bool CanEditResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to edit a resource.
	 @param ref			[IN]  UID reference of the link resource.
	 @param uri			[IN]  URI of the resource to edit.
	 @param appInfo		[IN]  Indicates which app to edit the resource with.
							  kNullAppInfo means use the default editor.
	 @param errorString	[OUT] If editing fails, this fills out an error message when the string pointer is non-nil
	 @return kSuccess if the resource was successfully edited, else an error code.
	 */
	virtual ErrorCode EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const = 0;

	/**
	 Called to determine if a resource can be revealed.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be revealed, else false.
	 */
	virtual bool CanRevealResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to reveal a resource.
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to reveal.
	 @return kSuccess if the resource was successfully revealed, else an error code.
	 */
	virtual ErrorCode RevealResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to determine if a resource can be revealed in Adobe Bridge
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be revealed, else false.
	 */
	virtual bool CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const = 0;

	/**
	 Called to reveal a resource in Adobe Bridge
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to reveal.
	 @return kSuccess if the resource was successfully revealed, else an error code.
	 */
	virtual ErrorCode RevealResourceInBridge(const UIDRef& ref, const URI& uri) const = 0;
	
	/**
	 Called to determine if a resource can be revealed in CC Libraries panel
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to check.
	 @return True if the resource can be revealed, else false.
	 */
	virtual bool CanRevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const = 0;
	
	/**
	 Called to reveal a resource in CC Libraries panel
	 @param ref [IN] UID reference of the link resource.
	 @param uri [IN] URI of the resource to reveal.
	 @return kSuccess if the resource was successfully revealed, else an error code.
	 */
	virtual ErrorCode RevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Determines if we can get the XMP Info for the resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if we can get the XMP info else false.
	*/
	virtual bool CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Get the XMP Info for the resource
	@param resourceRef [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@param packet [OUT] the resource's XMP info
	@return true if the XMP info is filled in packet else false .
	*/
	virtual bool GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const = 0;

	/**
	Called to determine if the original for an FPO resource can be downloaded.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if the resource can be downloaded, else false.
	@see ILinkResourceRenditionData::ResourceRenditionType
	*/
	virtual bool CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Called to download original synchronously for an FPO resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the resource to be downloaded.
	@return kSuccess if the resource was downloaded.
	@see ILinkResourceRenditionData::ResourceRenditionType
	*/
	virtual ErrorCode DownloadOriginalResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Called to download original asynchronously for an FPO resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the resource to be downloaded.
	@param completionFunction [IN] completion function to be called at the end of download.
	@return kSuccess if the resource can be downloaded.
	@see ILinkResourceRenditionData::ResourceRenditionType
	*/
	virtual ErrorCode AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const = 0;

	/**
	Called to determine if the FPO resource can be replaced with original.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if the FPO resource can be replaced with the original.
	@see ILinkResourceRenditionData::ResourceRenditionType
	*/
	virtual bool CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Return resource's download state and fill progress
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@param progress [OUT] the download progress, currently unused.
	@Return resource's download state
	*/
	virtual ILinkResource::ResourceDownloadState GetResourceDownloadProgress(const UIDRef& ref, const URI& uri, PMReal& progress) const = 0;

	/**
	Determines if a resource can provide the underlying file or not.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if the resource can provide the file.
	*/
	virtual bool CanProvideFile(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Get the underlying file from the link resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@param idFile [OUT] IDFile of the underlying link resource.
	@return kSuccess if the underlying file is available, else an error code.
	*/
	virtual ErrorCode GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const = 0;
	
    /*
	Determines if a resource can get the underlying instance name or not.
	@return true if the resource can provide the underlying instance name.
	*/
	virtual bool canGetInstanceName() const = 0;
	
    /*
	Get the underlying instance name from the link resource.
	@param instanceURI [OUT] authority component of the instance.
	return kSucess if it the instance name is available, else an error code.
	*/
	virtual ErrorCode GetInstanceName(PMString &instanceURI) const = 0;
	
};

#endif // __ILinkResourceHandler__
