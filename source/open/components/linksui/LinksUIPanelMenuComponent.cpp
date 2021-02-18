//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelMenuComponent.cpp $
//  
//  Owner: lance bushore
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

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IActionStateList.h"
#include "IWidgetParent.h"
#include "IControlView.h"
#include "ISubject.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IApplication.h"
#include "ILinkInfoProvider.h"
#include "ILinksUIUtils.h"
#include "ILinksUIPanelPrefs.h"
#include "IMetaDataAccess.h"
#include "IActiveContext.h"
#include "ILinkUtils.h"
#include "ILink.h"
#include "ILinkResource.h"
#include "ILinkFacade.h"
#include "IDataLinkAction.h"
#include "IAdobeAuxMetaData.h"
#include "IOpenFileDialog.h"
#include "IMetaDataUIUtils.h"
#include "IClipboardController.h"
#include "IDataExchangeHandler.h"
#include "ITextScrapData.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IDocument.h"
#include "ILinkItemSuite.h"
#include "ISelectionUtils.h"
#include "ISharedContentFacade.h"
#include "ILinkManager.h"
#include "IPersistUIDData.h"
#include "ILinkObject.h"
#include "IWindow.h"
#include "IBoolData.h"
#include "IStringData.h"
#include "ITemporaryDataForLogging.h"
#include "ITreeViewController.h"
#include "ISplitterPanelControlData.h"
#include "IWidgetUtils.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "IUsageTracking.h"
#include "ILinkObjectReference.h"
#include "ISelectionManager.h"
#include "ILayoutHitTestSuite.h"
#include "ILayoutTarget.h"

// Includes:
#include "CActionComponent.h"
#include "LinksUIID.h"
#include "UIDList.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "LinksUIResDefs.h"
#include "Utils.h"
#include "PreferenceUtils.h"
#include "SysFileList.h"
#include "CAlert.h"
#include "FileUtils.h"
#include "IDFile.h"
#include "LinkQuery.h"
#include "LinkResourceQuery.h"
#include "DrawStringUtils.h"
#include "StringUtils.h"
#include "IRelinkUtils.h"
#include "ICloudLibraryLinkedAssetUtils.h"
#include "URI.h"
#include "IPrivateLinkUtils.h"
#include "IEndnoteFacade.h"
#include "IAEMLinkUtils.h"

// Event name for logging actions on CC Libraries linked assets.
#define kRelinkInitiated		"RelinkInitiated"
#define kEditOriginalInitiated	"EditOriginalInitiated"
#define kRevealInCCInitiated	"RevealInCCLibsInitiated"
#define kUnembedInitiated		"UnembedInitiated"
#define kUnembedSuccessful		"UnembedSuccessful"

#define kMenuString				"Menu"
#define kLinksPanel				"LinksPanel"


class LinksUIPanelMenuComponent : public CActionComponent
{
public:
	LinksUIPanelMenuComponent(IPMUnknown *boss) : CActionComponent(boss)
		{}
	
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

private:
	void DisplayPrefsDialog(IPMUnknown* widget) const;
	void CopyStringToScrap(const WideString& pathStr) const;
	UIDList GetLinkResourcesForMenuAction(IPMUnknown* widget, bool16 inDisplayOrder = kFalse) const;
	void HandleNonLinkAction(ActionID actionID, IPMUnknown* widget);
	void DoCopyLinks(const UIDList& targetLinks) const;
	void ShowXMPInfoForLink(const ILink* oneLink) const;
	void GenerateLinkReport(const UIDList& targetLinks) const;
	void CopyAllLinkInfo(const UIDList& targetLinks) const;
	bool16 ContainsDifferentParentStories(const UIDList& storyList) const;
	bool16 ValidateCanEditStoryLinks(const UIDList& targetLinks) const;
	void LogCloudAssetActions(ActionID actionID, UIDList& targetLinks, bool16 unembedSuccessful = kFalse);
	UIDList GetAllDocLinks(const IDocument* currentDoc) const;
    UIDList GetAllDownloadableLinks(const IDocument* currentDoc, const UIDList& allLinks) const;
    UIDList GetAllReplacableLinks(const IDocument* currentDoc, const UIDList& allLinks) const;
    bool16 ValidateCanDownloadAllOriginalLinks(const IDocument* currentDoc) const;
    bool16 ValidateCanReplaceAllFPOWithOriginalLinks(const IDocument* currentDoc) const;
};

CREATE_PMINTERFACE(LinksUIPanelMenuComponent, kLinksUIPanelMenuComponentImpl)

UIDList LinksUIPanelMenuComponent::GetLinkResourcesForMenuAction(IPMUnknown* widget, bool16 inDisplayOrder) const
{
	InterfacePtr<const ILinkResource> resourceFromWidget(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(widget));
	UIDList selectedResources = Utils<ILinksUIUtils>()->GetLinkResourcesSelectedInPanel(inDisplayOrder);
	if(!resourceFromWidget || selectedResources.Contains(::GetUID(resourceFromWidget)))
		return selectedResources;
		
	return UIDList(::GetUIDRef(resourceFromWidget));
}

enum WhichMenuItem { kRelinkMenuItemEnum, kUpdateMenuItemEnum, kEmbedMenuItemEnum, kUnEmbedMenuItemEnum, kUnlinkMenuItemEnum, kCCRelinkMenuItemEnum, kAALRelinkMenuItemEnum, kReplaceFPOWithOriginalMenuItemEnum };

PMString GetDynamicMenuItemNameForAction(WhichMenuItem menuItem, bool applyToAllInstances, PMString& singleResourceName)
{
	if(applyToAllInstances)
	{
		if(singleResourceName.IsEmpty())
		{
			switch(menuItem)
			{
                case kAALRelinkMenuItemEnum:
				case kCCRelinkMenuItemEnum:
				case kRelinkMenuItemEnum:
					return "#LinksUIRelinkResourceMenu";
				case kUpdateMenuItemEnum:
					return "#LinksUIUpdateLinkResourceMenu";
				case kEmbedMenuItemEnum:
					return "#LinksUIEmbedResourceMenu";
				case kUnEmbedMenuItemEnum:
					return "#LinksUIUnEmbedResourceMenu";
				case kUnlinkMenuItemEnum:
					return "#UnLinkResourceMenu";
                case kReplaceFPOWithOriginalMenuItemEnum:
                    return "#ReplaceFPOWithOriginalResourceMenu";
				default:
					ASSERT_FAIL("GetDynamicMenuItemNameForAction got unknown menu item");
			}
		}
		else
		{
			PMString menuItemName;
			switch(menuItem)
			{
				case kCCRelinkMenuItemEnum:
					menuItemName.SetCString("#RelinkCloudResource ^1 Menu");
					break;
				case kRelinkMenuItemEnum:
					menuItemName.SetCString("#RelinkResource ^1 Menu");
					break;
				case kUpdateMenuItemEnum:
					menuItemName.SetCString("#UpdateResource ^1 Menu");
					break;
				case kEmbedMenuItemEnum:
					menuItemName.SetCString("#EmbedResource ^1 Menu");
					break;
				case kUnEmbedMenuItemEnum:
					menuItemName.SetCString("#UnembedResource ^1 Menu");
					break;
				case kUnlinkMenuItemEnum:
					menuItemName.SetCString("#UnLinkResource ^1 Menu");
					break;
                case kAALRelinkMenuItemEnum:
                    menuItemName.SetCString("#RelinkAALResource ^1 Menu");
                    break;
                case kReplaceFPOWithOriginalMenuItemEnum:
                    menuItemName.SetCString("#ReplaceFPOWithOriginalResource ^1 Menu");
                    break;
				default:
					ASSERT_FAIL("GetDynamicMenuItemNameForAction got unknown menu item");
			}
			menuItemName.Translate();
			singleResourceName.SetTranslatable(kFalse);
			StringUtils::ReplaceStringParameters(&menuItemName,singleResourceName);
			return menuItemName;
		}
	}
	else
	{
		switch(menuItem)
		{
			case kRelinkMenuItemEnum:
				return "#LinksUIRelinkLinkMenu";
			case kUpdateMenuItemEnum:
				return "#LinksUIUpdateLinkMenu";
			case kEmbedMenuItemEnum:
				return "#LinksUIEmbedLinkMenu";
			case kUnEmbedMenuItemEnum:
				return "#LinksUIUnEmbedLinkMenu";
			case kUnlinkMenuItemEnum:
				return "#LinksUIUnLinkMenu";
			case kCCRelinkMenuItemEnum:
				return "#LinksUIRelinkFromCloudAssetLinkMenu";
            case kAALRelinkMenuItemEnum:
                return "#LinksUIRelinkFromAALAssetLinkMenu";
            case kReplaceFPOWithOriginalMenuItemEnum:
                return "#LinksUIReplaceFPOWithOriginalLink";
			default:
				ASSERT_FAIL("GetDynamicMenuItemNameForAction got unknown menu item");
		}
	}
	ASSERT_FAIL("GetDynamicMenuItemNameForAction found no string to return");
	return "";
}

