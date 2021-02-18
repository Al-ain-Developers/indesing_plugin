//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIScriptingDefs.h $
//  
//  Owner: Adobe Developer Technologies
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
#ifndef _BPIScriptingDefs_h_
#define _BPIScriptingDefs_h_

// GUIDs for script objects

// {EEC6B2A5-B118-436b-B249-A4A68607E6A7}
#define kBPIPref_CLSID {0xeec6b2a5, 0xb118, 0x436b, {0xb2, 0x49, 0xa4, 0xa6, 0x86, 0x7, 0xe6, 0xa7} }

// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Object ScriptIDs
enum BPIScriptClasses
{
	c_BPIPref		= 'BPPR' // The BasicPersistInterface preferences object
};

// Property ScriptIDs
enum BPIScriptProperties
{
	p_BPIPref		= 'BPpr',
	p_BPIData		= 'BPda'
};

#endif  //_BPIScriptingDefs_h_

// End BPIScriptingDefs.h


