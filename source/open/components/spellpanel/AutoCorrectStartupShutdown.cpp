//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectStartupShutdown.cpp $
//  
//  Owner: Heath Horton
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
//  Proj:	Spelling Panel.µ
//  
//========================================================================================

#include "VCPlugInHeaders.h"		

#include "IIdleTask.h"
#include "IObserver.h"
#include "IStartupShutdownService.h"

#include "HelperInterface.h"
#include "SpellPanelID.h"

#include "Trace.h"

#include "PreferenceUtils.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "IAutoCorrectPrefs.h"
#include "IAutoCorrectUtils.h"

#include "FileUtility.h"

class AutoCorrectStartupShutdown : public IStartupShutdownService
{
public:
					AutoCorrectStartupShutdown(IPMUnknown *boss);
					~AutoCorrectStartupShutdown();
					
	virtual void 	Startup();
	virtual void 	Shutdown();

private:
			//void ExportAllAutoCorrectFiles();

	DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(AutoCorrectStartupShutdown, kAutoCorrectStartupShutdownImpl)
DEFINE_HELPER_METHODS(AutoCorrectStartupShutdown)


AutoCorrectStartupShutdown::AutoCorrectStartupShutdown(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}


AutoCorrectStartupShutdown::~AutoCorrectStartupShutdown()
{
}

void AutoCorrectStartupShutdown::Startup()
{
	InterfacePtr<IObserver> autoCorrectObserver(this, IID_IOBSERVER);
	if (autoCorrectObserver)
		autoCorrectObserver->AutoAttach();

	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS));
	if (autoCorrectPrefs && autoCorrectPrefs->GetAutoCorrect() )
	{
		InterfacePtr<IIdleTask> autoCorrectFolderTask((IIdleTask*) ::CreateObject (kAutoCorrectFolderIdleTaskBoss, IID_IIDLETASK));
		if (autoCorrectFolderTask)
			autoCorrectFolderTask->InstallTask(10000);	/* wait 10 seconds before we begin to read */
	}
}

void AutoCorrectStartupShutdown::Shutdown()
{
	//ExportAllAutoCorrectFiles();		we do not write these at shutdown, but it's a possible way to go
	
	InterfacePtr<IObserver> autoCorrectObserver(this, IID_IOBSERVER);
	if (autoCorrectObserver)
		autoCorrectObserver->AutoDetach();
}

#if 0
void AutoCorrectStartupShutdown::ExportAllAutoCorrectFiles()
{
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS));
	if (!autoCorrectPrefs)
		return;
	
	const AutoCorrectList& autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();

	InterfacePtr<ILanguageList> languageList((ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST));
	if (languageList)
	{
		for (int32 i = 0;  i < languageList->GetLanguageCount(); i++)
		{
			InterfacePtr<ILanguage> language(languageList->QueryNthLanguage(i));
			if (language)
			{
				bool16 foundLang = kFalse;

				LanguageID langID = language->GetLanguageID();

				for (int32 j = 0; j < autoCorrectList.Length(); ++j)
				{
					if (autoCorrectList[j].fLanguageID == langID)
					{
						foundLang = kTrue;
						break;
					}
				}

				if (foundLang)
				{
					IDFile file;
   					PMString autoCorrectPathname;
					
					bool16 bFoundXMLFile = kFalse;
					
					bool16 bHavePath = Utils<IAutoCorrectUtils>()->GetAutocorrectPrefsFile(file, language, autoCorrectPathname);
					if (bHavePath)
					{
						FileUtility fileUtility(file);
						bFoundXMLFile = fileUtility.FileExists();
					}

					ErrorCode err = Utils<IAutoCorrectUtils>()->ExportAutoCorrectXML(file, language);
				}
   			}
		}
	}
}
#endif