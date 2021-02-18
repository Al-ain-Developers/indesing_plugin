//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/GalleyInfoID.h $
//  
//  Owner: Matt Ramme
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

#ifndef __GALLEYINFOID__
#define __GALLEYINFOID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGalleyInfoPrefix	 RezLong(0xf900)	// reserved in AdobePrefix.h

//PlugInID
#define kGalleyInfoPlugInName		"GalleyInfo"
DECLARE_PMID(kPlugInIDSpace, kGalleyInfoPlugInID, kGalleyInfoPrefix + 1)

//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kGalleyInfoMenuActionBoss, 			kGalleyInfoPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kGalleyInfoKitRegisterBoss,			kGalleyInfoPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGalleyInfoBoss,					kGalleyInfoPrefix + 6)
DECLARE_PMID(kClassIDSpace, kStoryInfoWidgetBoss,				kGalleyInfoPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSelectionInfoWidgetBoss,			kGalleyInfoPrefix + 8)
DECLARE_PMID(kClassIDSpace, kToBeginInfoWidgetBoss,				kGalleyInfoPrefix + 9)
DECLARE_PMID(kClassIDSpace, kToEndInfoWidgetBoss,				kGalleyInfoPrefix + 10)
DECLARE_PMID(kClassIDSpace, kUpdateInfoButtonBoss,				kGalleyInfoPrefix + 11)
DECLARE_PMID(kClassIDSpace, kGalleyInfoShortcutsBoss,			kGalleyInfoPrefix + 12)
DECLARE_PMID(kClassIDSpace, kGalleyFitBarBoss,					kGalleyInfoPrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace, kWordCountOptionsDialogBoss,		kGalleyInfoPrefix + 15)
//gap

DECLARE_PMID(kClassIDSpace, kTestOversetRegisterBoss,			kGalleyInfoPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTabbedStatsPanelBoss,				kGalleyInfoPrefix + 18)
DECLARE_PMID(kClassIDSpace, kStatsStartUpServiceBoss,			kGalleyInfoPrefix + 19)
DECLARE_PMID(kClassIDSpace, kGalleyInfoConversionProviderBoss, 		kGalleyInfoPrefix + 20)

//---------------------------------------------------------------
//	Widget IDs
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kGalleyInfoPanelWidgetID,			kGalleyInfoPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kGalleyInfoHBarViewWidgetID,		kGalleyInfoPrefix + 2)
//gap
DECLARE_PMID(kWidgetIDSpace, kGalleyInfoPalViewWidgetID,		kGalleyInfoPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kStoryControlSetWidgetID,			kGalleyInfoPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kSelectionControlSetWidgetID,			kGalleyInfoPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kToBeginControlSetWidgetID,			kGalleyInfoPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kToEndControlSetWidgetID,			kGalleyInfoPrefix + 8)
//gap
DECLARE_PMID(kWidgetIDSpace, kGalleyInfoViewWidgetID,			kGalleyInfoPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kWholeStoryIconWidgetID,			kGalleyInfoPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kWholeStoryInfoWidgetID,			kGalleyInfoPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSelectionIconWidgetID,			kGalleyInfoPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSelectionInfoWidgetID,			kGalleyInfoPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kToBeginIconWidgetID,				kGalleyInfoPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kToBeginInfoWidgetID,				kGalleyInfoPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kToEndIconWidgetID,				kGalleyInfoPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kToEndInfoWidgetID,				kGalleyInfoPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kFitControlSetWidgetID,			kGalleyInfoPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kFitBarWidgetID,					kGalleyInfoPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kGalleyFitIconWidgetID,			kGalleyInfoPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kWordCountOptionsDialogId,			kGalleyInfoPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kWordCountOptionsClusterWidgetId,	kGalleyInfoPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kActualWordCountWidgetId,			kGalleyInfoPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFakeWordCountWidgetId,			kGalleyInfoPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kCharPerWordEditWidgetID,			kGalleyInfoPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kCountCharsStaticWidgetID,			kGalleyInfoPrefix + 27)

DECLARE_PMID(kWidgetIDSpace, kWholeStoryCountWidgetID,			kGalleyInfoPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSelectionCountWidgetID,			kGalleyInfoPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kToBeginCountWidgetID,				kGalleyInfoPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kToEndCountWidgetID,				kGalleyInfoPrefix + 33)

DECLARE_PMID(kWidgetIDSpace, kLinesStaticTextID,				kGalleyInfoPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kWordsStaticTextID,				kGalleyInfoPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kCharactersStaticTextID,			kGalleyInfoPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kDepthStaticTextID,				kGalleyInfoPrefix + 37)

// J text statistics widgets
DECLARE_PMID(kWidgetIDSpace, kFullCharStaticTextID,				kGalleyInfoPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kHalfCharStaticTextID,				kGalleyInfoPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kTotalCharsStaticTextID,			kGalleyInfoPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kStoryDetailedControlSetWidgetID,	kGalleyInfoPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kSelectionDetailedControlSetWidgetID,	kGalleyInfoPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kToBeginDetailedControlSetWidgetID,	kGalleyInfoPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kToEndDetailedControlSetWidgetID,	kGalleyInfoPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kParagraphsStaticTextID,			kGalleyInfoPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kKanjiStaticTextID,				kGalleyInfoPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kKanaStaticTextID,					kGalleyInfoPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kFitDetailedControlSetWidgetID,	kGalleyInfoPrefix + 48)