PMString GetStringFromControlUnderAtPoint(IPMUnknown* widget,GSysPoint mousePoint)
{
	PMString controlString;
	InterfacePtr<const IControlView>	myView(widget, UseDefaultIID());
	InterfacePtr<const IPanelControlData> panelData(widget,UseDefaultIID());
	if(panelData && myView)
	{
		SysPoint localWhere = ::ToSys(myView->GlobalToWindow(mousePoint));
		IControlView *childWidget = panelData->FindWidget(localWhere);
		InterfacePtr<const ITextControlData> textData(childWidget,UseDefaultIID());
		if(textData)
		{
			controlString = textData->GetString();
			controlString.Translate();
		}
	}
	return controlString;
}

void LinksUIPanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(mousePoint)
	UIDList targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget);
	UIDList targetResources = GetLinkResourcesForMenuAction(widget);

	const int32 nCount = listToUpdate->Length();

	const IDocument* currentDoc = ac->GetContextDocument();
	Utils<Facade::ILinkFacade> linkFacade;

	Utils<Facade::ISharedContentFacade> sharedContentFacade;

	for (int32 i = 0; i < nCount; i++)
	{
		ActionID nAction = listToUpdate->GetNthAction(i);

		switch (nAction.Get())
		{
			case kGenerateLinkReportActionID:
			{
				if(targetLinks.size() >= 1)
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
				}
			}
			break;
			case kAutosizeLinkInfoActionID:
			case kCopyAllLinkInfoActionID:
			{
				if(targetLinks.size() == 1)
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
				}
			}
			break;
			case kCopySingleLinkInfoFieldActionID:
			{
				if(targetLinks.size() == 1 && widget)
				{
					PMString controlUnderMouseString = GetStringFromControlUnderAtPoint(widget,mousePoint);
					if(!controlUnderMouseString.IsEmpty())
					{
						PMString menuName("#CopyLinkInfoStr '^1'");
						menuName.Translate();
						StringUtils::ReplaceStringParameters(&menuName,controlUnderMouseString);
						listToUpdate->SetNthActionName(i, menuName);
						listToUpdate->SetNthActionState(i, kEnabledAction);
					}

				}
			}
			break;
			case kShowHideLinkInfoActionID:
			{
				if(widget)
				{
					InterfacePtr<const ISplitterPanelControlData> splitterControlData((ISplitterPanelControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget(widget,kLinkUISplitterPanelWidgetID,IID_ISPLITTERPANELCONTROLDATA));
					if(splitterControlData)
					{
						listToUpdate->SetNthActionState(i, kEnabledAction);
						if(splitterControlData->IsSinglePanelVisible())
							listToUpdate->SetNthActionName(i,"#LinksUIShowLinkInfoMenu");
						else
							listToUpdate->SetNthActionName(i,"#LinksUIHideLinkInfoMenu");
					}
				}
			}
			break;
			case kUpdateAllOutOfDateLinksActionID:
			{
				IDataBase* docDB = ::GetDataBase(currentDoc);
				if (docDB)
				{
					UIDList resultUIDs(docDB);
					InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
					LinkQuery query; 
					query.SetResourceModState(ILink::kResourceModified); 
					query.SetLinkType(ILink::kImport); 
					query.SetLinkType(ILink::kExport); 
					query.SetLinkType(ILink::kBidirectional);
					
					linkMgr->QueryLinks(query, kIDLinkClientID, resultUIDs);
					if(resultUIDs.size())
						listToUpdate->SetNthActionState(i, kEnabledAction);
				}
				
			}
			break;
			case kAutoFindAllMissingLinksActionID:
			{
				if(currentDoc)
				{					
					IDataBase* docDB = ::GetDataBase(currentDoc);
					const IDFile* pPubDir(docDB->GetSysFile());
					if(!pPubDir)
						pPubDir = docDB->GetSysFileFromOpen();
					if (docDB && pPubDir)
					{
						UIDList resultUIDs(docDB);
						InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
						LinkResourceQuery query;
						query.SetState(ILinkResource::kMissing);

						linkMgr->QueryResources(query, kIDLinkClientID, resultUIDs);
						if(resultUIDs.size())
							listToUpdate->SetNthActionState(i, kEnabledAction);
					}
				}
			}
			break;
			case kLinksUIHideShowInfoThumbnailActionID:
			{
				listToUpdate->SetNthActionState(i, kEnabledAction);
				
				InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
				if(linksUIPrefs->GetShowLinkInfoThumbnail())
					listToUpdate->SetNthActionName(i,"#LinksUIHideInfoThumbnailMenu");
				else
					listToUpdate->SetNthActionName(i,"#LinksUIShowInfoThumbnailMenu");
				break;
			}			
			case kLinksUIHideShowThumbnailActionID:
			{
				InterfacePtr<const ILinkInfoProvider> headerProvider(Utils<ILinksUIUtils>()->QueryLinkInfoProviderFromHeaderWidget(widget));
				if(headerProvider && ::GetClass(headerProvider) == kLinkInfoNameProviderBoss) // this item is only on the 'name' column
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
					
					InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
					if(linksUIPrefs->GetShowLinkThumbnail())
						listToUpdate->SetNthActionName(i,"#LinksUIHideThumbnailMenu");
					else
						listToUpdate->SetNthActionName(i,"#LinksUIShowThumbnailMenu");
				}
				break;
			}			
			case kLinksUIRemoveColumnActionID:
			{
				InterfacePtr<const ILinkInfoProvider> headerProvider(Utils<ILinksUIUtils>()->QueryLinkInfoProviderFromHeaderWidget(widget));
				if(headerProvider && ::GetClass(headerProvider) != kLinkInfoNameProviderBoss) // they can remove any column except name.
					listToUpdate->SetNthActionState(i, kEnabledAction);
				break;
			}
			case kRevealLinkInBridgeSelectionActionID:
			{
				UIDRef linkSelectedInLayout = Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout();
				if (linkFacade && linkSelectedInLayout.GetUID() != kInvalidUID && linkFacade->CanRevealLinkInBridge(linkSelectedInLayout))
				{
					listToUpdate->SetNthActionState(i,kEnabledAction);
				}
			}
				break;
			case kRevealLinkInCloudLibrariesSelectionActionID:
				{
					UIDRef linkSelectedInLayout = Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout();
					if (linkFacade && linkSelectedInLayout.GetUID() != kInvalidUID && linkFacade->CanRevealLinkInCloudLibraries(linkSelectedInLayout))
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
				}
				break;
			case kRevealLinkInOSSelectionActionID:
			{
				UIDRef linkSelectedInLayout = Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout();
				if (linkFacade && linkSelectedInLayout.GetUID() != kInvalidUID && linkFacade->CanRevealLink(linkSelectedInLayout))
				{
					listToUpdate->SetNthActionState(i,kEnabledAction);
				}
			
			}
				break;
			case kRevealLinkInBridgeActionID:
				{
					if(targetLinks.size() == 1)
					{
						if (linkFacade->CanRevealLinkInBridge(targetLinks.GetRef(0)))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;
			case kLicenseStockAssetActionID:
				{
					if (targetLinks.size() == 1)
					{
						InterfacePtr<const ILink> link(targetLinks.GetRef(0), UseDefaultIID());
						InterfacePtr<const ILinkResource> linkResource(::GetDataBase(link), link->GetResource(), UseDefaultIID());
						if (linkResource)
						{
							URI uri = linkResource->GetURI();
							if (linkResource->GetStoreState() != ILinkResource::kEmbedded && Utils<ICloudLibraryLinkedAssetUtils>()->IsCloudScheme(uri))
							{
								// Check if the accessor APIs can tell us. 
								PMString elementRef(uri.GetComponent(URI::kPath));
								std::string elementRefStr(elementRef.GetUTF8String());

								if (Utils<ICloudLibraryLinkedAssetUtils>()->IsElementStock(elementRefStr) && !Utils<ICloudLibraryLinkedAssetUtils>()->IsElementStockLicensed(elementRefStr))
									listToUpdate->SetNthActionState(i, kEnabledAction);
							}
						}
					}
				}
				break;
			case kRevealLinkInCloudLibrariesActionID:
				{
					if(targetLinks.size() == 1)
					{
						if (linkFacade->CanRevealLinkInCloudLibraries(targetLinks.GetRef(0)))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;
			case kRevealLinkInOSActionID:
				{
					if(targetLinks.size() == 1)
					{
						if (linkFacade && linkFacade->CanRevealLink(targetLinks.GetRef(0)))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;
			case kGotoLinkActionID:
				{
					if(targetLinks.size() == 1)
					{
						InterfacePtr<IDataLinkAction> dlAction(targetLinks.GetRef(0), UseDefaultIID());
						if (dlAction && dlAction->EnableGotoLink())
							listToUpdate->SetNthActionState(i,kEnabledAction);
					}
				}
				break;
			case kLinksUICopyPathActionID :
			case kLinksUICopyPlatformPathActionID:
					if(targetResources.size() == 1)
					{
						InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0),UseDefaultIID());
						if(linkResource && !linkResource->GetLongName(false).empty())
							listToUpdate->SetNthActionState(i,kEnabledAction);
					}
				break;
			case kEditOriginalLayoutSelectionActionID :
				{	
					UIDList targetLayoutLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
					if (targetLayoutLinks.Length() >= 1)
					{
						if (Utils<ILinksUIUtils>()->SomeCanEdit(targetLayoutLinks))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;

			case kLinksUIEditOriginalActionID :
				{	
					if(targetResources.size() >= 1 && targetLinks.size() >= 1)
					{
						if (Utils<ILinksUIUtils>()->SomeCanEdit(targetLinks))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;

			case kGoToSourceLayoutSelectionActionID :
				{	
					UIDList targetLayoutLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
					if (targetLayoutLinks.Length() >= 1)
					{
						if (Utils<ILinksUIUtils>()->SomeCanGoToSource(targetLayoutLinks))
						{
							bool16 enableEditOriginal = ValidateCanEditStoryLinks(targetLayoutLinks);
							if(enableEditOriginal)
								listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;

			case kLinksUIGoToSourceActionID :
				{	
					if(targetResources.size() >= 1 && targetLinks.size() >= 1)
					{
						if (Utils<ILinksUIUtils>()->SomeCanGoToSource(targetLinks))
						{
							bool16 enableEditOriginal = ValidateCanEditStoryLinks(targetLinks);
							if(enableEditOriginal)
								listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
				}
				break;

			case kLinksUIUpdateLinkActionID :
				{
					bool updatingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);
					PMString singleResourceToUpdateName;
					if(updatingAllInstances)
					{
						if(targetResources.size() == 1)
						{
							InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0),UseDefaultIID());
							singleResourceToUpdateName.SetString(linkResource->GetShortName(true));
						}
					}
					
					for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
					{
						if (linkFacade->CanUpdateLink(targetLinks.GetRef(linkIndex), false))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
							break;
						}
					}
					listToUpdate->SetNthActionName(i,GetDynamicMenuItemNameForAction(kUpdateMenuItemEnum,updatingAllInstances,singleResourceToUpdateName));
				}
				break;
			case kLinksUIRelinkToCloudAssetActionID:
				{
					PMString singleResourceToRelinkName;
					bool relinkingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);
					if (relinkingAllInstances)
					{

						if (targetResources.size() == 1)
						{
                            IDataBase* linkDB = targetResources.GetDataBase();
                            InterfacePtr<const ILink> iLink(targetLinks.GetRef(0),UseDefaultIID());
                            if (iLink && iLink->GetLinkType() == ILink::kChild)
                                break;
    
							InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0), UseDefaultIID());
							singleResourceToRelinkName.SetString(linkResource->GetShortName(true));
							if (linkFacade->CanRelinkResource(targetResources.GetRef(0)))
							{
								listToUpdate->SetNthActionState(i, kEnabledAction);
							}
						}
					}
					else
					{
						for (int32 linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
						{
							if (linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
							{
								listToUpdate->SetNthActionState(i, kEnabledAction);
								break;
							}
						}
					}
					if (nAction == kLinksUIRelinkToCloudAssetActionID)
					{
						listToUpdate->SetNthActionName(i, GetDynamicMenuItemNameForAction(kCCRelinkMenuItemEnum, relinkingAllInstances, singleResourceToRelinkName));
					}
				}
				break;
                
            case kLinksUIRelinkToAALAssetActionID:
            {
                bool16 addAALToMenuItem = Utils<IAEMLinkUtils>()->ShouldShowAALRelinkAction();
                if (!addAALToMenuItem)
                    break;
                PMString singleResourceToRelinkName;
                bool relinkingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);
                if (relinkingAllInstances)
                {
                    if (targetResources.size() == 1)
                    {
                        IDataBase* linkDB = targetResources.GetDataBase();
                        InterfacePtr<const ILink> iLink(targetLinks.GetRef(0),UseDefaultIID());
                        if (iLink && iLink->GetLinkType() == ILink::kChild)
                            break;
                        
                        InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0), UseDefaultIID());
                        singleResourceToRelinkName.SetString(linkResource->GetShortName(true));
                        if (linkFacade->CanRelinkResource(targetResources.GetRef(0)))
                        {
                            listToUpdate->SetNthActionState(i, kEnabledAction);
                        }
                    }
                }
                else
                {
                    for (int32 linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
                    {
                        if (linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
                        {
                            listToUpdate->SetNthActionState(i, kEnabledAction);
                            break;
                        }
                    }
                }
                if (nAction == kLinksUIRelinkToAALAssetActionID)
                {
                    listToUpdate->SetNthActionName(i, GetDynamicMenuItemNameForAction(kAALRelinkMenuItemEnum, relinkingAllInstances, singleResourceToRelinkName));
                }
            }
                break;
			case kLinksUIRelinkActionID:
			case kLinksUIRelinkFileExtensionActionID:
			case kLinksUIRelinkToFolderActionID:				
				{
					PMString singleResourceToRelinkName;
					bool relinkingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);
					if(relinkingAllInstances)
					{
						if(targetResources.size() == 1)
						{
							InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0),UseDefaultIID());
							singleResourceToRelinkName.SetString(linkResource->GetShortName(true));
                            
                            IDataBase* linkDB = targetResources.GetDataBase();
                            InterfacePtr<const ILink> iLink(targetLinks.GetRef(0), UseDefaultIID());
                            if (iLink && iLink->GetLinkType() == ILink::kChild)
                                break;
						}

						for(int resIndex = targetResources.Length() - 1; resIndex >= 0; --resIndex)
						{
							if (linkFacade->CanRelinkResource(targetResources.GetRef(resIndex)))
							{
								listToUpdate->SetNthActionState(i,kEnabledAction);
								break;
							}
						}

						//let us disable relink extension for shared content links 
						if(nAction == kLinksUIRelinkFileExtensionActionID)
						{
							for(int resIndex = targetResources.Length() - 1; resIndex >= 0; --resIndex)
							{
								InterfacePtr<const ILinkResource> theLinkResource(targetResources.GetRef(resIndex),UseDefaultIID());
								if(sharedContentFacade && sharedContentFacade->IsSharedContentLinkResource(theLinkResource))
								{
									listToUpdate->SetNthActionState(i,kDisabled_Unselected);
									break;
								}
							}
						}
					}
					else
					{
						for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
						{
							if (linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
							{
								listToUpdate->SetNthActionState(i,kEnabledAction);
								break;
							}
						}

						//let us disable relink extension for shared content links 
						if(nAction == kLinksUIRelinkFileExtensionActionID)
						{
							for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
							{
								InterfacePtr<const ILink> theLink(targetLinks.GetRef(linkIndex),UseDefaultIID());
								if(sharedContentFacade && sharedContentFacade->IsSharedContentLink(theLink))
								{
									listToUpdate->SetNthActionState(i,kDisabled_Unselected);
									break;
								}
							}
						}
					}
					if(nAction == kLinksUIRelinkActionID)
					{
						listToUpdate->SetNthActionName(i,GetDynamicMenuItemNameForAction(kRelinkMenuItemEnum,relinkingAllInstances,singleResourceToRelinkName));
					}
				}
				break;
			case kLinksUIEmbedLinkActionID :
				{					
					bool allEmbeddable = true;
					bool allUnembeddable = true;
					bool allUnlinkable = true;
					
					bool embeddingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);

					PMString singleResourceToEmbedName;
					if(embeddingAllInstances)
					{
						if(targetResources.size() == 1)
						{
							InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0),UseDefaultIID());
							singleResourceToEmbedName.SetString(linkResource->GetShortName(true));
						}
					}
						
					for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
					{
						UIDRef linkRef = targetLinks.GetRef(linkIndex);
						bool bCanEmbedLink = linkFacade->CanEmbedLink(linkRef);
						bool bCanUnembedLink = linkFacade->CanUnembedLink(linkRef);

						if(allUnlinkable)
						{
							InterfacePtr<const ILink> link(linkRef,UseDefaultIID());
							InterfacePtr<const ILinkResource> linkResource(::GetDataBase(link),link->GetResource(),UseDefaultIID());
							if(link->GetLinkType() == ILink::kChild || (linkResource && linkResource->GetStoreState() != ILinkResource::kContained) || LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
							{
								allUnlinkable = false;
							}
						}

						ASSERT_MSG(!bCanEmbedLink || !bCanUnembedLink, "LinksUIPanelMenuComponent::UpdateActionStates - link cannot be both embeddable and unembeddable?");

						allEmbeddable &= bCanEmbedLink;
						allUnembeddable &= bCanUnembedLink;
						if(!allUnlinkable && !allEmbeddable && !allUnembeddable)
							break;
					}


					if(allEmbeddable && !allUnembeddable)
					{
						listToUpdate->SetNthActionName(i,GetDynamicMenuItemNameForAction(kEmbedMenuItemEnum,embeddingAllInstances,singleResourceToEmbedName));
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else if(!allEmbeddable && allUnembeddable)
					{
						listToUpdate->SetNthActionName(i,GetDynamicMenuItemNameForAction(kUnEmbedMenuItemEnum,embeddingAllInstances,singleResourceToEmbedName));							
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else if(targetLinks.size() && allUnlinkable)
					{
						listToUpdate->SetNthActionName(i,GetDynamicMenuItemNameForAction(kUnlinkMenuItemEnum,embeddingAllInstances,singleResourceToEmbedName));							
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}

				}
				break;
			case kLinksUIPanelFileXMPInfoActionID:
				{
					if(targetLinks.size() == 1)
					{
						InterfacePtr<const ILink> theLink(targetLinks.GetRef(0),UseDefaultIID());
						if(sharedContentFacade && sharedContentFacade->IsSharedContentLink(theLink))
							break;

						InterfacePtr<const IMetaDataAccess> iMetaDataAccess(Utils<ILinksUIUtils>()->QueryMetaDataAccessFromLink(theLink));
						// Also check for non-xmp metadata by getting the actual packet (might contain converted EXIF, etc.)
						InterfacePtr<const ILinkResource> linkResource(::GetDataBase(theLink),theLink->GetResource(),UseDefaultIID());
						std::string packet;
						bool16 xmpFound = Utils<IPrivateLinkUtils>()->GetXMPPacketInfo(::GetUIDRef(linkResource), packet);
						if(iMetaDataAccess || xmpFound)
							listToUpdate->SetNthActionState(i,kEnabledAction);
					}
				
				}
				break;
		case kCopyLinksActionID:
			{
					for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
					{
						if (linkFacade->CanCopyLinkToFolder(targetLinks.GetRef(linkIndex)))
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
							break;
						}
					}
			}
			break;
		
	
		case kEmbedLinkFromPropsPanelActionID:
			{
				UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
				bool allEmbeddable = true;
				bool allUnembeddable = true;

				for (int linkIndex = selectedLinks.Length() - 1; linkIndex >= 0; --linkIndex)
				{
					UIDRef linkRef = selectedLinks.GetRef(linkIndex);
					bool bCanEmbedLink = linkFacade->CanEmbedLink(linkRef);
					bool bCanUnembedLink = linkFacade->CanUnembedLink(linkRef);

					ASSERT_MSG(!bCanEmbedLink || !bCanUnembedLink, "LinksUIPanelMenuComponent::UpdateActionStates - link cannot be both embeddable and unembeddable?");

					allEmbeddable &= bCanEmbedLink;
					allUnembeddable &= bCanUnembedLink;
					
					if (!allEmbeddable && !allUnembeddable)
						break;
				}

				bool enableAction = (allEmbeddable && !allUnembeddable) || (!allEmbeddable && allUnembeddable);
				if (enableAction)
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
				}
			}
			break;
        
            case kReplaceFPOWithOriginalLinkActionID:
            {
                PMString singleResourceToReplaceName;
                bool replacingAllInstances = Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget);
                
                // Now check if a selected child link has mulitple siblings for the same resource
                if (targetLinks.size() != 0)
                {
                    InterfacePtr<const ILink> link(targetLinks.GetRef(0), UseDefaultIID());
                    InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0), UseDefaultIID());
                    IDataBase* linkDB = targetResources.GetDataBase();
                    InterfacePtr<ILinkManager> iLinkMgr(linkDB, linkDB->GetRootUID(), UseDefaultIID());
                    UIDList allLinksToSameResource(linkDB);
                    iLinkMgr->QueryLinksByResourceUID(::GetUID(linkResource), true, allLinksToSameResource);
                    
                    UIDList uniqueUIDList = targetResources;
                    std::sort(uniqueUIDList.begin(), uniqueUIDList.end(), IDType<UID_tag>::less_IDType);
                    uniqueUIDList.erase(std::unique(uniqueUIDList.begin(), uniqueUIDList.end()), uniqueUIDList.end());
                    bool uniqueResource = (uniqueUIDList.size() == 1);
                    
                    if (replacingAllInstances || allLinksToSameResource.Length() > 1)
                    {
                        if (uniqueResource && allLinksToSameResource.Length() > 1)
                        {
                            InterfacePtr<const ILinkResource> linkResource(targetResources.GetRef(0), UseDefaultIID());
                            singleResourceToReplaceName.SetString(linkResource->GetShortName(true));
                        }
                        replacingAllInstances = true;
                    }
                    if (linkFacade->CanReplaceFPOWithOriginalLink(targetLinks.GetRef(0)))
                    {
                        listToUpdate->SetNthActionState(i, kEnabledAction);
                    }
                }
                else
                {
                    for (int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
                    {
                        if (linkFacade->CanReplaceFPOWithOriginalLink(targetLinks.GetRef(linkIndex)))
                        {
                            listToUpdate->SetNthActionState(i, kEnabledAction);
                            break;
                        }
                    }
                }
                if (nAction == kReplaceFPOWithOriginalLinkActionID)
                {
                    listToUpdate->SetNthActionName(i, GetDynamicMenuItemNameForAction(kReplaceFPOWithOriginalMenuItemEnum, replacingAllInstances, singleResourceToReplaceName));
                }
            }
                break;
            case kReplaceAllFPOWithOriginalLinksActionID:
            {
                if (ValidateCanReplaceAllFPOWithOriginalLinks(currentDoc) == kTrue)
                {
                    listToUpdate->SetNthActionState(i, kEnabledAction);
                    
                }
            }
                break;
            case kDownloadOriginalLinkActionID:
            {
                for (int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
                {
                    if (linkFacade->CanDownloadOriginalLink(targetLinks.GetRef(linkIndex)))
                    {
                        listToUpdate->SetNthActionState(i, kEnabledAction);
                        break;
                    }
                }
                
            }
                break;
                
            case kDownloadAllOriginalLinksActionID:
            {
                if (ValidateCanDownloadAllOriginalLinks(currentDoc) == kTrue)
                {
                    listToUpdate->SetNthActionState(i, kEnabledAction);
                    
                }
            }
                break;
		
		
			default:
				ASSERT_FAIL("asked to update action I don't know about!");
				break;
		}
	}
}

