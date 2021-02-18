//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapID.h $
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
//  Defines IDs used by the Snap plug-in.
//  
//========================================================================================

#ifndef __SnapID_h__
#define __SnapID_h__

#include "SnapRezDefs.h"

// Company:
#define kSnapCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kSnapCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kSnapPluginName	"SnapShot" // Name of this plug-in.
#define kSnapPrefixNumber	0x4FD00 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kSnapVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kSnapAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kSnapPrefixNumber above to modify the prefix.)
#define kSnapPrefix		RezLong(kSnapPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kSnapStringPrefix	SDK_DEF_STRINGIZE(kSnapPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kSnapPluginID, kSnapPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kSnapActionComponentBoss, kSnapPrefix + 0)
DECLARE_PMID(kClassIDSpace, kSnapToolBoss, kSnapPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSnapTrackerBoss, kSnapPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSnapDialogBoss, kSnapPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSnapSetPrefsCmdBoss, kSnapPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSnapTrackerRegisterBoss, kSnapPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSnapIteratorRegisterBoss, kSnapPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSnapErrorStringServiceBoss, kSnapPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSnapPrefsScriptProviderBoss, kSnapPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSnapConversionProviderBoss, kSnapPrefix + 12)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPPREFSDATA, kSnapPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPSELECTIONSUITE, kSnapPrefix + 1)

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kSnapActionComponentImpl, kSnapPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kSnapTrackerRegisterImpl, kSnapPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSnapToolImpl, kSnapPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSnapTrackerImpl, kSnapPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSnapCursorProviderImpl, kSnapPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSnapDialogControllerImpl, kSnapPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSnapPrefsDataPersistImpl, kSnapPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSnapPrefsDataImpl, kSnapPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSnapSetPrefsCmdImpl, kSnapPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSnapIteratorRegisterImpl, kSnapPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSnapSelectionSuiteASBImpl, kSnapPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSnapSelectionSuiteCSBImpl, kSnapPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSnapErrorStringServiceImpl, kSnapPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSnapPrefsScriptProviderImpl, kSnapPrefix + 16)

// WidgetIDs	
DECLARE_PMID(kWidgetIDSpace, kSnapWidgetID, kSnapPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kSnapDialogWidgetID, kSnapPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kFileOptionsGroupTextWidgetID, kSnapPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kFilenameStaticTextWidgetID, kSnapPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kFilenameTextEditBoxWidgetID, kSnapPrefix + 5) 
DECLARE_PMID(kWidgetIDSpace, kFileFormatStaticTextWidgetID, kSnapPrefix + 6) 
DECLARE_PMID(kWidgetIDSpace, kFileFormatDropDownWidgetId, kSnapPrefix + 7) 
DECLARE_PMID(kWidgetIDSpace, kGeneralOptionsGroupTextWidgetID, kSnapPrefix + 8) 
DECLARE_PMID(kWidgetIDSpace, kScaleStaticTextWidgetID, kSnapPrefix + 9) 
DECLARE_PMID(kWidgetIDSpace, kScalePercentageComboBoxWidgetID, kSnapPrefix + 10) 
DECLARE_PMID(kWidgetIDSpace, kResolutionStaticTextWidgetID, kSnapPrefix + 11) 
DECLARE_PMID(kWidgetIDSpace, kResolutionRealComboBoxWidgetID, kSnapPrefix + 12) 
DECLARE_PMID(kWidgetIDSpace, kBleedStaticTextWidgetID, kSnapPrefix + 13) 
DECLARE_PMID(kWidgetIDSpace, kBleedXMeasureEditBoxWidgetID, kSnapPrefix + 14) 
DECLARE_PMID(kWidgetIDSpace, kBleedXMeasureEditBoxNudgeWidgetID, kSnapPrefix + 15) 
DECLARE_PMID(kWidgetIDSpace, kSelectionOptionsGroupTextWidgetID, kSnapPrefix + 16) 
DECLARE_PMID(kWidgetIDSpace, kDrawStaticTextWidgetID, kSnapPrefix + 17) 
DECLARE_PMID(kWidgetIDSpace, kDrawAreaRadioWidgetID, kSnapPrefix + 18) 
DECLARE_PMID(kWidgetIDSpace, kDrawItemRadioWidgetID, kSnapPrefix + 19) 
DECLARE_PMID(kWidgetIDSpace, kMinimumResolutionStaticTextWidgetID, kSnapPrefix + 20) 
DECLARE_PMID(kWidgetIDSpace, kMinimumResolutionRealComboBoxWidgetID, kSnapPrefix + 21) 
DECLARE_PMID(kWidgetIDSpace, kFullResolutionWidgetID, kSnapPrefix + 22) 
DECLARE_PMID(kWidgetIDSpace, kGrayscaleWidgetID, kSnapPrefix + 23) 
DECLARE_PMID(kWidgetIDSpace, kPrintingWidgetID, kSnapPrefix + 25) 

