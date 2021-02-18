//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/examplefiles/TransparencyEffect.jsx $
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

var outputFilepath = "/TransparencyEffect_jsx.indd";
if (app.scriptArgs.isDefined("output")) {
	outputFilepath = app.scriptArgs.get("output");
}

// create a new document
var myDocument = app.documents.add();

// Draw a rectangle on the first page of the document
var myRect = myDocument.pages.item(0).rectangles.add();
myRect.geometricBounds = [6, 6, 18, 18];
myRect.strokeWeight = 4;

// set the transparency effect settings of the rectangle
with(myRect.transparencyeffectsettingsproperty){
	transparencyeffectmode = true;
	transparencyeffectusealpha = true;
	transparencyeffectoffsetxdirection = 10;
	transparencyeffectoffsetydirection = 8;
	transparencyeffectuseblackasopaque = true;
	transparencyeffectuseblur = true;
}

// save and close the file
myDocument.close(SaveOptions.yes, new File(outputFilepath));