void LinksUIPanelMenuComponent::HandleNonLinkAction(ActionID actionID, IPMUnknown* widget)
{
	switch (actionID.Get()) 
	{
		case kAutosizeLinkInfoActionID:
		{
			Utils<ILinksUIUtils>()->ToggleLinkInfoSectionVisibility(true,true);		
		}
		break;
		case kShowHideLinkInfoActionID:
		{
			Utils<ILinksUIUtils>()->ToggleLinkInfoSectionVisibility(false,false);		
		}
		break;
		case kLinksUIEditColumnsActionID:
		{
			DisplayPrefsDialog(widget);
		}
		break;		
		case kLinksUIHideShowThumbnailActionID:
		{
#ifdef DEBUG
			InterfacePtr<const ILinkInfoProvider> headerProvider(Utils<ILinksUIUtils>()->QueryLinkInfoProviderFromHeaderWidget(widget));
			ASSERT_MSG(headerProvider,"Can't find header provider - how did we get here?");
#endif
				
			InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			linksUIPrefs->SetShowLinkThumbnail(!linksUIPrefs->GetShowLinkThumbnail());
		}
		break;
		case kLinksUIHideShowInfoThumbnailActionID:
		{
			InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			linksUIPrefs->SetShowLinkInfoThumbnail(!linksUIPrefs->GetShowLinkInfoThumbnail());
		}
		break;
		
		case kLinksUIRemoveColumnActionID:
		{
			InterfacePtr<const ILinkInfoProvider> headerProvider(Utils<ILinksUIUtils>()->QueryLinkInfoProviderFromHeaderWidget(widget));
			ASSERT_MSG(headerProvider,"Can't find header provider - how did we get here?");
				
			InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			int32 numShowing = linksUIPrefs->GetNumShowingInfoColumns();
			
			K2Vector<ILinkInfoProvider*> newShowingProviders;
			for(int index = 0; index < numShowing; ++index)
			{
				InterfacePtr<ILinkInfoProvider> infoProvider(linksUIPrefs->QueryNthShowingInfoColumn(index));
				if(infoProvider != headerProvider)
					newShowingProviders.push_back(infoProvider);
			}
			linksUIPrefs->SetShowingInfoColumns(newShowingProviders);
		}
		break;
		default: 
			ASSERT_FAIL("LinksUIPanelMenuComponent::HandleNonLinkAction - unknown menu id");
			break;
	}

}

void LinksUIPanelMenuComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{	
#pragma unused(ac,mousePoint)					
	switch (actionID.Get()) 
	{
		case kLinksUIEditColumnsActionID:
		case kLinksUIRemoveColumnActionID:
		case kLinksUIHideShowThumbnailActionID:
		case kLinksUIHideShowInfoThumbnailActionID:
		case kAutosizeLinkInfoActionID:
		case kShowHideLinkInfoActionID:
		{
			HandleNonLinkAction(actionID, widget);
			return;
		}
		break;
	}
	
	UIDList targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget);
	UIDList targetResources = GetLinkResourcesForMenuAction(widget);
	const IDocument* currentDoc = ac->GetContextDocument();
	Utils<Facade::ILinkFacade> linkFacade;

	switch (actionID.Get()) 
	{
		case kGenerateLinkReportActionID:
		{
			GenerateLinkReport(targetLinks);
		}
		break;
		case kCopySingleLinkInfoFieldActionID:
		{
			PMString controlUnderMouseString = GetStringFromControlUnderAtPoint(widget,mousePoint);
			WideString strToCopy(controlUnderMouseString);
			CopyStringToScrap(strToCopy);
		}
		break;
		
		case kCopyAllLinkInfoActionID:
		{
			CopyAllLinkInfo(targetLinks);
		}
		break;
		case kUpdateAllOutOfDateLinksActionID:
		{
			IDataBase* docDB = ::GetDataBase(currentDoc);
			UIDList resultUIDs(docDB);
			InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
			LinkQuery query; 
			query.SetResourceModState(ILink::kResourceModified); 
			query.SetLinkType(ILink::kImport); 
			query.SetLinkType(ILink::kExport); 
			query.SetLinkType(ILink::kBidirectional);
			
			linkMgr->QueryLinks(query, kIDLinkClientID, resultUIDs);
			linkFacade->UpdateLinksRecursively(resultUIDs, false, kMinimalUI, false);
		}
		break;
		case kAutoFindAllMissingLinksActionID:
		{
			IDataBase* docDB = ::GetDataBase(currentDoc);
			const IDFile* pPubDir(docDB->GetSysFile());
			if(!pPubDir)
				pPubDir = docDB->GetSysFileFromOpen();
			URI pubURI;
			if (pPubDir)
			{
				Utils<ILinkUtils>()->IDFileToResourceId(*pPubDir, pubURI);
				
				uint32 nFixed(0);
				ErrorCode findMissingErr(linkFacade->FindMissingResources(docDB, kIDLinkClientID, pubURI, true, false, kMinimalUI, nFixed));
				if(findMissingErr != kCancel && nFixed == 0)
				{
					PMString errString("#AutoFindFoundNothingAlert");
					CAlert::WarningAlertWithDontShowAgain(errString,kAutoFindAllMissingLinksActionID,false,CAlert::eInformationIcon);
				}
			}
		}
		break;

		case kCopyLinksActionID:
			{
				DoCopyLinks(targetLinks);
			}
			break;
		case kLicenseStockAssetActionID:
			{
				ASSERT_MSG(GetLinkResourcesForMenuAction(widget).Length() == 1, "Should only be enabled for single selected link resource");
				InterfacePtr<ILinkResource> linkResource(GetLinkResourcesForMenuAction(widget).GetRef(0), UseDefaultIID());
				if (linkResource)
				{
					URI linkURI = linkResource->GetURI();
					if (Utils<ICloudLibraryLinkedAssetUtils>()->IsCloudScheme(linkURI))
					{
						PMString elementRef(linkURI.GetComponent(URI::kPath));
						std::string elementRefStr(elementRef.GetUTF8String());
						if (Utils<ICloudLibraryLinkedAssetUtils>()->IsElementStock(elementRefStr) && !Utils<ICloudLibraryLinkedAssetUtils>()->IsElementStockLicensed(elementRefStr))
						{
							Utils<ICloudLibraryLinkedAssetUtils>()->LicenseStockElement(elementRefStr);
							InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
							if (usageTracking && usageTracking->IsUsageLoggingEnabled())
								usageTracking->LogUsageEvent(IDUsageTracking_kStockCategory, IDUsageTracking_kStockAssetPurchaseInitiate, "linksPanelFlyout/Context");
						}
					}
				}
			}
			break;
			
		
		case kRevealLinkInBridgeActionID:
		case kRevealLinkInBridgeSelectionActionID:
			{
				InterfacePtr<ILinkResource> linkResource;
				
				if(actionID == kRevealLinkInBridgeActionID)
				{
					ASSERT_MSG(GetLinkResourcesForMenuAction(widget).Length() == 1,"Should only be enabled for single selected resource");
					InterfacePtr<ILinkResource> panelSelLinkR(GetLinkResourcesForMenuAction(widget).GetRef(0),UseDefaultIID());
					linkResource = panelSelLinkR;
				}
				else
				{
					InterfacePtr<const ILink> selectedLink(Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout(),UseDefaultIID());
					InterfacePtr<ILinkResource> selectedRes(::GetDataBase(selectedLink),selectedLink->GetResource(),UseDefaultIID());
					linkResource.reset(selectedRes.forget());
				}

				if (linkResource)
				{
					if (linkResource->RevealInBridge() != kSuccess)
					{
						PMString errString("BrowseFailed");
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
						CAlert::InformationAlert(errString);
					}
				}
			}
			break;

		case kRevealLinkInCloudLibrariesActionID:
		case kRevealLinkInCloudLibrariesSelectionActionID:
			{
				InterfacePtr<ILinkResource> linkResource;
				if (actionID == kRevealLinkInCloudLibrariesActionID)
				{
					ASSERT_MSG(GetLinkResourcesForMenuAction(widget).Length() == 1,"Should only be enabled for single selected resource");
					InterfacePtr<ILinkResource> panelSelLinkR(GetLinkResourcesForMenuAction(widget).GetRef(0),UseDefaultIID());
					linkResource = panelSelLinkR;
				}
				else
				{
					InterfacePtr<const ILink> selectedLink(Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout(),UseDefaultIID());
					InterfacePtr<ILinkResource> selectedRes(::GetDataBase(selectedLink),selectedLink->GetResource(),UseDefaultIID());
					linkResource.reset(selectedRes.forget());
				}

				if (linkResource)
				{
					// Log initiation of "Reveal in CC libraries".
					LogCloudAssetActions(actionID, targetLinks);

					if (linkResource->RevealInCloudLibraries() != kSuccess)
					{
						PMString errString("RevealLinkError");
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
						CAlert::InformationAlert(errString);
					}
				}
			}
			break;
		case kRevealLinkInOSActionID:
		case kRevealLinkInOSSelectionActionID: 
			{
				InterfacePtr<ILinkResource> linkResource;
				
				if(actionID == kRevealLinkInOSActionID)
				{
					ASSERT_MSG(GetLinkResourcesForMenuAction(widget).Length() == 1,"Should only be enabled for single selected link resource");
					InterfacePtr<ILinkResource> panelSelLinkR(GetLinkResourcesForMenuAction(widget).GetRef(0),UseDefaultIID());
					linkResource = panelSelLinkR;
				}
				else
				{
					InterfacePtr<const ILink> selectedLink(Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout(),UseDefaultIID());
					InterfacePtr<ILinkResource> selectedRes(::GetDataBase(selectedLink),selectedLink->GetResource(),UseDefaultIID());
					linkResource.reset(selectedRes.forget());
				}

				if (linkResource)
				{
					if (linkResource->Reveal() != kSuccess)
					{
						PMString errString("RevealLinkError");
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
						CAlert::InformationAlert(errString);
					}
				}
			}
			break;
		case kGotoLinkActionID:
			{
				ASSERT_MSG(targetLinks.Length() == 1,"Should only be enabled for single selected link");
				InterfacePtr<IDataLinkAction> dlAction(targetLinks.GetRef(0), UseDefaultIID());
				if (dlAction)
				{
					PMString errString;
					if (dlAction->GotoLink(&errString) != kSuccess)	// failed
						if (!errString.IsEmpty())
						{
							ErrorUtils::PMSetGlobalErrorCode(kSuccess);
							CAlert::InformationAlert(errString);
						}
				}
			}
			break;
		case kLinksUICopyPathActionID:
		case kLinksUICopyPlatformPathActionID:
			{
				ASSERT_MSG(GetLinkResourcesForMenuAction(widget).Length() == 1,"Should only be enabled for single selected link resource");
				InterfacePtr<const ILinkResource> linkResource(GetLinkResourcesForMenuAction(widget).GetRef(0),UseDefaultIID());
				ASSERT_MSG(linkResource,"Can't do kLinksUICopyPathActionID without valid link resource. How is this enabled?");
				WideString pathStr = linkResource->GetLongName((actionID == kLinksUICopyPlatformPathActionID));
				CopyStringToScrap(pathStr);
			}
			break;
		case kEditOriginalLayoutSelectionActionID :
			{	
				UIDList targetLayoutLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
				UIDList targetLayoutResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLayoutLinks);
				InterfacePtr<ITemporaryDataForLogging> tempData(GetExecutionContextSession(), UseDefaultIID());
				const char* invokedFrom = NULL;
				ScopedTemporayLoggingData scopedTempData;
				bool16 isValuePresent = tempData->GetValue(kDesignLibraries, kDesignLibraries_EditOriginal_Invoker, &invokedFrom);
				if (!isValuePresent)
					scopedTempData.SetData(kDesignLibraries, kDesignLibraries_EditOriginal_Invoker, kMenuString);
				Utils<ILinksUIUtils>()->EditAllOriginals(targetLayoutLinks, targetLayoutResources);
			}
			break;
		case kLinksUIEditOriginalActionID:
			{
				// Log initiation of "Edit Original".
				LogCloudAssetActions(actionID, targetLinks);
				ScopedTemporayLoggingData tempData(kDesignLibraries, kDesignLibraries_EditOriginal_Invoker, kLinksPanel);
				Utils<ILinksUIUtils>()->EditAllOriginals(targetLinks, targetResources);
			}
			break;

		case kGoToSourceLayoutSelectionActionID :
			{	
				UIDList targetLayoutLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
				UIDList targetLayoutResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLayoutLinks);
				Utils<ILinksUIUtils>()->GoToAllSources(targetLayoutLinks, targetLayoutResources);
			}
			break;
		case kLinksUIGoToSourceActionID:
			{	
				Utils<ILinksUIUtils>()->GoToAllSources(targetLinks, targetResources);
			}
			break;
		
		case kLinksUIUpdateLinkActionID :
			{
				IDataBase *docDB = targetLinks.GetDataBase();
				
				UIDList uidsToUpdate(docDB);
				for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
				{
					if (linkFacade->CanUpdateLink(targetLinks.GetRef(linkIndex), false))
					{
						uidsToUpdate.push_back(targetLinks[linkIndex]);
					}
				}

				if ( !uidsToUpdate.IsEmpty())
				{
					UIDList newLinkUIDs;
					linkFacade->UpdateLinks(uidsToUpdate, false, kMinimalUI, false,&newLinkUIDs);
					Utils<ILinksUIUtils>()->SelectLinksInPanel(newLinkUIDs);
				}
			}
			break;
		case kLinksUIEmbedLinkActionID :
			{
				if(linkFacade->CanUnembedLink(targetLinks.GetRef(0)))
				{
					bool16 unembedDone = Utils<ILinksUIUtils>()->DoUnembedSelectedLinks(targetLinks, kTrue);

					// Link has been unembedded. Log highbeam data if CC assets has been unembedded.
					LogCloudAssetActions(actionID, targetLinks, unembedDone);
				}
				else if(linkFacade->CanEmbedLink(targetLinks.GetRef(0)))
				{				
					ErrorCode embedErr = linkFacade->EmbedLinks(targetLinks);
					if(embedErr != kSuccess)
					{
						PMString errString("#ErrorEmbeddingLink");
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
						CAlert::InformationAlert(errString);
					}
				}
				else
				{	// must be unlink
#ifdef DEBUG
					InterfacePtr<const ILink> debugLink(targetLinks.GetRef(0),UseDefaultIID());
					InterfacePtr<const ILinkResource> debugLinkResource(::GetDataBase(debugLink),debugLink->GetResource(),UseDefaultIID());
					ASSERT_MSG(debugLinkResource->GetStoreState() == ILinkResource::kContained,"Expecting this to be an unlink action, so the selected resources should all be contained...");
#endif
					bool16 endnotesICMA = kFalse;
					UID pageitemUID = kInvalidUID;
					UIDRef unlinkStoryRef(targetLinks.GetDataBase(), kInvalidUID);
					for (int32 i = 0; i < targetLinks.Length(); i++) {
						InterfacePtr<const ILink> targetLink(targetLinks.GetRef(0), UseDefaultIID());
						InterfacePtr<const ILinkObject> linkObj(::GetDataBase(targetLink), targetLink->GetObject(), UseDefaultIID());
						if (linkObj) {
							InterfacePtr<const ITextModel> textModel((ITextModel*)linkObj->QueryLinkedObject(IID_ITEXTMODEL));
							if (textModel && Utils<Facade::IEndnoteFacade>()->IsEndnoteAnchorOrEndnoteStoryInAssignment(::GetUIDRef(textModel))
								== kTrue) {
								unlinkStoryRef = ::GetUIDRef(textModel);
								endnotesICMA = kTrue;
								break;
							}
						}
					}
					if (endnotesICMA) {
						UIDList storyAsUIDList(unlinkStoryRef);
						Utils<Facade::IEndnoteFacade>()->AppendEndnoteRelatedStories(unlinkStoryRef, storyAsUIDList);
						ErrorCode errCode = linkFacade->DeleteLinksByObject(storyAsUIDList, true, false);
					}
					else {
						linkFacade->DeleteLinks(targetLinks, true, true);
					}
				}
			}
			break;
		case kLinksUIRelinkToFolderActionID:
			{
				targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget, kTrue);
				Utils<IRelinkUtils>()->DoRelinkToFolder(targetLinks);
			}
			break;
		case kLinksUIRelinkFileExtensionActionID:
			{
				Utils<IRelinkUtils>()->DoRelinkFileExtension(targetLinks);
			}
			break;
		case kLinksUIRelinkToCloudAssetActionID:
			{
				if (Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget))
				{
					Utils<IRelinkUtils>()->DoRelinkSelectedLinkResourcesWithCloudAssets(GetLinkResourcesForMenuAction(widget, kTrue), kIDLinkClientID);
				}
				else
				{
					targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget, kTrue);
				
					for (int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
					{
						if (!linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
							targetLinks.Remove(linkIndex);
					}
					ASSERT_MSG(targetLinks.Length() > 0, "Relink is enabled, but nothing is relinkable?");
					UIDList newLinkUIDs(targetLinks.GetDataBase());
					Utils<IRelinkUtils>()->DoRelinkSelectedLinksWithCloudAssets(targetLinks, kIDLinkClientID);
				}
				
				// Log initiation of "Relink from CC Libraries".
				LogCloudAssetActions(actionID, targetLinks);
			}
			break;
		case kLinksUIRelinkActionID:
			{
				if(Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget))
				{
					UIDList allResources = GetLinkResourcesForMenuAction(widget, kTrue);
					for (int linkResourceIndex = allResources.Length() - 1; linkResourceIndex >= 0; --linkResourceIndex)
					{
						if (!linkFacade->CanRelinkResource(allResources.GetRef(linkResourceIndex)))
							allResources.Remove(linkResourceIndex);
					}
					Utils<IRelinkUtils>()->DoRelinkSelectedLinkResources(allResources, kIDLinkClientID);

				}
				else
				{
					targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget, kTrue);

					for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
					{
						if (!linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
							targetLinks.Remove(linkIndex);
					}
					ASSERT_MSG(targetLinks.Length() > 0,"Relink is enabled, but nothing is relinkable?");
					UIDList newLinkUIDs(targetLinks.GetDataBase());
					Utils<IRelinkUtils>()->DoRelinkSelectedLinks(targetLinks,kIDLinkClientID,&newLinkUIDs);
					Utils<ILinksUIUtils>()->SelectLinksInPanel(newLinkUIDs);
				}
			}
			break;
        case kLinksUIRelinkToAALAssetActionID:
            {
                if (Utils<ILinksUIUtils>()->IsMenuActionEntirelyOnLinkResourceRows(widget))
                {
                    Utils<IRelinkUtils>()->DoRelinkSelectedLinkResourcesWithAALAssets(GetLinkResourcesForMenuAction(widget, kTrue), kIDLinkClientID);
                }
                else
                {
                    targetLinks = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget, kTrue);
                    
                    for (int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
                    {
                        if (!linkFacade->CanRelinkLink(targetLinks.GetRef(linkIndex)))
                            targetLinks.Remove(linkIndex);
                    }
                    ASSERT_MSG(targetLinks.Length() > 0, "Relink is enabled, but nothing is relinkable?");
                    UIDList newLinkUIDs(targetLinks.GetDataBase());
                    Utils<IRelinkUtils>()->DoRelinkSelectedLinksWithAALAssets(targetLinks, kIDLinkClientID);
                }
            }
            break;
		case kLinksUIPanelFileXMPInfoActionID:
			{
				ASSERT_MSG(targetLinks.Length() == 1,"Should only be enabled for single selected link");
				InterfacePtr<const ILink> oneLink(targetLinks.GetRef(0),UseDefaultIID());
				ShowXMPInfoForLink(oneLink);
			}
			break;
		case kRelinkAssetFromPropsPanelActionID:
		{
			UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
			InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
			InterfacePtr<ILayoutHitTestSuite> layoutHitTestSuite(Utils<ISelectionUtils>()->QueryLayoutHitTestSuite(iSelectionManager));
			InterfacePtr<ILayoutTarget> layoutTarget(layoutHitTestSuite, UseDefaultIID());
			UIDList selectedPageItems = layoutTarget->GetUIDList(kDontStripStandoffs);
			ASSERT(selectedLinks.Length() == 1 && selectedPageItems.Length() == 1);

			if (Utils<ICloudLibraryLinkedAssetUtils>()->IsCloudLibraryAsset(selectedPageItems.GetRef(0)))
			{
				Utils<IRelinkUtils>()->DoRelinkSelectedLinksWithCloudAssets(selectedLinks, kIDLinkClientID);
			}
			else
			{
				UIDList newLinkUIDs(selectedLinks.GetDataBase());
				Utils<IRelinkUtils>()->DoRelinkSelectedLinks(selectedLinks, kIDLinkClientID, &newLinkUIDs);
			}
		}
            break;
            
        // Replace single FPO link with original resource
        case kReplaceFPOWithOriginalLinkActionID:
        {
            UIDList uidsToReplace = GetAllReplacableLinks(currentDoc, targetLinks);
            
            if (!uidsToReplace.IsEmpty())
            {
                UIDList newLinkUIDs;
                linkFacade->ReplaceAllFPOWithOriginalLinks(uidsToReplace, kMinimalUI, kTrue /*Ignore errors*/, &newLinkUIDs);
                Utils<ILinksUIUtils>()->SelectLinksInPanel(newLinkUIDs);
            }
        }
        break;
            
        // Replace all FPO links with their original resource
        case kReplaceAllFPOWithOriginalLinksActionID:
        {
            UIDList allLinks = GetAllDocLinks(currentDoc);
            UIDList allReplacableLinks = GetAllReplacableLinks(currentDoc, allLinks);
            if (!allReplacableLinks.IsEmpty())
            {
                UIDList newLinkUIDs;
                linkFacade->ReplaceAllFPOWithOriginalLinks(allReplacableLinks, kMinimalUI, kTrue /*Ignore errors*/, &newLinkUIDs);
                Utils<ILinksUIUtils>()->SelectLinksInPanel(newLinkUIDs);
            }
        }
            break;
            
        // Download original resource of a single link
        case kDownloadOriginalLinkActionID:
        {
            UIDList uidsToDownload = GetAllDownloadableLinks(currentDoc, targetLinks);
            
            if (!uidsToDownload.IsEmpty())
            {
                linkFacade->DownloadAllOriginalLinks(uidsToDownload);
                Utils<ILinksUIUtils>()->SelectLinksInPanel(uidsToDownload);
            }
            
        }
            break;
            
            // Download original resource of multiple link
        case kDownloadAllOriginalLinksActionID:
        {
            UIDList allLinks = GetAllDocLinks(currentDoc);
            UIDList allDownloadableLinks = GetAllDownloadableLinks(currentDoc, allLinks);
            linkFacade->DownloadAllOriginalLinks(allDownloadableLinks);
        }
            break;

		case kEmbedLinkFromPropsPanelActionID:
		{
			UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();

			if (linkFacade->CanUnembedLink(selectedLinks.GetRef(0)))
			{
				bool16 unembedDone = Utils<ILinksUIUtils>()->DoUnembedSelectedLinks(selectedLinks, kTrue);

				// Link has been unembedded. Log highbeam data if CC assets has been unembedded.
				LogCloudAssetActions(actionID, targetLinks, unembedDone);
			}
			else if (linkFacade->CanEmbedLink(selectedLinks.GetRef(0)))
			{
				ErrorCode embedErr = linkFacade->EmbedLinks(selectedLinks);
				if (embedErr != kSuccess)
				{
					PMString errString("#ErrorEmbeddingLink");
					ErrorUtils::PMSetGlobalErrorCode(kSuccess);
					CAlert::InformationAlert(errString);
				}
			}
			break;
		}
		case kUpdateLinkFromPropsPanelActionID:
		{
			UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
			IDataBase *db = selectedLinks.GetDataBase();
			UIDList uidsToUpdate(db);
			
			if (linkFacade->CanUpdateLink(selectedLinks.GetRef(0), false))
			{
				uidsToUpdate.push_back(selectedLinks[0]);
			}

			if (!uidsToUpdate.IsEmpty())
			{
				UIDList newLinkUIDs;
				linkFacade->UpdateLinks(uidsToUpdate, false, kMinimalUI, false, &newLinkUIDs);
				Utils<ILinksUIUtils>()->SelectLinksInPanel(newLinkUIDs);
			}

			break;
		}
		case kUnlinkFromPropPanelActionID:
		{
			UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
#ifdef DEBUG
			InterfacePtr<const ILink> debugLink(selectedLinks.GetRef(0), UseDefaultIID());
			InterfacePtr<const ILinkResource> debugLinkResource(::GetDataBase(debugLink), debugLink->GetResource(), UseDefaultIID());
			ASSERT_MSG(debugLinkResource->GetStoreState() == ILinkResource::kContained, "Expecting this to be an unlink action, so the selected resources should all be contained...");
#endif
			bool16 endnotesICMA = kFalse;
			UID pageitemUID = kInvalidUID;
			UIDRef unlinkStoryRef(selectedLinks.GetDataBase(), kInvalidUID);
			for (int32 i = 0; i < selectedLinks.Length(); i++) {
				InterfacePtr<const ILink> targetLink(selectedLinks.GetRef(0), UseDefaultIID());
				InterfacePtr<const ILinkObject> linkObj(::GetDataBase(targetLink), targetLink->GetObject(), UseDefaultIID());
				if (linkObj) {
					InterfacePtr<const ITextModel> textModel((ITextModel*)linkObj->QueryLinkedObject(IID_ITEXTMODEL));
					if (textModel && Utils<Facade::IEndnoteFacade>()->IsEndnoteAnchorOrEndnoteStoryInAssignment(::GetUIDRef(textModel))
						== kTrue) {
						unlinkStoryRef = ::GetUIDRef(textModel);
						endnotesICMA = kTrue;
						break;
					}
				}
			}
			if (endnotesICMA) {
				UIDList storyAsUIDList(unlinkStoryRef);
				Utils<Facade::IEndnoteFacade>()->AppendEndnoteRelatedStories(unlinkStoryRef, storyAsUIDList);
				ErrorCode errCode = linkFacade->DeleteLinksByObject(storyAsUIDList, true, false);
			}
			else {
				linkFacade->DeleteLinks(selectedLinks, true, true);
			}
			break;
		}

		default: 
			ASSERT_FAIL("LinksUIPanelMenuComponent - unknown menu id");
			break;
	}
}

