//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/ApplySpellPanelOptionsCmd.cpp $
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

#include "Command.h"
#include "SpellPanelID.h"

#include "IUIDData.h"
#include "ITextOptions.h"
#include "ISubject.h"
#include "TextID.h"
#include "TextWalkerServiceProviderID.h"
#include "ISpellPanelOptions.h"
#include "PreferenceUtils.h"

class ApplySpellPanelOptionsCmd : public Command
{
public:
	ApplySpellPanelOptionsCmd(IPMUnknown * boss);
	
	virtual void Do();
	virtual void DoNotify();

protected:
	PMString* CreateName();
};


CREATE_PMINTERFACE(ApplySpellPanelOptionsCmd, kApplySpellPanelOptionsCmd)

ApplySpellPanelOptionsCmd::ApplySpellPanelOptionsCmd(IPMUnknown *boss) :
	 Command(boss)
{
	this->SetTarget( Command::kSessionWorkspaceTarget );
	this->SetUndoability( ICommand::kAutoUndo );
}

PMString* ApplySpellPanelOptionsCmd::CreateName()
{
	return new PMString("Setting Spelling Options");
}

void ApplySpellPanelOptionsCmd::Do()
{
	InterfacePtr<ISpellPanelOptions> pWorkSpaceOptions((ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS ));	
	if( !pWorkSpaceOptions )
		return;
	
	InterfacePtr<ISpellPanelOptions>pNewOptions( this, IID_ISPELLPANELOPTIONS);
	InterfacePtr<ISpellPanelOptions>pSavedOptions( this, IID_ISAVEDSPELLPANELOPTIONS);
	pSavedOptions->CopyFrom( pWorkSpaceOptions );
	pWorkSpaceOptions->CopyFrom( pNewOptions );
}


void ApplySpellPanelOptionsCmd::DoNotify()
{
	InterfacePtr<ISpellPanelOptions> pWorkSpaceOptions((ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS ));	
	if( !pWorkSpaceOptions )
		return;
	InterfacePtr<ISubject> workspaceSubject( pWorkSpaceOptions, IID_ISUBJECT );
	if( workspaceSubject )
		workspaceSubject->ModelChange(kApplySpellPanelOptionsCmdBoss, IID_ISPELLPANELOPTIONS, this);
}

