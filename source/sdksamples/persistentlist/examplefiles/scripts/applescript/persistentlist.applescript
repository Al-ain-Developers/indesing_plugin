-- ========================================================================================
-- 
--   $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/examplefiles/scripts/applescript/persistentlist.applescript $
-- 
--   Owner: Adobe Developer Technologies
-- 
--   $Author: pmbuilder $
-- 
--   $DateTime: 2020/11/06 13:08:29 $
-- 
--   $Revision: #2 $
-- 
--   $Change: 1088580 $
-- 
--   Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
-- 
--   NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance
--   with the terms of the Adobe license agreement accompanying it.  If you have received
--   this file from a source other than Adobe, then your use, modification, or
--   distribution of it requires the prior written permission of Adobe.
-- 
--   AppleScript scripting sample using the PersistentList plug-in.
-- 
-- ========================================================================================
-- change this line according to the application you want to use.
tell application "Adobe InDesign CS6"
-- For InCopy, use:  tell application "Adobe InCopy CS6"
-- For InDesign-J, use:  tell application "Adobe InDesign CS6_J"
	-- get document
	if (count of documents) > 0 then
		set myDoc to active document
		tell myDoc
			if (count of page items) > 0 then
				-- get first page item
				set myPageItem to item 1 of page items
			else
				-- make a new rectangle
				set myPageItem to make rectangle
			end if
		end tell
	else
		-- no document open, so make one
		set myDoc to make document
		tell myDoc
			-- make a new rectangle
			set myPageItem to make rectangle
		end tell
	end if
	
	tell myPageItem
		-- get persistent list data items on the page item
		set pstlstitems to persistent list data items
		tell pstlstitems
			set c to count
			if (c > 0) then
				-- get info on item 1
				set item1 to item 1 of pstlstitems
				set name1 to name of item1
				-- set the name to something new
				set name of item1 to "item 1"
				-- delete item (uncomment to actually delete)
				delete item1
			else
				-- add new item
				set newItem to make persistent list data item of myPageItem with properties {name:"Hello world"}
			end if
		end tell
	end tell
end tell
