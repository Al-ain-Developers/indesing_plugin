//========================================================================================
//  
//  $File: 
//  
//  Owner: 
//  
//  $Author: 
//  
//  $DateTime: 
//  
//  $Revision:  
//  
//  $Change:
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
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

#include "VCShuksanHeaders.h"

#include "IDIMSConnection.h"
#include "Ext.h"
#include "ExtLibLoader.h"

#include "SerialNumberPrivate.h"
#include "LocaleSetting.h"
#include "LocaleIDConversionUtils.h"

#include "PlugInList.h"
#include "BuildNumber.h"
#include "ICSXSExtension.h"
#include "IUsageTracking.h"

using namespace extlib;

bool16 CExt::extInitialized = kFalse;

CExt::CExt()
{
}

CExt::~CExt()
{
}

bool16 CExt::isInitialized()
{
	return extInitialized;
}

bool16 CExt::InitializeExtLib()
{
    if(extInitialized)
    {
        return kTrue;
    }
    
    InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
    bool16 isLoggingEnabled = usageTracking && usageTracking->IsUsageLoggingEnabled();
    
    //name of point product - 4 char code
    const char* product_code;
    
    if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS))
    {
        product_code = kIDEnigmaCode;
    }
    else if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
    {
        product_code = kICEnigmaCode;
    }
    else
    {
        if(isLoggingEnabled)
        {
            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kExtSubCategory, "Unexpected_product");
        }
        
        return kFalse;
    }
    
    //Locale
    PMLocaleId localeID = LocaleSetting::GetLocale();
    PMString uiLocale = LocaleIDConversionUtils::GetFullEnumString(localeID);
    uiLocale.Insert('_', 2);
    uiLocale.SetTranslatable(kFalse);
    std::string product_locale = uiLocale.GetUTF8String();
    
    if(product_locale == "")
    {
        return kFalse;
    }
    
    //User Guid
    int success = 0;
    const char *userGUID = "";
    
#if USE_AMT
    if (AMTPrivate::UseAMT())
    {
        success = SerialNumberPrivate::GetAMTUserGUID(&userGUID);
        if (success == 0) // GUID not retrieved successfully
        {
            userGUID = "";
            return kFalse;
        }
    }
#endif
    
    IDIMSConnection* fIDIMSConnection = new IDIMSConnection(kInDesignTypeKitInstance);
    
	bool isGM = false;
    std::string client_id = "";

    if(fIDIMSConnection)
    {
        isGM = fIDIMSConnection->GetGmValue();
        
        //IDIMS Client ID
        client_id = fIDIMSConnection->GetClientId();
        if(client_id == "")
        {
            return kFalse;
        }

		delete fIDIMSConnection;
		fIDIMSConnection = nil;
    }
    else
    {
        if(isLoggingEnabled)
        {
            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kExtSubCategory, "IDIMS_Connection_Failed");
        }

        return kFalse;
    }
    
    //Host Session GUID
    std::string sessionID = "";

	sessionID = usageTracking->GetSessionID();

    if(sessionID == "")
    {
        return kFalse;
    }
    
    ext_status status = ext_initialize(client_id.c_str(),
                                       product_code,
                                       kVersionNumberForResourceStr,
                                       userGUID,
                                       product_locale.c_str(),
                                       sessionID.c_str(),
                                       isGM);
    
    if(status == kExt_Success)
    {
        extInitialized = kTrue;
        return kTrue;
    }
    
    if(isLoggingEnabled)
    {
        std::string errorStr = std::to_string(status);
        usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kExtSubCategory, errorStr.c_str());                     //init failed with error code
    }
    
    return kFalse;
}

