//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIPresetPopupDynamicMenu.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IActionComponent.h"
#include "IActionIDToUIDData.h"
#include "IActionManager.h"
#include "IAnimationAttributeSuite.h"
#include "IApplication.h"
#include "IDynamicMenu.h"
#include "IMenuManager.h"
#include "IMotionPresetMgr.h"
#include "IPMStream.h"
#include "ISelectionManager.h"
#include "ISession.h"

// ----- Includes -----

#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// ----- Utility files -----

#include "IMotionPresetUtils.h"
#include "ISelectionUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsID.h"


class AnimationUIPresetPopupDynamicMenu : public CPMUnknown<IDynamicMenu>
{
public:
	AnimationUIPresetPopupDynamicMenu(IPMUnknown* boss) : CPMUnknown<IDynamicMenu>(boss), fNumOldActions(0) {}

	virtual void RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget);
	void ReadWrite(IPMStream* stream, ImplementationID i);

private:
	int32 fNumOldActions;

	//	Need to cache submenu path name so that they can be removed first when rebuilding.
	//	Their position may change since custom presets now come before all default presets.
	std::vector<PMString> fSubmenuNames;
};

// =============================================================================
// *** AnimationUIPresetPopupDynamicMenu impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(AnimationUIPresetPopupDynamicMenu, kAnimationUIPresetPopupDynamicMenuImpl);

// -----------------------------------------------------------------------------

