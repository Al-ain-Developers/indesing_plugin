'//========================================================================================
'//  
'//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/examplefiles/scripts/vbscript/SnippetRunner.vbs $
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
'// SnippetRunner plug-in scripting sample.
'// NOTE:  Requires the SnippetRunner plug-in!
'//  
'//========================================================================================

'Get the application
Set gApp = CreateObject("InDesign.Application")

' Get the Snippet Runner
Set gSnippetRunner = gApp.SDKCodeSnippetRunnerObject
    
' check trace mode
mode = gSnippetRunner.SnipRunTraceMode
If mode = InDesign.idSnipRunTraceModeEnum.idSnipRunTraceOn Then
    MsgBox("Trace mode is on.")
Else
    MsgBox("Trace mode is off.")
End If

' check panel visibility - if it's invisible, attempt to show it
visibility = gSnippetRunner.SnipRunPanelVisibility
If visibility = InDesign.idSnipRunPanelVisibilityEnum.idPanelInvisible Then
    MsgBox("Panel is currently invisible.  Setting panel visiblity on.")
    gSnippetRunner.SnipRunPanelVisibility = InDesign.idSnipRunPanelVisibilityEnum.idPanelVisible
    If gSnippetRunner.SnipRunPanelVisibility = InDesign.idSnipRunPanelVisibilityEnum.idPanelInvisible Then
        MsgBox("error:  Panel is still invisible.")
    End If
End If

' show the number of snippets
MsgBox ("Found " & CStr(gSnippetRunner.SdkCodeSnippets.Count) & " snippets")

' iterate through registered snippets
i = 0
For Each snippet in gSnippetRunner.SdkCodeSnippets
    If snippet.CanRun() Then
        ' display a message dialog for each runnable snippet
        MsgBox("(" & i & ") " & snippet.CodeSnippetName & ":  " & snippet.CodeSnippetDescription)
    End If
    i = i + 1
Next
