//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextModel.h $
//  
//  Owner: EricM
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
#ifndef __ITEXTMODEL__
#define __ITEXTMODEL__

#include "IPMUnknown.h"
#include "PMTextUtils.h"
#include "TextID.h"
#include "WideString.h"
#include "K2SmartPtr.h"
#include "ErrorUtils.h"
#include "ITextFocusManager.h"

class ICommand;
class AttributeBossList;
class ReplaceInfo;
class VOS_SavedData;
class PasteData;
class ILanguage;
class IParcel;
class ITextStoryThread;
class ITextParcelList;
class IFrameList;

/** This is the main interface for a text story. It has the following responsibilities:
	<ol>
	<li>Strand management: a story is represented by multiple strands of data
	 Text, Paragraph Attrs, Character Attrs, Story Thread, etc. Each strand
	is a separate boss, made available here.
	<li>Copying selections: a range can be copied into a fairly raw format
	PasteData that is pretty implementation restricted
	<li>The actual functions for major operations (insert, delete, paste, apply) are here.
	<li>A couple of misc functions: TotalLength() - number of chars in story including
	the non-editable, must-have carriage return at the end.
	</ol>
	Note: use ITextModelCmds to get to text edit commands.
	@ingroup text_story
*/
class ITextModel : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTMODEL };

		/**
			Returns the wax strand (a.k.a frame list) uid.
			The frame list is set by registering the frame list boss as a strand.
		*/
		virtual UID GetFrameListUID() const = 0;

		/**
			Returns a pointer to the wax strand boss.
		*/
		virtual IFrameList * QueryFrameList() const = 0;

		/**
			Returns the UID of the strand attached to the model that has a particular class.
			kInvalidUID is returned when no such a strand is found.
			@param klass IN strand class.
		*/
		virtual UID GetStrandFromClass(ClassID klass) const = 0;

		/**
			Returns a pointer to an interface on the strand attached to the model that has a particular class.
			@param clsID IN strand class.
			@param faceID IN id of an interface on the strand boss. When faceID is equal IID_IUNKOWN, a pointer to the strand boss is returned.
		*/
		virtual IPMUnknown *QueryStrand(ClassID clsID, PMIID faceID) const = 0;

		/**
			Returns a pointer to an interface on the Nth strand attached to the model.
			@param n IN strand index.
			@param faceID IN id of an interface on the strand boss. When faceID is equal IID_IUNKNOWN, a pointer to the strand boss is returned.
		*/
		virtual IPMUnknown *QueryNthStrand(int32 n, PMIID faceID) const = 0;

		/** Takes data from the model to store it in a stream (clipboard, database, ...)
			@param start IN start of copy range.
			@param length IN length of copy range.
			@param pasteData OUT is the copied data. It should be used by caller to paste the data
			somewhere else in the same story, another story in the same document, or
			another story in another document.
			pasteData is a shared pointer. @see K2SmartPtr.h for usage of shared_ptr.
			@return error code
		*/
		virtual ErrorCode CopyRange(TextIndex start, int32 length, boost::shared_ptr<PasteData>&pasteData ) = 0;

		/** Takes data from the model to store it in a stream (clipboard, database, ...)
			@param list IN list of ranges to copy from.
			@param pasteData OUT is the copied data. It should be used by caller to paste the data
			somewhere else in the same story, another story in the same document, or
			another story in another document.
			pasteData is a shared pointer. @see K2SmartPtr.h for usage of shared_ptr.
			@return error code
		*/
		virtual ErrorCode  CopyRange(Text::StoryRangeList* list, boost::shared_ptr<PasteData>&pasteData) = 0;

		/** Forces recomposition within a range.
		    Most operations do this automatically, sometimes damage must be forced. e.g. dragging an inline graphic.
			@param start IN start of recomposition range.
			@param len IN length of recomposition range.
		*/
		virtual void DoForceCompositionDamage(TextIndex start, int32 len) = 0;

        /** Forces recomposition within a range.
            Most operations do this automatically, sometimes damage must be forced. e.g. dragging an inline graphic.
            Incase where we do not want to delete wax line and merely want to invalidate so that it will be reconsidered for composition
            @param start IN start of recomposition range.
            @param len IN length of recomposition range.
        */
        virtual void DoForceContentDamage(TextIndex start, int32 len) = 0;

	//-------------------------------------------------------------------------------
	/**@name	Retrieve data functions */
	//@{-----------------------------------------------------------------------------
		/**
			Returns the total number of characters in the text model (including data for embedded tables).
		*/
		virtual int32 TotalLength() const = 0;

		/** Returns the total number of characters in the primary story thread.
			(It does not include any characters that are part of story threads for table cells.)
		*/
		virtual int32 GetPrimaryStoryThreadSpan() const = 0;

