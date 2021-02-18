//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/TOCID.h $
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
//========================================================================================

#ifndef __TOCID__
#define __TOCID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTOCPrefix	 					RezLong(0x11600)

// PluginID
#define kTOCPluginName 					"TOC"
DECLARE_PMID(kPlugInIDSpace, kTOCPluginID, kTOCPrefix + 1)

// <Class ID>
//gap
DECLARE_PMID(kClassIDSpace, kCreateTOCCmdBoss,		kTOCPrefix + 3)
DECLARE_PMID(kClassIDSpace, kFormatTOCCmdBoss,		kTOCPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTOCStyleBoss,			kTOCPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCreateTOCStyleCmdBoss, kTOCPrefix + 6)
DECLARE_PMID(kClassIDSpace, kEditTOCStyleCmdBoss,	kTOCPrefix + 7)
DECLARE_PMID(kClassIDSpace, kDeleteTOCStyleCmdBoss,	kTOCPrefix + 8)
DECLARE_PMID(kClassIDSpace, kLoadTOCStyleCmdBoss,	kTOCPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSetDefaultTOCStyleCmdBoss,			kTOCPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTOCDataLinkRegistryBoss,			kTOCPrefix + 11)
DECLARE_PMID(kClassIDSpace, kAttachTOCDataLinkCmdBoss,			kTOCPrefix + 12)
DECLARE_PMID(kClassIDSpace, kRemoveTOCDataLinkCmdBoss,			kTOCPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCopyOneTOCStyleCmdBoss,			kTOCPrefix + 14)
DECLARE_PMID(kClassIDSpace, kTOCOpenDocResponderBoss,			kTOCPrefix + 15)
DECLARE_PMID(kClassIDSpace, kGetUniqueStyleNamesOfBookCmdBoss,	kTOCPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTOCDataLinkHelperBoss,				kTOCPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTOCStyleSyncBoss,					kTOCPrefix + 18)	
DECLARE_PMID(kClassIDSpace, kModifyTOCFormatInfoCmdBoss,		kTOCPrefix + 19)
DECLARE_PMID(kClassIDSpace, kTOCNewDocResponderBoss,			kTOCPrefix + 20)
DECLARE_PMID(kClassIDSpace, kTOCStyleScriptProviderBoss,		kTOCPrefix + 21)
DECLARE_PMID(kClassIDSpace, kGenerateTOCByDefaultCmdBoss,		kTOCPrefix + 22)
DECLARE_PMID(kClassIDSpace, kTOCStyleEntryScriptProviderBoss,	kTOCPrefix + 23)
DECLARE_PMID(kClassIDSpace, kTOCStyleEntryScriptObjectBoss,		kTOCPrefix + 24)
DECLARE_PMID(kClassIDSpace, kTOCNewWSResponderBoss,				kTOCPrefix + 25)
DECLARE_PMID(kClassIDSpace, kTOCPhase2ConversionBoss,			kTOCPrefix + 26)
DECLARE_PMID(kClassIDSpace, kGenerateTOCScriptProviderBoss,		kTOCPrefix + 27)
DECLARE_PMID(kClassIDSpace, kTOCConversionProviderBoss,			kTOCPrefix + 28)
DECLARE_PMID(kClassIDSpace, kTOCErrorStringServiceBoss,			kTOCPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTOCRIDXNotifierHandlerBoss,		kTOCPrefix + 30)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCCMDDATA,		kTOCPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTYLEINFO,		kTOCPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTYLENAMETABLE, kTOCPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTYLENAME,		kTOCPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATALINKUIDDATA,	kTOCPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYUIDDATA,		kTOCPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTYLEUIDDATA,	kTOCPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCDATALINKHELPER, kTOCPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGETUNIQUESTYLENAMESCMDDATA, kTOCPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEINFOMAPDATA,	kTOCPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCOBSERVER,		kTOCPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETUIDDATA,		kTOCPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IMODIFYTOCFORMATINFOCMDDATA, kTOCPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTRIPCHARSERVICE, kTOCPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTYLEPERSISTUIDDATA, kTOCPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYPERSISTUIDDATA, kTOCPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITOCCLOSEDDOCUIDLIST, kTOCPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCSTORYSUITE, kTOCPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITOCUNDOSTATE, kTOCPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCUTILS,		kTOCPrefix + 20)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kTOCStripCharService, kTOCPrefix + 1)

