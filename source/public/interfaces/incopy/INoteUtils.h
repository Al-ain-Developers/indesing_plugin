//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteUtils.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __INOTEUTILS__
#define __INOTEUTILS__

#include "NoteID.h"

//-----------------------------------
//	Forward References
//
class IControlView;
class IMultiColumnTextFrame;
class ITextModel;
class IWaxStrand;
class PMPoint;
class PMString;
class IDocument;
class IGalleySwitch;
class INoteStringAttribute;
class IFrameList;
class IMasterSpreadList;
class IHierarchy;
class PMRect;
class IDocumentPresentation;
class INoteData;
class WideString;
class RangeData;


#include "IPMUnknown.h"
#include "UIDList.h"

/** Utility interface for Notes.
*/
class INoteUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INOTEUTILS };
		

/**	Convert tip content into meaningful display characters.
	@param inString 
	@param inBufLength 
	@param outBuffer 
 */
		virtual void ConvertNoteTipText(const uchar16* inString, int32& inBufLength, PMString& outBuffer) = 0;

/**	Query Note data by given the text index 
	@param textModel 
	@param noteDataIndex 
	@return INoteData* 
 */
		virtual INoteData* QueryNoteData(const ITextModel* textModel, const TextIndex noteDataIndex) = 0;

/**	Query Note data by given noteDataRef
	@param noteDataRef 
	@return INoteData* 
 */
		virtual INoteData* QueryNoteData(const UIDRef& noteDataRef) = 0;

/**	Get Note data by given offset
	@param textModel 
	@param offset 
	@return INoteData* 
 */
		virtual INoteData* GetNoteData(ITextModel* textModel, TextIndex offset) = 0;


/**	Convert a SysPoint from global coordinate to a local coordinate in the
	controlView context.
	@param controlView 
	@param globalPoint 
	@return  
 */
		virtual SysPoint 	GlobalToLocal(IControlView* controlView, SysPoint globalPoint) = 0;
					// Convert a SysPoint from global coordinate to a local coordinate in the
					// controlView context.


/**	With the given locaiton in "where", this method performs a hittest RangeData
	over the controlView.
	If found, it returns the hittest text range and
	the resulting text frame
	If not found, it returns a nil text frame.
	"ComposeFirst" allows the text system to force recompose the
	story in order to get accurate information.	
	@param controlView 
	@param where 
	@param caret 
	@param composeFirst 
	@return IMultiColumnTextFrame* 
 */
		virtual IMultiColumnTextFrame* QueryTextFrame(IControlView* controlView, 
										   PMPoint where, 
										   RangeData *caret, 										   
										   bool16 composeFirst = kTrue) = 0;	

/**	 Return the current time which includes date and time
	@param time 
 */
		virtual void GetTime(PMString* time) = 0;

/**	Not used anymore in CS2.
	@param model 
	@param view 
	@return IDocument* 
 */
		virtual IDocument* QueryDocument(ITextModel* model, IControlView* view) = 0;
					// Return the document with a given text model


/**	Check if the active view is galley/story editor
	Return kTrue if the current mode is in the Galley mode in InCopy
	Return kFalse if the current mode is in the layout mode in InCopy
	@param galleySwitch nil = return kFalse
	@return bool16 
 */
		virtual bool16 InGalley(IGalleySwitch* galleySwitch) = 0;
	
/**	Given a text index range, return the local coordinate on the page.  
	It also returns the frame index of the given text range.
	For instance, if try to find out the Note Anchor coordinate on the page,
	could use RangeData(noteAnchorIndex, RangeData::kLeanForward)
	@param textModel 
	@param caret The text index 
	@param thisFrameIndex Return the start text index of the frame contains the Note
	@return PMPoint 
 */
		virtual PMPoint IndexToPMPoint(ITextModel* textModel, const RangeData &caret, int32* thisFrameIndex) = 0;

/**	Report the current lock state by given story, use the insert lock
	to determine state, assume not locked if there is no valid model.
	@param textModel 
	@return bool16 
 */
		virtual bool16 GetStoryLockState(ITextModel* textModel) = 0;

/** Report the lock state of all the stories with the given
    document.  Return kTrue if at least one story is locked, otherwise, return kFalse.
	@param document 
	@return bool16 
*/
		virtual bool16 GetStoryLockState(IDocument* document) = 0;

/**	Get the total Notes count by the given document
	@param document 
	@return const 
 */
		virtual const int32 GetDocAnchorCount(IDocument* document) = 0;

/**	Get the total Notes count by given the story (param textModel)
	@param textModel 
	@return const 
 */
		virtual const int32 GetAnchorCount(ITextModel* textModel) = 0;

/**	Not used anymore in CS2.
	@param textModel 
	@return int32 
 */
		virtual int32 ResetStoryAnchorCount(ITextModel* textModel) = 0;
					// accumulate the anchor count from the text model and return the total
					// count for this story.  This is 100% accurate but performance can be an issue
					// for large story with large number of notes in it.
					
/**	Not used anymore in CS2.
	@param document 
	@return int32 
 */
		virtual int32 ResetDocAnchorCount(IDocument* document) = 0;
					// for each story in the document, accumulate the anchor count from the text model and return the total
					// count for the document.  This is 100% accurate but performance can be an issue for larger document
					// with large number of notes in it.

/**	Not used anymore in CS2.
	@param none
	@return PMReal 
 */
		virtual PMReal GetGalleyLeftIndent() = 0;
					// return the left indent of the info panel in Galley.  If in layout this value will be zero.


