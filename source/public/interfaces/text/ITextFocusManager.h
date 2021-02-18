//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFocusManager.h $
//  
//  Owner: Eric Menninga
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
#ifndef __ITextFocusManager__
#define __ITextFocusManager__

#include "IPMUnknown.h"
#include "TextID.h"

//----------------------------------------------------------------------------------------
// Interface ITextFocusManager
//----------------------------------------------------------------------------------------

class ITextFocus;
class RangeData;

/** TextFocusManager maintains a list of ITextFocus objects and updates them accordingly
	when characters are inserted/deleted.  ITextFocusManager is an interface of the TextModelBoss.
	@see ITextFocus
	@see IFocusCache
	@ingroup text_focus
*/
class ITextFocusManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTFOCUSMANAGER };

		/** FocusUpdateType allows a series of changes to be done
			at one time -- e.g. a Change-All operation. */
	enum FocusUpdateType
	{
		kInvalidUpdateType = 0,
		kInserted,
		kDeleted,
		kAppliedAttrs
	};

		/** FocusUpdateInfo allows a series of changes to be done
			at one time -- e.g. a Change-All operation. */
	struct FocusUpdateInfo
		{
				/** FocusUpdateInfo is just raw data */
			typedef base_type data_type;

			FocusUpdateInfo(FocusUpdateType type, TextIndex start, int32 len)
					:fUpdateType(type), fStart(start), fLen(len)
				{}

			bool operator==(const FocusUpdateInfo&) const
				{ ASSERT_FAIL("appease K2Vector.Location"); return false; }

			FocusUpdateType	fUpdateType;
			TextIndex 		fStart;
			int32			fLen;
		};

		/** A list of FocusUpdateInfo allows a series of changes to be done
			at one time -- e.g. a Change-All operation. */
	typedef K2Vector<FocusUpdateInfo>	FocusUpdateInfoList;


		/** Create a new Text Focus managed by this list.
			@param range specifies where the TextFocus should be located.
			@focusClass allows alternate TextFocusBoss classes to be used.
			@return an AddRef'd textfocus.
		*/
	virtual ITextFocus* 		NewFocus( const RangeData& range, ClassID focusClass = kInvalidClass) = 0;

		/** Add the pre-existing ITextFocus boss to this list. It is assumed that the text focus
			will be for this manager's story.
			@param f is the textfocus object to add.
		*/
	virtual void				AddFocus(ITextFocus* f) = 0;

		/** Remove the pre-existing ITextFocus boss from this list.
			@param f is the textfocus object to remove.
		*/
	virtual void				RemoveFocus(ITextFocus* f) = 0;

		/** Count how many text foci there are on this story, managed by this list.
			@return the number of text foci. */
	virtual int32				GetFocusCount() const = 0;

		/** Get one of the foci managed by this list.
			@param nAt is the index of the text foci requested.
			@return the n'th AddRef'd ITextFocus interface. */
	virtual ITextFocus *		QueryNthFocus( int32 nAt ) = 0;

		/** The textmodel calls this to adjust the textfoci to reflect text being inserted.
			@param start is the location of the insert.
			@param count is the number of characters inserted.
			@param allowNotify specifies whether the event should be broadcast. */
	virtual void				Inserted(TextIndex start, int32 count, bool16 allowNotify = kTrue) = 0;

		/** The textmodel calls this to adjust the textfoci to reflect text being deleted.
			@param start is the location of the delete.
			@param count is the number of characters deleted.
			@param allowNotify specifies whether the event should be broadcast. */
	virtual void				Deleted(TextIndex start, int32 count, bool16 allowNotify = kTrue) = 0;

		/** The textmodel calls this to adjust the textfoci to reflect text being formatted.
			@param start is the location of the format change.
			@param count is the number of characters changed..
			@param allowNotify specifies whether the event should be broadcast. */
	virtual void				AttributeApplied(TextIndex start, int32 count, bool16 allowNotify = kTrue) = 0;

		/** The textmodel calls this when new story threads are created.
			@param at is the location of the new story thread.
			@param len is the length of the new story thread. */
	virtual void				StoryThreadCreated(TextIndex at, int32 len) = 0;

		/** Update following a sequence of text model changes.
			@param updateInfoList is a list of operations performed.
			@param allowNotify specifies whether the event should be broadcast. */
	virtual void				Update(const FocusUpdateInfoList& updateInfoList, bool16 allowNotify) = 0;

 	virtual void				DeRegisterTextFoci() = 0;
};

#endif
	// __ITextFocusManager__

