//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelPlugIn.cpp $
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

#include "VCPlugInHeaders.h"
#include "PlugIn.h"


// ------- PlugIn ---------
class SpellPanelPlugIn : public PlugIn {
public:
	virtual bool16 Load(ISession* theSession);

};

extern "C" IPlugIn *GetTextPanelLibPlugIn();	//exported from TextPanelLib.lib

bool16 SpellPanelPlugIn::Load(ISession* theSession)
{
	// First load TextPanelLib so its session is set up, then load ourselves
	bool16 result = GetTextPanelLibPlugIn()->Load(theSession);
	if (result == kTrue)
		result = PlugIn::Load(theSession);
	return result;
}

// ------------------------
// The Plugin:
static SpellPanelPlugIn gPlugIn;

// -------------------------------------------------------------
// ::GetPlugIn()
// -------------------------------------------------------------
// This is the main entry point from the application to the plug-in.
// The application calls this function when the plug-in is installed
// or loaded. This function is called by name, so it must be called
// GetPlugIn, and defined as C linkage.
IPlugIn *GetPlugIn()
{
	return &gPlugIn;
}

#ifdef DEBUG

	#include "TestMenuComponent.h"
	#include "Trace.h"

	#include "IDocument.h"
	#include "ISpellPanelOptions.h"
	#include "ISpellingPrefs.h"
	#include "PreferenceUtils.h"
	#include "SpellPanelID.h"
	#include "ILayoutUIUtils.h"
	#include "CmdUtils.h"
	#include "UIDList.h"
	#include "IActiveContext.h"

	static void IgnoreClearList();
	static void IgnoreDumpList();
	static void ToggleDynamicSpellCheck();

	bool16 bDynamicSpellCheck = kFalse;

	class SpellPanelTestMenu : public TestMenuComponent
	{
	public:
		SpellPanelTestMenu(IPMUnknown *boss);
	};
	CREATE_PERSIST_PMINTERFACE(SpellPanelTestMenu, kSpellPanelTestMenu)

	SpellPanelTestMenu::SpellPanelTestMenu(IPMUnknown *boss) :
		TestMenuComponent(boss)
	{
		AddTestMenu( "Linguistic",  "Ignore:Clear List", IgnoreClearList );
		AddTestMenu( "Linguistic",  "Ignore:Dump List", IgnoreDumpList );
		AddTestMenu( "Linguistic",  "Spelling:Dynamic Spell Check (Toggle Front Target)", ToggleDynamicSpellCheck );
	}

	//---------------------------------------------------------------
	// static IgnoreClearList()
	//---------------------------------------------------------------


	static void IgnoreClearList()
	{
		InterfacePtr<ISpellPanelOptions>pOptions( (ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS ) );
		if( pOptions )
			pOptions->ClearIgnoreList();
	}

	//---------------------------------------------------------------
	// static IgnoreDumpList()
	//---------------------------------------------------------------

	static void IgnoreDumpList()
	{
		InterfacePtr<ISpellPanelOptions>pOptions( (ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS ) );
		if( !pOptions )
			return;

		TRACEFLOW_OBSOLETE("Old:SpellPanel", "Dump Ignore All List:\n" );
		const int32 nMax = pOptions->GetIgnoredCount();
		for( int32 i = 0; i < nMax; ++i )
			TRACEFLOW_OBSOLETE("Old:SpellPanel", "\t\"%s\"\n", pOptions->GetNthIgnored( i ).GetUTF8String().c_str() );
	}

	//---------------------------------------------------------------
	// static ToggleDynamicSpellCheck()
	//---------------------------------------------------------------

	static void ToggleDynamicSpellCheck()
	{
		bDynamicSpellCheck = ! bDynamicSpellCheck;

	#if SPELL_PREFS_IMPLEMENTED
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSpellingPrefsCmdBoss));
		if (cmd)
		{
			InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
			if (!spellingPrefs)
			{
				ASSERT_MSG(spellingPrefs != nil, "spellingPrefs != nil");
				return;
			}

			cmd->SetItemList(UIDList(spellingPrefs));

			InterfacePtr<ISpellingPrefs> cmdPrefs(cmd, IID_ISPELLINGPREFS);
			if (!cmdPrefs)
			{
				ASSERT_MSG(cmdPrefs != nil, "cmdPrefs != nil");
				return;
			}

			cmdPrefs->SetDynamicSpellCheck(! spellingPrefs->GetDynamicSpellCheck());

			CmdUtils::ProcessCommand(cmd);
		}
	#endif
	}


#endif
