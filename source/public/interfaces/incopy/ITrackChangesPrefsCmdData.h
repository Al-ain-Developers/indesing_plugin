//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITrackChangesPrefsCmdData.h $
//  
//  Owner: Michele Goodwin
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ITrackChangesPrefsCmdData__
#define __ITrackChangesPrefsCmdData__

#include "IPMUnknown.h"
#include "InCopySharedID.h"
#include "ITrackChangesSettings.h"

class ITrackChangeAppSettings;

/**
	ITrackChangesPrefsCmdData is a data interface for the kSetTrackChangesPrefsCmdBoss.  It is used to
	specify the options for the track changes preferences.
	@see ITrackChangeAppSettings in ITrackChangesSettings.h
*/
class ITrackChangesPrefsCmdData : public IPMUnknown
{
public:
	/**
		use this to set all track changes prefs command data in one call
		@param showAddedText whether or not to show added text
		@param showDeletedText whether or not to show deleted text
		@param showMovedText whether or not to show moved text
		@param showChangeBar whether or not to show change bars
		@param cbColorIndex change bar color index
		@param spellchkDeletedText whether or not to spell check deleted text
		@param addedTextColorIndex added text color index
		@param addedBGColorIndex added text background color index
		@param deletedTextColorIndex deleted text color index
		@param deletedBGColorIndex deleted text background color index
		@param movedTextColorIndex moved text color index
		@param movedBGColorIndex moved text background color index
		@param addedTextMarking added text marking
		@param deletedTextMarking deleted text marking
		@param movedTextMarking moved text marking
		@param cbLocation change bar location
		@param addedTextColorChoice added text color choice
		@param addedBGColorChoice added text background color choice
		@param deletedTextColorChoice deleted text color choice
		@param deletedBGColorChoice deleted text background color choice
		@param movedTextColorChoice moved text color choice
		@param movedBGColorChoice moved text background color choice
	*/
	virtual void Set(	bool16 showAddedText,
						bool16 showDeletedText,
						bool16 showMovedText,
						bool16 showChangeBar,
						int32 cbColorIndex,
						bool16 spellchkDeletedText,
						bool16 preventDupeColor,
						int32 addedTextColorIndex,
						int32 addedBGColorIndex,
						int32 deletedTextColorIndex,
						int32 deletedBGColorIndex,
						int32 movedTextColorIndex,
						int32 movedBGColorIndex,
						int32 addedTextMarking,
						int32 deletedTextMarking,
						int32 movedTextMarking,
						int32 cbLocation,
						ITrackChangeAppSettings::ChangeTextColorChoice addedTextColorChoice,
						ITrackChangeAppSettings::ChangeBackgroundColorChoice addedBGColorChoice,
						ITrackChangeAppSettings::ChangeTextColorChoice deletedTextColorChoice,
						ITrackChangeAppSettings::ChangeBackgroundColorChoice deletedBGColorChoice,
						ITrackChangeAppSettings::ChangeTextColorChoice movedTextColorChoice,
						ITrackChangeAppSettings::ChangeBackgroundColorChoice movedBGColorChoice
					) = 0;
						
