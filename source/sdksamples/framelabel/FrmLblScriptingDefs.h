//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblScriptingDefs.h $
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
#ifndef _FrmLblScriptingDefs_h_
#define _FrmLblScriptingDefs_h_

// GUIDs for script objects

// {D96E53DE-B6FB-43f5-96E2-5EE370522BAF}
#define kFrmLblPref_CLSID {0xd96e53de, 0xb6fb, 0x43f5, {0x96, 0xe2, 0x5e, 0xe3, 0x70, 0x52, 0x2b, 0xaf } }

// {D96E53DE-B6FB-43f5-96E2-5EE370522BB0}
#define kFrmLblPrintPref_CLSID {0xd96e53de, 0xb6fb, 0x43f5, {0x96, 0xe2, 0x5e, 0xe3, 0x70, 0x52, 0x2b, 0xb0 } }

// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Property ScriptIDs
enum FrmLblScriptProperties
{
	p_FrmLblString = 'FLst', 		// frame label string
    p_FrmLblSize = 'FLsz',			// frame label point size (in points)
    p_FrmLblVisibility = 'FLvi',	// frame label visibility
	p_FrmLblFontColor = 'FLfc',		// frame label color
	p_FrmLblPosition = 'FLrp',		// frame label position
	p_FrmLblPrintPref = 'FLpr',		// frame label print preference
	p_FrmLblPrint = 'FLpp',			// frame label print preference value
	p_FrmLblPref = 'FLdp'			// frame label preference

};

// Object ScriptIDs
enum FrmLblScriptClasses
{
	c_FrmLblPrintPref  = 'FLPF', 
	c_FrmLblPref = 'FLDP'
};

enum FrmLblScriptEnums
{
	en_FrmLblPosition = 'FLep',
	en_FrmLblLeft = 'FLel',
	en_FrmLblRight = 'FLer', 
	en_FrmLblTop = 'FLet',
	en_FrmLblBottom = 'FLeb'	
};

#endif  //_FrmLblScriptingDefs_h_

// End FrmLblScriptingDefs.h


