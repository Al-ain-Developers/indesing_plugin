//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/LinguisticTestMenu.cpp $
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

#include "VCPlugInHeaders.h"		// must be the first header file to include
#ifdef DEBUG

// ::HyphenateSelection
#include "ISelectionUtils.h"
#include "ITextFocus.h"

#include "WideString.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IComposeScanner.h"

#include "ISession.h"
#include "IHyphenationService.h"
#include "IHyphenationMgr.h"
#include "IHyphenatedWord.h"
#include "ExceptionHyphenWord.h"

#include "LanguageID.h"
#include "SpellPanelID.h"
#include "ILinguisticMgr.h"
#include "ILinguisticServiceData.h"
#include "PMString.h"
#include "PMTimer.h"

#include "TestMenuComponent.h"
#include "LinguisticID.h"

#include "ISpellingMgr.h"
#include "ISpellingService.h"
#include "ITextMiscellanySuite.h"

#include "IUserDictMgr.h"
#include "IUserDictService.h"
#include "IUserDictIterator.h"

#include "ILanguage.h"
#include "ILanguageList.h"
#include "IDocument.h"
#include "ITextAttrUID.h"
#include "CmdUtils.h"
#include "ICommand.h"
#include "TextAttrID.h"
#include "TextAttrUtils.h"

#include "CAlert.h"
#include "DebugClassUtils.h"

#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "TextWalkerServiceProviderID.h"
#include "ITextWalker.h"
#include "TextEditorID.h"

#include "Command.h"		//	HyphenateStoryCmd
#include "K2SmartPtr.h"		//	HyphenateStoryCmd

#include "ICmdCollection.h"		//	HyphenateStoryWalker

#include "ITextAttrUnderlineMode.h"	//	SpellCheckStoryWalker
#include "ISwatchUtils.h"	//	SpellCheckStoryWalker
#include "ISwatchList.h"	//	SpellCheckStoryWalker
#include "IWorkspace.h"	//	SpellCheckStoryWalker
#include "IApplyStyleData.h"	//	SpellCheckStoryWalker
#include "AttributeBossList.h"	//	SpellCheckStoryWalker

#include "IInsertHyphExceptionsCmdData.h"
#include "TextChar.h"

#include "IBoolData.h"

#include "ShuksanCoolType.h"			// kCTRomanScript

#include "LocaleSetting.h"
#include "IWalkerScopeFactoryUtils.h"
#include "ITextWalkerScope.h"
#include "Utils.h"

#include "IDictionaryUtils.h"
#include "TextCharBuffer.h"
#include "IHyphenationExceptions.h"
#include "Utils.h"

#include "IStrand.h"
#include "ISpellingDataStrand.h"
#include "IActiveContext.h"

#include "ISpellingUtils.h"
#include <stdarg.h>

//---------------------------------------------------------------
// templates
//---------------------------------------------------------------

#include "K2Vector.tpp"

#pragma warn_notinlined off

// -------------------------------------------------------------
//	debug globals
// -------------------------------------------------------------
extern bool16 gPaintInvalRect;
extern bool16 gDrawPurpleCache;
extern bool16 gDrawRunOriginPt;

// -------------------------------------------------------------
//	static functions
// -------------------------------------------------------------

//static void InstallTestMenu();
static PMString GetLanguageName( LanguageID nLanguage );

static void HyphenateSelection( const char *pProviderName, ClassID nClass, LanguageID nLang );
static void Hyphenate( IHyphenationService *pDict, const TextCharBuffer &rTxt, int16 nMinHead, int16 nMinTail );

static void SpellSelection( const char *pProviderName, ClassID nClass, LanguageID nLang );
static void Spell( ISpellingService *pDict, const WideString &rTxt );

static void ImportUserDict( const char *pProviderName, ClassID nClass, LanguageID nLang );

void VeryifyActiveStoryIsSpellChecked();


static void TraceSettings();
static void TraceLanguageIDs();

static void AddToUserDict();
static void RemoveFromUserDict();
static void DumpUserDict();
static void RemoveFromMainDict();
static void UndoRemoveFromMainDict();
static void DumpMainDict();
static void ClearUserDict();
static void ClearRemovedFromMainDict();
static void GetCorrectedWord();
static bool16 GetSelectedText( WideString *pTxt );
static void HyphenateStory();
static void SpellCheckStory();

static void ToggleChangeLocking();
static void TogglePaintInvalRect();
static void ToggleHilitePurple();
static void ToggleDrawRunOriginPt();

static void AddStandardAutoCorrections();
static void GuessScriptOfText();

static void SortSomeStrings();

//---------------------------------------------------------------
// static GetSelectedText()
//---------------------------------------------------------------

static bool16 GetSelectedText( WideString *pTxt )
{
	ISelectionManager*	iSelectionManager = Utils<ISelectionUtils> ()->GetActiveSelection();
	InterfacePtr<ITextMiscellanySuite> miscText(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, iSelectionManager)));

	if (miscText == nil)
		return kFalse;

	miscText->GetSelectedText(*pTxt);
	return pTxt->Length() > 0;
}

static  bool16 LinguTrace(bool16 traceit, bool16 bAutoUndo, char *format, ... )
{
	va_list argPtr;
	va_start( argPtr, format );
	const int kMaxStringSize = 4096;
	char aBuffer[kMaxStringSize];
	const int nLen = std::vsprintf( aBuffer, format, argPtr );
 	va_end( argPtr ); // clean up

	if( !nLen )
	{
		return kFalse;
	}

	if (traceit)
	{
		TRACEFLOW("Linguistics", aBuffer );
	}
	else
	{
#if 0
		if (!InsertWord( WideString(aBuffer), bAutoUndo))
		{
			return kFalse;
		}
#endif
	}

	return kTrue;
}

static  bool16 LinguTraceWideString(bool16 traceit, const WideString &rWideString )
{
	if (traceit)
		{
		TRACEFLOW("Linguistics", PMString(rWideString).GetUTF8String().c_str()  );
		}
	else
	{
#if 0
		if (!InsertWord(rWideString, kFalse))
		{
			return kFalse;
		}
#endif
	}

	return kTrue;
}



#define INHERITED PlugIn

#define UNKNOWN_LANGUAGE  "(unknown language)"

// --- classid
#ifndef kProxLinguistic
	#define kProximityPrefix		0x2E00			// Proximity spelling/hyphenation
	#define kInsoPrefix			0x2F00			// Inso spelling/hyphenation
	#define kSoftArtPrefix		0x3000			// SoftArt spelling/hyphenation
#endif

// -------------------------------------------------------------
// Test function table
// -------------------------------------------------------------

#define TEST_NAME( What, kClass, nLang )			What##kClass##_##nLang
#define USE_TEST( kClass, pName, nLang ) 	 TestFunctions( kClass, (pName), (nLang),  TEST_NAME( Hyph, kClass, nLang ), TEST_NAME( Spell, kClass, nLang ), TEST_NAME( Dict, kClass, nLang ) )
#define DECL_HYPH( kClass,  pName, nLang ) \
	void TEST_NAME( Hyph, kClass, nLang )(); \
	void TEST_NAME( Hyph, kClass, nLang )() \
	{ \
		HyphenateSelection( pName, kClass, nLang ); \
	}

#define DECL_SPELL( kClass,  pName, nLang ) \
	void TEST_NAME( Spell, kClass, nLang )(); \
	void TEST_NAME( Spell, kClass, nLang )() \
	{ \
		SpellSelection( pName, kClass, nLang ); \
	}

#define DECL_DICT( kClass,  pName, nLang ) \
	void TEST_NAME( Dict, kClass, nLang )(); \
	void TEST_NAME( Dict, kClass, nLang )() \
	{ \
		ImportUserDict( pName, kClass, nLang ); \
	}

#define DECL_LINGU(  kClass,  pName, nLang ) \
	DECL_HYPH( kClass,  pName, nLang ) \
	DECL_SPELL( kClass,  pName, nLang ) \
	DECL_DICT( kClass,  pName, nLang )

struct TestFunctions
{
	TestFunctions(ClassID classID, const char* name, LanguageID language,
		TestFuncPtr hyphFunc, TestFuncPtr spellFunc, TestFuncPtr dictFunc)
		: fClass(classID), fName(name), fLanguage(language),
		fHyphFunc(hyphFunc), fSpellFunc(spellFunc), fDictFunc(dictFunc) {};

	ClassID		fClass;
	const char *	fName;
	LanguageID	fLanguage;
	TestFuncPtr	fHyphFunc;
	TestFuncPtr	fSpellFunc;
	TestFuncPtr	fDictFunc;
};

static const char *pSimple = "Simple";
void HyphkInvalidClass_0(); void HyphkInvalidClass_0() { HyphenateSelection( pSimple, kInvalidClass, 0 ); }
void SpellkInvalidClass_0(); void SpellkInvalidClass_0() { SpellSelection( pSimple, kInvalidClass, 0 ); }
void DictkInvalidClass_0(); void DictkInvalidClass_0() { ImportUserDict( pSimple, kInvalidClass, 0 ); }
//DECL_LINGU( kInvalidClass, pSimple, kLanguageNeutral )  !!!MW x86 chokes on this statement!

static const char *pProximity = "Proximity";
const ClassID kProxLinguistic =	 kProximityPrefix + 1;
DECL_LINGU( kProxLinguistic, pProximity, kLanguageEnglish  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguageGerman  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguageDutch  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguageRussian  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguagePolish  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguageFrench  )
DECL_LINGU( kProxLinguistic, pProximity, kLanguageSpanish  )

static const char *pInso = "Inso";
const ClassID kInsoLinguistic = kInsoPrefix + 1;
DECL_LINGU( kInsoLinguistic, pInso, kLanguageEnglish )
DECL_LINGU( kInsoLinguistic, pInso, kLanguageGerman )
DECL_LINGU( kInsoLinguistic, pInso, kLanguageDutch  )

static const char *pSoftArt = "SoftArt";
const ClassID kSoftArtLinguistic = kSoftArtPrefix + 1;
DECL_LINGU( kSoftArtLinguistic, pSoftArt, kLanguageEnglish  )

static TestFunctions gTestFuncTable[] =
{
	//USE_TEST( kInvalidClass, pSimple, kLanguageNeutral ),	 !!!MW x86 chokes on this statement!
	TestFunctions( kInvalidClass, (pSimple), (0), HyphkInvalidClass_0, SpellkInvalidClass_0, DictkInvalidClass_0 ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageEnglish ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageGerman ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageDutch ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageRussian ),
	USE_TEST( kProxLinguistic, pProximity, kLanguagePolish ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageFrench ),
	USE_TEST( kProxLinguistic, pProximity, kLanguageSpanish ),
	USE_TEST( kInsoLinguistic, pInso, kLanguageEnglish ),
	USE_TEST( kInsoLinguistic, pInso, kLanguageGerman ),
	USE_TEST( kInsoLinguistic, pInso, kLanguageDutch ),
	USE_TEST( kSoftArtLinguistic, pSoftArt, kLanguageEnglish )
};

