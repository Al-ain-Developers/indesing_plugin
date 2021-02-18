//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextStoryThread.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextStoryThread__
#define __ITextStoryThread__

#include "IPMUnknown.h"
#include "TextID.h"

#include "RequestContext.h"

class IFrameList;
class IParcelList;
class IParcel;
class IScript;
class ITextModel;
class AttributeBossList;

/** 
	ITextStoryThreads subdivide the entire length of the ITextModel into
	discrete ranges that contain at least one paragraph.
	Each ITextStoryThread is composable into one and only one IParcelList. It is
	not necessary to have a IParcelList to have a ITextStoryThread, only if it
	is to be composed in some way. 

	Examples of objects which implement ITextStoryThread are Table Cells,
	Footnotes, Notes, Text Macros and Deleted Text.

	Every ITextModel has at least one ITextStoryThread that begins at TextIndex
	zero. This ITextStoryThread is known as the "primary story thread" and is
	the one that composes into the IParcelList that is mapped to the IFrameList.

	ITextStoryThreads are not required to be UID based objects, so their
	management is handled by a parent UID based object which implements the
	ITextStoryThreadDict interface. All the ITextStoryThreads managed by the
	same parent dictionary are stored contiguously and will return the same
	value for GetDictUID() but will return unique values, with respect to the
	parent dictionary, for GetDictKey().

	@see ITextModel
	@see IParcelList
	@see ITextStoryThreadDict
	@see IFrameList
	@ingroup text_story
*/
class ITextStoryThread : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTSTORYTHREAD };

		/**
		Returns the IParcelList that this ITextStoryThread will compose into.
		@return Pointer to IParcelList, may be nil.
		*/
		virtual IParcelList*	QueryParcelList() const = 0;

		/**
		The Dictionary is a UID based object that implements the ITextStoryThreadDict interfaces.
		@return UID of parent dictionary boss.
		*/
		virtual UID				GetDictUID() const = 0;

		/*
		The Dictionary Key is unique only with respect to the parent dictionary boss, not other parent dictionaries.
		@return key assigned by parent dictionary boss.
		*/
		virtual uint32			GetDictKey() const = 0;

		/**
		Returns information about the subset of the ITextModel mapped to the ITextStoryThread. The span of the ITextStoryThread is always greater than 0.
		@param pSpan Optional pointer to out parameter which will be filled in with the span.
		@return TextIndex within the ITextModel of the first character in the ITextStoryThread.
		*/
		virtual TextIndex		GetTextStart(int32 *pSpan = nil) const = 0;

		/**
		Returns information about the subset of the ITextModel mapped to the ITextStoryThread. The span of the ITextStoryThread is always greater than 0.
		@param pStart Optional pointer to out parameter which will be filled in with the TextIndex of the first character in the ITextStoryThread.
		@return TextIndex within the ITextModel of the last character, plus 1, in the ITextStoryThread.
		*/
		virtual TextIndex		GetTextEnd(TextIndex *pStart = nil) const = 0;

		/**
		Returns information about the subset of the ITextModel mapped to the ITextStoryThread. The span of the ITextStoryThread is always greater than 0.
		@param pStart Optional pointer to out parameter which will be filled in with the TextIndex of the first character in the ITextStoryThread.
		@return Span within the ITextModel.
		*/
		virtual int32			GetTextSpan(TextIndex *pStart = nil) const = 0;

		/**
		Returns the ITextModel that this ITextStoryThread is part of.
		@return Pointer to ITextModel
		*/
		virtual ITextModel* 	QueryTextModel() const = 0;

		/**
		Returns the UID of the style that this story thread uses for story thread attributes.
		@return The UID of the style applied.
		*/
		virtual UID				GetTextStyle() const = 0;

		/**
		Returns IScript object that is considered to be the Parent of any TextObject in the Thread. See ITextObjectParent for more information.
		@param RequestContext Reference to Scripting RequestContext
		@return Pointer to IScript object
		*/
		virtual IScript*		QueryParent(const ScriptInfo::RequestContext& context) const = 0;

		/**
		Returns the adjusted thread start/end for the specified scripting context. Some implementations do not support making the full range of the StoryThread available to scripting and this method allows them to clip off the beginning and/or the end of the thread. This adjusted range will limit the natural extensions that take place for scripting objects such as Words, Lines, Paragraphs, etc that occur beyond a sub-range of the thread.
		Most implementations need simply forward this call to GetTextStart().
		@param RequestContext Reference to Scripting RequestContext
		@param pAdjustedSpan Pointer to out parameter which will be filled in with the adjusted text span
		@return TextIndex of the adjusted text start
		*/
		virtual TextIndex		GetAdjustedTextStart(const ScriptInfo::RequestContext& context, int32 *pAdjustedSpan) const = 0;

};

#endif	// __ITextStoryThread__
