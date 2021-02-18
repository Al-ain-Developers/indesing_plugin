//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUIID.h $
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

#ifndef __SuppUIID_h__
#define __SuppUIID_h__

#include "SDKDef.h"

// Company:
#define kSuppUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kSuppUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kSuppUIPluginName	"SuppUI"			// Name of this plug-in.
#define kSuppUIPrefixNumber	0xaf100 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kSuppUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kSuppUIAuthor		"Heath Lynn"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kSuppUIPrefixNumber above to modify the prefix.)
#define kSuppUIPrefix		RezLong(kSuppUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kSuppUIStringPrefix	SDK_DEF_STRINGIZE(kSuppUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kSuppUIPluginID, kSuppUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kSuppUIActionComponentBoss, kSuppUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kSuppUISuppressedUIServiceBoss, kSuppUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSuppUISuppressedUIWithXMLServiceBoss, kSuppUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSuppUIQuickApplyFilterServiceBoss, kSuppUIPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kSuppUIBoss, kSuppUIPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISuppUIINTERFACE, kSuppUIPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kSuppUIActionComponentImpl, kSuppUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kSuppUISuppressedUIImpl, kSuppUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSuppUISysFileDataImpl, kSuppUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSuppUIQuickApplyFilterProviderImpl, kSuppUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSuppUIQuickApplyFilterServiceImpl, kSuppUIPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kSuppUIImpl, kSuppUIPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kSuppUIAboutActionID, kSuppUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kSuppUISuppressStyleChangesActionID, kSuppUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSuppUISuppressFontAndSizeActionID, kSuppUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kSuppUISuppressOpenFileDialogControlsActionID, kSuppUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kSuppUISuppressParaStyleQuickApplyActionID, kSuppUIPrefix + 4)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kSuppUIActionID, kSuppUIPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 1)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kSuppUIWidgetID, kSuppUIPrefix + 25)


// "About Plug-ins" sub-menu:
#define kSuppUIAboutMenuKey			kSuppUIStringPrefix "kSuppUIAboutMenuKey"
#define kSuppUIAboutMenuPath			kSDKDefStandardAboutMenuPath kSuppUICompanyKey

// "Plug-ins" sub-menu:
#define kSuppUIPluginsMenuKey 		kSuppUIStringPrefix "kSuppUIPluginsMenuKey"
#define kSuppUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kSuppUICompanyKey kSDKDefDelimitMenuPath kSuppUIPluginsMenuKey

// Menu item keys:
#define kSuppUISuppressStyleChangesKey 		kSuppUIStringPrefix "kSuppUISuppressStyleChangesKey"
#define kSuppUISuppressFontAndSizeKey	kSuppUIStringPrefix "kSuppUISuppressFontAndSizeKey"
#define kSuppUISuppressOpenFileDialogControlsKey	kSuppUIStringPrefix "kSuppUISuppressOpenFileDialogControlsKey"
#define kSuppUISuppressParaStyleQuickApplyKey	kSuppUIStringPrefix "kSuppUISuppressParaStyleQuickApplyKey"



// Other StringKeys:
#define kSuppUIAboutBoxStringKey				kSuppUIStringPrefix "kSuppUIAboutBoxStringKey"
#define kSuppUITargetMenuPath kSuppUIPluginsMenuPath

// Menu item positions:

#define kSuppUISuppressStyleChangesMenuItemPosition 13.0
#define kSuppUISuppressFontAndSizeMenuItemPosition 14.0
#define kSuppUISuppressOpenFileDialogControlsMenuItemPosition 15.0
#define kSuppUISuppressParaStyleQuickApplyMenuItemPosition 16.0

// Initial data format version numbers
#define kSuppUIFirstMajorFormatNumber  RezLong(1)
#define kSuppUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kSuppUICurrentMajorFormatNumber kSuppUIFirstMajorFormatNumber
#define kSuppUICurrentMinorFormatNumber kSuppUIFirstMinorFormatNumber

#endif // __SuppUIID_h__

//  Code generated by DollyXs code generator
