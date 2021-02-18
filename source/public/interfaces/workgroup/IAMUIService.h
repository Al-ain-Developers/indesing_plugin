//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMUIService.h $
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
#ifndef __IAMUISERVICE__
#define __IAMUISERVICE__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IManageableAsset;


/** The IAMUIService interface represents an asset management UI service. Typical UI services
	display alerts or query for user input such as checkin comments. Defining and using ui
	services is similar to defining and using IAMServices.
	
	Example:
	
	This is the ui service that displays the Adobe (Version Cue) Save Dialog. Note that the
	IID_IAMSERVICEDATA (IAMServiceData) interface is used to exchange data with a UI service.
	
		Class
		{
			kVCSaveDialogServiceBoss,
			kInvalidClass,
			{
				IID_IAMUISERVICE,	kVCSaveDialogServiceImpl,
				IID_IAMSERVICEDATA,	kAMServiceDataImpl,
			}
		},
		
*/
class IAMUIService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMUISERVICE };

	/** FollowupActions are user commands that must be performed after the UI closes.
		A UI service returns at most one FollowupAction.
	*/
	enum FollowupAction
	{
		/** No followup action required */
		enNone							= 0,
		
		/** Cancel the current operation */
		enCancel						= 1,
		
		/** Perform the default action */
		enDefaultAction					= 2,
		
		/** Save the document */
		enSave 							= kWorkgroupPrefix + 1,
		
		/** Save a new version of the document */
		enSaveVersion					= kWorkgroupPrefix + 2,
		
		/** Do not save (discard changes) */
		enDontSave						= kWorkgroupPrefix + 3,
		
		/** Discard model changes */
		enRevertDocument				= kWorkgroupPrefix + 4,
		
		/** Revert the document to the existing stored version */
		enRevertToLastVersion			= kWorkgroupPrefix + 5,
		
		/** Promote an older version to be the current version */
		enPromoteVersion				= kWorkgroupPrefix + 6,
		
		/** Open a file for viewing */
		enOpenFile						= kWorkgroupPrefix + 7,
		
		/** Discard model changes */
		enDiscardChanges				= kWorkgroupPrefix + 8,
		
		/** Continue editing an out-of-date document */
		enContinueEditing				= kWorkgroupPrefix + 9,
		
		/** Save model changes anyway */
		enOverride						= kWorkgroupPrefix + 10,
		
		/** Save model changes over current version */
		enOverrideAndSaveAVersion		= kWorkgroupPrefix + 11,
		
		/** Save to a new file location */
		enSaveToNewFile					= kWorkgroupPrefix + 12,
		
		/** Save a new version */
		enSaveAVersion					= kWorkgroupPrefix + 13,
		
		/** Close the current document */
		enCloseDocument					= kWorkgroupPrefix + 14,
		
		/** Recreate the document from the latest version. */
		enRecreateDocument				= kWorkgroupPrefix + 15,
		
		/** Save the document for previous version (IDML) */
		enSaveBackwards					= kWorkgroupPrefix + 16
	};
	
	/** Predefined IAMServiceData identifiers for data parameters passed to services
		(input parameter) or returned to the service requestor (output parameter).
		@see IAMServiceData.
		@see IAMUIServiceProvider for the data parameters and data types required by
			each predefined UI Service.
	*/
	enum
	{
		/** Output parameter: the predefined FollowupAction. */
		enFollowupAction				= 1,
		
		/** Input parameter: default file destination. */
		enDefaultFile 					= kWorkgroupPrefix + 1,
		
		/** Output parameter: the user-selected file. */ 
		enSelectedFile					= kWorkgroupPrefix + 2,
		
		/** Input parameter: init dialog to use system default directory. */
		enUseSystemDefaultDirectory		= kWorkgroupPrefix + 3,
		
		/** Input parameter: init dialog to save as stationery. */
		enSaveAsStationery				= kWorkgroupPrefix + 4,
		
		/** Output parameter: temporary version file (for viewing older version). */
		enTemporaryVersionFile			= kWorkgroupPrefix + 5,
		
		/** Output parameter: user comments. */
		enVersionComment				= kWorkgroupPrefix + 6,
		
		/** Input parameter: number of assets involved (for UI for batch operation). */
		enAssetCount					= kWorkgroupPrefix + 7,
		
		/** Input parameter: name of the current document. */
		enDocumentName					= kWorkgroupPrefix + 8,
		
		/** Input parameter: the IAMUIService service id. This parameter can be set
			by the IAMUIServiceProvider::GetService implementation. This allows a
			single instance and implementation of IAMUIService to handle more than one
			UI service. For example, a single alert service can check the enServiceID to
			determine which alert to display. */
		enServiceID						= kWorkgroupPrefix + 9,
		
		/** User message text (e.g., for alerts. */
		enMessageText					= kWorkgroupPrefix + 10,
		
		/** Current IAMLockable user name that owns the lock. */
		enCheckedOutBy					= kWorkgroupPrefix + 11,
		
		/** Current IAMLockable application name that owns the lock. */
		enCheckedOutApp					= kWorkgroupPrefix + 12,
		
		/** Current IAMLockable document name that owns the lock. */
		enCheckedOutDoc					= kWorkgroupPrefix + 13,
		
		/** Input parameter: init dialog to suppress save as IDML in save dlg. */
		enSuppressIDMLInSaveDlg			= kWorkgroupPrefix + 14		
	}; // end predefined IAMServiceData identifiers 
	

	
	/** Performs the UI service.
		@param asset is a pointer to a bound IManageableAsset or nil. When nil, the IAMServiceData
			can be checked for additional parameters, such as IAMUIService::enDefaultFile.
		@return an ErrorCode indicating the status of executing the service. Normal return is
			kSuccess, in which case the caller should check for an enFollowupAction in the
			IAMServiceData.
	*/
	virtual ErrorCode Do( IManageableAsset * asset = nil ) = 0;
	
}; // end IAMUIService interface

#endif // __IAMUISERVICE__
