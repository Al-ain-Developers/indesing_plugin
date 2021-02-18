//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/aem/AEMExtensionEventsWrapper.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CPMUnknown.h"

// Interfaces
#include "IApplication.h"
#include "IActiveContext.h"
#include "IAEMCurrentServerInfo.h"
#include "IAemExtensionContext.h"
#include "IAEMExtensionEventsWrapper.h"
#include "ICSXSPlugPlugEventHandler.h"
#include "ICSXSPlugPlugExtensions.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "IDocumentPrivate.h"
#include "IHTTPLinkConnectionManager.h"
#include "IHTTPLinkManager.h"
#include "IImportProvider.h"
#include "IJsonUtils.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ILinkManager.h"
#include "ILinkResource.h"
#include "IPanelMgr.h"

#include "AEMModelDefs.h"
#include "LinksUIID.h"
#include "LocaleSetting.h"
#include "OpenPlaceID.h" // kImportProviderService
#include "ProgressBar.h"

// Utils
#include "PaletteRefUtils.h"
#include "StreamUtil.h"
#include "IXMLParserUtils.h"
#include "IAEMLinkUtils.h"
#include "IRelinkUtils.h"

//AEM extension ID
static const char* kAEMAssetsExtensionID = "com.adobe.assetlink";

// AEM Assets event type
static const char* kAEMReadyEvtType = "com.adobe.assetlink.ready";
static const char* kAEMPlaceEvtType = "com.adobe.assetlink.place";
static const char* kAEMPlaceEmbedEvtType = "com.adobe.assetlink.embed";
static const char* kAEMRelinkElementEvtType = "com.adobe.assetlink.relink";

class AEMExtensionEventsWrapper : public CPMUnknown<IAEMExtensionEventsWrapper>
{
public:
    //  Constructor
    AEMExtensionEventsWrapper(IPMUnknown* boss);

    //  Destructor
    virtual ~AEMExtensionEventsWrapper() {}

    //  Called to add event listeners
    virtual void AddAEMEventListeners();

    //  Called to remove event listeners
    virtual void RemoveAEMEventListeners();

	virtual void OpenAEMAssetsPanel()
	{
		InterfacePtr<ICSXSPlugPlugExtensions> plugPlugExtensions(GetExecutionContextSession(), UseDefaultIID());
		if (plugPlugExtensions)
		{
			ActionID aemAssetsPanelActionID = plugPlugExtensions->GetExtensionActionID(kAEMAssetsExtensionID);

			if (aemAssetsPanelActionID != kInvalidActionID)
			{
				InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
				InterfacePtr<IPanelMgr> panelMgr(theApp->QueryPanelManager());
				if (panelMgr)
				{
					const IControlView* panelView = panelMgr->GetPanelFromActionID(aemAssetsPanelActionID);
					if (panelView)
					{
						PaletteRef palette = panelMgr->GetPaletteRefContainingPanel((IPMUnknown*)(panelView));
						if (PaletteRefUtils::IsPaletteVisible(palette))
							return;

						panelMgr->ShowPanelByMenuID(aemAssetsPanelActionID);
					}
				}
			}
		}
	}
    

private:
    // Event listener for when Panel is ready to be displayed
    static void AEMReadyEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context);
    // Event listener for Placing assets from Panel
    static void AEMPlaceEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context);
	// Event listener for when the Relinking has succeeded/failed from the AAL Panel
    static void AEMRelinkElementEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context);
   
    // Helper for getting AEM Extension Id
    static bool GetAEMExtensionID(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, PMString& AEMExtensionID);
};

CREATE_PMINTERFACE(AEMExtensionEventsWrapper, kAEMExtensionEventsWrapperImpl)

//========================================================================================
// AEMExtensionEventsWrapper::Constructor
//========================================================================================
AEMExtensionEventsWrapper::AEMExtensionEventsWrapper(IPMUnknown* boss) : CPMUnknown<IAEMExtensionEventsWrapper>(boss)
{
}


