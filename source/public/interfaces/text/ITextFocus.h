//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFocus.h $
//  
//  Owner: Eric_Kenninga
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
#ifndef __ITextFocus__
#define __ITextFocus__

#include "IPMUnknown.h"
#include "TextID.h"
#include "RangeData.h"
#include "ITextFocusManager.h"
class ITextModel;

/** This interface describes a text selection. It describes the start, end
	and the story selected. There are methods to get and set the range.
	In the current implementation, the TextModel has a TextFocusManager
	that maintains the foci positions during editing.
	@ingroup text_focus
	@see ITextModel
	@see ITextFocusManager
	@see RangeData
*/
class ITextFocus : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTFOCUS };

		/** Initialize the TextFocus. DO NOT call this to move a selection from one model to another,
			that isn't supported, and is done through ITextFocusManager.
			@param model is the textModel.
			@range is the selection start/end.
		*/
		virtual void		Initialize(ITextModel* model, const RangeData& range) = 0;

		/** Query for the TextModel from this focus
			@return an AddRef'd ITextModel for this focus.
		*/
		virtual ITextModel*	QueryModel() const = 0;

		/** This function must be called before the text focus scope changes.
		Provide an implementation of PreDirty that will help restore the text focus at undo and redo.
		*/

		virtual void		PreDirtyFocus() = 0;

		virtual void		SetRange(bool16 allowNotify, const RangeData& range, bool16 excludeCacheEnd = kTrue) = 0;

		/** Get the range of text in the selection.
			@return the selected range.
		*/
		virtual RangeData	GetCurrentRange() const = 0;

		/** Get the start of the selection. Lean indicates whether the caret "sticks" left or right. This
			affects shift selecting among other things.
			@param lean is set based on the direction stickiness of the selection.
			@return the starting text index.
		*/
		virtual TextIndex	GetStart(RangeData::Lean* lean) const = 0;

		/** Get the end of the selection.
			@return the ending text index.
		*/
		virtual TextIndex	GetEnd() const = 0;

		/** Get whether a range of text is selected. The alternative is a caret.
			@return kTrue is the selection is more than just a caret.
		*/
		virtual bool16		IsRange() const = 0;

		/** Get the number of characters selected. Length() > 0 == IsRange().
			@return the number of selected characters.
		*/
		virtual uint32		Length() const = 0;

		/** Only called by the TextFocusManager to maintain foci during editing.
			@param start is the location of the insert.
			@param count is the number of characters inserted.
			@param allowNotify tells whether to tell the focus cache about the change.
		*/
		virtual void		Inserted(TextIndex start, int32 count, bool16 allowNotify) = 0;

		/** Only called by the TextFocusManager to maintain foci during editing.
			@param start is the location of the delete.
			@param count is the number of characters deleted.
			@param allowNotify tells whether to tell the focus cache about the change.
		*/
		virtual void		Deleted(TextIndex start, int32 count, bool16 allowNotify) = 0;

		/** Only called by the TextFocusManager to maintain foci during editing.
			@param updateInfoList is a list of changes.
			@param allowNotify tells whether to tell the focus cache about the change.
		*/
		virtual void		Update(const ITextFocusManager::FocusUpdateInfoList & updateInfoList, bool16 allowNotify) = 0;

		/** NotifyChanged is called during the undo/redo of certain Text editing operations to try and maintain a legal selection.
			@param excludeCacheEnd indicates whether the range-damage (IFocusCache) will damage when at the end.
		*/
		virtual void 		NotifyChanged(bool16 excludeCacheEnd = kTrue) = 0;
		virtual void		DeRegisterFromModel(void) = 0;
};

#endif
		// __ITextFocus__

