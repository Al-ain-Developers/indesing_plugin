//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/BookID.h $
//  
//  Owner: Yeming Liu
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
//  Comments: Contains IDs used by the book architecture.
//  
//========================================================================================

#ifndef __BOOKID__
#define __BOOKID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kBookPrefix	 				RezLong(0x10000)

// PluginID
#define kBookPluginName 				"Book"
DECLARE_PMID(kPlugInIDSpace, kBookPluginID, kBookPrefix + 1)

// Conversion
// For pub conversion constants see BookConversionID.h

// <Start IDC>
// <Class ID>
DECLARE_PMID(kClassIDSpace, kBookBoss, kBookPrefix + 1)
DECLARE_PMID(kClassIDSpace, kBookContentBoss, kBookPrefix + 2)
DECLARE_PMID(kClassIDSpace, kBookScriptObserverBoss, kBookPrefix + 3)
DECLARE_PMID(kClassIDSpace, kNewBookCmdBoss, kBookPrefix + 4)
DECLARE_PMID(kClassIDSpace, kOpenBookCmdBoss, kBookPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSaveBookCmdBoss, kBookPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSaveAsBookCmdBoss, kBookPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCloseBookCmdBoss, kBookPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAddDocToBookCmdBoss, kBookPrefix + 9)
DECLARE_PMID(kClassIDSpace, kRemoveDocFromBookCmdBoss, kBookPrefix + 10)
DECLARE_PMID(kClassIDSpace, kMoveDocInBookCmdBoss, kBookPrefix + 11)
DECLARE_PMID(kClassIDSpace, kConstructContentCmdBoss, kBookPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetRepaginationCmdBoss, kBookPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSetBookMasterDocCmdBoss, kBookPrefix + 14)
DECLARE_PMID(kClassIDSpace, kReplaceBookContentCmdBoss, kBookPrefix + 15)
DECLARE_PMID(kClassIDSpace, kBookOpenDocResponderBoss, kBookPrefix + 16)
DECLARE_PMID(kClassIDSpace, kBookNewDocResponderBoss, kBookPrefix + 17)
DECLARE_PMID(kClassIDSpace, kBookSyncCmdBoss, kBookPrefix + 18)
DECLARE_PMID(kClassIDSpace, kOpenDocFromBookCmdBoss, kBookPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSetCurrentActiveBookCmdBoss, kBookPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSetPaginateOptionsCmdBoss, kBookPrefix + 21)
DECLARE_PMID(kClassIDSpace, kBookScriptProviderBoss, kBookPrefix + 22)
DECLARE_PMID(kClassIDSpace, kBookContentScriptProviderBoss, kBookPrefix + 23)
DECLARE_PMID(kClassIDSpace, kRecoverBookCmdBoss, kBookPrefix + 24)
DECLARE_PMID(kClassIDSpace, kBookConversionProviderBoss, kBookPrefix + 25)
DECLARE_PMID(kClassIDSpace, kBookPrintActionCmdBoss, kBookPrefix + 26)
DECLARE_PMID(kClassIDSpace, kBookExportActionCmdBoss, kBookPrefix + 27)
DECLARE_PMID(kClassIDSpace, kBookSavePrintDataCmdBoss, kBookPrefix + 28)
DECLARE_PMID(kClassIDSpace, kSetRepageFlagCmdBoss, kBookPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSaveACopyBookCmdBoss, kBookPrefix + 30)
DECLARE_PMID(kClassIDSpace, kRecomposeWrapCmdBoss, kBookPrefix + 31)
DECLARE_PMID(kClassIDSpace, kBookSyncOptionScriptProvider60Boss, kBookPrefix + 32)
DECLARE_PMID(kClassIDSpace, kBookSyncOptionScriptProviderBoss, kBookPrefix + 33)
DECLARE_PMID(kClassIDSpace, kBookSyncOptionScriptObjectBoss, kBookPrefix + 34)
//	DECLARE_PMID(kClassIDSpace, kNewBookPanelCmdBoss, kBookPrefix + 35)	-- moved to BookPanel
DECLARE_PMID(kClassIDSpace, kBookTempInkListBoss, kBookPrefix + 36)
DECLARE_PMID(kClassIDSpace, kBookOpenServiceBoss, kBookPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSetBookContentPageRangeCmdBoss, kBookPrefix + 38)
DECLARE_PMID(kClassIDSpace, kBookPrintPageInitializerBoss, kBookPrefix + 39)
DECLARE_PMID(kClassIDSpace, kBookInkListPhase2ConversionBoss, kBookPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSetAutoConvertContentCmdBoss, kBookPrefix + 41)
DECLARE_PMID(kClassIDSpace, kBookErrorStringServiceBoss, kBookPrefix + 42)
DECLARE_PMID(kClassIDSpace, kSetMergeLayersFlagCmdBoss, kBookPrefix + 43)
DECLARE_PMID(kClassIDSpace, kSetStyleMatchingStrategyOnBookSyncPrefCmdBoss, kBookPrefix + 44)
DECLARE_PMID(kClassIDSpace, kBookPhase2ConversionBoss, kBookPrefix + 45)
DECLARE_PMID(kClassIDSpace, kBookContentNewLinkConverterBoss, kBookPrefix + 46)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKMANAGER, kBookPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOK, kBookPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKPAGINATEOPTIONS, kBookPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKCONTENTMGR, kBookPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKCONTENT, kBookPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKDATALINKLIST, kBookPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKCMDDATA, kBookPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKCONTENTCMDDATA, kBookPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEINFODATA, kBookPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMASTERDOCCMDDATA, kBookPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKSYNCOPTIONS, kBookPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCMDDATA, kBookPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACEBOOKCONTENT, kBookPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKDOCOBSERVER, kBookPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKSYNCCMDDATA, kBookPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSEBOOKUIFLAG, kBookPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKDOCOBSERVERSWITCHER, kBookPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKOUTPUTACTIONCMDDATA, kBookPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKPRINTDATA, kBookPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKEXPORT, kBookPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IALLOWCANCELCLOSEBOOKDATA, kBookPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKUTILS, kBookPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IISTRIGGEREDBYBOOKDOCOBSERVER, kBookPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPECIALHANDLINGBOOKASMODIFIED, kBookPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKUIUTILS, kBookPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKSYNCUISETTING, kBookPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOKSCRIPTUTILS, kBookPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETREPAGINATIONCMDOPTIONS, kBookPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTSAVEASMESSAGE, kBookPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace,  IID_ISTYLEMATCHINGSTRATEGY, kBookPrefix + 30)
// This is really a faux IID. It's used to provide a subject/observer link that communicates
// the command used for the model change (the existing subjects pass UIDRefs of the book
// and we don't want to change that for fear of impacting other developers).
DECLARE_PMID(kInterfaceIDSpace,  IID_IBOOKCONTENTCHANGE, kBookPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace,  IID_IFORCENOTSAVEWHENCLOSE, kBookPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace,  IID_IBOOKEXPORTINGBOOKTOPDF, kBookPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace,  IID_IBOOKCOMPOSITEFONTCONFLICTONEXPORT, kBookPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace,	 IID_IALLOWCANCELSAVEBOOKDATA, kBookPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace,	 IID_IALLOWCANCELSAVEASBOOKDATA, kBookPrefix + 36)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kBookManagerImpl, kBookPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBookImpl, kBookPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kBookPaginateOptionsImpl, kBookPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBookContentMgrImpl, kBookPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kBookContentImpl, kBookPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kBookDataLinkListImpl, kBookPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewBookCmdImpl, kBookPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kBookCmdDataImpl, kBookPrefix + 8	)
DECLARE_PMID(kImplementationIDSpace, kOpenBookCmdImpl, kBookPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSaveBookCmdImpl, kBookPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSaveAsBookCmdImpl, kBookPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCloseBookCmdImpl, kBookPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kAddDocToBookCmdImpl, kBookPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kBookContentCmdDataImpl, kBookPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kRemoveDocFromBookCmdImpl, kBookPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kMoveDocInBookCmdImpl, kBookPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kConstructContentCmdImpl, kBookPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSetRepaginationCmdImpl, kBookPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPageInfoDataImpl, kBookPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSetBookMasterDocCmdImpl, kBookPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSetMasterDocCmdDataImpl, kBookPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kReplaceBookContentCmdImpl, kBookPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kBookOpenDocResponderImpl, kBookPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kBookNewDocResponderImpl, kBookPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kBookDocObserverImpl, kBookPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kBookSyncCmdImpl, kBookPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kOpenDocFromBookCmdImpl, kBookPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kBookDocObserverSwitcherImpl, kBookPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSetCurrentActiveBookCmdImpl, kBookPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSetPaginateOptionsCmdImpl, kBookPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kBookSyncOptionsImpl, kBookPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPersistBookSyncOptionsImpl, kBookPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kBookSyncCmdDataImpl, kBookPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kBookScriptImpl, kBookPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetAutoConvertContentCmdImpl, kBookPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kBookContentScriptImpl, kBookPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kBookScriptUtilsImpl, kBookPrefix + 37) 
DECLARE_PMID(kImplementationIDSpace, kBookScriptProviderImpl, kBookPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kBookContentScriptProviderImpl, kBookPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kBookScriptObserverImpl, kBookPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kRecoverBookCmdImpl, kBookPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kBookPrintActionCmdImpl, kBookPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kBookOutputActionCmdDataImpl, kBookPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kBookExportActionCmdImpl, kBookPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kBookSavePrintDataCmdImpl, kBookPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kBookPrintDataImpl, kBookPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kExportBookServiceImpl, kBookPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSetRepageFlagCmdImpl, kBookPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSaveACopyBookCmdImpl, kBookPrefix + 49) 
DECLARE_PMID(kImplementationIDSpace, kAllowCancelCloseBookDataImpl, kBookPrefix + 50) 
DECLARE_PMID(kImplementationIDSpace, kBookUtilsImpl, kBookPrefix + 51) 
DECLARE_PMID(kImplementationIDSpace, kRecomposeWrapCmdImpl, kBookPrefix + 52) 
DECLARE_PMID(kImplementationIDSpace, kSetMergeLayersFlagCmdImpl, kBookPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kBookSyncOptionScriptProvider60Impl, kBookPrefix + 54)
// gap
DECLARE_PMID(kImplementationIDSpace, kBookSyncOptionScriptProviderImpl, kBookPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kBookSyncUISettingImpl, kBookPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kBookErrorStringServiceImpl, kBookPrefix + 58)
//	DECLARE_PMID(kImplementationIDSpace, kNewBookPanelCmdImpl, kBookPrefix + 59) -- moved to bookpanel
DECLARE_PMID(kImplementationIDSpace, kBookOpenFilterImpl, kBookPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kBookUIUtilsImpl, kBookPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kSetBookContentPageRangeCmdImpl, kBookPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kBookPrintPageInitializerImpl, kBookPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kBookInkListPhase2ConverterImpl, kBookPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kSetRepaginationCmdOptionsImpl, kBookPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kStyleMatchingStrategyImpl, kBookPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kSetStyleMatchingStrategyOnBookSyncPrefCmdImpl, kBookPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kBookLinkObjectImpl, kBookPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kBookPhase2ConversionImpl, kBookPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kBookContentNewLinkConverterImpl, kBookPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kBookExportingBookToPDFImpl, kBookPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kBookCompositeFontConflictOnExportImpl, kBookPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kAllowCancelSaveBookDataImpl, kBookPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kAllowCancelSaveAsBookDataImpl, kBookPrefix + 75)