#define kMaxFunc 	(sizeof( gTestFuncTable ) / sizeof( TestFunctions ))


//////////////////////////////////////////////////////////////////
//				Test Menu
//////////////////////////////////////////////////////////////////

#ifdef DEBUG
class LinguisticTestMenu : public TestMenuComponent {
public:
	LinguisticTestMenu(IPMUnknown *boss);
};


CREATE_PERSIST_PMINTERFACE(LinguisticTestMenu, kLinguisticTestMenuImpl)

LinguisticTestMenu::LinguisticTestMenu(IPMUnknown *boss) :
	TestMenuComponent(boss)
{
	const CString pLingu = "Linguistic";

	// --- Unfortunately the runtime modification of menus is not supported yet.
	//	   So everything is hardcoded in the TestFunction table above...
	for( int16 i = 0; i < kMaxFunc; ++i )
	{
		TestFunctions &rFunc = gTestFuncTable[i];
		PMString aHyph( (const CString)rFunc.fName );
		PMString aSpell( (const CString)rFunc.fName );
		PMString aDict( (const CString)rFunc.fName );

		if( rFunc.fLanguage == kLanguageNeutral )
		{
			aHyph += " Hyphenation";
			aSpell += " Spelling";
			aDict += " UserDict";
		}
		else
		{
			aHyph += ":Hyphenation";
			aHyph += ":";
			aHyph += ::GetLanguageName( rFunc.fLanguage );

			aSpell += ":Spelling";
			aSpell += ":";
			aSpell += ::GetLanguageName( rFunc.fLanguage );

			aDict += ":Import";
			aDict += ":";
			aDict += ::GetLanguageName( rFunc.fLanguage );
		}

		AddTestMenu( pLingu,  aHyph, rFunc.fHyphFunc, kAlwaysEnabled, kFalse );
		AddTestMenu( pLingu,  aSpell, rFunc.fSpellFunc, kAlwaysEnabled, kFalse );
		AddTestMenu( pLingu,  aDict, rFunc.fDictFunc, kAlwaysEnabled, kFalse );
	}

//	AddTestMenu( pLingu,  "Mode:Manual + Algorithm", SwitchAlgoManual, kAlwaysEnabled, kFalse );
//	AddTestMenu( pLingu,  "Mode:Manual + Dictionary", SwitchDictManual, kAlwaysEnabled, kFalse );
//	AddTestMenu( pLingu,  "Mode:Manual", SwitchManual, kAlwaysEnabled, kFalse );
//	AddTestMenu( pLingu,  "Mode:Off", SwitchOff, kAlwaysEnabled, kFalse );
	//AddTestMenu( pLingu,  "Apply Klingon", ApplyKlingon, kAlwaysEnabled, kFalse );
	//InCopy
//	AddTestMenu( pLingu,  "Apply Extraterrestrial", ApplyKlingon, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "Trace Language Assignments", TraceSettings, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Trace Language IDs", TraceLanguageIDs, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "Dict:Clear removed from MainDict", ClearRemovedFromMainDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Clear UserDict", ClearUserDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Dump MainDict", DumpMainDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Undo remove from MainDict", UndoRemoveFromMainDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Remove from MainDict", RemoveFromMainDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Dump UserDict", DumpUserDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Remove from UserDict", RemoveFromUserDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Add to UserDict", AddToUserDict, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Dict:Get corrected word", GetCorrectedWord, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "Hyphenate Story", HyphenateStory, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "Spell Check Story", SpellCheckStory, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "Sort some strings", SortSomeStrings, kAlwaysEnabled, kFalse );

	AddTestMenu( "Text",  "Fonts:Toggle Change Locking", ToggleChangeLocking, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "Guess Script of Text", GuessScriptOfText, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "DSC:Verify Active Story is Spell Checked (Walk VOS)", VeryifyActiveStoryIsSpellChecked, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "DSC:Toggle DSC Paint Inval Rect", TogglePaintInvalRect, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "DSC:Toggle DSC Hilite Purple When Drawing From Cache", ToggleHilitePurple, kAlwaysEnabled, kFalse );
	AddTestMenu( pLingu,  "DSC:Toggle DSC Draw Run Origin Pt", ToggleDrawRunOriginPt, kAlwaysEnabled, kFalse );

	AddTestMenu( pLingu,  "AutoCorrect:Add Standard AutoCorrections", AddStandardAutoCorrections, kAlwaysEnabled, kFalse );

}
#endif


#if 0

//---------------------------------------------------------------
// static Switch*Mode()
//---------------------------------------------------------------

static void SwitchMode( LinguisticServiceMode nMode )
{
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	const int32 nMax = pLinguMgr->GetProviderCount();
	for( int32 i = 0; i < nMax; ++i )
	{
		 InterfacePtr<IK2ServiceProvider>pProvider( pLinguMgr->QueryNthProvider( i ) );
		InterfacePtr<ILinguisticServiceData>pData( pProvider, IID_ILINGUISTICDATA );
		pData->SetServiceMode( nMode );
	}
}

static void SwitchOff()
{
	::SwitchMode( kLinguisticService_Nothing );
}

static void SwitchManual()
{
	::SwitchMode( kLinguisticService_ManualOnly );
}

static void SwitchAlgoManual()
{
	::SwitchMode( kLinguisticService_Algorithm );
}

static void SwitchDictManual()
{
	::SwitchMode( kLinguisticService_Dictionary );
}
#endif

//---------------------------------------------------------------
// static QueryUserDictService()
//---------------------------------------------------------------

static ILanguage * QueryLanguage( ILinguisticMgr *pLinguMgr, LanguageID nLanguage )
{
	if( !pLinguMgr )
		return nil;

	PMString aLanguage;
	if( !pLinguMgr->GetLanguageName( nLanguage, &aLanguage ) )
		return nil;

	return pLinguMgr->QueryLanguage( aLanguage );
}


//---------------------------------------------------------------
// static HyphenateSelection()
//---------------------------------------------------------------

static void HyphenateSelection( const char *pProviderName, ClassID nClass, LanguageID nLang )
{
	LinguTrace(kTrue, kFalse, "\n***\n" );

	WideString aTxt;
	if (!GetSelectedText(&aTxt))
	{
		return;
	}

	// --- get the Hyphenation Service
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	// --- this works only with default hyphenator
	InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryLanguageByID(MakeLanguageID( nLang, kSubLanguageDefault )  ) );
	if( !pLanguage )
		return;

	InterfacePtr<IHyphenationService>pDict(  pLinguMgr->QueryHyphenationService( pLanguage,  nClass ) );
	ASSERT_MSG( pDict != nil, "LinguisticPlugin - no hyphenation service" );
	if( !pDict )
		return;

	InterfacePtr<IK2ServiceProvider>pProvider( pLinguMgr->QueryProviderByClassID( nClass ) );
	ASSERT_MSG( pProvider != 0, "LinguisticPlugin - hyphenation service not available, please check your shared libs" );
	if( pProvider )
	{
		LinguTrace(kTrue, kTrue, "Testing %s on %s\n", pProviderName, pLanguage->GetLanguageName().GetUTF8String().c_str());

		// --- 3 tests:
		TextCharBuffer		wrap(aTxt);
		::Hyphenate( pDict, wrap, 2, 3 );	// standard test
		::Hyphenate( pDict, wrap, 4, 0 );	// MinHead test
		::Hyphenate( pDict, wrap, 0, 4 );	// MinTail test
	}
}

//---------------------------------------------------------------
// static Hyphenate
//---------------------------------------------------------------

static void Hyphenate( IHyphenationService *pDict, const TextCharBuffer &rTxt, int16 nMinHead, int16 nMinTail  )
{

	IHyphenatedWord *pWord = 0;
	{
		// --- timer scope!
#ifdef DEBUG
		Timer aTimer( (char*)"\nHyphenation timer...", " ticks for a hyphenated word\n" );
#endif
		pWord = pDict->Hyphenate( rTxt, kLinguisticService_Algorithm, nMinTail, nMinHead );
	}

	pDict = 0;

	// MinTail and MinHead
	LinguTrace( kTrue, kTrue, "\tMinHead = %d, MinTail = %d\n", nMinHead, nMinTail );
	if( !pWord )
	{
		LinguTrace( kTrue, kTrue, "Hyphenation no positions found\n" );
	}
	else
	{
		const int nMax = pWord->GetPointCount();
		WideString aFirst, aLast;
		aFirst = pWord->GetWord();

		// The hyphenated word
		LinguTrace( kTrue, kTrue, "Hyphenation of '" );
		LinguTraceWideString( kTrue, aFirst );
		LinguTrace( kTrue, kTrue, "': %d positions found\n", pWord->GetPointCount() );


		for( int16 i = 0; i < nMax; ++i )
		{
			pWord->GetPartsOfPoint( i, &aFirst, &aLast );

			const char *pValueTxt = "unknown quality";
			switch( pWord->GetQualityOfPoint(i) )
			{
				case IHyphenatedWord::kNoHyphenPoint : 				pValueTxt = "no hyphen?! "; break;
				case IHyphenatedWord::kUnpreferredHyphenPoint :		pValueTxt = "unpreferred hyphen"; break;
				case IHyphenatedWord::kRegularHyphenPoint : 		pValueTxt = "regular hyphen"; break;
				case IHyphenatedWord::kPreferredHyphenPoint :		pValueTxt = "preferred hyphen"; break;
				case IHyphenatedWord::kDiscretionaryHyphenPoint : 	pValueTxt = "discretionary hyphen"; break;
				case IHyphenatedWord::kHardHyphenPoint : 			pValueTxt = "hard hyphen"; break;
			}

			LinguTrace( kTrue, kTrue, "\t" );
			LinguTraceWideString( kTrue, aFirst );
			LinguTrace( kTrue, kTrue, "-" );
			LinguTraceWideString( kTrue, aLast );
			LinguTrace( kTrue, kTrue, " \t[%s with %d%% at position %d]\n", pValueTxt, pWord->GetQualityOfPoint(i),
				pWord->GetIndexOfPoint(i) );

		}
		pWord->Release();
	}
}


//---------------------------------------------------------------
// static SpellSelection()
//---------------------------------------------------------------