void AnimationUIPresetPopupDynamicMenu::RebuildMenu (ActionID dynamicActionID, IPMUnknown* widget) 
{
	ASSERT(dynamicActionID == kAnimationUIAction_PresetPopupMenuActionID);

	InterfacePtr<IMotionPresetMgr>	presetMgr(Utils<IMotionPresetUtils>()->QueryMotionPresetManager());
	int32 numPresets = presetMgr->GetNumPresets();

	// Nothing to be done; strange.
	if (numPresets == 0 && fNumOldActions == 0)
		return;

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication()); 
	InterfacePtr<IActionManager> actionMgr(app->QueryActionManager()); 
	InterfacePtr<IMenuManager> menuMgr(actionMgr,UseDefaultIID()); 

	InterfacePtr<IActionComponent> actionComp(this, UseDefaultIID()); 
	InterfacePtr<IActionIDToUIDData> idToUIDData(this, UseDefaultIID()); 

	PreDirty();

	PMString sepName("kAnimationUIPresetPopupMenu:-");
	ActionID firstActionID = kAnimationUIAction_FirstPresetDynamicActionID;
	ActionID lastActionID = kAnimationUIAction_LastPresetDynamicActionID;

	//	Remove menu items before rebuilding
	int32 i;
	for (i = 0; i < fNumOldActions; i++)
	{
		if (actionMgr->IsValidAction(firstActionID + i))
		{
			actionMgr->RemoveAction(firstActionID + i);
			idToUIDData->RemoveEntry(firstActionID + i);
		}
		else
			menuMgr->RemoveMenuItem(sepName, firstActionID + i);
	}

	for (std::vector<PMString>::iterator m = fSubmenuNames.begin (); 
		m != fSubmenuNames.end (); ++m)
	{
		menuMgr->RemoveMenuItem(*m, kInvalidActionID);
	}
	fSubmenuNames.clear ();

	fNumOldActions = 0;

	ActionID actionID = firstActionID;

	// Add first item to the preset list which is for removing applied animation or indicate
	// the user should "choose" an animation to apply it.
	actionMgr->AddAction(actionComp, actionID, "kAnimationUINone", kPaletteMenusAnimationUIActionArea, 
		kNormalAction, kCustomEnabling|kDisableIfNoFrontLayoutView, 0, kFalse); 
	menuMgr->AddMenuItem(actionID, "kAnimationUIPresetPopupMenu", actionID.Get(), kFalse); 
	idToUIDData->AddEntry(actionID, kInvalidUID);

	// Advance the action id and counter
	actionID++;
	fNumOldActions++;

	// Add the separator following the first item
	menuMgr->AddMenuItem(actionID, sepName, actionID.Get(), kFalse);

	// Advance the action id and counter
	actionID++;
	fNumOldActions++;

	// Add preset menu items
	bool16 addedCustomPresetSeparator(kFalse);
	PMString previousSubMenuName(kNullString);

	//	List of custom presets
	for (i = 0; i < numPresets && actionID <= lastActionID; i++)
	{
		if (!presetMgr->IsDefaultPreset (i))
		{
			PMString presetName;
			presetMgr->GetNthPresetName(i, presetName);

			PMString menuName("kAnimationUIPresetPopupMenu");

			// Add the preset menu item
			actionMgr->AddAction(actionComp, actionID, presetName, kPaletteMenusAnimationUIActionArea, 
				kNormalAction, kCustomEnabling|kDisableIfNoFrontLayoutView, 0, kFalse); 
			menuMgr->AddMenuItem(actionID, menuName, actionID.Get(), kFalse); 
			idToUIDData->AddEntry(actionID, presetMgr->GetNthPresetUID(i));

			// Advance the action id and counter
			actionID++;
			fNumOldActions++;
		}
	}

	// Put a separator below the custom presets (and above defaults)
	menuMgr->AddMenuItem(actionID, sepName, actionID.Get(), kFalse);
	addedCustomPresetSeparator = kTrue;

	// Advance the action id and counter
	actionID++;
	fNumOldActions++;

	//	Default presets.
	for (i = 0; i < numPresets && actionID <= lastActionID; i++)
	{
		//	If custom, skip. We already processed these.
		if (!presetMgr->IsDefaultPreset (i)) continue;

		PMString presetName;
		presetMgr->GetNthPresetName(i, presetName);

		PMString menuName("kAnimationUIPresetPopupMenu");

		PMString presetGroupName(kNullString);
		PMString presetTranslatedName(presetName);
		presetTranslatedName.Translate();
		Utils<IMotionPresetUtils>()->GetPresetGroupName(presetTranslatedName, presetGroupName);
		if (!presetGroupName.empty())
		{
			// Add the preset group sub-menu if it wasn't already added.
			menuName.Append(kMenuPathSeparator);
			menuName.Append(presetGroupName);

			PMString subMenuName(menuName);
			subMenuName.Append(kMenuPathSeparator);
			if (subMenuName != previousSubMenuName)
			{
				if (presetGroupName == "kBounceGroup")
				{
					// Put a separator above the "Bounce" group
					menuMgr->AddMenuItem(actionID, sepName, actionID.Get(), kFalse);

					// Advance the action id and counter
					actionID++;
					fNumOldActions++;
				}
				// Add the group sub-menu
				menuMgr->AddMenuItem(kInvalidActionID, subMenuName, actionID.Get(), kFalse); 
				previousSubMenuName = subMenuName;
				fSubmenuNames.push_back (subMenuName);

				// Advance the action id and counter
				actionID++;
				fNumOldActions++;
			}
		}

		// Add the preset menu item
		actionMgr->AddAction(actionComp, actionID, presetName, kPaletteMenusAnimationUIActionArea, 
			kNormalAction, kCustomEnabling|kDisableIfNoFrontLayoutView, 0, kFalse); 
		menuMgr->AddMenuItem(actionID, menuName, actionID.Get(), kFalse); 
		idToUIDData->AddEntry(actionID, presetMgr->GetNthPresetUID(i));

		// Advance the action id and counter
		actionID++;
		fNumOldActions++;
	}
} // end RebuildMenu()

// -----------------------------------------------------------------------------

void AnimationUIPresetPopupDynamicMenu::ReadWrite(IPMStream* stream, ImplementationID	i)
{	
	ASSERT_IF_WRITING_TO_DOCUMENT(stream);
	stream->XferInt32(fNumOldActions);

	int32 numSubmenus = static_cast<int32> (fSubmenuNames.size ());
	if (stream->IsReading ())
	{
		fSubmenuNames.clear ();
		stream->XferInt32(numSubmenus);
		for (int32 n = 0; n < numSubmenus; n++)
		{
			PMString submenuName;
			submenuName.ReadWrite (stream);
			fSubmenuNames.push_back (submenuName);
		}
	}
	else
	{
		stream->XferInt32(numSubmenus);
		for (std::vector<PMString>::iterator m = fSubmenuNames.begin (); 
			m != fSubmenuNames.end (); ++m)
		{
			m->ReadWrite (stream);
		}
	}

} // end ReadWrite()
