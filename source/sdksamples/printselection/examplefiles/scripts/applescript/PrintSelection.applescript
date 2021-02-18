--========================================================================================
--  
--  $File: //depot/shuksan/source/sdksamples/printselection/internal/scripts/applescript/PrintSelection.as $
--  
--  Owner: Adobe Developer Technologies
--  
--  $Author: sadahiro $
--  
--  $DateTime: 2004/11/08 17:07:35 $
--  
--  $Revision: #3 $
--  
--  $Change: 297847 $
--  
--  Copyright 1997-2004 Adobe Systems Incorporated. All rights reserved.
--  
--  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
--  with the terms of the Adobe license agreement accompanying it.  If you have received
--  this file from a source other than Adobe, then your use, modification, or 
--  distribution of it requires the prior written permission of Adobe.
--  
--  PrintSelection plug-in scripting sample.
--  Please refer to InDesign Scripting Guide for details on how to write scripts for InDesign.
--========================================================================================

tell application "Adobe InDesign CS3"
-- For InCopy, use:  tell application "Adobe InCopy CS3"
-- For InDesign-J, use:  tell application "Adobe InDesign CS3_J"

	-- Create a new document
	tell (make document)
		-- create a page item
		set theRect to make rectangle
		set geometric bounds of theRect to {3, 3, 30, 30}
		
		-- Create an oval and select it
		set theOval to make oval
		set geometric bounds of theOval to {30, 30, 50, 50}
		select theOval
		
		-- print selection only
		-- Note: if no item is selected, the whole document will be printed
		set print selection of print selection preferences to true
		-- Print the document without a dialog
		print without print dialog
	end tell
	
end tell
