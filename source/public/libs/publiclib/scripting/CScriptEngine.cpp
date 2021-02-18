//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CScriptEngine.cpp $
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

#include "VCPublicHeaders.h"
#include "CScriptEngine.h"

#include "IScriptRequestData.h"
#include "IScriptManager.h"
#include "IScriptPreferences.h"
#include "IPrivateScriptUtils.h"

// Moved to PublicImpl.cpp in Utilities project
//CREATE_PMINTERFACE( CScriptEngine, kSingleScriptEngineImpl )

CScriptEngine::CScriptEngine( IPMUnknown* boss, ClassID requestDataBoss /*= kCScriptRequestDataBoss*/ ) :
	Inherited( boss ),
	fRequestDataBoss( requestDataBoss ),
	fActiveScripts( 0 )
{
}

ErrorCode CScriptEngine::Install()
{
	return kSuccess ;
}

ErrorCode CScriptEngine::UnInstall()
{
	return kSuccess ;
}

IScriptRequestData* CScriptEngine::CreateScriptRequestData() /*const*/
{
	InterfacePtr<IScriptRequestData> scriptRequestData ;

	//Search the cache for a boss to recycle
	for ( K2Vector<InterfacePtr<IScriptRequestData> >::iterator iter = fSEDCache.begin() ; iter != fSEDCache.end() ; ++iter )
	{
		//We assume a boss is available if we own the only references
		InterfacePtr<IControllingUnknown> boss( *iter, UseDefaultIID() ) ;
		ASSERT( boss ) ;
		if ( boss && boss->GetRefCount() == 2 )	//one ref for the cache and one for IControllingUnknown
		{
			scriptRequestData = *iter ;
			break ;
		}
	}

	if ( scriptRequestData == nil )
	{
		//Create a new boss and add it to the cache
		scriptRequestData.reset( ::CreateObject2<IScriptRequestData>( fRequestDataBoss ) ) ;
		fSEDCache.push_back( scriptRequestData ) ;
	}

	if ( scriptRequestData )
		ResetScriptRequestData(scriptRequestData);

	return scriptRequestData.forget() ;
}

EngineContext CScriptEngine::GetRequestContext() const
{
	InterfacePtr<IScriptPreferences> scriptPrefs( this, UseDefaultIID() ) ;
	ASSERT( scriptPrefs ) ;
	if ( scriptPrefs )
	{
		InterfacePtr<IScriptManager> scriptMgr( QueryScriptManager() ) ;
		return EngineContext( scriptMgr, scriptPrefs->GetVersion(), scriptPrefs->GetLocale(), this ) ;
	}
	return EngineContext() ;
}

IScriptManager* CScriptEngine::QueryScriptManager() const
{
	//For the single engine client, it's simplest to aggregate its IScriptEngine to the IScriptManager boss
	InterfacePtr<IScriptManager> scriptMgr( this, UseDefaultIID() ) ;
	ASSERT( scriptMgr ) ;
	return scriptMgr.forget() ;
}

PMString CScriptEngine::GetName() const
{
	return PMString( "Default" ) ;	//##jwb need to translate?
}

bool16 CScriptEngine::IsScriptActive() const
{
	return fActiveScripts > 0 ;
}

void CScriptEngine::IncrementActiveScriptCount()
{
	++fActiveScripts ;

	// Release cached script providers so that their cached state won't reflect previous
	// ScriptRequestContext.
	Utils<IScriptUtils>()->ClearScriptProviders();
}

void CScriptEngine::DecrementActiveScriptCount()
{
	--fActiveScripts ;
	ASSERT_MSG( fActiveScripts >= 0, "Negative script active count" ) ;

	// Release cached script providers so that their state won't go stale
	Utils<IScriptUtils>()->ClearScriptProviders();
}

bool16 CScriptEngine::GetShowAlerts() const
{
	InterfacePtr<IScriptPreferences> scriptPrefs( this, UseDefaultIID() ) ;
	return ( scriptPrefs->GetInteractionLevel() != IScriptPreferences::kNeverInteract ) ;
}

bool16 CScriptEngine::GetShowDialogs() const
{
	InterfacePtr<IScriptPreferences> scriptPrefs( this, UseDefaultIID() ) ;
	return ( scriptPrefs->GetInteractionLevel() == IScriptPreferences::kInteractWithAll ) ;
}

void CScriptEngine::ResetScriptRequestData( IScriptRequestData* scriptRequestData ) const
{
	InterfacePtr<IScriptManager> scriptMgr( QueryScriptManager() ) ;
	scriptRequestData->SetRequestContext( GetRequestContext() ) ;		//init with the current request context
	scriptRequestData->SetErrorPolicy( scriptMgr->GetErrorPolicy() ) ;			//init with the client's error policy
	scriptRequestData->SetSetPropertiesOrderPolicy( scriptMgr->GetSetPropertiesOrderPolicy() ) ;	//init with the client's order policy
}
