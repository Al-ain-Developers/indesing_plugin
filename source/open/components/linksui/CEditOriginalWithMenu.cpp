//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/CEditOriginalWithMenu.cpp $
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

#include "IActionManager.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "IDocument.h"
#include "IDynamicMenu.h"
#include "IMenuManager.h"
#include "IPanelControlData.h"
#include "IPMStream.h"
#include "ILinksUIPanelPrefs.h"
#include "ILink.h"

// ----- Includes -----

#include "ActionDefs.h"
#include "CActionComponent.h"
#include "CPMUnknown.h"
#include "AppInfo.h"
#include "PreferenceUtils.h"
#include "UIDList.h"

// ----- Utility files -----

#include "ILinksUIUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "LinksUIID.h"

//
// Base class
//
class CEditOriginalWithMenu : public CPMUnknown<IDynamicMenu>
{
	public:
		CEditOriginalWithMenu(IPMUnknown *boss);
		virtual ~CEditOriginalWithMenu();
		
		virtual void		RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget);
		void ReadWrite(IPMStream *s, ImplementationID i);

	protected:
		virtual ActionID 	GetMainActionID() const = 0;
		virtual ActionID    GetDynamicStartMenuID() const = 0;
		virtual ActionID    GetDynamicEndMenuID() const = 0;
		virtual void		GetMenuList(K2Vector<PMString>& menuList) = 0;
		virtual void		GetMenuItems(AppInfoList& appList, IPMUnknown* widget) = 0;

	private:
		PMString			GetEditorNameForMenu(const AppInfo& appInfo);

		ActionID	fHighestActionID;
		bool16		fHaveSeparator;
};

CEditOriginalWithMenu::CEditOriginalWithMenu(IPMUnknown *boss) : CPMUnknown<IDynamicMenu>(boss),
	fHighestActionID(kInvalidActionID),
	fHaveSeparator(kFalse)
{
}

CEditOriginalWithMenu::~CEditOriginalWithMenu()
{
}

void CEditOriginalWithMenu::ReadWrite(IPMStream *s, ImplementationID )
{
	// Track the highest actionID we use so we can call RemoveAction properly
	s->XferInt32((int32&)fHighestActionID);
	s->XferBool(fHaveSeparator);
}

void CEditOriginalWithMenu::RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget)
{
#ifdef DEBUG
	ASSERT(dynamicActionID == this->GetMainActionID());
#else
	#pragma unused(dynamicActionID)
#endif
	InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr,UseDefaultIID());
	InterfacePtr<const IActionComponent> actionComponent(this, UseDefaultIID());

	PreDirty();

	//
	// Remove all the actions(which removes all menus/shortcuts)
	//
	for (ActionID action = this->GetDynamicStartMenuID(); action <= fHighestActionID; action++)
	{
		if (actionMgr->IsValidAction(action))
		{
			actionMgr->RemoveAction(action);
		}
	}

	// Remove "Other..." at bottom of menu. It's always present.
	if (actionMgr->IsValidAction(kEditOriginalOtherAppActionID))
	{
		actionMgr->RemoveAction(kEditOriginalOtherAppActionID);
	}

	// List of menus we put the dynamic application names in
	K2Vector<PMString> menuList;
	GetMenuList(menuList);

	// Remove separators
	for (uint32 i = 0; i < menuList.size(); i++)
	{
		PMString menuString = menuList[i];
		menuString += ":-";
		
		// This is the separator between Adobe apps and regular apps
		if (fHaveSeparator)
			menuMgr->RemoveMenuItem(menuString, kEditOriginalSepActionID);

		// This is the separator between apps and "Other...". It's always present.
		menuMgr->RemoveMenuItem(menuString, kEditOriginalOtherAppSepActionID);
	}

	//
	// Add all of the editors to the list
	//
	if(1)
	{
		ActionID startID = this->GetDynamicStartMenuID();
		
		// List of items in menus (the actual editor names)
		AppInfoList appList;
		
		GetMenuItems(appList, widget);

		fHaveSeparator = kFalse;
		bool16 bFirstAppIsAdobeApp = kFalse;

		int32 appCount = appList.size();
		for (int32 j = 0; j < appCount; ++j)
		{
			fHighestActionID = startID + j;

			//
			// Since we only allocated a limited number of actionIDs
			//
			if (fHighestActionID < this->GetDynamicEndMenuID())
			{
				PMString editorName = GetEditorNameForMenu(appList[j]);

				// Track whether to add a separator between Adobe apps and other apps
				if (j == 0)
					bFirstAppIsAdobeApp = appList[j].GetIsAdobeApp();

				// Add the action
				actionMgr->AddAction(actionComponent, fHighestActionID, editorName, kEditMenuActionArea,kNormalAction,kCustomEnabling|kDisableIfLowMem,0,kFalse); // can't add shortcut.

				// Now add to each menu we want it in
				for (uint32 k = 0; k < menuList.size(); k++)
				{	
					PMString menuString = menuList[k];
					
					// Add separator between Adobe apps and regular apps.
					if (bFirstAppIsAdobeApp != appList[j].GetIsAdobeApp() && !fHaveSeparator)
					{
						PMString sepString(menuString);
						sepString += ":-";
						menuMgr->AddMenuItem(kEditOriginalSepActionID, sepString, j - 0.5, kFalse);
						if (k == menuList.size() - 1)
							fHaveSeparator = kTrue;
					}

					menuMgr->AddMenuItem(startID + j, menuString, j, kFalse);
				}
			}
			else
			{				
				break;
			}
		}

		// Now add "Other..." actionID to allow user to choose some other app not listed.
		actionMgr->AddAction(actionComponent, kEditOriginalOtherAppActionID, "#OtherApp", kEditMenuActionArea,kNormalAction,kCustomEnabling|kDisableIfLowMem,0,kFalse); // can't add shortcut.

		// Now add to each menu we want it in
		for (uint32 l = 0; l < menuList.size(); l++)
		{	
			PMString menuString = menuList[l];
			PMString sepString(menuString);
			sepString += ":-";
			
			// Add separator between list of apps and "Other..."
			menuMgr->AddMenuItem(kEditOriginalOtherAppSepActionID, sepString, appCount, kFalse);

			// Now add "Other..." to end of menu
			menuMgr->AddMenuItem(kEditOriginalOtherAppActionID, menuString, appCount + 1, kFalse);
		}

	}
}

