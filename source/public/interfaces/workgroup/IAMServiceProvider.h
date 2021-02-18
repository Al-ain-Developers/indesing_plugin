//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMServiceProvider.h $
//  
//  Owner: Bill Tislar
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
#ifndef __IAMSERVICEPROVIDER__
#define __IAMSERVICEPROVIDER__

#include "IPMUnknown.h"
#include "workgroupid.h"
#include "IDFile.h"
#include "FileTypeRegistry.h"
#include "ILinkResource.h"
#include "IOpenFileCmdData.h"
#include "IManageableAsset.h"

class IAMService;
class WideString;

/** The IAMServiceProvider interface provides IAMService instances and other asset management services.
	@see IAMService.
*/
class IAMServiceProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSERVICEPROVIDER };
	
	/** The AssetService enum defines the service ID numbers for all of the asset management services
		currently used by the InDesign/InCopy/InDesignServer codebase. This list may be extended as
		needed by defining new unique service ID numbers.
	*/
	enum AssetService
	{
		/** This is the default AssetService ID. */
		enInvalidService = 0,
		
		/** This service ensures that the local (cached) file for an asset is the latest version by downloading
			the file from the asset store in cases where the cached file is missing or a newer version is
			available. If the cached file has been modified, the download should not be done without user
			authorization even if a newer version of the asset is available; i.e., local changes are never
			clobbered automatically.
			
			Provided that a local copy of the asset exists, implementations of this service should report
			kSuccess for this service even if the asset management system reports a download error. This
			policy assures that the existing local copy of the asset at least can be opened so that status
			alerts can be displayed with more infomation.
			
			Input IAMServiceData parameters:
				
				IAMService Data Identifier		  | Data Type	  |	Notes
			   -----------------------------------+---------------+--------------------------------------
				IAMService::enTargetAsset		  | IDFile		  | When specified, the service should use
												  |				  | the IDFile rather than the IManageableAsset *
												  |				  | argument on the IAMService::Do() method.
				
			Output IAMServiceData parameters: None.
			
			@see IAMService.
			@see IAMServiceData.		
		*/	
		enEnsureLatestVersion			= kWorkgroupPrefix + 1,
		
		/** Checks an asset into the asset management system and unlocks it. For most implementations this
			service will copy local changes to a secure location, such as the asset management database.
			After this service completes successfully, the asset is available for check out (see the enCheckOut
			service).
			
			Input IAMServiceData parameters:
			
				IAMService Data Identifier		 | Data Type	      | Notes
			   ----------------------------------+--------------------+--------------------------------------
				IAMService::enTargetAsset		 | IDFile		      | When specified, the service should use
												 |				      | the IDFile rather than the IManageableAsset *
												 |					  | argument on the IAMService::Do() method.
				IAMService::enCheckInComment	 | PMString			  | Empty PMString signifies a blank comment.
				IAMService::enForceSave			 | IWorkgroupFacade:: | Controls overwriting latest version with
												 |    ForceSave		  | local changes. 
				IAMService::enContentSaver		 | void *			  | Pointer to ISaveAssetContent callback.
												 |					  | When nil, save is not needed.
				IAMService::enOverrideAuthority  | boolean flag		  | For assignment packaging feature.
				IAMService::enCheckOutToUserName | PMString			  | For assignment packaging feature.
				IAMService::enUIFlags			 | UIFlags			  | UI permitted for use by the service.
			
			Output IAMServiceData parameters: None.
															  			
			@see ISaveAssetContent.
			@see IWorkgroupFacade.
		*/
		enCheckIn						= kWorkgroupPrefix + 2,
		
		/** Reverts local changes to an asset.
		
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.
		*/
		enRevert						= kWorkgroupPrefix + 3,
		
		/** Checks out an asset for editing. If locking is supported, the asset is also locked to indicate
			to others that it is in use.
			
			Input IAMServiceData parameters:
			
				IAMService Data Identifier		 | Data Type | Notes
			   ----------------------------------+-----------+--------------------------------------
				IAMService::enCheckOutToUserName | PMString	 | Empty PMString signifies a blank comment.
				IAMService::enUIFlags			 | UIFlags	 | UI permitted for use by the service.
			
			Output IAMServiceData parameters: None.			
		*/
		enCheckOut						= kWorkgroupPrefix + 4,
		
		/** Cancels a previous checkout without reverting the asset's contents. This service fails if the
			asset has been edited.
			
			Input IAMServiceData parameters:
			
				IAMService Data Identifier		 | Data Type | Notes
			   ----------------------------------+-----------+--------------------------------------
				IAMService::enUIFlags			 | UIFlags	 | UI permitted for use by the service.
			
			Output IAMServiceData parameters: None.			
		*/
		enCancelCheckOut				= kWorkgroupPrefix + 5,
		
		/** Executes any termination code required before an IManageableAsset instance is destroyed.
		
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.		
		*/
		enTerminate						= kWorkgroupPrefix + 6,
		
		/** Executes any initialization code to make an IManageableAsset instance ready for use.
			
			Input IAMServiceData parameters:
			
				IAMService Data Identifier	| Data Type	   | Notes
			   -----------------------------+--------------+--------------------------------------
				IAMService::enUseStoredData	| boolean flag | If set, init using asset management data
														   | stored with the link. This parameter applies
														   | only to managed linked assets.
			
			Output IAMServiceData parameters: None.			
		*/
		enInitialize					= kWorkgroupPrefix + 7,
		
		/** Executes any followup code required by the asset management system at the conclusion of
			a document Save operation. For example, as part of its asset status bookkeeping, Version Cue
			requires notification after a document has been saved locally.
			
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.				
		*/		
		enAfterSave						= kWorkgroupPrefix + 8,
		
		/** Executes any followup code required by the asset management system at the conclusion of
			a document SaveAs operation.
			
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.				
		*/
		enAfterSaveAs					= kWorkgroupPrefix + 9,
		
		/** Updates stored asset reference data for a managed link. The stored data (if any) depends on
			the requirements of the asset management system. For example, an opaque data byte sequence supplied
			by the Version Cue API is stored with the IDataLink when the link references a Version Cue asset.
			
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.				
		*/
		enUpdateStoredAssetReference	= kWorkgroupPrefix + 10,
		
		/** Upates the proxy version number for a managed link. The proxy version number is the version number
			of the asset used to create the proxy stored in an InDesign document. For example, the proxy may be
			the low-res version of a placed image, or the latest text in a placed InCopy story. The proxy version
			number is used to determine when the proxy itself (not the link) is out of date. 

			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.
		*/
		enUpdateProxyVersionNumber		= kWorkgroupPrefix + 11,
		
		/** Invalidates the proxy version number for a managed link.
		
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.			
		*/
		enInvalidateProxyVersionNumber	= kWorkgroupPrefix + 12,

		/** Provides a unique location with respect to the asset management system. This service is useful for
			providing a default location when saving a new asset.
			
			Input IAMServiceData parameters:
			
				IAMService Data Identifier		  | Data Type	  |	Notes
			   -----------------------------------+---------------+--------------------------------------
				IAMService::enTargetAsset		  | IDFile		  | Proposed location.


			Output IAMServiceData parameters:

				IAMService Data Identifier		  | Data Type	  |	Notes
			   -----------------------------------+---------------+--------------------------------------
				IAMService::enUniqueAssetLocation | IDFile		  | Location provided by asset management sytem.							
		*/
		enGetUniqueAssetLocation		= kWorkgroupPrefix + 13,
		
		/** Checks in a list of assets. This service is useful when it is faster for an asset management system
		    to check in multiple assets in batch rather than one at a time.
		    
		    Input IAMServiceData parameters:
		    
				IAMService Data Identifier		    | Data Type					 |	Notes
			   -------------------------------------+----------------------------+------------------------------------
				IAMService::enTargetAsset(implicit) | IAMServiceData::IDFileList | IDFiles to checkin.		    
				IAMService::enCheckInComment		| PMString					 | Empty PMString signifies a blank comment.

			Output IAMServiceData parameters: None.
		*/
		enBatchCheckIn					= kWorkgroupPrefix + 14,
		
		/** Performs any follow-up actions needed after an enCheckIn service completes.

			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.		
		*/
		enAfterCheckIn					= kWorkgroupPrefix + 15,
		
		/** Performs any actions needed before an enCheckIn service is executed.

			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.		
		*/	
		enBeforeCheckOut				= kWorkgroupPrefix + 16,
		
		/** Performs any follow-up actions needed after an enCancelCheckout service completes.

			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.		
		*/		
		enAfterCancelCheckOut			= kWorkgroupPrefix + 17,
		
		/** The service updates the IDataLink for a link to a managed asset. The service is useful
			for updating links to assets that have been moved or renamed.
			
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.			
		*/
		enUpdateLinkLocation			= kWorkgroupPrefix + 18,
		
		/** This service relinks a story page item. Used for porting from IInCopyBridgeCmdSuite::Relink.
		
			Input IAMServiceData parameters: None.
			Output IAMServiceData parameters: None.		
		*/
		enRelink						= kWorkgroupPrefix + 19,
		
		/** This service unembeds story content to an external asset location. Used for porting from
			IInCopyBridgeCmdSuite::Relink.

			Input IAMServiceData parameters:
			
				IAMService Data Identifier		 | Data Type			 | Notes
			   ----------------------------------+-----------------------+--------------------------------------
				IAMService::enCommandUndoability | ICommand::Undoability | Applies to any ICommands executed by the service
				IAMService::enUIFlags			 | UIFlags				 | UI permitted for use by the service.
			
			Output IAMServiceData parameters: None.			
		*/
		enUnembed						= kWorkgroupPrefix + 20,

		/** This service stores checkin data for later retrieval. Useful for situations in which
			it is impractical to pass checkin data parameters explicitly throughout the APIs.
			
			Input IAMServiceData parameters: IAMService::enTargetAsset IDFile & IAMService::enCheckInComment PMString
			Output IAMServiceData parameters: None.				
		*/
		enStoreCheckInData				= kWorkgroupPrefix + 21,
		
		/** This service retrieves checkin data that was previously stored.
		
			Input IAMServiceData parameters: IAMService::enTargetAsset IDFile.
			Output IAMServiceData parameters: IAMService::enCheckInComment PMString.		
		*/
		enRetrieveCheckInData			= kWorkgroupPrefix + 22
		
	}; // end AssetService enum
	
	
	/** The IAMServiceProvider::AssetHints class has cached information about a file-based asset.
		The following information is available:
		
			kFileType is the SysOSType;
			kFileExtension is a PMString containing the file extension.
			
		AssetHints are usually accessed through a pointer (see the IAMServiceProvider::CanService method).
		Example:
		
			PMString theExtension = hints->kFileExtension;
			
	*/
	class AssetHints
	{
		public:
		AssetHints() :
			kFileType(0),
			kFileExtension(PMString(""))
			{}
		AssetHints( SysOSType sysOSType, PMString & fileExtension ) :
			kFileType(sysOSType),
			kFileExtension(fileExtension)
			{}
		AssetHints( const AssetHints & hints ) :
			kFileType(hints.kFileType),
			kFileExtension(hints.kFileExtension)
			{}
		AssetHints& operator = (const AssetHints &copy)
			{ kFileType = copy.kFileType; kFileExtension = copy.kFileExtension; return *this; }				
		SysOSType kFileType;
		PMString kFileExtension;
	}; // end AssetHints

	//////////////////////////// IAMServiceProvider methods //////////////////////////// 

	/** This form of the CanService method tests if the service provider can service (owns) a specified
		file; i.e., if the file can be handled by the asset management system. If the asset management
		system does not support files, this method should always return kFalse (the second form of this
		method can be used to determine ownership).
		@param file is the IDFile to test for ownership.
		@param hints contain more information about the file (input parameter).
		@return kTrue if the service provider recognizes the file; kFalse otherwise.
	*/
	virtual bool16 CanService( const IDFile & file, const IAMServiceProvider::AssetHints * hints = nil ) = 0;

	/** This for of the CanService method tests if the service provider can service an IManageableAsset
		instance.
		@param asset is a valid pointer to an IManageableAsset interface.
		@return kTrue if the service provider recognizes the IManageableAsset; kFalse otherwise.
	*/
	virtual bool16 CanService( const IManageableAsset * asset ) = 0;

	/** The CanUpdateScriptedAssetData method tests if the asset management service provider recognizes
		the specified script data for the purpose of updating it as necessary. This method is used in
		conjunction with the IAMServiceProvider::UpdateScriptedAssetData method.
		@param assetRef is the UIDRef of a boss that aggregates the IManageableAsset (IID_IMANAGEABLEASSET)
		interface.
		@param scriptString is the IScriptRequestData converted to a PMString.
		@param scriptID is the script data item's ScriptID.
		@return kTrue if the service provider recognizes the script data; kFalse otherwise.
	*/	
	virtual bool16 CanUpdateScriptedAssetData( UIDRef assetRef, const PMString & scriptString, int32 scriptID ) = 0;
	
	/** Retrieves the ILinkResource::ResourceId for a specified file.
		@param inFile a resource IDFile.
		@param outResourceId is set to the ResourceId if available.
		@return kTrue if outResourceId was set; kFalse otherwise.
	*/
	virtual bool16 GetLinkResourceId( const IDFile & inFile, ILinkResource::ResourceId & outResourceId ) = 0;
	
	/** The GetService method obtains an instance of an IAMService interface for a specified
		AssetService id. The IAMService pointer is returned with a refcount of 1; the caller of
		this method is responsible for releasing the IAMService pointer. Suggested usage:
		
			InterfacePtr<IAMService> pService( myAMServiceProvider->GetService( myServiceID ) );
			
		The advantage of the suggested usage is that the IAMService pointer will be released
		automatically when pService goes out of scope.
		
		This method is typically implemented as a switch statement as in the following example.
		
		Implementation example:
		
			IAMService* InCopyAMServiceProvider::GetService( int32 assetServiceID )
			{
				IAMService * service(nil);
				switch ( assetServiceID )
				{
					case IAMServiceProvider::enInitialize :	
						service = ::CreateObject2<IAMService>( kICInitializeStoryServiceBoss );					
						break;			
					case IAMServiceProvider::enCheckOut :
						service = (IAMService*)::CreateObject( kICCheckOutServiceBoss, IID_IAMSERVICE );
						break;
					case IAMServiceProvider::enCancelCheckOut :
					case IAMServiceProvider::enRevert :
						service = (IAMService*)::CreateObject( kICCancelCheckOutServiceBoss, IID_IAMSERVICE );
						break;
					case IAMServiceProvider::enCheckIn :
						service = (IAMService*)::CreateObject( kICCheckInServiceBoss, IID_IAMSERVICE );
						break;					
				}	
				return service;
			} // end InCopyAMServiceProvider::GetService()		
		
		@param assetServiceID a 32-bit service identifier supported by the IAMServiceProvider
			implementation. This need not be a predefined IAMServiceProvider::AssetService identifier
			as long as it is unique. 
		@return a valid IAMService pointer if an implementation exists, othersize returns nil.
	*/
	virtual IAMService* GetService( int32 assetServiceID ) = 0;

	/** The Init method prepares the asset management service provider for use. This method may be
		called any number of times, but it must be called at least once before calling any other method
		on the service provider.
		@return kSuccess if initialization succeeded or if already successfully initialized; kFalse if
			the service provider is unavailable.
	*/	
	virtual ErrorCode Init() = 0;
	
	/** This method tests if a file is a temporary file created by the asset management system from an
		older version of an asset. The tempory file is typically used for viewing past versions. Note that
		this was originally a Version Cue concept, but have relevance to other asset management systems.
		@param file is an IDFile containing a path to an existing temporary file.
		@return kTrue if the file is a temporary file of an older version of an asset; kFalse otherwise.
	*/
	virtual bool16 IsTemporaryVersion( const IDFile & file ) = 0;
	
	/** This method tests if an asset is versioned; that is, it tests if there are historical versions
		of an asset.
		@param file is an IDFile containing a valid file path.
		@return kTrue if the IDFile represents a versioned asset; kFalse otherwise.
	*/	
	virtual bool16 IsVersioned( const IDFile & file ) = 0;
	
	/** The OverrideOpenFlags method allows the asset management service provider to override the file open
		flags for an InDesign document asset.
		@param file is an IDFile containing a path to an existing InDesign document file.
		@param inOpenFlags are the default IOpenFileCmdData::OpenFlags.
		@return the inOpenFlags unless the file must be opened in a different way. For example, a temporary version
			file (see IsTemporaryVersion() method) should be opened with the IOpenFileCmdData::kOpenCopy flag.
	*/	
	virtual IOpenFileCmdData::OpenFlags OverrideOpenFlags( const IDFile & file, IOpenFileCmdData::OpenFlags inOpenFlags ) = 0;
	
	/** The UpdateScriptedAssetData method modifies asset data from a scripting environment.
		@param assetRef is the UIDRef of a boss that aggregates the IManageableAsset (IID_IMANAGEABLEASSET)
			interface.
		@param scriptString is the IScriptRequestData converted to a PMString.
		@param scriptID is the script data item's ScriptID.
		@return kSuccess if the update succeeds; otherwise returns a failure error code.	
	*/
	virtual ErrorCode UpdateScriptedAssetData( UIDRef assetRef, const PMString & scriptString, int32 scriptID ) = 0;
	
	/** The IsWriteable method tests if it is currently safe to write to an asset file. Since writeability is
		transient, this method should be called immediately before writing. This method is useful when an
		IAMLockable interface is unavailable for determining writeability, as when determining if a text frame can
		be exported as a story asset over an existing story file. 
		@param assetFile has a valid path.
		@return kTrue if the assetFile can be legally overwritten or if the assetFile does not yet exist. Caution
		should be used in returning kTrue, especially for LiveEdit assets, since a file may not be overwritten while
		it is in use by another app or story text frame. It is up to the implementaton of this method to honor the
		LiveEdit workflow. The default return value should be kFalse.
		@see IAMLockable.
	*/
	virtual bool16 IsWriteable( const IDFile & assetFile ) = 0;
	
	/** This method retrieves available lock data associated with a locked file-based asset.
		@param assetFile represents an existing file-based asset.
		@param outLockData is populated with the relevant IManagedStatus::WGStatusType data strings.
		@param uiFlags controls UI that may be displayed in determining the lock data.
		@return kTrue if the asset is locked and data is available; kFalse otherwise.
		@see IManagedStatus.
	*/
	virtual bool16 GetLockData( const IDFile & assetFile, IManagedStatus::StatusStringTable & outLockData, UIFlags uiFlags = kFullUI ) = 0;
	
}; // end IAMServiceProvider interface

#endif // __IAMSERVICEPROVIDER__
