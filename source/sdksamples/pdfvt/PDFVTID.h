//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/PDFVTID.h $
//  
//  Owner: DevTech
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


#ifndef __PDFVTID_h__
#define __PDFVTID_h__

#include "SDKDef.h"

// Company:
#define kPDFVTCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPDFVTCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPDFVTPluginName	"PDFVT SDK Sample Plug-in"			// Name of this plug-in.
#define kPDFVTPrefixNumber	0x162f00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPDFVTVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPDFVTAuthor		"DevTech"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPDFVTPrefixNumber above to modify the prefix.)
#define kPDFVTPrefix		RezLong(kPDFVTPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPDFVTStringPrefix	SDK_DEF_STRINGIZE(kPDFVTPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kPDFVTMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kPDFVTMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPDFVTPluginID, kPDFVTPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPDFVTExportProviderBoss, kPDFVTPrefix + 0)
DECLARE_PMID(kClassIDSpace, kWritePDFVTDataSourceInfoCmdBoss, kPDFVTPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kPDFVTBoss, kPDFVTPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kPDFVTBoss, kPDFVTPrefix + 3)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IDATASOURCEDATA, kPDFVTPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPDFVTINTERFACE, kPDFVTPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPDFVTINTERFACE, kPDFVTPrefix + 2)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPDFVTExportProviderImpl, kPDFVTPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDataSourceDataImpl, kPDFVTPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kWritePDFVTDataSourceInfoCmdImpl, kPDFVTPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kPDFVTImpl, kPDFVTPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kPDFVTImpl, kPDFVTPrefix + 4)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPDFVTAboutActionID, kPDFVTPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kPDFVTActionID, kPDFVTPrefix + 1)
//DECLARE_PMID(kActionIDSpace, kPDFVTActionID, kPDFVTPrefix + 2)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kPDFVTWidgetID, kPDFVTPrefix + 0)
//DECLARE_PMID(kWidgetIDSpace, kPDFVTWidgetID, kPDFVTPrefix + 1)
//DECLARE_PMID(kWidgetIDSpace, kPDFVTWidgetID, kPDFVTPrefix + 2)

// "About Plug-ins" sub-menu:
#define kPDFVTAboutMenuKey			kPDFVTStringPrefix "kPDFVTAboutMenuKey"
#define kPDFVTAboutMenuPath		kSDKDefStandardAboutMenuPath kPDFVTCompanyKey

// "Plug-ins" sub-menu:
#define kPDFVTPluginsMenuKey 		kPDFVTStringPrefix "kPDFVTPluginsMenuKey"
#define kPDFVTPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPDFVTCompanyKey kSDKDefDelimitMenuPath kPDFVTPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kPDFVTAboutBoxStringKey	kPDFVTStringPrefix "kPDFVTAboutBoxStringKey"
#define kPDFVTTargetMenuPath kPDFVTPluginsMenuPath

#define kPDFVTWriteDataSourceInfoCmdKey kPDFVTStringPrefix "kWritePDFVTDataSourceInfoCmdStringKey"

// Menu item positions:


// Initial data format version numbers
#define kPDFVTFirstMajorFormatNumber  RezLong(1)
#define kPDFVTFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kPDFVTCurrentMajorFormatNumber kPDFVTFirstMajorFormatNumber
#define kPDFVTCurrentMinorFormatNumber kPDFVTFirstMinorFormatNumber

#endif // __PDFVTID_h__

//  Code generated by DollyXs code generator
