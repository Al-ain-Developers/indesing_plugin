//========================================================================================
//  
//  $File $
//  
//  Owner: Heath Lynn
//  
//  $Author $
//  
//  $DateTime $
//  
//  $Revision $
//  
//  $Change $
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
#ifndef _CustSEScriptingDefs_h_
#define _CustSEScriptingDefs_h_


// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Property ScriptIDs
enum CustSEScriptEvents
{
	// TODO ... Register these!
	e_ParaStyleListChangedEvent = 'psLC',
	e_CharStyleListChangedEvent = 'csLC',
	e_SpreadListChangedEvent = 'spLC',
	
};

#endif  //_CustSEScriptingDefs_h_

// End CustSEScriptingDefs.h

