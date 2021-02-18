//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblID.h $
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

#ifndef __FrmLblID_h__
#define __FrmLblID_h__

#include "SDKDef.h"

// Company:
#define kFrmLblCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kFrmLblCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kFrmLblPluginName	"FrameLabel"			// Name of this plug-in.
#define kFrmLblPrefixNumber	0x42600 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kFrmLblVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kFrmLblAuthor		" "					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kFrmLblPrefixNumber above to modify the prefix.)
#define kFrmLblPrefix		RezLong(kFrmLblPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kFrmLblStringPrefix	SDK_DEF_STRINGIZE(kFrmLblPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kFrmLblMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kFrmLblMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kFrmLblPluginID, kFrmLblPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kFrmLblScriptProviderBoss, kFrmLblPrefix + 1)
DECLARE_PMID(kClassIDSpace, kFrmLblCmdBoss, kFrmLblPrefix + 2)
DECLARE_PMID(kClassIDSpace, kFrmLblPrintPrefsCmdBoss, kFrmLblPrefix + 3)
DECLARE_PMID(kClassIDSpace, kFrmLblPrefsScriptProviderBoss, kFrmLblPrefix + 4)
DECLARE_PMID(kClassIDSpace, kFrmLblErrorStringServiceBoss, kFrmLblPrefix + 5)
DECLARE_PMID(kClassIDSpace, kFrmLblAdornmentBoss, kFrmLblPrefix + 6)
DECLARE_PMID(kClassIDSpace, kFrmLblConversionProviderBoss, kFrmLblPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFrmLblNewPIResponderBoss, kFrmLblPrefix + 8)
DECLARE_PMID(kClassIDSpace, kFrmLblNewDocResponderBoss, kFrmLblPrefix + 9)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IFRMLBLDATASUITE, kFrmLblPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRMLBLDATA,  kFrmLblPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRMLBLPRINTBOOLDATA, kFrmLblPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_FRMLBLDATAFACADE, kFrmLblPrefix + 3)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kFrmLblScriptProviderImpl, kFrmLblPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataSuiteASBImpl, kFrmLblPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataSuiteLayoutCSBImpl, kFrmLblPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataSuiteTextCSBImpl, kFrmLblPrefix + 3 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataImpl, kFrmLblPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataSuiteDefaultsCSBImpl, kFrmLblPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblAdornmentImpl, kFrmLblPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kFrmLblCmdImpl, kFrmLblPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataSuiteTableCSBImpl, kFrmLblPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kFrmLblPrintPrefsDataPersistImpl, kFrmLblPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kFrmLblPrintPrefsCmdImpl, kFrmLblPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kFrmLblPrefsScriptProviderImpl, kFrmLblPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kFrmLblResponderImpl, kFrmLblPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kFrmLblDataFacadeImpl, kFrmLblPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kFrmLblErrorStringServiceImpl, kFrmLblPrefix + 14)

//Script Element IDs
//Events

// Properties

// ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblStringElement, kFrmLblPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblSizeElement, kFrmLblPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblVisibilityElement, kFrmLblPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblFontColorElement, kFrmLblPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPositionEnumElement, kFrmLblPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPositionElement, kFrmLblPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPrintPrefElement, kFrmLblPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPrefObjectScriptElement, kFrmLblPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPrefObjectPropertyScriptElement, kFrmLblPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPrintPrefObjectScriptElement, kFrmLblPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kFrmLblPrintPrefObjectPropertyScriptElement, kFrmLblPrefix + 10)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kFrmLblFailureErrorCode,			kFrmLblPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kFrmLblLabelCommandFailedErrorCode,	kFrmLblPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kFrmLblNoValidPageItemsSelectedErrorCode, kFrmLblPrefix + 2)

// Other StringKeys:
#define kFrmLblAboutBoxStringKey		kFrmLblStringPrefix "kFrmLblAboutBoxStringKey"
#define kFrmLblTargetMenuPath			kFrmLblPluginsMenuPath
#define kFrmLblCmdStringKey				kFrmLblStringPrefix "kFrmLblCmdStringKey"
#define kFrmLblPrintPrefsCmdStringKey	kFrmLblStringPrefix "kFrmLblPrintPrefsCmdStringKey"

#define kFrmLblFailureErrorCodeStringKey		kFrmLblStringPrefix "kFrmLblFailureErrorCodeStringKey"
#define kFrmLblLabelCommandFailedErrorKey		kFrmLblStringPrefix "kFrmLblLabelCommandFailedErrorKey"

// Initial data format version numbers: the frame label persistent data was first introduced in InDesign 1.0
#define kFrmLblInitialMajorFormat		kSDKDef_10_PersistMajorVersionNumber
#define kFrmLblInitialMinorFormat		kSDKDef_10_PersistMinorVersionNumber

// Data format version numbers used for FrmLbl InDesign 1.5. 
// (No data format changes, but a forced format version number change.)
#define kFrmLbl_15_MajorFormat			kSDKDef_15_PersistMajorVersionNumber
#define kFrmLbl_15_MinorFormat			kSDKDef_15_PersistMinorVersionNumber

// Data format IDs used for FrmLbl InDesign 1.0J. 
// (No data format changes, but a forced format version number change.)
#define kFrmLbl_1J_MajorFormat			kSDKDef_1J_PersistMajorVersionNumber
#define kFrmLbl_1J_MinorFormat			kSDKDef_1J_PersistMinorVersionNumber

// Note: There have been no data format changes since InDesign 2.0.

// InDesign CS4 format changes
#define kFrmLblStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kFrmLblStoreWideStringMinorFormat		RezLong(1)

// Format IDs for the PluginVersion resource 
#define kFrmLblLastMajorFormatChange	kFrmLblStoreWideStringMajorFormat		// Most recent major format change
#define kFrmLblLastMinorFormatChange	kFrmLblStoreWideStringMinorFormat					// Most recent minor format change


// Schema field IDs:
#define kFrmLblLabel 0
#define kFrmLblLabelWidth 1
#define kFrmLblPointSize 2
#define kFrmLblVisibility 3
#define kFrmLblColor 4
#define kFrmLblPosition 5

// other constants
#define kFrmLblDefaultLabel ""
#define kFrmLblDefaultWidth 0
#define kFrmLblDefaultPointSize 12
#define kFrmLblDefaultVisibility kFalse
#define kFrmLblDefaultColor kInvalidUID
#define kFrmLblDefaultPosition 1

#endif // __FrmLblID_h__