static void SpellSelection( const char *pProviderName, ClassID nClass, LanguageID nLang )
{
	LinguTrace( kTrue, kFalse, "\n***\n" );

	WideString aTxt;
	if (!GetSelectedText(&aTxt))
	{
		return;
	}
	if( !aTxt.Length() )
		return;

	// --- get the Hyphenation Service
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	// --- this works only with default hyphenator
	InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryLanguageByID(MakeLanguageID( nLang, kSubLanguageDefault )  ) );
	if( !pLanguage )
		return;

	InterfacePtr<ISpellingService>pDict(  pLinguMgr->QuerySpellingService( pLanguage,  nClass ) );
	ASSERT_MSG( pDict != nil, "LinguisticPlugin - no hyphenation service" );
	if( !pDict )
		return;

	InterfacePtr<IK2ServiceProvider>pProvider( pLinguMgr->QueryProviderByClassID( nClass ) );
	ASSERT_MSG( pProvider != 0, "LinguisticPlugin - hyphenation service not available, please check your shared libs" );
	if( pProvider )
	{
		LinguTrace( kTrue, kTrue, "Testing %s on %s\n", pProviderName, pLanguage->GetLanguageName().GetUTF8String().c_str());
		::Spell( pDict, aTxt );
	}
}

//---------------------------------------------------------------
// static Spell
//---------------------------------------------------------------

static void Spell( ISpellingService *pDict, const WideString &rTxt )
{

	K2Vector<WideString> aAlternatives;

	ISpellingService::SpellResult nResult = ISpellingService::kIncorrectWord;
	{
		// --- timer scope!
#ifdef DEBUG
		Timer aTimer( (char*)"\tSpelling timer...", " ticks for a spelled word\n" );
#endif
		bool16 bEndsWithPeriod;

		nResult = pDict->Spell( rTxt, &aAlternatives, &bEndsWithPeriod );
	}

	if( nResult == ISpellingService::kCorrect )
	{
		LinguTrace( kTrue, kTrue, "This word is correct: '" );
		LinguTraceWideString( kTrue, rTxt );
		LinguTrace( kTrue, kTrue, "'\n" );
		return;
	}

	const int32 nMax = aAlternatives.size();
	if( !nMax )
	{
		LinguTrace( kTrue, kTrue, "This word is not correct but there are no alternatives found: '" );
		LinguTraceWideString( kTrue, rTxt );
		LinguTrace( kTrue, kTrue, "'\n" );
		return;
	}

	LinguTrace( kTrue, kTrue, "This word is not correct but there are %d alternatives found for '", nMax );
	LinguTraceWideString( kTrue, rTxt );
	LinguTrace( kTrue, kTrue, "':\n" );
	for( int32 i = 0; i < nMax; ++i )
	{
		const WideString &rAlternative = aAlternatives[i];
		LinguTrace( kTrue, kTrue, "\t\t'" );
		LinguTraceWideString( kTrue, rAlternative  );
		LinguTrace( kTrue, kTrue, "'\n" );
	}
}



//---------------------------------------------------------------
// static GetLanguageName()
//---------------------------------------------------------------

static PMString GetLanguageName( LanguageID nLanguage )
{
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	const LanguageID nLang = GetPrimaryLanguageID( nLanguage );
	PMString aLanguageName;
	pLinguMgr->GetLanguageName( nLang, &aLanguageName );
	return aLanguageName;
}


//---------------------------------------------------------------
// static TraceSettings()
//---------------------------------------------------------------

static void TraceSettings()
{
	LinguTrace( kTrue, kFalse, "\n***\n" );

	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );


	// dump the language assignments
	PMString aName;
	const int32 nProviderMax = pLinguMgr->GetProviderCount();

	LinguTrace( kTrue, kFalse, "LinguisticMgr has build the settings for each language:\n" );
	LinguTrace( kTrue, kTrue, "\t%ld Provider: ", nProviderMax );
	{
		for( int16 i = 0; i < nProviderMax; ++i )
		{
			InterfacePtr<IK2ServiceProvider>pProvider( pLinguMgr->QueryNthProvider( i ) );
			pProvider->GetName( &aName );
			LinguTrace( kTrue, kTrue, ", %s", aName.GetUTF8String().c_str() );
		}
	}
	LinguTrace( kTrue, kTrue, ".\n\n" );

	const uint32 nLanguageMax = pLinguMgr->GetLanguageCount();
	for( uint32 i = 0; i < nLanguageMax; ++i )
	{
		// Language
		InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryNthLanguage( i ) );
		LinguTrace( kTrue, kTrue, "\t%s: default=", pLanguage ? pLanguage->GetLanguageName().GetUTF8String().c_str() : "Default Language" );
		LanguageID nLang1 = pLanguage->GetLanguageID();
#ifdef DEBUG
		DebugClassUtilsBuffer aClassIDName;
		DebugClassUtils::GetIDName( &aClassIDName, ::GetClass( pLanguage ), kTrue );
#endif


		// Default:
		InterfacePtr<IK2ServiceProvider>pDefault( pLinguMgr->QueryDefaultService( ILinguisticMgr::kHyphenation, pLanguage ) );
		if( !pDefault )
			LinguTrace( kTrue, kTrue, "(no default)\n" );
		else
		{
			pDefault->GetName( &aName );
			LinguTrace( kTrue, kTrue, "%s\n", aName.GetUTF8String().c_str() );
		}

		// Hyphenation
		const uint32 nServiceMax = pLinguMgr->GetServiceCount( ILinguisticMgr::kHyphenation, pLanguage );
		for( uint32 j = 0; j < nServiceMax; ++j )
		{
			LanguageID nLang2 = pLanguage->GetLanguageID();
			InterfacePtr<IK2ServiceProvider>pHyphenation( pLinguMgr->QueryNthService( ILinguisticMgr::kHyphenation, pLanguage, j ) );
			pHyphenation->GetName( &aName );
			LinguTrace( kTrue, kTrue, "\t\t%s\n", aName.GetUTF8String().c_str() );
		}

//		LinguTrace( kTrue, kTrue, " \n"  );
	}
	LinguTrace( kTrue, kTrue, " \n\n\n" );
}

//---------------------------------------------------------------
// static TraceLanguageIDs()
//---------------------------------------------------------------

inline void TraceLangID( ILinguisticMgr *pMgr, const char *pPrimName, const char *pSubName, LanguageID nPrim,  LanguageID nSub )
{
	const LanguageID nLang = MakeLanguageID( nPrim, nSub );
	PMString aLanguage;
	if( !pMgr->GetLanguageName( nLang, &aLanguage ) )
		aLanguage = UNKNOWN_LANGUAGE;
	if( nSub != kSubLanguageNeutral )
		LinguTrace( kTrue, kTrue, "\t %s(0x%04X) = Prim:%s(0x%02X), Sub:%s(0x%02X).\n", aLanguage.GetUTF8String().c_str(),  nLang, pPrimName, nPrim, pSubName,  nSub );
	else
		LinguTrace( kTrue, kTrue, "\t %s(0x%04X)\n",   aLanguage.GetUTF8String().c_str(),  nLang );
}

#define TRACE_LANGID( nPrim, nSub ) \
	TraceLangID( pLinguMgr, #nPrim, #nSub, nPrim, nSub );

// BP 4/15/97: the bug is fixed (see LinguisticServiceProvider.cpp). So we don't need this trace function anymore.
//	But we will some day...

static void TraceLanguageIDs()
{
	LinguTrace( kTrue, kFalse, "\n***\n" );

	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	TRACE_LANGID( kLanguageArabic, kSubLanguageNeutral );

	// Arabic sub languages
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabic );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicIraq );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicEgypt );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicLibya );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicAlgeria );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicMorocco );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicTunisia );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicOman );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicYemen );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicSyria );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicJordan );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicLebanon );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicKuwait );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicUAE );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicBahrain );
	TRACE_LANGID( kLanguageArabic, kSubLanguageArabicQatar );

	TRACE_LANGID( kLanguageAfrikaans, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageAlbanian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageBasque, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageBulgarian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageByeloRussian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageCatalan, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageChinese, kSubLanguageNeutral );
// Chinese sub languages
	TRACE_LANGID( kLanguageChinese, kSubLanguageChineseTraditional );
	TRACE_LANGID( kLanguageChinese, kSubLanguageChineseSimplified );
	TRACE_LANGID( kLanguageChinese, kSubLanguageChineseHongKong );
	TRACE_LANGID( kLanguageChinese, kSubLanguageChineseSingapore );
	TRACE_LANGID( kLanguageCroatian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageCzech, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageDanish, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageDutch, kSubLanguageNeutral );
// Dutch sub languages
	TRACE_LANGID( kLanguageDutch, kSubLanguageDutch );
	TRACE_LANGID( kLanguageDutch, kSubLanguageDutchBelgian );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageNeutral );
// English sub languages
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishUS );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishUK );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishAustralian );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishCanadian );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishNewZealand );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishEire );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishSouthAfrica );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishJamaica );
	TRACE_LANGID( kLanguageEnglish, kSubLanguageEnglishCarribean );
	TRACE_LANGID( kLanguageEstonian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageFaeroese, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageFarsi, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageFinnish, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageFrench, kSubLanguageNeutral );
// French sub languages
	TRACE_LANGID( kLanguageFrench, kSubLanguageFrench );
	TRACE_LANGID( kLanguageFrench, kSubLanguageFrenchBelgian );
	TRACE_LANGID( kLanguageFrench, kSubLanguageFrenchCanadian );
	TRACE_LANGID( kLanguageFrench, kSubLanguageFrenchSwiss );
	TRACE_LANGID( kLanguageFrench, kSubLanguageFrenchLuxembourg );
	TRACE_LANGID( kLanguageGerman, kSubLanguageNeutral );
// German sub languages
	TRACE_LANGID( kLanguageGerman, kSubLanguageGerman );
	TRACE_LANGID( kLanguageGerman, kSubLanguageGermanSwiss );
	TRACE_LANGID( kLanguageGerman, kSubLanguageGermanAustrian );
	TRACE_LANGID( kLanguageGerman, kSubLanguageGermanLuxembourg );
	TRACE_LANGID( kLanguageGerman, kSubLanguageGermanLiechtenstein );
	TRACE_LANGID( kLanguageGreek, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageHebrew, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageHungarian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageIcelandic, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageIndonesian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageItalian, kSubLanguageNeutral );
// Italian sub languages
	TRACE_LANGID( kLanguageItalian, kSubLanguageItalian );
	TRACE_LANGID( kLanguageItalian, kSubLanguageItalianSwiss );
	TRACE_LANGID( kLanguageJapanese, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageKorean, kSubLanguageNeutral );
