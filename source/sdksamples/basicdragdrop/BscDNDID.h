//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdragdrop/BscDNDID.h $
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

#ifndef __BscDNDID_h__
#define __BscDNDID_h__

#include "SDKDef.h"

// Company:
#define kBscDNDCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscDNDCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscDNDPluginName	"BasicDragDrop"			// Name of this plug-in.
#define kBscDNDPrefixNumber	0x5cb00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscDNDVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBscDNDAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscDNDPrefixNumber above to modify the prefix.)
#define kBscDNDPrefix		RezLong(kBscDNDPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscDNDStringPrefix	SDK_DEF_STRINGIZE(kBscDNDPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscDNDPluginID, kBscDNDPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscDNDActionComponentBoss,	kBscDNDPrefix + 0)
DECLARE_PMID(kClassIDSpace, kBscDNDPanelWidgetBoss,		kBscDNDPrefix + 1)

DECLARE_PMID(kClassIDSpace, kBscDNDSourceStaticTextWidgetBoss,		kBscDNDPrefix + 7)
DECLARE_PMID(kClassIDSpace, kBscDNDCustomStaticTextWidgetBoss,		kBscDNDPrefix + 8)
DECLARE_PMID(kClassIDSpace, kBscDNDCustomScrapHandlerBoss,			kBscDNDPrefix + 9)
DECLARE_PMID(kClassIDSpace, kBscDNDCustomFlavorHelperBoss,			kBscDNDPrefix + 10)


// InterfaceIDs:

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscDNDActionComponentImpl,	kBscDNDPrefix + 0 )

// for drag and drop target
DECLARE_PMID(kImplementationIDSpace, kBscDNDDropTargetImpl,		kBscDNDPrefix + 4)

// for drag and drop source
DECLARE_PMID(kImplementationIDSpace, kBscDNDDragSourceImpl,		kBscDNDPrefix + 5)

// for custom flavor target helper
DECLARE_PMID(kImplementationIDSpace, kBscDNDCustomDragSourceImpl,		kBscDNDPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kBscDNDCustomDEHandlerImpl,		kBscDNDPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kBscDNDCustomFlavorHelperImpl,		kBscDNDPrefix + 8)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscDNDAboutActionID,					kBscDNDPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscDNDPanelWidgetActionID,			kBscDNDPrefix + 1)

// WidgetIDs:

DECLARE_PMID(kWidgetIDSpace, kBscDNDPanelWidgetID,				kBscDNDPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kBscDNDTargetStaticTextWidgetID,	kBscDNDPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kBscDNDSourceStaticTextWidgetID,	kBscDNDPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kBscDNDCustomStaticTextWidgetID,	kBscDNDPrefix + 3) 


// "About Plug-ins" sub-menu:
#define kBscDNDAboutMenuKey			kBscDNDStringPrefix "kBscDNDAboutMenuKey"
#define kBscDNDAboutMenuPath		kSDKDefStandardAboutMenuPath kBscDNDCompanyKey

// "Plug-ins" sub-menu:
#define kBscDNDPluginsMenuKey 		kBscDNDStringPrefix "kBscDNDPluginsMenuKey"
#define kBscDNDPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscDNDCompanyKey kSDKDefDelimitMenuPath kBscDNDPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kBscDNDAboutBoxStringKey				kBscDNDStringPrefix "kBscDNDAboutBoxStringKey"
#define kBscDNDPanelTitleKey					kBscDNDStringPrefix	"kBscDNDPanelTitleKey"
#define kBscDNDStaticTextKey					kBscDNDStringPrefix	"kBscDNDStaticTextKey"
#define kBscDNDTargetPanelWidgetTipKey			kBscDNDStringPrefix "kBscDNDTargetPanelWidgetTipKey"
// for drag and drop source
#define kBscDNDSourceStaticTextKey				kBscDNDStringPrefix	"kBscDNDSourceStaticTextKey"
#define kBscDNDSourcePanelWidgetTipKey			kBscDNDStringPrefix	"kBscDNDSourcePanelWidgetTipKey"
// for custom flavor target helper
#define kBscDNDCustomStaticTextKey				kBscDNDStringPrefix	"kBscDNDCustomStaticTextKey"

// custom flavor 
#define customFlavor PMFlavor('AOL1')

// Initial data format version numbers
#define kBscDNDFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscDNDFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscDNDCurrentMajorFormatNumber kBscDNDFirstMajorFormatNumber // most recent major format change
#define kBscDNDCurrentMinorFormatNumber kBscDNDFirstMinorFormatNumber // most recent minor format change

#endif // __BscDNDID_h__

//  Code generated by DollyXS code generator
