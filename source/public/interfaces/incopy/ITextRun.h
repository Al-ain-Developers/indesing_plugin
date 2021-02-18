//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextRun.h $
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
#ifndef __ITextRun__
#define __ITextRun__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "PMRect.h"
#include "IInterfaceColors.h"
#include "LineDescription.h"

class IGraphicsPort;
class ITextModel;
class WideString;

/** 
	ITextRun is an interface that is used to draw individual run types. There are run types
	for track change text, inline note text, footnote text, inline note begin/end markers and footnote begin/end markers. 
	Regular text is drawn directly in the implementation of ITextRuns so there is no ITextRun implementation for that. More
	types may be added later. There is no way for a 3rd party to add a new type of runtype currently.
	There is not a separate instance of this for each run rather one per run type. Data on each individual
	run is passed in.
*/
class ITextRun : public IPMUnknown
{
public:
	/**
		Called at the beginning of each draw of a line to initialize run data if desired 
		@return none.
	**/
	virtual void InitializeForDraw() = 0;
	
	/**
		Answers the question of whether this run is currently displayed
		@param description - what is the information about this run passed in by TextRuns implementation
		@return a RunDescription
	**/
	virtual bool16 IsVisible(const RunDescription &description) = 0;
	
	/**
		Answers the question of whether this run type draws text
		@return kTrue if this draws text (as opposed to a marker or tag with no text associated)
	**/	
	virtual bool16 DrawsText() = 0;
	
	/**
		Implementation of this will return information about the story thread associated with this run type
		@param description - passed in describes the specific run instance in the text that thread information is going to be returned for
		@param primaryTextModel - passed in what text model does this run live in
		@param threadDictUID - returns the dict UID for the story thread (see ITextModel)
		@param threadDictKey - returns the threadDictKey for the story thread (see ITextModel)
		@param threadStart - returns the start text Index of the story thread associated with the run passed in via description param
		@param threadSpan - returns the span of the story thread associated with the run passed in via description param
		@return kTrue if able to return data for the description passed in.
	**/	
	virtual bool16 GetRunThreadData(const RunDescription &description, ITextModel *primaryTextModel,
													UID &threadDictUID, uint32 &threadDictKey, 
													TextIndex &threadStart, int32 &threadSpan) = 0;

	/**
		Given a run description and some information about the port and where and how to draw the run this routine will draw it.
		@param gPort - port to draw into
		@param at - index of line the run lives in
		@param description - description of the specific run to draw
		@param runRect - bounds of the run can be altered by this routine to match width actually drawn
		@param textDrawPt - position to start drawing text associated with this run
		@param runDrawLength - how many characters is this run passed in
		@param runIndex - what is the index of the run within the line, passed in.
		@param showInvisibles - visibly show white space characters, passed in
		@param highlightRect - the currently highlighted area rect within a single line. Use to determine background fill rect for the run.
		@return width of run drawn
	**/	
	virtual PMReal DrawRun(IGraphicsPort *gPort, int32 at, const RunDescription &description, PMRect &runRect, 
							const PMPoint &textDrawPt, int32 runDrawLength, int32 runIndex,
							bool16 showInvisibles, const PMRect &highlightRect) = 0;

	/**
		Called at line draw time to draw the text highlight and is a good place to also draw any custom run background color.
		@param at - index of line to highlight
		@param gPort - port to highlight in
		@param scrollCompensationValue - what is the current scroll value for the view
		@return none
	**/	
	virtual void DrawHilite(int32 at, IGraphicsPort *gPort, const PMPoint &scrollCompensationValue) = 0;
	
	/**
		Draw highlight for a specific range of text corresponding to a text run.
		@param textModelStart - index to start drawing highlight at in text model indices
		@param textModelEnd - index to end drawing highlight at in text model indices
		@return none
	**/	
	virtual void DrawHilite(const TextIndex textModelStart, const TextIndex textModelEnd) = 0;

	/**
		This is used to draw the overlapping portion of runs that draw inbetween two lines. For instance
		footnotes and inline notes draw a border line inbetween two lines that must occasionally be refreshed
		when the line next to it gets erased but the line that this line lives in does not.
		@param gPort - port to draw into
		@param at - index of line this run lives in
		@param description - information about the run to draw the overlap for
		@param runRect - bounds to draw into
		@param runIndex - index of run with in the line.
		@return none
	**/	
	virtual void DrawRunOverlap(IGraphicsPort *gPort, int32 at, const RunDescription &description, PMRect &runRect,
								int32 runIndex) = 0;
};

#endif 		// __ITextRun__