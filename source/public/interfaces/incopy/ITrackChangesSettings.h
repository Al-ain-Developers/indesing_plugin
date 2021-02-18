//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITrackChangesSettings.h $
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
//========================================================================================

#pragma once
#ifndef __ITrackChangesSettings__
#define __ITrackChangesSettings__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/**
	ITrackChangeAppSettings

	Represents information about the track changes settings for the application.
*/
class ITrackChangeAppSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRACKCHANGEAPPSETTINGS };

	enum ChangeBarLocation
	{ 
		/** Left */
		kLeftMargin,
		/** Right */
		kRightMargin
	};

	enum ChangeMarking
	{
		/** No marking */
		kNone,
		/** Text has strikethrough */
		kStrikethrough,
		/** Text has underline */
		kUnderline,
		/** Text has outline */
		kOutline
	};

	enum ChangeTextColorChoice
	{
		/** change text uses galley text color */
		kUseGalleyColor,
		/** change text uses change preference color */
		kUseChangePrefColor
	};

	enum ChangeBackgroundColorChoice
	{
		/** change background uses galley background color */
		kUseGalleyColorBG,
		/** change background uses user color */
		kUseUserColorBG,
		/** change background uses change preference color */
		kUseChangePrefColorBG
	};

	/**
		deleted text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual bool16 GetShowDeletedText() const = 0;
	/**
		deleted text should show or not (when changes are showing)
		@param whether or not to show deleted text
	*/
	virtual void SetShowDeletedText(bool16 showDeletedText) = 0;

	/**
		added text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual bool16 GetShowAddedText() const = 0;
	/**
		added text should show or not (when changes are showing)
		@param whether or not to show added text
	*/
	virtual void SetShowAddedText(bool16 showAddedText) = 0;

	/**
		moved text should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual bool16 GetShowMovedText() const = 0;
	/**
		moved text should show or not (when changes are showing)
		@param whether or not to show moved text
	*/
	virtual void SetShowMovedText(bool16 showMovedText) = 0;

	/**
		change bars should show or not (when changes are showing)
		@return kTrue if deleted text is showing
	*/
	virtual bool16 GetShowChangeBars() const = 0;
	/**
		change bars should show or not (when changes are showing)
		@param whether or not to show change bars
	*/
	virtual void SetShowChangeBars(bool16 showChangeBars) = 0;
	
	/**
		change bar color
		@return color index
	*/
	virtual int32 GetChangeBarColorIndex() const = 0;
	/**
		change bar color
		@param color index
	*/
	virtual void SetChangeBarColorIndex(int32 colorIndex) = 0;

	/**
		user can turn on/off track changes; for system integrators to modify the app default behavior
		@return kTrue is user can turn on or off
	*/
	virtual bool16 GetUserCanTurnOnOffTrackChanges () const = 0;
	/**
		user can turn on/off track changes; for system integrators to modify the app default behavior
		@param whether or not user can turn on/off
	*/
	virtual void SetUserCanTurnOnOffTrackChanges (bool16 canTOO) = 0;
	
	/**
		user can accept/reject track changes; for system integrators to modify the app default behavior
		@return kTrue is user can accept or reject
	*/
	virtual bool16 GetUserCanAcceptRejectChanges () const = 0;
	/**
		user can accept/reject track changes; for system integrators to modify the app default behavior
		@param whether or not user can accept/reject
	*/
	virtual void SetUserCanAcceptRejectChanges (bool16 canAR) = 0;

	/**
		the application tracking state; used to initialize new stories tracking state in incopy
		@return kTrue if tracking is enabled
	*/
	virtual bool16 GetTrackingState () const = 0;
	/**
		the application tracking state; used to initialize new stories tracking state in incopy
		@param whether or not to track changes
	*/
	virtual void SetTrackingState (bool16 trackingState) = 0;
	
	/**
		deleted text should be included in spell checking or not
		@return kTrue if deleted text is included
	*/
	virtual bool16 GetSpellChkDeletedText () const = 0;
	/**
		deleted text should be included in spell checking or not
		@param whether or not to show change bars
	*/
	virtual void SetSpellChkDeletedText (bool16 spellchkState) = 0;

	/**
		prevent duplicate user color or not for tracked changes background color
		@return kTrue to prevent duplicate user color
	*/
	virtual bool16 GetPreventDupeColor () const = 0;
	/**
		prevent duplicate user color or not for tracked changes background color
		@param whether or not to prevent duplicate user color
	*/
	virtual void SetPreventDupeColor (bool16 preventDupeColor) = 0;

	/**
		text color for added text
		@return color index
	*/
	virtual int32 GetAddedTextColorIndex() const = 0;
	/**
		text color for added text
		@param color index
	*/
	virtual void SetAddedTextColorIndex(int32 colorIndex) = 0;
	/**
		background color for added text
		@return color index
	*/
	virtual int32 GetAddedBGColorIndex() const = 0;
	/**
		background color for added text
		@param color index
	*/
	virtual void SetAddedBGColorIndex(int32 colorIndex) = 0;

	/**
		text color for deleted text
		@return color index
	*/
	virtual int32 GetDeletedTextColorIndex() const = 0;
	/**
		text color for deleted text
		@param color index
	*/
	virtual void SetDeletedTextColorIndex(int32 colorIndex) = 0;
	/**
		background color for deleted text
		@return color index
	*/
	virtual int32 GetDeletedBGColorIndex() const = 0;
	/**
		background color for deleted text
		@param color index
	*/
	virtual void SetDeletedBGColorIndex(int32 colorIndex) = 0;

	/**
		text color for moved text
		@return color index
	*/
	virtual int32 GetMovedTextColorIndex() const = 0;
	/**
		text color for moved text
		@param color index
	*/
	virtual void SetMovedTextColorIndex(int32 colorIndex) = 0;
	/**
		background color for moved text
		@return color index
	*/
	virtual int32 GetMovedBGColorIndex() const = 0;
	/**
		background color for moved text
		@param color index
	*/
	virtual void SetMovedBGColorIndex(int32 colorIndex) = 0;

	/**
		marking for added text
		@return marking
	*/
	virtual int32 GetAddedTextMarking() const = 0;
	/**
		marking for added text
		@param marking
	*/
	virtual void SetAddedTextMarking(int32 marking) = 0;

	/**
		marking for deleted text
		@return marking
	*/
	virtual int32 GetDeletedTextMarking() const = 0;
	/**
		marking for deleted text
		@param marking
	*/
	virtual void SetDeletedTextMarking(int32 marking) = 0;

	/**
		marking for moved text
		@return marking
	*/
	virtual int32 GetMovedTextMarking() const = 0;
	/**
		marking for moved text
		@param marking
	*/
	virtual void SetMovedTextMarking(int32 marking) = 0;

	/**
		location for change bar
		@return location
	*/
	virtual int32 GetChangeBarLocation() const = 0;
	/**
		location for change bar
		@param location
	*/
	virtual void SetChangeBarLocation(int32 location) = 0;

	/**
		text color choice for added text
		@return color choice
	*/
	virtual ChangeTextColorChoice GetAddedTextColorChoice() const = 0;
	/**
		text color choice for added text
		@param color choice
	*/
	virtual void SetAddedTextColorChoice(ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for added text
		@return color choice
	*/
	virtual ChangeBackgroundColorChoice GetAddedBGColorChoice() const = 0;
	/**
		background color choice for added text
		@param color choice
	*/
	virtual void SetAddedBGColorChoice(ChangeBackgroundColorChoice colorChoice) = 0;

	/**
		text color choice for Deleted text
		@return color choice
	*/
	virtual ChangeTextColorChoice GetDeletedTextColorChoice() const = 0;
	/**
		text color choice for Deleted text
		@param color choice
	*/
	virtual void SetDeletedTextColorChoice(ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for Deleted text
		@return color choice
	*/
	virtual ChangeBackgroundColorChoice GetDeletedBGColorChoice() const = 0;
	/**
		background color choice for Deleted text
		@param color choice
	*/
	virtual void SetDeletedBGColorChoice(ChangeBackgroundColorChoice colorChoice) = 0;

	/**
		text color choice for Moved text
		@return color choice
	*/
	virtual ChangeTextColorChoice GetMovedTextColorChoice() const = 0;
	/**
		text color choice for Moved text
		@param color choice
	*/
	virtual void SetMovedTextColorChoice(ChangeTextColorChoice colorChoice) = 0;
	/**
		background color choice for Moved text
		@return color choice
	*/
	virtual ChangeBackgroundColorChoice GetMovedBGColorChoice() const = 0;
	/**
		background color choice for Moved text
		@param color choice
	*/
	virtual void SetMovedBGColorChoice(ChangeBackgroundColorChoice colorChoice) = 0;
};


/**
	ITrackChangeStorySettings

	Represents information about the track changes settings for the story.
*/
class ITrackChangeStorySettings : public IPMUnknown
{
	public:
	enum { kDefaultIID = IID_ITRACKCHANGESTORYSETTINGS };

	/**
		the story tracking state
		@return kTrue if changes are being tracked
	*/
	virtual bool16 GetIsTracking() const = 0;
	/**
		the story tracking state
		@param whether or not changes should be tracked
	*/
	virtual void SetIsTracking(bool16 isTracking) = 0;

	/**
		this is an indicator that track change data should be preserved - currently
		used to distiguish when importing an incopy file so the source track change data 
		is transferred to the destination story we also use this same flag to determine 
		if other story level settings should be copied when placing such as opt margin 
		alignment and story label
		@return kTrue if track change data should be preserved
	*/
	virtual bool16 GetPreserveTrackChangeData() const = 0;
	/**
		this is an indicator that track change data should be preserved - currently
		used to distiguish when importing an incopy file so the source track change data 
		is transferred to the destination story we also use this same flag to determine 
		if other story level settings should be copied when placing such as opt margin 
		alignment and story label
		@param whether or not to preserve track change data
	*/
	virtual void SetPreserveTrackChangeData(bool16 preserveData) = 0;
};

#endif // __ITrackChangesSettings__
