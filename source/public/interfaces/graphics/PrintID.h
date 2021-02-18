//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PrintID.h $
//  
//  Owner: Michael Easter
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
//  Contains IDs used by the printing plug-in
//  
//========================================================================================

#ifndef __PRINTID__
#define __PRINTID__

// ----- Includes -----

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kPrintPrefix	 RezLong(0x0A00)
#define kPrintPrefix2	 RezLong(0x17F00)

//_______________________________________________________________________________________
// <Start IDC>
// PluginID
//_______________________________________________________________________________________
#define kPrintPluginName 					"Print"
DECLARE_PMID(kPlugInIDSpace, kPrintPluginID, kPrintPrefix + 1)


//_______________________________________________________________________________________
// <Class ID>
// ClassIDs
//_______________________________________________________________________________________
DECLARE_PMID(kClassIDSpace, kPrintPSViewPortBoss, kPrintPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPrintNonPSViewPortBoss, kPrintPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPrintEventScriptProviderBoss, kPrintPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPrintScriptEventBoss, kPrintPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPrintCmdBoss_obsolete, kPrintPrefix + 5)
#ifdef MACINTOSH
DECLARE_PMID(kClassIDSpace, kMPageSetupCmdBoss_obsolete, kPrintPrefix + 6)
#endif
DECLARE_PMID(kClassIDSpace, kPrintGetClientItemsCmdBoss_obsolete, kPrintPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPrintInitClientItemsCmdBoss_obsolete, kPrintPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPrintInitAGMCmdBoss_obsolete, kPrintPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPrintViaAGMCmdBoss_obsolete, kPrintPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPrintSaveDocClientItemsCmdBoss_obsolete, kPrintPrefix + 11)
DECLARE_PMID(kClassIDSpace, kPrintClientItemsBoss_obsolete, kPrintPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPrintObjectBoss_obsolete, kPrintPrefix + 13)

// Export EPS ClassIDs
DECLARE_PMID(kClassIDSpace, kEPSExportBoss, kPrintPrefix + 14)
DECLARE_PMID(kClassIDSpace, kExportEPSCmdBoss, kPrintPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSetEPSExportPrefsCmdBoss, kPrintPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSetSEPExportPrefsCmdBoss_obsolete, kPrintPrefix + 17)
//gap
DECLARE_PMID(kClassIDSpace, kPrintSaveAppClientItemsCmdBoss_obsolete, kPrintPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPrintProgressDrawEventBoss, kPrintPrefix + 21)

// New for Sherpa
//gap
DECLARE_PMID(kClassIDSpace, kPrintSignatureHelperBoss_obsolete, kPrintPrefix + 24)
DECLARE_PMID(kClassIDSpace, kPrintSignatureHelperCallbacksBoss_obsolete, kPrintPrefix + 25)
//gap

// New for Hotaka
DECLARE_PMID(kClassIDSpace, kSetAllowCompleteFontCmdBoss_obsolete, kPrintPrefix + 27)

// New for Anna
//gap

DECLARE_PMID(kClassIDSpace, kPrintDataBoss, kPrintPrefix + 38)
//gap
DECLARE_PMID(kClassIDSpace, kPrintConversionProviderBoss, kPrintPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPrintDataOnlyBoss, kPrintPrefix + 41)
//gap
DECLARE_PMID(kClassIDSpace, kPrintSavePrintDataCmdBoss, kPrintPrefix + 44)
DECLARE_PMID(kClassIDSpace, kExportSEPCmdBoss, kPrintPrefix + 45)

DECLARE_PMID(kClassIDSpace, kPrintSaveFileDialogBoss_obsolete, kPrintPrefix + 46)
DECLARE_PMID(kClassIDSpace, kNonPrintDrawEventBoss, kPrintPrefix + 47)

//gap

DECLARE_PMID(kClassIDSpace, kTrapStyleBoss, kPrintPrefix + 50)

//	For Ink Manager dialog panel
//gap

DECLARE_PMID(kClassIDSpace, kTrapStyleExportRootBoss, kPrintPrefix + 57)
DECLARE_PMID(kClassIDSpace, kTrapStyleAddCmdBoss, kPrintPrefix + 58)
DECLARE_PMID(kClassIDSpace, kTrapStyleEditCmdBoss, kPrintPrefix + 59)
DECLARE_PMID(kClassIDSpace, kTrapStyleDeleteCmdBoss, kPrintPrefix + 60)
DECLARE_PMID(kClassIDSpace, kTrapStyleSetCmdBoss, kPrintPrefix + 61)
DECLARE_PMID(kClassIDSpace, kAssignTrapStyleCmdBoss, kPrintPrefix + 62)

DECLARE_PMID(kClassIDSpace, kPrintActionCmdBoss, kPrintPrefix + 63)
DECLARE_PMID(kClassIDSpace, kNewPrintCmdBoss, kPrintPrefix + 64)
DECLARE_PMID(kClassIDSpace, kPrintJobDataBoss, kPrintPrefix + 65)
DECLARE_PMID(kClassIDSpace, kPrintGatherDataCmdBoss, kPrintPrefix + 66)

DECLARE_PMID(kClassIDSpace, kPrintDocPhase2ConversionBoss, kPrintPrefix + 67)
DECLARE_PMID(kClassIDSpace, kTrapStyleWSResponderBoss, kPrintPrefix + 68)
DECLARE_PMID(kClassIDSpace, kTrapStyleNDResponderBoss, kPrintPrefix + 69)
DECLARE_PMID(kClassIDSpace, kTrapStyleSyncBoss, kPrintPrefix + 70)

//	For Ink Manager dialog panel
//gap

DECLARE_PMID(kClassIDSpace, kPrintNewWSResponderBoss, kPrintPrefix + 73)
DECLARE_PMID(kClassIDSpace, kPrintNewDocResponderBoss, kPrintPrefix + 74)
DECLARE_PMID(kClassIDSpace, kLaterPrintNewDocResponderBoss, kPrintPrefix + 75)

//gap

DECLARE_PMID(kClassIDSpace, kSavePrintStyleDataCmdBoss, kPrintPrefix + 78)
DECLARE_PMID(kClassIDSpace, kExportValidationCmdBoss, kPrintPrefix + 79)

DECLARE_PMID(kClassIDSpace, kInkMgrScriptProviderBoss, kPrintPrefix + 80)
//gap
DECLARE_PMID(kClassIDSpace, kCheckColorProviderBoss, kPrintPrefix + 84)
DECLARE_PMID(kClassIDSpace, kCheckDCSPlatesProviderBoss, kPrintPrefix + 85)
DECLARE_PMID(kClassIDSpace, kXPGatherProviderBoss, kPrintPrefix + 86)
DECLARE_PMID(kClassIDSpace, kInkGatherProviderBoss, kPrintPrefix + 87)
DECLARE_PMID(kClassIDSpace, kCheckImageProviderBoss, kPrintPrefix + 88)
DECLARE_PMID(kClassIDSpace, kTrapGatherProviderBoss, kPrintPrefix + 89)
DECLARE_PMID(kClassIDSpace, kGatherFontProviderBoss, kPrintPrefix + 90)