// Korean sub languages
	TRACE_LANGID( kLanguageKorean, kSubLanguageKorean );
	TRACE_LANGID( kLanguageKorean, kSubLanguageKoreanJohab );
	TRACE_LANGID( kLanguageLatvian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageLithuanian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageNorwegian, kSubLanguageNeutral );
// Norwegian sub languages
	TRACE_LANGID( kLanguageNorwegian, kSubLanguageNorwegianBokmal );
	TRACE_LANGID( kLanguageNorwegian, kSubLanguageNorwegianNynorsk );
	TRACE_LANGID( kLanguagePolish, kSubLanguageNeutral );
	TRACE_LANGID( kLanguagePortuguese, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageRomanian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageRussian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageSlovak, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageSlovenian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageSerbian, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageSerbian, kSubLanguageSerbianLatin );
	TRACE_LANGID( kLanguageSerbian, kSubLanguageSerbianCyrillic );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageNeutral );
// Spanish sub languages
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanish );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishMexican );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishModern );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishGuatemala );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishCostaRica );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishPanama );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishDominican );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishVenezuela );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishColombia );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishPeru );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishArgentina );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishEcuador );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishChile );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishUruguay );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishParaguay );
	TRACE_LANGID( kLanguageSpanish, kSubLanguageSpanishBolivia );
	TRACE_LANGID( kLanguageSwedish, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageThai, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageTurkish, kSubLanguageNeutral );
	TRACE_LANGID( kLanguageUkrainian, kSubLanguageNeutral );

}


//---------------------------------------------------------------
// static QueryUserDictService()
//---------------------------------------------------------------

static IUserDictService * QueryUserDictService()
{
	// --- get the Hyphenation Service
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryLanguageByID(MakeLanguageID( kLanguageEnglish, kSubLanguageDefault )  ) );
	if( !pLanguage )
		return nil;

	IUserDictService *pDict = pLinguMgr->QueryUserDictService( pLanguage );
	ASSERT_MSG( pDict != nil, "LinguisticPlugin - no UserDict service" );
	return pDict;
}

//---------------------------------------------------------------
// static AddToUserDict()
//---------------------------------------------------------------

static void AddToUserDict()
{
	// --- get the selected text
	WideString aWord;
	if( !::GetSelectedText( &aWord ) )
	{
		CAlert::WarningAlert( PMString( "Please select a word for adding to the user dict." ) );
		return;
	}

	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->AddToUserDict( nil, aWord ) )
		CAlert::WarningAlert( PMString( "IUserDictService::AddToDict() was refused." ) );
}

//---------------------------------------------------------------
// static RemoveFromUserDict()
//---------------------------------------------------------------

static void RemoveFromUserDict()
{
	// --- get the selected text
	WideString aWord;
	if( !::GetSelectedText( &aWord ) )
	{
		CAlert::WarningAlert( PMString( "Please select a word for adding to the user dict." ) );
		return;
	}

	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->RemoveFromUserDict( nil, aWord ) )
		CAlert::WarningAlert( PMString( "IUserDictService::RemoveFromUserDict() was refused." ) );
}

//---------------------------------------------------------------
// static RemoveFromMainDict()
//---------------------------------------------------------------

static void RemoveFromMainDict()
{
	// --- get the selected text
	WideString aWord;
	if( !::GetSelectedText( &aWord ) )
	{
		CAlert::WarningAlert( PMString( "Please select a word for adding to the user dict." ) );
		return;
	}

	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->RemoveFromMainDict( aWord ) )
		CAlert::WarningAlert( PMString( "IUserDictService::RemoveFromMainDict() was refused." ) );
}

//---------------------------------------------------------------
// static UndoRemoveFromMainDict()
//---------------------------------------------------------------

static void UndoRemoveFromMainDict()
{
	// --- get the selected text
	WideString aWord;
	if( !::GetSelectedText( &aWord ) )
	{
		CAlert::WarningAlert( PMString( "Please select a word for adding to the user dict." ) );
		return;
	}

	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->UndoRemoveFromMainDict( aWord ) )
		CAlert::WarningAlert( PMString( "IUserDictService::UndoRemoveFromMainDict() was refused." ) );
}

//---------------------------------------------------------------
// static ClearUserDict()
//---------------------------------------------------------------

static void ClearUserDict()
{
	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->ClearUserDict(nil) )
		CAlert::WarningAlert( PMString( "IUserDictService::ClearUserDict() was refused." ) );
}

//---------------------------------------------------------------
// static ClearRemovedFromMainDict()
//---------------------------------------------------------------

static void ClearRemovedFromMainDict()
{
	InterfacePtr<IUserDictService> pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	if( !pDict->ClearRemovedFromMainDict(nil) )
		CAlert::WarningAlert( PMString( "IUserDictService::ClearRemovedFromMainDict() was refused." ) );
}

//---------------------------------------------------------------
// static GetCorrectedWord()
//---------------------------------------------------------------

static void GetCorrectedWord()
{
	// --- get the selected text
	WideString aWord;
	if( !::GetSelectedText( &aWord ) )
	{
		CAlert::WarningAlert( PMString( "Please select a word for adding to the user dict." ) );
		return;
	}

	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	if( !pDict )
		return;

	WideString aCorrected;
	if( !pDict->GetCorrectedWord( nil, aWord, &aCorrected ) )
		CAlert::WarningAlert( PMString( "IUserDictService::GetCorrectedWord() was refused." ) );
}

//---------------------------------------------------------------
// static DumpUserDict()
//---------------------------------------------------------------

static void DumpUserDict()
{
	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	InterfacePtr<IUserDictIterator>pIterator(  pDict, IID_IUSERDICTITERATOR );
	if( !pDict || !pIterator )
		return;

	WideString aWord;
	PMString aPMString;
	if( !pIterator->First( pDict, nil, IUserDictService::kIsAWord, &aWord ) )
		return;

	aWord.GetSystemString( &aPMString );
	LinguTrace( kTrue, kTrue, "\t%s\n", aPMString.GetUTF8String().c_str() );

	while( pIterator->Next( &aWord ) )
	{
		aWord.GetSystemString( &aPMString );
		LinguTrace( kTrue, kTrue, "\t%s\n", aPMString.GetUTF8String().c_str() );
	}
}

//---------------------------------------------------------------
// static DumpMainDict()
//---------------------------------------------------------------

static void DumpMainDict()
{
	InterfacePtr<IUserDictService>pDict(  ::QueryUserDictService() );
	InterfacePtr<IUserDictIterator>pIterator(  pDict, IID_IUSERDICTITERATOR );
	if( !pDict || !pIterator )
		return;

	WideString aWord;
	PMString aPMString;
	if( !pIterator->First( pDict, nil, IUserDictService::kNotAWord, &aWord ) )
		return;

	aWord.GetSystemString( &aPMString );
	LinguTrace( kTrue, kTrue, "\t%s\n", aPMString.GetUTF8String().c_str() );

	while( pIterator->Next( &aWord ) )
	{
		aWord.GetSystemString( &aPMString );
		LinguTrace( kTrue, kTrue, "\t%s\n", aPMString.GetUTF8String().c_str() );
	}
}


//---------------------------------------------------------------
// static HyphenateStory()
//---------------------------------------------------------------