// <Implementation ID>
// gap
DECLARE_PMID(kImplementationIDSpace, kCreateTOCCmdImpl, kTOCPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kFormatTOCCmdImpl,	kTOCPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTOCCmdDataImpl,	kTOCPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleInfoImpl, kTOCPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleNameTableImpl, kTOCPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCreateTOCStyleCmdImpl, kTOCPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kEditTOCStyleCmdImpl,	 kTOCPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDeleteTOCStyleCmdImpl, kTOCPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLoadTOCStyleCmdImpl,	 kTOCPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTOCDataLinkProviderImpl,	kTOCPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTOCDataLinkServiceImpl,	kTOCPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetDefaultTOCStyleCmdImpl,kTOCPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAttachTOCDataLinkCmdImpl,	kTOCPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kRemoveTOCDataLinkCmdImpl,	kTOCPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDataLinkUIDDataImpl,		kTOCPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kStoryUIDDataImpl,			kTOCPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCopyOneTOCStyleCmdImpl,	kTOCPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTOCStylePersistUIDDataImpl, kTOCPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kStyleInfoMapDataImpl,		kTOCPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleUIDDataImpl,		kTOCPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kTOCDataLinkHelperImpl,	kTOCPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kStoryPersistUIDRefDataImpl, kTOCPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleSyncServiceImpl,	kTOCPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kGetUniqueStyleOfBookCmdImpl, kTOCPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGetUniqueStyleNamesCmdDataImpl, kTOCPrefix + 26)
//gap
DECLARE_PMID(kImplementationIDSpace, kModifyTOCFormatInfoCmdImpl, kTOCPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kTargetUIDDataImpl,		kTOCPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kTOCNewDocResponderImpl,	kTOCPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kTOCFormatEntryStyleNameImpl, kTOCPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleScriptImpl,		kTOCPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTOCErrorStringServiceImpl, kTOCPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleScriptProviderImpl, kTOCPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kGenerateTOCByDefaultCmdImpl, kTOCPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleEntryScriptProviderImpl, kTOCPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kTOCUtilsImpl,					kTOCPrefix + 37)				  
DECLARE_PMID(kImplementationIDSpace, kTOCRIDXNotifierHandlerImpl,	kTOCPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kModifyTOCFormatInfoCmdDataImpl, kTOCPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kTOCStripCharServiceProviderImpl, kTOCPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kTOCStripCharServiceImpl, kTOCPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kTOCNewWSResponderImpl, kTOCPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kGenerateTOCScriptProviderImpl, kTOCPrefix + 43)
//DECLARE_PMID(kImplementationIDSpace, kTOCCloseDocUIDRefListDataImpl, kTOCPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTOCStyleEntryScriptImpl, kTOCPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kTOCPhase2ConversionImpl, kTOCPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kTOCStorySuiteASBImpl, kTOCPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kTOCStorySuiteLayoutCSBImpl, kTOCPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTOCStorySuiteTextCSBImpl, kTOCPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kIData_K2Vector_UndoWithPreviousSequenceImpl, kTOCPrefix + 50)
// <Message ID>

// <Error ID>

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kTOCSuiteScriptElement,							kTOCPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleObjectScriptElement,						kTOCPrefix + 40)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateTOCMethodScriptElement,						kTOCPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kAddTOCStyleEntryMethodScriptElement,				kTOCPrefix + 81)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kTOCIncludeBookDocumentsPropertyScriptElement,		kTOCPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kTOCIncludeHiddenPropertyScriptElement,			kTOCPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kTOCRunInPropertyScriptElement,					kTOCPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleNamePropertyScriptElement,				kTOCPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kTOCTitlePropertyScriptElement,					kTOCPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kTOCTitleStylePropertyScriptElement,				kTOCPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedTOCStylePropertyScriptElement,				kTOCPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStyleEntryObjectScriptElement,					kTOCPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kTOCFormatStylePropertyScriptElement,				kTOCPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kTOCLevelPropertyScriptElement,					kTOCPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kTOCPageNumberStylePropertyScriptElement,			kTOCPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kTOCPageNumPosPropertyScriptElement,				kTOCPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kTOCSeparatorPropertyScriptElement,				kTOCPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kTOCSeparatorStylePropertyScriptElement,			kTOCPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kTOCSortAlphabetPropertyScriptElement,				kTOCPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kTOCCreateBookmarksPropertyScriptElement,			kTOCPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kTOCStoryDirectionropertyScriptElement,			kTOCPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kTOCNumberedParagraphsScriptElement,				kTOCPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kTOCMakeTextAnchorPropertyScriptElement,			kTOCPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kTOCRemoveFixedLineBreakPropertyScriptElement,		kTOCPrefix + 160)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kTOCPageNumPositionEnumScriptElement,				kTOCPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kTOCNumberedParagraphsEnumScriptElement,			kTOCPrefix + 221)

//Errors
DECLARE_PMID(kErrorIDSpace, kMissingTOCEntryInStyleError,	kTOCPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDeleteDefaultTOCStyleError,	kTOCPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kAddDuplicateTOCEntryInStyleError, kTOCPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kTOCEntryIncludeStyleError,		kTOCPrefix + 4)
DECLARE_PMID(kErrorIDSpace,	kConditionTag_LockedContainerErr,		kTOCPrefix + 5)

#endif //__TOCID__