void LinksUIPanelMenuComponent::ShowXMPInfoForLink(const ILink* oneLink) const
{
	ASSERT_MSG (oneLink != nil,"ShowXMPInfoForLink can't do anything without a valid link!");
	InterfacePtr<const ILinkResource> linkResource(::GetDataBase(oneLink),oneLink->GetResource(),UseDefaultIID());
	PMString linkName = linkResource->GetShortName(true);
	URI resourceURI = linkResource->GetId();	// Allows DisplayMetaData to get xmp directly from file, thus supporting EXIF conversion (read only)

	InterfacePtr<IMetaDataAccess> iMetaDataAccess(Utils<ILinksUIUtils>()->QueryMetaDataAccessFromLink(oneLink));
    // ASSERT_MSG (iMetaDataAccess != nil,"Can't get IMetaDataAccess while handling kLinksUIPanelFileXMPInfoActionID!");
	// Get the title of the FileInfo dialog.
	PMString dialogTitle;
	if (linkName.IsEmpty())
	{
		// Cannot find link name, the title is "File Information".
		dialogTitle.SetCString("kFileInformation");
		dialogTitle.Translate();
	}
	else
	{
		// With a link name, the title is "File Information for [link name]".
		dialogTitle.SetCString("kFileInformationFor");
		dialogTitle.Translate();
		dialogTitle.Append(linkName);
	}

	Utils<IMetaDataUIUtils>()->DisplayMetaData(iMetaDataAccess, dialogTitle, kTrue /* read only */, &resourceURI, linkResource);
}

