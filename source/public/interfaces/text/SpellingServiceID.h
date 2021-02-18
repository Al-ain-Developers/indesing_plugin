//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/SpellingServiceID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __SpellingServiceID__
#define __SpellingServiceID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSpellingServicePrefix			RezLong(0x5200) 	

// ---- Plugin ID

#define kSpellingServicePluginName 				"Spelling Service"
DECLARE_PMID(kPlugInIDSpace, kSpellingServicePluginID, kSpellingServicePrefix + 1)

#define kSpellingServiceStringsRsrcID				2000
#define kSpellingServiceStringsNoTransRsrcID		2100

// ---- Class IDs

DECLARE_PMID(kClassIDSpace, kSpellReplaceTextCmdBoss, kSpellingServicePrefix +  0)
DECLARE_PMID(kClassIDSpace, kSpellCheckTextCmdBoss, kSpellingServicePrefix + 1)
DECLARE_PMID(kClassIDSpace, kSpellCheckFindChangeDataBoss, kSpellingServicePrefix + 2)
DECLARE_PMID(kClassIDSpace, kSpellingPrefsCmdBoss, kSpellingServicePrefix +  3)
DECLARE_PMID(kClassIDSpace, kSpellPrefsScriptProviderBoss, kSpellingServicePrefix + 4)
DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckAdornmentBoss, kSpellingServicePrefix + 9)	// Was moved from SpellPanelID.h. Related to changelist 248176 (Model-UI separation).
DECLARE_PMID(kClassIDSpace, kAutoCorrectPrefsBoss, kSpellingServicePrefix + 10)
DECLARE_PMID(kClassIDSpace, kAutoCorrectPrefsScriptProviderBoss, kSpellingServicePrefix + 11)
DECLARE_PMID(kClassIDSpace, kAutoCorrectPrefsCmdBoss, kSpellingServicePrefix + 12)
DECLARE_PMID(kClassIDSpace, kAutoCorrectScriptProviderBoss, kSpellingServicePrefix + 13)
DECLARE_PMID(kClassIDSpace, kAutoCorrectWordPairScriptProviderBoss, kSpellingServicePrefix + 14)
DECLARE_PMID(kClassIDSpace, kAutoCorrectScriptBoss, kSpellingServicePrefix + 15)
DECLARE_PMID(kClassIDSpace, kAutoCorrectWordPairScriptBoss, kSpellingServicePrefix + 16)
DECLARE_PMID(kClassIDSpace, kAutoCorrectContentHandlerBoss, kSpellingServicePrefix + 17)
DECLARE_PMID(kClassIDSpace, kSpellingServiceConversionProviderBoss, kSpellingServicePrefix + 18)
DECLARE_PMID(kClassIDSpace, kAutoCorrectSettingsMigrationServiceProviderBoss, kSpellingServicePrefix + 19)


// ---- Interface IDs

DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGPREFS, kSpellingServicePrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCORRECTPREFS, kSpellingServicePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCORRECTUTILS, kSpellingServicePrefix + 2)

// ---- Implementation IDs

DECLARE_PMID(kImplementationIDSpace, kSpellReplaceTextCmd, kSpellingServicePrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kSpellingPrefsCmd, kSpellingServicePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSpellPrefsScriptProviderImpl, kSpellingServicePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kObsolete_AutoCorrectPrefsImpl, kSpellingServicePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectPrefsScriptProviderImpl, kSpellingServicePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectPrefsCmdImpl, kSpellingServicePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectScriptProviderImpl, kSpellingServicePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectWordPairScriptProviderImpl, kSpellingServicePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectScriptImpl, kSpellingServicePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectWordPairScriptImpl, kSpellingServicePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectContentHandlerImpl, kSpellingServicePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectUtilsImpl, kSpellingServicePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectPrefsImpl, kSpellingServicePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectSettingsMigrationImpl, kSpellingServicePrefix + 13)

//gap
DECLARE_PMID(kImplementationIDSpace, kSpellingPrefsImpl, kSpellingServicePrefix + 147)

// ---- Widget IDs

// ---- Action IDs

// ---- Script Element IDs

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kSpellPrefsObjectScriptElement,					kSpellingServicePrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectPrefsObjectScriptElement,				kSpellingServicePrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectObjectScriptElement,					kSpellingServicePrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectWordPairObjectScriptElement,			kSpellingServicePrefix + 13)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectPrefsPropertyScriptElement,			kSpellingServicePrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectPropertyScriptElement,					kSpellingServicePrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectCapErrorsPropertyScriptElement,		kSpellingServicePrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kAutoCorrectWordPairListPropertyScriptElement,		kSpellingServicePrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kMisspelledWordPropertyScriptElement,				kSpellingServicePrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kCorrectedWordPropertyScriptElement,				kSpellingServicePrefix + 66)

DECLARE_PMID(kScriptInfoIDSpace, kSpellPrefsPropertyScriptElement,					kSpellingServicePrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicSpellCheckPropertyScriptElement,			kSpellingServicePrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kMisspelledWordColorPropertyScriptElement,			kSpellingServicePrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kRepeatedWordColorPropertyScriptElement,			kSpellingServicePrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kUncapitalizedWordColorPropertyScriptElement,		kSpellingServicePrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kUncapitalizedSentenceColorPropertyScriptElement,	kSpellingServicePrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kCheckMisspelledWordsPropertyScriptElement,		kSpellingServicePrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kCheckRepeatedWordsPropertyScriptElement,			kSpellingServicePrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kCheckCapitalizedWordsPropertyScriptElement,		kSpellingServicePrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kCheckCapitalizedSentencesPropertyScriptElement,	kSpellingServicePrefix + 170)

//Enums


//GUIDS
// {AB3EA327-FA8A-438b-B76A-41B2A49E2D62}
#define kSpellPref_CLSID { 0xab3ea327, 0xfa8a, 0x438b, { 0xb7, 0x6a, 0x41, 0xb2, 0xa4, 0x9e, 0x2d, 0x62 } }
// {B31AF5C3-18BB-44e2-8A70-5624138BBEEA}
#define kAutoCorrectPref_CLSID { 0xb31af5c3, 0x18bb, 0x44e2, { 0x8a, 0x70, 0x56, 0x24, 0x13, 0x8b, 0xbe, 0xea } }
// {972BC446-C4E6-4f4f-B02D-39F0938E3775}
#define kAutoCorrect_CLSID { 0x972bc446, 0xc4e6, 0x4f4f, { 0xb0, 0x2d, 0x39, 0xf0, 0x93, 0x8e, 0x37, 0x75 } }
// {BF4F846F-EAB4-4f5a-AD1D-6272324EF3DA}
#define kAutoCorrects_CLSID	{ 0xbf4f846f, 0xeab4, 0x4f5a, { 0xad, 0x1d, 0x62, 0x72, 0x32, 0x4e, 0xf3, 0xda } }
// {20F8F012-8279-40b0-917C-A0C1F18167CD}
#define kAutoCorrectWordPair_CLSID { 0x20f8f012, 0x8279, 0x40b0, { 0x91, 0x7c, 0xa0, 0xc1, 0xf1, 0x81, 0x67, 0xcd } }
// {9B42640E-69AC-4b07-AAB4-87EF1DD6DF00}
#define kAutoCorrectWordPairs_CLSID { 0x9b42640e, 0x69ac, 0x4b07, { 0xaa, 0xb4, 0x87, 0xef, 0x1d, 0xd6, 0xdf, 0x0 } }

#endif // __SpellingServiceID__
