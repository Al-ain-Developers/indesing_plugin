//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/examplefiles/scripts/javascript/persistentlist.jsx $
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
//  JavaScript scripting sample using the PersistentList plug-in.
//  
//  exercises each scriptable feature of the plug-in.
//  
//  The results of the script are logged in a file called 
//  persistentlist.jsx-log.txt in the folder that contains
//  the script. Check the log file for the results.
//  
//  This script can be used on InDesign or InDesign Server.
//  
//  Close all open files.
//  
//========================================================================================

CloseAll();

//Get a reference to the folder containing the running script.
var myScriptFileName = app.activeScript;
var myScriptFile = File(myScriptFileName);
var myFolder = myScriptFile.parent + "/";

// Open log file alongside the script.
var myLogFile = myScriptFile + "-log.txt";
var sink;
sink = new File(myLogFile);
sink.open("w");

// Local variables used to track status.
var myDoc;
var myError = false;
var myName = "";
var myPageItem;
var pstlstitems;
var newItem;

// Create a new document
myDoc = app.documents.add();

        
// document.pages[j].rectangles[k].persistentListDataItems[m];
myName = "Set and get persistentListData on rectangle page item";
sink.writeln(myName);
myPageItem = myDoc.pages[0].rectangles.add();

// get persistent list data items on the page item
pstlstitems = myPageItem.persistentListDataItems;

newItem = pstlstitems.add("Hello world");
if (app.documents[0].pages[0].rectangles[0].persistentListDataItems[0]. name != "Hello world") {
	sink.writeln(" error");
	myError = true;
}


myName = "Add 3 persistentListData items on rectangle page item and get count";
sink.writeln(myName);
newItem = pstlstitems.add("Hello world2");
newItem = pstlstitems.add("Hello world3");
newItem = pstlstitems.add("Hello world4");
numItems = pstlstitems.length;
if (numItems != 4) {
        sink.writeln(" error");
        myError = true;
} else {
        sink.writeln(" count is now 4");
}


myName = "Remove 2 persistentListData items from rectangle page item and get count";
sink.writeln(myName);
pstlstitems[3].remove();
pstlstitems[2].remove();
numItems = pstlstitems.length;
if (numItems != 2) {
        sink.writeln(" error");
        myError = true;
} else {
        sink.writeln(" count is now 2");
}


// Report results of script.
if (myError) {
	alert("DONE WITH ERRORS");
	sink.writeln("DONE WITH ERRORS");
	alert("Check log file: "  + myLogFile);}
else {
	alert("DONE");
	sink.writeln("DONE");
}  

// Close the log.
sink.close();

/* CloseAll
*/
function CloseAll() 
{
	while	(app.documents.length >	0)  {
		app.documents[0].close(SaveOptions.NO);	
	}
	if (app.name !=	"Adobe InCopy")	{
		while (app.books.length	> 0) {
			app.books[0].close(SaveOptions.NO);	
		}
		while (app.libraries.length	> 0) {
			app.libraries[0].close(); 
		}
	}
}

// End, persistentlist.jsx.