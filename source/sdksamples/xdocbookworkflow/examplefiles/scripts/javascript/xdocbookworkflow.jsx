//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/examplefiles/scripts/javascript/xdocbookworkflow.jsx $
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
//  Close all open files.
//  
//========================================================================================

CloseAll();

var templatePaths = new Array("","");
app.xdocbookworkflowPreferences.templatePaths = templatePaths;

app.xdocbookworkflowPreferences.placeImagesViaPostImportResponder = true;
app.xdocbookworkflowPreferences.createTableViaSaxHandler = false;
app.xdocbookworkflowPreferences.useXmlTransformerService = true;
app.xdocbookworkflowPreferences.xslFileOverridesProcessingInstruction = true;

var myFilePath = File.openDialog ("Choose a dcbk file to open", "*.dcbk",false);
if(myFilePath)
{
	var myFile = new File(myFilePath);
	app.open(myFile);
}
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