DECLARE_PMID(kClassIDSpace, kPrintOutputPagesBoss, kPrintPrefix + 91)
DECLARE_PMID(kClassIDSpace, kThumbnailProviderBoss, kPrintPrefix + 92)
DECLARE_PMID(kClassIDSpace, kInsertPSProcProviderBoss, kPrintPrefix + 93)
DECLARE_PMID(kClassIDSpace, kBaseDocIterationProviderBoss, kPrintPrefix + 94)
DECLARE_PMID(kClassIDSpace, kDocIterationResultPrintAdapterBoss, kPrintPrefix + 95)
DECLARE_PMID(kClassIDSpace, kDocIterationResultGenericBoss, kPrintPrefix + 96)
DECLARE_PMID(kClassIDSpace, kPrintProgressBoss,kPrintPrefix + 97)
DECLARE_PMID(kClassIDSpace, kCheckEPSProviderBoss, kPrintPrefix + 98)
DECLARE_PMID(kClassIDSpace, kCheckTextProviderBoss, kPrintPrefix + 99)
DECLARE_PMID(kClassIDSpace, kCheckConditionalTextProviderBoss, kPrintPrefix + 100)
DECLARE_PMID(kClassIDSpace, kCheckFlashExportProviderBoss, kPrintPrefix + 101)

//gap

DECLARE_PMID(kClassIDSpace, kPrintPrefsScriptProviderBoss, kPrintPrefix + 102)
DECLARE_PMID(kClassIDSpace, kScriptEventPrintSetupProviderBoss, kPrintPrefix + 103)
DECLARE_PMID(kClassIDSpace, kPrintPropScriptProviderBoss, kPrintPrefix + 104)
DECLARE_PMID(kClassIDSpace, kPrintStylePhase2ConversionBoss, kPrintPrefix + 105)

// New for Dragontail
DECLARE_PMID(kClassIDSpace, kPrintPreviewConfigServiceBoss, kPrintPrefix + 106)
DECLARE_PMID(kClassIDSpace, kPrintPreviewFeatureServiceBoss, kPrintPrefix + 107)
DECLARE_PMID(kClassIDSpace, kPrintPreviewConfigStateBoss, kPrintPrefix + 108)

DECLARE_PMID(kClassIDSpace, kBookPrintDataBoss, kPrintPrefix + 109)
DECLARE_PMID(kClassIDSpace, kStylePrintDataBoss, kPrintPrefix + 110)
DECLARE_PMID(kClassIDSpace, kEPSExportPrefsScriptProviderBoss, kPrintPrefix + 111)
DECLARE_PMID(kClassIDSpace, kTrapStyleScriptProviderBoss, kPrintPrefix + 112)

DECLARE_PMID(kClassIDSpace, kSetPrintGlyphThresholdPrefCmdBoss, kPrintPrefix + 113)
DECLARE_PMID(kClassIDSpace, kPrintDataHelperStrategyProviderBoss, kPrintPrefix + 114)

DECLARE_PMID(kClassIDSpace, kTinFontsWarningDialogCmdBoss,	kPrintPrefix + 115)

// InCopy
DECLARE_PMID(kClassIDSpace, kInCopyPrintActionCmdBoss, kPrintPrefix + 201)
DECLARE_PMID(kClassIDSpace, kInCopyNewPrintCmdBoss, kPrintPrefix + 202)
DECLARE_PMID(kClassIDSpace, kPrintGalleyScriptProviderBoss, kPrintPrefix + 203)
DECLARE_PMID(kClassIDSpace, kPrintLayoutScriptProviderBoss, kPrintPrefix + 204)

DECLARE_PMID(kClassIDSpace, kPrintPreviewDrawStrategyBoss, kPrintPrefix + 209)
DECLARE_PMID(kClassIDSpace, kDocPrintPageInitializerBoss, kPrintPrefix + 210)
//[]DECLARE_PMID(kClassIDSpace, kInkMgrListElementBoss, kPrintPrefix + 211)

DECLARE_PMID(kClassIDSpace, kTrapStyleListPhase2ConversionBoss, kPrintPrefix + 212)
DECLARE_PMID(kClassIDSpace, kPrintRecordBoss, kPrintPrefix + 213)
DECLARE_PMID(kClassIDSpace, kExportFileNameGeneratorBoss, kPrintPrefix + 214)
DECLARE_PMID(kClassIDSpace, kCustomDataSummaryProviderBoss, kPrintPrefix + 215)

//For Print Booklet
DECLARE_PMID(kClassIDSpace, kPrintBookletCmdBoss, kPrintPrefix + 216)
DECLARE_PMID(kClassIDSpace, kPrintBookletPrintDataBoss, kPrintPrefix + 217)
DECLARE_PMID(kClassIDSpace, kPrintBookletProviderBoss, kPrintPrefix + 218)
DECLARE_PMID(kClassIDSpace, kPrintBookletScriptProviderBoss, kPrintPrefix + 219)
DECLARE_PMID(kClassIDSpace, kPrintBookletPrintPrefsScriptProviderBoss, kPrintPrefix + 220)
DECLARE_PMID(kClassIDSpace, kPrintErrorStringServiceBoss, kPrintPrefix + 221)

DECLARE_PMID(kClassIDSpace, kCheckXRefsStatusProviderBoss, kPrintPrefix + 222)
DECLARE_PMID(kClassIDSpace, kPrintSignalMgrBoss, kPrintPrefix + 223)
DECLARE_PMID(kClassIDSpace, kCheckTextFragmentLinksProviderBoss, kPrintPrefix + 224)


//_______________________________________________________________________________________
// <Interface ID>
// IIDs
//_______________________________________________________________________________________
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCMDDATA, kPrintPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCLIENTITEMSUID, kPrintPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCLIENTITEMS_OBSOLETE, kPrintPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTOBJECT, kPrintPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTSETUPPROVIDER, kPrintPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPORT, kPrintPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSPORT, kPrintPrefix + 7)

// EPS Export IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTEPSCMDDATA, kPrintPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSEXPORTPREFERENCES, kPrintPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEPEXPORTPREFERENCES_OBSOLETE, kPrintPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSSEPEXPORTPREFSCMDDATA, kPrintPrefix + 11)

// New for Sherpa
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISIGNATUREHELPER_OBSOLETE, kPrintPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISIGNATUREHELPERCALLBACKS_OBSOLETE, kPrintPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRTSIGNATUREHELPERCALLBACKS_OBSOLETE, kPrintPrefix + 17)

// New For Hotaka
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCONTENTPREFS, kPrintPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IALLOWCOMPLETEFONTPREFERENCE_OBSOLETE, kPrintPrefix + 19)

// New for Anna
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATTENERSETUP, kPrintPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDATA, kPrintPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTSEPCMDDATA, kPrintPrefix + 22)
//gap

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDIALOGCMDDATA, kPrintPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRAPSTYLE, kPrintPrefix + 25)

//	Ink Manager
//gap

DECLARE_PMID(kInterfaceIDSpace, IID_ITRAPSTYLELISTMGR, kPrintPrefix + 27)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ITRAPSTYLEUIDDATA, kPrintPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTJOBDATA, kPrintPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDEVICEINFO, kPrintPrefix + 32)

DECLARE_PMID(kInterfaceIDSpace, IID_IINKMGR_SYNCHG, kPrintPrefix + 33)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINKMGRUTILS, kPrintPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRAPSTYLEUTILS, kPrintPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTVALIDATIONCMDDATA, kPrintPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCITERATIONPROVIDER, kPrintPrefix + 39)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTUTILS, kPrintPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTINSERTPSPROCPROVIDER, kPrintPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCITERATIONRESULT, kPrintPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPROGRESS, kPrintPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPRIVUTILS, kPrintPrefix + 46)

// New for Dragontail
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPREVIEWCONFIGSTATEDATA, kPrintPrefix + 47)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDATAHELPER, kPrintPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDATAHELPERSTRATEGY, kPrintPrefix + 49)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGFORCANCELBUTTON, kPrintPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGFORPRINTBUTTON,  kPrintPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGFORDIALOGTITLE,  kPrintPrefix + 52)

