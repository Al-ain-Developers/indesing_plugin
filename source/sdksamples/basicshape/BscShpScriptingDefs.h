//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpScriptingDefs.h $
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
#ifndef _BscShpScriptingDefs_h_
#define _BscShpScriptingDefs_h_


// GUIDs for script objects:

// {576252F1-187A-4b95-ABB4-21160B20CBD0}
#define kBscShpBasicShapeObject_CLSID {0x576252f1, 0x187a, 0x4b95, {0xab, 0xb4, 0x21, 0x16, 0xb, 0x20, 0xcb, 0xd0} }
// {ECEAB454-4E99-4142-BFEB-943DE788C213}
#define kBscShpBasicShapesObject_CLSID {0xeceab454, 0x4e99, 0x4142,  {0xbf, 0xeb, 0x94, 0x3d, 0xe7, 0x88, 0xc2, 0x13} }

// ScriptIDs:
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Object ScriptIDs:
enum BscShpScriptClasses
{
	c_BasicShape		= 'BASH', // The basic shape script object (See kBasicShapeObjectScriptElement in BscShp.fr)
	c_BasicShapes		= 'BASC'  // Collection of basic shape script objects.
};

enum BscShpScriptProperties
{
    p_TextBasicShape     =   'pTBS'
};
#endif  //_BscShpScriptingDefs_h_

// End BscShpScriptingDefs.h


