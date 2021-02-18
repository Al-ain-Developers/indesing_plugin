//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMSPManager.h $
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
#ifndef __IAMSPMANAGER__
#define __IAMSPMANAGER__

#include "IPMUnknown.h"
#include "IAMServiceProvider.h"
#include "IAMSystemProvider.h"
#include "IManageableAsset.h"

#include "IDFile.h"

#include <vector>

class IAssetMonitor;
class IAMUIServiceProvider;
class IDFile;
class IAMUIEnablementRules;


/** The IAMSPManager interface accesses the AMSP (asset management system provider) manager. The
	AMSP manager maintains knowledge of IAMSystemProviders and their service, UI, and monitoring
	components. This interface is the starting point for obtaining access to an asset management
	system. IAMSPManager is obtained from the session as follows:
	
		InterfacePtr<IAMSPManager> iAMSPManager( GetExecutionContextSession(), UseDefaultIID() );
		
	In order to be recognized by the AMSP manager, an asset management system provider's boss must
	subclass the kAMSPBoss (see workgroupid.h).
	
	Example:
	
	This is a simple asset management system provider that has an asset management service provider
	(IAMServiceProvider) for providing IAMServices.
	
		Class
		{
			kMyAMSPBoss,
			kAMSPBoss,
			{	
				IID_IAMSYSTEMPROVIDER,		kMyAMSPImpl,	
				IID_IAMSERVICEPROVIDER,		kMyAMServiceProviderImpl,
			}
		},
		
	@see IAMSystemProvider.
	@see IAMServiceProvider.
	@see IAMService.
*/	
class IAMSPManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSPMANAGER };

	typedef std::vector<IAssetMonitor*> AssetMonitorPtrList;
	typedef std::vector<UIDRef> UIDRefList;
	
	/** The BindAsset method attaches (binds) asset management components to any boss (model object) that
		aggregates the IManageableAsset interface. Binding must be done before monitoring or performing
		any asset management services on the IManageableAsset. Any IManageableAsset instance that is bound
		using this method must also be unbound using IAMSPManager::UnbindAsset(). An IManageableAsset instance
		may be bound any number of times. It is not necessary to call UnbindAsset() before calling BindAsset().
		A model object must be rebound whenever its association with an asset changes. For example, when a kDocBoss
		is written as part of the Save As command, it does not get recreated, but its location changes, so it
		must be bound to the new location.
		@param pAsset is a valid pointer to an IManageableAsset interface on a model object boss.
		@param assetType is one of the predefined IManageableAsset::AssetTypes. Attempting to bind an
			IManageableAsset of type IManageableAsset::enLinked will fail if the link's IDataBase is
			not associated with an IDocument in the app's IDocumentList. 
		@param file is an IDFile with a valid path or an empty path. This argument is ignored unless the
			assetType is IManageableAsset::enDocument. Specify this argument when binding a document boss
			associated with an existing file. Omit this argument (or specify an IDFile with an empty path) when
			binding a new document that has not yet been saved.
		@return kSuccess if the asset was bound successfully; otherwise returns a failure ErrorCode if binding
			could not be done.
		@see UnbindAsset.
		@see IManageableAsset.
	*/
	virtual ErrorCode BindAsset( IManageableAsset * pAsset, IManageableAsset::AssetType assetType, const IDFile & file = IDFile() ) = 0;

	/** The UnbindAsset method removes asset management components that are bound to an asset. Before destroying
		any IManageableAsset instance, call this method if the instance was previously bound using BindAsset().
		Failure to call UnbindAsset() for a bound IManageableAsset may result in unreleased resources when a document
		is closed.
		@param pAsset is a valid pointer to an IManageableAsset interface on a model object boss.
		@return kSuccess if the asset was unbound successfully; otherwise returns a failure ErrorCode.
		@see BindAsset.
		@see IManageableAsset.
	*/
	virtual ErrorCode UnbindAsset( IManageableAsset * pAsset ) = 0;

	/** This method retrieves the number of IAMSystemProvider instances that are currently registered with
		the AMSP manager.
		@return int32 greater than or equal to zero.
	*/
	virtual int32 GetNumberOfAMSystemProviders() = 0;
	
	/** This method retrieves the IAMSystemProvider for a specified index. 
	
		Example usage:
	
			InterfacePtr<IAMSystemProvider> amsp( iAMSPManager->GetNthSystemProvider( i ), UseDefaultIID() );
		
		@param n is an integer >= 0.
		@return pointer to an IAMSystemProvider or nil if n is out of bounds.
		@see IAMSystemProvider.
	*/
	virtual IAMSystemProvider* GetNthSystemProvider( int32 n ) = 0;
	
	/** This method retrieves a pointer to the IAMSystemProvider instance for an AMSP boss.
		@param amspClassID is the ClassID of a boss that subclasses kAMSPBoss.
		@return pointer to an IAMSystemProvider or nil if amspClassID is invalid orthe boss
			does not have an IAMSystemProvider interface.
		@see IAMSystemProvider.
	*/
	virtual IAMSystemProvider* GetSystemProvider( ClassID amspClassID ) = 0;
	
	/** This method retrieves the ClassID of the asset management system provider for an asset management
		service provider (IAMServiceProvider).
		@param amServiceProviderClassID is the ClassID of a boss that aggregates IID_IAMSERVICEPROVIDER.
		@return the ClassID of a boss that aggregates IID_IAMSYSTEMPROVIDER.
		@see IAMSystemProvider.
		@see IAMServiceProvider.
	*/
	virtual ClassID GetSystemProviderClassID( ClassID amServiceProviderClassID ) = 0;
	
	/** This method retrieves the IAMServiceProvider interface for a specific asset management system
		provider (AMSP) implementation.
		@param amServiceProviderClassID is the ClassID of an existing AMSP.
		@return a pointer to an IAMServiceProvider, or nil if the specified ClassID is invalid or the
			AMSP is disabled.
		@see IAMServiceProvider.
	*/
	virtual IAMServiceProvider* GetServiceProvider( ClassID amServiceProviderClassID ) = 0;
	
	/** This method retrieves a list of all of the IAssetMonitors.
		@param outList is populated with valid pointers to all of the IAssetMonitors registered with the
			AMSP manager. The pointers are guaranteed to be valid for the duration of the session.
		@return the number of IAssetMonitors in the list.
		@see IAssetMonitor.
	*/	
	virtual int32 GetAllAssetMonitors( IAMSPManager::AssetMonitorPtrList & outList ) = 0;
	
	/** This method retrieves the IAMUIServiceProvider for an asset.
		@param asset is a valid pointer to a bound IManageableAsset or nil. If nil, this method
			returns the first enabled IAMUIServiceProvider available.
		@return a valid pointer to an IAMUIServiceProvider if found; otherwise returns nil.
		@see IAMUIServiceProvider.
	*/
	virtual IAMUIServiceProvider* GetUIServiceProvider( IManageableAsset * asset = nil ) = 0;
	
	/** This method retrieves the IAMUIServiceProvider that offers a particular UI service.
		@param asset is a valid pointer to a bound IManageableAsset.
		@param serviceID specifies the IAMUIService service identifier.
		@return a valid pointer to an IAMUIServiceProvider or nil if no UI service provider can be
			found that offers the service.
	*/
	virtual IAMUIServiceProvider* GetUIServiceProvider( IManageableAsset * asset, int32 serviceID ) = 0;
	
	/** This method retrieves the IAMUIServiceProvider that offers a particular UI service that is
		compatible with an asset file.
		@param file is an IDFile with a valid path to an existing asset.
		@param serviceID specifies the IAMUIService service identifier.
		@return a valid pointer to the first IAMUIServiceProvider found that can handle the file. Returns nil
			if no UI service provider can be found that offers the service.
	*/	
	virtual IAMUIServiceProvider* GetUIServiceProvider( const IDFile & file, int32 serviceID ) = 0;
	
	/** This method retrieves the IAMUIServiceProvider that offers a particular UI service that is
		compatible with a list of assets. This method is used primarily to display UI for batch
		checkin comments.
		@param assetList is a list of UIDRefs for bound IManageableAssets.
		@param serviceID specifies the IAMUIService service identifier.
		@return a valid pointer to the first IAMUIServiceProvider found that can handle the list. Returns nil
			if no UI service provider can be found that offers the service.
	*/		
	virtual IAMUIServiceProvider* GetUIServiceProvider( const IAMSPManager::UIDRefList & assetList, int32 serviceID ) = 0;

	/** This method retrieves the IAMServiceProvider for a file.
		@param file is an IDFile with a valid path to an existing asset. 
		@return a pointer to the IAMServiceProvider that recognizes the file.
	*/
	virtual IAMServiceProvider* QueryServiceProvider( const IDFile & file ) = 0;
	
	/** This method notifies the underlying asset management systems that warning dialogs are allowed.
	*/
	virtual void ShowAllWarningDialogs() = 0;
	
	/** This method retrieves the IAMUIEnablementRules for a specific IManageableAsset. The enablement
		rules are used to enable or disable UI widgets for an asset.
		@param asset is a valid pointer to a bound IManageableAsset.
		@return a valid pointer to the asset's IAMUIEnablementRules or nil if not found.
		@see IAMUIEnablementRules.
	*/
	virtual IAMUIEnablementRules* GetUIEnablementRules( IManageableAsset * asset ) = 0;
		
	/** INTERNAL USE ONLY. This method tests if authentication UI is enabled. 
		@return kTrue if authentication UI is enable; kFalse otherwise.
	*/
	virtual bool16 IsAuthenticationUIEnabled() const = 0;
	
	/** INTERNAL USE ONLY. This method enables or disables authentication UI.
		@param enable kTrue enables authentication UI; kFalse disables it.
		@return kTrue if authentication UI is enabled; kFalse otherwise.
	*/
	virtual bool16 EnableAuthenticationUI( bool16 enable = kTrue ) const = 0;	
};

#endif // __IAMSPMANAGER__