//galley
//gap

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPREVIEWDRAWSTRATDATA, kPrintPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPAGEINITIALIZER,      kPrintPrefix + 59)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTGLYPHTHRESHOLDPREF,      kPrintPrefix + 60)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPREFLIGHT, kPrintPrefix + 61)
//
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTUIPROVIDER, kPrintPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTRECORD, kPrintPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace,	IID_IEXPORTFILENAMEGENERATOR, kPrintPrefix + 64)

DECLARE_PMID(kInterfaceIDSpace,	IID_IPRINTCOPYCUSTOMDATAPROVIDER, kPrintPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace,	IID_ICUSTOMDATASUMMARYPROVIDER, kPrintPrefix + 66)

//For Print Booklet
DECLARE_PMID(kInterfaceIDSpace,	IID_IPRINTBOOKLETDATA, kPrintPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPRINTBOOKLETPRINTDATA, kPrintPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTBOOKLETUTILS, kPrintPrefix + 69)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTSCRIPTEVENTDATA, kPrintPrefix + 70)

// for PDF Passhtrough Mode
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPASSTHROUGHMODE, kPrintPrefix + 71)

// For printing master pages
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTMASTERPAGES, kPrintPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTSIGNALDATA, kPrintPrefix + 73)


//_______________________________________________________________________________________
// <Implementation ID>
// ImplementationIDs
//_______________________________________________________________________________________
//[]DECLARE_PMID(kImplementationIDSpace, kPrintMenuActionImpl, kPrintPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPrintSetupServiceImpl, kPrintPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPrintCmdImpl_obsolete, kPrintPrefix + 3)
#ifdef MACINTOSH
DECLARE_PMID(kImplementationIDSpace, kMPageSetupCmdImpl_obsolete, kPrintPrefix + 4)
#endif
DECLARE_PMID(kImplementationIDSpace, kPrintGetClientItemsCmdImpl_obsolete, kPrintPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPrintInitClientItemsCmdImpl_obsolete, kPrintPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPrintInitAGMCmdImpl_obsolete, kPrintPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPrintViaAGMCmdImpl_obsolete, kPrintPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPrintSaveDocClientItemsCmdImpl_obsolete, kPrintPrefix + 9)

DECLARE_PMID(kImplementationIDSpace, kPrintCmdDataImpl, kPrintPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPrintClientItemsImpl_obsolete, kPrintPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPrintObjectImpl_obsolete, kPrintPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPrintPortImpl, kPrintPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kPSPort, kPrintPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPSViewPortAttributesImpl, kPrintPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kNonPSViewPortAttributesImpl, kPrintPrefix + 16)

// EPS Export ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kEPSExportServiceImpl_reuse, kPrintPrefix + 17)   //GAP
DECLARE_PMID(kImplementationIDSpace, kEPSExportProviderImpl, kPrintPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kExportEPSCmdImpl, kPrintPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kExportEPSCmdDataImpl, kPrintPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCEPSExportPreferencesImpl, kPrintPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSessionEPSExportPreferencesImpl, kPrintPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSessionSEPExportPreferencesImpl_obsolete, kPrintPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSetEPSExportPrefsCmdImpl, kPrintPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSetSEPExportPrefsCmdImpl_obsolete, kPrintPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kEPSSEPExportPrefsCmdDataImpl, kPrintPrefix + 26)
//[] DECLARE_PMID(kImplementationIDSpace, kEPSExportTestMenuImpl, kPrintPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPrintPersistUIDDataImpl, kPrintPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPrintSaveAppClientItemsCmdImpl_obsolete, kPrintPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPrintProgressDrawEventHandlerImpl, kPrintPrefix + 31)

// New for Sherpa
//[]DECLARE_PMID(kImplementationIDSpace, kPrtErrorsDialogControllerImpl, kPrintPrefix + 32)
//[]DECLARE_PMID(kImplementationIDSpace, kPrtErrorsDialogDataImpl, kPrintPrefix + 33)
//[]DECLARE_PMID(kImplementationIDSpace, kPrtErrorsFindFontObserverImpl, kPrintPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPrintSignatureHelperImpl_obsolete, kPrintPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSignatureHelperCallbacksImpl_obsolete, kPrintPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPrtSignatureHelperCallbacksImpl_obsolete, kPrintPrefix + 37)

// New for Hotaka
DECLARE_PMID(kImplementationIDSpace, kPrintContentPrefsImpl, kPrintPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kAllowCompleteFontPrefImpl_obsolete, kPrintPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kSetAllowCompleteFontCmdImpl_obsolete, kPrintPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPersistPrintContentPrefsImpl, kPrintPrefix + 41)

// Gap left for hotaka expansion (42-49 unused, use for Hotaka conflicts)

// New for Anna
//gap

DECLARE_PMID(kImplementationIDSpace, kPrintDataImpl, kPrintPrefix + 76)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrintSavePrintDataCmdImpl, kPrintPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kExportSEPCmdImpl, kPrintPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kExportSEPCmdDataImpl, kPrintPrefix + 81)

DECLARE_PMID(kImplementationIDSpace, kPrintSaveFileDialogImpl_obsolete, kPrintPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kNonPrintDrawEventHandlerImpl, kPrintPrefix + 83)

//gap

DECLARE_PMID(kImplementationIDSpace, kPrintDialogCmdImpl, kPrintPrefix + 86)
//gap
DECLARE_PMID(kImplementationIDSpace, kTrapStyleImpl, kPrintPrefix + 88)

//	For Ink Manager dialog panel
//gap

DECLARE_PMID(kImplementationIDSpace, kTrapStyleScriptImpl, kPrintPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleAddCmdImpl, kPrintPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleScriptProviderImpl, kPrintPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleDeleteCmdImpl, kPrintPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleEditCmdImpl, kPrintPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleListMgrImpl, kPrintPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleLockInfoImpl, kPrintPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleSetCmdImpl, kPrintPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kAssignTrapStyleCmdImpl, kPrintPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleUIDDataImpl, kPrintPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kPrintStylePhase2ConversionImpl, kPrintPrefix + 108)

DECLARE_PMID(kImplementationIDSpace, kPrintJobDataImpl, kPrintPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kPrintActionCmdImpl, kPrintPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kNewPrintCmdImpl, kPrintPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kPrintGatherDataCmdImpl, kPrintPrefix + 112)

DECLARE_PMID(kImplementationIDSpace, kPrintUtilsImpl, kPrintPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kPrintPrivUtilsImpl, kPrintPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kPrintDeviceInfoImpl, kPrintPrefix + 115)

DECLARE_PMID(kImplementationIDSpace, kPrintDocPhase2ConversionImpl, kPrintPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleWSResponderImpl, kPrintPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleNDResponderImpl, kPrintPrefix + 118)

DECLARE_PMID(kImplementationIDSpace, kTrapStyleSyncServiceImpl, kPrintPrefix + 119)

DECLARE_PMID(kImplementationIDSpace, kInkMgrScriptProviderImpl, kPrintPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kInkMgrScriptImpl, kPrintPrefix + 121)

//gap

DECLARE_PMID(kImplementationIDSpace, kPrintNewWSResponderImpl, kPrintPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kPrintNewDocResponderImpl, kPrintPrefix + 125)
//gap
DECLARE_PMID(kImplementationIDSpace, kGenStlEditNameListObserverImpl, kPrintPrefix + 127)

//gap

DECLARE_PMID(kImplementationIDSpace, kLaterPrintNewDocResponderImpl, kPrintPrefix + 132)

//gap

