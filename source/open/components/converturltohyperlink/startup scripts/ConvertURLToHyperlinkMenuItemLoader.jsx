//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/startup scripts/ConvertURLToHyperlinkMenuItemLoader.jsx $
//  
//  Owner: Saurabh Deshpande
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
//  Purpose: Load and run the ConvertURLToHyperlink Menu Item script
//
//  The ConvertURLToHyperlink Menu Item script needs to run in a persistent script engine.
//  Binary scripts can't switch to a specfic script engine. Thus we use this
//  uncompiled script to run the ConvertURLToHyperlink Menu Item script in the proper
//  script engine.
//
//==============================================================================


#targetengine "ConvertURLToHyperlinks"

//Set to true to enable DEBUG code
var DEBUG = false ;

function assert( condition, text ) { if ( DEBUG && !condition ) { alert( text ) ; } }

//Don't want to run twice
if (typeof(ConvertURLToHyperlinkMenuItem) == 'undefined')
{
	//------------------------------------------------------------------------------
	// ConvertURLToHyperlinkMenuItemLoader.constructor
	//------------------------------------------------------------------------------

	function ConvertURLToHyperlinkMenuItemLoader()
	{
	}

	//------------------------------------------------------------------------------
	// ConvertURLToHyperlinkMenuItemLoader.getScriptsFolderPath
	//------------------------------------------------------------------------------

	ConvertURLToHyperlinkMenuItemLoader.getScriptsFolderPath = function()
	{
		try
		{
			var script = app.activeScript;
		}
		catch(e)
		{
			// we are running from the ESTK
			var script = File(e.fileName);
		}
		return script.parent.parent ;	//this file is in the "startup scripts" subfolder
	}


	//------------------------------------------------------------------------------
	// ConvertURLToHyperlinkMenuItemLoader.loadScript
	//------------------------------------------------------------------------------

	ConvertURLToHyperlinkMenuItemLoader.loadScript = function(filename)
	{
		return File(ConvertURLToHyperlinkMenuItemLoader.getScriptsFolderPath() + '/' + filename );
	}

	//------------------------------------------------------------------------------
	// main
	//------------------------------------------------------------------------------

	// load the script
	ConvertURLToHyperlinkMenuItemLoader.script = ConvertURLToHyperlinkMenuItemLoader.loadScript('ConvertURLToHyperlinkMenuItem.jsxbin');
	if ( !ConvertURLToHyperlinkMenuItemLoader.script.exists )
	{
		ConvertURLToHyperlinkMenuItemLoader.script = ConvertURLToHyperlinkMenuItemLoader.loadScript('ConvertURLToHyperlinkMenuItem.jsx');
	}
	// execute it
	assert( ConvertURLToHyperlinkMenuItemLoader.script.exists, "ConvertURLToHyperlinkMenuItem.jsx* missing; load failed" ) ;
	if ( ConvertURLToHyperlinkMenuItemLoader.script.exists )
	{
		var cacheCurrent = Folder.current ;
		try
		{
			Folder.current = ConvertURLToHyperlinkMenuItemLoader.getScriptsFolderPath();
			app.doScript(ConvertURLToHyperlinkMenuItemLoader.script);
		}
		finally
		{
			Folder.current = cacheCurrent ;
		}
	}
}
