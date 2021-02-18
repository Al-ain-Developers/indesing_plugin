//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICreateMCFrameData.h $
//  
//  Owner: eric_menninga
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
#ifndef __ICreateMCFrameData__
#define __ICreateMCFrameData__

#include "IPMUnknown.h"
#include "TextID.h"

class IDataBase;
class IDocument;
class IControlView;

/** This data interface is used by a number of commands to describe how the frame
	is supposed to be created: what document, which story, linked or not, in what graphical frame, etc.
	@ingroup text_layout
*/
class ICreateMCFrameData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATEMCFRAMEDATA };

		/**	Copy the data settings from one interface to another.
			@param into is another interface to write these settings into.
		 */
		virtual void CopyInto(ICreateMCFrameData *into) const = 0;

		/**	SetFrameList is used when creating a new text frame by using the in/out ports of another.
			@param framelist the UID of the frameList to insert into.
			@param insertAt the index of the new frame to create within the frameList.
		 */
		virtual void SetFrameList(const UIDRef& framelist, int32 insertAt) = 0;

		/**	When placing an existing story. No framelist, but the story exists.
			@param story is the story to place.
		 */
		virtual void SetStory(const UIDRef& story) = 0;

		/**	When we only know the document -- story & framelist will be created.
			@param document a pointer to the document.
		 */
		virtual void SetDocument(IDocument* document) = 0;

		/**	Used when converting a graphic frame to a text frame.
			@param nGraphicFrameUID the UID of the graphic frame that will be converted.
		 */
		virtual void SetGraphicFrameParent(UID nGraphicFrameUID) = 0;

		/**	was a story CREATED by this interface, or set to something already in existence?
			@return kTrue when the story was created.
		 */
		virtual bool16 IsStoryCreated() const = 0;

		/**	was a framelist CREATED by this interface, or set to something already in existence?
			@return kTrue when the frameList was created.
		 */
		virtual bool16 IsFrameListCreated() const = 0;

		/**	What is the document being placed into?
			@return a pointer to the document. Not referenced.
		 */
		virtual IDocument* GetDocument() const = 0;

		/**	What is the database?
			@return the database being placed into.
		 */
		virtual IDataBase* GetDataBase() const = 0;

		/** What is the graphic frame when converting a spline into a text frame.
			@return the UID of the graphic frame which will contain the new text frame.
		 */
		virtual UID GetGraphicFrameParent() const = 0;

		/**	Returns the story UID cached locally.
			@return the UID of the story.
		 */
		virtual UID GetCachedStory() const = 0;

		/**	Get the FrameList UID cached locally. 
			@return the UID of the frame list. 
		 */
		virtual UID GetCachedFrameList() const = 0;
		
		/**	Returns the story of the created text frame.  Will create one if one wasn't provided.
			@return the UID of the story (created or not).
		 */
		virtual UID GetStory() const = 0;

		/**	Get the FrameList of the created text farme. Will create one if one wasn't provided.
			@return the UID of the frame list. (created or not).
		 */
		virtual UID GetFrameList() const = 0;

		/**	when linking, the new frame has a position in an already existing frame list.
			This is the index to insert the new frame at.
			@return the index to use in the frame list.
		 */
		virtual int32 GetInsertIndex() const = 0;

		enum Orientation { kHorizontal, kVertical };

		/**	Is the frame to be vertical or horizontal?
			@param nOrientation vertical or horizontal?
		 */
		virtual void SetOrientation( Orientation nOrientation ) = 0;

		/**	Get the orientation set.
			@return Orientation vertical or horizontal?
		 */
		virtual Orientation GetOrientation() const = 0;

		enum Direction { kLeftToRight, kRightToLeft };

		/**	Is the frame to be left to right or right to left?
			@param nDirection kRightToLeft or kLeftToRight?
		 */
		virtual void SetDirection( Direction nDirection ) = 0;

		/**	Get the direction set.
			@return Direction kRightToLeft or kLeftToRight?
		 */
		virtual Direction GetDirection() const = 0;

		/**	Is the frame being created for an endnotes story?
		@param isEndnoteStory kTrue if the frame is being created for an endnotes story
		*/
		virtual void SetIsEndnoteStory(bool16 isEndnoteStory) = 0;

		/**	Get whether the frame is being created for an endnotes story.
		@return kTrue if the frame is being created for an endnotes story
		*/
		virtual bool16 GetIsEndnoteStory()  const = 0;

		/**
		To activate the TextEditorView, use the new utility method
		ITextEditUtils::ActivateTextEditorView().
		*/
};

#endif
