//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvScriptingDefs.h $
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
//  Defines Scripting IDs used by the PersistentList plug-in.
//  
//========================================================================================

#ifndef __PnlTrvScriptingDefs_h__
#define __PnlTrvScriptingDefs_h__


// GUIDS
//{E06AAC73-9A8D-47ca-B6FD-6A5A99934B9F}
#define kPnlTrvPreferences_CLSID { 0xe06aac73, 0x9a8d, 0x47ca, { 0xb6, 0xfd, 0x6a, 0x5a, 0x99, 0x93, 0x4b, 0x9f } }

/* ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.
*/
enum PnlTrvScriptingDefs
{
	c_PnlTrvPreferences = 'PTpo',	// The panel tree view preference object
	p_PnlTrvPreferences = 'PTpp'	// The panel tree view preference property
};

#endif // #ifndef __PnlTrvScriptingDefs_h__
