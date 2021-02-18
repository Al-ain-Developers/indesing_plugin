//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptMutationData.h $
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
#ifndef __IScriptMutationData__
#define __IScriptMutationData__

#include "IScriptEvent.h"
#include "IScriptEventTarget.h"

#include "ScriptReturnData.h"

using namespace ScriptInfo ;

/**
	An interface used by the kMutationScriptEventBoss to store associated data.
*/  
class IScriptMutationData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTMUTATIONDATA };

	/** Set the attribute that changed
	*/
	virtual void SetAttribute( ScriptID propID ) = 0 ;

	/** Get the attribute that changed
	*/
	virtual ScriptID GetAttribute() const = 0 ;

	/** Return the name of the attribute formatted for the appropriate client context
	*/
	virtual PMString GetAttributeName( IScript* target, const EngineContext& context ) const = 0 ;

	/** Return the value of the attribute formatted for the appropriate client context
	*/
	virtual ScriptReturnData GetAttributeValue( IScript* target, const EngineContext& context ) const = 0 ;

	/** A standard event initializer callback for mutation events. See @IScriptEventTarget.h. The code 
		to dispatch the MutationEvent for a change in the name of an object might look like this:

			ScriptID propID = p_Name ;
			InterfacePtr<IScriptEventTarget> target( iScript, UseDefaultIID() ) ;
			if ( target )
				target->DispatchScriptEvent( kAfterAttributeChangedEventScriptElement, 
					&IScriptMutationData::InitMutationEventCallback, &propID ) ; 
	*/
	static void InitMutationEventCallback( IScriptEvent* e, IScriptEventTarget::InitCallbackType t, void* privateData )
	{
		const ScriptID* propID = (ScriptID*) privateData ;
		ASSERT( propID ) ;
		InterfacePtr<IScriptMutationData> mutationData( e, UseDefaultIID() ) ;
		ASSERT( mutationData ) ;
		if ( t == IScriptEventTarget::kPreDispatch )
		{
			mutationData->SetAttribute( *propID ) ;
		}
		else if ( t == IScriptEventTarget::kPostDispatch )
		{
		}
	}

};

#endif
