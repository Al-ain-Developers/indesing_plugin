//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/startup scripts/ConvertFootnotesToEndnotesMenuItemLoader.jsx $
//  
//  Owner: 
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
//  Purpose: Load and run the ConvertFootnoteToEndnoteMenuItem script
//
//  The ConvertFootnoteToEndnoteMenuItem script needs to run in a persistent script engine.
//  Binary scripts can't switch to a specfic script engine. Thus we use this
//  uncompiled script to run the ConvertFootnoteToEndnoteMenuItem script in the proper
//  script engine.
//
//==============================================================================


#targetengine "ConvertFootnoteToEndnote"

//Set to true to enable DEBUG code
var DEBUG = false ;

function assert( condition, text ) { if ( DEBUG && !condition ) { alert( text ) ; } }


//Don't want to run twice
if (typeof(ConvertFootnoteToEndnoteMenuItem) == 'undefined')
{
	//------------------------------------------------------------------------------
	// ConvertFootnoteToEndnoteMenuItemLoader.constructor
	//------------------------------------------------------------------------------

	function ConvertFootnoteToEndnoteMenuItemLoader()
	{
	}

	//------------------------------------------------------------------------------
	// ConvertFootnoteToEndnoteMenuItemLoader.getScriptsFolderPath
	//------------------------------------------------------------------------------

	ConvertFootnoteToEndnoteMenuItemLoader.getScriptsFolderPath = function()
	{
        var script;
		try
		{
			script = app.activeScript;
		}
		catch(e)
		{
			// we are running from the ESTK
			script = File(e.fileName);
		}
		return script.parent.parent ;	//this file is in the "startup scripts" subfolder
	}


	//------------------------------------------------------------------------------
	// ConvertFootnoteToEndnoteMenuItemLoader.loadScript
	//------------------------------------------------------------------------------

	ConvertFootnoteToEndnoteMenuItemLoader.loadScript = function(filename)
	{
		return File(ConvertFootnoteToEndnoteMenuItemLoader.getScriptsFolderPath() + '/' + filename );
	}

	//------------------------------------------------------------------------------
	// main
	//------------------------------------------------------------------------------

	// load the script
	ConvertFootnoteToEndnoteMenuItemLoader.script = ConvertFootnoteToEndnoteMenuItemLoader.loadScript('ConvertFootnoteToEndnoteMenuItem.jsxbin');
	if ( !ConvertFootnoteToEndnoteMenuItemLoader.script.exists )
	{
		ConvertFootnoteToEndnoteMenuItemLoader.script = ConvertFootnoteToEndnoteMenuItemLoader.loadScript('ConvertFootnoteToEndnoteMenuItem.jsx');
	}
	// execute it
	assert( ConvertFootnoteToEndnoteMenuItemLoader.script.exists, "ConvertFootnoteToEndnoteMenuItem.jsx* missing; load failed" ) ;
	if ( ConvertFootnoteToEndnoteMenuItemLoader.script.exists )
	{
		var cacheCurrent = Folder.current ;
		try
		{
			Folder.current = ConvertFootnoteToEndnoteMenuItemLoader.getScriptsFolderPath();
			if(app.name == "Adobe InDesign" )
              {
                  app.doScript(ConvertFootnoteToEndnoteMenuItemLoader.script);
              }
		}
		finally
		{
			Folder.current = cacheCurrent ;
		}
	}
}
