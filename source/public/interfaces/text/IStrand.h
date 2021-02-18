//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStrand.h $
//  
//  Owner: eric menninga
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
#ifndef __ISTRAND__
#define __ISTRAND__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"
#include "WideString.h"
#include "K2SmartPtr.h"
#include "ITextModel.h"

class IStrandPastePiece;
class ICommand;
class ITextModelMemento;


/** Abstract interface that all strands must support.
	Some of the common methods that a strand of the text model must support.
	@ingroup text_story
*/
class IStrand : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTRAND };

		typedef K2Vector<InterfacePtr<ITextModelMemento> > MementoList;

		virtual void Insert(const WideString* data, TextIndex pos) = 0;
		virtual void Delete(TextIndex startpos, int32 numchars) = 0;
		virtual IStrandPastePiece* Cut(TextIndex startpos, int32 numchars) = 0;

		// Used to perform a set of replacements on the strand. 
		// The replacementList argument contains a list of ranges\
		// associated with replacement strings.
		// This is an optmized form for doing multiple replacements.
		// The list of ranges is passed by the text model
		// in descending order.
		virtual void Replace(const boost::shared_ptr<ITextModel::ReplacementList  >& replList,
							bool16 clearNonContinuingAttrs) = 0;

			/** hardly any strands will care about damage. */
        virtual void ForceCompositionDamage(TextIndex position, int32 numChars) = 0;
        /** hardly any strands will care about damage. */
        virtual void ForceContentDamage(TextIndex position, int32 numChars) = 0;

			/** returns the REMAINING length only -- length of what's left AFTER position */
		virtual int32 GetRunLength(TextIndex position, TextIndex *runBegin = nil) = 0;

		virtual IStrandPastePiece* CopyRange(TextIndex startpos, int32 numchars) = 0;
		virtual int32 Paste(TextIndex startpos, IStrandPastePiece *str) = 0;

			/** Called by the text model during Paste for all strands that did
				generate VOSSavedData to be pasted. */
		virtual void IncreaseSpan(TextIndex at, int32 len) = 0;

		virtual void CollectMementosForDelete(TextIndex at, int32 len,
										MementoList& list) = 0;

		virtual void CollectMementosForCut(TextIndex at, int32 len,
										MementoList& list) = 0;

		virtual void CollectMementosForCopyRange(TextIndex at, int32 len,
										MementoList& list) const = 0;

		virtual void CollectMementosForReplace(TextIndex at, int32 len,
										MementoList& list) = 0;

			/** Return the first disk page in the strand. Creates the
				first page if there wasn't one already. */
		virtual UID GetFirstPage() = 0;
			/** Make @param firstPage the first page in the strand. Returns what
				previously was the first page. */
		virtual UID SetFirstPage(UID firstPage) = 0;
			/** Create a new page. */
		virtual UID CreatePage() = 0;
			
			/** Return the classID of the VOS objects on the pages. */
		virtual ClassID GetObjectClass() const = 0;

			/** Called to obtain a command when the strand is about to be removed
				from the document. The returned command should remove any owned UIDs
				make sure to also remove all disk pages! It should be undoable. */
		virtual ICommand* QueryRemoveFromDocumentCmd(UID textModelUID) = 0;
		
			/** frequently returns kInvalidUID, each strand is NOT required to remember this */
		virtual UID GetOwningStoryUID() const = 0;
		virtual void StrandAttachedToStory(UID textModelUID, int32 length) = 0;
		virtual void StrandDetachedFromStory(UID textModelUID) = 0;


			/** Insert a new story thread.
				Strands that do not need to do special handling for StoryThread
				creation can simply implement this method by calling DoInsert()
				on themselves.
				Valid 'pos' values for InsertStoryThread() are the first index
				after an existing StoryThread. This means you can't insert
				a StoryThread at TextIndex zero (0) but you CAN insert after the
				final CR (and story thread) of the TextModel.
				'data' must be terminated by a CR. */
		virtual void	InsertStoryThread(UID dictUID, uint32 dictKey,
									const WideString* data, TextIndex pos) = 0;

			/** Divide existing story thread into one or more new story threads.
				We always divide off the bottom of an existing story thread.
				Stands without special StoryThread responsibilities are not
				required to do anything with this call.
			
				Valid 'pos' values for CreateStoryThread() is the next
				character after what will become the new final CR of the
				dividing story thread.
			
				An K2Vector is allowed in order to speed creation of many
				StoryThreads at one time. A typical creation sequence might
				be to create an initial story thread with InsertStoryThread(),
				insert one more sequences of initial text, each terminated by
				a CR, in the new story thread and then call CreateStoryThread()
				with the appropriate list of keys and lengths. */
		virtual bool16		CreateStoryThreads(UID dictUID,
										const K2Vector<uint32>& dictKeyList,
										const K2Vector<int32>& lenList,
										TextIndex pos) = 0;

			/**	The inverse of CreateStoryThread. The span of the joined
				StoryThread(s) are given back to the preceding StoryThread. This
				method does not change the length of the TextModel. */
		virtual bool16		JoinStoryThreads(TextIndex start, int32 len) = 0;

};

#endif		// __ISTRAND__
