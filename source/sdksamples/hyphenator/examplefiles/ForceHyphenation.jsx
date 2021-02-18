//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/examplefiles/ForceHyphenation.jsx $
//  
//  Owner: ???
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
//========================================================================================

//HelloWorld.jsx
//Create a new document.
var myDocument = app.documents.add();
var myPage = myDocument.pages.item(0);

// Tell the document to use our sample's hyphenator (assumes default doc lang is "English: USA")
var myLang = myDocument.languages.item("English: USA");
myLang.hyphenationVendor = "Hyphenator[US]";

//Create a skinny text frame and set content to long words to force hyphenation.
var myTextFrame = myPage.textFrames.add();
myTextFrame.geometricBounds = ["6p0", "6p0", "27p0", "11p0"];
myTextFrame.contents = "ThisIsLongText!  Are you Hyphenating this?";

//Save the document (fill in a valid file path).
var myFile = new File("/c/ServerTestFiles/HypenationExample.indd");
var result = "saved to:  " + myFile.fullName;
if(!myFile.parent.exists && !myFile.parent.create()) {
	result = "Not saved.  Unable to create the folder:  " + myFile.parent.fullName;
} else {
	myDocument = myDocument.save(myFile);
}
myDocument.close();

// Here is were we access our plug-in's performance metrics.
var myMetric = app.performanceMetric(app.hyphenationMax);
result += String(" ; hyphenation Max metric = " + myMetric);

myMetric = app.performanceMetric(app.hyphenationTotal);
result += String(" ;  hyphenation Total metric = " + myMetric);
		 
result;
		