#ifdef ID_DEPRECATED
		// 11/26/07 dwaterfa: The ownership of this API, that is, who gets to
		// set it is unclear. Currently it is owned by InCopy. Our direction
		// is to remove this InCopy "special" and make them use the new change
		// counters.
		/**
			Returns the status set by the SetChanged function.
		*/
		virtual bool16 HasChanged() const = 0;
#endif

		/**
		The TextModel maintains a counter that will be incremented whenever
		a character is inserted, removed or replaced in the TextModel.
		@return Current counter value for Text Strand changes
		*/
		virtual uint32	GetTextChangeCount() const = 0;

		/**
		The TextModel maintains a counter that will be incremented whenever
		the effective attribute applied to any chracters may have changed.
		This includes changes to applied styles and overrides.
		@return Current counter value for Char/Para Attribute Strand changes
		*/
		virtual uint32	GetAttrChangeCount() const = 0;

		/**
		The TextModel maintains a counter that should be changed by entities
		which are associated with the TextModel, such as Inlines, Tables, etc,
		when some appropriate aspect of them changes. An easy example of this
		is Tables - a change to a Table stroke does represent an effective
		change to the TextModel, that is an export of the contents of the
		TextModel will be different after the change than before the change -
		and so the TableModel will use this counter to signal change.
		@return Current counter value for Non Text and Char/Para Attribute Strand changes
		*/
		virtual uint32	GetOtherChangeCount() const = 0;

		/**
		The TextModel maintains a counter that will be incremented for any
		change to the above counters, be it Text, Attribute or Other. This is
		intended to simplify most clients who are not interested in particular
		details.
		@return Current counter value for all changes
		*/
		virtual uint32	GetChangeCount() const = 0;

		/** Returns the boundaries of the wrapping paragraph.
		@param newstart IN specifies a position to look for paragraph boundaries.
		This argument is also an out argument. It returns the actual start of the paragraph.
		@param newlen OUT returns the actual length of the paragraph.
		*/
		virtual void GetSurroundingParaBoundaries(int32& newstart, int32& newlen) const = 0;

		/** Gets the offset boundaries of a storythread.
			@param threadDictUID IN thread disctionary uid.
			@param threadDictKey IN, thread dictionary key.
			@param pStart OUT start of range
			@param pSpan OUT span of range.
		*/
		virtual bool16 FindStoryThread(UID threadDictUID, uint32 threadDictKey,
											TextIndex *pStart = nil,
											int32 *pLen = nil) const = 0;

		/** Returns a pointer to the storythread at a particular text index
			@param at IN text index where to look for storythread.
			@param pStart OUT start of storythread range.
			@param pSpan OUT length of storythread range.
		*/
		virtual ITextStoryThread* QueryStoryThread(TextIndex at,
											TextIndex *pStart = nil,
											int32 *pSpan = nil) const = 0;

		/** Gets the range of a storythread
			@param at IN text index where to look for storythread.
			@param pStart OUT start of storythread range.
			@param pSpan OUT length of storythread range.
		*/

		virtual int32	GetStoryThreadSpan(TextIndex at, TextIndex *pStart,
											int32 *pSpan = nil) const = 0;

		/**
			Returns range of storythread
			@param at IN text index where to look for storythread.
		*/
		virtual RangeData GetStoryThreadRange(TextIndex at) const = 0;

		/**
			Returns the story thread style at a particular index (a UID for an object that implements ITextAttributes).
			Optionally a start and a span are returned through runStart and runSpan.
			This start and span forms a run of adjoining story threads that have
			the same story thread styles.
			@param at IN The index to get the story thread style for.
			@param pStart OUT the index this story thread style begins being good for.
			@param pSpan OUT how far from runStart is this story thread applied.
		*/
		virtual UID GetStoryThreadStyle(TextIndex at , TextIndex * pStart = nil, TextIndex * pSpan = nil) const = 0;

		/**
			Returns a pointer to the text parcel list at an offset.
			@param at IN text index to look for parcel list.
		*/
		virtual ITextParcelList* QueryTextParcelList(TextIndex at) const = 0;
	//@}-----------------------------------------------------------------------------

