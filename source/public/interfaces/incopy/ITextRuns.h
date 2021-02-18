//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextRuns.h $
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
#ifndef __ITextRuns__
#define __ITextRuns__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "PMRect.h"
#include "UIDList.h"
#include "IInterfaceColors.h"
#include "LineDescription.h"
#include "K2Vector.h"
#include "IStoryService.h"

class ITextRun;
class IGraphicsPort;
class IPMFont;
class ITextModel;
class WideString;
class RangeData;

/** 
	RunLocation is used in the GetExtendedRunSpanInformation method to pass information about what run to start searching at.
*/
class RunLocation
{
	public:
		/**
			Initialize to default values
			@return none.
		**/
		RunLocation() : fLineIndex(-1), fRunIndex(-1) {}
		
		/**
			Initialize to specified values
			@param lineIndex - index of line
			@param runIndex - index of run within line
			@return none.
		**/		
		RunLocation(int32 lineIndex, int32 runIndex) : fLineIndex(lineIndex), fRunIndex(runIndex) {}
		
		/** no getter so retrieve line index with this variable */
		int32 fLineIndex;
		
		/** no getter so retrieve run index with this variable */
		int32 fRunIndex;
};

/** 
	The TextRuns interface has methods related to the handling of story/galley text runs. Note that when talking about
	textruns with regard to this interface these are not character style runs but rather. Runs of a certain text display
	type like a inline note text run footnote text run or regular text run. Each line displayed in story and galley may contain
	text runs. It's possible also that a line may contain no text runs. This would be the case for divider lines although this
	may change.
*/
class ITextRuns : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTRUNS };
                
		/**
			Get an ITextRun interface for a given line description 
			@param description a rundescription to get a cooresponding ITextRun for
			@return An ITextRun interface instance.
		**/
		virtual ITextRun *QueryRunInterface(const RunDescription &description) = 0;
		
		/**
			Get a RunDescription for a given line and run index
			@param at index of line to get RunDescription of
			@param run index of run within line to get RunDescription of
			@return a RunDescription
		**/
		virtual const RunDescription& GetRun(int32 at, int32 run) = 0;
		
		/**
			Get a RunDescription for a given story, line and run index
			@param storyIndex index of story to get RunDescription of
			@param at index of line to get RunDescription of
			@param run index of run within line to get RunDescription of
			@return a RunDescription
		**/
		virtual const RunDescription& GetRun(int32 storyIndex, int32 at, int32 run) = 0;
		
		/**
			Tell the caller whether a line has any runs. Some lines don't for instance
			divider lines
			@param storyIndex index of story the line is in
			@param lineIndex index of line interested in
			@return kTrue if the line has runs. kFalse otherwise will return kFalse for invalid line numbers as well.
		**/		
		virtual bool16 TextRunsContainedInLine(int32 storyIndex, int32 lineIndex) = 0;
		
		/**
			Used to draw all of the text runs in a line
			@param at index line to draw runs of
			@param gPort IGraphicsPort to draw runs in
			@param clipRect area of the graphics port we are allowed to draw in
			@param scrollCompensationValue amount scrolled vertically in the view
			@param displayFont instance of display font we are using to draw the text may in fact not be used if this font is not appropriate for a run 
			@param displaySize size of the display font we use to draw text.
			@param description description of the line. DrawRuns will draw the runs contained in this line description
			@param topLineInDraw a flag to indicate whether this is the first line in this draw sequence (not usually important it is used as an optimization)
			@return void
		**/
		virtual void DrawRuns(int32 at, IGraphicsPort *gPort, const PMRect &clipRect, const PMPoint &scrollCompensationValue, 
						IPMFont *displayFont, PMReal displaySize, const LineDescription &description, bool16 topLineInDraw) = 0;
						
		/**
			Used to draw all of the text runs in a line
			@param storyIndex index of story to draw runs for
			@param at index line to draw runs of
			@param gPort IGraphicsPort to draw runs in
			@param clipRect area of the graphics port we are allowed to draw in
			@param scrollCompensationValue amount scrolled vertically in the view
			@param displayFont instance of display font we are using to draw the text may in fact not be used if this font is not appropriate for a run 
			@param displaySize size of the display font we use to draw text.
			@param description description of the line. DrawRuns will draw the runs contained in this line description
			@param topLineInDraw a flag to indicate whether this is the first line in this draw sequence (not usually important it is used as an optimization)
			@return void
		**/
		virtual void DrawRuns(int32 storyIndex, int32 at, IGraphicsPort *gPort, const PMRect &clipRect, const PMPoint &scrollCompensationValue, 
						IPMFont *displayFont, PMReal displaySize, const LineDescription &description, bool16 topLineInDraw) = 0;
		
		
		/**
			Used to copy run information from one LineDescription to another.
			@param source copy run information from this
			@param source item to make a copy of
			@param destination item to copy to
			@return void
		**/
		virtual void CopyRuns(K2Vector<RunDescription> *source, K2Vector<RunDescription> *destination) = 0;
		
		/**
			depricated do not use
			@return void
		**/
		virtual void AppendRun(LineDescription& line, RunDescription::RunType runType, TextIndex runStartOffset, TextIndex runEndOffset, UIDRef storyThreadRef, RealAGMColor runColor =  RealAGMColor(1.0, 1.0, 1.0)) = 0;
		
		/**
			Used to get text of a run when drawing.
			@param at index of line to get text of
			@return number of runs in line
		**/
		virtual int32 GetNumRuns(int32 at) = 0;
		
		/**
			Get number of runs within a line
			@param storyIndex index of story to get run information for
			@param at index of line to get run information for
			@return number of runs within the line
		**/
		virtual int32 GetNumRuns(int32 storyIndex, int32 at) = 0;

		/**
			Gets line owned rectangular screen area for a given run
			@param lineIndex index of line to get rect of
			@param runIndex index of run to get rect of
			@return rectangle describing draw bounds of the run
		**/
		virtual PMRect CalculateRunRect(int32 lineIndex, int32 runIndex) = 0;

		/**
			Get the index of a run at a given point on the screen
			@param point where on the screen is of interest. Given in terms of 0 being first line in view.
			@param lineIndex filled in by the routine this is the index of the line the returned run is in
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 FindIndexOfRunAtPoint(const PMPoint &point, int32 *lineIndex) = 0;

		/**
			Same as other FindIndexOfRunAtPoint but if you already know the line that was hit use this one because it is faster.
			@param point where on the screen is of interest. Given in terms of 0 being first line in view.
			@param lineIndex of the line which was hit.
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 FindIndexOfRunAtPoint(const PMPoint &point, int32 lineIndex) = 0;

		/**
			Get index of the last run with in a line.
			@param lineIndex to get run for
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 GetLastRunIndex(int32 lineIndex) = 0;
		
		/**
			Get index of the last run with in a line.
			@param storyIndex index of story to get run of
			@param lineIndex to get run for
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 GetLastRunIndex(int32 storyIndex, int32 lineIndex) = 0;

		/**
			depricated
		**/
		virtual PMReal ComputeRunWidth(int32 lineIndex, const RunDescription& runDescription, int32 *runLength) = 0;

		/**
			Returns true if we are using runs for the view associated with this interface
			@return kTrue if we are using runs
		**/
		virtual bool8 GetUseTextRuns() = 0;

		/**
			Get the text index of the start of line this run is in if this is an inlinenotetext run we return the thread start offset;
			 otherwise, return the run's line start offset. Not recommended for external use
			@param lineIndex index of line to get start offset of
			@param runIndex index of run to get start offset of
			@return return a text index of the start of the line associated with given run
		**/
		virtual TextIndex GetLineStartOffsetAtRun(int32 lineIndex, int32 runIndex) = 0;
		
		/**
			Get the text index of the end of the line this run is in if this is an inlinenotetext run we return the thread start offset;
			otherwise, return the run's line start offset. Not recommended for external use
			@param lineIndex index of line to get end offset of
			@param runIndex index of run to get end offset of
			@return return a text index of the end of the line associated with given run
		**/
		virtual TextIndex GetLineEndOffsetAtRun(int32 lineIndex, int32 runIndex) = 0;
		
		/**
			This method assumes that the caller has already determined that a Point is within the run specified
			by the parameter atLineIndex/atRunIndex and is now asking which character within the run has been hit 
			based on xPosition. The routine will alway return a valid result. xPosition starts at left point of container panel
			@param atLineIndex index of line to character in
			@param atRunIndex index of run to get character in
			@param xPosition position of interest
			@param offsetIntoLine index into line of the character at the xPosition
			@return kTrue if found a valid character at given xPosition
		**/
		virtual bool16 FindCharacterAtXPosition(int32 atLineIndex, int32 atRunIndex, PMReal &xPosition, int32 &offsetIntoLine) = 0;
		
		
		/**
			Given a text model index find the run. Only works for runs that are part of the primary thread. Use FindIndexOfRunAtDisplayOffset()
			to find runs that contain external data (like notes, deleted text). FindIndexOfRunAtDisplayOffset() is valid for regular text runs too.
			Mostly for internal use.
			@param description of line this line will look in
			@param atTextModelOffset text model index that the run will be found for
			@return index of run at the text index
		**/
		virtual int32 FindIndexOfRunAtTextModelOffset(LineDescription &description, int32 atTextModelOffset) = 0;
		
		/**
			Given a galley display index find the run. A galley display index includes runs that are outside of the primary text thread.
			@param offset text display index to find run for
			@param offsetIntoRun returns offset into run for the given text display index
			@param bUsingEndOfLine if kFalse skip to start of next line if text index is at end of a line
			@return index of run at the display text index
		**/
		virtual int32 FindIndexOfRunAtDisplayOffset(TextIndex offset, int32 &offsetIntoRun, bool16 bUsingEndOfLine = kFalse) = 0;
		
		/**
			Returns the note text content at a given offset. It's better to use Note related routines in general to get information like this. This routine is
			not neccessarily efficient.
			@param model the model to find note text in
			@param textStart anchor position of the note text
			@param textLength returned character length of note text at requested position
			@param textContent returned note text characters at requested text position
			@param startIndex offset into note text to start getting text at
			@return UIDRef of the note text owned item
		**/
		virtual UIDRef GetNoteContent(ITextModel* model, TextIndex textStart, int32 &textLength, WideString &textContent, int32 startIndex = -1) = 0;

		/**	
			Find the first run display offset for a set of associated runs that span multiple lines. For instance, a note may span many lines
			and have many associated run this routine will find the line that the note starts in and get the display index of the first character in the note.
			Useful to find the starting galley display offset of a note or deleted text run that has been split across several lines.
			@param at index of line to start searching for run start at
			@param runIndex index of run with in line to start searching for run start display index at.
			@param type type of run the run group belongs to
			@return display index of the first run start that heads a run group.
		**/
		virtual TextIndex FindInitialRunStart(int32 at, int32 runIndex, RunDescription::RunType type) = 0;
		
		/**	
			Find the first run display offset for a set of associated runs that span multiple lines. For instance, a note may span many lines
			and have many associated run this routine will find the line that the note starts in and get the display index of the first character in the note.
			Useful to find the starting galley display offset of a note or deleted text run that has been split across several lines.
			@param storyIndex index of line to start searching for run start at
			@param at index of line to start searching for run start at
			@param runIndex index of run with in line to start searching for run start display index at.
			@param type type of run the run group belongs to
			@return display index of the first run start that heads a run group.
		**/
		virtual TextIndex FindInitialRunStart(int32 storyIndex, int32 at, int32 runIndex, RunDescription::RunType type) = 0;
		
		/**	
			Find a run in the line that contains a galley display offset
			@param galleyDisplayOffset display index to search for
			@param lineIndex line that we want to search within.
			@param runIndex return the index of the run.
			@return return a discription of the run that is at a given display index.
		**/
		virtual RunDescription *FindRunAtDisplayOffset(TextIndex galleyDisplayOffset, int32 lineIndex, int32 *runIndex = nil) = 0;
		
		/**	
			Find a run in the line that contains a galley display offset
			@param storyIndex index of story to search within.
			@param galleyDisplayOffset display index to search for
			@param lineIndex line that we want to search within.
			@param runIndex return the index of the run.
			@return return a discription of the run that is at a given display index.
		**/
		virtual RunDescription *FindRunAtDisplayOffset(int32 storyIndex, TextIndex galleyDisplayOffset, int32 lineIndex, int32 *runIndex = nil) = 0;
		
		/**	
			This routine gets text in blocks of continuous font styles. Useful when you would like to measure text widths and for drawing.
			@param model textmodel to get text for
			@param description desciption of run to get the text of
			@param textStart text index to start getting text at.
			@param textLength length of text interested in getting maximum.
			@param textContent text returned in this parameter.
			@param widths an array of glyph widths is filled out by GetRunChunk (array is preallocated by caller).
			@param showInvisibles kTrue if want hidden character information to be filled out. See IStoryService.
			@param bufferSize max number of characters that preallocated buffers will hold
			@param fontStyle returns the font style that the text should draw in
			@param capMode return the Capitize mode that the text would draw in
			@param lineIndex index of the line to get text for
			@param runIndex index of the run to get text for
			@return return number of characters actually returned
		**/
		virtual int32 GetRunChunk(ITextModel *model, const RunDescription &description, TextIndex textStart, int32 textLength, WideString &textContent, 
							float *widths, bool16 showInvisibles, int32 bufferSize, IFontMgr::FontStyleBits &fontStyle, IDrawingStyle::CapitalizeMode &capMode,
							int32 lineIndex, int32 runIndex) = 0;
							
		/**	
			This routine gets text in blocks of continuous font styles. Useful when you would like to measure text widths and for drawing.
			@param storyIndex index of story to get the text of
			@param model textmodel to get text for
			@param description desciption of run to get the text of
			@param textStart text index to start getting text at.
			@param textLength length of text interested in getting maximum.
			@param textContent text returned in this parameter.
			@param widths an array of glyph widths is filled out by GetRunChunk (array is preallocated by caller).
			@param showInvisibles kTrue if want hidden character information to be filled out. See IStoryService.
			@param bufferSize max number of characters that preallocated buffers will hold
			@param fontStyle returns the font style that the text should draw in
			@param capMode return the Capitize mode that the text would draw in
			@param lineIndex index of the line to get text for
			@param runIndex index of the run to get text for
			@return return number of characters actually returned
		**/
		virtual int32 GetRunChunk(int32 storyIndex, ITextModel *model, const RunDescription &description, TextIndex textStart, int32 textLength, WideString &textContent, 
							float *widths, bool16 showInvisibles, int32 bufferSize, IFontMgr::FontStyleBits &fontStyle, IDrawingStyle::CapitalizeMode &capMode,
							int32 lineIndex, int32 runIndex) = 0;
							
		
		/**	
			This routine gets text in blocks of continuous font styles. Useful when you would like to measure text widths and for drawing.
			This version does not get actual text
			just the glyph data. This is more efficient than the other two versions of this call because the glyph data is cached while
			the text unicode data is not.
			@param storyIndex index of story to get the text of
			@param model textmodel to get text for
			@param description desciption of run to get the text of
			@param textStart text index to start getting text at.
			@param textLength length of text interested in getting maximum.
			@param widths an array of glyph widths is filled out by GetRunChunk (array is preallocated by caller).
			@param showInvisibles kTrue if want hidden character information to be filled out. See IStoryService.
			@param bufferSize max number of characters that preallocated buffers will hold
			@param fontStyle returns the font style that the text should draw in
			@param capMode return the Capitize mode that the text would draw in
			@param lineIndex index of the line to get text for
			@param runIndex index of the run to get text for
			@return return number of characters actually returned
		**/
		virtual int32 GetRunChunk(int32 storyIndex, ITextModel *model, const RunDescription &description, TextIndex textStart, int32 textLength, 
							float *widths, bool16 showInvisibles, int32 bufferSize, IFontMgr::FontStyleBits &fontStyle, IDrawingStyle::CapitalizeMode &capMode,
							int32 lineIndex, int32 runIndex) = 0;
							
		/**	
			Draw a regular text run. That is a run that is part of the primary text model. Called by DrawRuns() and some instances of DrawRun()
			@param at index line to draw text of
			@param gPort graphics port to draw text in
			@param displayFont font to draw in
			@param displaySize size of text to draw
			@param runIndex index of the run to draw.
			@param textColor color to draw the text
			@param drawPt where to draw the text.
			@param showInvisibles kTrue if want hidden character information to be filled out. See IStoryService.
			@param showInvisibles should it show the invisible character symbols
			@return returns width of text drawn
		**/
		virtual PMReal DrawRegularTextRun(int32 at, IGraphicsPort *gPort, IPMFont *displayFont, PMReal displaySize, 
									int32 runIndex, const RealAGMColor &textColor, const PMPoint &drawPt, bool16 showInvisibles) = 0;

		/**
			Get the index of a run at a given point on the screen
			@param storyIndex index of story to use to find point in.
			@param point where on the screen is of interest. Given in terms of 0 being first line in view.
			@param lineIndex filled in by the routine this is the index of the line the returned run is in
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 FindIndexOfRunAtPoint(int32 storyIndex, const PMPoint &point, int32 *lineIndex) = 0;
		
		/**
			Same as other FindIndexOfRunAtPoint but if you already know the line that was hit use this one because it is faster.
			@param storyIndex index of story to use to find point in.
			@param point where on the screen is of interest. Given in terms of 0 being first line in view.
			@param lineIndex of the line which was hit.
			@return index of the run (may be -1 if none is found).
		**/
		virtual int32 FindIndexOfRunAtPoint(int32 storyIndex, const PMPoint &point, int32 lineIndex) = 0;


		/**
			Internal use for handling lines that draw over other lines. Called by DrawRun().
			@param at index of line to draw overlap portion of
			@param gPort port to draw in
			@param scrollCompensationValue vertical scroll compensation value
			@param description description of line to draw overlap portion of
			@param topLineInDraw optimiztion kTrue if this is the first line drawn in a inval
			@param storyIndex index of story to draw overlaps in.
			@return void.
		**/
		virtual void DrawLineOverlaps(int32 at, IGraphicsPort *gPort, const PMPoint &scrollCompensationValue,
								const LineDescription &description, bool16 topLineInDraw, int32 storyIndex) = 0;
		
		/** 	Given a starting run this routine will give back information on the extent of the whole block of associated runs.
				For example, a note may span many lines and consist of many individual runs this routine will give information on
				both where the note begins an ends and what the total text span of the run is in galley/story display indexes. This
				is useful to know when navigating through text in the order things are displayed rather than the order text is actually
				stored in the text moded.
				Return true if succesful and false otherwise
				@param storyIndex TextLines story index of the story we are interested in (see ITextLines interface)
				@param runIndex The location of the start run to begin search at
				@param type the type of the start run
				@param displayIndexRange returns display index range of the total extended run
				@param extendedRunStart returns the lineIndex and runIndex of the first run in the extended run
				@param extendedRunEnd return the lineIndex and the runIndex of the last run in the extended run.
		*/						
		virtual bool16 GetExtendedRunSpanInformation(int32 storyIndex, const RunLocation &runIndex, RunDescription::RunType type, 
													RangeData *displayIndexRange, 
													RunLocation *extendedRunStart, RunLocation *extendedRunEnd) = 0;
};

#endif 		// __ITextRuns__
