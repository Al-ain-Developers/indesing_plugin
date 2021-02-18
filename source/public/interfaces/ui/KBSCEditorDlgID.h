//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/KBSCEditorDlgID.h $
//  
//  Owner: Jonathan W. Brown
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

#ifndef __KBSCEditorDlgID__
#define __KBSCEditorDlgID__

#include "CrossPlatformTypes.h" // for RezLong
#include "IDFactory.h"

#define kKBSCEditorDlgPrefix				RezLong(0x10c00)

// PluginID
#define kKBSCEditorDlgPluginName 			"Shortcut Editor Dialog"
DECLARE_PMID(kPlugInIDSpace, kKBSCEditorDlgPluginID, kKBSCEditorDlgPrefix + 1)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kKBSCEditorDlgBoss, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kClassIDSpace, kKBSCEditorDlgMenuActionBoss, kKBSCEditorDlgPrefix + 2)
DECLARE_PMID(kClassIDSpace, kKBSCConversionBoss, kKBSCEditorDlgPrefix + 3)
DECLARE_PMID(kClassIDSpace, kKBSCAssignButtonWidgetBoss, kKBSCEditorDlgPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kKBSCActionsListWidgetBoss, kKBSCEditorDlgPrefix + 6)
DECLARE_PMID(kClassIDSpace, kKBSCShortcutsListWidgetBoss, kKBSCEditorDlgPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kKBSCCurrentActionTextWidgetBoss, kKBSCEditorDlgPrefix + 9)
DECLARE_PMID(kClassIDSpace, kKBSCSetsComboWidgetBoss, kKBSCEditorDlgPrefix + 10)
DECLARE_PMID(kClassIDSpace, kKBSCProductAreasComboWidgetBoss, kKBSCEditorDlgPrefix + 11)
DECLARE_PMID(kClassIDSpace, kKBSCDuplicateButtonWidgetBoss, kKBSCEditorDlgPrefix + 12)
DECLARE_PMID(kClassIDSpace, kKBSCDeleteButtonWidgetBoss, kKBSCEditorDlgPrefix + 13)
DECLARE_PMID(kClassIDSpace, kKBSCSaveButtonWidgetBoss, kKBSCEditorDlgPrefix + 14)
DECLARE_PMID(kClassIDSpace, kKBSCExportButtonWidgetBoss, kKBSCEditorDlgPrefix + 15)

