//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelScriptingDefs.h $
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
//  
//  Defines Scripting IDs used by the PrnSel plug-in.
//  
//========================================================================================

#ifndef __PrnSelScriptingDefs_h__
#define __PrnSelScriptingDefs_h__

/*
//  IDs used by the PrintSelection plug-in for scripting purposes
*/

/* GUIDs for script objects
*/

// {A940C9EF-1AD6-41a2-9800-4BF9022BD01E}
#define kPrnSel_CLSID { 0xa940c9ef, 0x1ad6, 0x41a2, { 0x98, 0x0, 0x4b, 0xf9, 0x2, 0x2b, 0xd0, 0x1e } }

/* ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.
*/
enum PrnSelScriptingDefs
{
	// Script object ScriptIDs:
	c_PrintSelection = 'PSel',					// the print selection object
	// Property ScriptIDs:
	p_PrintSelectionProperty = 'PSep',			// the print selection property on the parent object
	p_PrintSelection = 'PSEL'					// the print selection property on this object
};

#endif // #ifndef __PrnSelScriptingDefs_h__
