//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapScriptingDefs.h $
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
#ifndef _SnapScriptingDefs_h_
#define _SnapScriptingDefs_h_

// GUIDs for script objects

// {4D160E2A-CA5C-4CB8-998F-6A37D2E1F356}
#define kSnapPref_CLSID {0x4D160E2A, 0xCA5C, 0x4CB8, {0x99, 0x8F, 0x6A, 0x37, 0xD2, 0xE1, 0xF3, 0x56} }

// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Script Object ScriptIDs
enum SnapScriptClasses
{
	c_SnapPref		= 'SNPR' // The SnapShot preferences object
};

// Property ScriptIDs
enum SnapScriptProperties
{
	p_SnapPref						= 'SNpr',
	p_SnapFileName					= 'SNfn',
	p_SnapImageFormat				= 'SNif',
	p_SnapScale						= 'SNsl',
	p_SnapResolution				= 'SNrs',
	p_SnapMinimumResolution			= 'SNmr',
	p_SnapBleed						= 'SNbd',
	p_SnapDrawArea					= 'SNda',
	p_SnapFullResolutionGraphics	= 'SNfr',
	p_SnapDrawGray					= 'SNdg',
	p_SnapDrawingFlags				= 'SNdf',
	p_SnapJPEGEncoding				= 'SNje',
	p_SnapJPEGQuality				= 'SNjq',
	p_SnapTIFFPaletteType			= 'SNtt',
	p_SnapGIFPaletteType			= 'SNgt',
	p_SnapTIFFTransparent			= 'SNtp',
	p_SnapGIFTransparent			= 'SNgp',
	p_SnapGIFInterlaced				= 'SNgi',
	en_SnapImgeWriteFormat			= 'SEif',
	en_SnapExPNG					= 'SEpn',
	en_SnapExGIF					= 'SEgf',
	en_SnapExSCT					= 'SEst',
	en_SnapExTIFF					= 'SEtf',
	en_SnapExJPEG					= 'SEjg',
	en_SnapTool						= 'snTl'
};

#endif  //_SnapScriptingDefs_h_

// End SnapScriptingDefs.h


