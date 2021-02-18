//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscID.h $
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
//  Defines IDs used by the TblBsc plug-in.
//  
//========================================================================================

#ifndef __TblBscID_h__
#define __TblBscID_h__

#include "SDKDef.h"

// Company:
#define kTblBscCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTblBscCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTblBscPluginName	"TableBasics"			// Name of this plug-in.
#define kTblBscPrefixNumber	0x57300 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTblBscVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kTblBscAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTblBscPrefixNumber above to modify the prefix.)
#define kTblBscPrefix		RezLong(kTblBscPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTblBscStringPrefix	SDK_DEF_STRINGIZE(kTblBscPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTblBscPluginID, kTblBscPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kTblBscActionComponentBoss,	kTblBscPrefix + 0)
//obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblBscStringRegisterBoss,	kTblBscPrefix + 1)
//obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblBscMenuRegisterBoss,		kTblBscPrefix + 2)
//obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTblBscActionRegisterBoss,	kTblBscPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTblBscDialogBoss,			kTblBscPrefix + 4)
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITBLBSCWIDGETOBSERVER,		kTblBscPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ITBLBSCSELECTIONOBSERVER,	kTblBscPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITBLBSCSUITE,	kTblBscPrefix + 2)
// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kTblBscActionComponentImpl,		kTblBscPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTblBscSelectionObserverImpl,		kTblBscPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTblBscWidgetObserverImpl,			kTblBscPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTblBscSuiteASBImpl,				kTblBscPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTblBscSuiteTextCSBImpl,			kTblBscPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTblBscDialogControllerImpl,		kTblBscPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTblBscDialogObserverImpl,			kTblBscPrefix + 6)
// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTblBscAboutActionID,				kTblBscPrefix + 0)
DECLARE_PMID(kActionIDSpace, kTblBscNewTableActionID,			kTblBscPrefix + 11)
// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kTblBscDialogWidgetID,						kTblBscPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kTblBscIconSuiteWidgetID,					kTblBscPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTblBscNumRowsNudgeWidgetID,				kTblBscPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTblBscNumColsNudgeWidgetID,				kTblBscPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTblBscNumRowsEditWidgetID,				kTblBscPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTblBscNumColsEditWidgetID,				kTblBscPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTblBscPreFilledCheckboxWidgetID,			kTblBscPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTblBscAddressFillRadioWidgetID,			kTblBscPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTblBscPlaceholderFillRadioWidgetID,		kTblBscPrefix + 8)


// "About Plug-ins" sub-menu:
#define kTblBscAboutMenuKey				kTblBscStringPrefix "kTblBscAboutMenuKey"
#define kTblBscAboutMenuPath			kSDKDefStandardAboutMenuPath kTblBscCompanyKey

// "Plug-ins" sub-menu:
#define kTblBscPluginsMenuKey 		kTblBscStringPrefix "kTblBscPluginsMenuKey"
#define kTblBscPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kTblBscCompanyKey kSDKDefDelimitMenuPath kTblBscPluginsMenuKey

// Menu item keys:
#define kTblBscNewTableMenuItemKey		kTblBscStringPrefix "kTblBscNewTableMenuItemKey"

// Other StringKeys:
#define kTblBscDialogTitleKey			kTblBscStringPrefix "kTblBscDialogTitleKey"

#define kTblBscAboutBoxStringKey				kTblBscStringPrefix "kTblBscAboutBoxStringKey"
#define kTblBscNewTableStringKey				kTblBscStringPrefix "kTblBscNewTableStringKey"
#define kTblBscTargetMenuPath					kTblBscPluginsMenuPath

#define kTblBscNumRowsWidgetKey			kTblBscStringPrefix	"kTblBscNumRowsWidgetKey"
#define kTblBscNumColsWidgetKey			kTblBscStringPrefix "kTblBscNumColsWidgetKey"
#define kTblBscPreFilledWidgetKey		kTblBscStringPrefix "kTblBscPreFilledWidgetKey"

#define kTblBscAddressFillRadioWidgetKey			kTblBscStringPrefix "kTblBscAddressFillRadioWidgetKey"
#define kTblBscPlaceholderFillRadioWidgetKey		kTblBscStringPrefix "kTblBscPlaceholderFillRadioWidgetKey"


// Menu item positions:
#define kTblBscNewTableMenuItemPosition			1.0
#define	kTblBscSeparator1MenuItemPosition			10.0
#define kTblBscAboutThisMenuItemPosition				11.0

// Initial data format version numbers
#define kTblBscFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kTblBscFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kTblBscCurrentMajorFormatNumber kTblBscFirstMajorFormatNumber // most recent major format change
#define kTblBscCurrentMinorFormatNumber kTblBscFirstMinorFormatNumber // most recent minor format change

#endif // __TblBscID_h__

// End, TblBscID.h.



