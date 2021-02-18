//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyCoreID.h $
//  
//  Owner: kvanwiel
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

#ifndef __InCopyCoreID__
#define __InCopyCoreID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kJDefaultMargin		(20.0 * 72.0 / 25.4)*2
#define kRDefaultMargin		36*2

#define kInCopyCorePrefix	 RezLong(0xab00)	// reserved in AdobePrefix.h

//PlugInID
#define kInCopyCorePlugInName				"InCopyCore"
DECLARE_PMID(kPlugInIDSpace, kInCopyCorePlugInID, kInCopyCorePrefix + 1)

// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kInCopyCoreNewDocResponderBoss,		kInCopyCorePrefix + 12)
DECLARE_PMID(kClassIDSpace, kWidgetBarWindowBoss_Obsolete,		kInCopyCorePrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace, kInCopyCoreOpenDocResponderBoss,	kInCopyCorePrefix + 15)
DECLARE_PMID(kClassIDSpace, kTransposeCmdBoss,					kInCopyCorePrefix + 16)
DECLARE_PMID(kClassIDSpace, kTransposeHelperCmdBoss,			kInCopyCorePrefix + 17)
//gap
DECLARE_PMID(kClassIDSpace, kResetTextIndexForUndoCmdBoss,		kInCopyCorePrefix + 19)
//gap
DECLARE_PMID(kClassIDSpace, kInCopyCoreConversionProviderBoss,	kInCopyCorePrefix + 21)
//DECLARE_PMID(kClassIDSpace, kRemoveInCopyStoryCmdBoss,			kInCopyCorePrefix + 22) //Duplicate; causes compiler error (dresnick; integration from Dragontail into main)
//DECLARE_PMID(kClassIDSpace, kInCopyAutoFlowCmdBoss,				kInCopyCorePrefix + 23) //Duplicate; causes compiler error (dresnick; integration from Dragontail into main)

// moved from InCopyFilter
DECLARE_PMID(kClassIDSpace, kSetStandAloneCmdBoss,				kInCopyCorePrefix + 24)
//gap
DECLARE_PMID(kClassIDSpace, kInCopyAutoFlowCmdBoss,				kInCopyCorePrefix + 27)
DECLARE_PMID(kClassIDSpace, kRemoveInCopyStoryCmdBoss,			kInCopyCorePrefix + 28) // You don't need to call these commands directly, Use IInCopyStoryList::ProcessAddStory and ProcessRemoveStory instead
DECLARE_PMID(kClassIDSpace, kAddInCopyStoryCmdBoss,				kInCopyCorePrefix + 29) // Use IInCopyStoryList::ProcessAddStory and IInCopyStoryList::ProcessRemoveStory instead

// print/pdf export
DECLARE_PMID(kClassIDSpace, kInCopyLayoutPrintDataBoss, kInCopyCorePrefix + 30)
DECLARE_PMID(kClassIDSpace, kInCopyGalleyPrintDataBoss, kInCopyCorePrefix + 31)
DECLARE_PMID(kClassIDSpace, kSaveInCopyPrintDataCmdBoss, kInCopyCorePrefix + 32)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptLayoutDataBoss, kInCopyCorePrefix + 33)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptGalleyDataBoss, kInCopyCorePrefix + 34)
DECLARE_PMID(kClassIDSpace, kSaveInCopyPDFExptGalleyDataCmdBoss, kInCopyCorePrefix + 35)
DECLARE_PMID(kClassIDSpace, kSaveInCopyPDFExptLayoutDataCmdBoss, kInCopyCorePrefix + 36)