// <Message ID>
DECLARE_PMID(kMessageIDSpace, IID_INEWBOOKMSG, kBookPrefix + 1)
DECLARE_PMID(kMessageIDSpace, IID_IOPENBOOKMSG, kBookPrefix + 2)
DECLARE_PMID(kMessageIDSpace, IID_ISAVEBOOKMSG, kBookPrefix + 3)
DECLARE_PMID(kMessageIDSpace, IID_ISAVEASBOOKMSG, kBookPrefix + 4)
DECLARE_PMID(kMessageIDSpace, IID_ICLOSEBOOKMSG, kBookPrefix + 5)
DECLARE_PMID(kMessageIDSpace, IID_ISETCURRENTACTIVEBOOKMSG, kBookPrefix + 6)

// <Error ID>
//gap
DECLARE_PMID(kErrorIDSpace, kSaveBookFailure, kBookPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kSaveAsBookFailure, kBookPrefix + 5)
//gap
DECLARE_PMID(kErrorIDSpace, kOpenBookFailure, kBookPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kNewBookCmdFailure, kBookPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kOpenBookCmdFailure, kBookPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kSaveBookCmdFailure, kBookPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kSaveAsBookCmdFailure, kBookPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kCloseBookCmdFailure, kBookPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kAddDocToBookCmdFailure, kBookPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kRemoveDocFromBookCmdFailure, kBookPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kReorderDocInBookCmdFailure, kBookPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kSaveACopyBookFailure, kBookPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kSaveACopyBookCmdFailure, kBookPrefix + 17)