#ifdef DEBUG
	//-------------------------------------------------------------------------------
	/**@name	Internal use only */
	//@{-----------------------------------------------------------------------------
		virtual	void	LockModel( bool16 bLock ) = 0;
		virtual	bool16	IsModelLocked() const = 0;
	//@}-----------------------------------------------------------------------------
#endif

public:
	//-------------------------------------------------------------------------------
	/**@name	Text operations
			The following functions perform specific text operations.
			The parameter is false when the client wants irreversible changes.
			The case of parameter true is currently exclusive to internal use.
			ErrorCode returns the global error state which may be set if embedded commands fail.
		*/
	//@{-----------------------------------------------------------------------------

		/**
			Insert string at a text index.
			@param start IN insert position.
			@param data IN string to insert.
			@param language IN language of text inserted.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Insert(TextIndex start, const WideString* data, const ILanguage *language = nil ) = 0;

		/**
			Delete text range from story
			@param start IN range start.
			@param len IN range len.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Delete( TextIndex start, int32 len) = 0;

		/**
			Delete text range.
			@param range IN range to delete.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Delete(const RangeData& range) = 0;

		/**
			Cut range of text from story.
			@param start IN start of cut range.
			@param len IN length of cut range.
			@param pasteData OUT is the cut data. It should be used by caller to paste the data
			somewhere else in the same story, another story in the same document, or
			another story in another document.
			pasteData is a shared pointer. @see K2SmartPtr.h for usage of shared_ptr.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Cut(TextIndex start, int32 len, boost::shared_ptr<PasteData>& pasteData) = 0;

		/**
			Cut range of text from story.
			@param range IN cut range.
			@param pasteData OUT is the cut data. It should be used by caller to paste the data
			somewhere else in the same story, another story in the same document, or
			another story in another document.
			pasteData is a shared pointer. @see K2SmartPtr.h for usage of shared_ptr.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Cut(const RangeData& range, boost::shared_ptr<PasteData>& pasteData) = 0;

		/**
			Replace text in a range
			@param start IN replace range start.
			@param len IN replace range length.
			@param data IN replacement string.
			@param language IN replacement string language.
			@param clearNonContinuingAttrs IN whether non-continuing attributes should be cleared after insert.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Replace(TextIndex start,
										 int32 len,
										 const WideString *data,
										 const ILanguage *language = nil,
										 bool16 clearNonContinuingAttrs = kTrue) = 0;

		/**
			Paste data into story.
			@param start IN insertion position.
			@param data IN paste data to insert. data is a shared pointer.
			@see K2SmartPtr.h for usage of shared_ptr.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode Paste(TextIndex start, const boost::shared_ptr<PasteData>& data) = 0;

		/**
			Apply style to a range.
			@param start IN start of apply range.
			@param len IN length of apply range.
			@param styleref IN style to apply.
			@param which IN whether this is a character or a paragraph style.
			@param destroyAll IN whether overrides must be removed along with the application of the style.
			@param keepOldStyleAsOverrides IN whether to apply current style as overrides before setting new style.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode ApplyStyle(TextIndex start, int32 len, UID styleref, ClassID which, bool16 destroyAll, bool16 keepOldStyleAsOverrides = kTrue) = 0;

		/**
			Apply attribute boss list to a range.
			@param start IN start of apply range.
			@param len IN length of apply range.
			@param these IN attribute boss list to apply.
			@param which IN indicates whether the applied attributes are paragraph or character attributes.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode ApplyOverrides(TextIndex start, int32 len, const AttributeBossList *these, ClassID which) = 0;

		/**
			Clear attribute boss list from range.
			@param start IN start of clear range.
			@param length IN length of clear range.
			@param these IN attribute boss list to clear.
			@param which IN whether the attributes to clear are paragraph or character attributes.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode ClearOverrides(TextIndex start, int32 length, const AttributeBossList *these, ClassID which) = 0;

		/**
			Insert a new StoryThread.
			There are a few restrictions :
			start must be the first TextIndex after an existing StoryThread.
			This means you are either inserting at the beginning of any
			StoryThread other than the one at TextIndex 0 or you are at
			the end of the TextModel (at TotalLength()).
			Note that this is the only permitted way to insert past the end of the TextModel.
			@param start IN insert position.
			@param threadDictUID IN thread disctionary uid.
			@param threadDictKey IN, thread dictionary key.
			@param data IN string to insert.
			@param language IN of inserted string. It must end with a carriage return.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode InsertStoryThread(TextIndex start,
											UID threadDictUID,
											uint32 threadDictKey,
											const WideString* data,
											const ILanguage* language=nil) = 0;

		/**
			Create one or more StoryThreads sharing the same Dictionary uid
			There are a few restrctions: start must be > 1. There must be a CR at (start - 1).
			Each threadLenList[] value must be at least 1 and there must be a CR at the end of each new StoryThread.
			This method does not change the length of the TextModel.
			@param start IN insert position.
			@param threadDictUID IN thread disctionary uid.
			@param threadDictKeyList IN story thread key list.
			@param threadLenList IN story thread length list.
			@return whether the operation succeeded or failed.
			*/
		virtual ErrorCode	CreateStoryThreads(TextIndex start,
									UID threadDictUID,
									const K2Vector<uint32>& threadDictKeyList,
									const K2Vector<int32>& threadLenList) = 0;

		/**
			The inverse of CreateStoryThread.
			The span of the joined StoryThread(s) are given back to the preceding StoryThread.
			This method does not change the length of the TextModel.
			@param start IN start join range.
			@param len IN length of join range.
			@return whether the operation succeeded or failed.
			*/
		virtual ErrorCode JoinStoryThreads(TextIndex start, int32 len) = 0;

		/**
			Attach strand to text model.
			@param strand IN strand uid.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode RegisterStrand(UID strand) = 0;

		/**
			Detach strand from text model.
			@param strand IN strand uid.
			@return whether the operation succeeded or failed.
		*/
		virtual ErrorCode UnregisterStrand(UID strand) = 0;

		/**
			Remove redundant overrides from range.
			These are the overrides that have no effect because they exist in the applied styles.
			@param start IN range start
			@param len IN range length.
			@return whether the operation succeeded or failed.
			*/
		virtual ErrorCode RemoveRedundantOverrides
			(TextIndex start, int32 len) = 0;