DECLARE_PMID(kImplementationIDSpace, kSavePrintStyleDataCmdImpl, kPrintPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kInkMgrUtilsImpl, kPrintPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleUtilsImpl, kPrintPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kExportValidationCmdDataImpl, kPrintPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kExportValidationCmdImpl, kPrintPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kCheckXRefsStatusProviderImpl, kPrintPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kCheckTextFragmentLinksProviderImpl, kPrintPrefix + 142)
//gap
DECLARE_PMID(kImplementationIDSpace, kCheckFlashExportProviderImpl, kPrintPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kCheckColorsProviderImpl, kPrintPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kDocIterationServiceImpl, kPrintPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kDocIterationSplitterImpl, kPrintPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kCheckDCSPlatesProviderImpl, kPrintPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kXPGatherProviderImpl,       kPrintPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kInkGatherProviderImpl,      kPrintPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kCheckImageProviderImpl,     kPrintPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kTrapGatherProviderImpl,     kPrintPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kGatherFontProviderImpl,     kPrintPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kCheckConditionalTextProviderImpl, kPrintPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kThumbnailProviderImpl,     kPrintPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kInsertPSProcServiceImpl,     kPrintPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kInsertPSProcProviderImpl,     kPrintPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kDocIterationResultPrintAdapterImpl, kPrintPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kDocIterationResultGenericImpl,      kPrintPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kPrintProgressImpl,     kPrintPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kCheckEPSProviderImpl, kPrintPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kCheckTextProviderImpl, kPrintPrefix + 166)

DECLARE_PMID(kImplementationIDSpace, kPrintScriptEventDataImpl, kPrintPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kPrintEventScriptProviderImpl, kPrintPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kPrintPropScriptProviderImpl, kPrintPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kPrintPrefsScriptProviderImpl, kPrintPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kScriptEventPrintSetupProviderImpl, kPrintPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kGenStyleCmdDataImpl, kPrintPrefix + 172)

// New for Dragontail
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewConfigServiceImpl, kPrintPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewConfigProviderImpl, kPrintPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewConfigStateImpl, kPrintPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewFeatureServiceImpl, kPrintPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewFeatureProviderImpl, kPrintPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewConfigStateDataImpl, kPrintPrefix + 178)

DECLARE_PMID(kImplementationIDSpace, kCPrintDataHelperImpl, kPrintPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kBookPrintDataHelperImpl, kPrintPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kStylePrintDataHelperImpl, kPrintPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kEPSExportPrefsScriptProviderImpl, kPrintPrefix + 182)
// gap
DECLARE_PMID(kImplementationIDSpace, kPrintGlyphThresholdPrefImpl, kPrintPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kSetPrintGlyphThresholdPrefCmdImpl, kPrintPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kDataHelperStrategyServiceImpl, kPrintPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kDataHelperStrategyProviderImpl, kPrintPrefix + 187)

DECLARE_PMID(kImplementationIDSpace, kTinFontsWarningDialogCancelDataImpl,	kPrintPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kTinFontsWarningDialogPrintDataImpl,	kPrintPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kTinFontsWarningDialogTitleImpl,		kPrintPrefix + 190)

//InCopy
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintActionCmdImpl, kPrintPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kInCopyNewPrintCmdImpl, kPrintPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kPrintGalleyScriptProviderImpl, kPrintPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kPrintLayoutScriptProviderImpl, kPrintPrefix + 208)

DECLARE_PMID(kImplementationIDSpace, kPrintPreflightImpl, kPrintPrefix + 220)

DECLARE_PMID(kImplementationIDSpace, kPrintPreviewDrawStrategyImpl, kPrintPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kPrintPreviewDrawStratDataImpl, kPrintPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kDocPrintPageInitializerImpl,   kPrintPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kTinFontsWarningDialogCmdImpl, kPrintPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kTrapStyleListPhase2ConversionImpl, kPrintPrefix + 234)
//
DECLARE_PMID(kImplementationIDSpace, kPrintRecordImpl, kPrintPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kExportFileNameGeneratorImpl, kPrintPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kCustomDataSummaryServiceImpl, kPrintPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kCustomDataSummaryProviderImpl, kPrintPrefix + 238)

//For Print Booklet
DECLARE_PMID(kImplementationIDSpace, kPrintBookletCmdImpl, kPrintPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletDataImpl, kPrintPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletPrintDataHelperImpl, kPrintPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletPrintDataImpl, kPrintPrefix + 242 )
//gap
DECLARE_PMID(kImplementationIDSpace, kPrintBookletProviderImpl, kPrintPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletUtilsImpl, kPrintPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletPropScriptProviderImpl, kPrintPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletPrintPropScriptProviderImpl, kPrintPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kPrintErrorStringServiceImpl, kPrintPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletSaveDataCmdImpl, kPrintPrefix + 249 )

DECLARE_PMID(kImplementationIDSpace, kPrintSignalDataImpl, kPrintPrefix + 250 )
DECLARE_PMID(kImplementationIDSpace, kBeforePrintSignalResponderServiceImpl, kPrintPrefix + 251 )
DECLARE_PMID(kImplementationIDSpace, kAfterPrintSignalResponderServiceImpl, kPrintPrefix + 252 )
DECLARE_PMID(kImplementationIDSpace, kFailedPrintSignalResponderServiceImpl, kPrintPrefix + 253 )

//_______________________________________________________________________________________
// <Widget ID>
//	Widget IDs
//_______________________________________________________________________________________
//_______________________________________________________________________________________
// <Service ID>
//	Service IDs
//_______________________________________________________________________________________
DECLARE_PMID(kServiceIDSpace, kPrintSetupService, kPrintPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kFlattenerSetupService, kPrintPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kPrintSelectableDialogService, kPrintPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kDocIterationService, kPrintPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kPrintInsertPSProcService, kPrintPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kPrintDataHelperStrategyService, kPrintPrefix + 6)

//InCopy
//DECLARE_PMID(kServiceIDSpace, kPrintPanelPickerService, kPrintPrefix + 10)
//DECLARE_PMID(kServiceIDSpace, kInCopyPrintDialogService, kPrintPrefix + 11)
//
DECLARE_PMID(kServiceIDSpace,kPrintUIServiceID,       kPrintPrefix + 12)
DECLARE_PMID(kServiceIDSpace,kPrintCopyCustomDataService,       kPrintPrefix + 13)
DECLARE_PMID(kServiceIDSpace,kCustomDataSummaryService,    kPrintPrefix + 14)
DECLARE_PMID(kServiceIDSpace,kBeforePrintSignalResponderService,    kPrintPrefix + 15)
DECLARE_PMID(kServiceIDSpace,kAfterPrintSignalResponderService,    kPrintPrefix + 16)
DECLARE_PMID(kServiceIDSpace,kFailedPrintSignalResponderService,    kPrintPrefix + 17)


//_______________________________________________________________________________________
// <Error ID>
//	Error IDs
//_______________________________________________________________________________________
DECLARE_PMID(kErrorIDSpace, kBIBErrorStartNumError,				kPrintPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kBRVErrorStartNumError,				kPrintPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kAGMErrorStartNumError,				kPrintPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kCTErrorStartNumError,				kPrintPrefix + 50)
DECLARE_PMID(kErrorIDSpace, kK2ErrorStartNumError,				kPrintPrefix + 100)

DECLARE_PMID(kErrorIDSpace, kEPSExportError,					kPrintPrefix + 200)
DECLARE_PMID(kErrorIDSpace, kEPSInitializationError,			kPrintPrefix + 201)
DECLARE_PMID(kErrorIDSpace, kEPSPreferenceError,				kPrintPrefix + 202)
DECLARE_PMID(kErrorIDSpace, kEPSOutputFileError,				kPrintPrefix + 203)

DECLARE_PMID(kErrorIDSpace, kTrapErrIndexOutOfRange,			kPrintPrefix + 210)
DECLARE_PMID(kErrorIDSpace, kTrapErrNullParameter,				kPrintPrefix + 211)
DECLARE_PMID(kErrorIDSpace, kTrapErrNameConflict,				kPrintPrefix + 212)