// doc preset
DECLARE_PMID(kClassIDSpace, kSaveDocumentPresetDataCmdBoss, kInCopyCorePrefix + 50)
DECLARE_PMID(kClassIDSpace, kDocPresetDefaultBoss,		kInCopyCorePrefix + 51)
DECLARE_PMID(kClassIDSpace, kDocPresetBoss,				kInCopyCorePrefix + 52)
DECLARE_PMID(kClassIDSpace, kDocEditPresetCmdBoss,		kInCopyCorePrefix + 53)
DECLARE_PMID(kClassIDSpace, kDocSetPresetNameCmdBoss,	kInCopyCorePrefix + 54)
DECLARE_PMID(kClassIDSpace, kDocAddPresetCmdBoss,		kInCopyCorePrefix + 55)
DECLARE_PMID(kClassIDSpace, kDocDeletePresetCmdBoss,	kInCopyCorePrefix + 56)
DECLARE_PMID(kClassIDSpace, kSetTextAreaPrefsCmdBoss,	kInCopyCorePrefix + 58)
DECLARE_PMID(kClassIDSpace, kDocPresetNewWSResponderBoss, kInCopyCorePrefix + 59)
DECLARE_PMID(kClassIDSpace, kDocPresetExportRootBoss,	kInCopyCorePrefix + 60)
DECLARE_PMID(kClassIDSpace, kDocPresetPhase2ConversionResponderBoss, kInCopyCorePrefix + 61)
DECLARE_PMID(kClassIDSpace, kICDocPrefsScriptProvider40Boss, kInCopyCorePrefix +62)
DECLARE_PMID(kClassIDSpace, kICDocPresetScriptProviderBoss, kInCopyCorePrefix + 63)
DECLARE_PMID(kClassIDSpace, kICDocStandAlonePrefScriptProviderBoss, kInCopyCorePrefix + 64)
DECLARE_PMID(kClassIDSpace, kSetGridAttributesPrefsCmdBoss,	kInCopyCorePrefix + 65)
DECLARE_PMID(kClassIDSpace, kSetInCopyNewDocFlagCmdBoss,	kInCopyCorePrefix + 66)
DECLARE_PMID(kClassIDSpace, kInCopyResetColumnCmdBoss,	kInCopyCorePrefix + 67)
DECLARE_PMID(kClassIDSpace, kInCopySetTextFramePrivateCmdBoss,	kInCopyCorePrefix + 68)
DECLARE_PMID(kClassIDSpace, kInCopyCoreAfterNewDocResponderBoss,	kInCopyCorePrefix + 69)

// From GalleyInfo
DECLARE_PMID(kClassIDSpace, kGIStoryPropScriptProviderBoss,		kInCopyCorePrefix + 70)
DECLARE_PMID(kClassIDSpace, kGalleyInfoErrorStringServiceBoss,	kInCopyCorePrefix + 71)


//WidgetIDs

DECLARE_PMID(kWidgetIDSpace, kWritingStatePanelID, 			kInCopyCorePrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kLayoutStatsWidgetBarID, 		kInCopyCorePrefix + 44)

DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelLineData, 		kInCopyCorePrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelWordData, 		kInCopyCorePrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelCharData, 		kInCopyCorePrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelOverfitGraph,	kInCopyCorePrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsGenericWidget1WidgetID,	kInCopyCorePrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsGenericWidget2WidgetID,	kInCopyCorePrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsGenericWidget3WidgetID,	kInCopyCorePrefix + 51)

// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYAPP,						kInCopyCorePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYCOREDOCOBSERVER,			kInCopyCorePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYWORKGROUPHELPER,			kInCopyCorePrefix + 7)
// gap 8
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETBARMGR_OBSOLETE,				kInCopyCorePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYCOREDOCTITLEOBSERVER,		kInCopyCorePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYCOREOVERFLOWHANDLER,			kInCopyCorePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYSTORYLIST,					kInCopyCorePrefix + 13)

// moved from InCopyFilter
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDALONEDOC,						kInCopyCorePrefix + 14)
//OBSOLETE: DECLARE_PMID(kInterfaceIDSpace, IID_ISETFONTDISPLAYSIZE,				kInCopyCorePrefix + 15)

DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONCONTEXTCHECKER,				kInCopyCorePrefix + 16)

//print/pdf export
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYLAYOUTPRINTDATA, kInCopyCorePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYGALLEYPRINTDATA, kInCopyCorePrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPDFEXPTGALLEYDATA, kInCopyCorePrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPDFEXPTLAYOUTDATA, kInCopyCorePrefix + 20)


//gap

//Doc preset
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTAREAPREFERENCES, kInCopyCorePrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCPRESETLISTMGR, kInCopyCorePrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCPRESETNAME, kInCopyCorePrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTAREAPREFSDATA, kInCopyCorePrefix + 26)
DECLARE_PMID(kInterfaceIDSpace,  IID_IDOCUMENTSETUPUTILS,kInCopyCorePrefix + 27)

DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYFILEACTIONSSUITE, kInCopyCorePrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRIDATTRIBUTESPREFERENCES, kInCopyCorePrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRIDATTRIBUTESPREFSDATA, kInCopyCorePrefix + 30)
DECLARE_PMID(kInterfaceIDSpace,  IID_IDOCUMENTSETUPPRIVATEUTILS,kInCopyCorePrefix + 31)

DECLARE_PMID(kInterfaceIDSpace,  IID_IINCOPYNONPRIVATETEXTFRAME,kInCopyCorePrefix + 32)

