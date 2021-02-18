//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvtui/PDFVTUIID.h $
//  
//  Owner: Devtech
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __PDFVTUIID_h__
#define __PDFVTUIID_h__

#include "SDKDef.h"

// Company:
#define kPDFVTUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPDFVTUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPDFVTUIPluginName	"PDFVTUI"			// Name of this plug-in.
#define kPDFVTUIPrefixNumber	0x163300 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPDFVTUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPDFVTUIAuthor		"Devtech"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPDFVTUIPrefixNumber above to modify the prefix.)
#define kPDFVTUIPrefix		RezLong(kPDFVTUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPDFVTUIStringPrefix	SDK_DEF_STRINGIZE(kPDFVTUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kPDFVTUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kPDFVTUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPDFVTUIPluginID, kPDFVTUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPDFVTUIActionComponentBoss, kPDFVTUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPDFVTUIPanelWidgetBoss, kPDFVTUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPDFVTUIDialogBoss, kPDFVTUIPrefix + 2)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFVTUIDROPDOWNLISTSELECTION, kPDFVTUIPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPDFVTUIINTERFACE, kPDFVTUIPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPDFVTUIActionComponentImpl, kPDFVTUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kPDFVTUIDialogControllerImpl, kPDFVTUIPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kPDFVTUIDialogObserverImpl, kPDFVTUIPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kPDFVTUIDropDownListSelectionImpl, kPDFVTUIPrefix + 3 )
// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPDFVTUIAboutActionID, kPDFVTUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPDFVTUIPanelWidgetActionID, kPDFVTUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPDFVTUISeparator1ActionID, kPDFVTUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPDFVTUIPopupAboutThisActionID, kPDFVTUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPDFVTUIDialogActionID, kPDFVTUIPrefix + 4)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIPanelWidgetID, kPDFVTUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIDialogWidgetID, kPDFVTUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIDataSourceFileTextWidgetID,  kPDFVTUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIFindDataSourceFileButtonWidgetID, kPDFVTUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIFirstNameDropDownListWidgetID, kPDFVTUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIFirstNameTextWidgetID, kPDFVTUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUILastNameDropDownListWidgetID, kPDFVTUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUILastNameTextWidgetID, kPDFVTUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUICityDropDownListWidgetID, kPDFVTUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUICityTextWidgetID, kPDFVTUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIPostalCodeDropDownListWidgetID, kPDFVTUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUIPostalCodeTextWidgetID, kPDFVTUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUICountryDropDownListWidgetID, kPDFVTUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPDFVTUICountryTextWidgetID, kPDFVTUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCIP4MappingGroupTextWidgetID, kPDFVTUIPrefix + 14)



// "About Plug-ins" sub-menu:
#define kPDFVTUIAboutMenuKey			kPDFVTUIStringPrefix "kPDFVTUIAboutMenuKey"
#define kPDFVTUIAboutMenuPath		kSDKDefStandardAboutMenuPath kPDFVTUICompanyKey

// "Plug-ins" sub-menu:
#define kPDFVTUIPluginsMenuKey 		kPDFVTUIStringPrefix "kPDFVTUIPluginsMenuKey"
#define kPDFVTUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPDFVTUICompanyKey kSDKDefDelimitMenuPath kPDFVTUIPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kPDFVTUIAboutBoxStringKey	kPDFVTUIStringPrefix "kPDFVTUIAboutBoxStringKey"
#define kPDFVTUIInternalPopupMenuNameKey kPDFVTUIStringPrefix	"kPDFVTUIInternalPopupMenuNameKey"
#define kPDFVTUITargetMenuPath kPDFVTUIInternalPopupMenuNameKey


#define kPDFVTUIDataSourceFileLabelItemKey  kPDFVTUIStringPrefix "kPDFVTUIDataSourceFilelabelItemKey"
#define kPDFVTUIFindDataSourceFileButtonKey kPDFVTUIStringPrefix "kPDFVTUIFindDataSourceFileButtonKey"
#define kPDFVTUIFirstNameLabelItemKey       kPDFVTUIStringPrefix "kPDFVTUIFirstNameLabelItemKey"
#define kPDFVTUILastNameLabelItemKey        kPDFVTUIStringPrefix "kPDFVTUILastNameLabelItemKey"
#define kPDFVTUICityLabelItemKey            kPDFVTUIStringPrefix "kPDFVTUICityLabelItemKey"
#define kPDFVTUIPostalCodeLabelItemKey      kPDFVTUIStringPrefix "kPDFVTUIPostalCodeLabelItemKey"
#define kPDFVTUICountryLabelItemKey         kPDFVTUIStringPrefix "kPDFVTUICountryLabelItemKey"
#define kPDFVTUICityLabelItemKey            kPDFVTUIStringPrefix "kPDFVTUICityLabelItemKey"
#define kPDFVTUICIP4UnmappedKey             kPDFVTUIStringPrefix "kPDFVTUICIP4UnmappedKey"
#define kCIP4MappingOptionsKey              kPDFVTUIStringPrefix "kCIP4MappingOptionsKey"

#define kPDFVTUIWriteDataSourceErrorStringKey kPDFVTUIStringPrefix "kPDFVTUIWriteDataSourceErrorStringKey"

#define kPDFVTUIDataSourceFileKey "Select Data Source File"
#define kPDFVTUIFileTypeTextKey "Text file(text)"
#define kPDFVTUIFileTypeCSVKey "CSV file(csv)"

#define kUnsupportedEncodingWarningKey "Unsupported encoding.\nOnly UTF-8 and UTF-16 encoded files are supported."

// Menu item positions:

#define	kPDFVTUISeparator1MenuItemPosition		10.0
#define kPDFVTUIAboutThisMenuItemPosition		11.0

#define kPDFVTUIDialogTitleKey kPDFVTUIStringPrefix "kPDFVTUIDialogTitleKey"
// "Plug-ins" sub-menu item key for dialog:
#define kPDFVTUIDialogMenuItemKey kPDFVTUIStringPrefix "kPDFVTUIDialogMenuItemKey"
// "Plug-ins" sub-menu item position for dialog:
#define kPDFVTUIDialogMenuItemPosition	12.0


// Initial data format version numbers
#define kPDFVTUIFirstMajorFormatNumber  RezLong(1)
#define kPDFVTUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kPDFVTUICurrentMajorFormatNumber kPDFVTUIFirstMajorFormatNumber
#define kPDFVTUICurrentMinorFormatNumber kPDFVTUIFirstMinorFormatNumber

#endif // __PDFVTUIID_h__

//  Code generated by DollyXs code generator