DECLARE_PMID(kWidgetIDSpace, kTIFFOptionsGroupTextWidgetID, kSnapPrefix + 27) 
DECLARE_PMID(kWidgetIDSpace, kGIFOptionsGroupTextWidgetID, kSnapPrefix + 28) 
DECLARE_PMID(kWidgetIDSpace, kJPEGOptionsGroupTextWidgetID, kSnapPrefix + 29) 
DECLARE_PMID(kWidgetIDSpace, kPaletteTypeStaticTextWidgetID, kSnapPrefix + 30) 
DECLARE_PMID(kWidgetIDSpace, kTIFFPaletteTypeDropDownWidgetID, kSnapPrefix + 31) 
DECLARE_PMID(kWidgetIDSpace, kGIFPaletteTypeDropDownWidgetID, kSnapPrefix + 32) 
DECLARE_PMID(kWidgetIDSpace, kTIFFTransparentWidgetID, kSnapPrefix + 33) 
DECLARE_PMID(kWidgetIDSpace, kGIFTransparentWidgetID, kSnapPrefix + 34) 
DECLARE_PMID(kWidgetIDSpace, kJPEGEncodingStaticTextWidgetID, kSnapPrefix + 35) 
DECLARE_PMID(kWidgetIDSpace, kJPEGEncodingDropDownWidgetID, kSnapPrefix + 36) 
DECLARE_PMID(kWidgetIDSpace, kJPEGQualityStaticTextWidgetID, kSnapPrefix + 37) 
DECLARE_PMID(kWidgetIDSpace, kJPEGQualityDropDownWidgetID, kSnapPrefix + 38) 
DECLARE_PMID(kWidgetIDSpace, kGIFInterlacedWidgetID, kSnapPrefix + 39) 

//ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kSnapPrefObjectScriptElement, kSnapPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kSnapPrefObjectPropertyScriptElement, kSnapPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSnapFileNamePropertyScriptElement, kSnapPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kSnapImageFormatPropertyScriptElement, kSnapPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kSnapScaleFactorPropertyScriptElement, kSnapPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kSnapResolutionPropertyScriptElement, kSnapPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kSnapMinimumResolutionPropertyScriptElement, kSnapPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kSnapDrawAreaPropertyScriptElement, kSnapPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kSnapBleedPropertyScriptElement, kSnapPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kSnapFullResolutionPropertyScriptElement, kSnapPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kSnapDrawGrayPropertyScriptElement, kSnapPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kSnapDrawingFlagsPropertyScriptElement, kSnapPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kSnapJPEGEncodingPropertyScriptElement, kSnapPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kSnapJPEGQualityPropertyScriptElement, kSnapPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kSnapTIFFPaletteTypePropertyScriptElement, kSnapPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kSnapGIFPaletteTypePropertyScriptElement, kSnapPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kSnapTIFFTransparentPropertyScriptElement, kSnapPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kSnapGIFTransparentPropertyScriptElement, kSnapPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kSnapGIFInterlacedPropertyScriptElement, kSnapPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kSnapImageWriteFormatEnumScriptElement, kSnapPrefix + 19)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kSnapFailureErrorCode, kSnapPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kSnapDataAccessErrorCode, kSnapPrefix + 1)