DECLARE_PMID(kErrorIDSpace, kPageSetupError,					kPrintPrefix + 215)
DECLARE_PMID(kErrorIDSpace, kPrintingError,						kPrintPrefix + 216)

DECLARE_PMID(kErrorIDSpace, kInkMgrErrCantAliasProcessInk,		kPrintPrefix + 220)

DECLARE_PMID(kErrorIDSpace, kPrtErrorInvalidDict,				kPrintPrefix + 225)
DECLARE_PMID(kErrorIDSpace, kPrtErrorInvalidSelectorObject,		kPrintPrefix + 226)
DECLARE_PMID(kErrorIDSpace, kPrtErrorCreatePrintRecord,			kPrintPrefix + 227)
DECLARE_PMID(kErrorIDSpace, kPrtErrorInvalidPrintRecord,		kPrintPrefix + 228)
DECLARE_PMID(kErrorIDSpace, kPrtErrorUnsupportedPSDevice,		kPrintPrefix + 229)
DECLARE_PMID(kErrorIDSpace, kPrtErrorNoPrintersInstalled,		kPrintPrefix + 230)
DECLARE_PMID(kErrorIDSpace, kPrtErrorInvalidPrinterName,		kPrintPrefix + 231)
DECLARE_PMID(kErrorIDSpace, kPrtErrorInvalidPPDName,			kPrintPrefix + 232)
DECLARE_PMID(kErrorIDSpace, kPrtErrorPlatformPrintDialog,		kPrintPrefix + 233)
DECLARE_PMID(kErrorIDSpace, kPrtErrorPrintDataRestore,			kPrintPrefix + 234)
DECLARE_PMID(kErrorIDSpace, kPrtErrorDefaultPrinter,			kPrintPrefix + 235)
DECLARE_PMID(kErrorIDSpace, kPrtErrorPrintPreview,				kPrintPrefix + 236)

DECLARE_PMID(kErrorIDSpace, kBinaryEPSDontShowAgainID,			kPrintPrefix + 237)
DECLARE_PMID(kErrorIDSpace, kBlendSpaceDontShowAgainID,			kPrintPrefix + 238)

DECLARE_PMID(kErrorIDSpace, kPrtErrorMaxSpots_SimOPOn,			kPrintPrefix + 239)
DECLARE_PMID(kErrorIDSpace, kPrtErrorMaxSpots_HasXP,			kPrintPrefix + 240)
DECLARE_PMID(kErrorIDSpace, kPrtErrorMaxSpots_DoingSeps,		kPrintPrefix + 241)
DECLARE_PMID(kErrorIDSpace, kOversetTextDontShowAgainID,		kPrintPrefix + 242)

//Print Booklet Errors
DECLARE_PMID(kErrorIDSpace, kBleedBetPagesGTHalfSpaceBetPagesError,		kPrintPrefix + 243)

DECLARE_PMID(kErrorIDSpace, kPrtErrorPrintMacTelFile,			kPrintPrefix + 244)
DECLARE_PMID(kErrorIDSpace, kInconsistentConditionTagsDontShowAgainID,	kPrintPrefix + 245)
DECLARE_PMID(kErrorIDSpace, kFlashExportXPDontShowAgainID,		kPrintPrefix + 246)
DECLARE_PMID(kErrorIDSpace, kFlashExportFormDontShowAgainID,	kPrintPrefix + 247)
DECLARE_PMID(kErrorIDSpace, kFlashExportButtonXPDontShowAgainID,	kPrintPrefix + 248)
DECLARE_PMID(kErrorIDSpace, kBadXRefStatusDontShowAgainID,	kPrintPrefix + 249)

//_______________________________________________________________________________________
// <Action ID>
// ActionIDs
//_______________________________________________________________________________________
//DECLARE_PMID(kActionIDSpace, kPrintPageSetupActionID, kPrintPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPrintWithGridsActionID, kPrintPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPrintActionID, kPrintPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPrintSepActionID, kPrintPrefix + 4)
DECLARE_PMID(kActionIDSpace, kPrintGridsOnlyActionID, kPrintPrefix + 5)
DECLARE_PMID(kActionIDSpace, kInkMgrActionID, kPrintPrefix + 6)


//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________
DECLARE_PMID(kViewPortAttrIDSpace, kSpotOVPFlagsVPAttr, kPrintPrefix + 1)
	enum
	{
		// The following set up the basic spot/overprint mode.  Note that it's the responsibility
		// of the attribute initializer to examine the front view for OPP on/off when determining
		// whether the UI entry of "simulate screen" means SimPressCompOnly (OPP on) or
		// SimScreenNoOPP (OPP off).
		kSOVP_Mode_Mask					= (3L<<0),	// Mask used to derive mode:
		kSOVP_Mode_Legacy				= (0L<<0),	// - preserve spots, no comp path, eps/pdf preserve
		kSOVP_Mode_SimPress				= (1L<<0),	// - simulate spots/ovp in output, dual path on PS
		kSOVP_Mode_SimPressCompOnly		= (2L<<0),	// - simulate spots/ovp in output, comp path only
		kSOVP_Mode_SimScreenNoOPP		= (3L<<0)	// - simulate screen with OPP OFF: no spots, no ovp
	};
	
DECLARE_PMID(kViewPortAttrIDSpace, kPrintColorsInBlackVPAttr, kPrintPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintHiddenLayersVPAttr, kPrintPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintBaselineGridsVPAttr, kPrintPrefix + 4)
// DECLARE_PMID(kViewPortAttrIDSpace, kPrintDocumentGridsVPAttr, kPrintPrefix + 5)	This has been unused for several releases, no way to print/export document grids. 1-11-2005.
DECLARE_PMID(kViewPortAttrIDSpace, kPrintRulerGuidesVPAttr, kPrintPrefix + 6)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintColumnMarginGuidesVPAttr, kPrintPrefix + 7)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintWYSIWYGGridsGuidesVPAttr, kPrintPrefix + 8)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintIgnoreOverprintVPAttr, kPrintPrefix + 9)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintSimulatingPaperColor, kPrintPrefix + 10)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintFrameBaselineGridsVPAttr, kPrintPrefix + 11)
DECLARE_PMID(kViewPortAttrIDSpace, kPrintLayersVPAttr, kPrintPrefix + 12)
	enum
	{
		// Viewport Attribute settings for the kPrintLayersVPAttr parameter...
		// The following set up which layers we are drawing. Normally, the visible layers are
		// drawn to screen. When printing or exporting to PDF, the user now has the option of
		// drawing All Layers, Visible Layers or Visible and Printable Layers.
		kPrintLayers_Mask				= (3L<<0),	// Mask used to derive mode:
		kPrintLayers_Unknown			= (0L<<0),	// - unknown or hasn't been set yet
		kPrintLayers_AllLayers			= (1L<<0),	// - print / export all layers
		kPrintLayers_VisibleLayers		= (2L<<0),	// - print / export visible layers
		kPrintLayers_VisiblePrintableLayers	= (3L<<0)	// - print / export visible & printable layers
	};

//
//Script Element IDs
//