void LinksUIPanelMenuComponent::DisplayPrefsDialog(IPMUnknown* widget) const
{				
	InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());

	IDialog* columnsDialog = dialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(),kLinksUIPluginID, kViewRsrcType, kLinkColumnDialogResID), IDialog::kMovableModal);

	InterfacePtr<IControlView> widgetView(widget,UseDefaultIID());
	columnsDialog->Open(widgetView);
}

void LinksUIPanelMenuComponent::CopyStringToScrap(const WideString& pathStr) const
{
	InterfacePtr<IClipboardController> clipController(GetExecutionContextSession(), UseDefaultIID());
	if (clipController->IsValid())
	{
		clipController->PrepareForCopy();
		
		InterfacePtr<IDataExchangeHandler> textHandler(clipController->QueryHandler(kPMTextFlavor));
		clipController->SetActiveHandler(textHandler);

		InterfacePtr<ITextScrapData> scrapData(textHandler, UseDefaultIID());
		if(scrapData)
		{
			scrapData->Clear();

			InterfacePtr<ITextModel> model(scrapData->GetStoryRef(),UseDefaultIID());
			ASSERT_MSG(model !=nil,"EditboxScrapSuite::Copy - scrap model should not be nil!");


			// TextModel requires wide strings for Insert
			boost::shared_ptr<WideString>	stringData (new WideString(pathStr));
			InterfacePtr<ITextModelCmds> modelCmds(model, UseDefaultIID());
			InterfacePtr<ICommand> insertCmd(modelCmds->InsertCmd(0, stringData));
			CmdUtils::ProcessCommand(insertCmd);
		}
		clipController->CopyHasCompleted();
	}

}

