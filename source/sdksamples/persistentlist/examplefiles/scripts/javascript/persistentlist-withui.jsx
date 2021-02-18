//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/examplefiles/scripts/javascript/persistentlist-withui.jsx $
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
//  JavaScript scripting sample using the PersistentList plug-in.
//  
//  get document
//  
//========================================================================================

if (app.documents.length > 0)
{
        // If there is a document already open, 
        // you must first have a selected page item.
        
        // Just get the first selection
        myDoc = app.activeDocument;
        myPageItem = myDoc.selection[0];
}
else
{
        // Create a new document
        myDoc = app.documents.add();
        // Add a new rectangle (default location)
        myPageItem = myDoc.pages[0].rectangles.add();
}

// get persistent list data items on the page item
pstlstitems = myPageItem.persistentListDataItems;

// get info about the persistent list data item (0)
c = pstlstitems.length;
if (c > 0) 
{
	// get info on item 0
	item0 = pstlstitems[0];
	name0 = item0.name;
	// set the name to something new
	item0.name = "This is item 0";
	// remove item
        item0.remove();
}
else
{
	// add new item
	newItem = pstlstitems.add("Hello world");
}