// "About Plug-ins" sub-menu:
DECLARE_PMID(kActionIDSpace, kSnapAboutActionID, kSnapPrefix + 0)

#define kSnapAboutMenuKey			kSnapStringPrefix "kSnapAboutMenuKey"
#define kSnapAboutMenuPath			kSDKDefStandardAboutMenuPath kSnapCompanyKey

// Action IDs
// Action IDs for the tool shortcuts.
DECLARE_PMID(kActionIDSpace, kSnapToolActionID, kSnapPrefix + 1)

// "Plug-ins" sub-menu:
#define kSnapPluginsMenuKey 		kSnapStringPrefix "kSnapPluginsMenuKey"
#define kSnapPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kSnapCompanyKey kSDKDefDelimitMenuPath kSnapPluginsMenuKey

// StringKeys:
#define kSnapAboutBoxStringKey		kSnapStringPrefix "kSnapAboutBoxStringKey"
// Tool (string) IDs:
#define kSnapStringKey				kSnapStringPrefix kSnapPluginName "kSnapStringKey"
#define kTrackingStartKey			kSnapStringPrefix kSnapPluginName "kTrackingStartKey"

// Command Keys
#define kCommandSnapSetPrefsCmdKey	kSnapStringPrefix "kCommandSnapSetPrefsCmdKey"

// Dialog IDs:
#define kDialogTitleKey					kSnapStringPrefix "kDialogTitleKey"
#define kDialogFilenameKey 				kSnapStringPrefix "kDialogFilenameKey"
#define kDialogDefaultFilenameKey 		"Snapshot"
#define kDialogFileOptionsKey 			kSnapStringPrefix "kDialogFileOptionsKey"
#define kDialogFileFormatKey			kSnapStringPrefix "kDialogFileFormatKey"
#define kDialogDefaultFileFormatKey 	kSnapStringPrefix "kDialogDefaultFileFormatKey"
#define kDialogScaleKey	 				kSnapStringPrefix "kDialogScaleKey"
#define kDialogResolutionKey	 		kSnapStringPrefix "kDialogResolutionKey"
#define kDialogBleedKey		 			kSnapStringPrefix "kDialogBleedKey"
#define kDialogGeneralOptionsKey	 	kSnapStringPrefix "kDialogGeneralOptionsKey"
#define kDialogTIFFOptionsKey	 		kSnapStringPrefix "kDialogTIFFOptionsKey"
#define kDialogGIFOptionsKey	 		kSnapStringPrefix "kDialogGIFOptionsKey"
#define kDialogJPEGOptionsKey	 		kSnapStringPrefix "kDialogJPEGOptionsKey"
#define kDialogSelectionOptionsKey 	 	kSnapStringPrefix "kDialogSelectionOptionsKey"
#define kDialogDrawKey 	 				kSnapStringPrefix "kDialogDrawKey"
#define kDialogDrawAreaKey 	 			kSnapStringPrefix "kDialogDrawAreaKey"
#define kDialogDrawItemKey 	 			kSnapStringPrefix "kDialogDrawItemKey"
#define kDialogMinimumResolutionKey		kSnapStringPrefix "kDialogMinimumResolutionKey"
#define kDialogFullResolutionKey		kSnapStringPrefix "kDialogFullResolutionKey"
#define kDialogGrayscaleKey				kSnapStringPrefix "kDialogGrayscaleKey"
#define kDialogPrintingKey				kSnapStringPrefix "kDialogPrintingKey"

