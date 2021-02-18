//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/ConvertFootnoteToEndnoteMenuItem.jsx $
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
//  
//  Purpose: 
//  
//========================================================================================

function ConvertFootnoteToEndnoteMenuItem() {
}

// this object requires a certain version of the scripting DOM
ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion = 14.0;

ConvertFootnoteToEndnoteMenuItem.contextmenu = app.menus.item(app.translateKeyString('$ID/RtMouseText'));

ConvertFootnoteToEndnoteMenuItem.objendnotefootnote = null;

//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.loadScript
// Loads a script file from the install location
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.loadScript = function(filename)
{
	return File(ConvertFootnoteToEndnoteMenuItem.scriptsFolder + '/' + filename );
}


//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.onContextMenuInvoke
// This function handles context menu conversion cases.
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.onContextMenuInvoke = function() {

    if (app.documents.count() > 0)
	{
        // Addition of localization code  
        ConvertFootnoteToEndnoteMenuItem.localizeStrings();
        ConvertFootnoteToEndnoteMenuItem.cleanContextMenu();
        var menutemp = ConvertFootnoteToEndnoteMenuItem.contextmenu;
        var menuref = menutemp.menuElements.previousItem(menutemp.menuElements.item(localize(footnoteToEndnoteStrings.CONTEXT_MENU_LOCATION)));
        
        if( (app.documents.length >0) && (app.selection.length>0) && ((app.selection[0].constructor.name == "Text") || (app.selection[0].constructor.name == "InsertionPoint") 
        || (app.selection[0].constructor.name == "Word") || (app.selection[0].constructor.name == "Paragraph") 
        || (app.selection[0].constructor.name == "TextColumn") || (app.selection[0].constructor.name == "Character")) 
        && (app.selection[0].parent.constructor.name == "Story") && (app.selection[0].parent.isEndnoteStory) )
        {
            var mactionName;
            if(app.selection[0].endnoteRanges.length>1)
            {
                mactionName = localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES);
            }
            else
            {
                mactionName = localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE);
            }
              
            var maction = app.scriptMenuActions.add(mactionName);
            var myEventListener = maction.addEventListener("onInvoke", ConvertFootnoteToEndnoteMenuItem.context_endnote_to_footnote ,false);

                             
            if((app.selection[0].endnoteRanges.length>1) && (menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES) ) == null ))
            {
                ConvertFootnoteToEndnoteMenuItem.contextmenu.menuItems.add(maction,LocationOptions.before, menuref);
            }
            else if(menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE)) == null )
            {
                ConvertFootnoteToEndnoteMenuItem.contextmenu.menuItems.add(maction,LocationOptions.before, menuref);
            }
                
        }
        else if ((app.documents.length >0) && (app.selection.length>0) && (app.selection[0].parent.constructor.name == "Footnote") && ((app.selection[0].constructor.name == "Text") || (app.selection[0].constructor.name == "InsertionPoint") || (app.selection[0].constructor.name == "Word") || (app.selection[0].constructor.name == "Paragraph") || (app.selection[0].constructor.name == "Character"))  )
        {  
            // Addition of localization code
            var mactionName = localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE);
            var maction = app.scriptMenuActions.add(mactionName);
            var myEventListener = maction.addEventListener("onInvoke", ConvertFootnoteToEndnoteMenuItem.context_footnote_to_endnote,false);
            if(menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE)) == null )
            {
                ConvertFootnoteToEndnoteMenuItem.contextmenu.menuItems.add(maction,LocationOptions.before, menuref);
        
		/*case 'TextStyleRange':
		case 'Line':
		case 'TextColumn':
		case 'Story':
		case 'TextFrame':
        case 'TextPath':*/
            }            
        }

	}
	else
	{
		assert( false, localize(footnoteToEndnoteStrings.NO_ACTIVE_DOC_ERROR)) ;	
	}
    
	return true;
}

