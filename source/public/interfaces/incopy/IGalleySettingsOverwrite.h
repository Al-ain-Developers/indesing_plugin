//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleySettingsOverwrite.h $
//  
//  Owner: Cindy Chen
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

#pragma once
#ifndef __IGalleySettingsOverwrite__
#define __IGalleySettingsOverwrite__

#include "WritingModeUIID2.h"
#include "IPMUnknown.h"

class RealAGMColor;

/**
   This interface sets the galley/story view settings when printing/PDF-exporting
   If GetSettingsOverwrite returns kTrue, the galley/story view will construct using this interface's setting,
   otherwise, the galley/story view will construct using the preference - IGalleySettings
 */
class IGalleySettingsOverwrite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGALLEYSETTINGSOVERWRITE };
	
	/**	Get the galley settings overwrite falg
		@param none
		@return bool16 kTrue means this interface's settings are used to construct the galley/story view
	*/
	virtual bool16 GetSettingsOverwrite() = 0;

	/**	Set the galley settings overwrite falg
		@param overwrite 
	*/
	virtual void SetSettingsOverwrite(bool16 overwrite) = 0;
			
	/**	Display paragraph style names or not
		@param none
		@return bool16 kTrue means to display the paragraph style names
	*/
	virtual bool16 GetShowParagraphStyleNames() = 0;

	/**	Set to display paragraph names or not
		@param showStyleNames 
	*/
	virtual void SetShowParagraphStyleNames(bool16 showStyleNames) = 0;
	
	/**	Display line numbers or not
		@param none
		@return bool16 kTrue means to display line numbers
	*/
	virtual bool16 GetShowLineNumbers() = 0;

	/**	Set to display line numbers or not
		@param showLineNumbers 
	*/
	virtual void SetShowLineNumbers(bool16 showLineNumbers) = 0;
	
	/**	Display accurate line endings or not
		@param none
		@return bool16 kTrue means to display accurate line endings
	*/
	virtual bool16 GetIsGalleyAle() = 0;

	/**	Set to display accurate line endings or not
		@param isAle 
	*/
	virtual void SetGalleyAle(bool16 isAle) = 0;
	
	/**	Display Notes or not
		@param storyRef The story the Notes belong to
		@return bool16 kTrue means to display Notes
	*/
	virtual bool16 GetShowInlineNotes(UIDRef &storyRef) = 0;

	/**	Set to display Notes or not
		@param show 
	*/
	virtual void SetShowInlineNotes(bool16 show) = 0;


	/**	Get the type of Notes to display in the view
		@param none
		@return int32 0 means to display all Notes, 1 means to only display the visible Notes in document view
	*/
	virtual int32 GetShowInlineNotesType() = 0;

	/**	Set the type of Notes to display in the view
		@param show, 0 means to display all Notes, 1 means to only display the visible Notes in document view
	*/
	virtual void SetShowInlineNotesType(int32 show) = 0;


	/**	Display story information or not
		@param none
		@return bool16 kTrue means to display story information
	*/
	virtual bool16 GetStoryInfo() = 0;

	/**	Set to display story information or not
		@param show 
	*/
	virtual void SetStoryInfo(bool16 show)  = 0;


	/**	Display the background color in tracked changes text or not
		@param none
		@return bool16 kTrue means to display the background color in tracked changes text
	*/
	virtual bool16 GetTrackChangesBackgroundInColor() = 0;

	/**	Set to display the background color in tracked changes text or not
		@param show 
	*/
	virtual void SetTrackChangesBackgroundInColor(bool16 show) = 0;


	/**	Display the background color in Notes or not
		@param none
		@return bool16 kTrue means to display the background color in Notes
	*/
	virtual bool16 GetNotesBackgroundInColor() = 0;

	/**	Set to display the background color in Notes or not
		@param show 
	*/
	virtual void SetNotesBackgroundInColor(bool16 show)  = 0;

	/**	Display tracked changes or not
		@param none
		@return bool16 kTrue means to display tracked changes
	*/
	virtual bool16 GetShowTrackChanges() = 0;

	/**	Set to display tracked changes or not
		@param show 
	*/
	virtual void SetShowTrackChanges(bool16 show) = 0;


	/**	Get the type of tracked changes to display in the view
		@param none
		@return int32 0 means to display all tracked changes, 1 means to only display the visible tracked changes in document view
	*/
	virtual int32 GetShowTrackChangesType() = 0;

	/**	Set the type of tracked changes to display in the view
		@param show 0 means to display all tracked changes, 1 means to only display the visible tracked changes in document view
	*/
	virtual void SetShowTrackChangesType(int32 show) = 0;

	/**	Get the display font 
		@param none
		@return PMString the font name
	*/
	virtual PMString GetDisplayFont() = 0;

	/**	Set the display font
		@param font 
	*/
	virtual void SetDisplayFont(const PMString &font) = 0;

	/**	Get the display font size
		@param none
		@return PMReal 
	*/
	virtual PMReal GetDisplayFontSize() = 0;

	/**	set the display font size
		@param size 
	*/
	virtual void SetDisplayFontSize(PMReal size) = 0;

	/**	Get the display font leading
		@param none
		@return PMReal 
	*/
	virtual PMReal GetDisplayFontLeading() = 0;

	/**	set the display font leading
		@param leading 
	*/
	virtual void SetDisplayFontLeading(PMReal leading) = 0;

};

#endif // __IGalleySettingsOverwrite__