//========================================================================================
// AEMExtensionEventsWrapper::GetAEMExtensionID
//========================================================================================
bool AEMExtensionEventsWrapper::GetAEMExtensionID(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, PMString& AEMExtensionID)
{
    bool found = false;
    AEMExtensionID = csxsEvent->extensionId;

    if (AEMExtensionID.IsEmpty())
    {
		AEMExtensionID = Utils<IXMLParserUtils>()->GetContentAtChild(csxsEvent->data, "Id", &found);
    }
    else
    {
        found = true;
    }
    return found;
}

// On CSXS start we add an event listener for a message type to catch AEM messages from AEM Panel
//========================================================================================
// AEMExtensionEventsWrapper::AddAEMEventListeners
//========================================================================================
void AEMExtensionEventsWrapper::AddAEMEventListeners()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
	if (!plugPlug)
    {
        return;
    }

    plugPlug->AddPlugPlugEventListener(kAEMReadyEvtType, &AEMReadyEventListener, nil);
    plugPlug->AddPlugPlugEventListener(kAEMPlaceEvtType, &AEMPlaceEventListener, nil);
    plugPlug->AddPlugPlugEventListener(kAEMPlaceEmbedEvtType, &AEMPlaceEventListener, nil);
    plugPlug->AddPlugPlugEventListener(kAEMRelinkElementEvtType, &AEMRelinkElementEventListener, nil);
}

// On CSXS shutdown we remove the event listener for the message type that we added on startup
//========================================================================================
// AEMExtensionEventsWrapper::RemoveAEMEventListeners
//========================================================================================
void AEMExtensionEventsWrapper::RemoveAEMEventListeners()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
	if (!plugPlug)
    {
        return;
    }

    plugPlug->RemovePlugPlugEventListener(kAEMReadyEvtType, &AEMReadyEventListener, nil);
    plugPlug->RemovePlugPlugEventListener(kAEMPlaceEvtType, &AEMPlaceEventListener, nil);
    plugPlug->RemovePlugPlugEventListener(kAEMPlaceEmbedEvtType, &AEMPlaceEventListener, nil);
	plugPlug->RemovePlugPlugEventListener(kAEMRelinkElementEvtType, &AEMRelinkElementEventListener, nil);
}

//========================================================================================
// AEMExtensionEventsWrapper::AEMReadyEventListener
//========================================================================================
void AEMExtensionEventsWrapper::AEMReadyEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
    ASSERT(csxsEvent);
    if (!csxsEvent)
        return;

    PMString extensionID;
    if( false == GetAEMExtensionID(csxsEvent, extensionID))
    {
        ASSERT_MSG(kFalse, "No AEM Extension Id Found");
        return;
    }

    if (extensionID == kAEMAssetsExtensionID)
    {
		InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
		if (!plugPlug)
        {
            return;
        }

        if (strcmp(csxsEvent->type, kAEMReadyEvtType) == 0)
        {
            JSON json;
            std::stringstream jsonInput(csxsEvent->data);
            json.read_json(jsonInput);
            
            if (!json.checkKey("scheme") || !json.checkKey("host") || !json.checkKey("port"))
                return;
            
            std::string scheme = json.GetString("scheme");
            std::string host = json.GetString("host");
            int port = json.GetNumber("port");
            
            InterfacePtr<IAEMCurrentServerInfo> currentServerInfo(GetExecutionContextSession(), UseDefaultIID());
            currentServerInfo->SetCurrentServer(scheme, host, port);
            
			InterfacePtr<IAemExtensionContext> aemExtensionContext(GetExecutionContextSession(), UseDefaultIID());
			if (aemExtensionContext && aemExtensionContext->IsContextSet() && aemExtensionContext->GetCurrentContext() == IAemExtensionContext::kRelinkElementContext)
			{
				// Dispatch an event to the extension to relink
				ICSXSPlugPlugEventHandler::CSXSEvent csxsAemEvent;
				if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS))
				{
					csxsAemEvent.appId = kIDEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h 
				}
				else
				{
					return;
				}

				csxsAemEvent.extensionId = kAEMAssetsExtensionID;
				csxsAemEvent.type = kElementChooseEvent;
				csxsAemEvent.scope = ICSXSPlugPlugEventHandler::kEventScope_Application;


				std::string relinkElementJsonString;
				ErrorCode err = aemExtensionContext->GetContext(IAemExtensionContext::kRelinkElementContext, relinkElementJsonString);
				ASSERT(err == kSuccess);

				const char* data = relinkElementJsonString.c_str();
				csxsAemEvent.data = data;

				// send the event 
				ICSXSPlugPlugEventHandler::CSXSEventErrorCode csxsAemResult = plugPlug->DispatchPlugPlugEvent(&csxsAemEvent);
			}
        }
    }
}

