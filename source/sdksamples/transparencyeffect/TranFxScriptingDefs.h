//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxScriptingDefs.h $
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
#ifndef _TranFxScriptingDefs_h_
#define _TranFxScriptingDefs_h_

// {CC392421-6C6C-436d-87FD-84D33688285A}
#define kTranFxSettings_CLSID { 0xcc392421, 0x6c6c, 0x436d, { 0x87, 0xfd, 0x84, 0xd3, 0x36, 0x88, 0x28, 0x5a } }

// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Script object ScriptIDs 
enum CHDMScriptClasses
{
	c_TranFxSettings			= 'FXST' // The settings object
};
// Property ScriptIDs
// NB All these have been registered through partners.adobe.com to be sure
// that they are unique and don't clash with either application script IDs, or other third parties
// At time of writing (Jun 2005): 
// http://partners.adobe.com/public/developer/indesign/script/scriptid_reg.do
//
enum TranFxScriptProperties
{
	p_TranFxMode				= 'FXmd',
	p_TranFxOffsetX				= 'FXox',
	p_TranFxOffsetY				= 'FXoy',
	p_TranFxUseBlackAsOpaque	= 'FXbo',
	p_TranFxUseAlpha			= 'FXua',
	p_TranFxUseBlur				= 'FXub',
	p_TranFxSettings			= 'FXst' // Expose settings object as property

};



#endif  //_TranFxScriptingDefs_h_

// End TranFxScriptingDefs.h