//Events
DECLARE_PMID(kScriptInfoIDSpace, kBeforePrintEventScriptElement,				kPrintPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kAfterPrintEventScriptElement,					kPrintPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPrintPreferenceObjectScriptElement,			kPrintPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kInkObjectScriptElement,						kPrintPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kTrapStyleObjectScriptElement,					kPrintPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBookletObjectScriptElement,				kPrintPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBookletPrintPrefsObjectScriptElement,	kPrintPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kPrintEventObjectScriptElement,				kPrintPrefix + 16)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kPrintDocumentsMethodScriptElement,			kPrintPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kPrintMethodScriptElement,						kPrintPrefix + 81)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kDeleteTrapStyleMethodScriptElement,			kPrintPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBookletMethodScriptElement,				kPrintPrefix + 84)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kEPSExColorSpaceEnumScriptElement,				kPrintPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kEPSExColorSpacePropertyScriptElement,			kPrintPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kEPSPreviewEnumScriptElement,					kPrintPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kEPSPreviewPropertyScriptElement,				kPrintPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kEPSExportPrefsObjectScriptElement,			kPrintPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kEPSExportPrefsPropertyScriptElement,			kPrintPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kEPSFontEmbeddingEnumScriptElement,			kPrintPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kEPSFontEmbeddingPropertyScriptElement,		kPrintPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kEPSSpreadsPropertyScriptElement,				kPrintPrefix + 98)

DECLARE_PMID(kScriptInfoIDSpace, kActivePrinterStylePropertyScriptElement,		kPrintPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kPrintUseDocumentBleedPropertyScriptElement,	kPrintPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kPrintIncludeSlugPropertyScriptElement,		kPrintPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kBlackAnglePropertyScriptElement,				kPrintPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kBlackFrequencyPropertyScriptElement,			kPrintPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kCyanAnglePropertyScriptElement,				kPrintPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kCyanFrequencyPropertyScriptElement,			kPrintPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kYellowAnglePropertyScriptElement,				kPrintPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kYellowFrequencyPropertyScriptElement,			kPrintPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kMagentaAnglePropertyScriptElement,			kPrintPrefix + 119)
DECLARE_PMID(kScriptInfoIDSpace, kMagentaFrequencyPropertyScriptElement,		kPrintPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBlackPropertyScriptElement,				kPrintPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kPrintCyanPropertyScriptElement,				kPrintPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kPrintMagentaPropertyScriptElement,			kPrintPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kPrintYellowPropertyScriptElement,				kPrintPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kAllPrintersMarksPropertyScriptElement,		kPrintPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kDeviceTypePropertyScriptElement,				kPrintPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kPrintToPropertyScriptElement,					kPrintPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kPPDFilePropertyScriptElement,					kPrintPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kPrintRecordPropertyScriptElement,				kPrintPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kBleedBottomPropertyScriptElement,				kPrintPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kBleedInsidePropertyScriptElement,				kPrintPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kBleedMarksPropertyScriptElement,				kPrintPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kBleedOutsidePropertyScriptElement,			kPrintPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kBleedTopPropertyScriptElement,				kPrintPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kCollatingPropertyScriptElement,				kPrintPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kColorBarsPropertyScriptElement,				kPrintPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kMarkTypePropertyScriptElement,				kPrintPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kColorOutputPropertyScriptElement,				kPrintPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeAnglePropertyScriptElement,			kPrintPrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFrequencyPropertyScriptElement,		kPrintPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kCopiesPropertyScriptElement,					kPrintPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kCRDPropertyScriptElement,						kPrintPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kCropMarksPropertyScriptElement,				kPrintPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kMarkOffsetPropertyScriptElement,				kPrintPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kDataFormatPropertyScriptElement,				kPrintPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kDownloadPPDFontsPropertyScriptElement,		kPrintPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerStyleNamePropertyScriptElement,		kPrintPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kMarkLineWeightPropertyScriptElement,			kPrintPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kFlipPropertyScriptElement,					kPrintPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kIntentPropertyScriptElement,					kPrintPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kFontDownloadingPropertyScriptElement,			kPrintPrefix + 151)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreSpreadOverridesPropertyScriptElement,	kPrintPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kResolutionPropertyScriptElement,				kPrintPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kNegativePropertyScriptElement,				kPrintPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kOmitBitmapsPropertyScriptElement,				kPrintPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kOmitEPSPropertyScriptElement,					kPrintPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kOmitPDFPropertyScriptElement,					kPrintPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kOPIImageReplacementPropertyScriptElement,		kPrintPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kPageInformationPropertyScriptElement,			kPrintPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kPagePositionPropertyScriptElement,			kPrintPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kPrPageRangePropertyScriptElement,				kPrintPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPaperGapPropertyScriptElement,				kPrintPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kPaperHeightPropertyScriptElement,				kPrintPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kPaperOffsetPropertyScriptElement,				kPrintPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizePropertyScriptElement,				kPrintPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizeListPropertyScriptElement,			kPrintPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kPaperTransversePropertyScriptElement,			kPrintPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kPaperWidthPropertyScriptElement,				kPrintPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kPostscriptLevelPropertyScriptElement,			kPrintPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kPPDPropertyScriptElement,						kPrintPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kPPDListPropertyScriptElement,					kPrintPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kBleedChainPropertyScriptElement,				kPrintPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBlankPagesPropertyScriptElement,			kPrintPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterPropertyScriptElement,					kPrintPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterListPropertyScriptElement,				kPrintPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kPrintFilePropertyScriptElement,				kPrintPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kPrintGuidesGridsPropertyScriptElement,		kPrintPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kSpotAnglePropertyScriptElement,				kPrintPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kSpotFrequencyPropertyScriptElement,			kPrintPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kPrintMasterPagesPropertyScriptElement,		kPrintPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kPrintNonPrintingPropertyScriptElement,		kPrintPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kPrintOrientationPropertyScriptElement,		kPrintPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kPrintSpreadsPropertyScriptElement,			kPrintPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kPrintToDiskPropertyScriptElement,				kPrintPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizeSelectorPropertyScriptElement,		kPrintPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kProfilePropertyScriptElement,					kPrintPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kRegistrationMarksPropertyScriptElement,		kPrintPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kReverseOrderPropertyScriptElement,			kPrintPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kScaleHeightPropertyScriptElement,				kPrintPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kScaleModeEnumScriptElement,					kPrintPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kScaleModePropertyScriptElement,				kPrintPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kScaleProportionalPropertyScriptElement,		kPrintPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kScaleWidthPropertyScriptElement,				kPrintPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kScreeningPropertyScriptElement,				kPrintPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kScreeningListPropertyScriptElement,			kPrintPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kSendImageDataPropertyScriptElement,			kPrintPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kSequencePropertyScriptElement,				kPrintPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kSimulateOverprintPropertyScriptElement,		kPrintPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kSourceSpacePropertyScriptElement,				kPrintPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kTextAsBlackPropertyScriptElement,				kPrintPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kThumbnailsPropertyScriptElement,				kPrintPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kThumbnailsPerPagePropertyScriptElement,		kPrintPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kTilePropertyScriptElement,					kPrintPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kTilingOverlapPropertyScriptElement,			kPrintPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kTilingTypePropertyScriptElement,				kPrintPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kTrappingPropertyScriptElement,				kPrintPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kAliasInkNamePropertyScriptElement,			kPrintPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kAnglePropertyScriptElement,					kPrintPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kConvertToProcessPropertyScriptElement,		kPrintPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kFrequencyPropertyScriptElement,				kPrintPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kPrintPrefsPropertyScriptElement,				kPrintPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kIsProcessInkPropertyScriptElement,			kPrintPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizeRectPropertyScriptElement,			kPrintPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kNeutralDensityPropertyScriptElement,			kPrintPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kPrintInkPropertyScriptElement,				kPrintPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kSolidityPropertyScriptElement,				kPrintPrefix + 217)
DECLARE_PMID(kScriptInfoIDSpace, kTrapOrderPropertyScriptElement,				kPrintPrefix + 218)
DECLARE_PMID(kScriptInfoIDSpace, kInkTypePropertyScriptElement,					kPrintPrefix + 219)
DECLARE_PMID(kScriptInfoIDSpace, kImageablePaperSizeRectPropertyScriptElement,	kPrintPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kPaperHeightRangePropertyScriptElement,		kPrintPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kPaperWidthRangePropertyScriptElement,			kPrintPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kPaperOffsetRangePropertyScriptElement,		kPrintPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kSeparationScreeningPropertyScriptElement,		kPrintPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeScreeningPropertyScriptElement,		kPrintPrefix + 225)

