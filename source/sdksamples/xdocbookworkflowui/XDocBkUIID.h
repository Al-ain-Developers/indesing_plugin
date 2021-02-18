//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflowui/XDocBkUIID.h $
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
//========================================================================================

#ifndef __XDocBkUIID_h__
#define __XDocBkUIID_h__

#include "SDKDef.h"

// Company:
#define kXDocBkUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kXDocBkUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kXDocBkUIPluginName	"XDocBookWorkflowUI"			// Name of this plug-in.
#define kXDocBkUIPrefixNumber	0x5c3a0 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kXDocBkUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kXDocBkUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kXDocBkUIPrefixNumber above to modify the prefix.)
#define kXDocBkUIPrefix		RezLong(kXDocBkUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kXDocBkUIStringPrefix	SDK_DEF_STRINGIZE(kXDocBkUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kXDocBkUIPluginID, kXDocBkUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kXDocBkUIActionComponentBoss,	kXDocBkUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kXDocBkUIDialogBoss,	kXDocBkUIPrefix + 1)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IXDOCBKUIWIDGETOBSERVER,	kXDocBkUIPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kXDocBkUIActionComponentImpl,	kXDocBkUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kXDocBkUIDialogControllerImpl,	kXDocBkUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXDocBkUIPanelCreatorImpl,		kXDocBkUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXDocBkUIDialogObserverImpl,	kXDocBkUIPrefix + 3)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kXDocBkUIAboutActionID,			kXDocBkUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kXDocBkUIPrefSepActionID,			kXDocBkUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kXDocBkUISetOptionsActionID,		kXDocBkUIPrefix + (10 + 1))
DECLARE_PMID(kActionIDSpace, kXDocBkUIUnitTestActionID,			kXDocBkUIPrefix + (10 + 7))

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIPanelWidgetID,					kXDocBkUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUITemplateTitleTextWidgetID,		kXDocBkUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUITemplateGroupWidgetID,			kXDocBkUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUITemplateDescriptionTextWidgetID,	kXDocBkUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUITemplateTextEditWidgetID,			kXDocBkUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIChangeTemplateButtonWidgetID,		kXDocBkUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIChangeStylesheetButtonWidgetID,	kXDocBkUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIStylesheetGroupWidgetID,			kXDocBkUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIStylesheetDescriptionTextWidgetID,	kXDocBkUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIStylesheetTitleTextWidgetID,		kXDocBkUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIStylesheetTextEditWidgetID,		kXDocBkUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIUseImagePostImportResponderWidgetID,		kXDocBkUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIUseXMLTransformerWidgetID,		kXDocBkUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUIUseCALSContentHandlerWidgetID,		kXDocBkUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUISuppliedOverridesPIWidgetID,		kXDocBkUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kXDocBkUITableGraphicsTitleTextWidgetID,		kXDocBkUIPrefix + 15)



// widget ID

// "About Plug-ins" sub-menu:
#define kXDocBkUIAboutMenuKey			kXDocBkUIStringPrefix "kXDocBkUIAboutMenuKey"
#define kXDocBkUIAboutMenuPath			kSDKDefStandardAboutMenuPath kXDocBkUICompanyKey

// "Plug-ins" sub-menu:
#define kXDocBkUIPluginsMenuKey 		kXDocBkUIStringPrefix "kXDocBkUIPluginsMenuKey"
#define kXDocBkUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kXDocBkUICompanyKey kSDKDefDelimitMenuPath kXDocBkUIPluginsMenuKey

// Menu item keys:
#define kXDocBkUISetOptionsMenuItemKey				kXDocBkUIStringPrefix "kXDocBkUISetOptionsMenuItemKey"
#define kXDocBkUIUnitTestMenuItemKey				kXDocBkUIStringPrefix "kXDocBkUIUnitTestMenuItemKey"

// Other StringKeys:
#define kXDocBkUIAboutBoxStringKey				kXDocBkUIStringPrefix "kXDocBkUIAboutBoxStringKey"
#define kXDocBkUITargetMenuPath kXDocBkUIPluginsMenuPath

#define kXDocBkUISetOption1StringKey			kXDocBkUIStringPrefix "kXDocBkUISetOption1StringKey"
#define kXDocBkUISetOption2StringKey			kXDocBkUIStringPrefix "kXDocBkUISetOption2StringKey"
#define kXDocBkUIPanelTitleKey					kXDocBkUIStringPrefix "kXDocBkUIPanelTitleKey"
// Widget keys
#define kXDocBkUIChangeTemplateButtonWidgetKey				kXDocBkUIStringPrefix "kXDocBkUIChangeTemplateButtonWidgetKey"
#define kXDocBkUITemplateDescriptionTextWidgetKey			kXDocBkUIStringPrefix "kXDocBkUITemplateDescriptionTextWidgetKey"
#define kXDocBkUITemplateTitleTextWidgetKey					kXDocBkUIStringPrefix "kXDocBkUITemplateTitleTextWidgetKey"
#define kXDocBkUIStylesheetDescriptionTextWidgetKey			kXDocBkUIStringPrefix "kXDocBkUIStylesheetDescriptionTextWidgetKey"
#define kXDocBkUIChangeStylesheetButtonWidgetKey			kXDocBkUIStringPrefix "kXDocBkUIChangeStylesheetButtonWidgetKey"
#define kXDocBkUIStylesheetTitleTextWidgetKey				kXDocBkUIStringPrefix "kXDocBkUIStylesheetTitleTextWidgetKey"
#define kXDocBkUITableGraphicsTitleTextWidgetKey			kXDocBkUIStringPrefix "kXDocBkUITableGraphicsTitleTextWidgetKey"
#define kXDocBkUIUseImagePostImportResponderWidgetKey		kXDocBkUIStringPrefix "kXDocBkUIUseImagePostImportResponderWidgetKey"
#define kXDocBkUIUseXMLTransformerWidgetKey					kXDocBkUIStringPrefix "kXDocBkUIUseXMLTransformerWidgetKey"
#define kXDocBkUIUseCALSContentHandlerWidgetKey				kXDocBkUIStringPrefix "kXDocBkUIUseCALSContentHandlerWidgetKey"
#define kXDocBkUISuppliedOverridesPIWidgetKey					kXDocBkUIStringPrefix "kXDocBkUISuppliedOverridesPIWidgetKey"

// Menu item positions:


#define kXDocBkUIUnitTestMenuItemPosition 9

#define kXDocBkUIPrefMenuPosition			1540.0

// Separator for 'Main:Edit:Preferences'
#define kXDocBkUIPrefSepMenuPath			kSDKDefPreferencesStandardMenuPath kSDKDefDelimiterAndSeparatorPath 
#define kXDocBkUIPrefSepMenuPosition			1530.0

// Initial data format version numbers
#define kXDocBkUIFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kXDocBkUIFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kXDocBkUICurrentMajorFormatNumber kXDocBkUIFirstMajorFormatNumber // most recent major format change
#define kXDocBkUICurrentMinorFormatNumber kXDocBkUIFirstMinorFormatNumber // most recent minor format change

#endif // __XDocBkUIID_h__

