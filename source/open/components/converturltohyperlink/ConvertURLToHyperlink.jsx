//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/ConvertURLToHyperlink.jsx $
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
//  Purpose: 
//  
//========================================================================================

#include "includes/URLToHyperlinkStrings.jsx"
#include "includes/URLToHyperlinkStrings-en_US.jsx"
#include "ConvertURLToHyperlinkDialog.jsx"

function ConvertURLToHyperlink() {
}

ConvertURLToHyperlink.prototype.InitData = function() {
	try {
		this.myFoundItems = null;
		this.currentFoundItem;
		this.currentSelectionObjectIndex;
          
          // Create regular expressions for searching URL
          this.CreateURLRegExp(); 
  	   
         app.findGrepPreferences = NothingEnum.nothing;
		app.findChangeGrepOptions.includeFootnotes = true;
		app.findChangeGrepOptions.includeHiddenLayers = true;
		app.findChangeGrepOptions.includeLockedLayersForFind = false;
		app.findChangeGrepOptions.includeLockedStoriesForFind = false;
		app.findChangeGrepOptions.includeMasterPages = true;

		var findWhat = this.findWindowsPath;
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findMailToURL);
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findURLWithScheme);
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findURLWithoutScheme);
		
		app.findGrepPreferences.findWhat = findWhat;
		
		this.currentFoundItem = null;
		this.currentSelectionObjectIndex = 0;
		
		switch (this.dialog.SelectedScope()){
			case localize(urlToHyperlinkStrings.SEARCHDOCUMENTITEM):
				this.myFoundItems = this.doc.findGrep().reverse();
				break;
			case localize(urlToHyperlinkStrings.SEARCHSTORYITEM):
				switch (this.Selection[0].constructor.name){
					case 'Character':
					case 'Word':
					case 'TextStyleRange':
					case 'Line':
					case 'Paragraph':
					case 'TextColumn':
					case 'Text':
					case 'InsertionPoint':
						this.currentSelectionObjectIndex++;
						this.myFoundItems = this.Selection[0].parentStory.findGrep().reverse();
						break;
					case 'Story':
					case 'TextFrame':
						this.currentSelectionObjectIndex++;
						this.myFoundItems = this.Selection[0].texts.item(0).findGrep().reverse();
						break;
					default :
						alert(localize(urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR, 'Story', this.Selection[0].constructor.name), localize(urlToHyperlinkStrings.INDESIGN));
						break;
				}
				break;
			case localize(urlToHyperlinkStrings.SEARCHSELECTIONITEM):
				switch (this.Selection[0].constructor.name){
					case 'Character':
					case 'Word':
					case 'TextStyleRange':
					case 'Line':
					case 'Paragraph':
					case 'TextColumn':
					case 'Text':
					case 'TextFrame':
						this.myFoundItems = this.Selection[0].findGrep().reverse();
						this.currentSelectionObjectIndex++;
						break;
					default :
						alert(localize(urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR, 'Selection', this.Selection[0].constructor.name), localize(urlToHyperlinkStrings.INDESIGN));
						break;
				}
		}
	} catch (x) {
		assert(false, 'Caught in InitData : ' + x);
	}
}