#ifdef ID_DEPRECATED
		// 11/26/07 dwaterfa: The ownership of this API, that is, who gets to
		// set it is unclear. Currently it is owned by InCopy. Our direction
		// is to remove this InCopy "special" and make them use the new change
		// counters.
		/**
			Indicate the start/end of text model changes
			@param changed IN whether changing the model.
		*/
		virtual void SetChanged(bool16 changed = kTrue) = 0;
#endif

		/**
		Increments the changed counter associated with Char/Para Attr changes. 
		The TextModel will handle this internally for normal sorts of applies
		but actions that take place outside the view of the TextModel, such as
		Style deletion, must result in a call to this method.
		@return The previous value of the attr changed counter
		*/
		virtual uint32	IncrementAttrChangeCount() = 0;

		/**
		Increments the change counter associated with non Text and Char/Para
		Attr changes. 
		@return The previous value of the other change counter
		*/
		virtual uint32	IncrementOtherChangeCount() = 0;

		/**
			Typically used when multiple replacement operatations must be performed on the text model.
			SingleReplacementInfo describes one text replacement. fPosition is the
			offset of the replacement. fFoundStringLen is the length of the replaced text.
			fReplacementStringLen is the length of the replacement string, and fReplacementString
			is the actual string.
		*/
		struct SingleReplacementInfo
		{
			typedef object_type				data_type;

			SingleReplacementInfo():
				fPosition(kInvalidTextIndex),
				fFoundStringLen(0),
				fReplacementStringLen(0),
				fReplacementString()
			{}

			SingleReplacementInfo(const SingleReplacementInfo& rVal):
				fPosition(rVal.fPosition),
				fFoundStringLen(rVal.fFoundStringLen),
				fReplacementStringLen(rVal.fReplacementStringLen),
				fReplacementString(rVal.fReplacementString)
			{}

			TextIndex						fPosition;
			int32							fFoundStringLen;
			int32							fReplacementStringLen;
			boost::shared_ptr<WideString>		fReplacementString;
		};

		typedef  K2Vector<SingleReplacementInfo > ReplacementList;

		/**
			Used to perform a set of replacements on the text model.
			This is an optmized form for doing multiple replacements.
			The list of ranges must be in ascending text index order.
			@param replacementList IN list of ranges and replacement strings.
			This is a shared_ptr. @see K2SmartPtr.h for usage of shared_ptr.
			@return whether the operation succeeded or failed.
			*/
		virtual ErrorCode Replace(const boost::shared_ptr<ReplacementList>& replacementList,
									const ILanguage *language,
 									bool16 clearNonContinuingAttrs = kTrue) = 0;
		virtual void StartRecordingChanges_ForUndoRedo() = 0;
		virtual void EndRecordingChanges_ForUndoRedo() = 0;
	//@}-----------------------------------------------------------------------------

};

#endif
