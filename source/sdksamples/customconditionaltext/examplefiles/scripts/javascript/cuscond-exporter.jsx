//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/examplefiles/scripts/javascript/cuscond-exporter.jsx $
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
sink.writeln("Export conditions");

if(app.documents.count() == 0) {
	ws = app;
}
else {
	ws = app.activeDocument;
}

var fso = new File(myFolder + "mycondition.xml");
fso.open ("w");

fso.write("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
fso.write("<Conditions>\n");

var conCount = ws.conditions.count();

for(i = 0; i < conCount; i++) {	
	fso.write("<Condition>\n");

	fso.write("	<CondName>" + ws.conditions[i].name+ "</CondName>\n");
	fso.write("	<IndicatorColor>" + ws.conditions[i].indicatorColor + "</IndicatorColor>\n");
	fso.write("	<Visible>" + ws.conditions[i].visible + "</Visible>\n");
	
	fso.write("	<Method>" + ws.conditions[i].indicatorMethod + "</Method>\n");
	
	if(ws.conditions[i].indicatorMethod == ConditionIndicatorMethod.useUnderline) {
		fso.write("	<Appearance>" + ws.conditions[i].underlineIndicatorAppearance + "</Appearance>\n");
	}

	fso.write("	<IdmlVisible>" + ws.conditions[i].idmlVisible + "</IdmlVisible>\n");
	fso.write("	<PrintVisible>" +  ws.conditions[i].printVisible + "</PrintVisible>\n");
	
	fso.write("</Condition>\n");
}

fso.write("</Conditions>\n");

fso.close();
// Close the log.
sink.close();
