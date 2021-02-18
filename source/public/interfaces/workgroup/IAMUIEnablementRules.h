//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMUIEnablementRules.h $
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
#ifndef __IAMUIENABLEMENTRULES__
#define __IAMUIENABLEMENTRULES__

#include "IPMUnknown.h"
#include "workgroupid.h"

class IManageableAsset;

/** The IAMUIEnablementRules interface is responsible for handling the rules that enable
	commands that are invoked through the User Interface.
	
	Developer hint: implementations of this interface may find it useful to incorporate
	the use of the IAMService::VerifyContext() method into the rules logic.
*/
class IAMUIEnablementRules : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMUIENABLEMENTRULES };

	/** The WGUICommandID enum defines the UI commands that are tested for enablement.
	*/
	enum WGUICommandID
	{
		enInvalidCommandID	= 0,
		enDisplayVersions	= kWorkgroupPrefix + 1, /* Versions... menu item */
		enSaveVersion		= kWorkgroupPrefix + 2, /* Save a Version... menu item */
		enRevertToProject	= kWorkgroupPrefix + 3, /* Revert menu item */
		enCheckOut			= kWorkgroupPrefix + 4, /* Story Check Out menu item */
		enCheckIn			= kWorkgroupPrefix + 5, /* Story Check In menu item */
		enCancelCheckOut	= kWorkgroupPrefix + 6  /* Story Cancel Check Out menu item */
	};
	
	/** This method invokes the enablement rule.
		@param commandID is a predefined WGUICommandID or any unique integer (when called by
			one of the public workgroup facades, this will always be a WGUICommandID).
		@param assetRef is a UIDRef of a boss that aggregates the IManageableAsset interface.
		@param itemRef is a UIDRef of a model boss associated with the IManageableAsset.
		@see IManageableAsset.
	*/
	virtual bool16 IsCommandEnabled( int32 commandID, UIDRef assetRef, UIDRef itemRef ) = 0;

};

#endif // __IAMUIENABLEMENTRULES__