//========================================================================================
// AEMExtensionEventsWrapper::AEMPlaceEventListener
//========================================================================================
void AEMExtensionEventsWrapper::AEMPlaceEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
    ASSERT(csxsEvent);
    if (!csxsEvent)
        return;
    
    PMString extensionID;
    if( false == GetAEMExtensionID(csxsEvent, extensionID))
    {
        ASSERT_MSG(kFalse, "No AEM Extension Id Found");
        return;
    }
    
    if (extensionID == kAEMAssetsExtensionID)
    {
		InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
		if (!plugPlug)
        {
            return;
        }
        if (0 == strcmp(csxsEvent->type, kAEMPlaceEvtType) || 0 == strcmp(csxsEvent->type, kAEMPlaceEmbedEvtType))
        {
            IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
            IDocument* activeDocument = activeContext->GetContextDocument();
            if( !activeDocument )
                return;
            IDataBase* db = ::GetDataBase(activeDocument);
            
            InterfacePtr<IPMStream> memoryStream(StreamUtil::CreatePointerStreamRead(const_cast<char*>(csxsEvent->data), strlen(csxsEvent->data)));
            
            
            UIDRef importedItem(db, kInvalidUID);
            InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
            InterfacePtr<IK2ServiceProvider> serviceProvider(serviceRegistry->QueryServiceProviderByClassID(kImportProviderService, kChromiumImportBoss));
            InterfacePtr<IImportProvider> chromiumProvider(serviceProvider, IID_IIMPORTPROVIDER);
            if( chromiumProvider )
            {
                IAbortableCmdSeq* importAEMAssetsCmdSeq = CmdUtils::BeginAbortableCmdSeq();
                importAEMAssetsCmdSeq->SetName("Import");
                importAEMAssetsCmdSeq->SetUndoability(ICommand::kRegularUndo);
                
                chromiumProvider->ImportThis(db, memoryStream, kFullUI, &importedItem);
                
                CmdUtils::EndCommandSequence(importAEMAssetsCmdSeq);
            }
        }
    }
}

