//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/ISaveAssetContent.h $
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
#ifndef __ISAVEASSETCONTENT__
#define __ISAVEASSETCONTENT__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IDFile;

/** This is a call-back interface that is responsible for saving (writing) asset content.
	It may be used by IAMServiceProvider::enCheckIn services to assure that an asset's
	model changes are applied as part of the check in. For example, an ISaveAssetContent
	implementation for stories would export a story page item. Similarly, an implementation
	for InDesign documents would write the document to an indd file. The ISaveAssetContent
	hook is useful for complicated checkin rules that involve displaying UI with a Cancel
	option. Thus, should the user cancel the operation, the checkin can be aborted without
	the unwanted side-effect writing the content.
	
	To enable this callback during the enCheckIn service, add this interface to the service
	boss. 
	
	Example:
	
	The following boss checks in an InDesign document to Version Cue:
	
		Class
		{
			kVCCheckInServiceBoss,
			kInvalidClass,
			{
				IID_IAMSERVICE,			kVCCheckInServiceImpl,
				IID_IAMSERVICEDATA,		kAMServiceDataImpl,
				IID_ISAVEASSETCONTENT,	kSaveDocumentContentImpl, // Saves an indd document
			}
		},

	Example:

	The following boss checks in a LiveEdit story (does not use Version Cue):
	
		Class
		{
			kICCheckInServiceBoss,
			kInvalidClass,
			{
				IID_IAMSERVICE,			kICCheckInServiceImpl,
				IID_IAMSERVICEDATA,		kAMServiceDataImpl,
				IID_ISAVEASSETCONTENT,	kSaveStoryContentImpl,	// Exports a story
			}
		},
			
*/

class ISaveAssetContent : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAVEASSETCONTENT };
	
	/**	Writes asset content to secure storage.
		@param assetRef is the UIDRef of a boss that aggregates the IManageableAsset interface.
		@param destination is the IDFile to write the content data to. The file need not exist
			beforehand. For an asset that is not file-based, the file path may be empty. In this 
			case, an implementation of this method must be able to determine the destination from
			the UIDRef alone.
		@return kSuccess if the content was written without error, or did not require
			writing. An appropriate ErrorCode is returned if the operation fails.
	*/
	virtual ErrorCode Do( UIDRef assetRef, const IDFile & destination ) = 0;
	
}; // end ISaveAssetContent interface

#endif // __ISAVEASSETCONTENT__
