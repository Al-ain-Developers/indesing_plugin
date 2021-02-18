//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUIID.h $
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
//  Defines IDs used by the DataUpdaterUI plug-in.
//  
//========================================================================================

#ifndef __DataUpdaterUIID_h__
#define __DataUpdaterUIID_h__

#include "SDKDef.h"

// Company:
#define kDataUpdaterUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDataUpdaterUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDataUpdaterUIPluginName	"XMLDataUpdaterUI"			// Name of this plug-in.
#define kDataUpdaterUIPrefixNumber	0xd9b00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDataUpdaterUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kDataUpdaterUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDataUpdaterUIPrefixNumber above to modify the prefix.)
#define kDataUpdaterUIPrefix		RezLong(kDataUpdaterUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDataUpdaterUIStringPrefix	SDK_DEF_STRINGIZE(kDataUpdaterUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDataUpdaterUIPluginID, kDataUpdaterUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDataUpdaterUIActionComponentBoss,	kDataUpdaterUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kDataUpdaterUIPanelWidgetBoss,	kDataUpdaterUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDataUpdaterUITreeViewWidgetBoss,	kDataUpdaterUIPrefix + 6)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAUPDATERUIDATAMODEL,	kDataUpdaterUIPrefix + 0)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterUIActionComponentImpl,			kDataUpdaterUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterUITVWidgetMgrImpl,				kDataUpdaterUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterUITVHierarchyAdapterImpl,		kDataUpdaterUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterUIDataModelImpl, kDataUpdaterUIPrefix + 13)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDataUpdaterUIAboutActionID,				kDataUpdaterUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kDataUpdaterUIInsertDataActionID,		kDataUpdaterUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDataUpdaterUILoadDataActionID,		kDataUpdaterUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDataUpdaterUIInsertAllDataActionID,			kDataUpdaterUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDataUpdaterUIUpdateDataActionID,		kDataUpdaterUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kDataUpdaterUIPanelWidgetActionID,		kDataUpdaterUIPrefix + 5)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUIPanelWidgetID,					kDataUpdaterUIPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUITreeViewWidgetID,				kDataUpdaterUIPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUINodeWidgetId,					kDataUpdaterUIPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUINodeNameWidgetID,				kDataUpdaterUIPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUIElementWidgetId,				kDataUpdaterUIPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kDataUpdaterUITextMessageWidgetID,			kDataUpdaterUIPrefix + 7)


// Menu item keys:
#define kDataUpdaterUILoadDataMenuItemKey				kDataUpdaterUIStringPrefix "kDataUpdaterUILoadDataMenuItemKey"
#define kDataUpdaterUIInsertDataMenuItemKey			kDataUpdaterUIStringPrefix "kDataUpdaterUIInsertDataMenuItemKey"
#define kDataUpdaterUIInsertAllDataMenuItemKey			kDataUpdaterUIStringPrefix "kDataUpdaterUIInsertAllDataMenuItemKey"
#define kDataUpdaterUIUpdateDataMenuItemKey			kDataUpdaterUIStringPrefix "kDataUpdaterUIUpdateDataMenuItemKey"

// Error strings
#define kDataUpdaterUIErrorFileOpen			kDataUpdaterUIStringPrefix	"kDataUpdaterUIErrorFileOpen"
#define kDataUpdaterUIErrorInsertAllSequenceFailed				kDataUpdaterUIStringPrefix "kDataUpdaterUIErrorInsertAllSequenceFailed"
#define kDataUpdaterUIErrorUpdateDataFailed kDataUpdaterUIStringPrefix "kDataUpdaterUIErrorUpdateDataFailed"


// Other StringKeys:
#define kDataUpdaterUIInternalPopupMenuNameKey			kDataUpdaterUIStringPrefix	"kDataUpdaterUIInternalPopupMenuNameKey"
#define kDataUpdaterUIAboutBoxStringKey				kDataUpdaterUIStringPrefix "kDataUpdaterUIAboutBoxStringKey"
#define kDataUpdaterUISelectDataFileStringKey kDataUpdaterUIStringPrefix "kDataUpdaterUISelectDataFileStringKey"
#define kDataUpdaterUIPanelTitleKey					kDataUpdaterUIStringPrefix	"kDataUpdaterUIPanelTitleKey"
#define kDataUpdaterUITargetMenuPath kDataUpdaterUIInternalPopupMenuNameKey
#define kDataUpdaterUICSVFilterStringKey			kDataUpdaterUIStringPrefix "kDataUpdaterUICSVFilterStringKey" //Comma separated(*.csv)

// Menu item positions:
#define kDataUpdaterUILoadDataMenuItemPosition			1.0
#define	kDataUpdaterUIInsertDataMenuItemPosition			2.0
#define kDataUpdaterUIInsertAllDataMenuItemPosition				3.0
#define kDataUpdaterUIUpdateDataMenuItemPosition				4.0
#define kDataUpdaterUIAboutThisMenuItemPosition			11.0

#define kDataUpdaterUINodeWidgetRsrcID 	1200


// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kDataUpdaterUIInitialMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kDataUpdaterUIInitialMinorFormat		kSDKDef_50_PersistMinorVersionNumber

// Format IDs for the PluginVersion resource 
#define kDataUpdaterUILastMajorFormatChange	kDataUpdaterUIInitialMajorFormat		// Last major format change
#define kDataUpdaterUILastMinorFormatChange	kDataUpdaterUIInitialMinorFormat		// Last minor format change


#endif // __DataUpdaterUIID_h__

// End, DataUpdaterUIID.h.


