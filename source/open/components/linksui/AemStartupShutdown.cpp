//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/AemStartupShutdown.cpp $
//
//  Owner: swagarg
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
//  Copyright 1997-2014 Adobe Systems Incorporated. All rights reserved.
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

#include "VCPlugInHeaders.h"

#include "IAEMCurrentServerInfo.h"
#include "IAEMLinkUtils.h"
#include "IJsonUtils.h"
#include "IStartupShutdownService.h"

#include "URI.h"
#include "AEMModelDefs.h"

//========================================================================================

class AemStartupShutdown : public CPMUnknown<IStartupShutdownService>
{
public:
	AemStartupShutdown(IPMUnknown *boss);
	virtual void Startup();
	virtual void Shutdown();
};

CREATE_PMINTERFACE(AemStartupShutdown, kAemStartupShutdownImpl)

//========================================================================================

AemStartupShutdown::AemStartupShutdown(IPMUnknown *boss)
: CPMUnknown<IStartupShutdownService>(boss)
{}

//========================================================================================

void AemStartupShutdown::Startup()
{
    // If AEM server details file is present, read that & set current server info details
    InterfacePtr<IAEMCurrentServerInfo> aemCurrentServerInfo(GetExecutionContextSession(), UseDefaultIID());
    URI currentUri = aemCurrentServerInfo->GetCurrentServer();
    if (currentUri == URI("") || currentUri.GetComponent(URI::kAuthority) == kAEMPlaceholderURI)
    {
        std::string serverDetails;
        bool16 serverInfoFilePresent = Utils<IAEMLinkUtils>()->GetServerInfoFromFile(serverDetails);
        if (serverInfoFilePresent)
        {
            JSON json;
            std::stringstream jsonInput(serverDetails);
            try
            {
                json.read_json(jsonInput);
            }
            catch (...)
            {
                return;
            }
            
            if (!json.checkKey("scheme") || !json.checkKey("host") || !json.checkKey("port"))
                return;
            
            std::string scheme = json.GetString("scheme");
            std::string host = json.GetString("host");
            int port = json.GetNumber("port");
            
            InterfacePtr<IAEMCurrentServerInfo> currentServerInfo(GetExecutionContextSession(), UseDefaultIID());
            currentServerInfo->SetCurrentServer(scheme, host, port);
        }
    }
}

//========================================================================================

void AemStartupShutdown::Shutdown()
{
}

//========================================================================================
