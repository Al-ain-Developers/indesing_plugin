//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/examplefiles/scripts/javascript/PrintSelection.jsx $
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
//  PrintSelection plug-in scripting sample.
//  Please refer to InDesign Scripting Guide for details on how to write scripts for InDesign.
//  
//  local variables
//  
//========================================================================================

var theDoc;
var thePage;
var theRect;
var theOval;
var printSelectionPrefs;

// create a new document
theDoc = app.documents.add();
// get the 1st page
thePage = theDoc.pages.item(0);

// make a rectangle
theRect = theDoc.rectangles.add();
// resize the rectangle so that it is visible to user
theRect.geometricBounds = new Array(3, 3, 30, 30);

// make an oval
theOval = theDoc.ovals.add();
// resize the oval so that it is visible to user
theOval.geometricBounds = new Array(30, 30, 50, 50);
// select the oval
theOval.select();

// Get print selection preferences
printSelectionPrefs = theDoc.printSelectionPreferences;

// Set print selection to true. so that only the selected items are printed
// Note: it nothing is selected, whole document will be printed.
printSelectionPrefs.printSelection = true;

// Print out the document (only selected items).
// 'false' means do not bring up the print dialog
theDoc.print(false);

// End, PrintSelection.jsx
