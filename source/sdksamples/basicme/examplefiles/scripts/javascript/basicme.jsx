//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicme/examplefiles/scripts/javascript/basicme.jsx $
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
//========================================================================================

var txt = ["\u0627\u0628\u062A \u062B\u062C\u062D \u062E\u062F\u0630 " +
			"\u0631\u0632\u0633 \u0634\u0635\u0636 \u0637\u0638\u0639 " +
			"\u063A\u0641\u0642 \u0643\u0644\u0645 \u0646\u0647\u0648 " +
			"\u064A\u0627\u0628 \u062A\u062B\u062C \u062D\u062E\u062F " +
			"\u0630\u0631\u0632 \u0633\u0634\u0635 \u0636\u0637\u0638 " +
			"\u0639\u063A\u0641 \u0642\u0643\u0644 \u0645\u0646\u0647 " +
			"\u0647\u0648\u064A ",
			"\u05D0\u05D1\u05D2 \u05D3\u05D4\u05D5 \u05D6\u05D7\u05D8 "+
			"\u05D9\u05DB\u05DC \u05DE\u05E0\u05E1 \u05E2\u05E4\u05E6 "+
			"\u05E7\u05E8\u05E9\u05EA \u05D0\u05D1\u05D2 \u05D3\u05D4\u05D5 "+
			"\u05D6\u05D7\u05D8 \u05D9\u05DB\u05DC \u05DE\u05E0\u05E1 "+
			"\u05E2\u05E4\u05E6 \u05E7\u05E8\u05E9\u05EA\r",
			"One two three "]

var composerSet = ["Adobe World-Ready Paragraph Composer", 
					"Adobe World-Ready Single-line Composer",
					"Adobe Paragraph Composer",
					"Adobe Single-line Composer"];
	
main();

function main(){
	var basicme = app.basicme;
	var myDocument = basicme.createDocument(BasicmeDicrection.rightToLeft);
	
	var mt = basicme.createTextFrame(myDocument.pages[0], ["0p", "0p", "15p", "18p"], BasicmeDicrection.rightToLeft, 2);
	var s = mt.parentStory;
	mt.contents = "\r";
	s.insertionPoints[-1].contents = txt[0];
	var myParagraph = s.paragraphs[-1];
	basicme.changeParagraphAttr(myParagraph, composerSet[0], BasicmeLanguage.arabic, "Adobe Arabic");	

	var mt = basicme.createTextFrame(myDocument.pages[0], ["18p", "0p", "33p", "18p"], BasicmeDicrection.rightToLeft, 1);
	var s = mt.parentStory;
	mt.contents = "\r";
	s.insertionPoints[-1].contents = txt[1];
	var myParagraph = s.paragraphs[-1];
	basicme.changeParagraphAttr(myParagraph, composerSet[0], BasicmeLanguage.hebrew, "Adobe Hebrew");	

	mt = basicme.createTextFrame(myDocument.pages[0], ["36p", "0p", "50p", "18p"], BasicmeDicrection.leftToRight, 1);
	s = mt.parentStory;
	mt.contents = "\r";
	s.insertionPoints[-1].contents = txt[2];
	myParagraph = s.paragraphs[-1];
	basicme.changeParagraphAttr(myParagraph, composerSet[2], BasicmeLanguage.roman, "Minion Pro");	
	
	var myFile = new File("/c/ServerTestFiles/BasicMe.indd");
	if(!myFile.parent.exists)
	{
		myFile.parent.create();
	}	
	myDocument.close(SaveOptions.YES, myFile, "", true);
}

 
