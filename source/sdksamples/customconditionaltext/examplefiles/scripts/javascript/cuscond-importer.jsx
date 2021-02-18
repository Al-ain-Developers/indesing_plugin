//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/examplefiles/scripts/javascript/cuscond-importer.jsx $
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
//========================================================================================

//  Get a reference to the folder containing the running script.
var myScriptFileName = app.activeScript;
var myScriptFile = File(myScriptFileName);
var myFolder = myScriptFile.parent + "/";

// Open log file alongside the script.
var myLogFile = myScriptFile + "-log.txt";
var sink = new File(myLogFile);
sink.open("w");

var myName = "Import conditions";
sink.writeln(myName);

if(app.documents.count() == 0) {
	ws = app;
}
else {
	ws = app.activeDocument;
}

var fso = new File(myFolder + "mycondition.xml");
fso.open ("r");
var context = fso.read();
fso.close();

var myRoot = new XML(context);
var xmlConditionsCount = myRoot.children().length();

for(var i = 0; i < xmlConditionsCount; i++) {
	var condName = myRoot.Condition[i].CondName.toString();
	var indexInWS = GetConditionIndexByName(ws, condName);
	if(indexInWS < 0) {
		indexInWS = ws.conditions.add().index;
	}

	ws.conditions[indexInWS].name = condName;
	ws.conditions[indexInWS].indicatorColor = Number(myRoot.Condition[i].IndicatorColor);
	
	var visible = myRoot.Condition[i].Visible;
	if(visible == "" || visible == "true") {
		ws.conditions[indexInWS].visible = true;
	}
	else {
		ws.conditions[indexInWS].visible = false;
	}
	
	var indicatorMethod = Number(myRoot.Condition[i].Method);
	ws.conditions[indexInWS].indicatorMethod = indicatorMethod;
	if(indicatorMethod == ConditionIndicatorMethod.useUnderline) {
		ws.conditions[indexInWS].underlineIndicatorAppearance = Number(myRoot.Condition[i].Appearance);
	}
	
	var idmlVisible =  myRoot.Condition[i].IdmlVisible;
	if(idmlVisible == "" || idmlVisible == "true") {
		ws.conditions[indexInWS].idmlVisible = true;
	}
	else {
		ws.conditions[indexInWS].idmlVisible = false;
	}
	
	var printVisible =  myRoot.Condition[i].PrintVisible;
	if(printVisible == "" || printVisible == "true") {
		ws.conditions[indexInWS].printVisible = true;	
	}
	else{
		ws.conditions[indexInWS].printVisible = false;	
	}
}

function GetConditionIndexByName(workspace, conditionName)
{
	for(var i = 0; i < workspace.conditions.count(); i++) {
		if(workspace.conditions[i].name == conditionName) 
			return i;
	}
	return -1;
}

// Close the log.
sink.close();