//---------------------------------------------------------------
//	Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSTATINFO, 			kGalleyInfoPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYFITCALCULATOR, 	kGalleyInfoPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDLEBOOLDATA, 			kGalleyInfoPrefix + 3)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYINFOSUITE, 		kGalleyInfoPrefix + 5)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERSETINFORMATIONEXCHANGE, kGalleyInfoPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IFITEXCHANGE, 			kGalleyInfoPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATSIDLETASK, 		kGalleyInfoPrefix + 10)

//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------
// gap
DECLARE_PMID(kImplementationIDSpace, kCTextStatInfoImpl,				kGalleyInfoPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoMenuComponentImpl,		kGalleyInfoPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoIdleTaskImpl,			kGalleyInfoPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoPanelViewImpl,			kGalleyInfoPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kUpdateInfoButtonObserverImpl,		kGalleyInfoPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStoryTextStatInfoImpl,			kGalleyInfoPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSelectionTextStatInfoImpl,		kGalleyInfoPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kToBeginTextStatInfoImpl,			kGalleyInfoPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kToEndTextStatInfoImpl,			kGalleyInfoPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kUpdateStatObserverImpl,			kGalleyInfoPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kUpdateFitObserverImpl,			kGalleyInfoPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGalleyFitCalculatorImpl,			kGalleyInfoPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kGalleyFitBarImpl,					kGalleyInfoPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kStatIdleObserverImpl,				kGalleyInfoPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoStaticTextViewImpl,		kGalleyInfoPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoKeyShortcutsImpl,		kGalleyInfoPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kWCOptionsDlgControllerImpl,		kGalleyInfoPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kWordCountOptionDataImpl_Obsolete,			kGalleyInfoPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoSuiteASBImpl,			kGalleyInfoPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoSuiteTextCSBImpl,		kGalleyInfoPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGalleyInfoSuiteNoteCSBImpl,		kGalleyInfoPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTextStatSelectionObserverImpl,	kGalleyInfoPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTextStatViewObserverImpl,			kGalleyInfoPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kFitTextStatInfoImpl,				kGalleyInfoPrefix + 25)
//gap
DECLARE_PMID(kImplementationIDSpace, kTextStatCountThreadImpl,			kGalleyInfoPrefix + 28)
//gap
DECLARE_PMID(kImplementationIDSpace, kOversetRegisterProviderImpl,		kGalleyInfoPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kTestOversetRegisterImpl,			kGalleyInfoPrefix + 31)
//gap
DECLARE_PMID(kImplementationIDSpace, kTabbedStatSetsDetailControllerImpl, kGalleyInfoPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kStatsStartupShutdownServiceImpl, kGalleyInfoPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kNoPanelTextStatInfoImpl, 			kGalleyInfoPrefix + 35)
//gap


//---------------------------------------------------------------
//	Message IDs
//---------------------------------------------------------------
//DECLARE_PMID(kMessageIDSpace, kChangesDialogActivatedMsg, 		kGalleyInfoPrefix + 1)

//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kGalleyInfoPanelActionID,				kGalleyInfoPrefix + 1)
DECLARE_PMID(kActionIDSpace, kUpdateAutoActionID,					kGalleyInfoPrefix + 2)
DECLARE_PMID(kActionIDSpace, kUpdateStoryInfoActionID,				kGalleyInfoPrefix + 3)
DECLARE_PMID(kActionIDSpace, kUpdateSelectionInfoActionID,			kGalleyInfoPrefix + 4)
DECLARE_PMID(kActionIDSpace, kUpdateToBeginInfoActionID,			kGalleyInfoPrefix + 5)
DECLARE_PMID(kActionIDSpace, kUpdateToEndInfoActionID,				kGalleyInfoPrefix + 6)
DECLARE_PMID(kActionIDSpace, kUpdateGalleyFitInfoActionID,			kGalleyInfoPrefix + 7)
DECLARE_PMID(kActionIDSpace, kWordCountOptionsActionID,				kGalleyInfoPrefix + 8)
DECLARE_PMID(kActionIDSpace, kWCPopupSepActionID,					kGalleyInfoPrefix + 9)
DECLARE_PMID(kActionIDSpace, kShowDetailsActionID,					kGalleyInfoPrefix + 10)
DECLARE_PMID(kActionIDSpace, kIncludeFootnotesActionID,				kGalleyInfoPrefix + 11)


//---------------------------------------------------------------
//	Scripting IDs
//---------------------------------------------------------------
DECLARE_PMID(kScriptInfoIDSpace, kOversetTextPropertyScriptElement,					kGalleyInfoPrefix + 1)


#define kFitExchangeSuppressed -2

#endif // __GALLEYINFOID__




