//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunScriptingDefs.h $
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
//  Defines Scripting IDs used by the SnipRun plug-in.
//  
//========================================================================================

#ifndef __SnipRunScriptingDefs_h__
#define __SnipRunScriptingDefs_h__


// Suite ScriptIDs
enum SnipRunScriptSuites
{
	s_SnipRunSuite = 'SRSU'	// The snippet runner suite
};

/*
// SnippetRunner IDs
*/

// GUID for kSnipRunObjectScriptElement script object (only one GUID needed cause it's a singlteton)
// {6EB7D3B3-64A0-4319-900A-ED1103671EC1}
#define kSnipRun_CLSID { 0x6eb7d3b3, 0x64a0, 0x4319, { 0x90, 0xa, 0xed, 0x11, 0x3, 0x67, 0x1e, 0xc1 } }

// ScriptIDs
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Class ScriptIDs 
enum SnipRunScriptClasses
{
	c_SnipRun =						'SRSR'	// The snippet runner object
};

// Event ScriptIDs 
enum SnipRunScriptEvents
{
	e_SnipRunIsSnippetRegistered =	'SRir',	// is snippet registered
	e_SnipRunGetSnipLog = 			'SRgl',	// get sniplog text
	e_SnipRunClearSnipLog = 		'SRcl',	// clear sniplog
	e_SnipRunSaveSnipLog = 			'SRsl'	// save sniplog to file
};
  // Property ScriptIDs
enum SnipRunScriptProperties
{
	p_SnipRun =						'SRob',	// The snippet runner object property to hang off of Application
	p_SnipRunPanelVisibility = 		'SRpv',	// snippet runner panel visibility
	p_SnipRunTraceMode = 			'SRtM'	// snippet runner trace mode (you can set it on in debug build only)
};
// Parameter ScriptIDs
enum SnipRunScriptParameters
{
	p_SnipRunSnippetToCheck = 		'SRtc'	// snippet to check
};
// Enum ScriptIDs
enum SnipRunScriptEnums
{
	en_SnipRunPanelVisibility = 	'SRvi',	// visibiilty enums
	en_SnipRunPanelVisible =		'SRvs',
	en_SnipRunPanelInvisible =		'SRin',
	en_SnipRunTraceMode	=			'SRtm',	// trace mode enums
	en_SnipRunTraceOn =				'SRtn',
	en_SnipRunTraceOff =			'SRtF'
};

/*
// Snippet IDs
*/

// GUIDs kSnpRunnableObjectScriptElement script object (two GUIDs needed cause it has a collection)
// {F10D1BE5-6222-4c54-BCED-65785166B897}
#define kSnpRunnable_CLSID { 0xf10d1be5, 0x6222, 0x4c54, { 0xbc, 0xed, 0x65, 0x78, 0x51, 0x66, 0xb8, 0x97 } }

// {9FD5648B-0308-4e11-8FF8-F4E123D7CCC2}
#define kSnpRunnables_CLSID { 0x9fd5648b, 0x308, 0x4e11, { 0x8f, 0xf8, 0xf4, 0xe1, 0x23, 0xd7, 0xcc, 0xc2 } }

// ScriptIDs

// Class ScriptIDs
enum SnpRunnableScriptClasses
{
	c_SnpRunnable =					'SRrN',	// The SnpRunnable object (a snippet)
	c_SnpRunnables =				'SRRn'	// The SnpRunnables object (plural)
};
// Event ScriptIDs
enum SnpRunnableScriptEvents
{
	e_SnpRunnableCanRunSnippet = 	'SRcr',	// can snippet be run?
	e_SnpRunnableRunSnippet =		'SRrs',	// run snippet
	e_SnpRunnableSetupContext =		'SRsc'	// set up the snippet context in order to run
};
// Property ScriptIDs
enum SnpRunnableScriptProperties
{
	p_SnpRunnableName = 			'SRna',	// snippet name (string)
	p_SnpRunnableDescription = 		'SRde',	// snippet description (string)
	p_SnpRunnablePreconditions =	'SRpr',	// snippet preconditions (string)
	p_SnpRunnableCategories =		'SRca'	// snippet categories (array of strings)
};
// Parameter ScriptIDs
enum SnpRunnableScriptParameters
{
	p_SnpRunnableEnableParameterDialog =	'SRep',	// snippet run: enable parameter dialogs
	p_SnpRunnableParameters	= 				'SRpa'	// snippet run: parameters
};
#endif // #ifndef __SnipRunScriptingDefs_h__
