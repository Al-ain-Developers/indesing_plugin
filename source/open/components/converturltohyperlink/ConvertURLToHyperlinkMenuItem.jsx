//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/ConvertURLToHyperlinkMenuItem.jsx $
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
//  
//  Purpose: Load and run the ConvertURLToHyperlink Menu Item script
//  
//  The ConvertURLToHyperlink Menu Item script needs to run in a persistent script engine.
//  Binary scripts can't switch to a specfic script engine. Thus we use this
//  uncompiled script to run the ConvertURLToHyperlink Menu Item script in the proper
//  script engine.
//  
//========================================================================================

function ConvertURLToHyperlinkMenuItem() {
}

// this object requires a certain version of the scripting DOM
ConvertURLToHyperlinkMenuItem.requiredDOMVersion = 6.0;


ConvertURLToHyperlinkMenuItem.storeScriptsFolderPath = function()
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
	ConvertURLToHyperlinkMenuItem.scriptsFolder = script.parent;	//this file is in the ConvertURLToHyperlink folder and is executed via doScript
}


//------------------------------------------------------------------------------
// ConvertURLToHyperlinkMenuItem.loadScript
// Loads a script file from the install location
//------------------------------------------------------------------------------

ConvertURLToHyperlinkMenuItem.loadScript = function(filename)
{
	return File(ConvertURLToHyperlinkMenuItem.scriptsFolder + '/' + filename );
}

var obj = null;
ConvertURLToHyperlinkMenuItem.onMenuItemInvoke = function() {
	if ((obj != null) && (obj.dialogOpen == true))
		return;
	if (app.documents.count() > 0)
	{
		// try to load localized strings 
		if ($.locale != 'en_US') 
		{ 
			script = ConvertURLToHyperlinkMenuItem.loadScript('Resources/URLToHyperlinkStrings-' + $.locale + '.jsxbin'); 
			if ( !script.exists )
			{
				script = ConvertURLToHyperlinkMenuItem.loadScript('Resources/URLToHyperlinkStrings-' + $.locale + '.jsx'); 
			}
			assert( script.exists, 'Resources/URLToHyperlinkStrings-' + $.locale + '.jsx* missing; load failed' ) ; 
			if ( script.exists ) 
			{
				var cacheCurrent = Folder.current ; 
				try 
				{ 
					Folder.current = Folder( ConvertURLToHyperlinkMenuItem.scriptsFolder + '/Resources' ) ; 
					app.doScript( script ) ; 
				}
				catch (x) {
					assert(false, x);
				}
				finally 
				{ 
					Folder.current = cacheCurrent ; 
				} 
			} 
		} 

		// load the script
		ConvertURLToHyperlinkMenuItem.script = ConvertURLToHyperlinkMenuItem.loadScript('ConvertURLToHyperlink.jsxbin');
		if ( !ConvertURLToHyperlinkMenuItem.script.exists )
		{
			ConvertURLToHyperlinkMenuItem.script = ConvertURLToHyperlinkMenuItem.loadScript('ConvertURLToHyperlink.jsx');
		}
		// execute it
		assert( ConvertURLToHyperlinkMenuItem.script.exists, "ConvertURLToHyperlink.jsx* missing; load failed" ) ;
		if ( ConvertURLToHyperlinkMenuItem.script.exists )
		{
			var cacheCurrent = Folder.current ;
			try
			{
				Folder.current = ConvertURLToHyperlinkMenuItem.scriptsFolder;
				app.doScript(ConvertURLToHyperlinkMenuItem.script);
				obj = new ConvertURLToHyperlink();
				obj.RunDialog();
			}
			catch (x) {
				assert(false, x);
			}
			finally
			{
				Folder.current = cacheCurrent ;
			}
		}
	}
	else
	{
		assert( false, localize(urlToHyperlinkStrings.NOACTIVEDOCERROR)) ;	
	}
	return true;
}


//------------------------------------------------------------------------------
// ConvertURLToHyperlinkMenuItem.enableDisable
// Handles enablement/disablement of the menu action
//------------------------------------------------------------------------------

ConvertURLToHyperlinkMenuItem.enableDisable = function()
{
	try {
		// set up our script preferences
		var currDOMVersion = app.scriptPreferences.version;
		if(currDOMVersion != ConvertURLToHyperlinkMenuItem.requiredDOMVersion) {
			app.scriptPreferences.version = ConvertURLToHyperlinkMenuItem.requiredDOMVersion;
		}
		
		ConvertURLToHyperlinkMenuItem.action.enabled = (app.documents.length > 0);
		
		if(currDOMVersion != ConvertURLToHyperlinkMenuItem.requiredDOMVersion) {
			app.scriptPreferences.version = currDOMVersion;
		}
	}
	catch (x) {
		assert(false, x);
	}
}

//------------------------------------------------------------------------------
// ConvertURLToHyperlinkMenuItem.install
// Creates the menu action and installs its event handlers and menu item
//------------------------------------------------------------------------------

ConvertURLToHyperlinkMenuItem.storeScriptsFolderPath = function()
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
	ConvertURLToHyperlinkMenuItem.scriptsFolder = script.parent;	//this file is in the ConvertURLToHyperlink folder and is executed via doScript
}