static void HyphenateStory()
{
	InterfacePtr<ICommand>pCmd( CmdUtils::CreateCommand( kHyphenateStoryCmdBoss ) );
	if( pCmd )
		CmdUtils::ProcessCommand( pCmd );
}



	//===============================================================
	// CLASS HyphenateStoryCmd
	//===============================================================

	class HyphenateStoryCmd : public Command
	{
	public:
					HyphenateStoryCmd(IPMUnknown * boss);

		virtual void Do();

	protected:
		virtual	PMString* CreateName()	{ return new PMString( "" ); }

	private:
		typedef		Command		Inherited;
	};

	//---------------------------------------------------------------
	// HyphenateStoryCmd constructor
	//---------------------------------------------------------------

	CREATE_PMINTERFACE(HyphenateStoryCmd, kHyphenateStoryCmdImpl)

	HyphenateStoryCmd::HyphenateStoryCmd(IPMUnknown *boss) :
		 Inherited(boss)
	{
		this->SetUndoability( ICommand::kAutoUndo );
	}

	//---------------------------------------------------------------
	// HyphenateStoryCmd::Do()
	//---------------------------------------------------------------

	void HyphenateStoryCmd::Do()
	{
		InterfacePtr<ITextWalker>pWalker( this, IID_ITEXTWALKER );
		if( !pWalker)
		{
			ASSERT_FAIL("missing IID_ITEXTWALKER at this boss");
			return;
		}

		ICommandSequence *cmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

		bool16 bResult = kFalse;
		K2::scoped_ptr<PMString>pName( this->CreateName() );
		cmdSequence->SetName( *pName );

		if (!pWalker->IsWalking())
		{
//			InterfacePtr<IWalkerScopeFactoryUtils>pScopeUtils(this, IID_IWALKERSCOPEFACTORYUTILS);
			InterfacePtr<ITextWalkerClient>pClient(this, UseDefaultIID());
			if( !pClient /*|| !pScopeUtils*/)
			{
				ASSERT_MSG( pClient != nil, " missing IID_ITEXTWALKERCLIENT at this boss." );
				return;
			}
			const IWalkerScopeFactoryUtils::WalkScopeType nScope = IWalkerScopeFactoryUtils::kStoryScope;
			InterfacePtr<ITextWalkerScope>pScope(static_cast <ITextWalkerScope*>
				(Utils<IWalkerScopeFactoryUtils>()->QueryWalkerScope_UsingSelections(nScope)));
			if (!pScope)
				return;
			pWalker->Initialize(pClient,pScope, nil, nil);
		}
		bResult = pWalker->Walk();
		CmdUtils::EndCommandSequence( cmdSequence );
	}

	//===============================================================
	// CLASS HyphenateStoryWalker
	//===============================================================

	class HyphenateStoryWalker : public ITextWalkerClient
	{
	public:
							HyphenateStoryWalker(IPMUnknown * boss);
							~HyphenateStoryWalker();

		virtual	bool16		OnStart( ITextWalker *pWalker );
		virtual	bool16		OnEnd( ITextWalker *pWalker );
		virtual	bool16		OnResume( ITextWalker *pWalker ) ;
		virtual bool16		OnSuspend( ITextWalker *pWalker ) { return kTrue; }

		virtual	bool16		OnNextPosition( ITextWalker *pWalker, ITextModel *pModel, TextIndex nPosition, TextIndex nStartRange, TextIndex nEndRange, int32 startRangePrcnt, int32 endRangePrcnt, bool16 rangeAdjustable);
		virtual	bool16		OnStoryStart( ITextWalker *pWalker, UID storyUID );
		virtual	void		OnStoryEnd( ITextWalker *pWalker ) { }
		virtual	bool16		OnDocumentStart( ITextWalker *pWalker, const UIDRef &doc ) { return kTrue; }
		virtual	void		OnDocumentEnd( ITextWalker *pWalker ) { }
		virtual void		SetReplacementCount(int32 nCount) { }
		virtual	int32		GetReplacementCount() { return 0; }
		virtual bool16		UpdateTextRange() { return kTrue; }

	DECLARE_HELPER_METHODS()

	private:

		ICommand *			fReplaceCmd;
		int32				fReplaceCount;
		TextIndex 			fStoryStart;

		const WideString	fPrefTilde;
		const WideString	fRegularTilde;
		const WideString	fUnprefTilde;
		const WideString	fBackSlash;
			 WideString		fHyPref;
			 WideString		fHyNorm;
			 WideString		fHyUnpref;
	struct ReplaceRec
	{
		typedef object_type	data_type;

		ReplaceRec(TextIndex at, uint32 oldWordLen,
			WideString* altReplaceString = nil) :
			fAt(at), fOldWordLen(oldWordLen)
			{
			if (altReplaceString)
			{
				fAltReplaceString = boost::shared_ptr<WideString>(new WideString(*altReplaceString));
			}
			else
			{
				fAltReplaceString = WideString::kNil_shared_ptr;
			}
			}

		bool16	operator<(const ReplaceRec& other) const
			{ return fAt < other.fAt; }
		bool16	operator>(const ReplaceRec& other) const
			{ return fAt > other.fAt; }
		bool16	operator==(const ReplaceRec& other) const
			{ return fAt == other.fAt; }

		TextIndex	fAt;
		uint32		fOldWordLen;
		boost::shared_ptr<WideString>	fAltReplaceString;
	};

	struct StoryRec
	{
		typedef object_type	data_type;

		StoryRec(UID storyUID) :
			fStoryUID(storyUID)
			{}

		~StoryRec()
		{
		}

		void	EmitReplaceCmds(ICmdCollection* pBag,
								int32* pReplaceCount,
								WideString* stdReplaceStr,
								IDataBase* db);

		UID						fStoryUID;
		K2Vector<ReplaceRec>	fReplaceList;
	};

	struct DocumentRec
	{
		typedef object_type	data_type;

		DocumentRec(UIDRef docRef) :
			fDocRef(docRef)
			{}

		void	EmitReplaceCmds(ICmdCollection* pBag,
								int32* pReplaceCount,
								WideString* stdReplaceStr);

		UIDRef				fDocRef;
		K2Vector<StoryRec>	fStoryList;
	};

	K2Vector<DocumentRec>	fDocList;

				bool16		HyphenateWord( const WideString &rWord, WideString *pReplaceString, const ILanguage *pLanguage ) const;
		bool16				MatchesLanguage( ITextModel *pModel,TextIndex nStart, TextIndex nEnd, UID nLanguage ) const;
		bool16 				GetHyphenatedWord( const IHyphenatedWord *pHyphWord, WideString *pWord ) const;
	};

	//=====================================================
	// CLASS HyphenateStoryWalker
	//=====================================================

	CREATE_PMINTERFACE(HyphenateStoryWalker, kHyphenateStoryWalkerImpl)
	DEFINE_HELPER_METHODS(HyphenateStoryWalker)

