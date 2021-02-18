//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMUIServiceProvider.h $
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
#ifndef __IAMUISERVICEPROVIDER__
#define __IAMUISERVICEPROVIDER__

#include "IPMUnknown.h"
#include "workgroupid.h"
#include "IDFile.h"


class IAMUIService;

/** The IAMUIServiceProvider interface is responsible for providing IAMUIServices.
	@see IAMUIService.
*/
class IAMUIServiceProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMUISERVICEPROVIDER };

	/** The UIService enum defines the ID numbers for all of the asset management UI services
		currently used by the InDesign/InCopy/InDesignServer codebase. This list may be extended as
		needed by defining new unique ID numbers.
	*/
	enum UIService
	{
		/** This is the default UIService ID. */
		enInvalidService			= 0,
		
		/** This service displays a SaveAs dialog.
		
			Input IAMServiceData parameters:
			
				IAMUIService::enDefaultFile (IDFile)
				IAMUIService::enUseSystemDefaultDirectory (boolean flag)
			
			Output IAMServiceData parameters:
			
				IAMUIService::enSelectedFile (IDFile)
				IAMUIService::enSaveAsStationery (boolean flag)
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enSave (save to the IAMUIService::enSelectedFile).
					IAMUIService::enCancel (cancel all followup processing).
		*/
		enSaveAsDialog				= kWorkgroupPrefix + 1,
		
		/** This service displays a dialog to view historical versions.
		
			Input IAMServiceData parameters: none.
			Output IAMServiceData parameters:
			
				IAMUIService::enTemporaryVersionFile (IDFile)
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enPromoteVersion
					IAMUIService::enOpenFile (open the IAMUIService::enTemporaryVersionFile)		
					IAMUIService::enNone (no followup action or data).				
		*/
		enViewVersions				= kWorkgroupPrefix + 2,
		
		/** This service displays a save alert dialog.
			
			Input IAMServiceData parameters:
				IAMUIService::enDocumentName (PMString)
				
			Output IAMServiceData parameters:
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enSave (save the document)
					IAMUIService::enCancel (cancel the current operation)
					IAMUIService::enSaveVersion (save a version)
					IAMUIService::enDontSave (discard unsaved changes)			
				
		*/
		enSaveAlert					= kWorkgroupPrefix + 3,
		
		/** This service displays a revert alert dialog.
		
			Input IAMServiceData parameters: none.
			Output IAMServiceData parameters:
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enRevertToLastVersion
					IAMUIService::enRevertDocument
					IAMUIService::enCancel				
		*/
		enRevertAlert				= kWorkgroupPrefix + 4,
		
		/** This service displays a dialog to save a copy of a document.
		
			Input IAMServiceData parameters:
				IAMUIService::enUseSystemDefaultDirectory (boolean flag)
				
			Output IAMServiceData parameters:
				IAMUIService::enSelectedFile (IDFile)
				IAMUIService::enSaveAsStationery (boolean flag)
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enSave
					IAMUIService::enCancel
		*/
		enSaveACopyDialog			= kWorkgroupPrefix + 5,
		
		/** This service displays an alert when saving multiple links.
		
			Input IAMServiceData parameters: none.
			Output IAMServiceData parameters:
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enCancel
					IAMUIService::enDefaultAction
			
		*/
		enSaveMultiLinkAlert		= kWorkgroupPrefix + 6,
		
		/** This service displays a dialog to get version comments for checkin.
		
			Input IAMServiceData parameters: none.
			Output IAMServiceData parameters:
				IAMUIService::enVersionComment (PMString)
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enDefaultAction (comment string available as IAMUIService::enVersionComment)
					IAMUIService::enCancel (cancel all followup processing)
		*/
		enGetVersionComments		= kWorkgroupPrefix + 7,
		
		/** This service displays a dialog to get version comments for a batch checkin.
		
			Input IAMServiceData parameters:
				IAMUIService::enAssetCount (int32)
				
			Output IAMServiceData parameters:
				IAMUIService::enVersionComment (PMString)
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enDefaultAction (comment string available as IAMUIService::enVersionComment)
					IAMUIService::enCancel (cancel all followup processing)
					IAMUIService::enNone		
		*/
		enGetBatchVersionComments	= kWorkgroupPrefix + 8,
		
		/** This service displays a version or lock conflict alert.
		
			Input IAMServiceData parameters: none.

			Output IAMServiceData parameters:
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enOverrideAndSaveAVersion			
					IAMUIService::enRevertToLastVersion				
		*/
		enConflictAlert				= kWorkgroupPrefix + 9,
		
		/** This service displays the LiveEdit conflict alert which offers the option to embed story content.
		
			Input IAMServiceData parameters:
				IAMUIService::enCheckedOutBy (PMString; stories only)
				IAMUIService::enCheckedOutApp (PMString; stories only)
				IAMUIService::enCheckedOutDoc (PMString; stories only)
				IAMUIService::enMessageText (PMString; stories only)			
							
			Output IAMServiceData parameters:
				IAMUIService::enFollowupAction (IAMUIService::FollowupAction):
				
					IAMUIService::enDefaultAction		
					IAMUIService::enCancel				
		*/
		enLiveEditConflictAlert				= kWorkgroupPrefix + 10		
	};
	
	/** This method enables or disables the UI service provider. When disabled, the GetService() method
		returns nil for every UI service ID.
		@param b if kTrue enable UI; else disable UI.
	*/
	virtual void Enable( bool16 b ) = 0;
	
	/** This method tests if UI service provider is enabled.
		@return kTrue if enabled; kFalse otherwise. 
	*/
	virtual bool16 IsEnabled( void ) = 0;

	/** The GetService method obtains an instance of an IAMUIService interface for a specified
		UIService ID. The IAMUIService pointer is returned with a refcount of 1; the caller of
		this method is responsible for releasing the IAMUIService pointer. Suggested usage:
		
			InterfacePtr<IAMUIService> pService( myAMUIServiceProvider->GetService( myServiceID ) );
			
		The advantage of the suggested usage is that the IAMUIService pointer will be released
		automatically when pService goes out of scope.
	*/	
	virtual IAMUIService* GetService( int32 uiServiceID ) = 0;
	
	/** Tests if an IAMUIService is available.
		@param assetRef is the UIDRef of an IManageableAsset.
		@param uiServiceID is a unique UIService identifier.
		@return kTrue if the service is available; kFalse otherwise.
	*/
	virtual bool16 IsServiceAvailable( UIDRef assetRef, int32 uiServiceID ) = 0;
	
	/** This method controls displaying warning dialogs by the underlying asset management system.
	*/
	virtual void ShowAllWarningDialogs() = 0;
	
}; // end IAMUIServiceProvider interface

#endif // __IAMUISERVICEPROVIDER__
