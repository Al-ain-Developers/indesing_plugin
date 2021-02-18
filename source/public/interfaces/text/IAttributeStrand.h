//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAttributeStrand.h $
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
#ifndef __IAttributeStrand__
#define __IAttributeStrand__


#include "IPMUnknown.h"
#include "TextID.h"
#include "DataWrapper.h"

class AttributeBossList;
class ITextModel;

/**
	Abstract interface that all  attribute strands must implement.
	@ingroup text_story
*/
class IAttributeStrand : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IATTRIBUTESTRAND };

		/**
			Applies a text style to a range.
			@param model IN text model.
			@param which IN whether this is a character or a paragraph style.
			@param pstartpos IN start of apply range.
			@param pnumchars IN length of apply range.
			@param styleref IN applied style uid
			@param removeall IN whether to remove all overrides.
			@param keepOldStyleAsOverrides IN whether to apply current style as overrides before setting new style.
			*/
		/**
			Adjusts pstartpos & pnumchars to encompass EXACTLY ALL the characters within the
			intersecting paragraphs.
		*/
		virtual void DoApplyTextStyle(const ITextModel* model, ClassID which, TextIndex *pstartpos,
									  int32 *pnumchars, UID styleref, bool16 removeAll, bool16 keepOldStyleAsOverrides = kTrue) = 0;

		/**
			Applies text attributes to a range.
			@param model IN text model.
			@param whichStrand IN whether these are character or a paragraph attributes.
			@param startpos IN start of apply range.
			@param numchars IN apply range length.
			@param over IN attributes to apply.
			*/
		/**
			Adjusts startpos & numchars to encompass EXACTLY ALL the characters within the
			intersecting paragraphs.
		*/
		virtual void DoApplyOverrides(const ITextModel* model, ClassID whichStrand,
								TextIndex *startpos, int32 *numchars, const AttributeBossList* over) = 0;

		/**
			Clears text attributes from a range.
			@param model IN text model.
			@param whichStrand IN whether these are character or paragraph attributes.
			@param startpos IN start of clear range.
			@param numchars IN clear range length.
			@param over IN attributes to clear.
		*/
		/**
			Adjusts startpos & numchars to encompass EXACTLY ALL the characters within the
			intersecting paragraphs.
		*/
		virtual void DoClearOverrides(const ITextModel* model, ClassID whichStrand,
								TextIndex *startpos, int32 *numchars, const AttributeBossList* over) = 0;

		/**
			Remove reference to paragraph style but leave its effect in the form of overrides.
			@param model IN text model.
			@param start IN start of unhook range.
			@param len IN unhook range length.
			@param rootStyle IN root style UID.
			@param oldParagraphStyle IN paragraph style to unhook.
			@param storyThreadStyle IN story thread style.
		*/
		virtual void UnhookParagraphStyle(const ITextModel* model, TextIndex start, int32 len,
								UID rootStyle, UID oldParagraphStyle, UID storyThreadStyle) = 0;

		/**
			@return UID of the style applied at a position
			@param position IN text index to look at.
			@param count OUT length from 'position' to end of paragraph run.
			@param runBegin OUT text index of start of paragraph run.
		*/
		virtual UID GetStyleUID(TextIndex position, int32 *count, TextIndex *runBegin = nil) const = 0;

		/**
			@return list of attributes applied at a position.
			@param position IN text index to look at.
			@param count OUT length from position to end of paragraph run.
			@param runBegin OUT text index of start of paragraph run.
		*/
		virtual DataWrapper<AttributeBossList> GetLocalOverrides(TextIndex position, int32 *count, TextIndex *runBegin = nil) const = 0;

		/** For internal use only. */
		virtual void ResetWithNoUndo(const ITextModel* model, TextIndex start, int32 length, UID toStyle) = 0;

		/** For internal use only. */
		virtual void StoryThreadStyleDiffs_ApplyAtPaste(TextIndex start, int32 length,
													const UID	&charRootStyle,	const UID	&paraRootStyle,
													const AttributeBossList *diffAttrs,
													const AttributeBossList * dest_SrcStoryThreadStyleDiffs,
													const ITextModel* model) = 0;

		/** For internal use only. */
		virtual void ParaRootStyleDiffs_ApplyAtPaste(TextIndex start, int32 length,
													const UID	&charRootStyle,	const UID	&paraRootStyle,
													const AttributeBossList *diffAttrs,
													const AttributeBossList * paraDest_SrcRootStyleDiffs,
													const ITextModel* model) = 0;

		/** For internal use only. */
		virtual void CharRootStyleDiffs_ApplyAtPaste(TextIndex start, int32 length,
													const UID	&charRootStyle,
													const UID	&paraRootStyle,
													const AttributeBossList *diffAttrs,
													const AttributeBossList * charDest_SrcRootStyleDiffs,
													const ITextModel* model) = 0;

		/**
			Remove overrides which are already applied through styles.
			@param model IN text model.
			@param start IN start of remove range.
			@param numchars IN remove range length.
		*/
		virtual void RemoveRedundantOverrides(const ITextModel* model, TextIndex start, int32 len) = 0;
};

#endif		// __IAttributeStrand__