/*
	const uchar HY_NORM = 0x04;
	const uchar HY_PREF = 0x05;
	const uchar HY_UNPREF = 0x06;
	const uchar E_LRSEP = 0x08;
*/
	//---------------------------------------------------------------
	// HyphenateStoryWalker constructor
	//---------------------------------------------------------------

	HyphenateStoryWalker::HyphenateStoryWalker( IPMUnknown *boss) :
		HELPER_METHODS_INIT(boss),
		fPrefTilde( "~" ) ,
		fRegularTilde( "~~" ),
		fUnprefTilde( "~~~" ),
		fBackSlash( "\\" )
	{
		fReplaceCmd = nil;
		fReplaceCount = 0;
		fStoryStart = kInvalidTextIndex;

		fHyPref.Append( uchar( HY_PREF ) );
		fHyNorm.Append( uchar( HY_NORM ) );
		fHyUnpref.Append( uchar( HY_UNPREF ) );
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker destructor
	//---------------------------------------------------------------

	HyphenateStoryWalker::~HyphenateStoryWalker()
	{
		if( fReplaceCmd )
			fReplaceCmd->Release();
	}


	//---------------------------------------------------------------
	// HyphenateStoryWalker::OnStart
	//---------------------------------------------------------------

	bool16	HyphenateStoryWalker::OnStart( ITextWalker *pWalker )
	{
		// BP 07/10/98: TODO: right now OnStart() is called twice from TextWalker::WalkAllDocument().
		//	This is unnecessary since the introduction of OnDocumentChange(). After Wai has switched
		//	the code in FindChangeWalker you can remove the following two lines.
		if( fReplaceCmd )
			return kTrue;

		fReplaceCount = 0;
		fStoryStart = kInvalidTextIndex;

		ASSERT_MSG( fReplaceCmd == nil, "HyphenateStoryWalker - OnStart() called twice, missing OnEnd()" );
		if( fReplaceCmd )
		{
			fReplaceCmd->Release();
			fReplaceCmd = nil;
		}

		fReplaceCmd = CmdUtils::CreateCommand( kCompoundSequenceCmdBoss );


		return kTrue;
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::OnResume
	//---------------------------------------------------------------

	bool16	HyphenateStoryWalker::OnResume( ITextWalker *pWalker )
	{
		if( fReplaceCmd )
			return kTrue;

		fReplaceCount = 0;
		fStoryStart = kInvalidTextIndex;

		ASSERT_MSG( fReplaceCmd == nil, "HyphenateStoryWalker - OnResume() called twice, missing OnEnd()" );
		if( fReplaceCmd )
		{
			fReplaceCmd->Release();
			fReplaceCmd = nil;
		}

		fReplaceCmd = CmdUtils::CreateCommand( kCompoundSequenceCmdBoss );


		return kTrue;
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::OnEnd
	//---------------------------------------------------------------

	bool16	HyphenateStoryWalker::OnEnd( ITextWalker *pWalker )
	{
		if( fReplaceCmd )
		{
			// BP 07/10/98: spell checking and multiple documents.
			if( fReplaceCount )
				CmdUtils::ProcessCommand( fReplaceCmd );

			fReplaceCmd->Release();
			fReplaceCmd = nil;
		}

		fReplaceCount = 0;
		fStoryStart = kInvalidTextIndex;

		return kTrue;
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::OnNextPosition
	//---------------------------------------------------------------

	bool16 HyphenateStoryWalker::OnNextPosition( ITextWalker *pWalker,
										   ITextModel *pModel,
										   TextIndex nPosition,
										   TextIndex nStartRange,
										   TextIndex nEndRange,
										   int32 /* startRangePrcnt */,
										   int32 /* endRangePrcnt */,
										   bool16 rangeAdjustable)
	{

		InterfacePtr<IComposeScanner>pScanner( pModel, IID_ICOMPOSESCANNER );
		ASSERT_MSG( pScanner != 0, "HyphenateStoryWalker - missing IID_ICOMPOSESCANNER" );

		UID nLanguageUID = kInvalidUID;
		WideString aWord;
		const TextIndex nStart = pScanner->CopySurroundingWord( nPosition, &aWord, &nLanguageUID );
		if( nStart == kInvalidTextIndex || aWord.Length() == 0 )
		{
			// just move on...
			pWalker->MoveTo( nPosition + 1 );
			TRACEFLOW( "Linguistics", "HyphenateStoryWalker - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n" );
			return kTrue;
		}

		// BP 09/29/98: #263972 Spelling Change All and Ignore All do not respect the langauge settings.
		const TextIndex nEnd = nStart + aWord.Length();
		if( !this->MatchesLanguage( pModel, nStart, nEnd, nLanguageUID ) )
		{
			pWalker->MoveTo( nEnd + 1 );
			TRACEFLOW( "Linguistics", "HyphenateStoryWalker - Skipping word that does not match our language...\n" );
			return kTrue;
		}

		ASSERT((nStart >= nPosition) &&
				(nStart < nEndRange) &&
				(nEnd > nStart) &&
				(nEnd <= nEndRange));

		//
		// To deal with problem of starting the search in the middle
		// of a word we adjust the starting point to the first position
		// we have found something. This allows the search to wrap
		// around (if that's the scope) and find the word we started on.
		//
		if (rangeAdjustable)
		{
			int32	delta = (nStart - nPosition);
			if ((delta) &&
				(pWalker->AdjustRangeToStoryStart(delta)))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}

		int32 nWordLength = aWord.Length();
		WideString aDifferentReplaceString;

		// BP 4/9/97: CopySurroundingWord() could return kInvalidTextIndex
		InterfacePtr<const ILanguage>pLanguage( ::GetDataBase( pModel ), nLanguageUID, UseDefaultIID() );
		if( nWordLength == 0 || !this->HyphenateWord( aWord, &aDifferentReplaceString, pLanguage ))
		{
			// just move on...
			pWalker->MoveTo( nPosition + 1 );
			TRACEFLOW( "Linguistics", "HyphenateStoryWalker - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n" );
			return kTrue;
		}

		fDocList.back().fStoryList.back().fReplaceList.push_back(HyphenateStoryWalker::ReplaceRec(nStart, nWordLength, &aDifferentReplaceString));

		pWalker->MoveTo( nStart + nWordLength + 1 );

		return kTrue;
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::MatchesLanguage
	//---------------------------------------------------------------

	bool16 HyphenateStoryWalker::MatchesLanguage( ITextModel *pModel, TextIndex nStart, TextIndex nEnd, UID nLanguage) const
	{
		InterfacePtr<const ILanguage>pLanguage( this, UseDefaultIID() );
		if( !pLanguage || pLanguage->GetLanguageID() == kLanguageNeutral )
			return kTrue;

		if( nLanguage == kInvalidUID )
			return kFalse;

		InterfacePtr<const ILanguage>pFoundLanguage( ::GetDataBase( pModel ), nLanguage, UseDefaultIID() );
		if( !pFoundLanguage )
			return kFalse;

		return pLanguage->IsEqual( pFoundLanguage );
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::OnStoryStart
	//---------------------------------------------------------------

	bool16	HyphenateStoryWalker::OnStoryStart( ITextWalker *pWalker, UID storyUID )
	{
		return kTrue;
	}

	//---------------------------------------------------------------
	// HyphenateStoryWalker::HyphenateWord
	//---------------------------------------------------------------

	bool16 HyphenateStoryWalker::HyphenateWord( const WideString &rWord, WideString *pReplaceString, const ILanguage *pLanguage ) const
	{
		if( !rWord.Length() || !pReplaceString || !pLanguage )
			return kFalse;

		// see DictHyphenateObserver::DoApplyToFocus

		// --- get the Hyphenation Service
		InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
		InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
		InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
		if( !pLinguMgr )
			return kFalse;

		// --- this works only with default hyphenator
		InterfacePtr<IHyphenationService>pHyphenator( pLinguMgr->QueryHyphenationService( pLanguage ) );
		if( !pHyphenator )
			return kFalse;

		TextCharBuffer	wrap(rWord);
		K2::scoped_ptr<IHyphenatedWord>pHyphWord( pHyphenator->Hyphenate( wrap, kLinguisticService_Algorithm ) );
		return this->GetHyphenatedWord( pHyphWord.get(), pReplaceString );
	}


	//---------------------------------------------------------------
	// HyphenateStoryWalker::GetHyphenatedWord
	//---------------------------------------------------------------


	bool16 HyphenateStoryWalker::GetHyphenatedWord( const IHyphenatedWord *pHyphWord, WideString *pWord ) const
	{
		// see DictHyphenateObserver::GetHyphenatedWord
		if( !pHyphWord || !pWord )
			return kFalse;

		const int32 nMax = pHyphWord->GetPointCount();
		*pWord = pHyphWord->GetWord();
		if( !nMax )
			return kFalse;

		int32 i;
		for( i = nMax - 1; i >= 0; --i )
		{
			const int32 nQuality = pHyphWord->GetQualityOfPoint( i );

			const WideString *pPoint = nil;
			if( nQuality < IHyphenatedWord::kRegularHyphenPoint )
				pPoint = &fHyUnpref;
			else if( nQuality < IHyphenatedWord::kPreferredHyphenPoint )
				pPoint = &fHyNorm;
			else
				pPoint = &fHyPref;

			if( pPoint )
			{
				const int32 nIdx = pHyphWord->GetIndexOfPoint(i) + 1;
				ASSERT_MSG( nIdx < pWord->Length(), "DictHyphenateObserver - wrong IHyphenatedWord::GetIndexOfPoint()" );
				pWord->Insert( *pPoint, nIdx );
			}
		}

		const int32 nWordLength = pWord->Length();
		const uchar cTilde = '~';
		const uchar cBackSlash = '\\';

		for( i = nWordLength - 1; i >= 0; --i )
		{
			const UTF32TextChar cChar (pWord->GetChar(i));
			switch( cChar.GetValue() )
			{
				case HY_PREF :
					{
						pWord->Remove( i, 1 );
						pWord->Insert( fPrefTilde, i );
					}
					break;
				case HY_NORM :
					{
						pWord->Remove( i, 1 );
						pWord->Insert( fRegularTilde, i );
					}
					break;
				case HY_UNPREF :
					{
						pWord->Remove( i, 1 );
						pWord->Insert( fUnprefTilde, i );
					}
					break;
				case cTilde :
				case cBackSlash :
					{
						pWord->Insert( fBackSlash, i );
					}
					break;
			}
		}

		return kTrue;
	}

	void HyphenateStoryWalker::StoryRec::EmitReplaceCmds(ICmdCollection* pBag,
													   int32* pReplaceCount,
													   WideString* stdReplaceString,
													   IDataBase* db)
	{
		//
		// We are going to add a series of replaces commands
		// to the ICmdCollection interface on this boss. Each
		// replacement has the potential of adding or subtracting
		// characters and thus disturbing the starting location
		// of the NEXT replacement farther down in the TextModel.
		// To deal with this we have to perturb the starting
		// index of each replacement by the effect of all the
		// replacements that will occur before it.
		//	//
		// Since the order that the records were added is NOT
		// necessarily in TextModel order, we will need to sort
		// the records first.
		//
		std::sort(fReplaceList.begin(), fReplaceList.end());

		//
		// Build the commands and add them to the list.
		//
		InterfacePtr<ITextModel>	pModel(db, fStoryUID, UseDefaultIID());
		int32	delta = 0;
		InterfacePtr<ITextModelCmds>modelCmds(pModel, UseDefaultIID());
		for (int32 i = 0; i < fReplaceList.size(); i++)
		{
			int32		replaceIndex = delta + fReplaceList[i].fAt;
			int32		nWordLength = fReplaceList[i].fOldWordLen;
			boost::shared_ptr<WideString>	replaceStr = fReplaceList[i].fAltReplaceString;

			ICommand * pReplace = modelCmds->ReplaceCmd(replaceIndex, nWordLength, replaceStr);
			if (pReplace)
			{
				pBag->Append(pReplace);
				(*pReplaceCount)++;
				delta += (replaceStr->Length() - nWordLength);
			}
		}
	}

	void HyphenateStoryWalker::DocumentRec::EmitReplaceCmds(ICmdCollection* pBag,
														int32* pReplaceCount,
														WideString* stdReplaceStr)
	{
		for (int32 i = 0; i < fStoryList.size(); i++)
		{
			fStoryList[i].EmitReplaceCmds(pBag, pReplaceCount, stdReplaceStr, fDocRef.GetDataBase());
		}
	}


//---------------------------------------------------------------
// static SpellCheckStory()
//---------------------------------------------------------------

static void SpellCheckStory()
{
	InterfacePtr<ICommand>pCmd( CmdUtils::CreateCommand( kSpellCheckStoryCmdBoss ) );
	if( pCmd )
		CmdUtils::ProcessCommand( pCmd );
}



	//===============================================================
	// CLASS SpellCheckStoryCmd
	//===============================================================

	class SpellCheckStoryCmd : public Command
	{
	public:
					SpellCheckStoryCmd(IPMUnknown * boss);

		virtual void Do();

	protected:
		virtual	PMString* CreateName()	{ return new PMString( "SpellCheckStoryCmd" ); }

	private:
		typedef		Command		Inherited;
	};

	//---------------------------------------------------------------
	// SpellCheckStoryCmd constructor
	//---------------------------------------------------------------

	CREATE_PMINTERFACE(SpellCheckStoryCmd, kSpellCheckStoryCmdImpl)

	SpellCheckStoryCmd::SpellCheckStoryCmd(IPMUnknown *boss) :
		 Inherited(boss)
	{
		this->SetUndoability( ICommand::kAutoUndo );
	}

	//---------------------------------------------------------------
	// SpellCheckStoryCmd::Do()
	//---------------------------------------------------------------

	void SpellCheckStoryCmd::Do()
	{
		InterfacePtr<ITextWalker>pWalker( this, IID_ITEXTWALKER );
		if( !pWalker)
		{
			ASSERT_FAIL("missing IID_ITEXTWALKER at this boss");
			return;
		}
		ICommandSequence *cmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

		bool16 bResult = kFalse;
		K2::scoped_ptr<PMString>pName( this->CreateName() );
		cmdSequence->SetName( *pName );

		if (!pWalker->IsWalking())
		{
//			InterfacePtr<IWalkerScopeFactoryUtils>pScopeUtils(this, IID_IWALKERSCOPEFACTORYUTILS);
			InterfacePtr<ITextWalkerClient>pClient(this, UseDefaultIID());
			if( !pClient /*|| !pScopeUtils*/)
			{
				// TODO: set global error state...
				ASSERT_MSG( pClient != nil, " missing IID_ITEXTWALKERCLIENT at this boss." );
				return;
			}

			const IWalkerScopeFactoryUtils::WalkScopeType nScope = IWalkerScopeFactoryUtils::kStoryScope;
			InterfacePtr<ITextWalkerScope>pScope(static_cast <ITextWalkerScope*>
					(Utils<IWalkerScopeFactoryUtils>()->
						QueryWalkerScope_UsingSelections(nScope)));
			if (!pScope)
					return;
			pWalker->Initialize( pClient, pScope, nil, nil);
		}
		bResult = pWalker->Walk();
		CmdUtils::EndCommandSequence( cmdSequence );
	}


	//===============================================================
	// CLASS SpellCheckStoryWalker
	//===============================================================

	class SpellCheckStoryWalker : public ITextWalkerClient
	{
	public:
						SpellCheckStoryWalker(IPMUnknown * boss);
						~SpellCheckStoryWalker();

		virtual	bool16		OnStart( ITextWalker *pWalker );
		virtual	bool16		OnEnd( ITextWalker *pWalker );
		virtual	bool16		OnResume( ITextWalker *pWalker ) ;
		virtual bool16		OnSuspend( ITextWalker *pWalker ) { return kTrue; }

		virtual	bool16		OnNextPosition( ITextWalker *pWalker, ITextModel *pModel, TextIndex nPosition, TextIndex nStartRange, TextIndex nEndRange, int32 startRangePrcnt, int32 endRangePrcnt, bool16 rangeAdjustable);
		virtual	bool16		OnStoryStart( ITextWalker *pWalker, UID storyUID );
		virtual	void		OnStoryEnd( ITextWalker *pWalker ) { }
		virtual	bool16		OnDocumentStart( ITextWalker *pWalker, const UIDRef &doc ) { return kTrue; }
		virtual	void		OnDocumentEnd( ITextWalker *pWalker ) { }
		virtual void		SetReplacementCount(int32 nCount) { }
		virtual	int32		GetReplacementCount() { return 0; }
		virtual bool16		UpdateTextRange() { return kTrue; }

	DECLARE_HELPER_METHODS()

	private:

		ICommand *			fApplyCmd;

		TextIndex 			fStoryStart;
		int32				fApplyCount;

				bool16		SpellCheckWord( const WideString &rWord, const ILanguage *pLanguage ) const;
		bool16				MatchesLanguage( ITextModel *pModel,TextIndex nStart, TextIndex nEnd, UID nLanguage ) const;
	};

	//=====================================================
	// CLASS SpellCheckStoryWalker
	//=====================================================

	CREATE_PMINTERFACE(SpellCheckStoryWalker, kSpellCheckStoryWalkerImpl)
	DEFINE_HELPER_METHODS(SpellCheckStoryWalker)

	//---------------------------------------------------------------
	// SpellCheckStoryWalker constructor
	//---------------------------------------------------------------

	SpellCheckStoryWalker::SpellCheckStoryWalker( IPMUnknown *boss) :
		HELPER_METHODS_INIT(boss)
	{
		fApplyCmd = nil;
		fApplyCount = 0;
		fStoryStart = kInvalidTextIndex;
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker destructor
	//---------------------------------------------------------------

	SpellCheckStoryWalker::~SpellCheckStoryWalker()
	{
		if( fApplyCmd )
			fApplyCmd->Release();
	}


	//---------------------------------------------------------------
	// SpellCheckStoryWalker::OnStart
	//---------------------------------------------------------------

	bool16	SpellCheckStoryWalker::OnStart( ITextWalker *pWalker )
	{
		// BP 07/10/98: TODO: right now OnStart() is called twice from TextWalker::WalkAllDocument().
		//	This is unnecessary since the introduction of OnDocumentChange(). After Wai has switched
		//	the code in FindChangeWalker you can remove the following two lines.
		if( fApplyCmd )
			return kTrue;

		fApplyCount = 0;
		fStoryStart = kInvalidTextIndex;

		ASSERT_MSG( fApplyCmd == nil, "SpellCheckStoryWalker - OnStart() called twice, missing OnEnd()" );
		if( fApplyCmd )
		{
			fApplyCmd->Release();
			fApplyCmd = nil;
		}

		fApplyCmd = CmdUtils::CreateCommand( kCompoundSequenceCmdBoss );
		fApplyCmd->SetCreatorID( kTextAttrUnderlineBoss );

		return kTrue;
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker::OnResume
	//---------------------------------------------------------------

	bool16	SpellCheckStoryWalker::OnResume( ITextWalker *pWalker )
	{
		if( fApplyCmd )
			return kTrue;

		fApplyCount = 0;
		fStoryStart = kInvalidTextIndex;

		ASSERT_MSG( fApplyCmd == nil, "SpellCheckStoryWalker - called twice, missing OnEnd()" );
		if( fApplyCmd )
		{
			fApplyCmd->Release();
			fApplyCmd = nil;
		}

		fApplyCmd = CmdUtils::CreateCommand( kCompoundSequenceCmdBoss );
		fApplyCmd->SetCreatorID( kTextAttrUnderlineBoss );

		return kTrue;
	}
	//---------------------------------------------------------------
	// SpellCheckStoryWalker::OnEnd
	//---------------------------------------------------------------

	bool16	SpellCheckStoryWalker::OnEnd( ITextWalker *pWalker )
	{
		if( fApplyCmd )
		{
			// BP 07/10/98: spell checking and multiple documents.
			if( fApplyCount )
				CmdUtils::ProcessCommand( fApplyCmd );

			fApplyCmd->Release();
			fApplyCmd = nil;
		}

		fApplyCount = 0;
		fStoryStart = kInvalidTextIndex;

		return kTrue;
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker::OnNextPosition
	//---------------------------------------------------------------

	bool16 SpellCheckStoryWalker::OnNextPosition( ITextWalker *pWalker,
										   ITextModel *pModel,
										   TextIndex nPosition,
										   TextIndex nStartRange,
										   TextIndex nEndRange,
										   int32 /* startRangePrcnt */,
										   int32 /* endRangePrcnt */,
										   bool16 rangeAdjustable)
	{

		InterfacePtr<IComposeScanner>pScanner( pModel, IID_ICOMPOSESCANNER );
		ASSERT_MSG( pScanner != 0, "SpellCheckStoryWalker - missing IID_ICOMPOSESCANNER" );

		UID nLanguageUID = kInvalidUID;
		WideString aWord;
		const TextIndex nStart = pScanner->CopySurroundingWord( nPosition, &aWord, &nLanguageUID );
		if( nStart == kInvalidTextIndex || aWord.Length() == 0 )
		{
			// just move on...
			pWalker->MoveTo( nPosition + 1 );
			TRACEFLOW( "Linguistics", "SpellCheckStoryWalker - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n" );
			return kTrue;
		}

		// BP 09/29/98: #263972 Spelling Change All and Ignore All do not respect the langauge settings.
		const TextIndex nEnd = nStart + aWord.Length();
		if( !this->MatchesLanguage( pModel, nStart, nEnd, nLanguageUID ) )
		{
			pWalker->MoveTo( nEnd + 1 );
			TRACEFLOW( "Linguistics", "SpellCheckStoryWalker - Skipping word that does not match our language...\n" );
			return kTrue;
		}

		ASSERT((nStart >= nPosition) &&
				(nStart < nEndRange) &&
				(nEnd > nStart) &&
				(nEnd <= nEndRange));

		//
		// To deal with problem of starting the search in the middle
		// of a word we adjust the starting point to the first position
		// we have found something. This allows the search to wrap
		// around (if that's the scope) and find the word we started on.
		//
		if (rangeAdjustable)
		{
			int32	delta = (nStart - nPosition);
			if ((delta) &&
				(pWalker->AdjustRangeToStoryStart(delta)))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}

		int32 nWordLength = aWord.Length();

		 // 	see SpellWordObserver::ApplyToFocus()
		InterfacePtr<ICmdCollection>pBag( fApplyCmd, IID_ICMDCOLLECTION );
		ASSERT_MSG( pBag != nil, "SpellCheckStoryWalker - missing IID_ICMDCOLLECTION at kCompoundSequenceCmdBoss." );


		// BP 4/9/97: CopySurroundingWord() could return kInvalidTextIndex
		IDataBase *pDB = ::GetDataBase( pModel );
		InterfacePtr<const ILanguage>pLanguage( pDB, nLanguageUID, UseDefaultIID() );
		if( nWordLength == 0 || !pBag || this->SpellCheckWord( aWord, pLanguage ) )
		{
			// just move on...
			pWalker->MoveTo( nPosition + 1 );
			TRACEFLOW( "Linguistics", "SpellCheckStoryWalker - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n" );
			return kTrue;
		}

		// see CharUnderlineObserver
		InterfacePtr<ITextAttrUnderlineMode>pUnderlineAttr( static_cast<ITextAttrUnderlineMode*>(::CreateObject( kTextAttrUnderlineBoss, IID_ITEXTATTRUNDERLINEMODE )) );
		pUnderlineAttr->SetMode( IDrawingStyle::kUnderlineSingle );

		ICommand *pApplyCmd = ::BuildApplyUserTextAttrCmd( pModel, nStart, nWordLength, pUnderlineAttr, kCharAttrStrandBoss );
		if( pApplyCmd )
		{
			pApplyCmd->SetCreatorID( kTextAttrUnderlineBoss );

			const PMString aSpellCheckColorName( "Misspelled" );
			InterfacePtr<IDocument>pDocument( pDB, pDB->GetRootUID(), UseDefaultIID() );
			InterfacePtr<IWorkspace>pWorkspace( pDocument->GetDocWorkSpace(), UseDefaultIID() );
			InterfacePtr<ISwatchList>pSwatchList( pWorkspace, IID_ISWATCHLIST );
			UIDRef	aSpellCheckColor;
			if( pSwatchList )
			{
				aSpellCheckColor = pSwatchList->FindSwatch( aSpellCheckColorName );
				if( aSpellCheckColor.GetUID() == kInvalidUID )
					aSpellCheckColor = UIDRef( pDB, Utils<ISwatchUtils>()->CreateProcessRGBSwatch( pWorkspace, aSpellCheckColorName, 1.0, 0.0, 0.0 ) );

				if( aSpellCheckColor.GetUID() != kInvalidUID )
				{
					InterfacePtr<ITextAttrUID>pColorAttr( static_cast<ITextAttrUID*>(::CreateObject( kTextAttrColorBoss, IID_ITEXTATTRUID )) );
					pColorAttr->SetUIDData( aSpellCheckColor.GetUID() );
					InterfacePtr<IApplyStyleData>pAttributes( pApplyCmd, UseDefaultIID() );
					pAttributes->GrabOverrides()->ApplyAttribute( pColorAttr);
				}
			}

			pBag->Append( pApplyCmd );
			++fApplyCount;
		}

		pWalker->MoveTo( nStart + nWordLength + 1 );

		return kTrue;
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker::MatchesLanguage
	//---------------------------------------------------------------

	bool16 SpellCheckStoryWalker::MatchesLanguage( ITextModel *pModel, TextIndex nStart, TextIndex nEnd, UID nLanguage) const
	{
		InterfacePtr<const ILanguage>pLanguage( this, UseDefaultIID() );
		if( !pLanguage || pLanguage->GetLanguageID() == kLanguageNeutral )
			return kTrue;

		if( nLanguage == kInvalidUID )
			return kFalse;

		InterfacePtr<const ILanguage>pFoundLanguage( ::GetDataBase( pModel ), nLanguage, UseDefaultIID() );
		if( !pFoundLanguage )
			return kFalse;

		return pLanguage->IsEqual( pFoundLanguage );
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker::OnStoryStart
	//---------------------------------------------------------------

	bool16	SpellCheckStoryWalker::OnStoryStart( ITextWalker *pWalker, UID storyUID )
	{
		return kTrue;
	}

	//---------------------------------------------------------------
	// SpellCheckStoryWalker::SpellCheckWord
	//---------------------------------------------------------------

	bool16 SpellCheckStoryWalker::SpellCheckWord( const WideString &rWord, const ILanguage *pLanguage ) const
	{
		if( !rWord.Length() || !pLanguage )
			return kFalse;

		// see DictHyphenateObserver::DoApplyToFocus

		// --- get the Hyphenation Service
		InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
		InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
		InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
		if( !pLinguMgr )
			return kFalse;

		// --- this works only with default hyphenator
		InterfacePtr<ISpellingService>pSpellChecker( pLinguMgr->QuerySpellingService( pLanguage ) );
		if( !pSpellChecker )
			return kFalse;

		bool16 bEndsWithPeriod;

		return pSpellChecker->IsCorrect(rWord, &bEndsWithPeriod) == ISpellingService::kCorrect;
	}

	static void ToggleChangeLocking()
	{
		InterfacePtr<IK2ServiceRegistry>pServices( GetExecutionContextSession(), UseDefaultIID() );
		const int32 serviceCount = pServices->GetServiceProviderCount( kUserEditTextCmdResponder );
		for( int32 i = 0; i < serviceCount; ++i )
		{
			InterfacePtr<IK2ServiceProvider>editCmdResp( pServices->QueryNthServiceProvider( kUserEditTextCmdResponder, i ) );
			InterfacePtr<IBoolData>enableResp( editCmdResp, UseDefaultIID() );
			if( enableResp )
				enableResp->Set( !enableResp->GetBool() );
		}
	}

	static void TogglePaintInvalRect()
	{
		gPaintInvalRect = ! gPaintInvalRect;
	}

	static void ToggleHilitePurple()
	{
		gDrawPurpleCache = ! gDrawPurpleCache;
	}

	static void ToggleDrawRunOriginPt()
	{
		gDrawRunOriginPt = ! gDrawRunOriginPt;
	}

	// BP 09/07/00: only used by GuessScriptOfText()
	static int32 RoundTripScriptOfText( const char *anyText, int32 writingScript, bool16 dontAssert = kFalse )
	{
		if( writingScript == kCTDontKnowScript )
		{
			writingScript = Utils<ITextUtils>()->IsScriptOfText( anyText, writingScript );
			if( writingScript == kCTDontKnowScript )
				return writingScript;
		}

		if( !Utils<ITextUtils>()->IsScriptOfText( anyText, writingScript ) )
		{
			ASSERT_MSG( dontAssert || kFalse, "RoundTripScriptOfText: IsScriptOfText() failed." );
			return kCTDontKnowScript;
		}

		const int32 guessedWritingScript = Utils<ITextUtils>()->GuessScriptOfText( anyText, writingScript );
		ASSERT_MSG( dontAssert || guessedWritingScript == writingScript, "RoundTripScriptOfText: GuessScriptOfText() failed." );

		return guessedWritingScript;
	}

	// BP 09/07/00: introduced for testing PMTextUtils::IsScriptOfText() and PMTextUtils::GuessScriptOfText().
	static void GuessScriptOfText()
	{
		// simple Roman text is kCTRomanScript ...
		const char *romanText = "This is Roman text";
		ASSERT_MSG( ::RoundTripScriptOfText( romanText, kCTRomanScript ) == kCTRomanScript, "TestIsScriptOfText: simple Roman text." );

		// Roman text can be kCTJapaneseScript...
		ASSERT_MSG( ::RoundTripScriptOfText( romanText, kCTJapaneseScript, kTrue ) == kCTJapaneseScript, "TestIsScriptOfText: Roman can be Japanese." );

		// high ASCII Roman text is still kCTRomanScript...
		const unsigned char highASCIIStart = 0x80;
		const unsigned char highASCIIEnd = 0xFF;
		const int32 romanHighAsciiLength = ((highASCIIEnd-highASCIIStart)*2)+3;
		char romanHighAscii[romanHighAsciiLength];

		// we have to satisfy criteria #1: no more than 3 consecutive high ASCII characters
		for( int32 i = 0; i < (highASCIIEnd-highASCIIStart); ++i )
		{
			romanHighAscii[i*2] = highASCIIStart + i;
			romanHighAscii[(i*2)+1] = ' ';
		}

		// we have to satisfy criteria #2: no more than 49% high ASCII characters
		romanHighAscii[romanHighAsciiLength-1] = '\0';
		romanHighAscii[romanHighAsciiLength-2] = ' ';
		romanHighAscii[romanHighAsciiLength-3] = ' ';

		ASSERT_MSG( ::RoundTripScriptOfText( romanHighAscii, kCTRomanScript ) == kCTRomanScript, "TestIsScriptOfText: high ASCII Roman text." );

		// simple Japanese text is kCTJapaneseScript...
		const char *japaneseText = "Ç†Ç¢Ç§Ç¶Ç®";
		ASSERT_MSG( ::RoundTripScriptOfText( japaneseText, kCTJapaneseScript ) == kCTJapaneseScript, "TestIsScriptOfText: simple Japanese text." );

		// Japanese text is not kCTRomanScript
		ASSERT_MSG( ::RoundTripScriptOfText( japaneseText, kCTRomanScript, kTrue ) != kCTRomanScript, "TestIsScriptOfText: Japanese is not Roman." );

		// mixed Japanese/Roman text is kCTJapaneseScript...
		const char *mixedText = "TextÇ†Ç¢Ç§Ç¶Ç®";
		ASSERT_MSG( ::RoundTripScriptOfText( mixedText, kCTJapaneseScript ) == kCTJapaneseScript, "TestIsScriptOfText: mixed J/R text is Japanese." );
	}

#define kStringArraySize	11

static void SortSomeStrings()
{
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>	pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>		pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	InterfacePtr<ILanguage>				pLanguage(::QueryLanguage(pLinguMgr, MakeLanguageID(kLanguageEnglish, kSubLanguageEnglishUS)));

	WideString		a[kStringArraySize];

	a[0].SetCString("cat");
	a[1].SetCString("Caterpillar");
	a[2].SetCString("«at");
	a[3].SetCString("catheter");
	a[3].Insert(kTextChar_DiscretionaryHyphen, 3);

	a[4].SetCString("difficult");
	a[5].SetCString("dixculty");
	a[5].SetChar(2, kTextChar_ffiLigature);

	a[6].SetCString("Schoﬂ");
	a[7].SetCString("Schoss");
	a[8].SetCString("n");
	a[9].SetCString("x"); // U+00D2 is valid 1st byte in J
	a[9].SetChar(0, 0xD2);
	a[10].SetCString("o");


	for (int i = 0; i < kStringArraySize; i++)
	{
		for (int j = 0; j < kStringArraySize; j++)
		{
			LinguTraceWideString(kTrue, a[i]);
			int		compare = pLanguage->LinguisticCompare(a[i], a[j]);
			if (compare == 0)
				TRACEFLOW("Linguistics", " is equal to ");
			else if (compare < 0)
				TRACEFLOW("Linguistics", " sorts before ");
			else
				TRACEFLOW("Linguistics", " sorts after ");

			LinguTraceWideString(kTrue, a[j]);
			TRACEFLOW("Linguistics", "\n");
		}
	}

	InterfacePtr<ILanguage> pGermanLanguage(::QueryLanguage(pLinguMgr, MakeLanguageID(kLanguageGerman, kSubLanguageGerman)));

	for (int i = 0; i < kStringArraySize; i++)
	{
		for (int j = 0; j < kStringArraySize; j++)
		{
			LinguTraceWideString(kTrue, a[i]);
			int		compare = pGermanLanguage->LinguisticCompare(a[i], a[j]);
			if (compare == 0)
				TRACEFLOW("Linguistics", " is equal to ");
			else if (compare < 0)
				TRACEFLOW("Linguistics", " sorts before ");
			else
				TRACEFLOW("Linguistics", " sorts after ");

			LinguTraceWideString(kTrue, a[j]);
			TRACEFLOW("Linguistics", "\n");
		}
	}

	InterfacePtr<ILanguage> pSpanishLanguage(::QueryLanguage(pLinguMgr, MakeLanguageID(kLanguageSpanish, kSubLanguageSpanish)));

	for (int i = 0; i < kStringArraySize; i++)
	{
		for (int j = 0; j < kStringArraySize; j++)
		{
			LinguTraceWideString(kTrue, a[i]);
			int		compare = pSpanishLanguage->LinguisticCompare(a[i], a[j]);
			if (compare == 0)
				TRACEFLOW("Linguistics", " is equal to ");
			else if (compare < 0)
				TRACEFLOW("Linguistics", " sorts before ");
			else
				TRACEFLOW("Linguistics", " sorts after ");

			LinguTraceWideString(kTrue, a[j]);
			TRACEFLOW("Linguistics", "\n");
		}
	}


}

// BP 06/04/01: for Gary Cosimini and the NYT.
static void ImportUserDict( const char *pProviderName, ClassID providerClass, LanguageID nLang )
{
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider>	pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>		pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
	InterfacePtr<ILanguage>pLanguage( pLinguMgr->QueryLanguageByID(MakeLanguageID( nLang, kSubLanguageDefault )  ) );

	IDFile *userDoctFile = nil;
	const bool16 replaceOldDict = kTrue;
	const bool16 ignoreRanking = kTrue;

	Utils<IDictionaryUtils>()->ImportUserDict( pLanguage, nil, providerClass, userDoctFile, replaceOldDict, ignoreRanking );
}

#include "ISpellingDataStrand.h"
#include "ITextModel.h"
#include "IVOSCache.h"
#include "ISelectionManager.h"
#include "ITextTrackerAccess.h"
#include "ITextFocus.h"
#include "ISelectionUtils.h"

void VeryifyActiveStoryIsSpellChecked(void)
{
	InterfacePtr<ISelectionManager> selMgr( Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<ITextTrackerAccess> focusAccess( selMgr, UseDefaultIID());
	if (!focusAccess) return;

	InterfacePtr<ITextFocus> focus( focusAccess->QueryTextFocus());
	if (!focus) return;

	InterfacePtr<ITextModel> model(focus->QueryModel());
	if (!model) return;

	Utils<ISpellingUtils>()->VerifyStoryIsSpellChecked(model);
}

#include "IAutoCorrectPrefs.h"
#include "PreferenceUtils.h"

static void AddStandardAutoCorrections( void )
{
    InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
    if (autoCorrectPrefs)
	{
		AutoCorrectList autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();

		KeyValuePair<WideString,WideString> pair1(WideString("hte"), WideString("the"));
		KeyValuePair<WideString,WideString> pair2(WideString("hh"), WideString("Heath Horton"));
		KeyValuePair<WideString,WideString> pair3(WideString("waht"), WideString("what"));
		AutoCorrectItem autoCorrectItem;

		//autoCorrectItem.fAutoStringPair.Append(pair1);
		//autoCorrectItem.fAutoStringPair.Append(pair2);
		//autoCorrectItem.fAutoStringPair.Append(pair3);
		autoCorrectItem.fAutoStringPair.Bind(pair1.Key(), pair1.Value());
		autoCorrectItem.fAutoStringPair.Bind(pair2.Key(), pair2.Value());
		autoCorrectItem.fAutoStringPair.Bind(pair3.Key(), pair3.Value());
		autoCorrectItem.fLanguageID = MakeLanguageID(kLanguageEnglish, kSubLanguageEnglishUS);

		autoCorrectList.Insert(autoCorrectItem);

        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kAutoCorrectPrefsCmdBoss));
        InterfacePtr<IAutoCorrectPrefs> newPrefs(cmd, IID_IAUTOCORRECTPREFS);    /* grab the prefs interface on the cmd boss */
        ASSERT_MSG(newPrefs != nil, "newPrefs != nil");

        newPrefs->SetAutoCorrect(autoCorrectPrefs->GetAutoCorrect());
        newPrefs->SetAutoCorrectCapitalizationErrors(autoCorrectPrefs->GetAutoCorrectCapitalizationErrors());
        newPrefs->SetAutoCorrectList(autoCorrectList);

        CmdUtils::ProcessCommand(cmd);
	}
}


#endif