ConvertURLToHyperlink.prototype.CreateURLRegExp = function() {
    
    // local variables used to create complete regular expression for parsing URLs
   var unreserved, pctEncoded, genDelim, subDelimits, pchar, fragment, query, scheme; 
   var userinfo, IPv6Address, IPv4Address, subDomain, host, hostRestricted;
   var decOctlet, h16, ls32;
   
   
    // This regular expression matches to windows path
    this.findWindowsPath = "(\\w:\\\\[\\w\\d:\\-\\\\]*)"; //Windows path prefixed with drive letter
    // This regular expression match email ids . Mail ids with mailto: scheme will be identified as  URIs
    this.findMailToURL = "(([\\w\\d]\\.?\\-?)+@([\\w\\d-]+\\.)+([\\l\\u]{2,}))"; //mailto - without mailto prefix!
       
    //unreserved = "([a-zA-Z0-9-._~])" ;
    unreserved = "([a-zA-Z0-9._~\\-])"; 
    // pct encoded : percentage followed by two hexadecimal digits
    pctEncoded = "(%[0-9a-fA-F][0-9a-fA-F])";
    // General de limiters    :/?#@ [ ]   
    genDelim = "([][:/?#@])";
    // Sub delimiter ! $ & ' (  ) + , ; =  
    subDelimits = "([!\\$&'()*+,;=])";
    // path characters
    pchar = "(" +  unreserved  + "|"  + pctEncoded +  "|" + subDelimits  + ")" ;  
    
    //http query    
    query = "(\\?(" + pchar + "|\\/|\\?)*)";   
    // fragment is series of pchar or / or ?    
    fragment = "(#(" + pchar + "|\\/|\\?)*)";
    
    // scheme starts with alphabet and after that sequence of alphabet, digit, +, - or . (dot)   
    scheme =  "[a-zA-Z][a-zA-Z0-9+.-]*";//
    // path is path elements seperated by / , element are o or more pcharacters 
    path = "(\\/" + pchar + "*)*";
    userinfo =  "((" + pchar + "|:)*@)";
    
    //Dec octlet is number between 0 to 255
    decOctlet = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]])";
    //IPv4 address is 4 octlets 
    IPv4Address = "(" + decOctlet + "\\." + decOctlet + "\\." + decOctlet + "\\." + decOctlet + ")";
    
    //  hexalet..16 bit address represented by 1 to 4 hexadecimal digital in ipV6, leading zero assumed   
    h16 =     "([a-fA-F0-9]{1,4})";
    // lowest 32 bit address in IPv6 is  either two h16 or ipv4 Address   
    ls32 =     "((" + h16 + ":" + h16 + ")|" + IPv4Address +")";
    //  Ipv6 address can be  6  hexlet followed by least 32 bits in ls32 form
    IPv6Address  =  "((" +h16  + ":){6}" + ls32 +")";
    //ipv6 can also be :: (assumed series of zeros) followed by 5 hexlet and then ls32
    IPv6Address = IPv6Address + "|(::(" +h16 + ":){5}" + ls32 +")";
    //ipv6 can also be  1 hexalet  then :: (assumed series of zeros) followed by 4 hexlet and then ls32
    IPv6Address = IPv6Address + "|(" +  h16 + "::(" +h16 + ":){4}" + ls32 +")";
    //ipv6 can also be 0 to 1 hexalet  then :: (assumed series of zeros) followed by 3 hexlet and then ls32
    IPv6Address = IPv6Address + "|((" + h16 + ":){0,1}" + h16 + "::(" +h16 + ":){3}" + ls32 +")";
    //ipv6 can also be 0 to 2 hexalet  then :: (assumed series of zeros) followed by 2 hexlet and then ls32
    IPv6Address = IPv6Address + "|((" + h16 + ":){0,2}" + h16 + "::(" +h16 + ":){2}" + ls32 +")";
    //ipv6 can also be 0 to 3 hexalet  then :: (assumed series of zeros) followed by 1 hexlet and then ls32
    IPv6Address = IPv6Address + "|((" + h16 + ":){0,3}" + h16 + "::(" +h16 +":){1}" + ls32 +")";
    //ipv6 can also be 0 to 4 hexlet then   :: (assumed series of zeros) followed by  ls32
    IPv6Address = IPv6Address + "|(("  + h16 + ":){0,4}" + h16 + "::" + ls32 +")";
    //ipv6 can also be 0 to 5 hexlet then   :: (assumed series of zeros) followed by  hexalet
    IPv6Address = IPv6Address + "|((" + h16 + ":){0,5}::" + h16 + ")";
     //ipv6 can also be 0 to 6 hexlet then   :: (assumed series of zeros) 
    IPv6Address = IPv6Address + "|((" + h16 + ":){0,6}" + h16 + "::)";
    //ipv6 address are enclosed by square braces
    IPv6Address = "(\\[" + "(" + IPv6Address + ")" +"\\])";
    
    // subDomain , starts  with letter, ends with letter or digit,  max 63 character, can have - in middle but not at end or start      
    //subDomain =  "([a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)" ;  
   subDomain = "([a-zA-Z]([a-zA-Z0-9\\-]*[a-zA-Z0-9])?)";
   regName = "((" +subDomain + "\\.)+"  +subDomain + ")" ;
     
    // Hostname is 
    host = "(" + IPv6Address + "|" +  IPv4Address + "|" + regName +")"; 
  
    // in case of scheme is not present, restricted hostname is used
    hostRestricted = "((" +subDomain + "\\.)+"  + this.CreateTLDRegExp() + ")" ;
  
     
     // scheme, optional userInfo, hostname,  optional portNumber, optional ?query, optional #fragment
     // Add a negative look behind to ignore matches ending with period as trailing period usually is punctuation mark 
    this.findURLWithScheme = "(" + scheme + ":"  +  "\\/\\/"  +  host + "(:[0-9]*)?" + path + query  + "?" + fragment + "?" + "(?=(\\W|\\s|$))(?<![;,.()]))";
    
    // Parse URIs without scheme. Assume it to be http scheme. Restrict further by TLDs (top level domains to avoid normal words to be interpreted as http without scheme)
    this.findURLWithoutScheme = "(" +   hostRestricted + "(:[0-9]*)?" + path + query  + "?" + fragment + "?" + "(?=(\\W|\\s|$))(?<![;,.()]))";
}


