//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IMEID.h $
//  
//  Owner: Heath Horotn
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

#ifndef __CJKIMEID__
#define __CJKIMEID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


// Double check kIMEPrefix with AdobePrefix.h
#define kIMEPrefix						RezLong(0x2400)
#define UNICODE_IME		1

// <Start IDC>
// PluginID
#define kIMEPluginName 					"IME"
DECLARE_PMID(kPlugInIDSpace, kIMEPluginID, kIMEPrefix + 1)



// <Class ID>
// class ids
DECLARE_PMID(kClassIDSpace, kCJKIMEBoss, kIMEPrefix + 1)
// Gap - was kTextAttrClauseModeBoss
DECLARE_PMID(kClassIDSpace, kIMETextAttrCompModeBoss_Obsolete, kIMEPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kTextAdornmentIMEHintsBoss, kIMEPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTextAdornmentIMEHintsDataBoss, kIMEPrefix + 6)
DECLARE_PMID(kClassIDSpace, kIMETestMenuBoss, kIMEPrefix + 7)
DECLARE_PMID(kClassIDSpace, kIMEStartupBoss, kIMEPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSetIMEPrefsCmdBoss, kIMEPrefix + 9)
// Gap - kIMEPrefsPanelBoss moved to IMEPrefs plugin
// Gap - kIMEPrefsMenuComponentBoss moved to IMEPrefs plugin
DECLARE_PMID(kClassIDSpace, kOpenIMEPrefsCmdBoss, kIMEPrefix + 12)
// Gap - kIMEMenuRegisterBoss removed during Hotaka development
DECLARE_PMID(kClassIDSpace, kIMEConversionBoss, kIMEPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCarbonTypingThreadBoss, kIMEPrefix + 15)
DECLARE_PMID(kClassIDSpace, kIMEPrefsScriptProviderBoss, kIMEPrefix + 16)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IINPUTEDITOR, kIMEPrefix + 1)
	// Gap - IID_IIMEWINDOW and IID_ITEXTATTRCLAUSEMODE removed for Hotaka
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRCOMPMODE, kIMEPrefix + 4)
	// Gap - IID_IMACIMEEVENTHANDLER removed for Hotaka
DECLARE_PMID(kInterfaceIDSpace, IID_IIMECONTEXT, kIMEPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEEVENTHANDLER, kIMEPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEPREFERENCES, kIMEPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEPREFSCMDDATA, kIMEPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMECOMPCLAUSE, kIMEPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMESUITE, kIMEPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEGALLEYTEXTADORNMENT, kIMEPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMETEXTOBSERVER, kIMEPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEUTILS, kIMEPrefix + 14)


// <Implementation ID>
// ImplementationIDs
	// Gap - kIMEWindow removed for Hotaka
DECLARE_PMID(kImplementationIDSpace, kIMEObserverImpl, kIMEPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kIMEInputEditor, kIMEPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kIMEEventHandler, kIMEPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kIMETextAttrClauseMode_Obsolete, kIMEPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kIMETAClauseReport_Obsolete, kIMEPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kIMETextAttrCompMode_Obsolete, kIMEPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kIMETACompReport_Obsolete, kIMEPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kIMEServiceProvider, kIMEPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kTextAdornmentIMEHintsImpl, kIMEPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTextAdornmentIMEHintsDataImpl, kIMEPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kIMETestMenuImpl, kIMEPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kIMEStartupServiceImpl, kIMEPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kIMEStartupShutdownImpl, kIMEPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSetIMEPrefsCmdImpl, kIMEPrefix + 18)
	// Gap - kCIMEPrefsImpl and kSessionIMEPrefsImpl removed during Hotaka development
DECLARE_PMID(kImplementationIDSpace, kCIMECompClauseImpl, kIMEPrefix + 21)
	// Gap - kIMEFocusImpl removed during Hotaka development
DECLARE_PMID(kImplementationIDSpace, kIMEPrefsImpl_Obsolete, kIMEPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kIMEPrefsCmdDataImpl, kIMEPrefix + 24)
// Gap - kIMEPrefsDialogControllerImpl moved to IMEPrefs plugin
// Gap - kIMEPrefsPanelCreator moved to IMEPrefs plugin
// Gap - kIMEPrefsMenuComponent removed during Hotaka development
DECLARE_PMID(kImplementationIDSpace, kIMEContext, kIMEPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPlatformEventHandler, kIMEPrefix + 29)
//gap
DECLARE_PMID(kImplementationIDSpace, kIMEPrefsImpl, kIMEPrefix + 32)
//gap kCarbonTypingIdleTaskImpl deleted(it never actually ran as an idle task)
DECLARE_PMID(kImplementationIDSpace, kGalleyIMEAdornmentImpl, kIMEPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kIMEPrefsScriptProviderImpl, kIMEPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kIMETextObserverImpl, kIMEPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kIMEUtilsImpl, kIMEPrefix + 37)


DECLARE_PMID(kImplementationIDSpace, kIMESuiteASBImpl, 						kIMEPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteTextCSBImpl, 					kIMEPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteGalleyCSBImpl, 				kIMEPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteNoteCSBImpl, 					kIMEPrefix + 43)
//...
DECLARE_PMID(kImplementationIDSpace, kIMESuiteASBSelectionExtImpl, 			kIMEPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteTextCSBSelectionExtImpl, 		kIMEPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteGalleyCSBSelectionExtImpl, 	kIMEPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kIMESuiteNoteCSBSelectionExtImpl, 		kIMEPrefix + 49)



//
//Script Element IDs
//

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kIMEPreferenceObjectScriptElement, 		kIMEPrefix + 10)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kIMEPrefsPropertyScriptElement, 			kIMEPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kInlineInputPropertyScriptElement, 		kIMEPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kNativeDigitsPrefPropertyScriptElement,	kIMEPrefix + 22)

//GUIDS
// {A26F1392-4E33-4451-B923-899ADA3A96ED}
#define kIMEPref_CLSID { 0xa26f1392, 0x4e33, 0x4451, { 0xb9, 0x23, 0x89, 0x9a, 0xda, 0x3a, 0x96, 0xed } }


// <Service ID>
//service ID
	// Gap - kCJKIMEService removed for Hotaka


#endif //__CJKIMEID__
