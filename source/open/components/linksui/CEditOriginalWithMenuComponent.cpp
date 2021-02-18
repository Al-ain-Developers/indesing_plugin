//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/CEditOriginalWithMenuComponent.cpp $
//  
//  Owner: Paul Sorrick
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

// ----- Interfaces -----

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IDynamicMenu.h"
#include "IPanelControlData.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "IOpenFileDialog.h"
#include "ISharedContentFacade.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "ILinksUIUtils.h"

// ----- Utility files -----

#include "ICloudLibraryLinkedAssetUtils.h"
#include "FileUtils.h"
#include "IPalettePanelUtils.h"
#include "Utils.h"
#include "UIDList.h"
#include "SysFileList.h"
#include "K2VectorBase.h"

// ----- ID.h files -----

#include "LinksUIID.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif

static const WideString kCloudAssetScheme("cclibraries");

class CEditOriginalWithMenuComponent : public CActionComponent
{
	public:
		CEditOriginalWithMenuComponent(IPMUnknown *boss);
		virtual ~CEditOriginalWithMenuComponent();

		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

	protected:
		virtual ActionID GetMainActionID() const = 0;
		virtual ActionID GetDynamicStartMenuID() const = 0;
		virtual ActionID GetDynamicEndMenuID() const = 0;
		virtual void DoMenuAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget) = 0;
		virtual ILink*	QueryLinkForMenuAction(IPMUnknown* widget) const = 0;
		virtual UIDList GetTargetLinks(IPMUnknown* widget) const = 0;
};

CEditOriginalWithMenuComponent::CEditOriginalWithMenuComponent(IPMUnknown *boss) : CActionComponent(boss)
{
}


CEditOriginalWithMenuComponent::~CEditOriginalWithMenuComponent()
{
}

void CEditOriginalWithMenuComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	if (actionID.Get() == this->GetMainActionID())
	{
		InterfacePtr<IDynamicMenu> dynamicMenu(this, UseDefaultIID());
		dynamicMenu->RebuildMenu(this->GetMainActionID(), nil);
	}
	else
	{
		this->DoMenuAction(ac, actionID, mousePoint, widget);
	}			
}

void CEditOriginalWithMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	#pragma unused(mousePoint,ac)

	Utils<Facade::ILinkFacade> linkFacade;
	UIDList targetLayoutLinks = GetTargetLinks(widget);

	//need to disable menu option for Shared Content Links in CS5.5
	Utils<Facade::ISharedContentFacade> sharedContentFacade;


	if (Utils<ILinksUIUtils>()->SomeCanEdit(targetLayoutLinks))
	{
		ActionID mainActionID = this->GetMainActionID();
		const int32 nCount = listToUpdate->Length();
		for (int32 i = 0; i < nCount; i++)
		{
			ActionID nAction = listToUpdate->GetNthAction(i);

			if (nAction >= this->GetDynamicStartMenuID() && nAction <= this->GetDynamicEndMenuID() )
			{
				listToUpdate->SetNthActionState(i,kEnabledAction);
			}
			else if (nAction == kEditOriginalOtherAppActionID)
			{
				int16 action = kEnabledAction;
				IDataBase* database = targetLayoutLinks.GetDataBase();
				for(UIDList::const_iterator iter = targetLayoutLinks.begin(); iter != targetLayoutLinks.end(); ++iter)
				{
					InterfacePtr<const ILink> iLink(database, *iter, UseDefaultIID()); 
					if( sharedContentFacade->IsSharedContentLink(iLink) )
					{
						action = kDisabled_Unselected;
						break;
					}
					else
					{
						IDataBase* database = targetLayoutLinks.GetDataBase();
						InterfacePtr<const ILinkResource> iResource(database, iLink->GetResource(), UseDefaultIID());

						URI uri = iResource->GetURI();
						if (Utils<ICloudLibraryLinkedAssetUtils>()->IsCloudScheme(uri))
						{
							action = kDisabled_Unselected;
							break;
						}
					}
				}

				listToUpdate->SetNthActionState(i,action);
			}
			else
			{
				listToUpdate->SetNthActionState(i,kDisabled_Unselected);
			}
		}
	}
}

