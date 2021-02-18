//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMService.h $
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
#ifndef __IAMSERVICE__
#define __IAMSERVICE__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IManageableAsset;

/** The IAMService interface represents an asset management service. An implementation of
	this interface should perform a specific, atomic service that either succeeds or has
	no affect whatsoever. Each asset management service has unique AssetService number. It
	is the responsibility of the IAMServiceProvider to map the AssetService number to the
	actual service implementation.
	
	The typical implementation of a service aggregates IID_IAMSERVICE on a separate
	service boss. For exchanging service data parameters between the service and the caller,
	also aggregate the IID_IAMSERVICEDATA (IAMServiceData) interface. For most services,
	the standard implementation of IAMServiceData (kAMServiceDataImpl) can be used.
	
	Example:
	
	The following example defines an IAMServiceProvider::enCheckOut service that uses the
	Version Cue API to do the checkout operation.
	
	<pre>
		Class
		{
			kVCCheckOutServiceBoss,
			kInvalidClass,
			{
				IID_IAMSERVICE,		kVCCheckOutServiceImpl,
				IID_IAMSERVICEDATA, kAMServiceDataImpl, // standard impl
				IID_IVCUTILS,		kVCUtilsImpl,		// utils specific to Version Cue
			}
		},
	</pre>
	Example:
	
	The following sample code invokes the above enCheckOut service. Assume that
	assetRef is a valid UIDRef and uiFlags are standard UIFlags passed in to this code.
	
	<pre>
		ErrorCode status(kFailure);
		InterfacePtr<IManageableAsset> asset( assetRef, UseDefaultIID() );
		InterfacePtr<IAMSPManager> iAMSPManager( GetExecutionContextSession(), UseDefaultIID() );
		if ( asset && asset->IsBound() && iAMSPManager )
		{
			InterfacePtr<IAMServiceProvider> amsp( iAMSPManager->GetServiceProvider( 
				asset->GetServiceProviderClass() ), UseDefaultIID() );
			if ( amsp )
			{
				status = kSuccess; // always assume kSuccess if no service is available
				InterfacePtr<IAMService> checkOutService( amsp->GetService( IAMServiceProvider::enCheckOut ) );
				if ( checkOutService )
				{
					InterfacePtr<IAMServiceData> checkOutServiceData( checkOutService, UseDefaultIID() );
					if ( checkOutServiceData )
						checkOutServiceData->Set( IAMService::enUIFlags, uiFlags );
						
					status = checkOutService->Do( asset );
				}
			}
		}
	</pre>			
	@see IAMServiceProvider.
	@see IAMServiceData.
*/
class IAMService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSERVICE };

	/** Predefined IAMServiceData identifiers for data parameters passed to services
		(input parameter) or returned to the service requestor (output parameter).
		@see IAMServiceData.
		@see IAMServiceProvider for the data parameters and data types required by
			each predefined AssetService.
	*/
	enum
	{
		/** Default identifer. */
		enInvalid				= 0,
		
		/** Input parameter: the asset to perform the service on. */
		enTargetAsset			= kWorkgroupPrefix + 1,
		
		/** Input parameter: the CheckIn comment. */
		enCheckInComment		= kWorkgroupPrefix + 2,
		
		/** Input parameter: the ISaveAssetContent callback interface. */
		enContentSaver			= kWorkgroupPrefix + 3,
		
		/** Input parameter: the UIFlags permitted for the service. */
		enUIFlags				= kWorkgroupPrefix + 4,
		
		/** Output parameter: the unique asset location as return by the
			IAMServiceProvider::enGetUniqueAssetLocation service. */
		enUniqueAssetLocation	= kWorkgroupPrefix + 5,
		
		/** Input parameter: flag specifies use of stored asset management-specific
			data for an IDataLink. */
		enUseStoredData			= kWorkgroupPrefix + 6,
		
		/** Input parameter: user name to check out an asset to. */
		enCheckOutToUserName	= kWorkgroupPrefix + 7,
		
		/** Input parameter: flag specifies permission to override a lock during CheckIn. */
		enOverrideAuthority		= kWorkgroupPrefix + 8,
		
		/** Input parameter: asset save option during CheckIn. */
		enForceSave				= kWorkgroupPrefix + 9,
		
		/** Input parameter: the ICommand::Undoability permitted for any ICommands executed by the service. */
		enCommandUndoability	= kWorkgroupPrefix + 10,
		
		/** Input parameter: flag specifies whether or not to save a new version as part of a CheckIn. */
		enSaveVersion			= kWorkgroupPrefix + 11,
		
		/** Input parameter: identifies the model object associated with an asset. */
		enModelObject			= kWorkgroupPrefix + 12
	};
	
	/**
		The Do method executes the service. Unlike ICommands, services are executed by directly calling
		the Do() method. For convenience, facades may be used to set up service data, invoke the
		IAMService::Do() method and interpret the results.
		@param pAsset is a pointer to an IManageableAsset object that is the target of the service.
			This parameter is specified if the service target is a model boss that aggregates the
			IManageableAsset interface. Omit this parameter for other service targets; instead, set the
			target using the service's IAMServiceData interface.
		@see IAMServiceData.
		@see IManageableAsset.
		@see IWorkgroupFacade.
	*/
	virtual ErrorCode Do( IManageableAsset * pAsset = nil ) = 0;
	
	/**
		The VerifyContext method verifies that the service is allowed for the specified asset. It does
		not predict whether or not the service will execute successfully. This method is useful for
		enabling or disabling UI widgets that invoke the service. For example, VerifyContext() for a
		CheckIn service would verify that the asset is checked out.
		@param pAsset is a pointer to an IManageableAsset object that is the target of the service.
		@return kFalse only if it is known that the service should not be executed within the current
			context; otherwise, this method should return kTrue.
		@see IManageableAsset.
	*/
	virtual bool16 VerifyContext( IManageableAsset * pAsset = nil ) = 0;

}; // end IAMService interface

#endif // __IAMSERVICE__
