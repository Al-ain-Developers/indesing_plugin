//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/TxtImpID.h $
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
//  Defines IDs used by the TxtImp plug-in.
//  
//========================================================================================

#ifndef __TxtImpID_h__
#define __TxtImpID_h__

#include "SDKDef.h"

// Company:
#define kTxtImpCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTxtImpCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTxtImpPluginName	"TextImportFilter"			// Name of this plug-in.
#define kTxtImpPrefixNumber	0x42100 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTxtImpVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kTxtImpAuthor		"Adobe Developer Technologies"	// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTxtImpPrefixNumber above to modify the prefix.)
#define kTxtImpPrefix		RezLong(kTxtImpPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTxtImpStringPrefix	SDK_DEF_STRINGIZE(kTxtImpPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTxtImpPluginID, kTxtImpPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kTxtImpActionComponentBoss,	kTxtImpPrefix + 0) // kept here for record keeping purposes (Do not reuse this ID!)
//Start from InDesign 3.0, plug-ins no longer need to provide register bosses for menu, string, action, panel and tool tip.
#if 0
DECLARE_PMID(kClassIDSpace, kTxtImpStringRegisterBoss,	kTxtImpPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTxtImpMenuRegisterBoss, kTxtImpPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTxtImpActionRegisterBoss, kTxtImpPrefix + 4)
#endif

DECLARE_PMID(kClassIDSpace, kTxtImpFilterBoss, kTxtImpPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kTxtImpDialogBoss, kTxtImpPrefix + 5) // kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kClassIDSpace, kASCIIFileReaderBoss, kTxtImpPrefix + 10)
DECLARE_PMID(kClassIDSpace, kUNICODEFileReaderBoss, kTxtImpPrefix + 11)
DECLARE_PMID(kClassIDSpace, kShiftJISFileReaderBoss, kTxtImpPrefix + 12)
DECLARE_PMID(kClassIDSpace, kJISFileReaderBoss, kTxtImpPrefix + 13)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITXTIMPFILEREADER, kTxtImpPrefix + 0)

// ImplementationIDs:
//DECLARE_PMID(kImplementationIDSpace, kTxtImpActionComponentImpl, kTxtImpPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kTxtImpFilterImpl,	kTxtImpPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kTxtImpDialogControllerImpl, kTxtImpPrefix + 3) // kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kASCIIFileReaderImpl, kTxtImpPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kUNICODEFileReaderImpl, kTxtImpPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kShiftJISFileReaderImpl, kTxtImpPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kJISFileReaderImpl, kTxtImpPrefix + 13)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTxtImpAboutActionID, kTxtImpPrefix + 0)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kTxtImpDialogWidgetID, kTxtImpPrefix + 0) // kept here for record keeping purposes (Do not reuse this ID!)
//DECLARE_PMID(kWidgetIDSpace, kTxtImpDropdownWidgetId, kTxtImpPrefix + 2) // kept here for record keeping purposes (Do not reuse this ID!)

// "About Plug-ins" sub-menu:
#define kTxtImpAboutMenuKey			kTxtImpStringPrefix "kTxtImpAboutMenuKey"
#define kTxtImpAboutMenuPath		kSDKDefStandardAboutMenuPath kTxtImpCompanyKey

// "Plug-ins" sub-menu:
#define kTxtImpPluginsMenuKey 		kTxtImpStringPrefix "kTxtImpPluginsMenuKey"
#define kTxtImpPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kTxtImpCompanyKey kSDKDefDelimitMenuPath kTxtImpPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kTxtImpAboutBoxStringKey	kTxtImpStringPrefix "kTxtImpAboutBoxStringKey"
#define kTxtImpTargetMenuPath 		kTxtImpPluginsMenuPath
#define kTxtImpFormatNameKey		kTxtImpStringPrefix "kTxtImpFormatName"
#define kTxtImpProgressBarTitleKey	kTxtImpStringPrefix "kTxtImpProgressBarTitleKey"
#define kTxtImpInProgressStringKey	kTxtImpStringPrefix "kTxtImpInProgressStringKey"
#define kTxtImpEncodingASCIIKey		kTxtImpStringPrefix "kTxtImpEncodingASCIIKey"
#define kTxtImpEncodingUNICODEKey	kTxtImpStringPrefix "kTxtImpEncodingUNICDEKey"
#define kTxtImpEncodingShiftJISKey	kTxtImpStringPrefix "kTxtImpEncodingShiftJISKey"
#define kTxtImpEncodingJISKey		kTxtImpStringPrefix "kTxtImpEncodingJISKey"

// Nontranslated Stringkeys:
#define kTxtImpFileExtensionKey		"CPP"

// Nontranslated Strings:
#define kTxtImpFileType				'TEXT'

// Initial data format version numbers
#define kTxtImpFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kTxtImpFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kTxtImpCurrentMajorFormatNumber kTxtImpFirstMajorFormatNumber // most recent major format change
#define kTxtImpCurrentMinorFormatNumber kTxtImpFirstMinorFormatNumber // most recent minor format change

#endif // __TxtImpID_h__

// End, TxtImpID.h.