#define kDialogTransparentKey			kSnapStringPrefix "kDialogTransparentKey"
#define kDialogJPEGEncodingKey			kSnapStringPrefix "kDialogJPEGEncodingKey"
#define	kJPEGEncodingBaselineKey		kSnapStringPrefix "kJPEGEncodingBaselineKey"
#define	kJPEGEncodingProgressiveKey		kSnapStringPrefix "kJPEGEncodingProgressiveKey"
#define	kDialogJPEGQualityKey			kSnapStringPrefix "kDialogJPEGQualityKey"
#define	kJPEGQualityLowKey				kSnapStringPrefix "kJPEGQualityLowKey"
#define	kJPEGQualityGoodKey				kSnapStringPrefix "kJPEGQualityGoodKey"
#define	kJPEGQualityExcellentKey		kSnapStringPrefix "kJPEGQualityExcellentKey"
#define	kJPEGQualityGreatKey			kSnapStringPrefix "kJPEGQualityGreatKey"
#define	kDialogPaletteTypeKey			kSnapStringPrefix "kDialogPaletteTypeKey"
#define	kNoPaletteTypeKey				kSnapStringPrefix "kNoPaletteTypeKey"
#define	kExactThenAdaptivePaletteTypeKey		kSnapStringPrefix "kExactThenAdaptivePaletteTypeKey"
#define	kMacPaletteTypeKey				kSnapStringPrefix "kMacPaletteTypeKey"
#define	kWebPaletteTypeKey				kSnapStringPrefix "kWebPaletteTypeKey"
#define	kWinPaletteTypeKey				kSnapStringPrefix "kWinPaletteTypeKey"
#define kGIFInterlacedKey				kSnapStringPrefix "kGIFInterlacedKey"
#define k9dpiKey						kSnapStringPrefix "k9dpiKey"
#define k18dpiKey						kSnapStringPrefix "k18dpiKey"
#define k36dpiKey						kSnapStringPrefix "k36dpiKey"
#define k72dpiKey						kSnapStringPrefix "k72dpiKey"
#define k144dpiKey						kSnapStringPrefix "k144dpiKey"
#define k288dpiKey						kSnapStringPrefix "k288dpiKey"
#define k576dpiKey						kSnapStringPrefix "k576dpiKey"

// Alert strings
#define kAlertBadFilenameKey			kSnapStringPrefix "kAlertBadFilenameKey"
#define kAlertSnapshotTakenKey			kSnapStringPrefix "kAlertSnapshotTakenKey"
#define kAlertSnapshotFailedKey			kSnapStringPrefix "kAlertSnapshotFailedKey"
#define kAlertMemoryKey					kSnapStringPrefix "kAlertMemoryKey"
#define kAlertSaveFileKey				kSnapStringPrefix "kAlertSaveFileKey"
#define kAlertBadFileNumberKey			kSnapStringPrefix "kAlertBadFileNumberKey"
#define kAlertFormatDoesNotSupportRgbOrGrayscaleKey					kSnapStringPrefix "kAlertFormatDoesNotSupportRgbOrGrayscaleKey"
#define kAlertMinimumResolutionKey		kSnapStringPrefix "kAlertMinimumResolutionKey"
#define kAlertDoYouReallyWantToDoThis	kSnapStringPrefix "kAlertDoYouReallyWantToDoThis"
#define kSnapFailureErrorCodeErrorCodeStringKey					kSnapStringPrefix "kSnapFailureErrorCodeErrorCodeStringKey"
#define kSnapDataAccessErrorCodeStringKey				kSnapStringPrefix "kSnapDataAccessErrorCodeStringKey"

#define kDefaultResolution 72.0

// Icon and Cursor IDs
#define kCursorSnapResourceID				kCursorSnapResource
#define kIconSnapResourceID					kIconSnapResource

// Initial data format version numbers: the persistent data for this plug-in was introduced in InDesign 1.5
#define kSnapInitialMajorFormat		kSDKDef_15_PersistMajorVersionNumber
#define kSnapInitialMinorFormat		kSDKDef_15_PersistMinorVersionNumber

// Data format version numbers used for InDesign 1.0J. 
// (No data format changes, but a forced format version number change.)
#define kSnap_1J_MajorFormat		kSDKDef_1J_PersistMajorVersionNumber
#define kSnap_1J_MinorFormat		kSDKDef_1J_PersistMinorVersionNumber

#define kSnapStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kSnapStoreWideStringMinorFormat		RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kSnapLastMajorFormatChange	kSnapStoreWideStringMajorFormat		// Most recent major format change
#define kSnapLastMinorFormatChange	kSnapStoreWideStringMinorFormat		// Most recent minor format change

#endif // __SnapID_h__

// End, SnapID.h.