	/**
		added text should show or not (when changes are showing)
		@param showAdded whether or not to show added text
	*/
	virtual void SetShowAddedText(const bool16 showAdded) = 0;
	/**
		deleted text should show or not (when changes are showing)
		@param showDeleted whether or not to show deleted text
	*/
	virtual void SetShowDeletedText(const bool16 showDeleted) = 0;
	/**
		moved text should show or not (when changes are showing)
		@param showMoved whether or not to show moved text
	*/
	virtual void SetShowMovedText(const bool16 showMoved) = 0;
	/**
		change bars should show or not (when changes are showing)
		@param showChangeBars whether or not to show change bars
	*/
	virtual void SetShowChangeBars(const bool16 showChangeBars) = 0;
	/**
		change bar color
		@param val color index
	*/
	virtual void SetChangeBarColorIndex(const int32 val) = 0;
	/**
		deleted text should be included in spell checking or not
		@param val whether or not to spell check deleted text
	*/
	virtual void SetSpellChkDeletedText(const bool16 val) = 0;
	/**
		prevent duplicate user color or not
		@param val whether or not to prevent duplicate user color
	*/
	virtual void SetPreventDupeColor(const bool16 val) = 0;
	/**
		text color for added text
		@param colorIndex
	*/
	virtual void SetAddedTextColorIndex(const int32 colorIndex) = 0;
	/**
		background color for added text
		@param colorIndex
	*/
	virtual void SetAddedBGColorIndex(const int32 colorIndex) = 0;
	/**
		text color for deleted text
		@param colorIndex
	*/
	virtual void SetDeletedTextColorIndex(const int32 colorIndex) = 0;
	/**
		background color for deleted text
		@param colorIndex
	*/
	virtual void SetDeletedBGColorIndex(const int32 colorIndex) = 0;
	/**
		text color for moved text
		@param colorIndex
	*/
	virtual void SetMovedTextColorIndex(const int32 colorIndex) = 0;
	/**
		background color for moved text
		@param colorIndex
	*/
	virtual void SetMovedBGColorIndex(const int32 colorIndex) = 0;
	/**
		marking for added text
		@param marking
	*/
	virtual void SetAddedTextMarking(const int32 marking) = 0;
	/**
		marking for deleted text
		@param marking
	*/
	virtual void SetDeletedTextMarking(const int32 marking) = 0;
	/**
		marking for moved text
		@param marking
	*/
	virtual void SetMovedTextMarking(const int32 marking) = 0;
	/**
		location for change bar
		@param location
	*/
	virtual void SetChangeBarLocation(const int32 location) = 0;
	/**
		text color choice for added text
		@param colorChoice
	*/
	virtual void SetAddedTextColorChoice(const ITrackChangeAppSettings::ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for added text
		@param colorChoice
	*/
	virtual void SetAddedBGColorChoice(const ITrackChangeAppSettings::ChangeBackgroundColorChoice colorChoice) = 0;
	/**
		text color choice for Deleted text
		@param colorChoice
	*/
	virtual void SetDeletedTextColorChoice(const ITrackChangeAppSettings::ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for Deleted text
		@param colorChoice
	*/
	virtual void SetDeletedBGColorChoice(const ITrackChangeAppSettings::ChangeBackgroundColorChoice colorChoice) = 0;
	/**
		text color choice for Moved text
		@param colorChoice
	*/
	virtual void SetMovedTextColorChoice(const ITrackChangeAppSettings::ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for Moved text
		@param colorChoice
	*/
	virtual void SetMovedBGColorChoice(const ITrackChangeAppSettings::ChangeBackgroundColorChoice colorChoice) = 0;

	/**
		added text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual const bool16 GetShowAddedText() const = 0;
	/**
		deleted text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual const bool16 GetShowDeletedText() const = 0;
	/**
		moved text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual const bool16 GetShowMovedText() const = 0;
	/**
		change bars should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual const bool16 GetShowChangeBars() const = 0;
	/**
		change bar color
		@return color index
	*/
	virtual const int32 GetChangeBarColorIndex() const = 0;
	/**
		deleted text should be included in spell checking or not
		@return kTrue if deleted text is included
	*/
	virtual const bool16 GetSpellChkDeletedText() const = 0;
	/**
		prevent duplicate user color or not
		@return kTrue to prevent duplicate user color
	*/
	virtual const bool16 GetPreventDupeColor() const = 0;
	/**
		text color for added text
		@return color index
	*/
	virtual const int32 GetAddedTextColorIndex() const = 0;
	/**
		background color for added text
		@return color index
	*/
	virtual const int32 GetAddedBGColorIndex() const = 0;
	/**
		text color for deleted text
		@return color index
	*/
	virtual const int32 GetDeletedTextColorIndex() const = 0;
	/**
		background color for deleted text
		@return color index
	*/
	virtual const int32 GetDeletedBGColorIndex() const = 0;
	/**
		text color for moved text
		@return color index
	*/
	virtual const int32 GetMovedTextColorIndex() const = 0;
	/**
		background color for moved text
		@return color index
	*/
	virtual const int32 GetMovedBGColorIndex() const = 0;
	/**
		marking for added text
		@return marking
	*/
	virtual const int32 GetAddedTextMarking() const = 0;
	/**
		marking for deleted text
		@return marking
	*/
	virtual const int32 GetDeletedTextMarking() const = 0;
	/**
		marking for moved text
		@return marking
	*/
	virtual const int32 GetMovedTextMarking() const = 0;
	/**
		location for change bar
		@return location
	*/
	virtual const int32 GetChangeBarLocation() const = 0;
	/**
		text color choice for added text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeTextColorChoice GetAddedTextColorChoice() const = 0;
	/**
		background color choice for added text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeBackgroundColorChoice GetAddedBGColorChoice() const = 0;
	/**
		text color choice for Deleted text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeTextColorChoice GetDeletedTextColorChoice() const = 0;
	/**
		background color choice for Deleted text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeBackgroundColorChoice GetDeletedBGColorChoice() const = 0;
	/**
		text color choice for Moved text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeTextColorChoice GetMovedTextColorChoice() const = 0;
	/**
		background color choice for Moved text
		@return color choice
	*/
	virtual const ITrackChangeAppSettings::ChangeBackgroundColorChoice GetMovedBGColorChoice() const = 0;
};


#endif // __ITrackChangesPrefsCmdData__
