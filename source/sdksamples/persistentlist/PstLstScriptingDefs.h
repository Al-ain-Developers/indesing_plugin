//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstScriptingDefs.h $
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

#ifndef __PstLstScriptingDefs_h__
#define __PstLstScriptingDefs_h__

/*
//  IDs used by the PersistentList plug-in for scripting purposes
*/

/* GUIDs for script objects
*/
// {D8DDA94E-F65A-483e-B181-4B12F4665280}
#define kPstLstDataItem_CLSID { 0xd8dda94e, 0xf65a, 0x483e, { 0xb1, 0x81, 0x4b, 0x12, 0xf4, 0x66, 0x52, 0x80 } }

// {83483B5D-461D-4b76-AFBF-4B91C2B2BD4E}
#define kPstLstDataItems_CLSID { 0x83483b5d, 0x461d, 0x4b76, { 0xaf, 0xbf, 0x4b, 0x91, 0xc2, 0xb2, 0xbd, 0x4e } }


/* ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.
*/
enum PstLstScriptingDefs
{
	// Suite ScriptIDs
	s_PstLstSuite = 'PLSu',		// The persistent list suite
	// Script object ScriptIDs 
	c_PstLstDataItem = 'PLIt',	// The persistent list object
	c_PstLstDataItems = 'PLIT'	// The persistent list object collection
};

#endif // #ifndef __PstLstScriptingDefs_h__