/**	Not used anymore in CS2.
	@param noteSpreadUID 
	@param curSpreadUID 
	@param masterSpreadList 
	@return bool16 
 */
		virtual bool16 NoteInCurrentSpread(UID noteSpreadUID, UID curSpreadUID, IMasterSpreadList* masterSpreadList) = 0;
					// check if this note window (i.e. with noteSpreadUID) should be open in the curSpreadUID.
					// return kTrue to open, otherwise return kFalse


/**	Not used anymore in CS2.
	@param textModel 
	@param hierItem 
	@return bool16 
 */
		virtual bool16 PageItemInvisible(ITextModel* textModel, IHierarchy* hierItem) = 0;
					// This method determines if the page item in the hierarchy is in the invisible
					// layer, which is used to hold the overset text for InCopy text frame.


/**	Not used anymore in CS2.
	@param textModel 
	@param startIndex 
	@return UID 
 */
		virtual UID	GetLastVisibleFrame(ITextModel* textModel, TextIndex startIndex) = 0;
					// !!! InCopy call only !!!
					// With a given text index, this function returns the UID of the
					// of the last visible frame.


/**	Not used anymore in CS2.
	@param dataBase 
	@return IDocumentPresentation* 
 */
		virtual IDocumentPresentation* GetDocWindow(IDataBase* dataBase) = 0;
					// With a given database, return the front document window (the first in the 
					// IPresentationList order).  $$$ This will NOT work in the multiple views of the 
					// same document case because it gives us the first in the list.  Since Note
					// is not required of InDesign, this will work fine in InCopy.


/**	Not used anymore in CS2.
	// Given the story and its text index offset, return the 
	// spread UID of the text frame containing this given index.
	@param textModel 
	@param offset 
	@return UID 
 */
		virtual UID GetSpreadUID(ITextModel* textModel, TextIndex offset) = 0;


/**	Not used anymore.
	// This method handles differently in InCopy and InDesign due
	// to the way overset text is structured.  
	//
	// InCopy: 
	//		This method first determine if a given text index lives
	//		in the overset text frame.  There is actually no overset
	//		in InCopy, we create enough frames to hold the overset 
	//		text and put them in the pasteboard.  
	//		1. If the index is in overset frame, this method walks from
	//		the given index backward to find the last non-overset
	//		text frame and returns the spread UID of that frame.
	//		2. If the index is not in the overset frame, we simply use
	//		the given INoteTextAttribute to get the frame UID.
	//		
	//		Usage:  This is used for switching between layout and galley
	//		view where the page spread we're switching to will not be
	//		correct if we're in overset text in Galley view.
	//
	// InDesign:
	//		Simply return the spread UID from the attribute.  This is
	//		probably not used for InDesign with InCopy plugin since
	//		there is no note window UI there.  Just add here for future
	//		use.
	@param noteData 
	@param textModel 
	@param position 
	@return UID 
 */
		virtual UID GetSpreadUID(INoteData* noteData, ITextModel* textModel, TextIndex position) = 0;

/**	 Not used anymore.
	Given the story and its text index offset, this routine determines
	if the given text position is in the 'invisible' layer.  This special
	layer is created to hold the text frames big enough to hold
	the overset text.  Therefore, in InCopy, there will never be an 
	overset situation because we always expand to hold the last
	character in the story.  This will go away in InDesign 2.0.
	@param textModel 
	@param index 
	@return bool16 
 */
		virtual bool16 InvisibleText(ITextModel* textModel, TextIndex index) = 0;

/**	Find the Note thread by given the param noteDataUID
	@param textModel The story contains the Note
	@param noteDataUID The Note Data UID
	@param threadStart Return the start text index of Note thread 
	@param threadSpan Return the Note thread length
	@return bool16 kTrue = Note thread exists, kFalse = Note thread not exists
 */
		virtual bool16 FindNoteStoryThread(ITextModel* textModel, UID noteDataUID, TextIndex* threadStart, int32* threadSpan) = 0;

/**	Get the Note content by given param noteRef
	@param textModel The story contains the Note
	@param noteRef The Note UIDRef
	@return WideString The content of the Note
 */
		virtual WideString GetNoteContent(ITextModel* textModel, const UIDRef& noteRef) = 0;

/**	Toggle to collapse/expand all Notes on teh given story (param textModel)
	@param textModel The story
	@param currentNoteUID The current Note
	@param newCollapseState kTrue = Collapsed All Notes, kFalse = Expand All Notes
	@param collapseAllButOne kTrue = affect only current Note, kFalse = affect all Notes
	@return ErrorCode 
 */
		virtual ErrorCode ToggleAllNoteCollapse(ITextModel* textModel,  UID currentNoteUID, bool16 newCollapseState, bool16 collapseAllButOne) = 0;
			

/**	Remove all Notes on the given document
	@param document
*/
		virtual	void ClearAllNotes(IDocument* document) = 0;

/**	Remove all Notes on the given story (param textModel)
	@param textModel 
 */
		virtual void ClearAllNotes(ITextModel* textModel) = 0;

/** Internal Use Only
*/
	virtual void	DoDragDropNoteModel(UIDRef srcStoryRef, UIDRef targetStoryRef, TextIndex srcTextIndex, TextIndex targetTextIndex, bool16 duplicateNote, bool16 startOfDeletedText) = 0;
};

#endif // __INOTEUTILS__