//
// This menu component is for editing links selected in the links panel
//
class EditOriginalWithMenuComponent : public CEditOriginalWithMenuComponent
{
	public:
		EditOriginalWithMenuComponent(IPMUnknown *boss) : CEditOriginalWithMenuComponent(boss) { }
		virtual ~EditOriginalWithMenuComponent() { }

	protected:
		// This menu operates on a selected link item in links panel flyout or links panel context menu
		ActionID 	GetMainActionID() const			{ return kEditOriginalWithActionID; }
		ActionID	GetDynamicStartMenuID() const	{ return kEditOriginalWithStartID; }
		ActionID	GetDynamicEndMenuID() const		{ return kEditOriginalWithEndID;}
		void		DoMenuAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		ILink*	QueryLinkForMenuAction(IPMUnknown* widget) const;
		UIDList GetTargetLinks(IPMUnknown* widget) const;
};

CREATE_PMINTERFACE(EditOriginalWithMenuComponent, kEditOriginalWithMenuComponentImpl)


ILink* EditOriginalWithMenuComponent::QueryLinkForMenuAction(IPMUnknown* widget) const
{
	ILink* theLink = Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(widget);
	if(theLink == nil)
	{
		UIDList selectedResources = Utils<ILinksUIUtils>()->GetLinkResourcesSelectedInPanel();
		if(selectedResources.Length() == 1)
		{
			UIDList selectedLinksInPanel = Utils<ILinksUIUtils>()->GetLinksSelectedInPanel();
			ASSERT_MSG(selectedLinksInPanel.Length() >= 1,"How do we have 1 selected resource and 0 selected links?");
			theLink = (ILink*)selectedLinksInPanel.GetDataBase()->Instantiate(selectedLinksInPanel[0],IID_ILINK);
		}
	}
	return theLink;
}

UIDList EditOriginalWithMenuComponent::GetTargetLinks(IPMUnknown* widget) const
{
	return Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget);
}

static bool32 GetOtherAppFromUser(IDFile& file)
{
	InterfacePtr<IOpenFileDialog> openFileDialog((IOpenFileDialog*)::CreateObject(kOpenFileDialogBoss, IID_IOPENFILEDIALOG));
	if (!openFileDialog)
		return kFalse; // Out of memory.

#ifdef WINDOWS
	// Show application files in dialog.
	openFileDialog->AppendAllFilesToFilterList(); // Add "All Files, *.*" to the end of the filter list.
	PMString exe("exe");
	PMString applications("ApplicationFiles");
	openFileDialog->AddExtension(&applications, &exe);
	openFileDialog->SetDefaultFilter(applications);
#elif defined (MACINTOSH)
	PMString appString("app");
	openFileDialog->AddExtension(&appString, &appString);
#endif

	// Show the dialog and get a filename from the user.
	PMString title("#ChooseEditingApplication");
	title.Translate();
	SysFileList fileList;
	if (!openFileDialog->DoDialog(nil, fileList, kFalse /* allowMultipleFiles */, &title, nil /* infoMessage */))
		return kFalse; // user canceled

	// Get the file selected.
	file = *fileList.GetNthFile(0);

	return kTrue;
}



void EditOriginalWithMenuComponent::DoMenuAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(mousePoint,ac)
	UIDList targetLinks = GetTargetLinks(widget);
	UIDList targetResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLinks);

	AppInfoList appList;
	Utils<ILinksUIUtils>()->GetEditOriginalEditorList(appList, targetResources);

	int32 whichEditor = actionID - this->GetDynamicStartMenuID();
	ASSERT_MSG(whichEditor >= 0 && whichEditor < (int32)appList.size() || actionID == kEditOriginalOtherAppActionID, "Bad index");
	if (actionID == kEditOriginalOtherAppActionID)
	{
		IDFile file;
		if (GetOtherAppFromUser(file))
		{
			PMString path;
#ifdef WINDOWS
			FileUtils::IDFileToPMString(file, path);
#endif
#ifdef MACINTOSH			
			// Convert from "MacintoshHD:Applications:Safari.app" to "/Applications/Safari.app" type of path. There is probably a better way...

			CFURLRef appURL = MacFileUtils::AFileToCFURLRef(file);
			if (appURL != NULL)
			{
				CFStringRef app_str = ::CFURLCopyFileSystemPath(appURL, kCFURLPOSIXPathStyle);
				if (app_str)
				{
					path.SetCFString(app_str);
					::CFRelease(app_str);
				}
				::CFRelease(appURL);
			}
#endif

			AppInfo appInfo(path, "" /* displayName */, "" /* version */);
			Utils<ILinksUIUtils>()->EditAllOriginals(targetLinks, targetResources, appInfo);
		}
	}
	else if (whichEditor >= 0 && whichEditor < (int32)appList.size())
	{
		Utils<ILinksUIUtils>()->EditAllOriginals(targetLinks, targetResources, appList[whichEditor]);
	}
}