//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.context_footnote_to_endnote
//This function is mainly created for UNDO support of footnote conversion.
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.context_footnote_to_endnote = function(){
    
    app.doScript('ConvertFootnoteToEndnoteMenuItem.objendnotefootnote.do_context_footnote_to_endnote()', undefined, undefined, UndoModes.entireScript);
}

//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.context_footnote_to_endnote
//This function is mainly created for UNDO support of endnote conversion.
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.context_endnote_to_footnote = function(){
    
    app.doScript('ConvertFootnoteToEndnoteMenuItem.objendnotefootnote.do_context_endnote_to_footnote()', undefined, undefined, UndoModes.entireScript);
}


//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.cleanContextMenu
// This clears all older menu entry for conversion.
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.cleanContextMenu = function() 
{
    var menutemp = ConvertFootnoteToEndnoteMenuItem.contextmenu;

    //Check for exsisting context menu entry.
    if(menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE)) != null )
    {
        menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE)).remove();
    }

    //Check for exsisting context menu entry.
    if(menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES)) != null )
    {
        menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES)).remove();
    }

    if(menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE)) != null )
    {
        menutemp.menuItems.itemByName(localize(footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE)).remove();
    }

}



//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.onMenuItemInvoke
// Invoke dialog for conversion via type menu.
//------------------------------------------------------------------------------

var obj = null;
ConvertFootnoteToEndnoteMenuItem.onMenuItemInvoke = function() 
{
	if ((obj != null) && (obj.dialogOpen == true))
		return;
	if (app.documents.count() > 0)
	{
        obj = ConvertFootnoteToEndnoteMenuItem.objendnotefootnote ;
		obj.RunDialog();
	}
	else
	{
		assert( false, localize(footnoteToEndnoteStrings.NO_ACTIVE_DOC_ERROR)) ;	
	}
	return true;
}


//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.enableDisable
// Handles enablement/disablement of the menu action
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.enableDisable = function()
{
	try 
    {
		// set up our script preferences
		var currDOMVersion = app.scriptPreferences.version;
		if(currDOMVersion != ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion) {
			app.scriptPreferences.version = ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion;
		}
		
		ConvertFootnoteToEndnoteMenuItem.action.enabled = (app.documents.length > 0);
		
		if(currDOMVersion != ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion) {
			app.scriptPreferences.version = currDOMVersion;
		}
	}
	catch (x) 
    {
		assert(false, x);
	}
}

//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.storeScriptsFolderPath
// Stores path of script
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.storeScriptsFolderPath = function()
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
	ConvertFootnoteToEndnoteMenuItem.scriptsFolder = script.parent;	//this file is in the ConvertFootnoteToEndnote folder and is executed via doScript
}


//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.localizeStrings
// This is for enabling localized strings inside dialog and menus.
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.localizeStrings = function() 
{
   var cacheCurrent;
   try
    {
        if ($.locale != 'en_US')
        {
            // try to load localized strings
            var localizationScript = ConvertFootnoteToEndnoteMenuItem.loadScript('Resources/FootnoteToEndnoteStrings-' + $.locale + '.jsxbin');
            if ( !localizationScript.exists )
            {
                localizationScript = ConvertFootnoteToEndnoteMenuItem.loadScript('Resources/FootnoteToEndnoteStrings-' + $.locale + '.jsx');
            }
    
            if ( localizationScript.exists )
            {
                cacheCurrent = Folder.current ;
                Folder.current = Folder( ConvertFootnoteToEndnoteMenuItem.scriptsFolder + '/Resources' ) ;
                app.doScript( localizationScript ) ;
            }
            
            Folder.current = cacheCurrent ;
        }
        
    }
    catch (x) 
    {
        assert(false,x + 'Alert : Unable to localize');
    }
}