ConvertURLToHyperlinkMenuItem.install = function()
{
	try {
		// This is a hack to check if the Hyperlinks Panel plugin exists in the application across all locales.
		// We do that by checking if the HyperlinkPanelActionID is defined.
		if(!app.menuActions.itemByID(0x13600 + 1).isValid)
			return;
		} catch (x) {
			assert(false, x);
		}

	if(app.name == "Adobe InDesign" || app.name == "Adobe InCopy") {
		// set up our script preferences
		var currDOMVersion = app.scriptPreferences.version;
		if (currDOMVersion != ConvertURLToHyperlinkMenuItem.requiredDOMVersion)
			app.scriptPreferences.version = ConvertURLToHyperlinkMenuItem.requiredDOMVersion;

		// determine and store the path from were we load our scripts from
		ConvertURLToHyperlinkMenuItem.storeScriptsFolderPath();

		var ConvertURLToHyperlinkScript = ConvertURLToHyperlinkMenuItem.loadScript('ConvertURLToHyperlink.jsxbin');
		if ( !ConvertURLToHyperlinkScript.exists )
		{
			ConvertURLToHyperlinkScript = ConvertURLToHyperlinkMenuItem.loadScript('ConvertURLToHyperlink.jsx');
		}
		assert( ConvertURLToHyperlinkScript.exists, "ConvertURLToHyperlink.jsx* missing; load failed" ) ;
		if ( ConvertURLToHyperlinkScript.exists )
		{
			var cacheCurrent = Folder.current ;
			try
			{
				Folder.current = ConvertURLToHyperlinkMenuItem.scriptsFolder ;
				app.doScript( ConvertURLToHyperlinkScript ) ;
			}
			catch (x) {
					assert(false, x);
			}
			finally
			{
				Folder.current = cacheCurrent ;
			}
			if ($.locale != 'en_US')
			{
				// try to load localized strings
				var localizationScript = ConvertURLToHyperlinkMenuItem.loadScript('Resources/URLToHyperlinkStrings-' + $.locale + '.jsxbin');
				if ( !localizationScript.exists )
				{
					localizationScript = ConvertURLToHyperlinkMenuItem.loadScript('Resources/URLToHyperlinkStrings-' + $.locale + '.jsx');
				}
				assert( localizationScript.exists, 'Resources/URLToHyperlinkStrings-' + $.locale + '.jsx* missing; load failed' ) ;
				if ( localizationScript.exists )
				{
					var cacheCurrent = Folder.current ;
					try
					{
						Folder.current = Folder( ConvertURLToHyperlinkMenuItem.scriptsFolder + '/Resources' ) ;
						app.doScript( localizationScript ) ;
					}
					catch (x) {
						assert(false, x);
					}
					finally
					{
						Folder.current = cacheCurrent ;
					}
				}
			}
		
			try 
			{
				// menu action for the File menu
				var actionname = localize(urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME );
				var uRLToHyperlinkAction = app.scriptMenuActions.item(actionname);
				if(uRLToHyperlinkAction == null) {
					// first launch:
					// we need to create the menu action
					uRLToHyperlinkAction = app.scriptMenuActions.add(actionname);
					uRLToHyperlinkAction.area = app.translateKeyString('$ID/KBSCE Type menu');
					uRLToHyperlinkAction.checked = false;
					uRLToHyperlinkAction.enabled = true;
				}

				// install event listeners for our action
				uRLToHyperlinkAction.addEventListener("onInvoke", ConvertURLToHyperlinkMenuItem.onMenuItemInvoke);	
				uRLToHyperlinkAction.addEventListener("beforeDisplay", ConvertURLToHyperlinkMenuItem.enableDisable);
	//			action.addEventListener("afterInvoke", ConvertURLToHyperlinkMenuItem.cleanup);

				// store the action in a class variable
				ConvertURLToHyperlinkMenuItem.action = uRLToHyperlinkAction;

				var filemenu = app.menus.item(app.translateKeyString('$ID/Main')).submenus.item(app.translateKeyString('$ID/&Type')) ;
				var hyperlinksMenu = filemenu.submenus.item(app.translateKeyString('$ID/XRefSubMenu'));
				
				hyperlinksMenu.menuItems.add(uRLToHyperlinkAction, LocationOptions.AFTER, hyperlinksMenu.menuItems.item(app.translateKeyString('$ID/Create hyperlink to selected URL')));
				
				var flyoutMenu = app.menus.itemByName(app.translateKeyString('$ID/HyperlinkPanelPopup'));
				flyoutMenu.menuItems.add(uRLToHyperlinkAction, LocationOptions.AFTER, flyoutMenu.menuItems.item(app.translateKeyString('$ID/Create hyperlink to selected URL')));
			}
			catch (x) {
				assert(false, 'Alert : Cannot install ConvertURLToHyperlink');
			}
		}
		try 
		{
			if(currDOMVersion != ConvertURLToHyperlinkMenuItem.requiredDOMVersion)
				app.scriptPreferences.version = currDOMVersion;
		}
		catch (x) {
			assert(false, x);
		}
	}
}

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------

ConvertURLToHyperlinkMenuItem.install();	// install our menu item and event listeners