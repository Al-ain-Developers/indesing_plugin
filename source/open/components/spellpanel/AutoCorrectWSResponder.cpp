//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectWSResponder.cpp $
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
//  Initializes the app workspace's swatch lists.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CResponder.h"
#include "isignalmgr.h"
#include "INewWorkspaceSignalData.h"
#include "IAutoCorrectPrefs.h"
#include "ISubject.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "ICommand.h"

#include "ErrorUtils.h"
#include "HelperInterface.h"
#include "SpellPanelID.h"
#include "PreferenceUtils.h"

class AutoCorrectWorkspaceResponder : public CResponder
{
public:
	AutoCorrectWorkspaceResponder(IPMUnknown*);

public:
	virtual void		Respond(ISignalMgr* signalMgr);

};

CREATE_PMINTERFACE (AutoCorrectWorkspaceResponder, kAutoCorrectNewWSResponderImpl)

AutoCorrectWorkspaceResponder::AutoCorrectWorkspaceResponder(IPMUnknown* boss) :
	CResponder (boss)
{
}
	

#pragma mark-
//________________________________________________________________________________________
//	DESCR:		Initialize the app workspace's default swatch list and ui color list
//				We assume that the default swatch list contains only colors.
//________________________________________________________________________________________
void AutoCorrectWorkspaceResponder::Respond(ISignalMgr* signalMgr)
{
	InterfacePtr<INewWorkspaceSignalData> data(signalMgr, IID_INEWWORKSPACESIGNALDATA);
	InterfacePtr<IWorkspace> workspace(data->GetWorkspace(), IID_IWORKSPACE);
	
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
	if (autoCorrectPrefs)
	{

	}
		
	//InterfacePtr<IAutoCorrect>	swatchList( workspace, IID_ISWATCHLIST );
	//if ( swatchList )
	//	swatchList->Init();
	
	// default UI color list
	//InterfacePtr<IAutoCorrect>	uiColorList( workspace, IID_IUICOLORLIST );
	//if ( uiColorList )
	//	uiColorList->Init();
		
	//InterfacePtr<IInkList>		inkList( workspace, IID_IINKLIST );
	//if ( inkList )
	//	inkList->Init();
}