//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.install
// install our menu items and event listeners, so that conversion can be triggered
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.install = function()
{

	try 
	{

        if(app.name == "Adobe InDesign" ) 
        {
            // set up our script preferences
            var currDOMVersion = app.scriptPreferences.version;
            if (currDOMVersion != ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion)
                app.scriptPreferences.version = ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion;

            // determine and store the path from were we load our scripts from
            ConvertFootnoteToEndnoteMenuItem.storeScriptsFolderPath();

            var ConvertFootnoteToEndnoteScript = ConvertFootnoteToEndnoteMenuItem.loadScript('ConvertFootnoteToEndnote.jsxbin');
            if ( !ConvertFootnoteToEndnoteScript.exists )
            {
                ConvertFootnoteToEndnoteScript = ConvertFootnoteToEndnoteMenuItem.loadScript('ConvertFootnoteToEndnote.jsx');
            }
		
            //  assert( ConvertFootnoteToEndnoteScript.exists, "ConvertFootnoteToEndnote.jsx* missing; load failed" ) ;
            if ( ConvertFootnoteToEndnoteScript.exists )
            {
                var cacheCurrent = Folder.current ;
                Folder.current = ConvertFootnoteToEndnoteMenuItem.scriptsFolder ;
                app.doScript( ConvertFootnoteToEndnoteScript ) ;
                ConvertFootnoteToEndnoteMenuItem.objendnotefootnote = new ConvertFootnoteToEndnote();

                Folder.current = cacheCurrent ;
                ConvertFootnoteToEndnoteMenuItem.localizeStrings();
                
                var contextmenulistener = ConvertFootnoteToEndnoteMenuItem.contextmenu.addEventListener("beforeDisplay",ConvertFootnoteToEndnoteMenuItem.onContextMenuInvoke,false);
                                
				// menu action for the File menu
				var actionname = localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE_ACTION_NAME );
				var footnotetoendnoteAction = app.scriptMenuActions.item(actionname);
				if(footnotetoendnoteAction == null) 
                {
					// first launch:
					// we need to create the menu action
					footnotetoendnoteAction = app.scriptMenuActions.add(actionname);
					footnotetoendnoteAction.area = app.translateKeyString('$ID/KBSCE Type menu');
					footnotetoendnoteAction.checked = false;
					footnotetoendnoteAction.enabled = true;
				}

				// install event listeners for our action
				footnotetoendnoteAction.addEventListener("onInvoke", ConvertFootnoteToEndnoteMenuItem.onMenuItemInvoke);	
				footnotetoendnoteAction.addEventListener("beforeDisplay", ConvertFootnoteToEndnoteMenuItem.enableDisable);

				// store the action in a class variable
				ConvertFootnoteToEndnoteMenuItem.action = footnotetoendnoteAction;

                //Need to check translations for these
				var filemenu = app.menus.item(app.translateKeyString('$ID/Main')).submenus.item(app.translateKeyString('$ID/&Type')) ;

                //This can further be changed based on more inputs.  
                if( ! filemenu.menuItems.itemByName(actionname).isValid )
                {
                    var menu_location = localize(footnoteToEndnoteStrings.MAIN_MENU_LOCATION);
                    filemenu.menuItems.add(footnotetoendnoteAction,LocationOptions.after,filemenu.menuElements.item(menu_location)); 
                }
                  
                  
			}
			
		}
    }
    catch (x) 
    {
		assert(false, 'Alert : Cannot install ConvertFootnoteToEndnote and unable to create menus');
	}
	
    try 
	{
		if(currDOMVersion != ConvertFootnoteToEndnoteMenuItem.requiredDOMVersion)
			app.scriptPreferences.version = currDOMVersion;
	}
	catch (x) 
    {
		assert(false, x);
	}
	
}

//------------------------------------------------------------------------------
// ConvertFootnoteToEndnoteMenuItem.install
// install our menu item and event listeners
//------------------------------------------------------------------------------

ConvertFootnoteToEndnoteMenuItem.install();	