//
// This menu component is for editing links in the layout selection
//
class EditOriginalSelectionWithMenuComponent : public CEditOriginalWithMenuComponent
{
	public:
		EditOriginalSelectionWithMenuComponent(IPMUnknown *boss) : CEditOriginalWithMenuComponent(boss) { }
		virtual ~EditOriginalSelectionWithMenuComponent() { }

	protected:
		// This menu operates on the layout selection
		ActionID 	GetMainActionID() const			{ return kEditOriginalSelectionWithActionID; }
		ActionID	GetDynamicStartMenuID() const	{ return kEditOriginalSelectionWithStartID; }
		ActionID	GetDynamicEndMenuID() const		{ return kEditOriginalSelectionWithEndID; }
		void		DoMenuAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		ILink*	QueryLinkForMenuAction(IPMUnknown* widget) const;
		UIDList GetTargetLinks(IPMUnknown* widget) const;
};

CREATE_PMINTERFACE(EditOriginalSelectionWithMenuComponent, kEditOriginalSelectionWithMenuComponentImpl)

ILink* EditOriginalSelectionWithMenuComponent::QueryLinkForMenuAction(IPMUnknown* widget) const
{
	#pragma unused(widget)
	UIDRef linkSelectedInLayout = Utils<ILinksUIUtils>()->GetSingleLinkUIDRefSelectedInLayout();
	if(linkSelectedInLayout.GetUID() != kInvalidUID)
	{
		return (ILink*)linkSelectedInLayout.GetDataBase()->Instantiate(linkSelectedInLayout.GetUID(),IID_ILINK);
	}
	return nil;
}

UIDList EditOriginalSelectionWithMenuComponent::GetTargetLinks(IPMUnknown* widget) const
{
#pragma unused(widget)
	return Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
}


void EditOriginalSelectionWithMenuComponent::DoMenuAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(ac,mousePoint)
	UIDList targetLinks = GetTargetLinks(widget);
	UIDList targetResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLinks);

	AppInfoList appList;
	Utils<ILinksUIUtils>()->GetEditOriginalEditorList(appList, targetResources);

	int32 whichEditor = actionID - this->GetDynamicStartMenuID();
	ASSERT_MSG(whichEditor >= 0 && whichEditor < (int32)appList.size() || actionID == kEditOriginalOtherAppActionID, "Bad index");
	if (actionID == kEditOriginalOtherAppActionID)
	{
		IDFile file;
		if (GetOtherAppFromUser(file))
		{
			PMString path;
#ifdef WINDOWS
			FileUtils::IDFileToPMString(file, path);
#endif
#ifdef MACINTOSH				
			// Convert from "MacintoshHD:Applications:Safari.app" to "/Applications/Safari.app" type of path. There is probably a better way...
			CFURLRef appURL = MacFileUtils::AFileToCFURLRef(file);
			if (appURL != NULL)
			{
				CFStringRef app_str = ::CFURLCopyFileSystemPath(appURL, kCFURLPOSIXPathStyle);
				if (app_str)
				{
					path.SetCFString(app_str);
					::CFRelease(app_str);
				}

				::CFRelease(appURL);
			}

#endif
			AppInfo appInfo(path, "" /* displayName */, "" /* version */);
			Utils<ILinksUIUtils>()->EditAllOriginals(targetLinks, targetResources, appInfo);
		}
	}
	else if (whichEditor >= 0 && whichEditor < (int32)appList.size())
	{
		Utils<ILinksUIUtils>()->EditAllOriginals(targetLinks, targetResources, appList[whichEditor]);
	}
}