DECLARE_PMID(kScriptInfoIDSpace, kTrapDefaultWidthPropertyScriptElement,		kPrintPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kTrapBlackWidthPropertyScriptElement,			kPrintPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kTrapJoinStylePropertyScriptElement,			kPrintPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kTrapEndStylePropertyScriptElement,			kPrintPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kTrapObjectsToImagesPropertyScriptElement,		kPrintPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kTrapImagesToImagesPropertyScriptElement,		kPrintPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kTrapInternalImagesPropertyScriptElement,		kPrintPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kTrapOneBitImagesPropertyScriptElement,		kPrintPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kTrapImagePlacementPropertyScriptElement,		kPrintPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kTrapStepThresholdPropertyScriptElement,		kPrintPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kTrapBlackColorPropertyScriptElement,			kPrintPrefix + 236)
DECLARE_PMID(kScriptInfoIDSpace, kTrapBlackDensityPropertyScriptElement,		kPrintPrefix + 237)
DECLARE_PMID(kScriptInfoIDSpace, kTrapSlidingTrapPropertyElement,				kPrintPrefix + 238)
DECLARE_PMID(kScriptInfoIDSpace, kTrapColorReductionPropertyScriptElement,		kPrintPrefix + 239)

DECLARE_PMID(kScriptInfoIDSpace, kEPSSendImageDataPropertyScriptElement,		kPrintPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveColorNumbersPropertyScriptElement,	kPrintPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kBitmapPrintingPropertyScriptElement,			kPrintPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kBitmapResolutionPropertyScriptElement,		kPrintPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLayersEnumScriptElement,					kPrintPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLayersPropertyScriptElement,				kPrintPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentPrintUIOptionPropertyScriptElement,	kPrintPrefix + 246)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kRenderingIntentEnumScriptElement,				kPrintPrefix2 + 1)
DECLARE_PMID(kScriptInfoIDSpace, kMarkLineWeightEnumScriptElement,				kPrintPrefix2 + 2)
DECLARE_PMID(kScriptInfoIDSpace, kMarkTypeEnumScriptElement,					kPrintPrefix2 + 3)
DECLARE_PMID(kScriptInfoIDSpace, kColorOutputModeEnumScriptElement,				kPrintPrefix2 + 4)
DECLARE_PMID(kScriptInfoIDSpace, kDataFormatEnumScriptElement,					kPrintPrefix2 + 5)
DECLARE_PMID(kScriptInfoIDSpace, kFlipEnumScriptElement,						kPrintPrefix2 + 6)
DECLARE_PMID(kScriptInfoIDSpace, kFontDownloadingEnumScriptElement,				kPrintPrefix2 + 7)
DECLARE_PMID(kScriptInfoIDSpace, kPagePositionEnumScriptElement,				kPrintPrefix2 + 8)
DECLARE_PMID(kScriptInfoIDSpace, kPostscriptLevelEnumScriptElement,				kPrintPrefix2 + 9)
DECLARE_PMID(kScriptInfoIDSpace, kPrintOrientationEnumScriptElement,			kPrintPrefix2 + 10)
DECLARE_PMID(kScriptInfoIDSpace, kSendImageDataEnumScriptElement,				kPrintPrefix2 + 11)
DECLARE_PMID(kScriptInfoIDSpace, kSequenceEnumScriptElement,					kPrintPrefix2 + 12)
DECLARE_PMID(kScriptInfoIDSpace, kSourceSpaceEnumScriptElement,					kPrintPrefix2 + 13)
DECLARE_PMID(kScriptInfoIDSpace, kThumbsPerPageEnumScriptElement,				kPrintPrefix2 + 14)
DECLARE_PMID(kScriptInfoIDSpace, kTilingTypeEnumScriptElement,					kPrintPrefix2 + 15)
DECLARE_PMID(kScriptInfoIDSpace, kTrappingEnumScriptElement,					kPrintPrefix2 + 16)
DECLARE_PMID(kScriptInfoIDSpace, kInkTrapTypeEnumScriptElement,					kPrintPrefix2 + 17)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterStyleEnumScriptElement,				kPrintPrefix2 + 18)
DECLARE_PMID(kScriptInfoIDSpace, kCRDEnumScriptElement,							kPrintPrefix2 + 19)
DECLARE_PMID(kScriptInfoIDSpace, kPageRangeEnumScriptElement,					kPrintPrefix2 + 20)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizeEnumScriptElement,					kPrintPrefix2 + 21)
DECLARE_PMID(kScriptInfoIDSpace, kPPDEnumScriptElement,							kPrintPrefix2 + 22)
DECLARE_PMID(kScriptInfoIDSpace, kProfileEnumScriptElement,						kPrintPrefix2 + 23)
DECLARE_PMID(kScriptInfoIDSpace, kScreeningEnumScriptElement,					kPrintPrefix2 + 24)
DECLARE_PMID(kScriptInfoIDSpace, kPaperSizesEnumScriptElement,					kPrintPrefix2 + 25)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterEnumScriptElement,						kPrintPrefix2 + 26)

DECLARE_PMID(kScriptInfoIDSpace, kTrapImagePlacementEnumScriptElement,			kPrintPrefix2 + 27)
DECLARE_PMID(kScriptInfoIDSpace, kTrapJoinStyleEnumScriptElement,				kPrintPrefix2 + 28)
DECLARE_PMID(kScriptInfoIDSpace, kTrapEndStyleEnumScriptElement,				kPrintPrefix2 + 29)

DECLARE_PMID(kScriptInfoIDSpace, kEPSSendImageDataEnumScriptElement,			kPrintPrefix2 + 30)

// InCopy Print Scripting
DECLARE_PMID(kScriptInfoIDSpace, kUseGalleySettingsPropertyScriptElement,		kPrintPrefix2 + 31)
DECLARE_PMID(kScriptInfoIDSpace, kPrintParaStylesPropertyScriptElement,			kPrintPrefix2 + 32)
DECLARE_PMID(kScriptInfoIDSpace, kPrintNotesPropertyScriptElement,				kPrintPrefix2 + 33)
DECLARE_PMID(kScriptInfoIDSpace, kPrintNotesBackgroundPropertyScriptElement,	kPrintPrefix2 + 34)
DECLARE_PMID(kScriptInfoIDSpace, kPrintChangesPropertyScriptElement,			kPrintPrefix2 + 35)
DECLARE_PMID(kScriptInfoIDSpace, kPrintChangesBackgroundPropertyScriptElement,	kPrintPrefix2 + 36)
DECLARE_PMID(kScriptInfoIDSpace, kPrintAccurateLineEndingsPropertyScriptElement,kPrintPrefix2 + 37)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLineRangePropertyScriptElement,			kPrintPrefix2 + 38)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLineNumbersPropertyScriptElement,		kPrintPrefix2 + 39)
DECLARE_PMID(kScriptInfoIDSpace, kPrintMultipleColumnsPropertyScriptElement,	kPrintPrefix2 + 41)
DECLARE_PMID(kScriptInfoIDSpace, kPrintTextColumnWidthPropertyScriptElement,	kPrintPrefix2 + 42)
DECLARE_PMID(kScriptInfoIDSpace, kPrintPageInfoPropertyScriptElement,			kPrintPrefix2 + 43)
DECLARE_PMID(kScriptInfoIDSpace, kPrintStoryInfoPropertyScriptElement,			kPrintPrefix2 + 44)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kPrintAllStoriesPropertyScriptElement,			kPrintPrefix2 + 49)
DECLARE_PMID(kScriptInfoIDSpace, kPrintGalleyLeadingEnumScriptElement,			kPrintPrefix2 + 50)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLayoutPreferenceObjectScriptElement,		kPrintPrefix2 + 51)
DECLARE_PMID(kScriptInfoIDSpace, kPrintGalleyPreferenceObjectScriptElement,		kPrintPrefix2 + 52)
DECLARE_PMID(kScriptInfoIDSpace, kPrintLayoutPrefsPropertyScriptElement,		kPrintPrefix2 + 53)
DECLARE_PMID(kScriptInfoIDSpace, kPrintGalleyPrefsPropertyScriptElement,		kPrintPrefix2 + 54)
DECLARE_PMID(kScriptInfoIDSpace, kAllOrVisibleEnumScriptElement,				kPrintPrefix2 + 55)
//Print Booklet
DECLARE_PMID(kScriptInfoIDSpace, kPBPageRangeEnumScriptElement,					kPrintPrefix2 + 56)
DECLARE_PMID(kScriptInfoIDSpace, kPBBookletTypeEnumScriptElement,				kPrintPrefix2 + 57)
DECLARE_PMID(kScriptInfoIDSpace, kPBSignatureSizeEnumScriptElement,				kPrintPrefix2 + 58)