//Create Regular expression for  Valid Top Level Domains
ConvertURLToHyperlink.prototype.CreateTLDRegExp = function() {
    
        var  TLDRegExp, allTLDs , originalTLDs, numberElements ; 
        var countryTLDs, indexTLDs;
        
        originalTLDs = ["com" , "net",  "org", "int", "edu" , "gov", "mil", "arpa"];
         
         //Country level TLDs are two letter words " 
         TLDRegExp = "(" + "([a-zA-Z]{2,2})";
               
        // Add original top level domains         
        numberElements= originalTLDs.length;
        
        for (indexTLDs=0; indexTLDs < numberElements ; indexTLDs ++)
        {
             TLDRegExp = TLDRegExp + "|" + originalTLDs[indexTLDs];
        }      
         
        TLDRegExp = TLDRegExp + ")";
        return  TLDRegExp;
 }


ConvertURLToHyperlink.prototype.Findbtnclickevent  = function() {
	try {
		if ((this.myFoundItems != null) && (this.myFoundItems.length == 0) && (this.currentSelectionObjectIndex < this.Selection.length) && (this.dialog.SelectedScope() != localize(urlToHyperlinkStrings.SEARCHDOCUMENTITEM)) ) {
			this.GetNextTextSelection();
		}

		var exists = true;
		this.currentFoundItem = null;
		if ((this.myFoundItems != null) && (this.myFoundItems.length > 0)) {
			this.currentFoundItem = this.myFoundItems.pop();
			var exists = this.CheckSourceHyperlinkExists(this.currentFoundItem);
			while ((exists) && (this.myFoundItems.length > 0)) {
				this.currentFoundItem = this.myFoundItems.pop();
				exists = this.CheckSourceHyperlinkExists(this.currentFoundItem);
			}
			if (!exists) {
				SetCurrentScopes.canChangeScopes = false;
				this.doc.select(this.currentFoundItem);
				this.currentFoundItem.showText();
				this.dialog.SetFindNextButtonText();
				// Refer bug #2396633 and #2421430, it seems that the onSelectionChange event (after showText()) 
				// is dispatched after 250 ms. Hence, we cannot let "canChangeScopes" change its value until then.
				var counter = 0;
				while (SetCurrentScopes.canChangeScopes == false && counter < 10)
				{
					IdleCPU(250);
					counter++;
				}
				SetCurrentScopes.canChangeScopes = true;
			} 
		}
		if(exists) {
			alert(localize(urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE), localize(urlToHyperlinkStrings.INDESIGN));
			this.InitData();
			this.dialog.SetFindButtonText();
		}
	} catch (x) {
		assert(false, 'Caught in FindBtnClickEvent : ' + x);
	}
}

function IdleCPU(millis)
{
	var date = new Date();
	var curDate = null;

	do { curDate = new Date(); }
	while(curDate-date < millis);
} 

ConvertURLToHyperlink.prototype.GetNextTextSelection = function() {
	try {
		var textSelectedFound = false;

		while (!textSelectedFound && (this.currentSelectionObjectIndex < this.Selection.length)) {
				switch (this.Selection[this.currentSelectionObjectIndex].constructor.name){
				case 'Character':
				case 'Word':
				case 'TextStyleRange':
				case 'Line':
				case 'Paragraph':
				case 'TextColumn':
				case 'TextFrame':
				case 'Story':
					if (this.Selection[this.currentSelectionObjectIndex].texts.item(0).length > 0)
						this.myFoundItems = this.Selection[this.currentSelectionObjectIndex].texts.item(0).findGrep().reverse();
					textSelectedFound = true;
					break;
				case 'Text':
					if (this.Selection[this.currentSelectionObjectIndex].length > 0)
						this.myFoundItems = this.Selection[this.currentSelectionObjectIndex].findGrep().reverse();
					textSelectedFound = true;
					break;
				default:
					break;
			}
			this.currentSelectionObjectIndex++;
		}
	} catch (x) {
		assert(false, 'Caught in GetNextTextSelection : ' + x);
	}
}

