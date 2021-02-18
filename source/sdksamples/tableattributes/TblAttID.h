//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tableattributes/TblAttID.h $
//  
//  Owner: Adobe Developer Technologies
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
//  
//  Defines IDs used by the TblAtt plug-in.
//  
//========================================================================================

#ifndef __TblAttID_h__
#define __TblAttID_h__

#include "SDKDef.h"

// Company:
#define kTblAttCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTblAttCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTblAttPluginName	"TableAttributes"			// Name of this plug-in.
#define kTblAttPrefixNumber	0x57350 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTblAttVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kTblAttAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTblAttPrefixNumber above to modify the prefix.)
#define kTblAttPrefix		RezLong(kTblAttPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTblAttStringPrefix	SDK_DEF_STRINGIZE(kTblAttPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTblAttPluginID, kTblAttPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kTblAttActionComponentBoss,	kTblAttPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblAttStringRegisterBoss,	kTblAttPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblAttMenuRegisterBoss,	kTblAttPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblAttActionRegisterBoss,	kTblAttPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTblAttPanelWidgetBoss,		kTblAttPrefix + 4)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblAttPanelRegisterBoss,	kTblAttPrefix + 5)
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITBLATTSELECTIONOBSERVER,	kTblAttPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ITBLATTWIDGETOBSERVER,		kTblAttPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kTblAttActionComponentImpl,		kTblAttPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTblAttSelectionObserverImpl,		kTblAttPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTblAttWidgetObserverImpl,			kTblAttPrefix + 2)
// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTblAttAboutActionID,					kTblAttPrefix + 0)
DECLARE_PMID(kActionIDSpace, kTblAttPanelWidgetActionID,			kTblAttPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTblAttSeparator1ActionID,				kTblAttPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTblAttPopupAboutThisActionID,			kTblAttPrefix + 3)
DECLARE_PMID(kActionIDSpace, kTblAttClearAllOverridesActionID,		kTblAttPrefix + 11)
// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kTblAttPanelWidgetID,						kTblAttPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kTblAttCellAttributesPanelTitleWidgetID,	kTblAttPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kTblAttRowAttributesPanelTitleWidgetID,	kTblAttPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kTblAttColAttributesPanelTitleWidgetID,	kTblAttPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kTblAttTableAttributesPanelTitleWidgetID,	kTblAttPrefix + 4) 

// Nudge x 4 for the cell attr
DECLARE_PMID(kWidgetIDSpace, kTblAttCellLeftNudgeWidgetID,		kTblAttPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTblAttCellRightNudgeWidgetID,		kTblAttPrefix + 6) 
DECLARE_PMID(kWidgetIDSpace, kTblAttCellTopNudgeWidgetID,		kTblAttPrefix + 7) 
DECLARE_PMID(kWidgetIDSpace, kTblAttCellBottomNudgeWidgetID,	kTblAttPrefix + 8) 
 
// Nudge x 2 for row and col
DECLARE_PMID(kWidgetIDSpace, kTblAttRowNudgeWidgetID,			kTblAttPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kTblAttColNudgeWidgetID,			kTblAttPrefix + 10) 

// Nudge x 4 for the table
DECLARE_PMID(kWidgetIDSpace, kTblAttTableLeftNudgeWidgetID,		kTblAttPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kTblAttTableRightNudgeWidgetID,	kTblAttPrefix + 12) 
DECLARE_PMID(kWidgetIDSpace, kTblAttTableTopNudgeWidgetID,		kTblAttPrefix + 13) 
DECLARE_PMID(kWidgetIDSpace, kTblAttTableBottomNudgeWidgetID,	kTblAttPrefix + 14) 

// x 4 for the cell attr
DECLARE_PMID(kWidgetIDSpace, kTblAttCellLeftComboBoxWidgetID,		kTblAttPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTblAttCellRightComboBoxWidgetID,		kTblAttPrefix + 16) 
DECLARE_PMID(kWidgetIDSpace, kTblAttCellTopComboBoxWidgetID,		kTblAttPrefix + 17) 
DECLARE_PMID(kWidgetIDSpace, kTblAttCellBottomComboBoxWidgetID,		kTblAttPrefix + 18) 
 
