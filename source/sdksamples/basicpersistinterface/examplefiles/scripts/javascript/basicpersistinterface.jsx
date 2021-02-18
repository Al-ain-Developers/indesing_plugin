//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/examplefiles/scripts/javascript/basicpersistinterface.jsx $
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
//  exercises each scriptable feature of the plug-in.
//  
//  The results of the script are logged in a file called 
//  basicpersistinterface.jsx-log.txt in the folder that contains
//  the script. Check the log file for the results.
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
var myError = false;
var myName = "";

// app.basicpersistinterfacePreferences.bpiData
myName = "Set and get bpiData application default";
sink.writeln(myName);
app.basicpersistinterfacePreferences.bpiData = "default";
if (app.basicpersistinterfacePreferences.bpiData != "default") {
	sink.writeln(" error");
	myError = true;
}

// app.documents[i].basicpersistinterfacePreferences.bpiData 
myName = "Set and get bpiData document default";
sink.writeln(myName);
app.documents.add();
app.documents[0].basicpersistinterfacePreferences.bpiData = "doc-default";
if (app.documents[0].basicpersistinterfacePreferences.bpiData != "doc-default") {
	sink.writeln(" error");
	myError = true;
}

// app.documents[i].pages[j].rectangles[k].bpiData
myName = "Set and get bpiData on rectangle page item";
sink.writeln(myName);
app.documents[0].pages[0].rectangles.add();
app.documents[0].pages[0].rectangles[0].bpiData = "rectangle-bpiData";
if (app.documents[0].pages[0].rectangles[0].bpiData != "rectangle-bpiData") {
	sink.writeln(" error");
	myError = true;
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

/*
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