'//========================================================================================
'//  
'//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/examplefiles/scripts/vbscript/PrintSelection.vbs $
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
'//  Copyright 1997-2004 Adobe Systems Incorporated. All rights reserved.
'//  
'//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
'//  with the terms of the Adobe license agreement accompanying it.  If you have received
'//  this file from a source other than Adobe, then your use, modification, or 
'//  distribution of it requires the prior written permission of Adobe.
'//  
'// PrintSelection plug-in scripting sample.
'// Please refer to InDesign Scripting Guide for details on how to write scripts for InDesign.
'//  
'//========================================================================================

'Get the application
Set theApp = CreateObject("InDesign.Application")
' NOTE: Uncomment the following line and comment the above line 
' to run this script in InCopy.
'Set theApp = CreateObject("InCopy.Application")

' create a new document
Set theDoc = theApp.Documents.Add

' get the 1st page
Set thePage = theDoc.Pages.Item(1)

' make a rectangle
Set theRect = theDoc.Rectangles.Add
'Resize the pageitem so that it is visible to user
theRect.GeometricBounds = Array(3, 3, 30, 30)

' make an oval
Set theOval = theDoc.Ovals.Add
'Resize the pageitem so that it is visible to user
theOval.GeometricBounds = Array(30, 30, 50, 50)
'Select the object
theOval.Select

'Get print selection preferences
Set printSelectionPrefs = theDoc.PrintSelectionPreferences

'Set print selection to true. so that only the selected items are printed
'Note: it nothing is selected, whole document will be printed.
printSelectionPrefs.PrintSelection = True

' Print out the document (only selected items).
' 'False' means do not bring up the print dialog
Call theDoc.PrintOut(False)

