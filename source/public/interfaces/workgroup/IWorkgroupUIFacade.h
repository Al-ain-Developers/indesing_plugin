//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IWorkgroupUIFacade.h $
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
#ifndef __IWORKGROUPUIFACADE__
#define __IWORKGROUPUIFACADE__

#include "workgroupid.h"
#include "IPMUnknown.h"
#include "IAMUIService.h"
#include "IManagedStatus.h"
#include "IAMUIEnablementRules.h"
#include "Utils.h"

class IDFile;
class ILink;
class IManageableAsset;

/** The IWorkgroupUIFacade provides high-level access to the public AMSP interfaces for displaying UI. Suggested usage:

		Utils<IWorkgroupUIFacade>()->method( params,... );
*/
class IWorkgroupUIFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWORKGROUPUIFACADE };
	
	/** This method invokes a IAMUIServiceProvider::enConflictAlert service.
		@param assetRef is a UIDRef for an IManageableAsset.
		@return the followup action as defined for IAMUIServiceProvider::enConflictAlert.
		@see IAMUIServiceProvider.
	*/
	virtual IAMUIService::FollowupAction DoConflictAlert( UIDRef assetRef ) = 0;

	/** This method invokes an IAMUIServiceProvider::enGetBatchVersionComments service to get a single
		checkin comment for a list of UIDRefs.
		@param inAssetList is a UIDList of UIDRef for IManageableAssets.
		@param outCheckinComment is populated with the comment text (empty string is a valid blank comment).
		@return the followup action as defined for IAMUIServiceProvider::enGetBatchVersionComments.
		@see IAMUIServiceProvider.
	*/
	virtual IAMUIService::FollowupAction DoGetBatchVersionComments( UIDList & inAssetList, PMString & outCheckinComment ) = 0;	

	/** This method invokes an IAMUIServiceProvider::enGetBatchVersionComments service to get a single
		checkin comment for the files in a folder. This is an alternative way to get batch version
		comments when individual asset UIDRefs do not exist or asset files have not yet been created.
		@param infolder is an IDFile with a valid path to a folder.
		@param numberOfAssets is the number of asset files to check in.
		@param outCheckinComment is populated with the comment text (empty string is a valid blank comment).
		@return the followup action as defined for IAMUIServiceProvider::enGetBatchVersionComments.
		@see IAMUIServiceProvider.		
	*/
	virtual IAMUIService::FollowupAction DoGetBatchVersionComments( const IDFile & inFolder, int32 numberOfAssets, PMString & outCheckinComment ) = 0;
	
	/** This method invokes an IAMUIServiceProvider::enGetVersionComments service to get checkin comments for
		a single asset.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param outCheckinComment is populated with the comment text (empty string is a valid blank comment).
		@return the followup action as defined for IAMUIServiceProvider::enGetVersionComments.
		@see IAMUIServiceProvider.		
	*/
	virtual IAMUIService::FollowupAction DoGetVersionComments( UIDRef assetRef, PMString & outCheckinComment ) = 0;	

	/** This method invokes an IAMUIServiceProvider::enRevertAlert service.
		@param assetRef is a UIDRef for an IManageableAsset.
		@return the followup action as defined for IAMUIServiceProvider::enRevertAlert.
		@see IAMUIServiceProvider.		
	*/
	virtual IAMUIService::FollowupAction DoRevertAlert( UIDRef assetRef ) = 0;

	/** This method invokes an IAMUIServiceProvider::enSaveACopyDialog service.
		@param inCopyFile is an IDFile with the default copy filename.
		@param inUseSystemDefaultDir if kTrue, initialize the dialog to the system default directory.
		@param outSaveFile is the IDFile to save to.
		@param outSaveAsStationery is the save option.
		@return the followup action as defined for IAMUIServiceProvider::enSaveACopyDialog.
	*/
	virtual IAMUIService::FollowupAction DoSaveACopyDialog( const IDFile & inCopyFile,
														bool16 inUseSystemDefaultDir,
														IDFile & outSaveFile,
														bool16 & outSaveAsStationery ) = 0;		

	/** This method invokes an IAMUIServiceProvider::enSaveAlert service.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param docName is the document name to place in the alert message.
		@param allowCancel displays a Cancel button when kTrue.
		@return the followup action as defined for IAMUIServiceProvider::enSaveAlert.
		@see IAMUIServiceProvider.		
	*/
	virtual IAMUIService::FollowupAction DoSaveAlert( UIDRef assetRef, const PMString & docName, bool16 allowCancel ) = 0;

	/** This method invokes an IAMUIServiceProvider::enSaveAsDialog service.
		@param assetRef is a UIDRef for the IManageableAsset to be saved.
		@param inDefaultFile initializes the dialog to this file path.
		@param inUseSystemDefaultDir if kTrue, initialize the dialog to the system default directory.
		@param outSaveFile is the IDFile to save to.
		@param outSaveAsStationery is the save option.
		@return the followup action as defined for IAMUIServiceProvider::enSaveAsDialog.
	*/
	virtual IAMUIService::FollowupAction DoSaveAsDialog( UIDRef assetRef,
														const IDFile & inDefaultFile,
														bool16 inUseSystemDefaultDir,
														IDFile & outSaveFile,
														bool16 & outSaveAsStationery ) = 0;	
												
	/** This method invokes an IAMUIServiceProvider::enSaveMultiLinkAlert service.
		@param inAssetList is a list of UIDRefs for IManageableAssets.
		@return the followup action as defined for IAMUIServiceProvider::enSaveMultiLinkAlert.
		@see IAMUIServiceProvider.		
	*/
	virtual IAMUIService::FollowupAction DoSaveMultipleLinkAlert( UIDList & inAssetList ) = 0;

	/** This method retrieves the IManagedStatus display icon for an IManageableAsset.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param statusType is a predefined IManagedStatus::WGStatusType or other unique identifier.
		@return a RsrcID or 0 if statusType not found.
		@see IManagedStatus.
	*/
	virtual PMRsrcID GetStatusIconID( UIDRef assetRef, int32 statusType ) = 0;
	
	/** This method retrieves the IManagedStatus status display string for an IManageableAsset.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param statusType is a predefined IManagedStatus::WGStatusType or other unique identifier.
		@param outString is populated with the status text.
		@return kTrue if statusType was found, kFalse otherwise.
		@see IManagedStatus.	
	*/
	virtual bool16 GetStatusString( UIDRef assetRef, int32 statusType, PMString & outString ) = 0;
	
	/** This method accesses the IAMUIEnablementRules for an IManageableAsset to determine if a UI
		command should be enabled.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param commandID is a predefined IAMUIEnablementRules::WGUICommandID or any unique integer.
		@return kTrue if enabled; kFalse if not.
		@see IAMUIEnablementRules.
	*/
	virtual bool16 IsCommandEnabled( UIDRef assetRef, int32 commandID ) = 0;	

	/** This method determines if a Link UI workgroup command should be enabled.
		@param iLink is a pointer to an ILink instance.
		@param commandID is a predefined IAMUIEnablementRules::WGUICommandID or any unique integer.
		@return kTrue if enabled; kFalse if not.
		@see IAMUIEnablementRules.
	*/
	virtual bool16 IsCommandEnabled( const ILink * iLink, int32 commandID ) = 0;
	
	/** This method invokes an IAMUIServiceProvider::enViewVersions service.
		@param assetRef is a UIDRef for an IManageableAsset.
		@param outTempVersion if the followup action is IAMUIService::enOpenFile, this is an IDFile
			with a valid path to a temporary file of the version to open for viewing.
		@return the followup action as defined for IAMUIServiceProvider::enViewVersions.
		@see IAMUIServiceProvider.		
	*/	
	virtual IAMUIService::FollowupAction ViewVersions( UIDRef assetRef, IDFile & outTempVersion ) = 0;
		
	/** This method invokes an IAMUIServiceProvider::enSaveAsDialog service.
		@param assetRef is a UIDRef for the IManageableAsset to be saved.
		@param inDefaultFile initializes the dialog to this file path.
		@param inUseSystemDefaultDir if kTrue, initialize the dialog to the system default directory.
		@param outSaveFile is the IDFile to save to.
		@param outSaveAsStationery is the save option.
		@param inShouldSuppressIDMLSave if kTrue, option of Save as IDML is suppressed
		@return the followup action as defined for IAMUIServiceProvider::enSaveAsDialog.
	*/
	virtual IAMUIService::FollowupAction DoSaveAsDialog2( UIDRef assetRef,
														const IDFile & inDefaultFile,
														bool16 inUseSystemDefaultDir,
														IDFile & outSaveFile,
														bool16 & outSaveAsStationery,
														bool16   inShouldSuppressIDMLSave = kFalse) = 0;
}; // end IWorkgroupUIFacade interface


#endif	// __IWORKGROUPUIFACADE__
