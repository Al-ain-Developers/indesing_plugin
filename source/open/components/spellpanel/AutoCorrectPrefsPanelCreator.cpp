//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectPrefsPanelCreator.cpp $
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
//  Proj:	AutoCorrectPanel
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IControlView.h"

#include "CmdUtils.h"
#include "CoreResTypes.h"
#include "cpanelcreator.h"

#include "SpellPanelID.h"

class AutoCorrectPrefsPanelCreator : public CPanelCreator
{
public:
	// ----- Initialization -----
	
						AutoCorrectPrefsPanelCreator(IPMUnknown *boss);
	virtual				~AutoCorrectPrefsPanelCreator();
	
	// ----- Dialog protocol -----

	virtual	RsrcID		GetPanelRsrcID() const;
};


CREATE_PMINTERFACE(AutoCorrectPrefsPanelCreator, kAutoCorrectPrefsPanelCreatorImpl)

AutoCorrectPrefsPanelCreator::AutoCorrectPrefsPanelCreator(IPMUnknown *boss) :
	CPanelCreator(boss)
{
}

AutoCorrectPrefsPanelCreator::~AutoCorrectPrefsPanelCreator()
{
}

RsrcID AutoCorrectPrefsPanelCreator::GetPanelRsrcID() const
{
	RsrcID	rsrcID = kAutoCorrectPrefsDialogCreatorRsrcID;

	return rsrcID;
}

