//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICSXSPlugPlugExtensions.h $
//  
//  Owner: Sameer Manuja
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __ICSXSPlugPlugExtensions__
#define __ICSXSPlugPlugExtensions__

#include "ICSXSPlugPlugEventHandler.h"
#include "IPMUnknown.h"
#include "CSXSID.h"

class ICSXSPlugPlugExtensions : public ICSXSPlugPlugEventHandler
{
public:
	enum { kDefaultIID = IID_ICSXSPLUGPLUG };

	/** Loads an extension given its id.

	@param extensionID The ID of the extension to load.
	@return kTrue, if the extension starts loading.
	**/
	virtual bool16 LoadExtension(const PMString& extensionID) = 0;

	/** Unloads an extension given its id.

	@param extensionID The ID of the extension to unload.
	@return kTrue, if the extension starts unloading.
	*/
	virtual bool16 UnloadExtension(const PMString& extensionID) = 0;

	/** Get the action ID for the extension.
		The action ID can be used with IActionManager::PerformAction to mimick extension
		menu trigger behavior.

	@param extensionID The ID of the extension to get the action ID for.
	@return action ID of the extension.
	*/
	virtual ActionID GetExtensionActionID(const PMString& extensionID) = 0;


	/** Get the widget ID from the extension ID.
	@param extensionID The ID of the extension to get the widget ID for.
	@return widgetID of the widget from given extension ID.
	*/
	virtual WidgetID GetExtensionWidgetID(const PMString& extensionID ) = 0;
};

#endif
