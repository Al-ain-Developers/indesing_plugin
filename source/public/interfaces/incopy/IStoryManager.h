//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryManager.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IStoryManager__
#define __IStoryManager__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "PMRect.h"
#include "UIDList.h"
#include "IInterfaceColors.h"
#include "LineDescription.h"
#include "K2Vector.h"

class ITextRun;
class IGraphicsPort;
class IPMFont;
class ITextModel;
class IdleTimer;

/**   Provides multiple story management of TextLines data for story/galley views.
	@author Kevin Van Wiel
  	@see ITextLines, ITextRuns
*/
class IStoryManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTORYMANAGER };

	   /** Delete a story from the view. Returns true if the story was removed.
	      @param storyUID IN uid of the story (textmodel uid) to remove from the view
	      @return kTrue if successful in deleted story from the view.
	   */
		virtual bool16 DeleteStory(UID storyUID) = 0;

	   /** Sync view stories to the incopystorylist.
	   */
		virtual void SyncStoriesToManaged() = 0;
		
	   /** Should not call this directly normally. The general way this is called is by processing a kReorderStoriesCmdBoss
	   		which will trigger a call to this method for each active story/galley view. 
	   		Set the display order of the stories in the galley or story views. Unlike calling InitializeLines this
	   		does not cause any recomposition. Use is restricted to re-arranging existing stories that
	   		already exist in the view. That is stories may not be added or deleted from the view with this method.
	   		@precondition stories must already exist in the view 
	   		@param storiesInDisplayOrder IN list of text model uids in the order they should be display in
	   			the view.
	   		@param redraw IN should the view be invaled after rearranging the stories (default is true that it
	   			should be invaled)
	   		@precondition the stories in the storiesInDisplayOrder must already exist in the view otherwise
	   			the caller should call InitializeLines in ITextLines to add them first.
	   */
		virtual void SetStoryDisplayOrder(const UIDList &storiesInDisplayOrder, bool16 redraw = kTrue) = 0;
		
	   /** All text in story or galley view is not necessary composed to a window bounds at 
	   		a given moment if it is composed the range of the composed text is stored. If more text is composed the composed
	   		range is added to here. Note simply adding a range to the composed range doesn't actually cause it
	   		to be composed rather this method is called when text has been composed. Normally this is only used
	   		internally
	   		@param storyIndex Is the index of the story to mark the range in.
	   		@param start start text index of range to mark composed
	   		@param length length of range to add to the start text index
	   */
		virtual void RemoveFromUncomposedRange(int32 storyIndex, int32 composeID) = 0;
		
	   /** All text in story or galley view is not necessary composed to a window bounds at a given moment
	   		if it is composed the range of the composed text is stored. If text is not composed this routine
	   		is used to track the non-composed range. Normally this is only used internally.
	   		@param storyIndex Is the index of the story to mark the range in.
	   		@param start start text index of range to mark composed
	   		@param length length of range to add to the start text index
	   */
		virtual void AddToUncomposedRange(int32 storyIndex, int32 composeID, int32 lineIndexHint = -1) = 0;

	   /** A psuedo line is created as a temporary line before lines are really composed. This routine reports if there
	   		are any psuedo lines in a specific story
	   		@param storyIndex to check if it has psuedo lines.
	   */
		virtual bool16 StoryHasPsuedoLines(int32 storyIndex) = 0;
		
	   /** Compose a section of psuedo lines.
	   		@param storyIndex to start composing at.
	   		@param timeCheck determines the maximum of time that the routine will compose until it quits.
	   */
		virtual bool16 ComposeUncomposed(int32 storyIndex, IdleTimer* timeCheck) = 0;
		
	   /** Set where an overset divider line is placed in the story view. Used as reference to refind this line quickly.
	   		once the index is set it is kept current when lines are deleted or inserted. Internal use only
	   		@param storyIndex Is the index of the story to set the index in.
	   		@param lineIndex index of the line to mark as story of overset.
	   */
		virtual void SetOversetLineIndex(int32 storyIndex, int32 lineIndex) = 0;
		
	   /** Get the line that overset text starts on.
	   		@param storyIndex Is the index of the story to set the index in.
	   		@param lineIndex index of the line to mark as story of overset.
	   */
		virtual int32 GetOversetLineIndex(int32 storyIndex) = 0;

};

#endif // __IStoryManager__