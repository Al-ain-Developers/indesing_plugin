//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceHandler.h $
//  
//  Owner: Adobe Developer Technologies
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
//  
//========================================================================================

#pragma once
#ifndef __CusDtLnkLinkResourceHandler__
#define __CusDtLnkLinkResourceHandler__

// ----- Includes -----
#include "CPMUnknown.h"
#include "ILinkResourceHandler.h"


/** The resource handler for link resource with an URI whose scheme is 'CSVLink'.  A resource handler is required when you create link
	with youe own URI scheme.  By default InDesign's file link has its URI begins with file://... the file in the URI is the scheme.
	Therefore, in the InDesign code base, there is a resource handler that knows how to handle link resource of URI scheme 'file'.
	
	CusDtLnk creats a new type of link with URI scheme 'CSVLink', its URI beings with CSVLink://... This resource handler CusDtLnkLinkResourceHandler
	provides important data for the link resource, such as the import stream.  When a CSVLink link needs to import data, this resource 
	handler will be the one called upon by links architecture to actually parse the CSV, and open the corresponding image file for read.

	@ingroup customdatalink
*/
class CusDtLnkLinkResourceHandler : public CPMUnknown<ILinkResourceHandler>
{
public:
	typedef CPMUnknown<ILinkResourceHandler> inherited;
	typedef object_type data_type;

	CusDtLnkLinkResourceHandler(IPMUnknown* boss);
	virtual ~CusDtLnkLinkResourceHandler();

	/**	@see ILinkResourceHandler::Init
	 */
	virtual bool Init(const UIDRef& ref, const URI& uri) { return true; }

	/**	@see ILinkResourceHandler::IsResourceURIValid
	 */
	virtual bool IsResourceURIValid(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::AreResourceIdsEquivalent
	 */
	virtual bool AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const;
	/**	@see ILinkResourceHandler::GetResourceDataType
	 */
	virtual FileTypeInfo GetResourceDataType(const UIDRef& ref, const URI& uri) const;

	/**	@see ILinkResourceHandler::GetShortResourceName
	 */
	virtual WideString GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;
	/**	@see ILinkResourceHandler::GetLongResourceName
	 */
	virtual WideString GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;

	/**	@see ILinkResourceHandler::GetResourceStateInfo
	 */
	virtual PMString GetResourceStateInfo(const UIDRef& ref, const URI& uri, ILinkResource::ResourceState state, ILinkResource::ResourceStoreState storeState) const { return PMString(); }

	/**	@see ILinkResourceHandler::AreStampsEquivalent
	 */
	virtual bool AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const;

	/**	@see ILinkResourceHandler::CanReadResource
	 */
	virtual bool CanReadResource(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CanWriteResource
	 */
	virtual bool CanWriteResource(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CanReadWriteResource
	 */
	virtual bool CanReadWriteResource(const UIDRef& ref, const URI& uri) const;

	/**	@see ILinkResourceHandler::CanCreateResourceStream
	 */
	virtual bool CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const;
	/**	@see ILinkResourceHandler::CreateResourceReadStream
	 */
	virtual IPMStream* CreateResourceReadStream(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CreateResourceWriteStream
	 */
	virtual IPMStream* CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CreateResourceReadWriteStream
	 */
	virtual IPMStream* CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const;

	/**	@see ILinkResourceHandler::CanCacheResource
	 */
	virtual bool CanCacheResource(const UIDRef& ref, const URI& uri) const { return true; }
	/**	@see ILinkResourceHandler::CanEmbedResource
	 */
	virtual bool CanEmbedResource(const UIDRef& ref, const URI& uri) const { return true; }
	/**	@see ILinkResourceHandler::CanUnembedResource
	 */
	virtual bool CanUnembedResource(const UIDRef& ref, const URI& uri) const { return true; }

	/**	
		@see ILinkResourceHandler::CanCopyToFile
	 */
	virtual bool CanCopyToFile(const UIDRef& ref, const URI& uri) const;

	/**	@see ILinkResourceHandler::CopyToFile
	 */
	virtual ErrorCode CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const;

	/**	@see ILinkResourceHandler::CanEditResource
	 */
	virtual bool CanEditResource(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::EditResource
	 */
	virtual ErrorCode EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const;

	/**	@see ILinkResourceHandler::CanRevealResource
	 */
	virtual bool CanRevealResource(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::RevealResource
	 */
	virtual ErrorCode RevealResource(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CanRevealResourceInBridge
	 */
	virtual bool CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::RevealResourceInBridge
	 */
	virtual ErrorCode RevealResourceInBridge(const UIDRef& ref, const URI& uri) const;
	/**	@see ILinkResourceHandler::CanRevealResourceInCloudLibraries
	 */	
	virtual bool CanRevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const { return false; }
	/**	@see ILinkResourceHandler::RevealResourceInCloudLibraries
	 */
	virtual ErrorCode RevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const { return kFailure; }
	/**	@see ILinkResourceHandler::GetXMPPacketInfo
	*/
	virtual bool GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const { return false; }
	/**	@see ILinkResourceHandler::CanGetXMPPacketInfo
	*/
	virtual bool CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const { return false; }
	/**	@see ILinkResourceHandler::CanDownloadOriginalResource
	*/
	virtual bool CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const { return false; }
	/**	@see ILinkResourceHandler::DownloadOriginalResource
	*/
	virtual ErrorCode DownloadOriginalResource(const UIDRef& ref, const URI& uri) const { return kFailure; }
	/**	@see ILinkResourceHandler::AsyncDownloadOriginalResource
	*/
	virtual ErrorCode AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const { return kFailure; }
	/**	@see ILinkResourceHandler::CanReplaceFPOWithOriginalResource
	*/
	virtual bool CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const { return false; }
	/**	@see ILinkResourceHandler::GetResourceDownloadProgress
	*/
	virtual ILinkResource::ResourceDownloadState GetResourceDownloadProgress(const UIDRef& ref, const URI& uri, PMReal& progress) const { return ILinkResource::kComplete; }
	/**	@see ILinkResourceHandler::CanProvideFile
	*/
	virtual bool CanProvideFile(const UIDRef& ref, const URI& uri) const { return false; }
	/**	@see ILinkResourceHandler::GetFile
	*/
	virtual ErrorCode GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const { return kFailure; }
	virtual bool canGetInstanceName() const { return false; }
	virtual ErrorCode GetInstanceName(PMString &uri) const { return kFailure; }

private:
	// Prevent copy construction and assignment.
	CusDtLnkLinkResourceHandler(const CusDtLnkLinkResourceHandler&);
	CusDtLnkLinkResourceHandler& operator=(const CusDtLnkLinkResourceHandler&);
};

#endif // __CusDtLnkLinkResourceHandler__