ConvertURLToHyperlink.prototype.CheckSourceHyperlinkExists = function(text) {
	try {
		if(text.findHyperlinks(RangeSortOrder.NO_SORT).length > 0)
			return true;
		else
			return false;
	} catch(x) {
		return true;
	}
}

ConvertURLToHyperlink.prototype.Convertbtnclickevent  = function() {
	try {
		if ( this.currentFoundItem != null) {
			app.doScript('this.AddHyperlink()', undefined, undefined, UndoModes.entireScript);
			this.currentFoundItem = null;
		}
	} catch (x) {
		assert(false, 'Caught in Convertbtnclickevent : ' + x);
	}
}

ConvertURLToHyperlink.prototype.Donebtnclickevent  = function() {
		this.dialog.close();
}

ConvertURLToHyperlink.prototype.onCloseEvent = function() {
	try {
		app.removeEventListener('afterSelectionChanged', SetCurrentScopes);
		this.doc.removeEventListener( 'beforeClose', BeforeDocCloseEvent);
		this.dialogOpen = false;
	} catch (x) {
	}
}

ConvertURLToHyperlink.prototype.AddHyperlink = function() {
	var document = this.doc;
	var text = this.currentFoundItem;

	var source = null;
	var destination = null;
	var hyperlink = null;
	try {

		source = document.hyperlinkTextSources.add(text);
		var destinationType = -1;
		if (destinationType == -1)
		{
			app.findGrepPreferences.findWhat = this.findWindowsPath;
			if(text.findGrep().length > 0)
				destinationType = 1;
		}
		if (destinationType == -1)
		{
			app.findGrepPreferences.findWhat = this.findMailToURL;
			if(text.findGrep().length > 0)
				destinationType = 3;
		}
		if (destinationType == -1)
		{
			app.findGrepPreferences.findWhat = this.findURLWithScheme;
			if(text.findGrep().length > 0)
				destinationType = 2;
		}
		if (destinationType == -1)
		{
			app.findGrepPreferences.findWhat = this.findURLWithoutScheme;
			if(text.findGrep().length > 0)
				destinationType = 4;
		}

		var findWhat = this.findWindowsPath;
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findMailToURL);
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findURLWithScheme);
		findWhat = findWhat.concat("|");
		findWhat = findWhat.concat(this.findURLWithoutScheme);
		app.findGrepPreferences.findWhat = findWhat;

		if (destinationType == 3)
		{
			var destText = "mailto:" + text.contents;
			destination = document.hyperlinkURLDestinations.itemByName(destText);
			if ( destination == null) {
				destination = document.hyperlinkURLDestinations.add(destText, {name:destText});
			}
		}
		else if (destinationType == 4)
		{
			var destText = "http://" + text.contents;
			destination = document.hyperlinkURLDestinations.itemByName(destText);
			if ( destination == null) {
				destination = document.hyperlinkURLDestinations.add(destText, {name:destText});
			}
		}
		else
		{
			destination = document.hyperlinkURLDestinations.itemByName(text.contents);
			if ( destination == null) {
				destination = document.hyperlinkURLDestinations.add(text.contents, {name:text.contents});
			}
		}
		
		hyperlink = document.hyperlinks.add(source, destination);
		this.ApplyCharacterStyle(document, source);

	} catch(x) {
		assert(false, 'Caught in AddHyperlink : ' + x);
		if (source != null)
			source.remove();
		if (destination != null)
			destination.remove();
		if (hyperlink != null)
			hyperlink.remove();
	}

}

ConvertURLToHyperlink.prototype.ApplyCharacterStyle = function(document, source) {
	if(this.dialog.characterStyleToSet())
		if(this.dialog.CharStyleCount() > 0)
		{
			var selectedStyle = this.dialog.SelectedStyle();
			for (var i=0 ; i < document.characterStyles.length ; i++)
				if (selectedStyle == document.characterStyles[i].name) {
					source.sourceText.applyCharacterStyle(document.characterStyles[i]);
					break;
				}
		}
}

ConvertURLToHyperlink.prototype.AddCharacterStyle = function() {
//		app.menuActions.itemByName('New Character Style...' ).invoke() ;
		app.menuActions.itemByID( 0x2100 + 14 ).invoke();
}