DECLARE_PMID(kInterfaceIDSpace,  IID_IGRIDPREFSCHANGE,			kInCopyCorePrefix + 33)
DECLARE_PMID(kInterfaceIDSpace,  IID_IGRIDPREFSDIRECTIONCHANGE,	kInCopyCorePrefix + 34)
DECLARE_PMID(kInterfaceIDSpace,  IID_IGRIDPREFSFRAMETYPECHANGE,	kInCopyCorePrefix + 35)
DECLARE_PMID(kInterfaceIDSpace,  IID_IGRIDPREFSCHARPERLINECHANGE,kInCopyCorePrefix + 36)
DECLARE_PMID(kInterfaceIDSpace,  IID_IMISSINGFONTDISPLAYED,kInCopyCorePrefix + 37)
DECLARE_PMID(kInterfaceIDSpace,  IID_ISUPPRESSMISSINGLINKS,kInCopyCorePrefix + 38)

DECLARE_PMID(kInterfaceIDSpace, IID_INEWDOC,					kInCopyCorePrefix + 39)

DECLARE_PMID(kInterfaceIDSpace, IID_IRESTORESELECTIONTASK,		kInCopyCorePrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESTORESELECTIONTASKDATA,		kInCopyCorePrefix + 41)

// From GalleyInfo
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYFITDATA, 			kInCopyCorePrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IWORDCOUNTOPTIONS, 		kInCopyCorePrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYINFOUTILS, 		kInCopyCorePrefix + 44)

DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSAVE,		kInCopyCorePrefix + 45)


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kInCopyAppImpl,					kInCopyCorePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kInCopyWorkgroupHelperImpl,		kInCopyCorePrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreNewDocResponderImpl,	kInCopyCorePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreDocObserverImpl,		kInCopyCorePrefix + 14)
// gap
DECLARE_PMID(kImplementationIDSpace, kWidgetBarWindowImpl_Obsolete,		kInCopyCorePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kWidgetBarMgrImpl_Obsolete,		kInCopyCorePrefix + 18)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreOpenDocResponderImpl,	kInCopyCorePrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreDocTitleObserverImpl,	kInCopyCorePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreOverflowHandlerImpl,	kInCopyCorePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTransposeCmdImpl,					kInCopyCorePrefix + 23)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyStoryListImpl,				kInCopyCorePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kRemoveInCopyStoryCmdImpl,			kInCopyCorePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kInCopyAutoFlowCmdImpl,				kInCopyCorePrefix + 28)

// moved from InCopyFilter
DECLARE_PMID(kImplementationIDSpace, kStandAloneDocImpl,				kInCopyCorePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSetStandAloneCmdImpl,				kInCopyCorePrefix + 30)
//gap
DECLARE_PMID(kImplementationIDSpace, kAddInCopyStoryCmdImpl,			kInCopyCorePrefix + 32)

// print/pdf export
DECLARE_PMID(kImplementationIDSpace, kInCopyLayoutPrintDataImpl,		kInCopyCorePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kInCopyGalleyPrintDataImpl,		kInCopyCorePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSaveInCopyPrintDataCmdImpl, kInCopyCorePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptLayoutDataImpl, kInCopyCorePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptGalleyDataImpl, kInCopyCorePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSaveInCopyPDFExptGalleyDataCmdImpl, kInCopyCorePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSaveInCopyPDFExptLayoutDataCmdImpl, kInCopyCorePrefix + 39)

//gap

DECLARE_PMID(kImplementationIDSpace, kTransposeHelperCmdImpl,				kInCopyCorePrefix + 43)