DECLARE_PMID(kClassIDSpace, kKBSCDuplicateDlgBoss, kKBSCEditorDlgPrefix + 16)
//gap
DECLARE_PMID(kClassIDSpace, kKBSCSetCurrentSetCmdBoss, kKBSCEditorDlgPrefix + 18)
DECLARE_PMID(kClassIDSpace, kKBSCRemoveButtonWidgetBoss, kKBSCEditorDlgPrefix + 19)
DECLARE_PMID(kClassIDSpace, kKBSCSettingsMigrationServiceProviderBoss,	kKBSCEditorDlgPrefix + 20)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kKBSCEditorDlgId, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kKBSCActionsListWidgetId, kKBSCEditorDlgPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kKBSCShortcutsListWidgetId, kKBSCEditorDlgPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kKBSCShortcutEditBoxWidgetId, kKBSCEditorDlgPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kKBSCCurrentActionTextWidgetId, kKBSCEditorDlgPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kKBSCAssignButtonWidgetId, kKBSCEditorDlgPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kKBSCAreaRowWidgetId, kKBSCEditorDlgPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kKBSCSetsComboWidgetId, kKBSCEditorDlgPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kKBSCProductAreasComboWidgetId, kKBSCEditorDlgPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kKBSCDuplicateButtonWidgetId, kKBSCEditorDlgPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kKBSCDeleteButtonWidgetId, kKBSCEditorDlgPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kKBSCSaveButtonWidgetId, kKBSCEditorDlgPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kKBSCExportButtonWidgetId, kKBSCEditorDlgPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kKBSCDuplicateDlgId, kKBSCEditorDlgPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kKBSCNewNameEditBoxWidgetId, kKBSCEditorDlgPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kKBSCBasedOnComboWidgetId, kKBSCEditorDlgPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kKBSCSetLabelWidgetId, kKBSCEditorDlgPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kProductAreaLabelWidgetId, kKBSCEditorDlgPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kCommandsLabelWidgetId, kKBSCEditorDlgPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kKBSCGroupWidgetId, kKBSCEditorDlgPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPressLabelWidgetId, kKBSCEditorDlgPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kCurrentLabelWidgetId, kKBSCEditorDlgPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kKBSCGroup2WidgetId, kKBSCEditorDlgPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kNameLabelWidgetId, kKBSCEditorDlgPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kBasedOnLabelWidgetId, kKBSCEditorDlgPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kKBSCRemoveButtonWidgetId, kKBSCEditorDlgPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kKBSCContextListWidgetID, kKBSCEditorDlgPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kContextLabelWidgetID, kKBSCEditorDlgPrefix + 28)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kKBSCEditorDlgMenuAction, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kKBSCEditorDlgController, kKBSCEditorDlgPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kKBSCDataImpl, kKBSCEditorDlgPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kKBSCShortcutsListObserver, kKBSCEditorDlgPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kKBSCAssignButtonObserverImpl, kKBSCEditorDlgPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kKBSCCurrentActionTextObserver, kKBSCEditorDlgPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kKBSCActionListObserver, kKBSCEditorDlgPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kKBSCAreaComboObserver, kKBSCEditorDlgPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kKBSCDeleteButtonObserver, kKBSCEditorDlgPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kKBSCDuplicateButtonObserver, kKBSCEditorDlgPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kKBSCSetComboObserver, kKBSCEditorDlgPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kKBSCExportButtonObserver, kKBSCEditorDlgPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kKBSCSaveButtonObserver, kKBSCEditorDlgPrefix + 13)
//gap
DECLARE_PMID(kImplementationIDSpace, kKBSCSetData, kKBSCEditorDlgPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kKBSCPreferences, kKBSCEditorDlgPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kKBSCDuplicateDlgController, kKBSCEditorDlgPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kKBSCDuplicateDlgData, kKBSCEditorDlgPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kKBSCAdd, kKBSCEditorDlgPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kKBSCRemove, kKBSCEditorDlgPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kKBSCSetCurrentSetCmd, kKBSCEditorDlgPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kKBSCSetCurrentSetCmdData, kKBSCEditorDlgPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kKBSCSetsManager, kKBSCEditorDlgPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kKBSCDuplicateSet, kKBSCEditorDlgPrefix + 25)
//gap
DECLARE_PMID(kImplementationIDSpace, kShortcutListLooseFocus, kKBSCEditorDlgPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kKBSCShortcutListBoxEH, kKBSCEditorDlgPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kKBSCListBoxControllerImpl, kKBSCEditorDlgPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kShortcutListGetFocus, kKBSCEditorDlgPrefix + 30)

//gap
DECLARE_PMID(kImplementationIDSpace, kKBSCRemoveButtonObserverImpl, kKBSCEditorDlgPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kKBSCRemoveButtonViewImpl, kKBSCEditorDlgPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kKBSCSettingsMigrationImpl,		kKBSCEditorDlgPrefix + 34)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCDATA, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCSETDATA, kKBSCEditorDlgPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCPREFERENCES, kKBSCEditorDlgPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCDUPLICATEDLGDATA, kKBSCEditorDlgPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCSETCURRENTSETCMDDATA, kKBSCEditorDlgPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCSETSMANAGER, kKBSCEditorDlgPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCDUPLICATESET, kKBSCEditorDlgPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IKBSCEDITORMSG, kKBSCEditorDlgPrefix + 9)

// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kKBSCCantWriteDisk, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCantReadSetFromOtherPlateform, kKBSCEditorDlgPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kSetFormatWrongOrCorrupt, kKBSCEditorDlgPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kShortcutSetStillExists, kKBSCEditorDlgPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kKBSCSetFormatTooRecent, kKBSCEditorDlgPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kKBSCSetFolderIsFile, kKBSCEditorDlgPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kKBSCCantCreateSetFolder, kKBSCEditorDlgPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kKBSCEmptyName, kKBSCEditorDlgPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kKBSCExistName, kKBSCEditorDlgPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kKBSCToLongName, kKBSCEditorDlgPrefix + 10	)
DECLARE_PMID(kErrorIDSpace, kKBSCBadSyntaxName, kKBSCEditorDlgPrefix + 11)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kKBSCEditorDlgActionID, kKBSCEditorDlgPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSeparatorOfDoomActionID, kKBSCEditorDlgPrefix + 2)

#endif	// __KBSCEditorDlgID__