void LinksUIPanelMenuComponent::DoCopyLinks(const UIDList& targetLinks) const
{
	static IDFile gDefaultCopyLocation;
	static bool gDefaultCopyLocationInited = false;

	InterfacePtr<IOpenFileDialog> folderDlg((IOpenFileDialog*)::CreateObject(kSelectFolderDialogBoss, IID_IOPENFILEDIALOG));
	ASSERT_MSG(folderDlg,"Failed to create folder dialog");
	if (folderDlg) 
	{
		IDFile directoryToUse;
		
		IDFile* defaultDir = nil;
		if ( gDefaultCopyLocationInited )
			defaultDir = &gDefaultCopyLocation;
		
		SysFileList selectedFolder;
		PMString titleString("#LinksUICopyLinksTitle");
		titleString.Translate();
		if (folderDlg->DoDialog(defaultDir, selectedFolder, kFalse, nil, &titleString)) 
		{
			if (selectedFolder.GetFileCount() == 1 ) 
			{
				directoryToUse = *selectedFolder.GetNthFile(0);
				gDefaultCopyLocation = directoryToUse;
				gDefaultCopyLocationInited = true;

				ErrorCode result = Utils<Facade::ILinkFacade>()->CopyLinksToFolder(targetLinks, directoryToUse, kTrue, kFullUI);
				if(result != kSuccess)
				{
					PMString errString("#CopyLinksFailedAlert");
					ErrorUtils::PMSetGlobalErrorCode(kSuccess);
					CAlert::InformationAlert(errString);
				}

			}
		}
	}
}				

