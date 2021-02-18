//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpID.h $
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
//  Defines IDs used by the TxtExp plug-in.
//  
//========================================================================================

#ifndef __TxtExpID_h__
#define __TxtExpID_h__

#include "SDKDef.h"

// Company:
#define kTxtExpCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTxtExpCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTxtExpPluginName	"TextExportFilter"			// Name of this plug-in.
#define kTxtExpPrefixNumber	0x42200 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTxtExpVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kTxtExpAuthor		"Adobe Developer Technologies"	// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTxtExpPrefixNumber above to modify the prefix.)
#define kTxtExpPrefix		RezLong(kTxtExpPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTxtExpStringPrefix	SDK_DEF_STRINGIZE(kTxtExpPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTxtExpPluginID, kTxtExpPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kTxtExpActionComponentBoss, kTxtExpPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTxtExpStringRegisterBoss,	kTxtExpPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTxtExpFilterBoss,	kTxtExpPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTxtExpMenuRegisterBoss, kTxtExpPrefix + 4)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kTxtExpActionRegisterBoss,	kTxtExpPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTxtExpDialogBoss, kTxtExpPrefix + 6)
DECLARE_PMID(kClassIDSpace, kASCIIFileWriterBoss, kTxtExpPrefix + 10)
DECLARE_PMID(kClassIDSpace, kUNICODEFileWriterBoss, kTxtExpPrefix + 11)
DECLARE_PMID(kClassIDSpace, kShiftJISFileWriterBoss, kTxtExpPrefix + 12)
DECLARE_PMID(kClassIDSpace, kJISFileWriterBoss, kTxtExpPrefix + 13)

 
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITXTEXPFILEWRITER, kTxtExpPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ITXTEXPSUITE, kTxtExpPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kTxtExpActionComponentImpl,	kTxtExpPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTxtExpFilterImpl, kTxtExpPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTxtExpDialogControllerImpl, kTxtExpPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTxtExpDialogObserverImpl, kTxtExpPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kASCIIFileWriterImpl, kTxtExpPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kUNICODEFileWriterImpl, kTxtExpPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kShiftJISFileWriterImpl, kTxtExpPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kJISFileWriterImpl, kTxtExpPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTxtExpSuiteASBImpl, kTxtExpPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTxtExpSuiteTextCSBImpl, kTxtExpPrefix + 15)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTxtExpAboutActionID, kTxtExpPrefix + 0)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kTxtExpDialogWidgetID, kTxtExpPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kTxtExpIconSuiteWidgetID, kTxtExpPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTxtExpDropdownWidgetId, kTxtExpPrefix + 2)
 
// "About Plug-ins" sub-menu:
#define kTxtExpAboutMenuKey		kTxtExpStringPrefix "kTxtExpAboutMenuKey"
#define kTxtExpAboutMenuPath	kSDKDefStandardAboutMenuPath kTxtExpCompanyKey

// "Plug-ins" sub-menu:
#define kTxtExpPluginsMenuKey 	kTxtExpStringPrefix "kTxtExpPluginsMenuKey"
#define kTxtExpPluginsMenuPath	kSDKDefPlugInsStandardMenuPath kTxtExpCompanyKey kSDKDefDelimitMenuPath kTxtExpPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kTxtExpAboutBoxStringKey	kTxtExpStringPrefix "kTxtExpAboutBoxStringKey"
#define kTxtExpDialogTitleKey		kTxtExpStringPrefix "kTxtExpDialogTitleKey"
#define kTxtExpTargetMenuPath 		kTxtExpPluginsMenuPath
#define kTxtExpFormatNameKey		kTxtExpStringPrefix "kTxtExpFormatNameKey"
#define kTxtExpProgressBarTitleKey	kTxtExpStringPrefix "kTxtExpProgressBarTitleKey"
#define kTxtExpInProgressStringKey	kTxtExpStringPrefix "kTxtExpInProgressStringKey"
#define kTxtExpEncodingASCIIKey		kTxtExpStringPrefix "kTxtExpEncodingASCIIKey"
#define kTxtExpEncodingUNICODEKey	kTxtExpStringPrefix "kTxtExpEncodingUNICDEKey"
#define kTxtExpEncodingShiftJISKey	kTxtExpStringPrefix "kTxtExpEncodingShiftJISKey"
#define kTxtExpEncodingJISKey		kTxtExpStringPrefix "kTxtExpEncodingJISKey"

// non-translated StringKeys:
#define kTxtExpFileExtensionKey		"CPP"

// Nontranslated Strings:
#define kTxtExpFileType				'TEXT'

// Initial data format version numbers
#define kTxtExpFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kTxtExpFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kTxtExpCurrentMajorFormatNumber kTxtExpFirstMajorFormatNumber // most recent major format change
#define kTxtExpCurrentMinorFormatNumber kTxtExpFirstMinorFormatNumber // most recent minor format change

#endif // __TxtExpID_h__

// End, TxtExpID.h.



