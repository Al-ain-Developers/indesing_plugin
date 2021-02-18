//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectFolderIdleTask.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IIdleTask.h"
#include "IIdleTaskMgr.h"
#include "IAutoCorrectPrefs.h"

// ----- Implementation Includes -----

#include "SpellPanelID.h"
#include "CPMUnknown.h"

#include "IAutoCorrectUtils.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "ISession.h"
#include "PreferenceUtils.h"

//========================================================================================
// CLASS AutoCorrectFolderIdleTask
//========================================================================================

class AutoCorrectFolderIdleTask: public CPMUnknown<IIdleTask>
{
public:
	typedef CPMUnknown<IIdleTask> inherited;

	AutoCorrectFolderIdleTask(IPMUnknown *boss); 

	virtual uint32 RunTask( uint32 appFlags, IdleTimer* timeCheck);
	virtual void InstallTask(uint32 millisecsBeforeFirstRun);
	virtual void UninstallTask();
	virtual const char* TaskName();

private:
	int32	fLanguageIndex;
};

//========================================================================================
// METHODS AutoCorrectFolderIdleTask
//========================================================================================

CREATE_PMINTERFACE(AutoCorrectFolderIdleTask, kAutoCorrectFolderIdleTaskImpl)

//----------------------------------------------------------------------------------------
// AutoCorrectFolderIdleTask::AutoCorrectFolderIdleTask
//----------------------------------------------------------------------------------------

AutoCorrectFolderIdleTask::AutoCorrectFolderIdleTask(IPMUnknown *boss) :
	inherited(boss),
		fLanguageIndex(0)
{
}

//----------------------------------------------------------------------------------------
// AutoCorrectFolderIdleTask::RunTask
//----------------------------------------------------------------------------------------

 uint32 AutoCorrectFolderIdleTask::RunTask( uint32 appFlags, IdleTimer* timeCheck)
 {
	if ( appFlags & IIdleTaskMgr::kModalDialogUp )
		return kOnFlagChange;
		
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
	if (!autoCorrectPrefs || !autoCorrectPrefs->GetAutoCorrect() )
		return kEndOfTime;

	InterfacePtr<ILanguageList> languageList((ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST));
	// hkhalfal
	// We do not want any of the changes this function may make to the session Workspace DB 
	// to appear on the undo stack.
	CmdUtils::AutoUndoSequencePtr auSeq(::GetDataBase(languageList));

	if (languageList)
	{
		if (fLanguageIndex <= languageList->GetLanguageCount())
		{
			for (int32 i = fLanguageIndex;  i < languageList->GetLanguageCount(); i++)
			{
				InterfacePtr<ILanguage> language(languageList->QueryNthLanguage(i));
				if (language)
				{
					IDFile file;
   					PMString autoCorrectPathname;
					
					bool16 bFoundXMLFile = kFalse;
					
					bool16 bHavePath = Utils<IAutoCorrectUtils>()->GetAutocorrectPrefsFile(file, language, autoCorrectPathname);
					if (bHavePath)
						bFoundXMLFile = file.Exists();

					if (!bFoundXMLFile)
					{
						bHavePath = Utils<IAutoCorrectUtils>()->GetAutocorrectPresetsFile(file, language, autoCorrectPathname);
						if (bHavePath)
							bFoundXMLFile = file.Exists();
					}
					
					ErrorCode err = kSuccess;
					if (bFoundXMLFile)
						err = Utils<IAutoCorrectUtils>()->ImportAutoCorrectXML(file);

					++fLanguageIndex;

					if (bFoundXMLFile)
						break;
   				}
			}
		}
	}
	
	int32 numMilliSeconds = 1000;

	if (fLanguageIndex >= languageList->GetLanguageCount())
		numMilliSeconds = kEndOfTime;

	return numMilliSeconds;
 }

//----------------------------------------------------------------------------------------
// AutoCorrectFolderIdleTask::InstallTask
//----------------------------------------------------------------------------------------
 
 void AutoCorrectFolderIdleTask::InstallTask(uint32 millisecsBeforeFirstRun)
 {
	InterfacePtr<IIdleTaskMgr> idleTaskMgr(GetExecutionContextSession(), UseDefaultIID());
	if (idleTaskMgr)
		idleTaskMgr->AddTask(this, millisecsBeforeFirstRun);
 }

//----------------------------------------------------------------------------------------
// AutoCorrectFolderIdleTask::UninstallTask
//----------------------------------------------------------------------------------------

 void AutoCorrectFolderIdleTask::UninstallTask()
 {
	InterfacePtr<IIdleTaskMgr> idleTaskMgr(GetExecutionContextSession(), UseDefaultIID());
	if (idleTaskMgr)
		idleTaskMgr->RemoveTask(this);
 }

//----------------------------------------------------------------------------------------
// AutoCorrectFolderIdleTask::TaskName
//----------------------------------------------------------------------------------------

 const char* AutoCorrectFolderIdleTask::TaskName()
 {
	 return "AutoCorrect Folder Task";
 }
