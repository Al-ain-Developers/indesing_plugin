//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITrackChangeSuite.h $
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
#ifndef __ITrackChangeSuite__
#define __ITrackChangeSuite__

#include "IPMUnknown.h"
#include "InCopySharedID.h"
#include "redlineiterator.h"
#include "ITextModel.h"
#include "RangeData.h"

/**
	ITrackChangeSuite

	This is a suite for getting a setting track changes settings.
*/

class ITrackChangeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRACKCHANGESUITE };

	/**	Can accept the change(s) if story is unlocked and user has permissions (see ITrackChangesSettings.h)
		@param none
		@return bool16 
	 */
	virtual bool16 CanAccept() const = 0;

	/**	Can reject the change(s) if story is unlocked and user has permissions (see ITrackChangesSettings.h)
		@param none
		@return bool16 
	 */
	virtual bool16 CanReject() const = 0;

	/**	Accept the selected change(s)
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 Accept() = 0;

	/**	Reject the selected change(s)
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 Reject() = 0;

	/**	Accept the selected change(s) and go to next change
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 AcceptAndNext() = 0;

	/**	Reject the selected change(s) and go to next change
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 RejectAndNext() = 0;
	
	/**	Accept all changes in the active story
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 AcceptAll() = 0;

	/**	Reject all changes in the active story
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 RejectAll() = 0;

	/**	Accept all changes by the user of the active change in the active story
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 AcceptAllByUser() = 0;

	/**	Reject all changes by the user of the active change in the active story
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 RejectAllByUser() = 0;

	/**	Accept all changes in all the stories in the document
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 AcceptAllStories() = 0;

	/**	Reject all changes in all the stories in the document
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 RejectAllStories() = 0;

	/**	Accept all changes in all the stories by the user of the active change in the document
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 AcceptAllStoriesByUser() = 0;

	/**	Reject all changes in all the stories by the user of the active change in the document
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 RejectAllStoriesByUser() = 0;

	/**	Scroll to (if necessary) and hilite the next change
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 GotoNextChange() = 0;

	/**	Scroll to (if necessary) and hilite the previous change
		@param none
		@return bool16 indicating if action was handled or not
	 */
	virtual bool16 GotoPreviousChange() = 0;

	/**	Moves the deleted text selection (if any) to that deletion's anchor index
		in the primary story - caller can specify if selection should be moved only
		when deleted text is hidden.
		@param onlyWhenDeletedTextIsHidden kTrue to prevent moving selection when deletes are showing
		@return bool16 indicating if action was taken
	 */
	virtual bool16 DeletedTextSelectionToPrimaryIndex(bool16 onlyWhenDeletedTextIsHidden = kTrue) = 0;

	/**	Finds the previous track change (if any) given a redline iterator (this iterates change objects,
		a track change may be represented by one or more change objects which this util takes into
		account) and positions the iterator at the previous track change (if any).  It does not consider
		the change type visibility.
		@param redline iterator; positioned at previous change (if any) upon return to caller
		@return bool16 indicating if there is previous change
	 */
	virtual bool16  FindPreviousChange(RedlineIterator * iterator) = 0;

	/**	Finds the next track change (if any) given a redline iterator (this iterates change objects,
		a track change may be represented by one or more change objects which this util takes into
		account) and positions the iterator at the next track change (if any).  It does not consider
		the change type visibility.
		@param redline iterator; positioned at next change (if any) upon return to caller
		@return bool16 indicating if there is next change
	 */
	virtual bool16  FindNextChange(RedlineIterator * iterator) = 0;

	/**	Finds the next track change in the story (if any) given a redline iterator (this iterates change objects,
		a track change may be represented by one or more change objects which this util takes into
		account) and positions the iterator at the next track change (if any).  It does not consider
		the change type visibility.
		@param redline iterator; positioned at next change (if any) upon return to caller
		@param model story to find the next change
		@param range the range to start looking for next change
		@return bool16 indicating if there is next change
	 */
	virtual bool16 FindNextChangeInStory(RedlineIterator * iterator, const ITextModel* model, const RangeData& range) = 0;
};

#endif