int32 CExt::LogEventForPluginList()
{
    //ExtLib should be initialized for this call
    if(!extInitialized)
    {
        return -1;
    }
    
    InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
    bool16 isLoggingEnabled = usageTracking && usageTracking->IsUsageLoggingEnabled();

    ext_event_list myList;
    ext_status status = ext_create_event_list(&myList);
    
	if (status == kExt_Success)
    {
        InterfacePtr<IPlugInList> pluginList(GetExecutionContextSession(), UseDefaultIID());
        InterfacePtr<const IPlugInListUtils> plugInUtils(GetExecutionContextSession(), IID_IPLUGINLISTUTILS);
        
        int32 pluginCount = pluginList->GetPluginCount();
        
        for (int32 i = 0; i < pluginCount; i++)
        {
            PluginID pluginID = pluginList->GetNthPlugin(i);
            
            // checking for 3rd party developers plugins
            if (!plugInUtils->IsAdobePlugin(pluginID))
            {
                std::string id = std::to_string( pluginID.Get());
                
                const PMString &tempName = pluginList->GetPluginName(pluginID);
                std::string pluginName = tempName.GetUTF8String();
                
                if(pluginName == "")
                {
                    pluginName = id;
                }

                //plugin version of form x.y.z.w
                const PMString* plugin_version = pluginList->GetAUMVersionString(pluginID);
                std::string addon_version = plugin_version->GetUTF8String();
                
                //application version
                int32 app_major, app_minor;
                pluginList->GetAppExpectedVersionNumber(pluginID, app_major, app_minor);
				std::string minor_version = std::to_string(app_minor);
                std::string major_version = std::to_string(app_major);
                
                ext_event evt;
                status = ext_create_event(pluginName.c_str(), kCPP, &evt);
                
				if (status == kExt_Success)
                {
                    ext_set_addon_id(evt, id.c_str());
                    ext_set_addon_version(evt, addon_version.c_str());
                    ext_set_min_supported_version(evt, minor_version.c_str());
                    ext_set_max_supported_version(evt, major_version.c_str());
                    
                    status = ext_add_event_to_list(myList, evt);
                    
                    if(status == kExt_Success)
                    {
                        if(isLoggingEnabled)
                        {
                            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCPPEvent, pluginName.c_str());              //successfully added event for cpp plugin
                        }
                    }
                    else
                    {
                        if(isLoggingEnabled)
                        {
                            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCPPEvent, "Add_event_failed");
                        }
                    }
                    
					ext_release_event(&evt);
                }
                else
                {
                    if(isLoggingEnabled)
                    {
                        usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCPPEvent, "Create_event_failed");
                    }
                }
            }
            //else its an adobe plugin
        }
        
        //log all the events
        status = ext_log_events(myList);
        if(status != kExt_Success)
        {
            if (isLoggingEnabled)
            {
                usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCPPEvent, "Log_events_failed");
            }
        }
       
		ext_release_event_list(&myList);
    }
    else
    {
        if(isLoggingEnabled)
        {
            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCPPEvent, "Create_event_list_failed");
        }
        
        return -1;
    }
    return 0;
}

int32 CExt::LogCepExtension(const PMString& extensionID)
{
    if(!extInitialized)
    {
        return -1;
    }
    
    InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
    bool16 isLoggingEnabled = usageTracking && usageTracking->IsUsageLoggingEnabled();
    
    std::string addon_name = extensionID.GetUTF8String();
    
    ext_event evt;
    ext_status status = ext_create_event(addon_name.c_str(), kCEP, &evt);
    
	if(status == kExt_Success)
    {
        ext_set_addon_id(evt, addon_name.c_str());

        InterfacePtr<ICSXSPlugPlug> plugPlug( ICSXSPlugPlug::QueryPlugPlug() ) ;
        InterfacePtr<ICSXSExtension> extension( plugPlug->QueryExtensionByExtensionID(extensionID) ) ;
        
        if(extension)
        {
            const PlugPlugExtensionData* extensionData = extension->GetExtensionData();
            if(extensionData)
            {
                PlugPlugVersionType* version = extensionData->version;
                if(version)
                {
                    ext_set_addon_version(evt, version->versionStr);
                }
            }
        }
        
        status = ext_log_event(evt);
        
        if(status != kExt_Success)
        {
            if(isLoggingEnabled)
            {
                usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCEPEvent, "Log_event_failed");
            }
        }
        
        ext_release_event(&evt);
        
        return 0;
    }
    else
    {
        if(isLoggingEnabled)
        {
            usageTracking->LogUsageEvent(IDUsageTracking_kExtCategory, IDUsageTracking_kCEPEvent, "Create_event_failed");
        }
    }
    return -1;
}

void CExt::DeinitializeExtlib()
{
	if (extInitialized)
	{
		ext_status status = ext_deinitialize();
		extInitialized = kFalse;
    }
}







































