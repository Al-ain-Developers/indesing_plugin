//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactionsui/InCopyRecentDocsDynamicMenu.cpp $
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

//interfaces
#include "IDynamicMenu.h"
#include "IApplication.h"
#include "IDocumentList.h"
#include "IRecentFileListFacade.h"
#include "IMenuManager.h"
#include "IMenuUtils.h"
#include "IActionManager.h"
#include "IActionComponent.h"
#include "IPMStream.h"

// includes
#include "HelperInterface.h"
#include "Utils.h"
#include "AdobeMenuPositions.h"
#include "ActionDefs.h"
#include "Utils.h"

// IDs
#include "InCopyFileActionsUIID.h"

//system includes
#include <vector>

class InCopyRecentDocsDynamicMenu : public IDynamicMenu
{
public:
	InCopyRecentDocsDynamicMenu(IPMUnknown *boss);
	void ReadWrite(IPMStream *s, ImplementationID i);

	void RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget);
private:
	int32 fNumOldMenuEntries;
DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(InCopyRecentDocsDynamicMenu)

CREATE_PERSIST_PMINTERFACE(InCopyRecentDocsDynamicMenu, kInCopyRecentDocsDynamicMenuImpl )

InCopyRecentDocsDynamicMenu::InCopyRecentDocsDynamicMenu(IPMUnknown *boss) : 
	HELPER_METHODS_INIT(boss),fNumOldMenuEntries(0)
{
}

void InCopyRecentDocsDynamicMenu::ReadWrite(IPMStream *s, ImplementationID )
{
	ASSERT_IF_WRITING_TO_DOCUMENT(s);
	s->XferInt32(fNumOldMenuEntries);
}

/*
	Convert a filename to an itemname for the menu.  There are a number of issues to consider here:
	1) On Windows, we want to preface items with a keyboard accelerator number and a space
	2) Embedded ampersands within the filename must be "escaped" (turned into double ampersands)
	    so that they appear as ampersands on the menu and not as accelerators
	3) On the Macintosh (or in the case of Windows if we have an item past the 9th on the list w/o accelerator)
	    we are going to append a space onto the end of the name.  This ensures that there will be
	    no collision between any item names the MRU list might be adding and any existing menu entries.
	4) If we do not add a keyboard accelerator to the front and the item starts with a -, we need to add
	   a space to the front of the menu itemname so that it does not become a separator.
	5) If the name is too long, we need to rip out the middle of it and put a ... in so the menu stays
	   a reasonable size.
*/

void InCopyRecentDocsDynamicMenu::RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr,UseDefaultIID());

	InterfacePtr<IActionComponent> myComp(this,UseDefaultIID());

	// Find out the new count of items in the list
	
	int32 newCount = Utils<Facade::IRecentFileListFacade>() -> GetFileCount ();
			
			// remove all the old ones
	for (int32 i = 0; i < fNumOldMenuEntries; i++)
	{
		ASSERT_MSG(actionMgr -> IsValidAction(i + kFirstDocActionID), "We can't remove this action, because it doesn't exist");
		if (actionMgr -> IsValidAction(i + kFirstDocActionID))
			actionMgr -> RemoveAction (i + kFirstDocActionID);
	}

	if ( fNumOldMenuEntries == 0 && newCount > 0 )
	{
		// we have never added our menu...do it now.
		menuMgr -> AddMenuItem ( 0, "Main:&File:Open &Recent:",kOpenRecentMenuPosition, kFalse);
	}

	// If we added new menu items update count 
	
	if (newCount != fNumOldMenuEntries)
	{
		PreDirty ();
		fNumOldMenuEntries = newCount;
		
	}
	
	PMReal menuPos = 100.0;
	// gather filenames so we can check for duplicates. If we get duplicates, we will need to show the entire path
	// otherwise, we show only the filename.
	std::vector<AString> filenames(newCount);
	for (int32 k = 0; k < newCount ; k++)
	{
		ASSERT_MSG(k + kFirstDocActionID < kLastDocActionID,"Too many doc menu items - out of ID space!");
		// Get item name

		const IDFile *fileToAdd = Utils<Facade::IRecentFileListFacade>()->GetNthFile(k);
		ASSERT_MSG (fileToAdd != nil, "RecentDocsComponent::RebuildMenu() got nil file from FileList");

		if (!fileToAdd) break;

		filenames[k] = fileToAdd->GetNameStr();
	}


	// now we add the real menu items.
	for (int32 k = 0; k < newCount ; k++)
	{
		ASSERT_MSG(k + kFirstDocActionID < kLastDocActionID,"Too many doc menu items - out of ID space!");
		// Get item name
	
		const PMString *pathname = nil; 

		bool found = false;
		for(int32 kk = 0; kk < newCount; kk++)
		{
			// look for duplicate and if found, display the entire path
			if (kk != k && filenames[k] == filenames[kk])
			{
				// duplicate
				found = true;
				break;
			}
			
		}
		if (found)
		{
			pathname = Utils<Facade::IRecentFileListFacade>()->GetNthPathName (k);
			ASSERT_MSG (pathname != nil, "RecentDocsComponent::RebuildMenu() got nil file from FileList");
		}
		else 
		{
			pathname = new PMString(filenames[k].GrabWString(), filenames[k].UTF16Count());
		}
		
		PMString menuName = Utils<IMenuUtils>()->GetMenuNameFromFileName (*pathname, k + 1);

		if (!found)
		{
			delete pathname;
			pathname = nil;
		}

		

		actionMgr->AddAction( myComp, k + kFirstDocActionID,menuName, kFileMenuActionArea, kNormalAction, kDisableIfLowMem,0,kFalse);
		menuMgr -> AddMenuItem (k + kFirstDocActionID, "Main:&File:Open &Recent", menuPos, kFalse);
		menuPos += 100.0;
	}
}
