//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITrackChangeUtils.h $
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
#ifndef __ITRACKCHANGEUTILS__
#define __ITRACKCHANGEUTILS__

// ----- Interfaces -----
#include "IInterfaceColors.h"

// ----- Includes -----
#include "redlineiterator.h"

// ----- Utility files -----
#include "WideString.h"

// ----- ID.h files -----
#include "InCopySharedID.h"


class ITextModel;

/**
	ITrackChangeUtils is an aggregrate of many different utility functions centered
	around track changes feature.
*/

class ITrackChangeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRACKCHANGEUTILS };

	/**
		Checks application preference for show/hide track changes.  
		@return kTrue if showing changes
	*/
	virtual bool16 MarkAnyChanges() = 0;

	/**
		Checks application preferences for show/hide track changes and
		show/hide deleted text.  
		@return kTrue if showing changes and deleted text
	*/
	virtual bool16 MarkDeleteChanges() = 0;

	/**
		Checks application preferences for show/hide track changes and
		show/hide added text.  
		@return kTrue if showing changes and added text
	*/
	virtual bool16 MarkInsertChanges() = 0;

	/**
		Checks application preferences for show/hide track changes and
		show/hide moved text.  
		@return kTrue if showing changes and moved text
	*/
	virtual bool16 MarkMoveChanges() = 0;

	/**
		Checks application preferences for show/hide track changes and
		show/hide change bars.  
		@return kTrue if showing changes and change bars
	*/
	virtual bool16 ShowChangeBars() = 0;

	/**
		Returns the text color for the change.  
		@param db database of the story
		@param iterator redline iterator at the change to interrogate
		@return text color
	*/
	virtual RealAGMColor GetTrackedChangeTextColor(IDataBase *db, RedlineIterator *iterator) = 0;

	/**
		Returns the background color for the change.  
		@param db database of the story
		@param iterator redline iterator at the change to interrogate
		@return background color
	*/
	virtual RealAGMColor GetTrackedChangeBGColor(IDataBase *db, RedlineIterator *iterator) = 0;

	/**
		Returns the marking for the change.  
		@param db database of the story
		@param iterator redline iterator at the change to interrogate
		@return marking
	*/
	virtual int32 GetTrackedChangeMarking(IDataBase *db, RedlineIterator *iterator) = 0;

	/**
		Returns deleted text in the form of a widestring  
		@param textModel
		@param anchorPosition
		@param newString
		@return UIDRef of the deleted text story thread
	*/
	virtual UIDRef GetDeletedText(ITextModel* textModel, TextIndex anchorPosition, WideString& newString) = 0;

	/**
		Returns deleted text in the form of a widestring  
		@param textModel
		@param anchorPosition
		@param newString
		@return UIDRef of the deleted text story thread
	*/
	virtual UIDRef GetDeletedText(ITextModel* textModel,  TextIndex anchorPosition, PMString& newString) = 0;

	/**
		Returns active story UIDRef, calls GalleyUtils::GetCurrentTextSelection 
		@return UIDRef of the active story
	*/
	virtual UIDRef GetActiveStoryRef() = 0;

	/**
		Checks to see if the active story has any changes. Changes in hidden conditional text are ignored.
		@return kTrue if story has changes
	*/
	virtual bool16 ActiveStoryHasChanges() = 0;

	/**
		Checks to see if the active story has any changes that are hidden according to track change app settings.
		Changes in hidden conditional text are ignored.
		@return kTrue if story has changes that are hidden
		@see ITrackChangeAppSettings
	*/
	virtual bool16 ActiveStoryHasChangesHidden() = 0;

	/**
		Checks to see if the specified story has any changes. Changes in hidden conditional text are ignored.
		@param storyRef UIDRef of the story to evaluate
		@return kTrue if story has changes
	*/
	virtual bool16 StoryHasChanges(UIDRef storyRef) = 0;

	/**
		Checks to see if the specified story has any changes that are hidden according to track change app settings.
		Changes in hidden conditional text are ignored.
		@param storyRef UIDRef of the story to evaluate
		@return kTrue if story has changes that are hidden
		@see ITrackChangeAppSettings
	*/
	virtual bool16 StoryHasChangesHidden(UIDRef storyRef) = 0;

	/**
		Checks to see if the specified text range has any changes.
		@param storyRef UIDRef of the story to evaluate
		@param startIndex start index of the range
		@param endIndex end index of the range
		@param convertedRange kTrue if the range is in deleted text
		@return kTrue if text range has changes
	*/
	virtual bool16 RangeHasChanges(UIDRef storyRef, TextIndex startIndex, TextIndex endIndex, bool16 convertedRange) = 0;
	
	/**
		Converts an index within deleted text to primary index (aka anchor position)
		@param IN textModel specifies the text model containing the table
		@param IN withinDeletedTextIndex text index to interrogate (will verify it is in deleted text)
		@param OUT threadStart of the deleted text story thread
		@param OUT threadSpan of the deleted text story thread
		@return primary story thread index (aka anchor position) of the deleted text
	*/
	virtual TextIndex DeletedTextToPrimaryIndex(ITextModel* textModel, TextIndex withinDeletedTextIndex, TextIndex* threadStart = nil, int32* threadSpan = nil) = 0;

	/**
		Checks for a deleted text owned item at the specified primary index (aka anchor position).
		@param IN textModel specifies the text model
		@param IN withinPrimaryIndex text index to interrogate
		@param OUT threadStart of the deleted text story thread (if found at primary index)
		@param OUT threadSpan of the deleted text story thread (if found at primary index)
		@return whether or not deletion found at primary index (aka anchor position)
	*/
	virtual bool16 PrimaryIndexToDeletedText(ITextModel* textModel, TextIndex withinPrimaryIndex, TextIndex* threadStart = nil, int32* threadSpan = nil) = 0;

#ifdef DEBUG
	/**
		Toggles whether or not to display track changes.  DEBUG ONLY.
		@return whether or not track changes should be displayed.
	*/
	virtual bool16 ToggleTrackChangeDisplay() = 0;
#endif
};

#endif // __ITRACKCHANGEUTILS__