// anirudh, fix for bug# 1206196.
// added 1 error message customised for scripting support for book export.
DECLARE_PMID(kErrorIDSpace, kInvalidScriptExportDocsFailure, kBookPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kInvalidScriptExportFormatFailure, kBookPrefix + 19)

DECLARE_PMID(kErrorIDSpace, kNoBookOpenError, kBookPrefix + 20)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kExportBookService, kBookPrefix + 1)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kSyncCompleteAlertWidgetID, kBookPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kMissingFontDocInBookRepageWidgetID, kBookPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kOpenBookFileConvertContentAlertWidgetID, kBookPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kBookedDocumentWithMissingPluginWidgetID, kBookPrefix + 4)

//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________
DECLARE_PMID(kViewPortAttrIDSpace, kOutputtingBookVPAttr, kBookPrefix + 1)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kBookSuiteScriptElement,					kBookPrefix + 0)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kBookObjectScriptElement,					kBookPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kBookContentObjectScriptElement,			kBookPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kSynchronizeOptionObjectScriptElement,		kBookPrefix + 42)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateBookMethodScriptElement,				kBookPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateXRefMethodScriptElement,				kBookPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kSaveBookMethodScriptElement,				kBookPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kExportBookToPDFMethodScriptElement,		kBookPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kSynchronizeMethodScriptElement,			kBookPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kCreateBookContentMethodScriptElement,		kBookPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kMoveBookContentMethodScriptElement,		kBookPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kReplaceBookContentMethodScriptElement,		kBookPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kSynchronizeBookContentMethodScriptElement,	kBookPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kRepaginationMethodScriptElement,			kBookPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateNumberingInBookMethodScriptElement,	kBookPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateAllNumberingInBookMethodScriptElement,	kBookPrefix + 91)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kMasterDocPropertyScriptElement,			kBookPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kRepaginationOptionPropertyScriptElement,	kBookPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kInsertBlankPagePropertyScriptElement,		kBookPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kAutomaticPaginationPropertyScriptElement,	kBookPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kGroupNamePropertyScriptElement,			kBookPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kUseStylePropertyScriptElement,			kBookPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kBookStatusPropertyScriptElement,			kBookPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kSizePropertyScriptElement,				kBookPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kPageRangePropertyScriptElement,			kBookPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kAutomaticConversionPropertyScriptElement,	kBookPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kMergeLayersPropertyScriptElement,			kBookPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kActiveBookPropertyScriptElement,			kBookPrefix + 171)

DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleSyncPropertyScriptElement,		kBookPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kTextVariableSyncPropertyScriptElement,	kBookPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleSyncPropertyScriptElement,		kBookPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kParaStyleSyncPropertyScriptElement,		kBookPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kCharStyleSyncPropertyScriptElement,		kBookPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kTrapStyleSyncPropertyScriptElement,		kBookPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kMasterPageSyncPropertyScriptElement,		kBookPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleSyncPropertyScriptElement,		kBookPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kSwatchSyncPropertyScriptElement,			kBookPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kCellStyleSyncPropertyScriptElement,		kBookPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kBNListSyncPropertyScriptElement,			kBookPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiStyleSyncPropertyScriptElement,	kBookPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kCompositionFontSyncPropertyScriptElement,	kBookPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuStyleSyncPropertyScriptElement,	kBookPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kNamedGridSyncPropertyScriptElement,		kBookPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kStyleMatchingStrategyPropertyScriptElement, kBookPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kConditionalTextSyncPropertyScriptElement,	kBookPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kXReferenceFormatPropertyScriptElement,    kBookPrefix + 189)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kRepaginateOptionEnumScriptElement,		kBookPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kBookContentStatusEnumScriptElement,		kBookPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kStyleMatchingStrategyEnumScriptElement,	kBookPrefix + 222)

#endif //__BOOKID__
