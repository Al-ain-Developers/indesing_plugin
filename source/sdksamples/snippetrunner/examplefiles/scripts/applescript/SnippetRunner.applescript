--//========================================================================================
--//  
--//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/examplefiles/scripts/applescript/SnippetRunner.applescript $
--//  
--//  Owner: Adobe Developer Technologies
--//  
--//  $Author: pmbuilder $
--//  
--//  $DateTime: 2020/11/06 13:08:29 $
--//  
--//  $Revision: #2 $
--//  
--//  $Change: 1088580 $
--//  
--//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
--//  
--//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
--//  with the terms of the Adobe license agreement accompanying it.  If you have received
--//  this file from a source other than Adobe, then your use, modification, or 
--//  distribution of it requires the prior written permission of Adobe.
--//  
--//  AppleScript sample for the SnippetRunner plug-in 
--//========================================================================================
tell application "Adobe InDesign CS3"
	-- For InCopy, use:  tell application "Adobe InCopy CS3"
	-- For InDesign-J, use:  tell application "Adobe InDesign CS3_J"
	-- display trace mode if it is on
	set mySnipRunPanelTraceMode to Snip run trace mode of SDK code snippet runner object
	display dialog "Trace mode is " & (mySnipRunPanelTraceMode as string)
	if (mySnipRunPanelTraceMode = snip run trace off) then
		set mySnipRunPanelTraceMode to snip run trace on
	end if
	-- display visibility mode if invisible, then adjust
	if (Snip run panel visibility of SDK code snippet runner object = panel invisible) then
		display dialog "Visibility is " & (Snip run panel visibility of SDK code snippet runner object as string)
		set Snip run panel visibility of SDK code snippet runner object to panel visible
		if (Snip run panel visibility of SDK code snippet runner object = panel invisible) then
			display dialog "ERROR: Visibility is still invisible"
		end if
	end if
	-- iterate through loaded codesnippets
	set numSnippets to count of SDK code snippet of SDK code snippet runner object
	if (numSnippets > 0) then
		repeat with counter from 1 to numSnippets
			tell SDK code snippet counter of SDK code snippet runner object
				set snippetName to code snippet name
				set snippetDescr to code snippet description
				if (can run) is true then
					display dialog "(" & counter & ") " & snippetName & ": " & snippetDescr
					-- else -- this snippet can't run in the current context.
					-- display dialog "(" & counter & ") " & snippetName & " cannot run in the context." -- 
				end if
			end tell
		end repeat
	else
		display dialog "There are no snippets!"
	end if
end tell