void LinksUIPanelMenuComponent::GenerateLinkReport(const UIDList& targetLinks) const
{
	ASSERT_MSG(targetLinks.size() >= 1,"Should only be enabled for single selected link");
	
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	int32 numInfos = linksUIPrefs->GetNumShowingInfoColumns();
	PMString allInfoString;
	// generate the header row
	for(int32 i = 0; i < numInfos; ++i)
	{
		InterfacePtr<const ILinkInfoProvider> linkInfoProv(linksUIPrefs->QueryNthShowingInfoColumn(i));
		PMString infoDesc = linkInfoProv->GetInfoDescriptionString();
		infoDesc.Translate();
		allInfoString.Append(infoDesc);
		if(i != numInfos - 1)
			allInfoString.Append("\t");
	}
	allInfoString.Append("\r");

	// generate the row for each link
	for(uint32 linkIndex = 0; linkIndex < targetLinks.size(); ++linkIndex)
	{
		InterfacePtr<const ILink> link(targetLinks.GetRef(linkIndex),UseDefaultIID());
		InterfacePtr<const ILinkResource> linkResource(::GetDataBase(link),link->GetResource(),UseDefaultIID());
		for(int32 i = 0; i < numInfos; ++i)
		{
			InterfacePtr<const ILinkInfoProvider> linkInfoProv(linksUIPrefs->QueryNthShowingInfoColumn(i));
			PMString infoStr = linkInfoProv->GetUpdatedInfoForLink(link,linkResource,false);
			infoStr.Translate();
			allInfoString.Append(infoStr);
			if(i != numInfos - 1)
				allInfoString.Append("\t");
		}
		if(linkIndex != targetLinks.size() - 1)
			allInfoString.Append("\r");
	}
	WideString allInfoWString(allInfoString);
	CopyStringToScrap(allInfoWString);
}

void LinksUIPanelMenuComponent::CopyAllLinkInfo(const UIDList& targetLinks) const
{
	ASSERT_MSG(targetLinks.size() == 1,"Should only be enabled for single selected link");
	
	InterfacePtr<const ILink> link(targetLinks.GetRef(0),UseDefaultIID());
	InterfacePtr<const ILinkResource> linkResource(::GetDataBase(link),link->GetResource(),UseDefaultIID());
	
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	int32 numInfos = linksUIPrefs->GetNumMoreInfoProviders();
	PMString allInfoString;
	for(int32 i = 0; i < numInfos; ++i)
	{
		InterfacePtr<const ILinkInfoProvider> linkInfoProv(linksUIPrefs->QueryNthMoreInfoProvider(i));
		PMString infoStr = linkInfoProv->GetUpdatedInfoForLink(link,linkResource,false);
		if(!infoStr.IsEmpty())
		{
			infoStr.Translate();
			PMString infoDesc = linkInfoProv->GetInfoDescriptionString();
			infoDesc.Translate();
			allInfoString.Append(infoDesc);
			allInfoString.Append("\t");
			allInfoString.Append(infoStr);
			allInfoString.Append("\r");
		}
	}
	WideString allInfoWString(allInfoString);
	CopyStringToScrap(allInfoWString);

}

bool16 LinksUIPanelMenuComponent::ContainsDifferentParentStories(const UIDList& storyList) const
{
	UIDRef lastParentStoryRef(nil, kInvalidUID);
	int32 len = storyList.Length();
	for(int32 j = 0; j < len; ++j)
	{
		UIDRef parentStoryRef = storyList.GetRef(j);
		if((lastParentStoryRef.GetDataBase() == nil) && (lastParentStoryRef.GetUID() == kInvalidUID))
		{
			lastParentStoryRef = parentStoryRef;
		}
		else if(lastParentStoryRef != parentStoryRef)
		{
			return kTrue;
		}
	}
	return kFalse;
}

bool16 LinksUIPanelMenuComponent::ValidateCanEditStoryLinks(const UIDList& targetLinks) const
{
	bool16 ret = kTrue;
	Utils<Facade::ISharedContentFacade> sharedContentFacade;
	
	if(sharedContentFacade)
	{
		IDataBase* database = targetLinks.GetDataBase();
		UIDList parentStoryList(database);

		for(UIDList::const_iterator iter = targetLinks.begin(); iter != targetLinks.end(); ++iter)
		{
			UIDRef parentStoryRef = sharedContentFacade->GetResourceObjectForSharedStoryLink(UIDRef(database,*iter));
			UID parentUID = parentStoryRef.GetUID();
			if( (parentUID != kInvalidUID) && database->IsValidUID(parentUID) )
				parentStoryList.Append(parentUID);
		}
		
		int32 len = parentStoryList.Length();
		if(len>1 && ContainsDifferentParentStories(parentStoryList))
		{
			ret = kFalse;
		}
	}
	return ret;
}

// Logging of actions on cloud assets
// 1. Reveal in CC Libraries
// 2. Edit Original
// 3. Unembed
// 4. Relink from CC Libraries
void LinksUIPanelMenuComponent::LogCloudAssetActions(ActionID actionID, UIDList& targetLinks, bool16 unembedDone)
{
	InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
	if(!usageTracking || !usageTracking->IsUsageLoggingEnabled())
		return;
	
	if(targetLinks.Length() < 1)
		return;

	UID linkUID = targetLinks.At(0);
	IDataBase* db = targetLinks.GetDataBase();
	if(db)
	{
		InterfacePtr<ILink> link(db, linkUID, UseDefaultIID());
		InterfacePtr<ILinkResource> linkResource(db, link->GetResource(), UseDefaultIID());
		
		URI uri = linkResource->GetURI();
		// The URI for cloud asset is: cclibraries:<LibraryName>/<AssetName>
		if(Utils<ICloudLibraryLinkedAssetUtils>()->IsCloudScheme(uri))
		{
			switch(actionID.Get())
			{
			case kRevealLinkInCloudLibrariesActionID:
			case kRevealLinkInCloudLibrariesSelectionActionID:
				usageTracking->LogCCLibrariesUsageEvent(IDUsageTracking_kImageElementType, kRevealInCCInitiated);
				break;

			case kLinksUIEditOriginalActionID:
				usageTracking->LogCCLibrariesUsageEvent(IDUsageTracking_kImageElementType, kEditOriginalInitiated);
				break;
					
			case kLinksUIEmbedLinkActionID:
				usageTracking->LogCCLibrariesUsageEvent(IDUsageTracking_kImageElementType, kUnembedInitiated);
				if (unembedDone)
				{
					usageTracking->LogCCLibrariesUsageEvent(IDUsageTracking_kImageElementType, kUnembedSuccessful);
				}
				break;
					
			case kLinksUIRelinkToCloudAssetActionID:
				usageTracking->LogCCLibrariesUsageEvent(IDUsageTracking_kImageElementType, kRelinkInitiated);
				break;
			}
		}
	}
}

UIDList LinksUIPanelMenuComponent::GetAllDocLinks(const IDocument* currentDoc) const
{
	IDataBase* docDB = ::GetDataBase(currentDoc);
	if (!docDB) return UIDList();

	UIDList allLinks(docDB);
	InterfacePtr<const ILinkManager> linkMgr(docDB, docDB->GetRootUID(), UseDefaultIID());
	LinkQuery query;
	linkMgr->QueryLinks(query, kIDLinkClientID, allLinks);
	return allLinks;	
}


UIDList LinksUIPanelMenuComponent::GetAllDownloadableLinks(const IDocument* currentDoc, const UIDList& allLinks) const
{
    IDataBase* docDB = ::GetDataBase(currentDoc);
    UIDList allDownloadableLinks(docDB);
    Utils<Facade::ILinkFacade> linkFacade;
    
    for (int linkIndex = allLinks.Length() - 1; linkIndex >= 0; --linkIndex)
    {
        if (linkFacade->CanDownloadOriginalLink(allLinks.GetRef(linkIndex)))
        {
            allDownloadableLinks.push_back(allLinks[linkIndex]);
        }
    }
    
    return allDownloadableLinks;
}

UIDList LinksUIPanelMenuComponent::GetAllReplacableLinks(const IDocument* currentDoc, const UIDList& allLinks) const
{
    IDataBase* docDB = ::GetDataBase(currentDoc);
    UIDList allReplacableLinks(docDB);
    Utils<Facade::ILinkFacade> linkFacade;
    
    for (int linkIndex = allLinks.Length() - 1; linkIndex >= 0; --linkIndex)
    {
        if (linkFacade->CanReplaceFPOWithOriginalLink(allLinks.GetRef(linkIndex)))
        {
            allReplacableLinks.push_back(allLinks[linkIndex]);
        }
    }
    
    return allReplacableLinks;
}

bool16 LinksUIPanelMenuComponent::ValidateCanDownloadAllOriginalLinks(const IDocument* currentDoc) const
{
    IDataBase* database = ::GetDataBase(currentDoc);
    UIDList allLinks = GetAllDocLinks(currentDoc);
    Utils<Facade::ILinkFacade> linkFacade;
    bool16 validateCanDownloadAllOption = kFalse;
    
    for (UIDList::const_iterator iter = allLinks.begin(); iter != allLinks.end(); ++iter)
    {
        if (linkFacade->CanDownloadOriginalLink(UIDRef(database, *iter)))
        {
            validateCanDownloadAllOption = kTrue;
            break;
        }
    }
    return validateCanDownloadAllOption;
    
}

bool16 LinksUIPanelMenuComponent::ValidateCanReplaceAllFPOWithOriginalLinks(const IDocument* currentDoc) const
{
    IDataBase* database = ::GetDataBase(currentDoc);
    UIDList allLinks = GetAllDocLinks(currentDoc);
    Utils<Facade::ILinkFacade> linkFacade;
    bool16 validateCanReplaceAllOption = kFalse;
    
    for (UIDList::const_iterator iter = allLinks.begin(); iter != allLinks.end(); ++iter)
    {
        if (linkFacade->CanReplaceFPOWithOriginalLink(UIDRef(database, *iter)))
        {
            validateCanReplaceAllOption = kTrue;
            break;
        }
    }
    return validateCanReplaceAllOption;
}