//========================================================================================
// AEMExtensionEventsWrapper::AEMRelinkElementChosenEventListener
//========================================================================================
void AEMExtensionEventsWrapper::AEMRelinkElementEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
	ASSERT(csxsEvent);
	if (!csxsEvent)
		return;

	PMString extensionID;
	if (false == GetAEMExtensionID(csxsEvent, extensionID))
	{
		ASSERT_MSG(kFalse, "No AEM Extension Id Found");
		return;
	}

	if (extensionID == kAEMAssetsExtensionID)
	{
		InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
		if (!plugPlug)
		{
			return;
		}
		if (0 == strcmp(csxsEvent->type, kAEMRelinkElementEvtType))
		{
            InterfacePtr<IAemExtensionContext> aemExtensionContext(GetExecutionContextSession(), UseDefaultIID());
            if (!aemExtensionContext || !aemExtensionContext->IsAfterExecutionContextSet())
                return;
            
            JSON json;
            std::stringstream jsonInput(csxsEvent->data);
            json.read_json(jsonInput);
            
            // success is false if the relink event was cancelled from the AAL Panel
            if (!json.checkKey("success"))
                return;
            
            bool16 relinkSucceded = json.GetString("success") == "true" ? kTrue : kFalse;
            
            if (relinkSucceded)
            {
                std::string contextRequestRef;
                int32 contextDocID = 0;
                UID contextLinkUID = 0;
                UID contextLinkResourceUID = 0;
                UIDList uidsToRelink;
                
                if (aemExtensionContext->GetRelinkElementReceivedContext(contextRequestRef, contextDocID, contextLinkUID, contextLinkResourceUID, uidsToRelink) == kFailure)
                    return;
                
                std::string requestRef(json.GetString(kRequestRefKey));
                if (requestRef.compare(contextRequestRef))
                    return;
            
                //Extract the URI from Json response
                if (!json.checkKey("assetList"))
                    return;
                std::vector<std::string> uriList;
                JSONArray assetList;
                json.GetListAt("assetList", assetList);
                for (auto& asset : assetList)
                {
                    //skip this asset
                    if (!asset.checkKey("path"))
                        continue;
                    uriList.push_back(asset.GetString("path"));
                }
                if(uriList.size() < 1)
                    return;
                
                //See if the said document is still open.
                InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
                InterfacePtr<IDocumentList> docList(application->QueryDocumentList());
                int32 docCount = docList->GetDocCount();
                bool16 docStillOpen = kFalse;
                IDataBase * docDB = NULL;
                for(int32 i = 0; i < docCount; i++)
                {
                    InterfacePtr<IDocumentPrivate> iDoc(docList->GetNthDoc(i), UseDefaultIID());
                    if(iDoc->GetID() == contextDocID)
                    {
                        docStillOpen = kTrue;
                        docDB = ::GetDataBase(iDoc);
                        break;
                    }
                }
                if(docStillOpen == kFalse)
                {
                    aemExtensionContext->ResetAfterExecutionContext();
                    return;
                }
                
                
                // Check if link/resource exists.
                ILinkManager::QueryResult result;
                InterfacePtr<ILinkManager> iLinkManager(docDB, docDB->GetRootUID(), UseDefaultIID());
                if (contextLinkUID != kInvalidUID)
                {
                    bool16 linkExists = docDB->IsValidUID(contextLinkUID);
                    if (!linkExists)
                        return;
                }
                
                bool16 linkResourceExists = iLinkManager->QueryLinksByResourceUID(contextLinkResourceUID, kTrue, result);
                if (!linkResourceExists)
                    return;
                
                // Call RelinkUtils with Link and LinkResource and elementRef.
                InterfacePtr<ILink> contextLink(docDB, contextLinkUID, UseDefaultIID());
                InterfacePtr<ILinkResource> contextLinkResource(docDB, contextLinkResourceUID, UseDefaultIID());
                
                
                TaskProgressBar progress("kImportingAEMAsset", 1, kTrue);
                progress.DisableChildProgressBars(kTrue);
                
                progress.SetTaskStatus("kImportingAEMAsset");
                
                Utils<IRelinkUtils>()->DoRelinkWithAALAsset(uriList[0], contextLink, contextLinkResource);
                
                progress.DoTask("kImportingAEMAsset");
                
                
                aemExtensionContext->ResetAfterExecutionContext();
                
                // Check if there are any pending links remaining for relinking
                if (uidsToRelink.size() > 1)
                {
                    uidsToRelink.Remove(0);
                    Utils<IRelinkUtils>()->DoRelinkSelectedLinksWithAALAssets(uidsToRelink, kIDLinkClientID);
                }
            }
            else
            {
                aemExtensionContext->ResetAfterExecutionContext();
            }
            
		}
	}
}
