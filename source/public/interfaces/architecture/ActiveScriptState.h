//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ActiveScriptState.h $
//  
//  Owner: Jonathan W. Brown
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

#pragma once
#ifndef __ActiveScriptState__
#define __ActiveScriptState__

#include "IAMSPManager.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IScriptEngine.h"

#include "CAlert.h"
#include "ProgressBar.h"
#include "Utils.h"
/**
	Stack-based approach to handling the active script state
*/
class ActiveScriptState
{
public:
	ActiveScriptState(IScriptEngine* eng) : fEng(eng), fShowAlerts(kFalse), fSuppressProgressBars(nil), fSuppressDialogs(kFalse), fShowWGAuthenticationUI(kFalse)
	{
		ASSERT_MSG( fEng != nil, "ActiveScriptState is missing IScriptEngine" ) ;
		if ( fEng )
		{
			fEng->AddRef() ;
			fEng->IncrementActiveScriptCount() ;
			fShowAlerts = CAlert::GetShowAlerts() ;
			InterfacePtr<IApplication> app;
			ISession* session = GetExecutionContextSession();
			if (session)
				app = InterfacePtr<IApplication>(session->QueryApplication());
			InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
			if (dialogMgr)
				fSuppressDialogs = dialogMgr->GetSuppressDialogs();

			InterfacePtr<IAMSPManager> iAMSPManager( session, UseDefaultIID() );
			if ( iAMSPManager != nil )
				fShowWGAuthenticationUI = iAMSPManager->IsAuthenticationUIEnabled();

		//	We don't want to clobber the current ShowAlerts or SupressDialogs setting if someone else is trying to supress the UI(e.g. buildacceptance)
			if(fShowAlerts)
				CAlert::SetShowAlerts( fEng->GetShowAlerts() ) ;
			if (dialogMgr && !fSuppressDialogs)
				dialogMgr->SetSuppressDialogs( !fEng->GetShowDialogs() ) ;

			if ( !fEng->GetShowDialogs() )
				fSuppressProgressBars = new SuppressProgressBarDisplay();
			if ( iAMSPManager != nil )
				iAMSPManager->EnableAuthenticationUI( fEng->GetShowDialogs() );
		}
	}

	~ActiveScriptState()
	{
		if ( fEng )
		{
			InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
			if (dialogMgr)
				dialogMgr->SetSuppressDialogs( fSuppressDialogs ) ;
			CAlert::SetShowAlerts( fShowAlerts ) ;

			InterfacePtr<IAMSPManager> iAMSPManager( GetExecutionContextSession(), UseDefaultIID() );
			if ( iAMSPManager != nil )
				iAMSPManager->EnableAuthenticationUI( fShowWGAuthenticationUI );
				
			fEng->DecrementActiveScriptCount() ;
			fEng->Release() ;
			fEng = nil ;
			if (fSuppressProgressBars)
				delete fSuppressProgressBars;
		}
	}

	IScriptEngine* GetScriptEngine()
	{
		return fEng ;
	}

private:
	IScriptEngine*				fEng ;
	SuppressProgressBarDisplay* fSuppressProgressBars;
	bool16						fShowAlerts ;
	bool16						fSuppressDialogs ;
	bool16						fShowWGAuthenticationUI;
} ;

#endif