PMString CEditOriginalWithMenu::GetEditorNameForMenu(const AppInfo& appInfo)
{
	PMString editorName;
	editorName.AppendW( kDontTranslateChar );    // do this so the menu won't be translated by the menumgr.
	editorName.Append(appInfo.GetDisplayName());

	// If version string isn't already part of display name, append it.
	PMString versionStr = appInfo.GetVersion();
	if (!editorName.Contains(versionStr) && 
		!editorName.Contains(PMString("CS")))
	{
		if (versionStr.CharCount())
		{
			editorName += " ";
			editorName += versionStr;
		}
	}

	// If it is the default editor, append " (Default)"
	if (appInfo.GetIsDefault())
	{
		editorName += " ";
		PMString defaultStr("kDefaultEditorStr", PMString::kTranslateDuringCall);
		editorName += defaultStr;
	}

	return editorName;
}


//
// This dynamic menu is for editing links selected in the links panel
//
class EditOriginalWithMenu : public CEditOriginalWithMenu
{
	public:
		EditOriginalWithMenu(IPMUnknown *boss) : CEditOriginalWithMenu(boss) { }
		virtual ~EditOriginalWithMenu() { }

	protected:
		ActionID 	GetMainActionID() const			{ return kEditOriginalWithActionID; }
		ActionID    GetDynamicStartMenuID() const	{ return kEditOriginalWithStartID; }
		ActionID    GetDynamicEndMenuID() const		{ return kEditOriginalWithEndID;}

		void GetMenuList(K2Vector<PMString>& menuList)
		{
			// These menus operate on a selected link item in links panel flyout or links panel context menu
			menuList.push_back("#LinksUIPanelMenu:#EditWithApp");
			menuList.push_back("RtMenuLinksUILinkItem:#EditWithApp");
		}
		void GetMenuItems(AppInfoList& appList, IPMUnknown* widget);

};

CREATE_PERSIST_PMINTERFACE(EditOriginalWithMenu, kEditOriginalWithMenuImpl)

void EditOriginalWithMenu::GetMenuItems(AppInfoList& appList, IPMUnknown* widget)
{
	UIDList targetLinks =  Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget);
	UIDList targetResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLinks);

	Utils<ILinksUIUtils>()->GetEditOriginalEditorList(appList, targetResources);
}


//
// This dynamic menu is for editing links in the layout selection
//
class EditOriginalSelectionWithMenu : public CEditOriginalWithMenu
{
	public:
		EditOriginalSelectionWithMenu(IPMUnknown *boss) : CEditOriginalWithMenu(boss) { }
		virtual ~EditOriginalSelectionWithMenu() { }

	protected:
		ActionID 	GetMainActionID() const			{ return kEditOriginalSelectionWithActionID; }
		ActionID    GetDynamicStartMenuID() const	{ return kEditOriginalSelectionWithStartID; }
		ActionID    GetDynamicEndMenuID() const		{ return kEditOriginalSelectionWithEndID; }

		void GetMenuList(K2Vector<PMString>& menuList)
		{
			// These menus operate on the layout selection
			menuList.push_back("Main:&Edit:#EditWithApp");
			menuList.push_back("RtMouseLayout:#EditWithApp");
		}

		void GetMenuItems(AppInfoList& appList, IPMUnknown* widget);
};

CREATE_PERSIST_PMINTERFACE(EditOriginalSelectionWithMenu, kEditOriginalSelectionWithMenuImpl)

void EditOriginalSelectionWithMenu::GetMenuItems(AppInfoList& appList, IPMUnknown* widget)
{
	#pragma unused(widget)

	UIDList targetLinks =  Utils<ILinksUIUtils>()->GetLinkUIDsOfSelectedItems();
	UIDList targetResources = Utils<ILinksUIUtils>()->GetResourcesOfLinks(targetLinks);

	Utils<ILinksUIUtils>()->GetEditOriginalEditorList(appList, targetResources);
}