ConvertURLToHyperlink.prototype.Convertallbtnclickevent = function() {
	try
	{
		this.InitData();
		var numberURLsConverted = 0;
		
		if (this.dialog.SelectedScope() == localize(urlToHyperlinkStrings.SEARCHDOCUMENTITEM))
		{
			while (this.myFoundItems.length > 0) {
				this.currentFoundItem = this.myFoundItems.pop();
				var exists = this.CheckSourceHyperlinkExists(this.currentFoundItem);
				if (!exists)
				{
					app.doScript('this.AddHyperlink()', undefined, undefined, UndoModes.entireScript);
					numberURLsConverted++;
				}
			}
			this.currentFoundItem = null;
		}
		else {
			while ((this.myFoundItems.length > 0) || (this.currentSelectionObjectIndex < this.Selection.length) ) {
				if ((this.myFoundItems.length == 0) && (this.currentSelectionObjectIndex < this.Selection.length) ) {
					this.GetNextTextSelection();
				}

				this.currentFoundItem = null;
				if (this.myFoundItems.length > 0) {
					this.currentFoundItem = this.myFoundItems.pop();
					var exists = this.CheckSourceHyperlinkExists(this.currentFoundItem);
					if (!exists)
					{
						app.doScript('this.AddHyperlink()', undefined, undefined, UndoModes.entireScript);
						numberURLsConverted++;
					}
				}
			}
		}
		alert(localize(urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE, numberURLsConverted), localize(urlToHyperlinkStrings.INDESIGN));
	} catch(x) {
		this.currentFoundItem = null;
		assert(false, 'Caught in Convertallbtnclickevent : ' + x);
	}
}

function BeforeDocCloseEvent() {
	obj.dialog.close();
}

function SetCurrentScopes() {
	try {
		var currentSelection = app.selection;

		if (SetCurrentScopes.canChangeScopes == false)
		{
			SetCurrentScopes.canChangeScopes = true;
 			return;
		}

		if((currentSelection.length == 0) ||
			(currentSelection[0].constructor.name != 'Text') || 
			(typeof(obj.currentFoundItem) == "undefined") ||
			(obj.currentFoundItem == null) ||
			(obj.currentFoundItem.contents != currentSelection[0].contents))
		{
			var possibleScopes = new Array(localize(urlToHyperlinkStrings.SEARCHDOCUMENTITEM));
			if (currentSelection.length > 0)
			{
				switch (currentSelection[0].constructor.name){
					case 'InsertionPoint':
					case 'Story':
					case 'TextFrame':
						possibleScopes[1] = localize(urlToHyperlinkStrings.SEARCHSTORYITEM);
						break;
					case 'Character':
					case 'Word':
					case 'TextStyleRange':
					case 'Line':
					case 'Paragraph':
					case 'TextColumn':
					case 'Text':
						possibleScopes[1] = localize(urlToHyperlinkStrings.SEARCHSTORYITEM);
						possibleScopes[2] = localize(urlToHyperlinkStrings.SEARCHSELECTIONITEM);
						break;
					default:
						break;
				}
			}
			obj.dialog.InitScopeDL(possibleScopes, obj);
		//	obj.InitData();  // uncommenting this will grep the urls on selectionChange event like typing. But, this will start the matching right from the first url (we don't have a way to tell grep to start from a particular
		//	location except to iterate the matches in the javascipt), so it's not very useful.
		}
	} catch(x) {
		assert(false, 'Caught in SetCurrentScopes : ' + x);
		SetCurrentScopes.canChangeScopes = true;
	}
}

ConvertURLToHyperlink.prototype.RunDialog  = function(){
	try {
		this.activeApp = app;
		this.doc = this.activeApp.documents.item(0);
		this.Selection = app.selection;
		
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
		
		this.dialog = new ConvertURLToHyperlinkDialog();
		this.dialog.InitDialog(this.doc.characterStyles);
		this.dialogOpen = true;

		SetCurrentScopes.disableSelectionChangeEvent = false;
		app.eventListeners.add( "afterSelectionChanged", SetCurrentScopes);
		this.doc.eventListeners.add( "beforeClose", BeforeDocCloseEvent);

		SetCurrentScopes.canChangeScopes = true;
		SetCurrentScopes();
		this.InitData(this.doc);
		this.dialog.BindDialogEvents(this.Findbtnclickevent, this.Convertbtnclickevent, this.ConvertAllbtnclickevent, this.Donebtnclickevent, obj);
	} catch(x) {
		assert(false, 'Caught in RunDialog : ' + x);
	}
}

