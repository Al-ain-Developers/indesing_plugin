//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptCoreFunctor.h $
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
#ifndef __IScriptCoreFunctor__
#define __IScriptCoreFunctor__

#include "IPMUnknown.h"
#include "ScriptingID.h"
#include "RequestContext.h"

using namespace ScriptInfo ;

/**
	A functor represents a generic function object.
*/
class IScriptCoreFunctor : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTCOREFUNCTOR };

	/**
		Call during creation of the interface to store the request context for the function.
	*/
	virtual void SetRequestContext( const EngineContext& context ) = 0 ;

	/**
		Access to the request context for this function.
	*/
	virtual const EngineContext& GetRequestContext() const = 0 ;

	/**
		Check for equality with another functor.
	*/
	virtual bool16 IsEqual( const IScriptCoreFunctor* other ) const = 0 ;
};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("iscriptcorefunctor:indesign:adobe", IScriptCoreFunctor);

#endif