//  x 2 for row and col
DECLARE_PMID(kWidgetIDSpace, kTblAttRowComboBoxWidgetID,			kTblAttPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kTblAttColComboBoxWidgetID,			kTblAttPrefix + 20) 

//  x 4 for the table
DECLARE_PMID(kWidgetIDSpace, kTblAttTableLeftComboBoxWidgetID,		kTblAttPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kTblAttTableRightComboBoxWidgetID,		kTblAttPrefix + 22) 
DECLARE_PMID(kWidgetIDSpace, kTblAttTableTopComboBoxWidgetID,		kTblAttPrefix + 23) 
DECLARE_PMID(kWidgetIDSpace, kTblAttTableBottomComboBoxWidgetID,	kTblAttPrefix + 24) 



// "About Plug-ins" sub-menu:
#define kTblAttAboutMenuKey			kTblAttStringPrefix "kTblAttAboutMenuKey"
#define kTblAttAboutMenuPath		kSDKDefStandardAboutMenuPath kTblAttCompanyKey

// "Plug-ins" sub-menu:
#define kTblAttPluginsMenuKey 		kTblAttStringPrefix "kTblAttPluginsMenuKey"
#define kTblAttPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kTblAttCompanyKey kSDKDefDelimitMenuPath kTblAttPluginsMenuKey

// Menu item keys:
#define kTblAttClearAllOverridesMenuItemKey		kTblAttStringPrefix "kTblAttClearAllOverridesMenuItemKey"

// Other StringKeys:
#define kTblAttAboutBoxStringKey				kTblAttStringPrefix "kTblAttAboutBoxStringKey"
#define kTblAttPanelTitleKey					kTblAttStringPrefix	"kTblAttPanelTitleKey"
#define kTblAttStaticTextKey					kTblAttStringPrefix	"kTblAttStaticTextKey"
#define kTblAttInternalPopupMenuNameKey			kTblAttStringPrefix	"kTblAttInternalPopupMenuNameKey"
#define kTblAttTargetMenuPath					kTblAttInternalPopupMenuNameKey

// Misc
#define kTblAttCellAttributesPanelTitleKey	kTblAttStringPrefix "TblAttCellAttributesPanelTitleKey"
#define kTblAttRowAttributesPanelTitleKey	kTblAttStringPrefix "TblAttRowAttributesPanelTitleKey"
#define kTblAttColAttributesPanelTitleKey	kTblAttStringPrefix "TblAttColAttributesPanelTitleKey"
#define kTblAttTableAttributesPanelTitleKey	kTblAttStringPrefix "TblAttTableAttributesPanelTitleKey"

#define kTblAttCellLeftKey		kTblAttStringPrefix "kTblAttCellLeftKey"
#define kTblAttCellRightKey		kTblAttStringPrefix "kTblAttCellRightKey"
#define kTblAttCellTopKey		kTblAttStringPrefix "kTblAttCellTopKey"
#define kTblAttCellBottomKey	kTblAttStringPrefix "kTblAttCellBottomKey"

#define kTblAttRowKey			kTblAttStringPrefix "kTblAttRowKey"
#define kTblAttColKey			kTblAttStringPrefix "kTblAttColKey"

#define kTblAttTableLeftKey		kTblAttStringPrefix "kTblAttTableLeftKey"
#define kTblAttTableRightKey	kTblAttStringPrefix "kTblAttTableRightKey"
#define kTblAttTableTopKey		kTblAttStringPrefix "kTblAttTableTopKey"
#define kTblAttTableBottomKey	kTblAttStringPrefix "kTblAttTableBottomKey"


// Menu item positions:
#define kTblAttClearAllOverridesMenuItemPosition		1.0
#define	kTblAttSeparator1MenuItemPosition				10.0
#define kTblAttAboutThisMenuItemPosition				11.0

// Initial data format version numbers
#define kTblAttFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kTblAttFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kTblAttCurrentMajorFormatNumber kTblAttFirstMajorFormatNumber // most recent major format change
#define kTblAttCurrentMinorFormatNumber kTblAttFirstMinorFormatNumber // most recent minor format change

#endif // __TblAttID_h__
// End, TblAttID.h.



