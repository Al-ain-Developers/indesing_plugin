//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/examplefiles/candlechart.jsx $
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
//  exercises scriptable features of the plug-in.
//  
//  The results of the script are logged in a file called 
//  CandleChart.jsx-log.txt in the folder that contains
//  the script. Check the log file for the results.
//  
//  Get a reference to the folder containing the running script.
//  
//========================================================================================

var myScriptFileName = app.activeScript;
var myScriptFile = File(myScriptFileName);
var myFolder = myScriptFile.parent + "/";
var myDataFile = myFolder + "SampleData1.csv";

// Open log file alongside the script.
var myLogFile = myScriptFile + "-log.txt";
var sink;
sink = new File(myLogFile);
sink.open("w");

// Local variables used to track status.
var myError = false;
var myName = "";

myName = "Create a CandleChart";
sink.writeln(myName);
app.documents.add();
app.documents[0].spreads[0]. candleCharts.add( );
if (app.documents[0].spreads[0]. candleCharts.length != 1) {
	sink.writeln(" error");
	myError = true;
}
app.documents[0].spreads[0]. candleCharts[0].geometricBounds = ["0p0", "0p0", "18p0", "36p0"];

myName = "Load data from CSV file into the CandleChart";
sink.writeln(myName);
app.documents[0].spreads[0]. candleCharts[0].importData(new File(myDataFile));
if (app.documents[0].spreads[0]. candleCharts[0]. candleStocks.length  == 0) {
	sink.writeln(" error");
	myError = true;
}

myName = "Create CandleChart manually";
sink.writeln(myName);
var myChart = app.documents[0].spreads[0]. candleCharts.add();
if (app.documents[0].spreads[0]. candleCharts.length != 2) {
	sink.writeln(" error");
	myError = true;
}
myChart.geometricBounds = ["40p0", "0p0", "56p0", "36p0"];
myChart.name = "Second example";

myName = "Add 3 candle stocks";
sink.writeln(myName); 
myChart. candleStocks.add();
myChart. candleStocks.add();
myChart. candleStocks.add();

myChart.candleStocks[0].stockOpen = 20;
myChart.candleStocks[0].stockHigh = 22;
myChart.candleStocks[0].stockLow = 19;
myChart.candleStocks[0].stockClose = 21;
myChart.candleStocks[0].stockVolume = 10000;

myChart.candleStocks[1].stockOpen = 30;
myChart.candleStocks[1].stockHigh = 32;
myChart.candleStocks[1].stockLow = 29;
myChart.candleStocks[1].stockClose = 31;
myChart.candleStocks[1].stockVolume = 20000;

myChart.candleStocks[2].stockOpen = 25;
myChart.candleStocks[2].stockHigh = 27.50;
myChart.candleStocks[2].stockLow = 19;
myChart.candleStocks[2].stockClose = 26;
myChart.candleStocks[2].stockVolume = 15000;

if (myChart. candleStocks.length != 3) {
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

