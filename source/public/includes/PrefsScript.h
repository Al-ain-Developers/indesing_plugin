//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PrefsScript.h $
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
#ifndef __PrefsScript__
#define __PrefsScript__

#include "CProxyScript.h"

class PUBLIC_DECL PrefsScript : public CProxyScript
{
public:
	PrefsScript( IPMUnknown* boss ) ;
	~PrefsScript() ;

	virtual ScriptObject GetScriptObject( const RequestContext& context ) const ;
} ;

#endif