DECLARE_PMID(kScriptInfoIDSpace, kDocumentPrintUIOptionsEnumScriptElement,		kPrintPrefix2 + 59)

//Print Booklet Properties
DECLARE_PMID(kScriptInfoIDSpace, kPBBookletTypePropertyScriptElement,			kPrintPrefix2 + 60)
DECLARE_PMID(kScriptInfoIDSpace, kPBSpaceBetPagesPropertyScriptElement,			kPrintPrefix2 + 61)
DECLARE_PMID(kScriptInfoIDSpace, kPBBleedBetPagesPropertyScriptElement,			kPrintPrefix2 + 62)
DECLARE_PMID(kScriptInfoIDSpace, kPBCreepPropertyScriptElement,					kPrintPrefix2 + 63)
DECLARE_PMID(kScriptInfoIDSpace, kPBSignatureSizePropertyScriptElement,			kPrintPrefix2 + 64)
DECLARE_PMID(kScriptInfoIDSpace, kPBTopMarginPropertyScriptElement,				kPrintPrefix2 + 65)
DECLARE_PMID(kScriptInfoIDSpace, kPBBottomMarginPropertyScriptElement,			kPrintPrefix2 + 66)
DECLARE_PMID(kScriptInfoIDSpace, kPBLeftMarginPropertyScriptElement,			kPrintPrefix2 + 67)
DECLARE_PMID(kScriptInfoIDSpace, kPBRightMarginPropertyScriptElement,			kPrintPrefix2 + 68)
DECLARE_PMID(kScriptInfoIDSpace, kPBAutoAdjMarginPropertyScriptElement,			kPrintPrefix2 + 69)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBookletPropertyScriptElement,			kPrintPrefix2 + 70)
DECLARE_PMID(kScriptInfoIDSpace, kPrintBookletPrintPrefsPropertyScriptElement,	kPrintPrefix2 + 71)
DECLARE_PMID(kScriptInfoIDSpace, kPBChainMarginPropertyScriptElement,			kPrintPrefix2 + 72)
DECLARE_PMID(kScriptInfoIDSpace, kPBPrintBlankPrinterSpreadsPropertyScriptElement, kPrintPrefix2 + 73)

// PDF Passthrough mode
DECLARE_PMID(kScriptInfoIDSpace, kPDFPassthroughModePropertyScriptElement,		kPrintPrefix2 + 74)

//GUIDS
// {496F0BE3-7834-11d2-AAF0-00C04FA37726}
#define kPrintPref_CLSID { 0x496f0be3, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {DC9C36DD-A297-4c81-85C0-6E203D13ADFC}
#define kInk_CLSID { 0xdc9c36dd, 0xa297, 0x4c81, { 0x85, 0xc0, 0x6e, 0x20, 0x3d, 0x13, 0xad, 0xfc } }
// {0BA359C1-FF1A-45ed-A999-9476BE2D2A03}
#define kInks_CLSID { 0xba359c1, 0xff1a, 0x45ed, { 0xa9, 0x99, 0x94, 0x76, 0xbe, 0x2d, 0x2a, 0x3 } }
// {1F276696-EDD9-4a86-9CF1-F23941F0D0A8}
#define kTrapStyle_CLSID { 0x1f276696, 0xedd9, 0x4a86, { 0x9c, 0xf1, 0xf2, 0x39, 0x41, 0xf0, 0xd0, 0xa8 } }
// {6F31E0A0-1BD2-4f9b-A353-2B4A548D8834}
#define kTrapStyles_CLSID { 0x6f31e0a0, 0x1bd2, 0x4f9b, { 0xa3, 0x53, 0x2b, 0x4a, 0x54, 0x8d, 0x88, 0x34 } }
// {4034A250-56C9-4cd5-B1D7-EAA1EA932F25}
#define kEPSExportPrefs_CLSID {0x4034a250, 0x56c9, 0x4cd5, { 0xb1, 0xd7, 0xea, 0xa1, 0xea, 0x93, 0x2f, 0x25 }}
// {DE277C92-AF39-4af9-B103-826C68EFDD76}
#define kLayoutPrintPref_CLSID { 0xde277c92, 0xaf39, 0x4af9, { 0xb1, 0x3, 0x82, 0x6c, 0x68, 0xef, 0xdd, 0x76 } }
// {D53766C9-07EA-4c9d-9938-EB1F64D6BA34}
#define kGalleyPrintPref_CLSID { 0xd53766c9, 0x7ea, 0x4c9d, { 0x99, 0x38, 0xeb, 0x1f, 0x64, 0xd6, 0xba, 0x34 } }
// {39323485-72A0-4caa-97C5-43A51572A544}
#define kPrintBooklet_CLSID { 0x39323485, 0x72a0, 0x4caa, { 0x97, 0xc5, 0x43, 0xa5, 0x15, 0x72, 0xa5, 0x44 } }
// {7D4B7FD7-5763-40bb-A3C4-7F07B52DAE94}
#define kPrintBookletPrint_CLSID { 0x7d4b7fd7, 0x5763, 0x40bb, { 0xa3, 0xc4, 0x7f, 0x7, 0xb5, 0x2d, 0xae, 0x94 } }
// {8A78B37F-82D3-4d66-8CDD-674006116D32}
#define kPrintEvent_CLSID { 0x8a78b37f, 0x82d3, 0x4d66, { 0x8c, 0xdd, 0x67, 0x40, 0x6, 0x11, 0x6d, 0x32 } }

//ScriptIDs
enum PrintScriptIDs {
	c_PrintEvent				=	'cPEv',

	e_BeforePrint				=	'bfPr',
	e_AfterPrint				=	'afPr',

	p_DocumentPrintUIOption		=	'pdpu',

	en_DocumentPrintUIOptions	=	'dpuo',
	en_SuppressPrintProgress	=	'spps',
	en_SuppressPrintWarnings	=	'spwr',
	en_SuppressPrintDialog		=	'spdg',
	en_SuppressFileSaveDialog	=	'sfad',

} ;


// Miscellaneous defines
#define kPrintDrawEventLinkedItem	kPrintPrefix + 1
#define kPrintDrawEventContent		kPrintPrefix + 2

#endif // __PrintID__

// End, PrintID.h.