//doc preset
DECLARE_PMID(kImplementationIDSpace, kSaveDocumentPresetDataCmdImpl,		kInCopyCorePrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSessionTextAreaPrefsImpl,				kInCopyCorePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDocEditPresetCmdImpl,					kInCopyCorePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDocSetPresetNameCmdImpl,				kInCopyCorePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDocAddPresetCmdImpl,					kInCopyCorePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kDocDeletePresetCmdImpl,				kInCopyCorePrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kDocPresetListMgrImpl,				kInCopyCorePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kDocPresetNamePersistImpl,			kInCopyCorePrefix + 52)
//gap
DECLARE_PMID(kImplementationIDSpace, kFwdTextAreaPrefsImpl,				kInCopyCorePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSetTextAreaPrefsCmdImpl,				kInCopyCorePrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kTextAreaPrefsDataImpl,				kInCopyCorePrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kDocTextAreaPrefsImpl,					kInCopyCorePrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kDocPresetNewWSResponderImpl,			kInCopyCorePrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kDocPresetPhase2ConversionImpl,		kInCopyCorePrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kICDocPrefsScriptProvider40Impl,		kInCopyCorePrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kICDocPresetScriptProviderImpl,		kInCopyCorePrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kICDocStandAlonePrefScriptProviderImpl,kInCopyCorePrefix + 65)
//gap
DECLARE_PMID(kImplementationIDSpace,  kDocumentSetupUtilsImpl,				kInCopyCorePrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kInCopyFileActionsSuiteASBImpl,		kInCopyCorePrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kInCopyFileActionsTextCSBImpl,			kInCopyCorePrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kInCopyFileActionsLayoutCSBImpl,		kInCopyCorePrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kInCopyFileActionsDefaultCSBImpl,		kInCopyCorePrefix + 71)

DECLARE_PMID(kImplementationIDSpace, kSessionGridAttributesPrefsImpl,		kInCopyCorePrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kFwdGridAttributesPrefsImpl,			kInCopyCorePrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kDocGridAttributesPrefsImpl,			kInCopyCorePrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kSetGridAttributesPrefsCmdImpl,		kInCopyCorePrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kGridAttributesPrefsDataImpl,			kInCopyCorePrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kDocumentSetupPrivateUtilsImpl,		kInCopyCorePrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kInCopyNonPrivateTextFrameImpl,		kInCopyCorePrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kMissingFontDisplayedImpl,				kInCopyCorePrefix + 79)

DECLARE_PMID(kImplementationIDSpace, kSetInCopyNewDocFlagCmdImpl,			kInCopyCorePrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kInCopyResetColumnCmdImpl,		kInCopyCorePrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kInCopySetTextFramePrivateCmdImpl,		kInCopyCorePrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kRestoreSelectionTaskImpl,			kInCopyCorePrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kRestoreSelectionTaskDataImpl,		kInCopyCorePrefix + 84)

// from GalleyInfo
DECLARE_PMID(kImplementationIDSpace, kStoryFitDataImpl,					kInCopyCorePrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kWordCountOptionDataImpl,			kInCopyCorePrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kGIStoryPropScriptProviderImpl,	kInCopyCorePrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoUtilsImpl,				kInCopyCorePrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoErrorStringServiceImpl, kInCopyCorePrefix + 91)


// moved from InCopyFilter
DECLARE_PMID(kMessageIDSpace, kSetFontDisplaySizeMsg,				kInCopyCorePrefix + 1)
DECLARE_PMID(kMessageIDSpace, kHideChangesMsg,						kInCopyCorePrefix + 2)
DECLARE_PMID(kMessageIDSpace, kShowChangesMsg,						kInCopyCorePrefix + 3)

//InvalHandlers
DECLARE_PMID(kInvalHandlerIDSpace, kEmptySelectionHandlerID, 					kInCopyCorePrefix + 1)


//
//Script Element IDs
//
//Objects
DECLARE_PMID(kScriptInfoIDSpace, kICDocStandAlonePrefObjectScriptElement,		kInCopyCorePrefix + 20)


//---------------------------------------------------------------
//	Service IDs
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kOversetFrameService, 				kInCopyCorePrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kTextAreaWidthPropertyScriptElement,			kInCopyCorePrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kTextAreaDepthPropertyScriptElement,			kInCopyCorePrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kTextAreaDepthUnitPropertyScriptElement,		kInCopyCorePrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kICDocStandAlonePrefPropertyScriptElement,		kInCopyCorePrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kDPGridCharAkiPropertyScriptElement,			kInCopyCorePrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kDPGridLineAkiPropertyScriptElement,			kInCopyCorePrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kDPCharPerLinePropertyScriptElement,			kInCopyCorePrefix + 106)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kTextAreaDepthUnitEnumScriptElement,			kInCopyCorePrefix + 200)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kICDocStandAloneINXPolicies40MetadataScriptElement,kInCopyCorePrefix + 240)

//----------------------------------------------------------------------------------------
// Error identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kErrorIDSpace,				kInvalidFitStoryID, 	kInCopyCorePrefix + 1)

//GUIDs
// {DF166B59-B461-4439-8182-F52CECC23AC4}
#define kICDocStandAlonePref_CLSID { 0xdf166b59, 0xb461, 0x4439, { 0x81, 0x82, 0xf5, 0x2c, 0xec, 0xc2, 0x3a, 0xc4 } }

#endif	// __InCopyCoreID__
