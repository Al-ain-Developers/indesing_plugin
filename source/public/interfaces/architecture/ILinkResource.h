//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResource.h $
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
//  This class defines an interface used to maintain and access a linked resource.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResource__
#define __ILinkResource__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"
#include "AppInfo.h"
#include <boost/function.hpp> 
class ILinkResourceHandler;
class IPMStream;

class FileTypeInfo;
class IDTime;
class PMString;
class UIDList;
class URI;
class WideString;


/**
 ILinkResource is used to maintain and access a linked resource.  A linked resource is
 an external or internal source of imported data, or external or internal target of
 exported data.  All linked resources are referenced by a URI, whose scheme is used to
 denote the type of the resource and obtain the correct ILinkResourceHandler.

 Several operations and attribute request are deferred to the ILinkResourceHandler.
 When the resource is instantiated, the handler is obtained using the scheme of
 the resource's URI as a key to find the appropriate provider.  If no handler is found,
 due to a missing plug-in for instance, the resource is assigned a default handler that
 essentially treats the resource as if it were missing, and results in the resource's
 state to be set to kUnknown.

 @see ILinkResourceHandler
 @see IPMStream
 @see URI
 */
class ILinkResource : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCE };

	typedef URI			ResourceId;
	typedef WideString	ResourceStamp;

	/**
	 DEPRECATED - Please call the GetId method instead.
	 Returns the resource's Uniform Resource Identifier (URI). \\
	 The URI is used to uniquely identify the resource's type and location.
	 @return Resource's URI.
	 */ 
	virtual ResourceId GetURI() const = 0;

	/**
	 Returns the resource's Uniform Resource Identifier (URI). \\
	 The URI is used to uniquely identify the resource's type and location.
	 @return Resource's URI.
	 */ 
	virtual ResourceId GetId() const = 0;

	/**
	 Determines if the given id is equivalent to the resource's id.
	 @param id [IN] Resource id to compare with the resource's id.
	 @return True if the given id is equivalent to the resource's id, else false.
	 */ 
	virtual bool IsIdEquivalent(const ResourceId& id) const = 0;

	/**
	 Returns the resource's link client identifier.
	 @return Resource's link client identifier.
	 */ 
	virtual LinkClientID GetClientID() const = 0;

	/**
	 Returns the resource's short name. \\
	 For example, the short name for a file resource is the file's name.
	 @param bUIName [IN] Denotes to return the resource's short UI name if different
						 from the resource's actual short name.\\
						 In some cases, resources may want to have short UI name that
						 differs from the resource's actual short name. For example, file
						 resources on the Mac return a POSIX file name as the resource's
						 actual short name, and a HFS file name as the resource's short
						 UI name.
	 @return Resource's short name.
	 */ 
	virtual WideString GetShortName(bool bUIName) const = 0;

	/**
	 Returns the resource's long name. \\
	 For example, the long name for a file resource is the file's full path.
	 @param bUIName [IN] Denotes to return the resource's long UI name if different
						 from the resource's actual long name.\\
						 In some cases, resources may want to have long UI name that
						 differs from the resource's actual long name. For example,
						 file resources on the Mac return a POSIX path as the resource's
						 actual long name, and a HFS path as the resource's long UI name.
	 @return Resource's long name.
	 */ 
	virtual WideString GetLongName(bool bUIName) const = 0;

	/**
	 Identifiers that denote the availability state of the linked resource.
	 The identifiers are used to get and set the availability state of a linked resource.
	 The state may not be the actual current availability state of the resource.
	 */
	enum ResourceState {
		/** Resource is available for use. */
		kAvailable = 0,
		/** Resource cannot be found. */
		kMissing,
		/** Resource's state is in the process of being updated. */
		kPending,
		/** Resource's state is not known, and cannot be obtained. */
		kUnknown,
		/** Resource is not accessible by the user. */
		kInaccessible
	};
	
	/**
	 Returns the resource's availability state.
	 @return Resource's availability state.
	 */ 
	virtual ResourceState GetState() const = 0;

	/**
	 Sets the resource's availability state.
	 @param state [IN] Availability state of the resource.
	 */ 
	virtual void SetState(ResourceState state) = 0;

	/**
	 Identifiers that denote the store state of the link resource.
	 The identifiers are used to get the store state of the resource.
	 */
	enum ResourceStoreState {
		/** Resource is not cached or embedded. */
		kNormal = 0,
		/** Resource is cached. */
		kCached,
		/** Resource is embedded. */
		kEmbedded,
		/** Resource is fully contained in the object that links the resource.\\
			Contained resources can not be cached or embedded. */
		kContained
	};
	
	/**
	 Returns the resource's store state.
	 @return Resource's store state.
	 */ 
	virtual ResourceStoreState GetStoreState() const = 0;

	/**
	 Sets the resource's store state to kContained.\\
	 This call is ignored for resources that are cached or embedded.
	 */ 
	virtual void SetContainedInObject() = 0;

	/**
	 Returns the resource's stamp. \\
	 The stamp, in conjuction with the URI, uniquely identifies
	 an resource at a given point in time.
	 @return Resource's stamp.
	 */ 
	virtual ResourceStamp GetStamp() const = 0;

	/**
	 Sets the resource's stamp.
	 @param stamp [IN] Stamp of the resource.
	 */ 
	virtual void SetStamp(const ResourceStamp& stamp) = 0;

	/**
	 Determines if the given stamp is equivalent to the resource's stamp.
	 @param stamp [IN] Stamp to compare with the resource's stamp.
	 @return True if the given stamp is equivalent to the resource's stamp, else false.
	 */ 
	virtual bool IsStampEquivalent(const ResourceStamp& stamp) const = 0;

	/**
	 Returns the resource's current modification date/time.
	 @return Resource's current modification date/time.
	 */ 
	virtual IDTime GetModTime() const = 0;

	/**
	 Sets the resource's current modification date/time.
	 @param size [IN] Current modification date/time of the resource.
	 */ 
	virtual void SetModTime(const IDTime& time) = 0;

	/**
	 Returns the resource's size in bytes.
	 @return Resource's size in bytes.
	 */ 
	virtual uint64 GetSize() const = 0;

	/**
	 Sets the resource's size in bytes.
	 @param size [IN] Size of the resource in bytes.
	 */ 
	virtual void SetSize(uint64 size) = 0;

	/**
	 Returns the resource's data/file type.
	 @return Resource's data/file type.
	 */ 
	virtual FileTypeInfo GetDataType() const = 0;

	/**
	 Returns the resource's import/export format type.
	 @return Resource's import/export format type.
	 */ 
	virtual PMString GetFormatType() const = 0;

	/**
	 Sets the resource's import/export format type.
	 @param formatType [IN] Resource's import/export format type.
	 */ 
	virtual void SetFormatType(const PMString& formatType) = 0;

	/**
	 Identifiers that denote the type of access the link resource supports.
	 The identifiers are used to get the type of access supported by the
	 resource, and to query for streams.
	 */
	enum AccessMode {
		/** Read data from the resource. */
		kRead = 0,
		/** Write data to the resource. */
		kWrite,
		/**
		 Read and write the resource's data simultaneously. \\
		 Read/write is never supported for cached or embedded resources.
		 */
		kReadWrite
	};

	/**
	 Determines if the resource generally supports the given access mode. \\
	 It is possible that the resource generally supports the given
	 access mode, but it is not possible to currently obtain a
	 stream due to the resource being read or written by other processes.
	 Therefore, to determine if a stream can currently be obtained with
	 the given access mode, call CanQueryStream().
	 @param mode [IN] Access mode.
	 @return True if the resource generally supports the given access mode,
			 else false.
	 */ 
	virtual bool IsAccessSupported(AccessMode mode) const = 0;

	/**
	 Test whether a stream with the given access mode can currently
	 be obtained for the resource. \\
	 The state of whether a stream can be obtained with the given access
	 mode may change at any time, so it is best to attempt to obtain
	 the stream immediately following the call to CanQueryStream(). 
	 @param mode [IN] Access mode.
	 @return True if a stream with the given access mode can currently
			 be obtained, else false.
	 */ 
	virtual bool CanQueryStream(AccessMode mode) const = 0;

	/**
	 Returns a stream that is used to access the resource's data. \\
	 If the access mode is kRead and the resource is cached or embedded,
	 the returned stream will read the cached or embedded data. \\
	 If the access mode is kWrite and the resource is cached, the returned
	 stream will write data to the actual resource, not the cache.
	 @param mode [IN] Access mode.
	 @return Pointer to a referenced stream; the caller is responsible
			 for releasing the stream. \\
			 Nil if a stream cannot be obtained.
	 */
	virtual IPMStream* QueryStream(AccessMode mode) const = 0;

	/**
	 Determines if the resource can be cached by calling Cache(). \\
	 Embedded resources are never are cacheable.
	 @return True if the resource can be cached by calling Cache(), else false.
	 */
	virtual bool CanCache() const = 0;

	/**
	 Caches the resource. \\
	 If the resource is already cached, then attempts to update the cache from the resource.
	 @return kSuccess if the resource was cached, else an error code.
	 */
	virtual ErrorCode Cache() = 0;

	/**
	 Uncaches the resource.
	 @return kSuccess if the resource was uncached, else an error code. \\
			 kFailure is returned if the resource is not currently cached.
	 */
	virtual ErrorCode Uncache() = 0;

	/**
	 Determines if the resource can be embedded by calling Embed().
	 @return True if the resource can be embedded by calling Embed(), else false.
	 */
	virtual bool CanEmbed() const = 0;

	/**
	 Embeds the resource. \\
	 If the resource is already embedded, then the call is ignored and returns kSuccess.
	 @return kSuccess if the resource was embedded, else an error code.
	 */
	virtual ErrorCode Embed() = 0;

	/**
	 Embeds the resource from the given read stream. If successful, this call will set the
	 resource's state, stored state and size.  However, it is the caller's responsibility
	 to set the resource's stamp. \\
	 Note: This method should only be used for special cases like creating an embedded
		   link resource from INX, or creating link resources for embedded graphics
		   contained in Word documents.
	 @param stream [IN] Read stream containing the resource's embedded data.
	 @return kSuccess if the resource was embedded, else an error code.
	 */
	virtual ErrorCode EmbedFromStream(IPMStream* stream) = 0;

	/**
	 Determines if the resource can be unembedded by calling Unembed().
	 @return True if the resource can be unembedded by calling Unembed(), else false.
	 */
	virtual bool CanUnembed() const = 0;

	/**
	 Unembeds the resource to the same location it was embedded from.
	 @return kSuccess if the resource was unembedded, else an error code. \\
			 kFailure is returned if the resource is not currently embedded.
	 */
	virtual ErrorCode Unembed() = 0;

	/**
	 Determines if the resource can be copied to a file by calling CopyToFile().
	 @return True if the resource can be copied to a file by calling CopyToFile(), else false.
	 */
	virtual bool CanCopyToFile() const = 0;

	/**
	 Copies the resource to the given file.
	 @param file [IN] File to copy the resource to.
	 @return kSuccess if the resource was successfuly copied, else an error code.
	 */
	virtual ErrorCode CopyToFile(IDFile& file) const = 0;

	/**
	 Determines if the resource can be edited by calling Edit(). \\
	 Embedded resources are never editable.
	 @return True if the resource can be edited by calling Edit(), else false.
	 */
	virtual bool CanEdit() const = 0;

	/**
	 Edits the resource. \\
	 Embedded resources cannot be edited.
	 @param appInfo		[IN]  Indicates which app to edit the resource with.
							  kNullAppInfo to use the default editor.
	 @param errorString	[OUT] If editing fails, this fills out an error message when the string
							  pointer is non-nil
	 @return kSuccess if the resource was edited, else an error code.
	 */
	virtual ErrorCode Edit(const AppInfo& appInfo, PMString* errorString) = 0;

	/**
	 Determines if the resource can be revealed by calling Reveal().
	 @return True if the resource can be revealed by calling Reveal(), else false.
	 */
	virtual bool CanReveal() const = 0;

	/**
	 Reveals the resource.
	 @return kSuccess if the resource was revealed, else an error code.
	 */
	virtual ErrorCode Reveal() = 0;
	
	/**
	 Determines if the resource can be revealed by calling RevealInBridge().
	 @return True if the resource can be revealed by calling RevealInBridge(), else false.
	 */
	virtual bool CanRevealInBridge() const = 0;

	/**
	 Reveals the resource.
	 @return kSuccess if the resource was revealed, else an error code.
	 */
	virtual ErrorCode RevealInBridge() = 0;

	/**
	 Determines if the resource can be revealed by calling RevealInCloudLibraries.
	 @return True if the resource can be revealed by calling RevealInCloudLibraries(), else false.
	 */
	virtual bool CanRevealInCloudLibraries() const = 0;
	
	/**
	 Reveals the resource.
	 @return kSuccess if the resource was revealed in CC Libraries, else an error code.
	 */
	virtual ErrorCode RevealInCloudLibraries() = 0;

	/**
	 Copies the attributes of the resource referenced by the given UIDRef to this resource.
	 @param resourceRef [IN] UIDRef of the resource to copy. \\
							 The UIDRef may reference a resource in a different database.
	 @return kSuccess if the resource attributes were successfuly copied, else an error code.
	 */
	virtual ErrorCode CopyAttributes(const UIDRef& resourceRef) = 0;

	/**
	Determines if the resource is an FPO.
	@return true if the resource is an FPO else false.
	@see ILinkResourceRenditionData::ResourceRenditionType
	*/
	virtual bool IsFPO() const = 0;	
	
	/**
	Determines if we can get the XMP Info for the resource.
	@return true if we can get the XMP info else false.
	*/
	virtual bool CanGetXMPPacketInfo() const = 0;
	
	/**
	Get the XMP Info for the resource
	@param packet [OUT] the resource's XMP info 
	@return true if the XMP info is filled in packet else false .
	*/
	virtual bool GetXMPPacketInfo(std::string& packet) const = 0;


	/**Identifiers that denote the download states of resource. */
	
	enum ResourceDownloadState {
		/** Download is not requested. */
		kNotStarted = 0,
		/** Download started or request is in queue. */
		kInProgress,
		/** Download completed. */
		kComplete,
		/** Download stopped without completion. */
		kDownloadError
	};

	/**
	Return resource's download state and fill progress 
	@param progress [OUT] the progress of the resource download - currently unused
	@return ResourceDownloadState resource's download state
	*/
	virtual ResourceDownloadState GetDownloadProgress(PMReal& progress) const = 0;

	/**
	Determines if a resource which is a placeholder(FPO) can be downloaded.
	@return true if the original resource can be downloaded.
	*/
	virtual bool CanDownloadOriginal() const = 0;

	/**
	Downloads the original asset synchronously for the given placeholder link resource.
	@return kSuccess if the original is downloaded, else an error code.
	*/
	virtual ErrorCode DownloadOriginal() = 0;

	typedef boost::function<void(const ILinkResource::ResourceId& resourceId, const ILinkResource::ResourceDownloadState& resourceDownloadState)> DownloadCompletionFunction;

	/**
	Downloads the original asset asynchronously for the given placeholder link resource.
	@param completionFunction function to invoke when download has completed.
	@return kSuccess if the original can be downloaded, else an error code.
	*/
	virtual ErrorCode AsyncDownloadOriginal(ILinkResource::DownloadCompletionFunction completionFunction) = 0;

	/**
	Determines if a placeholder(FPO) can be replaced with the original
	@return true if the FPO can be replaced with the original else false.
	*/
	virtual bool CanReplaceFPOWithOriginal() const = 0;

	/**
	Determines if a resource can provide the underlying file or not.
	@return true if the resource can provide the file.
	*/
	virtual bool CanProvideFile() const = 0;

	/**
	Get the underlying file from the link resource.
	@param idFile [OUT] the underlying file for the link resource
	@return kSuccess if the underyling file is available, else an error code.
	*/
	virtual ErrorCode GetFile(IDFile& idFile) const = 0;
	
    /**
	Determines if a link instance can be obtained.
    @return true if the link instance can be obtained.
	*/
	virtual bool CanGetLinkInstance() const = 0;
    
	/*
	Get the underlying link instance.
	@param PMString [OUT] instance the underlying instance name
    @return kSuccess if the link instance can be obtained, else an error code.
	*/
	virtual ErrorCode GetlinkInstance(PMString &instance) const = 0;

};

#endif // __ILinkResource__
