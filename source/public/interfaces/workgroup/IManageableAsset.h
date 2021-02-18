//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IManageableAsset.h $
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
#ifndef __IMANAGEABLEASSET__
#define __IMANAGEABLEASSET__

#include "IPMUnknown.h"
#include "workgroupid.h"
#include "IAMLockable.h"
#include "IAssetStateMachine.h"
#include "IManagedStatus.h"

class IAssetMonitor;
class IAMSystemProvider;


/** The IManageableAsset interface represents a managed asset. A "managed asset" is one that is under
	the control of an asset management system (for example, Version Cue).
	
	The IManageableAsset interface is added to any boss whose content can reside in an asset management
	system. InDesign documents may reside in an asset managment system, and IDataLinks may refer to content
	in an asset management system, so both the kDocBoss and the kDataLinkBoss aggregate this interface.
	
	The default implementation for this interface is kManageableAssetImpl; for most applications, the
	default implementation can be used rather than creating a new implementation. 
*/	
class IManageableAsset : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMANAGEABLEASSET };
	
	/** The AssetType defines how an IManageableAsset is used within InDesign. */
	enum AssetType
	{
		/** No type has been assigned */
		enUndefined			= 0,
		/** Identifies a document asset */
		enDocument			= 1,
		/** Identifies a linked asset */
		enLinked			= 2,
		/** Identifies an unmanaged instance; asset management capability will not be bound to it. */
		enUnmanageable		= 3
	};

	/** This method retrieves the IAssetMonitor bound to this asset.
		@return valid pointer to an IAssetMonitor or nil if no asset monitor was found that could monitor
		the asset.
	*/
	virtual IAssetMonitor * GetAssetMonitor() = 0;
	
	/** This method retrieves the asset URL if it has been set.
		@param outURL is PMString to be populated with the URL.
		@return kTrue if there is a URL, kFalse otherwise.
		@see IManageableAsset::SetAssetURL.
	*/
	virtual bool16 GetAssetURL( PMString & outURL ) = 0;
	
	/** This method retrieves the IAMLockable instance for this IManageableAsset instance.
		@return a valid pointer to an IAMLockable instance or nil. Returning nil indicates that
		this asset is not lockable.
		@see IAMLockable.
	*/
	virtual IAMLockable * GetLockable() = 0;
			
	/** This method applies only to a file-based asset. Retrieves the IDFile of the location that
		the asset was read from. The IDFile may be for a temporary file, so this method should
		never be used to obtain the file to write to; use GetWriteFile() instead.
		@param file is set to the IDFile that the asset was read from.
		@return kTrue if the file param was set to a valid path.
		@see IManageableAsset::GetWriteFile.
	*/
	virtual bool16 GetReadFile( IDFile & file ) = 0;

	/** This method retrieves the ClassID for the IAMServiceProvider for this asset that was set during
		binding.
		@return kInvalidClass until a service provider is bound to this instance. After binding,
			returns the IAMServiceProvider that recognizes this asset.
		@see IAMSPManager::BindAsset.	
	*/		
	virtual ClassID GetServiceProviderClass() const = 0;

	/** This method retrieves the IAssetStateMachine that can process IManagedStatus changes for the
		asset.
		@return a valid pointer to an IAssetStateMachine instance or nil if not set.
	*/
	virtual IAssetStateMachine * GetStateMachine() = 0;
			
	/** This method retrieves the IManagedStatus instance for the asset. May legally return nil if
		the AMSP implementation does not support status monitoring of assets.
		@return a valid pointer to an IManagedStatus instance or nil.
		@see IManagedStatus.
	*/	
	virtual IManagedStatus * GetStatus() = 0;

	/** This method retrieves the AssetType that was set during binding.
		@return one of the predefined AssetTypes.
		@see IAMSPManager::BindAsset. 
	*/
	virtual IManageableAsset::AssetType GetType() = 0;
		
	/** This method applies only to a file-based asset. Retrieves the IDFile of the location that
		the asset can be written to. Only writeable assets like documents and stories have a write
		file.
		@param file is set to the IDFile of the write file.
		@return kTrue if the file param was set to a valid path.
	*/	
	virtual bool16 GetWriteFile( IDFile & file ) = 0;

	/** This method tests if this IManageable asset represents versioned content. "Versioned" in this
		case refers to historical versions rather than, say, different language versions.
		@return kTrue if versioned; kFalse otherwise.
		@see IManageableAsset::SetHasVersionedContent.
	*/	
	virtual bool16 HasVersionedContent() const = 0;

	/** This method tests if this IManageableAsset instance has been properly bound and can be used
		successfully in workgroup API calls.
		@return kTrue if bound; kFalse if not.
		@see IAMSPManager::BindAsset.
	*/	
	virtual bool16 IsBound() const = 0;
			
	/** This method applies only to a file-based asset. It tests if the IManageableAsset instance
		was	created from a temporary file supplied by the asset management system. For Version Cue
		assets, this method returns kTrue for an IManageableAsset representing an historical version.
		@return kTrue if temporary asset file; fFalse otherwise.
	*/
	virtual bool16 IsTemporary() = 0;

	/** This method tests if this asset is versioned; i.e., tests if the asset maintains a history
		of revisions. This method is similar to the IManageableAsset::HasVersionedContent method;
		however, this method will return kFalse for an IManageableAsset::enLinked asset (even when
		linked to versioned content) unless the link itself is versioned. For enDocument assets,
		this method returns the same as the HasVersionedContent method.
		@return kTrue if versioned; kFalse if not.
		@see IManageableAsset::HasVersionedContent.
	*/ 
	virtual bool16 IsVersioned() const = 0;
	
	/** This method sets the current IAssetMonitor. The method is called during binding.
		@param assetMonitor is a valid pointer to an IAssetMonitor instance or nil.
		@see IAMSPManager::BindAsset.
	*/
	virtual void SetAssetMonitor( IAssetMonitor * assetMonitor ) = 0;
		
	/** This method sets the current URL for the asset.
		@parm url is a PMString with a valid URL.
	*/
	virtual void SetAssetURL( const PMString & url ) = 0;

	/** This method sets a flag indicating that a versioned asset (content) is associated with this
		IManageableAsset instance. This method is typically called by an IAMServiceProvider::enInitialize
		service implementation.
		@param b is kTrue if versioned content; kFalse if not.
		@see IManageableAsset::HasVersionedContent.
		@see IAMServiceProvider.
	*/	
	virtual void SetHasVersionedContent( bool16 b ) = 0;

	/** This method flags that the IManageableAsset instance has been bound. This method is called during
		execution of the IAMSPManager::BindAsset method. An instance must be bound before it can be used
		in IAMService requests, monitored, etc.
		@param b is kTrue if bound; kFalse if not.
		@see IAMSPManager::BindAsset.
	*/
	virtual void SetIsBound( bool16 b = kTrue ) = 0;

	/** This method sets a flag indicating that the IManageableAsset is versioned. This method is
		typically called by an IAMServiceProvider::enInitialize service implementation. Do not call this
		method with kTrue for a enLinked assets unless the link itself is versioned; use SetHasVersionedContent
		instead.
		@param b is kTrue if versioned; kFalse if not.
	*/
	virtual void SetIsVersioned( bool16 b ) = 0;

	/** This method sets the IAMLockable instance for this IManageableAsset instance. An IAMLockable instance
		should be set for story assets in order to participate correctly in the LiveEdit workflow.
		@param lock is a valid pointer to an IAMLockable instance or nil if the asset is not lockable. When
			non-nil, the pointer is assumed to be valid for the life of the IManageableAsset instance unless
			reset by another call to this method.
	*/
	virtual void SetLockable( IAMLockable * lock ) = 0;
				
	/** This method applies only to a file-based asset. Sets the IDFile for the location that the asset
		was read from. This method is typically called within the IAMServiceProvider::enInitialize
		service.
		@param file an IDFile with a valid path to a file in the asset management system's local asset
			cache (for Version Cue assets, this is the local replica file in a Version Cue project folder).
		@see IAMServiceProvider.
	*/
	virtual void SetReadFile( const IDFile & file ) = 0;

	/** This method is called during binding provided that an IAMServiceProvider is found that recognizes
		the asset.
		@param id is the ClassID of the IAMServiceProvider.
		@see IAMSPManager::BindAsset.
		@see IAMServiceProvider.
	*/
	virtual void SetServiceProviderClass( ClassID id ) = 0;

	/** This method sets the IAssetStateMachine instance that can process IManagedStatus changes for the asset.
		This method is typically called within the IAMServiceProvider::enInitialize service.
		@param sm is a valid pointer to an IAssetStateMachine instance or nil. The non-nil pointer is assumed to be
			valid for the life of this IManageableAsset instance unless reset with another call to this method.
	*/	
	virtual void SetStateMachine( IAssetStateMachine * sm ) = 0;
	
	/** This method sets the IManagedStatus instance for the IManageableAsset. An IManagedStatus instance
		may not be set on more than one IManageableAsset instance; that is, two IManageableAsset instances
		may not share an IManagedStatus instance.
		@param status is a valid pointer to an IManagedStatus instance or nil.
	*/
	virtual void SetStatus( IManagedStatus * status ) = 0;

	/** This method sets the AssetType. This method is called during binding.
		@param t is the AssetType.
		@see IAMSPManager::BindAsset.
	*/
	virtual void SetType( IManageableAsset::AssetType t ) = 0;
			
	/** This method applies only to a writeable, file-based asset. Sets the IDFile for the location
		that the asset model changes can be written to. This method is typically called within the
		IAMServiceProvider::enInitialize service.
		@param file an IDFile with a valid path to a file in the asset management system's local asset
			cache (for Version Cue assets, this is the local replica file in a Version Cue project folder).
		@see IAMServiceProvider.	
	*/	
	virtual void SetWriteFile( const IDFile & file ) = 0;
		
}; // end IManageableAsset interface

#endif // __IMANAGEABLEASSET__
