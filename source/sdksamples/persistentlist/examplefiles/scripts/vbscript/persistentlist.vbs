'//========================================================================================
'//  
'//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/examplefiles/scripts/vbscript/persistentlist.vbs $
'//  
'//  Owner: Adobe Developer Technologies
'//  
'//  $Author: pmbuilder $
'//  
'//  $DateTime: 2020/11/06 13:08:29 $
'//  
'//  $Revision: #2 $
'//  
'//  $Change: 1088580 $
'//  
'//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
'//  
'//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
'//  with the terms of the Adobe license agreement accompanying it.  If you have received
'//  this file from a source other than Adobe, then your use, modification, or 
'//  distribution of it requires the prior written permission of Adobe.
'//  
'//  
'//  VBScript scripting sample using the PersistentList plug-in.
'//  
'//  exercises scriptable features of the plug-in.
'//  
'//========================================================================================


' Get the application
Set gApp = CreateObject("InDesign.Application")


' If no document is open, create one
If gApp.Documents.Count = 0 Then
	Set myDoc = gApp.Documents.Add
Else
	Set myDoc = gApp.ActiveDocument
End If


' If there is no page item, add a rectangle
Set myPage = myDoc.Pages.Item(1)
If myPage.PageItems.Count = 0 Then
	Set myPageItem = myPage.Rectangles.Add
	myPageItem.GeometricBounds = Array("20p", "20p", "30p", "30p")
Else
	Set myPageItem = myPage.PageItems(1)
End If

'gApp.Select myPageItem


' Get the list of persistent data
Set persistentItems = myPageItem.PersistentListDataItems

' Add a persistent item data if none exists
If persistentItems.Count = 0 Then
	Set myPersistentItem = persistentItems.Add
Else
	Set myPersistentItem = persistentItems(1)
End If

' Toggle the name of the persistent item between "Hello World" and "Item 1"
If myPersistentItem.Name = "Hello World" Then
	myPersistentItem.Name = "Item 1"
Else
	myPersistentItem.Name = "Hello World"
End If



