//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/examplefiles/scripts/javascript/SnippetRunner.jsx $
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
//  JavaScript sample for Snippet Runner plug-in
//  
//  NOTE: Requires the SnippetRunner plug-in!
//  
//  Get a reference to the folder containing the running script.
//  
//========================================================================================

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

// get the SDKCodeSnippetRunner object
var snippetRunner = app.sdkCodeSnippetRunnerObject;
if (snippetRunner)
{
    sink.writeln("Got sdkCodeSnippetRunnerObject");
}
else
{
    sink.writeln(" error: sdkCodeSnippetRunnerObject not found");
    myError = true;
}

// check trace mode
var traceMode = snippetRunner.snipRunTraceMode;
if (traceMode == SnipRunTraceModeEnum.snipRunTraceOn) 
{
    alert("Trace mode is on.");
    sink.writeln("Checking trace mode: Trace mode is on");
}
else
{
    alert("Trace mode is off.");
    sink.writeln("Checking trace mode: Trace mode is off");
}

// check panel visibility
var visibility = snippetRunner.snipRunPanelVisibility;
if (visibility == SnipRunPanelVisibilityEnum.panelInvisible) 
{
    alert("Panel is currently invisible. Setting panel visibility on");
    sink.writeln("Panel is currently invisible. Setting panel visibility on");
    // NOTE: Must use the actual property, not the local variable
    snippetRunner.snipRunPanelVisibility = SnipRunPanelVisibilityEnum.panelVisible;
    if (app.sdkCodeSnippetRunnerObject.snipRunPanelVisibility == SnipRunPanelVisibilityEnum.panelInvisible)
    {
        sink.writeln(" error: Visibility is still invisible");
        myError = true;
    }
}

// iterate through registered snippets
var numSnippets = snippetRunner.sdkCodeSnippets.count();
if (numSnippets > 0) 
{
    var msg = "Found "; 
    msg += numSnippets;
    msg += " code snippets. Information for code snippets that can be run in the current context will be logged in ";
    msg += myLogFile;
    alert(msg);
    
    sink.writeln("[Information about code snippets that can be run in the current context]"); 
    for (i = 0 ; i < numSnippets ; i++) 
    {
        var snippet = snippetRunner.sdkCodeSnippets.item(i);
        if (snippet.canRun() == true) 
        {
            var snippetName = snippet.codeSnippetName;
            var snippetDescr = snippet.codeSnippetDescription;
            var msg = "(" + i + ") " + snippetName + ": " + snippetDescr;
            sink.writeln(msg); 
        }
        else
        {
            // this snippet cannot run in the current context
        }
    }
}
else
{
    alert("There are no code snippets!"); 
    sink.writeln("There are no code snippets!");
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

// End.
